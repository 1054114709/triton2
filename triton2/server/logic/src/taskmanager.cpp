#include "stdafx.hpp"
#include "taskmanager.h"
#include "mapmodule.h"
#include "npcmodule.h"
#include "taskmodule.h"
#include "performance.h"

STORAGE_TASKS_CONTAINER  CStorageTaskManager::m_Storage;

CDir::CDir(const char* dirpath)
{
	bad = 0;
	if ((dir = opendir (dirpath)) == NULL) 
	{
		perror(strerror(errno));
		bad = errno;
	}
}

CDir::~CDir()
{
	if(dir) closedir(dir); dir = NULL;
}


const char* CDir::file()
{
	if (bad == 0)
	{
		while((dp = readdir (dir)) != NULL)
		{
			//struct stat buf; 
			//if (stat(dp->d_name, &buf) == 0 && S_ISREG(buf.st_mode)) return dp->d_name;
			if (dp->d_name[0] != '.') return dp->d_name;
		}
		if(dir) closedir(dir); dir = NULL;
	}

	return NULL;
}


//----------------------------------------------------------------------------------------------------

bool st_event::operator < ( const struct st_event& other )  const
{
	if ( nEventID < other.nEventID )
		return true;
	else if ( nEventID > other.nEventID )
		return false;
	else
		return nParam < other.nParam;
}

//----------------------------------------------------------------------------------------------------
CTask::CTask()
{
	if (CObj::msCreateMode)
	{
		mTaskID = 0;
		mTaskProgress = TASK_BEGIN;
		mTimerID = 0 ;
		mGameTimeLeft = -1;
		memset(mTaskData, 0, sizeof(mTaskData));
		mWatchEventN = 0;
		memset(mTalkedNpc, 0, sizeof(mTalkedNpc));
		mTalkedNum = 0;
		mExFlags = 0;
		mTaskBeginTime = time(0);
	}
}

void CTask::RegEventTick( unsigned int vEventID, unsigned int vParam, unsigned int vNum )
{
	if( vEventID == 0 ) 
	{
		LOG_ERROR("TASK", "reg event failed! vEventID=%d, vParam=%d taskid=%d", vEventID, vParam, mTaskID );
		return ;
	}

	// �����¼�
	if ( vParam == 0 && ( vEventID & EVENT_MASK_PARAM0 ) != EVENT_MASK_PARAM0 )
	{
		LOG_ERROR( "TASK", "event %x has no param! task ID=%d", vEventID , mTaskID );
		return ;
	}

	st_event key( vEventID, vParam );
	int	nRet = mEventData.insert(key);

	if( nRet == 0 )  // �ɹ�
	{
		// ��Ҫ���⴦����¼�
		if ( vEventID == EVENT_ITEMCHANGE ) // ��ͨ��Ʒ�����
		{
			CTplItem *tpItem = (CTplItem *)CDataStatic::SearchTpl( vParam );
			LK_ASSERT( tpItem, return);
			if ( IS_TASK_ITEM( tpItem ) )
			{
				LOG_DEBUG("TASK", "add mWatchEventN=%d task=%d", mWatchEventN, mTaskID );
				mWatchEventN += vNum;
			}
		}
		else if( vEventID == EVENT_OGREDIE)
		{
			LOG_DEBUG("TASK", "add mWatchEventN=%d task=%d", mWatchEventN, mTaskID );
			mWatchEventN += vNum;
		}
		else if ( vEventID == EVENT_KILLLEVELOGRE )
		{
			mExFlags |= EXFLAG_LEVELKILLOGRE;
			mWatchEventN += vNum;
		}
		else if ( vEventID == EVENT_COMPLETESTORAGETASK )
		{
			mExFlags |= EXFLAG_COMPLETE_STORAGE;
		}
		else if ( vEventID == EVENT_KILLFOREIGNER )
		{
			mExFlags |= EXFLAG_KILL_FOREIGNER;
		}
		else if ( vEventID == EVENT_COMPLETE_LOOP )
		{
			mExFlags |= EXFLAG_COMPLETE_LOOP;
		}
		else if ( vEventID == EVENT_PROTECT_FLAG )
		{
			mExFlags |= EXFLAG_PROTECT_FLAG_TASK;
		}
		else if ( vEventID == EVENT_COMPLETE_QUESTION )
		{
			mExFlags |= EXFLAG_COMPLETE_QUESTION;
		}

		// ȫ��Ψһ�¼�����¼��TaskList��
		if ( (vEventID&EVENT_MASK_GLOBAL) == EVENT_MASK_GLOBAL ) 
			CTaskLuaInterface::RegEventToPlayer( vEventID );

	}
	else if( nRet == -1 ) // �Ѵ��ڵ��¼� (ɱ�ֳ��� ��Ϊ�������������Ҫ�ֱ�ע��һ�� ��ֹ�����־)
	{
		if ( vEventID != EVENT_OGREDIE )
			LOG_ERROR("TASK", "reg event failed ! repeated vEventID=%x, vParam=%d  taskid=%d", vEventID, vParam, mTaskID );
		return ;
	}
	else if( nRet == -2 ) 
	{
		LOG_ERROR("TASK", "reg event failed ! events full! ID=%d", mTaskID );
		return ;
	}

}

// �Ƿ�����
bool CTask::IsEventTick ( unsigned int vEventID, unsigned int vParam )
{
	st_event key( vEventID, vParam );
	return mEventData.find(key) != NULL ; // ����
}


void CTask::GetTaskDataStruct(TaskStruct* pData)
{
	pData->set_taskid(mTaskID);
	pData->set_taskprogress(mTaskProgress);

	if ( (mExFlags&EXFLAG_LEVELKILLOGRE) == EXFLAG_LEVELKILLOGRE )  // ����ǵȼ�ɱ������ taskdata��һ��ֵ������ͻ��˷�-1 ��ֻ��2���� ��Ϊÿ������ֻ������1���ȼ�ɱ������ 
	{
		pData->add_taskdata(CONDITION_LEVELOGRE);
		pData->add_taskdata(mTaskData[1]);
	}
	// ���⣬����else if
	else if ( (mExFlags&EXFLAG_KILL_FOREIGNER) == EXFLAG_KILL_FOREIGNER ) 
	{
		pData->add_taskdata(CONDITION_KILL_FOREIGNER);
		pData->add_taskdata(mTaskData[1]);
	}
	else if ( (mExFlags&EXFLAG_COMPLETE_STORAGE) == EXFLAG_COMPLETE_STORAGE ) 
	{
		pData->add_taskdata(CONDITION_COMPLETE_STORAGE);
		pData->add_taskdata(mTaskData[1]);
	}
	else if ( (mExFlags&EXFLAG_COMPLETE_LOOP) == EXFLAG_COMPLETE_LOOP ) 
	{
		pData->add_taskdata(CONDITION_COMPLETE_LOOP);
		pData->add_taskdata(mTaskData[1]);
	}
	else if ( (mExFlags&EXFLAG_COMPLETE_QUESTION) == EXFLAG_COMPLETE_QUESTION ) 
	{
		pData->add_taskdata(CONDITION_COMPLETE_QUESTION);
		pData->add_taskdata(mTaskData[1]);
	}	
	else
	{
		for(int i = 0; i < TASK_DATA_SIZE; ++i)
		{
			pData->add_taskdata(mTaskData[i]);
		}
	}


	for(int i = 0; i < mTalkedNum; ++i)
	{
		pData->add_talkednpcs(mTalkedNpc[i]);
	}

	pData->set_timer( mGameTimeLeft );
}

// �Ƿ��ĳNPC�Թ���
bool CTask::IsTalkedWithNpc( int nNpcTempID )
{
	for(int i = 0; i < mTalkedNum; ++i)
	{
		if ( mTalkedNpc[i] == nNpcTempID )
			return true;
	}
	return false;
}

// ���Ӻ�NPC�ĶԻ�
bool CTask::AddTalkedWithNpc( int nNpcTempID )
{
	if ( mTalkedNum < MAX_NPC_TALK_NUM )
	{
		mTalkedNpc[mTalkedNum++] = nNpcTempID;
		return true;
	}
	return false;
}

// ���ٺ�NPC�ĶԻ�
bool CTask::RemoveTalkedWithNpc( int nNpcTempID )
{
	for (int i = 0; i < mTalkedNum; ++i)
	{
		if ( mTalkedNpc[i] == nNpcTempID )
		{
			for (int j = i; j < mTalkedNum-1; ++j)
			{
				mTalkedNpc[j] = mTalkedNpc[j+1];
			}
			mTalkedNpc[--mTalkedNum] = 0;
			return true;
		}
	}
	return false;
}

// �õ���һ��ĳ�¼���param
int CTask::GetFirstParamByEvent( int nEventID )
{
	for ( int i =0; i < mEventData.GetNum(); ++i ) // ������ARRCNT������ ȡָ��
	{
		st_event* tpEvent = mEventData.GetByIndex(i);
		if ( tpEvent == NULL )
			break;
		if ( tpEvent->nEventID == (unsigned int)nEventID )
			return tpEvent->nParam;
	}
	return 0;
}


//---------------------------------------------------------------------------------------------------

LoopTaskData::LoopTaskData()
{
	//#ifndef WIN32
	if (CObj::msCreateMode)
	{
		mTodayCompletedCircles =0 ;
		mLastCompletedTime    = 0 ;
		memset( mLoopTasks, 0, sizeof(mLoopTasks) );
		mCompletedTimes       = 0 ;		   
		mLastAbortTime		  = 0 ;		   
		mCurSubIndex		  = -1;
		mSubTasksNum		  = 0 ;
		mWeekLoops			  = 0 ;
	}
	//		else
	//		{
	//			;
	//		}
	//#endif
}

// ***********************************************************
//  Function:		GetRndTasks	
//  Description:	����һ��������ظ��Ļ��������� (���ƻ�ԭʼ���ݣ���)
//  Input:			��ѡ����ID���飬��ѡ������Ҫ�������
//  OutPut:			�������ָ��
//  Return:			NULL
//  Others:			Author: Liyan
//  Date:			2008.11.12
// **********************************************************
bool LoopTaskData::GetRndTasks( unsigned short arrSrc[], int nSrcNum, int nOutNum, unsigned short* pOut )
{
	if ( nOutNum > nSrcNum )
		return false;

	LK_ASSERT( arrSrc != NULL, return false );
	LK_ASSERT( pOut   != NULL, return false );

	for ( int i = 0 ; i < nOutNum; ++i )
	{
		int nRnd = rand() % nSrcNum;
		*(pOut++) = arrSrc[nRnd];
		arrSrc[nRnd] = arrSrc[--nSrcNum];
	}

	mSubTasksNum = nOutNum;
	return true;
}

void LoopTaskData::Clear()
{
	mTodayCompletedCircles =0 ;
	mLastCompletedTime    = 0 ;
	memset( mLoopTasks, 0, sizeof(mLoopTasks) );
	mCompletedTimes       = 0 ;		   
	mLastAbortTime		  = 0 ;		   
	mCurSubIndex		  = -1;
	mSubTasksNum		  = 0 ;
	mWeekLoops			  = 0 ;			
	mDayCompletedLoopFlag = 0 ;
}


// =====  Gets ==== //
int		LoopTaskData::GetCompletedTimes(/*unsigned short vLoopTaskID*/)
{
	return mCompletedTimes;
}

time_t	LoopTaskData::GetLastAbortTime(/*unsigned short vLoopTaskID*/)
{
	return mLastAbortTime;
}

short LoopTaskData::GetCurSubTaskIndex(/*unsigned short vLoopID*/)
{
	return mCurSubIndex;
}

unsigned short LoopTaskData::GetSubTaskIDbyIndex(short usIndex)
{
	if ( usIndex < 0 )
		return 0;

	if ( usIndex >= mSubTasksNum )
	{
		// LOG_ERROR( "TASK", "[%s:%d] task index %d out of range", __FUNCTION__, __LINE__, usIndex  );
		return 0;
	}
	return mLoopTasks[usIndex];
}

