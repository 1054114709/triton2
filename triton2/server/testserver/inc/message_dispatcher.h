#ifndef _MESSAGE_DISPATCH_H_ 
#define _MESSAGE_DISPATCH_H_ 


#include "servertool.h"


class CMessage;


class CMessageDispatcher : public CSingleton< CMessageDispatcher >
{
public:

	CMessageDispatcher( );
	~CMessageDispatcher( );

	/**
	** ����Ϣ�������һ����Ϣ
	*/
	int AppendMsg( CMessage* vMessage );

	int AppendMsg( CMessage* pMsg, void* pPara, unsigned short usParaLen );

	/**
	** ���ⲿʵ�巢����Ϣ
	*/
	int PostMessage(/*CMsgHead* pMsgHead, short shMsgParaLength, const BYTE* pMsgPara,BYTE opt = ST_CLIENT_ONLINE*/);

	/**
	** ����Ϣ������ȡ����Ϣ�����ɷ� 
	*/
	enum {MAX_MSG_DISPACH_ONCE = 3000};//�����ɷ��������Ϣ�� 
	int DispachMsg(int iCount = MAX_MSG_DISPACH_ONCE);


	enum ENMDispacherResult
	{	
		Success				= 0,  //�ɹ�	
		Err_MsgQueueFull	= -1, //��Ϣ������ 
		Err_PushMsg			= -2, //ѹ����Ϣ����
		Err_Para			= -3, //��������
	};

private:

	/**
	** ����������Ϣ
	*/
	int ProcessMessage(CMessage* pMsg);

	int ProcessDataMsg( CMessage* pMsg );
	int ProcessRouterMsg( CMessage* pMsg );
	int ProcessClientMsg( CMessage* pMsg );
};

#endif
