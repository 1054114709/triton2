/******************************************************************************
��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾
******************************************************************************
�ļ���		: template_pb.hxx
�汾��		: 1.0
����		: Edwin
��������	: 2009-03-03
����޸�	: 
��������	: ����Ľṹ��template.h�еĸ��������Ӧ
			: [ע] PB ȫ��[Protocal Buffers -- google����Э��]
�����б�	: 
�޸���ʷ	: 
�޸�����	: ����
*******************************************************************************/


/****************************	�ֶ�����   ************************************
*
*	required: ���븳ֵ���ֶΣ�һ��Ҫ����˲�������������
*	optional: ���п��޵��ֶ�
*	repeated: ���ظ��ֶ�(�䳤�ֶ�)
*
******************************************************************************/

// ������ٶ�����/������
option optimize_for = SPEED;

message PBItemSet
{
	repeated PBItemBase				Item			= 1;	// ��ͨ����
	repeated PBItemBindStone		BindStone		= 2;	// ��ʯ
	repeated PBItemBluePrint		BluePrint		= 3;	// 
	repeated PBItemBook				ItemBook		= 4;	// ������
	repeated PBItemCard				ItemCard		= 5;	// ��Ƭ
	repeated PBItemExp				ItemExp			= 6;
	repeated PBItemHorse			Horse			= 7;
	repeated PBItemJewel			Jewel			= 8;
	repeated PBItemPetEgg			PetEgg			= 9;
	repeated PBItemPetFood			PetFood			= 10;
	repeated PBItemPhysic			Physic			= 11;	// ҩ
	repeated PBItemQuestion			Question		= 12;	// ����
	repeated PBItemRelife			Relife			= 13;	// ����
	repeated PBItemReturn			Return			= 14;	// ���ط�
	repeated PBItemReturnPaper		ReturnPaper		= 15;	// ���ؾ�
	repeated PBItemRune				Rune			= 16;	// 
	repeated PBItemScroll			Scroll			= 17;	// ����
	repeated PBItemSequence			Sequence		= 18;	// ��������
	repeated PBItemShout			Shout			= 19;	// ����
	repeated PBItemSkill			ItemSkill		= 20;	// 
	repeated PBItemStove			Stove			= 21;	// ¯ʯ
	repeated PBItemStuff			Stuff			= 22;	// ԭ��
	repeated PBItemTask				ItemTask		= 23;	// �������
	repeated PBItemTeleport			Teleport		= 24;	// ������Ʒ
	repeated PBItemTeleSymbol		TeleSymbol		= 25;	// ָ�����ͷ�
	repeated PBItemUpgLeast			UpgLeast		= 26;	// �������׷�
	repeated PBItemUpgLuck			UpgLuck			= 27;	// 
	repeated PBItemYuanBug			YuanBug			= 28;	// Ԫ����
	repeated PBItemYuanEgg			YuanEgg			= 29;	// Ԫ����
	repeated PBRedStone				RedStone		= 30;
	repeated PBItemAutoShout		AutoShout		= 31;
	repeated PBItemKitBag			KitBag			= 32;
	repeated PBItemUpg				ItemUpg			= 33;
	repeated PBItemRemove			ItemRemove		= 34;
	repeated PBItemChange			ItemChange		= 35;
	repeated PBItemAdapter			ItemAdapter		= 36;
	repeated PBItemMineMap			MineMap			= 37;	
	repeated PBItemCall				ItemCall		= 38;
	repeated PBItemGiftBag			GiftBag			= 39;
	repeated PBItemMagicWeapon		MagicWeapons	= 40;
	repeated PBItemToken			Token			= 41;
	repeated PBFuncItem				FuncItem	= 42;
	repeated PBItemSkillBook		SkillBook	= 43;	
	repeated PBItemRedPaper			RedPaper		= 44;
	repeated PBItemMagicStone		MagicStone		= 45;
	repeated PBItemVip				VipItem			= 46;
	repeated PBItemClean			CleanItem		= 47;
	repeated PBAwardInfo			AwardInfo		= 48;
	repeated PBLeagueBag			LeagueBag		= 49;
	repeated PBInvitation			Invitation		= 50;
	repeated PBSysInvitation		SysInvitation	= 51;	
	repeated PBItemRefresh			ItemRefresh		= 52;
	repeated PBItemSummon			ItemSummon		= 53;
	repeated PBItemDirect			ItemDirect		= 54;
	repeated PBItemGetStar			ItemGetStar		= 55;
	repeated PBItemAutoCollect		ItemAutoCollect	= 56;
	repeated PBItemBlackPills		ItemBlackPills	= 57;	
	repeated PBItemExpContainer		ExpContainer	= 58;	// �������鵤
	repeated PBItemExpPills			ExpPills		= 59;	// ���鵤
	repeated PBSpiritItem			SpiritItem		= 60;	// ����
	repeated PBItemExpTome		ExpTome		=	61; //�����ĵ�
};


message PBConfigTable
{	
	repeated PBBeginner				Beginner		= 1;	// ��������
	repeated PBData					Data			= 2;	// ���ñ�
	repeated PBDiploidTable			Diploid			= 3;	// ��˫��
	repeated PBDropLevel			DropLevel		= 4;	// ����ȼ�
	repeated PBDropTable			DropTable		= 5;	// �����
	repeated PBRedStoneExpTable		RedStoneTable	= 6;
	repeated PBReliveTable			ReliveTable		= 7;	// �����
	repeated PBSellTable			SellTable		= 8;	// ���۱�
	repeated PBTeleTable			TeleTable		= 9;	// ���ͱ�
	repeated PBAddPKTable			AddPkTable		= 10;
	repeated PBOfficialTable		OfficialTable	= 11;
	repeated PBOgreTran				OgreTran		= 12;
	repeated PBTplMagicWeaponProIncTable MagicWeaponProTable = 13;
	repeated PBBindChargeTable		BindChargeTabel = 14;	
	repeated PBPKValueTable			PKTable			= 15;
	repeated PBMagicWeaponSkillBoxProTable MagicWeaponSkillBox = 16;	
	repeated PBEquipExchangeTable	EquipExchange	= 17;
	repeated PBMapTable				MapTable		= 18;
	repeated PBMultiAttackTable		MultiAttackTable = 19;
	repeated PBMatrixTable			MatrixTable		= 20;
	repeated PBTemplateMarriageConfig MarriageConfig = 21; 	
	repeated PBProGressConfig		ProgressConfig	= 22;
	repeated PBCountTable			CountTable		= 23;
	repeated PBActivityConfig		ActivityConfig	= 24;	// ����ñ�
	repeated PBDirectTable			DirectTable		= 25;
	repeated PBWorldBattleConfig	BattleConfig	= 26;
	repeated PBLevelMoneyLmt		MoneyLmt		= 27;
    repeated PBHandinTable          HandinTable     = 28;   // �Ͻɽ������ձ�
    repeated PBHandinEncourage      HandinEncourage = 29;   // �Ͻɽ���
	repeated PBItemChangeCamp       changeCamp      = 30;   // ת��Ӫ
	repeated PBAccuseConfig			AccuseConfig	= 31;
	//repeated PBRuneConfig			RuneConfig      = 32; //����ת������
	repeated PBComRuneConfig		ComRuneConfig   = 32; //���ӷ�����������
	repeated PBMagicWeaponDecomposeTable	MWDecomposTab = 33; // �����ֽ��
	repeated PBMagicWeaponQuickUpTable		MWQuickUpTab = 34; // ����������
	repeated PBGlobalMapConfig		GlobalMapConfig	= 35;
	repeated PBOffLineExpConfig		OffLineExpConfig = 36;
	repeated PBRepeFameTable		RepeFameTable	= 37;
	repeated PBCastingSpiritTable	CastingSpiritTable	= 38;
	
};

message PBSkillSet
{
	repeated PBAureoleSkill			AureoleSkill	= 1;	// 
	repeated PBBuff					Buff			= 2;	// Buff
	repeated PBNormalSkill			NormalSkill		= 3;	// ��ͨ����
	repeated PBSkill				Skill			= 4;	// ����
	repeated PBSkillTree			SkillTree		= 5;	// ������
	repeated PBSkillTreeNode		SkillTreeNode	= 6;	// �������ڵ�
	repeated PBTrapSkill			TrapSkill		= 7;
	repeated PBMultiBuff			MultiBuff		= 8;
	repeated PBFangCunTree			FangCunTree		= 9;	// ����ɽ������
	repeated PBFangCunTreeNode		FangCunNode		= 10;	// ����ɽ�ڵ�
};

message PBEquipSet
{
	repeated PBEquipArmor			EquipArmor		= 1;	
	repeated PBEquipFashion			EquipFashion	= 2;	// ʱװ
	repeated PBEquipment			Equipment		= 3;	// ��ͨװ��
	repeated PBEquipUpg				EquipUpg		= 4;	// װ������
	repeated PBEquipWeapon			Weapon			= 5;	// ����
	repeated PBOpenSlot				OpenSlot		= 6;	// ����
	repeated PBProduceEquip			ProduceEquip	= 7;	// ����װ��
	repeated PBProduceExp			ProduceExp		= 8;	
	repeated PBProducePhysic		ProducePhysic	= 9;
	repeated PBSpell				Spell			= 10;
	repeated PBSuitNormal			SuitNormal		= 11;	// ��ͨ��װ
	repeated PBSuitProducer			SuitProducer	= 12;	// ��������װ
	repeated PBMultiCompose			MultiCompose	= 13;	// ���Ӻϳ�
	repeated PBCompose				Compose			= 14;	// �ϳ�
	repeated PBCTemplateDecompound	Decompound		= 15;
	repeated PBLightTable			LightTable		= 16;
	repeated PBMWProJudgeEffTable	MWJudgeEff		= 17;
	repeated PBMWProJudgeSpirTable	MWJudgeSpir		= 18;
	repeated PBMWLevelQuotietyTab	MWQuotiety		= 19;
};	

message PBTemplate
{
	optional PBItemSet				ItemSet			= 1;
	optional PBConfigTable			ConfigTable		= 2;
	optional PBSkillSet				SkillSet		= 3;
	optional PBEquipSet				EquipSet		= 4;

	repeated PBBattlePet			BattlePet		= 5;	// ս����

	repeated PBHonorObtain			HonorObtain		= 6;	// ��ѫ���
	repeated PBHonorToExp			HonorToExp		= 7;	// ��ѫת����
	repeated PBLevelExp				LevelExp		= 8;	// �ȼ�����ת����
	repeated PBLevelProperty		LevelPro		= 9;	// �ȼ����Ա�
	repeated PBMetier				Metier			= 10;	// ְҵ
	repeated PBMetierPro			MetierPro		= 11;	// ְҵ����
	repeated PBMine					Mine			= 12;	// ��
	repeated PBNpc					Npc				= 13;	// NPC
	repeated PBNPCCollect			NpcCollect		= 15;	// �ɼ�npc
	repeated PBOgreBox				Box				= 16;	// ����
	repeated PBOgreProperty			OgreProperty	= 17;
	repeated PBPetLevelExp			PetLevelExp		= 18;
	repeated PBQuestionExp			QuestionExp		= 19;
	repeated PBShowPet				ShowPet			= 20;	// ���ͳ�
	repeated PBSummonBeast			SummonBeast		= 21;	// �ٻ���	
	repeated PBTemplateProperty		TplProperty		= 22;
	repeated PBTemplatePropertyTable TplProTable	= 23;
	repeated PBTotalDrop			TotalDrop		= 24;
	repeated PBBlock				Block			= 25;	
	repeated PBTplHierogram			Hierogram		= 26;	
	repeated PBTemplateTalent		Talent			= 27;
	repeated PBTplBuffImmunity		BuffImmunity	= 28;
	repeated PBTemplateLifeSkill	LifeSkill		= 29;
			
	repeated PBLifeSkillScroll		LifeSkillScroll	= 30;
	repeated PBTitleManager			TitleManager	= 31;
	repeated PBSkillStorage				 MagicWeaponSkillStorage = 32;
	
	
	repeated PBCDGroupTable			CDGroupTable	= 33;					  
	repeated PBApConfig				ApConfig		= 34;
		
	repeated PBJudgeConfig			JudgeConfig		= 35;	
	repeated PBWizardTable			WizardTable		= 36;	
	
	repeated PBTrend				Trend			= 37;
	repeated PBAchieveAward			AchieveAward	= 38;
	repeated PBPower				Power			= 39;
	repeated PBOfficial				Official		= 40;	
	repeated PBConstructExp			ConstructExp	= 41;	
	repeated PBTemplateTalentStage	TalentStage		= 42;
	repeated PBCorpsBOSS			CorpsBOSS		= 43;

};

message PBHandinEncourage
{
    optional uint32     TempId               = 1; // ģ��ID
    optional uint32     HandinItemType       = 2; // �Ͻ���Ʒ����
    optional uint32     HandinItemID         = 3; // �Ͻ���ƷID
    optional uint32		HandinItemNum        = 4; // �Ͻ���Ʒ����
    optional uint32		EncourageType        = 5; // ������Ʒ����
    optional uint32		EncourageId          = 6; // ������ƷID
    optional uint32		EncourageNum         = 7; // ������Ʒ����	
};

//**********************************
// PBItemBase ���߻�����
//**********************************
message PBHandinTable
{
    optional uint32     TempID              = 1; // ģ����
    optional uint32     ActivityId          = 2; // ����
    repeated uint32     EncourageTplID      = 3; // �������ID
};

//----------------------------------------------------
// ����, PBItem### ��Ӧtemplate.h �� CTplItem###
//----------------------------------------------------

//**********************************
// PBItemBase ���߻�����
//**********************************
message PBItemBase
{
	optional uint32		TempID				= 1;	// ģ��ID
	optional uint32		ItemType			= 2;	// ��������
	optional uint32		ProcessType			= 3;	// ����ʽ
	optional uint32		PileLimit			= 4;	// �ѵ�����
	optional string		ItemName			= 5;	// ������ʾ����
	optional string		ModelName			= 6;	// ���ߵ���ģ������
	optional string		IconName			= 7;	// ����ͼ������
	optional uint32		PurchasePrice		= 8;	// ���ߵ�����
	optional uint32		SalePrice			= 9;	// ���������
	optional uint32		PurchaseBindMoney	= 10;	// �������Ƿ�֧�ְ󶨽�Ǯ
	optional uint32		SaleBindMoney		= 11;	// ������Ƿ�֧�ְ󶨽�Ǯ
	optional string		Describe			= 12;	// ��ϸ˵��
	optional uint32		LastTime			= 13;	// ��Чʱ��
	optional uint32		StopAttack			= 14;	// ʹ�ú��Ƿ�ֹͣ�Զ�����
	optional string		TypeDesc			= 15;	// ��������
	optional uint32		CanUse				= 16;	// �Ҽ�����Ƿ����ʹ��
	optional uint32		SkillID				= 17;	// ʹ�õļ���ID
	optional uint32		Level				= 18;	// ��Ʒ�ȼ�
	optional uint32		Disappear			= 19;	// ʹ�ú��Ƿ���ʧ
	repeated uint32		CDGroup				= 20;	// ��ȴ��
	repeated uint32		LmtMapID			= 21;	// ���Ƴ��е�ͼID
	optional uint32		ValidTime			= 22;	// ��Чʱ��
	optional uint32		ValidType			= 23;	// ��Чʱ���ʱ����
	optional uint32		CommonID			= 24;	// ������ID
	optional uint32		EatType				= 25;	// ��������
	optional uint32		EatValue			= 26;	// ����ֵ
	optional uint32		CountType			= 27;	// ʹ������
	optional uint32		LmtLineID			= 28;	// ����ʹ�õ���ӪID
	repeated uint32		LmtUseMapID			= 29;	// ����ʹ�õ�ͼID
	repeated uint32		LmtRepetionID		= 30;
	optional uint32		CompID				= 31;	// �ϳ��䷽ID
	optional uint32		InvilidDate			= 32;   // ���ھ�������
};

//**********************************
// PBItemReturn �سǾ���
//**********************************

message PBItemReturn
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		Timer				= 2;	// ����ʹ��ʱ��
};

//**********************************
// PBItemSkillBook ����������
//**********************************

message PBItemSkillBook
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		Color				= 2;	// ��Ӧ���ܿ���ɫ
	optional uint32		SkillID				= 3;	// ����ID
	optional uint32		SuccProb			= 4;	// �ɹ�����
	optional uint32		NeedMoneyType		= 5;	// ��Ҫ��Ǯ����
	optional uint32		NeedMoney			= 6;	// ��Ҫ��Ǯ
};

//**********************************
// PBItemBindStone ��ʯ
//**********************************

message PBItemBindStone
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		FaceGroupID			= 2;	// ������ID
	optional uint32      BindStoneType      = 3; //��ʯ����
};

//**********************************
// PBItemScroll ����
//**********************************

message PBItemScroll
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		GetTaskID			= 2;	// ʹ�ú󴥷�����
};


//**********************************
// PBItemCall �ٻ�����Ʒ
//**********************************

message PBItemCall
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		CallNpcID			= 2;	// �ٻ�������NPC ID
	optional int32		X					= 3;	// ����X
	optional int32		Y					= 4;	// ����Y
	optional int32		IsDestroy			= 5;	// ʹ�ú��Ƿ���ʧ
	optional int32		MapID				= 6;	// �ٻ���ͼID
	optional int32		LmtMapID			= 7;	// ����ʹ�õ�ͼID
	optional int32		LmtX				= 8;	// ����ʹ������X
	optional int32		LmtY				= 9;	// ����ʹ������Y
	optional int32		LmtWide				= 10;	// ���ƿ��
	optional int32		LmtHeight			= 11;	// ���Ƹ߶�
};


//**********************************
// PBItemCard ��Ƭ
//**********************************

message PBItemCard
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional string		ShowText			= 2;	// ��ʾ����
	optional uint32		Order				= 3;	// ����
	optional string		Weapon				= 4;	// ������ʾ
	optional string		Skill				= 5;	// ������ʾ
	optional string		Level				= 6;	// �ȼ���ʾ
	optional uint32		Exp					= 7;	// ����
	optional uint32		CanExchange			= 8;	// �Ƿ���Զһ�
	optional uint32		CanChallenge		= 9;	// �Ƿ������ս
	optional uint32		Type				= 10;	// ����
	optional uint32		Pos					= 11;	// λ��
	optional uint32		Bonus				= 12;	// ������
	optional uint32		SkillID1			= 13;	// ����ID1
	optional uint32		SkillID2			= 14;	// ����ID2
};

//**********************************
// PBItemTeleport ������Ʒ
//**********************************

message PBItemTeleport
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		MapID				= 2;	// ���͵���ĵ�ͼID
	optional uint32		UseTimes			= 3;	// ����ʹ�õĴ���
};

//**********************************
// PBItemReturnPaper ���ɷ��ؾ�
//**********************************

message PBItemReturnPaper
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		LineID				= 2;	// ���͵������ID
	optional uint32		MapID				= 3;	// ���͵����ĵ�ͼID
	optional uint32		PosX				= 4;	// ���͵����X����
	optional uint32		PosY				= 5;	// ���͵����Y����
};

//**********************************
// PBItemTeleSymbol ���ͷ�
//**********************************

message PBItemTeleSymbol
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		TeleTable			= 2;	// ���ͱ�ID
	optional uint32		UseTimes			= 3;	// ����ʹ�õĴ���
};

//**********************************
// PBItemStove ¯ʯ
//**********************************

message PBItemStove
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		LineID				= 2;	// ���͵������ID
	optional uint32		MapID				= 3;	// ���͵���ĵ�ͼID
	optional uint32		PosX				= 4;	// ���͵����X����
	optional uint32		PosY				= 5;	// ���͵����Y����
	optional uint32		CoolTime			= 6;	// ��ȴʱ��
	optional uint32		MetierLimit			= 7;	// ְҵ����
	optional uint32		LevelLimit			= 8;	// �ȼ�����
};

//**********************************
// PBItemPetEgg ���ﵰ
//**********************************

