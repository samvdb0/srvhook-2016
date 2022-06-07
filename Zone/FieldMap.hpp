#pragma once
#include "pch.h"

#include "Generic.h"

class __declspec(align(8)) FieldMap
{
    struct FieldBonus
    {
        int fb_Experience;
        int fb_DropRate;
    };

    struct BroadcastFunc
    {
        char _size[0x40];
    };
	
    enum CameraState
    {
        CS_NONE = 0x0,
        CS_MOVING = 0x1,
        CS_MAX = 0x2,
    };

    HOOK_PUB_M enum FM_MarkingError
    {
        FM_MARKSUCCESS = 0x0,
        FM_MAPNOTEXIST = 0x1,
        FM_OTHERMAP = 0x2,
        FM_BLOCKED = 0x3,
    };
	
    struct LuaField
    {
        class LuaScriptScenario* LuaScript;
        std::string PlyMapLogin;
        std::string PlyItemUse;
        std::string TutorialStep;
        std::string PlyMapLogout;
        std::string ObjectDied;
        std::string ServantSummon;
        std::string RankingValue;
    };

    Name3 fm_MapID;
    FieldOption::FieldAttr* fm_FieldOption;
    MapInfo* fm_MapInfo;
    MapBlock::MapBlockInformation* fm_BlockInfo;
    unsigned int fm_XSize;
    unsigned int fm_YSize;
    char _fm_SlantedListPoint[0x1C];
    unsigned int fm_KQHandle;
    unsigned __int16 fm_KQID;
    __declspec(align(4)) void* fm_Multiflex;
    MobDeadCount fm_MobDeadCount;
    FieldBonus fm_FieldBonus;
    char fm_PKField;
    __declspec(align(4)) BroadcastFunc fm_BroadFunc;
    GuildWarInfo fm_GuildTournamentInform;
    Navigator::VirtualMap fm_NavigatorMap;
    void* fm_pGuildTournamentSystem;
    int m_nGuildTournamentMapFlag;
    NPCManager::LinkInformTemplete m_SaveLinktoData;
    __declspec(align(4)) std::set<ABSTATEINDEX> fm_RefuseAbstate;
    FieldMap::CameraState fm_CameraState;
    FieldMap::LuaField fm_LuaScript;
    BoothManager fm_BoothManager;
    FieldFlag fm_FieldFlag;
    __declspec(align(4)) unsigned int fm_ReviveDelaySec;
    ID_LEVEL_TYPE fm_eLevelType;
};
