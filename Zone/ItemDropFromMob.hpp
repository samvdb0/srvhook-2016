#pragma once
#include "pch.h"

#include "Globals.h"
#include "ShineMob.hpp"

#include "ZoneServer.hpp"

namespace ItemDropFromMob
{
	struct DropItemListInGroup
	{
		HOOK_PUB_M void dilig_Drop(ShineObjectClass::ShineObject* attacker, ShineObjectClass::ShineMob* victim, ShineMultiTypeHandle* LooterHandle, unsigned int lot_rate, char upgrade_min, char upgrade_max)
		{
			// safety check
			if (this == nullptr)
			{
				return;
			}
			
			CallMemberFunction<DropItemListInGroup, void, ShineObjectClass::ShineObject*, ShineObjectClass::ShineMob*, ShineMultiTypeHandle*, uint, char, char>(0x0048E260, this, attacker, victim, LooterHandle, lot_rate, upgrade_min, upgrade_max);
		}

		HOOK_PUB_M void dilig_StoreItem(const char* index, DropItemStruct::ItemGroup* ig)
		{
			CallMemberFunction<DropItemListInGroup, void, const char*, DropItemStruct::ItemGroup*>(0x0048E6B0, this, index, ig);
		}
		
		ORToken dilig_Index;
		struct __declspec(align(2))
		{
			unsigned __int16 itemid;
			DropItemStruct::ItemGroup itemgroup;
		} dilig_ItemList[100];
		int dilig_MaxItem;
	};

	struct DropGroupCluster
	{		
		HOOK_PUB_M DropItemListInGroup* FindNew(ORToken val)
		{
			auto f = std::find_if(dgc_GroupList.begin(), dgc_GroupList.end(), [val](const std::pair<ORToken, DropItemListInGroup>& i) { return EQUALS(i.first.ort_Name, val.ort_Name); });

			return f == dgc_GroupList.end() ? nullptr : &f->second;
		}
		
		std::map<ORToken, DropItemListInGroup> dgc_GroupList;
	};
	
	DEFINE_GLOBAL(DropGroupCluster, 0x0D55BC30, dropgroupcluster);
	
	class DropItemListForSpecies
	{
		HOOK_PUB_S void Install_DropSystem()
		{
			Detour(0x0048EB90, dilfs_Drop);
		}

		HOOK_PUB_S void dilfs_Drop(DropItemStruct::DropTable* droptable, ORToken* regengroup, ShineObjectClass::ShineObject* attacker, ShineObjectClass::ShineMob* victim, ShineMultiTypeHandle* LooterHandle, RateRecalc* raterecalc, unsigned int lot_rate)
		{
			Global::g_PerformanceRecorder.pr_Entrance("ItemDropFromMob::DropItemListForSpecies::dilfs_Drop");

			if (EQUALS(droptable->index.area, "-") || EQUALS(droptable->index.area, regengroup->ort_Name))
			{
				auto lvl = attacker->so_GetLevel();

				if (lvl >= droptable->index.minlev && lvl <= droptable->index.maxlev)
				{
					if (droptable->cen.rate > 0 && droptable->cen.maxcen > 0)
					{
						auto dropMoney = Global::g_cWell512Random.well512_GetRandom(droptable->cen.mincen, droptable->cen.maxcen);
						
						if (dropMoney)
						{
							DropMoneyWithRate(attacker, victim, droptable->cen.rate, dropMoney, raterecalc, LooterHandle);
						}
					}

					for (auto index = 0; index < 45; index++)
					{
						DropItemWithRate(&droptable->droptable[index], attacker, victim, raterecalc, LooterHandle, lot_rate);
					}
				}
			}
			
			Global::g_PerformanceRecorder.pr_Exit("ItemDropFromMob::DropItemListForSpecies::dilfs_Drop");
		}

