import "coremessage_pb.hxx";
import "property_pb.hxx";

// ������ٶ�����/������
option optimize_for = SPEED;

// ��������Ϣ��ID�����ٴΣ���ֹ�ظ�����
// task message��Ϣ��ID��Χ(0x1000 -- 0x1400)
enum TASK_MSG_ID
{	
	ID_C2S_REQUEST_OBTAINTASK			= 0x1000; // �ͻ���->������ ������������
	ID_C2S_REQUEST_ENDTASK				= 0x1001; // �ͻ���->������ �����������
	ID_S2C_NOTICE_OBTAINTASK			= 0x1002; // ������->�ͻ��� �������֪ͨ
	ID_S2C_NOTICE_COMPLETE				= 0x1003; // ������->�ͻ��� �������֪ͨ
	ID_S2C_NOTICE_TASKEND				= 0x1004; // ������->�ͻ��� �������֪ͨ
	ID_S2C_NOTICE_UPDATE				= 0x1005; // ������->�ͻ��� �����������
	ID_S2C_NOTICE_RESET					= 0x1006; // ������->�ͻ��� ����ع�֪ͨ
	ID_C2S_REQUEST_ABORTTASK			= 0x1007; // �ͻ���->������ ������������
	ID_S2C_NOTICE_TASKLIST				= 0x1008; // ������->�ͻ��� ����ҷ������ϵ������б�
	ID_S2C_NOTICE_NPCTASKLIST			= 0x1009; // ������->�ͻ��� ����NPC�󶨵������б�
	ID_S2C_NOTICE_NPCTASKTIP			= 0x100A; // ������->�ͻ��� ����NPCͷ��
	ID_C2S_REQUEST_TASK_SEARCH			= 0x100B; // �ͻ���->������ ���������������
	ID_S2C_NOTICE_TASK_SEARCH			= 0x100C; // ������->�ͻ��� ����������
	ID_C2S_INVITE_TASK_REQUEST			= 0x100D; // �ͻ���->������ ���������������
	ID_S2C_INVITE_TASK_NOTICE			= 0x100E; // ������->�ͻ��� ����������յ�����Ϣ
	ID_C2S_INVITE_TASK_RESPONSE_REQUEST = 0x100F; // �ͻ���->������ ��һ�Ӧ�������뺯
	ID_S2C_INVITE_TASK_RESPONSE_NOTICE  = 0x1210; // ������->�ͻ��� ���������߶Է��Ļظ�  0x1010 + 0x0200 
	ID_S2S_DOPLAYER_INVITE_TASK_MSG		= 0x1211; // 0x1011 + 0x0200 {��������Ϣ}
	ID_S2C_PLAYER_INVITE_TASK_ERROR_MSG = 0x1212; // 0x1012 + 0x0200 ���͸��ͻ��ˣ��Է����ܽ����������
	ID_S2C_NOTICE_ABORT_TASK			= 0x1014; // ������->�ͻ��� ��������֪ͨ
	ID_S2C_NOTICE_TASKFAIL				= 0x1015; // ������->�ͻ��� ����ʧ��֪ͨ
	ID_S2C_NOTICE_TASKOPRFAIL			= 0x1016; // ������->�ͻ��� �������ʧ��֪ͨ
	ID_S2C_NOTICE_NPCSTORAGETASKLIST	= 0x1017; // ������->�ͻ��� ����NPC�󶨵Ŀ������б�
	ID_C2S_REQUEST_OBTAINSCROLLTASK		= 0x1018; // �ͻ���->������ �ͻ�������ʹ��������������������
	ID_S2C_NOTICE_TRAGEDYTASKUPDATE		= 0x1019; // ������->�ͻ��� ���������б�
	ID_C2S_REQUEST_GETTIP				= 0x101A; // �ͻ���->������ ���ָ��NPC��ͷ��
	ID_C2S_REQUEST_ENDTALK				= 0x101B; // �ͻ���->������ �����ɺ�ĳNPC�ĶԻ�
	ID_S2C_NOTICE_NPCTALKCHANGE			= 0x101C; // ������->�ͻ��� ���öԻ�״̬
	ID_C2S_REQUEST_LOCKBAG				= 0x101D; // �ͻ���->������ ���������������
	ID_S2C_LOCKBAG_RESPONSE				= 0x101E; // ������->�ͻ��� ��������������� ��Ӧ
	ID_S2C_UPDATE_CONDITIONS			= 0x101F; // ������->�ͻ��� �°�����������Ϣ
	ID_S2C_CLEARTASKNOTIFY				= 0x1020; // ������->�ͻ��� �������֪ͨ
	ID_C2S_REQUEST_TAKEOFFITEM			= 0x1021; // �ͻ���->������ ����õ���Ʒ����
	ID_C2S_REQUEST_GETFAMILYTASK		= 0x1022; // �ͻ���->������ ��һ�û����������
	ID_S2C_RESPONSE_GETFAMILYTASK		= 0x1023; // ������->�ͻ��� ��һ�û�������Ӧ
	ID_C2S_REQUEST_GETCORPSTASK			= 0x1024; // �ͻ���->������ ��һ�þ�����������
	ID_S2C_RESPONSE_GETCORPSTASK		= 0x1025; // ������->�ͻ��� ��һ�þ��������Ӧ
	ID_C2S_REQUEST_GETCOUNTRYTASK		= 0x1026; // �ͻ���->������ ��һ�ù�����������
	ID_S2C_RESPONSE_GETCOUNTRYTASK		= 0x1027; // ������->�ͻ��� ��һ�ù��������Ӧ
	ID_C2S_REQUEST_GETCAMPTASK			= 0x1028; // �ͻ���->������ ��һ����Ӫ��������
	ID_S2C_RESPONSE_GETCAMPTASK			= 0x1029; // ������->�ͻ��� ��һ����Ӫ�����Ӧ
	ID_C2S_REQUEST_GETCHAIRMANTASK		= 0x102A; // �ͻ���->������ ��һ��������������
	ID_S2C_RESPONSE_GETCHAIRMANTASK		= 0x102B; // ������->�ͻ��� ��һ�����������Ӧ
	ID_S2C_NOTIFY_GETTEAMLOOPERR		= 0x102C; // ������->�ͻ��� ��ҽ�ȡ��ӻ����� ����
	ID_S2C_NOTIFY_UNFINISHTIMEERR		= 0x102D; // ������->�ͻ��� �����δ����������ʱ�� ����
	ID_C2S_REQUEST_REFRESHTASK			= 0x102E; // �ͻ���->������ �������ˢ��������
	ID_S2C_NOTICE_TASKREFRESHFAIL		= 0x102F; // ������->�ͻ��� ˢ������ʧ��֪ͨ
	ID_S2C_NOTICE_TASKUNREFRESHED		= 0x1030; // ������->�ͻ��� ���񲻿�ˢ�½���
	ID_S2C_NOTICE_TASKREFRESHRESULT		= 0x1031; // ������->�ͻ��� ����ˢ�½��Ʒ��֪ͨ
	ID_S2C_NOTICE_REMOVETASKCOLOR		= 0x1032; // ������->�ͻ��� ɾ�����ػ���֪ͨ
	ID_S2C_NOTICE_TASKUNREACCEPT		= 0x1033; // ������->�ͻ��� ������ȴʱ����δ����֪ͨ

