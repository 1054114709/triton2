import "coremessage_pb.hxx";
import "property_pb.hxx";

// ������ٶ�����/������
option optimize_for = SPEED;

enum StallMessageID{
	ID_C2S_REQUEST_OPENSTALL		= 0x2800;		// ��̯λ
	ID_S2C_RESPONSE_OPENSTALL		= 0x2801;	
	ID_C2S_REQUEST_READPROCESS		= 0x2802;		// ���ȶ�ȡ
	ID_S2C_NOTIFY_STARTSTALL		= 0x2803;		// ��ʼ��̯��code : ���԰�̯�� ��̯ʧ��
	ID_C2S_REQUEST_UPDATEGOODS		= 0x2804;		// ����̯λ��Ʒ
	ID_S2C_RESPONSE_UPDATEGOODS		= 0x2805;		
	ID_C2S_REQUEST_UPDATEPRICE		= 0x2806;		// ����̯λ�۸�
	ID_S2C_RESPONSE_UPDATEPRICE		= 0x2807;
	ID_C2S_REQUEST_CLICKSTALL		= 0x2809;		// ��ҵ��̯λ
	ID_S2C_RESPONSE_CLICKSTALL		= 0x280A;	
	ID_C2S_REQUEST_BUYGOODS			= 0x280B;		// ��ҹ���
	ID_S2C_RESPONSE_BUYGOODS		= 0x280C;
	ID_C2S_REQUEST_CLOSESTALL		= 0x280D;		// ��̯
	ID_S2C_RESPONSE_CLOSESTALL		= 0x280E;
	ID_C2S_REQUEST_CLOSEDIALOG		= 0x280F;		// �ر�̯λ����(�۲���)
	ID_C2S_REQUEST_UPDATETEXT		= 0x2810;		// �޸����֣���桢̯��
	ID_S2C_RESPONSE_UPDATETEXT		= 0x2811;

	ID_C2S_REQUEST_STALLRECORD		= 0x2812;
	ID_S2C_RESPONSE_STALLRECORD		= 0x2813;

	ID_C2S_REQUEST_CLEANRECORD		= 0x2814;
	ID_S2C_RESPONSE_CLEANRECORD		= 0x2815;
};


//***********************************************
// CMessageOpenStallRequest
//***********************************************

message CMessageOpenStallRequest
{
	optional string StallName  = 		1; 	// ̯��
	optional string AdContent  = 		2; 	// �������
	optional int32 StallType   =        3;  //���Ӱ�̯���� 0:�����֣�1����2��Ԫ��
};

//***********************************************
// CMessageOpenStallResponse
//***********************************************

message CMessageOpenStallResponse
{
	optional uint32		EntityID	= 		1; 	// ����ʵ��ID
	optional int32		ErrorCode	=		2;	// ������; 0-�ɹ�; !0-��������
};

//***********************************************
// CMessageProcessReadResult
// �ͻ���֪ͨ��������������ȡ�ɹ����
//***********************************************

message CMessageProcessReadResult
{
	optional uint32		RtnCode	  = 		1; 	// ��ȡ�����true--�ɹ���false--ʧ��
};

//***********************************************
// CMessageStartStallResponse
// send to client
//***********************************************

message CMessageStartStallNotify
{
	optional uint32		EntityID  = 		1; 	 // ̯��entityid
	optional string		AdContent  = 		2; 	 // �������
	optional string		StallName  = 		3; 	 // ̯��
	repeated uint32		StallIndex  = 		4; 
	repeated uint32		Price  = 		5; 
	repeated PBItemObject ItemList  = 		6; 
	repeated uint32		PriceType  =		7; // ��Ʒ�۸����ͣ�1�����2���ǰ��4����Ԫ����5��Ԫ����ʵ��ֻ��2,5
	optional int32		StallType  =		8; //��̯����
};

//***********************************************
// CMessageUpdateTextRequest
// �޸�̯λ��Ϣ��������ݺ�̯λ����
//***********************************************

message CMessageUpdateTextRequest
{
	optional string		AdContent	 = 		1; 	// �������
	optional uint32		Type  = 		2; 			// ̯λ���ƣ�STALL_NAME,������ݣ�STALL_ADCONTENT
	optional string		StallName	 = 		3; 	// ̯λ����
};

//***********************************************
// CMessageUpdateTextResponse
//***********************************************

message CMessageUpdateTextResponse
{
	optional uint32		EntityID  = 		1; 	// ̯��entityid
	optional uint32		Type	 = 		2; 	// �޸����ͣ�STALL_NAME--̯λ���ƣ�STALL_ADCONTENT--�������
	optional string		AdContent  = 		3; 	// �������
	optional string		StallName  = 		4; 	// ̯λ����
};

//***********************************************
// CMessageUpdateStallRequest
// ���°�̯��Ʒ�ͽ�Ǯ
//***********************************************

message CMessageUpdateStallRequest
{
	optional uint32		ItemIndex	 = 		1; 		// �����е�index
	optional uint32		Type		 = 		2; 		// �������ͣ�STALL_PUSH--�ϼܣ�STALL_DOWN--�¼�
	optional uint32		StallIndex   = 		3; 		// ̯λ����
	optional uint32		ItemNum		 = 		4; 		// ��Ʒ����
	optional uint32		Price		 = 		5; 		// ��Ʒ�ϼܼ۸�
	optional uint32		PriceType	 =		6;		// ��Ʒ�۸����ͣ�1�����2���ǰ��4����Ԫ����5��Ԫ����ʵ��ֻ��2,5
};

