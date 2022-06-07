#pragma once
#include "pch.h"
#include "Generic.h"

void(__thiscall* AbstateListInObject_Ctor_Org)(class AbstateListInObject* pthis);
void* vftable = (void*)0x006A44F0;

class AbstateListInObject
{
public:
	void Ctor()
	{
		Container = new AbnormalStateContainer::AbstateElementInObject[128];
		
		asl_List = List<AbnormalStateContainer::AbstateElementInObject>();
		asl_List.vfptr = vftable;
		asl_List.l_MakeList(128);

		for (auto i = 0; i < asl_List.l_MaxSize; i++)
		{
			if (asl_List.l_Array[i].ls_Content == nullptr)
			{
				asl_List.l_Array[i].ls_Content = &Container[i];
			}
		}
	}

	void Dtor()
	{
		delete[] asl_List.l_Array;
		delete[] Container;
	}

	static void Install_AbstateLimitPerObject()
	{
		Detour(0x0040CF10, MF(Ctor));
		Detour(0x00406630, MF(Dtor));
	}
public:
	AbnormalStateContainer::AbstateElementInObject* Container;
	char _pad[0x74 - 0x4];
	AbnormalStateContainer::AbstateElementInObject asl_Element[27];
	List<AbnormalStateContainer::AbstateElementInObject> asl_List;
};