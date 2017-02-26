// ������ٶ�����/������
option optimize_for = SPEED;
import "corpsinfo_pb.hxx";


enum CountryMessageID // MESSAGE_COUNTRY = 0x5400
{
	ID_C2S_REQUEST_COUNTRYINFO			= 0x5401;	// ��ù�����Ϣ����
	ID_S2C_RESPONSE_COUNTRYINFO			= 0x5402;	// ��ù�����Ϣ��Ӧ

	ID_C2S_REQUEST_JOINCOUNTRY			= 0x5403;	// �����������
	ID_S2C_RESPONSE_JOINCOUNTRY			= 0x5404;	// ������һ�Ӧ

	ID_C2S_REQUEST_LEAVECOUNTRY			= 0x5405;	// �뿪��������
	ID_S2C_RESPONSE_LEAVECOUNTRY		= 0x5406;	// �뿪���һ�Ӧ

	ID_C2S_REQUEST_SETOFFICIAL			= 0x5407;	// ����������ְ����
	ID_S2C_RESPONSE_SETOFFICIAL			= 0x5408;	// ����������ְ��Ӧ

	ID_C2S_REQUEST_UNSETOFFICIAL		= 0x5409;	// ���������ְ����
	ID_S2C_RESPONSE_UNSETOFFICIAL		= 0x540A;	// ���������ְ��Ӧ

	ID_C2S_REQUEST_USEFUNCTION			= 0x540B;	// ʹ�ù��ҹ�������
	ID_S2C_RESPONSE_USEFUNCTION			= 0x540C;	// ʹ�ù��ҹ��ܻ�Ӧ

	ID_C2S_REQUEST_OFFICIALINFO			= 0x540D;	// ��ְ��Ϣ����
	ID_S2C_RESPONSE_OFFICIALINFO		= 0x540E;	// ��ְ��Ϣ��Ӧ

	ID_C2S_REQUEST_USETIME				= 0x540F;	// ��ѯʹ��ʱ������
	ID_S2C_RESPONSE_USETIME				= 0x5410;	// ��ѯʹ��ʱ���Ӧ

	ID_C2S_REQUEST_WORLDQUEST			= 0x5411;	// �����������
	ID_S2C_RESPONSE_WORLDQUEST			= 0x5412;	// ���������Ӧ

	ID_S2C_NOTIFY_WORLDQUEST			= 0x5413;	// �������֪ͨ

	ID_C2S_REQUEST_WORLDANSWER			= 0x5414;	// �ظ���������
	ID_S2C_RESPONSE_WORLDANSWER			= 0x5415;	// �ظ������Ӧ

	ID_S2C_NOTIFY_WORLDRESULT			= 0x5416;	// ������֪ͨ

	ID_C2S_REQUEST_WORLDINFO			= 0x5417;	// ������Ϣ����
	ID_S2C_RESPONSE_WORLDINFO			= 0x5418;	// ������Ϣ��Ӧ

	ID_S2C_NOTIFY_JOINCOUNTRY			= 0x5419;	// �������֪ͨ
	ID_S2C_NOTIFY_OFFICIALCHANGE		= 0x541A;	// ��Ա�ı�֪ͨ
	ID_S2C_NOTIFY_WORLDANSWER			= 0x541B;	// ����ظ�֪ͨ

	ID_C2S_REQUEST_PLAYERGSINFO			= 0x541C;		// ��ȡ�������������
	ID_S2C_RESPONSE_PLAYERGSINFO		= 0x541D;
	ID_S2C_NOTIFY_PLAYERGSINFO			= 0x541E;

	ID_S2C_NOTIFY_KINGCHANGE			= 0x5420;	// �����ı�֪ͨ

	ID_C2S_REQUEST_GETAWARD				= 0x5421;	// ��ȡ��������
	ID_S2C_RESPONSE_GETAWARD			= 0x5422;	
	ID_S2C_NOTIFY_STARTCOUNTRYREDSTONE	= 0x5423; 		// ���������ڵ���֪ͨ	
	ID_S2C_NOTIFY_SUMMONPLAYER			= 0x5424;

	ID_C2S_REQUEST_SUBMITWAR			= 0x5425;	// ��ս��������
	ID_S2C_RESPONSE_SUBMITWAR			= 0x5426;	// ��ս������Ӧ

