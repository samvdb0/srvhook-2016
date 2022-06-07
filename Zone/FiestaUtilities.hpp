#pragma once
#include "Generic.h"

struct FiestaUtilities
{
	static uchar ConvertToClass(UseClassType type)
	{
		switch (type)
		{
		case UCT_FIGHTER_ALL:
			return 1;
		case UCT_CLEVERFIGHTER_AND_OVER:
			return 2;
		case UCT_WARRIOR_AND_OVER:
			return 3;
		case UCT_WARRIOR_OVER:
		case UCT_GLADIATOR_ONLY:
			return 4;
		case UCT_KNIGHT_ONLY:
			return 5;
		case UCT_CLERIC_ALL:
			return 6;
		case UCT_HIGHCLERIC_AND_OVER:
			return 7;
		case UCT_PALADIN_AND_OVER:
			return 8;
		case UCT_PALADIN_OVER:
		case UCT_HOLYKNIGHT_ONLY:
			return 9;
		case UCT_GUARDIAN_ONLY:
			return 10;
		case UCT_ARCHER_ALL:
			return 11;
		case UCT_HAWKARCHER_AND_OVER:
			return 12;
		case UCT_SCOUT_AND_OVER:
			return 13;
		case UCT_SCOUT_OVER:
		case UCT_SHARPSHOOTER_ONLY:
			return 14;
		case UCT_RANGER_ONLY:
			return 15;
		case UCT_MAGE_ALL:
			return 16;
		case UCT_WIZMAGE_AND_OVER:
			return 17;
		case UCT_ENCHANTER_AND_OVER:
			return 18;
		case UCT_ENCHANTER_OVER:
		case UCT_WARLOCK_ONLY:
			return 19;
		case UCT_WIZARD_ONLY:
			return 20;
		case UCT_JOKER_ALL:
			return 21;
		case UCT_CHASER_AND_OVER:
			return 22;
		case UCT_CRUEL_AND_OVER:
			return 23;
		case UCT_CRUEL_OVER:
		case UCT_CLOSER_ONLY:
			return 24;
		case UCT_ASSASSIN_ONLY:
			return 25;
		case UCT_SENTINEL_ALL:
			return 26;
		case UCT_SAVIOR_ONLY:
			return 27;
		default:
			return 0;
		}
	}

	static bool IsMultiClass(UseClassType type)
	{
		switch (type)
		{
		case UCT_WARRIOR_OVER:
		case UCT_PALADIN_OVER:
		case UCT_SCOUT_OVER:
		case UCT_ENCHANTER_OVER:
		case UCT_CRUEL_OVER:
			return true;
		default:
			return false;
		}
	}

	static DWORD GetTime()
	{
		return CallStaticFunction<0x00650700, DWORD>();
	}
};
