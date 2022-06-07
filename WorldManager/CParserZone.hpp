#pragma once
#include "pch.h"
#include "Generic.h"

int(__thiscall* fc_NC_MAP_LINKEND_Org)(class CParserZone* pthis, void* pSession, void* netpacket, int len);

class CParserZone
{
public:
	static void Install_NoExpoMaps()
	{
		fc_NC_MAP_LINKEND_Org = (int(__thiscall*)(CParserZone*, void*, void*, int))Detour(0x0042D8D0, MF(fc_NC_MAP_LINKEND_CMD));
	}

	int fc_NC_MAP_LINKEND_CMD(void* pSession, NETPACKET* netpacket, int len)
	{
		try
		{
			auto np = (PROTO_NC_MAP_LINKEND_CMD*)netpacket->data;
			auto sess = Global::g_CWMClientSessionManager.GetSession(np->wmshandle);

			if (sess != nullptr && sess->IsInRaid() && DataStore::IsNoRaidMap(np->map.n3_name))
			{
				np->IsPartyRelease = 1;
			}

			return fc_NC_MAP_LINKEND_Org(this, pSession, netpacket, len);
		}
		catch (...)
		{
			return fc_NC_MAP_LINKEND_Org(this, pSession, netpacket, len);
		}
	}
};