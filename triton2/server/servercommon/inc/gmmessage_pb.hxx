import "property_pb.hxx";
import "db_msg_pb.hxx";

option optimize_for = SPEED;

enum EMGMCmdMessageID // 0x4000 + 0x8000 = 0xC000
{
    ID_G2M_CMDNORMAL_RESULT					= 0xC000; 
    ID_M2G_KICKROLE_CMD						= 0xC001;
    ID_M2G_MOVEROLE_CMD						= 0xC002;
    ID_M2G_SHUTUP_CMD						= 0xC003;
    ID_M2G_CANCLESHUTUP_CMD					= 0xC004;
    ID_M2G_FROZENACCOUNT_CMD				= 0xC005;
    ID_M2G_UNFROZENACCOUNT_CMD				= 0xC006;
    ID_M2G_TRUSTEEUSER_CMD					= 0xC007;
    ID_M2G_UNTRUSTEEUSER_CMD				= 0xC008;
    ID_M2G_ENDTASK_CMD						= 0xC009;
    ID_M2G_TRUSTEESTORAGE_CMD				= 0xC00A;
    ID_M2G_UNTRUSTEESTORAGE_CMD				= 0xC00B;
    ID_M2G_RECOVERROLE_CMD					= 0xC00C;
    ID_M2G_POSTBULLETIN_CMD					= 0xC00D;
    ID_M2G_MULTIEXP_CMD						= 0xC00E;
    ID_M2G_CANCELMULTIEXP_CMD				= 0xC00F;
    ID_M2G_CHANGEMONEY_CMD					= 0xC010;
    ID_M2G_CHANGEEXP_CMD					= 0xC011;
    ID_M2G_CHANGEITEM_CMD					= 0xC012;
    ID_M2G_DELETEROLE_CMD					= 0xC013;
    ID_M2G_CLEARBAG_CMD						= 0xC014;

    /*��ɫ��Ϣ�ӿ�*/	
    ID_M2G_USERSOCIALINFO_CMD				= 0xC015;
    ID_G2M_USERSOCIALINFO_RESULT			= 0xC016;
    ID_M2G_ROLEDETAIL_CMD					= 0xC020;
    ID_G2M_ROLEDETAIL_RESULT				= 0xC021;
    ID_M2G_USERSTORAGEINFO_CMD				= 0xC022;
    ID_G2M_USERSTORAGEINFO_RESULT			= 0xC023;
    ID_M2G_ROLELOCATION_CMD					= 0xC024;
    ID_G2M_ROLELOCATION_RESULT				= 0xC025;
    ID_M2G_USERLEVELINFO_CMD				= 0xC026;
    ID_G2M_USERLEVELINFO_RESULT				= 0xC027;

    /*��Ʒ�ƶ���Ϣ*/
    ID_M2G_GOODSHISTORYTONPC_CMD			= 0xC028;
    ID_G2M_GOODSHISTORYTONPC_RESULT			= 0xC029;
    ID_M2G_GOODSHISTORYFROMNPC_CMD			= 0xC02A;
    ID_G2M_GOODSHISTORYFROMNPC_RESULT		= 0xC02B;
    ID_M2G_GOODSHISTORYBETWEENUSERS_CMD		= 0xC02C;
    ID_G2M_GOODSHISTORYBETWEENUSERS_RESULT	= 0xC02D;
    ID_M2G_GOODSHISTORY_CMD					= 0xC02E;
    ID_G2M_GOODSHISTORY_RESULT				= 0xC02F;
    ID_M2G_PETHISTORY_CMD					= 0xC030;
    ID_G2M_PETHISTORY_RESULT				= 0xC031;

    /*��ɫ������¼*/
    ID_M2G_OPERATIONDETAIL_CMD				= 0xC032;
    ID_G2M_OPERATIONDETAIL_RESULT			= 0xC033;

    /*��Ϸ������Ϣ*/
    ID_M2G_NPCDETAIL_CMD					= 0xC034;
    ID_G2M_NPCDETAIL_RESULT					= 0xC035;
    ID_M2G_GOODSDROPLOG_CMD					= 0xC036;
    ID_G2M_GOODSDROPLOG_RESULT				= 0xC037;

    /*�����ѯ*/
    ID_M2G_TASKINFO_CMD						= 0xC038;
    ID_G2M_TASKINFO_RESULT					= 0xC039;

