#ifndef _TIMERMNG_H_
#define _TIMERMNG_H_

#include "object.h"
#include "servertool.h"
#include "objmanager.h"
#include "lk_vector.h"

class CSharedMem;

#define OBJ_ID_START(obj_type)	(((obj_type) << OBJ_ID_BITS) + 1)
#define OBJ_ID_END(obj_type)	((((obj_type) + 1) << OBJ_ID_BITS) - 10)
#define OBJ_ID_COUNT(obj_type, count) OBJ_ID_START(obj_type), count, OBJ_ID_END(obj_type)

#define MAX_TIMER_PARA_NUM 4
#define TIMER_OBJECT_SHORT_ID  0xFD	// timer����type, û��ʵ������
#define TIMER_OBJECT_MIDDLE_ID 0xFE	// timer����type, û��ʵ������
#define TIMER_OBJECT_LONG_ID   0xFF	// timer����type, û��ʵ������
#define TIMER_DIVIDE_1	60000		// ����Timer�ֽ�
#define TIMER_DIVIDE_2	1800000		// �г�Timer�ֽ�
#define TIMER_CHECK_1	1000		// ��Timer���
#define TIMER_CHECK_2	5000		// ��Timer���

#define MAX_MILLSECONDS_OF_TIMER  2073600000 // ��ʱ��΢�������Ϊ24�� 3600*1000*24*24

/**
** @class CTimerItem
**
** ��ʱ������
**
*/
class CTimerItem : public CObj
{
public:

	enum emTimerType
	{
		SHORT_TIMER		= 0,	// �̶�ʱ��
		MIDDLET_TIMER	= 1,	// �ж�ʱ��
		LONG_TIMER		= 2,	// ����ʱ��
	};

	CTimerItem()
	{
		if( CObj::msCreateMode )
			Initialize();
		else
			Resume();
	}


	virtual ~CTimerItem(){}

	virtual int Resume();
	virtual int Initialize( );

	// ǿ�Ƴ�ʱ(��ʱ�������ⲿǿ�е���timeout)
	inline bool IsForceTimeOut( ) { return mMillSeconds >= 0 ; }

public:

	int				mOwnerID;		// ��ʱ��ӵ����ʵ��ID
	int				mSeconds;		// ����ʱ��, s
	int				mMillSeconds;	// ����ʱ�䣬ms	
	short			mTimerMark;		// ��ʱ����־
	char			mIsCleared;		// ��ʱ��״̬, �Ƿ��Ѿ�����ʶΪ�������ֹ��������±�ɾ����timer�ٴ�����( 0-��1-�ǣ�
	unsigned char	mOtherInfoLength;
	int				mOtherInfo[MAX_TIMER_PARA_NUM];
	int				mCalledNum;		// ִ�д���
	int				mDurationSeconds; // ��ʱ��ʱ��(����仯����ע�⡿���ڳ���ʱ����Ч)
}; /* CTimerItem */


/**
** @class CTimerMng
**
** ��ʱ������
**
*/
class CTimerMng : public CSingleton<CTimerMng>
{
public:

	CTimerMng();
	~CTimerMng();

	void* operator new( size_t nSize );
	void  operator delete( void *pMem );

	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* pointer, const char* file, int line);

	/**
	** ��ʼ���� �ڹ����ڴ�Ԥ�������timer����
	*/
	int Initialize( );

	/** 
	** ��鶨ʱ�����У�ɾ�����ڶ�ʱ��
	*/
	int CheckTimerQueue( unsigned int nTimeOffset );

	/**
	** ���ö�ʱ��
	*/
	int SetTimer(int nOwnerID, short nTimerMark, int nMillSec, unsigned char ucOtherInfoLen = 0, int* nOtherInfo = NULL, int nCalledTime = 1);
	
	//  ע�⣺ֻ�г���24��ļ�ʱ��������ʹ�øýӿڡ� ��ʱ��λ����
	int SetTimerBySec( int nOwnerID, short nTimerMark, int nSec, unsigned char ucOtherInfoLen = 0, int* nOtherInfo = NULL, int nCalledTime = 1 );

	/**
	** �����ʱ��(ĳЩ����²�����ѭ����ɾ��)
	*/
	int ClearTimer(int vTimerID, bool bNow = false );

	/**
	** ǿ���Գ�ʱ
	*/
	int ForceTimeOut( int nTimerID );

	/**
	** ��ȡ��ʱ��ʣ��ʱ��
	*/
	int GetLeftTime( int nTimerID, int& nSec, int& nMillSec );

	/**
	** ���ͳ��
	*/
	void Dump( char* pBuffer, unsigned int& unLen );

	/**
	** �õ���ʱ��
	*/ 
	CTimerItem* GetTimer( int nTimerID );

	void CheckTimer( CTimerItem* pTimerItem, unsigned int nTimeOffset );

	static CSharedMem *mShmPtr;

	static int CountSize();

private:

	/**
	** ����ʱ��ʱ��
	*/
	int TimeOut(CTimerItem* pTimerItem);

private:
	enum
	{
		TIMER_PRECISION		= 200,		// ��ʱ������ 200 ms 
		TIMER_QUEUE_LENGTH	= 160000,	// ��ʱ��������
	};

	typedef ObjManager< CTimerItem,	OBJ_ID_COUNT( TIMER_OBJECT_SHORT_ID, TIMER_QUEUE_LENGTH	) >		 ShortTimerObjMng;
	typedef ObjManager< CTimerItem,	OBJ_ID_COUNT( TIMER_OBJECT_MIDDLE_ID, TIMER_QUEUE_LENGTH	) >	 MiddleTimerObjMng;
	typedef ObjManager< CTimerItem,	OBJ_ID_COUNT( TIMER_OBJECT_LONG_ID, TIMER_QUEUE_LENGTH	) >		 LongTimerObjMng;

	ShortTimerObjMng		mShortTimerQueue;
	MiddleTimerObjMng		mMiddleTimerQueue;
	LongTimerObjMng			mLongTimerQueue;
	unsigned int			mCheckTimer1;
	unsigned int			mCheckTimer2;

	typedef lk::vector< int, 5000 > DeleteList;
	typedef lk::vector< int, 8000 > TimeoutList;

	DeleteList		mDeleteList;
	TimeoutList		mTimeoutList;



}; /* CTimerMng */



#endif /* _TIMERMNG_H_ */

