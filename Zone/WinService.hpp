#pragma once
#include "pch.h"

#include "CAnnounceSystem.hpp"
#include "FieldContainer.hpp"
#include "Generic.h"
#include "ItemDropFromMob.hpp"

#include "ShineMob.hpp"
#include "ShinePlayer.hpp"

#include "LuaScript.hpp"
#include "ZoneServer.hpp"

#include "GameDBSession.hpp"
#include "SkillEffectApply.hpp"

#include "ClientSession.hpp"
#include "LuaScriptScenario.hpp"
#include "NPCItemList.hpp"
#include "KQRegenTable.hpp"

#include "HookScript.hpp"
#include "ItemMixData.hpp"

bool(__thiscall* onServiceStart_Org)(void* pthis);
class WinService
{
    HOOK_PUB_S void InstallHook()
    {
        onServiceStart_Org = (bool(__thiscall*)(void*)) Detour(0x006533C0, MF(onServiceStart));
    	
		#ifdef CONSOLE
        Detour(0x00653290, MF(QueryServiceStatus));
        Detour(0x006535B0, MF(StartDispatcher));
		#endif
    }
	
    HOOK_PUB_M int QueryServiceStatus(uint* result, const char* netMachine, const char* serviceName)
    {
        return 1;
    }

	HOOK_PUB_S bool OnStart_Service()
    {
        return CallStaticFunction<0x0049DC00, bool>();
    }

	HOOK_PUB_S bool ServiceLoop()
    {
	    return CallStaticFunction<0x00653480, bool>();
    }

    HOOK_PUB_M bool onServiceStart()
    {
        std::vector<std::function<void()>> toHook;

        NoticeEnabled = Config->GetBoolean("Hook", "EnableNotice", false);
        LogEnabled = Config->GetBoolean("Hook", "EnableLog", false);

        // Always-On fixes    	
        toHook.emplace_back(&LuaScript::Install_GRFix);
        toHook.emplace_back(&ZoneServer::Install_GRFix);

        toHook.emplace_back(&ItemActionObserveManager::Install_IAFix);
        toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_IAFix);

