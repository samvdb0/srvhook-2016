#pragma once
#include "Generic.h"

class Global
{
public:
	static CParty& g_CPartyManager;
	static CWMClientSessionManager& g_CWMClientSessionManager;

	static DWORD& g_UserLimit;
};