    /*��¼�ǳ���¼*/
    ID_M2G_LOGININFO_CMD					= 0xC03A;
    ID_G2M_LOGININFO_RESULT					= 0xC03B;
    ID_M2G_ONLINETIME_CMD					= 0xC03C;
    ID_G2M_ONLINETIME_RESULT				= 0xC03D;
    ID_M2G_IPINFO_CMD						= 0xC03E;
    ID_G2M_IPINFO_RESULT					= 0xC03F;
    ID_M2G_USERINFOBYIP_CMD					= 0xC040;
    ID_G2M_USERINFOBYIP_RESULT				= 0xC041;
    ID_M2G_ATTRCHANGEHISTORY_CMD			= 0xC042;
    ID_G2M_ATTRCHANGEHISTORY_RESULT			= 0xC043;

    /* ���ݿ�ά�� */
    ID_M2G_ROLEPROTO_CMD					= 0xC044;

    /* �̳� */
    ID_M2G_IBINFO_CMD						= 0xC045;
    ID_M2G_SETIBPRICE_CMD					= 0xC046;
    ID_M2G_SETIBLOCATION_CMD				= 0xC047;
    ID_M2G_IBONSALE_CMD						= 0xC048;
    ID_M2G_IBNOTSALE_CMD					= 0xC049;
    ID_M2G_IBDESCRIPT_CMD					= 0xC04A;
    ID_M2G_IPBIND_CMD						= 0xC04B;

    /* 2.4 �汾���� */
    ID_M2G_ROLEEQUIPMENT_CMD				= 0xC04C; 
    ID_M2G_ROLEPACKINFO_CMD					= 0xC04D; 
    ID_M2G_ROLEITEMINPACK_CMD				= 0xC04E; 
    ID_M2G_ROLESKILLINFO_CMD				= 0xC04F;
    ID_M2G_ROLESKILLDETAIL_CMD				= 0xC050;

    ID_G2M_ROLEEQUIPMENT_RESULT				= 0xC051; 
    ID_G2M_ROLEPACKINFO_RESULT				= 0xC052; 
    ID_G2M_ROLEITEMINPACK_RESULT			= 0xC053; 
    ID_G2M_ROLESKILLINFO_RESULT				= 0xC054;
    ID_G2M_ROLESKILLDETAIL_RESULT			= 0xC055;

    /* �̳����� */
    ID_G2M_IBINFO_RESULT					= 0xC056;

    // �������װ����ϸ����Ҳֿ���ϸ
    ID_M2G_ROLEEQUIPMENT_DETAIL_CMD         = 0xC058;
    ID_M2G_ROLESTORAGE_DETAIL_CMD           = 0xC059;
    ID_G2M_ROLEEQUIPMENT_DETAIL_RESULT      = 0xC05A;
    ID_G2M_ROLESTORAGE_DETAIL_RESULT        = 0xC05B;

    /* �NPC ��ȡ��Ʒ */
    ID_S2E_USERITEMLIST_REQUEST				= 0xC060;       // ���ѯ��Ϣ 
    ID_E2S_USERITEMLIST_RESPONSE			= 0xC061;

    ID_S2E_USERITEMMINUS_REQUEST			= 0xC062;      // ��ȡ���Ʒ��Ϣ
    ID_E2S_USERITEMMINUS_RESPONSE			= 0xC063;

    ID_S2E_ACTIVITYLIST_REQUEST				= 0xC064;       // �鿴��б�
    ID_E2S_ACTIVITYLIST_RESPONSE			= 0xC065;

    // ��ֵ֪ͨ
    ID_M2G_USER_CHARGE_NOTICE               = 0xC866;       // ��ֵ֪ͨ

    // ������
    ID_S2G_FANGCHENMI_REQUEST			= 0xC067;   // �����������Ч��ʱ���ѯ
    ID_G2S_FANGCHENMI_RESPONSE			= 0xC068;   // ����ȥEraing��ѯ�󷵻ظ������Ļ�Ӧ
    ID_G2S_FCMPLAYERLIST_NOTIFY			= 0xC069;   // ����֪ͨ�����������������
	ID_G2S_FCMPLAYERRESET_NOTIFY		= 0xC06A;	// Խ�ϰ�ÿ�շ�����״̬��Ҫ����
	ID_S2G_FCMPLAYERRESET_REQUEST		= 0xC06E;	// Խ�ϰ��������������

	// �޸���������
	ID_S2G_CHANGEGATE_NOTIFY			= 0xC06B;
	
	// �����ҲƲ����������
	ID_S2G_REQUEST_RESETROLEPASSWORD	= 0xC06C; 
	
	// �����ҲƲ��������Ϣ��Ӧ
	ID_G2S_RESPONSE_RESETROLEPASSWORD	= 0xC06D; 

