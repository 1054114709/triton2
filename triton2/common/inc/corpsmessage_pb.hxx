option optimize_for = SPEED;
import "familydbinfo_pb.hxx";
import "corpsinfo_pb.hxx";

enum CorpsMessageID
{ 
	ID_C2S_REQUEST_CREATCORPS					= 0x3800;		// �������ŵ�����
	ID_S2C_RESPONSE_CREATCORPS 					= 0x3801;		// �������ŵĻ�Ӧ��Ϣ
	
	ID_C2S_REQUEST_APPLYCORPS					= 0x3802;		// ���������ŵ�������Ϣ
	ID_S2C_RESPONSE_APPLYCORPS					= 0x3803;		// ���������ŵĻ�Ӧ��Ϣ
	ID_S2C_NOTIFY_CORPSMEMBERAPPLY				= 0x3804;		// �м������������ŵ���Ϣ֪ͨ
	ID_C2S_REQUEST_REPLYCORPSMEMBERAPPLY		= 0x3805;		// �ظ��������������ŵ���Ϣ����
	ID_S2C_RESPONSE_REPLYCORPSMEMBERAPPLY		= 0x3806;		// �ظ��������������ŵ���Ϣ��Ӧ
	ID_S2C_NOTIFY_APPLYCORPSRESULT				= 0x3807;		// ���������ŵĽ��֪ͨ
	
	ID_C2S_REQUEST_INVITECORPSMEMBER			= 0x3808;		// ������������ŵ���Ϣ����
	ID_S2C_RESPONSE_INVITECORPSMEMBER			= 0x3809;		// ������������ŵ���Ϣ��Ӧ
	ID_S2C_NOTIFY_CORPSINVITE					= 0x380A;		// ���������ŵ���Ϣ֪ͨ
	ID_C2S_REQUEST_REPLYCORPSINVITE				= 0x380B;		// �𸴾����������Ϣ����
	ID_S2C_RESPONSE_REPLYCORPSINVITE			= 0x380C;		// �𸴾����������Ϣ�ظ�
	ID_S2C_NOTIFY_CORPSINVITERESULT				= 0x380D;		// ������������ŵĽ��֪ͨ
	
	ID_S2C_NOTIFY_FAMILYJOINCORPS				= 0x380E;		// �м��������ŵ���Ϣ֪ͨ
	
	ID_C2S_REQUEST_LEAVECORPS					= 0x380F;		// �����뿪���ŵ���Ϣ����
	ID_S2C_RESPONSE_LEAVECORPS					= 0x3810;		// �����뿪���ŵ���Ϣ��Ӧ
	
	ID_S2C_NOTIFY_FAMILYLEAVED					= 0x3811;		// �����뿪���ŵ���Ϣ֪ͨ
	
	ID_C2S_REQUEST_KICKFAMILY					= 0x3812;		// �Ӿ����߳��������Ϣ����
	ID_S2C_RESPONSE_KICKFAMILY					= 0x3813;		// �Ӿ����߳��������Ϣ��Ӧ
	
	ID_S2C_NOTIFY_FAMILYKICKED					= 0x3814;		// ����Ӿ������汻�ߵ���֪ͨ	
	
	
	ID_C2S_REQUEST_GETCORPSFAMILYINFO			= 0x3815;		// ��ȡ���ż����Ա��Ϣ������
	ID_S2C_RESPONSE_GETCORPSFAMILYINFO			= 0x3816;		// ��ȡ���ż����Ա��Ϣ�Ļ�Ӧ��Ϣ
	
	ID_C2S_REQUEST_GETCORPSPROPERTYINFO			= 0x3817;		// ��ȡ����������Ϣ��������Ϣ
	ID_S2C_RESPONSE_GETCORPSPROPERTYINFO		= 0x3818;		// ��ȡ����������Ϣ�Ļ�Ӧ��Ϣ
	
	ID_C2S_REQUEST_GETCOPRSFAMILYMEMBER			= 0x3819;		// ��ȡ������ĳ������ĳ�Ա��Ϣ����Ϣ����
	ID_S2C_RESPONE_GETCOPRSFAMILYMEMBER			= 0x381A;		// ��ȡ������ĳ������ĳ�Ա��Ϣ����Ϣ��Ӧ
	
	ID_C2S_REQUEST_CHANGECORPSBULLETIN			= 0x381B;		// �ı���Ź������Ϣ����
	ID_S2C_RESPONSE_CHANGECORPSBULLETIN			= 0x381C;		// �ı���Ź������Ϣ�ظ�
	
	ID_S2C_NOTIFY_CHANGECORPSBULLETIN			= 0x381D;		// �ı���Ź������Ϣ֪ͨ
	
	ID_C2S_REQUEST_CHANGECORPSHEADER			= 0x381E;		// �ı�����������Ϣ����
	ID_S2C_RESPONSE_CHANGECORPSHEADER			= 0x381F;		// �ı�����������Ϣ�ظ�
	
	ID_S2C_NOTIFY_CHANGECORPSHEADER				= 0x3820;		// �ı�����������Ϣ֪ͨ
	
	ID_C2S_REQUEST_GETCORPSAPPLYLIST			= 0x3821;		// ��ȡ�����б����Ϣ����
	ID_S2C_RESPONSE_GETCORPSAPPLYLIST			= 0x3822;		// ��ȡ�����б����Ϣ��Ӧ
	
	ID_C2S_REQUEST_DISBANDCORPS					= 0x3823;		// ��ɢ���ŵ���Ϣ����
	ID_S2C_RESPONSE_DISBANDCORPS				= 0x3824;		// ��ɢ���ŵ���Ϣ��Ӧ
	
	ID_S2C_NOTIFY_DISBANDCORPS					= 0x3825;		// ��ɢ���ŵ���Ϣ֪ͨ
	
	ID_C2S_REQUEST_CANCELCORPSDISBAND			= 0x3826;		// ȡ����ɢ�������Ϣ����
	ID_S2C_RESPONSE_CANCELCORPSDISBAND			= 0x3827;		// ȡ����ɢ�������Ϣ��Ӧ
	
	ID_C2S_REQUEST_CLEARCORPSAPPLY				= 0x3828;		// ������������б���Ϣ����
	ID_S2C_RESPONSE_CLEARCORPSAPPLY				= 0x3829;		// ������������б����Ϣ��Ӧ
	
	ID_C2S_REQUEST_REFRESHCORPSINFO				= 0x382A;		// ˢ�¾�����Ϣ������
	ID_S2C_RESPONSE_REFRESHCORPSINFO			= 0x382B;		// ˢ�¾�����Ϣ����Ϣ�ظ�
	
	ID_C2S_REQUEST_GETCOPRSLIST					= 0x382C;		// ��ȡ������Ϣ����Ϣ����
	ID_S2C_RESPONSE_GETCORPSLIST				= 0x382D;		// ��ȡ������Ϣ����Ϣ��Ӧ

	ID_C2S_REQUEST_BATTLEBID					= 0x382E;		// ����ս������������
	ID_S2C_RESPONSE_BATTLEBID					= 0x382F;		// ����ս�������ۻظ�

	ID_C2S_REQUEST_QUERYBIDRANK					= 0x3830;		// �鿴�������а�����
	ID_S2C_RESPONSE_QUERYBIDRANK				= 0x3831;		// �鿴�������а�ظ�

	ID_C2S_REQUEST_SELECTFAMILY					= 0x3832;		// ѡ����帳���ս�ʸ�����
	ID_S2C_RESPONSE_SELECTFAMILY				= 0x3833;		// ѡ����帳���ս�ʸ�ظ�
	
	ID_C2S_REQUEST_SETCORPSPOST					= 0x3834;		// ���þ��ų�Աְλ����Ϣ����
	ID_S2C_RESPONSE_SETCORPSPOST				= 0x3835;		// ���þ��ų�Աְλ����Ϣ��Ӧ	
	
	ID_C2S_REQUEST_LEVELUPCORPS					= 0x3836;		// �������ŵ���Ϣ����
	ID_S2C_RESPONSE_LEVELUPCORPS				= 0x3837;		// �������ŵ���Ϣ��Ӧ
	
	ID_C2S_REQUEST_CONTRIBUTECORPSMONEY			= 0x3838;		// ���׾��Ž�Ǯ����Ϣ����
	ID_S2C_RESPONSE_CONTRIBUTECORPSMONEY		= 0x3839;		// ���׾��Ž�Ǯ����Ϣ��Ӧ
	
	ID_C2S_REQUEST_FAMILYCONTRIBUTEMONEY		= 0x383A;		// ��������Ź��׽�Ǯ����Ϣ����
	ID_S2C_RESPONSE_FAMILYCONTRIBUTEMONEY		= 0x383B;		// ��������Ź��׽�Ǯ����Ϣ��Ӧ
	
	ID_C2S_REQUEST_SETMEMBERNAME				= 0x383C;		// ���þ��ų�Ա�ƺŵ���Ϣ����
	ID_S2C_RESPONSE_SETMEMBERNAME				= 0x383D;		// ���þ��ų�Ա�ƺŵ���Ϣ��Ӧ
	
	ID_S2C_NOTIFY_SETCORPSPOST					= 0x383E;		// ���þ���ְλ��֪ͨ
	
	ID_S2C_NOTIFY_CORPSLEVELUP					= 0x383F;		// ����������֪ͨ
	
	ID_S2C_NOTIFY_CORPSPVPSTARLEVELUP				= 0x3840;		// ����pvp�ȼ�������֪ͨ	

	ID_S2C_NOTIFY_CORPSBATTLERIGHTS				= 0x3841;		// �����ʸ�֪ͨ
	ID_S2C_NOTIFY_RECBATTLERIGHTS				= 0x3842;		// �����ս�ʸ�֪ͨ

	ID_C2S_REQUEST_SELECTBATTLE					= 0x3843;			// ѡ���Ա�μ�ս������
	ID_S2C_RESPONSE_SELECTBATTLE				= 0x3844;			// ѡ���Ա�μ�ս����Ӧ

	ID_S2C_NOTIFY_MEMBERBATTLERIGHTS			= 0x3845;			// ���˲�ս�ʸ�֪ͨ
	
	ID_S2C_NOTIFY_CORPSMONEYCHANGED				= 0x3846;			// ���ľ��Ž�Ǯ��֪ͨ
	ID_S2C_NOTIFY_CORPSGLORYCHANGED				= 0x3847;			// ������ҫ�ı��֪ͨ
	ID_S2C_NOTIFY_CORPSCONTRIBUTECHANGED		= 0x3848;			// ���Ÿ��˹��׶ȸı��֪ͨ 

