
// ������ٶ�����/������
option optimize_for = SPEED;

// core message id ö��ֵ
enum EMCoreMessageID
{
	ID_L2C_NOTIFY_LOGINERROR		= 0x0401; // ��½����֪ͨ
	ID_G2C_NOTIFY_GATEERROR			= 0x0402; // ���ش���֪ͨ
	ID_C2L_REQUEST_LOGINSERVER		= 0x0403; // �ͻ��˵�½����(loginserver)
	ID_L2C_NOTIFY_WAITFORQUEUE		= 0x0404; // ��¼������֪ͨ�ͻ����Ŷ� 
	ID_L2C_NOTIFY_REDIRECTGATE		= 0x0405; // ��½������֪ͨ�ͻ����ض���
	ID_C2G_REQUEST_LOGINGATE		= 0x0406; // ��½��������
	ID_G2C_RESPONSE_LOGINGATE		= 0x0407; // ��½���ػ�Ӧ
	ID_C2G_REQUEST_OBTAINCHAR		= 0x0408; // �ͻ��������ȡ����
	ID_G2C_NOTIFY_OBTAINCHAR		= 0x0409; // ����֪ͨ��ȡ����
	ID_G2C_NOTIFY_OBTAINCHARCOMPLTE = 0x040A; // ����֪ͨ��ȡ�������
	ID_C2G_REQUEST_ENTERGAME		= 0x040B; // �ͻ����������ؽ�����Ϸ
	ID_G2C_RESPONSE_ENTERGAME		= 0x040C; // ���ػ�Ӧ�ͻ��˽�����Ϸ
	ID_C2S_REQUEST_LOGINSCENE		= 0x040D; // �ͻ��������½����
	ID_S2C_RESPONSE_LOINGSCENE		= 0x040E; // ������Ӧ�ͻ��˵�½
	ID_C2S_REQUEST_RETURN2GATE		= 0x040F; // �ͻ������󷵻�����
	ID_S2C_RESPONSE_RETURN2GATE		= 0x0410; // ��Ӧ�ͻ��˷�������
	ID_C2G_REQUEST_CREATECHAR		= 0x0411; // ��������ɫ
	ID_G2C_RESPONSE_CREATECHAR		= 0x0412; // ��Ӧ������ɫ
	ID_C2G_REQUEST_DELETECHAR		= 0x0413; // ����ɾ����ɫ
	ID_G2C_RESPONSE_DELETECHAR		= 0x0414; // ��Ӧɾ����ɫ
	ID_S2C_NOTIFY_RECONNECTSCENE	= 0x0415; // ֪ͨ�������ӳ���
	ID_C2S_REQUEST_REDIRECTSCENE	= 0x0416; // �����ض��򳡾�
	ID_S2C_RESPONSE_REDIRECTSCENE	= 0x0417; // ��Ӧ�ض��򳡾�
	ID_C2S_REQUEST_LEAVEGAME		= 0x0418; // �����뿪��Ϸ
	ID_S2C_RESPONSE_LEAVEGAME		= 0x0419; // ��Ӧ�뿪��Ϸ
	ID_S2C_NOTIFY_KICK				= 0x041A; // ֪ͨ�ͻ�������
	ID_C2S_REQUEST_PING				= 0x041B; // �ͻ���ping������
	ID_S2C_RESPONSE_PING			= 0x041C; // ��������ping��Ӧ
	ID_G2S_NOTIFY_KICKPLAYER		= 0x041D; // ��������(�������ظ���½ʱ�ߵ���һ�����)
	ID_S2C_REDIRECT_ERR_CODE        = 0x041E;	
    ID_G2S_NOTIFY_LOGINQUEUE        = 0x041F;	// ����֪ͨ�ͻ����Ŷ�    
    ID_C2G_REQUEST_CHECKROLEPWD		= 0x0420;	// ������������
    ID_G2C_RESPONSE_CHECKROLEPWD	= 0x0421;	// �������Ļ�Ӧ
	ID_C2S_REQUEST_CLIENTINFO		= 0x0422;	// ���Ϳͻ���������Ϣ
	ID_S2G_CANCEL_LOGINQUEUE        = 0x0423;	// �ͻ���ȡ���Ŷ�
	ID_C2S_NOTIFY_CLIENTANTIBOTDATA	= 0x0424;	// �ͻ���->������ �������������
	ID_S2C_NOTIFY_SERVERANTIBOTDATA	= 0x0425;	// ������->�ͻ��� �������������
	ID_C2S_NOTIFY_CLIENTANTIBOTSTARTRET = 0x0426;// �ͻ���->������ �ͻ��˷�����������	
    ID_S2C_NOTIFY_DISCONNECT        = 0x0427;   // ������->�ͻ��� ֪ͨ�ͻ��˶Ͽ���������
    ID_S2C_NOTIFY_USERAUTH          = 0x0428;   // ������->�ͻ��� ������Ҫ�ͻ��������Ȩ��
    ID_C2S_REQUEST_USERAUTH         = 0x0429;   // �ͻ���->������ ��Ȩ����
    ID_S2C_RESPONSE_USERAUTH        = 0x0430;   // ������->�ͻ��� ��Ȩ��Ӧ
    
