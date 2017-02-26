#pragma once  
//---------------------------------------------
// Declare PB class
//---------------------------------------------
#ifdef TEMPEDIT
#pragma pack(4)
#endif
class PBTemplate;
class PBItemBase;
class PBItemReturn;
class PBItemBindStone;
class PBItemScroll;
class PBItemCall;
class PBItemCard;
class PBItemTeleport;
class PBItemReturnPaper;
class PBItemTeleSymbol;
class PBItemStove;
class PBItemPetEgg;
class PBItemPetFood;
class PBItemRelife;
class PBItemSkill;
class PBItemBook;
class PBItemUpgLuck;
class PBItemUpgLeast;
class PBItemQuestion;
class PBItemTask;
class PBItemStuff;
class PBItemExp;
class PBItemShout;
class PBItemAutoShout;
class PBItemPhysic;
class PBItemHorse;
class PBStuff;
class PBProduct;
class PBItemBluePrint;
class PBItemRune;
class PBItemJewel;
class PBItemYuanBug;
class PBItemYuanEgg;
class PBItemSequence;
class PBEquipment;
class PBEquipFashion;
class PBEquipWeapon;
class PBEquipArmor;
class PBTemplateProperty;
class PBPropertyPercent;
class PBTemplatePropertyTable;
class PBMetier;
class PBNpc;
class PBSellItem;
class PBSellTable;
class PBTotalDrop;
class PBDropItem;
class PBDropTable;
class PBNPCCollect;
class PBOgreProperty;
class PBBox_Click;
class PBOgreBox;
class PBShowPet;
class PBBattlePet;
class PBMineOutput;
class PBMineOgre;
class PBMine;
class PBSkillTreeNode;
class PBSkillTree;
class PBCost;
class PBUseCondition;
class PBSkill;
class PBAureoleType;
class PBAureoleSkill;
class PBNormalSkill;
class PBTrapSkill;
class PBBuffFunc;
class PBBuff;
class PBLevelExp;
class PBPetLevelExp;
class PBProduceExp;
class PBUpg;
class PBEquipUpg;
class PBSuitProducer;
class PBSuitNormal;
class PBSpell;
class PBProduceEquip;
class PBProducePhysic;
class PBOpenSlot;
class PBCompose;
class PBTeleTable;
class PBData;
class PBPetData;
class PBSummonBeast;
class PBBeginner;
class PBDropLevel;
class PBOgreTran;
class PBMetierPro;
class PBLevelProperty;
class PBHonorToExp;
class PBHonorObtain;
class PBDiploidTable;
class PBRedStone;
class PBRedStoneExpTable;
class PBReliveTable;
class PBQuestionExp;
class PBBindChargeTable;
class PBItemMineMap;
class PBItemUpg;
class PBPKValueTable;
class PBItemToken;
class PBBlock;
class PBRelatively_Pos;
class PBItemKitBag;
class PBItemRemove;
class PBItemChange;
class PBItemAdapter;
class PBMultiCompose;
class PBTplHierogram;
class PBItemGiftBag;
class PBCardBook;
class PBTitleManager;
class PBTplBuffImmunity;
class PBTemplateTalent;
class PBTemplateLifeSkill;
class PBCTemplateDecompound;
class PBItemMagicWeapon;
class PBTplMagicWeaponProIncTable;
class PBItemMagicStone;
class PBLifeSkillScroll;
class PBSkillStorage;
class PBMagicWeaponSkillBoxProTable;
class PBFuncItem;
class PBItemSkillBook;
class PBEquipExchangeTable;
class PBMultiBuff;
class PBCDGroupTable;
class PBApConfig;
class PBLightTable;
class PBJudgeConfig;
class PBItemRedPaper;
class PBWizardTable;
class PBTrend;
class PBMWProJudgeEffTable;
class PBMWProJudgeSpirTable;
class PBMWLevelQuotietyTab;
class PBAchieveAward;
class PBPower;
class PBOfficial;
class PBOfficialTable;
class PBConstructExp;
class PBAddPKTable;
class PBMapTable;
class PBMultiAttackTable;
class PBItemVip;
class PBItemClean;
class PBAwardInfo;
class PBLeagueBag;
class PBMatrixTable;
class PBTemplateMarriageConfig; 	
class PBInvitation;
class PBProGressConfig;
class PBSysInvitation;
class PBCountTable;
class PBActivityConfig;
class PBItemRefresh;
class PBItemSummon;
class PBDirectTable;
class PBItemDirect;
class PBItemGetStar;
class PBWorldBattleConfig;
class PBLevelMoneyLmt;
class PBItemAutoCollect;
class PBFangCunTreeNode;
class PBFangCunTree;
class PBItemBlackPills;
class PBTemplateTalentStage;
class PBItemExpContainer;
class PBItemExpPills;
class PBItemExpTome;
class PBHandinTable;
class PBHandinEncourage;
class PBItemChangeCamp;
class PBAccuseConfig;
class PBComRuneConfig;
class PBMagicWeaponDecomposeTable;
class PBMagicWeaponQuickUpTable;
class PBGlobalMapConfig;
class PBCorpsBOSS;
class PBOffLineExpConfig;
class PBRepeFameTable;
class PBCastingSpiritTable;
class PBSpiritItem;
//---------------------------------------------
// End Declare
//---------------------------------------------

#define TEMPLATE_CACHE_SIZE 25 * 1024 * 1024	// ��Cache��

#ifndef ARRAY_CNT
#define ARRAY_CNT( a ) ( sizeof(a)/(sizeof(a[0])) )	
#endif
#define ARRAY_ROW( a ) ( sizeof(a)/(sizeof(a[0])) )		// ��ά��������
#define ARRAY_COL( a ) ( sizeof(a[0])/sizeof(a[0][0]))	// ��ά��������

#define STRING32					32
#define STRING256					256
#define MAX_TEMPLATE				100000	// ���ְҵģ����
#define MAX_DIALOG					32		// ���Ի���
#define MAX_SKILL					10000	// �����ģ����
#define MAX_LEVEL					100		// ����ܵȼ�
#define MAX_METIER					10		// ���ְҵ��
#define MAX_GENER					150		// ���������
#define MAX_TASK					20000	// ���������
#define MAX_EQUIP					11		// һ���ĵȼ���
#define MAX_SUIT					150		// ��װ��
#define MAX_GRADE					120		// ���ȼ�
#define MAX_MAGICWEAPON_GRADE		120		// �������ȼ�
#define TMP_MAX_GRADE				161		// ģ�����õĵȼ�����
#define MAGICWEAPON_MAX_GRADE		161		// �����ĵȼ�����
#define MAX_QUESTION_NUM			10		// ÿ�������������Ŀ����
#define MAX_RULE_NUM				 3		// ������������
#define MAX_MINEPOS					25		// ��౦���ھ��
#define MAX_MINEEVENT					8		// ���ر�ͼ�����¼�����
#define MAX_BOXLEVEL				5		// ���伶�� 
#define MAX_COMPOSE					100		// ���ϳ���
#define TOTAL_TALENT_STAGE			100		// �컯С������
#define STEP_SWITCH					3		// С���л���
#define TOTAL_TALENT_POINT			10000	// ����츳��

#define MAX_BUFFFUN_COUNT			( 6 )	// Buff������

#define PROPERTY_OPTION				2		// ���Ա�ʾ������
#define CUR_ADD_PROPERTY			0		// ��ǰ�ȼ��������Ե�
#define CUR_TOTAL_PROPERTY			1		// ��ǰ�ȼ������Ե�
#define MAX_PROPERTY				6		// ���������
#define OPTION_NONE					0		// ��ѡ�� ( ��Ҫ���ڸ�protype.h������ö�����Ӧ )
#define	OPTION_STA					1		// ����ѡ��
#define	OPTION_WIS					2		// ����ѡ��
#define	OPTION_STR					3		// ����ѡ��
#define	OPTION_CON					4		// ����ѡ��
#define	OPTION_SPR					5		// ����ѡ��

#define REDNAME_SECTION				4		// ����4���׶�
#define PKSATE_COUNT				8		// pk ״̬����

#define PRODUCE_RANK	4			// װ�������в��ϵĵȼ�������1����2����3����4��
#define PRODUCE_LEVEL	16			// װ�����������ɵĵȼ�������1-160��
#define PRODUCE_DETAIL2 6			// װ�������еĵڶ����������Ѿ�����
#define PRODUCE_TYPE	10			// װ�������е���Ҫ���ͣ����������·���ñ�ӵ�
#define PRODUCE_DETAIL1	11			// װ�������еĵ�һ����������ǹ���ؼף���������

#define MAX_FAIL_TASKS 10			// NPC��ʧ �����������������ʧ��
#define MAX_TITLE		500			// �ƺ�������

#define MAX_LIFESKILL_DEGREESTEP 10		// �������������䷽�����ȵĲ�ֵ�ײ�
#define MAX_LIFESKILL_LEVEL		  10	// ����ܵ���ߵȼ�
#define MAX_LIFESKILL_COMPOSENUM  300	// ÿ������ܵ�����䷽��Ŀ

#define SKILL_STORAGE_LMT 100			// ���ܿ�����
#define IMMU_SKILL_LMT	  30			// �������ʱ�������ߵļ����б������
#define MAX_MAGICSTONE_USEDTIMES 5		// ��ħ��Ʒ�����ħ����	
#define MAX_COMPOSEkIND_NUM	 23			// ��������͸���
#define DECOMPOUND_MAXTABLEINDEX   32	// װ���ֽ������ȼ��ֶ�(5��Ϊһ��)
#define SKILL_STORAGE_LMT 100		// ���ܿ�����
#define SKILL_BOX_LMT	  5			// �������ܿ��������
#define MAX_EQUIPCOMPOSEID_NUM	100	// װ���һ�������䷽ID����

#define MAX_MUTIBUFFEVENT		11	// ������buff�¼�
#define MAX_EVENTPARAM	6

// �Ż����ȼ�
#define MAX_WIZARD_GRADE	99
// �Ż����ģ����
#define MAX_WIZARD_TEMP		100
#define MAX_JUDGE_LEVEL	12	// ���ۼ�������
#define MAX_JUDGE_OTHER	20	// ������������

#define MAX_PAPERVALUE_NUM	10	// ���ÿ�ֽ�Ǯ�ĵ������п��ܵ�����

#define MAX_PHYSIC_NUM 5	// ҩƷ��������

#define MAX_MW_PERCENT_NUM	200		// �����ٷֱ���ֵ������

#define MAX_ACHIEVE_ITEM	5	// �ɾ�ÿ�����Ʒ����
#define MAX_ACHIEVE_AWARD	100	// �ɾͽ���������
#define MAX_POWER			100	// ��ְȨ�������
#define MAX_OFFICAL_NUM		6	// ÿ����Ա�������
#define MAX_CONSTRUCT_LEVEL	5	// �������ߵȼ�
#define MAX_PEACE_TYPE		7	// �Ѻù�ϵ������
#define MAX_MAP_NUM			200	// ����ͼ����
#define MAX_LEAGUEITEMINBAG	20	// ÿ����������ع���Ʒ�ܹ������������Ʒ����
#define MAX_MATRIX_LEVEL	4	// �������ȼ�
#define MAX_MATRIX_MENBER	130	// �����������
#define MAX_WEDDING_MODULENUM 3	// ���������ģ����
#define MAX_WEDDING_NPCNUM	15	// ��������npc����
#define MAX_WEDDING_KEEPSNAKENUM 20 // ������������
#define MAX_PROGRESSFUNC_NUM	50	// ʹ�ý����������������
#define MAX_COUNT_NUM			100
#define MAX_HYDRANGEA_SUGARNUM  20	// �������׻�����ϲ������
#define MAX_AUTOCOLLECT_MATERIALSNUM 20 //  �Զ��ɼ��Ĳ���Ʒ����

#define MAX_PRELIMINARY_TIMELYLISTNUM	10	// ��ʱ���а���������
#define MAX_MASTER_NUM		3	// ���ʦ������
#define	MAX_BEGINNER_SLAVE_NUM	30	// ������������
#define MAX_MASTER_AWARD_NUM	15	// �����Ե��������

#define MAX_HANDINENCOURAGE_NUM     20      // ����Ͻɽ�����
#define MAX_HANDINTABLE             10      // ����Ͻɽ�����Ӧ����
#define MAX_HANDINENCOURAGE         200     // ����Ͻɽ�������
#define MAX_RUNECOMTYPE				9    // ���������������

#define MAX_CORPSBOSSNUM			20	 // ���ľ���boss��
#define MAX_CASTINGSPIRIT_POSITION			6	 // ���鲿λ��
#define MAX_CASTINGSPIRIT_TYPE				3	 // ����ϵ����
#define MAX_CASTINGSPIRIT_SLOT				8	 // ����ÿ��ϵ�����
#define MAX_SPIRITITEM_GRADE				8	 // ����������ȼ�
#define MAX_SPIRITUPGRADE_ITEMNUM			4	 // ������Ҫ�ĸ������ޣ����������

enum EM_FameType							// ��������
{
	FAME_TYPE_COMBAT			= 1,
	FAME_TYPE_REPE				= 2,
	FAME_TYPE_COMMON			= 3,
};


//---------------------------------------------
// Main Section
//---------------------------------------------

enum TEMPTYPE
{
	TEMP_LEVELEXP       = 0,				// �ȼ������
	TEMP_DATA       = 1,					// ��ֵ������
	TEMP_UPGRADE       = 2,					// װ��������
	TEMP_OPENSLOT       = 3,				// ���۱�
	TEMP_PROSUIT       = 4,					// ��������װ
	TEMP_PROEXP       = 5,					// �����ȼ��ľ���
	TEMP_BEGINNER       = 6,				// ��������
	TEMP_DROPLEVEL       = 7,				// ����װ���ȼ���
	TEMP_HONORTOEXP       = 8,				// ��ѫ����ת����
	TEMP_HONOROBTAIN       = 9,				// ��ѫ��ñ�
	TEMP_RELIVETABLE       = 10,			// ����ѱ�
	TEMP_QUESTIONEXPTABLE       = 11,		// ���⾭���
	TEMP_REDSTONEEXPTABLE       = 12,		// �ڵ������
	TEMP_BINDCHARGETABLE       = 13,		// �󶨻��ѱ�
	TEMP_PKVALUE       = 14,				// PKֵ��Χ��
	TEMP_TITLE       = 15,					// �ƺ����ñ�
	TEMP_TALENT       = 16,					// �컯��
	TEMP_MAGIC_WEAPON_PRO       = 17,		// ��������������
	TEMP_MULTIBUFF       = 18,				// buff���
	TEMP_CDGROUP       = 19,				// ��ȴʱ��
	TEMP_LIGHT       = 20,					// ��������
	TEMP_APCONFIG       = 21,				// �������ñ�
	TEMP_WIZARD       = 22,					// �Ż������
	TEMP_JUDGECONFIG       = 23,			// �������ñ�
	TEMP_OFFICAL       = 24,				// ��ְ���ܱ�
	TEMP_OFFICALLIST       = 25,			// ��ְ���ñ�
	TEMP_KING       = 26,					// ��������
	TEMP_CONSTRUCTEXP       = 27,			// ����ȱ�
	TEMP_ADDPKTABLE       = 28,				// PK���ӱ�
	TEMP_MAPTABLE       = 29,				// ��ͼ������
	TEMP_MULTIATTACKTABLE       = 30,		// Ⱥ���˺���
	TEMP_DOUBLE       = 31,					// ˫��ʱ���
	TEMP_MATRIXTABLE       = 32,			// �������ñ�
	TEMP_COUNT       = 33,					// ������
	TEMP_DIRECT		= 34,					// ֱ�����ñ�
	TEMP_BATTLECONFIG = 35,					// ��ս���ñ�
	TEMP_MONEYLMT_CFG = 36,					// ��Ǯ�������ñ�
	TEMP_FANGCUNTREE = 37,					// ����ɽ����
	TEMP_TALENTSTAGE = 38,					// �컯���
	TEMP_CHANGECAMP = 39,					// ת��Ӫ
	TEMP_ACCUSECONFIG = 40,					// ��������
	TEMP_RUNECOMCONFIG = 41,					// ��������������
	TEMP_ACHIEVEAWARD = 42,					// �ɾͽ�����
	TEMP_GLOBALMAPCONFIG = 43,				// ȫ�ֵ�ͼ���ñ�	
	TEMP_CORPSBOSSTABLE = 44,				// ����boss��
	TEMP_OFFLINEEXPCONFIG = 45,				// ���߾������ñ�
	TEMP_REPEFAMETABLE = 46,				// �����������ñ�
	TEMP_CASTING_SPIRIT_TABLE = 47,			// �������ñ�
};

//---------------------------------------------
// Main Section
//---------------------------------------------

enum ITEMTYPE
{
	ITEM_RETURN       = 1,							// �سǾ���
	ITEM_TELEPORT       = 2,						// ������Ʒ
	ITEM_EQUIPUPG       = 3,						// װ��������Ʒ
	ITEM_RELIFE       = 4,							// �������
	ITEM_PETEGG       = 5,							// ���ﵰ
	ITEM_PETFOOD       = 6,							// ����ʳƷ
	ITEM_UPGLUCK       = 7,							// װ���������˷�
	ITEM_UPGLEAST       = 8,						// װ���������׷�
	ITEM_REFRESHTASK       = 9,						// ˢ�����õ���
	ITEM_TASK       = 10,							// �������
	ITEM_PRODUCE       = 11,						// ����ԭ��
	ITEM_SHOUT       = 12,							// ���Ⱥ�������
	ITEM_PHYSIC       = 13,							// ҩƷ
	ITEM_SKILL       = 14,							// ���ü��ܵ���Ʒ
	ITEM_BOOK       = 15,							// ������
	ITEM_EXP       = 16,							// ���Ӿ������
	ITEM_WEAPON       = 17,							// ����װ��
	ITEM_ARMOR       = 18,							// ����װ��
	ITEM_FASHION       = 19,						// ʱװװ��
	ITEM_RUNE       = 20,							// ���ĵ���
	ITEM_JEWEL       = 21,							// �鱦����
	ITEM_YUANBUG       = 22,						// Ԫ�������
	ITEM_YUANEGG       = 23,						// Ԫ��������
	ITEM_SPECIAL_TASK       = 24,					// ����������Ʒ
	ITEM_AUTOSHOUT                = 25,		        // �Զ���������
	ITEM_HORSE       = 26,							// �������
	ITEM_BINDSTONE                = 27,		        // ��ʯ	
	ITEM_SCROLL       = 28,							// ����
	ITEM_CARD       = 29,							// ��Ƭ
	ITEM_RETURNPAPER       = 30,					// ָ�����;�
	ITEM_TELESYMBOL       = 31,						// ָ�����ͷ�
	ITEM_REDSTONE       = 32,						// �ڵ�
	ITEM_STOVE       = 33,							// ָ��¯ʯ
	ITEM_QUESTIONPAPER       = 34,					// ���
	ITEM_MINEMAP       = 35,						// �ر�ͼ
	ITEM_TOKEN       = 36,							// ��������
	ITEM_KITBAG       = 37,							// ����
	ITEM_REMOVE       = 38,							// ��ʯժ����
	ITEM_CHANGE       = 39,							// ����ת��ʯ
	ITEM_ADAPTER       = 40,						// ��Ʒ������
	ITEM_CALL       = 41,							// �ٻ�����Ʒ
	ITEM_GIFTBAG       = 42,						// �������Ʒ
	ITEM_GOLDSTONE       = 43,						// ���ʯ
	ITEM_PLANT       = 44,							// �ɼ���ֲ��
	ITEM_MINERAL       = 45,						// �ɼ������Ŀ���  	
	ITEM_MAGICWEAPON       = 46,					// ����
	ITEM_MAGICSTONE       = 47,						// ��ħ��Ʒ
	ITEM_LIFESKILLSCROLL       = 48,				// ������䷽����
	ITEM_FUNCITEM       = 49,						// ��������Ʒ
	ITEM_SKILLBOOK       = 50,						// ����������
	ITEM_CORPSTOKEN       = 51,						// ���彫����
	ITEM_REDPAPER       = 52,						// ���
	ITEM_VIP       = 53,							// ��Ա����
	ITEM_CLEAN       = 54,							// ϴ�����
	ITEM_LEAGUEBAG       = 55,						// ��������ع���Ʒ
	ITEM_INVITATION       = 56,						// �������
	ITEM_SYSINVITATION       = 57,					// ϵͳ���ŵ�����	
	ITEM_REFRESH       = 58,						// ϴ���Ե���
	ITEM_SUMMON			= 59,						// �ٻ�����
	ITEM_DIRECT			= 60,						// ֱ������
	ITEM_GETSTAR		= 61,						// ժ����Ʒ
	ITEM_AUTOCOLLECT	= 62,						// �Զ��ɼ�����
	ITEM_BLACKPILLS		= 63,						// �ڹ���
	ITEM_EXPCONTAINER	= 64,							// �������鵤
	ITEM_EXPPILLS		= 65,							// ���鵤
	ITEM_SPIRIT_CASTING	= 67,						// ����
	ITEM_EXP_TOME	= 70,								//�����ĵ£� �°��������鵤
};

enum ADAPTERTYPE
{
	ADAPTER_NPC			= 1,			// NPC������
	ADAPTER_OGRE		= 2,			// ����������	
	ADAPTER_HIEROGRAM	= 3,			// ���������
	ADAPTER_MONEY		= 4,			// ��Ǯ������
	ADAPTER_BINDMONEY	= 5,			// �󶨽�������
	ADAPTER_YUANBAO		= 6,			// Ԫ��������
	ADAPTER_EXP			= 7,			// ����������
	ADAPTER_COLLECTNPC	= 8,			// �ɼ�NPC������
};

enum SKILLITEMOPRTYPE
{
	TYPE_ADDBUFF2SENDNPC = 1,			// �����ڻ��͵�NPC�Ӹ�BUFF
	TYPE_REMOVEBUFF2SENDNPC = 2,		// �����ڻ��͵�NPCȥ��BUFF
};


// ģ�����ͣ����ڴӻ������ָ�������ģ��
enum emTemplateType
{
	EM_TEMPTYPE_NONE	= 0,
	EM_TEMPTYPE_ITEM	= 1,	// ��Ʒ��
	EM_TEMPTYPE_NPC		= 2,	// NPC��
	EM_TEMPTYPE_OGRE	= 3,	// ����
	EM_TEMPTYPE_BLOCK	= 4,	// �赲
	EM_TEMPTYPE_COLLECT	= 5,	// �ɼ�NPC
	EM_TEMPTYPE_BOX		= 6,	// ����
};



// ����ģ��Ļ���
class CTemplate
{
public:
	int		mTempID;

#ifndef TEMPEDIT
	emTemplateType		mTemplateType;
#endif

	CTemplate() 
	{
		mTempID = 0;
#ifndef TEMPEDIT
		mTemplateType = EM_TEMPTYPE_NONE;
#endif
	}

	~CTemplate() {}

};

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			        ## �������ɵ����ݿ���
// name		= �Ͻɽ�����		    ## ģ������
// version	= 1				        ## �汾��
// path		= config/�Ͻɽ�����     ## ·��
// parent	=           	        ## ����ģ��
// ********************************************************************** //

class CTplHandinEncourage : public CTemplate
{
public:
    // �Ͻ���Ʒ����
    enum EN_HANDINITEM_TYPE
    {
        EN_HIIT_ITEM    = 0    // �Ͻ���Ʒ
    };
    // ������Ʒ����
    enum EN_ENCOURAGEITEM_TYPE
    {
        EN_EIT_EXP      = 0    // ���齱��
    };
public:
    // FieldName: �Ͻ���Ʒ����
    // FieldType: INT4
    // Type:	  COMBOENUM(EN_HANDINITEM_TYPE)
    int		      mHandinItemType;	

    // FieldName: �Ͻ���ƷID
    // FieldType: INT4
    // Type:	  EDITNUMBER(0,100000)
    int		      mHandinItemID;

    // FieldName: �Ͻ���Ʒ����
    // FieldType: INT4
    // Type:	  EDITNUMBER(0,100000)
    int		      mHandinItemNum;

    // FieldName: ������Ʒ����
    // FieldType: INT4
    // Type:	   COMBOENUM(EN_ENCOURAGEITEM_TYPE)
    int		      mEncourageType;

    // FieldName: ������ƷID
    // FieldType: INT4
    // Type:	  EDITNUMBER(0,100000)
    int		      mEncourageId;	

    // FieldName: ������Ʒ����
    // FieldType: INT4
    // Type:	  EDITNUMBER(0,100000)
    int		      mEncourageNum;	

public:

    void SetFromPB( bool bServer, PBHandinEncourage* pHandinEncourage );
    void CreateTlvPB( bool bServer, PBHandinEncourage* pHandinEncourage );
    int Initialize();
    CTplHandinEncourage()
    {
        Initialize();
    }
    ~CTplHandinEncourage(){}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			        ## �������ɵ����ݿ���
// name		= �Ͻɽ������ձ�		## ģ������
// version	= 1				        ## �汾��
// path		= config/�Ͻɽ������ձ� ## ·��
// parent	=           	        ## ����ģ��
// ********************************************************************** //

class CTplHandinTable : public CTemplate
{
public:
    // FieldName: ����
    // FieldType: INT4
    // Type:	  EDITNUMBER(0,1000)
    int		      mActivityId;	

    // FieldName: ��%d���Ͻ���Ʒ��Ӧ�õ���
    // FieldType: INT4
    // Type:	  TEMPPATH
    int		      mEncourageTplId[MAX_HANDINENCOURAGE_NUM];	

public:

    void SetFromPB( bool bServer, PBHandinTable* pHandinTable );
    void CreateTlvPB( bool bServer, PBHandinTable* pHandinTable );
    int Initialize();
    CTplHandinTable()
    {
        Initialize();
    }
    ~CTplHandinTable(){}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= true			## �������ɵ����ݿ���
// name		= ���߻�����Ϣ	## ģ������
// version	=				## �汾��
// path		=				## ·��
// parent	=				## ����ģ��
// ********************************************************************** //

class CTplItem : public CTemplate
{
public:	

	enum
	{
		ITEM_RETURN       = 1,								// �سǾ���
		ITEM_TELEPORT       = 2,							// ������Ʒ
		ITEM_EQUIPUPG       = 3,							// װ��������Ʒ
		ITEM_RELIFE       = 4,								// �������
		ITEM_PETEGG       = 5,								// ���ﵰ
		ITEM_PETFOOD       = 6,								// ����ʳƷ
		ITEM_UPGLUCK       = 7,								// װ���������˷�
		ITEM_UPGLEAST       = 8,							// װ���������׷�
		ITEM_REFRESHTASK       = 9,							// ˢ�����õ���
		ITEM_TASK       = 10,								// �������
		ITEM_PRODUCE       = 11,							// ����ԭ��
		ITEM_SHOUT       = 12,								// ���Ⱥ�������
		ITEM_PHYSIC       = 13,								// ҩƷ
		ITEM_SKILL       = 14,								// ���ü��ܵ���Ʒ
		ITEM_BOOK       = 15,								// ������
		ITEM_EXP       = 16,								// ���Ӿ������
		ITEM_WEAPON       = 17,								// ����װ��
		ITEM_ARMOR       = 18,								// ����װ��
		ITEM_FASHION       = 19,							// ʱװװ��
		ITEM_RUNE       = 20,								// ���ĵ���
		ITEM_JEWEL       = 21,								// �鱦����
		ITEM_YUANBUG       = 22,							// Ԫ�������
		ITEM_YUANEGG       = 23,							// Ԫ��������
		ITEM_SPECIAL_TASK       = 24,						// ����������Ʒ
		ITEM_AUTOSHOUT                = 25,		            // �Զ���������
		ITEM_HORSE       = 26,								// �������
		ITEM_BINDSTONE                = 27,		            // ��ʯ
		ITEM_SCROLL       = 28,								// ����
		ITEM_CARD       = 29,								// ��Ƭ
		ITEM_RETURNPAPER       = 30,						// ָ�����;�
		ITEM_TELESYMBOL       = 31,							// ָ�����ͷ�
		ITEM_REDSTONE       = 32,							// �ڵ�
		ITEM_STOVE       = 33,								// ָ��¯ʯ
		ITEM_QUESTIONPAPER       = 34,						// ���
		ITEM_MINEMAP       = 35,							// �ر�ͼ
		ITEM_TOKEN       = 36,								// ��������
		ITEM_KITBAG       = 37,								// ����
		ITEM_REMOVE       = 38,								// ��ʯժ����
		ITEM_CHANGE       = 39,								// ����ת��ʯ
		ITEM_ADAPTER       = 40,							// ��Ʒ������
		ITEM_CALL       = 41,								// �ٻ�����Ʒ
		ITEM_GIFTBAG       = 42,							// �������Ʒ
		ITEM_GOLDSTONE       = 43,							// ���ʯ
		ITEM_PLANT       = 44,								// �ɼ���ֲ��
		ITEM_MINERAL       = 45,							// �ɼ������Ŀ���  	 
		ITEM_MAGICWEAPON       = 46,						// ����
		ITEM_MAGICSTONE       = 47,							// ��ħ��Ʒ
		ITEM_LIFESKILLSCROLL       = 48,					// ������䷽����
		ITEM_FUNCITEM       = 49,							// ��������Ʒ
		ITEM_SKILLBOOK       = 50,							// ����������
		ITEM_CORPSTOKEN       = 51,							// ���彫����
		ITEM_REDPAPER       = 52,							// ���
		ITEM_VIP       = 53,								// ��Ա����
		ITEM_CLEAN       = 54,								// ϴ�����
		ITEM_LEAGUEBAG       = 55,							// ��������ع���Ʒ��
		ITEM_INVITATION       = 56,							// �������
		ITEM_SYSINVITATION       = 57,						// ϵͳ���ŵ�����	
		ITEM_REFRESH       = 58,							// ϴ���Ե���
		ITEM_SUMMON			= 59,							// �ٻ�����
		ITEM_DIRECT			= 60,							// ֱ������
		ITEM_GETSTAR		= 61,							// ժ����Ʒ
		ITEM_AUTOCOLLECT	= 62,							// �Զ��ɼ�����
		ITEM_BLACKPILLS		= 63,							// �ڹ���
		ITEM_EXPCONTAINER	= 64,							// �������鵤
		ITEM_EXPPILLS		= 65,							// ���鵤	
		ITEM_SPIRIT_CASTING	= 67,							// ����
		ITEM_EXP_TOME	= 70,								//�����ĵ£� �°��������鵤
	};

	enum
	{
		PROCESSTYPE_CANSALE		= 0x0001,	// �Ƿ��������
		PROCESSTYPE_MAKEGUID	= 0x0002,	// �Ƿ�����ΨһID
		PROCESSTYPE_BINDONPICK	= 0x0004,	// �Ƿ���ʰȡ���
		PROCESSTYPE_BINDONEQUIP = 0x0008,	// �Ƿ���װ�����
		PROCESSTYPE_BINDONUSER	= 0x0010,	// �Ƿ���ʹ�ú��
		PROCESSTYPE_CANBIND		= 0x0020,	// �Ƿ���ֶ���
		PROCESSTYPE_ISRMBITEM	= 0x0040,	// �Ƿ��������Ʒ
		PROCESSTYPE_ISREFRESHTASK= 0x0080,	// �ܷ�ˢ�¿�����
	};

public:

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOENUM(ITEMTYPE)
	int		mItemType;			

	// FieldName: ����ʽ
	// FieldType: INT4
	// Type:	  CHECKMUTI(�Ƿ��������,�Ƿ�����ΨһID,�Ƿ���ʰȡ���,�Ƿ���װ�����,�Ƿ���ʹ�ú��,�Ƿ���ֶ���,�Ƿ��������Ʒ,�ܷ�ˢ�¿�����)
	int		mProcessType;			

	// FieldName: �ѵ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(1,1000)
	int		mPileLimit;				 

	// FieldName: $������ʾ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mItemName[ STRING32 ];

	// FieldName: ���ߵ���ģ������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mModelName[ STRING32 ];	

	// FieldName: ����ͼ������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mIconName[ STRING32 ];

	// FieldName: ���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mPriceSale;

	// FieldName: ���ߵ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mPricePurchase;	

	// FieldName: $��Ʒ��ϸ˵��
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char	mDescribe[ STRING256 ];

	// FieldName: $������������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mTypeDesc[ STRING32 ];

	// FieldName: �������Ƿ�֧�ְ󶨽�Ǯ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mPurchaseBindMoney;

	// FieldName: ��Чʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mLastTime;	

	// FieldName: ������Ƿ�֧�ְ󶨽�Ǯ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mSaleBindMoney;	

	// FieldName: ʹ�ú��Ƿ�ֹͣ�Զ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��ֹͣ=0,ֹͣ=1)
	int		mStopAttack;

	// FieldName: �Ҽ�����Ƿ����ʹ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mCanUse;

	// FieldName: ʹ�õļ���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mSkillID;

	// FieldName: ��Ʒ�ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mLevel;

	// FieldName: ʹ�ú��Ƿ���ʧ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mDisappear;

	// FieldName: ��ȴ���%d��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mCDGroup[ 25 ];

	// FieldName: ����ʹ�õ�ͼID(0��ʾ������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mUseMapID;

	// FieldName: �Ի����Чʱ��(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,90000000)
	int		mValidTime;

	// FieldName: ��Чʱ���ʱ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(ʹ�ÿ�ʼ��ʱ=0,������ʼ��ʱ=1,װ����ʼ��ʱ=2)
	int		mValidType;

	// FieldName: ���Ƶ�%d�����е�ͼID(0��ʾ������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mLmtMapID[ 5 ];

	// FieldName: �������־
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mCommonID;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mEatType;

	// FieldName: ����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mEatValue;

	// FieldName: ʹ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mCountType;

	// FieldName: ����ʹ�õ���ӪID
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,����=1,Ǭ��=2,����=3,��Ԫ=4)
	int		mLmtLineID;

	// FieldName: ���Ƹ�����ʹ��%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mLmtRepetionID[ 5 ];

	// FieldName: ���Ƶ�%d��ʹ�õ�ͼID(0��ʾ������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mLmtUseMapID[ 20 ];

	// FieldName: �ϳ��䷽ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mCompID;

	// FieldName: ���ھ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,29991231)
	int		mInvilidDate;

public:

	bool IsEquipable( ) const
		{ return mItemType == ITEM_WEAPON || mItemType == ITEM_ARMOR; }
	bool IsMagicWeapon() const
	{
		return mItemType == ITEM_MAGICWEAPON;
	}

	void SetFromPB( bool bServer, PBItemBase* pItem );
	void CreateTlvPB( bool bServer, PBItemBase* pItem );
	int Initialize();

	CTplItem() { 
#ifndef TEMPEDIT
		mTemplateType = EM_TEMPTYPE_ITEM; 
#endif
		Initialize();
	}
	~CTplItem() { }

};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= �سǾ���		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/�سǾ���	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemReturn : public CTplItem
{
public:
	// FieldName: ����ʹ��ʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mTimer;	

public:

	void SetFromPB( bool bServer, PBItemReturn* pItem );
	void CreateTlvPB( bool bServer, PBItemReturn* pItem );
	int Initialize();
	CTplItemReturn()
	{
		Initialize();
	}
	~CTplItemReturn(){}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ����������	## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/����������	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemSkillBook : public CTplItem
{
public:
	enum BOOK_COLOR
	{
		COLOR_NONE    = 0,  // ������
		COLOR_WHITE   = 1,  // ��ɫ
		COLOR_BLUE    = 2,  // ��ɫ
		COLOR_PURPLE  = 3,  // ��ɫ
		COLOR_GOLD    = 4,  // ��ɫ
	};

	// FieldName: ��������ɫ
	// FieldType: INT4
	// Type:	  COMBOENUM(BOOK_COLOR)
	int			mBookColor;

	// FieldName: ��Ӧ����
	// FieldType: INT4
	// Type:	  SKILLPATH
	int			mSkillID;

	// FieldName: �ɹ�����(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mSuccProb;

	// FieldName: ���ĵĽ�Ǯ����
	// FieldType: INT4
	// Type:	  COMBOENUM(MW_DECOMPOS_MONEY_TYPE)
	int			mNeedMoneyType;	

	// FieldName: ���ĵĽ�Ǯ��ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			mNeedMoney;	

public:

	void SetFromPB( bool bServer, PBItemSkillBook* pItem );
	void CreateTlvPB( bool bServer, PBItemSkillBook* pItem );
	int Initialize();
	CTplItemSkillBook(){ Initialize(); }
	~CTplItemSkillBook() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ������
enum FUNC_CODE
{
	FUNCCODE_RECVMWHP	= 1,  // �ָ�����HP  ����0�����ӵĵ���
	FUNCCODE_RECVMWMP	= 2,		  // �ָ�����MP  ����0�����ӵĵ���
	FUNCCODE_JUDGEMWPRO	= 3,	  // ������������ ����0:������Ӧ��Ӱ��ȼ����� ����1:������Ӧ�����Լ�����
	FUNCCODE_FAMILYEXPCARD= 4,	  // ���徭������
	FUNCCODE_CORPSTOKEN	  = 5,	  // ����������
	FUNCCODE_MW_WASH_SMALL= 6,	  // ����Сϴʯ  �޲���
	FUNCCODE_MW_WASH_BIG  = 7,	  // ������ϴʯ  �޲���
	FUNCCODE_WIZARDVALUE  = 8,	  // ��òŻ�ֵ����  ����0 ��� ����1 �Ż�ֵ
	FUNCCODE_GETTITLE     = 9,		  // �ƺž��� ����0 �ƺ�ID
	FUNCCODE_LIHUA		  = 10,	  // �񻨵��� 0:���ŷ�ʽ 1:����Сֵ 2:�����ֵ 3:���Ÿ���4:buff���5:����6:�����id
	FUNCCODE_XIANHUA	  = 11,		  // �ʻ����� ����0:��Ӧ�ڵ������ID ����1:����ֵ ����2:�Ƿ�㲥 ����3:������Ч�Ĳ��� ����4:��ȡ�����ܶ�ֵ
	FUNCCODE_MATRIX		  = 12,		  // �������� ����0 �����ĵȼ� ����1 �����ĵ���	
	FUNCCODE_LEVEL		  = 13,			  // �������� ����0 ���ʹ�õȼ�
	FUNCCODE_MONEYTREE	  = 14,		  // ҡǮ��
	FUNCCODE_REPAIR		  = 15,		  // �������
	FUNCCODE_COMMONBIND	  = 16,	  // ��ͨ�󶨵���
	FUNCCODE_NEEDLE		  = 17,		  // �廨��	����0���廨�����õ���󱳰������� ����1������ʹ��ʱ��(����)
	FUNCCODE_LUCKYBAG	  = 18,		  // Ǭ���� ����0�����ID(Ĭ����ģ��ID) ����1:�Ƿ���������ɲ��ܿ���
	FUNCCODE_CLEARRED	  = 19,		// ϴ�������� ����0�����Ƶȼ�
	FUNCCODE_FAMILY_MONEY = 20,		// ����� ����0�� ��Ǯ��
	FUNCCODE_CORPS_MONEY = 21,		// ���Ž� ����0�� ��Ǯ��
	FUNCCODE_DUNGEON_TIME_DEL = 22,	// ������������� ����0: ����ID (��ʱ��֧�ּ�һ��) 
	FUNCCODE_EXTRA		 = 23,		// ӡ����Ʒ ����0 : ӡ����	
	FUNCCODE_POINT		 = 24,		// ��Ǳ�ܵ㼼�ܵ� ����0 Ǳ�ܵ��� ����1 ���ܵ���  ����2 ʹ�õȼ�  
	FUNCCODE_EXP		= 25,		// ������� ����0��������1:�����ģ��id 2:������ֱ� 
	FUNCCODE_ACTIVITY	= 26,		// ����� ����0:�ID 1:�����¼�ID
    FUNCCODE_XIANLU     = 27,       // ��¶���� ����0��0ΪС��¶��1Ϊ����¶��2Ϊ����¶
    FUNCCODE_JINPING    = 28,       // ��ƿ���� ����0��0Ϊ����ƿ���У�1Ϊ����ƿ����
    FUNCCODE_JINYEZHI   = 29,       // ��Ҷ�ӵ���
	FUNCCODE_FASHIONNEEDLE= 30,       // ʱװ�廨��	����0:ʱװ����:(1.��2.��4.��8.�� :ʹ��ʱ��ɫֵ�Ӻ�) ����1:ʱװ�ӳ���ʱ��(����)
	FUNCCODE_CLEARMWSP  = 31,       // ����������ܵ����
	FUNCCODE_CHANGERUNE = 32,       // ת����
	FUNCCODE_DIGITALFIREWORKS = 33, // ������	����0:���Բ�������Ŀ	 ����1:��Ч����
	FUNCCODE_UPRUNE     = 34,       //���������� ����0������
	FUNCCODE_QILING     = 35,       // �������� ����0-4:�ӳ��񶨷����������� 5:�滻�󷨱����ܿ�� 6:��ɫ 7:Ʒ�� 8:ӡ�Ǹ��� 9:ӡ�Ƿ��� 10:�ϳɽ������ 11:�ϳɽ�� 12:����ID 13:��������
	FUNCCODE_MWPIECE     = 36,       // ������Ƭ ����0:Ʒ��
	FUNCCODE_MWPRNTLUCKY     = 37,       // ����ӡ�����˷� ����0:���Ӹ�����ֱ� ����1:Ʒ��
	FUNCCODE_MWGETEXP     = 38,       // �������鵤 ����0:�����ID
	FUNCCODE_CORPCRYSTAL  = 39,		  // BOSS���� ����0: BOSS ID	  ����1:����ֵ  ����2: �������� ����3:���Ź��׶�
	FUNCCODE_CORPBOSSSTONE = 40,	  // ������  ����0:������ ����1:���Ź��׶�
	FUNCCODE_FAME		 = 41,		  // ���� ����0�����1����2����3����������1������ֵ
};

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ��������Ʒ	## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/��������Ʒ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplFuncItem : public CTplItem
{
public:

	// FieldName: ���߹���
	// FieldType: INT4
	// Type:	  COMBOENUM(FUNC_CODE)
	int		mFuncCode;	

	// FieldName: ����0
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����1
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����2
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����3
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����4
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����5
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����6
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����7
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����8
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����9
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����-10
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����-11
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����-12
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����-13
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����-14
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)

	// FieldName: ����-15
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,100000000)
	int		mParams[16];	

public:
	void SetFromPB( bool bServer, PBFuncItem* pItem );
	void CreateTlvPB( bool bServer, PBFuncItem* pItem );
	int Initialize();
	CTplFuncItem() {Initialize();}
	~CTplFuncItem(){}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ��ʯ		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/��ʯ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemBindStone : public CTplItem
{
public:
	//��ʯ����
	enum BINDSTONE_TYPE
	{
		BINDSTONE_EQUIP                = 0,			// װ����ʯ
		BINDSTONE_MAGICWEAPON  = 1,			// ������ʯ
	};
public:
	// FieldName: ������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mFaceGroupID;	

	// FieldName: ��ʯ����
	// FieldType: INT4
	// Type:	COMBOENUM(BINDSTONE_TYPE)
	int			mBindStoneType;

public:
	void SetFromPB( bool bServer, PBItemBindStone* pItem );
	void CreateTlvPB( bool bServer, PBItemBindStone* pItem );
	int Initialize();
	CTplItemBindStone(){Initialize();}
	~CTplItemBindStone() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ����			## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/����		## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemScroll : public CTplItem
{
public:

	// FieldName: ʹ�ú󴥷�����
	// FieldType: INT4
	// Type:	  TASKPATH
	int		mGetTaskID;	

public:
	void SetFromPB( bool bServer, PBItemScroll* pItem );
	void CreateTlvPB( bool bServer, PBItemScroll* pItem );
	int Initialize();
	CTplItemScroll(){Initialize();}
	~CTplItemScroll(){}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //



// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= �ٻ�����Ʒ	## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/�ٻ�����Ʒ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemCall : public CTplItem
{
public:

	// FieldName: ʹ�ú��ٻ�NPC
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mCallNpcID;	

	// FieldName: �ٻ�NPCλ�õ�x���� -1��ʾ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,1000)
	int		mX;	

	// FieldName: �ٻ�NPCλ�õ�y���� -1��ʾ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,1000)
	int		mY;	

	// FieldName: ʹ�ú��Ƿ���ʧ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int		mIsDestroy;	

	// FieldName: �ٻ�NPC���ڵĵ�ͼ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMapID;	

	// FieldName: ʹ�������������ڵ�ͼID(0������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mLmtMapID;	

	// FieldName: ʹ��������������X
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,100000)
	int		mLmtX;	

	// FieldName: ʹ��������������Y
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,100000)
	int		mLmtY;	

	// FieldName: ʹ������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mLmtWide;	

	// FieldName: ʹ����������߶�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mLmtHeight;	


public:
	void SetFromPB( bool bServer, PBItemCall* pItem );
	void CreateTlvPB( bool bServer, PBItemCall* pItem );
	int Initialize();
	CTplItemCall(){	Initialize();}
	~CTplItemCall() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ��Ƭ			## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/��Ƭ		## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemCard : public CTplItem
{
	enum EType
	{
		CARD_YMZ	= 0,	// ��ħ־
		CARD_SBB,			// �����
		CARD_MCP,			// ������
		CARD_FSJ,			// �����
		CARD_FWL,			// ����¼
	};

public:
	// FieldName: $��ʾ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mShowText[ STRING32 ];

	// FieldName: ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mOrder;	

	// FieldName: $����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mWeapon[ STRING32 ];

	// FieldName: $����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mSkill[ STRING32 ];

	// FieldName: $�ȼ�
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mLevel[ STRING32 ];

	// FieldName: ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mExp;	

	// FieldName: �Ƿ���Զһ�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mCanExchange;

	// FieldName: �Ƿ������ս
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mCanChallenge;

	// FieldName: ��Ƭ����
	// FieldType: INT4
	// Type:	  COMBOENUM(EType) 
	int		mType;	

	// FieldName: λ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mPos;

	// FieldName: ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mBonus;

	// FieldName: ����ID1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mSkillID1;

	// FieldName: ����ID2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mSkillID2;

public:
	void SetFromPB( bool bServer, PBItemCard* pItem );
	void CreateTlvPB( bool bServer, PBItemCard* pItem );
	int Initialize();
	CTplItemCard(){ Initialize();}
	~CTplItemCard() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ������Ʒ		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/������Ʒ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemTeleport : public CTplItem
{
public:
	// FieldName: ת�͵�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(�������=1,�ع�����=2,���䴫��=3,�б��ʹ��͵���=4)
	int		mMapID;		

	// FieldName: ����ʹ�õĴ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mUseTimes;		

public:
	void SetFromPB( bool bServer, PBItemTeleport* pItem );
	void CreateTlvPB( bool bServer, PBItemTeleport* pItem );
	int Initialize();
	CTplItemTeleport() {Initialize();}
	~CTplItemTeleport() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ���ɷ��ؾ�	## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/���ɷ��ؾ�	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplReturnPaper : public CTplItem
{
public:
	// FieldName: ���ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mLineID;

	// FieldName: ������ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMapID;

	// FieldName: x����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mPosX;

	// FieldName: y����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mPosY;

public:
	void SetFromPB( bool bServer, PBItemReturnPaper* pItem );
	void CreateTlvPB( bool bServer, PBItemReturnPaper* pItem );
	int Initialize();
	CTplReturnPaper() { Initialize(); }
	~CTplReturnPaper() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ���ͷ�		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/���ͷ�	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplTeleSymbol : public CTplItem
{
public:
	// FieldName: ���ͱ�ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mTeleTable;

	// FieldName: ʹ�ô���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mUseTimes;

public:
	void SetFromPB( bool bServer, PBItemTeleSymbol* pItem );
	void CreateTlvPB( bool bServer, PBItemTeleSymbol* pItem );
	int Initialize();
	CTplTeleSymbol() { Initialize(); }
	~CTplTeleSymbol() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ¯ʯ			## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/¯ʯ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplStove : public CTplItem
{
public:
	// FieldName: ���ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mLineID;

	// FieldName: ������ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMapID;

	// FieldName: x����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mPosX;

	// FieldName: y����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mPosY;

	// FieldName: ��ȴʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mCoolTime;

	// FieldName: ְҵ����
	// FieldType: INT4
	// Type:	  CHECKMUTI(����=0,սʿ,����,����,��ʦ,��ʿ,����ʦ,����)
	int		mMetierRequire;
	
	// FieldName: �ȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,160)
	int		mLevelRequire;

public:
	void SetFromPB( bool bServer, PBItemStove* pItem );
	void CreateTlvPB( bool bServer, PBItemStove* pItem );
	int Initialize();
	CTplStove() { Initialize(); }
	~CTplStove() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ���ﵰ		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/���ﵰ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplPetEgg : public CTplItem
{
public:
	// FieldName: ת�͵���ĵ�ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mPetTempID;				

	// FieldName: ������Ҫ�ĵ���ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mNeedItemID;			

	// FieldName: ��ԭ��Ҫ�ļ۸�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mRevertPrice;			

	// FieldName: ��ʼ�ҳ϶�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitAdvice;	

	// FieldName: ��ʼ�ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mInitLevel;

	// FieldName: ��ʼ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mInitExp;				

	// FieldName: ��ʼ���ܵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mInitSkillPoint;		

	// FieldName: ��1���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��2���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��3���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��4���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��5���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��6���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��7���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��8���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��9���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��10���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��11���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��12���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��13���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��14���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��15���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��16���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��17���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��18���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��19���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��20���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��21���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��22���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��23���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��24���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��25���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��26���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��27���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��28���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��29���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��30���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��31���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��32���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH
	int		mInitSkillID[ 32 ];		

	// FieldName: ��1���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��2���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��3���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��4���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��5���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��6���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��7���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��8���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��9���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��10���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��11���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��12���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��13���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��14���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��15���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��16���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��17���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��18���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��19���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��20���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��21���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��22���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��23���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��24���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��25���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��26���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��27���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��28���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��29���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��30���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��31���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ��32���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)
	int		mInitSkillLevel[ 32 ];	 

public:
	void SetFromPB( bool bServer, PBItemPetEgg* pItem );
	void CreateTlvPB( bool bServer, PBItemPetEgg* pItem );
	int Initialize();
	CTplPetEgg() { Initialize(); }
	~CTplPetEgg() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ����ʳƷ		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/����ʳƷ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplPetFood : public CTplItem
{
public:
	enum
	{
		FOOD_FUITE = 1,		// ˮ����ʳƷ
		FOOD_MEET  = 2,		// ����ʳƷ
		FOOD_WATER = 3,		// ������ʳƷ
	};

public:
	// FieldName: ��ʼ�ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)
	int		mInitLevel;	

	// FieldName: ���ӵı�ʳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)
	int		mFullLevel;				

	// FieldName: ʳ���������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(ˮ����ʳƷ,����ʳƷ,������ʳƷ)
	int		mTypeMask;	

public:
	void SetFromPB( bool bServer, PBItemPetFood* pItem );
	void CreateTlvPB( bool bServer, PBItemPetFood* pItem );
	int Initialize();
	CTplPetFood() { Initialize(); }
	~CTplPetFood() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= �������		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/�������	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTplItemRelife : public CTplItem
{
public:
	// FieldName: ʹ��ʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mTimer;				

	// FieldName: ��ȴʱ�䣨���룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mCooldown;			

	// FieldName: �Ƿ��������Ʒ������ȴ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int		mShareCD;	

public:
	void SetFromPB( bool bServer, PBItemRelife* pItem );
	void CreateTlvPB( bool bServer, PBItemRelife* pItem );
	int Initialize();
	CTplItemRelife() { Initialize(); }
	~CTplItemRelife() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ���ü��ܵ���Ʒ		## ģ������
// version	= 1						## �汾��
// path		= ��Ʒ/���ü��ܵ���Ʒ	## ·��
// parent	= ���߻�����Ϣ			## ����ģ��
// ********************************************************************** //
class CTplItemSkill : public CTplItem
{
public:
	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOENUM(SKILLITEMOPRTYPE)
	int		mOprType;

	// FieldName: ʹ�õĵȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,160)
	int		mLevelLimit;		

	// FieldName: ���õļ���ID
	// FieldType: INT4
	// Type:	  SKILLPATH
	int		mSkillID;	

	// FieldName: ��ȴʱ�䣨���룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mCooldown;				

	// FieldName: �Ƿ��������Ʒ������ȴ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int		mShareCD;

	// FieldName: ���BUFF ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mBuffID;

public:
	void SetFromPB( bool bServer, PBItemSkill* pItem );
	void CreateTlvPB( bool bServer, PBItemSkill* pItem );
	int Initialize();
	CTplItemSkill() { Initialize(); }
	~CTplItemSkill() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= װ��������Ʒ		## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/װ��������Ʒ	## ·��
// parent	= ���߻�����Ϣ		## ����ģ��
// ********************************************************************** //
class CTplItemEquipUpg : public CTplItem
{
public:
	enum enUpType
	{
		UPTYPE_EQUIT = 0, // ����װ��
		UPTYPE_MW    = 1, // ��������
	};
	// FieldName: ����ʹ�õĵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mMaxLevel;	

	// FieldName: ���
	// FieldType: INT4
	// Type:	  CHECKMUTI(װ������=0,��������,��������)
	int			mType;	

	// FieldName: ����
	// FieldType: INT4
	// Type:	  CHECKMUTI(��=0,��,��)
	int			mLimit;	

	// FieldName: �Ƿ�����ʧ��
	// FieldType: INT4
	// Type:	  CHECKMUTI(��=0,��=1)
	int			mFail;	 

	// FieldName: �����ɹ�������%d���ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mLuck[ 4 ];

	// FieldName: ����Ŀ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(װ��=0,����=1)
	int			mUpType;	 

public:
	void SetFromPB( bool bServer, PBItemUpg* pItem );
	void CreateTlvPB( bool bServer, PBItemUpg* pItem );
	int Initialize();
	CTplItemEquipUpg() { Initialize(); }
	~CTplItemEquipUpg() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= D����Ʒ		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/D����Ʒ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTplItemBook : public CTplItem
{
public:

	enum OPType
	{
		TYPE_NONE		= 0,		// ������
		TYPE_ADDSLOT	= 1,		// ����
		TYPE_JUDGE		= 2,		// ����
		TYPE_UNION		= 3,		// ��������
		TYPE_JEWEL		= 4,		// ��ʯ�ϳ�
		TYPE_KEY		= 5,		// ������
		TYPE_CARVE		= 6,		// ������
		TYPE_OPENEXPTOME	=	7, // ���������ĵ�
	};

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOENUM(OPType) 
	int			mOPType;

public:
	void SetFromPB( bool bServer, PBItemBook* pItem );
	void CreateTlvPB( bool bServer, PBItemBook* pItem );
	int Initialize();
	CTplItemBook() { Initialize(); }
	~CTplItemBook() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= װ���������˷�		## ģ������
// version	= 1						## �汾��
// path		= ��Ʒ/װ���������˷�	## ·��
// parent	= ���߻�����Ϣ			## ����ģ��
// ********************************************************************** //
class CTplUpgLuck : public CTplItem
{
public:
	// FieldName: ��߾����ɹ��ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mIncLuck1;	

	// FieldName: ��߾���ʧ�ܺ�ֻ��һ���ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mIncLuck2;	

	// FieldName: ��߾����ɹ�������%d���ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mIncLuck3[ 4 ];

	// FieldName: ����ĵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mLevel;	

public:
	void SetFromPB( bool bServer, PBItemUpgLuck* pItem );
	void CreateTlvPB( bool bServer, PBItemUpgLuck* pItem );
	int Initialize();
	CTplUpgLuck() { Initialize(); }
	~CTplUpgLuck() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= װ���������׷�		## ģ������
// version	= 1						## �汾��
// path		= ��Ʒ/װ���������׷�	## ·��
// parent	= ���߻�����Ϣ			## ����ģ��
// ********************************************************************** //
class CTplUpgLeast : public CTplItem
{
public:
	// FieldName: ��߾����ɹ��ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mIncLuck1;			
	
	// FieldName: ��߾���ʧ�ܺ�ֻ��һ���ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mIncLuck2;	

	// FieldName: ʹ�õ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(װ��=0,��ʯ=1)
	int			mType;

public:
	void SetFromPB( bool bServer, PBItemUpgLeast* pItem );
	void CreateTlvPB( bool bServer, PBItemUpgLeast* pItem );
	int Initialize();
	CTplUpgLeast() 
	{
		Initialize();
	}
	~CTplUpgLeast() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ��ʯժ����	## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/��ʯժ����	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTplItemRemove : public CTplItem
{
public:
	// FieldName: ���͵�%d���ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mRand[ 9 ];

	// FieldName: ժ�����Ƿ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mBind;

	// FieldName: ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mLevel;

	// FieldName: �Ƿ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mLow;

public:
	void SetFromPB( bool bServer, PBItemRemove* pItem );
	void CreateTlvPB( bool bServer, PBItemRemove* pItem );
	int Initialize();
	CTplItemRemove() 
	{
		Initialize();
	}
	~CTplItemRemove(){}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ����ת��ʯ	## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/����ת��ʯ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTplItemChange : public CTplItem
{
public:
	// FieldName: ת��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1)
	int			mType;

	// FieldName: ת���������
	// FieldType: INT4
	// Type:	  CHECKMUTI(���1,���2,���3,���4,���5,���6)
	int		mRes;

	// FieldName: ְҵ����
	// FieldType: INT4
	// Type:	  CHECKMUTI(����=0,սʿ,����,����,��ʦ,��ʿ,����ʦ,����)
	int		mMetierRequire;

public:
	void SetFromPB( bool bServer, PBItemChange* pItem );
	void CreateTlvPB( bool bServer, PBItemChange* pItem );
	int Initialize();
	CTplItemChange() { Initialize(); }
	~CTplItemChange() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ���					## ģ������
// version	= 1						## �汾��
// path		= ��Ʒ/���				## ·��
// parent	= ���߻�����Ϣ			## ����ģ��
// ********************************************************************** //
class CTplQuestionPaper : public CTplItem
{
public:
	// FieldName: ��������%d����ʱ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mQuestionRate[MAX_QUESTION_NUM];	
		
	// FieldName: �����ľ���ӳɰٷֱ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mExpAddRae;	
	
	// FieldName: �����ÿ����Ŀ�Ĵ���ʱ������,������-1 ��ʾû������
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,1000000)
	int			mEachTimeLength;	
	
	// FieldName: �����������Ŀ�Ĵ���ʱ������,������-1��ʾû������
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,100000000)
	int			mTotalTimeLength;	
	
	// FieldName: �����ÿ����Ŀ������Ĵ�����-1��ʾû������
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,100)
	int			mRepeatTimeAllowed;	

public:
	void SetFromPB( bool bServer, PBItemQuestion* pItem );
	void CreateTlvPB( bool bServer, PBItemQuestion* pItem );
	int Initialize();
	CTplQuestionPaper() 
	{
		Initialize();
	}
	~CTplQuestionPaper() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //



// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ˢ�����õ���		## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/ˢ�����õ���	## ·��
// parent	= ���߻�����Ϣ		## ����ģ��
// ********************************************************************** //
class CTplItemTask : public CTplItem
{
public:
	// FieldName: ����ʹ�õĴ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,2000000000)
	int		mUseTimes;	

	// FieldName: ʹ��ʱ����ʱ��(��,0=������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)
	int		mUsingTime;	

	// FieldName: $����ʱ�ͻ�����ʾ����
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char	mShowText[ STRING256 ];
    
	// FieldName: ʹ�������������ڵ�ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMapID;	

	// FieldName: ʹ��������������X
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,100000)
	int		mX;	

	// FieldName: ʹ��������������Y
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,100000)
	int		mY;	

	// FieldName: ʹ������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mWide;	

	// FieldName: ʹ����������߶�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mHeight;	

	// FieldName: ʹ�ú󴥷�����
	// FieldType: INT4
	// Type:	  TASKPATH
	int		mGetTaskID;	

	// FieldName: ʹ�ú󷢷ŵ���
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mGiveItemID;	

	// FieldName: ������������һ��Ʒ(Ҫ�󲻿ɶѵ���)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mChangeTime;	

	// FieldName: ��ʱ����ɵ���һ��Ʒ
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mChangeItem;	

	// FieldName: ��ʱ��ǿ�����ĸ�����ʧ��
	// FieldType: INT4
	// Type:	  TASKPATH
	int		mFailTaskID;	

public:
	void SetFromPB( bool bServer, PBItemTask* pItem );
	void CreateTlvPB( bool bServer, PBItemTask* pItem );
	int Initialize();
	CTplItemTask() 
	{
		Initialize();
	}
	~CTplItemTask();
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �������			## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/�������		## ·��
// parent	= ˢ�����õ���		## ����ģ��
// ********************************************************************** //
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ����������Ʒ		## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/����������Ʒ	## ·��
// parent	= ˢ�����õ���		## ����ģ��
// ********************************************************************** //
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ����ԭ��		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/����ԭ��	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTplItemStuff : public CTplItem
{
public:
	// FieldName: ��ʾ��ɫ�������Ͻ�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��ɫԭ��,��ɫԭ��,��ɫԭ��,��ɫԭ��)
	int		mShowColour;

	// FieldName: �ϳɵ��䷽ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int mComposeID;

public:
	void SetFromPB( bool bServer, PBItemStuff* pItem );
	void CreateTlvPB( bool bServer, PBItemStuff* pItem );
	int Initialize();
	CTplItemStuff()
	{
		Initialize();
	}
	~CTplItemStuff() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ���Ӿ������		## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/���Ӿ������	## ·��
// parent	= ���߻�����Ϣ		## ����ģ��
// ********************************************************************** //
class CTplItemExp : public CTplItem
{
public:
	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,2)
	int		mIncRate;		 

	// FieldName: ����ʱ�䣨�룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mTime;	

public:
	void SetFromPB( bool bServer, PBItemExp* pItem );
	void CreateTlvPB( bool bServer, PBItemExp* pItem );
	int Initialize();
	CTplItemExp() 
	{
		Initialize();
	}
	~CTplItemExp(){}
};


// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ��������		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/��������	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTplItemShout : public CTplItem
{
public:	
	// FieldName: ������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mFaceGroupID;

public:
	void SetFromPB( bool bServer, PBItemShout* pItem );
	void CreateTlvPB( bool bServer, PBItemShout* pItem );
	int Initialize();
	CTplItemShout()
	{
		Initialize();
	}
	~CTplItemShout() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= �Զ�����		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/�Զ�����	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTplItemAutoShout : public CTplItem
{
public:	
	// FieldName: ������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mFaceGroupID;

public:
	void SetFromPB( bool bServer, PBItemAutoShout* pItem );
	void CreateTlvPB( bool bServer, PBItemAutoShout* pItem );
	int Initialize();
	CTplItemAutoShout() 
	{
		Initialize();
	}
	~CTplItemAutoShout() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ҩƷ			## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/ҩƷ		## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTplItemPhysic : public CTplItem
{
public:
	enum EM_PhisicType
	{
		PHISICTYPE_COMMON		= 1,	// ��ͨҩƷ
		PHISICTYPE_LIFESKILL	= 2,	// �����ҩƷ
		PHISICTYPE_AP			= 3,	// ����ҩƷ
		PHISICTYPE_SPECIAL		= 4,	// ����ҩƷ
	};

	enum EM_PHYSIC_COLOR
	{
		PHYSIC_WHITE	= 0,			// ��ɫ
		PHYSIC_BLUE,					// ��ɫ
		PHYSIC_PURPLE,					// ��ɫ
		PHYSIC_GOLD,					// ��ɫ
		PHYSIC_COLOR,					// ��ɫ
	};
public:
	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(�����=0,��1��=100,��2��,��3��,��4��,��1��,��2��,��3��,��4��,��1��,��2��,��3��,��4��,��1��,��2��,��3��,��4��,��1��,��2��,��3��,��4��,����ҩ,�����ҩ)
	int			mShowType;	

	// FieldName: BUFF���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mBuffID;

	// FieldName: �ȼ�Ҫ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,160)
	int			mLevelRequire;	
	
	// FieldName: HP���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int			mHPValue;			

	// FieldName: HP�ָ���Ҫʱ�䣨���룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mHPTime;

	// FieldName: HPÿ�λָ���������룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mHPIncTime;

	// FieldName: HPÿ�λָ�ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int			mHPIncValue;

	// FieldName: MP���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int			mMPValue;			

	// FieldName: MP�ָ���Ҫʱ�䣨���룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mMPTime;

	// FieldName: MPÿ�λָ���������룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mMPIncTime;

	// FieldName: MPÿ�λָ�ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mMPIncValue;

	// FieldName: ��ȴʱ�䣨���룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int			mCooldown;			

	// FieldName: �Ƿ��������Ʒ������ȴ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mShareCD;	
	
	// FieldName: �Զ��ظ��ĺ�ٷֱ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mHPPercent;

	// FieldName: �Զ��ظ������ٷֱ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mMPPercent;

	// FieldName: ���ظ��ĺ�ٷֱ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mMaxHPPercent;

	// FieldName: ���ظ������ٷֱ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mMaxMPPercent;
	
	// FieldName: ���������
	// FieldType: INT4
	// Type:	  COMBOENUM(EM_LIFESKILL)
	int			mLifeSkillType;
	
	// FieldName: ʹ�ú������������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mDegreeValue;
	
	// FieldName: ҩƷ����
	// FieldType: INT4
	// Type:	  COMBOENUM(EM_PhisicType)
	int		mPhysicType;	

	// FieldName: ��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mApValue;
	
	// FieldName: ҩƷ��ɫ
	// FieldType: INT4
	// Type:	  COMBOENUM(EM_PHYSIC_COLOR)
	int		mColor;
public:
	void SetFromPB( bool bServer, PBItemPhysic* pItem );
	void CreateTlvPB( bool bServer, PBItemPhysic* pItem );
	int Initialize();
	CTplItemPhysic() 
	{
		Initialize();
	}
	~CTplItemPhysic() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ����			## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/����		## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTplItemHorse : public CTplItem
{
public:
	// FieldName: ְҵ����
	// FieldType: INT4
	// Type:	  CHECKMUTI(����=0,սʿ,����,����,��ʦ,��ʿ,����ʦ,����)
	int			mMetierRequire;

	// FieldName: �ȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mLevelRequire;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mPersonRequire;

	// FieldName: ʹ��ʱ�䣨���룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mUseTime;

	// FieldName: �ٶ����Ӱٷֱȣ�����ֱȣ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mIncreaseSpeedPer;

	// FieldName: �����Ӧģ��·��
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		mModelName[ STRING32 ];

	// FieldName: ��ȴʱ�䣨���룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int			mCooldown;

	// FieldName: �Ƿ��������Ʒ������ȴ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mShareCD;

	// FieldName: ��Ӧ����BUFF
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mSpeedBuff;

	// FieldName: ʹ��ʱ����ʱ��(��,0=������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,500000)
	int		mUsingTime;	

	// FieldName: $����ʱ�ͻ�����ʾ����
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char	mShowText[ STRING256 ];

	// FieldName: ���������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mOffHorseProb;

	// FieldName: ������������ϵ�BUFF
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mOffBuffID;

	// FieldName: �������ĵĻ���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mInitAP;

	// FieldName: ����ÿ�����ĵĻ���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mDeltaAP;

public:
	void SetFromPB( bool bServer, PBItemHorse* pItem );
	void CreateTlvPB( bool bServer, PBItemHorse* pItem );
	int Initialize();
	CTplItemHorse() 
	{
		Initialize();
	}
	~CTplItemHorse() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ����			## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/����		## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTplKitBag : public CTplItem
{	
public:	
	// FieldName: ������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mFaceGroupID;

	// FieldName: ������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(1,48)
	int			mIndexNum;	  
public:	
	void SetFromPB( bool bServer, PBItemKitBag* pItem );
	void CreateTlvPB( bool bServer, PBItemKitBag* pItem );
	int Initialize();
	CTplKitBag() 
	{
		Initialize();
	}
	~CTplKitBag() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= �������Ʒ	## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/�������Ʒ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTplGiftBag : public CTplItem
{	
public:	
	// FieldName: ʹ��ʱ��Ҫ��ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mMinLevel;

	// FieldName: ��Ǯ��Сֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mMinMoney;

	// FieldName: ��Ǯ���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mMaxMoney;

	// FieldName: �󶨽�Ǯ��Сֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mMinBindMoney;

	// FieldName: �󶨽�Ǯ���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mMaxBindMoney;

	// FieldName: ��Ԫ����Сֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mMinSilverYB;

	// FieldName: ��Ԫ�����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mMaxSilverYB;

	// FieldName: ������Сֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mMinExp;

	// FieldName: �������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mMaxExp;

	// FieldName: �����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mDropTableID;

	// FieldName: ������Ʒ�Ƿ�ֱ�ӽ��� 
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int			mDropInBag;

	// FieldName: �Ƿ�������ռ� 
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int			mCheckBag;

	// FieldName: ��%d�ȼ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mLevelTableID[TMP_MAX_GRADE];

	// FieldName: ��Ӧ����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mLiHuaID;

	// FieldName: ������Ҫ�ĵ�%d����ƷID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mOpenItemID[ 5 ];

	// FieldName: �����ĵ�%d�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mOpenTableID[ 5 ];

public:	
	void SetFromPB( bool bServer, PBItemGiftBag* pItem );
	void CreateTlvPB( bool bServer, PBItemGiftBag* pItem );
	int Initialize();
	CTplGiftBag()
	{
		Initialize();
	}
	~CTplGiftBag() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= װ����������			## ģ������
// version	= 1						## �汾��
// path		= װ����������			## ·��
// parent	=						## ����ģ��
// ********************************************************************** //
class CTemplateProperty : public CTemplate
{
public:
	enum PROPERTY_FUNC
	{
		PROPERTYINC_PATTACKPER       = 1,		// �����﹥�ٷֱ�
		PROPERTYINC_MATTACKPER       = 2,		// ���ӷ����ٷֱ�
		PROPERTYINC_PDEFENCEPER       = 3,		// ��������ٷֱ�
		PROPERTYINC_MDEFENCEPER       = 4,		// ���ӷ����ٷֱ�
		PROPERTYINC_PATTACKFIX       = 5,		// �����﹥�̶�ֵ
		PROPERTYINC_MATTACKFIX       = 6,		// ���ӷ����̶�ֵ
		PROPERTYINC_PDEFENCEFIX       = 7,		// ��������̶�ֵ
		PROPERTYINC_MDEFENCEFIX       = 8,		// ���ӷ����̶�ֵ
		PROPERTYINC_STA       = 9,				// ���������̶�ֵ
		PROPERTYINC_WIS       = 10,				// ���������̶�ֵ
		PROPERTYINC_CON       = 11,				// �������ʹ̶�ֵ
		PROPERTYINC_SPR       = 12,				// ���Ӿ���̶�ֵ
		PROPERTYINC_STR       = 13,				// ���������̶�ֵ
		PROPERTYINC_MAXHPPER       = 14,		// ����HP���ްٷֱ�
		PROPERTYINC_MAXMPPER       = 15,		// ����MP���ްٷֱ�
		PROPERTYINC_MAXHPFIX       = 16,		// ����HP���޹̶�ֵ
		PROPERTYINC_MAXMPFIX       = 17,		// ����MP���޹̶�ֵ
		PROPERTYINC_PRESIST       = 18,			// �����￹�̶�ֵ
		PROPERTYINC_MRESIST       = 19,			// ���ӷ����̶�ֵ
		PROPERTYDEC_PDAMAGEPER       = 20,		// ���ⱻ����ʱ���˰ٷֱ�
		PROPERTYDEC_MDAMAGEPER       = 21,		// ���ⱻ����ʱ���˰ٷֱ�
		PROPERTYDEC_PDAMAGEFIX       = 22,		// ���ⱻ����ʱ���˹̶�ֵ
		PROPERTYDEC_MDAMAGEFIX       = 23,		// ���ⱻ����ʱ���˹̶�ֵ
		PROPERTYINC_DAMAGEFIX       = 24,		// �������ӷ����˺��̶�ֵ
		PROPERTYINC_NORMALHITRATE       = 25,	// �����չ�����ֵ
		PROPERTYINC_NORMALDUCK       = 26,		// �����չ�����ֵ
		PROPERTYINC_SKILLHITRATE       = 27,	// ���Ӽ������й̶�ֵ
		PROPERTYINC_SKILLDUCK       = 28,		// ���Ӳ�Ӱ�̶�ֵ
		PROPERTYINC_DEATHRATE       = 29,		// ��������һ���ȼ��̶�ֵ
		PROPERTYINC_DEATHVALUE       = 30,		// ��������һ���˺��ӳ�
		PROPERTYINC_EXPRATE       = 31,			// ���ӻ�þ���ʱ�ӳ�
		PROPERTYINC_SPEED       = 32,			// �����ƶ��ٶȰٷֱ�
		PROPERTYINC_HPRSPEEDFIX       = 33,		// ����HP�ָ��ٶȹ̶�ֵ
		PROPERTYINC_MPRSPEEDFIX       = 34,		// ����MP�ָ��ٶȹ̶�ֵ
		PROPERTYINC_HPRSPEEDPER       = 35,		// ����HP�ָ��ٶȰٷֱ�
		PROPERTYINC_MPRSPEEDPER       = 36,		// ����MP�ָ��ٶȰٷֱ�
		PROPERTYFUNC_HPABSORB       = 37,		// ������ȡ
		PROPERTYFUNC_MPABSORB       = 38,		// ������ȡ
		PROPERTYFUNC_PATTACKDAMAGE       = 39,	// ���������˺��ٷֱ�
		PROPERTYFUNC_MATTACKDAMAGE       = 40,	// ���ӷ����˺��ٷֱ�
		PROPERTYFUNC_REFLECT       = 41,		// 100%�����˺��ٷֱ�		
		PROPERTYFUNC_RESDEF1       = 42,		// ����1
		PROPERTYFUNC_RESDEF2       = 43,		// ����2
		PROPERTYFUNC_RESDEF3       = 44,		// ����3
		PROPERTYFUNC_RESDEF4       = 45,		// ����4
		PROPERTYFUNC_RESDEF5       = 46,		// ����5
		PROPERTYFUNC_RESDEF6       = 47,		// ����6
		PROPERTYFUNC_RESATT1       = 48,		// ���Թ���1
		PROPERTYFUNC_RESATT2       = 49,		// ���Թ���2
		PROPERTYFUNC_RESATT3       = 50,		// ���Թ���3
		PROPERTYFUNC_RESATT4       = 51,		// ���Թ���4
		PROPERTYFUNC_RESATT5       = 52,		// ���Թ���5
		PROPERTYFUNC_RESATT6       = 53,		// ���Թ���6
		PROPERTYFUNC_IGNOREDUCK       = 54,		// ��������
		PROPERTYFUNC_DEATHDEFENSE       = 55,	// ��������
		PROPERTYFUNC_OBTAINSKILL       = 56,	// ���ĳ������
		PROPERTYINC_SKILLLEVEL       = 57,		// ���Ӽ��ܵȼ���ĳ����
		PROPERTYINC_SKILLGENRELEVEL       = 58,	// ���Ӽ��ܵȼ���ĳϵ��			
		PROPERTYINC_ALL       = 59,				// ����ȫ����
		PROPERTYFUNC_REDUCECOOLFIX       = 60,	// ����ĳ������ȴʱ��̶�ֵ	
		PROPERTYFUNC_DEATHRATEFIX       = 61,	// ����ĳ�����������ȼ�
		PROPERTYFUNC_DEATHVALUEFIX       = 62,	// ����ĳ�����ܱ����˺��ٷֱ�
		PROPERTYFUNC_REDUCELEVEL       = 63,	// ����װ���ȼ�����
		PROPERTYFUNC_HITSKILL       = 64,		// ����ʱʹ�õļ���
		PROPERTYFUNC_BEHITSKILL       = 65,		// ������ʱʹ�õļ���
		PROPERTYFUNC_DEATHSKILL       = 66,		// ����ʱʹ�õļ���
		PROPERTYFUNC_HPSKILL       = 67,		// ��Ѫʱʹ�õļ���
		PROPERTYINC_WIZARD1       = 68,			// �Ż��ȼ�1
		PROPERTYINC_WIZARD2       = 69,			// �Ż��ȼ�2		
		PROPERTYINC_WIZARD3       = 70,			// �Ż��ȼ�3
		PROPERTYINC_WIZARD4       = 71,			// �Ż��ȼ�4
		PROPERTYINC_WIZARD5       = 72,			// �Ż��ȼ�5
		PROPERTYINC_WIZARD6       = 73,			// �Ż��ȼ�6
		PROPERTYFUNC_RESDEFALL    = 74,			// ȫ����
		PROPERTYFUNC_RESATTALL    = 75,			// ȫ����
	};

public:
	
	// FieldName: $������������	
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char	mPropertyName[ STRING256 ];	

	// FieldName: ���Թ�ʽ
	// FieldType: INT4
	// Type:	  COMBOENUM(PROPERTY_FUNC)
	int		mPropertyFunc;				

	// FieldName: ʹ�õ�Ŀ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1)
	int		mCanOut;					

	// FieldName: �̶�ֵ������ֵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mIntMinValue;					

	// FieldName: �̶�ֵ������ֵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mIntMaxValue;		

	// FieldName: ������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(һ��=1,����)
	int		mArea;

	// FieldName: �ٷֱ�������ֵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mFloatMinValue;				

	// FieldName: �ٷֱ�������ֵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mFloatMaxValue;				

	// FieldName: ��ؼ���ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mSkillID;

public:
	void SetFromPB( bool bServer, PBTemplateProperty* pProperty );
	void CreateTlvPB( bool bServer, PBTemplateProperty* pProperty );
	int Initialize();
	CTemplateProperty()
	{
		Initialize();
	}
	~CTemplateProperty() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= �������Ա�	## ģ������
// version	= 1				## �汾��
// path		= �������Ա�	## ·��
// parent	=				## ����ģ��
// ********************************************************************** //
class CTemplatePropertyTable : public CTemplate
{
public:
	class CPropertyPercent
	{
	public:
		int		mTempID;		// ��������ģ��ID
		int		mPercent;		// �������Եõ��ٷֱ�
	};
public:
	
	// FieldName: ��1������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��1������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��2������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��2������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��3������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��3������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��4������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��4������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��5������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��5������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��6������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��6������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��7������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��7������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��8������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��8������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��9������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��9������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��10������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��10������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��11������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��11������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��12������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��12������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��13������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��13������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��14������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��14������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��15������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��15������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��16������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��16������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��17������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��17������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��18������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��18������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��19������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��19������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��20������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��20������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��21������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��21������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��22������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��22������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��23������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��23������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��24������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��24������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��25������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��25������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��26������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��26������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��27������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��27������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��28������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��28������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��29������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��29������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��30������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��30������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��31������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��31������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��32������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��32������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��33������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��33������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��34������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��34������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��35������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��35������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��36������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��36������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��37������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��37������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��38������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��38������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��39������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��39������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��40������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��40������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��41������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��41������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��42������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��42������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��43������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��43������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��44������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��44������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��45������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��45������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��46������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��46������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��47������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��47������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��48������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��48������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��49������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��49������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��50������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��50������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��51������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��51������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��52������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��52������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��53������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��53������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��54������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��54������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��55������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��55������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��56������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��56������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��57������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��57������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��58������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��58������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��59������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��59������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��60������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��60������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��61������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��61������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��62������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��62������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��63������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��63������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��64������Ե�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��64������Եĵõ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	CPropertyPercent	mProperty[ 64 ];

public:
	void SetFromPB( bool bServer, PBTemplatePropertyTable* pTable );
	void CreateTlvPB( bool bServer, PBTemplatePropertyTable* pTable );
	int Initialize();
	CTemplatePropertyTable()
	{
		Initialize();
	}
	~CTemplatePropertyTable() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= true			## �������ɵ����ݿ���
// name		= װ����������	## ģ������
// version	= 1				## �汾��
// path		=				## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTemplateEquipment : public CTplItem
{
public:
	enum
	{
		PART_RING		= 1,				// ��ָ��װ��
		PART_CUFF,							// ������װ��
		PART_WEAPON,						// ������װ��
		PART_CHEST,							// ������װ��
		PART_LEG,							// ������װ��
		PART_HEAD,							// ��ͷ��װ��
		PART_NECK,							// ������װ��
		PART_SASH,							// ������װ��
		PART_CHARM,							// ������װ��
		PART_BALL,							// ������װ��
		PART_CLOAK,							// ������װ��
		PART_FASHION,						// ʱװ��װ��
		PART_MAGICWEAPON,					// ������װ��
		PART_WIZARD,						// �Ż���װ��
		PART_MARRY,							// �����װ��
	};

	enum
	{
		EQUIPMENT_WHITE	= 1,				// ��ɫװ��
		EQUIPMENT_BLUE,						// ��ɫװ��
		EQUIPMENT_PURPLE,					// ��ɫװ��
		EQUIPMENT_GOLD,						// ��ɫװ��
	};

	enum
	{
		EXTRA_NONE	=	0,					// �޸���
		EXTRA_FIRST	=	1,					// 1�฽��
		EXTRA_SECOND =	2,					// 2�฽��
	};

public:
	// FieldName: װ��ģ������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mEquipModal[ STRING32 ];	

	// FieldName: װ���ȼ�������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,15)
	int		mShowLevel;			

	// FieldName: װ����λ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��ָ��װ��,������װ��,������װ��,������װ��,������װ��,��ͷ��װ��,������װ��,������װ��,������װ��,������װ��,������װ��,ʱװ��װ��,����װ��,�Ż���װ��,�����װ��)
	int		mEquipType;					

	// FieldName: ��ʾ��ɫ�������Ͻ�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��ɫװ��,��ɫװ��,��ɫװ��,��ɫװ��)
	int		mShowColour;		

	// FieldName: ��������%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mStrRequire[ 6 ];			

	// FieldName: ��������%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mConRequire[ 6 ];

	// FieldName: ��������%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mStaRequire[ 6 ];				

	// FieldName: ��������%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mWisRequire[ 6 ];

	// FieldName: ��������%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mSprRequire[ 6 ];

	// FieldName: ְҵ����
	// FieldType: INT4
	// Type:	  CHECKMUTI(����=0,սʿ,����,����,��ʦ,��ʿ,����ʦ,����)
	int		mMetierRequire;

	// FieldName: �ȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mLevelRequire;				

	// FieldName: �Ա�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����,����,Ů��)
	int		mSexRequire;	

	// FieldName: ת����Ԫ��ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mYuan;

	// FieldName: װ���;ö�(-1��ʾ��Զ������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,1000)
	int    mEquipmentDurability;

	// FieldName: ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int    mBaseMendCharge;

	// FieldName: ��npc����һ�ε�������ֱ�
	// FieldType: INT4
	// Type:	 EDITNUMBER(0,10000)
	int   mNpcAbrasionRate;

	// FieldName: ��ҽ���1�ε�������ֱ�
	// FieldType: INT4
	// Type:     EDITNUMBER(0,10000)	
	int mPlayerAbrasionRate;

	// FieldName: �Ƿ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1)
	int    mCanUpgrade;

	// FieldName: �Ƿ���Կ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1)
	int    mCanDefUpgrade;

	// FieldName: �Ƿ������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1)
	int    mCanAttUpgrade;

	// FieldName: ������Ҫ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mUpgCharge;	

	// FieldName: �����Ƿ�֧�ְ󶨽�Ǯ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mNeedBindMoney;

	// FieldName: �������ӵĵ�%d������ID
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,�����﹥�̶�ֵ=5,���ӷ����̶�ֵ=6,��������̶�ֵ=7,���ӷ����̶�ֵ=8,���������̶�ֵ=9,���������̶�ֵ=10,�������ݹ̶�ֵ=11,���Ӿ���̶�ֵ=12,���������̶�ֵ=13,�������й̶�ֵ=25,�������̶ܹ�ֵ=26,���Ӻ����̶�ֵ=54)
	int		mUpgProperty[ 3 ];	

	// FieldName: ��%d������ֵ����%d�����ӵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int		mUpgValue[ 3 ][ 16 ];	

	// FieldName: ��%d�����ӵ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int		mPAttackDiff[ 16 ];

	// FieldName: ��%d�����ӵķ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int		mMAttackDiff[ 16 ];

	// FieldName: ��ʼ���Բ۸���Ϊ%d�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mSlotNumber1[ 5 ];	

	// FieldName: ���ɼ����Բ۸���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mSlotNumber2;	

	// FieldName: ����ʱһ������������Ϊ%d�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mPropertyPercent[ 5 ];		

	// FieldName: һ����%d���������Ա�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mPropertyTableID[ 3 ];

	// FieldName: ����ʱ��������������Ϊ%d�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mPropertyPercentEx[ 6 ];		

	// FieldName: ������%d���������Ա�ģ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mPropertyTableIDEx[ 5 ];

	// FieldName: ��һ�μ���������Ϊ%d�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mJudgePercent1[ 25 ];

	// FieldName: �ڶ��μ���������Ϊ%d�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mJudgePercent2[ 25 ];

	// FieldName: ����ʱ����Ϊ%d�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mResDefPercent[ 7 ];

	// FieldName: ����ʱ���Թ���Ϊ%d�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mResAttPercent[ 7 ];

	// FieldName: ��%d�����ӵ��Ŀ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int		mResDefValue[ 7 ];

	// FieldName: ��%d�����ӵ������Թ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int		mResAttValue[ 7 ];

	// FieldName: ��װID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,200)
	int    mSuitID;

	// FieldName: ��װ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,200)
	int    mSuitPos;

	// FieldName: ���۷���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mOpenCharge;

	// FieldName: �Ӳ۷���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mAddCharge;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mJudgeCharge;

	// FieldName: �ٴμ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mReJudgeCharge;

	// FieldName: ����ǿ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mDefUpgCharge;

	// FieldName: ����ת������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mDefChangeCharge;

	// FieldName: ����ǿ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mAttUpgCharge;

	// FieldName: ����ת������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mAttChangeCharge;	

	// FieldName: ��Ѫ���ӱ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mBindBonus;

	// FieldName: ���Ӻϳ��䷽
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mMultiCompose;

	// FieldName: �Ƿ����ת������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mCanChange;

	// FieldName: ����ת������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mChangeCharge;

	// FieldName: �Ƿ���Բ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mCanSplit;

	// FieldName: ��%d�ֲ�ֵ�ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int		mSplitID[ 3 ];

	// FieldName: ��%d�ֲ�ֵ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mSplitNum[ 3 ];

	// FieldName: ��ַ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mSplitCharge;

	// FieldName: ��%d�����Ե�����ֵ1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mUpgExtra1[ 3 ];

	// FieldName: ��%d�����Ե�����ֵ2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mUpgExtra2[ 3 ];

	// FieldName: ���̷���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mExtCharge;

	// FieldName: �Ƿ��ֿܵ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int		mResistTran;

	// FieldName: �Ƿ�������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int		mIsShenQi;

public:
	void SetFromPB( bool bServer, PBEquipment* pItem );
	void CreateTlvPB( bool bServer, PBEquipment* pItem );
	int Initialize();
	CTemplateEquipment() { Initialize(); }
	~CTemplateEquipment() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ʱװ			## ģ������
// version	= 1				## �汾��
// path		= װ��/ʱװ		## ·��
// parent	= װ����������	## ����ģ��
// ********************************************************************** //
class CTemplateFashion : public CTemplateEquipment
{
public:
	// FieldName: ������BuffID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mBuffID;

public:
	void SetFromPB( bool bServer, PBEquipFashion* pEquip );
	void CreateTlvPB( bool bServer, PBEquipFashion* pEquip );
	int Initialize();
	CTemplateFashion()
	{
		Initialize();
	}
	~CTemplateFashion() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ����			## ģ������
// version	= 1				## �汾��
// path		= װ��/����		## ·��
// parent	= װ����������	## ����ģ��
// ********************************************************************** //

enum ATTACK_TYPE
{
	ATTACKTYPE_NONE		= 0,		// �޹�������
	ATTACKTYPE_PHYSICS	= 1,		// ����������
	ATTACKTYPE_MAGIC	= 2,				// ������������
	ATTACKTYPE_NORMAL	= 3,				// ͨ�ù�������
};
class CTemplateWeapon : public CTemplateEquipment
{
public:
	enum WEAPON_TYPE
	{
		WEAPON_UNLIMIT	= 0,			// ������
		WEAPON_SPEAR	= 1,					// ǹ
		WEAPON_BLADE	= 2,					// ˫��
		WEAPON_BOW		= 3,						// ��
		WEAPON_SHIELD	= 4,					// ����
		WEAPON_STAFF	= 5,					// ����
		WEAPON_TOMAHAWK	= 6,				// ��
		WEAPON_SWORD	= 7,					// ��
		WEAPON_WRIST	= 8,					// ����
	};


public:
	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(ǹ,˫��,��,����,����,��,��,����)
	WEAPON_TYPE		mWeaponType;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(������,��������)
	int		mAttackType;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)
	int		mAttackDistance;

public:
	void SetFromPB( bool bServer, PBEquipWeapon* pEquip );
	void CreateTlvPB( bool bServer, PBEquipWeapon* pEquip );
	int Initialize();
	CTemplateWeapon() { Initialize(); }
	~CTemplateWeapon() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ����			## ģ������
// version	= 1				## �汾��
// path		= װ��/����		## ·��
// parent	= װ����������	## ����ģ��
// ********************************************************************** //
class CTemplateArmor : public CTemplateEquipment
{
public:
	enum
	{
		LDEFENSE	= 1,		// �ؼ׷���
		LLIFE		= 2,					// �ؼ�����
		MDEFENSE	= 3,				// ��׷���
		MLIFE		= 4,					// �������
		SDEFENSE	= 5,				// ���ӷ���
		SLIFE		= 6,					// ��������
	};
public:
	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,�ؼ�,���,����)
	int		mShowType;

	// FieldName: ������װ��Դ
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mArmorSuit[ STRING32 ];

public:
	void SetFromPB( bool bServer, PBEquipArmor* pEquip );
	void CreateTlvPB( bool bServer, PBEquipArmor* pEquip );
	int Initialize();
	CTemplateArmor() 
	{
		Initialize();
	}
	~CTemplateArmor() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ������������	## ģ������
// version	= 1				## �汾��
// path		= ������������	## ·��
// parent	= װ����������	## ����ģ��
// ********************************************************************** //
class CTemplateMagicWeapon : public CTemplateEquipment
{
public:

	// FieldName: $������ʾƷ��
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mMWShowLevel[ STRING32 ];

	// FieldName: $������ʾ���
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mShowType[ STRING32 ];

	// FieldName: װ��������������������Դ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		mNewWeaponName[ STRING32 ];

	// FieldName: ������ʼ�ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int				mInitLevel;

	// FieldName: ������ʼ����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int				mInitMp;

	// FieldName: ������ʼ����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int				mInitHp;

	// FieldName: ������ʼ����ֵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int				mInitMaxMp;

	// FieldName: ������ʼ����ֵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int				mInitMaxHp;

	// FieldName: �������Ի���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int				mInitBase;

	// FieldName: �������Գɳ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int				mInitShape;

	// FieldName: ��������Ӱ���(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int				mInitEffect;

	// FieldName: ������ʼ����(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int				mInitSpir;

	// FieldName: ÿ�㶨�����ӷ�������ֵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int				mIncMaxMp;

	// FieldName: ÿ�㶨�����ӷ�������ֵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int				mIncMaxHp;

	// FieldName: ����ֵÿ������ֵ(������ʾ����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,10000)
	int			mMPIncValue;

	// FieldName: ����ֵÿ������ֵ(������ʾ����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,10000)
	int			mHPIncValue;

	// FieldName: ÿ10000�㷨��Ӱ�취��ֵÿ������ֵ(������ʾ����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,10000)
	int			mMPIncValuePerMagic;

	// FieldName: ÿ10000������Ӱ������ֵÿ������ֵ(������ʾ����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,10000)
	int			mHPIncValuePerMagic;

	// FieldName: ÿ10000������Ӱ�취������������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,500000000)
	int			mAttackInc;

	// FieldName: ÿ10000�㶨��Ӱ�취������������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,500000000)
	int			mRecovInc;

	// FieldName: ÿ10000�㷨��Ӱ�취���������MP����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,500000000)
	int			mMaxMPInc;

	// FieldName: ÿ10000������Ӱ�취���������HP����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,500000000)
	int			mMaxHPInc;

	// FieldName: ÿ10000������Ӱ�취��������������ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,500000000)
	int			mDeadLineInc;
	
	// FieldName: �ܷ�ʹ�ü�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int			mCanUseBook;

	// FieldName: ����ʱ���������¼��ܸ���(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mGetSkillScl;

	// FieldName: �������Ա�
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mLevelTableID;

	// FieldName: ���ܿ����Ա�
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mSkillBoxTableID;

	// FieldName: ����������ٵ�����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mDieOffHp;

	// FieldName: ���Լ����շ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mProJudgeCost;

	// FieldName: �����������BUFF��
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mUmmiBuffTableID;

	// FieldName: λ��ģ����Դ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		mDispResName[ STRING32 ];

	// FieldName: Ĭ�ϼ���1(�Զ����ǵ�0�����ܿ�)
	// FieldType: INT4
	// Type:	  SKILLPATH
	int			mDefaultSkill;

	// FieldName: Ĭ�ϼ���2(�Զ����ǵ�1�����ܿ�)
	// FieldType: INT4
	// Type:	  SKILLPATH
	int			mDefaultSkill2;

	// FieldName: ������Ӧ��Ӱ��ȼ�����
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mJudgeEffTableID;

	// FieldName: ������Ӧ�����Լ�����
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mJudgeSpirTableID;

	// FieldName: ������Ӧ�ľ����ȼ���
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mLevelQuotietyTabID;	

	// FieldName: �����ֽ��
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mDecomposeTabID;	

	// FieldName: ����Ʒ�������֣�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int			mLvByNum;

	// FieldName: ����������
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mQuickUpTabID;	

	// FieldName: ������Ʒ��
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mUpLevelTabID;	

public:
	void SetFromPB( bool bServer, PBItemMagicWeapon* pItem );
	void CreateTlvPB( bool bServer, PBItemMagicWeapon* pItem );
	int Initialize();
	CTemplateMagicWeapon()
	{
		Initialize();
	}
	~CTemplateMagicWeapon() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

class CMagicWeaponProIncValue
{
public:
	unsigned long long	mLevelExp;	
	unsigned int	mLevelPoints;
	unsigned int	mLevelProcessVal;
	unsigned int	mLevelProcessCurel;
	unsigned int	mLevelProcessCurelVal;
	unsigned int	mLevelKeen;		
	unsigned int	mLevelCalm;		
	unsigned int	mLevelMagic;	
	unsigned int	mLevelBier;		
	unsigned int	mLevelImmortal;
};

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= �������Ե�������			 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/�������Ե�������	 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTplMagicWeaponProIncTable : public CTemplate
{
public:

	// FieldName: ��%d����������һ���ľ�����ֵ
	// FieldType: INT8
	// Type:	  EDITNUMBER(0,72057594037927935)

	// FieldName: ��������%d�����ӵļ��ܵ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: ��������%d����õļ��ܿ����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: ��������%d����õļ��ܿ����ֵ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: ��������%d����õļ��ܿ����ֵ������ֵ(��Ҫ��Ӧ��õĽ���ֵ)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: ��������%d������������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,3000000000)

	// FieldName: ��������%d���Ķ�������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,3000000000)

	// FieldName: ��������%d���ķ�������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,3000000000)

	// FieldName: ��������%d������������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,3000000000)

	// FieldName: ��������%d������������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,3000000000)

	CMagicWeaponProIncValue mValues[ MAGICWEAPON_MAX_GRADE ];
public:
	void SetFromPB( bool bServer, PBTplMagicWeaponProIncTable* pItem );
	void CreateTlvPB( bool bServer, PBTplMagicWeaponProIncTable* pItem );
	int Initialize();
	CTplMagicWeaponProIncTable()
	{
		Initialize();
	}
	~CTplMagicWeaponProIncTable() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// �����ֽ��
class CSingleMWDecomposeData
{
public:
	int			mTempID; // ģ��ID
	int			mNumMin; // ��������
	int			mNumMax; // �������
	int			mProb;   // ��ü���(��ֱ�)
};

enum  MW_DECOMPOS_MONEY_TYPE
{
	MW_DECOMPOS_MONEY_TYPE_NONE = 0,  // ������
	MW_DECOMPOS_MONEY_TYPE_BINDMONEY , // ���İ�Ǯ
	MW_DECOMPOS_MONEY_TYPE_NOTBINDMONEY , // ���ķǰ�Ǯ
};

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= �����ֽ��			 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/�����ֽ��	 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CMagicWeaponDecomposeTable : public CTemplate
{
public:

	// FieldName: �ֽ����ĵĽ�Ǯ����
	// FieldType: INT4
	// Type:	  COMBOENUM(MW_DECOMPOS_MONEY_TYPE)
	int			mNeedMoneyType;	

	// FieldName: �ֽ����ĵĽ�Ǯ/Ԫ����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			mNeedMoney;	

	// FieldName: ��%d���ֽ���Ʒ��ģ��
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��%d���ֽ���Ʒ����С����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: ��%d���ֽ���Ʒ���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: ��%d���ֽ���Ʒ�Ļ�ü���(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	CSingleMWDecomposeData  mItems[5];

public:
	void SetFromPB( bool bServer, PBMagicWeaponDecomposeTable* pItem );
	void CreateTlvPB( bool bServer, PBMagicWeaponDecomposeTable* pItem );
	int Initialize();
	CMagicWeaponDecomposeTable()
	{
		Initialize();
	}
	~CMagicWeaponDecomposeTable() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= ������������Ʒ��			 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/������������Ʒ��	 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CMagicWeaponQuickUpTable : public CTemplate
{
public:

	// FieldName: ���Է�������͵ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mNeedLevel;	

	// FieldName: ������Ҫ����ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mNeedItem;	

	// FieldName: ������Ҫ����Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			mNeedItemNum;	

	// FieldName: �������ĵĽ�Ǯ����
	// FieldType: INT4
	// Type:	  COMBOENUM(MW_DECOMPOS_MONEY_TYPE)
	int			mNeedMoneyType;	

	// FieldName: �������ĵĽ�Ǯ��ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			mNeedMoney;	

	// FieldName: �����ɹ�����(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mSuccessProb;	

	// FieldName: �����ɹ����滻�ķ���ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mNewMWID;	

	// FieldName: ��Ʒ��Ҫ�ĸ�������͵ȼ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mLeastLeve;	


public:
	void SetFromPB( bool bServer, PBMagicWeaponQuickUpTable* pItem );
	void CreateTlvPB( bool bServer, PBMagicWeaponQuickUpTable* pItem );
	int Initialize();
	CMagicWeaponQuickUpTable()
	{
		Initialize();
	}
	~CMagicWeaponQuickUpTable() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


class CTplSkillStorageBase
{
public:
	int mSkillID;
	int mFirstProb;
	int mOtherProb;
};

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= �������ܿ��			 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/�������ܿ��	 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTplSkillStorage : public CTemplate
{
public:


	// FieldName: ��%d������ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��%d�����ܵ�һ�μ�������(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��%d�������Ժ��������(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	CTplSkillStorageBase		  mValues[SKILL_STORAGE_LMT];	

public:
	void SetFromPB( bool bServer, PBSkillStorage* pTable );
	void CreateTlvPB( bool bServer, PBSkillStorage* pTable );
	int Initialize();
	CTplSkillStorage() 
	{
		Initialize();
	}
	~CTplSkillStorage() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


class CSkillBoxProperty
{
public:
	int			mSkillBoxColor;
	int			mSkillBoxNeedVal;
	int			mInitState;
	int			mInitSkillID;
	int			mSkillBoxType;
	int			mSkillBoxSkill;
	int			mSkillBoxSkillStorage;
	int			mSkillBoxActMoney;
};

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= �������ܿ����Ա�			 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/�������ܿ����Ա�	 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTplMagicWeaponSkillBoxProTable : public CTemplate
{
public:
	enum MagicWeapon_COLOR
	{
		COLOR_NONE    = 0,  // ��
		COLOR_WHITE   = 1,  // ��ɫ
		COLOR_BLUE    = 2,  // ��ɫ
		COLOR_PURPLE  = 3,  // ��ɫ
		COLOR_GOLD    = 4,  // ��ɫ
	};

	enum MagicWeapon_SKILLBOX_TYPE
	{
		TYPE_STATIC    = 0,		// �̶�����
		TYPE_STORAGE   ,		// �Ӽ��ܿ���ѡ
	};

	// FieldName: ��%d�����ܿ���ɫ
	// FieldType: INT4
	// Type:	  COMBOENUM(MagicWeapon_COLOR)

	// FieldName: �����%d�����ܿ���Ҫ�Ľ���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��%d�����ܿ�ĳ�ʼ״̬
	// FieldType: INT4
	// Type:	  COMBOSINGLE(δ����=0,�Ѽ���=1)

	// FieldName: ��%d�����ܿ�ĳ�ʼ����(��������)
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��%d�����ܿ�ļ��ʽ
	// FieldType: INT4
	// Type:	  COMBOENUM(MagicWeapon_SKILLBOX_TYPE)

	// FieldName: ��%d�����ܿ��Ӧ�ļ���
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��%d�����ܿ��Ӧ�ļ��ܿ�
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��%d�����ܿ�ļ����շ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	CSkillBoxProperty	mValues[SKILL_BOX_LMT];
public:
	void SetFromPB( bool bServer, PBMagicWeaponSkillBoxProTable* pTable );
	void CreateTlvPB( bool bServer, PBMagicWeaponSkillBoxProTable* pTable );
	int Initialize();
	CTplMagicWeaponSkillBoxProTable()
	{
		Initialize();
	}
	~CTplMagicWeaponSkillBoxProTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false							 ## �������ɵ����ݿ���
// name		= �������Լ���Ӱ��ȱ�			 ## ģ������
// version	= 1								 ## �汾��
// path		= Config/�������Լ���Ӱ��ȱ�	 ## ·��
// parent	=								 ## ����ģ��
// ********************************************************************** //

enum MW_JUDGE_LEVEL
{
	MW_COMMON = 1, // ��ͨ
	MW_GOOD,// ����
	MW_POLISH,// ����
	MW_BEST,// ׿Խ
};

class CTplMWProJudgeEffTable : public CTemplate
{
public:

	// FieldName: �ٷ�֮%dӰ��ȵ�һ�μ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mProbFirst[MAX_MW_PERCENT_NUM];

	// FieldName: �ٷ�֮%dӰ��ȵڶ��μ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mProbSecond[MAX_MW_PERCENT_NUM];

	// FieldName: $�ٷ�֮%dӰ��ȵ���ʾ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mShowName[MAX_MW_PERCENT_NUM][ STRING32 ];

	// FieldName: �ٷ�֮%dӰ��ȵļ���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��ͨ=1,����,����,׿Խ)
	int		mJudgeLevel[MAX_MW_PERCENT_NUM];
	
public:
	void SetFromPB( bool bServer, PBMWProJudgeEffTable* pTable );
	void CreateTlvPB( bool bServer, PBMWProJudgeEffTable* pTable );
	int Initialize();
	CTplMWProJudgeEffTable()
	{
		Initialize();
	}
	~CTplMWProJudgeEffTable()  {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false							 ## �������ɵ����ݿ���
// name		= �������Լ������Ա�			 ## ģ������
// version	= 1								 ## �汾��
// path		= Config/�������Լ������Ա�  	 ## ·��
// parent	=								 ## ����ģ��
// ********************************************************************** //
class CTplMWProJudgeSpirTable : public CTemplate
{
public:

	// FieldName: �ٷ�֮%d���Ե�һ�μ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mProbFirst[MAX_MW_PERCENT_NUM];

	// FieldName: �ٷ�֮%d���Եڶ��μ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mProbSecond[MAX_MW_PERCENT_NUM];

	// FieldName: $�ٷ�֮%d���Ե���ʾ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mShowName[MAX_MW_PERCENT_NUM][ STRING32 ];		

	// FieldName: �ٷ�֮%dӰ��ȵļ���
	// FieldType: INT4
	// Type:	  COMBOENUM(MW_JUDGE_LEVEL)
	int		mJudgeLevel[MAX_MW_PERCENT_NUM];

public:
	void SetFromPB( bool bServer, PBMWProJudgeSpirTable* pTable );
	void CreateTlvPB( bool bServer, PBMWProJudgeSpirTable* pTable );
	int Initialize();
	CTplMWProJudgeSpirTable() 
	{
		Initialize();
	}
	~CTplMWProJudgeSpirTable(){}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false							 ## �������ɵ����ݿ���
// name		= ��������ϵ����				 ## ģ������
// version	= 1								 ## �汾��
// path		= Config/��������ϵ����		  	 ## ·��
// parent	=								 ## ����ģ��
// ********************************************************************** //
class CTplMWLevelQuotietyTab : public CTemplate
{
public:

	// FieldName: ���������ȼ�%d��Ӧ�ľ���ϵ��(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mKeenQuotiety[20];

	// FieldName: ���������ȼ�%d��Ӧ�ľ���ϵ��(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mCalmQuotiety[20];

	// FieldName: ���������ȼ�%d��Ӧ�ľ���ϵ��(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mMagicQuotiety[20];

	// FieldName: ���������ȼ�%d��Ӧ�ľ���ϵ��(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mBierQuotiety[20];

	// FieldName: ���������ȼ�%d��Ӧ�ľ���ϵ��(��ֱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mImmorQuotiety[20];

public:
	void SetFromPB( bool bServer, PBMWLevelQuotietyTab* pTable );
	void CreateTlvPB( bool bServer, PBMWLevelQuotietyTab* pTable );
	int Initialize();
	CTplMWLevelQuotietyTab() 
	{
		Initialize();
	}
	~CTplMWLevelQuotietyTab() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ְҵ����			## ģ������
// version	= 1					## �汾��
// path		= Config/ְҵ����	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
    enum METIER_GENERID
    {
		GENDERID_NONE         = 0,			    //�� 
		WARRIOR_PRED                  = 1,	  //սʿǰ��
		WARRIOR_WEAPIN                = 2,	  //սʿ����
		WARRIOR_RECOVER               = 3,	  //սʿ����
		WARRIOR_FRENZY       = 4,				//սʿ��
		SWORDMAN_PRED                 = 5,	  //����ǰ��
		SWORDMAN_PUTOUT               = 6,	  //���ʹ�ɱ
		SWORDMAN_COLDBLOODNESS        = 7,	  //������Ѫ
		SWORDMAN_RISK       = 8,				//��������
		HUNTER_PRED                   = 9,	  //����ǰ��
		HUNTER_FIRE                   = 10,	  //�������
		HUNTER_HOOK                   = 11,	  //��������
		HUNTER_MAGGIC                 = 12,	  //���˷���
		RABBI_PRED                    = 13,	  //��ʦǰ��
		RABBI_ICE                     = 14,	  //��ʦ����
		RABBI_FIRE                    = 15,	  //��ʦ����
		RABBI_WIND                    = 16,	  //��ʦŭ��
		TAOIST_PRED                   = 17,	  //��ʿǰ��
		TAOIST_RIGHT                  = 18,	  //��ʿ����
		TAOIST_WARROR                 = 19,	  //��ʿ����
		TAOIST_MITZVAH                = 20,	  //��ʿ����
		MAGIC_PRED                    = 21,	  //����ʦǰ��
		MAGIC_WRESTIE                 = 22,	  //����ʦ��
		MAGIC_LION                    = 23,	  //����ʦʨ֮�û�
		MAGIC_PANTER                  = 24,	  //����ʦ��֮�û�
		FRESH_PRED                    = 25,	  //����
		TALENT       = 26,						// �컯
		OGRE       = 27,						// ��ħ־
		FANGCUN		= 28,						// ����ɽ
    };
    enum METIER_TYPE
    {
		ANYMETIER	= 0,					//����
        WARRIOR		= 1,	                //սʿ 
        SWORDMAN	= 2,                   //����
        HUNTER		= 3,                     //����
        RABBI		= 4,                      //��ʦ
        TAOIST		= 5,                     //��ʿ
        MAGIC		= 6,                      //����ʦ
        FRESH		= 7,                      //����
    };
class CTemplateMetier : public CTemplate
{
public:

	// FieldName: $ְҵ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mMetierName[ STRING32 ];		

	// FieldName: ְҵID
	// FieldType: INT4
	// Type:	  COMBOENUM(METIER_TYPE)
	int		mMetierID;						

	// FieldName: ְҵ�ĵ�1���ϵ��ID
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,սʿǰ��,սʿ����,սʿ����,սʿ��,����ǰ��,���ʹ�ɱ,������Ѫ,��������,����ǰ��,�������,��������,���˷���,��ʦǰ��,��ʦ����,��ʦ����,��ʦŭ��,��ʿǰ��,��ʿ����,��ʿ����,��ʿ����,����ʦǰ��,����ʦ��,����ʦʨ֮�û�,����ʦ��֮�û�,����)

	// FieldName: ְҵ�ĵ�2���ϵ��ID
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,սʿǰ��,սʿ����,սʿ����,սʿ��,����ǰ��,���ʹ�ɱ,������Ѫ,��������,����ǰ��,�������,��������,���˷���,��ʦǰ��,��ʦ����,��ʦ����,��ʦŭ��,��ʿǰ��,��ʿ����,��ʿ����,��ʿ����,����ʦǰ��,����ʦ��,����ʦʨ֮�û�,����ʦ��֮�û�,����)

	// FieldName: ְҵ�ĵ�3���ϵ��ID
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,սʿǰ��,սʿ����,սʿ����,սʿ��,����ǰ��,���ʹ�ɱ,������Ѫ,��������,����ǰ��,�������,��������,���˷���,��ʦǰ��,��ʦ����,��ʦ����,��ʦŭ��,��ʿǰ��,��ʿ����,��ʿ����,��ʿ����,����ʦǰ��,����ʦ��,����ʦʨ֮�û�,����ʦ��֮�û�,����)

	// FieldName: ְҵ�ĵ�4���ϵ��ID
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,սʿǰ��,սʿ����,սʿ����,սʿ��,����ǰ��,���ʹ�ɱ,������Ѫ,��������,����ǰ��,�������,��������,���˷���,��ʦǰ��,��ʦ����,��ʦ����,��ʦŭ��,��ʿǰ��,��ʿ����,��ʿ����,��ʿ����,����ʦǰ��,����ʦ��,����ʦʨ֮�û�,����ʦ��֮�û�,����)

	// FieldName: ְҵ�ĵ�5���ϵ��ID
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,սʿǰ��,սʿ����,սʿ����,սʿ��,����ǰ��,���ʹ�ɱ,������Ѫ,��������,����ǰ��,�������,��������,���˷���,��ʦǰ��,��ʦ����,��ʦ����,��ʦŭ��,��ʿǰ��,��ʿ����,��ʿ����,��ʿ����,����ʦǰ��,����ʦ��,����ʦʨ֮�û�,����ʦ��֮�û�,����)
	int		mGenerID[ 5 ];

	// FieldName: ÿ��һ����ü��ܵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mSkillPoint;		

	// FieldName: ְҵ�����ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mWalkSpeed;		

	// FieldName: ÿ��һ��������Ե�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mPropertyPoint;	
	

	// FieldName: ְҵ�����ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mRunSpeed;		

	// FieldName: ְҵ��ʼ�ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mInitLevel;		

	// FieldName: ְҵ��ʼ���HP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mInitHP;			

	// FieldName: ְҵ��ʼ���MP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mInitMP;			


	// FieldName: ְҵ��ʼ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitPDefense;		

	// FieldName: ְҵ��ʼ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitPAttack;

	// FieldName: ְҵ��ʼ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitMAttack;		

	// FieldName: ְҵ��ʼ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitMDefense;		

	// FieldName: ְҵ��ʼ�쳣״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitAbnResist;			

	// FieldName: ְҵ��ʼŭ��״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitWindResist;		

	// FieldName: ְҵ��ʼ����״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitFireResist;		

	// FieldName: ְҵ��ʼ����״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitWaterResist;		

	// FieldName: ְҵ��ʼ����״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitLightResist;		

	// FieldName: ְҵ��ʼ����״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitEarthResist;		

	// FieldName: ְҵ��ʼ����״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitShadowResist;		

	// FieldName: ְҵ��ʼ�����ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mInitDeathRate;		

	// FieldName: ְҵ��ʼ�����˺��ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mInitDeathValue;		

	// FieldName: ְҵ��ʼ�չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mInitNormalHitrate;	

	// FieldName: ְҵ��ʼ�չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mInitNormalDuck;	

	// FieldName: ְҵ��ʼ���ܲ�Ӱ(��Ӱ)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mInitSkillDuck;		

	// FieldName: ְҵ��ʼ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mInitIgnoreDuck;

	// FieldName: ְҵ��ʼ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mInitDeathDefense;

	// FieldName: ְҵÿ��һ���������HP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mDeltaHP;					

	// FieldName: ְҵÿ��һ���������MP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mDeltaMP;					

	// FieldName: ְҵÿ��һ������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaPAttack;				

	// FieldName: ְҵÿ��һ�������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaPDefense;				

	// FieldName: ְҵÿ��һ�����ӷ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaMAttack;				

	// FieldName: ְҵÿ��һ�����ӷ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaMDefense;				

	// FieldName: ְҵÿ��һ�������쳣״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaAbnResist;		

	// FieldName: ְҵÿ��һ������ŭ��״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaWindResist;				

	// FieldName: ְҵÿ��һ�����ӳ���״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaFireResist;				

	// FieldName: ְҵÿ��һ����������״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaWaterResist;		

	// FieldName: ְҵÿ��һ�����Ӵ���״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaLightResist;				

	// FieldName: ְҵÿ��һ����������״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaEarthResist;				

	// FieldName: ְҵÿ��һ�����Ӻ���״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaShadowResist;				

	// FieldName: ְҵÿ��һ�����������ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaDeathRate;			

	// FieldName: ְҵÿ��һ�����ӱ����˺��ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaDeathValue;		

	// FieldName: ְҵÿ��һ�������չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaNormalHitrate;		

	// FieldName: ְҵÿ��һ�������չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaNormalDuck;			

	// FieldName: ְҵÿ��һ�����Ӽ�������(��Ӱ)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaSkillDuck;	

	// FieldName: ְҵÿ��һ�����Ӻ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaIgnoreDuck;

	// FieldName: ְҵÿ��һ��������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeltaDeathDefense;

	// FieldName: ÿ��������Ӧ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mPAttackPerStr;	

	// FieldName: ÿ��������Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMAttackPerStr;	

	// FieldName: ÿ��������Ӧ�����ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mDeathRatePerStr;

	// FieldName: ÿ��������Ӧ�����˺��ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mDeathValuePerStr;	

	// FieldName: ÿ��������ӦHP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMaxHPPerStr;

	// FieldName: ÿ��������ӦMP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMaxMPPerStr;

	// FieldName: ÿ��������Ӧ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mPDefensePerStr;

	// FieldName: ÿ��������Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMDefensePerStr;

	// FieldName: ÿ��������Ӧ�չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mNormalHitratePerStr;		

	// FieldName: ÿ��������Ӧ�չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mNormalDuckPerStr;	

	// FieldName: ÿ��������Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mIgnoreDuckPerStr;

	// FieldName: ÿ��������Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeathDefensePerStr;

	// FieldName: ÿ�����ʶ�Ӧ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mPAttackPerCon;	

	// FieldName: ÿ�����ʶ�Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMAttackPerCon;	

	// FieldName: ÿ�����ʶ�Ӧ�����ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mDeathRatePerCon;

	// FieldName: ÿ�����ʶ�Ӧ�����˺��ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mDeathValuePerCon;	

	// FieldName: ÿ�����ʶ�ӦHP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMaxHPPerCon;

	// FieldName: ÿ�����ʶ�ӦMP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMaxMPPerCon;

	// FieldName: ÿ�����ʶ�Ӧ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mPDefensePerCon;

	// FieldName: ÿ�����ʶ�Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMDefensePerCon;

	// FieldName: ÿ�����ʶ�Ӧ�չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mNormalHitratePerCon;		

	// FieldName: ÿ�����ʶ�Ӧ�չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mNormalDuckPerCon;	

	// FieldName: ÿ�����ʶ�Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mIgnoreDuckPerCon;

	// FieldName: ÿ�����ʶ�Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeathDefensePerCon;

	// FieldName: ÿ�����ʶ�ӦHP�ָ��ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mHPRSpeedPerCon;			

	// FieldName: ÿ��������Ӧ���HP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMaxHPPerSta;

	// FieldName: ÿ��������Ӧ������˰ٷֱ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int	mPReducePerSta;

	// FieldName: ÿ��������Ӧ�������˰ٷֱ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int	mMReducePerSta;

	// FieldName: ÿ��������Ӧ���ÿ��������Ӧ�쳣״̬����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mAbnResistPerSta;

	// FieldName: ÿ��������Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeathDefensePerSta;

	// FieldName: ÿ��������Ӧ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mPAttackPerWis;

	// FieldName: ÿ��������Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMAttackPerWis;	

	// FieldName: ÿ��������Ӧ���HP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMaxHPPerWis;

	// FieldName: ÿ��������Ӧ���MP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMaxMPPerWis;

	// FieldName: ÿ��������Ӧ�����ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mDeathRatePerWis;

	// FieldName: ÿ��������Ӧ�����˺�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mDeathValuePerWis;	

	// FieldName: ÿ��������Ӧ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mPDefensePerWis;

	// FieldName: ÿ��������Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMDefensePerWis;

	// FieldName: ÿ��������Ӧ�չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mNormalHitratePerWis;		

	// FieldName: ÿ��������Ӧ�չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mNormalDuckPerWis;	

	// FieldName: ÿ��������Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mIgnoreDuckPerWis;

	// FieldName: ÿ��������Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeathDefensePerWis;

	// FieldName: ÿ�㾫���Ӧ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mPAttackPerSpr;

	// FieldName: ÿ�㾫���Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMAttackPerSpr;	

	// FieldName: ÿ�㾫���Ӧ���HP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMaxHPPerSpr;

	// FieldName: ÿ�㾫���Ӧ���MP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMaxMPPerSpr;

	// FieldName: ÿ�㾫���Ӧ�����ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mDeathRatePerSpr;

	// FieldName: ÿ�㾫���Ӧ�����˺�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mDeathValuePerSpr;	

	// FieldName: ÿ�㾫���Ӧ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mPDefensePerSpr;

	// FieldName: ÿ�㾫���Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMDefensePerSpr;

	// FieldName: ÿ�㾫���Ӧ�չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mNormalHitratePerSpr;		

	// FieldName: ÿ�㾫���Ӧ�չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mNormalDuckPerSpr;	

	// FieldName: ÿ�㾫���Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mIgnoreDuckPerSpr;

	// FieldName: ÿ�㾫���Ӧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mDeathDefensePerSpr;

	// FieldName: ÿ�㾫���ӦMP�ָ��ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,63)
	int	mMPRSpeedPerSpr;			

	// FieldName: ��ͨ״̬HP�ָ��ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mNormalHPRSpeed;	

	// FieldName: ��ͨ����״̬HP�ָ��ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mNormalSitHPRSpeed;			

	// FieldName: ս��״̬HP�ָ��ٶ�	
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mBattleHPRSpeed;			

	// FieldName: ս��״̬����HP�ָ��ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mBattleSitHPRSpeed;			

	// FieldName: ��ͨ״̬MP�ָ��ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mNormalMPRSpeed;		

	// FieldName: ��ͨ����״̬MP�ָ��ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mNormalSitMPRSpeed;			

	// FieldName: ս��״̬MP�ָ��ٶ�	
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mBattleMPRSpeed;			

	// FieldName: ս��״̬����MP�ָ��ٶ�	
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mBattleSitMPRSpeed;	

public:
	void SetFromPB( bool bServer, PBMetier* pMetier );
	void CreateTlvPB( bool bServer, PBMetier* pMetier );
	int Initialize();
	CTemplateMetier()
	{
		Initialize();
	}
	~CTemplateMetier() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ���۱�			## ģ������
// version	= 1					## �汾��
// path		= Config/���۱�		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateSellTable : public CTemplate
{
public:
	enum EM_SELLTABLETYPE
	{
		SELLTABLETYPE_PLAYERMONEYNEEDED = 1,	// ���۱��е���Ʒ��Ҫ������ҽ�Ǯ
		SELLTABLETYPE_FAMILYMONEYNEEDED = 2,	// ���۱��е���Ʒ��Ҫ���ļ����Ǯ
		SELLTABLETYPE_CORPSMONEYNEEDED  = 3,	// ���۱��е���Ʒ��Ҫ���ľ��Ž�Ǯ
		SELLTABLETYPE_FAMILYWAR			= 4,	// ����ս���˵ĳ��۱�
		SELLTABLETYPE_CORPSWAR			= 5,	// ����ս���˵ĳ��۱�
	};
public:
	class CSellItem
	{
	public:
		char	mPage[ STRING32 ];
		int		mItemID[ 42 ];
	};

public:


	// FieldName: $��1ҳ����
	// FieldType: STRING32
	// Type:	  EDITSTRING

	// FieldName: ��1ҳ��1�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��1ҳ��2�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��1ҳ��3�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��4�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��5�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��6�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��7�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��8�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��9�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��10�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��11�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��12�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��1ҳ��13�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��14�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��15�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��16�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��17�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��18�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��19�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��20�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��21�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��22�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��1ҳ��23�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��24�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��25�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��26�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��27�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��28�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��29�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��1ҳ��30�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��31�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��32�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��1ҳ��33�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��34�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��35�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��1ҳ��36�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��37�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��38�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��39�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��1ҳ��40�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��41�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��1ҳ��42�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: $��2ҳ����
	// FieldType: STRING32
	// Type:	  EDITSTRING

	// FieldName: ��2ҳ��1�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��2ҳ��2�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��2ҳ��3�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��4�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��5�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��6�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��7�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��8�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��9�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��10�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��11�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��12�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��2ҳ��13�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��14�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��15�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��16�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��17�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��18�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��19�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��20�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��21�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��22�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��2ҳ��23�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��24�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��25�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��26�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��27�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��28�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��29�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��2ҳ��30�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��31�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��32�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��2ҳ��33�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��34�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��35�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��2ҳ��36�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��37�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��38�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��39�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��2ҳ��40�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��41�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��2ҳ��42�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: $��3ҳ����
	// FieldType: STRING32
	// Type:	  EDITSTRING

	// FieldName: ��3ҳ��1�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��3ҳ��2�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��3ҳ��3�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��4�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��5�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��6�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��7�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��8�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��9�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��10�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��11�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��12�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��3ҳ��13�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��14�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��15�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��16�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��17�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��18�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��19�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��20�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��21�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��22�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��3ҳ��23�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��24�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��25�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��26�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��27�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��28�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��29�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��3ҳ��30�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��31�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��32�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��3ҳ��33�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��34�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��35�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��3ҳ��36�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��37�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��38�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��39�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��3ҳ��40�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��41�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��3ҳ��42�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: $��4ҳ����
	// FieldType: STRING32
	// Type:	  EDITSTRING

	// FieldName: ��4ҳ��1�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��4ҳ��2�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��4ҳ��3�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��4�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��5�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��6�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��7�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��8�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��9�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��10�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��11�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��12�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��4ҳ��13�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��14�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��15�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��16�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��17�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��18�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��19�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��20�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��21�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��22�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��4ҳ��23�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��24�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��25�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��26�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��27�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��28�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��29�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��4ҳ��30�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��31�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��32�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��4ҳ��33�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��34�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��35�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��4ҳ��36�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��37�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��38�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��39�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��4ҳ��40�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��41�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��4ҳ��42�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: $��5ҳ����
	// FieldType: STRING32
	// Type:	  EDITSTRING

	// FieldName: ��5ҳ��1�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��5ҳ��2�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��5ҳ��3�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��4�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��5�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��6�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��7�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��8�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��9�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��10�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��11�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��12�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��5ҳ��13�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��14�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��15�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��16�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��17�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��18�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��19�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��20�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��21�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��22�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��5ҳ��23�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��24�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��25�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��26�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��27�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��28�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��29�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��5ҳ��30�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��31�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��32�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��5ҳ��33�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��34�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��35�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��5ҳ��36�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��37�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��38�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��39�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��5ҳ��40�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��41�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��5ҳ��42�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: $��6ҳ����
	// FieldType: STRING32
	// Type:	  EDITSTRING

	// FieldName: ��6ҳ��1�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��6ҳ��2�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��6ҳ��3�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��4�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��5�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��6�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��7�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��8�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��9�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��10�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��11�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��12�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��6ҳ��13�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��14�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��15�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��16�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��17�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��18�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��19�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��20�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��21�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��22�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��6ҳ��23�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��24�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��25�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��26�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��27�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��28�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��29�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��6ҳ��30�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��31�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��32�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��6ҳ��33�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��34�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��35�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��6ҳ��36�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��37�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��38�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��39�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��6ҳ��40�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��41�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ��6ҳ��42�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	CSellItem	mItem[ 6 ];	
	
	
	// FieldName: ���۱�����
	// FieldType: INT4
	// Type:	  COMBOENUM(EM_SELLTABLETYPE)
	int mSellTableType;	
	

	// FieldName: ��%dҳ��%d����Ʒ�Ľ𶧼�Ǯ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int	mItemGoldPrice[6][42];		 	
	
	// FieldName: ��%dҳ��%d����Ʒ������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int	mItemNum[6][42];	
	
	// FieldName: �������ռ���̵�ʱ����ռ����еĵ�ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int	mWarCityMapID; 
	
	// FieldName: ��%dҳ��%d����Ʒ��ˢ��ʱ��(Сʱ)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int	mItemRefreshDay[6][42];	
		
public:
	void SetFromPB( bool bServer, PBSellTable* pTable );
	void CreateTlvPB( bool bServer, PBSellTable* pTable );
	int Initialize();
	CTemplateSellTable()
	{
		Initialize();
	}
	~CTemplateSellTable() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ����ĸ��			## ģ������
// version	= 1					## �汾��
// path		= Config/����ĸ��	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //

class CTemplateTotalDrop : public CTemplate
{
public:

	// FieldName: �����ӱ�%d��id
	// FieldType: INT4
	// Type:	  TEMPPATH	

	int		mDropTableID[ 32 ];

	// FieldName: �����ӱ�%d�Ĵ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	int		mDropCount[ 32 ];

public:
	void SetFromPB( bool bServer, PBTotalDrop* pDrop );
	void CreateTlvPB( bool bServer, PBTotalDrop* pDrop );
	int Initialize();
	CTemplateTotalDrop()
	{
		Initialize();
	}
	~CTemplateTotalDrop() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

enum DropNoticeType
{
	NONE_NOTICE		= 0,		// ��֪ͨ
	MINEMAP_NOTICE	= 1,		// �ر�ͼ֪ͨ
	COUNTRY_NOTICE	= 2,		// ��Ӫ����֪ͨ
	WORLD_NOTICE	= 3,		// �������֪ͨ
	SPECIAL_NOTICE	= 4,		// ����㲥֪ͨ
};

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �����ӱ�			## ģ������
// version	= 1					## �汾��
// path		= Config/�����ӱ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateDrop : public CTemplate
{
public:
	class CDropItem
	{
	public:
		int		mDropItemID;
		int		mDropItemProbability;
		int		mLevelProbability;
		int		mNotify;
		int		mSpecial;
		int		mShow;

	};

public:
	
	// FieldName: ���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,31)
	int		mDropTurn;

	// FieldName: ÿ���ֵ���0����Ʒ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ÿ���ֵ���1����Ʒ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: ÿ���ֵ���2����Ʒ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: ÿ���ֵ���3����Ʒ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: ÿ���ֵ���4����Ʒ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int	mDropNumberProbability[ 5 ];	

	// FieldName: �����%d����Ʒ��id
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �����%d����Ʒ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �����%d����Ʒ�ļ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,15)

	// FieldName: �����%d����Ʒ����ʾ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,�ر�ͼ=1,��Ӫ֪ͨ=2,����֪ͨ=3,������ʾ=4)

	// FieldName: �����%d����Ʒ��������ʾ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(-100000,100000)

	// FieldName: �����%d����Ʒ�Ƿ���ʾ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��ʾ=1)

	CDropItem	mDrops[ 50 ];

public:
	void SetFromPB( bool bServer, PBDropTable* pDrop );
	void CreateTlvPB( bool bServer, PBDropTable* pDrop );
	int Initialize();
	CTemplateDrop()
	{
		Initialize();
	}
	~CTemplateDrop(){}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �ɼ�NPC			## ģ������
// version	= 1					## �汾��
// path		= �ɼ�NPC			## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateCollect : public CTemplate
{
public:
	enum ECollectType
	{
		LIFESKILL_TASK	= 0,	// ����Ĳɼ�npc
		LIFESKILL_LIFESKILL,	// ����ܵĲɼ�npc
	}; 	

	enum ELifSkillKind
	{
		SKILLKIND_NULL	= 0,	// ��		
		SKILLKIND_PLANT,	// ֲ��
		SKILLKIND_MINERAL,	// ����
	};	

	enum ECollectTaskType
	{	
		TASKTYPE_COMMON = 0,	// ��ͨ�ɼ�����
		TASKTYPE_CORPSCOLLECT = 1,		// ���Ųɼ�����
	};

	class CDegreeInfo	
	{	
		public:							
		int		mValue;			// ��ұ�����������Ҫ��������ȵĲ�ֵ
		int		mProbality;		// �ڲ�ֵ��Χ�ڻ�ȡ�����ȵĸ���
		int		mDegreeValue;	// �ڲ�ֵ��Χ�ڻ�ȡ�����ȵ�ֵ
	};
public:


	// FieldName: $NPC����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mName[ STRING32 ];			

	// FieldName: ͼ����Դ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mModelName[ STRING32 ];

	// FieldName: ��%d������
	// FieldType: INT4
	// Type:      TASKPATH
	int     mTaskID[ 10 ];

	// FieldName: ��%d��������Ҫ��Ʒ
	// FieldType: INT4
	// Type:      TEMPPATH
	int     mItemID[ 10 ];
	
	// FieldName: ��%d��������Ҫ��Ʒ������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,100) 
	int     mItemNum[ 10 ];
	
	// FieldName: ��%d��������Ҫ�Ĳ�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000) 
	int     mItemProbality[ 10 ];

	// FieldName: ��%d������������������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,100)
	int		mExtraItemNum[ 10 ];

	// FieldName: ��%d�������������ĸ���
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)
	int		mExtraItemProbality[ 10 ];

	// FieldName: ���ɼ�����
	// FieldType: INT4
	// Type:      EDITNUMBER(0,1000) 
	int     mNumber;

	// FieldName: ����ĸ��
	// FieldType: INT4
	// Type:      TEMPPATH 
	int     mDropID;	
	
	// FieldName: �ɼ���Ҫ�ļ�������
	// FieldType: INT4
	// Type:      COMBOENUM(ECollectType) 
	int		mSkillType;
	
	// FieldName: �ɼ���Ҫ�ļ������͹������
	// FieldType: INT4
	// Type:      COMBOENUM(ELifSkillKind) 
	int		mSkillKind;
	
	// FieldName: ����ܲɼ���Ҫ���ĵĻ���ֵ
	// FieldType: INT4
	// Type:      EDITNUMBER(0,1000) 
	int		mApCost; 
	
	// FieldName: �ɼ���Ҫ��������
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,1000) 
	int		mCollectDegree;
	
	// FieldName: ���������ȺͲɼ���Ҫ�������ȵĵ�%d����ֵ����
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,1000) 

	
	// FieldName: ���������ȺͲɼ���Ҫ�������ȵĵ�%d����ֵ����Ļ�ȡ�����ȵĸ���
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,10000) 

	
	// FieldName: ���������ȺͲɼ���Ҫ�������ȵĵ�%d����ֵ����Ļ�ȡ�����ȵ�ֵ
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,10000) 

	CDegreeInfo mDegreeInfo[MAX_LIFESKILL_DEGREESTEP];
	
	// FieldName: �ɼ���Ҫ�ĵȼ�
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,1000) 
	int		mCollectLevel;

	// FieldName: �ɼ�����������
	// FieldType: INT4	
	// Type:      COMBOENUM(ECollectTaskType) 
	int		mCollectTaskType;

public:
	void SetFromPB( bool bServer, PBNPCCollect* pNpc );
	void CreateTlvPB( bool bServer, PBNPCCollect* pNpc );
	int Initialize();
	CTemplateCollect()
	{
#ifndef TEMPEDIT
		mTemplateType = EM_TEMPTYPE_COLLECT; 
#endif
		Initialize();
	}
	~CTemplateCollect() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= true				## �������ɵ����ݿ���
// name		= �����NPC			## ģ������
// version	= 					## �汾��
// path		=					## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateOgre : public CTemplate
{
public:
	enum
	{
		PATROL_RAND,		// ����߶�
		PATROL_STAND,		// վ������
		PATROL_FIX,			// �̶��߶�
	};

	enum
	{
		OGRESHOW_NONE	= 1,		
		OGRESHOW_TASK,
		OGRESHOW_VIP,		
		OGRESHOW_NORMAL,
		OGRESHOW_BOSS,
	};	
	
	enum ESpecialEvent
	{
		EVENT_NONE				=	0,
		EVENT_GATE				=	1,		// ��������
		EVENT_FLAG				=	2,		// ��������
	};

public:

	// FieldName: $NPC����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mName[ STRING32 ];			

	// FieldName: ͼ����Դ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mModelName[ STRING32 ];		

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(������=1,��������)
	int		mOgreType;	
	
	// FieldName: ���䷽ʽ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����˳��=1,�˺�˳��)
	int		mDropType;	
	
	// FieldName: ����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mStrategyID;

	// FieldName: ����ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mDropID;	

	// FieldName: ����ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,160)
	int		mLevel;				

	// FieldName: ������ʾ�ȼ�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=1,�����,��Ӣ��,��ͨ��,BOSS)
	int		mDisplayLevel;
	
	// FieldName: ����Ƶ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mAttackRate;

	// FieldName: ��������ʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mAttackTime;
	
	// FieldName: �����Ѫ�ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mHPRSpeed;					

	// FieldName: ��������ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mMPRSpeed;							

	// FieldName: ���ﱼ���ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mRunSpeed;		

	// FieldName: �����ʼ�ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mInitLevel;		

	// FieldName: �����ʼ���HP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mHP;				

	// FieldName: �����ʼ���MP
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mMP;				

	// FieldName: �����ʼ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mPAttack;			

	// FieldName: �����ʼ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mPDefence;			

	// FieldName: �����ʼ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mPAttackRange;		

	// FieldName: �����ʼ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mPReducePer;

	// FieldName: �����ʼ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mMAttack;					

	// FieldName: �����ʼ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mMDefence;			

	// FieldName: �����ʼ������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMAttackRange;

	// FieldName: �����ʼ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mMReducePer;

	// FieldName: �����ʼ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mDeathRate;			

	// FieldName: �����ʼ�����˺��ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mDeathValue;	

	// FieldName: �����ʼ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mDeathDefense;

	// FieldName: �����ʼ�չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mNormalHitrate;		

	// FieldName: �����ʼ�չ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mNormalDuck;

	// FieldName: �����ʼ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mIgnoreDuck;

	// FieldName: �����ܻ��Ƿ��Ѫ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1)
	int		mRecover;	

	// FieldName: �����ʼ����%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mResDef[ 6 ];

	// FieldName: �����ʼ���Թ���%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mResAtt[ 6 ];

	// FieldName: �����Ƿ�Զ�̹���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int		mNeedDelay;			

	// FieldName: Ѳ������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����߶�=0,վ������,�̶��߶�)
	int		mPatrolType;	

	// FieldName: �Ƿ�������������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(������=0,������)
	int		mIsInitiative;		

	// FieldName: ���о���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mWalkDistance;

	// FieldName: ����ʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mTeleTime;

	// FieldName: ��޾���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mEnmityDistance;	

	// FieldName: ���ʱ��(��Ϊ��λ)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mEnmityTime;	

	// FieldName: ��վʱ��(��Ϊ��λ)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mClearTimer;			

	// FieldName: ����������õ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mExp;					

	// FieldName: ����������õ���ʼ��Ǯ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mInitMoney;					

	// FieldName: ����������õ���Ǯ����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mDeltaMoney;				 

	// FieldName: ����״̬�б�
	// FieldType: INT4
	// Type:	  CHECKMUTI(����,ѣ��,��Ĭ)
	int		mResist;					

	// FieldName: ����ת��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mTranID;

	// FieldName: PK����
	// FieldType: INT4
	// Type:	  CHECKMUTI(�Թ������,���������,�Ա�������Ѻ�,������Ҷ����Ѻ�,�Ա����������,������Ҷ�������,�Ա�����ҵж�,������Ҷ���ж�,���������Ѻ�,�����Ҷ����Ѻ�,������������,�����Ҷ�������,�������ҵж�,�����Ҷ���ж�)
	int		mPKType;

	// FieldName: ��ӪID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mGroupID;

	// FieldName: ����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mSkillID;

	// FieldName: ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mSkillLevel;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mSearchDistance;

	// FieldName: ���ʱ��(��)(��ʱ��͸ɵ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mLifeTime;

	// FieldName: ������ʾ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=-1,����1=0,����2,����3,����4,����5,����6)
	int		mResShow;

	// FieldName: �������ṩ������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mJusticeValue;

	// FieldName: NPC��ʧ����������%dʧ��
	// FieldType: INT4
	// Type:	  TASKPATH
	int		mFailTaskID[MAX_FAIL_TASKS];

	// FieldName: ����Buff�����б�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mBuffImmunity;

	// FieldName: ɱ��������һ�óƺ�ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mObtainTitle;

	// FieldName: ��ȡ����
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mAwardID;

	// FieldName: ���Ƶķ�����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mLmtLineID;
	
	// FieldName: ��Ӫ�ڵ�ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mRedstoneID;

	// FieldName: ���������¼�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,����=1,����=2)
	int			mOgreEvent;

	// FieldName: ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mCorpsValue;

	// FieldName: ��������id
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mDropsDesc;

	// FieldName: �����Ѷ�ϵ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mDiffcultIndex;

	// FieldName: �����ѶȽ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mDiffcultAward;



public:
	void SetFromPB( bool bServer, PBOgreProperty* pOgre );
	void CreateTlvPB( bool bServer, PBOgreProperty* pOgre );
	int Initialize();
	CTemplateOgre()
	{
#ifndef TEMPEDIT
		mTemplateType = EM_TEMPTYPE_OGRE; 
#endif
		Initialize();
	}
	~CTemplateOgre() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ����				## ģ������
// version	= 1					## �汾��
// path		= ����				## ·��
// parent	= �����NPC			## ����ģ��
// ********************************************************************** //
class CTemplateBox : public CTemplateOgre
{
public:
	enum STORTBOX_EVENT
	{
		EVENT_NOTHING		= 0,	// ���¼�
		EVENT_DROPITEM,				// �����¼�
		EVENT_MACHINERY,			// �����¼�
        EVENT_PICKFORYQS,           // �û���ҡǮ�����ʰȡ����
		EVENT_PICKFORCORPSBOSS,		//  �û��ھ���boss������ʰȡ����
	};

	enum BOX_TYPE
	{
		BOX_NEEDKEY			= 0,	// ������ҪԿ��
		BOX_NOTNEEDKEY,				// ���䲻��ҪԿ��
	};

	enum STORTBOX_TYPE
	{
		TYPE_NEEDKEY		= 0,	// ��ҪԿ�׵ı���
		TYPE_NEEDNOTKEY	,			// ����ҪԿ�׵ı���
	};

	struct STORTBOX_CLICK
	{
		STORTBOX_EVENT	mEvent;	
		int				mProbability;
	};
public:
	// FieldName: �����%d�¼�
	// FieldType:	INT4
	// Type:      COMBOENUM(STORTBOX_EVENT)

	// FieldName: �����%d�¼�����
	// FieldType:	INT4
	// Type:      EDITNUMBER(0,10000)
	STORTBOX_CLICK mClick[ 5 ];

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOENUM(BOX_TYPE)
	BOX_TYPE		mType;

	// FieldName: %d�������(���˼�������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int				mDropTable[ MAX_BOXLEVEL ];
	
	// FieldName: Կ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int				mKey;	

public:
	void SetFromPB( bool bServer, PBOgreBox* pBox );
	void CreateTlvPB( bool bServer, PBOgreBox* pBox );
	int Initialize();
	CTemplateBox() 
	{
#ifndef TEMPEDIT
		mTemplateType = EM_TEMPTYPE_BOX; 
#endif
		Initialize();
	}
	~CTemplateBox() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �赲NPC				## ģ������
// version	= 1					## �汾��
// path		= �赲NPC				## ·��
// parent	= �����NPC			## ����ģ��
// ********************************************************************** //

class CTemplateBlock : public CTemplateOgre
{
public:
	enum IS_SELECT
	{
		CAN_SELECT			= 0,	//���Ա�ѡ��
		NO_SELECT,					//�����Ա�ѡ��
	};

	struct Relatively_Pos
	{
		int mX;
		int mY;
	};
public:
	

	// FieldName: ���ƫ�Ƶ�%d������X
	// FieldType:	INT4
	// Type:      EDITNUMBER(-50,50)

	// FieldName: ���ƫ�Ƶ�%d������Y
	// FieldType:	INT4
	// Type:      EDITNUMBER(-50,50)
	Relatively_Pos mPos[ 30 ];

	// FieldName: �Ƿ���Ա�ѡ��
	// FieldType: INT4
	// Type:	  COMBOENUM(IS_SELECT)
	IS_SELECT		mSelect;

public:
	void SetFromPB( bool bServer, PBBlock* pBlock );
	void CreateTlvPB( bool bServer, PBBlock* pBlock );
	int Initialize();
	CTemplateBlock()
	{
#ifndef TEMPEDIT
		mTemplateType = EM_TEMPTYPE_BLOCK; 
#endif
		Initialize();
	}
	~CTemplateBlock() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ���ͳ�			## ģ������
// version	= 1					## �汾��
// path		= ����/���ͳ�		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateShowPet : public CTemplate
{
public:

	// FieldName: $��Ϸ�е���ʾ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mName[ STRING32 ];			

	// FieldName: ģ��·��
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mModel[ STRING32 ];			

	// FieldName: ͼ��·��
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mIconName[ STRING32 ];		

	// FieldName: �ʺϵ�ְҵ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(սʿ=1,����,����,��ʦ,��ʿ,����ʦ,����ְҵ)
	int		mMetierID;

	// FieldName: ����ȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,150)
	int		mMaxLevel;

	// FieldName: ����ҵĵȼ�Ҫ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,150)
	int		mRequireLevel;

	// FieldName: �����Ը߳���Ҷ��ټ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,150)
	int		mExceedLevel;

	// FieldName: �ӳ��ﵰ�����ɳ�����Ҫ��rmb����id
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mPetItemID;

	// FieldName: �ӳ��ﻹԭ�ɳ��ﵰ��Ҫ��ȡ�������
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mRevertCost;

	// FieldName: ��ʼ�ֿ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mInitStorage;

	// FieldName: ����ÿ�����ټ��ֿ������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mLevelIncStorage;
	
	// FieldName: ������Ϊ����ÿ�����ӵĲֿ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mIncStorage;

	// FieldName: ÿ���ӹ��ͳ��õľ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mExpPerMin;

	// FieldName: ��ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mRepletionLimit;

	// FieldName: ������ı�ʳ�ȴﵽʲô��ֵʱ������ս��״̬�»�Ѫ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mRepletionHP;

	// FieldName: ��������������ս��״̬�»�Ѫʱһ�λض���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mRevertHPValue;

	// FieldName: ״̬1�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMinRepletion1;

	// FieldName: ״̬1�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mMaxRepletion1;

	// FieldName: ��״̬1�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mExpSpeedRate1;

	// FieldName: ״̬2�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMinRepletion2;

	// FieldName: ״̬2�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mMaxRepletion2;

	// FieldName: ��״̬2�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mExpSpeedRate2;

	// FieldName: ״̬3�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMinRepletion3;

	// FieldName: ״̬3�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mMaxRepletion3;

	// FieldName: ��״̬3�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mExpSpeedRate3;

	// FieldName: ״̬4�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMinRepletion4;

	// FieldName: ״̬4�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mMaxRepletion4;

	// FieldName: ��״̬4�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mExpSpeedRate4;

	// FieldName: ״̬5�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMinRepletion5;

	// FieldName: ״̬5�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mMaxRepletion5;

	// FieldName: ��״̬5�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mExpSpeedRate5;

	// FieldName: �ɳԵ�ʳ�����
	// FieldType: INT4
	// Type:	  CHECKMUTI(�߲�,ˮ��,����)
	int		mFoodCombo;

public:
	void SetFromPB( bool bServer, PBShowPet* pPet );
	void CreateTlvPB( bool bServer, PBShowPet* pPet );
	int Initialize();
	CTemplateShowPet() 
	{
		Initialize();
	}
	~CTemplateShowPet() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ս����			## ģ������
// version	= 1					## �汾��
// path		= ����/ս����		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateBattlePet : public CTemplate
{
public:

	// FieldName: $��Ϸ�е���ʾ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mName[ STRING32 ];			

	// FieldName: ģ��·��
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mModel[ STRING32 ];			

	// FieldName: ͼ��·��
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mIconName[ STRING32 ];		

	// FieldName: �ʺϵ�ְҵ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(սʿ,����,����,��ʦ,��ʿ,����ʦ,����ְҵ)
	int		mMetierID;

	// FieldName: ����ȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,150)
	int		mMaxLevel;

	// FieldName: ����ҵĵȼ�Ҫ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,150)
	int		mRequireLevel;

	// FieldName: �����Ը߳���Ҷ��ټ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,150)
	int		mExceedLevel;

	// FieldName: �ӳ��ﵰ�����ɳ�����Ҫ��rmb����id
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mPetItemID;

	// FieldName: �ӳ��ﻹԭ�ɳ��ﵰ��Ҫ��ȡ�������
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mRevertCost;

	// FieldName: ��ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mRepletionLimit;

	// FieldName: ״̬1�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMinRepletion1;

	// FieldName: ״̬1�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mMaxRepletion1;

	// FieldName: ��״̬1�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mExpSpeedRate1;

	// FieldName: ��״̬1�³����hp������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mHPRate1;

	// FieldName: ��״̬1�³���Ĺ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mAttackRate1;

	// FieldName: ״̬2�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMinRepletion2;

	// FieldName: ״̬2�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mMaxRepletion2;

	// FieldName: ��״̬2�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mExpSpeedRate2;

	// FieldName: ��״̬1�³����hp������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mHPRate2;

	// FieldName: ��״̬1�³���Ĺ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mAttackRate2;

	// FieldName: ״̬3�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMinRepletion3;

	// FieldName: ״̬3�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mMaxRepletion3;

	// FieldName: ��״̬3�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mExpSpeedRate3;

	// FieldName: ��״̬1�³����hp������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mHPRate3;

	// FieldName: ��״̬1�³���Ĺ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mAttackRate3;

	// FieldName: ״̬4�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMinRepletion4;

	// FieldName: ״̬4�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mMaxRepletion4;

	// FieldName: ��״̬4�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mExpSpeedRate4;

	// FieldName: ��״̬1�³����hp������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mHPRate4;

	// FieldName: ��״̬1�³���Ĺ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mAttackRate4;

	// FieldName: ״̬5�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMinRepletion5;

	// FieldName: ״̬5�ı�ʳ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)	
	int		mMaxRepletion5;

	// FieldName: ��״̬5�³����þ�����ٶ��Ǳ�׼�ٶȵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mExpSpeedRate5;

	// FieldName: ��״̬1�³����hp������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mHPRate5;

	// FieldName: ��״̬1�³���Ĺ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int	mAttackRate5;

	// FieldName: ����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mHPValue;

	// FieldName: ����ֵǱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mHPPotential;

	// FieldName: ����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMPValue;

	// FieldName: ����ֵǱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMPPotential;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mPAttack;

	// FieldName: ��������Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mPAttackPotential;

	// FieldName: ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMAttack;

	// FieldName: ����������Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMAttackPotential;

	// FieldName: �������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mPDefence;

	// FieldName: �������Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mPDefencePotential;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMDefence;

	// FieldName: ��������Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMDefencePotential;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mPResist;

	// FieldName: ��������Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mPResistPotential;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMResist;

	// FieldName: ��������Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMResistPotential;

	// FieldName: �쳣״̬��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mAbnResist;

	// FieldName: �쳣״̬��������Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mAbnResistPotential;

	// FieldName: ����ϵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mFireResist;

	// FieldName: ����ϵ����Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mFireResistPotential;

	// FieldName: ŭ��ϵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mWindResist;

	// FieldName: ŭ��ϵ����Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mWindResistPotential;

	// FieldName: ����ϵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mLightResist;

	// FieldName: ����ϵ����Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mLightResistPotential;

	// FieldName: ����ϵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mShadowResist;

	// FieldName: ����ϵ����Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mShadowResistPotential;

	// FieldName: ����ϵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mWaterResist;

	// FieldName: ����ϵ����Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mWaterResistPotential;

	// FieldName: ����ϵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mEarthResist;

	// FieldName: ����ϵ����Ǳ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mEarthResistPotential;

	// FieldName: �ɳԵ�ʳ�����
	// FieldType: INT4
	// Type:	  CHECKMUTI(�߲�,ˮ��,����)
	int		mFoodCombo;

public:
	void SetFromPB( bool bServer, PBBattlePet* pPet );
	void CreateTlvPB( bool bServer, PBBattlePet* pPet );
	int Initialize();
	CTemplateBattlePet()
	{
		Initialize();
	}
	~CTemplateBattlePet() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �䷽				## ģ������
// version	= 1					## �汾��
// path		= �䷽				## ·��
// parent	= ���߻�����Ϣ		## ����ģ��
// ********************************************************************** //
class CTemplateBlueprint : public CTplItem
{
protected:
	class CStuff
	{
	public:
		int		mStuffID;		// ����ID
		int		mNumber;
	};

	class CProduct
	{
	public:
		int		mProductID;		// ����ID
		int	mPercent;		// ��������
	};

public:

	// FieldName: ��Ҫ�ļ���ID
	// FieldType: INT4
	// Type:	  SKILLPATH
	int			mNeedSkillID;

	// FieldName: ��Ҫ�ļ��ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)
	int			mNeedSkillLevel;

	// FieldName: һ�������ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)
	int			mProduceCount;

	// FieldName: һ��������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,5000)
	int			mProduceCost;

	// FieldName: ÿ��������õĻ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,5000)
	int			mObtainExp;

	// FieldName: ��Ҫ�ĵ�1��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�1��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�2��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�2��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�3��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�3��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�4��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�4��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�5��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�5��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�6��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�6��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�7��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�7��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�8��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�8��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�9��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�9��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�10��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�10��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�11��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�11��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�12��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�12��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�13��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�13��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�14��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�14��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�15��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�15��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ��Ҫ�ĵ�16��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ҫ�ĵ�16��ԭ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	CStuff		mStuff[ 16 ];

	// FieldName: �õ��ĵ�1���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�1���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�2���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�2���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�3���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�3���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�4���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�4���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�5���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�5���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�6���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�6���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�7���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�7���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�8���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�8���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�9���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�9���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�10���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�10���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�11���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�11���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�12���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�12���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�13���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�13���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�14���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�14���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�15���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�15���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �õ��ĵ�16���ƷID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �õ��ĵ�16���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	CProduct	mProduct[ 16 ];

public:
	void SetFromPB( bool bServer, PBItemBluePrint* pItem );
	void CreateTlvPB( bool bServer, PBItemBluePrint* pItem );
	int Initialize();
	CTemplateBlueprint()
	{
		Initialize();
	}
	~CTemplateBlueprint() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��������			## ģ������
// version	= 1					## �汾��
// path		= ��������			## ·��
// parent	= �����NPC			## ����ģ��
// ********************************************************************** //
enum EFamilyService
{
	FAMILYSERVICE_NONE = 0,			// �޼������
	FAMILYSERVICE_FAMILYNPC = 1,		// ����NPC
	FAMILYSERVICE_AREANPC	= 2,			// ���NPC
	FAMILYSERVICE_CONTRIBUTENPC = 3,	// ����NPC
	FAMILYSERVICE_TASKNPC		= 4,			// ����NPC
	FAMILYSERVICE_ACTIVITYNPC = 5,		// ����NPC
	FAMILYSERVICE_WARNPC	 = 6,			// ����ս��NPC
	FAMILYSERVICE_HOMENPC     = 7,			// ��԰NPC	
};
enum ELifeSkillService
{
	LIFESKILLSERVICE_NONE		= 0,		// ������ܷ���
	LIFESKILLSERVICE_COLLECT	= 1,		// �ɼ����ܷ���	
	LIFESKILLSERVICE_GOLDMAKE	= 2,		// ����ܷ���
	LIFESKILLSERVICE_ARTIFICER	= 3,		// �ɽ����ܷ���
	LIFESKILLSERVICE_PILLMAKER	= 4,		// �������ܷ���
	LIFESKILLSERVICE_KOOKER		= 5,		// ��⿼��ܷ���
};
class CTemplateNpc : public CTemplateOgre
{
public:
	enum EFuncType
	{
		FUNCNPC_SERVICE		= 1,
		FUNCNPC_GUARDER,
		FUNCNPC_TASK,
	};

	enum EWDayType
	{
		WDAY_MONDAY			= 0x0001,		// ��һ
		WDAY_TUESDAY		= 0x0002,		// �ܶ�
		WDAY_WEDENSDAY		= 0x0004,		// ����
		WDAY_THURSDAY		= 0x0008,		// ����
		WDAY_FRIDAY			= 0x0010,		// ����
		WDAY_SATURDAY		= 0x0020,		// ����
		WDAY_SUNDAY			= 0x0040,		// ����
	};
	
	enum EMarriageType
	{
		MARRIAGETYPE_NOSERVICE		=	0,		// û�л������		
		MARRIAGETYPE_MARRIAGE		=	1,		// ����npc
		MARRIAGETYPE_WEDDINGHALL	=	2,		// ���ý�����
		MARRIAGETYPE_BAITANG		=	3,		// ����npc		
		MARRIAGETYPE_EXCHANGE		=	4,		// ���һ�
	};

	enum ESwornType
	{
		SWORNTYPE_NOSERVICE			=	0,		// û�н�ݷ���
		SWORNTYPE_SWORN				=	1,		// ��ݷ���
		SWORNTYPE_EXCHANGE			=	2,		// ��ݶһ�
	};

	enum EFamilyHomeType
	{
		FAMILYHOME_NONE				=	0,		// �޼�԰����
		FAMILYHOME_MAIN				=	1,		// ��������
		FAMILYHOME_WUFANG			=	2,		// �����䷻
		FAMILYHOME_GONGFANG			=	3,		// ���幤��
		FAMILYHOME_SHUFANG			=	4,		// �����鷻
		FAMILYHOME_ITEM				=	5,		// ����װ��
	};

	enum EWarOpType
	{
		WAR_OP_NONE					=	0,		// ������
		WAR_OP_CHARACTER			=	1,		// ռ��ݵ�
		WAR_OP_STONE				=	2,		// ����ʯ
		WAR_OP_DAQI					=	3,		// ����
		WAR_OP_FLAG					=	4,		// ռ����
	};

	enum EWarServiceType
	{
		WAR_SERVICE_NONE		=	0,		// ��
		WAR_SERVICE_MAIN	=	0x01,		// ��Ҫ
		WAR_SERVICE_CAMP	=	0x02,		// Ӫ��
		WAR_SERVICE_AWARD	=	0x04,		// ����
		WAR_SERVICE_TELE	=	0x08,		// ����
		WAR_SERVICE_BUFF	=	0x10,		// ��buff
	};

	enum ETaxServiceType
	{
		TAX_SERVICE_NONE		=	0,		// ��
		TAX_SERVICE_INTRO		=	0x01,	// ����
		TAX_SERVICE_MODIFY		=	0x02,	// ����
		TAX_SERVICE_GET			=	0x04,	// ���
	};

	enum ELastOneType
	{
		LO_SERVICE_NONE			= 0,		//��
		LO_SERVICE_INTRO		= 0x01,		//����
	};
public:

	// FieldName: NPC����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����NPC=1,����,����NPC)
	int			mFuncType;	
	
	// FieldName: $������
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char		mTalk[ STRING256 ];

	// FieldName: ��վID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mStageID;	

	// FieldName: ̸������ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mTalkServiceID;

	// FieldName: ���۷���ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mSellServiceID;

	// FieldName: �ʼ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mMailService;

	// FieldName: �ֿ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mStorageService;
	
	// FieldName: ��������
	// FieldType: INT4
	// Type:	  CHECKMUTI(��=0,����,����,����)
	int			mUpgService;
	
	// FieldName: װ���󶨷���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mEqtBindService;		
	
	// FieldName: ÿ�ո�������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mWelfareService;		

	// FieldName: $�ƺ�
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		mDesc[ STRING32 ];

	// FieldName: ѧϰ����ְҵID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,6)
	int			mStudySkillMetierID;	

	// FieldName: �سǵ�X
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mTownX;

	// FieldName: �سǵ�Y
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mTownY;

	// FieldName: �ʰ�����NPC
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mStorageTaskNPC;

	// FieldName: NPC�ҵĻʰ�����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,200)
	int			mStorageTaskID;

	// FieldName: �ʰ�����ȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mDownLevel;

	// FieldName: �ʰ�����ȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mUpLevel;	

	// FieldName: ϴ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mResetPService;	

	// FieldName: ��ȡ˫��ʱ���б�ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mDiploidTime;
	
	// FieldName: �������
	// FieldType: INT4
	// Type:	   COMBOENUM(EFamilyService) 
	int			mFamilyService;	

	// FieldName: ���ŷ���
	// FieldType: INT4
	// Type:	   COMBOENUM(EFamilyService)
	int			mCorpService;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  CHECKMUTI(��=0,�״�,�ٴ�)
	int			mJudgeService;

	// FieldName: ת������
	// FieldType: INT4
	// Type:	  CHECKMUTI(��=0,����,����)
	int			mChangeService;	

	// FieldName: �����
	// FieldType: INT4
	// Type:	   COMBOSINGLE(��=0,��)
	int			mActivityService;	

	// FieldName: �һ�����
	// FieldType: INT4
	// Type:	  CHECKMUTI(��=0,��ͨ,��װ)
	int			mExchangeService;

	// FieldName: ��ѫ����
	// FieldType: INT4
	// Type:	  CHECKMUTI(��=0,����,�Ż�,��Ʒ)
	int			mHonorService;

	// FieldName: ս������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mBattle;

	// FieldName: ����ܷ���
	// FieldType: INT4
	// Type:	   COMBOENUM(ELifeSkillService) 
	int			mLifeSkillService;	
	// FieldName: ��������
	// FieldType: INT4
	// Type:	  CHECKMUTI(��һ,�ܶ�,����,����,����,����,����)
	int			mBidDay;

	// FieldName: ����ʱ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,23)
	int			mBidHour;

	// FieldName: ���۷�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,59)
	int			mBidMinute;

	// FieldName: ����ս��������
	// FieldType: INT4
	// Type:    COMBOSINGLE(��=0,��=1)
	int			mCorpsBattle;

	// FieldName: �������ۼӼ����ֵ
	// FieldType: INT4
	// Type:	EDITNUMBER(0,100000000)
	int			mMinBidPrice;

	// FieldName: ����ս�ǳ�ID
	// FieldType: INT4
	// Type:	EDITNUMBER(0,100000000)
	int			mBattleCity;

	// FieldName: �������Լ�������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mMWProJudgeService;

	// FieldName: �������ܼ�������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mMWSkillJudgeService;
	
	// FieldName: װ���һ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mEquipExchangeService;
	
	// FieldName: װ���һ���ID
	// FieldType: INT4
	// Type:	EDITNUMBER(0,100000000)
	int			mExChangeTableID;	

	// FieldName: ����ս��������
	// FieldType: INT4
	// Type:	  CHECKMUTI(��һ,�ܶ�,����,����,����,����,����)
	int			mCorpsBidDay;

	// FieldName: ����ս����ʱ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,23)
	int			mCorpsBidHour;

	// FieldName: ����ս���۷�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,59)
	int			mCorpsBidMinute;

	// FieldName: ����ϴ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mMWClearPointService;

	// FieldName: �������μ���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mMWSecondJudgeService;

	// FieldName: �������˷���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mUnionService;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mCountryService;

	// FieldName: �⽻����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mFriendService;

	// FieldName: NPC����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����=0,�ڼ�=1,����=2,����=3,Ů��=4)
	int			mCountryType;
	
	// FieldName: ��Ԫ����ȡ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mGoldenYBService;

	// FieldName: �����������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mChairManTaskService;

	// FieldName: ��������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,399)
	int			mChairManTaskID;
	
	// FieldName: ������
	// FieldType: INT4
	// Type:	 COMBOENUM(EMarriageType)
	int			mMarriageService;

	// FieldName: ��Ե����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mMatrixService;

	// FieldName: ����NPC������
	// FieldType: INT4
	// Type:	   COMBOENUM(EFamilyHomeType) 
	int			mFamilyType;	

	// FieldName: ��ȡ����ʯBuff
	// FieldType: INT4
	// Type:	EDITNUMBER(0,100000000)
	int			mStoneBuff;

	// FieldName: ��ȡ���Ƿ���ʧ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mDisappear;

	// FieldName: ˢ���Է���
	// FieldType: INT4
	// Type:	   COMBOSINGLE(��=0,��)
	int			mRefreshService;

	// FieldName: ��ѯ�Ĵ��͵�����
	// FieldType: INT4
	// Type:	EDITNUMBER(0,100000000)
	int			mPedalIndex;

	// FieldName: �Ƿ���ժ�ǹ���
	// FieldType: INT4
	// Type:	COMBOSINGLE(��=0,��)
	int			mDirectService;

	// FieldName: �Ƿ���ӡ������
	// FieldType: INT4
	// Type:	COMBOSINGLE(��=0,��)
	int			mExtraService;

	// FieldName: �Ƿ��й�ս����
	// FieldType: INT4
	// Type:	  CHECKMUTI(��=0,��Ҫ,Ӫ��,����,����,��buff)
	int			mWarService;

	// FieldName: ��ս����
	// FieldType: INT4
	// Type:	  COMBOENUM(EWarOpType)
	int			mWarOpType;

	// FieldName: ��ս����ֵ
	// FieldType: INT4
	// Type:	EDITNUMBER(0,100000000)
	int			mWarValue;

	// FieldName: ��ʼ��������Ӫ
	// FieldType: INT4
	// Type:	EDITNUMBER(0,100000000)
	int			mWarCamp;
	
	// FieldName: �Ƿ�������װ������
	// FieldType: INT4
	// Type:	COMBOSINGLE(��=0,��)
	int			mEquipLevelService;

	// FieldName: ��սս��ֵ
	// FieldType: INT4
	// Type:	EDITNUMBER(0,100000000)
	int			mWarHonor;

	// FieldName: ѧϰ����ɽ���ܷ���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mFangCunService;

	// FieldName: �Ƿ��ֿܵ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int		mResistTran;

	// FieldName: ��������
	// FieldType: INT4
	// Type:    EDITNUMBER(0,100000000)
	int		mFBFunc;

	// FieldName: �������ܲ���1
	// FieldType: INT4
	// Type:    EDITNUMBER(0,100000000)
	int		mFBFuncParame1;

	// FieldName: �������ܲ���2
	// FieldType: INT4
	// Type:    EDITNUMBER(0,100000000)
	int		mFBFuncParame2;

	// FieldName: ����������ʾ�ַ���
	// FieldType: STRING128
	// Type:    EDITSTRING
	char	mFBFuncStr[ 128 ];

	// FieldName: �Ƿ�����˰����
	// FieldType: INT4
	// Type:	  CHECKMUTI(��=0,����,����,���)
	int			mTaxService;

	// FieldName: ת��Ӫ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mChangeCampService;

	// FieldName: ������������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mWeakProtectService;

    // FieldName: ҡǮ�����а�
    // FieldType: INT4
    // Type:      COMBOSINGLE(��=0,��)
    int         mYaoQianShuRankService;

    // FieldName: �Ͻɷ���
    // FieldType: INT4
    // Type:      COMBOSINGLE(��=0,��)
    int         mHandInService;

	// FieldName: �����¼�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,����=1,����=2)
	int			mSpecialEvent;

    // FieldName: ҡǮ��˵��
    // FieldType: INT4
    // Type:      EDITNUMBER(0,100000000)
    int         mYaoQianShuServiceInfo;
	
	// FieldName: �۱��������
	// FieldType: INT4
	// Type:      COMBOSINGLE(��=0,��)
	int         mTreasureBowlService;

	// FieldName: �����ֽ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mMWDecomposeService;

	// FieldName: ��������ӡ�Ƿ���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mMWImprintService;

	// FieldName: ������������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mMWUpdateService;

	// FieldName: ������Ʒ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mMWUpdateExService;

	// FieldName: ����ս���ۿ�ʼ����
	// FieldType: INT4
	// Type:	  CHECKMUTI(��һ,�ܶ�,����,����,����,����,����)
	int			mCorpsBidStartDay;

	// FieldName: ����ս���ۿ�ʼʱ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,23)
	int			mCorpsBidStartHour;

	// FieldName: ����ս���ۿ�ʼ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,59)
	int			mCorpsBidStartMinute;
	
	// FieldName: ����ɱ˵��
	// FieldType: INT4
	// Type:	  CHECKMUTI(��=0,����)
	int			mLastOneService;  

	// FieldName: ����ս���ۿ�ʼʱ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,23)
	int			mFamilyBidStartHour;

	// FieldName: ����ս���ۿ�ʼ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,59)
	int			mFamilyBidStartMinute;

	// FieldName: ��������ϳɷ���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mMWQLComposeService;
	
	// FieldName: ���������⴫�ͷ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)
	int			mRandomTeleService;

	// FieldName: ��ͼ˵��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mIntroduceMapID;

	// FieldName: ʦͽ˵��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mShiTuService;
	
	// FieldName: ��ݷ���
	// FieldType: INT4
	// Type:	 COMBOENUM(ESwornType)
	int			mSwornService;

	// FieldName: ���ս˵��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mGlobalWarService;

	// FieldName: �Ƿ��������һ�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			mSuperEquipExchange;

public:
	void SetFromPB( bool bServer, PBNpc* pNpc );
	void CreateTlvPB( bool bServer, PBNpc* pNpc );
	int Initialize();
	CTemplateNpc()
	{
#ifndef TEMPEDIT
		mTemplateType = EM_TEMPTYPE_NPC; 
#endif
		Initialize();
	}
	~CTemplateNpc() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��				## ģ������
// version	= 1					## �汾��
// path		= NPC/��			## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateMine : public CTemplate
{
public:
	class CMineOutput
	{
	public:
		int		mStuffID;
		int	mPrecent;
	};

	class CMineOgre
	{
	public:
		int		mNpcID;		
		int		mNumber;
		int		mPrecent;
	};

public:

	// FieldName: $��Ϸ�е���ʾ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		mName[ STRING32 ];

	// FieldName: �ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int			mLevel;

	// FieldName: �ȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int			mLevelRequire;

	// FieldName: ����Ҫ�Ĺ�������
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mToolID;

	// FieldName: ���Ĳɾ��þ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mDecRate;

	// FieldName: �ɿ�ʱ�����ޣ��룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int			mMineTimeLow;

	// FieldName: �ɿ�ʱ�����ޣ��룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int			mMineTimeHigh;

	// FieldName: ģ��·������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		mModel[ STRING32 ];
	
	// FieldName: �����ĵ�1��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �����ĵ�1��ԭ�ϸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: �����ĵ�2��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �����ĵ�2��ԭ�ϸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �����ĵ�3��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �����ĵ�3��ԭ�ϸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �����ĵ�4��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �����ĵ�4��ԭ�ϸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �����ĵ�5��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �����ĵ�5��ԭ�ϸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: �����ĵ�6��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �����ĵ�6��ԭ�ϸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �����ĵ�7��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �����ĵ�7��ԭ�ϸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: �����ĵ�8��ԭ��ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: �����ĵ�8��ԭ�ϸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	CMineOutput mOutput[ 8 ];

	// FieldName: ���ֵĵ�1�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���ֵĵ�1���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ���ֵĵ�1��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ���ֵĵ�2�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���ֵĵ�2���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ���ֵĵ�2��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ���ֵĵ�3�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���ֵĵ�3���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ���ֵĵ�3��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ���ֵĵ�4�����ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���ֵĵ�4���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ���ֵĵ�4��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	CMineOgre	mOgre[ 4 ];

public:
	void SetFromPB( bool bServer, PBMine* pMine );
	void CreateTlvPB( bool bServer, PBMine* pMine );
	int Initialize();
	CTemplateMine()
	{
		Initialize();
	}
	~CTemplateMine() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// CSkillTreeNode
// ********************************************************************** //

class CSkillTreeNode
{
public:
	int		mSkillID;				// ����ID
	int		mMaxLevel;				// ���ȼ�( ����ܵ�Ͷ���� )
	int		mNeedSkillID;			// ��Ҫ��ǰ������
	int		mNeedSkillPoint;		// ��Ҫ��ǰ������Ͷ����
	int		mNeedGenerID;			// ��ҪͶ���ϵ��ID
	int		mNeedGenerPoint;		// ��ҪͶ���ϵ��Ͷ����
	int		mLevel;					// ��Ҫ����ҵȼ�
	int		mNeedBook;				// �Ƿ���Ҫ��Ӧ�ļ�����

public:
	void SetFromPB( bool bServer, PBSkillTreeNode* pNode );
	void CreateTlvPB( bool bServer, PBSkillTreeNode* pNode );
};

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ������			## ģ������
// version	= 1					## �汾��
// path		= ����/������		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateSkillTree  : public CTemplate
{
public:
	enum
	{
		GENER_WARRIOR_NOVICE       = 1,
		GENER_WARRIOR_WEAPON       = 2,
		GENER_WARRIOR_RAGE       = 3,
		GENER_WARRIOR_DEFENCE       = 4,
		GENER_ROGUE_NOVICE       = 5,
		GENER_ROGUE_STING       = 6,
		GENER_ROGUE_COLD       = 7,
		GENER_ROGUE_BRAVO       = 8,
		GENER_HUNTER_NOVICE       = 9,
		GENER_HUNTER_SHOT       = 10,
		GENER_HUNTER_TRAP       = 11,
		GENER_HUNTER_MAGIC       = 12,
		GENER_SORCERER_NOVICE       = 13,
		GENER_SORCERER_WATER       = 14,
		GENER_SORCERER_FIRE       = 15,
		GENER_SORCERER_WIND       = 16,
		GENER_PRIEST_NOVICE       = 17,
		GENER_PRIEST_HOLY       = 18,
		GENER_PRIEST_SHADOW       = 19,
		GENER_PRIEST_MITZVAH       = 20,
		GENER_DRUID_NOVICE       = 21,
		GENER_DRUID_WRESTLE       = 22,
		GENER_DRUID_LION       = 23,
		GENER_DRUID_LEOPARD       = 24,
		GENER_NOVICE       = 25,
		GENER_TALENT	= 100,
	};

public:

	// FieldName: $ϵ������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char			mGenerName[ 32 ];		

	// FieldName: ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 
	int				mGenerID;		

	// FieldName: ��1�е�1�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��1�е�1�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�1����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��1�е�1����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�1����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��1�е�1����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�1����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�1���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��2�е�1�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��2�е�1�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�1����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��2�е�1����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�1����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��2�е�1����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�1����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�1���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��3�е�1�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��3�е�1�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�1����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��3�е�1����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�1����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��3�е�1����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�1����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�1���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��4�е�1�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��4�е�1�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�1����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��4�е�1����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�1����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��4�е�1����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�1����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�1���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��5�е�1�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��5�е�1�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�1����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��5�е�1����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�1����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��5�е�1����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�1����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�1���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��6�е�1�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��6�е�1�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�1����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��6�е�1����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�1����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 


	// FieldName: ��6�е�1����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�1����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�1���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��7�е�1�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��7�е�1�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�1����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��7�е�1����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�1����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��7�е�1����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�1����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�1���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��8�е�1�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��8�е�1�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�1����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��8�е�1����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�1����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��8�е�1����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�1����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�1���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��9�е�1�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��9�е�1�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�1����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��9�е�1����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�1����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��9�е�1����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�1����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�1���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)
	
	// FieldName: ��10�е�1�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��10�е�1�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�1����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��10�е�1����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�1����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��10�е�1����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�1����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�1���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��1�е�2�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��1�е�2�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�2����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��1�е�2����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�2����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��1�е�2����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�2����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�2���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��2�е�2�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��2�е�2�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�2����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��2�е�2����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�2����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��2�е�2����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�2����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�2���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��3�е�2�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��3�е�2�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�2����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��3�е�2����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�2����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��3�е�2����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�2����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�2���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��4�е�2�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��4�е�2�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�2����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��4�е�2����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�2����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��4�е�2����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�2����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�2���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��5�е�2�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��5�е�2�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�2����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��5�е�2����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�2����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��5�е�2����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�2����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�2���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��6�е�2�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��6�е�2�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�2����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��6�е�2����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�2����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��6�е�2����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�2����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�2���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��7�е�2�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��7�е�2�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�2����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��7�е�2����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�2����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��7�е�2����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�2����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�2���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��8�е�2�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��8�е�2�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�2����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��8�е�2����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�2����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��8�е�2����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�2����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�2���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��9�е�2�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��9�е�2�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�2����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��9�е�2����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�2����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��9�е�2����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�2����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�2���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)
	
	// FieldName: ��10�е�2�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��10�е�2�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�2����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��10�е�2����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�2����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��10�е�2����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�2����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�2���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��1�е�3�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��1�е�3�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�3����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��1�е�3����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�3����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��1�е�3����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�3����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�3���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��2�е�3�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��2�е�3�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�3����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��2�е�3����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�3����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��2�е�3����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�3����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�3���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��3�е�3�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��3�е�3�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�3����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��3�е�3����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�3����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��3�е�3����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�3����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�3���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��4�е�3�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��4�е�3�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�3����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��4�е�3����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�3����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��4�е�3����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�3����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�3���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��5�е�3�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��5�е�3�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�3����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��5�е�3����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�3����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��5�е�3����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�3����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�3���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��6�е�3�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��6�е�3�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�3����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��6�е�3����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�3����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��6�е�3����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�3����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�3���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��7�е�3�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��7�е�3�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�3����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��7�е�3����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�3����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��7�е�3����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�3����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�3���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��8�е�3�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��8�е�3�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�3����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��8�е�3����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�3����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��8�е�3����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�3����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�3���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��9�е�3�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��9�е�3�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�3����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��9�е�3����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�3����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��9�е�3����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�3����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�3���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)
	
	// FieldName: ��10�е�3�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��10�е�3�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�3����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��10�е�3����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�3����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��10�е�3����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�3����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�3���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��1�е�4�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��1�е�4�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�4����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��1�е�4����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�4����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��1�е�4����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�4����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��1�е�4���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��2�е�4�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��2�е�4�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�4����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��2�е�4����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�4����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 
	
	// FieldName: ��2�е�4����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�4����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��2�е�4���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��3�е�4�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��3�е�4�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�4����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��3�е�4����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�4����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��3�е�4����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�4����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��3�е�4���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��4�е�4�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��4�е�4�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�4����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��4�е�4����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�4����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��4�е�4����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�4����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��4�е�4���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��5�е�4�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��5�е�4�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�4����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��5�е�4����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�4����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��5�е�4����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�4����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��5�е�4���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��6�е�4�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��6�е�4�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�4����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��6�е�4����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�4����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��6�е�4����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�4����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��6�е�4���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��7�е�4�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��7�е�4�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�4����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��7�е�4����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�4����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 
	
	// FieldName: ��7�е�4����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�4����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��7�е�4���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��8�е�4�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��8�е�4�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�4����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��8�е�4����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�4����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��8�е�4����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�4����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��8�е�4���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)

	// FieldName: ��9�е�4�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��9�е�4�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�4����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��9�е�4����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�4����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��9�е�4����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�4����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��9�е�4���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)
	
	// FieldName: ��10�е�4�м���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��10�е�4�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�4����Ҫ��ǰ������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��10�е�4����Ҫ��ǰ������Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�4����ҪͶ���ϵ��ID
	// FieldType: INT4
	// Type:      COMBOENUM(METIER_GENERID) 

	// FieldName: ��10�е�4����ҪͶ���ϵ��Ͷ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�4����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��10�е�4���Ƿ���Ҫ��Ӧ�ļ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����Ҫ������=0,��Ҫ������)
	CSkillTreeNode	mLayerNode[ 4 ][ 10 ];	

public:
	void SetFromPB( bool bServer, PBSkillTree* pSkillTree );
	void CreateTlvPB( bool bServer, PBSkillTree* pSkillTree );
	int Initialize();
	CTemplateSkillTree() 
	{
		Initialize();
	}
	~CTemplateSkillTree() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= true			## �������ɵ����ݿ���
// name		= ���ܻ�����Ϣ	## ģ������
// version	= 1				## �汾��
// path		=				## ·��
// parent	=				## ����ģ��
// ********************************************************************** //
class CTemplateSkill : public CTemplate
{
public:
	enum FIRE_TYPE
	{
		FIRETYPE_NORMAL		= 1,	// ��ͨʩ����̬
		FIRETYPE_LION,				// ʨ��ʩ����̬
		FIRETYPE_LEOPARD,			// ����ʩ����̬
		FIRETYPE_ANY,				// ����ʩ����̬
	};

	enum FIRE_TIME_TYPE
	{
		TIMETYPE_NORMAL		= 1,	// ��ͨ����Ҫ����
		TIMETYPE_INSTANT,			// ˲��������Ҫ����
	};

	enum PASSINC_TYPE
	{
		PASSINC_NONE				= 0,	// ��Ч��
		PASSINC_MAXHPFIX			= 1,	// ����HP���޹̶�ֵ
		PASSINC_MAXMPFIX			= 2,	// ����MP���޹̶�ֵ
		PASSINC_MAXHPPER			= 3,	// ����HP���ްٷֱ�
		PASSINC_MAXMPPER			= 4,	// ����MP���ްٷֱ�
		PASSINC_HPRSPEEDFIX			= 5,	// ����HP�ָ��ٶȹ̶�ֵ
		PASSINC_MPRSPEEDFIX			= 6,	// ����MP�ָ��ٶȹ̶�ֵ
		PASSINC_HPRSPEEDPER			= 7,	// ����HP�ָ��ٶȰٷֱ�
		PASSINC_MPRSPEEDPER			= 8,	// ����MP�ָ��ٶȰٷֱ�
		PASSINC_STR					= 9,	// ��������
		PASSINC_STA					= 10,	// ��������
		PASSINC_SPR					= 11,	// ���Ӿ���
		PASSINC_CON					= 12,	// ��������
		PASSINC_WIS					= 13,	// �����ǻ�
		PASSINC_SPEED				= 14,	// �����ƶ��ٶ�
		PASSINC_PDEFENCEFIX			= 15,	// ������������̶�ֵ
		PASSINC_MDEFENCEFIX			= 16,	// ���ӷ��������̶�ֵ
		PASSINC_PDEFENCEPER			= 17,	// ������������ٷֱ�
		PASSINC_MDEFENCEPER			= 18,	// ���ӷ��������ٷֱ�
		PASSINC_NORMALHITRATE		= 19,	// ������ͨ�������й̶�ֵ
		PASSINC_NORMALDUCK			= 20,	// ������ͨ�������̶ܹ�ֵ
		PASSINC_SKILLDUCK			= 21,	// ���Ӽ������̶ܹ�ֵ
		PASSINC_DEATHRATE			= 22,	// ��������һ���ȼ�
		PASSINC_DEATHVALUE			= 23,	// ��������һ���˺��ӳ�
		PASSINC_DAMAGEFIX			= 24,	// �����˺��̶�ֵ
		PASSINC_NEEDMPFIX			= 25,	// ���ټ�������MP�̶�ֵ
		PASSINC_RELIVE				= 26,	// ��������
		PASSINC_DAMAGELESSFIX		= 27,	// �����˺�����̶�ֵ
		PASSINC_DAMAGELESSPER		= 28,	// �����˺�����ٷֱ�
		PASSINC_PATTACKFIX			= 29,	// �����������̶�ֵ
		PASSINC_MATTACKFIX			= 30,	// ���ӷ��������̶�ֵ
		PASSINC_NEEDMPPER			= 31,	// ���ټ�������MP�ٷֱ�

		PASSINC_IGNOREDUCK			= 32,	// ���Ӻ������̶ܹ�ֵ
		PASSINC_DEATHDEFENSE		= 33,	// ��������һ������
		PASSINC_ALL					= 34,	// ����ȫ����
		PASSINC_REDUCECOOLFIX		= 35,	// ʹĳ��������ȴʱ����ٹ̶�ֵ
		PASSINC_DEATHRATEFIX		= 36,	// ����ĳ�����������ȼ�
		PASSINC_DEATHVALUEFIX		= 37,	// ����ĳ�����ܱ����˺��ٷֱ�
		PASSINC_HITSKILL			= 38,	// ����ʱʹ�ü���
		PASSINC_BEHITSKILL			= 39,	// ������ʱʹ�ü���
		PASSINC_DEATHSKILL			= 40,	// ����ʱʹ�ü���
		PASSINC_HPSKILL				= 41,	// ��Ѫʱʹ�ü���
		PASSINC_KEENPOINTS			= 42,	// ���ӷ��������� 
		PASSINC_CALMPOINTS			= 43,	// ���ӷ����Ķ��� 
		PASSINC_MAGICPOINTS			= 44,	// ���ӷ����ķ��� 
		PASSINC_BIERPOINTS			= 45,	// ���ӷ��������� 
		PASSINC_IMMORTALPOINTS		= 46,	// ���ӷ��������� 
		PASSINC_MWHPMAX				= 47,   // ���ӷ���������ֵ����
		PASSINC_MWMPMAX				= 48,   // ���ӷ����ķ���ֵ����
		PASSINC_DUCKRATE			= 49,	// ����������
		PASSINC_RESDEF				= 50,   // ���ӿ���
		PASSINC_RESATT				= 51,   // ��������
	};
	
	enum COST_TYPE
	{
		COST_NONE		= 0,					// ������
		COST_HP			= 1,					// ����HP
		COST_MP			= 2,					// ����MP
		COST_ITEM		= 3,					// ���ĵ���
		COST_AP			= 4,					// ����AP
	};

	enum SKILL_TYPE
	{
		SKILLTYPE_ATTACK       = 1,				// �����༼��
		SKILLTYPE_BLESS       = 2,				// ף���༼��
		SKILLTYPE_CUSS       = 3,				// �����༼��
		SKILLTYPE_PETBLESS       = 4,			// ����ף���༼��
		SKILLTYPE_SELFBLESS       = 5,			// ����ף���༼��
		SKILLTYPE_TEAMBLESS       = 6,			// С��ף���༼��
		SKILLTYPE_PASSIVITY       = 7,			// �����༼��
		SKILLTYPE_RELIVE       = 8,				// �����༼��
		SKILLTYPE_TELEPORT       = 9,			// �����༼��
		SKILLTYPE_TRIP       = 10,				// �����༼��
		SKILLTYPE_SUMMON       = 11,			// �ٻ��༼��	
		SKILLTYPE_AUREOLE       = 12,			// �⻷�༼��
		SKILLTYPE_NORMALATTACK       = 13,		// ��ͨ�����༼��
		SKILLTYPE_PETTELEPORT       = 14,		// �ٻ��޴����༼��
		SKILLTYPE_SELFRANDTELEPORT       = 15,	// �����������
		SKILLTYPE_RANDTELEPORT       = 16,		// ʹ�����������
		SKILLTYPE_CONTINUEDATTACK       = 17,	// ���������༼��
		SKILLTYPE_CONTINUEDBLESS       = 18,	// ����ף���༼��
		SKILLTYPE_CONTINUEDCUSS       = 19,		// ���������༼��
		SKILLTYPE_TRANSFORM			  = 20,		// ������
		SKILLTYPE_1PFRIENDINBLESS	= 21,		// һ����Χ���ѷ�ף��(������BUFF��)
		SKILLTYPE_SUMMONNPC			= 22,		// �ٻ��̶���NPC
	};

	enum SKILL_USECONDITION
	{
		SKILL_USECONDITION_NONE		= 0,	// ������
		SKILL_USECONDITION_HPPER	= 1,			// HP�����ڶ��ٰٷֱ�
		SKILL_USECONDITION_MPPER	= 2,			// MP�����ڶ��ٰٷֱ�
		SKILL_USECONDITION_ITEM		= 3,			// �����б�����ĳ����Ʒ
	};

	enum SKILLLIST_SHOWTYPE
	{
		SKILLlIST_SHOWTYPE_SINGLE		= 0,	// ���幥��
		SKILLLIST_SHOWTYPE_UNSINGLE		= 1,			// Ⱥ�幥��
		SKILLLIST_SHOWTYPE_ASSISTANT	= 2,			// ������
		SKILLLIST_SHOWTYPE_PASSIVITY	= 3,			// ������
		SKILLLIST_SHOWTYPE_NOTSHOW		= 4,			// ����ʾ
	};

	enum SKILL_TEMPLATE_TYPE
	{
		SKILL_TEMPLATE_TYPE_AUREOLE		= 0,	// �⻷����
		SKILL_TEMPLATE_TYPE_NORMAL		= 1,				// ��ͨ����
		SKILL_TEMPLATE_TYPE_TRIP		= 2,				// ���弼��
		SKILL_TEMPLATE_TYPE_SUMMONBEAST	= 3,		// �ٻ��޼���
	};

	class CCost
	{
	public:
		int		mCostType;
		int		mCostParam[ 2 ];
	};

	class CUseCondition
	{
	public:
		SKILL_USECONDITION mConditionType;
		int mParam;								// SKILL_USECONDITION_HPPER		HP��ֱ�
												// SKILL_USECONDITION_MPPER		MP��ֱ�
												// SKILL_USECONDITION_ITEM		ITEMģ��ID
	};
public:

	// FieldName: $��������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mName[ STRING32 ];	

	// FieldName: ����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,65535)
	int		mSkillID;				

	// FieldName: ������Ҫ���������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(������=0,ǹ,˫��,��,����,��,��)
	CTemplateWeapon::WEAPON_TYPE		mRequireWeapon;			

	// FieldName: ��������ְҵ
	// FieldType: INT4
	// Type:	  COMBOENUM(METIER_TYPE)
	int		mMetierID;			

	// FieldName: ��������ְҵϵ��
	// FieldType: INT4
	// Type:	  COMBOENUM(METIER_GENERID) 
	int		mGenerID;		

	// FieldName: ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50000000)
	unsigned int mSkillLevel;		
	
	// FieldName: ����ͼ��
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mSkillIcon[ STRING32 ];	

	// FieldName: $����˵��
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char	mSkillDesc[ STRING256 ];		

	// FieldName: ʩ����̬
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��ͨ,����,ʨ��,����)
	FIRE_TYPE		mFireType;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOENUM(SKILL_TYPE)
	SKILL_TYPE		mSkillType;

	// FieldName: ʱ������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��ͨ,˲��)
	FIRE_TIME_TYPE		mTimeType;

	// FieldName: ʩ��ʱ�伴����ʱ��(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mAniTime;

	// FieldName: ����ʱ��(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mFireTime;

	// FieldName: ��ȴʱ��(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mCDTime;
	
	// FieldName: ��һ����������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(������=0,����,����,����,����)

	// FieldName: ��һ��������ֵ1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��һ��������ֵ2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: �ڶ�����������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(������=0,����,����,����,����)

	// FieldName: �ڶ���������ֵ1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: �ڶ���������ֵ2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��������������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(������=0,����,����,����,����)

	// FieldName: ������������ֵ1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ������������ֵ2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��������������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(������=0,����,����,����,����)

	// FieldName: ������������ֵ1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ������������ֵ2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	CCost	mCost[ 4 ];

	// FieldName: ��Ӧ��1���Ч��ID
	// FieldType: INT4
	// Type:	   COMBOENUM(PASSINC_TYPE)
	PASSINC_TYPE  mSkillFuncID1;

	// FieldName: �����Ƿ���Ҫ�ӳټ����˺�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int		mNeedDelay;

	// FieldName: ��1��Ч��ID��Ӧ��ֵ1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��1��Ч��ID��Ӧ��ֵ2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��1��Ч��ID��Ӧ��ֵ3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��1��Ч��ID��Ӧ��ֵ4
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��1��Ч��ID��Ӧ��ֵ5
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	unsigned int  mParameter1[ 5 ];

	// FieldName: ��Ӧ��2���Ч��ID
	// FieldType: INT4
	// Type:	  COMBOENUM(PASSINC_TYPE)
	PASSINC_TYPE  mSkillFuncID2;
	
	// FieldName: ��2��Ч��ID��Ӧ��ֵ1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��2��Ч��ID��Ӧ��ֵ2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��2��Ч��ID��Ӧ��ֵ3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��2��Ч��ID��Ӧ��ֵ4
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��2��Ч��ID��Ӧ��ֵ5
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	unsigned int  mParameter2[ 5 ];

	// FieldName: ��Ӧ��3���Ч��ID
	// FieldType: INT4
	// Type:	  COMBOENUM(PASSINC_TYPE)
	PASSINC_TYPE  mSkillFuncID3;

	// FieldName: ��3��Ч��ID��Ӧ��ֵ1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��3��Ч��ID��Ӧ��ֵ2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��3��Ч��ID��Ӧ��ֵ3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��3��Ч��ID��Ӧ��ֵ4
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��3��Ч��ID��Ӧ��ֵ5
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	unsigned int  mParameter3[ 5 ];

	// FieldName: ��Ӧ��4���Ч��ID
	// FieldType: INT4
	// Type:	  COMBOENUM(PASSINC_TYPE)
	PASSINC_TYPE  mSkillFuncID4;

	// FieldName: ��4��Ч��ID��Ӧ��ֵ1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��4��Ч��ID��Ӧ��ֵ2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��4��Ч��ID��Ӧ��ֵ3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��4��Ч��ID��Ӧ��ֵ4
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ��4��Ч��ID��Ӧ��ֵ5
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	unsigned int  mParameter4[ 5 ];
	
	// FieldName: �Ƿ��Զ��ظ�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(�����ظ�=0,�����ظ�)
	int		mAutoRepeat;	

	// FieldName: ���ܶ���
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mSkillAction[ STRING32 ];

	// FieldName: �Ƿ���ȴ���м���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	unsigned int  mAutoCoolingSkill;

	// FieldName: ����ʹ��������������1
	// FieldType: INT4
	// Type:	  COMBOSINGLE(������=0,HP�ٷֱȲ�����,MP�ٷֱȲ�����,������Я����Ʒ)

	// FieldName: ��������1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)

	// FieldName: ����ʹ��������������2
	// FieldType: INT4
	// Type:	  COMBOSINGLE(������=0,HP�ٷֱȲ�����,MP�ٷֱȲ�����,������Я����Ʒ)

	// FieldName: ��������2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)

	// FieldName: ����ʹ��������������3
	// FieldType: INT4
	// Type:	  COMBOSINGLE(������=0,HP�ٷֱȲ�����,MP�ٷֱȲ�����,������Я����Ʒ)

	// FieldName: ��������3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	CUseCondition	mUseCondition[ 3 ];

	// FieldName: ѧϰ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int				mStudyGold;

	// FieldName: �Ƿ��Զ���ͨ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(�����չ�=0,�����չ�)
	int		mAutoNormalAttack;
	
	// FieldName: ѧϰ�����������Ƿ�֧�ְ󶨽�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int				mBindStudyGold;

	// FieldName: �����б���ʾ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(���幥��=0,Ⱥ�幥��,������,������,����ʾ)
	SKILLLIST_SHOWTYPE mSkillListShowType;
	
	// FieldName: ����ģ������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(�⻷����=0,��ͨ����,���弼��,�ٻ��޼���)
	SKILL_TEMPLATE_TYPE mSkillTemplateType;

	// FieldName: ѧϰ������������ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,160)
	int					mStudySkillLevel;

	// FieldName: �Ƿ�����Զ��ظ�����״̬
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int					mInsertAutoState;

	// FieldName: �Ƿ����Զ��ظ�����״̬
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int					mBreakAutoState;

	// FieldName: �Ƿ���Ҫ����Ŀ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��,����)
	int					mNeedTarget;

	// FieldName: �Ƿ���Ҫ�ٻ���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int					mNeedPet;

	// FieldName: ��ʩ����Ӫ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(�ѷ�=0,�з�)
	int					mActionCamp;

	// FieldName: �˺�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(������=1,��������=2,ͨ�ù���=3)
	int			  mDamageType;

	// FieldName: ���ܹ������̶�ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mAttackFix;			

	// FieldName: ���ܹ������ٷֱ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int	mAttackPer;	

	// FieldName: ���Թ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mResType;

	// FieldName: ���Թ�����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mResValue;

	// FieldName: $������������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mSkillTypeDesc[ STRING32 ];

	// FieldName: �Ƿ񷨱�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			 mIsMagicWeaponSkill;

	// FieldName: �����Ƿ�ƫ��λ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			 mIsMWOffset;

	// FieldName: ��ȴ���%d��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mCDGroup[ 25 ];

	// FieldName: �Ƿ񲻿��Ա�ϴ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int  mCanClean;

	// FieldName: ʩ��Ŀ��ȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int			mTargetLevel;

	// FieldName: �ٻ���NPC����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int			mSummonIndex;

public:
	void SetFromPB( bool bServer, PBSkill* pSkill );
	void CreateTlvPB( bool bServer, PBSkill* pSkill );
	int Initialize();
	CTemplateSkill()
	{
		Initialize();
	}
	~CTemplateSkill() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //



// ********************************************************************** //
// BEGINMAKE
// virtual  = false       
// name     = �⻷���� 
// version  = 1             
// path     = ����/�⻷����
// parent   = ���ܻ�����Ϣ
// ********************************************************************** //
class CTemplateAureoleSkill : public CTemplateSkill
{
public:
	enum AUREOLE_BOOL
	{
		emTRUE	=	0, //��
		emFLASE = 1,			//��
	};

	enum AUREOLE_AREA
	{
		AUREOLE_NONE	= 0,	//��
		AUREOLE_SELF	= 1,			//�Լ�
		AUREOLE_TEAM	= 2,			//С��
		AUREOLE_FOE		= 3,			//�ж�
		AUREOLE_CORPS	= 4,			//����
		AUREOLE_ALL		= 5,			//ȫ��
	};

	struct AUREOLE_TYPE
	{
		AUREOLE_AREA	mAureoleArea;
		int				mBuffID;	
	};

public:
    // FieldName: �Ƿ��������
    // FieldType: INT4
    // Type:      COMBOENUM(AUREOLE_BOOL) 
	AUREOLE_BOOL  mIncessary;

    // FieldName: ��������ʱ����
    // FieldType: INT4
    // Type:      EDITNUMBER(1000,100000)
	int			  mIncessaryTime;

    // FieldName: �������ĵ�%d������ 
    // FieldType: INT4
    // Type:      COMBOENUM(COST_TYPE) 

    // FieldName: �������ĵ�%d����ֵ1
    // FieldType: INT4
    // Type:      EDITNUMBER(0,100000) 

    // FieldName: �������ĵ�%d����ֵ2
    // FieldType: INT4
    // Type:      EDITNUMBER(0,100000)
    CCost   mCost[ 3 ];

	// FieldName: Ӱ�췶Χ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			  mAureoleDistance;
	
	// FieldName: �⻷���ܵ�%d�������
	// FieldType: INT4
	// Type:	  COMBOENUM(AUREOLE_AREA)

	// FieldName: �⻷���ܵ�%d��ܶ�ӦBuffID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	AUREOLE_TYPE  mAureoleType[ 3 ];

public:
	void SetFromPB( bool bServer, PBAureoleSkill* pAureoleSkill );
	void CreateTlvPB( bool bServer, PBAureoleSkill* pAureoleSkill );
	int Initialize();
	CTemplateAureoleSkill()
	{
		Initialize();
	}
	~CTemplateAureoleSkill() {}

};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ��ͨ����		## ģ������
// version	= 1				## �汾��
// path		= ����/��ͨ����	## ·��
// parent	= ���ܻ�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTemplateNormalSkill : public CTemplateSkill
{
public:
	enum RANGE_TYPE
	{
		RANGE_SINGLE	= 1,// �Ե���ʹ��
		RANGE_FRONTRECT	= 2,	// ���Լ���ǰ�ľ���ʹ��
		RANGE_FRONTANGLE = 3,	// ���Լ���ǰ������ʹ��
		RANGE_SELFCIRCLE = 4,	// �����Լ�Ϊ���ĵ�Բ��ʹ��
		RANGE_TARGETCIRCLE = 5,	// ����ѡ��Ŀ��Ϊ���ĵ�Բ��ʹ��
		RANGE_BOUND		= 6,		// ��������
		RANGE_PLAYER	=7,		//ֻ�ܶ����ʹ��
	};

public:
	// FieldName: ����׼ȷ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mSkillHitrate;				

	// FieldName: ��ʼ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mMinDistance;	

	// FieldName: ׷������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mMaxDistance;		

	// FieldName: �����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mEffectMaxNumber;

	// FieldName: ������Χ����
	// FieldType: INT4
	// Type:	  COMBOENUM(RANGE_TYPE) 
	RANGE_TYPE	mAttackRange;	

	// FieldName: ��Χ������1����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	
	
    // FieldName: ��Χ������2���� 
    // FieldType: INT4
    // Type:      EDITNUMBER(0,100000)
	int		mRandParame[ 2 ];	

	// FieldName: ��ӦĿ���1��Buff��
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��ӦĿ���2��Buff��
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��ӦĿ���3��Buff��
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��ӦĿ���4��Buff��
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ӧ����Buff��
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��ӦС��Buff��
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mBuffGroupID[ 6 ];	

	// FieldName: ���ܴ������
	// FieldType: INT4
	// Type:	  CHECKMUTI(�������=0,�ƶ����,���ĵ�ı���)
	int		mContinuedRule;
	
	// FieldName: �����������ʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,60000000)
	int		mContinuedInterval;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)
	int		mContinuedNum;

	// FieldName: ���Ի���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)
	int		mIgnoreArmor;
	
public:
	void SetFromPB( bool bServer, PBNormalSkill* pNormalSkill );
	void CreateTlvPB( bool bServer, PBNormalSkill* pNormalSkill );
	int Initialize();
	CTemplateNormalSkill()
	{
		Initialize();
	}
	~CTemplateNormalSkill() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ���弼��		## ģ������
// version	= 1				## �汾��
// path		= ����/���弼��	## ·��
// parent	= ���ܻ�����Ϣ	## ����ģ��
// ********************************************************************** //
class CTemplateTrapSkill : public CTemplateSkill
{
public:
	enum APPLY_TYPE
	{
		APPLYTYPE_SINGLE	 = 1,	// ��������
		APPLYTYPE_RANGE,			// ��Χ����
	};

public:
	// FieldName: ����ʱ�䣨��λ���룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int				mLastTime;
 
	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��������,��Χ����)
	APPLY_TYPE		mApplyType;

	// FieldName: ������Χ���뾶��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mTouchRange;

	// FieldName: ���÷�Χ���뾶��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mApplyRange;
	
	// FieldName: ������Դ
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mTrapRes[ 32 ];

	// FieldName: ��Ӧ��1��Buff��
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ӧ��2��Buff��
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ӧ��3��Buff��
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��Ӧ��4��Buff��
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mBuffGroupID[ 4 ];	

	// FieldName: ��Ӧ��1�������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��Ӧ��2�������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��Ӧ��3�������
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��Ӧ��4�������
	// FieldType: INT4
	// Type:	  SKILLPATH
	int		mCondition[ 4 ];

	// FieldName: �����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mEffectMaxNumber;
public:
	void SetFromPB( bool bServer, PBTrapSkill* pTrapSkill );
	void CreateTlvPB( bool bServer, PBTrapSkill* pTrapSkill );
	int Initialize();
	CTemplateTrapSkill()
	{
		Initialize();
	}
	~CTemplateTrapSkill() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

class CTemplateSummonSkill : public CTemplateSkill
{
};

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= Buff				## ģ������
// version	= 1					## �汾��
// path		= ����/Buff			## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateBuff : public CTemplate
{
public:
	enum BUFF_TYPE
	{
		BUFF_INC		= 1,		// ����BUFF
		BUFF_DEC		= 2,					// ����BUFF
	};

	enum
	{
		RESIST_WIND		= 1,		// ŭ��ϵ
		RESIST_FIRE		= 2,				// ����ϵ
		RESIST_WATER	= 3,				// ����ϵ
		RESIST_LIGHT	= 4,				// ����ϵ
		RESIST_EARTH	= 5,				// ����ϵ
		RESIST_SHADOW	= 6,				// ����ϵ
		RESIST_BASE		= 7,				// ����
	};

	enum BUFF_FUN_TYPE
	{
		BUFFINC_NONE				= 0,	// �޹���
		BUFFINC_PATTACKPER			= 1,	// �����������ٷֱ�
		BUFFINC_MATTACKPER			= 2,	// ���ӷ��������ٷֱ�
		BUFFINC_PATTACKFIX			= 3,	// �����������̶�ֵ
		BUFFINC_MATTACKFIX			= 4,	// ���ӷ��������̶�ֵ
		BUFFINC_PDEFENCEPER			= 5,	// ������������ٷֱ�
		BUFFINC_MDEFENCEPER			= 6,	// ���ӷ��������ٷֱ�
		BUFFINC_PDEFENCEFIX			= 7,	// ������������̶�ֵ
		BUFFINC_MDEFENCEFIX			= 8,	// ���ӷ��������̶�ֵ
		BUFFINC_MAXHPFIX			= 9,	// ����HP���޹̶�ֵ
		BUFFINC_MAXMPFIX			= 10,	// ����MP���޹̶�ֵ
		BUFFINC_MAXHPPER			= 11,	// ����HP���ްٷֱ�
		BUFFINC_MAXMPPER			= 12,	// ����MP���ްٷֱ�
		BUFFINC_INCSPEEDPER			= 13,	// �����ƶ��ٶȹ̶�ֵ
		BUFFINC_STRFIX				= 14,	// ���������̶�ֵ
		BUFFINC_CONFIX				= 15,	// �������ʹ̶�ֵ
		BUFFINC_STAFIX				= 16,	// ���������̶�ֵ
		BUFFINC_SPRFIX				= 17,	// ���Ӿ���̶�ֵ
		BUFFINC_WISFIX				= 18,	// ���������̶�ֵ
		BUFFINC_NORMALHITRATEFIX	= 19,	// �����չ����й̶�ֵ
		BUFFINC_SKILLHITRATEFIX		= 20,	// ���Ӽ������й̶�ֵ
		BUFFINC_DEATHHITFIX			= 21,	// ���������ȼ��̶�ֵ
		BUFFINC_DEATHRATEFIX		= 22,	// ���������˺��ӳɹ̶�ֵ
		BUFFINC_NORMALDUCKFIX		= 23,	// �����չ�����̶�ֵ
		BUFFINC_SKILLDUCKFIX		= 24,	// ���Ӽ�������̶�ֵ
		BUFFINC_INCSRCDAMAGEFIX		= 25,	// ���ӹ���ʱ����˺��̶�ֵ
		BUFFINC_INCSRCDAMAGEPER		= 26,	// ���ӹ���ʱ����˺��ٷֱ�
		BUFFINC_DECSRCDAMAGEFIX		= 27,	// ���͹���ʱ����˺��̶�ֵ
		BUFFINC_DECSRCDAMAGEPER		= 28,	// ���͹���ʱ����˺��ٷֱ�
		BUFFINC_INCDESPDAMAGEFIX	= 29,	// ���ӱ�����ʱ���������˺��̶�ֵ
		BUFFINC_INCDESPDAMAGEPER	= 30,	// ���ӱ�����ʱ���������˺��ٷֱ�
		BUFFINC_DECDESPDAMAGEFIX	= 31,	// ���ͱ�����ʱ���������˺��̶�ֵ
		BUFFINC_DECDESPDAMAGEPER	= 32,	// ���ͱ�����ʱ���������˺��ٷֱ�
		BUFFINC_INCDESMDAMAGEFIX	= 33,	// ���ӱ�����ʱ���ܷ����˺��̶�ֵ
		BUFFINC_INCDESMDAMAGEPER	= 34,	// ���ӱ�����ʱ���ܷ����˺��ٷֱ�
		BUFFINC_DECDESMDAMAGEFIX	= 35,	// ���ͱ�����ʱ���ܷ����˺��̶�ֵ
		BUFFINC_DECDESMDAMAGEPER	= 36,	// ���ͱ�����ʱ���ܷ����˺��ٷֱ�
		BUFFINC_DECMAXHPFIX			= 37,	// ����HP���޹̶�ֵ
		BUFFINC_DECMAXHPPER			= 38,	// ����HP���ްٷֱ�
		BUFFINC_HPRSPEEDFIX			= 39,	// ����HP�ָ��ٶȹ̶�ֵ
		BUFFINC_MPRSPEEDFIX			= 40,	// ����MP�ָ��ٶȹ̶�ֵ
		BUFFINC_HPRSPEEDPER			= 41,	// ����HP�ָ��ٶȰٷֱ�
		BUFFINC_MPRSPEEDPER			= 42,	// ����MP�ָ��ٶȰٷֱ�
		BUFFINC_DECSPEEDPER			= 43,	// �����ٶȰٷֱ�
		BUFFINC_DECPATTACKFIX		= 44,	// �����������̶�ֵ
		BUFFINC_DECMATTACKFIX		= 45,	// ���ͷ��������̶�ֵ
		BUFFINC_DECPDEFENCEFIX		= 46,	// ������������̶�ֵ
		BUFFINC_DECMDEFENCEFIX		= 47,	// ���ͷ��������̶�ֵ
		BUFFINC_DECPATTACKPER		= 48,	// �����������ٷֱ�
		BUFFINC_DECMATTACKPER		= 49,	// ���ͷ��������ٷֱ�
		BUFFINC_DECPDEFENCEPER		= 50,	// ������������ٷֱ�
		BUFFINC_DECMDEFENCEPER		= 51,	// ���ͷ��������ٷֱ�
		BUFFFUNC_PGENERATTACKFIX	= 52,	// ����ָ��ϵ�𹥻��̶�ֵ
		BUFFFUNC_NEXTDEATHHITFIX	= 53,	// �����´ι��������ȼ��̶�ֵ
		BUFFFUNC_NEXTDEATHRATEFIX	= 54,	// �����´ι��������˺��ӳɹ̶�ֵ
		BUFFFUNC_PERSISTINCFIXHP	= 55,	// ������Ѫ
		BUFFFUNC_PERSISTINCFIXMP	= 56,	// ��������
		BUFFFUNC_PERSISTDECFIXHP	= 57,	// �����˺�
		BUFFFUNC_PERSISTDECFIXMP	= 58,	// ��������
		BUFFFUNC_INCFIXHP			= 59,	// ҽ��HP�̶�ֵ
		BUFFFUNC_INCPERHP			= 60,	// ҽ��HP�ٷֱ�
		BUFFFUNC_INCFIXMP			= 61,	// �ָ�MP�̶�ֵ
		BUFFFUNC_INCPERMP			= 62,	// �ָ�MP�ٷֱ�
		BUFFFUNC_DECFIXHP			= 63,	// ����HP�̶�ֵ
		BUFFFUNC_DECPERHP			= 64,	// ����HP�ٷֱ�
		BUFFFUNC_DECFIXMP			= 65,	// ����MP�̶�ֵ
		BUFFFUNC_DECPERMP			= 66,	// ����MP�ٷֱ�
		BUFFFUNC_PERSISTINCFIXEXP	= 67,	// ������þ���ֵ
		BUFFFUNC_INCHONORPER		= 68,	// ���ӹ�ѫ��ðٷֱ�
		BUFFFUNC_PROTECTED			= 69,	// �ػ�
		BUFFFUNC_TELEPORT			= 70,	// ˲��
		BUFFFUNC_RELIVE				= 71,	// ����
		BUFFFUNC_HITBACK			= 72,	// ����
		BUFFFUNC_MAGICSHIELD		= 73,	// ħ����
		BUFFFUNC_IMMUNITYDAMAGE		= 74,	// �����˺�
		BUFFFUNC_REBOUNDDAMAGE		= 75,	// �����˺�
		BUFFFUNC_OBLITERATEDAMAGE	= 76,	// �ܵ��˺�ɾ��Buff
		BUFFFUNC_UNMOVE				= 77,	// �޷��ƶ�
		BUFFFUNC_UNUSEITEM			= 78,	// �޷���ҩ
		BUFFFUNC_UNATTACK			= 79,	// �޷�����
		BUFFFUNC_RANDMOVE			= 80,	// �漴�߶�
		BUFFFUNC_REMOVEREVERSDBUFF	= 81,	// �������Buff
		BUFFFUNC_IMMUNITYREVERSD	= 82,	// ���߸���Buff
		BUFFFUNC_SNEER				= 83,	// ����
		BUFFFUNC_HITDEATH			= 84,	// ����
		BUFFFUNC_IGNORECLOTH		= 85,	// �����·������Լ���
		BUFFFUNC_UNARM				= 86,	// �������������Լ���
		BUFFFUNC_IMBIBITIONMP		= 87,	// ��ȡMP�̶�ֵ
		BUFFFUNC_SUICIDE			= 88,	// ��Ѫ����
		BUFFFUNC_STEALHP			= 89,	// ���˺��ٷֱ�͵HP
		BUFFFUNC_STEALMP			= 90,	// ���˺��ٷֱ�͵MP
		BUFFFUNC_INCGENERDAMAGEFIX	= 91,	// ��ĳϵ���ܹ����������ܵ����˺��̶�ֵ
		BUFFFUNC_INCGENERDAMAGEPER	= 92,	// ��ĳϵ���ܹ����������ܵ����˺��ٷֱ�
		BUFFFUNC_CHARGE				= 93,  // ���
		BUFFFUNC_ATTACKEFFECT		= 94,	// ������N�ι���ʱ��������Ч��
		BUFFFUNC_HPBACKEFFECT		= 95,  // �����ָ�Ч�����Ͱٷֱ�
		BUFFFUNC_LEAVEAREA			= 96,	// �뿪��debuffʱ������Χ���ܵ�����Ч��
		BUFFFUNC_SUMMON				= 97,	// ����
		BUFFFUNC_MAGICFIRE			= 98,	// ����ȼ��
		BUFFFUNC_DAMAGELESS			= 99,	// ����N���˺�
		BUFFFUNC_KILLERRENEW		= 100,	// ɱ��ȡѪ
		BUFFFUNC_ENDEVENT			= 101,	// Buff��ʧʱ������Ч��
		BUFFFUNC_CHANGEPATH			= 102,	// ����λ��
		BUFFFUNC_EXCHANGE			= 103,	// ��Ѫ
		BUFFFUNC_DAMAGEFORMP		= 104,	// ����ȱʧ�ķ���ֵ�İٷֱȵ�Ѫ
		BUFFFUNC_DAMAGEDEVENT		= 105,	// �ܵ��˺�ʱ��Ŀ���������Ч��
		BUFFFUNC_CIRCUMGYRATE		= 106,	// ����
		BUFFFUNC_CUREDAMAGE			= 107,	// ����Ŀ�겢��Χ�˺�Ŀ����Χ
		BUFFFUNC_FIREEVENT			= 108,	// �ɹ��ż��ܻ��ܵ�����Ч��
		BUFFFUNC_TREE				= 109,	// ��Χ����
		BUFFFUNC_ATTACKEVENT		= 110,	// ��������Ч��
		BUFFFUNC_FIREWALL			= 111,	// ��ǽ
		BUFFFUNC_INCEXP				= 112,	// ���Ӿ���ٷֱ�
		BUFFFUNC_HITDEATHHP			= 113,	// ������N�����N����ֵ���µ�Ŀ��������N���ϵ����M���˺�
		BUFFFUNC_DECALLDAMAGEPER	= 114,	// ���������ܵ��˺��İٷֱȰ���BUFF
		BUFFFUNC_DAMAGEDEVENTSELF	= 115,	// �ܵ��˺����Լ���������Ч��
		BUFFFUNC_CLEARBUFF			= 116,	// �������BUFF
		BUFFFUNC_CLEARDEBUFF		= 117,	// �������BUFF
		BUFFFUNC_SAVEDAMAGE			= 118,	// �����˺�����BUFF���������յ��˺�����
		BUFFFUNC_RANGEDAMAGE		= 119,	// ��Χ�̶��˺�
		BUFFFUNC_TRANSFORM			= 120,	// ����BUFF
		BUFFFUNC_PERSISTINCPERHP	= 121,	// ������MaxHP�ٷֱȻָ�CurHP
		BUFFFUNC_PERSISTINCPERMP	= 122,	// ������MaxMP�ٷֱȻָ�CurMP

		BUFFINC_STRPER				= 123,	// ���������ٷֱ�
		BUFFINC_CONPER				= 124,	// �������ʰٷֱ�
		BUFFINC_STAPER				= 125,	// ���������ٷֱ�
		BUFFINC_SPRPER				= 126,	// ���Ӿ���ٷֱ�
		BUFFINC_WISPER				= 127,	// ���������ٷֱ�
		BUFFINC_IGNOREDUCK			= 128,	// ���Ӻ��ӷ���
		BUFFINC_DEATHDEFENSE		= 129,	// ������������
		BUFFINC_RESDEF1				= 130,	// ���ӿ���1
		BUFFINC_RESDEF2				= 131,	// ���ӿ���2
		BUFFINC_RESDEF3				= 132,	// ���ӿ���3
		BUFFINC_RESDEF4				= 133,	// ���ӿ���4
		BUFFINC_RESDEF5				= 134,	// ���ӿ���5
		BUFFINC_RESDEF6				= 135,	// ���ӿ���6
		BUFFINC_RESATT1				= 136,	// ��������1
		BUFFINC_RESATT2				= 137,	// ��������2
		BUFFINC_RESATT3				= 138,	// ��������3
		BUFFINC_RESATT4				= 139,	// ��������4
		BUFFINC_RESATT5				= 140,	// ��������5
		BUFFINC_RESATT6				= 141,	// ��������6
		BUFFFUNC_INCAP				= 142,	// ���ӹ�ѫ
		BUFFFUNC_INCCORPSGORY		= 143,	// ���Ӿ��ž���
	
		BUFFFUNC_PLAYER_UNATTACK	= 144,	// �޷�����ҹ��� 
		BUFFFUNC_UNATTACK_PLAYER	= 145,	// �޷��������
		BUFFFUNC_HORSE				= 146,	// ����״̬
		BUFFFUNC_INVISIBLE			= 147,	// ���� 
		BUFFFUNC_USESKILL_REMOVE	= 148,	// ʹ�ü���ɾ��BUFF
		BUFFFUNC_DISINVISIBLE		= 149,	// ��Ӱ��
		BUFFFUNC_UNFUNC				= 150,	// �ض�BUFF������Ч
		BUFFINC_DUCKRATE			= 151,	// ����������
		BUFFFUNC_FLY				= 152,	// ����
		BUFFINC_DEFALLPER			= 153,	// ���ӷ����ٷֱ�
		BUFFINC_DEFALLFIX			= 154,	// ���ӷ����̶�ֵ
		BUFFINC_ATTALLPER			= 155,	// ���ӹ����ٷֱȣ��ޣ�
		BUFFINC_ATTALLFIX			= 156,	// ���ӹ����̶�ֵ���ޣ�
		BUFFFUNC_STONE				= 157,	// ��ʯ
		BUFFINC_RESDEFALL			= 158,	// ȫ��
		BUFFINC_RESATTALL			= 159,	// ȫ��
		BUFFFUNC_ADDSKILL			= 160,	// ��ü���
        BUFFFUNC_REFRESHSKILLCD     = 161,  // ˢ�¼���
		BUFFFUNC_HIDE				= 162,	// ������������
		BUFFFUNC_PERSISTDECPERHP	= 163,	// �����ٷֱ��˺�
		BUFFFUNC_OBTEXP_BYTAB		= 164,	// ���ݾ����Ӿ���
		BUFFFUNC_IGNOREPIMUPER		= 165,	// �����������˰ٷֱ�
		BUFFFUNC_IGNOREMIMUPER		= 166,	// ���ӷ������˰ٷֱ�
		BUFFFUNC_INCOFFLINEEXP		= 167,	// �������߾���ٷֱ�
		BUFFFUNC_IGNOREPDEFENCE		= 168,	// ������������ٷֱ�
		BUFFFUNC_IGNOREMDEFENCE		= 169,	// ���ӷ��������ٷֱ�
		BUFFFUNC_BUFFAFTERBUFF		= 170,	//�ɹ���ʧ�ܺ��õ�����Ч��
		BUFFFUNC_REDUCEHPTO			= 171,	//�������HP���̶�ֵ
		BUFFFUNC_REDUCEMPTO			= 172,	//�������MP���̶�ֵ
	};
	// BUFFFUNC_REFRESHSKILLCD:
	// mBuffParam[0] = 0 ˢ��һ������ mBuffParam[1] Ҫˢ�µļ���id mBuffParam[2] ��ˢ�µļ���id 
	//                 = 1 ˢ��һ��ϵ�ļ��� mBuffParam[1] Ҫˢ�µļ���ϵ��id mBuffParam[2] ��ˢ�µļ���id 
	//                 = 2 ˢ��ȫ�弼�� mBuffParam[1] ������  mBuffParam[2] ��ˢ�µļ���id 

	class CBuffFunc
	{
	public:
		BUFF_FUN_TYPE		mBuffFunc;
		int					mBuffParam[ 4 ];
	};

	enum BUFF_STYLE
	{
		BUFF_COMM					= 0,	// ��ͨBuff
		BUFF_AUREOLE				= 1,						// �⻷Buff
	};

	enum EMBUFF_TIMER_TYPE
	{
		BUFF_TIMER_TYPE_GAME = 0,			// ��Ϸʱ��
		BUFF_TIMER_TYPE_REAL = 1,				// ��ʵʱ��
	};

	enum BUFF_CANCLE_TYPE
	{
		BUFF_CANCEL				= 0,	// Ҫ���
		BUFF_NOTCANCEL			= 1,	// �����				
	};

	enum BUFF_MAP_TYPE
	{
		NON_BUFF				= 0,		// ��
		BATTLE_BUFF				= 1,			// ս��Buff
		FB_BUFF					= 2,			// FB Buff
		COMM_BUFF				= 3,			// ��ͨBuff
		GROUND_BUFF				= 4,			// �ع�Buff
	};

	enum BUFF_SUPERPOSITION_TYPE
	{
		NONE_SUPERPOSITION			= 0,		// �޵���
		TIME_SUPERPOSITION,						// ʱ�����
		FUNC_SUPERPOSITION,						// ���ܵ���
	};

	enum NUFF_STONE_TYPE
	{
		STONE_COLLECT				= 1,		// �ɼ���
		STONE_FLAG					= 2,		// ������
	};

public:

	// FieldName: Buff��ϵ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mBuffSeriesID;

	// FieldName: Buff������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mIdenValue;


	// FieldName: Buff��������
	// FieldType: INT4
	// Type:	  COMBOENUM(BUFF_STYLE)
	BUFF_STYLE mBuffStyle; 

    // FieldName: Buff�����״�����ʱ����(0��ʾ��������;������������ʱ������ͬ)
    // FieldType: INT4
    // Type:      EDITNUMBER(0,1000000) 
	int		mBuffFirstActionTime;

    // FieldName: Buff��������ʱ����(0��ʾ���Ǽ��������;��������ܱ�buff����ʱ������)
    // FieldType: INT4
    // Type:      EDITNUMBER(0,1000000) 
	int		mBuffActionTime;

	// FieldName: Buff�ĵ�%d�����
	// FieldType: INT4
	// Type:	  COMBOENUM(BUFF_FUN_TYPE)

	// FieldName: Buff�ĵ�%d����빦����ֵ1
	// FieldType: INT4
	// Type:	  EDITNUMBER(-100000,100000000)

	// FieldName: Buff�ĵ�%d����빦����ֵ2
	// FieldType: INT4
	// Type:	  EDITNUMBER(-100000,100000000)

	// FieldName: Buff�ĵ�%d����빦����ֵ3
	// FieldType: INT4
	// Type:	  EDITNUMBER(-100000,100000000)

	// FieldName: Buff�ĵ�%d����빦����ֵ4
	// FieldType: INT4
	// Type:	  EDITNUMBER(-100000,100000000)

	CBuffFunc	mBuff[ MAX_BUFFFUN_COUNT ]; 

	// FieldName: $Buff����ʾ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mBuffName[ 32 ];

	// FieldName: Buff��ͼ��
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mBuffIcon[ 32 ];

	// FieldName: $Buff����ʾ������ʾ
	// FieldType: STRING128
	// Type:	  EDITSTRING
	char	mBuffDesc[ 128 ];

	// FieldName: Buff�ľ������и���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mHitrate;
	
	// FieldName: Buffֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mBuffValue;
	
	// FieldName: Buff����ϵ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(ŭ��ϵ,����ϵ,����ϵ,����ϵ,����ϵ,����ϵ,����)
	int		mResistType;
	
	// FieldName: Buff����ʱ�����(0��ʾ��������1��,��1��,-1Ϊ����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,100000000)
	int		mLastTime;

	// FieldName: Buff������(�������)
	// FieldType: INT4
	// Type:	  COMBOENUM(BUFF_TYPE)
	BUFF_TYPE	mBuffType;

	// FieldName: Buff�Ƿ�����ֶ�ȡ��
	// FieldType: INT4
	// Type:	  COMBOENUM(BUFF_CANCLE_TYPE)
	int		mCancelBuff;

	// FieldName: Buff�Ƿ����ս��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����ս��=0,����ս��)
	int		mEnableBattle;

	// FieldName: Buff�Ķ�����Ч
	// FieldType: STRING32
	// Type:	  EDITSTRING	
	char	mBuffAni[ 32 ];

	// FieldName: Buff��ʾ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����ʾ=0,��һ��=1,�ڶ���,������)
	unsigned int mBuffRow;

	// FieldName: Buff�������Ƿ���ʧ
	// FieldType: INT4
	// Type:	  COMBOENUM(BUFF_CANCLE_TYPE)
	unsigned int mBuffDieDel;

	// FieldName: Buff��ʱ������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��Ϸʱ��=0,��ʵʱ��)
	int			 mTimerType;

	// FieldName: Buff�ܷ����
	// FieldType: INT4
	// Type:      COMBOENUM(BUFF_CANCLE_TYPE)
	int			 mBuffClear;

	// FieldName: �ض���ͼID
	// FieldType: INT4
	// Type:      EDITNUMBER(0,65535)
	int			 mBuffMapID;

	// FieldName: �ض���ID
	// FieldType: INT4
	// Type:      EDITNUMBER(0,65535)
	int			 mBuffLineID;

	// FieldName: �˺�����
	// FieldType: INT4
	// Type:      EDITNUMBER(0,65535)
	int			 mSkillLevel;

	// FieldName: ����Buff
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int			  mCountryBuff;

	// FieldName: Buff��ͼ����
	// FieldType: INT4
	// Type:	  COMBOENUM(BUFF_MAP_TYPE)
	BUFF_MAP_TYPE mBuffMapType;

	// FieldName: Buff��������
	// FieldType: INT4
	// Type:      COMBOENUM(BUFF_SUPERPOSITION_TYPE)
	BUFF_SUPERPOSITION_TYPE	mBuffSuperposition;	

	// FieldName: Buff�������и���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mAccurate;

	// FieldName: �����Ƿ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int		mOffRemove;

	// FieldName: Buff�Ƿ��Ʊ���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	int		mTransform;	

	// FieldName: Buffȥ�����ӵ�ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mRemoveCountID;
public:
	void SetFromPB( bool bServer, PBBuff* pBuff );
	void CreateTlvPB( bool bServer, PBBuff* pBuff );
	int Initialize();
	CTemplateBuff()
	{
		Initialize();
	}
	~CTemplateBuff() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �ȼ������		## ģ������
// version	= 1					## �汾��
// path		= Config/�ȼ������	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateLevelExp : public CTemplate
{
public:

	// FieldName: ��%d���ľ�����ֵ
	// FieldType: INT8
	// Type:	  EDITNUMBER(0,72057594037927935)
	unsigned long long	mLevelExp[ TMP_MAX_GRADE ];	

public:
	void SetFromPB( bool bServer, PBLevelExp* pLevelExp );
	void CreateTlvPB( bool bServer, PBLevelExp* pLevelExp );
	int Initialize();
	CTemplateLevelExp() 
	{
		Initialize();
	}
	~CTemplateLevelExp() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

struct CSingleMoneyLmt
{
	unsigned int   mBagMoneyLmt;	
	unsigned int   mBagBindMoneyLmt;	
	unsigned int   mStorageMoneyLmt;	
	unsigned int   mStorageBindMoneyLmt;	
};
// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �ȼ���Ǯ���ޱ�	## ģ������
// version	= 1					## �汾��
// path		= Config/�ȼ���Ǯ���ޱ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateLevelMoneyLmt : public CTemplate
{
public:

	// FieldName: ��%d�����ư���Я���ķǰ󶨽�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,900000000)

	// FieldName: ��%d�����ư���Я���İ󶨽�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,900000000)

	// FieldName: ��%d�����Ʋֿ��ŵķǰ󶨽�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,900000000)

	// FieldName: ��%d�����Ʋֿ��ŵİ󶨽�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,900000000)
	CSingleMoneyLmt  mLmtTable[ TMP_MAX_GRADE ];

public:
	void SetFromPB( bool bServer, PBLevelMoneyLmt* pLevelMoney );
	void CreateTlvPB( bool bServer, PBLevelMoneyLmt* pLevelMoney );
	int Initialize();
	CTemplateLevelMoneyLmt() 
	{
		Initialize();
	}
	~CTemplateLevelMoneyLmt() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ���ﾭ���		## ģ������
// version	= 1					## �汾��
// path		= Config/���ﾭ���	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplatePetLevelExp : public CTemplate
{
public:

	// FieldName: ��1��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��2��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��3��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��4��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��5��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��6��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��7��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��8��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��9��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��10��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��11��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��12��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��13��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��14��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��15��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��16��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��17��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��18��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��19��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��20��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��21��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��22��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��23��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��24��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��25��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��26��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��27��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��28��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��29��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��30��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��31��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��32��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��33��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��34��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��35��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��36��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��37��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��38��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��39��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��40��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��41��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��42��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��43��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��44��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��45��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��46��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��47��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��48��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��49��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��50��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��51��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��52��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��53��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��54��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��55��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��56��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��57��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��58��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��59��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��60��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��61��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��62��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��63��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��64��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��65��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��66��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��67��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��68��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��69��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��70��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��71��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��72��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��73��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��74��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��75��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��76��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��77��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��78��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��79��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��80��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��81��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��82��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��83��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��84��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��85��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��86��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��87��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��88��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��89��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��90��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��91��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��92��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��93��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��94��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��95��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��96��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��97��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��98��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��99��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��100��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��101��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��102��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��103��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��104��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��105��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��106��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��107��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��108��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��109��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��110��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��111��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��112��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��113��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��114��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��115��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��116��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��117��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��118��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��119��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��120��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��121��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��122��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��123��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��124��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��125��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��126��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��127��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��128��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��129��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��130��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��131��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��132��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��133��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��134��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��135��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��136��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��137��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��138��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��139��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��140��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��141��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��142��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��143��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��144��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��145��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��146��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��147��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��148��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��149��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��150��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��151��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��152��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��153��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��154��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��155��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��156��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��157��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��158��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��159��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��160��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	unsigned int	mLevelExp[ TMP_MAX_GRADE ];	

public:
	void SetFromPB( bool bServer, PBPetLevelExp* pLevelExp );
	void CreateTlvPB( bool bServer, PBPetLevelExp* pLevelExp );
	int Initialize();
	CTemplatePetLevelExp() 
	{
		Initialize();
	}
	~CTemplatePetLevelExp() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ���������		## ģ������
// version	= 1					## �汾��
// path		= Config/���������	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateProExp : public CTemplate
{
public:


	// FieldName: ��1��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��2��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��3��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��4��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��5��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��6��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��7��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��8��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��9��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��10��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��11��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��12��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��13��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��14��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��15��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	unsigned int	mLevelExp[ 15 ];	

public:
	void SetFromPB( bool bServer, PBProduceExp* pExp );
	void CreateTlvPB( bool bServer, PBProduceExp* pExp );
	int Initialize();
	CTemplateProExp()
	{
		Initialize();
	}
	~CTemplateProExp() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= װ��������		## ģ������
// version	= 1					## �汾��
// path		= Config/װ��������	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateEquipUpg : public CTemplate
{
public:
	class CEquipUpg
	{
	public:
		int		mSuccess;		// �ɹ��ĸ���
		int		mFail;			// ��ʧ�ĸ���
		int		mResult;		// ʧ�ܺ�Ľ��
		int		mIncLevel;		// �����ɹ��������ĵȼ�
		int		mExtSuccess;	// �������ĳɹ�����
	};

public:

	// FieldName: %d��%d��װ�������ĳɹ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)

	// FieldName: %d��%d��װ����������ʧ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)

	// FieldName: %d��%d��װ������ʧ�ܵĽ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,100)

	// FieldName: %d��%d��װ�������ɹ��������ĵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: %d��%d��װ���������ĳɹ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	CEquipUpg	mEquipUpg[ 3 ][ 15 ];

public:
	void SetFromPB( bool bServer, PBEquipUpg* pEquip );
	void CreateTlvPB( bool bServer, PBEquipUpg* pEquip );
	int Initialize();
	CTemplateEquipUpg() 
	{
		Initialize();
	}
	~CTemplateEquipUpg() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��������װ		## ģ������
// version	= 1					## �汾��
// path		= ��װ/��������װ	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateSuitProducer : public CTemplate
{
public:

	// FieldName: ȫ��4��װ����ͬ1�����������ĸ�������ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ȫ��5��װ����ͬ1�����������ĸ�������ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ȫ��6��װ����ͬ1�����������ĸ�������ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ȫ��7��װ����ͬ1�����������ĸ�������ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ȫ��8��װ����ͬ1�����������ĸ�������ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ȫ��9��װ����ͬ1�����������ĸ�������ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ȫ��10��װ����ͬ1�����������ĸ�������ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mPropertyTempID[ 7 ];

	// FieldName: ȫ��+%dװ����%d������ĸ�������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mUpgTempID[ 16 ][ 21 ];

	// FieldName: ȫ����%d�����̵ĸ�������ID%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mExtTempID[ 21 ][ 5 ];

	// FieldName: $��������%d����
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char		mDesText[ 21 ][ STRING256 ];

public:
	void SetFromPB( bool bServer, PBSuitProducer* pSuit );
	void CreateTlvPB( bool bServer, PBSuitProducer* pSuit );
	int Initialize();
	CTemplateSuitProducer() 
	{
		Initialize();
	}
	~CTemplateSuitProducer() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��ͨ��װ			## ģ������
// version	= 1					## �汾��
// path		= ��װ/��ͨ��װ		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateSuitNormal : public CTemplate
{
public:
	
	// FieldName: $��װ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		mName[ STRING32 ];
	
	// FieldName: ��װ��Ҫ��װ��1ID
	// FieldType: INT4
	// Type:	  EDITNUMBER
	
	// FieldName: ��װ��Ҫ��װ��2ID
	// FieldType: INT4
	// Type:	  EDITNUMBER
	
	// FieldName: ��װ��Ҫ��װ��3ID
	// FieldType: INT4
	// Type:	  EDITNUMBER
	
	// FieldName: ��װ��Ҫ��װ��4ID
	// FieldType: INT4
	// Type:	  EDITNUMBER
	
	// FieldName: ��װ��Ҫ��װ��5ID
	// FieldType: INT4
	// Type:	  EDITNUMBER
	
	// FieldName: ��װ��Ҫ��װ��6ID
	// FieldType: INT4
	// Type:	  EDITNUMBER
	
	// FieldName: ��װ��Ҫ��װ��7ID
	// FieldType: INT4
	// Type:	  EDITNUMBER
	
	// FieldName: ��װ��Ҫ��װ��8ID
	// FieldType: INT4
	// Type:	  EDITNUMBER
	
	// FieldName: ��װ��Ҫ��װ��9ID
	// FieldType: INT4
	// Type:	  EDITNUMBER
	
	// FieldName: ��װ��Ҫ��װ��10ID
	// FieldType: INT4
	// Type:	  EDITNUMBER
	
	// FieldName: ��װ��Ҫ��װ��11ID
	// FieldType: INT4
	// Type:	  EDITNUMBER
	
	// FieldName: ��װ��Ҫ��װ��12ID
	// FieldType: INT4
	// Type:	  EDITNUMBER

	// FieldName: ��װ��Ҫ��װ��13ID
	// FieldType: INT4
	// Type:	  EDITNUMBER
	int			mEquipTempID[ 13 ];
	
	// FieldName: $��װ�������ҳƺ�
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		mActiveTitle[ STRING32 ];

	// FieldName: ��װ�������Ҹ�������1ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��װ�������Ҹ�������2ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��װ�������Ҹ�������3ID
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��װ�������Ҹ�������4ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mPropertyTempID[ 4 ];

public:
	void SetFromPB( bool bServer, PBSuitNormal* pSuit );
	void CreateTlvPB( bool bServer, PBSuitNormal* pSuit );
	int Initialize();
	CTemplateSuitNormal( )
	{
		Initialize();
	}
	~CTemplateSuitNormal() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��������			## ģ������
// version	= 1					## �汾��
// path		= ��װ/��������		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateSpell : public CTemplate
{
public:

	// FieldName: $���׷�����ʾ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		mName[ STRING32 ];

	// FieldName: ��װ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mSuitID;

	// FieldName: ���׷�����Ҫ������1
	// FieldType: INT4
	// Type:	  TEMPPATH
	
	// FieldName: ���׷�����Ҫ������2
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷�����Ҫ������3
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷�����Ҫ������4
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷�����Ҫ������5
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷�����Ҫ������6
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷�����Ҫ������7
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷�����Ҫ������8
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷�����Ҫ������9
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷�����Ҫ������10
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷�����Ҫ������11
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷�����Ҫ������12
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷�����Ҫ������13
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mLetterID[ 13 ];

	// FieldName: ���׷��ļ���ĵ�һ���������Ҫ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ���׷��ļ���ĵڶ����������Ҫ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ���׷��ļ���ĵ������������Ҫ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ���׷��ļ���ĵ������������Ҫ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ���׷��ļ���ĵ������������Ҫ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	int			mRequire[ 5 ];

	// FieldName: ���׷��ļ���ĵ�һ�������1
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ�һ�������2
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ�һ�������3
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ�һ�������4
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵڶ��������1
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵڶ��������2
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵڶ��������3
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵڶ��������4
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ����������1
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ����������2
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ����������3
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ����������4
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ����������1
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ����������2
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ����������3
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ����������4
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ����������1
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ����������2
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ����������3
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ���׷��ļ���ĵ����������4
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mPropertyTempID[ 5 ][ 4 ];

	// FieldName: $��������1����
	// FieldType: STRING256
	// Type:	  EDITSTRING

	// FieldName: $��������2����
	// FieldType: STRING256
	// Type:	  EDITSTRING

	// FieldName: $��������3����
	// FieldType: STRING256
	// Type:	  EDITSTRING

	// FieldName: $��������4����
	// FieldType: STRING256
	// Type:	  EDITSTRING

	// FieldName: $��������5����
	// FieldType: STRING256
	// Type:	  EDITSTRING

	char		mDesText[ 5 ][ STRING256 ];

public:
	void SetFromPB( bool bServer, PBSpell* pSpell );
	void CreateTlvPB( bool bServer, PBSpell* pSpell );
	int Initialize();
	CTemplateSpell()
	{
		Initialize();
	}
	~CTemplateSpell() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= װ������			## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/װ������		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateProEquip : public CTemplate
{
public:

	// FieldName: װ������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����=0,ñ��,�·�,����,����,��ָ,����,����,����,����,����)
	int			mType;

	// FieldName: װ������ϸ���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(ǹ=0,˫��,��,����,����,��,�ؼ�,���,����,����,����)
	int			mDetailID1;

	// FieldName: ���ߵ���ϸ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,�������,��������,ȫ����,ȫ����,��������,��������)
	int			mDetailID2;

	// FieldName: װ���ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int			mLevel;

	// FieldName: $װ������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		mName[ STRING32 ];

	// FieldName: ����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mMaterialID;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int			mMaterialNum;

	// FieldName: ���ϵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int			mMaterialRank;

	// FieldName: ����1ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mItemID1;

	// FieldName: ����1����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mItemRan1;

	// FieldName: ����2ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mItemID2;

	// FieldName: ����2����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mItemRan2;

	// FieldName: ����3ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mItemID3;

	// FieldName: ����3����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mItemRan3;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mMoney;

	// FieldName: �Ƿ�֧�ְ󶨽�Ǯ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int			mBindMoney;

	// FieldName: ͼ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mIconID;

	// FieldName: $װ��˵��
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char		mDesc[ STRING256 ];

	// FieldName: ���þ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mExp;

public:
	void SetFromPB( bool bServer, PBProduceEquip* pEquip );
	void CreateTlvPB( bool bServer, PBProduceEquip* pEquip );
	int Initialize();
	CTemplateProEquip()
	{
		Initialize();
	}
	~CTemplateProEquip() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ҩƷ����			## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/ҩƷ����		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateProPhysics : public CTemplate
{
public:

	// FieldName: ҩƷ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��,����BUFF,����BUFF,����BUFF,����BUFF,����BUFF,����)
	int			mType;

	// FieldName: ҩƷ�ȼ�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(1��=0,2��,3��,4��)
	int			mLevel;

	// FieldName: $ҩƷ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		mName[ STRING32 ];

	// FieldName: ����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mMaterialID;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int			mMaterialNum;

	// FieldName: ����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mItemID;

	// FieldName: ���þ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mExp;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mMoney;

	// FieldName: �Ƿ�֧�ְ󶨽�Ǯ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int			mBindMoney;

public:
	void SetFromPB( bool bServer, PBProducePhysic* pPhysic );
	void CreateTlvPB( bool bServer, PBProducePhysic* pPhysic );
	int Initialize();
	CTemplateProPhysics() 
	{
		Initialize();
	}
	~CTemplateProPhysics() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ����				## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/����			## ·��
// parent	= ���߻�����Ϣ		## ����ģ��
// ********************************************************************** //
class CTplItemRune : public CTplItem
{
public:

	// FieldName: ��װ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mSuitID;

	// FieldName: $������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		mWord[ STRING32 ];

	// FieldName: ��װ�е�˳��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mOrderID;

	// FieldName: ��Ƕ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mInsertCharge;

	// FieldName: ������������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mPropertyID;

	// FieldName: ����˳����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mRuneIndex;

	// FieldName: ��ʾ��ɫ�������Ͻ�ʣ�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��ɫ=0,��ɫ,��ɫ,��ɫ,��ɫ)
	int			mShowColor;



public:
	void SetFromPB( bool bServer, PBItemRune* pRuneItem );
	void CreateTlvPB( bool bServer, PBItemRune* pRuneItem );
	int Initialize();
	CTplItemRune() 
	{ 
		Initialize();
	}
	~CTplItemRune()  {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �鱦				## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/�鱦			## ·��
// parent	= ���߻�����Ϣ		## ����ģ��
// ********************************************************************** //
class CTplItemJewel : public CTplItem
{
public:

	enum
	{
		POS_RING		= 0x01,				// ��ָ��װ��
		POS_CUFF		= 0x02,				// ������װ��
		POS_WEAPON		= 0x04,				// ������װ��
		POS_CHEST		= 0x08,				// ������װ��
		POS_LEG			= 0x10,				// ������װ��
		POS_HEAD		= 0x20,				// ��ͷ��װ��
		POS_NECK		= 0x40,				// ������װ��
		POS_SASH		= 0x80,				// ������װ��
		POS_CHARM		= 0x100,			// ������װ��
		POS_BALL		= 0x200,			// ������װ��
		POS_CLOAK		= 0x400,			// ������װ��
		POS_FASHION		= 0x800,			// ʱװ��װ��
		POS_MAGICWEAPON	= 0x1000,			// ������װ��
	};

	enum
	{
		JEWEL_WHITE	= 0,				// ��ɫ��ʯ
		JEWEL_BLUE  = 1,						// ��ɫ��ʯ
		JEWEL_PURPLE = 2,					// ��ɫ��ʯ
		JEWEL_GOLD   = 3,						// ��ɫ��ʯ
		JEWEL_COLOR  = 4,					// ��ɫ��ʯ
	};	

	// FieldName: �鱦�ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mTypeID;

	// FieldName: װ��λ��
	// FieldType: INT4
	// Type:	  CHECKMUTI(��ָ��װ��=1,������װ��,������װ��,������װ��,������װ��,��ͷ��װ��,������װ��,������װ��,������װ��,������װ��,������װ��,������װ��)
	int			mPos;

	// FieldName: ��ʾ��ɫ�������Ͻ�ʣ�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��ɫ=0,��ɫ,��ɫ,��ɫ,��ɫ)
	int			mShowColor;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mProperty;

	// FieldName: �Ƿ�Ψһ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mUnique;

	// FieldName: ����%d���õ��ı�ʯID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mJewelID[ 9 ];

	// FieldName: ��ʯ�䷽ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mComposeID;

	// FieldName: ��Ƕ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mInsertCharge;

	// FieldName: ժ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mRemoveCharge;

	// FieldName: �ϳɷ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mComposeCharge;

	// FieldName: �鱦����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mLevel;

	// FieldName: %d�ָ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mRand[ 5 ];

	// FieldName: ����õ��ı�ʯID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int			mNewJewelID;

	// FieldName: %d���ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mNewRand[ 5 ];

	// FieldName: �����õ��ı�ʯID%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mCarveJewelID[ 3 ];

	// FieldName: �����õ��ĸ���%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mCarveRand[ 3 ];

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mCarveCharge;

	// FieldName: ��Ҫ�ĵ�����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mCardID;

	// FieldName: �Ƿ���Ե���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int			mCanCarve;

	// FieldName: �Ժϳɸ���Ӱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mAffectRand;

	// FieldName: ��ʯ�ϳɹ��ñ�־
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mJewComID;

	// FieldName: �ϳɵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mComLevel;

public:
	void SetFromPB( bool bServer, PBItemJewel* pJewelItem );
	void CreateTlvPB( bool bServer, PBItemJewel* pJewelItem );
	int Initialize();
	CTplItemJewel() 
	{
		Initialize();
	}
	~CTplItemJewel() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= Ԫ����			## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/Ԫ����		## ·��
// parent	= ���߻�����Ϣ		## ����ģ��
// ********************************************************************** //
class CTplItemYuanBug : public CTplItem
{
public:

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mYuan;

	// FieldName: ת���ɵĵ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mEggID;

	// FieldName: �������Ͱ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mYuanType;

public:
	void SetFromPB( bool bServer, PBItemYuanBug* pBugItem );
	void CreateTlvPB( bool bServer, PBItemYuanBug* pBugItem );
	int Initialize();
	CTplItemYuanBug( )
	{
		Initialize();
	}
	~CTplItemYuanBug() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= Ԫ����			## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/Ԫ����		## ·��
// parent	= ���߻�����Ϣ		## ����ģ��
// ********************************************************************** //
class CTplItemYuanEgg : public CTplItem
{
public:

	// FieldName: �ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int			mLevel;

	// FieldName: �ϳɵ��䷽ID
	// FieldType: INT4
	// Type:	  TEMPPATH
	int mComposeID;

	// FieldName: ���װ���ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mMaxEquip;

public:
	void SetFromPB( bool bServer, PBItemYuanEgg* pEggItem );
	void CreateTlvPB( bool bServer, PBItemYuanEgg* pEggItem );
	int Initialize();
	CTplItemYuanEgg() 
	{
		Initialize();
	}
	~CTplItemYuanEgg() {}
};	 

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��ħ��Ʒ			## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/��ħ��Ʒ		## ·��
// parent	= ���߻�����Ϣ		## ����ģ��
// ********************************************************************** //
class CTplItemMagicStone : public CTplItem
{
public:
	enum EPart
	{
		PART_RING			= ( 1 << 0 ),		// ��ָ��װ��
		PART_CUFF			= ( 1 << 1 ),		// ������װ��
		PART_WEAPON			= ( 1 << 2 ),		// ������װ��
		PART_CHEST			= ( 1 << 3 ),		// ������װ��
		PART_LEG			= ( 1 << 4 ),		// ������װ��
		PART_HEAD			= ( 1 << 5 ),		// ��ͷ��װ��
		PART_NECK			= ( 1 << 6 ),		// ������װ��
		PART_SASH			= ( 1 << 7 ),		// ������װ��
		PART_CHARM			= ( 1 << 8 ),		// ������װ��
		PART_BALL			= ( 1 << 9 ),		// ������װ��
		PART_CLOAK			= ( 1 << 10 ),		// ������װ��
		PART_FASHION		= ( 1 << 11 ),		// ʱװ��װ��
		PART_MAGICWEAPON	= ( 1 << 12 ),		// ������װ��
	};		
		
public:
	// FieldName: ��ħ�Ĳ�λ
	// FieldType: INT4
	// Type:	  CHECKMUTI(��ָ��װ��,������װ��,������װ��,������װ��,������װ��,��ͷ��װ��,������װ��,������װ��,������װ��,������װ��,������װ��,ʱװ��װ��,������װ��)
	int		mPart;

	// FieldName: ͬ�฽ħʯ��%d�θ�ħʱ���ɵ�����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mAttribute[MAX_MAGICSTONE_USEDTIMES];
	
	// FieldName: ����ʹ�õĴ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mUsedTimes;
	
	// FieldName: ��%d��ʹ�ø�ħ��Ʒ��ħ�ɹ��ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mProbability[MAX_MAGICSTONE_USEDTIMES];
	
	// FieldName: ��ħװ���ȼ�Ҫ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mLevelLimit;
	
public:
	void SetFromPB( bool bServer, PBItemMagicStone* pMagicStone );
	void CreateTlvPB( bool bServer, PBItemMagicStone* pMagicStone );
	int Initialize();
	CTplItemMagicStone() 
	{
		Initialize();
	}
	~CTplItemMagicStone() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ������䷽����		## ģ������
// version	= 1						## �汾��
// path		= ��Ʒ/������䷽����	## ·��
// parent	= ���߻�����Ϣ			## ����ģ��
// ********************************************************************** //
class CTplItemLifeSkillScroll : public CTplItem
{											
public:
	// FieldName: �����䷽ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mComposeID;
	
	// FieldName: �䷽����
	// FieldType: INT4
	// Type:	  COMBOENUM(EM_LIFESKILL)
	int		mComposeType;

public:
	void SetFromPB( bool bServer, PBLifeSkillScroll* pScroll );
	void CreateTlvPB( bool bServer, PBLifeSkillScroll* pScroll );
	int Initialize();
	CTplItemLifeSkillScroll()
	{
		Initialize();
	}
	~CTplItemLifeSkillScroll() {}
};	
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** // 

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ���۱�			## ģ������
// version	= 1					## �汾��
// path		= Config/���۱�		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //

class CTemplateOpenSlot : public CTemplate
{
public:

	// FieldName: �򿪵�1������Ҫ�ĵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: �򿪵�2������Ҫ�ĵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: �򿪵�3������Ҫ�ĵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: �򿪵�4������Ҫ�ĵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: �򿪵�5������Ҫ�ĵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	int		mSlotLevel[ 5 ];

	// FieldName: �򿪵�1������Ҫ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: �򿪵�2������Ҫ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: �򿪵�3������Ҫ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: �򿪵�4������Ҫ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: �򿪵�5������Ҫ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	int		mSlotNumber[ 5 ];

public:
	void SetFromPB( bool bServer, PBOpenSlot* pSlot );
	void CreateTlvPB( bool bServer, PBOpenSlot* pSlot );
	int Initialize();
	CTemplateOpenSlot()
	{
		Initialize();
	}
	~CTemplateOpenSlot() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �ϳ�				## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/�ϳ�			## ·��
// parent	=					## ����ģ��
// ********************************************************************** //

class CTemplateCompose : public CTemplate 
{
public:

	// FieldName: �ϳ���Ҫ�Ĳ���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	int		mMaterialID;

	// FieldName: �ϳ���Ҫ�Ĳ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	int		mMaterialNum;

	// FieldName: �ϳɵõ�����ƷID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	int		mItemID;

	// FieldName: �ϳɵõ�����Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	int		mItemNum;

public:
	void SetFromPB( bool bServer, PBCompose* pCompose );
	void CreateTlvPB( bool bServer, PBCompose* pCompose );
	int Initialize();
	CTemplateCompose() 
	{
		Initialize();
	}
	~CTemplateCompose() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ���Ӻϳ�			## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/���Ӻϳ�		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //  

enum EM_LIFESKILL	
{	
	LIFESKILL_NONE			= 0,	// �������
	LIFESKILL_COLLECT		= 1,	// �ɼ�����
	LIFESKILL_GOLDMAKE		= 2,	// ���	
	LIFESKILL_ARTIFICER		= 3,	// �ɽ�
	LIFESKILL_PILLMAKER		= 4,	// ����
	LIFESKILL_KOOKER		= 5,	// ���
	LIFESKILL_MAILSKILL		= 6,	// ���޼���
	LIFESKILL_SUBSKILL		= 7,	// ���޼���
};
	

class CTemplateMultiCompose : public CTemplate
{
public:
	enum EM_LifSkillKind
	{		
		SKILLKIND_COLLECT_STONE				=	1,	// �ɼ�ְҵ�Ľ�ʯ�䷽
		SKILLKIND_COLLECT_MAKER				=	2,	// �ɼ�ְҵ��֯���䷽
		SKILLKIND_PILLMAKER_HPITEM			=	3,	// ����ְҵ������ҩ���䷽
		SKILLKIND_PILLMAKER_MPITEM			=	4,	// ����ְҵ��ħ��ҩ���䷽		
		SKILLKIND_PILLMAKER_BUFFITEM		=	5,	// ����ְҵ��BUFFҩ���䷽
		SKILLKIND_PILLMAKER_SPECIALITEM		=	6,	// ����ְҵ������ҩ���䷽					
		SKILLKIND_ARTIFICER_KITBAG			=	7,	// �ɽ�ְҵ�ı��������䷽
		SKILLKIND_ARTIFICER_MAGICPAPER		=	8,	// �ɽ�ְҵ�ķ��������䷽
		SKILLKIND_ARTIFICER_SPECIALITEM		=	9,	// �ɽ�ְҵ��������Ʒ�����䷽
		SKILLKIND_GOLDMAKE_HEAD				=	10, // ���ְҵ�Ļ�ͷ����ʯ�����䷽
		SKILLKIND_GOLDMAKE_RING				=	11, // ���ְҵ�Ľ�ָ����ʯ�����䷽
		SKILLKIND_GOLDMAKE_CUFF				=	12, // ���ְҵ�Ļ�������ʯ�����䷽
		SKILLKIND_GOLDMAKE_WEAPON			=	13,	// ���ְҵ����������ʯ�����䷽			
		SKILLKIND_GOLDMAKE_CHEST			=	14,	// ���ְҵ�Ļ�������ʯ�����䷽	
		SKILLKIND_GOLDMAKE_LEG				=	15,	// ���ְҵ�Ļ�������ʯ�����䷽							
		SKILLKIND_GOLDMAKE_NECK				=	16,	// ���ְҵ����������ʯ�����䷽													
		SKILLKIND_GOLDMAKE_SASH				=	17,	// ���ְҵ����������ʯ�����䷽															
		SKILLKIND_GOLDMAKE_CHARM			=	18,	// ���ְҵ�Ļ�������ʯ�����䷽																	
		SKILLKIND_GOLDMAKE_BALL				=	19,	// ���ְҵ�ķ�������ʯ�����䷽																			
		SKILLKIND_GOLDMAKE_CLOAK			=	20,	// ���ְҵ����������ʯ�����䷽																							
		SKILLKIND_GOLDMAKE_FASHION			=	21,	// ���ְҵ��ʱװ����ʯ�����䷽
		SKILLKIND_GOLDMAKE_OTHER			=	22,	// ���ְҵ�������ʯ�����䷽																											
		SKILLKIND_KOOKER_COOLMAKE			=	23,	// ���ְҵ����������Ʒ�����䷽
		SKILLKIND_KOOKER_BOIL				=	24,	// ���ְҵ��������Ʒ�����䷽
		SKILLKIND_KOOKER_DRYBYFIRE			=	25,	// ���ְҵ�ĳ�����Ʒ�����䷽
		SKILLKIND_KOOKER_FRY				=	26,	// ���ְҵ��ը����Ʒ�����䷽
		SKILLKIND_KOOKER_VAPORIZE			=	27,	// ���ְҵ��������Ʒ�����䷽
	};	
	  
	enum EM_ComposeType
	{
		COMPOSETYPE_CARDEXCHANGE		=	0,			// ��Ƭ�һ��䷽
		COMPOSETYPE_LIFESKILL			=	1,			// ������䷽		
		COMPOSETYPE_EQUIPMENTCHANGE		=	2,			// װ���һ�
		COMPOSETYPE_FAMILYEXCHANGE		=	3,			// ����һ�
		COMPOSETYPE_CORPSEXCHANGE		=	4,			// ���Ŷһ�
		COMPOSETYPE_MARRIAGEEXCHANGE	=	5,			// ���������һ�		
		COMPOSETYPE_EQUIPUPGRADE		=	6,			// װ������
		COMPOSETYPE_USEVALUES			=	7,			// ����ֵ�һ�
	}; 	

	// �һ���Ҫ����ֵ����
	enum EM_NeedValueType
	{
		NEEDVALUETYPE_NONE				= 0,		// ����Ҫ
		NEEDVALUETYPE_CHARM				= 1,		// ����ֵ
		NEEDVALUETYPE_SLAVE				= 2,		// ��Եֵ
		NEEDVALUETYPE_MASTER			= 3,		// ʦ��ֵ
		NEEDVALUETYPE_LASTONE			= 4,		// ���Ҷ�����ֵ
		NEEDVALUETYPE_MARRYINTIMACY		= 5,		// ����֮������ܶ�
		NEEDVALUETYPE_SWORNINTIMACY		= 6,		// ��ݳ�Ա�����ܶ�
	};

public:	
	class CDegreeInfo	
	{	
	public:							
		int		mValue;			// ��ұ�����������Ҫ��������ȵĲ�ֵ
		int		mProbality;		// �ڲ�ֵ��Χ�ڻ�ȡ�����ȵĸ���
		int		mDegreeValue;	// �ڲ�ֵ��Χ�ڻ�ȡ�����ȵ�ֵ
	};		
		
public:
	
	// FieldName: �ϳɱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	int		mOrder;

	// FieldName: $�ϳ�����
	// FieldType: STRING32
	// Type:	  EDITSTRING	

	char	mDescribe[ STRING32 ];
	
	// FieldName: �䷽����
	// FieldType: INT4
	// Type:	  COMBOENUM(EM_ComposeType)
	int		mComposeType;

	// FieldName: �ϳ���Ҫ�Ĳ���ID%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000) 
	int		mMaterialID[ 10 ];	   	

	// FieldName: �ϳ���Ҫ�Ĳ�������%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	int		mMaterialNum[ 10 ];

	// FieldName: �ϳ���Ҫ����ֵ����%d
	// FieldType: INT4
	// Type:	  COMBOENUM(EM_NeedValueType)
	int		mNeedValueType[ 10 ];	   	

	// FieldName: �ϳ���Ҫ����ֵ%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	int		mNeedValue[ 10 ];

	// FieldName: �ϳɵõ�����ƷID%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	int		mItemID[ 10 ];

	// FieldName: �ϳɵõ�����Ʒ����%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	int		mItemNum[ 10 ];

	// FieldName: �ϳɵõ��ľ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mExp;  	 			
	
	// FieldName: �ϳɵõ�����Ʒ�ĸ���%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mItemProbability[ 10 ];
	
	// FieldName: ���������
	// FieldType: INT4
	// Type:	  COMBOENUM(EM_LIFESKILL)
	int		mLifeSkillType;
	
	// FieldName: ����������ļ�������
	// FieldType: INT4
	// Type:	  COMBOENUM(EM_LifSkillKind)
	int		mSkillKind;	  
	
	// FieldName: ѧϰ������䷽��Ҫ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mSpecializedDegree; 	
	
	// FieldName: �����������
	// FieldType: INT4
	// Type:	  CHECKMUTI(npc��ѧϰ���䷽,�����о����ɵ��䷽,ͨ������ѧϰ���䷽)
	int		mLifeComposeType;
	
	// FieldName: ��������䷽��������Ļ���
	// FieldType: INT4
	// Type:	   EDITNUMBER(0,100000000)
	int		mCreatValue;	
	
	// FieldName: ѧϰ��������䷽����Ľ�Ǯ
	// FieldType: INT4
	// Type:	   EDITNUMBER(0,100000000)
	int		mStudyMoney;		
	
	// FieldName: �������䷽��ȡ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mSkillCreatDegree;
	
	// FieldName: ���������Ⱥ��䷽��Ҫ�������ȵĵ�%d����ֵ����
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,10000) 


	// FieldName: ���������Ⱥ��䷽��Ҫ�������ȵĵ�%d����ֵ����Ļ�ȡ�����ȵĸ���
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,10000) 


	// FieldName: ���������Ⱥ��䷽��Ҫ�������ȵĵ�%d����ֵ����Ļ�ȡ�����ȵ�ֵ
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,10000) 

	CDegreeInfo mDegreeInfo[MAX_LIFESKILL_DEGREESTEP];
	
	// FieldName: ÿ��ʹ���䷽��Ҫ���ĵ�APֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)		
	int		mApNeedCost;	
	
	// FieldName: �䷽��ʹ�ô���(-1��ʾû�д�������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,10000)		
	int		mUsedTimes;		
	
	// FieldName: ��ֵ��С��Χ( �����䷽ʱ���ֵ��ģ��ֵ���õĻ��ֵС�ڸ�ֵʱ���㴴��ɹ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)		
	int		mMinValue;	
	// FieldName: Դװ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mSrcEquipID;

	// FieldName: ����װ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mDesEquipID;
		
	// FieldName: �ϳ���Ҫ�Ĺ��׶�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000) 	
	int		mContribute;

	// FieldName: %d�������������ƷID%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mUpgItemID[ 20 ][ 3 ];

	// FieldName: %d�����������Ʒ����%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mUpgItemNum[ 20 ][ 3 ];
		
public:
	void SetFromPB( bool bServer, PBMultiCompose* pCompose );
	void CreateTlvPB( bool bServer, PBMultiCompose* pCompose );
	int Initialize();
	CTemplateMultiCompose()
	{
		Initialize();
	}
	~CTemplateMultiCompose() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ���ͱ�			## ģ������
// version	= 1					## �汾��
// path		= Config/���ͱ�		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //

class CTemplateTeleTable : public CTemplate
{
public:


	// FieldName: ���ͼID%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	int		mLineID[ 20 ];

	// FieldName: ������ͼID%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	int		mMapID[ 20 ];

	// FieldName: X����%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)	

	int		mPosX[ 20 ];

	// FieldName: Y����%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	int		mPosY[ 20 ];

	// FieldName: $����%d
	// FieldType: STRING32
	// Type:	  EDITSTRING	

	char		mDes[ 20 ][ STRING32 ];	

	// FieldName: ����%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)	
	int		mFee[ 20 ];

	// FieldName: ������Ʒ%d
	// FieldType: INT4
	// Type:		EDITNUMBER(0,100000)
	int			mNeedTempID[ 20 ];

	// FieldName: ����buff%d
	// FieldType: INT4
	// Type:		EDITNUMBER(0,100000)
	int			mNeedBuffID[ 20 ];

	// FieldName: ����ȼ�%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	int			mNeedLevel[ 20 ];

public:
	void SetFromPB( bool bServer, PBTeleTable* pTable );
	void CreateTlvPB( bool bServer, PBTeleTable* pTable );
	int Initialize();
	CTemplateTeleTable() 
	{
		Initialize();
	}
	~CTemplateTeleTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��ֵ������		## ģ������
// version	= 1					## �汾��
// path		= Config/��ֵ������	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateData : public CTemplate
{
public:

	// FieldName: ���������1��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������2��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������3��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������4��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������5��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������6��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������7��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������8��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������9��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������10��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������11��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������12��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������13��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������14��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������15��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������16��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������17��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������18��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������19��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������20��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������21��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������22��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������23��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������24��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������25��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������26��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������27��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������28��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������29��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������30��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������31��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������32��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������33��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������34��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������35��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������36��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������37��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������38��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������39��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������40��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������41��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������42��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������43��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������44��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������45��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������46��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������47��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������48��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������49��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������50��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������51��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������52��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������53��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������54��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������55��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������56��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������57��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������58��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������59��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������60��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������61��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������62��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������63��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������64��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������65��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������66��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������67��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������68��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������69��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������70��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������71��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������72��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������73��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������74��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������75��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������76��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������77��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������78��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������79��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������80��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������81��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������82��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������83��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������84��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������85��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������86��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������87��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������88��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������89��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������90��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������91��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������92��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������93��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������94��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������95��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������96��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������97��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������98��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������99��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: ���������100��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)
	int		mLevelFix[ 100 ];

	// FieldName: �������1�ĵ�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: �������2�ĵ�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: �������3�ĵ�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: �������4�ĵ�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: �������5�ĵ�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: �������6�ĵ�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: �������7�ĵ�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: �������8�ĵ�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: �������9�ĵ�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)

	// FieldName: �������10�ĵ�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)
	int		mTeamFix[ 10 ];
	
public:
	void SetFromPB( bool bServer, PBData* pData );
	void CreateTlvPB( bool bServer, PBData* pData );
	int Initialize();
	CTemplateData()
	{
		Initialize();
	}
	~CTemplateData() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �ٻ���			## ģ������
// version	= 1					## �汾��
// path		= �ٻ���			## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateSummonBeast : public CTemplate
{
public:
	enum COLOR_TYPE
	{
		EM_COLOR_TYPE_WHITE = 0,	// RGB(255,255,255)
		EM_COLOR_TYPE_GREEN = 1,		// RGB(109,207,246)
		EM_COLOR_TYPE_BULE  = 2,			// RGB(0,0,255)
	};

	enum ATTACK_TYPE
	{
		EM_ATTACK_TYPE_PHY = 1,		// ������
		EM_ATTACK_TYPE_MGC = 2,			// ��������
	};

	enum
	{
		PET_LEVEL_ONE = 0,
		PET_LEVEL_TWO = 1,
		PET_LEVEL_THREE = 2,
	};

	class CPetData
	{
	public:
		// �ٻ���������ɫ
		COLOR_TYPE mNameColor;
		// �ٻ��޹�������
		ATTACK_TYPE mAttackType;
		// �ٻ���������������
		int mPAttackUp;
		// �ٻ���������������
		int mPAttackLow;
		// �ٻ��޷�������������
		int mMAttackUp;
		// �ٻ��޷�������������
		int mMAttackLow;
		// �ٻ����ƶ��ٶ�
		int mSpeed;
		// �ٻ����������
		int mPDefence;
		// �ٻ��޷�������
		int mMDefence;
		// �ٻ����������
		int mPReducePer;
		// �ٻ��޷�������
		int mMReducePer;
		// �ٻ���HP����
		int mMaxHP;
		// �ٻ���HP�ָ�����
		int mHPRSpeed;
		// �ٻ�����������
		int mDeathRate;
		// �ٻ��������˺�
		int mDeathValue;
		// �ٻ�����������
		int mDeathDefense;
		// �ٻ����չ�����ֵ
		int mNormalDuck;
		// �ٻ��޼�������ֵ
		int mSkillDuck;
		// �ٻ��޺�������ֵ
		int mIgnoreDuck;
		// �ٻ��޼���ID
		int mSkillID;
		// �ٻ��޼��ܵȼ�
		int mSkillLevel;
		// �ٻ�����������Χ
		int mPAttackRange;
		// �ٻ��޷���������Χ
		int mMAttackRange;
		// ����
		int mResDef[ 6 ];
		// ���Թ���
		int mResAtt[ 6 ];
		// �����ӳ�
		int mAttPercent;
		// �����ӳ�
		int mDefPercent;
		// �����ӳ�
		int mHPPercent;
	};
public:

	// FieldName: $��Ϸ�е���ʾ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mName[ STRING32 ];			

	// FieldName: ģ��·��
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mModel[ STRING32 ];	

	// FieldName: �ٻ��޵ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,160)
	int		mLevel;
	
	// FieldName: ����1������ʱ��(��λ������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1200000)

	// FieldName: ����2������ʱ��(��λ������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1200000)

	// FieldName: ����3������ʱ��(��λ������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1200000)
	int		mLevelUpDelayTime[ 3 ];

	// FieldName: 1���ٻ���������ɫ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��ɫ=0,��ɫ,��ɫ)

	// FieldName: 1���ٻ��޹�������
	// FieldType: INT4
	// Type:	  COMBOENUM(ATTACK_TYPE)

	// FieldName: 1���ٻ���������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 1���ٻ���������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 1���ٻ��޷�������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 1���ٻ��޷�������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 1���ٻ����ƶ��ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: 1���ٻ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 1���ٻ��޷�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 1���ٻ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 1���ٻ��޷�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 1���ٻ���HP����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: 1���ٻ���HP�ָ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ��������˺�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: 1���ٻ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 1���ٻ����չ�����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: 1���ٻ��޼��ܲ�Ӱֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: 1���ٻ��޺�������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: 1���ٻ��޼���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: 1���ٻ��޼��ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: 1���ٻ�����������Χ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,15)

	// FieldName: 1���ٻ��޷���������Χ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,15)

	// FieldName: 1���ٻ��޿���0
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ��޿���1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ��޿���2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ��޿���3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ��޿���4
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ��޿���5
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ������Թ���0
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ������Թ���1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ������Թ���2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ������Թ���3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ������Թ���4
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ������Թ���5
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 1���ٻ��޹����ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: 1���ٻ��޷����ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: 1���ٻ��������ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: 2���ٻ���������ɫ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��ɫ=0,��ɫ,��ɫ)

	// FieldName: 2���ٻ��޹�������
	// FieldType: INT4
	// Type:	  COMBOENUM(ATTACK_TYPE)

	// FieldName: 2���ٻ���������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 2���ٻ���������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 2���ٻ��޷�������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 2���ٻ��޷�������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 2���ٻ����ƶ��ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: 2���ٻ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 2���ٻ��޷�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 2���ٻ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 2���ٻ��޷�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 2���ٻ���HP����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: 2���ٻ���HP�ָ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ��������˺�
	// FieldType: INT4
	// Type:	 EDITNUMBER(0,1000000)

	// FieldName: 2���ٻ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 2���ٻ����չ�����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: 2���ٻ��޼��ܲ�Ӱֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: 2���ٻ��޺�������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: 2���ٻ��޼���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: 2���ٻ��޼��ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: 2���ٻ�����������Χ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,15)

	// FieldName: 2���ٻ��޷���������Χ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,15)

	// FieldName: 2���ٻ��޿���0
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ��޿���1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ��޿���2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ��޿���3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ��޿���4
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ��޿���5
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ������Թ���0
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ������Թ���1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ������Թ���2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ������Թ���3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ������Թ���4
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ������Թ���5
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 2���ٻ��޹����ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: 2���ٻ��޷����ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: 2���ٻ��������ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: 3���ٻ���������ɫ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��ɫ=0,��ɫ,��ɫ)

	// FieldName: 3���ٻ��޹�������
	// FieldType: INT4
	// Type:	  COMBOENUM(ATTACK_TYPE)

	// FieldName: 3���ٻ���������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 3���ٻ���������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 3���ٻ��޷�������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 3���ٻ��޷�������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 3���ٻ����ƶ��ٶ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: 3���ٻ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 3���ٻ��޷�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 3���ٻ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 3���ٻ��޷�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 3���ٻ���HP����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: 3���ٻ���HP�ָ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ��������˺�
	// FieldType: INT4
	// Type:	 EDITNUMBER(0,1000000)

	// FieldName: 3���ٻ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,9999)

	// FieldName: 3���ٻ����չ�����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: 3���ٻ��޼��ܲ�Ӱֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: 3���ٻ��޺�������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: 3���ٻ��޼���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: 3���ٻ��޼��ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: 3���ٻ�����������Χ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,15)

	// FieldName: 3���ٻ��޷���������Χ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,15)

	// FieldName: 3���ٻ��޿���0
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ��޿���1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ��޿���2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ��޿���3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ��޿���4
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ��޿���5
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ������Թ���0
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ������Թ���1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ������Թ���2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ������Թ���3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ������Թ���4
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ������Թ���5
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: 3���ٻ��޹����ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: 3���ٻ��޷����ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: 3���ٻ��������ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	CPetData mPetData[ 3 ];

	// FieldName: �ٻ��޹���Ƶ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int mAttackFrequency;

public:
	void SetFromPB( bool bServer, PBSummonBeast* pBeast );
	void CreateTlvPB( bool bServer, PBSummonBeast* pBeast );
	int Initialize();
	CTemplateSummonBeast() 
	{
		Initialize();
	}
	~CTemplateSummonBeast() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��������				## ģ������
// version	= 1					## �汾��
// path		= Config/��������			## ·��
// parent	=					## ����ģ��
// ********************************************************************** //

class CTemplateBeginner : public CTemplate
{
public:

	// FieldName: ������ƷID1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ������ƷID2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ������ƷID3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mEquipItemID[ 3 ];

	// FieldName: ������Ʒ����1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ������Ʒ����2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ������Ʒ����3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mEquipItemNum[ 3 ];

	// FieldName: ������ƷID1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ������ƷID2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ������ƷID3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mBaggageItemID[ 3 ];

	// FieldName: ������Ʒ����1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ������Ʒ����2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	// FieldName: ������Ʒ����3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mBaggageItemNum[ 3 ];

	// FieldName: ����ID1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ����ID2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ����ID3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mSkillID[ 3 ];

	// FieldName: ���ܵȼ�1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ���ܵȼ�2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)

	// FieldName: ���ܵȼ�3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mSkillLevel[ 3 ];

	// FieldName: ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mStrNum;

	// FieldName: ���ʵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mConNum;

	// FieldName: ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mStaNum;

	// FieldName: ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mWisNum;

	// FieldName: �����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mSprNum;

	// FieldName: ���ܵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mSkillNum;

	// FieldName: ����X����1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mPosX1;

	// FieldName: ����X����2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mPosX2;

	// FieldName: ����Y����1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mPosY1;

	// FieldName: ����Y����2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mPosY2;

	// FieldName: תսʿ��1���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: תսʿ��2���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: תսʿ��3���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	int mSkillID1[ 3 ];

	// FieldName: תսʿ��1���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: תսʿ��2���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: תսʿ��3���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	int mSkillLevel1[ 3 ];

	// FieldName: ת���͵�1���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ת���͵�2���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ת���͵�3���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	int mSkillID2[ 3 ];

	// FieldName: ת���͵�1���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ת���͵�2���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ת���͵�3���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	int mSkillLevel2[ 3 ];

	// FieldName: ת���˵�1���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ת���˵�2���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ת���˵�3���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	int mSkillID3[ 3 ];

	// FieldName: ת���˵�1���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ת���˵�2���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ת���˵�3���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	int mSkillLevel3[ 3 ];

	// FieldName: ת��ʦ��1���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ת��ʦ��2���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ת��ʦ��3���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	int mSkillID4[ 3 ];

	// FieldName: ת��ʦ��1���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ת��ʦ��2���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ת��ʦ��3���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	int mSkillLevel4[ 3 ];

	// FieldName: ת��ʿ��1���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ת��ʿ��2���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ת��ʿ��3���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	int mSkillID5[ 3 ];

	// FieldName: ת��ʿ��1���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ת��ʿ��2���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ת��ʿ��3���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	int mSkillLevel5[ 3 ];

	// FieldName: ת����ʦ��1���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ת����ʦ��2���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ת����ʦ��3���ʼ����
	// FieldType: INT4
	// Type:	  SKILLPATH

	int mSkillID6[ 3 ];

	// FieldName: ת����ʦ��1���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ת����ʦ��2���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	// FieldName: ת����ʦ��3���ʼ���ܵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,50)

	int mSkillLevel6[ 3 ];

	// FieldName: ���ֱ����ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,160)
	int mBeginnerProtectLevel;

	// FieldName: �糡������ʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,3600000)
	int mTransProtectTime;

	// FieldName: ������ͼ
	// FieldType: INT4
	// Type:	  EDITNUMBER(1,50)
	int mMapID;

	// FieldName: �������ʱװ�������;ö�ռװ��ȫ���;öȵ���ֱ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int mDeathDuraRate;	

	// FieldName: ����װ��ʱ�Ƿ���ʹ�ð󶨽�Ǯ(0��ʾ����1��ʾ������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1)
	int mCanMendUseBindMoney;	

	// FieldName: ����ʱ����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mBeginnerAP;
public:
	void SetFromPB( bool bServer, PBBeginner* pBeginner );
	void CreateTlvPB( bool bServer, PBBeginner* pBeginner );
	int Initialize();
	CTemplateBeginner() 
	{
		Initialize();
	}
	~CTemplateBeginner() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ��������˳��	## ģ������
// version	= 1				## �汾��
// path		= Config/��������˳��	## ·��
// parent	=				## ����ģ��
// ********************************************************************** //

class CItemSequence : public CTemplate 
{
public:

	// FieldName: ��������%d
	// FieldType: INT4
	// Type:	  COMBOENUM(ITEMTYPE)
	int mSequence[20];	

public:
	void SetFromPB( bool bServer, PBItemSequence* pItem );
	void CreateTlvPB( bool bServer, PBItemSequence* pItem );
	int Initialize();
	CItemSequence() 
	{
		Initialize();
	}
	~CItemSequence() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ����ȼ�			## ģ������
// version	= 1					## �汾��
// path		= Config/����ȼ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //

class CTemplateDropLevel : public CTemplate
{
public:

	// FieldName: ��д%d����%d�ĸ���
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000)
	int     mRan[ 16 ][ 16 ];
	
public:
	void SetFromPB( bool bServer, PBDropLevel* pLevel );
	void CreateTlvPB( bool bServer, PBDropLevel* pLevel );
	int Initialize();
	CTemplateDropLevel()
	{
		Initialize();
	}
	~CTemplateDropLevel() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ����ת����			## ģ������
// version	= 1						## �汾��
// path		= Config/����ת����		## ·��
// parent	=						## ����ģ��
// ********************************************************************** //

class CTemplateOgreTran : public CTemplate
{
public:

	// FieldName: ��%d���ĵ����
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mDrop[ TMP_MAX_GRADE ];

	// FieldName: ��%d����HP
	// FieldType: INT4
	// Type:      EDITNUMBER(0,1000000000)
	int     mHP[ TMP_MAX_GRADE ];

	// FieldName: ��%d����MP
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mMP[ TMP_MAX_GRADE ];

	// FieldName: ��%d�����﹥
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mPA[ TMP_MAX_GRADE ];

	// FieldName: ��%d���ķ���
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mMA[ TMP_MAX_GRADE ];

	// FieldName: ��%d�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mPD[ TMP_MAX_GRADE ];

	// FieldName: ��%d���ķ���
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mMD[ TMP_MAX_GRADE ];

	// FieldName: ��%d��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mHit[ TMP_MAX_GRADE ];

	// FieldName: ��%d���Ĳ�Ӱ
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mDodge[ TMP_MAX_GRADE ];

	// FieldName: ��%d���ĺ���
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mIgnore[ TMP_MAX_GRADE ];

	// FieldName: ��%d���ı���
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mDeath[ TMP_MAX_GRADE ];

	// FieldName: ��%d���Ĺ���%d
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mResAtt[ TMP_MAX_GRADE ][ 7 ];	

	// FieldName: ��%d���Ŀ���%d
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mResDef[ TMP_MAX_GRADE ][ 7 ];	

	// FieldName: ��%d���ľ���
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int     mExp[ TMP_MAX_GRADE ];

public:
	void SetFromPB( bool bServer, PBOgreTran* pOgre );
	void CreateTlvPB( bool bServer, PBOgreTran* pOgre );
	int Initialize();
	CTemplateOgreTran() 
	{
		Initialize();
	}
	~CTemplateOgreTran() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= (ְҵ)���Ա�			## ģ������
// version	= 1						## �汾��
// path		= Config/(ְҵ)���Ա�	## ·��
// parent	=						## ����ģ��
// ********************************************************************** //

class CTemplateMetierProperty : public CTemplate
{
public:

	// FieldName: ְҵ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����=0,սʿ,����,����,��ʦ,��ʿ,����ʦ,����)
	int		mMetierRequire;

	// FieldName: ����ѡ��
	// FieldType: INT4
	// Type:	  CHECKMUTI(��ǰ����=0,��ǰ��ֵ)
	int		mOption;

	// FieldName: ��д�ȼ�%d��Ӧ��%d�����Ե�ֵ
	// FieldType: INT4
	// Type:      EDITNUMBER(0,99999)
	int     mMetierProperty[ TMP_MAX_GRADE ][ MAX_PROPERTY ];

public:
	void SetFromPB( bool bServer, PBMetierPro* pMetier );
	void CreateTlvPB( bool bServer, PBMetierPro* pMetier );
	int Initialize();
	CTemplateMetierProperty()
	{
		Initialize();
	}
	~CTemplateMetierProperty() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= (�ȼ�)���Ա�			## ģ������
// version	= 1						## �汾��
// path		= Config/(�ȼ�)���Ա�	## ·��
// parent	=						## ����ģ��
// ********************************************************************** //

class CTemplateLevelProperty : public CTemplate
{
public:

	// FieldName: ����ѡ��
	// FieldType: INT4
	// Type:	  CHECKMUTI(��ǰ����=0,��ǰ��ֵ)
	int		mOption;

	// FieldName: �ȼ�%d��Ӧ������ֵ
	// FieldType: INT4
	// Type:      EDITNUMBER(0,99999)
	int     mLevelProperty[ TMP_MAX_GRADE ];

public:
	void SetFromPB( bool bServer, PBLevelProperty* pLevel );
	void CreateTlvPB( bool bServer, PBLevelProperty* pLevel );
	int Initialize();
	CTemplateLevelProperty()
	{
		Initialize();
	}
	~CTemplateLevelProperty() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ��ѫ�����			## ģ������
// version	= 1						## �汾��
// path		= Config/��ѫ�����		## ·��
// parent	=						## ����ģ��
// ********************************************************************** //
class CTemplateHonorToExp : public CTemplate
{
public:

	// FieldName: �ȼ�%d�õ��ľ���ֵ
	// FieldType: INT4
	// Type:      EDITNUMBER(0,9999999)
	int     mExp[ TMP_MAX_GRADE ];

	// FieldName: �ȼ�%d�õ��ĲŻ�ֵ
	// FieldType: INT4
	// Type:      EDITNUMBER(0,9999999)
	int     mWizard[ MAX_WIZARD_TEMP ];

	// FieldName: ÿ�նһ��������������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,9999999)
	int		mExpLimit;

	// FieldName: �һ��õ�����Ʒ
	// FieldType: INT4
	// Type:      EDITNUMBER(0,9999999)
	int		mItemID;

	// FieldName: �һ���Ʒ��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,9999999)
	int		mItemHonor;

	// FieldName: ÿ�նһ���Ʒ����������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,9999999)
	int		mItemLimit;

public:
	void SetFromPB( bool bServer, PBHonorToExp* pHonor );
	void CreateTlvPB( bool bServer, PBHonorToExp* pHonor );
	int Initialize();
	CTemplateHonorToExp()
	{
		Initialize();
	}
	~CTemplateHonorToExp(){}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ��ѫ��ñ�			## ģ������
// version	= 1						## �汾��
// path		= Config/��ѫ��ñ�		## ·��
// parent	=						## ����ģ��
// ********************************************************************** //
class CTemplateHonorObtain : public CTemplate
{
public:

	// FieldName: ���ѫ����
	// FieldType: INT4
	// Type:      EDITNUMBER(0,999999999)
	int     mInLimit;

	// FieldName: ÿ�����ṩ�Ĺ�ѫ����
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,9999999)
	int     mOutLimit;

	// FieldName: ����������õ��Ĺ�ѫ
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,99999)
	int     mOutDieExp;

	// FieldName: �ڱ��������õ��Ĺ�ѫ
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,99999)
	int     mInDieExp;

	// FieldName: �����������õ��Ĺ�ѫ
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,99999)
	int     mBorderDieExp;

	// FieldName: �ȼ�����Ŀ��%d������õ��Ĺ�ѫ
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,99999)
	int     mOutLowExp[ TMP_MAX_GRADE ];

	// FieldName: �ȼ�����Ŀ��%d������õ��Ĺ�ѫ
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,99999)
	int     mOutHighExp[ TMP_MAX_GRADE ];

	// FieldName: �ȼ�����Ŀ��%d�ڱ����õ��Ĺ�ѫ
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,99999)
	int     mInLowExp[ TMP_MAX_GRADE ];

	// FieldName: �ȼ�����Ŀ��%d�ڱ����õ��Ĺ�ѫ
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,99999)
	int     mInHighExp[ TMP_MAX_GRADE ];

	// FieldName: �ȼ�����Ŀ��%d�������õ��Ĺ�ѫ
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,99999)
	int     mBorderLowExp[ TMP_MAX_GRADE ];

	// FieldName: �ȼ�����Ŀ��%d�������õ��Ĺ�ѫ
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,99999)
	int     mBorderHighExp[ TMP_MAX_GRADE ];

	// FieldName: �ȼ�����Ŀ��%d��ʧ�Ĺ�ѫ
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,99999)
	int     mLostLowExp[ TMP_MAX_GRADE ];

	// FieldName: �ȼ�����Ŀ��%d��ʧ�Ĺ�ѫ
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,99999)
	int     mLostHighExp[ TMP_MAX_GRADE ];

	// FieldName: %d��������ѫ
	// FieldType: INT4
	// Type:      EDITNUMBER(-99999,99999)
	int     mBasicExp[ TMP_MAX_GRADE ];

public:
	void SetFromPB( bool bServer, PBHonorObtain* pObtain );
	void CreateTlvPB( bool bServer, PBHonorObtain* pObtain );
	int Initialize();
	CTemplateHonorObtain()
	{
		Initialize();
	}
	~CTemplateHonorObtain() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ˫��ʱ���			## ģ������
// version	= 1						## �汾��
// path		= Config/˫��ʱ���	 ## ·��
// parent	=						## ����ģ��
// ********************************************************************** //

class CTemplateDiploidTimeTable : public CTemplate
{
public:

	// FieldName: ÿ�ܿ���ȡ��ʱ��(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mTotalTime;

	// FieldName: ��ȡ��ʽ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int mTypeNumber;

	// FieldName: ��Ч˫������(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mValidMax;

	// FieldName: ���Сʱ(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000) 

	// FieldName: 1��Сʱ(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: 2��Сʱ(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: 3��Сʱ(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: 4��Сʱ(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	int mBuffID[ 5 ];

public:
	void SetFromPB( bool bServer, PBDiploidTable* pTable );
	void CreateTlvPB( bool bServer, PBDiploidTable* pTable );
	int Initialize();
	CTemplateDiploidTimeTable()
	{
		Initialize();
	}
	~CTemplateDiploidTimeTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= �ڵ�					 ## ģ������
// version	= 1						 ## �汾��
// path		= �ڵ�					 ## ·��
// parent	= ���߻�����Ϣ			 ## ����ģ��
// ********************************************************************** //
class CTplRedStone: public CTplItem
{
public:
	enum ERedStoneType
	{
		TYPE_TEAM				=	1,		//	�����ڵ�
		TYPE_FAMILY				=	2,		//	�����ڵ�
		TYPE_FAMILYREPETION		=	3,		//	���帱���ڵ�
		TYPE_CAMP				=	4,		//	��Ӫ�ڵ�
		TYPE_COUNTRY			=	5,		//	�����ڵ�
		TYPE_MARRIAGE			=	6,		//  ����ڵ�
		TYPE_SERVER				=	7,		//	ȫ���ڵ�
		TYPE_METIER				=	8,		//  �����ڵ�			
	};	
	
	// FieldName: ����ͼ������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mMagicIconName[ STRING32 ];			
		
	// FieldName: ���������Ľ�����ʱ��(����)
	// FieldType: INT4
	// Type:      EDITNUMBER(0,100000)
	unsigned int   mGuageTime;

	// FieldName: ������ʱ��(����)
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	unsigned int   mMagicSustainTime;

	// FieldName:  ����ʱ���侭���ʱ����(����)
	// FieldType: INT4
	// Type:      EDITNUMBER(0,100000)
	unsigned int   mExpTime;

	// FieldName:  ����ʱ�����ð뾶
	// FieldType: INT4
	// Type:      EDITNUMBER(0,100000)
	unsigned int   mRadius;
	
	// FieldName: �ڵ�����
	// FieldType: INT4
	// Type:      COMBOENUM(ERedStoneType)
	unsigned int   mRedStoneType;
	
	// FieldName:  �����ڵ��ľ���ӳ�
	// FieldType: INT4
	// Type:      EDITNUMBER(0,100000)
	unsigned int   mFamilyExpRate;
	
	// FieldName: �ڵ������ID
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	unsigned int   mExpTableID;	  	

	// FieldName: �����Ƿ�Ӱ�쾭�����( 0 )
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	unsigned int   mNumberEffected;
	
	// FieldName: �ڵ�����������ID
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	unsigned int   mMetierID;

	// FieldName: ����ĵ�%d��buffid
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	unsigned int   mKeyBuffID[ 20 ];

	// FieldName: ��%d�ּӳ�buffid
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	unsigned int   mEncBuffID[ 20 ];

	// FieldName: ��%d�ּӳɰٷֱ�
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	unsigned int   mEncPercent[ 20 ];

	// FieldName: �Ƿ�������(����)
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��)
	unsigned int  mIsEternal;
public:
	void SetFromPB( bool bServer, PBRedStone* pStone );
	void CreateTlvPB( bool bServer, PBRedStone* pStone );
	int Initialize();
	CTplRedStone()
	{
		Initialize();
	}
	~CTplRedStone() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= ��Ʒ������			 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/��Ʒ������	 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTplItemAdapter : public CTemplate 
{
public:

	// FieldName: ģ������
	// FieldType: INT4
	// Type:	  COMBOENUM(ITEMTYPE)
	int		mItemType;		

	// FieldName: ��ʵ����
	// FieldType: INT4
	// Type:	  COMBOENUM(ADAPTERTYPE)
	int		mRealType;

	// FieldName: ��ʵģ��
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mRealTempID;

	// FieldName: ��Ч��������>����ȼ���(0��ʾ������)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,200)
	int		mMaxLevelMinus;

	// FieldName: ��Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mParam;

	// FieldName: ���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mMaxValue;

	// FieldName: ��Сֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mMinValue;
public:
	void SetFromPB( bool bServer, PBItemAdapter* pAdapter );
	void CreateTlvPB( bool bServer, PBItemAdapter* pAdapter );
	int Initialize();
	CTplItemAdapter() 
	{
		Initialize();
	}
	~CTplItemAdapter() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= �ڵ��ȼ������		 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/�ڵ��ȼ������	 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTemplateRedStoneExpTable : public CTemplate
{
public:

	// FieldName: ʹ���ڵ�ʱ%d�����ÿ�λ�õľ���ֵ
	// FieldType: INT4
	// Type:      EDITNUMBER(0,2100000000)
	unsigned int   mExp[ TMP_MAX_GRADE ];	

	// FieldName: ���������Ч����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		   mEffectName[ STRING32 ];

public:
	void SetFromPB( bool bServer, PBRedStoneExpTable* pTable );
	void CreateTlvPB( bool bServer, PBRedStoneExpTable* pTable );
	int Initialize();
	CTemplateRedStoneExpTable() 
	{
		Initialize();
	}
	~CTemplateRedStoneExpTable() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //






// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ����ѱ�			## ģ������
// version	= 1						## �汾��
// path		= Config/����ѱ�	## ·��
// parent	=						## ����ģ��
// ********************************************************************** //
class CTemplateReliveTable : public CTemplate
{
public:

	// FieldName: �ȼ�%d����ѽ�Ǯ��
	// FieldType: INT4
	// Type:      EDITNUMBER(0,99999999)
	int     mFee[ TMP_MAX_GRADE ];

	// FieldName: �����Ǯϵ��
	// FieldType: INT4
	// Type:      EDITNUMBER(0,99999999)
	int     mRate;

public:
	void SetFromPB( bool bServer, PBReliveTable* pTable );
	void CreateTlvPB( bool bServer, PBReliveTable* pTable );
	int Initialize();
	CTemplateReliveTable() 
	{
		Initialize();
	}
	~CTemplateReliveTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //




// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= ����ȼ������		 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/����ȼ������	 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTemplateQuestionExpTable : public CTemplate
{
public:

	
	// FieldName: ÿ�ո���npc������Ŀ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(1,100)
	int			  mNpcQuestionNum;			
	
	// FieldName:  ����ʱ�ȼ�Ϊ%d����һ�õľ���
	// FieldType: INT4
	// Type:      EDITNUMBER(0,100000)
	int   mExp[TMP_MAX_GRADE];	

	// FieldName: ÿ�ո�����Ŀ����ӳɱ���(��������Ķ��ٱ�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(1,100)
	int			mNpcExpAddRate;
	
public:
	void SetFromPB( bool bServer, PBQuestionExp* pExp );
	void CreateTlvPB( bool bServer, PBQuestionExp* pExp );
	int Initialize();
	CTemplateQuestionExpTable() 
	{
		Initialize();
	}
	~CTemplateQuestionExpTable() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= �󶨷��ñ�			 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/�󶨷��ñ�		 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTplBindChargeTable : public CTemplate
{
public:

	// FieldName: ��װ����Ҫ���ѵĽ�Ǯ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mMoneyBindNeed;	
	
	// FieldName: ��װ���Ƿ�֧�ְ󶨽�Ǯ 1��ʾ֧��0��ʾ��֧��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1)
	int			  mCanBindUseBM;	
	
	// FieldName: ȡ��װ������Ҫ�Ľ�Ǯ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mMoneyUnBindNeed;		
	
	// FieldName: ȡ��װ���Ƿ�֧�ְ󶨽�Ǯ 1��ʾ֧��0��ʾ��֧��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1)
	int			  mCanUnBindUseBM;	
	
	// FieldName: �ָ�����Ҫ�Ľ�Ǯ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mMoneyResumeBindNeed;	
	
	// FieldName:  �ָ����Ƿ�֧�ְ󶨽�Ǯ 1��ʾ֧��0��ʾ��֧��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1)
	int			  mCanResumeBindUseBM;		
	
public:
	void SetFromPB( bool bServer, PBBindChargeTable* pTable );
	void CreateTlvPB( bool bServer, PBBindChargeTable* pTable );
	int Initialize();
	CTplBindChargeTable()
	{
		Initialize();
	}
	~CTplBindChargeTable() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= �ر�ͼ				 ## ģ������
// version	= 1						 ## �汾��
// path		= ��Ʒ/�ر�ͼ			 ## ·��
// parent	= ���߻�����Ϣ			 ## ����ģ��
// ********************************************************************** //

class CMinePos
{
public:
	int		mMapID;	
	int		mPosX;
	int		mPosY;
	int		mProbability;
};

class CTplMineMap : public CTplItem
{
public:

	enum EVENT_TYPE
	{
		EVENT_DROPITEM = 0,			// ������Ʒ
		EVENT_DESBUFF  = 1,				// ����BUFF
		EVENT_BRUSHOGRE= 2,			// ��������ˢ��N������ҵȼ���ͬ�Ĺ�
		EVENT_BRUSHOGREANDNOTIFY  = 3,	// ��������ˢ��N������ҵȼ���ͬ�Ĺֲ�֪ͨ���
		EVENT_BRUSHSPECIALOGRE	  = 4,		// ��������ˢ��N���ض�����ֲ�֪ͨ���
		EVENT_LOGINREPETION		  = 5,		// ���븱��
	};

	class CMineEvent
	{
	public:
		EVENT_TYPE	mEventID;	// �¼�ID
		int		mTouchRate;	// �¼���������
	};

	// FieldName: ��%d���ھ��MapID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d���ھ��x����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d���ھ��y����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d���ھ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	CMinePos	mPos[ MAX_MINEPOS ];

	// FieldName: ��%d�������¼�
	// FieldType: INT4
	// Type:	  COMBOENUM(EVENT_TYPE)

	// FieldName: ��%d���¼���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	CMineEvent	mEvent[ MAX_MINEEVENT ];

	// FieldName: ʹ�ð뾶
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	int			mRadius;

	// FieldName: �����
	// FieldType: INT4
	// Type:	  TEMPPATH

	int			mDropTable;

	// FieldName: ����BUFF
	// FieldType: INT4
	// Type:	  TEMPPATH

	int			mDecBuff;

	// FieldName: ����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	int			mOgreID;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)

	int			mOgreNum;

	// FieldName: ����MapID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	int			mMapID;

	// FieldName: ���븱���������X
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	int			mPosX;
	
	// FieldName: ���븱���������Y
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	int			mPosY;

	// FieldName: �Ƿ�������ر�ͼ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1)
	int			mSpecial;
	
public:
	void SetFromPB( bool bServer, PBItemMineMap* pItem );
	void CreateTlvPB( bool bServer, PBItemMineMap* pItem );
	int Initialize();
	CTplMineMap() 
	{
		Initialize();
	}
	~CTplMineMap() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= ��������				 ## ģ������
// version	= 1						 ## �汾��
// path		= ��Ʒ/��������		 ## ·��
// parent	= ���߻�����Ϣ			 ## ����ģ��
// ********************************************************************** //

class CTplToken : public CTplItem
{
public:


	// FieldName: ��%d���ٻ������MapID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d���ٻ������x����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d���ٻ������y����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d���ٻ���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	CMinePos	mPos[ MAX_MINEPOS ];

	// FieldName: ʹ�ð뾶
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mRadius;

	// FieldName: ����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mOgreID;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int			mOgreNum;

public:
	void SetFromPB( bool bServer, PBItemToken* pItem );
	void CreateTlvPB( bool bServer, PBItemToken* pItem );
	int Initialize();
	CTplToken()
	{
		Initialize();
	}
	~CTplToken() {}
};



// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			 ## �������ɵ����ݿ���
// name		= ���			 ## ģ������
// version	= 1				 ## �汾��
// path		= ��Ʒ/���		 ## ·��
// parent	= ���߻�����Ϣ	 ## ����ģ��
// ********************************************************************** //
class CTplItemRedPaper : public CTplItem
{
public:
	enum EM_REDPAPERTYPE
	{
		REDPAPER_FAMILY = 1,	// ������
		REDPAPER_CORPS	= 2,	// ���ź��
	};
public:
	class CPaperValue 
	{
	public:
		int mValue;
		int mProbality;
	};
public:		
	// FieldName: ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mBaseCharge;

	// FieldName: ������ܿ����ĵ�%d���ǰ󶨽�Ǯ������
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,10000000)	   

	// FieldName: ������ܿ����ĵ�%d���ǰ󶨽�Ǯ�ĸ���
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,10000000) 
	CPaperValue mMoney[MAX_PAPERVALUE_NUM];
	
	// FieldName: ������ܿ����ĵ�%d���󶨽�Ǯ������
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,10000000)	   

	// FieldName: ������ܿ����ĵ�%d���󶨽�Ǯ�ĸ���
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,10000000) 
	CPaperValue mBindMoney[MAX_PAPERVALUE_NUM];
	
	// FieldName: �������
	// FieldType: INT4
	// Type:	  COMBOENUM(EM_REDPAPERTYPE)
	int		mRedPaperType;
public:
	void SetFromPB( bool bServer, PBItemRedPaper* pItem );
	void CreateTlvPB( bool bServer, PBItemRedPaper* pItem );
	int Initialize();
	CTplItemRedPaper()
	{
		Initialize();
	}
	~CTplItemRedPaper() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false			 ## �������ɵ����ݿ���
// name		= �ڹ���		 ## ģ������
// version	= 1				 ## �汾��
// path		= ��Ʒ/�ڹ���	 ## ·��
// parent	= ���߻�����Ϣ	 ## ����ģ��
// ********************************************************************** //
class CTplItemBlackPills : public CTplItem
{
public:
	// FieldName: ����ת��������ʱ��(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int			mExchangeTime;	
	
	// FieldName: �ȼ������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int			mExpTableID;		
public:
	void SetFromPB(  bool bServer, PBItemBlackPills* pItem );
	void CreateTlvPB( bool bServer, PBItemBlackPills* pItem );
	int Initialize();
	CTplItemBlackPills()
	{
		Initialize();
	}
	~CTplItemBlackPills()
	{
		
	}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= ���			 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/���		 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTplHierogram : public CTemplate
{
public:
	enum HIEROGRAM_TYPE
	{
		USE_SKILL		= 0,			//ʹ�ü���
	};
public:

	// FieldName: ��Դ
	// FieldType: STRING32
	// Type:      EDITSTRING
	char		mRes[ 32 ];

	// FieldName: ����ʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mAlive;

	// FieldName: ����
	// FieldType: INT4
	// Type:      COMBOENUM(HIEROGRAM_TYPE)
	HIEROGRAM_TYPE     mType;
	
	// FieldName: ��%d����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mParame[ 2 ];

public:
	void SetFromPB( bool bServer, PBTplHierogram* pTable );
	void CreateTlvPB( bool bServer, PBTplHierogram* pTable );
	int Initialize();
	CTplHierogram()
	{
		Initialize();
	}
	~CTplHierogram() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false						 ## �������ɵ����ݿ���
// name		= Buff���������б�		   	 ## ģ������
// version	= 1							 ## �汾��
// path		= Config/Buff���������б�	 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTplBuffImmunity : public CTemplate
{
public:
	// FieldName:	��%d������״̬
	// FieldType:	INT4
	// Type:		COMBOENUM(BUFF_FUN_TYPE)
	CTemplateBuff::BUFF_FUN_TYPE	mBuffImmunity[ 15 ];
public:
	void SetFromPB( bool vServer, PBTplBuffImmunity* pImmunity );
	void CreateTlvPB( bool vServer, PBTplBuffImmunity* pImmunity );
	int Initialize();
	CTplBuffImmunity()
	{
		Initialize();
	}
	~CTplBuffImmunity() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= PKֵ��Χ��			 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/PKֵ��Χ��		 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTplPKValueTable : public CTemplate
{
public:

	enum PK_NAMESTATE
	{
		STATE_WHITENAME = 0,	// ����
		STATE_AZURY		= 1,			// ǳ����
		STATE_BLUE		= 2,				// ����
		STATE_NAVYBLUE	= 3,			// ������
		STATE_ROSINESS	= 4,			// ǳ��ɫ
		STATE_RED		= 5,				// ����
		STATE_CARMINE	= 6,			// �����
		STATE_PKTOPLIMIT= 7,		// PKֵ����
	};

	class CPKDrop
	{
	public:

		PK_NAMESTATE	mState;
		int				mEquipDropRate;
		int				mBagDropRate1;	// ����1��
		int				mBagDropRate2;	// ����2��
		int				mGoPrisonRate;	// ����������
		int				mPrisonTime;	// ����ʱ��
	};

	// FieldName: ����ֵ(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mNavyBlue;	

	// FieldName: ��ɫֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mBlue;	

	// FieldName: ǳ��ֵ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mCambridgeBlue;	

	// FieldName: ��ɫֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,0)
	int			  mWhite;	

	// FieldName: ǳ��ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,0)
	int			  mRosiness;	

	// FieldName: �к�ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,0)
	int			  mRed;	

	// FieldName: ���ֵ(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1000000,0)
	int			  mCarmine;	

	// FieldName: ����ʱ��(��λ:��)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			  mYellowTime;

	// FieldName: ���ÿ����һСʱPKֵ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mDecValue;

	// FieldName: ����%d�׶����������ʧ����ٷֱ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			  mDecExpRate[ REDNAME_SECTION ];

	// FieldName: %d�����ÿ����ʧ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mTopLimitDecExp[ TMP_MAX_GRADE ];

	// FieldName: �������%d�׶���NPC���׵ļ۸�䶯�ٷֱ�(������ʾ�ϵ����µ��۸�)
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,10000)
	int			  mPriceChange[ REDNAME_SECTION ];

	// FieldName: ������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int			  mLineID;

	// FieldName: ������ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int			  mMapID;

	// FieldName: ����X
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			  mPosX;

	// FieldName: ����Y
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			  mPosY;

	// FieldName: ��Һ���״̬%d�׶�
	// FieldType: INT4
	// Type:	  COMBOENUM(PK_NAMESTATE)

	// FieldName: %d�׶�װ���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: %d�׶ε���1����Ʒ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: %d�׶ε���2����Ʒ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: %d�׶δ��������ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: %d�׶μ���������ʱ��(��λ����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	CPKDrop		  mDrop[ REDNAME_SECTION ];

	// FieldName: �Ӽ����ͷŴ��͵�Ŀ���ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			  mFreeMapID;

	// FieldName: �Ӽ����ͷŴ��͵�Ŀ������X
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			  mFreePosX;

	// FieldName: �Ӽ����ͷŴ��͵�Ŀ������Y
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			  mFreePosY;

	// FieldName: ��������ʱ��(��λ����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			  mPrisonTime;

	// FieldName: PK�ͷ�����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			  mBasePKValue;

	// FieldName: �ȼ���(%d+1)*10�ͷ�ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			  mPKValueLevel[ PRODUCE_LEVEL ];

	// FieldName: �ڵжԹ�������������Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			  mDropRateInEnemy;

	// FieldName: ����buffID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			  mPrisonBuffID;

public:
	void SetFromPB( bool bServer, PBPKValueTable* pTable );
	void CreateTlvPB( bool bServer, PBPKValueTable* pTable );
	int Initialize();
	CTplPKValueTable() 
	{
		Initialize();
	}
	~CTplPKValueTable() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ����ܱ�		## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/����ܱ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //

class CTemplateLifeSkill : public CTemplate
{
public:	
	enum ELifSkillKind
	{
		SKILLKIND_COOK			= 1,	// ���
		SKILLKIND_MINERAL		= 2,	// ����ɼ�	
	};
public:

	// FieldName: ���������	
	// FieldType: INT4
	// Type:	  COMBOENUM(EM_LIFESKILL)
	int			  mLifeSkillType; 
	
	// FieldName: ����ܹ������
	// FieldType: INT4
	// Type:	  COMBOENUM(ELifSkillKind)
	int			  mLifeSkillKind; 

	// FieldName: ��%d������ܼ��ܵ�ѧϰ����Ҫ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mStudyDegree[MAX_LIFESKILL_LEVEL];
	
	// FieldName: ��%d������ܿ���������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mDegreeStarted[MAX_LIFESKILL_LEVEL];
	
	// FieldName: ��%d������ܵ�ѧϰ��Ǯ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mStudyMoney[MAX_LIFESKILL_LEVEL];
	
	// FieldName: ѧϰ��%d������ܵĵȼ�Ҫ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mLevel[MAX_LIFESKILL_LEVEL]; 
	
	// FieldName: ѧϰ��%d������ܺ��ܹ���ȡ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			  mDegreeValue[MAX_LIFESKILL_LEVEL];
	
	// FieldName: $��%d������ܵ�����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char		  mSkillName[MAX_LIFESKILL_LEVEL][ STRING32 ];
	
	// FieldName: ��%d������ܸ���ҵĳƺ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			  mCharacterNameID[MAX_LIFESKILL_LEVEL];	
	
	// FieldName: �����������Ǹ���ְҵ�Ļ�,�ܹ��ﵽ�ĵȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			 mSubSkillLevelLimit;
	
public:
	void SetFromPB( bool bServer, PBTemplateLifeSkill* pLifeSkill );
	void CreateTlvPB( bool bServer, PBTemplateLifeSkill* pLifeSkill );
	int Initialize();
	CTemplateLifeSkill()
	{
		Initialize();
	}
	~CTemplateLifeSkill() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= �ƺ�ϵͳ				 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/�ƺ�ϵͳ		 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //

class CTitle 
{
public:
	char mTitle[ STRING32 ];		// �ƺ�
	int  mType;						// ���
	int  mObtainCondition;			// �������
	int  mSubCondition;				// ��������
	int  mColor;					// �ƺ���ɫ
	int  mAddProperty;				// ��Ӧ��������
	int  mIsHidden;					// �ƺ��Ƿ�����
	int  mIsReplace;				// �Ƿ�ֱ���滻ԭ���ĳƺ�
	int  mValidTime;				// �ƺ���Чʱ��
	char mDescribe[ STRING256 ];	// ����
	int	 mIsTeamTitle;				// ����ƺ�����
	int	 mParm;						// ����
	char mDetail[ STRING256 ];		// �ƺ�˵��
};

class CTplTitleManager : public CTemplate
{
public:
	enum ETitleType
	{
		RANK_PLAYER_INTEGRATE	= 0x1001,		// ���а���ƺţ������ۺ�ʵ��
		RANK_PLAYER_LEVEL		= 0x1002,		// ���а���ƺţ�����ȼ�
		RANK_MONEY_OWN			= 0x1003,		// ���а���ƺţ�ӵ�вƸ�
		RANK_KILLENEMY_NUM		= 0x1004,		// ���а���ƺţ�ɱ����
		RANK_EXPLOIT			= 0x1005,		// ���а���ƺţ���ѫ
		RANK_PRSNHONER_FB		= 0x1006,		// ���а���ƺţ�������������
		RANK_TEAMHONER_FB		= 0x1007,		// ���а���ƺţ������Ŷ�����
		RANK_NUM_DIE			= 0x1008,		// ���а���ƺţ���������
		RANK_RELIFE				= 0x1009,		// ���а���ƺţ�ԭ�ظ������
		RANK_TOTAL_TASK			= 0x100A,		// ���а���ƺţ������������
		RANK_ONLINE_TIME		= 0x100B,		// ���а���ƺţ�����ʱ��
		RANK_KILLOGRE_NUM		= 0x100C,		// ���а���ƺţ�ɱ����
		RANK_REFINEFAIL_NUM		= 0x100D,		// ���а���ƺţ�����ʧ�ܴ���
		RANK_KILLSAMENATION		= 0x100E,		// ���а���ƺţ�ɱ����Ӫ��
		RANK_DAYANTA			= 0x100F,		// ���а���ƺţ����������֣�ȫ����
		RANK_LIANHUADONG		= 0x1010,		// ���а���ƺţ����������֣�ȫ����
		RANK_HUANGFENGDONG		= 0x1011,		// ���а���ƺţ��Ʒ䶴���֣�ȫ����
		RANK_ACHIVE_POINT		= 0x1012,		// ���а���ƺţ��ɾ͵㣨ȫ����
		RANK_FAVOR_POINT		= 0x1013,		// ���а���ƺţ��øжȣ�ȫ����
		RANK_BAD_POINT			= 0x1014,		// ���а���ƺţ�����ȣ�ȫ����
		RANK_FAMILY_PVP			= 0x1015,		// ���а���ƺţ�����PVP���֣�ȫ����
		RANK_CORPS_PVP			= 0x1016,		// ���а���ƺţ�����PVP���֣�ȫ����
		RANK_FAMILY_TAO			= 0x1017,		// ���а���ƺţ�����Ʒ���һ��֣�ȫ����
		RANK_HONOR_ALL_TODAY	= 0x1018,		// ���а���ƺţ�������������
		RANK_HONER_MYNATION_TODAY = 0x1019,		// ���а���ƺţ�������Ӫ����
		RANK_KILL_PROT_NATION_TODAY	= 0x101A,	// ���а���ƺţ�����ɱ����(����)
		RANK_KILL_OUT_TODAY			= 0x101B,	// ���а���ƺţ�����ɱ����(����)
		RANK_KILL_TOTAL_TODAY		= 0x101C,	// ���а���ƺţ����ձ�����ɱ��
		RANK_CHARM				= 0x101D,		// ���а���ƺţ�������������ֵ
		RANK_FLYFB				= 0x101E,		// ���а���ƺţ����ƴ�ս����
		RANK_ZHIGUO					= 0x101F,		// ���а���ƺţ��ι���
		RANK_TONGSHUAI				= 0x1020,		// ���а���ƺţ�ͳ˧��
		RANK_ZHANGONG				= 0x1021,		// ���а���ƺţ�ս��
		RANK_WISALL					= 0x1022,		// ���а���ƺţ��Ż���ֵ
		RANK_YUNXIAOTA				= 0x1023,		// ���а���ƺţ�����������
		RANK_YUNXIAOTA_LV			= 0x1024,		// ���а���ƺţ�����������
		RANK_SHIDE					= 0x1025,		// ���а���ƺţ�ʦ�»���
		RANK_XIANYUANMARK			= 0x1026,		// ���а���ƺţ���Ե����
		RANK_CHUSHITU				= 0x1027,		// ���а���ƺţ���ʦͽ��
		RANK_WUDIDONG				= 0x1028,		// ���а���ƺţ��޵׶�����
		RANK_GLOBALWAR				= 0x1029,		// ���а���ƺţ����ƶɻ���
		RANK_SPIRIT					= 0x1030,		// ���а���ƺţ���������
		RANK_CORPSBOSS_SCORE		= 0x1031,		// ���а���ƺţ�����boss����
		RANK_CORPSCOLLECT_ACTIVE	= 0x1032,		// ���а���ƺţ����Ųɼ���Ծ��
		RANK_NEW_YUNXIAOTA			= 0x1033,		// ���а���ƺţ�������60����֣����лþ��������֣�

		CNDISN_COOKING			= 0x2001,		// ������ƺţ����
		CNDISN_CORPSCLAN		= 0x2002,		// ������ƺţ����ż���
		CNDISN_LIFE				= 0x2003,		// ������ƺţ�����ϵͳ
		STATISTIC_TASK			= 0x3001,		// ͳ����ƺţ�����
		STATISTIC_KILLOGRE		= 0x3002,		// ͳ����ƺţ�ɱ��
		STATISTIC_REFINE		= 0x3003,		// ͳ����ƺţ�����
		STATISTIC_TRANVEL		= 0x3004,		// ͳ����ƺţ�����
		STATISTIC_KILLBOSS		= 0x3005,		// ͳ����ƺţ�ɱBOSS
		STATISTIC_FRIEND		= 0x3006,		// ͳ����ƺţ�����
		STATISTIC_MARRIAGE		= 0x3007,		// ͳ����ƺţ�����		
		STATISTIC_YAOMOZHI		= 0x3008,		// ͳ����ƺţ���ħ־
		SPECIAL_KILLBOOS		= 0x4001,		// ������ƺţ�ɱBOSS
		SPECIAL_NATION			= 0x4002,		// ������ƺţ�������
		SPECIAL_XIANYUAN		= 0x4003,		// ������ƺţ���Ե��
		MARRIAGE_SPOUSE			= 0x4004,		// �����޳ƺ�
		TITLETYPE_SWORN			= 0x4005,		// ��ݳƺ�

		TITLETYPE_CAMP			= 0x5000,		// ��Ӫ��ƺ�(����������4����Ӫ)
		
	};

	enum ECndisnScope
	{
		SCOPE_GLOBAL		= 0,				// ȫ������
		SCOPE_COUNTRY		= 1,						// ����
		SCOPE_UNBOUNDMONEY  = 2,					// �ǰ󶨽�
		SCOPE_TOTAL			= 3,						// �ܼ�
		SCOPE_PROTECT_WEEK  = 4,					// ���ܻ���
		SCOPE_BATTLE_WEEK	= 5,					// ���ܳ���
		SCOPE_WORLD_TOTAL	= 6,					// ���������ܹ�ѫ
		SCOPE_COUNTRY_TOTAL = 7,				// ���ܱ����ܹ�ѫ
		SCOPE_FB_TOTAL		= 8,						// ���������ܻ���
		SCOPE_PANTAO		= 9,						// ��ҽ�
		SCOPE_LONGGONG		= 10,						// ����
		SCOPE_TASKFINISH	= 11,					// �������
		SCOPE_KILLOGRENUM	= 12,					// ɱ������
		SCOPE_ONLINETIME	= 13,					// ����ʱ��
		SCOPE_REFINEFAIL	= 14,					// ����ʧ��
		SCOPE_FRIENDNUM		= 15,					// ��������
		SCOPE_CAIJI			= 16,						// �ɼ�����
		SCOPE_DIANJIN		= 17,						// �����
		SCOPE_PENGREN		= 18,						// ��⿼���
		SCOPE_QIAOJIANG		= 19,					// �ɽ�����
		SCOPE_LIANDAN		= 20,						// ��������
		SCOPE_FIRSTTIME		= 21,					// ɱ����BOOS
		SCOPE_NATIONALITY	= 22,					// ��������
		SCOPE_OWNNATION		= 23,					// ����ռ��
		SCOPE_OWNNORMALMAP	= 24,					// Ұ���ͼռ��
	};

	enum ERankLevel
	{
		LEVEL_1		= 0,		// ��1��
		LEVEL_2_4	= 1,				// ��2-4��
		LEVEL_5_10	= 2,				// ��5-10��
		TASK_10		= 3,				// ���10��֮ǰ��������
		TASK_20		= 4,				// ���20��֮ǰ��������
		TASK_30		= 5,				// ���30��֮ǰ��������
		TASK_40		= 6,				// ���40��֮ǰ��������
		TASK_50		= 7,				// ���50��֮ǰ��������
		TASK_60		= 8,				// ���60��֮ǰ��������
		TASK_70		= 9,				// ���70��֮ǰ��������
		TASK_80		= 10,				// ���80��֮ǰ��������
		TASK_90		= 11,				// ���90��֮ǰ��������
		TASK_100	= 12,				// ���100��֮ǰ��������
		TASK_110	= 13,				// ���110��֮ǰ��������
		KILLOGRE_10000= 14,			// ɱ�������ﵽ10000ֻ
		KILLOGRE_100000=15,		// ɱ�������ﵽ100000ֻ
		ONLINE_500	= 16,				// ����ʱ���ﵽ500Сʱ
		ONLINE_1500	= 17,			// ����ʱ���ﵽ1500Сʱ
		REFINEFAIL_100= 18,			// ��������ʧ��100��
		FRIEND_100	= 19,				// ���������ﵽ100��
		FRIEND_200	= 20,				// ���������ﵽ200��
		LEVEL_DASHI = 21,			// ��ʦ����
		COLLECT_500	= 22,			// �ռ������ﵽ500
		FIRST_TIME	= 23,				// ��һ��
		JUNTUANZHANG= 24,			// ���ų�
		XIANYUAN_QT	= 25,			// ��ͭǰ��
		XIANYUAN_BY	= 26,			// ����ǰ��
		XIANYUAN_HJ	= 27,			// �ƽ�ǰ��
		XIANYUAN_ZS	= 28,			// ��ʯǰ��
		XIANYUAN_ZZ	= 29,			// ����ǰ��
		LEVEL_2		= 30,			// �ڶ���
		LEVEL_3		= 31,			// ������
	};

	enum EColor
	{
		COLOR_RED			= 0,					// ��ɫ
		COLOR_OGANGE		= 1,					// ��ɫ
		COLOR_YELLOW		= 2,					// ��ɫ
		COLOR_GREEN			= 3,					// ��ɫ
		COLOR_CYAN			= 4,					// ��ɫ
		COLOR_BLUE			= 5,					// ��ɫ
		COLOR_PURPLE		= 6,					// ��ɫ
		COLOR_WHITE			= 7,					// ��ɫ
		COLOR_GRAY			= 8,					// ��ɫ
		COLOR_COLOR			= 9,					// ��ɫ
	};	

	enum ETeamType
	{
		TEAM_NONE	= 0,		// ������
		TEAM_FAMILY = 1,			// ����ƺ�
		TEAM_CORPS  = 2,				// ���ųƺ�
		TEAM_UNION  = 3,				// �����˳ƺ�
		TEAM_NATION = 4,			// ���ҳƺ�
		TEAM_CAMP	= 5,				// ��Ӫ�ƺ�
	};
	
	// FieldName: $�ƺ�����,��%d���ƺ�
	// FieldType: STRING32
	// Type:	  EDITSTRING

	// FieldName: ���,��%d���ƺ�
	// FieldType: INT4
	// Type:	  COMBOENUM(ETitleType)

	// FieldName: ��ȡ������Χ,��%d���ƺ�
	// FieldType: INT4
	// Type:������COMBOENUM(ECndisnScope)

	// FieldName: ��ȡ������,��%d���ƺ�
	// FieldType: INT4
	// Type:������COMBOENUM(ERankLevel)

	// FieldName: �ƺ���ʾ��ɫ,��%d���ƺ�
	// FieldType: INT4
	// Type:������COMBOENUM(EColor)

	// FieldName: ��Ӧ��������,��%d���ƺ�
	// FieldType: INT4
	// Type:	��EDITNUMBER(0,1000000)

	// FieldName: �ƺ���ʾ�Ƿ����أ���%d���ƺ�
	// FieldType: INT4
	// Type:	��COMBOSINGLE(��=0,��=1)

	// FieldName: �Ƿ�ֱ���滻ԭ���ĳƺ�,��%d���ƺ�
	// FieldType: INT4
	// Type:	��COMBOSINGLE(��=0,��=1)

	// FieldName: �ƺ���Чʱ��(��λ:Сʱ),��%d���ƺ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(-1,100000)

	// FieldName: $�ƺŶ�Ӧ��������������,��%d���ƺ�
	// FieldType: STRING256
	// Type:	  EDITSTRING

	// FieldName: ����ƺ�����,��%d���ƺ�
	// FieldType: INT4
	// Type:	  COMBOENUM(ETeamType)

	// FieldName: ����,��%d���ƺ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	// FieldName: $�ƺ�˵��,��%d���ƺ�
	// FieldType: STRING256
	// Type:	  EDITSTRING

	CTitle		mTitle[ MAX_TITLE ];

public:
	void SetFromPB( bool bServer, PBTitleManager* pManager );
	void CreateTlvPB( bool bServer, PBTitleManager* pManager );	
	int Initialize();
	CTplTitleManager()
	{
		Initialize();
	}
	~CTplTitleManager() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= װ���ֽ��		## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/װ���ֽ��	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
enum EDecompoundResult
{	
	DECOMPOUND_SUCESS		   = 0,
	DECOMPOUND_DEGREENOTENOUGH = 1,	
};

class CTemplateDecompound : public CTemplate
{
public:
	class DecompondTable 
	{		
		public:
			int FstItemID;			// �ֽ�װ�����ɵ�һ����Ʒ��ID
			int FstProbability;		// �ֽ�װ�����ɵ�һ����Ʒ�ĸ���
			int FstItemNum;			// �ֽ�װ�����ɵ�һ����Ʒ������
			int SecItemID;			// �ֽ�װ�����ɵڶ�����Ʒ��ID
			int SecProbability;		// �ֽ�װ�����ɵڶ�����Ʒ�ĸ���
			int SecItemNum;			// �ֽ�װ�����ɵڶ�����Ʒ������
			int ThirdItemID;		// �ֽ�װ�����ɵ�������Ʒ��ID
			int ThirdProbability;	// �ֽ�װ�����ɵ�������Ʒ�ĸ���
			int ThirdItemNum;		// �ֽ�װ�����ɵ�������Ʒ������
			int	DegreeNeeded;		// �ֽ�װ����Ҫ��������
	};	
public:
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�һ����Ʒ��ģ��id
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�һ����Ʒ�����ɸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�һ����Ʒ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵڶ�����Ʒ��ģ��id
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵڶ�����Ʒ�����ɸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵڶ�����Ʒ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�������Ʒ��ģ��id
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�������Ʒ�����ɸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�������Ʒ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	
	// FieldName: ��%d*5+5����װ�ֽ���Ҫ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	
	DecompondTable mWhitDecompond[DECOMPOUND_MAXTABLEINDEX];	// ��װ��װ���ֽ��
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�һ����Ʒ��ģ��id
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�һ����Ʒ�����ɸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�һ����Ʒ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: ��%d*5+5����װ�ֽ����ɵĵڶ�����Ʒ��ģ��id
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: ��%d*5+5����װ�ֽ����ɵĵڶ�����Ʒ�����ɸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵڶ�����Ʒ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�������Ʒ��ģ��id
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�������Ʒ�����ɸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�������Ʒ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	
	// FieldName: ��%d*5+5����װ�ֽ���Ҫ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	DecompondTable mBlueDecompond[DECOMPOUND_MAXTABLEINDEX];	// ��װ��װ���ֽ��
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�һ����Ʒ��ģ��id
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�һ����Ʒ�����ɸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�һ����Ʒ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: ��%d*5+5����װ�ֽ����ɵĵڶ�����Ʒ��ģ��id
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: ��%d*5+5����װ�ֽ����ɵĵڶ�����Ʒ�����ɸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵڶ�����Ʒ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�������Ʒ��ģ��id
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)

	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�������Ʒ�����ɸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	
	// FieldName: ��%d*5+5����װ�ֽ����ɵĵ�������Ʒ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	
	// FieldName: ��%d*5+5����װ�ֽ���Ҫ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	DecompondTable mPurpleDecompond[DECOMPOUND_MAXTABLEINDEX];	// ��װ��װ���ֽ��
	
	// FieldName: ���������ȶ���ֽ�װ����Ҫ�������ȵĵ�%d����ֵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mValue[MAX_LIFESKILL_DEGREESTEP];	

	// FieldName: ��%d���Ĳ�ֵ����ֽ�װ����ȡ�����ȵĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mProbality[MAX_LIFESKILL_DEGREESTEP];	

	// FieldName: ��%d���Ĳ�ֵ����ֽ�װ����ȡ�����ȵ���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mDegreeValue[MAX_LIFESKILL_DEGREESTEP];	
	
public:
	void SetFromPB( bool bServer, PBCTemplateDecompound* pCompound );
	void CreateTlvPB( bool bServer, PBCTemplateDecompound* pCompound );
	int Initialize();
	CTemplateDecompound()
	{
		Initialize();
	}
	~CTemplateDecompound() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= �컯����				 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/�컯����		 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //

class CTemplateTalent : public CTemplate
{
public:
	class CStep
	{
	public:
		int			mStageID;
		char		mStageDesc[ 32 ];
		int			mSkillTree;
		int			mNext[ STEP_SWITCH ];
	  //int			mExp;
		int			mMaxPoint;
		int			mLayer;
	};


	// FieldName: ��%d��С�׵Ĵ�ױ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: $��%d��С�׵�����
	// FieldType: STRING32
	// Type:      EDITSTRING

	// FieldName: ��%d��С�׵ļ�����
	// FieldType: INT4
	// Type:	  TEMPPATH

	// FieldName: ��%d��С�׵ĵ�1����һС��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d��С�׵ĵ�2����һС��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d��С�׵ĵ�3����һС��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)	

	// FieldName: ��%d��С�׵�����ܵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d��������ڵĲ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	CStep	mStep[ TOTAL_TALENT_STAGE ];	

	// FieldName: ��%d��С�׵���Ϊֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mExp[ TOTAL_TALENT_POINT ];

public:
	void SetFromPB( bool bServer, PBTemplateTalent* pTalent );
	void CreateTlvPB( bool bServer, PBTemplateTalent* pTalent );
	int Initialize();
	CTemplateTalent()
	{
		Initialize();
	}
	~CTemplateTalent() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= װ���һ���		## ģ������
// version	= 1					## �汾��
// path		= Config/װ���һ���	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTempateEquipExchangeTable : public CTemplate
{
public:
	enum EM_EXCHANGETYPE
	{		
		EXCHANGETYPE_EQUIPMENTCHANGE	=	0,			// װ���һ�
		EXCHANGETYPE_FAMILYEXCHANGE		=	1,			// ����һ�
		EXCHANGETYPE_CORPSEXCHANGE		=	2,			// ���Ŷһ�
		EXCHANGETYPE_MARRIAGEEXHCNANGE	=	3,			// ���������һ�
	}; 
public:

	
	// FieldName: ��%d���䷽ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mMultiComposeID[MAX_EQUIPCOMPOSEID_NUM];	// �һ����䷽ID
	
	// FieldName: �һ�����
	// FieldType: INT4
	// Type:	  COMBOENUM(EM_EXCHANGETYPE)
	int		mExchangeType;
	
public:
	void SetFromPB( bool bServer, PBEquipExchangeTable* pTalent );
	void CreateTlvPB( bool bServer, PBEquipExchangeTable* pTalent );
	int Initialize();
	CTempateEquipExchangeTable() 
	{
		Initialize();
	}
	~CTempateEquipExchangeTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ���buff���ñ�	## ģ������
// version	= 1					## �汾��
// path		= Config/���buff���ñ� 	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //

class CTemplateEvent
{
public:
	int		mEventID;
	int		mTeamFlag;
	int		mDistance;
	int		mBuffID;
    int     mRepetionIndex[3];
};

class CTemplateMultiBuffConfig : public CTemplate
{
public:
	enum EEventType
	{
		EVENT_SHITU = 1,	// ʦͽ����
		EVENT_MARRY = 2,		// ����
		EVENT_4METIRE_AWARD = 3,// 4ְҵ��ӽ���
		EVENT_5METIRE_AWARD = 4,// 5ְҵ��ӽ���
		EVENT_6METIRE_AWARD = 5,// 6ְҵ��ӽ���
		EVENT_4METIRE_AWARD_FB = 6,// 4ְҵ������ӽ���
		EVENT_5METIRE_AWARD_FB = 7,// 5ְҵ������ӽ���
		EVENT_6METIRE_AWARD_FB = 8,// 6ְҵ������ӽ���
		EVENT_4SAMEBUFF_AWARD = 9,// 4��ͬbuff��ӽ���
		EVENT_5SAMEBUFF_AWARD = 10,// 5��ͬbuff��ӽ���
		EVENT_6SAMEBUFF_AWARD = 11,// 6��ͬbuff��ӽ���
	};

	// FieldName: ��%d���¼�,�¼�����
	// FieldType: INT4
	// Type:	  COMBOENUM(EEventType)

	// FieldName: ��%d���¼�,�Ƿ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ��%d���¼�,���þ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)

	// FieldName: ��%d���¼�,Ч��buffid
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)

	// FieldName: ��%d���¼�,��������0
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
    
	// FieldName: ��%d���¼�,��������1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
    
	// FieldName: ��%d���¼�,��������2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)

	CTemplateEvent mEvent[ MAX_MUTIBUFFEVENT ];

	// FieldName: ��%d�¼�,��%d������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)

	int		mEventParam[ MAX_MUTIBUFFEVENT ][ MAX_EVENTPARAM ];

	// FieldName: ��%d�¼�,��%d��buff
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)

	int		mEventBuff[ MAX_MUTIBUFFEVENT ][ MAX_EVENTPARAM ];

public:
	void SetFromPB( bool bServer, PBMultiBuff* pMBuff );
	void CreateTlvPB( bool bServer, PBMultiBuff* pMBuff );
	int Initialize();
	CTemplateMultiBuffConfig()
	{
		Initialize();
	}
	~CTemplateMultiBuffConfig() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��ȴCD��			## ģ������
// version	= 1					## �汾��
// path		= Config/��ȴCD��	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateCDGroupTable : public CTemplate
{
public:

	// FieldName: ��%d����ȴ���ʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mCDTime[ 200 ];	
public:
	void SetFromPB( bool bServer, PBCDGroupTable* pTable );
	void CreateTlvPB( bool bServer, PBCDGroupTable* pTable );
	int Initialize();
	CTemplateCDGroupTable()
	{
		Initialize();
	}
	~CTemplateCDGroupTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �������ñ�		## ģ������
// version	= 1					## �汾��
// path		= Config/�������ñ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //

class CMetierAp
{
public:
	int mMetier ;	// ְҵ
	int mAp;		// ÿ��ظ��û���ֵ
};

class CTplApConfig : public CTemplate
{
public:


	// FieldName: һ���ӹһ�ʱ�����ĵû���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mConsumeHook;	

	// FieldName: ����Ƶ���������ĵû���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mWorldChat;	

	// FieldName: ��ӪƵ���������ĵû���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mCampChat;	

	// FieldName: ��ҵȼ�ÿ����һ��������ֵ��������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mIncApMax;

	// FieldName: ��%d��ְҵ
	// FieldType: INT4
	// Type:	  COMBOENUM(METIER_TYPE)
	
	// FieldName: ��%d��ְҵ��Ӧ�û����ظ�ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)

	CMetierAp mMetierAp[ MAX_METIER ];

	// FieldName: �Զ��һ�����%d���ҩ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	int			mRedPhysic[ MAX_PHYSIC_NUM ];

	// FieldName: �Զ��һ�����%d����ҩ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	int			mBluePhysic[ MAX_PHYSIC_NUM ];

	// FieldName: �Զ��һ�����%d�����ҩ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	int			mApPhysic[ MAX_PHYSIC_NUM ];

	// FieldName: �Զ��һ�����%d�෨������ҩ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	int			mFbHpPhysic[ MAX_PHYSIC_NUM ];

	// FieldName: �Զ��һ�����%d�෨������ҩ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	int			mFbMpPhysic[ MAX_PHYSIC_NUM ];

	// FieldName: �Զ��һ�����%d������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	int			mMendPhysic[ MAX_PHYSIC_NUM ];
	
public:
	void SetFromPB( bool bServer, PBApConfig* pConfig );
	void CreateTlvPB( bool bServer, PBApConfig* pConfig );
	int Initialize();
	CTplApConfig()
	{
		Initialize();
	}
	~CTplApConfig() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �������ñ�		## ģ������
// version	= 1					## �汾��
// path		= Config/�������ñ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateLightTable : public CTemplate
{
public:


	// FieldName: ��%d�������ķ���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mLevelPoint[ 12 ];	

	// FieldName: ��%d����ʯ�ķ���ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mJewelPoint[ 8 ];	

	// FieldName: ��%d����������ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mLevelGrade1[ 5 ];	

	// FieldName: ��%d�ַ��߷���ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mLevelGrade2[ 5 ];	

	// FieldName: ��%d��������ʯ����ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mJewelGrade1[ 5 ];	

	// FieldName: ��%d�ַ��߱�ʯ����ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mJewelGrade2[ 5 ];	
public:
	void SetFromPB( bool bServer, PBLightTable* pTable );
	void CreateTlvPB( bool bServer, PBLightTable* pTable );
	int Initialize();
	CTemplateLightTable()
	{
		Initialize();
	}
	~CTemplateLightTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �Ż������			## ģ������
// version	= 1					## �汾��
// path		= Config/�Ż������	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateWizardTable : public CTemplate
{
public:

	// FieldName: ��%d�������ľ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mExp[ MAX_WIZARD_TEMP ];	

	// FieldName: ��������ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mKeepRand;

	// FieldName: ��%d���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mTrendRand[ 20 ];

	// FieldName: ��%d������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mTrendResult[ 20 ];

	// FieldName: �����ļ۸�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mMoney;
public:
	void SetFromPB( bool bServer, PBWizardTable* pTable );
	void CreateTlvPB( bool bServer, PBWizardTable* pTable );
	int Initialize();
	CTemplateWizardTable()
	{
		Initialize();
	}
	~CTemplateWizardTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �ø����ñ�		## ģ������
// version	= 1					## �汾��
// path		= Config/�ø����ñ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //

class CJudgeLevel
{
public:
	int		mType;		// �øС���С�İ��
	int		mLevelMin;		// �ȼ��ٽ�ֵ����
	int		mLevelMax;		// �ȼ��ٽ�ֵ����
	int		mStar;		// ��Ӧ�Ǽ�
	int		mLevelType;	// ��������
};

class CTplJudgeConfig : public CTemplate 
{
public:
	enum JudgeTypeTpl
	{
		JUDGE_FAVOR = 0,	// �ø�
		JUDGE_BAD   = 1,			// ���
	};
	enum JudgeLevel
	{
		JUDGE_BAD_ENEMY = 0,	// ����
		JUDGE_BAD_ABHOR = 1,		// ʹ��
		JUDGE_BAD_DETEST = 2,		// ���
		JUDGE_BAD_REPULSION = 3,	// �ų�
		JUDGE_BAD_REBEL = 4,		// ����
		JUDGE_BAD_COOL  = 5,			// ��Į
		JUDGE_FAVOR_COOL = 6,		// İ��
		JUDGE_FAVOR_FIRST = 7,		// ��ʶ
		JUDGE_FAVOR_ACQ = 8,		// ��ʶ
		JUDGE_FAVOR_FRIEND = 9,		// �Ѻ�
		JUDGE_FAVOR_BOSOM  = 10,		// ��֪
		JUDGE_FAVOR_INTIMITY= 11,	// �׽�
	};
	enum JudgeStarLevel
	{
		JUDGE_STAR_Y1 = 0,		// һ����
		JUDGE_STAR_R1 = 1,			// һ����
		JUDGE_STAR_R1Y1 = 2,		// һ��һ����
		JUDGE_STAR_R2  = 3,			// ������
		JUDGE_STAR_R2Y1= 4,		// ����һ����
		JUDGE_STAR_R3  = 5,			// ������
	};
public:


	// FieldName: �����ر�CDʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mOpenCD;	

	// FieldName: ��%d������������
	// FieldType: INT4
	// Type:	  COMBOENUM(JudgeTypeTpl)

	// FieldName: ��%d����ȼ��ٽ�ֵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��%d����ȼ��ٽ�ֵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��%d�����Ӧ�Ǽ�
	// FieldType: INT4
	// Type:	  COMBOENUM(JudgeStarLevel)

	// FieldName: ��%d��������
	// FieldType: INT4
	// Type:	  COMBOENUM(JudgeLevel)

	CJudgeLevel		mJudgeLevel[ MAX_JUDGE_LEVEL ];

	// FieldName: �Ը����������޻�׼��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mScoreBase;

	// FieldName: �Ը�����������ϵ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mScoreRate;

	// FieldName: �����۵ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mScoreLevel;

public:
	void SetFromPB( bool bServer, PBJudgeConfig* pTable );
	void CreateTlvPB( bool bServer, PBJudgeConfig* pTable );
	int Initialize();
	CTplJudgeConfig()
	{
		Initialize();
	}
	~CTplJudgeConfig() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �Ż�����			## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/�Ż�����		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateTrend : public CTemplate
{
public:

	// FieldName: $��������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mName[ STRING32 ];	

	// FieldName: $��������
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char	mDesc[ STRING256 ];

	// FieldName: ��%d�ֲŻ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mBonus[ 6 ];

public:
	void SetFromPB( bool bServer, PBTrend* pTable );
	void CreateTlvPB( bool bServer, PBTrend* pTable );
	int Initialize();
	CTemplateTrend() 
	{
		Initialize();
	}
	~CTemplateTrend() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= �ɾͽ�����			 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/�ɾͽ�����		 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //

class CAward
{
public:
	int		mItemID;	// ����ID
	int		mItemNum;	// ��������
};

class CTplAchieveAward : public CTemplate
{
public:

	// FieldName: ��%d���%d�ֽ�������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	int		mAwardID[ MAX_ACHIEVE_AWARD ][ MAX_ACHIEVE_ITEM ];

	// FieldName: ��%d���%d�ֽ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mAwardNum[ MAX_ACHIEVE_AWARD ][ MAX_ACHIEVE_ITEM ];

	// FieldName: ��%d��Ҫ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mPoint[ MAX_ACHIEVE_AWARD ];
	
	// FieldName: ϵͳ�ʼ�ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mSysMailID;

public:
	void SetFromPB( bool bServer, PBAchieveAward* pAchieveAward );
	void CreateTlvPB( bool bServer, PBAchieveAward* pAchieveAward );
	int Initialize();
	CTplAchieveAward()
	{
		Initialize();
	}
	~CTplAchieveAward() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

enum EOfficialFunction
{
	OFFICIAL_FUNCTION_RENSHI			= 0,	// ����
	OFFICIAL_FUNCTION_HUKOU				= 1,	// ����
	OFFICIAL_FUNCTION_LIBIN				= 2,	// ��
	OFFICIAL_FUNCTION_GUOFANG			= 3,	// ����
	OFFICIAL_FUNCTION_FAYUAN			= 4,	// �̲�
	OFFICIAL_FUNCTION_GONGCHENG			= 5,	// ����
	OFFICIAL_FUNCTION_KING				= 6,	// ����
	OFFICIAL_FUNCTION_NUM				= 7,
};


enum EOfficial
{
	OFFICAL_RENSHI			= 0,	// ����
	OFFICAL_HUKOU			= 1,	// ����
	OFFICAL_LIBIN			= 2,	// ��
	OFFICAL_GUOFANG			= 3,	// ����
	OFFICAL_FAYUAN			= 4,	// �̲�
	OFFICAL_GONGCHENG		= 5,	// ����
	OFFICAL_NUM				= 6,
};

enum EOfficialLevel
{
	OFFICIAL_LEVEL_NONE		= 0,		// ��
	OFFICIAL_LEVEL_NINE		= 1,		// ��Ʒ
	OFFICIAL_LEVEL_EIGHT	= 2,
	OFFICIAL_LEVEL_SEVEN	= 3,
	OFFICIAL_LEVEL_SIX		= 4,
	OFFICIAL_LEVEL_FIVE		= 5,
	OFFICIAL_LEVEL_FOUR		= 6,
	OFFICIAL_LEVEL_THREE	= 7,
	OFFICIAL_LEVEL_TWO		= 8,
	OFFICIAL_LEVEL_ONE		= 9,		// һƷ
	OFFICIAL_LEVEL_ZERO		= 10,		// ����
	OFFICIAL_LEVEL_KING		= 11,		// ����
	OFFICIAL_LEVEL_NUM		= 12,
};

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��ְ����			## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/��ְ����		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplatePower : public CTemplate
{
public:

	enum EPowerType
	{
		POWER_NONE		= 0,  // �޹���
		POWER_SHUT		= 1,  // ����
		POWER_PRISON    = 2,  // ����
		POWER_ITEM		= 3,  // ��Ʒ
		POWER_BUFF	    = 4,  // BUFF
		POWER_TASK		= 5,  // ����
		POWER_SUMMON	= 6,  // �ٻ�����
		POWER_STONE		= 7,  // �ڵ�
		POWER_FREE		= 8,  // �ͷ�
		POWER_ALL		= 9,  // ������
		POWER_PASSIVE	= 10, // ����
		POWER_SUMMONWORLD	= 11, // �ٻ���Ӫ
		POWER_SUMMONCOUNTRY	= 12, // �ٻ�����
		POWER_SUMMONCORPS	= 13, // �ٻ�����
		POWER_SUMMONFAMILY	= 14, // �ٻ�����
		POWER_MAKEGT	= 15,	// ������̽
		POWER_MAKELW	= 16,	// ��������
	};	


	// FieldName: $��������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mName[ STRING32 ];	

	// FieldName: $��������
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char	mDesc[ STRING256 ];

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOENUM(EPowerType)
	int		mType;

	// FieldName: ���Ƶ�Ʒ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int		mLevel;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����=0,����,��,����,�̲�,����,������Ȩ)
	int		mOfficial;	

	// FieldName: ���˳��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mOrder;

	// FieldName: ����1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mParam1;

	// FieldName: ����2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mParam2;

	// FieldName: ��%d����ʹ�ô���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mUseTime[ 12 ];

	// FieldName: ��Ҫ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mConstruct;

	// FieldName: ��Ҫ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mPower;

	// FieldName: ��Ҫ��Ǯ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mMoney;

	// FieldName: ͼ������
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char	mIcon[ STRING256 ];

	// FieldName: �������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=-1,����,�ڼ�,����,����)
	int		mCountry;

	// FieldName: �Ƿ�ȫ������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mAllCount;

	// FieldName: ��ʼʱ�䣨Сʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,23)
	int		mStartHour;

	// FieldName: ��ʼʱ�䣨���ӣ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,59)
	int		mStartMin;

	// FieldName: ����ʱ�䣨Сʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,23)
	int		mEndHour;

	// FieldName: ����ʱ�䣨���ӣ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,59)
	int		mEndMin;


public:
	void SetFromPB( bool bServer, PBPower* pPower );
	void CreateTlvPB( bool bServer, PBPower* pPower );
	int Initialize();
	CTemplatePower()
	{
		Initialize();
	}
	~CTemplatePower() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��Ա��Ϣ			## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/��Ա��Ϣ		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateOfficial : public CTemplate
{
public:

	enum EOfficialConfig
	{
		OFFICIAL_CFG_RENSHI		= 0x0001,		// ����
		OFFICIAL_CFG_HUKOU		= 0x0002,		// ����
		OFFICIAL_CFG_LIBIN		= 0x0004,		// ��
		OFFICIAL_CFG_GUOFANG	= 0x0008,		// ����
		OFFICIAL_CFG_FAYUAN		= 0x0010,		// �̲�
		OFFICIAL_CFG_GONGCHENG	= 0x0020,		// ����
	};


	// FieldName: $��ְ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mName[ STRING32 ];	

	// FieldName: $��ְ����
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char	mDesc[ STRING256 ];

	// FieldName: ��Ա����
	// FieldType: INT4
	// Type:	  CHECKMUTI(��=0,����,����,��,����,�̲�,����)
	int		mType;

	// FieldName: ��Ҫ�ĲŻ�ֵ%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mWizard[ 6 ];

	// FieldName: �����������۵�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mPower;

	// FieldName: ��Ҫ�Ĺ��ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mCountryLevel;

	// FieldName: ��Ҫ�Ľ���ȵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mConstructLevel;

public:
	void SetFromPB( bool bServer, PBOfficial* pOfficial );
	void CreateTlvPB( bool bServer, PBOfficial* pOfficial );
	int Initialize();
	CTemplateOfficial()
	{
		Initialize();
	}
	~CTemplateOfficial() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= ��Ա���ñ�			 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/��Ա���ñ�		 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTemplateOfficialTable : public CTemplate
{
public:

	// FieldName: $��%dƷ��%d���ְID
	// FieldType: INT4
	// Type:	  TEMPPATH	

	int	mOfficial[ 12 ][ 6 ];

public:
	void SetFromPB( bool bServer, PBOfficialTable* pTable );
	void CreateTlvPB( bool bServer, PBOfficialTable* pTable );
	int Initialize();
	CTemplateOfficialTable()
	{
		Initialize();
	}
	~CTemplateOfficialTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ���辭���		## ģ������
// version	= 1					## �汾��
// path		= Config/���辭���	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateConstructExp : public CTemplate
{
public:


	// FieldName: ��%d����������һ���ľ�����ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,3000000000)
	int	mExp[ MAX_CONSTRUCT_LEVEL ];

	// FieldName: ��%d������ȶ�Ӧ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,3000000000)
	int	mBonus[ MAX_CONSTRUCT_LEVEL ];

public:
	void SetFromPB( bool bServer, PBConstructExp* pLevelExp );
	void CreateTlvPB( bool bServer, PBConstructExp* pLevelExp );
	int Initialize();
	CTemplateConstructExp()
	{
		Initialize();
	}
	~CTemplateConstructExp() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= PK���ӱ�			## ģ������
// version	= 1					## �汾��
// path		= Config/PK���ӱ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateAddPKTable : public CTemplate
{
public:

	// FieldName: ɱ�����˸ı���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mKFChangePower;	

	// FieldName: ɱ�������ı���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mKPChangePower;	

	// FieldName: ɱ����ս�ı���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mKWChangePower;	

	// FieldName: ��ɱ�����˸ı���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mDFChangePower;	

	// FieldName: ��ɱ�������ı���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mDPChangePower;	

	// FieldName: ��ɱ����ս�ı���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mDWChangePower;	

	// FieldName: ɱ�����˸ı��Ѻö�
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mKFChangeFriend;	

	// FieldName: ɱ�������ı��Ѻö�
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mKPChangeFriend;	

	// FieldName: ɱ����ս�ı��Ѻö�
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mKWChangeFriend;

	// FieldName: ɱ�����˸ı�PKֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mKFChangePK;	

	// FieldName: ɱ����ս�ı�PKֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mKWChangePK;

	// FieldName: ɱ����%d�������ı�PKֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mKPChangePK[ MAX_PEACE_TYPE ];

	// FieldName: ��%d���������Ѻö�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(-100000,100000)
	int	mPFriendMin[ MAX_PEACE_TYPE ];

	// FieldName: ��%d���������Ѻö�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(-100000,100000)
	int	mPFriendMax[ MAX_PEACE_TYPE ];

	// FieldName: ɱ�����˸ı�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mKFChangeHonor;	

	// FieldName: ɱ�������ı�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mKPChangeHonor;	

	// FieldName: ɱ����ս�ı�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(-10000,100000)
	int	mKWChangeHonor;

public:
	void SetFromPB( bool bServer, PBAddPKTable* pTable );
	void CreateTlvPB( bool bServer, PBAddPKTable* pTable );
	int Initialize();
	CTemplateAddPKTable()
	{
		Initialize();
	}
	~CTemplateAddPKTable() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��ͼ������		## ģ������
// version	= 1					## �汾��
// path		= Config/��ͼ������	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateMapTable : public CTemplate
{
public:

	// FieldName: ��%d��ͼ�ĵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mLevel[ MAX_MAP_NUM ];	

	// FieldName: ��%d��ͼ������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mPower[ MAX_MAP_NUM ];
public:
	void SetFromPB( bool bServer, PBMapTable* pTable );
	void CreateTlvPB( bool bServer, PBMapTable* pTable );
	int Initialize();
	CTemplateMapTable()
	{
		Initialize();
	}
	~CTemplateMapTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= Ⱥ���˺���		## ģ������
// version	= 1					## �汾��
// path		= Config/Ⱥ���˺���	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateMultiAttackTable : public CTemplate
{
public:

	// FieldName: ��%d��Ŀ����˺�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mReduce[ 20 ];
public:
	void SetFromPB( bool bServer, PBMultiAttackTable* pTable );
	void CreateTlvPB( bool bServer, PBMultiAttackTable* pTable );
	int Initialize();
	CTemplateMultiAttackTable()
	{
		Initialize();
	}
	~CTemplateMultiAttackTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��Ա����			## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/��Ա����		## ·��
// parent	= ���߻�����Ϣ		## ����ģ��
// ********************************************************************** //
class CTplItemVip : public CTplItem
{
public:

	enum EVipType
	{
		emVipNone = 0,	// �ǻ�Ա
		emVipNormal,	// ��ͨ��Ա
	};

	// FieldName: ��Ա����
	// FieldType: INT4
	// Type:	  COMBOENUM(EVipType)
	int		mVipLevel;

	// FieldName: ��Ա��Ч��(��λ:Сʱ)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mVipTime;
public:
	void SetFromPB( bool bServer, PBItemVip* pItem );
	void CreateTlvPB( bool bServer, PBItemVip* pItem );
	int Initialize();
	CTplItemVip() 
	{
		Initialize();
	}
	~CTplItemVip() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ϴ�����			## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/ϴ�����		## ·��
// parent	= ���߻�����Ϣ		## ����ģ��
// ********************************************************************** //
class CTplItemClean : public CTplItem
{
public:

	enum ECleanType
	{
		emTypeNone = 0,		// ��Ч����
		emTypeSkill,		// ϴ���ܵ�
		emTypePotential,	// ϴǱ�ܵ�
		emTypeTalent,		// ϴ�컯��
	};

	// FieldName: ϴ������
	// FieldType: INT4
	// Type:	  COMBOENUM(ECleanType)
	int		mCleanType;

	// FieldName: ϴ��ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mCleanLevel;

	// FieldName: ��������С��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mStep;
public:
	void SetFromPB( bool bServer, PBItemClean* pItem );
	void CreateTlvPB( bool bServer, PBItemClean* pItem );
	int Initialize();
	CTplItemClean() 
	{
		Initialize();
	}
	~CTplItemClean() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //  

// ********************************************************************** //
// BEGINMAKE
// virtual	= false						## �������ɵ����ݿ���
// name		= ��������ع���Ʒ			## ģ������
// version	= 1							## �汾��
// path		= ��Ʒ/��������ع���Ʒ		## ·��
// parent	= ���߻�����Ϣ				## ����ģ��
// ********************************************************************** //
class CTplLeagueBag : public CTplItem
{
public:
	enum ELeagueBagType
	{
		LEAGUEBAG_FAMILY = 0,		// �����ع���Ʒ
		LEAGUEBAG_CORPS	 = 1,		// �����ع���Ʒ		
	};
public:
	class CLeagueItemInfo 
	{
	public:
		int mItemID;
		int mItemNum;
		int	mProbality;				
	};
	
	// FieldName: �ع���Ʒ����
	// FieldType: INT4
	// Type:	  COMBOENUM(ELeagueBagType)
	int		mLeagueBagType;

	// FieldName: �һ���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mExchangeTableID;
	
	// FieldName: ��%d����Ʒ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	
	// FieldName: ��%d����Ʒ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	
	// FieldName: ��%d����Ʒ�ĵ����ɸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)			
	CLeagueItemInfo mLeagueInfo[MAX_LEAGUEITEMINBAG];
	
	// FieldName: ��Ʒ�ܹ�ʹ�õĵ�ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mMapID;
	
	// FieldName: ��Ʒ�ܹ�ʹ�õĺ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mPosX;
	
	// FieldName: ��Ʒ�ܹ�ʹ�õ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int		mPosY;
	
public:
	void SetFromPB( bool bServer, PBLeagueBag* pItem );
	void CreateTlvPB( bool bServer, PBLeagueBag* pItem );
	int Initialize();
	CTplLeagueBag()
	{
		Initialize();
	}
	~CTplLeagueBag() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��ȡ				## ģ������
// version	= 1					## �汾��
// path		= ��Ʒ/��ȡ			## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateAwardInfo : public CTemplate
{
public:

	// FieldName: $��ȡ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char	mName[ STRING32 ];	

	// FieldName: $��ȡ����
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char	mDesc[ STRING256 ];

	// FieldName: ��%d����ƷID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mItemID[ 3 ];

	// FieldName: ��%d����Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mItemNum[ 3 ];

	// FieldName: ��ӵ�BUFF
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mBuffID;

	// FieldName: ÿ�տ���ȡ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int		mTimes;

	// FieldName: ��Ҫ��NPC
	// FieldType: INT4
	// Type:	  TEMPPATH
	int		mNpcID;

	// FieldName: ��Ҫ�Ĺ���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(ȫ��=-2,��=-1,����=0,�ڼ�=1,����=2,����=3,Ů��=4)
	int		mCountry;

	// FieldName: �Ǽ��������ȡ
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int		mNoFamily;

public:
	void SetFromPB( bool bServer, PBAwardInfo* pInfo );
	void CreateTlvPB( bool bServer, PBAwardInfo* pInfo );
	int Initialize();
	CTemplateAwardInfo()
	{
		Initialize();
	}
	~CTemplateAwardInfo() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �������ñ�		## ģ������
// version	= 1					## �汾��
// path		= Config/�������ñ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateMatrixTable : public CTemplate
{
public:

	// FieldName: ��%d�������ĵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mLevel[ MAX_MATRIX_LEVEL ];	

	// FieldName: �������ĵȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMaxLimit;	

	// FieldName: �����ߵĵȼ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMinLimit;

	// FieldName: ��%d����%d�ִ���������Ʒ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mMasterItemID[ MAX_MATRIX_LEVEL ][ MAX_MASTER_AWARD_NUM ];

	// FieldName: ��%d����%d�ִ���������Ʒ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMasterItemNum[ MAX_MATRIX_LEVEL ][ MAX_MASTER_AWARD_NUM ];

	// FieldName: ��%d��ϵͳ�ʼ���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mMailID[ MAX_MATRIX_LEVEL ];

	// FieldName: ��ʽ���ӵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mFormalLevel;

	// FieldName: ��ʦ�ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mEducatedLevel;

	// FieldName: ��ʦ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mEnterLimit;

	// FieldName: �����Ҫ��Ʒ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mRemoveItem;

	// FieldName: �����Ҫ��Ǯ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mRemoveMoney;

	// FieldName: �������ְٷֱ�1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mFormalPercent;

	// FieldName: �������ְٷֱ�2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mEducatedPercent;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int		mReturnLimit;

	// FieldName: �����ж�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mAlterMax;

	// FieldName: �����ж�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mAlterMin;

	// FieldName: �����ʼ���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mReturnMailID;

	// FieldName: ��%d����%d�ֵ��ӽ�����Ʒ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int		mSlaveItemID[ MAX_MATRIX_LEVEL ][ 15 ];

	// FieldName: ��%d����%d�ֵ��ӽ�����Ʒ�ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mSlaveItemNum[ MAX_MATRIX_LEVEL ][ 15 ];

	// FieldName: �����ж�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mAlterAll;

	// FieldName: �����ж�Ĭ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)
	int		mAlterDefault;

	// FieldName: ͽ���ʼ���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int		mSlaveMailID;

public:
	void SetFromPB( bool bServer, PBMatrixTable* pTable );
	void CreateTlvPB( bool bServer, PBMatrixTable* pTable );
	int Initialize();
	CTemplateMatrixTable()
	{
		Initialize();
	}
	~CTemplateMatrixTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false						## �������ɵ����ݿ���
// name		= ���ϵͳ���ñ�			## ģ������
// version	= 1							## �汾��
// path		= Config/���ϵͳ���ñ�		## ·��
// parent	=							## ����ģ��
// ********************************************************************** //
class CTemplateMarriageConfig : public CTemplate
{

public:
	class CWeddingInfo
	{
		public:			
			int mWeddingLength;			// ����Ļ���ʱ��(����)
			int mMoneyNeeded;			// �������
			int mDelayMoneyNeeded;		// �ӳ�����ÿ������Ҫ�ķ���
			int mWeddingRedstoneID;		// �����ڵ�ID
			int mWeddingHallRedstoneID;	// ���õ��ڵ�ID			
			int mWeddingHallMapID;		// ���õĵ�ͼID
			int mInvitationCardID;		// npc���͵�������ID
			int mInvitationCardNum;		// npc���͵�����������
			int mMaleKeepsakeID;		// npc���͵��з�����ID
			int mFemaleKeepsakeID;		// npc���͵�Ů������ID
			int mPosX;					// ��Ҵ��͵����õ�x����
			int mPosY;					// ��Ҵ��͵����õ�y����
			int mMaleKeepsakeTwo;		// npc���͵ĵ�2���з�����ID
			int mFemaleKeepsakeTwo;		// npc���͵ĵ�2��Ů������ID			
			int mMaleKeepsakeThree;		// npc���͵ĵ�3���з�����ID
			int mFemaleKeepsakeThree;	// npc���͵ĵ�3��Ů������ID	
			int mMaleBufferID;			// ���ɱ���buff��ģ��ID					
			int mFemaleBufferID;		// �������buff��ģ��ID	
			int mMaleItemID;			// ���ɱ�����Ʒ��ID
			int mFemaleItemID;			// ���������Ʒ��ID			
			int mGroomPosX;				// ���ɰ���ʱ����λ�õĺ�����
			int mGroomPosY;				// ���ɰ���ʱ����λ�õ�������
			int mBridePosX;				// �������ʱ����λ�õĺ�����
			int mBridePosY;				// �������ʱ����λ�õ�������
			int mGroomBufferID;			// ���ɱ���buff��ģ��ID
			int mBrideBufferID;			// �������buff��ģ��ID	
			int mMarriageItemID;		// ������ID
			int mWeddingScroll;			// ���²��������Ҫ�ĵ���			
	};		
	
	class CKeepsnakeInfo
	{
		public:
			int mKeepsakeID;			// ����ID
			int mEquipID;				// ����һ���װ����ģ��ID
	};
public:
	// FieldName: ������͵ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,160)		
	int mMarriageLevel;
	
	// FieldName: �����Ҫ���ĵİ�֤��Ǯ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000000)		
	int mMarriageMoney;		

	
	// FieldName: ��%d�ֹ�ģ����Ļ���ʱ��(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)		
	
	// FieldName: ��%d�ֹ�ģ����Ļ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000000)			

	// FieldName: ��%d�ֹ�ģ�����ӳ�����ÿ������Ҫ�ķ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)				


	// FieldName: ��%d�ֹ�ģ����Ļ����ڵ�ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)				
	
	// FieldName: ��%d�ֹ�ģ��������õ��ڵ�ID			
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ��������õ�ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ�����npc���͵�������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	
	// FieldName: ��%d�ֹ�ģ�����npc���͵�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)					

	// FieldName: ��%d�ֹ�ģ�����npc���͵��з�����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)						
	
	// FieldName: ��%d�ֹ�ģ�����npc���͵�Ů������ID		
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ���������õĺ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ���������õ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ����npc���͵ĵ�2���з�����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ����npc���͵ĵ�2��Ů������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ����npc���͵ĵ�3���з�����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	

	// FieldName: ��%d�ֹ�ģ����npc���͵ĵ�3��Ů������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ�������ɱ���buff��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ�����������buff��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ�������ɱ�����Ʒ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ�������������Ʒ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ�������ɰ���ʱ����λ�õĺ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ�������ɰ���ʱ����λ�õ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ�����������ʱ����λ�õĺ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	

	// FieldName: ��%d�ֹ�ģ�����������ʱ����λ�õ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ�������ɱ���buff��ģ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ�����������buff��ģ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ��������Ҫ�ĵ���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: ��%d�ֹ�ģ���񲹰�������Ҫ�ĵ���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
		
	CWeddingInfo mWeddinInfo[MAX_WEDDING_MODULENUM];
	
	// FieldName: ��%d�й�ģ����ĵ�%d��npc��ģ��ID		
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)						
	int mWeddingNpc[MAX_WEDDING_MODULENUM][MAX_WEDDING_NPCNUM];
	
	// FieldName: Ů�����õĵ�%d�������ID	
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	
	// FieldName: Ů�����õĵ�%d������һ����ɵ�װ����ID	
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)		
	CKeepsnakeInfo mFemaleKeepsakeInfo[MAX_WEDDING_KEEPSNAKENUM];
	
	// FieldName: �з����õĵ�%d�������ID	
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	

	// FieldName: �з����õĵ�%d������һ����ɵ�װ����ID	
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)		
	CKeepsnakeInfo mMaleKeepsakeInfo[MAX_WEDDING_KEEPSNAKENUM];
	
	// FieldName: �����ô����ĵ�ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int mMapID;
	
	// FieldName: �����ô����ĵ�ͼ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int mPosX;
	
	// FieldName: �����ô����ĵ�ͼ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int mPosY;
	
	// FieldName: �����Ҫ�ĵ���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int mDivorceItemID;
	
	// FieldName: ����ȡ�ĳƺ�ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int mMarriageTitleID;
	
	// FieldName: �����л���ʱϵͳ���ŵ��з�����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int mMaleKeepsakeID;
	
	// FieldName: �����л���ʱϵͳ���ŵ�Ů������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int mFemaleKeepsakeID;
	
	// FieldName:  �����л���ʱϵͳ���ŵ�����ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int mInvitationID;
	
	// FieldName:  �����л���ʱϵͳ���ŵ���������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int mInvitationNum;
	
	// FieldName:  �����л���ʱϵͳ���ŵ����ɱ�����Ʒ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int mMaleItemID;			
	
	// FieldName:  �����л���ʱϵͳ���ŵ����������Ʒ��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)			
	int mFemaleItemID;	
	
	// FieldName:  ���������ʱ����buff��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)			
	int mBaitangBuffID;		
	
	// FieldName: �����Ҫ�Ļ�������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)			
	int mBasicMarriageItem;		
	
	// FieldName: �����Ҫ�Ļ�����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)			
	int mBasicMarriageItemNum;		
	
	// FieldName: ���npc���ڵĵ�ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)			
	int mMarriageNpcMapID;		
	
	// FieldName: ���npc���ڵĵ�ͼ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)			
	int mMarriageNpcPosX;		
	
	// FieldName: ���npc���ڵĵ�ͼ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)			
	int mMarriageNpcPosY;		

	// FieldName: ���ܶ���ֵ(�ﵽ����ֵʱ��Ҫ��ʯͷ����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)			
	int mMarriageIntimacy;		

	// FieldName: ���ܶ��㹻ʱ��Ҫ��ʯͷ���� 
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)			
	int mIntimacyItemNum;		
	
public:
	void SetFromPB( bool bServer, PBTemplateMarriageConfig* pTable );
	void CreateTlvPB( bool bServer, PBTemplateMarriageConfig* pTable );
	int Initialize();
	CTemplateMarriageConfig()
	{
		Initialize();
	}
	~CTemplateMarriageConfig() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ����					## ģ������
// version	= 1						## �汾��
// path		= ��Ʒ/����				## ·��
// parent	= ���߻�����Ϣ			## ����ģ��
// ********************************************************************** //
class CTplInvitation : public CTplItem
{	
public:
	// FieldName: �����һ����ɵ���ƷID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)			
	int mExchangeItemID;			

public:
	void SetFromPB( bool bServer, PBInvitation* pTable );
	void CreateTlvPB( bool bServer, PBInvitation* pTable );	
	int Initialize();
	CTplInvitation()
	{
		Initialize();
	}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ϵͳ����					## ģ������
// version	= 1						## �汾��
// path		= ��Ʒ/ϵͳ����				## ·��
// parent	= ���߻�����Ϣ			## ����ģ��
// ********************************************************************** //
class CTplSysInvitation : public CTplItem
{	
public:
	// FieldName: ϵͳ�����ܹ���ȡ������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)	
	int mInvitationID;	
public:
	void SetFromPB( bool bServer, PBSysInvitation* pTable );
	void CreateTlvPB( bool bServer, PBSysInvitation* pTable );	
	int Initialize();
	CTplSysInvitation()
	{
		Initialize();
	}
	~CTplSysInvitation() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ������������Ϣ		## ģ������
// version	= 1						## �汾��
// path		= Config/������������Ϣ	## ·��
// parent	=						## ����ģ��
// ********************************************************************** // 
class CTemplateProgressConfig:public CTemplate
{ 
public:
	class CProGressTime
	{
	public:
		int mFunctype;
		int mTime;
	};
public:
	enum Em_ProgressFunctype
	{
		PROGRESS_FUCTYPE_HORSE		=	0,		// ����
		PROGRESS_FUCTYPE_COLLECT	=	1,		// �ɼ�
		PROGRESS_FUCTYPE_TELEPORT	=	2,		// ���ͷ�
		PROGRESS_FUCTYPE_BOX		=	3,		// ����
		PROGRESS_FUCTYPE_TELESYMBOL	=	4,		// �س�ʯ
		PROGRESS_FUCTYPE_MINMAP		=	5,		// �ر�ͼ
		PROGRESS_FUCTYPE_TOKEN		=	6,		// ������
		PROGRESS_FUCTYPE_STONE		=	7,		// ��ʯ
		PROGRESS_FUCTYPE_CORPSBANNER=	8,		// ����
		PROGRESS_FUCTYPE_JUDIAN		=	9,		// �ݵ�
		PROGRESS_FUCTYPE_INSTONE	=	10,		// ��ʯ
	};
public:
	// FieldName: ��%d�ֹ��ܵĹ�������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����=0,�ɼ�=1,���ͷ�=2,����=3,�س�ʯ=4,�ر�ͼ=5,������=6,��ʯ=7,����=8,�ݵ�=9,��ʯ=10)	

	// FieldName: ��%d�ֹ��ܽ������Ķ���ʱ��(����)	
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)		
	CProGressTime mProgressInfo[MAX_PROGRESSFUNC_NUM];
public:
	void SetFromPB( bool bServer, PBProGressConfig* pTable );
	void CreateTlvPB( bool bServer, PBProGressConfig* pTable );	
	int Initialize();
	CTemplateProgressConfig() 
	{
		Initialize();
	}
	~CTemplateProgressConfig() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

enum EClearType
{
	CLEAR_ETH  = 0,			// ���ñ���
	CLEAR_DAY  = 1,			// ÿ�����
	CLEAR_WEEK = 2,			// ÿ�����	
};

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ʹ�ô�����		## ģ������
// version	= 1					## �汾��
// path		= Config/ʹ�ô�����	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateCountTable : public CTemplate
{
public:

	class CCount
	{
	public:
		int mCountType;
		int mCountTime;
		int mVipTime;
		int mClearType;
	};

	// FieldName: ��%d�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d��ÿ��һ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d��ÿ��VIP����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d�ֹ��ܵ��������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����=0,ÿ��=1,ÿ��=2)	
	CCount		mCountData[ MAX_COUNT_NUM ];

public:
	void SetFromPB( bool bServer, PBCountTable* pTable );
	void CreateTlvPB( bool bServer, PBCountTable* pTable );
	int Initialize();
	CTemplateCountTable()
	{
		Initialize();
	}
	~CTemplateCountTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ����ñ�		## ģ������
// version	= 1					## �汾��
// path		= Config/����ñ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateActivityConfig : public CTemplate
{
public:
	// FieldName: ����ʼ��ú�������(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mHydrangeaThrowTime;
	
	// FieldName: ��%d��ϲ�Ƕ�Ӧ�ı���buffer��ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mHydrangeaSugarID[MAX_HYDRANGEA_SUGARNUM];
	
	// FieldName: �����һ��ϲ��(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mSugarSpreadTime;
	
	// FieldName: ϲ�������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mSugarSpreadNum;
	
	// FieldName: ���������ʱ��(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mHydrangeaActivityTime;
	
	// FieldName: ��ҵĳ���ʱ��(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mHydrangeaHolderTime;
	
	// FieldName: ���������ʱ��(����)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mHydrangeaGrabTime;
	
	// FieldName: �ڵ�ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mHydrangeaRedStone;	
	
	// FieldName: ��������������ĵȼ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mHydrangeaExpTableID;	
	
	
	
	// FieldName: ��������˻�ȡ�ĳƺ�ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mPreliminaryTitleID;		
	
	// FieldName: ����ÿ����Ŀ�Ļ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mPreliminaryBaseScore;
	
	// FieldName: ���Լ�ʱ���%d+1���Ķ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mPreliminaryExtralScore[MAX_PRELIMINARY_TIMELYLISTNUM];
	
	// FieldName: ���Կ�ʼǰ��ý�����ʾ(��)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mPreliminaryTipsTime;
	
	// FieldName: ������Ŀ��ú�����Ŀ��(��)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mPreliminaryAnswerTime;
	
	// FieldName: ������Ŀ�𰸶�ú�����һ����(��)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mPreliminaryQuestionTime;
	
	// FieldName: ���Ե���Ŀ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mPreliminaryQuestionNum;
	
	// FieldName: ���Եȼ������ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int mPreliminaryExpTableID;	
	
	// FieldName: ����ʱ�����Ч����ʱ��֮��Ķһ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int mEffectiveOffLineExchangeRate;	
	
	// FieldName: ÿ���ת��Ϊ��Ч����ʱ����������ʱ��(Сʱ)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int mMaxOnLineEffectiveTime;
	
	// FieldName: �����Ч����ʱ��(Сʱ)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int mMaxEffectiveOffLineTime;
	
	// FieldName: ÿ���ת�����������ʱ��(Сʱ)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int mMaxOffLineTime;
	
	// FieldName:��ת��Ϊ���������ʱ������(Сʱ)
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int mOffLineTimeLimit;	
	
	// FieldName:  ��Ա����ʱ�����Ч����ʱ��֮��Ķһ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int mVipOffLineExchangeRate;		
public:
	void SetFromPB( bool bServer, PBActivityConfig* pTable );
	void CreateTlvPB( bool bServer, PBActivityConfig* pTable );	
	int Initialize();
	CTemplateActivityConfig() 
	{
		Initialize();
	}
	~CTemplateActivityConfig() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ϴ������Ʒ			## ģ������
// version	= 1						## �汾��
// path		= ��Ʒ/ϴ������Ʒ		## ·��
// parent	= ���߻�����Ϣ			## ����ģ��
// ********************************************************************** //
class CTplItemRefresh : public CTplItem
{											
public:
	// FieldName: ��ɫ����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=1,��=2,��=3,��=4)
	int			mColor;

	// FieldName: ���Ƶȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	int			mLevel;

	// FieldName: �޹���
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ��ָ��װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ������װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ������װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ������װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ������װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ��ͷ��װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ������װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ������װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ������װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ������װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ������װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ʱװ��װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: ����װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: �Ż���װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)

	// FieldName: �����װ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int			mLimitPos[ 16 ];
public:
	void SetFromPB( bool bServer, PBItemRefresh* pItem );
	void CreateTlvPB( bool bServer, PBItemRefresh* pItem );
	int Initialize();
	CTplItemRefresh()
	{
		Initialize();
	}
	~CTplItemRefresh() {}
};	
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** // 

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= �ټ�����Ʒ	## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/�ټ�����Ʒ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemSummon : public CTplItem
{
public:
	enum ESummon
	{
		SUMMON_NONE		=	0,		// ��
		SUMMON_SINGLE	=	1,		// ����
		SUMMON_FAMILY	=	2,		// ����
		SUMMON_CORPS	=	3,		// ����
		SUMMON_TEAM		=	4,		// ���
		SUMMON_MASTER	=	5,		// ʦ��
		SUMMON_SLAVE	=	6,		// ͽ��
	};
public:

	// FieldName: �ټ�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,����=1,����=2,����=3,���=4,ʦ��=5,ͽ��=6)
	int			mSummonType;

public:
	void SetFromPB( bool bServer, PBItemSummon* pItem );
	void CreateTlvPB( bool bServer, PBItemSummon* pItem );
	int Initialize();
	CTplItemSummon(){	Initialize();}
	~CTplItemSummon() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ֱ�����ñ�		## ģ������
// version	= 1					## �汾��
// path		= Config/ֱ�����ñ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateDirectTable : public CTemplate
{
public:
	// FieldName: ��%d��װ��%d�ǵõ���ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mDirectID[ 16 ][ 16 ];

	// FieldName: ��%d�ǵõ��ıس�ʯID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mLuckID[ 16 ];

	// FieldName: �õ�%d���ĸ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mLuckRate[ 3 ];

public:
	void SetFromPB( bool bServer, PBDirectTable* pTable );
	void CreateTlvPB( bool bServer, PBDirectTable* pTable );	
	int Initialize();
	CTemplateDirectTable() 
	{
		Initialize();
	}
	~CTemplateDirectTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ֱ����Ʒ		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/ֱ����Ʒ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemDirect : public CTplItem
{
public:

	// FieldName: ���Ƶȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			mLevel;

	// FieldName: �����Ǽ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			mStar;

public:
	void SetFromPB( bool bServer, PBItemDirect* pItem );
	void CreateTlvPB( bool bServer, PBItemDirect* pItem );
	int Initialize();
	CTplItemDirect(){	Initialize();}
	~CTplItemDirect() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ժ����Ʒ		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/ժ����Ʒ	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemGetStar : public CTplItem
{
public:

	// FieldName: ���Ƶȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			mLevel;

public:
	void SetFromPB( bool bServer, PBItemGetStar* pItem );
	void CreateTlvPB( bool bServer, PBItemGetStar* pItem );
	int Initialize();
	CTplItemGetStar(){	Initialize();}
	~CTplItemGetStar() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= �������鵤		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/�������鵤  ## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemExpContainer : public CTplItem
{
public:	   	
	// FieldName: ÿ�λ�ô�־������ֱ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mOgreExpRate;	
	
	// FieldName: �ܹ��洢�������ֵ
	// FieldType: INT8
	// Type:	  EDITNUMBER(0,100000000000000)
	unsigned long long			mMaxExp;
	
	// FieldName: ����洢��ʱ�ܹ�ת���ľ��鵤ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mExpPillsID;	
public:
	void SetFromPB( bool bServer, PBItemExpContainer* pItem );
	void CreateTlvPB( bool bServer, PBItemExpContainer* pItem );
	int Initialize();
	
	CTplItemExpContainer(){ Initialize(); }
	~CTplItemExpContainer(){}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= ���鵤		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/���鵤	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemExpPills : public CTplItem
{
public:

	// FieldName: �ܹ�ʹ�õ���͵ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mLevelLimit;
	
	// FieldName: ʹ�ú��ܹ���ȡ�ľ���ֵ
	// FieldType: INT8
	// Type:	  EDITNUMBER(0,100000000000000)
	unsigned long long			mExp;	

public:
	void SetFromPB( bool bServer, PBItemExpPills* pItem );
	void CreateTlvPB( bool bServer, PBItemExpPills* pItem );
	int Initialize();
	
	CTplItemExpPills(){ Initialize(); }
	~CTplItemExpPills(){ }
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= �����ĵ�		## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/�����ĵ�	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemExpTome : public CTplItem
{
public:

	// FieldName: ������Ҫ�ĵ�%d����ƷID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mOpenItemID[ 5 ];

	// FieldName: �ܹ�ʹ�õ���͵ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mLevelLimit;

	// FieldName: ʹ�ú��ܹ���ȡ�ľ���ֵ
	// FieldType: INT8
	// Type:	  EDITNUMBER(0,100000000000000)
	unsigned long long			mExp;	

public:
	void SetFromPB( bool bServer, PBItemExpTome* pItem );
	void CreateTlvPB( bool bServer, PBItemExpTome* pItem );
	int Initialize();

	CTplItemExpTome(){ Initialize(); }
	~CTplItemExpTome(){ }
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ��ս���ñ�		## ģ������
// version	= 1					## �汾��
// path		= Config/��ս���ñ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateWorldBattleConfig : public CTemplate
{
public:

	class CWarDate
	{
	public:
		int mDay;
		int mHour;
		int mMinute;
	};

	class CTax
	{
	public:
		int mTaxRate;
		int	mIncomeRate;
		int mLimit;
	};

	// FieldName: ������ʼ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����=0,��һ,�ܶ�,����,����,����,����)

	// FieldName: ������ʼʱ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ������ʼ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	CWarDate	mSubmitBegin;

	// FieldName: ��ս��ʼ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����=0,��һ,�ܶ�,����,����,����,����)

	// FieldName: ��ս��ʼʱ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��ս��ʼ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	CWarDate	mBattleBegin;

	// FieldName: ��ս������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����=0,��һ,�ܶ�,����,����,����,����)

	// FieldName: ��ս����ʱ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��ս������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	CWarDate	mBattleEnd;

	// FieldName: ��%d�ֹ�ս�ڵ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			mStoneID[ 10 ];

	// FieldName: ��ʼ��BUFFID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mInitBuffID;

	// FieldName: �������Դ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mFlagSource;

	// FieldName: ɱ�˵���Դ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mKillSource;

	// FieldName: ���콱��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mFlagBonus;

	// FieldName: ��%dս����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mPerNum[ 5 ];

	// FieldName: ��%dս����ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mMapID[ 5 ];

	// FieldName: ��%d�����������Ǯ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mSubmitMoney[ 160 ];

	// FieldName: �������Ƶȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mSubmitLevel;

	// FieldName: ��%d�������X
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mPosX[ 5 ];

	// FieldName: ��%d�������Y
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mPosY[ 5 ];

	// FieldName: ������ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mOutMapID;

	// FieldName: ������ͼ����X
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mOutPosX;

	// FieldName: ������ͼ����Y
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mOutPosY;

	// FieldName: ��%d��Ӫ������%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mFlagIndex[ 5 ][ 100 ];

	// FieldName: ���۽�����
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����=0,��һ,�ܶ�,����,����,����,����)

	// FieldName: ���۽���ʱ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ���۽�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	CWarDate	mBidEnd;

	// FieldName: ÿ�����ս��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mMaxWarHonor;

	// FieldName: ��%dְҵ�ĳƺ�%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mTitle[ 7 ][ 3 ];

	// FieldName: ��ʾ��ʼ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����=0,��һ,�ܶ�,����,����,����,����)

	// FieldName: ��ʾ��ʼʱ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��ʾ��ʼ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	CWarDate	mNoticeBegin;

	// FieldName: �ƺŵ���Чʱ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000000)
	int			mTitleValidTime;

	// FieldName: �ڵ�����X
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mStonePosX;

	// FieldName: �ڵ�����Y
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100000)
	int			mStonePosY;

	// FieldName: ��%d��˰��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��%d��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��%d������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)
	CTax		mTax[ 15 ];

	// FieldName: ��ʤ��˰�ʸı�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mWinTax;

public:
	void SetFromPB( bool bServer, PBWorldBattleConfig* pTable );
	void CreateTlvPB( bool bServer, PBWorldBattleConfig* pTable );
	int Initialize();
	CTemplateWorldBattleConfig()
	{
		Initialize();
	}
	~CTemplateWorldBattleConfig() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false			## �������ɵ����ݿ���
// name		= �Զ��ɼ�����	## ģ������
// version	= 1				## �汾��
// path		= ��Ʒ/�Զ��ɼ�����	## ·��
// parent	= ���߻�����Ϣ	## ����ģ��
// ********************************************************************** //

class CTplItemAutoCollect : public CTplItem
{
public:	
	
	class CDegreeInfo	
	{	
	public:							
		int		mValue;			// ��ұ�����������Ҫ��������ȵĲ�ֵ
		int		mProbality;		// �ڲ�ֵ��Χ�ڻ�ȡ�����ȵĸ���
		int		mDegreeValue;	// �ڲ�ֵ��Χ�ڻ�ȡ�����ȵ�ֵ
	};
	
	class CItemInfo
	{
	public:
		int	mItemID;		// ��ƷID
		int mItemNum;		// ��Ʒ����
		int mProbality;		// ��Ʒ�Ĳ�������
	};
public:
	// FieldName: ��%d�ֲ��ϵ���ƷID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)		
	
	// FieldName: ��%d�ֲ��ϵ���Ʒ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)		
	
	// FieldName: ��%d�ֲ��ϵ���Ʒ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)		
	CItemInfo mItemInfo[MAX_AUTOCOLLECT_MATERIALSNUM];	
	
	// FieldName: ���������ȺͲɼ���Ҫ�������ȵĵ�%d����ֵ����
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,1000) 


	// FieldName: ���������ȺͲɼ���Ҫ�������ȵĵ�%d����ֵ����Ļ�ȡ�����ȵĸ���
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,10000) 


	// FieldName: ���������ȺͲɼ���Ҫ�������ȵĵ�%d����ֵ����Ļ�ȡ�����ȵ�ֵ
	// FieldType: INT4	
	// Type:      EDITNUMBER(0,10000)	   
	CDegreeInfo mDegreeInfo[MAX_LIFESKILL_DEGREESTEP];
	
	// FieldName: �����ܹ�ʹ�õĵ�ͼID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mMapID;
	
	// FieldName: �����ܹ�ʹ�õĺ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mPosX;
	
	// FieldName: �����ܹ�ʹ�õ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mPosY;
	
	// FieldName: �����ܹ�ʹ�õľ���Ŀ���������Ч��Χ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mGrid;	
	
	// FieldName: �����ܹ�ʹ�õ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)
	int			mMaxUseTimes;
public:
	void SetFromPB( bool bServer, PBItemAutoCollect* pItem );
	void CreateTlvPB( bool bServer, PBItemAutoCollect* pItem );
	int Initialize();
	CTplItemAutoCollect(){Initialize();}
	~CTplItemAutoCollect() {}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// CFangCunTreeNode
// ********************************************************************** //

class CFangCunTreeNode
{
public:
	int		mSkillID;				// ����ID
	int		mMaxLevel;				// ���ȼ�( ����ܵ�Ͷ���� )
	int		mNeedSkillID[ 4 ];		// ��Ҫ��ǰ������
	int		mNeedSkillPoint[ 4 ];	// ��Ҫ��ǰ������Ͷ����
	int		mLevel;					// ��Ҫ����ҵȼ�
	int		mNeedBook;				// �Ƿ���Ҫ��Ӧ�ļ�����
	int		mStage;					// ��Ӧ�Ľ�
	int		mOrder;					// ��˳��

public:
	void SetFromPB( bool bServer, PBFangCunTreeNode* pNode );
	void CreateTlvPB( bool bServer, PBFangCunTreeNode* pNode );
};

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ������			## ģ������
// version	= 1					## �汾��
// path		= ����/������		## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateFangCunTree  : public CTemplate
{
public:
	// FieldName: ��%d�׵�%d�ּ���ID
	// FieldType: INT4
	// Type:	  SKILLPATH

	// FieldName: ��%d�׵�%d�����ȼ�( ����ܵ�Ͷ���� )
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��%d�׵�%d����Ҫ��ǰ������1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��%d�׵�%d����Ҫ��ǰ������2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��%d�׵�%d����Ҫ��ǰ������3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��%d�׵�%d����Ҫ��ǰ������4
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��%d�׵�%d����Ҫ��ǰ������Ͷ����1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��%d�׵�%d����Ҫ��ǰ������Ͷ����2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��%d�׵�%d����Ҫ��ǰ������Ͷ����3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��%d�׵�%d����Ҫ��ǰ������Ͷ����4
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,120)

	// FieldName: ��%d�׵�%d����Ҫ����ҵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,160)

	// FieldName: ��%d�׵�%d����Ҫ�ļ�����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	// FieldName: ��%d�׵�%d�ֶ�Ӧ�Ľ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,160)

	// FieldName: ��%d�׵�%d�ֽ�˳��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000000)

	CFangCunTreeNode	mNode[ 10 ][ 5 ];

public:
	void SetFromPB( bool bServer, PBFangCunTree* pSkillTree );
	void CreateTlvPB( bool bServer, PBFangCunTree* pSkillTree );
	int Initialize();
	CTemplateFangCunTree() 
	{
		Initialize();
	}
	~CTemplateFangCunTree() {}
};


// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= �컯���				 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/�컯���		 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //

class CTemplateTalentStage : public CTemplate
{
public:
	class CStage
	{
	public:
		int			mStageID;
		int			mNext[ STEP_SWITCH ];
		int			mLayer;
	};

	// FieldName: ��%d����ױ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d����׵ĵ�1����һ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d����׵ĵ�2����һ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d����׵ĵ�3����һ���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	// FieldName: ��%d��������ڵĲ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000)

	CStage	mStage[ 8 ];	

public:
	void SetFromPB( bool bServer, PBTemplateTalentStage* pTalent );
	void CreateTlvPB( bool bServer, PBTemplateTalentStage* pTalent );
	int Initialize();
	CTemplateTalentStage()
	{
		Initialize();
	}
	~CTemplateTalentStage() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= ת��Ӫ				 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/ת��Ӫ			 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTemPlateChangeCampCfg: public CTemplate
{

public:
	// FieldName: ת��Ӫ����id
	// FieldType: INT4
	// Type:      TEMPPATH
	int  m_itemId; 

	// FieldName: ת��Ӫ������Ӫ���id
	// FieldType: INT4
	// Type:      TEMPPATH
	int  m_giftId;

	// FieldName: cdʱ�䵥λ��
	// FieldType: INT4
	// Type:      EDITNUMBER(0,30)
	unsigned int m_cd_time; 
public:
	void SetFromPB( bool bServer, PBItemChangeCamp* changeCampTable);
	void CreateTlvPB( bool bServer, PBItemChangeCamp* changeCampTable);
	int Initialize();
	CTemPlateChangeCampCfg() 
	{
		Initialize();
	}
	~CTemPlateChangeCampCfg(){}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					 ## �������ɵ����ݿ���
// name		= ����ת������		 ## ģ������
// version	= 1						 ## �汾��
// path		= Config/����ת������	 ## ·��
// parent	=						 ## ����ģ��
// ********************************************************************** //
class CTemplateComRuneCfg: public CTemplate
{
public:
	// FieldName: ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int  m_upRuneRand;

	// FieldName: �����������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10)
	int  m_max;

	// FieldName: ��С��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10)
	int  m_min;

public:
	class CRuneRand
	{
	public:
		int  m_whitenum;
		int  m_bluenum;
		int  m_purplenum;
		int  m_rand;
		int  m_money;;
		int  m_runeLevel;
	};

	// FieldName: %d��ɫ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)

	// FieldName: %d��ɫ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)

	// FieldName: %d��ɫ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10)

	// FieldName: ��%d��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)

	// FieldName: ��%d�������Ľ�Ǯ
	// FieldType: INT4
	// Type:      EDITNUMBER(0,2000000000)

	// FieldName: ��%d������ĵȼ�
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10)
	CRuneRand     m_Rune[MAX_RUNECOMTYPE];


public:
	void SetFromPB( bool bServer, PBComRuneConfig* changeCampTable);
	void CreateTlvPB( bool bServer, PBComRuneConfig* changeCampTable);
	int Initialize();
	CTemplateComRuneCfg() 
	{
		Initialize();
	}
	~CTemplateComRuneCfg(){}
};
// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= �������ñ�		## ģ������
// version	= 1					## �汾��
// path		= Config/�������ñ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateAccuseConfig : public CTemplate
{
public:

	// FieldName: ��ʼ����ʱ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,23)
	int			mAccuseBeginHour;

	// FieldName: ��ʼ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,59)
	int			mAccuseBeginMinute;

	// FieldName: ��������ȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,160)
	int			mAccuseLevel;

	// FieldName: ��������ʱ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,23)
	int			mAccuseEndHour;

	// FieldName: ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,59)
	int			mAccuseEndMinute;

	// FieldName: �������ѽ��
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mAccuseMoney;

	// FieldName: ������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,100)
	int			mAccusePerson;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int			mAccusePercent;

	// FieldName: ʧ�ܽ�������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mAwardPower;

	// FieldName: ������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mGateNum;

	// FieldName: ������������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mFlagNum;

	// FieldName: ���Ż������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mGatePower;

	// FieldName: ����������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mFlagPower;

	// FieldName: ��ʾ����ʱ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,23)
	int			mAccuseNoticeHour;

	// FieldName: ��ʾ������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,59)
	int			mAccuseNoticeMinute;

	// FieldName: ��ʾ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mNoticePower;

	// FieldName: ���Ų���1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mGateParam1;

	// FieldName: �������1
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mFlagParam1;

	// FieldName: ���Ų���2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mGateParam2;

	// FieldName: �������2
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mFlagParam2;

	// FieldName: ���Ų���3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mGateParam3;

	// FieldName: �������3
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mFlagParam3;

	// FieldName: ���轱���ӳ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mLWPercent;

public:
	void SetFromPB( bool bServer, PBAccuseConfig* pTable );
	void CreateTlvPB( bool bServer, PBAccuseConfig* pTable );
	int Initialize();
	CTemplateAccuseConfig()
	{
		Initialize();
	}
	~CTemplateAccuseConfig() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ȫ�ֵ�ͼ���ñ�	## ģ������
// version	= 1					## �汾��
// path		= Config/ȫ�ֵ�ͼ���ñ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateGlobalMapConfig : public CTemplate
{
public:
	// FieldName: ȫ�ֵ�ͼ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mMapID;

	// FieldName: ��Ҫ��buffid
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mBuffID;

	// FieldName: ��������
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mLimit;

	// FieldName: ������ͼ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mOutMap;

	// FieldName: ����X
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mOutX;

	// FieldName: ����Y
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mOutY;

	// FieldName: ���ս����buffID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int			mEscapeBuffID;
public:
	void SetFromPB( bool bServer, PBGlobalMapConfig* pTable );
	void CreateTlvPB( bool bServer, PBGlobalMapConfig* pTable );
	int Initialize();
	CTemplateGlobalMapConfig()
	{
		Initialize();
	}
	~CTemplateGlobalMapConfig() {}
};


// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ����BOSS��		## ģ������
// version	= 1					## �汾��
// path		= Config/����BOSS��	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateCorpsBOSSTable : public CTemplate
{
public:

	// FieldName: ��%d��BOSS ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mBOSSID[ MAX_CORPSBOSSNUM ];	

	// FieldName: ��%d��ϡ��BOSS ID
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int		mHardBOSSID[ MAX_CORPSBOSSNUM ];

	// FieldName: ��%d�����ŵ�����ֵ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int		mValueLimit[ 6 ];

	// FieldName: ��%d��boss�ĵ�������
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char	mDropDesc[MAX_CORPSBOSSNUM][ STRING256 ];

	// FieldName: ��%d��ϡ��boss�ĵ�������
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char	mHardDropDesc[MAX_CORPSBOSSNUM][ STRING256 ];

	// FieldName: ��%d��boss���ٻ�������͵ȼ�����
	// FieldType:	INT4
	// Type:	EDITNUMBER(0,200)
	int		mSummonMinLevel[ MAX_CORPSBOSSNUM ];

	// FieldName: ��%d��ϡ��boss���ٻ�������͵ȼ�����
	// FieldType:	INT4
	// Type:	EDITNUMBER(0,200)
	int		mHardSummonMinLevel[ MAX_CORPSBOSSNUM ];

	// FieldName: ��%d��boss���ٻ������������
	// FieldType: INT4
	// Type:	EDITNUMBER(0,100000)
	int		mSummonMinValue[ MAX_CORPSBOSSNUM ];

	// FieldName: ��%d��ϡ��boss���ٻ������������
	// FieldType: INT4
	// Type:	EDITNUMBER(0,100000)
	int		mHardSummonMinValue[ MAX_CORPSBOSSNUM ];

public:
	void SetFromPB( bool bServer, PBCorpsBOSS* pTable );
	void CreateTlvPB( bool bServer, PBCorpsBOSS* pTable );
	int Initialize();
	CTemplateCorpsBOSSTable()
	{
		Initialize();
	}
	~CTemplateCorpsBOSSTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ���߾������ñ�	## ģ������
// version	= 1					## �汾��
// path		= Config/���߾������ñ�	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateOffLineExpConfig : public CTemplate
{
public:
	// FieldName:�����߻��һ�ξ������С��λ���룩
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int mOffLineUnit;	

	// FieldName:�����߻��һ�ξ������ֵ%d
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int mOffLineExp[ TMP_MAX_GRADE ];

	// FieldName:�����߻�þ���ĵȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000)
	int mOffLineLevel;

	// FieldName: ��%d���ľ�������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,1000000000)
	int mExpLimit[ TMP_MAX_GRADE ];

	// FieldName:�����߻�þ���ı���
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,10000)
	int mOffLinePercent;

public:
	void SetFromPB( bool bServer, PBOffLineExpConfig* pTable );
	void CreateTlvPB( bool bServer, PBOffLineExpConfig* pTable );
	int Initialize();
	CTemplateOffLineExpConfig()
	{
		Initialize();
	}
	~CTemplateOffLineExpConfig() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false				## �������ɵ����ݿ���
// name		= ����������		## ģ������
// version	= 1					## �汾��
// path		= Config/����������	## ·��
// parent	=					## ����ģ��
// ********************************************************************** //
class CTemplateRepeFameTable : public CTemplate
{
public:
	enum EM_REPETYPE
	{		
		REPETYPE_NANTIANMEN		=	0,			// ��ս������
		REPETYPE_LINGYUNDU		=	1,			// ���ƶ�
		REPETYPE_QITIAN			=	2,			// �����ս
		REPETYPE_LIANHUADONG	=	3,			// ������
		REPETYPE_HUANGFENGDONG	=	4,			// �Ʒ綴
		REPETYPE_YUHUAYUAN		=	5,			// ����԰
		REPETYPE_DAYANTA		=	6,			// ������
		REPETYPE_YUNXIAOTA10	=	7,			// ������10��
		REPETYPE_YUNXIAOTA20	=	8,			// ������20��
		REPETYPE_YUNXIAOTA30	=	9,			// ������30��
		REPETYPE_YUNXIAOTA40	=	10,			// ������40��
		REPETYPE_YUNXIAOTA50	=	11,			// ������50��
		REPETYPE_WUDIDONG1		=	12,			// �޵׶�1
		REPETYPE_WUDIDONG2		=	13,			// �޵׶�2
		REPETYPE_WUDIDONG3		=	14,			// �޵׶�3
		REPETYPE_WUDIDONG4		=	15,			// �޵׶�4
		REPETYPE_PINXIANTAO		=	16,			// Ʒ����
		REPETYPE_TENGYUN		=	17,			// ���ƴ�ս
		REPETYPE_LONGGONG1		=	18,			// ����1
		REPETYPE_LONGGONG2		=	19,			// ����2
		REPETYPE_LONGGONG3		=	20,			// ����3
		REPETYPE_PANTAO1		=	21,			// ���1
		REPETYPE_PANTAO2		=	22,			// ���2
		REPETYPE_PANTAO3		=	23,			// ���3
	}; 
public:

	
	// FieldName: ��%d����������
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��������=1,��������=2,��������=3)
	int		mFameType[ 50 ];	

	// FieldName: ��%d����������ֵ
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int		mFameValue[ 50 ];

	// FieldName: ��%d������Ʒ����
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int		mItemValue[ 50 ];

	// FieldName: ������ƷID
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int		mCombatItemID;

	// FieldName: ������ƷID
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int		mRepeItemID;

	// FieldName: ������ƷID
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int		mCommonItemID;

	// FieldName: ��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int		mCombatLimit;

	// FieldName: ��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int		mRepeLimit;

	// FieldName: ��������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,10000000)
	int		mCommonLimit;
	
public:
	void SetFromPB( bool bServer, PBRepeFameTable* pTable );
	void CreateTlvPB( bool bServer, PBRepeFameTable* pTable );
	int Initialize();
	CTemplateRepeFameTable() 
	{
		Initialize();
	}
	~CTemplateRepeFameTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= �������ñ�			## ģ������
// version	= 1						## �汾��
// path		= Config/�������ñ�		## ·��
// parent	=						## ����ģ��
// ********************************************************************** //
class CTplCastingSpiritTable :	public CTemplate
{
public:
	// FieldName: ��%d����λ����״̬
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=0,��=1)
	int				m_anIsOpen[MAX_CASTINGSPIRIT_POSITION];

	// FieldName: $��%d����λ����
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char			m_acPositionName[MAX_CASTINGSPIRIT_POSITION][STRING32];

	// FieldName: $��%d����λ����
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char			m_acPositionDesc[MAX_CASTINGSPIRIT_POSITION][STRING256];

	// FieldName: $��%d��ϵ������
	// FieldType: STRING32
	// Type:	  EDITSTRING
	char			m_acTypeName[MAX_CASTINGSPIRIT_TYPE][STRING32];

	// FieldName: $��%d��ϵ������
	// FieldType: STRING256
	// Type:	  EDITSTRING
	char			m_acTypeDesc[MAX_CASTINGSPIRIT_TYPE][STRING256];

	// FieldName: ��%d����������Ҫ��������ID
	// FieldType: INT4
	// Type:      EDITNUMBER(0,100000)
	int				m_anSpiritItem[MAX_CASTINGSPIRIT_SLOT];

	// FieldName: ��%d����������Ҫ�����������
	// FieldType: INT4
	// Type:      EDITNUMBER(0,100)
	int				m_anSpiritItemNum[MAX_CASTINGSPIRIT_SLOT];

	// FieldName: ��������%d��������Ҫ�ķǰ󶨽�
	// FieldType: INT4
	// Type:      EDITNUMBER(0,1000000000)
	int				m_anUpgradeMoney[MAX_SPIRITITEM_GRADE];

	// FieldName: ��%d������������Ҫ�ķǰ󶨽�
	// FieldType: INT4
	// Type:      EDITNUMBER(0,1000000000)
	int				m_anDowngradeMoney[MAX_SPIRITITEM_GRADE];

	// FieldName: ������Ҫ����Ʒ
	// FieldType: INT4
	// Type:      EDITNUMBER(0,100000)
	int				m_nUpgradeItem;

	// FieldName: ������Ҫ����Ʒ
	// FieldType: INT4
	// Type:      EDITNUMBER(0,100000)
	int				m_nDowngradeItem;

public:
	void SetFromPB( bool bServer, PBCastingSpiritTable* pTable );
	void CreateTlvPB( bool bServer, PBCastingSpiritTable* pTable );
	int Initialize();
	CTplCastingSpiritTable() 
	{
		Initialize();
	}
	~CTplCastingSpiritTable() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //


// ********************************************************************** //
// BEGINMAKE
// virtual	= false					## �������ɵ����ݿ���
// name		= ����					## ģ������
// version	= 1						## �汾��
// path		= ��Ʒ/����				## ·��
// parent	= ���߻�����Ϣ			## ����ģ��
// ********************************************************************** //
class CTplSpiritItem : public CTplItem
{
public:
	// FieldName: ����
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,8)
	int			m_nGrade;

	// FieldName: ����ȼ�
	// FieldType: INT4
	// Type:	  COMBOSINGLE(��=1,��=2,��=3,��=4)
	int			m_nColorGrade;

	// FieldName: ϵ��
	// FieldType: INT4
	// Type:	  COMBOSINGLE(����=0,����=1,���=2)
	int			m_nSpiritType;

	// FieldName: ʹ�����Ƶȼ�
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,160)
	int			m_nLevelLimit;

	// FieldName: ����������ֵ
	// FieldType: INT4
	// Type:	  EDITNUMBER(0,1000000000)
	int			m_nEffectPoint;

public:
	void SetFromPB( bool bServer, PBSpiritItem* pItem );
	void CreateTlvPB( bool bServer, PBSpiritItem* pItem );
	int Initialize();
	CTplSpiritItem() 
	{
		Initialize();
	}
	~CTplSpiritItem() {}
};

// ********************************************************************** //
// ENDMAKE
// ********************************************************************** //

// ********************************************************************** //
// CDataStatic
// ********************************************************************** //

template< int RANK, int LEVEL, int SIZE >
class CProduceTable
{
public:
	int mTable[ RANK ][ LEVEL ][ SIZE ];
};

struct CComposeInfo
{
	int mComposeID[MAX_LIFESKILL_COMPOSENUM];
	int mComposeNum;
	int mComposeType;
};

struct CCompose
{
	int mComposeID;				// ģ��ID
	int mDegreeValue;			// ѧϰ��Ҫ��������
};

class CLifeSkillInfo
{
public:
	void* spLifeSkillTable;							// ����ܱ�	
	CComposeInfo mComposeInfo[MAX_COMPOSEkIND_NUM];	// �䷽��Ϣ
	int mComposeKindNum;	
	CCompose mCompose[MAX_LIFESKILL_COMPOSENUM];
	int mComposeNum;
public:
	CLifeSkillInfo( )
	{
		Initialize();
	}
	~CLifeSkillInfo(){  }
public:
	int Initialize( );
	
public:
	int InsertComposeInfo( int nComposeID, int nComposeKind, int nDegreeValue, int nComposeType );
	int InsertCompose( int nComposeID, int nDegreeValue );
};

class CDataStatic
{
public:
	static CTemplate* spTemplate[ MAX_TEMPLATE ];							// ģ���
	static void* spLevelExp;											// �ȼ������
	static void* spData;												// ��ֵ�������ȼ�����ӣ�
	static void* spUpgrade;												// װ��������
	static void* spSkill[ MAX_SKILL ][ MAX_LEVEL ];						// ���ܱ�
	static void* spOpenSlot;											// ���۱�
	static void* spProSuit;												// ��������װ
	static void* spProExp;												// �����ȼ��ľ���
	static void* spBeginner;											// ��������
	static void* spDropLevel;											// ����װ���ȼ���
	static void* spMetierProperty[ MAX_METIER ][ PROPERTY_OPTION ];		// (ְҵ)���Ա�
	static void* spLevelProperty[ PROPERTY_OPTION ];					// (�ȼ�)���Ա�
	static void* spHonorToExp;											// ��ѫ���黻���
	static void* spHonorObtain;											// �����ñ�
	static void* spReliveTable;											// ����ѱ�
	static void* spQuestionExpTable;									// ����ȼ������
	static void* spRedStoneExpTable;									// �ڵ��ȼ������ 
	static void* spBindChargeTable;										// �󶨻��ѱ�
	static void* spPKValueTable;										// PK��Χ��
	static void* spTitleManager;										// �Q̖ϵ�y����
	static void* spTalent;												// �컯��
	static void* spMultiBuff;											// buff���
	static void* spCDGroup;												// ��ȴʱ��
	static void* spLight;												// ��������
	static void* spApConfig;											// �������ñ�
	static void* spWizard;												// �Ż�������
	static void* spJudgeConfig;											// �������ñ�
	static int spOffical[ OFFICAL_NUM ][ MAX_POWER ];					// ��ְ���ܱ�
	static void* spOfficalTable;										// ��ְ����
	static int spKing[ MAX_POWER ];										// ��������
	static void* spConstructExp;										// ����ȱ�
	static void* spAddPKTable;											// PK���ӱ�
	static void* spMapTable;											// ��ͼ������
	static void* spMultiAttackTable;									// Ⱥ���˺���
	static void* spDoubleTimeTable;										// ˫��ʱ���
	static void* spMatrixTable;											// �������ñ�
	static void* spCountTable;											// ������
	static void* spDirectTable;											// ֱ����
	static void* spBattleConfig;										// ��ս���ñ�
	static void* spMoneyLmtConfig;										// ��Ǯ���ޱ�
	static void* spFangCunTree;											// ����ɽ����
	static void* spTalentStage;											// �컯���
    static void* spHandinTable[MAX_HANDINTABLE];                        // �Ͻɽ������ձ�
    static void* spHandinEncourage[MAX_HANDINENCOURAGE];                // �Ͻɽ���
	static void* spChangeCamp;											// ת��Ӫ
	static void* spAccuseConfig;										// �������ñ�
	//static void* spRuneConfig ;											//ת�����ı�
	static void * spComRuneConfig;						//�������ı�
	static void* spAchieve;												// �ɾͽ�����
	static void* spGlobalMapConfig;										// ȫ�ֵ�ͼ���ñ�
	static void* spOffLineExpConfig;									// ���߾������ñ�
	static void* spRepeFameTable;										// �����������ñ�
	static void* spCastingSpiritTable;									// �������ñ�
	
	static unsigned short sMetierID[ MAX_METIER ];						// ְҵID
	static unsigned short sGenerID[ MAX_GENER ];						// ְҵ����ϵ��ID
	static unsigned short sComposeID[ MAX_COMPOSE ];					// �ϳ�ID
	static int sTemplateVersion;										// ģ���ļ��汾��
	static int sTaskVersion;											// �����ļ��汾��
	static int mFamilyExpID;											// ���徭������id
	static const int sProNum = 16;
	static int mFamilyRedstoneID;										// �����ڵ�ID
	static void *mMarriageConfig;										// �������
	// ����װ�����б�
	static CProduceTable< PRODUCE_RANK, PRODUCE_LEVEL, PRODUCE_DETAIL2 > sProEquip[ PRODUCE_TYPE ][ PRODUCE_DETAIL1 ];				
	static int sProPhys[ 8 ][ 4 ];	
	static int sRuneLevelID[4][400];
	// ����ҩƷ���б�
	static int sSuitID[ MAX_SUIT ];
 	
	static unsigned int sBugleItemId ;											// ���ȵ���id
	static unsigned int sAutoChatItemId ;										// �Զ���������id
	
	static void* spDecompund;											//	װ���ֽ��
	
	static CLifeSkillInfo mCollect;											// �ɼ�������Ϣ
	static CLifeSkillInfo mGoldMake;										// �������Ϣ	
	static CLifeSkillInfo mArtificer;										// �ɽ�������Ϣ
	static CLifeSkillInfo mPillMaker;										// ����������Ϣ
	static CLifeSkillInfo mCooker;											// ��⿼�����Ϣ		
	static void* spProgressConfig;											// ������������Ϣ
	static void* mActivityConfig;											// ����ñ�(��������)	 	
	static void* spCorpsBOSSTable;											// ����boss��
public:
	static int	InitializeFromPakFile();									// ��ѹ�������ģ������
	static int	Initialize( );
	static void	Finialize( );
	static CTemplate* SearchTpl( unsigned int vTempID );
	static void* SearchSkill( unsigned short vSkillID, unsigned short vLevel );
	static void* SearchMetier( unsigned short vMetierID );
	static void* SearchGener( unsigned short vGenerID );
	static void* GetLevelExp( );
	static void* GetData( );
	static void* GetUpgrade( );
	static void* GetOpenSlot( );
	static void* GetProSuit( );
	static void* GetProExp( );
	static void* GetBeginner( );
	static void* GetDropLevel( );
	static void* GetHonorToExp( );
	static void* GetChangeCamp();
	static void*  GetComRuneConfig();
	static void* GetHonorObtain( );
	static void* GetReliveTable( );	
	static void* GetBindChargeTable();
	static CTemplateBuff::CBuffFunc*	GetBuffFunc( CTemplateBuff* tpBuff, CTemplateBuff::BUFF_FUN_TYPE vType );
	static int GetProNum( );
	static int GetProEquip( unsigned short vType1, unsigned short vType2, unsigned short vLevel, unsigned short vRank = 0, unsigned short vType3 = 0 );
	static int GetProPhy( unsigned short vType1, unsigned short vType2 );
	static int GetChangeRandRuneId(unsigned short vlevel, int itemid );//add by  qiufufu 
	static int  GetMaxRuneIndex(unsigned short level,int maxindex);
	static int GetSuitID( unsigned short vIndex );
	static int GetMetierProperty( int vMetier, int vLevel, int vOption, int vProperty );
	static int GetLevelProperty( int vLevel, int vOption );
	static int GetCompose( int vComposeID );
	static void* GetTemp( TEMPTYPE vType );
	static void Clear();
	static int GetTempVersion();
	static CTitle* GetTitle( int vType, int vRootCndsn, int vSubCndsn, int& vTitleID );
	static CTitle* GetTitle( int vTitleID );
	static int GetTitle( int nParam, int nAction, int nLevel );
	static CJudgeLevel* GetJudgeLevel( int nValue, int nType, int& nNumerator, int& nDenominator );
	static int GetJudgeNumMax( int nLevel );

	static void* GetSkillLifeTable( int nSkillType );
	static void* GetSkillLifeInfo( int nSkillType );
	static int	InsertComposeInfo( int nLifeSkillType, int nComposeID, int nComposeKind, int nDegreeValue, int nComposeType );
	static int	GetCompoundIDList( int nDegreeValue, int nEquipLevel, int nEquipColor, int *pIDList,int *pNumList, int &nNum, int &rDegreeObtained );	
	static int GetWeddingMoney( int nWeddingModule );
	static int GetProgressTimeLength( int nFuncType );
	static bool IsWeddingHall( int nMapID );
	static bool IsInBaitangPos( int nWeddingModue, int nMapID, int nBridePosX, int nBridePosY, int nGroomPosX, int nGroomPosY );
	static int GetPreliminaryScore( int nPreliminaryToplistRank );

    static void* GetHandinEncourage( int nTempId );
    static void* GetHandinTable( int nActivityId );

	static int GetFameLimit( int nFameType );
};
#ifdef TEMPEDIT
#pragma pack(pop)
#endif