	ID_C2S_REQUEST_ENTERWAR				= 0x5427;	// ��ս����ս������
	ID_S2C_RESPONSE_ENTERWAR			= 0x5428;	// ��ս����ս����Ӧ

	ID_C2S_REQUEST_QUERYWARCAMP			= 0x5429;	// ��ս��ѯս����������
	ID_S2C_RESPONSE_QUERYWARCAMP		= 0x542A;	// ��ս��ѯս�������Ӧ

	ID_C2S_REQUEST_QUERYWARNUM			= 0x542B;	// ��ս��ѯս����������
	ID_S2C_RESPONSE_QUERYWARNUM			= 0x542C;	// ��ս��ѯս��������Ӧ

	ID_C2S_REQUEST_QUERYWARINFO			= 0x542D;	// ��ս��ѯս����Ϣ����
	ID_S2C_RESPONSE_QUERYWARINFO		= 0x542E;	// ��ս��ѯս����Ϣ��Ӧ

	ID_C2S_REQUEST_QUERYRANK			= 0x5430;	// ��ս��ѯְҵ��������
	ID_S2C_RESPONSE_QUERYRANK			= 0x5431;	// ��ս��ѯְҵ������Ӧ

	ID_S2C_NOTIFY_WARSOURCE				= 0x5432;	// ս����Դ֪ͨ

	ID_C2S_REQUEST_BIDCAMP				= 0x5433;	// ��սӪ�ؾ�������
	ID_S2C_RESPONSE_BIDCAMP				= 0x5434;	// ��սӪ�ؾ��ۻ�Ӧ

	ID_C2S_REQUEST_CAMPBIDINFO			= 0x5435;	// ��ս��ѯӪ�ؾ�������
	ID_S2C_RESPONSE_CAMPBIDINFO			= 0x5436;	// ��ս��ѯӪ�ؾ��ۻ�Ӧ

	ID_C2S_REQUEST_CAMPRESINFO			= 0x5437;	// ��ս��ѯӪ�ؽ������
	ID_S2C_RESPONSE_CAMPRESINFO			= 0x5438;	// ��ս��ѯӪ�ؽ����Ӧ

	ID_C2S_REQUEST_GETWARAWARD			= 0x5439;	// ��ս��ý�������
	ID_S2C_RESPONSE_GETWARAWARD			= 0x543A;	// ��ս��ý�����Ӧ

	ID_S2C_NOTIFY_WARINFO				= 0x543B;	// ��ս��Ϣ֪ͨ

	ID_C2S_REQUEST_QUERYWARAWARD		= 0x543C;	// ��ս��ѯ��������
	ID_S2C_RESPONSE_QUERYWARAWARD		= 0x543D;	// ��ս��ѯ������Ӧ

	ID_S2C_NOTIFY_WARHONOR				= 0x543E;	// ��ս���ս��֪ͨ
	ID_S2C_NOTIFY_WARCAMP				= 0x5440;	// ��ս��Ӫ֪ͨ

	ID_C2S_REQUEST_MODIFYRATE			= 0x5441;	// �޸�˰������
	ID_S2C_RESPONSE_MODIFYRATE			= 0x5442;	// �޸�˰�ʻ�Ӧ
	ID_S2C_NOTIFY_MODIFYRATE			= 0x5443;	// �޸�˰��֪ͨ

	ID_C2S_REQUEST_GETTAX				= 0x5444;	// ���˰������
	ID_S2C_RESPONSE_GETTAX				= 0x5445;	// ���˰���Ӧ

	ID_S2C_NOTIFY_QUERYSTONE			= 0x5446;	// ��ѯ��ʯ֪ͨ
	ID_C2S_REQUEST_REFUSESUMMON			= 0x5447;	// �ܾ��ٻ�����
	ID_S2C_NOTIFY_REFUSESUMMON			= 0x5448;	// �ܾ��ٻ�֪ͨ

	ID_C2S_REQUEST_ACCUSEKING			= 0x5449;	// ������������
	ID_S2C_RESPONSE_ACCUSEKING			= 0x544A;	// �������ӻ�Ӧ
	ID_S2C_NOTIFY_ACCUSEKING			= 0x544B;	// ��������֪ͨ
	ID_S2C_NOTIFY_ACCUSESTATUS			= 0x544C;	// �����㲥֪ͨ
	ID_C2S_REQUEST_POWERINFO			= 0x544D;	// ������ѯ����
	ID_S2C_RESPONSE_POWERINFO			= 0x544E;	// ������ѯ��Ӧ
	ID_S2C_NOTIFY_MAKEGUOTAN			= 0x5450;	// ������֪̽ͨ
	ID_S2C_NOTIFY_MAKELUANWU			= 0x5451;	// ��������֪ͨ
};

