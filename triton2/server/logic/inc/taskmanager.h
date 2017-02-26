#pragma once
#include "protype.h"
#include "westserver.h"
#include "property_pb.hxx.pb.h"
#include "taskmessage_pb.hxx.pb.h"
#include "tasktype.h"
#include "sceneobj_define.h"
#include "entity.h"
#include "servercore.h"
#include "familytype.h"

struct st_storage_data
{
	unsigned short m_usBackRefreshTasks[STORAGE_SIZE];
	unsigned short m_nRefreshNum;
	st_storage_data ()
	{ 
		if ( CObj::msCreateMode)
		{ memset( m_usBackRefreshTasks, 0, sizeof(m_usBackRefreshTasks) ); m_nRefreshNum = 0;}
	}
};

struct st_event
{
	unsigned int nEventID;
	unsigned int nParam;
	st_event()
	{
		if ( CObj::msCreateMode)
		{ nEventID = 0 , nParam = 0 ;}
	}
	st_event( unsigned int vEventID, unsigned int vParam )
		: nEventID ( vEventID ), nParam( vParam )
	{}
	bool operator < ( const struct st_event& other )  const;
};

struct st_event_single
{
	st_event stevent;
	int		 nTicked;	// ��Ӧ�˶��ٴ�

	st_event_single()
	{
		if ( CObj::msCreateMode)
		{ nTicked = 0; }
	}
	st_event_single( int vEventID, int vParam );

	bool operator < ( const struct st_event_single& other )  const;
};


struct st_drop_data 
{
	int m_ItemID;	// �������Ʒ��ID
	int m_n;		// ��������
	int m_p;		// �������
	int m_maxn;		// ���������Ҫ�Ѽ�����Ʒ�ĸ���

	st_drop_data()	
	{
		m_ItemID = 0; m_n = 0; m_p = 0; m_maxn = 0; // �������ʱ���� ���ô���ڹ����ڴ� ��reload��ʱ������¼���
	}
};

// �������� �����ṹ
struct st_tragedy_task
{
	unsigned short  us_NextTaskID;// �����ĸ��������ˣ������û���������0���ڽ������ʱ������Ϊ��һ�������񣬲������ͻ���,ȫ������ˣ�Ҳ��0 ����״̬�����״̬
	short	        s_State;	 // ��ǰ״̬

	st_tragedy_task()
	{
		if ( CObj::msCreateMode)
		{ us_NextTaskID=0;s_State=0; }
	}
};

struct st_invite_data
{
	char name[NAME_LENGTH];
	unsigned short task_id;
};

struct st_refresh_data 
{
	int rTaskID;
	int rTaskColor;
	bool bflag;

	void Inintialize()
	{
		rTaskID = 0;
		rTaskColor = 0;
		bflag = false;
	}
	st_refresh_data()
	{
		rTaskID = 0;
		rTaskColor = 0;
		bflag = false;
	}
};


typedef std::map<unsigned short, st_storage_data>			STORAGE_TASKS_CONTAINER;
typedef std::map<int, st_drop_data>							DROP_DATA_CONTAINER;
typedef lk::hash_map<unsigned int, std::vector<st_invite_data>, SERVER_CAP_PLAYER > TASK_INVITE_CONTAINER;
typedef lk::hash_map<unsigned short, int, TASK_LIST_SIZE>					ID_MAP_CONTAINER;
//typedef lk::hash_map<unsigned short, unsigned short>			SAVE_DB_TASKS_TYPE;

// ***********************************************************
//  ����������	���ʴ����ļ�
// **********************************************************
class CDir
{
private:
	DIR *dir;
	struct dirent *dp;
public:
	int bad;
	CDir(const char* dirpath);	  
	const char* file();
	~CDir();
};


