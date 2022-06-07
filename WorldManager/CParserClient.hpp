#pragma once
#include "pch.h"
#include "Generic.h"
#include "DataStore.hpp"
#include "Globals.h"

int(__thiscall* cpc_Parser_Org)(void* pthis, void* pSession);

int(__thiscall* fc_NC_RAID_MAKE_REQ_Org)(void* pthis, void* pSession, void* netpacket, int len);
int(__thiscall* fc_NC_RAID_INVITATION_ANSWER_REQ_Org)(void* pthis, void* pSession, void* netpacket, int len);


class CParserClient
{
public:
	static void Install_CrashFix()
	{
		cpc_Parser_Org = (int(__thiscall *)(void*, void*))Detour(0x00419690, MF(ParserH));
	}

	static void Install_NoRaidMaps()
	{
		fc_NC_RAID_MAKE_REQ_Org = (int(__thiscall*)(void*, void*, void*, int))Detour(0x0041ED50, MF(fc_NC_RAID_MAKE_REQ));
		fc_NC_RAID_INVITATION_ANSWER_REQ_Org = (int(__thiscall*)(void*, void*, void*, int))Detour(0x00422400, MF(fc_NC_RAID_INVITATION_ANSWER_REQ));
	}

	int ParserH(void* pSession)
	{
#ifdef DEMO_VERSION
		Global::g_CWMClientSessionManager.m_MaxSessions = DEMO_PLAYER_LIMIT;
		if (Global::g_CWMClientSessionManager.m_NumSessions > DEMO_PLAYER_LIMIT)
		{
			return 0;
		}
#endif
		
		try
		{
			return cpc_Parser_Org(this, pSession);
		}
		catch (...)
		{
			return 0;
		}
	}

	int fc_NC_RAID_MAKE_REQ(void* pSession, void* netpacket, int len)
	{
		auto map = (Name3*)(*(DWORD*)((DWORD)pSession + 0x560) + 0x42); // pSession->m_pCharDataBase->logininfo.currentmap
		auto partyno = *(ushort*)((DWORD)pSession + 0x639); // pSession->m_CharDataGame.client.partyno
		auto party = Global::g_CPartyManager.GetParty(partyno);

		if (!party)
		{
			return 1;
		}

		for (auto i = 0; i < party->NumOfMember; i++)
		{
			auto memb = Global::g_CWMClientSessionManager.GetSession(party->Members[i].MemberInform.Member.wmcharhandle);

			if (memb != nullptr && DataStore::IsNoRaidMap(((Name3*)(*(DWORD*)((DWORD)memb + 0x560) + 0x42))->n3_name)) // pSession->m_pCharDataBase->logininfo.currentmap
			{
				return 1;
			}
		}
		
		if (DataStore::IsNoRaidMap(map->n3_name))
		{
			return 1;
		}

		return fc_NC_RAID_MAKE_REQ_Org(this, pSession, netpacket, len);
	}

	int fc_NC_RAID_INVITATION_ANSWER_REQ(void* pSession, void* netpacket, int len)
	{
		auto map = (Name3*)(*(DWORD*)((DWORD)pSession + 0x560) + 0x42); // pSession->m_pCharDataBase->logininfo.currentmap

		if (DataStore::IsNoRaidMap(map->n3_name))
		{
			return 1;
		}

		return fc_NC_RAID_INVITATION_ANSWER_REQ_Org(this, pSession, netpacket, len);
	}
	
protected:
	char _size[0x1108];
};