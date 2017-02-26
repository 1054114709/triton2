import "property_pb.hxx";
import "coremessage_pb.hxx";
// ������ٶ�����/������
option optimize_for = SPEED;

enum MarriageMessageID
{
	MARRIAGE_MESSAGE = 0x5C00;
	ID_C2S_REQUEST_APPLYMARRY				= 0x5C01;		// ���������Ϣ����
	ID_S2C_RESPONSE_APPLYMARRY				= 0x5C02;		// ���������Ϣ��Ӧ
	
	ID_S2C_NOTIFY_MARRYREQUEST				= 0x5C03;		// ���������Ϣ֪ͨ
	ID_C2S_REQUEST_REPLYMARRY				= 0x5C04;		// �𸴽�����Ϣ����
	ID_S2C_RESPONSE_REPLYMARRY				= 0x5C05;		// �𸴽�����Ϣ��Ӧ
	
	ID_S2C_NOTIFY_MARRIAGETIPS				= 0x5C06;		// ��������
	
	ID_C2S_REQUEST_BEGINWEDDING				= 0x5C07;		// ��ʼ�������Ϣ����
	ID_S2C_RESPONSE_BEGINWEDDING			= 0x5C08;		// ��ʼ�������Ϣ��Ӧ	
	
	ID_S2C_NOTIFY_BEGINWEDDING	 			= 0x5C09;		// �����һ������ʼ�����֪ͨ

	ID_C2S_REQUEST_REPLYBEGINWEDDING		= 0x5C0A;		// ����ż��ʼ�������Ϣ����
	ID_S2C_RESPONSE_REPLYBEGINWEDDING		= 0x5C0B;		// ����ż��ʼ�������Ϣ��Ӧ	
	
	ID_S2C_NOTIFY_WEDDINGSTART				= 0x5C0C;		// ����ʼ��֪ͨ(ȫ��֪ͨ)	
	
	ID_S2C_NOTIFY_ENTERMARRIAGEHALL			= 0x5C0D;		// �������õ�֪ͨ
	ID_C2S_REQUEST_REPLYENTERMARRIAGEHALL	= 0x5C0E;		// �Ƿ�ͬ��������õĴ�����
	ID_S2C_RESPONSE_REPLYENTERMARRIAGEHALL	= 0x5C0F;		// �Ƿ�ͬ��������õĴ𸴻�Ӧ
	
	ID_C2S_REQUEST_NEWLYWEDENTERHALL		= 0x5C10;		// ��������������õ���Ϣ����
	ID_S2C_RESPONSE_NEWLYWEDENTERHALL		= 0x5C11;		// ��������������õ���Ϣ��Ӧ
	
	ID_C2S_REQUEST_GUESTENTERHALL			= 0x5C12;		// ӵ��������������������õ���Ϣ����	
	ID_S2C_RESPONSE_GUESTENTERHALL			= 0x5C13;		// ӵ��������������������õ���Ϣ��Ӧ
	
	ID_C2S_REQUEST_BAITANG					= 0x5C14;		// ���˰��õ�����
	ID_S2C_RESPONSE_BAITANG					= 0x5C15;		// ���˰��õĻ�Ӧ
	
	ID_S2C_NOTIFY_BAITANG					= 0x5C16;		// ���˰��õ���Ϣ֪ͨ		
	
	ID_C2S_REQUEST_PUTKEEPSAKE				= 0x5C17;		// �����������Ϣ����
	ID_S2C_RESPONSE_PUTKEEPSAKE				= 0x5C18;		// �����������Ϣ��Ӧ
			
	ID_C2S_REQUEST_EXCHANGKEEPSAKE			= 0x5C19;		// �������������
	ID_S2C_RESPONSE_EXCHANGKEEPSAKE			= 0x5C1A;		// ��������Ļ�Ӧ��Ϣ
	
	ID_S2C_NOTIFY_EXCHANGEKEEPSAKE			= 0x5C1B;		// ���������֪ͨ
	
	ID_C2S_REQUEST_DIVORCE					= 0x5C1C;		// ������Ϣ����
	ID_S2C_RESPONSE_DIVORCE					= 0x5C1D;		// ������Ϣ��Ӧ
	
	ID_S2C_NOTIFY_DIVORCE					= 0x5C1E;		// ������Ϣ֪ͨ	
	
