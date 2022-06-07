#pragma once
#include "Generic.h"

union NETCOMMAND
{
    unsigned __int16 protocol;
    struct
    {
        unsigned __int16 command : 10;
        unsigned __int16 department : 6;
    } str;
};

struct __declspec(align(2)) NETPACKETZONEHEADER
{
    unsigned __int16 clienthandle;
    unsigned int charregistnumber;
};

struct __declspec(align(1)) ZONERINGLINKAGESTART
{
    char machine;
    unsigned __int16 handle;
    unsigned int regnum;
};

struct __declspec(align(2)) PROTO_NC_CHAR_ZONE_CHARDATA_REQ
{
    unsigned __int16 wldmanhandle;
    Name5 charid;
};

struct __declspec(align(2)) PROTO_NC_CHAR_REGISTNUMBER_ACK
{
    unsigned int usrregnum;
    unsigned int chrregnum;
    PROTO_NC_CHAR_ZONE_CHARDATA_REQ loginreq;
};

struct __declspec(align(2)) PROTO_NC_DICE_TAISAI_DB_DICE_ROLL_RESULT_ACK
{
    unsigned __int16 nError;
    int nGameNo;
    NETPACKETZONEHEADER header;
    SHINE_ITEM_REGISTNUMBER nActiveDiceTaiSaiKey;
    unsigned __int16 nResultCnt;
    DiceRollApplyResult DiceRollResult[];
};

struct __declspec(align(1)) PROTO_NC_DICE_TAISAI_DB_RANK_ACK
{
    unsigned __int16 nError;
    NETPACKETZONEHEADER header;
    unsigned int nReqCharNo;
    char nRankCnt;
    DiceRankInfo Rank[];
};

struct PROTO_NC_DICE_TAISAI_DB_ITEM_ID_CHANGE_ACK
{
    unsigned __int16 nError;
    NETPACKETZONEHEADER header;
    ITEM_INVEN nInvenSlot;
    unsigned __int16 lockindex;
    __declspec(align(1)) SHINE_ITEM_REGISTNUMBER nDiceTaiSaiKey;
    unsigned __int16 nGameItemID;
    unsigned __int16 nMoneyCardItemID;
    unsigned __int64 nRewardMoney;
};

struct PROTO_NC_CHARSAVE_PKCOUNT_CMD
{
    unsigned int chrregnum;
    unsigned int pkcount;
};

struct PROTO_NC_CHARSAVE_LOCATION_CMD
{
    unsigned int chrregnum;
    Name3 map;
    SHINE_XY_TYPE coord;
    unsigned int kqhandle;
    Name3 map_kq;
    SHINE_XY_TYPE coord_kq;
};

struct __declspec(align(2)) PROTO_NC_CHARSAVE_ALL_ACK
{
    unsigned __int16 bufferlocation;
    unsigned int chrregnum;
};

struct __declspec(align(1)) PROTO_NC_CHARSAVE_LEVEL_CMD
{
    unsigned int chrregnum;
    char level;
    unsigned __int64 exp;
    unsigned int fame;
};

struct __declspec(align(2)) PROTO_NC_CHARSAVE_CHARSTAT_CMD
{
    unsigned int chrregnum;
    unsigned int CurPwrStone;
    unsigned int CurGrdStone;
    unsigned int CurHPStone;
    unsigned int CurSPStone;
    unsigned int CurHP;
    unsigned int CurSP;
    CHARSTATDISTSTR statdistribute;
};

struct __declspec(align(1)) PROTO_NC_CHARSAVE_ALL_REQ
{
    PROTO_NC_CHARSAVE_ALL_ACK handle;
    PROTO_NC_CHARSAVE_LEVEL_CMD level;
    PROTO_NC_CHARSAVE_LOCATION_CMD location;
    PROTO_NC_CHARSAVE_CHARSTAT_CMD stat;
};

struct PROTO_NC_CHARSAVE_2WLDMAN_QUEST_DOING_CMD
{
    struct __declspec(align(2)) tagQUESTDOING
    {
      unsigned int chrregnum;
      char bNeedClear;
      char nNumOfDoingQuest;
      PLAYER_QUEST_INFO QuestDoingArray[];
    };

    unsigned __int16 wldmanhandle;
    PROTO_NC_CHARSAVE_2WLDMAN_QUEST_DOING_CMD::tagQUESTDOING questdoing;
};

struct PROTO_NC_CHARSAVE_QUEST_DOING_REQ
{
    PROTO_NC_CHARSAVE_ALL_ACK handle;
    char bNeedClear;
    char nNumOfDoingQuest;
    PLAYER_QUEST_INFO QuestDoingArray[];
};

struct PROTO_NC_CHARSAVE_2WLDMAN_QUEST_READ_CMD
{
    struct __declspec(align(2)) tagQUESTREAD
    {
      unsigned int chrregnum;
      unsigned __int16 nNumOfReadQuest;
      unsigned __int16 QuestReadIDArray[];
    };

    unsigned __int16 wldmanhandle;
    PROTO_NC_CHARSAVE_2WLDMAN_QUEST_READ_CMD::tagQUESTREAD questread;
};

struct PROTO_NC_CHARSAVE_2WLDMAN_QUEST_REPEAT_CMD
{
    struct __declspec(align(2)) tagQUESTREPEAT
    {
      unsigned int chrregnum;
      unsigned __int16 nNumOfRepeatQuest;
      PLAYER_QUEST_INFO QuestRepeatArray[];
    };

    unsigned __int16 wldmanhandle;
    PROTO_NC_CHARSAVE_2WLDMAN_QUEST_REPEAT_CMD::tagQUESTREPEAT questrepeat;
};

struct PROTO_NC_CHARSAVE_ABSTATE_REQ
{
    PROTO_NC_CHARSAVE_ALL_ACK handle;
    unsigned __int16 abstatenum;
    ABSTATEREADBLOCK abstate[];
};

struct PROTO_NC_CHARSAVE_SKILL_REQ
{
    PROTO_NC_CHARSAVE_ALL_ACK handle;
    unsigned __int16 number;
    PROTO_SKILLREADBLOCK skill[];
};

struct __declspec(align(1)) PROTO_GAMEDATA_CMD
{
    struct ZoneServer
    {
        char bIsGM;
    };
	
    struct Client
    {
        unsigned __int16 partyno;
        unsigned __int16 nRaidNo;
    };

    PROTO_GAMEDATA_CMD::ZoneServer zone;
    PROTO_GAMEDATA_CMD::Client client;
};

struct PROTO_ITEM_CMD
{
    char numofitem;
    PROTO_ITEMPACKET_TOTAL ItemArray[];
};

struct __declspec(align(1)) PROTO_NC_CHARSAVE_2WLDMAN_ITEM_CMD
{
    unsigned __int16 wldmanhandle;
    unsigned int nCharNo;
    struct
    {
        __int8 nPacketOrderNum : 7;
        __int8 nIsLastOfInven : 1;
    } PacketOrder;
    char nPartMark;
    PROTO_ITEM_CMD itemstr;
};

struct PROTO_NC_CHAR_CHESTINFO_REQ
{
    PROTO_NC_CHARSAVE_ALL_ACK handle;
    unsigned __int16 number;
    unsigned __int16 loc[];
};

struct __declspec(align(1)) CHARACTER_TITLE_READBLOCK
{
    char nFirstConnection;
    char CurrentTitle;
    char CurrentTitleElement;
    unsigned __int16 CurrentTitleMobID;
    unsigned __int64 TitleValues[128];
    unsigned __int16 NumOfTitle;
    CT_INFO TitleArray[];
};

struct __declspec(align(2)) PROTO_NC_CHARSAVE_2WLDMAN_MISC_CMD
{
    unsigned __int16 wldmanhandle;
    unsigned __int64 cen;
    unsigned int fame;
    unsigned int nCharNo;
};

struct PROTO_NC_ITEMDB_ADMINCREATESUC_ACK
{
    unsigned __int16 lockindex;
};

struct __declspec(align(2)) PROTO_NC_ITEMDB_DEPOSIT_ACK
{
    NETPACKETZONEHEADER packheader;
    unsigned __int16 lockindex;
    unsigned __int64 cen;
    unsigned __int16 err;
};

struct __declspec(align(2)) PROTO_NC_ITEMDB_WITHDRAW_ACK
{
    NETPACKETZONEHEADER packheader;
    unsigned __int16 lockindex;
    unsigned __int64 cen;
    unsigned __int16 err;
};

struct __declspec(align(2)) PROTO_NC_ITEMDB_GUILD_STORAGE_WITHDRAW_ACK
{
    NETPACKETZONEHEADER packheader;
    unsigned __int16 lockindex;
    unsigned __int64 cen;
    unsigned __int16 err;
};

struct __declspec(align(1)) PROTO_NC_CHAR_BASE_CMD
{
    struct __declspec(align(1)) LoginLocation
    {
      Name3 currentmap;
      SHINE_COORD_TYPE currentcoord;
    };

    unsigned int chrregnum;
    Name5 charid;
    char slotno;
    char Level;
    unsigned __int64 Experience;
    unsigned __int16 CurPwrStone;
    unsigned __int16 CurGrdStone;
    unsigned __int16 CurHPStone;
    unsigned __int16 CurSPStone;
    unsigned int CurHP;
    unsigned int CurSP;
    unsigned int CurLP;
    unsigned int fame;
    unsigned __int64 Cen;
    PROTO_NC_CHAR_BASE_CMD::LoginLocation logininfo;
    CHARSTATDISTSTR statdistribute;
    char pkyellowtime;
    unsigned int pkcount;
    unsigned __int16 prisonmin;
    char adminlevel;
    union
    {
        unsigned int bin;
        struct
        {
            unsigned __int32 skillempower_can_reset : 1;
            unsigned __int32 restunion : 31;
        } str;
    } flags;
};

struct __declspec(align(1)) PROTO_NC_ITEMDB_OPEN_GUILD_STORAGE_ACK
{
    NETPACKETZONEHEADER zonepackheader;
    unsigned __int64 cen;
    unsigned __int64 nToken;
    char itemcounter;
    PROTO_ITEMPACKET_TOTAL itemarray[];
};

struct __declspec(align(2)) PROTO_NC_CHAR_MAPLOGIN_ACK
{
    unsigned __int16 charhandle;
    CHAR_PARAMETER_DATA param;
    SHINE_XY_TYPE logincoord;
};

struct PROTO_AVATAR_SHAPE_INFO
{
    __int8 race : 2;
    __int8 chrclass : 5;
    __int8 gender : 1;
    __int8 hairtype : 8;
    __int8 haircolor : 8;
    __int8 faceshape : 8;
};

struct __declspec(align(2)) PROTO_NC_CHAR_QUEST_DOING_CMD
{
    unsigned int chrregnum;
    char bNeedClear;
    char nNumOfDoingQuest;
    PLAYER_QUEST_INFO QuestDoingArray[];
};

struct PROTO_NC_CHAR_QUEST_DONE_CMD
{
    unsigned int chrregnum;
    unsigned __int16 nTotalDoneQuest;
    unsigned __int16 nTotalDoneQuestSize;
    unsigned __int16 nDoneQuestCount;
    unsigned __int16 nIndex;
    PLAYER_QUEST_DONE_INFO QuestDoneArray[];
};

struct __declspec(align(2)) PROTO_NC_CHAR_QUEST_READ_CMD
{
    unsigned int chrregnum;
    unsigned __int16 nNumOfReadQuest;
    unsigned __int16 QuestReadIDArray[];
};

struct __declspec(align(2)) PROTO_NC_CHAR_QUEST_REPEAT_CMD
{
    unsigned int chrregnum;
    unsigned __int16 nNumOfRepeatQuest;
    PLAYER_QUEST_INFO QuestRepeatArray[];
};

struct __declspec(align(2)) PROTO_NC_CHAR_ABSTATE_CMD
{
    unsigned int chrregnum;
    unsigned __int16 number;
    ABSTATEREADBLOCK abstate[];
};

struct __declspec(align(1)) PROTO_NC_CHAR_SKILL_CMD
{
    unsigned int chrregnum;
    PARTMARK PartMark;
    unsigned __int16 nMaxNum;
    unsigned __int16 number;
    PROTO_SKILLREADBLOCK skill[];
};

struct PROTO_NC_CHAR_CHARGEDBUFF_CMD
{
    unsigned __int16 NumOfChargedBuff;
    PROTO_CHARGEDBUFF_INFO ChargedBuff[];
};

struct PROTO_NC_CHAR_SKILL_PASSIVE_CMD
{
    unsigned __int16 number;
    unsigned __int16 passive[];
};

struct PROTO_NC_CHAR_ITEM_CMD
{
    struct
    {
        __int8 nPacketOrderNum : 7;
        __int8 nIsLastOfInven : 1;
    } PacketOrder;
    char nPartMark;
    PROTO_ITEM_CMD ItemCmd;
};

struct __declspec(align(1)) PROTO_NC_ITEMDB_OPENSTORAGE_ACK
{
    NETPACKETZONEHEADER zonepackheader;
    char curpage;
    char nOpenType;
    unsigned __int64 cen;
    char itemcounter;
    PROTO_ITEMPACKET_TOTAL itemarray[];
};

struct PROTO_NC_CHAR_CHESTINFO_CMD
{
    unsigned __int16 itemnum;
    unsigned __int16 location[];
};

struct __declspec(align(1)) PROTO_EQUIPMENT
{
    unsigned __int16 Equ_Head;
    unsigned __int16 Equ_Mouth;
    unsigned __int16 Equ_RightHand;
    unsigned __int16 Equ_Body;
    unsigned __int16 Equ_LeftHand;
    unsigned __int16 Equ_Pant;
    unsigned __int16 Equ_Boot;
    unsigned __int16 Equ_AccBoot;
    unsigned __int16 Equ_AccPant;
    unsigned __int16 Equ_AccBody;
    unsigned __int16 Equ_AccHeadA;
    unsigned __int16 Equ_MiniMon_R;
    unsigned __int16 Equ_Eye;
    unsigned __int16 Equ_AccLeftHand;
    unsigned __int16 Equ_AccRightHand;
    unsigned __int16 Equ_AccBack;
    unsigned __int16 Equ_CosEff;
    unsigned __int16 Equ_AccHip;
    unsigned __int16 Equ_Minimon;
    unsigned __int16 Equ_AccShield;
    struct
    {
        __int8 lefthand : 4;
        __int8 righthand : 4;
        __int8 body : 4;
        __int8 leg : 4;
        __int8 shoes : 4;
    } upgrade;
};

struct CHARBRIEFINFO_NOTCAMP
{
    PROTO_EQUIPMENT equip;
};

struct CHARBRIEFINFO_CAMP
{
    unsigned __int16 minihouse;
    char dummy[10];
};

struct STREETBOOTH_SIGNBOARD
{
    char signboard[30];
};

struct __declspec(align(1)) CHARBRIEFINFO_BOOTH
{
    CHARBRIEFINFO_CAMP camp;
    char issell;
    STREETBOOTH_SIGNBOARD signboard;
};

struct __declspec(align(1)) CHARBRIEFINFO_RIDE
{
    struct RideInfo
    {
        unsigned __int16 horse;
    };

    PROTO_EQUIPMENT equip;
    CHARBRIEFINFO_RIDE::RideInfo rideinfo;
};

struct __declspec(align(1)) STOPEMOTICON_DESCRIPT
{
    char emoticonid;
    unsigned __int16 emoticonframe;
};

struct CHARTITLE_BRIEFINFO
{
    char Type;
    char ElementNo;
    unsigned __int16 MobID;
};

struct __declspec(align(1)) PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD
{
    unsigned __int16 handle;
    Name5 charid;
    SHINE_COORD_TYPE coord;
    char mode;
    char chrclass;
    PROTO_AVATAR_SHAPE_INFO shape;
    union __declspec(align(1))
    {
        CHARBRIEFINFO_NOTCAMP notcamp;
        CHARBRIEFINFO_CAMP camp;
        CHARBRIEFINFO_BOOTH booth;
        CHARBRIEFINFO_RIDE ride;
    } shapedata;
    unsigned __int16 polymorph;
    STOPEMOTICON_DESCRIPT emoticon;
    CHARTITLE_BRIEFINFO chartitle;
    ABNORMAL_STATE_BIT abstatebit;
    unsigned int myguild;
    char type;
    char isGuildAcademyMember;
    char IsAutoPick;
    char Level;
    char sAnimation[32];
    unsigned __int16 nMoverHnd;
    char nMoverSlot;
    char nKQTeamType;
    char IsUseItemMinimon;
};

struct __declspec(align(1)) PROTO_NC_ITEMDB_CHARGED_LIST_ACK
{
    NETPACKETZONEHEADER packheader;
    unsigned __int16 ErrorCode;
    char nPartMark;
    unsigned __int16 NumOfChargedItem;
    PROTO_CHARGED_ITEM_INFO ChargedItemInfoList[];
};

struct __declspec(align(2)) PROTO_NC_ITEMDB_CHARGED_WITHDRAW_ACK
{
    NETPACKETZONEHEADER packheader;
    unsigned __int16 lockindex;
    PROTO_CHARGED_ITEM_INFO ChargedItemInfo;
    unsigned __int16 ErrorCode;
};

struct __declspec(align(1)) PROTO_NC_BOOTH_ITEMTRADE_REQ
{
    unsigned __int16 booth;
    char slot;
    unsigned __int16 itemnum;
};

struct __declspec(align(1)) PROTO_NC_CHAR_STAT_INCPOINTSUC_DB_ACK
{
    NETPACKETZONEHEADER header;
    char stat;
};

struct __declspec(align(1)) PROTO_NC_CHAR_STAT_DECPOINTSUC_DB_ACK
{
    NETPACKETZONEHEADER header;
    char stat;
    unsigned __int16 lockindex;
};

struct __declspec(align(2)) PROTO_NC_ITEM_BUY_REQ
{
    unsigned __int16 itemid;
    unsigned int lot;
};

struct __declspec(align(2)) PROTO_NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_ACK
{
    NETPACKETZONEHEADER packheader;
    unsigned __int16 lockindex;
    unsigned __int64 cen;
    unsigned __int16 Error;
};

struct __declspec(align(2)) PROTO_NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_DEPOSIT_ACK
{
    NETPACKETZONEHEADER packheader;
    unsigned __int16 lockindex;
    unsigned __int64 cen;
    unsigned __int16 Error;
};

struct _declspec(align(1)) PROTO_NC_GUILD_ACADEMY_DB_ACADEMY_REWARD_ACK
{
    NETPACKETZONEHEADER packheader;
    unsigned __int16 Error;
    unsigned int nCharNo;
    unsigned int nGuildNo;
    unsigned __int64 nWantMoney;
    unsigned int nWantItemCnt;
    GUILD_ACADEMY_REWARD_ITEM WantItem;
    unsigned __int64 nSubAcademyMoney;
    unsigned __int64 nStorageMoney;
    char nModifyItemCnt;
    EACH_MODIFY_ITEM ModifyItem[];
};

struct PROTO_NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_OPEN_ACK
{
    NETPACKETZONEHEADER zonepackheader;
    __declspec(align(1)) unsigned __int64 cen;
    char nOpenType;
    char itemcounter;
    PROTO_ITEMPACKET_TOTAL itemarray[];
};

struct __declspec(align(1)) GUILD_ACADEMY_REWARDSTORAGE_ITEM_INFO_CMD
{
    char who;
    char type;
    Name5 charid;
    unsigned __int16 item;
    char slot;
    union
    {
        unsigned __int64 lot;
        unsigned __int64 cen;
    } ___u5;
    unsigned __int64 storage_cen;
};

struct PROTO_NC_ITEMDB_ITEMBREAKSUC_ACK
{
    NETPACKETZONEHEADER packheader;
    unsigned __int16 lockindex;
};

struct PROTO_NC_ITEMDB_ITEMBREAKFAIL_ACK
{
    NETPACKETZONEHEADER packheader;
    unsigned __int16 lockindex;
    unsigned __int16 ErrorCode;
};

struct __declspec(align(1)) PROTO_NC_ITEMDB_CHESTITEM_ACK
{
    NETPACKETZONEHEADER header;
    SHINE_ITEM_REGISTNUMBER chest;
    ITEM_INVEN location;
    unsigned __int16 error;
    PROTO_ITEM_CMD item;
};

struct __declspec(align(1)) PROTO_NC_GUILD_TOURNAMENT_START_CMD
{
    char nTournamentSeed;
    unsigned __int16 nTournamentMapNo;
    unsigned __int16 nExploerTimeMin;
    unsigned __int16 nWaitPlayTimeSec;
    unsigned __int16 nPlayTimeMin;
    unsigned int nNo1;
    unsigned int nNo2;
};

struct __declspec(align(1)) PROTO_NC_GUILD_TOURNAMENT_ZONE_JOIN_NEW_REQ
{
    unsigned __int16 hWMChar;
    unsigned int nCharNo;
    unsigned int nGTNo;
    unsigned int nGuildNo;
    char nMinLevel;
    unsigned __int16 nMinMember;
    unsigned __int64 nProposalMoney;
};

struct __declspec(align(1)) PROTO_NC_CHAR_WEDDINGDATA_ACK
{
    NETPACKETZONEHEADER header;
    unsigned __int16 Error;
    struct
    {
        __int8 Main : 4;
        __int8 Sub : 4;
    } Status;
    ShineDateTime When;
    union
    {
        ShineDateTime SubWhen;
        ShineDateTime ApplicationLimit;
        ShineDateTime DelayLimit;
        ShineDateTime DivorceLimit;
        ShineDateTime NewlyLimit;
    } ___u4;
    struct 
    {
        Name5 Name;
        unsigned int RegisterNumber;
    } Partner;
    char WeddingCount;
    char RefusalCount;
};

struct PROTO_NC_SKILL_ERASE_ACK
{
    NETPACKETZONEHEADER header;
    unsigned __int16 skill;
    unsigned __int16 err;
};

struct PROTO_NC_CHAR_GET_ITEMLIST_BY_TYPE_NUM_ACK
{
    NETPACKETZONEHEADER header;
    char nInvenType;
    __declspec(align(1)) unsigned int nOwner;
    __declspec(align(1)) unsigned __int16 Error;
    PROTO_NC_CHAR_ITEM_CMD ItemCmd;
};

struct __declspec(align(1)) PROTO_NC_HOLY_PROMISE_CENTRANSFER_RNG
{
    ZONERINGLINKAGESTART start;
    unsigned int upper;
    unsigned int cen;
    Name5 lower;
};

struct PROTO_NC_HOLY_PROMISE_DB_GET_CEN_REWARD_ACK
{
    NETPACKETZONEHEADER header;
    unsigned __int16 nError;
    unsigned __int64 nMoney;
};

struct PROTO_NC_HOLY_PROMISE_DB_WITHDRAW_CEN_REWARD_ACK
{
    NETPACKETZONEHEADER header;
    unsigned __int16 nError;
    unsigned __int64 nMoney;
};

struct __declspec(align(1)) PROTO_NC_CHAR_REGNUM_VARIFICATION_ACK
{
    unsigned __int16 zonehandle;
    unsigned int charregnum;
    char iscorrect;
};

struct PROTO_NC_ITEMDB_WEAPONENDURE_CHARGE_ACK
{
    NETPACKETZONEHEADER header;
    unsigned __int16 lockindex;
    SHINE_ITEM_REGISTNUMBER WeaponKey;
    ITEM_INVEN WeaponSlot;
    __declspec(align(1)) unsigned int ChargedNumber;
    unsigned __int16 Error;
};

struct PROTO_NC_ITEMDB_SHIELDENDURE_CHARGE_ACK
{
    NETPACKETZONEHEADER header;
    unsigned __int16 lockindex;
    SHINE_ITEM_REGISTNUMBER ShieldKey;
    ITEM_INVEN ShieldSlot;
    __declspec(align(1)) unsigned int ChargedNumber;
    unsigned __int16 Error;
};

struct PROTO_NC_USER_CONNECTION_DB_CHANGE_CHAR_ID_ITEM_USE_ACK
{
    NETPACKETZONEHEADER Header;
    unsigned __int16 nError;
    unsigned __int16 lockindex;
    unsigned __int16 nUsedItemID;
};

struct __declspec(align(2)) PROTO_NC_ACT_SOMEONEMOVEWALK_CMD
{
    unsigned __int16 handle;
    SHINE_XY_TYPE from;
    SHINE_XY_TYPE to;
    unsigned __int16 speed;
    struct
    {
        unsigned __int16 direct : 1;
    } moveattr;
};

struct PROTO_NC_CHAR_GET_CHAT_BLOCK_SPAMER_CMD
{
    unsigned int BlockTime;
    unsigned int DelayTime;
};

struct __declspec(align(1)) PROTO_NC_CHAR_FREESTAT_SET_DB_ACK
{
    NETPACKETZONEHEADER header;
    char nFreeStat[5];
    unsigned __int16 nLockIndex;
    unsigned __int16 nErrorType;
};

struct PROTO_NC_CHAR_COININFO_CMD
{
    unsigned __int64 nCoin;
    unsigned __int64 nExchangedCoin;
};

struct __declspec(align(1)) PROTO_NC_ITEMDB_CAPSULEITEM_ACK
{
    NETPACKETZONEHEADER Header;
    unsigned __int16 nError;
    SHINE_ITEM_REGISTNUMBER nItemReg;
    ITEM_INVEN nLocation;
    ItemTotalInformation ContentItemInfo;
};

struct PROTO_NC_GAMBLE_SLOTMACHINE_DB_RESULT_ACK
{
    NETPACKETZONEHEADER header;
    unsigned __int16 lockindex;
    unsigned __int16 nError;
};

struct __declspec(align(2)) PROTO_NC_CHAR_CARDCOLLECT_CMD
{
    struct __declspec(align(1)) CardInform
    {
      int RegistTime;
      unsigned int SerialNumber;
      unsigned __int16 CardID;
      char StarNumber;
    };

    unsigned int chrregnum;
    unsigned __int16 number;
    PROTO_NC_CHAR_CARDCOLLECT_CMD::CardInform CardList[];
};

struct __declspec(align(2)) PROTO_NC_CHAR_CARDCOLLECT_BOOKMARK_CMD
{
    struct CardBookmarkInfo
    {
        unsigned __int16 Slot;
        unsigned __int16 CardID;
    };

    unsigned int chrregnum;
    unsigned __int16 number;
    PROTO_NC_CHAR_CARDCOLLECT_BOOKMARK_CMD::CardBookmarkInfo ViewList[];
};

struct __declspec(align(2)) PROTO_NC_CHAR_CARDCOLLECT_REWARD_CMD
{
    unsigned int chrregnum;
    unsigned __int16 number;
    unsigned __int16 RewardID[];
};

struct __declspec(align(1)) PROTO_NC_ITEMDB_ITEMINFO_ACK
{
    unsigned int clientregnum;
    unsigned __int16 clientzonehandle;
    unsigned __int16 err;
    NETCOMMAND FailProtocol;
    ItemTotalInformation ItemInfo;
};

struct PROTO_NC_COLLECT_BOOKMARK_REGIST_ACK
{
    unsigned __int16 BookMarkSlot;
    unsigned __int16 CardID;
    unsigned __int16 err;
};

struct PROTO_NC_ACT_MOVEWALK_CMD
{
    SHINE_XY_TYPE from;
    SHINE_XY_TYPE to;
};

struct PROTO_NC_ACT_STOP_REQ
{
    SHINE_XY_TYPE loc;
};

struct __declspec(align(1)) PROTO_NC_ITEMDB_CHAT_COLOR_CHANGE_ACK
{
    unsigned __int16 nError;
    unsigned __int16 nLockIndex;
    unsigned int nCharRegNum;
    SHINE_ITEM_REGISTNUMBER nItemKey;
    unsigned __int16 nItemID;
    CAHT_CHAT_COLOR_ITEM_TYPE eChatColorItemType;
    char nChangeColor;
};

struct __declspec(align(1)) PROTO_NC_CHAR_SELL_ITEM_INFO_ZONE_CMD
{
    char NumOfSellItem;
    PROTO_SELL_ITEM_INFO_SERVER SellItemList[];
};

struct CHARDATA_TO_CLIENT
{
    PROTO_NC_CHAR_BASE_CMD basedata;
    PROTO_AVATAR_SHAPE_INFO shape;
};

struct __declspec(align(1)) ZoneCharData
{
    unsigned int usrregnum;
    CHARDATA_TO_CLIENT toclient;
};

struct BriefInfoBackup
{
    CHARBRIEFINFO_NOTCAMP bib_BriefInfo;
    char bib_Backuped;
};

struct __declspec(align(4)) StreetBooth
{
    void* vfptr;
    STREETBOOTH_SIGNBOARD sb_SignBoard;
    char sb_Terminal;
    unsigned __int16 sb_BoothOwner;
};

struct __declspec(align(8)) StreetBoothSell : StreetBooth
{
    struct
    {
        char invenslot;
        ItemInventoryCell* invencell;
        unsigned __int64 unitcost;
    } sbs_BoothCell[20];
    unsigned __int16 sbs_LockIndex;
};

struct StreetBoothBuy : StreetBooth
{
    struct
    {
        unsigned __int16 item;
        unsigned __int16 quantity;
        unsigned __int64 unitcost;
    } sbb_BoothCell[20];
};

struct PROTO_NC_ACT_MOVESPEED_CMD
{
    unsigned __int16 walkspeed;
    unsigned __int16 runspeed;
};

struct PROTO_NC_ITEM_MIX_ITEM_REQ
{
    char nSubRaw;
    char nRawLeft;
    char nRawRight;
};


