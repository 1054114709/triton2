option optimize_for = SPEED;

enum IBSTORE_MSG_ID
{
    ID_C2S_REQUEST_LISTIBITEMS                  = 0x4801;       // �ͻ���->������ �����̳���Ʒ�б�
    ID_S2C_RESPONSE_LISTIBITEMS                 = 0x4802;       // ������->�ͻ��� �����������̳���Ʒ�б�
    ID_C2S_REQUEST_PURCHASEIBITEM               = 0x4803;       // �ͻ���->������ �����̳���Ʒ����
    ID_S2C_RESPONSE_PURCHASEIBITEM              = 0x4804;       // ������->�ͻ��� �����̳���Ʒ��Ӧ
    ID_S2C_NOTIFY_USERCHARGE                    = 0x4805;       // ��ҳ�ֵ֪ͨ
    ID_S2C_NOTIFY_IBSTOREPROMOTION		= 0x4806;	// ������Ϣ֪ͨ

	ID_C2S_GET_FUNCCONSUMES_REQUEST				= 0x4807;		// �ͻ���->������ ������ܸ����б�
	ID_S2C_GET_FUNCCONSUMES_RESPONSE			= 0x4808;		// ������->�ͻ��� ���ظ����б�

	ID_C2S_PURCHASE_FUNC_REQUEST				= 0x4809;		// �ͻ���->������ ������ ����
	ID_S2C_PURCHASE_FUNC_RESPONSE				= 0x480A;		// ������->�ͻ��� �����Ӧ
};

enum IBSTORE_FLAG
{
	EM_GOODS_RECOMMEND      = 1; // �Ƽ�
        EM_GOODS_COUNT_LIMITED  = 2; // ����                                                                      
        EM_GOODS_TIME_LIMITED   = 3; // ��ʱ                                                                      
        EM_GOODS_DISCOUNT       = 4; // �ۿ�                                                                      
        EM_GOODS_HOT            = 5; // ����                                                                      
        EM_GOODS_NEW            = 6; // ��Ʒ                                                                      
        EM_GOODS_SELL_OUT       = 7; // ����                                                                      
	EM_GOODS_INACTIVE       = 8; // �¼�                                                                      
	EM_GOODS_TIME_COUNT	= 9; // ��ʱ����
}; 

// �̳ǻ���λ������
message PBLocation
{
	optional uint32 page = 1;  // ҳ��
	optional uint32 row  = 2;  // �к�
	optional uint32 col  = 3;  // �к�
};

// ����Ԫ������
message PBIbMoney
{
	optional uint32 unit    = 1;  // �Ƽ۵�λ 3:��Ԫ�� 4: ��Ԫ��
	optional int32  value   = 2;  // ֵ
};

// �����ϵ���Ʒ����
message PBIbItemOnSale
{
	optional uint32 GoodsID       = 1;   // ��ƷID
	optional uint32 ItemID        = 2;   // ��Ʒ��ģ��ID
	optional uint32 ItemCount     = 3;   // �����ڵ���Ʒ����
	optional int32  GoodsCount    = 4;   // �̳��д���Ʒ������
	optional PBIbMoney GoodsPrice = 5;   // ��Ʒ��ԭ��
	optional PBIbMoney Discount   = 6;   // �ۿۺ�ļ۸� 
	optional int32  ExpiryTime    = 7;   // �˼۸�Ľ���ʱ��
	optional int32  ColdTime      = 8;   // ����ʱ�� -- ����
	optional int32  ElapsedTime   = 9;   // �Ѿ����ĵ�CDʱ��  -- ����
	optional uint32 Active        = 10;  // ��Ʒ�Ƿ���Ч	
	optional string GoodsName     = 11;  // Ĭ����ʾ��������Ϣ�еģ������Ϣû�д����ʹ��ItemID��ģ���е�����
	optional string GoodsDesc     = 12;  // Ĭ������ʹ����Ϣ�еģ������Ϣ��û�д����ʹ��ItemID��ģ���е�����
	optional int32 IsPack         = 13;  // �Ƿ��ǰ�����Ʒ	-- ����
	optional int32 Flag           = 14;  // ��Ʒ��ǩ
	optional int32 LimitPerChar   = 15;  // ÿ������ƹ��������
	optional int32 LimitType      = 16;  // ÿ������ƹ��������
};

// ��Ҵ��̳ǽ�������
message CMessageListIbItemsRequest
{
	optional uint32 Version  =  1;   // �汾��
	optional uint32 IsOpenRMBShopUI = 2; // �Ƿ��RMB UI �ͻ�������
};

// ��Ҵ��̳ǽ����Ӧ
message CMessageListIbItemsResponse
{
	optional int32  Error           = 1;  // �Ƿ�ɹ� 0: �ɹ� 1��ͬ�ͻ��˰汾һ��
	optional uint32 Version         = 2;  // �̳ǰ汾��
	repeated PBIbMoney RemainMoneys = 3;  // ����ʺ���Ŀǰ�Ľ�Ǯ�б�
	repeated PBIbItemOnSale Goods   = 4;  // �̳������۵���Ʒ�б�
    	repeated PBIbStore IbStore      = 5;  // ����, Ŀǰֻ���������ݽ���Ԫ������
	optional string Bulletin	= 6;  // �̳ǹ���
	repeated PBIbSubTab FocusTab	= 7;  // ������Ʒ�б�
	optional uint32 IsOpenRMBShopUI = 8; // �Ƿ��RMB UI �ͻ�������
};

// ��ҹ�����Ʒ����
message CMessagePurchaseIbItemRequest
{
	optional uint32 GoodsID      = 1;  //  ���������ƷID
	optional uint32 GoodsCount   = 2;  //  ���������Ʒ����
};

