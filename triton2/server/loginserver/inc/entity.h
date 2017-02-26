#ifndef _LOGIN_ENTITY_H_
#define _LOGIN_ENTITY_H_

#include "servertool.h"
#include "coretype.h"
#include "object.h"
#include "log.h"
#include "lk_string.h"
#include "dbinterface.h"

#ifdef USING_ERATING
#include "SysProtocol.h"

enum em_connect_erating_flag
{
	em_connect = 0,
	em_reconnect = 1
};

#endif

// ********************************************************************** //
// CLoginPlayer
// ********************************************************************** //

class CLoginPlayer: public CObj
{
public:
#ifdef YUENAN
	enum 
	{
		USER_NAME_LEN = 50, 
		USER_PASSWD_LEN = 32,
		USER_PASSWD_DBLEN = 32,
	};
#else
	enum 
	{
		USER_NAME_LEN = 32, 
		USER_PASSWD_LEN = 128,
		USER_PASSWD_DBLEN = 32,
	};
#endif

	int		mLoginToken;	// ��½����
	int		mCommHandle;	// ͨѶ�˿�
	int		mAccountID;		// �˺���Ϣ
	int 	mClientAddr; 	// �ͻ���IP
	time_t 	mSockTime;   	// sock�Ĵ���ʱ��
	int 	mClientPort; 	// �ͻ��˶˿ں�
	time_t	mActiveTime;	// �����󼤻�ʱ��
	bool 	mVerifiedByERating; // �Ƿ񾭹���ERating��֤
	
	char	mUserName[USER_NAME_LEN+1]; 	//����ʺ�����
	char 	mUserPasswd[USER_PASSWD_LEN+1];	//�������	

	int 	m_nMatrixType; 	// �ܱ�����
	char 	m_szMatrixCode[USER_PASSWD_LEN+1]; // �ܱ�
	char	m_szMatrixCoord[USER_PASSWD_LEN+1];// �ܱ�����
	char 	m_szMac[USER_NAME_LEN];	// MAC��ַ
	
	uint8_t mAdultFlag; 	// ���˱�־
	uint8_t mUserClass; 	// VIP �ȼ�
	int32_t mUserPoint;		// ��һ���
	uint32_t mUserFlag; 	// ������־
	uint32_t mUrlID; 		// ���������صĿͻ���

	int		mStatus;		// �û�״̬ ����GM��

	int    m_nGameID;		// ���������û�

	unsigned int 	m_nDiskID;		// �������к�
	unsigned int 	m_nCpuID;		// CPU ����

	enum
	{
		STATE_INWAIT  = 1,  // �ʺ���֤֮ǰ
		STATE_INLOGIN = 2,	// �ʺ���֤֮�� ---- ��ҶϿ�����֮ǰ
		STATE_INGATE  = 3,  // ��ҶϿ�����֮�� ---- �����ɵ�¼֮ǰ
		STATE_INGAME  = 4,  // �����Ϸ��   ---- ��Ҷ�������
	} mWhere;
				    
public:
	CLoginPlayer( ) 
	{
		if ( CObj::msCreateMode ) Initialize(); else Resume();
	}

	int Initialize()
	{
		//TODO: 
		mLoginToken  = 0;
		mVerifiedByERating = false;


		memset(mUserName, 0, sizeof(mUserName));
		memset(mUserPasswd, 0, sizeof(mUserPasswd));

		m_nMatrixType = 1;
		memset(m_szMatrixCode, 0, sizeof(m_szMatrixCode));

		mAccountID = 0;

		mUrlID = 0;
		mStatus = 0;
		memset( m_szMatrixCoord, 0, sizeof( m_szMatrixCoord ) );

		m_nGameID = 4;

		strcpy(m_szMac, "000000000000"); 

		m_nDiskID = 0;
		m_nCpuID = 0;

		return 0;
	}

	bool IsPartner()
	{
		return (mUserName[0] == '$');
	}

	int GetGameID()
	{
		return m_nGameID;
	}

	int  Resume(){ return 0; }

	~CLoginPlayer() {}
};

// ********************************************************************** //
// CLoginPlayer
// ********************************************************************** //
class CWorldServer: public CObj
{
public:
	enum 
	{
		IP_ADDRESS_LENGTH= 32,
		HOST_NAME_LENGTH = 32,
		SCENE_NUMBER = 10
	};

	char mAddress[IP_ADDRESS_LENGTH];		// ���������ַ
	char mHostName[HOST_NAME_LENGTH];		// ��������
	int  mPlayerNumber[SCENE_NUMBER];		// �������
	int  mGameVersion;						// ����汾

#ifdef USING_ERATING
	char mGateCode[AGIP_GATEWAY_CODE_LEN+1];
	char mGatePasswd[AGIP_PASSWORD_LEN+1];
	char mGateMac[AGIP_MAC_LEN+1];
#endif

	int  mRegistID;							// ע�ᵽERATING֮�󷵻ص�GateID
	int  mWorldID; 							// ��Ϸ�Լ�������ʶ��, ��Ϊerating �涨����xxx
	int  mGameID;							// ��ϷID
public:
	CWorldServer()
	{
		if ( CObj::msCreateMode ) Initialize(); else Resume();
	}

	~CWorldServer() {}

	int Initialize()
	{
		mAddress[0] = 0;
		mHostName[0] = 0;
		mWorldID = 0;
#ifdef USING_ERATING
		mGateCode[0] = 0;
		mGateMac[0] = 0;
		mGatePasswd[0] = 0;
#endif
		mGameID = 504;

		for (int i = 0; i< SCENE_NUMBER; ++i) mPlayerNumber[i] = 0;
		
		return 0;
	}

