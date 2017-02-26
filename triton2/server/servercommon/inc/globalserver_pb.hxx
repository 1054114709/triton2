// ������ٶ�����/������
option optimize_for = SPEED;

// ȫ�ַ�������Ϣ 0x6400 + 0x8000
enum EMGlobalServerMessageID 
{
	ID_S2D_REQUEST_GLOBALTELEPORT = 0xE400;	// ��ȫ�ַ��������Ϳ���������
	ID_D2S_RESPONSE_GLOBALTELEPORT = 0xE401;// ��ȫ�ַ��������Ϳ�������Ϣ��Ӧ
	ID_D2G_REQUEST_CHANGESERVER   = 0xE402;// ȫ�ַ�����֪ͨ���������Ҫ����
	ID_G2D_RESPONSE_CHANGESERVER  = 0xE403;// ����֪ͨȫ�ַ�����Ҫ�����������ؽ�ɫ�Ѿ�����(���Ե�¼)
	ID_D2G_REQUEST_CREATEREPETION = 0xE404;// ������������Ϣ����
	ID_G2D_RESPONSE_CREATEREPETION = 0xE405;// ������������Ϣ��Ӧ

	ID_S2D_REQUEST_PLAYERAPPLYWAR  = 0xE406;// ��ұ���������
	ID_D2S_REQPONSE_PLAYERAPPLYWAR = 0xE407;// ��ұ����Ļ�Ӧ
	ID_D2S_NOTIFY_WARENABLE		   = 0xE408; // ���Խ���ս����֪ͨ(��������)
	ID_S2D_NOTIFY_PLAYERLEAVEWAR	= 0xE409; // ����뿪ս����֪ͨ
	ID_S2D_NOTIFY_WAREND			= 0xE40A; // ս��������֪ͨ
	ID_S2S_NOTIFY_KICKGLOBALPLAYER	= 0xE40B; // �߳���ҵ�֪ͨ
	ID_S2S_NOTIFY_KICKGLOBALPLAYERACK= 0xE40C; // �߳���ҵ�֪ͨ
	ID_S2S_NOTIFY_SYNCGLOBALPLAYE	= 0xE40D; // ͬ��ȫ��ս���������Ϣ(�����һЩԭ�����������ƶ��е����)
};

message CMapData
{
	optional uint32 MapID = 1;
	optional uint32 PosX  = 2;
	optional uint32 PosY  = 3;
	optional uint32	LineID= 4;
};

// *************************************************************************** //
// CMessageGlobalTeleportRequest  
// ��ȫ�ַ��������Ϳ���������
// *************************************************************************** //
message CMessageGlobalTeleportRequest
{
	optional uint32 ServerType = 1;	// ���������ͣ��Ǹ�������������ȫ�ֳ���������
	optional uint32	WorldID	   = 2;	// ����������ID		
	optional uint32	ServerID	= 3;	// ���������������ID	
	optional uint32	RoleID		= 4;// ��ҽ�ɫID	
	optional uint32	AccountID	= 5;// �˺�ID(ע�ᵽĿ��������)

	optional uint32	OriginalServerID= 6;// ԭ�������ĵ�serverid(����ԭ��������)
	optional uint32	OriginalWorldID=7;	// ԭ��������worldid(����ԭ��������)	
	optional uint32	TeleType	=	8; // Ϊ1��ʾ����ԭ������������0��ʾ���͵�ȫ�ַ�����
	optional CMapData MapData	= 9;  // ��ͼ��Ϣ
	optional uint32	 GameID = 10;	  // ����˺ŵ�GameID
	optional string Mac		= 11;	  // mac��ַ
};

