// ������ٶ�����/������
option optimize_for = SPEED;

enum ACTIVITY_MSG_ID
{
	
	
	ID_C2S_REQUEST_CHECKANSWER					= 0x3001;		// �ͻ���->������ ������Ŀ��	
	ID_S2C_RESPONSE_CHECKANSER					= 0x3002;		// ������->�ͻ��� ������Ŀ�𰸵Ļظ�
	ID_C2S_NOTIFY_QUESTIONTIMEREND				= 0x3003;		// �ͻ���->������ �������ʱ�䵽��֪ͨ��npc��
	ID_S2C_NOTIFY_QUESTIONNEW					= 0x3004;		// ������->�ͻ��� ��������Ŀ��֪ͨ
	ID_S2C_NOTIFY_ENDANSWER						= 0x3005;		// ������->�ͻ��� �������		
	ID_C2S_NOTIFY_USEQUESTIONPAPER				= 0x3006;		// �ͻ���->������ ʹ������֪ͨ�����
	ID_C2S_NOTIFY_IFANSWERNOW					= 0x3007;		// �ͻ���->������ �Ƿ����ϻش�����(���)	
	ID_C2S_NOTIFY_IFBEGINQUEST					= 0x3008;		// �ͻ���->������ �Ƿ�ʼ�ش�npc��������(npc)	
	ID_C2S_NOTIFY_STOPANSWER					= 0x3009;		// �ͻ���->������ ��������		
	ID_S2C_RESPONSE_USEQUESIONPAPER				= 0x300A;		// ������->�ͻ��� ʹ�ô����Ļظ���Ϣ	
	ID_S2C_NOIIFY_INVESTQUESTION				= 0x300B;		// ������->�ͻ��� �����ʾ��֪ͨ
	ID_C2S_NOTIFY_INVESTANSWER					= 0x300C;		// �ͻ���->������ �����ʾ�Ĵ�֪ͨ	
		
		
	ID_S2C_NOTIFY_THROWHYDRANGEA				= 0x300D;		// ������->�ͻ��� ������֪ͨ
	ID_S2C_NOTIFY_GRABHYDRANGEAENABLE			= 0x300E;		// ������->�ͻ��� �����������֪ͨ
	
	ID_C2S_REQUEST_GRABHYDRANGEA				= 0x300F;		// �ͻ���->������ �������������Ϣ
	ID_S2C_RESPONSE_GRABHYDRANGEA				= 0x3010;		// ������->�ͻ��� ������Ļ�Ӧ��Ϣ
	ID_S2C_NOTIFY_GRABHYDRANGEARESULT			= 0x3011;		// ������->�ͻ��� ������Ľ��֪ͨ
	
	ID_S2C_NOTIFY_HYDRANGEAREASULT				= 0x3012;		// ������->�ͻ��� �������Ľ��֪ͨ
	
	ID_S2C_NOTIFY_STARTHYDRANGEA				= 0x3013;		// �ͻ���->������ ��������ʼ��֪ͨ
	
	ID_C2S_REQUEST_THROWHYDRANGEA				= 0x3014;		// �ͻ���->������ �����������
	ID_S2C_RESPONSE_THROWHYDRANGEA				= 0x3015;		// ������->�ͻ��� ������Ļ�Ӧ��Ϣ	
	
	ID_S2C_NOTIFY_NPCTHROWSUGAR					= 0x3016;		// ������->�ͻ��� NPC��ϲ�ǵ���Ϣ֪ͨ
	
	ID_S2C_NOTIFY_SETHYDRANGEASTATUS			= 0x3017;		// ������->�ͻ��� �����������״̬��֪ͨ
	