    ID_C2G_REQUEST_CANCELROLEDELETE	= 0x0431;	// �ͻ���->������ �ָ�ɾ����ɫ
    ID_G2C_RESPONSE_CANCELROLEDELETE= 0x0432;	// �ͻ���->������ �ָ�ɾ����ɫ

// 100304 MAOCY ADD-BEGIN
    ID_C2G_REQUEST_QUESTIONREQUIRE  = 0x0433;	// �ͻ���->������ ����������֤
    ID_G2C_RESPONSE_QUESTIONREQUIRE = 0x0434;	// ������->�ͻ��� ��������
    ID_C2G_REQUEST_QUESTIONANSWER   = 0x0435;	// �ͻ���->������ �������֤
    ID_G2C_RESPONSE_QUESTIONANSWER  = 0x0436;	// ������->�ͻ��� ������
// 100304 MAOCY ADD-END

// 100325 MAOCY ADD-BEGIN
   // �û���֤
   ID_C2A_REQUEST_CERTIFY       = 0x0440; // �û���ȫ�ַ�������֤����
   ID_A2C_RESPONSE_CERTIFY      = 0x0441; // �û���ȫ�ַ�������֤Ӧ��
   ID_A2L_REQUEST_CERTIFYQUERY  = 0x0442; // ȫ�ַ���������¼��������֤����
   ID_L2A_RESPONSE_CERTIFYQUERY = 0x0443; // ��¼��������ȫ�ַ�������֤Ӧ��
   ID_L2A_REQUEST_CERTIFYTOKEN  = 0x0444; // ��¼��������ȫ�ַ�������֤��������
   ID_A2L_RESPONSE_CERTIFYTOKEN = 0x0445; // ��¼��������ȫ�ַ�������֤����Ӧ��
   // ��ɫ��Ŀ��ѯ
   ID_L2G_REQUEST_ROLEQUERY     = 0x0446; // ��¼������ȥ���ط�������ѯ��ɫ��Ϣ����
   ID_G2L_RESPONSE_ROLEQUERY    = 0x0447; // ��¼������ȥ���ط�������ѯ��ɫ��ϢӦ��
   ID_L2A_NOTIFY_ROLEQUERY      = 0x0448; // ��¼��������ȫ�ַ�����֪ͨ��ɫ��Ϣ
   // ��������Ϣ֪ͨ
   ID_L2A_NOTIFY_ONLINESTATUS   = 0x0449; // ��������Ϣ֪ͨ
// 100325 MAOCY ADD-END


   ///////////////////////////////////
   // ��Ϣ��ת��Ӫ��ת������Ϣ����	
   // author�� qiufufu
   // date : 10-08-23
   //////////////////////////////////////

   ID_C2S_REQUEST_INVITE_CAMP			= 0x0450; // �ͻ�������ת��Ӫ
   ID_S2C_RSPONSE_INVITE_CAMP			= 0x0451; // ����˻ظ�ת��Ӫ �ѿ�ת����Ӫ�б�֪ͨ���ͻ���

   ID_C2S_REQUEST_CHANGE_CAMP			= 0x0452; // �ͻ���ѡ��һ����Ӫ��֪ͨ�����ת��Ӫ
   ID_S2C_RSPONSE_CHANGE_CAMP			= 0x0453; // ����˻ظ��ͻ��� ת��Ӫ�Ƿ�ɹ�

   ID_S2C_NOTIFY_CHANGE_CAMP_SUCCESED   = 0x0454; // ��	��Ƶ��֪ͨ���ת��Ӫ�ɹ�
   ID_S2G_CHANGE_CAMP_NOTICE            = 0x0455; // scenserver ת���ɹ���֪ͨ gateserver

   ID_C2S_REQUEST_CHANGE_CAMP_CONDITION = 0x0456; // �ͻ��˷��Ͳ�ѯ��Ӫת������
   ID_S2C_RSPONSE_CHANGE_CAMP_CONDITION = 0x0457; // ����˻ظ���ѯ��Ӫת������

};

// ·����Ϣ
message CMessageRouter
{
	enum MSGID { MSGROUTER = 0x0200; };

	enum EMRouterType
	{
		ROUTER_NAME = 0;
		ROUTER_CHAR = 1;
	};

	enum EMRouterReason
	{
		REASON_SUCCESS	= 0;		// ת���ɹ�
		REASON_REDIRECT	= 1;		// ת��ʱ��������ڿ糡��
		REASON_OFFLINE	= 2;		// ת��ʱ����Ҳ�����
	};


	optional uint32	RouterReason	= 1;	// �Ƿ�ת���ɹ�
	optional uint32	Send2Player		= 2;	// �Ƿ�Ҫ���͸��ͻ���
	optional uint32	SendBack		= 3;	// �Ƿ�ط���Ϣ
	optional uint32	RouterType		= 4;	// ת������
	optional uint32 SrcCharID		= 5;	// ���ͽ�ɫID, ���Ŀ��Ϊ0, ��ʾ���͸�ȫ������
	optional uint32 DesCharID		= 6;	// Ŀ���ɫID
	optional string	SrcName			= 7;	// ���ͽ�ɫ����
	optional string	DesName			= 8;	// Ŀ���ɫ����
};