int LoopTaskData::GetLoopTaskNum()
{
	return mSubTasksNum;
}
// ��ʼ��������
bool LoopTaskData::PlayerGetLoopTask( unsigned short usArrSrc[], int n )
{
	//return GetRndTasks( usArrSrc, n, min( (unsigned int)n, CSceneCfgManager::GetSingletonPtr()->GetTask_cfg()->mLooptasksubnum ), mLoopTasks );
	mCurSubIndex =-1;
	mSubTasksNum = n;
	memset(mLoopTasks, 0, sizeof(mLoopTasks) );
	for ( int i=0; i < std::min( n, MAX_LOOP_SUB_TASKS ); ++i )
	{
		mLoopTasks[i] = usArrSrc[i];
	}
	return true;
}

int LoopTaskData::GetTodayCompletedTimes()
{
	return mTodayCompletedCircles;
}

unsigned short LoopTaskData::GetLastLoopTaskID()
{
	LK_ASSERT( mSubTasksNum > 0, return 0 );
	return mLoopTasks[mSubTasksNum-1];
}


// =====  Sets ==== //
bool  LoopTaskData::SetCurSubTaskID( unsigned short vSubTaskID )
{
	CheckInitTodayLoops();
	if ( GetSubTaskIDbyIndex( mCurSubIndex + 1 ) == vSubTaskID ) // ����һ����
	{
		++mCurSubIndex;
		return true;
	}
	else
	{
		return false;
	}
}

void  LoopTaskData::SetAbortData( )
{
	memset( mLoopTasks, 0, sizeof(mLoopTasks) );
	mCurSubIndex		  = -1;
	mSubTasksNum		  = 0 ;
	mLastAbortTime		  = time(0);
}

// ��������һ�ֵ�ʱ����� 
int  LoopTaskData::SetEndLoopData( )
{
	mCompletedTimes++;
	mCurSubIndex = -1;
	memset( mLoopTasks, 0, sizeof(mLoopTasks) );
	mSubTasksNum	= 0 ;

	return 0;
}

// ��һ��Ĵ���
void   LoopTaskData::OnNewDay()
{
	mDayCompletedLoopFlag = 0;
}
// ��һ�ܵĴ���
void   LoopTaskData::OnNewWeek()
{
	mWeekLoops = 0;
}

void LoopTaskData::GetTlvBuffer2(PBLoopTaskData*& pBuffer)
{
	pBuffer->set_todaycompletedcircles(mTodayCompletedCircles);
	pBuffer->set_lastcompletedtime(mLastCompletedTime);

	for( int i = 0 ; i < mSubTasksNum; ++i )
	{
		pBuffer->add_looptasks( mLoopTasks[i] );
	}

	pBuffer->set_completedtimes( mCompletedTimes );
	pBuffer->set_lastaborttime( mLastAbortTime );
	pBuffer->set_cursubindex( mCurSubIndex );
	pBuffer->set_weekloops( mWeekLoops );
	pBuffer->set_daycompletedloopflag( mDayCompletedLoopFlag );
}

// ����ǲ���ÿ��ĵ�һ��
void LoopTaskData::CheckInitTodayLoops()
{
	time_t t = time( 0 );
	tm tmp,tmp2;
	localtime_r( &t, &tmp ); 
	localtime_r( &mLastCompletedTime, &tmp2 ); 

	if ( tmp.tm_yday != tmp2.tm_yday || tmp.tm_year != tmp2.tm_year ) 
	{
		mTodayCompletedCircles = 0;
	}
}

void LoopTaskData::CreateFromTlv2(PBLoopTaskData*& pBuffer)
{
	mTodayCompletedCircles = pBuffer->todaycompletedcircles();
	mLastCompletedTime     = pBuffer->lastcompletedtime();

	CheckInitTodayLoops();
	
	mSubTasksNum           = pBuffer->looptasks_size();

	for( int i = 0 ; i < pBuffer->looptasks_size(); ++i )
	{
		mLoopTasks[i] = pBuffer->looptasks( i );
	}

	mCompletedTimes		   = pBuffer->completedtimes( );
	mLastAbortTime		   = pBuffer->lastaborttime( );
	mCurSubIndex		   = pBuffer->cursubindex( );
	mWeekLoops			   = pBuffer->weekloops();			
	mDayCompletedLoopFlag  = pBuffer->daycompletedloopflag();
}


// ÿ���һ�����������Ӧ
int  LoopTaskData::OnCompletedTask( unsigned short vTaskID )
{
	CheckInitTodayLoops();
	++mTodayCompletedCircles;
	mLastCompletedTime = time(0);
	if ( mTodayCompletedCircles >= LOOP_SUB_NUM )
	{
		if ( mDayCompletedLoopFlag == 0 )
		{
			mDayCompletedLoopFlag = 1; 
			++ mWeekLoops;
			return mWeekLoops;
		}
	}
	return 0;
}

// �õ��ڼ���(��1��ʼ���Ҳ����򷵻�0)
int LoopTaskData::GetLoopByTaskID( unsigned short usTaskID )
{
	if ( usTaskID == 0 )
		return 0;

	for ( int i = 0; i < mSubTasksNum; ++i )
	{
		if ( mLoopTasks[i] == usTaskID )
			return i+1;
	}
	return 0;
}


//---------------------------------------------------------------------------------------------------------

st_event_single::st_event_single( int vEventID, int vParam )
{
	stevent = st_event( vEventID , vParam );
}

bool st_event_single::operator < ( const struct st_event_single& other )  const
{
	return stevent < other.stevent;
}

//-------------------------------------------------------------------------------------------------------

CTaskList::CTaskList( ) 
{
	if ( CObj::msCreateMode)
	{
		Initialize();
	}
	else
	{
		Resume();
	}
}

CTaskList::~CTaskList( ) 
{

}

// ��ʼ��
int CTaskList::Initialize()
{
	mTaskNumber = 0;
	//::memset(mCompleteTasks, 0, sizeof(mCompleteTasks));
	mCompleteTasks.initailize();
	mRepeatTasks.initailize();
	mCorpsPublishTask.initailize();		//  ���ŷ���
	//::memset(mFailedTasks, 0, sizeof(mFailedTasks));
	mFailedTasks.initailize();
	::memset(mTaskList, 0, sizeof(mTaskList));
	mTickEvents = 0;

	mLoopTaskData = LoopTaskData();
	mEventMgr     = CTaskEventManager();
	mStorageTaskMgr= CStorageTaskManager();
	mTragedyTaskMgr=CTragedyTaskMgr();
	mBossNpcEntityID = 0;
	mPlayerCurTalkNpcID = 0;
	mPlayerCurSendNpcID = 0;
	mInvitingPlayerID = -1;
	_IDmap.initailize();
	mRedirectFailTask = 0;
	mOwnerEntityID=0;
	mTodayTeamLoopNum=0;

	return 0;
}

// �ָ�
int CTaskList::Resume()
{
	return 0;
}


void CTaskList::Clear( )
{
	mTaskNumber = 0;
	//::memset( mCompleteTasks, 0, sizeof(mCompleteTasks));
	mCompleteTasks.clear();
	//::memset( mFailedTasks, 0, sizeof(mFailedTasks));
	mFailedTasks.clear();
	mRepeatTasks.clear();
	::memset( mTaskList, 0, sizeof( mTaskList ) );
}


void CTaskList::SetEnd(unsigned short vTaskID)
{
	mCompleteTasks.insert( std::make_pair( vTaskID, vTaskID ) );
}

void CTaskList::SetEndTime(unsigned short vTaskID, int vEndTime)
{	
	lk::hash_map<unsigned short, int, COMPLETE_TASK_NUM>::iterator it = mRepeatTasks.find(vTaskID);
	if ( it == mRepeatTasks.end())
	{
		mRepeatTasks.insert( std::make_pair( vTaskID, vEndTime ) );
	}
	else
	{
		it->second = vEndTime;
	}
}

int CTaskList::GetEndTime(unsigned short vTaskID)
{
	if (mRepeatTasks.find(vTaskID) == mRepeatTasks.end())
	{
		return 0;
	}
	return mRepeatTasks.find(vTaskID)->second;
}

bool CTaskList::GetEnd(unsigned short vTaskID)
{
	return mCompleteTasks.find(vTaskID) != mCompleteTasks.end(); 
}

void CTaskList::SetFailed(unsigned short vTaskID)
{
	mFailedTasks.insert( std::make_pair( vTaskID, vTaskID ) );
}

bool CTaskList::GetFailed(unsigned short vTaskID)
{
	return mFailedTasks.find(vTaskID) != mFailedTasks.end(); 
}

int CTaskList::InsertRefreshedTask(unsigned short vTaskID , int taskColor )
{
	int num = 0;
	for (int i = 0; i < TASK_LIST_SIZE; ++ i)
	{
		if (mRememberRefreshNum[i].rTaskID == vTaskID)
		{
			mRememberRefreshNum[i].rTaskColor = taskColor;
			if (mRememberRefreshNum[i].bflag == true)
			{
				num = i;
				break;
			}
			else
			{
				mRememberRefreshNum[i].bflag = true;

				if (i == TASK_LIST_SIZE - 1)
				{
					mRememberRefreshNum[0].bflag = false;
				}
				else
				{
					mRememberRefreshNum[i+1].bflag = false;
				}
				num = i;
				break;
			}
		} 
		else if (mRememberRefreshNum[i].bflag == false)
		{
			mRememberRefreshNum[i].rTaskID = vTaskID;
			mRememberRefreshNum[i].rTaskColor = taskColor;
			mRememberRefreshNum[i].bflag = true;

			if (i == TASK_LIST_SIZE - 1)
			{
				mRememberRefreshNum[0].bflag = false;
			}
			else
			{
				mRememberRefreshNum[i+1].bflag = false;
			}
			num = i;
			break;
		}
	}
	return num;
}

void CTaskList::GetTlvBuffer2( PBTaskList* pBuffer )
{
	pBuffer->set_tasknumber(mTaskNumber);

	for (int i = 0 ; i < mTaskNumber && i < (int)ARRAY_CNT( mTaskList ); ++i)
	{
		PBTask* tpPBTask = pBuffer->add_tasklist();

		tpPBTask->set_taskid(mTaskList[i].mTaskID);
		tpPBTask->set_taskprogress(mTaskList[i].mTaskProgress);
		tpPBTask->set_gametimeleft( mTaskList[i].mGameTimeLeft );
		tpPBTask->set_exflags( mTaskList[i].mExFlags );
		tpPBTask->set_begintime(mTaskList[i].mTaskBeginTime);

		for ( int j = 0 ; j < TASK_DATA_SIZE && j < (int)ARRAY_CNT( mTaskList ); ++j )
		{
			// ��Ϊtaskdata����pair��ʽʹ�õ� ����ֻҪ����2��0 �����break
			if ( j < TASK_DATA_SIZE-1 && mTaskList[i].mTaskData[j] == 0 && mTaskList[i].mTaskData[j+1] == 0 )
				break;
			tpPBTask->add_taskdata(mTaskList[i].mTaskData[j]);
		}

		for ( int j = 0 ; j < mTaskList[i].mTalkedNum; ++j )
		{
			tpPBTask->add_talkednpcs(mTaskList[i].mTalkedNpc[j]);
		}
	}

	//pBuffer->set_completedtasks(mCompleteTasks, COMPLETE_TASK_BIT_SIZE);
	for ( lk::hash_map<unsigned short, unsigned short, COMPLETE_TASK_NUM>::iterator it = mCompleteTasks.begin(); it != mCompleteTasks.end(); ++it )
	{
		pBuffer->add_completedtask( it->first );
	}
	//pBuffer->set_failedtasks(mFailedTasks, COMPLETE_TASK_BIT_SIZE);
	for ( lk::hash_map<unsigned short, unsigned short, FAILED_TASK_NUM>::iterator it = mFailedTasks.begin(); it != mFailedTasks.end(); ++it )
	{
		pBuffer->add_failedtask( it->first );
	}

	for ( lk::hash_map<unsigned short, int, COMPLETE_TASK_NUM>::iterator it = mRepeatTasks.begin(); it != mRepeatTasks.end(); ++it )
	{
		pBuffer->add_repeatetask( it->first );
		pBuffer->add_endtime( it->second );
	}
	for ( PUBLISHTASK::iterator it = mCorpsPublishTask.begin(); it != mCorpsPublishTask.end(); ++it )
	{
		GroupPublishData *pCorpsTask = pBuffer->add_corpspublish();
		LK_ASSERT(pCorpsTask, return;)
		pCorpsTask->set_taskid(it->first);
		pCorpsTask->set_taskstate(it->second);
	}
	for (int i = 0; i < TASK_LIST_SIZE; ++i)
	{
		PBRefreshTaskData *pRefresh = pBuffer->add_refreshdata();
		LK_ASSERT(pRefresh, return;)
		pRefresh->set_taskid(mRememberRefreshNum[i].rTaskID);
		pRefresh->set_taskcolor(mRememberRefreshNum[i].rTaskColor);
		pRefresh->set_resultflag(mRememberRefreshNum[i].bflag);	
	}

	PBLoopTaskData* tpLoopTaskData = pBuffer->mutable_looptaskdata();
	mLoopTaskData.GetTlvBuffer2( tpLoopTaskData );

	PBStorageTaskData* tpStorageTaskData = pBuffer->mutable_storagetaskdata();
	mStorageTaskMgr.GetTlvBuffer2( tpStorageTaskData );

	for( int i = 0 ; i < mEventMgr.mEvents.GetNum(); ++i )
	{
		st_event_single* pEvent = mEventMgr.mEvents.GetByIndex(i);
		if (pEvent)
		{
			pBuffer->add_eventid( pEvent->stevent.nEventID );
			pBuffer->add_eventparam( pEvent->stevent.nParam );
			pBuffer->add_eventtick( pEvent->nTicked );
		}
	}

	// ׼��������������
	mTragedyTaskMgr.GetTlvBuffer2(pBuffer);

	mTaskGroupMgr.GetPBBuffer( pBuffer );
	pBuffer->set_completedtragedy( mTragedyTaskMgr.GetCompleted() );
	pBuffer->set_redirectfailtask( mRedirectFailTask );
	PBChairManTaskData* tpChairMan = pBuffer->mutable_chairmantask();
	mChairManTaskMgr.GetTlvBuffer2(tpChairMan);
	pBuffer->set_todayteamloopnum(mTodayTeamLoopNum);
}