	ID_S2C_NOTIFY_STARTPRELIMINARY				= 0x3018;		// ������->�ͻ��� ���Լ�����ʼ��֪ͨ	
	ID_S2C_NOTIFY_PRELIMINARYQUESTION			= 0x3019;		// ������->�ͻ��� ���Ե���Ŀ֪ͨ		
	ID_S2C_NOTIFY_PRELIMINARYANSWER				= 0x3020;		// ������->�ͻ��� ���ԵĴ�֪ͨ
	ID_S2C_NOTIFY_ENDPRELIMINARY				= 0x3021;		// ������->�ͻ��� �������Ե�֪ͨ
	ID_C2S_REQUEST_SUBMITPRELIMINARYANSWER		= 0x3022;		// �ͻ���->������ �ύ��Ŀ�𰸵���Ϣ
	ID_S2C_RESPONSE_SUBMITPRELIMINARYANSWER		= 0x3023;		// ������->�ͻ��� �ύ��Ŀ�𰸵Ļ�Ӧ��Ϣ	
	ID_C2S_REQUEST_VIEWPREMILINARYLIST			= 0x3024;		// �ͻ���->������ �鿴���԰����Ϣ����
	ID_S2C_RESPONSE_IEWPREMILINARYLIST			= 0x3025;		// ������->�ͻ��� �鿴���԰����Ϣ��Ӧ				
    // �Ͻ�ϵͳ��Ϣ
    ID_C2S_HANDIN_REQUEST                       = 0x3026;   // �Ͻ���Ʒ����
    ID_S2C_HANDIN_RESPONSE                      = 0x3027;   // �Ͻ���Ʒ��Ӧ

    // ҡǮ���
    ID_C2S_GETCAMPRANKFORYQS_REQUEST            = 0x3028;    // ��ȡҡǮ����Ӫ����(C->S)
    ID_S2C_GETCAMPRANKFORYQS_RESPONSE           = 0x3029;    // ��ȡҡǮ����Ӫ����(S->C)
    ID_S2C_YQSPHASECHANGE_NOTICE                = 0x3030;    // ҡǮ������֪ͨ(S->C)
    ID_S2C_YQSENCOURAGE_NOTICE                  = 0x3031;    // ҡǮ������֪ͨ(S->C)
    ID_C2S_GETPLAYERRANKFORYQS_REQUEST          = 0x3032;    // ��ȡҡǮ���û���������(C->S)
    ID_S2C_GETPLAYERRANKFORYQS_RESPONSE         = 0x3033;    // ��ȡҡǮ���û���������(S->C)
	
	ID_S2C_NOTIFY_QUESTIONVERIFY				= 0x3034;		// ������->�ͻ��� ��Ҫ���д�����֤��֪ͨ
	ID_C2S_REQUEST_ANSWERVERIFY					= 0x3035;		// �ͻ���->������ ���д���֤����Ϣ����
	ID_S2C_RESPONSE_ANSWERVERIFY				= 0x3036;		// ������->�ͻ��� ���д���֤����Ϣ��Ӧ

    // ҡǮ���������֪ͨ
    ID_S2C_YQSDROPITEM_NOTICE                   = 0x3037;    // ҡǮ��������Ʒ��ʾ(S->C)

	// �����ͺ�����Ϣ
	ID_S2C_GIFTTIMER_NOTIFY	                    = 0x3038;    // ֪ͨ��ʱ
	ID_C2S_GETGIFT_REQUEST	                    = 0x3039;    // ��ȡ
	ID_S2C_GETGIFT_RESPONSE	                    = 0x303A;    // ��ȡ ��Ӧ

    // ҡǮ�����ʼ��Ϣ                       
    ID_S2C_YQSSTART_NOTICE                             = 0x303B;     // ҡǮ�����ʼ��Ϣ(S->C)		 ]
    
    // �۱�����Ϣ
    ID_C2S_REQUEST_GETTREASUREBOWLINFO			=	0x303C;     // ��ȡĳ����Ʒ�ľ۱���Ϣ����
    ID_S2C_RESPONSE_GETTREASUREBOWLINFO			=	0x303D;     // ��ȡĳ����Ʒ�ľ۱���Ϣ�Ļ�Ӧ��Ϣ
    