// ***********************************************************
//  ����������	�����������������ۻ��������������ͨ����
// **********************************************************
class CTask
{
public:
	unsigned short		mTaskID;			// ����ID
	unsigned short		mTaskProgress;		// �������
	int					mTimerID;				// ��ʱ����ļ�ʱ��ID
	int					mGameTimeLeft;			// ��Ϸʱ��ʣ������ ����ʱ����Ϊ-1 ע��ʵ�ʼ�ʱ�Զ�ʱ��Ϊ�� �����ֵֻ���ڽ���������ߵ�ʱ�������
	unsigned int		mTaskData[TASK_DATA_SIZE]; // �������� һ������pair��ʽʹ��
	unsigned int		mWatchEventN;		// �����¼�ʣ�����  �����ڸ�EntiyDie����
	int					mTalkedNpc[MAX_NPC_TALK_NUM]; // �Ѿ��Ի�����NPC
	int					mTalkedNum;
	int					mExFlags;			// ������ Ϊ������ Ŀǰ�����ȼ�ɱ���õ��� ö�ټ�enTaskExFlags
	int					mTaskBeginTime;		// ��������ʱ��

private:
	CSearchArray<st_event,	MAX_EVENTS_PER_TASK>  mEventData;

public:
	CTask();

public:
	void RegEventTick( unsigned int vEventID, unsigned int vParam, unsigned int vNum );
	// �Ƿ����� ����Ǽ����¼����ڴ���ӵ�����
	bool IsEventTick ( unsigned int vEventID, unsigned int vParam );
	void GetTaskDataStruct(TaskStruct* pData);
	unsigned short		GetTaskProgress() {return mTaskProgress; } // �õ��������
	void SetTaskProgress( TaskState state ) {  mTaskProgress = state; } // �õ��������

	// �Ƿ��ĳNPC�Թ���
	bool IsTalkedWithNpc( int nNpcTempID );

	// ���Ӻ�NPC�ĶԻ�
	bool AddTalkedWithNpc( int nNpcTempID );
	// ����
	bool RemoveTalkedWithNpc( int nNpcTempID );

	inline void SetTaskData(unsigned int idx, unsigned int v) { if(idx < TASK_DATA_SIZE) mTaskData[idx] = v; } 
	inline unsigned int GetTaskData(unsigned int idx){ return (idx < TASK_DATA_SIZE) ? mTaskData[idx] : 0; }

	// �õ���һ��ĳ�¼���param
	int GetFirstParamByEvent( int nEventID );
};

// ***********************************************************
//  ����������	�����������
// **********************************************************
class LoopTaskData
{
protected:
	unsigned int		mTodayCompletedCircles;	// �����Ѿ���ɵ����л�����Ĵ���
	time_t				mLastCompletedTime;	    // �ϴ���ɻ������ʱ��

	unsigned short		mLoopTasks[MAX_LOOP_SUB_TASKS];
	int					mCompletedTimes;		    //  ����ɴ���(����)
	time_t				mLastAbortTime;		    //  �����ϴη���ʱ��
	short				mCurSubIndex;		    //  ��ǰ�����е�������������ֻ�н�����Ż���¸�ֵ����������ֵ���� ��ʼ-1
	short				mSubTasksNum;			//  �����������
	int					mWeekLoops;				//  ����Ȼ����ɵ�����  ÿ������ֻ��1��
	int					mDayCompletedLoopFlag;	//  �����Ƿ����һ���ֻ�����ı�־
	int					mCompletedSingle;		//  ��ɻ�����ĸ������������ۼ���1�֣�10����Ȼ����0
	void				CheckInitTodayLoops();


public:
	LoopTaskData();
	bool GetRndTasks( unsigned short arrSrc[], int nSrcNum, int nOutNum, unsigned short* pOut );
	void Clear();

public:
	// =====  Gets ==== //
	int     GetDayCompletedLoops() {return mDayCompletedLoopFlag;}
	int     GetSubTaskNum() {return mSubTasksNum;}
	int		GetCompletedTimes();
	time_t	GetLastAbortTime();
	short   GetCurSubTaskIndex();
	unsigned short GetSubTaskIDbyIndex(short usIndex);
	int     GetLoopTaskNum();
	// ������ɻ�����
	bool    PlayerGetLoopTask( unsigned short usArrSrc[], int n );
	int     GetTodayCompletedTimes();
	unsigned short GetLastLoopTaskID();