message PBItemPetEgg
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		PetTempID			= 2;	// Ҫ���͵ĵ�ͼID
	optional uint32		NeedItemID			= 3;	// ��Ҫ�ĵ���ID
	optional uint32		RevertPrice			= 4;	// ��ԭ�����Ǯ
	optional uint32		InitAdvice			= 5;	// ��ʼ�ҳ϶�
	optional uint32		InitLevel			= 6;	// ��ʼ�ȼ�
	optional uint32		InitExp				= 7;	// ��ʼ����
	optional uint32		InitSkillPoint		= 8;	// ��ʼ���ܵ�
	repeated uint32		InitSkillID			= 9;	// ��ʼ����ID
	repeated uint32		InitSkillLevel		= 10;	// ��ʼ���ܵȼ�
};

//**********************************
// PBItemPetFood ����ʳ��
//**********************************

message PBItemPetFood
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		InitLevel			= 2;	// ��ʼ�ȼ�
	optional uint32		FullLevel			= 3;	// ���ӵı�ʳ��
	optional uint32		TypeMask			= 4;	// ʳ���������
};

//**********************************
// PBItemRelife �������
//**********************************

message PBItemRelife
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		Timer				= 2;	// ʹ��ʱ��
	optional uint32		CoolTime			= 3;	// ��ȴʱ��
	optional uint32		ShareCD				= 4;	// �Ƿ��������Ʒ������ȴ
};

//**********************************
// PBItemSkill ���ü��ܵ���Ʒ
//**********************************

message PBItemSkill
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		LevelLimit			= 2;	// �ȼ�����
	optional uint32		SkillID				= 3;	// ���õļ���ID
	optional uint32		CoolTime			= 4;	// ��ȴʱ��
	optional uint32		ShareCD				= 5;	// �Ƿ��������Ʒ������ȴ
	optional uint32		OprType				= 6;	// ��������
	optional uint32     BuffID				= 7;    // BUFF ID
};

//**********************************
// PBItemBook ������
//**********************************

message PBItemBook
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		OPType				= 2;	// ����������
};

//**********************************
// PBItemUpg ����ʯ
//**********************************

message PBItemUpg
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		MaxLevel			= 2;	// ����ʹ�õĵȼ�
	optional uint32		Type				= 3;	// ���
	optional uint32		Limit				= 4;	// ����
	optional uint32		Fail				= 5;	// �Ƿ�ʧ��
	repeated uint32		Luck				= 6;	// �����ɹ�����
	optional uint32		UpType				= 7;	// ������������
};

//**********************************
// PBItemUpgLuck װ���������˷�
//**********************************

message PBItemUpgLuck
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		IncLuck1			= 2;	// ��߾����ɹ��ĸ���
	optional uint32		IncLuck2			= 3;	// ��߾���ʧ�ܺ�ֻ��һ���ĸ���
	repeated uint32		IncLuck3			= 4;	// ��߾����ɹ�������n���ĸ���
	optional uint32		Level				= 5;	// ����ĵȼ�
};

//**********************************
// PBItemUpgLeast װ���������׷�
//**********************************

message PBItemUpgLeast
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		IncLuck1			= 2;	// ��߾����ɹ��ĸ���
	optional uint32		IncLuck2			= 3;	// ��߾���ʧ�ܺ�ֻ��һ���ĸ���
	optional uint32		Type				= 4;
};

//**********************************
// PBItemRemove ��ʯժ����
//**********************************

message PBItemRemove
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	repeated uint32		Rand				= 2;	// ժ�������ĸ���
	optional uint32		Bind				= 3;	// ժ����ʯ�Ƿ��
	optional uint32		Level				= 4;	// ����
	optional uint32		Low					= 5;	// 
};

//**********************************
// PBItemChange ����ת��ʯ
//**********************************

message PBItemChange
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		Type				= 2;	// ת��������
	optional uint32		Res					= 3;	// ת���������
	optional uint32		MetierRequire		= 4;	// ְҵ����
};

//**********************************
// PBItemQuestion �����
//**********************************

message PBItemQuestion
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	repeated uint32		QuestionRate		= 2;	// ��������n����ʱ�ĸ���
	optional uint32		ExpAddRae			= 3;	// �����ľ���ӳɰٷֱ�
	optional uint32		EachTimeLength		= 4;	// �����ÿ����Ŀ�Ĵ���ʱ������,������-1 ��ʾû������
	optional uint32		TotalTimeLength		= 5;	// �����������Ŀ�Ĵ���ʱ������,������-1��ʾû������
	optional uint32		RepeatTimeAllowed	= 6;	// �����ÿ����Ŀ������Ĵ�����-1��ʾû������
};

//**********************************
// PBItemTask �������
//**********************************

message PBItemTask
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		UseTimes			= 2;	// ʹ�ô���
	optional uint32		ValidTime			= 3;	// ʹ��ʱ����ʱ��
	optional string		ShowText			= 4;	// ����ʱ�ͻ�����ʾ����
	optional uint32		MapID				= 5;	// ʹ�������������ڵ�ͼID
	optional uint32		PosX				= 6;	// ʹ�������������Ͻ�X
	optional uint32		PosY				= 7;	// ʹ�������������Ͻ�Y
	optional uint32		Width				= 8;	// ʹ������������
	optional uint32		Height				= 9;	// ʹ����������߶�
	optional uint32		GetTaskID			= 10;	// ʹ�ú󴥷�����
	optional uint32		GiveItemID			= 11;	// ʹ�ú󷢷ŵ���
	optional uint32		ChangeTime			= 12;	// x�����������Ʒ
	optional uint32		ChangeItem			= 13;	// ��ɵ���Ʒ
	optional uint32		FailTaskID			= 14;   // �仯��ǿ�����ĸ�����ʧ��
};

//**********************************
// PBItemStuff ����ԭ��
//**********************************

message PBItemStuff
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		ShowColor			= 2;	// ��ʾ��ɫ
	optional uint32		ComposeID			= 3;	// �ϳɵ��䷽ID
};

//**********************************
// PBItemExp ���Ӿ������
//**********************************

message PBItemExp
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		IncRate				= 2;	// ���ӱ���. Rate * 10000
	optional uint32		Time				= 3;	// ����ʱ��
};

//**********************************
// PBItemExp ���Ӿ������
//**********************************

message PBItemChangeCamp
{
	optional uint32		TmpID				= 1;	// ģ��ID
	optional uint32		m_itemId			= 2;	// ����id
	optional uint32		m_giftId			= 3;	// ���id
	optional uint32     m_cd_time           = 4;    // cd ʱ��

};
//message PBRuneConfig
//{
//	optional uint32  TmpID					=1;  //ģ��ID
//	optional uint32  m_changeRuneItemId     =2;  //ת������id
//
//}
message PBComRuneUnit
{
	optional uint32   m_whitenum			=1;	 //��ɫ����
	optional uint32   m_bluenum				=2;	 //��ɫ����
	optional uint32   m_purplenum			=3;	 //��ɫ����
	optional uint32   m_rand				=4;	//%d��������
	optional uint32   m_money				=5;	//�������Ľ�Ǯ
	optional uint32   m_runeLevel			=6;	//������ĵȼ�
};

message PBComRuneConfig //���ӷ�����������
{
	optional uint32  TmpID					=1;  //ģ��ID
	optional uint32   m_upRuneRand			=2;  //%d����������
	optional uint32   m_max					=3; //�����������
	optional uint32   m_min					=4; //��С��������
	repeated PBComRuneUnit m_upRuneUnit     =5; //ÿ����������


}
 

//**********************************
// PBItemShout ��������
//**********************************

message PBItemShout
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		FaceGroupID			= 2;	// ������ID
};

//**********************************
// PBItemAutoShout �Զ�����
//**********************************

message PBItemAutoShout
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		FaceGroupID			= 2;	// ������ID
};

//**********************************
// PBItemPhysic ҩƷ
//**********************************

message PBItemPhysic
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		ShowType			= 2;	// ��������
	optional uint32		BuffID				= 3;	// Buff���
	optional uint32		LevelLimit			= 4;	// �ȼ�����
	optional uint32		HPMaxValue			= 5;	// HP���ֵ
	optional uint32		HPTime				= 6;	// HP�ָ�����Ҫ��ʱ��
	optional uint32		HPIncTime			= 7;	// HPÿ�λָ���ʱ����
	optional uint32		HPInvValue			= 8;	// HP�ָ�ֵ
	optional uint32		MPMaxValue			= 9;	// MP���ֵ
	optional uint32		MPTime				= 10;	// MP�ָ�����Ҫ��ʱ��
	optional uint32		MPIncTime			= 11;	// MPÿ�λָ���ʱ����
	optional uint32		MPInvValue			= 12;	// MP�ָ�ֵ
	optional uint32		CoolTime			= 13;	// ��ȴʱ��
	optional uint32		ShareCD				= 14;	// �Ƿ��������Ʒ������ȴ
	optional uint32		HPPercent			= 15;	// �Զ��ָ��ĺ�ٷֱ�
	optional uint32		MPPercent			= 16;	// �Զ��ָ������ٷֱ�
	optional uint32		MaxHPPercent		= 17;	// ���ظ��ĺ�ٷֱ�
	optional uint32		MaxMPPercent		= 18;	// ���ظ������ٷֱ�
	optional uint32		LifeSkilType		= 19;	// ���������
	optional uint32		DegreeValue			= 20;	// ʹ�ú������������������
	optional uint32		PhisicType			= 21;	// ҩƷ����
	optional uint32		ApValue				= 22;	// ��������ֵ
	optional uint32		Color				= 23;	// ҩƷ��ɫ
};

//**********************************
// PBItemHorse ����
//**********************************

message PBItemHorse
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		MetierLimit			= 2;	// ְҵ����
	optional uint32		LevelLimit			= 3;	// �ȼ�����
	optional uint32		PersonLimit			= 4;	// ��������
	optional uint32		UseTime				= 5;	// ʹ��ʱ��
	optional uint32		IncreaseSpeedPer	= 6;	// �ٶ����Ӱٷֱ�
	optional string		ModelName			= 7;	// �����Ӧģ��·��
	optional uint32		CoolTime			= 8;	// ��ȴʱ��
	optional uint32		ShareCD				= 9;	// �Ƿ��������Ʒ������ȴ
	optional uint32		SpeedBuff			= 10;	// ��Ӧ����BUFF
	optional uint32		UsingTime			= 11;	// ʹ��ʱ����ʱ��
	optional string		ShowText			= 12;	// ��������
	optional uint32		OffHorseProb		= 13;	// �������������
	optional uint32		OffBuffID			= 14;	// ������ϵ�BUFF
	optional uint32		InitAP				= 15;	// �������ĵĻ���ֵ
	optional uint32		DeltaAP				= 16;	// ����ÿ�����ĵĻ���ֵ
};

//**********************************
// PBItemBluePrint �䷽����
//**********************************

message PBStuff
{
	optional uint32		StuffID		= 1;
	optional uint32		Number		= 2;
};
message PBProduct
{
	optional uint32		ProductID	= 1;
	optional uint32		Percent		= 2;	// ��������
};

message PBItemBluePrint
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		TempID				= 2;	// ģ��ID
	optional uint32		NeedSkillID			= 3;	// ��Ҫ�ļ���ID
	optional uint32		NeedSkillLevel		= 4;	// ��Ҫ�ļ��ܵȼ�
	optional uint32		ProduceCount		= 5;	// һ�������ĸ���
	optional uint32		ProduceCost			= 6;	// һ��������������
	optional uint32		ObtainExp			= 7;	// ÿ��������õĻ�������
	repeated PBStuff	Stuff				= 8;	// ԭ��
	repeated PBProduct	Product				= 9;	// ��Ʒ
};

//**********************************
// PBItemRune ���ĵ���
//**********************************

message PBItemRune
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		SuitID				= 2;	// ��װ���
	optional string		Word				= 3;	// ������
	optional uint32		OrderID				= 4;	// ��װ�е�˳��
	optional uint32		InsertCharge		= 5;	// ��Ƕ����
	optional uint32		PropertyID			= 6;	// ������������ID
	optional uint32     RuneIndex			= 7;	// ���ĵȼ��б�
	optional uint32		ShowColor			= 8;	// ��ʾ��ɫ
};

//**********************************
// PBItemJewel �鱦����
//**********************************

message PBItemJewel
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		TypeID				= 2;	// �鱦�ȼ�
	optional uint32		Pos					= 3;	// װ��λ��
	optional uint32		ShowColor			= 4;	// ��ʾ��ɫ
	optional uint32		Property			= 5;	// ��������
	optional uint32		Unique				= 6;	// �Ƿ�Ψһ
	repeated uint32		JewelID				= 7;	// �����õ��ı�ʯID
	optional uint32		ComposeID			= 8;	// �䷽ID
	optional uint32		InsertCharge		= 9;	// ��Ƕ����
	optional uint32		RemoveCharge		= 10;	// ժ������
	optional uint32		ComposeCharge		= 11;	// �ϳɷ���
	optional uint32		Level				= 12;	// �鱦����
	repeated uint32		Rand				= 13;
	optional uint32		NewJewelID			= 14;	// ID
	repeated uint32		NewRand				= 15;
	repeated uint32		CarveJewelID		= 16;	// �����õ��ı�ʯID
	repeated uint32		CarveRand			= 17;	// �����õ��ĸ���
	optional uint32		CarveCharge			= 18;	// ��������
	optional uint32		CardID				= 19;	// ������ID
	optional uint32		CanCarve			= 20;	// �Ƿ���Ե���
	optional uint32		AffectRand			= 21;	// Ӱ��ϳɸ���
	optional uint32		JewComID			= 22;	// ��ʯ�ϳɹ��ñ�־
	optional uint32		ComLevel			= 23;	// �ϳɵȼ�
};

//**********************************
// PBItemYuanBug Ԫ����
//**********************************

message PBItemYuanBug
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		Yuan				= 2;	// �洢����
	optional uint32		EggID				= 3;	// ת������
	optional uint32		YuanType			= 4;	// ��������
};

//**********************************
// PBItemYuanEgg Ԫ��������
//**********************************

message PBItemYuanEgg
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		Level				= 2;	// �ȼ�
	optional uint32		ComposeID			= 3;	// �ϳ��䷽ID
	optional uint32		MaxEquip			= 4;	// ���װ���ȼ�
};

//**********************************
// PBItemSequence ��������˳��
//**********************************

message PBItemSequence
{
	optional uint32		TempID				= 1;
	repeated uint32		Sequence			= 2;	// ��������
};

//---------------------------------------------
// װ����������, �̳е�������
//---------------------------------------------

//**********************************
// PBEquipment װ������
//**********************************

message PBEquipment
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional string		ModalName			= 2;	// װ��ģ������
	optional uint32		ShowLevel			= 3;	// װ���ȼ�(0-15)
	optional uint32		EquipType			= 4;	// װ����λ
	optional uint32		ShowColor			= 5;	// ��ʾ��ɫ
	repeated uint32		StrRequire			= 6;	// ��������
	repeated uint32		ConRequire			= 7;	// ��������
	repeated uint32		StaRequire			= 8;	// ��������
	repeated uint32		WisRequire			= 9;	// ��������
	repeated uint32		SprRequire			= 10;	// ��������
	optional uint32		MetierRequire		= 11;	// ְҵ����
	optional uint32		LevelRequire		= 12;	// �ȼ�����
	optional uint32		SexRequire			= 13;	// �Ա�����
	optional uint32		YuanValue			= 14;	// Ԫ��ֵ
	optional uint32		EquipDurability		= 15;	// װ���;ö�
	optional uint32		BaseMendCharge		= 16;	// ����������
	optional uint32		NpcAbrasionRate		= 17;	// ��npc����1�ε�������ֱ�
	optional uint32		PlayerAbrasionRate	= 18;	// ��ҽ���1�ε�������ֱ�
	optional uint32		CanUpGrade			= 19;	// �Ƿ��������
	optional uint32		UpgCharge			= 20;	// ������Ҫ��������
	optional uint32		NeedBindMoney		= 21;	// �Ƿ���Ҫ�󶨽�Ǯ
	repeated uint32		UpgPropertyID		= 22;	// �������ӵ�����ID
	repeated uint32		UpgValue			= 23;	// ��n�����ӵ��ĵ�m������ֵ; value[m][n](0<=m<3,0<=n<15)
	repeated uint32		MaxSlotNumber1		= 24;	// ������Բ۸���
	optional uint32		MaxSlotNumber2		= 25;	// ������Բ۸���
	repeated uint32		PropertyPercent		= 26;	// ����ʱ����������Ϊn�ĸ���(0<=n<5)
	repeated uint32		PropertyTableID		= 27;	// �������Ա�ģ��ID
	repeated uint32		PropertyPercentEx	= 28;	// ����ʱ����������Ϊn�ĸ���(0<=n<5)
	repeated uint32		PropertyTableIDEx	= 29;	// �������Ա�ģ��ID
	repeated uint32		PAttackDiff			= 30;	// �������ӵ�����������
	repeated uint32		JudgePercent1		= 31;	// ��һ�μ���������Ϊn�ĸ���
	repeated uint32		JudgePercent2		= 32;	// �ڶ��μ���������Ϊn�ĸ���
	repeated uint32		ResDefPercent		= 33;	// ���Եĸ���
	repeated uint32		ResAttPercent		= 34;	// ���Թ����ĸ���
	repeated uint32		ResDefValue			= 35;	// ������������ֵ
	repeated uint32		ResAttValue			= 36;	// ���Թ�����������ֵ
	optional uint32		SuitID				= 37;	// ��װID
	optional uint32		SuitPos				= 38;	// ��װ���
	repeated uint32		MAttackDiff			= 39;	// �������ӵķ�����������
	optional uint32		OpenCharge			= 40;	// ���۷���
	optional uint32		AddCharge			= 41;	// �Ӳ۷���
	optional uint32		JudgeCharge			= 42;	// ��������
	optional uint32		ReJudgeCharge		= 43;	// �ٴμ�������
	optional uint32		DefUpgCharge		= 44;	// ����ǿ������
	optional uint32		DefChangeCharge		= 45;	// ����ת������
	optional uint32		AttUpgCharge		= 46;	// ����ǿ������
	optional uint32		AttChangeCharge		= 47;	// ����ת������
	optional uint32		CanDefUpgrade		= 48;	// �Ƿ���Կ�������
	optional uint32		CanAttUpgrade		= 49;	// �Ƿ������������	
	optional uint32		BindBonus			= 50;	// ��Ѫ�������Ա�
	optional uint32		MultiCompose		= 51;	// ���Ӻϳ��䷽
	optional uint32		CanChange			= 52;	// �Ƿ����ת��
	optional uint32		ChangeCharge		= 53;	// ת�����Է���
	optional uint32		CanSplit			= 54;	// �Ƿ���Բ��
	repeated uint32		SplitID				= 55;	// ��ֵ�ID
	repeated uint32		SplitNum			= 56;	// ��ֵ�����
	optional uint32		SplitCharge			= 57;	// ��ַ���
	repeated uint32		UpgExtra1			= 58;	// ���Ե�����ֵ1
	repeated uint32		UpgExtra2			= 59;	// ���Ե�����ֵ2
	optional uint32		ExtCharge			= 60;	// ������Ҫ��������
	optional uint32		ResistTran			= 61;	// �Ƿ��ֿܵ�����
	optional uint32		IsShenQi			= 62;	// �Ƿ�������


};

//**********************************
// PBEquipFashion ʱװװ��
//**********************************

message PBEquipFashion
{
	optional PBEquipment EquipInfo			= 1;	// װ��������Ϣ
	optional uint32	BuffID					= 2;
};

//**********************************
// PBEquipWeapon ����װ��
//**********************************

message PBEquipWeapon
{
	optional PBEquipment EquipInfo			= 1;	// װ��������Ϣ
	optional uint32		 WeaponType			= 2;	// ��������
	optional uint32		 AttackType			= 3;	// ��������	
	optional uint32		 AttackDistance		= 4;	// ��������		
};

//**********************************
// PBEquipArmor  ��������
//**********************************

message PBEquipArmor
{
	optional PBEquipment EquipInfo			= 1;	// װ��������Ϣ
	optional uint32		ShowType			= 2;	// ��������
	optional string		ArmorSuit			= 3;	// ������װ��Դ
};

//---------------------------------------------
// װ������, �������Ա�
//---------------------------------------------

//**********************************
// PBTemplateProperty װ����������
//**********************************

