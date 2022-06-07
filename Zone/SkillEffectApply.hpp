#pragma once
#include "pch.h"

#include "Generic.h"

#include "ShinePlayer.hpp"

namespace SkillEffectApply
{
    bool CheckWeapon;

    void(__thiscall* sbe_BlastLocate_Org) (class SkillBlastEffect* pthis);
    void(__thiscall* sbe_BlastObject_Org) (class SkillBlastEffect* pthis);
	
    class SkillBlastEffect
    {
        HOOK_PUB_S void Install_SkillFix()
        {
            CheckWeapon = Config->GetBoolean("Feature", "SkillDemandWeaponChecking", false);
        	
#ifdef DEMO_VERSION
            CheckWeapon = false;
#endif

            sbe_BlastLocate_Org = (void(__thiscall*) (SkillBlastEffect* pthis))Detour(0x00584160, MF(sbe_BlastLocate));
            sbe_BlastObject_Org = (void(__thiscall*) (SkillBlastEffect* pthis))Detour(0x00583BC0, MF(sbe_BlastObject));
        }

        HOOK_PUB_M bool IsCorrectWeapon(ActiveSkillInfo* skill, ushort itemId)
        {
            if (itemId == 0xFFFF)
            {
                return skill->DemandType == DT_ALL || skill->DemandType == DT_NONE;
            }

            auto dataBox = Global::g_ItemDataBox[itemId];

            if (dataBox == nullptr)
            {
                return false;
            }

            auto itemInfo = dataBox->data;
            switch (skill->DemandType)
            {
	            case DT_ONEHAND:
	                return !itemInfo->TwoHand;
	            case DT_TWOHAND:
	                return itemInfo->TwoHand;
	            case DT_ALL:
	            case DT_NONE:
	                return true;
	            case DT_WEAPON:
	                return itemInfo->Class == ITEMCLASS_WEAPON;
	            case DT_HAMMER:
                    // return !itemInfo->TwoHand;
                    return itemInfo->WeaponType == WT_HAMMER;
	            case DT_MACE:
                    // return !itemInfo->TwoHand;
	                return itemInfo->WeaponType == WT_MACE;
	            case DT_SHIELD:
                    return true;
	                // return itemInfo->Class == ITEMCLASS_SHIELD;
	            case DT_BOW:
                    // return itemInfo->TwoHand;
	                return itemInfo->WeaponType == WT_BOW;
	            case DT_CBOW:
                    // return itemInfo->TwoHand;
	                return itemInfo->WeaponType == WT_CROSSBOW;
	            case DT_STAFF:
                    // return itemInfo->TwoHand;
	                return itemInfo->WeaponType == WT_STAFF;
	            case DT_WAND:
                    // return itemInfo->TwoHand;
	                return itemInfo->WeaponType == WT_WAND;
	            case DT_CLAW:
                    //return itemInfo->TwoHand;
	                return itemInfo->WeaponType == WT_CLAW;
	            case DT_DSWORD:
                    // return itemInfo->TwoHand;
	                return itemInfo->WeaponType == WT_DSWORD;
	            case DT_BLADE:
                    // return itemInfo->TwoHand;
	                return itemInfo->WeaponType == WT_BLADE;
                case MAX_WEAPONDEMANDTYPE:
	                return true;
            }
        }

    	HOOK_PUB_M void sbe_BlastLocate()
        {
            auto active = sbe_SkillIndex->sdi_Activ;
        	
            if (sbe_CasterObject == nullptr)
            {
                return;
            }

        	if (sbe_CasterObject->IsCharacter())
        	{
                if (active->First != TARGET_SPOT)
                {
                    sbe_CasterObject->NotifyExploit("Skills: target skill on location", "Only location skills can be used on a location.");
                    return;
                }
        		
                if (CheckWeapon)
                {
                    ITEM_INVEN temp;
                    auto weapon = sbe_CasterObject->so_ply_EquipWeapon(&temp);
                    auto canUse = weapon != nullptr ? IsCorrectWeapon(active, weapon->iic_Item.iti_itemstruct.itemid) : IsCorrectWeapon(active, 0xFFFF);
                    
                    if (!canUse && active->DemandType != DT_SHIELD)
                    {
                        sbe_CasterObject->NotifyExploit("Skills: invalid weapon to use skill", "Wrong weapon equipped to use this skill.");
                        return;
                    }                
                }

                if (sbe_CasterObject->so_Field->fm_MapInfo->InSide && active->CannotInside)
                {
                    sbe_CasterObject->so_ply_Notice("Cannot use this skill on this map.");
                    return;
                }
        	}

            sbe_BlastLocate_Org(this);
        }
    	