	ID_C2S_REQUEST_MENDSHENGHUOTAI				= 0x3849;	// ����ʥ��̨����
	ID_S2C_NOTIFY_CORPSPROPERTY					= 0x384A;	// �������Ը�����Ϣ

	ID_C2S_REQUEST_CHALLEGE						= 0x384B;	// ������ս
	ID_S2C_RESPONSE_CHALLEGE					= 0x384C;	// ��ս�ظ�
	ID_S2C_NOTIFY_CHALLEGE						= 0x384D;	// ��ս֪ͨ

	ID_C2S_REQUEST_ROOMOPERATION				= 0x384E;	// ��������
	ID_S2C_RESPONSE_ROOMOPERATION				= 0x384F;	// ����ظ�
	ID_S2C_NOTIFY_ROOM							= 0x3850;	// ����֪ͨ

	ID_C2S_REQUEST_REPLYCHALLEGE				= 0x3851;	// �ظ���ս����
	ID_S2C_RESPONSE_REPLYCHALLEGE				= 0x3852;	// �ظ���ս����Ļظ�

	ID_C2S_REQUEST_QUERYROOM					= 0x3853;	// ��ѯ��������
	ID_S2C_RESPONSE_QUERYROOM					= 0x3854;	// ��ѯ����ظ�

	ID_C2S_REQUEST_QUERYCHALLEGELIST			= 0x3855;	// ��ѯ��ս�б�
	ID_S2C_RESPONSE_QUERYCHALLEGELIST			= 0x3856;	// ��ѯ��ս�б�

	ID_C2S_REQUEST_QUERYRECCHALLEGE				= 0x3857;	// �յ�����ս�б��ѯ
	ID_S2C_RESPONSE_QUERYRECCHALLEGE			= 0x3858;	// �յ�����ս�б��ѯ
	
	ID_C2S_REQUEST_QUERYCORPSWELFARE			= 0x3859;	// ��ѯ����npc��������Ϣ����
	ID_S2C_RESPONSE_QUERYCORPSWELFARE			= 0x385A;	// ��ѯ����npc��������Ϣ��Ӧ
	
	ID_C2S_REQUEST_OBTAINCORPSWELFARE			= 0x385B;	// ��ȡ���Ÿ�������Ϣ����
	ID_S2C_RESPONSE_OBTAINCORPSWELFARE			= 0x385C;	// ��ȡ���Ÿ�������Ϣ��Ӧ
	
	ID_C2S_REQUEST_GETCORPSMONEY				= 0x385D;	// �Ѿ��Ž�Ǯ��ȡΪ���˽�Ǯ������
	ID_S2C_RESPONSE_GETCORPSMONEY				= 0x385E;	// �Ѿ��Ž�Ǯ��ȡΪ���˽�Ǯ����Ϣ��Ӧ	

	ID_C2S_REQUEST_ABORTBATTLECITY				= 0x385F;
	ID_S2C_RESPONSE_ABORTBATTLECITY				= 0x3860;
	ID_S2C_NOTIFY_ABORTBATTLECITY				= 0x3861;
	
	ID_S2C_NOTIFY_CORPSCANLEVELUP				= 0x3862;	// ���ſ�����������Ϣ֪ͨ

	ID_S2C_NOTIFY_CORPSBATTLERESULT				= 0x3863;

	ID_S2C_NOTIFY_NPCOWNERUPDATE				= 0x3864;	
	
	ID_S2C_NOTIFY_CORPSNAMECHANGED				= 0x3865;	// ���ųƺŸı��֪ͨ 


	ID_C2S_REQUEST_CREATEUNION					= 0x386E;		// ������������
	ID_S2C_RESPONSE_CREATEUNION					= 0x386F;		// ����������Ӧ
	ID_S2C_NOTIFY_CREATEUNION					= 0x3870;		// ��������֪ͨ

	ID_C2S_REQUEST_APPLYUNION					= 0x3871;		// �������������������Ϣ
	ID_S2C_RESPONSE_APPLYUNION					= 0x3872;		// ������������Ļ�Ӧ��Ϣ
	ID_S2C_NOTIFY_UNIONMEMBERAPPLY				= 0x3873;		// �о������������������Ϣ֪ͨ
	ID_C2S_REQUEST_REPLYUNIONMEMBERAPPLY		= 0x3874;		// �ظ��������������������Ϣ����
	ID_S2C_RESPONSE_REPLYUNIONMEMBERAPPLY		= 0x3875;		// �ظ��������������������Ϣ��Ӧ
	ID_S2C_NOTIFY_APPLYUNIONRESULT				= 0x3876;		// ������������Ľ��֪ͨ

	ID_C2S_REQUEST_INVITEUNIONMEMBER			= 0x3877;		// ������ż�����������Ϣ����
	ID_S2C_RESPONSE_INVITEUNIONMEMBER			= 0x3878;		// ������ż�����������Ϣ��Ӧ
	ID_S2C_NOTIFY_UNIONINVITE					= 0x3879;		// ���������������Ϣ֪ͨ
	ID_C2S_REQUEST_REPLYUNIONINVITE				= 0x387A;		// �������������Ϣ����
	ID_S2C_RESPONSE_REPLYUNIONINVITE			= 0x387B;		// �������������Ϣ�ظ�
	ID_S2C_NOTIFY_UNIONINVITERESULT				= 0x387C;		// ������ż��������Ľ��֪ͨ

	ID_S2C_NOTIFY_CORPSJOINUNION				= 0x387D;		// �о��ż�����������Ϣ֪ͨ

	ID_C2S_REQUEST_LEAVEUNION					= 0x387E;		// �����뿪��������Ϣ����
	ID_S2C_RESPONSE_LEAVEUNION					= 0x387F;		// �����뿪��������Ϣ��Ӧ

	ID_S2C_NOTIFY_CORPSLEAVED					= 0x3880;		// �����뿪��������Ϣ֪ͨ

	ID_C2S_REQUEST_KICKCORPS					= 0x3881;		// �������߳����ŵ���Ϣ����
	ID_S2C_RESPONSE_KICKCORPS					= 0x3882;		// �������߳����ŵ���Ϣ��Ӧ
	ID_S2C_NOTIFY_CORPSKICKED					= 0x3883;		// ���Ŵ��������汻�ߵ���֪ͨ

	ID_C2S_REQUEST_MAKEUNION					= 0x3884;		// ������������
	ID_S2C_RESPONSE_MAKEUNION					= 0x3885;		// ����������Ӧ
	ID_S2C_NOTIFY_MAKEUNION						= 0x3886;		// ��������֪ͨ
	ID_C2S_REQUEST_UNIONINFO					= 0x3887;		// ������Ϣ����
	ID_S2C_RESPONSE_UNIONINFO					= 0x3888;		// ������Ϣ��Ӧ
	ID_C2S_REQUEST_DISMISSUNION					= 0x3889;		// ��ɢ��������
	ID_S2C_RESPONSE_DISMISSUNION				= 0x388A;		// ��ɢ������Ӧ
	ID_S2C_NOTIFY_DISMISSUNION					= 0x388B;		// ��ɢ����֪ͨ
	ID_C2S_REQUEST_UNIONAPPLYLIST				= 0x388C;		// ������������б�����
	ID_S2C_RESPONSE_UNIONAPPLYLIST				= 0x388D;		// ������������б��Ӧ
	ID_C2S_REQUEST_ALLUNIONLIST					= 0x388E;		// ��������б�����
	ID_S2C_RESPONSE_ALLUNIONLIST				= 0x388F;		// ��������б��Ӧ

	ID_C2S_REQUEST_GETOTHERMEMBER				= 0x3890;		// ����������Ų�ս��Ա�б�
	ID_S2C_RESPONSE_GETOTHERMEMBER				= 0x3891;		// ����������Ų�ս��Ա�б�

	ID_C2S_REQUEST_UNIONSUBMIT					= 0x3892;		// �����˲�ս
	ID_S2C_RESPONSE_UNIONSUBMIT					= 0x3893;		// �����˲�ս

	ID_C2S_REQUEST_GETALLMAP					= 0x3894;		// ������ռ��ͼ
	ID_S2C_RESPONSE_GETALLMAP					= 0x3895;		// ������ռ��ͼ

	ID_C2S_REQUEST_APPOINTPRINCE				= 0x3896;
	ID_S2C_RESPONSE_APPOINTPRINCE				= 0x3897;
	ID_S2C_NOTIFY_APPOINTPRINCE					= 0x3898;

	ID_C2S_REQUEST_MOVECAPITAL					= 0x3899;
	ID_S2C_RESPONSE_MOVECAPITAL					= 0x389A;

	ID_C2S_REQUEST_SELECTCOLOR					= 0x389B;
	ID_S2C_RESPONSE_SELECTCOLOR					= 0x389C;
	
	ID_C2S_REQUEST_GETCORPSGOODSLIST			= 0x389F;			// ��ȡ������Ʒ�б����Ϣ����
	ID_S2C_RESPONSE_GETCORPSGOODSLIST			= 0x38A0;;			// ��ȡ������Ʒ�б����Ϣ��Ӧ

	ID_C2S_REQUEST_GETCORPSEXCHANGEGOODSLIST	= 0x38A1;		// ��ȡ���Ŷһ���Ʒ�б����Ϣ����
	ID_S2C_RESPONSE_GETCORPSEXCHANGEGOODSLIST 	= 0x38A2;		// ��ȡ���Ŷһ���Ʒ�б����Ϣ��Ӧ
	
	ID_S2C_NOTIFY_CHANGECORPSGOODSLIST			= 0x38A3;		// �����̵���Ʒ�б����仯��֪ͨ
	ID_S2C_NOTIFY_CHANGEXCHANGEECORPSGOODSLIST	= 0x38A4;		// ���Ŷһ��̵���Ʒ�б����仯��֪ͨ	

	ID_C2S_REQUEST_CHANGEUNIONNAME				= 0x38A5;	// �������˸���
	ID_S2C_RESPONSE_CHANGEUNIONNAME				= 0x38A6;
	ID_S2C_NOTIFY_CHANGEUNIONNAME				= 0x38A7;  
	
	ID_S2C_NOTIFY_USECORPSLEAGUEITEM			= 0x38A8;	// ʹ�þ����ع���Ʒ��֪ͨ  

	ID_C2S_REQUEST_LOGINBATTLE					= 0x38A9;	// ����ս������
	ID_S2C_RESPONSE_LOGINBATTLE					= 0x38AA;	// ����ս���ظ�
	ID_S2C_CORPSBOSSTIMES_CHANGED_NOTIFY		= 0x38AB;	// ֪ͨ����boss�����ı�
	ID_S2C_CORPSBOSSREFINEVALUE_CHANGED_NOTIFY	= 0x38AC;	// ֪ͨ����boss������ֵ