	// =====  Sets ==== //
	bool   SetCurSubTaskID( unsigned short vSubTaskID );
	void   SetAbortData( );
	// ��������һ�ֵ�ʱ�����
	int    SetEndLoopData( );
	void   GetTlvBuffer2(PBLoopTaskData*& pBuffer);
	void   CreateFromTlv2(PBLoopTaskData*& pBuffer);
	// ÿ���һ�����������Ӧ ������������1�� �򷵻ر������� ���򷵻�0
	int   OnCompletedTask( unsigned short vTaskID );
	// �õ��ڼ���(��1��ʼ���Ҳ����򷵻�0)
	int    GetLoopByTaskID( unsigned short usTaskID );
	unsigned short	GetWeekLoops(){ return  mWeekLoops;	}			//  ����Ȼ����ɵ�����  ÿ������ֻ��1�� 
	// ��һ��Ĵ���
	void   OnNewDay();
	// ��һ�ܵĴ���
	void   OnNewWeek();
	// �õ��������һ��������ID
	unsigned short  GetOneSubTaskID() { return mLoopTasks[0]; }
};


// ***********************************************************
//  ����������	�¼�������
// **********************************************************
class CTaskEventManager
{
public:
	CSearchArray<st_event_single, MAX_SAVE_EVENT> mEvents;

public:
	bool RegEvent( unsigned int nEventID, unsigned int nParam ); // ��������¼�¼�
	int  GetTickNum( unsigned int nEventID, unsigned int nParam ); // �õ���������
	bool RemoveTick( unsigned int nEventID, unsigned int nParam , int n ); // ����¼���¼
};


class CTaskList;
// **********************************************************
//  ����������	�����񣨻ʰ����񣩹�����
// **********************************************************
class CStorageTaskManager
{
	friend class CTaskList;
private:
	CSearchArray<unsigned short, MAX_STORAGETASK_LIST_NUM> m_Tasks; // ������ϵĿ������б�
	CSearchArray<unsigned short, MAX_STORAGETASK_LIST_NUM> m_GotTasks;  // �ѽ��ܵ�

	time_t		   m_nLastClickNpc;		// ����ϴε��NPC��ʱ�䣨����Ǵ��գ���ˢ�������б�
	unsigned short m_usCurID;			// ��ǰ������ID
	int			   m_nGotNum;			 //  �Ѿ��������ϵĿ���������
	int			   m_nTodayCompleted;	//	�����Ѿ���ɵĴ��� (����Ժ��޸�)
	int			   m_nTodayRMBTimes;	// �����Ѿ�ʹ��RMB����ˢ�¹��Ĵ���

public: //TODO:�ڷ������Իָ�ģʽ������ʱ��Ҫ���³�ʼ��
	static STORAGE_TASKS_CONTAINER m_Storage;
	static void	RefreshStorage(unsigned short vTaskID);
	static void	RefreshStorageOnTime( );

	CStorageTaskManager();
	bool IsInList( unsigned short usTaskID );
	void RemoveFromList( unsigned short usTaskID );
	bool OnAbortTask( unsigned short vTaskID );
	bool OnEndTask( unsigned short vTaskID );
	int	 GetGotNum() { return m_nGotNum; }
	int	 GetTaskNum() { return m_Tasks.GetNum(); }

	int	 GetTodayCompleted() { return m_nTodayCompleted; }
	void ZeroTodayCompleted() { m_nTodayCompleted = 0; }
	void PlusTodayCompleted() { ++m_nTodayCompleted; }

	void GetTlvBuffer2(PBStorageTaskData*& pBuffer);
	void CreateFromTlv2(PBStorageTaskData*& pBuffer);

	unsigned short GetCurTaskID() { return m_usCurID; }

	int  GetTodayRMBTimes() { return m_nTodayRMBTimes; }
	void ZeroTodayRMBTimes() { m_nTodayRMBTimes=0; }
	void PlusTodayRMBTimes() { ++m_nTodayRMBTimes; }
};



// **********************************************************
//  ����������	�������������
// **********************************************************
class CTragedyTaskMgr
{
public:
	// �õ�ĳ�����Ѹý��е�������ID
	unsigned short GetNextTask( short vTragedyIndex );
	void		   SetNextTask( short vTragedyIndex, unsigned short vTaskID );
	int			   GetState( short vTragedyIndex );
	void		   SetState( short vTragedyIndex, enTragedyTaskState vState );

