/******************************************************************************
	��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

******************************************************************************
	�ļ���		: property_pb.hxx
	�汾��		: 1.0
	����		: ZHL
	��������	: 2008-09-10
	����޸�	: 
	��������	: 1 - �������Զ�Ӧ��PB��ʽ���壬ԭ������proclient_svr.h������ģ�飬��taskmodule.h��
				: 2 - �����ǽ�����������PB��ʽ�浽���ݿ��е�Blob�ֶ��
				: 3 - ���ļ��Ժ��ǰ汾���Ƶĺ����ļ���Ҳ�����ݿ���Blob�ֶ�ǿ���������ߵĻ�����
				: 4 - ÿ���ֶ�һ��Ҫע����ϸ
				: 5 - �ֶ�ֻ�����ӣ�����ɾ����ɾ�����ֶ�Ҫ���ϰ汾��
				: [ע] PB ȫ��[Protocal Buffers -- google����Э��]
	�����б�	: 
	�޸���ʷ	: 
		1 ����	: 2008-09-10
		����	: ZHL
		�޸�����: ����
*******************************************************************************/


/****************************	�ֶ�����   ************************************
*
*	required: ���븳ֵ���ֶΣ�һ��Ҫ����˲�������������
*	optional: ���п��޵��ֶ�
*	repeated: ���ظ��ֶ�(�䳤�ֶ�)
*
******************************************************************************/


/***************************   �������� ***************************************
*	double
*	float
*	int32		Uses variable-length encoding. Inefficient for encoding negative numbers 
*				�C if your field is likely to have negative values, use sint32 instead. 
*	int64		Uses variable-length encoding. Inefficient for encoding negative numbers 
*				�C if your field is likely to have negative values, use sint64 instead. 
*	uint32		Uses variable-length encoding. 
*	uint64		Uses variable-length encoding. 
*	sint32		Uses variable-length encoding. 
*				Signed int value. These more efficiently encode negative numbers than regular int32s. 
*	sint64		Uses variable-length encoding. Signed int value.
*				These more efficiently encode negative numbers than regular int64s. 
*	fixed32		Always four bytes. More efficient than uint32 if values are often greater than 228. 
*	fixed64		Always eight bytes. More efficient than uint64 if values are often greater than 256. 
*	sfixed32	Always four bytes.  
*	sfixed64	Always eight bytes.
*	bool
*	string		A string must always contain UTF-8 encoded or 7-bit ASCII text.
*	bytes		May contain any arbitrary sequence of bytes.
*
*	ע�� PBû�ж���1Byte,2Byte�����ͣ�����4Byte��; ���ǻ�������ͷ�Χ��̬�����ֽ�����
*		
******************************************************************************/

// ������ٶ�����/������
option optimize_for = SPEED;

message PBPropertyValue1
{
	optional uint32		InitValue	= 1;
	optional uint32		DeltaValue	= 2;
};

// �������ܿ�
message PBSkillBox
{
	optional uint32			Skills			= 1;			// �Ѽ���� 0��ʾ�ǿռ��ܿ�
	optional uint32			SkillActNum		= 2;			// �Ѽ�������
	optional uint32			SkillBookID		= 3;			// ��ʹ�õļ�����
	optional uint32			AddedSkillPoints= 4;			// ��Ӧ�����Ѽӵļ��ܵ�
	optional uint32			SkillInitLevel  = 5;			// ��Ӧ���ܳ�ʼ�ȼ�
	optional uint32         ActiveState		= 6;			// ����״̬
};

/* ��Ʒͨ������
**
** ������Ʒ���л��󶼴��ͨ�õ�PB��ʽ��Ȼ���ٸ���ÿ����Ʒ�����ͣ���ȡPB�и���Ȥ����ֵ
** 
**/
message PBItemObject
{
	optional uint32			ItemID				= 1;			// ����ID
	optional uint32			Number				= 2;			// ��������
	optional uint32			Index				= 3;			// �����ڰ����е�����
	optional uint32			InvalidTime			= 4;			// ����ʱ��
	optional uint32			Cooldown			= 5;			// ��ȴʱ��
	optional uint32         BindStatus			= 6;			// ��Ʒ��״̬
	optional uint64			ObjGuID				= 7;			// ����ʱ��Ψһ��ʶ
	optional uint32		    UsedTimes			= 8;			// ��ʹ�ô���
	optional PBItemContent	ItemContent			= 9;			// ��Ʒ����
	optional uint64         PurchaseID			= 10;           // ������Ʒʱ��Ľ���ID
	optional string			GroomName			= 11;			// ��������
	optional string			BrideName			= 12;			// ��������
	optional uint32			WeddingTime			= 13;			// ����ʱ��
	optional uint32			WeddingTimeLength	= 14;			// ����	  	
};

/* ��Ʒ����
** һ�������һ����Ʒ�������������е�һ�֣�������Ʒ���ܻ�ͬʱ�ж�������
**/
message PBItemContent
{
	optional uint32			RemainHP		= 1;			// ʣ��HP
	optional uint32			RemainMP		= 2;			// ʣ��MP
	optional uint32			RemainAP		= 3;			// ʣ��AP
	optional uint32			Current			= 4;			// ��ǰ�洢��Ԫ��
	repeated PBTelePostion  TelePos			= 5;			// ������Ϣ(��ͨ������Ʒֻ����һ���㣻��������Ʒ�����ж�����͵�)
	optional PBItemObjMW	ItemMW			= 6;			// ����Ƿ��� ��������ֶ�
	optional PBItemObjEquip ItemEquip		= 7;			// �����װ�� ��������ֶ�
	optional uint32			LeftOffLineTime	= 8;			// �ڹ�����õ�ʣ������ʱ��		
	optional uint32			Exp				= 9;			// �������鵤�ľ���
};

