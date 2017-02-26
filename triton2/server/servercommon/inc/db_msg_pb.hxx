
import "property_pb.hxx";
import "boursemessage_pb.hxx";

// ������ٶ�����/������
option optimize_for = SPEED;


enum DB_MSG_ID
{	
	ID_S2S_EXECUTESQL_REQUEST			= 0x81FE; // ������->������ ִ��SQL�������
	ID_S2S_EXECUTESQL_RESPONSE			= 0x81FF; // ������->������ ִ��SQL����Ӧ

	ID_S2D_LOADPLAYERITEMINFO_REQUEST	= 0x7C02;	// ����������->���ݷ����� �����ݿ�����װ����Ϣ
	ID_D2S_LOADPLAYERITEMINFO_RESPONSE	= 0x7C03;	// ���ݷ�����->���������� ���ݿⷵ��װ����Ϣ

	ID_S2D_SAVEPLAYERITEMINFO_REQUEST	= 0x7C04;	// ����������->���ݷ����� ���������Ϣ����
	ID_D2S_SAVEPLAYERITEMINFO_RESPONSE	= 0x7C05;	// ���ݷ�����->���������� ���������Ϣ��Ӧ

	ID_S2D_LOADPLAYERINFO_REQUEST		= 0x7C06;	// ����->����				Load ��һ�����������
	ID_D2S_LOADPLAYERINFO_RESPONSE		= 0x7C07;	// ����->����				Load ��һ������ݻ�Ӧ	

	ID_S2D_SAVEPLAYER_REQUEST		= 0x7C08;		// ����->����				���������������
	ID_D2S_SAVEPLAYER_RESPONSE		= 0x7C09;		// ����->����				b����������ݻ�Ӧ

	ID_S2D_LOADPLAYERPROPERTY_REQUEST	= 0x7C0A;
	ID_D2S_LOADPLAYERPROPERTY_RESPONSE	= 0x7C0B;


	ID_S2D_UPDATEPLAYERINFO_REQUEST		= 0x7C0E;	// ֱ���޸������������
	ID_D2S_UPDATEPLAYERINFO_RESPONSE	= 0x7C10;	// ֱ���޸�������ݻ�Ӧ

	// ������
	ID_G2D_GETBOURSE_INFO				= 0x7C11;
	ID_S2D_BOURSE_INC_ACCOUNT			= 0x7C13;		// ���ʻ������
	ID_S2D_BOURSE_DEC_ACCOUNT			= 0x7C14;		// ���ʻ�����ȡ
	ID_S2D_BOURSE_GET_ACCOUNT			= 0x7C15;		// ����ʻ�
	ID_D2S_BOURSE_ACCOUNT_NOTICE		= 0x7C16;		//	�ʻ���Ϣ����
	ID_S2D_BOURSE_ADD_DOC				= 0x7C17;		// ��Ӷ���
	ID_S2D_BOURSE_PLAYER_LIST_GET		= 0x7C18;		// 
	ID_D2S_BOURSE_PLAYER_NOTICE			= 0x7C19;
	ID_G2D_BOURSE_TRADE					= 0x7C1A;
	ID_S2D_BOURSE_DEC_BUY_DOC			= 0x7C1B;
	ID_S2D_BOURSE_DEC_SELL_DOC			= 0x7C1C;
	ID_S2D_BOURSE_LOG_QUERY				= 0x7C1D;
	ID_D2S_BOURSE_LOG					= 0x7C1E;
};

enum SQLTYPE {
	SELECT = 1;
	INSERT = 2;
	UPDATE = 3;
	DELETE = 4;
};

//message PBBourseDetail
//{
//	optional string bourse_doc_no	= 1;
//	optional uint32	account_id		= 2;
//	optional uint32 price			= 3;
//	optional uint32 yb_count		= 4;
//	optional uint32 bourse_date		= 5;
//	optional uint32 trade_type		= 6;
//};

//message PBBourseDetailList
//{	 
//	repeated PBBourseDetail list = 1;
//};