void CTaskList::CreateFromTlv2( PBTaskList* pBuffer )
{
	//LOG_DEBUG("TASK", "create: %s", pBuffer->DebugString().c_str() );

	if ( pBuffer == NULL )
	{
		LOG_DEBUG( "TASK", "[ %s : %d ] pBuff is NULL", __LK_FILE__, __LINE__ ); 
	}

	mTaskNumber = pBuffer->tasknumber();

	for (int i = 0 ; i < mTaskNumber && i < (int)ARRAY_CNT( mTaskList )&& i < pBuffer->tasklist_size(); ++i)
	{
		PBTask tpPBTask = pBuffer->tasklist(i);

		mTaskList[i].mTaskID = tpPBTask.taskid();
		mTaskList[i].mTaskProgress = tpPBTask.taskprogress();
		mTaskList[i].mGameTimeLeft = tpPBTask.gametimeleft();
		mTaskList[i].mExFlags = tpPBTask.exflags();
		mTaskList[i].mTaskBeginTime = tpPBTask.begintime();
		_IDmap.insert( std::make_pair( mTaskList[i].mTaskID, i ) );

		for ( int j = 0 ; j < tpPBTask.taskdata_size() && j < (int)ARRAY_CNT( mTaskList ); ++j )
		{
			mTaskList[i].mTaskData[j] = tpPBTask.taskdata(j);
		}

		mTaskList[i].mTalkedNum = tpPBTask.talkednpcs_size();
		for ( int j = 0 ; j < tpPBTask.talkednpcs_size(); ++j )
		{
			mTaskList[i].mTalkedNpc[j] = tpPBTask.talkednpcs(j);
		}
	}

	//if ( pBuffer->has_completedtasks() )
	//	memcpy(mCompleteTasks, pBuffer->mutable_completedtasks()->c_str(), COMPLETE_TASK_BIT_SIZE );
	//else
	//	memset( mCompleteTasks, 0, sizeof( mCompleteTasks ) );

	for ( int i = 0; i < pBuffer->completedtask_size(); ++i )
	{
		mCompleteTasks.insert( std::make_pair( (unsigned short)pBuffer->completedtask(i), (unsigned short)pBuffer->completedtask(i) ) );
	}

	for ( int i = 0; i < pBuffer->repeatetask_size(); ++i )
	{
		mRepeatTasks.insert( std::make_pair( (unsigned short)pBuffer->repeatetask(i), (int)pBuffer->endtime(i) ) );
	}
	//if ( pBuffer->has_failedtasks() )
	//	memcpy(mFailedTasks, pBuffer->mutable_failedtasks()->c_str(), COMPLETE_TASK_BIT_SIZE );
	//else
	//	memset( mFailedTasks, 0, sizeof( mFailedTasks ) );

	for ( int i = 0; i < pBuffer->failedtask_size(); ++i )
	{
		mFailedTasks.insert( std::make_pair( (unsigned short)pBuffer->failedtask(i), (unsigned short)pBuffer->failedtask(i) ) );
	}

	PBLoopTaskData* tpLoopTaskData = pBuffer->mutable_looptaskdata();
	mLoopTaskData.CreateFromTlv2( tpLoopTaskData );

	if ( pBuffer->has_storagetaskdata() )
	{
		PBStorageTaskData* tpData = pBuffer->mutable_storagetaskdata();
		mStorageTaskMgr.CreateFromTlv2( tpData );
	}
	
	for( int i = 0 ; i < pBuffer->eventid_size(); ++i )
	{
		st_event_single item;
		item.stevent = st_event( pBuffer->eventid(i), pBuffer->eventparam(i) );
		item.nTicked = pBuffer->eventtick(i);
		mEventMgr.mEvents.insert(item);
	}
	
	for(int i = 0; i < pBuffer->refreshdata_size(); ++i)
	{
		PBRefreshTaskData pRefresh = pBuffer->refreshdata(i);
		mRememberRefreshNum[i].rTaskID = pRefresh.taskid();
		mRememberRefreshNum[i].rTaskColor = pRefresh.taskcolor();
		mRememberRefreshNum[i].bflag = pRefresh.resultflag();	
	}

	for(int i = 0; i < pBuffer->corpspublish_size(); ++i)
	{
		GroupPublishData pCorpsTask = pBuffer->corpspublish(i);
		mCorpsPublishTask.insert( std::pair<unsigned short, unsigned short>(pCorpsTask.taskid(), pCorpsTask.taskstate()) );
	}
	mTragedyTaskMgr.CreateFromTlv2(pBuffer);
	mTaskGroupMgr.CreateFromPB( pBuffer );
	mTragedyTaskMgr.SetCompleted( pBuffer->completedtragedy() );
	mLastLogOffTime = pBuffer->lastlogoff();
	mRedirectFailTask = pBuffer->redirectfailtask();

	PBChairManTaskData* tpChairMan = pBuffer->mutable_chairmantask();
	mChairManTaskMgr.CreateFromTlv2(tpChairMan);
	mTodayTeamLoopNum = pBuffer->todayteamloopnum();
}

// �ؽ�����������remove��ʱ�����
void CTaskList::RebuildIndex()
{
	_IDmap.clear();
	for ( int i = 0 ; i < mTaskNumber; ++i )
	{
		_IDmap.insert(std::make_pair(mTaskList[i].mTaskID, i));
	}
}

void CTaskList::TaskReset( )
{
	mTaskNumber = 0;
	//::memset(mCompleteTasks, 0, sizeof(mCompleteTasks));
	mCompleteTasks.clear();
	//::memset(mFailedTasks, 0, sizeof(mFailedTasks));
	mFailedTasks.clear();
	::memset( mTaskList, 0, sizeof( mTaskList ) );
}

void CTaskList::RemoveTask( int vTaskID )
{
	int nIndex = GetTaskIndex( vTaskID );
	LK_ASSERT( nIndex >= 0 && nIndex < mTaskNumber, return );
	std::copy( &mTaskList[nIndex] +1, mTaskList + mTaskNumber, &mTaskList[nIndex] );
	-- mTaskNumber;
	if ( mRedirectFailTask == vTaskID )
		mRedirectFailTask = 0;
	RebuildIndex();
}

CTask* CTaskList::GetTask( unsigned short vTaskID )
{
	int nIndex = GetTaskIndex( vTaskID );
	// LK_ASSERT( nIndex >= 0 && nIndex < mTaskNumber, return NULL );
	if ( nIndex >= 0 && nIndex < mTaskNumber )
		return &mTaskList[nIndex];
	return NULL;
}

int CTaskList::InsertTask( const CTask& rTask )
{
	// ������������, �����ڽ��ܸ�����
	if (GetEnd(rTask.mTaskID)) return ERROR_TASK_HASDONE;

	// ��������б�����, �����ڽ��ܸ�����
	if ( mTaskNumber >= TASK_LIST_SIZE )
		return ERROR_TASK_OUTOFSPACE;

	int nIndex = GetTaskIndex( rTask.mTaskID );
	if( nIndex >= 0 && nIndex < mTaskNumber )
		return ERROR_TASK_HASACCEPT;

	if( mTaskNumber < sizeof( mTaskList ) / sizeof( mTaskList[ 0 ] ) )
	{
		mTaskList[ mTaskNumber ] = rTask;
		_IDmap.insert(std::make_pair(rTask.mTaskID, mTaskNumber));
		++mTaskNumber;
	}
	return ERROR_TASK_SUCCESS;
}


bool CTaskList::IsTaskComplete( unsigned short vTaskID )
{
	int nIndex = GetTaskIndex( vTaskID );
	LK_ASSERT( nIndex >= 0 && nIndex < mTaskNumber, return false );

	return mTaskList[ nIndex ].mTaskProgress == TASK_COMPLETE ;
}

bool CTaskList::IsTaskProgress( unsigned short vTaskID )
{
	int nIndex = GetTaskIndex( vTaskID );
	return ( nIndex >= 0 && nIndex < mTaskNumber );
}

int CTaskList::GetTaskState( unsigned short vTaskID )
{
	if ( IsTaskEnd( vTaskID ) == true )
		return TASK_END;

	if ( IsTaskFailed( vTaskID ) == true )
		return TASK_FAILED;

	int nIndex = GetTaskIndex( vTaskID );
	if( nIndex >= 0 && nIndex < mTaskNumber )
		return mTaskList[ nIndex ].mTaskProgress;
	return -1;
}
int CTaskList::SetTaskState( unsigned short vTaskID, int State )
{
	int nIndex = GetTaskIndex( vTaskID );
	if( nIndex >= 0 && nIndex < mTaskNumber )
	{
		 mTaskList[ nIndex ].mTaskProgress = State;
		 return 0;
	}

	return -1;
}

int CTaskList::GetTaskColor(unsigned short vTaskID)
{
	for (int i = 0; i < TASK_LIST_SIZE; ++i)
	{
		if (mRememberRefreshNum[i].rTaskID == vTaskID)
		{
			return mRememberRefreshNum[i].rTaskColor;
			break;
		}
	}
	return 1;
}

void CTaskList::RemoveTaskColor(unsigned short vTaskID)
{
	for (int i = 0; i < TASK_LIST_SIZE; ++i)
	{
		if (vTaskID == mRememberRefreshNum[i].rTaskID)
		{
			mRememberRefreshNum[i].Inintialize();
			break;
		}
	}
}

void CTaskList::OnNewdayCome()
{
	// �����鴦��
	mTaskGroupMgr.OnNewdayCome();

	// ���ÿ����ɵĿ�����
	mStorageTaskMgr.ZeroTodayCompleted();

	// ÿ����ջ�����
	mLoopTaskData.OnNewDay();

	// ���ÿ���RMBˢ���������
	mStorageTaskMgr.ZeroTodayRMBTimes();

	// ��վ��ŷ�����Ϣ
	mCorpsPublishTask.initailize();

}

void CTaskList::OnNewWeekCome()
{
	mLoopTaskData.OnNewWeek();
	mTaskGroupMgr.OnNewWeekCome();
}



