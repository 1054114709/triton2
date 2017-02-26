import "ibstore_pb.hxx";
import "property_pb.hxx";
import "countrymessage_pb.hxx";
import "boursemessage_pb.hxx";

// ������ٶ�����/������
option optimize_for = SPEED;


enum EMServerMessageID
{
	// 0x0000 + 0x8000
    ID_INTER_TIMEOUT					= 0x8000;	// �������ڲ��ĳ�ʱ��Ϣ(���ڲ�ʹ��)
    ID_G2L_GATE_INFO_NOTICE				= 0x8001;
    ID_L2G_GATE_INFO_RESPONSE			= 0x8002;
    ID_S2G_SERVER_INFO_NOTICE			= 0x8006;
    ID_G2S_SERVER_INFO_RESPONSE			= 0x8007;
    ID_G2S_CREATE_MAP_NOTICE			= 0x800F;
    ID_S2G_CREATE_MAP_RESPONSE			= 0x8010;
    ID_G2S_SCENE_NOT_OPEN_NOTICE		= 0x8014;
    ID_G2L_UPDATE_VERSION_NOTICE		= 0x8015;
    ID_X2X_ERATING_PROTO_STREAM			= 0x8016;
    ID_L2G_ERATING_STATUS_NOTICE		= 0x8017;
    ID_G2L_GATE_SHUTDOWN_NOTICE			= 0x8018;
	ID_G2L_HEARTBEAT_NOTICE				= 0x8019; // ���ص���½������������
    ID_X2P_REGIST_SERVER_REQUEST		= 0x8020;
    ID_P2X_REGIST_SERVER_RESPONSE		= 0x8021;
    ID_X2P_HEART_BEAT_NOTICE			= 0x8022;
    ID_G2S_COUNTRY_INFO					= 0x8030;
    ID_S2G_GAME_HEART_BEAT_NOTICE		= 0x8031;
    ID_A2G_GAME_PRIVILEGE_NOTICE		= 0x8032;	// ��ȫ�ַ�����ȡ��Ȩ�޵�֪ͨ
	ID_G2S_NOTIFY_SAFE_SHUTDOWN			= 0x8033;	// ��ȫ�رշ�����֪ͨ
	ID_S2G_REGIST_REPETION_INFO			= 0x8034;
	ID_S2G_ACK_SAFE_SHUTDOWN			= 0x8035;	// ��ȫ�رշ�������Ӧ
	ID_L2G_LOGINSVRSTARTUP_NOTICE		= 0x8040;	// Loginserver����֪ͨ

	// 0x0400 + 0x8000
    ID_L2G_PLAYER_ENTER_GATE_NOTICE		= 0x8403;  
    ID_G2L_PLAYER_ENTER_GATE_RESPONSE	= 0x8404;
    ID_G2L_PLAYER_LEAVE_GATE_NOTICE		= 0x8405;
    ID_G2S_PLAYER_ENTER_MAP_NOTICE		= 0x8408;
    ID_S2G_PLAYER_ENTER_MAP_RESPONSE	= 0x8409;
    ID_G2S_PLAYER_LOGIN_COMPLETE_NOTICE	= 0x840A;
    ID_S2G_PLAYER_LEAVE_MAP_NOTICE		= 0x840B;
    ID_G2S_PLAYER_LEAVE_MAP_RESPONSE	= 0x840C;
    ID_S2G_PLAYER_RETURN2GATE_NOTICE	= 0x840D;
    ID_G2S_PLAYER_RETURN2GATE_RESPONSE	= 0x840E;
    ID_S2G_PLAYER_REDIRECT_REQUEST		= 0x8411;
    ID_G2S_PLAYER_REDIRECT_RESPONSE		= 0x8412;
    ID_S2G_PLAYER_ENTER_CONFIRM_NOTICE	= 0x8413;
    ID_G2S_KICKOFF_PLAYER_REQUEST		= 0x8423;
    ID_S2G_KICKOFF_PLAYER_RESPONSE		= 0x8424;
    ID_G2S_REDIRECT_MAP_NOTICE			= 0x8426;
    ID_S2G_REDIRECT_ENTER_MAP_RESPONSE	= 0x8427;
    ID_G2S_REDIRECT_G_ERROR_CODE		= 0x8428;
    ID_S2G_REDIRECT_S_ERROR_CODE		= 0x8429;
    ID_S2G_SERVICE_MAILCOUNT_NOTICE		= 0x8435;

	ID_S2G_ENTITY_GM_MOVE				= 0x8436;	// gm�ƶ�
	ID_G2S_ENTITY_GM_MOVE				= 0x8437;


	ID_S2G_ROLECHANGECAMP_NOTICE		= 0x8439;	// ���ѡ����Ӫ��֪ͨ����
	ID_S2G_NOTIFY_ROLEGAMEINFO2GATE		= 0x8441;	// ����֪ͨ���������Ϸ���ݱ仯	
	ID_G2S_TRACEDPLAYER_NOTIFY			= 0x8442;   // ����֪ͨ������������׷�ٵ�����б�	
	ID_G2S_NOTIFY_CREATE_REPETION		= 0x8443;
	ID_S2G_NOTIFY_CHANGEPASSWORDSTATUS	= 0x8444;	// ��Ұ�ȫ����״̬�ı��֪ͨ	

	ID_S2G_NOTIFY_VIPFLAG				= 0x8445;	// ��һ�Ա��־�ı��֪ͨ
	ID_G2S_NOTIFY_RESETROLEPASSWORD		= 0x8446;	// ����֪ͨ���������������

	ID_S2G_ROLE_MOVE					= 0x8447;
	ID_G2S_ROLE_MOVE					= 0x8448;

	// �����������´���
	ID_G2S_REQUEST_RESAVEPLAYER			= 0x8449;
	ID_S2G_RESPONSE_RESAVEPLAYER		= 0x844A;

	//	......							//0x81FE; // ռλ
	//	......							//0x81FF; // ռλ
	

	// 0x1000 + 0x8000
	// ��������ģ��
	ID_S2G_REQUEST_PLAYERPBULISHTASK	= 0x9001; // ����->���� ��ҷ�������
	ID_G2S_RESPONSE_PBULISHTASKRESULT	= 0x9002; // ����->���� ��ҷ��������Ӧ

	ID_S2G_REQUEST_CHECKPUBLISHBOARD	= 0x9003; // ����->���� ��Ҳ鿴չ������	
	ID_G2S_RESPONSE_CHECKPUBLISHBOARD	= 0x9004; // ����->���� �鿴չ���Ӧ


    // ����ģ�����ϢID 0x1800 + 0x8000
    ID_S2G_PLAYER_ONLINE_FRIEND_REQUEST	= 0x9801;
    ID_G2S_PLAYER_ONLINE_FIREND_RESPONSE= 0x9802;
    ID_S2G_PLAYER_CHANGE_STATUS_NOTICE	= 0x9803;
	ID_S2G_ADDFRIEND_REQUEST			= 0x9804;  
	ID_G2S_ADDFRIEND_RESPONSE			= 0x9805;  
	ID_S2G_GETCHARID_REQUEST			= 0x9806;  
	ID_G2S_GETCHARID_RESPONSE			= 0x9807;  
	ID_S2G_ADDMASTERPOINT_REQUEST		= 0x9808;
	ID_G2S_ADDMASTERPOINT_NOTIFY		= 0x9809;
	ID_S2G_ACQUIREMASTER_NOTIFY			= 0x980A;

    // ���ģ�����ϢID 0x1C00 + 0x8000
    ID_S2G_REQUEST_CREATETEAMATGATE		= 0x9C01;
    ID_S2G_REQUEST_JOINREQUEST			= 0x9C02;
	ID_S2G_REQUEST_REPLYJOINREQUEST		= 0x9C03;
	ID_S2G_REQUEST_JOININVITE			= 0x9C04;
	ID_S2G_REQUEST_REPLYJOININVITE		= 0x9C05;
	ID_S2G_REQUEST_KICKOUTTEAM			= 0x9C06;
	ID_S2G_REQUEST_CHANGEHEADER			= 0x9C07;
	ID_S2G_REQUEST_LEAVETEAM			= 0x9C08;
	ID_S2G_REQUEST_ENDTEAM				= 0x9C09;
	ID_G2S_NOTIFY_ERRORNOTICE			= 0x9C0A;
	ID_G2S_RESPONSE_CREATETEAM			= 0x9C0B;
	ID_G2S_RESPONSE_JOINREQUEST			= 0x9C0C;
	ID_G2S_RESPONSE_JOININVITE			= 0x9C0D;
	ID_G2S_NOTIFY_UPDATETEAM			= 0x9C0E;
	ID_G2S_NOTIFY_SENDLIST				= 0x9C0F;
	ID_G2S_RESPONSE_INVITEREQUEST		= 0x9C10;
	ID_S2G_REQUEST_UPDATETEAMPRO		= 0x9C11;
	ID_G2S_RESPONSE_UPDATETEAMPRO		= 0x9C12;
	ID_S2G_REQUEST_CLAIMRECRUIT			= 0x9C13;
	ID_S2G_REQUEST_QUERYCLAIMRECRUIT	= 0x9C14;
	ID_G2S_RESPONSE_QUERYCLAIMRECRUIT	= 0x9C15;
	ID_G2S_RESPONSE_CLAIMRECRUIT		= 0x9C16;
	ID_S2G_REQUEST_FOLLOW				= 0x9C17;
	ID_G2S_RESPONSE_FOLLOW				= 0x9C18;
	ID_S2G_REQUEST_DELETECLAIMRECRUIT	= 0x9C19;
	ID_G2S_RESPONSE_DELETECLAIMRECRUIT	= 0x9C1A;
	ID_S2G_REQUEST_DISTRIBUTE			= 0x9C1B;
	ID_G2S_RESPONSE_DISTRIBUTE			= 0x9C1C;
	ID_S2G_REQUEST_OBTAINTEAMATGATE		= 0x9C1D;
	ID_S2G_REQUEST_CLEARRECORD			= 0x9C1E;
	
	// �ʼ�ģ�����ϢID 0x2000 + 0x8000
    ID_C2G_REQUEST_GETMAILINFO			= 0xA001;		// ��ȡ����ʼ������Ϣ
    ID_G2S_RESPONSE_GETMAIINFO			= 0xA002;		// ��������ʼ������Ϣ
    ID_G2S_NOTIFY_SENDSYSMAILTOPLAYER   = 0xA003;       // ����ҷ���ϵͳ�ʼ�
    
	// ����ģ�����ϢID 0x2C00 + 0x8000
	ID_S2G_DESTROY_REPETION_MAP			= 0xAC01;
	ID_S2G_BATTLE_TEAM_WAIT				= 0xAC02;
	ID_S2G_BATTLE_WAIT_LEAVE_REQUEST	= 0xAC03;
	ID_G2S_BATTLE_JOIN_NOTICE			= 0xAC04;
	ID_S2G_BATTLE_PLAYER_JOIN			= 0xAC05;
	ID_G2S_BATTLE_WAIT_NOTICE			= 0xAC06;
	ID_G2S_BATTLE_WAIT_LEAVE_RESPONSE	= 0xAC07;
	ID_S2G_BATTLE_CREATE_REQUEST		= 0xAC08;
	ID_G2S_BATTLE_CREATE_RESPONSE		= 0xAC09;
	ID_S2G_CREATE_REPETION_ERR			= 0xAC0A;
	ID_S2G_INTO_REPETION_TEAM			= 0xAC0B;
	ID_S2G_INTO_REPETION_SINGLE			= 0xAC0C;
	ID_G2S_INTO_REPETION_NOTIFY			= 0xAC0D;
	ID_G2S_REPETION_EVENT_CODE			= 0xAC0E;
        ID_S2G_BATTLE_TEAM_FIX_WAIT             = 0xAC0F;
        ID_S2G_BATTLE_SINGLE_FIX_WAIT           = 0xAC10;
        ID_S2G_BATTLE_FIX_WAIT_LEAVE_REQUEST    = 0xAC11;
	ID_S2G_REPETION_BATTLE_WINNER_NOTIFY= 0xAC12;
	ID_S2G_JOIN_ONTIME_OPEN_BATTLE_REQUEST = 0xAC13;
	ID_S2G_BATTLE_CLOSE					= 0xAC14;
	ID_S2G_INTO_CORPSBOSS_REPETION		= 0xAC15;
	ID_S2G_END_CORPSBOSS_REPETION		= 0xAC16;

	// �ģ�����ϢID 0x3000 + 0x8000	
	ID_G2S_TODAYACTIVITYS_LIST_NOTIFY	= 0xB001;
	ID_G2S_ACTIVITY_CHANGE_NOTIFY		= 0xB002;
	ID_G2S_ACTIVITY_EVENT_NOTIFY		= 0xB003;
	
    	// ��ȡҡǮ�����Ϣ
    	ID_S2G_GETCAMPRANKFORYQS_REQUEST    	= 0xB004;    // ��ȡҡǮ����Ӫ����(S->G)
    	ID_G2S_GETCAMPRANKFORYQS_RESPONSE   	= 0xB005;    // ��ȡҡǮ����Ӫ����(G->S)

	ID_S2G_UPDATEYQSGROWING_REQUEST     	= 0xB006;    // �ϱ�ҡǮ���ɳ���(S->G)
    	ID_G2S_UPDATEYQSGROWING_RESPONSE    	= 0xB007;    // �ϱ�ҡǮ���ɳ���(G->S)
    	ID_G2S_SETTLE_NOTICE                	= 0xB008;    // ����֪ͨ
    	ID_G2S_YAOQIANSHUSTART_NOTICE      	= 0xB009;    // ҡǮ�����ʼ֪ͨ

    // ����ģ�����ϢID 0x3400 + 0x8000	����ģ�����Ϣͷ
    ID_S2G_REQUEST_FAMILYMSG				= 0xB401;		
    ID_G2S_RESPONSE_FAMILYMSG				= 0xB402;
	ID_G2S_NOTIFY_FAMILYIDNAME				= 0xB403;
	ID_G2S_NOTIFY_NPCLIST					= 0xB404;
	ID_S2G_NOTIFY_BIDTIMEOUT				= 0xB405;
	ID_S2G_REQUEST_BATTLESTART				= 0xB406;
	ID_G2S_RESPONSE_BATTLESTART				= 0xB407;
	ID_S2G_NOTIFY_BATTLEEND					= 0xB408;
	ID_G2S_NOTIFY_BIDRESTART				= 0xB409;  
	
	ID_S2G_NOTIFY_CHANGEFAMILYCONTRIBUTE	= 0xB40A;			// �ı���Ҽ��幱�׶ȵ�֪ͨ
	ID_S2G_NOTIFY_CHANGEFAMILYGLORY			= 0xB40B;			// �ı������ҫ��֪ͨ
	ID_S2G_NOTIFY_CHANGEFAMILYMONEY			= 0xB40C;			// �ı�����Ǯ��֪ͨ
	
	ID_S2G_NOTIFY_FAMILYAPANDEXPCHANGED		= 0xB40D;			// �����Աap��exp�ı��֪ͨ