	void CreateFromTlv2( PBTaskList* pBuffer );
	void GetTlvBuffer2( PBTaskList* pBuffer );

	int  GetAllInfo( int *anIndex, unsigned short *asNextID, int *anState );

	void Clear( int nIndex );

	CTragedyTaskMgr() { m_nCompleted = 0; }
	void PlusCompleted() { ++ m_nCompleted; }
	int  GetCompleted() { return m_nCompleted; }
	void SetCompleted(int nVal) {m_nCompleted = nVal;}
private:
	st_tragedy_task m_tasks[TRAGEDY_TASK_SIZE+1]; // ��1��ʼ�������洢
	int				m_nCompleted;	// ����ɵĽ��Ѹ���
};


// ***********************************************************
//  ����������	 ��������Թ�����
//  ��Ҫ������
//  ά������Ϊ��λ����������
// **********************************************************
class CTaskGroupData
{
private:
	int				mTodayTimes;	// ������ɴ���
	int				mTodayAccptTimes;	// ���ս�ȡ����
	int				mWeekTimes;		//��������������
	int				mWeekAccptTimes;   //���ܽ�ȡ����

public:
	CTaskGroupData()
	{
		if ( CObj::msCreateMode )
		{
			mTodayTimes = 0;
			mTodayAccptTimes = 0;
			mWeekTimes = 0;
			mWeekAccptTimes = 0;
		}
	}
	void OnEndOneTask();	// �����һ�α��������
	void OnAccptOneTask();	// ��ȡ��һ�α��������


	int GetTodayTimes() { return mTodayTimes;}
	int GetTodayAccptTimes() { return mTodayAccptTimes;}
	int GetWeekTimes(){ return mWeekTimes; }
	int GetWeekAccptTimes(){return mWeekAccptTimes; }

	void SetTodayTimes( int nValue) { mTodayTimes = nValue;}
	void SetTodayAccpTimes( int nValue) { mTodayAccptTimes = nValue;}
	void SetWeekTimes(int nValue) { mWeekTimes = nValue; }
	void SetWeekAccptTimes(int nValue) { mWeekAccptTimes = nValue; }

};

typedef lk::hash_map<unsigned int, CTaskGroupData, MAX_TASKGROUP_NUM> TaskGroupMgrType;

class CTaskGroupManager
{
private:
	TaskGroupMgrType mData;

public:
	CTaskGroupManager()
	{
		if (CObj::msCreateMode)
		{
			mData.initailize();
		}
	}

public:	// interfaces
	int  OnEndOneTask( unsigned int nGroupID );	// �����һ������ID������
	int  OnAcceptOneTask( unsigned int nGroupID );	// ������һ������ID������

	int  GetTodayTimes( unsigned int nGroupID );	// �õ��������ĳ����������
	int  GetTodayAcceptTimes( unsigned int nGroupID );	// �õ��������ĳ����������
	int  OnNewdayCome();	// �µ�һ�쵽��
	void  SetTodayTimes( unsigned int nGroupID, int nTimes );

	int	 GetWeekTimes( unsigned int nGroupID ) ;      //�õ��������ĳ������Ĵ���
	int  GetWeekAcceptTimes( unsigned int nGroupID ); //�õ����ܽ���ĳ������Ĵ���
	int  OnNewWeekCome();	// �µ�һ�ܵ���
	void  SetWeekTimes(unsigned int nGroupID, int nTimes );

public:	// data manager
	void CreateFromPB( PBTaskList* pBuffer );
	void GetPBBuffer( PBTaskList* pBuffer );
};


// **********************************************************
//  ����������	�������������
// **********************************************************
struct SingleChairManTask_T
{
	unsigned short  mTaskID;
	int				mState;
};

typedef lk::hash_map<unsigned short, int, 50> CHAIRMAN_COMPLETED_TYPE;