#pragma region NETCMDS
enum PROTOCOL
{
    NC_LOG_USER_LOGINFAIL = 0x0720,
    NC_LOG_USER_LOGIN = 0x0721,
    NC_LOG_USER_LOGOUT = 0x0722,
    NC_LOG_GAME_DATA_TYPE_0 = 0x07E8,
    NC_LOG_GAME_DATA_TYPE_1 = 0x07E9,
    NC_LOG_GAME_DATA_TYPE_2 = 0x07EA,
    NC_LOG_GAME_DATA_TYPE_3 = 0x07EB,
    NC_LOG_GAME_DATA_TYPE_4 = 0x07EC,
    NC_LOG_GAME_DATA_TYPE_5 = 0x07ED,
    NC_LOG_GAME_DATA_TYPE_6 = 0x07EE,
    NC_LOG_GAME_DATA_TYPE_7 = 0x07EF,
    NC_LOG_GAME_DATA_TYPE_8 = 0x07F0,
    NC_LOG_GAME_DATA_TYPE_9 = 0x07F1,
    NC_LOG_GAME_DATA_TYPE_A = 0x07F2,
    NC_LOG_GAME_DATA_TYPE_B = 0x07F3,
    NC_LOG_GAME_DATA_TYPE_C = 0x07F4,
    NC_LOG_GAME_DATA_TYPE_D = 0x07F5,
    NC_LOG_GAME_DATA_TYPE_E = 0x07F6,
    NC_LOG_GAME_DATA_TYPE_F = 0x07F7,
    NC_LOG_GAME_DATA_TYPE_G = 0x07F8,
    NC_LOG_GAME_DATA_TYPE_H = 0x07F9,
    NC_LOG_GAME_DATA_TYPE_I = 0x07FA,
    NC_LOG_GAME_DATA_TYPE_J = 0x07FB,
    NC_LOG_GAME_DATA_TYPE_K = 0x07FC,
    NC_LOG_GAME_DATA_TYPE_L = 0x07FD,
    NC_LOG_NULL = 0x0400,
    NC_LOG_GAME_ADD = 0x0401,
    NC_LOG_GAME_ADD_REQ = 0x0402,
    NC_LOG_GAME_ADD_ACK = 0x0403,
    NC_LOG_GAME_LOGIN = 0x040A,
    NC_LOG_GAME_LOGOUT = 0x040B,
    NC_LOG_GAME_LOGIN_SPAWN_APPS = 0x040C,
    NC_LOG_GAME_LINK = 0x040F,
    NC_LOG_GMAE_LOGOUT_ZONEINFO = 0x0410,
    NC_LOG_GAME_CREATE_AVATAR = 0x0411,
    NC_LOG_GAME_DELETE_AVATAR = 0x0412,
    NC_LOG_GAME_HIT = 0x0414,
    NC_LOG_GAME_MOVE = 0x0415,
    NC_LOG_GAME_PRISON = 0x0419,
    NC_LOG_GAME_PRISON_RELEASE = 0x041A,
    NC_LOG_GAME_LEVEL_UP = 0x041E,
    NC_LOG_GAME_LEVEL_DOWN = 0x041F,
    NC_LOG_GAME_CHANGE_CLASS = 0x0420,
    NC_LOG_GAME_PK = 0x0428,
    NC_LOG_GAME_PKED = 0x0429,
    NC_LOG_GAME_MK = 0x042A,
    NC_LOG_GAME_MKED = 0x042B,
    NC_LOG_GAME_MK_GETEXP = 0x042C,
    NC_LOG_GAME_MK_GETEXPINFIELD = 0x042D,
    NC_LOG_GAME_SKILL_LEARN = 0x0432,
    NC_LOG_GAME_SKILL_DELETE = 0x0433,
    NC_LOG_GAME_SKILL_USE = 0x0434,
    NC_LOG_GAME_STATE_SET = 0x0437,
    NC_LOG_GAME_STATE_CLEAR = 0x0438,
    NC_LOG_GAME_CHARGED_BUFF_SET = 0x0439,
    NC_LOG_GAME_CHARGED_BUFF_CLR = 0x043A,
    NC_LOG_GAME_QUEST_GET = 0x043C,
    NC_LOG_GAME_QUEST_COMPLETE = 0x043D,
    NC_LOG_GAME_QUEST_SET_INFO = 0x043E,
    NC_LOG_GAME_QUEST_ITEM_GET = 0x043F,
    NC_LOG_GAME_QUEST_DELETE = 0x0440,
    NC_LOG_GAME_KQ_ENTER = 0x0441,
    NC_LOG_GAME_KQ_LEAVE = 0x0442,
    NC_LOG_GAME_ITEM_MOB_DROP_RATE = 0x0444,
    NC_LOG_GAME_ITEM_BREAK = 0x0445,
    NC_LOG_GAME_ITEM_TAKE = 0x0446,
    NC_LOG_GAME_ITEM_DROP = 0x0447,
    NC_LOG_GAME_ITEM_BUY = 0x0448,
    NC_LOG_GAME_ITEM_SELL = 0x0449,
    NC_LOG_GAME_ITEM_TRADE = 0x044A,
    NC_LOG_GAME_ITEM_USE = 0x044B,
    NC_LOG_GAME_ITEM_INVEN_MOVE = 0x044C,
    NC_LOG_GAME_ITEM_EQUIP = 0x044D,
    NC_LOG_GAME_ITEM_UNEQUIP = 0x044E,
    NC_LOG_GAME_ITEM_CREATE = 0x044F,
    NC_LOG_GAME_ITEM_STORE_IN = 0x0450,
    NC_LOG_GAME_ITEM_STORE_OUT = 0x0451,
    NC_LOG_GAME_ITEM_UPGRADE = 0x0452,
    NC_LOG_GAME_ITEM_TITLE = 0x0454,
    NC_LOG_GAME_ITEM_MOB_DROP = 0x0455,
    NC_LOG_GAME_ITEM_MERGE = 0x0456,
    NC_LOG_GAME_ITEM_SPLIT = 0x0457,
    NC_LOG_GAME_ITEM_SOULSTONEBUY = 0x0458,
    NC_LOG_GAME_ITEM_USELOT = 0x0459,
    NC_LOG_GAME_ITEM_USEALL = 0x045A,
    NC_LOG_GAME_ITEM_BOOTH_BUY = 0x045B,
    NC_LOG_GAME_ITEM_BOOTH_SELL = 0x045C,
    NC_LOG_GAME_ITEM_PRODUCT = 0x0453,
    NC_LOG_GAME_ITEM_PRODUCT_STUFF = 0x045D,
    NC_LOG_GAME_MONEY_DEPOSIT = 0x045E,
    NC_LOG_GAME_MONEY_WITHDRAW = 0x045F,
    NC_LOG_GAME_MONEY_TRADE_INCOME = 0x0460,
    NC_LOG_GAME_MONEY_TRADE_OUTGO = 0x0461,
    NC_LOG_GAME_MONEY_CHANGE = 0x0462,
    NC_LOG_GAME_ENCHANNT = 0x0464,
    NC_LOG_GAME_DISENCHANT = 0x0465,
    NC_LOG_GAME_PARTY_CREATE = 0x046E,
    NC_LOG_GAME_PARTY_JOIN = 0x046F,
    NC_LOG_GAME_PARTY_LEAVE = 0x0470,
    NC_LOG_GAME_PARTY_CHG_MAS = 0x0471,
    NC_LOG_GAME_PARTY_DELETE = 0x0472,
    NC_LOG_GAME_PARTY_BANISH = 0x0473,
    NC_LOG_GAME_FRIEND_ADD = 0x0478,
    NC_LOG_GAME_FRIEND_DELETE = 0x0479,
    NC_LOG_GAME_MAS_PUP_ADD = 0x0482,
    NC_LOG_GAME_MAS_PUP_DELETE = 0x0483,
    NC_LOG_GAME_GUILD_CREATE = 0x048C,
    NC_LOG_GAME_GUILD_DELETE = 0x048D,
    NC_LOG_GAME_GUILD_TYPE = 0x048E,
    NC_LOG_GAME_GUILD_GRADE = 0x048F,
    NC_LOG_GAME_GUILD_WAR_DECLARE = 0x0490,
    NC_LOG_GAME_GUILD_WAR_ACCEPT = 0x0491,
    NC_LOG_GAME_GUILD_WAR_RESULT = 0x0492,
    NC_LOG_GAME_GUILD_M_JOIN = 0x04A0,
    NC_LOG_GAME_GUILD_M_LEAVE = 0x04A1,
    NC_LOG_GAME_GUILD_M_BANISH = 0x04A2,
    NC_LOG_GAME_GUILD_M_GRADE = 0x04A3,
    NC_LOG_GAME_GUILD_K_MONEY_WITHDRAW = 0x04AA,
    NC_LOG_GAME_GUILD_G_REWARD_MONEY = 0x04AB,
    NC_LOG_GAME_GUILD_4_REWARD_FAME = 0x04AC,
    NC_LOG_GAME_GUILD_G_REWARD_EXP = 0x04AD,
    NC_LOG_GAME_GUILD_4_TOURNAMENT_RESULT = 0x04AE,
    NC_LOG_GAME_GUILD_G_REWARD_TOKEN = 0x04AF,
    NC_LOG_GAME_GUILD_G_REWARD_MONEY_DIVISION = 0x04B0,
    NC_LOG_GAME_CHARGE_WITHDRAW = 0x04BE,
    NC_LOG_GAME_MINIHOUSE = 0x04C8,
    NC_LOG_GAME_MINIHOUSE_BUILDING = 0x04C9,
    NC_LOG_GAME_MINIHOUSE_VISIT = 0x04CA,
    NC_LOG_GAME_PET = 0x04FA,
    NC_LOG_GAME_EMBLEM = 0x050E,
    NC_LOG_GAME_QUEST_REWARD_EXP = 0x0518,
    NC_LOG_GAME_QUEST_REWARD_MONEY = 0x0519,
    NC_LOG_GAME_QUEST_REWARD_ITEM = 0x051A,
    NC_LOG_GAME_QUEST_REWARD_ABSTATE = 0x051B,
    NC_LOG_GAME_QUEST_REWARD_FAME = 0x051C,
    NC_LOG_GAME_QUEST_REWARD_PET = 0x051D,
    NC_LOG_GAME_QUEST_REWARD_MINIHOUSE = 0x051E,
    NC_LOG_GAME_QUEST_REWARD_TITLE = 0x051F,
    NC_LOG_GAME_ARENA_PVP = 0x052C,
    NC_LOG_GAME_ARENA_FBZ = 0x0536,
    NC_LOG_GAME_ARENA_CNG = 0x0540,
    NC_LOG_GAME_ARENA_GUILD = 0x054A,
    NC_LOG_GAME_ITEM_PUT_ON_BELONGED = 0x0554,
    NC_LOG_GAME_SEAWAR = 0x0590,
    NC_LOG_REGENLOCATESAVE_CMD = 0x05EA,
    NC_LOG_GAME_MINIGAME = 0x05F4,
    NC_LOG_GAME_ITEM_TAKE_INVEN_EXT = 0x05FE,
    NC_LOG_GAME_ITEM_DROP_INVEN_EXT = 0x05FF,
    NC_LOG_GAME_ITEM_BUY_INVEN_EXT = 0x0600,
    NC_LOG_GAME_ITEM_SELL_INVEN_EXT = 0x0601,
    NC_LOG_GAME_ITEM_USE_INVEN_EXT = 0x0602,
    NC_LOG_GAME_ITEM_INVEN_MOVE_INVEN_EXT = 0x0603,
    NC_LOG_GAME_ITEM_EQUIP_INVEN_EXT = 0x0604,
    NC_LOG_GAME_ITEM_UNEQUIP_INVEN_EXT = 0x0605,
    NC_LOG_GAME_ITEM_CREATE_INVEN_EXT = 0x0606,
    NC_LOG_GAME_ITEM_STORE_IN_INVEN_EXT = 0x0607,
    NC_LOG_GAME_ITEM_STORE_OUT_INVEN_EXT = 0x0608,
    NC_LOG_GAME_ITEM_PUT_ON_BELONGED_EXT = 0x0609,
    NC_LOG_GAME_ITEM_CW_BREAKATZERO = 0x0612,
    NC_LOG_WEDDING_PROPOSE_EXE = 0x0658,
    NC_LOG_WEDDING_PROPOSE_CANCEL = 0x0659,
    NC_LOG_WEDDING_DIVORCE_REQ = 0x065A,
    NC_LOG_WEDDING_DIVORCE_EXE = 0x065B,
    NC_LOG_WEDDING_DIVORCE_CANCEL = 0x065C,
    NC_LOG_WEDDING_HALL_RESERVE = 0x065D,
    NC_LOG_WEDDING_HALL_START = 0x065E,
    NC_LOG_WEDDING_HALL_CANCEL = 0x065F,
    NC_LOG_WEDDING_WEDDING_EXE = 0x0660,
    NC_LOG_GUILD_ACADEMY_JOIN = 0x0752,
    NC_LOG_GUILD_ACADEMY_LEAVE = 0x0753,
    NC_LOG_GUILD_ACADEMY_VANISH = 0x0754,
    NC_LOG_GUILD_ACADEMY_SET_MASTER = 0x0755,
    NC_LOG_GUILD_ACADEMY_GRADUATE = 0x0756,
    NC_LOG_GUILD_ACADEMY_GUILD_INVITE = 0x0757,
    NC_LOG_GUILD_ACADEMY_CHAT_BAN = 0x0758,
    NC_LOG_GUILD_ACADEMY_MASTER_TELEPORT = 0x0759,
    NC_LOG_GUILD_ACADEMY_SET_REWARD_MONEY = 0x075A,
    NC_LOG_GUILD_ACADEMY_SET_REWARD_ITEM = 0x075B,
    NC_LOG_GUILD_ACADEMY_CLEAR_REWARD_MONEY = 0x075C,
    NC_LOG_GUILD_ACADEMY_CLEAR_REWARD_ITEM = 0x075D,
    NC_LOG_GUILD_ACADEMY_REWARD_MONEY = 0x075E,
    NC_LOG_GUILD_ACADEMY_REWARD_ITEM = 0x075F,
    NC_LOG_GUILD_ACADEMY_REWARD_ITEM_PAY = 0x0760,
    NC_LOG_GUILD_ACADEMY_LEVEL_UP = 0x0761,
    NC_LOG_GAME_MK2_START = 0x078E,
    NC_LOG_GAME_MK2_SUCCESS = 0x078F,
    NC_LOG_GAME_MK2_FAIL = 0x0790,
    NC_LOG_GAME_MK2_DEAD = 0x0791,
    NC_LOG_GAME_MK_DROP_ITEM = 0x0798,
    NC_LOG_MOVER_UPGRADE = 0x079A,
    NC_LOG_MOVER_RAREMOVER = 0x079B,
    NC_LOG_ITEMMONEY_BUY = 0x079C,
    NC_LOG_RANDOMOPTION_CHANGE = 0x079D,
    NC_LOG_RANDOMOPTION_CHANGE_BEFORE = 0x079E,
    NC_LOG_RANDOMOPTION_CHANGE_AFTER = 0x079F,
    NC_LOG_RANDOMOPTION_USE_CONSUME_ITEM_TO_TARGET_ITEM = 0x07A0,
    NC_LOG_UES_FRIEND_POINT = 0x07A1,
    NC_LOG_CLASS_CHANGE_REQ = 0x07A2,
    NC_LOG_RANDOMOPTION_RECOVER_COUNT_LIMIT = 0x07A5,

    NC_MISC_NULL = 0x0800,
    NC_MISC_S2SCONNECTION_RDY = 0x0801,
    NC_MISC_S2SCONNECTION_REQ = 0x0802,
    NC_MISC_S2SCONNECTION_ACK = 0x0803,
    NC_MISC_HEARTBEAT_REQ = 0x0804,
    NC_MISC_HEARTBEAT_ACK = 0x0805,
    NC_MISC_SEED_REQ = 0x0806,
    NC_MISC_SEED_ACK = 0x0807,
    NC_MISC_USER_COUNT_CMD = 0x0808,
    NC_MISC_CONNECTER_REQ = 0x0809,
    NC_MISC_CONNECTER_ACK = 0x080A,
    NC_MISC_DELIVER_WM_LOGIN_ACDB_CMD = 0x080B,
    NC_MISC_DELIVER_WM_LOGIN_ALDB_CMD = 0x080C,
    NC_MISC_GAMETIME_REQ = 0x080D,
    NC_MISC_GAMETIME_ACK = 0x080E,
    NC_MISC_CLIENT_DEBUG_MSG_CMD = 0x080F,
    NC_MISC_RESTMINUTE_CMD = 0x0810,
    NC_MISC_ZONERINGLINKTEST_RNG = 0x0811,
    NC_MISC_PINGTEST_CLIENT_ZONE_DB = 0x0812,
    NC_MISC_PINGTEST_TOOL_WM_CLIENT_ZONE_DB = 0x0813,
    NC_MISC_PINGTEST_TOOL_WM_DB = 0x0814,
    NC_MISC_PINGTEST_TOOL_WM_ZONE_DB = 0x0815,
    NC_MISC_PINGTEST_TOOL_WM_ZONE = 0x0816,
    NC_MISC_HIDE_EXCEPT_ME_ON_CMD = 0x0817,
    NC_MISC_HIDE_EXCEPT_ME_OFF_CMD = 0x0818,
    NC_MISC_APEX_SERVER_DATA_CMD = 0x0819,
    NC_MISC_APEX_CLIENT_DATA_CMD = 0x081A,
    NC_MISC_WEB_KEY_REQ = 0x081B,
    NC_MISC_WEB_KEY_ACK = 0x081C,
    NC_MISC_WEB_DB_KEY_REQ = 0x081D,
    NC_MISC_WEB_DB_KEY_ACK = 0x081E,
    NC_MISC_CHAR_LOGOFF_STATISTICS = 0x081F,
    NC_MISC_EVENT_HIT3_ADD_CASH = 0x0820,
    NC_MISC_TIMEFROMWORLD_CMD = 0x0821,
    NC_MISC_START_THE_BOOM_CMD = 0x0823,
    NC_MISC_WHSHANDLEFIX_CMD = 0x0824,
    NC_MISC_WHSHANDLEREPAIR_CMD = 0x0825,
    NC_MISC_XTRAP2_SERVER_DATA_CMD = 0x0826,
    NC_MISC_XTRAP2_CLIENT_DATA_CMD = 0x0827,
    NC_MISC_XTRAP2_OPTOOL_READ_CODEMAP_REQ = 0x0828,
    NC_MISC_XTRAP2_OPTOOL_READ_CODEMAP_ACK = 0x0829,
    NC_MISC_CONNECTFROMWHERE_REQ = 0x082A,
    NC_MISC_CONNECTFROMWHERE_ACK = 0x082B,
    NC_MISC_CONNECTFROMWHERE_DB_REQ = 0x082F,
    NC_MISC_CONNECTFROMWHERE_DB_ACK = 0x0830,
    NC_MISC_EVENT_L20_DB_REQ = 0x082C,
    NC_MISC_EVENT_L20_DB_ACK = 0x082D,
    NC_MISC_EVENT_L20_CMD = 0x082E,
    NC_MISC_SERVERPARAMETER_REQ = 0x082F,
    NC_MISC_SERVERPARAMETER_ACK = 0x0830,
    NC_MISC_CS_REQ = 0x0831,
    NC_MISC_CS_ACK = 0x0832,
    NC_MISC_CS_CLOSE = 0x0833,
    NC_MISC_HACK_SCAN_STORE_CMD = 0x0834,
    NC_MISC_HACK_SCAN_STORE_DB_CMD = 0x0835,
    NC_MISC_APEX_CLIENT_CHCSTART_CMD = 0x0836,
    NC_MISC_EVENT_DONE_MUNSANG_Z2WM = 0x0837,
    NC_MISC_EVENT_DONE_MUNSANG_WM2ACC = 0x0838,
    NC_MISC_EVENT_DONE_MUNSANG_ACC2WM = 0x0839,
    NC_MISC_EVENT_DONE_MUNSANG_WM2Z = 0x083A,
    NC_MISC_EVENT_DONE_MUNSANG_Z2CLI = 0x083B,
    NC_MISC_GM_CHAT_COLOR_REQ = 0x083D,
    NC_MISC_CLIENT_LOADING_BUG_DETECT_CMD = 0x0840,
    NC_MISC_DB_CLIENT_LOADING_BUG_DETECT_CMD = 0x0841,
    NC_MISC_MISCERROR_CMD = 0x0842,
    NC_MISC_EVENT_LONG_TIME_PLAY_CMD = 0x0843,
    NC_MISC_GET_CHAT_BLOCK_SPAM_FILTER_DB_CMD = 0x0844,
    NC_MISC_GET_CHAT_BLOCK_SPAM_FILTER_CMD = 0x0845,
    NC_MISC_SET_CHAT_BLOCK_SPAM_FILTER_CMD = 0x0846,
    NC_MISC_SET_CHAT_BLOCK_SPAM_FILTER_DB_CMD = 0x0847,
    NC_MISC_CHAT_BLOCK_SPAMER_BLOCKTIME_CMD = 0x0848,
    NC_MISC_SERVER_TIME_NOTIFY_CMD = 0x0849,
    NC_MISC_SPAMMER_REPORT_REQ = 0x085F,
    NC_MISC_SPAMMER_REPORT_ACK = 0x0860,
    NC_MISC_SPAMMER_CHAT_BAN_REQ = 0x0861,
    NC_MISC_SPAMMER_CHAT_BAN_ACK = 0x0862,
    NC_MISC_SPAMMER_SET_DB_CHAT_BAN_REQ = 0x0863,
    NC_MISC_SPAMMER_SET_DB_CHAT_BAN_ACK = 0x0864,
    NC_MISC_SPAMMER_ZONE_CHAT_BAN_CMD = 0x0865,
    NC_MISC_SPAMMER_RELEASE_CHAT_BAN_REQ = 0x0866,
    NC_MISC_SPAMMER_RELEASE_CHAT_BAN_ACK = 0x0867,
    NC_MISC_SPAMMER_RELEASE_CHAT_BAN_DB_REQ = 0x0868,
    NC_MISC_SPAMMER_RELEASE_CHAT_BAN_DB_ACK = 0x0869,
    NC_MISC_EVENTNPC_STANDSTART_ZONE_CMD = 0x086A,
    NC_MISC_EVENTNPC_STANDEND_ZONE_CMD = 0x086B,
    NC_MISC_EVENTNPC_STANDSTART_CLIENT_CMD = 0x086C,
    NC_MISC_EVENTNPC_STANDEND_CLIENT_CMD = 0x086D,
    NC_MISC_ITEMSHOP_URL_REQ = 0x086E,
    NC_MISC_ITEMSHOP_URL_ACK = 0x086F,
    NC_MISC_ITEMSHOP_URL_DB_REQ = 0x0870,
    NC_MISC_ITEMSHOP_URL_DB_ACK = 0x0871,

    NC_USER_NULL = 0x0C00,
    NC_USER_XTRAP_REQ = 0x0C04,
    NC_USER_XTRAP_ACK = 0x0C05,
    NC_USER_LOGIN_REQ = 0x0C06,
    NC_USER_PASSWORD_CHECK_REQ = 0x0C07,
    NC_USER_PASSWORD_CHECK_ACK = 0x0C08,
    NC_USER_LOGINFAIL_ACK = 0x0C09,
    NC_USER_LOGIN_ACK = 0x0C0A,
    NC_USER_WORLDSELECT_REQ = 0x0C0B,
    NC_USER_WORLDSELECT_ACK = 0x0C0C,
    NC_USER_WILLLOGIN_REQ = 0x0C0D,
    NC_USER_WILLLOGIN_ACK = 0x0C0E,
    NC_USER_LOGINWORLD_REQ = 0x0C0F,
    NC_USER_LOGIN_DB = 0x0C10,
    NC_USER_LOGOUT_DB = 0x0C11,
    NC_USER_AVATARINFO_REQ = 0x0C12,
    NC_USER_AVATARINFO_ACK = 0x0C13,
    NC_USER_LOGINWORLD_ACK = 0x0C14,
    NC_USER_LOGINWORLDFAIL_ACK = 0x0C15,
    NC_USER_KICKOFFFROMWORLD_CMD = 0x0C16,
    NC_USER_CONNECTCUT_CMD = 0x0C17,
    NC_USER_NORMALLOGOUT_CMD = 0x0C18,
    NC_USER_CONNECTCUT2ZONE_CMD = 0x0C19,
    NC_USER_CONNECTCUT2WORLDMANAGER_CMD = 0x0C1A,
    NC_USER_WORLD_STATUS_REQ = 0x0C1B,
    NC_USER_WORLD_STATUS_ACK = 0x0C1C,
    NC_USER_LOGIN_NETMARBLE_REQ = 0x0C1D,
    NC_USER_LOGIN_NETMARBLE_DB_REQ = 0x0C1E,
    NC_USER_AVATAR_LIST_REQ = 0x0C1F,
    NC_USER_LOGIN_OUTSPARK_REQ = 0x0C20,
    NC_USER_REGISENUMBER_REQ = 0x0C23,
    NC_USER_REGISENUMBER_ACK = 0x0C24,
    NC_USER_TEENAGER_CMD = 0x0C25,
    NC_USER_TEENAGER_REQ = 0x0C26,
    NC_USER_TEENAGER_ACK = 0x0C27,
    NC_USER_TEENAGER_SET_CMD = 0x0C28,
    NC_USER_TEENAGER_REMAIN_MIN_CMD = 0x0C29,
    NC_USER_IS_IP_BLOCK_REQ = 0x0C2A,
    NC_USER_IS_IP_BLOCK_ACK = 0x0C2B,
    NC_USER_POSSIBLE_NEW_CONNECT_CMD = 0x0C31,
    NC_USER_USE_BEAUTY_SHOP_CMD = 0x0C32,
    NC_USER_WILL_WORLD_SELECT_REQ = 0x0C33,
    NC_USER_WILL_WORLD_SELECT_ACK = 0x0C34,
    NC_USER_CREATE_OTP_REQ = 0x0C35,
    NC_USER_CREATE_OTP_ACK = 0x0C36,
    NC_USER_LOGIN_WITH_OTP_REQ = 0x0C37,
    NC_USER_GER_LOGIN_REQ = 0x0C38,
    NC_USER_GER_PASSWORD_CHECK_REQ = 0x0C39,
    NC_USER_GER_PASSWORD_CHECK_ACK = 0x0C3A,
    NC_USER_GER_IS_IP_BLOCK_REQ = 0x0C3B,
    NC_USER_GER_IS_IP_BLOCK_ACK = 0x0C3C,
    NC_USER_TW_LOGIN_REQ = 0x0C3D,
    NC_USER_TW_PASSWORD_CHECK_REQ = 0x0C3E,
    NC_USER_TW_PASSWORD_CHECK_ACK = 0x0C3F,
    NC_USER_TW_IS_IP_BLOCK_REQ = 0x0C40,
    NC_USER_TW_IS_IP_BLOCK_ACK = 0x0C41,
    NC_USER_JP_LOGIN_REQ = 0x0C4A,
    NC_USER_JP_PASSWORD_CHECK_REQ = 0x0C4B,
    NC_USER_JP_PASSWORD_CHECK_ACK = 0x0C4C,
    NC_USER_JP_IS_IP_BLOCK_REQ = 0x0C4D,
    NC_USER_JP_IS_IP_BLOCK_ACK = 0x0C4E,
    NC_USER_CH_LOGIN_REQ = 0x0C52,
    NC_USER_CH_PASSWORD_CHECK_REQ = 0x0C53,
    NC_USER_CH_PASSWORD_CHECK_ACK = 0x0C54,
    NC_USER_CH_IS_IP_BLOCK_REQ = 0x0C55,
    NC_USER_CH_IS_IP_BLOCK_ACK = 0x0C56,
    NC_USER_US_LOGIN_REQ = 0x0C5A,
    NC_USER_US_PASSWORD_CHECK_REQ = 0x0C5B,
    NC_USER_US_PASSWORD_CHECK_ACK = 0x0C5C,
    NC_USER_US_IS_IP_BLOCK_REQ = 0x0C5D,
    NC_USER_US_IS_IP_BLOCK_ACK = 0x0C5E,
    NC_USER_TUTORIAL_CAN_SKIP_CMD = 0x0C5F,
    NC_USER_RETURN_CHECK_REQ = 0x0C60,
    NC_USER_RETURN_CHECK_ACK = 0x0C61,
    NC_USER_LOGOUT_LAST_DAY_REQ = 0x0C62,
    NC_USER_LOGOUT_LAST_DAY_ACK = 0x0C63,
    NC_USER_SET_RETURN_CMD = 0x0C64,
    NC_USER_CLIENT_VERSION_CHECK_REQ = 0x0C65,
    NC_USER_CLIENT_WRONGVERSION_CHECK_ACK = 0x0C66,
    NC_USER_CLIENT_RIGHTVERSION_CHECK_ACK = 0x0C67,

