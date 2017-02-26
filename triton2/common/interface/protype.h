#pragma once
#ifndef NAME_LENGTH
#define NAME_LENGTH 32
#endif
#include <string.h>
#include "errcode.h"
#include "template.h"

#ifdef LINUX
#include "lk_assert.h"
#endif

#define  MAXBAGINDEX 24
#define  MAXEQUIPMENTINDEX 14
#define  BINDITEM_CONSUMENUM 1
#define  BINDSTONEID     26338    

// ���ְ�����Ҫ�������ĸ���
#define  MAX_HELPACTON_INT_NUM 6

// һ�η��͵����ֿ���Ʒ����
#define  MAX_STORAGEITEM    30
  
// �������������
#define TEAMNUM 6

// �󶨽������Ʒ����
#define   ITEM_FREE_COUNT   50	

// ȡ���ֶ�����Ҫ�Ľ�Ǯ
#define	  MONEY_RESUMEBIND_NEED 200	

// ��Ǯ�ı�������
#define MONEY_CHANGE_MAX 1000

// NPC���һ���۳��ĵ���
#define ITEM_LASTSELL	-1	

// �����������аٷֱ�����ֱȴ���
#define SERVER_PERCENT_FLOAT 10000.0f
#define SERVER_PERCENT_INT 10000 
#define SERVER_DIPLOID_EXP 2

#define BOURSE_ACCOUNT_MONEY_MAX		( 900000000 )
#define BOURSE_ACCOUNT_YB_MAX			( 900000000 )
#define BOURSE_EXCHANGE_AMOUNT_MAX		( 900000000 )


// һ��ʱ��
#define WEEK_SECOND (7*24*60*60)

// ������ϵ�˫������
#define DIPLOID_LIMIT ( 4 * 60 * 60 * 1000 )

// ���ܹ�����ȴʱ��
#define SKILL_COMMON_COOLDOWN 1000

// ���߱���ʱ��
#define ITEM_PROTECT_TIME	60000 // 1����

// ������ʧʱ��
#define ITEM_DISAPPER_TIME	120000 // 2����

// �ڵ�����ʱ��
#define REDSTONE_PROTECT_TIME 30000 // 30��

// �ڵ���ʧʱ��
#define  REDSTONE_DISAPPER_TIME 120000

// �ڵ����볬ʱʱ��
#define  REDSTONE_PROCESSTIMER_OUTTIME 5000	// 5��

// ����ģ��protobuff����
#define MAX_PRO_PB_DATA_LEN 45000	

// npc ������������Ŀ����
#define  MAX_NPC_QUESTNUM			10 

// �ɼ�NPC ��Ч������(��Ҿ���ֲ��ľ���ҪС�ڵ������ֵ)
#define MAX_COLLECT_GRID			2

// �󶨽����ʱ��
#define ITEMBINDFREETIME       ( 7*24*3600 )

// ��ȡÿ�ո�������͵ȼ�					
#define WELFARE_LEVLE_NEED		10					

// ����NPC��������ʧ/����ʱ��(����)
#define FUNC_NPC_DISAPPEAR		2000
#define FUNC_NPC_RELIFE			5000

// ��Һ�NPC̸��(��������)�����Ϸ�����
#define MAX_NPC_TALK_GIRD 5	

// ����ܿ�ѧ�������
#define  MAXLIFESKILL	  2

// �������ܳ�ʼ�ȼ�
#define MW_SKILL_INIT_LEVEL		0

// �ӳ�ɾ���б� ����
#define	DELETE_LIST_SIZE	4000

// �ڵ�ÿ�η��侭����������
#define  MAX_REDSTONE_ROLENUM 2000

// �����е��������
#define  MAX_WEDDINGHALL_PLAYENUM 500

// �۱���ÿ��۱�����Ʒ��������
#define  TREASUREBOWL_DAILYEXCHANGENUM  500

// �궨�� �ж��Ƿ����������
#define IS_TASK_ITEM(x) ( (x)->mItemType == CTplItem::ITEM_TASK \
	|| (x)->mItemType == CTplItem::ITEM_SPECIAL_TASK \
	|| (x)->mItemType == CTplItem::ITEM_TOKEN \
	|| (x)->mItemType == CTplItem::ITEM_CALL )

#define IS_NOT_TASK_ITEM(x) ( (x)->mItemType != CTplItem::ITEM_TASK \
	&& (x)->mItemType != CTplItem::ITEM_SPECIAL_TASK \
	&& (x)->mItemType != CTplItem::ITEM_TOKEN \
	&& (x)->mItemType != CTplItem::ITEM_CALL )

#define CARDBOOK_TYPE	7
#define CARDBOOK_NUM	100		
#define MATERIALINDEXNUM 3 
#define TITLEMAX_SELF	200	// �������ƺ�����
#define TOPTEN			10
#define NATIONLIMIT		10
#define MIN_JEWCOM_NUM	3	// ��ʯ�ϳ����ٸ���
#define MIN_COUNTRY_LEVEL 10
#define UPG_ITEM_NUM	10
#define MAX_DROP_TURN	16	// ��������
#define MAX_AWARD_NUM	100	// �����ȡ��
#define PROTECT_TIME	600000

#define DEFAULT_RATE			5			// Ĭ��˰������

#define CHANGE_CAMP_LEVEL    30 //ת��Ӫ�ȼ�����

#define FAME_TOTAL_LIMIT			99999	// ����������


// �ɼ�ְҵ����
enum EM_CollectSkill
{
	COLLECTSKILL_WOOD			= 1,	// ֲ��ɼ�
	COLLECTSKILL_MINERAL		= 2,	// ����ɼ�
	COLLECTSKILL_MATERIALMAKER	= 3,	// ���ϼӹ�	
};

// ѧϰ�䷽�ķ�ʽ
enum EM_ComposeGetWay
{ 
	COMPOSEGETWAY_BYNPC			=	0x01,	// ͨ��npcѧϰ
	COMPOSEGETWAY_BYCREAT		=	0x02,	// ͨ���о����
	COMPOSEGETWAY_BYSCROLL		=	0x04,	// ͨ������ѧϰ	
};
// ����ܵ�����
enum EM_LifeSkillKind
{
	LIFESKILLKIND_NONE				= 1,		// δѧϰ״̬
	LIEFSKILLKIND_MAINSKILL			= 2,		// ������
	LIEFSKILLKIND_SUBSKILL			= 3,		// ���޼���	
};

// ����״̬
enum EM_KITBAGSTATUS
{
	KITBAG_STATUS_CLEAN		= 0,			// ��ձ������ٴ洢
	KITBAG_STATUS_NOTCLEAN	= 1,			// ���������ֱ�Ӵ洢	
};

// ��������״̬
enum EM_KITBAGSENDSTATUS
{
	KITBAG_SENDSTATUS_HASLEFTINFO = 0,	   // ���б�����Ϣδ����
	KITBAG_SENDSTATUS_INFOEND	  = 1,	   // ������Ϣ�������
};

// �ڵ�ʹ��״̬
enum EM_RedStoneStatus
{
	REDSTONE_STATUS_PROTECT,				// �������ר������״̬
	REDSTONE_STATUS_DROP,					// ר��������ʧ����������״̬
	REDSTONE_STATUS_PROCESSTIMEER,			// �ڵ���������״̬	
	REDSTONE_STATUS_USED,					// ������������
};

enum EM_StorageStatus
{
	STORAGE_STATUS_INVALID = 1 ,	// �ֿⲻ����״̬����Ʒ��Ϣ��û�з����ͻ���
	STORAGE_STATUS_INITIALIZED ,	// �ֿ��Ѿ���ʼ������Ʒ��Ϣ�Ѿ������ͻ���
};


// ��Ʒ�󶨵�״̬
enum ItemBindStatus
{
	ITEM_BINDSTATUS_FREE          = 0,	  // ��Ʒδ��
	ITEM_BINDSTATUS_BINDED        = 1,    // ��״̬
	ITEM_BINDSTATUS_BYITEM        = 2,    // �ֶ���
	ITEM_BINDSTATUS_FREEBIND      = 4,    // ����ֶ���״̬
};

// ����Ʒ�ķ���
enum ItemBindWay
{
	ITEM_BINDWAY_BYPICKUP = 0 ,
	ITEM_BINDWAY_BYEQUIP,
	ITEM_BINDWAY_BYUSE,
	ITEM_BINDWAY_BYITEM,
	ITEM_BINDWAY_FREE,
};


// �ٻ��޲���ģʽ
enum EMPetMode
{
	EM_PET_MODE_FOLLOW = 0,
	EM_PET_MODE_ASSIST,
};

// ���Ҷ���
enum EObjectECode
{
	ERROR_OBJECT_NOTFOUND	= -1,
	ERROR_OBJECT_USEDUP		= -2,
};


enum ETaskTip
{
	TASKTIP_NONE					= 0,			// ������û���κι�ϵ
	TASKTIP_ACTIVE					= 1,			// ��������Խ�
	TASKTIP_BEGIN					= 2,			// ��������Խ�( û����� )
	TASKTIP_COMPLETE				= 3,			// ��������Խ�( �Ѿ���� )
	TASKTIP_LOOPTYPE				= 4,			// ��ӻ�����Ŀɽ�����
};

/*
enum ETaskProgress
{
	TASK_BEGIN						= 0,			// �����Ѿ����ܣ�������
	TASK_COMPLETE					= 1,			// �����Ѿ���ɣ�����û�н�
	TASK_END						= 2,			// �����Ѿ�����
	TASK_ACTIVE						= 3,			// �����Ѿ�����
};
*/
enum EResultType
{

	RESULT_NONE						= 0,			// ��
	RESULT_NORMAL					= 1,			// ��������
	RESULT_DEATHHIT					,			// ����
	RESULT_NORMALDUCK				,			// ����
	RESULT_SKILLDUCK				,			// ���ܲ�Ӱ
	RESULT_BUFFRESIST				,			// BUFF�ֿ�
	RESULT_IMMUNITY					,			// ����
	RESULT_OBSORB					,			// ����
	RESULT_STEALMP					,			// ͵ȡMP
	RESULT_STEALHP					,			// ͵ȡHP
	RESULT_PROTECTED				,			// �ػ�
	RESULT_COST						,			// ��������
	RESULT_USEITEM					,			// ʹ��ҩƷ
	RESULT_DAMAGELESS				,			// �����˺�
	RESULT_SKILLCARTOON				,			// ���ܶ���
	RESULT_REBOUND					,			// damage rebound
	RESULT_NORMALREFRESH			,			// ������Ѫ������
	RESULT_STATEON					,			// ���״̬
	RESULT_STATEOFF					,			// ɾ��״̬
	RESULT_CHARGE					,			// ���
	RESULT_TELEPORT					,			// ����
	RESULT_TELESYMBOL				,			// ʹ�ô��ͷ�
	RESULT_GIFT						,			// ʹ�����
	RESULT_USEBYITEM				,			// ����Ʒʹ��
};