class CChairManTaskManager
{
private:
	//SingleChairManTask_T  m_Tasks[CHAIRMAN_TASK_NUM]; // ���ר���������б�
	unsigned short  m_usCurID;			// ��ǰ��������ID
	int				m_nAccepted;		// ��ǰ�ѽ�������
public: 
	CHAIRMAN_COMPLETED_TYPE mCompleted; // ���������
	CChairManTaskManager();
	void Initialize();
	void GetTlvBuffer2(PBChairManTaskData* pBuffer);
	void CreateFromTlv2(PBChairManTaskData* pBuffer);
	void FillMessage2Cli( CMessageGetChairManTaskResponse* pMsg );
	unsigned short GetCurID( ) { return m_usCurID ; } 
	int  GetCompleteNum( ) ;
	void ResetTasks( int nCurID );
	void OnTaskEnd();
	bool CheckAcceptChairMan( unsigned short usChairManID );
	void OnAccepted();
	void OnAborted();
	int  GetAcceptedNum() {return m_nAccepted;}
	void SetAcceptedNum( int nAcc ) { m_nAccepted=nAcc;}
};

typedef lk::hash_map<unsigned short, unsigned short, PUBLISH_LIST_SIZE> PUBLISHTASK;// �����������Ϣ    first : ����ID second :����״̬


struct GroupTempInfo
{
	unsigned int GroupID;		// ����ID
	unsigned int GroupLevel;	// ����ȼ�
	unsigned int GroupMoney;	// �����Ǯ
	unsigned int PlayerPosition; // ����������ְλ

	GroupTempInfo()
	{
		GroupID			= 0;
		GroupLevel		= 0;
		GroupMoney		= 0;
		PlayerPosition	= 0;
	}
	GroupTempInfo(unsigned int ID, unsigned int Level, unsigned int Money, unsigned int Position)
	{
		GroupID				= ID;
		GroupLevel			= Level;
		GroupMoney			= Money ;
		PlayerPosition		= Position;
	}
};
// ***********************************************************
//  ����������	�����������Ԫ
// **********************************************************
class CTaskList : public CObj
{
public:
	unsigned short					mTaskNumber;		// �ѽ��ܵ��������
	CTask							mTaskList[ TASK_LIST_SIZE ];	// �ѽ��ܵ������б�
	//unsigned char					mCompleteTasks[COMPLETE_TASK_BIT_SIZE]; 
	lk::hash_map<unsigned short, unsigned short, COMPLETE_TASK_NUM> mCompleteTasks;// ��ɵ��Ҳ����ظ���������
	//unsigned char					mFailedTasks[COMPLETE_TASK_BIT_SIZE]; // ʧ�ܵ��ǲ����ظ���������
	lk::hash_map<unsigned short, unsigned short, FAILED_TASK_NUM> mFailedTasks;// ʧ�ܵ��ǲ����ظ���������

	lk::hash_map<unsigned short, int, COMPLETE_TASK_NUM> mRepeatTasks;// ��ɵĿ��ظ���������

	st_refresh_data mRememberRefreshNum[ TASK_LIST_SIZE ];  // ����¼��T����Ʒ������

	LoopTaskData					mLoopTaskData;      // ����������
	CTaskEventManager				mEventMgr;
	CStorageTaskManager				mStorageTaskMgr;    // ����������
	CTragedyTaskMgr					mTragedyTaskMgr;	// �������������
	CTaskGroupManager				mTaskGroupMgr;		// �����������
	CChairManTaskManager			mChairManTaskMgr;	// �������������

	// ��������
	GroupTempInfo					mGroupTempInfo;
	PUBLISHTASK						mCorpsPublishTask;  // ���ŷ���

	unsigned int					mTickEvents;		// ��Ӧ��ȫ��Ψһ�¼�

	// ���£�ʵʱ���� ���ô�
	int								mBossNpcEntityID;   // ���������NPC��BOSS���� ��¼��NPC��ʵ��ID
	int								mPlayerCurTalkNpcID;// ��ҵ�ǰ��̸��NPC ��ʱ��� �ڻỰ��Ϻ����̸ɵ�
	int								mPlayerCurSendNpcID;// ��ҵ�ǰ�Ļ���NPC ʵ��ID
	int								mInvitingPlayerID;	// ����������ʵ��ID
	time_t							mLastLogOffTime;	// ����ϴ�����/���ʱ���
	unsigned short					mRedirectFailTask;	// ���ͼʧ�ܵ����� ��ͬʱ����ֻ������1����
	int								mOwnerEntityID;	// ���˵�ʵ��ID
	int								mTodayTeamLoopNum; // ������ɵ���ӻ�����ĸ���

public:
	CTaskList( ) ;
	~CTaskList( ) ;
	// ��ʼ��
	virtual int Initialize();
	// �ָ�
	virtual int Resume(); 

private:
	ID_MAP_CONTAINER _IDmap;
	void RebuildIndex();
	inline int  GetTaskIndex( unsigned short vTaskID )
	{
		ID_MAP_CONTAINER::iterator it = _IDmap.find( vTaskID );
		if ( it != _IDmap.end() )
			return it->second;
		else
			return -1;
	}

public:
	void Clear( );

