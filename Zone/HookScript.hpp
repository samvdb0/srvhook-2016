#pragma once
#include "pch.h"

struct Timer
{
	UINT64 RunTime;
	UINT64 RunTimeGap;
	const char* Func;
};

struct Cmd
{
	const char* Command;
	const char* Func;
	uchar AdminLevel;
};

struct funcsetstruct
{
	void* vfptr;
	lua_State* ls_LuaObject;
};

class HookScript
{
public:
	HookScript();

	void Load(const char* path);
	bool ExecuteFunction(const char* fn);
	void Main();

	static int cAddTimer(lua_State* L);
	static int cAddCommand(lua_State* L);
	static int cLog(lua_State* L);

	bool RunCommand(ushort handle, uchar adminLevel, const std::string& msg);

	lua_State* hs_State;
	std::vector<Timer> Timers;
	std::vector<Cmd> Commands;

	static HookScript* Instance;
};