message CMessageRedirectErr
{
	optional int32 ErrorCode  = 		1; 
	optional uint32 CharID     = 		2; 
}

// *************************************************************************** //
// CMessageLoginErrorNotice ��½������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageLoginErrorNotice
{
	optional string ErrorString  = 		1; 		// �����ַ���
	optional int32 ErrorCode	 = 		2; 		// ϵͳ������
};


// *************************************************************************** //
// CMessageGateErrorNotice ���ط����� -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageGateErrorNotice 
{
	optional int32 KeepAlive     = 		1;          // �Ƿ���ͻ��˶Ͽ�����
	optional string ErrorString	 = 		2; 			// �����ַ���
	optional int32 ErrorCode	 = 		3; 			// ϵͳ������
}


// ********************************************************************** //
// CMessageLoginServerRequest����Ϸ�ͻ��� -> ��½������ 
// �ͻ��˵�½����
// ********************************************************************** //
message CMessageLoginServerRequest
{
   // 103031 [GS] MAOCY ADD-BEGIN
   enum EType
   {
      TYPE_CLIENT = 0; // �ͻ�����֤
      TYPE_GLOBAL = 1; // ȫ�ַ�������֤
   };
   // 103031 [GS] MAOCY ADD-END
   optional string UserName          =  1; // �������
   optional string Md5Code           =  2; // �ͻ���MD5�� 
   optional uint32 TaskVersion       =  3; // �����ļ��汾��
   optional string UserPsw           =  4; // �������
   optional uint32 Version           =  5; // �ͻ��˰汾��	
   optional int32  SourceID          =  6; // ��װԴ
   optional uint32 TemplateVersion   =  7; // ģ���ļ��汾��
   optional uint32 MatrixType        =  8; // ��Ȩ��ʽ
   optional string MatrixCode        =  9; // ��Ȩ��
   optional string Mac               = 10; // �ͻ���MAC��ַ
   optional string MatrixCoord       = 11; // �ܱ�������
   // 103031 [GS] MAOCY ADD-BEGIN
   optional EType  type              = 12; // ��֤����
   optional uint32 accountId         = 13; // �˺ű��
   optional uint32 token             = 14; // ����
   // 103031 [GS] MAOCY ADD-END
   optional uint32 cpuid             = 15; // CPUID
   optional uint32 diskid            = 16; // DISK����
};


// ********************************************************************** //
// CMessageLoginServerResponse����½������ -> ��Ϸ�ͻ���
// ��½������֪ͨ�ͻ����Ŷ�
// ********************************************************************** //
message CMessageWaitForLoginNotice
{
	optional uint32	QueueNumber	 = 		1; 	// �Ŷ�˳��
};


// ********************************************************************** //
// CMessageRedirectGateNotice����½������ -> ��Ϸ�ͻ���
// ֪ͨ�ͻ����ض���
// ********************************************************************** //
message CMessageRedirectGateNotice
{
	optional string	Address		 = 		1; 
	optional uint32 OtherClient	 = 		2; 
	optional uint32 LoginToken	 = 		3; 
	optional uint32	AccountID	 = 		4; 
	optional uint32	CleanCSkey	 =		5; // �Ƿ����cskey
};


// ********************************************************************** //
// CMessageEnterGateRequest�����ط����� -> ��Ϸ�ͻ���   
// ********************************************************************** //
message CMessageLoginGateRequest
{

	optional uint32 LoginToken	 = 		1; 		// ��½����
	optional uint32	AccountID	 = 		2; 		// �ʺ�ID
	optional uint32 TemplateVer	 = 		3; 		// ģ���
};


// ********************************************************************** //
// CMessageLoginGateResponse�����ط����� -> ��Ϸ�ͻ���   
// ********************************************************************** //
message CMessageLoginGateResponse
{
	optional string     ErrorString =  1; 		// �����ַ���( ֻҪ�����ַ�����Ϊ�գ�����ʾ�ַ��� )
	optional int32     ErrorCode   =  2; 		// ������
	optional int32     GateWayID   =  3; 		// ����ID
};


// ********************************************************************** //
// CMessageObtainCharRequest����Ϸ�ͻ��� -> ���ط����� 
// ********************************************************************** //
message CMessageObtainCharRequest
{
};


