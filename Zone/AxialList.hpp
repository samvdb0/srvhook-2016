#pragma once
#include "pch.h"

namespace ShineObjectClass {
	class ShineObject;
}

struct AxialListIterator
{
	virtual char ali_Work(ShineObjectClass::ShineObject*, ShineObjectClass::ShineObject*, unsigned int) { return 1; }
};

class AxialListWall : public AxialListIterator
{
	HOOK_PUB_M AxialListWall(const char* msg)
	{
		((void(__thiscall*)(AxialListWall*, const char*))0x004281A0)(this, msg);
	}
	
	const char* alw_message;
};