    NC_CHAR_NULL = 0x1000,
    NC_CHAR_LOGIN_REQ = 0x1001,
    NC_CHAR_LOGINFAIL_ACK = 0x1002,
    NC_CHAR_LOGIN_ACK = 0x1003,
    NC_CHAR_CHARDATA_REQ = 0x1004,
    NC_CHAR_CHARDATA_ACK = 0x1005,
    NC_CHAR_CHARDATAFAIL_ACK = 0x1006,
    NC_CHAR_BASE_CMD = 0x1007,
    NC_CHAR_SHAPE_CMD = 0x1008,
    NC_CHAR_QUEST_DOING_CMD = 0x100A,
    NC_CHAR_QUEST_DONE_CMD = 0x100B,
    NC_CHAR_ABSTATE_CMD = 0x100C,
    NC_CHAR_SKILL_CMD = 0x100D,
    NC_CHAR_SKILL_PASSIVE_CMD = 0x100E,
    NC_CHAR_HOUSE_CMD = 0x100F,
    NC_CHAR_FRIEND_CMD = 0x1010,
    NC_CHAR_MASPUP_CMD = 0x1011,
    NC_CHAR_GUILD_CMD = 0x1012,
    NC_CHAR_EMBLEM_CMD = 0x1013,
    NC_CHAR_PET_CMD = 0x1014,
    NC_CHAR_ARENA_CMD = 0x1015,
    NC_CHAR_SEAWAR_CMD = 0x1016,
    NC_CHAR_ITEM_CMD = 0x1017,
    NC_CHAR_CHESTINFO_CMD = 0x1018,
    NC_CHAR_CHARTITLE_CMD = 0x1019,
    NC_CHAR_KQMAP_CMD = 0x101A,
    NC_CHAR_CHARGEDBUFF_CMD = 0x101B,
    NC_CHAR_ZONE_CHARDATA_REQ = 0x101C,
    NC_CHAR_ZONE_CHARDATA_ACK = 0x101D,
    NC_CHAR_ZONE_CHARDATAFAIL_ACK = 0x101E,
    NC_CHAR_ZONE_BASE_CMD = 0x101F,
    NC_CHAR_ZONE_SHAPE_CMD = 0x1020,
    NC_CHAR_ZONE_QUEST_DOING_CMD = 0x1021,
    NC_CHAR_ZONE_QUEST_DONE_CMD = 0x1022,
    NC_CHAR_ZONE_ABSTATE_CMD = 0x1023,
    NC_CHAR_ZONE_SKILL_CMD = 0x1024,
    NC_CHAR_ZONE_PASSIVE_CMD = 0x1025,
    NC_CHAR_ZONE_HOUSE_CMD = 0x1026,
    NC_CHAR_ZONE_FRIEND_CMD = 0x1027,
    NC_CHAR_ZONE_MASPUP_CMD = 0x1028,
    NC_CHAR_ZONE_GUILD_CMD = 0x1029,
    NC_CHAR_ZONE_EMBLEM_CMD = 0x102A,
    NC_CHAR_ZONE_PET_CMD = 0x102B,
    NC_CHAR_ZONE_ARENA_CMD = 0x102C,
    NC_CHAR_ZONE_SEAWAR_CMD = 0x102D,
    NC_CHAR_ZONE_ITEM_CMD = 0x102E,
    NC_CHAR_ZONE_CHESTINFO_CMD = 0x102F,
    NC_CHAR_ZONE_GAME_CMD = 0x1030,
    NC_CHAR_ZONE_CHARTITLE_CMD = 0x1031,
    NC_CHAR_ZONE_CHARGEDBUFF_CMD = 0x1032,
    NC_CHAR_CENCHANGE_CMD = 0x1033,
    NC_CHAR_BASEPARAMCHANGE_CMD = 0x1034,
    NC_CHAR_CHANGEPARAMCHANGE_CMD = 0x1035,
    NC_CHAR_LOGIN_DB = 0x1036,
    NC_CHAR_LOGOUT_DB = 0x1037,
    NC_CHAR_CLIENT_BASE_CMD = 0x1038,
    NC_CHAR_CLIENT_SHAPE_CMD = 0x1039,
    NC_CHAR_CLIENT_QUEST_DOING_CMD = 0x103A,
    NC_CHAR_CLIENT_QUEST_DONE_CMD = 0x103B,
    NC_CHAR_CLIENT_ABSTATE_CMD = 0x103C,
    NC_CHAR_CLIENT_SKILL_CMD = 0x103D,
    NC_CHAR_CLIENT_PASSIVE_CMD = 0x103E,
    NC_CHAR_CLIENT_HOUSE_CMD = 0x103F,
    NC_CHAR_CLIENT_FRIEND_CMD = 0x1040,
    NC_CHAR_CLIENT_MASPUP_CMD = 0x1041,
    NC_CHAR_CLIENT_GUILD_CMD = 0x1042,
    NC_CHAR_CLIENT_EMBLEM_CMD = 0x1043,
    NC_CHAR_CLIENT_PET_CMD = 0x1044,
    NC_CHAR_CLIENT_ARENA_CMD = 0x1045,
    NC_CHAR_CLIENT_SEAWAR_CMD = 0x1046,
    NC_CHAR_CLIENT_ITEM_CMD = 0x1047,
    NC_CHAR_CLIENT_GAME_CMD = 0x1048,
    NC_CHAR_CLIENT_CHARTITLE_CMD = 0x1049,
    NC_CHAR_CLIENT_CHARGEDBUFF_CMD = 0x104A,
    NC_CHAR_REGISTNUMBER_REQ = 0x104B,
    NC_CHAR_REGISTNUMBER_ACK = 0x104C,
    NC_CHAR_DEADMENU_CMD = 0x104D,
    NC_CHAR_REVIVE_REQ = 0x104E,
    NC_CHAR_REVIVESAME_CMD = 0x104F,
    NC_CHAR_REVIVEOTHER_CMD = 0x1050,
    NC_CHAR_PROMOTE_REQ = 0x1055,
    NC_CHAR_CLASSCHANGE_REQ = 0x1056,
    NC_CHAR_CLASSCHANGE_ACK = 0x1057,
    NC_CHAR_CLASSCHANGE_CMD = 0x1058,
    NC_CHAR_PROMOTE_ACK = 0x1059,
    NC_CHAR_SOMEONEPROMOTE_CMD = 0x105A,
    NC_CHAR_STAT_REMAINPOINT_CMD = 0x105B,
    NC_CHAR_STAT_INCPOINT_REQ = 0x105C,
    NC_CHAR_STAT_INCPOINT_DB_REQ = 0x105D,
    NC_CHAR_STAT_INCPOINTSUC_DB_ACK = 0x105E,
    NC_CHAR_STAT_INCPOINTSUC_ACK = 0x105F,
    NC_CHAR_STAT_INCPOINTFAIL_DB_ACK = 0x1060,
    NC_CHAR_STAT_INCPOINTFAIL_ACK = 0x1061,
    NC_CHAR_STAT_DECPOINT_REQ = 0x1062,
    NC_CHAR_STAT_DECPOINT_DB_REQ = 0x1063,
    NC_CHAR_STAT_DECPOINTSUC_DB_ACK = 0x1064,
    NC_CHAR_STAT_DECPOINTSUC_ACK = 0x1065,
    NC_CHAR_STAT_DECPOINTFAIL_DB_ACK = 0x1066,
    NC_CHAR_STAT_DECPOINTFAIL_ACK = 0x1067,
    NC_CHAR_PLAYERSEARCH_RNG = 0x1068,
    NC_CHAR_PLAYERFOUND_RNG = 0x1069,
    NC_CHAR_PLAYERSUMMON_RNG = 0x106A,
    NC_CHAR_KICKPLAYEROUT_RNG = 0x106B,
    NC_CHAR_PLAYERBANNED_RNG = 0x106C,
    NC_CHAR_SOMEONEGUILDCHANGE_CMD = 0x106E,
    NC_CHAR_FAMECHANGE_CMD = 0x106F,
    NC_CHAR_FAMESAVE_CMD = 0x1070,
    NC_CHAR_LOGOUTREADY_CMD = 0x1071,
    NC_CHAR_LOGOUTCANCEL_CMD = 0x1072,
    NC_CHAR_EXP_CHANGED_CMD = 0x1073,
    NC_CHAR_LEVEL_CHANGED_CMD = 0x1074,
    NC_CHAR_DATATRANSMISSION_RNG = 0x1075,
    NC_CHAR_GET_ITEMLIST_BY_TYPE_REQ = 0x1076,
    NC_CHAR_GET_ITEMLIST_BY_TYPE_ACK = 0x1077,
    NC_CHAR_SET_STYLE_REQ = 0x1078,
    NC_CHAR_SET_STYLE_ACK = 0x1079,
    NC_CHAR_SET_STYLE_DB_REQ = 0x107A,
    NC_CHAR_SET_STYLE_DB_ACK = 0x107B,
    NC_CHAR_SET_STYLE_GET_INFO_REQ = 0x107C,
    NC_CHAR_SET_STYLE_GET_INFO_ACK = 0x107D,
    NC_CHAR_SET_STYLE_GET_INFO_DB_REQ = 0x107E,
    NC_CHAR_SET_STYLE_GET_INFO_DB_ACK = 0x107F,
    NC_CHAR_WEDDINGDATA_REQ = 0x1080,
    NC_CHAR_WEDDINGDATA_ACK = 0x1081,
    NC_CHAR_WEDDINGDATA_CMD = 0x1082,
    NC_CHAR_WEDDING_PROPOSE_REQ = 0x1083,
    NC_CHAR_WEDDING_PROPOSE_ACK = 0x1084,
    NC_CHAR_WEDDING_PROPOSE_CANCEL_REQ = 0x1085,
    NC_CHAR_WEDDING_PROPOSE_CANCEL_ACK = 0x1086,
    NC_CHAR_WEDDING_ESCAPE_DIVORCE_REQ = 0x1087,
    NC_CHAR_WEDDING_ESCAPE_DIVORCE_ACK = 0x1088,
    NC_CHAR_WEDDING_DIVORCE_BY_AGREE_REQ = 0x1089,
    NC_CHAR_WEDDING_DIVORCE_BY_AGREE_ACK = 0x108A,
    NC_CHAR_WEDDING_DIVORCE_BY_FORCE_REQ = 0x108B,
    NC_CHAR_WEDDING_DIVORCE_BY_FORCE_ACK = 0x108C,
    NC_CHAR_WEDDING_DIVORCE_DO_REQ = 0x108D,
    NC_CHAR_WEDDING_DIVORCE_DO_ACK = 0x108E,
    NC_CHAR_WEDDING_DIVORCE_CANCEL_REQ = 0x108F,
    NC_CHAR_WEDDING_DIVORCE_CANCEL_ACK = 0x1090,
    NC_CHAR_WEDDING_DO_REQ = 0x1091,
    NC_CHAR_WEDDING_DO_ACK = 0x1092,
    NC_CHAR_WEDDING_PARTNER_INFO_REQ = 0x1093,
    NC_CHAR_WEDDING_PARTNER_INFO_ACK = 0x1094,
    NC_CHAR_WEDDING_PARTNER_INFO_RNG = 0x1095,
    NC_CHAR_SOMEONEGUILDACADEMYCHANGE_CMD = 0x1096,
    NC_CHAR_GUILD_ACADEMY_CMD = 0x1097,
    NC_CHAR_GUILD_ACADEMY_ZONE_CMD = 0x1098,
    NC_CHAR_GET_ITEMLIST_BY_TYPE_NUM_REQ = 0x1099,
    NC_CHAR_GET_ITEMLIST_BY_TYPE_NUM_ACK = 0x109A,
    NC_CHAR_WEDDING_PARTNER_SUMMON_RNG = 0x10AA,
    NC_CHAR_WEDDING_REFRESH_INFO_RNG = 0x10AB,
    NC_CHAR_PLAYERSEARCH_BY_NORMAL_USER_RNG = 0x10AD,
    NC_CHAR_PLAYERFOUND_BY_NORMAL_USER_RNG = 0x10AE,
    NC_CHAR_POLYMORPH_CMD = 0x10AF,
    NC_CHAR_DEPOLYMORPH_CMD = 0x10B0,
    NC_CHAR_EMPTY_INSTANCE_DUNGEON_RNG = 0x10B1,
    NC_CHAR_WEDDING_CANCEL_WEDDING = 0x10B2,
    NC_CHAR_REGNUM_VARIFICATION_REQ = 0x10B3,
    NC_CHAR_REGNUM_VARIFICATION_ACK = 0x10B4,
    NC_CHAR_ZONE_LINK_FROM_CMD = 0x10B8,
    NC_CHAR_SAVE_LINK_REQ = 0x10B9,
    NC_CHAR_CLIENT_AUTO_PICK_REQ = 0x10BC,
    NC_CHAR_CLIENT_AUTO_PICK_ACK = 0x10BD,
    NC_CHAR_CLIENT_AUTO_PICK_CMD = 0x10BE,
    NC_CHAR_ZONE_AUTO_PICK_CMD = 0x10C1,
    NC_CHAR_ADMIN_LEVEL_INFORM_CMD = 0x10C6,
    NC_CHAR_GET_CHAT_BLOCK_SPAMER_DB_CMD = 0x10CA,
    NC_CHAR_GET_CHAT_BLOCK_SPAMER_CMD = 0x10CB,
    NC_CHAR_QUEST_READ_CMD = 0x10CC,
    NC_CHAR_ZONE_QUEST_READ_CMD = 0x10CD,
    NC_CHAR_CLIENT_QUEST_READ_CMD = 0x10CE,
    NC_CHAR_ITEMACTIONCOOLTIME_CMD = 0x10CF,
    NC_CHAR_ITEMACTIONCOOLTIME_ZONE_CMD = 0x10D0,
    NC_CHAR_FREESTAT_SET_DB_REQ = 0x10D1,
    NC_CHAR_FREESTAT_SET_DB_ACK = 0x10D2,
    NC_CHAR_SINGLE_OPTION_CMD = 0x10D2,
    NC_CHAR_ZONE_SINGLE_OPTION_CMD = 0x10D3,
    NC_CHAR_MYSTERYVAULT_UI_STATE_CMD = 0x10D4,
    NC_CHAR_QUEST_REPEAT_CMD = 0x10D5,
    NC_CHAR_ZONE_QUEST_REPEAT_CMD = 0x10D6,
    NC_CHAR_CLIENT_QUEST_REPEAT_CMD = 0x10D7,
    NC_CHAR_NEWBIE_GUIDE_VIEW_LIST_CMD = 0x10D8,
    NC_CHAR_CLIENT_NEWBIE_GUIDE_VIEW_LIST_CMD = 0x10D9,
    NC_CHAR_NEWBIE_GUIDE_VIEW_SET_CMD = 0x10DA,
    NC_CHAR_DB_NEWBIE_GUIDE_VIEW_SET_CMD = 0x10DB,
    NC_CHAR_COININFO_CMD = 0x10DC,
    NC_CHAR_ZONE_COININFO_CMD = 0x10DD,
    NC_CHAR_CLIENT_COININFO_CMD = 0x10DE,
    NC_CHAR_CHANGEBYCONDITION_PARAM_CMD = 0x10DF,
    NC_CHAR_CARDCOLLECT_CMD = 0x10E2,
    NC_CHAR_ZONE_CARDCOLLECT_CMD = 0x10E3,
    NC_CHAR_CLIENT_CARDCOLLECT_CMD = 0x10E4,
    NC_CHAR_CARDCOLLECT_BOOKMARK_CMD = 0x10E5,
    NC_CHAR_ZONE_CARDCOLLECT_BOOKMARK_CMD = 0x10E6,
    NC_CHAR_CLIENT_CARDCOLLECT_BOOKMARK_CMD = 0x10E7,
    NC_CHAR_CARDCOLLECT_REWARD_CMD = 0x10E8,
    NC_CHAR_ZONE_CARDCOLLECT_REWARD_CMD = 0x10E9,
    NC_CHAR_CLIENT_CARDCOLLECT_REWARD_CMD = 0x10EA,
    NC_CHAR_EVENT_ATTENDANCE_LIST_DB_REQ = 0x10EB,
    NC_CHAR_EVENT_ATTENDANCE_LIST_DB_ACK = 0x10EC,
    NC_CHAR_EVENT_ATTENDANCE_LIST_CLIENT_CMD = 0x10ED,
    NC_CHAR_EVENT_ATTENDANCE_CHECK_DB_REQ = 0x10EE,
    NC_CHAR_EVENT_ATTENDANCE_CHECK_DB_ACK = 0x10EF,
    NC_CHAR_EVENT_ATTENDANCE_CHECK_CMD = 0x10F0,
    NC_CHAR_EVENT_ATTENDANCE_REWARD_REQ = 0x10F1,
    NC_CHAR_EVENT_ATTENDANCE_REWARD_ACK = 0x10F2,
    NC_CHAR_EVENT_ATTENDANCE_REWARD_DB_REQ = 0x10F3,
    NC_CHAR_EVENT_ATTENDANCE_REWARD_DB_ACK = 0x10F4,
    NC_CHAR_EVENT_ATTENDANCE_CHANGE_DAY_CMD = 0x10F5,
    NC_CHER_EVENT_ATTENDANCE_CHANGE_START_CMD = 0x10F6,
    NC_CHAR_REBIRTH_CMD = 0x1102,
    NC_CHAR_REBIRTH_REJECT_CMD = 0x1103,
    NC_CHAR_TUTORIAL_POPUP_REQ = 0x1110,
    NC_CHAR_TUTORIAL_POPUP_ACK = 0x1111,
    NC_CHAR_TUTORIAL_MAKE_ITEM_REQ = 0x1112,
    NC_CHAR_TUTORIAL_MAKE_ITEM_ACK = 0x1113,
    NC_CHAR_TUTORIAL_INFO_WORLD_CMD = 0x1114,
    NC_CHAR_TUTORIAL_INFO_ZONE_CMD = 0x1115,
    NC_CHAR_TUTORIAL_STEP_REQ = 0x1116,
    NC_CHAR_TUTORIAL_STEP_ACK = 0x1117,
    NC_CHAR_TUTORIAL_STEP_SAVE_REQ = 0x1118,
    NC_CHAR_TUTORIAL_STEP_SAVE_ACK = 0x1119,
    NC_CHAR_TUTORIAL_FREESTAT_INIT_REQ = 0x111A,
    NC_CHAR_TUTORIAL_FREESTAT_INIT_ACK = 0x111B,
    NC_CHAR_TUTORIAL_STEP_SAVE_CMD = 0x111C,
    NC_CHAR_TUTORIAL_DOING_CMD = 0x111D,
    NC_CHAR_CHAT_COLOR_CMD = 0x111E,
    NC_CHAR_ZONE_CHAT_COLOR_CMD = 0x111F,
    NC_CHAR_SUPPORT_REWARD_CMD = 0x1120,
    NC_CHAR_USEITEM_MINIMON_INFO_CMD = 0x1121,
    NC_CHAR_USEITEM_MINIMON_INFO_ZONE_CMD = 0x1122,
    NC_CHAR_USEITEM_MINIMON_INFO_CLIENT_CMD = 0x1123,
    NC_CHAR_USEITEM_MINIMON_NORMAL_ITEM_ON_REQ = 0x1124,
    NC_CHAR_USEITEM_MINIMON_NORMAL_ITEM_ON_ACK = 0x1125,
    NC_CHAR_USEITEM_MINIMON_NORMAL_ITEM_OFF_REQ = 0x1126,
    NC_CHAR_USEITEM_MINIMON_NORMAL_ITEM_OFF_ACK = 0x1127,
    NC_CHAR_USEITEM_MINIMON_CHARGED_ITEM_ON_REQ = 0x1128,
    NC_CHAR_USEITEM_MINIMON_CHARGED_ITEM_ON_ACK = 0x1129,
    NC_CHAR_USEITEM_MINIMON_CHARGED_ITEM_OFF_REQ = 0x112A,
    NC_CHAR_USEITEM_MINIMON_CHARGED_ITEM_OFF_ACK = 0x112B,
    NC_CHAR_USEITEM_MINIMON_USE_BROAD_CMD = 0x112C,
    NC_CHAR_USEITEM_MINIMON_NOTICE_CMD = 0x112D,
    NC_CHAR_CHARGEDBUFF_ERASE_REQ = 0x112E,
    NC_CHAR_CHARGEDBUFF_ERASE_ACK = 0x112F,
    NC_CHAR_SELL_ITEM_INFO_ZONE_CMD = 0x1130,
    NC_GAMIGO_NEW_TUTORIAL_STORE_STEP_REQ = 0x1142,
    NC_CHAR_ANI_FILE_CHECK_CMD = 0x1143,

    NC_AVATAR_NULL = 0x1400,
    NC_AVATAR_CREATE_REQ = 0x1401,
    NC_AVATAR_CREATEDATA_REQ = 0x1402,
    NC_AVATAR_CREATEDATAFAIL_ACK = 0x1403,
    NC_AVATAR_CREATEFAIL_ACK = 0x1404,
    NC_AVATAR_CREATEDATASUC_ACK = 0x1405,
    NC_AVATAR_CREATESUCC_ACK = 0x1406,
    NC_AVATAR_ERASE_REQ = 0x1407,
    NC_AVATAR_ERASEDATA_REQ = 0x1408,
    NC_AVATAR_ERASEDATAFAIL_ACK = 0x1409,
    NC_AVATAR_ERASEFAIL_ACK = 0x140A,
    NC_AVATAR_ERASEDATASUC_ACK = 0x140B,
    NC_AVATAR_ERASESUCC_ACK = 0x140C,
    NC_USP_USER_CHARACTER_INSERT = 0x140D,
    NC_USP_USER_CHARACTER_DELETE = 0x140E,
    NC_AVATAR_RENAME_REQ = 0x140F,
    NC_AVATAR_RENAME_ACK = 0x1410,
    NC_AVATAR_RENAME_DB_REQ = 0x1411,
    NC_AVATAR_RENAME_DB_ACK = 0x1412,
    NC_AVATAR_GUILD_DATA_REQ = 0x1413,
    NC_AVATAR_GUILD_DATA_ACK = 0x1414,
    NC_AVATAR_GUILD_MEMBER_DATA_REQ = 0x1415,
    NC_AVATAR_GUILD_MEMBER_DATA_ACK = 0x1416,

    NC_MAP_NULL = 0x1800,
    NC_MAP_LOGIN_REQ = 0x1801,
    NC_MAP_LOGIN_ACK = 0x1802,
    NC_MAP_LOGINCOMPLETE_CMD = 0x1803,
    NC_MAP_LOGINFAIL_ACK = 0x1804,
    NC_MAP_LOGOUT_CMD = 0x1805,
    NC_MAP_LINK_CMD = 0x1806,
    NC_MAP_LINKCANCEL_ACK = 0x1807,
    NC_MAP_LINKALLOW_ACK = 0x1808,
    NC_MAP_LINKSAME_CMD = 0x1809,
    NC_MAP_LINKOTHER_CMD = 0x180A,
    NC_MAP_LINKSTART_CMD = 0x180B,
    NC_MAP_LINKEND_CMD = 0x180C,
    NC_MAP_LINKRESERVE_REQ = 0x180D,
    NC_MAP_LINKRESERVE_ACK = 0x180E,
    NC_MAP_REGIST_CMD = 0x180F,
    NC_MAP_EXPBONUS_RNG = 0x1810,
    NC_MAP_ITEMBONUS_RNG = 0x1811,
    NC_MAP_FREEPKZONE_ON_CMD = 0x1812,
    NC_MAP_FREEPKZONE_OFF_CMD = 0x1813,
    NC_MAP_WING_SAVE_REQ = 0x1814,
    NC_MAP_WING_SAVE_ACK = 0x1815,
    NC_MAP_WING_FLY_REQ = 0x1816,
    NC_MAP_WING_FLY_ACK = 0x1817,
    NC_MAP_PARTYBATTLEZONE_ON_CMD = 0x1818,
    NC_MAP_PARTYBATTLEZONE_OFF_CMD = 0x1819,
    NC_MAP_TOWNPORTAL_REQ = 0x181A,
    NC_MAP_TOWNPORTAL_ACK = 0x181B,
    NC_MAP_TONORMALCOORD_CMD = 0x181C,
    NC_MAP_LINK_FAIL_CMD = 0x181D,
    NC_MAP_MULTY_LINK_CMD = 0x181F,
    NC_MAP_MULTY_LINK_SELECT_REQ = 0x181F,
    NC_MAP_MULTY_LINK_SELECT_ACK = 0x1820,
    NC_MAP_FIELD_ATTRIBUTE_CMD = 0x1827,
    NC_MAP_KQTEAMBATTLEZONE_ON_CMD = 0x1828,
    NC_MAP_KQTEAMBATTLEZONE_OFF_CMD = 0x1829,
    NC_MAP_LINKEND_CLIENT_CMD = 0x182A,
    NC_MAP_CAN_USE_REVIVEITEM_CMD = 0x182B,
    NC_MAP_INDUN_LEVEL_VIEW_CMD = 0x182C,

    NC_BRIEFINFO_NULL = 0x1C00,
    NC_BRIEFINFO_INFORM_CMD = 0x1C01,
    NC_BRIEFINFO_CHANGEDECORATE_CMD = 0x1C02,
    NC_BRIEFINFO_CHANGEUPGRADE_CMD = 0x1C03,
    NC_BRIEFINFO_UNEQUIP_CMD = 0x1C04,
    NC_BRIEFINFO_CHANGEWEAPON_CMD = 0x1C05,
    NC_BRIEFINFO_LOGINCHARACTER_CMD = 0x1C06,
    NC_BRIEFINFO_CHARACTER_CMD = 0x1C07,
    NC_BRIEFINFO_REGENMOB_CMD = 0x1C08,
    NC_BRIEFINFO_MOB_CMD = 0x1C09,
    NC_BRIEFINFO_DROPEDITEM_CMD = 0x1C0A,
    NC_BRIEFINFO_ITEMONFIELD_CMD = 0x1C0B,
    NC_BRIEFINFO_MAGICFIELDSPREAD_CMD = 0x1C0C,
    NC_BRIEFINFO_MAGICFIELDINFO_CMD = 0x1C0D,
    NC_BRIEFINFO_BRIEFINFODELETE_CMD = 0x1C0E,
    NC_BRIEFINFO_BUILDDOOR_CMD = 0x1C0F,
    NC_BRIEFINFO_DOOR_CMD = 0x1C10,
    NC_BRIEFINFO_EFFECTBLAST_CMD = 0x1C11,
    NC_BRIEFINFO_EFFECT_CMD = 0x1C12,
    NC_BRIEFINFO_MINIHOUSEBUILD_CMD = 0x1C13,
    NC_BRIEFINFO_MINIHOUSE_CMD = 0x1C14,
    NC_BRIEFINFO_PLAYER_LIST_INFO_APPEAR_CMD = 0x1C16,
    NC_BRIEFINFO_ABSTATE_CHANGE_CMD = 0x1C18,
    NC_BRIEFINFO_ABSTATE_CHANGE_LIST_CMD = 0x1C19,
    NC_BRIEFINFO_REGENMOVER_CMD = 0x1C1A,
    NC_BRIEFINFO_MOVER_CMD = 0x1C1B,
    NC_BRIEFINFO_REGENPET_CMD = 0x1C1C,
    NC_BRIEFINFO_PET_CMD = 0x1C1D,

    NC_ACT_NULL = 0x2000,
    NC_ACT_CHAT_REQ = 0x2001,
    NC_ACT_SOMEONECHAT_CMD = 0x2002,
    NC_ACT_WALK_REQ = 0x2003,
    NC_ACT_SOMEONEWALK_CMD = 0x2004,
    NC_ACT_RUN_REQ = 0x2005,
    NC_ACT_SOMEONERUN_CMD = 0x2006,
    NC_ACT_MOVEFAIL_ACK = 0x2007,
    NC_ACT_CHANGEMODE_REQ = 0x2008,
    NC_ACT_SOMEONECHANGEMODE_CMD = 0x2009,
    NC_ACT_NPCCLICK_CMD = 0x200A,
    NC_ACT_ENDOFTRADE_CMD = 0x200B,
    NC_ACT_WHISPER_REQ = 0x200C,
    NC_ACT_SOMEONEWHISPER_CMD = 0x200D,
    NC_ACT_WHISPERFAIL_ACK = 0x200E,
    NC_ACT_WHISPERSUCCESS_ACK = 0x200F,
    NC_ACT_NOTICE_REQ = 0x2010,
    NC_ACT_NOTICE_CMD = 0x2011,
    NC_ACT_STOP_REQ = 0x2012,
    NC_ACT_SOMEONESTOP_CMD = 0x2013,
    NC_ACT_PARTYCHAT_REQ = 0x2014,
    NC_ACT_PARTYCHAT_CMD = 0x2015,
    NC_ACT_PARTYCHAT_ACK = 0x2016,
    NC_ACT_MOVEWALK_CMD = 0x2017,
    NC_ACT_SOMEONEMOVEWALK_CMD = 0x2018,
    NC_ACT_MOVERUN_CMD = 0x2019,
    NC_ACT_SOMEONEMOVERUN_CMD = 0x201A,
    NC_ACT_MOVEFAIL_CMD = 0x201B,
    NC_ACT_NPCMENUOPEN_REQ = 0x201C,
    NC_ACT_NPCMENUOPEN_ACK = 0x201D,
    NC_ACT_SHOUT_CMD = 0x201E,
    NC_ACT_SOMEONESHOUT_CMD = 0x201F,
    NC_ACT_EMOTICON_CMD = 0x2020,
    NC_ACT_SOMEONEEMOTICON_CMD = 0x2021,
    NC_ACT_EMOTICONSTOP_CMD = 0x2022,
    NC_ACT_SOMEONEEMOTICONSTOP_CMD = 0x2023,
    NC_ACT_JUMP_CMD = 0x2024,
    NC_ACT_SOMEEONEJUMP_CMD = 0x2025,
    NC_ACT_SOMEONESPEEDCHANGE_CMD = 0x2026,
    NC_ACT_PITCHTENT_REQ = 0x2027,
    NC_ACT_PITCHTENT_ACK = 0x2028,
    NC_ACT_SOMEONEPITCHTENT_CMD = 0x2029,
    NC_ACT_FOLDTENT_REQ = 0x202A,
    NC_ACT_FOLDTENT_ACK = 0x202B,
    NC_ACT_SOMEONEFOLDTENT_CMD = 0x202C,
    NC_ACT_GATHERSTART_REQ = 0x202D,
    NC_ACT_GATHERSTART_ACK = 8238,
    NC_ACT_SOMEONEGATHERSTART_CMD = 0x202F,
    NC_ACT_GATHERCANCEL_CMD = 0x2030,
    NC_ACT_SOMEONEGATHERCANCEL_CMD = 0x2031,
    NC_ACT_GATHERCOMPLETE_REQ = 0x2032,
    NC_ACT_GATHERCOMPLETE_ACK = 8243,
    NC_ACT_SOMEONEGATHERCOMPLETE_CMD = 0x2034,
    NC_ACT_PRODUCE_CAST_REQ = 0x2035,
    NC_ACT_PRODUCE_CAST_FAIL_ACK = 0x2036,
    NC_ACT_PRODUCE_CAST_SUC_ACK = 0x2037,
    NC_ACT_SOMEONEPRODUCE_CAST_CMD = 0x2038,
    NC_ACT_PRODUCE_CASTABORT_CMD = 0x2039,
    NC_ACT_SOMEONEPRODUCE_CASTCUT_CMD = 0x203A,
    NC_ACT_PRODUCE_MAKE_CMD = 0x203B,
    NC_ACT_SOMEONEPRODUCE_MAKE_CMD = 0x203C,
    NC_ACT_REINFORCE_FOLDTENT_CMD = 0x203D,
    NC_ACT_MOVESPEED_CMD = 0x203E,
    NC_ACT_RIDE_ON_CMD = 0x203F,
    NC_ACT_SOMEONERIDE_ON_CMD = 0x2040,
    NC_ACT_RIDE_FAIL_CMD = 0x2041,
    NC_ACT_RIDE_OFF_CMD = 0x2042,
    NC_ACT_SOMEONERIDE_OFF_CMD = 0x2043,
    NC_ACT_RIDE_FEEDING_REQ = 0x2044,
    NC_ACT_RIDE_FEEDING_ACK = 0x2045,
    NC_ACT_RIDE_HUNGRY_CMD = 0x2046,
    NC_ACT_CREATECASTBAR = 0x2047,
    NC_ACT_CANCELCASTBAR = 0x2048,
    NC_ACT_REINFORCE_RUN_CMD = 0x2049,
    NC_ACT_REINFORCE_STOP_CMD = 0x204A,
    NC_ACT_ROAR_REQ = 0x204B,
    NC_ACT_ROAR_ACK = 0x204C,
    NC_ACT_REINFORCE_WALK_CMD = 0x204D,
    NC_ACT_WEDDING_PROPOSE_WORD_REQ = 0x204E,
    NC_ACT_WEDDING_PROPOSEREQ_REQ = 0x204F,
    NC_ACT_WEDDING_PROPOSEACK_REQ = 0x2050,
    NC_ACT_WEDDING_PROPOSEACK_ACK = 0x2051,
    NC_ACT_WEDDING_PROPOSEREQ_ACK = 0x2052,
    NC_ACT_WEDDING_HALL_RESERV_REQ = 0x2053,
    NC_ACT_WEDDING_HALL_RESERV_ACK = 0x2054,
    NC_ACT_WEDDING_COUPLE_ENTRANCE_RNG = 0x2055,
    NC_ACT_WEDDING_HALL_GUEST_ENTER_READY_REQ = 0x2056,
    NC_ACT_WEDDING_HALL_GUEST_ENTER_READY_ACK = 0x2057,
    NC_ACT_WEDDING_HALL_GUEST_ENTER_REQ = 0x2058,
    NC_ACT_WEDDING_HALL_GUEST_ENTER_ACK = 0x2059,
    NC_ACT_WEDDING_SOMEONE = 0x205A,
    NC_ACT_WEDDING_AGREEMENT_DIVORCE_REQ = 0x205B,
    NC_ACT_WEDDING_COMPULSORY_DIVORCE_REQ = 0x205C,
    NC_ACT_WEDDING_DIVORCE_REQ_ACK = 0x205D,
    NC_ACT_WEDDING_DIVORCE_REFUSE_CMD = 0x205E,
    NC_ACT_ACTIONBYITEM_REQ = 0x2067,
    NC_ACT_ACTIONBYITEM_ACK = 0x2068,
    NC_ACT_REINFORCERELOC_CMD = 0x2069,
    NC_ACT_REINFORCEMOVEBYPATH_CMD = 0x206A,
    NC_ACT_SETITEMHEALEFFECT = 0x206F,
    NC_ACT_AUTO_WAY_FINDING_USE_GATE_REQ = 0x2070,
    NC_ACT_AUTO_WAY_FINDING_USE_GATE_ACK = 0x2071,
    NC_ACT_NPC_ACTION_CMD = 0x2072,
    NC_ACT_NPC_MENU_CMD = 0x2073,
    NC_ACT_ANIMATION_START_CMD = 0x2074,
    NC_ACT_ANIMATION_STOP_CMD = 0x2075,
    NC_ACT_ANIMATION_LEVEL_CHANGE_CMD = 0x2076,
    NC_ACT_EFFECT_MESSAGE_CMD = 0x2077,
    NC_ACT_PLAY_SOUND_CMD = 0x2078,
    NC_ACT_SCRIPT_MSG_CMD = 0x2079,
    NC_ACT_OBJECT_SOUND_CMD = 0x207A,
    NC_ACT_OBJECT_EFFECT_CMD = 0x207B,
    NC_ACT_EVENT_CODE_ACTION_CMD = 0x207C,
    NC_ACT_SCRIPT_MSG_WORLD_CMD = 0x207D,
    NC_ACT_SHOW_CINEMATIC = 0x2082,
    NC_ACT_END_CINEMATIC = 0x2083,
    NC_ACT_DUEL_INVITE_REQ = 0x2084,
    NC_ACT_COOKING_OPEN_CMD = 0x2085,
    NC_ACT_COOKING_START_REQ = 0x2086,
    NC_ACT_COOKING_START_ACK = 0x2087,
    NC_ACT_COOKING_COMPLETE_CMD = 0x2088,

    NC_BAT_NULL = 0x2400,
    NC_BAT_TARGETTING_REQ = 0x2401,
    NC_BAT_TARGETINFO_CMD = 0x2402,
    NC_BAT_HIT_REQ = 0x2403,
    NC_BAT_SOMEONEDAMAGED_SMALL_CMD = 0x2404,
    NC_BAT_SOMEONEDAMAGED_LARGE_CMD = 0x2405,
    NC_BAT_SOMEONEDEAD_SMALL_CMD = 0x2406,
    NC_BAT_SOMEONEDEAD_LARGE_CMD = 0x2407,
    NC_BAT_UNTARGET_REQ = 0x2408,
    NC_BAT_SKILLENCHANT_REQ = 0x2409,
    NC_BAT_SOMEONESKILLENCHANT_REQ = 0x240A,
    NC_BAT_EXPGAIN_CMD = 0x240B,
    NC_BAT_LEVELUP_CMD = 0x240C,
    NC_BAT_SUMEONELEVELUP_CMD = 0x240D,
    NC_BAT_HPCHANGE_CMD = 0x240E,
    NC_BAT_SPCHANGE_CMD = 0x240F,
    NC_BAT_APCHANGE_CMD = 0x2410,
    NC_BAT_EXPLOST_CMD = 0x2411,
    NC_BAT_SMASH_REQ = 0x2412,
    NC_BAT_SMASH_HIT_ACK = 0x2413,
    NC_BAT_SMASH_HITTED_ACK = 0x2414,
    NC_BAT_SMASH_MISS_ACK = 0x2415,
    NC_BAT_SOMEONESMASH_DAMAGED_CMD = 0x2416,
    NC_BAT_SOMEONESMASH_DEAD_CMD = 0x2417,
    NC_BAT_SKILLCAST_REQ = 0x2418,
    NC_BAT_SKILLCAST_FAIL_ACK = 0x2419,
    NC_BAT_SKILLCAST_SUC_ACK = 0x241A,
    NC_BAT_SOMEONESKILLCAST_CMD = 0x241B,
    NC_BAT_SKILLCASTABORT_CMD = 0x241C,
    NC_BAT_SOMEONESKILLCASTCUT_CMD = 0x241D,
    NC_BAT_SKILLCASTCUT_CMD = 0x241E,
    NC_BAT_SKILLSMASH_CMD = 0x241F,
    NC_BAT_SKILLSMASH_HIT_CMD = 0x2420,
    NC_BAT_SKILLSMASH_HITTED_CMD = 0x2421,
    NC_BAT_SKILLSMASH_MISS_CMD = 0x2422,
    NC_BAT_SKILLSMASH_ENCHANT_CMD = 0x2423,
    NC_BAT_SOMEONESKILLSMASH_DAMAGED_CMD = 0x2424,
    NC_BAT_SOMEONESKILLSMASH_DEAD_CMD = 0x2425,
    NC_BAT_SOMEONESKILLSMASH_ENCHANT_CMD = 0x2426,
    NC_BAT_ABSTATESET_CMD = 0x2427,
    NC_BAT_ABSTATERESET_CMD = 0x2428,
    NC_BAT_ABSTATEINFORM_CMD = 0x2429,
    NC_BAT_ABSTATEINFORM_NOEFFECT_CMD = 0x242A,
    NC_BAT_BASHSTART_CMD = 0x242B,
    NC_BAT_BASH_HIT_CMD = 0x242C,
    NC_BAT_BASH_HITTED_CMD = 0x242D,
    NC_BAT_SOMEONEBASH_HIT_CMD = 0x242E,
    NC_BAT_BASH_MISS_CMD = 0x242F,
    NC_BAT_BASH_MISSED_CMD = 0x2430,
    NC_BAT_SOMEONEBASH_MISS_CMD = 0x2431,
    NC_BAT_BASHSTOP_CMD = 0x2432,
    NC_BAT_SKILLBASH_CAST_REQ = 0x2433,
    NC_BAT_SKILLBASH_CAST_FAIL_ACK = 0x2434,
    NC_BAT_SKILLBASH_CAST_SUC_ACK = 0x2435,
    NC_BAT_SOMEONESKILLBASH_CAST_CMD = 0x2436,
    NC_BAT_SKILLBASH_CASTABORT_CMD = 0x2437,
    NC_BAT_SOMEONESKILLBASH_CASTCUT_CMD = 0x2438,
    NC_BAT_SKILLBASH_HIT_CMD = 0x2439,
    NC_BAT_SKILLBASH_HITTED_CMD = 0x243A,
    NC_BAT_SOMEONESKILLBASH_HIT_CMD = 0x243B,
    NC_BAT_DOTDAMAGE_CMD = 0x243C,
    NC_BAT_CEASE_FIRE_CMD = 0x243D,
    NC_BAT_ASSIST_REQ = 0x243E,
    NC_BAT_ASSIST_ACK = 0x243F,
    NC_BAT_SKILLBASH_OBJ_CAST_REQ = 0x2440,
    NC_BAT_SKILLBASH_FLD_CAST_REQ = 0x2441,
    NC_BAT_SOMEONESKILLBASH_OBJ_CAST_CMD = 0x2442,
    NC_BAT_SOMEONESKILLBASH_FLD_CAST_CMD = 0x2443,
    NC_BAT_SKILLBASH_CASTABORT_REQ = 0x2444,
    NC_BAT_SKILLBASH_CASTABORT_ACK = 0x2445,
    NC_BAT_FAMEGAIN_CMD = 0x2446,
    NC_BAT_SWING_START_CMD = 0x2447,
    NC_BAT_SWING_DAMAGE_CMD = 0x2448,
    NC_BAT_SOMEONESWING_DAMAGE_CMD = 0x2449,
    NC_BAT_PKINPKFIELD_WMS_CMD = 0x244A,
    NC_BAT_PKINPKFIELD_CLIENT_CMD = 0x244B,
    NC_BAT_REALLYKILL_CMD = 0x244A,
    NC_BAT_MOBSLAYER_CMD = 0x244C,
    NC_BAT_TARGETCHANGE_CMD = 0x244D,
    NC_BAT_SKILLBASH_HIT_OBJ_START_CMD = 0x244E,
    NC_BAT_SOMEONESKILLBASH_HIT_OBJ_START_CMD = 0x244F,
    NC_BAT_SKILLBASH_HIT_FLD_START_CMD = 0x2450,
    NC_BAT_SOMEONESKILLBASH_HIT_FLD_START_CMD = 0x2451,
    NC_BAT_SKILLBASH_HIT_DAMAGE_CMD = 0x2452,
    NC_BAT_SOULCOLLECT_CMD = 0x2453,
    NC_BAT_ABSTATE_ERASE_REQ = 0x2454,
    NC_BAT_ABSTATE_ERASE_ACK = 0x2455,
    NC_BAT_SUMEONESKILLCUT_CMD = 0x2456,
    NC_BAT_SKILLBASH_HIT_BLAST_CMD = 0x2457,
    NC_BAT_WORLD_MOB_KILL_ANNOUNCE_CMD = 0x2458,
    NC_BAT_CLIENT_MOB_KILL_ANNOUNCE_CMD = 0x2459,
    NC_BAT_AREADOTDAMAGE_CMD = 0x245A,
    NC_BAT_REFLECTIONDAMAGE_CMD = 0x245B,
    NC_BAT_TOGGLESKILL_ON_CMD = 0x245C,
    NC_BAT_TOGGLESKILL_OFF_CMD = 0x245D,
    NC_BAT_SKILLBLAST_LIGHTNINGWAVE_CMD = 0x245E,
    NC_BAT_LPCHANGE_CMD = 0x245F,

