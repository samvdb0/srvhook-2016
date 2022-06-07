#pragma once
#include <deque>

struct ItemDataBox;
struct MobDataBox;
union NETCOMMAND;

namespace ShineObjectClass {
	class ShineObject;
    class ShinePlayer;
    class ShineMobileObject;
    class ShineMob;
}

template<typename T>
struct ListStruct
{
    T* ls_Content;
    ushort ls_Next;
    ushort ls_Prev;
    char ls_IsActiv;
    ushort ls_Event;
};

template<typename T>
struct List
{
    void* vfptr;

    void l_MakeList(ushort size) { CallMemberFunction<List, void, ushort>(0x00409890, this, size); }

    unsigned __int16 l_MaxSize;
    char _pad[0x2];
    ListStruct<T>* l_Array;
    struct
	{
        unsigned __int16 empty;
        unsigned __int16 store;
    } l_Finger;
	
    void* l_ListArray;
    unsigned __int16 l_ListNum;
    char _pad2[0x2];
};

template<typename T>
struct CommonList : List<T>
{
    T* cl_Array;
};


union Name1
{
    char n1_name[4];
    unsigned int n1_code;
};

union Name2
{
    char n2_name[8];
    unsigned int n2_code[2];
};

union Name3
{
    static Name3 Create(const char* str)
    {
        auto token = Name3();
        strcpy_s(token.n3_name, str);
        return token;
    }

    char n3_name[12];
    unsigned int n3_code[3];
};

union Name4
{
    char n4_name[16];
    unsigned int n4_code[4];
};

union Name5
{
    char n5_name[20];
    unsigned int n5_code[5];
};

union Name8
{
    char n8_name[32];
    unsigned int n8_code[8];
};

struct String
{
    virtual void _Delete(uint);

    char* chData;
    int stringLength;
    int allocSize;
};

#pragma pack(push, 1)
union ORToken
{
    HOOK_PUB_S ORToken Create(const char* str)
    {
        auto token = ORToken();
        strcpy_s(token.ort_Name, str);
        return token;
    }
	
    HOOK_PUB_M char* ort_GetString(char* buff)
    {
        return CallMemberFunction<ORToken, char*, char*>(0x0064D4F0, this, buff);
    }
	
    char ort_Name[20];
    unsigned int ort_Code[5];
};
#pragma pack(pop)

struct BitANDInt
{
    unsigned int value;
    unsigned int mask;
};

struct BTree
{
    unsigned int operator[](const char* string)
    {
        return CallMemberFunction<BTree, unsigned int, const char*>(0x0063CC30, this, string);
    }

    unsigned int bt_id;
    BTree* bt_subtree[256];
};

struct CThread
{
    char activ;
    char stop;
    char _pad[0x2];
    void* handle;
    unsigned int id;
    unsigned int looping;
};

struct CCsl
{
    char _size[0x4F8];
};

struct CServerInfo
{
    struct MY_SERVER
    {
        char* pServiceName;
        char* pDisplayName;
        int nServerID;
        int nWorldNo;
        int nZoneNo;
    };

    CCsl m_Csl;
};

struct ZoneServerInfo
{
    CServerInfo serverinfo;
    CServerInfo::MY_SERVER myserver;
    Name4 worldname;
    char servergroup[32];
    char ConnectSocket_BindIP[16];
};

struct CIOCP_Process_Interfece
{
    char _size[0xC];
};

struct CIOCP_Process
{
    CIOCP_Process_Interfece* m_pProcess;
    CIOCP_Process_Interfece m_DefautProcess;
};

struct CIOCP
{
    struct WORKER
    {
        int WorkerID;
        int WorkerStatus;
        void* hThread;
        unsigned int ThreadID;
        CIOCP* pIOCP;
    };

    enum IOCP_WORK_TYPE
    {
        READ = 0x0,
        WRITE = 0x1,
        CLOSE = 0x2,
        STOP = 0x3,
    };

    struct IOCP_OVERLAPPED : _OVERLAPPED
    {
        IOCP_WORK_TYPE Type;
        CIOCP_Process* pIOCP_Process;
        void* pData;
    };

    void* m_HandleIOCP;
    int m_NumOfWorkThread;
    int m_ActiveWorker;
    WORKER* m_pWorkThreads;
    IOCP_OVERLAPPED m_Overlapped_Stop;
};

struct CSocket_Acceptor_Process
{
    char _size[0x8];
};

struct CSocket_Acceptor
{
    enum LISTEN_WORK
    {
        LISTEN_WORK_EMPTY = 0x0,
        LISTEN_WORK_ADD = 0x1,
        LISTEN_WORK_ADD_ERROR = 0x2,
        LISTEN_WORK_ACTIVE = 0x3,
        LISTEN_WORK_DEL = 0x4,
    };

    struct LISTEN_SOCKET
    {
        LISTEN_WORK Work;
        unsigned int Socket;
        sockaddr SocketAddr;
        char IP[64];
        int PortNo;
        int BacklogCount;
        unsigned int UserData;
    };

    struct ACCEPTED_SOCKET_INFO
    {
        unsigned int Socket;
        sockaddr_in SocketAddr;
        unsigned int UserData;
        unsigned int AcceptTime;
    };

    unsigned int m_ListenSocket;
    sockaddr m_ListenSocketAddr;
    LISTEN_SOCKET m_ListenArray[10];
    int m_NumOfListen;
    _RTL_CRITICAL_SECTION m_ListenBF_CS;
    ACCEPTED_SOCKET_INFO m_AcceptedRing[1300];
    int m_NumOfAccepted;
    unsigned int m_Accepted_Input;
    unsigned int m_Accepted_Output;
    _RTL_CRITICAL_SECTION m_AcceptBF_CS;
    CSocket_Acceptor_Process m_Acceptor_Process;
    int m_bActiveAcceptThread;
    int m_bAcceptThreadStop;
    timeval m_Listen_TimeOut;
    void* m_hAcceptThread;
    unsigned int m_AcceptThreadID;
};

struct ClientSessionManager
{
    void* vfptr;
    void* m_pSessionListArray;
    int m_MaxSessions;
    int m_NumSessions;
	
    char _size[0x2C - 16];
};

struct OptionReader
{
    bool or_Read(const char* filename)
    {
        return CallMemberFunction<OptionReader, bool, const char*>(0x00646BF0, this, filename);
    }

    int or_ErrorLine()
    {
        return CallMemberFunction<OptionReader, int>(0x00645F00, this);
    }

    void* or_SelectFromOrder(ORToken table, int order)
    {
        return CallMemberFunction<OptionReader, void*, ORToken, int>(0x00647A60, this, table, order);
    }

    void* or_SelectFrom(ORToken table, const char* column, const char* content, int skip)
    {
        return CallMemberFunction<OptionReader, void*, ORToken, const char*, const char*, int>(0x00647C00, this, table, column, content, skip);
    }

    const char* or_ErrorString()
    {
        return CallMemberFunction<OptionReader, const char*>(0x00645F10, this);
    }

    OptionReader()
    {
        CallMemberFunction<OptionReader, void>(0x00646A30, this);
    }

    ~OptionReader()
    {
        CallMemberFunction<OptionReader, void>(0x006467D0, this);
    }

    char _size[0x10854];
};

struct __declspec(align(8)) LuaScriptFactor
{
    long double lsf_Factor;
    bool lsf_IsFreeze;
    bool lsf_IsRecover;
};

struct LuaArgument
{
    int Count;
    int Interval;
    int MaxSkip;
    int Summary;
    int SkipNumber;
    int CertifyArg;
};

struct ShineObjectHandleUnion
{
    ushort sohu_Handle;
};

struct SlantedObjectList
{
    char _size[0x60];
};

struct SHINE_XY_TYPE
{
    unsigned int x;
    unsigned int y;
};

struct Location
{
    SHINE_XY_TYPE* location;
    char* direct;
};

struct LayerAndTemp
{
    char _size[0xC];
};

enum ABSTATEINDEX
{
    STA_SEVERBONE = 0x0,
    STA_REDSLASH = 0x1,
    STA_BATTLEBLOWSTUN = 0x2,
    STA_MIGHTYSOULMAIN = 0x3,
    STA_MIGHTYSOUL = 0x4,
    STA_MORALEDECREASEWC = 0x5,
    STA_SPEEDSHIELD = 0x6,
    STA_HARMDEFECT = 0x7,
    STA_BERSEKERFRENZY = 0x8,
    STA_SHOCKBLADESTUN = 0x9,
    STA_MIGHTYSOUL2 = 0xA,
    STA_MIGHTYSOUL3 = 0xB,
    STA_MIGHTYSOUL4 = 0xC,
    STA_MIGHTYSOUL5 = 0xD,
    STA_VIOLENCE = 0xE,
    STA_BUCKLER = 0xF,
    STA_NEGLECT = 0x10,
    STA_BREAK = 0x11,
    STA_BLESSINGMAIN = 0x12,
    STA_BLESSING = 0x13,
    STA_SAFEPROTECTION = 0x14,
    STA_PSYCHICBLUNTSTUN = 0x15,
    STA_PSYCHICCHOPBLOOD = 0x16,
    STA_DARKNESSPROTECTION = 0x17,
    STA_RESTORE = 0x18,
    STA_HITPROTECTION = 0x19,
    STA_MENTALSHOUTMAIN = 0x1A,
    STA_MENTALSHOUT = 0x1B,
    STA_DIVINESHIELD = 0x1C,
    STA_DIVINEWEAPONWCMAIN = 0x1D,
    STA_DIVINEWEAPONWC = 0x1E,
    STA_SACRIFICE = 0x1F,
    STA_CROSSCASTINGCOOLTIME = 0x20,
    STA_PANICFORCEMR = 0x21,
    STA_REVERSEORDER = 0x22,
    STA_HORRORFORCESTR = 0x23,
    STA_BLESSING2 = 0x24,
    STA_BLESSING3 = 0x25,
    STA_BLESSING4 = 0x26,
    STA_BLESSING5 = 0x27,
    STA_MENTALSHOUT2 = 0x28,
    STA_MENTALSHOUT3 = 0x29,
    STA_MENTALSHOUT4 = 0x2A,
    STA_MENTALSHOUT5 = 0x2B,
    STA_DIVINEWEAPONWC2 = 0x2C,
    STA_DIVINEWEAPONWC3 = 0x2D,
    STA_DIVINEWEAPONWC4 = 0x2E,
    STA_DIVINEWEAPONWC5 = 0x2F,
    STA_REBIRTH = 0x30,
    STA_DEADLYBLESSING = 0x31,
    STA_DODGE = 0x32,
    STA_PURYIMPACTSTUN = 0x33,
    STA_FORESTWIND = 0x34,
    STA_WINDCHARGEMAIN = 0x35,
    STA_WINDCHARGE = 0x36,
    STA_BONEARROW = 0x37,
    STA_SPIRITTHORNENTANGLE = 0x38,
    STA_POISONSHOT = 0x39,
    STA_BITEARROW = 0x3A,
    STA_MISTCHARGEMAIN = 0x3B,
    STA_MISTCHARGE = 0x3C,
    STA_SPIRITFOG = 0x3D,
    STA_HAWKTALONATKSPEED = 0x3E,
    STA_NATURECASTINGCOOLTIME = 0x3F,
    STA_PIERCINGGUARD = 0x40,
    STA_SHOCKSCREAMWC = 0x41,
    STA_STINGERUPTIONSLOW = 0x42,
    STA_WINDCHARGE2 = 0x43,
    STA_WINDCHARGE3 = 0x44,
    STA_WINDCHARGE4 = 0x45,
    STA_WINDCHARGE5 = 0x46,
    STA_MISTCHARGE2 = 0x47,
    STA_MISTCHARGE3 = 0x48,
    STA_MISTCHARGE4 = 0x49,
    STA_MISTCHARGE5 = 0x4A,
    STA_HIDE = 0x4B,
    STA_BLIND = 0x4C,
    STA_ENTRAPHIDE = 0x4D,
    STA_ICEBOLT = 0x4E,
    STA_LIGHTNINGBOLT = 0x4F,
    STA_BLUR = 0x50,
    STA_SOULEDGE = 0x51,
    STA_RINGSHIELD = 0x52,
    STA_ICEBLASTSTUN = 0x53,
    STA_CHAINLIGHTNINGSTUN = 0x54,
    STA_DRAINMINDFEAR = 0x55,
    STA_CHAINCASTINGCOOLTIME = 0x56,
    STA_CURSEMAGICCASTIME = 0x57,
    STA_FROSTNOVA = 0x58,
    STA_THUNDERBOLT = 0x59,
    STA_SOULEDGEMAIN = 0x5A,
    STA_SOULEDGE2 = 0x5B,
    STA_SOULEDGE3 = 0x5C,
    STA_SOULEDGE4 = 0x5D,
    STA_SOULEDGE5 = 0x5E,
    STA_DEEPER = 0x5F,
    STA_MESMERIZE = 0x60,
    STA_POLYMORPH = 0x61,
    STA_ICEFIELD = 0x62,
    STA_MARASTUN = 0x63,
    STA_KINGSLIMEBLOODING = 0x64,
    STA_MARLONEENTANGLE = 0x65,
    STA_NOXENTANGLE = 0x66,
    STA_SKELKNIGHTBLOODING = 0x67,
    STA_ROBOACPLUS = 0x68,
    STA_GOKINGSTUN = 0x69,
    STA_GOKINGSTRRATE = 0x6A,
    STA_KINGCALLACPLUS = 0x6B,
    STA_GHKNIGHTENTANGLE = 0x6C,
    STA_HUNGRYWOLFBLOODING = 0x6D,
    STA_KQSKELKNIGHTENTANGLE = 0x6E,
    STA_MARLONECAPTAINATKSPD = 0x6F,
    STA_ARCHMAGEBOOKSTUN = 0x70,
    STA_GHOSTFEAR = 0x71,
    STA_KQ_BOSSROBOFEAR = 0x72,
    STA_KQ_BOSSROBO2FEAR = 0x73,
    STA_NOXSK2BLOODING = 0x74,
    STA_KQ_G_TBRAIDERCURSE = 0x75,
    STA_ELFKNIGHTSOULDEXCURSE = 0x76,
    STA_JOKERTRUMPYTHCURSE = 0x77,
    STA_KEBINGCURSE = 0x78,
    STA_KINGCRABCURSE = 0x79,
    STA_NAVARCURSE = 0x7A,
    STA_MARACURSE = 0x7B,
    STA_SKELWARRIORCURSE = 0x7C,
    STA_ARCHMAGEBOOKCURSE = 0x7D,
    STA_KARATEMPLERCURSE = 0x7E,
    STA_SMARTPHINOCURSE = 0x7F,
    STA_MARLONESOLDIERCURSE = 0x80,
    STA_OLDFOXCURSE = 0x81,
    STA_GOBLINMAGECURSE = 0x82,
    STA_HARKANCURSE = 0x83,
    STA_DISHARKANCURSE = 0x84,
    STA_STONIECURSE = 0x85,
    STA_OGRECURSE = 0x86,
    STA_MARASAILORCURSE = 0x87,
    STA_OLDARCHONCURSE = 0x88,
    STA_KINGMUSHROOMCURSE = 0x89,
    STA_BCTRUMPYCURSE = 0x8A,
    STA_KQ_K_BOSSPHINOCURSE = 0x8B,
    STA_KQ_K_PHINOFLIECURSE = 0x8C,
    STA_TORTURERBLOODING = 0x8D,
    STA_SHARPBOARBLOODING = 0x8E,
    STA_FOBLOODING = 0x8F,
    STA_BABYWEREBEARBLOODING = 0x90,
    STA_SENIORTORTURERBLOODING = 0x91,
    STA_JEWELKEEPERBLOODING = 0x92,
    STA_SHYLPHBLOODING = 0x93,
    STA_SGTRUMPYBLOODING = 0x94,
    STA_KQ_K_SOLIDERBLOODING = 0x95,
    STA_SKELKNIGHTDISEASE = 0x96,
    STA_MOB1SLOW = 0x97,
    STA_MOB2SLOW = 0x98,
    STA_MOB3SLOW = 0x99,
    STA_MOB4SLOW = 0x9A,
    STA_MOB5SLOW = 0x9B,
    STA_MOB1STUN = 0x9C,
    STA_MOB2STUN = 0x9D,
    STA_MOB3STUN = 0x9E,
    STA_MOB4STUN = 0x9F,
    STA_MOB5STUN = 0xA0,
    STA_KQMARASTUN = 0xA1,
    STA_KQGOBLEKINGSTUN = 0xA2,
    STA_DIAMASTERSTUN = 0xA3,
    STA_ANCIENTSTONIESTUN = 0xA4,
    STA_MOB1ENTANGLE = 0xA5,
    STA_MOB2ENTANGLE = 0xA6,
    STA_MOB3ENTANGLE = 0xA7,
    STA_MOB4ENTANGLE = 0xA8,
    STA_MOB5ENTANGLE = 0xA9,
    STA_KQMARLONEENTANGLE = 0xAA,
    STA_LEGENDARYTREEENTANGLE = 0xAB,
    STA_GIANTELVENTREEENTANGLE = 0xAC,
    STA_MOB1POISON = 0xAD,
    STA_MOB2POISON = 0xAE,
    STA_MOB3POISON = 0xAF,
    STA_MOB4POISON = 0xB0,
    STA_MOB5POISON = 0xB1,
    STA_MOB6POISON = 0xB2,
    STA_DIATRUMPYPOISON = 0xB3,
    STA_MOB1DISEASE1 = 0xB4,
    STA_MOB2DISEASE1 = 0xB5,
    STA_MOB3DISEASE1 = 0xB6,
    STA_MOB4DISEASE1 = 0xB7,
    STA_MOB5DISEASE1 = 0xB8,
    STA_MOB6DISEASE1 = 0xB9,
    STA_MOB1DISEASE2 = 0xBA,
    STA_MOB2DISEASE2 = 0xBB,
    STA_MOB3DISEASE2 = 0xBC,
    STA_MOB4DISEASE2 = 0xBD,
    STA_MOB5DISEASE2 = 0xBE,
    STA_MOB6DISEASE2 = 0xBF,
    STA_MOB1DISEASE3 = 0xC0,
    STA_MOB2DISEASE3 = 0xC1,
    STA_MOB3DISEASE3 = 0xC2,
    STA_MOB4DISEASE3 = 0xC3,
    STA_MOB5DISEASE3 = 0xC4,
    STA_MOB6DISEASE3 = 0xC5,
    STA_MOBIMMORTAL = 0xC6,
    STA_MOBINVISIBLE = 0xC7,
    STA_MOBMRPLUS = 0xC8,
    STA_ACMODE = 0xC9,
    STA_MRMODE = 0xCA,
    STA_HELGAACMINUS = 0xCB,
    STA_BESTLOWCONHPPOTION = 0xCC,
    STA_LOWCONHPPOTION = 0xCD,
    STA_NORCONHPPOTION = 0xCE,
    STA_HIGHCONHPPOTION = 0xCF,
    STA_BESTHIGHCONHPPOTION = 0xD0,
    STA_BESTLOWCONSPPOTION = 0xD1,
    STA_LOWCONSPPOTION = 0xD2,
    STA_NORCONSPPOTION = 0xD3,
    STA_HIGHCONSPPOTION = 0xD4,
    STA_BESTHIGHCONSPPOTION = 0xD5,
    STA_BESTLOWTHSCROLL = 0xD6,
    STA_LOWTHSCROLL = 0xD7,
    STA_NORTHSCROLL = 0xD8,
    STA_HIGHTHSCROLL = 0xD9,
    STA_BESTHIGHTHSCROLL = 0xDA,
    STA_BESTLOWTBSCROLL = 0xDB,
    STA_LOWTBSCROLL = 0xDC,
    STA_NORTBSCROLL = 0xDD,
    STA_HIGHTBSCROLL = 0xDE,
    STA_BESTHIGHTBSCROLL = 0xDF,
    STA_BESTLOWMRSCROLL = 0xE0,
    STA_LOWMRSCROLL = 0xE1,
    STA_NORMRSCROLL = 0xE2,
    STA_HIGHMRSCROLL = 0xE3,
    STA_BESTHIGHMRSCROLL = 0xE4,
    STA_BESTLOWACSCROLL = 0xE5,
    STA_LOWACSCROLL = 0xE6,
    STA_NORACSCROLL = 0xE7,
    STA_HIGHACSCROLL = 0xE8,
    STA_BESTHIGHACSCROLL = 0xE9,
    STA_BESTLOWCRISCROLL = 0xEA,
    STA_LOWCRISCROLL = 0xEB,
    STA_NORCRISCROLL = 0xEC,
    STA_HIGHCRISCROLL = 0xED,
    STA_BESTHIGHCRISCROLL = 0xEE,
    STA_BESTLOWMAXHPSCROLL = 0xEF,
    STA_LOWMAXHPSCROLL = 0xF0,
    STA_NORMAXHPSCROLL = 0xF1,
    STA_HIGHMAXHPSCROLL = 0xF2,
    STA_BESTHIGHMAXHPSCROLL = 0xF3,
    STA_BESTLOWMAXSPSCROLL = 0xF4,
    STA_LOWMAXSPSCROLL = 0xF5,
    STA_NORMAXSPSCROLL = 0xF6,
    STA_HIGHMAXSPSCROLL = 0xF7,
    STA_BESTHIGHMAXSPSCROLL = 0xF8,
    STA_BESTLOWSTRCRISCROLL = 0xF9,
    STA_LOWSTRCRISCROLL = 0xFA,
    STA_NORSTRCRISCROLL = 0xFB,
    STA_HIGHSTRCRISCROLL = 0xFC,
    STA_BESTHIGHSTRCRISCROLL = 0xFD,
    STA_BESTLOWDEXSCROLL = 0xFE,
    STA_LOWDEXSCROLL = 0xFF,
    STA_NORDEXSCROLL = 0x100,
    STA_HIGHDEXSCROLL = 0x101,
    STA_BESTHIGHDEXSCROLL = 0x102,
    STA_BESTLOWACMRSCROLL = 0x103,
    STA_LOWACMRSCROLL = 0x104,
    STA_NORACMRSCROLL = 0x105,
    STA_HIGHACMRSCROLL = 0x106,
    STA_BESTHIGHACMRSCROLL = 0x107,
    STA_NORMSSCROLL = 0x108,
    STA_LOWPSNRESIPOTION = 0x109,
    STA_NORPSNRESIPOTION = 0x10A,
    STA_HIGHPSNRESIPOTION = 0x10B,
    STA_LOWDSSRESIPOTION = 0x10C,
    STA_NORDSSRESIPOTION = 0x10D,
    STA_HIGHDSSRESIPOTION = 0x10E,
    STA_LOWCURRESIPOTION = 0x10F,
    STA_NORCURRESIPOTION = 0x110,
    STA_HIGHCURRESIPOTION = 0x111,
    STA_ALLCURRESIPOTION = 0x112,
    STA_ALLDSSRESIPOTION = 0x113,
    STA_ALLPSNRESIPOTION = 0x114,
    STA_LOWMSSCROLL = 0x115,
    STA_HIGHMSSCROLL = 0x116,
    STA_BESTMSSCROLL = 0x117,
    STA_BESTLOWMSSCROLL = 0x118,
    STA_RAMAPOTION01 = 0x119,
    STA_RAMAPOTION02 = 0x11A,
    STA_RAMAPOTION03 = 0x11B,
    STA_RAMAPOTION04 = 0x11C,
    STA_RAMAPOTION05 = 0x11D,
    STA_RAMAPOTION06 = 0x11E,
    STA_RAMAPOTION07 = 0x11F,
    STA_GMHIDEMODE = 0x120,
    STA_OBSERVERHIDEMODE = 0x121,
    STA_QUESTENTANGLE = 0x122,
    STA_IMMORTAL = 0x123,
    STA_KEEPFROMCHAT = 0x124,
    STA_WEDDINGBUFF = 0x125,
    STA_WEDDINGSUB01 = 0x126,
    STA_WEDDINGSUB02 = 0x127,
    STA_SOLEFIRE = 0x128,
    STA_ACAMSBUF10PMAIN = 0x129,
    STA_ACAMSBUF10P = 0x12A,
    STA_ACAMSBUF7PMAIN = 0x12B,
    STA_ACAMSBUF7P = 0x12C,
    STA_ACAGENALBUF = 0x12D,
    STA_NATURALENEMY = 0x12E,
    STA_KALBANPOISON = 0x12F,
    STA_KALBANDISEASE = 0x130,
    STA_KALBANSTUN = 0x131,
    STA_COMMONSTUN01 = 0x132,
    STA_COMMONSTUN02 = 0x133,
    STA_COMMONSTUN03 = 0x134,
    STA_COMMONSTUN04 = 0x135,
    STA_COMMONSTUN05 = 0x136,
    STA_COMMONSTUN06 = 0x137,
    STA_COMMONSTUN07 = 0x138,
    STA_COMMONSTUN08 = 0x139,
    STA_COMMONSTUN09 = 0x13A,
    STA_COMMONSTUN10 = 0x13B,
    STA_COMMONFEAR01 = 0x13C,
    STA_COMMONFEAR02 = 0x13D,
    STA_COMMONFEAR03 = 0x13E,
    STA_COMMONFEAR04 = 0x13F,
    STA_COMMONFEAR05 = 0x140,
    STA_COMMONFEAR06 = 0x141,
    STA_COMMONFEAR07 = 0x142,
    STA_COMMONFEAR08 = 0x143,
    STA_COMMONFEAR09 = 0x144,
    STA_COMMONFEAR10 = 0x145,
    STA_ETHEREAL = 0x146,
    STA_GLDRESTORE = 0x147,
    STA_GLDMOVESPEEDUP = 0x148,
    STA_GLDACMINUS = 0x149,
    STA_GLDSLOW = 0x14A,
    STA_GLDSTUN = 0x14B,
    STA_KARENDOT = 0x14C,
    STA_KARENDIVINE = 0x14D,
    STA_KARENSTATIC = 0x14E,
    STA_KARENCAPTIVATE = 0x14F,
    STA_ROCKCANTHEAL = 0x150,
    STA_ROCKCANTCHAT = 0x151,
    STA_ROCKDASHSTUN = 0x152,
    STA_KARENDOTHEAL = 0x153,
    STA_KARENSTUN = 0x154,
    STA_MRMINUS = 0x155,
    STA_SILBERKBLOODING = 0x156,
    STA_BLOODFEAR = 0x157,
    STA_GLDATKUP = 0x158,
    STA_RESTEXP = 0x159,
    STA_KNOCKBACK = 0x15A,
    STA_KNOCKBACKFLY = 0x15B,
    STA_KNOCKBACKROLL = 0x15C,
    STA_FATALKNOCKBACK = 0x15D,
    STA_CANNOTCONTROL = 0x15E,
    STA_EVENTHPUP = 0x15F,
    STA_EVENTSPUP = 0x160,
    STA_EVENTALLSTATSUP = 0x161,
    STA_EVENTSPEED = 0x162,
    STA_EVENTACUP = 0x163,
    STA_EVENTMRUP = 0x164,
    STA_ANGRY = 0x165,
    STA_PARALYSIS = 0x166,
    STA_SPIRIT = 0x167,
    STA_TIMEATTACK = 0x168,
    STA_STAACREDDRAGON = 0x169,
    STA_STAMRBLUEDRAGON = 0x16A,
    STA_TIMEATTACKMINI = 0x16B,
    STA_MONKEYSTUN = 0x16C,
    STA_MONKEYDEFENSE = 0x16D,
    STA_GTIRATEPOINT = 0x16E,
    STA_GTISPEED = 0x16F,
    STA_GTIRESISTALL = 0x170,
    STA_GTIREFLECT = 0x171,
    STA_GTIBLIND = 0x172,
    STA_GTICONFUSION = 0x173,
    STA_GTIMETASLIME = 0x174,
    STA_GTIHIDE = 0x175,
    STA_GTISCAN = 0x176,
    STA_GTIBINDING = 0x177,
    STA_GTIBOMB1 = 0x178,
    STA_GTIBOMB2 = 0x179,
    STA_GTIBOMBDIE = 0x17A,
    STA_GTIREVERSEORDER = 0x17B,
    STA_GTIVIRUSRT = 0x17C,
    STA_GTIVIRUSMOVE = 0x17D,
    STA_GTIMOBSUICIDE = 0x17E,
    STA_GTIKNOCKBACKROLL = 0x17F,
    STA_CRACKERACDOWN = 0x180,
    STA_CRACKERWCDOWN = 0x181,
    STA_CRACKERDISEASE = 0x182,
    STA_CRACKERCURSE = 0x183,
    STA_CRACKERWCUPRATE = 0x184,
    STA_CRACKERACUPRATE = 0x185,
    STA_HUMARACDOWNRATE = 0x186,
    STA_BODYFORCE = 0x187,
    STA_CANNOTCHANGETARGET = 0x188,
    STA_SHADOWBINDING = 0x189,
    STA_SOULFREE = 0x18A,
    STA_NORTHPOISON = 0x18B,
    STA_FITBLOOD = 0x18C,
    STA_FITMOVEDOWN = 0x18D,
    STA_NORTFBURN = 0x18E,
    STA_RANGEEVASIONUP = 0x18F,
    STA_POISONDMGADD = 0x190,
    STA_POISONDMGDOWN = 0x191,
    STA_BLOODDMGDOWN = 0x192,
    STA_USESPADD = 0x193,
    STA_DOTDMGDOWN = 0x194,
    STA_EVASIONDOWN = 0x195,
    STA_SHOCKSTUN = 0x196,
    STA_DOTDMGADDALL = 0x197,
    STA_SHOCKRUN = 0x198,
    STA_KQSKELKNIGHTBLOODING = 0x199,
    STA_MOBBURNTYPE01 = 0x19A,
    STA_MOBSTUNTYPE01 = 0x19B,
    STA_VACANT = 0x19C,
    STA_WOLFCLAWTBUPRATE = 0x19D,
    STA_ENTRAPBLN = 0x19E,
    STA_ENTRAPMSD = 0x19F,
    STA_ENTRAPBLD = 0x1A0,
    STA_ENTRAPPLS = 0x1A1,
    STA_QUESTENTANGLE2 = 0x1A2,
    STA_GBGAMEMEMBERFULL = 0x1A3,
    STA_MULTIBLOOD = 0x1A4,
    STA_CHRTITLEWCUPRATE = 0x1A5,
    STA_CHRTITLEWCDOWNRATE = 0x1A6,
    STA_CHRTITLEMAUPRATE = 0x1A7,
    STA_CHRTITLEMADOWNRATE = 0x1A8,
    STA_CHRTITLEACUPRATE = 0x1A9,
    STA_CHRTITLEACDOWNRATE = 0x1AA,
    STA_CHRTITLEMRUPRATE = 0x1AB,
    STA_CHRTITLEMRDOWNRATE = 0x1AC,
    STA_CHRTITLEHPUPRATE = 0x1AD,
    STA_CHRTITLEHPDOWNRATE = 0x1AE,
    STA_CHRTITLEHPRESTORE = 0x1AF,
    STA_CHRTITLESPUPRATE = 0x1B0,
    STA_CHRTITLESPRESTORE = 0x1B1,
    STA_CHRTITLETHUPRATE = 0x1B2,
    STA_CHRTITLETHDOWNRATE = 0x1B3,
    STA_CHRTITLETBUPRATE = 0x1B4,
    STA_CHRTITLETBDOWNRATE = 0x1B5,
    STA_CHRTITLESPEEDUPRATE = 0x1B6,
    STA_CHRTITLESPEEDDOWNRATE = 0x1B7,
    STA_CHRTITLECRITICALUPRATE = 0x1B8,
    STA_CHRTITLEBLOODING = 0x1B9,
    STA_MOBAPU01 = 0x1BA,
    STA_BH_HELGA_NONE = 0x1BB,
    STA_HELGBALL = 0x1BC,
    STA_BH_KARATEMPLER_NONE = 0x1BD,
    STA_BH_HELGAAPU01 = 0x1BE,
    STA_BH_HELGADRT01 = 0x1BF,
    STA_BH_HELGA_IDLE01 = 0x1C0,
    STA_MOBACPLUS = 0x1C1,
    STA_MOBSTN01 = 0x1C2,
    STA_MOBPSN01 = 0x1C3,
    STA_MOBOPU01 = 0x1C4,
    STA_MOBMSD02 = 0x1C5,
    STA_MOBSLC01 = 0x1C6,
    STA_MOBBLD01 = 0x1C7,
    STA_MOBMTS01 = 0x1C8,
    STA_MOBBRN01 = 0x1C9,
    STA_MOBMSD01 = 0x1CA,
    STA_ADLUBAUP = 0x1CB,
    STA_ADLUBADOWN = 0x1CC,
    STA_BURNPAINME = 0x1CD,
    STA_BURNPAINFOE = 0x1CE,
    STA_GROUNDSTRIKE = 0x1CF,
    STA_BOMBSHOT = 0x1D0,
    STA_CROSSDROP = 0x1D1,
    STA_METEOR = 0x1D2,
    STA_MAGICDANCEUSESPDOWN = 0x1D3,
    STA_DEEPFEARMENDOWNRATE = 0x1D4,
    STA_MENDOWNRATE = 0x1D5,
    STA_SHAMECRIUP = 0x1D6,
    STA_MOBMRS01 = 0x1D7,
    STA_MOBACS01 = 0x1D8,
    STA_NOTTARGET = 0x1D9,
    STA_MAGICDANCEUSESPDOWN02 = 0x1DA,
    STA_MAGICDANCEUSESPDOWN03 = 0x1DB,
    STA_MAGICDANCEUSESPDOWN04 = 0x1DC,
    STA_MAGICDANCEUSESPDOWN05 = 0x1DD,
    STA_MENDOWNRATE02 = 0x1DE,
    STA_MENDOWNRATE03 = 0x1DF,
    STA_MENDOWNRATE04 = 0x1E0,
    STA_MENDOWNRATE05 = 0x1E1,
    STA_SHAMECRIUP02 = 0x1E2,
    STA_SHAMECRIUP03 = 0x1E3,
    STA_SHAMECRIUP04 = 0x1E4,
    STA_SHAMECRIUP05 = 0x1E5,
    STA_SNSATKUP = 0x1E6,
    STA_SNSCRIUP = 0x1E7,
    STA_SNSDEFENSEUP = 0x1E8,
    STA_SNSHPUP = 0x1E9,
    STA_SNSSPUP = 0x1EA,
    STA_SNSSPEEDUP = 0x1EB,
    STA_MULTIHEAL = 0x1EC,
    STA_HIDEWC = 0x1ED,
    STA_EGLACK04 = 0x1EE,
    STA_EGLACKMAD05 = 0x1EF,
    STA_SALARE04 = 0x1F0,
    STA_SALARE00 = 0x1F1,
    STA_ADLFLOUSSIER = 0x1F2,
    STA_ADLFLOUSSIERIMT = 0x1F3,
    STA_ADLFSTUN = 0x1F4,
    STA_EGLACKMAD04 = 0x1F5,
    STA_MINEICE = 0x1F6,
    STA_MINESTUN = 0x1F7,
    STA_MINEFIREVIVI = 0x1F8,
    STA_MINEICEVIVI = 0x1F9,
    STA_MINEREWARD = 0x1FA,
    STA_SETF2WCUP = 0x1FB,
    STA_SETF2ACUP = 0x1FC,
    STA_SETF4HPUP = 0x1FD,
    STA_SETF4ACDOWN = 0x1FE,
    STA_SETF4ACUP = 0x1FF,
    STA_SETF4WCUPRATE = 0x200,
    STA_SETF4ACUPRATE = 0x201,
    STA_SETA2WCUP = 0x202,
    STA_SETA4SPEEDUP = 0x203,
    STA_SETA4SPEEDDOWN = 0x204,
    STA_SETA4ATKSPEEDUP = 0x205,
    STA_SETM2MAUP = 0x206,
    STA_SETM2MRUP = 0x207,
    STA_SETM3SPUP = 0x208,
    STA_SETM4MAUP = 0x209,
    STA_SETM4MRDOWN = 0x20A,
    STA_SETM4SPUP = 0x20B,
    STA_SETM4MRUP = 0x20C,
    STA_SETC2WCUP = 0x20D,
    STA_SETC2MAUP = 0x20E,
    STA_SETC3MRUP = 0x20F,
    STA_SETC4MRUP = 0x210,
    STA_SETC4WCUP = 0x211,
    STA_SETC4ATKDOWN = 0x212,
    STA_SETC4ACUP = 0x213,
    STA_SETC4ACDOWN = 0x214,
    STA_SETC4MAUP = 0x215,
    STA_SETJ2WCUP = 0x216,
    STA_SETJ2HPUP = 0x217,
    STA_SETJ3SPUP = 0x218,
    STA_SETJ4ACDOWN = 0x219,
    STA_SETJ4ATKSPPEUP = 0x21A,
    STA_SETJ4CRLUP = 0x21B,
    STA_SETJ4WCUP = 0x21C,
    STA_ENWCUP = 0x21D,
    STA_ENMAUP = 0x21E,
    STA_ENATKSPEED = 0x21F,
    STA_ENWCRATE = 0x220,
    STA_ENADDDMGRATE = 0x221,
    STA_ENKNOCKBACKRATE = 0x222,
    STA_ENBINDINGRATE = 0x223,
    STA_ENMOVEDOWNRATE = 0x224,
    STA_QDAYWCUP = 0x225,
    STA_QDAYMAUP = 0x226,
    STA_QDAYEXPUP = 0x227,
    STA_QDAYDROPUP = 0x228,
    STA_SWICEWARN = 0x229,
    STA_SURPRISE = 0x22A,
    STA_SWPLSWARN = 0x22B,
    STA_SWSTNWARN = 0x22C,
    STA_SWBRN01WARN = 0x22D,
    STA_SWLVTWARN = 0x22E,
    STA_AWAYBACKSPOT = 0x22F,
    STA_RADIONBUFF = 0x230,
    STA_AIRIBUFF = 0x231,
    STA_WARLBRAINWASH = 0x232,
    STA_WARLBRN01 = 0x233,
    STA_STUNCANATTACK = 0x234,
    STA_TRANSFORM = 0x235,
    STA_BALLSNOW = 0x236,
    STA_SNOWMAN = 0x237,
    STA_WARNSETBUFF = 0x238,
    STA_SET_VALEN_STN = 0x239,
    STA_SET_VALEN_Heal = 0x23A,
    STA_VALEN_REWARD = 0x23B,
    STA_KQEGG_SPDW = 0x23C,
    STA_KQEGG_REWARD = 0x23D,
    STA_KQEGG_SPUP = 0x23E,
    STA_KQSPRING_FEAR = 0x23F,
    STA_KQSPRING_SLOW = 0x240,
    STA_KQ_SPUP_BUFF = 0x241,
    STA_KQ_SPIM_BUFF = 0x242,
    STA_KQ_SPUP_RATE_BUFF = 0x243,
    STA_KQSPRING_ARROW = 0x244,
    STA_WARHBRN01 = 0x245,
    STA_WARHBRN = 0x246,
    STA_STRONGER_RANGEATTACK = 0x247,
    STA_STRONGER_MELEEATTACK = 0x248,
    STA_FLAMINGBODY = 0x249,
    STA_COUNT30 = 0x24A,
    STA_WARHWPNBRN = 0x24B,
    STA_ORBATKRATEUP = 0x24C,
    STA_RECOUP = 0x24D,
    STA_LIGHTTOUCH = 0x24E,
    STA_TREAT = 0x24F,
    STA_LIGHTMARK = 0x250,
    STA_MINHP = 0x251,
    STA_MOONLIGHT = 0x252,
    STA_LPDOTPLUS = 0x253,
    STA_DMGSHIELD = 0x254,
    STA_DELCASTTIME = 0x255,
    STA_SETS2WCMAUP = 0x256,
    STA_SETS2ACMRUP = 0x257,
    STA_SETS4WCMAUP = 0x258,
    STA_SETS4ACMRUP = 0x259,
    STA_SENPARTYHPUPMAIN = 0x25A,
    STA_SENPARTYHPUP = 0x25B,
    STA_SENPARTYHPUP1 = 0x25C,
    STA_SENEVENTEXPUP = 0x25D,
    STA_SENEVENTDROPUP = 0x25E,
    STA_PZL_HIDE = 0x25F,
    STA_PZL_OCCUPY = 0x260,
    STA_PZL_REWARD_S = 0x261,
    STA_PZL_REWARD_H = 0x262,
    STA_PZL_REWARD_SH1 = 0x263,
    STA_PZL_REWARD_SH2 = 0x264,
    STA_ROUTMAGEATKUP = 0x265,
    STA_ARK_STN = 0x266,
    STA_ARK_BLD01 = 0x267,
    STA_ARK_BLD02 = 0x268,
    STA_ARK_BLD03 = 0x269,
    STA_ARK_BRN01 = 0x26A,
    STA_ARK_BRN02 = 0x26B,
    STA_ARK_BRN03 = 0x26C,
    STA_ARK_THDOWN01 = 0x26D,
    STA_ARK_THDOWN02 = 0x26E,
    STA_KAHAL_STN = 0x26F,
    STA_KAHAL_BLD = 0x270,
    STA_KAHAL_FEAR01 = 0x271,
    STA_KAHAL_FEAR02 = 0x272,
    STA_KAHAL_SHOUT = 0x273,
    STA_KAHAL_SPDDOWN = 0x274,
    STA_KAHAL_ICE = 0x275,
    STA_SIREN_STN1 = 0x276,
    STA_SIREN_STN2 = 0x277,
    STA_SIREN_NOMOVE = 0x278,
    STA_SIREN_KNOCKBACK1 = 0x279,
    STA_SIREN_KNOCKBACK2 = 0x27A,
    STA_SIREN_HEAL = 0x27B,
    STA_SIREN_LVT1 = 0x27C,
    STA_SIREN_LVT2 = 0x27D,
    STA_SIREN_BLD01 = 0x27E,
    STA_SIREN_FEAR = 0x27F,
    STA_SIREN_BLD02 = 0x280,
    STA_CONHPPOTION_T6 = 0x281,
    STA_CONSPPOTION_T6 = 0x282,
    STA_DEXPOTION_T6 = 0x283,
    STA_ACMRPOTION_T6 = 0x284,
    STA_STRCRIPOTION_T6 = 0x285,
    STA_PSNRESIPOTION_T6 = 0x286,
    STA_DSSRESIPOTION_T6 = 0x287,
    STA_CURRESIPOTION_T6 = 0x288,
    STA_THSCROLL_T6 = 0x289,
    STA_TBSCROLL_T6 = 0x28A,
    STA_MRSCROLL_T6 = 0x28B,
    STA_ACSCROLL_T6 = 0x28C,
    STA_CRISCROLL_T6 = 0x28D,
    STA_MAXHPSCROLL_T6 = 0x28E,
    STA_MAXSPSCROLL_T6 = 0x28F,
    STA_MSSCROLL_T6 = 0x290,
    STA_BERVALE_ICE01 = 0x291,
    STA_BERVALE_ICE02 = 0x292,
    STA_BERVALE_BLD01 = 0x293,
    STA_BERVALE_BLD02 = 0x294,
    STA_B_ALBI_BRN = 0x295,
    STA_B_ALBI_KNOCK = 0x296,
    STA_B_ALBI_STN = 0x297,
    STA_B_ALBI_FEAR = 0x298,
    STA_B_ALBI_DOT = 0x299,
    STA_B_ALBI_REFLECT = 0x29A,
    STA_B_ALBI_ACMRUP = 0x29B,
    STA_ADLFGCRAZY = 0x29C,
    STA_FCITRIEDOT = 0x29D,
    STA_LCWCMAUP = 0x29E,
    STA_E_SLIME = 0x29F,
    STA_E_HONEYING = 0x2A0,
    STA_E_PHINO = 0x2A1,
    STA_E_LIZARDMAN = 0x2A2,
    STA_E_KINGCRAB = 0x2A3,
    STA_E_SPARKDOG = 0x2A4,
    STA_E_LAVAVIVI = 0x2A5,
    STA_E_PHINOFLIE = 0x2A6,
    STA_E_MUSHROOM = 0x2A7,
    STA_E_SPIDER = 0x2A8,
    STA_E_B_CRACKERHUMAR = 0x2A9,
    STA_E_HELGA = 0x2AA,
    STA_EMP_STUN = 0x2AB,
    STA_EMP_KINGBLOODING = 0x2AC,
    STA_EMP_EMPBLOODING = 0x2AD,
    STA_EMP_LVT = 0x2AE,
    STA_LCACMRUP = 0x2AF,
    STA_E_FIREWORKS = 0x2B0,
    STA_ARENA_SPDUP = 0x2B1,
    STA_ARENA_STUN = 0x2B2,
    STA_ARENA_DRAGOUT = 0x2B3,
    STA_ARENA_DEFDW = 0x2B4,
    STA_ARENA_SPDDW = 0x2B5,
    STA_ARENA_ALLDW = 0x2B6,
    STA_ARENA_REWARD = 0x2B7,
    STA_ARENA_FLAG_RED = 0x2B8,
    STA_ARENA_FLAG_BLUE = 0x2B9,
    STA_ARENA_MINHP = 0x2BA,
    STA_X_ICE = 0x2BB,
    STA_X_SNOWMAN = 0x2BC,
    STA_X_REWARD01 = 0x2BD,
    STA_X_REWARD02 = 0x2BE,
    STA_X_REWARD03 = 0x2BF,
    STA_X_REWARD04 = 0x2C0,
    STA_E_SKI_ICE = 0x2C1,
    STA_E_SKI_SPEEDUP = 0x2C2,
    STA_E_SKI_REWARD = 0x2C3,
    STA_E_SKI_STUN = 0x2C4,
    STA_LAB_PURYIMPACTSTUN = 0x2C5,
    STA_C_PURYIMPACTSTUN = 0x2C6,
    STA_E_EGG2014_HOSHEMING = 0x2C7,
    STA_E_EGG2014_SELFREVIVE = 0x2C8,
    STA_E_EGG2014_EXPUP = 0x2C9,
    STA_E_EGG2014_DROPRATEUP = 0x2CA,
    STA_MOVERSTATUPSINGLE = 0x2CB,
    STA_MOVERSTATUPPARTY = 0x2CC,
    STA_MOVERSTATUP = 0x2CD,
    STA_KDSOCCER_SPEED_UP = 0x2CE,
    STA_KDSOCCER_INVINCIBLE = 0x2CF,
    STA_KQWATER_ARROW_BLUE = 0x2D0,
    STA_KQWATER_ARROW_RED = 0x2D1,
    STA_E_JACKO = 0x2D2,
    STA_E_KEBING = 0x2D3,
    STA_E_FORASCHIEF = 0x2D4,
    STA_E_H_WIN_SPEEDUP = 0x2D5,
    STA_E_H_WIN_SPEEDDOWN = 0x2D6,
    STA_ADLFLOUSSIER_H = 0x2D7,
    STA_E_USER_NEWBIE01 = 0x2D8,
    STA_E_USER_NEWBIE02 = 0x2D9,
    STA_E_USER_NEWBIE03 = 0x2DA,
    STA_E_USER_NEWBIE04 = 0x2DB,
    STA_E_USER_NEWBIE05 = 0x2DC,
    STA_E_USER_COMEBACK_MAIN01 = 0x2DD,
    STA_E_USER_COMEBACK_MAIN02 = 0x2DE,
    STA_E_USER_COMEBACK_MAIN03 = 0x2DF,
    STA_E_USER_COMEBACK_MAIN04 = 0x2E0,
    STA_E_USER_COMEBACK_MAIN05 = 0x2E1,
    STA_E_USER_COMEBACK01 = 0x2E2,
    STA_E_USER_COMEBACK02 = 0x2E3,
    STA_E_USER_COMEBACK03 = 0x2E4,
    STA_E_USER_COMEBACK04 = 0x2E5,
    STA_E_USER_COMEBACK05 = 0x2E6,
    STA_XMAS_STATUP = 0x2E7,
    STA_IDBUFF_100 = 0x2E8,
    STA_IDBUFF_80 = 0x2E9,
    STA_IDBUFF_60 = 0x2EA,
    STA_IDBUFF_40 = 0x2EB,
    STA_IDBUFF_20 = 0x2EC,
    STA_E_SNOWMANR = 0x2ED,
    STA_E_SNOWMANB = 0x2EE,
    STA_KDFARGELS_BLOOD01 = 0x2EF,
    STA_KDFARGELS_BLOOD02 = 0x2F0,
    STA_KDFARGELS_BLOOD03 = 0x2F1,
    STA_KDFARGELS_MRDOWNRATE = 0x2F2,
    STA_KDFARGELS_AIRBORNE = 0x2F3,
    STA_KDFARGELS_ACMRDOWN = 0x2F4,
    STA_KDFARGELS_DMGNEGLECT = 0x2F5,
    STA_KDFARGELS_DOTHEAL = 0x2F6,
    STA_SDVALE01_STN = 0x2F7,
    STA_SDVALE01_WHEEL = 0x2F8,
    STA_SDVALE01_SPDUP = 0x2F9,
    STA_SDVALE01_SPDDOWN = 0x2FA,
    STA_SDVALE01_BLIND = 0x2FB,
    STA_SDVALE01_PSN = 0x2FC,
    STA_SDVALE01_ICEFIELD = 0x2FD,
    STA_SDVALE01_BRN = 0x2FE,
    STA_SDVALE01_WCMAUP = 0x2FF,
    STA_SDVALE01_KNOCK = 0x300,
    STA_COSMUSAACRATE = 0x301,
    STA_COSMUSACRI = 0x302,
    STA_COSMUSAALLSTAT = 0x303,
    STA_BH_ALBI_REFLECT = 0x304,
    STA_BH_ALBI_ACMRUP = 0x305,
    STA_E_ZOMBIE = 0x306,
    STA_E_MARACREW = 0x307,
    STA_E_MARAELITE = 0x308,
    STA_E_MARASAILOR = 0x309,
    STA_E_PSYKEN = 0x30A,
    STA_E_PSYKENDOG = 0x30B,
    STA_E_MEGAN = 0x30C,
    STA_E_YETI = 0x30D,
    STA_E_IMP = 0x30E,
    STA_E_ROBO = 0x30F,
    STA_E_HOB = 0x310,
    STA_E_PINKY = 0x311,
    STA_E_WARH_DEVILDOM = 0x312,
    STA_E_ARKNOVICE = 0x313,
    STA_E_ARKTECH = 0x314,
    STA_E_MANDRAGORA = 0x315,
    STA_E_S_HAYREDDIN = 0x316,
    STA_E_MARA = 0x317,
    MAX_ABSTATEINDEX = 0x318,
};