	ID_M2G_REQUEST_ROLEITEMOPERATE 	= 0xC070;
	ID_M2G_ROLEMONEYOPERATE 	= 0xC071;
	ID_M2G_REQUEST_ROLEEXP 		= 0xC072;
	ID_M2G_REQUEST_ROLEITEMLEVELUP 	= 0xC073;

    // ����MAC��Ϣ
    ID_M2G_FROZENMAC_CMD				= 0xC075;
    ID_M2G_UNFROZENMAC_CMD				= 0xC076;

	// ������������ [3/10/2010 GaoHong]
	ID_M2G_REQUEST_FASTFREEZE_CMD		= 0xC077;
	ID_M2G_REQUEST_UNFASTFREEZE_CMD		= 0xC078;

	// �������壬���Ų�ѯ�ӿ�
	ID_M2G_REQUEST_CORPSTOTAL_CMD		= 0xC079;
	ID_M2G_REQUEST_CORPSDETAIL_CMD		= 0xC07A;

	// ����ͨ�ò�ѯ��Ϣ
	ID_M2G_REQUEST_CORPSINFO_CMD		= 0xC07B;
	ID_M2G_REQUEST_ROLEINFO_CMD		= 0xC07C;

	// ����ҷ��������ʼ�
	ID_S2G_NOTIFY_OFFLINEMAIL		= 0xC07D;

	// �ָ�װ��
	ID_M2G_ROLE_ITEM_RECOVERY_CMD		= 0xC07E;

	// ���ط��ص����ݿ��ѯ�����
	ID_G2M_SQL_QUERY_RESULT			= 0xC07F;

	// ����ʼ���ѯ
	ID_M2G_QUERY_ROLE_MAIL_CMD		= 0xC080;

	// ����ɵ������ѯ
	ID_M2G_FINISHED_TASKINFO_CMD		= 0xC081;

	// ��ѯ��һ�õĳƺ�
	ID_M2G_QUERY_ROLETITLE_CMD		= 0xC082;
};

/*
 *
 * CGMMessageKickRoleCmd
 * �����Ҳ��ڴ��ߣ�Ҳ���سɹ� 
 *
 */


/*ע�������ֶ���ȫ����GM�ĵ��ϵ�������*/
message CGMMessageKickRoleCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
};

message CGMMessageCmdNormalResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 result = 3; 
};

/**************��Ϣ��ѯ�ӿ�*******************/

/*��ɫ��ϸ��Ϣ*/
message CGMMessageRoleDetailCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
    optional int32 type = 4;
};

message PBRoleInfo
{
    optional int32 role_id = 1;
    optional int32 role_status = 2;
    optional int32 account_id = 3;
    optional string role_name = 4;
    optional int32 is_alive = 5;
    optional int32 gender_id = 6;
    optional int32 metier_id = 7;
    optional int32 nationality_id = 8;
    optional int32 face_type = 9;
    optional int32 line_id = 10;
    optional int32 map_id = 11;
    optional int32 pos_x = 12;
    optional int32 pos_y = 13;
    optional int32 role_level = 14;
    optional int64 role_expr = 15;
    optional int32 role_money = 16;
    optional int32 bounded_money = 17;
    optional int32 login_time = 18;
    optional int32 online_duration = 19;
    optional int32 update_time = 20;
    optional int32 create_time = 21;
    optional PBProperty proto = 22;
	optional string login_ip = 23;
};

message CGMMessageRoleDetailResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional PBRoleInfo proto = 3;
};

/*��ɫ�ֿ��ѯ*/
message CGMMessageUserStorageInfoCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
    optional int32 page = 4;
};

message CGMMessageUserStorageInfoResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional PBItemBox items = 3;
};

/*��ɫλ�ò�ѯ*/
message CGMMessageRoleLocationCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
};

message CGMMessageRoleLocationResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 line_id = 3;
    optional int32 map_id = 4;
    optional int32 x = 5;
    optional int32 y = 6;
    optional int32 role_id = 7;
};

/*��ҵľ���ȼ���־��ѯ*/
message CGMMessageUserLevelInfoCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 role_id = 3;
    optional string start_time = 4;
    optional string end_time = 5;
};

message PBRoleUpgradeInfo
{
    optional int32 level = 1;
    optional int32 up_period = 2; /*��������ʱ��*/
    optional int32 up_time = 3;   /*�����˵ȼ���ʱ��*/
};

message CGMMessageUserLevelInfoResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    repeated PBRoleUpgradeInfo role_upgrade_info = 3;
};

/*��ҵ�����ϵϵͳ��ѯ*/
message CGMMessageUserSocialInfoCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
    optional uint32	type	= 4;
};

