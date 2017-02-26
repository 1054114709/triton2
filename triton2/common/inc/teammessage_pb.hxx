import "coremessage_pb.hxx";
import "property_pb.hxx";

// ������ٶ�����/������
option optimize_for = SPEED;

enum TeamMessageID
{								
	ID_C2S_REQUEST_CREATETEAM						= 0x1C01;				// �Դ�������
	ID_C2S_REQUEST_INVITE							= 0x1C02;				// �������
	ID_C2S_REQUEST_INVITERTN						= 0x1C03;				// �������󷵻�
	ID_C2S_REQUEST_INVITEDREQUEST					= 0x1E04;				// 0x1C04 + 0x0200��Ա������������
	ID_C2S_REQUEST_SEARCH							= 0x1C05;				// �����Ϣ����
	ID_C2S_REQUEST_ASKFORJOIN						= 0x1C06;				// �������
	ID_C2S_REQUEST_APPLYRTN							= 0x1C07;				// ������Ϣ����		client to server
	ID_C2S_REQUEST_LEAVE							= 0x1C08;				// ���
	ID_C2S_REQUEST_NEWHEAD							= 0x1C09;				// ת�ƶӳ�
	ID_C2S_REQUEST_TICK								= 0x1C0A;				// ����
	ID_C2S_REQUEST_ENDTEAM							= 0x1C0B;				// ��ɢ����
	ID_S2C_REQUEST_PROPOSERRTN						= 0x1E0C;				// 0x1C0C + 0x0200��������Ϣ����	server to client
	ID_S2C_NOTIFY_SYNITEMLIST						= 0x1E0D;				// 0x1C0D + 0x0200ͬ����Ա�б�		server to client
	ID_S2C_NOTIFY_ITEMLIST							= 0x1C0E;				// ���ͳ�Ա�б�
	ID_S2C_NOTIFY_ENDTEAM							= 0x1C0F;				// �����ɢ				server to client
	ID_S2C_NOTIFY_ASKJOINRTN						= 0x1E10;				// 0x1C10 + 0x0200�����������ķ�����Ϣ	server to client
	ID_S2C_NOTIFY_TICKRTN							= 0x1C11;				// �������˵ķ�����Ϣ	server to client
	ID_S2C_NOTIFY_ERRORMSG							= 0x1E12;				// 0x1C12 + 0x0200���ʹ�����Ϣ		server to client
	ID_C2S_NOTIFY_ASKTEAMMSG						= 0x1C13;				// �ύ������Ϣ		client to server
	ID_S2C_NOTIFY_ASKTEAMTRN						= 0x1C14;				// ���ⷵ��
	ID_S2C_NOTIFY_CONSCRIBERTN						= 0x1C15;				// ��ļ����
	ID_C2S_NOTIFY_CONSCRIBEMSG						= 0x1C16;				// �ύ��ļ��Ϣ
	ID_S2C_NOTIFY_SYNPROPERTY						= 0x1E17;				// 0x1C17 + 0x0200ͬ�������Ա��Ϣ	server to client
	ID_C2S_REQUEST_CHANGEDISTRIBUTE					= 0x1C18;				// ���͸ı����ģʽ����	client to server
	ID_S2C_NOTIFY_CHANGEDISTRIBUTERTN				= 0x1C19;				// ���͸ı����ģʽ�ķ�����Ϣ server to client
	ID_S2C_NOTIFY_SYNBUFF							= 0x1C1A;				// ͬ��buff��Ϣ			server to client
	ID_C2S_REQUEST_BUFFRTN							= 0x1C1B;				// ����buff��Ϣ
	ID_C2S_REQUEST_ALIVESTATE						= 0x1E1C;				// 0x1C1C + 0x0200��������״̬��Ϣ
	ID_C2S_REQUEST_CLEARREQUESTLIST					= 0x1C1D;				// ɾ�������б�
	ID_C2S_REQUEST_CLEARINVITELIST					= 0x1C1E;				// ɾ�������б�
	ID_S2C_NOTIFY_CLEARREQUESTCALLBACK				= 0x1C1F;				// ɾ�������б�������
	ID_S2C_NOTIFY_CLEARINVITECALLBACK				= 0x1C20;				// ɾ�������б�������
	ID_C2S_REQUEST_SEARCHMSG						= 0x1C21;				// ����������Ϣ
	ID_C2S_REQUEST_SRHCONSCRIBEMSG					= 0x1C22;				// ������ļ��Ϣ
	ID_S2C_NOTIFY_SEARCHMSGCALLBACK					= 0x1E23;				// 0x1C23 + 0x0200����������Ϣ�������
	ID_S2C_NOTIFY_SRHCONSCRIBECALLBACK				= 0x1E24;				// 0x1C24 + 0x0200������ļ��Ϣ�������
	ID_C2S_REQUEST_DELMSG							= 0x1C25;				// ɾ��������ļ��Ϣ
	ID_S2C_NOTIFY_DELMSGCALLBACK					= 0x1C26;				// ɾ��������ļ��Ϣ�������
	ID_C2S_REQUEST_ORDERFOLLOW						= 0x1C27;				// ��Ӹ�������
	ID_C2S_REQUEST_REQUESTFOLLOW					= 0x1C28;				// �������ӳ�
	ID_S2C_NOTIFY_ORDERFOLLOWRTN					= 0x1C29;				//	������Ӹ���������
	ID_S2C_NOTIFY_REQUESTFOLLOWRTN					= 0x1C2A;				//	������Ӹ���������
	ID_S2C_NOTIFY_2PARAMNOTIFY						= 0x1C2B;				// ���������Ĳ�����ʾ��Ϣ
	ID_S2C_NOTIFY_CHANGETEAMSTATE					= 0x1C2C;				// ���Ͷ����־�ı�
	ID_S2S_RESPONSE_REDIRECTJOINTEAM				= 0x1E2D;				// 0x1C2D + 0x0200 �糡����ӻظ�
	ID_S2S_NOTIFY_REDIRECTRELATION					= 0x1E2E;				// 0x1C2E + 0x0200 �糡�����������ϵ
	ID_S2S_NOTIFY_REDIRECTCREATETEAM				= 0x1E2F;				// 0x1C2F + 0x0200 �糡��֪ͨ��������
	ID_S2C_NOTIFY_TEAMNOTICE						= 0x1C30;				// ���֪ͨ
};



