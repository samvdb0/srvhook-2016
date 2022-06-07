#pragma once
#include "ShineCommonParameter.hpp"
#include "FunctionProfiler.hpp"
#include "cWell512Random.hpp"
#include "ShineObjectManager.hpp"

struct PROTOCOLFUNCTIONTEMPLETE;
typedef std::map<ushort, Action*> ItemActionsContainerMap;

class Global
{
public:
	static ShineCommonParameter& g_ShineParameter;
	static LuaScriptFactor& g_LuaSecurity;
	static LuaArgument& g_LuaArgument;
	static FunctionProfiler::PerformanceRecorder& g_PerformanceRecorder;
	static FunctionProfiler::FunctionCallingAnalyzer& g_FunctionCallAnalyzer;
	static ItemActionsContainerMap& g_ItemActions;
	static cWell512Random& g_cWell512Random;
	static class ZoneServer& g_ZoneServer;
	static ItemDataBox& g_ItemDataBox;
	static SkillDataBox& g_SkillDataBox;
	static ItemAttributeClassContainer& g_ItemAttributeClassContainer;
	static ShineObjectManager& g_ShineObjectManager;
	static AbnormalStateDictionary::AbState& g_AbStateDictionary;
	static FieldOption& g_FieldOption;
	static AssertClass& g_ShineAssert;
	static ClockWatch& g_ClockWatch;
	static CSingleDataMap& g_SingleData;

	static BTree& mobnametree;
	static BTree& skillnametree;

	static PROTOCOLFUNCTIONTEMPLETE& shineprotofunc;

	static void __cdecl ShineExit(const char* where);
};