message PBTemplateProperty
{
	optional uint32		TempID				= 1;	// ��������ģ��ID
	optional string		PropertyName		= 2;	// ������������
	optional uint32		PropertyFunc		= 3;	// ���Թ�ʽ
	optional uint32		CanOut				= 4;	// �Ƿ���Ա�ת��
	optional uint32		IntMinValue			= 5;	// �̶�ֵ������ֵ����
	optional uint32		IntMaxValue			= 6;	// �̶�ֵ������ֵ����
	optional uint32		FloatMinValue		= 7; 	// �ٷֱ�������ֵ����
	optional uint32		FloatMaxValue		= 8;	// �ٷֱ�������ֵ����
	optional uint32		SkillID				= 9;	// ��ؼ���ID
	optional uint32		Area				= 10;	// ��������
};

//**********************************
// PBTemplatePropertyTable �������Ա�
//**********************************

message PBPropertyPercent
{
	optional uint32		TempID		= 1;
	optional uint32		Percent		= 2;	
};

message PBTemplatePropertyTable
{
	optional uint32			TempID			= 1;
	repeated PBPropertyPercent	Property	= 2;
};

//---------------------------------------------
// �������
//---------------------------------------------

//**********************************
// PBMetier  ְҵ����
//**********************************

message PBMetier
{
	optional uint32			TempID			= 1;	// ģ��ID
	optional string			MetierName		= 2;	// ְҵ����
	optional uint32			MetierID		= 3;	// ְҵID
	repeated uint32			GenerID			= 4;	// ְҵ�ĵ�n���ϵ��ID
	optional uint32			SkillPoint		= 5;	// ÿ��һ����ü��ܵ�
	optional uint32			PropertyPoint	= 6;	// ÿ��һ��������Ե�
	optional uint32			WalkSpeed		= 7;	// ְҵ�����ٶ�
	optional uint32			RunSpeed		= 8;	// ְҵ�����ٶ�
	optional uint32			InitLevel		= 9;	// ְҵ��ʼ�ȼ�
	optional uint32			InitHP			= 10;	// ְҵ��ʼ���HP
	optional uint32			InitMP			= 11;	// ְҵ��ʼ���MP
	optional uint32			InitPAttack		= 12;	// ְҵ��ʼ������
	optional uint32			InitPDefense	= 13;	// ְҵ��ʼ�������
	optional uint32			InitMAttack		= 14;	// ְҵ��ʼ��������
	optional uint32			InitMDefense	= 15;	// ְҵ��ʼ��������
	optional uint32			InitAbnResist	= 16;	// ְҵ��ʼ�쳣״̬����
	optional uint32			InitWindResist	= 17;	// ְҵ��ʼŭ��״̬����
	optional uint32			InitFireResist	= 18;	// ְҵ��ʼ����״̬����
	optional uint32			InitWaterResist	= 19;	// ְҵ��ʼ����״̬����
	optional uint32			InitLightResist	= 20;	// ְҵ��ʼ����״̬����
	optional uint32			InitEarthResist	= 21;	// ְҵ��ʼ����״̬����
	optional uint32			InitSadowResist	= 22;	// ְҵ��ʼ����״̬����
	optional uint32			InitDeathRate	= 23;	// ְҵ��ʼ������
	optional uint32			InitDeathValue	= 24;	// ְҵ��ʼ�����˺��ӳ�
	optional uint32			InitNmlHitrate	= 25;	// ְҵ��ʼ�չ�����
	optional uint32			InitNormalDuck	= 26;	// ְҵ��ʼ�չ�����
	optional uint32			InitSkillDuck	= 27;	// ְҵ��ʼ���ܲ�Ӱ
	optional uint32			DeltaHP			= 28;	// ְҵÿ��һ���������HP
	optional uint32			DeltaMP			= 29;	// ְҵÿ��һ���������MP
	optional uint32			DeltaPAttack	= 30;	// ְҵÿ��һ������������
	optional uint32			DeltaPDefense	= 31;	// ְҵÿ��һ�������������
	optional uint32			DeltaMAttack	= 32;	// ְҵÿ��һ�����ӷ�������
	optional uint32			DeltaMDefense	= 33;	// ְҵÿ��һ�����ӷ�������
	optional uint32			DeltaAbnResist	= 34;	// ְҵÿ��һ�������쳣״̬����
	optional uint32			DeltaWindResist	= 35;	// ְҵÿ��һ������ŭ��״̬����
	optional uint32			DeltaFireResist	= 36;	// ְҵÿ��һ�����ӳ���״̬����
	optional uint32			DeltaWaterResist = 37;	// ְҵÿ��һ����������״̬����
	optional uint32			DeltaLightResist = 38;	// ְҵÿ��һ�����Ӵ���״̬����
	optional uint32			DeltaEarthResist = 39;	// ְҵÿ��һ����������״̬����
	optional uint32			DeltaShadowResist = 40;	// ְҵÿ��һ�����Ӻ���״̬����
	optional uint32			DeltaDeathRate	= 41;	// ְҵÿ��һ�����ӱ�����
	optional uint32			DeltaDeathValue = 42;	// ְҵÿ��һ�����ӱ����˺��ӳ�
	optional uint32			DeltaNormalHitrate = 43;// ְҵÿ��һ�������չ�����
	optional uint32			DeltaNormalDuck = 44;	// ְҵÿ��һ�������չ�����
	optional uint32			DeltaSkillDuck	= 45;	// ְҵÿ��һ�����Ӽ�������
	optional uint32			PAttackPerStr	= 46;	// ÿ��������Ӧ������
	optional uint32			DeathValuePerStr = 47;	// ÿ��������Ӧ�����˺��ӳ�
	optional uint32			MaxHPPerStr		= 48;	// ÿ��������ӦHP
	optional uint32			PDefensePerCon	= 49;	// ÿ�����ʶ�Ӧ�������
	optional uint32			HPRSpeedPerCon	= 50;	// ÿ�����ʶ�ӦHP�ָ��ٶ�
	optional uint32			MaxHPPerSta		= 51;	// ÿ��������Ӧ���HP
	optional uint32			AbnResistPerSta	= 52;	// ÿ��������Ӧ���ÿ��������Ӧ�쳣״̬����
	optional uint32			MAttackPerWis	= 53;	// ÿ��������Ӧ��������
	optional uint32			MaxMPPerWis		= 54;	// ÿ��������Ӧ���MP
	optional uint32			DeathValuePerWis = 55;	// ÿ��������Ӧ�����˺�
	optional uint32			MDefensePerSpr	= 56;	// ÿ�㾫���Ӧ��������
	optional uint32			MaxMPPerSpr		= 57;	// ÿ�㾫���Ӧ���MP
	optional uint32			MPRSpeedPerSpr	= 58;	// ÿ�㾫���ӦMP�ָ��ٶ�
	optional uint32			NormalHPRSpeed	= 59;	// ��ͨ״̬HP�ָ��ٶ�
	optional uint32			NormalSitHPRSpeed = 60;	// ��ͨ����״̬HP�ָ��ٶ�
	optional uint32			BattleHPRSpeed	= 61;	// ս��״̬HP�ָ��ٶ�
	optional uint32			BattleSitHPRSpeed = 62;	// ս��״̬����HP�ָ��ٶ�
	optional uint32			NormalMPRSpeed	 = 63;	// ��ͨ״̬MP�ָ��ٶ�
	optional uint32			NormalSitMPRSpeed = 64;	// ��ͨ����״̬MP�ָ��ٶ�
	optional uint32			BattleMPRSpeed	 = 65;	// ս��״̬MP�ָ��ٶ�
	optional uint32			BattleSitMPRSpeed = 66;	// ս��״̬����MP�ָ��ٶ�

	optional uint32			InitIgnoreDuck	 = 67;	// ְҵ��ʼ��������	
	optional uint32			DeltaIgnoreDuck = 68;	// ְҵÿ��һ�����Ӻ�������
	optional uint32			MAttackPerStr	= 69;	// ÿ��������Ӧ��������
	optional uint32			DeathRatePerStr = 70;	// ÿ��������Ӧ�����ȼ�
	optional uint32			MaxMPPerStr		= 71;	// ÿ��������ӦMP
	optional uint32			PDefensePerStr	= 72;	// ÿ��������Ӧ�������
	optional uint32			MDefensePerStr	= 73;	// ÿ��������Ӧ��������
	optional uint32			NmlHitratePerStr	= 74;	// ÿ��������Ӧ�չ�����
	optional uint32			NormalDuckPerStr	= 75;	// ÿ��������Ӧ�չ�����
	optional uint32			IgnoreDuckPerStr	= 76;	// ÿ��������Ӧ��������
	optional uint32			PAttackPerCon	= 77;	// ÿ�����ʶ�Ӧ������
	optional uint32			MAttackPerCon	= 78;	// ÿ�����ʶ�Ӧ��������
	optional uint32			DeathRatePerCon = 79;	// ÿ�����ʶ�Ӧ�����ȼ�
	optional uint32			DeathValuePerCon = 80;	// ÿ�����ʶ�Ӧ�����˺��ӳ�
	optional uint32			MaxHPPerCon		= 81;	// ÿ�����ʶ�ӦHP
	optional uint32			MaxMPPerCon		= 82;	// ÿ�����ʶ�ӦMP
	optional uint32			MDefensePerCon	= 83;	// ÿ�����ʶ�Ӧ��������
	optional uint32			NmlHitratePerCon	= 84;	// ÿ�����ʶ�Ӧ�չ�����
	optional uint32			NormalDuckPerCon	= 85;	// ÿ�����ʶ�Ӧ�չ�����
	optional uint32			IgnoreDuckPerCon	= 86;	// ÿ�����ʶ�Ӧ��������
	optional uint32			PReducePerSta		= 87;	// ÿ��������Ӧ������˰ٷֱ�
	optional uint32			MReducePerSta		= 88;	// ÿ��������Ӧ�������˰ٷֱ�
	optional uint32			PAttackPerWis	= 89;	// ÿ��������Ӧ������
	optional uint32			MaxHPPerWis		= 90;	// ÿ��������Ӧ���HP
	optional uint32			DeathRatePerWis = 91;	// ÿ��������Ӧ�����ȼ�
	optional uint32			PDefensePerWis	= 92;	// ÿ��������Ӧ�������
	optional uint32			MDefensePerWis	= 93;	// ÿ��������Ӧ��������
	optional uint32			NmlHitratePerWis	= 94;	// ÿ��������Ӧ�չ�����
	optional uint32			NormalDuckPerWis	= 95;	// ÿ��������Ӧ�չ�����
	optional uint32			IgnoreDuckPerWis	= 96;	// ÿ��������Ӧ��������
	optional uint32			PAttackPerSpr	= 97;	// ÿ�㾫���Ӧ������
	optional uint32			MAttackPerSpr	= 98;	// ÿ�㾫���Ӧ��������
	optional uint32			DeathRatePerSpr = 99;	// ÿ�㾫���Ӧ�����ȼ�
	optional uint32			DeathValuePerSpr = 100;	// ÿ�㾫���Ӧ�����˺��ӳ�
	optional uint32			MaxHPPerSpr		= 101;	// ÿ�㾫���ӦHP
	optional uint32			PDefensePerSpr	= 102;	// ÿ�㾫���Ӧ�������
	optional uint32			NmlHitratePerSpr	= 103;	// ÿ�㾫���Ӧ�չ�����
	optional uint32			NormalDuckPerSpr	= 104;	// ÿ�㾫���Ӧ�չ�����
	optional uint32			IgnoreDuckPerSpr	= 105;	// ÿ�㾫���Ӧ��������
	optional uint32			InitDeathDefense	 = 106;	// ְҵ��ʼ��������	
	optional uint32			DeltaDeathDefense	= 107;	// ְҵÿ��һ��������������
	optional uint32			DeathDefensePerStr	= 108;	// ÿ��������Ӧ��������
	optional uint32			DeathDefensePerCon	= 109;	// ÿ�����ʶ�Ӧ��������
	optional uint32			DeathDefensePerSta	= 110;	// ÿ��������Ӧ��������
	optional uint32			DeathDefensePerWis	= 111;	// ÿ��������Ӧ��������
	optional uint32			DeathDefensePerSpr	= 112;	// ÿ�㾫���Ӧ��������
};

//---------------------------------------------
// NPC ģ������
//---------------------------------------------

//**********************************
// PBNpc ����NPC (NPC�̳�Ogre)
//**********************************

message PBNpc
{
	optional PBOgreProperty	Ogre			= 1;	// Ogre����
	optional uint32			FuncType		= 2;	// NPC����
	optional string			Talk			= 3;	// ������
	optional uint32			StageID			= 4;	// ��վID
	optional uint32			TalkServiceID	= 5;	// ̸������ID
	optional uint32			SellServiceID	= 6;	// ���۷���ID
	optional uint32			MailService		= 7;	// �ʼ�����
	optional uint32			StorageService	= 8;	// �ֿ����
	optional uint32			UpgService		= 9;	// ��������
	optional uint32			EqtBindService	= 10;	// װ���󶨷���
	optional uint32			WelfareService	= 11;	// ÿ�ո�������
	optional string			Describe		= 12;	// �ƺ�
	optional uint32			StudySkillID	= 13;	// ѧϰ����ְҵID
	optional uint32			TownX			= 14;	// �سǵ�X����
	optional uint32			TownY			= 15;	// �سǵ�Y����
	optional uint32			StorageTaskNpc	= 16;	// �ʰ�����npc
	optional uint32			StorageTaskID	= 17;	// npc�ҵĻʰ�����ID
	optional uint32			DownLevel		= 18;	// �ʰ�����ȼ�����
	optional uint32			UpLevel			= 19;	// �ʰ�����ȼ�����
	optional uint32			DiploidTable	= 20;	// ��˫��
	optional uint32			ResetPService	= 21;	// ϴ��
	optional uint32			FamilyService	= 22;	// �������
	optional uint32			CorpService		= 23;	// ���ŷ���
	optional uint32			ChangeService	= 24;	// ת������
	optional uint32			JudgeService	= 25;	// ��������
	optional uint32			ActivityService = 26;	// �����
	optional uint32			ExchangeService = 27;	// �һ�����
	optional uint32			HonorService	= 28;	// ��ѫ����
	optional uint32			Battle			= 29;	// ս������
	optional uint32			LifeSkillService= 30;	// ����ܷ���
	optional uint32			BidDay			= 31;	// ��������
	optional uint32			BidHour			= 32;	// ����ʱ
	optional uint32			BidMinute		= 33;	// ���۷�
	optional uint32			CoprsBattle		= 34;	// ����ս����
	optional uint32			MinBidPrice		= 35;	// ���ۼӼ���Сֵ
	optional uint32			BattleCity		= 36;	// �ǳ�ID
	optional uint32			MWProJudgeService		= 37;	// �������Լ�������
	optional uint32			MWSkillJudgeService		= 38;	// �������ܼ�������
	optional uint32			EquipExchangeService	= 39;	// װ���һ��ķ���
	optional uint32			ExchangeTableID			= 40;	// װ���һ����ID	
	optional uint32			CorpsBidDay			= 41;	// ����ս��������
	optional uint32			CorpsBidHour		= 42;	// ����ս����ʱ
	optional uint32			CorpsBidMinute		= 43;	// ����ս���۷�		
	optional uint32			MWClearPointService		= 44;	// ����ϴ�����
	optional uint32			MWSecondJudgeService	= 45;	// �������μ�������
	optional uint32			UnionService			= 46;	// �������˷���
	optional uint32			CountryService			= 47;	// ��������
	optional uint32			FriendService			= 48;	// �⽻����
	optional uint32			CountryType				= 49;	// NPC����
	optional uint32			GoldenYBService			= 50;	// Ԫ����ȡ����
	optional uint32			ChairManTaskService		= 51;	// �����������
	optional uint32			ChairManTaskID			= 52;	// ��������ID
	optional uint32			MarriageService			= 53;	// ������
	optional uint32			MatrixService			= 54;	// ��Ե����
	optional uint32			FamilyType				= 55;	// ����NPC����
	optional uint32			StoneBuff				= 56;	// ��ʯBUFF
	optional uint32			Disappear				= 57;	// ��ȡ���Ƿ���ʧ
	optional uint32			RefreshService			= 58;	// ˢ���Է���
	optional uint32			PedalIndex				= 59;	// ��ѯ�Ĵ��͵�����
	optional uint32			DirectService			= 60;	// ժ�Ƿ���
	optional uint32			ExtraService			= 61;	// ӡ������
	optional uint32			WarService				= 62;	// ��ս����
	optional uint32			WarOpType				= 63;	// ��ս����
	optional uint32			WarValue				= 64;	// ��սֵ
	optional uint32			WarCamp					= 65;	// ��ս��Ӫ
	optional uint32			EquipLevelService		= 66;	// װ�������ķ���
	optional uint32			WarHonor				= 67;	// ��սս��
	optional uint32			FangCunService			= 68;	// ѧϰ����ɽ���ܷ���
	optional uint32			ResistTran				= 69;	// �Ƿ��ֿܵ�����
	optional uint32			FBFunc					= 70;	// �������⹦��
	optional uint32			FBFunc_Parame1			= 71;	// �������⹦�ܲ���1
	optional uint32			FBFunc_Parame2			= 72;	// �������⹦�ܲ���2
	optional string			FBFunc_Str				= 73;	// �������⹦���ַ���
	optional uint32			TaxService				= 74;	// ��˰����
	optional uint32			ChangeCampService		= 75;   // ת��Ӫ���� add by qiufufu
	optional uint32			WeakProtectService		= 76;	// ������������
    optional uint32         YaoQianShuRank          = 77;   // ҡǮ�����а�
    optional uint32         Handin                  = 78;   // �Ͻɷ���
	optional uint32         SpecialEvent            = 79;   // �����¼�����
    optional uint32         YaoQianInfo             = 80;   // ҡǮ���˵��
	optional uint32			TreasureBowl			= 81;	// �۱������
	optional uint32			MWDecomposeService		= 82;	
	optional uint32			MWImprintService		= 83;	
	optional uint32			MWUpdateService			= 84;	
	optional uint32			MWUpdateExService		= 85;	
	optional uint32			CorpsBidStartDay		= 86;	// ����ս���ۿ�ʼ����
	optional uint32			CorpsBidStartHour		= 87;	// ����ս���ۿ�ʼʱ
	optional uint32			CorpsBidStartMinute		= 88;	// ����ս���ۿ�ʼ��		
	optional uint32         LastOneService			= 89;   // ����ɱ˵��
	optional uint32			FamilyBidStartHour		= 90;	// ����ս���ۿ�ʼʱ
	optional uint32			FamilyBidStartMinute	= 91;	// ����ս���ۿ�ʼ��	
	optional uint32			MWQLComposeService		= 92;	
	optional uint32			RandomTeleService		= 93;	// �����ڵ��������
	optional uint32			IntroduceMapID			= 94;	
	optional uint32			ShiTuService			= 95;	// ʦͽ����˵��
	optional uint32			SwornService			= 96;	// ��ݷ���
	optional uint32			GlobalWarService		= 97;	// ���ս˵��
	optional uint32			SuperEquipExchange		= 98;	// �Ƿ��������һ�
};

//**********************************
// PBSellTable ���۱�
//**********************************

message PBSellItem
{
	optional string		PageName		= 1;
	repeated uint32		ItemID			= 2;
	repeated uint32		ItemGoldPrice	= 3;	// ��Ʒ�𶧼۸�
	repeated uint32		ItemNum			= 4;	// ��Ʒ���۵��������
	repeated uint32		ItemRefreshDay	= 5;	// ��Ʒ��ˢ������
};

message PBSellTable
{
	optional uint32			TempID			= 1;
	repeated PBSellItem		Item			= 2;
	optional uint32			SellTableType	= 3;
	optional uint32			WarCityMapID	= 4;		
};

//**********************************
// PBTotalDrop ����ĸ��
//**********************************

message PBTotalDrop
{
	optional uint32			TempID			= 1;	// ģ��ID
	repeated uint32			DropTableID		= 2;	// �����
	repeated uint32			DropCount		= 3;	// �������
};

//**********************************
// PBDropTable �����ӱ�
//**********************************

