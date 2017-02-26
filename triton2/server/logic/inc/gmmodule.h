#pragma once

#include "gmmessage_pb.hxx.pb.h"
#include "servercore.h"
#include "servertool.h"
#include "errcode.h"
#include "entity.h"

class CMapObject;


// ********************************************************************** //
// CGMModule
// ********************************************************************** //
//
//
#define ACTIVITY_ITEM_LIMIT 12
#define INVALID_ITEM_ID -1

class CGMModule : public CLogicModule, public CSingleton< CGMModule >
{
  private:
	enum em_gm_right
	{
		em_priv_none				= 0x00000000,	// ��Чֵ
		em_priv_is_gm				= 0x10000000,	//GM
		em_priv_kickoff_player		= 0x00000001,	//����
		em_priv_shutoff_player		= 0x00000002, 	//����
		em_priv_cancel_shutoff		= 0x00000004,	//�����
		em_priv_freeze_player		= 0x00000008,	//�����ʺ�
		em_priv_unfreezen_player	= 0x00000010,	//�ⶳ�ʺ�
		em_priv_fly					= 0x00000020,	//��
		em_priv_insert_item			= 0x00000040,	//������Ʒ
		em_priv_insert_money		= 0x00000080,	//�����Ǯ
		em_priv_move				= 0x00000100,	//����
		em_priv_hide				= 0x00000200,	// ����/����
		em_priv_fb					= 0x00000400,
		em_priv_gate				= 0x00000800,	// �޸�Gate����		
		em_priv_clear_safe_pwd		= 0x00001000,	// ���ð�ȫ��
		em_priv_create_npc			= 0x00002000,	// ˢnpc
		em_priv_destroy_npc			= 0x00004000,	// ����npc
		em_priv_reload_map			= 0x00008000,	// ���¼��ص�ͼ
		em_priv_rank_remove			= 0x00010000,
		em_priv_show_npc_info		= 0x00020000,	// ��ʾʵ�����Ϣ
		em_priv_change_repetion		= 0x00040000,	// �޸ĸ����������
		em_priv_clean_all_repetion	= 0x00080000,
		em_priv_callback_corpsmoney = 0x00100000,	
		em_priv_battle				= 0x00200000,	// ս��Ȩ�ޣ���������ս����������ս�ȣ�
		em_priv_tel					= 0x00400000,
		em_priv_war					= 0x00800000,	// �޸Ĺ�սʱ��
		em_priv_change_camp         = 0x01000000,   // ת��Ӫ

	};

	enum em_user_right
	{
		em_account_trusted			= 0x00000002,	// ���й�״̬
	};

	inline bool HasRight(CEntityPlayer* tpPlayer, enum em_gm_right right)
	{
		return (tpPlayer != NULL && IsGm(tpPlayer->GetGmStatus()) && ((tpPlayer->GetGmStatus() & right) == (uint32_t) right));
	}


	//typedef std::pair<lk::CString32, int> CPairItemCount;
	class CPairItemCount
	{
		public:
			lk::CString32 ItemCode;
			int ItemID;
			int ItemNum;

			CPairItemCount(const char* szCode, int id, int num)
			{
				ItemCode = szCode; 
				ItemID = id;
				ItemNum = num;
			}

			CPairItemCount() {}
	};

	typedef lk::vector<CPairItemCount, ACTIVITY_ITEM_LIMIT > CActItemList;
	typedef lk::hash_map<int , CActItemList, SERVER_CAP_PLAYER>  CActItemBuffer; 

	CActItemBuffer mActItemBuffer;

public:
	static char			sModuleName[ NAME_LENGTH ];

	CGMModule() : CLogicModule( sModuleName )
	{ 
		if( CObj::msCreateMode )
		{
			mActItemBuffer.initailize();
		}
	}
	
	static unsigned int CountSize();

	// ly�ƶ���public ��Ϊ�ⲿҪ�ж��Ƿ�GM
	inline bool IsGm(unsigned int gm_status) 
	{
		return ((gm_status & em_priv_is_gm) == em_priv_is_gm );
	}