message CMessageExecuteSqlRequest
{
	optional uint32	SessionID		= 1; // �ỰID
	optional string	SQL				= 2; // SQL���
	optional uint32	BufSize			= 3; // ����buf�ĳ��ȣ�û�о���0
	optional bytes	Buffer			= 4; // �����Ķ�����buf  
	optional uint32	Callback		= 5; // �Ƿ���Ҫ����ֵ�� 1-��Ҫ��0-����Ҫ
	optional uint32 LatestAutoIncID	= 6; // �Ƿ���Ҫ����������ID; 1-��Ҫ��0-����Ҫ
	optional SQLTYPE SqlType		= 7 [default = SELECT];// sql ��������
	optional uint32 SessionType		= 8; // session���� CSessionType
};

message CMessageExecuteSqlResponse3
{
	optional uint32	SessionID		= 1; // �ỰID
	optional uint32	ResultCode		= 2; // ���صĴ�����
	optional uint32	RowCount		= 3[default=0]; // ������
	optional uint32	ColCount		= 4[default=0]; // ������
	repeated string FieldName		= 5; // ������ ( �䳤�������Ϊ ColCount )
	repeated uint32 FieldType		= 6; // ������ ( �䳤�������Ϊ ColCount )
	repeated bytes	FieldValue		= 7; // ��ֵ ( �䳤�������Ϊ RowCount * ColCount )
	repeated uint32	FieldValueLen	= 8; // ��ֵ���� ( �䳤�������Ϊ RowCount * ColCount )
	optional uint32 LatestAutoIncID	= 9; // ����������ID��ֵ
};






// ���ص�����Ϣ
enum emPackageIdx
{
	PACKAGE_EQUIPMENT	= 0; // װ��
	PACKAGE_BAGGAGE		= 1; // ����
	PACKAGE_STORAGE		= 2; // �ֿ�
	PACKAGE_TASK		= 3; // �����
};

// ���ֱ��������һ��
enum emReSaveFlag
{
	SAVE_PACKAGE_EQUIPMENT	= 0; // װ��
	SAVE_PACKAGE_BAGGAGE		= 1; // ����
	SAVE_PACKAGE_STORAGE		= 2; // �ֿ�
	SAVE_PACKAGE_TASK		= 3; // �����
	SAVE_PLAYER_INFO			= 4; // ��һ�����Ϣ
	SAVE_PLAYER_PRO			= 5; // ���������Ϣ
	SAVE_ITEM_NUM		= 6; // ����
	SAVE_ITEM_FULL_FLAG = 0x3F; // �洢���
};



// �����ݿ������ҵ�����Ϣ
message CMessageLoadPlayerItemInfoRequest
{
	optional uint32 AccountID		= 1;
	optional uint32 CharID			= 2;
	repeated uint32 PackageIdx		= 3;	//���� emPackageIdx
	optional uint32 SessionID		= 4;	
};

// ���ݿⷵ�ص�����Ϣ
message CMessageLoadPlayerItemInfoResponse
{
	enum emErrorCode
	{
		SUCCES			= 0;		// ִ��sql�ɹ�
		SQL_FAILED		= -1;		// ִ��sqlʧ��
		RECORD_EMPTY	= -2;		// �ռ�¼
		DATA_CRASH		= -3;		// �����𻵣�һ��ָblob����
	};
	
	optional int32	ErrCode			= 1;	// ������	
	optional uint32 AccountID		= 2;
	optional uint32 CharID			= 3;
	optional uint32 SessionID		= 4;
	repeated uint32 PackageIdx		= 5;	//���� emPackageIdx
	repeated PBItemBox ItemBox		= 6;
};

// ������ҵ�����Ϣ����
message CMessageSavePlayerItemInfoRequest
{
	optional uint32 AccountID		= 1;
	optional uint32 CharID			= 2;
	repeated uint32 PackageIdx		= 3;	//���� emPackageIdx
	optional uint32 SessionID		= 4;
	repeated PBItemBox ItemBox		= 6;
};