    ID_C2S_REQUEST_STARTTREASUREBOWL			= 0x303F;     // ��ʼ�۱�����Ϣ����
    ID_S2C_RESPONSE_STARTTREASUREBOWL			= 0x3040;     // ��ʼ�۱�����Ϣ��Ӧ
    ID_S2C_NOTIFY_TREASUREBOWLSUCCESS			= 0x3041;     // �۱��ɹ�����Ϣ֪ͨ
    
};

message CMessageActivityYqsStart
{
    optional uint32 activityid          = 1;    // ҡǮ������
    optional uint32 campid              = 2;    // ��Ӫ���
};

// ********************************************************************** //
// CMessageGetPlayerRankForYQSRequest �ͻ��� -> ����������
// ��ȡ�û��������а�
// ********************************************************************** //
message CMessageGetPlayerRankForYQSRequest
{
    optional uint32 playerid            = 1;     // ��ұ��
};

// ********************************************************************** //
// CMessageGetPlayerRankForYQSResponse ���������� -> �ͻ���
// ��ȡ�û����׶����а�
// ********************************************************************** //
message PlayerRankForYQS
{
    optional uint32 rank                = 1;    // ����
    optional uint32 userid              = 2;    // �û�ID
    optional string username            = 3;    // �û���
    optional uint32 userlevel           = 4;    // �û��ȼ�
    optional uint32 usermetie           = 5;    // ����
    optional uint32 Contribute          = 6;    // ���׶�
};

message CMessageGetPlayerRankForYQSResponse
{
    optional uint32  playerid           = 1;        // ��ұ��
    optional uint32  playerhandindawnum = 2;        // ����Ͻɵ���¶��
    optional uint32  playercontribute   = 3;        // ��ҵ��ܹ��׶�
    repeated PlayerRankForYQS playerrankinfo = 4;   // ���׶����а�

};

// ********************************************************************** //
// EncourageForHandin �ͻ��� -> ����������
// �Ͻ�����
// ********************************************************************** //
message ItemForHandin
{
    optional uint32 itemtype			= 1;	// ��Ʒ����
    optional uint32 itemid				= 2;	// ��Ʒid
    optional uint32 itemnum			    = 3;    // �Ͻ���
};

message CMessageHandInRequest 
{
    optional uint32  playerId        	= 1;    // ��ұ��
    optional uint32  ActivityId		    = 2;	// ����
    optional uint32  ItemNum			= 3;    // �Ͻ���Ʒ����
    repeated ItemForHandin Items		= 4;	// �Ͻ���ƷID
};

// ********************************************************************** //
// CMessageHandInResponse ���������� -> �ͻ���
// �Ͻɻ�Ӧ
// ********************************************************************** //
message EncourageForHandin
{
    optional uint32 	encouragetype	= 1;    // ��������
    optional uint32 	encourageid		= 2;    // ������Ʒid
    optional uint32	    encouragenum	= 3;	// ����ֵ
};

message CMessageHandInResponse
{
    optional uint32  result		    	= 1;    // �����Ͻɽ����1Ϊ�ɹ�������Ϊʧ�ܡ�
    optional uint32  playerId        	= 2;    // ��ұ��
    optional uint32  activityId		    = 3;	// ����
    optional uint32  encouragenum		= 4;    // ������
    repeated	 EncourageForHandin encourages = 5; // ����
};

// ********************************************************************** //
// CMessageC2SGetCampRankForYQSRequest �ͻ��� -> ����������
// ��ȡ��Ӫ��������
// ********************************************************************** //
message CMessageC2SGetCampRankForYQSRequest
{
    optional uint32  playerId           = 1;    // ��ұ��
    optional uint32  param1             = 2;    // ��������
};

// ********************************************************************** //
// CMessageS2CGetCampRankForYQSResponse ���������� -> �ͻ���
// ��ȡ��Ӫ����Ӧ��
// ********************************************************************** //

message CampRankForYQS
{
    optional uint32 rank				= 1;    // ����
    optional uint32 campid				= 2;    // ��ӪID
    optional uint32 growinggrade		= 3;    // �ɳ���
    optional uint32 growingphase		= 4;    // �ɳ��׶�
};

