

// ������ٶ�����/������
option optimize_for = SPEED;

//Proxy����ķ�����ʵ������
enum EMProxyEntityType
{
	CET_PROXYSERVER	= 1; // ת��������
	CET_GAMESERVER	= 2; // ��Ϸ������� ( ���������������������� ), �����ͷ�����������
	CET_DBSERVER	= 3; // ���ݿ��������
	CET_OTHERSERVER	= 4; // ����������� ( ��¼������:1 ���ط�����:2 ��־������:3 )
	CET_GLOBALPROXY	= 6; // ȫ�ִ��������	
	CET_DUNGEON		= 7; // ȫ�ָ���������
};

enum EMProxyCmd 
{
	CMD_NULL		= 0;
	CMD_REGKEY		= 1;
	CMD_START		= 2;  
	CMD_REGSERVER   = 3;  //������ע��
	CMD_KEEPALIVE   = 4;  //����
};

enum EMTransType
{
	TRANS_P2P		= 0; //�㵽��
	TRANS_P2G		= 2; //�㵽��
	TRANS_BROADCAST = 3; //ͬ�͹㲥
	TRANS_BYKEY		= 4; //���ݹؼ���ת��
};

// ����������ת������ͨѶ����Ϣͷ
message CProxyHead
{
    optional uint32			TotalLength		= 1;	// ��Ϣ�ĳ��� 
    optional uint32			SrcFE			= 2;	// ���������͵ķ���������
    optional uint32			SrcID			= 3;	// ���Ǹ�����������
    optional uint32			DstFE			= 4;	// ���������͵ķ�����
    optional EMTransType	TransferType	= 5;
    optional uint32			DstID			= 6;	// ���ĸ�������
    optional uint32			Uin				= 7;	// δ��
    optional EMProxyCmd		OpFlag			= 8;	// ��������
    optional uint32			OptLength		= 9 [default = 0];
    optional bytes			Option			= 10;
	optional uint32			SrcGameID		= 11;	// Դ�����������GameID
	optional uint32			DesGameID		= 12;	
};