	ID_S2C_NOTIFY_MARRYRESULT				= 0x5C1F;		// �����֪ͨ(�Է��Ƿ�ͬ��)
	
	ID_S2C_NOTIFY_BEGINWEDINGRESULT			= 0x5C20;		// ��ʼ����Ľ��֪ͨ(��ż�Ƿ�ͬ��)
	
	ID_C2S_REQUEST_GETCAMPMARRAIGEINFO		= 0x5C21;		// ����Ӫ������Ϣ����Ϣ����	
	ID_S2C_RESPONSE_GETCAMPMARRIAGEINFO		= 0x5C22;		// ����Ӫ������Ϣ����Ϣ��Ӧ	
	
	ID_S2C_NOTIFY_PERSONMARRIED				= 0x5C23;		// ��ȫ�����ͽ��֪ͨ	
	
	ID_S2C_NOTIFY_PERSONMARRIAGEINFO		= 0x5C24;		// ���˵Ļ�����Ϣ֪ͨ
	
	ID_S2C_NOTIFY_SPOUSEDIVORCE				= 0x5E25;		// ��ż����֪ͨ 0x0200 
	
	ID_C2S_REQUEST_USESYSINVITATION			= 0x5C26;		// ʹ��ϵͳ����������
	ID_S2C_RESPONSE_USESYSINVITATION		= 0x5C27;		// ʹ��ϵͳ��������Ϣ��Ӧ
	
	ID_S2C_NOTIFY_TIMETOPUTKEEPSAKE			= 0x5C28;		// ���Է��������֪ͨ
	
	ID_C2S_REQUEST_CANCELWEDDING			= 0x5C29;		// ȡ�����������
	ID_S2C_RESPONSE_CANCELWEDDING			= 0x5C30;		// ȡ���������Ϣ��Ӧ	
	
	ID_S2C_NOTIFY_NEWLYMARRIED				= 0x5C31;		// ���˽���֪ͨ
		
	ID_S2C_NOTIFY_WEDDINGEND				= 0x5C32;		// ���������֪ͨ
	
	ID_C2S_REQUEST_STARTKEEPSAKEEXCHANGE	= 0x5C33;		// ��ʼ����һ�����Ϣ����	
	ID_S2C_RESPONSE_STARTKEEPSAKEEXCHANGE	= 0x5C34;		// ��ʼ����һ�����Ϣ��Ӧ	
	ID_C2S_REQUEST_STOPKEEPSAKEEXCHANGE		= 0x5C35;		// ��ֹ����һ�����Ϣ����
	ID_S2C_RESPONSE_STOPKEEPSAKEEXCHANGE	= 0x5C36;		// ��ֹ����һ�����Ϣ��Ӧ
	ID_S2C_NOTIFY_STOPKEEPSAKEEXCHANGE		= 0x5C37;		// ��ֹ����һ�����Ϣ֪ͨ
	ID_C2S_REQUEST_INVITATIONEXCHANGE		= 0x5C38;		// �����һ�����Ϣ����
	ID_S2C_RESPONSE_INVITATIONEXCHANGE		= 0x5C39;		// �����һ�����Ϣ��Ӧ
	
	ID_S2C_NOTIFY_EXCHANGERESULT			= 0x5C3A;		// �����һ��Ľ��	
	
	ID_C2S_REQUEST_TELETOWEDDINGNPC			= 0x5C3B;		// ���͵�����npc��������Ϣ
	ID_S2C_RESPONSE_TELETOWEDDINGNPC		= 0x5C3C;		// ���͵�����npc����Ϣ��Ӧ
	
	ID_C2S_REQUEST_REVIEWWEDDING			= 0x5C3D;		// �������»������Ϣ����
	ID_S2C_RESPONSE_REVIEWWEDDING			= 0x5C3E;		// �������»������Ϣ��Ӧ
	ID_S2C_NOTIFY_REVIEWWEDDING				= 0x5C3F;		// �������»������Ϣ֪ͨ
};


