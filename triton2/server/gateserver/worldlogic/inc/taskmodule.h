#ifndef _TASK_GATE_H_
#define _TASK_GATE_H_

#include "module_manager.h"
#include "entity.h"
#include "lk_hashmap.h"
#include "lk_string.h"
#include "lk_vector.h"
#include "lk_queue.h"
#include "gateobj_define.h"
#include "gateobj_manager.h"
#include "servertool.h"
#include "tasktype.h"

using namespace GateServer;

// ���˷�������     ��������

class CSinglePublishInfo
{
private:
	unsigned int mTodayPublishTaskNum;   //  ��ƴ�
	unsigned int mOncePublishTaskNum;	 //  һ�η����������
	unsigned int mTotalFinishNum;		 //  ��ɷ���������
	unsigned int mEntityID;				 //  ���ID

	// �����������͵�����  ��������ɫ����
	struct st_single_color                
	{	
		unsigned short PubNum;
		unsigned short RecvAwards;
		st_single_color()
		{		
			if (CObj::msCreateMode)		
			{			
				PubNum		= 0;			
				RecvAwards	= 0;		
			}	
		}
	};

public:
	st_single_color mSingleColorInfo[ COLOR_TOTAL ];  // ��ͬ��ɫ����������

	CSinglePublishInfo()
	{
		if(CObj::msCreateMode)
		{
			Initailize();
		}
	};

	void Initailize();

	unsigned int GetTodayPublishNumber(){ return mTodayPublishTaskNum; }	
	unsigned int GetOncePublishNumber(){ return mOncePublishTaskNum; }	
	unsigned int GetFinishNumber(){ return mTotalFinishNum; }	
	unsigned int GetEntityID(){return mEntityID; }


	void SetTodayPublishNumber(int num){ mTodayPublishTaskNum = num; }	
	void SetOncePublishNumber(int num){ mOncePublishTaskNum = num; }	
	void SetFinishNumber(int num) { mTotalFinishNum = num ; }	
	void SetEntityID(int mID){ mEntityID = mID; }

};


// ���巢�������������

struct st_group_publish_task
{
	unsigned short	mTaskID;					
	unsigned short	mTaskState;				    // ȫ��ֻ��¼������δ����״̬��
	unsigned int	mEntityID;					// ������ID	
	st_group_publish_task()
	{
		if (CObj::msCreateMode)		
		{			
			mTaskID		= 0;			
			mTaskState  = 1;
			mEntityID	= 0;
		}	
	}
	st_group_publish_task(unsigned short vTaskID, unsigned short vTaskState, unsigned int vEntityID)
	{
		mTaskID		= vTaskID;			
		mTaskState  = vTaskState;
		mEntityID	= vEntityID;
	}
};

typedef lk::vector<st_group_publish_task, PUBLISH_LIST_SIZE > PUBLISHLIST;


// ���巢��������

class CGroupPublishInfo
{
private:
	int mTodayPublishTimes;					// �췢������
	int mWeekPublishTimes;					// �ܷ�������

public:
	PUBLISHLIST mPublishList;				// �����б�

	CGroupPublishInfo()
	{
		if(CObj::msCreateMode)
		{
			Initailize();
		}	
	}

	void Initailize();
	void OnNewDayCome();
	void OnNewWeekCome();
	
	int GetTodayPublishTimes(){ return mTodayPublishTimes; }
	int GetWeekPublishTimes(){ return mWeekPublishTimes; }	

	void SetTodayPublishTimes( int nTimes ){ mTodayPublishTimes = nTimes; }
	void SetWeekPublishTimes(int nTimes){ mWeekPublishTimes = nTimes; }

	
	void AddPublishCount(){ ++mTodayPublishTimes; ++mWeekPublishTimes;}
	void CleanPublishCout(){mTodayPublishTimes = 0; mWeekPublishTimes = 0;}

	unsigned short GetPublishStateByTask(unsigned short vTaskID);  //  �õ�����ķ���״̬
	unsigned int GetPublishPlayerByTask(unsigned short vTaskID);   //  �õ����񷢲���

	void SetPublishTaskState(unsigned short vTaskID, unsigned short vState, unsigned int vEntityID);
	void SetPublishPlayerID(unsigned short vTaskID, unsigned int vEntityID);

	void LoadPublishList( PUBLISHLIST *TempList)
	{
		mPublishList.initailize();
		PUBLISHLIST::iterator it = TempList->begin();
		for ( ;it != TempList->end(); ++it )
		{
			mPublishList.push_back(*it);
		}
	}
	
};

// ����ģ��洢����ʱ����  ������������
struct GroupLimitInfo 
{
	int TodayMaxPublish;					// ÿ�췢������
	int WeekMaxPublish;						// ÿ�ܷ�������
	
	PUBLISHLIST mTaskList;					// �����б�

	void Initailize()
	{
		TodayMaxPublish		= 0;
		WeekMaxPublish		= 0;
		mTaskList.initailize();
	}
	int GetTodayMaxPublish(){return TodayMaxPublish; }
	int GetWeekMaxPublish(){return WeekMaxPublish; }

	void SetTodayMaxPublish(int nMax){ TodayMaxPublish = nMax; }
	void SetWeekMaxPublish(int nMax){WeekMaxPublish = nMax; }
};

//  ����ģ��

class CTaskModule : public CDataModule, public CSingleton< CTaskModule >
{
public:
	GroupLimitInfo mCorpsLimit;
	CTaskModule(){ mCorpsLimit.Initailize(); }
	// ���ط�������Ϣ
	virtual void OnLaunchServer() { }
	virtual void OnExitServer() { }
	virtual void OnTimer(unsigned int, unsigned int) { }
	virtual void OnMessage(int vServerID, CMessage *pMessage);
	virtual void OnNewDayCome();

	virtual bool IsLaunched() { return true; }

	static int CountSize( ) { return sizeof( CTaskModule ); }

	void OnReloadConfig(const char* pRoot);

public:
	
	// ��÷��������б�
	GroupLimitInfo *GetCorpsLimit(){ return &mCorpsLimit; }

	int CheckPublishLimit(unsigned int role_id, unsigned short task_id, int vMoney);		//	��鷢������
	// ��Ϣ����
	void OnMessagePlayerCheckPublishBoard( int vServerID, CMessage *pMessage );     //   ��Ҳ鿴չ������
	
	void OnMessagePlayerPublishTask(int vServerID, CMessage *pMessage);             // ��ҷ�����������
};

#endif