// 
message PBCharProfile
{
	optional uint32	CharID				= 		1; 	// ��ɫID
	optional uint32 LineID				= 		2; 	// ������ID
	optional uint32 Sex					= 		3; 	// ��ɫ�Ա�
	optional uint32 HairColour			= 		4; 	// ��ɫ��ɫ
	optional uint32 Exp					= 		5; 	// ��ɫ����
	optional uint32 Level				= 		6; 	// ��ɫ�ȼ�
	optional uint32 AccountID			= 		7; 	// �ʺ�ID
	optional uint32 LastLogin			= 		8; 	// ��ɫ�ϴε�½ʱ��
	optional uint32 OnlineTime			= 		9; 	// ��ɫ����ʱ��
	optional uint32 Metier				= 		10; 	// ��ɫְҵ
	optional uint32 HairType			= 		11; 	// ��ɫ����
	optional uint32 FaceType			= 		12; 	// ��ɫ����
	optional uint32 MapID				= 		13; 	// ���ڵ�ͼID
	optional string CharName			= 		14; 	// ��ɫ����
	optional uint32 Nationality			= 		15; 	// ��ɫ����
	optional uint32	RoleDeleteStatus	=		16;		// ��ɫɾ��״̬EM_RoleDelteStatus
	optional uint32	DeleteStatusLeftTime=		17;		// ��ǰ��ɫɾ��״̬��ʣ��ʱ��  	
	optional uint32	PasswordUsed		=		18;		// �Ƿ�ʹ���˲Ʋ�����0Ϊû��ʹ������Ϊʹ��	
};



// ********************************************************************** //
// CMessageObtainCharNotice�����ط����� -> ��Ϸ�ͻ���
// ��ɫ�ſ�֪ͨ
// ********************************************************************** //
message CMessageObtainCharNotice
{
	repeated PBCharProfile	CharProfile	 = 		1;
	optional uint32			LastLoginIP	 =		2;		// �ϴεĵ�¼IP 
	optional uint32			LoginIP		 =		3;		// ���εĵ�¼IP
};


// ********************************************************************** //
// CMessageObtainCharCompleteNotice�����ط����� -> ��Ϸ�ͻ���
// ��ɫ�ſ���ȡ���֪ͨ
// ********************************************************************** //
message CMessageObtainCharCompleteNotice
{
};



// ********************************************************************** //
// CMessageEnterGameRequest����Ϸ�ͻ��� -> ���ط����� 
// ********************************************************************** //
message CMessageEnterGameRequest
{
	optional uint32 AccountID  = 	1;      // �ʺ�ID
	optional uint32 LineID	 = 		2; 		// ��������ID
	optional uint32 MapID	 = 		3; 		// ��ͼID
	optional uint32 CharID	 = 		4; 		// ��ɫID
    optional string Mac      =      5;      // �ͻ���MAC��ַ
};


// ********************************************************************** //
// CMessageEnterGameResponse�����ط����� -> ��Ϸ�ͻ��� 
// ********************************************************************** //
message CMessageEnterGameResponse
{
	optional string SceneName	 = 		1; 
	optional string	Address		 = 		2; 
	optional uint32	ClearDialog	 =		3;	// ����Ի�
};


// ********************************************************************** //
// CMessageLoginSceneRequest����Ϸ�ͻ��� -> ����������
// ********************************************************************** //
message CMessageLoginSceneRequest
{
	optional uint32 AccountID		 = 		1; 
	optional uint32 CharID			 = 		2; 
	optional uint32 LoginToken		 = 		3; 
};


// ********************************************************************** //
// CMessageEnterSceneResponse������������ -> ��Ϸ�ͻ��� 
// ********************************************************************** //
message CMessageLoginSceneResponse
{
	optional bytes	Key			= 1;	// ��Կ16, Լ���׳ɣ� 16λ
	optional uint32 CSDialogID	= 2;	// �ỰID
	optional uint64 ServerTime	= 3;	// ������ʱ��,����
};

// ********************************************************************** //
// CMessageEnterSceneResponse����Ϸ�ͻ��� -> ����������
// �ͻ������󷵻�����
// ********************************************************************** //
message CMessageReturn2GateRequest
{
};

// ********************************************************************** //
// CMessageReturnToGateResponse������������  -> ��Ϸ�ͻ���
// �ͻ������󷵻�����
// ********************************************************************** //
message CMessageReturn2GateResponse
{
	optional uint32	ReturnType = 1; // 0 ��ʾ�������� 1��ʾҪ����ԭ�����أ��ͻ���Ҫ��һЩ����
};

// ********************************************************************** //
// CMessageCreateCharRequest����Ϸ�ͻ��� -> ���ط�����
// �����������ɫ
// ********************************************************************** //
message CMessageCreateCharRequest
{
	optional PBCharProfile	Profile		 = 		1; 		// ��ɫ��Ҫ
};

// ********************************************************************** //
// CMessageCreateCharResponse�����ط����� -> ��Ϸ�ͻ���
// �����������ɫ��Ӧ
// ********************************************************************** //
message CMessageCreateCharResponse
{
	optional uint32		CharID  = 		1; 
};



// ********************************************************************** //
// CMessageDeleteCharRequest����Ϸ�ͻ��� -> ���ط�����
// �����������ɫ
// ********************************************************************** //
message CMessageDeleteCharRequest
{
	optional uint32		PasswdType  = 		1; 
	optional string		Passwd	 = 		2; 
	optional uint32		CharID	 = 		3; 
};