// װ��
message PBItemObjEquip
{
	repeated uint32			SlotProperty	= 1;			// װ�����Բ��Ƿ�򿪣�0δ����1��
	repeated uint32			Property		= 2;			// ��������ID,0��ʾû�и�������
	repeated uint32			SlotValue		= 3;			// װ�����Բ۵ı�ʯID
	optional uint32			Level			= 4;			// װ���ȼ�
	optional uint32			SlotNumber		= 5;			// �򿪵�װ�����Բ۸���	
	optional uint32			NameLength		= 6;			// ���������ֳ���
	optional string			Name			= 7;			// ����������
	optional uint32			SlotSpell		= 8;			// ��Ƕ�ķ���
	optional uint32         Durability      = 9;           // װ���;ö�	
	optional PBPropertyValue1 MaxSlotNumber	= 10;			// ���ɵ�������
	repeated uint32			Judge			= 11;			// �Ѽ����ı���������ֵ
	optional uint32			ResDef			= 12;			// �������
	optional uint32			ResAtt			= 13;			// ���Թ������
	optional uint32			DefLevel		= 14;			// ���Եȼ�
	optional uint32			AttLevel		= 15;			// ���Թ����ȼ�
	optional uint32			MagicStoneID	= 16;			// װ����ħʯID
	optional uint32			MagicStoneNum	= 17;			// ��ħ����
	optional uint32         BindFreeTime    = 18;			// ��Ʒ�ֶ��󶨽��ʱ��
	optional uint32			SpouseID		= 19;			// ��żID
	optional string			SpouseName		= 20;			// ��ż����
	optional uint32			ExtraType		= 21;			// ��������
	optional uint32			BindTime		= 22;			// װ����ͨ��ʱ��
};

// ��������
message PBItemObjMW
{
	optional uint32         MWLevel					= 1;			// �����ȼ�
	optional uint64         Exp						= 2;			// ��������
	optional uint32         Mp						= 3;			// ����ֵ
	optional uint32         Hp						= 4;			// ����ֵ
	optional uint32         CurKeenpoints			= 5;			// ��ǰ����
	optional uint32         CurCalmpoints			= 6;			// ��ǰ����
	optional uint32         CurMagicpoints			= 7;			// ��ǰ����
	optional uint32         CurBierpoints			= 8;			// ��ǰ����
	optional uint32         CurImmortalpoints		= 9;			// ��ǰ����
	optional uint32         LeftPoints				= 10;			// ��ǰʣ��Ǳ�ܵ�
	optional uint32         ProBase					= 11;			// ���Ի���ֵ
	optional uint32         ProUp					= 12;			// ���Գɳ�ֵ
	optional uint32         ProEff					= 13;			// ����Ӱ���
	optional uint32         ProSpir					= 14;			// ����
	optional uint32         ProcessVal				= 15;			// ��ǰ����ֵ
	optional uint32         LeftSkillPoints			= 16;			// ��ǰʣ�༼�ܵ�
	optional uint32         MaxMp					= 17;			// ����ֵ����
	optional uint32         MaxHp					= 18;			// ����ֵ����
	optional uint32         IncMp					= 19;			// ����ֵÿ�λָ�����
	optional uint32         IncHp					= 20;			// ����ֵÿ�λָ�����
	repeated PBSkillBox		SkillBox				= 21;			// �������ܿ����(ֻ���Ѽ���ļ��ܿ�)
	optional uint32         AddKeenpoints			= 22;
	optional uint32         AddCalmpoints			= 23;
	optional uint32         AddMagicpoints			= 24;
	optional uint32         AddBierpoints			= 25;
	optional uint32         AddImmortalpoints		= 26;
	optional PBSkillList    SkillList				= 27;
	optional uint32			JudgeFlag				= 28;		// ���Լ�����־ 0=δ����
	optional uint32			ExtraKeenpoints			= 29;	
	optional uint32			ExtraCalmpoints			= 30;	
	optional uint32			ExtraMagicpoints		= 31;	
	optional uint32			ExtraBierpoints			= 32;	
	optional uint32			ExtraImmortalpoints		= 33;
	repeated uint32			PlayerAddPointLastLevel	= 34;	// ��Ҽӵ㱸��
	optional uint32			LeftPointsLastLevel		= 35;	// ��������ǰ��ҵ�ʣ��Ǳ�ܵ�
	optional uint32			NewAddPoints			= 36;	// ���������¼ӵ�Ǳ�ܵ�
	optional uint32			NewAddSkillPoints		= 37;	// ���������¼ӵļ��ܵ�
	optional uint32			StepClearState			= 38;	// ���Сϴ״̬
	optional uint32			LastAddedSkillBoxIndex	= 39;	// �ϴμ��ܼӵ�ļ��ܿ�����
	optional uint32			LastLevelProcessVal		= 40;	// ����ֵ����
	optional uint32			NextActBoxIndex			= 41;	// ��һ����������ļ��ܿ�
	optional uint32			LastLevelNextActBox		= 42;	// ��һ����������ļ��ܿ� ��������
	optional uint32			QLTempID				= 43;	// ӡ����ȥ������ID
};

// CItemBox
message PBItemBox
{
	optional uint32			ReleaseIndex	= 1;			// ��ǰ�ͷŵ��ĸ�����
	repeated PBItemObject	ItemObjects		= 2;			// 255����Ʒ
	repeated PBItemObject	KitBag			= 3;			// ��չ��
	repeated uint32			KitLocked		= 4;			// ��λ�Ƿ�����
};

