#pragma once
#include "pch.h"

int(__thiscall* InitSessions_Org)(void* pthis, int MaxSessions);

class ClientSessionManagerH
{
public:
	__declspec(noinline) static void Install()
	{
		// InitSessions_Org = (int(__thiscall*)(void*, int)) Detour(0x0045C4C0, MF(InitSessions));
	}

	int InitSessions(int maxSessions)
	{
		// auto result = InitSessions_Org(this, DEMO_PLAYER_LIMIT);
		// 
		// return result;
	}	
};