message CMessageS2CGetCampRankForYQSResponse
{
    optional uint32  result             = 1;    // ���ؽ����1Ϊ�ɹ�������Ϊʧ��
    optional uint32  param1             = 2;    // ��������
    optional uint32  playerId      	    = 3;    // ��ұ��
    optional uint32  playerhandindawnum = 4;    // ����Ͻɵ���¶��
    optional uint32  playercontribute   = 5;    // ��ҵ��ܹ��׶�
    optional uint32  campnum			= 6;    // ��Ӫ��
    repeated  CampRankForYQS camprankinfo = 7;  // ��Ӫ������Ϣ
};

// ********************************************************************** //
// CMessageYQSPhaseChangeNotice ���������� -> �ͻ���
// ҡǮ������֪ͨ
// ********************************************************************** //
message CMessageYQSPhaseChangeNotice
{
    optional uint32 campid				= 1;        // ��Ӫid
    optional uint32 isfinished			= 2;        // �Ƿ����������׶Σ�1Ϊ�ǣ�0δ��
    optional uint32 currphase			= 3;        // ҡǮ����ǰ״̬
};

// ********************************************************************** //
// CMessageYQSEncourageChangeNotice ���������� -> �ͻ���
// ҡǮ������֪ͨ
// ********************************************************************** //
message CMessageYQSEncourageChangeNotice
{
    optional uint32 campid				= 1;        // ��Ӫid
    optional uint32 encourangeid		= 2;	    // �����ڼ��ν���
};

// ********************************************************************** //
// CMessageYQSEncourageChangeNotice ���������� -> �ͻ���
// ҡǮ������֪ͨ
// ********************************************************************** //
message CMessageYQSDropItemNotice
{
    optional uint32 playerid            = 1;        // ������
    optional uint32 itemid				= 2;        // ��Ʒ���
    optional uint32 itemnum		        = 3;	    // ��Ʒ����
};



// �������Ϣ


// *************************************************************************** //
// CMessageCheckAnswerRequest  ��Ϸ�ͻ���->��Ϸ������
// ������Ŀ�𰸽��м�������
// *************************************************************************** //
message CMessageCheckAnswerRequest
{
	optional uint32	  Answer	  = 		1; 		//  ��Ŀ��
	optional uint32   QuestionID  = 		2; 		//  ��Ŀ ID	
};

// *************************************************************************** //
// CMessageCheckAnswerResponse  ��Ϸ������->��Ϸ�ͻ���
// ����Ŀ�𰸼�����Ļظ�
// *************************************************************************** //
message CMessageCheckAnswerResponse
{
	optional uint32  QuestionID		 = 		1; 	   // ��Ŀid
	optional uint32  QuestionIndex   = 		2; 	   // ��������
	optional uint32  Result			 = 		3; 	   // ���Ƿ���ȷ1��ʾ��ȷ0��ʾ����	 
	optional uint32  IfLastQuestion  = 		4; 	   // �Ƿ����һ����Ŀ 1 ��ʾ�� 0 ��ʾ����
};


// *************************************************************************** //
// CMessageQuestionTimeEnd   ��Ϸ�ͻ���->��Ϸ������
// һ����Ŀ����ʱ�������֪ͨ
// *************************************************************************** //
message CMessageQuestionTimeEnd	
{
	optional uint32  QuestionID	  = 		1; 	   // ��Ŀid
};


// *************************************************************************** //
// CMessageQuestionNew		��Ϸ������->��Ϸ�ͻ���
// ����Ŀ��֪ͨ
// *************************************************************************** //
message CMessageQuestionNew
{
	optional uint32  QuestionIndex  = 		1; 	   // ��Ŀ����
	optional uint32  QuestionID	    = 		2; 	   // ��Ŀid
};


