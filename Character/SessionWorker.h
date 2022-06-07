#pragma once
#include "pch.h"
#include "Generic.h"

struct CSessionWorker : CSocket_Session
{
	char m_Connection;
	char _p1[0x3];
	int m_Connected_Server_ID;
	int m_Connected_World;
	int m_Connected_Zone;
	_SYSTEMTIME m_Connected_Time;
	unsigned int m_LastReceiveTime;
	unsigned int m_LastSendTime;
	NETCOMMAND m_Last_PacketCommand;
	char _p2[0x2];
	int m_Last_PacketLength;
	PACKET_WORKTYPE m_Last_PacketWorkType;
	int m_WorkerID;
	int m_WorkerStatus;
	int m_bJob;
	char _p3[0x4];
	unsigned __int64 m_JobIndex;
	CSessionWorkerManager* m_pWorkerManager;
	int m_ActiveWorker;
	void* m_hThread;
	unsigned int m_ThreadID;
	char m_Parser[0x124C - 0x138];
	CGameDB_Character m_DBF;
};