enum EM_CampMessageID								// CAMP_MESSAGE		= 0x6000 - 0x63FF
{
	ID_C2S_CAMPWEAKLIST_REQUEST			= 0x5501;	// �ͻ�������������Ӫ��Ϣ�б�
	ID_S2C_CAMPWEAKLIST_RESPONSE		= 0x5502;	// �������ظ�������Ӫ��Ϣ�б�

	ID_C2S_CAMPAWARDQUERY_REQUEST		= 0x5503;	// �ͻ��˲�ѯ������Ӫ����
	ID_S2C_CAMPAWARDQUERY_RESPONSE		= 0x5504;	// ����������������Ӫ������Ϣ

	ID_C2S_CAMPGETAWARD_REQUEST			= 0x5505;	// �ͻ�����ȡ������Ӫ����
	ID_S2C_CAMPGETAWARD_RESPONSE		= 0x5506;	// ������������ȡ������Ӫ����ȷ��
};

// ��Ա�Ĵ洢�ṹ
message PBOfficialData
{
	optional uint32			CharID			= 1;		// ��Ա��CharID
	optional string			CharName		= 2;		// ��Ա������
	optional uint32			OfficialLevel	= 3;
	optional uint32			OfficialOrder	= 4;
	repeated uint32			UseTimes		= 5;		// ��ԱȨ����ʹ�ô���
	repeated uint32			UseX			= 6;
	repeated uint32			UseY			= 7;
};

// ���ҵĹ�Ա�ṹ
message PBOfficialList
{
	repeated PBOfficialData	OfficialData = 1;		// ��Ա����
};

message CMessageCountryInfoRequest
{
	optional uint32		CharID			= 1;
	optional uint32		CountryID		= 2;
	optional uint32		NeedFull		= 3;
	optional uint32		WorldID			= 4;
};

message CMessageCountryInfoResponse
{
	optional uint32		CharID			= 1;
	optional uint32		CountryID		= 2;
	optional uint32		KingID			= 3;		// ����ID
	optional string		KingName		= 4;		// ��������
	optional uint32		CorpsID			= 5;		// ����ID
	optional string		CorpsName		= 6;		// ��������
	optional uint32		UnionID			= 7;		// ����ID
	optional string		UnionName		= 8;		// ��������
	optional uint32		PeopleNum		= 9;		// ��������
	optional uint32		KingPower		= 10;		// ��������
	optional uint32		Map				= 11;		// ��������
	optional uint32		Gold			= 12;		// ���ҽ��
	repeated uint32		Wizard			= 13;		// �Ż�ֵ
	repeated uint32		ConstructValue	= 14;		// �����
	repeated uint32		ConstructLevel	= 15;		// �����
	optional string		Notice			= 16;		// ����
	optional PBCorpsBattleList	BattleInfo	 =	17;			// ����ս����Ϣ
	optional uint32		NeedFull		= 18;		// �Ƿ���Ҫȫ����Ϣ
	optional uint32		WorldID			= 19;
	optional uint32		WorldLevel		= 20;		// ��Ӫ(����)�ȼ�
};

message CMessageJoinCountryRequest
{
	optional uint32		CharID			= 1;
	optional uint32		CountryID		= 2;
	optional uint32		NPCEntityID		= 3;
};

message CMessageJoinCountryResponse
{
	optional uint32		CharID			= 1;
	optional uint32		Result			= 2;
	optional uint32		CountryID		= 3;
};

message CMessageJoinCountryNotify
{
	optional uint32		CharID			= 1;
	optional uint32		CountryID		= 2;
	optional uint32		KingID			= 3;
};

message CMessageLeaveCountryRequest
{
	optional uint32		CharID			= 1;
	optional uint32		CountryID		= 2;
	optional uint32		NPCEntityID		= 3;
};

message CMessageLeaveCountryResponse
{
	optional uint32		CharID			= 1;
	optional uint32		Result			= 2;
	optional uint32		CountryID		= 3;
};

