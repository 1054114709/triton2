#pragma once

#include "sceneobj_define.h"  
#include "mailtype.h"
#include "maildboperate.h"
#include "mailmessage_pb.hxx.pb.h"
#include "servertool.h"
#include "lk_hashmap.h"


class CItemObject;
class  CEntityPlayer;


// �洢���ÿ���ʼ�����Ϣ
class CMailCache : public CObj
{
public:
	int			   mMailID;								                      // �ʼ�ID
	char           mSrcName[ NAME_LENGTH ];				                      // ������
	unsigned char  mLevel;                                                    // �ʼ�����	
    unsigned char  mType;										              // �ʼ�״̬	
	char           mMailTitle[MAIL_TITLE_LEN];				                  // ����
	int			   mItemObjID[MAIL_ITEM_COUNT_MAX];							  // �ʼ���������Ÿ���ID
	int	           mItemNum;	       										  // ����������	
	int            mExpiredTime;								              // ����ʱ��
	int            mSendTime;                                                 // �ʼ�����ʱ��
	int            mMoney;                                                    // �����еĽ�Ǯ	
	int            mMoneyNeedPayBack;                                         // ��Ҫ֧���Ľ�Ǯ	
	int			   mSrcId;													  // ���ͷ��Ľ�ɫID
	CWTimer        mMailTimer;                                                // �����ʼ���ʱ��10����
public:
 	CMailCache( )
	{
		if ( CObj::msCreateMode )
		{
			Initialize();
		}				
		else
		{
			Resume( );
		}				
	}
	~CMailCache( )
	{		
	
	}
	// ��ʼ��
	virtual int Initialize() 
	{ 	
		mMailID = 0;
		mLevel = 0;
		mType = 0;
		mExpiredTime = 0;
		mItemNum = 0;
		mMoney = 0;
		mMoneyNeedPayBack = 0;
		mSrcId = 0;
		mSendTime = 0;
		memset( mItemObjID, 0, sizeof( mItemObjID ) );
		memset( mSrcName, 0, sizeof( mSrcName ) );
		memset( mMailTitle, 0, sizeof( mMailTitle ) );		
		return 0;
	}
	// �ָ�
	virtual int Resume( ) { return 0; } 
}; 

// ��ҵ�������Ϣ
class CMail : public CObj
{
public:
	CMail( )
	{	
		if( CObj::msCreateMode )		
		{
			Initialize();
		}
		else
		{
			Resume();
		}
	}

	virtual ~CMail( )
	{ 
		
	} 
	
	// ��ʼ��
	virtual int Initialize(  ) 
	{
		m_nEntityID = 0;
		m_nTotalMailCount = 0;
		m_nCurCacheMailCount = 0;
		m_nMailBoxStatus = MAIL_STATUS_INITIALIZE; 
		memset( m_nList, 0, sizeof( m_nList ) );  		
		m_nActionMailID = 0;
		m_nLockMailNum = 0;
		m_nLastPageMailID = 0;
		m_nLeftPageMailNum = 0;	
		m_nLastMailID = 0;
		m_nReceiverID = 0;	
		m_vMailCache.initailize(); 
		m_nMailIDFetched = 0;	
		m_nMailFetcheCount = 0;	
		return 0; 
	}