	// �õ�����״̬
	int GetTaskState( unsigned short vTaskID );

	// ���������״̬
	int SetTaskState( unsigned short vTaskID, int State );

	// �ж������Ƿ��ڽ�����
	bool IsTaskProgress( unsigned short vTaskID );

	// �ж������Ƿ���������ڿ��ظ�������Զ����δ����
	bool IsTaskEnd( unsigned short vTaskID ){ return mCompleteTasks.find(vTaskID) != mCompleteTasks.end(); }

	// ���������ɱ�־
	void ClearTaskEndFlag( unsigned short vTaskID ){ mCompleteTasks.erase(vTaskID); }
	
	// �ж������Ƿ�ʧ�ܣ����ڿ�����������Զ����δʧ��
	bool IsTaskFailed( unsigned short vTaskID )	{ return mFailedTasks.find(vTaskID) != mFailedTasks.end(); }

	// �ж������Ƿ���ɣ���ɺͽ��������������ɴ������������Ҫ�󵫻�û�н���������ʾ�Ѿ�����
	bool IsTaskComplete( unsigned short vTaskID );

	// ��������
	void TaskReset( );

	// �������
	int InsertTask( const CTask& rTask );
	void SetGroupInfo(const GroupTempInfo &TempInfo)
	{
		mGroupTempInfo = TempInfo;
	}

	// ɾ������
	void RemoveTask( int vTaskID );

	// �õ���������
	CTask* GetTask( unsigned short vTaskID );

	void CreateFromTlv2( PBTaskList* pBuffer );
	void GetTlvBuffer2( PBTaskList* pBuffer );
	void SetEnd(unsigned short vTaskID);
	bool GetEnd(unsigned short vTaskID);

	void SetEndTime(unsigned short vTaskID, int vEndTime);
	int GetEndTime(unsigned short vTaskID);
	void SetFailed(unsigned short vTaskID);
	bool GetFailed(unsigned short vTaskID);
	int InsertRefreshedTask(unsigned short vTaskID , int taskColor );  // ����һ���µ�ˢ���������

	// ����������ⲿ�ӿ�
	void GetStorgeTaskList( NpcTaskList* pList, unsigned short usTaskID );
	void RefreshTasks( ETaskRefreshType etype );

	void SetBossNpcEntityID( int vEntityID ) { mBossNpcEntityID = vEntityID; }
	int  GetBossNpcEntityID( ) { return mBossNpcEntityID ; }

	void SetTalkNpcEntityID( int vEntityID ) { mPlayerCurTalkNpcID = vEntityID; }
	int  GetTalkNpcEntityID( ) { return mPlayerCurTalkNpcID ; }

	void SetSendNpcEntityID( int vEntityID ) { mPlayerCurSendNpcID = vEntityID; }
	int  GetSendNpcEntityID( ) { return mPlayerCurSendNpcID ; }

	void SetInvitingPlayerID( int nVal ) { mInvitingPlayerID = nVal; }
	int  GetInvitingPlayerID( ) { return mInvitingPlayerID; }

	void SetOwnerEntityID( int nVal ) { mOwnerEntityID = nVal; }
	int  GetOwnerEntityID( ) { return mOwnerEntityID; }

	int GetTaskColor(unsigned short vTaskID);
	void RemoveTaskColor(unsigned short vTaskID);

	// ÿ������ ��װ
	void OnNewdayCome();
	void OnNewWeekCome();

