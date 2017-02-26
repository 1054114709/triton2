import "servermessage_pb.hxx";
import "property_pb.hxx";

// ������ٶ�����/������
option optimize_for = SPEED;


enum LOG_MSG_ID
{	
	ID_S2L_LOGMESSAGE					= 0xC400;		// ����������->��־������
	ID_L2L_HANDLETIMEOUT				= 0xC401;		// ֪ͨÿ��HANDLE�߳�,��ʱ�洢ʱ�䵽
	ID_S2L_ROLE_OPTASK					= 0xC402;		// ��������¼�
	ID_S2L_ROLE_KILLED					= 0xC403;		// ��������¼�
	ID_S2L_ROLE_LOGOUT					= 0xC404;		// ����뿪�����¼�
	ID_S2L_ROLE_OPEXP					= 0xC405;		// ��һ�û�ʧȥ�����¼�
	ID_S2L_ROLE_OPMONEY					= 0xC406;		// ��û�û�ʧȥ��Ǯ�¼�
	ID_S2L_ROLE_OPITEM					= 0xC407;		// ��Ҷ���Ʒ����Ϊ��־
	ID_S2L_ROLE_GHOST					= 0xC408;		// �����Ʒ����
	ID_S2L_ROLE_UPGRADE					= 0xC409;		// ��������¼�
	ID_S2L_ITEM_UPGRADE					= 0xC40A;		// ��Ʒ�����¼�
	ID_S2L_ORGE_DROPED					= 0xC40B;		// �������
	ID_S2L_ITEM_DISPEAR					= 0xC40C;		// ��Ʒ��
	ID_S2L_FAMILY_ACTION				= 0xC40D;		// �������
	ID_S2L_CORPS_ACTION					= 0xC40E;		// ���Ų���
	ID_S2L_MAIL							= 0xC40F;		// �ʼ���־	
    ID_S2L_SERVER_STAT_INFO_NOTICE		= 0xC410;		// ������ͳ����־
	ID_G2L_FAMILY_BATTLE				= 0xC411;		// ����ս
	ID_G2L_CORPS_BATTLE					= 0xC412;		// ����ս
	ID_G2L_ROLE_CHAT					= 0xC413;		// ������־
	ID_G2L_REPETION						= 0xC414;
	ID_S2L_VALUABLE_EQUIP				= 0xC415;		// ������Ʒ����
	ID_S2L_BOSSORGEDIE					= 0xC416;		// boos�������ļ�¼
	ID_S2L_LIFESKILL					= 0xC417;		// ����ܵļ�¼
	ID_S2L_USEITEM_DROP					= 0xC418;		// ʹ����Ʒ����
	ID_S2L_EXCHANGELOG_LOG				= 0xC479;
	ID_S2L_MATRIX						= 0xC47A;		// ��Ե
	ID_S2L_WORLD						= 0xC47B;		// �����¼�
	ID_S2L_ROLE_DAMAGE					= 0xC47C;		// �˺�
	ID_S2L_ROLE_BUFFER					= 0xC47D;       // ��һ�û��߽��buffer
	ID_S2L_ROLE_REPE_SCORE				= 0xC47E;		// ��Ҹ������ּ�¼

};

// ID_L2L_HANDLETIMEOUT
message CMessageHandleTimeOut
{

};

// ID_S2L_ROLE_LOGOUT	��ҵǳ���־
message CMessageLogRoleLogout
{
	optional uint32 RoleID		= 1;
	optional uint32 OpTime		= 2;
	optional int32  LineID		= 3;
	optional uint64 RepetionID	= 4;
	optional int32  MapID		= 5;
	optional int32  RoleLevel	= 6;
	optional int32  MetierID	= 7;
	optional uint32	LoginIP		= 8;
	optional uint32 LoginTime	= 9;
	optional uint32 LogoutTime	= 10;
	optional EMLeaveReason LeaveReason = 11;
	optional int32	SaveReason	= 12;
	optional EMSaveResult SaveResult = 13;
	optional int32 	KickReason	= 14;
	optional int32 	KickCode	= 15;
};

// ��ɫ��ƷGhost
enum EPackType
{
	EM_ROLE_EQUIPMENT	= 1;
	EM_ROLE_PACKAGE		= 2;
	EM_ROLE_PACKAGE_KITBAG	= 3;
	EM_ROLE_STORAGE		= 4;
	EM_ROLE_STORAGE_KITBAG 	= 5;
};

// ID_S2L_ROLE_GHOST
message CMessageLogRoleGhost
{
	optional uint32 RoleID 		= 1;
	optional uint32 OpTime		= 2;
	optional EPackType PackType	= 3; 
	//optional PBItemBox PackInfo	= 4;
};

// ��ɫ����
enum EUpgradeType
{
	EM_UPGRADE_ROLE_EXP	= 0;
	EM_UPGRADE_TALENT_EXP	= 1;
	EM_UPGRADE_LIFE_EXP	= 2;
	EM_UPGRADE_PRODUCE_EXP	= 3;
	EM_UPGRADE_MW_EXP	= 4;
};