message PBDropItem
{
	optional uint32		DropItemID		= 1;
	optional uint32		DropProbability	= 2;	
	optional uint32		LevelProbablity = 3;
	optional uint32		Notify			= 4;
	optional uint32		Special			= 5;
	optional uint32		Show			= 6;
};

message PBDropTable
{
	optional uint32			TempID			= 1;	// ģ��ID
	optional uint32			DropTurn		= 2;	// ���������
	repeated uint32			DropNumberRate	= 3;	// ÿ���ֵ���n����Ʒ�ĸ���
	repeated PBDropItem		DropItem		= 4;	// ������Ʒ
};

//**********************************
// PBNPCCollect �ɼ�NPC
//**********************************

message PBNPCCollect
{
	optional uint32			TempID			= 1;	// ģ��ID
	optional string			Name			= 2;	// NPC����
	optional string			ModelName		= 3;	// ͼ����Դ����
	repeated uint32			TaskID			= 4;	// ��n������ID
	repeated uint32			ItemID			= 5;	// ��n����������Ҫ����Ʒ
	optional uint32			DropID			= 6;	// ����ĸ��
	optional uint32			Number			= 7;	// ���ɼ���
	optional uint32			SkillType		= 8;	// ���������
	optional uint32			SkillKind		= 9;	// ���������
	optional uint32			CollectDegree	= 10;	// �ɼ���Ҫ��������	
	repeated uint32			value			= 11;	// ���������ȺͲɼ���Ҫ�������ȵĲ�ֵ����
	repeated uint32			Probality		= 12;	// �����������ȺͲɼ���Ҫ�������ȵ���Ӧ��ֵ�����ȡ�����ȵĸ���
	repeated uint32			DegreeValue		= 13;	// �����������ȺͲɼ���Ҫ�������ȵ���Ӧ��ֵ�����ȡ�����ȵ�ֵ	
	optional uint32			apcost			= 14;	// ����ܲɼ���Ҫ���ĵĻ���ֵ
	repeated uint32			ItemNum			= 15;	// �����������Ʒ������
	repeated uint32 		ItemProbality	= 16;	// ����
	optional uint32			CollectLevel	= 17;	// �ɼ���Ҫ�ĵȼ�
	repeated uint32			ExtraItemNum = 18;	  //��n����������������Ʒ�������ֵ
	repeated uint32			ExtraItemProbality = 19;   //��n�������������ĸ���
	optional uint32			CollectTaskType = 20;		//�ɼ�����������

};

//**********************************
// PBOgreProperty ��������
//**********************************

message PBOgreProperty
{
	optional uint32			TempID			= 1;	// ģ��ID
	optional string			Name			= 2;	// NPC����
	optional string			ModelName		= 3;	// ͼ����Դ����
	optional uint32			OgreType		= 4;	// ��������
	optional uint32			DropType		= 5;	// ���䷽ʽ
	optional uint32			StrategyID		= 6;	// ����ID
	optional uint32			DropID			= 7;	// ����ID
	optional uint32			Level			= 8;	// ����ȼ�
	optional uint32			DisplayeLevel	= 9;	// ������ʾ�ȼ�
	optional uint32			AttackRate		= 10;	// ����Ƶ��
	optional uint32			AttackTime		= 11;	// ��������ʱ��
	optional uint32			HPRSpeed		= 12;	// �����Ѫ�ٶ�
	optional uint32			MPRSpeeds		= 13;	// ��������ٶ�
	optional uint32			RunSpeed		= 14;	// ���ﱼ���ٶ�
	optional uint32			InitLevel		= 15;	// �����ʼ�ȼ�
	optional uint32			HP				= 16;	// �����ʼ���HP
	optional uint32			MP				= 17;	// �����ʼ���MP
	optional uint32			PAttack			= 18;	// �����ʼ������
	optional uint32			PDefence		= 19;	// �����ʼ�������
	optional uint32			PAttackRange	= 20;	// �����ʼ����������
	optional uint32			PReducePer		= 21;	// �����ʼ�������
	optional uint32			MAttack			= 22;	// �����ʼ��������
	optional uint32			MDefence		= 23;	// �����ʼ��������
	optional uint32			MAttackRange	= 24;	// �����ʼ������������
	optional uint32			MReducePer		= 25;	// �����ʼ��������
	optional uint32			DeathRate		= 26;	// �����ʼ������
	optional uint32			DeathValue		= 27;	// �����ʼ�����˺��ӳ�
	optional uint32			DeathDefense	= 28;	// �����ʼ��������
	optional uint32			NormalHitrate	= 29;	// �����ʼ�չ�����
	optional uint32			NormalDuck		= 30;	// �����ʼ�չ�����
	optional uint32			Recover			= 31;	// �����Ƿ��Ѫ
	optional uint32			IgnoreDuck		= 32;	// �����ʼ��������
	repeated uint32			ResDef			= 33;	// �����ʼ����
	repeated uint32			ResAtt			= 34;	// �����ʼ���Թ���
	optional uint32			NeedDelay		= 35;	// �����Ƿ�Զ�̹���
	optional uint32			PatrolType		= 36;	// Ѳ������
	optional uint32			IsInitiative	= 37;	// �Ƿ�������������
	optional uint32			WalkDistance	= 38;	// ���о���
	optional uint32			TeleTime		= 39;	// ����ʱ��
	optional uint32			EnmityDistance  = 40;	// ��޾���
	optional uint32			EnmityTime		= 41;	// ���ʱ��
	optional uint32			ClearTimer		= 42;	// ��վʱ��(��Ϊ��λ)
	optional uint32			Exp				= 43;	// ����������õ�����
	optional uint32			InitMoney		= 44;	// ����������õ���ʼ��Ǯ
	optional uint32			DeltaMoney		= 45;	// ����������õ���Ǯ����ֵ
	optional uint32			Resist			= 46;	// ����״̬�б�
	optional uint32			TranID			= 47;	// ����ת��ID
	optional uint32			PkType			= 48;	// PK����
	optional uint32			GroupID			= 49;	// ��ӪID
	optional uint32			SkillID			= 50;	// ����ID
	optional uint32			SkillLevel		= 51;	// ���ܵȼ�
	optional uint32			SearchDistance	= 52;	// ��������
	optional uint32			LeftTime		= 57;	// ���ʱ��(��)(��ʱ��͸ɵ�)
	optional uint32			ResShow			= 58;	// ������ʾ
	repeated uint32		    FailTaskID		= 59;	// NPC��ʧ�� ����ʧ��
	optional uint32			JusticeValue	= 60;	// ����������õ�������ֵ
	optional uint32			BuffImmunity	= 61;	// ����Buff״̬�б�
	optional uint32			ObtainTitle		= 62;	// ɱ�����ֻ�õĳƺ�ID
	optional uint32			AwardID			= 63;	// ��ȡ����
	optional uint32			LmtLineID		= 64;	// ���Ƶķ�����ID
	optional uint32			RedstoneID		= 65;	// �ڵ�ID
	optional uint32			OgreEvent		= 66;	// ���������¼�
	optional uint32			CorpsValue		= 67;	// ����Ļ���ֵ
	optional uint32			DropsDescID		= 69;	// �����������
	optional uint32			DiffcultIndex		= 70;	// �����Ѷ�ϵ��
	optional uint32			DiffcultAward		= 71;	// �����ѶȽ�������
};

//**********************************
// PBOgreBox ����
//**********************************
message PBBox_Click
{
	optional uint32 Event								= 1;
	optional uint32 Probability							= 2;
};

message PBOgreBox
{
	optional PBOgreProperty	OgreInfo		= 1;	// ��������
	repeated PBBox_Click		Click			= 2;	// ����¼� 
	optional uint32			BoxType			= 3;	// ��������
	optional uint32			KeyID			= 4;	// Կ��ID
};

//**********************************
// PBShowPet ���ͳ�
//**********************************

message PBShowPet
{
	optional uint32			TempID			= 1;	// ģ��ID
	optional string			Name			= 2;	// ��Ϸ�е���ʾ����
	optional string			Model			= 3;	// ģ��·��
	optional string			IconName		= 4;	// ͼ��·��
	optional uint32			MetierID		= 5;	// �ʺϵ�ְҵ
	optional uint32			MaxLevel		= 6;	// ����ȼ�����
	optional uint32			LevelRequire	= 7;	// ����ҵĵȼ�Ҫ��
	optional uint32			ExceedLevel		= 8;	// �����Ը߳���Ҷ��ټ�
	optional uint32			PetItemID		= 9;	// �ӳ��ﵰ�����ɳ�����Ҫ��rmb����id
	optional uint32			RevertCost		= 10;	// �ӳ��ﻹԭ�ɳ��ﵰ��Ҫ��ȡ�������
	optional uint32			InitStorage		= 11;	// ��ʼ�ֿ������
	optional uint32			LevelIncStorage = 12;	// ����ÿ�����ټ��ֿ������������
	optional uint32			IncStorage		= 13;	// ������Ϊ����ÿ�����ӵĲֿ������
	optional uint32			ExpPerMin		= 14;	// ÿ���ӹ��ͳ��õľ���
	optional uint32			RepletionLimit	= 15;	// ��ʳ������
	optional uint32			RepletionHP		= 16;	// ������ı�ʳ�ȴﵽʲô��ֵʱ������ս��״̬�»�Ѫ
	optional uint32			RevertHPValue	= 17;	// ��������������ս��״̬�»�Ѫʱһ�λض���
	optional uint32			MinRepletion1	= 18;	// ״̬1�ı�ʳ������
	optional uint32			MaxRepletion1	= 19;	// ״̬1�ı�ʳ������
	optional uint32			ExpSpeedRate1	= 20;	// ��״̬1�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	optional uint32			MinRepletion2	= 21;	// ״̬2�ı�ʳ������
	optional uint32			MaxRepletion2	= 22;	// ״̬2�ı�ʳ������
	optional uint32			ExpSpeedRate2	= 23;	// ��״̬2�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	optional uint32			MinRepletion3	= 24;	// ״̬3�ı�ʳ������
	optional uint32			MaxRepletion3	= 25;	// ״̬3�ı�ʳ������
	optional uint32			ExpSpeedRate3	= 26;	// ��״̬3�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	optional uint32			MinRepletion4	= 27;	// ״̬4�ı�ʳ������
	optional uint32			MaxRepletion4	= 28;	// ״̬4�ı�ʳ������
	optional uint32			ExpSpeedRate4	= 29;	// ��״̬4�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	optional uint32			MinRepletion5	= 30;	// ״̬5�ı�ʳ������
	optional uint32			MaxRepletion5	= 31;	// ״̬5�ı�ʳ������
	optional uint32			ExpSpeedRate5	= 32;	// ��״̬5�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	optional uint32			FoodCombo		= 33;	// �ɳԵ�ʳ�����
};

//**********************************
// PBBattlePet ս����
//**********************************

message PBBattlePet
{
	optional uint32			TempID					= 1;	// ģ��ID
	optional string			Name					= 2;	// ��Ϸ�е���ʾ����
	optional string			Model					= 3;	// ģ��·��
	optional string			IconName				= 4;	// ͼ��·��
	optional uint32			MetierID				= 5;	// �ʺϵ�ְҵ
	optional uint32			MaxLevel				= 6;	// ����ȼ�����
	optional uint32			LevelRequire			= 7;	// ����ҵĵȼ�Ҫ��
	optional uint32			ExceedLevel				= 8;	// �����Ը߳���Ҷ��ټ�
	optional uint32			PetItemID				= 9;	// �ӳ��ﵰ�����ɳ�����Ҫ��rmb����id
	optional uint32			RevertCost				= 10;	// �ӳ��ﻹԭ�ɳ��ﵰ��Ҫ��ȡ�������
	optional uint32			RepletionLimit			= 11;	// ��ʳ������
	optional uint32			MinRepletion1			= 12;	// ״̬1�ı�ʳ������
	optional uint32			MaxRepletion1			= 13;	// ״̬1�ı�ʳ������
	optional uint32			ExpSpeedRate1			= 14;	// ��״̬1�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	optional uint32			HPRate1					= 15;	// ��״̬1�³����hp������������
	optional uint32			AttackRate1				= 16;	// ��״̬1�³���Ĺ�����������
	optional uint32			MinRepletion2			= 17;	// ״̬2�ı�ʳ������
	optional uint32			MaxRepletion2			= 18;	// ״̬2�ı�ʳ������
	optional uint32			ExpSpeedRate2			= 19;	// ��״̬2�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	optional uint32			HPRate2					= 20;	// ��״̬2�³����hp������������
	optional uint32			AttackRate2				= 21;	// ��״̬2�³���Ĺ�����������
	optional uint32			MinRepletion3			= 22;	// ״̬3�ı�ʳ������
	optional uint32			MaxRepletion3			= 23;	// ״̬3�ı�ʳ������
	optional uint32			ExpSpeedRate3			= 24;	// ��״̬3�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	optional uint32			HPRate3					= 25;	// ��״̬3�³����hp������������
	optional uint32			AttackRate3				= 26;	// ��״̬3�³���Ĺ�����������
	optional uint32			MinRepletion4			= 27;	// ״̬4�ı�ʳ������
	optional uint32			MaxRepletion4			= 28;	// ״̬4�ı�ʳ������
	optional uint32			ExpSpeedRate4			= 29;	// ��״̬4�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	optional uint32			HPRate4					= 30;	// ��״̬4�³����hp������������
	optional uint32			AttackRate4				= 31;	// ��״̬4�³���Ĺ�����������
	optional uint32			MinRepletion5			= 32;	// ״̬5�ı�ʳ������
	optional uint32			MaxRepletion5			= 33;	// ״̬5�ı�ʳ������
	optional uint32			ExpSpeedRate5			= 34;	// ��״̬5�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	optional uint32			HPRate5					= 35;	// ��״̬5�³����hp������������
	optional uint32			AttackRate5				= 36;	// ��״̬5�³���Ĺ�����������
	optional uint32			HPValue					= 37;	// ����ֵ
	optional uint32			HPPotential				= 38;	// ����ֵǱ��
	optional uint32			MPValue					= 39;	// ����ֵ
	optional uint32			MPPotential				= 40;	// ����ֵǱ��
	optional uint32			PAttack					= 41;	// ��������
	optional uint32			PAttackPotential		= 42;	// ��������Ǳ��
	optional uint32			MAttack					= 43;	// ����������
	optional uint32			MAttackPotential		= 44;	// ����������Ǳ��
	optional uint32			PDefence				= 45;	// �������
	optional uint32			PDefencePotential		= 46;	// �������Ǳ��
	optional uint32			MDefence				= 47;	// ��������
	optional uint32			MDefencePotential		= 48;	// ��������Ǳ��
	optional uint32			PResist					= 49;	// ��������
	optional uint32			PResistPotential		= 50;	// ��������Ǳ��
	optional uint32			MResist					= 51;	// ��������
	optional uint32			MResistPotential		= 52;	// ��������Ǳ��
	optional uint32			AbnResist				= 53;	// �쳣״̬��������
	optional uint32			AbnResistPotential		= 54;	// �쳣״̬��������Ǳ��
	optional uint32			FireResist				= 55;	// ����ϵ����
	optional uint32			FireResistPotential		= 56;	// ����ϵ����Ǳ��
	optional uint32			WindResist				= 57;	// ŭ��ϵ����
	optional uint32			WindResistPotential		= 58;	// ŭ��ϵ����Ǳ��
	optional uint32			LightResist				= 59;	// ����ϵ����
	optional uint32			LightResistPotential	= 60;	// ����ϵ����Ǳ��
	optional uint32			ShadowResist			= 61;	// ����ϵ����
	optional uint32			ShadowResistPotential	= 62;	// ����ϵ����Ǳ��
	optional uint32			WaterResist				= 63;	// ����ϵ����
	optional uint32			WaterResistPotential	= 64;	// ����ϵ����Ǳ��
	optional uint32			EarthResist				= 65;	// ����ϵ����
	optional uint32			EarthResistPotential	= 66;	// ����ϵ����Ǳ��
	optional uint32			FoodCombo				= 67;	// �ɳԵ�ʳ�����
};

//**********************************
// PBMine ��
//**********************************

message PBMineOutput
{
	optional uint32		StuffID		= 1;
	optional uint32		Percent		= 2;
};
message PBMineOgre
{
	optional uint32		NpcID		= 1;
	optional uint32		Number		= 2;
	optional uint32		Percent		= 3;
};

message PBMine
{
	optional uint32				TempID				= 1;	// ģ��ID
	optional string				Name				= 2;	// ��Ϸ�е���ʾ����
	optional uint32				Level				= 3;	// �ȼ�
	optional uint32				LevelRequire		= 4;	// �ȼ�����
	optional uint32				ToolID				= 5;	// ����Ҫ�Ĺ�������
	optional uint32				DecRate				= 6;	// ���Ĳɾ��þ�
	optional uint32				MineTimeLow			= 7;	// �ɿ�ʱ�����ޣ��룩
	optional uint32				MineTimeHigh		= 8;	// �ɿ�ʱ�����ޣ��룩
	optional string				Model				= 9;	// ģ��·������
	repeated PBMineOutput		Output				= 10;	// ����
	repeated PBMineOgre			MineOgre			= 11;	// ��
};

//---------------------------------------------
// ����
//---------------------------------------------

//**********************************
// PBSkillTreeNode �������ڵ�
//**********************************

message PBSkillTreeNode
{
	optional uint32				SkillID				= 1;	// ����ID
	optional uint32				MaxLevel			= 2;	// ���ȼ�( ����ܵ�Ͷ���� )
	optional uint32				NeedSkillID			= 3;	// ��Ҫ��ǰ������
	optional uint32				NeedSkillPoint		= 4;	// ��Ҫ��ǰ������Ͷ����
	optional uint32				NeedGenerID			= 5;	// ��ҪͶ���ϵ��ID
	optional uint32				NeedGenerPoint		= 6;	// ��ҪͶ���ϵ��Ͷ����
	optional uint32				Level				= 7;	// ��Ҫ����ҵȼ�
	optional uint32				NeedBook			= 8;	// �Ƿ���Ҫ��Ӧ�ļ�����
};

//**********************************
// PBSkillTree ������
//**********************************

message PBSkillTree
{
	optional uint32				TempID				= 1;	// ģ��ID
	optional string				GenerName			= 2;	// ϵ������
	optional uint32				GenerID				= 3;	// ϵ��ID
	repeated PBSkillTreeNode	SkillNode			= 4;	// 
};

//**********************************
// PBSkill ���ܻ�����Ϣ
//**********************************

message PBCost
{
	optional uint32		CostType	= 1;
	repeated uint32		CostParam	= 2;
};
message PBUseCondition
{
	optional uint32		ConditionType	= 1;
	optional uint32		Param			= 2;
};