enum ID_LEVEL_TYPE
{
    ILT_EASY = 0x0,
    ILT_NORMAL = 0x1,
    ILT_HARD = 0x2,
    ILT_MAX = 0x3,
};

enum WM_Link
{
    WM_NONE = 0x0,
    WM_ROUN = 0x1,
    WM_ROUCOS01 = 0x2,
    WM_ROUCOS02 = 0x3,
    WM_ROUCOS03 = 0x4,
    WM_ROUVAL01 = 0x5,
    WM_ROUVAL02 = 0x6,
    WM_ELD = 0x7,
    WM_ELDCEM01 = 0x8,
    WM_ELDCEM02 = 0x9,
    WM_ELDGBL01 = 0xA,
    WM_ELDPRI01 = 0xB,
    WM_ELDFOR01 = 0xC,
    WM_ELDSLEEP01 = 0xD,
    WM_URG = 0xE,
    WM_ECHOCAVE = 0xF,
    WM_WINDYCAVE = 0x10,
    WM_GOLDCAVE = 0x11,
    WM_URGFIRE01 = 0x12,
    WM_URGSWA01 = 0x13,
    WM_ELDGBL02 = 0x14,
    WM_ELDPRI02 = 0x15,
    WM_LINKFIELD01 = 0x16,
    WM_LINKFIELD02 = 0x17,
    WM_URG_ALRUIN = 0x18,
    WM_ADLTHORN01 = 0x19,
    WM_URGDARK01 = 0x1A,
    WM_BERKAL01 = 0x1B,
    WM_BERA_ = 0x1C,
    WM_ADL = 0x1D,
    WM_BERFRZ01 = 0x1E,
    WM_BERVALE01 = 0x1F,
    WM_ADLVAL01 = 0x20,
    MAX_WM_LINK = 0x21,
};

#pragma pack(push, 1)
struct MapInfo
{
    unsigned __int16 ID;
    Name3 MapName;
    char Name[32];
    WM_Link IsWMLink;
    unsigned int RegenX;
    unsigned int RegenY;
    char KingdomMap;
    Name3 MapFolderName;
    char InSide;
    unsigned int Sight;
};
#pragma pack(pop)

struct CanAttackTypes
{
    char PKer;
    char EnemyGuild;
    char PartyMember;
    char Mob;
    char Summoned;
};

struct RegenLocation
{
    unsigned int regenx;
    unsigned int regeny;
};

struct FieldOption : OptionReader
{
    struct __declspec(align(1)) GuildTournamentMapStr
    {
      char MapIDClient[13];
      char GTMapNo;
      unsigned int StoneX;
      unsigned int StoneY;
      unsigned __int16 StoneDir;
      unsigned int GldARgX;
      unsigned int GldARgY;
      unsigned int GldBRgX;
      unsigned int GldBRgY;
      struct
      {
          unsigned int DoorX;
          unsigned int DoorY;
          unsigned int DoorD;
          char DoorBlock[32];
      } DoorA0, DoorB0, DoorA1, DoorB1, DoorA2, DoorB2;
      char CheckSum;
    };

    struct __declspec(align(1)) FieldAttr
    {
        Name3 mapidclient;
        char delimiter;
        char subfrom[4];
        char subto[4];
        char serial;
        char _mapname[32];
        char KingdomQuestMap;
        unsigned int width;
        unsigned int height;
        unsigned __int16 immortal_millisec;
        char script[32];
        char ItemDropByKilled;
        CanAttackTypes attack;
        char ispkkq;
        char isfreepk;
        char ispartybattle;
        char NameHide;
        char LinkIn;
        char LinkOut;
        char SystemMap;
        Name3 regencity;
        RegenLocation regenloc[4];
        char regenspots;
        char canrestart;
        char cantrade;
        char byCanMiniHouset;
        char byCanItem;
        char byCanSkill;
        char byCanChat;
        char byCanShout;
        char byBooth;
        char byProduce;
        char byCanRide;
        char canstoneuse;
        char canparty;
        unsigned __int16 explost_atdead_bymob;
        unsigned __int16 explost_atdead_byply;
        char playersublayer;
        char checksum;
    };

	struct __declspec(align(1)) InstanceDungeonInfo
    {
      ORToken Argument;
      char IDNo;
      char ZoneNumber;
      char MapIDClient[13];
      char ScriptName[32];
      char ModeIDLv;
      char EntranceType;
      char Guild;
      char Individual;
      unsigned __int16 NeedQuest;
      char NeedItem[32];
      char Consume;
      char LimitTime;
      char MaxUseCount;
      char CheckSum;
      unsigned __int16 NeedItemID;
    };

    struct TutorialMapInfo
    {
        char MapIDClient[13];
        char MaxChr;
        char ScriptName[32];
    };

    const FieldOption::FieldAttr* fo_GetFieldAttr(const char* mapname)
    {
        return CallMemberFunction<FieldOption, FieldOption::FieldAttr*, const char*>(0x0063E160, this, mapname);
    }

    FieldAttr* fo_Array[512];
    int fo_Number;
};

struct AreaInfoData
{
    struct IAreaData
    {
        virtual void IntersectTest(float, float);
    	
        Name8 Name;
        int nAreaType;
    };

    virtual void _Delete(uint);
	
    IAreaData* m_pData[256];
    unsigned int m_uiTotalDataCnt;
};

struct BlockDistribute
{
    struct __declspec(align(4)) BlockingDistribute
    {
        unsigned __int16 bd_Top;
        unsigned __int16 bd_Bottom;
        unsigned __int16 bd_Left;
        unsigned __int16 bd_Right;
        BlockingDistribute* bd_Brench[4];
        unsigned __int16 bd_Brenchs;
        unsigned __int16 bd_EmptyCellNum;
        char bd_Act;
    };
};

struct MapBlock
{
    struct MapDoorBlockElement
    {
        Name8 mdbe_BlockName;
        unsigned int mdbe_StartX;
        unsigned int mdbe_StartY;
        unsigned int mdbe_EndX;
        unsigned int mdbe_EndY;
        unsigned int mdbe_DataSize;
        unsigned int mdbe_Address;
    };

    enum DoorAction
    {
        DA_CLOSE = 0x0,
        DA_OPEN = 0x1,
        DA_BREAK = 0x2,
    };

    struct MapDoorArray
    {
        unsigned int mda_TotalHeadCnt;
        MapDoorBlockElement mda_Array[32];
        int mda_Number;
        char* mda_BlockBuffer;
    };

    struct MapBlockInformation
    {
        unsigned int mbi_mapxsize;
        unsigned int mbi_mapysize;
        unsigned int mbi_blockxsize;
        unsigned int mbi_blockysize;
        unsigned int mbi_xbyte;
        char* mbi_MoveBlockBuffer;
        char* mbi_AttackBlockBuffer;
        unsigned int mbi_uiRealOneSideDataSize;
        unsigned int mbi_uiOneSideBlockCnt;
        AreaInfoData mbi_AreaData;
        BlockDistribute::BlockingDistribute* mbi_BlockDistribute;
        MapDoorArray mbi_DoorBlockInform;
    };
};

struct MobDeadCount
{
    unsigned __int16* mdc_Counter;
};

struct GuildWarInfo
{
    char seed;
    unsigned int guildA;
    unsigned int guildB;
};

struct FieldFlag
{
    __int8 ff_CanUseReviveItem : 1;
    __int8 ff_CanUseReviveSkill : 1;
};

#pragma pack(push, 1)
struct ShineItemKeyStruct
{
    unsigned __int32 notuse : 9;
    unsigned __int32 method : 4;
    unsigned __int32 zone : 5;
    unsigned __int32 serial : 8;
    unsigned __int32 second : 6;
    unsigned __int32 minute : 6;
    unsigned __int32 hour : 5;
    unsigned __int32 day : 5;
    unsigned __int32 month : 4;
    unsigned __int32 year : 5;
    unsigned __int32 world : 6;
    unsigned __int32 mrsv : 1;
};

union SHINE_ITEM_REGISTNUMBER
{
    ShineItemKeyStruct binary;
    unsigned int dwrdkey[2];
    unsigned __int64 key;
};

