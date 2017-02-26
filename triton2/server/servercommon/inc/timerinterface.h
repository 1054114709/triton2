#ifndef __TIMER_INTERFACE__
#define __TIMER_INTERFACE__

#include "timermanager.h"
#include "timer_define.h"


#define TIMER_OTHER_INFO 4 // ��ʱ��������Ϣ����

class CMessageInternalTimeOut;


/************************************************************************/
/*  ��ʱ����ӿ�                                                                     */
/************************************************************************/
class ITimerReceiver
{
public:
	
	// ���ö�ʱ���� �����µĶ�ʱ��id
	virtual int SetTimer( int nOwnerID, short nTimerMark, int nMillSec, unsigned char ucOtherInfoLen = 0, int* nOtherInfo = NULL, unsigned int nCalledTime = 1 ) = 0;

	// ���ö�ʱ���� �����µĶ�ʱ��id . (��λ:��, �Ƽ�������ʱ��>24��ʹ��)
	virtual int SetTimerBySec( int nOwnerID, short nTimerMark, int nSec, unsigned char ucOtherInfoLen = 0, int* nOtherInfo = NULL, unsigned int nCalledTime = 1 ) = 0;
	
	// ���ָ��id��ʱ�����ӱ�������ɾ����ʱ��id,ͬʱ��Ӷ�ʱ��������ɾ����ʱ������), ע���ӳ�ɾ�����������á�
	virtual int ClearTimer( int nTimerID, bool bNow = false ) = 0;

	// ���ָ�����Ͷ�ʱ��
	virtual int ClearTimer( emTimerMark nTimerMark, unsigned char ucOtherInfoLen = 0, int* nOtherInfo = NULL, bool bNow = false ) = 0;

	// ������ж�ʱ�����ӱ�������ɾ����ʱ��id,ͬʱ��Ӷ�ʱ��������ɾ����ʱ������
	virtual int ClearAllTimer() = 0;

	// ǿ�Ƴ�ʱ���ж�ʱ�����ӱ�������ɾ����ʱ��id,ͬʱ��Ӷ�ʱ��������ɾ����ʱ������
	//virtual int TimeOutAllTimer() = 0;

	// ǿ�Ƴ�ʱһ��ָ����ʱ��
	virtual int TimeOutOneTimer( int nTimerID ) = 0;
};

/************************************************************************/
/*  ��Ҷ�ʱ������																		*/
/************************************************************************/
class CPlayerTimerReceiver : public ITimerReceiver
{
public:

	CPlayerTimerReceiver();
	virtual ~CPlayerTimerReceiver();

	virtual int SetTimer( int nOwnerID, short nTimerMark, int nMillSec, unsigned char ucOtherInfoLen = 0, int* nOtherInfo = NULL, unsigned int nCalledTime = 1) ;

	virtual int SetTimerBySec( int nOwnerID, short nTimerMark, int nSec, unsigned char ucOtherInfoLen = 0, int* nOtherInfo = NULL, unsigned int nCalledTime = 1 ) ;

	virtual int ClearTimer( int nTimerID, bool bNow = false );

	virtual int ClearTimer( emTimerMark nTimerMark, unsigned char ucOtherInfoLen = 0, int* nOtherInfo = NULL, bool bNow = false ) ;

	virtual int ClearAllTimer() ;

	//virtual int TimeOutAllTimer() ;

	virtual int TimeOutOneTimer( int nTimerID ) ;

private:
	enum { MAX_PLYER_TIMER_SETTED = 64 };
	typedef lk::vector< int, MAX_PLYER_TIMER_SETTED >	TimerContainer;
	
	// �����Ҫ�Ķ�ʱ����ԱȽ϶�
	TimerContainer mTimerContainer;
};

/************************************************************************/
/* NPC��ʱ������                                                                      */
/************************************************************************/
class CNpcTimerReceiver : public ITimerReceiver
{
public:

	CNpcTimerReceiver();
	virtual ~CNpcTimerReceiver();

	virtual int SetTimer( int nOwnerID, short nTimerMark, int nMillSec, unsigned char ucOtherInfoLen = 0, int* nOtherInfo = NULL, unsigned int nCalledTime = 1) ;

	virtual int SetTimerBySec( int nOwnerID, short nTimerMark, int nSec, unsigned char ucOtherInfoLen = 0, int* nOtherInfo = NULL, unsigned int nCalledTime = 1 ) ;

	virtual int ClearTimer( int nTimerID, bool bNow = false );

	virtual int ClearTimer( emTimerMark nTimerMark, unsigned char ucOtherInfoLen = 0, int* nOtherInfo = NULL, bool bNow = false ) ;

	virtual int ClearAllTimer() ;

	//virtual int TimeOutAllTimer() ;

	virtual int TimeOutOneTimer( int nTimerID ) ;

private:
	enum { MAX_NPC_TIMER_SETTED = 16 };
	typedef lk::vector< int, MAX_NPC_TIMER_SETTED >	TimerContainer;

	// npc ��Ҫ�Ķ�ʱ����ԱȽ���
	TimerContainer mTimerContainer;
};


#endif // __TIMER_INTERFACE__
