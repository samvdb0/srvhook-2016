#pragma once
#include "pch.h"

#include "Generic.h"
#include "NETCOMMAND.h"

namespace FunctionProfiler
{
	struct __declspec(align(8)) FunctionPerformance
	{
		HOOK_PROT_M unsigned __int64 fp_ExecuteNumber;
		HOOK_PROT_M unsigned __int64 fp_EntryCount;
		HOOK_PROT_M unsigned __int64 fp_AccumulateCount;
		HOOK_PROT_M char* fp_FunctionName;
	};

	class PerformanceRecorder
	{
		HOOK_PUB_M void pr_Entrance(const char* funcName)
		{
			CallMemberFunction<PerformanceRecorder, void, const char*>(0x004682D0, this, funcName);
		}
		
		HOOK_PUB_M void pr_Exit(const char* funcName)
		{
			CallMemberFunction<PerformanceRecorder, void, const char*>(0x00468360, this, funcName);
		}
		
		HOOK_PROT_M std::set<FunctionPerformance> pr_Array;
		HOOK_PROT_M __int16 pr_CheckLoopCount_Real;
		HOOK_PROT_M __int16 pr_CheckLoopCount_Command;
	};

	class FunctionCallingAnalyzer
	{
		HOOK_PUB_M BitANDInt fca_Pointer;
		HOOK_PUB_M NETCOMMAND fca_NetCommand[64];
		HOOK_PUB_M char* fca_stack[128];
		HOOK_PUB_M unsigned int fca_Flag[128];
		HOOK_PUB_M int fca_stackpoint;
	};
}