	ID_S2G_REQUEST_BUYFAMILYITEM			= 0xB40E;			// ���������Ʒ��������Ϣ
	ID_G2S_RESPONSE_BUYFAMILYITEM			= 0xB40F;			// ����������Ļ�Ӧ��Ϣ	
	ID_G2S_NOTIFY_CLEARFAMILYREPETIONIFO	= 0xB410;			// ������帱������Ϣ
	ID_S2G_REQUEST_FAMILYEXCHANGE			= 0xB411;			// ���м���һ�����Ϣ����
	ID_G2S_RESPONSE_FAMILYEXCHANGE			= 0xB412;			// ���м���һ�����Ϣ��Ӧ
	ID_S2G_NOTIFY_ADDFAMILYEXCHANGEITEM		= 0xB413;			// ���Ӽ���һ���Ʒ����Ϣ֪ͨ
	ID_S2G_NOTIFY_CHANGEFAMILYSTABILITY		= 0xB414;			// �ı���尲���ȵ�֪ͨ

	// ����ģ�����ϢID 0x3800 + 0x8000

	ID_S2G_REQUEST_BIDTIMERSTOP			= 0xB801;	// ���۱���ʱ�����
	ID_G2S_NOTIFY_JOINBATTLE			= 0xB802;	// ��ս֪ͨ
	ID_S2G_REQUEST_BATTLERESULT			= 0xB803;	// ս�����
	ID_S2G_REQUEST_BATTLEFLAG			= 0xB804;
	ID_G2S_RESPONSE_BATTLEFLAG			= 0xB805;
	ID_S2G_REQUEST_STARTCOPRSBATTLE		= 0xB806;

	ID_S2G_NOTIFY_CHANGECORPSCONTRIBUTE	= 0xB807;			// �ı���Ҿ��Ź��׶ȵ�֪ͨ
	ID_S2G_NOTIFY_CHANGECORPSGLORY		= 0xB808;			// �ı������ҫ��֪ͨ
	ID_S2G_NOTIFY_CHANGECORPSMONEY		= 0xB809;			// �ı���Ž�Ǯ��֪ͨ
	
	ID_S2G_NOTIFY_CORPSAPEXPCHANGED		= 0xB80A;			// �������AP��EXP�ı��֪ͨ
	
	ID_S2G_REQUEST_BUYCORPSITEM			= 0xB80B;			// ���������Ʒ����Ϣ����
	ID_G2S_RESPONSE_BUYCORPSITEM		= 0xB80C;			// ���������Ʒ����Ϣ��Ӧ
	
	ID_S2G_REQUEST_CORPSEXCHANGE		=  0xB80D;			// ���о��Ŷһ�����Ϣ����
	ID_G2S_RESPONSE_CORPSEXCHANGE		=  0xB80E;			// ���о��Ŷһ�����Ϣ��Ӧ
	
	ID_S2G_REQUEST_ADDCORPSEXCHANGEITEM	= 0xB80F;			// ���Ӿ��Ŷһ���Ʒ����Ϣ֪ͨ

	ID_S2G_REQUEST_CALLBACK_CORPSMONEY	= 0xB810;			//  �ع�����վ��ؽ�Ǯ

	ID_S2G_REQUEST_BATTLEMAP			= 0xB811;		// ս����ͼ֪ͨ
	ID_S2G_CHANGE_CORPSBOSSTIMES		= 0xB812;			// ��Ӿ���boss����
	ID_S2G_CHANGE_CORPSBOSSREFINEVALUE	= 0xB813;			// �ı���ŵ�boss����ֵ
	ID_S2G_CHANGE_CORPSCOLLECTACTIVE	= 0xB814;			// �ı���Ųɼ���Ծ��

	// ���а�ģ����ϢID 0x3C00 + 0x8000
	ID_S2G_NOTIFY_PERSONALRANKINFO		= 0xBC01;	// ���͸���������Ϣ������
	ID_G2S_REQUEST_PERSONALRANKINFO		= 0xBC02;	// �����͸���������Ϣ������
	ID_G2S_NOTIFY_NEWTOPTEN				= 0xBC03;	// TopTen ֪ͨ�������³ƺ�
	ID_S2G_REQUEST_TOPTEN				= 0xBC04;
	ID_G2S_RESPONSE_TOPTEN				= 0xBC05;
	ID_S2G_RANK_REMOVE					= 0xBC06;

	// ERATING �̳���Ϣ 0x4800 + 0x8000
	ID_G2E_IBEXCHANGE_NOTICE			= 0xC801;
	ID_S2E_IBITEMUSED_NOTICE			= 0xC802;
	ID_S2G_LISTIBITEMS_REQUEST			= 0xC803;	// �̳���Ʒ����
	ID_G2S_LISTIBITEMS_RESPONSE			= 0xC804;	// �̳���Ʒ�б��Ӧ
	ID_S2G_PURCHASEIBITEM_REQUEST		= 0xC805;	// �����̳���Ʒ����
	ID_G2S_PURCHASEIBITEM_RESPONSE		= 0xC806;	// �����̳���Ʒ��Ӧ
	ID_S2G_ROLEIBTRANS_NOTIFY			= 0xC807;	// �������֪ͨ	  	
	
	ID_S2V_SERVERVALIDATE_REQUEST		= 0xC808;	// ��������֤����
	ID_V2S_SERVERVALIDATE_RESPONSE		= 0xC809;	// ��������֤��Ӧ  

	ID_S2G_SYNIBSTORE_REQUEST			= 0xC80A;	// �̳���Ʒ����
	ID_G2S_SYNIBSTORE_RESPONSE			= 0xC80B;	// �̳���Ʒ�б��Ӧ

	ID_S2G_QUERYYUANBAO_REQUEST			= 0xC80C;	// ��ѯԪ�����
	ID_G2S_QUERYYUANBAO_RESPONSE			= 0xC80D;	// ����Ԫ�����
	ID_S2G_DRAWYUANBAO_REQUEST			= 0xC80E;	// ��ȡԪ������
	ID_G2S_DRAWYUANBAO_RESPONSE			= 0xC80F;	// ��ȡԪ����Ӧ
	ID_S2G_LOCKGOODS_REQUEST			= 0xC810;	// ����������Ʒ��������
	ID_G2S_LOCKGOODS_RESPONSE			= 0xC811;	// ����������Ʒ������Ӧ	
	ID_G2S_NOTIFY_IBSTOREPROMOTION			= 0xC812;	// �̳Ƕ�̬��Ϣ֪ͨ
	ID_S2G_SYNFUNCSTORE_REQUEST			= 0xC813;	// ͬ�����ܸ�������
	ID_G2S_SYNFUNCSTORE_RESPONSE		= 0xC814;	// ͬ�����ܸ��ѻ�Ӧ

	// �øС����ģ����ϢID 0x4C00 + 0x8000
	ID_S2G_REQUEST_CHANGESCORE			= 0xCC01;	// �ı����۷�ֵ���� 
	ID_G2S_NOTIFY_JUDGEMODIFY			= 0xCC02;	// ֪ͨ���������۳ɹ�

	// ������Ϣ 0x5400 + 0x8000
	ID_S2G_REQUEST_CHANGEWIZARD			= 0xD401;	// �ı�Ż�ֵ����
	ID_G2S_RESPONSE_CHANGEWIZARD		= 0xD402;	// �ı�Ż�ֵ����

	ID_S2G_REQUEST_CHANGECONSTRUCT		= 0xD403;	// �ı佨�������
	ID_G2S_REQPONSE_CHANGECONSTRUCT		= 0xD404;	// �ı佨��Ȼ�Ӧ

	ID_S2G_REQUEST_CHANGEPOWER			= 0xD405;	// �ı���������
	ID_G2S_RESPONSE_CHANGEPOWER			= 0xD406;	// �ı�������Ӧ

	ID_G2S_NOTIFY_USEFUNCTION			= 0xD407;	// ʹ�ù���֪ͨ
	ID_G2S_NOTIFY_SETOFFICIAL			= 0xD408;	// �趨��Ա֪ͨ
	ID_S2G_NOTIFY_CHANGEFRIEND			= 0xD409;	// �ı��Ѻö�֪ͨ
	ID_S2G_REQUEST_KILLPERSON			= 0xD40A;	// ɱ��֪ͨ
	ID_G2S_RESPONSE_KILLPERSON			= 0xD40B;	// 
	ID_G2S_NOTIFY_SYNCNATION			= 0xD40C;	// ͬ�����ҹ�ϵ

	ID_G2S_NOTIFY_NATIONTITLE			= 0xD40D;	// ���ҳƺ�֪ͨ
	ID_S2G_REQUEST_NATIONTITLELIST		= 0xD40E;	// ��ȡ���ҳƺ��б�
	ID_G2S_RESPONSE_NATIONTITLELIST		= 0xD40F;	// ��ȡ���ҳƺ��б�

	ID_S2G_REQUEST_TRYSUMMON			= 0xD410;	// �����ٻ�����
	ID_G2S_RESPONSE_TRYSUMMON			= 0xD411;	// �����ٻ���Ӧ
	ID_S2G_REQUEST_REALSUMMON			= 0xD412;	// ʵ���ٻ�����
	ID_G2S_NOTIFY_REALSUMMON			= 0xD413;	// ʵ���ٻ�֪ͨ


	ID_S2G_NOTIFY_WARCHANGE				= 0xD414;	// ��ս�ı�֪ͨ
	ID_G2S_NOTIFY_RELIVECHANGE			= 0xD415;	// ��ս�����ı�֪ͨ
	ID_S2G_NOTIFY_OBTAINWARHONOR		= 0xD416;	// ��ս�������֪ͨ
	ID_G2S_NOTIFY_SYNCWARSTATUS			= 0xD417;	// ��սͬ��ս��״̬֪ͨ
	ID_S2G_NOTIFY_WARCONTROL			= 0xD418;	// �޸Ĺ�ս״̬֪ͨ
	ID_S2G_NOTIFY_WARSTONEOVER			= 0xD419;	// �ڵ�����֪ͨ
	ID_G2S_NOTIFY_CREATEWARSTONE		= 0xD41A;	// ������ս�ڵ�֪ͨ

	ID_S2G_NOTIFY_ADDTAX				= 0xD41B;	// ����˰��֪ͨ

	// ��������ϵͳ�����Ϣ
	ID_S2G_ADDHONER_NOTICE				= 0xD41C;	// ��������ֵ��ȡ֪ͨ
	ID_G2S_CAMPWAEKLIST_NOTICE			= 0xD41D;	// ������Ӫ�仯֪ͨ
	ID_S2G_CAMPWEAKLIST_REQUEST			= 0xD41E;	// ��ȡ������Ӫ�б�����
	ID_G2S_CAMPWEAKLIST_RESPONSE		= 0xD41F;	// ������Ӫ�б�ظ�

	ID_S2G_NOTIFY_SPECIALEVENT			= 0xD420;	// �����¼�֪ͨ

	// ������ 0x5800 + 0x8000
	ID_D2G_BOURSELIST_NOTICE            = 0xD801;
	ID_S2G_BOURSELIST_LOAD				= 0xD802;
	ID_G2S_BOURSELIST_LOAD				= 0xD803;
	ID_D2G_BOURSE_TRADE_NOTICE			= 0xD804;
	ID_G2S_BOURSE_TRADE_BUY				= 0xD805;
	ID_G2S_BOURSE_TRADE_SELL			= 0xD806;
	ID_D22_BOURSE_LOG					= 0xD807;

	ID_G2S_NOTIFY_SYNCGTANDLW			= 0xD808;	// ͬ����̽������Ϣ
	
	// ȫ�ַ�������Ϣ 0x8000 + 0x8000


}

enum EMFriendAddRetCode
{
	RET_SUCCESS					= 0x0000;
	RET_INVALID_PLAYER			= 0x0001;	// û���������
	RET_OFFLINE					= 0x0002;	// �Է�û����
}


// ���̷�ʽ
enum EMSaveResult
{
	EM_SAVE2DB   = 0;
	EM_SAVE2FILE = 1;
	EM_NOSAVE    = 2;
}

// �뿪������ԭ��
enum EMLeaveReason
{
    EM_LEAVE_REDIRECT = 0x01;
    EM_LEAVE_RETURN2GATE = 0x02;
    EM_LEAVE_LEAVEGAME = 0x03;
    EM_LEAVE_KICKOUT = 0x04;
	EM_LEAVE_CLOSESOCKET = 0x05;
};

// ********************************************************************** //
// CMessageYQSPhaseChangeNotice ���ط����� -> ����������
// ��ȡ��Ӫ��������
// ********************************************************************** //
message CMessageYQSActivtyStartNotice
{
    optional uint32    id                 = 1;     // ���ʾ
    optional uint32    campid             = 2;     // ��ӪID
    optional uint32    camprankid         = 3;     // ��Ӫ����
    optional uint32    growing            = 4;     // ҡǮ���ɳ���
    optional uint32    level              = 5;     // ҡǮ���ȼ�
    optional uint32    handindawnum       = 6;     // ҡǮ���Ͻ���¶��
    optional uint32    settlephase        = 7;     // ����׶�
};

// ********************************************************************** //
// CMessageYQSPhaseChangeNotice ���������� -> ���ط�����
// ��ȡ��Ӫ��������
// ********************************************************************** //
message CMessageS2GGetCampRankForYQSRequest
{
    optional uint32  playerId           = 1;        // ��ұ��
    optional uint32  param1             = 2;    // ��������

};

// ********************************************************************** //
// CMessageYQSPhaseChangeNotice ���ط����� -> ����������
// ��ȡ��Ӫ����Ӧ��
// ********************************************************************** //

message CampRankForYQSForSever
{
    optional uint32 rank				= 1;    // ����
    optional uint32 campid				= 2;    // ��ӪID
    optional uint32 growinggrade		= 3;    // �ɳ���
    optional uint32 growingphase		= 4;    // �ɳ��׶�
};

message CMessageG2SGetCampRankForYQSResponse
{
    optional uint32  result             = 1;        // ���ؽ����1Ϊ�ɹ�������Ϊʧ��
    optional uint32  playerId        	= 2;        // ��ұ��
    optional uint32  param1             = 3;        // ��������
    repeated  CampRankForYQSForSever	camprankinfo = 4; // ��Ӫ������Ϣ
};

// ********************************************************************** //
// CMessageS2GUpdateYQSGrowingRequest ���������� -> ���ط�����
// �ϱ�ҡǮ���ɳ���
// ********************************************************************** //
message CMessageS2GUpdateYQSGrowingRequest
{
     optional uint32 playerid           = 1;        // �û�ID
     optional uint32 campid             = 2;        // ��ӪID
     optional uint32 growingchangevalue = 3;        // ҡǮ���ɳ���
};

// ********************************************************************** //
// CMessageG2SUpdateYQSGrowingResponse ���ط����� -> ����������
// �ϱ�ҡǮ���ɳ���
// ********************************************************************** //
message CMessageG2SUpdateYQSGrowingResponse
{
     optional uint32 result             = 1;        // ���ؽ����1Ϊ�ɹ�������Ϊʧ��
     optional uint32 playerid           = 2;        // �û�ID
     optional uint32 id                 = 3;        // ���ʾ    
     optional uint32 campid             = 4;        // ��ӪID
     optional uint32 camprankid         = 5;        // ��Ӫ����
     optional uint32 growing            = 6;        // ҡǮ���ɳ���
     optional uint32 level              = 7;        // ҡǮ���ȼ�
     optional uint32 handindawnum       = 8;        // ҡǮ���Ͻ���¶��
     optional uint32 settlephase        = 9;        // ҡǮ������׶�
	 optional uint32 deltagrowing		= 10;		// ���ӵĳɳ���
};