	ID_C2S_REQUEST_CHECK_GROUPPUBLISH	= 0x1034; // �ͻ���->������ ��Ҳ鿴���巢������չ��
	ID_C2S_REQUEST_PLAYERPUBLISHTASK	= 0x1035; // �ͻ���->������ ��ҷ�����������
	ID_S2C_RESPONSE_CHECK_GROUPPUBLISH	= 0x1036; // ������->�ͻ��� ��Ӧ�鿴չ��
	ID_S2C_RESPONSE_PLAYERPUBLISHTASK	= 0x1037; // ������->�ͻ��� ��ҷ���������

	ID_C2S_REQUEST_CHECK_SINGLEPUBLISH	= 0x1038; // �ͻ���->������ ��Ҳ鿴���˷���������Ϣ
	ID_C2S_REQUEST_SINGLEPUBLISHTASK	= 0x1039; // �ͻ���->������ ��ҷ�������������������
	ID_C2S_REQUEST_REFRESHSINGLETASK	= 0x103A; // �ͻ���->������ ���ˢ�µ�����ɫ����
	ID_C2S_REQUEST_OBTAINSINGLETASK		= 0x103B; // �ͻ���->������ ��ҽ��ܷ�����������
	ID_C2S_REQUEST_RECVSINGLEAWARDS 	= 0x103C; // �ͻ���->������ �����ȡ���˷�������

	ID_S2C_RESPONSE_CHECK_SINGLEPUBLISH	= 0x103D; // ������->�ͻ��� �鿴���˷�����Ϣ��Ӧ
	ID_S2C_RESPONSE_SINGLEPUBLISHTASK	= 0x103E; // ������->�ͻ��� ���˷������
	ID_S2C_RESPONSE_REFRESHRESULT		= 0x103F; // ������->�ͻ��� ˢ�¸��˷���������

};


// ���������

message TaskStruct
{
	optional int32 Timer			 = 		1; 			// ����ʱ��
	repeated uint32 TaskData		 = 		2; 			// ��������
	optional uint32 TaskProgress	 = 		3; 			// �������
	repeated uint32	TalkedNpcs		 = 		4; 			// �Ѿ���ɵĶԻ�NPC
	optional uint32 TaskID			 = 		5; 			// ����ID
};


// *************************************************************************** //
// ������������
// *************************************************************************** //

message CMessageObtainTaskRequest
{
	optional uint32 NpcEntityID		 = 		1; 		// �������NPCʵ��ID
	optional uint32 TaskID			 = 		2; 		// ����ID
};

// *************************************************************************** //
// �����������
// *************************************************************************** //

message CMessageTaskEndRequest
{
	optional uint32 TaskID		 = 		1; 		// ����ID
	optional uint32 NpcEntityID	 = 		2; 		// �������NPCʵ��ID
	optional uint32 SelectID	 = 		3; 		// ��ѡ����ѡ�����Ʒ������(1��ʼ)
	optional uint32 BagIndex	 =		4;		// ������Ʒ�İ�������
};

message CMessageTaskRefreshRequest
{
	optional uint32 TaskID		 = 		1; 		// ����ID
	optional uint32 NpcEntityID	 = 		2; 		// �������NPCʵ��ID
	optional uint32 SelectID	 = 		3; 		// ��ѡ����ѡ�����Ʒ������(1��ʼ)
	optional uint32 RefreshItemIndex =	4;		// ˢ���������ĵ��ߵİ�������
};


message LoopTaskStruct
{
	optional uint32 TodayMultiLoops  = 		1; 			// ��������ɵĶ౶�����Ļ���
	optional uint32 WeekMultiLoops   = 		2; 			// ��������ɵĶ౶����������
	optional uint32 TotalMultiLoops  = 		3; 			// ÿ�ն౶�������ܻ���
	optional uint32 LoopTaskID		 = 		4; 			// ������ID
	optional uint32 CompletedLoops	 = 		5; 		    // ���������
	optional uint32 NextLoopID		 = 		6; 			// ��һ����ID û�ӹ���ʱ��1
	optional uint32 LoopID			 = 		7;          // ��ID
	optional uint32 WeekTotalMultiLoops   = 8; 		    // ���ܶ౶������������
	optional uint32 AwardMultipleToday = 	9; 			// ����ǰx�ֶ౶�����ı���
};

// �������������������ṹ��
message StorageTaskStruct
{
	optional uint32 TodayCompletes		=	1;			// ������ɴ���
	optional uint32 TotalMultiLoops		=	2;			// ÿ�ն౶�����Ĵ���
	optional uint32 AwardMultipleToday = 	3; 			// ����ǰx�ֶ౶�����ı���
};

// *************************************************************************** //
// �������֪ͨ
// *************************************************************************** //

message CMessageObtainTaskNotice
{

	optional TaskStruct		Task		 = 		1; 
	optional LoopTaskStruct LoopTask	 = 		2; 
};