/************************************************************************/
/* CMessageCreateTeamSelf �ͻ���->������ �Դ���*/
/************************************************************************/

message CMessageCreateTeamSelf
{
						                                		
};

// *************************************************************************** //
// CMessageTeamInvite ��Ϸ�ͻ���-> ��Ϸ������
// ������Ҽ������
// *************************************************************************** //

message CMessageTeamInvite
{
	optional uint32 EntityID		 = 		1; 	// �Է�EntityID
	optional uint32 CharID			 = 		2; 	//
};

// *************************************************************************** //
// CMessageTeamInviteRtn ��Ϸ�ͻ���-> ��Ϸ������
// ��������ҶԶ��������Ӧ
// *************************************************************************** //
message CMessageTeamInviteRtn
{
	optional uint32		RtnCode  = 		1; 		// �������������: ͬ�⡢�ܾ�
	optional uint32		InviteID  = 		2; 		// ������charid
	optional uint32		InviteEntityID  = 		3; 	// ������ʵ��id��������������ѯ����ʵ��id
	optional uint32		HeadCharID  = 		4; 		// �ӳ���ɫID
	optional uint32		TeamID  = 		5; 			// �����־
};

/************************************************************************/
/* CMessageTeamInvitedRequest ��Ա������������                                                                     */
/************************************************************************/
message CMessageTeamInvitedRequestCallBack
{
	optional CMessageRouter Router  = 		1; 
	optional uint32		AccoutID  = 		2; 			// �������˵�accountid
	optional string		InviteeName  = 		3; 		// �������˵�name
	optional uint32		InviteID  = 		4; 			// ������charid
	optional uint32		EntityID  = 		5; 			// �������˵�entityid
	optional uint32		Level  = 		6; 
	optional string		InviteName  = 		7; 			// ������name
	optional uint32		Nationality	 = 		8; 		// �������˵Ĺ��� 
	optional uint32		InviteeID  = 		9; 			// �������˵�charid
	optional uint32		Sex  = 		10; 
	optional uint32		Metier  = 		11; 
	optional uint32		Face  = 		12; 				// �������˵�����
};


