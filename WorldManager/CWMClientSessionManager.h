#pragma once
#include "pch.h"
#include "Globals.h"

int(__thiscall* InitSessions_Org)(void* pthis, int MaxSessions);

class CWMClientSessionManagerH
{
public:
	__declspec(noinline) static void Install()
	{
		// InitSessions_Org = (int(__thiscall*)(void*, int)) Detour(0x00437FD0, MF(InitSessions));
	}

	int InitSessions(int maxSessions)
	{		
		// auto result = InitSessions_Org(this, DEMO_PLAYER_LIMIT);
		// 
		// Global::g_CWMClientSessionManager.m_MaxSessions = DEMO_PLAYER_LIMIT;
		// Global::g_UserLimit = DEMO_PLAYER_LIMIT;

		// return result;
	}
};