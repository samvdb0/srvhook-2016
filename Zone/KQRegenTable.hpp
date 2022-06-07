#pragma once
#include "pch.h"

#include "Generic.h"
#include "Globals.h"

struct KQRegenTableElement
{
	Name3 tablename;
	OptionReader* reader;
};

std::map<std::string, KQRegenTableElement> Elements;

class KQRegenTable
{
public:

	static void Install_RegenTableLimit()
	{
		Detour(0x004B26B0, MF(kqrt_Load));
	}

	void kqrt_Load(const char* filename)
	{
		signed int v3; // eax
		char v4; // cl
		char buffer[256]; // [esp+10h] [ebp-190h]
		char path[128]; // [esp+110h] [ebp-90h]

		_splitpath(filename, nullptr, nullptr, buffer, nullptr);

		auto reader = new OptionReader();
		auto elem = KQRegenTableElement();

		sprintf(path, "../9Data/Shine/MobRegen/KingdomQuest/%s.txt", buffer);

		elem.reader = reader;

		if (!reader->or_Read(path))
		{
			sprintf(path, "../9Data/Shine/MobRegen/Instant/%s.txt", buffer);
			if (!reader->or_Read(path))
			{
				Global::g_ShineAssert.ac_AssertFail("KQRegenTable::kqrt_Load : Error found", path);
				Global::ShineExit("KQRegenTable::kqrt_Load");
			}
		}

		strncpy(elem.tablename.n3_name, buffer, 12);
		Elements[std::string(buffer)] = elem;
	}

	KQRegenTableElement kqrt_Array[50];
	int kqrt_Number;
};

class PineScriptMobRegenerator
{
public:
	struct RegenStruct
	{
		MobRegenStruct::RegenGroupStruct rs_group;
		MobRegenStruct::RegenMobStruct rs_data;
	};

	static void Install_RegenTableLimit()
	{
		Detour(0x004E7990, MF(psmr_Load));
	}

	bool psmr_Load(const char* map)
	{
		auto ret = false;
		Global::g_PerformanceRecorder.pr_Entrance("PineScriptMobRegenerator::psmr_Load");

		try
		{
			auto elem = Elements.at(map);

			auto i = 0; 
			char buffer[128]; 
			char buf[128];
			auto mobregen = ORToken::Create("MobRegen");
			auto mobregengroup = ORToken::Create("MobRegenGroup");
			while (true)
			{
				auto struc = (MobRegenStruct::RegenMobStruct*) elem.reader->or_SelectFromOrder(mobregen, i);
				if (!struc)
				{
					break;
				}

				if (psmr_btree[psmr_makeindex(buffer, map, struc->rms_groupname.ort_GetString(buf))] != 0xFFFFFFFF)
				{
					i++;
					continue;
				}

				auto struc2 = (MobRegenStruct::RegenGroupStruct*) elem.reader->or_SelectFrom(mobregengroup, "GroupIndex", buf, 0);
				if (struc2 != nullptr)
				{
					psmr_store(struc, struc2, buffer);
				}
				else
				{
					Global::g_ShineAssert.ac_AssertFail("PineScriptMobRegenerator::psmr_Load : Group name not found", buf);
				}

				i++;
			}

			ret = true;
		}
		catch (std::out_of_range& ex)
		{
			ret = false;
		}

		Global::g_PerformanceRecorder.pr_Exit("PineScriptMobRegenerator::psmr_Load");
		return ret;
	}

	char* psmr_makeindex(const char* buffer, const char* map, const char* index)
	{
		return CallMemberFunction<PineScriptMobRegenerator, char*, const char*, const char*, const char*>(0x004E7640, this, buffer, map, index);
	}

	void psmr_store(MobRegenStruct::RegenMobStruct* data, MobRegenStruct::RegenGroupStruct* rgs, const char* index)
	{
		return CallMemberFunction<PineScriptMobRegenerator, void, MobRegenStruct::RegenMobStruct*, MobRegenStruct::RegenGroupStruct*, const char*>(0x004E7790, this, data, rgs, index);
	}

private:
	PineScriptMobRegenerator::RegenStruct* psmr_struct;
	unsigned __int16 psmr_maxbuffer;
	unsigned __int16 psmr_curbuffer;
	BTree psmr_btree;
};