	// �ָ�
	virtual int Resume(  ) { return 0; } 
private:	 
	typedef lk::hash_map< int, int, MAIL_MAILBOX_MAXMAILNUM >  _MAIL_CACHE_LIST_TYPE_;
	struct MailItemList  
	{
		int ItemIndex;
		int ItemNum;
		MailItemList( )
		{
			if ( CObj::msCreateMode )
			{
				Initialize();
			}
			else
			{
				Resume();
			}
		}
		int Initialize()
		{
			ItemNum   = 0;
			ItemIndex = 0;	
			return 0;
		}
		int Resume()
		{
			return 0;
		}
		
	};	
	
public:
	int						   m_nMailBoxStatus;
	_MAIL_CACHE_LIST_TYPE_     m_vMailCache;                                        // �ʼ�����          
	MailItemList               m_nList[ MAIL_ITEM_COUNT_MAX ];                      // ��Ʒid�б����ڱ��淢���ʼ�������Ϣ��	
	int						   m_nReceiverID;										// �ʼ����շ��Ľ�ɫid�������ʼ��ã�
    unsigned short             m_nCurCacheMailCount;                                // ��ǰ�ռ����ʼ�����
	unsigned short			   m_nTotalMailCount;									// ��ǰ���ݿ���ʼ�����
	int                        m_nLastMailID;										// �ʼ�������������һ���ʼ��ķ�������
    CWTimer                    m_sTimer;											// �ʼ���ʱ��10���ӣ�ÿ5���Ӱ���Ҫ���̵��ʼ�����һ��
    int						   m_nLeftPageMailNum;									// ��δ��ȡ���ʼ�����  
	int						   m_nLastPageMailID;									// ��ǰ��ȡ���һҳ���һ���ʼ���ID  
	int						   m_nLockMailNum;										// �������ʼ�����
	int						   m_nActionMailID;										// �������ڱ��������ʼ�ID
	int		  			       m_nEntityID;											// ���ʵ��ID
	int						   m_nMailIDFetched;									// ��¼���ڴ����ݻ�ȡ�ʼ�ID			
	unsigned short			   m_nMailFetcheCount;									// ��¼���ڴ����ݻ�ȡ�����ʼ�ID
public:
	static MailInfo  m_sMailInfo;												    // ���ڴ浽���ݿ�����ݽṹ
public:
	/***************** ����������****************/
	// ��ȡ�ʼ�״̬
	int  GetMailStatus(  );	  
	
	// �����ʼ�״̬
	void SetMailStatus( int vMailStatus );	
	
	// �����Ƿ��Ѿ���ʼ�����
	bool IfMailBoxInitial(  );	   	
	
public:
	/************��������Ļ���*****************/
	// �������ʱ�����ʼ�����
	void DestroyMailCache(  );
	
	// ��ȡ�����е��ʼ�������Ϣ	
	int GetMAilListInfo( CMessageMailListNotify &pMessage );	
	
	// ��ȡ�ʼ�����
	int GetMailDetailInfo( int vMailID, CMessageMailReadResponse &MsgMailRead );
public:
    /************�����ʼ�*****************/
    
    // �����ʼ����շ���ɫid
	void SetMailReceiverID( int DestCharID );
	
	// ��ȡ�ʼ����շ���ɫid
	int  GetMailReceiverID(  );
    
	// �ı䷢���ʼ��ĸ���
	int ChangeMailItem( int SrcIndex, int ItemNum, int DesIndex, int MovePos = ITEM_ADD );

	// �����ʼ�
	int Send( int vMoney, int MoneyNeedPayBack, const char *pMailTitle, const char *pMailBody , int DesCharID, const char *pDesname );

	// ����ϵͳ�ʼ�
	static int SysSend( const char *pDesName, int DesCharid, const char *pTitle, const char *pSrcName, const char *pBody, CItemObject ** tpItemObj,int  ItemObjNum, int CountryID = 1, int nMoney = 0, int nCharID = 0 );

	// ���ʼ��������ݿ���
	static void SaveMail( CMailCache * tpMail , const char * pMailBody, int DesCharID = 0, bool IfNeedCallBack = false, const char *pDesname = NULL, int CountryID = 1, int nCharID = 0 );

	// ����Ʒid�б��������͵��ʼ�
	CMailCache * CreatNewMail( int vMoney, int MoneyNeedPayBack, const char *pMailTitle , int nDestCharID, const char* pDesName);	
	
	// �����ʼ������������������
	//static bool SendMailToPlayer( int DesCharID, CMailCache *tpMailCache );
	
	// �������ʼ��ʼ�֪ͨ
	static int SendNewMailNotice( int DesCharID, CMailCache *tpMailCache );
	
	// ����/��ȡ���ʵ��ID
	void SetEntityID( int vEntityID ){ m_nEntityID = vEntityID; }
	int	 GetEntityID( )	{ return m_nEntityID; }	  
	
	// ��ȡ���ʵ��ָ��
	CEntityPlayer *GetEntityPlayer( );
			
	// ��շ����ʼ��ĸ����б�
	void ClearItemList( );	
	
	// ���ÿͻ�����ʾ���ʼ�ID�����ֵ
	int SetMaxMailID( int vMailID );
	
	// ��ȡ�ͻ�����ʾ���ʼ�ID�����ֵ
	int GetMaxMailID();
	
