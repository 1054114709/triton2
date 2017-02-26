// ������ٶ�����/������
option optimize_for = SPEED;

enum RankMessageID // MESSAGE_RANK		= 0x3C00
{
	ID_C2S_REQUEST_PLAYERRANK			= 0x3C01;	// �ͻ��������ȡ��ҵȼ�����
	ID_S2C_RESPONSE_PLAYERRANK			= 0x3C02;	// �������ظ���ҵȼ�����
};


// ��Ҹ����� �������а�����
message PBSingleRankInfo
{
	optional string CharName		 = 		1;  // ��ɫ��
	optional uint32	Rank			 = 		2;  // ����
	optional uint32 ContinuousBoard	 = 		3;  // �����ϰ� 
	optional uint32 Metier			 = 		4;  // ְҵ
	optional uint32 Country			 = 		5;  // ����
	optional uint32 ContinuousFirst	 = 		6;  // ������һ���� (�ǵ�һ��Ϊ0) 
	optional uint32 Title			 = 		7;  // �ƺ�
	optional uint32 CharID			 = 		8;  // ��ɫID
	optional uint32 RankValue		 = 		9;  // ���������������ֵ
	optional int32	RankChange		 = 		10;  // ���α仯 1=��2=�� 0=ƽ
	optional int32	RankChangeVal	 = 		11;  // ���α仯���� �����0 �������ϰ�RankChange=1or2��������
};

/************************************************************************/
/* CMessageGetPlayerRankRequest �ͻ���->������ ����������� */
/************************************************************************/
message CMessageGetPlayerRankRequest
{
	optional uint32 RankType	 = 		1;  // ���а�����
	optional uint32 RecordNum	 = 		2;  // ��¼���� 
	optional uint32 CharID		 = 		3;  // �����ߵĽ�ɫID (��������)
	optional uint32 BeginIndex	 = 		4;  // ����ʼ����( ��С:0, ��󣺰����)
};

/************************************************************************/
/* CMessageGetPlayerLevelRankResponse ������->�ͻ��� ����������еĻ�Ӧ */
/************************************************************************/
message CMessageGetPlayerRankResponse
{
	optional uint32 MyRankChange		 = 		1;  // �ҵ����� 1=��2=�� 0=ƽ
	optional uint32 RankType	         = 		2;  // ���а�����
	optional uint32 MyRankValue			 = 		3;  // �ҵ���ֵ
	repeated PBSingleRankInfo RankInfo	 = 		4;  // ���а���Ϣ
	optional uint32 CharID				 = 		5;  // ��ɫID( �������� )
	optional int32	MyRankChangeVal		 = 		6;  // ���α仯���� �����0 �������ϰ�RankChange=1or2��������
	optional uint32	MyRankIndex			 = 		7;  // �ҵ����� ��1��ʼ
};