enum EExpAction
{
	EM_EXP_BY_HORNOR		= 1;	// ����ת��Ϊ����
	EM_EXP_BY_CARD			= 2;	// ��Ƭ��þ���
	EM_EXP_BY_MULTICOM		= 3;	// �һ���þ���
	EM_EXP_BY_COMMAND		= 4;	// GM ������
	EM_EXP_BY_TEAM_ALLOT		= 5;	// �ڵ���þ���
	EM_EXP_BY_FAMILY_ALLOT		= 6;	// �����ڵ�
	EM_EXP_BY_QUESTION		= 7;	// �����
	EM_EXP_BY_INVESTIGATION		= 8;	// �����ʾ�
	EM_EXP_BY_ERATING		= 9;	// ��͹ٽ���
	EM_EXP_BY_TASK			= 10;	// ������
	EM_EXP_BY_ENTITY_DIE		= 11; 	// ɱ��������
	EM_EXP_BY_BUFF			= 12; 	// �����Ӿ���̶�ֵBUFF
	EM_EXP_BY_FLOWER		= 13; 	// �����ʻ���þ���
	EM_EXP_BY_EXPITEM		= 14;	// ʹ�þ������
	EM_EXP_BY_BLACKPILLS	= 15;	// ʹ�úڹ���
	EM_EXP_BY_EXPILLS	= 16;	// ʹ�þ�����
    EM_EXP_BY_HANDIN        = 17;   // �Ͻ���Ʒ��ȡ����
	EM_EXP_BY_OFFLINE		= 18;	// �����߻�þ���
};

enum EBufferAction
{
	EM_BUFF_BY_SKILL			= 1;	// ���ܻ��BUFF
	EM_BUFF_BY_MAP				= 2;	// MAP����BUFF
	EM_BUFF_BY_YQSGROW			= 3;	// DEBUG������
	EM_BUFF_BY_BUFFITEM			= 4;	// ʹ��BUFF����
	EM_BUFF_BY_SYSTEM		    = 5;	// ϵͳ����BUFF
    EM_BUFF_BY_TIMEOUT			= 6;    // buff��ʱ
	EM_BUFF_BY_SELF				= 7;    // �Լ�ȥ��
	EM_BUFF_BY_DEATH			= 8;    // ����ʧȥbuff
	EM_BUFF_BY_CLOSEAUREOLE		= 9;    // ʧȥ�⻷Ч��
    EM_BUFF_BY_CHANGEMAP		= 10;   // ����ͼʧȥBUFF
    EM_BUFF_BY_LOGOFF			= 11;   // �ǳ�ʧȥBUFF
	EM_BUFF_BY_STATE_STONE      = 12;   // ����ʯʧȥbuff

};

// ������������ ID_S2L_ROLE_UPGRADE
message CMessageLogRoleUpgrade
{
	optional uint32 RoleID			= 1;
	optional uint32 UpgradeTime		= 2;
	optional uint32 MetierID		= 3;
	optional uint32 RoleLevel		= 4;
	optional EUpgradeType UpgradeType	= 5;
	optional uint32	SubType			= 6;
	optional uint32 CurrentLevel		= 7;
	optional uint32 DeltaLevel 		= 8;
};



// װ������ ID_S2L_ITEM_UPGRADE
message CMessageLogItemUpgrade
{
	optional uint32 ItemID 			= 1;	// ��ƷID
	optional uint64 ItemGUID		= 2;	// ��ƷGUID
	optional uint32 UpTime			= 3;	// ����ʱ��
	optional uint32 UpType			= 4;	// ��������
	optional uint32 Result			= 5;	// �������
	optional uint32 RoleID			= 6;	// ��ɫID
	optional uint32 PrevLevel		= 7;	// ����ǰ�ȼ�
	optional uint32 CurrLevel		= 8; 	// ������ȼ�
	optional uint32 Item1			= 9;	// ��Ʒ1 
	optional uint32 Item2			= 10; 	// ��Ʒ2
};

// ��Ʒ��־ 
enum EItemAction
{
	EM_GET_BY_IBSTORE	= 1; 	// ���̳ǻ����Ʒ
	EM_GET_BY_RECV_MAIL	= 2;	// ���ʼ������Ʒ
	EM_GET_BY_STALL_BUY	= 3;	// ͨ���������̯λ����Ʒ
	EM_GET_BY_EXCHANGE	= 4;	// ͨ����Ҽ佻���õ�
	EM_GET_BY_ACCEPT_TASK	= 5;	// ��������õ���Ʒ
	EM_GET_BY_END_TASK	= 6;	// ��������õ���Ʒ
	EM_GET_BY_ERATING	= 7;	// �ӻNPC���õ���Ʒ
	EM_GET_BY_PICKITEM	= 8;	// �ӵ��ϼ�����Ʒ
	EM_GET_BY_PRODUCE	= 9;	// ��������õ���Ʒ
	EM_GET_BY_CHANGE	= 10;	// ��Ʒת������
	EM_GET_BY_RUN_TASK	= 11;	// ���������л����Ʒ
	EM_GET_BY_NPC_SHOP	= 12;	// ͨ����NPC��������
	EM_GET_BY_DEFAULT	= 13;	// Ĭ�ϳ�ʼװ��
	EM_GET_BY_TASKITEM	= 14;	// ������Ʒ���
	EM_GET_BY_COLLECT	= 15;	// �ɼ����
	EM_GET_BY_COMPOSE	= 16;	// �ϳɻ��
	EM_GET_BY_REPETION	= 17;	// ��������
	EM_GET_BY_GMINSERT	= 18;	// GM INSERT
	EM_GET_BY_ROLLBACK	= 19;	// ����ʧ�ܺ󲹳������
	EM_GET_BY_DIRECTINS	= 20;	// ������ֱ�ӻ��
	EM_GET_BY_UNBOUND	= 21;	// �Ӵ��󶨻�ñ�ʯ
	EM_GET_BY_DECOMPOUND	= 22;	// �ֽ����
	EM_GET_BY_INVESTIGATION	= 23;	// �����ʾ���
	EM_GET_BY_GUAJI_SHOP	= 24;	// �һ�����
	EM_GET_BY_BUY_BACK	= 25;	// ��NPC���ع���Ʒ
	EM_GET_BY_AWARD		= 26;	// ��ȡ����
	EM_GET_BY_GETSTAR	= 27;	// ժ��
	EM_GET_BY_HONOR = 28;			// �����һ�
	EM_GET_BY_CARVE	= 29;		// �������
	EM_GET_BY_QLCOMPOSE	= 30;		// ��������ϳɻ��
	EM_GET_BY_TREASUREBOWL = 32;	// �۱������Ʒ
	EM_GET_BY_MWQUICKUP = 33;	// �������������Ʒ
	EM_GET_BY_SPIRIT_DOWNGRID = 34; // ��������Ʒ

