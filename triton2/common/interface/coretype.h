#pragma once

#ifdef LINUX
#include "object.h"
#endif

#include "base_define.h"
#include <time.h>
#include "errcode.h"
#include <string.h>	 

#define  MONEY_LIMIT		900000000	// �����������
#define  ITEM_BUYBACK_MAX	20			// ��һع�������������
#define	 BOX_LIMIT			320			// ��������( �ɣ�180 )
#define  FUNC_LIMIT			1024		// ����Ч��������
#define  BAGGAGE_BASE		30			// ������ʼ����
#define	 ITEM_BUFFER_MAX	10240		// �����ַ�����������
#define  THROWRANGE			1
#define	 PICKRANGE			2			// ʰȡ��Χ
#define  MAXPROLEVEL		10			// ��������ȼ�
#define	 ITEMUPLIMIT		10			// װ����������ȼ�
#define	 DAMAGELIMIT		128			// �˺��б�����
#define  TEAMNUM			6			// ������������
#define  TEAM_VALID_DISTANCE 15			// ��Ա֮����Ч����
#define  JEWELNUM			5			// ��ʯ����
#define	 PROPERTYNUM		8			// ��������
#define  YUANNUM			8			// Ԫ��װ������
#define  REFRESHTIME		10000		// �ָ�ʱ��
#define  CDGROUP			50			// ����CD��
#define	 PDEAL_LIMIT		64			// ����Ч��������
#define	 MAXLEVELDIFF		99			// �˺͹ֵ����ȼ���
#define  MAX_KITBAG_NUM     6	    	// �ֿⱳ�����ӵ��ܺ�
#define  MAX_BAGGAGEKITBAG_NUM 3		// �����������ӵ��ܺ�
#define  EQUIP_LIMIT		21			// װ������
#define	 MAX_STALL_INDEX	24			// ̯λ����������
#define  PLAYERNUM			8		    // ÿ���ʺŴ����Ľ�ɫ�������
#define  SUITIDNUM			150			// ��װ�������
#define  SUITPOSNUM			14			// ��װλ������
#define  OGREINDEX			200000		// ������������
#define	 KEYLEN				16			// ��������Կ����
#define	 MIN_HONOR_LEVEL	30			// ��ù�ѫ��͵ȼ�
#define  HONOR_REFRESHTIME	1800		// ��ѫ��õ�ʱ��
#define  MAX_DIPLOID_WAYS	5			// ��˫����չ�������ȡ��ʽ����
#define  PILELIMIT			10			// �ܻ����Ʒ��������
#define  UPGVALUENUM		3			// ������������
#define  ITEMRESLIMIT		6			// װ��������������
#define  COMPOSENUM			5			// ������Ʒ�ϳ�����
#define	 STATENUM			10			// ����״̬����
#define  INVITEDLISTNUM		5			// ����յ�������������
#define  MAXPLAYERNUM		100			// ��Ҫ��¼��־������������
#define  LOGNAMELENGTH		40			// ��־���Ƴ���
#define  SUBMITTIME			30			// ����NPC����ʱ��(����)
#define  MAXFIGHTTIME		60			// ����NPCս���ʱ��(����)
#define	 NOTIFYTIME			1			// ֪ͨ�������(����)

#define  MAXKITBAGINDEXNUM	48			// �����ĸ�������


#define  AUTO_PHYSICS_NUM	3			// �Զ��һ�ҩƷ����

#define  MAXSERVERNUM		6			// �������������������

// GM��ʶ
#define GM_STATE	0x10000000

#define GM_KICK_MAX		100
#define MAX_DUNGEONSERVER_NUM 6			// ȫ��ս��������
#define DEFAULT_REPETION_LINE_ID	( 99 )
#define IS_REPETION_LINE_ID( line )		( ( ( line ) == DEFAULT_REPETION_LINE_ID ) \
	|| ( ( line ) == 98 ) || ( ( line ) == 90) || ( ( line ) == 91) || IS_DUNGEONSERVER_LINE( line ) == true )

#define REPETION_PLAYER_COUNT_MAX	( 400 )
#define MAP_INDEX_MAX		( 200 )		// ������ϵĸ�����¼����ʱ��Ϊ50�����Ժ󸱱����˻�Ҫ����

#define  IS_DUNGEONSERVER_LINE(line) ( ( line ) <= DUNGEONSERVER_LINE_ID && ( line ) > DUNGEONSERVER_LINE_ID - MAX_DUNGEONSERVER_NUM )	// �Ƿ�ȫ�ָ�����ID
#define  DUNGEONSERVER_LINE_ID	97	// ȫ�ָ�����ID
#define  GLOBAL_SCENESERVER_ID 10		// ȫ�ֳ�������ID	
#define  IS_GLOBAL_SCENESERVER( line ) ( ( line ) == 10 )




// ��������������
#define NEUTRAL_LINE_ID				( 50 )
#define IS_NEUTRAL_LINE_ID( line )	( ( line ) == NEUTRAL_LINE_ID )

// ��ս����������
#define BATTLE_LINE_ID				( 51 )
#define IS_BATTLE_LINE_ID( line )	( ( line ) == BATTLE_LINE_ID )

// ��Ч������
#define INVALID_LINE_ID		( 250 )
#define INVALID_MAP_INDEX	( 0 )
#define	INVALID_MAP_ID		( 0 )
#define INVALID_REPETION_INDEX		( 0 )


//enum RESULT_CODE
//{
//	RESULT_AGREE	= 0,
//	RESULT_REFUSE,
//	RESULT_IGNORE,
//};
//
//enum TEAM_UPDATE_TYPE
//{
//	ACTION_JOIN			= 0,
//	ACTION_LEAVE,
//	ACTION_KICK,
//	ACTION_ENDTEAM,
//	ACTION_CHANGEHEADER,
//};