        toHook.emplace_back(&ShineObjectClass::ShineMob::Install_GatherRangeFix);
        toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_GatherRangeFix);

        toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_ItemMixFix);

        toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_TownPortalFix);

        toHook.emplace_back(&SkillEffectApply::SkillBlastEffect::Install_SkillFix);

        toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_LHFix);

        toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_BuffDeleteFix);

        toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_NoArrangeInVendor);
        toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_NoSplitInVendor);
    	
        toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_HOBMaxUsage);

        toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_TeleportWithMountFix);
        toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_NameCheck);
        toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_GuildMoneyExploitFix);

        toHook.emplace_back(&ClientSession::Install_PacketProtection);

        toHook.emplace_back(&LuaScriptScenario::Install_LuaFuncs);

        DataStore::Load();

        if (Config->GetBoolean("Feature", "AutoLearnSkill", false))
        {
            toHook.emplace_back(&CAnnounceSystem::Install_LevelUp);
            toHook.emplace_back(&GameDBSession::Install_AutoSkillFix);
        }

        if (Config->GetBoolean("Feature", "AntiLagUseTimers", false))
        {
            toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_PremiumInvFix);
            toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_RewardInvFix);
            toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_ChestSpamFix);
        }

        if (Config->GetBoolean("Feature", "LevelUpAtLuaFix", false))
        {
            toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_LevelUpAtLuaFix);
        }

        if (Config->GetBoolean("Feature", "MobPercentageExp", false))
        {
            toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_MobExp);
        }

        if (Config->GetBoolean("Feature", "PickupAnnounce", false))
        {
            toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_PickupNotice);
        }

        if (!Config->GetBoolean("Feature", "RemoveSkinOnBreak", true))
        {
            auto weaponCostumAddr = (DWORD*)0x005209D4;
            auto shieldCostumAddr = (DWORD*)0x00520C07;

            uchar disableWeaponCostumDelete[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            uchar disableShieldCostumDelete[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

            WriteMem(weaponCostumAddr, disableWeaponCostumDelete, sizeof disableWeaponCostumDelete);
            WriteMem(shieldCostumAddr, disableShieldCostumDelete, sizeof disableShieldCostumDelete);
        }
    	
        if (Config->GetBoolean("Experimental", "CustomDropSystem", false))
        {
            toHook.emplace_back(&ItemDropFromMob::DropItemListForSpecies::Install_DropSystem);
            toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_CenDropNotice);
        }

        if (Config->GetBoolean("Experimental", "SoloGuildInstances", false))
        {
            toHook.emplace_back(&FieldContainer::Install_SoloGuildInstances);
            //uchar skipTypeCheck[] = { 0xEB, 0x1F };
            //WriteMem((DWORD*)0x005A9396, skipTypeCheck, sizeof skipTypeCheck);

            uchar dontEndOnPartyFail[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            uchar skipInstanceCheck[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

            uchar expireTime = 1 /*sec*/ * 10;
            uchar expireTime1[] = { 0xC7, 0x06, expireTime, 0x00, 0x00, 0x00 };
            uchar expireTime2[] = { 0x05, expireTime, 0x00, 0x00, 0x00 };
        	
            WriteMem((DWORD*)0x005A93B1, dontEndOnPartyFail, sizeof dontEndOnPartyFail);
            WriteMem((DWORD*)0x00486A0F, expireTime1, sizeof expireTime1);
            WriteMem((DWORD*)0x00486A15, expireTime2, sizeof expireTime2);
            WriteMem((DWORD*)0x00440A1D, skipInstanceCheck, sizeof skipInstanceCheck);
            WriteMem((DWORD*)0x00440A3E, skipInstanceCheck, sizeof skipInstanceCheck);
        }

        if (Config->GetBoolean("Feature", "OverrideRegenFailMap", false))
        {
            toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_RegenFailMap);
        }

        if (Config->GetBoolean("Experimental", "RemoveMerchantLimit", false))
        {
            toHook.emplace_back(&NPCItemList::NPCItemListTable::Install_MerchantLimit);
        }

        if (Config->GetBoolean("Experimental", "RemoveRegenLimit", false))
        {
            toHook.emplace_back(&PineScriptMobRegenerator::Install_RegenTableLimit);
            toHook.emplace_back(&KQRegenTable::Install_RegenTableLimit);
        }

        if (Config->GetBoolean("Experimental", "AnimationTimeChecking", false))
        {
            toHook.emplace_back(&ShineObjectClass::ShinePlayer::Install_AnimationCheck);
        }

    	// auto pickupRange = Config->GetInteger("Feature", "")
        // memcpy((void*)0x00530C32 (void*) (125*125), 4);

    	// requires cc @ zone => ::GetMixItemIndex
    	if (Config->GetInteger("Lunaris", "NewItemCombine", 0) == 4568267)
    	{
            toHook.emplace_back(&ItemMixData::Install_MixOverride);
    	}

        // uchar noTmf[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
        // WriteMem((DWORD*)0x005A9E7F, noTmf, sizeof noTmf);

        for (UINT32 i = 0; i < toHook.size(); i++)
        {
            toHook.at(i)();
        }

        if (Config->GetBoolean("Feature", "HookScriptZone", false))
        {
            ShineObjectClass::ShinePlayer::Install_Commands();
        	
            HookScript::Instance = new HookScript();
            HookScript::Instance->Load(FORMAT_STR("..\\%s\\Lua.Zone\\hook.lua", Config->Get("Path", "Hook", "9Data/Hook")));
        }

        // Log::Info(FORMAT_STR("Loaded %d features.", toHook.size()));

#ifndef CONSOLE
        return onServiceStart_Org(this);
#else
        return OnStart_Service();
#endif
    }

	HOOK_PUB_M bool StartDispatcher(String* svcName, bool(__cdecl* startCallBack)(), void(__cdecl* stopCallBack)())
    {
        serviceStartFunc = startCallBack;
        serviceStopFunc = stopCallBack;
    	
        return ServiceLoop();
    }

	// Values
    char _pad[0x4];
    HOOK_PROT_M bool(__cdecl* serviceStartFunc)();
    HOOK_PROT_M void(__cdecl* serviceStopFunc)();
    HOOK_PROT_M String serviceName;
    HOOK_PROT_M SERVICE_STATUS_HANDLE__* handleServiceStatus;
    HOOK_PROT_M void* handleServiceEvent;
    HOOK_PROT_M unsigned int statusEvent;
    HOOK_PROT_M _SERVICE_STATUS ssQueryControl;
};