	EM_LOST_BY_SEND_MAIL	= 50;	// �����ʼ�ʧȥ��Ʒ
	EM_LOST_BY_STALL_SELL	= 51;	// ͨ����̯������Ʒ
	EM_LOST_BY_EXCHANGE	= 52;	// ͨ����Ҽ佻��ʧȥ
	EM_LOST_BY_ACCEPT_TASK	= 53;	// ��������ʧȥ��Ʒ
	EM_LOST_BY_END_TASK	= 54;	// ��������ʧȥ��Ʒ
	EM_LOST_BY_ERATING	= 55;	// �ӻNPC��ʧȥ��Ʒ
	EM_LOST_BY_THROW_ITEM	= 56;	// ��Ҷ���������Ʒ
	EM_LOST_BY_PRODUCE	= 57;	// ���ͨ������ʧȥ����
	EM_LOST_BY_USE		= 58;	// ʹ�ú�ʧȥ��Ʒ
	EM_LOST_BY_OPEN_SLOT	= 59;	// ���ۺ�ʧȥ��Ʒ
	EM_LOST_BY_COMPOSE	= 60;	// �ϳɺ�ʧȥ��Ʒ
	EM_LOST_BY_EAT		= 61;	// �Ե���Ʒ����Ԫ��
	EM_LOST_BY_INSERT_SLOT	= 62;	// ʹ�ñ�ʯ��Ƕ��Ʒ
	EM_LOST_BY_UPGRADE	= 63;	// ������Ʒ
	EM_LOST_BY_CHANGE	= 64;	// ת����ʧȥ
	EM_LOST_BY_DECOMPOUND	= 65;	// �ֽ��ʧȥ
	EM_LOST_BY_SELL2NPC	= 66;	// ����NPCʧȥ
	EM_LOST_BY_JUDGE	= 67;	// ������ʧȥ
	EM_LOST_BY_BOUND	= 68;	// ��Ѫ��ʧȥ
	EM_LOST_BY_ABORTTASK	= 69;	// ���������ʧȥ
	EM_LOST_BY_DESTROY	= 70;	// ���ֱ��������Ʒ
	EM_LOST_BY_TIMEOUT	= 71;	// ��ʱ��Ʒʱ�䵽��ϵͳ�ջ�
	EM_LOST_BY_CHANGEEQUIP = 72;	// ת��װ��
	EM_LOST_BY_REPETION	= 73;		// ����Կ��
	EM_LOST_BY_GETSTAR	= 74;		// ժ��
	EM_LOST_BY_ADDSTAR	= 75;		// ����
	EM_LOST_BY_ADDEXTRA = 76;		// ��ӡ
	EM_LOST_BY_FANGCUN = 77;		// ѧϰ����ɽ����	
	EM_LOST_BY_MASTER = 78;			// �����ʦʧȥ
	EM_LOST_BY_CARVE = 79;			// ����ʧȥ
	EM_LOST_BY_MWQUICKUP = 80;	// ��������ʧȥ��Ʒ
	EM_LOST_BY_QLCOMPOSE	= 81;		// ��������ϳ�ʧȥ
	EM_START_USE_TIME_ITEM = 82;    //��ʼʹ����ʱ����
	EM_LOST_BY_SWORN		= 83;	// ���ʧȥ����
};

enum EMoneyAction
{
	EM_GET_BY_SELL2NPC	= 1;	// ����NPC
	EM_GET_BY_PICKMONEY	= 2;	// �ӵ��ϼ���
	EM_GET_BY_EXCHANGE_MONEY= 3;	// ���׻��
	EM_GET_BY_GMINSERT_MONEY= 4;	// GM����
	EM_GET_BY_STORE_MONEY	= 5;	// �Ӳֿ�֧ȡ��Ǯ
	EM_GET_BY_RED_BAG	= 6;	// ��ȡ���
	EM_GET_BY_RECV_MONEY	= 7;	// ���ʼ��õ�
	EM_GET_BY_QUESTLIB	= 8;	// ÿ�մ���
	EM_GET_BY_ERATING_MONEY = 9;	// Erating ����
	EM_GET_BY_CORPS		= 10; 	// �Ӿ��Ż�ȡ
	EM_GET_BY_FAMILY	= 11;	// �Ӽ����ȡ
	EM_GET_BY_STALL		= 12;	// ��̯���
	EM_GET_BY_TASK		= 13;	// �����������
	EM_GET_BY_GIFT		= 14;	// ������
	EM_GET_BY_WAR		= 15;	// ��ս�콱���
	EM_GET_BY_BOURSE	= 16;	// ��Ԫ���������л��
	EM_GET_BY_BOURSE_ERR = 17;	// Ԫ����������Ǯʧ��
	EM_GET_BY_TELFAIL_ROLLBACK = 18; // ����ʧ��ϵͳ�ع�
	EM_GET_BY_FAME	= 19;		// �������

	EM_LOST_BY_SEND_MONEY	= 50;	// �ʼ�
	EM_LOST_BY_BUY4NPC 	= 51;	// ��NPC������
	EM_LOST_BY_REPAIR	= 52;	// ����װ��
	EM_LOST_BY_PRODUCE_EQUIP= 53;	// ����װ��
	EM_LOST_BY_PRODUCE_PHYS	= 54;	// ����ҩƷ
	EM_LOST_BY_UPGRADE_EQUIP= 55;	// ����װ��
	EM_LOST_BY_INSERT_RUNE	= 56;	// ��Ƕ����
	EM_LOST_BY_INSERT_JEWEL	= 57;	// ��Ƕ��ʯ
	EM_LOST_BY_OPEN_SLOT2	= 58;	// װ������
	EM_LOST_BY_STUDY_TALENT	= 59;	// ѧϰ�츳
	EM_LOST_BY_EXCHANGE_MONEY=60;	// ����ʧȥ
	EM_LOST_BY_MONEY_RELIFE	= 61;	// ��Ǯ����
	EM_LOST_BY_NPC_TELEPORT = 62;	// NPC����
	EM_LOST_BY_BUY_BACK	= 63;	// �ع���Ʒ
	EM_LOST_BY_BIND_ITEM	= 64;	// ����Ʒ
	EM_LOST_BY_UNBIND_ITEM	= 65;	// �����
	EM_LOST_BY_STUDY_SKILL	= 66;	// ѧϰ����
	EM_LOST_BY_STORE_MONEY	= 67;	// ��ֿ��Ǯ
	EM_LOST_BY_RESUME_BIND	= 68;	// �ָ���
	EM_LOST_BY_REMOVE_JEWEL	= 69;	// ժ����ʯ
	EM_LOST_BY_JUDGE_EQUIP  = 70;	// ����װ��
	EM_LOST_BY_CHANGE_RESIST= 71;	// ת������
	EM_LOST_BY_COMPOSE_JEWEL= 72;	// �ϳɱ�ʯ
	EM_LOST_BY_MULTI_COMPOSE= 73;	// �һ�
	EM_LOST_BY_UP_LIFESKILL = 75;	// ����������������
	EM_LOST_BY_STUDY_COMPOSE= 76;	// ѧϰ�䷽
	EM_LOST_BY_JUDGE_FABAO  = 77;	// ��������
	EM_LOST_BY_GUAJI_BUY    = 78;	// �һ���ҩ
	EM_LOST_BY_POSTAL_FEE	= 79;	// �����ʼ�������
	EM_LOST_BY_BUILD_CORPS  = 80;	// ��������
	EM_LOST_BY_CONTR_CORPS 	= 81;	// ����ž���
	EM_LOST_BY_BUILD_FAMILY	= 82;	// ��������
	EM_LOST_BY_CONTR_FAMILY	= 83;	// ��������
	EM_LOST_BY_STALL	= 84;	// �Ӱ�̯��ʧȥ
	EM_LOST_BY_EQUIPCHANGE	= 85; // װ��ת��
	EM_LOST_BY_ADD_EXTRA		= 86; // ��ӡ
	EM_LOST_BY_WAR		= 87; // ������ս
	EM_LOST_BY_BOURSE	= 88; // Ԫ��������
	EM_LOST_BY_TAX		= 89; // ��˰	
	EM_LOST_BY_STALLFEE = 90; //��̯����������
	EM_LOST_BY_MASTERMONEY	= 91; // ��ʦʧȥ
	EM_LOST_BY_CARVEMONEY	= 92;	// ����ʧȥ		
	EM_LOST_BY_DECOMPOS	= 93;	// �ֽ�װ��/������ʧȥ
	EM_LOST_BY_MWPRINT	= 94;	// ����ӡ�Ǻ�ʧȥ
	EM_LOST_MONEY_BY_QLCOMPOSE	= 95;	// ��������ϳ�ʧȥ
	EM_LOST_BY_BUY4FUNC		= 96;		//���ܸ���
	EM_LOST_BY_FAME			= 97;		// ����ʧȥ
	EM_LOST_BY_SPIRIT_UPGRADE  = 98;   // ����ʧȥ
	EM_LOST_BY_SPIRIT_DOWNGRADE  = 99;   // ����ʧȥ
};

// ��Ʒ ID_S2L_ROLE_OPITEM
message CMessageLogRoleOpItem
{
	optional uint32 RoleID			= 1;	// ���CHARID
	optional uint32 OpTime			= 2;	// ʱ��
	optional uint32 LineID			= 3;	// ��ID
	optional uint64 RepetionID		= 4;	// ����ID
	optional uint32 MapID			= 5;	// ��ͼID
	optional uint32	MetierID		= 6;	// ְҵ
	optional uint32 RoleLevel		= 7;	// �ȼ�
	optional uint32 ItemID			= 8;	// ��Ʒģ��ID
	optional uint32 ItemNum			= 9;	// ��Ʒ����
	optional uint64 ItemGUID		= 10;   // ��Ʒ��GUID
	optional uint32 ItemTotal		= 11;	// ����֮�����Ʒ�������� 
	optional uint32 OpType			= 12;   // ��Ϊ
	optional int32  OpParam1		= 13;   // ������Ϊ����1
	optional int32  OpParam2		= 14;   // ������Ϊ����2
	optional uint64 OpParam3		= 15;   // ������Ϊ����3
};

