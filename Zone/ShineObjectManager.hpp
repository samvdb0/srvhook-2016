#pragma once
#include "pch.h"
#undef GetObject

class ShineObjectManager
{
	HOOK_PUB_M ShineObjectClass::ShineObject* GetObject(ushort handle)
	{
		return CallMemberFunction<ShineObjectManager, ShineObjectClass::ShineObject*, ushort>(0x0054FD10, this, handle);
	}

	HOOK_PUB_M ShineObjectClass::ShinePlayer* FindPlayer(Name5* chrid)
	{
		return CallMemberFunction<ShineObjectManager, ShineObjectClass::ShinePlayer*, Name5*>(0x00550430, this, chrid);
	}
	
	HOOK_PRIV_M char _size[0x220];
};