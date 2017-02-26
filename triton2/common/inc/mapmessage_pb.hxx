
// ������ٶ�����/������
option optimize_for = SPEED;


// mapmessage��Ϣ��ID��Χ(0x0C00 -- 0x0CFF)
enum MAP_MSG_ID
{
	ID_C2S_NOTICE_ENTITYPATH					= 0x0C01; // ͨ��ʵ���ƶ�֪ͨ
	ID_S2C_NOTICE_ENTITYSTOP					= 0x0C02; // ͨ��ʵ��ֹͣ�ƶ�֪ͨ
	ID_S2C_NOTICE_DESTROYENTITY					= 0x0C03; // ʵ������֪ͨ
	ID_S2C_NOTICE_YOURMAPDATA					= 0x0C04; // ֪ͨ��ҵ�ͼ����
	ID_S2C_NOTICE_TELEPORT						= 0x0C05; // ʵ�崫��֪ͨ 
	ID_C2S_REQUEST_PLAYERPATH					= 0x0C06; // ����ƶ�����
	ID_C2S_REQUEST_PLAYERSTOP					= 0x0C07; // ���ֹͣ����
	ID_S2C_NOTICE_ENTITYPOSRESET				= 0x0C08; // ʵ����������֪ͨ
	ID_S2C_NOTICE_CANNTMOVE						= 0x0C09; // ʵ�岻���ƶ�֪ͨ
	ID_C2S_REQUEST_PETPATH						= 0x0C0A; // pet�ƶ�����
	ID_C2S_REQUEST_PETSTOP						= 0x0C0B; // petֹͣ����
};


// *************************************************************************** //
// CMessageDestroyEntityNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageDestroyEntityNotice
{
	repeated uint32 EntityID  = 		1; 
};

// *************************************************************************** //
// CMessageYourMapDataNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageYourMapDataNotice
{
	optional uint32 MotionState  = 	1; 
	optional uint32 MapID  = 		2; 
	optional uint32 LineID  = 		3; 
	optional uint32 PosX  = 		4; 
	optional uint32 CharID  = 		5; 
	optional string MapName  = 		6; 
	optional uint32 AliveState  = 	7; 
	optional uint32 PosY  = 		8; 
	optional uint32 Direction  = 	9; 
	optional string CountryName  = 	10; 
	optional uint32 VirtualMapID =	11;
};

// *************************************************************************** //
// CMessageTeleportNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageTeleportNotice
{
	optional uint32 PosX  = 		1; 
	optional uint32 PosY  = 		2; 
};


// *************************************************************************** //
// CMessagePlayerPathRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessagePlayerPathRequest
{
	optional uint32 SrcPosY  = 		1; 
	optional uint32 LineID  = 		2; 
	optional uint32 DesPosX  = 		3; 
	optional uint32 Direction  = 	4; 
	optional uint32 SrcPosX  = 		5; 
	optional uint32 DesPosY  = 		6; 
	optional uint32 MapID  = 		7; 
	optional uint64 TimeCheck	=		8;
};


// *************************************************************************** //
// CMessagePlayerStopRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessagePlayerStopRequest
{
	optional uint32 PosY  = 		1; 
	optional uint32 LineID  = 		2; 
	optional uint32 Direction  = 	3; 
	optional uint32 PosX  = 		4; 
	optional uint32 MapID  = 		5; 
	optional uint64	TimeCheck	=	6;
};


// *************************************************************************** //
// CMessageEntityPathNotice ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageEntityPathNotice
{
	optional uint32 EntityID  = 	1; 
	optional uint32 SrcPosY  = 		2; 
	optional uint32 NetSpeed  = 	3; 
	optional uint32 Direction  = 	4; 
	optional uint32 DesPosX  = 		5; 
	optional uint32 DesPosY  = 		6; 
	optional uint32 SrcPosX  = 		7; 
};

// *************************************************************************** //
// CMessageEntityStopNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageEntityStopNotice
{
	optional uint32 Direction  =	1; 
	optional uint32 NetSpeed  = 	2; 
	optional uint32 EntityID  = 	3; 
	optional uint32 PosX  = 		4; 
	optional uint32 PosY  = 		5; 
};



// *************************************************************************** //
// CMessageEntityPosReSetCallBack ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageEntityPosReSetCallBack
{
	optional uint32 Y  = 		1; 
	optional uint32 X  = 		2; 
	optional uint32 EntityID  = 3; 
};

// *************************************************************************** //
// CMessagePlayerCanntMoveCallBack ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessagePlayerCanntMoveCallBack
{
};



// *************************************************************************** //
// CMessagePetPathRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessagePetPathRequest
{
	optional uint32 SrcPosY  = 		1; 
	optional uint32 LineID  = 		2; 
	optional uint32 DesPosX  = 		3; 
	optional uint32 Direction  = 	4; 
	optional uint32 SrcPosX  = 		5; 
	optional uint32 DesPosY  = 		6; 
	optional uint32 MapID  = 		7;
	optional uint32 EntityID	=	8; // ʵ��ID
};


// *************************************************************************** //
// CMessagePetStopRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessagePetStopRequest
{
	optional uint32 PosY		= 	1; 
	optional uint32 LineID		= 	2; 
	optional uint32 Direction	= 	3; 
	optional uint32 PosX		= 	4; 
	optional uint32 MapID		= 	5; 
	optional uint32 EntityID	=	6; // ʵ��ID
};