//���� ID_S2L_ROLE_OPEXP
message CMessageLogRoleOpExp
{
	optional uint32 RoleID			= 1;	// ���CHARID
	optional uint32 OpTime			= 2;	// ʱ��
	optional uint32 LineID			= 3;	// ��ID
	optional uint64 RepetionID		= 4;	// ����ID
	optional uint32 MapID			= 5;	// ��ͼID
	optional uint32	MetierID		= 6;	// ְҵ
	optional uint32 RoleLevel		= 7;	// �ȼ�
	optional EUpgradeType ExpType		= 8;	// ��������
	optional uint32 OpType			= 9;	// ��÷�ʽ
	optional uint64 CurExp			= 10;	// ��ǰֵ
	optional uint32 Team			= 11;	// ��ǰ��������
	optional uint32 DeltaExp 		= 12;	// �ı�ֵ
	optional int32  OpParam1		= 13;   // ������Ϊ����1
	optional int32  OpParam2		= 14;   // ������Ϊ����2
	optional uint64 OpParam3		= 15;   // 64λ������Ϊ����3
};


// BUFFER ID_S2L_ROLE_BUFFER
message CMessageLogRoleBuffer
{
	optional uint32 RoleID			= 1;	// ���CHARID
	optional uint32 OpTime			= 2;	// ʱ��
	optional uint32 LineID			= 3;	// ��ID
	optional uint32 MapID			= 4;	// ��ͼID
	optional uint32 PersistTime		= 5; 	// ����ʱ��
	optional uint32 OpType			= 6;	// ���BUFF�ķ�ʽ
    optional uint32 BuffID			= 7;    // BuffID
	optional int32  OpParam1		= 8;    // ������Ϊ����1
	optional int32  OpParam2		= 9;    // ������Ϊ����2
};



// ��Ǯ ID_S2L_ROLE_OPMONEY
message CMessageLogRoleOpMoney
{
	optional uint32 RoleID			= 1;	// ���CHARID
	optional uint32 OpTime			= 2;	// ʱ��
	optional uint32 LineID			= 3;	// ��ID
	optional uint64 RepetionID		= 4;	// ����ID
	optional uint32 MapID			= 5;	// ��ͼID
	optional uint32	MetierID		= 6;	// ְҵ
	optional uint32 RoleLevel		= 7;	// �ȼ�
	optional uint32 MoneyType 		= 8; 	// ��Ǯ����
	optional uint32 OpType			= 9;	// ��ý�Ǯ�ķ�ʽ
	optional int32  CurMoney		= 10;	// ��ǰ��Ǯ
	optional int32  DeltaMoney 		= 11;	// ��Ǯ�ı���
	optional int32  OpParam1		= 12;   // ������Ϊ����1
	optional int32  OpParam2		= 13;   // ������Ϊ����2
	optional uint64 OpParam3		= 14;   // ������Ϊ����3
};


// ������� ID_S2L_ROLE_KILLED
message CMessageLogRoleBeKilled
{
	optional uint32 RoleID			= 1;	// ���CHARID
	optional uint32 OpTime			= 2;	// ʱ��
	optional uint32 LineID			= 3;	// ��ID
	optional uint64 RepetionID		= 4;	// ����ID
	optional uint32 MapID			= 5;	// ��ͼID
	optional uint32	MetierID		= 6;	// ְҵ
	optional uint32 RoleLevel		= 7;	// �ȼ�
	optional uint32 KillerType 		= 8;	// �Է�����
	optional uint32 KillerID		= 9;	// �Է�ID
	optional uint32 KillerMetier	= 10;	// �Է�ְҵID
	optional uint32 KillerLevel		= 11;	// �Է��ȼ�
};

// ����
enum ETaskAction
{
	EM_TASK_ACCEPT 				= 1;	// ��������
	EM_TASK_END 				= 2;	// ��������
	EM_TASK_CANCEL 				= 3;	// ��������
	EM_TASK_ACTION				= 4;	// �������������У�
	EM_TASK_REFRESH				= 5;    // ����ˢ�½���
	EM_TASK_PUBLISH				= 6;	// ��������
};

// ID_S2L_ROLE_OPTASK
message CMessageLogRoleOpTask
{
	optional uint32 RoleID			= 1;	// ���CHARID
	optional uint32 OpTime			= 2;	// ʱ��
	optional uint32 LineID			= 3;	// ��ID
	optional uint64 RepetionID		= 4;	// ����ID
	optional uint32 MapID			= 5;	// ��ͼID
	optional uint32	MetierID		= 6;	// ְҵ
	optional uint32 RoleLevel		= 7;	// �ȼ�
	optional uint32 TaskID			= 8; 	// ����
	optional ETaskAction OpType		= 9;	// ������ʽ
	optional int32  OpParam1		= 10;   // ������Ϊ����1
	optional int32  OpParam2		= 11;   // ������Ϊ����2
	optional uint64 OpParam3		= 13;   // ������Ϊ����3
};

message PBDropedItem
{
	optional uint32 ItemID			= 1;	// ������Ʒģ��ID
	optional uint32 ItemType		= 2;	// �������Ʒ����
	optional uint32 ItemLevel 		= 3;	// ������Ʒ�ĵȼ�
};

// NPC ���� ID_S2L_ORGE_DROPED
message CMessageLogOrgeDropItem
{
	optional int32	NpcID			= 1;	// NpcID
	optional int32  NpcIndex		= 2;	// Npc�Ĳ���ID
	optional int32  NpcLevel		= 3;	// Npc�ȼ�
	optional uint32 OpTime			= 4;	// ʱ��
	optional uint32 LineID			= 5;	// ��ID
	optional uint64 RepetionID		= 6;	// ����ID
	optional uint32 MapID			= 7;	// ��ͼID
	repeated PBDropedItem DropItem		= 8;	// �������Ʒ
};

