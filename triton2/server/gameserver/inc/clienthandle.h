#pragma once

//#define CRYPTKEYLENGTH		32
#define LOGOUT				(-100)
#define TNetHeadSize     sizeof(TNetHead)   /*TNetHead��С*/

typedef unsigned char BYTE;


class CEntityPlayer;

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

public:
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
	CLIENTHANDLE_WRONG_SOCKSTATE,		// ���socket״̬����ȷ
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

public:

	CClientHandle();
	~CClientHandle();


	void* operator new(size_t size);
	void  operator delete(void* pointer);

	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* pointer, const char* file, int line);

public:

	CCodeQueue* mC2SPipe;	// tcpserver	--> gameserver
	CCodeQueue* mS2CPipe;	// gameserver	--> tcpserver
	
	static CSharedMem* mShmPtr; // �����ڴ�ָ��
	

	int Initialize( );
	int Resume( );

	// ����ԭʼ��Ϣ���ض��ͻ���
	int Send(CMessage* pMsg, std::vector<CEntityPlayer*>* pPlayerSet);
	
	//************************************
	// Method:    Send
	// FullName:  CClientHandle::Send
	// Access:    public 
	// Returns:   int 0 �ɹ��� !0 ʧ��
	// Qualifier: �������л������Ϣ2���Ƹ�������� �������л������Ϣ2���Ƹ��������
	//				�ú�����Ҫ��Ϊ���������ܣ���ȥ��װvector�ĳɱ������л�һ�Σ����Ͷ�Ρ�
	// Parameter: CEntityPlayer * pPlayer  ���
	// Parameter: BYTE * pMessageBuff	���л������Ϣ2����
	// Parameter: int nLen				���л����2���Ƴ���
	// Parameter: CMessage * pMsg		ԭʼ��Ϣ����Ҫ��Ϊ����Send�ڲ���¼��־����ӡ��Ϣ����, ͳ����ϢID) 
	//************************************
	int Send(CEntityPlayer* pPlayer, BYTE* pMessageBuff, int nLen, CMessage* pMsg );
	
	int Recv();

	/**
	** ����Ϣ���а汾
	*/
	//int DecodeNetMsg( BYTE* pCodeBuff, int& vLen, CCSHead* pCSHead, CMessage* pMsg, BYTE* pMsgPara, unsigned short& usParaLen);
	
	/**
	** ������Ϣ���а汾
	*/
	int DecodeNetMsg( BYTE* pCodeBuff, int& nLen, CCSHead* pCSHead, CMessage* pMsg );

	// ��ӡ����
	void Dump(char* pBuffer, unsigned int& unLen );

	static unsigned int CountSize();

private:
	enum { MAX_EMULATOR_MSG_BUF = 60000 };
	static char msMessageBuff[ MAX_EMULATOR_MSG_BUF ];
};

