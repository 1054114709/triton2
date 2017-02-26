/*
 *	�øС���� ģ��
 */
// Include Head Files
#pragma once

#include "base_define.h"
#include "servertool.h"
#include "lk_hashmap.h"
#include "lk_vector.h"
#include "westserver.h"
#include "errcode.h"

#include "gateobj_define.h"
#include "protype.h"
#include "judgetype.h"
#include "judgemessage_pb.hxx.pb.h"

#include "nameservice.h"
#include "gatelogic.h"
#include "module_manager.h"
#include "core_service.h"

class CMessage;

using namespace GateServer;	

// ���ۼ�¼
struct JudgeRecord
{
	char	mName[ NAME_LENGTH ];
	int		mCharID;
	int		mValue;
	int		mTimeStamp;

	JudgeRecord(){ mCharID = 0; mValue = 0; mTimeStamp = 0; mName[0] = '\0'; }
	JudgeRecord( int nCharID, int nValue, int nTimeStamp, const char* npName ) 
		: mCharID( nCharID ), mValue( nValue ), mTimeStamp( nTimeStamp )
	{
		if ( npName != NULL )
			strncpy( mName, npName, sizeof( mName ) - 1 );
	}
};

// ���۹����б���
class CJudge
{
public:
	typedef lk::vector< JudgeRecord, JUDGE_OTHER_MAX > JudgeList;
	JudgeList mJudgeList;

	// ��������Ϣ
	int		mCharID;
	char	mName[ NAME_LENGTH ];

	int		mTotalScore;	// ��֧�����������
	int		mValidScore;	// ��ǰ��֧������

	int		mRecTotalScore;	// �յ�������ֵ

public:
	CJudge();
	~CJudge();

public:
	inline int GetJudgeCnt(){ return mJudgeList.size(); }

	// Set charid & name
	inline void SetJudgerInfo( int nCharID, char* npName )
	{
		mCharID = nCharID;
		if( npName != NULL ) strncpy( mName, npName, sizeof(mName)-1 );
	}

	// set & get
	inline void SetTotalScore(int nScore){ mTotalScore = nScore; }
	inline int  GetTotalScore(){return mTotalScore;}

	inline void SetValidScore(int nScore){ mValidScore = nScore; }
	inline int  GetValidScore(){return mValidScore;}

	inline void SetRecTotalScore( int nScore ) { mRecTotalScore = nScore; }
	inline int  GetRecTotalScore() { return mRecTotalScore; }

	// �������ۼ�¼
	int AttachJudge( int nCharID, int nValue, int nTime, const char* npName = NULL );

	// delete record
	int DeleteJudge( int nCharID );

	// has exist
	bool RecordExist( int nCharID );

	// ��ȡ�Ա��˵����ۼ�¼
	int GetJudgeValue( int nCharID );
};

// ����
class CJudgeFavor : public CJudge
{
public:
	int GetJudgeList( CMessage* npMessage );
};

// ����
class CJudgeBad : public CJudge
{
public:
	int GetJudgeList( CMessage* npMessage );
};

// logic module
class CJudgeModule : public CDataModule, public CSingleton< CJudgeModule >
{
public:
	// ֻ����ҵ�½��Ϸ��ʱ�򣬼��ظ�����������ݵ��ڴ�
	// �뿪�����Ƴ���Ϸʱ��ɾ��
	typedef lk::hash_map< int, CJudge, PLAYER_AT_GATE_CAP > JudgeOtherType;

	JudgeOtherType		mFavorJudge;
	JudgeOtherType		mBadJudge;

public:
	CJudgeModule();
	~CJudgeModule();

	void OnLaunchServer();
	void OnExitServer();
	void OnTimer( unsigned int nTickCount, unsigned int nTickOffset );
	void OnMessage( int nServerID, CMessage* pMessage );
	void OnSeverMessage( int nServerID, CMessage* pMessage );
	void OnDBMessage( CMessage* pMessage, int nParam1, int nParam2, int nSessionType );

	static unsigned int CountSize(); 
	virtual bool IsLaunched() { return true; }

	// internal interface
	CJudge* GetJudge( int nRoleID, int nType );

	// db operation
	void LoadJudgeDataFromDB( CGatePlayer* npPlayer );
	void OnSessionLoadJudgeData( CMessage* npMessage, int nParam1, int nParam2, int nSession );

	void QueryRecJudgeDataFromDB( CGatePlayer* npPlayer, int nCondition, int nParam = 0 );
	void OnSessionQueryRecJudgeData( CMessage* npMessage, int nParam1, int nParam2, int nSession );

	// attach judge recored
	int AttachJudgeRecordMemory( CGatePlayer* npPlayer, JudgeRecord* npRecord, JudgeType nType );

	void InsertJudgeRecordIntoDB( CGatePlayer* npPlayer, JudgeRecord* npRecord, JudgeType nType );
	void AttachJudgeRecordIntoDB( CGatePlayer* npPlayer, JudgeRecord* npRecord, JudgeType nType );

	void OnSessionAttachJudgeRecord( CMessage* npMessage, int nParam1, int nParam2, int nSession );

	// delete judge record from db!!!
	void DeleteJudgeRecordFromDB( int vAccountID, int nRoleID1, int nRoleID2, int nType );
	void OnSessionDeleteJudgeRecord( CMessage* npMessage, int nParam1, int nParam2, int nSession );

	// ��ѯ����յ�������������ֵ�ص�
	void OnSessionQueryRecSum( CMessage* npMessage, int nParam1, int nParam2, int nSession );

	// delete judge record from memory, not db, when you leave game
	void DeleteJudgeRecordMemory( int nRoleID );

	void SendJudgeModifyNotice( CGatePlayer* npPlayer, int nValue, int nType, int nDesRoleID );

	void ForceUpdateJudgeData( int nRoleID );

	// ֪ͨ�����������޸ĳɹ� [12/8/2009 Macro]
	void OnEventJudgeModifyNotice( int nServerID, int nRoleID );

	// external interface
	
	// judge request
	void OnMessageSingleJudgeRequest( int nServerID, CMessage* npMessage );
	void OnMessageMultiJudgeRequest( int nServerID, CMessage* npMessage );

	// query judge list
	void OnMessageQueryJudgeRequest( int nServerID, CMessage* npMessage );

	void OnMessageQuerySingleJudgeRequest( int nServerID, CMessage* npMessage );

	// update judge score limit
	void OnMessageChangeScoreLimitRequest( int nServerID, CMessage* npMessage );

	// ɾ����ɫID ��ص��������ۼ�¼
	void OnEventClearRoleJudgeDB( int vAccountID, int nRoleID );
};
