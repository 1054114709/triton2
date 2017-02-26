#pragma  once
//Enums
//
//enum ETask
//{
//	ERROR_TASK_SUCCESS				=	1300,
//	ERROR_TASK_HASACCEPT			=	1301,		// �����ѽ���
//	ERROR_TASK_HASDONE				=	1302,		// ���������
//	ERROR_TASK_OUTOFSPACE			=	1303,		// �����б�����
//	ERROR_TASK_DIALOGIDINVALID		=	1304,		// ����Ի�ID��Ч
//	ERROR_TASK_TASKIDINVALID		=	1305,		// ����ID��Ч
//	ERROR_TASK_NOTCOMPLETE			=	1306,		// ����û�����
//	ERROR_TASK_NOSPACE				=	1307,		// û���㹻�İ����ռ�
//	ERROR_TASK_ACCEPTINVALID		=   1308,		// ����������������
//	ERROR_TASK_ABORTINVALID			=   1309,       // �����ܱ�����
//};
//
//enum ETaskTip
//{
//	TASKTIP_NONE					= 0,			// ������û���κι�ϵ
//	TASKTIP_ACTIVE					= 1,			// ��������Խ�
//	TASKTIP_BEGIN					= 2,			// ��������Խ�( û����� )
//	TASKTIP_COMPLETE				= 3				// ��������Խ�( �Ѿ���� )
//};
//
//
//enum ETaskProgress
//{
//	TASK_BEGIN						= 0,			// �����Ѿ����ܣ�������
//	TASK_COMPLETE					= 1,			// �����Ѿ���ɣ�����û�н�
//	TASK_END						= 2,			// �����Ѿ�����
//	TASK_ACTIVE						= 3,			// �����Ѿ�����
//};

#define ONTIMER_REFRESH_TASK		(30*60)UL		// ��Сʱˢ�¸��˷���
#define RECV_AWARD_LIMITS_TIME		(12*60*60)UL	// 12Сʱ�޶�������ȡ����˷�����������ʧ

enum TaskErrCode
{
	DES_INVITED_LIST_FULL		= 1501,  // �Է��ı������б���
	DES_INVITED_THIS			= 1502,  // �Ѿ��������������������
};


enum TASK_DEFINE
{
	TASK_DATA_SIZE				= 16,
	TASK_LIST_SIZE				= 30,
	COMPLETE_TASK_BIT_SIZE		= 2500,
	COMPLETE_TASK_NUM			= 1500,
	FAILED_TASK_NUM				= 500,
	PUBLISH_LIST_SIZE			= 50,  
};

//// ��������
//enum enTaskType
//{
//	TASKTYPE_MAIN		= 1,	// ��������
//	TASKTYPE_LATERAL	,		// ֧������
//	TASKTYPE_WEST		,		// ��������
//	TASKTYPE_TRAGEDY	,		// ��������
//	TASKTYPE_LOOP		,		// ��������
//	TASKTYPE_STORAGE	,		// ��������
//	TASKTYPE_SCROLL		,		// ��������
//};

// ��������
enum enTaskType
{
	TASKTYPE_MAIN		= 0x0001,		// ��������
	TASKTYPE_LATERAL	= 0x0002,		// ֧������
	TASKTYPE_WEST		= 0x0004,		// ��������
	TASKTYPE_TRAGEDY	= 0x0008,		// ��������
	TASKTYPE_LOOP		= 0x0010,		// ��������
	TASKTYPE_STORAGE	= 0x0020,		// ��������
	TASKTYPE_PUBLISH	= 0x0024,		// ��������
	TASKTYPE_SCROLL		= 0x0040,		// ��������
	TASKTYPE_MINEMAP	= 0x0080,		// �ر�ͼ����
	TASKTYPE_LUCK		= 0x0100,		// ��Ե����
	TASKTYPE_FAMILY		= 0x0200,		// ��������
	TASKTYPE_CORPS		= 0x0400,		// ��������
	TASKTYPE_ACTIVITY	= 0x0800,		// �����
	TASKTYPE_NATION		= 0x1000,		// ��������
	TASKTYPE_CHAIRMAN	= 0x2000,		// ��������
	TASKTYPE_CAMP		= 0x4000,		// ��Ӫ����
};

// ���������״̬
enum enTragedyTaskState
{
	TRAGEDY_ACTIVE		   ,    // ������Խ���
	TRAGEDY_GOT			   ,	// �ѽ��ܣ��ͻ��˽��ܰ�ť�ҵ���
	TRAGEDY_COMPLETED	   ,	// �����
	TRAGEDY_DISABLED	   ,	// ���ɽ�
};

// ������ɫ
enum enTaskColor
{
	COLOR_WHITE   = 1, //--��
	COLOR_BLUE    = 2, //--��
	COLOR_PURPLE  = 3, //--��
	COLOR_GOLD    = 4, //--��


	COLOR_TOTAL   = 4, //--��ɫ����
};

#define TASK_NAME_LENGTH 128
#define TASK_DESC_LENGTH 512

#define MAX_COLLECT_TASKS 10  // �ɼ�NPC������������������

#define MAX_TASK_NUM  65536  // ϵͳ֧�ֵ����������

#define MAX_EVENTS_PER_TASK 40

#define TASK_NPC_TALK_LENGTH 512
#define TASK_PLAYER_TALK_LENGTH 512

#define MAX_NPC_TASK_NUM 64