// *************************************************************************** //
// �������֪ͨ
// *************************************************************************** //

message CMessageTaskCompleteNotice
{
	optional uint32		TaskID  = 		1; 		// ����ID
};

// *************************************************************************** //
// �������֪ͨ
// *************************************************************************** //

message CMessageTaskEndNotice
{
	optional uint32 TaskID  = 		1; 		// ����ID
	optional StorageTaskStruct StorageTask	=	2;	// ��ؿ���������
};

// *************************************************************************** //
// �����������֪ͨ
// *************************************************************************** //

message CMessageUpdateTaskNotice
{
	optional TaskStruct Task  = 		1; 
};

// *************************************************************************** //
// ��������֪ͨ
// *************************************************************************** //

message CMessageResetTaskNotice
{
	optional uint32 TaskID  = 		1; 		// ����ID
};


// *************************************************************************** //
// ������������
// *************************************************************************** //

message CMessageAbortTaskRequest
{
	optional uint32 TaskID  = 		1; 			// ����ID
	optional uint32 NpcEntityID  = 		2;     // û��
};

// *************************************************************************** //
// �õ�������ϵ������б�֪ͨ
// *************************************************************************** //

message CMessageTaskListNotice
{

	optional bytes		CompletedBuf	 = 		1;   // ����������buf���ͷ������ڴ��еı���һ��
	optional uint32     TaskNum			 = 		2;   // ������ϵ���������
	optional LoopTaskStruct LoopTask	 = 		3;   // ����������
	repeated TaskStruct Tasks			 = 		4;   // ������ϵ������б�
	repeated uint32		CompletedTasks	 =		5;	 // �������ɵ������б�(�����ظ�������Щ)
	optional StorageTaskStruct StorageTask	=	6;	 // ���������ݽṹ
	repeated uint32		ChairManSectionIDs	=	7;	 // ���������½�ID�б�
	repeated uint32		RepeateTasks			=	8;	 // �������ɵ������б�(���ظ�������Щ)
	repeated uint32		EndTime				=	9;	 // ������ɵ�ʱ��
};


// ********************************************************************** //
// CNpcTaskList
// ********************************************************************** //
//
message NpcTaskList
{
	repeated uint32     ExtendTaskID	 = 		1; 
	optional uint32     CallbackNumber	 = 		2; 
	optional uint32     ExtendNumber	 = 		3; 
	optional uint32     NpcID			 = 		4; 
	repeated uint32     CallbackTaskID	 = 		5; 
};


// *************************************************************************** //
// �õ�NPC���ϵ������б�
// *************************************************************************** //

message CMessageNpcTaskListNotice
{
	optional NpcTaskList   List  = 		1; 
};


// *************************************************************************** //
// �õ�NPCͷ����ʾ
// *************************************************************************** //

message CMessageNpcTaskTipNotice
{
	repeated uint32   NpcEntityID	 = 		1;  // NPC��ʵ��ID
	repeated uint32   Tip			 = 		2; 
	optional uint32   IdType		 = 		3;  // ID���� 0 ʵ��ID  1 ģ��ID
};


// *************************************************************************** //
// ���������������
// *************************************************************************** //

message CMessagePlayerSearchRequest
{
};


// *************************************************************************** //
// �����������Ӧ��
// *************************************************************************** //

message CMessagePlayerSearchResponse
{
	repeated uint32   TaskIDs	 = 		1;  // NPC��ʵ��ID
};


// *************************************************************************** //
// �����������   �ͻ���->������
// *************************************************************************** //

message CMessagePlayerInviteTaskRequest
{
	repeated string   PlayerNames	 = 		1;  // ���������ҵ�����
	optional uint32	  TaskID		 = 		2;  // ����ID
};


// *************************************************************************** //
// ����������յ�����Ϣ   ������->�ͻ���
// *************************************************************************** //

message CMessagePlayerInviteTaskNotice
{
	optional uint32   TaskID             = 		1;  // ����ID
	optional string   SrcPlayerName      = 		2;  // �����ߵ�����
};



