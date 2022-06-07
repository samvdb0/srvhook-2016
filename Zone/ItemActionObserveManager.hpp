#pragma once
#include "pch.h"

#include "ShineObject.hpp"

class ItemActionObserveManager
{
    struct GroupCoolTime
    {
        TickTimer CoolTimer;
        unsigned int ActionGroupID;
        unsigned int ActionID;
        unsigned int LastCheckTime;
    };

	HOOK_PUB_S void Install_IAFix()
	{
		Detour(0x005D17F0, MF(AddAction));
		Detour(0x005D15E0, MF(DelAction));
	}

	bool AddAction(ShineObjectClass::ShineObject* owner, ushort ActionID, ushort ItemID)
	{
        auto observe = new ItemActionObserve();
        auto action = Global::g_ItemActions.find(ActionID)->second;

		if (action == nullptr)
		{
            return false;
		}

        observe->Attach(action, ActionID, ItemID);
		
        iaom_Observes.push_back(observe);
		return true;
	}

	bool DelAction(ShineObjectClass::ShineObject* owner, ushort ActionID, ushort ItemID)
	{
		ItemActionObserve* observe = nullptr;
		for (auto i = 0; i < iaom_Observes.size(); i++)
		{
			auto curr = iaom_Observes.at(i);

			if (curr->iao_ActionID == ActionID && curr->iao_itemid == ItemID)
			{
				observe = curr;
				break;
			}
		}
		
		if (observe == nullptr)
		{
			return false;
		}

		iaom_Observes.erase(remove(iaom_Observes.begin(), iaom_Observes.end(), observe));
		return true;
	}

    HOOK_PUB_M std::vector<ItemActionObserve*> iaom_Observes;
    HOOK_PUB_M std::vector<ItemActionObserveManager::GroupCoolTime> iaom_CoolTimeList;
    HOOK_PUB_M ShineObjectClass::ShineObject* iaom_pObject;
};
