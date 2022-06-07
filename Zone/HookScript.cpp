#include "pch.h"
#include "HookScript.hpp"


#include <iterator>
#include <sstream>
#include <lua.hpp>
#pragma comment(lib, "lua52.lib")

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

	lua_register(hs_State, "cAddTimer",		cAddTimer);
	lua_register(hs_State, "cAddCommand",	cAddCommand);
	lua_register(hs_State, "cLog",			cLog);

	funcsetstruct fuck;
	fuck.vfptr = nullptr;
	fuck.ls_LuaObject = hs_State;

	// Register all LuaScriptScenario functions.
	CallMemberFunction<funcsetstruct, bool>(0x005F5350, &fuck);

	if (luaL_loadfile(hs_State, path))
	{
		Log::Error("Hook/Lua.Zone/hook.lua does not exist.");
		exit(0);
	}

	if (lua_pcallk(hs_State, 0, -1, 0, 0, nullptr) != LUA_OK)
	{
		Log::Error("An error occurred loading Hook/Lua.Zone/hook.lua");
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

int HookScript::cAddCommand(lua_State* L)
{
	auto result = 0;

	if (lua_type(L, 1))
	{
		auto cmd = lua_tostring(L, 1);
		auto adminLv = (uchar) lua_tonumber(L, 2);
		auto func = lua_tostring(L, 3);

		if (cmd)
		{
			Cmd c;
			c.Command = cmd;
			c.AdminLevel = adminLv;
			c.Func = func;

			Instance->Commands.push_back(c);
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

std::vector<std::string> tokenizer(const std::string& p_pcstStr, char delim)
{
	std::vector<std::string> tokens;
	std::stringstream   mySstream(p_pcstStr);
	std::string         temp;

	while (getline(mySstream, temp, delim)) {
		tokens.push_back(temp);
	}

	return tokens;
}

bool HookScript::RunCommand(ushort handle, uchar adminLevel, const std::string& msg)
{
	auto cmd = std::find_if(Commands.begin(), Commands.end(), [&](const Cmd& s)
	{
		return msg.find(s.Command) != std::string::npos;
	});
	
	if (cmd != Commands.end() && cmd->AdminLevel <= adminLevel)
	{
		auto cmdstr = *cmd;
		lua_getglobal(hs_State, cmdstr.Func);
		lua_pushnumber(hs_State, handle);

		auto split = tokenizer(msg, ' ');
		lua_pushnumber(hs_State, split.size() - 1);
		
		for (auto i = 1; i < split.size(); i++)
		{
			lua_pushstring(hs_State, split.at(i).c_str());
		}
		
		lua_pcall(hs_State, 2 + split.size() - 1, 0, 0);

		return true;
	}

	return false;
}