// ���ʹ����Ʒ����� 
message CMessageLogUseItemDropItem
{
	optional uint32	CharID			= 1;	// CharID
	optional int32  ItemID			= 2;	// ��ƷID
	optional int32	Param1			= 3;	// ����1
	optional int32	Param2			= 4;	// ����2
	optional uint32 OpTime			= 5;	// ʱ��
	optional uint32 LineID			= 6;	// ��ID
	optional uint64 RepetionID		= 7;	// ����ID
	optional uint32 MapID			= 8;	// ��ͼID
	repeated PBDropedItem DropItem	= 9;	// �������Ʒ
};

// ������Ȼ����
message CMessageLogItemDestroy
{
	optional int32	ItemID			= 1;	// Item ID
	optional int32	Level			= 2;	// �ȼ�	
	optional uint32 OpTime			= 4;	// ʱ��
	optional uint32 LineID			= 5;	// ��ID
	optional uint64 RepetionID		= 6;	// ����ID
	optional uint32 MapID			= 7;	// ��ͼID
	optional uint32 PosX			= 8;	// X
	optional uint32 PosY			= 9;	// Y
};

// ��������ö��
enum  EFamilyAttr
{
	EM_FAMILY_NULL			= 0;	// ��
	EM_FAMILY_MEMBER 		= 1;	// ��Ա��
	EM_FAMILY_MONEY  		= 2;	// ���
	EM_FAMILY_CHANLENGE 	= 3; 	// ��ս��
	EM_FAMILY_BATTLE    	= 4; 	// ������
	EM_FAMILY_CREATION  	= 5;	// ����״̬
	EM_FAMILY_CONTRIBUTION 	= 6;	// ���׶�
	EM_FAMILY_LEVEL 		= 7; 	// �ȼ�
	EM_FAMILY_RANK			= 8;	// ְλ
	EM_FAMILY_GLORY			= 9;	// ����
};

// ��������
enum  ECorpsAttr
{
	EM_CORPS_NULL			= 0;	// ��
	EM_CORPS_MEMBER 		= 1;	// ��Ա��
	EM_CORPS_MONEY  		= 2;	// ���
	EM_CORPS_CHANLENGE		= 3; 	// ��ս��
	EM_CORPS_BATTLE			= 4; 	// ������
	EM_CORPS_CREATION		= 5;	// ����״̬
	EM_CORPS_CONTRIBUTION 	= 6;	// ���׶�
	EM_CORPS_LEVEL 			= 7; 	// �ȼ�
	EM_CORPS_RANK			= 8;	// ְλ	
	EM_CORPS_GLORY			= 9;	// ����
	EM_CORPS_REFINEVALUE	= 10;	// ������
	EM_CORPS_SCORE			= 11;	// ���Ż���
	EM_CORPS_ACTIVITY		= 12;	// ��Ծ��
};

// ��������
enum EOrganAction
{
	EM_ORGAN_MEMBERJOIN			= 1;		// ��Ա����
	EM_ORGAN_MEMBERLEAVE		= 2;		// ��Ա�뿪
	EM_ORGAN_CREATE				= 3;		// ����(����)����
	EM_ORGAN_DISBAND			= 4;		// ����(����)��ɢ
	EM_ORGAN_GETMONEY			= 5;		// ��ȡ����(����)��Ǯ
	EM_ORGAN_CONTRIBUTEMONEY	= 6;		// ���׼���(����)��Ǯ
	EM_ORGAN_BUYITEM			= 7;		// �������(����)��Ʒ(���)
	EM_ORGAN_LEVELUP			= 8;		// ����(����)����
	EM_ORGAN_SETPOST			= 9;		// ����(����)ְλ�趨			
	EM_ORGAN_OPEN_ROOM 			= 10;		// ������(����)
	EM_ORGAN_CLOSE_ROOM 		= 11;		// �ط���(ȡ������)
	EM_ORGAN_SEND_CHALLEGE  	= 12;		// ������ս
	EM_ORGAN_REC_CHALLEGE		= 13;		// ������ս
	EM_ORGAN_BID_				= 14;		// ����
	EM_ORGAN_SUBMIT				= 15;		// ����
	EM_ORGAN_JOIN_BATTLE	  	= 16;		// ��ս 
	EM_ORGAN_GETNPCWELFARE		= 17;		// ��ȡ����(����)npc����
	EM_ORGAN_TASK				= 18;		// ����(����)����
	EM_ORGAN_EXCHANGE			= 19;		// ����(����)�һ�	
	EM_ORGAN_CONFIRM			= 20;		// ȷ��
	EM_ORGAN_FIN				= 21;		// ����
	EM_ORGAN_ABORT				= 22;		// ����	
	EM_ORGAN_REPETION			= 23;		// ���帱��
	EM_ORGAN_BATTLEVICTORY		= 24;		// ������ʤ��
	EM_ORGAN_CHALLENGEACCEPT	= 25;		// ������ս	
	EM_ORGAN_REDSTONE			= 26;		// ��ȡ�����ڵ�
	EM_ORGAN_TAX				= 27;		// ��˰
	EM_ORGAN_USEFUNCITEM		= 28;		// ʹ�ù�������Ʒ
	EM_ORGAN_SUMMONCORPSBOSS	= 29;		// �ٻ�����boss
	EM_ORGAN_CORPSREPETION		= 30;		// ��ɾ��Ÿ���
};

enum EWorldAction
{
	EM_WORLD_ACCUSEBEGIN		= 1;		// ������ʼ
	EM_WORLD_ACCUSEVOTE			= 2;		// ����ͶƱ
	EM_WORLD_ACCUSEEND			= 3;		// ��������
	EM_WORLD_POWERADD			= 4;		// ��������
	EM_WORLD_POWERDEL			= 5;		// ��������
	EM_WORLD_FORCE				= 6;		// ֱ����̨
};

