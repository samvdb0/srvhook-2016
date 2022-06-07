#pragma once
#include "pch.h"
#include "Generic.h"

#include "SessionWorker.h"

int(__thiscall* GetMainInventory)(CSQLPItem* sql, CGameDB_Character* a2, char rgbValue, CGameDB_Item::DB_ITEM_ARRAY_CHAR* a4) = (int(__thiscall *)(CSQLPItem *, CGameDB_Character*, char, CGameDB_Item::DB_ITEM_ARRAY_CHAR*))0x0046A290;
signed int(__thiscall* GetOptions)(class CPFsCharacter* pt, CGameDB_Item::DB_ITEM_ARRAY_CHAR* a2, int a3, int a4) = (signed int(__thiscall*)(class CPFsCharacter*, CGameDB_Item::DB_ITEM_ARRAY_CHAR*, int, int))0x00402E50;
int(__thiscall* fc_NC_CHAR_CHARDATA_REQ_Org)(class CPFsCharacter* pt, NETPACKET* netpacket, int len);

inline uint TimestampToEpoch(TIMESTAMP_STRUCT& outTime)
{
	tm currentTime;
	ZeroMemory(&currentTime, sizeof currentTime);

	currentTime.tm_sec = outTime.second;
	currentTime.tm_min = outTime.minute;
	currentTime.tm_hour = outTime.hour;
	currentTime.tm_mday = outTime.day;
	currentTime.tm_mon = outTime.month - 1;
	currentTime.tm_year = outTime.year - 1900;

	return (uint) _mktime32(&currentTime);
}

class CPFsCharacter
{
	HOOK_PUB_S void Install_InventoryFix()
	{
		Detour(0x00402F80, MF(GetCharInventory));
	}
	
	HOOK_PUB_S void Install_IndunRankFix()
	{
		fc_NC_CHAR_CHARDATA_REQ_Org = (int(__thiscall*)(CPFsCharacter*, NETPACKET*, int))Detour(0x00438DC0, MF(fc_NC_CHAR_CHARDATA_REQ));
	}

	HOOK_PUB_S bool usp_InstanceDungeon_GetTop3(CGameDB_Character* db, char mapIndx[12], BYTE modeId, BYTE type)
	{
		auto stmt = db->GetStatement();
		db->CloseCursor();

		SQLBindParameter(stmt, 1u, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, mapIndx, 12, nullptr);
		SQLBindParameter(stmt, 2u, SQL_PARAM_INPUT, SQL_C_TINYINT, SQL_TINYINT, 0, 0, &modeId, 0, nullptr);
		SQLBindParameter(stmt, 3u, SQL_PARAM_INPUT, SQL_C_TINYINT, SQL_TINYINT, 0, 0, &type, 0, nullptr);

		auto v4 = SQLExecDirect(stmt, (SQLCHAR*) "{CALL usp_InstanceDungeon_GetTop3(?, ?, ?)}", SQL_NTS);
		return !v4 || v4 == 1;
	}

	HOOK_PUB_S bool usp_InstanceDungeon_GetMyRank(CGameDB_Character* db, unsigned int charNo)
	{
		auto stmt = db->GetStatement();
		db->CloseCursor();

		SQLBindParameter(stmt, 3u, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &charNo, 0, nullptr);

		auto v4 = SQLExecDirect(stmt, (SQLCHAR*) "{CALL usp_InstanceDungeon_GetByCharNo(?)}", SQL_NTS);
		return !v4 || v4 == 1;
	}

	HOOK_PUB_S bool usp_InstanceDungeon_GetTop20(CGameDB_Character* db, char mapIndx[12], BYTE modeId, BYTE type)
	{
		auto stmt = db->GetStatement();
		db->CloseCursor();

		SQLBindParameter(stmt, 1u, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, mapIndx, 12, nullptr);
		SQLBindParameter(stmt, 2u, SQL_PARAM_INPUT, SQL_C_TINYINT, SQL_TINYINT, 0, 0, &modeId, 0, nullptr);
		SQLBindParameter(stmt, 3u, SQL_PARAM_INPUT, SQL_C_TINYINT, SQL_TINYINT, 0, 0, &type, 0, nullptr);

		auto v4 = SQLExecDirect(stmt, (SQLCHAR*)"{CALL usp_InstanceDungeon_GetTop20(?, ?, ?)}", SQL_NTS);
		return !v4 || v4 == 1;
	}