// ********************************************************************** //
// CMessageG2SSettleNotice ���ط����� -> ����������
// �����֪ͨ
// ********************************************************************** //
message CMessageG2SSettleNotice
{
     optional uint32    id                 = 1;     // ���ʾ
     optional uint32    campid             = 2;     // ��ӪID
     optional uint32    camprankid         = 3;     // ��Ӫ����
     optional uint32    growing            = 4;     // ҡǮ���ɳ���
     optional uint32    level              = 5;     // ҡǮ���ȼ�
     optional uint32    handindawnum       = 6;     // ҡǮ���Ͻ���¶��
     optional uint32    settlephase        = 7;     // ����׶�
     optional uint32    settlefinish       = 8;     // �����Ƿ����
     optional uint32    noticeid           = 9;     // ������ϢID
     optional uint32    noticeparam1       = 10;    // ��Ϣ����
     optional uint32    noticeparam2       = 11;    // ��Ϣ����
     optional uint32    noticeparam3       = 12;    // ��Ϣ����
     optional uint32    encourage          = 13;     // �Ƿ񷢷Ž���
};

// �������ڲ���ʱ��Ϣ
message CMessageInternalTimeOut
{
	optional uint32 TimerID		= 1; // ��ʱ��ID
	optional uint32	OwnerID		= 2; // ��ʱ��ӵ����ʵ��ID
	optional uint32	TimerMark	= 3; // ��ʱ����־
	optional uint32 MillSeconds = 4; // ����ʱ�䣬ms
	optional uint32 CalledNum	= 5; // ִ�д���
	repeated uint32 OtherInfo	= 6; // ������Ϣ
}

message CMessageCountryInfo
{
	optional uint32 Length = 1;
	optional bytes  CountryList = 2;
}

message CMessageRedirectGErrorCode
{
	optional uint32 CharID = 1;
	optional int32 ErrorCode = 2;
	optional uint32 LineID = 3;
	optional uint32 MapID = 4;
}

message CMessageRedirectSErrorCode
{
	optional uint32 CharID = 1;
	optional int32 ErrorCode = 2;
	optional uint32 LineID = 3;
	optional uint32 MapID = 4;
}

message CMessagePlayerRedirectEnterMapResponse
{
    optional uint32 CommHandle = 1;  
    optional uint32 CharID = 2; 
    optional uint32 LineID = 3; 
    optional uint32 MapID = 4;  
    optional uint32 PosX = 5;   
    optional uint32 PosY = 6;   
    optional string MapName = 7;
}


// ********************************************************************** //
// CMessageGateInfoNotice ���ط����� -> ��½������
// ********************************************************************** //

message CMessageGateInfoNotice 
{
    optional string Address = 1;
    optional string HostName = 2;
    optional uint32 GateVersion = 3;
    optional uint32 WorldID = 4;
    optional string GateCode = 5;
    optional string GatePasswd = 6;
    optional string GateMac = 7;
    optional uint32 GameID = 8;
}

// ********************************************************************** //
// CMessageGateInfoResponse ��½������ -> ���ط�����������������
// ********************************************************************** //

enum  EMGateInfoResponse
{
    ERROR_SUCCESS = 0;
    ERROR_OUTOFDATE = 1;
}

message CMessageGateInfoResponse 
{
    optional int32 ErrorCode = 1;
}	

// ********************************************************************** //
// CMessageUserLoginNotice ��½������ -> ���ط�����
// ��ҽ��������֪ͨ
// ********************************************************************** //

message CMessagePlayerEnterGateNotice 
{
    optional uint32 CommHandle = 1;
    optional uint32 LoginToken = 2;
    optional uint32 AccountID = 3;
    optional uint32 AdultFlag = 4;      // ���˱�־�� 1����, 0 �ǳ�����
    optional uint32 UserFlag =  5;      // �������Ƶı��
    optional uint32 UserClass = 6;      // vip ����
    optional uint32 UserPoint = 7;      // ��һ���
	optional uint32 WorldPlayerLimit = 8; // ��¼����������������
	optional uint32 UserStatus	 = 9; // �û�״̬ ����GM��
	optional uint32 GameID		= 10; // ��Ҵ���������
	optional int32  cpuid		= 11;	// cpu ����
	optional int32  diskid		= 12;	// disk ����
}

// ********************************************************************** //
// CMessageUserLoginResponse ���ط����� -> ��½������
// ��ҽ����������Ӧ
// ********************************************************************** //

message CMessagePlayerEnterGateResponse
{
    optional uint32 CommHandle = 1;
    optional uint32 AccountID = 2;
    optional uint32 LoginToken = 3;
    optional int32  ErrorCode = 4; 
    optional int32  WorldID = 5;
    optional uint32 OtherClient = 6; 
}

// ********************************************************************** //
// CMessageUserLeaveNotice ���ط����� -> ��½������
// ����뿪������֪ͨ
// ********************************************************************** //

message CMessagePlayerLeaveGateNotice 
{
    optional uint32 AccountID = 1;
    optional uint32 Reason = 2;
}

// ********************************************************************** //
// CMessageServerInfoNotice ���������� -> ���ط�����
// ���������������ر��泡��ģ��
// ********************************************************************** //

message CMessageServerInfoNotice 
{
    optional string Address = 1;		// ������������ַ
    optional string ServerName = 2;		// ��������������
    optional uint32 ServerVersion = 3;		// �����������汾��
    optional uint32 TemplateVersion = 4;        // ģ���ļ��汾��
    optional uint32 TaskVersion = 5;		// �����ļ��汾��
    optional uint32 ServerID = 6;		// ������ID
    optional uint32 LaunchMode = 7;             // ������������ģʽ, LAUNCH_INITIAL LAUNCH_RECOVERY
    optional uint32 PlayerCapacity = 8;         // ��������ҵ�����
}

// ********************************************************************** //
// CMessageServerInfoResponse ���ط����� -> ����������
// ********************************************************************** //

message CMessageServerInfoResponse 
{
    optional uint32 WorldID = 1;        // ����ID��ȫ��Ψһ, һ��Ϊ1XX
	optional uint32 LineID = 2;			// ������LineID
	optional uint32 GameID = 3;			// ��ϷID
}

// ********************************************************************** //
// CMessagePlayerEnterMapNotice�����ط����� -> ����������
// ********************************************************************** //
message CMessagePlayerEnterMapNotice 
{
    optional uint32 LoginToken = 1;		// ��½����
    optional uint32 LineID = 2;			// ��ID
    optional uint32 MapID = 3;			// ��ͼID
    optional uint32 PosX = 4;			// ������
    optional uint32 PosY = 5;			// ������
    optional uint32 CharID = 6;			// ��ҽ�ɫID
    optional uint32 AccountID = 7;		// �˺�ID
    optional uint32 AdultFlag = 8;		// �����˱�־ 1: ������ 0: �ǳ�����
    optional int32	ValidSeconds = 9;	// ������ϵͳʣ�����Ч������
    optional uint32 FamilyID = 10;		// ����ID
    optional string FamilyName = 11;	// ��������
    optional uint32	IsFamilyHeader = 12;// �Ƿ�����峤	1��ʾ���峤 0��ʾ����
    optional uint32 IfHasApplies   = 13;// �Ƿ���������Ϣ 1��ʾ�� 0��ʾû��
    optional uint32 CorpsID		= 14;	// ����ID
    optional string CorpsName	= 15;	// ��������
    optional uint32 IsCorperHeader = 16;// �Ƿ�������� 
    optional uint32 IfHasCorpsApply	= 17;// �Ƿ���������Ϣ 
    optional uint32 IfTracedPlayer = 18; // �Ƿ���Ҫ���ٵ����	
	optional uint64 Key	= 19;			 // ��ͼKey
	optional uint32	FamilyHeaderID	= 20;// ���������ɫID
	optional uint32 CorpsHeaderID	= 21;// ���������ɫID
	optional uint32	FamilyPost		= 22;// ����ְλ
	optional uint32	CorpsPost		= 23;// ����ְλ
	optional uint32 FamilyContribute= 24;// ���幱�׶�
	optional uint32	CorpsContribute = 25;// ���Ź��׶�  
	optional uint32	FamilyMoney		= 26;// �����Ǯ
	optional uint32	CorpsMoney		= 27;// ���Ž�Ǯ	
	optional uint32 UnionID			= 28;
	optional string UnionName		= 29;
	optional uint32 HeadCorpsID		= 30;
	optional uint32 CountryID		= 31;// ����
	optional uint32	OfficialID		= 32;// ��ְ
	optional uint32 KingID			= 33;// ����ID
	optional string	Password		= 34;// ��ȫ����
	optional uint32	ProtectTime		= 35;// ��ȫ�����ĵ���ʱ��	
	optional uint32	PasswordStatus	= 36;// ���뱣����״̬
	optional uint32	ProtectTimeLength = 37;	// ���뱣������ʱ��
	optional uint32	RoleWorldID		= 38;	// ��ҵ�����ID
}

message CMessagePlayerRedirectMapNotice
{
	optional uint32 CommHandle = 1;
	optional uint32 LoginToken = 2;
	optional uint32 CharID = 3;
	optional uint32 AccountID = 4;
	optional uint32	LineID = 5;
	optional uint32 MapID = 6;
	optional uint32 PosX = 7;
	optional uint32 PosY = 8;

    optional string CharName    = 9;
    optional uint32 Gender      = 10;
    optional uint32 Metier      = 11;
    optional uint32 Nationality = 12;
    optional uint32 Facetype    = 13;
    optional uint32 Charlevel   = 14;
    optional uint64 Exp         = 15;
    optional uint32 Lastlogin   = 16;
    optional uint32 DataLength  = 17;
    optional bytes  Data        = 18;
	optional uint32 TeamFlag	= 19;
	optional uint64 Key			= 20;
	optional bytes	EncryptKey	= 21; // �ϸ��������ļ�����Կ�� 16λ

	optional uint32 PetTempID		= 22;
	optional uint32	PetOnlineTime	= 23;
	optional uint32 PetMode			= 24;

	optional PBTeamInfo TeamData	= 25;
	optional PBMsg		TeamMsg		= 26;
	
	optional uint32 FamilyID = 27;		// ����ID
	optional string FamilyName = 28;	// ��������
	optional uint32	IsFamilyHeader = 29;// �Ƿ�����峤	1��ʾ���峤 0��ʾ����
	optional uint32 IfHasApplies   = 30;// �Ƿ���������Ϣ 1��ʾ�� 0��ʾû��
	optional uint32 CorpsID		= 31;	// ����ID
	optional string CorpsName	= 32;	// ��������
	optional uint32 IsCorperHeader = 33;// �Ƿ�������� 
	optional uint32 IfHasCorpsApply	= 34;// �Ƿ���������Ϣ 	

	optional uint32	Camp		= 35;	// ս��:��Ӫ
	optional uint32 IfTracedPlayer = 36;// �Ƿ���Ҫ���ٵ����
	optional uint32	FamilyHeaderID	= 37;// ���������ɫID
	optional uint32 CorpsHeaderID	= 38;// ���������ɫID			

    optional int32	ValidSeconds = 39;	// ������ϵͳʣ�����Ч������
    optional uint32 AdultFlag = 40;		// �����˱�־ 1: ������ 0: �ǳ�����
	optional uint32	FamilyPost	= 41;	// ����ְλ
	optional uint32	CorpsPost	= 42;	// ����ְλ
	optional uint32 FamilyContribute= 43;// ���幱�׶�
	optional uint32	CorpsContribute = 44;// ���Ź��׶�  
	optional uint32	FamilyMoney		= 45;// �����Ǯ
	optional uint32	CorpsMoney		= 46;// ���Ž�Ǯ
	optional uint32 UnionID			= 47;
	optional string UnionName		= 48;
	optional uint32 HeadCorpsID		= 49;
	optional uint32	CountryID		= 50;// ����
	optional uint32	OfficialID		= 51;// ��ְ
	optional uint32 KingID			= 52;// ����ID		  	
	optional string	Password		= 53;// ��ȫ����
	optional uint32	ProtectTime		= 54;// ��ȫ�����ĵ���ʱ��
	optional uint32	PasswordStatus	= 55;// ���뱣��״̬
	optional uint32	ProtectTimeLength = 56;	// ���뱣������ʱ��
	optional uint32 RoleWorldID		= 57; // ��ҵ�����ID
}

// ********************************************************************** //
// CMessagePlayerEnterMapResponse������������ -> ���ط�����
// ********************************************************************** //
message CMessagePlayerEnterMapResponse 
{
    optional uint32 AccountID = 1;     // ͨѶ�˿�ID
    optional uint32 CharID = 2;	// ��ɫID
    optional uint32 LineID = 3;	// ��ID
    optional uint32 MapID = 4;	// ��ͼID
    optional uint32 PosX = 5;	// ������
    optional uint32 PosY = 6;	// ������
    optional int32 ErrorCode = 7;       // 0 �ɹ�, ����ʧ��	
}

// ********************************************************************** //
// CMessageUserLoginCompleteNotice�����ط����� -> ����������
// ********************************************************************** //
message CMessagePlayerLoginCompleteNotice 
{
    optional uint32 AccountID = 1; // �˺�ID
}


// ********************************************************************** //
// CMessagePlayerLeaveMapNotice������������ -> ���ط�����
// ********************************************************************** //

message CMessagePlayerLeaveMapNotice 
{
    optional uint32 CharID = 1; // ��ɫID
    optional uint32 AccountID = 2; // �ʺ�ID
    optional EMLeaveReason Reason = 3; // �뿪ԭ��
    optional uint32 CharLevel = 4; // ��ɫ����
    optional uint32 CharMetier = 5; // ��ɫְҵ
    optional uint32 Money1 = 6; // �ǰ󶨽��
    optional uint32 Money2 = 7; // �󶨽��
    optional uint64 Exp = 8; // ��ǰ����ֵ
    optional uint32 LogoutFlag = 9; // Eratingʹ��
    optional EMSaveResult SaveFlag = 10;  // ���ߴ��̱�־
	optional uint32	GlobalSceneWorldID = 11; // ����0ʱ��ʾ���ʱĿ�������������Id
}

// ********************************************************************** //
// CMessagePlayerLeaveMapResponse�����ط����� -> ����������
// ********************************************************************** //

message CMessagePlayerLeaveMapResponse 
{
    optional uint32 CharID = 1; // ��ɫID
}

// ********************************************************************** //
// CMessagePlayerReturnToGateNotice������������ -> ���ط�����
// ����������֪ͨ·�ɷ�����,��ҽ�Ҫ��������
// ********************************************************************** //

message CMessagePlayerReturn2GateNotice 
{
    optional uint32 AccountID = 1; // �˺�ID
    optional uint32 CharID = 2;	   // ��ɫID

}

// ********************************************************************** //
// CMessagePlayerReturnToGateResponse�����ط����� -> ����������
// ·�ɷ�����֪ͨ����������,�Ѿ�ȷ����ҷ���,���ڵȴ����
// ********************************************************************** //

message CMessagePlayerReturn2GateResponse 
{
    optional uint32 CharID = 1; // ��ɫID
}

// ********************************************************************** //
// CMessageCreateMapNotice�����ط����� -> ����������
// ������ͼ֪ͨ
// ********************************************************************** //

