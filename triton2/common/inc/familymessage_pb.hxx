import "familydbinfo_pb.hxx";
// ������ٶ�����/������
option optimize_for = SPEED;

enum FamilyMessageID
{
	ID_C2S_REQUEST_CREATFAMILY				= 	0x3400;			// �������������
	ID_S2C_RESPONSE_CREATFAMILY				=   0x3401;			// ��������Ļ�Ӧ 
											
	ID_C2S_REQUEST_INVITEMEMBER				=	0x3402;			// ������Ҽ������
	ID_S2C_RESPONSE_INVITEMEMBER			=	0x3403;			// �������Ļ�Ӧ
	ID_S2C_NOTIY_FAMILYINVITED				=	0x3404;			// �����������֪ͨ	
	ID_C2S_REQUEST_REPLYFAMILYINVITE		=	0x3405;			// �𸴼������������
	ID_S2C_RESPONSE_REPLYFAMILYINVITE		=	0x3406;			// �𸴼�������Ļظ�
	ID_S2C_NOTIFY_INVITERESULT				=	0x3407;			// ��������֪ͨ
											
	ID_C2S_REQUEST_FAMILYAPPLY				=	0x3408;			// ����������	
	ID_S2C_RESPONSE_FAMILYAPPLY				=	0x3409;			// ����������Ļ�Ӧ	
	ID_S2C_NOTIFY_MEMBERAPPLY				=	0x340A;			// ���������������������������֪ͨ
	ID_C2S_REQUEST_REPLYMEMBERAPPLY			=	0x340B;			// �ظ�������������������
	ID_S2C_RESPONSE_REPLYMEMBERAPPLY		=	0x340C;			// �ظ��������������Ļ�Ӧ
	ID_S2C_NOTIFY_FAMILYAPPLYSUCESS			=	0x340D;			// ֪ͨ�������������ɹ�
	ID_S2C_NOTIFY_FAMILYMEMBERADDED			=	0x340E;			// ֪ͨ�����Ա���³�Ա���루���������ͨ�ã�	
	
	ID_C2S_REQUEST_POSTAPPOINT				=	0x340F;			// ���������ְλ���������
	ID_S2C_RESPONSE_POSTAPPOINT				=	0x3410;			// ���������ְλ����Ļ�Ӧ
	ID_S2C_NOTIFY_POSTAPPOINT				=	0x3411;			// �������������ְλ��֪ͨ
		
	ID_C2S_REQUEST_LEAVEFAMILY				=	0x3412;			// �����Ա�뿪���������
	ID_S2C_RESPONSE_LEAVEFAMILY				=	0x3413;			// �����Ա�뿪����Ļ�Ӧ
	ID_S2C_NOTIFY_MEMBERLEAVEFAMILY			=	0x3414;			// �����Ա�뿪�����֪ͨ	 
	
	ID_C2S_REQUEST_GETFAMILYMEMBERINFO		=	0x3415;			// ��ȡ�����Ա��Ϣ������
	ID_S2C_RESPONSE_GETFAMILYMEMBERINFO		=	0x3416;			// ��ȡ�����Ա��Ϣ�Ļ�Ӧ
	ID_C2S_REQUEST_GETFAMILYPROPERTY		=	0x3417;			// ��ȡ����������Ϣ������
	ID_S2C_RESPONSE_FAMILYPROPERTY			=	0x3418;			// ��ȡ������Ϣ�Ļ�Ӧ������������Ϣ
	
	
	ID_C2S_REQUEST_GETALLFAMILYINFO			=	0x3419;			// ��ȡ���м���Ļ�����Ϣ									 				
	ID_S2C_RESPONSE_GETALLFAMILYINFO		=	0x341A;			// ��ȡ���м��������Ϣ�Ļظ���Ϣ
	
	
	ID_C2S_REQUEST_GETAPPLYLIST				=	0x341B;			// ��ȡ�����б�
	ID_S2C_RESPONSE_GETAPPLYLIST			=	0x341C;			// ���������б�
	
	ID_C2S_REQUEST_KICKMEMBER				=	0x341D;			// �������˵�����
	ID_S2C_RESPONSE_KICKMEMBER				=	0x341E;			// �������˵Ļ�Ӧ
	ID_S2C_NOTIFY_KICKPLAYER				=	0x341F;			// �������˵�֪ͨ
	
	ID_C2S_REQUEST_DISBANDFAMILY			=	0x3420;			// ��ɢ���������
	ID_S2C_RESPONSE_DISBANDFAMILY			=	0x3421;			// ��ɢ����Ļ�Ӧ
	ID_S2C_NOTIFY_DISBANDFAMILY				=	0x3422;			// ��ɢ�����֪ͨ
	
	ID_C2S_REQUEST_CHANGENOTICE				=	0x3423;			// �ı���幫�������
	ID_S2C_RESPONSE_CHANGENOTICE			=	0x3424;			// �ı���幫��Ļ�Ӧ
	
	ID_C2S_REQUEST_APPOINTHEADER			=	0x3425;			// ����ת��ְλ������
	ID_S2C_RESPONSE_APPOINTHEADER			=	0x3426;			// ����ת��ְλ�Ļ�Ӧ��Ϣ
	ID_S2C_NOTIFY_CHANGERHEADER				=	0x3427;			// ����ת��ְλ��֪ͨ	
	
	ID_S2C_NOTIFY_FAMILYPEROPERTY			=	0x3428;			// ����������Ϣ֪ͨ
	
	ID_C2S_REQUEST_CLEARFAMILYAPPLYLIST		=	0x3429;			// ��ռ���������б����Ϣ����
	ID_S2C_RESPONSE_CLEARFAMILYAPPLYLIST	=	0x342A;			// ��ռ��������б����Ϣ��Ӧ
	
	ID_S2C_NOTIFY_JOINCORPS					=	0x342B;			// ���������ŵ���Ϣ֪ͨ
	
	ID_C2S_REQUEST_CANCELFAMILYDISBAND		=	0x342C;			// ȡ�������ɢ����Ϣ����
	ID_S2C_RESPONSE_CANCELFAMILYDISBAND		=	0x342D;			// ȡ�������ɢ����Ϣ�ظ�
	
	ID_S2C_NOTIFY_CHANGEFAMILYNOTICE		=	0x342E;			// �ı���幫�����Ϣ֪ͨ
	
	ID_C2S_REQUEST_REFRESHFAMILYINFO		=	0x342F;			// ˢ�¼����Ա��Ϣ������
	ID_S2C_RESPONSE_REFRESHFAMILYINFO		=	0x3430;			// ˢ�¼����Ա��Ϣ�Ļ�Ӧ��Ϣ
	
	

	ID_C2S_REQUEST_BIDNPC					=	0x3431;			// �峤��������NPC
	ID_S2C_RESPONSE_BIDNPC					=	0x3432;			// ����NPC��Ӧ

	ID_S2C_NOTIFY_MEMBERSUBMIT				=	0x3433;			// ���ᱨ��֪ͨ
	ID_C2S_REQUEST_MEMBERSUBMIT				=	0x3434;			// �峤��������
	ID_S2C_RESPONSE_MEMBERSUBMIT			=	0x3435;			// �峤������Ӧ

	ID_C2S_REQUEST_ABORTNPC					=	0x3436;			// �峤����NPC����
	ID_S2C_RESPONSE_ABORTNPC				=	0x3437;			// �峤����NPC��Ӧ

	ID_C2S_REQUEST_BIDINFO					=	0x3438;			// ��ѯ��������
	ID_S2C_RESPONSE_BIDINFO					=	0x3439;			// ��ѯ�����Ӧ
	
	ID_C2S_REQUEST_SETFAMILYMEMBERPOST		=	0x343A;			// ���ü����Աְλ����Ϣ����
	ID_S2C_RESPONSE_SETFAMILYMEMBERPOST		=	0x343B;			// ���ü����Աְλ����Ϣ��Ϣ��Ӧ
	
	ID_C2S_REQUEST_LEVELUPFAMILY			=	0x343C;			// �������������
	ID_S2C_RESPONSE_LEVELUPFAMILY			=	0x343D;			// ��������Ļ�Ӧ
	
	ID_C2S_REQUEST_CONTRIBUTEFAMILYMONEY	=	0x343E;			// ���׼����Ǯ����Ϣ����
	ID_S2C_RESPONSE_CONTRIBUTEFAMILYMONEY	=	0x343F;			// ���׼����Ǯ����Ϣ��Ӧ
	
	ID_C2S_REQUEST_OBTAINFAMILYMONEY		=	0x3440;			// ��ռ��npc����ȡ�����Ǯ����Ϣ����
	ID_S2C_RESPONSE_OBTAINFAMILYMONEY		=	0x3441;			// ��ռ��npc����ȡ�����Ǯ����Ϣ��Ӧ
	
	ID_S2C_NOTIFY_SETFAMILYPOST				=	0x3442;			// ���ü���ְλ��֪ͨ
	ID_S2C_NOTIFY_LEVELUPFAMILY				=	0x3443;			// ����������֪ͨ	

