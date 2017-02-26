#pragma once
#define MAX_FAMILYNAME_LENGTH		40			// �������Ƴ���(�ַ�����)
#define MAX_FAMILYNOTICE_LENGTH		300			// ���幫�泤��(�ַ�����)
#define	MAX_FAMILYMEMBER_NUM		30			// �����Ա��������
#define LEVEL_CREATFAMILY			40			// ����������Ҫ�ĵȼ�
#define LEVEL_FAMILYHEADER			40			// �峤�ĵȼ�
#define MAX_FAMILYMEMBERINFO_BUFFULENT     2048	// �����Ա��Ϣ������pb�ṹ������Ҫ��������鳤��
#define FAMILYTIMER_UPDATE_TIMELENGTH	30000	// ���м�����Ϣ����һ�ε�ʱ��   30��
#define FAMILY_FETCH_COUNT			10			// һ�δ����ݿ��ȡ�ļ�������  
#define	COST_CREATFAMILY			150000		// ����������Ҫ�Ľ�Ǯ  15��
#define LEVEL_JOINFAMILY			30			// ����������͵ȼ�
#define MAX_APPLYLIST_APPLIESNUM	30			// �����б�������������
#define MAX_CORPSINVITE_NUM	 		5			// ����������Ϣ������
#define FAMILY_DISBAND_TIMELENGTH	86400	 	// 86400 �����ɢʱ��
#define FAMILY_APPLYCORPS_TIMELENGTH 60			// 86400���������ŵ���ȴʱ��(���ڸ�Ϊ1����)
#define FAMILY_LEAVECORPS_TIMELENGTH 86400		// �뿪���ź��ٴμ������ȴʱ��	86400
#define MAX_UTF8_BYTES				3			// utf8�ĺ����ֽ���	 
#define FAMILYAPPLY_TIMELIMIT		60			// �������������ȴʱ��86400 3600*24 24Сʱ( ���ڸ�Ϊ1���� )
#define FAMILY_LEAVEFAMILY_TIMELENGTH  86400	// �뿪���߽�ɢ������ٴμ���������ȴʱ��	86400
#define FAMILY_LEVEL_LIMIT			5			// ����ȼ�����
#define FAMILY_MAP_ID				66			// ����ս��ͼID
#define SUBMIT_LIMIT				6			// ����ս������������

#define MAX_FAMILY_NUM				14000		// ���м���ĸ���,�����ǳ����ϼ���������4���������ϵļ�����Ϣֻ�е������Ա�����������ʱ�ŻὨ��

#define WELFARE_REFESH_TIMELENGTH	86400		// ˢ��npc������ʱ����86400
#define MAX_NPCWELFARE_MONEY		2000000		// npc������ȡ�Ľ�Ǯ������
#define MAX_NPCWELFARE_GLORY		2000		// npc������ȡ����ҫ������
#define FAMILYBOSS_MAP_ID			94			// ����boss�ĵ�ͼID	   
#define MAX_CONTRIBUTE				2000000		// ���˹��׶�����	   
#define MAX_FAMILYCORPS_MONEY		2000000	    // ������ŵĽ�Ǯ����  													
#define INVALID_FAMILYCORPSID	    -3			// ��Ч�ļ������ID
#define FAMILYCORPS_MAXGETNUM		50			// ��ȡ��������б�ʱÿ����෢�͵ļ����������
#define MAX_CONTRIBUTE				2000000		// ���˹��׶�����  
#define MAX_FAMILYCORPS_MONEY		2000000	    // ������ŵĽ�Ǯ����

#define MONEY_EXCHANGERATE	10000				// ������Ž�Ǯ�ͷ̰�����Ķһ�����

#define FAMILYTIMER_DISBAND_TIMELENGTH	600000	// �������ɢʱ���ʱ����10����

#define MAX_NPCNUMOFWELFARE		30				// ����npc������������


#define MAXGOODSINSHOP	50						// �̵������Ʒ���������
#define MAXLEAGUESHOPSNUM	20					// �������ӵ������̵������

#define MAXSHOPBYTELEN	1024					// �����̵�pb�ṹ����󳤶�
#define MAXESCAPEBUFFLENGTH 2048				// ת����������󳤶�
#define MAX_REPETIONTIMEINFO_NUM	7			// ����ʱ�����õ�������
#define MAX_MAILINFO_NUM	20					// �ʼ��������͵�������

enum EInviteList
{										
	INVITELIST_FULL		= 1,					// ��ҵ������б���
	INVITELIST_EXIST	= 2,					// ����������б��Ѿ��ڼ�����
};

enum EApplyList
{
	APPLYLIST_FULL		= 1,				   // �����б���
	APPLYLIST_EXIST		= 2,				   // ��ҵ��������
};	 

enum EFamilyPost
{	
	FAMILY_POST_HEADER			= 0,					// �峤		
	FAMILY_POST_PRESBYTER		= 1,					// ����
	FAMILY_POST_BUSINESSMAN		= 2,					// ��������	
	FAMILY_POST_MEMEBER			= 3,					// ������ͨ��Ա	
}; 

enum EReply
{
	FAMILY_REPLY_REFUSE = 0,	// �ܾ������������
	FAMILY_REPLY_AGREE	= 1,  	// ͬ�������������
	FAMILY_REPLY_IGNORE = 2,	// ���������������
	FAMILY_REPLY_DELETE = 3,	// ɾ�������������( �������� )
};

enum EMethodJoinCorps
{
	JOINCORPS_CREATBYFAMILYHEADER	= 0,		// �����˱������峤�����ľ���
	JOINCORPS_OTHERFAMILYCORPS		= 1,		// �������������彨���ľ���
};

enum EFamilyState
{
	STATE_NOBID		= 0,		// ��NPCδ����
	STATE_CHAZING	= 1,		// ��NPC�Ѿ���
	STATE_OWN		= 2,		// ��NPC��ռ��
};

enum EChaState
{
	STATE_IDLE		= 0,		// ��ս������
	STATE_WAITING	= 1,		// ��ս�ȴ���
	STATE_BUSY		= 2,		// ��սս����
};

enum EBattleType
{
	TYPE_BATTLE_NPC		= 0,
	TYPE_BATTLE_PLAYER		= 1,
};

enum EFamilyStatus
{
	FAMILY_STATUS_FAMILYEXPCARD	= ( 1 << 0 ),		// �������Ƶ���ȡ״̬
	FAMILY_STATUS_BOSSCHALLENGE	= ( 1 << 1 ),		// ��ս����boss��״̬	
};

enum EProChangedReason
{
	REASON_WAR				= 0,					// ��Ϊ��������ս
	REASON_TASK				= 1,					// ��Ϊ����
	REASON_NPCWELFARE		= 2,					// ��ȡռ��npc�ĸ���
	REASON_CONTRIBUTE		= 3,					// ��Ϊ���˹���	
	REASON_MEMBEREXP		= 4,					// ��Ϊ��Ա�ľ���ֵ
	REASON_MEMBERAP			= 5,					// ��Ϊ��Ա�Ĺ�ѫֵ
	REASON_ACTIVIYCONSUME	= 6,					// ��Ϊ�����
	REASON_LEVELUP			= 7,					// ��Ϊ����
	REASON_HEADERTAKE		= 8,					// ��Ϊ��Ǯ
	REASON_CHALLENGEWAR		= 9,					// ��Ϊ��ս��
	REASON_WARWIN			= 10,					// ��Ϊ��������ʤ
	REASON_CHALLENGEWARWIND	= 11,					// ��Ϊ��ս����ȡ
	REASON_MAKEREDPAPER		= 12,					// ��Ϊ������
	REASON_STARTREPETION	= 13,					// ��Ϊ��������
	REASON_USEMONEYITEM		= 14,					// ��Ϊʹ�ý𶧵���
	REASON_WARBID			= 15,					// ��Ӫս���ۿ�Ǯ
	REASON_ONLINETIME		= 16,					// ����ʱ���ۻ�
	REASON_LOWSTABILITY		= 17,					// �����ȹ���
	REASON_REDUCEONTIME		= 18,					// ��ʱ˥��
	REASON_USECORPCRYSTAL	= 19,					// �Ͻ�����boss����
	REASON_USECORPBOSSSTONE	= 20,					// ������
	REASON_SUMMONCORPBOSS = 21,					//�ٻ�����boss����
};


