#ifndef _PROXY_CONN_H_
#define _PROXY_CONN_H_
#include "tcp_conn.h"
#include "code_queue.h"
#include "servertool.h"
typedef CTCPSocket<RECVBUFLENGTH, POSTBUFLENGTH> CMyTCPSocket;

/*
enum eConnEntityTypes
{
	cet_gamesvr = 0,
	cet_dbsvr,
	cet_other,
	cet_proxy
};
*/

enum enConnFlags
{   
	FLG_CONN_IGNORE = 0,
	FLG_CONN_REDO   = 1,
	FLG_CONN_CTRL   = 2                                                                                           
};  

enum enEntityStates 
{
	ENTITY_OFF		= 0, 
	ENTITY_ON		= 1	
};

enum enBlockStates
{
	BLK_EMPTY    = 0,
	BLK_SAVING   = 1,
	BLK_REDOING  = 2
};  
    
class CMyTCPConn: public CTCPConn<RECVBUFLENGTH, POSTBUFLENGTH>
{
	public:
		CMyTCPConn() {}
		~CMyTCPConn() {}

		enum enConnParas
		{
#ifdef _DEBUG_
			BLOCKQUEUESIZE = 0x2000,
#else
			BLOCKQUEUESIZE = 0x1000000,
#endif
		};

		int EstConn( int iAcceptFD );
		int IsConnCanRecv();

		int RegToCheckSet( fd_set *pCheckSet );
		int IsFDSetted( fd_set *pCheckSet );
		int RecvAllData();
		int GetOneCode( unsigned short &nCodeLength, BYTE *pCode  );
		int SendCode(unsigned short nCodeLength, BYTE *pCode, int iFlag = FLG_CONN_IGNORE);
		int CleanBlockQueue(int iQueueLength);
		int SetConnState(int iConnState);
		int GetConnState();

	private:
		int m_iConnState;

		CCodeQueue *m_pBlockQueue;
		CCodeQueue *m_pRedoQueue;
		int m_iCurrentDumpSeq;
		int m_iCurrentRedoSeq;

		int m_iBlockStatus;

#ifdef _POSIX_MT_
		pthread_mutex_t m_stMutex;          //�����Ļ������
#endif
};

// socket���ӵļ���(��Ҫ���ڹ������е���Ϸ���������)
template < int MAX_CONN_NUM >
class CProxyConnSet
{
public:
	CProxyConnSet()
	{
		mActiveConnNum = 0;
	}
	~CProxyConnSet(){ }
public:
	CMyTCPConn *GetTcpConn(){ return mTcpConn; }	// ��ȡsocketָ��
	int	GetMaxConnNum(){ return MAX_CONN_NUM;  }	// ��ȡ����socket����

	int GetActiveConnNum(){ return mActiveConnNum; }	
	void SetActiveConnNum( int nNum ){ mActiveConnNum = nNum; }

	int Initialize( );		// ��ʼ������	
	CMyTCPConn* GetFreeTcpConn();	// ��ȡһ�����е�socket
	int UnRegistTcpConnByEntityID( int nEntityID );	// ע����һ�����õ�socket
	int UnRegistTcpConnBySocketID( int nFd );	// ע����һ�����õ�socket
	CMyTCPConn* Accept( int nEntityType, int nFd, u_long nIp, u_short nPort );	// ����һ���µ�socket����
	CMyTCPConn* ServerRegiste( u_long nIp, u_short nPort, int nGameID );		// ע��һ��������
	CMyTCPConn* GetTcpConnByIPAddr( u_long nIp, u_short nPort );	// ���ݵ�ַ��Ϣ��ȡsocket����
	CMyTCPConn* GetTcpConnByEntityID( int nEntityID );		// ����nEntityID��ȡsocket����
	CMyTCPConn& operator []( int nIndex );
private:
	int mActiveConnNum;								// ��Ծ�Ĵ�������״̬��socket����
	CMyTCPConn mTcpConn[MAX_CONN_NUM];				// socket
};
#include "proxyconnset.cpp"
#endif