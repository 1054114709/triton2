/******************************************************************************
   ��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

/******************************************************************************
  �ļ���          : tcpctrl.h
  �汾��          : 1.0
  ����            : �ź���
  ��������        : 2008-05-28
  ����޸�        : 
  ��������        : TCPServer����������ɺͿͻ��˵�ͨѶ����mainserver��ͨѶ���ͻ��˵ĳ�ʱ����Լ��ͻ��˵�
  �����б�        : 
  �޸���ʷ        : 
  1 ����          : 2008-05-28
    ����          : �ź���
    �޸�����      : ����
*******************************************************************************/
#ifndef __TCPCTRL_H__
#define __TCPCTRL_H__

#define MAX_ERRNO_NUM 10
#define READSTAT      0
#define WRITESTAT     1
    
typedef struct 
{
    int     m_iConnIncoming;
    int     m_iConnTotal;
	int		m_iPkgRecv;
	int		m_iPkgSend;
	int		m_iPkgSizeRecv;
	int		m_iPkgSizeSend;
}TTcpStat;


/*�ܵ���ʶ��*/
enum enLockIdx
{
    IDX_PIPELOCK_C2S = 0,
    IDX_PIPELOCK_S2C = 1,
    IDX_PIPELOCK_A2C = 2,
};

class    CSharedMem;
class    CCodeQueue;
class    CConfigFile;


int GetUinFromCode(BYTE* pCode, short nCodeLength);




class CTCPCtrl
{
public:
    CTCPCtrl();				/*���캯��*/
    ~CTCPCtrl();			/*��������*/
    int Initialize();		/*��ʼ��*/
    int PrepareToRun();
    void* operator new( size_t nSize);		/*���ص�new����*/
    void  operator delete(void *pBase);		/*���ص�delete����*/
    static CTCPCtrl* CreateTCPCtrl();		/*����CTCPCtrl�����ʵ��*/
    static int CountSize();					/*����CTCPCtrl����ռ�õĿռ�*/
    int  Run();								/*���Ⱥ���*/   
    int  SetRunFlag(int iRunFlag);
	void SetRunArgs( const char* pszArgs );
	char* GetRunArgs( );


private:        
    int  CreatePipe();                                             /*�����ڴ�ܵ�*/

    CCodeQueue  *CreatePipe(const char*szLockFile, char byPipeID, int iLockIdx); /*�����ڴ�ܵ�*/
 
    inline void ClearSocketInfo(short enError);                    /*���socket�ṹ��Ϣ*/
    int  CheckTimeOut();                                           /*���ͻ���socket�Ƿ�ʱ*/       
    int  GetExMessage();                                           /*�����ⲿ����*/
    int  RecvClientData(short nIndex);                             /*���տͻ��˷��͵�����*/
    int  CheckWaitSendData();                                      /*���gamesvrd�Ƿ���������Ҫ����*/
    int  SendClientData(BYTE* pbyInBuf, short nInLength);          /*����gamesvrd���ݸ�client*/        
    int  ReadCfgFile();
    int  ReloadCfgFile();
    int  TcpWrite(SOCKET iSocket, char *pBuf, int iPackLen);
    int  TcpRead(SOCKET iSocket, char *pBuf, int iLen);
    int  WriteTcpStat();
    int        InitEpollSocket(USHORT port);
    int        eph_init();
    int        eph_socket(int domain, int type, int protocol);    
    int        eph_new_conn(int sfd);
    int        eph_close(int sfd);
    int        eph_cleanup();    

	bool IsIgnoreIP( char* szIP );

private:
    static BYTE*        pCurrentShm;                      /*�ڴ���ָ��*/     
    CConfigFile         m_stConfigFile;
    TConfig             m_stConfig;                       /*������Ϣ*/
    int                 m_iRunFlag;
    time_t              m_iLastTime;                      /*�ϴμ�ⳬʱ��ʱ��*/
    time_t              m_iLastWriteStatTime;             /*�ϴμ�ⳬʱ��ʱ��*/
    time_t              m_iNowTime;                       /*��ǰʱ��*/
    TNetHead            m_stNetHead;                      /*NetHead�ṹ����gamesvrdͨѶ��*/
    struct  timeval     m_tvWait;                         /*�����¼���ʱ����*/ 
    SOCKET              m_iSocket;                        /*����socket*/        
    struct sockaddr_in  m_stSockAddr;                     /*�����ַ*/
    TSocketInfo         *m_pstSocketInfo[MAX_SOCKET_NUM];	/*socket�ṹ���飬���ڼ�¼�ͻ��˵���Ϣ*/        
    TSocketInfo         *m_pSocketInfo;                   /*��ǰ��socket�ṹָ��*/ 

    CSharedMem          *m_pShmCSPipe;                    /*�����ڴ�client   ���� gamesvrd*/
    CSharedMem          *m_pShmSCPipe;                    /*�����ڴ�gamesvrd ���� client*/

    CCodeQueue          *m_pC2SPipe;                      /*�������*/ 
    CCodeQueue          *m_pS2CPipe;                      /*�������*/

    char                m_szCSPipeFile[500];              /*�����ļ�*/ 
    char                m_szSCPipeFile[500];              /*�����ļ�*/ 

    char                m_szMsgBuf[MAX_BUF_LEN];        /*��Ϣ������(�Ӵ���Ϊ�˷�ֹgame��������Ϣ����)*/ 
    int                 timeout;
    TTcpStat            m_stTcpStat;
    int                 m_iWriteStatCount;
    char                m_szWriteStatBuf[1024];
    struct epoll_event  *events;
    int                 kdpfd;
    int                 maxfds;                
    struct epoll_event  m_stEpollEvent;
	char				m_szRunArgs[100];
};

#endif /* __RCCTRL_H__ */