	ID_S2C_NOTIFY_FAMILYSUBMIT				=	0x3444;			// ֪ͨ���屨��
	ID_S2C_NOTIFY_BATTLERESULT				=	0x3445;			// ֪ͨս�����
	
	ID_S2C_NOTIFY_FAMILYPVPSTARLEVELUP		=	0x3446;			// PVP�Ǽ�������֪ͨ		
																// ��ȱһ����Ϣ
	ID_C2S_REQUEST_MAKEROOM					=	0x3448;			// ���跿������
	ID_S2C_RESPONSE_MAKEROOM				=	0x3449;			// ���跿���Ӧ
	ID_C2S_REQUEST_CHAROOM					=	0x344A;			// ��ս��������
	ID_S2C_RESPONSE_CHAROOM					=	0x344B;			// ��ս�����Ӧ
	ID_C2S_REQUEST_AGREEBATTLE				=	0x344C;			// ͬ����ս����
	ID_S2C_RESPONSE_AGREEBATTLE				=	0x344D;			// ͬ����ս��Ӧ
	ID_C2S_REQUEST_QUERYALLROOM				=	0x344E;			// ��ѯ�����б�����
	ID_S2C_RESPONSE_QUERYALLROOM			=	0x344F;			// ��ѯ�����б��Ӧ
	ID_C2S_REQUEST_QUERYMYROOM				=	0x3450;			// ��ѯ�Լ��ķ�������
	ID_S2C_RESPONSE_QUERYMYROOM				=	0x3451;			// ��ѯ�Լ��ķ����Ӧ
	ID_C2S_REQUEST_QUERYMYCHA				=	0x3452;			// ��ѯ�Լ�����ս����
	ID_S2C_RESPONSE_QUERYMYCHA				=	0x3453;			// ��ѯ�Լ�����ս��Ӧ
	ID_C2S_REQUEST_ABORTROOM				=	0x3454;			// ������������
	ID_S2C_RESPONSE_ABORTROOM				=	0x3455;			// ���������Ӧ
	ID_C2S_REQUEST_ABORTCHA					=	0x3456;			// ������ս����
	ID_S2C_RESPONSE_ABORTCHA				=	0x3457;			// ������ս��Ӧ	   

	ID_S2C_NOTIFY_CONTRIBUTEFAMILYMONEY		=	0x3458;			// ���׼����Ǯ��֪ͨ

	ID_S2C_NOTIFY_FAMILYMONEYCHANGED		=	0x3459;			// �����Ǯ�ı����Ϣ֪ͨ	
	ID_S2C_NOTIFY_USEFAMILYEXPCARD			=	0x345A;			// ʹ�þ������Ƶ�֪ͨ	


	ID_C2S_REQUEST_STARTFAMILYBOSS			=	0x345B;			// ��ͨ����boss�������
	ID_S2C_RESPONSE_STARTFAMILYBOSS			=	0x345C;			// ��ͨ����boss��Ļ�Ӧ 	
	ID_C2S_REQUEST_ENTERBOSSREPTION			=	0x345D;			// ��Ա������帱��������
	ID_S2C_RESPONSE_ENTERBOSSREPTION		=	0x345E;			// ��Ա������帱������Ϣ��Ӧ

	ID_S2C_NOTIFY_MAKEROOM					=	0x345F;			// ���跿��֪ͨ
	ID_S2C_NOTIFY_ABORTROOM					=	0x3460;			// ȡ������֪ͨ
	ID_S2C_NOTIFY_CHAROOM					=	0x3461;			// ��ս����֪ͨ	
	ID_S2C_NOTIFY_ABORTCHA					=	0x3462;			// ȡ����ս֪ͨ 
	
	ID_S2C_NOTIFY_FAMILYGLORYCHANGED		=	0x3463;			// ������ҫ�ĸı��֪ͨ
	ID_S2C_NOTIFY_MEMBERCONTRIBUTECHANGED	=	0x3464;			// �ı���˹��׶ȵ�֪ͨ	 
	
	ID_C2S_REQUEST_QUERYNPCWELFARE			=	0x3465;			// ��ѯnpc������������ҫ�ͽ�Ǯ��
	ID_S2C_RESPONSE_QUERYNPCWELFARE			=	0x3466;			// ��ѯnpc�����Ļ�Ӧ��Ϣ����ҫ�ͽ�Ǯ��
	
	ID_C2S_REQUEST_GETFAMILYMONEY			=	0x3467;			// ��ȡ�����Ǯ�����˵���Ϣ����
	ID_S2C_RESPONSE_GETFAMILYMONEY			=	0x3468;			// ��ȡ�����Ǯ�����˵���Ϣ��Ӧ

	ID_S2C_NOTIFY_ABORTNPC					=	0x3469;			// �峤����NPC֪ͨ
	ID_S2C_NOTIFY_PREBATTLE					=	0x346A;			// ����սս��ǰ֪ͨ
	
	ID_C2S_REQUEST_GETEXPCARD				=	0x346B;			// ��ȡ�������Ƶ�����
	ID_S2C_RESPONSE_GETEXPCARD				=	0x346C;			// ��ȡ�������ƵĻ�Ӧ��Ϣ
	
	ID_S2C_NOTIFY_FAMILYCANLEVELUP			=	0x346D;			// �������������֪ͨ��Ϣ
					
	ID_S2C_NOTIFY_FAMILYREPETIONSCORE		=	0x346E;			// ���帱��������
	
	ID_C2S_REQUEST_GETFAMILYGOODSLIST		=	0x346F;			// ��ȡ������Ʒ�б����Ϣ����
	ID_S2C_RESPONSE_GETFAMILYGOODSLIST		=	0x3470;			// ��ȡ������Ʒ�б����Ϣ��Ӧ
	
	ID_C2S_REQUEST_GETFAMILYEXCHANGEGOODSLIST	= 0x3471;		// ��ȡ����һ���Ʒ�б����Ϣ����
	ID_S2C_RESPONSE_GETFAMILYEXCHANGEGOODSLIST 	= 0x3472;		// ��ȡ����һ���Ʒ�б����Ϣ��Ӧ
	
	ID_S2C_NOTIFY_CHANGEFAMILYGOODSLIST				= 0x3473;		// �ı���Ʒ�б��֪ͨ
	ID_S2C_NOTIFY_CHANGEFAMILYEXCHANGEGOODSLIST		= 0x3474;		// �ı�һ��б��֪ͨ 
	ID_S2C_NOTIFY_USEFAMILYLEAGUEITEM				= 0x3475;		// ʹ�ü����ع���Ʒ��֪ͨ

	ID_C2S_REQUEST_GETHOMEINFO				=	0x3476;			// ��ü�԰��Ϣ����
	ID_S2C_RESPONSE_GETHOMEINFO				=	0x3477;			// ��ü�԰��Ϣ��Ӧ

	ID_C2S_REQUEST_UPGRADEHOME				=	0x3478;			// ������ͨ��԰����������
	ID_S2C_RESPONSE_UPGRADEHOME				=	0x3479;			// ������ͨ��԰�������Ӧ
	
	ID_S2C_NOTIFY_FAMILYSTABILITYCHANGED	=	0x347A;			// ���尲���ȸı��֪ͨ
	
};									   

// *************************************************************************** //
//  ��Ϣͷ���ѿͻ��˷�����������������Ϣת�ɷ������ص���Ϣ( �������� )
// *************************************************************************** //
message FamilyHead
{
	optional uint32   RoleID	=	1;				// ��ɫID
	optional uint32   MsgID     =	2;			    // ��ϢID
	optional uint32	  EntityID	=	3;				// �ڳ����е�ʵ��ID
};


// *************************************************************************** //
// CMessageCreatFamilyRequest  
// ��Ҵ������������
// *************************************************************************** //
message CMessageCreatFamilyRequest
{
	optional  FamilyHead	HeadMsg		= 1;	    // ��Ϣͷ��������
	optional  string		FamilyName	= 2;		// ��������	
	optional  uint32		NpcEntityID = 3;		// ����NPC��ʵ��ID
};

// *************************************************************************** //
// CMessageCreatFamilyResponse  
// ��Ҵ�������Ļ�Ӧ
// *************************************************************************** //
// TODO:������������
message CMessageCreatFamilyResponse
{
	optional FamilyHead	HeadMsg			= 1;	    // ��Ϣͷ��������
	optional uint32 ErrCode				= 2;			// 0 ��ʾ�ɹ�������ʾ������
	optional uint32 FamilyID			= 3;			// �ɹ�ʱ�ļ���ID
	optional string FamilyName			= 4;			// �ɹ�ʱ�ļ�������
};