// *************************************************************************** //
// CMessageAnswerEnd		��Ϸ������->��Ϸ�ͻ���
// ������Ŀ�ش����
// *************************************************************************** //
message CMessageAnswerEnd
{
	optional uint32  EndType	  = 		1; 	   // �������� ��ʱ����Ŀ����	
};


// *************************************************************************** //
// CMessageUseQuestionPaper		��Ϸ�ͻ���->��Ϸ������
// ʹ������֪ͨ
// *************************************************************************** //
message CMessageUseQuestionPaper			  
{
	optional uint32  ItemIndex	  = 		1; 	   // ����ڰ������������
};


// *************************************************************************** //
// CMessageIfAnswerNow		��Ϸ�ͻ���->��Ϸ������
// �Ƿ����ϴ����֪ͨ
// *************************************************************************** //
message CMessageIfAnswerNow		  
{	
	optional uint32  Result		  = 		1; 	   // �Ƿ���� 1 ��ʾ���� 0 ��ʾ������
};


// *************************************************************************** //
// CMessageIfBeginQuest		��Ϸ�ͻ���->��Ϸ������
// �Ƿ�ʼnpc����
// *************************************************************************** //
message CMessageIfBeginQuest  
{
	optional uint32  IfBegin	  = 		1; 	   // �Ƿ�ʼ���� 1��ʾ��ʼ 0��ʾ����
};

// *************************************************************************** //
// CMessageStopAnser		��Ϸ�ͻ���->��Ϸ������
// ��������
// *************************************************************************** //
message CMessageStopAnser
{
	optional uint32  EndType	  = 		1; 	   // �������ʹ��, ��������
};

// *************************************************************************** //
// CMessageUsePaperResponse		��Ϸ�ͻ���->��Ϸ������
// ʹ�ô����Ļظ�
// *************************************************************************** //
message CMessageUsePaperResponse
{
	optional uint32  Result	  = 		1; 	   // 1.��ʾ���Դ��� 0.��ʾ���ܴ���
};

// *************************************************************************** //
// CMessageInvestQuestionNotify		��Ϸ������->��Ϸ�ͻ���
// �ʾ�������Ŀ֪ͨ
// *************************************************************************** //
message CMessageInvestQuestionNotify
{
	repeated uint32	 QuestionID  = 		1; 	// ��ĿID
};

// *************************************************************************** //
// CMessageInvestAnswerNotify		��Ϸ�ͻ���->��Ϸ������
// �����ʾ�Ĵ�֪ͨ
// *************************************************************************** //
message CMessageInvestAnswerNotify
{
	repeated uint32	QuestionID			 = 		1; 
	repeated uint32 QuestionAnswer		 = 		2; 
	optional uint32 IfAnswerNow			 = 		3; 		// �Ƿ����ڴ���
};


// *************************************************************************** //
// CMessageThrowHydrangeaNotify		������->�ͻ��� 
// ������֪ͨ			   ID_S2C_NOTIFY_THROWHYDRANGEA
// *************************************************************************** //
message CMessageThrowHydrangeaNotify
{
	optional uint32	ThrowType		= 1;			// 1��ʾϵͳ�׳�������0��ʾ����׳�������
	optional string	ThrowerName		= 2;			// ��������������
	optional string ReceiverName	= 3;			// ��������ߵ�����
	optional uint32	SrcPosX			= 4;			// �������ߵĺ�����
	optional uint32	SrcPosY			= 5;			// �������ߵ�������
	optional uint32	DesPosX			= 6;			// ��������ߵĺ�����
	optional uint32 DesPosY			= 7;			// ��������ߵ�������	
};

// *************************************************************************** //
// CMessageGrabHydrangeaEnableNotify		������->�ͻ���
// �����������֪ͨ		ID_S2C_NOTIFY_GRABHYDRANGEAENABLE
// *************************************************************************** //
message CMessageGrabHydrangeaEnableNotify
{
	optional string	HydrangeaHolder			=	1;			// �������������	
};