enum
{
	FUNC_NONE						= 0,			// �޹��� ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_ATTACK,									// ʹ�ü���( value1=Ŀ��EntityID, value2=����ID�� value3=���ܵȼ�, value4=Ŀ������X, value5=Ŀ������Y )( ����ID=0 ������ͨ���� )
	FUNC_ATTACKED,									// �����ܹ���( value1=ԴEntityID, value2=����ID�� value3=���ܵȼ�,value4=Դ����X, value5=Դ����Y )( ����ID = 0 ������ͨ���� )
	FUNC_INCHP,										// ����HP ( value1=HP�ı���, value2=HP��ǰֵ, value3=HP���ֵ, value4=0, value5=0 )
	FUNC_INCMP,										// ����MP ( value1=MP�ı���, value2=MP��ǰֵ, value3=MP���ֵ, value4=0, value5=0 )
	FUNC_INCAP,										// ����AP ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_DECHP,										// ����HP ( value1=HP�ı���, value2=HP��ǰֵ, value3=HP���ֵ, value4=0, value5=0 )
	FUNC_DECMP,										// ����MP ( value1=MP�ı���, value2=MP��ǰֵ, value3=MP���ֵ, value4=0, value5=0 )
	FUNC_DECAP,										// ����AP ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_INSERTBUFF,								// ���Buff ( value1=buffģ��ID, value2=BuffΨһID, value3=ʣ��ʱ��)
	FUNC_REMOVEBUFF,								// ɾ��Buff ( value1=buffģ��ID, value2=BuffΨһID )
	FUNC_DIE,										// ���� ( value1=x����, value2=y����, value3=0, value4=0, value5=0 )
	FUNC_COOLDOWN,									// ������ȴ��� ( value1=����ID, value2=���ܵȼ�, value3=0, value4=0, value5=0 )
	FUNC_PEACE,										// �뿪ս�� ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_BATTLE,									// ����ս�� ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_BEGINFIRE,									// ��ʼ�������� ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_ENDFIRE,									// ������������ ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_PKRED,										// PK״̬���, PKֵ��1 ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_PKYELLOW,									// PK״̬��� ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_PKWHITE,									// PK״̬��� ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_PKREDBDEC,									// PK״̬����������٣�����1�� ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_PKREDSDEC,									// PK״̬�����������٣�����0.01�� ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_CMCOOLDOWN,								// ������ȴ��� ( value1=0, value2=0, value3=0, value4=0, value5=0 )
	FUNC_PHCOOLDOWN,								// ҩƷ��ȴ��� ( value1=CD��ID, value2=0, value3=0, value4=0, value5=0 )
	FUNC_CHANGESTATE,								// ״̬�ı� ( value1=״̬����, value2=����1, value3=����2, value4=X����, value5=Y���� )
	FUNC_CHANGESPEED,								// �ٶȸı� ( value1=��ǰ�ٶ�, value2=0, value3=0, value4=0, value5=0 )
	FUNC_CHANGEPOS,									// λ�øı� ( value1=X����, value2=Y����, value3=0, value4=0, value5=0 )
	FUNC_PETLEVELUP,								// �������� ( value1=��ǰ�ȼ�, value2=0, value3=0, value4=0, value5=0 )
	FUNC_LEVELUP,									// �ȼ����� ( value1=��ǰ�ȼ�, value2=HP��ǰֵ, value3=HP���ֵ, value4=MP��ǰֵ, value5=MP���ֵ )
	FUNC_TRAPONTOUCH,								// ���屻����(value1=����ID, value2=���ܵȼ�, value3=x����, value4=y����, value5=0 )
	FUNC_EXP,										// ��þ���(value1=��þ���, value2=��ǰ����(��32bit), value3=�����ȼ�, value4=(��32bit), value5=0 )
	FUNC_HONOR,										// ��ù�ѫ(value1=��ѫ�ı�, value2=��ǰ��ѫ, value3=ɱ����, value4=���վ����Ѷһ�, value5=������Ʒ�Ѷһ� )
	FUNC_PKVALUE,									// pkֵ�ı�(value1=pkֵ, value2=0, value3=0, value4=0, value5=0 )
	FUNC_TALENT,									// ��Ϊ�ı�(value1=��ǰ��Ϊ, value2=��ǰ�컯, value3=�ı���, value4=�컯�ȼ�, value5=0 )
	FUNC_WIZARD,									// �Ż��ı�(value1=�Ż�����, value2=��ǰ�Ż�ֵ, value3=��ǰ�Ż��ȼ�, value4=0, value5=0 )
	FUNC_SYNCHPMP,									// ͬ��HP��MP( value1=��ǰHP�� value2=���HP, value3=��ǰMP, value4=���MP
	FUNC_CHANGEPROTECT,								// ����״̬�ı�( value1=����״̬ 0 1 )
	FUNC_CHARM,										// ����ֵ�ı�(value1=��ǰ����, ���඼��Ч )
	FUNC_ITEM,										// �����Ʒ(value1=��ƷID, value2=0, value3=0, value4=0, value5=0 )
	FUNC_MONEY,										// ��ý�Ǯ(value1=����, value2=0, value3=0, value4=0, value5=0 )
	FUNC_BINDMONEY,									// ��ð󶨽�Ǯ(value1=����, value2=0, value3=0, value4=0, value5=0 )
	FUNC_YUANBAO,									// ���Ԫ��(value1=����, value2=0, value3=0, value4=0, value5=0 )
	FUNC_OFFLINEEXP,								// ������߾���(value1=��õľ���, value2=ʣ�����߾���, value3=0, value4=0, value5=0 )
};
//
//enum ETaskTick
//{
//	TICK_KILLNPC					= 0,			// ɱ�ּ���
//	TICK_TALKNPC					= 1,			// �Ի�����
//	TICK_REGIONARRIVAL				= 2,			// �ﵽָ������
//	TICK_MONEY						= 3,			// �ﵽָ�����
//	TICK_LEVEL						= 4,			// �ﵽ�ƶ��ȼ�
//	TICK_ITEM						= 5,			// ���߼���
//};

enum ERelive
{
	RELIVE_WEAKGRAVE				= 1,			// ����Ĺ�ظ���
	RELIVE_NORMAL					= 2,			// ����ԭ�ظ���
	RELIVE_SKILL					= 3,			// ����ԭ�ظ���
	RELIVE_SYSTEM					= 4,			// ϵͳǿ�и���
};

enum EInsertBuff
{
	INSERTBUFF_SUCCESS				= -1,			// ���Buff�ɹ�
	INSERTBUFF_RESIST				= -2,			// ���Buff�ֿ�
	INSERTBUFF_BUFFNOTFOUND			= -3,			// ���Buffû���ҵ�
	INSERTBUFF_FULL					= -4,			// ���Buffʱ��Buff����
};

enum EExchageBaggage
{
	EXCHAGE_SUCCESS					= 0,			// ���׳ɹ�
	EXCHAGE_SRCISNOTPLAYER			= 1,			// Դ�������
	EXCHAGE_DESISNOTPLAYER			= 2,			// Ŀ�겻�����
	EXCHAGE_SRCOUTOFSPACE			= 3,			// Դ�����ռ䲻��
	EXCHAGE_DESOUTOFSPACE			= 4,			// Ŀ������ռ䲻��
	EXCHAGE_SRCMONEYNOTENOUGH		= 5,			// Դ������Ҳ���
	EXCHAGE_DESMONEYOVERFLOW		= 6,			// Ŀ�����������
	EXCHAGE_MYMONEYOVERFLOW			= 7,			// �ҵİ���������
};

enum EMail
{
	ERROR_MAIL_SUCCESS				= 0,
	ERROR_MAIL_ITEMNOTFOUND			= 1,			// �ʼ�����ʱ������û���ҵ�
	ERROR_MAIL_MONEYNOTENOUGH		= 2,			// �ʼ�����ʱ����Ҳ���
	ERROR_MAIL_ITEMLOCKED			= 3,			// �ʼ�����ʱ������������
	ERROR_MAIL_NOSPACE				= 4,			// �ʼ�����ʱ�������ռ䲻��
};

//enum EStall
//{
//	ERROR_STALL_SUCCESS				= 0,
//	ERROR_STALL_ENTITYNOTFOUND		= 1,			// ��̯����ʱ��ʵ��û���ҵ�
//	ERROR_STALL_NOTENOUGHMONEY		= 2,			// ��̯����ʱ��ʵ���Ǯ����
//	ERROR_STALL_NOSPACE				= 3,			// ��̯����ʱ��ʵ���������
//	ERROR_STALL_ITEMNOTFOUND		= 4,			// ��̯����ʱ��ָ�����������ڵ���
//	ERROR_STALL_ITEMLOCKED			= 5,			// ��̯����ʱ�����߱�����
//	ERROR_STALL_ITEMNOTENOUGH		= 6,			// ��̯����ʱ��Դ���û���㹻�ĵ���
//
//};

enum ELockItem
{
	LOCKTYPE_NONE					= 0,			// û�б�����
	LOCKTYPE_EXCHANGE				= 1,			// ������
	LOCKTYPE_MAIL					= 2,			// �ʼ���
	LOCKTYPE_AUCTION				= 3,			// ������
	LOCKTYPE_STALL					= 4,			// ��̯��
	LOCKTYPE_UPG					= 5,			// ������
	LOCKTYPE_RUNE					= 6,			// ������
	LOCKTYPE_JEWEL					= 7,			// ��ʯ��
	LOCKTYPE_SLOT					= 8,			// ������
	LOCKTYPE_EAT					= 9,			// ��װ����
	LOCKTYPE_COMPOSE				= 10,			// �ϳ���
	LOCKTYPE_SHOUT                  = 11,           // ����������
	LOCKTYPE_TASK					= 12,			// �������
	LOCKTYPE_BIND                   = 13,           // ����
	LOCKTYPE_QUESIONPAPER			= 14,			// �����	
	LOCKTYPE_TASK_RECVITEM			= 15,			// ��������Ʒ��(��ͨ��Ʒ)
	LOCKTYPE_LOCKCANUSE				= 16,			// ����������������ʹ��(���ͷ��򿪴��ͱ�ʱ)
	LOCKTYPE_ADD					= 17,			// �Ӳ���
	LOCKTYPE_REMOVE					= 18,			// ժ����
	LOCKTYPE_JUDGE					= 19,			// ������
	LOCKTYPE_CHANGE					= 20,			// ת��������
	LOCKTYPE_JEWCOM					= 21,			// ��ʯ�ϳ���
	LOCKTYPE_LIFESKILL				= 22,			// �������
	LOCKTYPE_MAGICWEAPON			= 22,			// ������
	LOCKTYPE_MAGICWEAPON_STONE		= 23,			// ��������ʯ��
	LOCKTYPE_MULTI					= 24,			// ���Ӻϳ���
	LOCKTYPE_DECOMPOUND				= 25,			// װ���ֽ���
	LOCKTYPE_KEEPSAKE				= 26,			// ����������
};