message PBTransform
{
	optional uint32			HasTransform	= 1; // �Ƿ���ڱ���״̬
	optional uint32			Sex				= 2;
	optional uint32			StateID			= 3;
	optional uint32			WeaponID		= 4;
	optional uint32			ClothID			= 5;
	optional uint32			FashionID		= 6;
	optional uint32			NpcID			= 7;
};

// CBuffObject
message PBBuffObject
{
	optional uint32			BuffID			= 1;			// Buffģ��ID
	optional uint64			PersistTime		= 2;			// Buff����ʱ�䣨����Ϊ��λ��
	optional uint32			SrcEntityID		= 3;			// �ͷ���ID
	optional uint32			TimerType		= 4;			// ʱ������
	optional uint32			LastInterval	= 5;			// �ϴ�ʱ����
	repeated uint32			Parames			= 6;			// ��չ����
	repeated uint32			Parames2		= 7;			// ��չ����2
	optional uint32			BackDamage		= 8;			// �����˺�������
	optional uint32			ListID			= 9;
	optional uint32			SuperCount		= 10;			// Buff���Ӵ���( ֻ��ʱ������Buff��Ч�� )
};

// CBuffList
message PBBuffList
{
	optional uint32			BuffNumber		= 1;			// Buff����
	repeated PBBuffObject	BuffObjects		= 2;			// BUFF�б�
	optional PBTransform	Transform		= 3;			// ����״̬
};

message PBStateParam
{
	optional uint32			StateType		= 1;			// ״̬����ID(��Ϊ�����±�ʹ��)
	optional uint32			From			= 2;
	optional uint32			Index			= 3;
	optional uint32			Parames1		= 4;
	optional uint32			Parames2		= 5;
	optional uint32			InState			= 6;			// �Ƿ��ڸ�״̬
	optional fixed32		BuffAdd			= 7;
};

message PBStateList
{
	repeated PBStateParam	StateParamObj	= 1;
};

// CSkillObject
message PBSkillObject
{
	optional uint32			SkillID			= 1;			// ����ģ��ID
	optional uint32			SkillLevel		= 2;			// ���ܵȼ�
	optional uint32			Cooldown		= 3;			// ������ȴʱ��, 0��ʾĿǰ���ܿ���ʹ��
	optional uint32			IncLevel		= 4;			// ���ӵļ��ܵȼ�
};

// CSkillList
message PBSkillList
{
	optional uint32			SkillNumber		= 1;			// ���ܸ���
	repeated PBSkillObject	SkillObjects	= 2;			// �����б�
};

// CShortcut
message PBShortcut
{
	optional uint32			Shortcut		= 1;
	optional uint32			mType			= 2;
	optional uint32			mIndex			= 3;
	optional uint32			mLabelType		= 4;
	optional uint32			mLabelIndex		= 5;
	optional uint32			Param1			= 6; 
};

// CShortcutList
message PBShortcutList
{
	optional uint32			ShortcutNumber	= 1;
	repeated PBShortcut		Shortcuts		= 2;			// ��ݼ��б�
	repeated uint32			HelpStatus		= 3;			// ����ָ���Ķ���״̬,ÿһλ��ʾһ��״̬
};

message PBKillData
{
	optional uint32			KillID			= 1;			// ɱ���ߵ�ID
	optional uint32			KillTime		= 2;			// ɱ����ʱ��
};

message PBWizard
{
	repeated uint32			WizardPoint		= 1;			// �Ż��ȼ�
	repeated uint32			WizardValue		= 2;			// �Ż�ֵ
	repeated uint32			WizardSubmit	= 3;			// �Ż��ύ��
	repeated uint32			WizardIncrease	= 4;			// �Ż��ӵ�
	optional uint32			Trend			= 5;			// �ɳ�����
	optional uint32			CombatFame		= 6;			
	optional uint32			RepeFame		= 7;
	optional uint32			CommonFame		= 8;
	optional uint32			CombatToday		= 9;
	optional uint32			RepeToday		= 10;
	optional uint32			CommonToday		= 11;
	optional uint32			CombatAll		= 12;
	optional uint32			RepeAll			= 13;
	optional uint32			CommonAll		= 14;
};

// �ɴ��͵���Ϣ
message PBTelePostion
{
	optional uint32			Line		= 1;			// ��ID
	optional uint32			Map			= 2;			// ��ͼID
	optional uint32			PosX		= 3;			// x����
	optional uint32			PosY		= 4;			// y����
};

// �����������
message PBPlayerBasicInfo
{
	optional uint32			Str				= 1;
	optional uint32			Sta				= 2;
	optional uint32			Spr				= 3;
	optional uint32			Con				= 4;
	optional uint32			Wis				= 5;
	optional uint32			RemainPoint		= 6;
	optional uint32			SkillPoint		= 7; // ���ܵ�
	optional uint32			ProLevel		= 8; // �����ȼ�
	optional uint32			ProExp			= 9; // ��������
	optional uint32         	ShowFashion     = 10; // ��ʾʱװ
    	optional uint32         	ShowEquip       = 11; // ��ʾװ��
};


// ��ħ־
message PBMonsterRecordInfo
{
	repeated uint32			ActiveCard		= 1;			// �Ѽ��Ƭ	
	repeated uint32			OwnCard			= 2;			// ���ռ���Ƭ
};

// ����������Ϣ
message PBPlayerMWInfo
{
	optional uint32			AssignExpScl	= 1;			// ��ҷ���������ľ���
};

