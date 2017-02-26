// ������ٶ�����/������
import "familydbinfo_pb.hxx";
option optimize_for = SPEED;


// ������ϸ������Ϣ(���ų�Ա�ɼ�)
message CorpsProperty
{
	optional uint32 CorpsMoney			 = 		1; 	// ���Ž�Ǯ
	optional string CorpsRooterName		 = 		2; 	// ������������
	optional uint32 CorpsFamilyNum		 = 		3; 	// ���ż�������
	optional uint32 CorpsLevel			 = 		4; 	// ���ŵȼ�
	optional string CorpsButtullin		 = 		5; 	// ���Ź���
	optional uint32 CorpsMemberNum		 = 		6; 	// ���ų�Ա����
	optional uint32	CorpsRooterID		 = 		7; 	// ���������ɫID
	optional uint32 CorpsID				 = 		8; 	// ����ID
	optional string CorpsName			 = 		9; 	// ��������	 
	optional uint32	CorpsGlory			 =		10;	// ��������
	optional uint32 CorpsDevelop		 =		11;	// ���ŷ�չ��	
	
	optional uint32 WarRank				 =		12;			// ����ս�ۺ�����
	optional uint32	WarWinNum			 =		13;			// ����ս��ʤ������
	optional uint32	WarLostNum			 =		14;			// ����ս��ʧ�ܴ���
	optional uint32	FamilyStarLevel		 =		15;			// �����Ǽ�
	optional uint32	WarExp				 =		16;			// ����ս������
	optional uint32 WarMaxExp			 =		17;			// ����ս���������ֵ
	optional uint32	MaxFamilyNum		 =		18;			// ����������	    
	optional uint32	CanLevelUp			 =		19;			// �Ƿ�������� 
	optional uint32	ChallengeStatus		 =		20;			// ��ս״̬
	optional uint32	ChallengeMoney		 =		21;			// ��ս��Ǯ	
	optional uint32	MaxGeneralNum		 =		22;			// ǰ�潫�����������
	optional uint32	MaxCounsellorNum	 =		23;			// ���ž�ʦ���������      

	repeated PBCorpsBattle	BattleInfo	 =		24;			// ����ս����Ϣ
	optional uint32	CountryID			 =		25;			// ������������ID	

	optional uint32	Color				 =		26;			// ������ɫ
	optional uint32	MainCityMap			 =		27;			// ���ǵ�ͼID
	optional uint32	LevelGlory		 =		29;			// ��ǰ�ȼ���������Ҫ�ľ��ž���
	optional uint32	LevleMoney		 =		30;			// ��ǰ�ȼ���������Ҫ�ľ��Ž�Ǯ
	optional uint32 BOSSRefineValue		 =		31;		// ���ŵ�����ֵ
	optional uint32	RefineValue			 =		32;		// ����ֵ����
	repeated PBCorpsBoss BossList	 =		33;		// boss�б�
	optional uint32 BossCDLimit			= 34;				//boss��cdʱ��
	optional uint32 BossCDCool			= 35;			//boss��Ҫ��ȴ��cd
	optional uint32 BossRepetionOpen	= 36;			// 1 open ,0 not open 
	optional uint32 CorpsCurBossID			= 37;					//��ǰ�ٻ���boss id
	optional uint32	CorpsBossScore			= 38;		//	����boss����
	optional uint32 CorpsCollectActive		= 39;		// ���Ųɼ���Ծ��
	optional uint32 CorpsReptionOpenTime	= 40;		// ����boss��������ʱ��
};

// ����ս��Ϣ�ṹ
message PBCorpsBattle
{
	optional uint32	NpcID			= 1;	// ����NPC
	optional uint32	NpcStatus		= 2;	// NPC״̬
	optional uint32 WarStatus		= 3;	// ս��״̬
	optional string	DesCorpsName	= 4;	// ��ս��������
	optional uint32	Type			= 5;	// ����ս��Ұ��ս
	optional uint32	BidMoney		= 6;	// ���۽�Ǯ
	optional uint32 DesCorpsID		= 7;	// ��ս����ID
	optional uint32	MapID			= 8;	// ��ͼID
	optional uint32 Time			= 9;	// ռ��ʱ��
	optional uint32	CorpsID			= 10;	// ռ�����ID
	optional string CorpsName		= 11;	// ռ���������
	optional string RooterName		= 12;	// ���Ŵ󽫾�
};