// *************************************************************************** //
// CMessageTeamSearch ��Ϸ�ͻ���-> ��Ϸ������
// �����������
// *************************************************************************** //
message CMessageTeamSearch
{

};

// *************************************************************************** //
// CMessageTeamInviteRequest ��Ϸ�ͻ���-> ��Ϸ������
// �������
// *************************************************************************** //
message CMessageTeamRequest
{
	optional uint32		EntityID  = 		1; 		// �Է�entityid (�ǳ�����)	
	optional uint32		CharID	  = 		2; 		// �Է�charid
};

// *************************************************************************** //
// CMessageTeamInviteRequestRtn ��Ϸ�ͻ���-> ��Ϸ������
// ���������Ҽ���
// *************************************************************************** //
message CMessageTeamRequestRtn
{
	optional uint32		CharID  = 		1; 			// �����˽�ɫid
	optional uint32		EntityID  = 		2; 		// ������entityid(�ǳ�����)
	optional uint32		Code  = 		3; 			// ͬ�⣬�ܾ�
	optional uint32		AccountID  = 		4; 		// �������˺�id
};

// *************************************************************************** //
// CMessageTeamLeave ��Ϸ�ͻ���-> ��Ϸ������
// �뿪����
// *************************************************************************** //
message CMessageTeamLeave
{

};

// *************************************************************************** //
// CMessageTeamNewHead ��Ϸ�ͻ���-> ��Ϸ������
// ת�ƶӳ�
// *************************************************************************** //
message CMessageTeamNewHead
{
	optional uint32 CharID  = 		1; 				// �¶ӳ�charid
	optional uint32 EntityID  = 		2; 			// �¶ӳ�ʵ��id(����ṩ)
};

// *************************************************************************** //
// CMessageTeamNewHead ��Ϸ�ͻ���-> ��Ϸ������
// ����
// *************************************************************************** //
message CMessageTeamTick
{
	optional uint32 EntityID	 = 		1; 		// �Է�EntityID��(�ǳ�����)
	optional uint32 CharID		 = 		2; 		// ������ҵ�charid
};

/************************************************************************/
/*	CMessageTeamEnd ��ɢ���� 
*/
/************************************************************************/
message CMessageTeamEnd 
{

};

// *************************************************************************** //
// CMessageTeamRequestPlayerCallBack ��Ϸ������-> ��Ϸ�ͻ���
// ������������Ϣ���͸��ӳ�
// *************************************************************************** //
message CMessageTeamRequestPlayerCallBack
{
	// ��ֻ�����Member���е����ݼ���
	//optional PBMember	Member = 9;				// ��������Ϣ
	optional CMessageRouter Router  = 		1; 
	optional uint32		EntityID  = 		2; 			// �����˵�ʵ��id
	optional uint32		Face  = 		3; 
	optional uint32		Nationality  = 		4; 		// �����˹���
	optional string		Name  = 		5; 				// ������name
	optional uint32		AccoutID  = 		6; 
	optional uint32		Level  = 		7; 
	optional uint32		Sex  = 		8; 
	optional uint32		Metier  = 		9; 
	optional uint32		CharID  = 		10; 
};