	HOOK_PUB_S bool usp_InstanceDungeon_SaveRank(CGameDB_Character* db, char mapIndx[12], BYTE modeId, uint playTime, SHINE_INDUN_RANK rank)
	{
		auto stmt = db->GetStatement();
		db->CloseCursor();

		SQLBindParameter(stmt, 1u, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &rank.nCharRegNum, 0, nullptr);
		SQLBindParameter(stmt, 2u, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, mapIndx, 12, nullptr);
		SQLBindParameter(stmt, 3u, SQL_PARAM_INPUT, SQL_C_TINYINT, SQL_TINYINT, 0, 0, &modeId, 0, nullptr);
		SQLBindParameter(stmt, 4u, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &playTime, 0, nullptr);
		SQLBindParameter(stmt, 5u, SQL_PARAM_INPUT, SQL_C_UBIGINT, SQL_BIGINT, 0, 0, &rank.nDamageDealt, 0, nullptr);
		SQLBindParameter(stmt, 6u, SQL_PARAM_INPUT, SQL_C_UBIGINT, SQL_BIGINT, 0, 0, &rank.nDamageTaken, 0, nullptr);
		SQLBindParameter(stmt, 7u, SQL_PARAM_INPUT, SQL_C_UBIGINT, SQL_BIGINT, 0, 0, &rank.nHealingDone, 0, nullptr);

		auto v4 = SQLExecDirect(stmt, (SQLCHAR*)"{CALL usp_InstanceDungeon_SaveRank(?, ?, ?, ?, ?, ?, ?)}", SQL_NTS);
		return !v4 || v4 == 1;
	}

	HOOK_PUB_S bool usp_InstanceDungeon_GetAllRanks(CGameDB_Character* db, uint charNo, char mapIndx[12], BYTE modeId, BYTE type)
	{
		auto stmt = db->GetStatement();
		db->CloseCursor();

		SQLBindParameter(stmt, 1u, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &charNo, 0, nullptr);
		SQLBindParameter(stmt, 2u, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, mapIndx, 12, nullptr);
		SQLBindParameter(stmt, 3u, SQL_PARAM_INPUT, SQL_C_TINYINT, SQL_TINYINT, 0, 0, &modeId, 0, nullptr);
		SQLBindParameter(stmt, 4u, SQL_PARAM_INPUT, SQL_C_TINYINT, SQL_TINYINT, 0, 0, &type, 0, nullptr);

		auto v4 = SQLExecDirect(stmt, (SQLCHAR*)"{CALL usp_InstanceDungeon_GetAllRanks(?, ?, ?, ?)}", SQL_NTS);
		return !v4 || v4 == 1;
	}

	HOOK_PUB_M uint GetUserRank(char mapIndx[12], BYTE modeId, uint charNo, uint type)
	{
		auto result = 0;
		
		if (usp_InstanceDungeon_GetAllRanks(&m_pSessionWorker->m_DBF, charNo, mapIndx, modeId, type))
		{
			uint currCharNo = 0;
			result = 0;
			
			while (currCharNo != charNo)
			{
				if (m_pSessionWorker->m_DBF.FetchResult())
				{
					m_pSessionWorker->m_DBF.GetUInt32(&currCharNo);
					result++;
				}
				else
				{
					result = 0;
					break;
				}
			}

			m_pSessionWorker->m_DBF.CloseCursor();
		}

		return result;
	}
		
	HOOK_PUB_S int SendToWorldManager(CSendPacket* packet)
	{
		return ((int(__stdcall*)(CSendPacket*))0x00402D80)(packet);
	}
	
