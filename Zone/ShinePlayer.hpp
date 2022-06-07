#pragma once
#include <cmath>

#include "DataStore.hpp"
#include "Globals.h"
#include "ShineMobileObject.hpp"
#include "PROTOCOLSTORE.h"

#include "HookScript.hpp"

typedef void(__thiscall* PACKET_HANDLE)(ShineObjectClass::ShinePlayer*, NETCOMMAND*, int, ushort);
void(__thiscall* so_Unmark_Org)(ShineObjectClass::ShinePlayer*, ShineObjectClass::RemoveWhen when, char logoutpacket, char SaveType);
void(__thiscall* sp_GatherComplete_Org) (ShineObjectClass::ShinePlayer* pthis, UINT32 lot_rate);
ushort(__thiscall* EraseGoodBuff_Org) (ShineObjectClass::ShinePlayer* pthis, ABSTATEINDEX index, ushort notfinderrortype);
void(__thiscall* so_GetExperienceFromMob_Org)(ShineObjectClass::ShinePlayer* pthis, int expgain, ushort mobid, ushort mobhandle);
bool(__thiscall* so_ply_PickupItem_Org)(ShineObjectClass::ShinePlayer* pthis, ShineObjectClass::ShineObject* itemobj, ItemTotalInformation* itemonfield, unsigned __int16 itemhandle);
void(__thiscall* so_ply_PickupMoney_Org)(ShineObjectClass::ShinePlayer* pthis, unsigned int money);
void(__thiscall* sp_ChestBoxOpen_Org)(ShineObjectClass::ShinePlayer* pthis, int slot, ItemTotalInformation* itm);
void(__thiscall* sp_KQReward_Org)(ShineObjectClass::ShinePlayer* pthis, void* rewardstr);
void(__thiscall* so_mobile_Teleport_Org)(ShineObjectClass::ShinePlayer* pthis, SHINE_XY_TYPE* location);
bool(__thiscall* sp_AmpersandCommand_Org)(ShineObjectClass::ShinePlayer* pthis, ushort handle, PROTO_NC_ACT_CHAT_REQ* chat);

bool(__thiscall* sp_MysteryVaultMakeItem_Org)(ShineObjectClass::ShinePlayer*, ItemTotalInformation*, ushort*);

PACKET_HANDLE sp_NC_GAMBLE_SLOTMACHINE_START_REQ_Org;
PACKET_HANDLE sp_NC_ITEM_MIX_ITEM_REQ_Org;
PACKET_HANDLE sp_NC_MAP_TOWNPORTAL_REQ_Org;
PACKET_HANDLE sp_NC_ITEM_CHARGEDINVENOPEN_REQ_Org;
PACKET_HANDLE sp_NC_ITEM_REWARDINVENOPEN_REQ_Org;
PACKET_HANDLE sp_NC_ITEM_AUTO_ARRANGE_INVEN_REQ_Org;
PACKET_HANDLE sp_NC_ITEM_SPLIT_REQ_Org;
PACKET_HANDLE sp_NC_ITEM_RANDOMOPTION_CHANGE_REQ_Org;
PACKET_HANDLE sp_NC_BAT_SKILLBASH_OBJ_CAST_REQ_Org;
PACKET_HANDLE sp_NC_BAT_SKILLBASH_FLD_CAST_REQ_Org;
PACKET_HANDLE sp_NC_ACT_GATHERCOMPLETE_REQ_Org;
PACKET_HANDLE sp_NC_MAP_LOGINCOMPLETE_CMD_Org;
PACKET_HANDLE sp_NC_ITEM_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_REQ_Org;

bool EnableDoubleReward;
uint MinGatherTime;

bool LogPickup;

std::map<UINT16, UINT64> LuckyHouseUseTimings;
std::map<UINT16, UINT64> PremiumInvUseTimings;
std::map<UINT16, UINT64> RewardInvUseTimings;
std::map<UINT16, UINT64> ChestUseTimings;
std::map<ushort, DWORD> NextSkillTime;

namespace ShineObjectClass
{
    class ShinePlayer : public ShineMobileObject
    {
        HOOK_PUB_S void Install_IAFix()
        {
            so_Unmark_Org = (void(__thiscall*)(ShinePlayer*, RemoveWhen, char, char)) Detour(0x00558900, MF(so_UnmarkH));
        }

        HOOK_PUB_S void Install_GatherRangeFix()
        {
            EnableDoubleReward = Config->GetBoolean("Feature", "InstantGatherDoubleDrop", true);
            MinGatherTime = Config->GetInteger("Feature", "GatherTime", 200) / 100;

            sp_GatherComplete_Org = (void(__thiscall*) (ShinePlayer*, uint)) Detour(0x0046B2F0, MF(sp_GatherComplete));
            sp_NC_ACT_GATHERCOMPLETE_REQ_Org = (PACKET_HANDLE)Detour(0x0046CBF0, MF(sp_NC_ACT_GATHERCOMPLETE_REQ));
        }

        HOOK_PUB_S void Install_LHFix()
        {
            sp_NC_GAMBLE_SLOTMACHINE_START_REQ_Org = (PACKET_HANDLE)Detour(0x0061E870, MF(sp_NC_GAMBLE_SLOTMACHINE_START_REQ));
        }

        HOOK_PUB_S void Install_ItemMixFix()
        {
            sp_NC_ITEM_MIX_ITEM_REQ_Org = (PACKET_HANDLE)Detour(0x00521540, MF(sp_NC_ITEM_MIX_ITEM_REQ));
        }

