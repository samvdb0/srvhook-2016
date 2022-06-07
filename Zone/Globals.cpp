#pragma once
#include "pch.h"
#include "Globals.h"

DEFINE_GLOBAL(ShineCommonParameter, 0x0DA3FC18, Global::g_ShineParameter)
DEFINE_GLOBAL(LuaScriptFactor, 0x00870DD8, Global::g_LuaSecurity)
DEFINE_GLOBAL(LuaArgument, 0x14D6FCD8, Global::g_LuaArgument)
DEFINE_GLOBAL(FunctionProfiler::PerformanceRecorder, 0x0D026C10, Global::g_PerformanceRecorder)
DEFINE_GLOBAL(FunctionProfiler::FunctionCallingAnalyzer, 0x00754520, Global::g_FunctionCallAnalyzer)
DEFINE_GLOBAL(ItemActionsContainerMap, 0x14D6FC84, Global::g_ItemActions)
DEFINE_GLOBAL(cWell512Random, 0x150BA418, Global::g_cWell512Random)
DEFINE_GLOBAL(class ZoneServer, 0x14D45B70, Global::g_ZoneServer)
DEFINE_GLOBAL(ItemDataBox, 0x14D4FB90, Global::g_ItemDataBox)
DEFINE_GLOBAL(SkillDataBox, 0x13286828, Global::g_SkillDataBox)
DEFINE_GLOBAL(ItemAttributeClassContainer, 0x150BA478, Global::g_ItemAttributeClassContainer);
DEFINE_GLOBAL(ShineObjectManager, 0x132826B8, Global::g_ShineObjectManager);
DEFINE_GLOBAL(AbnormalStateDictionary::AbState, 0x0087AEA8, Global::g_AbStateDictionary);
DEFINE_GLOBAL(FieldOption, 0x0CFD2B88, Global::g_FieldOption);
DEFINE_GLOBAL(AssertClass, 0x00871B00, Global::g_ShineAssert);
DEFINE_GLOBAL(ClockWatch, 0x14D41A60, Global::g_ClockWatch);
DEFINE_GLOBAL(CSingleDataMap, 0x1328C040, Global::g_SingleData)

DEFINE_GLOBAL(BTree, 0x14D450A0, Global::mobnametree)
DEFINE_GLOBAL(BTree, 0x13286D08, Global::skillnametree);

DEFINE_GLOBAL(PROTOCOLFUNCTIONTEMPLETE, 0x00850E28, Global::shineprotofunc);

void __cdecl Global::ShineExit(const char* where)
{
	CallStaticFunction<0x0063C7C0, void, const char*>(where);
}