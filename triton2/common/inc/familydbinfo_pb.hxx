
// ������ٶ�����/������
option optimize_for = SPEED;				

// �����б���Ϣ
message ApplyInfo								
{		
	optional string PlayerName			 = 		1; 
	optional uint32 PlayerLevel			 = 		2; 	
	optional uint32 FaceType			 = 		3; 
	optional uint32 LineID				 = 		4; 		
	optional uint32 PlayerCharID		 = 		5; 	
	optional uint32 PlayerOnLine		 = 		6; 
	optional uint32 PlayerMetier		 = 		7; 
	optional uint32 MapID				 = 		8; 
	optional uint32 PlayerSex			 = 		9; 
};

// �����б�������Ϣ
message PBApplyList
{
	repeated ApplyInfo	  ApplyData	   = 		1; 
};

// ������Ϣ
message FamilyData
{ 
	optional string FamilyName			 = 		1; 			// ��������
	optional uint32 FamilyID			 = 		2; 			// ����ID
	optional string HeaderName			 = 		3; 			// ����������
	optional uint32	HeaderRoleID		 = 		4; 			// �����Ľ�ɫID
	optional uint32 MemberNum			 = 		5; 			// ��Ա����
	optional uint32	FamilyLevel			 = 		6; 			// ����ȼ�
	optional uint32	FamilyGlory			 =		7;			// ��������
	optional uint32 FamilyDevelop		 =		8;			// ���巢չ��	
		
	optional uint32 NpcID				 =		9;			// ����ռ��/���۵�NPCID
	optional uint32 BidMoney			 =		10;			// ���徺�۵�Ǯ��
	optional uint32	BidTime				 =		11;			// ���徺�۵�ʱ��
	optional uint32 WarNpcStatus		 =		12;			// ս��npc��״̬0��ʾ�Ѿ�ռ��1��ʾ�������ᵱ��		
	optional uint32 WarRank				 =		13;			// ����վ�ۺ�����
	optional uint32	WarWinNum			 =		14;			// ����ս��ʤ������
	optional uint32	WarLostNum			 =		15;			// ����ս��ʧ�ܴ���
	optional uint32	FamilyStarLevel		 =		16;			// �����Ǽ�
	optional uint32	WarExp				 =		17;			// ����ս������
	optional uint32 WarMaxExp			 =		18;			// ����ս���������ֵ
	optional string EnemyFamilyName		 =		19;			// ��ս��������	
	optional uint32	WarStatus			 =		20;			// ս��״̬
	optional uint32 FamilyNpcNum		 =		21;			// ����npc����
	optional uint32	MaxMemberNum		 =		22;			// ����˿�����
	optional string	CorpsName			 =		23;			// �������ŵ�����		
};

// ������Ϣ�б�
message PBFamilyList
{
	repeated FamilyData	   FamilyInfo  = 		1; 
};


// �����Ա��Ϣ
message FamilyMemberInfo
{
	optional uint32 FaceID				 = 		1; 		// ����
	optional uint32 LineID				 = 		2; 		// ������ڵĹ���ID
	optional uint32	PlayerLevel			 = 		3; 		// ��ҵȼ�
	optional uint32	PlayerPost			 = 		4; 		// ���ְλ	
	optional uint32 PlayerCharID		 = 		5; 		// ��ҽ�ɫID
	optional uint32 RoleSex				 = 		6; 		// ��ɫ�Ա�
	optional string PlayerName			 = 		7; 		// �������
	optional uint32 MetierID			 = 		8; 		// ְҵID
	optional uint32 Online				 = 		9; 		// 1��ʾ����,0��ʾ������
	optional uint32 MapID				 = 		10; 	// ������ڵĵ�ͼID 
	optional uint32	FamilyWar			 =		11;		// �Ƿ�μӼ���ս
	optional uint32	Contribute			 =		12;		// ���˹��׶�
	optional uint32	CorpsContribute		 =		13;		// ���˶Ծ��ŵĹ��׶�
	optional uint32	CorpsWar			 =		14;		// �Ƿ�μӾ���ս
	optional string	CorpsTitle			 =		15;		// ���ųƺ�
};		  

// �����Ա��Ϣ�б�
message PBFamilyMemberList
{
	repeated FamilyMemberInfo Members  = 		1;   	
};						


// �����ְ��Ϣ
message PBFamilyOrganInfo
{
	optional uint32 Rights		 = 		1; 		// Ȩ��
	optional string OrganName    = 		2; 		// ��ְ����
	optional uint32 ID			 = 		3; 		// ��ְID
};