enum EMaxLength
{
	ITEMOBJ_BUFFLEN					= 1024,			// ���߶����ֽ�������
};

enum EClientState
{	CSTATE_HUMAN,
	CSTATE_LION,
	CSTATE_LEOPARD,
};

enum EPKMode
{
	PKMODE_TRAINING,	// ����ģʽ
	PKMODE_ALL,			// ��ɱģʽ
	PKMODE_CORPS,		// ����ģʽ
	PKMODE_ALLY,		// �˹�ģʽ
	PKMODE_EVIL,		// �ƶ񱣻�
	
	//PKMODE_ALL,			// ȫ�屣��
	//PKMODE_FAMILY,		// ���屣��
	//PKMODE_GUILD,		// ��ᱣ��
	//PKMODE_NATION,		// ���ұ���
	//PKMODE_EVIL,		// �ƶ񱣻�
	//PKMODE_ALLY,		// �˹�����������������
};

// �����ã�������postype���
enum ESlotType
{
	SLOT_EQUIPMENT			= 0,						// װ����
	SLOT_BAGGAGE,										// ������
	SLOT_STORAGE,										// �ֿ���
	SLOT_STORKITBAG,									// �ֿ�ı���
	SLOT_BAGGAGEKITBAG,									// �����ı���
};

// ������
enum EBagType
{
	BAGTYPE_BASEBAG = 1,								// ������( �ֿ������ )
	BAGTYPE_KITBAG  = 2,								// ����
};

enum EPosType
{
	POS_NULL   			= 0x00,			// �����Ƶ�λ��
	POS_EQUIPMENT		= 0x01,			// װ����
	POS_BAGGAGE			= 0x02,			// ������
	POS_TASK_BAGGAGE	= 0x04,			// ���������
	POS_STORAGE			= 0x08,			// �ֿ��� 
};


enum EPropertyType
{
	PROPERTY_STA			= 1,						// ����
	PROPERTY_WIS,										// �ǻ�
	PROPERTY_STR,										// ����
	PROPERTY_CON,										// ����
	PROPERTY_SPR,										// ����
};


enum EState
{
	STATE_NONE						= 0,					// �޹���
	STATE_IMMUNITYDAMAGE,								// �޵�
	STATE_IMMUNITYREVERSD,									// immunity debuf ���߸���BUFF
	STATE_CANNTMOVE,										// �޷��ƶ�
	STATE_REBOUND,											// �����˺�			Ŀǰ�޴���, �˺�������ֱ����Buff��������(2009.10.9 lixi)
	STATE_CUREHPLESS,										// less cure hp ����������
	STATE_SILENCE,											// ��Ĭ				Ŀǰ�����ɾ��״̬�ط�( 2009.10.9 lixi)
	STATE_CONFUSION,										// ����
	STATE_FASTING,											// ��ʳ
	STATE_SNEER,											// ����
	STATE_MAGICSHIELD,										// ħ����			Ŀǰά��״̬�� ����Ӧ��, ������Buffʵ��(2009.10.9 lixi)
	STATE_PDEFENCEZERO,										// �������Ϊ0a		Ŀǰ��״̬ά��,�޴���(2009.10.9 lixi)
	STATE_MDEFENCEZERO,										// ��������Ϊ0		Ŀǰ��״̬ά��,�޴���(2009.10.9 lixi)
	STATE_IGNORECLOTH,										// �����·�����		Ŀǰ�޴���, ��ά��(2009.10.9 lixi)
	STATE_UNARM,											// ������������		Ŀǰ��״̬ά��,�޴���(2009.10,9 lixi )
	STATE_INCGENERDAMAGEFIX,								// �����ܵ�ĳϵ�����˺��Ĺ̶�ֵ (��ʱδʹ��) ͬ��
	STATE_INCGENERDAMAGEPER,								// �����ܵ�ĳϵ�����˺��İٷֱ� Ŀǰ�޴���, ������Buffʵ��(2009.10.9 lixi)
	STATE_PGENERATTACKFIX,									// ����ָ��ϵ�𹥻��̶�ֵ		Ŀǰ��״̬ɾ��(2009.10.9 lixi)
	STATE_NEXTDEATHHITFIX,									// �����´ι��������ȼ��̶�ֵ	Ŀǰ��ɾ��ά���� �޴���, ������Buffά��(2009.10.9 lixi)
	STATE_NEXTDEATHRATEFIX,									// �����´ι��������˺��ӳɹ̶�ֵ	Ŀǰ��ɾ��ά��, �޴���, ������Buffʵ��(2009.10.9 lixi)
	STATE_INCHONORSCALE,									// ���ӹ�ѫ�����ֱ�
	STATE_PROTECTED,										// �ػ�				Ŀǰ�޴���, ������Buff����ʵ��(2009.10.9 lixi)
	STATE_UNATTACK,											// �޷�����
	STATE_DAMAGELESS,										// �����˺�			Ŀǰ�޴���, ������Buff����ʵ��(2009.10.9 lixi)
	STATE_INCREAMSPEED,										// �����ƶ��ٶ���ֱ�
	STATE_UNCREAMSPEED,										// �����ƶ��ٶ���ֱ�
	STATE_KILLERRENEW,										// ɱ��ȡѪ
	STATE_FIREEVENT,										// �ɹ��ͷż���ʹ������һ��DEBUFF		Ŀǰ�޴���, ������Buff����ʵ��(2009.10.9 lixi)
	STATE_ATTACKEVENT,										// ����ʱ�м���ʹ����������Ч��		Ŀǰ�޴���, ������Buff����ʵ��(2008.10,9 lixi)		
	STATE_RANDMOVE,											// ����ƶ�			Ŀǰ�޴���( 2009.10.9 lixi)
	STATE_INCDESPDAMAGEFIX,									// ���ӱ�����ʱ���������˺��̶�ֵ		Ŀǰ�޴���, ������Buff����ʵ��( 2008.10,9 lixi ) 
	STATE_INCDESPDAMAGEPER,									// ���ӱ�����ʱ���������˺��ٷֱ�		ͬ��
	STATE_DECDESPDAMAGEFIX,									// ���ͱ�����ʱ���������˺��̶�ֵ		ͬ��
	STATE_DECDESPDAMAGEPER,									// ���ͱ�����ʱ���������˺��ٷֱ�		ͬ��
	STATE_INCDESMDAMAGEFIX,									// ���ӱ�����ʱ���ܷ����˺��̶�ֵ		ͬ��
	STATE_INCDESMDAMAGEPER,									// ���ӱ�����ʱ���ܷ����˺��ٷֱ�		ͬ��
	STATE_DECDESMDAMAGEFIX,									// ���ͱ�����ʱ���ܷ����˺��̶�ֵ		ͬ��
	STATE_DECDESMDAMAGEPER,									// ���ͱ�����ʱ���ܷ����˺��ٷֱ�		ͬ��
	STATE_INCGENERATTACK,									// ����ĳϵ���ܵĹ����� (��ʱδʹ��)	Ŀǰ��ά���� �޴���( 2008.10,9 lixi ) 
	STATE_AUREOLE,											// aurlole skill �⻷����				
	STATE_INCEXP,											// ���Ӿ�����ֱ�
	STATE_DECALLDAMAGEPER,									// ���������˺����˺��ٷֱ�
	STATE_TRANSFORM,										// �����״̬
	STATE_INCCORPSGLORY,									// ���Ӿ�����ҫ��buff
	STATE_INCAP,											// ������ҹ�ѫ��buff


	STATE_UNATTACK_PLAYER,									// ���ܹ������
	STATE_PLAYER_UNATTACK,									// ���ܱ���ҹ���
	STATE_RIDE_HORSE,										// ����״̬
	STATE_INVISIBLE,										// ����
	STATE_DISINVISIBLE,										// ��Ӱ��
	STATE_FLY,												// ����
	STATE_STONE,											// ��ʯ
	STATE_HIDE,												// ������������
	STATE_MASKED,											//������
	STATE_INCOFFLINEEXP,									// �������߾�������ֱ�

		// ״̬��50���ˣ�������ӵĻ���ע��
	STATE_COUNT_MAX,		
	
};

enum EService
{
	SERVICE_NONE			= 0,						// �޷���״̬
	SERVICE_SHOP			= 1,						// �̵����״̬
	SERVICE_MAIL			= 2,						// �ʼ�����״̬
	SERVICE_STORAGE			= 3,						// �ֿ����״̬
	SERVICE_UPG				= 4,						// ��������״̬
	SERVICE_TELE			= 5,						// ���ͷ���״̬
	SERVICE_STUDYSKILL		= 6,						// ѧϰ����״̬
	SERVICE_TOWN			= 7,						// �سǷ���״̬
	SERVICE_BIND			= 8,						// װ����״̬
	SERVICE_WELFARE			= 9,						// ÿ�ո���״̬
	SERVICE_STALL			= 10,						// ��̯״̬
	SERVICE_TRADE			= 11,						// ����״̬
	SERVICE_CHANGE			= 12,						// ת��״̬
	SERVICE_JUDGE			= 13,						// ����״̬
	SERVICE_EXCHANGE		= 14,						// �һ�״̬
	SERVICE_HONOR			= 15,						// ��ѫ״̬
	SERVICE_BATTLE			= 16,						// ս������
	SERVICE_MWJUDGEPRO		= 17,						// �������Լ�������
	SERVICE_MWJUDGESKILL	= 18,						// �������ܼ�������
	SERVICE_GOLDENYB		= 19,						// Ԫ����ȡ����
	SERVICE_HONOR_TOKEN		= 20,						// �����һ����Ʒ���
};

enum EPKStatus
{
	PKSTATUS_WHITE			= 0,						// ��ɫ״̬
	PKSTATUS_AZURY,										// ǳ����
	PKSTATUS_BLUE,										// ����
	PKSTATUS_NAVYBLUE,									// ������
	PKSTATUS_ROSINESS,									// ǳ��ɫ
	PKSTATUS_RED,										// ����
	PKSTATUS_CARMINE,									// �����
	PKSTATUS_PKTOPLIMIT,								// PKֵ����
	PKSTATUS_YELLOW,									// ����
};

