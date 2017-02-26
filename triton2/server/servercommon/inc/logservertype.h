#ifndef LOGSERVERTYPE_H
#define LOGSERVERTYPE_H

#define MAX_TASK_ITEM_NUM	5	// �����������Ʒ��������

#define MAX_SQL_LENGTH	1024*30*100
#define MAX_TABLENAME_LENGTH	1024

// �����¼����ͽ��зֱ�
enum emEventType
{
	EM_EVENTTYPE_NONE				= 0,	// �¼�����
	EM_EVENTTYPE_OBTAINEXP,					// ��þ����¼�
	EM_EVENTTYPE_TASKOVER,					// ��������¼�
	EM_EVENTTYPE_PLAYERDIE,					// ��������¼�
	EM_EVENTTYPE_ENTERFB,					// ���븱���¼�
	EM_EVENTTYPE_EXITFB,					// �뿪�����¼�
	EM_EVENTTYPE_OBTAINITEM,				// �����Ʒ�¼�
	EM_EVENTTYPE_OBTAINMONEY,				// ��ý���¼�
    EM_EVENTTYPE_OBTAINBUFF,                // ���BUFF�¼�
};

// ÿ�����һ���¼�,��Ҫ��д��Ӧ��HANDLE�Ų��ں������ע��
// ��Ҫ���HANDLE,��Ҫ�޸�log�������ϵ���Ӧ��

#define CONTAINER_ITEM_NUM		16		// ������־�ֱ�����
#define MAX_HANDLE_NUM			8		// �����־�߳���

enum emEventHandle
{
	EIHANDLE_ONE		= 0,	// 1��handle (��¼��þ���)
	EIHANDLE_TWO,				// 2��handle (�������)
	EIHANDLE_THREE,				// 3��handle (��ý��)
	EIHANDLE_FOUR,				// 4��handle (�����Ʒ)
	EIHANDLE_FIVE,				// 5��handle (���븱��)
	EIHANDLE_SIX,				// 6��handle (�˳�����)
	EIHANDLE_SEVEN,				// 7��handle (�������)
	EIHANDLE_EIGHT,				// 8��handle
};


/*
 * ʱ�䣬�ص�Ӧ����Ĭ�Ͼ��еģ���˲�������Ϊ�����м�¼
 * ģʽ����ã�ʧȥ)  ��Ϊ����ö�٣� ��Ϊ����(3����ÿ����Ϊ��һ����������Ҫ������)
 * �����ӵ���Ϊ���붨�壬�������ݿⲻ�ɹ���
 *
 */



enum emExchangeOperate
{
	EXCHANGE_ACCOUNT_ADD			= 0,	// �������ʺ����
	EXCHANGE_ACCOUNT_DEC,					// �������ʺż���
	EXCHANGE_TRADE_BUY_ADD,					// �����������
	EXCHANGE_TRADE_BUY_DEC,					// ������ȡ����
	EXCHANGE_TRADE_SELL_ADD,				// �������
	EXCHANGE_TRADE_SELL_DEC,				// ȡ������
	EXCHANGE_TRADE_LOG_BUY,					// �򵥳ɽ�
	EXCHANGE_TRADE_LOG_SELL,				// �����ɽ�
};


#endif