#define SECTION_MAX			32
#define NPC_ACTIVET_TASKS	64
#define DIALOG_OPTION		16
#define ACCEPT_TASK			512

// �����������
#define TASK_INVITE_MAX		5

// �����������
#define TASK_INVITED_MAX	10

// ÿ�ֵĻ��������������� 
#define LOOP_SUB_NUM        10

// ������������
#define TRAGEDY_TASK_SIZE	81

// �����м�Ի�NPC�������
#define MAX_NPC_TALK_NUM	6

enum TaskState
{
	TASK_BEGIN						= 0,			// �����Ѿ����ܣ�������
	TASK_COMPLETE					= 1,			// �����Ѿ���ɣ�����û�н�
	TASK_END						= 2,			// �����Ѿ�����
	TASK_ACTIVE						= 3,			// �����Ѿ�����
	TASK_FAILED						= 4,			// ������ʧ��
	TASK_TOEND						= 5,			// �����������������ڲ�ʹ�ã�
};

typedef struct 
{
	unsigned short		mTaskID;			// ����ID
	unsigned short		mTaskProgress;		// �������
	int					mTimer;				// ����ʱ��, -1 ��ʾû�м�ʱ��0 ��ʾ��ʱ��
	unsigned short		mTaskData[TASK_DATA_SIZE]; //��������

	unsigned short		mLoopTaskID;		// ������ID
	unsigned short      mCompletedLoops;    // ���������
	unsigned short      mLoopID;            // ��ID
} TaskData;


enum EButtonType 
{
	TYPE_WINDOW = 1,				// ����һ���´���
	TYPE_FUNC ,					// ����ĳ�ֹ���
};

typedef enum EWindowType 
{
	WINDOW_NONE	  = 0,			// ������
	WINDOW_COMMON,				// ��ͨ
	WINDOW_AWARD,				// ����
	WINDOW_ACCEPT,				// �������
	WINDOW_ENDTALK,				// �����Ի�����
}emTaskWindowType;

enum EButttonFunc 
{
	FUNC_RETURN = 1,			// ����
	FUNC_CLOSE,					// �ر�
	FUNC_EXTANDTASK ,			// ��������
	FUNC_CALLBACKTASK ,			// �������
	FUNC_ERRORANSWER,			// ����Ĵ���ѡ�� 
	FUNC_UI_UPEQT,				// �������� (��NPC�Ի��������ܽ���)
	FUNC_UI_PRODUCE,			// �������棨��Ϸ�а�P��
	FUNC_UI_GUIRD,				// ͨ���«���棨��Ϸ�а�B���������������������ͼ��򿪣�
	FUNC_UI_STOVE,				// ����¯���棨��Ϸ�а�B�������������Ҽ�������ͼ��򿪣�
	FUNC_ENDTALK,				// ������NPC�ĶԻ�
	FUNC_UI_SKILL,				// ���ܽ���
};

enum ACCEPT_TASK_RETURN_CODE 
{ 
	ACCEPT_OK = 0, 
	LEVEL_FAIL = -1,
	MONEY_FAIL = -2,
	METIER_FAIL = -3,
	SEX_FAIL = -4,
	RE_GET = -5 //�����ظ���
};

enum PLAYER_ATTRIB_TYPE
{
	PLAYER_MONEY  = 1,
	PLAYER_EXPR   = 2,
	PLAYER_LEVEL  = 3,
	PLAYER_REGION = 4,
	PLAYER_SEX    = 5,
	PLAYER_MEITRE = 6,
	PLAYER_CAMP	 = 7,
};



enum ETaskCtrl
{
	CTRL_REPEATEABLE		= 1,    // ����ɹ�����ظ�
	CTRL_CANCELABLE		= 2,    // ������Ա�����
	CTRL_RETRYABLE		= 3,    // ����ʧ�ܺ��������
	CTRL_DIRECTCOMPLETE	= 4,	// ����ֱ�����
	CTRL_FAILONKILLED		= 5,	// ��ұ�ɱ������Ϊ����ʧ��
	CTRL_SENDNPC,				// ����NPCģ��ID
	CTRL_MAXGIRD,				 // ��������
	CTRL_NAME,					 // ��������
	CTRL_OFF_FAIL,				// �Ƿ����߾�ʧ��
	CTRL_TASKGROUP,				// ������ID
	CTRL_ISAUTOABORT,			// �Ƿ�ʧ�ܺ��Զ�����
	CTRL_ISSHARE,				// �Ƿ���ɺ����ͬ�����
	CTRL_TIMEOUT_TYPE,			// ��ʱ����ʱ�䵽�Ժ�Ĳ���
	CTRL_TIMELMT_TYPE,			 // ��ʱ�������� ��������Ϸ
	CTRL_IS_DAILY_FAILED=15,	 // �Ƿ����ʧ��
	CTRL_IS_TEAMLOOP=16,		// �Ƿ���ӻ�����
	CTRL_TEAM_MEMBER=17,		// ������������
	CTRL_FINISH_TIME=18,		// �������ʱ������
	CTRL_REFRESH_AWARD=19,		// �����Ƿ����ˢ�½���
	CTRL_TASK_ENDTIME=20,		// �������ж�ÿ�������
	CTRL_TASK_PUBLISHTYPE = 21,   // ���񷢲�����
	CTRL_TASK_IS_FINAL_CHILD = 22, //�Ƿ�Ϊ��������������һ��
};