message CMessageSetOfficialRequest
{
	optional uint32		CharID				= 1;	// ������ID,��������
	optional string		CharName			= 2;	// ��ɫ��
	optional uint32		OfficialLevel		= 3;	// ��ְƷ��
	optional uint32		OfficialOrder		= 4;	// ��ְλ��
	optional uint32		NormalSet			= 5;
};

message CMessageSetOfficialResponse
{
	optional uint32		CharID				= 1;	// ������ID,��������
	optional uint32		Result				= 2;
	optional string		CharName			= 3;	// ��ɫ��
	optional uint32		OfficialLevel		= 4;	// ��ְƷ��
	optional uint32		OfficialOrder		= 5;	// ��ְλ��
	optional uint32		NormalSet			= 6;
	optional uint32		TargetID			= 7;	// ���õ�ID
};

message CMessageUnSetOfficialRequest
{
	optional uint32		CharID				= 1;	// ������ID,��������
	optional uint32		OfficialLevel		= 2;	// ��ְƷ��
	optional uint32		OfficialOrder		= 3;	// ��ְλ��
};

message CMessageUnSetOfficialResponse
{
	optional uint32		CharID				= 1;	// ������ID,��������
	optional uint32		Result				= 2;
	optional string		CharName			= 3;	// ��ɫ��
	optional uint32		OfficialLevel		= 4;	// ��ְƷ��
	optional uint32		OfficialOrder		= 5;	// ��ְλ��
};

message CMessageUseFunctionRequest
{
	optional uint32		CharID				= 1;	// ������ID,��������
	optional uint32		FunctionType		= 2;	// ��������
	optional uint32		FunctionOrder		= 3;	// ���ܱ��
	optional string		TargetName			= 4;	// Ŀ������
	optional TeleportData Teleport			= 5;
	optional uint32		IntParam1			= 6;	// ����1
};

message CMessageUseFunctionResponse
{
	optional uint32			CharID				= 1;	// ������ID,��������
	optional uint32			Result				= 2;
	optional uint32			FunctionType		= 3;	// ��������
	optional uint32			FunctionOrder		= 4;	// ���ܱ��
	optional string			TargetName			= 5;	// Ŀ������
};

message CMessageOfficialInfoRequest
{
	optional uint32		CharID				= 1;	// ������ID,��������
};

message CMessageOfficialInfoResponse
{
	optional uint32			CharID				= 1;	// ������ID,��������
	optional uint32			Result				= 2;
	optional PBOfficialList OfficialList		= 3;	// ��Ա�б�
};

message CMessageUseTimeRequest
{
	optional uint32		CharID				= 1;	// ������ID,��������
};

message CMessageUseTimeResponse
{
	optional uint32			CharID				= 1;	// ������ID,��������
	optional uint32			Result				= 2;
	optional PBOfficialData OfficialData		= 3;	// ʹ�ô���
};

message CMessageWorldQuestRequest
{
	optional uint32		CharID			= 1;
	optional uint32		WorldID			= 2;
	optional uint32		OpType			= 3;
	optional uint32		NPCEntityID		= 4;
};

message CMessageWorldQuestResponse
{
	optional uint32		CharID			= 1;
	optional uint32		Result			= 2;
	optional uint32		WorldID			= 3;
	optional uint32		OpType			= 4;
};

message CMessageWorldAnswerRequest
{
	optional uint32		CharID			= 1;
	optional uint32		WorldID			= 2;
	optional uint32		OpType			= 3;
	optional uint32		Answer			= 4;
};

message CMessageWorldAnswerResponse
{
	optional uint32		CharID			= 1;
	optional uint32		Result			= 2;
	optional uint32		WorldID			= 3;
	optional uint32		OpType			= 4;
	optional uint32		Answer			= 5;	// ���ӷ��ػظ�����
};

message CMessageWorldAnswerNotify
{
	optional uint32		CharID			= 1;
	optional uint32		SrcWorldID		= 2;
	optional uint32		DesWorldID		= 3;
	optional uint32		OpType			= 4;
	optional uint32		Answer			= 5;
};

message CMessageWorldQuestNotify
{
	optional uint32		CharID			= 1;
	optional uint32		WorldID			= 2;
	optional uint32		OpType			= 3;
};