enum EmRight
{
	EM_CREATE_OFFICER			= 	0x80000000,		// ����, �޸�, ɾ��ְλ��Ȩ��
	EM_GRANT_RIGHTS				= 	0x40000000, 	// ������޸Ĺ�ְ��Ȩ����Ȩ��
	EM_INVITE_MEMBER 			= 	0x00000001,		// �����Ա��Ȩ��
	EM_APPROVE_APPLY 			= 	0x00000002,		// ������������Ȩ��
	EM_FIRE_MEMBER 				= 	0x00000004, 	// ������Ա��Ȩ��
	EM_GRANT_SETOFFICER			=  	0x00000008,		// �����¼���ְ��Ȩ��
	EM_LIST_APPLY 				= 	0x00000010,		// ���������Ȩ��
	EM_CHANGE_BULLETIN 			= 	0x00000020,		// �޸Ĺ����Ȩ��
	EM_ACTVITY_REDSTONE			= 	0x00000040,		// ��ȡ�����ڵ���Ȩ��
	EM_TASK_CONVOY				=	0x00000080,		// ���廤���������ȡ
	EM_MONEY_REIN				=	0x00000100,		// ��Ǯ��֧��
	EM_WAR_RID					=	0x00000200,		// ����
	EM_WAR_HALL					=	0x00000400,		// ��������
	EM_WAR_CHALLENGE			=	0x00000800,		// ��ս�ͽ�����ս
	EM_WAR_SETFIGHTER			=	0x00001000,		// ���Ų�ս��Ա
	EM_WELFARE_OBTAIN			=	0x00002000,		// ��ȡռ��npc����
	EM_WARNPC_GIVEUP			=	0x00004000,		// ����ռ��npc
	EM_RIGHT_DISBAND			=	0x00008000,		// ��ɢ������߾��ŵ�Ȩ��
	EM_RIGHT_CANCELDISBAND		=	0x00010000,		// ��ɢ������߾��ŵ�Ȩ��
	EM_RIGHT_CHALLENGEROOM		=	0x00020000,		// ��ս�����������Ȩ��
	EM_RIGHT_BUYFAMILYCORPSITEM	=	0x00040000,		// ������������Ʒ��Ȩ��
	EM_RIGHT_TASK				=	0x00080000,		// ��������
	EM_RIGHT_STARTFAMILYBOSS	=	0x00100000,		// �������帱����Ȩ��
	EM_RIGHT_STARTCORPSBOSS		=	0x00200000,		// ��������boss������Ȩ��
};


enum EHomeType
{
	HOME_MAIN				= 0,		// ����
	HOME_WUFANG				= 1,		// �䷻
	HOME_GONGFANG			= 2,		// ����
	HOME_SHUFANG			= 3,		// �鷻
	HOME_NUM				= 4,
};

#define MAX_ORNAMENT_NUM	10
#define MAX_VEGETABLE_NUM	100

enum EOrganLogType
{
	ORGANLOGTYPE_CORPS	= 0,	// ������־
	ORGANLOGTYPE_FAMILY = 1,	// ������־
};

#define  MAX_STABILITY_TIME_NUM 20	// ������ÿ���ȼ�������ʱ�����

#define  MAX_STABILITY_LEVEL_NUM 50	// �����ȵĵȼ�����
#define  MAX_FAMILYTASK_NUM 200	// ����������������
#define  FAMILY_INITIAL_STABILITY 200 

#define  MAX_STABILITY_REDSTONE_NUM 20 // ÿһ�ȼ������ȶ�Ӧ�ڵ������ֶ���