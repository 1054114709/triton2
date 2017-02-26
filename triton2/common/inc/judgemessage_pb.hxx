// ������ٶ�����/������
option optimize_for = SPEED;


enum JudgeMessageID // MESSAGE_JUDGE = 0x4C00
{
	ID_S2C_NOTIFY_OPENJUDGE				= 0x4C01;	// ֪ͨ�ͻ�������ϵͳ����
	ID_S2C_NOTIFY_CLOSEJUDGE			= 0x4C02;	// ֪ͨ�ͻ�������ϵͳ�ر�
	
	ID_C2S_REQUEST_MODIFYJUDGESINGLE	= 0x4C03;	// �����������
	ID_S2C_RESPONSE_MODIFYJUDGESINGLE	= 0x4C04;	// ������ۻظ�
	ID_C2S_REQUEST_MODIFYJUDGELIST		= 0x4C05;	// �����޸ĺøС��������
	ID_S2C_RESPONSE_MODIFYJUDGELIST		= 0x4C06;	// �����޸ĺøС���лظ�
	ID_S2C_NOTIFY_MODIFYJUDGE			= 0x4C07;	// �޸ĺøС����֪ͨ

	ID_C2S_REQUEST_QUERYJUDGELIST		= 0x4C08;	// ��ѯ�øС�����б�����
	ID_S2C_RESPONSE_QUERYJUDGELIST		= 0x4C09;	// ��ѯ�øС�����б�ظ�

	ID_S2C_NOTIFY_JUDGEMAX				= 0x4C0A;	// �øС�������޸���

	ID_C2S_REQUEST_QUERYJUDGE			= 0x4C0B;	// ��ѯ������¼
	ID_S2C_RESPONSE_QUERYJUDGE			= 0x4C0C;
};

// ����ϵͳ����֪ͨ
message CMessageOpenJudgeNotice
{
	optional uint32 Type	= 1;	// �øС����
	optional string Name	= 2;	// ���� name
	optional uint32	CharID	= 3;	// ���� charid; 
};

// ����ϵͳ�ر�֪ͨ
message CMessageCloseJudgeNotice
{
	optional uint32 Type	= 1;	// �øС����
	optional string Name	= 2;	// ���� name
	optional uint32	CharID	= 3;	// ���� charid; 
};

// �����������
message CMessageModifySingleJudgeRequest
{
	optional uint32	Type	= 1;	// �øС����
	optional uint32	SrcCharID = 2;	// ������ charid
	optional string DesName	= 3;	// �Է� name
	optional uint32	Value	= 4;	// value
};

// ������ۻظ�
message CMessageModifySingleJudgeResponse
{
	optional uint32	RtnCode = 1;
	optional uint32	Type	= 2;	// �øС����
	optional string DesName	= 3;	// �Է� name
	optional uint32	DesCharID = 4;	// �Է� charid
	optional uint32	Value	= 5;	// value
	optional uint32	Face	= 6;
	optional uint32	Sex		= 7;
};

// �޸ĺøС��������
message CMessageModifyJudgeListRequest
{
	optional uint32	Type	= 1;	// �øС����
	optional uint32	SrcCharID = 2;	// ������ charid
	repeated PBJudgeRecord Data = 3;
};

// �޸ĺøС���лظ�
message CMessageModifyJudgeListResponse
{
	optional uint32 RtnCode = 1;
	optional uint32	Type	= 2;	// �øС����
};

// �޸ĺøС����֪ͨ
message CMessageModifyJudgeNotice
{
	optional uint32	Type	= 1;	// �øС����
	optional string Name	= 2;	// ������ name
	optional uint32	CharID	= 3;	// ������ charid
	optional uint32	Value	= 4;	// value
	optional uint32	Face	= 5;
	optional uint32	Sex		= 6;
	optional uint32	IsAdd	= 7;	// �����
};

message PBJudgeRecord
{
	optional string SrcName		= 1;
	optional uint32	SrcCharID	= 2;
	optional string DesName		= 3;
	optional uint32	DesCharID	= 4;
	optional uint32	Type		= 5;
	optional uint32	Value		= 6;
	optional uint32	TimeStamp	= 7;
	optional uint32	Face		= 8;	// 
	optional uint32	Sex			= 9;	//
};

// ��ѯ�øС���������б�����
message CMessageQueryJudgeListRequest
{
	// һ�����󣬻�ȡ�Լ��������˺��յ������ۺøС�����б�;
	optional uint32	CharID	= 1;	// ������
	optional uint32	Condition = 2;	// ��ʱ�䡢��ֵ����
	optional uint32	Action = 3;		// ��Ϊ
};

// ��ѯ�øС���������б�ظ�
message CMessageQueryJudgeListResponse
{
	repeated PBJudgeRecord FavorJudgeOtherList	= 1;	// �����˺ø������б�
	repeated PBJudgeRecord BadJudgeOtherList	= 2;	// �����˶�������б�
	repeated PBJudgeRecord FavorRecJudgeList	= 3;	// �յ��ø������б�
	repeated PBJudgeRecord BadRecJudgeList		= 4;	// �յ���������б�
	
	optional uint32	FavorTotal = 5;		// �ø���ֵ
	optional uint32 BadTotal   = 6;		// �����ֵ
};

// �øС������ֵ����֪ͨ
message CMessageUpdateMaxJudgeValueNotice
{
	optional uint32	FavorTotal = 1;		// �ø���ֵ
	optional uint32 BadTotal   = 2;		// �����ֵ
}

message CMessageQuerySingleRecordRequest
{
	optional uint32	SrcCharID	= 1;
	optional uint32	DesCharID	= 2;
};

message CMessageQuerySingleRecordResponse
{
	optional PBJudgeRecord FavorRecord = 1;
	optional PBJudgeRecord BadRecord = 2;
};