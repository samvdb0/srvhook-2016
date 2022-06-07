#pragma once
#include "pch.h"


#include "AxialList.hpp"
#include "FieldMap.hpp"
#include "ItemActionObserveManager.hpp"
#include "LuaScript.hpp"
#include "Networking.hpp"

#pragma pack(push, 1)

struct ShineRTTI
{
    const char* m_pcName;
    ShineRTTI* m_pkBaseRTTI;
};

namespace ShineObjectClass
{
    enum RemoveWhen
    {
        REMOVE_NOW = 0x0,
        REMOVE_LOGOUT = 0x1,
        REMOVE_WARP = 0x2,
        REMOVE_REVIVE = 0x3,
    };

    enum PartyGroup
    {
        PartyGroup_Alone = 0x0,
        PartyGroup_Party = 0x1,
        PartyGroup_Raid = 0x2,
    };

    enum BattleCamp
    {
        BC_NONE = 0x0,
        BC_MOB = 0x1,
        BC_CHAR = 0x2,
        BC_NPC = 0x3,
    };

	enum DataBase
    {
        TOTAL_ITEM_STRUCT = 0x0,
        ONLY_REGISTNUMBER = 0x1,
    };

    enum ShineObjectType
    {
        OBJTYPE_FLAG = 0,
        OBJTYPE_DROPITEM = 1,
        OBJTYPE_CHARACTER = 2,
        OBJTYPE_MINIHOUSE = 3,
        OBJTYPE_NPC = 4,
        OBJTYPE_MOB = 5,
        OBJTYPE_MAGICFIELD = 6,
        OBJTYPE_DOOR = 7,
        OBJTYPE_BANDIT = 8,
        OBJTYPE_EFFECT = 9,
        OBJTYPE_SERVANT = 10,
        OBJTYPE_MOVER = 11,
        OBJTYPE_PET = 12,
        OBJTYPE_MAX = 13
    };
	
    class ShineObject
    {
        struct LuaAi
        {
            LuaScriptScenario* AIScript;
            std::string Entrance;
            std::string NPCClick;
            std::string NPCMenu;
            std::string MobDamaged;
            std::string ObjectDied;
            std::string NPCAction;
            std::string MobAttack;
            std::string RankingValue;
        };

        HOOK_PUB_M char IsDropping(ItemTotalInformation* item, ShineObjectClass::DataBase dbwrite, ShineMultiTypeHandle* LooterHandle, unsigned __int16 murdurerhandle, unsigned int murdurerregnum, ItemAttributeClass* attclass, int from)
        {
            return CallMemberFunction<ShineObject, char, ItemTotalInformation*, DataBase, ShineMultiTypeHandle*, ushort, uint, ItemAttributeClass*, int>(0x004B0A20, this, item, dbwrite, LooterHandle, murdurerhandle, murdurerregnum, attclass, from);
        }

    	HOOK_PUB_M int so_DistanceSquar(ShineObject* obj)
        {
            return CallMemberFunction<ShineObject, int, ShineObject*>(0x004028F0, this, obj);
        }

    	HOOK_PUB_M bool IsOfType(ShineObjectType type)
        {
            return so_ObjectType() == type;
        }

    	HOOK_PUB_M bool IsCharacter()
        {
            return IsOfType(OBJTYPE_CHARACTER);
        }

    	HOOK_PUB_M char so_AllInMap(AxialListIterator* ala, int toMe)
        {
            return CallMemberFunction<ShineObject, char, AxialListIterator*, int>(0x0054B9E0, this, ala, toMe);
        }

        HOOK_PUB_M void NotifyExploit(const char* type, const char* msg, bool onlyLog = false)
        {
            if (LogEnabled)
            {
                Log::ToFile("ExploitLog.Zone.txt", "Exploit", FORMAT_STR("%s -> %s", so_CharName(), type));
            }

            if (onlyLog || !NoticeEnabled)
            {
                return;
            }

            so_ply_Notice(msg);
        }
    	
