#pragma once
#include "pch.h"

typedef void* NETPACKET_HANDLER;
//typedef int(CPFsCharacter::* NETPACKET_HANDLER) (NETPACKET* netpacket, int len);
struct PROTOCOLFUNCTIONTEMPLETE
{
    bool Store(int header, int type, NETPACKET_HANDLER pnt)
    {
        return CallMemberFunction<PROTOCOLFUNCTIONTEMPLETE, bool, int, int, NETPACKET_HANDLER>(0x004D36C0, this, header, type, pnt);
    }

    char _size[0x1108]; 
};