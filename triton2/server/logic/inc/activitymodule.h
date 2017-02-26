#pragma once 
#include "activitytype.h"
#include "proclient_svr.h"
#include "activity.h"
#include "creator.h"
#include "servercore.h"
#include "servertool.h"
#include "activitymessag_pb.hxx.pb.h"

#define GAME_LIST_SIZE 32

#define MAX_EXCEPTIP_NUM 50
#define MAX_MULTI_CLIENT_EXCEPT 1024

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include "lua_tinker.h"
class CMessage;
class CEntityPlayer;
class CTimerItem;

struct NpcBidInfo 
{
	int			mNpcID;			// NPC��ģ��ID
	int			mState;			// ��ǰ��״̬
	CWTimer		mSubmitTimer;	// ��������ʱ
	CWTimer		mNotifyTimer;	// ֪ͨ����ʱ
	CWTimer		mWarTimer;		// ս������ʱ
	int			mEntityID;
};

class TimeListSingle 
{
public:
	int m_nStartTime;
	int m_nEndTime;

	TimeListSingle()
	{
		if ( CObj::msCreateMode )		
		{
			m_nStartTime = 0;
			m_nEndTime   = 0;
		}
	}
};

typedef lk::vector<TimeListSingle, ACTIVITY_TIME_LST_SIZE> TIMELIST_TYPE;

class CActivityInfo
{
public:
	TIMELIST_TYPE  mTimeList; // ʱ���<��̬>
	int m_nLmtLevel;	// �ȼ�����<��̬>
	int m_nMaxTimes;	// ÿ��������<��̬>
	int m_nCurState;	// ��ǰ״̬����enActivityStateö��
	int m_OgreIndex[ACTIVITY_OGREINDEX_SZ];
	int m_OgreIndexNum;

	CActivityInfo()
	{
		if ( CObj::msCreateMode )		
		{
			m_nLmtLevel  = 0;
			m_nMaxTimes  = 0;
			m_nCurState  = 0; // �״̬
			mTimeList.initailize();
			m_OgreIndexNum = 0;
			memset(m_OgreIndex, 0, sizeof(m_OgreIndex));
		}
	}
	void PushTime( int nType, int nTime )
	{
		if ( nType == ACTIVITY_START )
		{
			TimeListSingle obj;
			obj.m_nStartTime = nTime;
			mTimeList.push_back(obj);
		}
		else if ( nType == ACTIVITY_END )
		{
			// һ���ǰ�˳��ģ����Ը�ֵ�����1������
			if ( mTimeList.size() <= 0 )
				return;
			mTimeList[mTimeList.size()-1].m_nEndTime = nTime;
		}
	}
	bool PushOgreIndex( int nOgreIndex )
	{
		if ( m_OgreIndexNum >= ACTIVITY_OGREINDEX_SZ )
		{
			return false;
		}
		m_OgreIndex[m_OgreIndexNum++] = nOgreIndex;
		return true;
	}
};

// �����������
class CActivityOgreData
{
public:
	int		m_nActivityID; // �ID
	int		m_nDropID; // �����ID
	CActivityOgreData()
	{
		if (CObj::msCreateMode)
		{
			m_nActivityID = 0;
			m_nDropID = 0; 
		}
	}
};

typedef lk::hash_map<int, CActivityInfo, ACTIVITY_SIZE> ACTIVITY_MGR_TYPE;
typedef lk::hash_map<int, CActivityOgreData, ACTIVITY_DROP_SZ> ACTIVITY_OGRE_TYPE; // first�ǹ���ID����ԭ���ĵ����ID
typedef lk::vector<int, ACTIVITY_MAPDROP_SIZE> ACTIVITY_MAP_DROP_TYPE; 