	ID_C2S_SUMMON_CORPSBOSS_REQUEST				= 0x38AD;	// �ٻ�����boss
	ID_S2C_SUMMON_CORPSBOSS_RESPONSE			= 0x38AE;	// �ٻ�����boss��Ӧ
	ID_S2C_CORPSBOSSREPETION_OPEN_NOTIFY		= 0x38AF;	// ����boss����֪ͨ
	ID_S2C_INTO_CORPSBOSS_REPETION_RESPONSE		= 0x38B0;	// �������boss������Ӧ
	ID_S2C_CORPSBOSSREPETION_END_NOTIFY			= 0x38B1;	// ���Ÿ�������

	ID_S2C_NOTIFY_CORPSCOLLECTACTIVECHANGED		= 0x38B2;	// ���Ųɼ���Ծ�ȱ仯֪ͨ
	ID_S2C_NOTIFY_CORPSPUBLISHTASK				= 0x38B3;	// ���ŷ�������֪ͨ
};

// *************************************************************************** //
// CorpsHead  
// ������Ϣͷ
// *************************************************************************** //
message CorpsHead
{
	optional uint32   RoleID	=	1;				// ��ɫID
	optional uint32   MsgID     =	2;			    // ��ϢID
	optional uint32	  EntityID	=	3;				// �ڳ����е�ʵ��ID
};

// *************************************************************************** //
// CMessageCreatCorpsRequest  
// �����������Ϣ����
// *************************************************************************** //
message CMessageCreatCorpsRequest
{
	optional CorpsHead	CorpHead	= 1;					// ������Ϣͷ
	optional string		CorpsName	= 2;				    // ��������
	optional uint32		NpcEntityID = 3;					// ����NPC��ʵ��ID
	optional uint32		CorpsColor	= 4;					// ������ɫ
};

// *************************************************************************** //
// CMessageCreatCorpsRequest  
// �����������Ϣ����
// *************************************************************************** //
message CMessageCreatCorpsResponse
{
	optional CorpsHead	CorpHead	= 1;			// ������Ϣͷ
	optional uint32		Errcode		= 2;			// 0��ʾ�ɹ�������ʾ������
	optional string		CorpsName	= 3;			// ��������
	optional uint32		CorpsID		= 4;			// ����ID
	optional uint32		CorpsColor	= 5;			// ������ɫ
};

// *************************************************************************** //
// CMessageApplyCorpsRequest  
// ���������ŵ���Ϣ����
// *************************************************************************** //
message CMessageApplyCorpsRequest
{		
	optional CorpsHead	CorpHead		= 1;			// ������Ϣͷ
	optional string		CorpsName		= 2;			//	��������
	optional uint32		CorpsID			= 3;			//	����ID
	optional uint32		RoleID			= 4;			//	��ҽ�ɫID
};



// *************************************************************************** //
// CMessageApplyCorpsResponse  
// ���������ŵ���Ϣ��Ӧ
// *************************************************************************** //
message CMessageApplyCorpsResponse
{			
	optional CorpsHead	CorpHead	= 1;			// ������Ϣͷ
	optional uint32		Errcode		= 2;			// ������0��ʾ�ɹ�������ʾ������
	optional string		CorpsName	= 3;			// ��������
};

// *************************************************************************** //
// CMessageCorpsMemberApplyNotify  
// �м������������ŵ���Ϣ֪ͨ
// *************************************************************************** //
message CMessageCorpsMemberApplyNotify
{			
	optional CorpsHead	CorpHead	= 1;			// ������Ϣͷ
	optional FamilyData FamilyInfo	= 2;			// ����������Ϣ
};

// *************************************************************************** //
// CMessageReplyCorpsMemberApplyRequest  
// �𸴼����������Ϣ����
// *************************************************************************** //
message CMessageReplyCorpsMemberApplyRequest
{																		
	optional CorpsHead	CorpHead	= 1;				// ������Ϣͷ
	optional uint32		Result		= 2;				// ���ڼ�������Ļظ�1��ʾͬ��0��ʾ��ͬ��
	optional uint32		FamilyID	= 3;				// �������ļ����ID		
};

// *************************************************************************** //
// CMessageReplyCorpsMemberApplyResponse  
// �м������������ŵ���Ϣ֪ͨ
// *************************************************************************** //
message CMessageReplyCorpsMemberApplyResponse
{
	optional CorpsHead	CorpHead	= 1;				// ������Ϣͷ
	optional uint32		Errcode		= 2;				// 0��ʾ�����ɹ�������ʾ������
	optional uint32		Result		= 3;				// ֮ǰ�Ĵ𸴽��
	optional uint32		FamilyID	= 4;				// ����ID		
};

// *************************************************************************** //
// CMessageApplyCorpsResultNotify  
// ���������ŵĽ��֪ͨ
// *************************************************************************** //
message CMessageApplyCorpsResultNotify
{
	optional CorpsHead	CorpHead	= 1;				// ������Ϣͷ
	optional uint32 ResultCode		= 2;				// 1��ʾ����ɹ�0��ʾ���ܾ�������ʾ������
	optional uint32 CorpsID			= 3;				// ����ID
	optional string CorpsName		= 4;				// ��������
	optional uint32	UnionID			= 5;				// ��������ID
	optional string	UnionName		= 6;				// ������������
};


// *************************************************************************** //
// CMessageInviteCorpsMemberRequest  
// ������������ŵ���Ϣ����
// *************************************************************************** //
message CMessageInviteCorpsMemberRequest
{
	optional CorpsHead	CorpHead	= 1;				// ������Ϣͷ
	optional string FamilyName		= 2;				// ��������
	optional uint32 FamilyID		= 3;				// ����ID,Ŀǰ����
	optional uint32	MemberID		= 4;				// ��ɫID		
};


// ***************************************************************************//
// CMessageInviteCorpsMemberResponse  
// ������������ŵ���Ϣ��Ӧ
// ***************************************************************************//
message CMessageInviteCorpsMemberResponse
{
	optional CorpsHead	CorpHead	= 1;				// ������Ϣͷ
	optional uint32 Errcode			= 2;				// ������0��ʾ�ɹ�������ʾ������
	optional string FamilyName		= 3;				// ��������
};

// ***************************************************************************//
// CMessageCorpsInviteNotify  
// ���������ŵ���Ϣ֪ͨ
// ***************************************************************************//
message CMessageCorpsInviteNotify
{
	optional CorpsHead	CorpHead		= 1;			// ������Ϣͷ
	optional string InvitingName		= 2;			// ����������
	optional uint32 InvitingID			= 3;			// ������ID	
	optional PBCorpsBasicInfo CorpsInfo = 4;			// ������Ϣ 
};	

// ***************************************************************************//
// CMessageReplyCorpsInviteRequest  
// �𸴾����������Ϣ����
// ***************************************************************************//
message CMessageReplyCorpsInviteRequest
{
	optional CorpsHead	CorpHead		= 1;			// ������Ϣͷ
	optional uint32	 Result				= 2;			// 1��ʾͬ��������0��ʾ�ܾ��������
	optional uint32	 CorpsID			= 3;			// ����ID
	optional uint32	 InvitingID			= 4;			// ������ID
};

// ***************************************************************************//
// CMessageReplyCorpsInviteResponse  
// �𸴾����������Ϣ�ظ�
// ***************************************************************************//
message CMessageReplyCorpsInviteResponse
{
	optional CorpsHead	CorpHead		= 1;			// ������Ϣͷ
	optional uint32	Errcode				= 2;			// ������0��ʾ�ɹ�������ʾ������
	optional uint32 Result				= 3;			// �𸴽��
	optional string	CorpsName			= 4;			// ��������
	optional uint32 CorpsID				= 5;			// ����ID
	optional uint32	UnionID				= 6;			// ��������ID
	optional string	UnionName			= 7;			// ������������	
};

// ***************************************************************************//
// CMessageCorpsInviteResultNotify  
// ������������ŵĽ��
// ***************************************************************************//
message CMessageCorpsInviteResultNotify
{
	optional CorpsHead	CorpHead		= 1;			// ������Ϣͷ
	optional uint32 Result				= 2;			// 1��ʾ����ɹ�0��ʾ���ܾ�������ʾ������
	optional string FamilyName			= 3;			// ������ļ��������
};	 

																						
// ***************************************************************************//
// CMessageFamilyJoinCorpsNotify															  
// �м��������ŵ���Ϣ֪ͨ
// ***************************************************************************//
message CMessageFamilyJoinCorpsNotify
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional PBCorpsMember	FamilyInfo		= 2;			// ����������Ϣ
	optional uint32			UnionID			= 3;			// ��������ID
	optional string			UnionName		= 4;			// ������������	
};

// ***************************************************************************//
// CMessageFamilyLeaveCorpsRequest  
// �����뿪���ŵ���Ϣ����
// ***************************************************************************//
message CMessageFamilyLeaveCorpsRequest
{
	optional CorpsHead	CorpHead	= 1;			// ������Ϣͷ
	optional uint32		Msgcode		= 2;			// ���ò���
};

// ***************************************************************************//
// CMessageFamilyLeaveCorpsResponse  
// �����뿪���ŵ���Ϣ��Ӧ
// ***************************************************************************//
message CMessageFamilyLeaveCorpsResponse
{
	optional CorpsHead	CorpHead	= 1;			// ������Ϣͷ
	optional uint32		Errcode		= 2;			// ������0��ʾ�ɹ�������ʾ������	
};

// ***************************************************************************//
// CMessageFamilyLeaveCorpsNotify  
// �����뿪���ŵ���Ϣ֪ͨ
// ***************************************************************************//
message CMessageFamilyLeaveCorpsNotify
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32	FamilyID				= 2;			// ����ID
	optional string FamilyName				= 3;			// ��������
};

// ***************************************************************************//
// CMessageKickFamilyRequest  
// �Ӿ����߳��������Ϣ����
// ***************************************************************************//
message CMessageKickFamilyRequest
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32 FamilyID				= 2;			// ���ߵ��ļ���ID				
};

// ***************************************************************************//
// CMessageKickFamilyResponse  
// �Ӿ����߳��������Ϣ��Ӧ
// ***************************************************************************//
message CMessageKickFamilyResponse
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32 Errcode					= 2;			// ������0��ʾ�ɹ�������ʾ������
	optional string FamilyName				= 3;			// ���߳��ļ�������
	optional uint32 FamilyID				= 4;			// ���߳��ļ���ID
};

// ***************************************************************************//
// CMessageKickFamilyNotify  
// ����Ӿ������汻�ߵ���֪ͨ
// ***************************************************************************//
message CMessageKickFamilyNotify
{												
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32 FamilyID				= 2;			// ���ߵ��ļ���ID
	optional string	FamilyName				= 3;			// ���ߵ��ļ�������
};