// *************************************************************************** //
// CMessageInviteMemberRequest  
// ������Χ��Ҽ������
// *************************************************************************** //
message CMessageInviteMemberRequest
{
	optional FamilyHead	HeadMsg			= 1;	    // ��Ϣͷ��������
	optional uint32 RoleID				= 2;		// ��������ҵ�ʵ��ID	
	optional string RoleName			= 3;		// ���������ҵĽ�ɫ��(��ɫid�ͽ�ɫ��ֻ��ʹ��һ������)	
}; 

// *************************************************************************** //
// CMessageInviteMemberResponse  
// ������Ҽ������Ļ�Ӧ��Ϣ
// *************************************************************************** //
message CMessageInviteMemberResponse
{
	optional FamilyHead	HeadMsg			= 1;	    // ��Ϣͷ��������
	optional uint32 Errcode				= 2;			// 0��ʾ�ɹ�������ʾ������
	optional string RoleName			= 3;			// �������ҵ�����  	
};

// *************************************************************************** //
// CMessageFamilyInviteNotify  
// ���������������Ϣ֪ͨ
// *************************************************************************** //
message CMessageFamilyInvitedNotify
{
	optional FamilyHead	HeadMsg			= 1;			// ��Ϣͷ��������
	optional string PlayerName			= 2;			// �����ߵ�����
	optional string FamiltyName			= 3;			// ���������ڼ�������
	optional uint32 RoleID				= 4;			// �����ߵĽ�ɫID
	optional uint32 FamilyID			= 5;			// �����ߵļ���ID	
	optional uint32 FamilyLevel			= 6;			// ����ȼ�
	optional uint32 MemberNum			= 7;			// �����Ա����	
	optional string CorpsName			= 8;			// �������ھ�������	     	
	optional uint32	Glory				= 9;			// �������ҫֵ
	optional uint32	StarLevel			= 10;			// �����Ǽ�
	optional uint32 NpcID				= 11;			// ����npc
	optional string	FamilyHeaderName	= 12;			// �����峤����
	optional uint32	UnionID				= 13;			// ����ID
	optional string	UnionName			= 14;			// ��������
};

// *************************************************************************** //
// CMessageReplyFamilyInviteRequest  
// �𸴼������������
// *************************************************************************** //
message CMessageReplyFamilyInviteRequest
{				 
	optional FamilyHead	HeadMsg			= 1;				// ��Ϣͷ��������
	optional uint32 Result				= 2;				// 1��ʾͬ��������0��ʾ��ͬ��2��ʾ����
	optional uint32	FamilyID			= 3;				// ����ID
	optional uint32 InvitingRoleID		= 4;				// �������ҵĽ�ɫID	
};

// *************************************************************************** //
// CMessageReplyFamilyInviteResponse
// �𸴼������������
// *************************************************************************** //
message CMessageReplyFamilyInviteResponse
{				 
	optional FamilyHead	HeadMsg			= 1;	    // ��Ϣͷ��������
	optional uint32 Errcode				= 2;		// 0��ʾ����ɹ�������ʾ������
	optional uint32	FamilyID			= 3;		// ����ID
	optional string	FamilyName			= 4;		// ��������
	optional uint32	Result				= 5;		// 1��ʾͬ��0��ʾ�ܾ�
	optional uint32 CorpsID				= 6;		// �������ڵľ���ID
	optional string	CorpsName			= 7;		// ��������
	optional uint32	FamilyHeaderID		= 8;		// ��������ID
	optional uint32 CorpsHeaderID		= 9;		// ��������ID
	optional uint32	UnionID				= 10;		// ��������ID
	optional string UnionName			= 11;		// ������������
};

// *************************************************************************** //
// CMessageApplyFamilyRequest  
// ͨ����Χ��һ��߼���ID����������
// *************************************************************************** //
message CMessageApplyFamilyRequest
{
	optional FamilyHead	HeadMsg			= 1;			// ��Ϣͷ��������
	optional uint32 CharID				= 2;			// Ŀ����ҽ�ɫID
	optional uint32	FamilyID			= 3;			// ����ID( ʵ��ID�ͼ���idֻ����һ�� )
	optional string FamilyName			= 4;			// ��������( �Ժ�Ҫ�� )																									
};	

// *************************************************************************** //
// CMessageApplyFamilyResponse  
// ����������Ļظ���Ϣ
// *************************************************************************** //
message CMessageApplyFamilyResponse
{
	optional FamilyHead	HeadMsg	= 1;	    // ��Ϣͷ��������
	optional uint32	Errcode		= 2;		// 0��ʾ�ɹ�������ʾ������
	optional string	FamilyName	= 3;		// ��������
	optional uint32 FamilyID	= 4;		// ����ID  	
};

// *************************************************************************** //
// CMessageMemberApplyNotify  
// ����������������������������֪ͨ
// *************************************************************************** //
message CMessageMemberApplyNotify
{
	optional FamilyHead	HeadMsg			= 1;			// ��Ϣͷ��������
	optional string PlayerName			= 2;			// �����˵�����
	optional uint32	RoleID				= 3;			// �����˵Ľ�ɫID
	optional uint32	RoleLevel			= 4;			// �����˵ĵȼ�
	optional uint32	RoleMetier			= 5;			// �����˵�ְҵ
	optional uint32	FaceType			= 6;			// ����	
	optional uint32 RoleSex		        = 7;			// �Ա�
	optional uint32 LineID				= 8;			// ����ID
	optional uint32 MapID				= 9;			// ��ͼID
};

// *************************************************************************** //
// CMessageReplyMemberApplyRequest  
// ��������������������
// *************************************************************************** //
message CMessageReplyMemberApplyRequest
{
	optional FamilyHead	HeadMsg			=	1;				// ��Ϣͷ��������
	optional uint32 Result				=	2;				// �ظ����1��ʾ��׼����0��ʾ��ͬ�����2��ʾ����
	optional uint32 RoleID				=	3;				// �����˵Ľ�ɫID
};


// *************************************************************************** //
// CMessageReplyMemberApplyResponse  
// ���������������Ļظ�
// *************************************************************************** //
message CMessageReplyMemberApplyResponse  
{
	optional FamilyHead	HeadMsg			=	1;			// ��Ϣͷ��������
	optional uint32 Errcode				=	2;			// 0��ʾ�����ɹ�������ʾ������
	optional string PlayerName			=	3;			// �����˵Ľ�ɫ��
	optional uint32 CharID				=   4;			// �����˵Ľ�ɫID	
	optional uint32 Result				=   5;			// 1��ʾͬ��0��ʾ�ܾ�	   		
}; 

// *************************************************************************** //
// CMessageApplyFamilySuccessNotify  
// ֪ͨ�������������ɹ�
// *************************************************************************** //
message CMessageApplyFamilySuccessNotify
{
	optional FamilyHead	HeadMsg			=	1;			// ��Ϣͷ��������
	optional uint32 Result				=   2;			// 1��ʾ����ɹ�0��ʾ���ܾ�����ֵ��ʾ����ʧ��
	optional uint32	FamilyID			=	3;			// ����ID
	optional string FamilyName			=	4;			// ��������
	optional uint32 CorpsID				=	5;			// ����ID
	optional string CorpsName			=	6;			// ��������
	optional uint32	FamilyHeader		=	7;			// �����峤
	optional uint32 CorpsHeader			=	8;			// ��������
	optional uint32	UnionID				=	9;			// �������˵�ID
	optional string	UnionName			=	10;			// �������˵�����		
};

// *************************************************************************** //
// CMessageFamilyMemberAddedNotify  
// �³�Ա��������֪ͨ				  ::��Ϣ�޸�
// *************************************************************************** //
message CMessageFamilyMemberAddedNotify
{
	optional FamilyHead	HeadMsg			=	1;				// ��Ϣͷ��������
	optional string ManagerName			=	2;				// ��׼��Ҽ���Ĺ����ߵ�����
	optional FamilyMemberInfo RoleInfo  =	3;				// �����Ϣ
};



// *************************************************************************** //
// CMessagePostAppointRequest  
// ְλ���������
// *************************************************************************** //
message CMessagePostAppointRequest
{
	optional FamilyHead	HeadMsg			=	1;			 // ��Ϣͷ��������
	optional uint32 PlayerCharID		=	2;			// ��������Ľ�ɫID
	optional uint32 ActionKind			=	3;			// ��������(��ְ����ְ����ö��ֵ��ʾ)
};

// *************************************************************************** //
// CMessagePostAppointResponse  
// ְλ����Ļ�Ӧ
// *************************************************************************** //
message CMessagePostAppointResponse
{
	optional FamilyHead	HeadMsg			=	1;				// ��Ϣͷ��������
	optional uint32	Errcode				=	2;				// 0��ʾ�ɹ�������ʾ������
	optional uint32 PlayerCharID		=	3;				// ���������
	optional uint32	ActionKind			=	4;				// ��������	
};

// *************************************************************************** //
// CMessagePostAppointNoify  
// ְλ�����֪ͨ
// *************************************************************************** //
message CMessagePostAppointNoify
{	
	optional FamilyHead	HeadMsg			=	1;				// ��Ϣͷ��������
	optional uint32 PlayerCharID		=	2;				// ���������
	optional uint32	ActionKind			=	3;				// ��������	
	optional string ManagerName			=	4;				// �����ߵ�����
	optional string	PlayerName			=	5;				// �������ߵ�����
};