struct ShineDateTime
{
    unsigned __int32 year : 8;
    unsigned __int32 month : 5;
    unsigned __int32 date : 6;
    unsigned __int32 hour : 6;
    unsigned __int32 minute : 7;
};

enum SHINE_PUT_ON_BELONGED_ITEM
{
    SPOBI_NOT_BELONGED = 0x0,
    SPOBI_BELONGED = 0x1,
};

struct $BA792661B6A8A2DB1C0266A653A1AC4D
{
    __int8 identify : 1;
    __int8 optionnum : 7;
};

union ItemOptionNumber
{
    $BA792661B6A8A2DB1C0266A653A1AC4D str;
    char bin;
};

struct ItemOptionStorage
{
    struct FixedInfo
    {
        ItemOptionNumber optionnumber;
    };

    struct __declspec(align(1)) Element
    {
      char itemoption_type;
      unsigned __int16 itemoption_value;
    };

    FixedInfo fixed;
    Element optionlist[8];
};

struct __declspec(align(2)) MobKillInfo
{
    unsigned __int16 monster;
    unsigned __int32 killcount : 28;
    unsigned __int32 reserved : 4;
};

struct __declspec(align(1)) SocketInfo
{
    unsigned __int16 elementalGemID;
    char restCount;
};

struct FurnitureFlag
{
    __int8 IsPlaced : 1;
};

struct ItemChestFlag
{
    __int8 itemnum : 4;
    __int8 flag : 4;
};

struct RidingData
{
    unsigned __int16 ridenum : 15;
    unsigned __int16 duringriding : 1;
};

struct ShineItemAttr_ByteLot
{
    char lot;
};

struct ShineItemAttr_WordLot
{
    unsigned __int16 lot;
};

struct ShineItemAttr_DwrdLot
{
    unsigned int lot;
};

struct ShineItemAttr_QuestItem
{
    unsigned __int16 lot;
};

struct __declspec(align(2)) ShineItemAttr_Amulet
{
    ShineDateTime deletetime;
    SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
    char upgrade;
    char strengthen;
    char upgradefailcount;
    ItemOptionStorage UpgradeOption;
    char randomOptionChangedCount;
    ItemOptionStorage option;
};

#pragma pack(push, 1)
struct ShineItemAttr_Weapon
{
    char upgrade;
    char _pad[0x19-0x2];
    char _p2;
    unsigned __int16 CharacterTitleMobID;
    char usertitle[21];
    SocketInfo gemSockets[3];
    char maxSocketCount;
    char createdSocketCount;
    ShineDateTime deletetime;
    char randomOptionChangedCount;
    ItemOptionStorage option;
};
#pragma pack(pop)

struct __declspec(align(1)) ShineItemAttr_Armor
{
    char upgrade;
    char strengthen;
    char upgradefailcount;
    SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
    ShineDateTime deletetime;
    char randomOptionChangedCount;
    ItemOptionStorage option;
};

struct __declspec(align(1)) ShineItemAttr_Shield
{
    char upgrade;
    char strengthen;
    char upgradefailcount;
    SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
    ShineDateTime deletetime;
    char randomOptionChangedCount;
    ItemOptionStorage option;
};

struct __declspec(align(1)) ShineItemAttr_Boot
{
    char upgrade;
    char strengthen;
    char upgradefailcount;
    SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
    ShineDateTime deletetime;
    char randomOptionChangedCount;
    ItemOptionStorage option;
};

struct __declspec(align(4)) ShineItemAttr_Furniture
{
    FurnitureFlag flag;
    unsigned __int16 furnicherID;
    ShineDateTime deletetime;
    float LocX;
    float LocY;
    float LocZ;
    float Direct;
    ShineDateTime dEndureEndTime;
    char nEndureGrade;
    unsigned __int64 nRewardMoney;
};

struct ShineItemAttr_Decoration
{
    ShineDateTime deletetime;
    SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
};

struct ShineItemAttr_SkillScroll
{
};

struct ShineItemAttr_RecallScroll : ShineItemAttr_ByteLot
{
};

struct __declspec(align(1)) ShineItemAttr_BindItem
{
    char _size[0x65];
};

struct ShineItemAttr_UpSource : ShineItemAttr_ByteLot
{
};

struct __declspec(align(1)) ShineItemAttr_ItemChest
{
    ItemChestFlag type;
    SHINE_ITEM_REGISTNUMBER content[8];
};

struct ShineItemAttr_WeaponTitleLicence
{
};

struct ShineItemAttr_KingdomQuest
{
};

struct ShineItemAttr_MiniHouseSkin
{
    ShineDateTime deletetime;
};

struct ShineItemAttr_UpRed : ShineItemAttr_ByteLot
{
};

struct ShineItemAttr_UpBlue : ShineItemAttr_ByteLot
{
};

struct ShineItemAttr_UpGold : ShineItemAttr_ByteLot
{
};

struct ShineItemAttr_KQStep : ShineItemAttr_WordLot
{
};

struct ShineItemAttr_Feed : ShineItemAttr_ByteLot
{
};

struct __declspec(align(1)) ShineItemAttr_Riding
{
    unsigned __int16 hungrypoint;
    ShineDateTime deletetime;
    RidingData bitflag;
    SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
    unsigned int nHP;
    char nGrade;
    unsigned __int16 nRareFailCount;
};

struct ShineItemAttr_Amount
{
    unsigned int amount;
};

struct ShineItemAttr_CostumWeapon
{
    unsigned int CostumCharged;
};

struct ShineItemAttr_CostumShield
{
    unsigned int CostumCharged;
};

struct ShineItemAttr_ActionItem
{
    ShineDateTime deletetime;
};

struct ShineItemAttr_Enchant
{
    char lot;
};

struct ShineItemAttr_GBCoin
{
};

struct __declspec(align(4)) ShineItemAttr_Capsule
{
    SHINE_ITEM_REGISTNUMBER content;
    ShineDateTime useabletime;
};

struct __declspec(align(1)) ShineItemAttr_MobCardCollect_Unident
{
    unsigned int SerialNumber;
    unsigned __int16 CardID;
    char Star;
    unsigned __int16 Group;
};

struct __declspec(align(1)) ShineItemAttr_MobCardCollect
{
    unsigned int SerialNumber;
    char Star;
};

struct ShineItemAttr_NoEffect : ShineItemAttr_ByteLot
{
};

struct ShineItemAttr_ActiveSkill
{
    unsigned __int16 lot;
};

struct __declspec(align(2)) ShineItemAttr_Pet
{
    unsigned int nPetRegNum;
    unsigned int nPetID;
    char sName[17];
    char bSummoning;
};

struct __declspec(align(1)) ShineItemAttr_Bracelet
{
    ShineDateTime deletetime;
    SHINE_PUT_ON_BELONGED_ITEM IsPutOnBelonged;
    char upgrade;
    char strengthen;
    char upgradefailcount;
    char randomOptionChangedCount;
    ItemOptionStorage option;
};

union __declspec(align(1)) SHINE_ITEM_ATTRIBUTE
{
    ShineItemAttr_ByteLot blot;
    ShineItemAttr_WordLot wlot;
    ShineItemAttr_DwrdLot dlot;
    ShineItemAttr_QuestItem qstitm;
    ShineItemAttr_Amulet amulet;
    ShineItemAttr_Weapon weapon;
    ShineItemAttr_Armor armor;
    ShineItemAttr_Shield shield;
    ShineItemAttr_Boot boot;
    ShineItemAttr_Furniture furniture;
    ShineItemAttr_Decoration decorate;
    ShineItemAttr_SkillScroll skillscroll;
    ShineItemAttr_RecallScroll recallscroll;
    ShineItemAttr_BindItem binditem;
    ShineItemAttr_UpSource upsource;
    ShineItemAttr_ItemChest itemchest;
    ShineItemAttr_WeaponTitleLicence weapontitlelicence;
    ShineItemAttr_KingdomQuest kingdomquest;
    ShineItemAttr_MiniHouseSkin minihouseskin;
    ShineItemAttr_UpRed upgraderedgem;
    ShineItemAttr_UpBlue upgradebluegem;
    ShineItemAttr_UpGold upgradegoldgem;
    ShineItemAttr_KQStep kqstep;
    ShineItemAttr_Feed feed;
    ShineItemAttr_Riding riding;
    ShineItemAttr_Amount amount;
    ShineItemAttr_CostumWeapon costumweapon;
    ShineItemAttr_CostumShield costumshield;
    ShineItemAttr_ActionItem actionitem;
    ShineItemAttr_Enchant Enchant;
    ShineItemAttr_GBCoin GBCoin;
    ShineItemAttr_Capsule Capsule;
    ShineItemAttr_MobCardCollect_Unident MobCard_Unident;
    ShineItemAttr_MobCardCollect MobCard;
    ShineItemAttr_NoEffect NoEffect;
    ShineItemAttr_ActiveSkill ActiveSkill;
    ShineItemAttr_Pet Pet;
    ShineItemAttr_Bracelet Bracelet;
};

struct __declspec(align(1)) SHINE_ITEM_STRUCT
{
    unsigned __int16 itemid;
    SHINE_ITEM_ATTRIBUTE itemattr;
};
#pragma pack(pop)

struct BoothStoreInfo
{
    struct __declspec(align(4)) SellItemKeyNHandle
    {
      SHINE_ITEM_REGISTNUMBER nKey;
      unsigned int nItemHandle;
    };

    unsigned __int16 bsi_nOwnerHandle;
    __declspec(align(1)) SHINE_XY_TYPE bsi_Position;
    std::list<SellItemKeyNHandle> bsi_SellItemList;
};

struct __declspec(align(2)) BoothItemInfo
{
    char bii_nDataSize;
    unsigned int bii_nItemHandle;
    unsigned __int16 bii_nOwnerHandle;
    unsigned __int64 bii_nUnitPrice;
    SHINE_ITEM_STRUCT bii_ItemInfo;
};

struct BoothItemManager
{
    std::list<BoothItemInfo> bim_ItemList;
    unsigned int bim_nLastCreatedHandleNo;
};

struct BoothStoreManager
{
    std::list<BoothStoreInfo> bsm_StoreList;
};

struct BoothManager
{
    BoothStoreManager bm_BoothStoreManager;
    BoothItemManager bm_BoothItemManager;
};

struct NPCRoleBase
{
    void* vfptr;
    ORToken nrb_argument;
};

struct NPCManager
{
    struct __declspec(align(1)) LinkInformTemplete
    {
        char index[20];
        char linktoserver[33];
        char linktoclient[33];
        unsigned int coordx;
        unsigned int coordy;
        unsigned __int16 direct;
        char Party;
    };

    struct NPCInformTemplete
    {
        char mobname[33];
        char map[20];
        __declspec(align(1)) unsigned int coordx;
        __declspec(align(1)) unsigned int coordy;
        __declspec(align(1)) __int16 direct_degree;
        char npcmenu;
        ORToken role;
        ORToken rolearg;
    };
	
    struct __declspec(align(4)) NPCIndexArray
    {
        NPCInformTemplete* pnt;
        NPCRoleBase* func;
        unsigned __int16 handle;
    };

    NPCIndexArray nm_BufferArray[1024];
    int nm_BufferPoint;
    OptionReader nm_NPCInfo;
};

struct Navigator
{
    struct VirtualMap
    {
        class FieldMap* vm_Map;
    };
};

enum OBJECT_SIGHT_STATE
{
    OSS_NONE = 0x0,
    OSS_WIDE = 0x1,
    OSS_MAX = 0x2,
};

enum DICE_TAISAI_BETTING
{
    DTB_EVEN = 0x0,
    DTB_ODD = 0x1,
    DTB_BIG = 0x2,
    DTB_SMALL = 0x3,
    DTB_PAIR_1 = 0x4,
    DTB_PAIR_2 = 0x5,
    DTB_PAIR_3 = 0x6,
    DTB_PAIR_4 = 0x7,
    DTB_PAIR_5 = 0x8,
    DTB_PAIR_6 = 0x9,
    DTB_TRIPLE_1 = 0xA,
    DTB_TRIPLE_2 = 0xB,
    DTB_TRIPLE_3 = 0xC,
    DTB_TRIPLE_4 = 0xD,
    DTB_TRIPLE_5 = 0xE,
    DTB_TRIPLE_6 = 0xF,
    DTB_ANYTRIPLE = 0x10,
    DTB_SUM_4 = 0x11,
    DTB_SUM_5 = 0x12,
    DTB_SUM_6 = 0x13,
    DTB_SUM_7 = 0x14,
    DTB_SUM_8 = 0x15,
    DTB_SUM_9 = 0x16,
    DTB_SUM_10 = 0x17,
    DTB_SUM_11 = 0x18,
    DTB_SUM_12 = 0x19,
    DTB_SUM_13 = 0x1A,
    DTB_SUM_14 = 0x1B,
    DTB_SUM_15 = 0x1C,
    DTB_SUM_16 = 0x1D,
    DTB_SUM_17 = 0x1E,
    DTB_DOMINO_12 = 0x1F,
    DTB_DOMINO_13 = 0x20,
    DTB_DOMINO_14 = 0x21,
    DTB_DOMINO_15 = 0x22,
    DTB_DOMINO_16 = 0x23,
    DTB_DOMINO_23 = 0x24,
    DTB_DOMINO_24 = 0x25,
    DTB_DOMINO_25 = 0x26,
    DTB_DOMINO_26 = 0x27,
    DTB_DOMINO_34 = 0x28,
    DTB_DOMINO_35 = 0x29,
    DTB_DOMINO_36 = 0x2A,
    DTB_DOMINO_45 = 0x2B,
    DTB_DOMINO_46 = 0x2C,
    DTB_DOMINO_56 = 0x2D,
    DTB_SINGLE_1 = 0x2E,
    DTB_SINGLE_2 = 0x2F,
    DTB_SINGLE_3 = 0x30,
    DTB_SINGLE_4 = 0x31,
    DTB_SINGLE_5 = 0x32,
    DTB_SINGLE_6 = 0x33,
    MAX_DICE_TAISAI_BETTING = 0x34,
};

enum DICE_TAISAI_BETTING_TYPE
{
    DTBT_BETTING = 0x0,
    DTBT_BETTING_CANCEL = 0x1,
    MAX_DICE_TAISAI_BETTING_TYPE = 0x2,
};

enum DICE_TAISAI_GAME_STATUS
{
    DTGS_NONE_BETTING = 0x0,
    DTGS_BETTING = 0x1,
    DTGS_ROLLING = 0x2,
    DTGS_STAND_BY = 0x3,
    MAX_DICE_TAISAI_GAME_STATUS = 0x4,
};

enum DICE_TAISAI_GAME_MODE
{
    DTGM_AUTO = 0x0,
    DTGM_MANUAL = 0x1,
    MAX_DICE_TAISAI_GAME_MODE = 0x2,
};

struct DiceRollApplyResult
{
    unsigned __int16 nError;
    unsigned __int16 lockindex;
    unsigned int nPlayerNo;
    __int64 nTotalDividend;
};

struct DiceTaiSaiBetting
{
    DICE_TAISAI_BETTING nBetting;
    unsigned int nMoney;
};

struct DiceRankInfo
{
    Name5 sCharID;
    unsigned int nWinCnt;
};

struct PROTO_NC_MINIHOUSE_FURNITURE_EMOTION_REQ
{
    unsigned __int16 nFurnitureHnd;
    char nPosition;
    char nEmotionNo;
};

struct FURNITURE_EMOTION_INFO
{
    unsigned __int16 nPlayerHandle;
    unsigned __int16 nFurnitureHnd;
    char nPosition;
    char nEmotionNo;
};

union ITEM_INVEN
{
    unsigned __int16 Inven;
    struct
	{
        unsigned __int16 Pos : 10;
        unsigned __int16 Type : 6;
    } str;
};

struct __declspec(align(1)) LastUpgradeStruct
{
    SHINE_ITEM_REGISTNUMBER upgrade_item_regnum;
    unsigned __int16 upgrade_item_id;
    char item_old_upgrade_level;
    char item_new_upgrade_level;
    unsigned __int16 left_item_id;
    unsigned __int16 right_item_id;
    unsigned __int16 middle_item_id;
    ItemOptionStorage::Element upgrade_randomoption;
};

struct __declspec(align(1)) TradeStruct
{
    struct __declspec(align(2))
    {
        unsigned __int16 chrhandle;
        unsigned int chrregnum;
    } proposee, proposer;
    unsigned int proposetime;
    unsigned __int16 lockindex;
    bool waitingTradeResFromDB;
};

struct __declspec(align(2)) TradeBoard
{
    void* tb_opposit;
    struct
	{
        char lock;
        char decide;
    } tb_Bit;
    struct
    {
        char invenslot;
    } tb_board[12];
    unsigned __int64 tb_cen;
};

struct __declspec(align(1)) ItemTotalInformation
{
    HOOK_PUB_M void iti_mkregnum(ushort id, int method, int zone, int world)
    {
        CallMemberFunction<ItemTotalInformation, void, ushort, int, int, int>(0x00640710, this, id, method, zone, world);
    }
	
    SHINE_ITEM_REGISTNUMBER iti_registnum;
    SHINE_ITEM_STRUCT iti_itemstruct;
};

struct __declspec(align(2)) PROTO_NC_ITEMDB_ADMINCREATEFAIL_ACK
{
    unsigned __int16 lockindex;
    unsigned int owner;
};


struct Parameter
{
    struct Cluster
    {
        int Str;
        int Con;
        int Dex;
        int Int;
        int Men;
        int WCmin;
        int WCmax;
        int AC;
        int TH;
        int TB;
        int MAmin;
        int MAmax;
        int MR;
        int MH;
        int MB;
        int AbsoluteAttack;
        int AbsoluteDefend;
        int AbsoluteHit;
        int AbsoluteBlock;
        int MoveSpeed;
        int HPRecover;
        int SPRecover;
        int CastingTime;
        int Critical;
        int PhisycalWeaponMastery;
        int MagicalWeaponMastery;
        int ShieldAC;
        int HitRate;
        int EvaRate;
        int MACri;
        int CriDam;
        int MagCriDam;
        int CriDamRate;
        int MagCriDamRate;
        int AttSpeed;
        int MaxHP;
        int MaxHP_2;
        int MaxSP;
        int HPAbsorption_Hitted;
        int SPAbsorption_Hitted;
        int HPAbsorption_Hit;
        int SPAbsorption_Hit;
        int CriticalTB;
        int RegistNone;
        int ResistPoison;
        int ResistDeaseas;
        int ResistCurse;
        int ResistMoveSpdDown;
        int ResistGTI;
        int MaxLP;
        int LPRecover;
    };

    struct ChangeByConditionParam
    {
        unsigned __int16 cbcp_nID;
        unsigned int cbcp_nCondition;
        unsigned int cbcp_nChange;
        int cbcp_nChangeParam;
        int cbcp_nCharged;
        char cbcp_nMaxValueNum;
        int* cbcp_pValue;
    };

    struct __declspec(align(4)) Container
    {
        Parameter::Cluster PureCharParam;
        struct
        {
            Parameter::Cluster Plus;
            Parameter::Cluster Rate;
        } Item, ItemPowerRate, Upgrade, WeaponTitle, PassiveSkill, AbnormalState, LastTune;
        Parameter::Cluster Total;
        struct
        {
            __int16 Burn;
            __int16 Poison;
            __int16 Desease;
            __int16 Blooding;
            __int16 PitBlooding;
        } DotDamagePlus;
        __int16 SPRate;
        __int16 RangeEvasion;
        struct
        {
            __int8 cannotmove_stun : 1;
            __int8 cannotmove_entangle : 1;
            __int8 cannotattack : 1;
        } flag;
        unsigned __int16 MissPercentFix;
        unsigned __int16 DamageReflection;
        unsigned __int16 ChangeAbilityInfo;
        unsigned __int16 HealRate;
        unsigned __int16 PassiveBuffKeepTimeUPRate;
        unsigned __int16 PassiveHealRate;
        unsigned __int16 PassiveCriDamageRatePlus;
        Parameter::ChangeByConditionParam PassiveHPDownRateWCMin;
        Parameter::ChangeByConditionParam PassiveHPDownRateWCMax;
        Parameter::ChangeByConditionParam PassiveHPDownRateMAMin;
        Parameter::ChangeByConditionParam PassiveHPDownRateMAMax;
        Parameter::ChangeByConditionParam PassiveHPDownRateAC;
        Parameter::ChangeByConditionParam PassiveHPDownRateMR;
        Parameter::ChangeByConditionParam PassiveMovingTBPlus;
        unsigned __int16 PhysicalImmuneRate;
        unsigned __int16 MagicalImmuneRate;
        unsigned int RangeOver;
        unsigned __int16 DMGMinusRate;
    };

};

enum UseEffectType
{
    UE_HPUP = 0x0,
    UE_SPUP = 0x1,
    UE_POISONREMOVE = 0x2,
    UE_DISEASEREMOVE = 0x3,
    UE_ABSTATE = 0x4,
    UE_CURSEREMOVE = 0x5,
    UE_NONE = 0x6,
    UE_HPSPALLUP = 0x7,
    UE_DEBUFALLREMOVE = 0x8,
    UE_ACTIONITEM = 0x9,
    MAX_USEEFFECTTYPE = 0xA,
};

struct __declspec(align(2)) ItemUseEffect
{
    char ItemIndex[32];
    UseEffectType UseEffectA;
    unsigned __int16 UseValueA;
    UseEffectType UseEffectB;
    unsigned __int16 UseValueB;
    UseEffectType UseEffectC;
    unsigned __int16 UseValueC;
    char UseAbstateName[32];
    unsigned int UseAbstateIndex;
};

struct ItemAttributeClass
{
    struct ItemAttributeClassVtbl
    {
        void* (__thiscall* __vecDelDtor)(ItemAttributeClass* pthis, unsigned int);
        BYTE gap4[24];
        unsigned int(__thiscall* iac_GetLot)(ItemAttributeClass* pthis, const SHINE_ITEM_STRUCT*);
        void(__thiscall* iac_SetLot)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*, unsigned int);
        int(__thiscall* iac_equipbriefinfo)(ItemAttributeClass* pthis, unsigned __int16, NETCOMMAND*, SHINE_ITEM_STRUCT*, int, unsigned __int16*, char*);
        int(__thiscall* iac_ItemClass)(ItemAttributeClass* pthis);
        char(__thiscall* iac_DropItemMake)(ItemAttributeClass* pthis, ItemTotalInformation*, const class ItemGroup*, int, unsigned __int16);
        int(__thiscall* iac_Getupgrade)(ItemAttributeClass* pthis, ItemTotalInformation*);
        ShineDateTime* (__thiscall* iac_GetDeteleDateTime)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*);
        ShineDateTime* (__thiscall* iac_SetDeteleDateTime)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*, int, const tm*, int);
        void(__thiscall* iac_FoodEat)(ItemAttributeClass* pthis, ItemTotalInformation*, int, int);
        int(__thiscall* iac_GetHungry)(ItemAttributeClass* pthis, ItemTotalInformation*);
        ShineItemAttr_ItemChest* (__thiscall* iac_Getitemchest)(ItemAttributeClass* pthis, ItemTotalInformation*);
        int(__thiscall* iac_wptitle_Setlicense)(ItemAttributeClass* pthis, ItemTotalInformation*, unsigned __int16, Name5*);
        unsigned int(__thiscall* iac_wptitle_mobkilladd)(ItemAttributeClass* pthis, ItemTotalInformation*, unsigned __int16, unsigned int);
        char(*(__thiscall* iac_wptitle_Gettitle)(ItemAttributeClass* pthis, ItemTotalInformation*))[21];
        bool(__thiscall* iac_wptitle_Settitle)(ItemAttributeClass* pthis, ItemTotalInformation*, unsigned int, char(*)[21]);
        unsigned __int16(__thiscall* iac_wptitle_Getlicencemob)(ItemAttributeClass* pthis, MobDataBox*, ItemDataBox*, ItemTotalInformation*);
        int(__thiscall* iac_StepGet)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*);
        char(__thiscall* iac_GetDuringRide)(ItemAttributeClass* pthis, const SHINE_ITEM_STRUCT*);
        void(__thiscall* iac_SetDuringRide)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*, char);
        int(__thiscall* iac_GetAmount)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*);
        void(__thiscall* iac_SetAmount)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*, int);
        ItemOptionStorage* (__thiscall* iac_GetItemOptionStruct)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*);
        char(__thiscall* iac_GetRandomOptionChangeCount)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*);
        void(__thiscall* iac_SetRandomOptionChangeCount)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*, char);
        unsigned __int16(__thiscall* iac_GetItemOptionUpgrade)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*, char);
        void(__thiscall* iac_SetItemOptionUpgrade)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*, char, unsigned __int16);
        void(__thiscall* iac_ClearItemOptionUpgrade)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*);
        void(__thiscall* iac_SetFurnitureKey)(ItemAttributeClass* pthis, ItemTotalInformation*, unsigned __int16);
        ShineDateTime* (__thiscall* iac_GetEndureEndTime)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*);
        int(__thiscall* iac_SetEndureEndTime)(ItemAttributeClass* pthis, ItemTotalInformation*, unsigned __int16, unsigned __int16, const tm*);
        int(__thiscall* iac_SetEndureEndTime2)(ItemAttributeClass* pthis, ItemTotalInformation*, ShineDateTime*);
        void(__thiscall* iac_SetEndureGrade)(ItemAttributeClass* pthis, ItemTotalInformation*, char);
        int(__thiscall* iac_GetChargedNumber)(ItemAttributeClass* pthis, ItemTotalInformation*);
        void(__thiscall* iac_SetChargedNumber)(ItemAttributeClass* pthis, ItemTotalInformation*, int);
        SHINE_PUT_ON_BELONGED_ITEM(__thiscall* iac_GetIsPutOnBelonged)(ItemAttributeClass* pthis, ItemTotalInformation*);
        int(__thiscall* iac_SetIsPutOnBelonged)(ItemAttributeClass* pthis, ItemTotalInformation*, SHINE_PUT_ON_BELONGED_ITEM);
        ShineDateTime* (__thiscall* iac_GetUseableDateTime)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*);
        ShineDateTime* (__thiscall* iac_SetUseableDateTime)(ItemAttributeClass* pthis, SHINE_ITEM_STRUCT*, int, const tm*, int);
        void(__thiscall* iac_SetHP)(ItemAttributeClass* pthis, ItemTotalInformation*, unsigned int);
        unsigned int(__thiscall* iac_GetHP)(ItemAttributeClass* pthis, ItemTotalInformation*);
        void(__thiscall* iac_SetGrade)(ItemAttributeClass* pthis, ItemTotalInformation*, char);
        char(__thiscall* iac_GetGrade)(ItemAttributeClass* pthis, ItemTotalInformation*);
        void(__thiscall* iac_SetRareFailCount)(ItemAttributeClass* pthis, ItemTotalInformation*, unsigned __int16);
        unsigned __int16(__thiscall* iac_GetRareFailCount)(ItemAttributeClass* pthis, ItemTotalInformation*);
    } vfptr;

    virtual void* Delete(uint) { return nullptr; }
    /*1*/ virtual void FN001();
    /*2*/ virtual void FN002();
    /*3*/ virtual void FN003();
    /*4*/ virtual void FN004();
    /*5*/ virtual void FN005();
    /*6*/ virtual void FN006();
    HOOK_PUB_M virtual uint iac_GetLot(SHINE_ITEM_STRUCT*);
    HOOK_PUB_M virtual void iac_SetLot(SHINE_ITEM_STRUCT*, unsigned int);
    HOOK_PUB_M virtual int iac_equipbriefinfo(unsigned __int16, NETCOMMAND*, SHINE_ITEM_STRUCT*, int, unsigned __int16*, char*);
    HOOK_PUB_M virtual int iac_ItemClass();
    HOOK_PUB_M virtual char iac_DropItemMake(ItemTotalInformation*, void*, int, unsigned __int16);
    HOOK_PUB_M virtual int iac_Getupgrade(ItemTotalInformation*);
    HOOK_PUB_M virtual ShineDateTime* iac_GetDeteleDateTime(SHINE_ITEM_STRUCT*);
    HOOK_PUB_M virtual ShineDateTime* iac_SetDeteleDateTime(SHINE_ITEM_STRUCT*, int, tm*, int);
    HOOK_PUB_M virtual void iac_FoodEat(ItemTotalInformation*, int, int);
    HOOK_PUB_M virtual int iac_GetHungry(ItemTotalInformation*);
    HOOK_PUB_M virtual ShineItemAttr_ItemChest* iac_Getitemchest(ItemTotalInformation*);
    HOOK_PUB_M virtual int iac_wptitle_Setlicense(ItemTotalInformation*, unsigned __int16, Name5*);
    HOOK_PUB_M virtual uint iac_wptitle_mobkilladd(ItemTotalInformation*, unsigned __int16, unsigned int);
    HOOK_PUB_M virtual void iac_wptitle_Gettitle();
    HOOK_PUB_M virtual bool iac_wptitle_Settitle(ItemTotalInformation*, unsigned int, char(*)[21]);
    HOOK_PUB_M virtual ushort iac_wptitle_Getlicencemob(MobDataBox*, ItemDataBox*, ItemTotalInformation*);
    HOOK_PUB_M virtual int iac_StepGet(SHINE_ITEM_STRUCT*);
    HOOK_PUB_M virtual char iac_GetDuringRide(SHINE_ITEM_STRUCT*);
    HOOK_PUB_M virtual void iac_SetDuringRide(SHINE_ITEM_STRUCT*, char);
    HOOK_PUB_M virtual int iac_GetAmount(SHINE_ITEM_STRUCT*);
    HOOK_PUB_M virtual void iac_SetAmount(SHINE_ITEM_STRUCT*, int);
    HOOK_PUB_M virtual ItemOptionStorage* iac_GetItemOptionStruct(SHINE_ITEM_STRUCT*);
    HOOK_PUB_M virtual char iac_GetRandomOptionChangeCount(SHINE_ITEM_STRUCT*);
    HOOK_PUB_M virtual void iac_SetRandomOptionChangeCount(SHINE_ITEM_STRUCT*, char);
    HOOK_PUB_M virtual ushort iac_GetItemOptionUpgrade(SHINE_ITEM_STRUCT*, char);
    HOOK_PUB_M virtual void iac_SetItemOptionUpgrade(SHINE_ITEM_STRUCT*, char, unsigned __int16);
    HOOK_PUB_M virtual void iac_ClearItemOptionUpgrade(SHINE_ITEM_STRUCT*);
    HOOK_PUB_M virtual void iac_SetFurnitureKey(ItemTotalInformation*, unsigned __int16);
    HOOK_PUB_M virtual ShineDateTime* iac_GetEndureEndTime(SHINE_ITEM_STRUCT*);
    HOOK_PUB_M virtual int iac_SetEndureEndTime(ItemTotalInformation*, unsigned __int16, unsigned __int16, tm*);
    HOOK_PUB_M virtual int iac_SetEndureEndTime(ItemTotalInformation*, ShineDateTime*);
    HOOK_PUB_M virtual void iac_SetEndureGrade(ItemTotalInformation*, char);
    HOOK_PUB_M virtual int iac_GetChargedNumber(ItemTotalInformation*);
    HOOK_PUB_M virtual void iac_SetChargedNumber(ItemTotalInformation*, int);
    HOOK_PUB_M virtual SHINE_PUT_ON_BELONGED_ITEM iac_GetIsPutOnBelonged(ItemTotalInformation*);
    HOOK_PUB_M virtual int iac_SetIsPutOnBelonged(ItemTotalInformation*, SHINE_PUT_ON_BELONGED_ITEM);
    HOOK_PUB_M virtual ShineDateTime* iac_GetUseableDateTime(SHINE_ITEM_STRUCT*);
    HOOK_PUB_M virtual ShineDateTime* iac_SetUseableDateTime(SHINE_ITEM_STRUCT*, int, tm*, int);
    HOOK_PUB_M virtual void iac_SetHP(ItemTotalInformation*, unsigned int);
    HOOK_PUB_M virtual uint iac_GetHP(ItemTotalInformation*);
    HOOK_PUB_M virtual void iac_SetGrade(ItemTotalInformation*, char);
    HOOK_PUB_M virtual char iac_GetGrade(ItemTotalInformation*);
    HOOK_PUB_M virtual void iac_SetRareFailCount(ItemTotalInformation*, unsigned __int16);
    HOOK_PUB_M virtual ushort iac_GetRareFailCount(ItemTotalInformation*);
};