message CGMMessageUserSocialInfoResult
{
    optional uint32 session_id		= 1;
    optional uint32 fd				= 2;
    optional PBFriend friends		= 3;
    optional string familyname		= 4;
    optional string corpsname		= 5;
    optional uint32 spouseid		= 6;
    optional uint32	WeddingModule   = 7;
    optional uint32	MarriageID		= 8;	// ���ID
    optional string WeddingTime		= 9;	// �������ʱ��
    optional string MarriageTime	= 10;	// ���ʱ��
    optional PBMatrixInfo MatrixInfo = 11;	// ��Ե��Ϣ
};

/*��Ʒ�ƶ���¼*/
/*�����NPC*/
message CGMMessageGoodsHistoryToNPCCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id	= 3;
    optional int32 role_flag = 4;
    optional string npc_name = 5;
    optional string start_time = 6;
    optional string end_time = 7;
};

message PBItemExchange2Npc
{
    optional string npc_name = 1;
    optional string item_name = 2;
    optional int32  item_num = 3;
    optional string exchange_time = 4;
};

message CGMMessageGoodsHistoryToNPCResult
{
    repeated PBItemExchange2Npc items_selled = 1;
};

/*NPC�����*/
message CGMMessageGoodsHistoryFromNPCCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id	= 3;
    optional int32 role_flag = 4;
    optional string npc_name = 5;
    optional string start_time = 6;
    optional string end_time = 7;
};


message CGMMessageGoodsHistoryFromNPCResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    repeated PBItemExchange2Npc items_buyed = 3;
};

/*��������*/
message CGMMessageGoodsHistoryBetweenUsersCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id1 = 3;
    optional int32 role_id2 = 4;
    optional string start_time = 5;
    optional string end_time = 6;
};

message PBItemExchange2Player
{
    optional string from = 1;
    optional string to = 2;
    optional string item_name = 3;
    optional string item_count = 4;
    optional string exchange_time = 5;
};

message CGMMessageGoodsHistoryBetweenUsersResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    repeated PBItemExchange2Player item_exchanged = 3;
};

/*��Ʒ�ƶ������ѯ*/
message CGMMessageGoodsHistoryCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional string item_id = 3;
    optional string start_time = 4;
    optional string end_time = 5;
};

message PBItemAction
{
    optional string from = 1;
    optional string to = 2;
    optional string action = 3;
    optional string action_time = 4;
};


message CGMMessageGoodsHistoryResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    repeated PBItemAction item_actioned = 3;
};

/*�����佫�ƶ������ѯ*/
message CGMMessagePetHistoryCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional string role_name = 3;
    optional int32 pet_id = 4;
    optional string start_time = 5;
    optional string end_time = 6;
};

message PBPetHistory
{
    optional string from = 1;
    optional string to = 2;
    optional string action = 3;
    optional string action_time = 4;
    optional string action_attr = 5;
};

message CGMMessagePetHistoryResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    repeated PBPetHistory pet_history = 3;
};

/*��ɫ������¼��ѯ*/
message CGMMessageOperationDetailCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 server_id = 3;
    optional int32 role_id = 4;
    optional string start_time = 5;
    optional string end_time = 6;
};        


/*����NPC�����Ʒ���NPC���ڵ�ͼ�Լ�NPC������*/
message CGMMessageNPCDetailCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional string npc_name = 3;
};

message PBNPCDetail
{
    optional int32 map_id = 1;
    optional string npc_location = 2;
};

message CGMMessageNPCDetailResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    repeated PBNPCDetail npc_detail= 3;
};

/*��ҵ���Ʒ�ĵ�����־��ѯ*/
message CGMMessageGoodsDropLogCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 goods_id = 3;
    optional string map_name = 4;
    optional string start_time = 5;	
    optional string end_time = 6;	
};

message PBGoodsDropLog
{
    optional string role_name = 1;
    optional string drop_time = 2;
    optional int32 total_num = 3;	
    optional int32 drop_rate = 4;	
};

message CGMMessageGoodsDropLogResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    repeated PBGoodsDropLog goods_drop_log = 3; 
};

/* ��ѯָ���Ľ�ɫ��ǰ��������� */
message CGMMessageTaskInfoCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
};

message PBTaskInfo
{
    optional int32 task_id = 1;
    optional string task_name = 2;
    optional int32 finish_type = 3; /* 1 �C ����� 0 �C δ��� */
};

message CGMMessageTaskInfoResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    repeated PBTaskInfo task_detail = 3;
};