// ��ɫɾ��״̬
#define DELETEPROTECTTIME  3*3600*24		// ��ɫɾ������ʱ��	 3*3600*24
#define DELETEALLOWEDTIME  7*3600*24		// ��ɫ��ɾ��ʱ��	 7*3600*24
#define DELETECOOLTIME	   14*3600*24		// ����ɾ����ɫ��������ȴʱ��   14*3600*24 

#define DELETECOOLTIMESPACE	700*3600*24		// ȡ��ɾ���ȴ�״̬����ɾ��ʱ��Ļ���ʱ���

#define MINLEVELDELETEROLE	0				// ��ɫ�ܹ�����ɾ���ȴ�״̬����С�ȼ�
enum EM_RoleDelteStatus
{
	ROLEDELETESTATUS_LIVE				= 0,		// δɾ��״̬
	ROLEDELETESTATUS_DELETEPROTECT		= 1,		// ɾ������״̬
	ROLEDELETESTATUS_DELETEDALLOWED		= 2,		// ɾ������״̬
	ROLEDELETESTATUS_DELETECOOLTIME		= 3,		// ɾ����ȴ״̬
	ROLEDELETESTATUS_LEVELLOW			= 4,		// �ȼ��Ϳ���ֱ��ɾ��
};


enum CampDef
{
	Zero	= 0,
	One		= 1,
	Two		= 2,
	Three	= 3,
	Four	= 4,
	Five	= 5,
	Six		= 6
};

//#define NAME_LENGTH							32

// �Ѻã���ʩ�����漼�ܣ����ܹ��������ԶԻ�
// ����������ʩ�����漼�ܣ����ܹ��������ԶԻ�
// �жԣ������������������ܶԻ�
enum PKType
{
	ENEMY_WITH_OGRE		= 0x0001,		// �Թ�����ӣ��������	
	ENEMY_TO_OGRE		= 0x0002,		// ��������ӣ������﹥����
	FRIEND_WITH_SC		= 0x0004,		// �Ա�������Ѻ�
	FRIEND_TO_SC		= 0x0008,		// ������Ҷ����Ѻ�
	NEUTRAL_WITH_SC		= 0x0010,		// �Ա����������
	NEUTRAL_TO_SC		= 0x0020,		// ������Ҷ�������
	ENEMY_WITH_SC		= 0x0040,		// �Ա�����ҵж�
	ENEMY_TO_SC			= 0x0080,		// ������Ҷ���ж�
	FRIEND_WITH_FC		= 0x0100,		// ���������Ѻ�
	FRIEND_TO_FC		= 0x0200,		// �����Ҷ����Ѻ�
	NEUTRAL_WITH_FC		= 0x0400,		// ������������
	NEUTRAL_TO_FC		= 0x0800,		// �����Ҷ�������
	ENEMY_WITH_FC		= 0x1000,		// �������ҵж�
	ENEMY_TO_FC			= 0x2000,		// �����Ҷ���ж�
};


#define MAX_ERROR_STR_LEN					128		// �������ַ�������  

#define MAX_DIRECTION 8			// �������8��
enum EDirType
{
	DIR_DOWN			= 0,
	DIR_LEFTDOWN		= 1,
	DIR_LEFT			= 2,
	DIR_LEFTUP			= 3,
	DIR_UP				= 4,
	DIR_RIGHTUP			= 5,
	DIR_RIGHT			= 6,
	DIR_RIGHTDOWN		= 7,
};

enum EMotionType
{
	MOTION_IDLE			= 0,		// վ��״̬
	MOTION_RUN			= 1,		// ����״̬
	MOTION_SIT			= 2,		// ����״̬
};

enum EAliveType
{
	ALIVE_NORMAL		= 0,		// ����״̬(����)
	ALIVE_BATTLE		= 1,		// ս��״̬(����)
	ALIVE_DIE			= 2,		// ����״̬
	ALIVE_GHOST			= 3,		// ���״̬
	ALIVE_CLEAR			= 4,		// ������״̬
};

enum EGenderType
{
	GENDER_MALE			= 2,		// ����
	GENDER_FEMALE		= 3,		// Ů��
};

#define  MAX_DIPLOIDSTATE	7		// ��˫״̬����
enum EDiploidState
{
	DIPLOID_STATE		= 0,
	FREEZE_STATE		= 1,
	TIMEID_STATE		= 2,
	TIMERSTOP_STATE		= 3,
	LEFTVALID_STATE		= 4,
	TEMP_STATE			= 5,	// �Ա�����
	ACTIVITY_STATE		= 6,	// ����ӵ�˫������,����10000Ϊ��λ����
};

// ʵ������

enum EEntityType
{
	ENTITYTYPE_NONE			= 0x0000,		// ��
	ENTITYTYPE_PLAYER		= 0x0001,		// ���
	ENTITYTYPE_OGRE			= 0x0002,		// ogre����
	ENTITYTYPE_FUNCNPC		= 0x0004,		// ���� NPC
	ENTITYTYPE_PEDAL		= 0x0008,		// ���塢������
	ENTITYTYPE_ITEM			= 0x0010,		// ��Ʒ	
	ENTITYTYPE_COLLECT		= 0x0020,		// �ɼ�NPC
	ENTITYTYPE_MONEY		= 0x0040,		// ���
	ENTITYTYPE_PET			= 0x0080,		// ����
	ENTITYTYPE_TASKNPC		= 0x0100,		// ����NPC	
	ENTITYTYPE_BOX			= 0x0200,		// Store Box
	ENTITYTYPE_REDSTONE		= 0x0400,		// �ڵ���Ʒ
	ENTITYTYPE_BLOCK		= 0x0800,		// �赲
	ENTITYTYPE_MAGICWEAPON	= 0x1000,		// ����
	ENTITYTYPE_GHOST		= 0x2000,		// �ɴ�Խʵ��
};