        HOOK_PUB_S void Install_BuffDeleteFix()
        {
            EraseGoodBuff_Org = (ushort(__thiscall*) (ShinePlayer*, ABSTATEINDEX, ushort)) Detour(0x0042ACC0, MF(EraseGoodBuff));
        }

        HOOK_PUB_S void Install_TownPortalFix()
        {
            sp_NC_MAP_TOWNPORTAL_REQ_Org = (PACKET_HANDLE)Detour(0x0049FE70, MF(sp_NC_MAP_TOWNPORTAL_REQ));
        }

        HOOK_PUB_S void Install_PremiumInvFix()
        {
            sp_NC_ITEM_CHARGEDINVENOPEN_REQ_Org = (PACKET_HANDLE)Detour(0x004923C0, MF(sp_NC_ITEM_CHARGEDINVENOPEN_REQ));
        }

        HOOK_PUB_S void Install_MobExp()
        {
            so_GetExperienceFromMob_Org = (void(__thiscall*)(ShinePlayer*, int, ushort, ushort)) Detour(0x004302A0, MF(so_GetExperienceFromMobH));
        }

        HOOK_PUB_S void Install_PickupNotice()
        {
            LogPickup = Config->GetBoolean("Feature", "PickupAnnounceLogging", false);

            so_ply_PickupItem_Org = (bool(__thiscall*)(ShinePlayer*, ShineObject*, ItemTotalInformation*, unsigned __int16))Detour(0x0052FAF0, MF(so_ply_PickupItemH));
        }

        HOOK_PUB_S void Install_RewardInvFix()
        {
            sp_NC_ITEM_REWARDINVENOPEN_REQ_Org = (PACKET_HANDLE)Detour(0x004FC060, MF(sp_NC_ITEM_REWARDINVENOPEN_REQ));
        }

        HOOK_PUB_S void Install_ChestSpamFix()
        {
            sp_ChestBoxOpen_Org = (void(__thiscall*)(ShinePlayer*, int, ItemTotalInformation*))Detour(0x00598C90, MF(sp_ChestBoxOpen));
            sp_MysteryVaultMakeItem_Org = (bool(__thiscall*)(ShinePlayer*, ItemTotalInformation*, ushort*))Detour(0x005658F0, MF(sp_MysteryVaultMakeItem));
        }

        HOOK_PUB_S void Install_LevelUpAtLuaFix()
        {
            Detour(0x00561530, MF(so_ply_LevelUpAtLuaH));
        }

        HOOK_PUB_S void Install_CenDropNotice()
        {
            so_ply_PickupMoney_Org = (void(__thiscall*)(ShinePlayer*, unsigned int))Detour(0x0052FE80, MF(so_ply_PickupMoneyH));
        }

        HOOK_PUB_S void Install_NoArrangeInVendor()
        {
            sp_NC_ITEM_AUTO_ARRANGE_INVEN_REQ_Org = (PACKET_HANDLE)Detour(0x0051C360, MF(sp_NC_ITEM_AUTO_ARRANGE_INVEN_REQ));
        }

        HOOK_PUB_S void Install_NoSplitInVendor()
        {
            sp_NC_ITEM_SPLIT_REQ_Org = (PACKET_HANDLE)Detour(0x00539A40, MF(sp_NC_ITEM_SPLIT_REQ));
        }

        HOOK_PUB_S void Install_HOBMaxUsage()
        {
            sp_NC_ITEM_RANDOMOPTION_CHANGE_REQ_Org = (PACKET_HANDLE)Detour(0x00520E40, MF(sp_NC_ITEM_RANDOMOPTION_CHANGE_REQ));
        }

        HOOK_PUB_S void Install_RegenFailMap()
        {
            Detour(0x0043CF80, MF(sp_2Roumen));
        }

        HOOK_PUB_S void Install_TeleportWithMountFix()
        {
            so_mobile_Teleport_Org = (void(__thiscall*)(ShinePlayer*, SHINE_XY_TYPE*)) Detour(0x0057D1D0, MF(so_mobile_TeleportH));
        }

        HOOK_PUB_S void Install_Commands()
        {
            sp_AmpersandCommand_Org = (bool(__thiscall*)(ShinePlayer*, ushort, PROTO_NC_ACT_CHAT_REQ*)) Detour(0x0041A060, MF(sp_AmpersandCommand));
        }

        HOOK_PUB_S void Install_AnimationCheck()
        {
            sp_NC_BAT_SKILLBASH_OBJ_CAST_REQ_Org = (PACKET_HANDLE)Detour(0x0057FA50, MF(sp_NC_BAT_SKILLBASH_OBJ_CAST_REQ));
            sp_NC_BAT_SKILLBASH_FLD_CAST_REQ_Org = (PACKET_HANDLE)Detour(0x0057F400, MF(sp_NC_BAT_SKILLBASH_FLD_CAST_REQ));
        }

        HOOK_PUB_S void Install_NameCheck()
        {
            sp_NC_MAP_LOGINCOMPLETE_CMD_Org = (PACKET_HANDLE)Detour(0x00443390, MF(sp_NC_MAP_LOGINCOMPLETE_CMD));
        }

        HOOK_PUB_S void Install_GuildMoneyExploitFix()
        {
            sp_NC_ITEM_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_REQ_Org = (PACKET_HANDLE)Detour(0x00470110, MF(sp_NC_ITEM_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_REQ));
        }