// *************************************************************************** //
// ��һ�Ӧ�������뺯   �ͻ���->������
// *************************************************************************** //

message CMessagePlayerInviteTaskResponseRequest
{
	optional uint32	  TaskID         = 		1;  // ����ID
	optional uint32   AgreeFlag      = 		2;  // 1Ϊͬ�⣬0Ϊ�ܾ�
	optional string   SrcPlayerName	 = 		3;  // �����ߵ�����
};

// *************************************************************************** //
// ���������߶Է��Ļظ� ���ܲ���ͬһ��������������·����Ϣ  ������->�ͻ���
// *************************************************************************** //

message CMessagePlayerInviteTaskResponseNotice
{
	optional CMessageRouter Router			   = 		1;  // ���ǲ�һ����ͬһ��������
	optional string			SrcPlayerName      = 		2;  // �������ߵ�����
	optional uint32			TaskID             = 		3;  // ����ID
	optional uint32			AgreeFlag          = 		4;  // 1Ϊͬ�⣬0Ϊ�ܾ�
};

// *************************************************************************** //
// ���͵�������ڳ������������д���   ������->������
// *************************************************************************** //

message CMessageDoPlayerInviteTaskMsg
{
	optional CMessageRouter Router		 = 		1;    
	optional uint32	  TaskID             = 		2;  // ����ID
};


// *************************************************************************** //
// �������߲������������֪ͨ�����ߡ�����   ������->�ͻ���
// *************************************************************************** //

message CMessagePlayerInviteTaskErrorMsg
{
	optional CMessageRouter Router		 = 		1;    
	optional uint32	  TaskID             = 		2;  // ����ID
	optional uint32   TypeID			 = 		3;  // ʧ������: ��ETaskInviteRet
	optional string   MyName             = 		4;  // �������ߵ�����
};


// *************************************************************************** //
// ��������֪ͨ
// *************************************************************************** //

message CMessageAbortTaskNotice
{
	optional uint32 TaskID  = 		1; 		// ����ID
};

// *************************************************************************** //
// ����ʧ��֪ͨ
// *************************************************************************** //

message CMessageTaskFailNotice
{
	optional uint32 TaskID  = 		1; 		// ����ID
};

// *************************************************************************** //
// δ��������ʱ��֪ͨ
// *************************************************************************** //

message CMessageUnFinishTaskTime
{
	optional uint32 TaskID		= 		1; 		// ����ID
	optional uint32 NeedTime	= 		2;		//���������Ҫ��ʱ��
};


// *************************************************************************** //
// ������������������������ʧ��֪ͨ�ͻ�����UI
// *************************************************************************** //



message CMessageTaskOprFailNotice
{
};

// ���񲻿�ˢ��
message CMessageTaskUnRefreshNotice
{
	optional uint32 TaskID		= 		1; 		// ����ID
};


// ����ˢ�½��
message CMessageTaskRefreshResult
{
	optional uint32 TaskID		= 		1; 		// ����ID
	optional uint32 TaskColor	= 		2;		
	optional uint32 TaskNumber	= 		3; 
};

// ֪ͨ�ͻ��ˣ�ɾ���洢������Ʒ��
message CMessageRmoveTaskColor
{
	optional uint32 TaskID		= 		1; 		// ����ID
	optional uint32 TaskColor	= 		2;
};

// ����ˢ��ʧ��
message CMessageTaskRefreshFailNotice
{
	optional uint32 TaskID		= 		1; 		// ����ID
};

// ������δ��ȴ
message CMessageUnReaccpetTask
{
	optional uint32 TaskID		= 		1; 		// ����ID
	optional uint32 NeedTime	= 		2;
};

// *************************************************************************** //
// �õ�NPC���ϵĿ������б�
// *************************************************************************** //

message CMessageNpcStorageTaskListNotice
{
	optional NpcTaskList   List  = 		1; 
};

// *************************************************************************** //
// ʹ������ ����������������
// *************************************************************************** //

message CMessageObtainScrollTaskRequest
{
	optional uint32 ScrollID   = 		1; 		// ����
};