/*��¼�ǳ���¼��ѯ*/
message CGMMessageLoginInfoCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional string user_name = 3;
    optional string start_time = 4;
    optional string end_time = 5;
};

message PBLoginInfo
{
    optional int32 login_in_time = 1;
    optional int32 login_in_money = 2;
    optional int32 login_in_exp = 3 ;
    optional int32 login_in_ip = 4;
    optional int32 login_out_time = 5;
    optional int32 login_out_money = 6;
    optional int32 login_out_exp = 7;
};

message CGMMessageLoginInfoResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    repeated PBLoginInfo login_info = 3;
};

/*��ѯ�ʺŽ�ɫ������ʱ��*/

/* ָ���ʺš���ɫ��ĳʱ����ڵĵ���ǳ�IP��ַ IpInfo */ 

/* ��ѯĳָ��IP��ַ�µ�ȫ����ҡ���ɫ����Ϣ�� UserInfoByIp */

/**************** ��Ϸ����ӿ� **************/
/*����*/
message CGMMessageShutUpCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
    optional int32 channel = 4;
    optional int32 period = 5;
};



/*�����*/
message CGMMessageCancelShutUpCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
    optional int32 channel = 4;
};


/*�����ʺ� */
message CGMMessageFreezeAccountCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 user_id = 3;
};

message CGMMessageFreezeAccountBatCmd
{
	optional uint32 session_id = 1;
	optional uint32 fd = 2;
	optional string uid_list = 3;
};


/* �ⶳ���ʺ�*/
message CGMMessageUnFreezeAccountCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 user_id = 3;
};


/* �й��ʺ�*/
message CGMMessageTrusteeUserCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 user_id = 3;
    optional string password = 4;
};


/*����й�*/
message CGMMessageUnTrusteeUserCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 user_id = 3;
};



/* ˲�����*/
/*
 * CGMMessageMoveRoleCmd
 * ֻ�ܲ����������
 *
 * ����type�Ĳ�ͬ��taget_location����ĺ���Ҳ����ͬ��
 * �����ƶ���ĳ����λ�ã�taget_location������λ�ã�
 * �Ƶ�ĳNPC������taget_location����NPCλ�ã�
 * �Ƶ�ĳ��Ҹ�����taget_location�������λ�á��������£�
 * 0��type_user�������ƶ�����Ҹ���, target_location=user_id���������id.
 * 1��type_scene�������ƶ���ĳ�����������λ��, target_location=scene_id��������id��
 * 2��type_npc�������ƶ���npc������target_location=npc_id������npc id��
 *
 */

message CGMMessageMoveRoleCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
    optional int32 server_id = 4;
    optional int32 type = 5;
    optional string  target_location = 6;
};


/*��������*/
message CGMMessageEndTaskCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
    optional int32 task_id = 4;
};



/* �ֿ��й� */
message CGMMessageTrusteeStorageCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
};

/*����ֿ��й�*/
message CGMMessageUnTrusteeStorageCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
};


/*��ɫ�ָ�*/
message CGMMessageRecoverRoleCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
};

/*********************��Ϸ����ά��***************/
/*�������� PostBulletin*/
message CGMMessagePostBulletinCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional string content = 3;
    optional uint32 times = 4;
    optional uint32 interval = 5;
};

/* ˫���������� MultiExp*/
message CGMMessageMultiExpCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 gateway_id = 3;
    optional int32 server_id = 4;
    optional int32 exp_type = 5;
    optional string multi_num = 6;
    optional string reason = 7;
    optional int32 start_time = 8;
    optional int32 end_time = 9;
};


/* ȡ��˫������ CancelMultiExp */
/*
message CGMMessageCancelMultiExpCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 gateway_id = 3;
    optional int32 server_id = 4;
    optional int32 exp_type = 5;
};
*/
message CGMMessageCancelMultiExpCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 gateway_id = 3;
    optional int32 server_id = 4;
    optional int32 exp_type = 5;
    optional int32 multi_num = 6;
    optional string reason = 7;
    optional int32 start_time = 8;
    optional int32 end_time = 9;
};

/************** ��ɫ�����޸� *****************/
/*��Ǯ�Ĳ��� ChangeMoney */
message CGMMessageChangeMoneyCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 server_id = 3;
    optional int32 role_id = 4;
    optional int32 change_num = 5;
};

/* ����Ĳ��� ChangeExp*/
message CGMMessageChangeExpCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 server_id = 3;
    optional int32 role_id = 4;
    optional int32 change_num = 5;
};