message CMessageWorldResultNotify
{
	optional uint32		CharID			= 1;
	optional uint32		Result			= 2;
	optional uint32		SrcWorldID		= 3;
	optional uint32		DesWorldID		= 4;
	optional uint32		OpType			= 5;
};

message CWorldStatusData
{
	optional uint32		WorldID			= 1;
	optional uint32		Friends			= 2;
	optional uint32		Nation			= 3;
	optional uint32		KingID			= 4;
	optional string		KingName		= 5;
	optional uint32		CorpsID			= 6;
	optional string		CorpsName		= 7;
	optional uint32		UnionID			= 8;
	optional string		UnionName		= 9;
};

message CMessageWorldInfoRequest
{
	optional uint32				CharID			= 1;
	optional uint32				WorldID			= 2;
};

message CMessageWorldInfoResponse
{
	optional uint32				CharID			= 1;
	optional uint32				Result			= 2;
	optional uint32				WorldID			= 3;
	repeated CWorldStatusData	WorldData		= 4;
};

message CMessageOfficialChangeNotify
{
	optional uint32		CharID				= 1;
	optional string		CharName			= 2;	// ��ɫ��
	optional uint32		OfficialLevel		= 3;	// ��ְƷ��
	optional uint32		OfficialOrder		= 4;	// ��ְλ��
	optional uint32		CountryID			= 5;	// ����ID
	optional uint32		Type				= 6;
	optional uint32		WorldID				= 7;
};

message CMessagePlayerGSInfoRequest
{
	repeated uint32 SrcCharID	=		1;			// �����ߵ�CharID
	repeated uint32 InfoCharID	=		2;			// ��ȡ��Ϣ��CharID
};

message PlayerGSInfo
{
	optional uint32 CharID		=		1;			
	optional uint32	FamilyID	=		2;
	optional string	FamilyName	=		3;
	optional uint32	FamilyHead	=		4;
	optional uint32	CorpsID		=		5;
	optional string CorpsName	=		6;
	optional uint32	CorpsHead	=		7;
	optional uint32	UnionID		=		8;
	optional string	UnionName	=		9;
	optional uint32	UnionHead	=		10;
	optional uint32 CountryID	=		11;
	optional uint32	OfficialID	=		12;
	optional uint32 KingID		=		13;	
};

message WorldStatusInfo
{
	optional uint32	SrcWorldID	=		1;
	optional uint32	DesWorldID	=		2;
	optional uint32 Status		=		3;	
};

message GTAndLWInfo
{
	optional uint32	SrcWorldID	=		1;		// ������Ӫ
	optional uint32	DesWorldID	=		2;		// Ŀ����Ӫ
	optional uint32	TargetTime	=		3;		// ����ʱ��
};

message CMessagePlayerGSInfoResponse
{
	optional uint32				SrcCharID	=		1;
	repeated PlayerGSInfo		PlayerInfo	=		2;
	repeated WorldStatusInfo	WorldInfo	=		3;		
};

message CMessagePlayerGSInfoNotify
{
	optional uint32			SrcCharID	=		1;
	repeated PlayerGSInfo	PlayerInfo	=		2;
	repeated WorldStatusInfo	WorldInfo	=		3;
	optional uint32				WarState	=		4;		// ս��״̬
	optional uint32				WinWorld	=		5;		// ��ʤ��Ӫ
	optional uint32				TaxRate		=		6;		// ˰��
	repeated GTAndLWInfo		GTInfo		=		7;		// ��̽��Ϣ
	repeated GTAndLWInfo		LWInfo		=		8;		// ������Ϣ
};

// �������֪ͨ
message CMessageKingChangeNotify
{
	optional uint32		WorldID			= 1;
	optional uint32		CountryID		= 2;
	optional uint32		KingID			= 3;
	optional string		KingName		= 4;
};

// �����ټ�֪ͨ
message CMessageSummonPlayerNotify
{
	optional string		SrcName			= 1;
	optional uint32		LineID			= 2;
	optional uint32		MapID			= 3;
	optional uint32		PosX			= 4;
	optional uint32		PosY			= 5;
	optional uint32		TokenID			= 6;
};

// ��ȡ��������
message CMessageGetAwardRequest
{
	optional uint32		NPCEntityID		= 1;
	optional uint32		AwardID			= 2;
	optional uint32		TempID			= 3;
	optional uint32		Type			= 4;
};

