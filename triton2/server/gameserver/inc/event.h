/******************************************************************************
	��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾
	
******************************************************************************
	�ļ���          : event.h
	�汾��          : 1.0
	����            : 
	��������        : 2009-06-24
	����޸�        : 
	��������        : �������Ϸ�ڵ��¼���װ��������Ϲ۲���ģʽ�����֪ͨ�����۲��ߣ�
						����Ϸ�߼�������������϶ȸ��͡� ��ʵ�ּ����ӿڣ��ȴ������ع�ʱ
						���ģӦ�á�
	�����б�        : 
	�޸���ʷ        : 
	1 ����          : 2009-06-24
	����			: ZHL
	�޸�����		: ����
*******************************************************************************/

#pragma once

#include "servertool.h"
#include "coretype.h"
#include "lk_vector.h"


//enum EventType
//{
//	EVENT_DROPITEM    =  1,			// ������Ʒ
//	EVENT_CREATEOGRE  =  2,			// ��������
//	EVENT_PUSHINFB	  =  3,			// ���븱��
//};
//
//class CEvent;
//class CEventHandler;
//
//class CEvent
//{
//public:
//	int mEventID;
//
//	char mStrBuffer[ 1000 ];
//	int  mParam1;
//	int	 mParam2;
//	int  mParam3;
//	int  mParam4;
//
//public:
//	CEvent( )
//	{
//		mEventID = 0;
//		memset( mStrBuffer, 0, sizeof( mStrBuffer ) );
//		mParam1 = 0;
//		mParam2 = 0;
//		mParam3 = 0;
//		mParam4 = 0;
//	}
//	~CEvent( ){ }
//
//	CEvent( int vEventID, char *vStrBuffer, unsigned int vLen, int vParam1, int vParam2, int vParam3, int vParam4 ) : mEventID( vEventID ), 
//		mParam1( vParam1 ), mParam2( vParam2 ), mParam3( vParam3 ), mParam4( vParam4 )
//	{
//		memset( mStrBuffer, 0, sizeof( mStrBuffer ) );
//		memcpy( mStrBuffer, vStrBuffer, min( vLen, sizeof( mStrBuffer ) ) );
//	}
//
//	inline void Assign( int vEventID, char *vStrBuffer, unsigned int vLen, int vParam1, int vParam2, int vParam3, int vParam4 ) 
//	{
//		mEventID = vEventID;
//		mParam1 = vParam1;
//		mParam2 = vParam2;
//		mParam3 = vParam3;
//		mParam4 = vParam4;
//		memset( mStrBuffer, 0, sizeof( mStrBuffer ) );
//		memcpy( mStrBuffer, vStrBuffer, min( vLen, sizeof( mStrBuffer ) ) );
//	}
//};
//
//class CEventHandler
//{
//public:
//	static int OnEvent( CEvent vEvent );
//};
//



// -----------------------------------------------------------------------------

class CEvent;

// �¼��۲���
class CEventObserver
{
	virtual int OnEventTrigger( CEvent* pEvent ) = 0;
};

// -----------------------------------------------------------------------------

enum emEventTypeForOB
{
	OB_EVENT_LEVELUP	= 1,
};


class CEvent
{
public:
	
	int RegisterObserver( CEventObserver* pObserver );
	int NotifyObservers( );

	inline int GetType( ) { return mEventType; }

private:
	typedef lk::vector<unsigned int, 30> _ObserverList;
	_ObserverList mObservers;
	int mEventType;
};


// ��������¼�
class CEventLevelUp : public CEvent
{
	unsigned int mEntityID;
	unsigned int mOldLevel; // �ϵȼ�
};

// ��ҿ��ͼ
class CEventChangeMap : public CEvent
{

};