	inline bool IsGmTrusted(unsigned int gm_status)
	{
		return (!IsGm(gm_status)) && ((gm_status & em_account_trusted) == em_account_trusted); 
	}

private:
public:
	void OnGmMessageKickRoleCmd(CMessage* tpMessage);
	void OnGmMessageMoveRoleCmd(CMessage* tpMessage);
	void OnGmMessageShutUpCmd(CMessage* tpMessage);
	void OnGmMessageCancelShutUpCmd(CMessage* tpMessage);
	void OnGmMessageEndTaskCmd(CMessage* tpMessage);
	void OnGmMessageTrusteeStorageCmd(CMessage* tpMessage);
	void OnGmMessageUnTrusteeStorageCmd(CMessage* tpMessage);

	void OnGmMessageChangeMoneyCmd(CMessage* tpMessage);
	void OnGmMessageChangeExpCmd(CMessage* tpMessage);
	void OnGmMessageChangeItemCmd(CMessage* tpMessage);
	void OnGmMessageRoleLocationCmd(CMessage* tpMessage);
	void OnGmMessageTaskInfoCmd(CMessage* tpMessage);

	void OnMessageFangChenMiResponse(CMessage* tpMessage);

	bool GetOneValidPos4Player(CMapObject* pMap, CWTPoint here, CWTPoint* pwhere);

	EFcmStatus CheckPlayerFcmStatus(int nRemainSeconds);
	void OnMessageFCMPlayerListNotify(CMessage* tpMessage);
	void OnMessageFCMPlayerResetNotify(CMessage* tpMessage);

	// 2.4 ����
	void OnGmMessageRoleDetailCmd(CMessage* tpMessage);
	void OnGmMessageRoleEquipmentCmd(CMessage* tpMessage);
	void OnGmMessageRolePackInfoCmd(CMessage* tpMessage);
	void OnGmMessageRoleItemInPackCmd(CMessage* tpMessage);
	void OnGmMessageRoleSkillInfoCmd(CMessage* tpMessage);
	void OnGmMessageRoleSkillDetailCmd(CMessage* tpMessage);
	void OnGmMessagePostBulletinCmd(CMessage* tpMessage);
	void OnGmMessageUserStorageInfoCmd(CMessage* tpMessage);

	// ������ҵ�����ϵ
	void OnGmMessageUserSocialInfoCmd(CMessage* tpMessage);

	// ȡ����Ҳ���������Ʒ�б�
	void OnGmMessageUserItemListResponse(CMessage* tpMessage);

	// �����ȡ��Ʒ��Ӧ
	void OnGmMessageUserItemMinusResponse(CMessage* tpMessage);

	// ��ҵ���NPC��Ӧ
	void OnGmMessageActivityListResponse(CMessage* tpMessage);

	//void FillPbItem(PBItemObject* pbItem, const PBExItem& pbActivityItem);
	void OnMessageMinusActivityItem(CEntityPlayer* tpPlayer, CMessage* tpMessage);	

	// MultiExp
	void OnGmMessageMultiExpCmd(CMessage* tpMessage);

	// CanMultiExp
	void OnGmMessageCancelMultiExpCmd(CMessage* tpMessage);

	// ����ʹ��GMָ���Ӧ
	void SendUseGmCommandResult( CEntityPlayer* pPlayer, const char* pMsg );


public:
	// ����������
	virtual void OnLaunchServer();

	// �˳�������
	virtual void OnExitServer();

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );

	// ��������
	virtual int OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName ){	return SUCCESS; }

	// ·����Ϣ
	virtual void OnRouterMessage( CMessage* pMessage ){}
	
	// GM��Ϣ
	void OnGateMessage( CMessage* pMessage );

	// �ͻ��˷�����Ϣ
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����ʵ��
	virtual void OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst );

	// ����ʵ��
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode );

	// �洢����
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode ) { return true; }

	// ��������
	virtual void OnLoadConfig( ) ;

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }
};