message CMessageCreateMapNotice  
{
    /*optional uint32 LineID = 1;
    optional uint32 MapID = 2;
	optional uint32 Count = 3;
    optional string TplName = 4;*/
	repeated uint32 LineID = 1;
	repeated uint32 MapID = 2;	
	repeated string TplName = 3;
	optional uint32 Count = 4;
	optional uint32	RtnCode	= 5;
	optional string Notice = 6;
}

// ********************************************************************** //
// CMessageCreateMapResponse������������ -> ���ط�����
// ������ͼ֪ͨ
// ********************************************************************** //

message CMessageCreateMapResponse 
{
    repeated uint32 LineID = 1;
    repeated uint32 MapID = 2;
    repeated string TplName = 3;
}
// ********************************************************************** //
// CMessageRegistRepetionInfo ���������� -> ���ط�����
// ������ͼ��Ϣ
// ********************************************************************** //
message BattleLevel
{
	optional uint32	LevelMin		= 1;
	optional uint32	LevelMax		= 2;
};

message PBDate
{
	optional uint32 Year			= 1;
	optional uint32 Month			= 2;
	optional uint32 Day				= 3;
	optional uint32	Week			= 4;
	optional uint32 Hr				= 5;
	optional uint32 Minute			= 6;
	optional uint32 Sec				= 7;
};

message PBDateSpace
{
	optional PBDate Start				= 1;
	optional PBDate finish 			= 2;
};

message CMessageRegistRepetionInfo
{
	optional uint32 LineID = 1;
	repeated uint32 MapID = 2;
	optional uint32 PlayerMax = 3;
	optional uint32 BackMapID = 4;
	optional uint32 BackPosX = 5;
	optional uint32 BackPosY = 6;
	optional uint32 CountMax = 7;
	optional uint32 RepetionID = 8;

	repeated BattleLevel	Level = 9;
	repeated PBDateSpace		Space = 10;
	optional uint32 IsOnTimeOpen = 11;         
	optional uint32 NotLimitTime = 12;
	optional uint32	Relogin	= 13;	// �Ƿ��������
}

message CMessageDestroyRepetionMap
{
	optional uint32 RepetionIndex = 1;
	optional uint64 Key = 2;
	optional uint32 Parame = 3;
}

message CMessageG2SRepetionEventCode
{
	optional int32 RoleID			= 1;
	optional int32 Code				= 2;
	optional int32 RepetionID		= 3;
	optional int32 Parame			= 4;
}

// ********************************************************************** //
// CMessagePlayerRedirectRequest������������ -> ���ط�����
// ����л�����֪ͨ
// ********************************************************************** //
message CMessagePlayerRedirectRequest 
{
    optional uint32 LineID		= 1;
    optional uint32 MapID		= 2;
    optional uint32 PosX		= 3;
    optional uint32 PosY		= 4;
    optional uint32 AccountID	= 5;
    optional uint32 CharID		= 6;

	optional string CharName		= 7;
	optional uint32 Gender			= 8;
	optional uint32 Metier			= 9;
	optional uint32 Nationality		= 10;
	optional uint32 Facetype		= 11;
	optional uint32 Charlevel		= 12;
	optional uint64 Exp				= 13;
	optional uint32 Lastlogin		= 14;
	optional uint32 DataLength		= 16;
	optional bytes  Data			= 17;
	optional uint32 TeamFlag		= 18;
	optional uint32	TeamLevel		= 19;
	optional bytes	EncryptKey		= 20;		// ��Կ , 16λ
	optional PBTeamInfo TeamInfo	= 21;		// ������Ϣ

	optional uint32	PetTempID			= 22;		// ��ǰ�ٻ���ģ��ID(����򸱱�����ʹ��)
	optional uint32	PetOnlineTime		= 23;		// �ٻ�������ʱ��
	optional uint32 PetMode				= 24;		// �ٻ��޹���ģʽ
}

// ********************************************************************** //
// CMessagePlayerRedirectResponse�����ط����� -> ����������
// ����л�������Ӧ
// ********************************************************************** //
message CMessagePlayerRedirectResponse 
{
    optional uint32 CharID = 1;
	optional bool	Redirect = 2;
    optional uint32 LineID = 3;
    optional uint32 MapID = 4;
    optional uint32 PosX = 5;
    optional uint32 PosY = 6;
    optional string Address = 7;
}

// ********************************************************************** //
// CMessagePlayerEnterConfirmNotice������������ -> ���ط�����
// ��ҽ��볡�����ȷ��
// ********************************************************************** //
message CMessagePlayerEnterConfirmNotice 
{
    optional uint32 AccountID = 1;
    optional uint32 CharID = 2;
    optional string CharName = 3;
    optional uint32 LineID = 4;
    optional uint32 MapID = 5;
	// ��ҽ��볡�����أ�Я����ҵ�face��metier, level, sex, nationality
	optional uint32	Face = 6;
	optional uint32	Metier = 7;
	optional uint32	Level = 8;
	optional uint32	Sex = 9;
	optional uint32	Nationality = 10;
    optional bytes  CSKey = 11;         // ��������ͻ���ͨѶʹ�õļ���key
	optional uint32	VipFlag = 12;		// ��Ա��־
}

// ********************************************************************** //
// CMessageSceneNotOpenNotice�����ط����� -> ����������
// ��ҿ糡��ʱ,Ŀ�곡��û���ҵ�
// ********************************************************************** //
message CMessageSceneNotOpenNotice 
{
    optional uint32 CharID = 1;
}

// ********************************************************************** //
// CMessageUpdateGateInfoNotice ���ط����� -> ��½������
// ********************************************************************** //

message CMessageUpdateVersionNotice 
{
    optional uint32 TemplateVersion = 1;// ģ��汾��
    optional uint32 TaskVersion = 2;	// ����汾��
}

// ********************************************************************** //
// CMessageRegistServerResponse ע������ ���������� -> ��ת������
// ********************************************************************** //

message CMessageRegistServerRequest
{
	optional uint32 ServerType	= 1;	// ����������
	optional uint32 ServerID	= 2;	// ������ID
}

// ********************************************************************** //
// CMessageRegistServerResponse ע���Ӧ ��ת������ -> ����������
// ********************************************************************** //
message CMessageRegistServerResponse
{
	optional uint32 ServerType	= 1;	// ����������
	optional uint32 ServerID	= 2;	// ������ID
}

// ********************************************************************** //
// CMessageHeartBeatNotice ��ת������ -> ����������
// ********************************************************************** //
message CMessageHeartBeatNotice 
{
	optional uint32 ServerType	= 1;	// ����������
	optional uint32 ServerID	= 2;	// ������ID
}

// ********************************************************************** //
// CMessageGetPlayerInfoRequest ���������� -> ���ط�����
// ��ȡ������ֺ�״̬
// ********************************************************************** //
message CMessagePlayerOnLineFriendRequest
{
	repeated uint32 CharIDs		= 1;	// ��ɫID��
	optional uint32 Requester	= 2;	// �����ߵ�char id���ش���Ϣ��ʱ��Ҫ������
	optional uint32 Flag		= 3;	// ��ʶ���Ǻ��ѣ���У����ǡ�����
}

message PBSinglePlayerInfo
{
	optional uint32 CharID		= 1;	// ��ɫID
	optional uint32 Status		= 2;	// ״̬
	optional string Name		= 3;	// ����
	optional uint32 Sex			= 4;	// �Ա�
	optional uint32 Face		= 5;	// ͷ��
	optional uint32 Nation		= 6;	// ����
	optional uint32	VipFlag		= 7;	// 0:�ǻ�Ա, 1:��ͨ��Ա
	optional uint32	noExist		= 8;	// �Ƿ����  0:������   1:����
};
// ********************************************************************** //
// CMessageGetPlayerInfoNotice   ���ط����� -> ����������
// ����������������ֺ�״̬����
// ********************************************************************** //
message CMessagePlayerOnLineFriendResponse
{
	repeated PBSinglePlayerInfo Friends = 1; // ������Ϣ
	optional uint32 Requester			= 2;	// �����ߵ�char id���ش���Ϣ��ʱ��Ҫ������
	optional uint32 Flag				= 3;	// ��ʶ����enGateFlags
}

// ********************************************************************** //
// CMessageChangeStatusRequest   ���������� -> ���ط�����
// �޸�״̬����
// ********************************************************************** //
message CMessagePlayerChangeStatusNotice
{
	optional uint32 CharID		= 1;	// ��ɫID
	optional uint32 Status		= 2;	// �µ�״̬
}

// ********************************************************************** //
// CMessageGameHeartBeatNotice ��Ϸ������ -> ���ط�����
// ********************************************************************** //
message CMessageGameHeartBeatNotice 
{
	optional uint32 ServerID		= 1;	// ������ID
	repeated uint32	CharIDs			= 2;	// �������char id	
	repeated uint32	ExternalCharIDs	= 3;	// ���������ڷ����������ID�б�
}

// ********************************************************************** //
// CMessageERatingProto ��Ϸ������ -> ���ط�����
// ********************************************************************** //
message CMessageERatingProtoStream
{
	optional uint32 Length	= 1;	// ������
	optional bytes  buffer	= 2;	// ������
}

// ********************************************************************** //
// CMessageERatingStateNotice ��Ϸ������ -> ���ط�����
// ********************************************************************** //
message CMessageERatingStateNotice
{
        optional uint32 GatewayID = 1;
        optional uint32 binded = 2;
}

// ********************************************************************** //
// CMessageCreateGateTeamRequest ��Ϸ������ -> ���ط�����
// ********************************************************************** //

message CMessageCreateGateTeamRequest
{
	optional uint32	CharID = 1;	// �Խ�������������
};

message CMessageCreateGateTeamResponse
{
	optional uint32	CharID = 1;
	optional uint32	TeamID = 2;
};

message CMessageJoinGateTeamRequest
{
	optional uint32	SrcCharID = 1; // ������
	optional uint32	DesCharID = 2; // �ӳ�������������
	optional uint32	SrcNation = 3;
	optional uint32	DesNaiton = 4;	// �Է�����
};

message CMessageJoinGateTeamResponse
{
	optional uint32	DesCharID = 1;	// ���Ͷ���,�ӳ�
	optional PBTeamItem Item  = 2;	// ��Ա��Ϣ
};

message CMessageRequestJoinReply
{
	optional uint32	SrcCharID = 1; // �ӳ�������ͬ������Ȩ�޵����
	optional uint32	DesCharID = 2; // ������
	optional uint32	RtnCode	  = 3;	// ���ؽ����ͬ�⡢�ܾ�
};

message CMessageJoinGateTeamInvite
{
	optional uint32	SrcCharID = 1; // �����ˡ��ж�������
	optional uint32	DesCharID = 2; // ��������޶������
	optional uint32	SrcNation = 3;
	optional uint32	DesNaiton = 4;	// �Է�����
};

message CMessageJoinTeamInviteResponse
{
	optional uint32 DesCharID = 1;	// ���Ͷ��󣬱�������
	optional uint32 TeamID = 2;
	optional uint32	SrcCharID = 3;
	optional string SrcName = 4;	// ����������
	optional string HeadName = 5;
	optional PBTeamInfo TeamInfo = 6;
};

message CMessageInviteJoinReply
{
	optional uint32	SrcCharID = 1;	// �յ���������
	optional uint32	DesCharID = 2;	// ������
	optional uint32	TeamID = 3;
	optional uint32	RtnCode	  = 4;	// ���ؽ����ͬ�⡢�ܾ�
};

message CMessageInvite2Request
{
	optional PBTeamItem SrcItem = 1;
	optional uint32	DesCharID = 2;
	optional string InviterName = 3;
	optional uint32	InviterCharID = 4;
};

message CMessageKickoutGateTeamRequest
{
	optional uint32	HeadCharID = 1;	// �ӳ�
	optional uint32	MemberCharID = 2; // ���ߵĶ�Ա
};

message CMessageChangeHeaderRequest
{
	optional uint32	OldHeader = 1;
	optional uint32	NewHeader = 2;
};

message CMessageChangeDistributeRequest
{
	optional uint32	CharID	  = 1;
	optional uint32	Mode	  = 2;
};

message CMessageChangeDistributeResponse
{
	optional uint32	CharID	 = 1;
	optional uint32	Mode	 = 2;
};

message CMessageLeaveGateTeamRequest
{
	optional uint32	CharID = 1;
};

message CMessageEndGateTeamRequest
{
	optional uint32	CharID = 1;
};

message CMessageNotifySceneToUpdateTeam
{
	optional uint32	Code	= 1;	// ��������:���ˡ����ˡ���ɢ���顢ת�ƶӳ�
	optional uint32 DesCharID = 2;
	optional uint32	HeadID = 3;
	optional PBTeamItem Item = 4;
};

message CMessageNotifySceneToSendTeamList
{
	optional uint32	DesCharID = 1;	// �б��Ͷ���
	optional PBTeamInfo TeamInfo = 2;
};

message CMessageNotifyErrToScene
{
	optional uint32 DesCharID = 1;
	optional uint32	Code	= 2;
	optional string Param1	= 3;
	optional string Param2	= 4;
};

message CMessageUpdateTeamPropertyRequest
{
	optional uint32 CharID = 1;
	optional PBTeamInfo Info = 2;
};

message CMessageUpdateTeamPropertyResponse
{
	optional uint32 CharID = 1;
	optional PBTeamInfo Info = 2;
};

message CMessageFollowRequest
{
	optional uint32	CharID = 1;
	optional uint32	ActionType = 2;
	optional uint32	ResultCode = 3;
};

message CMessageFollowResponse
{
	optional uint32	CharID = 1;
	optional uint32	HeadID = 2;
	optional uint32	ActionType = 3;
	optional uint32	ResultCode = 4;
};

message CMessageSendClaimRecruitRequest
{
	optional uint32	CharID = 1;
	optional PBMsg	Msg	= 2;
	optional uint32 ActionType = 3;
};

message CMessageSendClaimRecruitResponse
{
	optional uint32	CharID = 1;
	optional PBMsg	Msg = 2;
	optional uint32	ActionType = 3;
};

message CMessageQueryClaimRecruitRequest
{
	optional uint32 CharID = 1;
	optional uint32	ActionType = 2;
	optional uint32	RootCondition = 3;
	optional uint32	SubCondition = 4;
	optional uint32	Level = 5;
	optional uint32	Metier = 6;
	optional uint32	MinLevel = 7;
	optional uint32	MaxLevel = 8;
	optional uint32	Nationality = 9;
	optional uint32	PageIndex = 10;
};

message CMessageQueryClaimRecruitResponse
{
	optional uint32	CharID = 1;
	repeated PBMsg	Msg = 2;
	optional uint32	PageIndex = 3;
	optional uint32 TotalIndex = 4;
	optional uint32	ActionType = 5;
};

message CMessageDeleteClaimRecruitRequest
{
	optional uint32	CharID = 1;
	optional uint32	ActionType = 2;
};

message CMessageDeleteClaimRecruitResponse
{
	optional uint32 CharID = 1;
	optional uint32	ActionType =2;
};

// ********************************************************************** //
// CMessageObtainGateTeamRequest ��Ϸ������ -> ���ط�����
// ********************************************************************** //

message CMessageObtainGateTeamRequest
{
	optional uint32 CharID		= 1;
};

