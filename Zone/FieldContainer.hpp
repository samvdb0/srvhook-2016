#pragma once
#include "pch.h"
#include "Generic.h"
#include "FieldMap.hpp"
#include "ShinePlayer.hpp"

struct EnterFieldErrInfo
{
    unsigned __int16 LevelFrom;
    unsigned __int16 LevelTo;
};

enum ENTER_MAP_ERR
{
    ENTER_MAP_ERR_NONE = 0x0,
    ENTER_MAP_ERR_DATA_NULL = 0x1,
    ENTER_MAP_ERR_LEVEL_LIMIT = 0x2,
    ENTER_MAP_ERR_PARTY_LIMIT = 0x3,
    ENTER_MAP_ERR_NEED_PARTY_OR_QUEST = 0x4,
    ENTER_MAP_ERR_NEED_RAID = 0x5,
    ENTER_MAP_ERR_NEED_ITEM = 0x6,
};

ENTER_MAP_ERR(__stdcall* fc_CanEnterIndun_Org)(ShineObjectClass::ShinePlayer* player, FieldOption::InstanceDungeonInfo* info, unsigned int* outRegNum, INSTANCE_DUNGEON::CATEGORY* outCategory);
char(__stdcall* cm_PlayerinToInstanceDungeon_Org)(Name3* pInsMapName, FieldOption::InstanceDungeonInfo* Info, unsigned int RegisterNumber, INSTANCE_DUNGEON::CATEGORY Category);

struct __declspec(align(8)) FieldContainer
{
    HOOK_PUB_S void Install_SoloGuildInstances()
    {
        fc_CanEnterIndun_Org = (ENTER_MAP_ERR(__stdcall*)(ShineObjectClass::ShinePlayer*, FieldOption::InstanceDungeonInfo*, unsigned int*, INSTANCE_DUNGEON::CATEGORY*))Detour(0x004624D0, fc_CanEnterIndun);
        cm_PlayerinToInstanceDungeon_Org = (char(__stdcall*)(Name3*, FieldOption::InstanceDungeonInfo*, unsigned int, INSTANCE_DUNGEON::CATEGORY))Detour(0x00486D80, cm_PlayerIntoInstanceDungeon);
    }

	HOOK_PUB_S ENTER_MAP_ERR fc_CanEnterIndun(ShineObjectClass::ShinePlayer* player, FieldOption::InstanceDungeonInfo* info, unsigned int* outRegNum, INSTANCE_DUNGEON::CATEGORY* outCategory)
    {
        switch (info->EntranceType)
        {
	        case 0:
        		if (player->so_PartyRegistNumber() != 0xFFFF || player->so_GetRaid() != nullptr)
        		{
                    player->so_ply_Notice("Instance is solo only. Please leave your party/raid.");
                    return ENTER_MAP_ERR::ENTER_MAP_ERR_DATA_NULL;
        		}

                *outRegNum = player->so_GetCharRegistNumber();
                *outCategory = INSTANCE_DUNGEON::CATEGORY::CATEGORY_INDIVIDUAL;
	            break;
	        case 1:
                if (player->so_ply_GetMyGuildNo() == 0)
                {
                    player->so_ply_Notice("Instance is guild only. Please join a guild.");
                    return ENTER_MAP_ERR::ENTER_MAP_ERR_DATA_NULL;
                }

                *outRegNum = player->so_ply_GetMyGuildNo();
                *outCategory = INSTANCE_DUNGEON::CATEGORY::CATEGORY_GUILD;
	            break;
	        case 2:
        		if (player->so_PartyRegistNumber() == 0xFFFF || player->so_GetRaid() != nullptr)
        		{
                    player->so_ply_Notice("Instance is party only. Please join a party/leave your raid.");
                    return ENTER_MAP_ERR::ENTER_MAP_ERR_NEED_PARTY_OR_QUEST;
        		}
	            break;
            case 3:
        		if (player->so_GetRaid() != nullptr)
        		{
                    player->so_ply_Notice("Instance is raid only. Please join a raid.");
                    return ENTER_MAP_ERR::ENTER_MAP_ERR_NEED_RAID;
        		}
            default:
                break;
        }
    	
        return fc_CanEnterIndun_Org(player, info, outRegNum, outCategory);
    }

	HOOK_PUB_S bool cm_PlayerIntoInstanceDungeon(Name3* name, FieldOption::InstanceDungeonInfo* info, unsigned int registerNumber, INSTANCE_DUNGEON::CATEGORY category)
    {
    	switch (info->EntranceType)
    	{
			case 0:
    			category = INSTANCE_DUNGEON::CATEGORY_INDIVIDUAL;
                break;
			case 1:
    			category = INSTANCE_DUNGEON::CATEGORY_GUILD;
                break;
			case 2:
    			category = INSTANCE_DUNGEON::CATEGORY_PARTY;
                break;
			case 3:
            case 4:
    			// don't touch category.
                break;
            default:
                return false;
    	}
    	
        return cm_PlayerinToInstanceDungeon_Org(name, info, registerNumber, category);
    }
	
    FieldOption fc_FieldOption;
    FieldMap fc_Array[512];
    struct
    {
        FieldOption::GuildTournamentMapStr** attr;
        int number;
    } fc_GuildTournamentMap;
    struct __declspec(align(4))
    {
        FieldOption::InstanceDungeonInfo** Attribute;
        int NumberOf;
        bool bIsConsume;
    } fc_InstanceDungeon;
    struct
    {
        FieldOption::TutorialMapInfo** ppAttribute;
        int nNumber;
    } fc_TutorialMap;
};