// ***********************************************************
//  Function:		GetStorgeTaskList	
//  Description:	����ҵ���ʰ�NPC��ʱ��ȡ�ʰ������б�
//  Input:			GG��ʽ���б�ָ�룬 ������ID
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2009.3.2
// **********************************************************
void CTaskList::GetStorgeTaskList( NpcTaskList* pList, unsigned short usTaskID )
{
	if ( usTaskID <= 100 || usTaskID > 200 || pList == NULL )
	{
		LOG_ERROR( "TASK", "[%s:%d] taskid %d worng or list null ", __FUNCTION__, __LINE__, usTaskID );
		return;
	}

	// ��������ϴ��Ǹ��б��ˣ�ǿ��ˢ��
	if ( usTaskID != mStorageTaskMgr.m_usCurID )
	{
		mStorageTaskMgr.m_usCurID = usTaskID;
		RefreshTasks( REFRESH_DAY );
	}
	else // �ж�����
	{
		time_t t = time( 0 );
		tm tmp, tmp2;
		localtime_r( &t, &tmp );
		localtime_r( &mStorageTaskMgr.m_nLastClickNpc, &tmp2 );

		if ( tmp.tm_mday != tmp2.tm_mday ) // �µ�һ�죬�����״ε�� ����ˢ��ʧ����
		{
			RefreshTasks( REFRESH_DAY );
		}
	}


	//  ���List
	pList->set_extendnumber( mStorageTaskMgr.m_Tasks.GetNum());
	for ( int i = 0 ; i < mStorageTaskMgr.m_Tasks.GetNum(); ++i )
	{
		unsigned short* tpTaskID = mStorageTaskMgr.m_Tasks.GetByIndex(i);
		LK_ASSERT(tpTaskID, continue);
		pList->add_extendtaskid(*tpTaskID) ;
	}

	if ( mStorageTaskMgr.m_Tasks.GetNum() > 0 ) // ˢ�³ɹ�
		mStorageTaskMgr.m_nLastClickNpc = time(0);
}


//  *************************************************
//   insert publish task   


void CTaskList::InsertPublishTask(unsigned short vTaskID, unsigned int vTaskType, unsigned int vTaskState)
{
	PUBLISHTASK::iterator it;
	switch(vTaskType)
	{
	case CORPS_PUBLISH_TASK:
			it = mCorpsPublishTask.find(vTaskID);
			if (it == mCorpsPublishTask.end())
			{
				mCorpsPublishTask.insert( std::make_pair( vTaskID, vTaskState ) );
			}
			else
			{
				it->second = vTaskState;
			}

			break;
	default:
		{
			break;
		}
	}
}


unsigned short CTaskList::GetPublishStateByType(unsigned short vTaskID, unsigned int vTaskType)
{

	PUBLISHTASK::iterator it;
	switch(vTaskType)
	{
	case CORPS_PUBLISH_TASK:
		it = mCorpsPublishTask.find(vTaskID);
		if (it == mCorpsPublishTask.end())
		{
			return UNEXIST_TASK;
		}
		else
		{
			return it->second;
		}

		break;
	default:
		{
			return UNEXIST_TASK;
			break;
		}
	}
}


void CTaskList::SetPublishTaskState(unsigned short vTaskID, unsigned short vTaskState, unsigned int vTaskType)
{

	PUBLISHTASK::iterator it;
	switch(vTaskType)
	{
	case CORPS_PUBLISH_TASK:
		{
			it = mCorpsPublishTask.find(vTaskID);
			if (it == mCorpsPublishTask.end())
			{
				mCorpsPublishTask.insert(std::pair<unsigned short, unsigned short>(vTaskID, vTaskState));
			}
			else
			{
				it->second = vTaskState;
			}

			break;
		}
	default:
		{
			break;
		}
	}
}
// ***********************************************************
//  Function:		RefreshTasks	
//  Description:	ˢ��������ϵĻʰ������б�(�ⲿ�����������б�)
//  Input:			����
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2009.3.2
// **********************************************************
void CTaskList::RefreshTasks( ETaskRefreshType etype )
{
	mStorageTaskMgr.m_Tasks.Clear();

	if (etype == REFRESH_DAY || etype == REFRESH_RMB)
	{
		unsigned short tmptasks[MAX_STORAGETASK_LIST_NUM] = {0};
		int n = CTaskModule::GetSingleton().RefreshStorageTask( mStorageTaskMgr.m_usCurID, etype, (unsigned short*)tmptasks ) ;	
		n = std::min(n, MAX_STORAGETASK_LIST_NUM);
		for ( int i = 0; i < n; ++i)
		{
			if (GetTask(tmptasks[i]) == NULL)
				mStorageTaskMgr.m_Tasks.insert(tmptasks[i]);
		}
	}
	else if (etype == REFRESH_BACK) // ÿ�ν�����ˢ
	{
		STORAGE_TASKS_CONTAINER::iterator it = CStorageTaskManager::m_Storage.find( mStorageTaskMgr.m_usCurID);
		if (it != CStorageTaskManager::m_Storage.end())
		{
			int tStartIndex = 0;
			if ( it->second.m_nRefreshNum > MAX_STORAGETASK_LIST_NUM )
				tStartIndex = rand() % (it->second.m_nRefreshNum - MAX_STORAGETASK_LIST_NUM);

			LOG_DEBUG("TASK", "it->second.m_nRefreshNum=%d", it->second.m_nRefreshNum );
			int tOutNum = std::min( MAX_STORAGETASK_LIST_NUM, (int)it->second.m_nRefreshNum );
			LOG_DEBUG("TASK", "tOutNum=%d", tOutNum );
			LOG_DEBUG("TASK", "tStartIndex=%d", tStartIndex );

			LK_ASSERT (tStartIndex < STORAGE_SIZE, return);
			LK_ASSERT (tStartIndex+tOutNum-1 < STORAGE_SIZE, return);

			for ( int i = 0; i < tOutNum; ++i)
			{
				if (GetTask(it->second.m_usBackRefreshTasks[tStartIndex+i]) == NULL)
					mStorageTaskMgr.m_Tasks.insert(it->second.m_usBackRefreshTasks[tStartIndex+i]);
			}		
		}
		else
		{
			LOG_ERROR( "TASK", "no storage task id=%d", mStorageTaskMgr.m_usCurID );
		}
	}

	// ����ѽ�����ˢ�º�ķ�����Ч��
	mStorageTaskMgr.m_GotTasks.Clear();

	if ( mStorageTaskMgr.m_Tasks.GetNum() == 0)
	{
		LOG_ERROR("TASK", "refreshed %d got 0 task! style=%d", mStorageTaskMgr.m_usCurID, (int)etype ) ;
	}
}


// ***********************************************************
//  Function:		RegEvent	
//  Description:	��������¼�¼�
//  Input:			����ID���¼�ID
//  OutPut:			NULL
//  Return:			�Ƿ�ɹ�
//  Others:
//  Date:			2008.11.24
// **********************************************************
bool CTaskEventManager::RegEvent( unsigned int nEventID, unsigned int nParam )
{
	st_event_single key( nEventID, nParam );
	st_event_single* pEvent = mEvents.find( key );

	if( pEvent ) // �Ѵ��ڵ��¼�
	{
		pEvent->nTicked++;
		return true;
	}
	else
	{
		st_event_single event;
		event.stevent.nEventID  = nEventID;
		event.stevent.nParam    = nParam;
		event.nTicked			= 1;

		if ( mEvents.insert(event) == 0 )
			return true;
	}
	return false;
}


// ***********************************************************
//  Function:		GetTickNum	
//  Description:	�õ���������
//  Input:			����ID���¼�ID
//  OutPut:			NULL
//  Return:			�Ƿ�ɹ�
//  Others:
//  Date:			2008.11.24
// **********************************************************
int  CTaskEventManager::GetTickNum( unsigned int nEventID, unsigned int nParam  )
{
	st_event_single key( nEventID, nParam );
	st_event_single* pEvent = mEvents.find( key );

	if( pEvent ) 
	{
		return pEvent->nTicked;
	}

	return 0;
}


// ***********************************************************
//  Function:		RemoveTick	
//  Description:	����¼���¼ ���С�ڵ���0���Ͱ����иɵ�
//  Input:			����ID���¼�ID
//  OutPut:			NULL
//  Return:			�Ƿ�ɹ�
//  Others:
//  Date:			2008.11.24
// **********************************************************
bool CTaskEventManager::RemoveTick( unsigned int nEventID, unsigned int nParam, int n )
{
	// ֻ�м�¼�¼�������� 
	if ( (nEventID&EVENT_MASK_RECORD) != EVENT_MASK_RECORD )
	{
		LOG_ERROR("TASK","event %x is not a reg event", nEventID );
		return false;
	}

	// ȫ���¼� �������Ƴ�
	if ( (nEventID&EVENT_MASK_GLOBAL) == EVENT_MASK_GLOBAL && n == _MAX_INT )
	{
		CTaskLuaInterface::ClearEventFromPlayer(nEventID);
	}

	st_event_single key( nEventID, nParam );
	st_event_single* pEvent = mEvents.find( key );

	if( pEvent ) 
	{
		 pEvent->nTicked -= n ;
		 if ( pEvent->nTicked <= 0 ) // �ɵ�
		 {
			 mEvents.remove(key);
		 }
		 return true;
	}
	return false;
}

//-------------------------------------�����ķָ���---------------------------------------------------------------
// ***********************************************************
//  Function:		StartNewSession	
//  Description:	��ʼ��һ������ʵ��
//  Input:			��ң�NPCģ��ID��·�㣬·����������ID
//  OutPut:			NULL
//  Return:			0���ɹ�  -1������
//  Others:
//  Date:			2008.12.2
// **********************************************************
int CSendNpcManager::StartNewSession( CEntityPlayer* pPlayer, int vNpcTempID, int* vX, int* vY, int* vMapID, int vTotal, unsigned short vTaskID, int vGird, int nNpcEntityID, int vLeaveTime, int nBuffTime, int nBuffID, int nWaitTimer )
{
	LK_ASSERT(pPlayer!=NULL, return -1);
	LK_ASSERT(vX != NULL, return -1);
	LK_ASSERT(vY != NULL, return -1);
	LK_ASSERT(vMapID != NULL, return -1);
	LK_ASSERT(vTotal > 0, return -1);

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return -1);

	unsigned int tEntityID = nNpcEntityID;
	if (pList->GetInvitingPlayerID() == -1) // ���Ǳ������ �ſ���������ĳ�ʼ��
	{
		if ( tEntityID == 0 ) // �»���  �򴴽�����NPC
		{
			CNpcCreator tCreator;
			tCreator.mNpcID = vNpcTempID;
			tCreator.mPosition = CWTPoint( vX[0], vY[0] );
			tCreator.mOwnerCharID = pPlayer->GetCharID();
			tCreator.mIsSendNpc = 1;
			tCreator.mIsShowOwner = 1;
			tCreator.SetIndex( pPlayer->GetMapIndex() );
			tCreator.set_id(0); // �������������� creater��obj��id����Ϊ��npc setup��ʱ�������ֵ��ֵ��entity���createrid����˾Ϳ��Ը������ֵ���ж����NPC�Ƿ�̬ˢ������
			if (!CMapModule::GetSingleton().CreateNpc( pPlayer->GetLineID(),
				pPlayer->GetMapID(),
				pPlayer->GetMapIndex(),
				&tCreator,
				tEntityID ) )
			{
				LOG_ERROR( "TASK", "[%s:%d] create npc failed, map %d, index %d", __FUNCTION__, __LINE__, pPlayer->GetMapID(), pPlayer->GetMapIndex() );
				return -1;
			}
		}

		CEntityNpc* pEntityNpc = (CEntityNpc*)CSceneLogic::GetSingleton().GetEntity( tEntityID );
		LK_ASSERT( pEntityNpc != NULL, return -1 );
		pEntityNpc->SetOwnerCharID( pPlayer->GetCharID() );
		pEntityNpc->SetSendNpcState(1);

		pEntityNpc->SetPKType( ENEMY_TO_OGRE | ENEMY_WITH_OGRE | NEUTRAL_WITH_SC | NEUTRAL_TO_SC | NEUTRAL_WITH_FC | NEUTRAL_TO_FC );

		CPropertyModule::GetSingleton().NotifyClientNpcPKTypeChanged( pEntityNpc );
		CSingleSendNpc _sendnpc_data( vX, vY, vMapID, vTotal, tEntityID, pPlayer->GetEntityID(), vTaskID, vGird, vLeaveTime, nBuffTime, nBuffID, nWaitTimer );
		_sendnpc_data.Start();
		// ����NPC�Ĳ��뻤�͵��˵��б�
		_sendnpc_data.AddSendingList( pPlayer->GetEntityID() );
		mSessions.insert( std::make_pair( tEntityID, _sendnpc_data ) );
	}
	else if (pList->GetInvitingPlayerID() == 0) // ������ ���Ǻ������߲���ͬһ������
	{
		return -1;
	}
	else
	{
		CEntityPlayer* tpSrcPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(pList->GetInvitingPlayerID());
		if ( tpSrcPlayer == NULL )
			return -1;

		CTaskList* pSrcList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(tpSrcPlayer->GetTaskToken( ));
		LK_ASSERT( pSrcList,  return -1);
		tEntityID = pSrcList->GetSendNpcEntityID(); // �õ������ҵ����ڻ��͵�npc ��Ҫ�����������
		SendNpcType::iterator itFind = mSessions.find( tEntityID );
		if ( itFind == mSessions.end() )
		{
			LOG_WARN("TASK", "can't find send npc in joining others? my=%d, src=%d, npc_entity=%d", pPlayer->GetCharID()
				, tpSrcPlayer->GetCharID(), tEntityID );  // ���ò���Ǻ���� ����������Ѿ�ʧ���� ���˲Ŵ�Ӧ��?�ͻ�����
			return -1;
		}
		// ����NPC�Ĳ��뻤�͵��˵��б�
		itFind->second.AddSendingList( pPlayer->GetEntityID() );
	}

	// ��¼���ڻ��͵�NPC�б�
	pList->SetSendNpcEntityID(tEntityID);
	return 0;
}