// ������ȴ����Ϣ
message PBSingleCDGroup
{
	optional uint32			Index			= 1;			// ��ȴ������
	optional uint32			CDTime			= 2;			// CDʱ��
};

// ��ȴ��
message PBPlayerCDGroupInfo
{
	repeated PBSingleCDGroup		CDGroup			= 1;			// ��ȴ��
};

// ��¼������Ϣ
message PBTelePosInfo
{
	optional PBTelePostion	TownPos			= 1;			// �سǵ�
	repeated PBTelePostion	TeleList		= 2;			// ���е��߼�����б�
};

// ���PVP��Ϣ
message PBPlayerPVPInfo
{
	optional uint32			PKMode			= 1;			// PKģʽ
	optional uint32			PKValue			= 2;			// PKֵ
	optional uint32			KillNum			= 3;			// ɱ����
	optional uint32			Honor			= 4;			// ��ѫ
	optional uint32			InHonPerDay		= 5;			// ÿ���õĹ�ѫֵ
	optional uint32			OutHonPerDay	= 6;			// ÿ���ṩ�Ĺ�ѫ��
	repeated PBKillData		Kill			= 7;			// ɱ���ļ�¼
	optional uint32			KillNumIn		= 8;			// �ڹ��ڵ�ɱ����
	optional uint32			YellowStatus	= 9;			// ����
	optional uint32			PrisonTime		= 10;			// ����ʱ��
	optional uint32			TotalPrisonTime = 11;			// �����ܹ�ʱ��
	optional uint32			TodayHonor		= 12;			// ���չ�ѫ
	optional uint32			TotalWar		= 13;			// ��ս�ۼ�ս��
	optional uint32			TodayWar		= 14;			// ���ι�սս��
	optional uint32			TodayOther		= 15;			// ��������ս��
	optional uint32			FreeWar			= 16;			// �ۼƿ�֧��ս��
	optional uint32			WarSerial		= 17;			// ��ǰ��ս�ƴ�	
	optional uint32			WarKill			= 18;			// ��ǰ��ս��ɱ	
	optional uint32			ExpHonor		= 19;			// �����Ѷһ���������
	optional uint32			ItemHonor		= 20;			// �����Ѷһ���Ʒ����
};

// ���ͳ����Ϣ
message PBPlayerStatisticInfo
{
	optional uint32			CompletedTasks				= 1;	// ��ɵ�������
	optional uint32         OriginReliveTimes			= 2;	// ԭ�ظ������
	optional uint32         KillSameNationNum			= 3;	// ɱ����Ӫ����
	optional uint32         KillOgreNum					= 4;	// ɱ����
	optional uint32         UpFailNum					= 5;	// ����ʧ�ܴ���
	optional uint32         TodayKillEnemyIn			= 6;	// �ڹ��ڵ�ɱ����
	optional uint32         TodayKillEnemyOut			= 7;	// �ڹ����ɱ����	
	optional uint32			DieNum						= 8;	// ��������
};

// �컯
message PBPlayerTalentInfo
{
	optional uint32			TalentPoint		= 1;			// �컯��
	optional uint32			TalentStep		= 2;			// ��ǰ�컯С��
	optional uint32			TalentStudy		= 3;			// ��ǰС����Ͷ����컯��
	optional PBSkillList	TalentSkill		= 4;			// �컯����
	optional uint32			TalentExp		= 5;			// ��Ϊֵ
	optional uint32			TalentLevel		= 6;			// �컯��ȼ�
};

// �ƺ�ϵͳ
message PBPlayerTitleInfo
{
	optional uint32			CurrentTitle	= 1;			// ��ǰ�ƺ�
	repeated uint32			TitleList		= 2;			// �ƺ��б�
	optional PBSkillList	TitleSkill		= 3;			// �ƺż���
	repeated uint32			Time			= 4;			// ���ʱ�䡣titlelist �� time Ӧ�÷ŵ�һ���ṹ�壬 ��������Ϊ�˼���������
};

// �״̬
message PBActivityStateInf
{
	optional uint32			ActivityID					= 1;			// �ID
	optional uint32			CurState					= 2;			// ��ǰ״̬
	repeated uint32			StateParam					= 3;			// ״̬����
	optional uint32			ChgTm						= 4;			// ʱ���
	optional uint32			RealLastedTime				= 5;			// ��ʵ�ı�״̬����ʱ�� 
};

// ���Ϣ
message PBPlayerActivityInfo
{
	optional uint32			DiploidTime					= 1;			// ��˫ʱ��
	optional uint32			LastRefreshTimeOfDipLoid	= 2;			// ��Ч˫��ʱ��
	repeated uint32			DiploidState				= 3;			// ˫������״̬
	optional uint32			DailyWelfareSta				= 4;			// ÿ�ո�����״̬
	optional uint32			LastDaylyDisposTime			= 5;			// �ϴδ���ÿ�������ʱ��
	optional uint32			LastWeeklyDisposTime		= 6;			// �ϴδ���ÿ�������ʱ��
	optional uint32			LastFamilyApplyTime			= 7;			// ���һ�������������ʱ��
	optional uint32			LastTimeLeaveFamily			= 8;			// ���һ���뿪�����ʱ��
	optional uint32			LastJudgeTime				= 9;			// �ϴ�����ʱ��
	optional uint32			SaveDate					= 10;			// ĳЩ���Ե�ˢ��ʱ�䣬�磺������pvp�����Ϣ
	optional uint32			VipFlag						= 11;			// vip ��־
	optional uint32			VipTime						= 12;			// vip ��ֹ����
	optional PBAwardRecord	AwardRecord					= 13;			// ��ȡ��¼
	optional uint32			InvestStatus				= 14;			// �����ʾ��״̬
	optional PBAwardRecord	WeeklyAwardRecord			= 15;			// ������ȡ��¼	
	repeated PBActivityStateInf  ActivityState			= 16;			// �״̬
	optional uint32			HasVoted					= 17;			// ����ͶƱ��¼
	optional uint32			SaveTm						= 18;			// ����ʱ���	
};