// *************************************************************************** //
// CMessageLeaveFamilyRequest  
// �뿪���������
// *************************************************************************** //
message CMessageLeaveFamilyRequest	
{
	optional FamilyHead	HeadMsg			=	1;			 // ��Ϣͷ��������
	optional uint32 MsgCode				=	2;				// ���ò���
};

// *************************************************************************** //
// CMessageLeaveFamilyResponse  
// �뿪����Ļ�Ӧ
// *************************************************************************** //
message CMessageLeaveFamilyResponse
{
	optional FamilyHead	HeadMsg			=	1;			 // ��Ϣͷ��������
	optional uint32 Errcode				=	2;			 // 0��ʾ�ɹ�������ʾ������
};

// *************************************************************************** //
// CMessageMemberLeaveFamilyNotify  
// ��Ա�뿪�����֪ͨ
// *************************************************************************** //
message CMessageMemberLeaveFamilyNotify
{		
	optional FamilyHead	HeadMsg			=	1;			// ��Ϣͷ��������
	optional uint32	RoleID				=	2;			// �뿪�������ҽ�ɫID
	optional string RoleName			=	3;			// �뿪�������ҵĽ�ɫ����
	optional uint32	PlayerLevel			=	4;			// ��ҵȼ�
	optional uint32	PlayerPost			=	5;			// ���ְλ	
};

// *************************************************************************** //
// CMessageGetFamilyMemberInfoRequest  
// ��ȡ�����Ա��Ϣ������
// *************************************************************************** /
message CMessageGetFamilyMemberInfoRequest
{
	optional FamilyHead	HeadMsg			=	1;			 // ��Ϣͷ��������
	//optional uint32	FamilyID			=	2;		// ����ID
};

// *************************************************************************** //
// CMessageFamilyMemberInfoResponse  
// ���ͼ����������Ϣ
// *************************************************************************** //
message CMessageGetFamilyMemberInfoResponse
{										
	optional FamilyHead			HeadMsg		=	1;			 // ��Ϣͷ��������
	optional PBFamilyMemberList MemberInfo	=	2;			 // ��ҽ�ɫ��Ϣ 		
};


// *************************************************************************** //
// CMessageGetFamilyPropertyRequest  
// ��ȡ����Ļ�������Ϣ�Ե�����
// *************************************************************************** //
message CMessageGetFamilyPropertyRequest
{
	optional FamilyHead	HeadMsg			=	1;			 // ��Ϣͷ��������
	// optional uint32	FamilyID			=	2;			 // ����ID	
}

// *************************************************************************** //
// CMessageGetFamilyPropertyResponse  
// ��ȡ����Ļ�������Ϣ�ԵĻ�Ӧ��Ϣ
// *************************************************************************** //
message CMessageGetFamilyPropertyResponse
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional string	FamilyNotice		=	2;		// ���幫��
	optional uint32	FamilyNum			=	3;		// ��������
	optional uint32 FamilyLevel			=   4;		// ����ȼ�
	optional uint32 FamilyMoney			=	5;		// �����Ǯ
	optional uint32 FamilyHeaderID		=	6;		// �峤ID
	optional string FamilyHeaderName	=	7;		// �峤����			
	
	optional uint32	FamilyGlory			=	8;			// ��������	
	optional uint32 NpcID				=	9;			// ����ռ��/���۵�NPCID
	optional uint32 BidMoney			=	10;			// ���徺�۵�Ǯ��
	optional uint32	BidTime				=	11;			// ���徺�۵�ʱ��
	optional uint32 WarNpcStatus		=	12;			// ս��npc��״̬0��ʾ�Ѿ�ռ��1��ʾ�������ᵱ��		
	optional uint32 WarRank				=	13;			// ����վ�ۺ�����
	optional uint32	WarWinNum			=	14;			// ����ս��ʤ������
	optional uint32	WarLostNum			=	15;			// ����ս��ʧ�ܴ���
	optional uint32	FamilyStarLevel		=	16;			// �����Ǽ�
	optional uint32	WarExp				=	17;			// ����ս������
	optional uint32 WarMaxExp			=	18;			// ����ս���������ֵ
	optional string EnemyFamilyName		=	19;			// ��ս��������	
	optional uint32	WarStatus			=	20;			// ս��״̬
	
	optional uint32	ChallengeStatus		=	21;			// ��ս�����״̬
	optional uint32	ChallengeMoney		=	22;			// ��ս���
	optional string	ChallengeStarted	=	23;			// ����������ս
	optional string ChallengeReceived	=	24;			// ����յ�����ս
	optional uint32	MaxFamilyMemberNum	=	25;			// ����˿�����
	optional uint32	CanLevelUP			=	26;			// �Ƿ��������
	optional uint32	MaxPresterNum		=	27;			// �����������
	optional uint32	GloryLimit			=	28;			// ���徭������
	optional uint32	LevelMoney			=	29;			// ������Ҫ�Ľ�Ǯ
	optional uint32	Stability			=	30;			// ������ļ��尲����
	optional uint32	ReduceStability		=	31;			// ÿ��˥���İ�����
	optional uint32	ExtraRedstonExp		=	32;			// ����ļ����ڵ�����ӳ�
};


// *************************************************************************** //
// CMessageGetAllFanmilyInfoRequest  
// ��ȡ���м��������Ϣ������
// *************************************************************************** //
message CMessageGetAllFanmilyInfoRequest
{
	optional FamilyHead	HeadMsg			=	1;			 // ��Ϣͷ��������
	optional uint32	CurPage				=	2;			 //	��ǰҳ��
														 // TODO:�Ժ����Ҫ��������
};

// *************************************************************************** //
// CMessageGetAllFamilyInfoResponse  
// ��ȡ���м��������Ϣ�Ļظ�
// *************************************************************************** //
message CMessageGetAllFamilyInfoResponse
{
	optional FamilyHead		HeadMsg			=	1;		// ��Ϣͷ��������
	optional PBFamilyList	FamilyInfo 		=	2;		// ������Ϣ
	optional uint32			CurPage			=	3;		// ��ǰҳ��
	optional uint32			TotalPage		=	4;		// ��ҳ��
};	   

// *************************************************************************** //
// CMessageGetApplyListRequest  
// ��ȡ�����б������
// *************************************************************************** //
message CMessageGetApplyListRequest
{
	optional FamilyHead	HeadMsg			= 1;		// ��Ϣͷ��������
	optional uint32 FamilyID			= 2;		// ����ID TODO:�ò���û��
};

// *************************************************************************** //
// CMessageGetApplyListResponse  
// ��ȡ�����б�Ļظ�
// *************************************************************************** //

message CMessageGetApplyListResponse
{
	optional FamilyHead	 HeadMsg			=	1;		// ��Ϣͷ��������
	optional PBApplyList ApplyList			=	2;		// �����б�
};	   



// *************************************************************************** //
// CMessageKickPlayerRequest  
// ���˵�����
// *************************************************************************** //
message CMessageKickPlayerRequest	
{		
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32 PlayerCharID		=	2;		// ��ҽ�ɫID	
};

// *************************************************************************** //
// CMessageKickPlayerResponse  
// ���˵Ļظ�
// *************************************************************************** //
message CMessageKickPlayerResponse
{
	optional FamilyHead	HeadMsg			=	1;			 // ��Ϣͷ��������
	optional uint32	Errcode				=	2;		// 0��ʾ�ɹ�������ʾ������
	optional string	PlayerName			=	3;		// �޳��Ľ�ɫ��
	optional uint32 PlayerCharID		=	4;		// ��ҵĽ�ɫID
};


// *************************************************************************** //
// CMessageKickPlayerNotify
// ���˵Ļظ�
// *************************************************************************** //
message CMessageKickPlayerNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional string	PlayerName			=	2;		// �޳��Ľ�ɫ��
	optional uint32 PlayerCharID		=	3;		// �޳��Ľ�ɫID
	optional string ManagerName			=	4;		// ���˵Ĺ����ߵĽ�ɫID
	optional uint32 ManagerCharID		=	5;		// ���˵Ĺ����ߵĽ�ɫ��
};

// *************************************************************************** //
// CMessageDisbandFamilyRequest  
// ��ɢ���������
// *************************************************************************** //
message CMessageDisbandFamilyRequest
{
	optional FamilyHead	HeadMsg			=	1;		 // ��Ϣͷ��������
	optional uint32	MsgCode				=	2;		 // ���ò���
	optional uint32	NpcEntityID			=	3;		 // ����NPC��ʵ��ID
};

// *************************************************************************** //
// CMessageDisbandFamilyResponse  
// ��ɢ����Ļظ�
// *************************************************************************** //
message CMessageDisbandFamilyResponse
{
	optional FamilyHead	HeadMsg			=	1;		 // ��Ϣͷ��������
	optional uint32	Errcode				=	2;		 // 0��ʾ�ɹ�������ʾ������
};