message CMessageClearInvReqRecordRequest
{
	optional uint32	Type		= 1;	// req or inv
	optional uint32 CharID		= 2;
};

//
//// ********************************************************************** //
//// CMessageObtainGateTeamResponse ���ط����� -> ��Ϸ������ 
//// ********************************************************************** //
//
//message CMessageObtainGateTeamResponse
//{
//	optional uint32 HeadCharID	 = 1;
//	optional string Name		 = 2;
//	optional uint32 AccountID	 = 3;
//	optional uint32 Mode		 = 4;
//	optional uint32 Count		 = 5;
//	repeated PBTeamItem Item	 = 6;
//	optional uint32	ItemCharID	 = 7;	// �������ݷ���Ŀ��
//};
//
//// ********************************************************************** //
//// CMessageUpdateGateTeamRequest ��Ϸ������ -> ���ط�����
//// ********************************************************************** //
//
//message CMessageUpdateGateTeamRequest
//{
//	optional uint32 HeadCharID	 = 1;
//	optional string HeadName	 = 2;
//	optional uint32 Type		 = 3;
//	optional uint32 ItemCharID	 = 4;
//	optional string ItemName	 = 5;
//	optional PBTeamItem Item	 = 6;
//};
//
//message CMessageUpdateItemProRequest
//{
//	optional uint32	HeadCharID	= 1;
//	repeated PBTeamItem ItemPro = 2;
//};
//
//// ********************************************************************** //
//// CMessageUpdateGateTeamResponse ���ط����� -> ��Ϸ������ 
//// ********************************************************************** //
//
//message CMessageUpdateGateTeamResponse
//{
//	optional uint32 HeadCharID	  = 1;
//	optional string HeadName	  = 2;
//	optional uint32 ItemCharID	  = 3;
//	optional string ItemName	  = 4;
//	optional uint32 ItemAccID	  = 5;
//	optional uint32 Type		  = 6;
//	optional PBTeamItem Item	  = 7;
//};
//
////**************************************************
//// CMessageProduceCRMsg
//// ����һ�����顢��ļ��Ϣ
////**************************************************
//
//message CMessageProduceCRMsg
//{
//	optional PBMsg	Msg = 1;
//	optional uint32 IsAdd = 2;	// true == ���ӣ� false == ɾ��
//	optional uint32	CharID = 3;	// ����
//};
//
//// ********************************************************************** //
//// CMessageObtainAllCRMsgRequest ��Ϸ������ -> ���ط�����
//// �������������ҵ�������ļ��Ϣ
//// ********************************************************************** //
//message CMessageObtainAllCRMsgRequest
//{
//	optional uint32 CharID		  = 1;	// ��������
//	optional uint32 Type		  = 2;	// ���ͣ�1--������Ϣ��2--��ļ��Ϣ
//	optional uint32 RootStyle	  = 3;	// һ������ �ع�������
//	optional uint32 SubStyle	  = 4;	// ��������
//	optional uint32 Metier		  = 5;	// ְҵ
//	optional uint32 Level		  = 6;	// 
//	optional uint32 MaxLevel	  = 7;
//	optional uint32 MinLevel	  = 8;
//	optional uint32	PageIndex	  = 9;	// ��ҳ��
//	optional uint32	Nationality	  = 10;	// ����
//};
//
//// ********************************************************************** //
//// CMessageObtainCRmsgNotify  ���ط����� -> ��Ϸ������ 
//// ֪ͨ��Ϸ����������ȡ������ļ��Ϣ
//// ********************************************************************** //
//message CMessageObtainCRMsgNotify
//{
//	repeated PBMsg	Msg = 1;
//	optional uint32	MsgSize = 2;	
//	optional uint32 CharID = 3;
//	optional uint32 Type = 4;
//	optional uint32 PageIndex = 5;
//	optional uint32 TotalPage = 6;
//};

message PBMsg
{
	optional uint32		Type = 1;		// ���� == TEAM_ASKFOR����ļ == TEAM_CONSCRIBE
	optional uint32		CharID = 2;
	optional string		Name = 3;
	optional uint32		Metier = 4;
	optional uint32		Level = 5;
	optional uint32		MaxLevel = 6;
	optional uint32		MinLevel = 7;
	optional string		Content = 8;
	optional uint32		Count = 9;
	optional uint32		RootStyle = 10;  // һ������
	optional uint32		SubStyle = 11;	 // ��������
	optional uint32		Nationality = 12;	// ���� 
};

// ********************************************************************** //
// �����Ա��Ϣ 
// ********************************************************************** //
message PBTeamItem
{
	optional uint32			CharID		= 1;
	optional string			Name		= 2;
	optional uint32			AccountID	= 3;
	optional uint32			Type		= 4;
	optional uint32			Face		= 5;
	optional uint32			Metier		= 6;
	optional uint32			Level		= 7;
	optional uint32			Sex			= 8;
	optional uint32			HP			= 9;
	optional uint32			MP			= 10;
	optional uint32			AP			= 11;
	optional uint32			PosX		= 12;	
	optional uint32			PosY		= 13;	
	optional uint32			LineID		= 14;	
	optional uint32			MapID		= 15;
	optional uint32			Status		= 16;
	optional uint32			Nationality	= 17;
	optional PBBuffList		BuffList	= 18;
	optional uint32			RepetionMapIndex = 19;
	optional uint32			Order		= 20; // �ڶ����е����
};



message PBTeamInfo
{
	optional uint32 HeaderCharID		= 1;
	optional uint32 DistributeMode		= 2;
	optional string HeadName			= 3;
	optional uint32	Count				= 4;
	optional uint32	TeamID				= 5;
	repeated PBTeamItem Members			= 6;
};



//message PBMemberPro
//{
//	optional uint32			CharID		= 1;
//	optional uint32			HP			= 2;
//	optional uint32			MP			= 3;
//	optional uint32			PosX		= 4;	
//	optional uint32			PosY		= 5;	
//	optional uint32			LineID		= 6;	
//	optional uint32			MapID		= 7;
//	optional uint32			Status		= 8;
//};


// ********************************************************************** //
// CMessageGateShutDownNotice ���ط����� -> ��¼������ 
// ֪ͨ���ط�����ֹͣ
// ********************************************************************** //
message CMessageGateShutDownNotice
{
        optional uint32 WorldID = 1;
};

// ********************************************************************** //
// CMessageKickOffPlayerRequest���ط����� -> ��Ϸ������
// �ߵ��������
// ********************************************************************** //
message CMessageKickOffPlayerRequest
{
    optional uint32 AccountID	= 1;
    optional uint32 CharID		= 2;
    optional int32  Reason		= 3;
    optional uint32 AnotherIP	= 4; 	//only for relogin reason.
	optional uint32	RoleWorldID = 5;	// ���������������ID
};

// ********************************************************************** //
// CMessageKickOffPlayerResponse  ��Ϸ������ -> ���ط�����
// �ߵ���������Ӧ
// ********************************************************************** //
message CMessageKickOffPlayerResponse
{
    optional uint32 AccountID = 1;
    optional uint32 CharID = 2;
    optional int32 Result = 3;  // 0 �ɹ�, ����ʧ��
	optional uint32 RoleWorldID = 4; // ���������������ID
};

// ********************************************************************** //
// CMessageGetPlayerMailiInfo  ��Ϸ������ -> ���ط�����
// ��ȡ����ʼ������Ϣ
// ********************************************************************** //
message CMessageGetPlayerMailiInfoRequest
{
	optional int32  CharID		= 1;		 // �ĸ���ҵ���Ϣ
	optional string RoleName	= 2;		 // ����ѯ��rolenames 	
	optional uint32 RoleID		= 3;		 // �������ҽ�ɫid	
	optional int32  QueryWay	= 4;		 // ��ѯ��ʽ��1.ʹ��CharID 2.ʹ��RoleName
	optional uint32	QueryType	= 5;		 // ��ѯ����1�����ʼ�ʱ��ѯ2.����ϵͳ�Ĳ�ѯ
	repeated uint32	QueryData	= 6;		 // ��ѯ��Ҫ���ص�����
};

// ********************************************************************** //
// CMessageGetPlayerMailiInfo  ��Ϸ������ -> ���ط�����
// ��ȡ����ʼ������Ϣ
// ********************************************************************** //
message CMessageGetPlayerMailInfoResponse
{
	optional int32  CharID			= 1;   // ԭ��Ϣ�е�entityID
	optional int32  ErrorCode		= 2;   // 1 ��Ҵ���, 2 ��Ҳ�����
	optional uint32 RoleID			= 3;   // ��ҽ�ɫID
	optional string RoleName		= 4;   // ��ҽ�ɫ��
	optional int32  RoleOfCountry	= 5;   // ��ҹ���
	optional int32  RoleInCountry	= 6;   // ����������ڵĹ��� 
	optional int32  RoleOnline		= 7;   // ����Ƿ�����
	optional int32  RoleMailCount	= 8;   // ����ʼ�����
	optional uint32	QueryType		= 9;   // ��ѯ����1�����ʼ�ʱ��ѯ2.����ϵͳ�Ĳ�ѯ
	repeated uint32	QueryData		= 10;  // ��ѯ��Ҫ���ص�����
};
// ********************************************************************** //
// CMessageGetPlayerMailiInfo  ��Ϸ������ -> ���ط�����
// ��ȡ����ʼ������Ϣ
// ********************************************************************** //
message CMessageChangeMailCountNotify
{
	optional int32  CharID		= 1;		// ���id
	optional string CharName	= 2;		// �������
	optional int32  QueryWay	= 3;		// ������ʽ��1.�ý�ɫID 2. �ý�ɫ��
	optional int32  NumChanged	= 4;		// �仯������
};	

message CMessageUserIbExchangeNotice
{
    optional uint64 PurchaseID = 1;
    optional uint32 AccountID = 2;
    optional uint32 RoleID = 3;
    optional uint32 GenderID = 4;
    optional uint32 MetierID = 5;
    optional uint32 Level = 6;
    optional uint32 RatingID = 7;
    optional string IBCode = 8;
    optional uint32 PackageFlag = 9;
    optional uint32 Count = 10;
    optional int32 PayTime = 11;
    optional uint32 UserIP = 12;
    optional uint32 SubjectID = 13;
    optional uint32 AuditFlag = 14;
    optional int32 Price = 15;
    optional int32 DiscountPrice = 16;
};

message CMessageUserUseIbItemNotice
{
    optional uint32 AccountID = 1;
    optional uint32 RoleID = 2;
    optional uint64 PurchaseID = 3;
    optional uint32 GenderID = 4;
    optional uint32 MetierID = 5;
    optional uint32 Level = 6;
};

message CMessageAddFriendRequest
{
	optional fixed32 SrcID    = 1;
	optional fixed32 DesID    = 2;
	optional uint32  SrcLevel = 3;
};

message CMessageAddFriendResponse
{
	optional uint32 SendBack	  = 1;	// �ǲ��Ƿ�����Ϣ
	optional uint32 RetCode		  = 2;	// ״̬��

	optional uint32         SrcCharID		= 3;	// �����ߵ�ID����Ҫ�ͻ��˴洢���ID
	optional uint32			SrcMetier		= 4;	// �����ߵ�ְҵID��Ҳ������ID
	optional uint32			SrcLevel		= 5;	// �����ߵĵȼ�
	optional uint32			SrcSex			= 6;	// �����ߵ��Ա�
	optional uint32			SrcHead			= 7;	// �����ߵ�ͷ��ID
	optional string			SrcName			= 8;	// �����ߵ�����
	optional uint32         DesCharID		= 9;	// �������ߵ�ID
	optional string			DesName			= 10;	// �������ߵ�����
};

// �������ֲ�char id
message CMessageGetCharIDRequest
{
	optional uint32 TypeID			= 1;
	optional string Name			= 2;
	optional fixed32 SrcEntityID	= 3;
};

message CMessageGetCharIDResponse
{
	optional uint32  TypeID			= 1;
	optional fixed32 CharID			= 2;
	optional fixed32 SrcEntityID	= 3;

	// ��չ ���Դ����������� ����type�ж� 
	optional string  Name			= 4;
	optional uint32  Head			= 5;
	optional uint32  Sex			= 6;

};

message CMessageRoleChangeCampNotice
{
    optional int32 RoleID = 1; 
    optional int32 Camp = 2;
};

message CMessageLoginSvrStartUpNotice
{
    optional int32 Status = 1;  //login�ϸ���server��״̬����λ������, 0 λ: eRating״̬ 1 λ: gmServer״̬
};

message CMessageGate2LoginHeartBeatNotice
{
	optional uint32 PlayerAtGate = 1; //  �����ϵ������
};

// ********************************************************************** //
// CMessagePersonalRankInfoNotify  ��Ϸ������ -> ���ط�����
// ���͸������а���Ϣ
// ********************************************************************** //
message PBPersonalRankInfo
{
	optional uint32 CharID			= 1; // ��ɫID
	optional string CharName		= 2; // ��ɫ��
	optional uint32 Level			= 3; // �ȼ�
	optional uint32 Money			= 4; // �ǰ󶨽�
	optional uint32 BoundedMoney	= 5; // �󶨽�
	optional uint32 KillEnemyNumIn	= 6; // ����ɱ����(����)
	optional uint32 KillEnemyNumOut	= 7; // ����ɱ����(����)
	optional uint32 Honor			= 8; // ��ѫ
	optional uint32 Comprehensive	= 9; // �ۺ�ʵ��
	optional uint32 DieNum			= 10; // ��������
	optional uint32 CompletedTasks	= 11; // ���������	
	optional uint32 Country			= 12; // ����
	optional uint32 Metier			= 13; // ְҵ
	optional uint32 Title			= 14; // �ƺ�
	optional uint32 OnLineTime		= 15; // ����ʱ��
	optional uint32 PantaoMark		= 16; // ��Ҹ�������
	optional uint32 LonggongMark	= 17; // ������������
	optional uint64 Exp				= 18; // ��Ҿ��� ���ڵȼ����и���
	optional uint32 OriginReliveTimes	= 19;	// ԭ�ظ������
	optional uint32 KillSameNationNum	= 20;   // ɱ����Ӫ����
	optional uint32 KillOgreNum			= 21;	// ɱ����
	optional uint32 UpFailNum			= 22;	// ����ʧ�ܴ���
	optional uint32 TodayKillEnemyNumIn	= 23; // ���չ���ɱ����(����)
	optional uint32 TodayKillEnemyNumOut= 24; // ���չ���ɱ����(����)
	optional uint32 TodayHonor			= 25; // ��������
	optional uint32 Dayanta				= 26; // ������
	optional uint32 Lianhuadong			= 27; // ������
	optional uint32 Huangfengdong		= 28; // �Ʒ䶴
	optional uint32 AchivePoint			= 29; // �ɾ͵�
	optional uint32 CharmValue			= 30; // ����ֵ
	optional uint32 FlyDungMark			= 31; // ���и�������
	optional uint32 Zhangong			= 32; // ս�������������棩
	optional uint32 Zhiguo				= 33; // �ι������ڲŻ����棩
	optional uint32 Tongshuai			= 34; // ͳ�������ڲŻ����棩
	optional uint32 Wisall				= 35; // �Ż���ֵ���ڲŻ����棩
	optional uint32 YunXiao				= 36; // ��������������
	optional uint32 WeekIncCharm		= 37; // �����ۼ�����ֵ
	optional uint32 Shide				= 38; // ʦ��
	optional uint32 XianYuanMark		= 39; // ��Ե
	optional uint32 Chushitu			= 40; // ��ʦͽ��������
	optional uint32 YunxiaoLevel		= 41; // ��������������
	optional uint32 WudidongMark		= 42; // �޵׶�����
    optional uint32 DaLuanDou		    = 43; // ���Ҷ���ǰ����
	optional uint32 DaLuanDouTotal		= 44; // ���Ҷ��ܻ���
	optional uint32 GlobalWar			= 45; // ���ս����
	optional uint32 SpiritScore			= 46; // ��������
};		