// *************************************************************************** //
// CMessageTeamNotifyCallBack ��Ϸ������-> ��Ϸ�ͻ���
// ��ͻ���ͬ�������Ա�б�
// ���⼸������:������Ա����Ա��ȥ���ӳ��仯����Ա���Ը���
// ��ֻ����� Code �� Member ��������
// *************************************************************************** //
message CMessageTeamNotifyCallBack
{
	
	//optional string		Name = 2;
	//optional uint32		CharID = 3;
	//optional uint32		Face = 5;
	//optional uint32		Metier = 6;
	//optional uint32		Level = 7;
	//optional uint32		Sex = 8;
	//optional uint32		EntityID = 9;	// ���ǵ�ʵ��id
	////optional PBMember	Member = 8;		// ���ǵ�����
	//optional uint32		LineID = 10;
	//optional uint32		MapID = 11;
	optional CMessageRouter Router  = 		1; 
	optional uint32		Code  = 		2; 
	optional PBMember	Member  = 		3; 
};

// *************************************************************************** //
// CMessageTeamCallBack ��Ϸ������-> ��Ϸ�ͻ���
// ���ͳ�Ա�б�
// *************************************************************************** //
message CMessageTeamCallBack
{ 
	optional string		HeaderName  = 		1; 	// �ӳ�
	optional uint32		Count  = 		2; 		// ��������
	optional string		Buff  = 		3; 
	optional uint32		HeadEtyID  = 		4; 	// �ӳ�ʵ��id
	repeated PBMember	Member  = 		5; 		// ��Ա����
	optional uint32		BuffSize  = 		6; 
	optional uint32		Distribute  = 		7; 	// ����ģʽ
};

// *************************************************************************** //
// CMessageTeamEndCallBack ��Ϸ������-> ��Ϸ�ͻ���
// �����ɢ
// *************************************************************************** //
message CMessageTeamEndCallBack
{

};

// *************************************************************************** //
// CMessageTeamInviteAskCallBack ��Ϸ������-> ��Ϸ�ͻ���
// ���������Ϣ
// *************************************************************************** //
message CMessageTeamInviteAskCallBack
{
	optional CMessageRouter Router  = 		1; 
	optional uint32			Count  = 		2; 
	optional string			HeadName  = 		3; 
	optional string			Name    = 		4; 		// ������name
	optional uint32			Nationality	 = 		5; 	// �����߹���
	repeated PBMember		Member  = 		6; 
	optional uint32			BuffLen  = 		7; 		// TODO deleted
	optional uint32			CharID  = 		8; 		// ������charid
	optional uint32			EntityID  = 		9; 		// �����ߵ�ʵ��id
	optional uint32			TeamID  = 		10; 
	optional uint32			Distribute  = 		11; 
	optional string			Buff  = 		12; 			// TODO deleted
};

// *************************************************************************** //
// CMessageTeamTickCallBack ��Ϸ������-> ��Ϸ�ͻ���
// �������˷�����Ϣ
// *************************************************************************** //
message CMessageTeamTickCallBack
{
	optional string			Name	 = 		1; 		// �������name
	optional uint32			CharID  = 		2; 			// ���ߵ����
	optional uint32			EntityID  = 		3; 		// �������ʵ��ID
};

// *************************************************************************** //
// CMessageTeamErrMsgCallBack ��Ϸ������-> ��Ϸ�ͻ���
// ����ʧ��
// *************************************************************************** //
message CMessageTeamErrMsgCallBack
{
	optional CMessageRouter Router  = 		1; 
	optional string		Name  = 		2; 
	optional uint32		Code  = 		3; 
	optional uint32		CharID  = 		4; 
};

// *************************************************************************** //
// CMessageTeamAskTeamMsg ��Ϸ�ͻ���-> ��Ϸ������
// ����������Ϣ
// *************************************************************************** //
message CMessageTeamAskTeamMsg
{
	optional uint32		ConscribeType  = 		1; 
	optional uint32		SubType  = 		2; 
	optional string		Msg  = 		3; 
};

// *************************************************************************** //
// CMessageTeamAskTeamCallBack Server-> client
// *************************************************************************** //
message CMessageTeamAskTeamCallBack
{
	optional string		Msg  = 		1; 
	optional string		Name  = 		2; 					// ����������Ϣ�����
	optional uint32		Level  = 		3; 
	optional uint32		SubType  = 		4; 
	optional uint32		Metier  = 		5; 
	optional uint32		ConscribeType  = 		6; 
};

