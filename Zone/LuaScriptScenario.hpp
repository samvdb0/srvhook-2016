#pragma once
#include "pch.h"
#include "ShinePlayer.hpp"

#include "lua.hpp"
#pragma comment(lib, "lua52.lib")

bool(__thiscall* ls_FuncSet_Org)(class LuaScriptScenario* pthis);

class LuaScriptScenario
{
	HOOK_PUB_S void Install_LuaFuncs()
	{
		ls_FuncSet_Org = (bool(__thiscall *)(LuaScriptScenario*)) Detour(0x005F5350, MF(ls_FuncSet));
	}

	HOOK_PUB_M bool ls_FuncSet()
	{
		ls_FuncSet_Org(this);

		lua_register(ls_LuaObject, "cGetClass",			cGetClass);
		lua_register(ls_LuaObject, "cGetTarget",		cGetTarget);
		lua_register(ls_LuaObject, "cGiveMoney",		cGiveMoney);
		lua_register(ls_LuaObject, "cCheckCooldown",	cCheckCooldown);
		lua_register(ls_LuaObject, "cUnmount",			cUnmount);
		lua_register(ls_LuaObject, "cResetAbstateAll",	cResetAbstateAll);
		lua_register(ls_LuaObject, "cKickout",			cKickout);
		lua_register(ls_LuaObject, "cIsGather",			cIsGather);
		lua_register(ls_LuaObject, "cAddChargedEffect",	cAddChargedEffect);
		lua_register(ls_LuaObject, "cNoticeText",		cNoticeText);

		return true;
	}

	HOOK_PUB_S int cGetClass(lua_State* L)
	{
		Global::g_PerformanceRecorder.pr_Entrance("cGetClass");
		
		int result = 0;
		if (lua_type(L, 1))
		{
			auto v2 = lua_tonumberx(L, 1, 0);
			auto obj = Global::g_ShineObjectManager.GetObject(v2);

			if (obj && obj->IsCharacter())
			{
				lua_pushnumber(L, obj->so_GetClass());
				result = 1;
			}
		}

		Global::g_PerformanceRecorder.pr_Exit("cGetClass");
		return result;
	}

	HOOK_PUB_S int cGetTarget(lua_State* L)
	{
		int result = 0;

		Global::g_PerformanceRecorder.pr_Entrance("cGetTarget");

		if (lua_type(L, 1))
		{
			auto v2 = lua_tonumber(L, 1);
			auto obj = Global::g_ShineObjectManager.GetObject(v2);

			if (obj)
			{
				auto target = obj->so_GetTargetObject();

				if (target)
				{
					lua_pushnumber(L, target->so_handle.sohu_Handle);
				}
				else
				{
					lua_pushnumber(L, 0xFFFF);
				}

				result = 1;
			}
		}

		Global::g_PerformanceRecorder.pr_Exit("cGetTarget");
		return result;
	}

	HOOK_PUB_S int cGiveMoney(lua_State* L)
	{
		Global::g_PerformanceRecorder.pr_Entrance("cGiveMoney");
		auto result = 0;

		if (lua_type(L, 1))
		{
			auto v2 = lua_tonumber(L, 1);
			auto obj = Global::g_ShineObjectManager.GetObject(v2);

			if (obj && obj->IsCharacter())
			{
				auto amount = lua_tonumber(L, 2);

				if (amount)
				{
					while (amount > 0)
					{
						if (amount > INT_MAX)
						{
							obj->so_ply_PickupMoney(INT_MAX);
							amount -= INT_MAX;
						}
						else
						{
							obj->so_ply_PickupMoney(amount);
							amount = 0;
						}
					}

					result = 1;
				}
			}
		}

		Global::g_PerformanceRecorder.pr_Exit("cGiveMoney");
		return result;
	}

	HOOK_PUB_S int cCheckCooldown(lua_State* L)
	{
		int result = 0;

		Global::g_PerformanceRecorder.pr_Entrance("cCheckCooldown");

		if (lua_type(L, 1))
		{
			auto v2 = lua_tonumber(L, 1);
			auto obj = Global::g_ShineObjectManager.GetObject(v2);

			if (obj && obj->IsCharacter())
			{
				auto skillId = lua_tonumber(L, 2);

				if (skillId)
				{
					lua_pushboolean(L, ((ShineObjectClass::ShinePlayer*) obj)->IsSkillCooldown(skillId));

					result = 1;
				}
			}
		}

		Global::g_PerformanceRecorder.pr_Exit("cCheckCooldown");
		return result;
	}

	HOOK_PUB_S int cUnmount(lua_State* L)
	{
		int result = 0;

		Global::g_PerformanceRecorder.pr_Entrance("cUnmount");

		if (lua_type(L, 1))
		{
			auto v2 = lua_tonumber(L, 1);
			auto obj = Global::g_ShineObjectManager.GetObject(v2);

			if (obj && obj->IsCharacter())
			{
				auto mover = obj->so_MoverSystem_GetMover();

				if (mover)
				{
					obj->so_MoverSystem_GetOff(0);
				}

				result = 1;
			}
		}

		Global::g_PerformanceRecorder.pr_Exit("cUnmount");
		return result;
	}