enum ETaskKind 
{
	KIND_SEEKITEM = 1,    //Ѱ��, 
	KIND_SENDMAIL = 2,    //����, 
	KIND_COLLECT = 3,     //�ռ��� 
	KIND_ZAYI = 4,        //����, 
	KIND_MAKEITEM = 5,    //����, 
	KIND_XIULIAN = 6,     //������ 
	KIND_KILLORGE = 7,    //ɱ��
	KIND_REVENGE = 8      //����, 
};

enum ETaskInviteRet
{
	ERROR_CANT_ACCEPT ,  // 0=�������� 
	ERROR_GOT,			 // 1=�Ѿ������� 
	ERROR_COMPLETED,	 // 2=�Ѿ����
	ERROR_OFFLINE,		 // 3=�Է�������
	// ERROR_DES_BAGFULL,	 // 4=�Է������� �����������Ҫ����������Ʒ

};


class region
{
public:
	unsigned short mMapID;
	unsigned short mX;
	unsigned short mY;

	region(unsigned short map_id, unsigned short X, unsigned short Y):mMapID(map_id),mX(X),mY(Y){}
	region():mMapID(0),mX(0),mY(0){}
};



// ********************************************************************** //
// COgreTaskList
// ********************************************************************** //

class COgreTaskList
{
public:
	COgreTaskList( ) : mOgreID( 0 ), mNumber( 0 )
	{
		memset( mTaskID,0,sizeof(mTaskID) );
	}

public:
	unsigned int	mOgreID;
	unsigned short	mNumber;
	unsigned short	mTaskID[ 64 ];
};

// ********************************************************************** //
// CTaskDropTable
// ********************************************************************** //

class CTaskDropTable
{
public:
	unsigned int		mOgreID;				// ����ID
	unsigned short		mNumber;
	unsigned short		mTaskID[ 64 ];
};

class CTaskCompleteOgreItem
{
public:
	int		mID;
	int		mNum;
public:
	CTaskCompleteOgreItem( int vID = 0, int vNum = 0 )
		: mID(vID), mNum(vNum)
	{
	}
};

//���ڴ洢�Ѿ��򿪹��Ŀ�ѡ������ģ��ID������
class CAwardOptions
{
public:
	unsigned int mItemID;
	unsigned short mNum;
};

//��¼�Զ��ӵ�������б�
class CTaskAutoGet
{
public:
	unsigned short	mTaskID;
	unsigned short	mMapID;
	unsigned short	mX;
	unsigned short	mY;
	unsigned short	mH;
	unsigned short	mW;
public:
	bool CheckInRegion(region vRegion)
	{
		return (vRegion.mMapID == mMapID) && (vRegion.mX >= mX) && vRegion.mX <= (mX + mW) && vRegion.mY >= mY &&  vRegion.mY <= (mY + mH);
	}
};



class CNpcTaskList
{
public:
	CNpcTaskList( ) : mExtendNumber( 0 ), mCallbackNumber( 0 )
	{
	}

	void clear()
	{
		mNpcID  = 0;
		mExtendNumber = 0;
		mCallbackNumber = 0;
	}

public:
	int   	mNpcID;
	unsigned short	mExtendNumber;
	unsigned short	mExtendTaskID[ MAX_NPC_TASK_NUM ];
	//short			mExtendTaskStatus[ 64 ];
	unsigned short	mCallbackNumber;
	unsigned short	mCallbackTaskID[ MAX_NPC_TASK_NUM ];
	//short			mCallbackTaskStatus[ 64 ];
	unsigned short  mLastTip;
};

// *** �¼��滮��
// �¼�ID ����32bits
// ��һλ����
// NO.2 bit �Ƿ�ȫ��Ψһ�¼�(����ͬʱ�����ϣ����߸ɴ�ȫ��������ֻ����1�Σ����羫���ȣ������¼���¼��������� ������ID)MASK=0x8000
#define EVENT_MASK_GLOBAL       0x40000000
// NO.3 bit �Ƿ���Ҫ��¼���¼� MASK=0x4000
#define EVENT_MASK_RECORD       0x20000000
// NO.4 bit �Ƿ���ӵ��¼�(Ϊ�˼ӿ��ٶȣ�������ӻ��ƣ�
//          Ŀǰֻ��ɱ�ֺ��Ѽ��б����ƣ������ӳ������е��¼���Ӧ�����������ʱ�򣬲Ż����update�ӿ�) MASK=0x2000
#define EVENT_MASK_WATCH        0x10000000
// NO.5 bit ���¼�������ʱ�� ǿ��֪ͨ�ͻ���ˢ������
#define EVENT_MASK_NOTIFY       0x08000000
// NO.6 bit ���¼���Param�ǲ���0����0�Ļ���λ��1
#define EVENT_MASK_PARAM0       0x04000000
// NO.7 bit ���¼�Ҫ�����������¼��������
#define EVENT_MASK_REGINTASK    0x02000000
// NO.8 bit û�õ� ���ô���
#define EVENT_MASK_NOUSE		0x01000000

// ��16bits ���������¼�ID
#define EVENT_MASK_ID           0x0000FFFF

