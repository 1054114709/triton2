#pragma once
#define MAX_WAR_PLAYER_NUM 40		// ÿ��ս�����������
#define MAX_WAR_REGINFO_NUM 1000	// ����ܹ�ע���ս����Ϣ
#define WAR_START_NUM 40			// ����ս����Ҫ������
#define MAX_WARREGINFO_NUM 10000	//  ����ע����Ϣ����

#define MAX_GLOBALSERVER_NUM 100	// ȫ�ַ�����������
#define MAX_GLOBALTELEINFO_NUM	1000 // ս������
#define MAX_WAITPLAYER_NUM 2000		 // ���ս���ȴ���ҵ�����
#define MAX_LEVLESECTION_NUM 30		 // ���ȼ���
#define MAX_OFFLINETIME 60			 // ���ɾ������ʱ��
#define MAX_WAITTIME 30				// ���븱���ĵȴ�ʱ��
#define MAX_GLOBALWAR_APPLYLEVEL 60	// ������ȼ�

#define MAX_PLAYER_INLIST	400		// ÿ���ȼ��εȴ����е��������
#define MAX_WARREGINFO_INLIST 100	// ÿ���ȼ��ο���ս�����������
#define MAX_WARNUM_CANSTART	20		// ������������ս����Ŀ
#define MAX_GLOBAL_REPETION_NUM 10	// ͬʱ������ȫ�ָ�����������
#define MAX_GLOBAL_SERVERLIST_NUM 20// �������б������
#define MAX_GAMECONFIG_NUM	 40		// ��Ϸ�����������Ϣ
#define MAX_GLOBALPLAYER_NUM 4000	// ��Ϸ�����������Ϣ
enum EObjType
{
	OBJTYPE_REGINFO = 1,
};

enum EServerType
{
	ESERVERTYPE_DUNGEON			= 0,	// ����������
	ESERVERTYPE_SCENESER		= 1,	// ��ͨ����������	
};

enum EReason_LeaveWar
{
	EREASON_LEAVEWAR_RETURNBACK	=	0,	// ��Ϊ����ԭ���������뿪ս��
	EREASON_LEAVEWAR_OFFLINE	=	1,	// ��Ϊ���߻��ߵ��߶��뿪ս��
	EREASON_LEAVEWAR_APPLYFAILED=	2,	// ����ʧ��
};

enum EReason_EndWar
{
	EREASON_ENDWAR_REPETIONEND	=	0,	// ��Ϊ��������������ս��
	EREASON_ENDWAR_BATTLEEND	=	1,	// ս������
};

enum EGlobalTeleType
{
	EGLOBALTELE_TYPE_GLOBALSERVER		 = 0,	// ���͵�ȫ�ַ�����
	EGLOBALTELE_TYPE_RETURNTOGAME		 = 1,	// ���ص�ԭ������������
	EGLOBALTELE_TYPE_RETURNTOGATE		 = 2,	// ���ص�ԭ�����ط�����
};