// ***********************************************************
//  Function:		OnTimer	
//  Description:	
//  Input:			ƫ�ƺ���
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2008.12.2
// **********************************************************
void CSendNpcManager::OnTimer( int vOffSet )
{
	mTimer += vOffSet;
	if ( mTimer < 1000 )
		return;

	std::vector<int> _todel;
	for ( SendNpcType::iterator it = mSessions.begin(); it != mSessions.end(); ++it )
	{
		int nRet = it->second.OnNpcCtrlTimer( );
		if ( nRet == 1 ) // ����ʧ�� (���뻤�͵�ȫ����Աʧ��)
		{
			std::vector<int> tEntityIDs;
			it->second.GetPlayerIDs( tEntityIDs );
			OnSendTaskFailed( tEntityIDs ); 
			//_todel.push_back(it->first);����Ϊͳһ����
		}
		else if( nRet == 2 )// ����ɹ�
		{
			std::vector<int> tEntityIDs;
			it->second.GetPlayerIDs( tEntityIDs );
			CEntityNpc* tpNpc = (CEntityNpc*)CSceneLogic::GetSingleton().GetEntity( it->first );
			if ( tpNpc == NULL )
			{
				LOG_ERROR( "TASK", "NPC can't find?? entityid=%d",  it->first );
				OnSendTaskFailed( tEntityIDs ); 
			}
			else
			{	
				for ( std::vector<int>::iterator it2 = tEntityIDs.begin(); it2 != tEntityIDs.end(); ++it2 )
				{
					CEntityPlayer* pPlayer = ( CEntityPlayer* )CSceneLogic::GetSingleton().GetEntity( *it2 );
					if ( pPlayer == NULL )
					{
						LOG_ERROR( "TASK", "[%s:%d] can't find player %d", __FUNCTION__, __LINE__, *it2 );
						continue;
					}
					CTaskModule::GetSingleton().FireEvent( pPlayer, EVENT_SENDNPCCOMPLETE, tpNpc->GetNpcID() );
					CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
					LK_ASSERT( pList,  continue );
					pList->SetSendNpcEntityID(0); // ���ͳɹ� ���
				}
				_todel.push_back(it->first);
			}
		}

		std::vector<int> tFailedPlayers;
		nRet = it->second.OnPlayerCtrlTimer( tFailedPlayers );
		if ( nRet > 0 ) // ����ʧ����
		{
			LOG_DEBUG("TASK", "OnPlayerCtrlTimer end  num=%d", nRet );
			OnSendTaskFailed( tFailedPlayers ); // ʧ�ܴ���
			//if ( it->second.mSendingList.GetNum() == 0 ) // �Ѿ�û���ڻ����� ����Ϊͳһ����
			//{
			//	_todel.push_back(it->first);
			//}
		}
	}

	if ( _todel.size() > 0 )
	{
		for( std::vector<int>::iterator it = _todel.begin(); it != _todel.end(); ++it )
		{
			ClearSession( *it );
		}
	}

	mTimer = 0;
}

// ***********************************************************
//  Function:		OnSendTaskFailed	
//  Description:	��������ʧ��
//  Input:			���ʵ��ID
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009.9.8
// **********************************************************
int CSendNpcManager::OnSendTaskFailed( std::vector<int>& rEntityIDs )
{
	for ( std::vector<int>::iterator it = rEntityIDs.begin(); it != rEntityIDs.end(); ++it )
	{
		CEntityPlayer* pPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity( *it );
		if( pPlayer == NULL )
		{
			LOG_ERROR( "TASK", "[%s:%d] can't find player %d", __FUNCTION__, __LINE__, *it );
		}
		else
		{
			ClearPlayerSendSession( pPlayer, true );	
		}
	}

	return 0;
}

// ***********************************************************
//  Function:		OnResetSendNpc	
//  Description:	���û���NPC��״̬ ���߸ɵ� ���ߴ��ͻ�ȥ
//  Input:			NPCʵ��ID
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009.7.14
// **********************************************************
int CSendNpcManager::OnResetSendNpc( int nEntityID )
{
	CEntityNpc* tpEntity = (CEntityNpc*)CSceneLogic::GetSingleton( ).GetEntity( nEntityID );
	if ( tpEntity != NULL )
	{
		if ( tpEntity->GetCreatorID() == 0 ) // ˢ������
		{
			CSceneLogic::GetSingleton( ).DestroyEntity( tpEntity, 0 );
		}
		else // ���ͻس�����  ����
		{
			tpEntity->SetOwnerCharID( 0 );
			tpEntity->SetSendNpcState(0);
			CTemplateNpc* pTplNpc = (CTemplateNpc*)CDataStatic::SearchTpl(tpEntity->GetNpcID());
			if ( pTplNpc == NULL )
			{
				LOG_ERROR("TASK", "npc template = NULL? npc id=%d, entityid=%d", tpEntity->GetNpcID(), tpEntity->GetEntityID() );
			}
			else
			{
				tpEntity->SetPKType( pTplNpc->mPKType );
				CPropertyModule::GetSingleton().NotifyClientNpcPKTypeChanged( tpEntity );
			}
			CMapModule::GetSingleton().Teleport( tpEntity->GetLineID(), tpEntity->GetOrginMapID(), tpEntity->GetOrginPos().mX
				, tpEntity->GetOrginPos().mY, tpEntity ) ;

			CPropertyModule::GetSingleton().EntityClearbuff( tpEntity, 0, 0 );

			CNpcModule::GetSingleton().StopTaskNpc( nEntityID );
		}
	}
	return 0;
}


// ***********************************************************
//  Function:		GetNpcCurTarget	
//  Description:	�õ�NPC��ǰĿ���
//  Input:			NPCʵ��ID
//  OutPut:			
//  Return:			����
//  Others:
//  Date:			2009.6.17
// **********************************************************
bool CSendNpcManager::GetNpcCurTarget( int nEntityID, CWTPoint& rPoint )
{
	SendNpcType::iterator it = mSessions.find(nEntityID);
	if (it == mSessions.end())
	{
		LOG_ERROR("TASK", "GetNpcCurTarget get entity target can't find NPC id=%d", nEntityID );
		return false;
	}
	else
	{
		rPoint = it->second.GetCurTargetPos();
		return true;
	}
}

// ***********************************************************
//  Function:		ClearSession	
//  Description:	�������ʵ�� ����������ɰ� ��Щ���洦��
//  Input:			NPC ʵ��ID
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2009.9.8
// **********************************************************
void CSendNpcManager::ClearSession( int nNpcEntityID )
{
	OnResetSendNpc( nNpcEntityID );
	mSessions.erase( nNpcEntityID );
}

// ***********************************************************
//  Function:		ClearPlayerSendSession	
//  Description:	���������һ���ʵ�� Ŀǰ�ǵ�������ߡ��������񡢵�������ʧ�ܵ�ʱ����� 
//  Input:			��� �Ƿ�����ʧ�� �Ƿ��ⲿ����
//  OutPut:			NULL 
//  Return:			NULL
//  Others:
//  Date:			2009.9.8
// **********************************************************
void CSendNpcManager::ClearPlayerSendSession( CEntityPlayer* pPlayer, bool bIsFailed )
{
	LK_ASSERT( pPlayer!=NULL, return );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	LOG_DEBUG("TASK", "in ClearPlayerSendSession player: %s fail flag:%d", pPlayer->GetCharNameShow(), bIsFailed ); 
	SendNpcType::iterator it = mSessions.find( pList->GetSendNpcEntityID() );
	if( it == mSessions.end() )
	{
		//LOG_ERROR("TASK", "player %d send npc not in session? npc entityid=%d", pPlayer->GetCharID(), pList->GetSendNpcEntityID() );
		return;
	}

	if (bIsFailed)
		CTaskModule::GetSingleton().OnTaskFailed( pPlayer, it->second.mTaskID );

	pList->SetSendNpcEntityID(0);

	// �����ڻ��͵�NPCʵ���иɵ�
	it->second.DelSendingList( pPlayer->GetEntityID() );

	// ����Ƿ�����
	if ( it->second.mPlayerEntityID == pPlayer->GetEntityID() ) 
	{
		// �������˵Ļ��Ͷ�ʧ��
		std::vector<int> tEntityIDs;
		it->second.GetPlayerIDs( tEntityIDs );
		for ( std::vector<int>::iterator it2 = tEntityIDs.begin(); it2 != tEntityIDs.end(); ++it2 )
		{
			CEntityPlayer* pPlayer = ( CEntityPlayer* )CSceneLogic::GetSingleton().GetEntity( *it2 );
			if ( pPlayer == NULL )
			{
				LOG_ERROR( "TASK", "[%s:%d] can't find player %d", __FUNCTION__, __LINE__, *it2 );
				continue;
			}
			CTaskModule::GetSingleton().OnTaskFailed( pPlayer, it->second.mTaskID );
			CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
			LK_ASSERT( pList,  continue );
			pList->SetSendNpcEntityID(0); // ����ʧ�� ���
		}

		// �ɵ�����ʵ�� (���һ��Ҫ��������)
		ClearSession( it->first );
	}
	else
	{
		// ����ǲ��Ǹøɵ�����ʵ��
		CheckSendingSession( it->first );
	}
}

// ***********************************************************
//  Function:		CheckSendingSession	
//  Description:	�����뻤�͵��˻����ڲ� ���ھ͸ɵ����ʵ�� (������ѭ���ڲ����ã�)
//  Input:			NPC ID
//  OutPut:			NULL 
//  Return:			NULL
//  Others:
//  Date:			2009.9.8
// **********************************************************
void CSendNpcManager::CheckSendingSession( int nNpcEntityID )
{
	SendNpcType::iterator it = mSessions.find( nNpcEntityID );
	if( it == mSessions.end() )
	{
		LOG_ERROR("TASK", "no such session? npc entityid=%d", nNpcEntityID );
		return;
	}
	if ( it->second.mSendingList.GetNum() == 0 ) // �Ѿ�û���ڻ�����
	{
		ClearSession( nNpcEntityID );
	}
}