    NC_OPTOOL_NULL = 0x2800,
    NC_OPTOOL_S2SCONNECT_LIST_REQ = 0x2801,
    NC_OPTOOL_S2SCONNECT_LIST_ACK = 0x2802,
    NC_OPTOOL_CLOSE_SERVER_REQ = 0x2803,
    NC_OPTOOL_CLOSE_SERVER_ACK = 0x2804,
    NC_OPTOOL_MAP_USER_LIST_REQ = 0x2805,
    NC_OPTOOL_MAP_USER_LIST_ACK = 0x2806,
    NC_OPTOOL_CONNECT_BRIF_REQ = 0x2807,
    NC_OPTOOL_CONNECT_BRIF_ACK = 0x2808,
    NC_OPTOOL_KQ_SCHEDULE_REQ = 0x2809,
    NC_OPTOOL_KQ_SCHEDULE_ACK = 0x280A,
    NC_OPTOOL_KQ_CHANGE_CMD = 0x280B,
    NC_OPTOOL_KQ_MAP_ALLOC_INFO_REQ = 0x280C,
    NC_OPTOOL_KQ_MAP_ALLOC_INFO_ACK = 0x280D,
    NC_OPTOOL_SET_CLIENT_NUM_OF_USER_LIMIT = 0x280E,
    NC_OPTOOL_REQ_CLIENT_NUM_OF_USER_LIMIT = 0x280F,
    NC_OPTOOL_ACK_CLIENT_NUM_OF_USER_LIMIT = 0x2810,
    NC_OPTOOL_KQ_DELETE_CMD = 0x2811,
    NC_OPTOOL_LOGIN_USER_RATABLE_GET_REQ = 0x2812,
    NC_OPTOOL_LOGIN_USER_RATABLE_GET_ACK = 0x2813,
    NC_OPTOOL_LOGIN_USER_RATABLE_SET_CMD = 0x2814,
    NC_OPTOOL_GUILD_TOURNAMENT_CHANGE_CMD = 0x2815,
    NC_OPTOOL_GUILD_TOURNAMENT_CHANGE_ACK = 0x2816,
    NC_OPTOOL_LOGON_PROCESS_TIME_VIEW_CLR = 0x2817,
    NC_OPTOOL_LOGON_PROCESS_TIME_VIEW_REQ = 0x2818,
    NC_OPTOOL_LOGON_PROCESS_TIME_VIEW_ACK = 0x2819,
    NC_OPTOOL_WM_SEND_PACKET_STATISTICS_CLR = 0x281A,
    NC_OPTOOL_WM_SEND_PACKET_STATISTICS_REQ = 0x281B,
    NC_OPTOOL_WM_SEND_PACKET_STATISTICS_ACK = 0x281C,
    NC_OPTOOL_CHARACTER_DELETE_REQ = 0x281D,
    NC_OPTOOL_CHARACTER_DELETE_ACK = 0x281E,
    NC_OPTOOL_CHARACTER_DELETE_CMD = 0x281F,
    NC_OPTOOL_GUILD_CHANGE_MEMBER_GRADE_REQ = 0x2820,
    NC_OPTOOL_GUILD_CHANGE_MEMBER_GRADE_ACK = 0x2821,
    NC_OPTOOL_GUILD_TOURNAMENT_SCHEDULE_RESET_REQ = 0x2822,
    NC_OPTOOL_GUILD_TOURNAMENT_SCHEDULE_RESET_ACK = 0x2823,
    NC_OPTOOL_GUILD_DATA_CHANGE_REQ = 0x2824,
    NC_OPTOOL_GUILD_DATA_CHANGE_ACK = 0x2825,
    NC_OPTOOL_KQ_ALL_RESET_CMD = 0x2826,
    NC_OPTOOL_FIND_USER_REQ = 0x2827,
    NC_OPTOOL_FIND_USER_ACK = 0x2828,
    NC_OPTOOL_KICK_USER_REQ = 0x2829,
    NC_OPTOOL_KICK_USER_ACK = 0x282A,
    NC_OPTOOL_GUILD_DISMISS_CANCEL_REQ = 0x282B,
    NC_OPTOOL_GUILD_DISMISS_CANCEL_ACK = 0x282C,

    NC_PATCH_NULL = 0x2C00,
    NC_PATCH_LAUNCHER_VERSION_REQ = 0x2C01,
    NC_PATCH_LAUNCHER_VERSION_ACK = 0x2C02,
    NC_PATCH_NOTICE_REQ = 0x2C03,
    NC_PATCH_NOTICE_ACK = 0x2C04,
    NC_PATCH_CLIENT_VERSION_REQ = 0x2C05,
    NC_PATCH_CLIENT_VERSION_ACK = 0x2C06,
    NC_PATCH_SERVER_ALLOC_REQ = 0x2C07,
    NC_PATCH_SERVER_ALLOC_ACK = 0x2C08,
    NC_PATCH_INFO_REQ = 0x2C09,
    NC_PATCH_INFO_ACK = 0x2C0A,
    NC_PATCH_INFO_DATA_REQ = 0x2C0B,
    NC_PATCH_INFO_DATA_ACK = 0x2C0C,
    NC_PATCH_FILE_INFO_REQ = 0x2C0D,
    NC_PATCH_FILE_INFO_ACK = 0x2C0E,
    NC_PATCH_FILE_DATA_REQ = 0x2C0F,
    NC_PATCH_FILE_DATA_ACK = 0x2C10,
    NC_PATCH_CLOSE_REQ = 0x2C11,
    NC_PATCH_STATUS_SET_REQ = 0x2C12,
    NC_PATCH_NOTICE_SET_REQ = 0x2C13,
    NC_PATCH_INFO_VERIFY_REQ = 0x2C14,
    NC_PATCH_INFO_VERIFY_ACK = 0x2C15,
    NC_PATCH_DATA_SERVER_READY_CMD = 0x2C16,
    NC_PATCH_DATA_SERVER_USER_COUNT_CMD = 0x2C17,

    NC_ITEM_NULL = 0x3000,
    NC_ITEM_CELLCHANGE_CMD = 0x3001,
    NC_ITEM_EQUIPCHANGE_CMD = 0x3002,
    NC_ITEM_BUY_REQ = 0x3003,
    NC_ITEM_BUY_ACK = 0x3004,
    NC_ITEM_SELL_ACK = 0x3005,
    NC_ITEM_SELL_REQ = 0x3006,
    NC_ITEM_DROP_REQ = 0x3007,
    NC_ITEM_DROP_ACK = 0x3008,
    NC_ITEM_PICK_REQ = 0x3009,
    NC_ITEM_PICK_ACK = 0x300A,
    NC_ITEM_RELOC_REQ = 0x300B,
    NC_ITEM_RELOC_ACK = 0x300C,
    NC_ITEM_SPLIT_REQ = 0x300D,
    NC_ITEM_SPLIT_ACK = 0x300E,
    NC_ITEM_EQUIP_REQ = 0x300F,
    NC_ITEM_RINGEQUIP_REQ = 0x3010,
    NC_ITEM_EQUIP_ACK = 0x3011,
    NC_ITEM_UNEQUIP_REQ = 0x3012,
    NC_ITEM_UNEQUIP_ACK = 0x3013,
    NC_ITEM_SOMEONEPICK_CMD = 0x3014,
    NC_ITEM_USE_REQ = 0x3015,
    NC_ITEM_USE_ACK = 0x3016,
    NC_ITEM_UPGRADE_REQ = 0x3017,
    NC_ITEM_UPGRADE_ACK = 0x3018,
    NC_ITEM_USEABORT_CMD = 0x3019,
    NC_ITEM_USECOMPLETE_CMD = 0x301A,
    NC_ITEM_PICKOTHER_ACK = 0x301B,
    NC_ITEM_DEPOSIT_REQ = 0x301C,
    NC_ITEM_DEPOSIT_ACK = 0x301D,
    NC_ITEM_WITHDRAW_REQ = 0x301E,
    NC_ITEM_WITHDRAW_ACK = 0x301F,
    NC_ITEM_CHARGEDINVENOPEN_REQ = 0x3020,
    NC_ITEM_CHARGEDINVENOPEN_ACK = 0x3021,
    NC_ITEM_CHARGED_WITHDRAW_REQ = 0x3022,
    NC_ITEM_CHARGED_WITHDRAW_ACK = 0x3023,
    NC_ITEM_BREAKSUCCESS_CMD = 0x3024,
    NC_ITEM_BREAKFAIL_CMD = 0x3025,
    NC_ITEM_GUILD_STORAGE_WITHDRAW_REQ = 0x3026,
    NC_ITEM_GUILD_STORAGE_WITHDRAW_ACK = 0x3027,
    NC_ITEM_OPENSTORAGEPAGE_REQ = 0x3028,
    NC_ITEM_SOMEONEUSE_CMD = 0x3029,
    NC_ITEM_DISMANTLE_REQ = 0x302A,
    NC_ITEM_DISMANTLE_ACK = 0x302B,
    NC_ITEM_REWARDINVENOPEN_REQ = 0x302C,
    NC_ITEM_REWARDINVENOPEN_ACK = 0x302D,
    NC_ITEM_REWARDINVENOPENFAIL_ACK = 0x302E,
    NC_ITEM_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_REQ = 0x302F,
    NC_ITEM_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_ACK = 0x3030,
    NC_ITEM_GUILD_ACADEMY_REWARD_STORAGE_DEPOSIT_REQ = 0x3031,
    NC_ITEM_GUILD_ACADEMY_REWARD_STORAGE_DEPOSIT_ACK = 0x3032,
    NC_ITEM_MH_FURNITURE_ENDURE_KIT_USE_REQ = 0x3033,
    NC_ITEM_MH_FURNITURE_ENDURE_KIT_USE_ACK = 0x3034,
    NC_ITEM_WEAPONENDURE_CHARGE_REQ = 0x3035,
    NC_ITEM_WEAPONENDURE_CHARGE_ACK = 0x3036,
    NC_ITEM_WEAPONENDURESET_CMD = 0x3037,
    NC_ITEM_ITEMBREAK_CMD = 0x3038,
    NC_ITEM_REVIVEITEMUSE_CMD = 0x3039,
    NC_ITEM_REVIVEITEMUSEFAIL_CMD = 0x303A,
    NC_ITEM_DICE_GAME_CMD = 0x303B,
    NC_ITEM_DICE_GAME_START_REQ = 0x303C,
    NC_ITEM_DICE_GAME_START_ACK = 0x303D,
    NC_ITEM_DICE_GAME_START_CMD = 0x303E,
    NC_ITEM_DICE_GAME_RESULT_CMD = 0x303F,
    NC_ITEM_ENCHANT_ADD_GEM_REQ = 0x3040,
    NC_ITEM_ENCHANT_ADD_GEM_ACK = 0x3041,
    NC_ITEM_ENCHANT_REMOVE_GEM_REQ = 0x3042,
    NC_ITEM_ENCHANT_REMOVE_GEM_ACK = 0x3043,
    NC_ITEM_ENCHANT_ADD_NEW_SOCKET_REQ = 0x3044,
    NC_ITEM_ENCHANT_ADD_NEW_SOCKET_ACK = 0x3045,
    NC_ITEM_ENCHANT_SET_GEM_LOT_CMD = 0x3046,
    NC_ITEM_BUY_SUC_ACTION_CMD = 0x3047,
    NC_ITEM_EQUIP_BELONGED_CANCEL_USE_REQ = 0x3048,
    NC_ITEM_EQUIP_BELONGED_CANCEL_USE_ACK = 0x3049,
    NC_ITEM_AUTO_ARRANGE_INVEN_REQ = 0x304A,
    NC_ITEM_AUTO_ARRANGE_INVEN_ACK = 0x304B,
    NC_ITEM_ACCOUNT_STORAGE_OPEN_CMD = 0x304C,
    NC_ITEM_ACCOUNT_STORAGE_CLOSE_CMD = 0x304D,
    NC_ITEM_USE_ACTIVESKILL_REQ = 0x304E,
    NC_ITEM_USE_ACTIVESKILL_ACK = 0x304F,
    NC_ITEM_MINIMON_EQUIP_REQ = 0x3050,
    NC_ITEM_MOVER_UPGRADE_REQ = 0x3051,
    NC_ITEM_MOVER_UPGRADE_ACK = 0x3052,
    NC_ITEM_RANDOMOPTION_CHANGE_REQ = 0x3053,
    NC_ITEM_RANDOMOPTION_CHANGE_ACK = 0x3054,
    NC_ITEM_CHAT_COLOR_CHANGE_REQ = 0x3055,
    NC_ITEM_CHAT_COLOR_CHANGE_ACK = 0x3056,
    NC_ITEM_TERMEXTEND_REQ = 0x3057,
    NC_ITEM_TERMEXTEND_ACK = 0x3058,
    NC_ITEM_REPURCHASE_REQ = 0x3059,
    NC_ITEM_REPURCHASE_ACK = 0x305A,
    NC_ITEM_SELL_ITEM_LIST_CMD = 0x305B,
    NC_ITEM_SELL_ITEM_INSERT_CMD = 0x305C,
    NC_ITEM_SELL_ITEM_DELETE_CMD = 0x305D,
    NC_ITEM_CLASS_CHANGE_REQ = 0x305E,
    NC_ITEM_CLASS_CHANGE_ACK = 0x305F,
    NC_ITEM_OPENCLASSCHANGEMENU_CMD = 0x3060,
    NC_ITEM_RANDOMOPTION_CHANGE_ACCEPT_REQ = 0x3061,
    NC_ITEM_RANDOMOPTION_CHANGE_ACCEPT_ACK = 0x3062,
    NC_ITEM_SHIELDENDURE_CHARGE_REQ = 0x3064,
    NC_ITEM_SHIELDENDURE_CHARGE_ACK = 0x3065,
    NC_ITEM_SHIELDENDURESET_CMD = 0x3066,
    NC_ITEM_MAPLINK_SCROLL_REQ = 0x3067,
    NC_ITEM_MAPLINK_SCROLL_ACK = 0x3068,
    NC_ITEM_MIX_ITEM_REQ = 0x3069,
    NC_ITEM_MIX_ITEM_ACK = 0x306A,
    NC_ITEM_RANDOMOPTION_RECOVER_COUNT_LIMIT_REQ = 0x306B,
    NC_ITEM_RANDOMOPTION_RECOVER_COUNT_LIMIT_ACK = 0x306C,
    NC_ITEM_NEW_UPGRADE_REQ = 0x306D,
    NC_ITEM_NEW_UPGRADE_ACK = 0x306E,
    NC_ITEM_BRACELET_UPGRADE_REQ = 0x306F,
    NC_ITEM_BRACELET_UPGRADE_ACK = 0x3070,

    NC_ITEMDB_NULL = 0x3400,
    NC_ITEMDB_ADMINCREATE_REQ = 0x3401,
    NC_ITEMDB_ADMINCREATESUC_ACK = 0x3402,
    NC_ITEMDB_ADMINCREATEFAIL_ACK = 0x3403,
    NC_ITEMDB_QUESTALL_REQ = 0x3404,
    NC_ITEMDB_QUESTALLSUC_ACK = 0x3405,
    NC_ITEMDB_QUESTALLFAIL_ACK = 0x3406,
    NC_ITEMDB_QUESTLOT_REQ = 0x3407,
    NC_ITEMDB_QUESTLOTSUC_ACK = 0x3408,
    NC_ITEMDB_QUESTLOTFAIL_ACK = 0x3409,
    NC_ITEMDB_BUYALL_REQ = 0x340A,
    NC_ITEMDB_BUYALLSUC_ACK = 0x340B,
    NC_ITEMDB_BUYALLFAIL_ACK = 0x340C,
    NC_ITEMDB_BUYLOT_REQ = 0x340D,
    NC_ITEMDB_BUYLOTSUC_ACK = 0x340E,
    NC_ITEMDB_BUYLOTFAIL_ACK = 0x340F,
    NC_ITEMDB_EQUIP_REQ = 0x3410,
    NC_ITEMDB_EQUIPSUC_ACK = 0x3411,
    NC_ITEMDB_EQUIPFAIL_ACK = 0x3412,
    NC_ITEMDB_UNEQUIP_REQ = 0x3413,
    NC_ITEMDB_UNEQUIPSUC_ACK = 0x3414,
    NC_ITEMDB_UNEQUIPFAIL_ACK = 0x3415,
    NC_ITEMDB_DROPALL_REQ = 0x3416,
    NC_ITEMDB_DROPALLSUC_ACK = 0x3417,
    NC_ITEMDB_DROPALLFAIL_ACK = 0x3418,
    NC_ITEMDB_DROPLOT_REQ = 0x3419,
    NC_ITEMDB_DROPLOTSUC_ACK = 0x341A,
    NC_ITEMDB_DROPLOTFAIL_ACK = 0x341B,
    NC_ITEMDB_PICKALL_REQ = 0x341C,
    NC_ITEMDB_PICKALLSUC_ACK = 0x341D,
    NC_ITEMDB_PICKALLFAIL_ACK = 0x341E,
    NC_ITEMDB_PICKMERGE_REQ = 0x341F,
    NC_ITEMDB_PICKMERGESUC_ACK = 0x3420,
    NC_ITEMDB_PICKMERGEFAIL_ACK = 0x3421,
    NC_ITEMDB_SELLALL_REQ = 0x3422,
    NC_ITEMDB_SELLALLSUC_ACK = 0x3423,
    NC_ITEMDB_SELLALLFAIL_ACK = 0x3424,
    NC_ITEMDB_SELLLOT_REQ = 0x3425,
    NC_ITEMDB_SELLLOTSUC_ACK = 0x3426,
    NC_ITEMDB_SELLLOTFAIL_ACK = 0x3427,
    NC_ITEMDB_RELOC_REQ = 0x3428,
    NC_ITEMDB_RELOCSUC_ACK = 0x3429,
    NC_ITEMDB_RELOCFAIL_ACK = 0x342A,
    NC_ITEMDB_EXCHANGE_REQ = 0x342B,
    NC_ITEMDB_EXCHANGESUC_ACK = 0x342C,
    NC_ITEMDB_EXCHANGEFAIL_ACK = 0x342D,
    NC_ITEMDB_MERGE_REQ = 0x342E,
    NC_ITEMDB_MERGESUC_ACK = 0x342F,
    NC_ITEMDB_MERGEFAIL_ACK = 0x3430,
    NC_ITEMDB_SPLIT_N_MERGE_REQ = 0x3431,
    NC_ITEMDB_SPLIT_N_MERGESUC_ACK = 0x3432,
    NC_ITEMDB_SPLIT_N_MERGEFAIL_ACK = 0x3433,
    NC_ITEMDB_SPLIT_REQ = 0x3434,
    NC_ITEMDB_SPLITSUC_ACK = 0x3435,
    NC_ITEMDB_SPLITFAIL_ACK = 0x3436,
    NC_ITEMDB_MOB_DROP_CMD = 0x3437,
    NC_ITEMDB_PICKMONEY_REQ = 0x3438,
    NC_ITEMDB_PICKMONEYSUC_ACK = 0x3439,
    NC_ITEMDB_PICKMONEYFAIL_ACK = 0x343A,
    NC_ITEMDB_ITEMTRADE_REQ = 0x343B,
    NC_ITEMDB_ITEMTRADEFAIL_ACK = 0x343C,
    NC_ITEMDB_ITEMTRADESUC_ACK = 0x343D,
    NC_ITEMDB_USELOT_REQ = 0x343E,
    NC_ITEMDB_USEALL_REQ = 0x343F,
    NC_ITEMDB_USE_ACK = 0x3440,
    NC_ITEMDB_SOULSTONEBUY_REQ = 0x3441,
    NC_ITEMDB_SOULSTONEBUYSUC_ACK = 0x3442,
    NC_ITEMDB_SOULSTONEBUYFAIL_ACK = 0x3443,
    NC_ITEMDB_OPENSTORAGE_REQ = 0x3444,
    NC_ITEMDB_OPENSTORAGE_FAIL_ACK = 0x3445,
    NC_ITEMDB_OPENSTORAGE_ACK = 0x3446,
    NC_ITEMDB_UPGRADE_REQ = 0x3447,
    NC_ITEMDB_UPGRADE_ACK = 0x3448,
    NC_ITEMDB_ITEMCHANGE_REQ = 0x3449,
    NC_ITEMDB_ITEMCHANGE_ACK = 0x344A,
    NC_ITEMDB_ITEMTOTALINFORM_REQ = 0x344B,
    NC_ITEMDB_ITEMTOTALINFORM_ACK = 0x344C,
    NC_ITEMDB_CREATEITEMLIST_REQ = 0x344D,
    NC_ITEMDB_CREATEITEMLISTSUC_ACK = 0x344E,
    NC_ITEMDB_CREATEITEMLISTFAIL_ACK = 0x344F,
    NC_ITEMDB_GETFROMCHEST_REQ = 0x3450,
    NC_ITEMDB_GETFROMCHESTSUC_ACK = 0x3451,
    NC_ITEMDB_GETFROMCHESTFAIL_ACK = 0x3452,
    NC_ITEMDB_BOOTHTRADE_ALL_REQ = 0x3453,
    NC_ITEMDB_BOOTHTRADE_MERGE_REQ = 0x3454,
    NC_ITEMDB_BOOTHTRADE_LOT_REQ = 0x3455,
    NC_ITEMDB_BOOTHTRADE_ACK = 0x3456,
    NC_ITEMDB_PRODUCE_REQ = 0x3457,
    NC_ITEMDB_PRODUCE_ACK = 0x3458,
    NC_ITEMDB_DESTROY_REQ = 0x3459,
    NC_ITEMDB_DESTROY_ACK = 0x345A,
    NC_ITEMDB_QUESTREWARD_REQ = 0x345B,
    NC_ITEMDB_QUESTREWARD_ACK = 0x345C,
    NC_ITEMDB_QUESTITEMGET_REQ = 0x345D,
    NC_ITEMDB_QUESTITEMGET_ACK = 0x345E,
    NC_ITEMDB_DEPOSIT_REQ = 0x345F,
    NC_ITEMDB_DEPOSIT_ACK = 0x3460,
    NC_ITEMDB_WITHDRAW_REQ = 0x3461,
    NC_ITEMDB_WITHDRAW_ACK = 0x3462,
    NC_ITEMDB_CHARGED_LIST_REQ = 0x3463,
    NC_ITEMDB_CHARGED_LIST_ACK = 0x3464,
    NC_ITEMDB_CHARGED_WITHDRAW_REQ = 0x3465,
    NC_ITEMDB_CHARGED_WITHDRAW_ACK = 0x3466,
    NC_ITEMDB_CREATEMUSHROOM_REQ = 0x3467,
    NC_ITEMDB_CREATEMUSHROOMSUC_ACK = 0x3468,
    NC_ITEMDB_CREATEMUSHROOMFAIL_ACK = 0x3469,
    NC_ITEMDB_ITEMBREAK_REQ = 0x346A,
    NC_ITEMDB_ITEMBREAKSUC_ACK = 0x346B,
    NC_ITEMDB_ITEMBREAKFAIL_ACK = 0x346C,
    NC_ITEMDB_CHESTITEM_REQ = 0x346D,
    NC_ITEMDB_CHESTITEM_ACK = 0x346E,
    NC_ITEMDB_GUILD_TOURNAMENT_REWARD_CREATE_REQ = 0x346F,
    NC_ITEMDB_GUILD_TOURNAMENT_REWARD_CREATE_ACK = 0x3470,
    NC_ITEMDB_OPEN_GUILD_STORAGE_REQ = 0x3471,
    NC_ITEMDB_OPEN_GUILD_STORAGE_FAIL_ACK = 0x3472,
    NC_ITEMDB_OPEN_GUILD_STORAGE_ACK = 0x3473,
    NC_ITEMDB_GUILD_STORAGE_WITHDRAW_REQ = 0x3474,
    NC_ITEMDB_GUILD_STORAGE_WITHDRAW_ACK = 0x3475,
    NC_ITEMDB_DISMANTLE_REQ = 0x3476,
    NC_ITEMDB_DISMANTLE_ACK = 0x3477,
    NC_ITEMDB_INC_DEC_MONEY_REQ = 0x347A,
    NC_ITEMDB_INC_DEC_MONEYSUC_ACK = 0x347B,
    NC_ITEMDB_INC_DEC_MONEYFAIL_ACK = 0x347C,
    NC_ITEMDB_MINIHOUSE_EFFECT_DEMANDGOOD_REQ = 0x347D,
    NC_ITEMDB_MINIHOUSE_EFFECT_DEMANDGOOD_ACK = 0x347E,
    NC_ITEMDB_REINFORCEUNEQUIP_REQ = 0x347F,
    NC_ITEMDB_REINFORCEUNEQUIPSUC_ACK = 0x3480,
    NC_ITEMDB_REINFORCEUNEQUIPFAIL_ACK = 0x3481,
    NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_OPEN_REQ = 0x3482,
    NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_OPEN_FAIL_ACK = 0x3483,
    NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_OPEN_ACK = 0x3484,
    NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_REQ = 0x3485,
    NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_ACK = 0x3486,
    NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_DEPOSIT_REQ = 0x3487,
    NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_DEPOSIT_ACK = 0x3488,
    NC_ITEMDB_MINIHOUSE_PORTAL_EFFECT_DEMANDGOOD_REQ = 0x3489,
    NC_ITEMDB_MINIHOUSE_PORTAL_EFFECT_DEMANDGOOD_ACK = 0x348A,
    NC_ITEMDB_FURNITURE_ENDURE_REQ = 0x348B,
    NC_ITEMDB_FURNITURE_ENDURE_ACK = 0x348C,
    NC_ITEMDB_WEAPONENDURE_CHARGE_REQ = 0x348D,
    NC_ITEMDB_WEAPONENDURE_CHARGE_ACK = 0x348E,
    NC_ITEMDB_WEAPONENDURESET_CMD = 0x348F,
    NC_ITEMDB_GUILD_TOKEN_BUYALL_REQ = 0x3490,
    NC_ITEMDB_GUILD_TOKEN_BUYALLSUC_ACK = 0x3491,
    NC_ITEMDB_GUILD_TOKEN_BUYALLFAIL_ACK = 0x3492,
    NC_ITEMDB_GUILD_TOKEN_BUYLOT_REQ = 0x3493,
    NC_ITEMDB_GUILD_TOKEN_BUYLOTSUC_ACK = 0x3494,
    NC_ITEMDB_GUILD_TOKEN_BUYLOTFAIL_ACK = 0x3495,
    NC_ITEMDB_ENCHANT_ADD_GEM_REQ = 0x3496,
    NC_ITEMDB_ENCHANT_ADD_GEM_ACK = 0x3497,
    NC_ITEMDB_ENCHANT_REMOVE_GEM_REQ = 0x3498,
    NC_ITEMDB_ENCHANT_REMOVE_GEM_ACK = 0x3499,
    NC_ITEMDB_ENCHANT_ADD_NEW_SOCKET_REQ = 0x349A,
    NC_ITEMDB_ENCHANT_ADD_NEW_SOCKET_ACK = 0x349B,
    NC_ITEMDB_ENCHANT_SET_GEM_LOT_REQ = 0x349C,
    NC_ITEMDB_ENCHANT_SET_GEM_LOT_ACK = 0x349D,
    NC_ITEMDB_MYSTERY_VAULT_MAKEITEM_REQ = 0x349E,
    NC_ITEMDB_MYSTERY_VAULT_MAKEITEM_ACK = 0x349F,
    NC_ITEMDB_BUYCAPSULE_REQ = 0x34A0,
    NC_ITEMDB_BUYCAPSULE_ACK = 0x34A1,
    NC_ITEMDB_CAPSULEITEM_REQ = 0x34A2,
    NC_ITEMDB_CAPSULEITEM_ACK = 0x34A3,
    NC_ITEMDB_GETFROMCAPSULE_REQ = 0x34A4,
    NC_ITEMDB_GETFROMCAPSULE_ACK = 0x34A5,
    NC_ITEMDB_EQUIP_BELONGED_CANCEL_USE_REQ = 0x34A6,
    NC_ITEMDB_EQUIP_BELONGED_CANCEL_USE_ACK = 0x34A7,
    NC_ITEMDB_ITEMINFO_REQ = 0x34A8,
    NC_ITEMDB_ITEMINFO_ACK = 0x34A9,
    NC_ITEMDB_ITEMREBUILD_REQ = 0x34AA,
    NC_ITEMDB_ITEMREBUILD_ACK = 0x34AB,
    NC_ITEMDB_MOVER_UPGRADE_REQ = 0x34AC,
    NC_ITEMDB_MOVER_UPGRADE_ACK = 0x34AD,
    NC_ITEMDB_MOVER_RAREMOVER_REQ = 0x34AE,
    NC_ITEMDB_MOVER_RAREMOVER_ACK = 0x34AF,
    NC_ITEMDB_ITEMMONEY_BUYALL_REQ = 0x34B0,
    NC_ITEMDB_ITEMMONEY_BUYLOT_REQ = 0x34B1,
    NC_ITEMDB_ITEMMONEY_BUY_ACK = 0x34B2,
    NC_ITEMDB_RANDOMOPTION_CHANGE_REQ = 0x34B3,
    NC_ITEMDB_RANDOMOPTION_CHANGE_ACK = 0x34B4,
    NC_ITEMDB_CHAT_COLOR_CHANGE_REQ = 0x34B5,
    NC_ITEMDB_CHAT_COLOR_CHANGE_ACK = 0x34B6,
    NC_ITEMDB_TERMEXTEND_REQ = 0x34B7,
    NC_ITEMDB_TERMEXTEND_ACK = 0x34B8,
    NC_ITEMDB_REPURCHASE_ALL_REQ = 0x34B9,
    NC_ITEMDB_REPURCHASE_ALL_ACK = 0x34BA,
    NC_ITEMDB_REPURCHASE_LOT_REQ = 0x34BB,
    NC_ITEMDB_REPURCHASE_LOT_ACK = 0x34BC,
    NC_ITEMDB_CLASS_CHANGE_REQ = 0x34BD,
    NC_ITEMDB_CLASS_CHANGE_ACK = 0x34BE,
    NC_ITEMDB_UES_FRIEND_POINT_REQ = 0x34BF,
    NC_ITEMDB_UES_FRIEND_POINT_ACK = 0x34C0,
    NC_ITEMDB_RANDOMOPTION_CHANGE_CONSUME_AND_COUNTING_REQ = 0x34C1,
    NC_ITEMDB_RANDOMOPTION_CHANGE_CONSUME_AND_COUNTING_ACK = 0x34C2,
    NC_ITEMDB_SHIELDENDURE_CHARGE_REQ = 0x34C6,
    NC_ITEMDB_SHIELDENDURE_CHARGE_ACK = 0x34C7,
    NC_ITEMDB_SHIELDENDURESET_CMD = 0x34C8,
    NC_ITEMDB_MAPLINK_ITEM_CONSUME_REQ = 0x34C9,
    NC_ITEMDB_MAPLINK_ITEM_CONSUME_ACK = 0x34CA,
    NC_ITEMDB_MIX_ITEM_REQ = 0x34CB,
    NC_ITEMDB_MIX_ITEM_ACK = 0x34CC,
    NC_ITEMDB_RANDOMOPTION_RECOVER_COUNT_LIMIT_REQ = 0x34CD,
    NC_ITEMDB_RANDOMOPTION_RECOVER_COUNT_LIMIT_ACK = 0x34CE,
    NC_ITEMDB_RESET_SCROLL_LINK_MAP_INFO_CMD = 0x34CF,
    NC_ITEMDB_NEW_UPGRADE_REQ = 0x34D1,
    NC_ITEMDB_NEW_UPGRADE_ACK = 0x34D2,
    NC_ITEMDB_BRACELET_UPGRADE_REQ = 0x34D3,
    NC_ITEMDB_BRACELET_UPGRADE_ACK = 0x34D4,