class  CActivityModule: public CLogicModule, public CSingleton< CActivityModule >
{
private:
	ACTIVITY_MGR_TYPE	mSceneActivityMgr; // �������
	ACTIVITY_OGRE_TYPE  mAvtivityOgreMgr;	// ��ֹ�����
	ACTIVITY_MAP_DROP_TYPE mMapAddDropTable[MAX_MAP_ID]; // ���ͼ�����(���)
	int					   mMapRepDropTable[MAX_MAP_ID]; // ���ͼ�����(�滻)
	lua_State* L;
	int			mLastClearWeekCharmTime;
public:
	static char	sModuleName[ NAME_LENGTH ];	
public:
	// ��ʼ��ÿ���ʴ����
	int InitialQuestionFile( const char *pFileName );
	
	// ��ʼ���ʾ��������
	int InitailInvestQuestionFile( const char *pFileName );

	// ��ʼ��˫��ʱ������
	int InitialDoubleExpFile( const char *pFileName );
	
	// ��ʼ������·������
	int InitialHydrangea( const char *pFileName );
	
	// ��ʼ���۱����������Ϣ
	int InitialTreasureBowlConfig();
public:	
	static unsigned int CountSize( );
public:	
	CActivityModule( ):CLogicModule( sModuleName )
	{ 
		mTimer = CWTimer( ACTIVITY_TIMER_LENGTH );
		mHydrangeaTimer = CWTimer(HYDRANGEA_TIMER_LENGTH);
		mInvestRecordTimer = CWTimer(INVESTRECORD_TIMER_LENGTH);
		mDoubleTime.initailize();
		/*
		memset( mDoubleTime, 0, sizeof(mDoubleTime) );
		memset( mExistTime, 0, sizeof(mExistTime) );
		mCount = 0;
		*/

		mDoubleActive = false;
		mDoubleIndex = -1;
		mEndTime = time(NULL);
		memset( mNpcInfo, 0, sizeof(mNpcInfo) );

		mSceneActivityMgr.initailize();
		mAvtivityOgreMgr.initailize();
		mNpcNum = 0;
		
		mTalentTableID = 0;
		memset( mRoleValidQuestions, 0, sizeof( mRoleValidQuestions ) );	
		memset( mRoleValidQuestionGroups, 0, sizeof( 0 ) ) ;			
		mRoleValideQuestionCount = 0;
		L=NULL;
		for (int i = 0 ; i < MAX_MAP_ID; ++i )
		{
			mMapAddDropTable[i].initailize();
		}
		memset(mMapRepDropTable, 0, sizeof (mMapRepDropTable));
		mTreasureBowlManager.Initialize();
		mLastClearWeekCharmTime=time(0);
	}
	virtual ~CActivityModule( )	{	}
public:
	void OnMessageIfBeginQuest( CEntityPlayer *tpPlayer, CMessage * pMessage );
	void OnMessageCheckAnswer( CEntityPlayer *tpPlayer, CMessage * pMessage );
	void OnMessageQuestionTimeEnd(CEntityPlayer *tpPlayer, CMessage * pMessage);
	void OnMessageIfAnswerNow( CEntityPlayer *tpPlayer, CMessage * pMessage );
	void OnMessageStopAnswer( CEntityPlayer *tpPlayer, CMessage * pMessage );
	void OnMsgSingleQuestTimeOut( CTimerItem* pTimerItem );
	void OnMsgTotalQuestTimeOut( CTimerItem* pTimerItem );
	void OnMessageUsePaper( CEntityPlayer *tpPlayer, CMessage * pMessage );
	
	void OnMessageInvestAnwerNotify( CEntityPlayer *tpPlayer, CMessage * pMessage );
	bool IsPassed( int nTime );

public:
	void PlayerBeginNpcQuest( CEntityPlayer *tpPlayer );
	void PlayerCheckAnswerRequest( CEntityPlayer *tpPlayer, int QuestionID, int Answer );
	void PlayerBeginPaperQuest( CEntityPlayer *tpPlayer, int Result );
	void StopCurrentQuestion( CEntityPlayer *tpPlayer, int  QuestionID  );
	void PlayerStopQuestionAnswer( CEntityPlayer *tpPlayer, int Entype );
	void PlayerUseQuestionPaper( CEntityPlayer *tpPlayer, int PaperIndex );	
	void EndAnswerQuestion( CEntityPlayer *tpPlayer, CAnswerStatus *tpAnswer, int EndType );
	void PlayerBeginQuestion( CEntityPlayer *tpPlayer, int Result ); 
																	  
