#pragma once
#pragma pack(8)
struct PROTO_AVATAR_SHAPE_INFO
{
	char _size[0x4];
};

struct SHINE_INDUN_RANK_CLIENT_VALUE
{
	Name5 nCharID;
	char nCharClass;
	unsigned __int64 nValue;
};

struct RankingInfo
{
	PROTO_AVATAR_SHAPE_INFO damageDealtShapeInfo1st;
	PROTO_AVATAR_SHAPE_INFO damageDealtShapeInfo2nd;
	PROTO_AVATAR_SHAPE_INFO damageDealtShapeInfo3th;
	PROTO_AVATAR_SHAPE_INFO damageTakenShapeInfo1st;
	PROTO_AVATAR_SHAPE_INFO damageTakenShapeInfo2nd;
	PROTO_AVATAR_SHAPE_INFO damageTakenShapeInfo3th;
	PROTO_AVATAR_SHAPE_INFO healingDoneShapeInfo1st;
	PROTO_AVATAR_SHAPE_INFO healingDoneShapeInfo2nd;
	PROTO_AVATAR_SHAPE_INFO healingDoneShapeInfo3th;
	char nDamageDealtCount;
	char nDamageTakenCount;
	char nHealingDoneCount;
	SHINE_INDUN_RANK_CLIENT_VALUE damageDealtRanks[20];
	SHINE_INDUN_RANK_CLIENT_VALUE damageTakenRanks[20];
	SHINE_INDUN_RANK_CLIENT_VALUE healingDoneRanks[20];
};

struct SHINE_INDUN_INFO
{
	Name3 MapIDClient;
	char ModeIDLv;
};

class __declspec(align(1)) RankingServer
{
public:
	__declspec(noinline) static void Install_RankingServer()
	{
		Detour(0x00402ED0, MF(RankingServerCtor));
		Detour(0x00402560, MF(GetRankingInfoMap));
		Detour(0x00402460, MF(GetRankingInfoMapIndex));
	}
	
	void RankingServerCtor()
	{
		m_indexListCount = 0;
		m_indexList = new SHINE_INDUN_INFO[254];
		m_rankingInfoMap = new RankingInfo[254];
	}

	RankingInfo* GetRankingInfoMap(SHINE_INDUN_INFO* indunMapInfo)
	{
		auto index = GetRankingInfoMapIndex(indunMapInfo);
		
		if (index == 0xFF)
		{
			return nullptr;
		}

		return &m_rankingInfoMap[index];
	}

	uchar GetRankingInfoMapIndex(SHINE_INDUN_INFO* indunMapInfo)
	{
		uchar out = 0xFF;
		if (!indunMapInfo)
		{
			return out;
		}

		if (m_indexListCount >= 0xFF)
		{
			return out;
		}

		// auto i = 0;
		// auto val = &m_indexList[i];
		// 
		// while (indunMapInfo->ModeIDLv != val->ModeIDLv && strcmp(val->MapIDClient.n3_name, indunMapInfo->MapIDClient.n3_name) != 0)
		// {
		// 	++i;
		// 	val = &m_indexList[i];
		// 
		// 	if (i >= m_indexListCount)
		// 	{
		// 		out = (uchar) i;
		// 		m_indexList[m_indexListCount++] = *indunMapInfo;
		// 	}
		// }

		for (auto i = 0; i < m_indexListCount; i++)
		{
			if (indunMapInfo->ModeIDLv == m_indexList[i].ModeIDLv && 
				!strcmp(m_indexList[i].MapIDClient.n3_name, indunMapInfo->MapIDClient.n3_name))
			{
				out = (uchar) i;
				break;
			}
		}
		
		if (out == 0xFF && m_indexListCount != 0xFF)
		{
			out = m_indexListCount;
			m_indexList[m_indexListCount++] = *indunMapInfo;
		}

		return out;
	}

	int RecalcRankingDamageDealt(SHINE_INDUN_INFO* indunMapInfo, SHINE_INDUN_RANK_CLIENT_VALUE* pRank, PROTO_AVATAR_SHAPE_INFO* pShape)
	{
		
	}
	
	uchar m_indexListCount;
	SHINE_INDUN_INFO* m_indexList;
	char _pad[0x1A3];
	RankingInfo* m_rankingInfoMap;
	char _pad2[0xF6A8 - 0x1AC];
};