/*������Ʒ�Ĳ��� ChangeItem */
message CGMMessageChangeItemCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 server_id = 3;
    optional int32 role_id = 4;
    optional int32 item_code = 5;
    optional int32 item_num = 6;
};

/************* ��ɫ���� **************/
/*ɾ����ɫ DeleteRole*/
message CGMMessageDeleteRoleCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
};

/*�����ҵİ��� ClearBag*/ 
message CGMMessageClearBagCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 role_id = 3;
    optional string bag_name = 4;
};

/*�佫���� ChangePet*/
message CGMMessageChangePetCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 role_id = 3;
    optional string user_name = 4;
};

/* ��������GM�˺� SetOLGMAccount*/
message CGMMessageSetOLGMAccountCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 user_id = 3;
    optional string password = 4;
};

/* �̳���Ʒ��ʾ IbInfo */
message CGMMessageIbInfoCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 item_id = 3;
};

message PBIbItem
{
    optional uint32 item_id = 1;
    optional string item_location = 2;
    optional uint32 pay_type = 3;
    optional uint32 item_type = 4;
    optional uint32 item_limit = 5;
    optional uint32 price = 6;
    optional uint32 discount = 7;
    optional uint32 start_time = 8;
    optional uint32 sale_room = 9;
    optional uint32 on_sale = 10;
};

message CGMMessageIbInfoResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 isall = 3;
    repeated PBIbItem ibitems = 4;
};

/* �̳���Ʒ�۸����� SetIbPrice */
message CGMMessageSetIbPriceCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 item_id = 3;        
    optional uint32 price = 4;  // ��Ʒ�۸�
    optional uint32 time = 5;   // ����ʱ�䣬����
    optional uint32 limit_num = 6;      // ��������� -1 ��ʾû����
};
    
/* �̳���Ʒ���� SetIbLocation */
message CGMMessageSetIbLocationCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional string pos = 3;
};

/* �̳���Ʒ�ϼ� IbOnSale */
message CGMMessageIbOnSaleCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 item_id = 3;
    optional string pos = 4;
};

/* �̳���Ʒ�¼� IbNotSale */
message CGMMessageIbNotSaleCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 item_id = 3;
};

/* ��̬�����̳���Ʒ���� IbDescript */
message CGMMessageIbDescriptCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 item_id = 3;
    optional string description = 4;
};

/* �ʻ�IP�� IpBind */
message CGMMessageIpBindCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 user_id = 3;
    optional string ip = 4;
    optional uint32 type = 5;
}

/************* ���ݿ�������ֶβ�ѯ���� **************/
message CGMMessageRoleProtoCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 role_id = 3;
    optional string field_name = 4;
};


/* 2.4 �汾���� */
message CGMMessageRoleEquipmentCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 role_id = 3;
};

message CGMMessageRolePackInfoCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 role_id = 3;
};

message CGMMessageRoleItemInPackCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 role_id = 3;
    optional uint32 item_id = 4;
};

message CGMMessageRoleSkillInfoCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 role_id = 3;
};

message CGMMessageRoleSkillDetailCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 role_id = 3;
    optional uint32 skill_id = 4;
};

/* ��ѯ��� */
message CGMMessageRoleEquipmentResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional PBItemBox proto = 3;
};

message CGMMessageRolePackInfoResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional PBItemBox proto = 3;
};

message CGMMessageRoleItemInPackResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional PBItemObject proto = 3;
};

message CGMMessageRoleSkillInfoResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional PBSkillList proto = 3;
};

message CGMMessageRoleSkillDetailResult
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional PBSkillObject proto = 3;
};

/* �NPC��ȡ��Ʒ�ӿ� */
message CMessageActivityListRequest
{
    optional uint32 RoleID = 1;
};

message PBActivity
{
    optional uint32 MenuID = 1;
    optional string Desc = 2;
    optional uint32 BeginTime = 3;
    optional uint32 EndTime = 4;
};

message CMessageActivityListResponse
{
    optional uint32 RoleID = 1;
    repeated PBActivity activity = 2;
};

message CMessageUserItemListRequest
{
    optional uint32 AccountID = 1;      // �ʺ�ID
    optional uint32 RoleID = 2;         // ��ɫID
    optional uint32 MenuID = 3;         // �˵�ID
    optional uint32 RoleLevel = 4;      // ��ɫ�ȼ�
    optional uint32 RoleMetier = 5;     // ��ɫְҵ
    optional uint32 RoleGender = 6;     // ��ɫ�Ա�
};

message PBActivityItem
{
    optional string ItemCode = 1;   // ��ƷID
    optional uint32 Number = 2;     // ��Ʒ����
    optional uint32 ActivityID = 3; // �ID
};