enum EEventForTask  // 32λ�������λ��ʾ�Ƿ���Ҫ��¼���¼�
{
	// ����Ҫ��¼���¼�
	// ��Ҫ���ӵ��¼�
	EVENT_ITEMCHANGE	= 0x18000001,             // ��Ʒ�仯 Param����Ʒģ��ID  ��ǿ��ˢ�¿ͻ�������
	EVENT_OGREDIE		= 0x18000002,             // �������� Param�ǹ���ID  �����ӡ���ǿ��ˢ�¿ͻ�������
	// ����Ҫ���ӵ��¼�
	EVENT_CHANGEMONEY	= 0x04000001,             // ��Ǯ�仯 Param��0
	EVENT_LEVELCHANGE	= 0x04000002,             // �ȼ��仯 Param��0
	EVENT_MOVEREGION	= 0x04000003,             // ����ƶ� Param��0 ����
	EVENT_PLAYERDIE		= 0x04000004,             // ������� Param��  ����
	EVENT_NPCDIE		= 0x04000005,             // NPC����  ����
	EVENT_METIERCHANGE	= 0x04000006,			    // ���ְҵ�ı�  Param��0
	EVENT_TASKCHANGE	= 0x04000007,			    // �����������ı� Param����Ʒ����ID
	EVENT_KILLLEVELOGRE	= 0x04000008,				// ���ȼ�ɱ��
	EVENT_BUFFCHANGED	= 0x04000009,				// ���BUFF�ѱ仯

	// ��Ҫ��¼���¼�(��������������񶼼�¼  ����!!) (������lua��check��clear) (�����Ǳ�֤���������������������)
	EVENT_USEITEM			  = 0x20000001,		// ���ʹ�õ��� Param����ƷID
	EVENT_SENDNPCCOMPLETE	  = 0x20000002,		// ��һ���NPC����ָ��λ�� Param��NPCģ��ID
	EVENT_TALKCOMPLETE		  = 0x20000003,		// �Ի����  Param��NPCģ��ID

	// ȫ��Ψһ�¼�(֧�ֿ��ٷ��ʣ����32�� Ҳ��Ҫ��¼�������������������ż�¼) (clear��ʱ��Ҫ���)
	EVENT_UPEQT				  = 0x64000001,		// ����ĳ����Ʒ���ھ���ʦ��ʹ����һ������ʯ��
	EVENT_PRODUCE_WEAPON      = 0x64000002,		// ������������ʹ������������ȸ��������������һ��������
	EVENT_PRODUCE_PREVENT	  = 0x64000003,		// �����˷��ߣ�ʹ��������߰׻���������������һ�����ߣ�
	EVENT_PRODUCE_DRUG		  = 0x64000004,		// ������ҩƷ��ʹ�÷��𻨣��ɲΣ�����Ҷ����֥��ѩ������������һ��ҩƷ��
	EVENT_STOVE				  = 0x64000005,		// ����ĳ����Ʒ������ĳ��װ����������¯�У������������¯�Ļ���ֵ�����ڿ��ܽ�Ԫ��ֵ��
	EVENT_JEWEL				  = 0x64000006,		// ��Ƕ��ʯ����ͨ���«�����У�����ʯ��Ƕ��װ���ϣ�
	EVENT_CHARSTONE			  = 0x64000007,		// ��Ƕ����ʯ(��ͨ���«�����У���������ʯ��Ƕ��װ����)
	EVENT_HOLE				  = 0x64000008,		// Ϊĳ����Ʒ��ף���ͨ���«�����У��û���Ϊĳ����Ʒ��ף�
	EVENT_SKILL				  = 0x64000009,		// ѧϰ����
	EVENT_ENDLOOP			  = 0x6400000A,		// ���һ�ֻ�����

	// ����ʱ ��Ҫ�����������¼�����������¼�
	EVENT_COMPLETESTORAGETASK = 0x02000001,		// �����һ�ο�����
	EVENT_KILLFOREIGNER		  = 0x02000002,		// ɱ�������
	EVENT_COMPLETE_LOOP		  = 0x02000003,		// ��ɻ�����
	EVENT_COMPLETE_QUESTION	  = 0x02000004,		// ���ÿ�մ���

	// ��ʱ�õ��¼����� ���ڴ�Lua����������Ϣ��C++  ��ͨ���߼� ����������߼� ����ע���¼��ĵط�����
	EVENT_PROTECT_FLAG		  = 0x01000001,		// �������� param1��NPCģ��ID
};

#define  MAX_SAVE_EVENT 20

// ����·������
#define MAX_WAY_POINTS 100

// ������ϵĿ������б�����
#define MAX_STORAGETASK_LIST_NUM 10
#define STORAGE_SIZE			 1000

// ����������Ŀ�����
#define MAX_ACCEPT_STORAGETASKS 10

enum ETaskRefreshType 
{
	REFRESH_DAY  = 1, //-- ÿ��ˢ
	REFRESH_BACK = 2, //-- ��������ˢ
	REFRESH_RMB  = 3, //--��RMB����ˢ
};

#define _MAX_INT 1000000000

#define MAX_LOOP_SUB_TASKS		    100		// ÿ���������������������

enum ETaskConditions
{ 
	CONDITION_OGREDIE			= 1, // ��������
	CONDITION_ITEM				= 2, // ��Ʒ�仯���������ӻ���٣�
	// �������������������ʵ�ʵĲ�ͬ ����˵�������ģ��ID��Ϊ��־�� ���������������� ʵ��������3�����������ǵ�һ��
	// ������Ʋ�̫�� ������ �����������
	CONDITION_LEVELOGRE			= -1,	// �ȼ�ɱ��
	CONDITION_KILL_FOREIGNER	= -2,	// ɱ�������
	CONDITION_COMPLETE_STORAGE	= -3,	// �������
	CONDITION_COMPLETE_LOOP		= -4,	// ��ɻ�����
	CONDITION_COMPLETE_QUESTION	= -5,	// ���ÿ�մ���
};