// ********************************************************************** //
// CMessageDeleteCharResponse�����ط����� -> ��Ϸ�ͻ���
// �����������ɫ��Ӧ
// ********************************************************************** //
message CMessageDeleteCharResponse
{
	optional uint32		CharID					=	1;
	optional uint32		Errcode					=	2;	
	optional uint32		DeleteStatus			=	3;	// ɾ��״̬
	optional uint32		DeleteStatusLeftTime	=	4;	// ��ǰɾ��״̬��ʣ��ʱ��
};

// ********************************************************************** //
// CMessageRedirectNotice����Ϸ������ -> ��Ϸ�ͻ���
// ֪ͨ�������������Ϸ������
// ********************************************************************** //
message CMessageReconnectSceneNotice 
{
	optional uint32 MapID		 = 		1; 
	optional uint32 LineID		 = 		2; 
	optional string Address		 = 		3; 
	optional uint32 PosY		 = 		4; 
	optional uint32 PosX		 = 		5; 
	optional string CountryName	 = 		6; 
	optional string MapName		 = 		7; 	
};

// ********************************************************************** //
// CMessageLoginSceneRequest����Ϸ�ͻ��� -> ����������
// ********************************************************************** //
message CMessageRedirectSceneRequest
{
	optional uint32		AccountID	 = 		1; 
	optional uint32		LoginToken	 = 		2; 
	optional uint32		CharID		 = 		3; 
};

// ********************************************************************** //
// CMessageRedirectSceneResponse����Ϸ�ͻ��� -> ����������
// ********************************************************************** //
message CMessageRedirectSceneResponse
{
};


// ********************************************************************** //
// CMessageLeaveGameRequest����Ϸ�ͻ��� -> ����������
// ********************************************************************** //
message CMessageLeaveGameRequest
{
	optional uint32 LeaveType	 = 		1;  // ���߷�ʽ��0 ��ȫ���ߣ�1 ǿ������
};

// ********************************************************************** //
// CMessageLeaveGameResponse������������ -> ��Ϸ�ͻ���
// ********************************************************************** //
message CMessageLeaveGameResponse 
{
};

// ********************************************************************** //
// CMessageKickoutNotice������������ -> ��Ϸ�ͻ���
// ********************************************************************** //
message CMessageKickoutNotice
{
	optional uint32 reason  = 		1; 
	optional uint32 param  = 		2; 
};

// ********************************************************************** //
// CMessageClientPingServerRequest�� ��Ϸ�ͻ��� -> ������
// ********************************************************************** //
message CMessageClientPingServerRequest
{

	optional uint32 CharID			 = 		1; 	// ��ɫID
	optional uint32 LatestPingValue	 = 		2; 	// client���һ��pingֵ( server���ſͻ��˵�ֵ,���粨��С�Ļ��ȽϾ�ȷ )
	optional uint64 ClientLocalTime	 = 		3; 	// client����ʱ��
};


// ********************************************************************** //
// CMessageClientPingServerResponse�������� -> ��Ϸ�ͻ���
// ********************************************************************** //
message CMessageClientPingServerResponse
{
	optional uint32 CharID			 = 		1; 	// ��ɫID
	optional uint64 ClientLocalTime	 = 		2; 	// ������Ϣ�е�client����ʱ�䣬������ֱ�ӻ���
	optional uint64 ServerTime		 =		3;	// ������ʱ��,����
};

// ********************************************************************** //
// CMessageGateKickPlayerNotify�������� -> ��Ϸ�ͻ���
// ********************************************************************** //
message CMessageGateKickPlayerNotify
{
	optional uint32	CharID		 = 		1; 	// ��ɫID
	optional uint32	KickReason	 = 		2; 	// ����ԭ��
};

// ********************************************************************** //
// CMessageQueuePlayerNotify�����ط����� -> ��Ϸ�ͻ���
// ********************************************************************** //
message CMessageQueuePlayerNotify
{
	optional uint32	CountInScene	 = 		1; 	// Ŀǰ��������
	optional uint32	ElapsSeconds	 = 		2; 	// �ͻ����Ŷ��Ѿ��Ŷӵ�ʱ������
	optional uint32	NeedSeconds	 = 		3; 	// �ͻ��˴����Ҫ�೤ʱ���Ŷ�
	optional uint32	YourPosition	 = 		4; 	// Ŀǰ�Ŷ�����
	optional uint32	CountInQueue	 = 		5; 	// Ŀǰ�Ŷ�����
};

message CMessagePlayerCancelLoginQueue
{

};

// ********************************************************************** //
// CMessageCheckRolePwdRequest�� ��Ϸ�ͻ��� -> ���ط����� ɾ����ɫʱ���2�����������
// ********************************************************************** //
message CMessageCheckRolePwdRequest
{
	optional uint32 CharID	  = 		1; 
	optional string Password  = 		2; 	
};

// ********************************************************************** //
// CMessageCheckRolePwdRequest�� ���ط����� -> ��Ϸ�ͻ��� ɾ����ɫʱ���2������Ļ�Ӧ
// ********************************************************************** //
message CMessageCheckRolePwdResponse
{
	optional uint32 Errcode  = 		1; 	// 0��ʾ������ȷ ������ʾ�������
};