enum EVersion
{
	VERSION				= 1005,		// �汾��
};

enum EMetier
{
	METIER_NONE		= 0,			// ����ְҵ
	METIER_WARRIOR	= 1,			// սʿ
	METIER_ROGUE	= 2,			// ����
	METIER_HUNTER	= 3,			// ����
	METIER_SORCERER = 4,			// ��ʦ
	METIER_PRIEST	= 5,			// ��ʿ
	METIER_DRUID	= 6,			// ����ʦ
	METIER_NOVICE	= 7,			// ����ְҵ
};

enum EMetierBlock
{
	BLOCK_NONE		= 0,				// ����ְҵ
	BLOCK_WARRIOR	= 0x0001,			// սʿ
	BLOCK_ROGUE		= 0x0002,			// ����
	BLOCK_HUNTER	= 0x0004,			// ����
	BLOCK_SORCERER  = 0x0008,			// ��ʦ
	BLOCK_PRIEST	= 0x0010,			// ��ʿ
	BLOCK_DRUID		= 0x0020,			// ����ʦ
	BLOCK_NOVICE	= 0x0040,			// ����ְҵ
};

enum EDropType
{
	DROP_OBJECTIVE	= 0,		// ��������
	DROP_SUBJECTIVE = 1,		// ��������
};

// ********************************************************************** //
// CCharProfile
// ********************************************************************** //

class CCharProfile
{
public:
	unsigned int	mCharID;					// ��ɫID
	unsigned int	mAccountID;					// �ʺ�ID
	char			mCharName[ NAME_LENGTH ];	// ��ɫ����
	unsigned char	mSex;						// ��ɫ�Ա�
	unsigned char	mMetier;					// ��ɫְҵ
	unsigned char	mNationality;				// ��ɫ����
	unsigned char	mLevel;						// ��ɫ�ȼ�
	unsigned short	mHairType;					// ��ɫ����
	unsigned short	mFaceType;					// ��ɫ����
	unsigned short	mLineID;					// ������ID
	unsigned short	mMapID;						// ���ڵ�ͼID
	unsigned short	mIndex;
	int				mHairColour;				// ��ɫ��?
	int				mExp;						// ��ɫ����
	int				mMoney;						// ��ɫ��Ǯ
	int				mPosX;						// ��ɫλ��
	int				mPosY;
	int				mStatus;					// ���״̬
	int				mOnlineTime;				// ��ɫ����ʱ��
	time_t			mLastLogin;					// ��ɫ�ϴε�½ʱ��

public:


	CCharProfile( )
	{
#ifdef LINUX
		if ( CObj::msCreateMode )
		{
			Initailize();
		} 
		else
		{
			Resume();
		}
#else
		Initailize();
#endif
	}

	int Initailize( )
	{
		mCharID = 0;
		mAccountID = 0;
		mSex = 1;
		mExp = 0;
		mMetier = 0;
		mNationality = 0;
		mLevel = 0;
		mLineID = 0;
		mMapID = 0;
		mOnlineTime = 0;
		mLastLogin = 0;
		::memset( mCharName, 0, sizeof( mCharName ) ); 
		mMoney = 0;
		mPosX = 0;
		mPosY = 0;
		mStatus = 0;
		return 0;
	}

	int Resume( )
	{
		return 0;
	}



public:
	~CCharProfile( )
	{
	}
};


typedef struct OBJGUID 
{
	union {
		struct {
			time_t			tmstmp;			// ����ʱ��ϵͳʱ��
			unsigned short  index;			// ����ʱ�ĵ������
			unsigned short	where;			// ������GateID, ServerID
		}st; 

		unsigned long long  guid;			// 
	}a;

	OBJGUID() { a.guid = 0; }

	OBJGUID(unsigned short nIndex, unsigned short nGateID, unsigned char nServerID)
	{
		a.st.tmstmp = time(0);
		a.st.index = nIndex;
		a.st.where = (nGateID << 4) + nServerID;
	}

	unsigned long long value() { return a.guid; }
}OBJGUID;

enum REDIRECT_ERR
{
	REDIRECT_PLAYER_IN_MAP		= 1,
	REDIRECT_OBJECT_IS_FULL		= 2,
	REDRIECT_ERR_UNKNOW			= 3,
	REDIRECT_MAP_NOTOPEN		= 4,
	REDIRECT_MAP_PLAYER_IS_FULL = 5,
};

enum TeamUpdateType
{
	emMemberJoin				= 6,
	emMemberQuit				= 7,
	emMemberTick				= 8,
	emTeamEnd					= 9,
	emChangeHead				= 10,
};

enum LSStateType
{
	LSSTATE_NONE			= 0,
	LSSTATE_CHARPROFILE		= 0x00000001,
	LSSTATE_PROPERTY		= 0x00000002,
	LSSTATE_BAGGAGE			= 0x00000004,
	LSSTATE_STORAGE			= 0x00000008,
	LSSTATE_TASK			= 0x00000010,
	LSSTATE_FRIEND			= 0x00000020,
	LSSTATE_REPETION		= 0x00000040,
	LSSTATE_YUANBAO			= 0x00000080,
    LSSTATE_YAOQIANSHU1     = 0x00000100,
    LSSTATE_YAOQIANSHU2     = 0x00000200,

	LSSTATE_TOTAL_COMMPLTE	=	LSSTATE_CHARPROFILE + \
								LSSTATE_PROPERTY + \
								LSSTATE_BAGGAGE + \
								LSSTATE_STORAGE + \
								LSSTATE_TASK + \
								LSSTATE_FRIEND +\
								LSSTATE_REPETION +\
								LSSTATE_YUANBAO + \
                                LSSTATE_YAOQIANSHU1 + \
                                LSSTATE_YAOQIANSHU2,
};