// ��NPC�Ի�״̬
enum ENpcTalkState
{
	NONE_TALKED		= 1,
};

// ������ID����  ���������  (��ֵ���ܸģ�������ҵ��ˣ�)
enum enTaskGroups
{
	TASKGROUP_START					=   0x00010000,		// ԭʼ���������ID��ʼ
	TASKGROUP_FAMILY_HONNER			=	0x00010001,		// ������ҫ����
	TASKGROUP_FAMILY_KILL			=	0x00010002,		// �����������
	TASKGROUP_FAMILY_SEND			=	0x00010003,		// ���廤������
	TASKGROUP_FAMILY_CHALANGE		=	0x00010004,		// ������ս����
	TASKGROUP_CORPS_IN				=	0x00020001,		// �����ر�����
	TASKGROUP_CORPS_OUT				=	0x00020002,		// �����ű�����
	TASKGROUP_CORPS_CHALANGE		=	0x00020003,		// ������ս����
	TASKGROUP_MINEMAP				=	0x00040001,		// �ر�ͼ����
	TASKGROUP_ACTIVITY				=	0x00080001,		// �������
	TASKGROUP_SAVEFLAG1				=	0x00100001,		// ����1
	TASKGROUP_SAVEFLAG2				=	0x00100002,		// ����2
	TASKGROUP_SAVEFLAG3				=	0x00100003,		// ����3
	TASKGROUP_SAVEFLAG4				=	0x00100004,		// ����4
	TASKGROUP_COUNTRY1				=	0x00200001,		// ��������
	TASKGROUP_COUNTRY2				=	0x00200002,		// ��������
	TASKGROUP_COUNTRY3				=	0x00200003,		// �񲿽���
	TASKGROUP_COUNTRY4				=	0x00200004,		// �̲�����
	TASKGROUP_COUNTRY5				=	0x00200005,		// ��������
	TASKGROUP_COUNTRY6				=	0x00200006,		// ��������
	TASKGROUP_COUNTRY7				=	0x00200007,		// ë���Լ�
	TASKGROUP_COUNTRY_ALL			=	0x00200008,		// ���н�������

	TASKGROUP_CAMP_TF1				=	0x00400001,		// ��Ӫ�ַ�����1
	TASKGROUP_CAMP_TF2				=	0x00400002,		// ��Ӫ�ַ�����2
	TASKGROUP_CAMP_RB				=	0x00400003,		// ��Ӫ�ű�����
	TASKGROUP_CAMP_SB				=	0x00400004,		// ��Ӫ�ر�����
	TASKGROUP_CAMP_SQ1				=	0x00400005,		// ��Ӫ����1
	TASKGROUP_CAMP_SQ2				=	0x00400006,		// ��Ӫ����2
	TASKGROUP_CAMP_SQ3				=	0x00400007,		// ��Ӫ����3
	TASKGROUP_CAMP_SQ4				=	0x00400008,		// ��Ӫ����4

	// �¼ӵĻ���� ��ʱ��ʱ������ �Ժ󳹵��������
	TASKGROUP_XUNXIAN1 = 524290, // �Ѱ��1
	TASKGROUP_XUNXIAN2 = 524291, // �Ѱ��2
	TASKGROUP_XUNXIAN3 = 524292, // �Ѱ��3
	TASKGROUP_XUNXIAN4 = 524293, // �Ѱ��4
	TASKGROUP_SISHEN1	=	524294	,
	TASKGROUP_SISHEN2	=	524295	,
	TASKGROUP_SISHEN3	=	524296	,
	TASKGROUP_SISHEN4	=	524297	,
	TASKGROUP_SISHEN5	=	524298	,
	TASKGROUP_SISHEN6	=	524299	,
	TASKGROUP_SISHEN7	=	524300	,
	TASKGROUP_SISHEN8	=	524301	,

	TASKGROUP_SPRING1	=	524302	,
	TASKGROUP_SPRING2	=	524303	,
	TASKGROUP_SPRING3	=	524304	,
	TASKGROUP_SPRING4	=	524305	,
	TASKGROUP_SPRING5	=	524306	,
	TASKGROUP_SPRING6	=	524307	,
	TASKGROUP_SPRING7	=	524308	,
	TASKGROUP_SPRING8	=	524309	,
	TASKGROUP_SPRING9	=	524310	,
	TASKGROUP_SPRING10	=	524311	,
	TASKGROUP_SPRING11	=	524312	,
	TASKGROUP_SPRING12	=	524313	,

	TASKGROUP_KILLZHUREN1	=	524314	,  // ɱ������1
	TASKGROUP_KILLZHUREN2	=	524315	,  // ɱ������2
	TASKGROUP_KILLZHUREN3	=	524316	,  // ɱ������3
	TASKGROUP_KILLZHUREN4	=	524317	,  // ɱ������4

	TASKGROUP_KILLWEIBIN1	=	524318	,  // ɱ������1
	TASKGROUP_KILLWEIBIN2	=	524319	,  // ɱ������2
	TASKGROUP_KILLWEIBIN3	=	524320	,  // ɱ������3
	TASKGROUP_KILLWEIBIN4	=	524321	,  // ɱ������4

	TASKGROUP_CITAN1			=	524322	,  // ��̽����1
	TASKGROUP_CITAN2		=	524323	,  // ��̽����2
	TASKGROUP_CITAN3			=	524324	,  // ��̽����3
	TASKGROUP_CITAN4			=	524325	,  // ��̽����4

