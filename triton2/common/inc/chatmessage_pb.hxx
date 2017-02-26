import "coremessage_pb.hxx";
import "property_pb.hxx";
// ������ٶ�����/������
option optimize_for = SPEED;


// ********************************************************************** //
// ChatMessageID  ����ģ����Ϣid
// ��ϢID+0x0200��ʾ����ϢΪ·����Ϣ
// ********************************************************************** //
enum ChatMessageID
{
	CHATMSG                       = 0x1400;        
	ID_C2S_CMESSCHATSEND          = 0x1401;          
	ID_S2C_CHATSENDCALLBACK       = 0x1402;        //0x1401 + 0x0200 
	ID_S2C_ROUTERCHATMESSAGE      = 0x1403;        //0x1403 + 0x0200
	ID_S2C_CHATRES2CLIENT         = 0x1404;  
	ID_C2S_NOTIFY_AUTOCHATMESSAGE = 0x1405;
	ID_C2S_NOTIFY_STOPAUTOCHAT    = 0x1406;
	ID_C2S_NOTIFY_USECHATITEM     = 0x1407;
	ID_C2S_NOTIFY_CLICKBUGLEITEM  = 0x1408;
	ID_C2S_REQUEST_CHECKDIRTYWORD = 0x1409;
	ID_S2C_NOTIFY_HASDIRTYWORD    = 0x140A;
};


// ********************************************************************** //
// CMessageChatSend  ��Ϸ�ͻ���->��Ϸ������
// ��ҷ���Ƶ��������Ϣ
// ********************************************************************** //
message CMessageChatSend
{
	optional string Msg				 = 		1;	// ��Ϣ����
	optional string PlayerID		 = 		2;	// Ŀ�����CharID 
	optional string PlayerName		 = 		3;	// Ŀ���������
	optional uint32 Channel			 = 		4;	// ����Ƶ��
	repeated uint32 PkgIndex		=		5;	// ��������(�磺�ֿ⣬�����������������װ���ȣ�
	repeated uint32 ItemIndex		=		6;	// ��Ʒ�ڰ����е�����
	repeated uint32 ItemSequence	=		7;	// �������У��ͻ���ר�ã�
};

// ********************************************************************** //
// CMessageChatSendCallBack����Ϸ������ -> ��Ϸ�ͻ���
// ����ҵ�������Ϣ���͸��ͻ���
// ********************************************************************** //
message CMessageChatSendCallBack
{	
	optional CMessageRouter Router  = 		1;    
	optional uint32	RepeatedNum	    = 		2; 						   // ϵͳ�����ظ����ŵĴ���
	optional uint32 ShowInTable     = 		3;                         // �Ƿ�����ͨ������ʾ	
	optional string Msg             = 		4;                         // ��Ϣ����		
	optional uint32 Channel         = 		5;                         // ����Ƶ��	
	repeated PBItemObject ItemInfo	=		6;							// �����������Ʒ��Ϣ
	optional uint32 CountryID       = 		7; 						   // ����ID,����Ƶ����	             
	optional uint32 NpcShoutFlag    = 		8; 						   // �����1���� ���ʾ���͵���NPC����xml�е�keyֵ(��#) �ɿͻ�����ת��
	optional uint32	FlagID			=		9;						   // ����ID���߾���ID����Ƶ���;���Ƶ���û��߶���ID
	optional uint32	UserType		=		10;						   // �����ߵ��û����� ��protype��� enUserTypeö��	
	optional uint32	DesUserType		=		11;						   // �����ߵ��û����� ��protype��� enUserTypeö��	
	optional uint32	UseFlag			=		12;						   // �����߾����������ʱ�����ID
	optional uint32	CampID			=		13;						   // ��ӪID
};

// ********************************************************************** //
// CMessageRouterChatMsg ����Ϸ������ -> ת��������
// ת��������Ҫ�������Ϣ
// ********************************************************************** //
message CMessageRouterChatMsg 
{   
	optional CMessageRouter Router  = 		1;                           
	optional string Msg             = 		2;                          // ��Ϣ
	optional uint32 Channel         = 		3;                          // Ƶ��
};
// ********************************************************************** //
// CMessageChatResult��   ��Ϸ������ -> ��Ϸ�ͻ���
// ���������������
// ********************************************************************** //
message  CMessageChatResult
{	

	optional uint32 ChatRes    = 		1;                     // ������� ������chattype��
	optional uint32 Channel    = 		2;                     // ��ҷ���Ƶ��
	optional string Msg        = 		3;                     // ��Ϣ 
	optional string Name       = 		4;                     // �������
	optional uint32 LeftTime   = 		5;                     // ���ڱ�ʾ����Ƶ����ʣ��ʱ�䣬�Զ�������ʣ�����
};
// ********************************************************************** //
// CAutoChatMessage��    ��Ϸ�ͻ��� -> ��Ϸ������ 
// �Զ�������Ϣ
// ********************************************************************** //
message CAutoChatMessage
{	
	optional string Msg       = 		1;                       // ��Ϣ
	optional uint32 Channel   = 		2;                       // ����Ƶ��
	optional uint32 Count     = 		3;                       // ��������
	optional string Name      = 		4;                       // ����
	optional uint32 Time      = 		5;                       // ����ʱ����
};
// ********************************************************************** //
// CStopAutoChatMessage��   ��Ϸ�ͻ��� -> ��Ϸ��Ϸ������
// ֹͣ�Զ�����
// ********************************************************************** //
message CStopAutoChatMessage
{	
	optional string Name      = 		1;                      // ����
	optional uint32 Channel   = 		2;                      // Ƶ��
};
// ********************************************************************** //
// CMessageUseItem��       ��Ϸ�ͻ��� -> ��Ϸ������ 
// ʹ��ָ�������ȵ��߷���
// ********************************************************************** //
message CMessageUseItem
{	
	optional string Msg        = 		1;                     // ��Ϣ
	optional bytes	ItemInfo   = 		2; 					  // �����������Ʒ��Ϣ
	optional uint32 ItemIndex  = 		3;                     // ���ĵ������ڵİ������� 	
};
// ********************************************************************** //
// CMesssageClickBugleItem�� ��Ϸ�ͻ��� -> ��Ϸ������
// ��ɫ�ſ���ȡ���֪ͨ
// ********************************************************************** //
message CMesssageClickBugleItem
{	
	optional uint32 ItemIndex  = 		1;                    // �������ڵĸ���	
	optional uint32 LockType   = 		2;                    // �������ͣ��������Ǽ��� �� 
}; 

// ********************************************************************** //
// CMessageCheckString�� ��Ϸ�ͻ��� -> ��Ϸ������
// ��鷢�͵���Ϣ���Ƿ���������
// ********************************************************************** //
message CMessageCheckDirtyWord
{
	optional string Msg   = 		1;                        // ��Ҫ�����ַ���
	optional uint32 Flag  = 		2;                        // ��Ϣ��־
};
// ********************************************************************** //
// CMessageCheckString    ��Ϸ������  -> ��Ϸ�ͻ��� 
// �������ֵļ�������͸��ͻ��˵�֪ͨ
// ********************************************************************** //

message CMessageHasDirtyWord
{	
	optional string Msg           = 		1;             // ���������ַ����зǷ������κ���ַ���
	optional uint32 HasDirtyWord  = 		2;             // ���������ֵı�־��1��ʾ�зǷ��ʣ�0��ʾû�У�
	optional uint32 Flag          = 		3;             // ��Ϣ��־
};