struct ItemInventoryCell
{
    ItemTotalInformation iic_Item;
    ItemAttributeClass* iic_AttrProc;
};

const struct __declspec(align(2)) ChargedEffectContainer
{
    char cec_SilverWingCoolTime_Minute;
    unsigned __int16 cec_HPStoneLimit;
    unsigned __int16 cec_SPStoneLimit;
    struct
    {
        char bless;
        unsigned __int16 blesshandle;
    } cec_ProveOfBless;
    char cec_MoreInven;
    char cec_MoreStorage;
    char cec_StreetBoothSlot;
    char cec_LighteningPickParts;
    unsigned __int16 cec_MaxHPRate;
    unsigned __int16 cec_MaxSPRate;
    unsigned __int16 cec_AttackForceRate1024;
    unsigned __int16 cec_DefendForceRate1024;
    unsigned __int16 cec_ItemDropRate;
    char cec_MoverNotHungry;
    char cec_MoreStat;
    unsigned __int16 cec_ExpBonus;
    unsigned __int16 cec_ItemPowerAttack;
    unsigned __int16 cec_ItemPowerDefence;
    unsigned __int16 cec_ProductCastTimeRate;
    unsigned __int16 cec_ProductMasteryRate;
    char cec_StorageAnywhere;
    unsigned __int16 cec_MaxLPRate;
    char cec_IsAutoPathFind;
    char cec_ChatFontColor;
    char cec_ChatBalloonColor;
    char cec_ChatColor;
    char cec_ExpHold;
};

struct ItemBag
{
	
    virtual ItemInventoryCell* ib_GetInventoryCell(int);
    virtual int ib_BagSizeInput(ChargedEffectContainer*);
    virtual int ib_BagSizeOutput();
    virtual char ib_GetInvenType();
};

struct SpecialItemIdent
{
    unsigned __int16 sii_cenid;
    unsigned __int16 sii_recall;
    unsigned __int16 sii_silverwing;
    unsigned __int16 sii_kqrewardchest;
    unsigned __int16 sii_FreeStatRedistAll;
    unsigned __int16 sii_SkillEmpowRedistAll;
    unsigned __int16 sii_FreeStatRedistPoint;
    unsigned __int16 sii_SkillEmpowRedistPoint;
    unsigned __int16 sii_WeaponLicenseClear;
    unsigned __int16 sii_MiniHouse_MushRoom;
    unsigned __int16 sii_MagicPortionHP0;
    unsigned __int16 sii_MagicPortionHP1;
    unsigned __int16 sii_MagicPortionHP2;
    unsigned __int16 sii_MagicPortionHP3;
    unsigned __int16 sii_MagicPortionSP0;
    unsigned __int16 sii_MagicPortionSP1;
    unsigned __int16 sii_MagicPortionSP2;
    unsigned __int16 sii_MagicPortionSP3;
    unsigned __int16 sii_Roar;
    unsigned __int16 sii_SkillErase;
    unsigned __int16 sii_SparrowWing;
    unsigned __int16 sii_SparrowFeather;
    unsigned __int16 sii_WingStone;
    unsigned __int16 sii_BossMobDetector;
    unsigned __int16 sii_ProposeRing;
    unsigned __int16 sii_InvitationCard;
    unsigned __int16 sii_WeddingCoupon;
    unsigned __int16 sii_WeddingPresent;
    unsigned __int16 sii_ImmediateDivorce;
    unsigned __int16 sii_Karis;
    unsigned __int16 sii_GuildReName;
    unsigned __int16 sii_GuildReType;
    unsigned __int16 sii_JustReviveItem;
    unsigned __int16 sii_DiceTaiSaiMoneyCard;
    unsigned __int16 sii_EnchantSocketRemover;
    unsigned __int16 sii_EnchantSocketDrill;
    unsigned __int16 sii_UpgradeMoverFeedType;
    unsigned __int16 sii_RandomOptionChange;
    unsigned __int16 sii_ClassChange;
    unsigned __int16 sii_MapLink;
    unsigned __int16 sii_RandomOptionRecoverCountLimit;
};

enum ItemTypeEnum
{
    ITEMTYPE_EQU = 0x0,
    ITEMTYPE_EXH = 0x1,
    ITEMTYPE_ETC = 0x2,
    ITEMTYPE_QUEST = 0x3,
    ITEMTYPE_STARTQUEST = 0x4,
    ITEMTYPE_VIP = 0x5,
    ITEMTYPE_CONFIRM = 0x6,
    MAX_ITEMTYPEENUM = 0x7,
};

enum ItemClassEnum
{
    ITEMCLASS_BYTELOT = 0x0,
    ITEMCLASS_WORDLOT = 0x1,
    ITEMCLASS_DWRDLOT = 0x2,
    ITEMCLASS_QUESTITEM = 0x3,
    ITEMCLASS_AMULET = 0x4,
    ITEMCLASS_WEAPON = 0x5,
    ITEMCLASS_ARMOR = 0x6,
    ITEMCLASS_SHIELD = 0x7,
    ITEMCLASS_BOOT = 0x8,
    ITEMCLASS_FURNITURE = 0x9,
    ITEMCLASS_DECORATION = 0xA,
    ITEMCLASS_SKILLSCROLL = 0xB,
    ITEMCLASS_RECALLSCROLL = 0xC,
    ITEMCLASS_BINDITEM = 0xD,
    ITEMCLASS_UPSOURCE = 0xE,
    ITEMCLASS_ITEMCHEST = 0xF,
    ITEMCLASS_WTLICENCE = 0x10,
    ITEMCLASS_KQ = 0x11,
    ITEMCLASS_HOUSESKIN = 0x12,
    ITEMCLASS_UPRED = 0x13,
    ITEMCLASS_UPBLUE = 0x14,
    ITEMCLASS_KQSTEP = 0x15,
    ITEMCLASS_FEED = 0x16,
    ITEMCLASS_RIDING = 0x17,
    ITEMCLASS_AMOUNT = 0x18,
    ITEMCLASS_UPGOLD = 0x19,
    ITEMCLASS_COSWEAPON = 0x1A,
    ITEMCLASS_ACTIONITEM = 0x1B,
    ITEMCLASS_GBCOIN = 0x1C,
    ITEMCLASS_CAPSULE = 0x1D,
    ITEMCLASS_CLOSEDCARD = 0x1E,
    ITEMCLASS_OPENCARD = 0x1F,
    ITEMCLASS_MONEY = 0x20,
    ITEMCLASS_NOEFFECT = 0x21,
    ITEMCLASS_ENCHANT = 0x22,
    ITEMCLASS_ACTIVESKILL = 0x23,
    ITEMCLASS_PUP = 0x24,
    ITEMCLASS_COSSHIELD = 0x25,
    ITEMCLASS_BRACELET = 0x26,
    MAX_ITEMCLASSENUM = 0x27,
};

enum ItemEquipEnum
{
    ITEMEQUIP_NONE = 0x0,
    ITEMEQUIP_HAT = 0x1,
    ITEMEQUIP_NOUSE03 = 0x2,
    ITEMEQUIP_NOUSE01 = 0x3,
    ITEMEQUIP_NOUSE02 = 0x4,
    ITEMEQUIP_FACETATTOO = 0x5,
    ITEMEQUIP_NECKLACE = 0x6,
    ITEMEQUIP_BODY = 0x7,
    ITEMEQUIP_BODYACC = 0x8,
    ITEMEQUIP_BACK = 0x9,
    ITEMEQUIP_LEFTHAND = 0xA,
    ITEMEQUIP_LEFTHANDACC = 0xB,
    ITEMEQUIP_RIGHTHAND = 0xC,
    ITEMEQUIP_RIGHTHANDACC = 0xD,
    ITEMEQUIP_BRACELET = 0xE,
    ITEMEQUIP_LEFTRING = 0xF,
    ITEMEQUIP_RIGHTRING = 0x10,
    ITEMEQUIP_COSEFF = 0x11,
    ITEMEQUIP_TAIL = 0x12,
    ITEMEQUIP_LEG = 0x13,
    ITEMEQUIP_LEGACC = 0x14,
    ITEMEQUIP_SHOES = 0x15,
    ITEMEQUIP_SHOESACC = 0x16,
    ITEMEQUIP_EARRING = 0x17,
    ITEMEQUIP_MOUTH = 0x18,
    ITEMEQUIP_MINIMON = 0x19,
    ITEMEQUIP_EYE = 0x1A,
    ITEMEQUIP_HATACC = 0x1B,
    ITEMEQUIP_MINIMON_R = 0x1C,
    ITEMEQUIP_SHIELDACC = 0x1D,
    MAX_ITEMEQUIPENUM = 0x1E,
};

enum AuctionGroup
{
    AG_ALL = 0x0,
    AG_M_WEAPON = 0x1,
    AG_M_ARMOR = 0x2,
    AG_M_ACCESSORY = 0x3,
    AG_M_PRODUCE = 0x4,
    AG_M_ENCHANT = 0x5,
    AG_M_RAW = 0x6,
    AG_M_ETC = 0x7,
    AG_S_ONEHANDSWORD = 0x8,
    AG_S_TWOHANDSWORD = 0x9,
    AG_S_AXE = 0xA,
    AG_S_MACE = 0xB,
    AG_S_HAMMER = 0xC,
    AG_S_BOW = 0xD,
    AG_S_CBOW = 0xE,
    AG_S_STAFF = 0xF,
    AG_S_WAND = 0x10,
    AG_S_CLAW = 0x11,
    AG_S_DSWORD = 0x12,
    AG_S_FIGHTER = 0x13,
    AG_S_CLERIC = 0x14,
    AG_S_ARCHER = 0x15,
    AG_S_MAGE = 0x16,
    AG_S_JOKER = 0x17,
    AG_S_NECK = 0x18,
    AG_S_EARRING = 0x19,
    AG_S_RING = 0x1A,
    AG_S_SCROLL = 0x1B,
    AG_S_POTION = 0x1C,
    AG_S_STONE = 0x1D,
    AG_S_FOOD = 0x1E,
    AG_S_ENCHANT = 0x1F,
    AG_S_PRODRAW = 0x20,
    AG_S_FARM = 0x21,
    AG_S_MOVER = 0x22,
    AG_S_MINIHOUSE = 0x23,
    AG_S_COSTUME = 0x24,
    AG_S_ABILLITY = 0x25,
    AG_S_EMOTION = 0x26,
    AG_S_ETC = 0x27,
    AG_S_BLADE = 0x28,
    AG_S_SENTINEL = 0x29,
    AG_S_BRACELET = 0x2A,
    MAX_AUCTIONGROUP = 0x2B,
};

enum GradeType
{
    GT_NORMAL = 0x0,
    GT_NAMED = 0x1,
    GT_RARE = 0x2,
    GT_UNIQUE = 0x3,
    GT_CHARGE = 0x4,
    GT_SET = 0x5,
    GT_LEGENDARY = 0x6,
    GT_MYTHIC = 0x7,
    MAX_GRADETYPE = 0x8,
};

enum UseClassType
{
    UCT_NONE = 0x0,
    UCT_ALL = 0x1,
    UCT_FIGHTER_ALL = 0x2,
    UCT_CLEVERFIGHTER_AND_OVER = 0x3,
    UCT_WARRIOR_AND_OVER = 0x4,
    UCT_WARRIOR_OVER = 0x5,
    UCT_GLADIATOR_ONLY = 0x6,
    UCT_KNIGHT_ONLY = 0x7,
    UCT_CLERIC_ALL = 0x8,
    UCT_HIGHCLERIC_AND_OVER = 0x9,
    UCT_PALADIN_AND_OVER = 0xA,
    UCT_GUARDIAN_ONLY = 0xB,
    UCT_HOLYKNIGHT_ONLY = 0xC,
    UCT_PALADIN_OVER = 0xD,
    UCT_ARCHER_ALL = 0xE,
    UCT_HAWKARCHER_AND_OVER = 0xF,
    UCT_SCOUT_AND_OVER = 0x10,
    UCT_RANGER_ONLY = 0x11,
    UCT_SHARPSHOOTER_ONLY = 0x12,
    UCT_SCOUT_OVER = 0x13,
    UCT_MAGE_ALL = 0x14,
    UCT_WIZMAGE_AND_OVER = 0x15,
    UCT_ENCHANTER_AND_OVER = 0x16,
    UCT_WIZARD_ONLY = 0x17,
    UCT_WARLOCK_ONLY = 0x18,
    UCT_ENCHANTER_OVER = 0x19,
    UCT_SENTINEL_EXCLUDE = 0x1A,
    UCT_JOKER_ALL = 0x1B,
    UCT_CHASER_AND_OVER = 0x1C,
    UCT_CRUEL_AND_OVER = 0x1D,
    UCT_ASSASSIN_ONLY = 0x1E,
    UCT_CLOSER_ONLY = 0x1F,
    UCT_CRUEL_OVER = 0x20,
    UCT_SENTINEL_ALL = 0x21,
    UCT_SAVIOR_ONLY = 0x22,
    UCT_DEEPER_SKILL = 0x23,
    UCT_SHIELD = 0x24,
    UCT_CLASS_CHANGE = 0x25,
    UCT_SHIELD_NOT_GLA = 0x26,
    MAX_USECLASSTYPE = 0x27,
};

enum WeaponTypeEnum
{
    WT_NONE = 0x0,
    WT_SWORD = 0x1,
    WT_BOW = 0x2,
    WT_STAFF = 0x3,
    WT_AXE = 0x4,
    WT_MACE = 0x5,
    WT_SPIKE = 0x6,
    WT_FIST = 0x7,
    WT_BODY = 0x8,
    WT_STONE = 0x9,
    WT_CROSSBOW = 0xA,
    WT_WAND = 0xB,
    WT_SPEAR = 0xC,
    WT_HAMMER = 0xD,
    WT_SPECIAL = 0xE,
    WT_PRODUCTIONTOOL = 0xF,
    WT_INVINCIBLEHAMMER = 0x10,
    WT_DSWORD = 0x11,
    WT_CLAW = 0x12,
    WT_BLADE = 0x13,
    WT_RANGE_PY = 0x14,
    WT_TSWORD = 0x15,
    MAX_WEAPONTYPEENUM = 0x16,
};

enum ArmorTypeEnum
{
    AT_NONE = 0x0,
    AT_CLOTH = 0x1,
    AT_LEATHER = 0x2,
    AT_SCALE = 0x3,
    AT_PLATE = 0x4,
    AT_BONE = 0x5,
    AT_HARDSKIN = 0x6,
    AT_WEAKSKIN = 0x7,
    AT_BARTSKIN = 0x8,
    AT_GELSKIN = 0x9,
    AT_FURSKIN = 0xA,
    AT_SPECIAL = 0xB,
    MAX_ARMORTYPEENUM = 0xC,
};

enum E_BelongType
{
    BT_COMMON = 0x0,
    BT_NO_SELL = 0x1,
    BT_NO_DROP = 0x2,
    BT_NO_SELL_DROP = 0x3,
    BT_ACC = 0x4,
    BT_CHR = 0x5,
    BT_ONLY_DEL = 0x6,
    BT_NO_DEL = 0x7,
    BT_PUTON_ACC = 0x8,
    BT_PUTON_CHR = 0x9,
    BT_NO_STORAGE = 0xA,
    MAX_E_BELONGTYPE = 0xB,
};

enum ItemFuncEnum
{
    ITEMFUNC_NONE = 0x0,
    ITEMFUNC_ENDUREKIT_WC = 0x1,
    ITEMFUNC_ENDUREKIT_F = 0x2,
    ITEMFUNC_JUSTREVIVAL = 0x3,
    ITEMFUNC_CHANGE_NAME = 0x4,
    ITEMFUNC_CHANGE_RELATION = 0x5,
    ITEMFUNC_PUTON_CLEAR = 0x6,
    MAX_ITEMFUNCENUM = 0x7,
};

enum ISEType
{
    ISET_NONEEQUIP = 0x0,
    ISET_MINIMON = 0x1,
    ISET_MINIMON_R = 0x2,
    ISET_MINIMON_BOTH = 0x3,
    ISET_COS_TAIL = 0x4,
    ISET_COS_BACK = 0x5,
    ISET_COS_RIGHT = 0x6,
    ISET_COS_LEFT = 0x7,
    ISET_COS_TWOHAND = 0x8,
    ISET_COS_HEAD = 0x9,
    ISET_COS_EYE = 0xA,
    ISET_COS_3PIECE_AMOR = 0xB,
    ISET_COS_3PIECE_PANTS = 0xC,
    ISET_COS_3PIECE_BOOTS = 0xD,
    ISET_COS_2PIECE_PANTS = 0xE,
    ISET_COS_1PIECE = 0xF,
    ISET_NORMAL_BOOTS = 0x10,
    ISET_NORMAL_PANTS = 0x11,
    ISET_RING = 0x12,
    ISET_SHIELD = 0x13,
    ISET_NORMAL_AMOR = 0x14,
    ISET_WEAPON_RIGHT = 0x15,
    ISET_WEAPON_TWOHAND = 0x16,
    ISET_WEAPON_LEFT = 0x17,
    ISET_EARRING = 0x18,
    ISET_NORMAL_HAT = 0x19,
    ISET_NECK = 0x1A,
    ISET_COS_MASK = 0x1B,
    ISET_INVINCIBLEHAMMER = 0x1C,
    ISET_COS_MASK_EYE = 0x1D,
    ISET_COS_HIDE_HEAD = 0x1E,
    ISET_COS_EFF = 0x1F,
    ISET_COS_SHIELD = 0x20,
    ISET_BRACELET = 0x21,
    MAX_ISETYPE = 0x22,
};

struct __declspec(align(2)) ItemInfoServer
{
    unsigned int ID;
    char InxName[32];
    char MarketIndex[20];
    char City[1];
    char DropGroupA[40];
    char DropGroupB[40];
    char RandomOptionDropGroup[33];
    unsigned int Vanish;
    unsigned int looting;
    unsigned __int16 DropRateKilledByMob;
    unsigned __int16 DropRateKilledByPlayer;
    ISEType ISET_Index;
    char ItemSort_Index[32];
    char KQItem;
    char PK_KQ_USE;
    char KQ_Item_Drop;
    char PreventAttack;
};

struct GradeItemOption
{
    char ItemIndex[32];
    unsigned __int16 STR;
    unsigned __int16 CON;
    unsigned __int16 DEX;
    unsigned __int16 INT;
    unsigned __int16 MEN;
    unsigned __int16 ResistPoison;
    unsigned __int16 ResistDeaseas;
    unsigned __int16 ResistCurse;
    unsigned __int16 ResistMoveSpdDown;
    unsigned __int16 ToHitRate;
    unsigned __int16 ToBlockRate;
    unsigned __int16 MaxHP;
    unsigned __int16 MaxSP;
    unsigned __int16 WCPlus;
    unsigned __int16 MAPlus;
};

#pragma pack(push, 1)
struct __declspec(align(1)) ItemInfo
{
    unsigned __int16 ID;
    char InxName[32];
    char Name[64];
    ItemTypeEnum Type;
    ItemClassEnum Class;
    unsigned int MaxLot;
    ItemEquipEnum Equip;
    AuctionGroup ItemAuctionGroup;
    GradeType ItemGradeType;
    char TwoHand;
    unsigned int AtkSpeed;
    unsigned int DemandLv;
    unsigned int Grade;
    unsigned int MinWC;
    unsigned int MaxWC;
    unsigned int AC;
    unsigned int MinMA;
    unsigned int MaxMA;
    unsigned int MR;
    unsigned int TH;
    unsigned int TB;
    unsigned int WCRate;
    unsigned int MARate;
    unsigned int ACRate;
    unsigned int MRRate;
    unsigned int CriRate;
    unsigned int CriMinWc;
    unsigned int CriMaxWc;
    unsigned int CriMinMa;
    unsigned int CriMaxMa;
    unsigned int CrlTB;
    UseClassType UseClass;
    unsigned int BuyPrice;
    unsigned int SellPrice;
    char BuyDemandLv;
    unsigned int BuyFame;
    unsigned int BuyGToken;
    unsigned int BuyGBCoin;
    WeaponTypeEnum WeaponType;
    ArmorTypeEnum ArmorType;
    char UpLimit;
    unsigned __int16 BasicUpInx;
    unsigned __int16 UpSucRatio;
    unsigned __int16 UpLuckRatio;
    char UpResource;
    unsigned __int16 AddUpInx;
    unsigned int ShieldAC;
    unsigned int HitRatePlus;
    unsigned int EvaRatePlus;
    unsigned int MACriPlus;
    unsigned int CriDamPlus;
    unsigned int MagCriDamPlus;
    E_BelongType BT_Inx;
    char TitleName[32];
    char ItemUseSkill[32];
    char SetItemIndex[32];
    ItemFuncEnum ItemFunc;
};
#pragma pack(pop)

enum DelConditionType
{
    DCT_NONE = 0x0,
    DCT_LINKIN_ALL = 0x1,
    MAX_DELCONDITIONTYPE = 0x2,
};

struct ItemMoney
{
    char IM_ItemIDX[32];
    char IM_MoneyIDX[32];
    unsigned __int16 IM_MoneyLot;
};

struct __declspec(align(4)) ItemDataBox
{
    struct ItemDataBoxIndex
    {
        ItemInfo* data;
        ItemInfoServer* dataserv;
        GradeItemOption* itemoption;
        char MovingShot;
        unsigned __int16 AttackAngle;
        unsigned __int16 SetItemIndex;
        unsigned __int16 HitTimeArray[3];
        void* itemdroplog;
        char ItemSortOrder;
        DelConditionType eDelConditionType;
        ItemMoney* pBuyItemData;
    };
	
    HOOK_PUB_M SpecialItemIdent* idb_SpecialItems()
    {
        return CallMemberFunction<ItemDataBox, SpecialItemIdent*>(0x00418FE0, this);
    }

	HOOK_PUB_M ItemDataBoxIndex* operator[](ushort itemId)
    {
        return CallMemberFunction<ItemDataBox, ItemDataBoxIndex*, ushort>(0x00419020, this, itemId);
    }

	HOOK_PUB_M ushort idb_2itemid(const char* index)
    {
        return CallMemberFunction<ItemDataBox, ushort, const char*>(0x00418FF0, this, index);
    }

    unsigned int idb_Itemspacies;
    unsigned int idb_maxItemhandle;
    BTree idb_btree;
    struct
	{
        char _size[0x4E8];
    } idb_BinData;
    ItemDataBoxIndex* idb_index;
    SpecialItemIdent idb_specialid;
};

enum SkillHitTp
{
    SHT_FROM_PY_NORMAL_HITRATE = 0x0,
    SHT_FROM_MA_NORMAL_HITRATE = 0x1,
    SHT_ALWAYHIT = 0x2,
    SHT_CURE = 0x3,
    SHT_DISPEL = 0x4,
    SHT_MANABURN = 0x5,
    MAX_SKILLHITTP = 0x6,
};

struct __declspec(align(2)) ActiveSkillInfoServer
{
    unsigned __int16 ID;
    char InxName[32];
    char UsualAttack;
    unsigned int SkilPyHitRate;
    unsigned int SkilMaHitRate;
    unsigned int PsySucRate;
    unsigned int MagSucRate;
    char StaLevel;
    unsigned int DmgIncRate;
    unsigned __int16 DmgIncValue;
    SkillHitTp SkillHitType;
    char ItremUseSkill;
    unsigned int AggroPerDamage;
    unsigned int AbsoluteAggro;
    char AttackStart;
    char AttackEnd;
    unsigned __int16 SwingTime;
    unsigned __int16 HitTime;
    char AddSoul;
};

enum WeaponDemandType
{
    DT_ONEHAND = 0x0,
    DT_TWOHAND = 0x1,
    DT_ALL = 0x2,
    DT_WEAPON = 0x3,
    DT_HAMMER = 0x4,
    DT_MACE = 0x5,
    DT_NONE = 0x6,
    DT_SHIELD = 0x7,
    DT_BOW = 0x8,
    DT_CBOW = 0x9,
    DT_STAFF = 0xA,
    DT_WAND = 0xB,
    DT_CLAW = 0xC,
    DT_DSWORD = 0xD,
    DT_BLADE = 0xE,
    MAX_WEAPONDEMANDTYPE = 0xF,
};

enum TargetType
{
    TARGET_ENEMY = 0x0,
    TARGET_ME = 0x1,
    TARGET_PARTY = 0x2,
    TARGET_FRIEND = 0x3,
    TARGET_SPOT = 0x4,
    TARGET_ALL = 0x5,
    TARGET_GROUP = 0x6,
    TARGET_ENEMYUSER = 0x7,
    TARGET_EVERY = 0x8,
    TARGET_ENEMYGUILD = 0x9,
    TARGET_MYGUILD = 0xA,
    TARGET_MYNPC = 0xB,
    TARGET_MYRAID = 0xC,
    TARGET_BOX = 0xD,
    TARGET_THISACTION = 0xE,
    TARGET_ATTACKME = 0xF,
    TARGET_DAMAGEBYME = 0x10,
    TARGET_THISSKILL = 0x11,
    TARGET_NONE = 0x12,
    MAX_TARGETTYPE = 0x13,
};

enum TargetState
{
    TS_LIVE = 0x0,
    TS_CORPSE = 0x1,
    TS_NONE = 0x2,
    MAX_TARGETSTATE = 0x3,
};

enum SkillEffectType
{
    SE_PHYSICDAMAGE = 0x0,
    SE_MAGICDAMAGE = 0x1,
    SE_FIREDAMAGE = 0x2,
    SE_COLDDAMAGE = 0x3,
    SE_LIGHTNINGDAMAGE = 0x4,
    SE_HEALING = 0x5,
    SE_TELEPORT = 0x6,
    SE_REVIVAL = 0x7,
    SE_CURE = 0x8,
    SE_DISPEL = 0x9,
    SE_WHOLEHEAL = 0xA,
    SE_DEFAULT = 0xB,
    SE_VOLLEY = 0xC,
    SE_SUMMON = 0xD,
    SE_METAMORPHOSIS = 0xE,
    SE_PYRATEDAMAGE = 0xF,
    MAX_SKILLEFFECTTYPE = 0x10,
};