	void OnEventInvestQuestion( int InvestType,  int ID, CEntityPlayer *pPlayer = NULL );																	  
	void SaveInvestAnswerToDB( CEntityPlayer *tpPlayer, int vLibedition, int LibID, int *pQuestionList, int *pAnswerList, int vQuestionNum );	
	void CheckInvestTime(  );
public:
	void SendMsgCheckAnswer( CEntityPlayer *tpPlayer, int Result, int QuestionID, int QuestionIndex ,int IfLastQuestion = 0 );
	void SendMsgNewQuestion( CEntityPlayer *tpPlayer,int QuestionID ,  int QuestionIndex );
	void SendMsgEndAnswerQuestion( CEntityPlayer *tpPlayer, int Result );
	void SendMsgUseQuestionPaper( CEntityPlayer *tpPlayer, int Result );
	
	void SendMsgInvestNotify( CEntityPlayer *tpPlayer, CInvestQuestionLib *pQuestionLib );		
public:			
	void CheckDoubleTime( );
	int GetDoubleState( int &vBeginTime, int &vEndTime );

	void AddNpcInfo( int vNpcID, int vEntityID = 0 );
	bool CanBidNpc( int vNpcID );

	void CheckNpcTime( );
	void SendMsgBidTimeOut( int vNpcID, int vFirst );
	void SendMsgBattleStart( int vNpcID );

	void DebugTimeOut( int vNpcID );
	void DebugBattleStart( int vNpcID );
	void DebugBattleEnd( int vNpcID );
	
public:
	int GetQuestNumOfPaper( int ItemID );
	void ClearActivitys();

	void OnGateMessageTodayActivityList( CMessage* pMessage );
	void OnGateMessageActivityChgNotice( CMessage* pMessage );
	void OnGateMessageActivityEventNotice( CMessage* pMessage );
	void Send2PlayerNowActivitys( CEntityPlayer* pPlayer );
	void SendHelpInfo2Client( CEntityPlayer* pPlayer );
	void FillGuideIncInfo( CEntityPlayer* pPlayer, PBTodayIncItem* pData );
	int  GetActivityStateByID( int nActivityID );

	// �õ�����/������ɻ����
	int  GetTodayCompleteTimes( CEntityPlayer* pPlayer,  int nActivityID );
	int  GetWeekCompleteTimes( CEntityPlayer* pPlayer,  int nActivityID );

	// �õ������ĵ����ID
	int  GetActivityOgreDropID( int nOgreTempID );
	void OnMessageGetActivityInfo( CEntityPlayer* pPlayer, CMessage* pMessage );
	int  GetReplaceDropID(CEntity* pEntity);
	void GetAddDropID(CEntity* pEntity, std::vector<int>& vAddIDs);
	
	// �Ѹ���IDת�ɶ�Ӧ�ĻID
	int ChangeRepetionIDToActivityID( int nRepetionID );

public:

	// ����������
	virtual void OnLaunchServer( );

	// �˳�������
	virtual void OnExitServer( );

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffsekt );

	// ��������	   
	virtual int OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName );


	// ·����Ϣ
	virtual void OnRouterMessage( CMessage* pMessage );

	// �ͻ��˷�����Ϣ
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����ʵ��
	virtual void OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst );

	// ����ʵ��
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode );
	
	// �洢����
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode );
	
	// ��������
	virtual void OnLoadConfig( );
	
	// ��ʱ��Ϣ
	virtual void OnTimeoutMessage( CMessage* pMessage );

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }

	// ������Ϣ
	void OnGateMessage( CMessage *pMsg );

	// ����˫��ʱ���
	bool AppendDoubleTime(time_t nStartTime, time_t nEndTime, int nRate );		// ��ʱ��γ�ͻУ��
	bool AppendDoubleTime(const char* tpDate, int nExistTime, int nRate = SERVER_PERCENT_INT );	// û��ʱ��γ�ͻУ��

	// ɾ��˫��ʱ���
	bool RemoveDoubleTime(time_t nStartTime, time_t nEndTime );
	
	// ����ɢϲ�ǵ�֪ͨ
	void SendThrowSugarNotify( CEntity *pEntity );	
	bool RegisterLua();	
	
	// ��һ�쵽��
	virtual void OnNewDayCome( );