	HOOK_PUB_M int fc_NC_INSTANCE_DUNGEON_RANK_SAVE_DB_CMD(NETPACKET* netpacket, int len)
	{
		try 
		{
			auto result = ConnectionValidation(netpacket);
			if (result)
			{
				auto packet = (PROTO_NC_INSTANCE_DUNGEON_RANK_SAVE_WORLD_CMD*)&netpacket[1];

				for (auto i = 0; i < packet->nRankCount; i++)
				{
					auto currRank = packet->ranks[i];

					if (!usp_InstanceDungeon_SaveRank(&m_pSessionWorker->m_DBF, packet->sIndunInfo.MapIDClient, packet->sIndunInfo.ModeIDLv, packet->nPlayTime, currRank))
					{
						Log::Error(FORMAT_STR("Failed to save ranking -> %d", i));
					}
					
					m_pSessionWorker->m_DBF.CloseCursor();
				}

				auto* pk = new CSendPacket();
				pk->ID(0xA414, 19 + 32 * packet->nRankCount, packet);
				SendToWorldManager(pk);
				delete pk;
				
				//PROTO_NC_INSTANCE_DUNGEON_RANK_MYRANK_CMD packet_ack;
				//ZeroMemory(&packet_ack, sizeof packet_ack);
				//
				//packet_ack.nCharRegNum = packet->;
				//
				//while (m_pSessionWorker->m_DBF.FetchResult())
				//{
				//	AddRanking(&packet_ack.MyRank[packet_ack.nMyRankCount]);
				//
				//	packet_ack.nMyRankCount++;
				//}
				//
				//m_pSessionWorker->m_DBF.CloseCursor();
				//
				//for (auto i = 0; i < packet_ack.nMyRankCount; i++)
				//{
				//	packet_ack.MyRank[i].nBestDamageDealtRank = GetUserRank(packet_ack.MyRank[i].sIndunInfo.MapIDClient, packet_ack.MyRank[i].sIndunInfo.ModeIDLv, packet_ack.nCharRegNum, 0);
				//	packet_ack.MyRank[i].nBestDamageTakenRank = GetUserRank(packet_ack.MyRank[i].sIndunInfo.MapIDClient, packet_ack.MyRank[i].sIndunInfo.ModeIDLv, packet_ack.nCharRegNum, 1);
				//	packet_ack.MyRank[i].nBestHealingDoneRank = GetUserRank(packet_ack.MyRank[i].sIndunInfo.MapIDClient, packet_ack.MyRank[i].sIndunInfo.ModeIDLv, packet_ack.nCharRegNum, 2);
				//}
				//
				//auto pk = new CSendPacket();
				//pk->ID(0xA420, 6 + 96 * packet_ack.nMyRankCount, &packet_ack);
				//m_pSession->Send(pk);
				//
				//delete pk;
			}
			else
			{
				result = 0;
			}

			return result;
		}
		catch (...)
		{
			return 0;
		}
	}

	HOOK_PUB_M void AddRanking(INDUN_CHAR_SHAPE* shape)
	{
		TEMP_SHAPE tempShape;
		ZeroMemory(&tempShape, sizeof tempShape);		

		m_pSessionWorker->m_DBF.GetByte(&tempShape.Race);
		m_pSessionWorker->m_DBF.GetByte(&tempShape.Class);
		m_pSessionWorker->m_DBF.GetByte(&tempShape.Gender);
		
		shape->RCG = tempShape.Race | tempShape.Class << 2 | tempShape.Gender << 7;
		
		m_pSessionWorker->m_DBF.GetByte(&shape->HairType);
		m_pSessionWorker->m_DBF.GetByte(&shape->HairColor);
		m_pSessionWorker->m_DBF.GetByte(&shape->FaceShape);
	}

	HOOK_PUB_M void AddRanking(SHINE_INDUN_RANK_CLIENT_VALUE* rank)
	{
		m_pSessionWorker->m_DBF.GetUInt64(&rank->nValue);
		m_pSessionWorker->m_DBF.GetString(&rank->nCharID, 20);
		m_pSessionWorker->m_DBF.GetByte(&rank->nCharClass);
	}

	HOOK_PUB_M void AddRanking(SHINE_INDUN_RANK_MYRANK* rank)
	{
		TIMESTAMP_STRUCT outTime;		
		m_pSessionWorker->m_DBF.m_DB.columnNo++; // Skip nCharNo.
		
		m_pSessionWorker->m_DBF.GetString(&rank->sIndunInfo.MapIDClient, 12);
		m_pSessionWorker->m_DBF.GetByte(&rank->sIndunInfo.ModeIDLv);

		m_pSessionWorker->m_DBF.GetUInt64(&rank->nBestDamageDealt);
		m_pSessionWorker->m_DBF.GetUInt64(&rank->nBestDamageTaken);
		m_pSessionWorker->m_DBF.GetUInt64(&rank->nBestHealingDone);
		m_pSessionWorker->m_DBF.GetUInt32(&rank->nBestPlayTime);
		m_pSessionWorker->m_DBF.GetDate(&outTime);
		rank->nBestPlayDate = TimestampToEpoch(outTime);
		
		m_pSessionWorker->m_DBF.GetUInt64(&rank->nLastDamageDealt);
		m_pSessionWorker->m_DBF.GetUInt64(&rank->nLastDamageTaken);
		m_pSessionWorker->m_DBF.GetUInt64(&rank->nLastHealingDone);
		m_pSessionWorker->m_DBF.GetUInt32(&rank->nLastPlayTime);
		m_pSessionWorker->m_DBF.GetDate(&outTime);
		rank->nLastPlayDate = TimestampToEpoch(outTime);
	}

