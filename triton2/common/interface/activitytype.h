#pragma once

#define	MAX_QUESTIONLIB_NUM			1000						// �������
#define	TOTAL_QUESTION_NUM			( MAX_QUESTIONLIB_NUM*20 )	// ��Ŀ����
#define	XML_ELEMENT_NAME_LENGTH		40							// xml���ֳ���
#define MAX_APPTYPE_NUM				5							// ���Ӧ�ø���
#define MAX_ANSWER_STRLEN			30							// ���ַ�������󳤶�
#define LIB_ROOT_NAME				"LIBRARY_LIST"				// ����б�xml��ʶ��
#define LIB_LIBRARY_NAME			"LIBRARY"					// ���xml��ʶ��
#define LIB_QUESTION_NAME			"QUESTION"					// ��Ŀxml��ʶ��
#define	MAX_PLAYER_QUESTIONNUM		20							// ÿ��������Ĵ�����Ŀ
#define EACH_QUESTION_TIMELENGTH	10							// ÿ������Ĵ���ʱ��
#define TOTAL_QUESTION_TIMELENGTH	300							// �����������ʱ��
#define	MAX_CREATED_LIBNUM			30							// ѡ��ʱ�п��ܲ���������������
#define MAX_RANDOM_QUESTIONNUM		50							// ��������������Ŀ��
#define MAX_QUESTIONNUM_EACHLIB		50							// ÿ�����������Ŀ����
#define MAX_INVEST_PRIZENUM			10							// �����ʾ���Ʒ��������
#define MAX_INVEST_QUESTLIBNUM		40							// �����ʾ������������
#define MAX_INVESTANSER_DBBUFFERLENGTH 1024						// �����ʾ�Ĵ𰸵�����ַ�������
#define ACTIVITY_TIMER_LENGTH		1800000
#define HYDRANGEA_TIMER_LENGTH      1000						// �����ʱ���ļ������
#define HYDRANGEA_TIMENUM			10							// ���ʱ����Ϣ����

#define MAX_NPCPRIZE_NUM			10							// npc���⽱�������ֵ
#define MAX_OPTION_NUM				15							// ��������ѡ����Ŀ
#define INVESTRECORD_TIMER_LENGTH   120000						// �����ʾ�����ʱ������
#define PRELIMINAY_PBBUFFER_LENGTH	5000						// �����ֽڳ���

#define CREATELIBID( TYPE, ID ) \
TYPE*1000000+ID					\

#define  MAKETIMEID( MONTH, DAY, HOUR  ) \
MONTH*10000 + DAY*100 + HOUR;	\

#define  MAX_ACTIVITYOGRE_NUM		50							// ��ֵ�������� 

enum EInvestType			// �����ʾ�Ĵ�������
{
	INVEST_TYPE_TIME	= 1,		// ����ʱ��㴥��	
	INVEST_TYPE_MAP		= 2,		// ���ݳ���ĳ����ͼ����
	INVEST_TYPE_ACTIVIY	= 3,		// �
	INVEST_TYPE_LEVEL	= 4,		// ���ݵȼ�����	
	INVEST_TYPE_METIER	= 5,		// ����ְҵ����
	INVEST_TYPE_SEX		= 6,		// �����Ա𴥷�
};

enum EBidState
{
	STATE_BIDDING		= 0,		// ���徺����
	STATE_SUBMITTING	= 1,		// ���屨����
	STATE_FIGHTING		= 2,		// ����ս����
};

enum EBattleResult
{
	WIN_ATTSIDE				= 1,
	WIN_DEFSIDE				= 2,
};


//************************************************************************
// ������������ػ ��������
//************************************************************************

enum enActivityType
{
	ACTIVITY_START,	// ���ʼ
	ACTIVITY_END,	// �����
	ACTIVITY_ACTION_GETGIFT = 100, // ��ȡ����
	ACTIVITY_ACTION_ONCREATE = 200, // �������
	ACTIVITY_ACTION_LEVELUP = 300, // �������
};

// �״̬
enum enActivityState
{
	ACTIVITYSTATE_NOT_START,	// δ����(�����)
	ACTIVITYSTATE_STARTED,		// ������(���ʼ)
};

#define ACTIVITY_TIME_LST_SIZE	20
#define ACTIVITY_MAPDROP_SIZE	30
#define MAX_MAP_ID				300
#define DROP_MAPS_STR_LEN		400
#define ACTIVITY_DROP_SZ		5000	// ������Ϣ ����
#define SINGLE_ACTIVITY_DROP_SZ		1000	// ÿ���������Ϣ ����
#define ACTIVITY_OGREINDEX_SZ	200	// ÿ������������Ĺ�����������
#define MAX_HYDRANGEANPC_NUM 20 // ����npc���������
#define MAX_TEMPENTITY_NUM 20 // ÿ��ģ�����õ����npc����

#define MAX_TREASUREBOWL_EXCHANGENUM 20	// �۱������ɵ���Ʒ���ܸ���������
#define MAX_TREASUREBOWL_PROBALITY_NUM 50	// �۱���һ�������Ϣ���������
#define MAX_TREASUREBOWL_ITEM_NUM 200	// �۱����ܹ����ڶԻ�����Ʒ����
#define MAX_TREASUREBOWL_SPACENUM 3		// �۱����ܹ����ڶԻ�����Ʒ����


// ������ķ�ʽ
enum Em_HydrangeaThrowType
{
	THROWTYPE_BYPLAYER = 0,		// ��������׳�
	THROWTYPE_BYNPC    = 1,		// ����ϵͳ�׳�	
};	

// ��������������
#define  MAX_HYDRANGEARABER_NUM 100

// ��������״̬
enum Em_HydrangeaActivityStatus
{
	HYDRANGEASTATUS_NULL				= 0,	// �δ��ʼ���߽���
	HYDRANGEASTATUS_START				= 1,	// ��Ѿ���ʼ
	HYDRANGEASTATUS_HOLD				= 2,	// ����ĳ����ռ�е�״̬
	HYDRANGEASTATUS_GRAB				= 3,	// ��������״̬	
};

// ����״̬
enum Em_HydrangeaStatus
{
	PLAYER_HYDRANGEASTATUS_NULL		=	0,		// û������״̬
	PLAYER_HYDRANGEASTATUS_HOLD		=	1,		// ������г�������
	PLAYER_HYDRANGEASTATUS_OWEN		=	2,		// ������������
};

// Ǭ�������
// �����ڲ�ʹ�õĽ�������
enum enum_luckybag_award_type
{
	LUCKYBAG_AWARD_ITEM = 1, // ��������
	LUCKYBAG_AWARD_MONEY = 2, // ������Ǯ
	LUCKYBAG_AWARD_BAG = 3, // ���������Ѿ���LUA�����˽�����
	LUCKYBAG_AWARD_OTHER = 4, // �����������Ѿ���LUA�����˽�����
	LUCKYBAG_AWARD_TELEPORT = 5, // ����
};

// ��ѡ��
enum EOptionType 
{
	OPTION_A = 0x0001,
	OPTION_B = 0x0002,
	OPTION_C = 0x0004,
	OPTION_D = 0x0008,
	OPTION_E = 0x0010,	
	OPTION_F = 0x0020,	
	OPTION_G = 0x0040,	
	OPTION_H = 0x0080,	
	OPTION_I = 0x0100,	
	OPTION_J = 0x0200,	
	OPTION_K = 0x0400,	
	OPTION_L = 0x0800,	
	OPTION_M = 0x1000,	
};

// �����ʾ��״̬
enum EInvestStatus
{
	INVEST_STATUS_LEVELINVEST = ( 1 >> 0 ),	// ���ݵȼ������ĵ����ʾ�
};

// �ƾٰ������
enum EPreliminaryListType
{
	PREMILINARYLISTTYPE_TUESDAY		=	1,		//	��2��
	PREMILINARYLISTTYPE_THURSDAY	=	2,		//	��4��		
};	

#define  MAX_PRELIMINARY_TOPLISTNUM 50		// ���԰���������
#define  MAX_PRELIMINARY_QUESTIONNUM 100	// ������Ŀ���������

enum EPreliminaryStatus
{
	PRELIMINARYSTATUS_NULL				= 0,		// �δ��ʼ
	PRELIMINARYSTATUS_READY				= 1,		// �����ʱ״̬		
	PRELIMINARYSTATUS_ANSWERQUESTION	= 2,		// �����״̬
	PRELIMINARYSTATUS_NOTIFYANSWER		= 3,		// ����֤״̬
};

enum ECampLimitType							// ��Ӫ��Ϣ����������
{
	CAMPLIMITTYPE_NULL	= 0,				// û������
	CAMPLIMITTYPE_LEVEL	= ( 1 << 0 ),		// �ȼ�����
};

// ����
enum EOgreActivityType
{
	OGREACTIVITY_NULL			=	0,	// û�л��Ϣ
	OGREACTIVITY_STARTOGRESIEGE	=	1,	// ���﹥�ǿ�ʼ����ʾ��Ϣ
	OGREACTIVITY_ENDOGRESIEGE	=	2,	// ���﹥�ǽ�������ʾ��Ϣ		
};

// �Event ID
enum enActivityEvents
{
	ACTIVITY_EVENT_START		= 1, // �����
	ACTIVITY_EVENT_END			= 2, // �����
	ACTIVITY_EVENT_USEITEM		= 3, // ʹ�û��Ʒ
	ACTIVITY_EVENT_USR			= 100, // 100�Ժ�����û��Զ���
};



// ������֤������
enum EQuestionVerifyKind
{
	VERIFYKIND_NULL		= 0,			// ����֤
	VERIFYKIND_REPETION = 1,			// ����������֤
										// ����
};

// ������֤�ķ�ʽ
enum EQuestionVerifyType
{
	VERIFYTYPE_NULL		=	0,				// û������
	VERIFYTYPE_TIMEOUT	=	( 1 << 0 ),		// ��ʱΪ������
	VERIFYTYPE_OFFLINE	=	( 1 << 1 ),		// ����Ϊ�������
};

// ������֤�Ľ��
enum EQuestionVerifyReasultReason
{
	VERIFYREASON_ANSWER		= 0,		// �����ȡ�Ľ��
	VERIFYREASON_TIMEOUT	= 1,		// ��ʱ��ȡ�Ľ��
	VERIFYREASON_OFFLINE	= 2,		// ���߻�ȡ�Ľ��				
};

// ��ͼ����
enum EMapDropType
{
	DROPTYPE_ADD, // ���
	DROPTYPE_REPLACE, // �滻
};