        bool IsCastable(ushort id)
        {
            auto val = NextSkillTime.find(so_handle.sohu_Handle);
            auto now = Global::g_ClockWatch.cw_CurrMilliSec;

            if (val != NextSkillTime.end() && now < val->second)
            {
                *(ushort*)((DWORD)this + 0x7F37) = 4040;
                return false;
            }

            auto sk = Global::g_SkillDataBox[id];
            if (!sk)
            {
                *(ushort*)((DWORD)this + 0x7F37) = 4040;
                return false;
            }

            NextSkillTime[so_handle.sohu_Handle] = now + DataStore::GetAnimationTime(sk->sdi_Activ->InxName);
            return true;
        }

        HOOK_PUB_M void sp_NC_BAT_SKILLBASH_OBJ_CAST_REQ(NETCOMMAND* netcmd, int len, ushort handle)
        {
            if (!IsCastable(netcmd[1].protocol))
            {
                return;
            }

            sp_NC_BAT_SKILLBASH_OBJ_CAST_REQ_Org(this, netcmd, len, handle);
        }

        void sp_NC_MAP_LOGINCOMPLETE_CMD(NETCOMMAND* netcmd, int len, ushort handle)
        {
            auto name = std::string(so_CharName()->n5_name);

            if (so_AdministratorLevel() <= 0 && std::find_if(name.begin(), name.end(), [](const char c) { return !(isalnum(c) || c == '_'); }) != name.end())
            {
                so_banning(REMOVE_NOW);
                return;
            }

            sp_NC_MAP_LOGINCOMPLETE_CMD_Org(this, netcmd, len, handle);
        }

        void sp_NC_ITEM_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_REQ(NETCOMMAND* netcmd, int len, ushort handle)
        {
            if (so_ply_isAcademyGuildMember())
            {
                so_banning(REMOVE_NOW);
                return;
            }

            sp_NC_ITEM_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_REQ_Org(this, netcmd, len, handle);
        }

        void sp_NC_BAT_SKILLBASH_FLD_CAST_REQ(NETCOMMAND* netcmd, int len, ushort handle)
        {
            if (!IsCastable(netcmd[1].protocol))
            {
                return;
            }

            sp_NC_BAT_SKILLBASH_FLD_CAST_REQ_Org(this, netcmd, len, handle);
        }

        HOOK_PUB_M void so_UnmarkH(RemoveWhen when, char logoutpacket, char SaveType)
        {
            so_GetItemActionObserves()->iaom_Observes.clear();

            PremiumInvUseTimings[so_handle.sohu_Handle] = 0;
            LuckyHouseUseTimings[so_handle.sohu_Handle] = 0;

            so_Unmark_Org(this, when, logoutpacket, SaveType);
        }

        HOOK_PUB_M void sp_GatherComplete(uint lot_rate)
        {
            auto objHandle = *(ushort*)((DWORD)this + 0x2A308);
            if (objHandle == 0xFFFF)
            {
                return;
            }

            auto gatherObject = Global::g_ShineObjectManager.GetObject(objHandle);
            if (gatherObject != nullptr && so_DistanceSquar(gatherObject) > 6 meters)
            {
                so_ply_Notice("Please go closer to the object to gather it.");
                return;
            }

            sp_GatherComplete_Org(this, EnableDoubleReward ? 2 : 1);
        }

        HOOK_PUB_M void sp_NC_ACT_GATHERCOMPLETE_REQ(NETCOMMAND* netcmd, int len, ushort handle)
        {
            bool isLightningPick = (*(ChargedItemEffectList::ChargedItem*)((DWORD)this + 0x2A330)).ci_Effect.cec_LighteningPickParts;
            auto gatherTime = Global::g_SingleData.GetValue("Gather_MaxTime_Gatherable") * 10 / (isLightningPick ? 2 : 1);
            auto ts = *(TimeScheduler*)((DWORD)this + 0x2A784);

            if (ts.ts_Limit - Global::g_ClockWatch.cw_CurrTick > gatherTime - MinGatherTime)
            {
                so_ply_Notice("You cannot complete gathering this fast.");

                CallMemberFunction<ShinePlayer, void, NETCOMMAND*, int, ushort>(0x0046B120, this, netcmd, len, handle);
                so_SendErrorCode(8, 46, 2818);
                return;
            }

            sp_NC_ACT_GATHERCOMPLETE_REQ_Org(this, netcmd, len, handle);
        }

        HOOK_PUB_M void sp_NC_GAMBLE_SLOTMACHINE_START_REQ(NETCOMMAND* netcmd, int len, ushort handle)
        {
            auto val = LuckyHouseUseTimings.find(so_handle.sohu_Handle);
            auto now = time(nullptr);

            if (val != LuckyHouseUseTimings.end() && now - val->second < 5)
            {
                NotifyExploit("Lucky House: gambling too fast", "Please don't use slots this fast.");
                return;
            }

            LuckyHouseUseTimings[so_handle.sohu_Handle] = now;
            sp_NC_GAMBLE_SLOTMACHINE_START_REQ_Org(this, netcmd, len, handle);
        }

        HOOK_PUB_M void sp_NC_ITEM_MIX_ITEM_REQ(NETCOMMAND* netcmd, int len, ushort handle)
        {
            auto packet = (PROTO_NC_ITEM_MIX_ITEM_REQ*)&netcmd[1];

            if (packet->nRawLeft == packet->nRawRight)
            {
                NotifyExploit("Item Combine: same item twice", "Please use 2 different item slots to combine.");
                return;
            }

            sp_NC_ITEM_MIX_ITEM_REQ_Org(this, netcmd, len, handle);
        }

