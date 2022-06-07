#pragma once
#include "pch.h"
#include "Generic.h"

class ItemMixData
{
public:
	static void Install_MixOverride()
	{
		Detour(0x00635820, MF(GetMixItemIndex));
	}

	std::string* GetMixItemIndex(ItemDataBox::ItemDataBoxIndex* left, ItemDataBox::ItemDataBoxIndex* right)
	{
		if (!left || !right)
		{
			return nullptr;
		}

		auto index = DataStore::GetItemCombine(left->data->InxName, right->data->InxName);

		return index;
	}
};