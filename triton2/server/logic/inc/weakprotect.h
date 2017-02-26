//=========================================================================
// weakprotect.h
//=========================================================================
#pragma once


#include "countrymessage_pb.hxx.pb.h"

class CEntityPlayer;
class CMessage;

#define CAMP_INDEX(x)			((x)-1)
#define MAX_CAMP_NUM	4	//��Ӫ����
class CWeakProtect
{
public:
	CWeakProtect();
	~CWeakProtect();

	void Init();

private:
	PBCampWeakForceInfo m_PBWeakInfo[MAX_CAMP_NUM];
	int m_nCampWeakLevel[MAX_CAMP_NUM];

public:
	// client request week list of camp
	void OnMessageCampWeakListReq( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// client get award of camp
	void OnMessageCampGetAward( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// syn camp list from gate
	void OnMessageGSCampWeakList( CMessage* pMessage );
	
	// ֪ͨ�����������ֱ仯
	void Send2GatePlayerGetHonerScoreNotify( int nCampID, int nRoleID, int nScore );
	
	// ����������������
	void Send2GateCampWeakListRequest();

public:
	// �ж�����Ƿ��ܹ���ȡ������Ӫ����
	bool CouldObtainTask( CEntityPlayer* pPlayer );
	
	// �ж���Ӫ�Ƿ�����
	bool IsWeakCamp( int nCampID );

	// �õ���Ӫ�ȼ�
	int  GetWeekLevel( int nCampID );
	//�ж� �Ƿ��ǻ�����ߵ���Ӫ
	bool IsTopTotalscoreCampID(int nCampID);

private:
	// ��ȡ����
	int GetWeakCampAward(CEntityPlayer* pPlayer, int nNpcEntityID, int nAwardType);
};