//*************************************************************************** //
// CMessageTeamConscirbeMsg ��Ϸ�ͻ���-> ��Ϸ������
// ������ļ��Ϣ
// *************************************************************************** //
message CMessageTeamConscribeMsg
{
	optional uint32		ConscribeType  = 		1; 
	optional uint32		SubType  = 		2; 
	optional uint32		MaxLevel  = 		3; 
	optional string		Msg  = 		4; 
	optional uint32		MinLevel  = 		5; 
	optional uint32		Metier  = 		6; 
};

/************************************************************************/
/*    CMessageTeamConscribeCallBack                                                                  */
/************************************************************************/
message CMessageTeamConscribeCallBack
{
	optional uint32		MaxLevel  = 		1; 
	optional uint32		Metier  = 		2; 
	optional string		Msg  = 		3; 
	optional uint32		Count  = 		4; 
	optional uint32		MinLevel  = 		5; 
	optional uint32		ConscribeType  = 		6; 
	optional uint32		SubType  = 		7; 
	optional string		HeaderName  = 		8; 
};

//************************************************************************/
//CMessageTeamPropertyNotifyCallBack ��������->�ͻ���
//ͬ��������Ϣ
//
//************************************************************************/


message CMessageTeamPropertyNotifyCallBack
{
	//optional uint32		CharID = 2;
	//optional string		Name = 3;
	//optional uint32		HP = 4;
	//optional uint32		MP = 5;
	//optional uint32		AP = 6;
	//optional uint32		Metier = 7;
	//optional uint32		Level = 8;
	//optional uint32		XPos = 9;
	//optional uint32		YPos = 10;
	//optional uint32		LineID = 11;	// ��ǰ��ķ�����ID
	//optional uint32		MapID = 12;		// ��ǰ��ĵ�ͼID
	optional CMessageRouter Router  = 		1; 
	repeated PBMember	ItemPro  = 		2; 		// ��Աpro
	optional uint32		ItemSize  = 		3; 		// ��Ա����
};

//***********************************************************************/
// CMessageTeamChangeDistribute�ͻ���->��������
//�ı����ģʽ
//
//************************************************************************/

message CMessageTeamChangeDistribute
{
	optional uint32		Distribute   = 		1; 
};

/************************************************************************/
/* CMessageTeamChangeDistributeCallBack ��������->�ͻ���
���͸ı����ģʽ�ķ�����Ϣ
*/
/************************************************************************/


message CMessageTeamChangeDistributeCallBack
{
	optional uint32		Distribute  = 		1; 
};

/************************************************************************/
/* CMessageTeamNotifyBuffCallBack��������->�ͻ���
ͬ��Buff��Ϣ
*/
/************************************************************************/

message CMessageTeamNotifyBuffCallBack
{
	optional uint32		IsAdd  = 		1; 			// true -- ����buff, false -- ɾ��buff
	optional string		Name  = 		2; 
	optional uint32		CharID  = 		3; 
	optional uint32		BuffID  = 		4; 
};

/************************************************************************/
/* CMessageTeamBuffCallBack                                                                     */
/************************************************************************/
message CMessageTeamBuffCallBack
{
	optional uint32		BuffSize	 = 		1;  
	optional string		BuffList	 = 		2; 
	optional string		Name		 = 		3; 
	optional uint32		CharID		 = 		4; 
	optional uint32		BuffCount	 = 		5; 
};

///************************************************************************/
///*   CMessageTeamAliveStateCallBack                                                                   */
///************************************************************************/
//
//message CMessageTeamAliveStateCallBack
//{
//	optional CMessageRouter Router = 1;
//	optional uint32			IsAlive = 2;	// ���ߡ����ߡ��������糡��
//	optional string			Name = 3;
//	optional uint32			CharID = 4;
//};

/************************************************************************/
/* CMessageTeamClearRequestList    ��������б�                                                                  */
/************************************************************************/

message CMessageTeamClearRequestList 
{
	optional uint32			CharID  = 		1; 		// ��������charid
};