// ������Ϣ�����ͻ�����)
message PBPlayerClientInfo
{
	optional PBShortcutList			Shortcut			= 1;			// [DB]��ҿ�ݼ��б�	
};

// һ��ϵ���������Ϣ
message PBSpiritTypeInfo
{
	repeated uint32 SlotOpenStatus		= 1;	// �Ƿ��ѿ���
	repeated uint32 CastingItemID		= 2;	// ����ʱʹ�õĵ��ߣ�O��ʾδ����
	repeated uint32 BindStatus			= 3;	// ������ߵİ�״̬��1��ʾ�󶨣�0��ʾ�ǰ� 
}

// һ����λ��������Ϣ
message PBSpiritPositionInfo
{
	repeated PBSpiritTypeInfo SpiritTypeInfo	= 1;	// ��ϵ����Ϣ
}

// ������Ϣ
message PBSpiritInfo
{
	repeated PBSpiritPositionInfo PositionInfo	= 1;	// ����λ��Ϣ 
}
/* CProperty
** ��Һ���������Ϣ,��Ϸ����Ҫ����Ϣ���ڴ�
** ���չ�������࣬�����պ���չ
** ����жԴ˽��иĶ���������ؿ������������ӣ�����ֻ�ܼӲ���ɾ
*/
message	PBProperty
{
	optional uint32					CurHP				= 1;			// [DB]��ǰHP
	optional uint32					CurMP				= 2;			// [DB]��ǰMP
	optional uint32					CurAP				= 3;			// [DB]��ǰAP
	optional PBPlayerBasicInfo		BasicInfo			= 4;			// [DB]������Ϣ
	optional PBItemBox				Baggage				= 5;			// [DB]��Ұ���
	optional PBItemBox				TaskBaggage			= 6;			// [DB]����������
	optional PBItemBox				Equipment			= 7;			// [DB]���װ��
	optional PBItemBox				Storage				= 8;			// [DB]��Ҳֿ�
	optional PBSkillList			Skill				= 9;			// [DB]��Ҽ����б�
	optional PBBuffList				Buff				= 10;			// [DB]���buff�б�
	optional PBPlayerCDGroupInfo	CDGroup				= 11;			// [DB]CD��
	optional PBMonsterRecordInfo	MonsterRecord		= 12;			// [DB]��ħ־��Ϣ
	optional PBTelePosInfo			TelePos				= 13;			// [DB]�ɴ��͵���Ϣ
	optional PBPlayerPVPInfo		PvPInfo				= 14;			// [DB]PVP��Ϣ
	optional PBPlayerTitleInfo		TitleInfo			= 15;			// [DB]�ƺ���Ϣ
	optional PBPlayerTalentInfo		TalentInfo			= 16;			// [DB]�컯��Ϣ
	optional PBPlayerMWInfo			MWInfo				= 17;			// [DB]������Ϣ
	optional PBLifeSkillBox			LifeSkillBox		= 18;			// [DB]�����
	optional PBPlayerStatisticInfo	StatisticInfo		= 19;			// [DB]ͳ����Ϣ
	optional PBPlayerClientInfo		ClientInfo			= 20;			// [DB]�ͻ��ȶ�����Ϣ
	optional PBWizard				Wizard				= 21;			// [DB]�Ż���Ϣ
	optional PBPlayerActivityInfo	Activity			= 22;			// [DB]���Ϣ
	optional PBAwardRecord			Award				= 23;			// [DB]��ȡ��Ϣ
	optional PBMatrixInfo			Matrix				= 24;			// [DB]������Ϣ
	optional PBExpTimeInfo			ExpTimeInfo			= 25;			// [DB]���߾��鵤��Ϣ
	optional PBTreasureBowl			TreasureBowl		= 26;			// [DB]�۱�����Ϣ
	optional PBSpiritInfo			SpiritInfo			= 27;			// [DB]������Ϣ
};


// Task
message PBTask
{
	required  uint32			TaskID			= 1;
	optional  uint32			TaskProgress	= 2;
	optional  int32				GameTimeLeft	= 3;			// ʣ��ʱ��  -1��ʾ������ʱ����
	repeated  uint32			TaskData		= 4;
	repeated  uint32			TalkedNpcs		= 5;			// �Ѿ���ɵĶԻ�NPC
	optional  uint32			ExFlags			= 6;			// ������ Ϊ��������
	optional  uint32			BeginTime		= 7;			// ���ڼ�¼����ʼ��ʱ��
};

// ����������
message PBLoopTaskData
{
	optional  uint32       TodayCompletedCircles	= 1; //  �����Ѿ���ɵ����л�����Ĵ���
	optional  uint64       LastCompletedTime		= 2; //  �ϴ���ɻ������ʱ��
	repeated  uint32	   LoopTasks				= 3; //  ���ϵĻ�����
	optional  uint32	   CompletedTimes			= 4; //  ����ɴ���(����)
	optional  uint64	   LastAbortTime			= 5; //  �����ϴη���ʱ��
	optional  int32        CurSubIndex				= 6; //  ��ǰ�����е�������������ֻ�н�����Ż���¸�ֵ����������ֵ���� ��ʼ-1
	optional  uint32       WeekLoops				= 7; //  ��������ɵ��������������
	optional  uint32       DayCompletedLoopFlag		= 8; //  �����Ƿ����һ���ֻ�����ı�־
};

