#pragma once
#include "pch.h"

#include <functional>

#include "CParserCharacter.hpp"
#include "CPFsCharacter.hpp"

bool(__thiscall* onServiceStart_Org)(void* pthis);
class WinService
{
    HOOK_PUB_S void InstallHook()
    {
        onServiceStart_Org = (bool(__thiscall*)(void*)) Detour(0x0044C110, MF(onServiceStart));

#ifdef CONSOLE
        Detour(0x0044BFE0, MF(QueryServiceStatus));
        Detour(0x0044C300, MF(StartDispatcher));
#endif
    }

    HOOK_PUB_M int QueryServiceStatus(uint* result, const char* netMachine, const char* serviceName)
    {
        return 1;
    }

    HOOK_PUB_S bool OnStart_Service()
    {
        return CallStaticFunction<0x004029A0, bool>();
    }

    HOOK_PUB_S bool ServiceLoop()
    {
        return CallStaticFunction<0x0044C1D0, bool>();
    }

    HOOK_PUB_M bool onServiceStart()
    {	
        std::vector<std::function<void()>> toHook;

        if (Config->GetBoolean("Experimental", "InstanceDungeonRanking", false))
        {
            toHook.emplace_back(&CParserCharacter::Install_IndunRankFix);
            toHook.emplace_back(&CPFsCharacter::Install_IndunRankFix);
        }

        if (Config->GetBoolean("Feature", "NewInventorySlots", false))
        {
            toHook.emplace_back(&CPFsCharacter::Install_InventoryFix);
        }

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