	int Resume(){ return 0; }
};

/*
class CSession: public CObj
{
public:
	int         mSessionID;
	int 		mSessionClass;
	int         mParameter1;
	int         mParameter2;
	CWTimer     mTimer;

public:
	CSession()
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	}

	~CSession() {}

	int Initialize()
	{
		mSessionID = 0;
		return 0;
	}

	int Resume() {return 0;}

	void assign(int session_id, int session_class, int param1, int param2, int timeout)
	{
		mSessionID = session_id;
		mSessionClass = session_class;
		mParameter1 = param1;
		mParameter2 = param2;
		mTimer = timeout;
	}
};
*/

enum 
{
	em_dbsession_null = 0x00,
	em_agipsession_handset = 0x01,
	em_agipsession_unbind, 
	em_agipsession_bind,
	em_agipsession_userlogin,
	em_agipsession_ibpayaudit,
	em_agipsession_ibitemused,
	em_agipsession_ibexchange1,
	em_agipsession_ibexchange2,
	em_agipsession_ibexchange3,
	em_agipsession_ibexchange4,
	em_dbsession_verifyacctbymysql,
	em_dbsession_roledetail,
	em_dbsession_roleproto,
	em_dbsession_ipbind,
	em_dbsession_chargeamount,
	em_dbsession_chargeaudit,
	em_dbsession_createaccount,
	em_dbsession_ibpayres,
	em_dbsession_ibpayaudit,
	em_dbsession_currentibpay,
	em_dbsession_ibtranserror,
	em_dbsession_loadibused,
	em_dbsession_goods2npc,
	em_dbsession_goodsfromnpc, 
	em_dbsession_goodsbetweenusers,
	em_dbsession_goodshistory,
	em_dbsession_operationdetail,
	em_dbsession_roleitemoperate,
	em_dbsession_rolemoneyoperate,
	em_dbsession_roleexpoperate,
	em_dbsession_itemupgrade,
	em_dbsession_corpslist,
	em_dbsession_corpsdetail,
	em_dbsession_paylistquery,
	em_dbsession_paydetaildemand, 
	em_dbsession_familylog,
	em_dbsession_corpslog,
	em_dbsession_querylogin,
	em_dbsession_querydeath,
	em_dbsession_recoverequip,

	em_dbsession_loadbourselog,
	em_agipsession_exchange,
	em_dbsession_querytask,
	em_dbsession_userlevel,
	em_dbsession_queryiplog,
	em_dbsession_query_stock1,
	em_dbsession_query_stock2,
	em_dbsession_query_stock3,
	em_dbsession_query_ybstall,
	em_dbsession_query_rolepickitemfromboss,
};

class CLoginLogic;
class SysProtocol;
class CMessage;
#ifdef USING_ERATING
typedef CSession CAGIPSession;
#endif

typedef CSession CServerSession;

// ********************************************************************** //
// CClientInfo
// ********************************************************************** //
//
// �ͻ���������Ϣ

class CClientInfo
{
	public:
		CClientInfo()
		{
			if ( CObj::msCreateMode )
			{
				Initialize( );
			} 
			else
			{
				Resume( );
			}
		};

		~CClientInfo() {};

		int Initialize()
		{
			mUin = 0;
			mClientAddr = 0;
			mClientPort = 0;
			mSockTime = 0;
			mSockIndex = 0;
			mNetSpeed = 0;
			mVer = 0;
			memset( mKey, 0, sizeof(mKey) );
			mFlag = 0;
			m_tLastActiveTime = 0;

			return 0;
		}

		int Resume() { return 0; }

		enum  { CRYPT_KEY_LENGTH = 32 };

		unsigned int			mUin;					//�ʺ�ID
		unsigned int 			mClientAddr;			//�ͻ��˵������ַ
		unsigned short 			mClientPort;			//�ͻ��˵Ķ˿ں�
		unsigned int 			mSockTime;				//�ͻ��˵������ַ
		unsigned short 			mSockIndex;				//�ͻ��˵Ķ˿ں�
		int 					mNetSpeed;				//�������
		short 					mVer;					//C-SЭ��汾��
		unsigned char 			mKey[CRYPT_KEY_LENGTH];	//����ʹ�õ�Key
		char 					mFlag;					//�ͻ���״̬��0 - δ���ӣ�1 - ���ߣ� 2 - ����
		time_t					m_tLastActiveTime;		// ����Ծʱ��
};

class CIbPayAudit: public CObj
{
  public:
  	enum { em_audit_limit = 64 };

	uint32_t m_nAccountID;
	uint32_t m_nCount;
	uint8_t  m_nSubjectID;
	uint64_t m_ullEndIbTransID;
	uint64_t m_ullMinIbTransID;

	struct 
	{
		uint64_t ullIbTransID;
		uint32_t nRoleID;
		uint8_t  nMetierID;
		uint8_t  nGenderID;
		uint8_t  nRoleLevel;
		uint8_t  nRatingID;
		uint32_t nIbCode;
		uint8_t  nPackageFlag;
		uint32_t nItemCount;
		time_t   nPayTime;
		uint32_t nUserIP;
		uint32_t nPrice;
		uint32_t nDiscountPrice;       
	}m_Records[em_audit_limit];

  public:
	CIbPayAudit()
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	};

	~CIbPayAudit() {};

	int Initialize()
	{
		m_nAccountID = 0;
		m_nCount = 0;
		m_ullMinIbTransID = 0;
		m_ullEndIbTransID = 0;

		memset(m_Records, 0, sizeof(m_Records));

		return 0;
	}

	int Resume() { return 0; }
};

#endif



