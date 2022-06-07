#pragma once
#include "pch.h"

#include "Generic.h"

struct ShineCommonParameter
{
    struct CommonParameter
    {
        char level;
        char nextexp[50];
        __declspec(align(1)) unsigned __int16 stat[28];
        __declspec(align(1)) unsigned int ExpLostAtPvP;
        char checksum;
    };

    struct FreeStatCon
    {
        char Stat;
        __declspec(align(1)) unsigned __int16 ACAbsoulte;
        __declspec(align(1)) unsigned __int16 BlockRate;
        __declspec(align(1)) unsigned __int16 MaxHP;
        char checksum;
    };

    struct FreeStatDex
    {
        char Stat;
        __declspec(align(1)) unsigned __int16 THRate;
        __declspec(align(1)) unsigned __int16 TBRate;
        char checksum;
    };
	
    struct FreeStatInt
    {
        char Stat;
        __declspec(align(1)) unsigned __int16 MAAbsolute;
        char checksum;
    };
	
    struct FreeStatMen
    {
        char Stat;
        __declspec(align(1)) unsigned __int16 MRAbsolute;
        __declspec(align(1)) unsigned __int16 CriRate;
        __declspec(align(1)) unsigned __int16 MaxSP;
        char checksum;
    };
	
    struct FreeStatStr
    {
        char Stat;
        __declspec(align(1)) unsigned __int16 WCAbsolute;
        char checksum;
    };

    struct ShineParameter
    {
        unsigned int chrrunspeed;
        unsigned int chrwalkspeed;
        unsigned int chrattackspeed;
        unsigned int shoutlevel;
        unsigned int shoutdelay;
        char levellimit;
        char _pad0[0x3];
        long double maxexpbonus;
        unsigned int RestExpRate;
        unsigned int MinNeedTime;
        unsigned int DefaultBonusTime;
        unsigned int IntervalTime;
        unsigned int AddBuffTime;
        unsigned int MaxBuffTime;
        char LostExpLevel;
        char MaxFreeStat;
        char _pad1[0x6];
        unsigned __int64 nextexp[151];
        CommonParameter* commonparam[151];
        FreeStatStr** freestatStr;
        FreeStatInt** freestatInt;
        FreeStatDex** freestatDex;
        FreeStatCon** freestatCon;
        FreeStatMen** freestatMen;
    };

    HOOK_PUB_M OptionReader scp_or;
    HOOK_PUB_M char _pad[0x4];
    HOOK_PUB_M ShineParameter scp_param;
};