message PBSkill
{	
	optional uint32				TempID			= 1;	// ģ��ID
	optional string				Name			= 2;	// ��������
	optional uint32				SkillID			= 3;	// ����ID
	optional uint32				RequireWeapon	= 4;	// ������Ҫ���������
	optional uint32				MetierID		= 5;	// ��������ְҵ
	optional uint32				GenerID			= 6;	// ��������ְҵϵ��
	optional uint32				SkillLevel		= 7;	// ���ܵȼ�
	optional string				SkillIcon		= 8;	// ����ͼ��
	optional string				SkillDescribe	= 9;	// ��������
	optional uint32				FireType		= 10;	// �ͷ���̬
	optional uint32				SkillType		= 11;	// ��������
	optional uint32				TimeType		= 12;	// ʱ������
	optional uint32				AniTime			= 13;	// ʩ��ʱ�伴����ʱ��(����)
	optional uint32				FireTime		= 14;	// ����ʱ��(����)
	optional uint32				CDTime			= 15;	// ��ȴʱ��(����)
	repeated PBCost				Cost			= 16;	// ����ֵ
	optional uint32				NeedDelay		= 17;	// �����Ƿ���Ҫ�ӳټ����˺�
	optional uint32				SkillFuncID1	= 18;	// ��Ӧ��1���Ч��ID
	repeated uint32				Parameter1		= 19;	// ��1��Ч��ID��Ӧ��ֵ
	optional uint32				SkillFuncID2	= 20;	// ��Ӧ��2���Ч��ID
	repeated uint32				Parameter2		= 21;	// ��2��Ч��ID��Ӧ��ֵ
	optional uint32				SkillFuncID3	= 22;	// ��Ӧ��3���Ч��ID
	repeated uint32				Parameter3		= 23;	// ��3��Ч��ID��Ӧ��ֵ
	optional uint32				SkillFuncID4	= 24;	// ��Ӧ��4���Ч��ID
	repeated uint32				Parameter4		= 25;	// ��4��Ч��ID��Ӧ��ֵ
	optional string				SkillAction		= 26;	// ���ܶ���
	optional uint32				AutoRepeat		= 27;	// �Ƿ��Զ��ظ�
	optional uint32				AutoNormalAttack = 28;	// �Ƿ��Զ���ͨ����
	optional uint32				AutoCoolingSkill = 29;	// �Ƿ���ȴ���м���
	repeated PBUseCondition		UseCondition	= 30;	// ����ʹ������
	optional uint32				StudyGold		= 31;	// ѧϰ����������
	optional uint32				StudyBindMoney	= 32;	// ѧϰ�����������Ƿ��
	optional uint32				SkillListShowType = 33;	// �����б���ʾ����
	optional uint32				SkillTempType	= 34;	// ����ģ������
	optional uint32				StudySkillLevel	= 35;	// ѧϰ������������ȼ�
	optional uint32				InsertAutoState	= 36;	// �Ƿ�����Զ��ظ�����״̬
	optional uint32				BreakAutoState	= 37;	// �Ƿ����Զ��ظ�����״̬
	optional uint32				NeedTarget		= 38;	// �Ƿ���Ҫ����Ŀ��
	optional uint32				NeedPet			= 39;	// �Ƿ���Ҫ�ٻ���
	optional uint32				ActionCamp		= 40;	// ��ʩ����Ӫ
	optional uint32				DamageType		= 41;	// �˺�����
	optional uint32				BindStudyGold	= 42;	// ѧϰ�����������Ƿ�֧�ְ󶨽�
	optional uint32				AttackFix		= 43;	// ���ܹ������̶�ֵ
	optional uint32				AttackPer		= 44;	// ���ܹ������ٷֱ�
	optional uint32				ResType			= 45;	// ���Թ������
	optional uint32				ResValue		= 46;	// ���Թ�����ֵ
	optional uint32				IsMWSkill		= 47;	// �Ƿ񷨱�����
	optional string				SkillTypeDesc	= 48;	// ������������
	optional uint32				IsMWOffset		= 49;	// �����Ƿ�ƫ��λ��
	repeated uint32				CDGroup			= 50;	// ��ȴ��
	optional uint32				CanClean		= 51;	// �Ƿ񲻿��Ա�ϴ
	optional uint32				TargetLevel		= 52;	// ʩ��Ŀ��ȼ�����
	optional uint32				SummonIndex		= 53;	// �ٻ�������
};

//**********************************
// PBAureoleSkill �⻷����
//**********************************

message PBAureoleType
{
	optional uint32		AureoleArea = 1;
	optional uint32		BuffID		= 2;
};

message PBAureoleSkill
{	
	optional PBSkill			SkillInfo		= 1;	// ���ܻ�����Ϣ
	optional uint32				Inceessary		= 2;	// �Ƿ��������
	optional uint32				InceessaryTime	= 3;	// ��������ʱ����
	repeated PBCost				Cost			= 4;
	optional uint32				AureoleDistance	= 5;	// Ӱ�췶Χ
	repeated PBAureoleType		AureoleType		= 6;	// �⻷��������
};

//**********************************
// PBNormalSkill ��ͨ����
//**********************************

message PBNormalSkill
{
	optional PBSkill			SkillInfo		= 1;	// ���ܻ�����Ϣ
	optional uint32				SkillHitrate	= 2;	// ����׼ȷ��	
	optional uint32				MinDistance		= 3;	// ��ʼ��������
	optional uint32				MaxDistance		= 4;	// ׷������
	optional uint32				EfktMaxNum		= 5;	// �����������
	optional uint32				AttackRange		= 6;	// ������Χ����
	repeated uint32				RandParam		= 7;	// ��Χ������n����(1,2)
	repeated uint32				BuffGroupID		= 8;	// Buff��
	optional uint32				ContinuedRule	= 9;	// ���ܴ������
	optional uint32				ContinuedTime	= 10;	// �����������ʱ��
	optional uint32				ContinuedNum	= 11;	// ��������
	optional uint32				IgnoreArmor		= 12;	// ���Ի���ֵ	
};

//**********************************
// PBTrapSkill ���弼��
//**********************************

message PBTrapSkill
{
	optional PBSkill			SkillInfo		= 1;	// ���ܻ�����Ϣ
	optional uint32				LastTime		= 2;	// ����ʱ��
	optional uint32				ApplyType		= 3;	// ��������
	optional uint32				TouchRange		= 4;	// ������Χ���뾶��
	optional uint32				ApplyRange		= 5;	// ���÷�Χ���뾶��
	optional string				TrapRes			= 6;	// ������Դ
	repeated uint32				BuffGroupID		= 7;	// Buff��
	repeated uint32				Condition		= 8;	// ��������
	optional uint32				EffectMaxNumber = 9;	// �����������
};

//---------------------------------------------
// Buff
//---------------------------------------------

//**********************************
// PBBuff buffģ��
//**********************************

message PBBuffFunc
{
	optional uint32		FuncType		= 1;
	repeated uint32		Parame			= 2;
};

message PBBuff
{
	optional uint32				TempID			= 1;	// ģ��ID
	optional uint32				BuffServiceID	= 2;	// Buff��ϵ��ID
	optional uint32				IdenValue		= 3;	// Buff������ֵ
	optional uint32				BuffStyle		= 4;	// Buff��������
	optional uint32				FirstActiveTime	= 5;	// �״�����ʱ����
	optional uint32				ActiveTime		= 6;	// ����ʱ����
	repeated PBBuffFunc			BuffFunc		= 7;	// ��n������Ӧ�Ĺ�����ֵ
	optional string				BuffName		= 8;	// Buff����ʾ����
	optional string				BuffIcon		= 9;	// Buff��ͼ��
	optional string				BuffDescribe	= 10;	// Buff����ʾ������ʾ
	optional uint32				Hitrate			= 11;	// Buff�ľ������и���
	optional uint32				BuffValue		= 12;	// Buffֵ
	optional uint32				ResistType		= 13;	// Buff����ϵ��
	optional uint32				LastTime		= 14;	// Buff����ʱ�����(0��ʾ��������1��,��1��,-1Ϊ����)
	optional uint32				BuffType		= 15;	// Buff����
	optional uint32				CancelBuff		= 16;	// Buff�Ƿ�����ֶ�ȡ��
	optional uint32				EnableBattle	= 17;	// Buff�Ƿ��ܹ�����ս��
	optional string				BuffAni			= 18;	// Buff�Ķ�����Ч
	optional uint32				BuffRow			= 19;	// Buff��ʾ����
	optional uint32				BuffDieDel		= 20;	// Buff�������Ƿ���ʧ
	optional uint32				TimerType		= 21;	// Buff��ʱ������
	optional uint32				BuffClear		= 22;	// Buff�ܷ����
	optional uint32				BuffMapID		= 23;	// �ض���ͼID
	optional uint32				BuffLineID		= 24;	// �ض���ID
	optional uint32				SkillLevel		= 25;	// �˺�����
	optional uint32				BuffMapType		= 26;	// Buff��ͼ����
	optional uint32				CountryBuff		= 27;	// ����Buff
	optional uint32				BuffSuperposition = 28; // Buff��������
	optional uint32				Accurate		= 29;	// ����
	optional uint32				OffRemove		= 30;	// �����Ƿ���ʧ
	optional uint32				Transform		= 31;	// �Ƿ��Ʊ���
	optional uint32				RemoveCountID	= 32;	// Buffȥ�����ӵ�ID
};

//**********************************
// PBLevelExp �ȼ������
//**********************************

message PBLevelExp
{
	optional uint32				TempID			= 1;	// ģ��ID
	repeated uint64				LevelExp		= 2;	// ������N���ľ���ֵ
};

//**********************************
// PBLevelMoneyLmt �ȼ���Ǯ���Ʊ�
//**********************************
message PBSingleMoneyLmt
{
	optional uint32				BagMoneyLmt				= 1;	// �����ǰ󶨽�
	optional uint32				BagBindMoneyLmt			= 2;	// �����󶨽�
	optional uint32				StorageMoneyLmt			= 3;	// �ֿ�ǰ󶨽�
	optional uint32				StorageBindMoneyLmt		= 4;	// �ֿ�󶨽�
};

message PBLevelMoneyLmt
{
	optional uint32				TempID					= 1;	// ģ��ID
	repeated PBSingleMoneyLmt	LmtTable				= 2;
};


//**********************************
// PBPetLevelExp ���ﾭ���
//**********************************

message PBPetLevelExp
{
	optional uint32				TempID			= 1;	// ģ��ID
	repeated uint32				LevelExp		= 2;	// ������N���ľ���ֵ
};

//**********************************
// PBProduceExp ���������
//**********************************

message PBProduceExp
{
	optional uint32				TempID			= 1;	// ģ��ID
	repeated uint32				LevelExp		= 2;	// ��n���ľ���ֵ
};

//**********************************
// PBEquipUpg װ��������
//**********************************

message PBUpg
{
	optional uint32		Success		= 1;	// �ɹ��ĸ���
	optional uint32		Failure		= 2;	// ʧ�ܵĸ���
	optional uint32		Result		= 3;	// ʧ�ܺ�Ľ��
	optional uint32		IncLevel	= 4;	// �����ɹ��������ĵȼ�
	optional uint32		ExtSuccess	= 5;	// �������ĳɹ�����
};

message PBEquipUpg
{
	optional uint32				TempID			= 1;	// ģ��ID
	repeated PBUpg				EquipUpg		= 2;	// ����
};

//**********************************
// PBSuitProducer ��������װ
//**********************************

message PBSuitProducer
{
	optional uint32				TempID			= 1;	// ģ��ID
	repeated uint32				PropertyTempID	= 2;	// ȫ��n��װ����ͬ1�����������ĸ�������ID
	repeated uint32				UpgTempID		= 3;	// ȫ��+nװ����m������ĸ�������ID
	repeated uint32				ExtTempID		= 4;	// ȫ��װ����m�����̵ĸ�������ID
	repeated string				DescribeText	= 5;	// ��������n������
};

//**********************************
// PBSuitNormal ��ͨ��װ
//**********************************

message PBSuitNormal
{
	optional uint32				TempID			= 1;	// ģ��ID
	optional string				Name			= 2;	// ��װ����
	repeated uint32				EquipTempID		= 3;	// ��װ��Ҫ��װ��ID
	optional string				ActiveTitle		= 4;	// ��װ�������ҳƺ�
	repeated uint32				PropertyTempID	= 5;	// ��װ�������Ҹ�������ID
};

//**********************************
// PBSpell ��������
//**********************************

message PBSpell
{
	optional uint32				TempID			= 1;	// ģ��ID
	optional string				Name			= 2;	// ���׷�����ʾ����
	optional uint32				SuitID			= 3;	// ��װ���
	repeated uint32				LetterID		= 4;	// ���׷�����Ҫ������
	repeated uint32				Require			= 5;	// ���׷��ļ���ĵ�һ���������Ҫ������
	repeated uint32				PropertyTempID	= 6;	// ���׷��ļ���ĵ�m�������n  [m][n]
	repeated string				DescribeText	= 7;	// ��������n������
};

//**********************************
// PBProduceEquip ����װ��
//**********************************

message PBProduceEquip
{
	optional uint32				TempID			= 1;	// ģ��ID
	optional uint32				Type			= 2;	// װ������
	optional uint32				DetailID1		= 3;	// װ������ϸ���
	optional uint32				DetailID2		= 4;	// ���ߵ���ϸ����
	optional uint32				Level			= 5;	// װ���ȼ�
	optional string				Name			= 6;	// װ������
	optional uint32				MaterialID		= 7;	// ����ID
	optional uint32				MaterialNum		= 8;	// ��������
	optional uint32				MaterialRank	= 9;	// ���ϵȼ�
	optional uint32				ItemID1			= 10;	// ����1ID
	optional uint32				ItemRand1		= 11;	// ����1����
	optional uint32				ItemID2			= 12;	// ����2ID
	optional uint32				ItemRand2		= 13;	// ����2����
	optional uint32				ItemID3			= 14;	// ����3ID
	optional uint32				ItemRand3		= 15;	// ����3����
	optional uint32				Money			= 16;	// ��������
	optional uint32				BindMoney		= 17;	// �Ƿ�󶨽�Ǯ
	optional uint32				IconID			= 18;	// ͼ��ID
	optional string				Describe		= 19;	// װ��˵��
	optional uint32				Exp				= 20;	// ���þ���
};

//**********************************
// PBProducePhysic ҩƷ����
//**********************************

message PBProducePhysic
{
	optional uint32				TempID			= 1;	// ģ��ID
	optional uint32				Type			= 2;	// ҩƷ����
	optional uint32				Level			= 3;	// ҩƷ�ȼ�
	optional string				Name			= 4;	// ҩƷ����
	optional uint32				MaterialID		= 5;	// ����ID
	optional uint32				MaterialNum		= 6;	// ��������
	optional uint32				ItemID			= 7;	// ����ID
	optional uint32				Exp				= 8;	// ���þ���
	optional uint32				Money			= 9;	// ��������
	optional uint32				BindMoney		= 10;	// �Ƿ�󶨽�Ǯ
};

//**********************************
// PBOpenSlot ���۱�
//**********************************

message PBOpenSlot
{
	optional uint32				TempID			= 1;	// ģ��ID
	repeated uint32				SlotLevel		= 2;	// �򿪵�n����ʱ��Ҫ�ĵȼ�
	repeated uint32				SlotNumber		= 3;	// �򿪵�n����ʱ��Ҫ������
};

//**********************************
// PBCompose �ϳ�
//**********************************

message PBCompose
{
	optional uint32				TempID			= 1;	// ģ��ID
	optional uint32				MaterialID		= 2;	// �ϳ���Ҫ�Ĳ���ID
	optional uint32				MaterialNum		= 3;	// �ϳ���Ҫ�Ĳ�������
	optional uint32				ItemID			= 4;	// �ϳɵõ�����ƷID
	optional uint32				ItemNum			= 5;	// �ϳɵõ�����Ʒ����
};

//**********************************
// PBMultiCompose ���Ӻϳ�
//**********************************

message PBMultiCompose
{
	optional uint32				TempID				= 1;	// ģ��ID
	optional string				Describe			= 2;	// �ϳ�����
	repeated uint32				MaterialID			= 3;	// �ϳ���Ҫ�Ĳ���ID
	repeated uint32				MaterialNum			= 4;	// �ϳ���Ҫ�Ĳ�������
	repeated uint32				ItemID				= 5;	// �ϳɵõ�����ƷID
	repeated uint32				ItemNum				= 6;	// �ϳɵõ�����Ʒ����
	optional uint32				Exp					= 7;	// �ϳɵõ��ľ���
	optional uint32				Order				= 8;	// �ϳɱ��		 	
	optional uint32				LifeSkillType		= 9;	// ���������
	optional uint32				LifeSkillKind		= 10;	// ��������
	optional uint32				SpecializedDegree	= 11;	// ѧϰ�䷽����Ҫ��������
	optional uint32				LifeComposeType		= 12;	// �䷽����
	optional uint32				CreatValue			= 13;	// ��������Ҫ�Ļ��(��⿵ȼ����䷽�о���)
	optional uint32				StudyMoney			= 14;	// ѧϰ�䷽��Ҫ���ѵĽ�Ǯ
	optional uint32				SkillCreatDegree	= 15;	// �о����䷽��ȡ��������
	repeated uint32				value				= 16;	// ���������ȺͲɼ���Ҫ�������ȵĲ�ֵ����
	repeated uint32				Probality			= 17;	// �����������ȺͲɼ���Ҫ�������ȵ���Ӧ��ֵ�����ȡ�����ȵĸ���
	repeated uint32				DegreeValue			= 18;	// �����������ȺͲɼ���Ҫ�������ȵ���Ӧ��ֵ�����ȡ�����ȵ�ֵ
	optional uint32				ApNeedCost			= 19;	// �䷽ѧϰ��Ҫ���ĵĻ���ֵ
	optional uint32				UsedTimes			= 20;	// �䷽��ʹ�ô���
	optional uint32				MinValue			= 21;	// ��ֵ��С��Χ( �����䷽ʱ���ֵ��ģ��ֵ���õĻ��ֵС�ڸ�ֵʱ���㴴��ɹ� )
	optional uint32				ComposeType			= 22;	// �䷽����
	optional uint32				EquipMetierType		= 23;	// װ���һ�ʱ�����õ�ְҵ����
	optional uint32				SrcEquipID			= 24;	// Դװ��ID
	optional uint32				DesEquipID			= 25;	// ����װ��ID
	optional uint32				Contribute			= 26;	// �ϳ���Ҫ�Ĺ��׶�	
	repeated uint32				UpgItemID			= 27;	// ������Ҫ�Ĳ���ID
	repeated uint32				UpgItemNum			= 28;	// ������Ҫ�Ĳ�������
	repeated uint32				NeedValueType		= 29;	// �ϳ���Ҫ����ֵ����
	repeated uint32				NeedValue			= 30;	// �ϳ���Ҫ����ֵ
};  

//**********************************
// PBTeleTable ���ͱ�
//**********************************

message PBTeleTable
{
	optional uint32				TempID			= 1;	// ģ��ID
	repeated uint32				LineID			= 2;	// ���ͼID(��ID)
	repeated uint32				MapID			= 3;	// ��ͼID
	repeated uint32				PosX			= 4;	// X����
	repeated uint32				PosY			= 5;	// Y����
	repeated string				Describe		= 6;	// ����
	repeated uint32				Money			= 7;	// ����
	optional uint32				BindMoney		= 8;	// �Ƿ�󶨽�Ǯ
	repeated uint32				NeedTempID		= 9;	//  ������Ʒ
	repeated uint32				NeedBuffID		= 10;	// ����buff
	repeated uint32				NeedLevel		= 11;	// ����ȼ�
};

//**********************************
// PBData ��ֵ������
//**********************************

message PBData
{
	optional uint32				TempID			= 1;	// ģ��ID
	repeated uint32				LevelFix		= 2;	// ���������n��������
	repeated uint32				TeamFix			= 3;	// �������n�ĵ�������
};

//**********************************
// PBSummonBeast �ٻ���
//**********************************

message PBPetData
{
	optional uint32		NameColor		= 1;	// �ٻ���������ɫ
	optional uint32		AttackType		= 2;	// ��������
	optional uint32		PAttackUp		= 3;	// �ٻ���������������
	optional uint32		PAttackLow		= 4;	// �ٻ���������������
	optional uint32		MAttackUp		= 5;	// �ٻ��޷�������������
	optional uint32		MAttackLow		= 6;	// �ٻ��޷�������������
	optional uint32		Speed			= 7;	// �ٻ����ƶ��ٶ�
	optional uint32		PDefence		= 8;	// �ٻ����������
	optional uint32		MDefence		= 9;	// �ٻ��޷�������
	optional uint32		MaxHP			= 10;	// �ٻ���HP����
	optional uint32		HPRSpeed		= 11;	// �ٻ���HP�ָ�����
	optional uint32		DeathRate		= 12;	// �ٻ�����������
	optional uint32		DeathValue		= 13;	// �ٻ��������˺�
	optional uint32		NormalDuck		= 14;	// �ٻ����չ�����ֵ
	optional uint32		SkillDuck		= 15;	// �ٻ��޼�������ֵ
	optional uint32		SkillID			= 16;	// ����ID
	optional uint32		SkillLevel		= 17;	// ���ܵȼ�
	optional uint32		PAttackRange	= 18;	// �ٻ�����������Χ
	optional uint32		MAttackRange	= 19;	// �ٻ��޷���������Χ
	optional uint32		PReducePer		= 20;	// �ٻ����������
	optional uint32		MReducePer		= 21;	// �ٻ��޷�������
	optional uint32		DeathDefense	= 22;	// �ٻ�����������
	optional uint32		IgnoreDuck		= 23;	// �ٻ��޺�������ֵ
	repeated uint32		ResDef			= 24;	// ����
	repeated uint32		ResAtt			= 25;	// ���Թ���
	optional uint32		AttPercent		= 26;	// �����ӳ�
	optional uint32		DefPercent		= 27;	// �����ӳ�
	optional uint32		HPPercent		= 28;	// �����ӳ�
};