/*	
*	���峣�÷���ֵ
*/

#define LK_ISUCCESS			1 
#define LK_IERROR			0
#define LK_NULL				NULL
#define LK_TRUE				true
#define LK_FALSE			false
#define LK_ZERO				0
#define LK_BINDMONEY		0
#define LK_NOTBIND			1
#define LK_ONE				1

enum EM_HONETSHOLE_SCORE 
{	 
	HONETSHOLE_SCORE_REPTIONLEVEL = 1,		// �����ȼ�
	HONETSHOLE_SCORE_OGRENUM	  = 2,		// ��������
	HONETSHOLE_SCORE_TOTALTIME	  = 3,		// ͨ��ʱ��
	HONETSHOLE_SCORE_GENERALSCORE = 4,		// ����
	HONETSHOLE_SCORE_EXTRALSCORE  = 5,		// ��������
	HONETSHOLE_SCORE_TOTALSCORE	  = 6,		// ������							 
};

enum REPETION_EVENT_NOTICE						   
{
	REPETION_NONE,								// ���¼�
	REPETION_CLOSE,								// �����ر�, ����1 �೤ʱ������
												// ����ɱ  : ����1 = ���������೤ʱ�����������2 = 1
												//			����1 = �����೤ʱ�����������2 = 2
	REPETION_END,								// ��������������1 ( 0ʧ�ܣ� 1�ɹ� )
	REPETION_CREATE_NPC,						// ����NPC�� ����1 ( npc TemplateID ), ����2( ʱ�� )
	REPETION_KILL,								// NPC����,	 ����1 ɱ��NPC��EntityID, ����2 NPCģ��ID
	REPETION_COUNTDOWN,							// ��������ʱ, ��ͬ�ĸ�������ʱ��ͬ, ����1Ϊͬһ�����еĲ�ͬ����ʱ
												// ����: 1 ����ͨ������ʱ(����1 = 1, ����2 = ʱ��), 
												//		2 ��������ʱ( ����1 = 2, ����2 = ʱ�� )
												//		3 �������ط���( ����1 = 3, ����2 = ʱ�� )
												// ����ɽս�� : 1 ��ʼ����ʱ( ����1 = 2�� ����2 = ʱ�� )
												//				2 �ڶ��׶ε���ʱ( ����1 = 1�� ����2 = ʱ�� )
												//
												// ������:	1 ��������㵹��ʱ( ����1 = 1, ����2 = ʱ�� )
												// Ʒ����	1 ���������( ����1 = 1, ����2 = ʱ�� )
												// ���ƴ�ս 1  ��Ǵ�������ʱ��( ����1 = 1�� ����2 = ʱ�� )
												//			2 ���Ǵ�������ʱ��( ����1 = 2�� ����2 = ʱ�� )
												// 			3	���̸���˸���ʱ��( ����1 = 3, ����2  = ʱ��  )
												//			4  ���̸���˸���ʱ��( ����1 = 4, ����2 = ʱ�� )
												//			5 ��������ʱ��( ����1=5, ����2= ʱ�� )
												// ����԰	1 ��԰ʱ��( ����1 = 1�� ����2 = 2 )
												// ������   1 �²㿪��ʱ��( ����1 = 1 )
												// ����ɱ   1 pk��ʼ����ʱ������1 = 1�� ����2 = ʱ�䣩
												//			2 pk��������ʱ������1 = 2�� ����2 = ʱ�䣩
												//			3 �������浹��ʱ������1 = 3�� ����2 = ʱ�䣩
												//			4 a�׶ν�������ʱ������1 = 4�� ����2 = ʱ�䣩
												//          5 b�׶ο�ʼ����ʱ(����1 = 5�� ����2 = ʱ��)
												// �޵׶� 	1 ���Ĳ������ֵ���ʱ
												//			2 ���Ĳ���ʱ����¼ʱ��
												// ���ս��:	1.��ʾս����������ʱ ������1 = 1�� ����2 = ʱ�䣩
												//				2.ħ���Źرյ���ʱ (����1=2������2=ʱ��)												//				
	REPETION_COUNTDOWN_END,						// ��������ʱ����, ����0 �����رյ���ʱ
												// ��������ʱ������ ����1������ͬREPETION_COUNTDOWN
	REPETION_TAKE_COUNT,						// ��������. ��ͬ�ĸ������������岻ͬ
												// ���: 	1 ������( ����1 = 1, ����2 = �������� )
												// 			2 ʯ������( ����1 = 2�� ����2 = ���� )
												//			3 ��������( ����1 = 3�� ����2 = ���� )
												//			4 ����( ����1 = 4�� ����2 = ���� )
												//			5 �����ȼ�( ����1 = 5 ����2 = �ȼ� )
												//			6 ɱ��ʯ������( ����1 = 6, ����2 = ���� )
												//			7 �������۴���( ����1 = 7, ����2 = ���� )
												//			8 �����۴���( ����1 = 8, ����2 = ���� )
												//			9 �������۴���( ����1 = 9, ����2 = ���� )
												//			10 �����۴���( ����1 = 10, ����2 = ���� )
												//			11 �������۴���( ����1 = 11, ����2 = ���� )
												//			12 �����۴���( ����1 = 12, ����2 = ���� )
												//			13 �������۴���( ����1 = 13, ����2 = ���� )
												//			14 �����۴���( ����1 = 14, ����2 = ���� )
												// ����:	1 ����( ����1 = 1, ����2 =  ������ )
												//			2 �ȼ�( ����1 = 2, ����2 = �ȼ� )
												//			3 ʱ��( ����1 = 3�� ����2 = ʱ�� )
												//			4 ��������( ����1 = 4, ����2 = �������� )
												//			5 ɱ������( ����1 = 5, ����2 = ɱ������ )
												// ������	1 ������(  ����1 = 1, ����2 = �������� )
												//			2 ����( ����1 = 2, ����2 = ����)
												//			3 ʣ��ʱ��*( ����1 = 3, ����2=ʱ�� )
												//			4 �ȼ�( ����1 = 4, ����2 = �ȼ� )
												//			5 ɱ������( ����1 = 5, ����2 = ���� )
												//			6 �������۴���( ����1 = 6, ����2 = ���� )
												//			7 �����۴���( ����1 = 7, ����2 = ���� )
												//			8 �������۴���( ����1 = 8, ����2 = ���� )
												//			9 �����۴���( ����1 = 9, ����2 = ���� )
												//			10 �������۴���( ����1 = 10, ����2 = ���� )
												//			11 �����۴���( ����1 = 11, ����2 = ���� )
												//			12 �������۴���( ����1 = 12, ����2 = ���� )
												//			13 �����۴���( ����1 = 13, ����2 = ���� )
												//			14 ��ý�Ǯ( ����1 = 14, ����2 = ��Ǯ )
												// Ʒ����	1 ������ ( ����1 = 1, ����2 = ������ )
												// 			2 ����( ����1=2, ����2=��ʽ(0���ɹ�, 1�ɹ�))
												//			3 ���������( ����1=3, ����2=����)
												//			4 ʱ��( ����1= 4, ����2=ʱ��)
												//			5 �׶�( ����1=5�� ����2=�׶�)
												//			6 ɱ��������( ����1=6, ����2= ������ )
												//			7 �ȼ�( ����1= 7�� ����2=�ȼ�)
												//			8 �´󲨿�ʼ( ����1=8, ����2=����)
												//			9 ���س���( ����1=9 )
												// �Ʒ䶴	�����鿴ö��EM_HONETSHOLE_SCORE�е�ֵ������2��ʾ��Ӧ����ֵ
												// ���ƴ�ս	1 ɱ������ ( ����1 = 1 �� ����2 = ���� )
												// 			2 ����ʱ��( ����1=2, ����2=ʱ��)
												//			3 �����ȼ�( ����1=3�� ����2=�ȼ� )
												//			4 ������Ǹ������( ����1=4�� ����2=����)
												//			5 ���̸���˷��˸������( ����1=5�� ����2=����)
												//			6 ����( ����1=6�� ����2=����);
												// ������   1 ����( ����1 = 1, ����2 = ���� )
												//			2 ��߲���( ����1 = 2. ����2 = ���� )
												//			3 ɱ������( ����1 = 3. ����2 = ���� )
												// ����ɱ:	1 ����( ����1 = 1, ����2 =  ������ )
												//			2 �ȼ�( ����1 = 2, ����2 = �ȼ� )
												//			3 ���ʱ��( ����1 = 3�� ����2 = ʱ�� )
												//			4 ɱ������( ����1 = 4, ����2 = ɱ������ )
												//			5 ɱ�˻���( ����1 = 5, ����2 = ɱ�˻��� )
												//			6 ���ʱ�����( ����1 = 6, ����2 = ���ʱ����� )
												//			7 ���ڴ������������1 = 7�� ����2 =  ���������
												//			8 �������ɱ����������1 = 8�� ����2 = ���ɱ������
												//          9 ��þ��飨����1 = 9������2 = ��þ���ֵ��
												//			10�˳�������ʽ������1 = 10�� ����2 =1 ������ɱ����
												//										 ����2 =2 ����ɱ��
												//			11 ���ʱ���ʱ��ʼ������1 = 11�� ����2 = ʱ�䣩
												//			12 ���ʱ����ͣ������1 = 12 ������2 = ʱ�䣩
												//			13 ��ǰ��ն��( ���� 1= 13�� ����2=ɱ���� )
												//			14 �������������� 1 = 14�� ����2 = ���� ��
												//			15 ������߻��֣����� 1 = 15�� ����2 = ���֣�
												//			16 �����ն��( ���� 1= 16�� ����2 = �����ն��)
												// ���ս��	1. ���˻���(����1=1������2=���˻���)
												//			2. �Ŷӻ���(����1=2������2=�Ŷӻ���)
												//			3. �ܻ���(����1=3������2=�ܻ���)												//			
												//			4. ��ɱ����(����1=4������2=��ɱ����)
												//			5. ��ɱ�����(����1=5������2=��ɱ�����)
												// �޵׶�:	1 ������ʣ��С��( ����1 = 1 )
	REPETION_RESOURCE,							// ����ս������1 ������Դ ����2 �ط���Դ
	REPETION_GET,								// ����ս������1 ռ���CampID�� ����2 ռ���Index	
	REPETION_CORPS_FLAG,						// ����ս���������,  ����1 ����ռ�췽����ӪID,����2 �Լ���ӪID,����3 ���������������
	REPETION_CORPS_RESOURCE,					// ����ս������1 ������Դ ����2 �ط���Դ
	REPETION_CORPS_OGRE,						// ����սʥ��̨
	REPETION_RELIVE,							// ��� ����1 ʣ�ิ��ʱ��	����2 �ܹ�����ʱ��
	REPETION_FLAGTEMP,							// ���Ŵ���ģ��ID
	REPETION_MSG,								// ����: 1 ���ط��俪��( ����1 =1 )
												// ����ս ����1 = 0 ֪ͨ��Դ����
												// �Ʒ���: ���� 1 = 0 ��ʾ���B ���� 1 ��ʾ���C ���� 2 ��ʾֹͣ��ʱ, ����2��ʾ��ѳ���ʱ��
												//	���ƴ�ս:
												// 			1 BOSS����( ����1=1, ����2=1( ������ ), 2( ����⨺� ),
												//									3( ����Ȯ ), 4( ������ ),
												//									5( ţħ�� ), 6( ��ˮ������ )
												//									7( �Ʒ���� ), 8( ������ )
												//									9( ��������	), 10( ��Ǵ��� )
												//									11( ���Ǵ��� ), 12( ���̸���� )
												//									13( ���̸���� )
												//			2 �����������δ��( ����1=2, ����2=ʱ�� )
												//			3 �����������δ��( ����1=3�� ����2=ʱ�� )
												//			4 ������������δ��( ����1=4�� ����2=ʱ��)
												//			5 ������������δ��( ����1=5�� ����2=ʱ�� )
												//	����԰:
												//		1 �����Ե	( ����1 = 1 )
												//		2 ��Ե����	( ����1 = 2 )
												//		3 ����ʱ��ʣ����Ե��( ����1 = 3, ����2 = ���� )
												//	������/������60��(���лþ�)
												//		1 ��ǰ¥����� ( ����1 = 1 )
												//	�޵׶�
												//		1 ��һ������ͷĿ����( ����1 = 1�� ����2 = 72914( �� ), 72915( 
												//				�� ), 72916( �� )
												//		2 ��һ�����ˮ��( ����1 = 2 )
												//		3 ��һ������ˮ��( ����1 = 3 )
												//		4 ��һ�����ˮ��( ����1 = 4 )
												//		5 ��һ�����ˮ����( ����1 = 5 )
												//		6 ��һ������ˮ����( ����1 = 6 )
												//		7 ��һ�����ˮ����( ����1 = 7 )
												//		8 ��һ��������( ����1 = 8 )
												//		9 �ڶ�����Ů��( ����1 = 9 )
												//		10��������ұ�����( ����1 = 10�� ����2 = ���ID )
												// 		11������ֱ�����( ����1 = 11 )
												//		12���Ĳ���λ����( ����1 = 12 )
												//		13���Ĳ�������( ����1 = 13 )
												//		14 �����ȼ�( ����1 = 14 )
												//		15 ����ʱ��( ����1 = 15 )
												//		16 ����ɱ������( ����1 = 16 )
												//		17 ��������( ����1 = 17 )
												//		18 �����Ʒ�( ����1 = 18 )
												//		19 ������BOSS����( ����1 = 19 )
												// 		20 ���г���( ����1 = 20 )
												//		21 ��ͼĿ��( ����1 = 21, ����2 = ��ǰ��ͼID  )
												//		22 ˮ����( ����1 = 22 )
												//	���ս�� 1.����ս������������1=0 �� ����2=ս��������
												//			 2.�з�ս������ (����1=1 �� ����2=ս��������
												//			 3.��ɱ������(����1=2 �� ����2=ɱ����������												
												//			 4.������Ӫ��õĻ�����(����1=3 �� ����2=��������
												//			 5.������ٴ�(����1=4 �� ����2=���������
												//			 6.ɱ�������(����1=5 �� ����2=�������
												//			 7.�з���Ӫ����(����1=6 �� ����2=�������
												//			 8.������(����1=7 �� ����2=(0��ʾ������Ӫ1��ʾ�з���Ӫ�� ����3=�������Ľ�ɫ����
												//			 10.��������֪ͨ(����1=8 �� ����2=(0��ʾ������Ӫ1��ʾ�з���Ӫ������3=ɱ��boss�������
												//			 11.������������(����1=9 �� ����2=(0��ʾ���1��ʾ������
												//			 12.�з���������(����1=10 ������2=(0��ʾ���1��ʾ������
												//			 13.�����������(����1=11 ������2=(��ʾ�����������)
												//			 13.�з��������(����1=12 ������2=(��ʾ�з��������)
	REPETION_UPDATETIME,						// ͬ������ʱ��,����1 ��ӪID ����2 ������ʱ��
	REPETION_BATTLEMAP,							// ����ս�����ͼ�� ����1=����ĵ�ͼID
	REPETION_SHOW_VALUE,						// ������60��:	1 ����( ����1 = 1, ����2 = ���� )
												//				2 ��߲���( ����1 = 2. ����2 = ���� )
												//				3 ɱ������( ����1 = 3. ����2 = ���� )

};