message CMessagePersonalRankInfoNotify
{
	repeated PBPersonalRankInfo PersonalRanks = 1; // �����������а���Ϣ
	optional uint32 Flag = 2; // �����1 ��ʾ����������Ҫ��
	optional uint32 RType = 3; // ˢ������ �ǰ�Сʱ����ÿ��
	optional uint32 IsOver = 4; // �Ƿ��ѽ���(�ְ�����)
};

message PBRankTopTen
{
	optional uint32	RankType = 1;
	repeated uint32	CharList = 2;
};

message CMessageRankRemove
{
	optional string CharName	= 1;
	optional uint32 RankType	= 2;
	optional uint32 Refresh		= 3; // 1. ��־�Ƿ�������ˢ�����а��������а����û�е�ʱ���ֶ�ˢ�³���
};

// �����ʳ���Ҫ��ҵ���Ϣ
message CMessagePersonalRankInfoRequest
{
	repeated PBRankTopTen TopTenList = 1;
	optional uint32		  RType = 2; // ˢ������ �ǰ�Сʱ����ÿ��
};

message CMessageNewRankTopTenNotify
{
	repeated PBRankTopTen TopTenList = 1;
};

// ********************************************************************** //
// CMessageRoleGameInfoReportToGateNotify  ��Ϸ������ -> ���ط�����
// ���͸�����Ϸ��Ϣ������
// ********************************************************************** //
message CMessageRoleGameInfoReportToGateNotify
{
	optional uint32 CharID		= 1; // ��ɫID
	optional uint32 Level		= 2; // �ȼ�
	optional uint32 MapID		= 3; // ��ͼID
	optional uint32 LineID		= 4; // ��ID
	optional uint32 Metier		= 5; // ְҵ
	optional uint32 Country		= 6; // ����
	repeated uint32	MasterID	= 7; // ǰ��ID
	optional uint32 PKValue		= 8;
};

// ********************************************************************** //
// CMessageBattleTeamWait  ��Ϸ������ -> ���ط�����
// �������ս���ȴ��б�
// ********************************************************************** //
message CMessageBattleTeamWait
{
	optional uint32 CharID		= 1; // ��ɫID
	optional uint32 Level		= 2; // �ȼ�
	optional uint32 BattleID	= 3; // ����ID
	optional uint32 MapID		= 4;
};

// ********************************************************************** //
// CMessageBattleWaitLeave  ��Ϸ������ -> ���ط�����
// �ӵȴ��б����뿪
// ********************************************************************** //
message CMessageBattleWaitLeaveRequest
{
	optional uint32 CharID		= 1; // ��ɫID
	optional uint32 BattleID	= 2; // ����ID
	optional uint32 MapID		= 3;
};


// ********************************************************************** //
// CMessageBattleJoinNotice  ���ط����� -> ��Ϸ������
// ��ҿ��Խ���ս��
// ********************************************************************** //
message CMessageBattleJoinNotice
{
	optional uint32 CharID		= 1; // ��ɫID
	optional uint32 BattleID	= 2; // ����ID
	optional uint32	MapID		= 3;
	optional uint32 Type		= 4;
	optional uint32 BattleTime	= 5; // ս����ʼʱ��
	optional uint32 Key			= 6; //key
	optional uint32	IntoLastRepetion=7;	// �Ƿ񸱱��ؽ���
};

// ********************************************************************** //
// CMessageBattlePlayerJoin  ��Ϸ������ -> ���ط�����
// ��ҽ���ս��
// ********************************************************************** //
message CMessageBattlePlayerJoin
{
	optional uint32 CharID		 = 1; // ��ɫID
	optional uint32 BattleID	= 2; // ����ID
	optional uint64 Key			= 3; // key
	optional uint32 CampID		= 4; // ��Ӫ
	optional uint32 MapID		= 5;
};

// ********************************************************************** //
// CMessageBattleWaitNotice  ���ط����� -> ��Ϸ������
// ��ҿ��Խ���ս���ȴ�����
// ********************************************************************** //
message CMessageBattleWaitNotice
{
	optional uint32 CharID		= 1; // ��ɫID
	optional uint32 BattleID	= 2; // ����ID
	optional uint32 MapID		= 3;
};	 



// ********************************************************************** //
// CMessageServerValidateRequest  ��¼������ -> ��֤������
// ���з�������֤������
// ********************************************************************** //
message CMessageServerValidateRequest
{
	optional string MacAddr	= 1;	//		Mac��ַ
	optional string IPAddr	= 2;	//		IP��ַ
};

// ********************************************************************** //
// CMessageBattleWaitLeaveResponse  ���ط����� -> ��Ϸ������
// ��ҿ��Խ���ս���ȴ�����
// ********************************************************************** //
message CMessageBattleWaitLeaveResponse
{
	optional uint32 CharID		= 1; // ��ɫID
	optional uint32 BattleID	= 2; // ����ID 
	optional uint32 MapID		= 3;
};


// ********************************************************************** //
// CMessageServerValidateResponse  ��֤������->��¼������
// ���з�������֤�Ļ�Ӧ
// ********************************************************************** //
message CMessageServerValidateResponse
{
	optional uint32 CheckResult	= 1;
};


// ********************************************************************** //
// CMessageNotifyTracedPlayer  ���ط�����->����������
// ֪ͨ��Ҫ��׷�ٵ����
// ********************************************************************** //
message CTracedPlayerInfo
{
	optional uint32 AccountID	= 1;
	repeated uint32 RoleID		= 2;
};

message CMessageNotifyTracedPlayer
{ 
	repeated CTracedPlayerInfo PlayerList = 1;	
};

// ********************************************************************** //
// CMessageBattleCreateRequest  sceneserver->gateserver
// ����BattleID
// ********************************************************************** //
message CMessageBattleCreateRequest
{
	optional uint32	BattleID		= 1;
	optional uint32 Level			= 2;
	optional uint32 MapID			= 3;
}
// ********************************************************************** //
// CMessageBattleCreateResponse  gateserver->sceneserver
// ����BattleID
// ********************************************************************** //
message CMessageBattleCreateResponse
{
	optional uint32 BattleID		= 1;
	optional uint64 Key				= 2;
	optional uint32 MapID			= 3;
}


// ֪ͨ����������ID���ֶ�Ӧ��ϵ
message CMessageFamilyIDNameNotify
{
	repeated uint32 FamilyID	= 1;
	repeated string FamilyName	= 2;
};

message PBCorpsNpc
{
	optional uint32	NpcID = 1;
	optional uint32	CorpsID = 2;
	optional string	CorpsName = 3;
	optional uint32	Type	= 4;	// add \ del
};

// ֪ͨ����������NPC�����Ӧ��ϵ
message CMessageNpcListNotify
{
	repeated uint32 NpcID		= 1;
	repeated uint32 FamilyID	= 2;
	optional uint32	Type		= 3; // 0:family; 1:corps
	repeated PBCorpsNpc CorpsNpc = 4;
};

// ����������֪ͨ���۽�ֹʱ�䵽
message CMessageBidTimeOutNotify
{
	optional uint32 NpcID		= 1;
	optional uint32 First		= 2;
};

// ����������֪ͨ����ս��
message CMessageBattleStartRequest
{
	optional uint32 NpcID		= 1;
};

// �ظ��������������۽�ֹʱ�䵽
message CMessageBattleStartResponse
{
	optional uint32 NpcID		= 1;
	repeated uint32 CharID		= 2;
	repeated string CharName	= 3;
	repeated uint32 Money		= 4;
};

// ����������֪ͨ����ս���
message CMessageBattleEndNotify
{
	optional uint64	Key				= 1;
	optional uint32 WinSide			= 2;
};

// ֪ͨ�����������������¿�ʼ
message CMessageBidRestartNotify
{
	optional uint32 NpcID		= 1;
};

message CMessageObtainTopTenRequest
{
	optional uint32	CharID = 1;
};

message PBRankTitle
{
	optional uint32	Index = 1;
	optional uint32	RankType = 2;
};

message CMessageObtainTopTenResponse
{
	optional uint32 CharID = 1;
	repeated PBRankTitle RankTitle = 2;
};

message CMessageCorpsBidTimerStopRequest
{
	optional uint32	NpcID = 1;
	optional uint32 BattleId = 2;
};

message CMessageCorpsJoinBattleNotice
{
	optional uint32	CharID = 1;
	optional uint32	NpcID = 2;
};

message CMessageNotifyBattleResult2Gate
{
	optional uint32	BattleID = 1;	// ս��ID
	optional uint32	WinCamp = 2;
	optional uint64	BattleKey = 3;
};

message CMessageCorpsBattleFlagRequest
{
	optional uint32 CharID = 1;
	optional uint32	CorpsID = 2;	// ֪ͨ����ľ���ID
	optional uint32 CampID = 3;		// �����������ӪID
	optional uint32	BattleID = 4;
	optional uint32	IsAll = 5;
	optional uint64 BattleKey = 6;
};

message CMessageCorpsBattleFlagResponse
{
	optional uint32	CharID = 1;
	optional string CorpsName = 2;
	optional uint32	BattleID = 3;
	optional uint32 CampID = 4;
	optional uint32	IsAll = 5;
};

message CMessageCreateRepetionNotify
{
	optional uint32 RepetionIndex = 1;
	optional uint64 Key = 2;
	optional uint32 Parame1 = 3;
	optional uint32 Parame2 = 4;
	optional uint32 LineID = 5;
	optional uint32	Creator = 6;
	optional uint32 RemoveItem = 7;
};

message CMessageCreateRepetionErr
{
	optional uint32 RepetionIndex = 1;
	optional uint64 Key = 2;
	optional uint32 ErrCode = 3;
};

message CMessageTeamIntoRepetion
{
	optional uint32 MapID	= 1;
	optional uint32 CharID	= 2;
	optional uint32 PosX	= 3;
	optional uint32 PosY	= 4;
	optional uint32 Parame1 = 5;
	optional uint32 Parame2 = 6;
	optional uint32 Level	= 7;
	optional uint32 RemoveItem = 8;
};

message CMessageSingleIntoRepetion
{
	optional uint32 MapID	= 1;
	optional uint32 CharID	= 2;
	optional uint32 PosX	= 3;
	optional uint32 PosY	= 4;
	optional uint32 Parame1 = 5;
	optional uint32 Parame2 = 6;
	optional uint32 Level	= 7;
	optional uint32 RemoveItem = 8;
};

message CMessageCorpsStartBattleRequest
{
	optional uint32	NpcID = 1;
	optional uint32	BattleID = 2;
};

message CMessageIntoRepetionNotify
{
	optional uint32 LineID	= 1;
	optional uint32 MapID	= 2;
	optional uint64 Key		= 3;
	optional uint32 PosX	= 4;
	optional uint32 PosY	= 5;
	optional uint32 CharID	= 6;
	optional uint32 RepetionIndex = 7;
};



// *************************************************************************** //
// CMessageChangeFamilyContributeNotify
// �ı���Ҽ��幱�׶ȵ�֪ͨ
// *************************************************************************** //
message CMessageChangeFamilyContributeNotify
{		
	optional uint32				RoleID			=	1;		// ��ҽ�ɫID
	optional uint32				Contribute		=	2;		// ���׶�	
	optional uint32				ChangeType		=	3;		// 0��ʾ����1��ʾ����
};

// *************************************************************************** //
// CMessageChangeFamilyGloryNotify
// �ı������ҫ��֪ͨ
// *************************************************************************** //
message CMessageChangeFamilyGloryNotify
{															
	optional uint32				FamilyID		=	1;		// ����ID
	optional uint32				Glory			=	2;		// ������ҫֵ
	optional uint32				IfReduced		=	3;		// �Ƿ����	
	optional uint32				RoleID			=	4;		// ��ɫID
	optional uint32				Reason			=	5;		// ������ҫ�ı��ԭ��	
	optional string				RoleName		=	6;		// ��ɫ����
};

// *************************************************************************** //
// CMessageChangeFamilyMoneyNotify
// �ı�����Ǯ��֪ͨ
// *************************************************************************** //
message CMessageChangeFamilyMoneyNotify
{			
	optional uint32				Money		=	1;		// ��Ǯ
	optional uint32				IfPayout	=	2;		// �Ƿ����
	optional uint32				FamilyID	=	3;		// ����ID
	optional uint32				RoleID		=	4;		// ��ɫID
	optional uint32				Reason		=	5;		// �ı��Ǯ��ԭ��
	optional string				RoleName	=	6;		// ��ɫ����
};


// *************************************************************************** //
// CMessageSynIbStoreRequest
// ͬ���̳���Ʒ����
// *************************************************************************** //
message CMessageSynIbStoreRequest
{
};

message CMessageSynIbStoreResponse
{
    repeated PBIbItemOnSale Goods   = 1;  // �̳������۵���Ʒ�б�
    repeated PBIbStore IbStore      = 2;  // ����, Ŀǰֻ���������ݽ���Ԫ������
    optional int32  Version	    = 3;  // �̳ǰ汾��
    repeated PBIbSubTab  FocusTab   = 4;  // �ص��ע�������ƷID
    optional string Bulletin        = 5;  // �̳ǹ��� 
};

// *************************************************************************** //
// CMessageSynFuncStoreRequest
// ͬ�����ܸ�����������
// *************************************************************************** //
message CMessageSynFuncStoreRequest
{
};

message CMessageSynFuncStoreResponse
{
	optional int32			Version		= 1;	//�汾��
	repeated PBFuncStore	FuncStore	= 2;	//������
};

// *************************************************************************** //
// CMessageChangeCorpsContributeNotify
// �ı���Ҿ��Ź��׶ȵ�֪ͨ
// *************************************************************************** //
message CMessageChangeCorpsContributeNotify
{		
	optional uint32				RoleID		=	1;		// ��ҽ�ɫID
	optional uint32				Contribute	=	2;		// ���׶�
	optional uint32				ChangeType 	=	3;		// 0��ʾ����1��ʾ����	
};

// *************************************************************************** //
// CMessageChangeCorpsGloryNotify
// �ı������ҫ��֪ͨ
// *************************************************************************** //
message CMessageChangeCorpsGloryNotify
{
	optional uint32				CorpsID		=	1;		// ����ID
	optional uint32				Glory		=	2;		// ������ҫֵ
	optional uint32				IfReduced	=	3;		// �Ƿ����	
	optional uint32				RoleID		=	4;		// ��ɫID
	optional uint32				Reason		=	5;		// ԭ��	
	optional string				RoleName	=	6;		// ��ɫ����
};

