#pragma once

#include "coretype.h"
#include "object.h"

#define PLAYER_DATALEN 60000	// ���TLV Buff����

#define MAX_MESSAGE_ONCE_SEND	1024 // �鲥��Ϣʱ��һ�οɷ��͵������Ϣ����
#define MAX_ENTITY_ONCE_SEARCH	2000 // һ�δӵ�ͼ����������������


// ʵ������
enum EmEntityReputation
{
	REP_FRIENDLY	= 0x0001,	// �Ѻ�
	REP_NEUTRALITY	= 0x0002,	// ����
	REP_HOSTILITY	= 0x0004,	// �ж�

	REP_ALL			= REP_FRIENDLY | REP_NEUTRALITY | REP_HOSTILITY, // ����

};

//  ʵ���ϵ
enum EmEntityRelationShip
{
	REL_TEAM		= 0x0100,	// ����
	REL_FAMILIY		= 0x0200,	// ����
	REL_FRIEND		= 0x0400,	// ����

	REL_ALL			= REL_TEAM | REL_FAMILIY | REL_FRIEND, // ����
};

// �ɼ���
enum EmEntityVisiblitiy
{
	VISIBLITY_ALL = 0,	// ������Ҷ��ɼ�
	VISIBLITY_SELF,		// ���Լ��ɼ� 
	VISIBLITY_TEAM,		// ������ɼ�
};

// ʵ���������( ��ҪΪ��ͼģ������� )
enum EmCombinedEntityType
{
	// �ᶯ��ʵ��
	COMB_ENTITYTYPE_DYNAMIC_ENTITY	= ( ENTITYTYPE_PLAYER | ENTITYTYPE_PET | ENTITYTYPE_FUNCNPC | ENTITYTYPE_OGRE ), 
	// ���ᶯ��ʵ��
	COMB_ENTITYTYPE_STATIC_ENTITY	= ( ENTITYTYPE_ITEM | ENTITYTYPE_MONEY | ENTITYTYPE_PEDAL ),					
	// ��������ʵ��
	COMB_ENTITYTYPE_ALL				= ( COMB_ENTITYTYPE_DYNAMIC_ENTITY | COMB_ENTITYTYPE_STATIC_ENTITY ),		
};


//// ��ҷ���״̬
//enum EmPlayerServiceStatus
//{
//	PLAYER_DONOTHING= 0,	// ʲôҲû��
//	PLAYER_STALLING,		// ��̯��...
//							// .. �����������״̬
//};


// ��Ϣ�е�ģ���־
//enum EmModuleFlagForMessage
//{
//	MESSAGE_PROPERTY	= 0x0002,
//	MESSAGE_MAP			= 0x0003,
//	MESSAGE_TASK		= 0x0004,
//	MESSAGE_CHAT		= 0x0005,
//	MESSAGE_FRIEND		= 0x0006,
//	MESSAGE_TEAM		= 0x0007,
//	MESSAGE_MAIL		= 0x0008,
//	MESSAGE_TRADE		= 0x0009,
//	MESSAGE_STALL		= 0x000A,
//	MESSAGE_ACTIVITY	= 0x000C,
//	MESSAGE_FAMILLY		= 0x000D,
//	MESSAGE_CORPS		= 0x000E,
//};
//

// �ͻ���������Ϣ
class CClientInfo
{
public:
	CClientInfo()
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	};

	~CClientInfo() {};

	int Initialize()
	{
		mUin = 0;
		mClientAddr = 0;
		mClientPort = 0;
		mSockTime = 0;
		mSockIndex = 0;
		mNetSpeed = 0;
		//mVer = 0;
		//memset( mKey, 0, sizeof(mKey) );
		mFlag = 0;
		m_tLastActiveTime = 0;
		return 0;
	}

	int Resume() {return 0;}

	enum  { CRYPT_KEY_LENGTH = 16};

	unsigned int			mUin;					//�ʺ�ID
	unsigned int 			mClientAddr;			//�ͻ��˵������ַ
	unsigned short 			mClientPort;			//�ͻ��˵Ķ˿ں�
	unsigned int 			mSockTime;				//�ͻ�������ʱ��
	unsigned short 			mSockIndex;				//�ͻ��˵Ķ˿ں�
	int 					mNetSpeed;				//�������
	//short 					mVer;					//C-SЭ��汾��
	//unsigned char 			mKey[CRYPT_KEY_LENGTH];	//����ʹ�õ�Key
	char 					mFlag;					//�ͻ���״̬��0 - δ���ӣ�1 - ���ߣ� 2 - ����
	time_t					m_tLastActiveTime;		// ����Ծʱ��
};


