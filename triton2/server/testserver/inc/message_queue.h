/******************************************************************************
	��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

 ******************************************************************************
	�ļ���		: message_queue.h
	�汾��		: 1.0
	����		: ZHL
	��������: 2008-08-10
	����޸�: 
	��������		: ��Ϣ���У�ͳһ�������Կͻ��˺ͷ���������Ϣ
	�����б�		: 
	�޸���ʷ		: 
		1 ����		: 2008-08-10
		����		: ZHL
		�޸�����	: ����
*******************************************************************************/

#pragma once

#include "network.h"
#include "servertool.h"
#include "lk_queue.h"

class CCodeQueue;
class CSharedMem;



class CMessageQueue : public CSingleton<CMessageQueue>
{
public:

	//MsgQueue����ֵ
	enum EMsgQueueResult
	{
		Success			=  0, //�ɹ�
		Err_QueueFull	= -1, //������ 
		Err_QueueEmpty	= -2, //���п�
		Err_UnKnown		= -5, //δ֪����
		Err_System		= -6, //ϵͳ����
		Err_Param		= -7, //��������
		Err_Decode		= -8, //�������
	};

	//MsgQueue����
	enum 
	{
		MSG_AVG_SIZE	= 200,		// Messageƽ����С
		MSG_CAPABILITY	= 16000,	// Queue��Message����
		MSG_QUEUE_LEN =  MSG_AVG_SIZE * MSG_CAPABILITY,
	};

public:
	CMessageQueue( );
	~CMessageQueue( );

	void* operator new( size_t nSize );
	void  operator delete( void *pMem );


	/**
	** ��ʼ��
	*/
	int Initialize( );
	int Resume( );


	/**
	** ��Ϣ�����Ƿ����� 
	*/
	bool IsQueueFull()	/*{ return mCurrentMsgNum == MSG_CAPABILITY; }*/
	{
		return mMsgQueue.size() == MSG_CAPABILITY ;
	}

	/**
	** ��Ϣ�����Ƿ�Ϊ��
	*/
	bool ISQueueEmpty() /*{ return mCurrentMsgNum == 0; }*/
	{
		return mMsgQueue.empty();
	}
	/**
	** ����Ϣ������ѹ��һ����Ϣͷ��һ�δ����ȵ���Ϣ�� 
	*/
	int Push( CMessage* vMessage );
	int Push( CMessage* pMsg, void* pPara, int usParaLen );

	/**
	** ����Ϣ�����е���һ��������Ϣ
	*/
	int Pop( BYTE* vBuff, int& vBuffLen );
	int Pop( CMessage& rMsg );

	static CSharedMem* mShmPtr;
	static unsigned int CountSize();
private:

	typedef lk::queue< CMessage, MSG_CAPABILITY > MsgQueue;

	MsgQueue mMsgQueue;
	CCodeQueue* mMsgArea;
	unsigned int mCurrentMsgNum;
};