//***********************************************
// CMessageUpdateStallResponse
//***********************************************

message CMessageUpdateStallResponse
{
	optional uint32		EntityID	 = 		1; 	 // ̯��entityid
	optional uint32		StallIndex	 = 		2; 	 // ̯λ����
	optional PBItemObject Item		 = 		3; 	 // ����
	optional uint32		Price		 = 		4; 
	optional uint32		Type		 = 		5; 	 // �ϼܣ��¼�(STALL_PUSH--�ϼܣ�STALL_DOWN--�¼�)
	optional uint32		PriceType	 =		6;		// ��Ʒ�۸����ͣ�1�����2���ǰ��4����Ԫ����5��Ԫ����ʵ��ֻ��2,5
};

//***********************************************
// CMessageUpdatePriceRequest
//***********************************************

message CMessageUpdatePriceRequest
{
	optional uint32		Price	 = 		1; 	// ���¼۸�
	optional uint32		StallIndex  = 		2; 	// ̯λ����
	optional uint32		PriceType  =   3;	
};

//***********************************************
// CMessageUpdatePriceResponse
//***********************************************

message CMessageUpdatePriceResponse
{
	optional uint32		Price	 = 		1; 	// �۸�
	optional uint32		StallIndex  = 		2; 	// ̯λ����
	optional uint32		EntityID  = 		3; 	// ̯��entityid
	optional uint32		PriceType  =   4;	
};

//***********************************************
// CMessageCloseStallRequest
//***********************************************

message CMessageCloseStallRequest
{
	optional uint32	IsSaved  = 		1; 		// �Ƿ񱣴��¼(true:save log, false:cancel log)
};

//***********************************************
// CMessageCloseStallResponse
//***********************************************

message CMessageCloseStallResponse
{
	optional uint32		EntityID  = 		1; 	// ̯��entityid
};

//***********************************************
// CMessageClickStallRequest
//***********************************************

message CMessageClickStallRequest
{
	optional uint32		EntityID	 = 		1; 	// ̯��ʵ��ID
};

//***********************************************
// CMessageClickStallResponse
//***********************************************

message CMessageClickStallResponse
{
	repeated PBItemObject ItemList	 = 		1; 	// ̯λ��Ʒ	
	repeated uint32		StallIndex  = 		2; 		// ̯λ����
	optional uint32		EntityID  = 		3; 		// ̯��entityid
	repeated uint32		Price   = 		4; 
	repeated uint32		PriceType =		5;
};

//***********************************************
// CMessageBuyGoodsRequest
//***********************************************

message CMessageBuyGoodsRequest
{
	optional uint32		Price  = 		1; 		// ���߼۸�
	optional uint32		EntityID  = 		2; 	// ̯��entityid
	optional uint32		Number  = 		3; 		// ��������
	optional uint32		StallIndex  = 		4; 	 // ̯λ����
	optional uint32		ItemID  = 		5; 		// ����id
	optional uint32		PriceType =		6;
};

//***********************************************
// CMessageBuyGoodsResponse
// ֪ͨ�ͻ�����Ʒ�Ѿ����ۣ�ɾ���õ���from̯λ
// �����ҿ����ڴ�̯λ��ˢ��һ��̯λ
//***********************************************

message CMessageBuyGoodsResponse
{
	optional uint32		EntityID  = 		1; 	 // ̯��entityid
	optional uint32		StallIndex  = 		2; 	 // ̯λ����
	optional uint32		Number	 = 		3; 	 // ��������
	optional uint32		BuyerEntityID = 4;	 // �����ߵ�ʵ��ID
};

//***********************************************
// CMessageCloseStallDlgRequest
// �۲��߹ر�̯λ����
//***********************************************

message CMessageCloseStallDlgRequest
{
	optional uint32		EntityID  = 		1; 	// ̯��entityid
};

message PBStallRecord
{
	optional string MasterName = 1;
	optional string BuyerName  = 2;
	optional uint32	ItemID	   = 3;
	optional uint32	Number	   = 4;
	optional uint32	Price	   = 5;
	optional uint32	Time       = 6;
	optional uint32	Action     = 7;  // ����: 0-�۳�  1-��Ϊ̯����Ǯ�������¼�
	optional uint32	Tax		   = 8;	 // ˰
	optional uint32 PriceType  = 9;  // ��������
	optional uint32	Fee		   = 10;	 // �����ѣ������Ժ����ͬʱ�շѺ�˰����������ֶε���
};

// ��ѯ̯λ���׼�¼����
message CMessageStallGetRecordRequest
{
	optional uint32	EntityID = 1;
};

// ��ѯ̯λ���׼�¼�ظ�
message CMessageStallGetRecordResponse
{
	optional uint32	EntityID = 1;
	repeated PBStallRecord Record = 2;
};

// ��ռ�¼
message CMessageStallCleanRecordRequest
{

};
 
// ��ռ�¼
message CMessageStallCleanRecordResponse
{
	optional uint32	RtnCode = 1;
};