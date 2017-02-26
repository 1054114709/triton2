#ifndef _FRIEND_TYPE_H_
#define _FRIEND_TYPE_H_

#define FRIENDS_LIMIT 220
#define ENEMIES_LIMIT 100
//#define STRANGER_LIMIT 50

#define BLACKLIST_LIMIT 50

#define MAX_APPLY_NUM 10 // ÿ���������ͬʱ������Ӻ��ѵ�����

#define PLAYER_NAME_SIZE 32
#define GROUP_NAME_SIZE 32 

#define PLAYER_GROUP_COUNT 4

// �����������
#define GROUP_NAME_LENGTH 32

// ÿ����Ϣ�����Ѹ��� <�������ļ�>
#define MAX_ONCE_FRIENDS 30

// ͬ��(�������Ϊ����)
#define AGREE_CODE 1
#define REFUSE_CODE 0

// ÿ����Ϣ��󳤶�
#define MAX_FRIEND_MSG_LENGTH 240
#define MAX_FRIEND_MSGBUF_LENGTH 4096

// ÿ��

enum EFriendModuleErrorID
{
	ERR_INSFRIEND_ON_FULL,
	ERR_INSFRIEND_ON_DECLINE
};


enum EFriendModuleSelectOption
{
	ESELECT_OPTION_IS_ACCEPT,
	ESELECT_OPTION_IS_DECLINE
};

// �ҵĺ��Ѻ��ҵĹ�ϵ (ֻ���ں�����ӣ���)
enum EPlayerRels 
{ 
	YOUR_HUSBAND ,	// �ɷ�
	YOUR_WIFE ,			// ����
	YOUR_BROTHER ,		// �ֵ�
	YOUR_TEACHER ,		// ʦ��
	YOUR_WATERSHOOT ,    // ͽ��	
	YOUR_FAMILY ,		// ����
	YOUR_CORPS ,			// ����
	YOUR_FRIEND, 
	YOUR_ENEMY , 
	YOUR_BLACKLIST , 
	YOUR_STRANGER ,	    // İ����
	YOUR_LATEST_CONTACTER, // �����ϵ�ˣ����߼��ϵĹ�ϵ���࣡
};

#define IS_FRIEND(rel)  (rel<=YOUR_FRIEND) // �Ƿ����

//���״̬
enum EPlayerShow 
{ 
	AT_OFFLINE = 0,		// ����
	AT_ONLINE ,		// ����
	AT_BUSY,		// æµ
	AT_LEAVE,		// �뿪
	AT_SUSPEND,		// �һ�
	AT_FIGHT,		// ս��	
	AT_NOTFAZE,		// ����
	AT_HIDE,		// ����
};

enum EKilledTypde 
{ 
	KILLED_OTHER, 
	BE_KILLED_BY_OTHER,
	BY_MANUAL
};

enum EOprFriendCode
{
	ADD_TO_STRANGER,    // ��ӵ�İ���ˣ���Ч�ֶΣ�ID������, rel2me
	ADD_TO_FRIEND,		// ��ӵ������б������ֶζ���Ч
	DEL_FRIEND,			// ɾ�����ѣ���ID��Ч
	ENEMY_MOVEFIRST,	// ���������ƶ�����һλ, ID��ɱ����������ɱ����,ʱ��� ��Ч
	ADD_TO_ENEMY,		// ��ӳ�� ���˷��� ����Ч
	DEL_ENEMY,			// �ӳ���б���ɾ������ID��Ч
	LOCK_ENEMY,			// ������У�ID��Ч
	DEL_BLACK,			// ɾ�������� ID,��ϵ��Ч
	ADD_TO_BLACK,		// ��Ӻ����� ID ���� ͷ�� �Ա� ��ϵ ״̬ ��Ч
	UNLOCK_ENEMY,		// ������У�ID��Ч
};

// ɾ�����ѵ����ͱ�ʾ
enum EDelFriendType
{
	TYPE_FRIEND ,
	TYPE_BLACK ,
	TYPE_EMEMY ,
	TYPE_DELRELS,	// ���ĳ�ֹ�ϵ
};

// ��GATEȡ���ݵı�־
enum enGateFlags
{
	FLAG_GETFRIEND_STATE    = 0x0001,   // ȡ����״̬
	FLAG_GETFRIEND_ALL      = 0x0002,	 // ȡ������Ϣ������ͷ���
	FLAG_GETENEMY_STATE     = 0x0003,
	FLAG_GETENEMY_ALL       = 0x0004,
	FLAG_GETBLACK			= 0x0005,
	FLAG_GETCONTACTER		= 0x0006,
	FLAG_GETCONTACTER_STATE	= 0x0007,
};

// ȥ����ȡcharid �ı�� ����session
enum enGetCharIDType
{
	TYPE_ADD_FRIEND,
	TYPE_ADD_BLACK ,
};

// ������� ��������
enum enLockOprType
{
	LOCK_TYPE_LOCK = 1,  // ����
	LOCK_TYPE_FREE = 2,  // ����
};

// �������ܶȵ�����
enum EM_EntimacyChangeType
{
	ENTIMACY_CHANGE_TYPE_MODIFY			= 0, // ����
	ENTIMACY_CHANGE_TYPE_UPDATE			= 1, // ֱ�Ӹ���
	ENTIMACY_CHANGE_TYPE_KILL			= 2, // ��Ϊ��ɱ������
	ENTIMACY_CHANGE_TYPE_LEAVESWORN		= 3, // ��Ϊ�뿪��ݶ�����
	ENTIMACY_CHANGE_TYPE_TEAM			= 4, // ��Ϊ��Ӹı����ܶ�
	ENTIMACY_CHANGE_TYPE_DISBANDSWORN	= 5, // ��Ϊ��ݽ�ɢ
	ENTIMACY_CHANGE_TYPE_DIVORCE		= 6, // ��Ϊ���������ܶ�
	ENTIMACY_CHANGE_TYPE_FLOWER			= 7, // ��Ϊ�ͻ��ı����ܶ�
};

// ���һ�δ�������
#define  MAX_ONCE_DISPOS 30

// ������ף���Ĵ������ֶ�
#define  MAX_FRIENDBLESS_NUM	50

// �����ϵ������
#define LATEST_CONTACT_MAX 30 

#endif
