#ifndef _DBCTRL_HPP_
#define _DBCTRL_HPP_

#include "dbhandle.h"
#include "base_db.h"

#ifdef _ASYNC_SQL_
#include "asqlexe.h"
#endif

#define MAXPROXYNUMBER				10					//���game server ��Ŀ

#ifdef _DEBUG_
#define MAXHANDLENUMBER				2
#else
#define MAXHANDLENUMBER				8
#endif 


#define SECSOFONEHOUR				3600

#define CHECKINTERVAL				10					//���ʱ��������λ����
#define PROXYKEEPALIVESECONDS		(3*CHECKINTERVAL)	//��proxy��������ʱʱ��
#define MAXPROXYCODELEN				1024				//��proxy���ʹ���������鳤��
#define PERF_TIMER	60		// һ���Ӵ�ӡһ��ͳ����Ϣ  �Ժ������� ��λ����

typedef struct
{
    int   m_iServerID;
    TName m_szServiceIP;
    TName m_szServicePort;
} STGenSvrdCfg;


// �����ļ���Ϣ
struct STDBSvrdCfg
{
    int  m_iDBSvrID;
    char m_szServiceIP[32];
    char m_szServicePort[10];
    short m_sProxySvrdNum;
    short m_sDBOperMode;    // 1 cache ����ģʽ, 2 ֱ�Ӹ������ݿ�
    short m_sCheckPointInterval;
    short m_sPrintStatInterval;  //��ӡ��������Ϣ��ʱ����
    
    STGenSvrdCfg m_astProxySvrdCfg[MAXPROXYNUMBER];//proxy
	char m_szMysql[SQL_HOST_INFO_STRING];

	int mHandleLogLevel; // �߳���־�ȼ�
};


// ͳ����Ϣ
struct STServerStatisticInfo
{
	int m_iCtrlLoopNum;							//��ѭ������
	int m_iRecvMsgNum;							//�յ���Ϣ������
	int m_iRecvPkgSize;							//������Ϣ��size
	int m_iSendMsgNum;							//�·���Ϣ������
	int m_iSendPkgSize;							//�·���Ϣ��size
	int m_iRecvMsgNumTransByKey;				//�յ�trans_bykey��Ϣ����
	int m_iRecvMsgNumTransBroadCast;			//�յ�trans_broadcast��Ϣ����

	int m_iInsertNum;							//insert��������
	int m_iUpdateNum;							//update��������
	int m_iSelectNum;							//select��������
	int m_iDeleteNum;							//delete��������

	int m_iSyncInsertNum;						//ͬ��insert��������
	struct timeval m_tSyncInsertTime;			//ͬ��insertִ��ʱ��
	int m_iSyncUpdateNum;						//ͬ��update��������
	struct timeval m_tSyncUpdateTime;			//ͬ��updateִ��ʱ��
	int m_iSyncSelectNum;						//ͬ��select��������
	struct timeval m_tSyncSelectTime;			//ͬ��selectִ��ʱ��
	int m_iSyncDeleteNum;						//ͬ��delete��������
	struct timeval m_tSyncDeleteTime;			//ͬ��deleteִ��ʱ��

	int m_iDecodeProxyMsgFailedTimes;			//����ʧ�ܴ���
	int m_iEncodeProxyMsgFailedTimes;			//����ʧ�ܴ���
	int m_iGetCodeFailedTimes;					//����Ϣ�����л�ȡ��Ϣʧ�ܴ���
	int m_iPostCodeFailedTimes;					//�ύ��Ϣ����Ϣ������ʧ�ܴ���

	int m_iExecSqlAsyncFailedNum;				//�첽ִ��ʧ�ܴ���
	int m_iExecSqlAsyncSuccNum;					//�첽ִ�гɹ�����
	struct timeval m_tExecSqlAsyncSuccTime;		//�첽ִ�гɹ�ʱ�� 
};

class CSharedMem;


class CDBCtrl : public CSingleton< CDBCtrl >
{
public:
    CDBCtrl();
    ~CDBCtrl();

    int Initialize( );
    int PrepareToRun();
    int Run();

    const STDBSvrdCfg GetDBSvrConf();

    void* operator new(size_t nSize);
    void  operator delete( void* pMem);

    static int CountSize();
    static CSharedMem *mShmPtr;

	
	// ���б�־
	enum ERunFlag
	{
		EFLG_CTRL_NO		= 0x01,
		EFLG_CTRL_QUIT		= 0x02,
		EFLG_CTRL_RELOAD	= 0x04
	};

	void SetRunFlag( int iFlag );
	void ClearRunFlag( int iFlag);
	bool IsRunFlagSet( int iFlag );

#ifdef _POSIX_MT_
    static pthread_mutex_t stMutex;
#endif

private:
    int ReadDBSvrdCfg(const char *szCfgFile);
	int ReadDBIpCfg(const char *szIpFile);

    int CreateServer();
    int	ConnectToProxyServer();
    int RegisterToProxyServer(CTCPConn<RECVBUFLENGTH, POSTBUFLENGTH> *pstTcpConn);
    int SendkeepAliveToProxy(CTCPConn<RECVBUFLENGTH, POSTBUFLENGTH> *pstTcpConn);     //��proxy����������Ϣ
    int CheckRunFlags();
    int CheckAndDispatchInputMsg();
    int RoutineCheck();
    int DispatchOneCode(int iProxyIdx, int nCodeLength, BYTE* pbyCode);
    int PostInternalMsgToHandle(int iHandleID, CMessage *pMsg);
    int NotifyHandleClearComplete();

    int ProcessOneCode(char *pacCode, int shCodeLength);
	int Event(CMessage *pstMsg);
    int PrintServerStatistic();

private:
	
	int m_iRunFlag;	// ���б�־

    STDBSvrdCfg m_stDBSvrdCfg;

    CTCPConn<RECVBUFLENGTH, POSTBUFLENGTH> m_astProxySvrdCon[MAXPROXYNUMBER];

    CDBHandle* m_apHandles[MAXHANDLENUMBER];
    short m_sCheckPointHandle;

    time_t m_tLastPrintTime;

    time_t m_atLastPorxyKeepAliveTime[MAXPROXYNUMBER];    //����յ�proxy������Ϣʱ��

#ifdef _ASYNC_SQL_
    CASqlExe* m_apExecers[MAXHANDLENUMBER];
#endif

};

#endif

