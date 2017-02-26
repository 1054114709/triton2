import "coremessage_pb.hxx";
import "property_pb.hxx";

// ������ٶ�����/������
option optimize_for = SPEED;

enum TradeMessageID
{
	ID_C2S_REQUEST_TRADEINVITE				= 0x2400;			// ��������
	ID_S2C_NOTIFY_INVITERTN					= 0x2401;			// 
	ID_C2S_REQUEST_INVITEREPLY				= 0x2402;			// ��������
	ID_S2C_NOTIFY_TRADEBEGIN				= 0x2403;			// ֪ͨ��ʼ����
	ID_C2S_REQUEST_SENDGOODSINFO			= 0x2404;			// ������Ʒ��Ϣ
	ID_S2C_NOTIFY_GOODSINFO					= 0x2405;			// ֪ͨ��Ʒ��Ϣ
	ID_C2S_REQUEST_SENDTRADEMONEY			= 0x2406;			// �����ͽ��׽��
	ID_S2C_NOTIFY_TRADEMONEY				= 0x2407;			// ֪ͨ���׽��
	ID_C2S_REQUEST_LOCKTRADEINFO			= 0x2408;			// ����������Ϣ
	ID_S2C_NOTIFY_TRADEINFOLOCK				= 0x2409;			// 
	ID_C2S_REQUEST_CLOSETRADE				= 0x2410;			// �����������
	ID_S2C_NOTIFY_TRADECLOSE				= 0x2411;			// ���ͽ��׽��������Ŀ��
	ID_C2S_REQUEST_SUBMITTRADE				= 0x2412;			// ȷ������
	ID_S2C_NOTIFY_RESULTCODE				= 0x2413;			// ���׹�����Ϣ
};

/************************************************************************/
/* 
	CMessageTradeInvite		client send trade invite to server
*/
/************************************************************************/

message CMessageTradeInvite
{
	optional uint32 TargetEntityID  = 		1; 	// ����������	
};

/************************************************************************/
/* 
	CMessageTradeInviteCallBack		
	server notify trade invite to target client
*/
/************************************************************************/

message CMessageTradeInviteCallBack
{
	optional uint32 OriginEntityID  = 		1;  // ���׷�����
};

/************************************************************************/
/* 
	CMessageTradeInviteReply
	client send invite process result to server
*/
/************************************************************************/

message CMessageTradeInviteReply
{
	optional uint32 OriginEntityID  = 		1; 
	optional uint32	Code  = 		2; 		// �������봦����: ͬ��,�ܾ�������
};

/************************************************************************/
/*     
	CMessageNotifyTradeBegin
	server noitfy clients to begin trade
*/
/************************************************************************/

message CMessageNotifyTradeBegin
{
	optional uint32 TargetEntityID  = 		1; 		// ֪ͨ����
};

/************************************************************************/
/* 
	CMessageSendGoodsInfo
	client send trade goods to server
*/
/************************************************************************/

message CMessageSendGoodsInfo
{
	optional uint32 TradeType  = 		1; 		// ��������
	optional uint32 TradeIndex  = 		2; 		// ����������
	optional uint32 ItemIndex  = 		3; 		// ��������
	optional uint32 Count  = 		4; 			// ��Ʒ����
};

/************************************************************************/
/* 
	CMessageNotifyGoodsInfo
	server notify goods info to clients
*/
/************************************************************************/

message CMessageNotifyGoodsInfo
{
	optional bytes	GoodsBuff  = 		1; 		// ��Ʒ�ַ���	
	optional PBItemObject Item  = 		2; 		// ������Ϣ
	optional uint32 BuffLen  = 		3; 		// 
	optional uint32 Type  = 		4; 			// �������ͣ�AddGoods, DelGoods, Money
	optional uint32 TradeIndex  = 		5; 		// ����������
	optional uint32 IsSelf  = 		6; 			// �Լ�?
	optional uint32 ItemIndex  = 		7; 		// ��������
};

/************************************************************************/
/* 
	CMessageSendTradeMoney
	client send trade money to server
*/
/************************************************************************/

message CMessageSendTradeMoney
{
	optional uint32 Money  = 		1; 		// ���׽��
};

/************************************************************************/
/* 
	CMessageNotifyTradeMoney
	server notify trade money to client
*/
/************************************************************************/

message CMessageNotifyTradeMoney
{
	optional uint32 IsSelf  = 		1; 		// �Լ�?
	optional uint32 Money  = 		2; 		// ���׽��
};

/************************************************************************/
/* 
	CMessageLockTradeInfo
	client request server to lock trade info,include goods and money info
*/
/************************************************************************/

message CMessageLockTradeInfo
{
	optional uint32 LockState  = 		1; 		// ������״̬
};

/************************************************************************/
/* 
	CMessageNotifyTradeInfoLock
	server notify client to lock trade info,so as to keep trade safety
*/
/************************************************************************/

message CMessageNotifyTradeInfoLock
{
	optional uint32 IsSelf  = 		1; 			// �Լ�?
	optional uint32 LockState  = 		2; 		// ������״̬
};

/************************************************************************/
/* 
	CMessageCloseTrade
	client request server to close trade window, when cancel trade ,
	special close and end trade normally
*/
/************************************************************************/

message CMessageCloseTrade
{
	optional uint32 Code  = 		1; 			// ������: ȡ������������
};

/************************************************************************/
/* 
	CMessageNotifyTradeClose
	server notify client to close trade window, as trade has been ended
*/
/************************************************************************/

message CMessageNotifyTradeClose
{
	optional uint32 Code  = 		1; 			// �����룺ȡ������������
};

/************************************************************************/
/* 
	CMessageNotifyResultCode
	server notify client to show process tips
*/
/************************************************************************/

message CMessageNotifyResultCode
{
	optional uint32 Code  = 		1; 			// ��ʾ��Ϣ��
	optional uint32 EntityID  = 		2; 		// ����
};

/************************************************************************/
/* 
	CMessageSubmitTrade
	client request server to submit trade ,so as to a normal trade end
*/
/************************************************************************/

message CMessageSubmitTrade
{
	optional uint32 Code  = 		1; 			// �����ύ��
};