// ***********************************************************
//  Function:		CSingleSendNpc	
//  Description:	����
//  Input:			.....
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2008.12.2
// **********************************************************
CSingleSendNpc::CSingleSendNpc( int* vpX, int* vpY, int* vpMapID, int vTotal, unsigned int vNpcEntityID, unsigned int vPlayerEntityID
			   , unsigned short vTaskID, int vGird, int vLeaveTime, int nBuffTime, int nBuffID, int nInitWait )
			   : mCurIndex(0), mTotalIndex(vTotal), mMaxGird(vGird), mMaxLeaveTime(vLeaveTime), mBuffTime( nBuffTime ), mBuffID(nBuffID)
			   , mBuffTimer(0), mWaitTimer(nInitWait), mNpcEntityID(vNpcEntityID), mPlayerEntityID( vPlayerEntityID ), mTaskID( vTaskID )
{
	memcpy( mX, vpX, vTotal*sizeof(int) );
	memcpy( mY, vpY, vTotal*sizeof(int) );
	memcpy( mMapID, vpMapID, vTotal*sizeof(int) );
}


// ***********************************************************
//  Function:		CSingleSendNpc	
//  Description:	����
//  Input:			.....
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2008.12.2
// **********************************************************
CSingleSendNpc::CSingleSendNpc( )
{
	if (CObj::msCreateMode)
	{
		mCurIndex =0; 
		mTotalIndex =0; 
		mMaxGird =0; 
		mMaxLeaveTime = 0;
		mBuffTime = 0;
		mBuffID = 0;
		mBuffTimer = 0; 
		mWaitTimer = 0;
		mNpcEntityID =0; 
		mPlayerEntityID = 0;
		mTaskID = 0 ;
		memset( mX, 0, sizeof(mX) );
		memset( mY, 0, sizeof(mY) );
		memset( mMapID, 0, sizeof(mMapID) );
	}
}


// ***********************************************************
//  Function:		OnTimer	
//  Description:	1��timer,����NPC·��
//  Input:			NULL
//  OutPut:			NULL
//  Return:			0������  1������ʧ�� (��ΪNPC������)  2:����ɹ�
//  Others:
//  Date:			2008.12.2
// **********************************************************
int CSingleSendNpc::OnNpcCtrlTimer( )
{
	if ( mWaitTimer > 0 ) //  �ȴ�
	{
		mWaitTimer--;
		return 0;
	}

	// �õ�NPCλ�ã����ǲ��Ǹ�path����һ��·����
	CEntityNpc* pNpc = (CEntityNpc*)CSceneLogic::GetSingleton().GetEntity( mNpcEntityID );
	if ( pNpc == NULL )
	{
		//LOG_ERROR( "TASK", "[%s:%d] task npc %d can't find", __FUNCTION__, __LINE__, mNpcEntityID );
		return 1; // ����NPC�Ѿ�������
	}

	if ( pNpc->GetAliveStatus() != 	ALIVE_NORMAL && pNpc->GetAliveStatus() != ALIVE_BATTLE )
	{
		//LOG_DEBUG( "TASK", "[%s:%d] task npc %d may die or disappear", __FUNCTION__, __LINE__, mNpcEntityID );
		return 1; // NPC�Ѿ�������
	}
	
	CWTPoint pt01 = CWTPoint( pNpc->GetPosX(), pNpc->GetPosY() );
	CWTPoint pt02 = CWTPoint( mX[mCurIndex-1], mY[mCurIndex-1] );
	if ( pt01.LimitDistance(pt02, 0) )
	{
		if ( mCurIndex >= mTotalIndex ) // �����յ�
			return 2;
		if ( mMapID[mCurIndex-1] != mMapID[mCurIndex] ) // ���ͼ�ˣ�
		{
			bool bRet = CMapModule::GetSingleton().Teleport( pNpc->GetLineID(), mMapID[mCurIndex], mX[mCurIndex], mY[mCurIndex], pNpc );
			if ( !bRet )
			{
				LOG_ERROR("TASK", "send npc teleport failed! npc temp id=%d  player entityid = %d", pNpc->GetNpcID(), mPlayerEntityID );
			}
			mWaitTimer = SEND_NPC_REDIRECT_WAIT_TIME;
			++mCurIndex;
			return 0; // ���������������
		}
		else
		{
			CNpcModule::GetSingleton().OnMoveNpc( mNpcEntityID, mX[mCurIndex], mY[mCurIndex] );
		}
		++mCurIndex;
	}
	//LOG_DEBUG("TASK", "nownpc:(%d,%d)  target:(%d,%d) player:(%d,%d)", pt01.mX, pt01.mY, pt02.mX, pt02.mY, pPlayer->GetPosX(), pPlayer->GetPosY() );

	// ���Ҫ��BUFF
	if ( mBuffTime > 0 )
	{
		if ( ++mBuffTimer >= mBuffTime )
		{
			CPropertyModule::GetSingleton().InsertBuff( pNpc, mBuffID );
			mBuffTimer = 0;
		}
	}

	return 0;
}

// ***********************************************************
//  Function:		OnPlayerCtrlTimer	
//  Description:	��ҿ���timer �ж����в��뻤�͵��˺�NPC�ľ���
//  Input:			NULL
//  OutPut:			ʧ�ܵ���
//  Return:			ʧ�ܵ��˵�����
//  Others:
//  Date:			2008.12.2
// **********************************************************
int CSingleSendNpc::OnPlayerCtrlTimer( std::vector<int>& rFailedPlayers )
{
	CEntityNpc* tpEntityNpc = ( CEntityNpc* )CSceneLogic::GetSingleton().GetEntity( mNpcEntityID );
	LK_ASSERT( tpEntityNpc!=NULL, return 0 ); // �����ܣ���Ϊ����ǽ�����npc ctrl��

	for ( int i = 0 ; i < mSendingList.GetNum(); ++i )
	{
		st_singlesendplayer_data* tpItem = mSendingList.GetByIndex(i);
		LK_ASSERT( tpItem != NULL, continue );
		// �ж���Һ�NPC�ľ���
		CEntityPlayer* pPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity( tpItem->mPlayerID );
		if ( pPlayer == NULL ) // ��ҿ����Ѿ�����
		{
			rFailedPlayers.push_back(tpItem->mPlayerID);
			continue;
		}

		if ( pPlayer->GetAliveStatus() != ALIVE_NORMAL && pPlayer->GetAliveStatus() != ALIVE_BATTLE ) // �����
		{
			LOG_DEBUG( "TASK", "[%s:%d] player %d may die or disappear", __FUNCTION__, __LINE__, tpItem->mPlayerID );
			rFailedPlayers.push_back(tpItem->mPlayerID);
			continue;
		}

		if ( tpEntityNpc->IsWithinDistance( pPlayer, mMaxGird ) == false ) // ���볬���ˣ���ʱ++ ֪ͨ�ͻ���
		{
			if (tpItem->mLeaveTime == 0) // �״��뿪 
			{
				CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_SENDNPC_LEAVE );
			}
			if ( ++tpItem->mLeaveTime >= mMaxLeaveTime ) // ����ʧ��
			{	
				rFailedPlayers.push_back(tpItem->mPlayerID);
				continue;
			}
		}
		else // �ص������ ��0
		{
			tpItem->mLeaveTime = 0;
		}
	}
	return (int)rFailedPlayers.size();
}

// ***********************************************************
//  Function:		Start	
//  Description:	��ʼ
//  Input:			NULL
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2008.12.2
// **********************************************************
void CSingleSendNpc::Start()
{
	// ���ڻ������е�NPC ���ĵ�һ������һ�� �����ǳ����� ����Ҫ�ƶ�����һ��
	CEntityNpc* tpNpc = (CEntityNpc*)CSceneLogic::GetSingleton().GetEntity( mNpcEntityID );
	LK_ASSERT( tpNpc != NULL, return );
	if ( tpNpc->GetPosX() != mX[0] || tpNpc->GetPosY() != mY[0] )
		CNpcModule::GetSingleton().OnMoveNpc( mNpcEntityID, mX[0], mY[0] );
	++mCurIndex;
}

CWTPoint CSingleSendNpc::GetCurTargetPos()
{
	LK_ASSERT( mCurIndex > 0, return CWTPoint(0,0) );
	return CWTPoint( mX[mCurIndex-1], mY[mCurIndex-1] );
}

void CSingleSendNpc::GetPlayerIDs( std::vector<int>& rEntitys )
{
	for ( int i = 0; i < mSendingList.GetNum(); ++i )
	{
		st_singlesendplayer_data* tpItem = mSendingList.GetByIndex(i);
		LK_ASSERT( tpItem!=NULL, continue );
		rEntitys.push_back( tpItem->mPlayerID );
	}
}

//----------------------------------------------------------------------------------------------------

int CTaskInviteManager::RegInvite( unsigned int nEntityID, const char* szName, unsigned short unTaskID )
{
	LK_ASSERT( szName != NULL, return -1 );

	TASK_INVITE_CONTAINER::iterator it = mData.find( nEntityID );
	if ( it != mData.end() && it->second.size() >= TASK_INVITED_MAX )
		return -1;

	st_invite_data tmp;
	strncpy( tmp.name , szName, sizeof(tmp.name)-1 );
	tmp.task_id = unTaskID;

	if ( it == mData.end() )
	{
		std::vector<st_invite_data> tmp_vec;
		tmp_vec.push_back( tmp );

		mData.insert( std::make_pair<unsigned int, std::vector<st_invite_data> >( nEntityID, tmp_vec ) );
	}
	else
	{
		for ( std::vector<st_invite_data>::iterator iter = it->second.begin(); iter != it->second.end(); ++iter )
		{
			if ( strncmp( iter->name , szName, sizeof(iter->name)-1 ) == 0 && iter->task_id == unTaskID )
				return -2;
		}
		it->second.push_back( tmp );
	}

	return 0;
}

// ����Ƿ���ע��������������¼
bool CTaskInviteManager::ChkReg ( int nEntityID, const char* szName, unsigned short unTaskID )
{
	LK_ASSERT( szName != NULL, return false );
	TASK_INVITE_CONTAINER::iterator it = mData.find( nEntityID );
	if ( it == mData.end() )
		return false;

	std::vector<st_invite_data>::iterator _del = it->second.end();
	for ( std::vector<st_invite_data>::iterator iter = it->second.begin(); iter != it->second.end(); ++iter )
	{
		if ( strncmp( iter->name, szName, sizeof(iter->name)-1 ) == 0 && iter->task_id == unTaskID )
			_del = iter;
	}
	if ( _del == it->second.end() )
		return false;

	it->second.erase( _del );
	if ( it->second.size() == 0 )
		mData.erase( nEntityID );

	return true;
}

//----------------------------------------------------------------------------------------------------

CStorageTaskManager::CStorageTaskManager()
{
	if (CObj::msCreateMode)
	{
		m_nLastClickNpc = 0;
		m_usCurID		= 0;
		m_nGotNum		= 0;
		m_nTodayCompleted=0;
		m_nTodayRMBTimes = 0;
	}
}


// ***********************************************************
//  Function:		RefreshStorage
//  Description:	ˢ�»���Ŀ�(���ڽ������ʱ��ˢ)
//  Input:			vTaskID
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2009.3.4
// **********************************************************
void	CStorageTaskManager::RefreshStorage(unsigned short vTaskID)
{
	if (vTaskID == 0)
		return;

	st_storage_data tmp;
	tmp.m_nRefreshNum = CTaskModule::GetSingleton().RefreshStorageTask( vTaskID, REFRESH_BACK, (unsigned short*)tmp.m_usBackRefreshTasks ) ;	

	m_Storage.insert(std::make_pair(vTaskID, tmp));
}


// ***********************************************************
//  Function:		RefreshStorageOnTime
//  Description:	��ʱˢ�»���Ŀ�(���ڽ������ʱ��ˢ)
//  Input:			NULL
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2009.3.4
// **********************************************************
void	CStorageTaskManager::RefreshStorageOnTime( )
{
	unsigned short to_refresh[100] = {0}; // �϶�û100��
	int n = 0;
	for (STORAGE_TASKS_CONTAINER::iterator it = m_Storage.begin(); it != m_Storage.end(); ++it)
		to_refresh[n++] = it->first;

	m_Storage.clear();
	for (int i = 0 ; i < n; ++i)
	{
		RefreshStorage(to_refresh[i]);
	}
}



// ***********************************************************
//  Function:		OnAbortTask
//  Description:	�����������ӻ��б�
//  Input:			vTaskID
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2009.2.13
// **********************************************************
bool CStorageTaskManager::OnAbortTask( unsigned short vTaskID )
{
	--m_nGotNum;
	// ����һ���ڲ����ѻ������
	if (m_GotTasks.find(vTaskID) == NULL)
		return false;

	return m_Tasks.insert(vTaskID) == 0;
}