// ����������
message PBStorageTaskData
{
	repeated  uint32	   Tasks					= 1; //  ���ϵĵ�ǰ�Ŀ������б�
	optional  uint32	   TaskNum					= 2; //  �����������
	optional  uint64	   LastClickNpc				= 3; //  ����ϴε��NPC��ʱ�䣨����Ǵ��գ���ˢ�������б�
	optional  uint32       CurTaskID				= 4; //  ��ǰ������ID
	repeated  uint32	   GotTasks					= 5; //  �Ѿ����˵�(��ǰˢ��������)
	optional  uint32	   GotNum					= 6; //  �Ѿ��������ϵĿ���������
	optional  uint32	   TodayCompleted			= 7; //  ��������ɴ���
	optional  uint32	   TodayRMBRefresh			= 8; //  ����RMB����ˢ���������
};

// ������������
message TragedyStruct
{
	optional uint32		TragedyIndex    = 1; // ������������ 1��ʼ
	optional fixed32	NextTragedyTask = 2; // ��Ӧ�� ��һ������������ID ����Ϊ0
	optional uint32		TragedyState	= 3; // ��Ӧ�Ľ�������״̬
};

message PBTaskGroupData
{
	optional  uint32				GroupID				= 1;	// ��ID
	optional  uint32				TodayCompleted		= 2;	// ������ɴ���
	optional  uint32				TodayAccepted		= 3;	// ���ս�ȡ����
	optional  uint32				WeekCompleted		= 4;	// ������ɴ���
	optional  uint32				WeekAccepted		= 5;	// ���ܽ�ȡ����
};

message SingleChairManTask
{
	optional uint32 TaskID			=	1;
	optional uint32 TaskState		=	2; // ����״̬����ͨ��״̬
};

message SingleCompletedInf
{
	optional uint32 ChairmanID			=	1;
	optional uint32 CompletedNum		=	2; // �������
};

// ������������
message PBChairManTaskData
{
	repeated  SingleChairManTask    Tasks					= 1; //  ���ϵĵ�ǰ�Ŀ������б�
	optional  uint32				ChairManID				= 2; //  ��������ID
	optional  uint32				CompletedNum			= 3; //  ��������� <����>
	optional  uint32				AcceptedNum				= 4; //  �ѽ�������
	repeated  SingleCompletedInf    Completed				= 5; //  �����������Ϣ
};

// ������ɫ��Ʒ�ʣ�����
message PBRefreshTaskData
{
	optional  uint32				TaskID				    = 1; //  ˢ������ID
	optional  uint32				TaskColor				= 2; //  ������ɫ ��Ʒ�ʣ�
	optional  uint32				ResultFlag				= 3; //  ���λ
};

message GroupPublishData
{
	optional  uint32				TaskID				    = 1; //  ��������ID
	optional  uint32				TaskState				= 2; //  ��������״̬ 
};

message PBTaskList
{
	optional  uint32				TaskNumber		= 1;
	repeated  PBTask				TaskList		= 2;
	optional  PBLoopTaskData		LoopTaskData	= 3;
	repeated  uint32				EventID			= 4;
	repeated  uint32				EventParam		= 5;
	repeated  uint32				EventTick		= 6;
	optional  PBStorageTaskData		StorageTaskData	= 7;
	repeated  TragedyStruct			TragedyTaskData = 8;
	repeated  uint32				CompletedTask	= 9;
	repeated  uint32				FailedTask		= 10;
	repeated  PBTaskGroupData		TaskGroups		= 11;
	optional  uint32				CompletedTragedy= 12;	// ����ɽ��ѵ�����
	optional  fixed32				LastLogOff		= 13; // �ϴο��/����ʱ��
	optional  uint32				RedirectFailTask= 14;
	optional  PBChairManTaskData	ChairManTask	= 15;	// ��������
	optional  uint32				TodayTeamLoopNum= 16;
	repeated  PBRefreshTaskData		RefreshData		= 17;
	repeated  uint32				RepeateTask		= 18;
	repeated  uint32				EndTime			= 19;
	repeated  GroupPublishData		CorpsPublish	= 20;
	
};

// ��ͼ��Ϣ
message PBMapData
{
	optional uint32			Direction	= 1; // ����
	optional uint32			PosX		= 2; // x����
	optional uint32			PosY		= 3; // y����
	optional uint32			AliveStatus	= 4; // ����״̬
};

// friend
message PBFriendGlobalData
{
	repeated  string  GroupNames	= 1; // ��������
	optional  uint32  IsRefuseAll	= 2; // �Ƿ��Զ��ܾ���Ӻ�������
};

message PBFriendData
{
	repeated  uint32  PlayerId		= 1; // ����charid
	repeated  uint32  GroupID		= 2; // ��ID
	repeated  uint32  Rel2Me		= 3; // ���ҵĹ�ϵ
	optional  uint32  BlessTimes	= 4; // ����ף�������Ĵ���
	repeated  uint32  IntimacyDegree= 5; // �������ܶ�	
	repeated  uint32  LastTimeAllOnline= 6; // �������ܶ�	
	repeated  uint32  DailyIntimacy = 7;	// ������ӻ�ȡ�����ܶ�
	repeated  uint32  LastUpdateTime = 8;	// ���һ�θ��µ�ʱ��
};