// *************************************************************************** //
// CMessageDisbandFamilyNotify  
// ��ɢ�����֪ͨ
// *************************************************************************** //
message CMessageDisbandFamilyNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32 ManagerCharID		=	2;		// ��ɢ����Ĺ����߽�ɫID
	optional uint32	FamilyID			=	3;		// ��ɢ�ļ���ID	
};

// *************************************************************************** //
// CMessageChangeFamilyNotice  
// �ı���幫��
// *************************************************************************** //
message CMessageChangeFamilyNoticeRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional string		Notice			=	2;		// ֪ͨ����
};

// *************************************************************************** //
// CMessageChangeFamilyNoticeResponse  
// �ı���幫��Ļظ���Ϣ
// *************************************************************************** //
message CMessageChangeFamilyNoticeResponse
{
	optional FamilyHead	HeadMsg			=	1;	   // ��Ϣͷ��������
	optional uint32 Errcode				=	2;	   // 0��ʾ�ɹ�������ʾ������
	optional string	Notice				=	3;	   // ��������
};



// *************************************************************************** //
// CMessageAppointHeaderRequest  
// ����ת��ְλ������
// *************************************************************************** //
message CMessageAppointHeaderRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32 PlayerCharID		=	2;		//	��ת��ְλ�Ľ�ɫID
};

// *************************************************************************** //
// CMessageAppointHeaderRequest  
// ����ת��ְλ������
// *************************************************************************** //
message CMessageAppointHeaderResponse
{
	optional FamilyHead	HeadMsg			=	1;			 // ��Ϣͷ��������
	optional uint32 Errcode				=	2;		//	0��ʾ�ɹ�������ʾ������
	optional uint32 PlayerCharID		=	3;		//	��ת��ְλ�Ľ�ɫID
	optional string PlayerName			=	4;		//	��ת��ְλ�Ľ�ɫ��
};

// *************************************************************************** //
// CMessageChangeHeaderNotify  
// ����ת��ְλ��֪ͨ
// *************************************************************************** //
message CMessageChangeHeaderNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32 PlayerCharID		=	2;		//	��ת��ְλ�Ľ�ɫID
	optional string PlayerName			=	3;		//	��ת��ְλ�Ľ�ɫ��
	optional uint32 ManagerID			=	4;		//	ת��ְλ�Ĺ�����ID
	optional string ManagerName			=	5;		//	ת��ְλ�Ĺ���������
};


// *************************************************************************** //
// CMessageFamilyPropertyNotify  
// �����������Ϣ֪ͨ
// *************************************************************************** //
message CMessageFamilyPropertyNotify
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������	 	
	optional PBFamilyPropery	Property		=	2;		// ��������
	optional uint32				FamilyLevel		=	3;		// ����ȼ�		
};

// *************************************************************************** //
// CMessageInviteResultNotify  
// �������Ľ��֪ͨ
// *************************************************************************** //
message CMessageInviteFamilyResultNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32 Result				=	2;		// �����������ܾ����Ǳ�ͬ��(1��ʾͬ��0��ʾ�ܾ�,������ʾ������)
	optional string RoleName			=	3;		// �������˵�����
};

// *************************************************************************** //
// CMessageClearFamilyApplyRequest  
// ������������б����Ϣ����
// *************************************************************************** //
message CMessageClearFamilyApplyRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32 MsgCode				=	2;		// ���ò���
};

// *************************************************************************** //
// CMessageClearFamilyApplyResponse
// ������������б����Ϣ��Ӧ
// *************************************************************************** //
message CMessageClearFamilyApplyResponse
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32 Errcode				=	2;		// �����룬0��ʾ�ɹ�������ʾ������
};

// *************************************************************************** //
// CMessageJoinCorpsNotify
// ���������ŵ���Ϣ��Ϣ֪ͨ
// *************************************************************************** //
message CMessageJoinCorpsNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		CorpsID			=	2;		// ����ID
	optional string		CorpsName		=	3;		// ��������
	optional uint32		JoinMethod		=	4;		// ���뷽ʽ���峤�������Ǽ���������������ö��ֵEMethodJoinCorps��ʾ
	optional uint32		UnionID			=	5;		// ��������ID
	optional string		UnionName		=	6;		// ������������	
};

// *************************************************************************** //
// CMessageCanelFamilyDisbandRequest
// ȡ����ɢ�������Ϣ����
// *************************************************************************** //
message CMessageCancelFamilyDisbandRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		NpcEntityID		=	2;		// ����NPC��ʵ��ID
};


// *************************************************************************** //
// CMessageCancelFamilyDisbandResponse
// ȡ����ɢ�������Ϣ�ظ�
// *************************************************************************** //
message CMessageCancelFamilyDisbandResponse
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		Errcode			=	2;		// 0��ʾ�����ɹ�������ʾ������
};

// *************************************************************************** //
// CMessageChangeFamilyNoticeNotify
// �ı���幫���֪ͨ
// *************************************************************************** //
message CMessageChangeFamilyNoticeNotify
{
	  optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	  optional string		Notice			=	2;		// ��������
};

// *************************************************************************** //
// CMessageRefreshFamilyInfoRequest
// ˢ�¼�����Ϣ������
// *************************************************************************** //
message CMessageRefreshFamilyInfoRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		MsgCode			=	2;		// ��������
};

// *************************************************************************** //
// CMessageRefreshFamilyInfoResponse
// ˢ�¼�����Ϣ�Ļ�Ӧ
// *************************************************************************** //
message CMessageRefreshFamilyInfoResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional PBFamilyMemberList	MemberList		=	2;		// ��Ա��Ϣ
};


// *************************************************************************** //
// CMessageSetFamilyPostRequest
// ���ü����Աְλ����Ϣ����
// *************************************************************************** //
message CMessageSetFamilyPostRequest
{
	optional FamilyHead	HeadMsg		=	1;	// ��Ϣͷ��������
	optional uint32		MemberID	=	2;	// ��Ա��ɫ
	optional uint32		Post		=	3;	// ְλ
};

// *************************************************************************** //
// CMessageSetFamilyPostResponse
// ���ü����Աְλ����Ϣ��Ϣ��Ӧ
// *************************************************************************** //
message CMessageSetFamilyPostResponse
{
	optional FamilyHead		HeadMsg		=	1;		// ��Ϣͷ��������
	optional uint32			Errcode		=	2;		// ������
	optional uint32			MemberID	=	3;		// ��Ա��ɫID
	optional uint32			Post		=	4;		// ְλ	
};

// *************************************************************************** //
// CMessageLevelUPFamilyRequest
// �����������Ϣ����
// *************************************************************************** //
message CMessageLevelUPFamilyRequest
{  
	optional FamilyHead	HeadMsg	=	1;		// ��Ϣͷ��������
	optional uint32		MsgCode	=	2;		// ���ò���	
};

// *************************************************************************** //
// CMessageLevelUPFamilyResponse
// ��������Ļ�Ӧ
// *************************************************************************** //
message CMessageLevelUPFamilyResponse
{  
	optional FamilyHead	HeadMsg		=	1;		// ��Ϣͷ��������
	optional uint32		Errcode		=	2;		// ������
	optional uint32		Level		=	3;		// ����ȼ�
};

// *************************************************************************** //
// CMessageContributeFamilyMoneyRequest
// ���׼����Ǯ����Ϣ����
// *************************************************************************** //
message CMessageContributeFamilyMoneyRequest
{ 
	optional FamilyHead		HeadMsg		=	1;		// ��Ϣͷ��������
	optional uint32			Money		=	2;		// ��Ǯ			 				
};

// *************************************************************************** //
// CMessageContributeFamilyMoneyResponse
// ���׼����Ǯ����Ϣ��Ӧ
// *************************************************************************** //
message CMessageContributeFamilyMoneyResponse
{  
	optional FamilyHead		HeadMsg		=	1;		// ��Ϣͷ��������
	optional uint32			Errcode		=	2;		// ������
	optional uint32			Money		=	3;		// ���׵Ľ�Ǯ
	optional uint32			Contribute	=	4;		// ���׽�Ǯ��ȡ��������
};

// *************************************************************************** //
// CMessageObtainFamilyMoneyRequest
// ��ռ��npc����ȡ���帣������Ϣ����
// *************************************************************************** //
message CMessageObtainFamilyMoneyRequest
{
	optional FamilyHead		HeadMsg		=	1;		// ��Ϣͷ��������
	optional uint32			NpcID		=	2;		// ����npcID
	optional uint32			NpcTmpID	=	3;		// npc��ģ��ID(��������)			
};

// *************************************************************************** //
// CMessageObtainFamilyMoneyResponse
// ��ռ��npc����ȡ���帣������Ϣ��Ӧ
// *************************************************************************** //
message CMessageObtainFamilyMoneyResponse
{
	optional FamilyHead		HeadMsg	=	1;		// ��Ϣͷ��������
	optional uint32			Errcode	=	2;		// ������		
	optional uint32			Money	=	3;		// ��ȡ�Ľ�Ǯ
	optional uint32			Glory	=	4;		// ��ȡ����ҫֵ
};