message CMessageLogFamily
{
	optional uint32 FamilyID		= 1;		// ����ID
	optional uint32 OpRoleID		= 2;		// ������ID
	optional uint32 OpTime			= 3;		// ����ʱ��
	optional EOrganAction OpType	= 4;		// ��Ϊ
	optional EFamilyAttr AttrID		= 5;		// ��Ϊ�޸ĵ�����
	optional uint32	Param1			= 6;		// ����1
	optional uint32 Param2			= 7;		// ����2
	optional uint32 Param3			= 8;		// ����3
};

message CMessageLogCorps
{
	optional uint32 CorpsID			= 1;		// ����ID
	optional uint32 OpRoleID		= 2;		// ������ID
	optional uint32 OpTime			= 3;		// ����ʱ��
	optional EOrganAction OpType	= 4;		// ��Ϊ
	optional ECorpsAttr AttrID		= 5;		// ��Ϊ�޸ĵ�����
	optional uint32	Param1			= 6;		// ����1
	optional uint32 Param2			= 7;		// ����2
	optional uint32 Param3			= 8;		// ����3
};

message CMessageLogWorld
{
	optional uint32 WorldID			= 1;		// ��ӪID
	optional uint32 OpTime			= 2;		// ����ʱ��
	optional uint32	OpType			= 3;		// ��Ϊ
	optional uint32	Param1			= 4;		// ����1
	optional uint32 Param2			= 5;		// ����2
	optional uint32 Param3			= 6;		// ����3
};


enum EM_MAILACTION
{ 
	EM_MAIL_SENDMAIL	= 1;		// �����ʼ�
	EM_MAIL_RECEIVEMAIL	= 2;		// ���ʼ�
	EM_MAIL_DELMAIL		= 3;		// ɾ���ʼ�
};


// �ʼ�����־
message CMessageLogMail
{
	optional uint32 RoleID				= 1;	// �ʼ������߽�ɫID
	optional uint32 MailID				= 2;	// �ʼ�ID	
	optional uint32 OpType				= 3;	// ��������
	optional uint32 Optime				= 4;	// ����ʱ��
	optional uint32	MailType			= 5;	// �ʼ�����
	optional string	MailTitle			= 6;	// �ʼ�����
	optional uint32	TotalNum			= 7;	// ��ǰ�ʼ�����
	optional uint32	ItemID1				= 8;	// �ʼ�������Ʒ1��ID		
	optional uint32	ItemNum1			= 9;	// �ʼ�������Ʒ1������
	optional uint32	ItemID2				= 10;	// �ʼ�������Ʒ2��ID		
	optional uint32	ItemNum2			= 11;	// �ʼ�������Ʒ2��ID
	optional uint32	ItemID3				= 12;	// �ʼ�������Ʒ3��ID		
	optional uint32	ItemNum3			= 13;	// �ʼ�������Ʒ3��ID
	optional uint32	ItemID4				= 14;	// �ʼ�������Ʒ4��ID		
	optional uint32	ItemNum4			= 15;	// �ʼ�������Ʒ4��ID
	optional uint32	ItemID5				= 16;	// �ʼ�������Ʒ5��ID		
	optional uint32	ItemNum5			= 17;	// �ʼ�������Ʒ5��ID
	optional uint32	Money				= 18;	// Я���ĸ�����Ǯ
	optional uint32	MoneyNeedCallBack	= 19;	// ��Ҫ�Է�֧���Ľ�Ǯ
	optional uint32	DesRoleID			= 20;	// �ʼ���ص�����һ���Ľ�ɫID
	optional string SrcName				= 21;	// �ʼ������ߵ�����
};


// *************************************************************************** //
// CMessageServerStatInfoNotify
// ������ͳ����Ϣ
// *************************************************************************** //
enum EM_STAT_CATALOG
{
	EM_SERVER_MONEY = 1;	// ���˽�Ǯ
	EM_SERVER_EXP	= 2;	// ���˾���
	EM_SERVER_ITEM	= 3;	// ������Ʒ
	EM_SERVER_EVENT	= 4;	// ������Ϊ
	EM_SERVER_FAMILY= 5;	// �������� 
	EM_SERVER_CORPS	= 6;	// ��������
};

message PBAttribute
{
	optional uint32 ID			= 1;	// ����ID
	optional int64	Value			= 2;	// ����ȡֵ
};

message PBCatalog
{
	optional uint32 ID			= 1;	// ������ID
	repeated PBAttribute Attr		= 2;	// ����
};

message CMessageServerStatInfoNotify
{
	optional uint32 ServerID		= 1;	// ͳ�Ƶ�ServerID
	repeated PBCatalog StatInfo		= 2;	// ͳ����Ϣ
};

message CMessageLogValuableEquip
{
	optional uint32 RoleID		= 1;	// ��ɫID
	repeated PBItemObject	ItemObj	= 2;	// ��Ʒ��Ϣ 
};



// *************************************************************************** //
// CMessageLogChat
// ������ͳ����Ϣ
// *************************************************************************** //
message CMessageLogChat 
{
	optional uint32 RoleID		= 1; // ��ɫID
	optional string ChatMsg		= 2; // ��������
	optional uint32 GateWayID	= 3; // ����ID
	optional uint32 Channel		= 4; // Ƶ��
	optional uint32 OpTime		= 5; // ����ʱ��
	optional uint32 IP			= 6; // ������IP
	optional string RoleName	= 7; // ��ɫ����
};