message CMessageGetAwardResponse
{
	optional uint32		Result			= 1;
	optional uint32		AwardID			= 2;
	optional uint32		TempID			= 3;
	optional uint32		Type			= 4;
};


// *************************************************************************** //
// CMessageStartCountryRedstoneNotify
// ���������ڵ�����Ϣ֪ͨ
// *************************************************************************** //
message CMessageStartCountryRedstoneNotify
{
	optional string ManagerName	=	1;		// ʹ��������
	optional uint32	ManagerID	=	2;		// ʹ���߽�ɫID
	optional uint32	LineID		=	3;		// ʹ����������ID
	optional uint32	MapID		=	4;		// ʹ���ߵ�ͼID
	optional uint32	PosX		=	5;		// ʹ����x����
	optional uint32	PosY		=	6;		// ʹ����y����
	optional uint32	CountryID	=	7;		// ����ID
	optional uint32	RedstoneType =	8;		// �ڵ����ͣ������ڵ�������Ӫ�ڵ�( CTplRedStone::ERedStoneType )
};

message TeleportData
{
	optional uint32			LineID		= 1;
	optional uint32			MapID		= 2;
	optional uint32			PosX		= 3;
	optional uint32			PosY		= 4;
	optional uint32			TokenID		= 5;
};

message CMessageSubmitWarRequest
{
	optional uint32			CharID			= 1;
	optional uint32			NPCEntityID		= 2;
	optional uint32			WarSerial		= 3;
};

message CMessageSubmitWarResponse
{
	optional uint32			CharID		= 1;
	optional uint32			Result		= 2;
	optional uint32			WarSerial	= 3;
};

message CMessageEnterWarRequest
{
	optional uint32			CharID			= 1;
	optional uint32			WarID			= 2;		// ��Ҫ�����ս��ID
	optional uint32			NPCEntityID		= 3;
	optional uint32			WarSerial		= 4;	
};

message CMessageEnterWarResponse
{
	optional uint32			CharID		= 1;
	optional uint32			WarID		= 2;		// ��Ҫ�����ս��ID
	optional uint32			Result		= 3;
	optional uint32			PosX		= 4;
	optional uint32			PosY		= 5;
};

message CMessageQueryWarCampRequest
{
	optional uint32			CharID			= 1;
	optional uint32			NPCEntityID		= 2;
};

message CMessageQueryWarCampResponse
{
	optional uint32			CharID		= 1;
	repeated uint32			WorldID		= 2;		// ��ӪID
	repeated uint32			CampID		= 3;		// ��Ӧ��ս��ID
	repeated uint32			Money		= 4;		// Ǯ
};

message CMessageQueryWarNumRequest
{
	optional uint32			CharID			= 1;
	optional uint32			NPCEntityID		= 2;
};

message WarNumData
{
	optional uint32			WorldID			= 1;
	optional uint32			CampID			= 2;		// ս��ID
	optional uint32			CurrentNum		= 3;		// ��ǰ����
};

message CMessageQueryWarNumResponse
{
	optional uint32			CharID		= 1;
	repeated WarNumData		WarData		= 2;	
	optional uint32			CampID		= 3;
};

message WarDetailInfo
{
	optional uint32			WorldID		= 1;		// ��ӪID
	optional uint32			CurrentNum	= 2;		// ��ǰ����
	optional uint32			Power		= 3;		// ս����
	optional uint32			Flag		= 4;		// ռ��ݵ�
	optional uint32			Resource	= 5;		// ��Դ
	optional uint32			Kill		= 6;		// ��ɱ
	optional uint32			CampID		= 7;		// ս��ID
};

message CMessageQueryWarInfoRequest
{
	optional uint32			CharID			= 1;
	repeated uint32			CampID			= 2;		// ս��ID
	optional uint32			NPCEntityID		= 3;
};

message CMessageQueryWarInfoResponse
{
	optional uint32			CharID		= 1;
	repeated WarDetailInfo	CampInfo	= 2;		// ս����Ϣ
};

message WarRankInfo
{
	optional uint32			WorldID		= 1;		// ��ӪID
	optional uint32			MetierID	= 2;		// ְҵID
	optional uint32			Kill		= 3;		// ��ɱ
	optional string			CharName	= 4;		// ��ɫ��
	optional uint32			Rank		= 5;		// ����
	optional uint32			Honor		= 6;		// ս��
};