	TASKGROUP_LIULI1			= 524326, // ����յ����1
	TASKGROUP_LIULI2			= 524327, // ����յ����2
	TASKGROUP_LIULI3			= 524328, // ����յ����3
	TASKGROUP_LIULI4			= 524329, // ����յ����4
	TASKGROUP_LIULI5			= 524330, // ����յ����5
	TASKGROUP_LIULI6			= 524331, // ����յ����6
	TASKGROUP_LIULI7			= 524332, // ����յ����7
	TASKGROUP_LIULI8			= 524333, // ����յ����8

	TASKGROUP_MARUI				= 530000,	// 53W�Ժ�� �������ɷ���
	TASKGROUP_YUEGONG1			= 530014,   // �¹�ʹ��1
	TASKGROUP_YUEGONG2			= 530015,   // �¹�ʹ��2
	TASKGROUP_YUEGONG3			= 530016,   // �¹�ʹ��3
	TASKGROUP_YUEGONG4			= 530017,   // �¹�ʹ��4
	
	TASKGROUP_NEW_LIULZ1		=  530019, //  ������յ1
	TASKGROUP_NEW_LIULZ2		=  530020, //  ������յ2
	TASKGROUP_NEW_LIULZ3		=  530021, //  ������յ3
	TASKGROUP_NEW_LIULZ4		=  530022, //  ������յ4
	TASKGROUP_NEW_LIULZ5		=  530023, //  ������յ5
	TASKGROUP_NEW_LIULZ6		=  530024, //  ������յ6

	TASKGROUP_NEWYEAR_SZ1		= 530026, // ����ʹ��1
	TASKGROUP_NEWYEAR_SZ2		= 530027, // ����ʹ��2
	TASKGROUP_NEWYEAR_SZ3		= 530028, // ����ʹ��3
	TASKGROUP_NEWYEAR_SZ4		= 530029, // ����ʹ��4

	TASKGROUP_QMJ1				= 530043, // ������1
	TASKGROUP_QMJ2				= 530044, // ������2
	TASKGROUP_QMJ3				= 530045, // ������3
	TASKDAILY_MOBAI				= 530049, // ÿ��Ĥ��

	TASKGROUP_BALANCE1			= 530054,  //ƽ��1
	TASKGROUP_BALANCE2			= 530055,  //ƽ��2
	TASKGROUP_BALANCE3			= 530056,  //ƽ��3
	TASKGROUP_BALANCE4			= 530057,  //ƽ��4


	TASKGROUP_HAVOC_HEAVEN1		= 530063,  // 72�����칬����1
	TASKGROUP_HAVOC_HEAVEN2		= 530065,  // 72�����칬����1
};

// �������������
#define  MAX_TASKGROUP_NUM	200

// ͨ��������� ������
enum enCommonCheckCode
{
	CHECKTYPE_ISFAMILYMEMBER	=	1	,		// �Ƿ�����Ա
	CHECKTYPE_ISFAMILYHEAD		=	2	,		// �Ƿ�����峤
	CHECKTYPE_ISCORPSMEMBER		=	3	,		// �Ƿ���ų�Ա
	CHECKTYPE_HASTITLE			=	4	,		// �Ƿ���ĳ�ƺ�   ����1�ǳƺ�ID
	CHECKTYPE_BUFF				=	5	,		// ��������Ƿ���ĳ��BUFF
	CHECKTYPE_COUNTRY			=	6	,		// ������
	CHECKTYPE_PUBLISH			=	7	,		// ��鷢�� �ҿɽӴ���0
	CHECKTYPE_FAMILY_NPC		=	8	,		// ������ڼ���ռ����NPC
	CHECKTYPE_CORPS_NPC			=	9	,		// ������ھ���ռ����NPC
	CHECKTYPE_ACTIVITY			=	10	,		// ���ָ�������
	CHECKTYPE_REG_DATE			=	11	,		// ���ע����������...
	CHECKTYPE_QUES_NUM			=	12	,		// ���������
	CHECKTYPE_HYDRANGEASTATUS	=	13	,		// �������״̬
	CHECKTYPE_IN_CAMP			=	14	,		// ����������Ӫ
	CHECKTYPE_ONLINESECS		=	15	,		// ����ۼ�����ʱ�� ��
	CHECKTYPE_WEEKNATION		=	16	,		// ��������
	CHECKTYPE_IN_MY_SELF		=	17	,		// ���ֻ���ڱ���Ӫ������
	CHECKTYPE_IS_NATIONKILL		=	18	,		// ����Ƿ��ڹ�̽�ڼ�
	CHECKTYPE_IS_LUANWU			=	19	,		// ����Ƿ��������ڼ�
	CHECKTYPE_IS_MASTER			=	20	,		// ����Ƿ�ʦ��
	CHECKTYPE_IS_TEAMHEAD		=	21	,		// ����Ƿ�ӳ�
	CHECKTYPE_TEAM_MEMBER		=	22	,		// ����������
	CHECKTYPE_ISVIP_PLAYER		= 	23	,		// ����Ƿ���VIP
	CHECKTYPE_ISSWORNED_PLAYER	= 	24	,		// ����Ƿ��Ѿ����
};