    NC_PARTY_NULL = 0x3800,
    NC_PARTY_FUNDAMENTAL_CMD = 0x3801,
    NC_PARTY_JOIN_REQ = 0x3802,
    NC_PARTY_JOINPROPOSE_REQ = 0x3803,
    NC_PARTY_JOINPROPOSE_ALLOW_ACK = 0x3804,
    NC_PARTY_JOINPROPOSE_REJECT_ACK = 0x3805,
    NC_PARTY_JOINPROPOSE_TIMEOUT_ACK = 0x3806,
    NC_PARTY_JOIN_ACK = 0x3807,
    NC_PARTY_JOIN_CMD = 0x3808,
    NC_PARTY_MEMBER_LIST_CMD = 0x3809,
    NC_PARTY_LEAVE_REQ = 0x380A,
    NC_PARTY_LEAVE_ACK = 0x380B,
    NC_PARTY_LEAVE_CMD = 0x380C,
    NC_PARTY_KICKOFF_REQ = 0x3814,
    NC_PARTY_KICKOFF_ACK = 0x3815,
    NC_PARTY_KICKOFF_CMD = 0x3816,
    NC_PARTY_DISMISS_ACK = 0x381E,
    NC_PARTY_DISMISS_CMD = 0x381F,
    NC_PARTY_CHANGEMASTER_REQ = 0x3828,
    NC_PARTY_CHANGEMASTER_ACK = 0x3829,
    NC_PARTY_CHANGEMASTER_CMD = 0x382A,
    NC_PARTY_MEMBERINFORM_CMD = 0x3832,
    NC_PARTY_MEMBERCLASS_CMD = 0x3833,
    NC_PARTY_LOGIN_CMD = 0x383C,
    NC_PARTY_LOGININFO_CMD = 0x383D,
    NC_PARTY_LOGOUT_CMD = 0x3846,
    NC_PARTY_LOGOUTINFO_CMD = 0x3847,
    NC_PARTY_MEMBERINFOREQ_CMD = 0x3848,
    NC_PARTY_MEMBERLOCATION_CMD = 0x3849,
    NC_PARTY_MEMBERMAPOUT = 0x384A,
    NC_PARTY_ITEM_LOOTING_SET = 0x384B,
    NC_PARTY_ITEM_LOOTING_CMD = 0x384C,
    NC_PARTY_ITEM_LOOTING_ZONE_CMD = 0x384D,
    NC_PARTY_MEMBERINFORM_REQ = 0x384E,
    NC_PARTY_MEMBERINFORM_ACK = 0x384F,
    NC_PARTY_FINDER_ADD_REQ = 0x3850,
    NC_PARTY_FINDER_ADD_ACK = 0x3851,
    NC_PARTY_FINDER_DELETE_REQ = 0x3852,
    NC_PARTY_FINDER_DELETE_ACK = 0x3853,
    NC_PARTY_FINDER_LIST_REQ = 0x3854,
    NC_PARTY_FINDER_LIST_ACK = 0x3855,
    NC_PARTY_FINDER_DELETE_YOUR_MSG_CMD = 0x3856,
    NC_PARTY_SET_LOOTER_REQ = 0x385A,
    NC_PARTY_SET_LOOTER_ACK = 0x385B,
    NC_PARTY_SET_LOOTER_CMD = 0x385C,
    NC_PARTY_SET_LOOTER_BROAD_CMD = 0x385D,
    NC_PARTY_ZONE_SET_LOOTER_CMD = 0x385E,
    NC_PARTY_ITEM_JOIN_LOOTING_CMD = 0x385F,
    NC_PARTY_ZONE_JOIN_CMD = 0x3860,
    NC_PARTY_ZONE_LEAVE_CMD = 0x3861,

    NC_MENU_NULL = 0x3C00,
    NC_MENU_SERVERMENU_REQ = 0x3C01,
    NC_MENU_SERVERMENU_ACK = 0x3C02,
    NC_MENU_SHOPOPENWEAPON_CMD = 0x3C03,
    NC_MENU_SHOPOPENSKILL_CMD = 0x3C04,
    NC_MENU_SHOPOPENSOULSTONE_CMD = 0x3C05,
    NC_MENU_SHOPOPENITEM_CMD = 0x3C06,
    NC_MENU_OPENSTORAGE_FAIL_CMD = 0x3C07,
    NC_MENU_OPENSTORAGE_CMD = 0x3C08,
    NC_MENU_SHOPOPENTABLE_WEAPON_CMD = 0x3C09,
    NC_MENU_SHOPOPENTABLE_SKILL_CMD = 0x3C0A,
    NC_MENU_SHOPOPENTABLE_ITEM_CMD = 0x3C0B,
    NC_MENU_GUILDMENUOPEN_CMD = 0x3C0C,
    NC_MENU_RANDOMOPTION_CMD = 0x3C0E,
    NC_MENU_SERVERMENU_CLOSE_CMD = 0x3C0F,
    NC_MENU_INDUNRANK_CMD = 0x3C10,

    NC_CHARSAVE_NULL = 0x4000,
    NC_CHARSAVE_ALL_REQ = 0x4001,
    NC_CHARSAVE_ALL_ACK = 0x4002,
    NC_CHARSAVE_LOCATION_CMD = 0x4003,
    NC_CHARSAVE_LEVEL_CMD = 0x4004,
    NC_CHARSAVE_QUEST_DOING_REQ = 0x4005,
    NC_CHARSAVE_QUEST_DOING_ACK = 0x4006,
    NC_CHARSAVE_ABSTATE_REQ = 0x4007,
    NC_CHARSAVE_ABSTATE_ACK = 0x4008,
    NC_CHARSAVE_SKILL_REQ = 0x4009,
    NC_CHARSAVE_SKILL_ACK = 0x400A,
    NC_CHARSAVE_TITLE_REQ = 0x400B,
    NC_CHARSAVE_TITLE_ACK = 0x400C,
    NC_CHARSAVE_CHARSTAT_CMD = 0x400D,
    NC_CHARSAVE_2WLDMAN_ALL_CMD = 0x400E,
    NC_CHARSAVE_2WLDMAN_QUEST_DOING_CMD = 0x400F,
    NC_CHARSAVE_2WLDMAN_QUEST_DONE_CMD = 0x4010,
    NC_CHARSAVE_2WLDMAN_ABSTATE_CMD = 0x4011,
    NC_CHARSAVE_2WLDMAN_SKILL_CMD = 0x4012,
    NC_CHARSAVE_2WLDMAN_ITEM_CMD = 0x4013,
    NC_CHARSAVE_2WLDMAN_CHESTINFO_CMD = 0x4014,
    NC_CHARSAVE_2WLDMAN_GAME_CMD = 0x4015,
    NC_CHARSAVE_2WLDMAN_TITLE_CMD = 0x4016,
    NC_CHARSAVE_2WLDMAN_MISC_CMD = 0x4017,
    NC_CHARSAVE_PKCOUNT_CMD = 0x4018,
    NC_CHARSAVE_2WLDMAN_LINK_FROM_CMD = 0x4019,
    NC_CHARSAVE_REST_EXP_LAST_EXEC_TIME_SAVE_REQ = 0x401A,
    NC_CHARSAVE_REST_EXP_LAST_EXEC_TIME_SAVE_ACK = 0x401B,
    NC_CHARSAVE_AUTO_PICK_SAVE_REQ = 0x401C,
    NC_CHARSAVE_AUTO_PICK_SAVE_ACK = 0x401D,
    NC_CHARSAVE_SET_CHAT_BLOCK_SPAMER_WM_CMD = 0x4021,
    NC_CHARSAVE_SET_CHAT_BLOCK_SPAMER_DB_CMD = 0x4022,
    NC_CHARSAVE_ITEMACTIONCOOLTIME_REQ = 0x4023,
    NC_CHARSAVE_ITEMACTIONCOOLTIME_ACK = 0x4024,
    NC_CHARSAVE_UI_STATE_SAVE_REQ = 0x4025,
    NC_CHARSAVE_UI_STATE_SAVE_ACK = 0x4026,
    NC_CHARSAVE_DB_UI_STATE_SAVE_REQ = 0x4027,
    NC_CHARSAVE_DB_UI_STATE_SAVE_ACK = 0x4028,
    NC_CHARSAVE_2WLDMAN_QUEST_READ_CMD = 0x4029,
    NC_CHARSAVE_2WLDMAN_SINGLE_OPTION_CMD = 0x402A,
    NC_CHARSAVE_2WLDMAN_QUEST_REPEAT_CMD = 0x402B,
    NC_CHARSAVE_2WLDMAN_COININFO_CMD = 0x402C,
    NC_CHARSAVE_CHAT_COLOR_CMD = 0x4031,
    NC_CHARSAVE_2WLDMAN_CHAT_COLOR_CMD = 0x4032,
    NC_CHARSAVE_2WLDMAN_PET_LINK_RESUMMON_CMD = 0x4033,
    NC_CHARSAVE_2WLDMAN_ITEMACTIONCOOLTIME_CMD = 0x4034,
    NC_CHARSAVE_USEITEM_MINIMON_INFO_DB_CMD = 0x4035,
    NC_CHARSAVE_USEITEM_MINIMON_INFO_WORLD_CMD = 0x4036,
    NC_CHARSAVE_SELL_ITEM_INFO_CMD = 0x4037,

    NC_QUEST_NULL = 0x4400,
    NC_QUEST_SCRIPT_CMD_REQ = 0x4401,
    NC_QUEST_SCRIPT_CMD_ACK = 0x4402,
    NC_QUEST_DB_SET_INFO_REQ = 0x4403,
    NC_QUEST_DB_SET_INFO_ACK = 0x4404,
    NC_QUEST_DB_CLEAR_REQ = 0x4405,
    NC_QUEST_DB_CLEAR_ACK = 0x4406,
    NC_QUEST_GIVE_UP_REQ = 0x4407,
    NC_QUEST_GIVE_UP_ACK = 0x4408,
    NC_QUEST_DB_GIVE_UP_REQ = 0x4409,
    NC_QUEST_DB_GIVE_UP_ACK = 0x440A,
    NC_QUEST_CLIENT_SCENARIO_DONE_REQ = 0x440B,
    NC_QUEST_CLIENT_SCENARIO_DONE_ACK = 0x440C,
    NC_QUEST_NOTIFY_MOB_KILL_CMD = 0x440D,
    NC_QUEST_SCENARIO_RUN_CMD = 0x440E,
    NC_QUEST_SELECT_START_REQ = 0x440F,
    NC_QUEST_SELECT_START_ACK = 0x4410,
    NC_QUEST_REWARD_SELECT_ITEM_INDEX_CMD = 0x4411,
    NC_QUEST_REWARD_NEED_SELECT_ITEM_CMD = 0x4412,
    NC_QUEST_ERR = 0x4413,
    NC_QUEST_START_REQ = 0x4414,
    NC_QUEST_START_ACK = 0x4415,
    NC_QUEST_READ_REQ = 0x4416,
    NC_QUEST_READ_ACK = 0x4417,
    NC_QUEST_DB_READ_REQ = 0x4418,
    NC_QUEST_DB_READ_ACK = 0x4419,
    NC_QUEST_DB_DONE_REQ = 0x441A,
    NC_QUEST_DB_DONE_ACK = 0x441B,
    NC_QUEST_RESET_TIME_CMD = 0x441C,
    NC_QUEST_RESET_TIME_ZONE_CMD = 0x441D,
    NC_QUEST_RESET_TIME_CLIENT_CMD = 0x441E,
    NC_QUEST_JOBDUNGEON_FIND_RNG = 0x441F,
    NC_QUEST_JOBDUNGEON_LINK_FAIL_CMD = 0x4420,

    NC_SKILL_NULL = 0x4800,
    NC_SKILL_SKILLTEACH_REQ = 0x4801,
    NC_SKILL_SKILLTEACHSUC_ACK = 0x4802,
    NC_SKILL_SKILLTEACHFAIL_ACK = 0x4803,
    NC_SKILL_SKILL_LEARNSUC_CMD = 0x4804,
    NC_SKILL_SKILL_LEARNFAIL_CMD = 0x4805,
    NC_SKILL_SETABSTATE_CMD = 0x4806,
    NC_SKILL_SOMEONESETABSTATE_CMD = 0x4807,
    NC_SKILL_RESETABSTATE_CMD = 0x4808,
    NC_SKILL_SOMEONERESETABSTATE_CMD = 0x4809,
    NC_SKILL_EMPOW_RESET_REQ = 0x480A,
    NC_SKILL_EMPOW_RESET_DB_REQ = 0x480B,
    NC_SKILL_EMPOW_RESET_DB_FAIL_ACK = 0x480C,
    NC_SKILL_EMPOW_RESET_DB_SUC_ACK = 0x480D,
    NC_SKILL_EMPOW_RESET_FAIL_ACK = 0x480E,
    NC_SKILL_EMPOW_RESET_SUC_ACK = 0x480F,
    NC_SKILL_EMPOWPOINT_CMD = 0x4810,
    NC_SKILL_EMPOWALLOC_REQ = 0x4811,
    NC_SKILL_EMPOWALLOC_DB_REQ = 0x4812,
    NC_SKILL_EMPOWALLOC_DB_ACK = 0x4813,
    NC_SKILL_EMPOWALLOC_ACK = 0x4814,
    NC_SKILL_SKILLEXP_CLIENT_CMD = 0x481D,
    NC_SKILL_REVIVE_CMD = 0x481E,
    NC_SKILL_SOMEONEREVIVE_CMD = 0x481F,
    NC_SKILL_PASSIVESKILL_LEARN_CMD = 0x4820,
    NC_SKILL_COOLTIME_CMD = 0x4821,
    NC_SKILL_PRODUCTFIELD_REQ = 0x4822,
    NC_SKILL_PRODUCTFIELD_ACK = 0x4823,
    NC_SKILL_UNLEARN_REQ = 0x4824,
    NC_SKILL_ERASE_REQ = 0x4825,
    NC_SKILL_ERASE_ACK = 0x4826,
    NC_SKILL_UNLEARN_ACK = 0x4827,
    NC_SKILL_WARP_CMD = 0x4828,
    NC_SKILL_SOMEONEREVAVALTOME_CMD = 0x4829,
    NC_SKILL_REPLYREVIVE_CMD = 0x482A,
    NC_SKILL_REPLYREVIVEFAIL_CMD = 0x482B,
    NC_SKILL_ITEMACTIONCOOLTIME_CMD = 0x482C,
    NC_SKILL_JUMP_CMD = 0x482D,

    NC_TRADE_NULL = 0x4C00,
    NC_TRADE_PROPOSE_REQ = 0x4C01,
    NC_TRADE_PROPOSE_ASK_REQ = 0x4C02,
    NC_TRADE_PROPOSE_ASKNO_ACK = 0x4C03,
    NC_TRADE_PROPOSENO_ACK = 0x4C04,
    NC_TRADE_PROPOSE_ASKYES_ACK = 0x4C05,
    NC_TRADE_PROPOSEYES_ACK = 0x4C06,
    NC_TRADE_PROPOSE_CANCEL_CMD = 0x4C07,
    NC_TRADE_PROPOSE_CANCELED_CMD = 0x4C08,
    NC_TRADE_START_CMD = 0x4C09,
    NC_TRADE_CANCEL_REQ = 0x4C0A,
    NC_TRADE_CANCEL_ACK = 0x4C0B,
    NC_TRADE_CANCEL_CMD = 0x4C0C,
    NC_TRADE_UPBOARD_REQ = 0x4C0D,
    NC_TRADE_UPBOARDFAIL_ACK = 0x4C0E,
    NC_TRADE_UPBOARD_ACK = 0x4C0F,
    NC_TRADE_OPPOSITUPBOARD_CMD = 0x4C10,
    NC_TRADE_DOWNBOARD_REQ = 0x4C11,
    NC_TRADE_DOWNBOARDFAIL_ACK = 0x4C12,
    NC_TRADE_DOWNBOARD_ACK = 0x4C13,
    NC_TRADE_OPPOSITDOWNBOARD_CMD = 0x4C14,
    NC_TRADE_CENBOARDING_REQ = 0x4C15,
    NC_TRADE_CENBOARDINGFAIL_ACK = 0x4C16,
    NC_TRADE_CENBOARDING_ACK = 0x4C17,
    NC_TRADE_OPPOSITCENBOARDING_CMD = 0x4C18,
    NC_TRADE_BOARDLOCK_REQ = 0x4C19,
    NC_TRADE_BOARDLOCKFAIL_ACK = 0x4C1A,
    NC_TRADE_BOARDLOCK_ACK = 0x4C1B,
    NC_TRADE_OPPOSITBOARDLOCK_CMD = 0x4C1C,
    NC_TRADE_BOARDUNLOCK_CMD = 0x4C1D,
    NC_TRADE_OPPOSITBOARDUNLOCK_CMD = 0x4C1E,
    NC_TRADE_DECIDE_REQ = 0x4C1F,
    NC_TRADE_DECIDEFAIL_ACK = 0x4C20,
    NC_TRADE_DECIDE_ACK = 0x4C21,
    NC_TRADE_OPPOSITDECIDE_CMD = 0x4C22,
    NC_TRADE_TRADEFAIL_CMD = 0x4C23,
    NC_TRADE_TRADECOMPLETE_CMD = 0x4C24,

    NC_SOULSTONE_NULL = 0x5000,
    NC_SOULSTONE_HP_BUY_REQ = 0x5001,
    NC_SOULSTONE_SP_BUY_REQ = 0x5002,
    NC_SOULSTONE_HP_BUY_ACK = 0x5003,
    NC_SOULSTONE_SP_BUY_ACK = 0x5004,
    NC_SOULSTONE_BUYFAIL_ACK = 0x5005,
    NC_SOULSTONE_USEFAIL_ACK = 0x5006,
    NC_SOULSTONE_HP_USE_REQ = 0x5007,
    NC_SOULSTONE_HP_USESUC_ACK = 0x5008,
    NC_SOULSTONE_SP_USE_REQ = 0x5009,
    NC_SOULSTONE_SP_USESUC_ACK = 0x500A,
    NC_SOULSTONE_HP_SOMEONEUSE_CMD = 0x500B,
    NC_SOULSTONE_SP_SOMEONEUSE_CMD = 0x500C,

    NC_FRIEND_NULL = 0x5400,
    NC_FRIEND_SET_REQ = 0x5401,
    NC_FRIEND_SET_ACK = 0x5402,
    NC_FRIEND_SET_CONFIRM_REQ = 0x5403,
    NC_FRIEND_SET_CONFIRM_ACK = 0x5404,
    NC_FRIEND_DEL_REQ = 0x5405,
    NC_FRIEND_DEL_ACK = 0x5406,
    NC_FRIEND_LIST_CMD = 0x5407,
    NC_FRIEND_ADD_CMD = 0x5408,
    NC_FRIEND_LOGIN_CMD = 0x5409,
    NC_FRIEND_LOGOUT_CMD = 0x540A,
    NC_FRIEND_REFUSE_CMD = 0x540B,
    NC_FRIEND_DEL_CMD = 0x540C,
    NC_FRIEND_MAP_CMD = 0x540D,
    NC_FRIEND_PARTY_CMD = 0x540E,
    NC_FRIEND_LEVEL_CMD = 0x540F,
    NC_FRIEND_DB_SET_REQ = 0x5410,
    NC_FRIEND_DB_SET_ACK = 0x5411,
    NC_FRIEND_DB_DEL_REQ = 0x5412,
    NC_FRIEND_DB_DEL_ACK = 0x5413,
    NC_FRIEND_DB_GET_REQ = 0x5414,
    NC_FRIEND_DB_GET_ACK = 0x5415,
    NC_FRIEND_CLASS_CHANGE_CMD = 0x5418,
    NC_FRIEND_DB_POINT_CMD = 0x541C,
    NC_FRIEND_POINT_REQ = 0x541D,
    NC_FRIEND_POINT_ACK = 0x541E,
    NC_FRIEND_FIND_FRIENDS_REQ = 0x541F,
    NC_FRIEND_FIND_FRIENDS_ACK = 0x5420,
    NC_FRIEND_UES_FRIEND_POINT_REQ = 0x5421,
    NC_FRIEND_UES_FRIEND_POINT_ACK = 0x5422,
    NC_FRIEND_SOMEONE_GET_SPECIALITEM_ZONE_CMD = 0x5423,
    NC_FRIEND_SOMEONE_GET_SPECIALITEM_WORLD_CMD = 0x5424,
    NC_FRIEND_GET_DIFF_FRIEND_POINT_CMD = 0x5425,

    NC_KQ_NULL = 0x5800,
    NC_KQ_LIST_REQ = 0x5801,
    NC_KQ_LIST_ACK = 0x5802,
    NC_KQ_STATUS_REQ = 0x5803,
    NC_KQ_STATUS_ACK = 0x5804,
    NC_KQ_JOIN_REQ = 0x5805,
    NC_KQ_JOIN_ACK = 0x5806,
    NC_KQ_JOIN_CANCEL_REQ = 0x5807,
    NC_KQ_JOIN_CANCEL_ACK = 0x5808,
    NC_KQ_SCHEDULE_REQ = 0x5809,
    NC_KQ_SCHEDULE_ACK = 0x580A,
    NC_KQ_NOTIFY_CMD = 0x580B,
    NC_KQ_START_CMD = 0x580C,
    NC_KQ_W2Z_MAKE_REQ = 0x580D,
    NC_KQ_Z2W_MAKE_ACK = 0x580E,
    NC_KQ_W2Z_START_CMD = 0x580F,
    NC_KQ_Z2W_END_CMD = 0x5810,
    NC_KQ_W2Z_DESTROY_CMD = 0x5811,
    NC_KQ_COMPLETE_CMD = 0x5812,
    NC_KQ_FAIL_CMD = 0x5813,
    NC_KQ_SCORE_CMD = 0x5814,
    NC_KQ_REWARD_REQ = 0x5815,
    NC_KQ_REWARDSUC_ACK = 0x5816,
    NC_KQ_REWARDFAIL_ACK = 0x5817,
    NC_KQ_RESTDEADNUM_CMD = 0x5818,
    NC_KQ_ENTRYRESPONCE_REQ = 0x5819,
    NC_KQ_ENTRYRESPONCE_ACK = 0x581A,
    NC_KQ_LIST_REFRESH_REQ = 0x581B,
    NC_KQ_LIST_TIME_ACK = 0x581C,
    NC_KQ_LIST_ADD_ACK = 0x581D,
    NC_KQ_LIST_DELETE_ACK = 0x581E,
    NC_KQ_LIST_UPDATE_ACK = 0x581F,
    NC_KQ_SCORE_SIMPLE_CMD = 0x5821,
    NC_KQ_MOBKILLNUMBER_CMD = 0x5822,
    NC_KQ_NOREWARD_CMD = 0x5823,
    NC_KQ_JOINING_ALARM_CMD = 0x5824,
    NC_KQ_JOINING_ALARM_END_CMD = 0x5825,
    NC_KQ_JOINING_ALARM_LIST = 0x5826,
    NC_KQ_VOTE_START_REQ = 0x5827,
    NC_KQ_VOTE_START_ACK = 0x5828,
    NC_KQ_VOTE_VOTING_CMD = 0x5829,
    NC_KQ_VOTE_VOTING_REQ = 0x582A,
    NC_KQ_VOTE_VOTING_ACK = 0x582B,
    NC_KQ_VOTE_RESULT_SUC_CMD = 0x582C,
    NC_KQ_VOTE_RESULT_FAIL_CMD = 0x582D,
    NC_KQ_VOTE_CANCEL_CMD = 0x582E,
    NC_KQ_VOTE_BAN_MSG_CMD = 0x582F,
    NC_KQ_VOTE_BAN_MSG_LOGOFF_CMD = 0x5830,
    NC_KQ_JOIN_LIST_REQ = 0x5831,
    NC_KQ_JOIN_LIST_ACK = 0x5832,
    NC_KQ_LINK_TO_FORCE_BY_BAN_CMD = 0x5833,
    NC_KQ_VOTE_START_CHECK_REQ = 0x5834,
    NC_KQ_VOTE_START_CHECK_ACK = 0x5835,
    NC_KQ_SCORE_INFO_CMD = 0x5836,
    NC_KQ_TEAM_SELECT_REQ = 0x5837,
    NC_KQ_TEAM_SELECT_ACK = 0x5838,
    NC_KQ_TEAM_SELECT_CMD = 0x5839,
    NC_KQ_TEAM_TYPE_CMD = 0x583A,
    NC_KQ_PLAYER_DISJOIN_CMD = 0x583B,
    NC_KQ_SCORE_BOARD_INFO_CMD = 0x583C,
    NC_KQ_WINTER_EVENT_2014_SCORE_CMD = 0x583D,

    NC_WT_NULL = 0x5C00,
    NC_WT_LICENSE_REQ = 0x5C01,
    NC_WT_LICENSE_ACK = 0x5C02,
    NC_WT_GRADE_CMD = 0x5C03,
    NC_WT_TITLE_CMD = 0x5C04,
    NC_WT_LICENSE_SET_REQ = 0x5C05,
    NC_WT_LICENSE_SET_ACK = 0x5C06,
    NC_WT_LICENSE_CLR_REQ = 0x5C07,
    NC_WT_LICENSE_CLR_ACK = 0x5C08,
    NC_WT_MOB_KILLCOUNT_SET_REQ = 0x5C09,
    NC_WT_MOB_KILLCOUNT_SET_ACK = 0x5C0A,
    NC_WT_TITLE_SET_REQ = 0x5C0B,
    NC_WT_TITLE_SET_ACK = 0x5C0C,
    NC_WT_MOBINC_CMD = 0x5C0D,

    NC_CT_NULL = 0x6000,
    NC_CT_SET_CURRENT_REQ = 0x6001,
    NC_CT_SET_CURRENT_ACK = 0x6002,
    NC_CT_SET_SOMEONECHANGE_CMD = 0x6003,
    NC_CT_SET_CMD = 0x6004,
    NC_CT_DB_SET_CMD = 0x6005,
    NC_CT_CHARTTING_CMD = 0x6006,
    NC_CT_ADD_FRIEND_CMD = 0x6007,
    NC_CT_SET_CURRENT_DB_CMD = 0x6008,
    NC_CT_LUASCRIPT_SET_WORLD_CMD = 0x6009,
    NC_CT_LUASCRIPT_SET_ZONE_CMD = 0x600A,

    NC_ANNOUNCE_NULL = 0x6400,
    NC_ANNOUNCE_Z2W_CMD = 0x6401,
    NC_ANNOUNCE_W2C_CMD = 0x6402,

    NC_BOOTH_NULL = 0x6800,
    NC_BOOTH_OPEN_REQ = 0x6801,
    NC_BOOTH_OPEN_ACK = 0x6802,
    NC_BOOTH_SOMEONEOPEN_CMD = 0x6803,
    NC_BOOTH_CLOSE_REQ = 0x6804,
    NC_BOOTH_CLOSE_ACK = 0x6805,
    NC_BOOTH_SOMEONECLOSE_CMD = 0x6806,
    NC_BOOTH_ENTRY_REQ = 0x6807,
    NC_BOOTH_ENTRY_SELL_ACK = 0x6808,
    NC_BOOTH_ENTRY_BUY_ACK = 0x6809,
    NC_BOOTH_REFRESH_REQ = 0x680A,
    NC_BOOTH_REFRESH_SELL_ACK = 0x680B,
    NC_BOOTH_REFRESH_BUY_ACK = 0x680C,
    NC_BOOTH_ITEMTRADE_REQ = 0x680D,
    NC_BOOTH_ITEMTRADE_ACK = 0x680E,
    NC_BOOTH_BUYREFRESH_CMD = 0x680F,
    NC_BOOTH_INTERIORSTART_REQ = 0x6810,
    NC_BOOTH_INTERIORSTART_ACK = 0x6811,
    NC_BOOTH_SOMEONEINTERIORSTART_CMD = 0x6812,
    NC_BOOTH_SEARCH_ITEM_LIST_CATEGORIZED_REQ = 0x6813,
    NC_BOOTH_SEARCH_ITEM_LIST_CATEGORIZED_ACK = 0x6814,
    NC_BOOTH_SEARCH_BOOTH_POSITION_REQ = 0x6815,
    NC_BOOTH_SEARCH_BOOTH_POSITION_ACK = 0x6816,
    NC_BOOTH_SEARCH_BOOTH_CLOSED_CMD = 0x6817,

    NC_SCENARIO_NULL = 0x6C00,
    NC_SCENARIO_RUNEFFECT_CMD = 0x6C01,
    NC_SCENARIO_ANIMATION_CMD = 0x6C02,
    NC_SCENARIO_MESSAGENPC_CMD = 0x6C03,
    NC_SCENARIO_MESSAGENOTICE_CMD = 0x6C04,
    NC_SCENARIO_AREAENTRY_REQ = 0x6C05,
    NC_SCENARIO_AREAENTRY_ACK = 0x6C06,
    NC_SCENARIO_AREALEAVE_REQ = 0x6C07,
    NC_SCENARIO_AREALEAVE_ACK = 0x6C08,
    NC_SCENARIO_DOORSTATE_CMD = 0x6C09,
    NC_SCENARIO_LIGHT_CMD = 0x6C0A,
    NC_SCENARIO_OBJTYPECHANGE_CMD = 0x6C0B,
    NC_SCENARIO_CHATWIN_CMD = 0x6C0C,
    NC_SCENARIO_ANIMATE_CMD = 0x6C0D,
    NC_SCENARIO_FOG_CMD = 0x6C0E,
    NC_SCENARIO_PLAYERLIKEMOB_ANIMATE_CMD = 0x6C0F,
    NC_SCENARIO_BRIEFEFFECT_CMD = 0x6C10,
    NC_SCENARIO_NPCCHAT_CMD = 0x6C11,
    NC_SCENARIO_MESSAGE_CMD = 0x6C12,
    NC_SCENARIO_CAMERA_MOVE_CMD = 0x6C14,
    NC_SCENARIO_SCRIPTMESSAGE_CMD = 0x6C15,
    NC_SCENARIO_TIMER_CMD = 0x6C16,
    NC_SCENARIO_MAPMARK_CMD = 0x6C17,
    NC_SCENARIO_MAP_OBJECT_CONTROL_CMD = 0x6C18,
    NC_SCENARIO_DIALOG_CMD = 0x6C19,
    NC_SCENARIO_TOPVIEW_CMD = 0x6C1A,
    NC_SCENARIO_SYSTEM_MESSAGE_CMD = 0x6C1B,
    NC_SCENARIO_HIDE_OTHER_PLAYER_CMD = 0x6C1C,
    NC_SCENARIO_EFFECT_TIMER_CMD = 0x6C1D,
    NC_SCENARIO_DIRECTIONAL_ARROW_CMD = 0x6C1E,
    NC_SCENARIO_DEL_DIRECTIONAL_ARROW_CMD = 0x6C1F,
    NC_SCENARIO_RANKING_LIST_CMD = 0x6C20,
    NC_SCENARIO_TIMER_START_CMD = 0x6C21,
    NC_SCENARIO_TIMER_END_CMD = 0x6C22,