// *************************************************************************** //
// CMessageChangeCorpsMoneyNotify
// �ı���Ž�Ǯ��֪ͨ
// *************************************************************************** //
message CMessageChangeCorpsMoneyNotify
{
	optional uint32	CorpsID		=	1;		// ����ID
	optional uint32	Money		=	2;		// ��Ǯ
	optional uint32	IfPayout	=	3;		// �Ƿ����
	optional uint32	RoleID		=	4;		// ��ɫID
	optional uint32	Reason		=	5;		// ��Ǯ�ı��ԭ��
	optional string	RoleName	=	6;		// ��ɫ����
};

// *************************************************************************** //
// CMessageChangeCorpsBossTimes
// ����boss ��Ӵ���
// *************************************************************************** //
message CMessageChangeCorpsBossTimes
{
	optional uint32 CorpsID		=  1;		//����id
	optional uint32	Times		=  2;		//��Ӵ���
	optional uint32 RoleID		=  3;		//��ɫID
	optional uint32 BossID		=  4;		//Boss id
	optional string RoleName	=  5;		//��ɫ��
	optional uint32 Reason		=  6;		//ԭ��
};
// *************************************************************************** //
//CMessageChangeCorpsBossRefineValue
//����boss����ֵ�ı�
// *************************************************************************** //
message CMessageChangeCorpsBossRefineValue
{
	optional uint32 CorpsID			= 1;	// ����ID
	optional uint32 RefineValue		= 2;	// ����ֵ
	optional uint32 Reason			= 3;	// ����ֵ�ı�ԭ��
	optional uint32 RoleID			= 4;	// ��ɫID
	optional string RoleName		= 5;	// ��ɫ��
};
// *************************************************************************** //
// CMessageChangeCorpsCollectActive
// ���Ųɼ���Ծ�ȸı�
// *************************************************************************** //
message CMessageChangeCorpsCollectActive
{
	optional uint32 RoleID			= 1;	// ��ɫID
	optional uint32 ActiveValue		= 2;	// �ı�Ļ�Ծ��ֵ
	optional uint32 ChangeType		= 3;	// �ı�����   0��ʾ����1��ʾ����
}




// CMessageFamilyApExpChangedNotify
// �����Ա�����apֵ�ı��֪ͨ
// *************************************************************************** //
message CMessageFamilyApExpChangedNotify
{ 
	optional uint32 RoleID		=	1;			// ��Ա��ɫID
	optional uint32 FamiyID		=	2;			// ����ID
	optional uint32	AP			=	3;			// apֵ
	optional uint32	Exp			=	4;			// ����ֵ
};

// *************************************************************************** //
// CMessageCorpsApExpChangedNotify
// ���ų�Ա�����apֵ�ı��֪ͨ
// *************************************************************************** //
message CMessageCorpsApExpChangedNotify
{
	optional uint32 RoleID		=	1;			// ��Ա��ɫID
	optional uint32 CorpsID		=	2;			// ����ID
	optional uint32	AP			=	3;			// apֵ
	optional uint32	Exp			=	4;			// ����ֵ
};

message CMessageChangeJudgeScoreReuqest
{
	optional uint32	RoleID		= 1;
	optional uint32	Total		= 2;
};


// *************************************************************************** //
// CMessageChangeWizardRequest
// �ı�Ż�����
// *************************************************************************** //
message CMessageChangeWizardRequest
{
	optional uint32		CharID			= 1;		// ��ɫID
	optional uint32		LineID			= 2;
	optional uint32		CountryID		= 3;
	optional uint32		ChangeType		= 4;		// �ı����
	repeated uint32		WizardValue		= 5;		// �Ż�ֵ
};

// *************************************************************************** //
// CMessageChangeWizardResponse
// �ı�Ż���Ӧ
// *************************************************************************** //
message CMessageChangeWizardResponse
{
	optional uint32		CharID			= 1;		// ��ɫID
	optional uint32		Result			= 2;		// ������
};

// *************************************************************************** //
// CMessageChangeConstructRequest
// �ı佨������
// *************************************************************************** //
message CMessageChangeConstructRequest
{
	optional uint32		CharID			= 1;		// ��ɫID
	optional uint32		LineID			= 2;
	optional uint32		CountryID		= 3;
	optional uint32		ChangeType		= 4;		// �ı����
	repeated uint32		ConstructType	= 5;		// ��������
	repeated uint32		ConstructValue	= 6;		// ����ֵ
};

// *************************************************************************** //
// CMessageChangeConstructResponse
// �ı佨���Ӧ
// *************************************************************************** //
message CMessageChangeConstructResponse
{
	optional uint32		CharID			= 1;		// ��ɫID
	optional uint32		Result			= 2;		// ������
};

// *************************************************************************** //
// CMessageChangePowerRequest
// �ı���������
// *************************************************************************** //
message CMessageChangePowerRequest
{
	optional uint32		CharID			= 1;		// ��ɫID
	optional uint32		LineID			= 2;
	optional uint32		CountryID		= 3;
	optional uint32		ChangeType		= 4;		// �ı����
	optional uint32		PowerValue		= 5;		// ����ֵ
};

// *************************************************************************** //
// CMessageChangePowerResponse
// �ı�������Ӧ
// *************************************************************************** //
message CMessageChangePowerResponse
{
	optional uint32		CharID			= 1;		// ��ɫID
	optional uint32		Result			= 2;		// ������
};

message CMessageUseFunctionNotify
{
	optional uint32			CharID				= 1;	// ������ID,��������
	optional uint32			FunctionType		= 2;	// ��������
	optional uint32			FunctionOrder		= 3;	// ���ܱ��
	optional uint32			TargetID			= 4;	// Ŀ��ID
	optional uint32			WorldID				= 5;	// ��ӪID
	optional uint32			CountryID			= 6;	// ����ID
	optional string			SrcName				= 7;	// ����������
	optional TeleportData	Teleport			= 8;	// ��������
	optional uint32			CorpsID				= 9;	// ����ID
	optional uint32			FamilyID			= 10;	// ����ID
	optional uint32			TokenID				= 11;	// ���ͱ�־
};

message CMessageSetOfficialNotify
{
	optional uint32			CharID				= 1;	// ������ID,��������
	optional uint32			OfficialLevel		= 2;	// ��Ա����
	optional uint32			OfficialOrder		= 3;	// ��Ա���
	optional uint32			TargetID			= 4;	// Ŀ��ID
};

message CMessageChangeFriendNotify
{
	optional uint32			CharID				= 1;	// ������ID,��������
	optional uint32			ChangeType			= 2;	// �ı�����
	optional uint32			SrcWorld			= 3;	// Դ��Ӫ
	optional uint32			DesWorld			= 4;	// Ŀ����Ӫ
	optional uint32			ChangeValue			= 5;	// �ı�ֵ
};

message CMessageKillPersonRequest
{
	optional uint32			SrcCharID			= 1;	// ������ID
	optional uint32			DesCharID			= 2;	// ��ɱ��ID
	optional uint32			Honor				= 3;	// �Ƿ�������ɱ
};

message CMessageKillPersonResponse
{
	optional uint32			SrcCharID			= 1;	// ������ID
	optional uint32			DesCharID			= 2;	// ��ɱ��ID
	optional uint32			PKValue				= 3;	// �ı��pkֵ
};

message CMessageSyncNationNotify
{
	repeated uint32			NationStatus		 = 1;	// ���ҹ�ϵ
};

// *************************************************************************** //
// CMessageBuyFamilyItemRequest
// ���������Ʒ����Ϣ����,Ŀǰֻ�м�����
// *************************************************************************** //
message CMessageBuyFamilyItemRequest
{
	optional uint32		RoleID		= 1;		// ��ɫID
	optional uint32		EntityID	= 2;		// ʵ��ID
	optional uint32		FamilyID	= 3;		// ����ID
	optional uint32		ItemID		= 4;		// ��ƷID
	optional uint32		ItemNum		= 5;		// �������
	optional uint32		TotalCost	= 6;		// ���к���Ļ���( �������� )
	optional uint32		NpcTmpID	= 7;		// ��ѡNpc��ģ��ID	
};

// *************************************************************************** //
// CMessageBuyFamilyItemResponse
// ���������Ʒ����Ϣ��Ӧ,Ŀǰֻ�м�����
// *************************************************************************** //
message CMessageBuyFamilyItemResponse
{
	optional uint32		Errcode		= 1;		// ������
	optional uint32		RoleID		= 2;		// ��ɫID
	optional uint32		EntityID	= 3;		// ʵ��ID	
	optional uint32		ItemID		= 4;		// ��ƷID
	optional uint32		ItemNum		= 5;		// �������
};


// *************************************************************************** //
// CMessageBuyCorpsItemRequest
// ���������Ʒ����Ϣ����,Ŀǰֻ�о��ź��
// *************************************************************************** //
message CMessageBuyCorpsItemRequest
{
	optional uint32		RoleID		= 1;		// ��ɫID
	optional uint32		EntityID	= 2;		// ʵ��ID
	optional uint32		CorpsID		= 3;		// ����ID
	optional uint32		ItemID		= 4;		// ��ƷID
	optional uint32		ItemNum		= 5;		// �������
	optional uint32		TotalCost	= 6;		// ���к���Ļ���( �������� )
	optional uint32		NpcTmpID	= 7;		// ��ѡNpc��ģ��ID	
	optional uint32		CityMapID	= 8;		// �����ս���̵����ʾ���̵����ڵĳ��е�ͼID
};

// *************************************************************************** //
// CMessageBuyCorpsItemResponse
// ���������Ʒ����Ϣ��Ӧ,Ŀǰֻ�о��ź��
// *************************************************************************** //
message CMessageBuyCorpsItemResponse
{
	optional uint32		Errcode		= 1;		// ������
	optional uint32		RoleID		= 2;		// ��ɫID
	optional uint32		EntityID	= 3;		// ʵ��ID	
	optional uint32		ItemID		= 4;		// ��ƷID
	optional uint32		ItemNum		= 5;		// �������
};


// *************************************************************************** //
// CMessageClearFamilyRepetionInfoNotify
// ������帱����Ϣ��֪ͨ
// *************************************************************************** //
message CMessageClearFamilyRepetionInfoNotify
{ 
	optional uint32		FamilyID			=	1;		//	����ID
	optional uint32		RepetionScore		=	2;		//	�����÷�
};

// ֪ͨ���������޸ĳɹ� [12/8/2009 Macro]
message CMessageJudgeModifySuccessNotice
{
	optional uint32	 CharID	= 1;	// ������
};

// ��ѯԪ������
message CMessage4EQueryYuanBaoRequest
{
	optional uint32 RoleID = 1;	// �鿴�ߵ�RoleID
};

// ��ѯԪ����Ӧ
message CMessage4EQueryYuanBaoResponse
{
	optional int32	ResultCode = 1;	// ��Ӧ����
	optional uint32 RoleID = 2;	// ��ɫID
	repeated PBIbMoney Remain = 3;	// �ʻ����
};

// ��ȡԪ������
message CMessage4EDrawYuanBaoRequest
{
	optional uint32 RoleID 	= 1;	// �����ߵ�RoleID		
	optional PBIbMoney Draw = 2;	// �����ȡ�Ľ�Ǯ
};

// ��ȡԪ����Ӧ
message CMessage4EDrawYuanBaoResponse
{
	optional uint32 RoleID		= 1;	// �����ߵ�RoleID
	optional int32	ResultCode 	= 2;	// ��Ӧ����
	optional int32  Amount		= 3;	// ERating����	
	optional int32  LeftAmount	= 4;	// ERating����	
};

// ���м���һ�����Ϣ����
message CMessageFamilyExchangeRequest
{
	optional uint32	RoleID		= 1;	// ��ɫID
	optional uint32	NpcTmpID	= 2;	// npc��ģ��ID
	optional uint32	ComposeID	= 3;	// ���Ӻϳɵ�ID
	optional uint32	FamilyID	= 4;	// ����ID
	optional uint32	ItemNum		= 5;	// �һ�������
};

// ���м���һ�����Ϣ��Ӧ
message CMessageFamilyExchangeResponse
{
	optional uint32	Errcode		= 1;	// ������
	optional uint32	RoleID		= 2;	// ��ɫID
	optional uint32	NpcTmpID	= 3;	// npc��ģ��ID
	optional uint32	ComposeID	= 4;	// ���Ӻϳɵ�ID	
	optional uint32	ItemNum		= 5;	// �һ�������
};

// ���о��Ŷһ�����Ϣ����
message CMessageCorpsExchangeRequest
{
	optional uint32	RoleID		= 1;	// ��ɫID
	optional uint32	NpcTmpID	= 2;	// npc��ģ��ID
	optional uint32	ComposeID	= 3;	// ���Ӻϳɵ�ID	
	optional uint32	CorpsID		= 4;	// ����ID
	optional uint32	ItemNum		= 5;	// �һ�������
};

// ���о��Ŷһ�����Ϣ��Ӧ
message CMessageCorpsExchangeResponse
{
	optional uint32	Errcode		= 1;	// ������
	optional uint32	RoleID		= 2;	// ��ɫID
	optional uint32	NpcTmpID	= 3;	// npc��ģ��ID
	optional uint32	ComposeID	= 4;	// ���Ӻϳɵ�ID
	optional uint32	ItemNum		= 5;	// �һ����ɵ���Ʒ����	
};

// ���Ӽ���һ���Ʒ����Ϣ����
message CMessageAddFamilyExchangeItemNotify
{
	optional uint32	RoleID			= 1;	// ��ɫID
	optional uint32	FamilyID		= 2;	// ����ID	
	optional uint32	LeagueBagTmpID	= 3;	// �ع���Ʒ��ģ��ID
};

// ���Ӿ��Ŷһ���Ʒ����Ϣ����
message CMessageAddCorpsExchangeItemNotify
{
	optional uint32	RoleID			= 1;	// ��ɫID
	optional uint32	CorpsID			= 2;	// ����ID	
	optional uint32	LeagueBagTmpID	= 3;	// �ع���Ʒ��ģ��ID
}
message CMessageGateEntityGMMove
{
	optional string RoleName	= 1;
	optional int32	LineID		= 2;
	optional int32 	MapID		= 3;
	optional int32  PosX		= 4;
	optional int32	PosY		= 5;

	optional int64  Key			= 6;
};

message CMessageSceneEntityGMMove
{
	optional int32 RoleID		= 1;
    optional int32  LineID      = 2;
    optional int32  MapID       = 3;
    optional int32  PosX        = 4;
    optional int32  PosY        = 5;

	optional int64  Key			= 6;
};

/// ���� ���Ϣ
message SingleActivityObj
{
	optional uint32 ActivityID		= 1;
	optional uint32 TimeType		= 2;
	optional uint32 TimeInfo	    = 3;
	optional uint32 LmtLevel		= 4;
	optional uint32 MaxTimes		= 5;
	optional uint32 State			= 6; // ״̬
};

message DropInfo
{
	optional uint32 OgreID		= 1;
	optional uint32 DropID		= 2;
};

message MapDrop
{
	optional uint32 DropID			= 1; // ����ID
	optional uint32 DropType		= 2; // ��������
	repeated uint32 MapIDs			= 3; // ��ͼID
};

// ��ۺϾ�̬��Ϣ
message SingleActivityInfo
{
	optional uint32   ActivityID		= 1;
	repeated DropInfo dropinfo			= 2;	// ������Ϣ
	repeated uint32   ogreindex			= 3;	// ������Ϣ
};

