#pragma once
#pragma pack(push, 1)
struct SHINE_XY_TYPE
{
    unsigned int x;
    unsigned int y;
};

union Name3
{
    char n3_name[12];
    unsigned int n3_code[3];
};

union Name5
{
    char n5_name[20];
    unsigned int n5_code[5];
};

union NETCOMMAND
{
    unsigned __int16 protocol;
    struct
    {
        unsigned __int16 command : 10;
        unsigned __int16 department : 6;
    } str;
};

struct NETPACKET
{
    NETCOMMAND netcmd;
    char data[];
};

struct PROTO_NC_MAP_LINKEND_CMD
{
    unsigned __int16 wmshandle;
    unsigned __int16 zonehandle;
    unsigned int chrregnum;
    Name3 map;
    char zoneid;
    SHINE_XY_TYPE location;
    char StoreType;
    unsigned __int64 CharExp;
    unsigned __int64 CharMoney;
    char IsPartyRelease;
};

struct CLooting
{
    char _size[0x14];
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
	struct PARTY_SLOT
	{
        struct PARTY_MEMBER_SLOT
        {
            PROTO_PARTY_MEMBER_AND_ZONEMERCHINE MemberInform;
            struct ShineObject* memberobj;
        };

        char NumOfMember;
        PARTY_MEMBER_SLOT Members[5];
        CLooting m_Looting;
        bool IsBelongItemDiceGameIng;
        bool isRaidTypeParty;
	};

	PARTY_SLOT* GetParty(ushort prt)
	{
        return CallMemberFunction<CParty, PARTY_SLOT*, ushort>(0x00464F50, this, prt);
	}
};

struct CWMBaseSession
{
    char _size[0x114];
};

struct CWMBaseSessionManager
{
    struct WM_SESSION_LIST
    {
        CWMBaseSessionManager::WM_SESSION_LIST* pLinkUp;
        CWMBaseSessionManager::WM_SESSION_LIST* pLinkDown;
        CWMBaseSession* pSession;
    };

    virtual void Dummy();

    CWMBaseSessionManager::WM_SESSION_LIST* m_pSessionListArray;
    int m_MaxSessions;
    int m_NumSessions;
    CWMBaseSessionManager::WM_SESSION_LIST* m_pActiveSessions;
    CWMBaseSessionManager::WM_SESSION_LIST* m_pEmptySessions;
};

struct CWMClientSession
{
    BOOL IsInRaid() { return CallMemberFunction<CWMClientSession, BOOL>(0x00431240, this); }
};


struct ANNOUNCE_MESSAGE
{
    char AnnounceType;
    char SizeOfMessage;
    char Message[256];
};

struct CSendPacket
{
    // 0x0044F880
    CSendPacket()
    {
        m_Packet.Size.type1.size = 2;
        m_Packet.ID = 0;
        m_DataSize = 0;
    }

    CSendPacket* ID(ushort protocol, size_t size, void* data)
    {
        return CallMemberFunction<CSendPacket, CSendPacket*, ushort, size_t, void*>(0x0045FE70, this, protocol, size, data);
    }

    struct __declspec(align(1)) PACKET_SIZE1
    {
        unsigned __int16 dummy;
        char size;
    };

    struct __declspec(align(1)) PACKET_SIZE2
    {
        char sizezero;
        unsigned __int16 size;
    };

    union PACKET_SIZE
    {
        PACKET_SIZE1 type1;
        PACKET_SIZE2 type2;
    };

    struct PACKET
    {
        PACKET_SIZE Size;
        __declspec(align(1)) unsigned __int16 ID;
        char Data[8187];
    };

    PACKET m_Packet;
    unsigned int m_DataSize;
};

struct CWMClientSessionManager : public CWMBaseSessionManager
{
    CWMClientSession* GetSession(ushort handle) { return CallMemberFunction<CWMClientSessionManager, CWMClientSession*, ushort>(0x00437860, this, handle); }
    static int BroadCastToPlayer(CSendPacket* packet, int isRoar) { return ((int(__stdcall*)(CSendPacket*, int))0x00437B40)(packet, isRoar); }

    CWMClientSession* m_pSessionArray;
    int m_NextSendWMTime;
    unsigned __int16 m_ClientSeed;
    std::vector<CWMClientSession**> m_SessionGroupByIPArray;
};
#pragma pack(pop)