// ***************************************************************************//
// ��ȡ���ż����Ա��Ϣ������  
// CMessageGetCorpsFamilyInfoRequest
// ***************************************************************************//
message CMessageGetCorpsFamilyInfoRequest
{
	optional CorpsHead		CorpHead  = 1;			// ������Ϣͷ
	optional uint32			MsgCode	  = 2;			// ���ò���
};

// ***************************************************************************//
// CMessageGetCorpsFamilyInfoResponse  
// ��ȡ���ż����Ա��Ϣ�Ļ�Ӧ��Ϣ
// ***************************************************************************//
message CMessageGetCorpsFamilyInfoResponse
{
	optional CorpsHead			CorpHead			= 1;			// ������Ϣͷ
	repeated PBCorpsMember		CorpsMemberInfo		= 2;			// ������Ϣ
}; 

// ***************************************************************************//
// CMessageGetCorpsPropertyRequest  
// ��ȡ����������Ϣ��������Ϣ
// ***************************************************************************//
message CMessageGetCorpsPropertyRequest
{
	optional CorpsHead		CorpHead  = 1;			// ������Ϣͷ
	optional uint32			MsgCode	  = 2;			// ���ò���	
};

// ***************************************************************************//
// CMessageGetCorpsPropertyResponse  
// ��ȡ����������Ϣ�Ļ�Ӧ��Ϣ
// ***************************************************************************//
message CMessageGetCorpsPropertyResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional CorpsProperty CorpProperty		= 2;			// ��������		
};

// ***************************************************************************//
// CMessageGetCorpsFamilyMemberRequest  
// ��ȡ������ĳ������ĳ�Ա��Ϣ����Ϣ����
// ***************************************************************************//
message CMessageGetCorpsFamilyMemberRequest
{
	optional CorpsHead		CorpHead  = 1;			// ������Ϣͷ
	optional uint32			FamilyID  = 2;			// ����ID
};

// ***************************************************************************//
// CMessageGetCorpsFamilyMemberResponse  
// ��ȡ������ĳ������ĳ�Ա��Ϣ����Ϣ��Ӧ
// ***************************************************************************//
message CMessageGetCorpsFamilyMemberResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			FamilyID		= 2;			// ����ID
	optional string			FamilyName		= 3;			// ��������
	optional PBFamilyMemberList MemberList	= 4;			// �����Ա�б�
};

// ***************************************************************************//
// CMessageChangeCorpsBulletinRequest  
// �ı���Ź������Ϣ����
// ***************************************************************************//
message CMessageChangeCorpsBulletinRequest
{
	optional CorpsHead		CorpHead  = 1;			// ������Ϣͷ
	optional string			Bulletin  = 2;			// ��������				
};	

// ***************************************************************************//
// CMessageChangeCorpsBulletinResponse  
// �ı���Ź������Ϣ�ظ�
// ***************************************************************************//
message CMessageChangeCorpsBulletinResponse
{
	optional CorpsHead		CorpHead	= 1;			// ������Ϣͷ
	optional uint32			Errcode		= 2;			// ������0��ʾ�ɹ�������ʾ������
	optional string			Bulletin	= 3;			// ��������		
};

// ***************************************************************************//
// CMessageChangeCorpsBulletinNotify  
// �ı���Ź������Ϣ֪ͨ
// ***************************************************************************//
message CMessageChangeCorpsBulletinNotify
{
	optional CorpsHead		CorpHead  = 1;			// ������Ϣͷ
	optional string			Bulletin  = 2;			// ��������			
};

// ***************************************************************************//
// CMessageChangeCorpsHeaderRequest  
// �ı�����������Ϣ����
// ***************************************************************************//
message CMessageChangeCorpsHeaderRequest
{
	optional CorpsHead		CorpHead  = 1;			// ������Ϣͷ
	optional uint32			MemberID  = 2;			// Ҫת�þ�������ְλ�ĳ�ԱID
};

// ***************************************************************************//
// CMessageChangeCorpsHeaderResponse  
// �ı�����������Ϣ�ظ�
// ***************************************************************************//
message CMessageChangeCorpsHeaderResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			Errcode			= 2;			// 0��ʾ�ɹ�������ʾ������
	optional uint32			MemberID		= 3;			// ��ɫID
	optional string			MemberName		= 4;			// ��ɫ����
}; 

// ***************************************************************************//
// CMessageChangeCorpsHeaderNotify  
// �ı�����������Ϣ֪ͨ
// ***************************************************************************//
message CMessageChangeCorpsHeaderNotify
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			HeaderRoleID	= 2;			// �����ɫID
	optional string			HeaderRoleName	= 3;			// ��������
	optional uint32			MemberRoleID	= 4;			// ��ת��ְλ�Ľ�ɫID
	optional string			MemberRoleName	= 5;			// ��ת��ְλ�Ľ�ɫ����
};

// ***************************************************************************//
// CMessageGetCorpsApplyListRequest  
// ��ȡ���������б����Ϣ����
// ***************************************************************************//
message CMessageGetCorpsApplyListRequest
{												
	optional CorpsHead		CorpHead  = 1;			// ������Ϣͷ
	optional uint32			MsgCode	  = 2;			// ���ò���	
};

// ***************************************************************************//
// CMessageGetCorpsApplyListResponse  
// ��ȡ���������б����Ϣ��Ӧ
// ***************************************************************************//
message CMessageGetCorpsApplyListResponse
{
	optional CorpsHead			CorpHead	 = 1;			// ������Ϣͷ
	optional uint32				MsgCode		 = 2;			// ���ò���
	optional PBCorpsApplyList	CorpsApply	 = 3;			// ����������б���Ϣ
};

// ***************************************************************************//
// CMessageDiBandCorps  
// ��ɢ���ŵ���Ϣ����
// ***************************************************************************//
message CMessageDisbandCorpsRequest
{
	optional CorpsHead		CorpHead	= 1;			// ������Ϣͷ
	optional uint32			NpcEntityID = 2;			// ����NPC��ʵ��ID
};

// ***************************************************************************//
// CMessageDiBandCorpsResponse  
// ��ɢ���ŵ���Ϣ��Ӧ
// ***************************************************************************//
message CMessageDisbandCorpsResponse
{
	optional CorpsHead		CorpHead  = 1;			// ������Ϣͷ
	optional uint32			Errcode	  = 2;			// ���ò���
};


// ***************************************************************************//
// CMessageDiBandCorpsNotify  
// ��ɢ���ŵ���Ϣ֪ͨ
// ***************************************************************************//
message CMessageDisbandCorpsNotify
{	
	optional CorpsHead		CorpHead  = 1;			// ������Ϣͷ
	optional uint32			MsgCode	  = 2;			// ���ò���
};


// ***************************************************************************//
// CMessageCancelCorpsDisbandRequest  
// ȡ����ɢ�������Ϣ����
// ***************************************************************************//
message CMessageCancelCorpsDisbandRequest
{
	 optional CorpsHead		CorpHead  = 1;			// ������Ϣͷ
	 optional uint32		MsgCode	  = 2;			// ���ò���
};

// ***************************************************************************//
// CMessageCancelCorpsDisbandResponse  
// ȡ����ɢ�������Ϣ��Ӧ
// ***************************************************************************//
message CMessageCancelCorpsDisbandResponse
{
	optional CorpsHead	CorpHead  = 1;			// ������Ϣͷ
	optional uint32		ErrCode	  = 2;			// 0��ʾ�ɹ�������ʾ������
};

// ***************************************************************************//
// CMessageClearCorpsApplyRequest  
// ������������б����Ϣ����
// ***************************************************************************//
message CMessageClearCorpsApplyRequest
{
	optional CorpsHead	CorpHead  = 1;			// ������Ϣͷ
	optional uint32		MsgCode	  = 2;			// ���ò���
};

// ***************************************************************************//
// CMessageClearCorpsApplyResponse
// ������������б����Ϣ��Ӧ
// ***************************************************************************//
message CMessageClearCorpsApplyResponse
{
	optional CorpsHead	CorpHead  = 1;			// ������Ϣͷ
	optional uint32		ErrCode	  = 2;			// 0��ʾ�����ɹ�������ʾ������
};

// ***************************************************************************//
// CMessageRefreshCorpsInfoRequest
// ˢ�¾��ŵļ�����Ϣ������
// ***************************************************************************//
message CMessageRefreshCorpsInfoRequest
{
	optional CorpsHead		CorpHead	= 1;			// ������Ϣͷ
	optional uint32			MsgCode		= 2;			// ���ò���
};

// ***************************************************************************//
// CMessageRefreshCorpsInfoResponse
// ˢ�¾��ŵļ�����Ϣ����Ϣ��Ӧ
// ***************************************************************************//
message CMessageRefreshCorpsInfoResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	repeated PBCorpsMember	CorpsMember		= 2;			// ������Ϣ
};

// ***************************************************************************//
// CMessageGetCorpsListRequest
// ��ȡ�����б����Ϣ����
// ***************************************************************************//
message CMessageGetCorpsListRequest
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			CurPage			= 2;			// ��ȡ���б�ҳ��
	
};

// ***************************************************************************//
// CMessageGetCorpsListResponse
// ��ȡ�����б����Ϣ��Ӧ
// ***************************************************************************//
message CMessageGetCorpsListResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional CorpsInfoList	CorpsList		= 2;			// ������Ϣ�б�
	optional uint32			CurPage			= 3;			// ��ȡ���б�ҳ��
	optional uint32			TotalPage		= 4;			// ��ҳ��
};


// ***************************************************************************//
// CMessageSetCorpsPostRequest
// ���þ��ų�Աְλ����Ϣ����
// ***************************************************************************//
message CMessageSetCorpsPostRequest
{
	optional CorpsHead	CorpHead		=	1;			// ������Ϣͷ
	optional uint32		MemberID		=	2;			// ��ԱID
	optional uint32		Post			=	3;			// �ƺ�	
};

// ***************************************************************************//
// CMessageSetCorpsPostRequest
// ���þ��ų�Աְλ����Ϣ����
// ***************************************************************************//
message CMessageSetCorpsPostResponse
{
	optional CorpsHead	CorpHead		=	1;			// ������Ϣͷ
	optional uint32		MemberID		=	2;			// ��ԱID
	optional uint32		Post			=	3;			// ְλ
	optional uint32		Errcode			=	4;			// ������
};

// ***************************************************************************//
// CMessageSetLevelUPCorpsRequest
// �������ŵ���Ϣ����
// ***************************************************************************//
message CMessageLevelUPCorpsRequest
{
	optional CorpsHead	CorpHead	=	1;		// ������Ϣͷ
	optional uint32		MsgCode		=	2;		// ���ò���	
};

