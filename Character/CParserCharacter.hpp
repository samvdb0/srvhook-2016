#pragma once
#include "pch.h"

#include "CPFsCharacter.hpp"

void(__thiscall* CParserCharacter_Org)(class CParserCharacter* pthis);

class __declspec(align(4)) CParserCharacter : public CParser
{
	HOOK_PUB_S void Install_IndunRankFix()
	{
		CParserCharacter_Org = (void(__thiscall*)(CParserCharacter*)) Detour(0x0043B040, MF(Ctor));
	}

	void Ctor()
	{
		CParserCharacter_Org(this);

		m_PFT.Store(41, 19, MF(CPFsCharacter::fc_NC_INSTANCE_DUNGEON_RANK_SAVE_DB_CMD));
		m_PFT.Store(41, 21, MF(CPFsCharacter::fc_NC_INSTANCE_DUNGEON_RANK_UPDATE_DB_REQ));
		m_PFT.Store(41, 26, MF(CPFsCharacter::fc_NC_INSTANCE_DUNGEON_RANK_REQ));
	}
};