		HOOK_PUB_S void DropMoneyWithRate(ShineObjectClass::ShineObject* attacker, ShineObjectClass::ShineMob* victim, int droprate, int amount, RateRecalc* rrcalc, ShineMultiTypeHandle* looterHandle)
		{
			Global::g_PerformanceRecorder.pr_Entrance("ItemDropFromMob::DropItemListForSpecies::DropMoneyWithRate");
			
			auto rnd = Global::g_cWell512Random.well512_GetRandom(1000000);

			if (Global::g_cWell512Random.well512_GetRandom(1000) < rrcalc->rr_ByLevel)
			{
				if (rnd < droprate * (rrcalc->rr_ByCharged + rrcalc->rr_FieldBonus + rrcalc->rr_ByAbstate) / 1000)
				{
					auto cen = Global::g_ItemDataBox.idb_SpecialItems()->sii_cenid;
					auto worldNo = Global::g_ZoneServer.zs_serverinfo.myserver.nWorldNo;
					auto zoneNo = Global::g_ZoneServer.zs_serverinfo.myserver.nZoneNo;

					auto item = new ItemTotalInformation();
					item->iti_mkregnum(cen, 3, zoneNo, worldNo);
					item->iti_itemstruct.itemid = cen;

					auto iac = Global::g_ItemAttributeClassContainer[cen];
					iac->iacc_default.iac_SetLot(&item->iti_itemstruct, amount);

					victim->IsDropping(
						item,
						ShineObjectClass::ONLY_REGISTNUMBER,
						looterHandle,
						attacker->so_handle.sohu_Handle,
						attacker->so_GetCharRegistNumber(),
						&iac->iacc_default,
						amount
					);
				}
			}

			Global::g_PerformanceRecorder.pr_Exit("ItemDropFromMob::DropItemListForSpecies::DropMoneyWithRate");
		}

		HOOK_PUB_S void DropItemWithRate(DropItemStruct::DropTable::Group* group, ShineObjectClass::ShineObject* attacker, ShineObjectClass::ShineMob* victim, RateRecalc* rrcalc, ShineMultiTypeHandle* looterHandle, uint lot_rate)
		{
			Global::g_PerformanceRecorder.pr_Entrance("ItemDropFromMob::DropItemListForSpecies::DropItemWithRate");

			if (Global::g_cWell512Random.well512_GetRandom(1000) < rrcalc->rr_ByLevel)
			{
				if (Global::g_cWell512Random.well512_GetRandom(1000000) < group->droprate * (rrcalc->rr_ByCharged + rrcalc->rr_FieldBonus + rrcalc->rr_ByAbstate) / 1000)
				{
					if (group->dropnumber)
					{
						if (group->dropnumber == 0xFFFF)
						{
							group->dropnumber -= 1;
						}

						//std::map<ORToken, DropItemListInGroup>::iterator act;
						//auto val = (*dropgroupcluster.Find(&act, &group->dropitemgroup))->second;
						//
						//val.dilig_Drop(attacker, victim, looterHandle, lot_rate, group->upgrademin, group->upgrademax);
						
						auto val = dropgroupcluster.FindNew(group->dropitemgroup);
						
						if (val != nullptr)
						{
							val->dilig_Drop(attacker, victim, looterHandle, lot_rate, group->upgrademin, group->upgrademax);
						}
					}
				}
			}

			Global::g_PerformanceRecorder.pr_Exit("ItemDropFromMob::DropItemListForSpecies::DropItemWithRate");
		}

		// HOOK_PUB_S void dilfs_DropByRate(int sub, DropItemStruct::DropTable* droptable, ShineObjectClass::ShineObject* attacker, ShineObjectClass::ShineMob* victim, RateRecalc* rrcalc, ShineMultiTypeHandle* LooterHandle, unsigned int lot_rate)
		// {
		// 	CallStaticFunction<0x0048E920, void, int, DropItemStruct::DropTable*, ShineObjectClass::ShineObject*, ShineObjectClass::ShineMob*, RateRecalc*, ShineMultiTypeHandle*, uint>(sub, droptable, attacker, victim, rrcalc, LooterHandle, lot_rate);
		// }
		
		HOOK_PROT_M DropItemStruct::DropTable* dilfs_List[100];
	};

	struct DropIndexCluster
	{
		OptionReader dic_Table;
		DropItemListForSpecies* dic_DropItemBySpecies;
	};
}