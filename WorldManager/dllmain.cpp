#include "pch.h"

#include "WinService.hpp"

LONG WINAPI VectoredEH(PEXCEPTION_POINTERS exc)
{
	return EXCEPTION_CONTINUE_EXECUTION;
}

LONG WINAPI FilterEH(PEXCEPTION_POINTERS exc)
{
	return EXCEPTION_CONTINUE_EXECUTION;
}

void SetupExceptionHandler()
{
	AddVectoredExceptionHandler(1, VectoredEH);
	SetUnhandledExceptionFilter(FilterEH);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {    	
		StartupTime = NOW();
		Config = new INIReader(FORMAT_STR("%s../Config.ini", GetBaseDir()));
		
    	if (Config->GetBoolean("Experimental", "RankingCapFix", false))
    	{
            RankingServer::Install_RankingServer();

            //uchar nopper[] = { 0x90, 0x90 };
            //WriteMem((DWORD*)0x00402496, nopper, sizeof nopper);
    	}
        
		#ifdef CONSOLE
		AllocConsole();
		freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
		freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std::ios_base::sync_with_stdio();
		SetConsoleTitleA("[srvHook] WorldManager v3.0.4-dev");
		#endif
    	
		SetupExceptionHandler();
    	
		WinService::InstallHook();
    }

    return TRUE;
}