//**********************************
// CMessageSendClientInfoRequest ��Ϸ�ͻ��� -> ���������� ���Ϳͻ���������Ϣ
//**********************************

message CMessageSendClientInfoRequest
{
	optional string		HostInfo	 = 		1; 	// ������Ϣ
	optional string		MacAddr		 = 		2; 	// ����Mac��ַ
};


//**********************************
// CMessageSendAntiBotDataToServerNotify ��Ϸ�ͻ��� -> ���������� ���Ϳͻ��˷����������Ϣ
//**********************************
message CMessageSendAntiBotDataToServerNotify
{
	optional uint32		Length		 = 		1; 	// ���ݳ���
	optional bytes		ClientData	 = 		2; 	// ����
};


//**********************************
// CMessageSendAntiBotDataToClientNotify	��Ϸ������ -> �ͻ��� ���ͷ����������������Ϣ
//**********************************
message CMessageSendAntiBotDataToClientNotify
{
	optional bytes		ServerData	 = 		1; 	// ����
	optional uint32		Length		 = 		2; 	// ���ݳ���
};


//**********************************
// CMessageClientAntiBotStartRetNotify	��Ϸ�ͻ��� -> ������ ���Ϳͻ��˷����ģ����������ֵ
//**********************************
message CMessageClientAntiBotStartRetNotify
{
	optional uint32		StartRet	 = 		1; 	// �����ģ����������ֵ
};

//**********************************
// CMessageDisconnectNotify	            ������ -> �ͻ��� ���ͷ����������Ͽ�������Ϣ, �û��������Ŀ��ơ��ͻ��˲���Ҫ��Ӧ
//**********************************
message CMessageDisconnectNotify
{
};

// ��������ͻ��˷���ĳ��Ϊ��Ҫ���м�Ȩ��֪ͨ
message CMessageUserAuthNotify
{
    optional uint32 ActionID = 1;
    optional uint32 AuthType = 2;
};

// �ͻ��˸��ݼ�Ȩ���;���Ҫ�������β���, ������ҵĲ������ظ�������
message CMessageUserAuthRequest
{
    optional uint32 ActionID = 1;
    optional uint32 AuthValue = 2;
};

// �����������Ƿ�����˲���
message CMessageUserAuthResponse
{
    optional uint32 ActionID = 1;
    optional uint32 OK = 2;
};


// �ָ�ɾ����ɫ������
message CMessageCancelDeleteRoleRequest
{
	 optional uint32 RoleID = 1;
};

// �ָ�ɾ����ɫ�Ļ�Ӧ
message CMessageCancelDeleteRoleResponse
{
	optional uint32 Errcode		= 1;	// ������
	optional uint32 RoleID		= 2;	// ��ɫID	
};

// 100304 MAOCY ADD-BEGIN
//============================================================
// �ͻ���->������ ����������֤
message CMessageQuestionRequireRequest
{
};

//============================================================
// ������->�ͻ��� ��������
message CMessageQuestionRequireResponse
{
	//------------------------------------------------------------
	// ״̬
	enum EStatus
	{
		STATUS_SUCCESS	= 0;		// ����Ҫ�ش�
		STATUS_WAIT = 1;		    // �ȴ��ش�
	};
	//------------------------------------------------------------
	optional EStatus Status    = 1; // ״̬
	optional uint32 QuestionId = 2; // ������
	optional string Question   = 3; // ��������
	optional bytes OptionA     = 4; // ѡ��A
	optional bytes OptionB     = 5; // ѡ��B
	optional bytes OptionC     = 6; // ѡ��C
	optional bytes OptionD     = 7; // ѡ��D
};

//============================================================
// �ͻ���->������ �������֤
message CMessageQuestionAnswerRequest
{
	//------------------------------------------------------------
	// ״̬
	enum EStatus
	{
		STATUS_SUCCESS	= 0;		// ����Ҫ�ش�
		STATUS_WAIT = 1;		    // �ȴ��ش�
	};
	//------------------------------------------------------------
	optional uint32 QuestionId = 1; // ������
	optional bytes Answer      = 2; // �ش���
};

//============================================================
// ������->�ͻ��� ������
message CMessageQuestionAnswerResponse
{
	//------------------------------------------------------------
	// ״̬
	enum EStatus
	{
		STATUS_SUCCESS	= 0;		// ����Ҫ�ش�
		STATUS_WAIT = 1;		    // �ȴ��ش�
	};
	//------------------------------------------------------------
	optional EStatus Status    = 1; // ״̬
};
// 100304 MAOCY ADD-END

// 100325 MAOCY ADD-BEGIN
//============================================================
// ��֤������״̬
message CMessageLoginServerInfo{
   optional uint32 id     = 1; // ���������
   optional uint32 flag   = 2; // ��������־
   optional uint32 status = 3; // ������״̬
   optional uint32 count  = 4; // ��ɫ����
};