	//	Ϊ�����ʼ�֧����Ǯ
	int PayMoneyForMail( int nMailID, int &rMoney, int &rTime );

	// �����Ƿ��и����ʼ� 
	bool IsHavePayMail();
public:
	/*************��ȡ�ʼ�***************/ 
	
	//// �õ�ָ��λ�õ��ʼ�
	//CMailCache * GetMailCache( int vIndex, int vMailID );
	
	// �õ�ָ���ʼ�id���ʼ�
	CMailCache *GetMailCacheByMailID( int vMailID );

	// �õ�����
	int GetAccessory( int vMailID );
	
	// ��ȡ�����ʼ��ĸ���
	int GetAccessory( int vItemIndex, int vMailID, bool vIsMoney );
	
	// �����ݿ��л���ʼ������Լ�������
	int GetMailFromDB( int count, int LastMailID, int ReceKind = FETCHMAIL_PAGE );

	// ���������һ�����ʼ�
	int InsertMail( CMailCache *tpMailCache, int InIfNewMail = 0 );	
	
	//	���������������������ʼ�
	int ReceiveRouterMail( CMessageNewMailNotify *tpMsg );
	
	// ���ʼ���Ϣ���µ�����������
	int UpdateAccesory( CMailCache *tpMailCache );
	
	// ���ʼ�״̬�ͽ�Ǯ���µ����ݿ���
	int UpdateMailStatus( CMailCache *tpMailCache );
	
	// �����ʼ���Ϣ
	int UpdateMailInfo( int MailID );	
	
	// �����ʼ���Ϣ�����ݿ���
	int UpdateMail(  CMailCache *tpMailCache );

	// ��ȡ�ʼ��ĸ�����������Ϣ
	int GetMailDetailFromDB( int MailID );
	
	// ��ȡһҳ�ʼ���Ϣ
	int GetMailPage(  );
	
	// �����ʼ�������Ʒ
	int DestroyMailAccessory( CMailCache *tpMailCache ); 
	
	// �������ڲ������ʼ�ID
	void SetActionMailID( int MailID );
	int GetActionMailID( ) { return m_nActionMailID; }	


	// �����ʼ���״̬��Ϣ�����ʼ��������ʼ�����
	void SendMsgMailBoxStatus( int MailCount, int NewMailCount );
	
public:
	/*************ɾ���ʼ�***************/ 	
	// ɾ��һ���ʼ�
	int DelMail( int MailId );
	
	// ���ʼ�������ɾ���ʼ�	
	int EraseMailCache( int MailId );
public:
	// ����
	int BackMail(  int vMailID , const char *pMailBody );
public:	
	/*************�ʼ��Ӽ���***************/ 
	// ���ʼ�����
	int LockMail( int MailId );
	
	// ���ʼ�����
	int UnLockMail( int MailId );
public:
	// ��ȡ
    static int TestGetMail( int CharId, int count, int m_nLastMailID );
    
    // 	�����ʼ��Ļص�����
	static void SendMailCallBack( int MailID, int MailCacheID, int CharId );
	
	// �����ݿ��ȡ�ʼ��Ļص�����
	static void RecMailFromDBCallBack( CEntityPlayer *pPlayer, CMail *tpMail, MailInfo *tpMailInfor, bool IfEnd,  CMessageMailListNotify & MsgMailList, int ReceKind = FETCHMAIL_PAGE  );
	
	// �����ݿ��ȡ�ʼ������Ļص�����
	static void GetMailCountCallBack( int CharID, int MailCount );
	
	// �����ݿ��ȡ���ʼ������Ļص�����
	static void CheckNewMailCallBack( int CharID, int NewMailCount );
		
	// �����ݿ��ȡһҳ�ʼ���Ϣ�Ļص�����
	static void GetMailPageCallBack( int CharID, int MailCount  );
	
	// �����ݿ��ȡ�ʼ���ϸ��Ϣ�Ļص�����
	static void GetMailDetailInfoCallBack( int CharID, int MailID, MailInfo &MailDeltailInfo, bool bMailExist = true ); 
	
	// �������
	int MailCacheClear( );		

public:
	inline int GetCharID( );
public:

	// �����ʼ�ʱ�Ƿ������ʼ�֪ͨ
	bool CanSendNewMailNotice();		
};


