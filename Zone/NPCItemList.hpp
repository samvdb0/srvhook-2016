#pragma once
#include "pch.h"

#include "Generic.h"
#include "Globals.h"

struct PROTO_NC_MENU_SHOPOPENTABLE_CMD
{
	struct __declspec(align(1)) MENUITEM
	{
		char slot;
		unsigned __int16 item;
	};

	PROTO_NC_MENU_SHOPOPENTABLE_CMD()
	{
		itemnum = 0;
		npc = 0xFFFF;
	}

	unsigned __int16 itemnum;
	unsigned __int16 npc;
	PROTO_NC_MENU_SHOPOPENTABLE_CMD::MENUITEM itemlist[1000];
};

std::map<const char*, PROTO_NC_MENU_SHOPOPENTABLE_CMD*> ShopByIndex;

namespace NPCItemList
{
	class ItemListOption : public OptionReader
	{
	public:
		ItemListOption() : OptionReader()
		{
			ilo_TempBuffer = new PROTO_NC_MENU_SHOPOPENTABLE_CMD();
		}

		~ItemListOption()
		{
			delete ilo_TempBuffer;
		}

		PROTO_NC_MENU_SHOPOPENTABLE_CMD* ilo_PacketMake(const char* mobindex)
		{
			return CallMemberFunction<ItemListOption, PROTO_NC_MENU_SHOPOPENTABLE_CMD*, const char*>(0x004C4DE0, this, mobindex);
		}

	public:
		PROTO_NC_MENU_SHOPOPENTABLE_CMD* ilo_TempBuffer;
	};

	class NPCItemListTable
	{
	public:
		static void Install_MerchantLimit()
		{
			Detour(0x004C5050, MF(nilt_MenuPacket));
			Detour(0x004C5130, MF(nilt_ReadTable));
		}

		void nilt_ReadTable(const char* mobindex)
		{
			char path[MAX_PATH];
			sprintf(path, "../9Data/Shine/NPCItemList/%s.txt", mobindex);

			auto itemListOption = new ItemListOption();

			if (itemListOption->or_Read(path))
			{
				auto p = itemListOption->ilo_PacketMake(mobindex);
				ShopByIndex[mobindex] = p;

				if (ShopByIndex[mobindex] == nullptr)
				{
					Global::g_ShineAssert.ac_AssertFail("NPCItemList::NPCItemListTable::nilt_ReadTable : Packet make err", ShopByIndex.size());
				}
			}
			else
			{
				Global::g_ShineAssert.ac_AssertFail("NPCItemList::NPCItemListTable::nilt_ReadTable : Read error", path);
				Global::g_ShineAssert.ac_AssertFail(itemListOption->or_ErrorString(), itemListOption->or_ErrorLine());
			}

			delete itemListOption;
		}

		PROTO_NC_MENU_SHOPOPENTABLE_CMD* nilt_MenuPacket(const char* mobindex)
		{
			PROTO_NC_MENU_SHOPOPENTABLE_CMD* ret;
			Global::g_PerformanceRecorder.pr_Entrance("NPCItemList::NPCItemListTable::nilt_MenuPacket");

			try
			{
				ret = ShopByIndex.at(mobindex);
			}
			catch (std::out_of_range& ex)
			{
				ret = nullptr;
			}

			Global::g_PerformanceRecorder.pr_Exit("NPCItemList::NPCItemListTable::nilt_MenuPacket");
			return ret;
		}
	};
};