// *************************************************************************** //
// CMessageSetCorpsPostNotify
// ����ְλ�����֪ͨ
// *************************************************************************** //
message CMessageSetFamilyPostNotify
{	
	optional FamilyHead		HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32			ManagerID		=	2;		// ������ID
	optional string			ManagerName		=	3;		// ����������
	optional uint32			MemberID		=	4;		// ��ԱID
	optional string			MemberName		=	5;		// ��Ա����				
	optional uint32			OriginalPost	=	6;		// ԭ����ְλ
	optional uint32			NewPost			=	7;		// �µ�ְλ
};

// *************************************************************************** //
// CMessageLevelUPFamilyNotify
// ����������֪ͨ
// *************************************************************************** //
message CMessageLevelUPFamilyNotify
{
	optional FamilyHead		HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32			Level			=	2;		// ����ȼ�	
	optional uint32			Money			=	3;		// ���嵱ǰ��Ǯ
	optional uint32			Glory			=	4;		// ���嵱ǰ��ҫ
	optional uint32			MaxFamilyMember =	5;		// ��������˿�����
	optional uint32			MaxPresterNum	=	6;		// ������ĳ�����������
	optional uint32			LevelMoney		=	7;		// ������Ҫ�Ľ�Ǯ
	optional uint32			LevelGlory		=	8;		// ������Ҫ����ҫ	
	optional uint32			Stability		=	9;		// ������ļ��尲����
	optional uint32			ReduceStability	=	10;		// ������ÿ��˥���İ�����
};

// *************************************************************************** //
// CMessageFamilyBidNpcRequest
// �峤��������NPC
// *************************************************************************** //
message CMessageFamilyBidNpcRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		NpcID			=	2;		// �����NPCID
	optional uint32		Money			=	3;		// ����Ľ��
};

// *************************************************************************** //
// CMessageFamilyBidNpcResponse
// ����NPC��Ӧ
// *************************************************************************** //
message CMessageFamilyBidNpcResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				Result			=	2;		// ����Ľ��
	optional uint32				NpcID			=	3;		// �����NPC ID
	optional uint32				Money			=	4;		// ʵ�ʿ۳��Ľ��
};

// *************************************************************************** //
// CMessageMemberSubmitNotify
// ���ᱨ��֪ͨ
// *************************************************************************** //
message CMessageMemberSubmitNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		NpcID			=	2;		// �����NPC ID
	optional string		FamilyName		=	3;		// ���ֵ�����
	optional uint32		First			=	4;		// �Ƿ����
};

// *************************************************************************** //
// CMessageMemberSubmitRequest
// ���ᱨ������
// *************************************************************************** //
message CMessageMemberSubmitRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		NpcID			=	2;		// �����NPC ID
	repeated uint32		MemberID		=	3;		// �����ĳ�ԱID
};

// *************************************************************************** //
// CMessageMemberSubmitResponse
// ���ᱨ����Ӧ
// *************************************************************************** //
message CMessageMemberSubmitResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				Result			=	2;		// �����Ľ��
	optional uint32				NpcID			=	3;		// �����NPC ID
};

// *************************************************************************** //
// CMessageAbortNpcRequest
// �峤����NPC����
// *************************************************************************** //
message CMessageAbortNpcRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		FamilyID		=	2;		// �����ļ���ID
	optional uint32		NpcID			=	3;		// ������NPC ID
};

// *************************************************************************** //
// CMessageAbortNpcResponse
// �峤����NPC��Ӧ
// *************************************************************************** //
message CMessageAbortNpcResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				Result			=	2;		// �����Ľ��
	optional uint32				FamilyID		=	3;		// �����ļ���ID
	optional uint32				NpcID			=	4;		// ������NPC ID
};

// *************************************************************************** //
// CMessageBidInfoRequest
// ��ѯ��������
// *************************************************************************** //
message CMessageBidInfoRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		NpcID			=	2;		// ��ѯ��NPC ID
};

message BidResult
{
	optional uint32				FamilyID		=	1;		// ���۵ļ���ID
	optional string				FamilyName		=	2;		// ���۵ļ�������
	optional uint32				Money			=	3;		// ���۵ļ۸�
	optional uint32				Win				=	4;		// ʤ
	optional uint32				Lost			=	5;		// ��
	optional uint32				Country			=	6;		// ����
	optional uint32				Level			=	7;		// �Ǽ�
};

// *************************************************************************** //
// CMessageBidInfoResponse
// ��ѯ�����Ӧ
// *************************************************************************** //
message CMessageBidInfoResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				Result			=	2;		// �����Ľ��
	optional uint32				NpcID			=	3;		// ��ѯ��NPC ID
	optional string				FamilyName		=	4;		// ռ�еļ�������
	repeated BidResult			BidData			=	5;		// ��ѯ��Ϣ				
};

// *************************************************************************** //
// CMessageFamilySubmitNotify
// ����֪ͨ
// *************************************************************************** //
message CMessageFamilySubmitNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		NpcID			=	2;		// �����NPC ID
	optional string		FamilyName		=	3;		// �Է�������
	repeated uint32		MemberID		=	4;		// �����ĳ�ԱID
	optional uint32		ManagerID		=	5;		// �ύ�Ĺ�����ID
	optional string		ManagerName		=	6;		// �ύ�Ĺ����߽�ɫ����
};

// *************************************************************************** //
// CMessageBattleResultNotify
// ս�����֪ͨ
// *************************************************************************** //
message CMessageBattleResultNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		NpcID			=	2;		// �����NPC ID
	optional string		AttFamilyName	=	3;		// ������������
	optional string		DefFamilyName	=	4;		// ���ط�������
	optional uint32		WinSide			=	5;		// ��ʤ����1��2��
	optional uint32		AttFamilyID		=	6;		// ������ID
	optional uint32		DefFamilyID		=	7;		// ���ط�ID
};


// *************************************************************************** //
// CMessagePVPStarLevelUPNotify
// pvp�Ǽ�������֪ͨ
// *************************************************************************** //
message CMessageFamilyPVPStarLevelUPNotify
{	
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				PVPStarLevel	=	2;		// pvp�Ǽ�	
};

// *************************************************************************** //
// CMessageMakeRoomRequest
// ���跿������
// *************************************************************************** //
message CMessageMakeRoomRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		Money			=	2;		// ������Ҫ��Ǯ
	optional string		Name			=	3;		// ��������
};

// *************************************************************************** //
// CMessageMakeRoomResponse
// ���跿���Ӧ
// *************************************************************************** //
message CMessageMakeRoomResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				Result			=	2;		// ����Ľ��
	optional string				Name			=	3;		// ��������
	optional uint32				Money			=	4;		// ������Ҫ��Ǯ
};

// *************************************************************************** //
// CMessageChaRoomRequest
// ��ս��������
// *************************************************************************** //
message CMessageChaRoomRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		FamilyID		=	2;		// ��ս�ļ���ID
};

// *************************************************************************** //
// CMessageChaRoomResponse
// ��ս�����Ӧ
// *************************************************************************** //
message CMessageChaRoomResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				Result			=	2;		// ��ս�Ľ��
	optional uint32				FamilyID		=	3;		// ��ս�ļ���ID
};

// *************************************************************************** //
// CMessageAgreeBattleRequest
// ͬ����ս����
// *************************************************************************** //
message CMessageAgreeBattleRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		FamilyID		=	2;		// ͬ��ļ���ID
};

// *************************************************************************** //
// CMessageAgreeBattleResponse
// ͬ����ս��Ӧ
// *************************************************************************** //
message CMessageAgreeBattleResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				Result			=	2;		// ͬ��Ľ��
	optional uint32				FamilyID		=	3;		// ͬ��ļ���ID
};

// *************************************************************************** //
// CMessageQueryAllRoomRequest
// ��ѯ�����б�����
// *************************************************************************** //
message CMessageQueryAllRoomRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
};

message AllRoomInfo
{
	optional uint32		FamilyID		= 1;
	optional string		FamilyName		= 2;
	optional uint32		Money			= 3;
	optional string		RoomName		= 4;
	optional uint32		Win				= 5;
	optional uint32		Lost			= 6;
	optional string		AttName			= 7;
	optional uint32		State			= 8;
};

// *************************************************************************** //
// CMessageQueryAllRoomResponse
// ��ѯ�����б��Ӧ
// *************************************************************************** //
message CMessageQueryAllRoomResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				Result			=	2;		// ��ѯ�Ľ��
	repeated AllRoomInfo		RoomData		=	3;		// ������Ϣ
};

// *************************************************************************** //
// CMessageQueryMyRoomRequest
// ��ѯ�Լ��ķ�������
// *************************************************************************** //
message CMessageQueryMyRoomRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
};