enum SkillSpecial
{
    SS_NONE = 0x0,
    SS_HEALAMOUNT = 0x1,
    SS_CURE = 0x2,
    SS_DISPEL = 0x3,
    SS_TELEPORT = 0x4,
    SS_WHOLEHEALAMOUNT = 0x5,
    SS_MANABURN = 0x6,
    SS_UNDEADTODMG = 0x7,
    SS_DISPELALL = 0x8,
    SS_DISPELONE = 0x9,
    SS_THHPUP = 0xA,
    SS_DIEHPUP = 0xB,
    SS_REVIVAL = 0xC,
    SS_MAGICFIELD_TICK = 0xD,
    SS_MAGICFIELD_KEEP = 0xE,
    SS_STEALENCHANT = 0xF,
    SS_HPCONVERTSP = 0x10,
    SS_HPUPRATE = 0x11,
    SS_FLYDURINGCAST = 0x12,
    SS_SILVERWING = 0x13,
    SS_DISPELDEBUFF = 0x14,
    SS_DISPELCURSE = 0x15,
    SS_DISPELPOISON = 0x16,
    SS_DISPELDISEASE = 0x17,
    SS_WHOLEAGGRORATE = 0x18,
    SS_WARPING = 0x19,
    SS_DISPELRANDOM = 0x1A,
    SS_DETECT = 0x1B,
    SS_WHOLEAGGRORANGE = 0x1C,
    SS_HIDE = 0x1D,
    SS_Silience = 0x1E,
    SS_MESMERIZE = 0x1F,
    SS_SUMMON = 0x20,
    SS_METAMORPHOSIS = 0x21,
    SS_CROSSCOUNTER = 0x22,
    SS_DISPELDEEPER = 0x23,
    SS_DASH = 0x24,
    SS_DISPELBUFF = 0x25,
    SS_DASH2 = 0x26,
    SS_HPRATE = 0x27,
    SS_CURSETIMEADD = 0x28,
    SS_FIRETIMEADD = 0x29,
    SS_HOLDME = 0x2A,
    SS_JWALK = 0x2B,
    SS_POSIONTIMEADD = 0x2C,
    SS_SHOOTME = 0x2D,
    SS_DMGCOLLTIMEDOWN = 0x2E,
    SS_AREATYPE = 0x2F,
    SS_BOMBDISPELALL = 0x30,
    SS_MAGICFIELDPARTY = 0x31,
    SS_HEALFRIENDRATE = 0x32,
    SS_SETABSTATEFRIEND = 0x33,
    SS_RANDOMTARGETNUMBER = 0x34,
    SS_NEXTTARGETAREA = 0x35,
    SS_DMGDOWNRATE = 0x36,
    SS_MAXDMGDOWNRATE = 0x37,
    SS_SHOTSPEED = 0x38,
    SS_TARGETHPDOWNDMGUPRATE = 0x39,
    SS_JUMP = 0x3A,
    SS_SETABSTATEME = 0x3B,
    SS_NOTTARGET = 0x3C,
    SS_ABKEEPTIME = 0x3D,
    SS_TOPAGGRONO = 0x3E,
    SS_RANDOMTARGET = 0x3F,
    SS_MAGICFIELD_DELAY_START_TIME = 0x40,
    SS_DISPELABSTATE = 0x41,
    SS_BMP_MAGICFIELD_ROTATIONSPEED_RIGHT = 0x42,
    SS_MOVE_CHR = 0x43,
    SS_HIDE_CHR_START = 0x44,
    SS_HIDE_CHR_END = 0x45,
    SS_RECALL = 0x46,
    SS_DMGSHARE = 0x47,
    SS_SUCKHP = 0x48,
    SS_RANDOMTARGETSPOT = 0x49,
    MAX_SKILLSPECIAL = 0x4A,
};

#pragma pack(push, 1)
struct __declspec(align(1)) ActiveSkillInfo
{
    unsigned __int16 ID;
    char InxName[32];
    char Name[64];
    unsigned int Grade;
    unsigned int Step;
    unsigned int MaxStep;
    WeaponDemandType DemandType;
    char DemandSk[32];
    unsigned __int16 UseItem;
    unsigned int ItemNumber;
    unsigned int ItemOption;
    unsigned __int16 DemandItem1;
    unsigned __int16 DemandItem2;
    unsigned int SP;
    unsigned int SPRate;
    unsigned int HP;
    unsigned int HPRate;
    unsigned int LP;
    unsigned int Range;
    TargetType First;
    TargetType Last;
    char IsMovingSkill;
    unsigned __int16 UsableDegree;
    unsigned __int16 DirectionRotate;
    unsigned __int16 SkillDegree;
    TargetState SkillTargetState;
    unsigned int CastTime;
    unsigned int DlyTime;
    unsigned int DlyGroupNum;
    unsigned int DlyTimeGroup;
    unsigned int MinWC;
    unsigned int MinWCRate;
    unsigned int MaxWC;
    unsigned int MaxWCRate;
    unsigned int MinMA;
    unsigned int MinMARate;
    unsigned int MaxMA;
    unsigned int MaxMARate;
    unsigned int AC;
    unsigned int MR;
    unsigned int Area;
    unsigned int TargetNumber;
    UseClassType UseClass;
    char StaNameA[32];
    unsigned int StaStrengthA;
    unsigned int StaSucRateA;
    char StaNameB[32];
    unsigned int StaStrengthB;
    unsigned int StaSucRateB;
    char StaNameC[32];
    unsigned int StaStrengthC;
    unsigned int StaSucRateC;
    char StaNameD[32];
    unsigned int StaStrengthD;
    unsigned int StaSucRateD;
    unsigned int nIMPT[4];
    unsigned int nT0[5];
    unsigned int nT1[5];
    unsigned int nT2[5];
    unsigned int nT3[5];
    SkillEffectType EffectType;
    SkillSpecial SpecialIndexA;
    unsigned int SpecialValueA;
    SkillSpecial SpecialIndexB;
    unsigned int SpecialValueB;
    SkillSpecial SpecialIndexC;
    unsigned int SpecialValueC;
    SkillSpecial SpecialIndexD;
    unsigned int SpecialValueD;
    SkillSpecial SpecialIndexE;
    unsigned int SpecialValueE;
    char SkillClassifierA[32];
    char SkillClassifierB[32];
    char SkillClassifierC[32];
    char CannotInside;
    char DemandSoul;
    unsigned __int16 HitID;
};
#pragma pack(pop);

enum ActiveSkillGroupIndex
{
    NONE = 0x0,
    BattleBlow = 0x1,
    BenTear = 0x2,
    Binding = 0x3,
    Bleach = 0x4,
    Blessing = 0x5,
    Blind = 0x6,
    BodyForce = 0x7,
    BoneArrow = 0x8,
    ChainCasting = 0x9,
    ChainLightning = 0xA,
    ContinueBlade = 0xB,
    CrossCasting = 0xC,
    CrushStrike = 0xD,
    CurseMagic = 0xE,
    Deeper = 0xF,
    DegroSlash = 0x10,
    DispelMagic = 0x11,
    DispelTrick = 0x12,
    DivineShield = 0x13,
    DrainMind = 0x14,
    DynastyCombo = 0x15,
    ElectricShock = 0x16,
    ExplosionNova = 0x17,
    FatalCondition = 0x18,
    FinalDynastBlood = 0x19,
    FinalSwordForce = 0x1A,
    FireBall = 0x1B,
    FireBolt = 0x1C,
    FitBlood = 0x1D,
    FitPoison = 0x1E,
    FrostNova = 0x1F,
    GreatHeal = 0x20,
    HarmDefect = 0x21,
    HawkTalon = 0x22,
    Heal = 0x23,
    HolySmite = 0x24,
    IceBlast = 0x25,
    IceBolt = 0x26,
    IceField = 0x27,
    Inferno = 0x28,
    LightningBolt = 0x29,
    MagicBall = 0x2A,
    MagicBurst = 0x2B,
    MentalShout = 0x2C,
    MightyChop = 0x2D,
    MightyPunch = 0x2E,
    MightySoul = 0x2F,
    MoraleDecrease = 0x30,
    MultiBloodShot = 0x31,
    MultiShot = 0x32,
    NatureCasting = 0x33,
    Neglect = 0x34,
    NobleFrgrance = 0x35,
    NorthBreeze = 0x36,
    NorthTear = 0x37,
    PiercingGuard = 0x38,
    PoisonShot = 0x39,
    PowerBenTear = 0x3A,
    PowerDrain = 0x3B,
    PowerNorthBreeze = 0x3C,
    PowerNorthTear = 0x3D,
    PowerShot = 0x3E,
    PowerWeaponBlast = 0x3F,
    PuryImpact = 0x40,
    RedSlash = 0x41,
    ResistCurse = 0x42,
    Restore = 0x43,
    ReverseOrder = 0x44,
    Sacrifice = 0x45,
    SafeProtection = 0x46,
    SeverBone = 0x47,
    ShiningPurge = 0x48,
    ShockEnemy = 0x49,
    SilverLining = 0x4A,
    SnearKick = 0x4B,
    SnearShout = 0x4C,
    SpeedShield = 0x4D,
    SpiritFog = 0x4E,
    StealEnchant = 0x4F,
    SwordForce = 0x50,
    TomaHawk = 0x51,
    WeaponBlast = 0x52,
    Wield = 0x53,
    WindyRaid = 0x54,
    WolfClaw = 0x55,
    BBDI = 0x56,
    GDHM = 0x57,
    HDMC = 0x58,
    HHMM = 0x59,
    MRMD = 0x5A,
    MRSD = 0x5B,
    SBBF = 0x5C,
    SHMP = 0x5D,
    SWAI = 0x5E,
    WEMI = 0x5F,
    WEMI2 = 0x60,
    Dash = 0x61,
    HealReinforce = 0x62,
    BiffTimeIncrease = 0x63,
    HeroStrike = 0x64,
    Advent = 0x65,
    LightStrike = 0x66,
    FinalLight = 0x67,
    LightWind = 0x68,
    LightBlast = 0x69,
    LightJump = 0x6A,
    LightExplosion = 0x6B,
    LightOrb = 0x6C,
    ImpactLight = 0x6D,
    LightBurst = 0x6E,
    Recoup = 0x6F,
    LightTouch = 0x70,
    Treat = 0x71,
    LightMark = 0x72,
    LightShield = 0x73,
    LightField = 0x74,
    MoonLight = 0x75,
    SunLight = 0x76,
    MAX_ACTIVESKILLGROUPINDEX = 0x77,
};

struct ActiveSkillGroup
{
    char InxName[32];
    ActiveSkillGroupIndex ActiveSkillGroupIndex;
};

enum ToggleSkillEnum
{
    TS_HPRATEOFF = 0x0,
    MAX_TOGGLESKILLENUM = 0x1,
};

struct __declspec(align(2)) ToggleSkill
{
    char TS_SkillInx[32];
    ToggleSkillEnum TS_Condition;
    unsigned __int16 TS_Value;
};

enum ImagePinType
{
    IPT_ME = 0x0,
    IPT_TARGET = 0x1,
    IPT_SPOT = 0x2,
    MAX_IMAGEPINTYPE = 0x3,
};

struct RulesOfEngagement
{
    void* vfptr;
};

struct EnumStruct
{
    char exist;
    char _pad[0x2];
    int value;
};


struct SkillDataBox
{
    struct SpecialSkill
    {
        unsigned __int16 ss_PortionProductMain;
        unsigned __int16 ss_ScrollProductMain;
        unsigned __int16 ss_StoneProductMain;
        unsigned __int16 ss_ResolveProductMain;
        unsigned __int16 ss_CompoundProductMain;
        unsigned __int16 ss_SummonMate;
    };

    struct SkillDataIndex
    {
        struct AreaSkillInfo
        {
            char AreaStep;
            char BMPIndex[32];
            ImagePinType EffectTarget;
            char bIsDirection;
            int AreaCenter_X;
            int AreaCenter_Y;
            int AreaSize;
            int AreaSize_X;
            int AreaSize_Y;
            char** AreaBMP;
        };

        ActiveSkillInfoServer* sdi_ServInf;
        ActiveSkillInfo* sdi_Activ;
        std::vector<ActiveSkillGroup*> sdi_ActiveSkillGroups;
        std::vector<ToggleSkill*> sdi_ToggleData;
        std::vector<SkillDataBox::SkillDataIndex::AreaSkillInfo> sdi_Area;
        SkillDataBox::SkillDataIndex* sdi_PrevSkill;
        SkillDataBox::SkillDataIndex* sdi_NextSkill;
        struct
        {
            ABSTATEINDEX abstateidx;
            int strength;
            int sucrate;
        } sdi_Abstate[4];
        RulesOfEngagement* sdi_DamageRule;
        unsigned int sdi_AttackDist;
        EnumStruct sdi_HEALAMOUNT;
        EnumStruct sdi_CURE;
        EnumStruct sdi_DISPEL;
        EnumStruct sdi_TELEPORT;
        EnumStruct sdi_WHOLEHEALAMOUNT;
        EnumStruct sdi_MANABURN;
        EnumStruct sdi_UNDEADTODMG;
        EnumStruct sdi_DISPELALL;
        EnumStruct sdi_DISPELONE;
        EnumStruct sdi_DISPELRANDOM;
        EnumStruct sdi_WHOLEAGGRORATE;
        EnumStruct sdi_WHOLEAGGRORANGE;
        EnumStruct sdi_WARPING;
        EnumStruct sdi_DETECT;
        EnumStruct sdi_CROSSCOUNTER;
        EnumStruct sdi_THHPUP;
        EnumStruct sdi_DIEHPUP;
        EnumStruct sdi_REVIVAL;
        EnumStruct sdi_MAGICFIELD_TICK;
        EnumStruct sdi_MAGICFIELD_KEEP;
        EnumStruct sdi_STEALENCHANT;
        EnumStruct sdi_HPCONVERTSP;
        EnumStruct sdi_HPUPRATE;
        EnumStruct sdi_FLYDURINGCAST;
        EnumStruct sdi_SILVERWING;
        EnumStruct sdi_DISPELDEBUFF;
        EnumStruct sdi_DISPELCURSE;
        EnumStruct sdi_DISPELPOISON;
        EnumStruct sdi_DISPELDISEASE;
        EnumStruct sdi_DISPELDEEPER;
        EnumStruct sdi_WARPING_TARGET;
        EnumStruct sdi_JWALK;
        EnumStruct sdi_SHOOTME;
        EnumStruct sdi_FIRETIMEADD;
        EnumStruct sdi_CURSETIMEADD;
        EnumStruct sdi_HOLDME;
        EnumStruct sdi_POSIONTIMEADD;
        EnumStruct sdi_DMGCOLLTIMEDOWN;
        EnumStruct sdi_AREATYPE;
        EnumStruct sdi_BOMBDISPELALL;
        EnumStruct sdi_MAGICFIELD_PARTY;
        EnumStruct sdi_HEALFRIENDRATE;
        EnumStruct sdi_SETABSTATEFRIEND;
        EnumStruct sdi_RANDOMTARGETNUMBER;
        EnumStruct sdi_NEXTTARGETAREA;
        EnumStruct sdi_DMGDOWNRATE;
        EnumStruct sdi_MAXDMGDOWNRATE;
        EnumStruct sdi_SHOTSPEED;
        EnumStruct sdi_TARGETHPDOWNDMGUPRATE;
        EnumStruct sdi_JUMP;
        EnumStruct sdi_SETABSTATEME;
        EnumStruct sdi_NOTTARGET;
        EnumStruct sdi_ABKEEPTIME;
        EnumStruct sdi_RANDOMTARGET;
        EnumStruct sdi_TOPAGGRONO;
        EnumStruct sdi_MAGICFIELD_DELAY_START_TIME;
        EnumStruct sdi_BMP_MAGICFIELD_ROTATIONSPEED_RIGHT;
        EnumStruct sdi_DISPELABSTATE;
        EnumStruct sdi_RECALL;
        EnumStruct sdi_DMGSHARE;
        EnumStruct sdi_SUCKHP;
        EnumStruct sdi_RANDOMTARGETSPOT;
    };

    HOOK_PUB_M SkillDataBox::SkillDataIndex* operator[](ushort skillId)
    {
        return CallMemberFunction<SkillDataBox, SkillDataBox::SkillDataIndex*, ushort>(0x00448140, this, skillId);
    }

    struct
    {
        char _size[0x4c4];
    } sdb_BinData;
    unsigned int sdb_ActivSkillNum;
    unsigned int sdb_MaxSkillHandle;
    SkillDataBox::SkillDataIndex* sdb_ValidArray;
    unsigned int sdb_MaxValid;
    SkillDataBox::SpecialSkill sdb_SpecSkill;
};

namespace UseEffect
{
	struct UIE_Functions;

	struct UseItemBase
    {
        virtual void _Delete(uint);
        virtual ushort uib_CanUseItem(ShineObjectClass::ShinePlayer*, ItemTotalInformation*);
    	virtual char uib_DirectUse(ShineObjectClass::ShinePlayer*, int, ItemTotalInformation*);
        virtual void uib_AfterCast(ShineObjectClass::ShinePlayer*, ItemBag*, ItemDataBox::ItemDataBoxIndex*, char);
        virtual void uib_Effect(ShineObjectClass::ShineObject*, ItemTotalInformation*, UseEffect::UIE_Functions*);
    };

    struct __declspec(align(4)) UIE_Functions
    {
        ItemUseEffect* useeffectstruct;
        UseEffect::UseItemBase* useitemclass;
        SkillDataBox::SkillDataIndex* useskill;
        char broadcast;
    };
}

struct CHARSTATDISTSTR
{
    char Strength;
    char Constitute;
    char Dexterity;
    char Intelligence;
    char MentalPower;
    char RedistributePoint;
};

struct __declspec(align(1)) PLAYER_QUEST_DATA
{
    __int64 StartTime;
    __int64 EndTime;
    unsigned int RepeatCount;
    char ProgressStep;
    char End_NPCMobCount[5];
    __int8 End_Location : 1;
    __int8 End_Scenario : 1;
    unsigned __int16 End_RunningTimeSec;
};

struct PLAYER_QUEST_INFO
{
    unsigned __int16 ID;
    char Status;
    PLAYER_QUEST_DATA Data;
};

struct SKILL_EMPOWER
{
    unsigned __int16 damage : 4;
    unsigned __int16 sp : 4;
    unsigned __int16 keeptime : 4;
    unsigned __int16 cooltime : 4;
};

struct ABSTATEREADBLOCK
{
    unsigned __int16 abstateid;
    char strength;
    __declspec(align(1)) unsigned int pasttime;
    __declspec(align(1)) unsigned int resttime;
    __declspec(align(1)) unsigned __int16 restcount;
    __declspec(align(1)) SKILL_EMPOWER empower;
    struct __declspec(align(1))
    {
        char nLevel;
        int nAttackPower;
    } CasterInfo;
    struct
    {
        unsigned __int16 Index;
        unsigned __int16 Value;
    } setitem[4];
};

struct PROTO_SKILLREADBLOCKCLIENT
{
    unsigned __int16 skillid;
    __declspec(align(1)) unsigned int cooltime;
    struct
    {
        __int8 damage : 4;
        __int8 sp : 4;
        __int8 keeptime : 4;
        __int8 cooltime : 4;
    } empow;
    unsigned int mastery;
};

struct PROTO_SKILLREADBLOCK
{
    int savetime;
    PROTO_SKILLREADBLOCKCLIENT skilldata;
};

struct PROTO_ITEMPACKET_TOTAL
{
    char datasize;
    __declspec(align(1)) ITEM_INVEN location;
    ItemTotalInformation info;
};

struct CT_INFO
{
    char Type;
    __int8 ElementNo : 6;
    __int8 ElementValue : 2;
};

struct CHARACTER_TITLE_DB_SAVE
{
    unsigned __int16 NumOfValues;
    struct __declspec(align(1))
    {
        char Type;
        unsigned __int64 TitleValue;
    } TitleValues[];
};

struct CT_TITLE
{
    __int8 Element0 : 2;
    __int8 Element1 : 2;
    __int8 Element2 : 2;
    __int8 Element3 : 2;
};

struct CCharacterTitleData
{
    char _size[0x40];
};

struct CCharacterTitle
{
    struct CT_VIEW
    {
        char Type;
        char ElementNo;
    };

    CCharacterTitleData* m_pCharacterTitleData;
    CT_TITLE m_Titles[128];
    int m_NumOfView;
    CCharacterTitle::CT_VIEW m_ViewArray[512];
    char m_CurrentTitle;
    char m_CurrentTitleElement;
    unsigned __int16 m_CurrentTitleMobID;
    const char* m_pTitle;
};

struct CCharacterTitleZone : CCharacterTitle
{
    struct __declspec(align(8)) TitleValueStruct
    {
        unsigned __int64 TitleValue;
        int bTitleSave;
    };

    ShineObjectClass::ShineObject* m_pPlayer;
    CCharacterTitleZone::TitleValueStruct m_TitleValues[128];
    int m_MoneyGiveTimeValue;
    unsigned int m_MoneyGivenToRegNum;
    int m_MoneyBegTimeValue;
    unsigned int m_MoneyBegnFromRegNum;
    unsigned __int16 m_KilledByMobHandle;
    int m_KilledByMobTimeValue;
    unsigned __int16 m_PartyJoinPartyNo;
    int m_PartyJoinTimeValue;
    unsigned int m_BoothSellCharNo;
    unsigned int m_AuctionSellCharNo;
    SHINE_ITEM_REGISTNUMBER m_nUpgradeItemNo;
    char m_nUpgradeItemStatus;
    int m_ProcessedTime;
};

struct BattleStat
{
    char bs_ClearAtLink;
    unsigned int bs_KillScore;
    unsigned int bs_DamageAmount;
    unsigned int bs_HealAmount;
    unsigned int bs_SkillBlast;
    unsigned int bs_CriticalNum;
    unsigned int bs_HittedNum;
    unsigned int bs_KnockDownNum;
    unsigned int bs_Dead;
    unsigned int bs_Kill;
    unsigned int bs_Score;
};

struct InventoryLocking
{
    struct LockedCell
    {
        char _size[0xA0];
    };

    struct __declspec(align(4)) InventoryCellLock
    {
        void* vfptr;
        unsigned __int16 icl_Index;
    };
	
    struct __declspec(align(8)) InventoryCellLockList : InventoryLocking::InventoryCellLock
    {
        ShineObjectClass::ShinePlayer* icll_sp;
        List<InventoryLocking::LockedCell> icll_List;
        InventoryLocking::LockedCell icll_Array[192];
        char icll_AllLock;
    };

};

struct EquipmentViewSlot
{
    char bEquip;
    char nMainSlot;
    unsigned __int16 nItemID;
};

struct __declspec(align(4)) ItemEquipment : ItemBag
{
    ItemInventoryCell ie_Array[30];
    char ie_DecoActCount;
    unsigned __int16 ie_DecoActList[30];
    EquipmentViewSlot ie_ViewSlot[30];
};

struct ItemInventory : ItemBag
{
    ItemInventoryCell ii_Array[192];
};

struct ItemQuestItemBox : ItemBag
{
    ItemInventoryCell iqb_Array[5];
};

struct ItemMiniHouseBox : ItemBag
{
    ItemInventoryCell imhb_Array[35];
};

struct ItemActionItemBox
{
    char _size[0x34C];
};


struct CharacterInventory
{
    char _padEquipment[0xE54];
    ItemInventory ci_Inventory;
    ItemQuestItemBox ci_QuestBox;
    ItemMiniHouseBox ci_MiniHouse;
    ItemActionItemBox ci_ActionBox;
};

struct unnamed_type_sp_Item
{
    CharacterInventory itembag;
    InventoryLocking::InventoryCellLockList invenlocklist;
};

struct SpyNet
{
    enum SecretReportType
    {
        SRT_EOR = 0x0,
        SRT_GETHEAL = 0x1,
        SRT_SOMEONE_GIVE_ABSTATE = 0x2,
        SRT_SOMEONE_REMOVE_ABSTATE = 0x3,
        SRT_VANISH_ABSTATE = 0x4,
    };

    struct SecretReport
    {
        char _size[0x10];
    };

    struct EspionageAgent
    {
        SpyNet::SecretReport ea_SecretReport[16];
        BitANDInt ea_Pointer;
    };
};

struct __declspec(align(2)) PrimaryParameter
{
    struct PointSoulStone
    {
        unsigned int soul;
        unsigned int maxsoul;
        unsigned int buysoul;
    };

    unsigned int level;
    unsigned int strength;
    unsigned int constitution;
    unsigned int intelligence;
    unsigned int wizdom;
    unsigned int dexterity;
    unsigned int mentalpower;
    PrimaryParameter::PointSoulStone hpsoulstone;
    PrimaryParameter::PointSoulStone spsoulstone;
    unsigned int aap;
    unsigned int dap;
    unsigned int maxaep;
    unsigned int soulaep;
    unsigned int buysoulaep;
    unsigned int aepwc;
    unsigned int aepma;
    unsigned int maxdep;
    unsigned int souldep;
    unsigned int buysouldep;
    unsigned int depac;
    unsigned int depmr;
    unsigned int painresistance;
    unsigned int restraintresistance;
    unsigned int curseresistance;
    unsigned int shockresistance;
    unsigned __int16 LevelHP;
    unsigned __int16 LevelSP;
    unsigned int CharTitlePt;
    unsigned int SkillPwrPt;
    unsigned __int16 JobChangeDmgUp;
};

struct __declspec(align(4)) CharClass : OptionReader
{
    void* vfptr;
    PrimaryParameter* cc_array[151];
    PrimaryParameter cc_def;
};

struct ABNORMAL_STATE_BIT
{
    char statebit[99];
};

struct __declspec(align(1)) SHINE_COORD_TYPE
{
    SHINE_XY_TYPE xy;
    char dir;
};

struct PROTO_ITEMPACKET_INFORM
{
    char datasize;
    __declspec(align(1)) ITEM_INVEN location;
    SHINE_ITEM_STRUCT info;
};

struct ShineMultiTypeHandle
{
    enum HandleType
    {
        ALONE = 0x0,
        PARTY = 0x1,
        RAID = 0x2,
        ALL = 0x3,
    };

    HandleType m_type;
    unsigned int m_ShineHandle;
    unsigned int m_LooterCharRegNo;
};

struct MultiHitArgument
{
    int mha_HitStep;
    int mha_DamageRate;
    int mha_AraeStep;
    struct
    {
        int mha_AbStateRate;
        ABSTATEINDEX mha_AbStateIndex;
        int mha_AbStateStrength;
    } mha_AbState[4];
};

struct EngageArgument
{
    ShineObjectClass::ShineObject* att;
    ShineObjectClass::ShineObject* def;
    SkillDataBox::SkillDataIndex* sklinfo;
    SKILL_EMPOWER empower;
    char actionnumber;
    char attackcode;
    char iscritical;
    char ismiss;
    char isdead;
    char isshieldblock;
    char isresist;
    char isDamege2Heal;
    char isImmune;
    SHINE_XY_TYPE* attackloc;
    int damagerate;
    int crirateadd;
    MultiHitArgument* pMultiHitArg;
    int nBMPDamageRate;
};

struct __declspec(align(2)) SmashArgument
{
    char actionnumber;
    char attackcode;
    char iscritical;
    char isdead;
    SkillDataBox::SkillDataIndex* sklidx;
    SKILL_EMPOWER empower;
};

