#pragma once
#include "pch.h"
#include <iterator>
#include "AmpersandCommand.hpp"
#include "DataStore.hpp"
#include "ShinePlayer.hpp"

#define COPY(from, to) { if (!(from).empty()) { std::copy(std::begin(from), std::end(from), std::back_inserter(to)); } }

class Events
{
	HOOK_PUB_S void OnLevelUp(ShineObjectClass::ShinePlayer* player, uchar level)
	{		
		#pragma region Automatic skill learning
		auto plyClass = player->so_GetClass();
		std::vector<LearnSkill> activeSkills;
		std::vector<LearnSkill> passiveSkills;

		switch (plyClass)
		{
		case 1:
		{
			auto a1 = DataStore::GetActives(1);
			auto p1 = DataStore::GetPassives(1);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
		}
		break;
		case 2:
		{
			auto a1 = DataStore::GetActives(1);
			auto p1 = DataStore::GetPassives(1);
			auto a2 = DataStore::GetActives(2);
			auto p2 = DataStore::GetPassives(2);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
		}
		break;
		case 3:
		{
			auto a1 = DataStore::GetActives(1);
			auto p1 = DataStore::GetPassives(1);
			auto a2 = DataStore::GetActives(2);
			auto p2 = DataStore::GetPassives(2);
			auto a3 = DataStore::GetActives(3);
			auto p3 = DataStore::GetPassives(3);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
		}
		break;
		case 4:
		{
			auto a1 = DataStore::GetActives(1);
			auto p1 = DataStore::GetPassives(1);
			auto a2 = DataStore::GetActives(2);
			auto p2 = DataStore::GetPassives(2);
			auto a3 = DataStore::GetActives(3);
			auto p3 = DataStore::GetPassives(3);
			auto a4 = DataStore::GetActives(4);
			auto p4 = DataStore::GetPassives(4);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
			COPY(a4, activeSkills);
			COPY(p4, passiveSkills);
		}
		break;
		case 5:
		{
			auto a1 = DataStore::GetActives(1);
			auto p1 = DataStore::GetPassives(1);
			auto a2 = DataStore::GetActives(2);
			auto p2 = DataStore::GetPassives(2);
			auto a3 = DataStore::GetActives(3);
			auto p3 = DataStore::GetPassives(3);
			auto a5 = DataStore::GetActives(5);
			auto p5 = DataStore::GetPassives(5);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
			COPY(a5, activeSkills);
			COPY(p5, passiveSkills);
		}
		break;
		case 6:
		{
			auto a1 = DataStore::GetActives(6);
			auto p1 = DataStore::GetPassives(6);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
		}
		break;
		case 7:
		{
			auto a1 = DataStore::GetActives(6);
			auto p1 = DataStore::GetPassives(6);
			auto a2 = DataStore::GetActives(7);
			auto p2 = DataStore::GetPassives(7);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
		}
		break;
		case 8:
		{
			auto a1 = DataStore::GetActives(6);
			auto p1 = DataStore::GetPassives(6);
			auto a2 = DataStore::GetActives(7);
			auto p2 = DataStore::GetPassives(7);
			auto a3 = DataStore::GetActives(8);
			auto p3 = DataStore::GetPassives(8);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
		}
		break;
		case 9:
		{
			auto a1 = DataStore::GetActives(6);
			auto p1 = DataStore::GetPassives(6);
			auto a2 = DataStore::GetActives(7);
			auto p2 = DataStore::GetPassives(7);
			auto a3 = DataStore::GetActives(8);
			auto p3 = DataStore::GetPassives(8);
			auto a4 = DataStore::GetActives(9);
			auto p4 = DataStore::GetPassives(9);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
			COPY(a4, activeSkills);
			COPY(p4, passiveSkills);
		}
		break;
		case 10:
		{
			auto a1 = DataStore::GetActives(6);
			auto p1 = DataStore::GetPassives(6);
			auto a2 = DataStore::GetActives(7);
			auto p2 = DataStore::GetPassives(7);
			auto a3 = DataStore::GetActives(8);
			auto p3 = DataStore::GetPassives(8);
			auto a4 = DataStore::GetActives(10);
			auto p4 = DataStore::GetPassives(10);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
			COPY(a4, activeSkills);
			COPY(p4, passiveSkills);
		}
		break;
		case 11:
		{
			auto a1 = DataStore::GetActives(11);
			auto p1 = DataStore::GetPassives(11);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
		}
		break;
		case 12:
		{
			auto a1 = DataStore::GetActives(11);
			auto p1 = DataStore::GetPassives(11);
			auto a2 = DataStore::GetActives(12);
			auto p2 = DataStore::GetPassives(12);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
		}
		break;
		case 13:
		{
			auto a1 = DataStore::GetActives(11);
			auto p1 = DataStore::GetPassives(11);
			auto a2 = DataStore::GetActives(12);
			auto p2 = DataStore::GetPassives(12);
			auto a3 = DataStore::GetActives(13);
			auto p3 = DataStore::GetPassives(13);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
		}
		break;
		case 14:
		{
			auto a1 = DataStore::GetActives(11);
			auto p1 = DataStore::GetPassives(11);
			auto a2 = DataStore::GetActives(12);
			auto p2 = DataStore::GetPassives(12);
			auto a3 = DataStore::GetActives(13);
			auto p3 = DataStore::GetPassives(13);
			auto a4 = DataStore::GetActives(14);
			auto p4 = DataStore::GetPassives(14);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
			COPY(a4, activeSkills);
			COPY(p4, passiveSkills);
		}
		break;
		case 15:
		{
			auto a1 = DataStore::GetActives(11);
			auto p1 = DataStore::GetPassives(11);
			auto a2 = DataStore::GetActives(12);
			auto p2 = DataStore::GetPassives(12);
			auto a3 = DataStore::GetActives(13);
			auto p3 = DataStore::GetPassives(13);
			auto a4 = DataStore::GetActives(15);
			auto p4 = DataStore::GetPassives(15);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
			COPY(a4, activeSkills);
			COPY(p4, passiveSkills);
		}
		break;
		case 16:
		{
			auto a1 = DataStore::GetActives(16);
			auto p1 = DataStore::GetPassives(16);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
		}
		break;
		case 17:
		{
			auto a1 = DataStore::GetActives(16);
			auto p1 = DataStore::GetPassives(16);
			auto a2 = DataStore::GetActives(17);
			auto p2 = DataStore::GetPassives(17);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
		}
		break;
		case 18:
		{
			auto a1 = DataStore::GetActives(16);
			auto p1 = DataStore::GetPassives(16);
			auto a2 = DataStore::GetActives(17);
			auto p2 = DataStore::GetPassives(17);
			auto a3 = DataStore::GetActives(18);
			auto p3 = DataStore::GetPassives(18);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
		}
		break;
		case 19:
		{
			auto a1 = DataStore::GetActives(16);
			auto p1 = DataStore::GetPassives(16);
			auto a2 = DataStore::GetActives(17);
			auto p2 = DataStore::GetPassives(17);
			auto a3 = DataStore::GetActives(18);
			auto p3 = DataStore::GetPassives(18);
			auto a4 = DataStore::GetActives(19);
			auto p4 = DataStore::GetPassives(19);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
			COPY(a4, activeSkills);
			COPY(p4, passiveSkills);
		}
		break;
		case 20:
		{
			auto a1 = DataStore::GetActives(16);
			auto p1 = DataStore::GetPassives(16);
			auto a2 = DataStore::GetActives(17);
			auto p2 = DataStore::GetPassives(17);
			auto a3 = DataStore::GetActives(18);
			auto p3 = DataStore::GetPassives(18);
			auto a4 = DataStore::GetActives(20);
			auto p4 = DataStore::GetPassives(20);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
			COPY(a4, activeSkills);
			COPY(p4, passiveSkills);
		}
		break;
		case 21:
		{
			auto a1 = DataStore::GetActives(21);
			auto p1 = DataStore::GetPassives(21);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
		}
		break;
		case 22:
		{
			auto a1 = DataStore::GetActives(21);
			auto p1 = DataStore::GetPassives(21);
			auto a2 = DataStore::GetActives(22);
			auto p2 = DataStore::GetPassives(22);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
		}
		break;
		case 23:
		{
			auto a1 = DataStore::GetActives(21);
			auto p1 = DataStore::GetPassives(21);
			auto a2 = DataStore::GetActives(22);
			auto p2 = DataStore::GetPassives(22);
			auto a3 = DataStore::GetActives(23);
			auto p3 = DataStore::GetPassives(23);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
		}
		break;
		case 24:
		{
			auto a1 = DataStore::GetActives(21);
			auto p1 = DataStore::GetPassives(21);
			auto a2 = DataStore::GetActives(22);
			auto p2 = DataStore::GetPassives(22);
			auto a3 = DataStore::GetActives(23);
			auto p3 = DataStore::GetPassives(23);
			auto a4 = DataStore::GetActives(24);
			auto p4 = DataStore::GetPassives(24);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
			COPY(a4, activeSkills);
			COPY(p4, passiveSkills);
		}
		break;
		case 25:
		{
			auto a1 = DataStore::GetActives(21);
			auto p1 = DataStore::GetPassives(21);
			auto a2 = DataStore::GetActives(22);
			auto p2 = DataStore::GetPassives(22);
			auto a3 = DataStore::GetActives(23);
			auto p3 = DataStore::GetPassives(23);
			auto a4 = DataStore::GetActives(25);
			auto p4 = DataStore::GetPassives(25);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
			COPY(a3, activeSkills);
			COPY(p3, passiveSkills);
			COPY(a4, activeSkills);
			COPY(p4, passiveSkills);
		}
		break;
		case 26:
		{
			auto a1 = DataStore::GetActives(26);
			auto p1 = DataStore::GetPassives(26);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
		}
		break;
		case 27:
		{
			auto a1 = DataStore::GetActives(26);
			auto p1 = DataStore::GetPassives(26);
			auto a2 = DataStore::GetActives(27);
			auto p2 = DataStore::GetPassives(27);

			COPY(a1, activeSkills);
			COPY(p1, passiveSkills);
			COPY(a2, activeSkills);
			COPY(p2, passiveSkills);
		}
		break;
		default:
			break;
		}

		for (auto i = 0; i < activeSkills.size(); i++)
		{
			auto skill = activeSkills[i];
			
			if (level >= skill.ReqLevel && !player->HasActiveSkill(skill.ID))
			{
				AmpersandCommand::LearnSkill(player, skill.ID);
			}
		}

		for (auto i = 0; i < passiveSkills.size(); i++)
		{
			auto skill = passiveSkills[i];

			if (level >= skill.ReqLevel && !player->HasPassiveSkill(skill.ID))
			{
				AmpersandCommand::LearnPassive(player, skill.ID);
			}
		}

		activeSkills.clear();
		passiveSkills.clear();
#pragma endregion
	}
};
