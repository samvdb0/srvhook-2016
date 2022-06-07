#pragma once
#include "pch.h"

#include <lua.hpp>
#pragma comment(lib, "lua52.lib")

struct Timer
{
	UINT64 RunTime;
	UINT64 RunTimeGap;
	const char* Func;
};

class HookScript
{
public:
	HookScript();

	void Load(const char* path);
	bool ExecuteFunction(const char* fn);
	void Main();

	static int cAddTimer(lua_State* L);
	static int cLog(lua_State* L);
	static int cSessionCount(lua_State*);
	static int cNotice(lua_State*);

	lua_State* hs_State;
	std::vector<Timer> Timers;

	static HookScript* Instance;
};