public:			

	// �����������֪ͨ
	void SendThrowHydrangeaNotify(  int nThrowType,  CEntityPlayer *pDesPlayer, CEntity *pNpc, CEntityPlayer *pSrcPlayer );
	
	// �����������֪ͨ
	void SendGrabHydrangeaEnableNotify( CEntityPlayer *pPlayer, CEntity *pEntity );	 	

	// ������Ļ�Ӧ��Ϣ
	void SendGrabHydrangeaResponse( CEntityPlayer *pPlayer, int nErrcode );
	
	// ������Ľ��֪ͨ
	void SendGrabHydrangeaResultNotify(  CEntityPlayer *pDesPlayer, int nSrcPosX, int nSrcPosY, const char *pSrcName = NULL );
	
	// �������Ľ��֪ͨ
	void SendHydrangeaResultNotify( CEntityPlayer *pPlayer );	

	// ��������ʼ��֪ͨ
	void SendStartHydrangeaNotify( int nMapID, int nPosX, int nPosY );
	
	// ������Ļ�Ӧ��Ϣ	
	void SendThrowHydrangeaResponse( CEntityPlayer *pPlayer, int nErrcode );	
	
	// �������������Ϣ
	void OnMessageGrabeHydrangeaRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// �����������
	void OnMessageThrowHydrangeaRequest( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ��ʼ����
	void StartHydrangeaActivity( int nActivityID );
	
	// ��������
	void EndHydrangeaActivity();

	// �����������Ϣ
	void ClearHydrangeaInfo();
	
	// ���npc���ƶ�·��
	void CheckNpcPath();
	
	// ������������Ƿ�ʼ
	void CheckHydrageaActivityTime();
	
	// �������׼�ʱ��
	void OnTimeOutHydrangeaActivity( CTimerItem *pTimer );
	
	// ������ļ�ʱ��
	void OnTimeOutHydrangeaThrow( CTimerItem *pTimer );
	
	// ��ϲ�ǵļ�ʱ��
	void OnTimeOutHydrangeaSugar( CTimerItem *pTimer );
	
	// ռ������ļ�ʱ��
	void OnTimeOutHydrangeaHold( CTimerItem *pTimer );
	
	// ��������ļ�ʱ��
	void OnTimeOutHydrangeaGrab( CTimerItem *pTimer );
	
	// ϵͳ��������
	void ThrowHydrangeaBySys();
	
	// ������
	void PlayerGrabHydrangea( CEntityPlayer *pOriginalPlayer, CEntityPlayer *pNewPlayer );
	
	// ������
	void PlayerThrowHydrangea( CEntityPlayer *pPlayer );
	
	// ���������������״̬��֪ͨ
	void SendSetHydrangeaStatusNotify( CEntityPlayer *pPlayer, int nStatus );
	
	// �����ҵ�����״̬
	void ClearHydrangeaStatus( CEntityPlayer *pPlayer );

	// ������Ǭ����������
	int  OnUseLuckyBag( CEntityPlayer* pPlayer, CTplFuncItem* pItem, int vIndex );
	
	// ��ʼ������ñ�
	int InitialOgreActivityConfig( const char *pFileName );
	
	// ˢ�¹���ʱ������Ļ��Ϣ
	int CheckOgreActivityInfoOnCreate( int nTempID, int nEntityID = 0 );
	
	// ��������ʱ������Ļ��Ϣ
	int CheckOgreActivityInfoOnDeath( int nTempID, int nkillerID = 0 );
	
	// ��������
	int EndOgreActivity( CTimerItem *pTimer );
	
	// ��ȡ��ֵ���Ϣ
	COgreInfo * GetActivityOgreInfo( int nTempID );
	
	// ������¼� (�ⲿ����)
	int  FireActivityEvent( int nActivityID, int nEventID, const std::vector<int>& rIntParams, std::vector<std::string>& rStrParams  );
	
	// ����������֤����Ϣ
	void BuildQuestionVerifyMsg( CMessageQuestionVerifyNotify &rMsg, SRoleValidQuestionOption* pResults );

	// ���������
	void BuildQuestionOptionData(SRoleValidQuestionOption* pInputOption, SRoleValidQuestionOption* pOutputOption);
	
	// ֪ͨ������֤
	void NotifyQuestionVerify( CEntityPlayer *pPlayer,  int nVerifyKind, int nVerifyType, int nVerifyTimeLength = 0 );
	
	// �ͻ��˴�����֤�Ľ��֪ͨ
	void OnMessageAnswerVerifyRequest( CEntityPlayer *pPlayer, CMessage *pMsg );
	void OnMessagePlayerGetGiftRequest( CEntityPlayer *pPlayer, CMessage *pMsg );

	// ������֤�Ľ��
	void NotifyQuestionVerifyResult( CEntityPlayer *pPlayer, int nVerifyKind, bool bResult, int nReason = VERIFYREASON_ANSWER );
	
	// ���ʹ�����֤�Ľ��
	void SendResponseAnswerVerify( CEntityPlayer *pPlayer, int nResult );
	
	// ������֤��ʱ
	void OnTimeOutAnswerVerify( CTimerItem *pTimer );
	
	// ��ȡ��Ƭ��֤������
	void ReadRoleValidQuestionConfig();
	
	// ��ʼ����Ƭ��֤��Ϣ
	int InitializeRoleValidQuestionInfo();
		
	int ChangeActivityState( CEntityPlayer* pPlayer, int nActivityID, int nNewState, int nStateParam1, int nStateParam2, bool bIsNotify, bool bIsSetTime );
	int OnPlayerLevelUp(CEntityPlayer* pPlayer);
	
	// ��ѯ��Ʒ�۱���Ϣ
	void OnMessageGetTreasureBowl( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ���Ͳ�ѯ��Ʒ�Ļ�Ӧ��Ϣ
	void  SendResponseGetTreasureBowl( CEntityPlayer *pPlayer, int nErrcode, int nItemIndex, int nItemUsedTimes = 0, int nItemTatolTimes = 0, int nAllUsedTimes = 0, int nTotalTimes = 0, int nTaxMoney = 0 );
	
	// ��ʼ��Ʒ�۱�
	void OnMessageStartTreasureBowl( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ���Ϳ�ʼ��Ʒ�۱��Ļ�Ӧ��Ϣ
	void SendResponseStartTreasureBowl( CEntityPlayer *pPlayer, int nErrcode, int nItemIndex = 0, int nNewItemID = 0 );
	
	// ���;۱��ɹ�����Ӫ��ʾ
	void SendTreasureBowlSuccessNotify( CEntityPlayer *pPlayer, int nOldItemID, int nNewItemID, int nItemNum, int nTipsType );	
	void OnlineGift4CreateEntity(CEntityPlayer* pPlayer, int nActivityID, bool vFirst );

private:   
	CQuestionManager mQuestionMng;
	CInvestQuestionManage mInvestQuestionMng;
	CWTimer			 mTimer;
	CWTimer			 mHydrangeaTimer;
	CWTimer			 mInvestRecordTimer;
	
	// ��ɫ��֤����
	SRoleValidQuestion mRoleValidQuestions[ROLE_VALID_QUESTION_COUNT];	
	// ��ɫ��֤ѡ��
	SRoleValidQuestionGroup mRoleValidQuestionGroups[ROLE_VALID_QUESTION_GROUP_COUNT];	
	// ��ɫ����
	int mRoleValideQuestionCount;
	// ��Χ
	int mRoleValidQuestionRange;
	// ������֤���⽱������Ϊ��ID
	int mTalentTableID;	
	/*
	RefreshDate mDoubleTime[ 30 ];
	int			mExistTime[ 30 ];
	int			mCount;
	*/

	class CRefresh
	{
	public:
		RefreshDate first;		// ��ʼʱ���, Ϊ�˱�����֮ǰ����, �ֶ�����Ϊ����
		int			second;		// ����ʱ��, Ϊ�˱�����֮ǰ����, �ֶ�����Ϊ����
		int 		rate;		// ��������, ������Ϊ�㣬����10000Ϊ��λ1

		CRefresh() {}
		CRefresh(RefreshDate& from, int nSeconds, int nRate)
		{
			first = from;
			second = nSeconds;
			rate = nRate;
		}
	};


	typedef lk::vector< CRefresh, 30> CDoubleTime;
	CDoubleTime mDoubleTime;

	bool		mDoubleActive;
	CWTimer		mDoubleTimer;
	unsigned int mEndTime; // ����ʱ��(����ʱ�� time_t )
	int			mDoubleIndex;

	NpcBidInfo  mNpcInfo[ 1000 ];
	int			mNpcNum;
	CHydrangeaNpcManager mHydrangeaNpcManager;
	CHydrangeaActivityManager mHydrangeaActivityManager;
	COgreActivityManager mOgreActivityManager;
	CTreasureBowlManager mTreasureBowlManager;
public:

	// ���ͳ�ƽ��
	int WriteInvestResultToFile();	
	
	// ��ȡ�����ͳ�ƽ��
	int GetInvestResult();

// ��LUA���õĽӿ�
public:
	// �õ���ҵȼ�
	static int GetPlayerLevel( int nEntityID );

	// �õ��������
	static int GetPlayerMetier( int nEntityID );

	// �õ���Ұ����ո���
	static int GetPlayerBagSpaceNum( int nEntityID );

	// ����ҽ�����Ʒ (֧�ּ���װ��)
	static int InsertItem( lua_tinker::table param );

	// ��������
	static int SendErrNotice( int nEntityID, int nErrID );

	// �õ�����Ա�
	static int GetPlayerGender( int nEntityID );

	static void Log_Error( const char* pStr );

	// ��ϵͳ�ʼ�
	static bool SendSysMail( lua_tinker::table param );

	// ��������Ӫ
	static int  GetCampID( int nEntityID );

	////////////// ������� ///////////////////////////////////////////////////////////////////////////////
	
	// ��û״̬
	static int  GetActivityState( int nActivityID );

	// �޸�ȫ����һ״̬ 
	// ������
	static int  ChangeAllActivityState( lua_tinker::table param );

	// �޸���һ״̬
	static int  ChangeSingleActivityState( lua_tinker::table param );

	// �������BUFF
	static int  EntityInsertBuff( int nEntityID, int nBuff, int nBuffTime );

	// ����ʵ��
	static int  EntityTeleport( lua_tinker::table param );

	// ���ѵ� 
	static bool  CheckPileLimit( int nEntityID, int nTempID, int nNum );

	// ֪ͨ�ͺ�����
	static void NotifyGetGiftResult( int nEntityID , int nRet, int nGiftType );

 //���ü��صĻص�����
public:
	static void LoadQuestionFileCallback(const char* pcConfigPath);
	static void LoadLuaFileCallback(const char* pcConfigPath);
	static void LoadInvestQuestionFileCallback(const char* pcConfigPath);
	static void LoadDoubleExpFileCallback(const char* pcConfigPath);
	static void LoadHydrangeaCallback(const char* pcConfigPath);
	static void LoadOgreActivityConfigCallback(const char* pcConfigPath);
	static void LoadTreasureBowlConfigCallback(const char* pcConfigPath);
	static void LoadActivityYqsConfigCallback(const char* pcConfigPath);
	static void LoadRoleValidQuestionConfigCallback(const char* pcConfigPath);

};

