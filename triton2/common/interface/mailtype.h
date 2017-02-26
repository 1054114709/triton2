#pragma once
#include "protype.h"

#define MAXMAILTABLENUM			6
#define MAILTABLEFIRNAME		"UMS_ROLE_MAIL_"
#define MAILMODULEID		    ( 8 )
#define MAIL_MAILBOX_MAXMAILNUM	    ( 40 )						 // �ͻ����ܹ���ʾ���ʼ����������ֵ
#define MAIL_SAVE_COUNT		    ( 240 )							 // ���ݿ��ܹ�������ʼ��������ֵ
#define MAIL_MAX_PAGENUM	    ( 40 )							 // ����ÿһҳ������ʼ�����	
#define MAIL_LOCKNUM_MAX	    ( 30 )							 // �ܹ��������ʼ����������
#define MAIL_TITLE_LEN		    ( 100 )   						 // �ʼ����ⳤ��
#define MAIL_BODY_LEN			( 1000 )						 // �ʼ����ĳ���
#define MAIL_PAGE_ITEM_PER_LEN	( ITEMOBJ_BUFFLEN )				 // ������Ʒ�ִ������� 
#define MAIL_ITEM_COUNT_MAX		( 5 )							 // �ʼ��е���󸽼�����
#define DAY_TIME				86400							 // ( 3600*24 )


#define MAIL_EXTDATE_LEN		( MAIL_ITEM_COUNT_MAX * MAIL_PAGE_ITEM_PER_LEN  ) // �������泤��
#define MAIL_SEND_MONEY_PRO		( 10 )											  // ��������
#define MAIL_ITEM_CHARGE        ( 100 )											  // ��������

#define MAIL_TIME_MONEYNEED     ( 2*24*3600 )									  // �����ʼ�ʱ��
#define MAIL_TIME_COMMON        ( 3*24*3600 )									  // ��ͨ�ʼ�δ��ʱ��
#define MAIL_TIME_PACKAGE       ( 30*24*3600 )									  // �����ʼ�ʱ�ޣ����ں󷵻�
#define MAIL_TIME_SYS           ( 30*24*3600 )									  // û��ʱ�ޣ�ֱ�����ȡ��������Ʒ(-1)
#define MAIL_OVER_TIME			( 7 * 24 * 3600 )								  // �ʼ���Чʱ��


// Level��ʾ�ʼ�����
#define MAIL_LEVEL_USER							( 1<<0  )                        // �û��ʼ�
#define MAIL_LEVEL_SYSTEM						( 0<<0  )                        // ϵͳ�ʼ�

#define MAIL_LEVEL_MONEYNEED                    ( 1<<1  )                        // �����ʼ�
#define MAIL_LEVEL_BACKMAIL                     ( 1<<2  )                        // ����
#define MAIL_LEVEL_CHATMSG                      ( 1<<3  )                        // ��������



// ����Level�ֶ�
#define MAIL_SETLEVEL_USER( vLevel )         ( vLevel |= ( 1<<0 )  )          
#define MAIL_SETLEVEL_SYSTEM( vLevel )       ( vLevel &= ~( 1<<0 ) )
#define MAIL_SETLEVEL_CHATMSG( vLevel )       ( vLevel |= ( 1<<3 ) )


#define MAIL_SETLEVEL_MONEYNEED( vLevel, boolvalue )     if( boolvalue ) vLevel |= MAIL_LEVEL_MONEYNEED; \
															else vLevel &= ~MAIL_LEVEL_MONEYNEED; 		\
															
#define MAIL_SETLEVEL_BACKMAIL( vLevel,	 boolvalue )     if ( boolvalue ) vLevel |= MAIL_LEVEL_BACKMAIL; \
															else vLevel	&= ~MAIL_LEVEL_BACKMAIL;		\
	

// Type�ֶα�ʾ�ʼ���״̬
#define MAIL_TYPE_NEW 						( 1<<0 )                            // δ���ʼ�
#define MAIL_TYPE_ACCESSORY					( 1<<1 )                            // �и���
#define MAIL_TYPE_LOCK                      ( 1<<2 )                            // ����
#define MAIL_TYPE_IFMONEYPAY                ( 1<<3 )                            // �Ƿ��Ѿ�����
#define MAIL_TYPE_ACCECHAGED                ( 1<<4 )                            // �����Ƿ����仯
#define MAIL_TYPE_NEEDSAVE                  ( 1<<5 )                            // �Ƿ���Ҫ���±��浽���ݿ���
#define MAIL_TYPE_HASSENDTOCLIENT           ( 1<<6 )							// �ʼ����ĺ͸�����Ϣ�Ƿ��Ѿ������ͻ���
#define MAIL_TYPE_HASBODY					( 1<<7 )							// �ʼ��Ƿ�������

// ����Type �ֶ�
#define  MAIL_SETTYPE_NEW( vType , boolvalue )              if ( boolvalue) vType |= MAIL_TYPE_NEW ; else vType &= ~MAIL_TYPE_NEW ; 
#define  MAIL_SETTYPE_ACCESSORY( vType , boolvalue )        if ( boolvalue) vType |= MAIL_TYPE_ACCESSORY ; else vType &= ~MAIL_TYPE_ACCESSORY ;
#define  MAIL_SETTYPE_LOCK( vType , boolvalue )             if ( boolvalue) vType |= MAIL_TYPE_LOCK ; else vType &= ~MAIL_TYPE_LOCK ; 
#define  MAIL_SETTYPE_IFMONEYPAY( vType , boolvalue )       if ( boolvalue) vType |= MAIL_TYPE_IFMONEYPAY ; else vType &= ~MAIL_TYPE_IFMONEYPAY ;
#define  MAIL_SETTYPE_ACCECHAGED( vType , boolvalue )        if ( boolvalue) vType |= MAIL_TYPE_ACCECHAGED ; else vType &= ~MAIL_TYPE_ACCECHAGED; 
#define  MAIL_SETTYPE_NEEDSAVE( vType , boolvalue )         if ( boolvalue) vType |= MAIL_TYPE_NEEDSAVE ; else vType &= ~MAIL_TYPE_NEEDSAVE; 
#define  MAIL_SETTYPE_HASSENDTOCLIENT( vType , boolvalue )  if ( boolvalue) vType |= MAIL_TYPE_HASSENDTOCLIENT ; else vType &= ~MAIL_TYPE_HASSENDTOCLIENT; 
#define	 MAIL_SETTYPE_HASBODY( vType , boolvalue  )			if ( boolvalue) vType |= MAIL_TYPE_HASBODY ; else vType &= ~MAIL_TYPE_HASBODY; 

#define MAIL_IS_USER( vLevel )                  ( ( vLevel &  MAIL_LEVEL_USER )== MAIL_LEVEL_USER )        // �Ƿ��û��ʼ�
#define MAIL_IS_SYSTEM( vLevel )                ( ( vLevel &  MAIL_LEVEL_USER )== MAIL_LEVEL_SYSTEM )      // �Ƿ�ϵͳ�ʼ�                            

#define MAIL_IS_MONEYNEED( vLevel )             ( (vLevel & MAIL_LEVEL_MONEYNEED) == MAIL_LEVEL_MONEYNEED ) // �Ƿ񸶷��ʼ�
#define MAIL_IS_BACKMAIL( vLevel )              ( (vLevel & MAIL_LEVEL_BACKMAIL) == MAIL_LEVEL_BACKMAIL )  // �Ƿ�ϵͳ����


// ����ʼ�״̬
#define MAIL_IS_NEW( vType )              ( ( vType & MAIL_TYPE_NEW ) )        // �Ƿ�δ��
#define MAIL_IS_ACCESSORY( vType )        ( ( vType & MAIL_TYPE_ACCESSORY ) )  // �Ƿ���и���
#define MAIL_IS_LOCK( vType )             ( ( vType & MAIL_TYPE_LOCK ) )       // �Ƿ�����
#define MAIL_IS_ACCECHAG( vType )         ( ( vType & MAIL_TYPE_ACCECHAGED ) ) // �����Ƿ����仯
#define MAIL_IS_NEEDSAVE( vType )         ( ( vType & MAIL_TYPE_NEEDSAVE ) )   // �Ƿ���Ҫ����
#define MAIL_IS_IFMONEYPAY( vType )       ( ( vType & MAIL_TYPE_IFMONEYPAY ) ) // �Ƿ��Ѹ���
#define MAIL_IS_HASSENDTOCLIENT( vType )  ( ( vType & MAIL_TYPE_HASSENDTOCLIENT ) )	// �ʼ������Ƿ��Ѿ����͸��ͻ���
#define MAIL_IS_HASBODY( vType )		  ( ( vType & MAIL_TYPE_HASBODY ) ) // �ʼ��Ƿ�������

#define  MAX_SYSMAILTYPE_NUM		100		// ϵͳ�ʼ�����������

enum Method_ChangeItem
{
	ITEM_ADD,							// �����ʼ�ʱ��Ӹ���
	ITEM_TAKE,							// �����ʼ�ʱȡ�¸���
	ITEM_MOVE,							// ����ʱ�ڸ����б����ƶ���Ʒ
};

enum FetchMailKind
{
	FETCHMAIL_PAGE,						// �����ݿ��ȡһҳ���ʼ���Ϣ
	FETCHMAIL_NEW,						// �����ݿ��ȡһ�����ʼ�
};

enum MailBoxStatus
{	 
	MAIL_STATUS_INITIALIZE   =  ( 0 ),				// ��ʼ��״̬
	MAIL_STATUS_GETCOUNT	 =  ( 1 << 1 ),			// ��ȡ�ʼ�����
	MAIL_STATUS_CHECKNEWMAIL =	( 1 << 2 ),			// ����Ƿ������ʼ�
	MAIL_STATUS_SHUTDOWN	 =	( 1 << 3 ),			// ����ر�״̬
	MAIL_STATUS_OPEN    	 =	( 1 << 4 ),			// �����״̬
	MAIL_STATUS_CHECROLEINFO =	( 1 << 5 ),			// ����ʼ����շ���Ϣ
	MAIL_STATUS_GETMAILPAGE	 =	( 1 << 6 ),			// ��ȡһҳ�ʼ�
	MAIL_STATUS_GETMAILDETAIL=	( 1 << 7 ),			// ��ȡ�ʼ���ϸ��Ϣ
	MAIL_STATUS_BACKMAIL	 =	( 1 << 8 ),			// ����״̬
	MAIL_STATUS_SENDMAIL     =	( 1 << 9 ),			// �ͼ���״̬
	MAIL_STATUS_READMAIL	 =	( 1 << 10 ),		// �ռ���״̬		
};


enum EMail_ERROR
{
	ERROR_MAILACTION_SUCCESS = 1,		// �ʼ������ɹ�	
	ERROR_MAILBOX_NOEXIST ,				// ��Ҳ�����
	ERROR_MAILBOX_CANNOTSEND,           // �ʼ����ܷ���
	ERROR_MAILBOX_CANNOTOPEN,			// ���䲻�ܴ�
	ERROR_GETACCESSORY_SUCESS,			// ��ȡ�����ɹ�	
	ERROR_SENDMAIL_SUCESS,				// �����ʼ��ɹ�
	ERROR_CHANGEPAGE_NOMAIL,			// �ͻ���Ҫ��ҳʱ�Ѿ�û���ʼ����Է���
	ERROR_INITIAL_NOTCOMPLETE,			// ������ʱ����û�г�ʼ�����		
	ERROR_SENDMAIL_NOTENGHMONEY,		// �����ʼ�ʱ�����ʲ���	
};

enum Email_CheckType
{
	CHECKTYPE_PAYMONEYFORMAIL	= 1,		// ��Ϊ�����ʼ���������ݿ�
};

enum EMail_RoleQueryType
{
	ROLEQUERYTYPE_MAILSEND				=	0,		// ��ͨ�����ʼ���ѯ
	ROLEQUERYTYPE_MARRIAGEINVITATION	=	1,		// ������������ѯ
};

// ϵͳ�ʼ�����
enum en_sys_mail_type
{
	SYSMAIL_QUESTION_AWARD = 33, // �����ʾ�
	SYSMAIL_FB_AWARD = 34,  // ����
};
enum en_mail_prize_type
{
	PRIZE_CHANGE_CAMP = 37,//ת��Ӫ����
};

// ϵͳ�ʼ�IDΪ�ɾ�ID+ACHIEVE_SYSMAIL_BASEID
#define  ACHIEVE_SYSMAIL_BASEID 10000

// �����ط��͵��������ʼ��ķ�������
enum Em_MailSendType
{
	MAILSENDTYPE_SYS	=	0,	// ϵͳֱ�ӷ���
	MAILSENDTYPE_BYID	=	1,	// ��Ҫͨ��ϵͳ�ʼ�IDת���ʼ�����
};