enum EProDebug
{
	COMMAND_INSERTITEM		 = 1,						// ��õ���
	COMMAND_MOVEITEM,									// �ƶ�����
	COMMAND_OBTAINSKILL,								// ��ü���
	COMMAND_EQUIPITEM,									// װ������
	COMMAND_UNEQUIPITEM,								// ж�µ���
	COMMAND_OBTAINEXP,									// ��þ���
	COMMAND_CHANGEMETIER,								// ת��ְҵ
	COMMAND_ADDTASK,									// �������
	COMMAND_REMOVETASK,									// ɾ������
};

//enum EUseItem
//{
//	ERROR_ITEMSUCCESS			= 1400,					// ʹ�óɹ�
//	ERROR_ITEMNOTEXIST,									// ��Ʒ������
//	ERROR_TPLNOTEXIST,									// ģ�岻����
//	ERROR_WRONGTYPE,									// ���ʹ���
//	ERROR_NOTENOUGHPOINT,								// ��������
//	ERROR_NOTCOOLDOWN,									// û����ȴ
//	ERROR_RECOVERING,									// ���߻ָ���
//	ERROR_RANDOMTP,										// �������
//	ERROR_RETURNTP,										// ��ڴ���
//	ERROR_REMEMBERTP,									// ���䴫��
//	ERROR_TOWNTP,										// �سǴ���
//	ERROR_SRCDEAD,										// ʹ��������
//	ERROR_UNUSEITEM,									// �����޷���ҩ״̬
//};

enum EEquipPart
{
	EQUIPMENT_WEAPON,									// ����
	EQUIPMENT_CHEST,									// �ز�����
	EQUIPMENT_LEG,										// �Ȳ�����
	EQUIPMENT_HEAD,										// ͷ������
	EQUIPMENT_NECK,										// ����
	EQUIPMENT_RINGLEFT,									// ���ָ
	EQUIPMENT_RINGRIGHT,								// �ҽ�ָ
	EQUIPMENT_SASH,										// ����
	EQUIPMENT_CUFFLEFT,									// ����
	EQUIPMENT_CUFFRIGHT,								// �һ���
	EQUIPMENT_CHARMLEFT,								// �󻤷�
	EQUIPMENT_CHARMRIGHT,								// �һ���
	EQUIPMENT_BALL,										// ����	
	EQUIPMENT_CLOAK,									// ����	
	EQUIPMENT_FASHION,									// ʱװ
	EQUIPMENT_WIZARD1,									// �Ż�װ��
	EQUIPMENT_WIZARD2,
	EQUIPMENT_WIZARD3,							
	EQUIPMENT_MAGICWEAPON,								// ����		
	EQUIPMENT_MARRY,									// ������
	EQUIPMENT_MAXPARTCOUNT								// װ���������
};


enum EUpgResult
{
	UPG_SUCCESS					= 0,					// �����ɹ�
	UPG_REMAIN,											// ʧ�ܵ�����
	UPG_FAIL,											// ʧ����ʧ
	UPG_DOWN,											// ʧ�ܽ���
	UPG_STOP,											// û�ɹ���Ҫֹͣ
	UPG_EXT,											// ʧ�ܵ�������
};

enum EProduceType
{
	EQUIP_WEAPON				= 0,					// ����
	EQUIP_HELM,											// ñ��
	EQUIP_BODY,											// �·�
	EQUIP_SHOE,											// Ь��
	EQUIP_BRACER,										// ����
	EQUIP_RING,											// ��ָ
	EQUIP_NECKLACE,										// ����
	EQUIP_CHARM,										// ����
	EQUIP_CLOAK,										// ����
	EQUIP_BELT,											// ����
	PHYSICS_RECOVER,									// �ָ�
	PHYSICS_BUFF,										// BUFF
	PHYSICS_DEXP,										// ˫������
};

enum EProduceLevel
{
	EQUIP_LEVEL_BEGIN			= 0,					// װ���ȼ���Χ
	EQUIP_LEVEL_END				= 11,
	HP_LEVEL_BEGIN				= 100,					// HPҩ�ȼ���Χ
	HP_LEVEL_END				= 103,
	MP_LEVEL_BEGIN				= 104,					// MPҩ�ȼ���Χ
	MP_LEVEL_END				= 107,
	HMP_LEVEL_BEGIN				= 108,					// HMPҩ�ȼ���Χ
	HMP_LEVEL_END				= 111,
	RES_LEVEL_BEGIN				= 112,					// ����ҩ�ȼ���Χ
	RES_LEVEL_END				= 115,
	PRO_LEVEL_BEGIN				= 116,					// ����ҩ�ȼ���Χ
	PRO_LEVEL_END				= 119,
	EXP_LEVEL					= 120,
};

// ���ϵ�ID��TYPE1-4Ϊ�������׻�����ȸ�����䣬RANK1-4
enum EMaterialID
{
	TYPE1RANK1 = 25397,
	TYPE1RANK2,
	TYPE1RANK3,
	TYPE1RANK4,
	TYPE2RANK1 = 25404,
	TYPE2RANK2,
	TYPE2RANK3,
	TYPE2RANK4,
	TYPE3RANK1 = 25390,
	TYPE3RANK2,
	TYPE3RANK3,
	TYPE3RANK4,
	TYPE4RANK1 = 25411,
	TYPE4RANK2,
	TYPE4RANK3,
	TYPE4RANK4,
	PHYTYPE	   = 25369,						// ҩƷ���ϵ���ʼ
	PHYDEXP	   = 25373,						// ˫������ҩ
};

// ���ԣ�����������������
enum TriggerType
{
	ONTIMER			= 0x01,	// ��ʱ����ʱ
	HPLESSTHAN		= 0x02,	// HP����%
	HPMORETHAN		= 0x04,	// HP����%
	BATTLESTART		= 0x08,	// ս����ʼ
	BATTLEEND		= 0x10,	// ս������
	RANDOMT			= 0x20,	// ���
	KILLPLAYER		= 0x40,	// ɱ�����
	KILLOGRE		= 0x80,	// ��������
};

// ���ԣ���������
enum ActionType
{
	ATTACK = 0,				// ��ʼ����
	USESKILL,				// ʹ�ü���
	SPEAK,					// ˵��
	RESETENMITY,			// ���ó���б�
	RUNTRIGGER,				// ִ�д�����
	STOPTRIGGER,			// ֹͣ������
	ACTIVETRIGGER,			// �������	
	FLEE,					// ����
	TARFIRSTENMITY,			// ��Ŀ������Ϊ���
	TARLASTENMITY,			// ��Ŀ������Ϊ���
	REDUCEHALFENMITY,		// ����Ŀ����50%
	BREAK,					// �����������
	OGRECONTROL,			// ������������
	CREATETIMER,			// ������ʱ��
	STOPTIMER,				// ֹͣ��ʱ��
};

// ���ԣ�Ŀ������
enum TargetType
{
	FIRSTENMITY		= 0x0100,		// ������
	SECONDENMITY	= 0x0200,		// �ڶ����
	RANDOMENMITY	= 0x0400,		// ����һ�����б�������
	MAXHP			= 0x0800,		// hp���
	MAXMP			= 0x1000,		// mp���
	MINHP			= 0x2000,		// hp����
	SELF			= 0x4000,		// �Լ�
	OTHEROGRE		= 0x8000,		// ��������
	PROF1			= 0x0001,		// ְҵ1-6
	PROF2			= 0x0002,
	PROF3			= 0x0004,
	PROF4			= 0x0008,
	PROF5			= 0x0010,
	PROF6			= 0x0020,
	PROF7			= 0x0040,

};


enum ETitleAction
{
	TITLE_ADD		=	0,	// ���ӳƺ�
	TITLE_REPLACE,			// �滻�ƺ�
	TITLE_DELETE,			// ɾ���ƺ�
};

enum CLOSEWINDOW
{
	CLOSE_UPG		= 0x001,							// �ر�����
	CLOSE_PRO		= 0x002,							// �ر�����
	CLOSE_RUNE		= 0x004,							// �رշ���
	CLOSE_JEWEL		= 0x008,							// �ر���Ƕ
	CLOSE_YUAN		= 0x010,							// �ر�Ԫ����
	CLOSE_SLOT		= 0x020,							// �رտ���
	CLOSE_COMPOSE	= 0x040,							// �رպϳ�
	CLOSE_MAIL		= 0x080,							// �ر��ʼ�
	CLOSE_BIND		= 0x100,							// �ر�װ����
	CLOSE_WELFARE	= 0x200,
	CLOSE_TASK		= 0x400,							// �رս��������
	CLOSE_TELESYMBOL = 0x800,							// �رմ��ͷ�����
	CLOSE_ADD		= 0x1000,							// �رռӲ�
	CLOSE_REMOVE	= 0x2000,							// �ر�ժ��
	CLOSE_CHANGE	= 0x4000,							// �ر�ת��
	CLOSE_JEWCOM	= 0x8000,							// �رձ�ʯ�ϳ�
	CLOSE_JUDGE		= 0x10000,							// �رռ���
	CLOSE_COMPOSECREAT		= 0x20000,					// �����䷽�Ľ���ر�
	CLOSE_DECOMPOUNDEQUIP	= 0x40000,					// װ���ֽ�Ľ���ر�
};

//��Ҷ���ְ��״̬
#define TEAM_NONE				0						//�޶������

#define MAX_TRIP_ENTITY			8						// ����������
#define SHOP_PAGEINDEX_MAX		6						// NPC�̵꽻�׽������ҳ��
#define SHOP_ITEMINDEX_MAX		12						// NPC�̵�ÿҳ��������

// ��̯
enum STALLMACRO
{
	STALL_NAME			= 0x1001,		// ̯λ����
	STALL_ADCONTENT,					// ���
	STALL_PUSH,							// �ϼ�
	STALL_DOWN,							// �¼�
};

// ���������Ұ�Ĵ�����ʽ
enum EPlayerCreatMethod
{	
	PLAYERCREAT_MOVE		= 0,		// ͨ���ƶ�������Ұ
	PLAYERCREAT_TELEPORT	= 1,		// ͨ�����ͽ��������Ұ		
};

// ���ֲŻ�
enum EWizardType
{
	WIZARD_ARTS	= 0,					// �Ĳ�
	WIZARD_TACTICS,						// ����
	WIZARD_POWER,						// ����
	WIZARD_WISDOM,						// ı��
	WIZARD_POLITICS,					// ����
	WIZARD_EDUCATE,						// ����	
	WIZARD_COMMON,						// ͨ��
	WIZARD_NUM,
};