enum SubState
{
    SUBAB_STRRATE = 0x0,
    SUBAB_STRPLUS = 0x1,
    SUBAB_WCPLUS = 0x2,
    SUBAB_WCRATE = 0x3,
    SUBAB_ACPLUS = 0x4,
    SUBAB_ACRATE = 0x5,
    SUBAB_DEXPLUS = 0x6,
    SUBAB_TBPLUS = 0x7,
    SUBAB_TBRATE = 0x8,
    SUBAB_THPLUS = 0x9,
    SUBAB_THRATE = 0xA,
    SUBAB_INTPLUS = 0xB,
    SUBAB_MAPLUS = 0xC,
    SUBAB_MENPLUS = 0xD,
    SUBAB_MRPLUS = 0xE,
    SUBAB_MRRATE = 0xF,
    SUBAB_DAMAGESHIELD = 0x10,
    SUBAB_MANASHIELD = 0x11,
    SUBAB_SHIELDACRATE = 0x12,
    SUBAB_MOVESPEED = 0x13,
    SUBAB_ATKSPEED = 0x14,
    SUBAB_STUN = 0x15,
    SUBAB_BLOODING = 0x16,
    SUBAB_ENTANGLE = 0x17,
    SUBAB_MAXHPRATE = 0x18,
    SUBAB_MAXSPRATE = 0x19,
    SUBAB_DEADHPSPRECOVRATE = 0x1A,
    SUBAB_DOTDAMAGE = 0x1B,
    SUBAB_FEAR = 0x1C,
    SUBAB_CONHEAL = 0x1D,
    SUBAB_CASTINGTIMEPLUS = 0x1E,
    SUBAB_COOLTIMEREMOVE = 0x1F,
    SUBAB_MAGICATTACKNOUSE = 0x20,
    SUBAB_POISON = 0x21,
    SUBAB_DISEASE = 0x22,
    SUBAB_CURSE = 0x23,
    SUBAB_RESIST = 0x24,
    SUBAB_CRITICALRATE = 0x25,
    SUBAB_DEFAULT = 0x26,
    SUBAB_MAXHPPLUS = 0x27,
    SUBAB_MAXSPPLUS = 0x28,
    SUBAB_CONSPHEAL = 0x29,
    SUBAB_QUESTSTUN = 0x2A,
    SUBAB_WCMINUS = 0x2B,
    SUBAB_DEXMINUS = 0x2C,
    SUBAB_ACMINUS = 0x2D,
    SUBAB_MRMINUS = 0x2E,
    SUBAB_STRMINUS = 0x2F,
    SUBAB_THMINUS = 0x30,
    SUBAB_TBMINUS = 0x31,
    SUBAB_CURSEMR = 0x32,
    SUBAB_CURSETH = 0x33,
    SUBAB_CURSEAC = 0x34,
    SUBAB_CURSETB = 0x35,
    SUBAB_CURSEDEX = 0x36,
    SUBAB_CURSEWC = 0x37,
    SUBAB_INTRATE = 0x38,
    SUBAB_CURSECRITICAL = 0x39,
    SUBAB_SELFREVIVE = 0x3A,
    SUBAB_RANGESHIELDCOUNTER = 0x3B,
    SUBAB_HIDE = 0x3C,
    SUBAB_BLIND = 0x3D,
    SUBAB_DEADLYBLESSING = 0x3E,
    SUBAB_GUILDBUFAC = 0x3F,
    SUBAB_NATURALENEMY = 0x40,
    SUBAB_QUESTENTANGLE = 0x41,
    SUBAB_CONHPSPHEAL = 0x42,
    SUBAB_KNOCKBACK = 0x43,
    SUBAB_FATALKNOCKBACK = 0x44,
    SUBAB_EVENTTRANSFORM = 0x45,
    SUBAB_CAPTIVATE = 0x46,
    SUBAB_CANTHEAL = 0x47,
    SUBAB_CANTCHAT = 0x48,
    SUBAB_ACMODE = 0x49,
    SUBAB_MRMODE = 0x4A,
    SUBAB_ANGRY = 0x4B,
    SUBAB_DAMAGENEGLECT = 0x4C,
    SUBAB_TIMEATTACK = 0x4D,
    SUBAB_DETACHPROCESS = 0x4E,
    SUBAB_HUMARWCRATE = 0x4F,
    SUBAB_HUMARACRATE = 0x50,
    SUBAB_ACDOWNRATE = 0x51,
    SUBAB_GTI = 0x52,
    SUBAB_BURN = 0x53,
    SUBAB_FITBLOODING = 0x54,
    SUBAB_RANGEEVASION = 0x55,
    SUBAB_USESPRATE = 0x56,
    SUBAB_SOULFREE = 0x57,
    SUBAB_ONETIMECANNOTUSESKILL = 0x58,
    SUBAB_MOBAPU = 0x59,
    SUBAB_HELGANONE = 0x5A,
    SUBAB_HELGBALL = 0x5B,
    SUBAB_UBAUP = 0x5C,
    SUBAB_UBADOWN = 0x5D,
    SUBAB_BURNPAINME = 0x5E,
    SUBAB_BURNPAINFOE = 0x5F,
    SUBAB_AIRBORNE = 0x60,
    SUBAB_BOMBSHOT = 0x61,
    SUBAB_CROSSDROP = 0x62,
    SUBAB_METEOR = 0x63,
    SUBAB_USESPDOWN = 0x64,
    SUBAB_MENDOWNRATEME = 0x65,
    SUBAB_MENDOWNRATE = 0x66,
    SUBAB_CRIUPRATE = 0x67,
    SUBAB_DMGSHIELD = 0x68,
    SUBAB_CANNOTTARGET = 0x69,
    SUBAB_HIDEDAMAGE = 0x6A,
    SUBAB_MAGICFIELD = 0x6B,
    SUBAB_MINEREWARD = 0x6C,
    SUBAB_EXPRATE = 0x6D,
    SUBAB_DROPRATE = 0x6E,
    SUBAB_MARATE = 0x6F,
    SUBAB_SURPRISE = 0x70,
    SUBAB_DISPEL = 0x71,
    SUBAB_RANGEDMGDOWNRATE = 0x72,
    SUBAB_DMGSHIELDRATE = 0x73,
    SUBAB_DMGDOWNRATE = 0x74,
    SUBAB_MINHP = 0x75,
    SUBAB_DELCASTING = 0x76,
    SUBAB_RANGEDMGDOWNRATEATK = 0x77,
    MAX_SUBSTATE = 0x78,
};

enum SubAbstateAction
{
    SAA_NONE = 0x0,
    SAA_STRRATE = 0x1,
    SAA_STRPLUS = 0x2,
    SAA_WCPLUS = 0x3,
    SAA_WCRATE = 0x4,
    SAA_ACPLUS = 0x5,
    SAA_ACRATE = 0x6,
    SAA_DEXPLUS = 0x7,
    SAA_TBPLUS = 0x8,
    SAA_TBRATE = 0x9,
    SAA_THPLUS = 0xA,
    SAA_THRATE = 0xB,
    SAA_INTPLUS = 0xC,
    SAA_MAPLUS = 0xD,
    SAA_MENTALPLUS = 0xE,
    SAA_MRPLUS = 0xF,
    SAA_MRRATE = 0x10,
    SAA_SHIELDAMOUNT = 0x11,
    SAA_SHIELDACRATE = 0x12,
    SAA_NOMOVE = 0x13,
    SAA_SPEEDRATE = 0x14,
    SAA_ATTACKSPEEDRATE = 0x15,
    SAA_MAXHPRATE = 0x16,
    SAA_MAXSPRATE = 0x17,
    SAA_DEADHPSPRECOVRATE = 0x18,
    SAA_NOATTACK = 0x19,
    SAA_TICK = 0x1A,
    SAA_DOTDAMAGE = 0x1B,
    SAA_CONHEAL = 0x1C,
    SAA_CASTINGTIMEPLUS = 0x1D,
    SAA_HEALAMOUNT = 0x1E,
    SAA_POISONRESISTRATE = 0x1F,
    SAA_DISEASERESISTRATE = 0x20,
    SAA_CURSERESISTRATE = 0x21,
    SAA_CRITICALRATE = 0x22,
    SAA_MAXHPPLUS = 0x23,
    SAA_MAXSPPLUS = 0x24,
    SAA_INTRATE = 0x25,
    SAA_FEAR = 0x26,
    SAA_ALLSTATEPLUS = 0x27,
    SAA_REVIVEHEALRATE = 0x28,
    SAA_COUNT = 0x29,
    SAA_SILIENCE = 0x2A,
    SAA_DEADLYBLESSING = 0x2B,
    SAA_DAMAGERATE = 0x2C,
    SAA_TARGETENEMY = 0x2D,
    SAA_MARATE = 0x2E,
    SAA_HEALRATE = 0x2F,
    SAA_DOTRATE = 0x30,
    SAA_AWAY = 0x31,
    SAA_TOTALDAMAGERATE = 0x32,
    SAA_DISPELSPEEDRATE = 0x33,
    SAA_SETABSTATEME = 0x34,
    SAA_SETABSTATEFRIEND = 0x35,
    SAA_SETABSTATE = 0x36,
    SAA_AREA = 0x37,
    SAA_GTIRESISTRATE = 0x38,
    SAA_MAXHPRATEDAMAGE = 0x39,
    SAA_METAABILITY = 0x3A,
    SAA_METASKIN = 0x3B,
    SAA_MISSRATE = 0x3C,
    SAA_REFLECTDAMAGE = 0x3D,
    SAA_RELESEACTION = 0x3E,
    SAA_SCANENEMYUSER = 0x3F,
    SAA_TARGETALL = 0x40,
    SAA_HIDEENEMY = 0x41,
    SAA_TARGETNOTME = 0x42,
    SAA_DOTDIEDAMAGE = 0x43,
    SAA_ADDALLDOTDMG = 0x44,
    SAA_ADDBLOODINGDMG = 0x45,
    SAA_ADDPOISONDMG = 0x46,
    SAA_EVASIONAMOUNT = 0x47,
    SAA_USESPRATE = 0x48,
    SAA_ACMINUS = 0x49,
    SAA_ACDOWNRATE = 0x4A,
    SAA_SUBTRACTALLDOTDMG = 0x4B,
    SAA_SUBTRACTBLOODINGDMG = 0x4C,
    SAA_SUBTRACTPOISONDMG = 0x4D,
    SAA_ATKSPEEDDOWNRATE = 0x4E,
    SAA_AWAYBACK = 0x4F,
    SAA_CRITICALDOWNRATE = 0x50,
    SAA_DEXMINUS = 0x51,
    SAA_HEALAMOUNTMINUS = 0x52,
    SAA_MAMINUS = 0x53,
    SAA_MADOWNRATE = 0x54,
    SAA_MAXHPDOWNRATE = 0x55,
    SAA_MRMINUS = 0x56,
    SAA_MRDOWNRATE = 0x57,
    SAA_SPEEDDOWNRATE = 0x58,
    SAA_STRMINUS = 0x59,
    SAA_TBMINUS = 0x5A,
    SAA_TBDOWNRATE = 0x5B,
    SAA_THMINUS = 0x5C,
    SAA_THDOWNRATE = 0x5D,
    SAA_WCMINUS = 0x5E,
    SAA_WCDOWNRATE = 0x5F,
    SAA_DOTWCRATE = 0x60,
    SAA_TARGETNUMVER = 0x61,
    SAA_DOTMARATE = 0x62,
    SAA_MENDOWNRATE = 0x63,
    SAA_USESPDOWN = 0x64,
    SAA_CRIUPRATE = 0x65,
    SAA_MRSHIELDRATE = 0x66,
    SAA_ACSHIELDRATE = 0x67,
    SAA_MONSTERSTICK = 0x68,
    SAA_SETACTIVESKILL = 0x69,
    SAA_HPRATEDAMAGE = 0x6A,
    SAA_EXPRATE = 0x6B,
    SAA_DROPRATE = 0x6C,
    SAA_AWAYBACKSPOT = 0x6D,
    SAA_STOPANI = 0x6E,
    SAA_DOTDMGDOWNRATE = 0x6F,
    SAA_SHIELDRATE = 0x70,
    SAA_LPAMOUNT = 0x71,
    SAA_MINHP = 0x72,
    SAA_DMGDOWNRATE = 0x73,
    SAA_SPEEDRESISTRATE = 0x74,
    SAA_MELEE = 0x75,
    SAA_RANGE = 0x76,
    SAA_ALLSTATPLUS = 0x77,
    SAA_RANGEOVER = 0x78,
    MAX_SUBABSTATEACTION = 0x79,
};

struct __declspec(align(1)) SubAbStateInfo
{
    unsigned __int16 ID;
    char InxName[32];
    unsigned int Strength;
    SubState Type;
    char SubType;
    unsigned int KeepTime;
    SubAbstateAction ActionIndexA;
    unsigned int ActionArgA;
    SubAbstateAction ActionIndexB;
    unsigned int ActionArgB;
    SubAbstateAction ActionIndexC;
    unsigned int ActionArgC;
    SubAbstateAction ActionIndexD;
    unsigned int ActionArgD;
};

enum DispelAttr
{
    DA_NONE = 0x0,
    DA_GOOD = 0x1,
    DA_DEBUFF = 0x2,
    DA_DISEASE = 0x3,
    DA_POISON = 0x4,
    DA_CURSE = 0x5,
    DA_STUN = 0x6,
    DA_FEAR = 0x7,
    DA_DEEPER = 0x8,
    DA_HIDE = 0x9,
    DA_BOMB = 0xA,
    DA_CHARGED = 0xB,
    MAX_DISPELATTR = 0xC,
};

enum SubDispelAttr
{
    SDA_NONE = 0x0,
    SDA_STUN = 0x1,
    SDA_MOVESPEED = 0x2,
    SDA_FEAR = 0x3,
    SDA_BLOODING = 0x4,
    SDA_DEEPER = 0x5,
    SDA_BLIND = 0x6,
    SDA_REVERSE = 0x7,
    SDA_BIND = 0x8,
    SDA_MESMERIZE = 0x9,
    SDA_SEVERBONE = 0xA,
    SDA_KNOCKBACK = 0xB,
    SDA_TBMINUS = 0xC,
    SDA_GTIRESIST = 0xD,
    MAX_SUBDISPELATTR = 0xE,
};

enum AbStateSaveTypeEnum
{
    AST_NONE = 0x0,
    AST_LINK_LOGOFF = 0x1,
    AST_LINK_LOGOFF_DIE = 0x2,
    AST_LINK_DIE = 0x3,
    MAX_ABSTATESAVETYPEENUM = 0x4,
};

struct __declspec(align(1)) AbnormalStateInfo
{
    unsigned __int16 ID;
    char InxName[32];
    ABSTATEINDEX AbStataIndex;
    unsigned int KeepTimeRatio;
    char KeepTimePower;
    char StateGrade;
    char PartyState1[32];
    char PartyState2[32];
    char PartyState3[32];
    char PartyState4[32];
    char PartyState5[32];
    unsigned int PartyRange;
    unsigned int PartyEnchantNumber;
    char SubAbState[32];
    DispelAttr DispelIndex;
    SubDispelAttr SubDispelIndex;
    AbStateSaveTypeEnum AbStateSaveType;
    char MainStateInx[32];
    char Duplicate;
};

struct __declspec(align(1)) AbStateSaveTypeInfo
{
    AbStateSaveTypeEnum AbStateSaveType;
    char IsSaveLink;
    char IsSaveDie;
    char IsSaveLogoff;
};

namespace AbnormalStateDictionary
{
    struct AbState
    {
        struct AbStateStr
        {
            struct AbStateStrArgument
            {
                SubAbStateInfo* assa_info;
                struct
                {
                    SubAbstateAction action;
                    int value;
                } assa_Effect[4];
            };

            AbnormalStateInfo* index;
            AbStateSaveTypeInfo* pSaveTypeInfo;
            int* debuffresist;
            AbnormalStateDictionary::AbState::AbStateStr::AbStateStrArgument subabstate[40];
        };
    	
        HOOK_PUB_M AbStateStr* as_FromIndex(ABSTATEINDEX indx)
        {
            return CallMemberFunction<AbState, AbStateStr*, ABSTATEINDEX>(0x00401420, this, indx);
        }

        char _pad[0x1AC];
        AbnormalStateDictionary::AbState::AbStateStr* as_AbstateArray;
        unsigned int as_Number;
        unsigned int as_maxhandle;
        AbnormalStateDictionary::AbState::AbStateStr* as_StateIndexList[792];
        BTree as_BTreeID;
        BTree as_BTreeIndex;
    };

}

struct Metronome
{
    unsigned int m_NextTick;
    unsigned int m_TickInterval;
};

namespace SetItemData
{
    struct SetItemAbstateEffect
    {
        struct EffectBuffer
        {
            unsigned __int16 eb_Index;
            unsigned __int16 Argument_Base1000;
        };

        SetItemData::SetItemAbstateEffect::EffectBuffer siae_Buffer[4];
    };

}

struct MiscDataTable
{
    struct MiscData_Skill
    {
        enum RegenLoc
        {
            RL_CASTER = 0x0,
            RL_TARGET = 0x1,
        };

        enum MDS_AI
        {
            SAI_ROOT = 0x0,
            SAI_CHASE = 0x1,
            SAI_RAMPAGE = 0x2,
            SAI_ROAM = 0x3,
        };

        struct PolymorphAction
        {
            __int8 Move : 1;
            __int8 Attack : 1;
        };

        struct mds_Dead
        {
            __int8 ByDebuff : 1;
        };

        enum mds_ExploseTriggerObject
        {
            ETO_NONE = 0x0,
            ETO_ENEMY = 0x1,
            ETO_TARGET = 0x2,
            ETO_ALWAYS = 0x3,
            ETO_CASTERTARGET = 0x4,
            ETO_TARGETALL = 0x5,
        };

        enum ExploseEffectSkillTo
        {
            EEST_NONE = 0x0,
            EEST_MYLOC = 0x1,
            EEST_MYOBJ = 0x2,
            EEST_TARGETLOC = 0x3,
            EEST_TARGETOBJ = 0x4,
        };

        enum MDS_MST
        {
            MST_NONE = 0x0,
            MST_MULTI = 0x1,
        };

        enum MDS_ROAMINGTYPE
        {
            RT_NONE = 0x0,
            RT_STRAIGHT = 0x1,
            RT_RANDOM = 0x2,
        };

        unsigned __int16 mds_SkillID;
        unsigned __int16 mds_BreedMob;
        char mds_SummonNumber;
        MiscDataTable::MiscData_Skill::MDS_AI mds_AI;
        MiscDataTable::MiscData_Skill::RegenLoc mds_RegenLoc;
        ABSTATEINDEX mds_Abstate;
        unsigned __int16 mds_Polymorph;
        MiscDataTable::MiscData_Skill::PolymorphAction mds_PolymorphAction;
        char mds_IsThereNeutralizationItem;
        unsigned __int16 mds_NeutralizationItemArray[30];
        int mds_LifeTime_MilliSec;
        MiscDataTable::MiscData_Skill::mds_Dead mds_Dead;
        MiscDataTable::MiscData_Skill::mds_ExploseTriggerObject mds_ExploseTriggerObject;
        unsigned int mds_ExploseTriggerRange;
        unsigned __int16 ExploseEffectSkill;
        MiscDataTable::MiscData_Skill::ExploseEffectSkillTo ExploseEffectSkillTo;
        unsigned __int16 mds_ExplosionNumber;
        unsigned int mds_ExplosionDelay;
        MiscDataTable::MiscData_Skill::MDS_MST mds_MultiSummonType;
        unsigned __int16 mds_RegenDistance;
        MiscDataTable::MiscData_Skill::MDS_ROAMINGTYPE mds_RoamingType;
    };

    struct MiscData_AbState
    {
        char _size[0xC];
    };
	
    struct __declspec(align(4)) MiscData_VarifyByAbstate
    {
        typedef ActiveSkillGroupIndex AbnormalStateAttr;

        unsigned __int16 mdvba_Skill;
        MiscDataTable::MiscData_VarifyByAbstate::AbnormalStateAttr mdvba_Condition;
        __int16 mdvba_DamageRate;
        ABSTATEINDEX mdvba_NewState;
        __int16 mdvba_Crirate;
    };

    MiscDataTable::MiscData_Skill mdt_SkillDataArray[100];
    int mdt_SkillDataSize;
    MiscDataTable::MiscData_AbState mdt_AbStateDataArray[50];
    int mdt_AbStateDataSize;
    MiscDataTable::MiscData_VarifyByAbstate mdt_VarifAbstateArray[100];
    int mdt_VarifAbstateSize;
};

namespace AbnormalStateContainer
{
    enum EnchantFrom
    {
        EF_DATABASE = 0x0,
        EF_PARTYBUFF2MEMBER = 0x1,
        EF_PARTYBUFF2ME = 0x2,
        EF_JUSTENCHANTHIDE = 0x3,
        EF_JUSTENCHANTSWING = 0x4,
        EF_JUSTENCHANTBATTLEOBJECT = 0x5,
        EF_JUSTENCHANTSTEALENCHANT = 0x6,
        EF_JUSTENCHANTIMMORTALPLAYER = 0x7,
        EF_JUSTENCHANTIMMORTALMOB = 0x8,
        EF_JUSTENCHANTPINESCRIPT = 0x9,
        EF_JUSTENCHANTIMMORTALREVIVE = 0xA,
        EF_JUSTENCHANTITEMUSE = 0xB,
        EF_JUSTENCHANTGLOBALACTION = 0xC,
        EF_SKILLSPECIAL = 0xD,
    };

    struct AbStateElementSetData
    {
        SHINE_XY_TYPE CenterLoc;
    };

    struct AbstateElementInObject
    {
        AbstateElementInObject()
        {
            CallMemberFunction<AbstateElementInObject, void>(0x00406550, this);
        }
    	
        struct ASE_Tick
        {
            unsigned int start;
            unsigned int terminate;
            Metronome nextaction;
        };

        struct
        {
            __int8 f_Cured : 1;
            __int8 f_Dispeled : 1;
            __int8 f_SystemRemove : 1;
        } aeo_Flag;
        ABSTATEINDEX aeo_Index;
        struct
        {
            ShineObjectClass::ShineObject* obj;
            unsigned int chrregnum;
            char nLevel;
            int nAttackPower;
        } aeo_Caster;
        char aeo_Strength;
        AbnormalStateContainer::AbstateElementInObject::ASE_Tick aeo_Tick;
        struct
        {
            ABSTATEINDEX soul;
            AbnormalStateDictionary::AbState::AbStateStr* skillindex;
        } aeo_PartyEnchant[5];
        int aeo_RestCount;
        AbnormalStateContainer::AbStateElementSetData AbsSetData;
        SetItemData::SetItemAbstateEffect aeo_SetItemEffect;
        MiscDataTable::MiscData_AbState* aeo_MiscData;
        char _pad[0x74 - 0x6E];
    };

	struct AbstateListInObject
    {
        AbnormalStateContainer::AbstateElementInObject asl_Element[28];
        List<AbnormalStateContainer::AbstateElementInObject> asl_List;
    };
}

struct __declspec(align(2)) ProtoExtraCharacterData
{
    unsigned __int16 pecd_worldmanagerhandle;
    char pecd_dimension[0x8];
};

namespace BattleObjectGroup
{
    struct BattleObjectStruct
    {
        unsigned __int16 bos_Attacker;
        unsigned __int16 bos_Defender;
        int bos_Damage;
        int bos_Heal;
        int bos_AbsoluteAggro;
        int bos_DamageRateAggro;
        int bos_MyHealHit;
        int bos_MyHealKill;
        struct
        {
            struct
            {
                ABSTATEINDEX abstateidx;
                int strength;
                int empowkeeptime;
            } array[4];
            int statenum;
        } bos_AbstateList;
        struct
        {
            struct
            {
                ABSTATEINDEX abstateidx;
            } array[16];
            int statenum;
        } bos_DispelLst;
        ABSTATEINDEX bos_StealedEnchant;
    };
}

struct MoveManager
{
    enum MMState
    {
        MM_HALT = 0x0,
        MM_WALK = 0x1,
        MM_RUN = 0x2,
        MM_REINFORCEMOVE = 0x3,
    };

    MoveManager::MMState mm_state;
    ShineObjectClass::ShineMobileObject* mm_object;
    int mm_charSpeed;
    SHINE_XY_TYPE mm_startPos;
    SHINE_XY_TYPE mm_goalPos;
    unsigned int mm_startTime_ms;
    unsigned int mm_fullTime_ms;
    unsigned int mm_currTime_ms;
    unsigned int mm_lastTime_ms;
    unsigned int mm_leftTime_ms;
    struct __declspec(align(4))
    {
        unsigned int x;
        bool xPositive;
        unsigned int y;
        bool yPositive;
    } mm_vector;
};

struct TickTimer
{
    unsigned int m_CurDelayTime;
    unsigned int m_DelayTime;
    bool m_bEnable;
    unsigned int m_PrevCheckTime;
};

enum ActionTargetType
{
    ATT_TargetType = 0x0,
    ATT_MobGradeType = 0x1,
    ATT_MobType = 0x2,
    ATT_ChrClassType = 0x3,
    MAX_ACTIONTARGETTYPE = 0x4,
};

enum ActionActivityType
{
    AAT_AttackType = 0x0,
    AAT_RecoverType = 0x1,
    AAT_ABSTATEINDEX = 0x2,
    AAT_DispelAttr = 0x3,
    AAT_TargetAction = 0x4,
    AAT_SkillEffectIncreaseType = 0x5,
    AAT_ActionRangeType = 0x6,
    AAT_ActiveSkillGroupIndex = 0x7,
    AAT_ActionETCType = 0x8,
    AAT_SetItemEffectType = 0x9,
    MAX_ACTIONACTIVITYTYPE = 0xA,
};

struct __declspec(align(2)) ItemActionEffect
{
    unsigned __int16 EffectID;
    ActionTargetType EffectTarget;
    unsigned int EffectTargetValue;
    ActionActivityType EffectActivity;
    unsigned int EffectActivityValue;
    unsigned __int16 Value;
    unsigned __int16 Area;
};

struct IActCondition
{
    void* vfptr;
    void* _subjectValidator;
    void* _objectValidator;
    void* _conditionData;
};

struct IActEffect
{
    void* vfptr;
    ItemActionEffect* _effectData;
};

struct Action
{
    unsigned __int16 _ID;
    unsigned int _coolTime;
    unsigned __int16 _coolGroupID;
    std::set<IActCondition*> _conditions;
    std::set<IActEffect*> _effects;
};

struct __declspec(align(4)) ItemActionObserve
{
    virtual void* Delete(uint) { return nullptr; }

    void Attach(Action* pAction, unsigned __int16 ActionID, unsigned __int16 itemid)
    {
        CallMemberFunction<ItemActionObserve, void, Action*, ushort, ushort>(0x005D0850, this, pAction, ActionID, itemid);
    }
	
    unsigned __int16 iao_ListHandle;
    char _pad[0x2];
    Action* iao_pAction;
    unsigned __int16 iao_ActionID;
    unsigned __int16 iao_itemid;
    bool iao_IsEnchant;
};

enum MoveDirect
{
    MD_FORWARD = 0x0,
    MD_BACKWARD = 0x1,
};

struct SHINE_CHAR_STATVAR
{
    unsigned int base;
    unsigned int change;
};

struct CHAR_PARAMETER_DATA
{
    unsigned __int64 PrevExp;
    unsigned __int64 NextExp;
    SHINE_CHAR_STATVAR Strength;
    SHINE_CHAR_STATVAR Constitute;
    SHINE_CHAR_STATVAR Dexterity;
    SHINE_CHAR_STATVAR Intelligence;
    SHINE_CHAR_STATVAR Wizdom;
    SHINE_CHAR_STATVAR MentalPower;
    SHINE_CHAR_STATVAR WClow;
    SHINE_CHAR_STATVAR WChigh;
    SHINE_CHAR_STATVAR AC;
    SHINE_CHAR_STATVAR TH;
    SHINE_CHAR_STATVAR TB;
    SHINE_CHAR_STATVAR MAlow;
    SHINE_CHAR_STATVAR MAhigh;
    SHINE_CHAR_STATVAR MR;
    SHINE_CHAR_STATVAR MH;
    SHINE_CHAR_STATVAR MB;
    unsigned int MaxHp;
    unsigned int MaxSp;
    unsigned int MaxLp;
    unsigned int MaxAp;
    unsigned int MaxHPStone;
    unsigned int MaxSPStone;
    struct
    {
        unsigned int flag;
        unsigned int EPPysic;
        unsigned int EPMagic;
        unsigned int MaxStone;
    } PwrStone, GrdStone;
    SHINE_CHAR_STATVAR PainRes;
    SHINE_CHAR_STATVAR RestraintRes;
    SHINE_CHAR_STATVAR CurseRes;
    SHINE_CHAR_STATVAR ShockRes;
};

struct __declspec(align(2)) PLAYER_QUEST_DONE_INFO
{
    unsigned __int16 ID;
    __int64 tEndTime;
};

struct PARTMARK
{
    __int8 bIsStart : 1;
    __int8 bIsEnd : 1;
    __int8 nOrder : 6;
};

struct __declspec(align(2)) PROTO_CHARGEDBUFF_INFO
{
    unsigned int ChargedBuffKey;
    unsigned __int16 ChargedBuffID;
    ShineDateTime UseTime;
    ShineDateTime EndTime;
};

enum MobGradeType
{
    MGT_NORMAL = 0x0,
    MGT_CHIEF = 0x1,
    MGT_BOSS = 0x2,
    MGT_HERO = 0x3,
    MGT_ELITE = 0x4,
    MGT_NONE = 0x5,
    MAX_MOBGRADETYPE = 0x6,
};

enum MobType
{
    MT_HUMAN = 0x0,
    MT_MAGICLIFE = 0x1,
    MT_SPIRIT = 0x2,
    MT_BEAST = 0x3,
    MT_ELEMENTAL = 0x4,
    MT_UNDEAD = 0x5,
    MT_NPC = 0x6,
    MT_OBJECT = 0x7,
    MT_MINE = 0x8,
    MT_HERB = 0x9,
    MT_WOOD = 0xA,
    MT_NONAME = 0xB,
    MT_NOTARGET = 0xC,
    MT_NOTARGET2 = 0xD,
    MT_GLDITEM = 0xE,
    MT_FLAG = 0xF,
    MT_DEVIL = 0x10,
    MT_META = 0x11,
    MT_NODAMAGE = 0x12,
    MT_NODAMAGE2 = 0x13,
    MT_NONAMEGATE = 0x14,
    MT_BOX_HERB = 0x15,
    MT_BOX_MINE = 0x16,
    MT_GB_DICE = 0x17,
    MT_NODAMAGE3 = 0x18,
    MT_FRIEND = 0x19,
    MT_GB_SLOTMACHINE = 0x1A,
    MT_FRIENDDMGABSORB = 0x1B,
    MT_DEVILDOM = 0x1C,
    MT_NOTARGET3 = 0x1D,
    MT_META2 = 0x1E,
    MT_DWARF = 0x1F,
    MT_MACHINE = 0x20,
    MAX_MOBTYPE = 0x21,
};