message CMessageUserItemListResponse
{
    optional int32 Result = 1;      // �ɹ����
    optional uint32 MenuID = 2;     // �˵�ID
    optional uint32 RoleID = 3;     // ��ɫID
    repeated PBActivityItem items = 4;  // �����ĵ���
};

message CMessageUserItemMinusRequest
{
    optional uint32 AccountID = 1;      // ��ȡ��Ʒ���ʺ�ID
    optional uint32 RoleID = 2;         // ��ɫID
    optional uint32 ActivityID = 3;     // �ID
    optional string ItemCode = 4;       // ��ȡ��Ʒ��ID
    optional uint32 ItemNum = 5;        // ��ȡ��Ʒ����Ŀ, ԭ���ϲ��������������ȡ����Ŀ��Ҫôȫ��ȡ��Ҫô����ȡ
    optional uint32 RoleLevel = 6;      // ��ɫ�ȼ�
    optional uint32 RoleMetier = 7;     // ��ɫְҵ
};

message CMessageUserItemMinusResponse
{
    optional int32 Result = 1;          // ��ȡ���
    optional int32 MenuID = 2;      	// �˵�ID
    optional int32 RoleID = 3;          // ��ɫID
    optional PBActivityItem Item = 4;   // ��ȡ����Ʒ, �Կɶѵ�����Ʒ������number���ܳ��������Ķѵ�����
};

message CGMMessageRoleEquipmentDetailCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 role_id = 3;
    optional uint32 item_id = 4;
};

message CGMMessageRoleStorageDetailCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional uint32 role_id = 3;
    optional uint32 item_id = 4;
};

message CGMMessageRoleEquipmentDetailResult
{
    optional uint32 session_id = 1; 
    optional uint32 fd = 2;
    optional PBItemObject proto = 3;
};

message CGMMessageRoleStorageDetailResult
{
    optional uint32 session_id = 1; 
    optional uint32 fd = 2;
    optional PBItemObject proto = 3;
};

// ������ʹ��
message PBSubjectAmount
{
    optional uint32 SubjectID = 1; // ��Ŀ
    optional uint32 Amount = 2; // ����
}

message CMessageFangChenMiResponse
{
    optional uint32 CharID = 1; // ��ɫID
    repeated PBSubjectAmount Subjects = 2; // ��Ŀ��Ϣ
}

message PBFangChenMi
{
    optional uint32 CharID = 1; // ��ɫID
    optional uint32 CharLevel = 2; // ��ɫ����
    optional uint32 CharMetier = 3; // ��ɫְҵ
    optional uint32 Money1 = 4; // �ǰ󶨽��
    optional uint32 Money2 = 5; // �󶨽��
    optional uint64 Exp = 6; 	// ��ǰ����ֵ
}

message CMessageFangChenMiRequest
{
    repeated PBFangChenMi RoleDetail = 1;
}

message CMessageFCMPlayerListNotify
{
    repeated uint32 ReportPlayer = 1;       // ��Ҫ�ϱ���״̬������б�
}

message CMessageFCMPlayerResetRequest
{
	optional uint32 AccountID = 1;	// �˺�ID
	optional uint32 Seconds   = 2;  // ���õ�����
};

message CMessageChangeGateNotify
{
	optional uint32	Type	= 1;
	optional string	Name	= 2;
	optional int32	Param1	= 3;
	optional int32	Param2	= 4;
	optional int32	Param3	= 5;
	optional int32	Param4	= 6;
};

// ��¼������->���ط����� �����ҲƲ��������Ϣ����
message CMessageResetRolePasswordRequest
{
	optional uint32 session_id = 1; 
	optional uint32 fd = 2;
	optional uint32	role_id = 3;				// ��ҵĽ�ɫID
};

// ���ط�����->��¼������ �����ҲƲ�����
message CMessageResetRolePasswordResponse
{
	optional uint32 session_id = 1; 
	optional uint32 fd = 2;
	optional uint32	Errcode = 3;			// ������
};

message CGMMessageRoleItemOperatedCmd
{
	optional uint32 session_id 	= 1; 
	optional uint32 fd 		= 2;
	optional uint32 role_id		= 3;
	optional int32 op_type		= 4;
	optional int32 item_id 		= 5;
	optional uint64 item_guid	= 6;
	optional string start_time 	= 7;
	optional string end_time 	= 8;
	optional int32  page 		= 9;
};

