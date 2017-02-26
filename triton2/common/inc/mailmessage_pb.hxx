import "coremessage_pb.hxx";
import "property_pb.hxx";
// ������ٶ�����/������
option optimize_for = SPEED;

enum MailMessageID
{	
	ID_C2S_REQUEST_OPENMAILBOX           = 0x2000;          // �����������
	ID_S2C_RESPONSE_OPENMAILBOX          = 0x2001;          // ������Ļ�Ӧ   
	ID_C2S_REQUEST_OPENSENDMAILBOX		 = 0x2002;			// �򿪷����������
	ID_S2C_RESPONSE_OPENSENDMAILBOX		 = 0x2003;			// �򿪷�����Ļ�Ӧ
	ID_C2S_REQUEST_OPENREADMAILBOX		 = 0x2004;			// ���ռ��������
	ID_S2C_RESPONSE_OPENREADMAILBOX		 = 0x2005;			// ���ռ���Ļ�Ӧ 	
	ID_S2C_NOTIFY_MAILERRORCODE			 = 0x2006;			// �ʼ�������
	ID_C2S_REQUEST_CHANGEITEM			 = 0x2007;       	// �޸��ʼ��������ݵ�����	
	ID_S2C_RESPONSE_CHANGEITEM 			 = 0x2008;          // �޸��ʼ��������ݵĻظ�
	ID_C2S_REQUEST_MAILCANSEND           = 0x2009;			// �ʼ��Ƿ���Է���
	ID_S2C_RESPONSE_MAILCANSEND          = 0x200A;			// �ʼ��Ƿ���Է��͵Ļ�Ӧ
	ID_S2S_RESPONSE_PLAYEONLINE			 = 0x200B;			// ����Ƿ�����
	ID_C2S_REQUEST_MAILSEND				 = 0x200C;			// �����ʼ�������
	ID_S2C_RESPONSE_MAILSEND			 = 0x200D;			// �ʼ����͵Ļظ�
	ID_S2C_NOTIFY_MAILLISTINFO			 = 0x200E;			// �����ʼ��б�
	ID_S2C_REQUEST_SHUTMAILBOX		     = 0x200F;			// �ر����������
	ID_C2S_REQUEST_SHUTREADMAILBOX		 = 0x2010;			// �ر��ռ��������
	ID_C2S_REQUEST_SHUTSENDMAILBOX		 = 0x2011;			// �رշ�����
	ID_S2C_NOTIFY_NEWMAIL				 = 0x2212;			// ���ʼ�֪ͨ,·����Ϣ +0x0200
	ID_C2S_REQUEST_READMAIL				 = 0x2013;			// ���ʼ�����
	ID_S2C_RESPONSE_READMAIL			 = 0x2014;			// �ʼ�����	
	ID_C2S_REQUEST_GETACCESSORY			 = 0x2015;			// ��ȡ�ʼ�����						
	ID_C2S_REQUEST_DELMAIL				 = 0x2016;			// ɾ���ʼ�
	ID_C2S_NOTIFY_READMAILEND			 = 0x2017;			// ��ȡ�ʼ����
	ID_C2S_REQUEST_BACKMAIL				 = 0x2018;			// ����
	ID_C2S_REQUEST_LOCKMAIL				 = 0x2019;			// �����ʼ�
	ID_C2S_REQUEST_UNLOCKMAIL			 = 0x201A;			// �����ʼ�
	ID_C2S_REQUEST_GETMAILPAGE			 = 0x201B;			// ��ȡ�ʼ��б� 
	ID_S2C_RESPONSE_DELMAIL				 = 0x201C;			// ɾ���ʼ��Ļ�Ӧ
	ID_S2C_RESPONSE_GETACCESSORY		 = 0x201D;			// ��ȡ�ʼ������Ļ�Ӧ��Ϣ
	ID_S2C_RESPONSE_BACKMAIL			 = 0x201E;			// ���ŵĻ�Ӧ��Ϣ
	ID_C2S_NOTIFY_CANNCELMAILSEND		 = 0x202F;			// ȡ���ʼ�����
	ID_S2C_NOTIFY_MAILBOXSTATUS			 = 0x2030;			// �ʼ�״̬֪ͨ���ʼ���������û�����ʼ�
	ID_C2S_REQUEST_PAYMAILMONEY			 = 0x2031;			// �����ʼ��ĸ�������
	ID_S2C_RESPONSE_PAYMAILMONEY		 = 0x2032;			// �����ʼ��ĸ����Ӧ
};


// *************************************************************************** //
// MailItemBox  
// 
// *************************************************************************** //
message MailItemBox
{
	repeated PBItemObject MailItem		 = 		1; 					// ������Ʒ
	repeated uint32		  ItemIndex		 = 		2; 					// ������Ʒ�ڸ����б��е�����
};

