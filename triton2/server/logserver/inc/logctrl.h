#ifndef _LOGCTRL_HPP_
#define _LOGCTRL_HPP_

#include "loghandle.h"
#include "base_log.h"
#include "lk_string.h"
#include "lk_hashmap.h"
#include "log_msg_pb.hxx.pb.h"
#include "template.h"

#define MAXPROXYNUMBER				10					//���game server ��Ŀ
#define MAXHANDLENUMBER				(CLogHandle::HANDLECOUNT)
#define SECSOFONEHOUR				3600

#define CHECKINTERVAL				10					//���ʱ��������λ����
#define PROXYKEEPALIVESECONDS		(3*CHECKINTERVAL)	//��proxy��������ʱʱ��
#define MAXPROXYCODELEN				1024				//��proxy���ʹ���������鳤��

typedef struct
{
    int   m_iServerID;
    TName m_szServiceIP;
    TName m_szServicePort;
} STGenSvrdCfg;


// �����ļ���Ϣ
struct STLogSvrdCfg
{
    int  m_iLogSvrID;
    char m_szServiceIP[32];
    char m_szServicePort[10];
    short m_sProxySvrdNum;
    short m_sLogOperMode;    // 1 cache ����ģʽ, 2 ֱ�Ӹ������ݿ�
    short m_sCheckPointInterval;
    short m_sPrintStatInterval;  //��ӡ��������Ϣ��ʱ����
    
    STGenSvrdCfg m_astProxySvrdCfg[MAXPROXYNUMBER];//proxy
	char m_szMysql[SQL_HOST_INFO_STRING];	// ����mysql������Ϣ
	char m_szRemoteStorage[SQL_HOST_INFO_STRING]; // Զ�̴洢mysql������Ϣ

	int mHandleLogLevel; // �߳���־�ȼ�
	int mMonitorTimer;	 // ����������
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


class CLogCtrl : public CSingleton< CLogCtrl >
{
public:
    CLogCtrl();
    ~CLogCtrl();

    int Initialize( );
    int PrepareToRun();
    int Run();

    const STLogSvrdCfg GetLogSvrConf();

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
    int ReadLogSvrdCfg(const char *szCfgFile);
	int ReadLogIpCfg(const char *szIpFile);

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
	int PrintStatistic();
	void LoadToken2String();
	void LoadCatalogDetail();

	int CreateLogDB( time_t time );
private:
	
	int m_iRunFlag;	// ���б�־

    STLogSvrdCfg m_stLogSvrdCfg;

    CTCPConn<RECVBUFLENGTH, POSTBUFLENGTH> m_astProxySvrdCon[MAXPROXYNUMBER];

    CLogHandle* m_apHandles[MAXHANDLENUMBER];
    short m_sCheckPointHandle;

    time_t m_tLastPrintTime;
	// ͳ����Ϣ
	enum
	{
		BASE_LOGMSG_ID = ID_S2L_LOGMESSAGE,
		MAX_LOGMSG_TYPE = 32,
	};
	CLogStat m_tLogStat[MAX_LOGMSG_TYPE];

    time_t m_atLastPorxyKeepAliveTime[MAXPROXYNUMBER];		//����յ�proxy������Ϣʱ��

	// TODO: ��ʱͳһ��¼ʱ��,�Ժ������þ���ÿ���¼��ļ�¼ʱ��
	time_t m_tLastSaveDataTime;								// ���һ�μ�¼handle���¼����ݵ��¼�

	typedef lk::string<256> CString256;
	typedef std::map<lk::CString32, CString256 > CTOKEN2STRING;

	CTOKEN2STRING mToken2String;
	//typedef std::map <int, std::pair<int, lk::CString32> > ID2TABLE;
	typedef struct 
	{
		int first;		// number
		lk::CString32 second;	//table name
		int handle;
	}IDINFO;

	//typedef std::map <int, std::pair<int, lk::CString32> > ID2TABLE;
	typedef lk::hash_map <int, IDINFO, 100> ID2TABLE;