message CGMMessageRoleMoneyOperateCmd
{
	optional uint32 session_id 	= 1; 
	optional uint32 fd 		= 2;
	optional uint32 role_id		= 3;
	optional int32 op_type		= 4;
	optional int32 item_type 	= 5;
	optional string start_time 	= 6;
	optional string end_time 	= 7;
	optional int32  page 		= 8;
};

message CGMMessageRoleExpCmd
{
	optional uint32 session_id 	= 1; 
	optional uint32 fd 		= 2;
	optional uint32 role_id		= 3;
	optional int32 op_type		= 4;
	optional int32 exp_type 	= 5;
	optional string start_time 	= 6;
	optional string end_time 	= 7;
	optional int32  page 		= 8;

};

message CGMMessageRoleItemLevelUpCmd
{
	optional uint32 session_id 	= 1; 
	optional uint32 fd 		= 2;
	optional int32  page 		= 3;
	optional uint32 role_id		= 4;
	optional int32 item_id 		= 5;
	optional string start_time 	= 6;
	optional string end_time 	= 7;
};

message CGMMessageFreezeMacCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional string mac = 3;
};


/* �ⶳ���ʺ�*/
message CGMMessageUnFreezeMacCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional string mac = 3;
};

/* ��ѯ�����б� */
message CGMMessageCorpsTotalCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional int32 type = 3;
    optional int32 page	= 4;
};

message CGMMessageCorpsDetailCmd
{
    optional uint32 session_id = 1;
    optional uint32 fd = 2;
    optional string corps_name = 3; 
    optional int32 type = 4;
};

message CGMMessageCorpsInfoCmd
{
    optional uint32 session_id	= 1;
    optional uint32 fd		= 2;
    optional string corps_name	= 3; 
    optional int32 type		= 4;
    optional string start_time 	= 6;
    optional string end_time 	= 7;
    optional int32 page		= 8;
};

message CGMMessageRoleInfoCmd
{
    optional uint32 session_id	= 1;
    optional uint32 fd		= 2;
    optional uint32 role_id	= 3; 
    optional int32 type		= 4;
    optional string start_time 	= 6;
    optional string end_time 	= 7;
    optional int32 page		= 8;
};

message CGMMsgRoleItemRecoveryCmd
{
    optional uint32 session_id	= 1;
    optional uint32 fd		= 2;
    optional uint32 role_id	= 3; 
    optional int32  type	= 4; 
    optional uint64 item_id	= 5; 
    optional string start_time	= 6; 
    optional string end_time	= 7; 
    optional uint32 page	= 8; 
};

message CMessageOfflineSysMailNotify
{
	optional uint32 	RoleId 		= 1; // ��ɫID
	optional uint32 	MailType 	= 2; // ϵͳ�ʼ�����
	optional uint32 	AttachMoney 	= 3; // �ǰ�𸽼�
	repeated PBItemObject 	AttachItem	= 4; // �������߸���
    	optional uint32 session_id		= 5;
    	optional uint32 fd			= 6;
};

message CGMMessageSqlQueryResult
{
    optional uint32 session_id				= 1;
    optional uint32 fd					= 2;
    optional uint32 type 				= 3;
    optional CMessageExecuteSqlResponse3 SqlResult 	= 4;
    optional uint32 page				= 5;
};

message CGMMessageUserInfoByIPCmd
{
	optional uint32 session_id 	= 1; 
	optional uint32 fd 		= 2;
	optional string ip		= 3;
	optional string start_time 	= 4;
	optional string end_time 	= 5;
	optional int32  type 		= 6;
	optional int32  page 		= 7;
};

message PlayerInfo
{
	optional uint32 account_id	= 1;
	optional string account_name	= 2;
	optional uint32 role_id		= 3;
	optional string role_name	= 4;
	optional int32	login_time 	= 5;
	optional int32	role_level	= 6;
	optional int32	metier_id	= 7;
	optional int32	cpu_id		= 8;
	optional int32	disk_id		= 9;
	optional string	mac		= 10;
	optional int32	line_id		= 11;
	optional int32	map_id		= 12;
	optional int32	game_id		= 13;
};

message IPInfo
{
	optional uint32 ip 		= 1;
	optional uint32 role_num	= 2;
	repeated PlayerInfo player_info = 3;
};

message CGMMsgUserInfoByIPResult
{
	optional uint32 session_id 	= 1; 
	optional uint32 fd 		= 2;
	repeated IPInfo ipinfo		= 3;
	optional uint32 ZeroIP		= 4;
};

message CGMMessageQueryRoleMailCmd
{
    optional uint32 session_id				= 1;
    optional uint32 fd					= 2;
    optional uint32 role_id				= 3;
    optional int32 page					= 4;
};