        HOOK_PUB_M virtual ShineRTTI* GetRTTI();
        HOOK_PUB_M virtual char so_mh_ClearDiceBettingInfo();
        HOOK_PUB_M virtual char so_mh_SetDiceHistory();
        HOOK_PUB_M virtual char so_mh_ClearGamerBettingInfo();
        HOOK_PUB_M virtual char so_mh_GetTaiSaiGamerCnt();
        HOOK_PUB_M virtual char so_mh_RankSort();
        HOOK_PUB_M virtual char so_mh_SetIsCreateDice(char, SHINE_ITEM_REGISTNUMBER);
        HOOK_PUB_M virtual char so_mh_IsCreateDice(SHINE_ITEM_REGISTNUMBER);
        HOOK_PUB_M virtual char so_mh_SetIsDeleteDice(char, SHINE_ITEM_REGISTNUMBER);
        HOOK_PUB_M virtual char so_mh_IsDeleteDice(SHINE_ITEM_REGISTNUMBER);
        HOOK_PUB_M virtual char so_mh_SetIsBlowGame(char);
        HOOK_PUB_M virtual char so_mh_IsBlowGame();
        HOOK_PUB_M virtual char so_mh_SetIsLeaveOwner(char);
        HOOK_PUB_M virtual char so_mh_IsLeaveOwner();
        HOOK_PUB_M virtual char so_mh_ExcuteLeaveRoom();
        HOOK_PUB_M virtual char so_mh_ExcuteLeaveGame();
        HOOK_PUB_M virtual char so_mh_ExcuteBlowGame();
        HOOK_PUB_M virtual char so_mh_IsActiveDiceTaiSai();
        HOOK_PUB_M virtual ushort so_mh_SendTaiSaiGameInfo(ShineObject*);
        HOOK_PUB_M virtual ushort so_mh_SendTaiSaiBettingInfo(ShineObject*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_CanEnter(ShineObject*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_Enter(ShineObject*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_BroadEnter(ShineObject*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_Out(ShineObject*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_BroadOut(ShineObject*, char);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_ModeChange(ShineObject*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_BroadModeChange(ShineObject*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_ModeChangeLeave(ShineObject*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_BroadModeChangeLeave(ShineObject*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_BroadSetTimer(DiceTaiSaiBetting*, DICE_TAISAI_BETTING_TYPE);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_CanBetting(ShineObject*, DiceTaiSaiBetting*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_Betting(ShineObject*, DiceTaiSaiBetting*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_BroadBetting(ShineObject*, DiceTaiSaiBetting*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_CanBettingCancel(ShineObject*, DiceTaiSaiBetting*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_BettingCancel(ShineObject*, DiceTaiSaiBetting*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_BroadBettingCancel(ShineObject*, DiceTaiSaiBetting*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_CanDiceRoll(ShineObject*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_CanAutoDiceRoll();
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_DiceRoll();
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_BroadDiceRoll();
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_MoneyResult_DiceRoll(PROTO_NC_DICE_TAISAI_DB_DICE_ROLL_RESULT_ACK*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_Result_DiceRoll();
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_ResultLog_DiceRoll(int);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_BroadResult_DiceRoll();
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_BroadEmotion_DiceRoll(PROTO_NC_DICE_TAISAI_DB_DICE_ROLL_RESULT_ACK*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_PrepareNextGame();
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_GetExpectIncomeMoney(ITEM_INVEN);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_GetReceiptIncomeMoney(ITEM_INVEN);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_GetRank(ShineObject*);
        HOOK_PUB_M virtual ushort so_mh_DiceTaiSai_SendRank(PROTO_NC_DICE_TAISAI_DB_RANK_ACK*);
        HOOK_PUB_M virtual char so_mh_DiceTaiSai_BroadLargeAmount();
        HOOK_PUB_M virtual char so_mh_DiceTaiSai_BroadGameFold();
        HOOK_PUB_M virtual DICE_TAISAI_GAME_STATUS so_mh_DiceTaiSai_GetGameStatus();
        HOOK_PUB_M virtual DICE_TAISAI_GAME_MODE so_mh_DiceTaiSai_GetGameMode();
        HOOK_PUB_M virtual char so_mh_SetDiceRewardMoney(PROTO_NC_DICE_TAISAI_DB_ITEM_ID_CHANGE_ACK*);
        HOOK_PUB_M virtual FURNITURE_EMOTION_INFO* so_ply_MH_GetFurnitureEmotionInfo();
        HOOK_PUB_M virtual char so_ply_MH_InitFurnitureEmotionInfo();
        HOOK_PUB_M virtual char so_ply_MH_IsFurnitureEmotion(unsigned __int16);
        HOOK_PUB_M virtual char so_ply_MH_IsFurnitureEmotionPosition(unsigned __int16, char);
        HOOK_PUB_M virtual char so_ply_MH_IsFurnitureEmotionNo(char);
        HOOK_PUB_M virtual ushort so_ply_MH_GetFurnitureEmotion();
        HOOK_PUB_M virtual char so_ply_MH_GetFurnitureEmotionPosition();
        HOOK_PUB_M virtual char so_ply_MH_GetFurnitureEmotionNo();
        HOOK_PUB_M virtual char so_ply_MH_SetFurnitureEmotion(unsigned __int16);
        HOOK_PUB_M virtual char so_ply_MH_SetFurnitureEmotionPosition(char);
        HOOK_PUB_M virtual char so_ply_MH_SetFurnitureEmotionNo(char);
        HOOK_PUB_M virtual ushort so_mh_CanFurnitureEmotion(ShineObject*, PROTO_NC_MINIHOUSE_FURNITURE_EMOTION_REQ*);
        HOOK_PUB_M virtual char so_mh_IsFurnitureEmotion(unsigned __int16, char);
        HOOK_PUB_M virtual char so_mh_FurnitureEmotionStop(unsigned __int16, ShineObject*);
        HOOK_PUB_M virtual char so_mh_SendInnerPlayerFurnitureEmotion(ShineObject*);
        HOOK_PUB_M virtual char so_PacketBufferFlush();
        HOOK_PUB_M virtual void so_SetRegistNumber(PROTO_NC_CHAR_REGISTNUMBER_ACK*);
        HOOK_PUB_M virtual void so_SetSocketSession(ClientSession*);
        HOOK_PUB_M virtual int so_EncSeedSet();
        HOOK_PUB_M virtual PacketContainerBase* so_GetDataSocketStream();
        HOOK_PUB_M virtual PacketContainerBase* so_GetGameSocketStream();
        HOOK_PUB_M virtual char so_IsEmpty();
        HOOK_PUB_M virtual void so_SendProtocol(int, int);
        HOOK_PUB_M virtual void so_SendErrorCode(int, int, int);
        HOOK_PUB_M virtual void so_FirstActionAfterSocketConnect();
        HOOK_PUB_M virtual void so_CloseByLink();
        HOOK_PUB_M virtual LastUpgradeStruct* so_GetLastUpgradeInfo();
        HOOK_PUB_M virtual char so_door_DoorAction(char*, MapBlock::DoorAction);
        HOOK_PUB_M virtual TradeStruct* so_TradeStructure();
        HOOK_PUB_M virtual TradeBoard* so_TradeBoard();
        HOOK_PUB_M virtual bool so_GetWaitTradeResFromDB();
        HOOK_PUB_M virtual void so_SetWaitTradeResFromDB(bool);
        HOOK_PUB_M virtual void so_ply_ItemMakeItem(ItemTotalInformation*);
        HOOK_PUB_M virtual void so_SetPossibleNewConnect(char);
        HOOK_PUB_M virtual char so_GetPossibleNewConnect();
        HOOK_PUB_M virtual void so_RefreshWMSSocket();
        HOOK_PUB_M virtual void so_Unmark(ShineObjectClass::RemoveWhen, char, char);
        HOOK_PUB_M virtual ushort so_GetWMSHandle();
        HOOK_PUB_M virtual uint so_GetCharRegistNumber();
        HOOK_PUB_M virtual uint so_GetUserRegistNumber();
        HOOK_PUB_M virtual void so_NC_ITEMDB_ADMINCREATEFAIL_ACK(PROTO_NC_ITEMDB_ADMINCREATEFAIL_ACK*);
        HOOK_PUB_M virtual void so_NC_ITEMDB_fail(int, int, unsigned __int16);
        HOOK_PUB_M virtual void so_NC_ITEMDB_USE_ACK(unsigned __int16);
        HOOK_PUB_M virtual void so_BackupParameter(Parameter::Cluster*);
        HOOK_PUB_M virtual void so_RecalcEquipParam();
        HOOK_PUB_M virtual void so_RecalcAbstateParam();
        HOOK_PUB_M virtual void so_RecalcPassiveParam();
        HOOK_PUB_M virtual void so_RecalcLastParam();
        HOOK_PUB_M virtual void so_ply_ItemEffect(UseEffectType, unsigned __int16, UseEffect::UIE_Functions*);
        HOOK_PUB_M virtual void so_ply_ChargedBuff(ItemTotalInformation*);
        HOOK_PUB_M virtual void so_ply_NewSkillCoolTime(unsigned __int16, int);
        HOOK_PUB_M virtual void so_ply_InitFreeStat();
        HOOK_PUB_M virtual void so_ply_InitSkillEmpow();
        HOOK_PUB_M virtual void so_ply_SkillEmpowerSetResult(unsigned __int16, unsigned __int16);
        HOOK_PUB_M virtual int so_ply_IncNGet_PKCount();
        HOOK_PUB_M virtual int so_ply_SavePKCount(PROTO_NC_CHARSAVE_PKCOUNT_CMD*);
        HOOK_PUB_M virtual int so_SaveLocation(PROTO_NC_CHARSAVE_LOCATION_CMD*);
        HOOK_PUB_M virtual int so_SaveLevel(PROTO_NC_CHARSAVE_LEVEL_CMD*);
        HOOK_PUB_M virtual int so_SaveQuestDoing(PROTO_NC_CHARSAVE_2WLDMAN_QUEST_DOING_CMD*);
        HOOK_PUB_M virtual int so_SaveQuestDoing(PROTO_NC_CHARSAVE_QUEST_DOING_REQ*);
        HOOK_PUB_M virtual int so_SaveQuestRead(PROTO_NC_CHARSAVE_2WLDMAN_QUEST_READ_CMD*);
        HOOK_PUB_M virtual int so_SaveQuestRepeat(PROTO_NC_CHARSAVE_2WLDMAN_QUEST_REPEAT_CMD*);
        HOOK_PUB_M virtual int so_SaveAbstate(PROTO_NC_CHARSAVE_ABSTATE_REQ*, Name5*, bool);
        HOOK_PUB_M virtual int so_SaveSkill(PROTO_NC_CHARSAVE_SKILL_REQ*, int);
        HOOK_PUB_M virtual int so_SaveStat(PROTO_NC_CHARSAVE_CHARSTAT_CMD*);
        HOOK_PUB_M virtual int so_SaveGameData(PROTO_GAMEDATA_CMD*);
        HOOK_PUB_M virtual int so_SaveItem(PROTO_ITEM_CMD*);
        HOOK_PUB_M virtual char so_SaveItem_Part(NETCOMMAND*, PROTO_NC_CHARSAVE_2WLDMAN_ITEM_CMD*);
        HOOK_PUB_M virtual int so_SaveChestInfo(PROTO_NC_CHAR_CHESTINFO_REQ*);
        HOOK_PUB_M virtual int so_SaveCharTitle(CHARACTER_TITLE_READBLOCK*);
        HOOK_PUB_M virtual int so_SaveMisc2WMS(PROTO_NC_CHARSAVE_2WLDMAN_MISC_CMD*);
        HOOK_PUB_M virtual int so_SaveToDB_CharTitle(CHARACTER_TITLE_DB_SAVE*);
        HOOK_PUB_M virtual FieldMap* so_ply_FindJobDungeon(char*);
        HOOK_PUB_M virtual char so_ply_2JobDungeon(FieldMap*, char*);
        HOOK_PUB_M virtual int so_ply_FirstJobChange();
        HOOK_PUB_M virtual int so_ply_SilverWingCoolTime();
        HOOK_PUB_M virtual void so_ply_MakeMiniHouse(PROTO_NC_ITEMDB_ADMINCREATESUC_ACK*);
        HOOK_PUB_M virtual void so_ply_SendBoothSize();
        HOOK_PUB_M virtual char so_AbnormalState_IsSet(ABSTATEINDEX);
        HOOK_PUB_M virtual char so_AbnormalState_Strength(ABSTATEINDEX);
        HOOK_PUB_M virtual uint so_AbnormalState_RestTime(ABSTATEINDEX);
        HOOK_PUB_M virtual void so_AbnormalState_Inform(ABSTATEINDEX, int, char);
        HOOK_PUB_M virtual void so_RetrateFromMap();
        HOOK_PUB_M virtual void so_RetreatFromMapByImmeditely();
        HOOK_PUB_M virtual void so_LinkToReserv(NPCManager::LinkInformTemplete*, char);
        HOOK_PUB_M virtual void so_TeleportReserv(SHINE_XY_TYPE*);
        HOOK_PUB_M virtual bool sp_IsLockedRefundReq();
        HOOK_PUB_M virtual void sp_LockRefundReq();
        HOOK_PUB_M virtual void sp_UnlockRefundReq();
        HOOK_PUB_M virtual bool sp_IsLockedRefundCancelReq();
        HOOK_PUB_M virtual void sp_LockRefundCancelReq();
        HOOK_PUB_M virtual void sp_UnlockRefundCancelReq();
        HOOK_PUB_M virtual uint sp_lastpickuptime();
        HOOK_PUB_M virtual CCharacterTitleZone* so_GetCharacterTitle();
        HOOK_PUB_M virtual CHARSTATDISTSTR* so_GetStatDistStr();
        HOOK_PUB_M virtual BattleStat* so_GetBattleStat();
        HOOK_PUB_M virtual void so_GetTargetInfo(ShineObject*);
        HOOK_PUB_M virtual Parameter::Container* so_parameter();
        HOOK_PUB_M virtual ulong so_ply_CurrentMoney();
        HOOK_PUB_M virtual ulong so_ply_CurrentExp();
        HOOK_PUB_M virtual uint so_ply_CurrentFame();
        HOOK_PUB_M virtual void so_ply_StoreMoney(unsigned __int64);
        HOOK_PUB_M virtual void so_ply_StoreFame(unsigned int);
        HOOK_PUB_M virtual void so_ply_ChangeCen();
        HOOK_PUB_M virtual void so_ply_ChangeFame();
        HOOK_PUB_M virtual void so_ply_SaveFame();
        HOOK_PUB_M virtual void so_ply_DepositAck(PROTO_NC_ITEMDB_DEPOSIT_ACK*);
        HOOK_PUB_M virtual void so_ply_WithdrawAck(PROTO_NC_ITEMDB_WITHDRAW_ACK*);
        HOOK_PUB_M virtual void so_ply_GuildStorageWithdrawAck(PROTO_NC_ITEMDB_GUILD_STORAGE_WITHDRAW_ACK*);
        HOOK_PUB_M virtual void so_ply_InvenCellReleaser_PointStone(InventoryLocking::LockedCell*);
        HOOK_PUB_M virtual void so_ply_InvenCellReleaser_QuestReward(InventoryLocking::LockedCell*);
        HOOK_PUB_M virtual ShineCommonParameter::FreeStatStr* so_ply_FreeStatStr();
        HOOK_PUB_M virtual ShineCommonParameter::FreeStatInt* so_ply_FreeStatInt();
        HOOK_PUB_M virtual ShineCommonParameter::FreeStatDex* so_ply_FreeStatDex();
        HOOK_PUB_M virtual ShineCommonParameter::FreeStatCon* so_ply_FreeStatCon();
        HOOK_PUB_M virtual ShineCommonParameter::FreeStatMen* so_ply_FreeStatMen();
        HOOK_PUB_M virtual unnamed_type_sp_Item* so_ItemInventory();
        HOOK_PUB_M virtual SpyNet::EspionageAgent* so_SpyAgent();
        HOOK_PUB_M virtual char so_CurMode();
        HOOK_PUB_M virtual void so_ply_ReinforceFoldtent();
        HOOK_PUB_M virtual int so_ply_InventorySize();
        HOOK_PUB_M virtual int so_ply_StorageSize();
        HOOK_PUB_M virtual int so_ply_StreetBoothSlot();
        HOOK_PUB_M virtual ChargedEffectContainer* so_ply_ChargedEffectContainer();
        HOOK_PUB_M virtual CharClass* so_CharacterClass();
        HOOK_PUB_M virtual ABNORMAL_STATE_BIT* so_Getabstatebit();
        HOOK_PUB_M virtual ushort so_RemakeHandle(unsigned __int16);
        HOOK_PUB_M virtual PacketEncrypt* so_PacketEncryptClass();
        HOOK_PUB_M virtual char so_Routine(List<ShineObject>*, unsigned __int16);
        HOOK_PUB_M virtual char so_ply_BanByServerDisconnect(List<ShineObject>*, unsigned __int16);
        HOOK_PUB_M virtual void so_StoreCharData(unsigned __int16, char*);
        HOOK_PUB_M virtual int so_OverlapFactor();
        HOOK_PUB_M virtual PROTO_NC_CHAR_BASE_CMD::LoginLocation* so_LoginLocation();
        HOOK_PUB_M virtual void so_datasync();
        HOOK_PUB_M virtual void so_FillBriefInformation(void*);
        HOOK_PUB_M virtual void so_SendMyBriefInfo(ShineObject*);
        HOOK_PUB_M virtual void so_SetGateBriefInform(char*);
        HOOK_PUB_M virtual char so_ObjectType();
        HOOK_PUB_M virtual uchar so_AdministratorLevel();
        HOOK_PUB_M virtual uchar so_GetLevel();
        HOOK_PUB_M virtual char so_GetClass();
        HOOK_PUB_M virtual char so_TargetType();
        HOOK_PUB_M virtual void so_Heal(int);
        HOOK_PUB_M virtual uint so_GetHP();
        HOOK_PUB_M virtual uint so_GetSP();
        HOOK_PUB_M virtual uint so_MaxHP();
        HOOK_PUB_M virtual uint so_MaxSP();
        HOOK_PUB_M virtual void so_LostSP(int);
        HOOK_PUB_M virtual void so_GainSP(int);
        HOOK_PUB_M virtual void so_LostHP(int);
        HOOK_PUB_M virtual void so_GainHP(int);
        HOOK_PUB_M virtual int so_attackspeed1000();
        HOOK_PUB_M virtual int so_attackspeed1000_packet();
        HOOK_PUB_M virtual uint so_AttackRange(ShineObject*);
        HOOK_PUB_M virtual ushort so_WalkSpeed();
        HOOK_PUB_M virtual ushort so_RunSpeed();
        HOOK_PUB_M virtual void so_BroadcastLogout();
        HOOK_PUB_M virtual int so_fullbufferitem(char*, PROTO_ITEMPACKET_INFORM*);
        HOOK_PUB_M virtual int so_fullbufferitem_box(char*, PROTO_ITEMPACKET_INFORM*, int, ItemBag*);
        HOOK_PUB_M virtual void so_RecalcAbstateParamReady();
        HOOK_PUB_M virtual AbnormalStateContainer::AbstateListInObject* so_mobile_AbstateList();
        HOOK_PUB_M virtual void so_Chat(unsigned __int16, char*, int, char, int);
        HOOK_PUB_M virtual void so_Shout(unsigned __int16, char*, char*, int, int);
        HOOK_PUB_M virtual void so_drpitm_CanLootingBitSet(ShineObject*);
        HOOK_PUB_M virtual char so_drpitm_CanLooting(ShineObject*);
        HOOK_PUB_M virtual char so_drpitm_IsIndividualType();
        HOOK_PUB_M virtual ushort so_ItemDrop(unsigned __int16, ShineObject*, ItemTotalInformation*, unsigned int, ShineMultiTypeHandle*, char);
        HOOK_PUB_M virtual ItemTotalInformation* so_drpitm_itemview();
        HOOK_PUB_M virtual void so_itempicked();
        HOOK_PUB_M virtual ushort so_PartyRegistNumber();
        HOOK_PUB_M virtual ushort so_GetRaidNumber();
        HOOK_PUB_M virtual void so_SetRaidNumber(unsigned __int16);
        HOOK_PUB_M virtual ShineObjectClass::PartyGroup so_GetPartyGroup();
        HOOK_PUB_M virtual ushort so_PartyRegistNumber_InAttack();
        HOOK_PUB_M virtual uint so_GetCharRegistNumber_ItemLooter();
        HOOK_PUB_M virtual ushort so_GetZoneHandle_ItemLooter();
        HOOK_PUB_M virtual Name5* so_CharName();
        HOOK_PUB_M virtual ProtoExtraCharacterData* so_extradata();
        HOOK_PUB_M virtual void so_SetParty(unsigned __int16);
        HOOK_PUB_M virtual void so_ply_SendPartyInformTo(ShineObject*);
        HOOK_PUB_M virtual void so_allparametercalculate();
        HOOK_PUB_M virtual int so_attack(ShineObject*, int);
        HOOK_PUB_M virtual int so_attack(ShineObject*, int, int);
        HOOK_PUB_M virtual void so_SetLastBattle();
        HOOK_PUB_M virtual char so_isinbattle();
        HOOK_PUB_M virtual void so_SlantedFlag(unsigned int, unsigned int, FieldMap*, ShineObject*);
        HOOK_PUB_M virtual int so_smash(EngageArgument*);
        HOOK_PUB_M virtual int so_Bash(EngageArgument*, int*, ABSTATEINDEX, int, int, int);
        HOOK_PUB_M virtual int so_skillsmash(ShineObject*, SmashArgument*);
        HOOK_PUB_M virtual char so_SkillEnchant(ShineObject*, SmashArgument*, BattleObjectGroup::BattleObjectStruct*, char*, char);
        HOOK_PUB_M virtual char so_SkillCure(ShineObject*, SmashArgument*, BattleObjectGroup::BattleObjectStruct*);
        HOOK_PUB_M virtual char so_Dispel(ShineObject*, SmashArgument*, BattleObjectGroup::BattleObjectStruct*, unsigned int);
        HOOK_PUB_M virtual char so_CanSkillTarget();
        HOOK_PUB_M virtual void so_MoveByServer(SHINE_XY_TYPE*, int, int, MoveManager::MMState, int);
        HOOK_PUB_M virtual void so_recoverhp(int);
        HOOK_PUB_M virtual void so_recoversp(int);
        HOOK_PUB_M virtual void so_KilledBy(ShineObject*, int, int, unsigned int);
        HOOK_PUB_M virtual void so_DamagedBy(ShineObject*, int, int, char);
        HOOK_PUB_M virtual void so_GetExperienceFromMob(int, unsigned __int16, unsigned __int16);
        HOOK_PUB_M virtual void so_briefequipset();
        HOOK_PUB_M virtual int so_EqualSetitemIndexNameCount(const char*);
        HOOK_PUB_M virtual ItemActionObserveManager* so_GetItemActionObserves();
        HOOK_PUB_M virtual void so_ItemActonAbstateApp(AbnormalStateContainer::AbstateElementInObject*, SkillDataBox::SkillDataIndex*, ShineObject*);
        HOOK_PUB_M virtual int so_AddItemAction(unsigned __int16, unsigned __int16);
        HOOK_PUB_M virtual int so_DelItemAction(unsigned __int16, unsigned __int16);
        HOOK_PUB_M virtual void so_ply_ItemAction_UnEquip(ItemInventoryCell*);
        HOOK_PUB_M virtual void so_ply_EnchantActionUse(const unsigned __int16);
        HOOK_PUB_M virtual void so_ply_GuildStoreFill(PROTO_NC_ITEMDB_OPEN_GUILD_STORAGE_ACK*);
        HOOK_PUB_M virtual void so_ply_GuildStoreGradeFill(char);
        HOOK_PUB_M virtual char so_ply_isGuildStoreGrade();
        HOOK_PUB_M virtual uint so_weapontitle(unsigned __int16*);
        HOOK_PUB_M virtual void so_Disconnect(int, ShineObjectClass::RemoveWhen, int);
        HOOK_PUB_M virtual void so_banning(ShineObjectClass::RemoveWhen);
        HOOK_PUB_M virtual char so_LinkTo(NPCManager::LinkInformTemplete*, int, int, int);
        HOOK_PUB_M virtual void so_ply_ChangeCell(ITEM_INVEN*, ItemInventoryCell*, ITEM_INVEN*);
        HOOK_PUB_M virtual void so_ply_ChangeBriefInfo(ItemInventoryCell*, int);
        HOOK_PUB_M virtual SHINE_XY_TYPE* so_mobile_Move2Where();
        HOOK_PUB_M virtual char so_mobile_IsInMoving();
        HOOK_PUB_M virtual SHINE_XY_TYPE* so_mob_RegenLocation();
        HOOK_PUB_M virtual SHINE_XY_TYPE* so_mob_LastHittedLocation();
        HOOK_PUB_M virtual uint so_mob_ChaseRangeSquar();
        HOOK_PUB_M virtual void so_LearnPassive(unsigned __int16);
        HOOK_PUB_M virtual void so_LearnSkill(unsigned __int16);
        HOOK_PUB_M virtual void so_TradeBoardreset();
        HOOK_PUB_M virtual void so_tradestart(ShineObject*);
        HOOK_PUB_M virtual char so_tradepropose_timecheck();
        HOOK_PUB_M virtual char so_AbnormalState_Resist(AbnormalStateDictionary::AbState::AbStateStr*);
        HOOK_PUB_M virtual char so_AbnormalState_Set(ShineObject*, ABSTATEINDEX, int, AbnormalStateDictionary::AbState::AbStateStr*, unsigned int, int, int, int, AbnormalStateContainer::EnchantFrom, AbnormalStateContainer::AbStateElementSetData*);
        HOOK_PUB_M virtual char so_AbnormalState_Set_CharAllMode(ShineObject*, ABSTATEINDEX, int, AbnormalStateDictionary::AbState::AbStateStr*, unsigned int, int, int, int, AbnormalStateContainer::EnchantFrom);
        HOOK_PUB_M virtual char so_AbnormalState_Set_Simple(ShineObject*, ABSTATEINDEX, int, bool, int, int, AbnormalStateContainer::EnchantFrom);
        HOOK_PUB_M virtual char so_AbnormalState_Set_Simple(ShineObject*, ABSTATEINDEX, int, bool);
        HOOK_PUB_M virtual char so_AbnormalState_Set_SS_SETABSTATEME(EnumStruct*, EnumStruct*);
        HOOK_PUB_M virtual void so_EscapeFromTarget();
        HOOK_PUB_M virtual void so_AbnormalState_Reset(ABSTATEINDEX);
        HOOK_PUB_M virtual void so_batobj_DamageReserv(int);
        HOOK_PUB_M virtual void so_batobj_DamageApply(int);
        HOOK_PUB_M virtual int so_batobj_GetDamage();
        HOOK_PUB_M virtual void so_mobile_MoveReserve(SHINE_XY_TYPE*, int, MoveManager::MMState, MoveDirect);
        HOOK_PUB_M virtual PROTO_NC_CHAR_MAPLOGIN_ACK* so_fill_PROTO_NC_CHAR_MAPLOGIN_ACK(PROTO_NC_CHAR_MAPLOGIN_ACK*);
        HOOK_PUB_M virtual CHAR_PARAMETER_DATA* so_fill_CHAR_PARAMETER_DATA(CHAR_PARAMETER_DATA*);
        HOOK_PUB_M virtual ShineObject* so_AllOfRange_Getthis();
        HOOK_PUB_M virtual void so_safm_SetCinema(void*);
        HOOK_PUB_M virtual void so_charbasedata(PROTO_NC_CHAR_BASE_CMD*);
        HOOK_PUB_M virtual void so_charsharpdata(PROTO_AVATAR_SHAPE_INFO*);
        HOOK_PUB_M virtual void so_StoreQuestDoing(PROTO_NC_CHAR_QUEST_DOING_CMD*);
        HOOK_PUB_M virtual void so_StoreQuestDone(PROTO_NC_CHAR_QUEST_DONE_CMD*);
        HOOK_PUB_M virtual void so_StoreQuestRead(PROTO_NC_CHAR_QUEST_READ_CMD*);
        HOOK_PUB_M virtual void so_StoreQuestRepeat(PROTO_NC_CHAR_QUEST_REPEAT_CMD*);
        HOOK_PUB_M virtual void so_CharAbstateData(PROTO_NC_CHAR_ABSTATE_CMD*);
        HOOK_PUB_M virtual void so_charskilldata(PROTO_NC_CHAR_SKILL_CMD*);
        HOOK_PUB_M virtual void so_CharChargedBuffData(PROTO_NC_CHAR_CHARGEDBUFF_CMD*);
        HOOK_PUB_M virtual void so_charpassivedata(PROTO_NC_CHAR_SKILL_PASSIVE_CMD*);
        HOOK_PUB_M virtual void so_StoreInventoryFromServer(PROTO_NC_CHAR_ITEM_CMD*);
        HOOK_PUB_M virtual void so_Storegamedata(PROTO_GAMEDATA_CMD*);
        HOOK_PUB_M virtual void so_accountstoragefill(PROTO_NC_ITEMDB_OPENSTORAGE_ACK*);
        HOOK_PUB_M virtual void so_ply_reinforce_reloc(FieldMap*, char*, int, int);
        HOOK_PUB_M virtual char so_ply_dupmenu_canmenuopen(unsigned __int16);
        HOOK_PUB_M virtual void so_ply_dupmenu_Set(unsigned __int16);
        HOOK_PUB_M virtual void so_ply_dupmenu_close(unsigned __int16);
        HOOK_PUB_M virtual int so_ply_TotalSkillEmpower();
        HOOK_PUB_M virtual void so_ply_skillempowerclear();
        HOOK_PUB_M virtual void so_ply_itempickresult(unsigned __int16, unsigned __int16);
        HOOK_PUB_M virtual void so_ply_Getchestinform(PROTO_NC_CHAR_CHESTINFO_CMD*);
        HOOK_PUB_M virtual void so_ply_ClassChange(char);
        HOOK_PUB_M virtual uint so_BodySize();
        HOOK_PUB_M virtual PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD* so_GetCharBriefInfo();
        HOOK_PUB_M virtual void so_mobile_Teleport(SHINE_XY_TYPE*);
        HOOK_PUB_M virtual void so_mobile_Teleport();
        HOOK_PUB_M virtual FieldMap::FM_MarkingError so_door_Build(Name3*, int, int, int, unsigned __int16, unsigned __int16, int, unsigned __int64);
        HOOK_PUB_M virtual FieldMap::FM_MarkingError so_mob_Regenerate(Name3*, int, int, int, unsigned __int16, unsigned __int16, PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD*, unsigned int, ShineObject*, MobRegenClass::MobBreeder*, int, char, unsigned __int64);
        HOOK_PUB_M virtual FieldMap::FM_MarkingError so_effect_EffectBlast(unsigned __int16, Name3*, ShineObject*, Name8*, unsigned int, int, int);
        HOOK_PUB_M virtual FieldMap::FM_MarkingError so_effect_EffectBlast(unsigned __int16, Name3*, int, int, int, Name8*, unsigned int, int, int);
        HOOK_PUB_M virtual uint so_mob_DistanceFromHome();
        HOOK_PUB_M virtual void so_effect_BlastComplete(unsigned __int16);
        HOOK_PUB_M virtual void so_mob_RegenComplete(unsigned __int16);
        HOOK_PUB_M virtual void so_door_BuildComplete(unsigned __int16);
        HOOK_PUB_M virtual void so_mob_ViewAggroList(ShineObject*);
        HOOK_PUB_M virtual void so_mob_AppendAggro(ShineObject*, int);
        HOOK_PUB_M virtual void so_mob_DecreaseAggro(ShineObject*, int);
        HOOK_PUB_M virtual ushort so_mob_MobID();
        HOOK_PUB_M virtual MobDataBox::MobDataBoxIndex* so_mob_DataBox();
        HOOK_PUB_M virtual MobDataBox::MobDataBoxIndex* so_mob_DataBoxforQuest(ShineObject*);
        HOOK_PUB_M virtual MobRace so_mob_Race();
        HOOK_PUB_M virtual uint so_mob_SetWeaponHitTime();
        HOOK_PUB_M virtual uint so_mob_SetWeaponAniTime();
        HOOK_PUB_M virtual ushort so_mob_CanGathered(ShineObjectClass::ShinePlayer*, unsigned __int16*);
        HOOK_PUB_M virtual void so_mob_CanRecover(char);
        HOOK_PUB_M virtual void so_mob_MobAggro(char);
        HOOK_PUB_M virtual char so_mobile_IsEnemy(ShineObject*);
        HOOK_PUB_M virtual void so_mobile_DamageOverTime(ShineObject*, int, ABSTATEINDEX, bool, int*);
        HOOK_PUB_M virtual void so_mobile_HPHealOverTime(ShineObject*, int, ABSTATEINDEX);
        HOOK_PUB_M virtual void so_mobile_SPHealOverTime(ShineObject*, int);
        HOOK_PUB_M virtual int so_mob_SelectWeapon(ShineObject*, char);
        HOOK_PUB_M virtual int so_mob_CurSelectWeapon();
        HOOK_PUB_M virtual FamilyMobList* so_mob_FalimyList();
        HOOK_PUB_M virtual ShineObjectClass::ShineMob* so_mob_FindMyRaceTarget(MobDataBox::MobDataBoxIndex*, int);
        HOOK_PUB_M virtual ShineObjectClass::ShineMob* so_mob_CanMyTarget(MobDataBox::MobDataBoxIndex*, int);
        HOOK_PUB_M virtual ShineObject* so_mob_CanNPCTarget(MobDataBox::MobDataBoxIndex*, int);
        HOOK_PUB_M virtual ushort so_CurrentTargetHandle();
        HOOK_PUB_M virtual void so_EquitEnd();
        HOOK_PUB_M virtual ShineObject* so_CurrentTargetObject();
        HOOK_PUB_M virtual ShineObject* so_ply_CanMyTarget(ShineObjectClass::ShineMob*, int);
        HOOK_PUB_M virtual void so_mob_RescueObject(ShineObject*, char);
        HOOK_PUB_M virtual char so_TentDistance(SHINE_XY_TYPE*);
        HOOK_PUB_M virtual void so_ply_KQRewardStruct(KingdomQuest::KQElement*);
        HOOK_PUB_M virtual void so_ply_KQRewardIndex(const char*);
        HOOK_PUB_M virtual void so_ply_Setpartyslot(CParty::PARTY_SLOT*);
        HOOK_PUB_M virtual void so_ply_partymemberlogin(unsigned int);
        HOOK_PUB_M virtual void so_ply_NewPartyMemberJoin();
        HOOK_PUB_M virtual void so_ply_SaveWeaponTitle();
        HOOK_PUB_M virtual void so_ply_Notice(const char*);
        HOOK_PUB_M virtual void so_ply_WeaponSpeedSet();
        HOOK_PUB_M virtual void so_ply_WeaponRangeSet();
        HOOK_PUB_M virtual void so_ply_PickupMoney(unsigned int);
        HOOK_PUB_M virtual void so_ply_IncDecMoney(unsigned int, char);
        HOOK_PUB_M virtual char so_ply_PickupItem(ShineObject*, ItemTotalInformation*, unsigned __int16);
        HOOK_PUB_M virtual char so_ply_SoloingMode();
        HOOK_PUB_M virtual void so_ply_PartyRecharge(int);
        HOOK_PUB_M virtual void so_ply_FillChargedInven(PROTO_NC_ITEMDB_CHARGED_LIST_ACK*);
        HOOK_PUB_M virtual void so_ply_ChargedWithdraw(PROTO_NC_ITEMDB_CHARGED_WITHDRAW_ACK*);
        HOOK_PUB_M virtual ItemInventoryCell* so_ply_EquipWeapon(ITEM_INVEN*);
        HOOK_PUB_M virtual int so_mobile_MoveSpeed();
        HOOK_PUB_M virtual MoveManager::MMState so_mobile_MoveState();
        HOOK_PUB_M virtual void so_RecalcSpeed(int);
        HOOK_PUB_M virtual void so_mobile_SpeedChange();
        HOOK_PUB_M virtual char so_mobile_DuringFlying();
        HOOK_PUB_M virtual void so_mobile_MoveHalt();
        HOOK_PUB_M virtual void so_ply_ShowBoothItem(ShineObject*, ShineObjectClass::ShinePlayer*, char);
        HOOK_PUB_M virtual void so_ply_BoothTrade(ShineObjectClass::ShinePlayer*, PROTO_NC_BOOTH_ITEMTRADE_REQ*);
        HOOK_PUB_M virtual void so_ply_TradeBoardUnlock(ShineObject*);
        HOOK_PUB_M virtual InventoryLocking::InventoryCellLock* so_ply_GetInventoryLockList();
        HOOK_PUB_M virtual void so_mgcfld_MagicFieldSpread(unsigned __int16, ShineObjectClass::ShineMobileObject*, SkillDataBox::SkillDataIndex*, SHINE_XY_TYPE*, SKILL_EMPOWER*);
        HOOK_PUB_M virtual void so_mgcfld_MagicFieldSpread_Friend(unsigned __int16, ShineObjectClass::ShineMobileObject*, SkillDataBox::SkillDataIndex*, SHINE_XY_TYPE*, SKILL_EMPOWER*);
        HOOK_PUB_M virtual void so_ply_Revival();
        HOOK_PUB_M virtual char so_mobile_TargetModeCheck(TargetState);
        HOOK_PUB_M virtual ushort so_mobile_GetHPChangeOrder();
        HOOK_PUB_M virtual void so_ply_StatIncrease(PROTO_NC_CHAR_STAT_INCPOINTSUC_DB_ACK*);
        HOOK_PUB_M virtual void so_ply_StatDecrease(PROTO_NC_CHAR_STAT_DECPOINTSUC_DB_ACK*);
        HOOK_PUB_M virtual void so_ply_QuestCheck(void(__thiscall*)(ShineQuestDiary* pthis, ShineObject*, ShineObject*, MobDataBox::MobDataBoxIndex*), ShineObject*, ShineObject*, MobDataBox::MobDataBoxIndex*);
        HOOK_PUB_M virtual void so_ply_ItemLotChange(unsigned __int16, int);
        HOOK_PUB_M virtual void so_ply_KQSuccess();
        HOOK_PUB_M virtual void so_ply_KQFail();
        HOOK_PUB_M virtual char so_ply_GetGender();
        HOOK_PUB_M virtual ShineQuestDiary* so_ply_QuestDiary();
        HOOK_PUB_M virtual ushort so_mobile_WhoIsKillMe();
        HOOK_PUB_M virtual ushort so_mobile_WhoIsClickMe();
        HOOK_PUB_M virtual void so_mobile_SetClicker(unsigned __int16);
        HOOK_PUB_M virtual uint so_ply_GetMyGuildNo();
        HOOK_PUB_M virtual void so_ply_SetMyGuildNo(unsigned int);
        HOOK_PUB_M virtual void so_ply_SetMyGuild(GUILD_ZONE*);
        HOOK_PUB_M virtual void so_ply_BroadcastGuildInfo();
        HOOK_PUB_M virtual uint so_mobile_GetGuildRegnum();
        HOOK_PUB_M virtual void so_ply_GuildStorageDeactivate();
        HOOK_PUB_M virtual ushort* so_ply_GetMyGuildStorageHandle();
        HOOK_PUB_M virtual void so_ply_SetMyGuildStorageHandle(unsigned __int16);
        HOOK_PUB_M virtual void so_ply_ItemBuyGuildToken(unsigned int, PROTO_NC_ITEM_BUY_REQ*);
        HOOK_PUB_M virtual ushort* so_ply_GetMyGuildAcademyRewardStorageHandle();
        HOOK_PUB_M virtual void so_ply_SetMyGuildAcademyRewardStorageHandle(unsigned __int16);
        HOOK_PUB_M virtual void so_ply_GuildAcademyRewardStorageDeactivate();
        HOOK_PUB_M virtual void so_ply_GuildAcademyRewardStorageWithdrawAck(PROTO_NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_WITHDRAW_ACK*);
        HOOK_PUB_M virtual void so_ply_GuildAcademyRewardStorageDepositAck(PROTO_NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_DEPOSIT_ACK*);
        HOOK_PUB_M virtual void so_ply_GuildAcademyRewardStorageRewardAck(PROTO_NC_GUILD_ACADEMY_DB_ACADEMY_REWARD_ACK*);
        HOOK_PUB_M virtual void so_ply_BroadcastGuildAcademyInfo();
        HOOK_PUB_M virtual char so_ply_isAcademyGuildMember();
        HOOK_PUB_M virtual uint so_ply_GetMyGuildAcademyNo();
        HOOK_PUB_M virtual void so_ply_SetMyGuildAcademyNo(unsigned int);
        HOOK_PUB_M virtual void so_ply_SetMyGuildAcademy(GUILD_ZONE*);
        HOOK_PUB_M virtual char so_ply_isIAmGuildAcademyMaster();
        HOOK_PUB_M virtual void so_ply_GuildAcademyRewardStoreFill(PROTO_NC_ITEMDB_GUILD_ACADEMY_REWARD_STORAGE_OPEN_ACK*);
        HOOK_PUB_M virtual void so_ply_GuildAcademyRewardStoreGradeFill(char);
        HOOK_PUB_M virtual char so_ply_isGuildAcademyRewardStoreGrade();
        HOOK_PUB_M virtual void so_ply_GuildAcademyRewardStorageRewardZoneRng(PROTO_NC_GUILD_ACADEMY_DB_ACADEMY_REWARD_ACK*);
        HOOK_PUB_M virtual void so_ply_GuildAcademyRewordSrorageItemInfoCmd(GUILD_ACADEMY_REWARDSTORAGE_ITEM_INFO_CMD*, char);
        HOOK_PUB_M virtual void so_ply_GuildReName(char, Name4);
        HOOK_PUB_M virtual void so_ply_GuildReType(char, char);
        HOOK_PUB_M virtual void so_ply_GuildReNameItemUseSuccess();
        HOOK_PUB_M virtual void so_ply_GuildReTypeItemUseSuccess();
        HOOK_PUB_M virtual void so_ply_BriefLink(Name3*, SHINE_XY_TYPE*);
        HOOK_PUB_M virtual char* so_mobile_GetIdxName();
        HOOK_PUB_M virtual void so_bandit_ChangeType(char);
        HOOK_PUB_M virtual char so_IsMob();
        HOOK_PUB_M virtual void so_relink(int);
        HOOK_PUB_M virtual int so_Prison_Go(unsigned __int16);
        HOOK_PUB_M virtual void so_Prison_End(Name3*, SHINE_XY_TYPE*);
        HOOK_PUB_M virtual void so_scene_MovePathSet(int, int, MoveManager::MMState);
        HOOK_PUB_M virtual void so_scene_ItemAttrSet(unsigned __int16, char*);
        HOOK_PUB_M virtual void so_scene_CreateItem(unsigned __int16);
        HOOK_PUB_M virtual void so_scene_EraseItem(unsigned __int16, int);
        HOOK_PUB_M virtual void so_scene_DetectRange(int);
        HOOK_PUB_M virtual void so_scene_Duplicate(int);
        HOOK_PUB_M virtual char so_scene_IsIdle();
        HOOK_PUB_M virtual void so_ply_HorseFeed();
        HOOK_PUB_M virtual ShineObjectClass::BattleCamp so_mobile_BattleCamp();
        HOOK_PUB_M virtual void so_ply_AllCastCancel();
        HOOK_PUB_M virtual void so_mobile_DeadCheck(DeadCheck::DC_DeadCause);
        HOOK_PUB_M virtual void so_SendInform2Admin(ShineObjectClass::ShinePlayer*);
        HOOK_PUB_M virtual void so_ply_PartyInformInit();
        HOOK_PUB_M virtual int so_ply_ChargedStatPlus();
        HOOK_PUB_M virtual void so_ply_RoarItemUseSuccess();
        HOOK_PUB_M virtual void so_ply_SkillEraseItemUseSuccess();
        HOOK_PUB_M virtual ShineObjectClass::RemoveWhen so_ply_RemoveWhen();
        HOOK_PUB_M virtual void so_ply_KeepFromChat(ShineObjectClass::ShinePlayer*);
        HOOK_PUB_M virtual SHINE_XY_TYPE* so_mob_SightCenter(int, SHINE_XY_TYPE*);
        HOOK_PUB_M virtual void so_mob_TargetChange();
        HOOK_PUB_M virtual void so_ply_Return2Quest(int);
        HOOK_PUB_M virtual void so_mob_SetGuildRegNum(unsigned int);
        HOOK_PUB_M virtual char so_mobile_MobAggroRate();
        HOOK_PUB_M virtual void so_ply_ItemBreakSuccess(PROTO_NC_ITEMDB_ITEMBREAKSUC_ACK*);
        HOOK_PUB_M virtual void so_ply_ItemBreakFail(PROTO_NC_ITEMDB_ITEMBREAKFAIL_ACK*);
        HOOK_PUB_M virtual void so_LogoutLog(char*);
        HOOK_PUB_M virtual void so_ply_SparrowWingExpand(int);
        HOOK_PUB_M virtual void so_ply_SparrowWingFly();
        HOOK_PUB_M virtual void so_ply_ItemUseResultPacket(int, char);
        HOOK_PUB_M virtual void so_ply_ChestBoxOpenAck(PROTO_NC_ITEMDB_CHESTITEM_ACK*);
        HOOK_PUB_M virtual void so_ply_Summon2GuildTournament(PROTO_NC_GUILD_TOURNAMENT_START_CMD*, FieldOption::GuildTournamentMapStr*, MapInfo*);
        HOOK_PUB_M virtual void so_ply_Send2GuildTournamentLogIn(PROTO_NC_GUILD_TOURNAMENT_START_CMD*, char);
        HOOK_PUB_M virtual void so_ply_GuildTournament_isSummon();
        HOOK_PUB_M virtual void so_ply_FlagCaptureCast(unsigned __int16);
        HOOK_PUB_M virtual ushort so_ply_GuildTournamentJoinNew(PROTO_NC_GUILD_TOURNAMENT_ZONE_JOIN_NEW_REQ*);
        HOOK_PUB_M virtual ushort so_IsInWeapon();
        HOOK_PUB_M virtual void so_ply_LoginIPSet(int, int, int, int);
        HOOK_PUB_M virtual void so_ply_FromWhere(char);
        HOOK_PUB_M virtual char so_ply_GetFromWhere();
        HOOK_PUB_M virtual char so_ply_Script_CostumeCreate(unsigned __int16, unsigned __int16, char*);
        HOOK_PUB_M virtual char so_ply_Script_CostumeTakeOff(unsigned __int16, unsigned __int16);
        HOOK_PUB_M virtual char so_ply_WeddingPrepareItem();
        HOOK_PUB_M virtual void so_ply_WeddingData(PROTO_NC_CHAR_WEDDINGDATA_ACK*);
        HOOK_PUB_M virtual PROTO_NC_CHAR_WEDDINGDATA_ACK* so_ply_WeddingStatus();
        HOOK_PUB_M virtual void so_ply_WeddingInfoUpdate(PROTO_NC_CHAR_WEDDINGDATA_ACK*);
        HOOK_PUB_M virtual void so_ply_DivorceProcess();
        HOOK_PUB_M virtual void so_ply_AdminCommand(char*, int);
        HOOK_PUB_M virtual char so_ply_ItemLotInspecting(char);
        HOOK_PUB_M virtual ItemLotInspector* so_ply_GetItemLotInspector();
        HOOK_PUB_M virtual int so_ply_CalcTotalLot(unsigned __int16, char*, char);
        HOOK_PUB_M virtual ushort so_ply_ItemLotCheck(SHINE_ITEM_REGISTNUMBER*);
        HOOK_PUB_M virtual char so_ply_ServerMenuactor_sma_IsReady();
        HOOK_PUB_M virtual void so_UnlearnSkillAck(PROTO_NC_SKILL_ERASE_ACK*);
        HOOK_PUB_M virtual char so_mobile_ICanDamageTo(ShineObject*, char*);
        HOOK_PUB_M virtual MiscDataTable::MiscData_Skill* so_MiscTable();
        HOOK_PUB_M virtual void so_serv_SetMaster(ShineObjectClass::ShineMobileObject*, MiscDataTable::MiscData_Skill*);
        HOOK_PUB_M virtual void so_serv_SetTarget(ShineObject*);
        HOOK_PUB_M virtual void so_mob_AggroAdjust(ShineObject*, int);
        HOOK_PUB_M virtual void so_ply_Volley();
        HOOK_PUB_M virtual void so_ply_TargetChange(ShineObject*);
        HOOK_PUB_M virtual void so_ply_AbstateMatchEquip();
        HOOK_PUB_M virtual void so_ply_ReinforceRemoveWeapon();
        HOOK_PUB_M virtual void so_ply_ReinforceRemoveShield();
        HOOK_PUB_M virtual void so_ply_ReinforceRemoveEquip(ItemEquipEnum);
        HOOK_PUB_M virtual int so_smo_CrossCounterDamage(ShineObjectClass::ShineMobileObject*);
        HOOK_PUB_M virtual ShineObjectClass::ShineMobileObject* so_serv_FindMaster();
        HOOK_PUB_M virtual void so_serv_ServantMissionSet(MiscDataTable::MiscData_Skill*);
        HOOK_PUB_M virtual char so_mob_CanBeAttackedByPlayer(ShineObjectClass::ShinePlayer*);
        HOOK_PUB_M virtual void so_ply_FillRewardInven(PROTO_NC_CHAR_GET_ITEMLIST_BY_TYPE_NUM_ACK*);
        HOOK_PUB_M virtual void so_ply_HolyPromiseSet(unsigned int);
        HOOK_PUB_M virtual void so_ply_HolyPromiseCenUseTry(unsigned int);
        HOOK_PUB_M virtual void so_ply_HolyPromiseCenUseSuccess();
        HOOK_PUB_M virtual void so_ply_HolyPromiseCenFrom(PROTO_NC_HOLY_PROMISE_CENTRANSFER_RNG*);
        HOOK_PUB_M virtual void so_ply_HolyPromiseGetCenReward(PROTO_NC_HOLY_PROMISE_DB_GET_CEN_REWARD_ACK*);
        HOOK_PUB_M virtual void so_ply_HolyPromiseWithdrawCenReward(PROTO_NC_HOLY_PROMISE_DB_WITHDRAW_CEN_REWARD_ACK*);
        HOOK_PUB_M virtual void so_mobile_SetNaturalEnemy(AbnormalStateDictionary::AbState::AbStateStr::AbStateStrArgument*);
        HOOK_PUB_M virtual AbnormalStateDictionary::AbState::AbStateStr::AbStateStrArgument* so_mobile_GetNaturalEnemy();
        HOOK_PUB_M virtual char sp_IsPreventAttack();
        HOOK_PUB_M virtual char sp_IsEthereal();
        HOOK_PUB_M virtual char so_mobile_IsInFear();
        HOOK_PUB_M virtual char so_ply_IsInBoothInterior();
        HOOK_PUB_M virtual char so_ply_RegistNumberVarifyCheck(PROTO_NC_CHAR_REGNUM_VARIFICATION_ACK*);
        HOOK_PUB_M virtual void so_ply_WeaponEndureChangeAck(PROTO_NC_ITEMDB_WEAPONENDURE_CHARGE_ACK*);
        HOOK_PUB_M virtual void so_ply_ShieldEndureChangeAck(PROTO_NC_ITEMDB_SHIELDENDURE_CHARGE_ACK*);
        HOOK_PUB_M virtual void so_ply_ChangeCharIDUseAck(PROTO_NC_USER_CONNECTION_DB_CHANGE_CHAR_ID_ITEM_USE_ACK*);
        HOOK_PUB_M virtual void so_mobile_Broadcast2ndTarget(ShineObject*, int);
        HOOK_PUB_M virtual ShineObject* so_GetTargetObject();
        HOOK_PUB_M virtual void so_Mob_SetSendTagetInfo(char);
        HOOK_PUB_M virtual char so_IsTarget();
        HOOK_PUB_M virtual void so_mobile_SendMyMoveInfo(ShineObject*);
        HOOK_PUB_M virtual void so_mob_RoamingPathSet(MobRoaming::MobRoamingPath*);
        HOOK_PUB_M virtual MobRoaming::MobRoamingPath* so_mob_RoamingPathGet();
        HOOK_PUB_M virtual void so_ply_StoreItem(ITEM_INVEN*, ItemTotalInformation*, ITEM_INVEN*);
        HOOK_PUB_M virtual char InteractWithNPC(ShineObject*);
        HOOK_PUB_M virtual void so_ply_ToNormalLoc(int);
        HOOK_PUB_M virtual void so_ReinforceMove(SHINE_XY_TYPE*, int, MoveDirect, PROTO_NC_ACT_SOMEONEMOVEWALK_CMD*, char);
        HOOK_PUB_M virtual void registerObsersver(Observer*);
        HOOK_PUB_M virtual void unregisterObsersver(Observer*);
        HOOK_PUB_M virtual void unregisterObsersvers(ShineObject*);
        HOOK_PUB_M virtual void notifyObservers(IObserver::Event, unsigned int, int);
        HOOK_PUB_M virtual bool hasObserver(ShineObject*);
        HOOK_PUB_M virtual void sp_DoEmotion(unsigned __int16, char);
        HOOK_PUB_M virtual void sm_UseSkillSimple(SkillDataBox::SkillDataIndex*, ShineObject*, SHINE_XY_TYPE*);
        HOOK_PUB_M virtual void so_mobile_StopHere();
        HOOK_PUB_M virtual void so_ply_SendMoveFail();
        HOOK_PUB_M virtual void smo_ply_ReinforceStopHere();
        HOOK_PUB_M virtual ushort so_getDetectRange();
        HOOK_PUB_M virtual void so_ply_InvenWrite(char*);
        HOOK_PUB_M virtual void so_smo_AbStateKeepTimeAdd(SubState, int);
        HOOK_PUB_M virtual int so_smo_SPExhByAbState();
        HOOK_PUB_M virtual char so_smo_AbnormalStateAttribute(MiscDataTable::MiscData_VarifyByAbstate::AbnormalStateAttr);
        HOOK_PUB_M virtual int so_smo_RangeEvation();
        HOOK_PUB_M virtual char so_smo_CanEnchant(ABSTATEINDEX, int);
        HOOK_PUB_M virtual ClientSession* so_ply_GetClientSession();
        HOOK_PUB_M virtual char so_ply_IsLink_OutMap_AndSendErrorMsg();
        HOOK_PUB_M virtual char so_ply_IsLink_In_MapAndSendErrorMsg();
        HOOK_PUB_M virtual void so_NPCRevive(ShineObjectClass::ShinePlayer*);
        HOOK_PUB_M virtual void so_npc_FromTable();
        HOOK_PUB_M virtual Raid* so_GetRaid();
        HOOK_PUB_M virtual void so_SetRaid(Raid*);
        HOOK_PUB_M virtual bool so_GetInsDunGeonInRegNoAndType(INSTANCE_DUNGEON::CATEGORY*, unsigned int*);
        HOOK_PUB_M virtual void so_mob_ReturnToRegen();
        HOOK_PUB_M virtual void so_FillBriefABState(ABSTATE_INFORMATION*, char*);
        HOOK_PUB_M virtual void so_ReviveByItem();
        HOOK_PUB_M virtual void so_AmpersandCommand_LevelUp();
        HOOK_PUB_M virtual char so_DiceItemPickInit(ShineObject*);
        HOOK_PUB_M virtual char so_DiceItemStart(ShineObject*, bool, unsigned __int16*);
        HOOK_PUB_M virtual char so_IsDiceGamePlay();
        HOOK_PUB_M virtual void so_SetHP(int);
        HOOK_PUB_M virtual void so_ply_GtItemEffectMsg(unsigned __int16);
        HOOK_PUB_M virtual void so_SpamRecvDataFromWM(PROTO_NC_CHAR_GET_CHAT_BLOCK_SPAMER_CMD*);
        HOOK_PUB_M virtual void so_SpamSendDataToCharDB();
        HOOK_PUB_M virtual void so_mob_SetLifeTime(unsigned int);
        HOOK_PUB_M virtual void so_SetAutoSaveTime(unsigned int, int);
        HOOK_PUB_M virtual char sp_FreeStat_Get_DecreaseNum(CHARSTATDISTSTR);
        HOOK_PUB_M virtual char sp_CharFreeStat_IsLock();
        HOOK_PUB_M virtual void sp_CharFreeStat_Lock();
        HOOK_PUB_M virtual void sp_CharFreeStat_UnLock();
        HOOK_PUB_M virtual void so_ply_FreeStat_Increase(PROTO_NC_CHAR_FREESTAT_SET_DB_ACK*);
        HOOK_PUB_M virtual void so_ply_FreeStat_Decrease(PROTO_NC_CHAR_FREESTAT_SET_DB_ACK*);
        HOOK_PUB_M virtual void so_BashStop();
        HOOK_PUB_M virtual char so_GetIsQuestRewardReq();
        HOOK_PUB_M virtual void so_SetIsQuestRewardReq(char);
        HOOK_PUB_M virtual void so_SetSpamerChatBan(unsigned int);
        HOOK_PUB_M virtual void so_Send_NC_CHARSAVE_2WLDMAN_SKILL_CMD(NETCOMMAND*);
        HOOK_PUB_M virtual char so_mob_GetbUseNextSkill();
        HOOK_PUB_M virtual void so_mob_SetbUseNextSkill(char);
        HOOK_PUB_M virtual char so_Gamble_IsGambleHouse();
        HOOK_PUB_M virtual void so_Gamble_SetPrevMapName(Name3);
        HOOK_PUB_M virtual void so_Gamble_CharCoinData(PROTO_NC_CHAR_COININFO_CMD*);
        HOOK_PUB_M virtual ulong so_Gamble_CurrentCoin();
        HOOK_PUB_M virtual void so_Gamble_StoreCoin(unsigned __int64);
        HOOK_PUB_M virtual void so_Gamble_ChangeCoin();
        HOOK_PUB_M virtual ulong so_Gamble_CurrentExchangedCoin();
        HOOK_PUB_M virtual void so_Gamble_StoreExchangedCoin(unsigned __int64);
        HOOK_PUB_M virtual void so_Gamble_ChangeExchangedCoin();
        HOOK_PUB_M virtual char so_Gamble_CanJoinGamble(GAMBLE_TYPE);
        HOOK_PUB_M virtual char so_Gamble_IsJoinThisGamble(GAMBLE_TYPE);
        HOOK_PUB_M virtual char so_Gamble_IsJoinAnyGamble(GAMBLE_TYPE*);
        HOOK_PUB_M virtual char so_Gamble_SetGambleType(GAMBLE_TYPE);
        HOOK_PUB_M virtual char so_Gamble_IsCanSessionCloseing();
        HOOK_PUB_M virtual uint so_mob_GetNextRoamingWaitTime();
        HOOK_PUB_M virtual void so_mob_SetNextRoamingWaitTime(unsigned int);
        HOOK_PUB_M virtual char so_mob_CheckNextRoamingWait();
        HOOK_PUB_M virtual void so_ply_EndofTrade(unsigned __int16, int);
        HOOK_PUB_M virtual void so_ply_ReactionNpcHandle();
        HOOK_PUB_M virtual void so_ply_NpcReaction(ReactionTypeEnum);
        HOOK_PUB_M virtual void so_ply_CapsuleItemOpenAck(PROTO_NC_ITEMDB_CAPSULEITEM_ACK*);
        HOOK_PUB_M virtual void so_npc_SetLocation(Name3, int, int, int);
        HOOK_PUB_M virtual void so_ply_SlotMachineDBResult(PROTO_NC_GAMBLE_SLOTMACHINE_DB_RESULT_ACK*);
        HOOK_PUB_M virtual void so_ply_IBurstJackPot(unsigned __int64);
        HOOK_PUB_M virtual char* so_ply_GodOfSlotMachine();
        HOOK_PUB_M virtual void so_AITraining(ShineObject*);
        HOOK_PUB_M virtual void so_AILearn(LuaScriptScenario*);
        HOOK_PUB_M virtual int so_AIScriptFuncExec(char*, LuaScriptArgument::LuaArgumentDefault*);
        HOOK_PUB_M virtual int so_AIScriptFuncExec(std::basic_string<char, std::char_traits<char>, std::allocator<char> >*, LuaScriptArgument::LuaArgumentDefault*);
        HOOK_PUB_M virtual int so_AIScriptFuncExec(char*, char*);
        HOOK_PUB_M virtual char so_LuaFunctionSet(std::basic_string<char, std::char_traits<char>, std::allocator<char> >*, const char*);
        HOOK_PUB_M virtual int so_mob_SetWeaponAsScript(char);
        HOOK_PUB_M virtual ushort so_mob_CurrentTarget();
        HOOK_PUB_M virtual char so_mob_SkillRegistAtScript(ShineObject*, unsigned __int16);
        HOOK_PUB_M virtual char so_mob_ParamSetAtScript(const char*, int);
        HOOK_PUB_M virtual char so_mob_SkillBlastAtScript(ShineObject*, unsigned __int16);
        HOOK_PUB_M virtual int so_mob_GetAggroList(std::vector<unsigned short, std::allocator<unsigned short> >*);
        HOOK_PUB_M virtual ShineObjectClass::ShineMobileObject* so_ShineMobileObject();
        HOOK_PUB_M virtual char so_mob_SkillParameterSet(unsigned __int16);
        HOOK_PUB_M virtual char so_mob_SkillParameterSetAtScript(SkillDamageParameterAtScript*);
        HOOK_PUB_M virtual void so_mgcfld_FirstTickDelay();
        HOOK_PUB_M virtual uint so_mob_GetMonEXP();
        HOOK_PUB_M virtual void so_mob_SetMobResist(unsigned __int16*, unsigned __int16);
        HOOK_PUB_M virtual void so_mob_SetEnemyDetect(EnemyDetect);
        HOOK_PUB_M virtual void so_mob_SetEnemyDetect(char*);
        HOOK_PUB_M virtual void so_mob_SetIsPlayerSide(int);
        HOOK_PUB_M virtual void so_mob_IsItemDropSetAtScript(char);
        HOOK_PUB_M virtual void so_mob_SetItemDropMobID(unsigned __int16);
        HOOK_PUB_M virtual void so_SetMovePacket(unsigned __int16, PROTO_NC_ACT_SOMEONEMOVEWALK_CMD*);
        HOOK_PUB_M virtual ShineObjectClass::ShinePlayer* so_ToShinePlayer();
        HOOK_PUB_M virtual char so_GetItemLot(const char*, unsigned __int64*, char*);
        HOOK_PUB_M virtual char so_ply_ToggleSkill_IsOn(unsigned __int16);
        HOOK_PUB_M virtual void so_ply_ToggleSkill_On(SkillDataBox::SkillDataIndex*, SKILL_EMPOWER*);
        HOOK_PUB_M virtual void so_ply_ToggleSkill_Off(SkillDataBox::SkillDataIndex*);
        HOOK_PUB_M virtual void so_ply_ToggleSkill_AllOff();
        HOOK_PUB_M virtual void so_ply_DmgCoolTimeDown();
        HOOK_PUB_M virtual int so_ply_GetDamageAbsorb();
        HOOK_PUB_M virtual void so_ply_SetDamageAbsorb(int);
        HOOK_PUB_M virtual int so_ply_GetRemainingDamageAbsorb();
        HOOK_PUB_M virtual void so_ply_SetRemainingDamageAbsorb(int);
        HOOK_PUB_M virtual int so_ply_CheckDamageAbsorption(int);
        HOOK_PUB_M virtual char smo_GetFlagDamageAbsorb();
        HOOK_PUB_M virtual void smo_SetFlagDamageAbsorb(char);
        HOOK_PUB_M virtual void smo_LightningWaveSkill(SkillDataBox::SkillDataIndex*, unsigned __int16, ShineObject*, ShineObject*, unsigned __int16, int);
        HOOK_PUB_M virtual void so_ply_PassiveSetAbstate(PS_ConditionEnum, ShineObject*, char, unsigned int);
        HOOK_PUB_M virtual void so_ply_CardCollect(PROTO_NC_CHAR_CARDCOLLECT_CMD*);
        HOOK_PUB_M virtual void so_ply_CardCollectBookMark(PROTO_NC_CHAR_CARDCOLLECT_BOOKMARK_CMD*);
        HOOK_PUB_M virtual void so_ply_CardCollectReward(PROTO_NC_CHAR_CARDCOLLECT_REWARD_CMD*);
        HOOK_PUB_M virtual void so_ply_CollectCardOpen(PROTO_NC_ITEMDB_ITEMINFO_ACK*);
        HOOK_PUB_M virtual void so_ply_CardRegist(unsigned __int16, unsigned int, int, CHARACTER_TITLE_TYPE);
        HOOK_PUB_M virtual void so_ply_CardBookmarkRegist(PROTO_NC_COLLECT_BOOKMARK_REGIST_ACK*);
        HOOK_PUB_M virtual void so_InitAIScript();
        HOOK_PUB_M virtual ShineObject* so_mob_GetTopAggroTarget();
        HOOK_PUB_M virtual ShineObject* so_smo_GetRandomTarget_Object(SkillDataBox::SkillDataIndex*, unsigned int, ShineObject*);
        HOOK_PUB_M virtual char so_smo_GetRandomTarget_Locate(SkillDataBox::SkillDataIndex*, SHINE_XY_TYPE*);
        HOOK_PUB_M virtual void so_CameraMoveSendBriefInfo(SHINE_XY_TYPE, int);
        HOOK_PUB_M virtual ShineObjectClass::ShineMob* so_ToShineMob();
        HOOK_PUB_M virtual void so_ply_SendMenuOpenReq(ShineObject*);
        HOOK_PUB_M virtual void so_SetAnimation(const char*);
        HOOK_PUB_M virtual void so_ResetAnimation();
        HOOK_PUB_M virtual void so_SetForcedAnimation(const char*);
        HOOK_PUB_M virtual void so_mob_SetDeadDelayTime(unsigned int);
        HOOK_PUB_M virtual char so_mob_SkillParameterSet_WeaponIndex(char);
        HOOK_PUB_M virtual char so_ply_IsRebirth();
        HOOK_PUB_M virtual void so_ply_setIsRebirth(char);
        HOOK_PUB_M virtual int so_ply_HealRate();
        HOOK_PUB_M virtual void so_ply_setHealRate(int);
        HOOK_PUB_M virtual void so_serv_SetRoamingData(MiscDataTable::MiscData_Skill::MDS_ROAMINGTYPE, int, int, SHINE_XY_TYPE);
        HOOK_PUB_M virtual char so_serv_ServantRoaming(int*, int*);
        HOOK_PUB_M virtual int so_serv_GetRoamingType();
        HOOK_PUB_M virtual void so_serv_LastExplosionReady();
        HOOK_PUB_M virtual void so_ply_setSwingTime(unsigned int);
        HOOK_PUB_M virtual uint so_ply_getSwingTime();
        HOOK_PUB_M virtual char so_MoverSystem_GetOff(int);
        HOOK_PUB_M virtual char so_MoverSystem_NoDamage();
        HOOK_PUB_M virtual ShineObject* so_MoverSystem_GetMover();
        HOOK_PUB_M virtual void so_MoverSystem_SetMover(ShineObject*);
        HOOK_PUB_M virtual char so_MoverSystem_GetMoverSlot();
        HOOK_PUB_M virtual void so_MoverSystem_SetMoverSlot(char);
        HOOK_PUB_M virtual void so_MoverSystem_GetLinkData(MOVER_LINKDATA*);
        HOOK_PUB_M virtual void so_MoverSystem_SetLinkData(MOVER_LINKDATA*);
        HOOK_PUB_M virtual void so_MoverSystem_ClearLinkData();
        HOOK_PUB_M virtual void so_MoverSystem_Feeding();
        HOOK_PUB_M virtual char so_MoverSystem_ChargedMoverNotHungry();
        HOOK_PUB_M virtual void so_smo_SetLocation(SHINE_XY_TYPE, char);
        HOOK_PUB_M virtual void so_smv_ClearMoverInfo();
        HOOK_PUB_M virtual char so_smv_SummonMover(Name3*, int, int, int, unsigned int, unsigned int, unsigned __int64);
        HOOK_PUB_M virtual void so_smv_SetMaster_RegNum(unsigned int);
        HOOK_PUB_M virtual uint so_smv_GetMaster_RegNum();
        HOOK_PUB_M virtual void so_smv_SetMaster_Object(ShineObject*);
        HOOK_PUB_M virtual ShineObject* so_smv_GetMaster_Object();
        HOOK_PUB_M virtual void so_smv_SetMoverItemInfo(ItemAttributeClass*, ItemTotalInformation*);
        HOOK_PUB_M virtual char so_smv_GetOn(ShineObject*, int);
        HOOK_PUB_M virtual char so_smv_GetOff(ShineObject*, int);
        HOOK_PUB_M virtual void so_smv_GetOffAll(int);
        HOOK_PUB_M virtual ushort so_smv_CanUseFeedItem(unsigned __int16);
        HOOK_PUB_M virtual char so_smv_Feeding();
        HOOK_PUB_M virtual char so_smv_MoveWalk(PROTO_NC_ACT_MOVEWALK_CMD*, ShineObject*);
        HOOK_PUB_M virtual char so_smv_MoveRun(PROTO_NC_ACT_MOVEWALK_CMD*, ShineObject*);
        HOOK_PUB_M virtual void so_smv_MoveStop(PROTO_NC_ACT_STOP_REQ*, ShineObject*);
        HOOK_PUB_M virtual char so_smv_GetMaxSlotNum();
        HOOK_PUB_M virtual ShineObject* so_smv_GetPassenger(char);
        HOOK_PUB_M virtual void so_smv_PassengerNotice(const char*);
        HOOK_PUB_M virtual uint so_smv_GetMoverID();
        HOOK_PUB_M virtual char so_smv_GetMyBookingSlot(unsigned int);
        HOOK_PUB_M virtual void so_smv_SkillBash_Object(unsigned __int16, unsigned __int16, ShineObject*);
        HOOK_PUB_M virtual void so_smv_SkillBash_Location(unsigned __int16, SHINE_XY_TYPE, ShineObject*);
        HOOK_PUB_M virtual char so_smv_MasterSetAbsCheck(ShineObject*, ABSTATEINDEX, int, AbnormalStateDictionary::AbState::AbStateStr*, unsigned int, int, int, int, AbnormalStateContainer::EnchantFrom, AbnormalStateContainer::AbStateElementSetData*);
        HOOK_PUB_M virtual void so_smv_MasterResetAbsCheck(ABSTATEINDEX);
        HOOK_PUB_M virtual char so_smv_GetMoverGrade();
        HOOK_PUB_M virtual void so_smv_SetMoverGrade(char);
        HOOK_PUB_M virtual void so_ply_getBanditBriefinfo(PROTO_NC_BRIEFINFO_LOGINCHARACTER_CMD*);
        HOOK_PUB_M virtual int so_ply_CheckCharType(ChrClassType);
        HOOK_PUB_M virtual void so_ply_ArrangeInvenInit();
        HOOK_PUB_M virtual char so_ply_ArrangeInvenDelayCheck();
        HOOK_PUB_M virtual int so_ply_IsArrangeInven();
        HOOK_PUB_M virtual void so_ply_SetArrangeInven(int);
        HOOK_PUB_M virtual void so_ply_ArrangeInven();
        HOOK_PUB_M virtual void so_Send_NC_CHARSAVE_2WLDMAN_QUEST_DONE_CMD(NETCOMMAND*);
        HOOK_PUB_M virtual void so_AccountStorageAnywhereOpen();
        HOOK_PUB_M virtual void so_AccountStorageAnywhereClose();
        HOOK_PUB_M virtual int so_ply_JobChangeDamageUp(ShineObject*, int);
        HOOK_PUB_M virtual int so_ply_IsEquipItem(unsigned int, unsigned int);
        HOOK_PUB_M virtual int so_ply_DecreaseDmgPassiveSkill(ShineObject*, int);
        HOOK_PUB_M virtual CQuestZone* so_ply_GetQuestZone();
        HOOK_PUB_M virtual void so_ply_SendFieldAttribute();
        HOOK_PUB_M virtual void so_mob_SetAnimationLevel(char);
        HOOK_PUB_M virtual char so_mob_GetAnimationLevel();
        HOOK_PUB_M virtual char so_mob_IsNPC();
        HOOK_PUB_M virtual void so_SendSpeedInformation(char);
        HOOK_PUB_M virtual MOVE_STATE smo_GetMoveState();
        HOOK_PUB_M virtual uint smo_GetMoveStateStartTime();
        HOOK_PUB_M virtual void so_ply_PartyZoneJoinCmd(unsigned int);
        HOOK_PUB_M virtual void so_ply_PartyZoneLeaveCmd();
        HOOK_PUB_M virtual void so_ply_EquipmentChange(unsigned __int16, int, ItemTotalInformation*, char);
        HOOK_PUB_M virtual void so_ply_ViewSlot_Equip(unsigned __int16);
        HOOK_PUB_M virtual void so_ply_ViewSlot_UnEquip(int);
        HOOK_PUB_M virtual void so_ply_ViewSlot_UnEquipAll(char);
        HOOK_PUB_M virtual void so_ply_ViewSlot_EquipInfoSend();
        HOOK_PUB_M virtual void so_ply_ViewSlot_EquipInfoClear();
        HOOK_PUB_M virtual void so_ply_DecoActList_Cehck();
        HOOK_PUB_M virtual void so_ply_PlaySound(const char*);
        HOOK_PUB_M virtual void so_ply_ShowCinematicText(const char*);
        HOOK_PUB_M virtual void so_ply_EndCinematicText();
        HOOK_PUB_M virtual void so_ply_EffectMsg(unsigned int);
        HOOK_PUB_M virtual void so_ply_Sen_InitLP();
        HOOK_PUB_M virtual uint so_ply_Sen_GetLP();
        HOOK_PUB_M virtual uint so_ply_Sen_MaxLP();
        HOOK_PUB_M virtual void so_ply_Sen_GainLP(int);
        HOOK_PUB_M virtual void so_ply_Sen_LostLP(int);
        HOOK_PUB_M virtual uint so_ply_Sen_GetLPRecover();
        HOOK_PUB_M virtual void so_ply_Sen_RecalcLPRecover();
        HOOK_PUB_M virtual uint so_ply_Sen_GetLPRecoverInterval();
        HOOK_PUB_M virtual char so_ply_Sen_LP_Tick();
        HOOK_PUB_M virtual void so_RecoverAlreadyDead();
        HOOK_PUB_M virtual int so_smo_LastDamageOperation(int, bool);
        HOOK_PUB_M virtual ulong so_ply_MakeLayerRegNum(LAYER_TYPE, LAYER_NUMBER_TYPE);
        HOOK_PUB_M virtual void so_ply_MoveNewLayer(LAYER_TYPE, LAYER_NUMBER_TYPE);
        HOOK_PUB_M virtual void so_ply_MoveOtherLayer(unsigned __int64);
        HOOK_PUB_M virtual void so_ply_DeleteObject_AllOfRange();
        HOOK_PUB_M virtual void so_ply_MoveNewLayer_AllInMap(LAYER_TYPE, LAYER_NUMBER_TYPE);
        HOOK_PUB_M virtual void so_ply_MoveOtherLayer_AllInMap(unsigned __int64);
        HOOK_PUB_M virtual void so_ply_DeleteObject_AllInMap();
        HOOK_PUB_M virtual void so_ply_LayerMoverRideOn(MOVER_SYSTEM_TYPE, int);
        HOOK_PUB_M virtual void so_ply_SendBriefInfo_MoveLayer();
        HOOK_PUB_M virtual void so_smo_StaticDamage(int);
        HOOK_PUB_M virtual void so_serv_SetFlag(const char*, char);
        HOOK_PUB_M virtual void so_serv_InitFlag();
        HOOK_PUB_M virtual void so_serv_SetMobCanDamageTo(int);
        HOOK_PUB_M virtual int so_serv_GetMobCanDamageTo();
        HOOK_PUB_M virtual void so_mob_SendReallyKill();
        HOOK_PUB_M virtual int so_ply_LoginTutorialMap();
        HOOK_PUB_M virtual void so_ply_SetTutorialInfo(PROTO_TUTORIAL_INFO*);
        HOOK_PUB_M virtual PROTO_TUTORIAL_INFO* so_ply_GetTutorialInfo();
        HOOK_PUB_M virtual void so_ply_LevelUpAtLua();
        HOOK_PUB_M virtual void so_SetKQTeamType(char);
        HOOK_PUB_M virtual char so_GetKQTeamType();
        HOOK_PUB_M virtual char so_smo_TargetIsEnemyKQTeam(ShineObject*);
        HOOK_PUB_M virtual char so_ply_IsKQJoiner();
        HOOK_PUB_M virtual void so_ply_SendCanUseReviveItem();
        HOOK_PUB_M virtual void so_ply_ItemBuyItemMoney(PROTO_NC_ITEM_BUY_REQ*, unsigned __int16, unsigned int);
        HOOK_PUB_M virtual void so_ply_DePorymorph();
        HOOK_PUB_M virtual void so_drpitm_bQuestDropItem_Set(char);
        HOOK_PUB_M virtual char so_drpitm_bQuestDropItem_Get();
        HOOK_PUB_M virtual char so_ply_QuestItemCheck(unsigned __int16);
        HOOK_PUB_M virtual char so_ply_GetChatFontColorID();
        HOOK_PUB_M virtual void so_ply_SetChatFontColorID(char);
        HOOK_PUB_M virtual char so_ply_GetChatBalloonColorID();
        HOOK_PUB_M virtual void so_ply_SetChatBalloonColorID(char);
        HOOK_PUB_M virtual void so_ply_ChatColorInfoApply(PROTO_NC_ITEMDB_CHAT_COLOR_CHANGE_ACK*);
        HOOK_PUB_M virtual void so_ply_ChatColorInfoClear(ChargedItemEffect*);
        HOOK_PUB_M virtual ShineObject* so_PetSystem_GetPet();
        HOOK_PUB_M virtual void so_SetAnimationBriefInfo(const char*);
        HOOK_PUB_M virtual ShineMultiTypeHandle* so_mob_FindLooter(ShineMultiTypeHandle* result);
        HOOK_PUB_M virtual void so_ply_SetUseItemMinimon(USEITEM_MINIMON_INFO*);
        HOOK_PUB_M virtual char so_ply_UseItemMinimon_IsUse();
        HOOK_PUB_M virtual void so_ply_UseItemMinimon_Off();
        HOOK_PUB_M virtual void so_ply_UseItemMinimon_SlotItemCheck(unsigned __int16);
        HOOK_PUB_M virtual char so_IsAlliance(ShineObject*);
        HOOK_PUB_M virtual void so_ply_SetSellItemInfo(PROTO_NC_CHAR_SELL_ITEM_INFO_ZONE_CMD*);
        HOOK_PUB_M virtual void so_ply_SendSellItemInfo_Client();
        HOOK_PUB_M virtual char so_ply_CanItemRepurchase();
        HOOK_PUB_M virtual void so_ply_SellItemList_Insert(SHINE_ITEM_REGISTNUMBER, ItemTotalInformation*);
        HOOK_PUB_M virtual void so_ply_SellItemList_Delete(unsigned __int16);
        HOOK_PUB_M virtual void so_Init();
        HOOK_PUB_M virtual void so_smo_SetStaticWalkSpeed(char, unsigned __int16);
        HOOK_PUB_M virtual void so_smo_SetStaticRunSpeed(char, unsigned __int16);
        HOOK_PUB_M virtual char so_smo_IsStaticWalkSpeed();
        HOOK_PUB_M virtual char so_smo_IsStaticRunSpeed();
        HOOK_PUB_M virtual ushort so_smo_GetStaticWalkSpeed();
        HOOK_PUB_M virtual ushort so_smo_GetStaticRunSpeed();

		HOOK_PUB_M void smv_PassengerMove()
		{
            CallMemberFunction<ShineObject, void>(0x0055EFE0, this);
		}

    	HOOK_PUB_M ShineObjectHandleUnion so_handle;
		HOOK_PUB_M SlantedObjectList so_slantedlist;
		HOOK_PUB_M Location so_LocateInfo;
		HOOK_PUB_M LayerAndTemp so_layer;
		HOOK_PUB_M FieldMap* so_Field;
		HOOK_PUB_M LuaAi so_AIScript;
		HOOK_PUB_M char so_bIsMapMarking;
		HOOK_PUB_M OBJECT_SIGHT_STATE so_eSightState;
    };
}
#pragma pack(pop)