// ********************************************************************** //
// CMessageApplyMarryRequest	ID_C2S_REQUEST_APPLYMARRY
// ���������Ϣ����
// ********************************************************************** //
message CMessageApplyMarryRequest
{
	optional uint32	TimeID				=	1;	// ʱ��ID
	optional uint32	WeddingModule		=	2;	// �����ģ( 0:��ͨ 1:���� 2:���� )
	optional uint32	DayID				=	3;	// �����ģ( 0:���� 1:���� 2:���� )
	optional uint32	HoldWedding			=	4;	// �Ƿ���л���(1��ʾ�ǣ�0��ʾ��)
	optional uint32	EntityID			=	5;	// ����npc��ʵ��ID
};

// ********************************************************************** //
// CMessageApplyMarryResponse	ID_S2C_RESPONSE_APPLYMARRY
// ���������Ϣ��Ӧ
// ********************************************************************** //
message CMessageApplyMarryResponse
{
	optional uint32	Errcode		=	1;			// ������
};



// ********************************************************************** //
// CMessageMarryRequestNotify		 ID_S2C_NOTIFY_MARRYREQUEST
// ���������Ϣ֪ͨ
// ********************************************************************** //
message CMessageMarryRequestNotify
{ 
	optional uint32	RoleID				=	1;		// ��������˵Ľ�ɫID
	optional string RoleName			=	2;		// ��������˵Ľ�ɫ����
	optional uint32	Year				=	3;		// ��
	optional uint32	Month				=	4;		// ��
	optional uint32	Day					=	5;		// ��
	optional uint32	BeginTime			=	6;		// ��ʼʱ��(����)	
	optional uint32	WeddingModule		=	7;		// ����Ĺ�ģ		
};


// ********************************************************************** //
// CMessageReplyMarryRequest	ID_C2S_REQUEST_REPLYMARRY
// �𸴽�����Ϣ����
// ********************************************************************** //
message CMessageReplyMarryRequest
{
	optional uint32	Result		= 1;	// �𸴽�� 1��ʾͬ���� 0��ʾ��ͬ��
	optional uint32	EntityID	= 2;	// npc��ʵ��ID
};

// ********************************************************************** //
// CMessageReplyMarryResponse	  ID_S2C_RESPONSE_REPLYMARRY
// �𸴽�����Ϣ��Ӧ
// ********************************************************************** //
message  CMessageReplyMarryResponse
{
	optional uint32	Errcode				=	1;	// ������
	optional uint32	Result				=	2;	// �Ƿ�ͬ���� 1��ʾͬ�� 0��ʾ��ͬ��
	optional string SpouseName			=	3;	// ��ż����
	optional uint32	MarriageStatus		=	4;	// ���״̬
};

// ********************************************************************** //
// CMessageMarriageTipsNotify	  ID_S2C_NOTIFY_MARRIAGETIPS
// ��������
// ********************************************************************** //
message CMessageMarriageTipsNotify
{
	optional uint32 WeddingTime		=	1;		// �������	
	optional uint32	WeddingStatus	=	2;		// ����״̬(EM_WeddingStatus)
};

// ********************************************************************** //
// CMessageBeginWeddingRequest		 ID_C2S_REQUEST_BEGINWEDDING
// ��ʼ�������Ϣ����
// ********************************************************************** //
message  CMessageBeginWeddingRequest
{
	optional uint32	EntityID	=	1;	// npcʵ��ID	
};

// ********************************************************************** //
// CMessageBeginWeddinResponse		ID_S2C_RESPONSE_BEGINWEDDING
// ��ʼ�������Ϣ��Ӧ
// ********************************************************************** //
message CMessageBeginWeddingResponse
{
	optional uint32	Errcode	=	1;
};

// ********************************************************************** //
// CMessageBeginWeddingNotify	   ID_S2C_NOTIFY_BEGINWEDDING
// �����һ������ʼ�����֪ͨ
// ********************************************************************** //
message CMessageBeginWeddingNotify
{
	
};

// ********************************************************************** //
// CMessageReplyBeginWeddingRequest
// ����ż��ʼ�������Ϣ����
// ********************************************************************** //
message CMessageReplyBeginWeddingRequest
{
	optional uint32	 Result	=	1;					// �𸴽��1��ʾͬ��0��ʾ��ͬ��
	optional uint32	 EntityID = 2;					// npc��ʵ��ID
};

// ********************************************************************** //
// CMessageReplyBeginWeddingResponse
// ����ż��ʼ�������Ϣ��Ӧ
// ********************************************************************** //
message CMessageReplyBeginWeddingResponse
{
	optional uint32	Errcode	=	1;				// ������
};	