// *************************************************************************** //
// CMessageOpenMailBox  
// ��Ҵ����������
// *************************************************************************** //
message CMessageOpenMailBoxRequest
{
	optional uint32 MsgCode		= 	1; 
	optional uint32	EntityID	=	2;	// npcʵ��ID 		
};

// *************************************************************************** //
// CMessageOpenMailBoxResponse  
// ��Ҵ���������Ļظ�
// *************************************************************************** //
message CMessageOpenMailBoxResponse
{
	optional uint32 Result  = 		1; 
};


// *************************************************************************** //
// CMessageShutDownMailBoxRequest
// ��Ҵ���������Ļظ�
// *************************************************************************** //
message CMessageShutDownMailBoxRequest
{
	optional uint32 MsgCode  = 		1; 
};

// *************************************************************************** //
// CMessageMailChangeItem          ��Ϸ�ͻ���->��Ϸ������
// ���ӻ���ɾ������
// *************************************************************************** //
message CMessageMailChangeItem
{
	optional uint32 ItemNum		  = 		1;    // ������Ʒ������
	optional uint32 SrcIndex      = 		2;    // Դ����	
	optional uint32	MoveMethod	  = 		3; 	// �ƶ���ʽ��0��ʾ�ڰ����͸����б�λ��֮����ƶ���ItemNum>0 ��ʾ�Ӱ�������										//���б� ItemNum=0 ��ʾ�Ӹ����б����� ����1��ʾ�ڸ����б�λ���ϵ��ƶ�
	optional uint32 DesIndex	  = 		4; 	// Ŀ������
};

// *************************************************************************** //
// CMessageMailChangeItemCallBack    ��Ϸ������->��Ϸ�ͻ���
// �ı丽����ķ�����Ϣ
// *************************************************************************** //

message CMessageMailChangeItemCallBack
{
	optional uint32 ItemNum		  = 		1;    // ������Ʒ������
	optional uint32 DesIndex	  = 		2; 	// Ŀ������
	optional uint32	MoveMethod	  = 		3; 	// �ƶ���ʽ��0��ʾ�ڰ����͸����б�λ��֮����ƶ���ItemNum>0 ��ʾ�Ӱ�������											//���б� ItemNum<=0 ��ʾ�Ӹ����б����� ����1��ʾ�ڸ����б�λ���ϵ��ƶ�
	optional uint32 SrcIndex      = 		4;    // Դ����	
};

// *************************************************************************** //
// CMessageMailCanSend ��Ϸ�ͻ���->��Ϸ������
// �ж�����Ƿ�����
// *************************************************************************** //
message CMessageMailCanSend 
{
	optional string Name        =	1;  //�ʼ����շ���ɫ��	
	optional uint32	EntityID	=	2;	// npcʵ��ID 		
};

// *************************************************************************** //
// CMessageMailCanSend ��Ϸ�ͻ���->��Ϸ������
// �ж�����Ƿ�����
// *************************************************************************** //
message CMessageMailCanSendCallBack
{
	optional uint32 CanSendMail      = 		1;                     // 1��ʾ���Է��ͣ�0��ʾ���ܷ���
	optional uint32 PlayerCharID     = 		2;                     // ���charid	
};


// *************************************************************************** //
// CMessageMailSend ��Ϸ�ͻ���-> ��Ϸ������
// �����ʼ�
// *************************************************************************** //

message AccessoryInfo
{
	optional uint32	ItemIndex				 =		1;				// �����ڰ����е�����
	optional uint32	ItemNum					 =		2;				// ��������
	optional uint32	ItemPos					 =		3;				// �ʼ������ڸ����е�λ������		
};
message CMessageMailSend
{
	optional string Body				     = 		1;              // �ʼ�����	
	optional uint32 MoneyNeedBack            = 		2;              // ��Ҫ�Է�֧�����ʼ�����
	optional string DesName					 = 		3; 				// �ʼ����շ�����
	optional uint32 DesCharID                = 		4;              // �ʼ����շ���CharID
	optional string Title				     = 		5;              // �ʼ�����
	optional uint32 Money			         = 		6;              // ���͵Ľ�Ǯ
	optional uint32	EntityID				 =		7;				// npcʵ��ID	
	repeated AccessoryInfo Accessory		 =		8;				// �ʼ�������Ϣ
};

// *************************************************************************** //
// CMessageMailListNotify ��Ϸ������ -> ��Ϸ�ͻ���
// ����ʼ��б�
// *************************************************************************** //