struct MobInfo
{
    unsigned __int16 ID;
    char InxName[32];
    char Name[32];
    __declspec(align(1)) unsigned int Level;
    __declspec(align(1)) unsigned int MaxHP;
    __declspec(align(1)) unsigned int WalkSpeed;
    __declspec(align(1)) unsigned int RunSpeed;
    char IsNPC;
    __declspec(align(1)) unsigned int Size;
    __declspec(align(1)) WeaponTypeEnum WeaponType;
    __declspec(align(1)) ArmorTypeEnum ArmorType;
    __declspec(align(1)) MobGradeType GradeType;
    __declspec(align(1)) MobType Type;
    char IsPlayerSide;
    unsigned int AbsoluteSize;
};

enum EnemyDetect
{
    ED_BOUT = 0x0,
    ED_AGGRESSIVE = 0x1,
    ED_NOBRAIN = 0x2,
    ED_AGGRESSIVE2 = 0x3,
    ED_AGGREESIVEALL = 0x4,
    ED_ENEMYALLDETECT = 0x5,
    MAX_ENEMYDETECT = 0x6,
};

enum MobKillType
{
    MKT_DEFAULT = 0x0,
    MKT_ONLYSCRIPT = 0x1,
    MKT_MOB = 0x2,
    MAX_MOBKILLTYPE = 0x3,
};

enum MobRace
{
    MR_NONE = 0x0,
    MR_PHINO = 0x1,
    MR_MARA = 0x2,
    MR_MARLONE = 0x3,
    MR_SKEL = 0x4,
    MR_CEM = 0x5,
    MR_GOBLIN = 0x6,
    MR_KARA = 0x7,
    MR_KEEPER = 0x8,
    MR_PI = 0x9,
    MR_LIZARD = 0xA,
    MR_TRUMPY = 0xB,
    MR_ORC = 0xC,
    MR_SLIME = 0xD,
    MR_BOAR = 0xE,
    MR_STAFF = 0xF,
    MR_ARCHON = 0x10,
    MR_STONIE = 0x11,
    MR_INCUBUS = 0x12,
    MR_TREE = 0x13,
    MR_IMP = 0x14,
    MR_VIVI = 0x15,
    MR_KEBING = 0x16,
    MR_GUARDIAN = 0x17,
    MR_MINER = 0x18,
    MR_BELLOW = 0x19,
    MR_CAIMAN = 0x1A,
    MR_RHINOCE = 0x1B,
    MR_MUD = 0x1C,
    MR_SLUG = 0x1D,
    MR_SHADOW = 0x1E,
    MR_CHAR = 0x1F,
    MR_STATUE = 0x20,
    MR_HELGA = 0x21,
    MR_SPIRIT = 0x22,
    MR_MAGRITE = 0x23,
    MR_WOLF = 0x24,
    MR_BEAR = 0x25,
    MR_SPIDER = 0x26,
    MR_MAND = 0x27,
    MR_LICH = 0x28,
    MR_POON = 0x29,
    MR_DEPRAVITY = 0x2A,
    MR_WIND = 0x2B,
    MR_SELF = 0x2C,
    MR_ELF = 0x2D,
    MR_HONEYING = 0x2E,
    MR_BOOGY = 0x2F,
    MR_CRAB = 0x30,
    MR_GUARD_NORMAL = 0x31,
    MR_DEVILDOM = 0x32,
    MR_SLAYER = 0x33,
    MR_DARKARMY = 0x34,
    MR_BKNIGHTS = 0x35,
    MAX_MOBRACE = 0x36,
};

struct __declspec(align(1)) MobInfoServer
{
    unsigned int ID;
    char InxName[32];
    char Visible;
    unsigned __int16 AC;
    unsigned __int16 TB;
    unsigned __int16 MR;
    unsigned __int16 MB;
    EnemyDetect EnemyDetectType;
    MobKillType MobKillInx;
    unsigned int MonEXP;
    unsigned __int16 EXPRange;
    unsigned __int16 DetectCha;
    char ResetInterval;
    unsigned __int16 CutInterval;
    unsigned int CutNonAT;
    unsigned int FollowCha;
    unsigned __int16 PceHPRcvDly;
    unsigned __int16 PceHPRcv;
    unsigned __int16 AtkHPRcvDly;
    unsigned __int16 AtkHPRcv;
    unsigned __int16 Str;
    unsigned __int16 Dex;
    unsigned __int16 Con;
    unsigned __int16 Int;
    unsigned __int16 Men;
    MobRace MobRaceType;
    char Rank;
    unsigned int FamilyArea;
    unsigned int FamilyRescArea;
    char FamilyRescCount;
    unsigned __int16 BloodingResi;
    unsigned __int16 StunResi;
    unsigned __int16 MoveSpeedResi;
    unsigned __int16 FearResi;
    char ResIndex[32];
    unsigned __int16 KQKillPoint;
    char Return2Regen;
    char IsRoaming;
    char RoamingNumber;
    unsigned __int16 RoamingDistance;
    unsigned __int16 RoamingRestTime;
    unsigned __int16 MaxSP;
    char BroadAtDead;
    unsigned __int16 TurnSpeed;
    unsigned __int16 WalkChase;
    char AllCanLoot;
    unsigned __int16 DmgByHealMin;
    unsigned __int16 DmgByHealMax;
    unsigned __int16 RegenInterval;
};

enum NORMALHITTYPE
{
    HT_PY = 0x0,
    HT_MA = 0x1,
    HT_NONE = 0x2,
    MAX_NORMALHITTYPE = 0x3,
};

enum ATKTYPE
{
    SKLTP_DAMAGE = 0x0,
    SKLTP_HEAL = 0x1,
    SKLTP_ABSTATE = 0x2,
    SKLTP_SPECIAL = 0x3,
    SKLTP_DISPEL = 0x4,
    MAX_ATKTYPE = 0x5,
};

enum MOBATTACKTARGET
{
    MAT_ENEMY = 0x0,
    MAT_ME = 0x1,
    MAT_MYRACE = 0x2,
    MAT_NONE = 0x3,
    MAT_NPC = 0x4,
    MAX_MOBATTACKTARGET = 0x5,
};

struct MobWeapon
{
    unsigned int ID;
    char InxName[33];
    char Skill[32];
    __declspec(align(1)) unsigned __int16 AtkSpd;
    __declspec(align(1)) unsigned __int16 BlastRate;
    __declspec(align(1)) unsigned __int16 AtkDly;
    __declspec(align(1)) unsigned __int16 SwingTime;
    __declspec(align(1)) unsigned __int16 HitTime;
    __declspec(align(1)) ATKTYPE AtkType;
    __declspec(align(1)) unsigned int MinWC;
    __declspec(align(1)) unsigned int MaxWC;
    __declspec(align(1)) unsigned __int16 TH;
    __declspec(align(1)) unsigned int MinMA;
    __declspec(align(1)) unsigned int MaxMA;
    __declspec(align(1)) unsigned __int16 MH;
    __declspec(align(1)) unsigned __int16 Range;
    __declspec(align(1)) MOBATTACKTARGET MopAttackTarget;
    __declspec(align(1)) NORMALHITTYPE HitType;
    char StaName[33];
    unsigned __int16 StaStrength;
    unsigned __int16 StaRate;
    unsigned __int16 AggroInitialize;
};

struct MobSpecies
{
    unsigned __int16 ID;
    char MobName[4][33];
};

struct __declspec(align(1)) QuestSpecies
{
    unsigned __int16 ID;
    char MobGroupName[5][33];
};

enum MobKillAnnounceType
{
    MKL_Helga = 0x0,
    MKL_Karen = 0x1,
    MKL_B_CrackerHumar = 0x2,
    MKL_BH_Helga = 0x3,
    MKL_BH_Humar = 0x4,
    MKL_Chimera = 0x5,
    MKL_B_Albireo = 0x6,
    MKL_BH_Albireo = 0x7,
    MAX_MOBKILLANNOUNCETYPE = 0x8,
};

struct MobKillLog
{
    unsigned int MobID;
};

struct MobKillAnnounce
{
    unsigned int MobID;
    MobKillAnnounceType TextIndex;
};

struct $361D2503CE59FA0B81E60E6B0FF72957
{
    __int8 IsBufferToBoss : 1;
    __int8 MobAutoAction_Damaged : 1;
};

struct __declspec(align(1)) MobRegenAni
{
    char MobIDX[32];
    unsigned __int16 RegenTime;
    char GroupAbStateIDX[32];
    char IsAggro;
};

struct GroupAbState
{
    char GroupAbStateIDX[32];
    char AbstateIDX[32];
    char Strength;
};

struct MobDataBox
{
    struct MobDataBoxIndex
    {
        struct _MobWeaponIndex
        {
            MobWeapon* weapon;
            unsigned __int16 skill;
            ABSTATEINDEX abstate;
        };

        MobInfo* data;
        MobInfoServer* serv;
        MobDataBox::MobDataBoxIndex::_MobWeaponIndex* weapon;
        int weaponnumber;
        MobSpecies* species;
        unsigned __int16 registindex;
        QuestSpecies* questspecies;
        MobKillAnnounce* p_mobkillannounce;
        MobKillLog* p_mobkilllog;
        unsigned int p_MobLifeTime;
        $361D2503CE59FA0B81E60E6B0FF72957 MobIndexFlag;
        MobRegenAni* pRegenAni;
        unsigned int nRegenAbstateGroup;
    };

    struct
    {
        char _size[0x65C];
    } mdb_BinData;
    MobDataBox::MobDataBoxIndex* mdb_index;
    unsigned int mdb_mobspacies;
    unsigned int mdb_maxmobhandle;
    BTree mdb_btree;
    std::multimap<unsigned long, GroupAbState*> mdb_GroupAbstate;
};

struct MobRegenStruct
{
    struct MobBreedSecond
    {
        unsigned int standard;
        unsigned int minsec;
        unsigned int maxsec;
        int timedist[9];
    };

    struct RegenRegion
    {
        unsigned int rgs_CenterX;
        unsigned int rgs_CenterY;
        unsigned int rgs_Width;
        unsigned int rgs_Height;
        unsigned int rgs_Rotate;
    };

    struct __declspec(align(1)) RegenGroupStruct
    {
        ORToken rgs_groupname;
        char rgs_family;
        MobRegenStruct::RegenRegion rgs_regreg;
    };

    struct __declspec(align(1)) RegenMobStruct
    {
      ORToken rms_groupname;
      char rms_mobname[33];
      char rms_Number;
      char rms_KillNumber;
      MobRegenStruct::MobBreedSecond rms_regen;
    };

};

struct MobRoaming
{
    struct __declspec(align(2)) PathElement
    {
      unsigned __int16 ID;
      unsigned int x;
      unsigned int y;
      char EventIndex[32];
    };

    struct MobRoamingPath : std::vector<MobRoaming::PathElement>
    {
        ORToken mrp_GroupName;
    };

};

namespace MobRegenClass
{
    struct MobBreederGroup;
	
    struct MobBreeder
    {
        MobRegenClass::MobBreederGroup* mb_Group;
        char mb_IsRegenEnable;
        unsigned __int16 mb_MobID;
        int mb_Level;
        MobRegenStruct::MobBreedSecond mb_RegenTime;
        unsigned __int16 mb_MobHandle;
        struct
        {
            unsigned int leftregen;
            char waitregen;
            unsigned int currentregensec;
            unsigned int regentime_tick;
            unsigned int deadtime_tick;
        } mb_NextRegen;
        int mb_RegenCount;
        struct
        {
            MobRegenClass::MobBreeder* prev;
            MobRegenClass::MobBreeder* next;
        } mb_Family;
        void* mb_BanditTemplete;
    };
	
    struct MobBreederGroup : List<MobRegenClass::MobBreeder>
    {
        MobRegenClass::MobBreeder mbg_array[64];
        ORToken mbg_GroupName;
        char mbg_isFamily;
        __declspec(align(1)) MobRegenStruct::MobBreedSecond mbg_regentime;
        __declspec(align(1)) Name3 mbg_RegenMap;
        ORToken mbg_AIType;
        struct
        {
            MobRegenStruct::RegenRegion region;
            struct
            {
                int width;
                int height;
                int cosD1024;
                int sinD1024;
            } rectangle;
            struct
            {
                int radious;
                int radioussqr;
            } circular;
        } mbg_RegenRegion;
        int mbg_RegenDirect;
        MobRegenClass::MobBreeder* mbg_Leader;
        MobRoaming::MobRoamingPath* mbg_RoamingPath;
    };
}

struct FamilyMobList
{
    ShineObjectClass::ShineMob* fml_Prev;
    ShineObjectClass::ShineMob* fml_Next;
};

struct __declspec(align(2)) PROTO_KQ_MAP_INFO
{
    char MapIndex;
    Name3 MapBase;
    Name3 MapName;
    char MapClear;
};

struct __declspec(align(1)) PROTO_KQ_INFO_CLIENT
{
    unsigned int Handle;
    char Status;
    unsigned __int16 NumOfJoiner;
    unsigned __int16 ID;
    char Title[64];
    unsigned __int16 LimitTime;
    int StartTime;
    tm tm_StartTime;
    unsigned __int16 StartWaitTime;
    char MinLevel;
    char MaxLevel;
    unsigned __int16 MinPlayers;
    unsigned __int16 MaxPlayers;
    char PlayerRepeatMode;
    unsigned __int16 PlayerRepeatCount;
    char PlayerRevivalMode;
    char PlayerRevivalCount;
    unsigned __int16 DemandQuest;
    unsigned __int16 DemandItem;
    __int64 DemandClass;
    char DemandGender;
};

struct __declspec(align(1)) PROTO_KQ_INFO : PROTO_KQ_INFO_CLIENT
{
    char NextStartMode;
    unsigned __int16 NextStartDelayMin;
    char RepeatMode;
    unsigned __int16 RepeatCount;
    unsigned __int16 RewardIndex;
    unsigned __int16 DemandMobKill;
    int ScheduleTime;
    tm tm_ScheduleTime;
    char RunCounter;
    PROTO_KQ_MAP_INFO MapLink[4];
    char ScriptLanguage[32];
    char ScriptInitValue[32];
    char IsTeamPVP;
    SHINE_XY_TYPE TeamRegenXY[2];
};

struct PineScriptToken
{
    char pst_Buffer[256];
};

namespace KingdomQuest
{
    struct __declspec(align(4)) KQPlayerInform
    {
        unsigned int kqpi_PlyRegnum;
        int kqpi_KnockDown;
        BattleStat kqpi_BattleStat;
        char kqpi_IsKQJoiner;
        char kqpi_nTeamType;
    };

    struct KQPlayerInfoList : CommonList<KingdomQuest::KQPlayerInform>
    {
    };

    struct KQElement
    {
        struct KQElementMap
        {
            PROTO_KQ_MAP_INFO mapinfo;
            FieldMap* fld;
            MapInfo* mapinf;
        };

        unsigned int kqe_Stop;
        PROTO_KQ_INFO kqe_kqinfo;
        KingdomQuest::KQElement::KQElementMap kqe_mapinfo[4];
        PineScriptToken kqe_Script;
        PineScriptToken kqe_InitValue;
        KingdomQuest::KQPlayerInfoList kqe_PlayerList;
    };

}

struct PROTO_CHARGED_ITEM_INFO
{
    unsigned int ItemOrderNo;
    unsigned int ItemCode;
    unsigned int ItemAmount;
    ShineDateTime ItemRegisterDate;
};

struct QUEST_DATA
{
    struct QUEST_START_CONDITION
    {
        char bIsWaitListView;
        char bIsWaitListProgress;
        char bLevel;
        char LevelMin;
        char LevelMax;
        char bNPC;
        unsigned __int16 NPCID;
        char bItem;
        unsigned __int16 ItemID;
        unsigned __int16 ItemLot;
        char bLocation;
        unsigned __int16 Location;
        unsigned int LocationX;
        unsigned int LocationY;
        unsigned int LocationRange;
        char bQuest;
        unsigned __int16 QuestID;
        char bRace;
        char Race;
        char bClass;
        char Class;
        char bGender;
        char Gender;
        char bDate;
        char DateMode;
        __int64 DateStart;
        __int64 DateEnd;
    };

    struct QUEST_END_CONDITION
    {
        struct ItemList
        {
            char bItem;
            unsigned __int16 ItemID;
            unsigned __int16 ItemLot;
        };
    	
        struct __declspec(align(2)) NPCMobList
        {
            char bNPCMob;
            unsigned __int16 NPCMobID;
            char NPCMobAction;
            char NPCMobCount;
            char TargetGroup;
        };

        char bIsWaitListProgress;
        char bLevel;
        char Level;
        QUEST_DATA::QUEST_END_CONDITION::NPCMobList NPCMobList[5];
        QUEST_DATA::QUEST_END_CONDITION::ItemList ItemList[5];
        char bLocation;
        unsigned __int16 Location;
        unsigned int LocationX;
        unsigned int LocationY;
        unsigned int LocationRange;
        char bScenario;
        unsigned __int16 ScenarioID;
        char bRace;
        char Race;
        char bClass;
        char Class;
        char bTimeLimit;
        unsigned __int16 TimeLimit;
    };

    struct __declspec(align(4)) QUEST_ACTION
    {
        char IfType;
        unsigned int IfTarget;
        char ThenType;
        unsigned int ThenTarget;
        unsigned int ThenPersent;
        unsigned int ThenCountMin;
        unsigned int ThenCountMax;
        char TargetGroup;
    };

    struct QUEST_REWARD
    {
        union VALUE
        {
            struct Item
            {
                unsigned __int16 ItemID;
                unsigned __int16 ItemLot;
            };

            struct __declspec(align(2)) Abstate
            {
                unsigned int AbstateKeepTime;
                unsigned __int16 AbstateID;
                char AbstateStrength;
            };
        	
            struct CharacterTitle
            {
                char Type;
                char ElementNo;
            };

            unsigned int Exp;
            unsigned int Money;
            QUEST_DATA::QUEST_REWARD::VALUE::Item Item;
            QUEST_DATA::QUEST_REWARD::VALUE::Abstate Abstate;
            unsigned int Fame;
            unsigned int PetID;
            char MiniHouseID;
            QUEST_DATA::QUEST_REWARD::VALUE::CharacterTitle CharacterTitle;
            unsigned int KillPoint;
        };

        char Use;
        char Type;
        QUEST_DATA::QUEST_REWARD::VALUE Value;
    };

    unsigned int nQuestDataSize;
    unsigned __int16 ID;
    unsigned int NameID;
    unsigned int BrifingID;
    char Region;
    char Type;
    char Repeatable;
    char nDailyQuestType;
    QUEST_DATA::QUEST_START_CONDITION Start;
    QUEST_DATA::QUEST_END_CONDITION End;
    char NumOfAction;
    QUEST_DATA::QUEST_ACTION Action[10];
    QUEST_DATA::QUEST_REWARD Reward[12];
    unsigned __int16 SizeOfScriptStart;
    unsigned __int16 SizeOfScriptEnd;
    unsigned __int16 SizeOfScriptDoing;
    char* pScriptStart;
    char* pScriptDoing;
    char* pScriptEnd;
    char DialogData[];
};

enum PLAYER_QUEST_STATUS
{
    PQS_NONE = 0x0,
    PQS_ABORT = 0x1,
    PQS_DONE = 0x2,
    PQS_SOON = 0x3,
    PQS_REPEAT = 0x4,
    PQS_ABLE = 0x5,
    PQS_ING = 0x6,
    PQS_FAILED = 0x7,
    PQS_REWARD = 0x8,
    PQS_LOWABLE = 0x9,
    PQS_READ_ABLE = 0x14,
    PQS_MAX_PLAYER_QUEST_STATUS = 0x15,
};

struct PROTO_NC_QUEST_RESET_TIME_CMD
{
    int tResetYearQuest;
    int tResetMonthQuest;
    int tResetWeekQuest;
    int tResetDayQuest;
};

struct CQuest
{
    struct NPC_QUEST_STATUS
    {
        unsigned __int16 hID;
        QUEST_DATA* lpQuestData;
        PLAYER_QUEST_STATUS eResultState;
        int nLevel;
    };

    void* vfptr;
    void* m_pQuestData;
    int m_NumOfQuest;
    int m_NumOfQuestBF;
    PLAYER_QUEST_INFO* m_pQuestArray;
    int m_ProcessedTime;
    int m_MaxOfQuestListWithNPC;
    int m_NumOfQuestListWithNPC;
    CQuest::NPC_QUEST_STATUS* m_pQuestListWithNPC;
    unsigned int m_QuestStatusPriority[21];
    unsigned int m_QuestTypePriority[11];
    PROTO_NC_QUEST_RESET_TIME_CMD m_QuestRestTime;
};

struct CQuestParserScript
{
    char _size[0x844];
};

struct __declspec(align(1)) STRUCT_QSC
{
    char _size[0x65];
};

struct CQuestZone : CQuest
{
    enum QUEST_PARSING_SCRIPT_TYPE
    {
        QPST_START = 0x0,
        QPST_DOING = 0x1,
        QPST_END = 0x2,
    };

    ShineObjectClass::ShinePlayer* m_pPlayer;
    CQuestParserScript m_ScriptParser;
    STRUCT_QSC* m_pQSC;
    int m_bWaitResult;
    unsigned __int16 m_QuestClickNPC;
    unsigned __int16 m_ParsingQuestID;
    CQuestZone::QUEST_PARSING_SCRIPT_TYPE m_ParsingQuestScriptType;
    unsigned int m_nSelectedItem;
    unsigned __int16 m_nClickNPCNo;
    int m_ScriptIdent;
};


struct ShineQuestDiary
{
    CQuestZone sqd_QuestDiary;
};

struct __declspec(align(1)) GUILD_ZONE
{
    unsigned int nNo;
    Name4 sName;
    unsigned __int64 nMoney;
    char nType;
    char nGrade;
    unsigned int nFame;
    unsigned __int16 nStoneLevel;
    unsigned __int64 nExp;
    char nWarStatus;
    unsigned int nWarEnemy;
};

enum REWARD_ITEM_OPTION
{
    RIO_MONEY = 0x1,
    RIO_ITEM = 0x2,
    RIO_LOT = 0x3,
    RIO_UPGRADE = 0x4,
};

struct __declspec(align(4)) GUILD_ACADEMY_REWARD_ITEM_OPTION
{
    REWARD_ITEM_OPTION nOptionType;
    unsigned __int64 nOptionData;
};

struct GUILD_ACADEMY_REWARD_ITEM
{
    char nLevel;
    __declspec(align(1)) unsigned __int16 nItemID;
    char NumOfItemOption;
    GUILD_ACADEMY_REWARD_ITEM_OPTION ItemOption[1];
};

struct __declspec(align(1)) EACH_MODIFY_ITEM
{
    char nStatus;
    unsigned __int16 nItemID;
    ITEM_INVEN nLocation;
    unsigned int nLot;
};

struct DeadCheck
{
    enum DC_DeadCause
    {
        DC_LIVE = 0x0,
        DC_DOT = 0x1,
        DC_ATTACK = 0x2,
        DC_ATTACK2 = 0x3,
        DC_SELFKILL = 0x4,
        DC_SKILL = 0x5,
    };

    DeadCheck::DC_DeadCause dc_Cause;
};

struct ItemLotInspector
{
    struct __declspec(align(4)) InspectNote
    {
        int ili_Action;
        unsigned __int16 ili_ItemID;
        struct
        {
            char Activ;
            __declspec(align(1)) ITEM_INVEN Locate;
            SHINE_ITEM_STRUCT Item;
        } ili_From[2];
        struct
        {
            char Activ;
            __declspec(align(1)) ITEM_INVEN Locate;
            int Lot;
        } ili_To[2];
        int ili_MoveLot;
        int ili_TotalLot;
        char ili_StorageCount;
    };

    int ili_Action;
    ItemLotInspector::InspectNote ili_Array[64];
    BitANDInt ili_ArrayPointer;
};

struct IObserver
{
    enum Event
    {
        EV_IDLE = 0x0,
        EV_DIE = 0x1,
        EV_SKILL = 0x2,
        EV_ABSTATE = 0x3,
        EV_EMOTION = 0x4,
        EV_DAMAGE = 0x5,
        EV_TICK_PARTY = 0x6,
        EV_LOCATION = 0x7,
        EV_ATTACKMOB = 0x8,
    };

    void* vfptr;
};

struct Observer : IObserver
{
    ShineObjectClass::ShineObject* master_;
    IObserver* next_;
    unsigned int birth_;
    Metronome tick_;
};

enum LOOTING_TYPE
{
    LOOTING_TYPE_FREE = 0x0,
    LOOTING_TYPE_ORDER = 0x1,
    LOOTING_TYPE_LOOTER = 0x2,
    LOOTING_TYPE_DICE = 0x3,
    MAX_LOOTING_TYPE = 0x4,
};

struct CLooting
{
    LOOTING_TYPE m_ItemLootingType[4];
    unsigned int m_Looter;
};

struct Raid
{
    virtual void* Delete(uint);
	
    unsigned __int16 m_Raidnum;
    char m_NumOfMember;
    unsigned __int16 m_PartyNos[4];
    unsigned int m_Leader;
    unsigned int m_SubLeader[4];
    CLooting m_Looting;
};

struct __declspec(align(1)) PROTO_PARTY_MEMBER
{
    unsigned int chrregnum;
    unsigned __int16 zonecharhandle;
    unsigned __int16 wmcharhandle;
    Name5 charname;
    char level;
    char flag;
    char charclass;
};

struct PROTO_PARTY_MEMBER_AND_ZONEMERCHINE
{
    PROTO_PARTY_MEMBER Member;
    char ZoneMerchineNo;
};

struct CParty
{
    struct __declspec(align(4)) PARTY_SLOT
    {
        struct PARTY_MEMBER_SLOT
        {
            PROTO_PARTY_MEMBER_AND_ZONEMERCHINE MemberInform;
            ShineObjectClass::ShineObject* memberobj;
        };

        char NumOfMember;
        CParty::PARTY_SLOT::PARTY_MEMBER_SLOT Members[5];
        CLooting m_Looting;
        bool IsBelongItemDiceGameIng;
        bool isRaidTypeParty;
    };

    CParty::PARTY_SLOT* m_Array;
    int m_NumOfParty;
    int m_EmptyPartySearchPoint;
};

struct ABSTATE_INFORMATION
{
    ABSTATEINDEX abstateID;
    unsigned int restKeeptime;
    unsigned int strength;
};

enum GAMBLE_TYPE
{
    GBT_BASE = 0x0,
    GBT_DICETAISAI = 0x1,
    GBT_SLOTMACHINE = 0x2,
    GBT_MAX = 0x3,
};

enum ReactionTypeEnum
{
    RAT_NONE = 0x0,
    RAT_BUY = 0x1,
    MAX_REACTIONTYPEENUM = 0x2,
};

struct SkillDamageParameterAtScript
{
    int MinWC;
    int MaxWC;
    int TH;
    int MinMA;
    int MaxMA;
    int MH;
};

enum PS_ConditionEnum
{
    PS_CBOWATKRATEKNOCKBACK = 0x0,
    PS_SKILLSPUSEDOWN = 0x1,
    PS_AREAENEMYSPDOWN = 0x2,
    PS_MEDMGMISSCRIUPRATE = 0x3,
    MAX_PS_CONDITIONENUM = 0x4,
};