message PBEnemyData
{
	repeated  uint32  PlayerId		= 1; // ���charid
	repeated  uint32  Killed		= 2; // ɱ�����Ĵ���
	repeated  uint32  BeKilled		= 3; // ����ɱ�Ĵ���
	repeated  uint32  IsLocked		= 4; // �Ƿ�����
	repeated  uint32  KillTime		= 5; // ʱ���
};

message PBFriend
{
	optional PBFriendGlobalData	 Global			= 1;
	optional PBFriendData		 Friend			= 2;
	optional PBEnemyData		 Enemy			= 3;
	repeated uint32				 BlackList		= 4;  // ������
	repeated uint32				 LatestContact	= 5;  // �����ϵ��
};

message PBRepetionData
{
	optional uint32 Index		= 1;
	optional uint32 Data		= 2;
};

message PBRepetionMap
{
	optional uint32	MapID				= 1;
	optional uint32 Count				= 2;
	repeated PBRepetionData Data		= 3;
	optional uint32 WeekCount			= 4;
};

message PBRepetionRepe
{
	repeated PBRepetionData RepetionData= 1;
	optional uint32 RepeIndex			= 2;
	optional uint32 Count				= 3;
	optional uint32 WeekCount			= 4;
	optional uint32 SignUp				= 5;
	optional uint32 IntoTime			= 6;
	optional uint32 DieCount			= 7;
};

message PBRepetion
{
	optional uint32			BackLineID  = 1;
	optional uint32 		BackMapID   = 2;
	optional uint32 		BackPosX 	= 3;
	optional uint32 		BackPosY	= 4;
	repeated PBRepetionMap 	MapInfo 	= 5;
	optional uint64			Key			= 6;
	optional uint32			CampID		= 7;
	repeated PBRepetionRepe RepeInfo	= 8;
	optional uint32			InRepetion	= 9;
	optional uint32			RepetionIndex = 10;
	optional uint32			CheckResult	= 11;	// ������������
	optional uint32			AnswerCount	= 12;	// �ش�����Ĵ���
	optional uint32			GlobalSceneStatus=13;// ȫ�ַ�������״̬
	optional uint32			GlobalWarOffLineTime=14;// �뿪ȫ��ս����ʱ��
	optional uint64			RepetionKey	= 15;	// ��������ĸ���Key	
};

// ********************************************************************** //
// �����Ա��Ϣ 
// ********************************************************************** //
message PBMember
{
	optional uint32			EntityID	= 1;
	optional uint32			CharID		= 2;
	optional string			Name		= 3;
	optional uint32			AccountID	= 4;
	optional uint32			Type		= 5;
	optional uint32			Face		= 6;
	optional uint32			Metier		= 7;
	optional uint32			Level		= 8;
	optional uint32			Sex			= 9;
	optional uint32			LineID		= 10;
	optional uint32			MapID		= 11;
	optional uint32			HP			= 12;	
	optional uint32			MP			= 13;
	optional uint32			AP			= 14;
	optional uint32			XPos		= 15;
	optional uint32			YPos		= 16;
	optional uint32			CommState	= 17;	// ���״̬�����ߡ����ߡ����...
	optional PBBuffList		BuffList	= 18;	// buff�б�	   	
	optional uint32			RepetionMapIndex	= 19;	// �����е�ͼindex
	optional uint32        Order		= 20;   // �ڶ����е�˳��
};
//********************************************************
// PBTeamMsg
// ������ļ��Ϣ
//********************************************************

message PBTeamMsg
{
	optional uint32		Type = 1;		// ���� == TEAM_ASKFOR����ļ == TEAM_CONSCRIBE
	optional uint32		CharID = 2;
	optional string		Name = 3;
	optional uint32		Metier = 4;
	optional uint32		Level = 5;
	optional uint32		MaxLevel = 6;
	optional uint32		MinLevel = 7;
	optional string		Content = 8;
	optional uint32		Count = 9;
	optional uint32		RootStyle = 10;  // һ������
	optional uint32		SubStyle = 11;	 // ��������
};

/*
 *	PBStallInfo
 */
message PBStallInfo
{
	optional string		StallName	= 1;
	optional string		AdContent	= 2;
	optional uint32		HasFlag		= 3;	// ̯λ�Ƿ���ڣ�true--���ڣ�false--������
	optional int32		StallType	= 4;  //��̯����
};


//********************************************************
// PBLifeSkill
// �������Ϣ
//********************************************************
message PBLifeSkill
{
	optional uint32	LifeSkillType		= 1;		// ���������
	optional uint32 LifeSkillLevel		= 2;		// ����ܵȼ�
	optional uint32 SpecializedDegree	= 3;		// �����������
	optional uint32	LifeSkillStatus		= 4;		// �����״̬
	optional uint32	LifeSkillKind		= 5;		// �������࣬�����ܻ��Ǹ��޼���	
	repeated uint32	ComposeID			= 6;		// ��ѧ�䷽ID
};

message PBLifeSkillBox
{
	repeated PBLifeSkill LifeSkill		= 1;	
};

//********************************************************
// PBExpTimeInfo
// ����ʱ�����
//********************************************************
message PBExpTimeInfo
{
	optional uint32 OffLineTimeLength		=	1;			// ʵ������ʱ��	
	optional uint32	EffectiveOffTimeLength	=	2;			// ��Ч����ʱ��	
	optional uint32	LastEffectiveTimeLength	=	3;			// ��������Ч����ʱ��ʱ�����ڵ��ۼӳ���		
	optional uint32	LastCalculateTime		=	4;			// ��һ�μ�����Ч����ʱ���ʱ��
	optional uint32	BlackPillsTime			=	5;			// �ڹ����ʱ��
	optional uint32	BlackPillID				=	6;			// �ڹ����ģ��ID
	optional uint32	ExpFromOffLine			=	7;			// ����ʱ���ۺϵľ���	
};