// ***************************************************************************//
// CMessageLevelUPCorpsResponse
// �������ŵ���Ϣ��Ӧ
// ***************************************************************************//
message CMessageLevelUPCorpsResponse
{
	optional CorpsHead	CorpHead	=	1;		// ������Ϣͷ
	optional uint32		Errcode		=	2;		// ������
	optional uint32		Level		=	3;		// ������ĵȼ�
};

// ***************************************************************************//
// CMessageContributeCorpsMoneyRequest
// ���˹��׾��Ž�Ǯ����Ϣ����
// ***************************************************************************//
message CMessageContributeCorpsMoneyRequest
{													
	optional CorpsHead	CorpHead	=	1;		// ������Ϣͷ
	optional uint32		Money		=	2;		// ���˾��׵Ľ�Ǯ		
};


// ***************************************************************************//
// CMessageContributeCorpsMoneyResponse
// ���˹��׾��Ž�Ǯ����Ϣ��Ӧ
// ***************************************************************************//
message CMessageContributeCorpsMoneyResponse
{
	optional CorpsHead	CorpHead	=	1;		// ������Ϣͷ
	optional uint32		Errcode		=	2;		// ������
	optional uint32		Money		=	3;		// ���˾��׵Ľ�Ǯ
};

// ***************************************************************************//
// CMessageFamilyContributeMoneyRequest
// ��������Ź��׽�Ǯ����Ϣ����
// ***************************************************************************//
message CMessageFamilyContributeMoneyRequest
{
	optional CorpsHead	CorpHead	=	1;		// ������Ϣͷ
	optional uint32		Money		=	2;		// �����
};

// ***************************************************************************//
// CMessageFamilyContributeMoneyResponse
// ��������Ź��׽�Ǯ����Ϣ��Ӧ
// ***************************************************************************//
message CMessageFamilyContributeMoneyResponse
{
	optional CorpsHead	CorpHead	=	1;		// ������Ϣͷ
	optional uint32		Errcode		=	2;		// ������
	optional uint32		Money		=	3;		// ���׵ļ����Ǯ	
};

// ***************************************************************************//
// CMessageSetMemberNameRequest
// ���þ��ų�Ա�ƺŵ���Ϣ����
// ***************************************************************************//
message CMessageSetMemberNameRequest
{
	optional CorpsHead	CorpHead	=	1;		// ������Ϣͷ
	optional uint32		MemberID	=	2;		// ��ԱID
	optional string		Name		=	3;		// ����
};

// ***************************************************************************//
// CMessageSetMemberNameResponse
// ���þ��ų�Ա�ƺŵ���Ϣ��Ӧ
// ***************************************************************************//
message CMessageSetMemberNameResponse
{  
	optional CorpsHead	CorpHead	=	1;		// ������Ϣͷ
	optional uint32		Errcode		=	2;		// ������
	optional uint32		MemberID	=	3;		// ��ԱID
	optional string		Name		=	4;		// �ƺ�
};

// ***************************************************************************//
// CMessageSetCorpsPostNotify
// ���þ���ְλ��֪ͨ
// ***************************************************************************//
message CMessageSetCorpsPostNotify
{
	optional CorpsHead	CorpHead		=	1;		// ������Ϣͷ
	optional uint32		ManagerID		=	2;		// �����˵�ְλ
	optional string		ManagerName		=	3;		// �����˵�����
	optional uint32		MemberID		=	4;		// ��ԱID
	optional string		MemberName		=	5;		// ��Ա����
	optional uint32		OriginalPost	=	6;		// ԭ����ְλ
	optional uint32		NewPost			=	7;		// ��ְλ
};

// ***************************************************************************//
// CMessageCorpsLevelUPNotify
// ������������Ϣ֪ͨ
// ***************************************************************************//
message CMessageCorpsLevelUPNotify
{		
	optional CorpsHead	CorpHead			=	1;		// ������Ϣͷ
	optional uint32		Level				=	2;		// ��ǰ�ȼ�
	optional uint32		Money				=	3;		// ���ŵ�ǰ��Ǯ
	optional uint32		Glory				=	4;		// ���ŵ�ǰ��ҫ
	optional uint32		MaxFamilyNum		=	5;		// ������ľ�����������
	optional uint32		MaxGeneralNum		=	6;		// ǰ�潫����������
	optional uint32		MaxCounsellorNum	=	7;		// ���ľ�ʦ���� 		
	optional uint32		LevelMoney			=	8;		// ������Ҫ�Ľ�Ǯ
	optional uint32		LevelGlory			=	9;		// ������Ҫ����ҫ
};

// ***************************************************************************//
// CMessageCorpsBattleBidRequest
// ս�����۱�������
// ***************************************************************************//

message CMessageCorpsBattleBidRequest
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			NpcID			= 2;			// ����NPC
	optional uint32			Money			= 3;			// ���۽�Ǯ
	optional uint32			MinIncMoney		= 4;			// �Ӽ����ֵ(����Ҫ�ͻ��˷�)
	optional uint32			MapID			= 5;
};

// ***************************************************************************//
// CMessageCorpsBattleBidResponse
// ս�����۱����ظ�
// ***************************************************************************//

message CMessageCorpsBattleBidResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			RtnCode			= 2;			// ���۱����Ƿ�ɹ�
	optional uint32			NpcID			= 3;
	optional uint32			Money			= 4;
};

// ***************************************************************************//
// CMessageCorpsQueryBidRankRequest
// ��ȡ�������а���Ϣ����
// ***************************************************************************//

message CMessageCorpsQueryBidRankRequest
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			NpcID			= 2;			// ����Npc	
	optional uint32			BattleCity		= 3;			// �ǳ�ID(�ͻ��˲���Ҫ���)
};

message PBBidRank
{
	optional string		CorpsName		= 1;	// ��������
	optional uint32		Money			= 2;	// ����۸�
	optional uint32		Nationality		= 3;	// ����ID
	optional uint32		Victory			= 4;	// սʤ����
	optional uint32		Loser			= 5;	// ս�ܴ���
	optional uint32		StarLevel		= 6;	// �Ǽ�
	optional uint32		CorpsID			= 7;	// ����ID
}; 

// ***************************************************************************//
// CMessageCorpsQueryBidRankResponse
// ��ȡ�������а���Ϣ�ظ�
// ***************************************************************************//

message CMessageCorpsQueryBidRankResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			NpcID			= 2;			// ����Npc
	optional string			CityOwner		= 3;			// �ǳص�ǰӵ����
	repeated PBBidRank		RankInfo		= 4;			// �������а��б�
};

// ***************************************************************************//
// CMessageCorpsSelectFamilyBattleRequest
// ������ż����ս�ʸ�����
// ***************************************************************************//

message CMessageCorpsSelectFamilyBattleRequest
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	repeated uint32			FamilyID		= 2;			// ����ID(ѡ���ս�ļ���)
};

// ***************************************************************************//
// CMessageCorpsSelectFamilyBattleResponse
// ������ż����ս�ʸ�����Ļظ�
// ***************************************************************************//		
message CMessageCorpsSelectFamilyBattleResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			RtnCode			= 2;			// 
};
	
// ***************************************************************************//
// CMessagePvPStarLevelUpNotify
// ����pvp�Ǽ���ߵ�֪ͨ
// ***************************************************************************//		
message CMessageCorpsPvPStarLevelUpNotify
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			PvPLevel		= 2;			// ����pvp�Ǽ�
};
 
//***************************************************
// ��ò�ս�ʸ�֪ͨ
//***************************************************

message CMessageCorpsBattleRightsNotify
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			NpcID			= 2;
	optional string			DesCorpsName	= 3;
	optional uint32			Type			= 4;			// ս������
};

// ֪ͨ�����峤��ò�ս�ʸ�
message CMessageCorpsRecBattleRightsNotify
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			NpcID		= 2;		
	optional uint32			SrcCorpsID	= 3;
	optional string			SrcCorpsName = 4;
	optional uint32			DesCorpsID	= 5;
	optional string			DesCorpsName = 6;
	optional uint32			Money = 7;
};

message CMessageCorpsSelectMemberBattleRequest
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	repeated uint32		MemberList		= 2;		// ��ս����б�(char id)
	optional uint32		BattleCity		= 3;
	optional uint32		Type			= 4;		// ��֯����:���š�����
};

message CMessageCorpsSelectMemberBattleResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32		RtnCode			= 2;
};

// ֪ͨ���˿��Բ�ս

message CMessageCorpsMemberBattleRightsNotify
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32		NpcID		= 2;	// npcid
	repeated uint32		MemberList		= 3;
	optional string		DesCorpsName	= 4;
	optional uint32		Type			= 5;		// ��֯����:���š�����
};

// ***************************************************************************//
// CMessageConsumeCorpsMoneyNotify	
// ���ľ��Ž�Ǯ��֪ͨ
// ***************************************************************************//
message CMessageCorpsMoneyChangedNotify
{
	optional uint32		Money	= 1;			// �������ڵĽ�Ǯ
	optional uint32		RoleID	= 2;			// �ı���Ž�Ǯ�Ľ�ɫID	
	optional uint32		Reason	= 3;			// ���Ž�Ǯ�ı��ԭ��
	optional string		RoleName= 4;			// �ı���Ž�Ǯ�Ľ�ɫ����  
	optional int32		Valeu	= 5;			// ��ֵ
};

// ***************************************************************************//
// CMessageCorpsGloryChangedNotify	
// ������ҫ�ı��֪ͨ
// ***************************************************************************//
message CMessageCorpsGloryChangedNotify
{
	optional uint32		Glory	= 1;			// �������ڵ���ҫ
	optional uint32		RoleID	= 2;			// �ı������ҫ�Ľ�ɫID	
	optional uint32		Reason	= 3;			// ������ҫ�ı��ԭ��
	optional string		RoleName= 4;			// �ı���Ž�Ǯ�Ľ�ɫ����
	optional int32		Value	= 5;			// ��ֵ
};

// ***************************************************************************//
// CMessageCorpsContributeChangedNotify	
// ���ŵĸ����׶ȸı��֪ͨ
// ***************************************************************************//
message CMessageCorpsContributeChangedNotify
{
	optional CorpsHead	CorpHead	= 1;			// ������Ϣͷ
	optional uint32		Contribute	= 2;			// ��ҵĸ��˹��׶�
	optional uint32		RoleID		= 3;			// ��ҵĽ�ɫID
	optional int32		Value		= 4;			// ��ֵ
};