// ***********************************************************
//  Function:		OnEndTask
//  Description:	��ɵ�ʱ�����
//  Input:			vTaskID
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2009.3.5
// **********************************************************
bool CStorageTaskManager::OnEndTask( unsigned short vTaskID )
{
	//if (m_Tasks.find(vTaskID) != NULL)
	PlusTodayCompleted();
	--m_nGotNum;
	return true;
}



// ***********************************************************
//  Function:		IsInList	
//  Description:	�ж������Ƿ����б��У����ڽ�������֤
//  Input:			����ID
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2008.12.12
// **********************************************************
bool CStorageTaskManager::IsInList( unsigned short usTaskID )
{
	return m_Tasks.find(usTaskID) != NULL;
}

// ***********************************************************
//  Function:		RemoveFromList	
//  Description:	���б���ɾ�� ���ڽ������Ժ�
//  Input:			����ID
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2008.12.12
// **********************************************************
void CStorageTaskManager::RemoveFromList( unsigned short usTaskID )
{
	m_Tasks.remove(usTaskID);
	m_GotTasks.insert(usTaskID);
	++m_nGotNum;
}

// �õ�BUF
void CStorageTaskManager::GetTlvBuffer2(PBStorageTaskData*& pBuffer)
{
	for( int i = 0 ; i < m_Tasks.GetNum(); ++i )
	{
		unsigned short *tpTaskID = m_Tasks.GetByIndex(i);
		LK_ASSERT( tpTaskID, continue );
		pBuffer->add_tasks( *tpTaskID );
	}

	for( int i = 0 ; i < m_GotTasks.GetNum(); ++i )
	{
		unsigned short *tpTaskID = m_GotTasks.GetByIndex(i);
		LK_ASSERT( tpTaskID, continue );
		pBuffer->add_gottasks( *tpTaskID );
	}

	pBuffer->set_tasknum( m_Tasks.GetNum() );
	pBuffer->set_lastclicknpc( m_nLastClickNpc );
	pBuffer->set_curtaskid( m_usCurID );
	pBuffer->set_gotnum( m_nGotNum );
	pBuffer->set_todaycompleted( m_nTodayCompleted );
	pBuffer->set_todayrmbrefresh( m_nTodayRMBTimes );
}

void CStorageTaskManager::CreateFromTlv2(PBStorageTaskData*& pBuffer)
{
	for( int i = 0 ; i < pBuffer->tasks_size(); ++i )
	{
		m_Tasks.insert( (unsigned short)pBuffer->tasks( i ) );
	}

	for( int i = 0 ; i < pBuffer->gottasks_size(); ++i )
	{
		m_GotTasks.insert( (unsigned short)pBuffer->gottasks( i ) );
	}

	m_nLastClickNpc = pBuffer->lastclicknpc( );
	m_usCurID		= pBuffer->curtaskid( );
	m_nGotNum		= pBuffer->gotnum();
	m_nTodayCompleted = pBuffer->todaycompleted();
	m_nTodayRMBTimes = pBuffer->todayrmbrefresh();
}

// ***********************************************************
//  Function:		RegDrop	
//  Description:	ע������
//  Input:			����ID ����ID ��ƷID ���� ���ʣ�base10000�� ���Ҫ�Ѽ�����
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2009.2.1
// **********************************************************
void CTaskDropItemMgr::RegDrop( unsigned short usTaskID, int nOgreID, int nItemID, int n, int nP, int nMaxn )
{
	LK_ASSERT( usTaskID < MAX_TASK_NUM , return );
	if ( mDropData[usTaskID].find( nOgreID ) != mDropData[usTaskID].end() )
	{
		LOG_ERROR( "TASK", "task%d ogre%d reged", usTaskID, nOgreID );
		return;
	}

	st_drop_data tmp;
	tmp.m_ItemID = nItemID;
	tmp.m_n      = n;
	tmp.m_p		 = nP;
	tmp.m_maxn   = nMaxn;
	mDropData[usTaskID].insert( std::make_pair( nOgreID, tmp ) );
}


// ***********************************************************
//  Function:		GetDropItems	
//  Description:	�õ�������Ʒ
//  Input:			����ID ����ID
//  OutPut:			��Ʒ�� ����
//  Return:			�Ƿ�����˵���
//  Others:
//  Date:			2009.2.2
// **********************************************************
bool CTaskDropItemMgr::GetDropItems( unsigned short usTaskID, int nOgreID, int& rnItemID, int& rn, int& rnmaxn )
{
	LK_ASSERT( usTaskID < MAX_TASK_NUM , return false );

	DROP_DATA_CONTAINER::iterator it = mDropData[usTaskID].find(nOgreID);
	if ( it == mDropData[usTaskID].end() )
		return false;
	if( rand()%10000 <= it->second.m_p )
	{
		rnItemID = it->second.m_ItemID;
		rn = rand()%it->second.m_n + 1;
		rnmaxn = it->second.m_maxn;
	}
	return true;
}

// �����������
void CTaskDropItemMgr::ClearDrop()
{
	for (int i = 0 ; i < MAX_TASK_NUM; ++i )
	{
		mDropData[i].clear();
	}
}


// �õ�ĳ�����Ѹý��е�������ID ʧ�ܷ���0
unsigned short CTragedyTaskMgr::GetNextTask( short vTragedyIndex )
{
	LK_ASSERT( vTragedyIndex >= 1 && vTragedyIndex <= TRAGEDY_TASK_SIZE, return 0 );
	return m_tasks[vTragedyIndex].us_NextTaskID;
}

void CTragedyTaskMgr::SetNextTask( short vTragedyIndex, unsigned short vTaskID )
{
	LK_ASSERT( vTragedyIndex >= 1 && vTragedyIndex <= TRAGEDY_TASK_SIZE, return );
	m_tasks[vTragedyIndex].us_NextTaskID = vTaskID;
}


// �õ�ĳ�����ѵ�״̬
int			   CTragedyTaskMgr::GetState( short vTragedyIndex )
{
	LK_ASSERT( vTragedyIndex >= 1 && vTragedyIndex <= TRAGEDY_TASK_SIZE, return 0 );
	return m_tasks[vTragedyIndex].s_State;
}
void		   CTragedyTaskMgr::SetState( short vTragedyIndex, enTragedyTaskState vState )
{
	LK_ASSERT( vTragedyIndex >= 1 && vTragedyIndex <= TRAGEDY_TASK_SIZE, return );
	m_tasks[vTragedyIndex].s_State = vState;
}

// ����ָ���õ�
void CTragedyTaskMgr::Clear( int nIndex )
{
	if (nIndex == 0)
	{
		memset( m_tasks, 0, sizeof(st_tragedy_task)*(TRAGEDY_TASK_SIZE+1) );
		return;
	}
	LK_ASSERT( nIndex >= 1 && nIndex <= TRAGEDY_TASK_SIZE, return );
	m_tasks[nIndex] = st_tragedy_task();
}


void CTragedyTaskMgr::CreateFromTlv2( PBTaskList* pBuffer )
{
	if (pBuffer->tragedytaskdata_size() <= 0)
		return;

	for ( int i = 1; i <= pBuffer->tragedytaskdata_size(); ++i )
	{
		TragedyStruct st = pBuffer->tragedytaskdata(i-1);
		LK_ASSERT( st.tragedyindex() >= 1 && st.tragedyindex() <= TRAGEDY_TASK_SIZE, continue );
		m_tasks[st.tragedyindex()].us_NextTaskID = st.nexttragedytask();
		m_tasks[st.tragedyindex()].s_State = st.tragedystate();
	}
}

void CTragedyTaskMgr::GetTlvBuffer2( PBTaskList* pBuffer )
{
	for (int i = 1; i<= TRAGEDY_TASK_SIZE; ++i)
	{
		if ( m_tasks[i].s_State != 0 || m_tasks[i].us_NextTaskID != 0 )
		{
			TragedyStruct* tp = pBuffer->add_tragedytaskdata();
			tp->set_tragedyindex(i);
			tp->set_nexttragedytask(m_tasks[i].us_NextTaskID);
			tp->set_tragedystate(m_tasks[i].s_State);
		}
	}
}

int  CTragedyTaskMgr::GetAllInfo( int *anIndex, unsigned short *asNextID, int *anState )
{
	int n = 0;
	for (int i = 1; i<= TRAGEDY_TASK_SIZE; ++i)
	{
		if ( m_tasks[i].s_State != 0 || m_tasks[i].us_NextTaskID != 0 )
		{
			anIndex[n]  = i;
			asNextID[n] = m_tasks[i].us_NextTaskID;
			anState[n]  = m_tasks[i].s_State;
			++n;
		}
	}
	return n;
}

////////////////////////// �����������

void CTaskGroupData::OnEndOneTask()
{
	++mTodayTimes; // ֻ++���� ���������OnDay....������
	++mWeekTimes; 
}

void CTaskGroupData::OnAccptOneTask()
{
	++mTodayAccptTimes; // ֻ++���� ���������OnDay....������
	++mWeekAccptTimes;
}


// 0�ɹ�
int  CTaskGroupManager::OnEndOneTask( unsigned int nGroupID )
{
	TaskGroupMgrType::iterator it = mData.find( nGroupID );
	if ( it == mData.end() )
	{
		CTaskGroupData _group;
		_group.OnEndOneTask();
		std::pair<TaskGroupMgrType::iterator, bool> ret = mData.insert( std::make_pair( nGroupID, _group ) );
		if ( ret.second )
		{
			return 0;
		}
		else
		{
			LOG_ERROR("TASK", "no space in TaskGroup!");
			return -1;
		}
	}
	else
	{
		it->second.OnEndOneTask();
	}
	return 0;
}



// 0�ɹ�
int  CTaskGroupManager::OnAcceptOneTask( unsigned int nGroupID )
{
	TaskGroupMgrType::iterator it = mData.find( nGroupID );
	if ( it == mData.end() )
	{
		CTaskGroupData _group;
		_group.OnAccptOneTask();
		std::pair<TaskGroupMgrType::iterator, bool> ret = mData.insert( std::make_pair( nGroupID, _group ) );
		if ( ret.second )
		{
			return 0;
		}
		else
		{
			LOG_ERROR("TASK", "no space in TaskGroup!");
			return -1;
		}
	}
	else
	{
		it->second.OnAccptOneTask();
	}
	return 0;
}



// �õ��������ĳ����������
int  CTaskGroupManager::GetTodayTimes( unsigned int nGroupID )
{
	TaskGroupMgrType::iterator it = mData.find( nGroupID );
	if ( it == mData.end() )
	{
		return 0;
	}
	else
	{
		return it->second.GetTodayTimes();
	}
}


// �õ��������ĳ����������
int  CTaskGroupManager::GetTodayAcceptTimes( unsigned int nGroupID )
{
	TaskGroupMgrType::iterator it = mData.find( nGroupID );
	if ( it == mData.end() )
	{
		return 0;
	}
	else
	{
		return it->second.GetTodayAccptTimes();
	}
}

// ���ô���
void  CTaskGroupManager::SetTodayTimes( unsigned int nGroupID, int nTimes )
{
	TaskGroupMgrType::iterator it = mData.find( nGroupID );
	if ( it == mData.end() )
	{
		return ;
	}
	else
	{
		it->second.SetTodayTimes(nTimes);
	}
}

// �µ�һ�쵽��
int  CTaskGroupManager::OnNewdayCome()
{
	for ( TaskGroupMgrType::iterator it = mData.begin(); it != mData.end(); ++it )
	{
		it->second.SetTodayTimes(0);
		it->second.SetTodayAccpTimes(0);
	}
	return 0;
}


// �õ��������ĳ����������
int  CTaskGroupManager::GetWeekTimes( unsigned int nGroupID )
{
	TaskGroupMgrType::iterator it = mData.find( nGroupID );
	if ( it == mData.end() )
	{
		return 0;
	}
	else
	{
		return it->second.GetWeekTimes();
	}
}


// �õ����ܽ���ĳ����������
int  CTaskGroupManager::GetWeekAcceptTimes( unsigned int nGroupID )
{
	TaskGroupMgrType::iterator it = mData.find( nGroupID );
	if ( it == mData.end() )
	{
		return 0;
	}
	else
	{
		return it->second.GetWeekAccptTimes();
	}
}