//============================================================
// �û���ȫ�ַ�������֤����
message CMessageCertifyRequest{
   optional string passport        =  1; // ��¼�˺�
   optional string password        =  2; // ��¼����
   optional string md5Code         =  3; // �ͻ���MD5�� 
   optional string mac             =  4; // �ͻ���MAC��ַ
   optional int32  sourceId        =  5; // ��װԴ
   optional uint32 version         =  6; // �ͻ��˰汾��	
   optional uint32 taskVersion     =  7; // �����ļ��汾��
   optional uint32 templateVersion =  8; // ģ���ļ��汾��
   optional uint32 matrixType      =  9; // ��Ȩ��ʽ
   optional string matrixCode      = 10; // ��Ȩ��
   optional string matrixCoord     = 11; // �ܱ�������
};

//============================================================
// �û���ȫ�ַ�������֤Ӧ��
message CMessageCertifyResponse
{
   //------------------------------------------------------------
   // ״̬
   enum EStatus
   {
      STATUS_SUCCESS = 0; // ��֤�ɹ�
      STATUS_INVALID = 1; // ��֤ʧ��
      STATUS_FAILURE = 2; // ִ��ʧ��
   };
   //------------------------------------------------------------
   optional EStatus                 status    = 1; // ״̬
   optional uint32                  playerId  = 2; // ��ұ��
   optional uint32                  accountId = 3; // �˺ű��
   optional uint32                  token     = 4; // ����
   repeated CMessageLoginServerInfo servers   = 5; // ��������Ϣ
   optional uint32                  errorCode = 6; // �������
};

//============================================================
// ȫ�ַ���������¼��������֤����
message CMessageCertifyQueryRequest
{
   optional uint32 playerId        =  1; // ��ұ��
   optional uint32 accountId       =  2; // �˺ű��
   optional string passport        =  3; // ��¼�˺�
   optional string password        =  4; // ��¼����
   optional string md5Code         =  5; // �ͻ���MD5�� 
   optional uint32 playerHost      =  6; // �ͻ��˵�ַ
   optional uint32 playerPort      =  7; // �ͻ��˶˿�
   optional string playerMac       =  8; // �ͻ���MAC��ַ
   optional int32  sourceId        =  9; // ��װԴ
   optional uint32 version         = 10; // �ͻ��˰汾��	
   optional uint32 taskVersion     = 11; // �����ļ��汾��
   optional uint32 templateVersion = 12; // ģ���ļ��汾��
   optional uint32 matrixType      = 13; // ��Ȩ��ʽ
   optional string matrixCode      = 14; // ��Ȩ��
   optional string matrixCoord     = 15; // �ܱ�������
};

//============================================================
// ��¼��������ȫ�ַ�������֤Ӧ��
message CMessageCertifyQueryResponse
{
   //------------------------------------------------------------
   // ״̬
   enum EStatus
   {
      STATUS_SUCCESS = 0; // ��֤�ɹ�
      STATUS_FAILURE = 1; // ִ��ʧ��
   };
   //------------------------------------------------------------
   optional EStatus status    = 1; // ״̬
   optional uint32  playerId  = 2; // ��ұ��
   optional uint32  accountId = 3; // �˺ű��
   optional uint32  errorCode = 4; // �������
};

//============================================================
// ��¼��������ȫ�ַ�������֤��������
message CMessageCertifyTokenRequest
{
   optional uint32 playerId  = 1; // ��ұ��
   optional uint32 accountId = 2; // �˺ű��
   optional uint32 token     = 3; // ��¼�˺�
   optional uint32 handle    = 4; // ���
};

//============================================================
// ��¼��������ȫ�ַ�������֤����Ӧ��
message CMessageCertifyTokenResponse
{
   //------------------------------------------------------------
   // ״̬
   enum EStatus
   {
      STATUS_SUCCESS = 0; // ��֤�ɹ�
      STATUS_FAILURE = 1; // ִ��ʧ��
   };
   //------------------------------------------------------------
   optional EStatus status          =  1; // ״̬
   optional uint32  playerId        =  2; // ��ұ��
   optional uint32  accountId       =  3; // �˺ű��
   optional uint32  handle          =  4; // ���
   optional string  passport        =  5; // ��¼�˺�
   optional string  password        =  6; // ��¼����
   optional uint32  playerHost      =  7; // �ͻ��˵�ַ
   optional uint32  playerPort      =  8; // �ͻ��˶˿�
   optional string  playerMac       =  9; // �ͻ���MAC��ַ
   optional string  md5Code         = 10; // �ͻ���MD5�� 
   optional int32   sourceId        = 11; // ��װԴ
   optional uint32  version         = 12; // �ͻ��˰汾��	
   optional uint32  taskVersion     = 13; // �����ļ��汾��
   optional uint32  templateVersion = 14; // ģ���ļ��汾��
   optional uint32  matrixType      = 15; // ��Ȩ��ʽ
   optional string  matrixCode      = 16; // ��Ȩ��
   optional string  matrixCoord     = 17; // �ܱ�������
};

//============================================================
// ��¼������ȥ���ط�������ѯ��ɫ��Ϣ����
message CMessageRoleQueryRequest
{
   optional uint32 playerId  = 1; // ��ұ��
   optional uint32 accountId = 2; // �˺ű��
};