// ͨ�ý�����
enum enCommonAwardCode
{
	AWARDTYPE_TELANT				=	1	,		// ������Ϊ��(����1������)
	AWARDTYPE_FAMILY_HONOR			=	2	,		// �������˼�����ҫֵ
	AWARDTYPE_FAMILY_MONEY			=	3	,		// ���������Ǯ
	AWARDTYPE_FAMILY_CONTRIBUTE		=	4	,		// �������˼��幱�׶�
	AWARDTYPE_CORPS_GLORY			=	5	,		// �������˾�����ҫֵ
	AWARDTYPE_CORPS_MONEY			=	6	,		// �������Ž�Ǯ
	AWARDTYPE_CORPS_CONTRIBUTE		=	7	,		// �������˾��Ź��׶�
	AWARDTYPE_TITLE					=	8	,		// �����ƺ�
	AWARDTYPE_HONOR					=	9	,		// ������ѫ
	AWARDTYPE_BINDYINGYUANBAO		=	10	,		// �����󶨵���Ԫ��
	AWARDTYPE_COUNTRYBUILD			=	11	,		// �������ҽ����
	AWARDTYPE_UPWIS					=	12	,		// �ϱ��Ż�
	AWARDTYPE_WISEXP				=	13	,		// �����Ż�����
	AWARDTYPE_CLEARHYDRANGEASTATUS	=	14	,		// �������״̬
	AWARDTYPE_COMBAT_FAME			=	15	,		// ������������
	AWARDTYPE_REPE_FAME				=	16	,		// ������������
	AWARDTYPE_COMMON_FAME			=	17	,		// ������������
	AWARDTYPE_CORPS_COLLECTACTIVE	=	18	,		// �������ţ��ɼ�����Ծ��

};

// �ͻ�������repeated�ֶ�����
enum enClientLimit
{
	// �ͻ���һ������ ����������� ����
	CLIENTREQUESTMAX_GETEVERYDAYTASK	=	20,
	// �ͻ���һ������ tips ����
	CLIENTREQUESTMAX_GETTIPS			=	300,
};

// ����NPC���ͼ��ȴ�ʱ�� ���룩
#define SEND_NPC_REDIRECT_WAIT_TIME	3

// Ϊ������ �������⴦���� ������������ö��
enum enTaskExFlags
{
	EXFLAG_LEVELKILLOGRE				=	0x0001,	// ���ȼ�ɱ��
	EXFLAG_KILL_FOREIGNER				=	0x0002,	// ɱ�����
	EXFLAG_COMPLETE_STORAGE				=	0x0004, // �������
	EXFLAG_PROTECT_FLAG_TASK			=	0x0008, // ��������
	EXFLAG_COMPLETE_LOOP				=	0x0010, // ��ɻ�����
	EXFLAG_COMPLETE_QUESTION			=	0x0020, // ��ɴ�������
};

// ����ģ��ID�������Ǹ�����Ҳ����˵���λ��Զ������Ϊ1�������ƶ�һ��������ڲ�ID ����ʵ���������Ҫ�����Ĺ���
enum enSpecialID
{
	SPECIALID_COMPLETESTORAGE			=	0x80000001,	// �����������
	SPECIALID_KILLFOREIGNER				=	0x80000002,	// ɱ�������
	SPECIALID_COMPLETELOOPTASK			=	0x80000003,	// ��ɻ�����
	SPECIALID_COMPLETEQUESTION			=	0x80000004,	// ���ÿ�մ���
};

// ���ڿͻ�����ʾ�Ľ�������
enum enShowAwardType 
{
	SHOWAWARD_EXP = 1, //�������� (n��ʾ����ֵ)
	SHOWAWARD_MONEY = 2, //������Ǯ(n��ʾ��Ǯֵ)
	SHOWAWARD_ITEM = 3, //������Ʒ(id,n)
	SHOWAWARD_TASK = 4, //����һ������(id��ʾ����ID)
	SHOWAWARD_TRANS = 5, //�������ͣ�(id��ʾĿ���ͼID��x,y��ʾĿ������)
	SHOWAWARD_TELANT=6, //������Ϊ��
	SHOWAWARD_HONOR=7, // ������ѫ
	SHOWAWARD_FAMILY_GLORY		=8,     // �������˼�����ҫֵ
	SHOWAWARD_FAMILY_MONEY		=9,    // ���������Ǯ
	SHOWAWARD_FAMILY_CONTRIBUTE	=10,   // �������˼��幱�׶�
	SHOWAWARD_CORPS_GLORY		=11,  //  �������˾�����ҫֵ
	SHOWAWARD_CORPS_MONEY		=12,   // �������Ž�Ǯ
	SHOWAWARD_CORPS_CONTRIBUTE	=13,  //  �������˾��Ź��׶�
	SHOWAWARD_BUILD_RENSHI		=14,  //  ���������
	SHOWAWARD_BUILD_HUKOU		=15,  //  ���������
	SHOWAWARD_BUILD_LIBIN		=16,  //  �񲿽����
	SHOWAWARD_BUILD_GUOFANG		=17,  //  ���������
	SHOWAWARD_BUILD_FAYUAN		=18,  //  �̲������
	SHOWAWARD_BUILD_GONGCHENG	=19,  //  ���������
	SHOWAWARD_WIS_ARTS			=20,  //  �����Ż����飺�Ĳ�
	SHOWAWARD_WIS_TACTICS		=21,  //  �����Ż����飺����
	SHOWAWARD_WIS_POWER			=22,  //  �����Ż����飺����
	SHOWAWARD_WIS_WISDOM		=23,  //  �����Ż����飺ı��
	SHOWAWARD_WIS_POLITICS		=24,  //  �����Ż����飺����
	SHOWAWARD_WIS_EDUCATE		=25,  //  �����Ż����飺����
	SHOWAWARD_BIND_YUANBAO		=26,  //  ������Ԫ��
	SHOWAWARD_BUFF				=27,  //  ����BUFF
	SHOWAWARD_COMBAT_FAME		=28,  //  ��������������
	SHOWAWARD_REPE_FAME			=29,  //  ��������������
	SHOWAWARD_COMMON_FAME		=30,  //  ��������������
};

