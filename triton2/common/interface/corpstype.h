#pragma once
#define  MAX_CORPSNAME_LENGTH	40			// ��������
#define  LEVEL_CREATCORPS		40			// ��������ʱ���������ٵȼ�
#define  MAX_OFFICER_NUM		10			// ���ŵĹ�Աְλ����
#define  MAX_CORPS_FAMILYNUM	20			// ���ŵļ����������
#define  MAX_CORPSNUM			2000		// ���ŵ��������
#define  MAX_CORPSAPPLY_NUM		30			// ���ŵ���������б�
#define  CORPSDISBAND_NUMBERLIMIT	50		// ���ŵĽ�ɢ����
#define	 CORPS_BULLETIN_LENGTH		300		// ���Ź�����ַ�����
#define  CORPS_MONEY_CREATCOPRS	300000		// ����������Ҫ�Ľ�Ǯ30��
#define  MAX_COPRSPBBUFFER_LENGTH	1024	// ����pb�ṹ�������������󳤶�
#define  COUNT_LOADCORPS	10				// ���ؾ�����Ϣʱÿ�δ����ݿ��ȡ�Ĵ���
#define  COUNT_LOADCORPSBID	20				// ���ؾ��ž�����Ϣʱÿ�δ����ݿ��ȡ�Ĵ���
#define  COUNT_LOADCORPSBATTLE	20			// ���ؾ���ս����Ϣʱÿ�δ����ݿ��ȡ�Ĵ���
#define  CORPSTIMER_UPDATE_TIMELENGTH 30000	// ������Ϣ�ĸ���ʱ��  30��
#define  CORPS_DISBAND_TIMELENGTH  86400	// 86400 ���ŵĽ�ɢʱ��
#define	 CORPS_LEVEL_LIMIT			5		// ���ŵȼ�����
#define  CORPS_BATTLE_NUM	100				
#define  CORPS_MAXMEMBERNUM     300			// ���ŵ��������
#define	 MAX_UNION_NUM			2000		// �����������
#define  MAX_CORPS_UNION		10			// ��������������(��������������)
#define  MAX_OTHER_UNION		9			// ��������������
#define  MAX_CORPS_NPCOWNER		20			// ���ſ�ռ���npc�����
#define  MAX_BATTLESIZE			300			// ��ս�������

#define CORPSTIMER_DISBAND_TIMELENGTH	600000	// �������ɢʱ���ʱ����10����
#define CORPSTIMER_CHECK_NPC_STATE		5000	// ������ս����NPC״̬��ʱ�� 5��
#define SUBMIT_TIME_BEFORE_BATTLE		1800	//���۽�����ս����ʼ֮��ѡ�����ݵ�ʱ�䣬30����
#define BID_CLOSE_TIME_BUCKET			4500	//���۽������������¿�ʼ��ʱ�䣬75����

#define MAX_CORPS_BOSS_NUM		20				//������boss��

enum ECorpsPost
{
	CORPS_POST_CORPSHEADER	= 0,	//	�󽫾�
	CORPS_POST_GENERAL		= 1,	//	ǰ�潫��	 
	CORPS_POST_COUNSELLOR	= 2,	//	��ʦ
	CORPS_POST_FAMILYHEADER	= 3,	//	��������
	CORPS_POST_MEMBER		= 4,	//	��ͨ��Ա
};

enum ECorpsMoney
{
	CRONTRIBUTEMONEY_BYMEMBER = 1,		// ���˾��׾��Ž�Ǯ
	CRONTRIBUTEMONEY_BYFAMILY = 2,		//	������׾��Ž�Ǯ
};

// ����ս��״̬
enum ECorpsWarStatus
{
	CORPS_WAR_FREE	= 0,	// ����
	CORPS_WAR_BIDING,		// ������
	CORPS_WAR_WAITING,		// ���۽���,�ȴ���ս
	CORPS_WAR_IN,			// ս����
};

enum ERoomAction
{
	ROOM_CLOSE = 0,
	ROOM_OPEN,
};

enum ERoomState
{
	ROOM_STATE_OPEN = 0, // ������ս
	ROOM_STATE_BUSY,
	ROOM_STATE_INWAR,	 // ս����
	ROOM_STATE_NONE,	 // ������
};

enum ECorpsChallegeAction
{	
	CHALLEGE_CANCEL = 0, // ȡ����ս 
	CHALLEGE_REQUEST,	 // ������ս
};