// ********************************************************************** //
// CMessageWeddingStartNotify
// ����ʼ��֪ͨ(ȫ��֪ͨ)
// ********************************************************************** //
message CMessageWeddingStartNotify
{	
	optional string GroomName				= 1;	// ��������
	optional string BrideName				= 2;	// ��������
	optional uint32	WeddingTimeLength		= 3;	// ����ʱ��
	optional uint32	WeddingModule			= 4;	// �����ģ
	optional uint32	GroomID					= 5;	// ���ɽ�ɫID
	optional uint32	BrideID					= 6;	// �����ɫID
	optional uint32	CampID					= 7;	// ��ӪID
};	

// ********************************************************************** //
// CMessageEnterMarriageHallNotify
// �������õ�֪ͨ
// ********************************************************************** //
message  CMessageEnterMarriageHallNotify
{
	
};

// ********************************************************************** //
// CMessageReplyEnterMarriageHallRequest
// �Ƿ�ͬ��������õĴ�����
// ********************************************************************** //
message CMessageReplyEnterMarriageHallRequest
{		
	optional uint32	Result = 1;			// ���1��ʾͬ��0��ʾ��ͬ��	
};

// ********************************************************************** //
// CMessageReplyEnterMarriageHallResponse
// �Ƿ�ͬ��������õĴ𸴻�Ӧ
// ********************************************************************** //
message CMessageReplyEnterMarriageHallResponse
{
	optional uint32	Errcode	=	1;		// ������	
};

// ********************************************************************** //
// CMessageNewlyEnterHallRequest
// ��������������õ���Ϣ����
// ********************************************************************** //
message CMessageNewlyEnterHallRequest
{
	optional uint32	EntityID	=	1;	// npcʵ��ID	
};

// ********************************************************************** //
// CMessageNewlyEnterHallResponse
// ��������������õ���Ϣ��Ӧ
// ********************************************************************** //
message CMessageNewlyEnterHallResponse
{
	optional uint32	Errcode			=	1;	// ������
	optional uint32	WeddingModule	=	2;	// �����ģ
	optional uint32	BaitangEnd		=	3;	// �Ƿ��Ѿ��ݹ��ã�1��ʾ�ݹ�0��ʾû�аݹ�
};

// ********************************************************************** //
// CMessageGuestEnterHallRequest
// ӵ��������������������õ���Ϣ����
// ********************************************************************** //
message CMessageGuestEnterHallRequest
{
	optional uint32	EntityID	=	1;		// npc��ʵ��ID			
};
	
// ********************************************************************** //
// CMessageGuestEnterHallResponse
// ӵ��������������������õ���Ϣ��Ӧ
// ********************************************************************** //
message CMessageGuestEnterHallResponse
{
	optional uint32 Errcode	=	1;			// ������	
}	

// ********************************************************************** //
// CMessageBaitangRequest
// ���˰��õ�����
// ********************************************************************** //
message CMessageBaitangRequest
{
	optional uint32	EntityID = 1;	// npc��ʵ��ID
};

// ********************************************************************** //
// CMessageBaitangResponse
// ���˰��õĻ�Ӧ
// ********************************************************************** //
message CMessageBaitangResponse
{
	optional uint32	Errcode	=	1;	// ������
};

// ********************************************************************** //
// CMessageBaitangNotify
// ���˰��õ�֪ͨ
// ********************************************************************** //
message CMessageBaitangNotify
{
	optional string GroomName			=	1;		// ��������
	optional string	BrideName			=	2;		// ��������
	optional uint32	GroomEntityID		=	3;		// ���ɵ�ʵ��ID
	optional uint32 BrideEntityID		=	4;		// �����ʵ��ID
};		

// ********************************************************************** //
// CMessagePutKeepSakeRequest
// �����������Ϣ����
// ********************************************************************** //
message CMessagePutKeepSakeRequest
{	
	optional uint32	 KeepsakeIndex = 1;		// �������� -1��ʾȡ������
};

// ********************************************************************** //
// CMessagePutKeepSakeResponse
// �����������Ϣ��Ӧ
// ********************************************************************** //
message CMessagePutKeepSakeResponse
{	
	optional uint32	 Errcode = 1;		// ������
	optional uint32	 Index	 = 2;		// �������� 
};


