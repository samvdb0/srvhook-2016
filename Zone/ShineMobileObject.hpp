#pragma once
#include "pch.h"

#include "ShineObject.hpp"

namespace ShineObjectClass
{
    class ShineMobileObject : public ShineObject
    {
        struct TA
        {
            TargetAnalyser* analyser;
        };

        struct __declspec(align(4)) AS
        {
            AbnormalStateContainer::AbstateListInObject abstatelist;
            char parameterchange;
        };

        struct MoveStateStruct
        {
            MOVE_STATE eMoveState;
            SHINE_XY_TYPE PrevLocation;
            unsigned int nStartTime;
            unsigned int nCheckTime;
        };

        struct __declspec(align(2)) SkillCastStruct
        {
            unsigned int scs_BlastTime;
            unsigned __int16 scs_Skill;
            struct
            {
                ShineObjectClass::ShineObject* target;
                SHINE_XY_TYPE locate;
            } scs_BattleSkill;
            struct
            {
                SkillDataBox::SkillDataIndex* sklidx;
                GatherProduce::RecipeBook::ProductIndex* prdidx;
            }  scs_ProduceSkill;
            struct __declspec(align(4))
            {
                int cooltime_millisec;
                ItemDataBox::ItemDataBoxIndex* itemdata;
                char invenslot;
                char bAutoUse;
            } scs_UseItem;
            SKILL_EMPOWER scs_Empower;
            char scs_AttackCode;
        };

        char _size[0x1EA8 - 0x167];
    	/*
        struct
        {
            unsigned __int16 movecommand;
            PROTO_NC_ACT_SOMEONEMOVEWALK_CMD movepacket;
        } smo_MovePacketBuffer;
        DeadCheck smo_DeadCheck;
        unsigned __int16 smo_WhoKillMe;
        unsigned __int16 smo_WhoClickMe;
        ShineObjectClass::ShineMobileObject::TA smo_TargetAnalyser;
        MoveManager smo_MoveManager;
        ShineObjectClass::ShineMobileObject::AS smo_Abstate;
        struct
        {
            char tempmode;
            char* mode;
        } smo_Mode;
        struct
        {
            unsigned int lasthp;
            unsigned int lastsp;
            unsigned int maxhp;
            unsigned int maxsp;
        } smo_Recover;
        SpyNet::EspionageAgent smo_Spy;
        DuringBattle smo_duringbattle;
        CharClass* smo_CharClass;
        Parameter::Container smo_Param;
        AttackRhythm::CharArgument smo_AttackRhythm;
        unsigned __int16 smo_HPChangeOrder;
        struct
        {
            char alreadydead;
            int damagereserve;
        } smo_BattleObject;
        ShineObjectClass::ShineMobileObject::SkillCastStruct smo_SkillCast;
        struct
        {
            struct
            {
                int x;
                int y;
                MoveManager::MMState stt;
            } buffer[16];
            int point;
        } smo_SceneMoveManager;
        RulesOfEngagement* smo_RulesOfNormalAttack;
        struct
        {
            __int8 Retrate : 1;
            __int8 DuringFlying : 1;
            __int8 InFear : 1;
            __int8 DeadProcessComplete : 1;
            __int8 InSkillShift : 1;
            __int8 InCaptivate : 1;
            __int8 ChineCast : 1;
            __int8 DamageAbsorb : 1;
        } smo_Flag;
        int smo_admindamage;
        char smo_NormalAttackSequence[2];
        AbnormalStateDictionary::AbState::AbStateStr::AbStateStrArgument* smo_NaturalEnemy;
        unsigned __int16 smo_NormalSwingIndex;
        unsigned __int16 smo_SkillIndexLastCasting;
        ShineObjectClass::ShineMobileObject::MoveStateStruct smo_moveState;
        char smo_bStaticWalkSpeed;
        unsigned __int16 smo_nStaticWalkSpeed;
        char smo_bStaticRunSpeed;
        unsigned __int16 smo_nStaticRunSpeed;*/
    };

}