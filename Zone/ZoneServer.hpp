#pragma once
#include "pch.h"

#include "Generic.h"
#include "LuaScript.hpp"

#ifdef WEB_API
#include "WebAPI.hpp"

inline DWORD WINAPI WebThread(LPVOID lp)
{
    auto web = WebAPI();
	
    return 0;
}
#endif

class ZoneServer
{
	HOOK_PUB_S void Install_GRFix()
	{
        Detour(0x005B07A0, MF(zs_LuaFromHTML));
	}

	HOOK_PUB_M bool zs_LuaFromHTML(char* address, int port)
	{
		#ifdef WEB_API
        CreateThread(NULL, 0, WebThread, NULL, 0, 0);
		#endif
		
        Global::g_LuaArgument.Interval = 999999;
        Global::g_LuaArgument.MaxSkip = 999999;
		
        SetConsoleTitleA(FORMAT_STR("[srvHook] ZoneServer v3.0.4-dev - Zone[%d]", zs_serverinfo.myserver.nZoneNo));

        if (LuaScript::chrlghk())
        {
            Global::g_LuaSecurity.lsf_Factor = 1.0;
            Global::g_LuaSecurity.lsf_IsFreeze = true;
            Global::g_LuaSecurity.lsf_IsRecover = false;
        	
            Log::Info("ZoneServer started succesfully.");
            return true;
        }

        return false;
	}

public:
    CThread zs_mainthread;
    CThread zs_stackcheck;
    CThread zs_ServiceThread;
    CThread zs_Certify;
    ZoneServerInfo zs_serverinfo;
    CIOCP zs_IOCP;
    CSocket_Acceptor zs_Acceptor;
    ClientSessionManager zs_clientsessionmanager;

    static ZoneServer& Instance;
};
