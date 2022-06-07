#pragma once
#include "pch.h"

#include <functional>

#include "CParserClient.hpp"
#include "DataStore.hpp"
#include "CParserZone.hpp"
#include "CWMClientSessionManager.h"
#include "HookScript.hpp"
#include "RankingServer.hpp"

bool(__thiscall* onServiceStart_Org)(void* pthis);
class WinService
{
    HOOK_PUB_S void InstallHook()
    {
        onServiceStart_Org = (bool(__thiscall*)(void*)) Detour(0x00466DE0, MF(onServiceStart));

#ifdef CONSOLE
        Detour(0x00466CB0, MF(QueryServiceStatus));
        Detour(0x00466FD0, MF(StartDispatcher));
#endif
    }

    HOOK_PUB_M int QueryServiceStatus(uint* result, const char* netMachine, const char* serviceName)
    {
        return 1;
    }

    HOOK_PUB_S bool OnStart_Service()
    {
        return CallStaticFunction<0x00403760, bool>();
    }

    HOOK_PUB_S bool ServiceLoop()
    {
        return CallStaticFunction<0x00466EA0, bool>();
    }

    HOOK_PUB_M bool onServiceStart()
    {
		std::vector<std::function<void()>> toHook;

        DataStore::Load();
    	
        // Always-On fixes
        toHook.emplace_back(&CParserClient::Install_CrashFix);
        toHook.emplace_back(&CParserClient::Install_NoRaidMaps);
        toHook.emplace_back(&CParserZone::Install_NoExpoMaps);

        if (Config->GetBoolean("Feature", "HookScriptWM", false))
        {
            HookScript::Instance = new HookScript();
            HookScript::Instance->Load(FORMAT_STR("..\\%s\\Lua.WM\\hook.lua", Config->Get("Path", "Hook", "9Data/Hook")));
        }

        uchar skipAnnounce[] = { 0xE9, 0x97, 0x00, 0x00, 0x00, 0x90 };
        uchar bootTimer[] = { 15 };

        WriteMem((DWORD*)0x0040FBB3, skipAnnounce, sizeof skipAnnounce);
        WriteMem((DWORD*)0x0040FC6F, skipAnnounce, sizeof skipAnnounce);
        WriteMem((DWORD*)0x0040FD2B, skipAnnounce, sizeof skipAnnounce);

        WriteMem((DWORD*)0x00438D66, bootTimer, 1);

#ifdef DEMO_VERSION
        CWMClientSessionManagerH::Install();
#endif

        for (UINT32 i = 0; i < toHook.size(); i++)
        {
            toHook.at(i)();
        }

#ifndef CONSOLE
        return onServiceStart_Org(this);
#else
        return OnStart_Service();
#endif
    }

    HOOK_PUB_M bool StartDispatcher(void* svcName, bool(__cdecl* startCallBack)(), void(__cdecl* stopCallBack)())
    {
        serviceStartFunc = startCallBack;
        serviceStopFunc = stopCallBack;

        return ServiceLoop();
    }

    // Values
    char _pad[0x4];
    HOOK_PROT_M bool(__cdecl* serviceStartFunc)();
    HOOK_PROT_M void(__cdecl* serviceStopFunc)();
    HOOK_PROT_M char serviceName[0x10];
    HOOK_PROT_M SERVICE_STATUS_HANDLE__* handleServiceStatus;
    HOOK_PROT_M void* handleServiceEvent;
    HOOK_PROT_M unsigned int statusEvent;
    HOOK_PROT_M _SERVICE_STATUS ssQueryControl;
};