message PBSummonBeast
{
	optional uint32			TempID				= 1;	// ģ��ID
	optional string			Name				= 2;	// ��Ϸ�е���ʾ����
	optional string			Model				= 3;	// ģ��·��
	optional uint32			Level				= 4;	// �ٻ��޵ȼ�
	repeated uint32			LevelUpDelayTime	= 5;	// ������n������ʱ��	
	repeated PBPetData		PetData				= 6;	// �ٻ�������
	optional uint32			AttackFrequency		= 7;	// �ٻ��޹���Ƶ��
};

//**********************************
// PBBeginner ��������
//**********************************

message PBBeginner
{
	optional uint32			TempID				= 1;	// ģ��ID
	repeated uint32			EquipItemID			= 2;	// ������ƷID
	repeated uint32			EquipItemNum		= 3;	// ������Ʒ����
	repeated uint32			BaggageItemID		= 4;	// ������ƷID
	repeated uint32			BaggageItemNum		= 5;	// ������Ʒ����
	repeated uint32			SkillID				= 6;	// ����ID
	repeated uint32			SkillLevel			= 7;	// ���ܵȼ�
	optional uint32			StrNum				= 8;	// ������
	optional uint32			ConNum				= 9;	// ���ʵ�
	optional uint32			StaNum				= 10;	// ������
	optional uint32			WisNum				= 11;	// ������
	optional uint32			SprNum				= 12;	// �����
	optional uint32			SkillNum			= 13;	// ���ܵ�
	optional uint32			PoxX1				= 14;	// ����X����1
	optional uint32			PoxX2				= 15;	// ����X����2
	optional uint32			PoxY1				= 16;	// ����Y����1
	optional uint32			PoxY2				= 17;	// ����Y����2
	repeated uint32			SkillID1			= 18;	// תսʿ��n���ʼ����
	repeated uint32			SkillLevel1			= 19;	// תսʿ��n���ʼ���ܵȼ�
	repeated uint32			SkillID2			= 20;	// ת���͵�n���ʼ����
	repeated uint32			SkillLevel2			= 21;	// ת���͵�n���ʼ���ܵȼ�
	repeated uint32			SkillID3			= 22;	// ת���˵�n���ʼ����
	repeated uint32			SkillLevel3			= 23;	// ת���˵�n���ʼ���ܵȼ�
	repeated uint32			SkillID4			= 24;	// ת��ʦ��n���ʼ����
	repeated uint32			SkillLevel4			= 25;	// ת��ʦ��n���ʼ���ܵȼ�
	repeated uint32			SkillID5			= 26;	// ת��ʿ��n���ʼ����
	repeated uint32			SkillLevel5			= 27;	// ת��ʿ��n���ʼ���ܵȼ�
	repeated uint32			SkillID6			= 28;	// ת����ʦ��n���ʼ����
	repeated uint32			SkillLevel6			= 29;	// ת����ʦ��n���ʼ���ܵȼ�
	optional uint32			BeginnerProtectLevel = 30;	// ���ֱ����ȼ�
	optional uint32			TransProtectTime	= 31;	// �糡������ʱ��
	optional uint32			MapID				= 32;	// ������ͼ
	optional uint32			DeathDuraRate		= 33;	// �������ʱװ�������;ö�ռװ��ȫ���;öȵ���ֱ�
	optional uint32			CanMendUseBindMoney = 34;	// ����װ��ʱ�Ƿ���ʹ�ð󶨽�Ǯ
	optional uint32			BeginnerAP			= 35;	// ��������ֵ
};

//**********************************
// PBLoopTaskAwds ������������
//**********************************

//message PBLoopTaskAwds
//{
//	optional uint32			TempID				= 1;	// ģ��ID
//	repeated uint32			Exp					= 2;	// ��m����ɵ�n����������
//	repeated uint32			Money				= 3;	// ��m����ɵ�n��������Ǯ
//};

//**********************************
// PBDropLevel ����ȼ�
//**********************************

message PBDropLevel
{
	optional uint32			TempID				= 1;	// ģ��ID
	repeated uint32			Ran					= 2;	// ��дn����n�ĸ���
};

//**********************************
// PBOgreTran ����ת����
//**********************************

message PBOgreTran
{
	optional uint32			TempID				= 1;	// ģ��ID
	repeated uint32			Drop				= 2;	// ��n���ĵ����
	repeated uint32			HP					= 3;	// ��n����HP
	repeated uint32			MP					= 4;	// ��n����MP
	repeated uint32			PA					= 5;	// ��n�����﹥
	repeated uint32			MA					= 6;	// ��n���ķ���
	repeated uint32			PD					= 7;	// ��n�������
	repeated uint32			MD					= 8;	// ��n���ķ���
	repeated uint32			Hit					= 9;	// ��n��������
	repeated uint32			Dodge				= 10;	// ��n���Ĳ�Ӱ
	repeated uint32			Exp					= 11;	// ��n���ľ���
	repeated uint32			Ignore				= 12;	// ��n���ĺ���
	repeated uint32			Death				= 13;	// ��n���ı���
	repeated uint32			ResDef				= 14;	// ��n���Ŀ���
	repeated uint32			ResAtt				= 15;	// ��n���Ĺ���
};

//**********************************
// PBMetierPro ְҵ���Ա�
//**********************************

message PBMetierPro
{
	optional uint32			TempID				= 1;	// ģ��ID
	optional uint32			MetierRequire		= 2;	// ְҵ����
	optional uint32			Option				= 3;	// ����ѡ��
	repeated uint32			MetierProperty		= 4;	// ��д�ȼ�n��Ӧ��n�����Ե�ֵ
};

//**********************************
// PBLevelProperty �ȼ����Ա�
//**********************************

message PBLevelProperty
{
	optional uint32			TempID				= 1;	// ģ��ID
	optional uint32			Option				= 2;	// ����ѡ��
	repeated uint32			LevelProperty		= 3;	// �ȼ�n��Ӧ������ֵ
};

//**********************************
// PBHonorToExp ��ѫ�����
//**********************************

message PBHonorToExp
{
	optional uint32			TempID				= 1;	// ģ��ID
	repeated uint32			Exp					= 2;	// �ȼ�n�õ��ľ���ֵ
	repeated uint32			Wizard				= 3;	// �ȼ�n�õ��ĲŻ�ֵ
	optional uint32			ExpLimit			= 4;	// ÿ�նһ�����������
	optional uint32			ItemID				= 5;	// �һ��õ�����Ʒ
	optional uint32			ItemHonor			= 6;	// �һ���Ʒ��������
	optional uint32			ItemLimit			= 7;	// ÿ�նһ���Ʒ����������
};

//**********************************
// PBHonorObtain ��ѫ��ñ�
//**********************************

message PBHonorObtain
{
	optional uint32			TempID				= 1;	// ģ��ID
	optional uint32			InLimit				= 2;	// ÿ���ܻ�õĹ�ѫ����
	optional uint32			OutLimit			= 3;	// ÿ���ܻ�õĹ�ѫ����
	optional uint32			OutDieExp			= 4;	// ����������õ��Ĺ�ѫ
	optional uint32			InDieExp			= 5;	// �ڱ��������õ��Ĺ�ѫ
	optional uint32			BorderDieExp		= 6;	// �����������õ��Ĺ�ѫ
	repeated uint32			OutLowExp			= 7;	// �ȼ�����Ŀ��n������õ��Ĺ�ѫ
	repeated uint32			OutHighExp			= 8;	// �ȼ�����Ŀ��n������õ��Ĺ�ѫ
	repeated uint32			InLowExp			= 9;	// �ȼ�����Ŀ��n�ڱ����õ��Ĺ�ѫ
	repeated uint32			InHighExp			= 10;	// �ȼ�����Ŀ��n�ڱ����õ��Ĺ�ѫ
	repeated uint32			BorderLowExp		= 11;	// �ȼ�����Ŀ��n�������õ��Ĺ�ѫ
	repeated uint32			BorderHighExp		= 12;	// �ȼ�����Ŀ��n�������õ��Ĺ�ѫ
	repeated uint32			LostLowExp			= 13;	// �ȼ�����Ŀ��n��ʧ�Ĺ�ѫ
	repeated uint32			LostHighExp			= 14;	// �ȼ�����Ŀ��n��ʧ�Ĺ�ѫ
	repeated uint32			BasicExp			= 15;	// ������ѫ
};

//**********************************
// PBDiploidTable ��˫��
//**********************************

message PBDiploidTable
{
	optional uint32			TempID				= 1;	// ģ��ID
	optional uint32			TotalTime			= 2;	// ÿ�ܿ���ȡ����ʱ��
	optional uint32			ValidMax			= 3;	// ��Ч˫������
	optional uint32			TypeNumber			= 4;	// ��ȡ��ʽ����
	repeated uint32			BuffID				= 5;	// ��ȡ��ʽ
};

//**********************************
// PBRedStone �ڵ�
//**********************************

message PBRedStone
{		
	optional PBItemBase		BaseItem			= 1;	// �ڵ��Ļ�����Ϣ	
	optional string			MagicIconName		= 2;	// ����ͼ������
	optional uint32			GuageTime			= 3;	// ���������Ľ�����ʱ��(����)
	optional uint32			MagicSustainTime	= 4;	// ������ʱ��(����)
	optional uint32			ExpTime				= 5;	// ����ʱ���侭���ʱ����(����)
	optional uint32			Radius				= 6;	// ����ʱ�����ð뾶
	optional uint32			RedStoneType		= 7;	// �ڵ�������
	optional uint32			FamilyExpRate		= 8;	// �����ڵ��ľ���ӳ�
	optional uint32			ExpTableID			= 9;	// �ڵ������ID
	optional uint32			NumberEffected		= 10;	// �ڵ��Ƿ�Ӱ�쾭��ӳ�
	optional uint32			MetierID			= 11;	// ����ID	
	repeated uint32			KeyBuffID			= 12;	// ����ĵ�%d��buffid
	repeated uint32			EncBuffID			= 13;	// ��%d�ּӳ�buffid
	repeated uint32			EncPercent			= 14;	// ��%d�ּӳɰٷֱ�
	optional uint32			IsEternal			= 15;	// �Ƿ�������
};

//**********************************
// PBRedStoneExpTable �ڵ��ȼ������
//**********************************

message PBRedStoneExpTable
{
	optional uint32			TempID				= 1;	// ģ��ID
	repeated uint32			Exp					= 2;	// ʹ���ڵ�ʱn�����ÿ�λ�õľ���ֵ
	optional string			EffectName			= 3;	// ���������Ч����
};

//**********************************
// PBReliveTable ����ѱ�
//**********************************

message PBReliveTable
{
	optional uint32			TempID				= 1;	// ģ��ID
	repeated uint32			Fee					= 2;	// �ȼ�n����ѽ�Ǯ��
	optional uint32			Rate				= 3;	// ϵ��
};

//**********************************
// PBQuestionExp ����ȼ������
//**********************************

message PBQuestionExp
{
	optional uint32			TempID				= 1;	// ģ��ID
	optional uint32			NpcQuestionNum		= 2;	// ÿ�ո���npc������Ŀ����
	repeated uint32			Exp					= 3;	// ����ʱ�ȼ�Ϊn����һ�õľ���
	optional uint32			NpcExpAddRate		= 4;	// ÿ�ո�����Ŀ����ӳɱ���(��������Ķ��ٱ�)
};

//**********************************
// PBBindChargeTable �󶨷��ñ�
//**********************************

message PBBindChargeTable
{
	optional uint32			TempID				= 1;
	optional uint32			MoneyBindNeed		= 2; // ��װ����Ҫ���ѵĽ�Ǯ
	optional uint32			CanBindUseBM		= 3; // ��װ���Ƿ�֧�ְ󶨽�Ǯ 1��ʾ֧��0��ʾ��֧��
	optional uint32			MoneyUnBindNeed		= 4; // ȡ��װ������Ҫ�Ľ�Ǯ
	optional uint32			UnBindUseBM			= 5; // ȡ��װ���Ƿ�֧�ְ󶨽�Ǯ 1��ʾ֧��0��ʾ��֧��
	optional uint32			MoneyResumeBind		= 6; // �ָ�����Ҫ�Ľ�Ǯ
	optional uint32			CanResumeBind		= 7; // �ָ����Ƿ�֧�ְ󶨽�Ǯ 1��ʾ֧��0��ʾ��֧��
};

//**********************************
// PBItemMineMap �ر�ͼ
//**********************************

message PBMinePos
{
	optional uint32			MapID		= 1;
	optional uint32			PosX		= 2;
	optional uint32			PosY		= 3;
	optional uint32			Probability = 4;
};

message PBMineEvent
{
	optional uint32			EventID		= 1;
	optional uint32			TouchRate	= 2;
};

message PBItemMineMap
{
	optional PBItemBase		BaseInfo			= 1;
	repeated PBMinePos		MinePos				= 2;	// �ھ�ص�
	repeated PBMineEvent	MineEvent			= 3;	// �¼�
	optional uint32			Radius				= 4;	// ʹ�ð뾶
	optional uint32			DropTable			= 5;
	optional uint32			DecBuff				= 6;
	optional uint32			OgreID				= 7;
	optional uint32			OgreNum				= 8;
	optional uint32			MapID				= 9;
	optional uint32			PosX				= 10;
	optional uint32			PosY				= 11;
	optional uint32			Special				= 12;
};

//**********************************
// PBBlock �赲NPC
//**********************************
message PBRelatively_Pos
{
	optional int32				X	= 1;
	optional int32				Y	= 2;
};

message PBBlock
{
	optional PBOgreProperty		BaseInfo	= 1;
	optional int32				Select		= 2;
	repeated PBRelatively_Pos	Pos			= 3;
};

message PBPKDrop
{
	optional uint32		State	= 1;
	optional int32		EquipDropRate	= 2;
	optional int32		BagDropRate1	= 3;
	optional int32		BagDropRate2	= 4;
	optional int32		GoPrisonRate	= 5;
	optional int32		PrisonTime		= 6;
};

message PBPKValueTable
{
	optional uint32			TempID				= 1;
	optional int32			NavyBlue			= 2;
	optional int32			Blue				= 3;
	optional int32			CambridgeBlue		= 4;
	optional int32			White				= 5;
	optional int32			Rosiness			= 6;
	optional int32			Red					= 7;
	optional int32			CarMine				= 8;
	optional int32			RedTopLimit			= 9;
	optional int32			YellowTime			= 10;
	optional int32			DecValue			= 11;
	repeated int32			DecExpRate			= 12;
	repeated int32			TopLimitDecExp		= 13;
	repeated int32			PriceChange			= 14;
	optional int32			LineID				= 15;
	optional int32			MapID				= 16;
	optional int32			PosX				= 17;
	optional int32			PosY				= 18;
	repeated PBPKDrop		Drop				= 19;
	optional uint32			FreeMapID			= 20;
	optional uint32			FreePosX			= 21;
	optional uint32			FreePosY			= 22;
	optional uint32			PrisonTime			= 23;
	optional uint32			BasePKValue			= 24;
	repeated uint32			PKValueLevel		= 25;
	optional uint32			DropRateInEnemy		= 26;
	optional uint32			PrisonBuffID		= 27;
};

//**********************************
// PBItemToken, �������ƣ�CTplToken
//**********************************

message PBItemToken
{
	optional PBItemBase		BaseInfo			= 1;
	repeated PBMinePos		Pos					= 2;
	optional uint32			Radius				= 3;
	optional uint32			OgreID				= 4;
	optional uint32			OgreNum				= 5;
};

//**********************************
// PBItemKitBag ����
//**********************************
message PBItemKitBag
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		IndexNum			= 2;	// ������������
};

//**********************************
// PBItemGiftBag �������Ʒ
//**********************************
message PBItemGiftBag
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		DropTableID			= 2;	// �����ID
    optional uint32 	MinLevel			= 3;	// ʹ����Ʒ��Ҫ����͵ȼ�
	optional uint32 	MinMoney			= 4;	// ��Ǯ��С
	optional uint32		MinBindMoney 		= 5;	// �󶨽���С
	optional uint32		MinSilverYB			= 6; 	// ��Ԫ����С
    optional uint32     DropInBag           = 7;    // ������Ʒ�Ƿ�ֱ�ӽ���
	optional uint32 	MaxMoney			= 8;	// ��Ǯ���
	optional uint32		MaxBindMoney 		= 9;	// �󶨽����
	optional uint32		MaxSilverYB			= 10; 	// ��Ԫ�����
	optional uint32		CheckBag			= 11;	// �Ƿ������	
	optional uint32		MinExp				= 12;
	optional uint32		MaxExp				= 13;
	repeated uint32		LevelTableID		= 14;	// ���ȼ��ĵ����
	optional uint32		LiHuaID				= 15;
	repeated uint32		OpenItemID			= 16;
	repeated uint32		OpenTableID			= 17;
};

//**********************************
// PBItemAdapter ��Ʒ������
//**********************************

message PBItemAdapter
{
	optional uint32			TempID				= 1;	// ģ��ID
	optional uint32			ItemType			= 2;	// ģ������
	optional uint32			RealType			= 3;	// ��ʵ����
	optional uint32			RealTempID			= 4;	// ��ʵģ��ID
	optional uint32			MaxLevelMinus		= 5;	// ���ȼ���
	optional uint32			Param				= 6;	// ��Ʒ����
	optional uint32			MaxValue			= 7;	// ���ֵ
	optional uint32			MinValue			= 8;	// ��Сֵ
};

//**********************************
// PBTplHierogram ��Ʒ������
//**********************************
message PBTplHierogram
{
	optional uint32			TempID				= 1;
	optional string			Res					= 2;
	optional uint32			Alive				= 3;
	optional uint32			Type				= 4;
	optional uint32			Parame1				= 5;
	optional uint32			Parame2				= 6;
};

//**********************************
// PBStep �컯С��
//**********************************
message PBStep
{
	optional uint32		StageID	= 1;
	optional uint32		SkillTree = 2;
	repeated uint32		Next	= 3;
	//optional uint32		Exp		= 4;
	optional uint32		MaxPoint = 5;
	optional string		StageDesc = 6;
	optional uint32		Layer = 7;
};

message PBTitle
{
	optional string			Title	= 1;	// �ƺ�
	optional uint32			Type	= 2;	// ���
	optional uint32			ObtainCondition = 3; // �������
	optional uint32			SubCondition = 4;	// ��������
	optional uint32			Color	= 5;	// �ƺ���ɫ
	optional uint32			AddProperty = 6;	// ��Ӧ��������
	optional uint32			IsHidden = 7;	// �ƺ��Ƿ�����
	optional uint32			IsReplace = 8;	// �Ƿ�ֱ���滻ԭ���ĳƺ�
	optional string			Descrbe	= 9;	// ����
	optional uint32			ValidTime = 10;	// ��Чʱ��
	optional uint32			IsTeamTitle = 11;	// �Ƿ�������ƺ�
	optional uint32			Param = 12;		// �ƺŲ���
	optional string			Detail	= 13;	// �ƺ�˵��
};

message PBTitleManager
{
	optional uint32		TempID = 1;
	repeated PBTitle	Title = 2;
};

message PBTplBuffImmunity
{
	optional uint32			TempID				= 1;
	repeated uint32			BuffType			= 2;
};

//**********************************
// PBTemplateTalent �컯����
//**********************************
message PBTemplateTalent
{
	optional uint32	  TempID = 1;	// ģ��ID
	repeated PBStep   Step = 2;
	repeated uint32	  Exp = 3;
};

// �������� ���ӱ� ��Ԫ
message PBMagicWeaponProIncValue
{
	optional uint32	LevelPoints			= 1;
	optional uint64	LevelExp			= 2;	// protobuf��8�ֽڶ��룡���Էŵ��ڶ���λ��
	optional uint32	LevelProcessVal		= 3;
	optional uint32	LevelProcessCurel	= 4;
	optional uint32	LevelProcessCurelVal= 5;
	optional uint32	LevelKeen			= 6;		
	optional uint32	LevelCalm			= 7;		
	optional uint32	LevelMagic			= 8;	
	optional uint32	LevelBier			= 9;		
	optional uint32	LevelImmortal		= 10;
};