	HOOK_PUB_S int cResetAbstateAll(lua_State* L)
	{
		int result = 0;

		Global::g_PerformanceRecorder.pr_Entrance("cResetAbstateAll");

		if (lua_type(L, 1))
		{
			auto v2 = lua_tonumber(L, 1);
			auto obj = Global::g_ShineObjectManager.GetObject(v2);

			if (obj && obj->IsCharacter())
			{
				for (auto i = 0; i < MAX_ABSTATEINDEX; i++)
				{
					obj->so_AbnormalState_Reset((ABSTATEINDEX)i);
				}

				result = 1;
			}
		}

		Global::g_PerformanceRecorder.pr_Exit("cResetAbstateAll");
		return result;
	}

	HOOK_PUB_S int cKickout(lua_State* L)
	{
		int result = 0;

		Global::g_PerformanceRecorder.pr_Entrance("cKickout");

		if (lua_type(L, 1))
		{
			auto v2 = lua_tonumber(L, 1);
			auto obj = Global::g_ShineObjectManager.GetObject(v2);

			if (obj && obj->IsCharacter())
			{
				obj->so_banning(ShineObjectClass::RemoveWhen::REMOVE_NOW);

				result = 1;
			}
		}

		Global::g_PerformanceRecorder.pr_Exit("cKickout");
		return result;
	}

	HOOK_PUB_S int cIsGather(lua_State* L)
	{
		int result = 0;

		Global::g_PerformanceRecorder.pr_Entrance("cIsGather");

		if (lua_type(L, 1))
		{
			auto v2 = lua_tonumber(L, 1);
			auto obj = Global::g_ShineObjectManager.GetObject(v2);

			if (obj && obj->IsCharacter())
			{
				lua_pushboolean(L, *(ushort*)((DWORD)obj + 0x2A308) != 0xFFFF);

				result = 1;
			}
		}

		Global::g_PerformanceRecorder.pr_Exit("cIsGather");
		return result;
	}

	HOOK_PUB_S int cAddChargedEffect(lua_State* L)
	{
		int result = 0;

		Global::g_PerformanceRecorder.pr_Entrance("cAddChargedEffect");

		if (lua_type(L, 1))
		{
			auto v2 = lua_tonumber(L, 1);
			auto obj = Global::g_ShineObjectManager.GetObject(v2);

			if (obj && obj->IsCharacter())
			{
				auto indx = lua_tostring(L, 2);

				if (indx)
				{
					auto item = Global::g_ItemDataBox.idb_2itemid(indx);

					if (item != 0xFFFF)
					{
						auto info = new ItemTotalInformation();
						info->iti_mkregnum(item, 3, Global::g_ZoneServer.zs_serverinfo.myserver.nWorldNo, Global::g_ZoneServer.zs_serverinfo.myserver.nZoneNo);
						info->iti_itemstruct.itemid = item;
						obj->so_ply_ChargedBuff(info);
						
						delete info;
						
						result = 1;
					}
				}
			}
		}

		Global::g_PerformanceRecorder.pr_Exit("cAddChargedEffect");
		return result;
	}

	HOOK_PUB_S int cRemoveChargedEffect(lua_State* L)
	{
		int result = 0;

		Global::g_PerformanceRecorder.pr_Entrance("cRemoveChargedEffect");

		if (lua_type(L, 1))
		{
			auto v2 = lua_tonumber(L, 1);
			auto obj = Global::g_ShineObjectManager.GetObject(v2);

			if (obj && obj->IsCharacter())
			{
				auto indx = lua_tostring(L, 2);

				if (indx)
				{
					auto itemId = Global::g_ItemDataBox.idb_2itemid(indx);
					if (itemId != 0xFFFF)
					{
						auto item = Global::g_ItemDataBox[itemId];
						if (item)
						{
						}
					}
				}
			}
		}

		Global::g_PerformanceRecorder.pr_Exit("cRemoveChargedEffect");
		return result;
	}

	HOOK_PUB_S int cNoticeText(lua_State* L)
	{
		int result = 0;

		Global::g_PerformanceRecorder.pr_Entrance("cNoticeText");

		if (lua_type(L, 1))
		{
			auto v2 = lua_tonumber(L, 1);
			auto obj = Global::g_ShineObjectManager.GetObject(v2);

			if (obj && obj->IsCharacter())
			{
				auto v3 = lua_tostring(L, 2);
				
				obj->so_ply_Notice(v3);

				result = 1;
			}
		}

		Global::g_PerformanceRecorder.pr_Exit("cNoticeText");
		return result;
	}

	HOOK_PROT_M void* vt;
	HOOK_PROT_M lua_State* ls_LuaObject;
};