enum RES_TYPE
{
	RES_NONE	= 0,			// �޿���
	RES_TYPE1	= 1,
	RES_TYPE2	= 2,
	RES_TYPE3	= 3,
	RES_TYPE4	= 4,
	RES_TYPE5	= 5,
	RES_TYPE6	= 6,
	RES_NUM		= 7,	
};

enum UPG_TYPE
{
	UPG_PROPERTY = 0,
	UPG_RESDEF	 = 1,
	UPG_RESATT	 = 2,
};

enum PEDAL_TYPE
{
	PEDAL_TELEPORT		= 0,		// ���͵�̤��
	PEDAL_TRAP,						// ����̤��
	PEDAL_HIEROGRAM,				// ���̤��
	PEDAL_NEEDFIRE,                 // ��������
};

enum CAMP_TYPE
{
	CAMP_1 = 1,
	CAMP_2 = 2,
};

// ����ս�ǳظ�������
enum CORPS_DATA
{
	DATA_CAMP1_CORPS = 0,		// ��Ӫ1��Ӧ�ľ���ID
	DATA_CAMP2_CORPS,		// ��Ӫ2��Ӧ�ľ���ID
	DATA_FLAG_OWNER,
	DATA_BATTLE_CHALLEGE,
	DATA_BATTLE_SCRABBLE,
};