        HOOK_PUB_M ushort EraseGoodBuff(ABSTATEINDEX index, ushort notfinderrortype)
        {
            auto abstate = Global::g_AbStateDictionary.as_FromIndex(index)->index;
            ushort result = 7282;

            if (abstate)
            {
                auto viewinfo = DataStore::GetView(abstate->ID);

                if (abstate->DispelIndex == DA_NONE && viewinfo.IconSort == "DEBUFF")
                {
                    NotifyExploit("Buffs: removed unremovable buff", "", true);
                    so_banning(REMOVE_NOW);
                    return result;
                }

                result = EraseGoodBuff_Org(this, index, notfinderrortype);
            }

            return result;
        }

        HOOK_PUB_M void sp_NC_MAP_TOWNPORTAL_REQ(NETCOMMAND* netcmd, int len, ushort handle)
        {
            auto target = so_GetTargetObject();

            if (target == nullptr || !EQUALS(target->so_CharName()->n5_name, "Teleport Gate"))
            {
                NotifyExploit("Town Gate: not selected when trying to tp", "Please target the town gate.");
                return;
            }

            sp_NC_MAP_TOWNPORTAL_REQ_Org(this, netcmd, len, handle);
        }

        HOOK_PUB_M void sp_NC_ITEM_CHARGEDINVENOPEN_REQ(NETCOMMAND* netcmd, int len, ushort handle)
        {
            auto val = PremiumInvUseTimings.find(so_handle.sohu_Handle);
            auto now = time(nullptr);

            if (val != PremiumInvUseTimings.end() && now - val->second < 1)
            {
                so_ply_Notice("Please wait 1 second to open premium inventory or switch pages again.");
                return;
            }

            PremiumInvUseTimings[so_handle.sohu_Handle] = now;
            sp_NC_ITEM_CHARGEDINVENOPEN_REQ_Org(this, netcmd, len, handle);
        }

        HOOK_PUB_M void sp_NC_ITEM_REWARDINVENOPEN_REQ(NETCOMMAND* netcmd, int len, ushort handle)
        {
            auto val = RewardInvUseTimings.find(so_handle.sohu_Handle);
            auto now = time(nullptr);

            if (val != RewardInvUseTimings.end() && now - val->second < 2)
            {
                so_ply_Notice("Please wait 2 seconds to open reward inventory or switch pages again.");
                return;
            }

            RewardInvUseTimings[so_handle.sohu_Handle] = now;
            sp_NC_ITEM_REWARDINVENOPEN_REQ_Org(this, netcmd, len, handle);
        }

        void so_GetExperienceFromMobH(int expgain, ushort mobid, ushort mobhandle)
        {
            auto mobexp = DataStore::GetExpMob(mobid);

            if (mobexp.MobID != 0xFFFF)
            {
                auto lvl = so_GetLevel();

                if (lvl <= mobexp.MaxLevel)
                {
                    auto nextExp = Global::g_ShineParameter.scp_param.nextexp[lvl];
                    auto prevExp = Global::g_ShineParameter.scp_param.nextexp[lvl - 1];

                    auto giveExp = ceil((float)mobexp.Percentage / 1000.f * (float)(nextExp - prevExp));

                    sp_GainExp((int)giveExp, mobhandle, mobid);
                    return;
                }
            }

            so_GetExperienceFromMob_Org(this, expgain, mobid, mobhandle);
        }

        HOOK_PUB_M bool so_ply_PickupItemH(ShineObjectClass::ShineObject* itemobj, ItemTotalInformation* itemonfield, unsigned __int16 itemhandle)
        {
            auto id = itemonfield->iti_itemstruct.itemid;
            auto inf = Global::g_ItemDataBox[id];
            auto ret = so_ply_PickupItem_Org(this, itemobj, itemonfield, itemhandle);

            try
            {
                if (ret && inf)
                {
                    if (DataStore::ShouldAnnounce(id, so_Field->fm_MapID.n3_name))
                    {
                        auto msg = FORMAT_STR("%s has picked up %s", so_CharName(), inf->data->Name);

                        if (LogPickup)
                        {
                            Log::Pickup(msg);
                        }

                        auto a = AxialListWall(msg);
                        so_AllInMap(&a, 1);
                    }
                }
            }
            catch (...)
            {

            }

            return ret;
        }

        HOOK_PUB_M void sp_ChestBoxOpen(int slot, ItemTotalInformation* itm)
        {
            auto val = ChestUseTimings.find(so_handle.sohu_Handle);
            auto now = time(nullptr);

            if (val != ChestUseTimings.end() && now - val->second < 2)
            {
                so_ply_ItemUseResultPacket(4290, 9);
                so_ply_Notice("Please wait 2 seconds between each chest open.");
                return;
            }

            ChestUseTimings[so_handle.sohu_Handle] = now;
            sp_ChestBoxOpen_Org(this, slot, itm);
        }

        HOOK_PUB_M bool sp_MysteryVaultMakeItem(ItemTotalInformation* item, unsigned short* error)
        {
            auto val = ChestUseTimings.find(so_handle.sohu_Handle);
            auto now = time(nullptr);

            if (val != ChestUseTimings.end() && now - val->second < 3)
            {
                *error = 1794;
                so_ply_Notice("Please wait 3 seconds between each chest open.");
                return false;
            }

            ChestUseTimings[so_handle.sohu_Handle] = now;
            return sp_MysteryVaultMakeItem_Org(this, item, error);
        }

