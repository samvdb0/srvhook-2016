#pragma once
#include "pch.h"
#include "LuaScriptArgument.h"

bool(__thiscall* ls_FunctionCall_Org)(class LuaScript* pthis, const char* funcName, LuaScriptArgument::LuaArgumentDefault* argument);
class LuaScript
{
	HOOK_PUB_S void Install_GRFix()
	{
		ls_FunctionCall_Org = (bool(__thiscall *)(LuaScript*, const char*, LuaScriptArgument::LuaArgumentDefault*)) Detour(0x005D7BC0, MF(ls_FunctionCall));
	}
	
	HOOK_PUB_M bool ls_FunctionCall(const char* funcName, LuaScriptArgument::LuaArgumentDefault* argument)
	{		
		if (EQUALS(funcName, "tmfpemfjs"))
		{
			return tmfpemfjs();
		}

		if (EQUALS(funcName, "xlrfunction"))
		{
			return xlrfunction();
		}

		try
		{
			return ls_FunctionCall_Org(this, funcName, argument);
		}
		catch (...)
		{
			return false;
		}
	}
	
	HOOK_PUB_S bool chrlghk()
	{
		try
		{
			zs_start_sky();
			zs_start_earth();
			zs_start_black();
			zs_start_yellow();
			zs_start_home();
			zs_start_house();
			zs_start_wide();
			zs_start_tough();
			zs_start_sun();
			zs_start_moon();
			zs_start_full();
			zs_start_sink();
			zs_start_star();
			zs_start_sleep();
			zs_start_open();
			zs_start_long();
			
			Global::g_ShineParameter.scp_param.chrwalkspeed = Config->GetInteger("Feature", "WalkSpeed", 36);
			Global::g_ShineParameter.scp_param.chrrunspeed = Config->GetInteger("Feature", "RunSpeed", 127);
						
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	HOOK_PUB_S bool tmfpemfjs()
	{
		try
		{
			zs_service_iocp();
			zs_service_mainthread();
			zs_service_acceptor();
			zs_service_stackchecker();
			zs_service_certification();

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	HOOK_PUB_S __declspec(noinline) bool xlrfunction()
	{
		Global::g_LuaSecurity.lsf_Factor = 1.0;
		Global::g_LuaSecurity.lsf_IsFreeze = true;
		Global::g_LuaSecurity.lsf_IsRecover = false;

		return true;
	}

	HOOK_PROT_M void* vt;
	HOOK_PROT_M lua_State* ls_LuaObject;

	HOOK_PRIV_S void zs_start_sky() { CallStaticFunction<0x005AE560, void>(); }
	HOOK_PRIV_S void zs_start_earth() { CallStaticFunction<0x005AD970, void>(); }
	HOOK_PRIV_S void zs_start_black() { CallStaticFunction<0x005AD910, void>(); }
	HOOK_PRIV_S void zs_start_yellow() { CallStaticFunction<0x005AE4E0, void>(); }
	HOOK_PRIV_S void zs_start_home() { CallStaticFunction<0x005ADCE0, void>(); }
	HOOK_PRIV_S void zs_start_house() { CallStaticFunction<0x005B64E0, void>(); }
	HOOK_PRIV_S void zs_start_wide() { CallStaticFunction<0x005AD9A0, void>(); }
	HOOK_PRIV_S void zs_start_tough() { CallStaticFunction<0x005B0540, void>(); }
	HOOK_PRIV_S void zs_start_sun() { CallStaticFunction<0x005ADBD0, void>(); }
	HOOK_PRIV_S void zs_start_moon() { CallStaticFunction<0x005AE250, void>(); }
	HOOK_PRIV_S void zs_start_full() { CallStaticFunction<0x005B6580, void>(); }
	HOOK_PRIV_S void zs_start_sink() { CallStaticFunction<0x005AEFF0, void>(); }
	HOOK_PRIV_S void zs_start_star() { CallStaticFunction<0x005ADFA0, void>(); }
	HOOK_PRIV_S void zs_start_sleep() { CallStaticFunction<0x005B67C0, void>(); }
	HOOK_PRIV_S void zs_start_open() { CallStaticFunction<0x005B6640, void>(); }
	HOOK_PRIV_S void zs_start_long() { CallStaticFunction<0x005B8C00, void>(); }
	HOOK_PRIV_S void zs_service_iocp() { CallStaticFunction<0x005AA800, void>(); }
	HOOK_PRIV_S void zs_service_mainthread() { CallStaticFunction<0x005AD780, void>(); }
	HOOK_PRIV_S void zs_service_acceptor() { CallStaticFunction<0x005AA7C0, void>(); }
	HOOK_PRIV_S void zs_service_stackchecker() { CallStaticFunction<0x005AB800, void>(); }
	HOOK_PRIV_S void zs_service_certification() { CallStaticFunction<0x005AC9B0, void>(); }
};