// *************************************************************************** //
// CMessageGrabHydrangeaRequest		�ͻ���->������ 
// �������������Ϣ		   ID_C2S_REQUEST_GRABHYDRANGEA
// *************************************************************************** //
message CMessageGrabHydrangeaRequest
{
	optional uint32	MsgCode	=	1;				// ���ò���	
};

// *************************************************************************** //
// CMessageGrabHydrangeaResponse		������->�ͻ���
// ������Ļ�Ӧ��Ϣ			  ID_S2C_RESPONSE_GRABHYDRANGEA
// *************************************************************************** //
message CMessageGrabHydrangeaResponse
{
	optional uint32	Errcode	=	1;			// ������Ĵ�����	
};

// *************************************************************************** //
// CMessageGrabHydrangeaResultNotify ������->�ͻ���
// ������Ľ��֪ͨ	   ID_S2C_NOTIFY_GRABHYDRANGEARESULT
// *************************************************************************** //
message CMessageGrabHydrangeaResultNotify
{
	optional string	SrcName	=	1;				// ����ԭ����������
	optional string DesName	=	2;				// �������г���������
	optional uint32	SrcPosX	=	3;				// ����ԭ�����ߵĺ�����
	optional uint32	SrcPosY	=	4;				// ����ԭ�����ߵ�������
	optional uint32	DesPosX	=	5;				// �������г����ߵĺ�����
	optional uint32	DesPosY	=	6;				// �������г����ߵ�������			
};

// *************************************************************************** //
// CMessageHydrangeaResultNotify ������->�ͻ���
// �������Ľ��֪ͨ		 ID_S2C_NOTIFY_HYDRANGEAREASULT
// *************************************************************************** //
message CMessageHydrangeaResultNotify
{
	optional string RoleName	=	1;			// �������ߵ�����
	optional uint32	RoleSex		=	2;			// �Ա�
};
// *************************************************************************** //
// CMessageStartHydrangeaNotify ������->�ͻ���
// �������Ŀ�ʼ��֪ͨ		 ID_S2C_NOTIFY_STARTHYDRANGEA
// *************************************************************************** //
message CMessageStartHydrangeaNotify
{
	optional uint32	MapID	=	1;				// ��ͼID
	optional uint32	PosX	=	2;				// ������
	optional uint32	PosY	=	3;				// ������
};

// *************************************************************************** //
// CMessageThrowHydrangeaRequest  �ͻ���->������ 
// �����������	 ID_C2S_REQUEST_THROWHYDRANGEA
// *************************************************************************** //
message CMessageThrowHydrangeaRequest
{
	optional uint32	MsgCode	=	1;			// ���ò���
};

// *************************************************************************** //
// CMessageThrowHydrangeaResponse  ������->�ͻ��� 
// ������Ļ�Ӧ��Ϣ	 ID_S2C_RESPONSE_THROWHYDRANGEA
// *************************************************************************** //
message CMessageThrowHydrangeaResponse
{
	optional uint32	Errcode	=	1;			// ������Ļ�Ӧ��Ϣ
};

// *************************************************************************** //
// CMessageThrowSugarNotify  ������->�ͻ��� 
// npcɢϲ�ǵ���Ϣ֪ͨ	 ID_S2C_NOTIFY_NPCTHROWSUGAR
// *************************************************************************** //
message CMessageThrowSugarNotify
{
	optional uint32	NpcEntityID	=	1;		// npc��ʵ��ID
};

// *************************************************************************** //
// CMessageSetHydrangeaStatusNotify  ������->�ͻ��� 
// �ı��������״̬����Ϣ֪ͨ	  ID_S2C_NOTIFY_SETHYDRANGEASTATUS
// *************************************************************************** //
message CMessageSetHydrangeaStatusNotify
{
	optional uint32	RoleEntityID	= 1;	// ���ʵ��ID
	optional uint32	HydrangeaStatus = 2;	// ����״̬
};

// *************************************************************************** //
// CMessageStartPreliminaryNotify  ������->�ͻ��� 
// ������->�ͻ��� ���Լ�����ʼ��֪ͨ
// *************************************************************************** //
message CMessageStartPreliminaryNotify
{
	
};			