// ���������� ������ֵ����ö��
enum enLianhuadongMarkType
{
	MARKTYPE_FB_LEVEL	=	1,	// �����ȼ�
	MARKTYPE_SAVE_NUM,		// ���������
	MARKTYPE_KILLNUM,		// ɱ������
	MARKTYPE_TIME,			// ͨ��ʱ�䣨�룩
	MARKTYPE_MARK,			// ����
	MARKTYPE_EXTRA_MARK,	// ��������
};


// ����MapID����
#define _REPE_LONGGONG_MAP_ID_ 					( 14 )
#define _REPE_LONGGONG_EASY_MAP_ID_ 			( 58 )
#define _REPE_LONGGONG_HARD_MAP_ID_ 			( 59 )
#define _REPE_PANTAO_MAP_ID_ 					( 21 )
#define _REPE_PANTAO_EASY_MAP_ID_ 				( 56 )
#define _REPE_PANTAO_HARD_MAP_ID_ 				( 57 )
#define _REPE_DAYANTA_MAP_ID_ 					( 81 )
#define _REPE_FAMILY_TASTE_MAP_ID_ 				( 94 )		// Ʒ����
#define _REPE_FAMILY_TASTE_DIE_MAP_ID_          ( 94 )      // Ʒ���ҵظ�
#define _REPE_LIANHUADONG_MAP_ID_ 				( 92 )
#define _REPE_HUANGFENGDONG_MAP_ID_ 			( 91 )
#define _REPE_HUAGUOSHAN_MAP_ID_ 				( 55 )		// ��ս����ɽ��ͼID
#define _REPE_FAMILY_MAP_ID_					( 66 )		// ����ս��ͼ
#define _REPE_CORPS_MAP_ID_						( 71 )		// ����ս��ͼ
#define _REPE_FLY_WAR_MAP_ID_					( 80 )		// ���п�ս��ͼ
#define _REPE_GRAND_MAP_ID_						( 99 )		// ����԰
#define _REPE_TOWER_MAP_ID_						( 119 )		// ͨ����
#define _REPE_WUDITON_MAP_ID_					( 144 )		// �޵׶�
#define _REPE_DALUANDOU_MAP_ID_                 ( 165)     // ���Ҷ�
#define _REPE_SHITU_MAP_ID_						( 160 )