// *************************************************************************** //
// CMessageGlobalTeleportResponse  
// ��ȫ�ַ��������Ϳ�������Ϣ��Ӧ
// *************************************************************************** //
message CMessageGlobalTeleportResponse
{
	optional uint32	Errcode = 1;		// ������
	optional string Addr	= 2;		// ��������ַ(��Ϊ���ص�ַ)	
	optional uint32	LoginToken = 3;		
	optional uint32 RoleID = 4;			// ��ɫID 
	optional uint32	LineID = 5;			// ��ID	(��Ŀ�곡���ڱ���ʱ��Ҫ��Щ��Ϣ)
	optional uint32 MapID  = 6;			// ��ͼID
	optional uint32	PosX   = 7;			// ������
	optional uint32	PosY	= 8;		// ������	
	optional uint64 ReptionKey = 10;	// ����keyֵ
	optional uint32	TeamFlag   = 11;	// �����־
	optional uint32	RepetionIndex=12;	// ��������
	optional uint32	SceneWorldID = 13;	// Ŀ���������ڵ�����ID
};

// *************************************************************************** //
// CMessageChangeServerRequest  
// ȫ�ַ�����֪ͨ���������Ҫ����( ע����Ϣ��Ŀ������ )
// *************************************************************************** //
message CMessageChangeServerRequest
{
	optional uint32	 RoleID			= 1;	// ��ɫID
	optional uint32	 WorldID		= 2;	// ��ɫ���ڵ���Ϸ����ID
	optional uint32	 ServerID		= 3;	// ��ɫ���ڵ���Ϸ���������ID	
	optional uint32	AccountID		= 4;	// ��ҵ��˺�ID
	optional uint32	CurrentWorldID	= 5;	// �������ڵ���Ϸ������������ID	

	optional uint32	 MapID	  = 6;	// Ҫ����ĵ�ͼID
	optional uint32	 PosX	= 7;	// Ҫ����ĵ�ͼ������
	optional uint32	 PosY	= 8;	// Ҫ����ĵ�ͼ������
	optional uint64	 Key	= 9;	// ����Ǹ����Ļ�����Key
	optional uint32	 ServerKey = 10;// ��ȫ�ַ����������б���keyֵ
	optional uint32	 LineID  = 11;	// Ҫ����ķ���������ID
	optional uint32	 TeamFlag = 12;	// �����ʶ
	optional uint32	 GameID = 13;	// ����˺ŵ�GameID
	optional string	Mac		= 14;	// mac��ַ
};

// *************************************************************************** //
// CMessageCreateGlobalRoleInfoNotify  
// ����֪ͨȫ�ַ�����Ҫ�����������ؽ�ɫ�Ѿ�����(���Ե�¼)
// *************************************************************************** //
message CMessageChangeServerResponse
{
	optional uint32	Errcode		=	1;	// ������
	optional uint32	RoleID		=	2;	// ��ɫID
	optional uint32	WorldID		=	3;	// ��Ϸ����ID
	optional uint32	ServerKey	=	4;	// ��ȫ�ַ����������б���keyֵ
	optional uint32	ServerID	=	5;	// ������ڷ�������ID
	optional string	Addr		=	6;	// ���ص�ַ
	optional uint32	LoginToken	=	7;	// Ŀ�����ط��ص�����	
};

// *************************************************************************** //
// CMessageCreateRepetionRequest  
// ������������Ϣ����
// *************************************************************************** //
message CMessageCreateRepetionRequest
{
	optional uint32	 ReptionIndex = 1;			// ��������
	optional uint32	 RegKey		  = 2;			// ս����Ϣ��ע��ID
	optional uint64	 RepetionLevel= 3;			// �����ȼ�
};

// *************************************************************************** //
// CMessageCreateRepetionResponse  
// ������������Ϣ��Ӧ
// *************************************************************************** //
message CMessageCreateRepetionResponse
{
	optional uint32	Errcode			= 1;	// ������
	optional uint32	RegKey			= 2;	// ս����Ϣ��ע��ID
	optional uint64	ReptionKey		= 3;	// �����õĸ���key
};

