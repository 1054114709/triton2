#pragma once

enum emTimerMark
{
	TIMER_SKLL_COOLDOWN				= 1, // ����CD �� ����CD
	TIMER_ENTITY_DISAPPER			= 2, // ʵ����ʧ
	TIMER_ENTTIY_REFRESH			= 3, // ʵ���Ѫ������
	TIMER_ENTITY_RELIVE				= 4, // ʵ�帴��
	TIMER_ENTITY_CLEAR				= 5, // ʵ������
	TIMER_ENTITY_PROTECT			= 6, // ���߱���
	TIMER_ENTITY_ALIVE_REFRESH		= 7, // ������ˢ��
	TIMER_DIPLOID_TIME				= 8, // ˫��ʱ��
	TIMER_REDSTONE_PROTECT			= 9, // �ڵ�����ʱ��
	TIMER_REDSTONE_CLEAR			= 10, // �ڵ���ʧ
	TIMER_REDSTONE_EXPMAGIC			= 11, // �ڵ����� 	
	TIMER_ANSWERSTATUS_TOTALTIMEEND = 12, // ������Ŀ�Ĵ���ʱ�䵽
	TIMER_ANSWERSTATUS_SINGLETIMEEND= 13, // һ����Ŀ�Ĵ���ʱ�䵽
	TIMER_REDSTONE_PRECESSTIMEOUT   = 14, // �ͻ��˶��볬ʱ
	//TIMER_KILLNPC_WITHHIDE_TIMEOUT  = 15, // NPC��ʧʱ�䵽 Ҫ������ �ٸɵ�
	TIMER_ASSIGNMENT				= 16, // Character��ʱ����
	TIMER_YELLOWNAME				= 17,	// ����
	TIMER_ITEMCHANGE				= 18,   // ��Ʒ�仯(eg.�����ɸ��õ�����)
	TIMER_NOTIFYREFRESH_TEN			= 19,	// ��ǰ10����֪ͨˢ��
	TIMER_NOTIFYREFRESH_FIVE		= 20,	// ��ǰ5����֪ͨˢ��
	TIMER_CREATEOGRE_TEN			= 21,	// 10���Ӻ�ˢ��
	TIMER_MAGICWEAPON_INCMP			= 22,	// �����Զ��ָ�MP
	TIMER_MAGICWEAPON_DECHP			= 23,	// �����Զ��ۼ�HP
	TIMER_FIREBATTLE				= 24,	// ս������
	TIMER_TASKTIMELIMIT				= 25,	// ��ʱ����
	TIMER_STARTCORPSBATTLE			= 26,	// ��ʼ����ս
	TIMER_CDGROUP					= 27,	// CD�� (para��ʾcd������ )
	TIMER_BUFF_FUNCTION				= 28,	// buff����
	TIMER_REPETION					= 29,	// repetion out
	TIMER_REPETION_CLEAR			= 30,	// repetion clear time out
	TIMER_ITEM_DESTROY				= 31,	// ��Ʒ���ټ�ʱ��
	TIMER_NATION_PROTECT			= 32,	// �����Ǳ���ʱ�䵽ʱ
	TIMER_WEDDING					= 33,	// �����ʱ��
	TIMER_WEDDINGNOTIFY				= 34,	// ����֪ͨ��ʱ��
	TIMER_MARRIAGEAPPLY				= 35,	// ����֪ͨ��ʱ��
	TIMER_WEDDINGONSTREET			= 36,	// �������м�ʱ��	
	
	TIMER_HYDRANGEATHROW			= 37,	// ����������׳�ʱ��
	TIMER_HYDRANGEAHOLD				= 38,	// ռ�������ʱ���ʱ��
	TIMER_HYDRANGEAGRAB				= 39,	// ���������ʱ���ʱ��										
	TIMER_HYDRANGEAACTIVITY			= 40,	// �������׵�ʱ���ʱ��
	TIMER_HYDRANGEASUGAR			= 41,	// �������׵ĵ�ϲ�Ǽ�ʱ��
	TIMER_TITLE_DISAPPEAR			= 42,	// �ƺż�ʱ��
	TIMER_OGREACTIVITY_TIMEEND		= 43,	// ������ʱ��
	TIMER_QUESTIONVERIFY			= 44,	// ������֤�ļ�ʱ��
	TIMER_REPETIONQUESTION			= 45,	// ������֤�ļ�ʱ��
	TIMER_KICKOUTBYVERIFY			= 46,	// ��Ϊ������֤���߳�
	TIMER_REPTIONVERIFYTIME			= 47,	// ���븱�����ý��и���������֤
    TIMER_STOREBOXRELIVE            = 48,   // ҡǮ������临��
	TIMER_CAMPKICKVOTETIME          = 49,   // ս�����˵ĳ�ʱʱ��
};


// �˶�����TIMER_ASSIGNMENT��, ��������TIMER_ASSIGNMENT�Ĳ�ͬ��������
enum
{
	TIMER_ASSIGNMENT_REPETION		= 1,
};


// ��timer�������ʱ��
#define SEC_TIMER_ALLOW_MISTAKE 10