enum CHARACTER_TITLE_TYPE
{
    ID_NONE = 0x0,
    ID_EXP = 0x1,
    ID_CLASS = 0x2,
    ID_LOGON_TIME_AT_ONCE = 0x3,
    ID_PLAY_TIME = 0x4,
    ID_MONEY = 0x5,
    ID_MONEY_GIVE = 0x6,
    ID_MONEY_BEG = 0x7,
    ID_KILLED_BY_MOB = 0x8,
    ID_NOKILLED_BY_MOB = 0x9,
    ID_WEAPON_TITLE = 0xA,
    ID_TOTAL_KILL_MOB = 0xB,
    ID_KILL_GUILD = 0xC,
    ID_KILLED_BY_GUILD = 0xD,
    ID_TOTAL_GUILD_ATC = 0xE,
    ID_MY_GUILD_GRADE = 0xF,
    ID_FULL_PARTY_JOIN = 0x10,
    ID_ARENA_MY_WIN = 0x11,
    ID_ARENA_MY_LOST = 0x12,
    ID_ARENA_MY_ATT = 0x13,
    ID_KQ_ATT = 0x14,
    ID_KQ_SUCCESS = 0x15,
    ID_KQ_FAIL = 0x16,
    ID_SELL_NPC_COUNT = 0x17,
    ID_BUY_NPC_COUNT = 0x18,
    ID_NOJUM_SELL = 0x19,
    ID_AUCTION_SELL = 0x1A,
    ID_ITEM_UP_SUCCESS_COUNT = 0x1B,
    ID_ITEM_UP_FAIL_COUNT = 0x1C,
    ID_ITEM_UP_SUC_CON = 0x1D,
    ID_ITEM_UP_FAIL_CON = 0x1E,
    ID_ITEM_UP_MY_BEST = 0x1F,
    ID_ITEM_UP_DESTORY_COUNT = 0x20,
    ID_MASTER_PUPIL_COUNT = 0x21,
    ID_FRIEND_COUNT = 0x22,
    ID_MINI_FUNI_COUNT = 0x23,
    ID_MINI_VISITOR_COUNT = 0x24,
    ID_PET_BUY = 0x25,
    ID_PET_KILLED = 0x26,
    ID_RARE_ITEM_GET = 0x27,
    ID_QUEST_SUC_COUNT = 0x28,
    ID_NOCHATTING_COUNT = 0x29,
    ID_BROADCAST_COUNT = 0x2A,
    ID_CHAR_TITLE = 0x2B,
    ID_FAME_COUNT = 0x2C,
    ID_JOB_FIGHTER = 0x2D,
    ID_JOB_CLERIC = 0x2E,
    ID_JOB_ARCHER = 0x2F,
    ID_JOB_MAGE = 0x30,
    ID_PRODUCT_HP = 0x31,
    ID_PRODUCT_SP = 0x32,
    ID_PRODUCT_GS = 0x33,
    ID_PRODUCT_PS = 0x34,
    ID_PRODUCT_US = 0x35,
    ID_COLLECT_MINERAL = 0x36,
    ID_COLLECT_TREE = 0x37,
    ID_COLLECT_HERB = 0x38,
    ID_CLBETA_TITLE = 0x39,
    ID_GAME_DICE_WIN = 0x3A,
    ID_GAME_DICE_SET = 0x3B,
    ID_JOB_JOKER = 0x3C,
    ID_CC_HUMAR02 = 0x3D,
    ID_CC_C_JEWELGOLEM01 = 0x3E,
    ID_CC_HELGA01 = 0x3F,
    ID_CC_KAREN02 = 0x40,
    ID_CC_KALBANOBEB02 = 0x41,
    ID_CC_MARA02 = 0x42,
    ID_CC_SLIME02 = 0x43,
    ID_CC_LEVIATHAN01 = 0x44,
    ID_CC_DARKFOG = 0x45,
    ID_CC_ELFKNIGHTSOUL = 0x46,
    ID_CC_FIREPAMELIA = 0x47,
    ID_CC_GUARDIANMASTER01 = 0x48,
    ID_CC_HARPY01 = 0x49,
    ID_CC_WOLF = 0x4A,
    ID_CC_JEWELKEEPER = 0x4B,
    ID_CC_KINGCRAB02 = 0x4C,
    ID_CC_MAGRITE = 0x4D,
    ID_CC_MARLONE03 = 0x4E,
    ID_CC_ORC = 0x4F,
    ID_CC_PHINOFLIE = 0x50,
    ID_CC_SILBERK = 0x51,
    ID_CC_STONIE = 0x52,
    ID_CC_TOMBRAIDER03 = 0x53,
    ID_CC_BAT = 0x54,
    ID_CC_BOOGY02 = 0x55,
    ID_CC_SHELLA = 0x56,
    ID_CC_VIVI = 0x57,
    ID_CC_GREENKY = 0x58,
    ID_CC_ICELICH = 0x59,
    ID_CC_LAB_1902 = 0x5A,
    ID_CC_LAB_BATTLE0102 = 0x5B,
    ID_CC_LAB_WATCHMAN0102 = 0x5C,
    ID_CC_MARASAILOR01 = 0x5D,
    ID_CC_RATMAN02 = 0x5E,
    ID_CC_SHYLPH = 0x5F,
    ID_CC_SKELKNIGHT02 = 0x60,
    ID_CC_VAMPIREBAT = 0x61,
    ID_CC_CLOVERTRUMPY02 = 0x62,
    ID_CC_CLOVERTRUMPY03 = 0x63,
    ID_CC_EARTHCALERBEN = 0x64,
    ID_CC_FLYINGSTAFF = 0x65,
    ID_CC_HARKAN01 = 0x66,
    ID_CC_HONEYING03 = 0x67,
    ID_CC_KEBING01 = 0x68,
    ID_CC_LEIPOON = 0x69,
    ID_CC_LIVINGSTATUE02 = 0x6A,
    ID_CC_LIZARDMAN03 = 0x6B,
    ID_CC_MINEMOLE01 = 0x6C,
    ID_CC_NOX = 0x6D,
    ID_CC_SPADETRUMPY02 = 0x6E,
    ID_CC_SPARKDOG02 = 0x6F,
    ID_CC_ZOMBIE = 0x70,
    ID_JOB_SENTINEL = 0x71,
    ID_PZL_SLIME = 0x72,
    ID_PZL_HONEYING = 0x73,
    ID_PZL_SLIME_HONEYING = 0x74,
    ID_OLYMPIC_MEDAL_GOLD = 0x75,
    ID_OLYMPIC_MEDAL_SILVER = 0x76,
    ID_OLYMPIC_MEDAL_BRONZE = 0x77,
    ID_SOCCER_TOP_SCORER = 0x78,
    ID_SOCCER_PLAYER = 0x79,
    ID_H_WIN_MASTER = 0x7A,
    ID_H_WIN_GUIDE = 0x7B,
    ID_H_WIN_PASSER = 0x7C,
    ID_H_WIN_HELGA = 0x7D,
    ID_H_WIN_HUMAR = 0x7E,
    ID_H_WIN_JACKO = 0x7F,
    MAX_CHARACTER_TITLE_TYPE = 0x80,
};

struct __declspec(align(1)) MOVER_LINKDATA
{
    unsigned int nCharNo;
    int nItemSlot;
    unsigned int nMoverID;
    unsigned int nMoverHP;
    unsigned int nMasterCharNo;
    char nGrade;
    unsigned int nPassenger[10];
};

enum ChrClassType
{
    CCT_FIGHTER = 0x0,
    CCT_ARCHER = 0x1,
    CCT_CLERIC = 0x2,
    CCT_MAGE = 0x3,
    CCT_JOKER = 0x4,
    CCT_SENTINEL = 0x5,
    CCT_COMMON = 0x6,
    MAX_CHRCLASSTYPE = 0x7,
};

enum MOVE_STATE
{
    MS_HALT = 0x0,
    MS_MOVE = 0x1,
    MS_MAX = 0x2,
};

enum LAYER_TYPE
{
    LT_BASE = 0x0,
    LT_TUTORIAL = 0x1,
    LT_MAX_LAYER = 0x2,
};

enum LAYER_NUMBER_TYPE
{
    LNT_BASE = 0x0,
    LNT_CHAR_NUMBER = 0x1,
    LNT_MAX = 0x2,
};

enum MOVER_SYSTEM_TYPE
{
    MVST_RIDE = 0x0,
    MVST_RIDE_ADEL = 0x1,
    MVST_MOVER = 0x2,
    MVST_MAX = 0x3,
};

enum TUTORIAL_STATE
{
    TS_PROGRESS = 0x0,
    TS_DONE = 0x1,
    TS_SKIP = 0x2,
    TS_EXCEPTION = 0x3,
    TS_MAX = 0x4,
};

struct __declspec(align(1)) PROTO_TUTORIAL_INFO
{
    TUTORIAL_STATE nTutorialState;
    char nTutorialStep;
};

enum CAHT_CHAT_COLOR_ITEM_TYPE
{
    CCCIT_CHAT_FONT_COLOR_CHANGE = 0x1,
    CCCIT_CHAT_BALLOON_COLOR_CHANGE = 0x2,
    CCCIT_CHAT_COLOR_CHANGE = 0x3,
};

enum EffectEnumerate
{
    EE_SILVERWINGCOOLTIME = 0x0,
    EE_NOLOSTINKILLED = 0x1,
    EE_MOREINVENTORY = 0x2,
    EE_MORESTORAGE = 0x3,
    EE_MOREBOOTHSLOT = 0x4,
    EE_FASTMINING = 0x5,
    EE_MOREHPSTONE = 0x6,
    EE_MORESPSTONE = 0x7,
    EE_MOREHSPSTONE = 0x8,
    EE_COSTUM = 0x9,
    EE_AKPOWER = 0xA,
    EE_DPPOWER = 0xB,
    EE_ALLPOWER = 0xC,
    EE_HPINCREASE = 0xD,
    EE_SPINCREASE = 0xE,
    EE_ALLINCREASE = 0xF,
    EE_DROP_RATE = 0x10,
    EE_FEED = 0x11,
    EE_EXP_RATE = 0x12,
    EE_STATUS = 0x13,
    EE_ITEMAT_RATE = 0x14,
    EE_ITENDF_RATE = 0x15,
    EE_ITEMAL_RATE = 0x16,
    EE_PRODUCTSPEEDRATE = 0x17,
    EE_PRODUCTMASTERYRATE = 0x18,
    EE_PRODUCTALLRATE = 0x19,
    EE_JUSTREVIVE_HP = 0x1A,
    EE_ENDURE_KIT = 0x1B,
    EE_WEAPON_MAXENDURE = 0x1C,
    EE_ADDPRODSKILL = 0x1D,
    EE_JUSTRREVIVAL = 0x1E,
    EE_SETABSTATE = 0x1F,
    EE_GBCOIN = 0x20,
    EE_STORAGE_ANYWHERE = 0x21,
    EE_LPINCREASE = 0x22,
    EE_AUTOPATHFIND = 0x23,
    EE_CHATCOLOR = 0x24,
    EE_TERMEXTEND = 0x25,
    EE_EXPHOLD = 0x26,
    EE_CLASSCHANGE = 0x27,
    MAX_EFFECTENUMERATE = 0x28,
};

struct __declspec(align(1)) ChargedItemEffect
{
    unsigned __int16 Handle;
    char ItemID[32];
    unsigned __int16 KeepTime_Hour;
    EffectEnumerate EffectEnum;
    unsigned __int16 EffectValue;
    char StaStrength;
};

struct USEITEM_MINIMON_INFO
{
    char bNormalItem;
    char bChargedItem;
    unsigned __int16 NormalItemList[12];
    unsigned __int16 ChargedItemList[12];
};

struct __declspec(align(2)) PROTO_SELL_ITEM_INFO_SERVER
{
    char nDataSize;
    unsigned __int16 nHandle;
    SHINE_ITEM_REGISTNUMBER nSellItemKey;
    ItemTotalInformation ItemTotalInfo;
};

namespace INSTANCE_DUNGEON
{
    enum CATEGORY
    {
        CATEGORY_CLASSIC = 0xFFFFFFFF,
        CATEGORY_PARTY = 0x0,
        CATEGORY_GUILD = 0x1,
        CATEGORY_INDIVIDUAL = 0x2,
        CATEGORY_RAID = 0x3,
    };
}

struct DuringBattle
{
    unsigned int db_lasthit;
};

enum TotalMasteryType
{
    MT_STONE = 0x0,
    MT_PORTION = 0x1,
    MT_SCROLL = 0x2,
    MT_SUMMON = 0x3,
    MT_COMPOUND = 0x4,
    MT_RESOLVE = 0x5,
    MT_COOK = 0x6,
    MAX_TOTALMASTERYTYPE = 0x7,
};

struct __declspec(align(2)) ProduceInfo
{
    unsigned __int16 ProductID;
    char ProduceIndex[32];
    char Name[64];
    char Product[32];
    unsigned int Lot;
    char Raw0[32];
    unsigned int Quantity0;
    char Raw1[32];
    unsigned int Quantity1;
    char Raw2[32];
    unsigned int Quantity2;
    char Raw3[32];
    unsigned int Quantity3;
    char Raw4[32];
    unsigned int Quantity4;
    char Raw5[32];
    unsigned int Quantity5;
    char Raw6[32];
    unsigned int Quantity6;
    char Raw7[32];
    unsigned int Quantity7;
    TotalMasteryType MasteryType;
    unsigned int MasteryGain;
    TotalMasteryType NeededMasteryType;
    unsigned int NeededMasteryGain;
};

namespace GatherProduce
{
    struct RecipeBook
    {
        struct ProductIndex
        {
            ProduceInfo* index;
            unsigned __int16 product;
            int productlot;
            struct
            {
                unsigned __int16 item;
                int quantity;
            } raw[8];
        };

        char rb_BinData[0x1F8];
        GatherProduce::RecipeBook::ProductIndex* rb_Array;
        int rb_Number;
    };
}

namespace AttackRhythm
{
    struct AttackRhythmBase
    {
        void* vfptr;
    };

    struct __declspec(align(4)) CharArgument
    {
        AttackRhythm::AttackRhythmBase* ca_attrhythm;
        char ca_group;
        char ca_point;
    };
}

struct TargetAnalyser
{
    void* vfptr;
    ShineObjectClass::ShineMobileObject* ta_body;
};

struct CallBackEvent
{
    void* vfptr;
};

struct TargetAnalyser_Player : TargetAnalyser
{
};

struct CeaseFireSender
{
    char cfs_Flag;
};

struct SkillCastFinish
{
    unsigned __int16 scf_ErrorType;
};

struct TargetObject
{
    char to_Type;
    unsigned __int16 to_Handle;
    unsigned int to_RegNum;
    ShineObjectClass::ShineObject* to_Object;
    ShineObjectClass::ShinePlayer* to_MainBody;
    unsigned int to_LastHp;
    unsigned int to_LastSp;
};

namespace NormalAttackDamageDelay
{
    struct NormalAttackDamageElement
    {
        unsigned int nade_Tick;
        ShineObjectClass::ShineObject* nade_Target;
        char nade_AttackSequance;
        unsigned int nade_MissileFlyMilliSec;
    };

    struct NormalAttackDamageTick
    {
        std::deque<NormalAttackDamageDelay::NormalAttackDamageElement> nadt_DamageTime;
    };
}

struct CharaterSkillList
{
    struct CharSkill
    {
        unsigned __int16 cs_SkillId;
        unsigned int cs_EndOfCooltime;
        SKILL_EMPOWER cs_Empower;
        unsigned int cs_Mastery;
        int cs_bSave;
    };
	
    struct __declspec(align(2)) CharacterToggleSkill
    {
        unsigned __int16 cts_nSkillID;
        char cts_bSkillOn;
    };

    std::vector<CharaterSkillList::CharSkill> csl_Skill;
    int csl_SkillNumber;
    std::vector<CharaterSkillList::CharacterToggleSkill> csl_ToggleSkill;
};

struct BitSet
{
    char* bs_bitlist;
    unsigned int bs_maxbit;
    unsigned int bs_maxbyte;
};

struct __declspec(align(2)) PassiveSkillInfo
{
    unsigned __int16 ID;
    char InxName[32];
    char Name[32];
    unsigned int WeaponMastery;
    char DemandSk[32];
    unsigned int MstRtTmp;
    unsigned int MstRtSword1;
    unsigned int MstRtHammer1;
    unsigned int MstRtSword2;
    unsigned int MstRtAxe2;
    unsigned int MstRtMace1;
    unsigned int MstRtBow2;
    unsigned int MstRtCrossBow2;
    unsigned int MstRtWand2;
    unsigned int MstRtStaff2;
    unsigned int MstRtClaw;
    unsigned int MstRtDSword;
    unsigned int MstPlTmp;
    unsigned int MstPlSword1;
    unsigned int MstPlHammer1;
    unsigned int MstPlSword2;
    unsigned int MstPlAxe2;
    unsigned int MstPlMace1;
    unsigned int MstPlBow2;
    unsigned int MstPlCrossBow2;
    unsigned int MstPlWand2;
    unsigned int MstPlStaff2;
    unsigned int MstPlClaw;
    unsigned int MstPlDSword;
    unsigned int SPRecover;
    unsigned int TB;
    unsigned int MaxSP;
    unsigned int MaxLP;
    unsigned int Intel;
    unsigned int CastingTime;
    unsigned __int16 MACriRate;
    unsigned int WCRateUp;
    unsigned int MARateUp;
    unsigned __int16 HpDownDamegeUp;
    unsigned __int16 DownDamegeHp;
    unsigned __int16 HpDownAcUp;
    unsigned __int16 DownAcHp;
    unsigned __int16 MoveTBUpPlus;
    unsigned __int16 HealUPRate;
    unsigned __int16 KeepTimeBuffUPRate;
    unsigned __int16 CriDmgUpRate;
    ActiveSkillGroupIndex ActiveSkillGroupInx;
    unsigned __int16 DMG_MinusRate;
};

struct __declspec(align(1)) PSkillSetAbstate
{
    char PS_InxName[32];
    PS_ConditionEnum PS_Condition;
    unsigned __int16 PS_ConditioRate;
    char PS_AbStateInx[32];
    char Strength;
};

struct PassiveDataBox
{
    struct SpecialSkill
    {
        unsigned __int16 ss_PowerOfLove;
    };

    struct PSSetAbstateIndex
    {
        unsigned __int16 pssabs_nID;
        PSkillSetAbstate* pssabs_pPSkillSetAbstate;
        PassiveDataBox::PSSetAbstateIndex* pssabs_Prev;
        PassiveDataBox::PSSetAbstateIndex* pssabs_Next;
    };

    PassiveSkillInfo* pdb_default;
    char pdb_databox[0x144-0x4];
    PassiveSkillInfo** pdb_index;
    int pdb_passivenumber;
    int pdb_maxpassiveID;
    PassiveDataBox::SpecialSkill sdb_SpecSkill;
    char pdb_SetAbstateDataBox[0x1DC-0x154];
    int pdb_nMaxPSkillSetAbstateNum;
    PassiveDataBox::PSSetAbstateIndex* pdb_pPSkillSetAbstate;
};

struct CharacterPassiveList
{
    BitSet cpl_Passive;
    std::list<PassiveDataBox::PSSetAbstateIndex*> cpl_SetAbstateList;
};

struct CurrentMenu
{
    NPCRoleBase* cm_NPC;
    SHINE_XY_TYPE cm_MenuLoc;
};

struct ServerMenuFuncter
{
};

struct __declspec(align(2)) PROTO_NC_ITEM_DROP_REQ
{
    ITEM_INVEN slot;
    unsigned int lot;
    SHINE_XY_TYPE loc;
};

union __declspec(align(4)) ServerMenuArgument
{
    struct ServerMenuLink
    {
        NPCManager::LinkInformTemplete sml_lnkinf;
        bool sml_isTemplink;
        unsigned __int16 sml_LevelFrom;
        unsigned __int16 sml_LevelTo;
    };

	struct SilverWingSet
    {
        ITEM_INVEN inven;
    };

    struct ItemBreaker
    {
        ITEM_INVEN invenslot;
        unsigned __int16 lockindex;
    };
	
    struct ItemDropper
    {
        ITEM_INVEN inven;
        ItemInventoryCell* invcell;
        PROTO_NC_ITEM_DROP_REQ drop;
        unsigned __int16 lockindex;
    };
	
    struct SelfRevive
    {
        unsigned __int16 healrate;
    };
	
    struct DeleteInstanceDungeon
    {
        INSTANCE_DUNGEON::CATEGORY Category;
        unsigned int RegisterNumber;
    };
	
    struct ServerMenuLinkDungeon
    {
        unsigned int IDRegisterNumber;
        char argument[20];
        char sep;
        INSTANCE_DUNGEON::CATEGORY category;
    };

    struct ServerMenuLuaInterface
    {
        unsigned __int16 smli_NPCHandle;
        char smli_LuaFunction[20];
    };

    ServerMenuArgument::ServerMenuLink sma_link;
    ServerMenuArgument::SilverWingSet sma_silverwing;
    ServerMenuArgument::ItemBreaker sma_ItemBreak;
    ServerMenuArgument::ItemBreaker sma_ImmediateDivorce;
    ServerMenuArgument::ItemDropper sma_ItemDrop;
    ServerMenuArgument::SelfRevive sma_SelfRevive;
    ServerMenuArgument::DeleteInstanceDungeon sma_DeleteInstanceDungeon;
    ServerMenuArgument::ServerMenuLinkDungeon sma_linkDungeon;
    ServerMenuArgument::ServerMenuLuaInterface sma_LuaInterface;
};

struct ServerMenuActor : SHINE_XY_TYPE
{
    struct _Selected
    {
        ServerMenuArgument smargument;
        void(__thiscall* smfunction)(ServerMenuFuncter*, ShineObjectClass::ShinePlayer*, ServerMenuArgument*);
    };

    ServerMenuActor::_Selected sma_Selected[10];
    int sma_Subst;
    char sma_bRangeCheck;
    ShineObjectClass::ShinePlayer* sma_pPlayer;
    ServerMenuActor::_Selected sma_ResetFuction;
};

struct DuplicatedMenuControl
{
    unsigned __int16 dmc_Control;
};

struct ItemRewardStorage : ItemBag
{
    ItemInventoryCell irs_Array[24];
};

struct ItemAccountStorage : ItemBag
{
    ItemInventoryCell ias_Array[576];
};

struct TreasureChestLocationManager : BitSet
{
};

#pragma pack(push, 1)
struct DropItemStruct
{
    struct ItemGroup
    {
        ORToken ig_itemgroupidx;
        char ig_itemid[40];
        unsigned __int16 ig_quantitylow;
        unsigned __int16 ig_quantityhigh;
        unsigned __int16 ig_upgraderate[16];
        unsigned int ig_CheckSum;
    };

    struct DropTable
    {
        struct __declspec(align(1)) Index
        {
          char area[33];
          char mobindex[33];
          unsigned __int16 minlev;
          unsigned __int16 maxlev;
          char abstatecount;
        };
    	
        struct __declspec(align(1)) Group
        {
          ORToken dropitemgroup;
          unsigned int droprate;
          char upgrademin;
          char upgrademax;
          char droptype;
          unsigned __int16 dropnumber;
        };
    	
        struct ExclusiveGroup
        {
            ORToken exclusive[5];
        };

        DropItemStruct::DropTable::Index index;
        __declspec(align(1)) struct
        {
            unsigned int mincen;
            unsigned int maxcen;
            unsigned int rate;
        } cen;
        __declspec(align(1)) struct
    	{
            ORToken TradeBoxA;
            unsigned int RateA;
            ORToken TradeBoxB;
            unsigned int RateB;
            ORToken TradeBoxC;
            unsigned int RateC;
        } treasurebox;
        DropItemStruct::DropTable::Group droptable[45];
        DropItemStruct::DropTable::ExclusiveGroup exgroup;
        unsigned int dt_CheckSum;
    };
};

struct RateRecalc
{
    int rr_ByCharged;
    int rr_ByLevel;
    int rr_FieldBonus;
    int rr_ByAbstate;
};

#pragma pack(pop)

struct ItemAttrCls_ByteLot : ItemAttributeClass
{
};

/* 1978 */
struct ItemAttrCls_WordLot : ItemAttributeClass
{
};

/* 1979 */
struct ItemAttrCls_DwrdLot : ItemAttributeClass
{
};

/* 1980 */
struct ItemAttrCls_QuestLot : ItemAttrCls_WordLot
{
};

/* 1981 */
struct ItemAttrCls_NotLot : ItemAttributeClass
{
};

/* 1982 */
struct ItemAttrCls_Amulet : ItemAttrCls_NotLot
{
};

/* 1983 */
struct ItemAttrCls_Weapon : ItemAttrCls_NotLot
{
};

/* 1984 */
struct ItemAttrCls_Armor : ItemAttrCls_NotLot
{
};

/* 1985 */
struct ItemAttrCls_Shield : ItemAttrCls_NotLot
{
};

/* 1986 */
struct ItemAttrCls_Boot : ItemAttrCls_NotLot
{
};

/* 1987 */
struct ItemAttrCls_Furniture : ItemAttrCls_NotLot
{
};

/* 1988 */
struct ItemAttrCls_Decoration : ItemAttrCls_NotLot
{
};

/* 1989 */
struct ItemAttrCls_SkillScroll : ItemAttrCls_NotLot
{
};

/* 1990 */
struct ItemAttrCls_RecallScroll : ItemAttrCls_ByteLot
{
};

/* 1991 */
struct ItemAttrCls_BindItem : ItemAttrCls_NotLot
{
};

/* 1992 */
struct ItemAttrCls_UpSource : ItemAttrCls_ByteLot
{
};

/* 1993 */
struct ItemAttrCls_ItemChest : ItemAttrCls_NotLot
{
};

/* 1994 */
struct ItemAttrCls_WeaponTitlaLicence : ItemAttrCls_NotLot
{
};

/* 1995 */
struct ItemAttrCls_KingdomQuestItem : ItemAttrCls_NotLot
{
};

/* 1996 */
struct ItemAttrCls_MiniHouseSkin : ItemAttributeClass
{
};

/* 1997 */
struct ItemAttrCls_UpgradeRedGem : ItemAttrCls_ByteLot
{
};

/* 1998 */
struct ItemAttrCls_UpgradeBlueGem : ItemAttrCls_ByteLot
{
};

/* 1999 */
struct ItemAttrCls_UpgradeGoldGem : ItemAttrCls_ByteLot
{
};

/* 2000 */
struct ItemAttrCls_KQStep : ItemAttrCls_WordLot
{
};

/* 2001 */
struct ItemAttrCls_Feed : ItemAttrCls_ByteLot
{
};

/* 2002 */
struct ItemAttrCls_Riding : ItemAttrCls_NotLot
{
};

/* 2003 */
struct ItemAttrCls_Amount : ItemAttrCls_NotLot
{
};

/* 2004 */
struct ItemAttrCls_CostumWeapon : ItemAttributeClass
{
};

/* 2005 */
struct ItemAttrCls_CostumShield : ItemAttributeClass
{
};

/* 2006 */
struct ItemAttrCls_ActionItem : ItemAttributeClass
{
};

/* 2007 */
struct ItemAttrCls_Enchant : ItemAttributeClass
{
};

/* 2008 */
struct ItemAttrCls_GBCoin : ItemAttrCls_NotLot
{
};

/* 2009 */
struct ItemAttrCls_Capsule : ItemAttrCls_NotLot
{
};

/* 2010 */
struct ItemAttrCls_CardCollect_Close : ItemAttrCls_NotLot
{
};

/* 2011 */
struct ItemAttrCls_CardCollect : ItemAttrCls_NotLot
{
};

/* 2012 */
struct ItemAttrCls_NoEffect : ItemAttrCls_ByteLot
{
};

/* 2013 */
struct ItemAttrCls_ActiveSkill : ItemAttributeClass
{
};

/* 2014 */
struct ItemAttrCls_Pet : ItemAttrCls_NotLot
{
};

/* 2015 */
struct ItemAttrCls_Bracelet : ItemAttrCls_NotLot
{
};

struct ItemAttributeClassContainer
{
    HOOK_PUB_M ItemAttributeClassContainer* operator[] (ushort itemid)
    {
        return CallMemberFunction<ItemAttributeClassContainer, ItemAttributeClassContainer*, ushort>(0x0063E2A0, this, itemid);
    }
	
    ItemAttributeClass iacc_default;
    ItemAttrCls_ByteLot iacc_bytelot;
    ItemAttrCls_WordLot iacc_wordlot;
    ItemAttrCls_DwrdLot iacc_dwrdlot;
    ItemAttrCls_QuestLot iacc_quest;
    ItemAttrCls_Amulet iacc_amulet;
    ItemAttrCls_Weapon iacc_weapon;
    ItemAttrCls_Armor iacc_armor;
    ItemAttrCls_Shield iacc_shield;
    ItemAttrCls_Boot iacc_boot;
    ItemAttrCls_Furniture iacc_furniture;
    ItemAttrCls_Decoration iacc_decorate;
    ItemAttrCls_SkillScroll iacc_skillscroll;
    ItemAttrCls_RecallScroll iacc_recallscroll;
    ItemAttrCls_BindItem iacc_binditem;
    ItemAttrCls_UpSource iacc_upsource;
    ItemAttrCls_ItemChest iacc_itemchest;
    ItemAttrCls_WeaponTitlaLicence iacc_weapontitlalicence;
    ItemAttrCls_KingdomQuestItem iacc_kingdomquest;
    ItemAttrCls_MiniHouseSkin iacc_minihouseskin;
    ItemAttrCls_UpgradeRedGem iacc_upgraderedgem;
    ItemAttrCls_UpgradeBlueGem iacc_upgradebluegem;
    ItemAttrCls_UpgradeGoldGem iacc_upgradegoldgem;
    ItemAttrCls_KQStep iacc_kqstep;
    ItemAttrCls_Feed iacc_feed;
    ItemAttrCls_Riding iacc_riding;
    ItemAttrCls_Amount iacc_amount;
    ItemAttrCls_CostumWeapon iacc_costumweapon;
    ItemAttrCls_ActionItem iacc_actionitem;
    ItemAttrCls_Enchant iacc_enchant;
    ItemAttrCls_GBCoin iacc_gbcoin;
    ItemAttrCls_Capsule iacc_capsule;
    ItemAttributeClass* iacc_Array[34];
};

struct AssertClass
{
    void ac_AssertFail(const char* message, int flag)
    {
        CallMemberFunction<AssertClass, void, const char*, int>(0x0063C710, this, message, flag);
    }

    void ac_AssertFail(const char* message, const char* flag)
    {
        CallMemberFunction<AssertClass, void, const char*, const char*>(0x0063C6C0, this, message, flag);
    }

    unsigned __int16 ac_Write2File;
    char ac_Date[32];
    char ac_Time[32];
    char ac_FileName[32];
};

struct __declspec(align(4)) ClockWatch
{
    unsigned int cw_LastMilliSec;
    unsigned int cw_CurrMilliSec;
    unsigned __int64 cw_TotalMilliSec;
    unsigned int cw_CurrTick;
    unsigned int cw_DeltaTick;
    unsigned int cw_LastMilliSecByDelta;
    char cw_IsReset;
};

struct PROTO_NC_ACT_CHAT_REQ
{
    char itemLinkDataCount;
    char len;
    char content[];
};

struct ChargedItemEffectList
{
    struct __declspec(align(2)) ChargedItem
    {
        char _pad[0x270];
        ChargedEffectContainer ci_Effect;
        char ci_bRecalcParam;
    };
};

struct CSingleDataMap
{
    ushort GetValue(std::string index)
    {
        return m_SingleData[index];
    }

    std::map<std::string, unsigned short> m_SingleData;
};