//message TragedyStruct
//{
//	optional uint32		TragedyIndex    = 1; // ������������ 1��ʼ
//	optional fixed32	NextTragedyTask = 2; // ��Ӧ�� ��һ������������ID ����Ϊ0
//	optional uint32		TragedyState	= 3; // ��Ӧ�Ľ�������״̬
//};

// *************************************************************************** //
// �������� �б�/������Ϣ
// *************************************************************************** //
message CMessageTragedyTaskUpdateNotice
{
	repeated TragedyStruct TragedyInfo   = 		1; 
	optional uint32		   IsLogin		 = 		2;  // �Ƿ��¼ʱ�򷢵�  
};


// *************************************************************************** //
// �ͻ��˻��ָ��NPC��ͷ��
// *************************************************************************** //

message CMessageGetTipRequest
{
	repeated uint32   NpcEntityID	= 		1;  // NPC��ʵ��ID
	optional uint32   IdType		= 		2;  // ID���� 0 ʵ��ID  1 ģ��ID
};


// *************************************************************************** //
// ��Һ�ĳNPC�Ի����
// *************************************************************************** //

message CMessageEndTalkRequest
{
	optional uint32 NpcEntityID		 = 		1; 	// NPCʵ��ID
	optional uint32 TaskID			 = 		2; 	// ����ID
};


// *************************************************************************** //
//  ��Һ�NPC�Ի�״̬�ı�
// *************************************************************************** //

message CMessageNpcTalkStateChangeNotice
{
	optional uint32 TaskID			 = 		1; 	// ����ID
	optional uint32 State			 = 		2; 	// �Ի�״̬ 1=�ѶԻ� 0=δ�Ի�
	optional uint32 NpcTempID		 = 		3; 	// NPCģ��ID
};


// *************************************************************************** //
// ��ҽ��������ȥ���� �������� ����
// *************************************************************************** //

message CMessageLockBaggageRequest
{
	optional uint32 ItemIndex			 = 		1; 	// ����
};

// *************************************************************************** //
// ��ҽ��������ȥ���� �������� ��Ӧ
// *************************************************************************** //

message CMessageLockBaggageResponse
{
	optional uint32 ItemIndex			 = 		1; 	// ����
};


message TaskCondition
{
	optional fixed32 TaskID			 = 		1; 	// ����ID
	optional fixed32 Condition		 = 		2; 	// ����ö��
	optional fixed32 TempID			 = 		3; 	// ģ��ID
	optional uint32  Num			 = 		4; 	// ����Ļ���ʾ����  ��Ʒ���ֶ���Ч
};

// *************************************************************************** //
// ֪ͨ�ͻ��˸������� ����Ϊ��λ ��������Ϊ��λ
// *************************************************************************** //
message CMessageUpdateTaskConditions
{
	repeated  TaskCondition  Contions  = 		1; 
};


// *************************************************************************** //
// ֪ͨ�ͻ��� ���
// *************************************************************************** //
message CMessageClearTaskNotify
{

};

// *************************************************************************** //
// ���ȡ�½��������ȥ�Ķ��� �������� ����
// *************************************************************************** //

message CMessageTakeOffItemRequest
{
};

// *************************************************************************** //
// ���������������б�
// *************************************************************************** //
message CMessageGetFamilyTaskRequest
{
	repeated uint32 TaskTypes		=	1;		// �������� ��� enTaskGroups ö��
};

message SingleFamilyTaskResponse
{
	optional uint32 TaskIDs				=	1;		// ����ID
	optional uint32 TodayTimes			=	2;		// �������൱������ɴ���
};

// *************************************************************************** //
// ���������������б� ��Ӧ
// *************************************************************************** //
message CMessageGetFamilyTaskResponse
{
	repeated SingleFamilyTaskResponse Tasks	=	1;
};


// *************************************************************************** //
// ���������������б�
// *************************************************************************** //
message CMessageGetCorpsTaskRequest
{
};

// *************************************************************************** //
// ���������������б� ��Ӧ
// *************************************************************************** //
message CMessageGetCorpsTaskResponse
{
	repeated SingleFamilyTaskResponse Tasks	=	1;
};



