#ifndef _PROXY_CTRL_HPP_
#define _PROXY_CTRL_HPP_

#include "proxy_handle.h"
#include "proxy_conn.h"

//���¶����������б�־
#define FLG_CTRL_QUIT			((BYTE)0x01)	//֪ͨ���ض����˳�
#define FLG_CTRL_RELOAD			((BYTE)0x02)	//�ض�����

#define MAX_TMP_BUF_LEN                               1024           //ע����Ϣ��󳤶�
#define MAX_UNREGISTER_NUM                      100             //��ǰδע���������

#define CHECK_INTERVAL_SECONDS              10             //���ʱ����
#define CHECK_TIMEOUT_SECONDS                 30            //����δע��ĳ�ʱʱ��
#define GLOBALPROXY_ALIVE_TIME 1000

//��ǰ�����ϣ�����δע��ṹ��Ϣ
struct STUnRegisterSocketInfo
{
	int m_iSocketFD;                    //�����׽ӿ�
	u_long m_ulIPAddr;                  //����ip��ַ
	time_t  m_tAcceptTime;              //���ӷ���ʱ��
};

class CProxyCtrl
{
public:
	CProxyCtrl();
	~CProxyCtrl();


	enum _enParas
	{
		MAX_MUTEX_NUM		= 2,
		MUTEX_HASHMAP		= 0,
		MUTEX_ROUTETAB		= 1
	};
	

	int Initialize(const char *szCfgFile);
	int PrepareToRun();
	int Run();


#ifdef _POSIX_MT_
	static pthread_mutex_t stMutex[MAX_MUTEX_NUM];
#endif
	

protected:

private:

	int ReadCfg(const char *szCfgFile);
	int PrintStatistic( );

	//int LoadConnInfoFromFile(short nConnType, CMyTCPConn* pConns, int& iConnNum);
	//int LoadHashMapFromFile();
	//int LoadMRTFromFile();

	// �����ȫ�ִ��������������״̬(���������ȫ�ַ�����������û�������ϵĻ�����ͣ����)
	int CheckGloalProxyStatus();
	bool Regist2GlobalProxy();
	int KeepAliveToGlobalProxy();
	int CheckTimer( );
	int CheckAliveTime( unsigned int nTime );

	int CheckRunFlags();
	int CheckConnRequest();
	int CheckRoutines();       //��ʱ���
	CMyTCPConn* GetConnByAddrAndID(short shSrcFE, short shSrcID, u_long ulSrcAddr, int nGameID );

	int ReceiveAndProcessRegister(int iUnRegisterIdx);  //���ղ�����ע����Ϣ
	int DeleteOneUnRegister(int iUnRegisterIdx);    //ɾ��һ��δע�������
	

	void  pbmsg_setproxy(CProxyHead* pProxy, unsigned int nSrcFE, unsigned int nDstFE, unsigned int nSrcID, 
		unsigned int nDstID, EMTransType emTransTp = TRANS_P2P, EMProxyCmd emProxyCmd = CMD_NULL, 
		unsigned char* szOption = NULL, unsigned int nOptlen = 0);

	TProxyCfg m_stProxyCfg;
	CMyTCPSocket m_stListenSocket;					// (ȫ�ֺ���Ϸ��������������õ�socket)

	//CMyTCPConn m_astMainConn[MAX_GAME_SERVER];
	CMyTCPConn* m_pstMainConn;
	//CMyTCPConn m_astDBConn[MAX_DB_SERVER];
	CMyTCPConn* m_pstDBConn;
	//CMyTCPConn m_astOtherConn[MAX_OTHER_SERVER];	
	CMyTCPConn* m_pstOtherConn;
	
	CMyTCPConn m_astGlobalProxy;					// ����ȫ�ַ�������

	CProxySet	 m_astProxyConn;	// ���������
	//CMyTCPConn m_astDunGeon[MAX_DUNGEON_NUM];	// ȫ�ָ���������
	CMyTCPConn* m_pstDunGeon;
	

	CProxyHandle* m_pMainHandle;
	CProxyHandle* m_pDBHandle;
	CProxyHandle* m_pOtherHandle;
	CProxyHandle *m_pProxyHandle;	// ���������
	CProxyHandle* m_pDungeonHandle;					// ȫ����Ϸ������
	CProxyHandle* m_pGlobalProxy;					// ȫ�ִ��������
	

	///����proxy��������֤����
	///֮ǰΪ����ip���ָ���Ϊid��ip��ͬ��֤
	int m_iCurrentUnRegisterNum;
	STUnRegisterSocketInfo m_astUnRegisterInfo[MAX_UNREGISTER_NUM];               //���δע��ṹ
	time_t m_tLastCheckTime;
	unsigned int mLastTickCount;
	int mAliveTimer;
};

#endif