// *************************************************************************** //
// CMessagePlayerApplyWarRequest  ID_S2D_REQUEST_PLAYERAPPLYWAR
// ��ұ���������
// *************************************************************************** //
message CMessagePlayerApplyWarRequest
{
	optional uint32	WorldID		= 1;		// ��ҵ�����ID
	optional uint32	ServerID	= 2;		// ������ڵĳ���ID
	optional uint32	RoleID		= 3;		// ��ҵĽ�ɫID
	optional uint32	RoleLevel	= 4;		// ��ҵĵȼ�
	optional uint32	RepetionIndex = 5;		// ��������
};

// *************************************************************************** //
// CMessagePlayerApplyWarResponse  ID_D2S_REQPONSE_PLAYERAPPLYWAR
// ��ұ����Ļ�Ӧ
// *************************************************************************** //
message CMessagePlayerApplyWarResponse
{
	optional uint32	Errcode = 1;
	optional uint32	RoleID = 2;	
	optional uint32	RegKey	= 3;
	optional uint32	CanStart = 4;	// �Ƿ������������ս��
	optional uint32	MinLevel = 5;	// ���ڵȼ��ε���͵ȼ�
	optional uint32	MaxLevel = 6;	// ���ڵȼ��ε���ߵȼ�
	optional uint32	TeamFlag = 7;	// ��ӪID
};

// *************************************************************************** //
// CMessageWarEnableNotify  ID_D2S_NOTIFY_WARENABLE
// ���Խ���ս����֪ͨ
// *************************************************************************** //
message CMessageWarEnableNotify
{
	optional uint32	WarRegKey = 1;		// ս��ע��ID
	optional uint32	RoleID	= 2;		// ��ɫID
	optional uint32 TeamFlag = 3;		// ��ӪID
};

// *************************************************************************** //
// CMessagePlayerLeaveWarNotify  ID_S2D_NOTIFY_PLAYERLEAVEWAR
// ����뿪ս����֪ͨ
// *************************************************************************** //
message CMessagePlayerLeaveWarNotify
{
	optional uint32 RoleID = 1;		// ��ɫID
	optional uint32 Reason = 2;		// �뿪ս����ԭ��
};

// *************************************************************************** //
// CMessageWarEndNotify  ID_S2D_NOTIFY_WAREND
// ս��������֪ͨ
// *************************************************************************** //
message CMessageWarEndNotify
{
	optional uint64	ReptionKey = 1;
	optional uint32	WarRegKey = 2;
	optional uint32	Reason	= 3;	// ������ԭ��
};

// *************************************************************************** //
// CMessageKickGlobalPlayerNotify  ID_S2S_NOTIFY_KICKGLOBALPLAYER
// �߳���ҵ�֪ͨ
// *************************************************************************** //
message CMessageKickGlobalPlayerNotify
{
	optional uint32	RoleID = 1;
	optional uint32	Reason	= 2;	// �߳���ԭ��
};

// *************************************************************************** //
// CMessageKickGlobalPlayerResultNotify  ID_S2S_NOTIFY_KICKGLOBALPLAYERACK
// �߳���ҵĽ��֪ͨ
// *************************************************************************** //
message CMessageKickGlobalPlayerACK
{
	optional uint32	RoleID		= 1;
	optional uint32	AccountID	= 2;	// �˺�ID
	optional uint32	RoleWorldID = 3;	// ������ڵ���Ϸ����ID
}

// *************************************************************************** //
// CMessageSyncGlobalPlayeNotify  ID_S2S_NOTIFY_SYNCGLOBALPLAYE
// ͬ��ȫ��ս���������Ϣ(�����һЩԭ�����������ƶ��е����)
// *************************************************************************** //
// ÿ�����������ƶ��е����
message PBWorldPlayer
{
	optional uint32	WorldID = 1;
	repeated uint32	RoleID	= 2;
};
message CMessageSyncGlobalPlayeNotify
{
	repeated PBWorldPlayer WorldPlayerList = 1; // ���ƶ��и���������ҵ���Ϣ																													
};