#pragma once
#include "mailtype.h"
#include "dbinterface.h"

#define MAIL_TABLE_COUNT	6
#define MAIL_TABLENAME_LENGTH 40   

// �ʼ�������Ϣ,�洢��ʱ�ã��ַ�����ָ��
struct MailBaseInfo
{
	int        mMailID;                   // �ʼ�ID
	const char *mSrc;                     // �ʼ�������
	unsigned int mSendTime;               // �ʼ�����ʱ�� 
	const char *mTitle;				      // �ʼ�������	
	int mType;                            // �ʼ���Ϣ
	int mLevel;							  // �ʼ�����
	unsigned int mExpiredTime;            // ����ʱ��
	int mSrcId;							  // �ʼ����ͷ���ɫID
	int mItemNum;						  // ��������
	int mDestId;						  // �ʼ����շ�ID
	const char *mDesName;				  // �ʼ����շ�������
	MailBaseInfo()
	{
		memset( this, 0, sizeof( MailBaseInfo ) );
	}
};

// �ʼ���Ϣ
struct MailInfo
{
	MailBaseInfo mMailBase;                // ������Ϣ
	int   mMoneySend;                      // ���͵Ľ�Ǯ
	int   mMoneyNeedBack;                  // ��Ҫ�Է�֧���Ľ�Ǯ	
	const char *  mBody;		           // �ʼ�����	
    char  mExtDate[ MAIL_EXTDATE_LEN ];    // �ʼ�������������Ǯ
    int   mExtLen;						   // �ʼ�����
	MailInfo()
	{
		memset( (char*)this, 0, sizeof( MailInfo ) );
	}
	void ClearMailInfor()
	{
		memset( (char*)this, 0, sizeof( MailInfo )  );
	}
};


// �ʼ���Ϣ�����ݲ���

class CMailDBOperate: public CDBReceiver
{
public:
	// �����ʼ��ĺ���ָ��
	typedef void (*SendMailFun)( int MailID , int MailPtr );
	
	// ��ȡ�ʼ��б�ĺ���ָ��
	typedef void (*GetMailListFun)( int vParameter1, int vCount, MailBaseInfo* pMailItemArray );
	
	// ��ȡ�ʼ��ĺ���ָ��
	typedef void (*ReadMailFun)( int vParameter1, const MailInfo* pMailInfo);

	// ��ȡ����ʼ���Ϣ��
    typedef void (*GetMailBoxInforFun)( int  Nationality, int MailCount , int SrcCharId , int IfPlayerExist ) ;

	// ִ���ʼ������ĺ���ָ�루 ��dataserverͨ�� ��
	typedef void (*ExecFun)( CMessage* pMessage, int vParameter1);
	
	// ִ�л�ȡ�ʼ��ĺ���
	typedef void (*GetMailFun )( int tMail, MailInfo * Mailinfor , bool IfEnd );
	
public:
	// ��ȡ��ҵ��ʼ�����
	static int GetMailBoxStatus( int CharID, int CountryID = 1 );
	
	// �����ʼ�
	static int MailSend( int  CharID, int MailCaCheID, const MailInfo *pMailInfo, bool IfNeedCallBack = false, int CountryID = 1, int nWorldCharID = 0 );
	
	// ��ȡ�ʼ�
	static int MailRead( ReadMailFun pFun, int vMailID, int vCharID, int CountryID = 1 );
	
	// ɾ���ʼ�
	static int MailDel(  int vMailID, int CharID = 0, int CountryID = 1 );
	
	// ��ȡ�ʼ�����ϸ��Ϣ
	static int GetMailDetailInfo( int MailID, int CharID, int CountryID = 1 );	
	
	// �����ʼ�����
	static int UpMailAccessory( int vMailID, const MailInfo *pMailInfo, int CharID = 0, int CountryID = 1 );
	
	// �����ʼ���Ǯ��״̬�����ݿ���
	static int UpMailStatus( int vMailID, const MailInfo *pMailInfo, int CharID = 0, int CountryID = 1 );		
	
	// �����ݿ��ȡ�ʼ�
	static int GetMailFormDB( int ReceKind, int Charid , int MailCount , int LastMailID, int CountryID = 1 );
	
	// ����Ҫ���⴦������ݿ�����Ļص�����
	static void MailReceNothing( CMessage* pMessage, int vParameter1, int vParameter2 );	

	// ɾ���ʼ���ʱ
	static void MailDelTimeout( int nParam1, int nParam2 );
    
    // �����ʼ��Ļص�����
    static void DbMsgRece( CMessage * pMessage, int vParameter1, int vParameter2 );
    
    // �����ݿ��ȡ�ʼ��Ļص�����
    static void DBMailRece( CMessage * pMessage, int Parameter1, int Parameter2 );
    
    // �����ݿ��ȡ����ʼ������Ļص�����
    static void GetMailCountRece( CMessage * pMessage, int Parameter1, int Parameter2 );
    
    // �����ݿ��ȡ��ҵ����ʼ���Ϣ
    static void CheckNewMailRece( CMessage * pMessage, int Parameter1, int Parameter2 );
    
    // �����ݿ��ȡ�ʼ���ϸ��Ϣ�Ļص�����
	static void GetMailDetailRece( CMessage * pMessage, int Parameter1, int Parameter2 );
	
	// ����ʼ��ı���
	static const char *GetMailTableName( int CharID, int CountryID );	
	
	// ������ݿ��Ƿ���ĳ���ʼ���¼
	static void CheckIfMailInDB( int nCharID, int nContryID, int nMailID );	
	
	// ת��Ӫʱ���ʼ�����
	static void ChangeRoleCampMail( int nRoleID, int nOldCampID, int nNewCampID );
	
	// ������������
	static void SaveOffLineChatMsg( int nSrcRoleID, const char *pSrcName, int nDesRoleID, const char *pMsg, int nCountryID );

	// ��ȡ��������
	static void LoadOffLineChatMsg( int nRoleID, int nCountryID, int nLimitCount = 30 );

	// ɾ����������
	static void DeleteOffLineChatMsg( int nRoleID, int nCountryID );
};


