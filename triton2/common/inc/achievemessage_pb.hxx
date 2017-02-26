// ������ٶ�����/������
option optimize_for = SPEED;

/*
 *	�ɾ�ϵͳ��Ϣ
 */

enum AchieveMessageID // MESSAGE_ACHIEVE = 0x5000
{
	ID_C2S_REQUEST_REPORTACHIEVE		= 0x5001;	// �ϱ��ɾ�
	ID_S2C_RESPONSE_REPORTACHIEVE		= 0x5002;

	ID_C2S_REQUEST_GETSINGLEACHIEVE		= 0x5003;	// ��ȡ�����ɾ�
	ID_S2C_RESPONSE_GETSINGLEACHIEVE	= 0x5004;

	ID_C2S_REQUEST_GETALLACHIEVE		= 0x5005;	// ��ȡ���гɾ�
	ID_S2C_RESPONSE_GETALLACHIEVE		= 0x5006;

	ID_S2C_NOTIFY_ACHIEVENOTICE			= 0x5007;	// �ɾͻ��֪ͨ

	ID_C2S_REQUEST_GETALLHONOR			= 0x5008;
	ID_S2C_RESPONSE_GETALLHONOR			= 0x5009;
	ID_S2C_NOTIFY_HONORFINSH			= 0x500A;

	ID_C2S_REQUEST_GETSTAGEBONUS		= 0x500B;	// ��ȡ�׶ν���
	ID_S2C_RESPONSE_GETSTAGEBONUS		= 0x500C;	
};

// �ϱ��ɾ�����
message CMessageAchieveReportRequest
{
	optional uint32	AchieveID	= 1;	// �ɾ�ID
	optional uint32	Key			= 2;	// 	
	optional uint32	Value		= 3;	// ��չ��
};

// �ϱ��ɾͻظ�
message CMessageAchieveReportResponse
{
	optional uint32	RtnCode		= 1;
};

// �ɾͽṹ
message PBAchieve
{
	optional uint32	AchieveID	= 1;
	optional uint32	Time		= 2;	// ���ʱ��
	optional uint32	Status		= 3;	// �Ƿ����
	optional uint32	RootType	= 4;	// ����
	repeated PBAchieveParam Param		= 5;	// �����б�
};

message PBAchieveBuffer
{
	repeated PBAchieve  Achieve = 1;
};

// ��ȡ�ɾ�����
message CMessageAchieveGetSingleRequest
{
	optional uint32	AchieveID	= 1;
};

message CMessageAchieveGetSingleResponse
{
	optional PBAchieve Achieve	= 1;
};

// ��ȡ���гɾ�
message CMessageAchieveGetAllRequest
{
	optional uint32		IsOpen		= 1;	// �Ƿ�򿪽���
};

message CMessageAchieveGetAllResponse
{
	optional uint32		TotalPoint	= 1;	// �ܳɾ͵���
	optional PBAchieveBuffer AchieveBuffer = 2;
	optional uint32		Stage		= 3;	// ��ȡ���Ľ׶�
	optional uint32		IsOpen		= 4;	// �Ƿ�򿪽���
};

// �ɾͻ�ȡ֪ͨ
message CMessageAchieveFinishNotice
{
	optional PBAchieve	Achieve	= 1;
	optional uint32		TotalPoint	= 2;	// �ܳɾ͵���
	optional uint32		CharID	= 3;
	optional string		Name	= 4;
};

message PBAchieveParam
{
	optional uint32	Key		= 1;
	optional uint32	Value	= 2;
};

// db pb struct
message PBDBAchieve
{
	optional uint32	AchieveID	= 1;
	optional uint32	Time		= 2;	// ���ʱ��
	optional uint32	Status		= 3;	// �Ƿ����
	optional uint32	RootType	= 4;	// ����
	repeated PBAchieveParam Param = 5;	// �����б�
};

message PBDBAchieveBuffer
{
	repeated PBDBAchieve Achieve = 1;
	repeated PBHonorData HonorData = 2;
	optional uint32		CharID		= 3;
	optional uint32		TotalPoint	= 4;
	optional uint32		Stage		= 5;
};

// ������й�������
message CMessageGetAllHonorRequest
{

};

message PBHonorData
{
	optional uint32	MapID	= 1;	// ������ͼID
	optional uint32	Time	= 2;	// ���ʱ��
	optional uint32	Param	= 3;	// Ԥ������
};

message CMessageGetAllHonorResponse
{
	repeated PBHonorData HonorData = 1;
};

// ��ɹ���ʱ��֪ͨ
message CMessageHonorFinishNotice
{
	optional PBHonorData HonorData = 1;
};

message CMessageGetStageBonusRequest
{
};

message CMessageGetStageBonusResponse
{
	optional uint32	Result	= 1;
	optional uint32	Stage	= 2;	// ��ȡ�󵽴�Ľ׶�
};