//// �������
//#define CONTATT_OVER 0xFFFFFFFF			// ���������
//enum CONTINUEDATTACK
//{
//	CONTATT_NONE		= 0x00000000,	// ��������
//	CONTATT_MOVE		= 0x00000001,	// �ƶ����
//	CONTATT_POSDIFF		= 0x00000002,	// �����������ĵ�ı���
//};

// *************************************************************************** //
// ���ܽ��, ����,���ߺ�Buff��ɵĽ�����ǹ�����ɵ�
// *************************************************************************** //
class CFuncResult
{
public:
	unsigned int	mEntityID;	// Ŀ��ʵ��ID
	int				mFunc;
	int				mResult;	// ִ�н��
	unsigned int	mValue1;
	unsigned int 	mValue2;
	unsigned int	mValue3;
	unsigned int	mValue4;
	unsigned int	mValue5;
	int				mPosX;
	int				mPosY;
	int				mDirection;
	int				mListID;
	unsigned int	mSrcEntityID;	// Դʵ��ID,�п���Ϊ0,���ڿͻ�����ʾ��
	bool			mBroadCast;		// �Ƿ�Ⱥ��

public:
	CFuncResult( unsigned int vSrcEntity, unsigned int vEntityID, unsigned short vFunc, unsigned short vResult, bool vBroadCast, int vListID, unsigned int vValue1, unsigned int vValue2, unsigned int vValue3 = 0, unsigned int vValue4 = 0, unsigned int vValue5 = 0 ) 
		: mEntityID( vEntityID ), mFunc( vFunc ), mResult( vResult ), mValue1( vValue1 ), mValue2( vValue2 ), mValue3( vValue3 ), mValue4( vValue4 ), mValue5( vValue5 ), 
		mPosX(0), mPosY(0), mDirection(0), mListID( vListID ),mSrcEntityID( vSrcEntity ), mBroadCast( vBroadCast )
	{

	}
	CFuncResult(){};

public:
	unsigned int	GetEntityID( )	{ return mEntityID; }
	unsigned short	GetFunc( )		{ return mFunc; }		// �õ�ִ�еĹ�����
	unsigned short	GetResult( )	{ return mResult; }		// �õ�ִ�еĽ��
	unsigned int	GetValue1( )	{ return mValue1; }
	unsigned int	GetValue2( )	{ return mValue2; }
	unsigned int	GetValue3( )	{ return mValue3; }
	unsigned int	GetValue4( )	{ return mValue4; }
	unsigned int	GetValue5( )	{ return mValue5; }
	int				GetPosX( )		{ return mPosX; }
	int				GetPosY( )		{ return mPosY; }
	int				GetDirection( )	{ return mDirection; }
	int				GetListID( )	{ return mListID; }
	unsigned int	GetSrcEntityID( ) { return mSrcEntityID; }
	bool			GetBroadCast( )	{ return mBroadCast; }
};

// ������ֵ����
enum enMagicWeaponValueTyle
{
	MAGIC_WEAPON_LEVEL			= 0x000001 ,		// �����ȼ�
	MAGIC_WEAPON_EXP			= 0x000002 ,		// ��������
	MAGIC_WEAPON_MP				= 0x000004 ,		// ����ֵ
	MAGIC_WEAPON_HP				= 0x000008 ,		// ����ֵ
	MAGIC_WEAPON_KEENPOINTS		= 0x000010 ,		// ��ǰ����
	MAGIC_WEAPON_CALMPOINTS		= 0x000020 ,		// ��ǰ����
	MAGIC_WEAPON_MAGICPOINTS	= 0x000040 ,		// ��ǰ����
	MAGIC_WEAPON_BIERPOINTS		= 0x000080 ,		// ��ǰ����
	MAGIC_WEAPON_IMMORTALPOINTS = 0x000100 ,		// ��ǰ����
	MAGIC_WEAPON_PROSPIR		= 0x000200 ,		// ����
	MAGIC_WEAPON_LEFTPOINTS		= 0x000400 ,		// ��ǰʣ��Ǳ�ܵ�
	MAGIC_WEAPON_LEFTSKILLPOINTS= 0x000800 ,		// ��ǰʣ�༼�ܵ�
	MAGIC_WEAPON_MP_INC			= 0x001000 ,		// ����ֵÿ�λָ�����
	MAGIC_WEAPON_HP_INC			= 0x002000 ,		// ����ֵÿ�λָ�����
	MAGIC_WEAPON_PROBASE		= 0x004000 ,		// ���Ի���ֵ
	MAGIC_WEAPON_PROUP			= 0x008000 ,		// ���Գɳ�ֵ
	MAGIC_WEAPON_PROEFF			= 0x010000 ,		// ����Ӱ���
	MAGIC_WEAPON_PROCESSVAL		= 0x020000 ,		// ��ǰ����ֵ
	MAGIC_WEAPON_MAXMP			= 0x040000 ,		// ����ֵ����
	MAGIC_WEAPON_MAXHP			= 0x080000 ,		// ����ֵ����
};

// �����ظ�MP������HPʱ�� (ms)
#define MW_INDEC_TIMER	300000

// ��������ȼ�Ӱ�츽��ֵ
#define MW_LEVEL_EXTRA_EFF 100

// ������ʱ��ö��
enum enMagicWeaponTimerType
{
	MW_TIMWR_MP_INC		=	0,		// ����MP��ʱ��
	MW_TIMWR_HP_DEC			 ,		// �ۼ�MP��ʱ��

	MW_TIMER_NUM			 ,		// �����±�
};

// ����Ӱ���˵Ĺ�ʽ
class CMagicWeaponFormula
{
public:
 	// ������ҹ�����
	// ������������ģ��ID����ǰ��������ǰ����Ӱ��ȣ���ǰ�ȼ�����ǰ�����ȼ�������, ����ֵ
	static int GetAttack( int nTempID, int nCurKeenpoints, int nProEff, int nMWLevel, int nLevel, int nProSpir, int nHP )
	{
		if ( nHP == 0 ) {return 0;}
		CTemplateMagicWeapon* tpItemMW = (CTemplateMagicWeapon*)CDataStatic::SearchTpl( nTempID );
#ifdef LINUX
		LK_ASSERT( tpItemMW!=NULL, return 0 );
#endif
		if ( tpItemMW == NULL )
		{
			return 0;
		}

		// ��������(����)Ӱ�죺
		int nHardValue = (int)((double)nCurKeenpoints*tpItemMW->mAttackInc/SERVER_PERCENT_INT*nProEff/SERVER_PERCENT_INT);

		// �ȵõ�����ϵ��
		CTplMWLevelQuotietyTab* tpTable = (CTplMWLevelQuotietyTab*)CDataStatic::SearchTpl( tpItemMW->mLevelQuotietyTabID );
		int nLevelEff = 0;
		if ( tpTable != NULL && nLevel >= 0 && nLevel < 20 )
		{
			nLevelEff = tpTable->mKeenQuotiety[nLevel];
		}

		// ����ȼ�Ӱ�죺
		int nLevelValue = (nMWLevel+MW_LEVEL_EXTRA_EFF)*nLevelEff/SERVER_PERCENT_INT;

		return (int)(nHardValue+nLevelValue)*nProSpir/SERVER_PERCENT_INT;
	}

	// ������ҷ�����
	// ������������ģ��ID����ǰ��������ǰ����Ӱ��ȣ���ǰ�ȼ�����ǰ�����ȼ�������
	static int GetRecovery( int nTempID, int nCurCalmpoints, int nProEff, int nMWLevel, int nLevel, int nProSpir, int nHP )
	{
		if ( nHP == 0 ) {return 0;}
		CTemplateMagicWeapon* tpItemMW = (CTemplateMagicWeapon*)CDataStatic::SearchTpl( nTempID );
#ifdef LINUX
		LK_ASSERT( tpItemMW!=NULL, return 0 );
#endif
		if ( tpItemMW == NULL )
		{
			return 0;
		}

		// ��������(����)Ӱ�죺
		int nHardValue = (int)((double)nCurCalmpoints*tpItemMW->mRecovInc/SERVER_PERCENT_INT*nProEff/SERVER_PERCENT_INT);

		// �ȵõ�����ϵ��
		CTplMWLevelQuotietyTab* tpTable = (CTplMWLevelQuotietyTab*)CDataStatic::SearchTpl( tpItemMW->mLevelQuotietyTabID );
		int nLevelEff = 0;
		if ( tpTable != NULL && nLevel >= 0 && nLevel < 20 )
		{
			nLevelEff = tpTable->mCalmQuotiety[nLevel];
		}

		// ����ȼ�Ӱ�죺
		int nLevelValue = (nMWLevel+MW_LEVEL_EXTRA_EFF)*nLevelEff/SERVER_PERCENT_INT;

		return (nHardValue+nLevelValue)*nProSpir/SERVER_PERCENT_INT;
	}

	// �������MP����
	// ������������ģ��ID����ǰ��������ǰ����Ӱ��ȣ���ǰ�ȼ�����ǰ�����ȼ�������
	static int GetMaxMp( int nTempID, int nCurMagicpoints, int nProEff, int nMWLevel, int nLevel, int nProSpir, int nHP )
	{
		if ( nHP == 0 ) {return 0;}
		CTemplateMagicWeapon* tpItemMW = (CTemplateMagicWeapon*)CDataStatic::SearchTpl( nTempID );
#ifdef LINUX
		LK_ASSERT( tpItemMW!=NULL, return 0 );
#endif
		if ( tpItemMW == NULL )
		{
			return 0;
		}

		// ��������(����)Ӱ�죺
		int nHardValue = (int)((double)nCurMagicpoints*tpItemMW->mMaxMPInc/SERVER_PERCENT_INT*nProEff/SERVER_PERCENT_INT);

		// �ȵõ�����ϵ��
		CTplMWLevelQuotietyTab* tpTable = (CTplMWLevelQuotietyTab*)CDataStatic::SearchTpl( tpItemMW->mLevelQuotietyTabID );
		int nLevelEff = 0;
		if ( tpTable != NULL && nLevel >= 0 && nLevel < 20 )
		{
			nLevelEff = tpTable->mMagicQuotiety[nLevel];
		}

		// ����ȼ�Ӱ�죺
		int nLevelValue = (nMWLevel+MW_LEVEL_EXTRA_EFF)*nLevelEff/SERVER_PERCENT_INT;

		return (nHardValue+nLevelValue)*nProSpir/SERVER_PERCENT_INT;
	}