enum EBattleMap
{
	CORPS_BATTLE_SCABBLE = 71, // ��������ͼ
	CORPS_BATTLE_MAP = 80,	// ��ս����ͼ
};

enum ECorpsBattleType
{
	TYPE_BATTLE_CHALLEGE = 0,	// ��ս��
	TYPE_BATTLE_SCRABBLE,		// ������
	TYPE_BATTLE_ALL				// �������� Add by DLC @2010-7-13
};

enum ECorpsErrCode
{
	CORPS_NOTICE_DESFORAGEDEAD = 0x1001,	// �Է����ݳ�������
	CORPS_NOTICE_SRCFORAGEDEAD,				// �������ݳ�������
	CORPS_NOTICE_FORAGEUPDATE,				// ���ݳ���ˢ��
	CORPS_NOTICE_GATEKILLED,				// ���ű���
	CORPS_NOTICE_FLAGCHANGE,				// ����仯
};

enum ETypeCorpsFamily
{
	TYPE_FAMILY = 0,
	TYPE_CORPS,
};

#define GAMBLE_FUND_PERCENT		90	// ��ս������(90%)
#define PERCENT	100.0f

enum EMakeUnionOP
{
	EM_CORPS_MAKE_INFO	= 0,		// ��ѯ��Ϣ
	EM_CORPS_MAKE_MODIFY = 1,		// �޸���Ϣ
	EM_CORPS_MAKE_INVITE = 2,		// ����ǩ��
	EM_CORPS_MAKE_SIGN = 3,			// ǩ��
	EM_CORPS_MAKE_CLOSE = 4,		// �ر�
};

// ����ս��չ�׶�
enum ECorspBattleStep
{
	emBidStep	= 0,	// ���۽׶�
	emSubmitStep,		// �����׶�
	emFightStep,		// ս���׶�
	emFinshStep,		// ս������
};

// �Ƿ������� [12/2/2009 Macro]
#define IS_MAIN_CITY( x ) ( \
	x == COUNTRY_MAP_CHANGAN || x == COUNTRY_MAP_WUJI \
	|| x == COUNTRY_MAP_CHECHI  || x == COUNTRY_MAP_BAOXIANG \
	|| x == COUNTRY_MAP_NVER )
#define IS_CHANGAN( x ) ( x == COUNTRY_MAP_CHANGAN ? true : false )

// ��ս���� [12/2/2009 Macro]
#define MAX_CHALLEGE_TIMES	3

enum EOrgType
{
	emTypeCorps = 0,	// ����
	emTypeUnion,	// ����
};

// ���ǡ�Ұ��ͼ����
enum ECorpsMapType
{
	emMapMain = 0,	// ����
	emMapNormal,	// Ұ��ͼ
};

// 
#define ID_SWAP 10000000
#define GATENPCID(npcid,countryid)	( npcid + countryid * ID_SWAP )	//��������NPCID
#define SCENENPCID(id,countryid)	( id - countryid * ID_SWAP )	//��ԭ����NPCID
#define SCENENPCID_2(id)			(id % ID_SWAP)					//��ԭ����NPCID
#define SCENESERVERID(id)			(id / ID_SWAP)					//��ԭ����ServerID
// ��֤����ID�Ƿ���ȷ
#define IS_COUNTRYID(x) ( ( x > 0 && x < 5 ) ? true : false )

// 
enum ENationTitleAction
{
	emNoneAction = 0,	// ����Ϊ
	emJoinNationality,	// �������
	emHoldNation,		// ռ�����
	emHoldWildMap,		// ռ��Ұ���ͼ
};

// ����ս����buffʱ��15����
#define SCRABBLE_BATTLE_BUFFTIME	(15*60)


//=========================================================================
// ����ϵͳ��ض���
//=========================================================================
// ��Ӫ���Ƽ���
enum EM_WeakLevel
{
	EWL_Normal					= 0,	// ��������Ӫ
	EWL_Level_1					= 1,	// ����һ����Ӫ
	EWL_Level_2					= 2,	// ���ƶ�����Ӫ
	EWL_Level_3					= 3,	// ����������Ӫ
};

// ��������
enum EM_AwardType
{
	EAT_Buff					= 0,
	EAT_GiftPackage				= 1,	// ���
	EAT_Task					= 2,	
};