        HOOK_PUB_M void so_ply_LevelUpAtLuaH()
        {
            auto currLevel = so_GetLevel();
            auto reqExp = Global::g_ShineParameter.scp_param.nextexp[currLevel] - Global::g_ShineParameter.scp_param.nextexp[currLevel - 1];

            while (reqExp > 0)
            {
                if (reqExp > INT_MAX)
                {
                    sp_GainExp(INT_MAX, 0xFFFF, 0xFFFF);
                    reqExp -= INT_MAX;
                }
                else
                {
                    sp_GainExp(reqExp, 0xFFFF, 0xFFFF);
                    reqExp = 0;
                }
            }
        }

        HOOK_PUB_M void so_ply_PickupMoneyH(unsigned int money)
        {
            sp_pickitem.itemid = *(ushort*)0x14D50488;
            sp_pickitem.itemlot = money;

            so_ply_PickupMoney_Org(this, money);
        }

        HOOK_PUB_M void sp_NC_ITEM_AUTO_ARRANGE_INVEN_REQ(NETCOMMAND* netcmd, int len, ushort handle)
        {
            if (so_CurMode() == 5)
            {
                so_ply_Notice("Please leave vendor to use auto sort.");
                return;
            }

            sp_NC_ITEM_AUTO_ARRANGE_INVEN_REQ_Org(this, netcmd, len, handle);
        }

        HOOK_PUB_M void sp_NC_ITEM_SPLIT_REQ(NETCOMMAND* netcmd, int len, ushort handle)
        {
            if (so_CurMode() == 5)
            {
                so_SendErrorCode(12, 14, 1090);
                so_ply_Notice("Please leave vendor to split item stacks.");
                return;
            }

            sp_NC_ITEM_SPLIT_REQ_Org(this, netcmd, len, handle);
        }

        struct PROTO_NC_ITEM_RANDOMOPTION_CHANGE_REQ
        {
            char nItemSlotNo;
            char nStuffSlotNo;
        };

        HOOK_PUB_M void sp_NC_ITEM_RANDOMOPTION_CHANGE_REQ(NETCOMMAND* netcmd, int len, ushort handle)
        {
            auto np = (PROTO_NC_ITEM_RANDOMOPTION_CHANGE_REQ*)&netcmd[1];
            auto item = so_ItemInventory()->itembag.ci_Inventory.ib_GetInventoryCell(np->nItemSlotNo);

            if (!item)
            {
                so_SendErrorCode(12, 84, 12873);
                return;
            }

            auto changeCount = Global::g_ItemAttributeClassContainer[item->iic_Item.iti_itemstruct.itemid]->iacc_default.iac_GetRandomOptionChangeCount(&item->iic_Item.iti_itemstruct);
            auto maxChangeCount = DataStore::GetMaxHammerUseCount(item->iic_Item.iti_itemstruct.itemid);

            if (maxChangeCount != 0xFFFF)
            {
                if (maxChangeCount <= 0)
                {
                    so_SendErrorCode(12, 84, 12873);
                    so_ply_Notice("This item cannot be rerolled.");
                    return;
                }

                if (changeCount >= maxChangeCount)
                {
                    so_SendErrorCode(12, 84, 12873);
                    so_ply_Notice(FORMAT_STR("This item cannot be rerolled more than %d times.", maxChangeCount));
                    return;
                }
            }

            sp_NC_ITEM_RANDOMOPTION_CHANGE_REQ_Org(this, netcmd, len, handle);
        }

        HOOK_PUB_M void sp_2Roumen()
        {
            Global::g_PerformanceRecorder.pr_Entrance("ShineObjectClass::ShinePlayer::sp_2Roumen");
            NPCManager::LinkInformTemplete lnkinf;

            auto v2 = &so_Field->fm_MapID;
            if (v2)
            {
                auto opt = Global::g_FieldOption.fo_GetFieldAttr(v2->n3_name);

                if (opt)
                {
                    auto temp = Global::g_FieldOption.fo_GetFieldAttr(opt->regencity.n3_name);
                    if (temp)
                    {
                        opt = temp;
                    }

                    strcpy_s(lnkinf.linktoserver, opt->regencity.n3_name);
                    strcpy_s(lnkinf.linktoclient, opt->regencity.n3_name);
                    lnkinf.coordx = opt->regenloc[0].regenx;
                    lnkinf.coordy = opt->regenloc[0].regeny;
                }
                else
                {
                    strcpy_s(lnkinf.linktoserver, Config->Get("RegenFailMap", "MapIndex", "RouN"));
                    strcpy_s(lnkinf.linktoclient, Config->Get("RegenFailMap", "MapIndex", "RouN"));
                    lnkinf.coordx = Config->GetInteger("RegenFailMap", "CoordX", 6445);
                    lnkinf.coordy = Config->GetInteger("RegenFailMap", "CoordY", 8630);
                }

                so_LinkToReserv(&lnkinf, 0);
            }

            Global::g_PerformanceRecorder.pr_Exit("ShineObjectClass::ShinePlayer::sp_2Roumen");
        }

        HOOK_PUB_M void so_mobile_TeleportH(SHINE_XY_TYPE* location)
        {
            auto mover = so_MoverSystem_GetMover();
            so_mobile_Teleport_Org(this, location);

            if (mover)
            {
                mover->so_mobile_StopHere();

                mover->so_LocateInfo.location->x = location->x;
                mover->so_LocateInfo.location->y = location->y;

                so_ply_SendMoveFail();
            }
        }

