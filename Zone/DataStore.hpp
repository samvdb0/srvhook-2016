#pragma once
#include "pch.h"

#include "FiestaUtilities.hpp"
#include "SHNFile.hpp"

struct Skill
{
	Skill(std::string name, ushort id)
	{
		IndexName = name;
		ID = id;
	}
	
	std::string IndexName;
	ushort ID;
};

struct LearnSkill
{
	LearnSkill(uchar req, ushort id)
	{
		ReqLevel = req;
		ID = id;
	}
	
	uchar ReqLevel;
	ushort ID;
};

struct AutoLearnSkill
{
	AutoLearnSkill(uchar classId, std::vector<LearnSkill> act, std::vector<LearnSkill> pas)
	{
		ClassID = classId;
		Actives = act;
		Passives = pas;
	}
	
	uchar ClassID;
	std::vector<LearnSkill> Actives;
	std::vector<LearnSkill> Passives;
};

struct ExpPercentageMob
{
	ExpPercentageMob(ushort mobId, ushort perc, uchar maxLevel)
	{
		MobID = mobId;
		Percentage = perc;
		MaxLevel = maxLevel;
	}
	
	ushort MobID;
	ushort Percentage;
	uchar MaxLevel;
};

struct AbStateView
{
	AbStateView(ushort id, std::string iconSort, uint typeSort)
	{
		ID = id;
		IconSort = std::move(iconSort);
		TypeSort = typeSort;
	}

	ushort ID;
	std::string IconSort;
	uint TypeSort;
};

struct PickupAnnounce
{
	PickupAnnounce(ushort id, std::string mapIndex)
	{
		ID = id;
		MapIndex = std::move(mapIndex);
	}

	ushort ID;
	std::string MapIndex;
};

struct HammerOfBijouUse
{
	HammerOfBijouUse(ushort itemId, ushort maxUses)
	{
		ItemID = itemId;
		MaxUses = maxUses;
	}

	ushort ItemID;
	ushort MaxUses;
};

struct AnimationTimer
{
	AnimationTimer(const char* skillName, ushort animTime)
	{
		SkillName = skillName;
		AnimationTime = animTime;
	}

	const char* SkillName;
	uint AnimationTime;
};

struct ItemCombine
{
	ItemCombine(const char* item1, const char* item2, std::string resultItem)
	{
		Item1 = item1;
		Item2 = item2;
		ResultItem = resultItem;
	}

	const char* Item1;
	const char* Item2;
	std::string ResultItem;
};

struct BlacklistedWord
{
	BlacklistedWord(std::string word)
	{
		Word = word;
	}

	std::string Word;
};

std::vector<Skill> ActiveSkills;
std::vector<Skill> PassiveSkills;
std::vector<ushort> ActiveExclude;
std::vector<ushort> PassiveExclude;

std::vector<PickupAnnounce> PickupAnnounces;

std::vector<HammerOfBijouUse> HammerOfBijouUses;

std::vector<AnimationTimer> AnimationTimers;
std::vector<ItemCombine> ItemCombines;

std::vector<BlacklistedWord> BlacklistedWords;

std::vector<ExpPercentageMob> ExpPercentageMobs;

std::vector<AbStateView> AbStateViews;

std::vector<AutoLearnSkill> SkillsToLearn;
std::vector<AutoLearnSkill> PassivesToLearn;