// *************************************************************************** //
// CMessagePreliminaryQuestionNotify  ������->�ͻ��� 
// ���Ե���Ŀ֪ͨ
// *************************************************************************** //
message CMessagePreliminaryQuestionNotify
{
	optional uint32	QuestionID			=	1;		// ��ĿID
	optional uint32	QuestionIndex		=	2;		// ��Ŀ����
};

// *************************************************************************** //
// CMessagePremilinaryAnswerNotify  ������->�ͻ���
// ���ԵĴ�֪ͨ						  
// *************************************************************************** //
message CMessagePreliminaryAnswerNotify
{
	optional uint32	QuestionID		=	1;		// ��ĿID
	optional uint32	QuestionAnswer	=	2;		// ��Ŀ��
	repeated string PlayerInList	=	3;		// ��ʱ���е�����б�
	repeated uint32	ExtraScore		=	4;		// ��һ�õĶ������
	optional uint32	QuestionIndex	=	5;		// ��Ŀ����
};

// *************************************************************************** //
// CMessageEndPrimilinaryNotify  ������->�ͻ���
// �������Ե�֪ͨ	 
// *************************************************************************** //
message CMessageEndPreliminaryNotify
{
	
};

// *************************************************************************** //
// CMessageSubmitPremiliynaryAnswerRequest �ͻ���->������
// �ύ��Ŀ�𰸵���Ϣ		 
// *************************************************************************** //
message CMessageSubmitPreliminaryAnswerRequest
{		
	optional uint32	QuestionAnswer	= 1;	// ��Ŀ��
};

// *************************************************************************** //
// CMessageSubmitPremiliynaryAnswerResponse ������->�ͻ���
// �ύ��Ŀ�𰸵Ļ�Ӧ��Ϣ		 
// *************************************************************************** //
message CMessageSubmitPreliminaryAnswerResponse
{		
	optional uint32 Errcode =   1;		// ������
};

// *************************************************************************** //
// CMessageViewPremilinaryListRequest �ͻ���->������
// �鿴���԰����Ϣ����			 
// *************************************************************************** //
message CMessageViewPreliminaryListRequest
{
	optional uint32	NpcID	=	1;		// npc��ʵ��ID
	optional uint32	Type	=	2;		// EPremilinaryListType
};


// *************************************************************************** //
// CMessageViewPremilinaryListRequest ������->�ͻ���
// �鿴���԰����Ϣ��Ӧ
// *************************************************************************** //
message PBPreliminaryInfo		
{		
	optional string RoleName		= 1;	// ��ɫ����
	optional uint32 Score			= 2;	// �÷����
	optional uint32	RightNum		= 3;	// ��Ե���Ŀ����
	optional uint32	TotalNum		= 4;	// �ܹ�������	
};
message CMessageViewPreliminaryResponse			
{
	repeated PBPreliminaryInfo PremilinaryInfoList = 1;	// ���Իʰ������Ϣ		
	optional uint32			   Type				   = 2;	// EPremilinaryListType
};

// *************************************************************************** //
// CMessageQuestionVerifyNotify ������->�ͻ���
// ��Ҫ���д�����֤��֪ͨ
// *************************************************************************** //
message CMessageQuestionVerifyNotify
{	
	optional uint32 QuestionId = 1; // ������
	optional string Question   = 2; // ��������
	optional bytes OptionA     = 3; // ѡ��A
	optional bytes OptionB     = 4; // ѡ��B
	optional bytes OptionC     = 5; // ѡ��C
	optional bytes OptionD     = 6; // ѡ��D
};

// *************************************************************************** //
// CMessageAnswerVerifyRequest �ͻ���->������
// ���д���֤����Ϣ����
// *************************************************************************** //
message CMessageAnswerVerifyRequest
{
	optional uint32 QuestionId = 1; // ������
	optional bytes Answer      = 2; // �ش���
};