// ��������
enum
{
	_REPE_INDEX_START_			 = 1, // ������ʼ������1��ʼ������0 

	_REPE_GUANGHANGONG_INDEX_    = 1,	// �㺮���þ�
    _REPE_PUTUO_INDEX_           = 2,	// ����ɽ�þ�
    _REPE_WUZHUANGGUAN_INDEX_    = 3,	// ��ׯ�ۻþ�
    _REPE_SHITUOLING_INDEX_      = 4,	// ʨ����þ�
    _REPE_LINEYANGE_INDEX_       = 5,	// ���̸�þ�
    _REPE_TIANWANG_INDEX_        = 6,	// ������þ�
    _REPE_LONGGONG_INDEX_        = 7,	// ����
    _REPE_LONGGONG_EASY_INDEX_   = 8,	// ��������
    _REPE_LONGGONG_HARD_INDEX_   = 9,	// ��Ӣ����
    _REPE_PANTAO_INDEX_          = 10,	// ���
    _REPE_PANTAO_EASY_INDEX_     = 11,	// �������
    _REPE_PANTAO_HARD_INDEX_     = 12,	// ��Ӣ���
    _REPE_HUAGUOSHAN_INDEX_      = 13,	// ����ɽ
    _REPE_CHANGBAOTU_INDEX_      = 14,	// �ر�ͼ����
    _REPE_CORPS_BATTLE_INDEX_    = 15,	// ����ս
    _REPE_FAMILY_INDEX_          = 16,	// ����ս
    _REPE_DAYANTA_INDEX_         = 17,	// ������
    _REPE_LIANHUADONG_INDEX_     = 18,	// ������
    _REPE_HORNETSHOLE_INDEX_     = 19,	// �Ʒ綴
    _REPE_FAMILY_TASTE_INDEX_    = 20,	// ����Ʒ����
	_REPE_CORPS_CHALLEGE_INDEX_	 = 21,	// ������ս��
	_REPE_FAMILY_CHALLENGE_INDEX_= 22,	// ������ս��
	_REPE_FLY_WAR				 = 23,	// ���ƴ�ս
	_REPE_GRAND_INDEX_			 = 24,	// ����԰
	_REPE_TOWNER_INDEX_			 = 25,	// ͨ����
	_REPE_LASTONE_INDEX_		 = 26,	// ����ɱ
	_REPE_LASTONE_TEAM_INDEX_	 = 27,	// ����ɱ���
	_REPE_WUDIDONG_INDEX_		 = 28,	// �޵׶�
	_REPE_SHITU_INDEX_			 = 29,  // ʦͽ����
	_REPE_GLOBALWAR_INDEX_		 = 30,  // ȫ��ս������
	_REPE_CORPSBOSS_INDEX_		 = 31,  // ����boss����
	_REPE_NEWTOWER_INDEX_		 = 32,	// ������60��

	_REPE_MAX_COUNT_,
};



// ping��ʱ�䶨��
#define _PLAYER_PING_TIME_MAX_					( 10 * 1000 )

// ��Ӫ�б�
enum EServerList
{
	EM_JUXIAN	= 1,	// ����
	EM_QIANKUN	= 2,	// Ǭ��
	EM_PUTI		= 3,	// ����
	EM_HUNYUAN	= 4,	// ��Ԫ
};


// 2������ĳ���
#define  MAX_PASSWORD_LENGTH 32