class DataStore
{
	HOOK_PUB_S bool Load()
	{
		auto shinePath = Config->Get("Path", "Shine", "9Data/Shine");
		auto hookPath = Config->Get("Path", "Hook", "9Data/Hook");

		auto itemInfo = new SHNFile();
		if (!itemInfo->Read(FORMAT_STR("..\\%s\\ItemInfo.shn", shinePath)))
		{
			Log::Info("Failed to read ItemInfo.shn");
			return false;
		}

		auto activeSkill = new SHNFile();
		if (!activeSkill->Read(FORMAT_STR("..\\%s\\ActiveSkill.shn", shinePath)))
		{
			Log::Info("Failed to read ActiveSkills.shn");
			return false;
		}

		auto passiveSkill = new SHNFile();
		if (!passiveSkill->Read(FORMAT_STR("..\\%s\\PassiveSkill.shn", shinePath)))
		{
			Log::Info("Failed to read PassiveSkills.shn");
			return false;
		}
		
		auto abstateView = new SHNFile();
		if (!abstateView->Read(FORMAT_STR("..\\%s\\View\\AbStateView.shn", shinePath)))
		{
			Log::Info("Failed to read AbStateView.shn");
			return false;
		}

		auto pickupAnnounce = new SHNFile();
		if (!pickupAnnounce->Read(FORMAT_STR("..\\%s\\PickupAnnounce.shn", hookPath)))
		{
			Log::Info("Failed to read PickupAnnounce.shn");
			return false;
		}

		auto hobUse = new SHNFile();
		if (!hobUse->Read(FORMAT_STR("..\\%s\\HammerOfBijouMaxUse.shn", hookPath)))
		{
			Log::Info("Failed to read HammerOfBijouMaxUse.shn");
			return false;
		}

		auto animTimer = new SHNFile();
		if (!animTimer->Read(FORMAT_STR("..\\%s\\AnimationTime.shn", hookPath)))
		{
			Log::Info("Failed to read AnimationTime.shn");
			return false;
		}

		// auto wordFilter = new SHNFile();
		// if (!wordFilter->Read(FORMAT_STR("..\\%s\\WordFilter.shn", hookPath)))
		// {
		// 	Log::Info("Failed to read AnimationTime.shn");
		// 	return false;
		// }

		// auto itemMixHook = new SHNFile();
		// if (!itemMixHook->Read(FORMAT_STR("..\\%s\\ItemCombine.shn", hookPath)))
		// {
		// 	Log::Info("Failed to read ItemCombine.shn");
		// 	return false;
		// }

		for (uint i = 0; i < pickupAnnounce->RowCount(); i++)
		{
			auto row = pickupAnnounce->Row(i);
			
			PickupAnnounces.emplace_back(PickupAnnounce(row->Get<ushort>(0), row->Get<std::string>(1)));
		}

		for (uint i = 0; i < hobUse->RowCount(); i++)
		{
			auto row = hobUse->Row(i);
			
			HammerOfBijouUses.emplace_back(HammerOfBijouUse(row->Get<ushort>(0), row->Get<ushort>(1)));
		}

		for (uint i = 0; i < animTimer->RowCount(); i++)
		{
			auto row = animTimer->Row(i);

			AnimationTimers.emplace_back(AnimationTimer(row->Get<char*>(0), row->Get<uint>(1)));
		}

		// for (uint i = 0; i < wordFilter->RowCount(); i++)
		// {
		// 	auto row = wordFilter->Row(i);
		// 
		// 	BlacklistedWords.emplace_back(BlacklistedWord(row->Get<char*>(0)));
		// }

		// for (uint i = 0; i < itemMixHook->RowCount(); i++)
		// {
		// 	auto row = itemMixHook->Row(i);
		// 
		// 	ItemCombines.emplace_back(ItemCombine(row->Get<char*>(0), row->Get<char*>(1), row->Get<std::string>(2)));
		// }

		for (uint i = 0; i < abstateView->RowCount(); i++)
		{
			auto abstateViewRow = abstateView->Row(i);

			auto id = abstateViewRow->Get<ushort>(0);
			auto iconSort = abstateViewRow->Get<std::string>(18);
			auto typeSort = abstateViewRow->Get<uint>(19);

			if (std::find_if(AbStateViews.begin(), AbStateViews.end(), [id](const AbStateView& s) { return s.ID == id; }) != AbStateViews.end())
			{
				continue;
			}

			AbStateViews.emplace_back(AbStateView(id, iconSort, typeSort));
		}

		#pragma region Mobexp percentages
		auto expPercentageMob = new SHNFile();
		if (!expPercentageMob->Read(FORMAT_STR("..\\%s\\ExpPercentageMob.shn", hookPath)))
		{
			Log::Info("Failed to read ExpPercentageMob.shn");
			return false;
		}

		for (uint i = 0; i < expPercentageMob->RowCount(); i++)
		{
			auto row = expPercentageMob->Row(i);
			auto id = row->Get<ushort>(0);
			auto perc = row->Get<ushort>(1);
			auto maxLvl = row->Get<uchar>(2);

			if (perc > 1000) { perc = 1000; }

			ExpPercentageMobs.emplace_back(ExpPercentageMob(id, perc, maxLvl));
		}
#pragma endregion

		#pragma region Automatic skill learning
		auto activeExclude = new SHNFile();
		if (!activeExclude->Read(FORMAT_STR("..\\%s\\AutoActiveExclude.shn", hookPath)))
		{
			Log::Info("Failed to read AutoActiveExclude.shn");
			return false;
		}

		auto passiveExclude = new SHNFile();
		if (!passiveExclude->Read(FORMAT_STR("..\\%s\\AutoPassiveExclude.shn", hookPath)))
		{
			Log::Info("Failed to read AutoPassiveExclude.shn");
			return false;
		}

		for (uint i = 0; i < activeSkill->RowCount(); i++)
		{
			auto skillRow = activeSkill->Row(i);
			auto skillId = skillRow->Get<ushort>(0);
			auto skillIndx = skillRow->Get<std::string>(1);

			if (std::find_if(ActiveSkills.begin(), ActiveSkills.end(), [skillIndx](const Skill& s) { return s.IndexName == skillIndx; }) != ActiveSkills.end())
			{
				continue;
			}

			ActiveSkills.emplace_back(Skill(skillIndx, skillId));
		}

		for (uint i = 0; i < activeExclude->RowCount(); i++)
		{
			auto skillRow = activeExclude->Row(i);
			auto skillId = skillRow->Get<ushort>(0);

			if (std::find_if(ActiveExclude.begin(), ActiveExclude.end(), [skillId](const ushort& s) { return s == skillId; }) != ActiveExclude.end())
			{
				continue;
			}

			ActiveExclude.emplace_back(skillId);
		}

		for (uint i = 0; i < passiveSkill->RowCount(); i++)
		{
			auto skillRow = passiveSkill->Row(i);
			auto skillId = skillRow->Get<ushort>(0);
			auto skillIndx = skillRow->Get<std::string>(1);

			if (std::find_if(PassiveSkills.begin(), PassiveSkills.end(), [skillIndx](const Skill& s) { return s.IndexName == skillIndx; }) != PassiveSkills.end())
			{
				continue;
			}

			PassiveSkills.emplace_back(Skill(skillIndx, skillId));
		}

		for (uint i = 0; i < passiveExclude->RowCount(); i++)
		{
			auto skillRow = passiveExclude->Row(i);
			auto skillId = skillRow->Get<ushort>(0);

			if (std::find_if(PassiveExclude.begin(), PassiveExclude.end(), [skillId](const ushort& s) { return s == skillId; }) != PassiveExclude.end())
			{
				continue;
			}

			PassiveExclude.emplace_back(skillId);
		}

		// Load skills to learn.
		for (uint i = 0; i < itemInfo->RowCount(); i++)
		{
			auto itemRow = itemInfo->Row(i);

			// Class = 11 (Learn Scroll)
			if (itemRow->Get<uchar>(4) == 11)
			{
				auto inxName = itemRow->Get<std::string>(1);
				auto demandLv = itemRow->Get<uchar>(11);
				auto useClass = (UseClassType)itemRow->Get<ushort>(31);
				auto isMultiClass = FiestaUtilities::IsMultiClass(useClass);
				auto classId = FiestaUtilities::ConvertToClass(useClass);

				auto as = std::find_if(ActiveSkills.begin(), ActiveSkills.end(), [inxName](const Skill& s) { return s.IndexName == inxName; });
				auto ps = std::find_if(PassiveSkills.begin(), PassiveSkills.end(), [inxName](const Skill& s) { return s.IndexName == inxName; });

				if (as != ActiveSkills.end())
				{
					try
					{
						if (std::find_if(SkillsToLearn.begin(), SkillsToLearn.end(), [classId](const AutoLearnSkill& s) { return s.ClassID == classId; }) == SkillsToLearn.end())
						{
							SkillsToLearn.emplace_back(AutoLearnSkill(classId, std::vector<LearnSkill>(), std::vector<LearnSkill>()));
						}

						auto entry = std::find_if(SkillsToLearn.begin(), SkillsToLearn.end(), [classId](const AutoLearnSkill& s) { return s.ClassID == classId; });
						auto upperEntry = std::find_if(SkillsToLearn.begin(), SkillsToLearn.end(), [classId](const AutoLearnSkill& s) { return s.ClassID == classId + 1; });
						auto shouldExclude = std::find_if(ActiveExclude.begin(), ActiveExclude.end(), [as](const ushort& s) { return s == as->ID; }) != ActiveExclude.end();

						if (!shouldExclude)
						{
							if (classId != 0)
							{
								entry->Actives.emplace_back(LearnSkill(demandLv, as->ID));
							}

							if (classId != 0 && isMultiClass)
							{
								upperEntry->Actives.emplace_back(LearnSkill(demandLv, as->ID));
							}
						}
					}
					catch (...)
					{
					}
				}
				else if (ps != PassiveSkills.end())
				{
					try
					{
						if (std::find_if(SkillsToLearn.begin(), SkillsToLearn.end(), [classId](const AutoLearnSkill& s) { return s.ClassID == classId; }) == SkillsToLearn.end())
						{
							SkillsToLearn.emplace_back(AutoLearnSkill(classId, std::vector<LearnSkill>(), std::vector<LearnSkill>()));
						}

						auto entry = std::find_if(SkillsToLearn.begin(), SkillsToLearn.end(), [classId](const AutoLearnSkill& s) { return s.ClassID == classId; });
						auto upperEntry = std::find_if(SkillsToLearn.begin(), SkillsToLearn.end(), [classId](const AutoLearnSkill& s) { return s.ClassID == classId + 1; });
						auto shouldExclude = std::find_if(PassiveExclude.begin(), PassiveExclude.end(), [ps](const ushort& s) { return s == ps->ID; }) != PassiveExclude.end();

						if (!shouldExclude)
						{
							if (classId != 0)
							{
								entry->Passives.emplace_back(LearnSkill(demandLv, ps->ID));
							}

							if (classId != 0 && isMultiClass)
							{
								upperEntry->Passives.emplace_back(LearnSkill(demandLv, ps->ID));
							}
						}
					}
					catch (...)
					{
					}
				}
			}
		}
#pragma endregion 

		return true;
	}