/************************************************************************/
/* CMessageTeamClearInviteList    ��������б�                                                                  */
/************************************************************************/

message CMessageTeamClearInviteList 
{
	optional uint32			CharID  = 		1; 		// ��������charid
};

/************************************************************************/
/* CMessageTeamClearRequestCallBack    ��������б�callback                                                                  */
/************************************************************************/

message CMessageTeamClearRequestCallBack
{
	optional uint32			CharID  = 		1; 		// ��������charid
};

/************************************************************************/
/* CMessageTeamClearInviteCallBack    ��������б�callback                                                                  */
/************************************************************************/

message CMessageTeamClearInviteCallBack
{
	optional uint32			CharID  = 		1; 		// ��������charid
};

//************************************************************************/
// CMessageTeamSearchMsg  
//	��������	
//
//************************************************************************/

message CMessageTeamSearchMsg
{
	optional uint32		ConscibeType  = 		1; 	// һ������
	optional uint32		SubType  = 		2; 		// ��������
	optional uint32		PageIndex  = 		3; 		// ��ҳ��
	optional uint32		MsgType  = 		4; 		// ��ʼ���ڡ�������������
};

/************************************************************************/
/* CMessageTeamSearchMsgCallBack                                                                     */
/************************************************************************/

message CMessageTeamSearchMsgCallBack
{
	optional CMessageRouter Router  = 		1; 
	optional uint32		TotalPage  = 		2; 		// ��ҳ��
	optional bytes		MsgBuff   = 		3; 
	optional uint32		MsgSize  = 		4; 		// ��Ϣ����
	optional uint32		PageIndex  = 		5; 		// ��ҳ��
	optional uint32		BuffLen  = 		6; 		// �ַ�����
	optional uint32		MsgType  = 		7; 
	optional uint32		MsgCount  = 		8; 	
	repeated PBTeamMsg	Msg  = 		9; 			// �����õ���ļ��Ϣ
};

/************************************************************************/
/* CMessageTeamSearchConscribeMsg                                                                     */
/************************************************************************/

message CMessageTeamSearchConscribeMsg
{
	optional uint32		MsgType  = 		1; 		// ��ʼ���桢��ļ��������
	optional uint32		MaxLevel  = 		2; 
	optional uint32		PageIndex  = 		3; 		// ��ҳ��
	optional uint32		MinLevel  = 		4; 		
	optional uint32		ConscribeType  = 		5; 	// һ������
	optional uint32		Metier  = 		6; 
	optional uint32		SubType  = 		7; 		// ��������
};

/************************************************************************/
/* CMessageTeamSearchConscribeCallBack                                                                     */
/************************************************************************/

message CMessageTeamSearchConscribeCallBack
{
	optional CMessageRouter Router  = 		1; 
	optional bytes		MsgBuff   = 		2; 
	optional uint32		BuffLen  = 		3; 			// �ַ�����
	optional uint32		MsgType  = 		4; 
	optional uint32		MsgCount  = 		5; 	
	optional uint32		PageIndex  = 		6; 		// ��ҳ��
	repeated PBTeamMsg	Msg  = 		7; 
	optional uint32		MsgSize  = 		8; 		// ��Ϣ����
	optional uint32		TotalPage  = 		9; 		// ��ҳ��
};

/************************************************************************/
/* CMessageTeamDeleteMsg                                                                     */
/************************************************************************/

message CMessageTeamDeleteMsg 
{
	optional uint32		MsgType  = 		1; 	// ���飿��ļ
	optional uint32		CharID  = 		2; 
};

/************************************************************************/
/* CMessageTeamDeleteMsgCallBack                                                                     */
/************************************************************************/

message CMessageTeamDeleteMsgCallBack
{
	optional uint32			EntityID  = 		1; 
	optional uint32			MsgType  = 		2; 
};

/************************************************************************/
/* CMessageTeamOrderFollow        ����������                                                             */
/************************************************************************/

message CMessageTeamOrderFollow 
{
	optional uint32			Code  = 		1; 	// 1--������棬0--ȡ������ 
};