// ********************************************************************** //
// CMessageExchangeKeepsakeRequest
// �������������
// ********************************************************************** //
message CMessageExchangeKeepsakeRequest
{
		
};

// ********************************************************************** //
// CMessageExchangeKeepsakeResponse
// ��������Ļ�Ӧ
// ********************************************************************** //
message CMessageExchangeKeepsakeResponse
{
	optional uint32	Errcode	= 1;		// ������
};

// ********************************************************************** //
// CMessageExchangeKeepsakeNotify
// ���������֪ͨ
// ********************************************************************** //
message CMessageExchangeKeepsakeNotify
{	
	optional string GroomName				= 1;	// ��������
	optional PBItemObject BrideKeepsake		= 2;	// �����͸����ɵ�����
	optional string BrideName				= 3;	// ��������
	optional PBItemObject GroomKeepsake		= 4;	// �����͸����������
};


// ********************************************************************** //
// CMessageDivorceRequest
// ������Ϣ����
// ********************************************************************** //
message CMessageDivorceRequest
{
	optional uint32	EntityID	=	1;		// npc��ʵ��ID
};
		 
// ********************************************************************** //
// CMessageDivorceResponse
// ������Ϣ����
// ********************************************************************** //
message CMessageDivorceResponse
{
	optional uint32	Errcode	=	1;	// ������
};

// ********************************************************************** //
// CMessageDivorceResponse
// ������Ϣ����
// ********************************************************************** //
message CMessageDivorceNotify
{		
	optional string GroomName		=	1;	// ��������
	optional uint32	GroomCharID		=	2;	// ���ɽ�ɫID
	optional string BrideName		=	3;	// ��������
	optional uint32	BrideCharID		=	4;	// ����Ľ�ɫID	
};

// ********************************************************************** //
// CMessageMarryResultNotify
// �����֪ͨ(�Է��Ƿ�ͬ��)
// ********************************************************************** //
message CMessageMarryResultNotify
{
	optional uint32	Result				= 1;	// �Ƿ�ͬ���� 1��ʾͬ�� 0��ʾ��ͬ��
	optional string SpouseName			= 2;	// ��ż����
	optional uint32	MarriageStatus		= 3;	// ���״̬
	optional uint32	WeddingTime			= 4;	// ����ʱ��
};

// ********************************************************************** //
// CMessageBeginWeddingResultNofiy
// ��ʼ����Ľ��֪ͨ(��ż�Ƿ�ͬ��)
// ********************************************************************** //
message CMessageBeginWeddingResultNofiy
{
	optional uint32	Result		= 1;	// ��ż�Ƿ�ͬ����� 1��ʾͬ�� 0��ʾ��ͬ��
	optional string SpouseName	= 2;	// ��ż����
};

// ********************************************************************** //
// CMessageGetCampMarriageInfoRequest
// ����Ӫ������Ϣ����Ϣ����
// ********************************************************************** //	
message CMessageGetCampMarriageInfoRequest
{		
	optional uint32	EntityID	=	1;	// npc��ʵ��ID	
};

// ********************************************************************** //
// CMessageGetCampMarriageInfoResponse
// ����Ӫ������Ϣ����Ϣ��Ӧ
// ********************************************************************** //
message PBMarriageInfo	
{ 
	optional string GroomName			=	1;		// ��������
	optional string BrideName			=	2;		// ��������	
	optional uint32	WeddingTime			=	3;		// ����ľ���ʱ��
	optional uint32	WeddingEndTime		=	4;		// ����Ľ���ʱ��  
	optional uint32	CommoAllowed		=	5;		// �Ƿ��ܹ�������ͨ����1��ʾ��0��ʾ��
	optional uint32	TimeUsed			=	6;		// ��ʱ����Ƿ��Ѿ�����1��ʾ���ù�0��
	optional uint32	TimeID				=	7;		// ��ʱ��ε�ID	
};

message PBMarriageList
{
	repeated PBMarriageInfo MarriageInfo	=	1;		// ���챾��Ӫ�Ļ�����Ϣ
	optional uint32	Year					=	2;		// ��
	optional uint32	Month					=	3;		// ��
	optional uint32	Day						=	4;		// ��
};