message CMailInfo
{
	optional string Title			 = 		1; 		// ����
	optional uint32 Money			 = 		2;        // ����Я���Ľ�Ǯ
	optional uint32 Sendtime  		 = 		3; 		// ʱ��
	optional uint32 ExpiredTime		 = 		4; 		// ����ʱ��
	optional uint32 MoneyNeedBack	 = 		5; 		// ��Ҫ֧���Ľ�Ǯ
	optional uint32 MailLevel		 = 		6; 		// ��־����ͨ�ʼ��������ʼ���ϵͳ�ʼ���	
	optional uint32 MailType		 = 		7; 		// �ʼ�״̬
	optional uint32 MailID			 = 		8; 		// �ʼ�id
	optional string Srcname 		 = 		9; 		// ������
	optional uint32 ItemNum			 = 		10; 		// ��������	
};

message CMessageMailListNotify
{	
	repeated CMailInfo  MailList    = 		1;  
};

// *************************************************************************** //
// CMessageMailErrorCode ��Ϸ������ -> ��Ϸ�ͻ���
// �ʼ�������Ϣ
// *************************************************************************** //
message CMessageMailErrorCode
{
	optional int32 ErrorCode  = 		1; 
};
// *************************************************************************** //
// CMessageShutDownMailBoxRequest ��Ϸ�ͻ���->��Ϸ������
// �ر�����
// *************************************************************************** //
message CMessageShutMailBoxRequest
{
	optional uint32 MsgCode  = 		1; 	
};

// *************************************************************************** //
// CMessageShutReadMailBoxRequest ��Ϸ�ͻ���->��Ϸ������
// �ر��ռ���
// *************************************************************************** //
message CMessageShutReadMailBoxRequest
{
	optional uint32 MsgCode  = 		1; 
};

// *************************************************************************** //
// CMessageShutSendMailBoxRequest ��Ϸ�ͻ���->��Ϸ������
// �رշ�����
// *************************************************************************** //
message CMessageShutSendMailBoxRequest
{
	optional uint32 MsgCode  = 		1; 
};

// *************************************************************************** //
// CMessageMailNewNotify ��Ϸ������ -> ��Ϸ�ͻ���
// ���ʼ�֪ͨ,������Ϣ
// *************************************************************************** //
message CMessageNewMailNotify
{		
	optional CMessageRouter Router  = 		1;  	// ·����Ϣ	
	optional uint32		HasList	    = 		2; 		// �Ƿ����ʼ�������Ϣ1��ʾ�У�0��ʾû��		
	optional CMailInfo  MailList    = 		3; 		// �ʼ�������Ϣ
};
// *************************************************************************** //
// CMessageMailRead ��Ϸ�ͻ���-> ��Ϸ������
// �õ��ʼ�������Ϣ
// *************************************************************************** //
message CMessageMailRead
{	
	optional uint32 MailID		= 	1;		// �ʼ�ID
	optional uint32	EntityID	=	2;		// ʵ��ID
};

// *************************************************************************** //
// CMessageMailReadCallBack ��Ϸ������->��Ϸ�ͻ���
// ����ʼ�������Ϣ
// *************************************************************************** //
message CMessageMailReadResponse
{	
	optional uint32 MailID					 = 		1; 		// �ʼ�ID
	optional string MailBody                 = 		2;         // �ʼ�����
	repeated uint32  MailItemIndex			 = 		3; 		// �����ڸ����б��е�����
	repeated PBItemObject Accessory          = 		4;         // ����
};

// *************************************************************************** //
// CMessageGetMailAccessory  ��Ϸ�ͻ���->��Ϸ������
// ��ȡ�ʼ�����
// *************************************************************************** //
message CMessageGetAccessory
{
	optional uint32 MailID       = 		1; 		// �ʼ�ID
	optional uint32 ItemIndex    = 		2; 		// ������Ʒ����
	optional uint32 IsMoney		 = 		3; 		// �ǲ��ǽ�Ǯ
	optional uint32	EntityID	 =		4;		// ʵ��ID		
}; 

// *************************************************************************** //
// CMessageMailReadCallBack ��Ϸ������->��Ϸ�ͻ���
// ����ʼ�������Ϣ
// *************************************************************************** //
message CMessageDelMail
{						
	optional uint32 MailId		 =	1;	// �ʼ�ID
	optional uint32 EntityID	 =	2;	// ʵ��ID		
};


// *************************************************************************** //
// CMessageReadMailEnd ��Ϸ�ͻ���->��Ϸ������
// ��ȡ�ʼ����
// *************************************************************************** //
message CMessageReadMailEnd
{
	optional uint32 MailID			 = 	1; 	// �ʼ�ID	
};

