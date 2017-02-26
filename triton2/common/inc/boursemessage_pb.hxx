/******************************************************************************
	��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

******************************************************************************
	�ļ���		: property_pb.hxx
	�汾��		: 1.0
	����		: ZHL
	��������	: 2008-09-10
	����޸�	: 
	��������	: 1 - �����н���Э��
				: [ע] PB ȫ��[Protocal Buffers -- google����Э��]
	�����б�	: 
	�޸���ʷ	: 
		1 ����	: 2010-01-29
		����	: ZHL
		�޸�����: ����
*******************************************************************************/


/****************************	�ֶ�����   ************************************
*
*	required: ���븳ֵ���ֶΣ�һ��Ҫ����˲�������������
*	optional: ���п��޵��ֶ�
*	repeated: ���ظ��ֶ�(�䳤�ֶ�)
*
******************************************************************************/


/***************************   �������� ***************************************
*	double
*	float
*	int32		Uses variable-length encoding. Inefficient for encoding negative numbers 
*				�C if your field is likely to have negative values, use sint32 instead. 
*	int64		Uses variable-length encoding. Inefficient for encoding negative numbers 
*				�C if your field is likely to have negative values, use sint64 instead. 
*	uint32		Uses variable-length encoding. 
*	uint64		Uses variable-length encoding. 
*	sint32		Uses variable-length encoding. 
*				Signed int value. These more efficiently encode negative numbers than regular int32s. 
*	sint64		Uses variable-length encoding. Signed int value.
*				These more efficiently encode negative numbers than regular int64s. 
*	fixed32		Always four bytes. More efficient than uint32 if values are often greater than 228. 
*	fixed64		Always eight bytes. More efficient than uint64 if values are often greater than 256. 
*	sfixed32	Always four bytes.  
*	sfixed64	Always eight bytes.
*	bool
*	string		A string must always contain UTF-8 encoded or 7-bit ASCII text.
*	bytes		May contain any arbitrary sequence of bytes.
*
*	ע�� PBû�ж���1Byte,2Byte�����ͣ�����4Byte��; ���ǻ�������ͷ�Χ��̬�����ֽ�����
*		
******************************************************************************/

// ������ٶ�����/������
option optimize_for = SPEED;

enum BOURSE_MSG_ID
{
	ID_S2C_BOURSE_NOTIFY_ACCOUNT				= 0x5801;
	ID_C2S_BOURSE_INC_ACCOUNT					= 0x5802;
	ID_C2S_BOURSE_DEC_ACCOUNT					= 0x5803;
	ID_C2S_BOURSE_LOAD_ACCOUNT					= 0x5804;
	ID_C2S_BOURSE_ADD_BUY						= 0x5805;
	ID_C2S_BOURSE_ADD_SELL						= 0x5806;
	ID_C2S_BOURSE_LOAD_SELF_LIST				= 0x5807;
	ID_S2C_BOURSE_NOTIFY_SELF_LIST				= 0x5808;
	ID_C2S_BOURSE_LOAD_LIST						= 0x5809;
	ID_S2C_BOURSE_LIST_NOTICE					= 0x580A;
	ID_S2C_BOURSE_CODE							= 0x580B;
	ID_S2C_BOURSE_TRADE_BUY						= 0x580C;
	ID_S2C_BOURSE_TRADE_SELL					= 0x580D;
	ID_C2S_BOURSE_BUY_DOC						= 0x580E;
	ID_C2S_BOURSE_SELL_DOC						= 0x5810;
	ID_C2S_BOURSE_TRADE_LOG_QUERY				= 0x5811;
	ID_S2C_BOURSE_TRADE_LOG						= 0x5812;
};

enum BOURSE_ACCOUNT_NOTIFY_CODE
{
	BOURSE_ACCOUNT_LOAD							= 0;
	BOURSE_ACCOUNT_INC							= 1;	// 1 ��Ǯ 2 Ԫ��
	BOURSE_ACCOUNT_DEC							= 2;	// 1 ��Ǯ 2 Ԫ��
	BOURSE_ACCOUNT_TRADE						= 4;
	BOURSE_ACCOUNT_NOTENOUGH_MONEY				= 16;
	BOURSE_ACCOUNT_NOTENOUGH_YB					= 32;
	BOURSE_ADD_DOC_BUY							= 64;	// 1 ���� 2 Ԫ������ 3 ˰
	BOURSE_ADD_DOC_SELL							= 128;	// ͬ��
	BOURSE_DEC_DOC_BUY							= 256;	// 1 ���� 2 Ԫ������
	BOURSE_DEC_DOC_SELL							= 512;	// ͬ��
};

message PBBourseAccountInfo
{
	optional uint32 Money						= 1;
	optional uint32 Yb							= 2;
};

message PBBourseDetail
{
    optional uint32 bourse_doc_no   = 1;
    optional uint32 account_id      = 2;
    optional uint32 price           = 3;
    optional uint32 yb_count        = 4;
    optional uint32 bourse_date     = 5;
	optional uint64 bourse_detail	= 6;
	optional uint32 role_id			= 7;
//  optional uint32 trade_type      = 6;
};

message PBBourseDetailList
{
    repeated PBBourseDetail list = 1;
};


// ����ʻ���Ϣ
message CMessageBourseAccountNotify
{
	optional PBBourseAccountInfo Account		= 1;
	optional uint32 YB							= 2;
	optional uint32 NotifyCode					= 3;
	optional uint32 Param1						= 4;
	optional uint32 Param2						= 5;
	optional uint32 Param3						= 6;
};

message CMessageBourseCode
{
	optional uint32 Code						= 1;
};

// ������ӽ������ʻ�
message CMessageBourseIncAccount
{
	optional PBBourseAccountInfo AccountInc		= 1;
};

// �����ȡ�������ʻ�
message CMessageBourseDecAccount
{
	optional PBBourseAccountInfo AccountDec		= 1;
};

message CMessageBourseAccountLoad
{
	
};

message CMessageBourseAccountAddBuy
{
	optional uint32 price = 1;
	optional uint32 yb_count = 2;
};

message CMessageBourseAccountAddSell
{

	optional uint32 price = 1;
	optional uint32 yb_count = 2;
};

message CMessageBourseLoadSelfList
{

};


message CMessageBourseSelfListNotice
{
	optional PBBourseDetailList BuyList		= 1;
	optional PBBourseDetailList SellList	= 2;
};

message CMessageBourseListNotice
{
	optional PBBourseDetailList BuyList		= 1;
	optional PBBourseDetailList SellList	= 2;
	optional uint32	ListID					= 3;
};

message CMessageBourseLoadList
{
	optional uint32 ListID					= 1;
};

message CMessageBourseTradeBuyNotice
{
	optional PBBourseDetail Detail			= 1;
};

message CMessageBourseTradeSellNotice
{
	optional PBBourseDetail Detail			= 1;
};

message CMessageBourseDecBuyDoc
{
	optional uint32 	Doc					= 1;
};

message CMessageBourseDecSellDoc
{
	optional uint32		Doc					= 1;
};

message CMessageBourseTradeLog
{
	optional PBBourseDetailList		buy_log				= 1;
	optional PBBourseDetailList		sell_log			= 2;
};

message CMessageBourseTradeLogQuery
{

};