    NC_CHAR_OPTION_NULL = 0x7000,
    NC_CHAR_OPTION_GET_ALL_REQ = 0x7001,
    NC_CHAR_OPTION_GET_SHORTCUTDATA_REQ = 0x7002,
    NC_CHAR_OPTION_GET_SHORTCUTDATA_ACK = 0x7003,
    NC_CHAR_OPTION_GET_SHORTCUTSIZE_REQ = 0x7004,
    NC_CHAR_OPTION_GET_SHORTCUTSIZE_ACK = 0x7005,
    NC_CHAR_OPTION_GET_VIDEO_REQ = 0x7006,
    NC_CHAR_OPTION_GET_VIDEO_ACK = 0x7007,
    NC_CHAR_OPTION_GET_SOUND_REQ = 0x7008,
    NC_CHAR_OPTION_GET_SOUND_ACK = 0x7009,
    NC_CHAR_OPTION_GET_GAME_REQ = 0x700A,
    NC_CHAR_OPTION_GET_GAME_ACK = 0x700B,
    NC_CHAR_OPTION_GET_WINDOWPOS_REQ = 0x700C,
    NC_CHAR_OPTION_GET_WINDOWPOS_ACK = 0x700D,
    NC_CHAR_OPTION_GET_KEYMAPPING_REQ = 0x700E,
    NC_CHAR_OPTION_GET_KEYMAPPING_ACK = 0x700F,
    NC_CHAR_OPTION_SET_SHORTCUTDATA_CMD = 0x7010,
    NC_CHAR_OPTION_SET_SHORTCUTSIZE_CMD = 0x7011,
    NC_CHAR_OPTION_SET_VIDEO_CMD = 0x7012,
    NC_CHAR_OPTION_SET_SOUND_CMD = 0x7013,
    NC_CHAR_OPTION_SET_GAME_CMD = 0x7014,
    NC_CHAR_OPTION_SET_WINDOWPOS_CMD = 0x7015,
    NC_CHAR_OPTION_SET_KEYMAPPING_CMD = 0x7016,
    NC_CHAR_OPTION_DB_GET_SHORTCUTDATA_REQ = 0x7017,
    NC_CHAR_OPTION_DB_GET_SHORTCUTDATA_ACK = 0x7018,
    NC_CHAR_OPTION_DB_GET_SHORTCUTSIZE_REQ = 0x7019,
    NC_CHAR_OPTION_DB_GET_SHORTCUTSIZE_ACK = 0x701A,
    NC_CHAR_OPTION_DB_GET_VIDEO_REQ = 0x701B,
    NC_CHAR_OPTION_DB_GET_VIDEO_ACK = 0x701C,
    NC_CHAR_OPTION_DB_GET_SOUND_REQ = 0x701D,
    NC_CHAR_OPTION_DB_GET_SOUND_ACK = 0x701E,
    NC_CHAR_OPTION_DB_GET_GAME_REQ = 0x701F,
    NC_CHAR_OPTION_DB_GET_GAME_ACK = 0x7020,
    NC_CHAR_OPTION_DB_GET_WINDOWPOS_REQ = 0x7021,
    NC_CHAR_OPTION_DB_GET_WINDOWPOS_ACK = 0x7022,
    NC_CHAR_OPTION_DB_GET_KEYMAPPING_REQ = 0x7023,
    NC_CHAR_OPTION_DB_GET_KEYMAPPING_ACK = 0x7024,
    NC_CHAR_OPTION_DB_SET_SHORTCUTDATA_CMD = 0x7025,
    NC_CHAR_OPTION_DB_SET_SHORTCUTSIZE_CMD = 0x7026,
    NC_CHAR_OPTION_DB_SET_VIDEO_CMD = 0x7027,
    NC_CHAR_OPTION_DB_SET_SOUND_CMD = 0x7028,
    NC_CHAR_OPTION_DB_SET_GAME_CMD = 0x7029,
    NC_CHAR_OPTION_DB_SET_WINDOWPOS_CMD = 0x702A,
    NC_CHAR_OPTION_DB_SET_KEYMAPPING_CMD = 0x702B,
    NC_CHAR_OPTION_IMPROVE_DB_GET_DATA_TYPE_CMD = 0x702C,
    NC_CHAR_OPTION_IMPROVE_DB_GET_SHORTCUTDATA_CMD = 0x702D,
    NC_CHAR_OPTION_IMPROVE_DB_GET_KEYMAP_CMD = 0x702E,
    NC_CHAR_OPTION_IMPROVE_DB_GET_GAMEOPTION_CMD = 0x702F,
    NC_CHAR_OPTION_IMPROVE_DB_GET_ETC3_CMD = 0x7030,
    NC_CHAR_OPTION_IMPROVE_DB_GET_ETC4_CMD = 0x7031,
    NC_CHAR_OPTION_IMPROVE_GET_SHORTCUTDATA_CMD = 0x7032,
    NC_CHAR_OPTION_IMPROVE_GET_KEYMAP_CMD = 0x7033,
    NC_CHAR_OPTION_IMPROVE_GET_GAMEOPTION_CMD = 0x7034,
    NC_CHAR_OPTION_IMPROVE_GET_ETC3_CMD = 0x7035,
    NC_CHAR_OPTION_IMPROVE_GET_ETC4_CMD = 0x7036,
    NC_CHAR_OPTION_IMPROVE_SET_SHORTCUTDATA_REQ = 0x7037,
    NC_CHAR_OPTION_IMPROVE_SET_SHORTCUTDATA_ACK = 0x7038,
    NC_CHAR_OPTION_IMPROVE_SET_KEYMAP_REQ = 0x7039,
    NC_CHAR_OPTION_IMPROVE_SET_KEYMAP_ACK = 0x703A,
    NC_CHAR_OPTION_IMPROVE_SET_GAMEOPTION_REQ = 0x703B,
    NC_CHAR_OPTION_IMPROVE_SET_GAMEOPTION_ACK = 0x703C,
    NC_CHAR_OPTION_IMPROVE_SET_ETC3_REQ = 0x703D,
    NC_CHAR_OPTION_IMPROVE_SET_ETC3_ACK = 0x703E,
    NC_CHAR_OPTION_IMPROVE_SET_ETC4_REQ = 0x703F,
    NC_CHAR_OPTION_IMPROVE_SET_ETC4_ACK = 0x7040,
    NC_CHAR_OPTION_IMPROVE_INIT_SHORTCUTDATA_REQ = 0x7041,
    NC_CHAR_OPTION_IMPROVE_INIT_SHORTCUTDATA_ACK = 0x7042,
    NC_CHAR_OPTION_IMPROVE_INIT_KEYMAP_REQ = 0x7043,
    NC_CHAR_OPTION_IMPROVE_INIT_KEYMAP_ACK = 0x7044,
    NC_CHAR_OPTION_IMPROVE_INIT_GAMEOPTION_REQ = 0x7045,
    NC_CHAR_OPTION_IMPROVE_INIT_GAMEOPTION_ACK = 0x7046,
    NC_CHAR_OPTION_IMPROVE_INIT_ETC3_REQ = 0x7047,
    NC_CHAR_OPTION_IMPROVE_INIT_ETC3_ACK = 0x7048,
    NC_CHAR_OPTION_IMPROVE_INIT_ETC4_REQ = 0x7049,
    NC_CHAR_OPTION_IMPROVE_INIT_ETC4_ACK = 0x704A,
    NC_CHAR_OPTION_IMPROVE_DB_SET_SHORTCUTDATA_REQ = 0x704B,
    NC_CHAR_OPTION_IMPROVE_DB_SET_SHORTCUTDATA_ACK = 0x704C,
    NC_CHAR_OPTION_IMPROVE_DB_SET_KEYMAP_REQ = 0x704D,
    NC_CHAR_OPTION_IMPROVE_DB_SET_KEYMAP_ACK = 0x704E,
    NC_CHAR_OPTION_IMPROVE_DB_SET_GAMEOPTION_REQ = 0x704F,
    NC_CHAR_OPTION_IMPROVE_DB_SET_GAMEOPTION_ACK = 0x7050,
    NC_CHAR_OPTION_IMPROVE_DB_SET_ETC3_REQ = 0x7051,
    NC_CHAR_OPTION_IMPROVE_DB_SET_ETC3_ACK = 0x7052,
    NC_CHAR_OPTION_IMPROVE_DB_SET_ETC4_REQ = 0x7053,
    NC_CHAR_OPTION_IMPROVE_DB_SET_ETC4_ACK = 0x7054,
    NC_CHAR_OPTION_IMPROVE_DB_INIT_SHORTCUTDATA_REQ = 0x7055,
    NC_CHAR_OPTION_IMPROVE_DB_INIT_SHORTCUTDATA_ACK = 0x7056,
    NC_CHAR_OPTION_IMPROVE_DB_INIT_KEYMAP_REQ = 0x7057,
    NC_CHAR_OPTION_IMPROVE_DB_INIT_KEYMAP_ACK = 0x7058,
    NC_CHAR_OPTION_IMPROVE_DB_INIT_GAMEOPTION_REQ = 0x7059,
    NC_CHAR_OPTION_IMPROVE_DB_INIT_GAMEOPTION_ACK = 0x705A,
    NC_CHAR_OPTION_IMPROVE_DB_INIT_ETC3_REQ = 0x705B,
    NC_CHAR_OPTION_IMPROVE_DB_INIT_ETC3_ACK = 0x705C,
    NC_CHAR_OPTION_IMPROVE_DB_INIT_ETC4_REQ = 0x705D,
    NC_CHAR_OPTION_IMPROVE_DB_INIT_ETC4_ACK = 0x705E,
    NC_CHAR_OPTION_LOGIN_BLOCKDATA_ERR = 0x705F,
    NC_CHAR_OPTION_LOGIN_BLOCKDATA_ERR_REQ = 0x7060,

    NC_GUILD_NULL = 0x7400,
    NC_GUILD_INFO_REQ = 0x7401,
    NC_GUILD_INFO_ACK = 0x7402,
    NC_GUILD_LIST_REQ = 0x7403,
    NC_GUILD_LIST_ACK = 0x7404,
    NC_GUILD_MAKE_REQ = 0x7405,
    NC_GUILD_MAKE_ACK = 0x7406,
    NC_GUILD_DISMISS_REQ = 0x7407,
    NC_GUILD_DISMISS_ACK = 0x7408,
    NC_GUILD_MEMBER_INVITE_REQ = 0x7409,
    NC_GUILD_MEMBER_INVITE_ACK = 0x740A,
    NC_GUILD_MEMBER_JOIN_REQ = 0x740B,
    NC_GUILD_MEMBER_JOIN_ACK = 0x740C,
    NC_GUILD_MEMBER_JOIN_ERR = 0x740D,
    NC_GUILD_MEMBER_VANISH_REQ = 0x740E,
    NC_GUILD_MEMBER_VANISH_ACK = 0x740F,
    NC_GUILD_NOTIFY_REQ = 0x7410,
    NC_GUILD_NOTIFY_ACK = 0x7411,
    NC_GUILD_MONEY_SUB_REQ = 0x7412,
    NC_GUILD_MONEY_SUB_ACK = 0x7413,
    NC_GUILD_GRADE_REQ = 0x7414,
    NC_GUILD_GRADE_ACK = 0x7415,
    NC_GUILD_MEMBER_GRADE_REQ = 0x7416,
    NC_GUILD_MEMBER_GRADE_ACK = 0x7417,
    NC_GUILD_MY_GUILD_INFO_REQ = 0x7418,
    NC_GUILD_MY_GUILD_INFO_ACK = 0x7419,
    NC_GUILD_MEMBER_LIST_REQ = 0x741A,
    NC_GUILD_MEMBER_LIST_ACK = 0x741B,
    NC_GUILD_MEMBER_LEAVE_REQ = 0x741C,
    NC_GUILD_MEMBER_LEAVE_ACK = 0x741D,
    NC_GUILD_MONEY_ADD_REQ = 0x741E,
    NC_GUILD_MONEY_ADD_ACK = 0x741F,
    NC_GUILD_MEMBER_INTRO_REQ = 0x7420,
    NC_GUILD_MEMBER_INTRO_ACK = 0x7421,
    NC_GUILD_WAR_REQ = 0x7422,
    NC_GUILD_WAR_ACK = 0x7423,
    NC_GUILD_WAR_ABLE_LIST_REQ = 0x7424,
    NC_GUILD_WAR_ABLE_LIST_ACK = 0x7425,
    NC_GUILD_WAR_LIST_REQ = 0x7426,
    NC_GUILD_WAR_LIST_ACK = 0x7427,
    NC_GUILD_WAR_SCORE_REQ = 0x7428,
    NC_GUILD_WAR_SCORE_ACK = 0x7429,
    NC_GUILD_WAR_SCORE_CMD = 0x742A,
    NC_GUILD_MONEY_ADD_CMD = 0x742B,
    NC_GUILD_MONEY_SUB_CMD = 0x742C,
    NC_GUILD_NOTIFY_CMD = 0x742D,
    NC_GUILD_GRADE_CMD = 0x742E,
    NC_GUILD_DISMISS_CMD = 0x742F,
    NC_GUILD_DELETE_CMD = 0x7430,
    NC_GUILD_WAR_DECLARATION_CMD = 0x7431,
    NC_GUILD_WAR_TARGET_CMD = 0x7432,
    NC_GUILD_WAR_START_CMD = 0x7433,
    NC_GUILD_WAR_END_CMD = 0x7434,
    NC_GUILD_WAR_COOLDOWN_DONE_CMD = 0x7435,
    NC_GUILD_MEMBER_JOIN_CMD = 0x7436,
    NC_GUILD_MEMBER_VANISH_CMD = 0x7437,
    NC_GUILD_MEMBER_LEAVE_CMD = 0x7438,
    NC_GUILD_MEMBER_GRADE_CMD = 0x7439,
    NC_GUILD_MEMBER_FLAGS_CMD = 0x743A,
    NC_GUILD_MEMBER_EXP_RATIO_CMD = 0x743B,
    NC_GUILD_MEMBER_INTRO_CMD = 0x743C,
    NC_GUILD_MEMBER_LOGON_CMD = 0x743D,
    NC_GUILD_MEMBER_LOGOFF_CMD = 0x743E,
    NC_GUILD_MEMBER_PARTY_CMD = 0x743F,
    NC_GUILD_MEMBER_LEVEL_CMD = 0x7440,
    NC_GUILD_MEMBER_MAP_CMD = 0x7441,
    NC_GUILD_MEMBER_CLASS_CMD = 0x7442,
    NC_GUILD_ZONE_WAR_START_CMD = 0x7443,
    NC_GUILD_ZONE_WAR_END_CMD = 0x7444,
    NC_GUILD_ZONE_WAR_KILL_CMD = 0x7445,
    NC_GUILD_ZONE_LIST_REQ = 0x7446,
    NC_GUILD_ZONE_LIST_ACK = 0x7447,
    NC_GUILD_ZONE_MAKE_CMD = 0x7448,
    NC_GUILD_ZONE_DELETE_CMD = 0x7449,
    NC_GUILD_ZONE_MEMBER_JOIN_CMD = 0x744A,
    NC_GUILD_ZONE_MEMBER_LEAVE_CMD = 0x744B,
    NC_GUILD_ZONE_MONEY_CMD = 0x744C,
    NC_GUILD_ZONE_TYPE_CMD = 0x744D,
    NC_GUILD_ZONE_GRADE_CMD = 0x744E,
    NC_GUILD_ZONE_FAME_CMD = 0x744F,
    NC_GUILD_ZONE_STONE_LEVEL_CMD = 0x7450,
    NC_GUILD_ZONE_EXP_CMD = 0x7451,
    NC_GUILD_DB_REQ = 0x7452,
    NC_GUILD_DB_ACK = 0x7453,
    NC_GUILD_DB_MEMBER_REQ = 0x7454,
    NC_GUILD_DB_MEMBER_ACK = 0x7455,
    NC_GUILD_DB_ALL_REQ = 0x7456,
    NC_GUILD_DB_ALL_ACK = 0x7457,
    NC_GUILD_DB_MAKE_REQ = 0x7458,
    NC_GUILD_DB_MAKE_ACK = 0x7459,
    NC_GUILD_DB_DELETE_REQ = 0x745A,
    NC_GUILD_DB_DELETE_ACK = 0x745B,
    NC_GUILD_DB_DISMISS_REQ = 0x745C,
    NC_GUILD_DB_DISMISS_ACK = 0x745D,
    NC_GUILD_DB_MONEY_ADD_REQ = 0x745E,
    NC_GUILD_DB_MONEY_ADD_ACK = 0x745F,
    NC_GUILD_DB_MONEY_SUB_REQ = 0x7460,
    NC_GUILD_DB_MONEY_SUB_ACK = 0x7461,
    NC_GUILD_DB_NOTIFY_REQ = 0x7462,
    NC_GUILD_DB_NOTIFY_ACK = 0x7463,
    NC_GUILD_DB_INTRO_REQ = 0x7464,
    NC_GUILD_DB_INTRO_ACK = 0x7465,
    NC_GUILD_DB_WAR_REQ = 0x7466,
    NC_GUILD_DB_WAR_ACK = 0x7467,
    NC_GUILD_DB_RESULT_WRITE_CMD = 0x7468,
    NC_GUILD_DB_MEMBER_JOIN_REQ = 0x7469,
    NC_GUILD_DB_MEMBER_JOIN_ACK = 0x746A,
    NC_GUILD_DB_MEMBER_LEAVE_REQ = 0x746B,
    NC_GUILD_DB_MEMBER_LEAVE_ACK = 0x746C,
    NC_GUILD_DB_MEMBER_INTRO_REQ = 0x746D,
    NC_GUILD_DB_MEMBER_INTRO_ACK = 0x746E,
    NC_GUILD_DB_MEMBER_GRADE_REQ = 0x746F,
    NC_GUILD_DB_MEMBER_GRADE_ACK = 0x7470,
    NC_GUILD_DB_MEMBER_VANISH_REQ = 0x7471,
    NC_GUILD_DB_MEMBER_VANISH_ACK = 0x7472,
    NC_GUILD_CHAT_REQ = 0x7473,
    NC_GUILD_CHAT_CMD = 0x7474,
    NC_GUILD_CHAT_ACK = 0x7475,
    NC_GUILD_NAME_REQ = 0x7476,
    NC_GUILD_NAME_ACK = 0x7477,
    NC_GUILD_GUILDWARCONFIRM_REQ = 0x7478,
    NC_GUILD_GUILDWARCONFIRM_ACK = 0x7479,
    NC_GUILD_TOURNAMENT_JOIN_REQ = 0x747A,
    NC_GUILD_TOURNAMENT_JOIN_ACK = 0x747B,
    NC_GUILD_TOURNAMENT_LEAVE_REQ = 0x747C,
    NC_GUILD_TOURNAMENT_LEAVE_ACK = 0x747D,
    NC_GUILD_TOURNAMENT_LIST_REQ = 0x747E,
    NC_GUILD_TOURNAMENT_LIST_ACK = 0x747F,
    NC_GUILD_TOURNAMENT_TYPE_CMD = 0x7480,
    NC_GUILD_TOURNAMENT_START_CMD = 0x7481,
    NC_GUILD_TOURNAMENT_END_CMD = 0x7482,
    NC_GUILD_TOURNAMENTSTART_CMD = 0x7483,
    NC_GUILD_TOURNAMENTSTOP_CMD = 0x7484,
    NC_GUILD_TOURNAMENT_DB_GET_REQ = 0x7485,
    NC_GUILD_TOURNAMENT_DB_GET_ACK = 0x7486,
    NC_GUILD_TOURNAMENT_DB_SET_REQ = 0x7487,
    NC_GUILD_TOURNAMENT_DB_SET_ACK = 0x7488,
    NC_GUILD_TOURNAMENT_DB_JOIN_REQ = 0x7489,
    NC_GUILD_TOURNAMENT_DB_JOIN_ACK = 0x748A,
    NC_GUILD_TOURNAMENT_DB_SET_TYPE_REQ = 0x748B,
    NC_GUILD_TOURNAMENT_DB_SET_TYPE_ACK = 0x748C,
    NC_GUILD_MOBGUILD_CMD = 0x748D,
    NC_GUILD_TOURNAMENT_DB_SET_RESULT_REQ = 0x748E,
    NC_GUILD_TOURNAMENT_DB_SET_RESULT_ACK = 0x748F,
    NC_GUILD_TOURNAMENT_RESULT_CMD = 0x7490,
    NC_GUILD_STORAGEOPEN_REQ = 0x7491,
    NC_GUILD_STORAGEOPEN_ACK = 0x7492,
    NC_GUILD_STORAGEWITHDRAW_RNG = 0x7493,
    NC_GUILD_STORAGEWITHDRAW_CMD = 0x7494,
    NC_GUILD_GUILDWARSTATUS_REQ = 0x7495,
    NC_GUILD_GUILDWARSTATUS_ACK = 0x7496,
    NC_GUILD_TOURNAMENT_DB_SET_MATCH_REQ = 0x7497,
    NC_GUILD_TOURNAMENT_DB_SET_MATCH_ACK = 0x7498,
    NC_GUILD_TOURNAMENT_DB_SET_MATCH_TIME_REQ = 0x7499,
    NC_GUILD_TOURNAMENT_DB_SET_MATCH_TIME_ACK = 0x749A,
    NC_GUILD_TOURNAMENT_RECALL_ENTER_CMD = 0x749B,
    NC_GUILD_TOURNAMENT_RECALL_ENTER_REQ = 0x749C,
    NC_GUILD_TOURNAMENT_RECALL_ENTER_ACK = 0x749D,
    NC_GUILD_STORAGE_WITHDRAW_GRADE_REQ = 0x749E,
    NC_GUILD_STORAGE_WITHDRAW_GRADE_ACK = 0x749F,
    NC_ITEMDB_CLOSE_GUILD_STORAGE_CMD = 0x74A0,
    NC_GUILD_GRADE_GROWTH_REQ = 0x74A1,
    NC_GUILD_GRADE_GROWTH_ACK = 0x74A2,
    NC_GUILD_GRADE_GROWTH_DATA_REQ = 0x74A3,
    NC_GUILD_GRADE_GROWTH_DATA_ACK = 0x74A4,
    NC_GUILD_GRADE_GROWTH_ZONE_REQ = 0x74A5,
    NC_GUILD_GRADE_GROWTH_ZONE_ACK = 0x74A6,
    NC_GUILD_DB_GRADE_GROWTH_REQ = 0x74A7,
    NC_GUILD_DB_GRADE_GROWTH_ACK = 0x74A8,
    NC_GUILD_DATA_CHANGE_CMD = 0x74A9,
    NC_GUILD_TOURNAMENT_DB_REWARD_CREATE_REQ = 0x74AA,
    NC_GUILD_TOURNAMENT_DB_REWARD_CREATE_ACK = 0x74AB,
    NC_GUILD_RENAME_REQ = 0x74AC,
    NC_GUILD_RENAME_ACK = 0x74AD,
    NC_GUILD_RENAME_CMD = 0x74AE,
    NC_GUILD_WORLD_RENAME_REQ = 0x74AF,
    NC_GUILD_WORLD_RENAME_ACK = 0x74B0,
    NC_GUILD_WORLD_RENAME_CMD = 0x74B1,
    NC_GUILD_DB_RENAME_REQ = 0x74B2,
    NC_GUILD_DB_RENAME_ACK = 0x74B3,
    NC_GUILD_RETYPE_REQ = 0x74B4,
    NC_GUILD_RETYPE_ACK = 0x74B5,
    NC_GUILD_RETYPE_CMD = 0x74B6,
    NC_GUILD_WORLD_RETYPE_REQ = 0x74B7,
    NC_GUILD_WORLD_RETYPE_ACK = 0x74B8,
    NC_GUILD_WORLD_RETYPE_CMD = 0x74B9,
    NC_GUILD_DB_RETYPE_REQ = 0x74BA,
    NC_GUILD_DB_RETYPE_ACK = 0x74BB,
    NC_GUILD_DB_TOKEN_ALL_REQ = 0x74BC,
    NC_GUILD_DB_TOKEN_ALL_ACK = 0x74BD,
    NC_GUILD_MY_GUILD_TOKEN_INFO_REQ = 0x74BE,
    NC_GUILD_MY_GUILD_TOKEN_INFO_ACK = 0x74BF,
    NC_GUILD_ZONE_USE_GUILD_TOKEN_CMD = 0x74C0,
    NC_GUILD_WORLD_USE_GUILD_TOKEN_CMD = 0x74C1,
    NC_GUILD_WORLD_SET_GUILD_TOKEN_CMD = 0x74C2,
    NC_GUILD_MY_GUILD_TOURNAMENT_MATCH_TIME_REQ = 0x74C3,
    NC_GUILD_MY_GUILD_TOURNAMENT_MATCH_TIME_ACK = 0x74C4,
    NC_GUILD_TOURNAMENT_LAST_WINNER_CMD = 0x74C5,
    NC_GUILD_TOURNAMENT_ZONE_MEMBERGRADE_REQ = 0x74C6,
    NC_GUILD_TOURNAMENT_ZONE_MEMBERGRADE_ACK = 0x74C7,
    NC_GUILD_TOURNAMENT_ZONE_FIGHTER_ENTER_CMD = 0x74C8,
    NC_GUILD_TOURNAMENT_ZONE_FIGHTER_OUT_CMD = 0x74C9,
    NC_GUILD_TOURNAMENT_FLAGCAPTURE_REQ = 0x74CA,
    NC_GUILD_TOURNAMENT_FLAGCAPTURE_ACK = 0x74CB,
    NC_GUILD_TOURNAMENT_FLAGCAPTURE_CMD = 0x74CC,
    NC_GUILD_TOURNAMENT_FLAGCAPTURE_RESULT_CMD = 0x74CD,
    NC_GUILD_TOURNAMENT_SKILLPOINT_CMD = 0x74CE,
    NC_GUILD_TOURNAMENT_USESKILL_REQ = 0x74CF,
    NC_GUILD_TOURNAMENT_USESKILL_ACK = 0x74D0,
    NC_GUILD_TOURNAMENT_USESKILL_CMD = 0x74D1,
    NC_GUILD_TOURNAMENT_DICEGAME_START_CMD = 0x74D2,
    NC_GUILD_TOURNAMENT_DICEGAME_THROW_REQ = 0x74D3,
    NC_GUILD_TOURNAMENT_DICEGAME_THROW_ACK = 0x74D4,
    NC_GUILD_TOURNAMENT_DICEGAME_THROW_CMD = 0x74D5,
    NC_GUILD_TOURNAMENT_DICEGAME_BEFORE_END_TIME_MSG_CMD = 0x74D6,
    NC_GUILD_TOURNAMENT_OBSERVER_ENTER_REQ = 0x74D7,
    NC_GUILD_TOURNAMENT_OBSERVER_ENTER_ACK = 0x74D8,
    NC_GUILD_TOURNAMENT_ZONE_OBSERVER_ENTER_REQ = 0x74D9,
    NC_GUILD_TOURNAMENT_ZONE_OBSERVER_ENTER_ACK = 0x74DA,
    NC_GUILD_TOURNAMENT_OBSERVER_OUT_REQ = 0x74DB,
    NC_GUILD_TOURNAMENT_OBSERVER_OUT_ACK = 0x74DC,
    NC_GUILD_TOURNAMENT_SCORE_CMD = 0x74DD,
    NC_GUILD_TOURNAMENT_PLAYERDIEMSG_CMD = 0x74DE,
    NC_GUILD_TOURNAMENT_PLAYERKILLMSG_CMD = 0x74DF,
    NC_GUILD_TOURNAMENT_STARTMSG_CMD = 0x74E0,
    NC_GUILD_TOURNAMENT_MANAGERUSERMSG_CMD = 0x74E1,
    NC_GUILD_TOURNAMENTSTOPMSG_CMD = 0x74E2,
    NC_GUILD_TOURNAMENT_ZONE_JOIN_NEW_REQ = 0x74E3,
    NC_GUILD_TOURNAMENT_ZONE_JOIN_NEW_ACK = 0x74E4,
    NC_GUILD_TOURNAMENT_DB_JOIN_NEW_REQ = 0x74E5,
    NC_GUILD_TOURNAMENT_DB_JOIN_NEW_ACK = 0x74E6,
    NC_GUILD_TOURNAMENT_DB_FINAL_SELECTION_REQ = 0x74E7,
    NC_GUILD_TOURNAMENT_DB_FINAL_SELECTION_ACK = 0x74E8,
    NC_GUILD_TOURNAMENT_JOIN_LIST_REQ = 0x74E9,
    NC_GUILD_TOURNAMENT_JOIN_LIST_ACK = 0x74EA,
    NC_GUILD_TOURNAMENT_DB_JOIN_LIST_REQ = 0x74EB,
    NC_GUILD_TOURNAMENT_DB_JOIN_LIST_ACK = 0x74EC,
    NC_GUILD_TOURNAMENT_NOTIFY_CMD = 0x74ED,
    NC_GUILD_DB_DELETE_CANCEL_REQ = 0x74EE,
    NC_GUILD_DB_DELETE_CANCEL_ACK = 0x74EF,
    NC_GUILD_TOURNAMENT_ITEM_PICK_CMD = 0x74F0,
    NC_GUILD_TOURNAMENT_ITEM_EFFECT_CMD = 0x74F1,
    NC_GUILD_TOURNAMENT_ITEM_FLAG_CMD = 0x74F2,
    NC_GUILD_TOURNAMENT_ITEM_SCAN_CMD = 0x74F3,
    NC_GUILD_TOURNAMENT_GOLD_REFUND_ZONE_CMD = 0x74F4,
    NC_GUILD_TOURNAMENT_GOLD_REFUND_CMD = 0x74F5,
    NC_GUILD_TOURNAMENT_ENTER_LIST_DB_GET_REQ = 0x74F6,
    NC_GUILD_TOURNAMENT_ENTER_LIST_DB_GET_ACK = 0x74F7,
    NC_GUILD_TOURNAMENT_REFUND_NOTICE_CMD = 0x74F8,
    NC_GUILD_TOURNAMENT_REFUND_NOTICE_DB_SET_REQ = 0x74F9,
    NC_GUILD_TOURNAMENT_REFUND_NOTICE_DB_SET_ACK = 0x74FA,
    NC_GUILD_HISTORY_LIST_REQ = 0x74FD,
    NC_GUILD_HISTORY_LIST_ACK = 0x74FE,
    NC_GUILD_HISTORY_DB_LIST_REQ = 0x74FF,
    NC_GUILD_HISTORY_DB_LIST_ACK = 0x7500,
    NC_GUILD_EMBLEM_CHECK_AVAILABILITY_REQ = 0x7501,
    NC_GUILD_EMBLEM_CHECK_AVAILABILITY_ACK = 0x7502,
    NC_GUILD_EMBLEM_INFO_DB_REQ = 0x7503,
    NC_GUILD_EMBLEM_INFO_DB_ACK = 0x7504,
    NC_GUILD_EMBLEM_SAVE_REQ = 0x7505,
    NC_GUILD_EMBLEM_SAVE_ACK = 0x7506,
    NC_GUILD_EMBLEM_SAVE_DB_REQ = 0x7507,
    NC_GUILD_EMBLEM_SAVE_DB_ACK = 0x7508,
    NC_GUILD_EMBLEM_OFF_MSG_CMD = 0x7509,
    NC_GUILD_EMBLEM_INFO_CMD = 0x750A,
    NC_GUILD_EMBLEM_INFO_NOTICE_CMD = 0x750B,
    NC_GUILD_EMBLEM_LEVELUP_CMD = 0x750C,
    NC_GUILD_EMBLEM_STATE_DB_REQ = 0x750D,
    NC_GUILD_EMBLEM_STATE_DB_ACK = 0x750E,

    NC_PRISON_NULL = 0x7C00,
    NC_PRISON_ADD_GM_REQ = 0x7C01,
    NC_PRISON_ADD_GM_ACK = 0x7C02,
    NC_PRISON_OK_CMD = 0x7C03,
    NC_PRISON_END_REQ = 0x7C04,
    NC_PRISON_END_ACK = 0x7C05,
    NC_PRISON_GET_REQ = 0x7C06,
    NC_PRISON_GET_ACK = 0x7C07,
    NC_PRISON_UNDOING_CMD = 0x7C08,
    NC_PRISON_ALTER_GM_REQ = 0x7C09,
    NC_PRISON_ALTER_GM_ACK = 0x7C0A,
    NC_DATA_PRISON_ADD_GM_REQ = 0x7C0B,
    NC_DATA_PRISON_ADD_GM_ACK = 0x7C0C,
    NC_DATA_PRISON_UPDATE_MIN_CMD = 0x7C0D,
    NC_DATA_PRISON_GET_REQ = 0x7C0E,
    NC_DATA_PRISON_GET_ACK = 0x7C0F,
    NC_DATA_PRISON_ALTER_GM_REQ = 0x7C10,
    NC_DATA_PRISON_ALTER_GM_ACK = 0x7C11,
    NC_ZONE_PRISON_END_CMD = 0x7C12,
    NC_ZONE_PRISON_GO_REQ = 0x7C13,
    NC_ZONE_PRISON_GO_ACK = 0x7C14,
    NC_PRISON_GIVE_UP_REQ = 0x7C15,
    NC_PRISON_GIVE_UP_FAIL_ACK = 0x7C16,
    NC_PRISON_ADD_REQ = 0x7C17,
    NC_PRISON_ADD_ACK = 0x7C18,

