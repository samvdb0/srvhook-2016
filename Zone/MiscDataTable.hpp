#pragma once
#include "pch.h"

#include "Globals.h"
#include "Generic.h"

class MiscDataTableN
{
	static void InstallNewMiscData()
	{
		Detour(0x004A82D0, MF(mdt_Load));
	}

	void mdt_Load()
	{
		OptionReader r = OptionReader();

		if (!r.or_Read("../9Data/Shine/World/MiscDataTable.txt"))
		{
			Global::g_ShineAssert.ac_AssertFail("Error in read MiscDataTable.txt", r.or_ErrorLine());
			Global::ShineExit("MiscDataTable::mdt_Load");
		}

		mdt_SkillDataSize = 0;
		mdt_AbStateDataSize = 0;
		mdt_VarifAbstateSize = 0;

		mdt_SkillBreedMob(&r);
	}

	void mdt_SkillBreedMob(OptionReader* miscdata)
	{
		uint k = 0;
		auto token = ORToken::Create("SkillBreedMob");

		while (true)
		{
			auto currRow = (SkillBreedMobRow*) miscdata->or_SelectFromOrder(token, k);

			if (!currRow)
			{
				break;
			}

			if (currRow->Serial != currRow->CheckSum)
			{
				Global::g_ShineAssert.ac_AssertFail("MiscDataTable::mdt_SkillBreedMob : SkillBreedMob : Checksum", currRow->Serial);
				Global::ShineExit("MiscDataTable::mdt_SkillBreedMob");
			}

			auto num = Global::mobnametree[currRow->MobIndex];
			if (num == -1)
			{
				Global::g_ShineAssert.ac_AssertFail("MiscDataTable::mdt_SkillBreedMob : Imvalid mob name", currRow->MobIndex);
				Global::ShineExit("MiscDataTable::mdt_SkillBreedMob");
			}

			auto v7 = MiscDataTable::MiscData_Skill();
			v7.mds_BreedMob = num;
			v7.mds_SummonNumber = currRow->SummonNum;
		}
	}

	MiscDataTable::MiscData_Skill* mdt_SkillBufferAlloc(const char* index)
	{


		return nullptr;
	}

	struct __declspec(align(1)) SkillBreedMobRow
	{
		char Serial;
		char Skill[33];
		char MobIndex[33];
		char SummonNum;
		ORToken AI;
		ORToken RegenLoc;
		ushort RegenDistance;
		ORToken MobRoam;
		uint LifeTime;
		char AbState[33];
		ORToken TriggerObject;
		uint TriggerRange;
		ushort Delay;
		ushort ExplNo;
		char Explosion[33];
		ORToken ExplosionWhere;
		ORToken Debuff;
		ORToken MultiTarget;
		char CheckSum;
	};

private:
	std::vector<MiscDataTable::MiscData_Skill> mdt_SkillDataArray;
	int mdt_SkillDataSize;
	std::vector<MiscDataTable::MiscData_AbState> mdt_AbStateDataArray;
	int mdt_AbStateDataSize;
	std::vector<MiscDataTable::MiscData_VarifyByAbstate> mdt_VarifAbstateArray;
	int mdt_VarifAbstateSize;
};