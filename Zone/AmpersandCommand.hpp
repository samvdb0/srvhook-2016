#pragma once
#include "pch.h"

#include "ShinePlayer.hpp"

void(__thiscall* AmpersandCommand_Org)(class AmpersandCommand* pthis);
typedef void(__fastcall* AC_CommandTemplate) (void*, DWORD, unsigned __int16 handle, ShineObjectClass::ShinePlayer* ply, int argNum, char(*arg)[33]);
typedef void(__stdcall* _AC_Command) (unsigned __int16 handle, ShineObjectClass::ShinePlayer* shinePlayer, int argNum, char(*arg)[33]);
_AC_Command ac_LearnSkill = (_AC_Command) 0x0041C290;
_AC_Command ac_LearnPassive = (_AC_Command)0x0041F270;
_AC_Command ac_SetAbstate = (_AC_Command)0x0041C410;
_AC_Command ac_MakeItem = (_AC_Command)0x0041B8A0;
_AC_Command ac_ExpBonus = (_AC_Command)0x0041E190;

typedef void(__thiscall* _AC_Store) (void* pthis, const char* cmd, int adminLevel, AC_CommandTemplate func, DWORD unk1, DWORD unk2, DWORD unk3);
_AC_Store ac_Store = (_AC_Store) 0x0041A310;

inline void __fastcall ac_Test(void*, DWORD, unsigned __int16 handle, ShineObjectClass::ShinePlayer* ply, int argNum, char(*arg)[33])
{
	ply->so_ply_Notice("Hey!");
}

inline void __fastcall ac_LinkToTown(void*, DWORD, unsigned __int16 handle, ShineObjectClass::ShinePlayer* ply, int argNum, char(*arg)[33])
{
	ply->so_ply_Notice("Hey!");
}

class AmpersandCommand
{
	HOOK_PUB_S void Install_Commands()
	{
		//AmpersandCommand_Org = (void(__thiscall*)(AmpersandCommand*))Detour(0x00425B70, MF(AmpersandCommandCtor));
		
		ampcmd.RegisterCommand("&town", 0, ac_LinkToTown);
	}

	HOOK_PUB_M void RegisterCommand(const char* name, int adminLv, AC_CommandTemplate function)
	{
		ac_Store(this, name, adminLv, function, 0, 0, 0);
	}

	HOOK_PUB_S void LearnSkill(ShineObjectClass::ShinePlayer* player, UINT16 skill)
	{
		char skillBuff[33];
		sprintf(skillBuff, "%d", skill);

		ac_LearnSkill(player->so_handle.sohu_Handle, player, 1, &skillBuff);
	}

	HOOK_PUB_S void MakeItem(ShineObjectClass::ShinePlayer* player, const char* itemIndx, char enchant = 0)
	{
		char itemBuff[33];
		sprintf(itemBuff, "%s %d", itemIndx, enchant);

		ac_MakeItem(player->so_handle.sohu_Handle, player, 1, &itemBuff);
	}

	HOOK_PUB_S void LearnPassive(ShineObjectClass::ShinePlayer* player, UINT16 skill)
	{
		char skillBuff[33];
		sprintf(skillBuff, "%d", skill);

		ac_LearnPassive(player->so_handle.sohu_Handle, player, 1, &skillBuff);
	}

	HOOK_PUB_S void SetAbState(ShineObjectClass::ShinePlayer* player, const char* abstate, UINT32 strength, UINT32 keepTime)
	{
		char abstateBuff[33];
		sprintf(abstateBuff, "%s %d %d", abstate, keepTime, strength);

		ac_SetAbstate(player->so_handle.sohu_Handle, player, 3, &abstateBuff);
	}
	
	char _size[0x2818];

	static AmpersandCommand& ampcmd;
};

AmpersandCommand& AmpersandCommand::ampcmd = *(AmpersandCommand*)0x0087C770;
