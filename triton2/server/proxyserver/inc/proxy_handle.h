#ifndef _PROXY_HANDLE_HPP_
#define _PROXY_HANDLE_HPP_

#include "thread.h"
#include "proxy_conn.h"
#include "servermessage_in.h"
#include "proxymessage_pb.hxx.pb.h"

#define PROXY_RESERVE               ((BYTE)0x01)
#define PROXY_CMD                   ((BYTE)0x02)

#define MAX_GAME_SERVER 18
#define MAX_DB_SERVER 2 
#define MAX_OTHER_SERVER 4
#define MAX_PROXY_NUM	20		// ���Ĵ������������
#define MAX_DUNGEON_NUM 2

#define MAXHASHMAPITEMNUMBER		512
#define MAXCLEANBLOCKCODES			512

typedef CProxyConnSet<MAX_PROXY_NUM> CProxySet;

inline int MaxServer(short CET_TYPE)
{
	switch (CET_TYPE)
	{
		case CET_GAMESERVER:
			return MAX_GAME_SERVER;
		case CET_DBSERVER:
			return MAX_DB_SERVER;
		case CET_OTHERSERVER:
			return MAX_OTHER_SERVER;
		case CET_DUNGEON:
			return MAX_DUNGEON_NUM;			
		default:
			return -1;
	}

	return -1;
}

typedef struct
{
	short m_nPrevSvrID;
	short m_nCurrentSvrID;
} THashMapItem;

typedef struct
{
	int   m_iProxyID;
	int   m_iProxyPort;
	int   m_iDBSvrNum;
	int   m_iMainSvrNum;
	int   m_iOtherEntityNum;
	int	  m_nProxyNum;			// �������������
	int	  m_nDungeonNum;		// ȫ����Ϸ����������
	int	  m_nFlag;				// �Ƿ�ȫ�ִ��������
	int	  m_nGameID;			// ��ϷID	
	TFName m_szMainSvrsFile;
	TFName m_szDBSvrsFile;
	TFName m_szOthEnsFile;
	TFName m_szMapFile;					//HashKey --> DB Server��ӳ���ļ�
	THashMapItem m_astHashMapTable[MAXHASHMAPITEMNUMBER];	//Key -> DB ӳ���	
	TFName m_szMRTFile;
	char m_sGlobalProxyAddr[64];		// ȫ�ִ����������ip��ַ
	//short  m_anMRT[MAXSVRNUMBER];

} TProxyCfg;


// ͳ�Ʒ���
struct STProxyStat
{
	int m_nTransferCodeNum;
	int m_nTransferCodeLength;
};


class CProxyHandle : public CThread
{
	public:
		CProxyHandle();
		~CProxyHandle();

		int Initialize(int iHandleType, 
				CMyTCPConn* pMainConn, 
				CMyTCPConn* pDBConn, 
				CMyTCPConn* pOtherConn, 
				CProxySet *pProxyHandle,
				CMyTCPConn*  pDunGeonHandle,
				CMyTCPConn*  pGlobalProxy,
				TProxyCfg *pstCfg
				);

		virtual int PrepareToRun() ;
		virtual int Run() ;
		virtual int IsToBeBlocked();

		STProxyStat& GetProxyStat( );

	private:

		int CheckInputCodes();
		int DoTransfer();
		int TransferOneCode( unsigned short nCodeLength, BYTE* pbyCode );

		int SendOneCodeTo( unsigned short nCodeLength, BYTE* pbyCode, short nDstFE, short nDstID, BYTE byOpFlag = 0, int nSrcGameID = 0, int nDesGameID = 0 );
		int BroadCastOneCode( unsigned short nCodeLength, BYTE* pbyCode, short nDstFE );
		int SendOneCodeByKey( unsigned short nCodeLength, BYTE* pbyCode, short nDstFE, u_int uiKey, BYTE byOpFlag = 0, int nSrcGameID = 0, int nDesGameID = 0 );


		short GetDstDBIDByKey(u_int uiKey);
		//short GetTargetMIDByRT(short nDstID);

		CMyTCPConn* GetDstTCPConn( CProxyHead* pTransHead );

		int ModifyHashMap(short nEntityID, int iModifyCount, BYTE *pbyKeys);
		int SaveHashMapToFile();

		int CheckBlockCodes();
		timeval m_tvLastCheck;


		int m_iHandleType;

		TProxyCfg *m_pstCfg;
		//short m_nMainCount;
		//short m_nDBCount;
		//short m_nOtherCount;

		CMyTCPConn* m_pMainConn;
		CMyTCPConn* m_pDBConn;
		CMyTCPConn* m_pOtherConn;
		CMyTCPConn* m_pReadConn;
		CProxySet* m_pProxyConn;	// ���������
		CMyTCPConn *m_pDungeonConn;		// ȫ�ָ���������
		CMyTCPConn* m_pGlobalProxy;	// ȫ�ִ��������
		

		int m_nReadCount; 

		// �����Ż����� 
		time_t  m_tLastCheckTime;
		void PrintBinT(char * pBuffer, int iLength);

		STProxyStat m_stStat;
};

#endif