    NC_REPORT_NULL = 0x8000,
    NC_REPORT_ADD_REQ = 0x8001,
    NC_REPORT_ADD_ACK = 0x8002,
    NC_REPORT_CANCEL_REQ = 0x8003,
    NC_REPORT_CANCEL_ACK = 0x8004,
    NC_REPORT_GET_REQ = 0x8005,
    NC_REPORT_GET_ACK = 0x8006,
    NC_DATA_REPORT_ADD_REQ = 0x8007,
    NC_DATA_REPORT_ADD_ACK = 0x8008,
    NC_DATA_REPORT_CANCEL_REQ = 0x8009,
    NC_DATA_REPORT_CANCEL_ACK = 0x800A,
    NC_DATA_REPORT_GET_REQ = 0x800B,
    NC_DATA_REPORT_GET_ACK = 0x800C,

    NC_MINIHOUSE_NULL = 0x8C00,
    NC_MINIHOUSE_ACTIV_REQ = 0x8C01,
    NC_MINIHOUSE_ACTIV_ACK = 0x8C02,
    NC_MINIHOUSE_BUILDING_REQ = 0x8C03,
    NC_MINIHOUSE_BUILDING_ACK = 0x8C04,
    NC_MINIHOUSE_BUILDING_CMD = 0x8C05,
    NC_MINIHOUSE_FUNICHERINVEN_CMD = 0x8C08,
    NC_MINIHOUSE_FUNICHER_CMD = 0x8C09,
    NC_MINIHOUSE_LOGINCOMPLETE_REQ = 0x8C0A,
    NC_MINIHOUSE_LOGINCOMPLETE_ACK = 0x8C0B,
    NC_MINIHOUSE_LOGINCOMPLETE_CMD = 0x8C0C,
    NC_MINIHOUSE_LOGOUTCOMPLETE_CMD = 0x8C0D,
    NC_MINIHOUSE_VISITREADY_REQ = 0x8C0E,
    NC_MINIHOUSE_VISITREADY_ACK = 0x8C0F,
    NC_MINIHOUSE_VISIT_REQ = 0x8C10,
    NC_MINIHOUSE_VISIT_ACK = 0x8C11,
    NC_MINIHOUSE_KICKOUT_REQ = 0x8C12,
    NC_MINIHOUSE_KICKOUT_ACK = 0x8C13,
    NC_MINIHOUSE_KICKOUT_CMD = 0x8C14,
    NC_MINIHOUSE_KICKOUTCANCEL_REQ = 0x8C15,
    NC_MINIHOUSE_KICKOUTCANCEL_ACK = 0x8C16,
    NC_MINIHOUSE_KICKOUTCANCEL_CMD = 0x8C17,
    NC_MINIHOUSE_EXIT_REQ = 0x8C18,
    NC_MINIHOUSE_EXIT_ACK = 0x8C19,
    NC_MINIHOUSE_ARRANGEMODE_REQ = 0x8C1A,
    NC_MINIHOUSE_ARRANGEMODE_ACK = 0x8C1B,
    NC_MINIHOUSE_ARRANGEMODE_CMD = 0x8C1C,
    NC_MINIHOUSE_FUNITUREINFOCOMPLETE_REQ = 0x8C1D,
    NC_MINIHOUSE_FUNITUREINFOCOMPLETE_ACK = 0x8C1E,
    NC_MINIHOUSE_REARRANGE_REQ = 0x8C1F,
    NC_MINIHOUSE_REARRANGE_ACK = 0x8C20,
    NC_MINIHOUSE_REARRANGE_CMD = 0x8C21,
    NC_MINIHOUSE_CREATE_FURNITURE_REQ = 0x8C22,
    NC_MINIHOUSE_CREATE_FURNITURE_ACK = 0x8C23,
    NC_MINIHOUSE_CREATE_FURNITURE_CMD = 0x8C24,
    NC_MINIHOUSE_DELETE_FURNITURE_REQ = 0x8C25,
    NC_MINIHOUSE_DELETE_FURNITURE_ACK = 0x8C26,
    NC_MINIHOUSE_DELETE_FURNITURE_CMD = 0x8C27,
    NC_MINIHOUSE_COMPULSIONMOVETO_REQ = 0x8C28,
    NC_MINIHOUSE_COMPULSIONMOVETO_ACK = 0x8C29,
    NC_MINIHOUSE_COMPULSIONMOVETO_CMD = 0x8C2A,
    NC_MINIHOUSE_MODIFY_PASSWORD_REQ = 0x8C2B,
    NC_MINIHOUSE_MODIFY_PASSWORD_ACK = 0x8C2C,
    NC_MINIHOUSE_MODIFY_PASSWORD_CMD = 0x8C2D,
    NC_MINIHOUSE_MODIFY_TITLE_REQ = 0x8C2E,
    NC_MINIHOUSE_MODIFY_TITLE_ACK = 0x8C2F,
    NC_MINIHOUSE_MODIFY_TITLE_CMD = 0x8C30,
    NC_MINIHOUSE_MODIFY_OUTSIDE_TITLE_CMD = 0x8C31,
    NC_MINIHOUSE_MODIFY_MAXENTERNUM_REQ = 0x8C32,
    NC_MINIHOUSE_MODIFY_MAXENTERNUM_ACK = 0x8C33,
    NC_MINIHOUSE_MODIFY_MAXENTERNUM_CMD = 0x8C34,
    NC_MINIHOUSE_MODIFY_OWNERBLOG_REQ = 0x8C35,
    NC_MINIHOUSE_MODIFY_OWNERBLOG_ACK = 0x8C36,
    NC_MINIHOUSE_OWNERBLOG_REQ = 0x8C37,
    NC_MINIHOUSE_OWNERBLOG_ACK = 0x8C38,
    NC_MINIHOUSE_DB_OWNERBLOG_GET_REQ = 0x8C39,
    NC_MINIHOUSE_DB_OWNERBLOG_GET_ACK = 0x8C3A,
    NC_MINIHOUSE_DB_OWNERBLOG_SET_REQ = 0x8C3B,
    NC_MINIHOUSE_DB_OWNERBLOG_SET_ACK = 0x8C3C,
    NC_MINIHOUSE_CHAR_ACTION_REQ = 0x8C3D,
    NC_MINIHOUSE_CHAR_ACTION_ACK = 0x8C3E,
    NC_MINIHOUSE_CHAR_ACTION_CMD = 0x8C3F,
    NC_MINIHOUSE_FURNITURE_EFFECT_REQ = 0x8C40,
    NC_MINIHOUSE_FURNITURE_EFFECT_ACK = 0x8C41,
    NC_MINIHOUSE_FURNITURE_EFFECT_CMD = 0x8C42,
    NC_MINIHOUSE_MODIFY_ITEM_INFO_OPEN_REQ = 0x8C43,
    NC_MINIHOUSE_MODIFY_ITEM_INFO_OPEN_ACK = 0x8C44,
    NC_MINIHOUSE_MODIFY_ITEM_INFO_OPEN_CMD = 0x8C45,
    NC_MINIHOUSE_MODIFY_NOTIFY_REQ = 0x8C48,
    NC_MINIHOUSE_MODIFY_NOTIFY_ACK = 0x8C49,
    NC_MINIHOUSE_MODIFY_NOTIFY_CMD = 0x8C4A,
    NC_MINIHOUSE_PORTAL_LIST_CMD = 0x8C4B,
    NC_MINIHOUSE_PORTAL_ADD_CMD = 0x8C4C,
    NC_MINIHOUSE_PORTAL_DEL_REQ = 0x8C4D,
    NC_MINIHOUSE_PORTAL_DEL_ACK = 0x8C4E,
    NC_MINIHOUSE_PORTAL_DEL_CMD = 0x8C4F,
    NC_MINIHOUSE_PORTAL_OPEN_REQ = 0x8C50,
    NC_MINIHOUSE_PORTAL_OPEN_ACK = 0x8C51,
    NC_MINIHOUSE_PORTAL_CLOSE_REQ = 0x8C53,
    NC_MINIHOUSE_PORTAL_CLOSE_ACK = 0x8C54,
    NC_MINIHOUSE_PORTAL_EFFECT_REQ = 0x8C56,
    NC_MINIHOUSE_PORTAL_EFFECT_ACK = 0x8C57,
    NC_MINIHOUSE_PORTAL_EFFECT_CMD = 0x8C58,
    NC_MINIHOUSE_DB_PORTAL_LIST_REQ = 0x8C59,
    NC_MINIHOUSE_DB_PORTAL_LIST_ACK = 0x8C5A,
    NC_MINIHOUSE_DB_VISITER_COUNT_REQ = 0x8C5B,
    NC_MINIHOUSE_DB_VISITER_COUNT_ACK = 0x8C5C,
    NC_MINIHOUSE_DB_PORTAL_ADD_REQ = 0x8C5D,
    NC_MINIHOUSE_DB_PORTAL_ADD_ACK = 0x8C5E,
    NC_MINIHOUSE_DB_PORTAL_DEL_REQ = 0x8C5F,
    NC_MINIHOUSE_DB_PORTAL_DEL_ACK = 0x8C60,
    NC_MINIHOUSE_FURNITURE_ENDURE_CMD = 0x8C61,
    NC_MINIHOUSE_FURNITURE_EMOTION_REQ = 0x8C62,
    NC_MINIHOUSE_FURNITURE_EMOTION_ACK = 0x8C63,
    NC_MINIHOUSE_FURNITURE_EMOTION_CMD = 0x8C64,
    NC_MINIHOUSE_FURNITURE_EMOTION_CANCEL_REQ = 0x8C65,
    NC_MINIHOUSE_FURNITURE_EMOTION_CANCEL_ACK = 0x8C66,
    NC_MINIHOUSE_FURNITURE_EMOTION_CANCEL_CMD = 0x8C67,

    NC_CHARGED_NULL = 0x9000,
    NC_CHARGED_SETBUFF_CMD = 0x9001,
    NC_CHARGED_RESETBUFF_CMD = 0x9002,
    NC_CHARGED_BUFFSTART_CMD = 0x9003,
    NC_CHARGED_BUFFTERMINATE_CMD = 0x9004,
    NC_CHARGED_STAT_INITIALIZE_DB_REQ = 0x9005,
    NC_CHARGED_SKILLEMPOW_INITIALIZE_DB_REQ = 0x9006,
    NC_CHARGED_STAT_INITIALIZE_DB_SUC_ACK = 0x9007,
    NC_CHARGED_SKILLEMPOW_INITIALIZE_DB_SUC_ACK = 0x9008,
    NC_CHARGED_STAT_INITIALIZE_DB_FAIL_ACK = 0x9009,
    NC_CHARGED_SKILLEMPOW_INITIALIZE_DB_FAIL_ACK = 0x900A,
    NC_CHARGED_DELETEWEAPONTITLE_CMD = 0x900B,
    NC_CHARGED_STAT_INITIALIZE_SUC_CMD = 0x900C,
    NC_CHARGED_SKILLEMPOW_INITIALIZE_SUC_CMD = 0x900D,
    NC_CHARGED_STAT_INITIALIZE_FAIL_CMD = 0x900E,
    NC_CHARGED_SKILLEMPOW_INITIALIZE_FAIL_CMD = 0x900F,
    NC_CHARGED_BOOTHSLOTSIZE_CMD = 0x9010,

    NC_HOLY_PROMISE_NULL = 0x9400,
    NC_HOLY_PROMISE_SET_UP_REQ = 0x9401,
    NC_HOLY_PROMISE_SET_UP_ACK = 0x9402,
    NC_HOLY_PROMISE_SET_UP_CONFIRM_ING = 0x9403,
    NC_HOLY_PROMISE_SET_UP_CONFIRM_REQ = 0x9404,
    NC_HOLY_PROMISE_SET_UP_CONFIRM_ACK = 0x9405,
    NC_HOLY_PROMISE_DEL_UP_REQ = 0x9406,
    NC_HOLY_PROMISE_DEL_UP_ACK = 0x9407,
    NC_HOLY_PROMISE_DEL_DOWN_REQ = 0x940A,
    NC_HOLY_PROMISE_DEL_DOWN_ACK = 0x940B,
    NC_HOLY_PROMISE_LIST_CMD = 0x9414,
    NC_HOLY_PROMISE_ADD_CMD = 0x9415,
    NC_HOLY_PROMISE_DEL_CMD = 0x9418,
    NC_HOLY_PROMISE_LOGIN_CMD = 0x9416,
    NC_HOLY_PROMISE_LOGOUT_CMD = 0x9417,
    NC_HOLY_PROMISE_LEVEL_CMD = 0x9419,
    NC_HOLY_PROMISE_REWARD_ITEM_CMD = 0x941A,
    NC_HOLY_PROMISE_REWARD_MONEY_CMD = 0x941B,
    NC_HOLY_PROMISE_DB_SET_UP_REQ = 0x941E,
    NC_HOLY_PROMISE_DB_SET_UP_ACK = 0x941F,
    NC_HOLY_PROMISE_DB_DEL_UP_REQ = 0x9420,
    NC_HOLY_PROMISE_DB_DEL_UP_ACK = 0x9421,
    NC_HOLY_PROMISE_DB_DEL_DOWN_REQ = 0x9422,
    NC_HOLY_PROMISE_DB_DEL_DOWN_ACK = 0x9423,
    NC_HOLY_PROMISE_DB_DEL_CHAR_REQ = 0x9424,
    NC_HOLY_PROMISE_DB_DEL_CHAR_ACK = 0x9425,
    NC_HOLY_PROMISE_DB_GET_UP_REQ = 0x9426,
    NC_HOLY_PROMISE_DB_GET_UP_ACK = 0x9427,
    NC_HOLY_PROMISE_DB_GET_MEMBER_REQ = 0x9428,
    NC_HOLY_PROMISE_DB_GET_MEMBER_ACK = 0x9429,
    NC_HOLY_PROMISE_DB_REWARD_REQ = 0x942A,
    NC_HOLY_PROMISE_DB_REWARD_ACK = 0x942B,
    NC_HOLY_PROMISE_DB_SET_DATE_REQ = 0x942C,
    NC_HOLY_PROMISE_DB_SET_DATE_ACK = 0x942D,
    NC_HOLY_PROMISE_MY_UP_ZONE = 0x9432,
    NC_HOLY_PROMISE_USE_MONEY_ZONE = 0x9433,
    NC_HOLY_PROMISE_MYUPPER_REQ = 0x9434,
    NC_HOLY_PROMISE_MYUPPER_ACK = 0x9435,
    NC_HOLY_PROMISE_CENTRANSFER_RNG = 0x9436,
    NC_HOLY_PROMISE_GET_CEN_REWARD_REQ = 0x943C,
    NC_HOLY_PROMISE_GET_CEN_REWARD_ACK = 0x943D,
    NC_HOLY_PROMISE_DB_GET_CEN_REWARD_REQ = 0x943E,
    NC_HOLY_PROMISE_DB_GET_CEN_REWARD_ACK = 0x943F,
    NC_HOLY_PROMISE_WITHDRAW_CEN_REWARD_REQ = 0x9440,
    NC_HOLY_PROMISE_WITHDRAW_CEN_REWARD_ACK = 0x9441,
    NC_HOLY_PROMISE_DB_WITHDRAW_CEN_REWARD_REQ = 0x9442,
    NC_HOLY_PROMISE_DB_WITHDRAW_CEN_REWARD_ACK = 0x9443,
    NC_HOLY_PROMISE_DB_GET_REMAIN_MONEY_CMD = 0x9444,
    NC_HOLY_PROMISE_CLIENT_GET_REMAIN_MONEY_CMD = 0x9445,

    NC_GUILD_ACADEMY_NULL = 0x9800,
    NC_GUILD_ACADEMY_START_DB_ALL_REQ = 0x9801,
    NC_GUILD_ACADEMY_START_DB_ALL_ACK = 0x9802,
    NC_GUILD_ACADEMY_START_DB_GET_RANKING_LIST_REQ = 0x9803,
    NC_GUILD_ACADEMY_START_DB_GET_RANKING_LIST_ACK = 0x9804,
    NC_GUILD_ACADEMY_START_DB_RANK_BALANCE_REQ = 0x9805,
    NC_GUILD_ACADEMY_START_DB_RANK_BALANCE_ACK = 0x9806,
    NC_GUILD_ACADEMY_MY_GUILD_ACADEMY_INFO_REQ = 0x9807,
    NC_GUILD_ACADEMY_MY_GUILD_ACADEMY_INFO_ACK = 0x9808,
    NC_GUILD_ACADEMY_MY_ACADEMY_RANK_INFO_REQ = 0x9809,
    NC_GUILD_ACADEMY_MY_ACADEMY_RANK_INFO_ACK = 0x980A,
    NC_GUILD_ACADEMY_LIST_REQ = 0x980B,
    NC_GUILD_ACADEMY_LIST_ACK = 0x980C,
    NC_GUILD_ACADEMY_MEMBER_LIST_REQ = 0x980D,
    NC_GUILD_ACADEMY_MEMBER_LIST_ACK = 0x980E,
    NC_GUILD_ACADEMY_DB_MEMBER_REQ = 0x980F,
    NC_GUILD_ACADEMY_DB_MEMBER_ACK = 0x9810,
    NC_GUILD_ACADEMY_MEMBER_JOIN_REQ = 0x9811,
    NC_GUILD_ACADEMY_MEMBER_JOIN_ACK = 0x9812,
    NC_GUILD_ACADEMY_MEMBER_JOIN_CMD = 0x9813,
    NC_GUILD_ACADEMY_DB_MEMBER_JOIN_REQ = 0x9814,
    NC_GUILD_ACADEMY_DB_MEMBER_JOIN_ACK = 0x9815,
    NC_GUILD_ACADEMY_MEMBER_VANISH_REQ = 0x9816,
    NC_GUILD_ACADEMY_MEMBER_VANISH_ACK = 0x9817,
    NC_GUILD_ACADEMY_MEMBER_VANISH_CMD = 0x9818,
    NC_GUILD_ACADEMY_DB_MEMBER_VANISH_REQ = 0x9819,
    NC_GUILD_ACADEMY_DB_MEMBER_VANISH_ACK = 0x981A,
    NC_GUILD_ACADEMY_MEMBER_LEAVE_REQ = 0x981B,
    NC_GUILD_ACADEMY_MEMBER_LEAVE_ACK = 0x981C,
    NC_GUILD_ACADEMY_DB_MEMBER_LEAVE_REQ = 0x981D,
    NC_GUILD_ACADEMY_DB_MEMBER_LEAVE_ACK = 0x981E,
    NC_GUILD_ACADEMY_MASTER_TELEPORT_REQ = 0x981F,
    NC_GUILD_ACADEMY_MASTER_TELEPORT_ACK = 0x9820,
    NC_GUILD_ACADEMY_MEMBER_CHAT_BAN_REQ = 0x9821,
    NC_GUILD_ACADEMY_MEMBER_CHAT_BAN_ACK = 0x9822,
    NC_GUILD_ACADEMY_MEMBER_CHAT_BAN_CMD = 0x9823,
    NC_GUILD_ACADEMY_NOTIFY_REQ = 0x9824,
    NC_GUILD_ACADEMY_NOTIFY_ACK = 0x9825,
    NC_GUILD_ACADEMY_NOTIFY_CMD = 0x9826,
    NC_GUILD_ACADEMY_DB_NOTIFY_REQ = 0x9827,
    NC_GUILD_ACADEMY_DB_NOTIFY_ACK = 0x9828,
    NC_GUILD_ACADEMY_MEMBER_GUILD_INVITE_REQ = 0x9829,
    NC_GUILD_ACADEMY_MEMBER_GUILD_INVITE_ACK = 0x982A,
    NC_GUILD_ACADEMY_MEMBER_GUILD_JOIN_REQ = 0x982B,
    NC_GUILD_ACADEMY_MEMBER_GUILD_JOIN_ACK = 0x982C,
    NC_GUILD_ACADEMY_MEMBER_GUILD_JOIN_ERR = 0x982D,
    NC_GUILD_ACADEMY_MEMBER_GUILD_JOIN_CMD = 0x982E,
    NC_GUILD_ACADEMY_DB_MEMBER_GUILD_JOIN_REQ = 0x982F,
    NC_GUILD_ACADEMY_DB_MEMBER_GUILD_JOIN_ACK = 0x9830,
    NC_GUILD_ACADEMY_GET_REWARD_MONEY_REQ = 0x9831,
    NC_GUILD_ACADEMY_GET_REWARD_MONEY_ACK = 0x9832,
    NC_GUILD_ACADEMY_DB_GET_REWARD_MONEY_REQ = 0x9833,
    NC_GUILD_ACADEMY_DB_GET_REWARD_MONEY_ACK = 0x9834,
    NC_GUILD_ACADEMY_GET_REWARD_ITEM_REQ = 0x9835,
    NC_GUILD_ACADEMY_GET_REWARD_ITEM_ACK = 0x9836,
    NC_GUILD_ACADEMY_DB_GET_REWARD_ITEM_REQ = 0x9837,
    NC_GUILD_ACADEMY_DB_GET_REWARD_ITEM_ACK = 0x9838,
    NC_GUILD_ACADEMY_SET_REWARD_MONEY_REQ = 0x9839,
    NC_GUILD_ACADEMY_SET_REWARD_MONEY_ACK = 0x983A,
    NC_GUILD_ACADEMY_DB_SET_REWARD_MONEY_REQ = 0x983B,
    NC_GUILD_ACADEMY_DB_SET_REWARD_MONEY_ACK = 0x983C,
    NC_GUILD_ACADEMY_SET_REWARD_ITEM_REQ = 0x983D,
    NC_GUILD_ACADEMY_SET_REWARD_ITEM_ACK = 0x983E,
    NC_GUILD_ACADEMY_DB_SET_REWARD_ITEM_REQ = 0x983F,
    NC_GUILD_ACADEMY_DB_SET_REWARD_ITEM_ACK = 0x9840,
    NC_GUILD_ACADEMY_CLEAR_REWARD_MONEY_REQ = 0x9841,
    NC_GUILD_ACADEMY_CLEAR_REWARD_MONEY_ACK = 0x9842,
    NC_GUILD_ACADEMY_DB_CLEAR_REWARD_MONEY_REQ = 0x9843,
    NC_GUILD_ACADEMY_DB_CLEAR_REWARD_MONEY_ACK = 0x9844,
    NC_GUILD_ACADEMY_CLEAR_REWARD_ITEM_REQ = 0x9845,
    NC_GUILD_ACADEMY_CLEAR_REWARD_ITEM_ACK = 0x9846,
    NC_GUILD_ACADEMY_DB_CLEAR_REWARD_ITEM_REQ = 0x9847,
    NC_GUILD_ACADEMY_DB_CLEAR_REWARD_ITEM_ACK = 0x9848,
    NC_GUILD_ACADEMY_GET_GRADUATE_REQ = 0x9849,
    NC_GUILD_ACADEMY_GET_GRADUATE_ACK = 0x984A,
    NC_GUILD_ACADEMY_DB_GET_GRADUATE_REQ = 0x984B,
    NC_GUILD_ACADEMY_DB_GET_GRADUATE_ACK = 0x984C,
    NC_GUILD_ACADEMY_GET_RANKING_LIST_REQ = 0x984D,
    NC_GUILD_ACADEMY_GET_RANKING_LIST_ACK = 0x984E,
    NC_GUILD_ACADEMY_DB_GET_RANKING_LIST_REQ = 0x984F,
    NC_GUILD_ACADEMY_DB_GET_RANKING_LIST_ACK = 0x9850,
    NC_GUILD_ACADEMY_DB_GRADUATE_JOIN_REQ = 0x9851,
    NC_GUILD_ACADEMY_DB_GRADUATE_JOIN_ACK = 0x9852,
    NC_GUILD_ACADEMY_DB_GRADUATE_JOIN_CMD = 0x9853,
    NC_GUILD_ACADEMY_DB_LEVEL_UP_REQ = 0x9854,
    NC_GUILD_ACADEMY_DB_LEVEL_UP_ACK = 0x9855,
    NC_GUILD_ACADEMY_DB_LEVEL_UP_CMD = 0x9856,
    NC_GUILD_ACADEMY_DB_RANK_BALANCE_REQ = 0x9857,
    NC_GUILD_ACADEMY_DB_RANK_BALANCE_ACK = 0x9858,
    NC_GUILD_ACADEMY_SET_MASTER_REQ = 0x9859,
    NC_GUILD_ACADEMY_SET_MASTER_ACK = 0x985A,
    NC_GUILD_ACADEMY_SET_MASTER_CMD = 0x985B,
    NC_GUILD_ACADEMY_DB_SET_MASTER_REQ = 0x985C,
    NC_GUILD_ACADEMY_DB_SET_MASTER_ACK = 0x985D,
    NC_GUILD_ACADEMY_DISMISS_CMD = 0x985E,
    NC_GUILD_ACADEMY_DELETE_CMD = 0x985F,
    NC_GUILD_ACADEMY_MEMBER_LEAVE_CMD = 0x9860,
    NC_GUILD_ACADEMY_MEMBER_LOGON_CMD = 0x9861,
    NC_GUILD_ACADEMY_MEMBER_LOGOFF_CMD = 0x9862,
    NC_GUILD_ACADEMY_MEMBER_MAP_CMD = 0x9863,
    NC_GUILD_ACADEMY_MEMBER_INTRO_CMD = 0x9864,
    NC_GUILD_ACADEMY_MEMBER_PARTY_CMD = 0x9865,
    NC_GUILD_ACADEMY_MEMBER_LEVEL_CMD = 0x9866,
    NC_GUILD_ACADEMY_MEMBER_CLASS_CMD = 0x9867,
    NC_GUILD_ACADEMY_CHAT_REQ = 0x9868,
    NC_GUILD_ACADEMY_CHAT_CMD = 0x9869,
    NC_GUILD_ACADEMY_CHAT_ACK = 0x986A,
    NC_GUILD_ACADEMY_DB_ACADEMY_REWARD_REQ = 0x986B,
    NC_GUILD_ACADEMY_DB_ACADEMY_REWARD_ACK = 0x986C,
    NC_GUILD_ACADEMY_REWARD_STORAGE_OPEN_REQ = 0x986D,
    NC_GUILD_ACADEMY_REWARD_STORAGE_OPEN_ACK = 0x986E,
    NC_GUILD_ACADEMY_REWARD_STORAGE_CLOSE_CMD = 0x986F,
    NC_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_GRADE_REQ = 0x9870,
    NC_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_GRADE_ACK = 0x9871,
    NC_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_RNG = 0x9872,
    NC_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_CMD = 0x9873,
    NC_GUILD_ACADEMY_REWARD_STORAGE_DEPOSIT_RNG = 0x9874,
    NC_GUILD_ACADEMY_REWARD_STORAGE_DEPOSIT_CMD = 0x9875,
    NC_GUILD_ACADEMY_ZONE_MEMBER_JOIN_CMD = 0x9876,
    NC_GUILD_ACADEMY_ZONE_MEMBER_LEAVE_CMD = 0x9877,
    NC_GUILD_ACADEMY_ZONE_MASTER_TELEPORT_CMD = 0x9878,
    NC_GUILD_ACADEMY_ZONE_MEMBER_GUILD_JOIN_CMD = 0x9879,
    NC_GUILD_ACADEMY_ZONE_GUILD_BUFF_CMD = 0x987A,
    NC_GUILD_ACADEMY_ZONE_GUILD_ACADEMY_MASTER_BUFF_CMD = 0x987B,
    NC_GUILD_ACADEMY_WAR_INFO_LIST_CMD = 0x987C,
    NC_GUILD_ACADEMY_WAR_START_CMD = 0x987D,
    NC_GUILD_ACADEMY_WAR_END_CMD = 0x987E,
    NC_GUILD_ACADEMY_DB_SET_MASTER_BY_LEAVE_REQ = 0x987F,
    NC_GUILD_ACADEMY_DB_SET_MASTER_BY_LEAVE_ACK = 0x9880,
    NC_GUILD_ACADEMY_SET_MASTER_BY_LEAVE_CMD = 0x9881,
    NC_GUILD_ACADEMY_DB_REWARD_WANT_CMD = 0x9882,
    NC_GUILD_ACADEMY_REWARD_WANT_CMD = 0x9883,
    NC_GUILD_ACADEMY_REWARDSTORAGE_ITEM_INFO_ZONE_RNG = 0x9884,
    NC_GUILD_ACADEMY_REWARDSTORAGE_REWARD_ZONE_RNG = 0x9885,
    NC_GUILD_ACADEMY_REWARDSTORAGE_GRADE_INFO_CMD = 0x9886,
    NC_GUILD_ACADEMY_MEMBER_DB_CHAT_BAN_REQ = 0x9887,
    NC_GUILD_ACADEMY_MEMBER_DB_CHAT_BAN_ACK = 0x9888,
    NC_GUILD_ACADEMY_MEMBER_DB_SAVE_CHAT_BAN_TIME_CMD = 0x9889,
    NC_GUILD_ACADEMY_MEMBER_CHAT_BAN_CANCEL_REQ = 0x988A,
    NC_GUILD_ACADEMY_MEMBER_CHAT_BAN_CANCEL_ACK = 0x988B,
    NC_GUILD_ACADEMY_MEMBER_CHAT_BAN_CANCEL_CMD = 0x988C,
    NC_GUILD_ACADEMY_MEMBER_DB_CHAT_BAN_CANCEL_REQ = 0x988D,
    NC_GUILD_ACADEMY_MEMBER_DB_CHAT_BAN_CANCEL_ACK = 0x988E,
    NC_GUILD_ACADEMY_HISTORY_LIST_REQ = 0x988F,
    NC_GUILD_ACADEMY_HISTORY_LIST_ACK = 0x9890,
    NC_GUILD_ACADEMY_HISTORY_DB_LIST_REQ = 0x9891,
    NC_GUILD_ACADEMY_HISTORY_DB_LIST_ACK = 0x9892,

    NC_PROMOTION_NULL = 0xA000,
    NC_PROMOTION_USER_REQ = 0xA001,
    NC_PROMOTION_USER_ACK = 0xA002,
    NC_PROMOTION_USER_CMD = 0xA003,
    NC_PROMOTION_DB_REWARD_REQ = 0xA004,
    NC_PROMOTION_DB_REWARD_ACK = 0xA005,
    NC_PROMOTION_REWARD_ITEM_CMD = 0xA006,

