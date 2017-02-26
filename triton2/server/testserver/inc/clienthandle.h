#pragma once

#include <shm.h>
#include "lk_hashmap.h"
#include "entity.h"

using namespace lk;

//#define CRYPTKEYLENGTH		32
#define LOGOUT				(-100)
#define TNetHeadSize     sizeof(TNetHead)   /*TNetHead��С*/

typedef unsigned char BYTE;


// ����ͷ �����ں�tcpserverͨѶ��
class CNetHead
{
public:

	unsigned int	mSrcIP;	
	unsigned short	mSrcPort;
	unsigned int	mDstIP;
	unsigned short	mDstPort;
	time_t			mStamp;
	char			mState; // ״̬�� < 0 ˵���ر���socket


	CNetHead( ) : mSrcIP(0), mSrcPort(0), mDstIP(0), mDstPort(0),  mStamp(0), mState(0) {}
	~CNetHead() {}

};


// �ܵ���ʶ��
enum enLockIdx
{
	IDX_PIPELOCK_C2S = 0,
	IDX_PIPELOCK_S2C = 1,
	IDX_PIPELOCK_A2C = 2,
};


// �ͻ�������״̬
enum enClientState
{
	CLIENT_NOTCONNECT = 0,
	CLIENT_ONLINE,
	CLIENT_OFFLINE
};


//// �ͻ���������Ϣ
//class CClientInfo
//{
//public:
//	unsigned int			mUin;					//�ʺ�ID
//	unsigned int 			mClientAddr;			//�ͻ��˵������ַ
//	unsigned short 			mClientPort;			//�ͻ��˵Ķ˿ں�
//	unsigned int 			mSockTime;				//�ͻ��˵������ַ
//	unsigned short 			mSockIndex;				//�ͻ��˵Ķ˿ں�
//	int 					mNetSpeed;				//�������
//	short 					mVer;					//C-SЭ��汾��
//	unsigned char 			mKey[CRYPTKEYLENGTH];	//����ʹ�õ�Key
//	char 					mFlag;					//�ͻ���״̬��0 - δ���ӣ�1 - ���ߣ� 2 - ����
//	time_t					m_tLastActiveTime;		// ����Ծʱ��
//};


// ������
enum ClientHandleErrCode
{
	CLIENTHANDLE_SUCCESS = 0,
	CLIENTHANDLE_INVALID_PARA,			// ��������
	CLIENTHANDLE_QUEUE_FULL,			// ������
	CLIENTHANDLE_QUEUE_EMPTY,			// ���п�
	CLIENTHANDLE_CODE_NOTINTEGRITY,		// ���ݲ�����
	CLIENTHANDLE_DECODE_FAILED,			// ����ʧ��
	CLIENTHANDLE_ENCODE_FAILED,			// ����ʧ��
	CLIENTHANDLE_QUEUE_CRASH,			// �����ڲ�����
	CLIENTHANDLE_EVIL_PKG,				// �Ƿ������
};

// ��ǰ������
class CCSHead;
class CMessage;
class CCodeQueue;
class CSharedMem;

// �����������
class CClientHandle 
{
	//�ܵ���С
	enum {MAX_PIPE_SIZE = 0x1000000};
	typedef void ( *OnMessageProc )( int vCommHandle, CMessage* pMessage );

public:

	CClientHandle();
	~CClientHandle();


	void* operator new(size_t size);
	void  operator delete(void* pointer);

public:

	CCodeQueue* mC2SPipe;	// tcpserver	--> gameserver
	CCodeQueue* mS2CPipe;	// gameserver	--> tcpserver
	
	static CSharedMem* mShmPtr; // �����ڴ�ָ��
	

	int Initialize( );
	int Resume( );

	int Send(CMessage* pMsg, CCertifyPlayer* pPlayers);
	int Recv();

	int DecodeNetMsg( BYTE* pCodeBuff, int& vLen, CCSHead* pCSHead, 
			CMessage* pMsg, BYTE* pMsgPara, int& usParaLen, CNetHead& tNetHead);

	int EncodeNetMsg( CMessage* pMsg, BYTE* pCodeBuff, int& vLen, CCertifyPlayer* ppPlayer);

	static unsigned int CountSize();
public:

	enum 
	{
		MAX_CLIENT_NUM = 0x7ff0,	// ���������
	};
	
	//typedef lk::hash_map<int, CClientInfo, MAX_CLIENT_NUM> ClientCommHash;

	//ClientCommHash mClientCommHash;
};