	// �������HP����
	// ������������ģ��ID����ǰ��������ǰ����Ӱ��ȣ���ǰ�ȼ�����ǰ�����ȼ�������
	static int GetMaxHp( int nTempID, int nCurBierpoints, int nProEff, int nMWLevel, int nLevel, int nProSpir, int nHP )
	{
		if ( nHP == 0 ) {return 0;}
		CTemplateMagicWeapon* tpItemMW = (CTemplateMagicWeapon*)CDataStatic::SearchTpl( nTempID );
#ifdef LINUX
		LK_ASSERT( tpItemMW!=NULL, return 0 );
#endif
		if ( tpItemMW == NULL )
		{
			return 0;
		}

		// ��������(����)Ӱ�죺
		int nHardValue = (int)((double)nCurBierpoints*tpItemMW->mMaxHPInc/SERVER_PERCENT_INT*nProEff/SERVER_PERCENT_INT);

		// �ȵõ�����ϵ��
		CTplMWLevelQuotietyTab* tpTable = (CTplMWLevelQuotietyTab*)CDataStatic::SearchTpl( tpItemMW->mLevelQuotietyTabID );
		int nLevelEff = 0;
		if ( tpTable != NULL && nLevel >= 0 && nLevel < 20 )
		{
			nLevelEff = tpTable->mBierQuotiety[nLevel];
		}

		// ����ȼ�Ӱ�죺
		int nLevelValue = (nMWLevel+MW_LEVEL_EXTRA_EFF)*nLevelEff/SERVER_PERCENT_INT;

		return (nHardValue+nLevelValue)*nProSpir/SERVER_PERCENT_INT;
	}

	// ������������ȼ�
	// ������������ģ��ID����ǰ��������ǰ����Ӱ��ȣ���ǰ�ȼ�����ǰ�����ȼ�������
	static int GetDeadLine( int nTempID, int nCurImmortalpoints, int nProEff, int nMWLevel, int nLevel, int nProSpir, int nHP )
	{
		if ( nHP == 0 ) {return 0;}
		CTemplateMagicWeapon* tpItemMW = (CTemplateMagicWeapon*)CDataStatic::SearchTpl( nTempID );
#ifdef LINUX
		LK_ASSERT( tpItemMW!=NULL, return 0 );
#endif
		if ( tpItemMW == NULL )
		{
			return 0;
		}

		// ��������(����)Ӱ�죺
		int nHardValue = (int)((double)nCurImmortalpoints*tpItemMW->mDeadLineInc/SERVER_PERCENT_INT*nProEff/SERVER_PERCENT_INT);

		// �ȵõ�����ϵ��
		CTplMWLevelQuotietyTab* tpTable = (CTplMWLevelQuotietyTab*)CDataStatic::SearchTpl( tpItemMW->mLevelQuotietyTabID );
		int nLevelEff = 0;
		if ( tpTable != NULL && nLevel >= 0 && nLevel < 20 )
		{
			nLevelEff = tpTable->mImmorQuotiety[nLevel];
		}

		// ����ȼ�Ӱ�죺
		int nLevelValue = (nMWLevel+MW_LEVEL_EXTRA_EFF)*nLevelEff/SERVER_PERCENT_INT;

		return (nHardValue+nLevelValue)*nProSpir/SERVER_PERCENT_INT;
	}
};

// ��ü��ܷ�ʽ
enum enGetSkillType
{
	GETSKILL_LEARN = 1,		// ����
	GETSKILL_JUDGE,			// ����
	GETSKILL_USEBOOK,		// ʹ�ü�����
};

// ������������
enum enMWLockType
{
	MWLOCK_SKILLJUDGE = 1,		// ���ܼ���
	MWLOCK_PROJUDGE		 ,		// ���Լ�����������
	MWLOCK_PROJUDGE_STONE ,		// ���Լ�����ʯ
};

//// ���buff����
//enum enMultiBuffType
//{
//	MULTIBUFF_SHITU = 1,	// ʦͽ����
//	MULTIBUFF_MARRY,		// ���
//	MULTIBUFF_4METIER,		// 4ְҵ��ӽ���
//	MULTIBUFF_5METIER,		// 5ְҵ��ӽ���
//	MULTIBUFF_6METIER,		// 6ְҵ��ӽ���
//};

// �û�����
enum enUserType
{
	USERTYPE_NONE = 0,
	USERTYPE_GM  = 1,		// ����GM
	USERTYPE_OFFICE = 2,	// �������ְ�����
	USERTYPE_TITLE = 3,		// ������ƺŵ����
	USERTYPE_KING = 4,		// ����
};

// ����ϴ������
enum enMW_ClearType
{
	CLEARTYPE_BIG,	// ��ϴ
	CLEARTYPE_SMALL,	// Сϴ
	CLEARTYPE_SP,	// ϴ����
};

// ����Ǳ�ܵ�����
enum enMW_POINT_TYPE
{
	KEENPOINTS		=	0,		
	CALMPOINTS	,	
	MAGICPOINTS	,
	BIERPOINTS	,	
	IMMORTALPOINTS,


	POINT_TYPE_NUM,
};


// ҩƷ����
enum enPhysicType
{
	PHYSIC_BLUE = 1,	// ��ҩ
	PHYSIC_RED,			// ��ҩ
	PHYSIC_AP,			// ����ҩ
	PHYSIC_FB_HP,		// ��������ҩ
	PHYSIC_FB_MP,		// ��������ҩ
	PHYSIC_MEND,		// �����
};

#define GET_TITLE_TYPE( x ) ( x & 0xF000 )

// ����Ƿ��ǹ����ƺ�
#define IS_NATION_TITLE( a, b ) ( \
	( a == CTplTitleManager::SPECIAL_NATION ) && \
	( b == CTplTitleManager::SCOPE_NATIONALITY ) )

// �ƺ�����
enum enTitleType
{
	EN_RANK_TYPE		= 0x1000,	// ���а���	
	EN_STATISTIC_TYPE	= 0x2000,	// ͳ����
	EN_CONDITION_TYPE	= 0x3000,	// ������
	EN_SPECIAL_TYPE		= 0x4000,	// ������
};


enum EWorld
{
	WORLD_START		= 0,
	WORLD_FIRST		= 1,
	WORLD_SECOND	= 2,
	WORLD_THIRD		= 3,
	WORLD_FOURTH	= 4,
	WORLD_NUM		= 5,
};

#define IS_WORLDID(x)	( ( (x) > 0 && (x) < 5 ) ? true : false )

enum ECountry
{
	COUNTRY_ALL			= -2,			// ����ȫ�����
	COUNTRY_NONE		= -1,
	COUNTRY_CHANGAN		= 0,
	COUNTRY_WUJI		= 1,
	COUNTRY_CHECHI		= 2,
	COUNTRY_BAOXIANG	= 3,
	COUNTRY_NVER		= 4, 
	COUNTRY_NUM			= 5,
};

enum CountryMapID
{
	COUNTRY_MAP_NVER		= 45,
	COUNTRY_MAP_CHANGAN		= 62,
	COUNTRY_MAP_WUJI		= 68,
	COUNTRY_MAP_CHECHI		= 69,
	COUNTRY_MAP_BAOXIANG	= 70,	
	COUNTRY_MAP_QITIAN		= 61,
};

enum EChangeType
{
	CHANGE_ADD	= 0,
	CHANGE_DEL	= 1,
};

enum EWorldOperationType
{
	WORLD_OP_INVITE		= 0x01,			// ������� 
	WORLD_OP_PEACE		= 0x02,			// ��������
	WORLD_OP_WAR		= 0x04,			// ������ս
	WORLD_OP_DISMISS	= 0x08,			// �������
};

enum EWorldResult
{
	WORLD_RESULT_AGREE	= 1,
	WORLD_RESULT_REFUSE	= 2,
};

enum EWorldStatus
{
	WORLD_STATUS_NONE		= 0,		// ����
	WORLD_STATUS_FRIEND		= 1,		// �Ѻ�
	WORLD_STATUS_WAR		= 2,		// ��ս
};

// ����ϵͳ ��ֵö��
// ����1 �����Ѿ���ɵĴ��� ����2 ���������ɵ�������
enum enHelpData
{
	HELPID_DOUBLE			= 1, // ˫������ �������� ��ʱ�� �������
	HELPID_QUESTION			= 2, //	ÿ�մ���
	HELPID_LONGGONG			= 3, // ������
	HELPID_PANTAO			= 4, // ��ҽ�
	HELPID_XIANTAO			= 5, // Ʒ����
	HELPID_HUANGFENGD		= 6, //	�Ʒ綴
	HELPID_BATTLE			= 7, //	��ս����ɽ
	HELPID_DAYANTA			= 8, // ������
	HELPID_LIANHUADONG		= 9, // ������
	HELPID_QUXIANTAO		= 10,// ��ʥȡ����
	HELPID_FAMILY_XIANTAO	= 11,// Ʒ����_����
	HELPID_NPC_BATTLE		= 12,//	NPC����ս
	HELPID_FAMILY_REDSTONE	= 13,// �����ڵ�
	HELPID_FAMILY_BATTLE	= 14,//	������ս��
	HELPID_NVERGUO			= 15,// ��ȢŮ����
	HELPID_FORCEBATTLE		= 16,//	��������ս
	HELPID_KING_LOGIN		= 17,// ���ٹ��ǻ�վ
	HELPID_SONOFKING		= 18,// ���ӵǻ�ս
	HELPID_CORPSBATTLE		= 19,// ������ս��
	HELPID_TODAY_LOOPS		= 20,// ��������ʦ������
	HELPID_WEEK_LOOPS		= 21,// ��������ʦ������
	HELPID_CHAIRMANTASK		= 22,// ��������
	HELPID_STORAGETASK		= 23,// �����ʰ�����
	HELPID_MINEMAP			= 24,//	ɱ���ᱦ����
	HELPID_FAMILY_SEND		= 25,// ���廤������
	HELPID_FAMILY_CHALLEGE  = 26,// ������ս����
	HELPID_CORPS_RAO		= 27,// �����ű�����
	HELPID_CORPS_SHOU		= 28,// �����ر�����
	HELPID_CORPS_CHALLEGE	= 29,//	������ս����
	HELPID_CORPS_SHOUQI		= 30,//	������������
	HELPID_SELLSELF			= 31,//	ë���Լ�	
	HELPID_FAMILY_HONOR		= 32,//	������ҫ����
	HELPID_COUNTRY_BUILD	= 33,//	���ҽ�����������

	HELPID_COUNTRY_HONOR	= 34,//	��Ӫ��������	
	HELPID_COUNTRY_FLAG		= 35,//	��������������	
	HELPID_COUNTRY_DOOR		= 36,//	���Ʊ߾�������

	HELPID_COUNTRY_JIAOZI	= 37,//	�����ͽ���
	HELPID_COUNTRY_QINGHUA	= 38,//	����黨
	HELPID_COUNTRY_WENQING	= 39,//	��������

	HELPID_COUNTRY_FULI		= 40,//	���Ҹ���
	HELPID_FAMILY_CHUYAO	= 41,//	�������
	HELPID_CAMP_HONOR		= 42,//	��Ӫ����

	HELPID_XUNXIAN			= 43, // ǧ��Ѱ��
	HELPID_SISHEN			= 44, // ��ʥ������
	HELPID_STONE			= 45, // �ɼ���ʯ
	HELPID_STONE2			= 46, // ������ʯ
	HELPID_HUANGFENG		= 47, // �Ʒ�����
	HELPID_CHIHUO			= 48, // �������
	HELPID_HEISHUI			= 49, // ��ˮ����
	HELPID_YUANXIAOJIE		= 50, // Ԫ����
	HELPID_CORP_TASK		= 51, // ��������
	HELPID_FAMILY_TASK		= 52, // ��������
	HELPID_COUNTRY_TASK		= 53, // ��������
	HELPID_CLOUD_ACTIVITY		= 54, // ������Ե
	HELPID_PILE_BATTLE		= 55, // ����ɽ����
	HELPID_BLAZE_BATTLE		= 56, // ����ɽ����
	HELPID_CHICK_COUNTRY		= 57, // �ڼ����ǻ�ս
	HELPID_ELEPHANT_COUNTY		= 58, // ������ǻ�ս
	HELPID_CAMP_TASK		= 59, // ��Ӫ����
	HELPID_FLY_FB			= 60, // ���Ƹ���
	HELPID_FLY_FB_TASK		= 61, // ���Ƹ�������
	HELPID_QINGMING			= 62, // �����ڻ
	HELPID_HYDRANGEA		= 63, // �������׻
	HELPID_LONGLING			= 64, // ���ۻ
	HELPID_NAZHA			= 65, // ��߸�ֺ�
	HELPID_LIULI			= 66, // ������յ
	HELPID_HOUWANG			= 67, // ��ٺ���
	HELPID_EVERYDAY			= 68, // ÿ������
	HELPID_REDPAPER                 = 69, // �������
	HELPID_ROSE			= 70, // ��õ�廨                
	HELPID_NVERBATTLE	= 71,  // Ů��������ս
	HELPID_CITAN				= 72,  // ��̽����
	HELPID_MEIRISHOUBIAN		= 73,  // ÿ���ر�
	HELPID_YUSHU				= 74,  // ��������
	HELPID_BAOXIANGXIUQIU		= 75,  // ����������
	HELPID_KILLZHUREN			= 76,  // ɱ����������
	HELPID_KILLWEIBIN			= 77,  // ɱ����������
	HELPID_CHIJIUBATTLE			= 78,  // �־ô���ս
	HELPID_YUHUAYUAN			= 79,  // ����԰����
	HELPID_BAODING				= 80,  // �콵�����
	HELPID_ACTIVITY520			= 81,  // 520�
	HELPID_DUANWU				= 82,  // ����ڻ
	HELPID_CAMP_TAOFA_VNM		= 83,  // Խ����Ӫ�ַ�����
	HELPID_GLOBALTEST			= 84,  // ȫ����Ի
	HELPID_DROP_ZONGZI			= 85,  // �콵���ӻ
	HELPID_JINGDOUYUN			= 86,  // ��ʥ�Ľ��
	HELPID_SONGJING				= 87,  // ʦ���о�
	HELPID_DUOBAO1				= 88,  // �ᱦ����յ1  ����ÿ���������� ��Ҫָ��
	HELPID_DUOBAO2				= 89,  // �ᱦ����յ2  ����ÿ���������� ��Ҫָ��
	HELPID_QITIANWAR			= 90,  // �����ս
	HELPID_SONGJING11			= 91,  // ʦ���о�1-1
	HELPID_SONGJING12			= 92,  // ʦ���о�1-2
	HELPID_SONGJING13			= 93,  // ʦ���о�1-3
	HELPID_SONGJING21			= 94,  // ʦ���о�2-1
	HELPID_SONGJING22			= 95,  // ʦ���о�2-2
	HELPID_SONGJING23			= 96,  // ʦ���о�2-3
	HELPID_MATAIWEI				= 97,  // ��̫ξ����
	HELPID_GONGCELIHUA			= 98,  // �����񻨻

	HELPID_SONGJING31			= 99,  // ʦ���о�3-1
	HELPID_SONGJING32			= 100,  // ʦ���о�3-2
	HELPID_SONGJING33			= 101,  // ʦ���о�3-3
	HELPID_SONGJING41			= 102,  // ʦ���о�4-1
	HELPID_SONGJING42			= 103,  // ʦ���о�4-2
	HELPID_SONGJING43			= 104,  // ʦ���о�4-3

	HELPID_SONGJING51			= 105,  // ʦ���о�5-1
	HELPID_SONGJING52			= 106,  // ʦ���о�5-2
	HELPID_SONGJING53			= 107,  // ʦ���о�5-3
	HELPID_SONGJING61			= 108,  // ʦ���о�6-1
	HELPID_SONGJING62			= 109,  // ʦ���о�6-2
	HELPID_SONGJING63			= 110,  // ʦ���о�6-3
	HELPID_OGREGONG				= 111,  // ���﹥�ǻ

	HELPID_SUOYUAN				= 112,  // ������Ը��Խ�ϻ��
	HELPID_YUNXIAOTA			= 113,  // ����������
	HELPID_FANJIAN				= 114,  // ���������
	HELPID_QIXI					= 115,  // ��Ϧ�
	HELPID_ZHONGYUANJIE			= 116,  // ��Ԫ�ڻ
	HELPID_ZHONGYUANJIE2		= 117,  // ��Ԫ�ڻ2
	HELPID_PUDU					= 118,  // ��Ԫ�ն�
	HELPID_ZHONGQIU1			= 119,  // �����1
	HELPID_ZHONGQIU2			= 120,  // �����2
	HELPID_ZHONGQIU3			= 121,  // �����3
	HELPID_GUOQING1				= 122,  // ����1
	HELPID_GUOQING2				= 123,  // ����2
	HELPID_YAOQIANSHU			= 124,  // ҡǮ��
	HELPID_BAIHUAXIANZI			= 125,  // �ٻ�����
	HELPID_WEEKNATION			= 126,  // ��������
	HELPID_ONLINEGIFT			= 127,  // �����ͺ���
	HELPID_MARKET1				= 128,  // �г�����1
	HELPID_DATAOSHA				= 129,  // ����ɱ(����ģʽ)
	HELPID_DATAOSHADUI			= 130,  // ����ɱ(���ģʽ)
	HELPID_ZHUYUSHU				= 131,  // ������
	HELPID_JUHUAJIU				= 132,  // �ջ���
	HELPID_FANGZHIYUAN			= 133,  // ��ֽ�
	HELPID_FANGZHIYUAN2			= 134,  // ��ֽ�2
	HELPID_YQSDROP				= 135,  // ҡǮ������
	HELPID_SD1					= 136,  // ʥ����1
	HELPID_SD2					= 137,  // ʥ����2
	HELPID_TREASUREBOWL			= 138,  // �۱���
	HELPID_NEW_XUNBAO			= 139,  // ��Ѱ������յ
	HELPID_NEW_XUNBAO2			= 140,  // ��Ѱ������յ2
	HELPID_NEW_FUWENBAO			= 141,  // ���İ���ȡ
	HELPID_NEW_YN_SD			= 142,  // ʥ��� ӡ��
	HELPID_2011_SPRING_TASK		= 143,  // 11��������
	HELPID_2011_SPRING_ACT		= 144,  // 11���ڻ
	HELPID_2011_OLFPLAYER		= 145,  // 11����һ
	HELPID_2011_SPRING3			= 146,  // 11���ڻ3
	HELPID_2011_SPRING4			= 147,  // 11���ڻ4
	HELPID_2011_QJ1				= 148,  // 11���˽�1
	HELPID_2011_QJ2				= 149,  // 11���˽�2
	HELPID_2011_YUANXIAO		= 150,  // Ԫ����1
	HELPID_WEAK_CAMP1			= 151,  // ����Ӫ1ָ��
	HELPID_WEAK_CAMP2			= 152,  // ����Ӫ2ָ��
	HELPID_WEAK_CAMP3			= 153,  // ����Ӫ3ָ��
	HELPID_WUDIDONG 			= 154,  // �޵׶�����
	HELPID_FAT_CHICKEN			= 155,  // �ʼ��-Խ�ϰ�
	HELPID_CITAN_NEW			= 156,  // ��̽���� ��
	HELPID_RUYI					= 157,  // ������
	HELPID_ONLINEGIFT2			= 158,  // �����ͺ���2��
	HELPID_HANSHI				= 159,  // ��ʳ���һ�
	HELPID_CHALIU				= 160,  // ������а
	HELPID_CHAODU				= 161,  // ��������		
	HELPID_ZHANYAO_VNM			= 162,  // Խ��ն���ᱦ

	HELPID_BHSH					= 163,  // �ٻ�ʢ��
	HELPID_TNSH					= 164,  // ��Ůɢ��
	HELPID_MGCQ4				= 165,  // õ�崫������	
	HELPID_TEAMLOOP				= 166,  // ��ӻ�����
	HELPID_WOKOU				= 167,  // ����֮��
	HELPID_GLOBALWAR			= 168,  // ���ս���
	HELPID_STWMG				= 169,  // ʦͽδ����
	HELPID_LINGYD				= 170,  // ���ƶ�

	HELPID_DAY_SJ				= 171,  // ÿ���о�
	HELPID_FOGUANG				= 172,  // �������
	HELPID_BAOKU				= 173,  // ���汦�� 
	HELPID_LEIYINSI				= 174,  // �����»
	HELPID_LEIYINSI2			= 175,  // ����ȡ�澭
	HELPID_XIANGBAO			= 176,  // ����ͺ���
	HELPID_QUYUAN			= 177,  // ��ɱ����ο��ԭ
	HELPID_YUENAN			= 178,   //Խ�ϻ
	HELPID_SHUANGBEIRONGYU	= 179,  // ˫�������ַ���
	HELPID_HEDANCENG		= 180,  // �ص�������������
	HELPID_XCTJ				= 181,  // ϲ���콵
	HELPID_FOGUANGPUZHAO	= 182,  // ����������ڻ
	HELPID_QIXI_LOVE		= 183,  // ��Ϧ����
	HELPID_LINGYUN_BATTLE	= 184,  // ��ս���ƶ�
	HELPID_COOL_SUMMER		= 185,  // ���������
	HELPID_VIP_WELFARE		= 186,  // ��Ա����
	HELPID_SWORN_TASK		= 187,  // �������
	HELPID_MEMBERS_MOONCAKE		= 188,  // ��Ա�±�
	HELPID_RABBIT_WINDRUG		= 189,  // ���ö�ҩ
	HELPID_REINCARNATION_SPIRIT = 190,	// ת������
	HELPID_SPIRIT_COME_TO_EARTH = 191,	// ���齵��
	HELPID_SIlVER_HAPPY_FROM_HEAVEN = 192,	// ����ϲ���콵
	HELPID_HAVOC_IN_HEAVEN			= 193,	  // 72�����칬
	HELPID_YAOHOU_HAVOC_IN_CHANGAN  = 194,	  // �����ֳ���
	HELPID_GIFTS_PUMPKIN			= 195, 	  // �����Ϲϵ�
	HELPID_STAND					= 196, 	  // ��������
	HELPID_STAND_SECOND				= 197, 	  // ��������2
	HELPID_CORPS_COLLECTION			= 198,	  // ���Ųɼ�
	HELPID_TREASURE_GLASS_FIRST		= 199,	  // Ѱ������յ1
	HELPID_TREASURE_GLASS_SECOND	= 200,	  // Ѱ������յ2
	