// ***************************************************************************//
//
// ***************************************************************************//
message CMessageCorpsBossTimesChangedNotify
{
	optional uint32 BossID		= 1;			//boss id
	optional uint32 RoleID		= 2;			//�ı�����Ľ�ɫID
	optional uint32 Reason		= 3;			//�ı�ԭ��
	optional string RoleName	= 4;			//�ı��ɫ������
	optional uint32 Times		= 5;			//���ڿ�����ս�Ĵ���
	optional uint32 Value		= 6;			//��ֵ
};

message CMessageCorpsBossRefineValueNotify
{
	optional uint32 RefineValue		= 1;		// �������ڵ�����ֵ
	optional uint32 RoleID			= 2;		// �ı�����ֵ�� ��ɫID
	optional uint32	Value			= 3;		// �ı�ֵ
	optional uint32 Reason			= 4;		// �ı��ԭ��
	optional string RoleName		= 5;		// ��ɫ������
};

message	CMessageCorpsCollectActiveChangeNotify
{
	optional CorpsHead	CorpHead		= 1;		// ������Ϣͷ
	optional uint32		ActiveValue		= 2;		// �������ڵĲɼ���Ծ��ֵ
	optional uint32		Vaule			= 3;		// �ı�ֵ
	optional uint32		ChangeType		= 4;		// ���ӻ����
}

// ����ʥ��̨��Ϣ����
message CMessageMendShengHuoTaiRequest
{
	optional uint32	NpcEntityID = 1;	// ʥ��̨ entityid
};

// ֪ͨ���¾�������
message CMessageCorpsPropertyNotice
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional CorpsProperty  Property		= 2;
};

// ��������
message CMessageCorpsOperateRoomRequest
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			Action			= 2;		// 1:������;0:�ط���
	optional uint32			Money			= 3;
	optional string			Name			= 4;
};

// ����ظ�
message CMessageCorpsOperateRoomResponse
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			Action			= 2;		// 1:������;0:�ط���
	optional uint32			RtnCode			= 3;
	optional uint32			Money			= 4;
	optional string			Name			= 5;
};

// ����仯֪ͨ�������г�Ա
message CMessageCorpsRoomNotice
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			Action			= 2;
	optional string			RooterName		= 3;
};

// ������ս����
message CMessageCorpsChallegeRequest
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			Action			= 2;		// ����ȡ��
	optional uint32			DesCropsID		= 3;		// �Է�����ID
};

// ������ս�ظ�
message CMessageCorpsChallegeResponse
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			RtnCode			= 2;
	optional uint32			Action			= 3;
	optional uint32			DesCropsID		= 4;		// �Է�����ID
};

// ��ս֪ͨ
message CMessageCorpsChallegeNotice
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			SrcCorpsID		= 2;
	optional string			SrcCorpsName	= 3;
	optional uint32			DesCropsID		= 4;		// �Է�����ID
	optional string			DesCorpsName	= 5;		// �Է���������
	optional uint32			WinTimes		= 6;
	optional uint32			LostTimes		= 7;
	optional string			SrcRooterName	= 8;
	optional string			DesRooterName	= 9;
	optional uint32			Action			= 10;
};

// �ظ���ս����
message CMessageCorpsReplyChallegeRequest
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			DesCorpsID		= 2;
};

// ������ս����Ļظ�
message CMessageCorpsReplyChallegeResponse
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional string			DesCorpsName	= 2;
	optional uint32			RtnCode			= 3;
};

// ��ѯ�Լ���ս���˵��б�����
message CMessageCorpsQueryChallegeListRequest
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
};

// ��ѯ�Լ���ս���˵��б�ظ�
message CMessageCorpsQueryChallegeListResponse
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	repeated uint32			CorpsIDList 	= 2;		// ��ս�ľ����б�
	optional uint32			RtnCode			= 3;
};

message PBChallege
{
	optional uint32	CorpsID = 1;
	optional string CorpsName = 2;
	optional uint32	WinTimes = 3;
	optional uint32	LostTimes = 4;
};

// ��ѯ�Լ������յ�����ս�б�����
message CMessageCorpsQueryRecChallegeListRequest
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
};

// ��ѯ�Լ������յ�����ս�б�ظ�
message CMessageCorpsQueryRecChallegeListResponse
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional string			RoomName		= 2;
	optional uint32			Money			= 3;
	optional uint32			WinTimes		= 4;
	optional uint32			LostTimes		= 5;
	repeated PBChallege		ChallegeList	= 6;
	optional uint32			RtnCode			= 7;
};

// ��ѯ��ս�����б�
message CMessageCorpsQueryRoomListRequest
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
};

message PBCorpsRoom
{
	optional uint32		CorpsID = 1; // ����ľ���ID
	optional string		CorpsName = 2;
	optional string		RoomName = 3;
	optional uint32		RoomState = 4;	// ����״̬
	optional string		DesCorpsName = 5;	// ս��״̬�µ���ս����������ս����Ϊ��
	optional uint32		WinTimes	= 6;
	optional uint32		LostTimes	= 7;
	optional uint32		Money = 8;
};

// ��ѯ��ս����ظ�
message CMessageCorpsQueryRoomListResponse
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	repeated PBCorpsRoom	RoomList		= 2;
	optional uint32			RtnCode			= 3;
};

// ***************************************************************************//
// CMessageQueryCorpsWelfareRequest	
// ��ѯ����npc��������Ϣ����
// ***************************************************************************//
message CMessageQueryCorpsWelfareRequest
{
	 optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	 optional uint32		EntityID		= 2;		// NPCʵ��ID
	 optional uint32		NpcID			= 3;		// npc��ģ��ID,��������
};

// ***************************************************************************//
// ��ѯ����npc��������Ϣ��Ӧ	
// CMessageQueryCorpsWelfareResponse
// ***************************************************************************//
message CMessageQueryCorpsWelfareResponse
{	
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			Errcode			= 2;		// ������	
	optional uint32			NpcGlory		= 3;		// ������ȡ����ҫ
	optional uint32			NpcMoney		= 4;		// ������ȡ�ļ����Ǯ
};

// ***************************************************************************//
// ��ȡ���Ÿ�������Ϣ����
// CMessageObtainCorpsWelfareRequest
// ***************************************************************************//
message CMessageObtainCorpsWelfareRequest
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			EntityID		= 2;		// NPCʵ��ID
	optional uint32			NpcID			= 3;		// npc��ģ��ID		
};

// ***************************************************************************//
// ��ȡ���Ÿ�������Ϣ��Ӧ
// CMessageObtainCorpsWelfareRequest
// ***************************************************************************//
message CMessageObtainCorpsWelfareResponse
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ	
	optional uint32			Errcode			= 2;		// ������	
	optional uint32			NpcGlory		= 3;		// ������ȡ����ҫ
	optional uint32			NpcMoney		= 4;		// ������ȡ�Ľ�Ǯ
}; 

// ***************************************************************************//
// �Ѿ��Ž�Ǯ��ȡΪ���˽�Ǯ������
// CMessageGetCorpsMoneyRequest
// ***************************************************************************//
message  CMessageGetCorpsMoneyRequest
{	 
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ	
	optional uint32			CorpsMoney		= 2;		// ���Ž���	
};

// ***************************************************************************//
// �Ѿ��Ž�Ǯ��ȡΪ���˽�Ǯ����Ϣ��Ӧ
// CMessageGetCorpsMoneyResponse
// ***************************************************************************//
message CMessageGetCorpsMoneyResponse
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			Errcode			= 2;		// ������		
	optional uint32			CorpsMoney		= 3;		// ��ȡ�ľ��Ž���	
};

// ����ռ��óǳ�����
message CMessageCorpsAbortBattleCityRequest
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			NpcEntityID		= 2;		// �Ի�npc
};

message CMessageCorpsAbortBattleCityResponse
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			RtnCode			= 2;		// �ɹ���0
	optional uint32			NpcID			= 3;
	optional string			RooterName		= 4;
};

message CMessageCorpsAbortBattleCityNotice
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			NpcID			= 2;
	optional string			RooterName		= 3;
};

// ***************************************************************************//
// ���ſ�����������Ϣ֪ͨ
// CMessageCorpsCanLevelUPNotify
// ***************************************************************************//
message CMessageCorpsCanLevelUPNotify
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ	
};

// ���ŷ�������֪ͨ
message CMessageCorpsPublishTaskNotify
{
	optional CorpsHead		NotifyHead		= 1;		// ������Ϣͷ	
};

// ս�����֪ͨ
message CMessageCorpsBattleResultNotice
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional string			WinCorpsName	= 2;
	optional string			LostCorpsName	= 3;
	optional uint32			WinCampID		= 4;		// 1:����Ӯ��2:�ط�Ӯ
	optional uint32			NpcID			= 5;
	optional uint32			BattleType		= 6;
	optional uint32			WinCorpsID		= 7;
	optional uint32			LostCorpsID		= 8;
};


// npc ��������֪ͨ
message CMessageCorpsNpcOwnerNotice
{
	optional uint32			Type			= 1;
	optional uint32			NpcID			= 2;
	optional string			CorpsName		= 3;
	optional uint32			CorpsID			= 4;
	optional string			FamilyName		= 5;
	optional uint32			FamilyID		= 6;
};

// ***************************************************************************//
// ���ųƺŸı��֪ͨ
// CMessageCorpsNameChangedNotify
// ***************************************************************************//
message CMessageCorpsNameChangedNotify
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			ManagerID		= 2;		// ����������
	optional string			ManagerName		= 3;		// ����������
	optional uint32			MemberID		= 4;		// �ƺű��޸ĵĽ�ɫID	
	optional string			CorpsName		= 5;		// ���޸ĺ�ĳƺ�
};

// ***************************************************************************//
// ������������
// CMessageCreateUnionRequest
// ***************************************************************************//
message CMessageCreateUnionRequest
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	repeated uint32			OtherID			= 2;		// ��������ID
	optional string			UnionName		= 3;		// ��������
	optional string			UnionNotice		= 4;		// ��������
	optional uint32			NPCEntityID		= 5;		// NPC ENTITYID
};

// ***************************************************************************//
// ����������Ӧ
// CMessageCreateUnionResponse
// ***************************************************************************//
message CMessageCreateUnionResponse
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ	
	optional uint32			Result			= 2;		// ������
	repeated uint32			OtherID			= 3;		// ��������ID
	optional uint32			UnionID			= 4;		// ����ID
}; 

// ***************************************************************************//
// ��������֪ͨ
// CMessageCreateUnionNotify
// ***************************************************************************//
message CMessageCreateUnionNotify
{
	optional CorpsHead		CorpHead		= 1;		// ������Ϣͷ
	optional uint32			HeadID			= 2;		// �������ID
	optional string			HeadName		= 3;		// �����������
	repeated uint32			OtherID			= 4;		// ��������ID
	repeated string			OtherName		= 5;		// ������������
	optional uint32			UnionID			= 6;		// ����ID
	optional string			UnionName		= 7;		// ��������
}; 