    NC_INSTANCE_DUNGEON_NULL = 0xA400,
    NC_INSTANCE_DUNGEON_EMPTY_DUNGEON_CMD = 0xA401,
    NC_INSTANCE_DUNGEON_DELETE_DUNGEON_CMD = 0xA402,
    NC_INSTANCE_DUNGEON_RESET_COUNTDOWN_CMD = 0xA403,
    NC_INSTANCE_DUNGEON_FIND_RNG = 0xA404,
    NC_INSTANCE_DUNGEON_LEVEL_SELECT_CHECK_REQ = 0xA408,
    NC_INSTANCE_DUNGEON_LEVEL_SELECT_CHECK_ACK = 0xA409,
    NC_INSTANCE_DUNGEON_LEVEL_SELECT_CHECK_ECHO_REQ = 0xA40A,
    NC_INSTANCE_DUNGEON_LEVEL_SELECT_CHECK_ECHO_ACK = 0xA40B,
    NC_INSTANCE_DUNGEON_LEVEL_SELECT_MENU_REQ = 0xA40C,
    NC_INSTANCE_DUNGEON_LEVEL_SELECT_MENU_ACK = 0xA40D,
    NC_INSTANCE_DUNGEON_LEVEL_SELECT_JOIN_REQ = 0xA40E,
    NC_INSTANCE_DUNGEON_LEVEL_SELECT_JOIN_ACK = 0xA40F,
    NC_INSTANCE_DUNGEON_LEVEL_SELECT_JOIN_ECHO_REQ = 0xA410,
    NC_INSTANCE_DUNGEON_LEVEL_SELECT_JOIN_ECHO_ACK = 0xA411,
    NC_INSTANCE_DUNGEON_RANK_RESULT_CMD = 0xA412,
    NC_INSTANCE_DUNGEON_RANK_SAVE_DB_CMD = 0xA413,
    NC_INSTANCE_DUNGEON_RANK_SAVE_WORLD_CMD = 0xA414,
    NC_INSTANCE_DUNGEON_RANK_UPDATE_DB_REQ = 0xA415,
    NC_INSTANCE_DUNGEON_RANK_UPDATE_DB_ACK = 0xA416,
    NC_INSTANCE_DUNGEON_RANK_LIST_REQ = 0xA417,
    NC_INSTANCE_DUNGEON_RANK_LIST_ACK = 0xA418,
    NC_INSTANCE_DUNGEON_MAP_REGIST_CMD = 0xA419,
    NC_INSTANCE_DUNGEON_RANK_REQ = 0xA41A,
    NC_INSTANCE_DUNGEON_RANK_TAB_DAMAGEDEALT_REQ = 0xA41B,
    NC_INSTANCE_DUNGEON_RANK_TAB_DAMAGETAKEN_REQ = 0xA41C,
    NC_INSTANCE_DUNGEON_RANK_TAB_HEALINGDONE_REQ = 0xA41D,
    NC_INSTANCE_DUNGEON_RANK_TAB_MYRANK_REQ = 0xA41E,
    NC_INSTANCE_DUNGEON_RANK_ACK = 0xA41F,
    NC_INSTANCE_DUNGEON_RANK_MYRANK_CMD = 0xA420,
    NC_INSTANCE_DUNGEON_RANK_TAB_DAMAGEDEALT_ACK = 0xA421,
    NC_INSTANCE_DUNGEON_RANK_TAB_DAMAGETAKEN_ACK = 0xA422,
    NC_INSTANCE_DUNGEON_RANK_TAB_HEALINGDONE_ACK = 0xA423,
    NC_INSTANCE_DUNGEON_RANK_TAB_MYRANK_ACK = 0xA424,
    NC_INSTANCE_DUNGEON_RANK_NEW_RANK_MSG = 0xA425,

    NC_CHAT_RESTRICT_NULL = 0xA800,
    NC_CHAT_RESTRICT_DB_LIST_CMD = 0xA801,
    NC_CHAT_RESTRICT_LIST_CMD = 0xA802,
    NC_CHAT_RESTRICT_ADD_REQ = 0xA803,
    NC_CHAT_RESTRICT_DB_ADD_REQ = 0xA804,
    NC_CHAT_RESTRICT_DB_ADD_ACK = 0xA805,
    NC_CHAT_RESTRICT_ADD_ACK = 0xA806,
    NC_CHAT_RESTRICT_DEL_REQ = 0xA807,
    NC_CHAT_RESTRICT_DB_DEL_REQ = 0xA808,
    NC_CHAT_RESTRICT_DB_DEL_ACK = 0xA809,
    NC_CHAT_RESTRICT_DEL_ACK = 0xA80A,
    NC_CHAT_RESTRICT_DEL_ALL_REQ = 0xA80B,
    NC_CHAT_RESTRICT_DB_DEL_ALL_REQ = 0xA80C,
    NC_CHAT_RESTRICT_DB_DEL_ALL_ACK = 0xA80D,
    NC_CHAT_RESTRICT_DEL_ALL_ACK = 0xA80E,

    NC_DICE_TAISAI_NULL = 0xAC00,
    NC_DICE_TAISAI_GAME_JOIN_REQ = 0xAC01,
    NC_DICE_TAISAI_GAME_JOIN_ACK = 0xAC02,
    NC_DICE_TAISAI_GAME_JOIN_CMD = 0xAC03,
    NC_DICE_TAISAI_GAME_BETTING_INFO_CMD = 0xAC04,
    NC_DICE_TAISAI_GAME_LEAVE_REQ = 0xAC05,
    NC_DICE_TAISAI_GAME_LEAVE_ACK = 0xAC06,
    NC_DICE_TAISAI_GAME_LEAVE_CMD = 0xAC07,
    NC_DICE_TAISAI_BOARD_PITCH_CMD = 0xAC08,
    NC_DICE_TAISAI_BOARD_FOLD_RESERVE_CMD = 0xAC09,
    NC_DICE_TAISAI_BOARD_FOLD_CMD = 0xAC0A,
    NC_DICE_TAISAI_EXPECT_INCOME_MONEY_REQ = 0xAC0B,
    NC_DICE_TAISAI_DB_EXPECT_INCOME_MONEY_REQ = 0xAC0C,
    NC_DICE_TAISAI_DB_EXPECT_INCOME_MONEY_ACK = 0xAC0D,
    NC_DICE_TAISAI_EXPECT_INCOME_MONEY_ACK = 0xAC0E,
    NC_DICE_TAISAI_RECEIPT_INCOME_MONEY_REQ = 0xAC0F,
    NC_DICE_TAISAI_DB_RECEIPT_INCOME_MONEY_REQ = 0xAC10,
    NC_DICE_TAISAI_DB_RECEIPT_INCOME_MONEY_ACK = 0xAC11,
    NC_DICE_TAISAI_RECEIPT_INCOME_MONEY_ACK = 0xAC12,
    NC_DICE_TAISAI_GAME_MODE_CHANGE_REQ = 0xAC13,
    NC_DICE_TAISAI_GAME_MODE_CHANGE_ACK = 0xAC14,
    NC_DICE_TAISAI_GAME_MODE_CHANGE_CMD = 0xAC15,
    NC_DICE_TAISAI_RANK_REQ = 0xAC16,
    NC_DICE_TAISAI_DB_RANK_REQ = 0xAC17,
    NC_DICE_TAISAI_DB_RANK_ACK = 0xAC18,
    NC_DICE_TAISAI_RANK_ACK = 0xAC19,
    NC_DICE_TAISAI_BETTING_REQ = 0xAC1A,
    NC_DICE_TAISAI_BETTING_ACK = 0xAC1B,
    NC_DICE_TAISAI_BETTING_CMD = 0xAC1C,
    NC_DICE_TAISAI_BETTING_CANCEL_REQ = 0xAC1D,
    NC_DICE_TAISAI_BETTING_CANCEL_ACK = 0xAC1E,
    NC_DICE_TAISAI_BETTING_CANCEL_CMD = 0xAC1F,
    NC_DICE_TAISAI_DICE_ROLL_REQ = 0xAC20,
    NC_DICE_TAISAI_DICE_ROLL_ACK = 0xAC21,
    NC_DICE_TAISAI_DICE_ROLL_CMD = 0xAC22,
    NC_DICE_TAISAI_DB_DICE_ROLL_RESULT_REQ = 0xAC23,
    NC_DICE_TAISAI_DB_DICE_ROLL_RESULT_ACK = 0xAC24,
    NC_DICE_TAISAI_DB_DICE_ROLL_RESULT_LOG_CMD = 0xAC25,
    NC_DICE_TAISAI_DICE_ROLL_RESULT_CMD = 0xAC26,
    NC_DICE_TAISAI_DICE_ROLL_RESULT_EMOTION_CMD = 0xAC27,
    NC_DICE_TAISAI_LARGE_AMOUNT_REQ = 0xAC28,
    NC_DICE_TAISAI_LARGE_AMOUNT_ACK = 0xAC29,
    NC_DICE_TAISAI_LARGE_AMOUNT_CMD = 0xAC2A,
    NC_DICE_TAISAI_BET_START_CMD = 0xAC2B,
    NC_DICE_TAISAI_TIMER_CMD = 0xAC2C,
    NC_DICE_TAISAI_DB_ITEM_ID_CHANGE_REQ = 0xAC2C,
    NC_DICE_TAISAI_DB_ITEM_ID_CHANGE_ACK = 0xAC2D,

    NC_RAID_NULL = 0xB000,
    NC_RAID_MAKE_REQ = 0xB001,
    NC_RAID_MAKE_ACK = 0xB002,
    NC_RAID_MAKE_BROAD_CMD = 0xB003,
    NC_RAID_ZONE_MAKE_CMD = 0xB004,
    NC_RAID_MEMBER_LIST_CMD = 0xB005,
    NC_RAID_DISMISS_BROAD_CMD = 0xB006,
    NC_RAID_ZONE_DISMISS_CMD = 0xB007,
    NC_RAID_LOOTING_TYPE_REQ = 0xB008,
    NC_RAID_LOOTING_TYPE_ACK = 0xB009,
    NC_RAID_LOOTING_TYPE_BROAD_CMD = 0xB00A,
    NC_RAID_ZONE_LOOTING_TYPE_CMD = 0xB00B,
    NC_RAID_INVITATION_REQ = 0xB00C,
    NC_RAID_INVITATION_ACK = 0xB00D,
    NC_RAID_INVITATION_CMD = 0xB00E,
    NC_RAID_INVITATION_ANSWER_REQ = 0xB00F,
    NC_RAID_INVITATION_ANSWER_ACK = 0xB010,
    NC_RAID_INVITATION_ANSWER_CMD = 0xB011,
    NC_RAID_MEMBER_JOIN_BROAD_CMD = 0xB012,
    NC_RAID_ZONE_MEMBER_JOIN_CMD = 0xB013,
    NC_RAID_LEAVE_REQ = 0xB014,
    NC_RAID_LEAVE_ACK = 0xB015,
    NC_RAID_LEAVE_BROAD_CMD = 0xB016,
    NC_RAID_ZONE_LEAVE_CMD = 0xB017,
    NC_RAID_VANISH_REQ = 0xB018,
    NC_RAID_VANISH_ACK = 0xB019,
    NC_RAID_VANISH_CMD = 0xB01A,
    NC_RAID_VANISH_BROAD_CMD = 0xB01B,
    NC_RAID_ZONE_VANISH_CMD = 0xB01C,
    NC_RAID_ZONE_LOGIN_CMD = 0xB01D,
    NC_RAID_LOGININFO_CMD = 0xB01E,
    NC_RAID_ZONE_LOGOUT_CMD = 0xB01F,
    NC_RAID_LOGOUTINFO_CMD = 0xB020,
    NC_RAID_MAPOUT_CMD = 0xB021,
    NC_RAID_MEMBERINFORM_CMD = 0xB022,
    NC_RAID_MEMBERCLASS_CMD = 0xB023,
    NC_RAID_WORLD_MEMBERCLASS_CMD = 0xB024,
    NC_RAID_MEMBER_BROADCAST_INFO_CMD = 0xB025,
    NC_RAID_LOCATION_CMD = 0xB026,
    NC_RAID_SLOT_MOVE_REQ = 0xB027,
    NC_RAID_SLOT_MOVE_ACK = 0xB028,
    NC_RAID_SLOT_MOVE_BROAD_CMD = 0xB029,
    NC_RAID_ZONE_SLOT_MOVE_CMD = 0xB02A,
    NC_RAID_SET_LEADER_REQ = 0xB02B,
    NC_RAID_SET_LEADER_ACK = 0xB02C,
    NC_RAID_SET_LEADER_CMD = 0xB02D,
    NC_RAID_SET_LEADER_BROAD_CMD = 0xB02E,
    NC_RAID_ZONE_SET_LEADER_CMD = 0xB02F,
    NC_RAID_SET_SUB_LEADER_REQ = 0xB030,
    NC_RAID_SET_SUB_LEADER_ACK = 0xB031,
    NC_RAID_SET_SUB_LEADER_CMD = 0xB032,
    NC_RAID_SET_SUB_LEADER_BROAD_CMD = 0xB033,
    NC_RAID_ZONE_SET_SUB_LEADER_CMD = 0xB034,
    NC_RAID_DEL_SUB_LEADER_REQ = 0xB035,
    NC_RAID_DEL_SUB_LEADER_ACK = 0xB036,
    NC_RAID_DEL_SUB_LEADER_CMD = 0xB037,
    NC_RAID_DEL_SUB_LEADER_BROAD_CMD = 0xB038,
    NC_RAID_ZONE_DEL_SUB_LEADER_CMD = 0xB039,
    NC_RAID_SET_LOOTER_REQ = 0xB03A,
    NC_RAID_SET_LOOTER_ACK = 0xB03B,
    NC_RAID_SET_LOOTER_CMD = 0xB03C,
    NC_RAID_SET_LOOTER_BROAD_CMD = 0xB03D,
    NC_RAID_ZONE_SET_LOOTER_CMD = 0xB03E,
    NC_RAID_CHAT_REQ = 0xB03F,
    NC_RAID_CHAT_ACK = 0xB040,
    NC_RAID_CHAT_BROAD_CMD = 0xB041,
    NC_RAID_WARNING_REQ = 0xB042,
    NC_RAID_WARNING_ACK = 0xB043,
    NC_RAID_WARNING_BROAD_CMD = 0xB044,

    NC_USER_CONNECTION_NULL = 0xB400,
    NC_USER_CONNECTION_SET_ACCLOG_UP_CMD = 0xB401,
    NC_USER_CONNECTION_SET_WORLD_DOWN_CMD = 0xB402,
    NC_USER_CONNECTION_GET_LOGIN_USER_REQ = 0xB403,
    NC_USER_CONNECTION_GET_LOGIN_USER_ACK = 0xB404,
    NC_USER_CONNECTION_SET_USER_WORLD_LOGIN_CMD = 0xB405,
    NC_USER_CONNECTION_SET_USER_WORLD_LOGOUT_CMD = 0xB406,
    NC_USER_CONNECTION_CHANGE_CHAR_ID_REQ = 0xB409,
    NC_USER_CONNECTION_DB_CHANGE_CHAR_ID_REQ = 0xB40A,
    NC_USER_CONNECTION_DB_CHANGE_CHAR_ID_ACK = 0xB40B,
    NC_USER_CONNECTION_CHANGE_CHAR_ID_ACK = 0xB40C,
    NC_USER_CONNECTION_CHANGE_CHAR_ID_CMD = 0xB40D,
    NC_USER_CONNECTION_CHANGE_CHAR_ID_ACADEMY_MASTER_CMD = 0xB40E,
    NC_USER_CONNECTION_ZONE_CHANGE_CHAR_ID_CMD = 0xB40F,
    NC_USER_CONNECTION_CHANGE_CHAR_ID_ITEM_USE_REQ = 0xB410,
    NC_USER_CONNECTION_DB_CHANGE_CHAR_ID_ITEM_USE_REQ = 0xB411,
    NC_USER_CONNECTION_DB_CHANGE_CHAR_ID_ITEM_USE_ACK = 0xB412,
    NC_USER_CONNECTION_CHANGE_CHAR_ID_ITEM_USE_ACK = 0xB413,

    NC_AUCTION_NOTIFY_STORAGE_BOX_EXIST_ITEM_CMD = 0xB801,
    NC_AUCTION_EXPIRATION_TIME_REQ = 0xB802,
    NC_AUCTION_EXPIRATION_TIME_ACK = 0xB803,
    NC_AUCTION_NOTIFY_EXPIRATION_ITEM_CMD = 0xB804,
    NC_AUCTION_NOTIFY_WORLD_SELL_ITEM_CMD = 0xB805,
    NC_AUCTION_NOTIFY_SELL_ITEM_CMD = 0xB806,
    NC_AUCTION_SEARCH_REQ = 0xB807,
    NC_AUCTION_DB_SEARCH_REQ = 0xB808,
    NC_AUCTION_DB_SEARCH_ACK = 0xB809,
    NC_AUCTION_SEARCH_ACK = 0xB80A,
    NC_AUCTION_BUY_REQ = 0xB80B,
    NC_AUCTION_DB_BUY_REQ = 0xB80C,
    NC_AUCTION_DB_BUY_ACK = 0xB80D,
    NC_AUCTION_BUY_ACK = 0xB80E,
    NC_AUCTION_MY_REGISTER_GOOD_LIST_REQ = 0xB80F,
    NC_AUCTION_DB_MY_REGISTER_GOOD_LIST_REQ = 0xB810,
    NC_AUCTION_DB_MY_REGISTER_GOOD_LIST_ACK = 0xB811,
    NC_AUCTION_MY_REGISTER_GOOD_LIST_ACK = 0xB812,
    NC_AUCTION_REGISTER_GOOD_REQ = 0xB813,
    NC_AUCTION_DB_REGISTER_GOOD_REQ = 0xB814,
    NC_AUCTION_DB_REGISTER_GOOD_ACK = 0xB815,
    NC_AUCTION_REGISTER_GOOD_ACK = 0xB816,
    NC_AUCTION_REGISTER_CANCEL_GOOD_REQ = 0xB817,
    NC_AUCTION_DB_REGISTER_CANCEL_GOOD_REQ = 0xB818,
    NC_AUCTION_DB_REGISTER_CANCEL_GOOD_ACK = 0xB819,
    NC_AUCTION_REGISTER_CANCEL_GOOD_ACK = 0xB81A,
    NC_AUCTION_MY_STORAGE_BOX_REQ = 0xB81B,
    NC_AUCTION_DB_MY_STORAGE_BOX_REQ = 0xB81C,
    NC_AUCTION_DB_MY_STORAGE_BOX_ACK = 0xB81D,
    NC_AUCTION_MY_STORAGE_BOX_ACK = 0xB81E,
    NC_AUCTION_MY_STORAGE_ITEM_DETAIL_INFO_REQ = 0xB81F,
    NC_AUCTION_DB_MY_STORAGE_ITEM_DETAIL_INFO_REQ = 0xB820,
    NC_AUCTION_DB_MY_STORAGE_ITEM_DETAIL_INFO_SUC_ACK = 0xB821,
    NC_AUCTION_DB_MY_STORAGE_ITEM_DETAIL_INFO_FAIL_ACK = 0xB822,
    NC_AUCTION_MY_STORAGE_ITEM_DETAIL_INFO_SUC_ACK = 0xB823,
    NC_AUCTION_MY_STORAGE_ITEM_DETAIL_INFO_FAIL_ACK = 0xB824,
    NC_AUCTION_STORAGE_BOX_WITHDRAW_REQ = 0xB825,
    NC_AUCTION_DB_STORAGE_BOX_WITHDRAW_REQ = 0xB826,
    NC_AUCTION_DB_STORAGE_BOX_WITHDRAW_ACK = 0xB827,
    NC_AUCTION_STORAGE_BOX_WITHDRAW_ACK = 0xB828,

    NC_GAMBLE_NULL = 0xBC00,
    NC_GAMBLE_ZONE_PREVMAPNAME_CMD = 0xBC01,
    NC_GAMBLE_GAMBLEHOUSE_EXIT_REQ = 0xBC02,
    NC_GAMBLE_GAMBLEHOUSE_EXIT_ACK = 0xBC03,
    NC_GAMBLE_COIN_CHANGE_CMD = 0xBC04,
    NC_GAMBLE_EXCHANGECOIN_CHANGE_CMD = 0xBC05,
    NC_GAMBLE_COIN_DB_ADD_REQ = 0xBC06,
    NC_GAMBLE_COIN_DB_ADD_ACK = 0xBC07,
    NC_GAMBLE_EXCHANGEDCOIN_INIT_CMD = 0xBC09,
    NC_GAMBLE_EXCHANGEDCOIN_DB_INFO_REQ = 0xBC0A,
    NC_GAMBLE_EXCHANGEDCOIN_DB_INFO_ACK = 0xBC0B,
    NC_GAMBLE_COIN_EXCHANGEMACHINE_UI_OPEN_CMD = 0xBC0C,
    NC_GAMBLE_COIN_VIPCARD_UI_OPEN_REQ = 0xBC0D,
    NC_GAMBLE_COIN_VIPCARD_UI_OPEN_ACK = 0xBC0E,
    NC_GAMBLE_COIN_BUY_REQ = 0xBC0F,
    NC_GAMBLE_COIN_BUY_ACK = 0xBC10,
    NC_GAMBLE_COIN_DB_BUY_REQ = 0xBC11,
    NC_GAMBLE_COIN_DB_BUY_ACK = 0xBC12,
    NC_GAMBLE_COIN_SELL_REQ = 0xBC13,
    NC_GAMBLE_COIN_SELL_ACK = 0xBC14,
    NC_GAMBLE_COIN_DB_SELL_REQ = 0xBC15,
    NC_GAMBLE_COIN_DB_SELL_ACK = 0xBC16,
    NC_GAMBLE_TYPE_AND_WHERE_STAND_REQ = 0xBC17,
    NC_GAMBLE_TYPE_AND_WHERE_STAND_ACK = 0xBC18,
    NC_GAMBLE_COIN_DB_USE_COINITEM_REQ = 0xBC19,
    NC_GAMBLE_COIN_DB_USE_COINITEM_ACK = 0xBC1A,
    NC_GAMBLE_COIN_USE_COINITEM_MESSAGE_CMD = 0xBC1B,
    NC_GAMBLE_ENTER_PLAYER_DIRECT_CMD = 0xBC1C,
    NC_GAMBLE_WORLD_PREVMAPNAME_CMD = 0xBC1D,
    NC_GAMBLE_PLAYERACT_CMD = 0xBC1E,
    NC_GAMBLE_DICE_TAISAI_GAME_JOIN_REQ = 0xBC64,
    NC_GAMBLE_DICE_TAISAI_GAME_JOIN_ACK = 0xBC65,
    NC_GAMBLE_DICE_TAISAI_GAME_JOIN_CMD = 0xBC66,
    NC_GAMBLE_DICE_TAISAI_GAME_BETTING_INFO_CMD = 0xBC67,
    NC_GAMBLE_DICE_TAISAI_GAME_LEAVE_REQ = 0xBC68,
    NC_GAMBLE_DICE_TAISAI_GAME_LEAVE_ACK = 0xBC69,
    NC_GAMBLE_DICE_TAISAI_GAME_LEAVE_CMD = 0xBC6A,
    NC_GAMBLE_DICE_TAISAI_ALL_RANK_REQ = 0xBC6B,
    NC_GAMBLE_DICE_TAISAI_DB_ALL_RANK_REQ = 0xBC6C,
    NC_GAMBLE_DICE_TAISAI_DB_ALL_RANK_ACK = 0xBC6D,
    NC_GAMBLE_DICE_TAISAI_ALL_RANK_ACK = 0xBC6E,
    NC_GAMBLE_DICE_TAISAI_CURR_RANK_REQ = 0xBC6F,
    NC_GAMBLE_DICE_TAISAI_CURR_RANK_ACK = 0xBC70,
    NC_GAMBLE_DICE_TAISAI_BETTING_REQ = 0xBC71,
    NC_GAMBLE_DICE_TAISAI_BETTING_ACK = 0xBC72,
    NC_GAMBLE_DICE_TAISAI_BETTING_CMD = 0xBC73,
    NC_GAMBLE_DICE_TAISAI_BETTING_CANCEL_REQ = 0xBC74,
    NC_GAMBLE_DICE_TAISAI_BETTING_CANCEL_ACK = 0xBC75,
    NC_GAMBLE_DICE_TAISAI_BETTING_CANCEL_CMD = 0xBC76,
    NC_GAMBLE_DICE_TAISAI_DICE_ROLL_CMD = 0xBC77,
    NC_GAMBLE_DICE_TAISAI_DB_DICE_ROLL_RESULT_REQ = 0xBC78,
    NC_GAMBLE_DICE_TAISAI_DB_DICE_ROLL_RESULT_ACK = 0xBC79,
    NC_GAMBLE_DICE_TAISAI_DB_DICE_ROLL_RESULT_LOG_CMD = 0xBC7A,
    NC_GAMBLE_DICE_TAISAI_DICE_ROLL_RESULT_CMD = 0xBC7B,
    NC_GAMBLE_DICE_TAISAI_DICE_ROLL_RESULT_EMOTION_CMD = 0xBC7C,
    NC_GAMBLE_DICE_TAISAI_LARGE_AMOUNT_REQ = 0xBC7D,
    NC_GAMBLE_DICE_TAISAI_LARGE_AMOUNT_ACK = 0xBC7E,
    NC_GAMBLE_DICE_TAISAI_LARGE_AMOUNT_CMD = 0xBC7F,
    NC_GAMBLE_DICE_TAISAI_BET_START_CMD = 0xBC80,
    NC_GAMBLE_DICE_TAISAI_TIMER_CMD = 0xBC81,
    NC_GAMBLE_SLOTMACHINE_GAME_JOIN_REQ = 0xBCC8,
    NC_GAMBLE_SLOTMACHINE_GAME_JOIN_ACK = 0xBCC9,
    NC_GAMBLE_SLOTMACHINE_GAME_LEAVE_REQ = 0xBCCA,
    NC_GAMBLE_SLOTMACHINE_GAME_LEAVE_ACK = 0xBCCB,
    NC_GAMBLE_SLOTMACHINE_START_REQ = 0xBCCC,
    NC_GAMBLE_SLOTMACHINE_START_ACK = 0xBCCD,
    NC_GAMBLE_SLOTMACHINE_STOPBUTTON_REQ = 0xBCCE,
    NC_GAMBLE_SLOTMACHINE_STOPBUTTON_ACK = 0xBCCF,
    NC_GAMBLE_SLOTMACHINE_WHEELSTOP_REQ = 0xBCD0,
    NC_GAMBLE_SLOTMACHINE_WHEELSTOP_ACK = 0xBCD1,
    NC_GAMBLE_SLOTMACHINE_STAND_UP_CMD = 0xBCD2,
    NC_GAMBLE_SLOTMACHINE_DB_RESULT_REQ = 0xBCD3,
    NC_GAMBLE_SLOTMACHINE_DB_RESULT_ACK = 0xBCD4,
    NC_GAMBLE_SLOTMACHINE_DB_GAMEINFO_REQ = 0xBCD5,
    NC_GAMBLE_SLOTMACHINE_DB_GAMEINFO_ACK = 0xBCD6,
    NC_GAMBLE_SLOTMACHINE_JACKPOTINFO_CMD = 0xBCD8,
    NC_GAMBLE_SLOTMACHINE_JACKPOTRANKING_REQ = 0xBCD9,
    NC_GAMBLE_SLOTMACHINE_JACKPOTRANKING_ACK = 0xBCDA,
    NC_GAMBLE_SLOTMACHINE_WINRANKING_REQ = 0xBCDB,
    NC_GAMBLE_SLOTMACHINE_WINRANKING_ACK = 0xBCDC,
    NC_GAMBLE_SLOTMACHINE_SOMEONE_GET_JACKPOT_CMD = 0xBCDD,

    NC_COMMAND_MATCH_INSTANCE_DUNGEON_dummy = 0xC000,

    NC_COLLECT_NULL = 0xC400,
    NC_COLLECT_PEEPING_REQ = 0xC401,
    NC_COLLECT_PEEPING_DB_REQ = 0xC402,
    NC_COLLECT_PEEPING_DB_COLLECT_ACK = 0xC403,
    NC_COLLECT_PEEPING_DB_COLLECT_BOOKMARK_ACK = 0xC404,
    NC_COLLECT_PEEPING_COLLECT_ACK = 0xC405,
    NC_COLLECT_PEEPING_COLLECT_BOOKMARK_ACK = 0xC406,
    NC_COLLECT_CARDOPEN_CMD = 0xC407,
    NC_COLLECT_CARDREGIST_REQ = 0xC408,
    NC_COLLECT_REGIST_REQ = 0xC409,
    NC_COLLECT_REGIST_ACK = 0xC40A,
    NC_COLLECT_CARDREGIST_ACK = 0xC40B,
    NC_COLLECT_BOOKMARK_REGIST_REQ = 0xC40C,
    NC_COLLECT_BOOKMARK_REGIST_DB_REQ = 0xC40D,
    NC_COLLECT_BOOKMARK_REGIST_DB_ACK = 0xC40E,
    NC_COLLECT_BOOKMARK_REGIST_ACK = 0xC40F,
    NC_COLLECT_REWARD_REQ = 0xC410,
    NC_COLLECT_REWARD_DB_REQ = 0xC411,
    NC_COLLECT_REWARD_DB_ACK = 0xC412,
    NC_COLLECT_REWARD_ACK = 0xC413,
    NC_COLLECT_CHARACTERDB_UP_GET_CARDCOUNT_CMD = 0xC414,

    NC_SYSLOG_NULL = 0xC800,
    NC_SYSLOG_ACCOUNT_LOGIN_SUCCESS = 0xC801,
    NC_SYSLOG_ACCOUNT_LOGIN_FAILURE = 0xC802,
    NC_SYSLOG_ACCOUNT_LOGOUT = 0xC803,
    NC_SYSLOG_CHAR_CREATED = 0xC804,
    NC_SYSLOG_CHAR_DELETED = 0xC805,
    NC_SYSLOG_CHAR_ENTER_GAME = 0xC806,
    NC_SYSLOG_CHAR_LEAVE_GAME = 0xC807,
    NC_SYSLOG_CHAR_LEVEL_UP = 0xC808,
    NC_SYSLOG_CHAR_ZONE_TRANSITION = 0xC809,
    NC_SYSLOG_CHAR_DEATH = 0xC80A,
    NC_SYSLOG_CHAR_VICTORY = 0xC80B,
    NC_SYSLOG_CHAR_LOOT = 0xC80C,
    NC_SYSLOG_CHAR_ITEM_BUY = 0xC80D,
    NC_SYSLOG_CHAR_ITEM_SELL = 0xC80E,
    NC_SYSLOG_CHAR_QUEST_STARTED = 0xC80F,
    NC_SYSLOG_CHAR_QUEST_FINISHED = 0xC810,
    NC_SYSLOG_SERVER_CCU = 0xC811,
    NC_SYSLOG_CHAR_ITEMMONEY_BUY = 0xC814,
    NC_SYSLOG_CHAR_ITEM_REBUY = 0xC815,
    NC_GAMIGO_NEW_TUTORIAL_STORE_STEP = 0xC817,

    NC_MOVER_NULL = 0xCC00,
    NC_MOVER_RIDE_ON_REQ = 0xCC01,
    NC_MOVER_RIDE_ON_CMD = 0xCC02,
    NC_MOVER_RIDE_ON_FAIL_CMD = 0xCC03,
    NC_MOVER_SOMEONE_RIDE_ON_CMD = 0xCC04,
    NC_MOVER_RIDE_OFF_REQ = 0xCC05,
    NC_MOVER_RIDE_OFF_CMD = 0xCC06,
    NC_MOVER_RIDE_OFF_FAIL_CMD = 0xCC07,
    NC_MOVER_SOMEONE_RIDE_OFF_CMD = 0xCC08,
    NC_MOVER_FEEDING_ERROR_CMD = 0xCC09,
    NC_MOVER_HUNGRY_CMD = 0xCC0A,
    NC_MOVER_LINKDATA_WORLD_CMD = 0xCC0B,
    NC_MOVER_LINKDATA_ZONE_CMD = 0xCC0C,
    NC_MOVER_MOVESPEED_CMD = 0xCC0D,
    NC_MOVER_SKILLBASH_OBJ_CAST_REQ = 0xCC0E,
    NC_MOVER_SKILLBASH_FLD_CAST_REQ = 0xCC0F,

    NC_EVENT_NULL = 0xD000,
    NC_EVENT_GET_ALL_EVENT_INFO_REQ = 0xD001,
    NC_EVENT_GET_ALL_EVENT_INFO_ACK = 0xD002,
    NC_EVENT_ADD_EVENT_REQ = 0xD003,
    NC_EVENT_ADD_EVENT_ACK = 0xD004,
    NC_EVENT_UPDATE_EVENT_REQ = 0xD005,
    NC_EVENT_UPDATE_EVENT_ACK = 0xD006,
    NC_EVENT_DEL_EVENT_REQ = 0xD007,
    NC_EVENT_DEL_EVENT_ACK = 0xD008,
    NC_EVENT_SET_ALL_READY_REQ = 0xD009,
    NC_EVENT_SET_ALL_READY_ACK = 0xD00A,
    NC_EVENT_ADD_UPDATE_EVENT_CMD = 0xD00B,
    NC_EVENT_DEL_EVENT_CMD = 0xD00C,

    NC_PET_NULL = 0xD400,
    NC_PET_SET_TENDENCY_DB_REQ = 0xD401,
    NC_PET_SET_NAME_DB_REQ = 0xD403,
    NC_PET_SET_NAME_DB_ACK = 0xD404,
    NC_PET_ASK_NEW_NAME_REQ = 0xD405,
    NC_PET_ASK_NEW_NAME_ACK = 0xD406,
    NC_PET_SET_NAME_REQ = 0xD407,
    NC_PET_SET_NAME_ACK = 0xD408,
    NC_PET_SET_NAME_CANCEL_REQ = 0xD409,
    NC_PET_SET_NAME_CANCEL_ACK = 0xD40A,
    NC_PET_LOAD_INFO_DB_REQ = 0xD40B,
    NC_PET_LOAD_INFO_DB_ACK = 0xD40C,
    NC_PET_CREATE_DB_REQ = 0xD40D,
    NC_PET_CREATE_DB_ACK = 0xD40E,
    NC_PET_REMOVE_DB_REQ = 0xD40F,
    NC_PET_REMOVE_DB_ACK = 0xD410,
    NC_PET_USE_ITEM_FAIL_ACK = 0xD411,
    NC_PET_LINK_RESUMMON_CMD = 0xD412,
    NC_PET_SET_NAME_CMD = 0xD413
};
#pragma endregion 