// ��ҹ�����Ʒ��Ӧ
message CMessagePurchaseIbItemResponse
{
	optional int32 Error          = 1;  // �����Ƿ�ɹ���־. 0�ɹ�����������ʧ��
	optional uint32 RoleID        = 2;  // ���׵����ID
	optional int32  TransID       = 3;  // �˴ν��׵Ľ���ID
	optional uint32 GoodsID       = 4;  // �������ƷID
	optional uint32 GoodsCount    = 5;  // �������Ʒ����
	optional uint32 ItemID        = 6;  // �������Ʒ��ID
	optional uint32 ItemCount     = 7;  // ����Ʒ�İ�������Ʒ����
	optional PBIbMoney GoodsCost  = 8;  // ���֧���˶���
	optional PBIbMoney Remained   = 9;  // ʣ���Ǯ��
};

// ��ҽ���֪ͨ, ����������Ϣ���ͻ��˲�ʹ��
message CMessageRoleIbTransNotify
{
	optional int32 TransID    = 1;  // ����ID
	optional int32 Successful = 2;  // �����Ƿ�ɹ�
};

// ����ҳ�� 
message PBIbSubTab
{
	optional uint32 SubTabID   = 1;  // ID  
	optional string SubTabName = 2;  // ������������
	repeated uint32 GoodsID    = 3;  // ��ƷID
};

// ����ҳ��
message PBIbTab
{
	optional uint32 TabID      = 1;  // ID    
	optional string TabName    = 2;  // ������������ 
	repeated PBIbSubTab SubTab = 3;  // PBIbSubTabҳ��
};

// һ��ҳ��
message PBIbStore
{
    optional uint32 PageID   = 1;  // ID
    optional string PageName = 2;  // һ����������
    repeated PBIbTab Tab     = 3;  // PBIbTabҳ��
};

// ��ֵ��֪ͨ�����Ϣ
message CMessageUserChargeNotice
{
    optional int64 DetailID = 1;    // ��ֵ��ˮ
    optional int32 UserID = 2;      // �ʺ�ID
    optional int32 SubjectID = 3;   // ��������
    optional int32 Amount = 4;      // ��ֵ���
};

// ��Ʒʣ������֪ͨ
message PBPromotion
{
	optional uint32 GoodsID		= 1; 	// ��ƷID
	optional int32 RemainCount	= 2;	// ��Ʒ��ǰʣ������
	optional int32 BeginTime 	= 3;	// ������ʼʱ��
	optional int32 EndTime 		= 4;	// ��������ʱ��
	optional int32 MaxCount		= 5;	// ������������
	optional int32 ColdNum 		= 6;  	// ÿ��CD֮�����������
	optional int32 ColdTime		= 7; 	// CDʱ��
	optional int32 ElapsedTime	= 8;	// �Ѿ���ȥ��CDʱ��
};

message CMessageIbItemRemainNotice
{
	repeated PBPromotion promotion = 1;	// ������Ϣ
};

message PBConsume
{
	optional uint32	ConsumeType		= 1;	//�������� Ԫ������Ԫ������Ǯ���󶨽�Ǯ
	optional uint32 ConsumeSprice	= 2;	//���Ѽ۸�
	optional uint32 TamplateRate	= 3;	//ģ��ļ۸��� ���������Ѽ۸�
};
//���ܸ���
message PBFuncStore
{
	optional uint32 FuncID				= 1;	//����ID
	optional string FuncName			= 2;	//��������
	optional uint32 FuncUnitType		= 3;	// EFuncUnitType ��λ���� �� ��Сʱ����
	repeated PBConsume Consume			= 4;	//�������ͣ��۸� 
	optional uint32	FuncShow			= 5;	// 1,��ʾ�ڽ��棬0����ʾ��	
	optional uint32 DefaultConsume		= 6;	// Ĭ�ϵ��������� 
	optional uint32 FuncUnit			= 7;	// ��λ
	optional uint32 FuncCountLimit		= 8;	// ��������/��������
};

message CMessageGetFuncConsumesRequest
{
};
message CMessageGetFuncConsumesResponse
{
	optional int32	Error			= 1;	// �Ƿ�ɹ� 0: �ɹ� ������ʧ��
	repeated PBFuncStore FuncStore	= 2;	// ������
};

message CMessagePurchaseFuncRequest
{
	optional uint32 FuncID			= 1;	// ����ID
	optional uint32 FuncCount		= 2;	// ��������
	optional uint32 ConsumeType		= 3;	// �������� ,  BIND_MONEY 1; UNBIND_MONEY  2;  LINEKONG_MONEY   3; SILVER_YUANBAO   4; GOLDEN_YUANBAO   5
	optional uint32 ExtraData1		= 4;	// ����Ĳ���  ���ڰ�����ExtraData1 ��index ����λ��;  
	optional uint32	ExtraData2		= 5;	// ExtraData2 ������ESlotType
};

message CMessagePurchaseFuncResponse
{
	optional int32  Error			= 1;	// �Ƿ�ɹ� 0�ɹ�������ʧ��
	optional uint32 FuncID			= 2;	// ����ID
	optional uint32 FuncCount		= 3;	// ��������
	optional uint32 ConsumeType		= 4;	// ���ѵ����� BIND_MONEY 1; UNBIND_MONEY  2; SILVER_YUANBAO   4; GOLDEN_YUANBAO   5
	optional uint32 FuncsCost		= 5;    // ���֧���˶���
	optional uint32 ExtraData1		= 6;	// ������� ���ڰ��� ExtraData1: index ����λ��
	optional uint32 ExtraData2		= 7;	//				���� ExtraData2: ����ESlotType
};