	HOOK_PUB_M int fc_NC_INSTANCE_DUNGEON_RANK_REQ(NETPACKET* netpacket, int len)
	{
		auto result = ConnectionValidation(netpacket);
		if (result)
		{
			auto packet = (PROTO_NC_INSTANCE_DUNGEON_RANK_REQ*)&netpacket[1];
			
			for (auto i = 0; i < packet->mapCount; i++)
			{
				auto currMap = packet->maps[i];

				PROTO_NC_INSTANCE_DUNGEON_RANK_ACK packet_ack;
				ZeroMemory(&packet_ack, sizeof packet_ack);

				strcpy_s(packet_ack.sIndunInfo.MapIDClient, currMap.mapIdClient);
				packet_ack.sIndunInfo.ModeIDLv = currMap.modeIdLv;
								
				for (auto j = 0; j < 3; j++)
				{
					if (usp_InstanceDungeon_GetTop3(&m_pSessionWorker->m_DBF, currMap.mapIdClient, currMap.modeIdLv, j))
					{
						int k = 0;
						
						while (m_pSessionWorker->m_DBF.FetchResult())
						{
							switch (k)
							{
								case 0:
									switch (j)
									{
										case 0:
											AddRanking(&packet_ack.damageDealtShapeInfo1st);
											break;
										case 1:
											AddRanking(&packet_ack.damageTakenShapeInfo1st);
											break;
										case 2:
											AddRanking(&packet_ack.healingDoneShapeInfo1st);
											break;
										default:
											break;
									}
									break;
								case 1:
									switch (j)
									{
										case 0:
											AddRanking(&packet_ack.damageDealtShapeInfo2nd);
											break;
										case 1:
											AddRanking(&packet_ack.damageTakenShapeInfo2nd);
											break;
										case 2:
											AddRanking(&packet_ack.healingDoneShapeInfo2nd);
											break;
										default:
											break;
									}
									break;
								case 2:
									switch (j)
									{
										case 0:
											AddRanking(&packet_ack.damageDealtShapeInfo3th);
											break;
										case 1:
											AddRanking(&packet_ack.damageTakenShapeInfo3th);
											break;
										case 2:
											AddRanking(&packet_ack.healingDoneShapeInfo3th);
											break;
										default:
											break;
									}
									break;
								default:
									break;
							}
							
							k++;
						}

						m_pSessionWorker->m_DBF.CloseCursor();
					}
					else
					{
						result = 0;
					}

					if (usp_InstanceDungeon_GetTop20(&m_pSessionWorker->m_DBF, currMap.mapIdClient, currMap.modeIdLv, j))
					{
						int k = 0;
						
						while (m_pSessionWorker->m_DBF.FetchResult())
						{
							switch (j)
							{
								case 0:
									packet_ack.nDamageDealtCount++;
									AddRanking(&packet_ack.damageDealtRanks[k]);
									break;
								case 1:
									packet_ack.nDamageTakenCount++;
									AddRanking(&packet_ack.damageTakenRanks[k]);
									break;
								case 2:
									packet_ack.nHealingDoneCount++;
									AddRanking(&packet_ack.healingDoneRanks[k]);
									break;
							}

							k++;
						}
						
						m_pSessionWorker->m_DBF.CloseCursor();
					}
				}

				auto* pk = new CSendPacket();
				pk->ID(0xA41F, sizeof packet_ack, &packet_ack);
				m_pSession->Send(pk);

				delete pk;
			}
		}

		return result;
	}