// ����֪ͨ�������ջ�б�
message CMessageTodayActivitysNotify
{
	repeated SingleActivityObj  ActivityList = 1;
	repeated SingleActivityInfo ActivityInfo = 2;
};

message SingleActivity
{
	optional uint32 ActivityID		= 1;
	optional uint32 ActivityState   = 2;
	repeated MapDrop  MapDrops		= 3;	// ��ͼ��������
};

// ����֪ͨ����XXX���ʼ/������
message CMessageActivityChangeNotify
{
	repeated SingleActivity ActivityList = 1;
};

// ����֪ͨ��Ұ�ȫ����״̬�ı��֪ͨ
message CMessageChangePasswordStatusNotify
{
	optional uint32	RoleID		=	1;	// ��ɫID
	optional uint32	PwdStatus	=	2;	// ����״̬
	optional string	Password	=	3;	// ����
};

// ֪ͨ���������ҳƺŸ��� [1/28/2010 Macro]
message CMessageUpdateNationTitleNotice
{
	optional int32	RoleID	= 1;	// ���ID
	optional uint32	TitleID	= 2;	// �ƺ�ID
	optional uint32	IsAdd	= 3;	// ���ӡ�ɾ��
};

// �������ھ��ŵĹ��ҳƺ��б�
message CMessageGetNationTitleListRequest
{
	optional int32	RoleID	= 1;	// ���ID
};

message CMessageGetNationTitleListResponse
{
	optional int32	RoleID	= 1;	// ���ID
	repeated uint32	TitleList	= 2;	// �ƺ��б�
};

// ����֪ͨ���ػ�Ա��־�����ı�
message CMessageSGProVipFlagNotice
{
	optional int32	RoleID	= 1;	// ���ID
	optional uint32	VipFlag	= 2;	// ��Ա��־
};

// ����֪ͨ����������ҲƲ�����
message CMessageResetRolePasswordNotify
{
	optional uint32	RoleID = 1;	
}

// ֪ͨ��ȫ�ر�
message CMessgeSafeShutdownNotify
{
	optional uint32 ServerType	= 1; // ����������
	optional uint32 ServerID	= 2; // ������ID
	optional uint32 OpType		= 3; // �رշ�ʽ
};

// ֪ͨ��ȫ�رջ�Ӧ
message CMessgeSafeShutdownAck
{
	optional uint32 ServerType	= 1; // ����������
	optional uint32 ServerID	= 2; // ������ID
	optional uint32 OpType		= 3; // �رշ�ʽ
};

// ����վ��Ǯ�ع�
message CMessageRollCorpsMoneyRequest
{
	optional uint32	IsAll	= 1;
	optional uint32	CorpsID = 2;
	optional uint32	NpcID	= 3;
};

// ����ս��ͼ֪ͨ
message CMessageCorpsBattleMapNotice
{
	optional uint64 BattleKey = 1;
	optional uint32	RoleID = 2;
};

// �����ټ�����
message CMessageTrySummonRequest
{
	optional uint32	CharID	=	1;
	optional string	CharName =	2;
	optional uint32 ItemIndex = 3;
	optional uint32	SummonType = 4;
};

// �����ټ���Ӧ
message CMessageTrySummonResponse
{
	optional uint32	CharID	=	1;
	optional string	CharName =	2;
	optional uint32	Result	=	3;
	optional uint32 ItemIndex = 4;
	optional uint32	SummonType = 5;
};

// ʵ���ټ�����
message CMessageRealSummonRequest
{
	optional uint32	CharID	=	1;
	optional string	CharName =	2;
	optional uint32	SummonType	= 3;
	optional uint32	LineID		=	4;
	optional uint32	MapID		=	5;
	optional uint32	PosX		=	6;
	optional uint32	PosY		=	7;
};

// ʵ���ټ�֪ͨ
message CMessageRealSummonNotify
{
	optional string SrcCharName	=	1;
	optional uint32	LineID		=	2;
	optional uint32	MapID		=	3;
	optional uint32	PosX		=	4;
	optional uint32	PosY		=	5;
	optional uint32	TokenID		=	6;
	optional uint32 DesCharID	=	7;
	optional uint32	FamilyID	=	8;
	optional uint32	CorpsID		=	9;
	optional uint32	SrcCharID	=	10;
};

// ������Ʒ����֪ͨ
message CMessageLockGoodsRequest
{
	optional uint32 GoodsID 	= 1;  // ��ƷID
	optional int32  LockCount 	= 2;  // �������Ʒ����
	optional uint32 RoleID 		= 3;  // ������Ʒ�Ľ�ɫID
	optional int32  TransObjID	= 4;  // �˴ι���Ľ��׶���ID���ǽ���ID
};

message CMessageLockGoodsResponse
{
	optional int32 Result 		= 1;  // ������
	optional uint32 GoodsID 	= 2;  // ������ƷID
	optional uint32 RoleID 		= 3;  // �����ɫID
	optional int32  LockCount 	= 4;  // ���������
	optional int32  Remain		= 5;  // ʣ�������
	optional int32  TransObjID 	= 6;  // ���׵Ķ���ID
};

message CMessageS2GRoleMove
{
	optional string SrcRole	= 1;
	optional string DesRole	= 2;
};

message CMessageG2SRoleMove
{
	optional string SrcRole = 1;
	optional string DesRole = 2;
};

message CMessageWarChangeNotify
{
	optional uint32	WorldID			=	1;
	optional uint32	SeedType		=	2;
	optional uint32	SeedValue		=	3;
	optional uint32	SourceType		=	4;
	optional uint32	SourceValue		=	5;
	optional uint32	MapID			=	6;
};

message CMessageReliveChangeNotify
{
	repeated uint32	WorldID			=	1;
	repeated uint32	CampID			=	2;
	optional uint32	WarStatus		=	3;
};

message WarHonorData
{
	optional uint32 CharID			=	1;
	optional uint32	WarHonor		=	2;
	optional uint32	WarKill			=	3;
};

message CMessageObtainWarHonorNotify
{
	repeated WarHonorData	WarHonor	=	1;
	optional uint32			IsKill		=	2;
};


message CMessageBourseG2SLoadList
{
	optional uint32	ListID					= 1;
	optional PBBourseDetailList BuyList     = 2;
	optional PBBourseDetailList SellList    = 3;
};

message CMessageBourseS2GLoadList
{
};


message CMessageSyncWarStatusNotify
{
	optional uint32 WarStatus		=	1;
	optional uint32	WarSerial		=	2;
};

message CMessageWarControlNotify
{
	optional uint32	ControlState	=	1;
	optional int32	GMHour			=	2;
	optional int32	GMMin			=	3;
	optional int32	GMDay			=	4;
	optional uint32 WarSerial		=	5;
};

message CMessageBourseTradeNotice
{
	optional PBBourseDetail BuyDetail		= 1;
	optional PBBourseDetail SellDetail		= 2;
};
// ���󳡾��������ٴδ���(���ļ�)
message CMessageReSavePlayerRequest
{
	optional uint32 RoleID			= 1; // ��ɫID
};

// ���󳡾��������ٴδ��� ��Ӧ
message CMessageReSavePlayerResponse
{
	optional uint32 RoleID			= 1; // ��ɫID
	optional uint32 Result			= 2; // ��� 0�ɹ�
	optional uint32 LineID			= 3; // ��ǰ��ID
	optional uint32 MapID			= 4; // ��ǰ��ͼID
	optional uint32 AccountID		= 5; // ����˺�ID
	optional uint32 PosX			= 6; // ��ǰ����X
	optional uint32 PosY			= 7; // ��ǰ����Y
};


message CMessageBoursePlayerTradeBuyNotice
{
	optional PBBourseDetail Detail      = 1;
};

message CMessageBoursePlayerTradeSellNotice
{
	optional PBBourseDetail Detail      = 1;
};

message CMessageWarStoneOverNotify
{
	optional uint32	 MapID			=	1;
};

message CMessageCreateWarStoneNotify
{
	optional uint32	 StoneLevel		=	1;
	optional uint32	 MapID			=	2;
};

message CMessageAddTaxNotify
{
	optional uint32	 Money			=	1;
};

// ���󳡾��������ٴδ��� ��Ӧ
message CMessageSendSysMailToPlayer
{
    optional string role_name	= 1;    // ����������
    optional uint32 role_id		= 2;    // ������ID
    optional string sender_name	= 3;    // ����������
    optional string title		= 4;    // �ʼ�����
    optional string body		= 5;    // �ʼ�����
    optional uint32 receive_countryid= 6; // ���������ڵ���Ӫ
    optional uint32 gateway_id  = 7;    // ����ID
    optional uint32 game_id     = 8;    // ��ϷID
    optional uint32 fd          = 9;
    optional uint32 type        = 10;
    optional uint32 session_id  = 11;	
    repeated uint32	ItemID		= 13;	// ��ƷID
    repeated uint32	ItemNum		= 14;	// ��Ʒ����	 
    optional uint32	MailSendType= 15;	// �ʼ���������()
};

// ����Ӫ�������������ж����ֵ�����ֵ
message CMessageCampAddHonerScore
{
	optional uint32 role_id			= 1;    // ��ɫID
	optional uint32 honer_value		= 2;    // ����ֵ
	optional uint32 camp_id			= 3;    // ��ӪID
};

// ********************************************************************** //
// CMessageBattleTeamFixWait  ��Ϸ������ -> ���ط�����
// ������붨ʱ�����ĸ����ȴ��б�
// ********************************************************************** //
message CMessageBattleTeamFixWait
{
	optional uint32 CharID		= 1; // ��ɫID
	optional uint32 Level		= 2; // �ȼ�
	optional uint32 BattleID	= 3; // ����ID
	optional uint32 MapID		= 4;
};

// ֪ͨ����ĳЩ��¼�����
message CMessageActivityEventNotify
{
	optional uint32 ActivityID	= 1;	// �ID
	optional uint32 EventID		= 2;	// �¼�ID
	repeated uint32 IntParams   = 3;	// ���ݵ����Ͳ���
	repeated string StrParams   = 4;	// ���ݵ��ַ�������
};


message CMessageAddMasterPointRequest
{
	optional uint32	MasterID	= 1;
	optional uint32	Point		= 2;
};

message CMessageAddMasterPointNotify
{
	optional uint32	CharID		= 1;
	optional uint32	Point		= 2;
};

// ********************************************************************** //
// CMessageBattleSingleFixWait  ��Ϸ������ -> ���ط�����
// ���˽��붨ʱ��ʱ�����ĸ����ȴ��б�
// ********************************************************************** //
message CMessageBattleSingleFixWait
{
	optional uint32 CharID		= 1; // ��ɫID
	optional uint32 Level		= 2; // �ȼ�
	optional uint32 BattleID	= 3; // ����ID
	optional uint32 MapID		= 4;
};

message CMessageSpecialEventNotify
{
	optional uint32	SrcWorldID	= 1;
	optional uint32	DesWorldID	= 2;
	optional uint32	EventType	= 3;
	optional uint32	CharID		= 4;
};

message CMessageAcquireMasterNotify
{
	optional uint32	SlaveID		= 1;
	optional uint32	MasterID	= 2;
};
// ********************************************************************** //
// CMessageBattleWinnerNotify  ��Ϸ������ -> ���ط����� 
// ���˽��붨ʱ��ʱ�����ĸ����ȴ��б�
// ********************************************************************** //
message CMessageBattleWinnerNotify
{
	optional uint32 HasWinner	= 1; // ��ɫID
	optional uint32 BattleID	= 2; // ����ID
	optional uint32 Level		= 3; // �ȼ�
	optional uint32 CharID		= 4; // ��ɫID
};

// *************************************************************************** //
// CMessageChangeFamilyStabilityNotify
// �ı���尲����
// *************************************************************************** //
message CMessageChangeFamilyStabilityNotify
{
	optional uint32				FamilyID	=	1;		// ����ID	
	optional uint32				RoleID		=	3;		// ��ɫID
	optional uint32				Reason		=	4;		// ԭ��	
	optional string				RoleName	=	5;		// ��ɫ����
	optional uint32				OnLineTime	=	6;		// ����ʱ��	
	optional uint32				RoleLevel	=	7;		// ��ҵȼ�
	optional uint32				Value		=	9;		// �ı����ֵ(�����и�)
};

// *************************************************************************** //
// CMessageS2GJionOnTimeOpenBattleRequest
// ֪ͨgateserver ��ҽ��붨ʱ���Ÿ�������������������
// *************************************************************************** //
message CMessageS2GJoinOnTimeOpenBattleRequest
{
	optional uint32 BattleID= 1;
	optional uint32 MapID	= 2;
	optional uint32 CharID	= 3;
	optional uint32 PosX	= 4;
	optional uint32 PosY	= 5;
	optional uint32 Level	= 6;
};

message CMessageSyncGTAndLWNotify
{
	repeated GTAndLWInfo GTInfo	= 1;
	repeated GTAndLWInfo LWInfo = 2;
};

message CMessageS2GBattleClose
{
	optional uint32 BattleID = 1;
	optional uint32 MapID	 = 2;
};

//�������boss����
message CMessageS2GIntoCorpsBossRepetion
{
	optional uint32	BattleID	= 1;
	optional uint32	MapID		= 2;
	optional uint32 CharID		= 3;
	optional uint32 CorpsID		= 4;
	optional uint32 PostX		= 5;
	optional uint32 PostY		= 6;
};

//����boss��������
message CMessgeS2GEndCorpsBossRepetion
{
	optional uint32 BattleID	= 1;
	optional uint32	MapID		= 2;
	optional uint32	CorpsID		= 3;
};

// ��������
//**********************************************
//���ػ�Ӧ�ķ���������Ϣ
// *******************************************

message PBGroupTasks
{
	optional uint32 TaskID			= 1;
	optional uint32 TaskState		= 2;
};

//  �鿴����չ�������  
message CMessageGateCheckGroupPublishRequest
{
	optional uint32	CharID			= 1;
	optional uint32 PublishType		= 2;
};


//  ���͵�����  �������� �������ؼ�¼
message CMessageGatePublishGroupRequest
{
	optional uint32 CharID			= 1;
	optional uint32 TaskID			= 2;
	optional uint32 PublishType		= 3;
	optional uint32 TaskState		= 4;
	optional uint32	PayGroupMoney	= 5;
};


//***************************************
//���ػ�Ӧ��Ϣ

message PBGroupInfo
{
	optional uint32 GroupID			= 1;
	optional uint32 GroupLevel		= 2;
	optional uint32 GroupMoney		= 3;
	optional uint32 PlayerPosition	= 4;
};

//���ػ�Ӧ  չ������
message CMessageGateCheckGroupPublishResponse
{

	optional uint32 CharID			= 1;
	optional uint32 PublishType		= 2;
	repeated PBGroupTasks	Tasks	= 3;
	optional PBGroupInfo GroupInfo	= 4;
	optional uint32 Result			= 5;
};

// ���ػ�Ӧ  ��������
message CMessageGatePublishGroupResponse
{
	optional uint32 CharID			= 1;
	optional uint32 TaskID			= 2;
	optional uint32 PublishType		= 3;
	optional uint32 TaskState		= 4;
	optional uint32 TaskAcion		= 5;
	optional uint32 Result			= 6;		// ���ػ�Ӧ  �ɹ����
};