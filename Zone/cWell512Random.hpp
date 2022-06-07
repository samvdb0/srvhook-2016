#pragma once
#include "pch.h"

class cWell512Random
{
	HOOK_PUB_M uint well512_GetRandom(uint maxValue)
	{
		return CallMemberFunction<cWell512Random, uint, uint>(0x0063CB10, this, maxValue);
	}

	HOOK_PUB_M uint well512_GetRandom(uint minValue, uint maxValue)
	{
		return CallMemberFunction<cWell512Random, uint, uint, uint>(0x0063CAB0, this, minValue, maxValue);
	}
	
    HOOK_PROT_M unsigned int m_nState[16];
    HOOK_PROT_M unsigned int m_nIndex;
    HOOK_PROT_M unsigned int m_nZ0;
    HOOK_PROT_M unsigned int m_nZ1;
    HOOK_PROT_M unsigned int m_nZ2;
};