// *************************************************************************** //
// CMessageApplyUnionRequest  
// ���������������Ϣ����
// *************************************************************************** //
message CMessageApplyUnionRequest
{		
	optional CorpsHead	CorpHead		= 1;			// ������Ϣͷ
	optional string		UnionName		= 2;			//	��������
	optional uint32		UnionID			= 3;			//	����ID
	optional uint32		RoleID			= 4;			//	��ҽ�ɫID
};


// *************************************************************************** //
// CMessageApplyUnionResponse  
// ���������������Ϣ��Ӧ
// *************************************************************************** //
message CMessageApplyUnionResponse
{			
	optional CorpsHead	CorpHead	= 1;			// ������Ϣͷ
	optional uint32		Errcode		= 2;			// ������0��ʾ�ɹ�������ʾ������
	optional string		UnionName	= 3;			// ��������
};

// *************************************************************************** //
// CMessageUnionMemberApplyNotify  
// �о������������������Ϣ֪ͨ
// *************************************************************************** //
message CMessageUnionMemberApplyNotify
{			
	optional CorpsHead	CorpHead	= 1;			// ������Ϣͷ
	optional PBCorpsBasicInfo CorpsInfo	= 2;		// ����������Ϣ
};

// *************************************************************************** //
// CMessageReplyUnionMemberApplyRequest  
// �𸴾����������Ϣ����
// *************************************************************************** //
message CMessageReplyUnionMemberApplyRequest
{																		
	optional CorpsHead	CorpHead	= 1;				// ������Ϣͷ
	optional uint32		Result		= 2;				// ���ھ�������Ļظ�1��ʾͬ��0��ʾ��ͬ��
	optional uint32		CorpsID		= 3;				// �������ľ��ŵ�ID		
};

// *************************************************************************** //
// CMessageReplyUnionMemberApplyResponse  
// �о������������������Ϣ֪ͨ
// *************************************************************************** //
message CMessageReplyUnionMemberApplyResponse
{
	optional CorpsHead	CorpHead	= 1;				// ������Ϣͷ
	optional uint32		Errcode		= 2;				// 0��ʾ�����ɹ�������ʾ������
	optional uint32		Result		= 3;				// ֮ǰ�Ĵ𸴽��
	optional uint32		CorpsID		= 4;				// ����ID		
};

// *************************************************************************** //
// CMessageApplyUnionResultNotify  
// ������������Ľ��֪ͨ
// *************************************************************************** //
message CMessageApplyUnionResultNotify
{
	optional CorpsHead	CorpHead	= 1;				// ������Ϣͷ
	optional uint32 ResultCode		= 2;				// 1��ʾ����ɹ�0��ʾ���ܾ�������ʾ������
	optional uint32 UnionID			= 3;				// ����ID
	optional string	UnionName		= 4;				// ��������
};


// *************************************************************************** //
// CMessageInviteUnionMemberRequest  
// ������ż�����������Ϣ����
// *************************************************************************** //
message CMessageInviteUnionMemberRequest
{
	optional CorpsHead	CorpHead	= 1;				// ������Ϣͷ
	optional string CorpsName		= 2;				// ��������
	optional uint32	MemberID		= 3;				// ��ɫID		
};


// ***************************************************************************//
// CMessageInviteUnionMemberResponse  
// ������ż�����������Ϣ��Ӧ
// ***************************************************************************//
message CMessageInviteUnionMemberResponse
{
	optional CorpsHead	CorpHead	= 1;				// ������Ϣͷ
	optional uint32 Errcode			= 2;				// ������0��ʾ�ɹ�������ʾ������
	optional string CorpsName		= 3;				// ��������
};

// ***************************************************************************//
// CMessageUnionInviteNotify  
// ���������������Ϣ֪ͨ
// ***************************************************************************//
message CMessageUnionInviteNotify
{
	optional CorpsHead	CorpHead		= 1;			// ������Ϣͷ
	optional string InvitingName		= 2;			// ����������
	optional uint32 InvitingID			= 3;			// ������ID	
	optional PBUnionBasicInfo UnionInfo = 4;			// ������Ϣ 
};	

// ***************************************************************************//
// CMessageReplyUnionInviteRequest  
// �������������Ϣ����
// ***************************************************************************//
message CMessageReplyUnionInviteRequest
{
	optional CorpsHead	CorpHead		= 1;			// ������Ϣͷ
	optional uint32	 Result				= 2;			// 1��ʾͬ���������0��ʾ�ܾ���������
	optional uint32	 UnionID			= 3;			// ����ID
	optional uint32	 InvitingID			= 4;			// ������ID
};

// ***************************************************************************//
// CMessageReplyUnionInviteResponse  
// �������������Ϣ�ظ�
// ***************************************************************************//
message CMessageReplyUnionInviteResponse
{
	optional CorpsHead	CorpHead		= 1;			// ������Ϣͷ
	optional uint32	Errcode				= 2;			// ������0��ʾ�ɹ�������ʾ������
	optional uint32 Result				= 3;			// �𸴽��
	optional string	UnionName			= 4;			// ��������
	optional uint32 UnionID				= 5;			// ����ID	
};

// ***************************************************************************//
// CMessageUnionInviteResultNotify  
// ������������ŵĽ��
// ***************************************************************************//
message CMessageUnionInviteResultNotify
{
	optional CorpsHead	CorpHead		= 1;			// ������Ϣͷ
	optional uint32 Result				= 2;			// 1��ʾ����ɹ�0��ʾ���ܾ�������ʾ������
	optional string CorpsName			= 3;			// ������ľ��ŵ�����
};	 


// ***************************************************************************//
// CMessageCorpsJoinUnionNotify  
// �о��ż�����������Ϣ֪ͨ
// ***************************************************************************//
message CMessageCorpsJoinUnionNotify
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional PBCorpsBasicInfo CorpsInfo		= 2;			// ����������Ϣ	
	optional uint32			UnionID			= 3;			// ����ID
	optional string			UnionName		= 4;			// ��������
};

// ***************************************************************************//
// CMessageCorpsLeaveUnionRequest  
// �����뿪��������Ϣ����
// ***************************************************************************//
message CMessageCorpsLeaveUnionRequest
{
	optional CorpsHead	CorpHead	= 1;			// ������Ϣͷ
	optional uint32		Msgcode		= 2;			// ���ò���
};

// ***************************************************************************//
// CMessageCorpsLeaveUnionResponse  
// �����뿪���ŵ���Ϣ��Ӧ
// ***************************************************************************//
message CMessageCorpsLeaveUnionResponse
{
	optional CorpsHead	CorpHead	= 1;			// ������Ϣͷ
	optional uint32		Errcode		= 2;			// ������0��ʾ�ɹ�������ʾ������	
};

// ***************************************************************************//
// CMessageCorpsLeaveUnionNotify  
// �����뿪���ŵ���Ϣ֪ͨ
// ***************************************************************************//
message CMessageCorpsLeaveUnionNotify
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32	CorpsID					= 2;			// ����ID
	optional string CorpsName				= 3;			// ��������
};

// ***************************************************************************//
// CMessageKickCorpsRequest  
// �������߳����ŵ���Ϣ����
// ***************************************************************************//
message CMessageKickCorpsRequest
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32 CorpsID				= 2;				// ���ߵ��ľ���ID				
};

// ***************************************************************************//
// CMessageKickCorpsResponse  
// �������߳����ŵ���Ϣ��Ӧ
// ***************************************************************************//
message CMessageKickCorpsResponse
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32 Errcode					= 2;			// ������0��ʾ�ɹ�������ʾ������
	optional string CorpsName				= 3;			// ���߳��ľ�������
	optional uint32 CorpsID					= 4;			// ���߳��ľ���ID
};

// ***************************************************************************//
// CMessageKickCorpsNotify  
// ���Ŵ��������汻�ߵ���֪ͨ
// ***************************************************************************//
message CMessageKickCorpsNotify
{												
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32 CorpsID					= 2;			// ���ߵ��ľ���ID
	optional string	CorpsName				= 3;			// ���ߵ��ľ�������
};

// ***************************************************************************//
// CMessageMakeUnionRequest  
// ������������Ϣ����
// ***************************************************************************//
message CMessageMakeUnionRequest
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32		OpType				= 2;			// ��������
	optional string		UnionName			= 3;			// ��������	
	optional string		UnionNotice			= 4;			// ��������
	optional uint32		CorpsID				= 5;			// �������ľ���ID
	optional uint32		TargetID			= 6;			// Ŀ��ID
};

// ***************************************************************************//
// CMessageMakeUnionResponse  
// ������������Ϣ��Ӧ
// ***************************************************************************//
message CMessageMakeUnionResponse
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32 Errcode					= 2;			// ������0��ʾ�ɹ�������ʾ������	
	optional uint32	OpType					= 3;			// ��������
};

// ***************************************************************************//
// CMessageMakeUnionNotify  
// ����������֪ͨ
// ***************************************************************************//
message CMessageMakeUnionNotify
{												
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32		OpType				= 2;			// ��������
	optional string		UnionName			= 3;			// ��������	
	optional string		UnionNotice			= 4;			// ��������
	repeated uint32		CorpsID				= 5;			// �������ľ���ID
	repeated string		CorpsName			= 6;			// �������ľ�������
	optional string		HeadCorpsName		= 7;			// ����������
	optional uint32		HeadCharID			= 8;			// �����ŷ�����
};

// ***************************************************************************//
// CMessageGetUnionInfoRequest  
// ���������Ϣ����Ϣ����
// ***************************************************************************//
message CMessageGetUnionInfoRequest
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32		UnionID				= 2;			// ����ID
};

// ***************************************************************************//
// CMessageGetUnionInfoResponse  
// ���������Ϣ����Ϣ��Ӧ
// ***************************************************************************//
message CMessageGetUnionInfoResponse
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32 Errcode					= 2;			// ������0��ʾ�ɹ�������ʾ������
	optional PBUnionBasicInfo UnionInfo		= 3;
	repeated PBCorpsBasicInfo CorpsInfo		= 4;			// ������Ϣ
	optional PBCorpsBattleList	BattleInfo		= 5;			// ����ս����Ϣ
};

// ***************************************************************************//
// CMessageDismissUnionRequest  
// ��ɢ��������Ϣ����
// ***************************************************************************//
message CMessageDismissUnionRequest
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32		NPCEntityID			= 2;			// NPC EntityID
};