//**********************************
// PBTemplateLifeSkill �����ģ��
//**********************************
message PBTemplateLifeSkill
{
	optional uint32	TempID					=	1;		// ģ��ID
	optional uint32	LifeSkillType			=	2;		// ���������
	optional uint32	LifeSkillKind			=	3;		// ���������	
	repeated uint32	DegreeStarted			=	4;		// ÿһ������ܿ���������������
	repeated uint32	StudyMoney				=	5;		// ÿһ������ܵ�ѧϰ��Ǯ
	repeated string SkillName				=   6;		// ÿһ��������
	repeated uint32 CharacterNameID			=	7;		// ÿһ�����ܸ���ҵĳƺ�
	repeated uint32	StudyDegree				=	8;		// ÿһ������ܿ���������������
	repeated uint32	Level					=	9;		// ѧϰÿһ���������Ҫ�ĵȼ�	
	optional uint32 SubSkillLevelLimit		=	10;		// ���޼����ܹ�ѧϰ�ĵȼ�����
	repeated uint32	DegreeValue				=	11;		// ����ܽ������ȡ��������
};

//**********************************
// PBCTemplateDecompound װ���ֽ��
//**********************************
message PBDecompondTable
{
	optional uint32	FstItemID			=	1;			// �ֽ�װ�����ɵ�һ����Ʒ��ID
	optional uint32	FstProbability		=	2;			// �ֽ�װ�����ɵ�һ����Ʒ�ĸ���	
	optional uint32	SecItemID			=	3;			// �ֽ�װ�����ɵڶ�����Ʒ��ID
	optional uint32	SecProbability		=	4;			// �ֽ�װ�����ɵڶ�����Ʒ�ĸ���
	optional uint32	ThirdItemID			=	5;			// �ֽ�װ�����ɵ�������Ʒ��ID
	optional uint32	ThirdProbability	=	6;			// �ֽ�װ�����ɵ�������Ʒ�ĸ���
	optional uint32	DegreeNeeded		=	7;			// �ֽ�װ����Ҫ��������
	optional uint32	FstItemNum			=	8;			// �ֽ�װ�����ɵ�һ����Ʒ��ID
	optional uint32	SecItemNum			=	9;			// �ֽ�װ�����ɵڶ�����Ʒ��ID
	optional uint32	ThirdItemNum		=	10;			// �ֽ�װ�����ɵ�������Ʒ��ID
};
message PBCTemplateDecompound
{ 
	optional	uint32				TempID			=	1;		// ģ��ID
	repeated 	PBDecompondTable	WhiteDecompond	=	2;		// ��װ�ֽ��
	repeated 	PBDecompondTable	BlueDecompond	=	3;		// ��װ�ֽ��
	repeated 	PBDecompondTable	PurpleDecompond	=	4;		// ��װ�ֽ��
	repeated	uint32				Value			=	5;		// ������������ֽ����Ҫ�������ȵĲ�ֵ����
	repeated	uint32				Probability		=	6;		// �ֽ�װ����ȡ�����ȵĸ���			
	repeated	uint32				DegreeValue		=	7;		// �ֽ�װ����ȡ�����ȵ���ֵ	
};
// �������� ���ӱ�
message PBTplMagicWeaponProIncTable
{
	optional uint32	  TempID = 1;	// ģ��ID
	repeated PBMagicWeaponProIncValue Values	= 3;
};

// ���� �ֽ��
message SingleMWDecomposeData
{
	optional uint32		TempID= 1; // ģ��ID
	optional uint32		NumMin= 2; // ��������
	optional uint32		NumMax= 3; // �������
	optional uint32		Prob  = 4; // ��ü���(��ֱ�)
};							 
			
message PBMagicWeaponDecomposeTable
{
	optional uint32		TempID				= 1;	// ģ��ID
	optional uint32		NeedMoneyType		= 2;
	optional uint32		NeedMoney			= 3;
	repeated SingleMWDecomposeData Items	= 4;
};

// ����������
message PBMagicWeaponQuickUpTable
{
	optional uint32	TempID				= 1;	// ģ��ID
	optional uint32	NeedItem		=	2;
	optional uint32	NeedItemNum	=	3;
	optional uint32	NeedMoneyType	=	4;
	optional uint32	NeedMoney		=	5;
	optional uint32	SuccessProb	=	6;
	optional uint32	NewMWID		=	7;
	optional uint32	NeedLevel		=	8;
	optional uint32	LeastLeve		=	9;
};

//**********************************
// PBItemMagicWeapon, ����
//**********************************

message PBItemMagicWeapon
{
	optional PBEquipment	Base					= 1;
	optional string			ShowLevel				= 2;
	optional string			ShowType				= 3;
	optional string			NewWeaponName			= 4;
	optional uint32			UmmiBuffID				= 5;
	optional uint32			InitLevel				= 6;
	optional uint32			InitMp					= 7;
	optional uint32			InitHp					= 8;
	optional uint32			InitMaxMp				= 9;
	optional uint32			InitMaxHp				= 10;
	optional uint32			InitBase				= 11;
	optional uint32			InitShape				= 12;
	optional uint32			InitEffect				= 13;
	optional uint32			InitSpir				= 14;
	optional uint32			IncMaxMp				= 15;
	optional uint32			IncMaxHp				= 16;
	optional uint32			MPIncValue				= 17;
	optional uint32			HPIncValue				= 18;
	optional uint32			MPIncValuePerMagic		= 19;		
	optional uint32			HPIncValuePerMagic		= 20;		
	optional uint32			AttackInc				= 21;
	optional uint32			RecovInc				= 22;
	optional uint32			MaxMPInc				= 23;
	optional uint32			MaxHPInc				= 24;
	optional uint32			DeadLineInc				= 25;
	optional uint32			CanUseBook				= 26;
	optional uint32			GetSkillScl				= 27;
	optional uint32			LevelTableID			= 28;	
	optional uint32			SkillBoxTableID			= 29;	
	optional uint32			DieOffHp				= 30;
	optional uint32			ProJudgeCost			= 31;
	optional string			DispResName				= 32;
	optional uint32			DefaultSkill			= 33;
	optional uint32			DefaultSkill2			= 34;
	optional uint32			JudgeEffTableID			= 35;	
	optional uint32			JudgeSpirTableID		= 36;	
	optional uint32			LevelQuotietyTabID		= 37;	
	optional uint32			DecomposeTabID			= 38;	
	optional uint32			LvByNum					= 39;
	optional uint32			QuickUpTabID			= 40;
	optional uint32			UpLevelTabID			= 41;	
};

// �������ܿ�
message PBSingleSkillStorage
{
	optional uint32			SkillID				= 1;
	optional uint32			FirstProb			= 2;
	optional uint32			OtherProb			= 3;
};

//**********************************
// PBItemMagicStone, ��ħ��Ʒ
//**********************************
message PBItemMagicStone
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		Part				= 2;	// ��ħλ��
	repeated uint32		Attribute			= 3;	// ��ħ����
	optional uint32		UsedTimes			= 4;	// ʹ�õĴ���
	repeated uint32		Probability			= 5;	// ÿ�θ�ħ�ĸ���
	optional uint32		LevelLimit			= 6;	// ��ħ�ĵȼ�����
};

//**********************************
// PBLifeSkillScroll, ����ܾ���
//**********************************
message PBLifeSkillScroll
{
	optional PBItemBase BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		ComposeID			= 2;	// �䷽ID
	optional uint32		ComposeType			= 3;	// �䷽����		
};
message PBSkillStorage
{
	optional uint32					TempID		= 1;
	repeated PBSingleSkillStorage	Values		= 2;
};

// �������ܿ����Ա�
message PBSkillBoxProperty
{
	optional uint32			SkillBoxColor		= 1;
	optional uint32			SkillBoxNeedVal		= 2;
	optional uint32			InitState			= 3;
	optional uint32			InitSkillID			= 4;
	optional uint32			SkillBoxType		= 5;
	optional uint32			SkillBoxSkill		= 6;
	optional uint32			SkillBoxActMoney	= 7;
	optional uint32			SkillBoxSkillStorage= 8;
};

message PBMagicWeaponSkillBoxProTable
{
	optional uint32					TempID		= 1;
	repeated PBSkillBoxProperty		Values		= 2;
};

// �������Լ���Ӱ��ȱ�
message PBMWProJudgeEffTable
{
	optional uint32		TempID		= 1;
	repeated uint32		ProbFirst	= 2;
	repeated uint32		ProbSecond	= 3;
	repeated string		ShowName	= 4;
	repeated uint32		JudgeLevel	= 5;
};

// �������Լ������Ա�
message PBMWProJudgeSpirTable
{
	optional uint32		TempID		= 1;
	repeated uint32		ProbFirst	= 2;
	repeated uint32		ProbSecond	= 3;
	repeated string		ShowName	= 4;
	repeated uint32		JudgeLevel	= 5;
};

// ��������ϵ����
message PBMWLevelQuotietyTab
{
	optional uint32		TempID			= 1;
	repeated uint32		KeenQuotiety	= 2;
	repeated uint32		CalmQuotiety	= 3;
	repeated uint32		MagicQuotiety	= 4;
	repeated uint32		BierQuotiety	= 5;
	repeated uint32		ImmorQuotiety	= 6;
};

//**********************************
// PBFuncItem ��������Ʒ
//**********************************
message PBFuncItem
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		FuncCode			= 2;	// ������
	repeated uint32     Params				= 3;	// ����
};

//**********************************
// PBFuncItem ��������Ʒ
//**********************************
message PBEquipExchangeTable
{
	optional uint32					TempID		 = 1;	// ģ��ID
	repeated uint32					ComposeID	 = 2;	// �䷽ID
	optional uint32					ExchangeType = 3;	// �һ�����	
};

message PBMultiBuffEvent
{
	optional uint32	EventID = 1;
	optional uint32	TeamFlag = 2;
	optional uint32	Distance = 3;
	optional uint32	BuffID = 4;
	repeated uint32	RepetionIndex= 5;
};

message PBMultiBuff
{
	optional uint32	TempID = 1;
	repeated PBMultiBuffEvent BuffEvent = 2;
	repeated uint32	Param = 3;
	repeated uint32	NewBuff	= 4;
};

message PBCDGroupTable
{
	optional uint32	  TempID = 1;	// ģ��ID
	repeated uint32	  CDTime = 2;
};

// ��������

message PBMetierAp
{
	optional uint32	Metier = 1;
	optional uint32	Ap = 2;
};

message PBApConfig
{
	optional uint32	TempID = 1;
	optional uint32	ConsumeHook = 2;
	optional uint32	WorldChat = 3;
	optional uint32	CampChat = 4;
	optional uint32	IncApMax = 5;
	repeated PBMetierAp MetierAp = 6;
	repeated uint32	RedPhysic = 7;
	repeated uint32	BluePhysic = 8;
	repeated uint32	ApPhysic = 9;
	repeated uint32 FbHpPhysic = 10;
	repeated uint32	FbMpPhysic = 11;
	repeated uint32	MendPhysic = 12;
};

message PBLightTable
{
	optional uint32	  TempID		= 1;	// ģ��ID
	repeated uint32	  LevelPoint	= 2;
	repeated uint32	  JewelPoint	= 3;
	repeated uint32	  LevelGrade1	= 4;
	repeated uint32	  JewelGrade1	= 5;
	repeated uint32	  LevelGrade2	= 6;
	repeated uint32	  JewelGrade2	= 7;
};

message PBWizardTable
{
	optional uint32	TempID		=	1;
	repeated uint32	Exp			=	2;
	optional uint32 KeepRand	=	3;
	repeated uint32 TrendRand	=	4;
	repeated uint32 TrendResult =	5;
	optional uint32 Money		=	6;
};

message PBJudgeLevel
{
	optional uint32 JudgeType = 1;
	optional uint32	LevelMin	= 2;
	optional uint32	LevelMax	= 3;
	optional uint32	Star	= 4;
	optional uint32	LevelType = 5;
};

message PBJudgeConfig
{
	optional uint32		TempID		= 1;	// ģ��ID
	optional uint32		OpenCD		= 2;	// 
	repeated PBJudgeLevel JudgeLevel = 3;
	optional uint32		ScoreBase	= 4;
	optional uint32		ScoreRate	= 5;
	optional uint32		ScoreLevel	= 6;
};


// �����Ʒ
message PBPaperValue
{	
	optional uint32	 Value		=	1;	//	��ֵ
	optional uint32	 Probality	=	2;	//	����
};

message PBItemRedPaper
{
   optional PBItemBase		BaseInfo			= 1;	// ���߻�����Ϣ
   optional uint32			BaseCharge			= 2;	// ������� 
   repeated PBPaperValue    MoneyInfo			= 3;	// �ǰ󶨽�Ǯ�ĵ�����Ϣ
   repeated PBPaperValue	BindMoneyInfo		= 4;	// �󶨽�Ǯ�ĵ�����Ϣ
   optional uint32			RedPaperType		= 5;	// �������
};

message PBTrend
{
	optional uint32		TempID		= 1;	// ģ��ID
	repeated uint32		Bonus		= 2;
	optional string		Name		= 3;
	optional string		Desc		= 4;
};

message PBAward
{
	optional uint32		ItemID		= 1;
	optional uint32		ItemNum		= 2;
};

message PBAchieveAward
{
	optional uint32			TempID	= 1;
	repeated uint32			AwardID = 2;
	repeated uint32			AwardNum = 3;
	repeated uint32			Point = 4;
	optional uint32			SysMailID = 5;
};

message PBPower
{
	optional uint32		TempID		= 1;	// ģ��ID
	optional string		Name		= 2;
	optional string		Desc		= 3;
	optional uint32		Type		= 4;
	optional uint32		Level		= 5;
	optional uint32		Official	= 6;
	optional uint32		Order		= 7;
	optional uint32		Param1		= 8;
	optional uint32		Param2		= 9;
	repeated uint32		UseTime		= 10;
	optional uint32		Construct	= 11;
	optional uint32		Power		= 12;
	optional uint32		Money		= 13;
	optional string		Icon		= 14;
	optional uint32		Country		= 15;
	optional uint32		AllCount	= 16;
	optional uint32		StartHour	= 17;
	optional uint32		StartMin	= 18;
	optional uint32		EndHour		= 19;
	optional uint32		EndMin		= 20;
};

message PBOfficial
{
	optional uint32		TempID		= 1;
	optional string		Name		= 2;
	optional string		Desc		= 3;
	optional uint32		Type		= 4;
	repeated uint32		Wizard		= 5;
	optional uint32		Power		= 6;
	optional uint32		CountryLevel = 7;
	optional uint32		ConstructLevel = 8;
};

message PBOfficialTable
{
	optional uint32		TempID		= 1;
	repeated uint32	OfficialData	= 2;	
};

message PBConstructExp
{
	optional uint32		TempID		= 1;
	repeated uint32		Exp			= 2;	
	repeated uint32		Bonus		= 3;
};

message PBAddPKTable
{
	optional uint32		TempID			= 1;
	optional uint32		KFChangePower	= 2;
	optional uint32		KPChangePower	= 3;
	optional uint32		KWChangePower	= 4;
	optional uint32		DFChangePower	= 5;
	optional uint32		DPChangePower	= 6;
	optional uint32		DWChangePower	= 7;
	optional uint32		KFChangeFriend	= 8;
	optional uint32		KPChangeFriend	= 9;
	optional uint32		KWChangeFriend	= 10;
	optional uint32		KFChangePK	= 11;
	optional uint32		KWChangePK	= 12;
	repeated uint32		KPChangePK	= 13;
	repeated uint32		PFriendMin	= 14;
	repeated uint32		PFriendMax	= 15;
	optional uint32		KFChangeHonor	= 16;
	optional uint32		KPChangeHonor	= 17;
	optional uint32		KWChangeHonor	= 18;
};

message PBMapTable
{
	optional uint32		TempID		= 1;
	repeated uint32		Level		= 2;	
	repeated uint32		Power		= 3;
};

message PBMultiAttackTable
{
	optional uint32		TempID		= 1;
	repeated uint32		Reduce		= 2;	
};

message PBItemVip
{
	optional PBItemBase BaseInfo = 1;
	optional uint32		VipLevel = 2;
	optional uint32		VipTime	 = 3;
};

message PBItemClean
{
	optional PBItemBase BaseInfo = 1;
	optional uint32		CleanType = 2;
	optional uint32		CleanLevel	 = 3;
	optional uint32		Step		= 4;
};

message PBAwardInfo
{
	optional uint32		TempID		= 1;
	optional string		Name		= 2;
	optional string		Desc		= 3;
	repeated uint32		ItemID		= 4;
	repeated uint32		ItemNum		= 5;
	optional uint32		BuffID		= 6;
	optional uint32		Times		= 7;
	optional uint32		NpcID		= 8;
	optional uint32		Country	    = 9;
	optional uint32		NoFamily	= 10;
};


// ��������ع���Ʒ
message PBLeagueItem
{
	optional uint32	ItemID		=	1;		// ��ƷID
	optional uint32	ItemNum		=	2;		// ��Ʒ����
	optional uint32	Probality	=	3;		// ��Ʒ�����ɸ���
};
message PBLeagueBag
{
	optional PBItemBase	  ItemBase		=  1;	// ��Ʒ������Ϣ
	repeated PBLeagueItem LeagueItemInfo = 2;	// �ع���Ʒ��������Ʒ
	optional uint32	LeagueBagType		 = 3;	// �ع���Ʒ������
	optional uint32	ExchangeTableID		 = 4;	// �ع���Ʒ���ڵĶһ���ID
	optional uint32	MapID				 = 5;	// �ܹ�ʹ�õĵ�ͼID
	optional uint32	PosX				 = 6;	// �ܹ�ʹ�õĺ�����
	optional uint32	PosY				 = 7;	// �ܹ�ʹ�õ�������
};

message PBMatrixTable
{
	optional uint32		TempID				=	1;
	repeated uint32		Level				=	2;
	optional uint32		MaxLimit			=	3;
	optional uint32		MinLimit			=	4;
	repeated uint32		MasterItemID		=	5;
	repeated uint32		MasterItemNum		=	6;
	repeated uint32		MailID				=	7;
	optional uint32		FormalLevel			=	8;
	optional uint32		EducatedLevel		=	9;
	optional uint32		EnterLimit			=	10;
	optional uint32		RemoveItem			=	11;
	optional uint32		RemoveMoney			=	12;
	optional uint32		FormalPercent		=	13;
	optional uint32		EducatedPercent		=	14;
	optional uint32		ReturnLimit			=	15;
	optional uint32		AlterMax			=	16;
	optional uint32		AlterMin			=	17;
	optional uint32		ReturnMailID		=	18;
	repeated uint32		SlaveItemID			=	19;
	repeated uint32		SlaveItemNum		=	20;
	optional uint32		AlterAll			=	21;
	optional uint32		AlterDefault		=	22;
	optional uint32		SlaveMailID			=	23;
};