//============================================================
// ���ط���������¼��������ѯ��ɫ��Ϣ����Ӧ��
message CMessageRoleQueryResponse
{
   //------------------------------------------------------------
   // ״̬
   enum EStatus
   {
      STATUS_SUCCESS = 0; // �ɹ�
      STATUS_FAILURE = 1; // ʧ��
   };
   //------------------------------------------------------------
   optional EStatus status    = 1; // ״̬
   optional uint32  playerId  = 2; // ��ұ��
   optional uint32  accountId = 3; // �˺ű��
   optional uint32  roleCount = 4; // ��ɫ����
};

//============================================================
// ��¼��������ȫ�ַ�����֪ͨ��ɫ��Ϣ֪ͨ
message CMessageRoleQueryNotify
{
   //------------------------------------------------------------
   // ״̬
   enum EStatus
   {
      STATUS_SUCCESS = 0; // �ɹ�
      STATUS_FAILURE = 1; // ʧ��
   };
   //------------------------------------------------------------
   optional EStatus status    = 1; // ״̬
   optional uint32  playerId  = 2; // ��ұ��
   optional uint32  accountId = 3; // �˺ű��
   optional uint32  loginId   = 4; // �˺ű��
   optional uint32  roleCount = 5; // ��ɫ����
};

//============================================================
// ��������Ϣ֪ͨ
message CMessageOnlineStatusNotify
{
   optional uint32 serverId = 1; // ���������
   optional uint32 total    = 2; // ������
   optional uint32 current  = 3; // ��ǰ����
};
// 100325 MAOCY ADD-END


///////////////////////////////////
// ��Ϣ��ת��Ӫ��ת������Ϣ����	
// author�� qiufufu
// date : 10-08-23
//////////////////////////////////////

message CMessageInviteCampRequest// �ͻ�������ת��Ӫ
{
	optional uint32  playerId        = 1; // ��ұ��
	optional uint32  currentCampId   = 2; //��ҵ�ǰ����Ӫid
	optional uint32  npcId			 = 3; //npcid
};
message  CampLevel
{
	optional uint32 camp_id			 = 1;	// ��ӪID
	optional uint32 weak_level		 = 2;	// ��Ӫ�ȼ�
};
message CMessageInviteCampResponse			// ����˻ظ�ת��Ӫ �ѿ�ת����Ӫ�б�֪ͨ���ͻ���
{
	repeated CampLevel  camp_list     = 1;  //��ת��Ӫ���б�
	optional uint32		errorcode       = 2;  //0 Ϊ�ɹ�������Ϊʧ��

};

message CMessageChangeSingleCampRequest // �ͻ���ѡ��һ����Ӫ��֪ͨ�����ת��Ӫ
{
	optional uint32  playerId        = 1; // ��ұ��
	optional  uint32 crrentCampId    = 2; //��ǰ����Ӫid
	optional  uint32 targetCampId    = 3; //Ŀ�����Ӫid
	optional uint32  npcId			 = 4; //npcid
};

message CMessageChangeSingleCampResponse// ����˻ظ��ͻ��� ת��Ӫ�Ƿ�ɹ�
{
	optional uint32		 campId			 = 1; //ת�������Ӫid 
	optional uint32		 errorcode		 = 2; //0Ϊ�ɹ�������Ϊʧ��
	optional uint32      playerId		 = 3; //��ɫ id

};

message CMessageChangeCampSuccesNotify // ����Ƶ��֪ͨ���ת��Ӫ�ɹ�
{	
	optional string  playerName  = 1; // �������
	optional uint32  campId      = 2; // �ɹ�ת�����Ӫ 
	optional uint32  srcCampId   = 3; // ԭʼ�����Ӫid
	optional uint32  playerId    = 4; // ���id

};
message CMessageChangeCamp2GateNotice //scenserver ת���ɹ���֪ͨ gateserver
{

	optional uint32  playerId    = 1; // ��ұ��
	optional uint32  campId		 = 2; //���ת�������Ӫid
};

message CMessageChangeCampConditionRequest // �ͻ��˷��Ͳ�ѯ��Ӫת������
{
	optional uint32  playerId    = 1; //��ұ��
	optional uint32  npcId		 = 2; //npcid
};

message CMessageChangeCampConditionResponse // ����˻ظ���ѯ��Ӫת������
{
	    
	optional uint32  isHaveTeam		 = 1; //�Ƿ������
	optional uint32  isHaveFamily	 = 2; //�Ƿ��м���
	optional uint32  isHaveCountry	 = 3; //�Ƿ��й���
	optional uint32  isHaveMaster    = 4; //�Ƿ���ʦͽ
	optional uint32  isHaveMarriage  = 5; //�Ƿ��н��
	optional uint32  isHavePayMail   = 6; //�Ƿ��и����ʼ�
	optional uint32  ishaveEnoughLevel =7; //�Ƿ�ﵽ�㹻�ĵȼ�
	optional uint32  errorcode		 = 8; //0Ϊ�ɹ�������Ϊʧ��
	optional uint32	 isHaveSworn	 = 9;	// �Ƿ��н��
};


