#pragma once
#include "pch.h"

#include "Events.hpp"
#include "Generic.h"

#include "Globals.h"

void(__stdcall* Send_PROTO_NC_ANNOUNCE_Z2W_CMD) (char announceType, const char* msg) = (void(__stdcall*) (char, const char*)) 0x005B8D30;
int(__thiscall* AnnounceSystem_LevelMax_Org) (class CAnnounceSystem* pthis, Name5* pCharName, uchar nLevel);

class CAnnounceSystem
{
	HOOK_PUB_S void Install_LevelUp()
	{
		AnnounceSystem_LevelMax_Org = (int(__thiscall*) (CAnnounceSystem* pthis, Name5 * pCharName, uchar nLevel)) Detour(0x005B8F70, MF(AnnounceSystem_LevelMax));
	}
	
	HOOK_PUB_S void WorldNotice(const char* msg)
	{
		Send_PROTO_NC_ANNOUNCE_Z2W_CMD(1, msg);
	}

	HOOK_PUB_M int AnnounceSystem_LevelMax(Name5* pCharName, uchar nLevel)
	{
		auto ply = Global::g_ShineObjectManager.FindPlayer(pCharName);

		if (ply)
		{
			Events::OnLevelUp(ply, nLevel);
		}
		
		return AnnounceSystem_LevelMax_Org(this, pCharName, nLevel);
	}
};