// ***************************************************************************//
// CMessageDismissUnionResponse  
// ��ɢ��������Ϣ��Ӧ
// ***************************************************************************//
message CMessageDismissUnionResponse
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32 Errcode					= 2;			// ������0��ʾ�ɹ�������ʾ������
};

// ***************************************************************************//
// CMessageDismissUnionNotify 
// ��ɢ��������Ϣ֪ͨ
// ***************************************************************************//
message CMessageDismissUnionNotify
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
};

// ***************************************************************************//
// CMessageUnionApplyListRequest  
// ������������б����Ϣ����
// ***************************************************************************//
message CMessageUnionApplyListRequest
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
};

// ***************************************************************************//
// CMessageUnionApplyListResponse  
// ������������б����Ϣ��Ӧ
// ***************************************************************************//
message CMessageUnionApplyListResponse
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32 Errcode					= 2;			// ������0��ʾ�ɹ�������ʾ������
	repeated PBCorpsBasicInfo CorpsInfo		= 3;			// ������Ϣ
};

// ***************************************************************************//
// CMessageAllUnionListRequest  
// ��������б����Ϣ����
// ***************************************************************************//
message CMessageAllUnionListRequest
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
};

// ***************************************************************************//
// CMessageAllUnionListResponse  
// ��������б����Ϣ��Ӧ
// ***************************************************************************//
message CMessageAllUnionListResponse
{
	optional CorpsHead	CorpHead			= 1;			// ������Ϣͷ
	optional uint32 Errcode					= 2;			// ������0��ʾ�ɹ�������ʾ������
	repeated PBUnionBasicInfo UnionInfo		= 3;			// ������Ϣ
};

// ��������Ŀɲ�ս�б����� [12/1/2009 Macro]
message CMessageCorpsGetOtherMemberRequest
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
};

message PBBattleMember
{
	optional uint32	CharID  = 1;
	optional string Name	= 2;
	optional uint32	Level	= 3;
	optional uint32	Metier	= 4;	// ְҵ
	optional string CorpsName = 5;	// 
	optional uint32	IsJoinUnion = 6;
};

message CMessageCorpsGetOtherMemberResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	repeated PBBattleMember MemberList		= 2;
};

// ��ѯ���˲�ս��Ա�б�
message CMessageUnionJoinBattleListRequest
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
};

message CMessageUnionJoinBattleListResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			RtnCode			= 2;
	repeated PBBattleMember	MemberList		= 3;
};

// ��ȡ�ѱ�ռ��ĵ�ͼ�б�
message CMessageCorpsGetAllMapRequest
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			ServerID		= 2;			// ��ӪID
};

message PBMapOwner
{
	optional uint32	 MapID		= 1;
	optional uint32  CorpsID	= 2;
	optional string  CorpsName	= 3;	// 
	optional uint32	 Color		= 4;	// ������ɫ 
	optional string  RooterName = 5;	// ���ų�����
	optional uint32	 CorpsPower = 6;	// ��������ֵ
	optional string	 UnionName	= 7;	// ������
	optional uint32	 UnionPower	= 8;	// ��������ֵ
	optional uint32	 PeopleNum	= 9;	// �����˿�
};

message CMessageCorpsGetAllMapResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	repeated PBMapOwner		MapList			= 2;
	optional uint32			ServerID		= 3;			// ��ӪID
};

// ����������
message CMessageCorpsAppointPrinceRequest
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			CorpsID			= 2;			// �����ľ���ID
	optional uint32			MapID			= 3;			// ������ͼID
};

message CMessageCorspAppointPrinceResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			RtnCode			= 2;			// �ɹ�:0,ʧ�ܣ���Ϣ��ʾ
	optional uint32			CorpsID			= 3;			// �����ľ���ID
	optional uint32			MapID			= 4;			// ������ͼID
};

// ֪ͨ�¹��� [12/22/2009 Macro]
message CMessageCorpsAppointPrinceNotice
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			CorpsID			= 2;			// �����ľ���ID
	optional uint32			MapID			= 3;			// ������ͼID
};

// Ǩ������ [12/22/2009 Macro]
message CMessageCorpsMoveCapitalRequest
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			MapID			= 2;			// �¶��ǵ�ͼID
};

message CMesssageCorpsMoveCapitalResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			RtnCode			= 2;			// �ɹ�:0,ʧ�ܣ���Ϣ��ʾ
	optional uint32			MapID			= 3;			// �¶��ǵ�ͼID
};

// �ϱ�������ɫ���� [12/22/2009 Macro]
message CMessageCorpsSelectColorRequest
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			Color			= 2;			// ��ɫ
};

message CMessageCorpsSelectColorResponse
{
	optional CorpsHead		CorpHead		= 1;			// ������Ϣͷ
	optional uint32			RtnCode			= 2;			// �ɹ�:0,ʧ�ܣ���Ϣ��ʾ
	optional uint32			Color			= 3;			// ��ɫ
};

// *************************************************************************** //
// CMessageGetCorpsGoodsListRequest
// ��ȡ������Ʒ�б����Ϣ����
// *************************************************************************** //
message CorpsGoodItem
{
	optional uint32 ItemID		= 1;
	optional uint32	ItemNum		= 2;
	optional uint32 ComposeID	= 3;	// ���Ӻϳɵ�ID,�һ���
};

message CMessageGetCorpsGoodsListRequest
{
	optional CorpsHead CorpHead = 1;			// ������Ϣͷ
	optional uint32	CorpsID		= 2;			// ����Id(������ֵ)
	optional uint32	EntityID	= 3;			// npcʵ��ID
	optional uint32	NpcTmpID	= 4;			// npcģ��ID( �������� )  
};

// *************************************************************************** //
// CMessageGetCorpsGoodsListResponse
// ��ȡ������Ʒ�б����Ϣ��Ӧ
// *************************************************************************** //
message CMessageGetCorpsGoodsListResponse
{	
	optional CorpsHead		CorpHead	= 1;		// ������Ϣͷ
	optional uint32			Errcode		= 2;		// ������
	repeated CorpsGoodItem	GoodsList	= 3;		// �����Ѿ��������Ʒ�б�
	optional uint32			NpcTmpID	= 4;		// npcģ��ID	
};

// *************************************************************************** //
// CMessageGetCorpsExchangeGoodsListRequest
// ��ȡ���Ŷһ���Ʒ�б����Ϣ����
// *************************************************************************** //
message CMessageGetCorpsExchangeGoodsListRequest
{
	optional CorpsHead CorpHead = 1;		// ������Ϣͷ
	optional uint32	CorpsID =	2;		// ����Id(������ֵ)
	optional uint32	EntityID =  3;		// npcʵ��ID
	optional uint32	NpcTmpID = 4;			// npcģ��ID( �������� )  
};

// *************************************************************************** //
// CMessageGetCorpsExchangeGoodsListResponse
// ��ȡ���Ŷһ���Ʒ�б����Ϣ��Ӧ
// *************************************************************************** //
message CMessageGetCorpsExchangeGoodsListResponse
{
	optional CorpsHead		CorpHead	= 1;		// ��������Ϣͷ
	optional uint32			Errcode		= 2;		// ������
	repeated CorpsGoodItem	GoodsList	= 3;		// �����ܹ��һ�����Ʒ�б�(��������)
	optional uint32			NpcTmpID	= 4;		// npcģ��ID
};


message CMessageChangeUnionNameRequest
{
	optional CorpsHead	CorpHead  = 1;		// ������Ϣͷ
	optional string	UnionName	=	2;		// ��������
	optional string	UnionNotice	=	3;		// ����֪ͨ
	optional uint32	CorpsID		=	4;		// �ͻ��˷����ľ���ID
};

message CMessageChangeUnionNameResponse
{
	optional CorpsHead	CorpHead  = 1;			// ������Ϣͷ
	optional uint32	Result		=	2;
};

message CMessageChangeUnionNameNotify
{
	optional CorpsHead	CorpHead  = 1;		// ������Ϣͷ
	optional string	UnionName	=	2;		// ��������
	optional string	UnionNotice	=	3;		// ����֪ͨ
	
};

// *************************************************************************** //
// CMessageChangeCorpsGoodsList
// �ı�����̵���Ʒ�б����Ϣ֪ͨ
// *************************************************************************** //
message CMessageChangeCorpsGoodsListNotify
{
	repeated CorpsGoodItem	GoodsList	=	1;		// ��Ʒ�б�
	optional uint32			NpcTmpID	=	2;		// npc��ģ��ID	
};

// *************************************************************************** //
// CMessageChangeCorpsExchangeGoodsListNotify
// �ı���Ŷһ��̵���Ʒ�б����Ϣ֪ͨ
// *************************************************************************** //
message CMessageChangeCorpsExchangeGoodsListNotify
{
	repeated CorpsGoodItem	GoodsList	=	1;		// ��Ʒ�б�
	optional uint32			NpcTmpID	=	2;		// npc��ģ��ID
};

// *************************************************************************** //
// CMessageUseCorpsLeagueShopItemNofiy
// ʹ�þ����ع���Ʒ��֪ͨ
// *************************************************************************** //
message CMessageUseCorpsLeagueItemNotify
{
	repeated CorpsGoodItem	GoodsList	=	1;		// ��Ʒ�б�
	optional uint32			ManagerID	=	2;		// ������ID
	optional string			ManagerName	=	3;		// �����߽�ɫ����	
};

// ����ս������
message CMessageCorpsLoginBattleRequest
{
	optional CorpsHead	CorpHead  = 1;		// ������Ϣͷ
	optional uint32		NpcID	  = 2;		// npcid
};

message CMessageCorpsLoginBattleResponse
{
	optional CorpsHead	CorpHead  = 1;		// ������Ϣͷ
	optional uint32		RtnCode	  = 2;		// ������
};

message CMessageSummonCorpsBossRequest
{
	optional CorpsHead CorpHead = 1;		//������Ϣͷ
	optional uint32	BossID		= 2;		//boss id
};

message CMessageSummonCorpsBossResponse
{
	optional CorpsHead CorpHead		= 1;		//������Ϣͷ
	optional uint32		ErrorCode	= 2;		//��Ϣ������ 0 ��ʾ��ȷ ������ʾ����
};

message CMessageCorpsBossRepetionOpenNotify
{
	optional uint32		BossID		= 1;			//����boss id
	optional uint32		RoleID		= 2;			//�����˵�roleid
	optional string		RoleName	= 3;			//�����˵Ľ�ɫ��
	optional uint32		BossCDCool	= 4;			//boss����ȴʱ��
};

message CMessageIntoCorpsBossRepetionResponse
{
	optional CorpsHead		CorpHead		= 1;		//������Ϣͷ			
	optional uint32			ErrorCode		= 2;		//������	
};

message CMessageCorpsBossRepetionEndNotify
{

};