// ������ҵ�����Ϣ��Ӧ
message CMessageSavePlayerItemInfoResponse
{
	enum emErrorCode
	{
		SUCCES			= 0;		// ִ��sql�ɹ�
		SQL_FAILED		= -1;		// ִ��sqlʧ��
		SERALIZE_FAILED	= -2;		// ���л�ʧ��
		FILTER_FAILED	= -3;		// Ϊblob����ת���ַ���ʧ��
		INVALID_PKGIDX	= -4;		// ��Ч�İ�������
	};

	optional int32	ErrCode			= 1;	// ������	
	optional uint32 AccountID		= 2;
	optional uint32 CharID			= 3;
	repeated uint32 PackageIdx		= 4;	//���� emPackageIdx
	optional uint32 SessionID		= 5;
};



message CMessagePlayerProperty
{
	optional uint32 role_hp					= 1;
	optional uint32 role_mp					= 2;
	optional uint32 role_ap					= 3;
	optional PBPlayerBasicInfo role_basic	= 4;
	optional PBSkillList role_skill			= 5;
	optional PBBuffList role_buff			= 6;
	optional PBPlayerCDGroupInfo role_cdgroup			= 7;
	optional PBPlayerPVPInfo role_pvp		= 8;
	optional PBPlayerTitleInfo role_title				= 9;
	optional PBPlayerActivityInfo role_activity			= 10;
	optional PBPlayerTalentInfo role_talent				= 11;
	optional PBPlayerMWInfo role_mw						= 12;
	optional PBLifeSkillBox role_lifeskill			= 13;
	optional PBPlayerStatisticInfo role_statistic			= 14;
	optional PBMonsterRecordInfo role_monster_record	= 15;
	optional PBTelePosInfo role_tele_pos			= 16;
	optional PBWizard role_wizard				= 17;
	optional PBPlayerClientInfo role_client				= 18;
	optional uint32	save_bitflag			= 19;
	optional PBFriend role_friend			= 20;
	optional PBRepetion role_repetion		= 21;
	optional PBTaskList role_task			= 22;
	optional PBMatrixInfo role_matrix		= 23;
	optional PBCharm role_charm		= 24;
	optional PBGuideData role_guide		= 25;
	optional PBTimes role_times		= 26;
	optional PBExpTimeInfo role_exptimeinfo	= 27;
	optional PBTreasureBowl role_treasurebowl = 28;
	optional PBSpiritInfo role_spiritinfo = 29;
};

message CMessageSavePlayerRequest
{
	optional uint32 RoleID					= 1;
	optional CMessagePlayerInfo Info		= 2;
	optional CMessagePlayerProperty Property= 3;
	optional uint32 SessionID				= 4;
	optional uint32 DetailID				= 5;
	optional uint32 CallBack				= 6;
};

message CMessageLoadPlayerInfoRequest
{
	optional uint32 RoleID					= 1;
	optional uint32 SessionID				= 2;
};

message CMessageLoadPlayerInfoResponse
{
	optional uint32 RoleID					= 1;
	optional uint32 SessionID				= 2;
	optional CMessagePlayerInfo Info		= 3;
	optional uint32 ResultCode				= 4;
};

message CMessageSavePlayerResponse
{
	optional uint32 RoleID					= 1;
	optional uint32 SessionID				= 2;
	optional uint32 ResultCode				= 3;
};

message CMessageLoadPlayerPropertyRequest
{
	optional uint32 RoleID					= 1;
	optional uint32 SessionID				= 2;
	optional uint32 DetailID				= 4;

};

message CMessageLoadPlayerPropertyResponse
{
	optional uint32	RoleID					= 1;
	optional uint32 SessionID				= 2;
	optional CMessagePlayerProperty Property= 3;
	optional uint32 ResultCode				 = 4;
};



enum UpdateType
{
	BasicInfo		= 1;
	SkillList		= 2;
	BuffList		= 3;
	CDGroup			= 4;
	PVPInfo			= 5;
	TitleInfo		= 6;
	ActivityInfo	= 7;
	TalentInfo		= 8;
	MWInfo			= 9;
	LifeSkill		= 10;
	StasticInfo		= 11;
	MonsterInfo		= 12;
	TelePosInfo		= 13;
	Wizard			= 14;
	ClientInfo		= 15;
	Friend			= 16;
	Repetion		= 17;
	TaskList		= 18;
	MatrixInfo		= 19;
	Charm			= 20;
	Guide			= 21;
	Times			= 22;
};