// ��ȫ�����״̬
enum EPasswordStatus
{
	EM_PASSWORD_NOTSET		=	1,	// δ����״̬
	EM_PASSWORD_PROTECTTIME	=	2,	// ��ȫ����ʱ��
	EM_PASSWORD_PASSLOCKED	=	3,	// ���뱣��״̬
	EM_PASSWORD_PASSFREE	=	4,	// ������֤�Ѿ�ͨ����״̬
};

// ��ȫ����Ӱ��Ĳ���
enum EPassWordAction 
{
	EM_PASSWORD_ACTION_SETPASSWORD = 0x0001,	// ��������
	EM_PASSWORD_ACTION_GAMEACTION  = 0x0002,	// ��Ϸ����
};

// ��ȫ����ʱ�����Сֵ
#define  MIN_PASSWORD_PROTECTIME 60		// һ����

// ��ȫ����ʱ������ֵ
#define  MAX_PASSWORD_PROTECTIME 3600   // һСʱ

// ��ȫ����ʱ���Ĭ��ʱ��
#define	  DEFAULT_PASSWORD_PROTECTTIME 180 // ������


// bourse
#define BOURSE_DB_YB_KEY		( 1 )
#define	BOURSE_DB_MONEY_KEY		( 2 )

#define BOURSE_DB_THREAD_KEY	( 5 )


// �ͻ��˿����ļ� ����3 ����
#define CLI_CTRL_PARM3_LEN		256


// 100421 MAOCY ADD-BEGIN
//============================================================
// <T>���ط�������־��</T>
//============================================================
enum EServerGatewayFlag{
   EServerGatewayFlag_Normal,    // ��ͨ
   EServerGatewayFlag_Recommend, // �Ƽ�
};

//============================================================
// <T>���ط�����״̬��</T>
//============================================================
enum EServerGatewayStatus{
   EServerGatewayStatus_Unknown, // δ֪(K)
   EServerGatewayStatus_Update,  // ά��(U)
   EServerGatewayStatus_Full,    // ��(F)
   EServerGatewayStatus_Rush,    // ��æ(R)
   EServerGatewayStatus_Busy,    // æµ(B)
   EServerGatewayStatus_Idle,    // ����(I)
};
// 100421 MAOCY ADD-END


//Ԫ����̯
enum EStallType{
	EM_STALL_TYPE_ALL = 0,  //����
	EM_STALL_TYPE_MONEY = 1, //�ǰ���̯
	EM_STALL_TYPE_YB = 2, //Ԫ����̯
};

enum EMIbstoreLimit
{
        EM_LIMIT_BY_LIFECYCLE   = 0,	// ��ɫ�޹�
        EM_LIMIT_BY_HOUR        = 1,	// ��ɫÿСʱ�޹�
        EM_LIMIT_BY_6HOUR       = 2,	// ��ɫÿ6Сʱ�޹�
        EM_LIMIT_BY_DAY         = 3,	// ��ɫÿ���޹�
        EM_LIMIT_BY_WEEK        = 4,	// ��ɫÿ���޹� (0-6)
        EM_LIMIT_BY_MONTH       = 5,	// ��ɫÿ���޹�
        EM_LIMIT_BY_YEAR        = 6,	// ��ɫÿ���޹�
        EM_LIMIT_BY_LEVEL       = 7,	// ��ɫÿ�ȼ��޹�
        EM_LIMIT_BY_5LEVEL      = 8,	// ��ɫÿ5���޹�
        EM_LIMIT_BY_10LEVEL     = 9,	// ��ɫÿ10���޹�
}; 

#define BIND_MONEY 1
#define UNBIND_MONEY  2
#define LINEKONG_MONEY   3
#define SILVER_YUANBAO   4
#define GOLDEN_YUANBAO   5
#define COMBAT_FAME		 6
#define REPE_FAME		 7
#define COMMON_FAME		 8


//���ܸ��ѵĹ������ʱ���⼸��
enum EFuncConsumeType
{
	RELIVE_BY_FUNCCONSUME			= 100000,	//����
	DEXP_BY_FUNCCONSUME				= 100001,	//˫������
	BLACKPILLSTIME_BY_FUNCCONSUME	= 100002,	//Ǭ���裨�ڹ���
	VIPTIME_BY_FUNCCONSUME			= 100003,	//VIPʱ��
	BAGTIME12_BY_FUNCCONSUME		= 100004,	//12�����ʱ��
	BAGTIME14_BY_FUNCCONSUME		= 100005,	//14�����ʱ��
	BAGTIME16_BY_FUNCCONSUME		= 100006,	//16�����ʱ��
	BAGTIME18_BY_FUNCCONSUME		= 100007,	//18�����ʱ��
	PROTECTTIME_BY_FUNCCONSUME		= 100008,	//������buff
};
//���ܸ��� ����
enum{
	FUNC_BIND_MONEY				= BIND_MONEY,		////�󶨽�Ǯ����
	FUNC_UNBIND_MONEY			= UNBIND_MONEY,		//��Ǯ����
	FUNC_LINEKONG_MONEY			= LINEKONG_MONEY,	//? ���۱ң�
	FUNC_SILVER_YB				= SILVER_YUANBAO,	//��Ԫ������
	FUNC_GOLDED_YB				= GOLDEN_YUANBAO,	//Ԫ������
	FUNC_CONSUME_COUNT			= 5,
};

enum EFuncUnitType
{
	FUNC_UNIT_ONCE		= 1,	// һ��
	FUNC_UNIT_H			= 2,	// Сʱ
	FUNC_UNIT_D			= 3,	// ��
};

enum ERepetionIndexType
{
	REPETION_INDEX_TYPE_COMMON		= 0,	// ��ͨ�������Խ���
	REPETION_INDEX_TYPE_RELOGIN		= 1,	// �������½���ĸ���֪ͨ
	REPETION_INDEX_TYPE_ENDRELOGIN	= 2,	// �����븱���ر�
};
