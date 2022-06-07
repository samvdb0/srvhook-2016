#pragma once
#include "ShineMobileObject.hpp"
#include "ShinePlayer.hpp"

unsigned short(__thiscall* so_mob_CanGathered_Org)(ShineObjectClass::ShineMob* mob, ShineObjectClass::ShinePlayer*, ushort*);

namespace ShineObjectClass
{
	class ShineMob : public ShineMobileObject
	{
		HOOK_PUB_S void Install_GatherRangeFix()
		{
			so_mob_CanGathered_Org = (unsigned short(__thiscall * )(ShineMob*, ShinePlayer*, ushort*))Detour(0x0046AF50, MF(so_mob_CanGatheredH));
		}

		HOOK_PUB_M unsigned short so_mob_CanGatheredH(ShinePlayer* ply, unsigned short* item)
		{
			if (so_DistanceSquar(ply) > 6 meters)
			{
				return 2818;
			}

			return so_mob_CanGathered_Org(this, ply, item);
		}

		char _size[0x2568 - 0x1EA8];
	};
}