//********************************************************
// ������Ҫ�����ݿ��ȫ������
//********************************************************
message PBSinglePublishInfo
{
	optional uint32 PubNum		= 1;	// Ψһ��ʶID������������ID��
	optional uint32 RecvAwards	= 2;	// ����״̬ ��enTaskPublishState
};

message PBTaskPublishInfo
{
	repeated PBSinglePublishInfo SingleData  = 1;	// �ֹ��Ҵ洢������
	optional uint32 TodayPublishNum			 = 2;
	optional uint32 OncePublishNum			 = 3;
	optional uint32 TotalFinishNum			 = 4;
};

message CMessagePlayerInfo
{
	optional uint32 role_id					= 1;
	optional uint32 account_id				= 2;
	optional string role_name				= 3;
	optional uint32 gender_id				= 4;
	optional uint32 metier_id				= 5;
	optional uint32 nationality_id			= 6;
	optional uint32 face_type				= 7;
	optional uint32 line_id					= 8;
	optional uint32 map_id					= 9;
	optional uint32 role_level				= 10;
	optional uint64 role_expr				= 11;
	optional uint32 role_money				= 12;
	optional int32 pos_x					= 13;
	optional int32 pos_y					= 14;
	optional uint32 is_alive				= 15;
	optional uint32 login_time				= 16;
	optional uint32 online_duration			= 17;
	optional uint32 save_status				= 18;
	optional uint32 save_bitflag			= 19;
	optional uint32 bounded_money			= 20;
	optional uint32 check_sum				= 21;
	optional uint32 silver_yb 				= 22;
	optional uint32 storage_money			= 23;
	optional uint32 storage_bounded_money	= 24;
	optional uint32 role_status_param		= 25;
	optional int32 country_id				= 26;
	optional uint32 role_familyid			= 27;
	optional uint32 role_corpsid			= 28;
	optional uint32 charged_silver_yb		= 29;
	optional uint32 consumed_silver_yb		= 30;
	optional uint32	role_protecttime		= 31;
	optional string	role_password			= 32;
	optional uint32	role_vip_flag			= 33;
	optional uint32	role_vip_time			= 34;
	optional uint32	role_marriageid			= 35;
	optional uint32 role_changecamp_time    = 36;
	optional uint32	role_status				= 37;
	optional uint32	role_swornid			= 38;
};

message PBAwardRecord
{
	repeated uint32	AwardID					= 1;
	repeated uint32	Times					= 2;
};

message PBMatrixInfo
{
	repeated uint32	MasterID				= 1;	// ʦ��ID����Ϊ3��
	repeated uint32	SlaveID					= 2;	// ���Ӹ���
	repeated uint32 SlaveValue				= 3;	// ��N������Եֵ
	optional uint32	SlavePoint				= 4;	// ��Ե����
	optional uint32	MasterPoint				= 5;	// ʦ�µ���
	optional uint32	SlaveTotal				= 6;	// ��Ե�ۼ�
	optional uint32	MasterTotal				= 7;	// ʦ���ۼ�
	repeated uint32	MasterPercent			= 8;	// �ж�����
	optional uint32	MasterTimes				= 9;	// ��ʦ����
	optional uint32	SlaveNum				= 10;	// ��ʦ����
	optional uint32	MasterGive				= 11;	// �ܼƸ���ʦ��
	optional uint32 BeginnerNum				= 12;	// ���ֵ�������
	optional uint32	FormalNum				= 13;	// �߼���������
};

// ����ϵͳ
message PBCharm
{
	optional uint32 CharmValue			= 1;	// �ۼ�����ֵ
	optional uint32 WeekIncCharm		= 2;	// �����ۼƻ��
	optional uint32 LastWeekIncCharm	= 3;	// ���ܵ�
};

// ����ϵͳ
message PBGuideData
{
	optional uint32		LevelBak	=	1;	// ���յȼ�����
	optional uint32		ExpBak   =	2;	// ���վ�������
	optional uint32		HonorBak =	3;	// ���չ�ѫ����
	optional uint32		AchiveBak =	4;	// ���ճɾ͵�������
	optional uint32		KillBak =	5;	// ����������ɱ����
};

message PBSingleTimes
{
	optional uint32		Key   = 1;
	optional uint32		Value = 2;
};
// �ƴ���Ϣ
message PBTimes
{
	repeated PBSingleTimes timesinfo = 1;
};

// ��ҵľ۱���pb�ṹ
message PBTreasureBowlItem
{
	optional uint32	 ItemID		= 1;	// ��ƷID
	optional uint32	 UsedTimes	= 2;	// ʹ�õĴ���
};
message PBTreasureBowl
{
	optional uint32					TotalNum			= 1;	// �ܴ���
	optional uint32					ExchangeTime		= 2;	// �۱���ʱ��
	repeated PBTreasureBowlItem		TreasureBowlItem	= 3;	// �Ѿ��۱�����Ʒ���б�
};

message PBRepetDataToClient
{
	optional uint32					RepetIndex			= 1;	//��������
	optional uint32					RepetData			= 2;	//��������
};

message PBRepetDataList
{
	repeated PBRepetDataToClient	RepetDataToClient			= 1;	// ��������
};

// ��ݳ�Ա��Ϣ
message PBSwornMember
{
	optional uint32	RoleID	= 1;	// ��ɫID
	optional uint32	TeamPos = 2;	// �������
};

// ���������Ϣ
message PBSwornTeam
{
	repeated PBSwornMember SwornMember = 1;
};