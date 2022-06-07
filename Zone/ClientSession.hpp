#pragma once
#include "pch.h"

void(__thiscall* cs_zbs_Parsing_Org)(class ClientSession* pthis, ShineObjectClass::ShinePlayer* sp, int handle);

class ClientSession
{
	HOOK_PUB_S void Install_PacketProtection()
	{
		cs_zbs_Parsing_Org = (void(__thiscall*)(ClientSession*, ShineObjectClass::ShinePlayer*, int)) Detour(0x004FB9F0, MF(zbs_Parsing));
	}

	HOOK_PUB_M void zbs_Parsing(ShineObjectClass::ShinePlayer* ply, int handle)
	{
		try
		{
#ifdef DEMO_VERSION
			if (Global::g_ZoneServer.zs_clientsessionmanager.m_NumSessions > DEMO_PLAYER_LIMIT)
			{
				ply->so_banning(ShineObjectClass::REMOVE_NOW);
			}
#endif
			
			cs_zbs_Parsing_Org(this, ply, handle);
		}
		catch (...)
		{
			if (ply) 
			{
				ply->so_banning(ShineObjectClass::RemoveWhen::REMOVE_NOW);
			}
		}
	}
};