/************************************************************************/
/* CMessageTeamOrderFollowCallBack                                                                     */
/************************************************************************/

message CMessageTeamOrderFollowCallBack 
{
	optional uint32			CharID		 = 		1; 
	optional string			HeaderName	 = 		2; 
	optional uint32			Code		 = 		3; 	// 1--������棬0--ȡ������ 
};

/************************************************************************/
/* CMessageTeamRequestFollow                  ������Ӹ���                     */
/************************************************************************/

message CMessageTeamRequestFollow 
{
	optional uint32			Code		 = 		1; 	// 1--������棬 0--ȡ������
};

/************************************************************************/
/* CMessageTeamRequestFollowCallBack                                                                     */
/************************************************************************/

message CMessageTeamRequestFollowCallBack
{
	optional string Name  = 		1; 			// ���������
	optional uint32	CharID  = 		2; 
};

/************************************************************************/
/* CMessageTeamTwoParamCallBack    ����ʱ��Ҫ2�����������ʾ����Ϣ                         */
/************************************************************************/

message CMessageTeamTwoParamCallBack 
{
	optional string		DesName  = 		1; 				// right parameter
	optional uint32		DesCharID  = 		2; 
	optional string		SrcName  = 		3; 				// left parameter
	optional uint32		Code  = 		4; 
	optional uint32		SrcCharID  = 		5; 
};

message CMessageTeamStateChange
{
	optional uint32		TeamFlag  = 		1; 	// ���Ƕ����־��Ϊ��ɫID �мǣ�����
	optional uint32		CharID  = 		2; 		// ���ǽ�ɫID
	optional uint32		EntityID  = 		3; 	// ��ʱ����				
};

//******************************************************
// CMessageRedirectJoinTeamResponse
//******************************************************

message CMessageRedirectJoinTeamResponse
{
	optional CMessageRouter Router   = 		1; 
	optional uint32 ItemID			 = 		2; 
	optional uint32	HeadID			 = 		3; 
};

//******************************************************
// CMessageRedirectTeamRelationNotice
// �������������ϵ��֪ͨ
//******************************************************

message CMessageRedirectTeamRelationNotice
{
	optional CMessageRouter Router  = 		1; 
	optional uint32		DesCharID  = 		2; 	// ������
	optional uint32		IsAdd	   = 		3; 	// true -- ������ false --ɾ��
	optional uint32		SrcCharID  = 		4; 	// ������
	optional string		DesName	   = 		5; 
	optional uint32		Type	   = 		6; 	// ���룿����
	optional string		SrcName	   = 		7; 
};

//****************************************************
// �糡��֪ͨ�Է���������
//****************************************************

message CMessageRedirectCreateTeamNotice
{
	optional CMessageRouter Router  = 		1; 
	optional uint32		CharID	   = 		2; 
	optional uint32		SrcCharID  = 		3; 
	optional string		CharName   = 		4; 
};

//**********************************
// CMessageTeamNotice �����ʾ
//**********************************

message CMessageTeamNotice
{
	optional uint32 	Code	 = 		1; 
	optional string		Param2	 = 		2; 
	optional string		Param1	 = 		3; 	// default
};

////******************************************************
//// CMessageUpdateHeadTipsNotice
//// ������ -> �ͻ��� ֪ͨ�ͻ��˸���ͷ����ʾ
//// TeamFlag����
////******************************************************
//
//message CMessageUpdateHeadTipsNotice
//{
//	optional uint32			EntityID	= 1;	// ����ʵ��id
//	optional uint32			TeamFlag	= 2;	// ���Ƕ����־��Ϊ�ӳ���EntityID
//	optional uint32			AddClaim	= 3;	// Ϊbool���ͣ�true:��ʾ��false:���
//	optional PBClaimMsg		ClaimMsg	= 4;	// ������Ϣ
//	optional uint32			AddRecruit	= 5;	// Ϊbool���ͣ�true:��ʾ��false:���
//	optional PBRecruitMsg	RecruitMsg	= 6;	// ��ļ��Ϣ
//};

