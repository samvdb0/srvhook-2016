#pragma once
#include "pch.h"

#include "ShineObject.hpp"

class ClientSession;

struct ProtocolPacket
{
    char* pp_Buffer;
    int pp_BufferSize;
    int pp_PacketLength;
};

struct GlobalProtocolPacket : ProtocolPacket
{
    char gpp_Buffer[8192];
};

struct ZoneBaseSession
{
    char _size[0x100];
};

struct PacketContainerBase
{
    virtual void pcb_SetSocketSession(ClientSession*);
    virtual void pcb_Clear();
    virtual char pcb_Flush(ClientSession*);
    virtual void pcb_Append(ShineObjectClass::ShineObject*, ProtocolPacket*);
};

struct PacketContainer : PacketContainerBase
{
    ClientSession* pc_Session;
    char pc_Buffer[8192];
    int pc_Pointer;
};

struct PacketEncrypt
{
    unsigned __int16 pe_point;
    unsigned __int16 pe_mark;
};

struct __declspec(align(2)) BriefInformationCharacter
{
    ProtocolPacket bic_pack;
    char bic_array[238];
    NETCOMMAND* bic_nc;
    PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD* bic_BriefInfo;
};