	HELPID_SIZE				,	// ����
	ACTIVITY_SIZE			,   // �����
};

// ��Ʒ��Чʱ���ʱ����
enum enValidType
{
	VALIDTYPE_USE = 0,
	VALIDTYPE_GET = 1,
	VALIDTYPE_EQUIP = 2, // װ����ʼ��ʱ
};


/* �ɼ���Χ
** X,Y��������������Ӱ�����Ҫ����������Ϸ�Ե�����¾����ܼ�С��
** ����ͻ����յ�����NPC��Ϣʱ�����볬����ǰ�ɼ�X,Y,�򲻴�����
** ����������߽���Ұʱ�����������ٴη��ʹ�����
**
*/
enum emViewRadius
{
	//VIEW_RADIUS = 15,		// ��ͼ�ɼ���Χ,������Ϸ�ڲ����߼��жϣ����������ͳһ��VIEW_RADIUS_X��VIEW_RADIUS_Y.
	//						// �п��ܶ���ͻ��˷�����Ϣ�����ǿͻ��˻��Զ��޸���
	//						// ���뿪NPC��Զ�رշ�����Ӿ����жϣ����Ͷ�������ɼ�/��ʧ
	VIEW_RADIUS_X = 10,		// ˮƽ�ɼ���Χ
	VIEW_RADIUS_Y = 13,		// ��ֱ�ɼ���Χ
};

enum ELookType
{
	LOOK_EQUIPMENT	= 0x01, // �鿴װ��
	LOOK_WIZARD		= 0x02, // �鿴�Ż�
	LOOK_NOUIPOP	= 0x04, // ֻ��ѯ���ݣ�������UI������ʾ
};

enum EHasBindItem
{
	BIND_ALL	= 0,
	BIND_YES	= 1,
	BIND_NO		= 2,
};

// �ƺ���Чʱ������ [12/29/2009 Macro]
enum EProTitleValidType
{
	emTitleInstant	= 0,	// ��ʱ��
	emTitleForever  = -1,	// ������
};

// ���͵�������
enum enTeleItemType
{
	TELE_RANDOM = 1, // �������
	TELE_DIGONG,	 // �ع�����
	TELE_JIYI,		 // ���䴫��
	TELE_LIST,		 // �б��ʹ��͵���
};

// ÿ�˵ļ�¼���͵�����
#define TELE_LIST_SIZE	20

// ��Ա�ȼ�
enum EVipLevel
{
	EM_VIP_NONE		= 0,	// �ǻ�Ա
	EM_VIP_NORMAL,			// ��ͨ��Ա
};

// ϴǱ�ܵ�ȼ�
#define CLEAN_POTENTIAL_LIMIT_LEVEL 30


// ������

#define BROUSE_DOC_NO_LENG  ( 30 ) 
#define BROUSE_LIST_COUNT_MAX ( 5 )
#define BROUSE_DB_UID		( 1 )

// �Զ��һ���ҩ��ʽ
enum EBuyType
{
	EM_NONE = 0,	// ������
	EM_BIND_YB,		// ��Ԫ��
	EM_UNBIND_YB,	// �ǰ�Ԫ��
	EM_BAG_MONEY,	// �������
};


enum enTimeMgrType
{
	TIMESMGR_USEFLOWER = 1,	// ʹ���ʻ�
	TIMESMGR_PURCHASE  = 2,	// ����ĳ��Ʒ����
	TIMESMGR_USEGIFT   = 3, // ��Ʒ
	TIMESMGR_FOGUANG   = 22, //�������ָ���ƴ� 
};

// ��������������
#define MAX_TIMER_MGR_LINE	100

// ÿ�����ʹ���ʻ�����
#define MAX_USE_FLOWER_TIME_PERDAY (CSceneCfgManager::GetSingleton().GetProperty_cfg()->mFlower_lmt_perday)

// ÿ��ʹ���������
#define MAX_USE_GIFT_TIME_PERDAY  10

// ��Աÿ��ʹ���������
#define MAX_VIP_USE_GIFT_TIME_PERDAY 20

// ������ʱ�����
#define PROGRESS_TIMEERROR		500	 // 500���� 

// ������ʧЧʱ��
#define  PROGRESS_INVALIDTIME	2000 // ����

// �����԰�ĵ�ͼID
#define FAMILY_HOME_MAPID	98

enum EVirtualItem
{
	EM_NOFUNC		=	0,
	EM_MONEY		=	1,		// Ǯ
	EM_BINDMONEY	=	2,		// ��Ǯ
	EM_YUANBAO		=	3,		// Ԫ��
	EM_BINDYUANBAO	=	4,		// ��Ԫ��
};


// ��ȡ�����ԭ��
enum EExpReason
{
	EXPREASON_OGRE		= 0,	// ��ֻ�ȡ�ľ���
	EXPREASON_TASK		= 1,	// �����ȡ�ľ���
	EXPREASON_REDSTONE	= 2,	// �ڵ�����
	EXPREASON_EXPITEM	= 3,	// ʹ�þ�����Ʒ
	EXPREASON_HANDINITEM = 4,    // �Ͻ���Ʒ
	EXPREASON_BUFF	   = 5,    //  BUFF����
	EXPREASON_ACTIVITY   = 6,  // �
	EXPREASON_EXCHANGE	 = 7,  // �һ�
};


enum WarStatus
{
	WAR_NONE	= 0,		// ��ս��״̬
	WAR_SUBMIT	= 1,		// ����״̬,�������콱
	WAR_BATTLE	= 2,		// ս��״̬
	WAR_BIDOVER	= 3,		// ���۽���״̬
	WAR_NOTICE	= 4,		// ��ʾ״̬
};

#define MAX_SKILL_CD_MGR_SIZE 50 // ͬʱ������ȴ�ķ������ܵ�����

#define MAX_WAR_ROOM_SIZE	200		// ս�������������

#define MAX_WAR_CAMP		3		// ս��ս����

enum BOURSE_TYPE
{
	BOURSE_TRADE_ING			= 0,
	BOURSE_TRADE_END			= 1,
	BOURSE_TRADE_CLOSE			= 2
};

enum BOURSE_KIND
{
	BOURSE_TRADE_BUY			= 0,
	BOURSE_TRADE_SELL			= 1,
};

#define BOURSE_TAX_YB( count )	( ( ( ( count ) * 20 / 1000 ) != 0 ) ? ( ( count ) * 20 / 1000 ) : 1 )
#define BOURSE_TAX_MONEY( count )	( ( ( ( count ) * 20 / 1000 ) != 0 ) ? ( ( count ) * 20 / 1000 )  : 1 )


// �ڹ���ʱ������ֵ
#define  MAX_BLACKPILLS_TIME 2000000000 // 20����

enum EAccuseType
{
	ACCUSE_NONE		= 0,	// ��״̬
	ACCUSE_YES		= 1,	// ����
	ACCUSE_NO		= 2,	// ������
	ACCUSE_ABORT	= 3,	// ��Ȩ
};

enum UpgNoticeType
{
	NOTICE_UPG_FIRST	=	4,	// ����
	NOTICE_UPG_SECOND	=	7,	// ��Ӫ
	NOTICE_UPG_THIRD	=	9,	// ����
};

enum JewNoticeType
{
	NOTICE_JEW_FIRST	=	7,	// ����
};

enum GlobalNoticeType
{
	UPG_NOTICE			=	1,	// װ����ʾ
	JEW_NOTICE			=	2,	// ��ʯ��ʾ
};
enum RuneColorType
{
	WHITE_RUNE       =  0, //��ɫ����
	BLUE_RUNE		 =  1, //��ɫ����
	PURPLE_RUNE		 =  2, //��ɫ����
	GOLD_RUNE		 =  3, //��ɫ����
};

// ���������ṩ�Ĳ���ȡֵö��
enum MWQLParamIdx
{
	QLIDX_KEENPOINTS,       // ���ӵ�����
	QLIDX_CALMPOINTS,		// ���ӵĶ���
	QLIDX_MAGICPOINTS,		// ���ӵķ���
	QLIDX_BIERPOINTS,		// ���ӵ�����
	QLIDX_IMMORTALPOINTS,	// ���ӵ�����
	QLIDX_REPLYSKILLBOC,	// �滻�󷨱����ܿ��
	QLIDX_COLOR,			// ��ɫ
	QLIDX_LEVEL,			// Ʒ��
	QLIDX_PROP,				// ӡ�Ǹ���
	QLIDX_MONEY,			// ӡ�Ƿ���
	QLIDX_COMPOS_MONEY_TYPE,	// �ϳɽ������
	QLIDX_COMPOS_MONEY,			// �ϳɽ��
	QLIDX_COMPOS_ID,			// ����ID
	QLIDX_COMPOS_PROB,			// ��������
};

// ������������
enum EMWUPTYPE
{
	MWUp_Color = 0, // ����
	MWUp_Level = 1, // ��Ʒ
};

#define MAX_MW_QL_COMPOSE_NUM 5 // �����ٸ�����ϳ�

// ȫ�ָ�����״̬
enum EGLobalWar_Status
{
	EGLOBALWAR_STATUS_NULL			= 0,	// δ����
	EGLOBALWAR_STATUS_APPLY			= 1,	// ����״̬	
	EGLOBALWAR_STATUS_APPLYSUCESS	= 2,	// �����ɹ�,Ԥ������ս��
	EGLOBALWAR_STATUS_INWAR			= 3,	// ��ս����  	
	EGLOBALWAR_STATUS_INGLOBALSCENE	= 4,	// ��ȫ�ַ�������
};
