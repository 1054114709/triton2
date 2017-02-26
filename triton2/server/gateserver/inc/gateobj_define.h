#ifndef _GATEOBJ_DEFINE_H_
#define _GATEOBJ_DEFINE_H_
#if 0
/******************************************************************************
   ��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

******************************************************************************
  �ļ���          : sceneobj_define.h
  �汾��          : 1.0
  ����            : ZHL
  ��������        : 2008-06-26
  ����޸�        : 
  ��������        : ���峡��������������Ϸ����Ԥ��������
  �����б�        : 
  �޸���ʷ        : 
  1 ����          : 2008-06-26
    ����          : ZHL
    �޸�����      : ����
*******************************************************************************/
#endif

// ���涨�����������
#ifdef _DEBUG_
	#define PLAYER_AT_GATE_CAP	100	// ����������
	#define SCENE_AT_GATE_CAP   15		// ���عҼ�̨����
	#define MAP_AT_GATE_CAP		700		// ���عҶ��ٵ�ͼ
	#define TEAM_AT_GATE_CAP	PLAYER_AT_GATE_CAP		// �����������
	#define AGIPSESSION_CAP     100	// ͬʱ��erating�����session
	#define SERVERSESSION_CAP   1000	// ͬʱ�������ڲ�seesion
	#define ROLEGLOBALINFO_CAP	50000	// ��ҵ�����
	#define MAP_REPETION_CAP	50		// ͬʱ���ڸ�������
	#define FAMILY_CAP			80
	#define SERVER_CAP_IBTRANS  (PLAYER_AT_GATE_CAP*2)
	#define SERVER_CAP_CORPS	80
	#define ACTIVITYITEM_CAP 	(PLAYER_AT_GATE_CAP*2)
	#define LEAGUESHOP_CAP		(FAMILY_CAP*20)	
	#define	CORPS_NPC_CAP		100		//��������սNPC�������
#else
	#define PLAYER_AT_GATE_CAP	8000	// ����������
	#define SCENE_AT_GATE_CAP	25		// ���عҼ�̨����
	#define MAP_AT_GATE_CAP		1500	// ���عҶ��ٵ�ͼ
	#define TEAM_AT_GATE_CAP	2000
	#define AGIPSESSION_CAP		2000
	#define SERVERSESSION_CAP	4000
	#define ROLEGLOBALINFO_CAP	1000000	// ��ҵ�����
	#define MAP_REPETION_CAP	1000 	// ͬʱ���ڸ�������
	#define FAMILY_CAP			6000	// �������������
	#define SERVER_CAP_IBTRANS  (PLAYER_AT_GATE_CAP*2)
	#define SERVER_CAP_CORPS	3000	 
	#define ACTIVITYITEM_CAP 	(PLAYER_AT_GATE_CAP*2)
	#define LEAGUESHOP_CAP		(FAMILY_CAP*20)	
	#define	CORPS_NPC_CAP		200		//��������սNPC�������
#endif // ! _DEBUG_

// ȫ�ֶ�������
enum EGlobalObjType
{
	OBJTYPE_START = 0x01,		// start 
	OBJTYPE_PLAYER_AT_GATE,		// CGatePlayer
	OBJTYPE_SCENE_AT_GATE,		// CSceneServer
	OBJTYPE_MAP_AT_GATE,		// CSceneMap
	OBJTYPE_TEAM_AT_GATE,		// CGateTeam
	OBJTYPE_AGIPSESSION,        // CAGIPSession
	OBJTYPE_SERVERSESSION,      // CServerSession
	OBJTYPE_ROLEGLOBALINFO,		// CRoleGlobalInfo
	OBJTYPE_REPETION_MAP,
	OBJTYPE_FAMILY,				// CFamily
	OBJTYPE_IBTRANS,			// CIbTrans
	OBJTYPE_CORPS,				
	OBJTYPE_MEMBER,				// Team member
	OBJTYPE_ACTIVITYITEM,		// CActivityItem
	OBJTYPE_UNION,
	OBJTYPE_LEAGUESHOP,			// CLeagueShopInfo
	OBJTYPE_END,				// end
};

#endif