// ���ô���
void  CTaskGroupManager::SetWeekTimes( unsigned int nGroupID, int nTimes )
{
	TaskGroupMgrType::iterator it = mData.find( nGroupID );
	if ( it == mData.end() )
	{
		return ;
	}
	else
	{
		it->second.SetWeekTimes(nTimes);
	}
}

// �µ�һ�ܵ���
int  CTaskGroupManager::OnNewWeekCome()
{
	for ( TaskGroupMgrType::iterator it = mData.begin(); it != mData.end(); ++it )
	{
		it->second.SetWeekTimes(0);
		it->second.SetWeekAccptTimes(0);
	}
	return 0;
}



void CTaskGroupManager::CreateFromPB( PBTaskList* pBuffer )
{
	for ( int i = 0; i < pBuffer->taskgroups_size(); ++i )
	{
		PBTaskGroupData* tpData = pBuffer->mutable_taskgroups(i);
		CTaskGroupData _group;
		_group.SetTodayTimes( tpData->todaycompleted() );
		_group.SetTodayAccpTimes( tpData->todayaccepted() );
		_group.SetWeekTimes( tpData->weekcompleted() );
		_group.SetWeekAccptTimes( tpData->weekaccepted() );
		mData.insert( std::make_pair( tpData->groupid(), _group ) );
	}
}

void CTaskGroupManager::GetPBBuffer( PBTaskList* pBuffer )
{
	for ( TaskGroupMgrType::iterator it = mData.begin(); it != mData.end(); ++it )
	{
		PBTaskGroupData* tpData = pBuffer->add_taskgroups();
		tpData->set_groupid( it->first );
		tpData->set_todaycompleted( it->second.GetTodayTimes() );
		tpData->set_todayaccepted( it->second.GetTodayAccptTimes() );
		tpData->set_weekcompleted(it->second.GetWeekTimes());
		tpData->set_weekaccepted( it->second.GetWeekAccptTimes() );
	}
}

//==============================================new class==============================

// NPC����� �������NPC��״̬ �Ա������һЩȫ�ֵ��¼�  ����һȺ������ʧ�ܵ�
int CTaskNpcMonitor::RegWatchNpc( int nNpcTempID )
{
	LOG_DEBUG("TASK", "%s  tempid=%d", __FUNCTION__, nNpcTempID );
	std::pair<NPC_MONITOR_TYPE::iterator, bool> ret = m_NpcMap.insert( std::make_pair( nNpcTempID, CNpcState() ) );
	if ( ret.second )
		return 0;
	else
		return -1;
}

int CTaskNpcMonitor::OnNpcCreated( int nNpcTempID, unsigned int nNpcEntityID )
{
	LOG_DEBUG("TASK", "%s  tempid=%d entityid=%d", __FUNCTION__, nNpcTempID, nNpcEntityID );
	NPC_MONITOR_TYPE::iterator it = m_NpcMap.find( nNpcTempID );
	if ( it == m_NpcMap.end() )
	{
		return -1;
	}
	else
	{
		if ( it->second.nNpcEntityID != INVALID_OBJ_ID )
			return -2;
		it->second.nNpcEntityID = nNpcEntityID;
	}
	return 0;
}

// NPC�����ٵ�ʱ�����
int CTaskNpcMonitor::OnNpcDestroyed( int nNpcTempID )
{
	LOG_DEBUG("TASK", "%s  tempid=%d ", __FUNCTION__, nNpcTempID );
	NPC_MONITOR_TYPE::iterator it = m_NpcMap.find( nNpcTempID );
	if ( it == m_NpcMap.end() )
	{
		return -1;
	}
	else
	{
		it->second.nNpcEntityID = 0;
		// �����ݳ�������ݶ����
		for ( int i = 0; i < MAX_ACTION_TYPES; ++i )
		{
			it->second.mActions[i].Clear();
		}
	}
	return 0;
}

unsigned int CTaskNpcMonitor::GetNpcEntityID( int nNpcTempID )
{
	NPC_MONITOR_TYPE::iterator it = m_NpcMap.find( nNpcTempID );
	if ( it == m_NpcMap.end() )
	{
		return 0;
	}
	else
	{
		return it->second.nNpcEntityID ;
	}
}

// NPC��������
int CTaskNpcMonitor::OnNpcDied( int nNpcTempID )
{
	NPC_MONITOR_TYPE::iterator it = m_NpcMap.find( nNpcTempID );
	if ( it == m_NpcMap.end() )
	{
		return 0;
	}
	else // Ҫ����
	{
		// ����
		int t = it->second.mActions[NPC_DIE].GetNum();
		LOG_DEBUG("TASK", "in %s  GetNum:%d", __FUNCTION__, t );
		for ( int i = 0; i < t ; ++i)
		{
			_PlayerAction* tpSingleAction = it->second.mActions[NPC_DIE].GetByIndex(i);
			if ( tpSingleAction != NULL )
			{
				LOG_DEBUG("TASK", "in %s dispos: player:%d, taskid=%d", __FUNCTION__, tpSingleAction->nPlayerEntityID, tpSingleAction->usTaskID);
				switch(tpSingleAction->nActionType)
				{
				case NPC_DIE_FAIL:
					{
						// NPC��������ʧ��
						CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(tpSingleAction->nPlayerEntityID);
						if ( tpPlayer == NULL )
						{
							LOG_ERROR("TASK", "can't find player%d ? taskid=%d", tpSingleAction->nPlayerEntityID, tpSingleAction->usTaskID );
						}
						else
						{
							// ������ѭ������ɾ����
							CTaskModule::GetSingleton().OnTaskFailed( tpPlayer, tpSingleAction->usTaskID, false, false );
						}
						break;
					}
				default:
					{
						LOG_ERROR("TASK", "err action:%d taskid=%d", tpSingleAction->nActionType, tpSingleAction->usTaskID );
					}
				}
			}
		}
		// ������� ֱ�����
		it->second.mActions[NPC_DIE].Clear();
	}
	return 0;
}

// ע��
int CTaskNpcMonitor::RegGlobalTaskAction( int nTempID, enTaskActionType etype, CEntityPlayer* pPlayer, unsigned short vTaskID )
{
	if ( pPlayer == NULL )
		return -3;

	NPC_MONITOR_TYPE::iterator it = m_NpcMap.find( nTempID );
	if ( it == m_NpcMap.end() )
	{
		LOG_ERROR("TASK", "in %s npc %d not reg?", __FUNCTION__, nTempID );
		return -1;
	}

	_PlayerAction _action;
	_action.nActionType = etype;
	_action.nPlayerEntityID = pPlayer->GetEntityID();
	_action.usTaskID = vTaskID;

	LOG_DEBUG("TASK", "in %s reg: player:%d, taskid=%d", __FUNCTION__, pPlayer->GetEntityID(), vTaskID);

	// ����16λ ��ô�������
	int nType = (etype>>16);
	if ( nType < 0 || nType >= MAX_ACTION_TYPES )
	{
		LOG_ERROR("TASK", "in %s ntype= %d ??", __FUNCTION__, etype );
		return -1;
	}
	else
	{
		int t = it->second.mActions[nType].insert(_action);
		LOG_DEBUG("TASK", "in %s insert ret:%d", __FUNCTION__, t );
	}
	return 0;
}

// ɾ��ע�ắ�� ���ô���������� �Ժ���һ��Ҫ1������ע��������� ����չ
// Ŀǰ������ʧ�ܡ����������������ɡ�������ߵ�ʱ�����
int CTaskNpcMonitor::RemoveGlobalTaskAction(int nTempID, CEntityPlayer* pPlayer, unsigned short vTaskID)
{
	if ( pPlayer == NULL )
		return -3;

	NPC_MONITOR_TYPE::iterator it = m_NpcMap.find( nTempID );
	if ( it == m_NpcMap.end() )
	{
		LOG_ERROR("TASK", "in %s npc %d not reg?", __FUNCTION__, nTempID );
		return -1;
	}

	_PlayerAction key;
	key.nPlayerEntityID = pPlayer->GetEntityID();
	key.usTaskID = vTaskID;

	// ���еĶ�Ҫ����
	for ( int i =0 ; i < MAX_ACTION_TYPES; ++i )
	{
		it->second.mActions[i].remove( key );
	}

	return 0;
}

CChairManTaskManager::CChairManTaskManager()
{
	if ( CObj::msCreateMode )
	{
		Initialize();
	}
}

void CChairManTaskManager::Initialize()
{
	//memset(m_Tasks, 0, sizeof(m_Tasks));
	m_usCurID = 0;	
	mCompleted.initailize();
	m_nAccepted = 0;
}


void CChairManTaskManager::GetTlvBuffer2(PBChairManTaskData* pBuffer)
{
	if ( m_usCurID == 0 ) // ��û�ӹ�
		return;

	pBuffer->set_chairmanid( m_usCurID );
	pBuffer->set_acceptednum( m_nAccepted );
	for ( CHAIRMAN_COMPLETED_TYPE::iterator it = mCompleted.begin();
		it != mCompleted.end(); ++it )
	{
		SingleCompletedInf* tpSngle = pBuffer->add_completed();
		LK_ASSERT( tpSngle != NULL, continue );
		tpSngle->set_chairmanid( it->first );
		tpSngle->set_completednum( it->second );
	}
}

void CChairManTaskManager::CreateFromTlv2(PBChairManTaskData* pBuffer)
{
	m_usCurID = pBuffer->chairmanid( );
	m_nAccepted  = pBuffer->acceptednum();
	for ( int i = 0 ; i < pBuffer->completed_size(); ++i )
	{
		SingleCompletedInf tSingle = pBuffer->completed(i);
		mCompleted.insert(std::pair<unsigned short, int>( tSingle.chairmanid(), tSingle.completednum() ) );
	}

	// Ϊ�˼��� �������������������� �Ͱ����µ����ݽṹд��ȥ
	int nLastCompleteNum = pBuffer->completednum();
	if ( nLastCompleteNum > 0)
	{
		mCompleted.insert(std::pair<unsigned short, int>( m_usCurID, nLastCompleteNum ) );
	}
}

void CChairManTaskManager::FillMessage2Cli( CMessageGetChairManTaskResponse* pMsg )
{
}

int  CChairManTaskManager::GetCompleteNum( )
{
	CHAIRMAN_COMPLETED_TYPE::iterator it = mCompleted.find( m_usCurID );
	if ( it == mCompleted.end() )
		return 0;
	return it->second;
}

void CChairManTaskManager::ResetTasks( int nCurID )
{
	if ( m_usCurID == nCurID )
		return;

	m_usCurID = nCurID;
	m_nAccepted = 0;

	//for ( int i = 0; i < nNum && i < CHAIRMAN_TASK_NUM; ++i )
	//{
	//	m_Tasks[i].mTaskID = paTasks[i];
	//}
}

// ������񴥷� ���ȫ������ˣ�����true
void CChairManTaskManager::OnTaskEnd()
{
	if ( m_nAccepted > 0 )
		--m_nAccepted;

	CHAIRMAN_COMPLETED_TYPE::iterator it = mCompleted.find( m_usCurID );
	if ( it == mCompleted.end() ) // �¼�
	{
		mCompleted.insert(std::pair<unsigned short, int>( m_usCurID, 1) );
	}
	else
	{
		it->second++;
	}
}

// ����Ƿ�ɽӵ�ǰ����
bool CChairManTaskManager::CheckAcceptChairMan( unsigned short usChairManID )
{
	// ���δ�� �ѽ���ͬ pass
	if ( m_usCurID == 0 || m_usCurID == usChairManID ) 
		return true;
	// ������ѽӲ�ͬ ��������û�� Ҳû��ɹ� ͨ��
	// �����޸� ȥ������ġ�Ҳû��ɹ���
	else if ( m_usCurID != usChairManID && m_nAccepted==0 )
		return true;

	return false;
}

// �������Ժ����
void CChairManTaskManager::OnAccepted()
{
	++m_nAccepted;
}

// �������Ժ����
void CChairManTaskManager::OnAborted()
{
	if ( m_nAccepted > 0 )
		--m_nAccepted;
}