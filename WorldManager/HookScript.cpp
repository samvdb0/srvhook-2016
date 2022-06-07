#include "pch.h"
#include "HookScript.hpp"

#include "Globals.h"

HookScript* HookScript::Instance;

static DWORD WINAPI ThreadStarter(LPVOID param)
{
	((HookScript*)param)->Main();

	return 1;
}

HookScript::HookScript()
{

}

void HookScript::Load(const char* path)
{
	hs_State = luaL_newstate();
	luaL_openlibs(hs_State);

	lua_register(hs_State, "cAddTimer", cAddTimer);
	lua_register(hs_State, "cSessionCount", cSessionCount);
	lua_register(hs_State, "cNotice", cNotice);

	#ifdef CONSOLE
	lua_register(hs_State, "cLog", cLog);
	#endif

	if (luaL_loadfile(hs_State, path))
	{
		Log::Error("Hook/Lua.WM/hook.lua does not exist.");
		exit(0);
	}

	if (lua_pcallk(hs_State, 0, -1, 0, 0, nullptr) != LUA_OK)
	{
		Log::Error("An error occurred loading Hook/Lua.WM/hook.lua");
		exit(0);
	}

	CreateThread(nullptr, 0, &ThreadStarter, this, 0, nullptr);
}

bool HookScript::ExecuteFunction(const char* fn)
{
	lua_getglobal(hs_State, fn);
	return lua_pcall(hs_State, 0, 0, 0) == LUA_OK;
}

void HookScript::Main()
{
	ExecuteFunction("init");

	while (true)
	{
		for (auto it = Timers.begin(); it != Timers.end(); ++it)
		{
			if (NOW() >= it->RunTime)
			{
				it->RunTime = NOW() + it->RunTimeGap;

				ExecuteFunction(it->Func);
			}
		}

		Sleep(10);
	}
}

int HookScript::cAddTimer(lua_State* L)
{
	auto result = 0;

	if (lua_type(L, 1))
	{
		auto gap = lua_tonumber(L, 1);
		auto str = lua_tostring(L, 2);

		if (str)
		{
			Timer t;
			t.RunTimeGap = gap;
			t.Func = str;
			t.RunTime = NOW() + gap;

			Instance->Timers.push_back(t);
		}
	}

	return result;
}

int HookScript::cLog(lua_State* L)
{
	auto result = 0;

	if (lua_type(L, 1))
	{
		auto msg = lua_tostring(L, 1);

		Log::Info(msg);
	}

	return result;
}

int HookScript::cSessionCount(lua_State* L)
{
	lua_pushnumber(L, Global::g_CWMClientSessionManager.m_NumSessions);

	return 1;
}

int HookScript::cNotice(lua_State* L)
{
	if (lua_isstring(L, 1))
	{
		size_t len = 0;
		auto str = lua_tolstring(L, 1, &len);

		ANNOUNCE_MESSAGE msg;
		ZeroMemory(&msg, sizeof msg);
		msg.AnnounceType = 1;
		strcpy_s(msg.Message, str);
		msg.SizeOfMessage = len;

		auto packet = new CSendPacket();
		packet->ID(0x6402, len + 4, &msg);
		
		CWMClientSessionManager::BroadCastToPlayer(packet, 0);
		delete packet;
	}

	return 1;
}