message CMessageLogRepetion
{
	optional uint64 RepetionKey = 1;
	optional uint32	Type		= 2;
	optional uint32 Index		= 3;
	optional uint32 LineID		= 4;
	optional uint32 Parame1		= 5;
	optional uint32	Parame2		= 6;
	optional uint32 OpTime		= 7;
};

// boss�������ļ�¼
message CMessageLogBossOgreDie
{
	optional uint32	DeathTime	=	1;		// ����ʱ��
	optional uint32	CampID		=	2;		// ��ӪID
	optional uint32	MapID		=	3;		// ��ͼID
	optional uint32	PosX		=	4;		// ����ʱ�ĺ�����
	optional uint32	PosY		=	5;		// ����ʱ��������
	optional uint32	TempID		=	6;		// ����ģ��ID
	optional uint32	KillerID	=	7;		// ���������ҵĽ�ɫID
	optional string	DamageInfo	=	8;		// �˺���Ϣ	
};

// ����ܵ���Ϣ
enum EM_LIFESKILL_ACTIONKIND
{
	EM_LIFESKILLACTION_INITIAL			=	1;		// ѧϰĳ�������
	EM_LIFESKILLACTION_STUDYCOMPOSE		=	2;		// ѧϰ�䷽
	EM_LIFESKILLACTION_LEVELUP			=	3;		// ����ܽ���
	EM_LIFESKILLACTION_FORGETLIFESKILL	=	4;		// ���������
	EM_LIFESKILLACTION_CREATCOMPOSE		=	5;		// �����䷽
	EM_LIFESKILLACTION_USECOMPOSESCROLL	=	6;		// ʹ���䷽����ѧϰ�䷽
};

message CMessageLifeSkill
{
	optional uint32	RoleID				=	1;		// ��ɫID
	optional uint32	OpTime				=	2;		// ����ʱ��
	optional uint32	LifeSkillType		=	3;		// ���������(EM_LIFESKILL)
	optional uint32	LifeSkillKind		=	4;		// ���޻��Ǹ���(EM_LifeSkillKind)			
	optional uint32	LifeSkillLevel		=	5;		// ����ܵĵȼ�
	optional uint32	SpecializedDegree	=	6;		// �����������
	optional uint32	ActionKind			=	7;		// ��������	
	optional uint32	ComposeID			=	8;		// �䷽ID
};

message CMessageExchangeLog
{
	optional uint32 account_id			= 1;
	optional uint32 role_id				= 2;
	optional uint32 optime				= 3;
	optional uint32 money				= 4;
	optional uint32 yb					= 5;
	optional uint32 operate				= 6;
	optional uint64 detail_id_1			= 7;
	optional uint64 detail_id_2			= 8;
	optional uint32 parame1				= 9;
	optional uint32 parame2				= 10;
	optional uint32 parame3				= 11;
	optional uint32 parame4				= 12;	
};

enum EMatrixAction
{
	EM_MATRIX_ADDSLAVE					= 1;		// ʦ����ͽ
	EM_MATRIX_ADDMASTER					= 2;		// ͽ�ܰ�ʦ
	EM_MATRIX_ADDPOINT					= 3;		// ����
	EM_MATRIX_DELSLAVE					= 4;		// ʦ�����
	EM_MATRIX_DELMASTER					= 5;		// ͽ�ܽ��
	EM_MATRIX_MASTERPERCENT				= 6;		// �������
};

message CMessageLogMatrix
{
	optional uint32	slave_id			= 1;
	optional uint32	master_id			= 2;
	optional uint32 optime				= 3;
	optional uint32 operate				= 4;
	optional uint32 parame1				= 5;
	optional uint32 parame2				= 6;
	optional uint32 parame3				= 7;
};

enum ERoleDamage
{
	EM_DAMAGE_NORMAL_MAX				= 8000;
	EM_DAMAGE_DEATH_MAX					= 20000;
	EM_DAMAGE_NORMAL_MIN				= 1000;
	EM_DAMAGE_DEATH_MIN					= 3000;
	EM_MIN_LEVEL						= 70;
};

message CMessageLogRoleDamage
{
	optional uint32	srccharid			= 1;
	optional uint32	descharid			= 2;
	optional uint32	optime				= 3;
	optional uint32	skillid				= 4;
	optional uint32	calcdamage			= 5;
	optional uint32	realdamage			= 6;
	optional uint32	srcpatt				= 7;
	optional uint32	srcmatt				= 8;
	optional uint32	despdef				= 9;
	optional uint32	desmdef				= 10;
	optional uint32	despimu				= 11;
	optional uint32	desmimu				= 12;
	optional uint32	srcdhit				= 13;
	optional uint32	desddef				= 14;
	optional uint32	srctitle			= 15;
	optional uint32 destitle			= 16;
	optional string	srcres				= 17;
	optional string desres				= 18;	
	optional string	srcbuff				= 19;
	optional string desbuff				= 20;
};

// ����������־

enum ERoleRepeScore
{
	EM_SCORE_COMMON_ORGE				= 1;
	EM_SCORE_BOSS_ORGE					= 2;
	EM_SCORE_EXTRAL						= 3;
	EM_SCORE_KILL_PLAYER				= 4;
};

message CMessageLogRoleRepeScore
{
	optional uint32	charid				= 1;
	optional uint32	lineid				= 2;
	optional uint32	optime				= 3;
	optional uint32	mapid				= 4;
	optional uint32	repeid				= 5;
	optional uint32	currentscore		= 6;
	optional uint32	deltascore			= 7;
	optional uint32	scoretype			= 8;
};