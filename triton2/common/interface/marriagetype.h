#pragma  once 

#define  WEDDING_TIME_DUARING 360		// ���ڵļ��Ϊ6����			   
#define  WEDDING_VALIDETIME	900			// ����ʼ����Ծ��л������Чʱ��
#define  DEFAULT_WEDDINGTIMELENGTH	1800	// Ĭ�ϵĻ���ʱ��
#define  WEDDING_TIPSTIME		3600	// ����ʱ��
#define  DEFAULT_WEDDINGMAXTIMELENGTH 3600	// ��������ʱ��

#define  WENDDINGDAYS	3				// ���ڿ�ѡ���뵱ǰʱ�伸���ڵ�ʱ��
#define  DAYSECOUNDS	86400			// һ�������
#define  MARRIAGELOADNUM	30			// ������Ϣһ�λ�ȡ������
#define  MAX_WEDDNGTIMEAREA_NUM	 20		// ���Ļ���ʱ�����Ŀ

#define MARRY_APPLY_VALIDTIMELENGTH	300000	//	�������Чʱ�䳤��300��   
#define WEDDING_ONSTREET_TIMELENGTH  600	// �ڻ������е�ʱ�䳤��(600��)	
#define SYSMAIL_INVITATION_ID 31			// �����ʼ�ʹ�õ�ϵͳ�ʼ�ID 
#define  WEDDING_NOTIFY_INTERVAL	20		// ���ͽ��֪ͨ��ʱ����(��)
#define  VALIDTIMELENGTH_TOWEDING	600		// ѡ�����ʱ��ʱ���������ʱ�����������Чʱ��

#define  WEDDINGNPC_TIMER_LENGTH	300			// ������npc��ʱ������
#define  MARRIAGESTATUS_TIMER_LENGTH	3000	// ������״̬npc��ʱ������
#define  BAITANGSTATUS_TIMER_LENGTH	10000		// ����������ļ�ʱ��

//  ����npc·����
#define  MAX_WEDDINGNPCPATH_STEPS 300	

//  ��������ʱ������
#define MAX_WEDDING_TIMERNUM	20		   


// ���״̬
enum EM_MarriageStatus
{
	MARRIAGESTATUS_NOTMARRIED		= 0,		// δ��״̬
	MARRIAGESTATUS_MARRY			= 1,		// ���
	MARRIAGESTATUS_WEDDINGINWAIT	= 2,		// �ȴ�����ľ���
	MARRIAGESTATUS_WEDDINGONSTREET	= 3,		// ��������״̬
	MARRIAGESTATUS_WEDDINGONHALL	= 4,		// ���û���
	MARRIAGESTATUS_WEDDINGEND		= 5,		// �������
	MARRIAGESTATUS_WEDDINGFAILED	= 6,		// ���û���ʱ�䵫��δ�ܾ��л���
};

// ����״̬
enum EM_WeddingStatus
{
	WEDDINGSTATUS_NOTSET		=	1,			// ����δ����
	WEDDINGSTATUS_TIMENEAR		=	2,			// ����ʱ�伴��(һСʱ)
	WEDDINGSTATUS_INTIME		=	3,			// �Ѿ��ڻ���ʱ������( ����ʼ10����֮�� )
	WEDDINGSTATUS_EXPIRED		=	4,			// �����Ѿ�����( �Ѿ���������ʼʱ��10���� )
	WEDDINGSTATUS_NOTINTIME		=	5,			// ����ʱ��δ��(�������ʼ����1Сʱ)
	WEDDINGSTATUS_FINISHED		=	6,			// �����Ѿ�����(������ϻ���δ����)
};

enum EKeepsakeStatus
{
	KEEPSAKSTATUS_EMPTY			=	0,			// ����δ����״̬
	KEEPSAKESTATUS_PUT			=	1,			// ���ﴦ�ڷ���״̬
	KEEPSAKESTATUS_EXCHANGE		=	2,			// ���ﴦ�ڽ���״̬
};

// �����һЩʱ��״̬��Ϣ
enum Em_WeddingEventStatus
{
	EVENT_WEDDINGNOTIFY			=	( 1 ),					// �������ѵ��¼�
	EVENT_WEDDINGINTIMENOTIFY	=	( 1 << 1 ),				// �Ѿ��ڻ��ڵ��¼�
	EVENT_WEDDINGBAITANG		=	( 1 << 2 ),				// �������
	EVENT_BAITANGEND			=	( 1 << 3 ),				// ���ý������¼�
	EVENT_EXCHANGEKEEPSAKE		=	( 1 << 4 ),				// ��������״̬
}; 

// ����Ŀ�ʼ����
enum EWeddingStartType
{
	WEDDINGSTARTTYPE_PLAYER	=	1,		// ��ҿ�ʼ����
	WEDDINGSTARTTYPE_SYS	=	2,		// ϵͳ��ʼ����
};