message CMessageQueryWarRankRequest
{
	optional uint32			CharID			= 1;
	optional uint32			NPCEntityID		= 2;
};

message CMessageQueryWarRankResponse
{
	optional uint32			CharID		= 1;
	repeated WarRankInfo	RankInfo	= 2;
};

message CMessageWarSourceNotify
{
	optional uint32			WorldID		= 1;
	optional uint32			MapID		= 2;
	optional uint32			Resource	= 3;
	optional uint32			CharID		= 4;
	optional uint32			SourceNum	= 5;
};

message CMessageBidCampRequest
{
	optional uint32			CharID			= 1;
	optional uint32			NPCEntityID		= 2;
	optional uint32			Money			= 3;
	optional uint32			CampID			= 4;
};

message CMessageBidCampResponse
{
	optional uint32			CharID		= 1;
	optional uint32			Result		= 2;
	optional uint32			Money		= 3;
	optional uint32			CampID		= 4;
};

message CMessageCampBidInfoRequest
{
	optional uint32			CharID			= 1;
	optional uint32			NPCEntityID		= 2;
};

message CMessageCampBidInfoResponse
{
	optional uint32			CharID		= 1;
	optional uint32			Result		= 2;
	optional uint32			Money		= 3;
	optional uint32			CampID		= 4;
};

message CMessageCampResInfoRequest
{
	optional uint32			CharID			= 1;
	optional uint32			NPCEntityID		= 2;
};

message CMessageCampResInfoResponse
{
	optional uint32			CharID		= 1;
	optional uint32			Result		= 2;
	repeated uint32			WorldID		= 3;
	repeated uint32			CampID		= 4;
	repeated uint32			Money		= 5;
};

message CMessageGetWarAwardRequest
{
	optional uint32			CharID			= 1;
	optional uint32			WarSerial		= 2;
};

message CMessageGetWarAwardResponse
{
	optional uint32			CharID		= 1;
	optional uint32			Result		= 2;
	optional uint32			Money		= 3;
	optional uint32			Rank		= 4;
	optional uint32			ValidTime	= 5;
};

message NPCWarInfo
{
	optional uint32			PosX		= 1;
	optional uint32			PosY		= 2;
	optional uint32			WorldID		= 3;
	optional uint32			TempID		= 4;
};

message CMessageWarInfoNotify
{
	optional uint32			MapID		= 1;
	repeated NPCWarInfo		WarInfo		= 2;
	optional uint32			StoneID		= 3;
	optional uint32			StoneX		= 4;
	optional uint32			StoneY		= 5;
};

message CMessageQueryWarAwardRequest
{
	optional uint32			CharID			= 1;
	optional uint32			WarSerial		= 2;
};

message CMessageQueryWarAwardResponse
{
	optional uint32			CharID		= 1;
	optional uint32			Result		= 2;
	optional uint32			WinMoney	= 3;
	optional uint32			BestMoney	= 4;
	repeated uint32			WinItem		= 5;
	optional uint32			Rank		= 6;
};

message CMessageWarHonorNotify
{
	optional uint32			TotalHonor		= 1;		// �ܼ�ս��
	optional uint32			FreeHonor		= 2;		// ��ǰս��
	optional uint32			WarHonor		= 3;		// ����ս��
};

message CMessageWarCampNotify
{
	repeated uint32			WorldID		= 1;		// ��ӪID
	repeated uint32			CampID		= 2;		// ��Ӧ��ս��ID
	repeated uint32			Money		= 3;		// Ǯ
	repeated uint32			BidCampID	= 4;		// ���۵�ս��ID
};

message CMessageModifyRateRequest
{
	optional uint32			RateOrder		= 1;
	optional uint32			CharID			= 2;
	optional uint32			NPCEntityID		= 3;
};

message CMessageModifyRateResponse
{
	optional uint32			RateOrder		= 1;
	optional uint32			Result			= 2;
	optional uint32			CharID			= 3;
};

message CMessageModifyRateNotify
{
	optional uint32			Rate			= 1;
	optional string			Name			= 2;
	optional uint32			Real			= 3;
	optional uint32			WinWorld		= 4;
};

message CMessageGetTaxRequest
{
	optional uint32			CharID			= 1;
	optional uint32			Query			= 2;		// �Ƿ��ѯ��Ǯ
	optional uint32			NPCEntityID		= 3;
};

