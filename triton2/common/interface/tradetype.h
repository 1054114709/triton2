#pragma once

#include "protype.h"

#define TRADE_COUNT_MAX			6			// ������Ʒ�б����ֵ	
#define TRADE_LENGTH_MAX		10			// ��Ч����
#define SERVER_TRADEUNIT_MAX	1000		// ��������������ʱ���֧�ֵĽ�����Ϊ
#define INVITE_UPPER_LIMIT		20			// ������������

#define TRADE_MONEY_MAX			900000000	// ����׽��
#define TRADE_MONEY_MIN			0			// ��С���׽��

#define TRADE_NONESTATE			-1			// ��״̬

// ������Ϊ����
enum TRADE_TYPE
{
	emAddGoods	= 0x1001,		// �����Ʒ
	emDelGoods,					// �Ƴ���Ʒ
	emUpdateMoney,				// ���½��׽��
};

// ��ҽ���״̬
enum TRADE_STATE
{
	emInTrade	= 0x2001,		// ������
	emOffTrade,					// �޽���,���׽���
	emLockTrade,				// ��������,�ȴ�ȷ��
	emWaitTrade,				// ȷ�Ͻ���
	emNoneState,				// ��״̬
	emUnlockTrade,			//����״̬
};

// ������
enum TRADE_OPERATE_CODE
{
	emTradeAgree = 0x3001 ,		// ͬ��
	emTradeRefuse,				// �ܾ�
	emTradeIgnore,				// ����
};

// �رս�������
enum TRADE_CLOST_TYPE
{
	emNormalFinish = 0x4001,	// ��������
	emInterrupt,				// �쳣�ж�
	emCancelTrade,				// ȡ������
};

// 
enum TRADE_PROCESS_CODE
{
	emCanDoTrade = 0x5001,		// ���Խ���
	emNeedTarget,				// �Դ��Է�ȷ��
};

struct _TRADE_GOODS_
{
	unsigned int mPackIndex;
	unsigned int mCount;
	char mGoodsBuf[ ITEMOBJ_BUFFLEN ];
};