// *************************************************************************** //
// CMessageBackMail  ��Ϸ�ͻ���->��Ϸ������
// ����
// *************************************************************************** //
message CMessageBackMail
{
	optional string MailBody	=	1; 				// ���ŵ��ʼ�����
	optional uint32 MailID		=	2; 				// �ʼ�ID
	optional uint32 EntityID	=	3;				// ʵ��ID			
};

// *************************************************************************** //
// CMessageDelMailResponse  ��Ϸ������->��Ϸ�ͻ���
// ɾ���ʼ��Ļ�Ӧ��Ϣ
// *************************************************************************** //
message CMessageDelMailResponse
{
	optional uint32  MailID      = 		1; 			// �ʼ�ID			 	
};

// *************************************************************************** //
// CMessageGetAccessoryResponse  ��Ϸ������->��Ϸ�ͻ���
// ��ȡ�ʼ���������Ϣ��Ӧ
// *************************************************************************** //
message CMessageGetAccessoryResponse
{
	optional uint32 ItemIndex    = 		1; 		// ������Ʒ����
	optional uint32 MailID       = 		2; 		// �ʼ�ID	
	optional uint32 IsMoney		 = 		3; 		// �ǲ��ǽ�Ǯ
	optional uint32 IfDelMail	 = 		4; 		// �Ƿ�ɾ���ʼ�1��ʾɾ���ʼ�0��ʾ����ɾ��		 	
};

// *************************************************************************** //
// CMessageBackMailResponse  ��Ϸ������->��Ϸ�ͻ���
// ���ŵĻ�Ӧ��Ϣ
// *************************************************************************** //
message CMessageBackMailResponse
{
	optional uint32 MailID       = 		1; 		// �ʼ�ID	
};


// *************************************************************************** //
// CMessageCannelMailSend  ��Ϸ������->��Ϸ�ͻ���
// ȡ���ʼ����͵���Ϣ
// *************************************************************************** //
message CMessageCannelMailSend
{
	optional uint32 MailID		=	1;	// �ʼ�ID	
};


/*���µ���Ϣ������*/


// *************************************************************************** //
// CMessageLockMail  ��Ϸ�ͻ���->��Ϸ������
// �����ʼ�
// *************************************************************************** //
message CMessageLockMail
{	
	optional uint32 MailID			 = 		1; 				// �ʼ�ID	
};

// *************************************************************************** //
// CMessageUnLockMail  ��Ϸ�ͻ���->��Ϸ������
// �����ʼ�
// *************************************************************************** //
message CMessageUnLockMail
{
	optional uint32 MailID			 = 		1; 				// �ʼ�ID	
};

// *************************************************************************** //
// CMessageGetMailPageRequest  ��Ϸ�ͻ���->��Ϸ������
// �ͻ��˵Ļ�ҳҪ��
// *************************************************************************** //
message CMessageGetMailPageRequest
{
	optional uint32  ClientCode      = 		1; 				 	
};



// *************************************************************************** //
// CMessageOpenSendMailBox
// ��Ҵ��ͼ��������
// *************************************************************************** //
message CMessageOpenSendMailBox
{
	optional uint32 MsgCode  = 		1; 
};

// *************************************************************************** //
// CMessageOpenSendMailBoxResponse
// ��Ҵ��ͼ���Ļ�Ӧ
// *************************************************************************** //
message CMessageOpenSendMailBoxResponse
{
	optional uint32 Result  = 		1; 
};

// *************************************************************************** //
// CMessageOpenReadMailBox 
// ���ռ��������
// *************************************************************************** //
message CMessageOpenReadMailBox
{
	optional uint32 MsgCode  = 		1; 
};

// *************************************************************************** //
// CMessageOpenReadMailBoxResponse
// ���ռ���Ļ�Ӧ
// *************************************************************************** //
message CMessageOpenReadMailBoxResponse
{
	optional uint32 Result  = 		1; 
};

// *************************************************************************** //
// CMessageMailBoxStatusNotify
// �ʼ���ʼ״̬��ѯ
// *************************************************************************** //
message CMessageMailBoxStatusNotify
{
	optional uint32 MailCount   = 		1; 					// �ʼ�����������ڿͻ����ܹ���ʾ������
	optional uint32 NewMailCount  = 		2; 				// ���ʼ�������
};

// *************************************************************************** //
// CMessageMailBoxStatusNotify
// �����ʼ��ĸ�������
// *************************************************************************** //
message CMessagePayMailMoneyRequest
{
	optional uint32 MailID 	=	1;
};	

// *************************************************************************** //
// CMessagePayMoneyResponse
// �����ʼ��ĸ����Ӧ
// *************************************************************************** //
message CMessagePayMailMoneyResponse
{
	optional uint32	Errcode			=	1;		// ������
	optional uint32	ExpiredTime		=	2;		// ����ʱ��
	optional uint32	MailID			=	3;		// �ʼ�ID
};	