message CMessageGetCampMarriageInfoResponse
{
	optional PBMarriageList	MarriageListA	=	1;		// ���챾��Ӫ�Ļ�����Ϣ
	optional PBMarriageList MarriageListB	=	2;		// ���챾��Ӫ�Ļ�����Ϣ
	optional PBMarriageList MarriageListC	=	3;		// ���챾��Ӫ�Ļ�����Ϣ		
};

// ********************************************************************** //
// CMessagePersonMarriedNotify
// ��ȫ�����ͽ��֪ͨ
// ********************************************************************** //	
message CMessagePersonMarriedNotify
{
	optional string GroomName			= 1;			// ��������
	optional string BrideName			= 2;			// ��������
	optional uint32	ServerSequence		= 3;			// �������ڼ���
};

// ********************************************************************** //
// CMessagePersonMarriageInfoNotify
// ���˵Ļ�����Ϣ֪ͨ
// ********************************************************************** //
message CMessagePersonMarriageInfoNotify
{
	optional string SpouseName		=	1;		// ��ż����
	optional uint32	MarriageStatus	=	2;		// ����״̬
	optional uint32	WeddingTime		=	3;		// ����Ŀ�ʼʱ��
	optional uint32	RoleID			=	4;		// ��ɫID
};

// ********************************************************************** //
// CMessageSpouseDivorceNotify
// ��ż����֪ͨ
// ********************************************************************** //
message CMessageSpouseDivorceNotify
{
	optional CMessageRouter Router  =	1;    	
};

// ********************************************************************** //
// CMessageUseSysInvitationRequest
// ʹ��ϵͳ����������
// ********************************************************************** //
message CMessageUseSysInvitationRequest
{
	optional uint32	ItemIndex		= 1;		// ϵͳ����������
	optional string	ReceivedName	= 2;		// ���������˵�����
	optional uint32	ReceivedID		= 3;		// ���������˵Ľ�ɫID
};

// ********************************************************************** //
// CMessageUseSysInvitationResponse
// ʹ��ϵͳ����������
// ********************************************************************** //
message CMessageUseSysInvitationResponse
{
	optional uint32	Errcode	=	1;		// ������
};

// ********************************************************************** //
// CMessageTimetoPutKeepsakeNotify
// ���Է��������֪ͨ
// ********************************************************************** //
message CMessageTimeToPutKeepsakeNotify
{ 
	optional uint32	 GroomRoleID = 1;		// ���ɽ�ɫID
	optional uint32	 BrideRoleID = 2;		// �����ɫID	
};

// ********************************************************************** //
// CMessageCancelWeddingRequest
// ȡ�����������
// ********************************************************************** //
message CMessageCancelWeddingRequest
{
	optional uint32 EntityID = 1;		// npcʵ��ID	
};

// ********************************************************************** //
// CMessageCancelWeddingRequest
// ȡ���������Ϣ��Ӧ
// ********************************************************************** //
message CMessageCancelWeddingResponse
{
	optional uint32 Errcode	= 2;		// ȡ���������Ϣ��Ӧ 
};
	
// ********************************************************************** //
// CMessageNewlyMarriedNotify
// ���˽���֪ͨ ȫ������ȫ��Ӫ֪ͨ
// ********************************************************************** //
message CMessageNewlyMarriedNotify
{
	optional string  BrideName			= 1;		// ��������
	optional string	 GroomName			= 2;		// ��������
	optional uint32	 WeddingTime		= 3;		// ����ʱ��
	optional uint32	 WeddingTimeLength	= 4;		// ����ʱ��
	optional uint32	 WeddingModule		= 5;		// �����ģ	 0 ��ͨ 1 ���� 2 ����
	optional uint32	 CampID				= 6;		// ��ӪID
	optional uint32	 SeverSequence		= 7;		// ȫ���ڼ�������
	optional uint32	 BrideID			= 8;		// ����ID
	optional uint32	 GroomID			= 9;		// ����ID
};

// ********************************************************************** //
// CMessageWeddingEndNotify
// ���������֪ͨ
// ********************************************************************** //
message CMessageWeddingEndNotify
{
	
};

// ********************************************************************** //
// CMessageStartKeepsakeExchangeRequest
// ��ʼ���ｻ������Ϣ����
// ********************************************************************** //
message CMessageStartKeepsakeExchangeRequest
{
	optional uint32	EntityID	=	1;	
};