message MyRoomInfo
{
	optional uint32		FamilyID		= 1;
	optional string		FamilyName		= 2;
	optional uint32		Win				= 3;
	optional uint32		Lost			= 4;
};

// *************************************************************************** //
// CMessageQueryMyRoomResponse
// ��ѯ�Լ��ķ����Ӧ
// *************************************************************************** //
message CMessageQueryMyRoomResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				Result			=	2;		// ��ѯ�Ľ��
	optional uint32				Money			=	3;		// ����Ľ��
	repeated MyRoomInfo			RoomData		=	4;		// ������Ϣ
	optional string				Name			=	5;		// ��������
};

// *************************************************************************** //
// CMessageQueryMyChaRequest
// ��ѯ�Լ�����ս����
// *************************************************************************** //
message CMessageQueryMyChaRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
};

message MyChaInfo
{
	optional uint32		FamilyID		= 1;
	optional string		FamilyName		= 2;
	optional uint32		Money			= 3;
	optional string		RoomName		= 4;
	optional uint32		Win				= 5;
	optional uint32		Lost			= 6;
};

// *************************************************************************** //
// CMessageQueryMyChaResponse
// ��ѯ�Լ�����ս��Ӧ
// *************************************************************************** //
message CMessageQueryMyChaResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				Result			=	2;		// ��ѯ�Ľ��
	repeated MyChaInfo			RoomData		=	3;		// ������Ϣ
};

// *************************************************************************** //
// CMessageAbortRoomRequest
// ������������
// *************************************************************************** //
message CMessageAbortRoomRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
};

// *************************************************************************** //
// CMessageAbortRoomResponse
// ���������Ӧ
// *************************************************************************** //
message CMessageAbortRoomResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				Result			=	2;		// �����Ľ��
};

// *************************************************************************** //
// CMessageAbortChaRequest
// ������ս����
// *************************************************************************** //
message CMessageAbortChaRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		FamilyID		=	2;		// �����ļ���ID
};

// *************************************************************************** //
// CMessageAbortChaResponse
// ������ս��Ӧ
// *************************************************************************** //
message CMessageAbortChaResponse
{
	optional FamilyHead			HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32				Result			=	2;		// �����Ľ��
	optional uint32				FamilyID		=	3;		// �����ļ���ID
};	  


// *************************************************************************** //
// CMessageContributeFamilyMoneyNotify
// ���׼����Ǯ��֪ͨ
// *************************************************************************** //
message CMessageContributeFamilyMoneyNotify
{
	optional FamilyHead	HeadMsg			=	1;	// ��Ϣͷ��������	
	optional uint32		FamilyMoney		=	2;	// �������н�Ǯ
	optional string		MemberName		=	3;	// ���׽�Ǯ�ĳ�Ա����
	optional uint32		MemberID		=	4;	// ���׽�Ǯ�ĳ�Ա��ɫID
	optional uint32		Value			=	5;	// ��ֵ
};

// *************************************************************************** //
// CMessageFamilyMoneyChangedNotify
// �����Ǯ�ı����Ϣ
// *************************************************************************** //
message CMessageFamilyMoneyChangedNotify
{
	optional uint32		Money	 =	1;		// ���嵱ǰ��Ǯ	
	optional uint32		RoleID	 =	2;		// ��������Ǯ�ı�Ľ�ɫID
	optional uint32		Reason	 =	3;		// ��Ǯ�ı��ԭ��
	optional string		RoleName =	4;		// ��������Ǯ�ı�Ľ�ɫ����
	optional int32		Value	 =	5;		// ��ֵ
};

// *************************************************************************** //
// CMessageUseFamilyExpCardNotify
// ʹ�þ������Ƶ�֪ͨ��Ϣ
// *************************************************************************** //
message CMessageUseFamilyExpCardNotify
{	
	optional string ManagerName	=	1;		// �峤����
	optional uint32	ManagerID	=	2;		// �峤��ɫID
	optional uint32	LineID		=	3;		// �峤������ID
	optional uint32	MapID		=	4;		// ��ͼID
	optional uint32	PosX		=	5;		// x����
	optional uint32	PosY		=	6;		// y����
};

// *************************************************************************** //
// CMessageStartFamilyBossRequest
// ��ͨ����boss�������
// *************************************************************************** //
message CMessageStartFamilyBossRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32 EnityID				=	2;		// npcID	
	optional uint32	RepetionLevel		=	3;		// ���帱���ȼ�	
	optional uint32	Date				=	4;		// ���븱����ʱ��
	optional uint32	MaxTimes			=	5;		// ���帱��һ����������������
};

// *************************************************************************** //
// CMessageMakeRoomNotify
// ���跿��֪ͨ
// *************************************************************************** //
message CMessageMakeRoomNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		HeaderID		=	2;		// �峤ID
	optional string		HeaderName		=	3;		// �峤����
};

// *************************************************************************** //
// CMessageStartFamilyBossResponse
// ��ͨ����boss��Ļظ���Ϣ
// *************************************************************************** //
message CMessageStartFamilyBossResponse
{	
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		Errcode			=	2;
};

// *************************************************************************** //
// *************************************************************************** //
// CMessageEnterBossReptionRequest
// ��Ա������帱��������
// *************************************************************************** //
message CMessageEnterBossReptionRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32	NpcID				=	2;		// npcID
	optional uint32 FamilyID			=	3;		// ����ID( �������� )
};

// *************************************************************************** //
// CMessageEnterBossReptionResponse
// ��Ա������帱������Ϣ��Ӧ
// *************************************************************************** //
message CMessageEnterBossReptionResponse
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		Errcode			=	2;		// ������
};

// *************************************************************************** //
// CMessageAbortRoomNotify
// ȡ������֪ͨ
// *************************************************************************** //
message CMessageAbortRoomNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		HeaderID		=	2;		// �峤ID
	optional string		HeaderName		=	3;		// �峤����
};

// *************************************************************************** //
// CMessageChaRoomNotify
// ��ս����֪ͨ
// *************************************************************************** //
message CMessageChaRoomNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		SrcFamilyID		=	2;		// ��ս����ID
	optional string		SrcFamilyName	=	3;		// ��ս��������
	optional uint32		SrcHeaderID		=	4;		// ��ս�峤ID
	optional string		SrcHeaderName	=	5;		// ��ս�峤����
	optional uint32		DesFamilyID		=	6;		// �������ID
	optional string		DesFamilyName	=	7;		// �����������
	optional uint32		DesHeaderID		=	8;		// �����峤ID
	optional string		DesHeaderName	=	9;		// �����峤����
	optional uint32		SrcWin			=	10;		// ��ս��ʤ
	optional uint32		SrcLost			=	11;		// ��ս����
};

// *************************************************************************** //
// CMessageAbortChaNotify
// ȡ����ս֪ͨ
// *************************************************************************** //
message CMessageAbortChaNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		SrcFamilyID		=	2;		// ȡ������ID
	optional string		SrcFamilyName	=	3;		// ȡ����������
	optional uint32		DesFamilyID		=	4;		// �������ID
	optional string		DesFamilyName	=	5;		// �����������
	optional string		HeaderName		=	6;		// �峤����
	optional uint32		ManagerID		=	7;		// �����Ĺ����ߵĽ�ɫID
	optional string		ManagerName		=	8;		// �����Ĺ����ߵĽ�ɫ����
};

// *************************************************************************** //
// CMessageFamilyGloryChangedNotify
// ������ҫ�ı��֪ͨ
// *************************************************************************** //
message CMessageFamilyGloryChangedNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		Glory			=	2;		// ���ڵ���ҫֵ
	optional uint32		RoleID			=	3;		// ������ҫֵ�ı����ҽ�ɫID
	optional uint32		Reason			=	4;		// ��ҫ�ı��ԭ��	
	optional string		RoleName		=	5;		// ��ɫ����
	optional int32		Value			=	6;		// ��ֵ
};

// *************************************************************************** //
// CMessageMemberContributeChangedNotify
// ���˹��׶ȸı��֪ͨ
// *************************************************************************** //
message CMessageMemberContributeChangedNotify
{ 
	optional FamilyHead	HeadMsg		=	1;		// ��Ϣͷ��������
	optional uint32	Contribute		=	2;		// ��ҵ�ǰ�Ĺ��׶�
	optional uint32	RoleID			=	3;		// ��ҽ�ɫID
	optional int32	Value			=	4;		// ��ֵ
};

// *************************************************************************** //
// CMessageQueryNpcWelfareRequest
// ��ѯnpc����������Ϣ����
// *************************************************************************** //
message CMessageQueryNpcWelfareRequest
{
	optional FamilyHead HeadMsg		=	1;		//	������Ϣͷ
	optional uint32		EntityID	=	2;		//	NPCʵ��ID
	optional uint32		NpcTmpID	=	3;		//	npc��ģ��ID(��������)
};

