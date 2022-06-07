#pragma once
#include "pch.h"

#include "NETCOMMAND.h"

inline void __stdcall gds_NC_SKILL_SKILLTEACHFAIL_ACK(NETCOMMAND* netcmd, int len)
{
	// fix for failed to learn skill
	
	return;

	// NC_SKILL_SKILLTEACHFAIL_ACK_Org(netcmd, len);
}

void(__thiscall* gdb_zbs_Parsing_Org)(class GameDBSession* pthis, ShineObjectClass::ShinePlayer* sp, int handle);

class GameDBSession
{
	HOOK_PUB_S void Install_AutoSkillFix()
	{
		Detour(0x0044EE70, gds_NC_SKILL_SKILLTEACHFAIL_ACK);

		gdb_zbs_Parsing_Org = (void(__thiscall*)(class GameDBSession*, ShineObjectClass::ShinePlayer*, int)) Detour(0x004FB6C0, MF(zbs_Parsing));
	}

	HOOK_PUB_M void zbs_Parsing(ShineObjectClass::ShinePlayer* ply, int handle)
	{
		try
		{
			gdb_zbs_Parsing_Org(this, ply, handle);
		}
		catch (...)
		{

		}
	}
	
	//HOOK_PUB_S void gds_NC_SKILL_SKILLTEACHFAIL_ACK(NETCOMMAND* netcmd, int len)
	//{
	//
	//}
};