	static std::vector<LearnSkill> GetActives(uchar classId)
	{
		auto ret = std::find_if(SkillsToLearn.begin(), SkillsToLearn.end(), [classId](const AutoLearnSkill& s) { return s.ClassID == classId; });

		return ret != SkillsToLearn.end() ? ret->Actives : std::vector<LearnSkill>();
	}

	HOOK_PUB_S std::vector<LearnSkill> GetPassives(uchar classId)
	{
		auto ret = std::find_if(SkillsToLearn.begin(), SkillsToLearn.end(), [classId](const AutoLearnSkill& s) { return s.ClassID == classId; });

		return ret != SkillsToLearn.end() ? ret->Passives : std::vector<LearnSkill>();
	}

	HOOK_PUB_S ExpPercentageMob GetExpMob(ushort mobId)
	{
		auto ret = std::find_if(ExpPercentageMobs.begin(), ExpPercentageMobs.end(), [mobId](const ExpPercentageMob& s) { return s.MobID == mobId; });

		return ret != ExpPercentageMobs.end() ? *ret : ExpPercentageMob(0xFFFF, 0, 0);
	}

	HOOK_PUB_S AbStateView GetView(ushort abstateId)
	{
		auto ret = std::find_if(AbStateViews.begin(), AbStateViews.end(), [abstateId](const AbStateView& s) { return s.ID == abstateId; });

		return ret != AbStateViews.end() ? *ret : AbStateView(0xFFFF, "DEBUFF", 0);
	}