// *************************************************************************** //
// ���������������б�
// *************************************************************************** //
message CMessageGetCountryTaskRequest
{
};

// *************************************************************************** //
// ���������������б� ��Ӧ
// *************************************************************************** //
message CMessageGetCountryTaskResponse
{
	repeated SingleFamilyTaskResponse Tasks	=	1;
};


// *************************************************************************** //
// ���������Ӫ�����б�
// *************************************************************************** //
message CMessageGetCampTaskRequest
{
};

// *************************************************************************** //
// ���������Ӫ�����б� ��Ӧ
// *************************************************************************** //
message CMessageGetCampTaskResponse
{
	repeated SingleFamilyTaskResponse Tasks	=	1;
};

// *************************************************************************** //
// ����������������б�
// *************************************************************************** //
message CMessageGetChairManTaskRequest
{
	optional uint32		NpcEntityID	= 1; // ���ڲ�����NPCʵ��ID
};

// *************************************************************************** //
// ����������������б� ��Ӧ
// *************************************************************************** //

message CMessageGetChairManTaskResponse
{
	repeated SingleChairManTask TaskIDs	=	1;		// ����ID
};


// *************************************************************************** //
// ��ҽ�ȡ��ӻ����� ʧ��֪ͨ
// *************************************************************************** //

message CMessageGetTeamLoopErrNotify
{
	optional string CharName = 1;
	optional uint32 ErrCode  = 2; // ��Ϣ�� �μ�errcode
};


message PBPubslishList
{
	optional uint32 TaskID			= 1;
	optional uint32 TaskState		= 2;
};

//******************************************//
//����������Ϣ
//����
//*******************************************//

// ��Ҽ�鷢������չ��
message CMessageCheckGroupPublishRequest
{
	optional uint32 PublishType		= 1;
};

message CMessagePublishGroupTaskRequest
{
	optional uint32 TaskID			= 1;
	optional uint32 PublishType		= 2;
};

// **************************************
// ��������  ��Ϣ��Ӧ


// �鿴չ������Ļ�Ӧ
message CMessageCheckGroupPublishResponse
{
	optional uint32 PublishType		= 1;
	repeated PBPubslishList Tasks	= 2;
};

// ��ҷ�����������Ļ�Ӧ

message CMessagePublishGroupTaskResponse
{
	optional uint32 TaskID			= 1;
	optional uint32 PublishType		= 2;
};


// ****************************************//
// ���˷�����Ϣ
// ****************************************//

// �鿴���˷���
message CMessagePlayerCheckSinglePublish
{
	
};

// ���˷���
message CMessagePlayerSinglePublishTask
{
	optional uint32 TaskColor		= 1;
	optional uint32 ItemIndex		= 2;
};

// ˢ�¸��˷�������
message CMessageRefreshSingleTaskRequest
{
	optional uint32 TaskColor		= 1;
	optional uint32 ItemIndex		= 2;
};

// ��ҽҰ���˷�������
message CMessagePlayerGetPublishTaskRequest
{
	optional uint32 TaskColor		= 1;
};

// ��ȡ��������
message CMessagePlayerGetAwardsRequest
{
	optional uint32 TaskColor		= 1;
};

//***************************************
//  ��Ϣ��������->�ͻ���
//	���ܣ����˷�������
//***************************************

// single color rank
message PBSingleColorRank
{
	optional uint32 PubNumber		= 1;
	optional uint32 RecvTasks		= 2;
	optional uint32 RecvAwards		= 3;
	optional uint32 CurrentTask		= 4;
};

// check single response 
message CMessageCheckSinglePublishResponse
{
	optional uint32 TodayPublish			= 1;
	optional uint32 OncePublish				= 2;
	optional uint32 TotalFinish				= 3;
	repeated PBSingleColorRank SingleRank	= 4;
};

// single publish response
message CMessagePlayerSinglePublishResponse
{
	optional uint32 TaskColor		= 1;
};

// refresh task response
message CMessageRefreshSingleTaskResponse
{
	optional uint32 TaskColor		= 1;
	optional uint32 TaskID			= 2;
};
