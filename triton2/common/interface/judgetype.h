#pragma once

// add need data struct

#define JUDGE_SCORE_MAX		500

#define JUDGE_COOL_TIME		300	// ��
#define JUDGE_BASE_LEVEL	30	// �����ۼ���

#define JUDGE_OTHER_MAX		20	// ������������
#define RECORD_EXIST		1	// 

#define ERR_NEED_NOTIFY(x) ( x < -47000 ? true : false )	

// ��������
enum JudgeType
{
	Judge_Favor = 0,	// �ø�
	Judge_Bad,			// ���
};

// ��ѯ����
enum JudgeQueryType
{
	Judge_Query_Time = 0,	// ʱ������
	Judge_Query_Value,		// ֵ����
	Judge_Query_Sum,		// Sum
	Judge_Query_Rec_Cnt,	// �յ����۸���
	Judge_Query_Rec_Max,	// �յ����������ֵ
	Judge_Query_Rec_Sum,	// �յ�����ֵ
};

// ��Ϊ����
enum JudgeActionType
{
	Judge_Other = 0,	// ������
	Judge_Rec,			// �յ���
};