	HOOK_PUB_S bool ShouldAnnounce(ushort itemId, char* map)
	{
		auto ret = std::find_if(PickupAnnounces.begin(), PickupAnnounces.end(), [itemId, map](const PickupAnnounce& s) { return s.ID == itemId && !strcmp(map, s.MapIndex.c_str()); });

		return ret != PickupAnnounces.end() ? true : false;
	}

	HOOK_PUB_S ushort GetMaxHammerUseCount(ushort itemId)
	{
		auto ret = std::find_if(HammerOfBijouUses.begin(), HammerOfBijouUses.end(), [itemId](const HammerOfBijouUse& s) { return s.ItemID == itemId; });

		return ret != HammerOfBijouUses.end() ? ret->MaxUses : 0xFFFF;
	}

	HOOK_PUB_S uint GetAnimationTime(const char* skillName)
	{
		auto ret = std::find_if(AnimationTimers.begin(), AnimationTimers.end(), [skillName](const AnimationTimer& s) { return EQUALS(skillName, s.SkillName); });

		return ret != AnimationTimers.end() ? ret->AnimationTime : 0;
	}

	HOOK_PUB_S bool ContainsBlacklistedWord(const std::string& msg)
	{
		auto ret = std::find_if(BlacklistedWords.begin(), BlacklistedWords.end(), [&](const BlacklistedWord& s) { return msg.find(s.Word) != std::string::npos; });

		return ret != BlacklistedWords.end() ? true : false;
	}

	HOOK_PUB_S std::string* GetItemCombine(const char* item1, const char* item2)
	{
		auto ret = std::find_if(ItemCombines.begin(), ItemCombines.end(), [item1, item2](const ItemCombine& s)
		{
			return EQUALS(item1, s.Item1) && EQUALS(item2, s.Item2)
				|| EQUALS(item1, s.Item2) && EQUALS(item2, s.Item1);
		});

		return ret != ItemCombines.end() ? &ret->ResultItem : nullptr;
	}
};