        HOOK_PUB_M bool sp_AmpersandCommand(ushort handle, PROTO_NC_ACT_CHAT_REQ* chat)
        {
            auto ret = sp_AmpersandCommand_Org(this, handle, chat);

            auto msg = std::string(chat->content, chat->len);
            if (HookScript::Instance->RunCommand(so_handle.sohu_Handle, so_AdministratorLevel(), msg))
            {
                ret = true;
            }

            // if (!ret)
            // {
            //     if (DataStore::ContainsBlacklistedWord(msg))
            //     {
            //         so_ply_Notice("Please don't say any forbidden words.");
            //         ret = true;
            //     }
            // }

            return ret;
        }

        HOOK_PUB_M bool HasActiveSkill(ushort id)
        {
            auto csl = (CharaterSkillList*)((DWORD)this + 0x17D0C);

            return CallMemberFunction<CharaterSkillList, bool, ushort>(0x00446630, csl, id);
        }

        HOOK_PUB_M bool IsSkillCooldown(ushort id)
        {
            auto csl = (CharaterSkillList*)((DWORD)this + 0x17D0C);

            return CallMemberFunction<CharaterSkillList, bool, ShineObject*, ushort>(0x0046A420, csl, this, id);
        }

        HOOK_PUB_M bool HasPassiveSkill(ushort id)
        {
            auto cpl = (CharacterPassiveList*)((DWORD)this + 0x17D30);

            return CallMemberFunction<CharacterPassiveList, bool, ushort>(0x004193B0, cpl, id);
        }

        HOOK_PUB_M void sp_GainExp(int expgain, ushort mobhandle, ushort mobid)
        {
            return CallMemberFunction<ShinePlayer, void, int, ushort, ushort>(0x0042D830, this, expgain, mobhandle, mobid);
        }

        HOOK_PROT_M char _beginSize[0x29278 - 0x1EA8];

        struct
        {
            unsigned __int16 itemid;
            char _pad[0x2];
            unsigned int itemlot;
        } sp_pickitem;

        HOOK_PROT_M char _endSize[0x2C058 - 0x29280];

#pragma region Structures
        struct __declspec(align(2)) MiniHouseEntrance
        {
            unsigned __int16 MHFlag;
            unsigned __int16 MHRegNum;
            char isCastMiniHouse;
        };

        struct SHINE_MINI_GAME
        {
            char _size[0x100];
        };

        struct SocketStream
        {
            PacketContainer stream;
            PacketContainerBase* gamestream;
            PacketContainerBase* datastream;
        };

        struct __declspec(align(4)) NPCProcess
        {
            unsigned __int16 npchandle;
            unsigned __int16 npcid;
            NPCManager::NPCIndexArray* npc;
            CurrentMenu currentmenu;
            ServerMenuActor servermenuactor;
            DuplicatedMenuControl duplicatemenustate;
        };

        struct __declspec(align(8)) AccountStorage
        {
            unsigned __int64 cen;
            ItemAccountStorage storage;
        };

        struct PartyMemberInform
        {
            CParty::PARTY_SLOT* pmi_PartySlot;
            int pmi_LastHP;
            int pmi_LastSP;
            int pmi_LastLP;
            char pmi_ChrClass;
            char pmi_Level;
            unsigned int pmi_MaxHP;
            unsigned int pmi_MaxSP;
            unsigned int pmi_MaxLP;
            SHINE_XY_TYPE pmi_Coord;
        };

        struct __declspec(align(4)) MiniHouseStr
        {
            BriefInfoBackup mhs_Backup;
            void* mhs_SkinHandle;
            void* mhs_DummyObject[10];
            unsigned __int16 mhs_HPTick;
            unsigned __int16 mhs_SPTick;
            int mhs_HPInc;
            int mhs_SPInc;
            int mhs_BoothSlot;
            char mhs_Activ;
        };

        struct BoothSell
        {
            unsigned int lastrefresh;
            StreetBooth* boardpnt;
            StreetBoothSell boardsell;
            StreetBoothBuy boardbuy;
        };

        struct SpeedNotice
        {
            NETCOMMAND sn_NetCommand;
            PROTO_NC_ACT_MOVESPEED_CMD sn_MoveSpeed;
        };

        struct TimeScheduler
        {
            enum TS_ReturnType
            {
                TSRT_DEFAULT = 0x0,
                TSRT_RETURN = 0x1,
            };

            enum TS_CurWork
            {
                TSCW_NONE = 0x0,
                TSCW_MISC = 0x1,
                TSCW_NORMALATTACK_SWING = 0x2,
                TSCW_NORMALATTACK_DAMAGE = 0x3,
                TSCW_LOGOUT = 0x4,
            };

            unsigned int ts_Limit;
            ShineObjectClass::ShinePlayer::TimeScheduler::TS_ReturnType(ShinePlayer::* ts_CallFunc)();
            ShineObjectClass::ShinePlayer::TimeScheduler::TS_ReturnType ts_DefaultReturn;
            ShineObjectClass::ShinePlayer::TimeScheduler::TS_CurWork ts_CurWork;
            ShineObjectClass::ShinePlayer::TimeScheduler::TS_ReturnType(ShinePlayer::* ts_TimerFunc)(ShineObjectClass::ShinePlayer*);
        };

#pragma endregion