	int GetTodayTeamLoopNum() { return mTodayTeamLoopNum; }
	void ZeroTodayTeamLoopNum() { mTodayTeamLoopNum=0; }
	int PlusTodayTeamLoopNum() { return ++mTodayTeamLoopNum; }

	void InsertPublishTask(unsigned short vTaskID, unsigned int vTaskType, unsigned int vTaskState);

	unsigned short GetPublishStateByType(unsigned short vTaskID, unsigned int vTaskType);
	void SetPublishTaskState(unsigned short vTaskID, unsigned short vTaskState,unsigned int vTaskType);

};

// �������뻤�͵���ҵĻ�������
struct st_singlesendplayer_data
{
	int mPlayerID;
	int mLeaveTime; // �뿪NPC��ʱ�� һ���ص������ ����0
	st_singlesendplayer_data()
	{
		if ( CObj::msCreateMode )
		{
			mPlayerID = 0;
			mLeaveTime = 0;
		}
	}
	st_singlesendplayer_data( int nPlayerID, int nLeaveTime )
	{
		mPlayerID = nPlayerID;
		mLeaveTime = nLeaveTime;
	}

	bool operator < ( const st_singlesendplayer_data& other ) const
	{
		return mPlayerID < other.mPlayerID;
	}
};

// ***********************************************************
//  ����������	������ҵĻ����������ݽṹ
// **********************************************************
class CSingleSendNpc
{
private:
	int mX[ MAX_WAY_POINTS ];
	int mY[ MAX_WAY_POINTS ];
	int mMapID[ MAX_WAY_POINTS ];
	int mCurIndex;
	int mTotalIndex; // ��������±�+1��[mTotalIndex-1]���յ�
	int mMaxGird; // ��������
	int mMaxLeaveTime; // ������� �뿪NPC��ʱ��
	int mBuffTime; // ÿ�������һ��BUFF
	int mBuffID;   // Ҫ�ϵ�BUFF ID
	int mBuffTimer;  // ��BUFF��ʱ��
	int mWaitTimer;	// �ȴ���ʱ��
public:
	unsigned int   mNpcEntityID;
	unsigned int   mPlayerEntityID;  // �����͵��˵�ID
	unsigned short mTaskID;

	// ���뻤�͵��˵��б�
	CSearchArray<st_singlesendplayer_data, MAX_FAMILYMEMBER_NUM>	mSendingList;	// ���е�ǰ���뻤�͵��˵��б�

public:
	CSingleSendNpc( int* vpX, int* vpY, int* vpMapID, int vTotal, unsigned int vNpcEntityID, unsigned int vPlayerEntityID
		, unsigned short vTaskID, int vGird, int vLeaveTime, int nBuffTime, int nBuffID, int nInitWait );
	CSingleSendNpc();

	int  OnNpcCtrlTimer( ); // NPC���ƶ�ʱ��
	int  OnPlayerCtrlTimer( std::vector<int>& rFailedPlayers ); // ��ҿ��ƶ�ʱ��
	void Start( );
	CWTPoint GetCurTargetPos();
	int  AddSendingList( int nEntityID ) { return mSendingList.insert( st_singlesendplayer_data( nEntityID, 0 ) ); }
	int  DelSendingList( int nEntityID ) { return mSendingList.remove( st_singlesendplayer_data( nEntityID, 0 ) ); }
	void GetPlayerIDs( std::vector<int>& rEntitys );
};

// ***********************************************************
//  ����������	 ������������� ��ػ���������������̣�ʧ�ܵĻ�ֱ�Ӹ���ҷ���Ϣ��ʾ��Ȼ��ɵ������񡣳ɹ��Ļ�fire event
//  ��Ҫ������
//  1,������������ʵ������¼���ʵ��ID��NPC������·��
//  2,�����쳣��������ߣ�NPC�����ȡ�������
// **********************************************************
typedef lk::hash_map<int, CSingleSendNpc, SERVER_CAP_PLAYER> SendNpcType;

class CSendNpcManager
{
private:
	SendNpcType mSessions;
	int mTimer;

public:
	CSendNpcManager()
	{
		if (CObj::msCreateMode)
		{
			mSessions.initailize();
			mTimer = 0;
		}

	}