	ID2TABLE m_Id2Table;

public:
	// ͳ����Ҫ��ID,�Լ���������
	typedef struct
	{
		unsigned int id;	// ��ĿID
		char table_id; 		// д��ı�ID
		int  value_type;	// ֵ����, ������Ʒ����ƷID
		char action_type;	// ��������	
		char entity_type;	// ��������	
	}CATALOG_INFO;

	typedef  lk::hash_map<unsigned int, int, 5000> ACTION2CATALOG;
	typedef  lk::hash_map<unsigned int, CATALOG_INFO, 2000> CATALOGDICT;
	typedef  lk::hash_map<int, int , 256> ITEMACTIONGROUP;

	int OnTime( );

	bool EvtTimeOut( time_t tCurTime );

	const char* GetTableName(int id)
	{
		ID2TABLE::const_iterator iter = m_Id2Table.find(id);
		return iter != m_Id2Table.end() ? (iter->second).second.c_str() : NULL;
	}

	const char* Token2String(const char* szToken)
	{
		if ( szToken[0] != '#') return szToken;

		CTOKEN2STRING::iterator iter = mToken2String.find(lk::CString32(&szToken[1]));
		return (iter == mToken2String.end() ? szToken : iter->second.c_str());
	}

	int  GetTableCount( int id)
	{
		ID2TABLE::const_iterator iter = m_Id2Table.find(id);
		return iter != m_Id2Table.end() ? (iter->second).first : 0;
	}

	int* Act2Catalog(int Key)
	{
		ACTION2CATALOG::iterator iter = m_Action2Catalog.find(Key);
		if (iter != m_Action2Catalog.end())	
		{
			return &(iter->second);
		}

		return NULL;
	}

	CATALOG_INFO* GetCatalog(int Key)
	{
		CATALOGDICT::iterator iter = m_CatalogDict.find(Key);
		if (iter != m_CatalogDict.end())	
		{
			return &(iter->second);
		}

		return NULL;
	}

	int ItemLife(int nCatalogType, int emAction)
	{
		int key = (nCatalogType << 8) + emAction;
		ITEMACTIONGROUP::iterator iter = m_Life.find(key);
		if ( iter != m_Life.end())
		{
			return iter->second;
		}

		return -1;
	}

	int CatalogID(int nCatalogType, int nEntityType, int nActionType, int nValueType);

	typedef  lk::hash_map<unsigned int, int, 5000> TExpExceptDict;
	typedef  lk::hash_map<unsigned int, int, 500> TItemFilterDict;
	bool IsExpLimited(int nExpType, int nExpValue)
	{
		int nLimit = 0;
		switch(nExpType) 
		{
			case EM_UPGRADE_ROLE_EXP:
			{
				nLimit = m_nMinRoleExp;
				break;
			}

			case EM_UPGRADE_TALENT_EXP:
			{
				nLimit = m_nMinTalentExp;
				break;
			}

			case EM_UPGRADE_MW_EXP:
			{
				nLimit = m_nMinMWExp;
				break;
			}
		}

		return nExpValue < nLimit;
	}

	bool IsExcept(int nRoleID)
	{
		return m_ExpExceptRole.find(nRoleID) != m_ExpExceptRole.end();
	}

	bool AddFilterItem(int nItemID, int nOptype)
	{
		return m_ItemFilter.insert(TItemFilterDict::value_type((nOptype << 24) + nItemID, 0)).second; 
	}

	bool AddFilterDrop(int nItemID)
	{
		return m_DropFilter.insert(TItemFilterDict::value_type(nItemID, 0)).second; 
	}

	bool IsFilterDrop(int nItemID)
	{
		return m_DropFilter.find((nItemID)) != m_DropFilter.end();
	}

	bool IsFilterItem(int nItemID, int nOptype)
	{
		return m_ItemFilter.find((nOptype << 24) + nItemID)  != m_ItemFilter.end();
	}

private:
	ACTION2CATALOG m_Action2Catalog;
	CATALOGDICT m_CatalogDict;

	ITEMACTIONGROUP m_Life;

	// for exp limit
	TExpExceptDict m_ExpExceptRole;
	TItemFilterDict m_ItemFilter;
	TItemFilterDict m_DropFilter;

	int m_nMinMWExp;
	int m_nMinRoleExp;
	int m_nMinTalentExp;
};

#endif