    	HOOK_PUB_M void sbe_BlastObject()
        {
            auto active = sbe_SkillIndex->sdi_Activ;
        	
			if (sbe_CasterObject == nullptr || sbe_TargetObject == nullptr)
			{
                return;
			}

        	if (sbe_CasterObject->IsCharacter())
        	{
                if (CheckWeapon)
                {
                    ITEM_INVEN garb;
                    auto weapon = sbe_CasterObject->so_ply_EquipWeapon(&garb);
                    auto canUse = weapon != nullptr ? IsCorrectWeapon(active, weapon->iic_Item.iti_itemstruct.itemid) : IsCorrectWeapon(active, 0xFFFF);

                    if (!canUse && active->DemandType != DT_SHIELD)
                    {
                        sbe_CasterObject->NotifyExploit("Skills: invalid weapon to use skill", "Wrong weapon equipped to use this skill.");
                        return;
                    }
                }

        		if (sbe_CasterObject->so_Field->fm_MapInfo->InSide && active->CannotInside)
        		{
                    sbe_CasterObject->so_ply_Notice("Cannot use this skill on this map.");
                    return;
        		}
                        		
                if (active->First == TARGET_SPOT)
                {
                    sbe_CasterObject->NotifyExploit("Skills: location skill on single target", "This skill is only usable on a location.");
                    return;
                }
        		
        		if (active->First == TARGET_ME && sbe_CasterObject != sbe_TargetObject)
        		{
                    sbe_CasterObject->NotifyExploit("Skills: self skill on other target", "This skill is only usable on yourself.");
                    return;
        		}

        		if (active->First == TARGET_ENEMYUSER && !sbe_TargetObject->IsCharacter())
        		{
                    sbe_CasterObject->NotifyExploit("Skills: enemy character skill on non-character or friendly object", "This skill is only usable on enemy players.");
                    return;
                }

        		if ((active->First == TARGET_ENEMY || active->First == TARGET_ENEMYUSER || active->First == TARGET_ENEMYGUILD) && !sbe_CasterObject->so_mobile_IsEnemy(sbe_TargetObject))
        		{
                    sbe_CasterObject->NotifyExploit("Skills: enemy skill on friendly object", "This skill is only usable on enemies.");
                    return;
                }
        	}

            sbe_BlastObject_Org(this);
        }
    	
        HOOK_PROT_M unsigned int sbe_BlastTick;
        HOOK_PROT_M unsigned __int16 sbe_Index;
        HOOK_PROT_M char _pad1[0x2];
        HOOK_PROT_M SkillDataBox::SkillDataIndex* sbe_SkillIndex;
        HOOK_PROT_M unsigned int sbe_CasterRegistNumber;
        HOOK_PROT_M ShineObjectClass::ShineMobileObject* sbe_CasterObject;
        HOOK_PROT_M SKILL_EMPOWER sbe_Empow;
        HOOK_PROT_M char _pad2[0x2];
        HOOK_PROT_M unsigned int sbe_TargetRegistNumber;
        HOOK_PROT_M ShineObjectClass::ShineObject* sbe_TargetObject;
        HOOK_PROT_M SHINE_XY_TYPE sbe_TargetLocate;
        HOOK_PROT_M int sbe_LastDamage;
        HOOK_PROT_M MultiHitArgument sbe_MultiHitArgument;
        HOOK_PROT_M char sbe_nLightningWaveCnt;
        HOOK_PROT_M char _pad3;
        HOOK_PROT_M unsigned __int16 sbe_nSetEffectForJustSkill;
    };
}