message CMessageGetTaxResponse
{
	optional uint32			Money			= 1;
	optional uint32			Result			= 2;
	optional uint32			CharID			= 3;
	optional uint32			Query			= 4;		// �Ƿ��ѯ��Ǯ
};

message CMessageQueryStoneNotify
{
	optional uint32			StoneID			= 1;
	optional uint32			StoneX			= 2;
	optional uint32			StoneY			= 3;
};

message CMessageRefuseSummonRequest
{
	optional uint32			AsynTeleTokenID	= 1;
	optional uint32			SrcCharID		= 2;
	optional uint32			DesCharID		= 3;
};

message CMessageRefuseSummonNotify
{
	optional string			SrcName			= 1;		// �ܾ���
	optional string			DesName			= 2;		// ���ܾ�����
	optional uint32			SrcCharID		= 3;
	optional uint32			DesCharID		= 4;
};


// ������Ӫͳ����Ϣ
message PBCampWeakForceInfo
{
	optional uint32 camp_id				= 1;	// ��ӪID
	optional uint32 level_score			= 2;	// �ȼ�����
	optional uint32 honer_score			= 3;	// ��������
	optional uint32 total_score			= 4;	// �ܷ�
	optional uint32 weak_level			= 5;	// ��Ӫ�ȼ�
};

// ������Ӫ�б��ѯ
message CMessageCampWeakListRequest
{
	
};

// ������Ӫ�б�ظ�
message CMessageCampWeakListResponse
{
	optional uint32 errcode					= 1;	//���������
	repeated PBCampWeakForceInfo camp_info	= 2;	//������Ӫ�б�
};

// ��ȡ������Ӫ��������
message CMessageCampGetAwardRequest
{
	optional uint32 npc_entity_id			= 1;
	optional uint32 award_type				= 2;
};

// ��ȡ������Ӫ�����ظ�
message CMessageCampGetAwardResponse
{
	optional uint32 errcode					= 1;	//���������
};

message CMessageAccuseKingRequest
{
	optional uint32	AccuseResult			= 1;	// ���� = 1, ������ = 2, ��Ȩ= 0
	optional uint32 WorldID					= 2;
	optional uint32 CharID					= 3;
};

message CMessageAccuseKingResponse
{
	optional uint32	ResponseResult			= 1;	// ���������
	optional uint32	AccuseResult			= 2;	// ������ͶƱ
	optional uint32	CharID					= 3;
};

message CMessageAccuseKingNotify
{
	optional string KingName				= 1;	// ������������
	optional uint32	CharID					= 2;
};

message CMessageAccuseStatusNotify
{
	optional string KingName				= 1;	// ������������
	optional uint32 YesNum					= 2;	// ��������
	optional uint32	NoNum					= 3;	// ����������
	optional uint32	AbortNum				= 4;	// ��Ȩ����
	optional uint32	CharID					= 5;
};

message CMessagePowerInfoRequest
{
	optional uint32	CharID					= 1;
};

message PowerInfo
{
	optional uint32 PowerType				= 1;	// ��������
	optional uint32	World					= 2;	// �Է���Ӫ
	optional uint32	ChangeType				= 3;	// �ı�����
	optional uint32 ChangeValue				= 4;	// �ı�ֵ
	optional uint32 Time					= 5;	// ʱ��
};

message CMessagePowerInfoResponse
{
	repeated PowerInfo	PowerHistory		= 1;	// ������¼
	optional uint32		PowerAdd			= 2;	// ��������
	optional uint32		PowerDel			= 3;	// ���ռ���
	optional uint32		Result				= 4;	// ���
	optional uint32		CharID				= 5;
};

message CMessageMakeGuoTanNotify
{
	optional uint32		SrcWorldID			= 1;	// ������Ӫ
	optional uint32		DesWorldID			= 2;	// �Է���Ӫ
	optional uint32		TargetTime			= 3;	// ����ʱ�䣬0��ʾ�Ѿ�����
	optional string		KingName			= 4;	// ��������
};

message CMessageMakeLuanWuNotify
{
	optional uint32		SrcWorldID			= 1;	// ������Ӫ
	optional uint32		DesWorldID			= 2;	// �Է���Ӫ
	optional uint32		TargetTime			= 3;	// ����ʱ�䣬0��ʾ�Ѿ�����
	optional string		KingName			= 4;	// ��������
};