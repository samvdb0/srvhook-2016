#pragma once
#include "pch.h"
#include "Generic.h"

struct TSTR
{
	struct SkillChange
	{
		unsigned __int16 sc_From;
		unsigned __int16 sc_To;
		unsigned int sc_Value;
		unsigned int sc_ASIndex;
	};


	struct SkillChangeList : List<SkillChange>
	{
		SkillChange scl_Array[100];
	};


	struct __declspec(align(4))	AttackElement4Mob
	{
		AttackElement4Mob()
		{
			CallMemberFunction<SkillChangeList, void>(0x004A8820, &ae4m_OutOfRangeBody);
			CallMemberFunction<SkillChangeList, void>(0x004A8820, &ae4m_HPLowBody);
			CallMemberFunction<SkillChangeList, void>(0x004A8820, &ae4m_TargetStateBody);
			CallMemberFunction<SkillChangeList, void>(0x004A8820, &ae4m_SaveNextSkillBody);
			CallMemberFunction<SkillChangeList, void>(0x004A8820, &ae4m_HPLow_ChangeOrderBody);

			ae4m_OutOfRange = nullptr;
			ae4m_HPLow = nullptr;
			ae4m_TargetState = nullptr;
			ae4m_SaveNextSkill = nullptr;
			ae4m_HPLow_ChangeOrder = nullptr;
		}

		~AttackElement4Mob()
		{
			CallMemberFunction<SkillChangeList, void>(0x004A8820, &ae4m_OutOfRangeBody);
			CallMemberFunction<SkillChangeList, void>(0x004A8820, &ae4m_HPLowBody);
			CallMemberFunction<SkillChangeList, void>(0x004A8820, &ae4m_TargetStateBody);
			CallMemberFunction<SkillChangeList, void>(0x004A8820, &ae4m_SaveNextSkillBody);
			CallMemberFunction<SkillChangeList, void>(0x004A8820, &ae4m_HPLow_ChangeOrderBody);
		}

		unsigned __int16 ae4m_BossMob;
		char ae4m_SequenceLength;
		unsigned __int16 ae4m_skillID[500];
		SkillChangeList ae4m_OutOfRangeBody;
		SkillChangeList ae4m_HPLowBody;
		SkillChangeList ae4m_TargetStateBody;
		SkillChangeList* ae4m_OutOfRange;
		SkillChangeList* ae4m_HPLow;
		SkillChangeList* ae4m_TargetState;
		SkillChangeList* ae4m_SaveNextSkill;
		SkillChangeList ae4m_SaveNextSkillBody;
		SkillChangeList ae4m_HPLow_ChangeOrderBody;
		SkillChangeList* ae4m_HPLow_ChangeOrder;
		char ae4m_StartIndex;
	};
};

std::map<ushort, TSTR::AttackElement4Mob*> MASList;

class MobAttackSequence
{
public:

	__declspec(noinline) static void Install()
	{
		Detour(0x0042C310, MF(mas_Find));
	}

	TSTR::AttackElement4Mob* mas_Find(ushort mobId)
	{
		auto result = MASList.find(mobId);
		if (result == MASList.end())
		{
			auto t = new TSTR::AttackElement4Mob();
			t->ae4m_BossMob = mobId;

			return t;
		}

		return result->second;
	}

private:
	int mas_MobNumber;
	char _size[0x79E04 - 0x4];
};