// *************************************************************************** //
// CMessageAnswerVerifyResponse ������->�ͻ���
// ���д���֤����Ϣ��Ӧ
// *************************************************************************** //
message CMessageAnswerVerifyResponse
{
	optional uint32 Errcode   = 1; // ������
};

// *************************************************************************** //
// ������->�ͻ���
// �����ͺ��� ��ʼ��ʱ֪ͨ
// *************************************************************************** //
message CMessageStartGiftTimerNotify
{
	optional uint32 Secs	 = 1; // ��ʱ������
	optional uint32 GiftId   = 2; // �����ģ��ID
	optional uint32 GiftType = 3; // ��������� 0-ʱ�� 1-�ȼ�
};

// *************************************************************************** //
// �ͻ���->������
// �����ͺ��� ��ȡ�������
// *************************************************************************** //
message CMessageGetOnlineGiftRequest
{
	optional uint32 GiftType = 1; // ��������� 0-ʱ�� 1-�ȼ�
};

// *************************************************************************** //
// ������->�ͻ���
// �����ͺ��� ��ȡ�����Ӧ
// *************************************************************************** //
message CMessageGetOnlineGiftResponse
{
	optional uint32 RetCode   = 1; // 0 �ɹ� ����ʧ��
	optional uint32 GiftType  = 2; // ��������� 0-ʱ�� 1-�ȼ�
};

// *************************************************************************** //
// CMessageGetTreasureBowlInfoRequest �ͻ���->������
// ��ȡĳ����Ʒ�ľ۱���Ϣ����
// *************************************************************************** //
message CMessageGetTreasureBowlInfoRequest
{
	optional uint32	 ItemIndex = 1;		// Ҫ�۱�����Ʒ����	
};

// *************************************************************************** //
// CMessageGetTreasureBowlInfoResponse ������->�ͻ���
// ��ȡĳ����Ʒ�ľ۱���Ϣ�Ļ�Ӧ��Ϣ
// *************************************************************************** //
message CMessageGetTreasureBowlInfoResponse
{
	optional uint32	 Errcode		= 1;		// ������
	optional uint32	 ItemUsedTimes	= 2;		// ��Ʒ�Ѿ��۱��Ĵ���
	optional uint32	 ItemTotalTimes	= 3;		// ��Ʒ�ܹ����Ծ۱��Ĵ���
	optional uint32	 AllUsedTimes	= 4;		// ������Ʒ�ľ۱�����
	optional uint32	 AllTotalTimes	= 5;		// ������Ʒ���ܹ��۱�����
	optional uint32	 TaxMoney		= 6;		// �۱���Ҫ���ѵĽ�Ǯ
	optional uint32	 Index			= 7;		// ��Ʒ����λ��
};

// *************************************************************************** //
// CMessageStartTreasureBowlRequest �ͻ���->������
// ��ʼ�۱�����Ϣ����
// *************************************************************************** //
message CMessageStartTreasureBowlRequest
{
	optional uint32 ItemIndex	=	1;	// ���۱���Ʒ������
	optional uint32	EntityID	=	2;	// npc��ʵ��ID
};

// *************************************************************************** //
// CMessageStartTreasureBowlResponse �ͻ���->������
// ��ʼ�۱�����Ϣ��Ӧ
// *************************************************************************** //
message CMessageStartTreasureBowlResponse
{
	optional uint32	Errcode		= 1;	// ������
	optional uint32	ItemIndex	= 2;	// ��Ʒ����	
	optional uint32	NewItemID	= 3;	// �¶һ���������ƷID
};

// *************************************************************************** //
// CMessageTreasureBowlSuccessNotify ������->�ͻ���
// �۱��ɹ�����ʾ
// *************************************************************************** //
message CMessageTreasureBowlSuccessNotify
{
	optional string	RoleName	=	1;	// ��ɫ����
	optional uint32	OldItemID	=	2;	// �۱�ǰ����ƷID
	optional uint32	NewItemID	=	3;	// �۱������ƷID
	optional uint32	ItemNum		=	4;	// �۱����������Ʒ����
};
										