        /*
        ItemLotInspector sp_ItemLotInspector;
        unsigned int sp_ScriptCommand;
        struct
        {
            __int8 JustRevive : 1;
            __int8 JustLink : 1;
            __int8 DataRecieve : 1;
            __int8 SoloingMode : 1;
            __int8 AccountStorage_opened : 1;
            __int8 AStorageAnywhere_opened : 1;
            __int8 LinkReserv_link : 1;
            __int8 InAdminImmortal : 1;
            __int8 TryLinkUntilSuccess : 1;
            __int8 TeleportReserv : 1;
            __int8 BeSummoned : 1;
            __int8 IsAutoPickUp : 1;
            __int8 LockRefundReq : 1;
            __int8 LockRefundCanCelReq : 1;
            __int8 SomeClericReviveMe : 1;
            __int8 bModeIDReqWait : 1;
            __int8 bMoverUpgradeWait : 1;
            __int8 bItemBuyWait : 1;
        } sp_MiscFlag;
        unsigned __int16 sp_ChangeAbilityMobInfo;
        unsigned int sp_NextSwingTick;
        unsigned int sp_LastSwingTick;
        PROTO_NC_CHAR_WEDDINGDATA_ACK sp_WeddingData;
        ShineObjectClass::ShinePlayer::MiniHouseEntrance sp_MH_InnerInfo;
        ShineObjectClass::ShinePlayer::SHINE_MINI_GAME sp_MiniGame;
        FURNITURE_EMOTION_INFO sp_FurnitureEmotionInfo;
        unsigned __int16 sp_hGuildTorunamentFlagHandle;
        CallBackEvent* sp_punMarkEvent;
        char sp_bCharFreeStatLock;
        char GuildStoreageGrade;
        char nTournamentSeed;
        ClientSession* sp_SocketSession;
        TargetAnalyser_Player sp_TargetAnalyser;
        ShineObjectClass::ShinePlayer::SocketStream sp_SocketContainer;
        PacketEncrypt sp_Encryption;
        BriefInformationCharacter sp_CharBriefInfo;
        CeaseFireSender sp_CeaseFireSender;
        __declspec(align(1)) SkillCastFinish sp_SkillFinish;
        ZoneCharData sp_CharData;
        unsigned __int64 sp_NextSaveExp;
        PROTO_GAMEDATA_CMD sp_GameData;
        TargetObject sp_Target;
        struct
        {
            CharacterInventory itembag;
            InventoryLocking::InventoryCellLockList invenlocklist;
        } sp_Item;
        struct
        {
            unsigned int lasthp;
            unsigned int lastsp;
            unsigned int lastmaxhp;
            unsigned int lastmaxsp;
            Parameter::Cluster last;
        } sp_LastStat;
        struct
        {
            unsigned int StoneTick;
            unsigned int StoneReservationTick;
            void(__thiscall* PointStoneCheck)(ShineObjectClass::ShinePlayer*);
        } sp_HPStoneManager, sp_SPStoneManager;
        char sp_DuringItemEquip;
        NormalAttackDamageDelay::NormalAttackDamageTick sp_NormalAttackDamageTick;
        ShineQuestDiary sp_QuestDiary;
        struct
        {
            unsigned __int16 storagehandle;
        } sp_GuildStorageManager;
        struct __declspec(align(2))
        {
            unsigned __int16 storagehandle;
            char GuildAcademyRewardStoreageGrade;
        } sp_GuildAcademyRewardStorageManager;
        char sp_bOpenGuildRewardStorageWindow[3];
        CharaterSkillList sp_SkillList;
        CharacterPassiveList sp_Passive;
        struct
        {
            unsigned int lastpacket;
        } sp_LogoutWait;
        TradeStruct sp_tradestr;
        __unaligned __declspec(align(1)) TradeBoard sp_tradeboard;
        ShineObjectClass::ShinePlayer::NPCProcess sp_NPCProcess;
        ShineObjectClass::ShinePlayer::AccountStorage sp_AccountStorage;
        ItemRewardStorage sp_RewardStorage;
        ShineObjectClass::ShinePlayer::PartyMemberInform sp_LastPartyParam;
        Raid* sp_RaidSlot;
        struct
        {
            unsigned int nextsmash;
            int attackspeed;
        } sp_attackspeed;
        struct
        {
            unsigned __int16 itemid;
            unsigned int itemlot;
        } sp_pickitem;
        struct __declspec(align(4))
        {
            int actionnumber;
            unsigned int bashrange;
            unsigned __int16 bashinterval;
        } sp_BashControl;
        struct
        {
            __int8 normalattackcontinue : 1;
            __int8 successpacket : 1;
            __int8 duringnormalhit : 1;
        } sp_SkillControl;
        LastUpgradeStruct sp_LastUpgrade;
        unsigned __int16 sp_Linkreserv;
        SHINE_XY_TYPE sp_TeleportReserv;
        ShineObjectClass::ShinePlayer::MiniHouseStr sp_MiniHouse;
        void(__thiscall* sp_AdminFunction)(ShineObjectClass::ShinePlayer*);
        ProtoExtraCharacterData sp_extra;
        __declspec(align(1)) TreasureChestLocationManager sp_ChestItemBox;
        unsigned int sp_LastItemPickup;
        unsigned int sp_LastItemPickupByRaid;
        ShineObjectClass::ShinePlayer::BoothSell sp_Booth;
        ShineObjectClass::ShinePlayer::SpeedNotice sp_SpeedNotice;
        void(__thiscall* sp_RecoverPoint)(ShineObjectClass::ShinePlayer*);
        unsigned int sp_LastEffect;
        unsigned __int16 sp_MoverRecoveryTick;
        unsigned __int16 sp_MoverRecovery;
        void(__thiscall* sp_MoverUpgradeEffect)(ShineObjectClass::ShinePlayer*);
        CCharacterTitleZone sp_CharacterTitle;
        struct
        {
            unsigned __int16 rawobjecthandle;
        } sp_GatherStruct;
        Metronome sp_AutoSave;
        Metronome sp_EquipTick;
        unsigned int m_nMyGuildNo;
        GUILD_ZONE* m_pMyGuild;
        char m_isGuildAcademyMaster;
        unsigned int m_nMyGuildAcademyNo;
        GUILD_ZONE* m_pMyGuildAcademy;
        ChargedItemEffectList::ChargedItem sp_ChargedItem;
        ShineObjectClass::ShinePlayer::ChargedInven sp_ChargedInven;
        char sp_LastBoothSlotSend;
        ShineObjectClass::ShinePlayer::RideCasting sp_RideCast;
        ItemBreaker sp_ItemBreaker;
        ItemDropper sp_ItemDropper;
        ShineObjectClass::ShinePlayer::TimeScheduler sp_TimerStr;
        unsigned int sp_NormalLogoutTick;
        unsigned __int16 sp_RoarFlag;
        unsigned __int16 sp_GuildReNameFlag;
        unsigned __int16 sp_GuildReTypeFlag;
        unsigned __int16 sp_SkillEraseFlag;
        unsigned __int16 sp_SparrowFly;
        HuntLog::MobHuntLog sp_MobHuntLog;
        unsigned __int16 sp_MissileFlyMilliSec;
        unsigned __int16 sp_LastUsedItem;
        $7C82E4E14E5AF0E9DAF9C2F329BB65B2 sp_PlayTimeDay;
        ItemInventoryCell* sp_WeaponCell;
        char sp_LoginIP[4];
        char sp_ConnectFrom;
        unsigned int sp_ShoutTime;
        char sp_MovingShot;
        unsigned __int16 sp_SetEffectForJustSkill;
        SetItemData::PlayerSetEffect sp_SetItemEffect;
        char sp_PreventAttack;
        ItemTotalInformation* sp_CostumWeaponChargeing;
        ItemTotalInformation* sp_CostumShieldChargeing;
        char sp_isPossibleNewConnect;
        char sp_isIgnoreSkillCoolTime;
        ProtocolLogger sp_ProtocolLog;
        unsigned __int16 sp_MultiHitNotIndex;
        SoulCollectStruct sp_SoulCollect;
        SHINE_XY_TYPE sp_EntrancePoint;
        ItemActionObserveManager sp_ItemActionObserves;
        char sp_WillDisconnect;
        std::vector<Observer, std::allocator<Observer> > observers_;
        char sp_tempDataForItemSlot;
        ItemTotalInformation sp_tempDataForRandOptChange;
        ABSTATEINDEX sp_nPolymorphAbstateIndex;
        MobTacticElement::MobActionArgument* m_pCaptivateAI;
        MobTargetPlayerCaptivate m_TargetSelect;
        ShineObjectClass::ShineObject* m_pAITarget;
        ShineObjectClass::ShinePlayer::SpamChatTimeInfo sp_SpamChatTimeInfo;
        ShineObjectClass::ShinePlayer::SpamerInfo sp_SpamerInfo;
        int sp_SpamerInfoSaveChack;
        unsigned int tAutoSaveTime;
        char sp_MysteryVaultUI;
        unsigned int sp_NextCharTitleChangeTime;
        unsigned int sp_ReviveReqProcessTime;
        char sp_IsQuestRewardReq;
        unsigned int sp_Spammer_ChatBan;
        Name3 sp_Gamble_PrevMapName;
        unsigned __int64 sp_Gamble_nTotalExchangedCoin;
        unsigned __int64 sp_Gamble_nCurCoin;
        GAMBLE_TYPE sp_Gamble_JoinType;
        unsigned int sp_Gamble_SessionCloseingTime;
        unsigned __int16 nReactionNpcHandle;
        char sp_GodOfSlotMachine[10];
        int sp_nDamageAbsorb;
        int sp_nRemainingDamageAbsorb;
        CardCollection::CardCollectionAlbum sp_CardCollectAlbum;
        CardCollection::CardCollectionBookmark sp_CardCollectBookmark;
        CardCollection::CardCollectionReward sp_CardCollectReward;
        $3C989BA8434E34123D07658A9F4F5261 sp_RebirthState;
        unsigned __int16 sp_CastingBarTargetHandle;
        unsigned int sp_SwingTime;
        MOVER_LINKDATA sp_Mover_LinkData;
        char sp_Mover_nSlot;
        ShineObjectClass::ShineObject* sp_Mover_pObject;
        unsigned __int16 sp_ArrangeInvenCnt;
        unsigned int sp_ArrangeInvenDelayCheckTime;
        ShineObjectClass::ShinePlayer::LPInfo sp_Sen_LP;
        int sp_dLastBoothSearchOpeningTime;
        int sp_dLastBoothSearchReqTime;
        PROTO_TUTORIAL_INFO sp_TutorialInfo;
        __unaligned __declspec(align(1)) Name5 sp_LoginCharID;
        char sp_nChatFontColor;
        char sp_nChatBalloonColor;
        ShineObjectClass::ShinePlayer::PetInfoPlayer sp_PetInfo;
        ShineObjectClass::ShinePlayer::PetInfoForLink sp_PetInfoLink;
        ShineObjectClass::ShineObject* sp_Pet_pObject;
        Metronome sp_Pet_HouseTick;
        Metronome sp_Pet_BoothTick;
        Metronome sp_Pet_DanceTick;
        unsigned int sp_Pet_DanceDataIndex;
        unsigned int sp_UseItemMinimonCheckTime;
        USEITEM_MINIMON_INFO sp_UseItemMinimon;
        ShineObjectClass::ShinePlayer::UseITemMinimon_LoginSlot sp_UseItemMinimon_LoginSlot;
        CSellItemManager sp_SellItemManager;*/
    };
}