// ��ְ��Ϣ�б�
message PBFamilyOrganList
{ 
	repeated PBFamilyOrganInfo 	Organes  = 		1;  // ְλ��Ϣ�б�
};	


// �������ԵĻ�����Ϣ
message PBFamilyPropery
{	
	optional uint32 FamilyHeaderID		 = 		1; 
	optional uint32 FamilyMoney			 = 		2; 
	optional uint32 FamilyLevel			 = 		3; 
	optional string FamilyNotice		 = 		4; 
	optional string FamilyHeaderName	 = 		5;   
	optional uint32 MemberNum			 = 		6; 
	optional uint32 FamilyID			 = 		7;	  
	optional uint32 NpcID				 =		8;			
	optional uint32 BidMoney			 =		9;			
	optional uint32	BidTime				 =		10;	
	optional uint32 WarNpc				 =		11;		// ս��npc��id
	optional uint32 WarNpcStatus		 =		12;		// ս��npc��״̬0��ʾ�Ѿ�ռ��1��ʾ�������ᵱ��		
	optional uint32 WarRank				 =		13;		// ����վ�ۺ�����
	optional uint32	WarWinNum			 =		14;		// ����ս��ʤ������
	optional uint32	WarLostNum			 =		15;		// ����ս��ʧ�ܴ���
	optional uint32	FamilyStarLevel		 =		16;		// �����Ǽ�
	optional uint32	WarExp				 =		17;		// ����ս������
	optional uint32 WarMaxExp			 =		18;		// ����ս���������ֵ
	optional string EnemyFamilyName		 =		19;		// ��ս��������
	repeated uint32	TaskID				 =		20;		// ���������б�	
	optional uint32	FamilyGlory			 =		21;		// ��������
	optional uint32 FamilyDevelop		 =		22;		// ���巢չ��
	optional uint32	WarStatus			 =		23;		// ս��״̬	
	
	optional uint32	ChallengeStatus		 =		24;			// ��ս�����״̬
	optional uint32	ChallengeMoney		 =		25;			// ��ս���
	optional string	ChallengeStarted	 =		26;			// ����������ս
	optional string ChallengeReceived	 =		27;			// ����յ�����ս
	optional uint32	MaxMemberNum		 =		28;			// ����˿�����
	optional uint32	CanLevelUp			 =		29;			// �Ƿ��������	
	
	optional uint32	MaxPresbyterNum		 =		30;			// ���峤������
	optional uint32	GloryLimit			 =		31;			// ��ǰ�ȼ��¼��徭������			
	optional uint32	LevelMoney			 =		32;			// ���������Ǯ
	optional uint32	Stability			 =		33;			// ���尲����
	optional uint32	ReduceStability		 =		34;			// ÿ��˥���İ�����	
	optional uint32	ExtraRedstonExp		 =		35;			// �����ڵ����⾭��ӳ�	
};

// �����Ա��Ϣ(���ݿ�洢)
message PBFamilyMemberInfo
{
	optional uint32 RoleID				=	1;	// ��ɫID
	optional uint32 FamilyPost			=	2;	// ����ְλID
	optional uint32	FamilyContribute	=	3;	// ���幱�׶�
	optional uint32	CorpsContribute		=	4;	// ���Ź��׶� 
	optional uint32 CorpsPost			=	5;	// ����ְλID	
	optional string	CorpsTitle			=	6;	// ���ųƺ�
};

// ������Ϣ��Ա�б�(���ݿ�洢)
message PBFamilyMemberInfoList
{
	repeated PBFamilyMemberInfo MemberInfo  = 		1;  
}; 

// ��������̵����Ʒ��Ϣ
message PBGoodItemInfo
{
	optional uint32		ItemID			= 1;
	optional uint32		ItemNum			= 2;
	optional uint32		ComposeID		= 3;
	optional uint32		PurcharseTime	= 4;
};

// �������ĳ���̵����Ʒ��Ϣ
message PBLeagueShopInfo
{
	optional uint32		ShopID			= 1;
	optional uint32		ShopType		= 2;
	repeated PBGoodItemInfo	ItemInfo	= 3;			
};

// ������������̵����Ϣ
message PBLeagueShopsListInfo
{
	repeated PBLeagueShopInfo LeagueShopInfo = 1;	// �����̵����	
};