// ��ʱ����ʱ����
enum enTimeOutType
{
	TIMEOUT_FAIL		=	0,	// ʧ��
	TIMEOUT_COMPLETE	=	1,	// �������
};

// ��ʱ��ʽ
enum enTimeLmtType
{
	TIMETYPE_GAME		=	0,	// ��Ϸʱ��
	TIMETYPE_PHYSICAL,			// ����ʱ��
};

// NPC�����������������
#define NPC_MONITOR_SIZE	10

// ������ ��Ӧ��������������ǰ��16λ
enum enActiveCode
{
	NPC_DIE			=	0,	// NPC����
	MAX_ACTION_TYPES,		// ����
};

// ���������� ���ɣ���16λ����������  ��16λ����������
enum enTaskActionType
{
	NPC_DIE_FAIL	=	0x00000001,	// NPC��������ʧ��
};

// ͨ�û���� ���ڻ�ø�����ֵ
enum enCommonGetCode
{
	GET_WIZARD_POLITICS = 1,	// ��ҲŻ�ֵ-����
	GET_WIZARD_WISDOM	= 2,	// ��ҲŻ�ֵ-ı��
	GET_WIZARD_ARTS		= 3,	// ��ҲŻ�ֵ-�Ĳ�
	GET_WIZARD_EDUCATE	= 4,	// ��ҲŻ�ֵ-����
	GET_WIZARD_TACTICS	= 5,	// ��ҲŻ�ֵ-����
	GET_WIZARD_POWER	= 6,	// ��ҲŻ�ֵ-����
	// ����6�����ܶ���LUA���ǰ���˳���õ� ���excel���йص�
	GET_PLAYER_CAMP		= 7,    // ��ҵ���Ӫ
};

// ����������
enum enTeleType
{
	TELEPORT_COMMON, // ��ͨ
	TELEPORT_INFB,   // ���븱��
	TELEPORT_INMENPAI,   // ��������
	TELEPORT_OUTMENPAI,  // ��������
};

// ���֧�ַ���������������
#define MAX_PUBLISH_TYPES	20

// ���񷢲�״̬
enum enTaskPublishState
{
	STATE_TODAY		= 1,	// ������Ч
	STATE_TOMORROW	= 2,	// ������Ч
};

// �ر�ͼ���� ÿ���������
#define CANGBAOTU_DAY_TOTAL 10

// �������������������
#define CHAIRMAN_TASK_NUM	10

// ��������״̬
enum enChairManTaskState
{
	CHAIRMAN_STATE_ENABLED	= 0,  // �ɽ�
	CHAIRMAN_STATE_GOT		= 1,  // �ѽ�
	CHAIRMAN_STATE_END		= 2,  // �����
};


// ���⽱������
enum EXTRA_DEFINE
{
	LOOP_TASK = 1,	// ������
	TRAGEDY_TASK = 2, // ��������
	CHAIRMAN_TASK = 3, // ��������
	TEAMLOOP_ENDLOOP = 4, // ��ӻ����� ���һ�ֽ���
	TEAMLOOP_TEAMEXTRA = 5, // ��ӻ����� ��Ӷ��⽱��
};

// ������������
enum emPublisType
{

	NOT_PUBLISH_TASK_TYPE		= 0, // ���Ƿ�����������
	CORPS_PUBLISH_TASK   		= 1, // ���ŷ���
	COUNTRY_PUBLISH_TASK  		= 2, // ���ҷ���
	FAMILY_PUBLISH_TASK  		= 3, // ���巢��
	CAMP_PUBLISH_TASK 			= 4, // ��Ӫ����
	UNION_PUBLISH_TASK			= 5, // ���˷���

	TOTLE_PUBLISH_TYPE			= 5, // ��������

	SINGLE_PUBLISH_TASK 		= 6, // ���˷���
};



// ���������������
enum emPublishLimits
{
	TODAY_MAX_PUBLISH_MUN		= 10,
	WEEK_MAX_PUBLISH_NUM		= 50,
};

// ��������״̬
enum emPublishState
{
	UNEXIST_TASK			= 0,
	UNPUBLISH_TASK			= 1,
	PUBLISHED_TASK			= 2,
	ACCEPTED_TASK			= 3,
	RECIEVE_TASK			= 4,
	FINISHED_TASK			= 5,
};

enum emPublishCheck
{
	CHECK_CORPS_LEVEL		= 1,
	CHECK_CORPS_MONEY		= 2,
	CHECK_CORPS_POSITION	= 3,
};


// ���˷�����Ϣ
enum emSinglePublish
{
	SINGLE_PUBLISH_TASK_LEVEL	= 70,    // ���˷�����Ҫ����͵ȼ�
	SINGLE_OBTAIN_PUBLISH_LEVEL = 70,	 // ���ܸ��˷�������͵ȼ�

	MAX_SINGLE_PUBLISH_BUFFER	= 500,	  // ÿ����ɫ�����б����󳤶�

};