message CMessageUpdatePlayerInfoRequest
{
	optional uint32	RoleID					= 1;
	optional uint32 SessionID				= 2;
	optional uint32	UpdateType				= 3;
	optional uint32 Param1					= 4;
	optional uint32	Param2					= 5;
	optional uint32	Value					= 6;
	optional uint32	DetailID				= 7;
	optional uint32 SubType					= 8;
};

enum MatrixSubType
{
	RemoveMaster	=	1;
	RemoveSlave		=	2;
	AddMasterPoint	=	3;
	AddSlaveNum		=	4;
	AddFormal		=	5;
};

enum MatrixParam
{
	BeginnerNum		=	1;
	FormalNum		=	2;
	EducatedNum		=	3;
};


message CMessageGetBourseInfo
{
	optional uint32 SessionID				= 1;
	optional uint32 AccountID				= 2;
};

message CMessageBourseInfoNotice
{
	optional uint32			SessionID		= 1;
	optional PBBourseDetailList BuyList			= 2;
	optional PBBourseDetailList SellList		= 3;	
};

message CMessageBourseAddDoc
{
	optional uint32			SessionID		= 1;
	optional uint32			AccountID		= 2;
	optional PBBourseDetail	Detail			= 3;
	optional uint32			Type			= 4;	// 1 buy 2 sell
	
	optional uint32			Tax				= 5;
	optional uint32			RoleID			= 6;
	optional uint32			Level			= 7;
	optional uint32			WorldID			= 8;
	optional uint32			ServerID		= 9;
	optional uint32			TaxID			= 10;
	optional uint32			GameID			= 11;
};


message CMessageBourseS2DIncAccount
{
	optional uint32			SessionID		= 1;
	optional uint32			Money			= 2;
	optional uint32			Yb				= 3;
	optional uint32			AccountID		= 4;
	optional uint32			RoleID			= 5;
};

message CMessageBourseS2DDecAccount
{
	optional uint32			SessionID		= 1;
	optional uint32			Money			= 2;
	optional uint32			Yb				= 3;
	optional uint32			AccountID		= 4;
	optional uint32			RoleID			= 5;
};

message CMessageBourseS2DGetAccount
{
	optional uint32			SessionID		= 1;
	optional uint32			AccountID		= 2;
	optional uint32			Code			= 3;
};

message CMessageBourseD2SAccountNotice
{
	optional uint32			SessionID		= 1;
	optional uint32         Money           = 2;
	optional uint32         Yb              = 3;
	optional uint32			AccountID		= 4;
	optional uint32			Code			= 5;	
	optional uint32			Result			= 6;
	optional uint32			Parame1		= 7;
	optional uint32			Parame2		= 8;
};


message CMessageUpdatePlayerInfoResponse
{
	optional uint32	RoleID					= 1;
	optional uint32 SessionID				= 2;
	optional uint32 ResultCode				= 3;
};


message CMessageBoursePlayerListNotice
{
	optional uint32 AccountID				= 1;
    optional PBBourseDetailList BuyList         = 2;
    optional PBBourseDetailList SellList        = 3;
};

message CMessageBoursePlayerListGet
{
	optional uint32 AccountID				= 1;	
};

message CMessageBourseTrade
{
	optional uint32 BuyPrice				= 1;
	optional uint32 SellPrice				= 2;
	optional uint32 Rating_id				= 3;
	optional uint32 Worldid					= 4;
};

message CMessageS2DBourseDecBuyDoc
{
	optional uint32 Doc						= 1;
	optional uint32 AccountID				= 2;
	optional uint32 RoleID					= 3;
};

message CMessageS2DBourseDecSellDoc
{
	optional uint32 Doc						= 1;
	optional uint32	AccountID				= 2;
	optional uint32 RoleID					= 3;
};

message CMessageBourseLogQuery
{
	optional uint32 AccountID				= 1;
};

message CMessageD2SBourseLog
{
	optional uint32 AccountID							= 1;
	optional PBBourseDetailList		buy_log				= 2;
	optional PBBourseDetailList		sell_log			= 3;

};