// ����BOSS��Ϣ
message PBCorpsBoss
{
	optional uint32 BossId			= 1;	//boss id
	optional uint32 CanIntoTimes	= 2;	//�ɽ������
};

// ս����Ϣ�б�
message PBCorpsBattleList
{
	repeated PBCorpsBattle BattleList = 1;
};


// ���ŵĳ�Ա��Ϣ
message PBCorpsMember
{
	optional PBFamilyMemberList		FamilyMemberList 	 = 		1;
	optional FamilyData				FamilyProperty		 = 		2; 
};

// ���ŵ����г�Ա��Ϣ
message PBCorpsMemberList
{
	repeated PBCorpsMember CorpsMemberList  = 		1; 
}; 


// ���ŵ�������Ϣ�б�
message PBCorpsApplyList
{
	repeated FamilyData ApplyList  = 		1; 
};


// ���ŵĻ�����Ϣ
message PBCorpsBasicInfo
{		
	optional uint32 CorpsMemberNum		 = 		1; 	// ���ų�Ա����
	optional uint32 CorpsFamilyNum		 = 		2; 	// ���ż�������
	optional uint32 CorpsID				 = 		3; 	// ����ID
	optional uint32 CorpsMoney			 = 		4; 	// ���Ž�Ǯ	  	
	optional string CorpsRooterName		 = 		5; 	// ������������
	optional uint32	CorpsRooterID		 = 		6; 	// ��������ID  
	optional uint32 CorpsLevel			 = 		7; 	// ���ŵȼ�
	optional string CorpsName			 = 		8; 	// ��������	
	optional uint32	CorpsGlory			 =		9;	// ��������
	optional uint32 CorpsDevelop		 =		10;	// ���ŷ�չ��	
	optional uint32	MaxFamilyNum		 =		11;	// ����������	
	optional uint32	CorpsStarLevel		 =		12;	// ���ŵ��Ǽ�       
	optional uint32	MainCityMap			 =		13;	// ���ǵ�ͼID	
};

// ������Ϣ�б�
message CorpsInfoList
{	
	repeated PBCorpsBasicInfo CorpsList  = 		1; 
};	


// ���ŵļ����Ա��Ϣ
message PBCorpsFamilyInfo
{
	optional uint32 Contribute  = 		1; 	
	optional uint32 FamilyID    = 		2; 	
};

// ���ŵļ����Ա��Ϣ�б�
message PBCorpsFamilyInfoList
{
	repeated PBCorpsFamilyInfo FamilyInfo  = 		1; 
};

// ����������Ϣ
message PBUnionBasicInfo
{
	optional uint32 UnionID			 = 		1; 	// ����ID	
	optional string UnionName		 = 		2; 	// ��������	
	optional uint32 CoreID			 =		3;	// ������ID
	optional string CoreName		 =		4;	// ������ID
	optional string RooterName		 = 		5; 	// ������������
	optional uint32	RooterID		 = 		6; 	// ��������ID  	
	optional uint32 CityID			 =		7;	// ����ID
	optional uint32	CorpsNum		 =		8;	// ������
	optional uint32	MemberNum		 =		9;	// �˿���
	repeated uint32	MapID			 =		10;	// ��ͼ��
	optional uint32	Money			 =		11;	// ��Ǯ
};

//  ���񷢲���Ϣ
message PBTaskListInfo
{
	optional uint32 TaskID			 = 		1; 	// ����ID	
	optional uint32 TaskState		 = 		2; 	// ����״̬	
	optional uint32 EntityID		 = 		3; 	// ������
};


// ���ŷ�����Ϣ
message PBCorpsPublishInfo
{
	optional uint32 TodayTimes		= 		1; 	// �����
	optional uint32 WeekTimes		= 		2; 	// �ܴ���
	repeated PBTaskListInfo TaskList= 		3; 	// �����б�
};