	HOOK_PUB_M int fc_NC_CHAR_CHARDATA_REQ(NETPACKET* netpacket, int len)
	{
		auto result = fc_NC_CHAR_CHARDATA_REQ_Org(this, netpacket, len);

		if (result)
		{
			auto packet = (PROTO_NC_CHAR_CHARDATA_REQ*)&netpacket[1];

			if (usp_InstanceDungeon_GetMyRank(&m_pSessionWorker->m_DBF, packet->CharNo))
			{
				PROTO_NC_INSTANCE_DUNGEON_RANK_MYRANK_CMD packet_ack;
				ZeroMemory(&packet_ack, sizeof packet_ack);

				packet_ack.nCharRegNum = packet->CharNo;

				while (m_pSessionWorker->m_DBF.FetchResult())
				{
					AddRanking(&packet_ack.MyRank[packet_ack.nMyRankCount]);

					packet_ack.nMyRankCount++;
				}
				
				m_pSessionWorker->m_DBF.CloseCursor();

				for (auto i = 0; i < packet_ack.nMyRankCount; i++)
				{
					packet_ack.MyRank[i].nBestDamageDealtRank = GetUserRank(packet_ack.MyRank[i].sIndunInfo.MapIDClient, packet_ack.MyRank[i].sIndunInfo.ModeIDLv, packet_ack.nCharRegNum, 0);
					packet_ack.MyRank[i].nBestDamageTakenRank = GetUserRank(packet_ack.MyRank[i].sIndunInfo.MapIDClient, packet_ack.MyRank[i].sIndunInfo.ModeIDLv, packet_ack.nCharRegNum, 1);
					packet_ack.MyRank[i].nBestHealingDoneRank = GetUserRank(packet_ack.MyRank[i].sIndunInfo.MapIDClient, packet_ack.MyRank[i].sIndunInfo.ModeIDLv, packet_ack.nCharRegNum, 2);
				}

				auto pk = new CSendPacket();
				pk->ID(0xA420, 6 + 96 * packet_ack.nMyRankCount, &packet_ack);
				m_pSession->Send(pk);

				delete pk;
			}
			else
			{
				result = 0;
			}
		}

		return result;
	}

	HOOK_PUB_M int fc_NC_INSTANCE_DUNGEON_RANK_UPDATE_DB_REQ(NETPACKET* netpacket, int len)
	{
		auto result = ConnectionValidation(netpacket);

		if (result)
		{
			auto packet = (PROTO_NC_INSTANCE_DUNGEON_RANK_UPDATE_DB_REQ*)&netpacket[1];

			PROTO_NC_INSTANCE_DUNGEON_RANK_UPDATE_DB_ACK packet_ack;
			ZeroMemory(&packet_ack, sizeof packet_ack);

			strcpy_s(packet_ack.sIndunInfo.MapIDClient, packet->sIndunInfo.MapIDClient);
			packet_ack.sIndunInfo.ModeIDLv = packet->sIndunInfo.ModeIDLv;

			for (auto i = 0; i < packet->CharListCount; i++)
			{
				auto currChar = packet->CharList[i];

				packet_ack.CharList[i].clienthandle = currChar.clienthandle;
				packet_ack.CharList[i].nDamageDealtRank = GetUserRank(packet_ack.sIndunInfo.MapIDClient, packet_ack.sIndunInfo.ModeIDLv, currChar.charregistnumber, 0);
				packet_ack.CharList[i].nDamageTakenRank = GetUserRank(packet_ack.sIndunInfo.MapIDClient, packet_ack.sIndunInfo.ModeIDLv, currChar.charregistnumber, 1);
				packet_ack.CharList[i].nHealingDoneRank = GetUserRank(packet_ack.sIndunInfo.MapIDClient, packet_ack.sIndunInfo.ModeIDLv, currChar.charregistnumber, 2);

				packet_ack.CharListCount++;
			}

			auto pk = new CSendPacket();
			pk->ID(0xA416, 15 + 14 * packet_ack.CharListCount, &packet_ack);
			m_pSession->Send(pk);

			delete pk;
		}

		return result;
	}

	HOOK_PUB_M int GetCharInventory(char rgbValue, int a3, int a4)
	{		
		auto itemArray = CGameDB_Item::DB_ITEM_ARRAY_CHAR();

		auto result = GetMainInventory(m_pSessionWorker->m_DBF.m_Item.m_pSQLPItem, &m_pSessionWorker->m_DBF, rgbValue, &itemArray);
		if (result)
		{
			result = GetOptions(this, &itemArray, a3, a4);
		}

		return result;
	}

	HOOK_PUB_M signed int ConnectionValidation(NETPACKET* netpacket)
	{
		return CallMemberFunction<CPFsCharacter, signed int, NETPACKET*>(0x0043C640, this, netpacket);
	}
	
	CSessionWorker* m_pSessionWorker;
	CSession* m_pSession;
};