// ���ϵͳ�������ļ�
message PBWeddingInfo
{
	optional uint32 WeddingLength			= 1;			// ����Ļ���ʱ��(����)
	optional uint32 MoneyNeeded				= 2;			// �������
	optional uint32	DelayMoneyNeeded		= 3;			// �ӳ�����ÿ������Ҫ�ķ���
	optional uint32 WeddingRedstoneID		= 4;			// �����ڵ�ID
	optional uint32	WeddingHallRedstoneID	= 5;			// ���õ��ڵ�ID			
	optional uint32	WeddingHallMapID		= 6;			// ���õĵ�ͼID
	optional uint32 InvitationCardID		= 7;			// npc���͵�������ID
	optional uint32 InvitationCardNum		= 8;			// npc���͵�����������
	optional uint32 FemaleKeepsakeID		= 9;			// npc���͵�Ů������ID
	optional uint32	MaleKeepsakeID			= 10;			// npc���͵��з�����ID
	optional uint32	PosX					= 11;			// �������õĺ�����
	optional uint32	PosY					= 12;			// �������õ�������	
	optional uint32	FemaleKeepsakeTwo		= 13;			// npc���͵ĵڶ���Ů������ID
	optional uint32	MaleKeepsakeTwo			= 14;			// npc���͵ĵڶ����з�����ID	
	optional uint32	FemaleKeepsakeThree		= 15;			// npc���͵ĵ�����Ů������ID
	optional uint32	MaleKeepsakeThree		= 16;			// npc���͵ĵ������з�����ID
	optional uint32	MaleBufferID			= 17;			// ���ɱ���buff��ģ��ID
	optional uint32	FemaleBufferID			= 18;			// �������buff��ģ��ID	
	optional uint32	MaleItemID				= 19;			// ���ɱ�����Ʒ��ID
	optional uint32	FemaleItemID			= 20;			// ���������Ʒ��ID	
	optional uint32	GroomPosX				= 21;			// ���ɰ���ʱ����λ�õĺ�����
	optional uint32	GroomPosY				= 22;			// ���ɰ���ʱ����λ�õ�������
	optional uint32	BridePosX				= 23;			// �������ʱ����λ�õĺ�����
	optional uint32	BridePosY				= 24;			// �������ʱ����λ�õ�������
	optional uint32	GroomBufferID			= 25;			// ���ɱ���buff��ģ��ID
	optional uint32	BrideBufferID			= 26;			// �������buff��ģ��ID
	optional uint32	MarriageItemID			= 27;			// �����Ҫ�ĵ���ID
	optional uint32	WeddingScroll			= 28;			// ���²��������Ҫ�Ļ������	
};

message PBKeepsnakeInfo
{
	optional uint32	KeepsakeID				= 1;			// ����ID
	optional uint32	EquipID					= 2;			// ����һ����ɵ�װ��ID	
};

message PBTemplateMarriageConfig
{
	optional uint32				TempID				= 1;		// ģ��ID
	repeated PBWeddingInfo		WeddingInfo			= 2;		// ������Ϣ
	repeated PBKeepsnakeInfo 	FemaleKeepsakeInfo 	= 3;		// Ů��������Ϣ
	repeated PBKeepsnakeInfo 	MaleKeepsakeInfo 	= 4;		// �з�������Ϣ
	repeated uint32				WeddingNpc			= 5;		// ����npcID
	optional uint32				MarriageLevel		= 6;		// ������͵ȼ�
	optional uint32				MarriageMoney		= 7;		// ��֤��Ǯ	
	optional uint32				MapID				= 8;		// �����ô����ĵ�ͼID
	optional uint32				PosX				= 9;		// �����ô����ĺ�����
	optional uint32				PosY				= 10;		// �����ô�����������
	optional uint32				DivorceItemID		= 11;		// �����ߵ�ID
	optional uint32				MarriageTitleID		= 12;		// ����ȡ�ĳƺ�ID	
	optional uint32				MaleKeepsakeID		= 13;		// �����л���ʱϵͳ���ŵ��з�����ID	
	optional uint32				FemaleKeepsakeID	= 14;		// �����л���ʱϵͳ���ŵ�Ů������ID	
	optional uint32				InvitationID		= 15;		// �����л���ʱϵͳ���ŵ�����ID	
	optional uint32				InvitationNum		= 16;		// �����л���ʱϵͳ���ŵ���������
	optional uint32				MaleItemID			= 17;		// �����л���ʱϵͳ���ŵ����ɱ�����Ʒ��ID			
	optional uint32				FemaleItemID		= 18;		// �����л���ʱϵͳ���ŵ����������Ʒ��ID
	optional uint32				BaitangBuffID		= 19;		// �����������ʱ����buff��ID	
	optional uint32				BasicMarriageItem	= 20;		// �����Ҫ�۳��İ�֤����
	optional uint32				BasicMarriageItemNum= 21;		// �����Ҫ�۳��İ�֤���ߵ�����  
	optional uint32				MarriageNpcMapID	= 22;		// ���npc���ڵĵ�ͼID
	optional uint32				MarriageNpcPosX		= 23;		// ���npc���ڵĺ�����
	optional uint32				MarriageNpcPosY		= 24;		// ���npc���ڵ�������
	optional uint32				MarriageIntimacy	= 25;		// ������ܶ�
	optional uint32				IntimacyItemNum		= 26;		// ���ܶ��㹻ʱ��Ҫ��ʯͷ
};

message PBInvitation
{
	optional PBItemBase		ItemBase			=	1;		// ���߻�����Ϣ	
	optional uint32			ExchangeItemID		=	2;		// ��Ʒ����ID
};

// ���������ñ�
message ProGressInfo
{
	optional uint32	 FuncType		=	1;		// ��������
	optional uint32	 ProGressTime	=	2;		// ����������ʱ��
};
message PBProGressConfig
{
	optional uint32		  TmpID		=	1;		// ģ��ID
	repeated ProGressInfo Progress	=	2;		// ��������Ϣ
};

// ϵͳ����
message PBSysInvitation
{
	optional PBItemBase ItemBase		=	1;		// ���߻�����Ϣ
	optional uint32		InvitationID	=	2;		// �ܹ���ȡ������ID	
};

message PBCount
{
	optional uint32		CountType		=	1;
	optional uint32		CountTime		=	2;
	optional uint32		VipTime			=	3;
	optional uint32		ClearType		=	4;
};

message PBCountTable
{
	optional uint32		TempID			= 1;
	repeated PBCount	CountData		= 2;
};

// ����ñ�
message PBActivityConfig
{		
	optional uint32	 TempID								= 1;	// ģ��ID
	optional uint32  HydrangeaThrowTime					= 2;	// ���ʼ��ú�������
	repeated uint32	 HydrangeaSugarID					= 3;	// ���ϲ�Ǳ���buff��ID	
	optional uint32	 SugarSpreadTime					= 4;	// �����һ��ϲ��
	optional uint32  SugarSpreadNum						= 5;	// ϲ��ÿ�������������		
	optional uint32  HydrangeaActivityTime				= 6;	// ���׻�����ʱ��	
	optional uint32	 HydrangeaHolderTime				= 7;	// ÿ����ҵ��������ʱ��	
	optional uint32  HydrangeaRabTime					= 8;	// ���������ʱ��	
	optional uint32	 HydrangeaRedstoneID				= 9;	// ���������ڵ�ID
	optional uint32	 HydrangeaExpTableID				= 10;	// ���������齱���ĵȼ������ID
	
	optional uint32	 PreliminaryTitleID					= 11;	// �����ϰ���ȡ�ĳƺ�		
	optional uint32	 PreliminaryBaseScore				= 12;	// ÿ���һ�����ȡ�Ļ�������
	repeated uint32	 PreliminaryExtralScore				= 13;	// ��ʱ���ϰ��Ķ������
	optional uint32	 PreliminaryTipsTime				= 14;	// ����������Ŀ��Ԥ����ʱ��
	optional uint32	 PreliminaryAnswerTime				= 15;	// ������Ŀ���÷��ʹ�
	optional uint32	 PreliminaryQuestionTime			= 16;	// ���ʹ𰸶�ú�����Ŀ
	optional uint32	 PreliminaryQuestionNum				= 17;	// ���Ե���Ŀ����
	optional uint32	 PreliminaryExpTableID				= 18;	// ���Եĵȼ������ID	
	optional uint32  EffectiveOffLineExchangeRate		= 19;	// ����ʱ�����Ч����ʱ��֮��Ķһ�����
	optional uint32	 MaxOnLineEffectiveTime				= 20;	// ÿ���ת��Ϊ��Ч����ʱ����������ʱ��
	optional uint32	 MaxEffectiveOffLineTime			= 21;	// ������Ч����ʱ��
	optional uint32	 MaxOffLineTime						= 22;	// ÿ���ת�����������ʱ��
	optional uint32	 OffLineTimeLimit					= 23;	// ��ת��Ϊ���������ʱ������
	optional uint32	 VipOffLineExchangeRate				= 24;	// ��Ա����ʱ�����Ч����ʱ��֮��Ķһ�����
};

// ����ˢ�µ���
message PBItemRefresh
{
	optional PBItemBase ItemBase		=	1;		// ���߻�����Ϣ
	optional uint32		Color			=	2;
	optional uint32		Level			=	3;
	repeated uint32		LimitPos		=	4;		// ���Ʋ�λ
};

// �ټ�����
message PBItemSummon
{
	optional PBItemBase ItemBase		=	1;		// ���߻�����Ϣ
	optional uint32		SummonType		=	2;
};

// ����ñ�
message PBDirectTable
{		
	optional uint32	 TempID					= 1;	// ģ��ID
	repeated uint32	 DirectID				= 2;	// �õ���ID
	repeated uint32	 LuckID					= 3;	// �س�ʯID
	repeated uint32	 LuckRate				= 4;	// �س�ʯ����
};

// ���ǵ���
message PBItemDirect
{
	optional PBItemBase ItemBase		=	1;		// ���߻�����Ϣ
	optional uint32		Level			=	2;		// ���Ƶȼ�
	optional uint32		Star			=	3;		// �����Ǽ�
};

// ժ�ǵ���
message PBItemGetStar
{
	optional PBItemBase ItemBase		=	1;		// ���߻�����Ϣ
	optional uint32		Level			=	2;		// ���Ƶȼ�
};

message PBWarDate
{
	optional uint32		Day				=	1;
	optional uint32		Hour			=	2;
	optional uint32		Minute			=	3;
};

message PBTax
{
	optional uint32		TaxRate			=	1;
	optional uint32		IncomeRate		=	2;
	optional uint32		Limit			=	3;
};

// ��ս���ñ�
message PBWorldBattleConfig
{
	optional uint32		TempID			=	1;
	optional PBWarDate	SubmitBegin		=	2;		// ������ʼʱ��		
	optional PBWarDate	BattleBegin		=	3;		// ��ս��ʼʱ��
	optional PBWarDate	BattleEnd		=	4;		// ��ս����ʱ��
	repeated uint32		StoneID			=	5;		// ��ս�������ڵ�ID(1-10)
	optional uint32		InitBuffID		=	6;		// ��ʼ��BUFFID
	optional uint32		FlagSource		=	7;		// �������Դ��
	optional uint32		KillSource		=	8;		// ɱ�˵���Դ��
	optional uint32		FlagBonus		=	9;		// ���콱��
	repeated uint32		PerNum			=	10;		// ս����������
	repeated uint32		MapID			=	11;		// ս����ͼID
	repeated uint32		SubmitMoney		=	12;		// ������
	optional uint32		SubmitLevel		=	13;		// �����ȼ�
	repeated uint32		PosX			=	14;		// ����X
	repeated uint32		PosY			=	15;		// ����Y
	optional uint32		OutMapID		=	16;		// ������ͼID
	optional uint32		OutPosX			=	17;		// ��������X
	optional uint32		OutPosY			=	18;		// ��������Y
	repeated uint32		FlagIndex		=	19;		// ��������
	optional PBWarDate	BidEnd			=	20;		// ���۽���ʱ��
	optional uint32		MaxWarHonor		=	21;		// ÿ�����ս��
	repeated uint32		Title			=	22;		// ְҵ�ƺ�
	optional PBWarDate	NoticeBegin		=	23;		// ��ʾ��ʼʱ��
	optional uint32		TitleValidTime	=	24;		// �ƺŵ���Чʱ��
	optional uint32		StonePosX		=	25;		// �ڵ�����X
	optional uint32		StonePosY		=	26;		// �ڵ�����Y
	repeated PBTax		Tax				=	27;		// ˰��
	optional uint32		WinTax			=	28;		// ��ʤ˰��
};

// �Զ��ɼ�����
message PBDegreeInfo
{
	optional uint32	Value		= 1;		// ��ұ�����������Ҫ��������ȵĲ�ֵ
	optional uint32	Probality	= 2;		// �ڲ�ֵ��Χ�ڻ�ȡ�����ȵĸ���
	optional uint32	DegreeValue = 3;		// �ڲ�ֵ��Χ�ڻ�ȡ�����ȵ�ֵ
};
message PBItemInfo
{
	optional uint32	ItemID		= 1;	// ��ƷID
	optional uint32	ItemNum		= 2;	// ��Ʒ����
	optional uint32	Probality	= 3;	// ��Ʒ�����ĸ���
};
message PBItemAutoCollect
{
	repeated PBItemInfo ItemInfo		= 1;
	repeated PBDegreeInfo DegreeInfo	= 2;	
	optional uint32		MapID			= 3;
	optional uint32		PosX			= 4;	
	optional uint32		PosY			= 5;
	optional uint32		Grid			= 6;	
	optional uint32		MaxUseTimes   	= 7;
};

//**********************************
// PBFangCunTreeNode ����ɽ�ڵ�
//**********************************

message PBFangCunTreeNode
{
	optional uint32				SkillID				= 1;	// ����ID
	optional uint32				MaxLevel			= 2;	// ���ȼ�( ����ܵ�Ͷ���� )
	repeated uint32				NeedSkillID			= 3;	// ��Ҫ��ǰ������
	repeated uint32				NeedSkillPoint		= 4;	// ��Ҫ��ǰ������Ͷ����
	optional uint32				Level				= 5;	// ��Ҫ����ҵȼ�
	optional uint32				NeedBook			= 6;	// �Ƿ���Ҫ��Ӧ�ļ�����
	optional uint32				Stage				= 7;	// ��
	optional uint32				Order				= 8;	// ˳��
};

//**********************************
// PBFangCunTree ����ɽ������
//**********************************

message PBFangCunTree
{
	optional uint32				TempID				= 1;	// ģ��ID
	repeated PBFangCunTreeNode	SkillNode			= 2;	// 
};

//**********************************
// PBBlackPills �ڹ���
//**********************************
message PBItemBlackPills
{
	optional PBItemBase ItemBase		=	1;		// ��Ʒ������Ϣ
	optional uint32		ExchangeTime	=	2;		// ���Զһ���ʱ��
	optional uint32		ExpTableID		=	3;		// �ȼ������
};

message PBStage
{
	optional uint32		StageID	= 1;
	repeated uint32		Next	= 2;
	optional uint32		Layer = 3;
};

message PBTemplateTalentStage
{
	optional uint32	  TempID = 1;	// ģ��ID
	repeated PBStage  Stage = 2;
};

//**********************************
// PBItemExpContainer �������鵤
//**********************************
message PBItemExpContainer
{
	optional PBItemBase ItemBase	=	1;	// ��Ʒ������Ϣ
	optional uint64 MaxExp			=	2;	// �ܹ��洢�������
	optional uint32	OgreExpRate		=	3;	// ��־���İٷֱ�
	optional uint32 ExpPillsID		=	4;	// ����洢�����ܹ���ȡ�ľ��鵤ID		
};

//**********************************
// PBItemExpPills ���鵤
//**********************************
message PBItemExpPills
{
	optional PBItemBase ItemBase	=	1;	// ��Ʒ������Ϣ
	optional uint64		Exp			=	2;	// �ܹ��洢�������
	optional uint32		LevelLimit	=	3;	// ʹ�õȼ�����
};


//**********************************
// PBItemExpPills �����ĵ�
//**********************************
message PBItemExpTome
{
	optional PBItemBase ItemBase	=	1;	// ��Ʒ������Ϣ
	optional uint64		Exp			=	2;	// �ܹ��洢�������
	optional uint32		LevelLimit	=	3;	// ʹ�õȼ�����
	repeated uint32	OpenItemID	=	4; //������Ʒ 
};

// �������ñ�
message PBAccuseConfig
{
	optional uint32		TempID				=	1;
	optional uint32		AccuseBeginHour		=	2;		// ��ʼ����ʱ
	optional uint32		AccuseBeginMinute	=	3;		// ��ʼ������
	optional uint32		AccuseLevel			=	4;		// ��������ȼ�
	optional uint32		AccuseEndHour		=	5;		// ��������ʱ
	optional uint32		AccuseEndMinute		=	6;		// ����������
	optional uint32		AccuseMoney			=	7;		// �������ѽ��
	optional uint32		AccusePerson		=	8;		// ������������
	optional uint32		AccusePercent		=	9;		// ��������
	optional uint32		AwardPower			=	10;		// ʧ�ܽ�������
	optional uint32		GateNum				=	11;		// ������������
	optional uint32		FlagNum				=	12;		// ������������
	optional uint32		GatePower			=	13;		// ���Ż������
	optional uint32		FlagPower			=	14;		// ����������
	optional uint32		AccuseNoticeHour	=	15;		// ��ʾ����ʱ
	optional uint32		AccuseNoticeMinute	=	16;		// ��ʾ������
	optional uint32		NoticePower			=	17;		// ��ʾ����
	optional uint32		GateParam1			=	18;		// ���Ų���1
	optional uint32		FlagParam1			=	19;		// �������1
	optional uint32		GateParam2			=	20;		// ���Ų���2
	optional uint32		FlagParam2			=	21;		// �������2
	optional uint32		GateParam3			=	22;		// ���Ų���3
	optional uint32		FlagParam3			=	23;		// �������3
	optional uint32		LWPercent			=	24;		// ���轱���ӳ�
};

// ȫ�ֵ�ͼ���ñ�
message PBGlobalMapConfig
{
	optional uint32		TempID			=	1;
	optional uint32		MapID			=	2;		// ȫ�ֵ�ͼ
	optional uint32		BuffID			=	3;		// ��Ҫ��buffid
	optional uint32		Limit			=	4;		// ��������
	optional uint32		OutMap			=	5;
	optional uint32		OutX			=	6;
	optional uint32		OutY			=	7;
	optional uint32		EscapeBuffID	=	8;		// ���ս��buffID
};

//����boss��

message PBCorpsBOSS
{
	optional uint32	TempID		= 1;
	repeated uint32 BOSSID		= 2;	//boss id
	repeated uint32 HardBOSSID	= 3;	//ϡ�� boss id
	repeated uint32	ValueLimit	= 4;	//����ֵ����
	repeated string	DropDesc	= 5;	//boss��������
	repeated string HardDropDesc= 6;	//hard boss ��������
	repeated uint32 SummonMinLevel = 7; //�ٻ�boss��Ҫ���ŵ���͵ȼ�
	repeated uint32 HardSummonMinLevel = 8; //�ٻ�hard boss��Ҫ���ŵ���͵ȼ�
	repeated uint32 SummonMinValue = 9; //�ٻ�bossʱ��������������
	repeated uint32 HardSummonMinValue = 10; //�ٻ�hard bossʱ��������������
};


// ���߾������ñ�
message PBOffLineExpConfig
{
	optional uint32		TempID				=	1;
	optional uint32		OffLineUnit			=	2;
	repeated uint32		OffLineExp			=	3;		
	optional uint32		OffLineLevel		=	4;
	repeated uint32		ExpLimit			=	5;
	optional uint32		OffLinePercent		=	6;
};

message PBRepeFameTable
{
	optional uint32		TempID				=	1;
	repeated uint32		FameType			=	2;
	repeated uint32		FameValue			=	3;
	repeated uint32		ItemValue			=	4;
	optional uint32		CombatItemID		=	5;
	optional uint32		RepeItemID			=	6;
	optional uint32		CommonItemID		=	7;
	optional uint32		CombatLimit			=	8;
	optional uint32		RepeLimit			=	9;
	optional uint32		CommonLimit			=	10;
};

message PBCastingSpiritTable
{
	optional uint32		TempID				=	1;
	repeated uint32		OpenStatus			=	2;
	repeated string		PositionName		=	3;
	repeated string		PositionDesc		=	4;
	repeated string		SpiritTypeName		=	5;
	repeated string		SpiritTypeDesc		=	6;
	repeated uint32		SpiritItem			=	7;
	repeated uint32		SpiritItemNum		=	8;
	repeated uint32		UpgradeMoney		=	9;
	repeated uint32		DowngradeMoney		=	10;
	optional uint32		UpgradeItem			=	11;
	optional uint32		DowngradeItem		=	12;
};

message PBSpiritItem
{
	optional PBItemBase	BaseInfo			= 1;	// ���߻�����Ϣ
	optional uint32		Grade				= 2;
	optional uint32		ColorGrade			= 3;
	optional uint32		SpiritType			= 4;
	optional uint32		LevelLimit			= 5;
	optional uint32		EffectPoint			= 6;
};