// ********************************************************************** //
// CMessageStartKeepsakeExchangeResponse
// ��ʼ����һ�����Ϣ��Ӧ
// ********************************************************************** //
message CMessageStartKeepsakeExchangeResponse
{
	optional uint32	 Errcode = 1;		
};

// ********************************************************************** //
// CMessageStopKeepsakeExchangeRequest
// ��ֹ����һ�����Ϣ����
// ********************************************************************** //
message CMessageStopKeepsakeExchangeRequest
{
	
};

// ********************************************************************** //
// CMessageStopKeepsakeExchangeResponse
// ��ֹ����һ�����Ϣ��Ӧ
// ********************************************************************** //
message CMessageStopKeepsakeExchangeResponse
{
	optional uint32 Errcode = 1;
};

// ********************************************************************** //
// CMessageStopKeepsakeExchangeNotify
// ��ֹ����һ�����Ϣ֪ͨ
// ********************************************************************** //
message CMessageStopKeepsakeExchangeNotify
{	
		
};

// ********************************************************************** //
// CMessageInvitationExchangeRequest
// �����һ�����Ϣ����
// ********************************************************************** //
message CMessageInvitationExchangeRequest
{
	optional uint32	ItemIndex = 1;		// ��Ʒ����
	optional uint32	EntityID  = 2;		// npc��ʵ��ID	
};

// ********************************************************************** //
// CMessageInvitationExchangeResponse
// �����һ�����Ϣ��Ӧ
// ********************************************************************** //
message CMessageInvitationExchangeResponse
{
	optional uint32	Errcode = 1;		// ��Ʒ����
};

// ********************************************************************** //
// CMessageExchangeResultNotify
// ����һ��Ľ��֪ͨ
// ********************************************************************** //
message CMessageExchangeResultNotify
{
	optional uint32	GroomRoleID = 1;	// ���ɽ�ɫID
	optional uint32	BrideRoleID = 2;	// �����ɫID
	optional uint32	GroomItemID	= 3;	// ���ɸ��������ƷID
	optional uint32	BrideItemID = 4;	// ��������ɵ���ƷID
	optional string	BrideName	= 5;	// ��������
	optional string GroomName	= 6;	// ��������
};

// ********************************************************************** //
// CMessageTeleToWeddingNpcRequest
// ���͵����npc����Ϣ����
// ********************************************************************** //
message CMessageTeleToWeddingNpcRequest
{
	
};

// ********************************************************************** //
// CMessageTeleToWeddingNpcRequest
// ���͵����npc����Ϣ����
// ********************************************************************** //
message CMessageTeleToWeddingNpcResponse
{
	optional uint32	 Errcode = 1;
};

// ********************************************************************** //
// CMessageReviewWeddingRequest
// �������»������Ϣ����
// ********************************************************************** //
message CMessageReviewWeddingRequest
{
	optional uint32	TimeID				=	1;	// ʱ��ID
	optional uint32	WeddingModule		=	2;	// �����ģ( 0:��ͨ 1:���� 2:���� )
	optional uint32	DayID				=	3;	// �����ģ( 0:���� 1:���� 2:���� )	
	optional uint32	EntityID			=	4;	// ����npc��ʵ��ID
};

// ********************************************************************** //
// CMessageTeleToWeddingNpcRequest
// �������»������Ϣ��Ӧ
// ********************************************************************** //
message CMessageReviewWeddingResponse
{
	optional uint32	 Errcode		   =	6;
};

// ********************************************************************** //
// CMessageTeleToWeddingNpcRequest
// �������»������Ϣ֪ͨ
// ********************************************************************** //
message CMessageReviewWeddingNotify
{
	optional string  BrideName			= 1;		// ��������
	optional string	 GroomName			= 2;		// ��������
	optional uint32	 WeddingTime		= 3;		// ����ʱ��
	optional uint32	 WeddingTimeLength	= 4;		// ����ʱ��
	optional uint32	 WeddingModule		= 5;		// �����ģ	 0 ��ͨ 1 ���� 2 ����
	optional uint32	 CampID				= 6;		// ��ӪID	
	optional uint32	 BrideID			= 7;		// ����ID
	optional uint32	 GroomID			= 8;		// ����ID
};