	int  StartNewSession( CEntityPlayer* pPlayer, int vNpcTempID, int* vX, int* vY, int* vMapID, int vTotal, unsigned short vTaskID, int vGird, int nNpcEntityID = 0, int vLeaveTime = 0, int nBuffTime = 0, int nBuffID = 0, int nWaitTimer = 0 );
	void OnTimer( int vOffSet );
	void ClearSession( int nNpcEntityID );
	void ClearPlayerSendSession( CEntityPlayer* pPlayer, bool bIsFailed );
	bool GetNpcCurTarget( int nEntityID, CWTPoint& rPoint );
	int  OnResetSendNpc( int nEntityID );
	int  OnSendTaskFailed( std::vector<int>& rEntityIDs );
	void CheckSendingSession( int nNpcEntityID );
};



// ***********************************************************
//  ����������	�������������
// **********************************************************
class CTaskInviteManager
{
public:

	// �����Ƿ�ע��ɹ�
	int RegInvite( unsigned int nEntityID, const char* szName, unsigned short unTaskID );

	// ����Ƿ���ע��������������¼
	bool ChkReg ( int nEntityID, const char* szName, unsigned short unTaskID );
	CTaskInviteManager()
	{
		if( CObj::msCreateMode ) 
			mData.initailize();
	}

private:
	TASK_INVITE_CONTAINER mData;

};


// ***********************************************************
//  ����������	����������ĵ���
// **********************************************************
class CTaskDropItemMgr
{
private:
	// ��������

	DROP_DATA_CONTAINER mDropData[MAX_TASK_NUM];

public:
	void RegDrop( unsigned short usTaskID, int nOgreID, int nItemID, int n, int nP, int nMaxn );
	bool GetDropItems( unsigned short usTaskID, int nOgreID, int& rnItemID, int& rn, int& rnmaxn ); 
	void ClearDrop();
};

// NPC����� �������NPC��״̬ �Ա������һЩȫ�ֵ��¼�  ����һȺ������ʧ�ܵ�
// ͨ��ע��������һЩȺ����Ϊ ��������Χ��Ӧ���߼� ֻ����ָ����ʱ����ָ������
// Ŀǰֻ֧��1�β��� ��������������
// �������ܣ�ά��ȫ��ΨһNPC��ģ��ID��ʵ��ID�Ķ�Ӧ
struct _PlayerAction
{
	enTaskActionType nActionType;
	int				 nPlayerEntityID;
	unsigned short	 usTaskID;

	bool operator < ( const struct _PlayerAction& other )  const
	{
		if ( nPlayerEntityID == other.nPlayerEntityID )
			return usTaskID < other.usTaskID;
		return nPlayerEntityID < other.nPlayerEntityID;
	}
};

class CNpcState
{
public:
	int				nNpcEntityID;	// ��NPC��ʵ��ID

	// ��������
	CSearchArray<_PlayerAction, SERVER_CAP_PLAYER>	mActions[MAX_ACTION_TYPES];

	CNpcState()
	{
		if (CObj::msCreateMode)
		{
			nNpcEntityID = INVALID_OBJ_ID;
			memset( mActions, 0, sizeof(mActions));
		}
	}
};

typedef lk::hash_map< int, CNpcState, NPC_MONITOR_SIZE> NPC_MONITOR_TYPE;
class CTaskNpcMonitor
{
private:
	NPC_MONITOR_TYPE	m_NpcMap;	// NPCģ��ID��ʵ��IDӳ���ϵ ���second��0 ˵��δ������������

public:
	CTaskNpcMonitor()
	{
		if (CObj::msCreateMode)
		{
			m_NpcMap.initailize();
		}
	}

	int RegWatchNpc( int nNpcTempID );
	int OnNpcCreated( int nNpcTempID, unsigned int nNpcEntityID );
	int OnNpcDestroyed( int nNpcTempID );
	unsigned int GetNpcEntityID( int nNpcTempID );

	int OnNpcDied( int nNpcTempID );
	int RegGlobalTaskAction( int nTempID,enTaskActionType etype, CEntityPlayer* pPlayer, unsigned short vTaskID );
	int RemoveGlobalTaskAction(int nTempID, CEntityPlayer* pPlayer, unsigned short vTaskID);
};