// *************************************************************************** //
// CMessageQueryNpcWelfareResponse
// ��ѯnpc����������Ϣ��Ӧ����ҫ�ͽ�Ǯ��
// *************************************************************************** //
message CMessageQueryNpcWelfareResponse
{
	optional FamilyHead HeadMsg		=	1;		//	������Ϣͷ
	optional uint32		Money		=	2;		//	������ȡ�Ľ�Ǯ
	optional uint32		Glory		=	3;		//	������ȡ����ҫֵ
	optional uint32		Errcode		=	4;
};

// *************************************************************************** //
// CMessageGetFamilyMoneyRequest
//  ��ȡ�����Ǯ�����˵���Ϣ����
// *************************************************************************** //
message  CMessageGetFamilyMoneyRequest
{
	optional FamilyHead HeadMsg		=	1;		//	������Ϣͷ
	optional uint32		FamilyMoney	=	2;		//	Ҫ��ȡ�Ľ�	
};

// *************************************************************************** //
// CMessageGetFamilyMoneyResponse
//  ��ȡ�����Ǯ�����˵���Ϣ��Ӧ
// *************************************************************************** //
message  CMessageGetFamilyMoneyResponse
{
	optional FamilyHead HeadMsg		=	1;		// ������Ϣͷ
	optional uint32		Errcode		=	2;		// ������
	optional uint32		FamilyMoney	=	3;		// Ҫ��ȡ�Ľ�	
};

// *************************************************************************** //
// CMessageAbortNpcNotify
// �峤����NPC֪ͨ
// *************************************************************************** //
message CMessageAbortNpcNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		NpcID			=	2;		// ������NPC ID
	optional string		HeaderName		=	3;		// �峤������
};

// *************************************************************************** //
// CMessagePreBattleNotify
// ����սս��ǰ֪ͨ
// *************************************************************************** //
message CMessagePreBattleNotify
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		NpcID			=	2;		// ս����NPC ID
	optional string		AttFamilyName	=	3;		// ��ս����������
	optional string		DefFamilyName	=	4;		// ���ط���������
	optional uint32		Money			=	5;		// ���۵�Ǯ��
};

// *************************************************************************** //
// CMessageGetExpCardRequest
// ��ȡ�������Ƶ�����
// *************************************************************************** //
message CMessageGetExpCardRequest
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		Msgcode			=	2;		// ���ò���
};

// *************************************************************************** //
// CMessageGetExpCardResponse
// ��ȡ�������ƵĻ�Ӧ
// *************************************************************************** //
message CMessageGetExpCardResponse
{
	optional FamilyHead	HeadMsg			=	1;		// ��Ϣͷ��������
	optional uint32		Errcode			=	2;		// ������
	optional uint32		RedStoneID		=	3;		// �����ڵ�ID
};

// *************************************************************************** //
// CMessageFamilyCanLevelUPNotify
// �������������֪ͨ��Ϣ
// *************************************************************************** //
message CMessageFamilyCanLevelUPNotify
{
	optional FamilyHead HeadMsg		= 1;		// ������Ϣͷ	
};

// *************************************************************************** //
// CMessageFamilyRepetionScoreNotify
// ���帱�����ֵ�֪ͨ
// *************************************************************************** //
message CMessageFamilyRepetionScoreNotify
{		
	optional uint32	 RepetionLevel	=	1;	// �����Ѷ�
	optional uint32	 OgreNum		=	2;	// ɱ����Ŀ
	optional uint32	 TimeLength		=	3;	// ����ͨ��ʱ��
	optional uint32	 WaveNum		=	4;	// �ڼ���
	optional uint32	 MaxHitNum		=	5;	// ���������
	optional uint32	 Score			=	6;	// �����ܷ�
};

// *************************************************************************** //
// CMessageGetFamilyGoodsListRequest
// ��ȡ������Ʒ�б����Ϣ����
// *************************************************************************** //
message GoodItem
{
	optional uint32 ItemID		= 1;
	optional uint32	ItemNum		= 2;
	optional uint32	ComposeID	= 3;	// ���Ӻϳ�ID���һ���
};

message CMessageGetFamilyGoodsListRequest
{
	optional FamilyHead HeadMsg = 1;		// ������Ϣͷ
	optional uint32	FamilyID =	2;			// ����Id(������ֵ)
	optional uint32	EntityID =  3;			// npcʵ��ID
	optional uint32	NpcTmpID =	4;			// npcģ��ID
};

// *************************************************************************** //
// CMessageGetFamilyGoodsListResponse
// ��ȡ������Ʒ�б����Ϣ��Ӧ
// *************************************************************************** //
message CMessageGetFamilyGoodsListResponse
{	
	optional FamilyHead HeadMsg		= 1;		// ������Ϣͷ
	optional uint32		Errcode		= 2;		// ������
	repeated GoodItem	GoodsList	= 3;		// �����Ѿ��������Ʒ�б�
	optional uint32		NpcTmpID	= 4;		// npc��ģ��ID(��������)	
};

// *************************************************************************** //
// CMessageGetFamilyExchangeGoodsListRequest
// ��ȡ����һ���Ʒ�б����Ϣ����
// *************************************************************************** //
message CMessageGetFamilyExchangeGoodsListRequest
{
	optional FamilyHead HeadMsg = 1;		// ������Ϣͷ
	optional uint32	FamilyID =	2;			// ����Id(������ֵ)
	optional uint32	EntityID =  3;			// npcʵ��ID	
	optional uint32	NpcTmpID	= 4;		// npc��ģ��ID(��������)	
};

// *************************************************************************** //
// CMessageGetFamilyExchangeGoodsListResponse
// ��ȡ����һ���Ʒ�б����Ϣ��Ӧ
// *************************************************************************** //
message CMessageGetFamilyExchangeGoodsListResponse
{
	optional FamilyHead HeadMsg		= 1;		// ������Ϣͷ
	optional uint32		Errcode		= 2;		// ������
	repeated GoodItem	GoodsList	= 3;		// �ܹ��һ�����Ʒ�б��������
	optional uint32		NpcTmpID	= 4;		// npc��ģ��ID		
};

// *************************************************************************** //
// CMessageChangeGoodsListNotify
// �����̵깺�����Ʒ�б����仯��֪ͨ
// *************************************************************************** //
message CMessageChangeFamilyGoodsListNotify
{
	repeated GoodItem	GoodList	= 1;		// �����仯����Ʒ���б�
	optional uint32		NpcTmpID	= 2;		// npc��ģ��ID
};

// *************************************************************************** //
// CMessageChangeExchangeGoodsListNotify
// ����һ��̵���Ʒ�б����仯��֪ͨ
// *************************************************************************** //
message CMessageChangeFamilyExchangeGoodsListNotify
{
	repeated GoodItem	GoodList	= 1;		// �����仯�Ķһ���Ʒ���б�	
};

// *************************************************************************** //
// CMessageChangeExchangeGoodsListNotify
// ����һ��̵���Ʒ�б����仯��֪ͨ
// *************************************************************************** //
message CMessageUseFamilyLeagueItemNotify
{
	repeated GoodItem	GoodList	= 1;		// �����仯�Ķһ���Ʒ���б�	
	optional uint32		ManagerID	= 2;		// �����߽�ɫID
	optional string		ManagerName	= 3;		// �����߽�ɫ����	
};

// ��ü����԰��Ϣ����
message CMessageGetHomeInfoRequest
{
	optional uint32		CharID		= 1;
	optional uint32		FamilyID	= 2;
};


// ��ü����԰��Ϣ��Ӧ
message CMessageGetHomeInfoResponse
{
	optional uint32		CharID		= 1;
	optional uint32		FamilyID	= 2;
	optional uint32		Result		= 3;
	repeated uint32		Wizard		= 4;		// ����Ż�
	repeated uint32		Construct	= 5;		// ���彨���
	repeated uint32		Level		= 6;		// ���彨��ȼ�
	repeated uint32		UpData		= 7;		// ������һ����ֵ
};


// ������ͨ�����԰����������
message CMessageUpgradeHomeRequest
{
	optional uint32		CharID		= 1;	
	optional uint32		Type		= 2;
};

// ������ͨ�����԰�������Ӧ
message CMessageUpgradeHomeResponse
{
	optional uint32		CharID		= 1;	
	optional uint32		Type		= 2;		// ��������
	optional uint32		UpData		= 3;		// ������һ����ֵ
};

// ���尲���ȸı��֪ͨ
message CMessageFamilyStabilityChangedNotify
{
	optional uint32		Reason		= 1;		// �ı��ԭ��
	optional uint32		Stability	= 2;		// ��ǰ���尲����	
	optional uint32		Value		= 3;		// �ı�İ�����ֵ
	optional uint32		RoleID		= 4;		// �ü��尲���ȸı�Ľ�ɫID
	optional string		RoleName	= 5;		// �ü��尲���ȸı�Ľ�ɫ����
	optional uint32		OnLineTime	= 6;		// ʹ���尲�������ӵ��ۻ�����ʱ��(��λ:Сʱ)
};