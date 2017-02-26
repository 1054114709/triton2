import "property_pb.hxx";
import "coremessage_pb.hxx";

// ������ٶ�����/������
option optimize_for = SPEED;

// ��������Ϣ��ID�����ٴΣ���ֹ�ظ�����
// promessage��Ϣ��ID��Χ(0x0800 -- 0x0BFF)
enum PRO_MSG_ID
{	
	ID_S2C_NOTIFY_YOURPRODATA					= 0x0800;		// ������->�ͻ��� ���������Ϣ
	ID_S2C_NOTIFY_CREATEPLAYER					= 0x0801;		// ������->�ͻ��� �������
	ID_S2C_NOTIFY_CREATENPC						= 0x0802;		// ������->�ͻ��� ����NPC
	ID_C2S_REQUEST_USESKILL						= 0x0803;		// �ͻ���->������ ʹ�ü���
	ID_C2S_REQUEST_NORMALATTACK					= 0x0804;		// �ͻ���->������ ��ͨ����
	ID_C2S_REQUEST_PICKITEM						= 0x0805;		// �ͻ���->������ ʰȡ��Ʒ
	ID_C2S_REQUEST_CLICKNPC						= 0x0806;		// �ͻ���->������ �������NPC
	ID_S2C_RESPONSE_CLICKNPC					= 0x0807;		// ������->�ͻ��� �������NPC
	ID_S2C_NOTIFY_CLOSEDIALOG					= 0x0808;		// ������->�ͻ��� �رնԻ�֪ͨ
	ID_S2C_NOTIFY_CHANGEAPPERTAININGS			= 0x0809;		// ������->�ͻ��� ֪ͨ�޸���Ʒ����
	ID_S2C_NOTIFY_UPDATEMONEY					= 0x0811;		// ������->�ͻ��� ��ý�Ǯ֪ͨ
	ID_C2S_REQUEST_PURCHASEITEM					= 0x0812;		// �ͻ���->������ �����������
	ID_C2S_REQUEST_SELLITEM						= 0x0813;		// �ͻ���->������ ���۵�������
	ID_S2C_NOTIFY_REMOVEITEM					= 0x0814;		// ������->�ͻ��� ɾ������֪ͨ
	ID_S2C_NOTIFY_REMOVETASKITEM				= 0x0815;		// ������->�ͻ��� ɾ���������֪ͨ
	ID_C2S_REQUEST_THROWITEM					= 0x0816;		// �ͻ���->������ ������������
	ID_S2C_NOTIFY_THROWITEM						= 0x0817;		// ������->�ͻ��� ��������֪ͨ
	ID_C2S_REQUEST_THROWMONEY					= 0x0818;		// �ͻ���->������ ������Ǯ����
	ID_C2S_REQUEST_SETSHORTCUT					= 0x0819;		// �ͻ���->������ ���ÿ�ݼ�����
	ID_S2C_NOTIFY_ENTITYRELIFE					= 0x081A;		// ������->�ͻ��� ʵ�帴��֪ͨ
	ID_S2C_NOTIFY_ENTITYDISAPPEAR				= 0x081B;		// ������->�ͻ��� ʵ����ʧ֪ͨ
	ID_C2S_REQUEST_PLAYERRELIVE					= 0x081C;		// �ͻ���->������ ��Ҹ�������
	ID_S2C_NOTIFY_PLAYERRELIVE					= 0x081D;		// ������->�ͻ��� ��Ҹ���֪ͨ
	ID_S2C_NOTIFY_REMOVEBUFF					= 0x081E;		// ������->�ͻ��� �Ƴ�BUFF֪ͨ
	ID_S2C_NOTIFY_CHANGESTATE					= 0x081F;		// ������->�ͻ��� ״̬�ı�֪ͨ
	ID_S2C_NOTIFY_USESKILL						= 0x0820;		// ������->�ͻ��� ʹ�ü���֪ͨ
	ID_S2C_NOTIFY_FUNCRESULT					= 0x0821;		// ������->�ͻ��� ���ܽ�� = PROMSG + 0; ���� = PROMSG + 0;���ߺ�Buff��ɵĽ�����ǹ�����ɵ�
	ID_S2C_NOTIFY_CHANGEMETIER					= 0x0822;		// ������->�ͻ��� �ı�ְҵ��֪ͨ
	ID_S2C_NOTIFY_LOCKITEM						= 0x0823;		// ������->�ͻ��� ������Ʒ��֪ͨ
	ID_S2C_NOTIFY_LEVELUP						= 0x0824;		// ������->�ͻ��� ������֪ͨ
	ID_S2C_NOTIFY_OBTAINEXP						= 0x0825;		// ������->�ͻ��� ��þ����֪ͨ
	ID_C2S_REQUEST_MOVEITEM						= 0x0826;		// �ͻ���->������ .��Ʒ������
	ID_S2C_NOTIFY_MOVEITEM						= 0x0827;		// ������->�ͻ��� �ƶ���Ʒ��֪ͨ
	ID_S2C_NOTIFY_INSERTITEM					= 0x0828;		// ������->�ͻ��� �����Ʒ��֪ͨ
	ID_S2C_NOTIFY_PRODEBUG						= 0x0829;		// ������->�ͻ��� ��������
	ID_S2C_NOTIFY_PROERROR						= 0x082A;		// ������->�ͻ��� ���Դ�����Ϣ
	ID_C2S_REQUEST_EQUIPITEM					= 0x082B;		// �ͻ���->������ װ����Ʒ������
	ID_C2S_REQUEST_UNEQUIPITEM					= 0x082C;		// �ͻ���->������ ж��װ��������
	ID_S2C_NOTIFY_EQUIPITEM						= 0x082D;		// ������->�ͻ��� װ����Ʒ��֪ͨ
	ID_S2C_NOTIFY_UNEQUIPITEM					= 0x082E;		// ������->�ͻ��� ж��װ����֪ͨ
	ID_S2C_NOTIFY_PLAYERCHANGEEQUIQ				= 0x082F;		// ������->�ͻ��� ��һ�װ��֪ͨ
	ID_S2C_NOTIFY_ENTITYREFRESH					= 0x0830;		// ������->�ͻ��� ʵ����µ�֪ͨ
	ID_C2S_REQUEST_CLICKSKILLPOINT				= 0x0831;		// �ͻ���->������ �Ӽ��ܵ������
	ID_S2C_RESPONSE_CLICKSKILLPOINT				= 0x0832;		// ������->�ͻ��� �Ӽ��ܵ�Ļ�Ӧ
	ID_C2S_REQUEST_CLICKPROPERTYPOINT			= 0x0833;		// �ͻ���->������ �����Ե������
	ID_S2C_RESPONSE_CLICKPROPERTYPOINT			= 0x0834;		// ������->�ͻ��� �����Ե�Ļ�Ӧ
	ID_C2S_REQUEST_RESETSPP						= 0x0835;		// �ͻ���->������ ����1�����Ե�
	ID_C2S_REQUEST_RESETAPP						= 0x0836;		// �ͻ���->������ �����������Ե�
	ID_S2C_RESPONSE_RESETSPP					= 0x0837;		// ������->�ͻ��� ����1�����Ե�
	ID_S2C_RESPONSE_RESETAPP					= 0x0838;		// ������->�ͻ��� �����������Ե�
	ID_C2S_REQUEST_RESETSSP						= 0x0839;		// �ͻ���->������ ����1�㼼�ܵ�
	ID_C2S_REQUEST_RESETASP						= 0x083A;		// �ͻ���->������ �������м��ܵ�
	ID_S2C_RESPONSE_RESETSSP					= 0x083B;		// ������->�ͻ��� ����1�㼼�ܵ�
	ID_S2C_RESPONSE_RESETASP					= 0x083C;		// ������->�ͻ��� �������м��ܵ�
	ID_S2C_NOTIFY_ENTITYDIE						= 0x083D;		// ������->�ͻ��� ʵ��������֪ͨ
	ID_C2S_REQUEST_GETROLEPERSONALINFOBYID		= 0x083E;		// �͑���->������ ͨ��ID�õ������Ϣ
	ID_C2S_REQUEST_GETROLEPERSONALINFOBYNAME	= 0x083F;		// �͑���->������ ͨ�����ֵõ������Ϣ
	ID_S2C_RESPONSE_SENDROLEPERSONALINFO		= 0x0840;		// ������->�ͻ��� ���������Ϣ
	ID_C2S_REQUEST_SETROLEPERSONALINFO			= 0x0841;		// �ͻ���->������ �޸������Ϣ
	ID_S2C_RESPONSE_ROLEPERSONALINFOBACK		= 0x0842;		// ������->�ͻ��� ����޸����ϻ���
	ID_C2S_REQUEST_USEITEM						= 0x0843;		// �ͻ���->������ ʹ����Ʒ
	ID_S2C_RESPONSE_USEITEM						= 0x0844;		// ������->�ͻ��� ʹ����Ʒ
	ID_S2C_NOTIFY_PLAYERUSEITEM					= 0x0845;		// ������->�ͻ��� ���ʹ�õ���
	ID_S2C_RESPONSE_TELEPORT					= 0x0846;		// ������->�ͻ��� ����
	ID_C2S_REQUEST_PRODUCEEQUIP					= 0x0847;		// �ͻ���->������ ����װ��
	ID_C2S_REQUEST_UPGADDITEM					= 0x0848;		// �ͻ���->������ ����������Ʒ
	ID_S2C_RESPONSE_UPGADDITEM					= 0x0849;		// ������->�ͻ��� ����������Ʒ
	ID_C2S_REQUEST_UPGDELITEM					= 0x084A;		// �ͻ���->������ �û�������Ʒ
	ID_S2C_RESPONSE_UPGDELITEM					= 0x084B;		// ������->�ͻ��� �û�������Ʒ
	ID_C2S_REQUEST_UPGEQUIP						= 0x084C;		// �ͻ���->������ ����װ��
	ID_S2C_NOTIFY_UPGEQUIP						= 0x084D;		// ������->�ͻ��� ����װ�����
	ID_C2S_REQUEST_PRODUCEPHY					= 0x084E;		// �ͻ���->������ ����ҩƷ
	ID_S2C_NOTIFY_PROFIN						= 0x084F;		// ������->�ͻ��� �������
	ID_S2C_NOTIFY_PROBREAK						= 0x0850;		// ������->�ͻ��� �����ж�
	ID_C2S_REQUEST_PUSHRUNE						= 0x0853;		// �ͻ���->������ �ŷ���
	ID_S2C_RESPONSE_PUSHRUNE					= 0x0854;		// ������->�ͻ��� �ŷ���
	ID_C2S_REQUEST_POPRUNE						= 0x0855;		// �ͻ���->������ �÷���
	ID_S2C_RESPONSE_POPRUNE						= 0x0856;		// ������->�ͻ��� �÷���
	ID_C2S_REQUEST_INSERTRUNE					= 0x0857;		// �ͻ���->������ �����
	ID_S2C_RESPONSE_INSERTRUNE					= 0x0858;		// ������->�ͻ��� �����
	ID_C2S_REQUEST_PUSHJEWEL					= 0x0859;		// �ͻ���->������ �ű�ʯ
	ID_S2C_RESPONSE_PUSHJEWEL					= 0x085A;		// ������->�ͻ��� �ű�ʯ
	ID_C2S_REQUEST_POPJEWEL						= 0x085B;		// �ͻ���->������ �ñ�ʯ
	ID_S2C_RESPONSE_POPJEWEL					= 0x085C;		// ������->�ͻ��� �ñ�ʯ
	ID_C2S_REQUEST_INSERTJEWEL					= 0x085D;		// �ͻ���->������ �ⱦʯ
	ID_S2C_RESPONSE_INSERTJEWEL					= 0x085E;		// ������->�ͻ��� �ⱦʯ
	ID_C2S_REQUEST_PUSHSLOT						= 0x085F;		// �ͻ���->������ �ſ���
	ID_S2C_RESPONSE_PUSHSLOT					= 0x0860;		// ������->�ͻ��� �ſ���
	ID_C2S_REQUEST_POPSLOT						= 0x0861;		// �ͻ���->������ �ÿ���
	ID_S2C_RESPONSE_POPSLOT						= 0x0862;		// ������->�ͻ��� �ÿ���
	ID_C2S_REQUEST_OPENSLOT						= 0x0863;		// �ͻ���->������ ����
	ID_S2C_RESPONSE_OPENSLOT					= 0x0864;		// ������->�ͻ��� ����
	ID_C2S_REQUEST_PUSHEAT						= 0x0865;		// �ͻ���->������ �ų�װ��
	ID_S2C_RESPONSE_PUSHEAT						= 0x0866;		// ������->�ͻ��� �ų�װ��
	ID_C2S_REQUEST_POPEAT						= 0x0867;		// �ͻ���->������ �ó�װ��
	ID_S2C_RESPONSE_POPEAT						= 0x0868;		// ������->�ͻ��� �ó�װ��
	ID_C2S_REQUEST_EATEQUIP						= 0x0869;		// �ͻ���->������ ��װ��
	ID_S2C_RESPONSE_EATEQUIP					= 0x086A;		// ������->�ͻ��� ��װ��
	ID_C2S_REQUEST_PUSHCOMPOSE					= 0x086B;		// �ͻ���->������ �źϳ�
	ID_S2C_RESPONSE_PUSHCOMPOSE					= 0x086C;		// ������->�ͻ��� �źϳ�
	ID_C2S_REQUEST_POPCOMPOSE					= 0x086D;		// �ͻ���->������ �úϳ�
	ID_S2C_RESPONSE_POPCOMPOSE					= 0x086E;		// ������->�ͻ��� �úϳ�
	ID_C2S_REQUEST_COMPOSE						= 0x086F;		// �ͻ���->������ �ϳ�
	ID_S2C_RESPONSE_COMPOSE						= 0x0870;		// ������->�ͻ��� �ϳ�
	ID_C2S_REQUEST_PLAYERTELE					= 0x0871;		// �ͻ���->������ ��Ҵ���
	ID_S2C_RESPONSE_PLAYERTELE					= 0x0872;		// ������->�ͻ��� ��Ҵ���
	ID_S2C_RANDMOVEDIRECTION					= 0x0873;		// ������->�ͻ��� ����漴�ƶ�
	ID_C2S_DEBUGCOMMAND							= 0x0875;		// �ͻ���->������ ��������
	ID_C2S_NOTIFY_DIRECTION						= 0x0876;		// �ͻ���->������ ͬ����ҷ���
	ID_S2C_NOTIFY_DIRECTION						= 0x0877;		// ������->�ͻ��� ͬ����ҷ���
	ID_C2S_REQUEST_CHANGEPETMODE				= 0x0878;		// �ͻ���->������ �ı����ģʽ
	ID_S2C_RESPONSE_CHANGEPETMODE				= 0x0879;		// ������->�ͻ��� �ı����ģʽ
	ID_S2C_NOTIFY_PETLEVELUP					= 0x087A;		// ������->�ͻ��� �ٻ�����ʱ�ȼ�����
	ID_S2C_NOTIFY_CHANGEHARDINESS               = 0x087B;       // ������->�ͻ��� ���װ���;öȸı�
	ID_S2C_NOTIFY_SYNCPOS						= 0x087C;		// ������->�ͻ��� ͬ��λ������
	ID_C2S_REQUEST_MENDEQUIPMENT                = 0x087D;       // �ͻ���->������ ����װ������
	ID_S2C_RESPONSE_MENDEQUIPMENT               = 0x087E;       // ������->�ͻ��� ����װ�����
	ID_S2C_NOTIFY_SPEEDCHANGED					= 0x087F;		// ������->�ͻ��� ����ƶ��ٶȸı�
	ID_S2C_NOTIFY_PROEXP						= 0x0880;		// ������->�ͻ��� �����������ȼ��ı�
	ID_C2S_REQUEST_SALEITEM						= 0x0881;		// �ͻ���->������ NPC���׻ع���Ʒ��Ϣ(�۳���)
	ID_S2C_RESPONSE_SALEITEM					= 0x0882;		// ������->�ͻ��� NPC���׻ع���Ʒ��Ϣ(�۳���)
	ID_C2S_REQUEST_BUYBACK						= 0x0883;		// �ͻ���->������ �����۳���NPC����Ʒ
	ID_C2S_REQUEST_MOVESTORAGEITEM              = 0x0884;       // �ͻ���->������ �ڰ����Ͳֿ�֮���ƶ���Ʒ     
	ID_C2S_REQUEST_CLOSEWINDOW					= 0x0885;		// �ͻ���->������ �ر�ָ���Ĵ���
	ID_S2C_RESPONSE_CLOSEWINDOW					= 0x0886;		// ������->�ͻ��� �ر�ָ���Ĵ���
	ID_S2C_RESPONSE_BINDITEM                    = 0x0887;       // ������->�ͻ��� ���͵��߰󶨵���Ϣ
	ID_C2S_REQUEST_BINDITEMREQ                  = 0x0888;       // �ͻ���->������ ����󶨵�֪ͨ
	ID_S2C_NOTIFY_ERRORACTONBINDITEM            = 0x0889;       // ������->�ͻ��� �԰�װ���Ĵ������
	ID_C2S_REQUEST_ADDITEMREQUEST               = 0x088A;       // �ͻ���->������ ��Ӱ󶨵���Ʒ
	ID_S2C_RESPONSE_ADDITEMREPONSE              = 0x088B;       // ������->�ͻ��� ��Ӱ���Ʒ��ȷ��
	ID_C2S_REQUEST_TAKEITEMREQUEST              = 0x088C;       // �ͻ���->������ ȡ�°���Ʒ������
	ID_S2C_RESPONSE_TAKEITEMRESPONSE            = 0x088D;       // ������->�ͻ��� ȡ����Ʒ�Ļ�Ӧ 
	ID_C2S_REQUEST_ADDITEMFORFREE               = 0x088E;       // �ͻ���->������ ����ӽ����Ʒ������
	ID_S2C_RESPONSE_ADDITEMFORFREE              = 0x088F;       // ������->�ͻ��� ����ӽ����Ʒ����Ļ�Ӧ
	ID_C2S_REQUEST_TAKEITEMFORFREE              = 0x0890;       // �ͻ���->������ ж�´�����Ʒ������
	ID_S2C_RESPONSE_TAKEITEMFORFREE             = 0x0891;       // ������->�ͻ��� ж�´�����Ʒ�Ļ�Ӧ
	ID_C2S_REQUEST_FREEITEM                     = 0x0892;       // �ͻ���->������ �������Ʒ������
	ID_S2C_RESPONSE_FREEITEM                    = 0x0893;	    // ������->�ͻ��� �������Ʒ����Ļ�Ӧ	
	ID_S2C_NOTIFY_RIDEHORSE						= 0x0894;		// ������->�ͻ��� ����֪ͨ
	ID_C2S_REQUEST_USETASKITEM					= 0x0895;       // �ͻ���->������ ʹ�������������
	ID_S2C_NOTICE_USETASKITEM					= 0x0896;       // ������->�ͻ��� ʹ���������֪ͨ
	ID_C2S_REQUEST_STUDYSKILL					= 0x0897;		// �ͻ���->������ ѧϰ����
	ID_S2C_RESPONSE_STUDYSKILL					= 0x0898;		// ������->�ͻ��� ѧϰ����
	ID_C2S_REQUEST_ADDPROPERTYPOINT				= 0x0899;		// �ͻ���->������ �����Ե�
	ID_S2C_RESPONSE_ADDPROPERTYPOINT			= 0x089A;		// ������->�ͻ��� �����Ե�
	ID_C2S_REQUEST_CHANGEPKMODE					= 0x089D;		// �ͻ���->������ �л�PKģʽ
	ID_S2C_RESPONSE_CHANGEPKMODE				= 0x089E;		// ������->�ͻ��� �л�PKģʽ
	ID_C2S_REQUEST_SETTOWN						= 0x08A1;		// �ͻ���->������ �趨�س�
	ID_S2C_RESPONSE_SETTOWN						= 0x08A2;		// ������->�ͻ��� �趨�س�
	ID_C2S_REQUEST_LOOKPROPERTY					= 0x08A3;		// �ͻ���->������ �۲����װ��������
	ID_S2C_RESPONSE_LOOKPROPERTY				= 0x08A4;		// ������->�ͻ��� �۲����װ���Ļظ�
	ID_S2S_REQUEST_LOOKPROPERTY					= 0x0AA5;		// ������->·�� �۲����װ�������� 0x08A5 + 0x0200
	ID_S2S_RESPONSE_LOOKPROPERTY				= 0x0AA6;		// ������->·�� �۲����װ���Ļظ� 0x08A6 + 0x0200
	ID_S2C_FUNCRESULT_CALLBACK					= 0x0AA7;		// ������->�ͻ���  ����ʹ�ý��
	ID_C2S_REQUEST_THROWSTORITEM                = 0x08A8;		// �ͻ���->������  �ӵ��ֿ���Ʒ������
	ID_C2S_RESPONSE_THROWSTORITEM               = 0x08A9;		// ������->�ͻ���  �ӵ��ֿ���Ʒ�Ļ�Ӧ
	ID_C2S_NOTIFY_ITEMHASBINDED                 = 0x08AA;		// ������->�ͻ���  ��Ʒ�Ѿ����󶨵�֪ͨ	
	ID_S2C_RESPONSE_BUYBACK						= 0x08AB;		// ������->�ͻ��� �ع�������Ϣ
	ID_S2C_RESPONSE_SELLITEM					= 0x08AC;		// ������->�ͻ��� �����۳��ظ�
	ID_S2C_NOTIFY_STORAGEITEM					= 0x08AD;		// ������->�ͻ��� ���ͻ��˷��Ͳֿ���Ʒ��Ϣ
	ID_C2S_REQUEST_TASKCOLLECT					= 0x08AE;		// �ͻ���->������ ����ɼ�������Ʒ
	ID_C2S_REQUEST_CHANGEHELPSTATUS				= 0x08AF;		// �ͻ���->������ ����ı����״̬	
	ID_C2S_REQUEST_CLICKBINDSERVICE				= 0x08B0;		// �ͻ���->������ ��npc�󶨷�����������
	ID_S2C_RESPONSE_CLICKBINDSERVICE		    = 0x08B1;		// ������->�ͻ��� ��npc�󶨷������Ļ�Ӧ
	ID_C2S_REQUEST_ADDEQTFORRESUMEBIND			= 0x08B2;		// �ͻ���->������ ����ȡ������ֶ��󶨵���Ʒ������
	ID_S2C_RESPONSE_ADDEQTFORRESUMEBIND  		= 0x08B3;		// ������->�ͻ��� ����ȡ������ֶ��󶨵���Ʒ�Ļ�Ӧ
	ID_C2S_REQUEST_TAKEEQTFORRUMEBIND			= 0x08B4;		// �ͻ���->������ ������Ҫȡ������ֶ��󶨵���Ʒ������
	ID_S2C_RESPONSE_TAKEEQTFORRUMEBIND			= 0x08B5;		// ������->�ͻ��� ������Ҫȡ������ֶ��󶨵���Ʒ�Ļ�Ӧ
	ID_C2S_REQUEST_RESUMEBIND					= 0x08B6;		// �ͻ���->������ �ظ���Ʒ���ֶ��󶨵�����
	ID_S2C_RESPONSE_RESUMEBIND					= 0x08B7;		// ������->�ͻ��� �ظ���Ʒ���ֶ��󶨵Ļ�Ӧ
	ID_C2S_REQUEST_OBTAINDIPLOIDTIME			= 0x08B8;		// �ͻ���->������ ��ȡ˫��ʱ������
	ID_S2C_NOTIFY_CHANGEHONOR					= 0x08B9;		// ������->�ͻ��� ��ҹ�ѫ�ı�
	ID_C2S_REQUEST_HONORTOEXP					= 0x08BA;		// �ͻ���->������ ��ҹ�ѫ������
	ID_S2C_NOTIFY_SERVERREFRESH					= 0x08BB;		// ������->�ͻ��� ������ˢ������
	ID_C2S_REQUEST_QUERYREMAINTIME				= 0x08BC;		// �ͻ���->������ ��ѯʣ�����˫ʱ��
	ID_S2C_RESPONSE_REMAINTIMENOTICE			= 0x08BD;		// ������->�ͻ��� ֪ͨʣ����˫ʱ��
	ID_S2C_RESPONSE_BINDMONEYNOTICE				= 0x08CE;		// ������->�ͻ��� ֪ͨ�󶨽�Ǯ�ı�
	ID_C2S_REQUEST_USECONTINUEDSKILL			= 0x08C0;		// �ͻ���->������ ʹ�ó������ܵ�����
	ID_C2S_REQUEST_CLICKREDSTONDE				= 0x08CF;		// �ͻ���->������ ʹ���ڵ�������
	ID_S2C_RESPONSE_CLICKREDSTONDE				= 0x08D0;		// ������->�ͻ��� ʹ���ڵ��Ļ�Ӧ
	ID_S2C_NOTIFY_STOPRENDSTONETIMEER			= 0x08D1;		// ������->�ͻ��� ֹͣʹ���ڵ�
	ID_C2S_NOTIFY_REDSTONETIMEREND				= 0x08D2;		// �ͻ���->������ �ڵ������������Ϣ
	ID_S2C_NOTIFY_EXPMAGICEND					= 0x08D3;		// ������->�ͻ��� ��������
	ID_C2S_REQUEST_FREEZEDIPLOID				= 0x08D4;		// �ͻ���->������ ����(�ⶳ)˫��ʱ��
	ID_S2C_RESPONSE_FREEZEDIPLOID				= 0x08D5;		// ������->�ͻ��� ����(�ⶳ)˫��ʱ��
	ID_S2C_RESPONSE_OBTAINDIPLOID				= 0x08D6;		// ������->�ͻ��� ��Ӧ��˫����
	ID_S2C_NOTIFY_CHANGEREDSTONESTATUS			= 0x08D7;		// ������->�ͻ��� �ı���ҵ�����״̬
	ID_C2S_REQUEST_CLICKWELFARE					= 0x08D8;		// �ͻ���->������ ���npcÿ���ʴ���������
	ID_S2C_RESPONSE_CLICKWELFARE				= 0x08D9;		// ������->�ͻ��� ���npcÿ���ʴ����Ļ�Ӧ		
	ID_C2S_CHANGE_CAMP_REQUEST					= 0x08DA;		// client -> server change player camp request	
	ID_S2C_CHANGE_CAMP_RESPONSE					= 0x08DB;		// server -> client player change camp response
	ID_S2C_NOTIFY_INSERTEQUIP					= 0x08DC;		// ������->�ͻ��� ������װ��
	ID_C2S_REQUEST_OPEN_SERVICE					= 0x08E0;		// �ͻ���->������ �򿪷�������
	ID_S2C_RESPONSE_OPEN_SERVICE				= 0x08E1;		// ������->�ͻ��� �򿪷���ظ�
	ID_S2C_NOTIFY_REFRESHPROPERTY				= 0x08E2;		// ������->�ͻ��� ˢ������֪ͨ
	ID_S2C_NOTIFY_CHANGEPKTYPE					= 0x08E3;		// ������->�ͻ��� �ı�PK����֪ͨ
	ID_S2C_NOTIFY_REDSTONESTATRED				= 0x08E4;		// ������->�ͻ��� �ڵ��Ѿ����ɹ�����
	ID_C2S_REQUEST_ACTIVEREMOVEBUFF				= 0x08E5;		// �ͻ���->������ �ֶ�ɾ��BUFF������
	ID_S2C_NOTIFY_BEGINREDSTONEMAGIC			= 0x08E6;		// ������->�ͻ��� �ڵ���������״̬
	ID_S2C_NOTIFY_CHANGEENTITYPKTYPE			= 0x08E7;		// ������->�ͻ��� �ı�ʵ��PK����
	ID_S2C_NOTIFY_BRUSHOGRE						= 0x08E8;		// ˢ��֪ͨ(�ر�ͼ)	
	
	ID_C2S_REQUEST_SETPASSWORD					= 0x08E9;		// �������������
	ID_S2C_RESPONSE_SETPASSWORD					= 0x08EA;		// ��������Ļ�Ӧ
	ID_C2S_REQUEST_CHECKPASSWORD				= 0x08EB;		// ������������
	ID_S2C_RESPONSE_CHECKPASSWORD				= 0x08EC;		// �������Ļ�Ӧ
	ID_C2S_REQUEST_MODIFYPASSWORD				= 0x08ED;		// �޸����������
	ID_S2C_RESPONSE_MODIFYPASSWORD				= 0x08EE;		// �޸�����Ļ�Ӧ��Ϣ
	ID_C2S_NOTIFY_SETPASSWORDOPTION				= 0x08EF;		// ��������ѡ��	

	ID_C2S_REQUEST_CLICKSYMBOL					= 0x08F0;		// �򿪴��ͷ��Ĵ��ͱ�����
	ID_S2C_RESPONSE_CLICKSYMBOL					= 0x08F1;		// response

	ID_C2S_REQUEST_ADDSLOT						= 0x08F6;		// �ͻ���->������ ���Ӱ�������
	ID_S2C_RESPONSE_ADDSLOT						= 0x08F7;		// ������->�ͻ��� ���Ӱ��ۻ�Ӧ
	ID_C2S_REQUEST_REMOVEJEWEL					= 0x08F8;		// �ͻ���->������ ժ����ʯ����
	ID_S2C_RESPONSE_REMOVEJEWEL					= 0x08F9;		// ������->�ͻ��� ժ����ʯ��Ӧ
	ID_C2S_REQUEST_JUDGE						= 0x08FA;		// �ͻ���->������ ����װ������
	ID_S2C_RESPONSE_JUDGE						= 0x08FB;		// ������->�ͻ��� ����װ����Ӧ
	ID_C2S_REQUEST_PUSHADDSLOT					= 0x08FC;		// �ͻ���->������ ���Ӱ��۷�������
	ID_S2C_RESPONSE_PUSHADDSLOT					= 0x08FD;		// ������->�ͻ��� ���Ӱ��۷����Ӧ
	ID_C2S_REQUEST_POPADDSLOT					= 0x08FE;		// �ͻ���->������ ���Ӱ����ó�����
	ID_S2C_RESPONSE_POPADDSLOT					= 0x08FF;		// ������->�ͻ��� ���Ӱ����ó���Ӧ
	ID_C2S_REQUEST_PUSHREMOVEJEWEL				= 0x0900;		// �ͻ���->������ ժ����ʯ��������
	ID_S2C_RESPONSE_PUSHREMOVEJEWEL				= 0x0901;		// ������->�ͻ��� ժ����ʯ�����Ӧ
	ID_C2S_REQUEST_POPREMOVEJEWEL				= 0x0902;		// �ͻ���->������ ժ����ʯ�ó�����
	ID_S2C_RESPONSE_POPREMOVEJEWEL				= 0x0903;		// ������->�ͻ��� ժ����ʯ�ó���Ӧ
	ID_C2S_REQUEST_PUSHJUDGE					= 0x0904;		// �ͻ���->������ ����װ����������
	ID_S2C_RESPONSE_PUSHJUDGE					= 0x0905;		// ������->�ͻ��� ����װ�������Ӧ
	ID_C2S_REQUEST_POPJUDGE						= 0x0906;		// �ͻ���->������ ����װ���ó�����
	ID_S2C_RESPONSE_POPJUDGE					= 0x0907;		// ������->�ͻ��� ����װ���ó���Ӧ
    
    ID_C2S_REQUEST_STORMONEY					= 0x0908;		// �ͻ���->������ �洢��Ǯ��������Ϣ
    ID_S2C_RESPONSE_STORMONEY					= 0x0909;		// ������->�ͻ��� �洢��Ǯ����Ϣ��Ӧ
    
    ID_C2S_REQUEST_TAKESTORMONEY				= 0x090A;		// �ͻ���->������ �Ӳֿ�ȡ����Ǯ����Ϣ����
    ID_S2C_RESPONSE_TAKESTORMONEY				= 0x090B;		// ������->�ͻ��� �ӿͻ���ȡ����Ǯ����Ϣ��Ӧ            
    
	ID_C2S_REQUEST_ADDKITBAG				= 0x090C;		// �ͻ���->������ ���ñ������ֿ��е�������Ϣ
	ID_S2C_RESPONSE_ADDKITBAG				= 0x090D;		// ������->�ͻ��� ���ñ������ֿ��еĻ�Ӧ��Ϣ
	
	ID_C2S_REQUEST_OPENKITBAG				= 0x090E;		// �ͻ���->������ �򿪲ֿⱳ����������Ϣ	
	ID_S2C_RESPONSE_OPENKITBAG				= 0x090F;		// ������->�ͻ��� �򿪲ֿⱳ���Ļ�Ӧ��Ϣ
	
	ID_C2S_REQUEST_MOVEKITBAG					= 0x0910;		// �ͻ���->������ �ƶ���������Ϣ����
	ID_S2C_RESPONSE_MOVEKITBAG					= 0x0911;		// ������->�ͻ��� �ƶ���������Ϣ��Ӧ

	ID_C2S_REQUEST_PUSHCHANGE					= 0x0912;		// �ͻ���->������ ת�����Է�������
	ID_S2C_RESPONSE_PUSHCHANGE					= 0x0913;		// ������->�ͻ��� ת�����Է����Ӧ
	ID_C2S_REQUEST_POPCHANGE					= 0x0914;		// �ͻ���->������ ת�������ó�����
	ID_S2C_RESPONSE_POPCHANGE					= 0x0915;		// ������->�ͻ��� ת�������ó���Ӧ
	ID_C2S_REQUEST_CHANGE						= 0x0916;		// �ͻ���->������ ת����������
	ID_S2C_RESPONSE_CHANGE						= 0x0917;		// ������->�ͻ��� ת�����Ի�Ӧ
	ID_C2S_REQUEST_PUSHJEWCOM					= 0x0918;		// �ͻ���->������ ��ʯ�ϳɷ�������
	ID_S2C_RESPONSE_PUSHJEWCOM					= 0x0919;		// ������->�ͻ��� ��ʯ�ϳɷ����Ӧ
	ID_C2S_REQUEST_POPJEWCOM					= 0x091A;		// �ͻ���->������ ��ʯ�ϳ��ó�����
	ID_S2C_RESPONSE_POPJEWCOM					= 0x091B;		// ������->�ͻ��� ��ʯ�ϳ��ó���Ӧ
	ID_C2S_REQUEST_JEWCOM						= 0x091C;		// �ͻ���->������ ��ʯ�ϳ�����
	ID_S2C_RESPONSE_JEWCOM						= 0x091D;		// ������->�ͻ��� ��ʯ�ϳɻ�Ӧ

    ID_C2S_REQUEST_LISTACTIVITYMENU             = 0x091E;		// �ͻ���->������ ����NPC��ȡ��˵�����
	ID_S2C_RESPONSE_LISTACTIVITYMENU            = 0x091F;		// ������->�ͻ��� ����NPC��ȡ�Ĳ˵��б�
    ID_C2S_REQUEST_LISTACTIVITYITEM             = 0x0920;		// �ͻ���->������ ���������Ʒ�б�����
    ID_S2C_RESPONSE_LISTACTIVITYITEM            = 0x0921;		// ������->�ͻ��� ���������Ʒ�б�Ӧ��
    ID_C2S_REQUEST_MINUSACTIVITYITEM            = 0x0922;		// �ͻ���->������ ��ȡ���Ʒ����         


	ID_C2S_REQUEST_INTERRUPTSKILL				= 0x0923;		// �ͻ���->������ �����ϼ�������
	ID_S2C_NOTIFY_INTERRUPTSKILL				= 0x0924;		// ������->�ͻ��� ֪ͨ��ϼ���
	ID_S2C_NOTIFY_USECONTINUESKILL				= 0x0925;		// ������->�ͻ��� ֪ͨʹ�ó����Լ���
	ID_C2S_REQUEST_MULTICOM						= 0x0926;		// �ͻ���->������ ���Ӻϳ�����
	ID_S2C_RESPONSE_MULTICOM					= 0x0927;		// ������->�ͻ��� ���Ӻϳɻ�Ӧ

	ID_S2C_NOTIFY_MODIFYPKVALUE					= 0x0928;		// ������->�ͻ��� ֪ͨ�ͻ��˸ı�PKֵ(�����ı䡢ֱ������)
	ID_S2C_NOTIFY_YELLOWSTATE					= 0x0929;		// ������->�ͻ��� ����״̬֪ͨ

	ID_S2C_NOTIFY_EVENT							= 0x092A;		// ������->�ͻ��� �����¼�֪ͨ
	ID_S2C_NOTIFY_ACTIVECARD					= 0x092B;		// ������->�ͻ��� ���Ƭ֪ͨ
	ID_C2S_REQUEST_PUSHCARD						= 0x092C;		// �ͻ���->������ ���뿨Ƭ����
	ID_S2C_RESPONSE_PUSHCARD					= 0x092D;		// ������->�ͻ��� ���뿨Ƭ��Ӧ

	ID_S2C_NOTIYFY_TALENTCHANGE					= 0x092E;		// ������->�ͻ��� ��Ϊֵ�컯��ı�֪ͨ
	ID_C2S_REQUEST_CLICKTALENTPOINT				= 0x092F;		// �ͻ���->������ ����컯������
	ID_S2C_RESPONSE_CLICKTALENTPOINT			= 0x0930;		// ������->�ͻ��� ����컯���Ӧ
	ID_C2S_REQUEST_INCREASESTAGE				= 0x0931;		// �ͻ���->������ �컯��������
	ID_S2C_RESPONSE_INCREASESTAGE				= 0x0932;		// ������->�ͻ��� �컯���׻�Ӧ
	ID_S2C_NOTICE_UPDATETITLE					= 0x0933;		// ������->�ͻ��� ���³ƺ�
	ID_C2S_REQUEST_SELECTTITLE					= 0x0934;		// �ͻ���->������ ѡ��ƺ�
	ID_S2C_NOTICE_UPDATECURRENTTITLE			= 0x0935;		// ������->�ͻ��� ������ǰ�ƺ�

	ID_S2C_NOTICE_ACTIVITYDIPLOID				= 0x0936;		// ������->�ͻ��� �˫��֪ͨ
	
	ID_C2S_REQUEST_INITIALLIFESKILL				= 0x0937;		// �ͻ���->������ ��������ŵ�����
	ID_S2C_RESPONSE_INITIALLIFESKILL			= 0x0938;		// ������->�ͻ��� ��������ŵĻ�Ӧ
	
	ID_C2S_REQUEST_LEVELUPLIFESKILL				= 0x0939;		// �ͻ���->������ ����ܽ��׵�����
	ID_S2C_RESPONSE_LEVELUPLIFESKILL			= 0x093A;		// ������->�ͻ��� ����ܽ��׵Ļ�Ӧ
	
	ID_C2S_REQUEST_STUDYCOMPOSE					= 0x093B;		// �ͻ���->������ ѧϰ�µļ����䷽������
	ID_S2C_RESPONSE_STUDYCOMPOSE				= 0x093C;		// ������->�ͻ��� ѧϰ�µļ����䷽�Ļ�Ӧ��Ϣ
	
	ID_C2S_REQUEST_SETMAGICSTONE				= 0x093D;		// �ͻ���->������ ��ħ��������Ϣ
	ID_S2C_RESPONSE_SETMAGICSTONE				= 0x093E;		// ������->�ͻ��� ��ħ����Ϣ��Ӧ
	
	ID_C2S_REQUEST_FORGETLIFESKILL				= 0x093F;		// �ͻ���->������ �������������
	ID_S2C_RESPONSE_FORGETLIFESKILL				= 0x0940;		// ������->�ͻ��� ��������ܻ�Ӧ
	
	ID_C2S_REQUEST_DECOMPOUNDEQUIP				= 0x0941;		// �ͻ���->������ �ֽ�װ��������
	ID_S2C_RESPONSE_DECOMPOUNDEQUIP				= 0x0942;		// ������->�ͻ��� �ֽ�װ���Ļ�Ӧ��Ϣ	
	
	ID_C2S_REQUEST_ADDMATERIAL					= 0x0943;		// �ͻ���->������ ���ò��ϵ���Ϣ����
	ID_S2C_RESPONSE_ADDMATERIAL					= 0x0944;		// ������->�ͻ��� ���ò��ϵ���Ϣ��Ӧ	
	
	ID_C2S_REQUEST_TAKEMATERIAL					= 0x0945;		// �ͻ���->������ ȡ�²��ϵ���Ϣ����
	ID_S2C_RESPONSE_TAKEMATERIAL				= 0x0946;		// ������->�ͻ��� ȡ�²��ϵ���Ϣ��Ӧ
	
	ID_S2C_NOTIFY_LIFESKILLATTRIBUTE			= 0x0947;		// ������->�ͻ��� ��������Ըı��֪ͨ

	ID_C2S_REQUEST_ADDPOTENTIAL					= 0x0948;		// �ͻ���->������ �����ӵ�����
	ID_S2C_RESPONSE_ADDPOTENTIAL				= 0x0949;		// ������->�ͻ��� �����ӵ��Ӧ

	ID_C2S_REQUEST_CHANGEEXPSCALE				= 0x094A;		// �ͻ���->������ ���侭��ٷֱ� ����
	ID_S2C_RESPONSE_CHANGEEXPSCALE				= 0x094B;		// ������->�ͻ��� ���侭��ٷֱ� ��Ӧ

	ID_S2C_NOTIFY_REFRESHVALUE					= 0x094C;		// ������->�ͻ��� ˢ�·�����ֵ ֪ͨ

	ID_S2C_NOTIFY_ACTIVESKILLBOX				= 0x094D;		// ������->�ͻ��� ����ܿ� ֪ͨ
	ID_S2C_NOTIFY_INSERTSKILL					= 0x094E;		// ������->�ͻ��� �����¼��� ֪ͨ
	ID_C2S_REQUEST_MWADDSKILLPOINTS				= 0x094F;		// �ͻ���->������ �������ܼӵ� ����
	ID_S2C_RESPONSE_MWADDSKILLPOINTS			= 0x0950;		// ������->�ͻ��� �������ܼӵ� ��Ӧ
	ID_C2S_REQUEST_MWJUDGESKILL					= 0x0951;		// �ͻ���->������ �������ܼ��� ����

	ID_C2S_REQUEST_MWLOCKBAG					= 0x0952;		// �ͻ���->������ ���Ϸ��� ����
	ID_S2C_RESPONSE_MWLOCKBAG					= 0x0953;		// ������->�ͻ��� ���Ϸ��� ��Ӧ
	ID_C2S_REQUEST_MWTAKEOFF					= 0x0954;		// �ͻ���->������ ȡ�·��� ����

	ID_C2S_REQUEST_JUDGEPROPERTY				= 0x0955;		// �ͻ���->������ ���Լ��� ����
	ID_S2C_RESPONSE_JUDGEPROPERTY				= 0x0956;		// ������->�ͻ��� ���Լ��� ��Ӧ

	ID_C2S_REQUEST_USESKILLBOOK					= 0x0957;		// �ͻ���->������ ʹ�ü�����ϳɼ��� ����

	ID_C2S_REQUEST_MULTIBUFF					= 0x0958;		// �ͻ���->������ ���buff����

	ID_S2C_CHANGE_CAMP							= 0x0959;
	ID_C2S_CHANGEPKDROP							= 0x095A;	
	
	ID_C2S_REQUEST_GETEUIPEXCHANGELIST			= 0x095B;		// ��ȡװ���һ��б������
	ID_S2C_RESPONSE_GETEUIPEXCHANGELIST			= 0x095C;		// ��ȡװ���һ��б�Ļ�Ӧ

	ID_C2S_REQUEST_AUTOHOOK						= 0x095D;		// �Զ��һ�
	ID_S2C_RESPONSE_AUTOHOOK					= 0x095E;

	ID_C2S_REQUEST_BUYPHYSIC					= 0x095F;		// �һ���ҩ
	ID_S2C_RESPONSE_BUYPHYSIC					= 0x0960;

	ID_C2S_REQUEST_PUSHMULTI					= 0x0961;		// �ͻ���->������ ���Ӻϳɷ�������
	ID_S2C_RESPONSE_PUSHMULTI					= 0x0962;		// ������->�ͻ��� ���Ӻϳɷ����Ӧ
	ID_C2S_REQUEST_POPMULTI						= 0x0963;		// �ͻ���->������ ���Ӻϳ��ó�����
	ID_S2C_RESPONSE_POPMULTI					= 0x0964;		// ������->�ͻ��� ���Ӻϳ��ó���Ӧ
	
	ID_C2S_REQUEST_ADDDECOMPOUNDEQUIP			= 0x0965;		// �ͻ���->������ ���ô��ֽ�װ������Ϣ����
	ID_S2C_RESPONSE_ADDDECOMPOUNDEQUIP			= 0x0966;		// ������->�ͻ��� ���ô��ֽ�װ������Ϣ��Ӧ
	
	ID_C2S_REQUEST_TAKERDECOMPOUNDEQUIP			= 0x0967;		// �ͻ���->������ ���´��ֽ�װ������Ϣ����
	ID_S2C_RESPONSE_TAKERDECOMPOUNDEQUIP		= 0x0968;		// ������->�ͻ��� ���´��ֽ�װ������Ϣ��Ӧ
	
	ID_S2C_NOTIFY_PLAYERFCMSTATUS				= 0x0969;		// ������ -> �ͻ��� ֪ͨ�ͻ�����ҵķ�����״̬

	ID_C2S_MAGICWEAPONCLEARPOINTREQUEST			= 0x096A;		// �ͻ���->������ ����ϴ������
	ID_S2C_MAGICWEAPONCLEARPOINTRESPONSE		= 0x096B;		// ������->�ͻ��� ����ϴ�������Ӧ

	ID_C2S_MAGICWEAPONCLEARPOINT_ADDMWREQUEST	= 0x096C;		// �ͻ���->������ ����ϴ��ŷ�������
	ID_S2C_MAGICWEAPONCLEARPOINT_ADDMWRESPONSE	= 0x096D;		// ������->�ͻ��� ����ϴ��ŷ�����Ӧ

	ID_C2S_REQUEST_ADDWIZARDPOINT				= 0x096E;		// �ͻ���->������ ���ӲŻ��ȼ�����
	ID_S2C_RESPONSE_ADDWIZARDPOINT				= 0x096F;		// ������->�ͻ��� ���ӲŻ��ȼ���Ӧ

	ID_C2S_REQUEST_HONORTOWIZARD				= 0x0970;		// �ͻ���->������ ��ѫ���Ż�����

	ID_C2S_REQUEST_GETTREND						= 0x0971;		// �ͻ���->������ ��������
	ID_S2C_RESPONSE_GETTREND					= 0x0972;		// ������->�ͻ��� ������Ӧ

	ID_S2C_NOTIFY_RUNTIMEPARAM					= 0x0973;		// ������->�ͻ��� ����ʱ����

	ID_C2S_GETHELPDATAREQUEST					= 0x0974;		// �ͻ���->������ �ͻ��������������
	ID_S2C_GETHELPDATARESPONSE					= 0x0975;		// ������->�ͻ��� �ͻ�������������� ��Ӧ	

	ID_S2C_NOTIFY_PRISONTIME					= 0x0976;		// ������->�ͻ��� ��������ʱ�䵹��ʱ֪ͨ
	ID_S2C_NOTIFY_PICKITEM						= 0x0977;
	
	ID_C2S_REQUEST_TAKEKITBAG					= 0x0978;		// �ͻ���->������   ���±�������Ϣ����
	ID_S2C_RESPONSE_TAKEKITBAG					= 0x0979;		// ������->�ͻ���	���±�������Ϣ��Ӧ	
	

	ID_C2S_REQUEST_GETTELELIST					= 0x097A;		// �ͻ���->������   ��ȡ���������б�����
	ID_S2C_RESPONSE_GETTELELIST					= 0x097B;		// ������->�ͻ���	��ȡ���������б��Ӧ

	ID_C2S_REQUEST_ADDTELEPOINT					= 0x097C;		// �ͻ���->������   ��¼���͵�����
	ID_S2C_RESPONSE_ADDTELEPOINT				= 0x097D;		// ������->�ͻ���	��¼���͵��Ӧ

	ID_C2S_REQUEST_DELTELEPOINT					= 0x097E;		// �ͻ���->������   ɾ�����͵�����
	ID_S2C_RESPONSE_DELTELEPOINT				= 0x097F;		// ������->�ͻ���	ɾ�����͵��Ӧ

	ID_C2S_REQUEST_USETELEITEM					= 0x0980;		// �ͻ���->������   ʹ�ô��͵��ߴ�������

	ID_S2C_NOTIFY_VIPNOTICE						= 0x0981;		// ������->�ͻ���	VIP ֪ͨ

	ID_C2S_REQUEST_QUERY_GOLDENYB					= 0x0982;		// �ͻ���->������ ��ѯ�ʻ�Ԫ�����
	ID_S2C_RESPONSE_QUERY_GOLDENYB					= 0x0983;		// ������->�ͻ��� ֪ͨ�ͻ���δ��Ԫ�������Ŀ
	ID_C2S_REQUEST_DRAW_GOLDENYB					= 0x0984;		// �ͻ���->������ ��ȡԪ������������
	ID_S2C_RESPONSE_DRAW_GLODENYB					= 0x0985;		// ������->�ͻ��� ��ȡԪ����������Ӧ
	
	ID_S2C_NOTIFY_USEITEM							= 0x0986;		// ������->�ͻ��� �㲥���ʹ�õ������
	
	ID_C2S_REQUEST_SETPWDPROTECTTIME				= 0x0987;		// �ͻ���->������ �������밲ȫ����ʱ�������
	ID_S2C_RESPONSE_SETPWDPROTECTTIME				= 0x0988;		// ������->�ͻ��� �������밲ȫ����ʱ�����Ϣ��Ӧ	

	ID_S2C_NOTIFY_ACTIVITYCHANGED					= 0x0989;		// ������->�ͻ��� �״̬���

	ID_C2S_REQUEST_USEFLOWER						= 0x098A;		// �ͻ���->������ ʹ���ʻ�����
	ID_S2C_RESPONSE_USEFLOWER						= 0x098B;		// ������->�ͻ��� ʹ���ʻ���Ӧ	
	ID_S2C_NOTIFY_OBTAINFLOWER						= 0x098C;		// ������->�ͻ��� �����ʻ�֪ͨ

	ID_S2S_REQUEST_USEFLOWER						= 0x0B8D;		// ������->������ ʹ���ʻ����� +0x0200
	ID_S2S_RESPONSE_USEFLOWER						= 0x0B8E;		// ������->������ ʹ���ʻ���Ӧ +0x0200

	ID_S2C_RESPONSE_MINUSACTIVITYITEM				= 0x0B8F;		// ������->�ͻ��� ��ȡ���Ʒ�����Ӧ
	
	ID_C2S_REQUEST_COMMONBIND						= 0x0B90;		// ������->�ͻ��� ��ͨ�󶨵���Ϣ����
	ID_S2C_RESPONSE_COMMONBIND						= 0x0B91;		// ������->�ͻ��� ��ͨ�󶨵���Ϣ��Ӧ
	
	ID_C2S_REQUEST_REMOTEMEND						= 0x0B92;		// �ͷ��� -> ������ Զ������
	ID_S2C_RESPONSE_REMOTEMEND						= 0x0B93;		// ������ -> �ͻ��� Զ������
	
	ID_C2S_REQUEST_STARTPROGRESS					= 0x0B94;		// �ͷ��� -> ������ ��������������
	ID_S2C_RESPONSE_STARTPROGRESS					= 0x0B95;		// ������ -> �ͻ��� ���������Ļ�Ӧ

	ID_C2S_REQUEST_RESETTALENT						= 0x0B96;		// �ͷ���-> �����������컯
	ID_S2C_RESPONSE_RESETTALENT						= 0x0B97;		// ������-> �ͻ��������컯

	ID_C2S_REQUEST_GETACTVITYINFO					= 0x0B98;		// �ͷ���-> ������ ��û��Ϣ
	ID_S2C_RESPONSE_GETACTVITYINFO					= 0x0B99;		// ������-> �ͻ��� ���Ϣ ��Ӧ

	ID_C2S_REQUEST_CHANGEEQUIPPRO					= 0x0B9A;		// �ͷ���-> ������ �ı�װ������
	ID_S2C_RESPONSE_CHANGEEQUIPPRO					= 0x0B9B;		// ������-> �ͻ��� �ı�װ������
	
	ID_C2S_REQUEST_USEKITBAGNEEDLE					= 0x0B9C;		// �ͷ���->������ ʹ���廨������������Ϣ����
	ID_S2C_RESPONSE_USEKITBAGNEEDLE					= 0x0B9D;		// ������->�ͻ��� ʹ���廨������������Ϣ��Ӧ

	ID_C2S_REQUEST_OPENSTONE						= 0x0B9E;		// �ͻ���->������ ������ʯ����
	ID_S2C_RESPONSE_OPENSTONE						= 0x0B9F;		// ������->�ͻ��� ������ʯ��Ӧ
	
	ID_C2S_REQUEST_LOCKPASSWORD						= 0x0BA0;		// �ͻ���->������ ��ȫ����������������������
	ID_S2C_RESPONSE_LOCKPASSWORD					= 0x0BA1;		// ������->�ͻ��� ��ȫ�����������������Ļ�Ӧ��Ϣ

	ID_C2S_REQUEST_LEARNOGRESKILL					= 0x0BA2;		// �ͻ���->������ ѧϰ��ħ־��������
	ID_S2C_RESPONSE_LEARNOGRESKILL					= 0x0BA3;		// ������->�ͻ��� ѧϰ��ħ־���ܻ�Ӧ

	ID_S2C_NOTIFY_PLAYERPICKITEM					= 0x0BA4;		// ������->�ͻ��� ���ʰȡ��Ʒ֪ͨ

	ID_C2S_REQUEST_QUERYPEDAL						= 0x0BA5;		// �ͻ���->������ ��ѯ���͵�����
	ID_S2C_RESPONSE_QUERYPEDAL						= 0x0BA6;		// ������->�ͻ��� ��ѯ���͵��Ӧ

	ID_C2S_REQUEST_AUTOBUYITEM						= 0x0BA7;		// �ͻ���->������ �Զ���������
	ID_S2C_RESPONSE_AUTOBUYITEM						= 0x0BA8;		// ������->�ͻ��� �Զ������Ӧ

	ID_C2S_REQUEST_USESUMMONITEM					= 0x0BA9;		// �ͻ���->������ ʹ���ټ���Ʒ����
	ID_S2C_RESPONSE_USESUMMONITEM					= 0x0BAA;		// ������->�ͻ��� ʹ���ټ���Ʒ��Ӧ

	ID_C2S_REQUEST_SPLITEQUIP						= 0x0BAB;		// �ͻ���->������ ���װ������
	ID_S2C_RESPONSE_SPLITEQUIP						= 0x0BAC;		// ������->�ͻ��� ���װ����Ӧ

	ID_C2S_REQUEST_GETSTAR							= 0x0BAD;		// �ͻ���->������ ժ������
	ID_S2C_RESPONSE_GETSTAR							= 0x0BAE;		// ������->�ͻ��� ժ�ǻ�Ӧ

	ID_C2S_REQUEST_ADDSTAR							= 0x0BB0;		// �ͻ���->������ ��������
	ID_S2C_RESPONSE_ADDSTAR							= 0x0BB1;		// ������->�ͻ��� ���ǻ�Ӧ

	ID_S2C_NOTIFY_EQUIPOVERDUE						= 0x0BB2;		// ������->�ͻ��� װ������֪ͨ
	ID_S2C_NOTIFY_STARTTIMER						= 0x0BB3;		// ������->�ͻ��� ��ʼ���ڼ�ʱ֪ͨ

	ID_C2S_REQUEST_ADDEXTRA							= 0x0BB4;		// �ͻ���->������ ����������
	ID_S2C_RESPONSE_ADDEXTRA						= 0x0BB5;		// ������->�ͻ��� �����̻�Ӧ

	ID_S2C_NOTIFY_CHANGEOWNCAMP						= 0x0BB6;		// ������->�ͻ��� �ı�������Ӫ֪ͨ

	ID_C2S_REQUEST_WAROPERATE						= 0x0BB7;		// �ͻ���->������ ��ս��������
	ID_S2C_RESPONSE_WAROPERATE						= 0x0BB8;		// ������->�ͻ��� ��ս������Ӧ
	
	ID_C2S_REQUEST_CANUSEAUTOCOLLECTITEM			= 0x0BB9;		// �ͻ���->������ �Ƿ����ʹ�òɼ����ߵ�����
	ID_S2C_RESPONSE_CANUSEAUTOCOLLECTITEM			= 0x0BBA;		// ������->�ͻ��� �Ƿ����ʹ�òɼ����ߵ���Ϣ��Ӧ
	
	ID_C2S_REQUEST_COLLECTBYAUTOITEM				= 0x0BBB;		// �ͻ���->������ ʹ���Զ��ɼ����߲ɼ�����Ϣ����
	ID_S2C_RESPONSE_COLLECTBYAUTOITEM				= 0x0BBC;		// ������->�ͻ��� ʹ���Զ��ɼ����߲ɼ�����Ϣ��Ӧ

	ID_C2S_REQUEST_LEARNFANGCUNSKILL				= 0x0BBD;		// �ͻ���->������   ѧϰ����ɽ��������
	ID_S2C_RESPONSE_LEARNFANGCUNSKILL				= 0x0BBE;		// ������->�ͻ���	ѧϰ����ɽ���ܻ�Ӧ
	ID_S2C_NOTIFY_PLAYERTRANSFORM					= 0x0BC0;		// ������->�ͻ���	��Ҹ��Ʊ���֪ͨ

	ID_C2S_REQUEST_HONORTOITEM						= 0x0BC1;		// �ͻ���->������ ��������Ʒ����
	ID_S2C_NOTIFY_USEBLACKPILLS						= 0x0BC2;		// ������->�ͻ��� ʹ�úڹ����֪ͨ
	
	ID_S2C_NOTIFY_EXPCONTAINER						= 0x0BC3;		// ������->�ͻ��� �������鵤����ı��֪ͨ
	ID_S2C_NOTICE_YUANBAOUPDATE						= 0x0BC4;		// ������->�ͻ��� Ԫ���仯֪ͨ
	ID_S2C_NOTICE_UPGANDJEW							= 0x0BC5;		// ������->�ͻ��� װ�������ͱ�ʯ�ϳ�֪ͨ
	ID_C2S_REQUEST_JEWELCARVE						= 0x0BC6;		// �ͻ���->������ ��ʯ��������
	ID_S2C_RESPONSE_JEWELCARVE						= 0x0BC7;		// ������->�ͻ��� ��ʯ������Ӧ

	ID_C2S_REQUEST_QUERYBOSS						= 0x0BC8;		// �ͻ���->������ ��ѯBOSS����
	ID_S2C_RESPONSE_QUERYBOSS						= 0x0BC9;		// ������->�ͻ��� ��ѯBOSS��Ӧ

	//���ĵڶ���
	ID_C2S_REQUEST_CHANGERUNE						= 0x0BCA;	    // �ͻ���->�����  ����ת������
	ID_S2C_RESPONSE_CHANGERUNE						= 0x0BCB;       // �����->�ͻ���  ����ת���ظ�
	ID_C2S_REQUEST_RUNECOM							= 0x0BCC;		// �ͻ���->�����  ������������
	ID_S2C_RESPONSE_RUNECOM							= 0x0BCD;		// �����->�ͻ���  ���������ظ�
	
	// ������
	ID_C2S_REQUEST_STARTDIGITALFIREWORKS			= 0x0BCE;		// �ͻ���->�����  �������񻨵���Ϣ����
	ID_S2C_RESPONSE_STARTDIGITALFIREWORKS			= 0x0BCF;		// �����->�ͻ���  �������񻨵���Ϣ��Ӧ
	ID_S2C_NOTIFY_STARTDIGITALFIREWORKS				= 0x0BD0;		// �����->�ͻ���  �������񻨵���Ϣ֪ͨ

    // ����û�ʱװ��ʾ״̬
    ID_C2S_REQUEST_PLAYERCHANGEFASHIONSHOW          = 0x0BD1;        // �ͻ���->������ ������ʱװ��ʾ״̬����
    ID_S2C_RESPONSE_PLAYERCHANGEFASHIONSHOW         = 0x0BD2;        // ������->�ͻ��� ������ʱװ��ʾ״̬��Ӧ
    ID_S2C_NOTIFY_PLAYERCHANGEFASHIONSHOW           = 0x0BD3;        // �����->�ͻ��� ������ʱװ��ʾ״̬֪ͨ

    // ����û�װ���Ƿ�ɱ��쿴
    ID_C2S_REQUEST_PLAYERCHANGEEQUIPSHOW            = 0x0BD4;        // �ͻ���->������ ������װ���쿴״̬����
    ID_S2C_RESPONSE_PLAYERCHANGEEQUIPTSHOW          = 0x0BD5;        // ������->�ͻ��� ������װ���쿴״̬��Ӧ

	// �ֽⷨ����Ϣ
	ID_C2S_REQUEST_DECOMPOSEMW						= 0x0BD6;		// �ֽⷨ������
	ID_S2C_RESPONSE_DECOMPOSEMW						= 0x0BD7;		// �ֽⷨ����Ӧ

	// ����ӡ����Ϣ
	ID_C2S_REQUEST_MWQLPNT							= 0x0BD8;		
	ID_S2C_RESPONSE_MWQLPNT							= 0x0BD9;		

	// ����������Ϣ
	ID_C2S_REQUEST_QUICKUP							= 0x0BDA;		
	ID_S2C_RESPONSE_QUICKUP							= 0x0BDB;		

	// ����ϳ���Ϣ
	ID_C2S_REQUEST_QLCOMPOSE						= 0x0BDC;		
	ID_S2C_RESPONSE_QLCOMPOSE						= 0x0BDD;		

	// ������þ���֪ͨ
	ID_S2C_NOTIFY_MWOBTAINEXP						= 0x0BDE;		

	ID_C2S_QUERY_AROUND_PLAYER						= 0x0BDF;
	ID_S2C_QUERY_AROUND_PLAYER						= 0x0BE0;
	// ������ҵĸ�������
	ID_S2C_PLAYER_REPETION_DATA						= 0x0BE1;
	// ͬ����ҵ�����
	ID_S2C_NOTIFY_SYNCFAME							= 0x0BE2;

	// ��������
	ID_C2S_REQUEST_SPIRIT_OPEN						= 0x0BE3;
	// ������Ӧ
	ID_S2C_RESPONSE_SPIRIT_OPEN						= 0x0BE4;
	// ��������
	ID_C2S_REQUEST_SPIRIT_CASTING					= 0x0BE5;
	// ������Ӧ
	ID_S2C_RESPONSE_SPIRIT_CASTING					= 0x0BE6;
	// ��������
	ID_C2S_REQUEST_SPIRIT_UPGRADE					= 0x0BE7;
	// ������Ӧ
	ID_S2C_RESPONSE_SPIRIT_UPGRADE					= 0x0BE8;
	// ��������
	ID_C2S_REQUEST_SPIRIT_DOWNGRADE					= 0x0BE9;
	// ������Ӧ
	ID_S2C_RESPONSE_SPIRIT_DOWNGRADE				= 0x0BEA;
	// ������Ϣ����
	ID_C2S_REQUEST_SPIRIT_INFO						= 0x0BEB;
	// ������Ϣ֪ͨ
	ID_S2C_NOTIFY_SPIRIT_INFO						= 0x0BEC;

	// ���������ͻ���   ֪ͨ��������
	ID_S2C_NOTIFY_BAGGAGELOCKEN						= 0x0BED;

	// �ͻ��˵�������   ������������
	ID_C2S_NOTIFY_BAGGAGELOCKEN						= 0x0BEF;
};

// *************************************************************************** //
// CMessagePlayerChangeFashionShowRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessagePlayerChangeFashionShowRequest
{
    optional uint32 PlayerId           = 1; // ��ұ��
    optional uint32 FashionShowState   = 2; // ���ʱװ״̬�� 0Ϊ��ʾʱװ��1Ϊ����ʾʱװ
};

// *************************************************************************** //
// CMessagePlayerChangeFashionShowResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessagePlayerChangeFashionShowResponse
{
    optional uint32 Result              = 1; // ���½����0Ϊ�ɹ�������Ϊʧ��
    optional uint32 PlayerId            = 2; // ��ұ��
    optional uint32 FashionShowState    = 3; // ���ʱװ״̬�� 0Ϊ��ʾʱװ��1Ϊ����ʾʱװ
};

// *************************************************************************** //
// CMessagePlayerChangeFashionNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessagePlayerChangeFashionNotice
{
    optional uint32 PlayerId           = 1; // ��ұ��
    optional uint32 FashionShowState   = 2; // ���ʱװ״̬��0Ϊ��ʾʱװ��1Ϊ����ʾʱװ
};

// *************************************************************************** //
// CMessagePlayerChangeEquipShowRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessagePlayerChangeEquipShowRequest
{
    optional uint32 PlayerId            = 1; // ��ұ��
    optional uint32 EquipShowState      = 2; // ���װ����ʾ״̬��0Ϊ����쿴װ����1Ϊ������쿴װ��
};

// *************************************************************************** //
// CMessagePlayerChangeEquipShowResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessagePlayerChangeEquipShowResponse
{
    optional uint32 Result              = 1; // ���½����0Ϊ�ɹ�������Ϊʧ��
    optional uint32 PlayerId            = 2; // ��ұ��
    optional uint32 EquipShowState      = 3; // ��ҵ�ǰװ����ʾ״̬�� 0Ϊ������쿴װ����1Ϊ����쿴װ��
};




// *************************************************************************** //
// CMessageYourProDataNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageYourProDataNotice
{
	optional string CorpsName			 = 		1; 		// ��������	
	optional uint32 FamilyID			 = 		2; 		// ����ID
	optional uint32 MapID				 = 		3; 
	optional uint32 LineID				 = 		4; 
	optional uint32 IsFamilyHeader		 = 		5; 		// �Ƿ�����峤
	optional uint32 Sex					 = 		6; 
	optional uint32 Nationality			 = 		7; 		// ��ӪID
	optional uint32 Level				 = 		8; 
	optional uint32 AliveState			 = 		9; 
	optional uint32 MotionState			 = 		10; 
	optional uint32 MaxMP				 = 		11; 
	optional uint32 IfHasCorpsApply		 = 		12; 		// �Ƿ��м���������Ϣ1��ʾ��������ʾ�� 	
	optional string MapName				 = 		13; 
	optional uint32 CorpsID				 = 		14; 		// ����ID
	optional uint32 MaxHP				 = 		15; 
	optional string CountryName			 = 		16; 
	optional uint32 HorseTempID			 = 		17; 		// �������ģ��ID
	optional uint32 IsCorpsHeader		 = 		18; 		// �Ƿ��������1��ʾ��������ʾ��
	optional PBProperty Property		 = 		19; 		// ���Լ���
	optional uint32 EntityID			 = 		20; 
	optional uint64 Exp					 = 		21; 
	optional uint32 PkgCurrentNum		 = 		22; 		// ��ǰ�ְ�����
	optional uint32 PkgTotal			 = 		23; 		// �ְܷ�����
	optional string FamilyName			 = 		24; 		// ��������
	optional uint32 CharID				 = 		25; 
	optional uint32 HorseState			 = 		26; 		// ����״̬(0:û���� 1:������)
	optional uint32 IfHasFamilyApply	 = 		27; 		// �Ƿ���������Ϣ
	optional uint32 PosY				 = 		28; 
	optional uint32 PosX				 = 		29; 
	optional uint32 Direction			 = 		30; 
	optional uint32 Metier				 = 		31; 
	optional uint32	CampID				 =		32;			// PVPս����Ӫ��Ϣ
	optional uint32	FamilyHeaderID		 =		33;			// �Լ���������Ľ�ɫID
	optional uint32	CorpsHeaderID		 =		34;			// �Լ���������Ľ�ɫID
	optional uint32	MaxAP				 =		35;			// AP Max
	optional uint32	FamilyPost			 =		36;			// ����ְλ
	optional uint32	CorpsPost			 =		37;			// ����ְλ	
	optional uint32	FamilyMoney			 =		38;			// �����Ǯ
	optional uint32	CorpsMoney			 =		39;			// ���Ž�Ǯ
	optional uint32 ChestLevel			 = 		40; 		// ��ɫ���·��ĵȼ�
	optional uint32 WeaponLevel			 = 		41; 		// ��ɫ�ֳ������ĵȼ�
	optional uint32	WeaponJewel			 =		42;			// ������ʯ��
	optional uint32	ChestJewel			 =		43;			// ���߱�ʯ��
	optional uint32	UnionID				 =		44;
	optional string UnionName			 =		45;
	optional uint32	HeadCorpsID			 =		46;
	optional uint32 CountryID			 =		47;			// ����
	optional uint32 OfficialID			 =		48;			// ��ְ
	optional uint32 UserType			 =		49;			// �û�����(GM)
	optional PBStateList StateList		 = 		50; 		// ״̬�б�
	optional PBSkillList EquipSkill		 =		51;			// װ���ṩ�ļ���
	optional int32 Money				 =		52;			// ��Ǯ
	optional int32 BindMoney			 =		53;			// �󶨽�
	optional uint32 KingID				 =		54;			// ����ID
	optional uint32	PasswordStatus		 =		55;			// ��ȫ����״̬
	optional uint32	ProtectTime			 =		56;			// ��ȫ�����ĵ���ʱ��	
	optional uint32	ProtectTimeLength	 =		57;			// ��ȫ����ʱ���ܳ�
	optional uint32	CharmValue			 =		58;			// ����ֵ
	optional uint32	TodayLeftFlower		 =		59;			// ����ʣ��ʹ���ʻ�����
	optional string	SpouseName			 =		60;			// ��ż����
	optional uint32	CurWarHonor			 =		61;			// ��ǰս��
	optional uint32	AllWarHonor			 =		62;			// �ܼ�ս��
	optional uint32	TodayWarHonor		 =		63;			// ����ս��
	optional uint32	OffLineTime			 =		64;			// ����ת��Ϊ���������ʱ��
	optional uint32	ExpHonor			 =		65;			// �Ѷһ���������
	optional uint32	ItemHonor			 =		66;			// �Ѷһ���Ʒ����
    optional uint32 FashionShowState     =      67;         // ���ʱװ��ʾ״̬
    optional uint32 EquipShowState       =      68;         // ���װ����ʾ״̬
	optional PBRepetDataList RepeDataToClientList	 =		69;         // ��������ֵ����ͬ������Ӧ��һ����
	optional uint32	OffLineExp			=		70;			// ���߾����
};

// *************************************************************************** //
// CMessageCreatePlayerProNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CPlayerProInfo
{
	optional uint32 FamilyID		 = 		1; 		// ����ID
	optional uint32 CharID			 = 		2;        // ��ɫID
	optional string Name			 = 		3; 
	optional uint32 CreatMethod		 = 		4; 		// ���������Ұ�Ĵ�����ʽ
	optional uint32 Direction		 = 		5; 
	optional PBTeamMsg Msg			 = 		6; 
	optional uint32 CurAP			 = 		7; 		// ��ɫ��ǰ����( �ٷֱ�0-100 )
	optional int32	PKValue			 = 		8; 		// pkֵ
	optional uint32 MaxMP			 = 		9; 		// MP���ֵ
	optional uint32 HorseState		 = 		10; 		// ����״̬(0:û���� 1:������)
	optional uint32 Fashion			 = 		11; 		// ��ɫ��ʱװ��ģ��ID
	optional string FamilyName		 = 		12; 		// ��������	 
	optional uint32	HasRedStoneSta   = 		13; 		// �Ƿ����ڵ�������״̬ 1��ʾ�� 0 ��ʾû��
	optional uint32 CurMP			 = 		14; 		// ��ɫ��ǰ����( �ٷֱ�0-100 )
	optional uint32 FaceType		 = 		15; 		// ���ͷ��ID	
	optional uint32 EntityID		 = 		16; 		// ��ɫʵ��ID
	optional uint32 HorseTempID		 = 		17; 		// �������ģ��ID
	optional uint32 Metier			 = 		18; 		// ��ɫְҵ
	optional string CorpsName		 = 		19; 		// ��������
	optional uint32	Sex				 = 		20; 		// ��ɫ�Ա�
	optional uint32 Nationality		 = 		21; 		// ����ID
	optional uint32 MaxHP			 = 		22; 		// HP���ֵ
	optional uint32 TeamFlag		 = 		23; 		// ��Ҷ���״̬
	optional uint32 PosY			 = 		24; 
	optional uint32 MotionState		 = 		25; 
	optional PBStallInfo StallInfo   = 		26; 		// ��̯����
	optional uint32 Chest			 = 		27; 		// ��ɫ���·���ģ��ID
	optional uint32 AliveState		 = 		28; 
	optional PBBuffList BuffList	 = 		29; 
	optional uint32 CurHP			 = 		30; 		// ��ɫ��ǰ����( �ٷֱ�0-100 )
	optional uint32 PosX			 = 		31; 
	optional uint32 Weapon			 = 		32; 		// ��ɫ�ֳ�������ģ��ID
	optional uint32 Speed			 = 		33; 
	optional uint32	CorpsID			 = 		34; 		// ����ID
	optional PBStateList StateList	 = 		35; 		// ״̬�б�
	optional uint32 ChestLevel		 = 		36; 		// ��ɫ���·��ĵȼ�
	optional uint32 WeaponLevel		 = 		37; 		// ��ɫ�ֳ������ĵȼ�
	optional uint32	YellowStatus	 = 		38; 		// �Ƿ����
	optional uint32 Level			 = 		39; 		// ��ɫ�ȼ�
	optional uint32	CurrentTitle	 =		40;			// ��ǰ�ƺ�
	optional uint32	WeaponJewel		 =		41;			// ������ʯ��
	optional uint32	ChestJewel		 =		42;			// ���߱�ʯ��
	optional uint32	MWID			 =		43;			// ����ID
	optional uint32 CampID			 =		44;			// ��ӪID
	optional uint32	MaxAP			 =		45;			// ap max			
	optional uint32	UserType		 =		46;			// �û����� ��protype��� enUserTypeö��
	optional uint32 UnionID			 =		47;
	optional string UnionName		 =		48;
	optional uint32	CountryID		 =		49;			// ����
	optional uint32	OfficialID		 =		50;			// ��ְ
	optional uint32	VipFlag			 =		51;			// VIP ��־
	optional uint32	ProtectStatus	 =		52;			// ����״̬	
	optional string SpouseName		 =		53;			// ��ż����
	optional uint32	HydrangeaStatus	 =		54;			// ����״̬(Em_HydrangeaStatus)
	optional uint32	MarriageID		 =		55;			// ���װ����ID
    optional uint32 FashionShowState =      56;         // ���ʱװ��ʾ״̬
    optional uint32 EquipShowState   =      57;         // ���װ����ʾ״̬
	optional uint32	MWQLID			 =		58;			// ��������ID
	optional string	SwornName		 =		59;			// �������
};

message CMessageCreatePlayerProNotice
{
	repeated CPlayerProInfo PlayerList	 = 		1; 	// ���
};

// *************************************************************************** //
// CMessageCreateNpcProNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CNpcProInfo
{
	optional uint32 Speed			 = 		1; 
	optional uint32 DieEntityID		 = 		2; 	// ����ID
	optional uint32 NpcID			 = 		3; 	// NpcID;
	optional uint32 NationNality	 = 		4; 	// ��������
	optional uint32 PedalType		 = 		5; 	// ��������(PEDAL_TELEPORT����̤�� = 0, PEDAL_TRAP����̤�� = 1, PEDAL_HIEROGRAM���̤�� = 2)
	optional uint32 CurHP			 = 		6; 	// ��ɫ��ǰ����( �ٷֱ�0-100 )
	optional uint32 SkillLevel		 = 		7; 	// ���弼���������ܵȼ�
	optional uint32 CreateType		 = 		8; 	// ������ԭ��0 ��������������1 �����������佨��
	optional uint32 RedStoneStatus   = 		9; 	// �ڵ�״̬ EM_RedStoneStatus
	optional uint32 CurMP			 = 		10; 	// ��ɫ��ǰ����( �ٷֱ�0-100 )
	optional uint32 MaxHP			 = 		11; 	// HP���ֵ
	optional uint32 PetTmpLevel		 = 		12; 	// �ٻ�����ʱ�ȼ�
	optional uint32 PosY			 = 		13; 
	optional uint32 SkillID			 = 		14; 	// ���弼����������ID
	repeated uint32 Appertainings	 = 		15; 	// ����(charid),�б�Ϊ�ձ�ʾ������
	optional uint32 OwnerID			 = 		16; 
	optional uint32 Reserve			 = 		17; 
	optional uint32 PosX			 = 		18; 
	optional uint32 WaitTransTime	 = 		19; 	// �ȴ�����ʱ��(����npc���ˢ��)
	optional uint32 NpcType			 = 		20; 	// NPC����
	optional string OwnerName		 = 		21; 	// NPC������������� 
	optional uint32 Direction		 = 		22; 
	optional uint32 Level			 = 		23; 	// ��ʾ�ȼ�
	optional uint32 MaxMP			 = 		24; 	// MP���ֵ
	optional PBBuffList BuffList	 = 		25; 
	optional uint32 Money			 = 		26; 
	optional uint32 TaskTip			 = 		27; 	// ������ʾͷ��
	optional uint32 CurAP			 = 		28; 	// ��ɫ��ǰ����( �ٷֱ�0-100 )
	optional uint32 AliveTime		 = 		29; 	// ���ʱ��
	optional uint32 PKType			 = 		30; 	// PK����
	optional uint32 AliveState		 = 		31; 
	optional uint32 PetAttackMode	 = 		32; 	// �ٻ��޵�ǰ����ģʽ
	optional uint32 EntityID		 = 		33; 	// ��ɫʵ��ID
	optional uint32 MotionState		 = 		34; 
	optional int32	TargetX			 =		35;		// Ŀ��λ��X
	optional int32	TargetY			 =		36;		// Ŀ��λ��Y
	optional string FamilyName		 =		37;		// ������������
	optional int32 CampID			 =		38;		// ��ӪID
	optional string	CorpsName		 =		39;		// ������������
	optional PBStateList StateList	 = 		40; 	// ״̬�б�
	optional string NewlyName		 =		41;		// ����npcҪ��ʾ����������
	optional uint32	OwnCampID		 =		42;		// ������ӪID
};

message CMessageCreateNpcProNotice
{
	repeated CNpcProInfo NpcList	 = 		1; 	// npc �б�
	optional uint32 ListID			 = 		2; 
};

// *************************************************************************** //
// CMessageUseSkillRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUseSkillRequest
{
	optional uint32 PosX  = 		1; 
	repeated uint32 EntityIDList  = 2; 	// Ⱥ��������ʵ���б�
	optional uint32 Index  = 		3; 	// �������� ( ��SkillList�е������±� )
	optional uint32 ListID  = 		4; 	// �ͻ������ڱ�ʾ�����Ⱥ�����к�
	optional uint32 EntityID  = 	5;	// Ŀ��ʵ��
	optional uint32 PosY  = 		6; 
	optional uint32 SkillID  = 		7; 	// ����ID
	optional uint32 IsMagicWeapon= 	8; 	// �Ƿ񷨱�����
	optional uint32 SrcEntityID	=	9; // Դʵ��(����Ϊ�ٻ���)
};

// *************************************************************************** //
// CMessageNormalAttackRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageNormalAttackRequest
{
	optional uint32 EntityID  = 		1; 
};

// *************************************************************************** //
// CMessagePickItemRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessagePickItemRequest
{
	optional uint32 EntityID  = 		1; 
};

// *************************************************************************** //
// �������NPC����
// *************************************************************************** //
message CMessageClickNpcRequest
{
	optional uint32 EntityID  = 		1; 
};

// *************************************************************************** //
// �������NPC��Ӧ
// *************************************************************************** //
message CMessageClickNpcResponse
{
	optional uint32 EntityID  = 		1; 
};

// *************************************************************************** //
// �رնԻ�֪ͨ
// *************************************************************************** //
message CMessageCloseDialogNotice
{
};

//// *************************************************************************** //
//// ���NPC�̵����
//// *************************************************************************** //
//message CMessageClickShopServiceRequest
//{
//	optional uint32 EntityID = 1;
//};
//
//// *************************************************************************** //
//// ���NPC�̵����
//// *************************************************************************** //
//message CMessageClickShopServiceResponse
//{
//	optional uint32 EntityID = 1;
//};

//// *************************************************************************** //
//// ���NPC�ʼ�����
//// *************************************************************************** //
//message CMessageClickMailServiceRequest
//{
//	optional uint32 EntityID = 1;
//};
//
//// *************************************************************************** //
//// ���NPC�ʼ�����
//// *************************************************************************** //
//message CMessageClickMailServiceResponse
//{
//	optional uint32 EntityID = 1;
//};

//// *************************************************************************** //
//// ���NPC�ֿ����
//// *************************************************************************** //
//message CMessageClickStorageServiceRequest
//{
//	optional uint32 EntityID = 1;
//};
//
//// *************************************************************************** //
//// ���NPC�ֿ����
//// *************************************************************************** //
//message CMessageClickStorageServiceResponse
//{
//	optional uint32 EntityID		= 1;
//	repeated PBItemObject PbItem	= 2; 
//};


//// *************************************************************************** //
//// ���NPC��������
//// *************************************************************************** //
//message CMessageClickUpgServiceRequest
//{
//	optional uint32 EntityID = 1;
//};
//
//// *************************************************************************** //
//// ���NPC��������
//// *************************************************************************** //
//message CMessageClickUpgServiceResponse
//{
//	optional uint32 EntityID = 1;
//};

//// *************************************************************************** //
//// ���NPC���ͷ���
//// *************************************************************************** //
//message CMessageClickTeleServiceRequest
//{
//	optional uint32 EntityID = 1;
//};
//
//// *************************************************************************** //
//// ���NPC���ͷ���
//// *************************************************************************** //
//message CMessageClickTeleServiceResponse
//{
//	optional uint32 EntityID = 1;
//};

// *************************************************************************** //
// ��ý�Ǯ֪ͨ
// *************************************************************************** //
message CMessageUpdateMoneyNotice
{
	optional uint32 Total  = 		1; 			// �ܵ�Ǯ��
	optional int32 Money  = 		2; 			// �ı��Ǯ��
};

// *************************************************************************** //
// ��ð󶨽�Ǯ֪ͨ
// *************************************************************************** //

message CMessageUpdateBindMoneyNotice
{
	optional uint32	Total  = 		1; 			// �ܵİ󶨽�Ǯ��
	optional int32	Money  = 		2; 			// �ı�İ󶨽�Ǯ��
};

// *************************************************************************** //
// �����������
// *************************************************************************** //
message CMessagePurchaseItemRequest
{
	optional uint32 Number  = 		1; 			// ��������
	optional uint32 PageIndex  = 		2; 		// ���߳��۱��е�ҳ����
	optional uint32 EntityID  = 		3; 		// ����NPCʵ��ID
	optional uint32 ItemIndex  = 		4; 		// ���߳��۱��еĵ�������
};

// *************************************************************************** //
// ���۵�������
// *************************************************************************** //
message CMessageSellItemRequest
{
	optional uint32 EntityID  = 		1; 		// ����NPCʵ��ID
	optional uint32 Number  = 		2; 			// ���߰����еĵ�������
	optional uint32 ItemIndex  = 		3; 		// ���߰����еĵ�������
};

//**************************************************************
// NPC �۳��ɹ��ظ�
//**************************************************************

message CMessageSellItemResponse
{
	optional PBItemObject Item  = 		1; 
};

// *************************************************************************** //
// ɾ������֪ͨ
// *************************************************************************** //
message CMessageRemoveItemNotify
{
	optional uint32 ItemIndex  = 		1; 		// ���߰����еĵ�������
	optional uint32 Pos  = 		2; 
	optional uint32 Number  = 		3; 		// ���߰����еĵ�������
};


// *************************************************************************** //
// ɾ���������֪ͨ
// *************************************************************************** //
message CMessageRemoveTaskItemNotice
{
	optional uint32 Number  = 		1; 		// ��������еĵ�������
	optional uint32 ItemIndex  = 		2; 		// ��������еĵ�������
};


// *************************************************************************** //
// ������������
// *************************************************************************** //
message CMessageThrowItemRequest
{
	optional uint32	Number     = 		1; 	    // ���߰����еĵ�������
	optional uint32	ItemIndex  = 		2; 		// ���߰����еĵ�������
};

// *************************************************************************** //
// ��������֪ͨ
// *************************************************************************** //
message CMessageThrowItemNotice
{
	optional uint32	ItemIndex  = 		1; 		// ���߰����еĵ�������
	optional uint32	Number  = 		2; 		// ���߰����еĵ�������
};

// *************************************************************************** //
// �����������
// *************************************************************************** //
message CMessageThrowMoneyRequest
{
	optional uint32	Number  = 		1; 		// �����Ľ������
};

// *************************************************************************** //
// �޸Ŀ��������
// �����˱�ʾ��λ���ͺ���λ�������ֶ�
// *************************************************************************** //

message CMessageSetShortcutRequest
{
	optional uint32 Type  = 		1; 
	optional uint32 LabelType   = 		2; 
	optional uint32 LabelIndex  = 		3;  
	optional uint32 Index  = 		4; 
	optional uint32 Shortcut  = 		5; 
	optional uint32 Param1	= 6;
};

// *************************************************************************** //
// CMessageEntityRelifeNotice ��Ϸ������  -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageEntityRelifeNotice
{
	optional uint32 EntityID  = 		1; 
	optional uint32 MaxHP  = 		2; 
	optional uint32 CurMP  = 		3; 
	optional uint32 PosX  = 		4; 
	optional uint32 CurHP  = 		5; 
	optional uint32 MaxMP  = 		6; 
	optional uint32 PosY  = 		7; 
};

// *************************************************************************** //
// CMessageEntityDisappearNotice ��Ϸ������  -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageEntityDisappearNotice
{
	optional uint32 EntityID  = 		1; 
};

// *************************************************************************** //
// CMessagePlayerReliveRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //

message CMessagePlayerReliveRequest
{
	optional uint32 ReliveType  = 		1; 		// ��������
};

// *************************************************************************** //
// CMessagePlayerReliveRequest ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessagePlayerReliveNotice
{
	optional uint32 PosY  = 		1; 			// ����ĺ�����
	optional uint32 MaxMP  = 		2; 			// ������MP���ֵ
	optional uint32 PosX  = 		3; 			// ����ĺ�����
	optional uint32 MaxHP  = 		4; 			// ������HP���ֵ
	optional uint32 CurHP  = 		5; 			// ������HP��ǰֵ
	optional uint32 CurMP  = 		6; 			// ������MP��ǰֵ
	optional uint32 EntityID  = 		7; 		// ����ʵ��ID
};

// *************************************************************************** //
// CMessageRemoveBuffNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageRemoveBuffNotice
{
	optional uint32 EntityID  = 		1; 		// ʵ��ID
	optional uint32 BuffID  = 		2; 		// BUFFID
};

// *************************************************************************** //
// CMessageChangeStateNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //

message CMessageChangeStateNotice
{
	optional uint32 State  = 		1; 
	optional bool InState  = 		2; 
	optional uint32 Parame1  = 		3; 
	optional uint32 ListID  = 		4; 
	optional uint32 Parame2  = 		5; 
	optional uint32 EntityID  = 		6; 
};

// *************************************************************************** //
// ���ܽ��, ����,���ߺ�Buff��ɵĽ�����ǹ�����ɵ�
// *************************************************************************** //
message PBFuncResult
{
	optional uint32 PosX  = 		1; 
	optional uint32 Func  = 		2; 
	optional uint32 EntityID  = 		3; 	// Ŀ��ʵ��ID
	optional uint32 Direction  = 		4; 
	optional uint32 PosY  = 		5; 
	optional uint32 Value1  = 		6; 
	optional uint32 Value2  = 		7; 
	optional uint32 Value5  = 		8; 
	optional uint32 Value3  = 		9; 
	optional uint32 Value4  = 		10; 
	optional uint32 Result  = 		11; 	// ִ�н���͹��ܣ���16λ����������16λ������
	optional uint32 ListID  = 		12; 
	optional uint32 SrcEntityID  = 		13; 
};

// *************************************************************************** //
// CMessageUseSkillNotice ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUseSkillNotice
{
	repeated PBFuncResult FuncResult  = 		1; 
	optional uint32 SrcY  = 		2; 
	optional uint32 SrcEntityID  = 		3; 		// Դʵ��ID
	optional uint32 ResultNumber  = 		4; 		// �������
	optional uint32 DesX  = 		5; 
	optional uint32 SkillID  = 		6; 			// ����ID
	optional uint32 SrcX  = 		7; 
	optional uint32 DesY  = 		8; 
	optional uint32 SkillLevel  = 		9; 		// ���ܵȼ�
	optional uint32 DesEntityID  = 		10; 		// Ŀ��ʵ��ID
	optional uint32 ListID  = 		11; 				// �ͻ������ڱ�ʾ�����Ⱥ�����к�
};

// *************************************************************************** //
// CMessageFuncResultNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageFuncResultNotice
{
	optional uint32 ResultNumber  = 		1; 		// �������
	repeated PBFuncResult FuncResult  = 		2; 
};

// *************************************************************************** //
// CMessageRemoveBuffNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageChangeMetierNotice
{
	optional uint32 MetierID  = 		1; 		// ְҵID
	optional uint32 EntityID  = 		2; 		// ʵ��ID
};

// *************************************************************************** //
// CMessageLockItemNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageLockItemNotice
{
	optional uint32 Index  = 		1; 			// ������������
	optional uint32 Locked  = 		2; 		// ������
};


// *************************************************************************** //
// CMessageObtainExpNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageObtainExpNotice
{
	optional uint32 ExpDelta  = 		1; 	// ������õľ���
	optional uint32 ListID  = 		2; 		// �������к�
	optional uint32 LeveUpFlag  = 		3; 	// ��Ϊ��þ����������־( 1 ����, 0 ������ )
	optional uint32 Exp  = 		4; 		// ������ǰ�ľ���
};

// *************************************************************************** //
// CMessageMoveItemRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageMoveItemRequest
{
	optional uint32 Number  = 		1; 
	optional uint32 DesIndex  = 	2; 
	optional uint32 SrcIndex  = 	3; 
	optional uint32 SrcSlot  = 		4; 
	optional uint32 DesSlot  = 		5; 
	optional uint32	NpcID	 =		6;			// ����ƶ��漰�ֿ�Ļ���NpcID��ʾ�ֿ����npc��ʵ��ID
};

// *************************************************************************** //
// CMessageMoveItemNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageMoveItemNotice
{
	optional uint32 DesIndex  = 		1; 
	optional uint32 SrcSlot   = 		2; 
	optional uint32 SrcIndex  = 		3; 
	optional uint32 Number    = 		4; 
	optional uint32 DesSlot   = 		5; 
	optional uint32	Errcode	  =			6;		// ������	
	optional uint32	SrcNum	  =			7;		// Դ������Ʒ��������	
	optional uint32	DesNum	  =			8;		// Ŀ�������Ʒ��������
};

// *************************************************************************** //
// CMessageInsertEquipNotify ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageInsertEquipNotify
{
	optional PBItemObject ItemObjet  = 		1; 
	optional uint32 Pos  = 		2; 
};

// *************************************************************************** //
// CMessageInsertItemNotify ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageInsertItemNotify
{
	repeated uint32 Index  = 		1; 
	repeated uint32 Number  = 		2; 
	optional uint32 ItemID  = 		3; 
	optional uint32 BindState  = 		4;  // ��״̬
	optional uint32 Pos  = 		5; 			
	optional uint32 Yuan  = 		6; 	   // �����Ԫ������ΪԪ��ֵ	
};

// *************************************************************************** //
// CMessageProDebugNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageProDebugNotice
{
	optional uint32 Command  = 		1; 			// ��������
	repeated uint32 Parameter  = 		2; 	// �������
	optional uint32 ParameterNumber  = 		3; 
};

// *************************************************************************** //
// CMessageProErrorNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageProErrorNotice
{
	optional int32 ErrorCode  = 		1; 		// ������
};

// *************************************************************************** //
// CMessageEquipItemRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageEquipItemRequest
{
	optional uint32 SrcIndex  = 		1; 			// װ��������
	optional uint32 DesIndex  = 		2; 			// Ŀ�ĵ�����
};

// *************************************************************************** //
// CMessageEquipItemRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUnEquipItemRequest
{
	optional uint32 Index  = 		1; 			// װ��������
	optional uint32 Part  = 		2; 			// жװ�Ĳ�λ
};

// *************************************************************************** //
// CMessageEquipItemNotice ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageEquipItemNotice
{
	optional uint32 SrcIndex  = 		1; 			// ����������
	optional uint32 DesIndex  = 		2; 			// Ŀ�ĵ�����
	optional uint32	Errcode	  =			3;			// ������	 	
};

// *************************************************************************** //
// CMessageUnEquipItemNotice ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUnEquipItemNotice
{
	optional uint32 Part	= 		1; 			// װ���Ĳ�λ
	optional uint32 Index	= 		2; 			// װ��������
	optional uint32	Errcode	=		3;			// ������
};

// *************************************************************************** //
// CMessagePlayerEquipNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessagePlayerChangeEquipNotice
{
	optional uint32 MaxHP  = 		1; 			// ���Ѫ
	optional uint32 CurMP  = 		2; 			// ��ǰ��
	optional uint32 EntityID  = 		3; 		// װ�������ʵ��ID
	optional uint32 Part  = 		4; 			// װ���Ĳ�λ
	optional uint32 MaxMP  = 		5; 			// �����
	optional uint32 ItemID  = 		6; 			// װ���ĵ���ID
	optional uint32 CurHP  = 		7; 			// ��ǰѪ
	optional uint32	WeaponJewel		 =		8;			// ������ʯ��
	optional uint32	ChestJewel		 =		9;			// ���߱�ʯ��
	optional uint32	WeaponLevel		 =		10;			// �����ȼ�
	optional uint32	ChestLevel		 =		11;			// ���ߵȼ�
	optional uint32	MWID			 =		12;			// ����ID
	optional uint32	FashionID		 =		13;			// ʱװID
	optional uint32	MarriageID		 =		14;			// ���װ��ID
	optional uint32	MWQLID			 =		15;			// ��������ID
};

// *************************************************************************** //
// CMessageEntityRefreshNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageEntityRefreshNotice
{
	optional uint32 MaxMP  = 		1; 			// ���MP���ֵ
	optional uint32 CurMP  = 		2; 			// ��ҵĵ�ǰ��
	optional uint32 CurHP  = 		3; 			// ��ҵĵ�ǰѪ
	optional uint32 MaxHP  = 		4; 			// ���HP���ֵ
	optional uint32 EntityID  = 		5; 		// ���ʵ��ID
};

// *************************************************************************** //
// CMessageClickSkillPointRequest ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageClickSkillPointRequest
{
	optional uint32 Row  = 		1; 			// ��������������
	optional uint32 Col  = 		2; 			// �������ĺ�����
	optional uint32 GenerID  = 		3; 		// ��������ϵ��ID
};

// *************************************************************************** //
// CMessageClickSkillPointResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageClickSkillPointResponse
{
	optional uint32 Col  = 		1; 			// �������ĺ�����
	optional uint32 Row  = 		2; 			// ��������������
	optional uint32 GenerID  = 		3; 		// ��������ϵ��ģ��ID
};



// *************************************************************************** //
// CMessageResetAPPRequest ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageResetAPPRequest
{
};


// *************************************************************************** //
// CMessageResetAPPResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageResetAPPResponse
{
	optional uint32 Ret  = 		1; 	// ������
};

// *************************************************************************** //
// CMessageResetSSPRequest ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageResetSSPRequest
{
	optional uint32 Col  = 		1; 
	optional uint32 Row  = 		2; 
	optional uint32 GenerID  = 		3; 
};

// *************************************************************************** //
// CMessageResetASPRequest ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageResetASPRequest
{
};

// *************************************************************************** //
// CMessageResetSSPResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageResetSSPResponse
{
	optional uint32 Row  = 		1; 
	optional uint32 GenerID  = 		2; 
	optional uint32 Col  = 		3; 
};

// *************************************************************************** //
// CMessageResetASPResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageResetASPResponse
{
	optional uint32 Ret  = 		1; 	// ������
};

// *************************************************************************** //
// CMessageEntityDieNotice ��Ϸ�ͻ��� -> ��Ϸ������ 
// *************************************************************************** //
message CMessageEntityDieNotice
{
	optional uint32 EntityID  = 		1; 
};

// *************************************************************************** //
// GetRolePersonalInfoByID ��Ϸ�ͻ��� -> ��Ϸ������ 
// �������ID��ȡ�������
// *************************************************************************** //
message GetRolePersonalInfoByIDMsg
{
	optional uint32 EntityID  = 		1; 
	optional uint32 SessionID  = 		2; 
};

// *************************************************************************** //
// GetRolePersonalInfoByName ��Ϸ�ͻ��� -> ��Ϸ������ 
// ������ҽ�ɫ����ȡ�������
// *************************************************************************** //
message GetRolePersonalInfoByNameMsg
{
	optional string Name  = 		1; 
	optional uint32 SessionID  = 		2; 
};


//�����װ�˽�ɫ�ĸ�������
message PBRolePersonalInfo
{
	optional string RealMetier  = 		1;  //��ʵְҵ
	optional string CharName  = 		2;  //��ɫ��
	optional string Space  = 		3;  //���Կռ�
	optional uint32 Age  = 		4; 		//���� 1-254
	optional string LoveNote  = 		5;  //�ҵİ����
	optional uint32 Cons  = 		6;  //����ID 1-12
	optional uint32 Head  = 		7;  //ͷ��ID��0��ʼ
	optional string Title  = 		8;  //��ν
	optional uint32 PlayerID  = 		9;  //���ID
	optional uint32 Sex  = 		10; 		//�Ա� 
};

// *************************************************************************** //
// SendRolePersonalInfo ��Ϸ������ -> ��Ϸ�ͻ��� 
// �����������������
// *************************************************************************** //
message SendRolePersonalInfoMsg
{
	optional PBRolePersonalInfo Info  = 		1; 
	optional uint32 SessionID  = 		2; 
};

// *************************************************************************** //
// GetRolePersonalInfo ��Ϸ�ͻ��� -> ��Ϸ������ 
// �޸��������
// *************************************************************************** //
message SetRolePersonalInfoMsg
{
	optional PBRolePersonalInfo Info  = 		1; 
	optional uint32 SessionID  = 		2; 
};

// *************************************************************************** //
// RolePersonalInfoBackMsg ��Ϸ������ -> ��Ϸ�ͻ��� 
// ���������ز�����
// *************************************************************************** //
message RolePersonalInfoBackMsg
{
	enum CHANGE_INFO
	{
		SET_OK = 0; //�޸�������ϳɹ�
		SET_FAIL = 1; //ʧ��
	};
	optional uint32 Code = 1;
	optional uint32 SessionID = 2;
};


// *************************************************************************** //
// CMessageUseItemRequest ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageUseItemRequest
{
	optional uint32 Pos    = 		1; 			// λ�õ�����
	optional uint32 Index  = 		2; 			// ����������
	optional uint32 Param  = 		3; 			// ����1( ʹ�ô��ͷ���Ʒʱ�����ͷ�ʽѡ�� )
};

// *************************************************************************** //
// CMessageUseItemResponse ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUseItemResponse
{
	optional uint32 Index  = 		1; 		// ����������
	optional uint32 Param1  = 		2; 		// ����������ҩ����ʾʣ���HP; ����Ǵ����ʹ��ͷ�����ʾ��ʹ�ô���
	optional uint32 Pos  = 		3; 		// λ�õ�����
	optional uint32 Result  = 		4; 		// ���صĽ��
	optional uint32 Param2  = 		5; 		// ����������ҩ����ʾʣ���MP
	optional uint32 ItemID  = 		6; 		// ʹ����Ʒ��ID	
	optional uint32	Param3	=		7;		// ʣ���AP
};

// *************************************************************************** //
// CMessagePlayerUseItemNotice ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessagePlayerUseItemNotice
{
	// ʵ��ID
	// ����ID
	optional uint32 CurHP  = 		1; 			// ��ǰѪ
	optional uint32 CurMP  = 		2; 			// ��ǰ��
	optional uint32 ItemID  = 		3; 
	optional uint32 EntityID  = 		4; 
};


// *************************************************************************** //
// CMessageTelePortResponse ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageTelePortResponse
{
	// ���͵�λ��
	optional uint32 PosX  = 		1; 
	optional uint32 Index  = 		2; 			// ����������
	optional uint32 PosY  = 		3; 
};

// *************************************************************************** //
// CMessageProduceEquipRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageProduceEquipRequest
{
	optional uint32 Type2  = 		1; 		// ��������ϸ��������Ϊ�������ͣ�����Ϊ����λ�ã�ҩƷΪҩƷ����
	optional uint32 Type1  = 		2; 		// ����������,0���� 1���� 
	optional uint32 Type3  = 		3; 		// ��������ϸ��������Ϊ����Ч��	
	optional uint32 Level  = 		4; 		// �������ߵĵȼ�
	optional uint32 Number  = 		5; 	// ��Ҫ����������
	optional uint32 Rank  = 		6; 		// ���ò��ϵļ���
	optional uint32 Bind =			7;	
};

// *************************************************************************** //
// CMessageUpgAddItemRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUpgAddItemRequest
{
	optional uint32 Index  = 		1; 		// �����λ��
};

// *************************************************************************** //
// CMessageUpgAddItemResponse ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUpgAddItemResponse
{
	optional uint32 Index1  = 		1; 		// �����λ��
	optional uint32 Index2  = 		2; 		// ����������λ��
};

// *************************************************************************** //
// CMessageUpgDelItemRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUpgDelItemRequest
{
	optional uint32 Index  = 		1; 		// ����������λ��
};

// *************************************************************************** //
// CMessageUpgDelItemResponse ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUpgDelItemResponse
{
	optional uint32 Index1  = 		1; 		// �����λ��
	optional uint32 Index2  = 		2; 		// ����������λ��
};

// *************************************************************************** //
// CMessageUpgEquipRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUpgEquipRequest
{
	optional uint32 NpcEntityID  = 		1;   // ������ڲ����İ󶨸÷����NPCʵ��ID
	optional uint32 Type		 = 		2;	 // ����װ��������	
	optional uint32 EquipIndex	 =		3;	 // װ����λ��
	optional uint32	ItemIndex	 =		4;	 // ����ʯ��λ��
	repeated uint32 LuckIndex	 =		5;	 // ����λ��
};

// *************************************************************************** //
// CMessageUpgEquipNotice ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUpgEquipNotice
{
	optional uint32 Type  = 		1; 			// ��������
	optional uint32 Level  = 		2; 			// ��ǰװ���ȼ�
	optional uint32 Result  = 		3; 			// ������� 0�ɹ�1����2��ʧ
	optional uint32 EqpIdx =		4;			// װ���ڰ����������
};

// *************************************************************************** //
// CMessageProducePhysRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageProducePhysRequest
{
	optional uint32 Type  = 		1; 		// ���������� 
	optional uint32 Level  = 		2; 		// �����ĵȼ�
	optional uint32 Number  = 		3; 		// ��Ҫ����������
};

// *************************************************************************** //
// CMessageProFinNotice ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageProFinNotice
{
	optional uint32 Result   = 		1; 
	optional uint32 LeftNum  = 		2; 	
};

// *************************************************************************** //
// CMessageProBreakNotice ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageProBreakNotice
{
	optional uint32 Result  = 		1; 
};


// ������Ϸ�װ������ĵ�����/��Ӧ
// *************************************************************************** //
// CMessagePushRuneRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessagePushRuneRequest
{
	optional uint32 Index  = 		1; 					// ����װ��������ڰ��е�λ��
};

// *************************************************************************** //
// CMessagePushRuneResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessagePushRuneResponse
{
	optional uint32 Index1  = 		1; 					// ����װ��������ڰ��е�λ��
	optional uint32 Index2  = 		2; 					// ��������λ��
};


// �����������װ��/���ĵ�����/��Ӧ
// *************************************************************************** //
// CMessagePopRuneRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessagePopRuneRequest
{
	optional uint32 Index  = 		1; 					// ���µ�λ��
};

// *************************************************************************** //
// CMessagePopRuneResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessagePopRuneResponse
{
	optional uint32 Index2  = 		1; 					// ���µ�λ��
	optional uint32 Index1  = 		2; 					// ����װ��������ڰ����λ��
};


// ��Ƕ���ĵ�����/��Ӧ
// *************************************************************************** //
// CMessageInsertRuneRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageInsertRuneRequest
{
	optional uint32	EquipIndex	=	1;			// װ����λ��
	optional uint32	RuneIndex	=	2;			// ���ĵ�λ��
};

// *************************************************************************** //
// CMessageInsertRuneNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageInsertRuneNotice
{
	optional uint32 Result  = 		1; 		// ���ؽ����0�ɹ�
};


// ����Ƕ��ʯ����Ϸ�װ��/��ʯ������/��Ӧ
// *************************************************************************** //
// CMessageInsertPushJewelRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageInsertPushJewelRequest
{
	optional uint32 DesIndex  = 		1; 					// ���õ�λ��
	optional uint32 SrcIndex  = 		2; 					// ����װ����ʯ�ڰ��е�λ��
};

// *************************************************************************** //
// CMessageInsertPushJewelResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageInsertPushJewelResponse
{
	optional uint32 Index1  = 		1; 					// ����װ����ʯ�ڰ��е�λ��
	optional uint32 Index2  = 		2; 					// ����λ��
};


// ����Ƕ��ʯ���������װ����ʯ������/��Ӧ
// *************************************************************************** //
// CMessageInsertPopJewelRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageInsertPopJewelRequest
{
	optional uint32	Index  = 		1; 					// ���µ�λ��
};

// *************************************************************************** //
// CMessageInsertPopJewelResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageInsertPopJewelResponse
{
	optional uint32	Index2  = 		1; 					// ���µ�λ��
	optional uint32 Index1  = 		2; 					// ����װ�����鱦�ڰ����λ��
};


// ��Ƕ��ʯ������/��Ӧ
// *************************************************************************** //
// CMessageInsertJewelRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageInsertJewelRequest
{
	optional uint32 EquipIndex	=	1;
	repeated uint32 JewelIndex	=	2;
};

// *************************************************************************** //
// CMessageInsertJewelNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageInsertJewelNotice
{
	optional uint32 Bind    = 		1; 		// װ���Ƿ񱻰�
	optional uint32	Result  = 		2; 		// ��Ƕ�����0�ɹ�
};


// ��Ԫ�����װ�������Ϸ�װ��������/��Ӧ
// *************************************************************************** //
// CMessageEatPushEquipRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageEatPushEquipRequest
{
	optional uint32	Index  = 		1; 					// ����װ���ڰ��е�λ��
};

// *************************************************************************** //
// CMessageEatPushEquipResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageEatPushEquipResponse
{
	optional uint32 Index2  = 		1; 					// ����λ��
	optional uint32	Index1  = 		2; 					// ����װ���ڰ��е�λ��
};


// ��Ԫ�����װ������������װ��������/��Ӧ
// *************************************************************************** //
// CMessageEatPopEquipRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageEatPopEquipRequest
{
	optional uint32	Index  = 		1; 					// ���µ�λ��
};

// *************************************************************************** //
// CMessageEatPopEquipResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //

message CMessageEatPopEquipResponse
{
	optional uint32	Index2  = 		1; 					// ���µ�λ��
	optional uint32 Index1  = 		2; 					// ����װ���ڰ����λ��
};

// ��װ��������/��Ӧ
// *************************************************************************** //
// CMessageEatEquipRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageEatEquipRequest
{
	optional uint32 BugIndex	= 		1; 				// Ԫ�����ڰ����λ��
	repeated uint32 EquipIndex	=		2;				// Ҫ�Ե�װ���ڰ����λ��
};

// *************************************************************************** //
// CMessageEatEquipNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageEatEquipNotice
{
	optional uint32 Number  = 		1; 		// �Ե���ĵ���
	optional uint32 Index  = 		2; 			// Ԫ�����ڰ����λ��
};

// �ϳɷŲ���/Ԫ����������/��Ӧ
// *************************************************************************** //
// CMessageComposePushRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageComposePushRequest
{
	optional uint32	Index  = 		1; 					// �ϳɵ����ڰ��е�λ��
};

// ��Ϸ�ͻ��� -> ��Ϸ������  ������λ��������
message CMessageBaggageLockedRequest
{	
	optional uint32 BagType			=		1;			//  ����������
	optional uint32 KitBagIndex		=		2;			//  �����Ĺ���������
	optional uint32 Locked			=		3;			//  �����Ƿ�����

};

// ������->�ͻ���		��Ӧ�������     
message CMessageBaggageLockedResponse
{	
	optional uint32 BagType			=		1;			//  ����������
	optional uint32 KitBagIndex		=		2;			//  �����Ĺ���������
	optional uint32 Locked			=		3;			//  �����Ƿ�����

};

// *************************************************************************** //
// CMessageComposePushResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageComposePushResponse
{
	optional uint32 Index2  = 		1; 					// ����λ��
	optional uint32	Index1  = 		2; 					// �ϳɵ����ڰ��е�λ��
};

// �ϳ����²���/Ԫ����������/��Ӧ
// *************************************************************************** //
// CMessageComposePopRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageComposePopRequest
{
};

// *************************************************************************** //
// CMessageComposePopResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageComposePopResponse
{
	optional uint32 Index  = 		1; 					// �ϳɵ����ڰ����λ��
};

// �ϳɵ�����/��Ӧ
// *************************************************************************** //
// CMessageComposeRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageComposeRequest
{
	optional uint32 Index  = 		1; 					// ���ϵ�λ��
};

// *************************************************************************** //
// CMessageComposeNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageComposeNotice
{
	optional uint32 Number2  = 		1; 					// ʣ�������
	optional uint32 Index  = 		2; 						// �ϳɵ����ڰ����λ��
	optional uint32 Number1  = 		3; 					// ���ɵ�����
	optional uint32 ItemID  = 		4; 					// ���ɵ���Ʒ
};


// ���۷�װ��/Ԫ����������/��Ӧ
// *************************************************************************** //
// CMessageOpenPushRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageOpenPushRequest
{
	optional uint32	Index  = 		1; 					// ���۵����ڰ��е�λ��
};

// *************************************************************************** //
// CMessageOpenPushResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageOpenPushResponse
{
	optional uint32 Index2  = 		1; 					// ����λ��
	optional uint32	Index1  = 		2; 					// ���۵����ڰ��е�λ��
};

// �������²���/Ԫ����������/��Ӧ
// *************************************************************************** //
// CMessageOpenPopRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageOpenPopRequest
{
	optional uint32	Index  = 		1; 					// ���µ�λ��
};

// *************************************************************************** //
// CMessageOpenPopResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageOpenPopResponse
{
	optional uint32	Index2  = 		1; 					// ���µ�λ��
	optional uint32 Index1  = 		2; 					// ���۵����ڰ����λ��
};

// ���۵�����/��Ӧ
// *************************************************************************** //
// CMessageOpenSlotRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageOpenSlotRequest
{
	optional uint32	EquipIndex	=	1;				// װ����λ��
	optional uint32 EggIndex	=	2;				// Ԫ������λ��
};

// *************************************************************************** //
// CMessageOpenSlotNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageOpenSlotNotice
{
	optional uint32 Index1  = 		1; 					// ����װ���ڰ����λ��
	optional uint32 Index2  = 		2; 					// Ԫ�����ڰ����λ��
	optional uint32 Number  = 		3; 					// ʣ���Ԫ��������
};


// ���͵�����/��Ӧ
// *************************************************************************** //
// CMessagePlayerTeleRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessagePlayerTeleRequest
{
	optional uint32 NpcEntityID  = 		1;	// ������ڲ����İ󶨸÷����NPCʵ��ID
	optional uint32 Order		 = 		2;	// ѡ��ĵص����б��е�λ��
	optional uint32	Index		 = 		3;	// ����������Ʒ�ڰ����е���Ʒ
	optional uint32 PedalEntityID =		4;	// ����̤���ʵ��ID
	optional uint32 AsynTeleTokenID =	5;	// �첽����ID
	optional uint32 IsStatic	 =		6;	// �Ƿ������赲�д���
	optional uint32	MarriageItem =		7;	// �����ߴ���(��������)
};

// *************************************************************************** //
// CMessagePlayerTeleResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessagePlayerTeleResponse
{
	optional int32	ErrCode	=		1;	// ������	
	optional uint32 Order  = 		2; 	// ѡ��ĵص����б��е�λ��
};

// *************************************************************************** //
// CMessagePlayerTeleNotify ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessagePlayerTeleNotify
{
	optional uint32 SrcCharID		= 1;	// �ټ����ͷ�����ID
	optional string SrcCharName		= 2;	// �ټ����ͷ���������
	optional uint32 TeleType		= 3;	// �ټ����ͣ�������
	optional uint32 Timeout			= 4;	// �ټ����ʱ����ʱ��Ч)
	optional uint32 AsynTeleTokenID = 5;	// �첽����ID
	optional uint32 LineID			= 6;	// Ŀ����
	optional uint32 MapID			= 7;	// Ŀ�ĵ�ͼ
	optional uint32 PosX			= 8;	// Ŀ��x
	optional uint32 PosY			= 9;	// Ŀ��y
};


message CMessageRandMoveDirectCallBack
{
	optional uint32 Direction  = 		1; 
	optional uint32 EntityID  = 		2; 
};

message CMessageProDebugCommand
{
	optional string DebugCommond  = 		1; 
};

message CMessageNotifyDirection
{
	optional uint32 Direction  = 		1; 
};

message CMessageNotifyDirectionCallBack
{
	optional uint32 EntityID  = 		1; 
	optional uint32 Direction  = 		2; 
};

message CMessageChangePetModeRequest
{
	optional uint32 ModeType  = 		1; 
};

message CMessageChangePetModeResponse
{
	optional uint32 Result  = 		1; 
};

message CMessagePetLevelUpNotice
{
	optional uint32 EntityID  = 		1; 
	optional uint32 Level  = 		2; 
};
// *************************************************************************** //
// CMessageNotifyEqptDurability ��Ϸ������ -> ��Ϸ�ͻ���
// ����װ���;öȵ�֪ͨ
// *************************************************************************** //
message CMessageNotifyEqptDurability
{
	optional uint32 IsInPackage     = 		1;       // �Ƿ��ڰ����У�1��ʾ�ڰ����У�0��ʾװ�������ϣ�
	repeated uint32 EqptDurability  = 		2;       // װ���;ö�	
	repeated uint32 EqptIndex       = 		3;       // װ������
};

// �����벻��ʱ��ͻ���ͬ������
// *************************************************************************** //
// CMessageSyncPosNotify ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageSyncPosNotify
{
	optional uint32 PosX  = 		1; 				// ʵ���X����
	optional uint32 EntityID  = 		2; 			// ��Ҫͬ����ʵ��ID
	optional uint32 PosY  = 		3; 				// ʵ���Y����
};
// *************************************************************************** //
// CMessageMendEquipment  ��Ϸ�ͻ���->��Ϸ������
// ����װ��������
// *************************************************************************** //
message CMessageMendEquipment 
{
	optional uint32 Index            = 		1;      // װ������ 
	optional uint32 IsInPackage      = 		2;      // �Ƿ��ڰ����У�1��ʾ�ڰ����У�0��ʾװ�������ϣ�
	optional uint32 IsAllEquipment   = 		3;      // �Ƿ���������װ��
	optional uint32	EntityID		 =		4;		// npc��ʵ��ID
};
// *************************************************************************** //
// CMessageMendEquipment ��Ϸ������->��Ϸ�ͻ���  
// ����װ����ɵ�֪ͨ
// *************************************************************************** //
message CMessaegMendEquipmentCallBack
{
	optional uint32  MendResult     = 		1;       // �Ƿ�����ɹ�	
};


// ���ٶȸı�ʱ֪ͨ�������
// *************************************************************************** //
// CMessageSpeedChangedNotify ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageSpeedChangedNotify
{
	optional uint32 EntityID  = 		1; 			// �ٶȸı��ʵ��ID
	optional uint32 Speed  = 		2; 				// ʵ������ٶ�
};

// ֪ͨ�����������ȼ��ĸı�
// *************************************************************************** //
// CMessageProExpNotify ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageProExpNotify
{
	optional uint32 ProExp  = 		1; 				// �µ���������
	optional uint32 ProLevel  = 		2; 			// �µ������ȼ�
};

// ����������۳���NPC�ĵ�����Ϣ
//****************************************************************************//
// CMessageObtainSaleItem	��Ϸ�ͻ��� -> ��Ϸ������
//****************************************************************************//

message CMessageObtainSaleItem
{
	optional uint32 EntityID   = 		1; 			// ����NPC���׵�ʵ��ID
};

// ����������۳���NPC�ĵ�����Ϣ
//****************************************************************************//
// CMessageObtainSaleItemCallBack	��Ϸ������ -> ��Ϸ�ͻ���
//****************************************************************************//

message CMessageObtainSaleItemCallBack
{
	repeated PBItemObject ItemList  = 		1; 		// �����б�
	optional uint32 Amount  = 		2; 				// ��������
};

// �����۳���NPC����Ʒ
//****************************************************************************//
// CMessageBuyBackItem		��Ϸ�ͻ��� -> ��Ϸ������
//****************************************************************************//

message CMessageBuyBackItem
{
	optional uint32 SaleIndex  = 		1; 			// ���ؽ���ĸ�������
}

message CMessageBuyBackItemCallBack
{
	optional uint32 SaleIndex	 = 		1; 
	optional uint32 Number		 = 		2; 		// ��������
	repeated PBItemObject ItemList  = 		3; 		// �����б�
};

message CMessageMoveStorageItem 
{
	optional uint32 DesIndex  = 		1;            // Ŀ��λ�ø�������
	optional uint32 SrcKind   = 		2;            // ԭλ�ã� 0��ʾ�ڰ������� 1 ��ʾ�ڲֿ����� 
	optional uint32 DesKind   = 		3;            // Ŀ��λ�ã�0��ʾ�ڰ������� 1 ��ʾ�ڲֿ�����
	optional uint32 SrcIndex  = 		4;            // ԭλ�ø�������
	optional uint32 ItemNum   = 		5;            // �ƶ�����Ʒ����
}

// �ر�ָ���Ĵ���
//****************************************************************************//
// CMessageCloseWindowReuest		��Ϸ�ͻ��� -> ��Ϸ������
//****************************************************************************//

message CMessageCloseWindowRequest
{
	optional uint32 CloseType  = 		1; 				// �رմ��ڵ����
}

//****************************************************************************//
// CMessageCloseWindowResponse		��Ϸ������ -> ��Ϸ�ͻ���
//****************************************************************************//

message CMessageCloseWindowResponse
{
	optional uint32 Result  = 		1; 				// �رմ��ڵ����
	optional uint32 CloseType  = 		2; 				// �رմ��ڵ����
}

//****************************************************************************//
// CMessageBindItemResponse		��Ϸ������ -> ��Ϸ�ͻ���
// ����Ʒ���
//****************************************************************************//
message CMessageErrorActOnBindItemNotify
{
	optional uint32 ItemPos    = 		1;     // ��Ʒλ��
	optional int32 ErrorCode  = 		2;     // ������
	optional uint32 ItemIndex  = 		3;     // ��Ʒ����
}
//****************************************************************************//
// CMessageAddBindItem		��Ϸ�ͻ���->��Ϸ������
// ��Ӱ���Ʒ
//****************************************************************************//
message CMessageAddBindItemRequest
{
	optional uint32  ItemIndex  = 		1;                 // λ������  
};
//****************************************************************************//
// CMessageAddBindItemResponse		 ��Ϸ������ -> ��Ϸ�ͻ���
// ��Ӱ���Ʒ�ķ�����Ϣ
//****************************************************************************//
message CMessageAddBindItemResponse
{
	optional uint32 InputPos   = 		1; 			     // ����λ��0��ʾ����λ��1��ʾ��ʯλ��
	optional uint32 ItemIndex  = 		2;                // λ������
	optional uint32 Result     = 		3; 				 // �������1��ʾ�ɹ�0��ʾʧ��
};

//****************************************************************************//
// CMessageTakeBindItemRequest		 ��Ϸ������ -> ��Ϸ�ͻ���
// ȡ�·��ڰ󶨽����ϵ���Ʒ����
//****************************************************************************//
message CMessageTakeBindItemRequest
{
	optional uint32 ItemIndex  = 		1;           // λ������0��ʾ����λ��1��ʾ��ʯλ��	
};

//****************************************************************************//
// CMessageTakeBindItemResponse		 ��Ϸ������ -> ��Ϸ�ͻ���
// ȡ�·��ڰ󶨽����ϵ���Ʒ��Ӧ
//****************************************************************************//
message CMessageTakeBindItemResponse
{
	optional uint32 ItemIndex  = 		1;     // λ������	
	optional uint32 InputPos   = 		2; 			     // ����λ��0��ʾ����λ��1��ʾ��ʯλ��	
};

//****************************************************************************//
// CMessageBindItemRequest	 ��Ϸ�ͻ���	 ->  ��Ϸ������
// ����Ʒ������
//****************************************************************************//
message CMessageBindItemRequest
{
	optional uint32 CLientCode  = 		1; 
	optional uint32	ItemIndex	=		2;
	optional uint32	BindIndex	=		3;
};
//****************************************************************************//
// CMessageBindItemResponse		��Ϸ������ -> ��Ϸ�ͻ���
// ����Ʒ���
//****************************************************************************//
message CMessageBindItemResponse
{
	optional uint32 BindResult  = 		1; 
	optional uint32 BindStatus  = 		2; 
	optional uint32 ItemIndex   = 		3; 
};

//****************************************************************************//
// CMessageFreeItem		��Ϸ�ͻ���->��Ϸ������
// ��ӽ������Ʒ������
//****************************************************************************//
message CMessageAddItemForFreeRequest
{
	optional uint32 ItemIndex  = 		1;    // λ������
};

//****************************************************************************//
// CMessageFreeItem		��Ϸ�ͻ���->��Ϸ������
// ��ӽ������Ʒ������
//****************************************************************************//
message CMessageAddItemForFreeResponse
{
	optional uint32 InputPos   = 		1;     // ����λ��0��ʾ����λ��1��ʾ��ʯλ��	
	optional uint32 ItemIndex  = 		2;     // λ������	
};

//****************************************************************************//
// CMessageTakeItemForFreeRequest		��Ϸ�ͻ���->��Ϸ������
// ж�´��������Ʒ������
//****************************************************************************//
message CMessageTakeItemForFreeRequest
{
	optional uint32 ItemIndex  = 		1; 
};

//****************************************************************************//
// CMessageTakeItemForFreeResponse		��Ϸ�ͻ���->��Ϸ������
// ж�´��������Ʒ������
//****************************************************************************//
message CMessageTakeItemForFreeResponse
{
	optional uint32 ItemIndex  = 		1;     // λ������	
	optional uint32 InputPos   = 		2; 	 // ����λ��0��ʾ����λ��1��ʾ��ʯλ��	
};

//*********************************************************************

//****************************************************************************//
// CMessageFreeItem		��Ϸ�ͻ���->��Ϸ������
// �����Ʒ�󶨵�����
//****************************************************************************//
message CMessageFreeItem 
{
	optional uint32 CLientCode     = 		1;
	optional uint32 ItemIndex	   =		2;	
};
//****************************************************************************//
// CMessageTakeBindItemResponse		 ��Ϸ������ -> ��Ϸ�ͻ���
// ȡ�·��ڰ󶨽����ϵ���Ʒ��Ӧ
//****************************************************************************//
message CMessageFreeItemResponse
{
	optional uint32 ItemIndex       = 		1;     // λ������	
	optional uint32 Result          = 		2;     // �������1��ʾ�ɹ�0��ʾʧ��
	optional uint32 InputPos        = 		3; 	  // ����λ��0��ʾ����λ��1��ʾ��ʯλ��	
	optional uint32 BindFreeTime	   = 		4;     // �󶨽��ʱ��
};

//****************************************************************************//
// CMessageRideHorseNotice			 ��Ϸ������ -> ��Ϸ�ͻ���
// ���������֪ͨ
//****************************************************************************//
message CMessageRideHorseNotice
{
	optional uint32 EntityID       = 		1;     // ʵ��ID	
	optional uint32 Speed          = 		2;     // ʵ�嵱ǰ�ٶ�
	optional uint32 HorseResult	   = 		3;     // ������(0Ϊ����,1Ϊ����)
	optional uint32 HorseTempID    = 		4; 	  // �������ģ��ID
};

// *************************************************************************** //
// CMessageUseTaskItemRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUseTaskItemRequest
{
	optional uint32 Index  = 		1; 			// ����������
};


// *************************************************************************** //
// CMessageUseTaskItemNotice ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageUseTaskItemNotice
{
	optional uint32 Index  = 		1; 			// ����������
};

// *************************************************************************** //
// CMessageStudySkillRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageStudySkillRequest
{
	repeated CMessageClickSkillPointRequest StudySkillList  = 		1; 			// ѧϰ�����б�
};

message CMessageSkillTreeResponse
{
	optional uint32								Index			 = 		1; 
	optional uint32								Result			 = 		2; 
	optional uint32								GenerID			 = 		3; 		// ��������ϵ��ģ��ID
	optional uint32								Row				 = 		4; 			// ��������������
	optional uint32								Col				 = 		5; 			// �������ĺ�����
	optional uint32								SkillID			 = 		6; 
};

// *************************************************************************** //
// CMessageStudySkillResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageStudySkillResponse
{
	//repeated CMessageClickSkillPointRequest StudySkillList		= 1;		// ѧϰ�����б�
	//repeated uint32							ResultList			= 2;		// ѧϰ���ܽ���б�
	repeated CMessageSkillTreeResponse		StudySkillList		 = 		1; 
	optional uint32							MaxHP				 = 		2; 		// ���HP
	optional uint32							CurHP				 = 		3; 		// ��ǰHP
	optional uint32							RemainSkillPoint	 = 		4; 		// ʣ�༼�ܵ�
	optional uint32							MaxMP				 = 		5; 		// ���MP
	optional uint32							CurMoney			 = 		6; 		// ��ǰ�����
	optional uint32							CurMP				 = 		7; 		// ��ǰMP
};

// *************************************************************************** //
// CMessageAddPropertyPointRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageAddPropertyPointRequest
{
	optional uint32 AddSTR  = 		1; 		// �����ӵ�
	optional uint32 AddSPR  = 		2; 		// ����ӵ�
	optional uint32 AddWis  = 		3; 		// �����ӵ�
	optional uint32 AddCON  = 		4; 		// ���ʼӵ�
	optional uint32 AddSTA  = 		5; 		// �����ӵ�
};

// *************************************************************************** //
// CMessageAddPropertyPointResponse ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageAddPropertyPointResponse
{
	optional uint32 Result			 = 		1; 		// �ӵ���
};


// *************************************************************************** //
// �趨�س�		�ͻ���->������
// *************************************************************************** //
message CMessageSetTownRequest
{
	optional uint32 NpcEntityID  = 		1;   // ������ڲ����İ󶨸÷����NPCʵ��ID
};

// *************************************************************************** //
// �趨�س�		������->�ͻ���
// *************************************************************************** //
message CMessageSetTownResponse
{

};

// *************************************************************************** //
// �л�PKģʽ		�ͻ���->������
// *************************************************************************** //
message CMessageChangePKModeRequest
{
	optional uint32 PKMode  = 		1; 		// �ı���PKģʽ
};

// *************************************************************************** //
// �л�PKģʽ		������->�ͻ���
// *************************************************************************** //
message CMessageChangePKModeResponse
{
	optional uint32 PKMode  = 		1; 		// ��ǰ��PKģʽ
	optional uint32 Result  = 		2; 		// �л��Ľ��( ���ݴ����� )
};

// *************************************************************************** //
// �۲����װ��������		�ͻ���->������
// *************************************************************************** //
message CMessageLookPropertyRequest
{
	optional uint32 CharID		 = 		1; 		// ���۲���ҵ�CharID
	optional uint32 LookType	 =		2;		// �۲�����
};

// *************************************************************************** //
// �۲����װ��������		������->�ͻ���
// *************************************************************************** //
message CMessageLookPropertyResponse
{
	optional string			Family						 = 		1; 		// ����
	optional uint32			Sex							 = 		2; 		// �Ա�
	optional uint32			PKValue						 = 		3; 		// PKֵ
	optional uint32			MetierID					 = 		4; 		// ְҵ
	optional PBItemBox		Equipment					 = 		5; 		// ���װ��
	optional uint32			CharID						 = 		6; 		// ���۲��ߵ�CHARID
	optional string			Name						 = 		7; 		// ���۲�������
	optional uint32			FaceType					 = 		8; 		// ͷ��ID
	optional string			IndividualityIdiograph		 = 		9; 		// ����ǩ��
	optional uint32			Level						 = 		10; 		// �ȼ�
	optional string			Title						 = 		11; 		// �ƺ�
	optional uint32			NationID					 = 		12; 		// ����
	optional string			Corps						 = 		13; 		// ����
	optional uint32			Honor						 = 		14; 		// ��ѫ
	optional uint32			KillNum						 = 		15; 		// ɱ����
	optional string			Mate						 = 		16; 		// ��ż
	optional PBWizard		Wizard						 =		17;		// �Ż�
	optional uint32			LookType					 =		18;		// �۲�����
	optional uint32			VipFlag						 =		19;		// vip ��־
	optional uint32			CountryID					 =		20;		// ����
	optional uint32			Result						 =		21;		// ��ѯ���	
};

// *************************************************************************** //
// �۲����װ��������		sceneserver->router->sceneserver
// *************************************************************************** //
message CMessageLookPropertyRouterRequest
{
	optional CMessageRouter		Router			 = 		1; 
	optional uint32				LookType		 =		2;
};

// *************************************************************************** //
// �۲����װ��������		sceneserver->router->sceneserver
// *************************************************************************** //
message CMessageLookPropertyRouterResponse
{
	optional CMessageRouter						Router				 = 		1; 
	optional CMessageLookPropertyResponse		EquipmentInfo		 = 		2; 
};


// *************************************************************************** //
// CMessageFuncResultCallBack ��Ϸ������ -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageFuncResultCallBack
{
	optional uint32 EntityID  = 		1; 
	optional uint32 ResultNumber  = 		2; 		// �������
	repeated PBFuncResult FuncResult  = 		3; 
	optional uint32	PosY  = 		4; 
	optional uint32	PosX  = 		5; 
};
// *************************************************************************** //
// CMessageThrowStorItemRequest   ��Ϸ������->��Ϸ�ͻ���
// *************************************************************************** //
message CMessageThrowStorItemRequest
{
	optional uint32 Num    = 		1; 	
	optional uint32 Index  = 		2; 
};
// *************************************************************************** //
// CMessageThrowStorItemRequest   ��Ϸ�ͻ���->��Ϸ������
// *************************************************************************** //
message CMessageThrowStorItemResponse
{
	optional uint32 Index  = 		1; 
	optional uint32 Num    = 		2; 		
};
// *************************************************************************** //
// CMessageThrowStorItemRequest   ��Ϸ������->��Ϸ�ͻ���
// *************************************************************************** //
message CMessageNotifyItemBinded
{
	optional uint32 ItemPos    = 		1; 		 //  ��Ʒ�ķ���λ��ESlotType
	optional uint32 ItemIndex  = 		2;        //  ��Ʒ�ڰ������������
	optional uint32	BindStatus =		3;
};

// *************************************************************************** //
// CMessageNotifyStorItem   ��Ϸ������->��Ϸ�ͻ���
// *************************************************************************** //
message CMessageNotifyStorItem
{			
	optional PBItemBox		Storage			= 1; 			// ��Ҳֿ�	
	optional uint32			StorMoney		= 2;			// �洢�ڲֿ�ķǰ󶨽�Ǯ
	optional uint32			StorBindMoney	= 3;			// �洢�ڲֿ�����İ󶨽�Ǯ	
};

// *************************************************************************** //
// CMessageTaskCollectRequest   ��Ϸ�ͻ���->��Ϸ������
// *************************************************************************** //
message CMessageTaskCollectRequest
{
	optional uint32 EntityID  = 		1; 
};

// *************************************************************************** //
// CMessageChangeHonorNotify   ��Ϸ������->��Ϸ�ͻ���
// *************************************************************************** //
message CMessageChangeHonorNotify
{
	optional uint32 KillNum			 = 		1; 	   //  ɱ����	
	optional int32 ChangeHonor	  	 = 		2;        //  ��ѫ�ĸı�ֵ
	optional uint32 TotalHonor       = 		3; 	   //  ��ѫ�ĵ�ǰֵ
};

// *************************************************************************** //
// CMessageHonorToExpRequest   ��Ϸ�ͻ���->��Ϸ������
// *************************************************************************** //
message CMessageHonorToExpRequest
{
	optional int32 ChangeHonor		 = 		1; 		// �һ��Ĺ�ѫֵ
};
// *************************************************************************** //
// CMessageChangeHelpStaus   ��Ϸ�ͻ���->��Ϸ������
// *************************************************************************** //
message CMessageChangeHelpStaus
{
	optional uint32 Status  = 		1; 	
	optional uint32 Index   = 		2; 
};

// *************************************************************************** //
// CMessageObtainDiploidTimeRequest   ��Ϸ�ͻ���->��Ϸ������
// *************************************************************************** //

message CMessageObtainDiploidTimeRequest
{
	optional uint32	Index  = 		1; 			// ��ȡ��ʽ��� 
	optional uint32 NpcEntityID  = 		2;   // ������ڲ����İ󶨸÷����NPCʵ��ID
};

//******************************************************
// CMessageObtainDiploidResponse
//******************************************************

message CMessageObtainDiploidResponse
{
	optional uint32	Time	 = 		1; 	// �ɹ�:˫��ʱ���ۼ�;ʧ��:���ܻ�ʣ��˫��(��λ:����)
	optional uint32	RtnCode  = 		2; 	// ��ȡ�ɹ�(true)?ʧ��(false)
};

//******************************************************
// CMessageFreezeDiploidRequest
//******************************************************

message CMessageFreezeDiploidRequest
{
	optional uint32 NpcEntityID  = 		1;     // ������ڲ����İ󶨸÷����NPCʵ��ID
	optional uint32 Type  = 		2; 			// ����: true; �ⶳ: false
};

//******************************************************
// CMessageFreezeDiploidResponse
//******************************************************

message CMessageFreezeDiploidResponse
{
	optional uint32 Time  = 		1; 			// ʱ��(��λ:����)
	optional uint32 Type  = 		2; 			// ����: true; �ⶳ: false
};

//******************************************************
// CMessageQueryRemainDiploid
//******************************************************

message CMessageQueryRemainDiploid
{
	optional uint32 NpcEntityID  = 		1;     // ������ڲ����İ󶨸÷����NPCʵ��ID
};

//******************************************************
// CMessageRemainDiploidNotice
//******************************************************

message CMessageRemainDiploidNotice
{
	optional uint32 Time  = 		1; 		// ʣ��ʱ�� (��λ:����)
};

message CMessageActivityDiploidNotice
{
	optional uint32	Type = 1;	// true:����;false:�ر�
	optional uint32 BeginTime = 2;	// ʱ*60+����(�磺 9��30Ϊ9*60+30),����
	optional uint32	EndTime = 3;	// ����ʱ�䣬����
};
//// *************************************************************************** //
//// CMessageClickBindSeviceRequest   ��Ϸ�ͻ���->��Ϸ������
//// *************************************************************************** //
//message CMessageClickBindSeviceRequest
//{
//	optional uint32 EntityID = 1;
//};
//// *************************************************************************** //
//// CMessageClickBindServiceResponse   ��Ϸ������->��Ϸ�ͻ���
//// *************************************************************************** //
//message CMessageClickBindServiceResponse
//{
//	optional uint32 EntityID = 1;
//};

// *************************************************************************** //
// CMessageOpenServiceRequest   ��Ϸ�ͻ���->��Ϸ������
// *************************************************************************** //
message CMessageOpenServiceRequest
{
	optional uint32 ServiceID	 = 		1;  // ������
	optional uint32 EntityID	 = 		2;  // ����ǵ��NPC��������npc id.
}

// *************************************************************************** //
// CMessageClickBindServiceResponse   ��Ϸ������->��Ϸ�ͻ���
// *************************************************************************** //
message CMessageOpenServiceResponse
{
	optional uint32 ServiceID	 = 		1;  // ������
	optional int32	ErrorCode	 = 		2;  // �����룻 0 �ɹ�
}

// *************************************************************************** //
// CMessageAddEqtForResumeBindReq   ��Ϸ�ͻ���->��Ϸ������
// ������Ҫȡ������ֶ��󶨵���Ʒ������
// *************************************************************************** //
message CMessageAddEqtForResumeBindRequest
{
	optional uint32 EqtIndex  = 		1; 
};
// *************************************************************************** //
// CMessageAddEqtForResumeBindResponse   ��Ϸ������->��Ϸ�ͻ���
// ������Ҫȡ������ֶ��󶨵���Ʒ�Ļ�Ӧ
// *************************************************************************** //
message CMessageAddEqtForResumeBindResponse
{
	optional uint32 EqtIndex  = 		1; 
}; 

// *************************************************************************** //
// CMessageTakeEqtForResumeBindRequest   ��Ϸ�ͻ���->��Ϸ������
// ȡ����Ҫȡ������ֶ��󶨵���Ʒ������
// *************************************************************************** //
message CMessageTakeEqtForResumeBindRequest
{
	optional uint32 EqtIndex  = 		1; 
};

// *************************************************************************** //
// CMessageTakeEqtForResumeBindResponse   ��Ϸ�ͻ���->��Ϸ������
// ȡ����Ҫȡ������ֶ��󶨵���Ʒ�Ļ�Ӧ
// *************************************************************************** //
message CMessageTakeEqtForResumeBindResponse
{
	optional uint32 EqtIndex  = 		1; 	
};

// *************************************************************************** //
// CMessageResumeBindRequest   ��Ϸ�ͻ���->��Ϸ������
// ȡ������ֶ��󶨵�����
// *************************************************************************** //
message CMessageResumeBindRequest
{
	optional uint32 EqtIndex  = 		1; 
};

// *************************************************************************** //
// CMessageResumeBindResponse   ��Ϸ�ͻ���->��Ϸ������
// ȡ������ֶ��󶨵Ļ�Ӧ
// *************************************************************************** //
message CMessageResumeBindResponse   
{
	optional uint32 EqtIndex  = 		1; 
};

// *************************************************************************** //
// CMessageServerRefreshNotify   ��Ϸ������->��Ϸ�ͻ���
// *************************************************************************** //
message CMessageServerRefreshNotify   
{
};

// *************************************************************************** //
// CMessageUseContinuedSkillRequest ��Ϸ�ͻ��� -> ��Ϸ������
// *************************************************************************** //
message CMessageUseContinuedSkillRequest
{
	optional uint32 SkillID  = 		1; 		// ����ID
	optional uint32 PosY  = 		2; 			// �������ĵ�Y����
	optional uint32 Index  = 		3; 			// �������� ( ��SkillList�е������±� )
	optional uint32 EntityID  = 		4; 		// ����ʹ����ID
	optional uint32 ListID  = 		5; 			// �ͻ������ڱ�ʾ�����Ⱥ�����к�
	repeated uint32 EntityIDList  = 		6; 	// Ⱥ��������ʵ���б�
	optional uint32 PosX  = 		7; 			// �������ĵ�X����
};

// *************************************************************************** //
// CMessageUseContinuedSkillNotify ��Ϸ������  -> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageUseContinuedSkillNotify
{
	optional uint32 SkillID  = 		1; 		// ����ID
	optional uint32 PosY  = 		2; 			// �������ĵ�Y����
	optional uint32 PosX  = 		3; 			// �������ĵ�X����
	optional uint32 EntityID  = 		4; 		// ����ʹ����ID
};

// *************************************************************************** //
// CMessageClickRedStoneRequest    ��Ϸ�ͻ���->��Ϸ������
// ʹ���ڵ�������
// *************************************************************************** //
message CMessageClickRedStoneRequest   
{
	optional uint32   RedStoneID  = 		1; 		// �ڵ���ʵ��ID
};

// *************************************************************************** //
// CMessageClickRedStoneResponse   ��Ϸ������->��Ϸ�ͻ���
// ʹ���ڵ��Ļ�Ӧ
// *************************************************************************** //
message CMessageClickRedStoneResponse   
{
	optional uint32	  Result	  = 		1; 		// ʹ�ý����1��ʾ����ʹ�ã�0 ��ʾ����ʹ��
	optional uint32   RedStoneID  = 		2; 		// �ڵ���ʵ��ID
};

// *************************************************************************** //
// CMessageStopRedStoneTimer   ��Ϸ������->��Ϸ�ͻ���
// ֹͣ�ڵ�����
// *************************************************************************** //
message CMessageStopRedStoneTimer
{
	optional uint32   RedStoneID  = 		1; 		// �ڵ���ʵ��ID	
};


// *************************************************************************** //
// CMessageRedStoneTimerEnd   ��Ϸ�ͻ���->��Ϸ������
// �ڵ��������
// *************************************************************************** //
message CMessageRedStoneTimerEnd
{
	optional uint32   RedStoneID  = 		1; 		// �ڵ���ʵ��ID
};

// *************************************************************************** //
// CMessageExpMagicEnd   ��Ϸ������->��Ϸ�ͻ���
// ��������
// *************************************************************************** //
message CMessageExpMagicEnd
{
	optional uint32   RedStoneID  = 		1; 		// �ڵ���ʵ��ID
};

// *************************************************************************** //
// CMessageChangeRestoneStaus   ��Ϸ������->��Ϸ�ͻ���
// ��ȡ�ڵ������֪ͨ��֪ͨ������Ч
// *************************************************************************** //
message CMessageChangeRestoneStaus
{
	optional uint32   Status		 = 		1; 		// 1��ʾ��Ҵ�������״̬��0��ʾû������״̬
	optional uint32   RedstoneTmpID	 = 		2; 		// �ڵ���ģ��ID
	optional uint32	  EntityID		 = 		3; 		// ʵ��ID
};


// *************************************************************************** //
// CMessageClickWelfareRequest   ��Ϸ�ͻ���->��Ϸ������
// ���ÿ���ʴ�ķ�������
// *************************************************************************** //
message CMessageClickWelfareRequest
{
	optional uint32   EntityID  = 		1; 		// npc��ʵ��id
};

// *************************************************************************** //
// CMessageClickWelfareResponse  ��Ϸ������->��Ϸ�ͻ���
// ���ÿ���ʴ�ķ���Ļ�Ӧ
// *************************************************************************** //
message CMessageClickWelfareResponse
{
	optional uint32   Result    = 		1; 		// ���	1 ��ʾ���Դ��� 0�Ѿ������ ��������ʾ����ȷ��npc״̬  
	optional uint32   EntityID  = 		2; 		// npc��ʵ��id
};


// *************************************************************************** //
// CMessageChangeCampRequest  ��Ϸ������->��Ϸ�ͻ���
// �ı���Ӫ����
// *************************************************************************** //
message CMessageChangeCampRequest
{
	optional uint32		CampID  = 		1; 
};

message CMessageChangeCampResponse
{
	optional uint32		CampID  = 		1; 
};


message PBPropertyValue
{
	optional uint32		InitValue	 = 		1; 
	optional uint32		DeltaValue	 = 		2; 
};

message PBInformation
{
	optional PBPropertyValue		PDefence	  = 		1; 
	optional uint32					RemainPoint	  = 		2;  // ʣ��Ǳ�ܵ�
	repeated uint32					SkillIndex	  = 		3; 
	optional PBPropertyValue		NormalDuck	  = 		4; 
	optional uint32					AddFixDamage  = 		5; 
	optional uint32					DecPerPDamage = 		6; 
	optional uint32					DecFixMDamage = 		7; 
	optional PBPropertyValue		IgnoreDuck	  = 		8; 
	repeated uint32					ResDef		  = 		9; 
	optional uint32					NormalHitRate = 		10; 
	optional uint32					SkillHitRate  = 		11; 
	optional PBPropertyValue		Con			  = 		12; 
	optional uint32					AttackType	  = 		13; 
	optional uint32					StealHP		  = 		14; 
	repeated uint32					ResAtt		  = 		15; 
	optional uint32					DecPerMDamage = 		16; 
	optional PBPropertyValue		DeathValue	  = 		17; 
	optional PBPropertyValue		Wis			  = 		18; 
	optional PBPropertyValue		Str			  = 		19; 
	optional PBPropertyValue		MaxMP		  = 		20; 
	optional uint32					DecFixPDamage = 		21; 
	optional uint32					StealMP		  = 		22; 
	optional PBPropertyValue		Speed		  = 		23; 
	repeated uint32					IncLevel	  = 		24; 	
	optional PBPropertyValue		Sta			  = 		25; 
	optional PBPropertyValue		Spr			  = 		26; 
	optional PBPropertyValue		DeathRate	  = 		27; 
	optional PBPropertyValue		SkillDuck	  = 		28; 
	optional uint32					AddPerDamage  = 		29; 
	optional uint32					ReduceLevel	  = 		30; 
	repeated uint32					ReduceCool	  = 		31;
	optional PBPropertyValue		MDefence	  = 		32; 
	optional PBPropertyValue		DeathDefense  = 		33; 
	optional PBPropertyValue		MaxAP		  = 		34; 
	optional PBPropertyValue		MaxHP		  = 		35; 
	optional uint32					RemainSkillPoint  = 	36;  // ʣ�༼�ܵ㣨ֻ���˲��У�
	optional PBPropertyValue		PAttackMax	  =			37;
	optional PBPropertyValue		PAttackMin	  =			38;
	optional PBPropertyValue		MAttackMax	  =			39;
	optional PBPropertyValue		MAttackMin	  =			40;
	repeated uint32					EquipWizard	  =			41;
};

// *************************************************************************** //
// CMessageRefreshPropertyNotify   ��Ϸ������->��Ϸ�ͻ���
// *************************************************************************** //
message CMessageRefreshPropertyNotify   
{
	optional PBInformation			Information	  = 		1; 	
	optional uint32					EntityID  = 		2; 
	optional uint32					CurHP  = 		3; 
	optional uint32					CurMP  = 		4; 
	optional uint32                 Level  = 		5; 
	optional uint32					CurAP  =		6;
};

// *************************************************************************** //
// CMessageChangePKTypeNotify   ��Ϸ������->��Ϸ�ͻ���
// *************************************************************************** //
message CMessageChangePKTypeNotify   
{
	optional uint32		EntityID  = 		1; 
	optional uint32		PKType	  = 		2; 
};

// *************************************************************************** //
// CMessageRedstoneStarted   ��Ϸ������->��Ϸ�ͻ���
// �ڵ����ɹ�����
// *************************************************************************** //
message CMessageRedstoneStarted  
{
	optional string Name  = 		1;     // �������	  
};

// *************************************************************************** //
// CMessageActiveRemoveBuffRequest   ��Ϸ�ͻ���->��Ϸ������
// *************************************************************************** //
message CMessageActiveRemoveBuffRequest
{
	optional uint32 BuffID  = 		1;     // ��Ҫ�ֶ������BUFFID	
	repeated uint32 ListID	=		2;
};
// *************************************************************************** //
// CMessageBeginRedstoneMagicNotify   ��Ϸ������->��Ϸ�ͻ���
// �ڵ���ʼ������֪ͨ
// *************************************************************************** //
message CMessageBeginRedstoneMagicNotify
{
	optional uint32 EntityID  = 		1;     // �ڵ���ʵ��ID	  
};

// *************************************************************************** //
// CMessageListIbItemsRequest �̳���Ʒ�б����� 
// *************************************************************************** //
/*
message CMessageListIbItemsRequest
{
};

message CMessageListIbItemsResponse
{
	repeated PBIbItemOnSale ibitems  = 		1;         // �̳���Ʒ�б�
	repeated PBIbMoney Money  = 		2;               // ���ʺ��ϵĽ�Ǯ
};

message PBLocation
{
	optional uint32 page  = 		1;                    // ҳ��
	optional uint32 row  = 		2;                     // �к�
	optional uint32 col  = 		3;                     // �к�
};

message PBIbItem2Client
{
	optional uint32 ActiveFlag  = 		1;              // ��Ʒ�Ƿ���Ч
	optional uint32 id  = 		2;                      // ��ƷID
	optional uint32 PriceUnit  = 		3;               // �ۼ۱���
	optional uint32 PriceValue  = 		4;              // ��Ʒ�ĵ���
	optional PBLocation location  = 		5;            // ��Ʒ��λ��
};

message CMessageListIbItemsResponse
{
	optional int32 CurrentMoney  = 		1;             // ��ҵ�ǰ��Ǯ��
	repeated PBIbItem2Client ibitems  = 		2;        // �̳���Ʒ�б�
};

// *************************************************************************** //
// CMessagePurchaseIbItemRequest
// *************************************************************************** //
message CMessagePurchaseIbItemRequest
{
	optional uint32 IbItemID  = 		1;        //  ���������ƷID
	optional uint32 IbItemCount  = 		2;     //  ���������Ʒ����
};

// *************************************************************************** //
// CMessagePurchaseIbItemResponse
// *************************************************************************** //
//
message CMessagePurchaseIbItemResponse
{
	optional int32 error  = 		1;              // �������, 0 �ɹ�, ���� ʧ��.
	repeated PBIbMoney money  = 		2;          // ���׺�ʣ��Ľ�Ǯ
};

message CMessagePurchaseIbItemResponse
{
	optional int32 RemainedMoney  = 		1;      // ���׺�ʣ��Ľ�Ǯ
	optional int32 error  = 		2;              // �������, 0 �ɹ�, ���� ʧ��.
};
*/

// *************************************************************************** //
// CMessageChangeEntityPKTypeNotify   ��Ϸ������->��Ϸ�ͻ���
// ʵ��PK���͸ı�֪ͨ
// *************************************************************************** //
message CMessageChangeEntityPKTypeNotify
{
	optional uint32 EntityID  = 		1;     // ʵ��ID	  
	optional uint32 NewType   = 		2; 	 // ��PK����
};


//**********************************
// CMessageBrushOgreNotify ˢ��֪ͨ
//**********************************

message CMessageBrushOgreNotify
{
	optional uint32	Code  = 		1; 	// ��ϢKey
};



//**********************************
// CMessageSetPassWordRequest 
// �������������
//**********************************
message CMessageSetPasswordRequest
{
	optional string PassWord  = 		1; 		// 2 ������	
}	

//**********************************
// CMessageSetPassWordRequest 
// ��������Ļ�Ӧ��Ϣ
//**********************************
message CMessageSetPasswordResponse
{
	optional uint32 Errcode		=	1; 	 // 0��ʾ���óɹ�,������ʾ������
	optional uint32	Password	=	2;	 // ���õ�����
	optional uint32	Status		=	3;	 // ����״̬
};

//**********************************
// CMessageCheckPasswordRequest 
// ������������
//**********************************
message CMessageCheckPasswordRequest
{	
	optional string PassWord  = 		1; 	// ����������
}

//**********************************
// CMessageCheckPasswordRequest 
// �������Ļ�Ӧ
//**********************************
message CMessageCheckPasswordResponse
{
	optional uint32 Errcode  =	1; 	// 0 ��ʾ�ɹ�������ʾ������
	optional uint32	Status	 =	2;	// ����״̬	
}

//**********************************
// CMessageModifyPasswordRequest 
// �޸����������
//**********************************
message CMessageModifyPasswordRequest
{
	optional string OrigPassword  = 		1; 		// ԭʼ����
	optional string NewPassword	  = 		2; 		// ������		
}

//**********************************
// CMessageModifyPasswordRequest 
// �޸�����Ļ�Ӧ
//**********************************
message CMessageModifyPasswordResponse
{
	optional uint32 Errcode		 = 	1; 	   // 0��ʾ�ɹ�������ʾ������ 	
	optional uint32	Status		 =	2;	   // ����״̬	 	
}

//**********************************
// CMessageSetPasswordOptionNotify 
// ��������ѡ��
//**********************************
message CMessageSetPasswordOptionNotify
{
	optional uint32 Option    = 		1; 		 // ��������	
};

//**********************************
// ��¯ʯ���ͱ����� 
//**********************************

message CMessageClickTeleSymbolRequest
{
	optional uint32	Index	  = 		1; 		// ��������
};

//**********************************
// ����ظ�
//**********************************
message CMessageClickTeleSymbolResponse
{
	optional uint32	Index    = 		1; 		// ��������
};

// *************************************************************************** //
// CMessageAddSlotRequest   ��Ϸ�ͻ���->��Ϸ������
// ���Ӱ�������
// *************************************************************************** //
message CMessageAddSlotRequest
{
	optional uint32 EquipIndex	=	1;		// װ����λ��
	optional uint32 ItemIndex	=	2;		// ��Ʒ��λ��
};

// *************************************************************************** //
// CMessageAddSlotResponse   ��Ϸ������->��Ϸ�ͻ���
// ���Ӱ��ۻ�Ӧ
// *************************************************************************** //
message CMessageAddSlotResponse   
{
	optional uint32 Slot  = 		1; 		// ���ӵĲ���
	optional uint32 Result  = 		2; 		// ���Ӱ��۵Ľ��
};

// *************************************************************************** //
// CMessageRemoveJewelRequest   ��Ϸ�ͻ���->��Ϸ������
// ժ����ʯ����
// *************************************************************************** //
message CMessageRemoveJewelRequest
{
	optional uint32 JewelIndex  = 		1; 		// ժ����ʯ��λ��
	optional uint32 EquipIndex	=		2;		// װ����λ��
	optional uint32	ItemIndex	=		3;		// ����λ��
};

// *************************************************************************** //
// CMessageRemoveJewelResponse   ��Ϸ������->��Ϸ�ͻ���
// ժ����ʯ��Ӧ
// *************************************************************************** //
message CMessageRemoveJewelResponse   
{
	optional uint32 Result  = 		1; 		// ժ����ʯ�Ľ��
};

// *************************************************************************** //
// CMessageJudgeRequest   ��Ϸ�ͻ���->��Ϸ������
// ����װ������
// *************************************************************************** //
message CMessageJudgeRequest
{
	optional uint32	EquipIndex	=	1;			// װ����λ��
	optional uint32	ItemIndex	=	2;			// ��Ʒ��λ��
};

// *************************************************************************** //
// CMessageJudgeResponse   ��Ϸ������->��Ϸ�ͻ���
// ����װ����Ӧ
// *************************************************************************** //
message CMessageJudgeResponse   
{
	optional uint32 Property3  = 		1; 	// �������ӵ���ֵ
	optional uint32 Result  = 		2; 		// ����װ���Ľ��
	optional uint32 Property1  = 		3; 	// �������ӵ���ֵ
	optional uint32 Property2  = 		4; 	// �������ӵ���ֵ
};

// *************************************************************************** //
// CMessagePushAddSlotRequest   ��Ϸ�ͻ���->��Ϸ������
// ���Ӱ��۷�������
// *************************************************************************** //
message CMessagePushAddSlotRequest
{
	optional uint32 Index  = 		1; 		// ���������
};

// *************************************************************************** //
// CMessagePushAddSlotResponse   ��Ϸ������->��Ϸ�ͻ���
// ���Ӱ��۷����Ӧ
// *************************************************************************** //
message CMessagePushAddSlotResponse   
{
	optional uint32 Index1  = 		1; 		// ���������
	optional uint32 Result  = 		2; 		// ����Ľ��
	optional uint32 Index2  = 		3; 		// Ŀ��λ��
};

// *************************************************************************** //
// CMessagePopAddSlotRequest   ��Ϸ�ͻ���->��Ϸ������
// ���Ӱ����ó�����
// *************************************************************************** //
message CMessagePopAddSlotRequest
{
	optional uint32 Index  = 		1; 		// �ó�������
};

// *************************************************************************** //
// CMessagePopAddSlotResponse   ��Ϸ������->��Ϸ�ͻ���
// ���Ӱ����ó���Ӧ
// *************************************************************************** //
message CMessagePopAddSlotResponse   
{
	optional uint32 Index2  = 		1; 		// �ó�λ��
	optional uint32 Index1  = 		2; 		// �ó�������
	optional uint32 Result  = 		3; 		// �ó��Ľ��
};

// *************************************************************************** //
// CMessagePushRemoveJewelRequest   ��Ϸ�ͻ���->��Ϸ������
// ժ����ʯ��������
// *************************************************************************** //
message CMessagePushRemoveJewelRequest
{
	optional uint32 Index  = 		1; 		// ���������
};

// *************************************************************************** //
// CMessagePushRemoveJewelResponse   ��Ϸ������->��Ϸ�ͻ���
// ժ����ʯ�����Ӧ
// *************************************************************************** //
message CMessagePushRemoveJewelResponse   
{
	optional uint32 Index2  = 		1; 		// Ŀ��λ��
	optional uint32 Result  = 		2; 		// ����Ľ��
	optional uint32 Index1  = 		3; 		// ���������
};

// *************************************************************************** //
// CMessagePopRemoveJewelRequest   ��Ϸ�ͻ���->��Ϸ������
// ժ����ʯ�ó�����
// *************************************************************************** //
message CMessagePopRemoveJewelRequest
{
	optional uint32 Index  = 		1; 		// �ó�������
};

// *************************************************************************** //
// CMessagePopRemoveJewelResponse   ��Ϸ������->��Ϸ�ͻ���
// ժ����ʯ�ó���Ӧ
// *************************************************************************** //
message CMessagePopRemoveJewelResponse   
{
	optional uint32 Result  = 		1; 		// �ó��Ľ��
	optional uint32 Index1  = 		2; 		// �ó�������
	optional uint32 Index2  = 		3; 		// �ó�λ��
};

// *************************************************************************** //
// CMessagePushJudgeRequest   ��Ϸ�ͻ���->��Ϸ������
// ����װ����������
// *************************************************************************** //
message CMessagePushJudgeRequest
{
	optional uint32 Index  = 		1; 		// ���������
};

// *************************************************************************** //
// CMessagePushJudgeResponse   ��Ϸ������->��Ϸ�ͻ���
// ����װ�������Ӧ
// *************************************************************************** //
message CMessagePushJudgeResponse   
{
	optional uint32 Index2  = 		1; 		// Ŀ��λ��
	optional uint32 Result  = 		2; 		// ����Ľ��
	optional uint32 Index1  = 		3; 		// ���������
};

// *************************************************************************** //
// CMessagePopJudgeRequest   ��Ϸ�ͻ���->��Ϸ������
// ����װ���ó�����
// *************************************************************************** //
message CMessagePopJudgeRequest
{
	optional uint32 Index  = 		1; 		// �ó�������
};

// *************************************************************************** //
// CMessagePopJudgeResponse   ��Ϸ������->��Ϸ�ͻ���
// ����װ���ó���Ӧ
// *************************************************************************** //
message CMessagePopJudgeResponse   
{
	optional uint32 Index1  = 		1; 		// �ó�������
	optional uint32 Result  = 		2; 		// �ó��Ľ��
	optional uint32 Index2  = 		3; 		// �ó�λ��
};

//**********************************
// CMessageStorMoneyRequest 
// �洢��Ǯ����Ϣ����
//**********************************
message CMessageStorMoneyRequest
{	 
	optional int32	StorMoney		 = 		1; 		// �洢�ķǰ󶨽�Ǯ
	optional int32	StorBindMoney	 = 		2; 		// �洢�İ󶨽�Ǯ
	optional uint32	NpcID			 =		3;		// �ֿ������npc��ʵ��ID
};	

//**********************************
// CMessageStorMoneyResponse 
// �洢��Ǯ����Ϣ����
//**********************************
message CMessageStorMoneyResponse
{
	optional uint32 Errcode		 = 		1; 	   // 0��ʾ�ɹ�������ʾ������
	optional int32 Money		 = 		2; 	   // �ֿ������еķǰ󶨽�Ǯ������
	optional int32 BindMoney	 = 		3; 	   // �ֿ������еİ󶨽�Ǯ������
	optional uint32 MoneyLmt	 = 		4; 	   // ���ƵĽ�Ǯ ��ϴ�����ʹ��
};

//**********************************
// CMessageTakeStorMoneyRequest 
// �Ӳֿ�ȡ����Ǯ������
//**********************************
message CMessageTakeStorMoneyRequest
{	
	optional int32	Money		 = 	1; 			// Ҫ�Ӳֿ�ȡ���Ľ�Ǯ������	
	optional int32	BindMoney	 = 	2; 			// Ҫ�Ӳֿ�ȡ���İ󶨽�Ǯ������
	optional uint32	NpcID		 =	3;			// npcʵ��ID
};	

//**********************************
// CMessageTakeStorMoneyResponse 
// �Ӳֿ�ȡ����Ǯ�Ļ�Ӧ��Ϣ
//**********************************
message CMessageTakeStorMoneyResponse
{ 
	optional uint32 Errcode		 = 		1; 		// 0��ʾ�ɹ�������ʾ������
	optional int32 Money		 = 		2; 		// �ֿ��������ڵķǰ󶨽�Ǯ����
	optional int32 BindMoney	 = 		3; 		// �ֿ��������ڵİ󶨽�Ǯ������
	optional uint32 MoneyLmt	 = 		4; 	   // ���ƵĽ�Ǯ ��ϴ�����ʹ��
};

//**********************************
// CMessageAddKitBagIndexRequest 
// �ڲֿ�ı�����λ���ñ�������Ϣ����
//**********************************
message CMessageAddKitBagRequest
{
	optional uint32 SrcSlot		 =		1;			// Դλ��	
	optional uint32 BagIndex	 = 		2; 			// �����ڰ����е�����
	optional uint32 DesIndex	 = 		3; 			// Ŀ����λ����
	optional uint32 DesSlot		 =		4;			// Ŀ��λ�����ڲֿⱳ�������ڰ�������
};

//**********************************
// CMessageAddKitBagIndexResponse 
// �ڲֿ�ı�����λ���ñ�������Ϣ��Ӧ
//**********************************
message CMessageAddKitBagResponse
{
	optional uint32 BagIndex	 = 		1; 			// �����ڰ����е�����
	optional uint32 Errocode	 = 		2; 			// 0��ʾ�ɹ�������ʾ������
	optional uint32 DesIndex	 = 		3; 			// Ŀ����λ����
	optional uint32 DesSlot		 =		4;			// �������õ�λ�òֿⱳ�����ǰ�������
	optional uint32	ExpiredTime	 =		5;			// �����ĵ���ʱ��
	optional uint32	BindStatus	 =		6;			// �����İ�״̬
};

//**********************************
// CMessageOpenKitBagRequest 
// �򿪲ֿⱳ����������Ϣ
//**********************************
message CMessageOpenKitBagRequest
{
	optional uint32 Index	= 		1; 					// �ֿⱳ����λ�������������õĲ���	
	optional uint32 DesSlot =		2;					// �ֿⱳ�����ǰ�������	
};

//**********************************
// CMessageOpenKitBagResponse 
// �򿪲ֿⱳ���Ļ�Ӧ��Ϣ
//**********************************
message CMessageOpenKitBagResponse
{  
	optional uint32		IfClean			= 		1; 			 // �Ƿ񸲸ǿͻ�������,��EM_KITBAGSTATUS��ʾ
	optional PBItemBox	ItemBox			= 		2; 			 // ������Ʒ
	optional uint32		Errcode			= 		3; 			 // 0��ʾ�ɹ�������ʾ������	
	optional uint32		IfInfoEnd		=		4;			 //	��Ϣ�Ƿ��ͽ���
	optional uint32		DesSlot			=		5;			 // �ֿⱳ�����ǰ�������ESlotType 
	optional uint32		KitBagIndex		=		6;			 // ������λ����
};

//**********************************
// CMessageMoveKitBagRequest 
// �򿪲ֿⱳ���Ļ�Ӧ��Ϣ
//**********************************
message CMessageMoveKitBagRequest
{
	optional uint32		DesIndex  = 		1; 
	optional uint32		SrcIndex  = 		2; 
};

// *************************************************************************** //
// CMessagePushChangeRequest   ��Ϸ�ͻ���->��Ϸ������
// ת�����Է�������
// *************************************************************************** //
message CMessagePushChangeRequest
{
	optional uint32 Index  = 		1; 		// ���������
};

// *************************************************************************** //
// CMessagePushChangeResponse   ��Ϸ������->��Ϸ�ͻ���
// ת�����Է����Ӧ
// *************************************************************************** //
message CMessagePushChangeResponse   
{
	optional uint32 Result  = 		1; 		// ����Ľ��
	optional uint32 Index2  = 		2; 		// Ŀ��λ��
	optional uint32 Index1  = 		3; 		// ���������
};

// *************************************************************************** //
// CMessagePopChangeRequest   ��Ϸ�ͻ���->��Ϸ������
// ת�������ó�����
// *************************************************************************** //
message CMessagePopChangeRequest
{
	optional uint32 Index  = 		1; 		// �ó�������
};

// *************************************************************************** //
// CMessagePopChangeResponse   ��Ϸ������->��Ϸ�ͻ���
// ת�������ó���Ӧ
// *************************************************************************** //
message CMessagePopChangeResponse   
{
	optional uint32 Index2  = 		1; 		// �ó�λ��
	optional uint32 Result  = 		2; 		// �ó��Ľ��
	optional uint32 Index1  = 		3; 		// �ó�������
};

// *************************************************************************** //
// CMessageChangeRequest   ��Ϸ�ͻ���->��Ϸ������
// ת����������
// *************************************************************************** //
message CMessageChangeRequest
{
	optional uint32 Type		=	1; 		// ת��������
	optional uint32	EquipIndex	=	2;		// װ����λ��
	optional uint32 ItemIndex	=	3;		// ת��ʯ��λ��
};

// *************************************************************************** //
// CMessageChangeResponse   ��Ϸ������->��Ϸ�ͻ���
// ת�����Ի�Ӧ
// *************************************************************************** //
message CMessageChangeResponse   
{
	optional uint32 Type  = 		1; 		// ת��������
	optional uint32 Result  = 		2; 		// ת���Ľ��
};

// *************************************************************************** //
// CMessagePushJewComRequest   ��Ϸ�ͻ���->��Ϸ������
// ��ʯ�ϳɷ�������
// *************************************************************************** //
message CMessagePushJewComRequest
{
	optional uint32 Index  = 		1; 		// ���������
};

// *************************************************************************** //
// CMessagePushJewComResponse   ��Ϸ������->��Ϸ�ͻ���
// ��ʯ�ϳɷ����Ӧ
// *************************************************************************** //
message CMessagePushJewComResponse   
{
	optional uint32 Result  = 		1; 		// ����Ľ��
	optional uint32 Index1  = 		2; 		// ���������
	optional uint32 Index2  = 		3; 		// Ŀ��λ��
};

// *************************************************************************** //
// CMessagePopJewComRequest   ��Ϸ�ͻ���->��Ϸ������
// ��ʯ�ϳ��ó�����
// *************************************************************************** //
message CMessagePopJewComRequest
{
	optional uint32 Index  = 		1; 		// �ó�������
};

// *************************************************************************** //
// CMessagePopJewComResponse   ��Ϸ������->��Ϸ�ͻ���
// ��ʯ�ϳ��ó���Ӧ
// *************************************************************************** //
message CMessagePopJewComResponse   
{
	optional uint32 Result  = 		1; 		// �ó��Ľ��
	optional uint32 Index2  = 		2; 		// �ó�λ��
	optional uint32 Index1  = 		3; 		// �ó�������
};

// *************************************************************************** //
// CMessageJewComRequest   ��Ϸ�ͻ���->��Ϸ������
// ��ʯ�ϳ�����
// *************************************************************************** //
message CMessageJewComRequest
{
	repeated uint32	JewelIndex		=	1;	// ��ʯ��λ��
	optional uint32	ItemIndex		=	2;	// ����λ��
};

// *************************************************************************** //
// CMessageJewComResponse   ��Ϸ������->��Ϸ�ͻ���
// ��ʯ�ϳɻ�Ӧ
// *************************************************************************** //
message CMessageJewComResponse   
{
	optional uint32 Result  = 		1; 		// �ϳɵĽ��
};

//**********************************
// CMessageListActivityMenuRequest
// ��ȡ��˵�����
//**********************************
message CMessageListActivityMenuRequest
{

};

//**********************************
// CMessageListActivityMenuResponse
// ��ȡ��˵�����
//**********************************
message PBOutlineActivity
{
	optional uint32 MenuID  = 		1;  // �˵�ID
	optional string Desc  = 		2; 	// �����
};

message CMessageListActivityMenuResponse
{
	repeated PBOutlineActivity Activity  = 		1; 
};

//**********************************
// CMessageListActivityItemRequest
// ��ȡĳ�˵��µĻ��Ʒ����
//**********************************
message CMessageListActivityItemRequest
{
	optional uint32 MenuID  = 		1;  
};

//**********************************
// CMessageListActivityItemResponse
// ��ȡĳ�˵��µĻ��Ʒ����
//**********************************
message PBItemIDCount
{
    optional uint32 ActivityID = 1; // �ID
    optional string ItemCode   = 2; // ��Ʒģ��ID
    optional uint32 ItemCount  = 3; // ��Ʒ����
};

message CMessageListActivityItemResponse
{
	optional uint32 MenuID  = 1; 	// �˵�ID
	repeated PBItemIDCount Items  = 2;  // ��Ʒ�б�
};

//**********************************
// CMessageMinusActivityItemRequest
// ��ȡĳ���Ʒ����
//**********************************
message CMessageMinusActivityItemRequest
{
	optional uint32      MenuID = 1;  // �˵�ID
	optional PBItemIDCount item = 2;	// ��ƷID
};

//**********************************
// CMessageMinusActivityItemResponse
// ��ȡĳ���Ʒ��Ӧ
//**********************************
message CMessageMinusActivityItemResponse
{
	optional int32 Result  = 		1; 	// 0: �ɹ�; 1: ʧ��
};

//**********************************
// CMessageInterruptContiuneSkillRequest
// �ͻ������������ϳ���ʩ����������
//**********************************
message CMessageInterruptContiuneSkillRequest
{
	optional uint32 SkillIndex	 = 		1; 	// ��������
	optional uint32	SkillID		 = 		2; 	// ����ID
};


//**********************************
// CMessageInterruptContiuneSkillNotify
// ������֪ͨ��ϳ���ʩ������
//**********************************
message CMessageInterruptContiuneSkillNotify
{
	optional uint32	SkillID		 = 		1; 	// ����ID
	optional uint32	EntityID	 = 		2; 	// ʵ��ID
};

// *************************************************************************** //
// CMessageMultiComRequest   ��Ϸ�ͻ���->��Ϸ������
// ���Ӻϳ�����
// *************************************************************************** //
message CMessageMultiComRequest
{
	optional uint32 ComposeID		= 		1; 		// �ϳɵĹ���
	repeated uint32 ComposeIndex	=		2;		// �ϳɵ�λ��
	optional uint32	EntityID		=		3;		// npc�һ���ʵ��ID
	optional uint32	ItemNum			=		4;		// Ҫ�Ի�������(Ŀǰֻ�м�����Ŷһ�ʹ��)
	optional uint32 ComposeType		=		5;		// �ϳɵ����ͣ��󶨣��ǰ󶨣�
	optional uint32	EquipIndex		=		6;		// ��Ҫ������װ������
};

// *************************************************************************** //
// CMessageMultiComResponse   ��Ϸ������->��Ϸ�ͻ���
// ���Ӻϳɻ�Ӧ
// *************************************************************************** //
message CMessageMultiComResponse   
{
	optional uint32 ComposeID  = 		1; 	// �ϳɵĹ���
	optional uint32 Result  = 		2; 		// �ϳɵĽ��
	optional uint32	EquipIndex	=	3;		// װ������ʱװ��������
};


//**********************************
// CMessageNotifyModifyPKValue
// ֪ͨ�ͻ����޸�PKֵ
//**********************************

message CMessageNotifyModifyPKValue
{
	optional int32	Value		 = 	1; 	// PKֵ��
	optional uint32	EntityID	 = 	2; 	// ���ID
	optional uint32	State		 =	3;	// ��1��2��3��4, ����	 
};

//**********************************
// CMessageYellowStateNotify
// ֪ͨ�ͻ������Ϊ����״̬
//**********************************

message CMessageYellowStateNotify
{
	optional uint32	EntityID	 = 		1; 	// ���ID
	optional uint32	State		 = 		2; 
};


//**********************************
// CMessageChangeAppertainings
// ֪ͨ�ͻ��˸ı���Ʒ����
//**********************************
message CMessageChangeAppertainings
{
	optional uint32 EntityID		 = 		1; 	// ��Ʒʵ��ID
	repeated uint32 Appertainings	 = 		2; 	// �޸ĺ�Ĺ���(charid),�б�Ϊ�ձ�ʾ������
}

// *************************************************************************** //
// CMessageEventNotify   ��Ϸ�ͻ���->��Ϸ������
// �����¼�֪ͨ
// *************************************************************************** //
message CMessageEventNotify
{
	optional uint32 EventID = 1;		// ֪ͨ�Ĵ�����
	repeated uint32 IntParam = 2;		// ���Ͳ���
	repeated string StringParam = 3;	// �ַ��Ͳ���	
	optional uint32 CountryID	= 4;	// ���͵�����Ӫ
};

// *************************************************************************** //
// CMessageActiveCardNotify   ��Ϸ������->��Ϸ�ͻ���
// ���Ƭ֪ͨ
// *************************************************************************** //
message CMessageActiveCardNotify   
{
	optional uint32 Type = 1;		// ����Ĳ����
	optional uint32 Pos = 2;		// ����Ĳ�λ��
	optional uint32 ItemID = 3;		// ����Ŀ�ƬID
};

// *************************************************************************** //
// CMessagePushCardRequest   ��Ϸ�ͻ���->��Ϸ������
// ���뿨Ƭ����
// *************************************************************************** //
message CMessagePushCardRequest
{
	optional uint32 Index = 1;		// ���������
};

// *************************************************************************** //
// CMessagePushCardResponse   ��Ϸ������->��Ϸ�ͻ���
// ���뿨Ƭ��Ӧ
// *************************************************************************** //
message CMessagePushCardResponse   
{
	optional uint32 Result = 1;		// ����Ľ��
	optional uint32 ItemID = 2;		// �����ID
};

// *************************************************************************** //
// CMessageTalentChangeNotify   ��Ϸ������->��Ϸ�ͻ���
// ��Ϊֵ�컯��ı�֪ͨ
// *************************************************************************** //
message CMessageTalentChangeNotify   
{
	optional uint32 TalentExp = 1;		// ��Ϊֵ��ǰֵ
	optional uint32 TalentPoint = 2;	// �컯�㵱ǰֵ
	optional uint32 TalentChange = 3;	// ��Ϊֵ�ı�
};

// *************************************************************************** //
// CMessageClickTalentPointRequest   ��Ϸ�ͻ���->��Ϸ������
// ����컯������
// *************************************************************************** //
message CMessageClickTalentPointRequest
{	
	optional uint32 Row = 1;		// ������������
	optional uint32 Col = 2;		// ������������
};

// *************************************************************************** //
// CMessageClickTalentPointResponse   ��Ϸ������->��Ϸ�ͻ���
// ����컯���Ӧ
// *************************************************************************** //
message CMessageClickTalentPointResponse   
{
	optional uint32 Result = 1;		// ����Ľ��
	optional uint32 Row = 2;		// ������������
	optional uint32 Col = 3;		// ������������
	optional uint32 TalentExp = 4;	// ��Ϊֵ��ǰֵ
	optional uint32 TalentPoint = 5;// �컯�㵱ǰֵ
	optional uint32 TalentStep = 6;	// ��ǰ����С��
};

// *************************************************************************** //
// CMessageIncreaseTalentRequest   ��Ϸ�ͻ���->��Ϸ������
// �컯��������
// *************************************************************************** //
message CMessageIncreaseTalentRequest
{	
	optional uint32 TalentStep = 1;		// �������С��
};

// *************************************************************************** //
// CMessageIncreaseTalentResponse   ��Ϸ������->��Ϸ�ͻ���
// �컯���׻�Ӧ
// *************************************************************************** //
message CMessageIncreaseTalentResponse   
{
	optional uint32 Result = 1;		// ���׵Ľ��
	optional uint32 TalentExp = 2;	// ��Ϊֵ��ǰֵ
	optional uint32 TalentPoint = 3;// �컯�㵱ǰֵ
	optional uint32 TalentStep = 4;	// ��ǰ����С��
};


// *************************************************************************** //
// CMessageAddPotentialRequest   ��Ϸ�ͻ���->��Ϸ������
// ���ӷ���Ǳ�ܵ�����
// *************************************************************************** //
message CMessageAddPotentialRequest
{
	optional uint32 KeenPoints = 1;		// �����ӵ���
	optional uint32 CalmPoints = 2;		// �����ӵ���
	optional uint32 MagicPoints = 3;	// �����ӵ���
	optional uint32 BierPoints =  4;	// �����ӵ���
	optional uint32 ImmortalPoints = 5;	// �����ӵ���
};

// *************************************************************************** //
// CMessageAddPotentialResponse   ��Ϸ������->��Ϸ�ͻ���
// ����Ǳ�ܼӵ��Ӧ
// *************************************************************************** //
message CMessageAddPotentialResponse
{
	optional uint32 Result		= 1; 	// �ӵ���  ������ӵ�һ��
};


// *************************************************************************** //
// CMessageChangeExpScaleRequest   ��Ϸ�ͻ���->��Ϸ������
// ��ҵ������⾭��������(�ٷֱ�)����
// *************************************************************************** //
message CMessageChangeExpScaleRequest
{
	optional uint32 Percent = 1;		// �ٷֱ�
};


// *************************************************************************** //
// CMessageChangeExpScaleResponse   ��Ϸ������->��Ϸ�ͻ���
// ��ҵ������⾭��������(�ٷֱ�)��Ӧ
// *************************************************************************** //
message CMessageChangeExpScaleResponse
{
	optional uint32 Result		= 1; 	// ���
};

// *************************************************************************** //
// CMessageMagicWeaponRefreshValueNotify   ��Ϸ������->��Ϸ�ͻ���
// ���������ֵˢ��
// *************************************************************************** //
message CMessageMagicWeaponRefreshValueNotify
{
	optional uint32         MWLevel         = 1;			// �����ȼ�
	optional uint64         Exp			    = 2;			// ��������
	optional uint32         Mp				= 3;			// ����ֵ
	optional uint32         Hp				= 4;			// ����ֵ
	optional uint32         CurKeenpoints   = 5;			// ��ǰ����
	optional uint32         CurCalmpoints	= 6;			// ��ǰ����
	optional uint32         CurMagicpoints	= 7;			// ��ǰ����
	optional uint32         CurBierpoints   = 8;			// ��ǰ����
	optional uint32         CurImmortalpoints = 9;			// ��ǰ����
	optional uint32         LeftPoints      = 10;			// ��ǰʣ��Ǳ�ܵ�
	optional uint32         ProSpir			= 11;			// ����
	optional uint32         ProcessVal      = 12;			// ��ǰ����ֵ
	optional uint32         LeftSkillPoints = 13;			// ��ǰʣ�༼�ܵ�
	optional uint32         IncMp		    = 14;			// ����ֵÿ�λָ�����
	optional uint32         IncHp		    = 15;			// ����ֵÿ�λָ�����
	optional uint32         ProBase         = 16;			// ���Ի���ֵ
	optional uint32         ProUp			= 17;			// ���Գɳ�ֵ
	optional uint32         ProEff			= 18;			// ����Ӱ���
	optional int32          Index			= 19;			// �������� -1��ʾ���ϵ�
	optional uint32         MaxMp			= 20;			// ����ֵ����
	optional uint32         MaxHp			= 21;			// ����ֵ����
	optional uint32			NextActBoxIndex	= 22;			// ��һ��Ҫ�����box����
	optional uint32			PrintedQL		= 23;			// ӡ�ǵ�����ID
};

// *************************************************************************** //
// CMessageUpdateTitleNotice   ��Ϸ������->��Ϸ�ͻ���
// ֪ͨ�ͻ��˸��³ƺ�(ֱ���滻ԭ�гƺš����³ƺ��б�)
// *************************************************************************** //

message CMessageUpdateTitleNotice
{
	optional uint32	IsBatch = 1;	// �Ƿ����������³ƺ��б�
	optional uint32	Type = 2;		// �ƺŸ������ͣ�0-ֱ���滻��1-����ƺ��б�2-�ƺ�����
	optional uint32	TitleID	 =3;	// �ƺ�ID������ƺ���Ϣ���ģ���Լ�ȡ	
	repeated uint32	TitleList = 4;	// ������������³ƺ��б�����������ȡ�ƺ�ID
	optional uint32	Time	= 5;	// �ƺ� ��ֹ����
	repeated uint32	TimeList = 6;	// �ƺ� ��ֹ�����б�	����������ʱ��
};

message CMessageSelectTitleRequest
{
	optional uint32	TitleID = 1;	// �ƺ�ID
};

// �ͻ�������ѡ��ƺ�֮�󣬷������Ὣѡ��ĳƺŹ㲥�ɼ���Χ
message CMessageUpdateCurrentTitleNotice
{
	optional uint32	CharID		= 1;	// �����ƺŵ�����
	optional uint32	TitleID		= 2; // �ƺ�ID
	optional string	TitleName	= 3; // �ƺ�����(����������ͬ��ͬһ�ƺŲ�ͬ��ʾ)
};

// *************************************************************************** //
// CMessageActiveSkillBoxNotify   ��Ϸ������->��Ϸ�ͻ���
// ����ܿ�֪ͨ(û���� �ռ���ֻ�Ǹ��տ�)
// *************************************************************************** //
message CMessageActiveSkillBoxNotify
{
	repeated uint32	Index = 1;	// ���� 0��ʼ
};

// *************************************************************************** //
// CMessageInsertSkillNotify   ��Ϸ������->��Ϸ�ͻ���
// ��������¼���֪ͨ �ڼ��������������ᷢ�����Ϣ֪ͨ�ͻ����¼Ӽ��ܻ��滻���м���
// *************************************************************************** //
message CMessageInsertSkillNotify
{
	optional uint32	Index	 = 1;	// ���� 0��ʼ
	optional uint32	SkillID  = 2;	// ����ID
	optional uint32	CurLevel = 3;	// ���ܵ�ǰ�ȼ�
	optional uint32	Reason   = 4;	// ԭ��1=�������� 2=�ֹ�����
	optional uint32	ActedNum = 5;	// �Ѽ�������
	optional uint32	BookID   = 6;	// ��ʹ�õļ������ģ��ID
	optional uint32	BagIndex = 7;	// �����ڰ��������
};

// *************************************************************************** //
// CMessageMWAddSkillPointsRequest   ��Ϸ�ͻ���->��Ϸ������
// ���� �Ӽ��ܵ�����
// *************************************************************************** //
message CMessageMWAddSkillPointsRequest
{
	optional uint32	Index	= 1;	// ���ܿ����� 0��ʼ
};
// *************************************************************************** //
// CMessageMWAddSkillPointsResponse   ��Ϸ������->��Ϸ�ͻ���
// ���� �Ӽ��ܵ��Ӧ
// *************************************************************************** //
message CMessageMWAddSkillPointsResponse
{
	optional uint32	Index	= 1;	// ���ܿ����� 0��ʼ
};

// *************************************************************************** //
// CMessageMWJudgeSkillRequest   ��Ϸ�ͻ���->��Ϸ������
// ���� ������������(�����˲��ܼ���)
// *************************************************************************** //
message CMessageMWJudgeSkillRequest
{
	optional uint32	Index	= 1;	// ���ܿ����� 0��ʼ
	optional uint32 NpcEntityID		= 2;	// ���в�����NPCʵ��ID
};


// *************************************************************************** //
// ��ҷŷ�����ȥ ����
// *************************************************************************** //
message CMessageLockMWInBagRequest
{
	optional uint32 ItemIndex			 = 		1; 	// ��������
	optional uint32 LockType			 = 		2; 	// ��������  ��enMWLockType
};

// *************************************************************************** //
// ��ҷŷ�����ȥ �������� ��Ӧ
// *************************************************************************** //
message CMessageLockMWInBagResponse
{
	optional uint32 ItemIndex			 = 		1; 	// ����
	optional uint32 LockType			 = 		2; 	// ��������  ��enMWLockType
};


// *************************************************************************** //
// ���ȡ�·��� �������� ����
// *************************************************************************** //
message CMessageMWTakeOffItemRequest
{
	optional uint32 LockType			 = 		1; 	// ��������  ��enMWLockType
};

// *************************************************************************** //
// CMessageMWJudgePropertyRequest   ��Ϸ�ͻ���->��Ϸ������
// ���� ������������
// *************************************************************************** //
message CMessageMWJudgePropertyRequest
{
	optional uint32  NpcEntityID		= 1;	// ���в�����NPCʵ��ID
	optional uint32  MWIndex			= 2;	// �����ڰ����������
	optional uint32  StoneIndex			= 3;	// ʯͷ�ڰ����������
};


// *************************************************************************** //
// CMessageMWJudgePropertyResponse   ��Ϸ�ͻ���->��Ϸ������
// ���� �������Ի�Ӧ
// *************************************************************************** //
message CMessageMWJudgePropertyResponse
{
	optional uint32  Result		  =1;		// ������� 0=�ɹ�
	optional uint32  BagIndex     =2;		// �����ڰ����������
};

// *************************************************************************** //
// CMessageMWUseBookRequest   ��Ϸ�ͻ���->��Ϸ������
// ���� ʹ�ü���������
// *************************************************************************** //
message CMessageMWUseBookRequest
{
	optional uint32  MWIndex	  =1;		// ��������
	optional uint32  BoxIndex	  =2;		// �������ܿ�����
	optional uint32  BagIndex     =3;		// �������ڰ����������
};


// *************************************************************************** //
// CMessageInitialLifeSkillRequest   ��Ϸ�ͻ���->��Ϸ������
// ����ܵ���������
// *************************************************************************** //
message CMessageInitialLifeSkillRequest
{
	optional uint32	LifeSkillType	= 1;		// �����
	optional uint32	EntityID		= 2;		// ʵ��ID
};

// *************************************************************************** //
// CMessageInitialLifeSkillResponse   ��Ϸ������->��Ϸ�ͻ���
// ����ܵ����Ż�Ӧ
// *************************************************************************** //
message CMessageInitialLifeSkillResponse
{
	optional uint32 Errcode				= 1;		// ������
	optional uint32	LifeSkillType		= 2;		// ���������
	optional uint32 LifeSkillLevel		= 3;		// ����ܵȼ�
	optional uint32 SpecializeDegree	= 4;		// ������
	optional uint32 LifeSkillKind		= 5;		// �������������ܻ��Ǹ��޼���
};			


// *************************************************************************** //
// CMessageLevelUPLifeSkillRequest   �ͻ���->������ 
// ����ܽ��׵�����
// *************************************************************************** //
message CMessageLevelUPLifeSkillRequest
{
	optional uint32 LifeSkillType		= 1;		// ���������
	optional uint32	EntityID			= 2;		// ʵ��ID
};										

// *************************************************************************** //
// CMessageLevelUPLifeSkillResponse   ������->�ͻ���
// ����ܽ��׵Ļ�Ӧ
// *************************************************************************** //
message CMessageLevelUPLifeSkillResponse
{
	optional uint32 Errcode				= 1;	// ������
	optional uint32 LifeSkillType		= 2;	// ��������
	optional uint32 Specializedegree	= 3;	// ������
	optional uint32 LifeSkillLevel		= 4;	// ����ܵȼ�
};

// *************************************************************************** //
// CMessageStudyComposeRequest   �ͻ���->������
// ѧϰ�µļ����䷽������
// *************************************************************************** //
message CMessageStudyComposeRequest
{
	optional uint32 ComPoseID		= 1;		// �䷽ID
	optional uint32 StudyWay		= 2;		// ѧϰ�䷽�ķ�ʽ(EM_ComposeGetWay)
	optional uint32 EntityID		= 3;		// npcʵ��ID,ͬ��npcѧϰ��
	optional uint32 Value			= 4;		// ����������䷽�Ļ�,�ǻ���	
	optional uint32	LifeSkillType	= 5;		// ���������
	optional uint32 SkillKind		= 6;		// �������䷽ʱ�ķ��࣬����⿵ļ壬����
	repeated uint32	MatierialIndex	= 7;		// ��������
};

// *************************************************************************** //
// CMessageStudyComposeResponse   ������->�ͻ���
// ѧϰ�µļ����䷽�Ļ�Ӧ��Ϣ
// *************************************************************************** //
message CMessageStudyComposeResponse
{
	optional uint32 Errcode				=	1;		// ������
	optional uint32 ComposeID			=	2;		// �䷽ID
	optional uint32 SpecializeDegree	=	3;		// ������
	optional uint32 LifeSkillType		=	4;		// ���������	
	optional uint32 StudyWay			=	5;		// ѧϰ�䷽�ķ�ʽ(EM_ComposeGetWay)
};															 

// *************************************************************************** //
// CMessageSetMagicStone   �ͻ���->������
// ��ħ��������Ϣ
// *************************************************************************** //
message CMessageSetMagicStoneRequest
{  
	optional uint32	MagicStoneIndex		=	1;		// ��ħʯ������
	optional uint32 EquipIndex			=	2;		// װ��������
	optional uint32	EquipSlot			=	3;		// װ�����ڵİ�������
};

// *************************************************************************** //
// CMessageSetMagicStoneResponse   ������->�ͻ���
// ��ħ����Ϣ��Ӧ
// *************************************************************************** //
message CMessageSetMagicStoneResponse
{
	optional uint32 Errcode				=	1;		// ������	
	optional uint32 EquipIndex			=	2;		// װ��������	
	optional uint32 AttributeID			=	3;		// ����ID
	optional uint32	MagicNum			=	4;		// װ����ħ�������ֵ
	optional uint32	MagicStoneID		=	5;		// ��ħʯID		
	optional uint32	EquipSlot			=	6;		// װ�����ڵİ�������
};

// *************************************************************************** //
// CMessageForgetSkillRequest   �ͻ���->������
// ��������ܵ�����
// *************************************************************************** //
message CMessageForgetSkillRequest
{  
	optional uint32	LifeSkillType		=	1;		// ���������	
};

// *************************************************************************** //
// CMessageForgetSkillRequest   �ͻ���->������
// ��������ܵĻ�Ӧ
// *************************************************************************** //
message CMessageForgetSkillResponse
{  
	optional uint32 Errcode				=	1;			// ������
	optional uint32 LifeSkillType		=	2;			// ���������
};

// *************************************************************************** //
// CMessageDecompoundEquipRequest   �ͻ���->������
// �ֽ�װ��������
// *************************************************************************** //
message CMessageDecompoundEquipRequest
{  
	optional uint32	EquipIndex		=	1;		// װ��������	
	optional uint32 Slot			=	2;		// ��������
};

// *************************************************************************** //
// CMessageDecompoundEquipRequest   �ͻ���->������
// �ֽ�װ���Ļ�Ӧ��Ϣ
// *************************************************************************** //
message CMessageDecompoundEquipResponse
{  
	optional uint32 Errcode			=	1;		// ������	
	optional uint32	EquipIndex		=	2;		// װ��������	
	optional uint32 Slot			=	3;		// ��������
};

// *************************************************************************** //
// CMessageAddMaterialRequest   �ͻ���->������
// ���ò��ϵ�����
// *************************************************************************** //
message CMessageAddMaterialRequest
{		
	optional uint32	MaterialIndex		=	1;		// ���ϵ�����	
	optional uint32	PosIndex			=	2;		// ���õ�λ������
	optional uint32 Slot				=	3;		// ��������
};

// *************************************************************************** //
// CMessageAddMaterialResponse   ������->�ͻ���
// ���ò��ϵĻ�Ӧ
// *************************************************************************** //
message CMessageAddMaterialResponse
{  
	optional uint32	Errcode				=	1;		// ������
	optional uint32	MaterialIndex		=	2;		// ���ϵ�����	
	optional uint32	PosIndex			=	3;		// ���õ�λ������
};


// *************************************************************************** //
// CMessageTakeMaterialRequest   �ͻ���->������
// ȡ�²��ϵ�����
// *************************************************************************** //
message CMessageTakeMaterialRequest
{
	optional uint32	PosIndex			=	1;		// ��ȡ�µĲ������ڵ�λ������
};

// *************************************************************************** //
// CMessageAddMaterialResponse   ������->�ͻ���
// ȡ�²��ϵĻ�Ӧ
// *************************************************************************** //
message CMessageTakeMaterialResponse
{ 
	optional uint32	Errcode			=	1;		// ������ 
	optional uint32	PosIndex		=	2;		// ��ȡ�µĲ������ڵ�λ������	
};

// *************************************************************************** //
// CMessageLifeSkillAttributeNotify   ������->�ͻ���
// ��������Ըı��֪ͨ
// *************************************************************************** //
message CMessageLifeSkillAttributeNotify
{ 
	optional uint32	LifeSkillType			=	1;		// ��������� 
	optional uint32	SpecializeDegree		=	2;		// ������		
};



//
// *************************************************************************** //
// CMessageMultiBuffRequest  �ͻ��� - > ������
//  buff����ϱ���Ϣ
// *************************************************************************** //
message PBEntityBuffEvent
{
	optional uint32 CharID	= 1; // ��ɫID
	optional uint32 Param1	= 2; // ����1( ʦͽ����->BuffID ; )
};

message CMessageMultiBuffRequest
{
	optional uint32	EventID						= 1;	// �¼�����
	repeated PBEntityBuffEvent	BuffEventList	= 2;	// ����ʵ���б�
	optional uint32 NeedRefresh					= 3;	// (0-ֻˢ��ʱ��; 1-���¼�������Ч��)
};


// *************************************************************************** //
// CMessageChangeCamp   ������->�ͻ���
// ��������Ըı��֪ͨ
// *************************************************************************** //
message CMessageChangeCamp
{
	optional uint32 EntityID			= 1;	
	optional uint32	CampID				= 2;
	optional uint32 CharID				= 3;
	optional uint32 TempID				= 4;
};

// *************************************************************************** //
// CMessageChangePKDropMode   �ͻ���->������
// �ı�PK����( ������ѫ�� )
// *************************************************************************** //
message CMessageChangePKDropMode
{
	optional bool IsDrop			= 1;	
};

// *************************************************************************** //
// CMessageGetEquipExchangeListRequest
// ��ȡװ���һ��б����Ϣ����
// *************************************************************************** //
message CMessageGetEquipExchangeListRequest
{
	optional uint32	EntityID	=	1;		 //	npcʵ��ID
};


// *************************************************************************** //
// CMessageGetEquipExchangeListRequest
// ��ȡװ���һ��б����Ϣ����
// *************************************************************************** //
message CMessageGetEquipExchangeListResponse
{
	repeated uint32	ComposeID	=	1;		// �䷽ID
};

// �Զ��һ�����
message CMessageOperateAutoHookRequest
{
	optional uint32	Action	= 1;	// 1:��ʼ,0:ȡ��
	optional uint32	RedPhyicsID = 2;	// ��ҩģ��ID
	optional uint32	BluePhyicsID = 3;	// ��ҩģ��ID
	optional uint32	EnergyPhyicsID = 4;	// ����ģ��ID
};

//�Զ��һ��ظ�
message CMessageOperateAutoHookResponse
{
	optional uint32 Action  = 1;
	optional uint32	RtnCode = 2; 
};

// �Զ��һ�ʱ��ҩ
message CMessageBuyPhysicRequest
{
	optional uint32	Index = 1;	// ҩƷ����
	optional uint32	Number = 2;	// ҩƷ����
	optional uint32	Type   = 3;	// ҩƷ����
	optional uint32	BuyType = 4;	// ����ʽ(��Ԫ�����ǰ�Ԫ������Ǯ)
};

message CMessageBuyPhysicResponse
{
	optional uint32	RtnCode = 1;	// ����ظ�
};

// *************************************************************************** //
// CMessagePushMultiRequest   ��Ϸ�ͻ���->��Ϸ������
// ���Ӻϳɷ�������
// *************************************************************************** //
message CMessagePushMultiRequest
{
	optional uint32 Index  = 		1; 		// ���������
};

// *************************************************************************** //
// CMessagePushMultiResponse   ��Ϸ������->��Ϸ�ͻ���
// ���Ӻϳɷ����Ӧ
// *************************************************************************** //
message CMessagePushMultiResponse   
{
	optional uint32 Result  = 		1; 		// ����Ľ��
	optional uint32 Index1  = 		2; 		// ���������
	optional uint32 Index2  = 		3; 		// Ŀ��λ��
};

// *************************************************************************** //
// CMessagePopMultiRequest   ��Ϸ�ͻ���->��Ϸ������
// ���Ӻϳ��ó�����
// *************************************************************************** //
message CMessagePopMultiRequest
{
	optional uint32 Index  = 		1; 		// �ó�������
};

// *************************************************************************** //
// CMessagePopMultiResponse   ��Ϸ������->��Ϸ�ͻ���
// ���Ӻϳ��ó���Ӧ
// *************************************************************************** //
message CMessagePopMultiResponse   
{
	optional uint32 Result  = 		1; 		// �ó��Ľ��
	optional uint32 Index2  = 		2; 		// �ó�λ��
	optional uint32 Index1  = 		3; 		// �ó�������
};


// *************************************************************************** //
// CMessageAddEcompoundEquipRequest   ��Ϸ�ͻ���->��Ϸ������
// ���ô��ֽ�װ������Ϣ����
// *************************************************************************** //
message CMessageAddEcompoundEquipRequest
{
	optional uint32	 EquipmentIndex = 1;			//	װ������	
};

// *************************************************************************** //
// CMessageAddEcompoundEquipResponse   ��Ϸ������->��Ϸ�ͻ���
// ���ô��ֽ�װ������Ϣ��Ӧ
// *************************************************************************** //
message CMessageAddEcompoundEquipResponse
{
	optional uint32	Errcode			=	1;		// ������
	optional uint32	EquipmentIndex	=	2;		// װ������
};

// *************************************************************************** //
// CMessageTakeDecompoundEquipRequest   ��Ϸ�ͻ���->��Ϸ������
// ���´��ֽ�װ������Ϣ����
// *************************************************************************** //
message CMessageTakeDecompoundEquipRequest
{
	optional uint32 MsgCode	=	1;		// ���ò���
};

// *************************************************************************** //
// CMessageTakeDecompoundEquipResponse   ������->�ͻ��� 
// ���´��ֽ�װ������Ϣ��Ӧ
// *************************************************************************** //
message CMessageTakeDecompoundEquipResponse
{ 
	optional uint32	Errcode		=	1;		// ������	
	optional uint32	EquipIndex	=	2;		// װ������
};

// *************************************************************************** //
// CMessagePlayerFcmStatusNotify   ������->�ͻ��� 
// ������״̬֪ͨ
// *************************************************************************** //
enum EFcmStatus
{
	em_none_rate = 0;				// 0 ����
	em_half_rate = 1;				// 50%����
	em_normal_rate = 2;				// ��������
};

message CMessagePlayerFcmStatusNotify
{ 
	optional EFcmStatus  FcmStatus  =1;			//��ǰ��״̬
	optional int32       ValidSecond=2; 	    //��ǰ״̬ʣ�����Чʱ������
};

// ����ϴ����Ϣ
message CMessageMagicWeaponClearPointRequest
{
	optional  uint32     ClearType	=	1;			// ϴ������ ��enMW_ClearType
	optional  uint32     MWBagIndex	=	2;			// ������������
	optional  uint32     StoneBagIndex	= 3;		// ϴ��ʯ��������
	optional  uint32	 NpcEntityID	= 4;	// ���в�����NPCʵ��ID
};


// ����ϴ����Ϣ��Ӧ
message CMessageMagicWeaponClearPointResponse
{
	optional  uint32     Result		=	1;		// ϴ���Ӧ  0�ɹ�
	optional  uint32     ClearType	=	2;		// ϴ������ ��enMW_ClearType
	optional  PBItemObject	MWObj	=	3;		// �µķ����ṹ ���Ǽ���
	optional  uint32     MWBagIndex	=	4;		// ������������
};

// ����ϴ�� �ŷ�������
message CMessageMagicWeaponClearPointAddMWRequest
{
	optional  uint32     MWBagIndex	=	1;			// ������������
};


// ����ϴ�� �ŷ�����Ӧ
message CMessageMagicWeaponClearPointAddMWResponse
{
	optional  uint32     NewPoints			=	1;		// �¼ӵ�Ǳ�ܵ�
	optional  uint32     NewSkillPoints		=	2;		// �¼ӵļ��ܵ�
};

// *************************************************************************** //
// CMessageAddWizardPointRequest   ��Ϸ�ͻ���->��Ϸ������
// ���ӲŻ��ȼ�����
// *************************************************************************** //
message CMessageAddWizardPointRequest
{
	optional uint32 Type			= 		1; 		// ���ӵ�����
};

// *************************************************************************** //
// CMessageAddWizardPointResponse   ��Ϸ������->��Ϸ�ͻ���
// ���ӲŻ��ȼ���Ӧ
// *************************************************************************** //
message CMessageAddWizardPointResponse   
{
	optional uint32 Result			= 		1; 		// ���ӵĽ��
	optional uint32 Type			= 		2; 		// ���ӵ�����
	optional uint32 Increase		=		3;		// ��ǰ�����ӵ���
	optional uint32 CommonLeft		=		4;		// ʣ���츳��
};

// *************************************************************************** //
// CMessageHonorToWizardRequest   ��Ϸ�ͻ���->��Ϸ������
// *************************************************************************** //
message CMessageHonorToWizardRequest
{
	optional int32 ChangeHonor		 = 		1; 		// �һ��Ĺ�ѫֵ
	optional int32 Type				 = 		2; 		// �һ������
};

// *************************************************************************** //
// CMessageGetTrendRequest   ��Ϸ�ͻ���->��Ϸ������
// ��������
// *************************************************************************** //
message CMessageGetTrendRequest
{

};

// *************************************************************************** //
// CMessageGetTrendResponse   ��Ϸ������->��Ϸ�ͻ���
// ������Ӧ
// *************************************************************************** //
message CMessageGetTrendResponse   
{
	optional uint32 Result			= 		1; 		// �����Ľ��
	optional uint32 Trend			= 		2; 		// �õ�������ֵ
};



// *************************************************************************** //
// CMessageClientRunTimePara   ��Ϸ������->��Ϸ�ͻ���
// ֪ͨ�ͻ�������ʱ����
// *************************************************************************** //
message PBRuntimeParam
{
	optional uint32 FunID	= 1;	// ����ID
	optional uint32 OnOFF	= 2;	// ����
	optional uint32 Param1	= 3;	// ����1
	optional uint32 Param2	= 4;	// ����2
	optional string Param3	= 5;	// ����3
};


message CMessageClientRunTimeParamNotify  
{
	optional uint32 Version				= 		1; 		// �汾��
	repeated PBRuntimeParam Functions	= 		2; 		// ����ʱ����
};

// �ͻ��������������
message CMessageGetHelpDataRequest
{
};

// �ʱ��
message PBActivityTime
{
	optional uint32		StartTime	=	1;	// ���ʼʱ��
	optional uint32		EndTime		=	2;	// �����ʱ��
	optional uint32		ShowFlag	=	3;	// ��ʾ��־
};

// ����ϵͳ ��������
message PBSingleHelpData
{
	optional uint32		HelpID	=	1;	// ����ID
	repeated uint32		Params	=	2;	// ������(����)
	optional uint32		Completed=	3;	// �Ѿ����XX��
	optional uint32		TotalTimes=	4;	// �ܼ�XX��
	repeated PBActivityTime		TimeList =	5;	// ���ʱ���
	optional uint32		WeekTimes=	6;	// ���ܴ���
};

// ����XX����
message PBTodayIncItem
{
	optional uint32		LevelUp	=	1;	// ���յȼ�����
	optional uint32		ExpUp   =	2;	// ���վ�������
	optional uint32		HonorUp =	3;	// ���չ�ѫ����
	optional uint32		AchiveUp =	4;	// ���ճɾ͵�������
	optional uint32		KillUp =	5;	// ����������ɱ����
};

// �ͻ�������������� ��Ӧ
message CMessageGetHelpDataResponse
{
	repeated PBSingleHelpData HelpDatas = 1;
	optional PBTodayIncItem   TodayUp	= 2; // ��������
};

message CMessagePickItemNotify
{
	optional uint32		EntityID	=	1;	
} ;

// ��������ʱ֪ͨ
message CMessageProPrisonTimeNotice
{
	optional uint32	Time = 1;
};


// ���±�������Ϣ����
message CMessageTakeKitBagRequest
{
	optional uint32 SrcSlot		 =		1;			// Ŀ��λ�����ڲֿⱳ�������ڰ�������
	optional uint32 SrcIndex	 = 		2; 			// �����ڱ�����λ�е�����
	optional uint32 DesIndex	 = 		3; 			// Ŀ���������
	optional uint32 DesSlot		 =		4;			// Դλ��		
};

// ���±�������Ϣ��Ӧ
message CMessageTakeKitBagResponse
{	
	optional uint32 Errocode	 = 		1; 			// 0��ʾ�ɹ�������ʾ������
	optional uint32 SrcSlot		 = 		2; 			// �����������ǲֿⱳ��
	optional uint32 SrcIndex	 = 		3; 			// �����ڱ�����λ������
	optional uint32 DesSlot		 =		4;			// ���õ�Ŀ���Ǳ������ǲֿ�
	optional uint32 DesIndex	 =		5;			// �����ڲֿ���ֿ߲��е�λ������
};

// ��ȡ���������б�����
message CMessageGetTeleListRequest
{
	optional uint32  BagIndex				= 1;	// ��������
};

// ��ȡ���������б��Ӧ
message CMessageGetTeleListResponse
{
	repeated PBTelePostion	TeleList		= 1;			// ���е��߼�����б�
	optional uint32  BagIndex				= 2;	// ��������
};

// ��¼���͵�����
message CMessageAddTelePointRequest
{
};

// ��¼���͵��Ӧ
message CMessageAddTelePointResponse
{
	optional PBTelePostion	TelePoint		= 1;
};

// ɾ�����͵�����
message CMessageDelTelePointRequest
{
	optional uint32  Index					= 1;	// Ҫɾ�������� ��0��ʼ
};

// ɾ�����͵��Ӧ
message CMessageDelTelePointResponse
{
	optional uint32  Index					= 1;	// ɾ�������� ��0��ʼ
};

// ʹ�ô��͵��ߴ�������
message CMessageUseTeleItemRequest
{
	optional uint32  Index					= 1;	// ���� ��0��ʼ
	optional uint32  BagIndex				= 2;	// ��������
};

// vip Ȩ��֪ͨ
message CMessageProVipNotice
{
	optional uint32	CharID = 1;
	optional uint32	Status = 2;		// 0 : �رգ� 1 : ��ͨ
	optional uint32	Time	= 3;	// ��Ա����ʱ��
};

// ��ѯȫ��δ��Ԫ���������
message CMessageQueryGoldenYBRequeset
{
	optional uint32	EntityID	= 1;	// NPCʵ��ID	
};

// ��ѯȫ��δ��Ԫ������Ӧ
message CMessageQueryGoldenYBResponse
{
	optional int32 GoldenYB = 1;		// ��Ԫ�����
};

// ������ȡ��Ԫ��ֵ
message CMessageDrawGoldenYBRequest
{
	optional uint32	EntityID	= 1;	// NPCʵ��ID	
	optional int32 RequiredGoldenYB = 2;	// ��ȡ��Ԫ����
};

// ��������Ӧ�Ƿ���ȡ�ɹ�
message CMessageDrawGoldenYBResponse
{
	optional int32 ErrorCode = 1;		// ��Ϣ��
};

// ʹ�õ��߹㲥��XXʹ����XX���ߣ�
message CMessagePlayerUseItemNotify
{
	optional uint32	EntityID	= 1;	// ���ʵ��ID	
	optional uint32	ItemID		= 2;	// ��ƷID
};

// �ͻ���->������ �������밲ȫ����ʱ�������
message CMessageSetPwdProtectTimeRequest
{
	optional uint32	ProtectTime	= 1;		
};

// ������->�ͻ��� �������밲ȫ����ʱ�����Ϣ��Ӧ
message CMessageSetPwdProtectTimeResponse
{
	optional uint32	Errcode		= 1;	// ������
	optional uint32	ProtectTime	= 2;	// ��ȫ����ʱ��				
};


// ������->�ͻ��� ���ʼ/����֪ͨ
message SingleActivityNewState
{
	optional uint32 ActivityID		= 1;
	optional uint32 ActivityState   = 2; // ��״̬ ��enActivityStateö��
	optional uint32 CompleteTimes   = 3; // ����ɴ���
};

// ����֪ͨ����XXX���ʼ/������
message CMessageActivityChange2CliNotify
{
	repeated SingleActivityNewState ActivityList = 1;
};


// ʹ���ʻ�����
message CMessageUseFlowerRequest
{
	optional uint32 BagIndex = 1;	// �ʻ��İ�������
	optional string DesName  = 2;	// �Է��Ľ�ɫ����
};

// ʹ���ʻ���Ӧ
message CMessageUseFlowerResponse
{
	optional uint32 ResultCode     = 1;	// 0�ɹ� ��Ȼ�Ǵ�����
	optional uint32 TodayLeftTimes = 2;	// ����ʣ�����ʹ���
};

// ����ʻ�֪ͨ
message CMessageObtainFlowerNotify
{
	optional uint32 CharID	 = 1;	// �������Ľ�ɫID
	optional string SrcName  = 2;	// �����˵�����
	optional string DesName	 = 3;	// ������������
	optional uint32 ItemID	 = 4;	// ʹ�õ���ƷID
};

// ��������֮�䡿ʹ���ʻ�����
message CMessageS2SPlayerUseFlowerRequest
{
	optional CMessageRouter Router			 = 		1;    
	optional uint32			BagIndex		 =		2; // ��������
	optional uint32			ItemID			 =		3; // ʹ�õ��ʻ�ID
};

// ��������֮�䡿ʹ���ʻ���Ӧ������������
message CMessageS2SPlayerUseFlowerResponse
{
	optional CMessageRouter Router			 = 		1;    
	optional uint32			ResultCode		 =		2; // ��� ��0�ɹ�
	optional uint32			BagIndex		 =		3; // ��������
};


// >�ͻ���->������ ��ͨ�󶨵���Ϣ����
message CMessageCommonBindRequest
{	
	optional uint32	BindStoneIndex	= 1;		// ��ʯ������
	optional uint32	ItemIndex		= 2;		// ��Ʒ������
	optional uint32	ItemSlot		= 3;		// װ�����ڵİ�������
};

// ������->�ͻ��� ��ͨ�󶨵���Ϣ��Ӧ	
message CMessageCommonBindResponse
{
	optional uint32	Errcode		=	1;	// ������
	optional uint32	ItemIndex	=	2;	// ��Ʒ����
	optional uint32	ItemSlot	=	3;	// ��Ʒ���ڵİ�������
};

// Զ������װ������
message CMessageRemoteMendAllEquipRequest
{

};

message CMessageRemoteMendAllEquipResponse
{
	optional uint32	 RtnCode = 1;	// ������
};

// �ͷ��� -> ������ ��������������
message CMessageStartProgressRequest
{
	optional uint32	FuncType	=	1;	// �������������Ǹ�ģ��(Em_ProgressFunctype)	
};

// ������->�ͻ��� ������������Ϣ��Ӧ
message CMessageStartProgressResponse
{
	optional uint32	Errcode	=	1;		// ������	
};

// *************************************************************************** //
// CMessageResetTalentRequest ��Ϸ������-> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageResetTalentRequest
{
};


// *************************************************************************** //
// CMessageResetTalentResponse ��Ϸ������-> ��Ϸ�ͻ���
// *************************************************************************** //
message CMessageResetTalentResponse
{
	optional uint32 Ret  = 		1; 	// ������
	optional uint32	Step =		2;	// ��ǰС��
	optional uint32	Point =		3;	// ʣ�����
};


// �ͻ��˻�û��Ϣ
message CMessageGetActivityInfoRequest
{
	repeated uint32  ActivityID	= 1;	// Ҫ��ȡ�ĻID
	optional uint32	 TypeID		= 2;	// ������ �����ڵ�ID��
};

message ActivityInfo_4MSG
{
	optional uint32  ActivityID = 1;	// �ID
	optional uint32  Times		= 2;	// ����
};

// �ͻ��˻�û���� ��Ӧ
message CMessageGetActivityTimesResponse
{
	repeated ActivityInfo_4MSG	Info		= 1;	// Ҫ��ȡ�ĻID
	optional uint32				TypeID		= 2;	// ������ �����ڵ�ID��
};

message CMessageChangeEquipProRequest
{
	optional uint32				EquipIndex	= 1;
	optional uint32				ItemIndex	= 2;
	optional uint32				NpcEntityID	= 3;
};

message CMessageChangeEquipProResponse
{
	optional uint32				Result		= 1;
	optional uint32				EquipIndex	= 2;
	optional uint32				ItemIndex	= 3;
	repeated uint32				PropertyID	= 4;
};

// �ͷ���->������ ʹ���廨������������Ϣ����
message CMessageUseKitbagNeedleRequest
{
	optional uint32	NeedleIndex = 1;		// �廨������
	optional uint32	KitbagSlot	= 2;		// �������ڵİ�������(ESlotType)
	optional uint32	KitbagIndex	= 3;		// �������ڵ�λ������
};	

// ������->�ͻ��� ʹ���廨������������Ϣ��Ӧ
message CMessageUseKitbagNeedleResponse
{
	optional uint32	Errcode		= 1;		// ������
	optional uint32	KitbagSlot	= 2;		// �������ڵİ�������(ESlotType)
	optional uint32	KitbagIndex = 3;		// �������ڵ�λ������
	optional uint32	ExpiredTime	= 4;		// �����Ĺ���ʱ��
	optional uint32	NeedleIndex = 5;		// �廨�������	
	optional uint32	TimeLength	= 6;		// ʹ���廨��󱳰��ӳ���ʹ��ʱ��
};

message CMessageOpenStoneRequest
{
	optional uint32	NpcEntityID		=	1;	// �����NPCID
};

message CMessageOpenStoneResponse
{
	optional uint32	Result			=	1;
	optional uint32	NpcEntityID		=	2;
};

// ��ȫ��������������������Ϣ����
message CMessageLockPasswordRequest
{
		
};

// ��ȫ��������������������Ϣ��Ӧ
message CMessageLockPasswordResponse
{
	optional uint32	Errcode	=	1;	// ������
	optional uint32 Status	=	2;	// ���ڵ�״̬
};

message CMessageLearnOgreSkillRequest
{
	optional uint32	CardID		=	1;	// ��ƬID
};

message CMessageLearnOgreSkillResponse
{
	optional uint32	Result			=	1;
	optional uint32	CardID			=	2;
	optional uint32 Index1			=	3;
	optional uint32 Index2			=	4;
};

message CMessagePlayerPickItemNotify
{
	optional string PlayerName		=	1;
	optional uint32	ItemID			=	2;
};

message CMessageQueryPedalRequest
{
	optional uint32	NPCEntityID		=	1;		// NPCID
};

message CMessageQueryPedalResponse
{
	optional uint32 NPCEntityID		=	1;		// NPCID
	optional uint32 ExistTime		=	2;		// ���ʱ��
	repeated uint32 Hour			=	3;		// ˢ��ʱ��
};

message CMessageAutoBuyItemRequest
{
};

message CMessageAutoBuyItemResponse
{
};

message CMessageUseSummonItemRequest
{
	optional uint32	ItemIndex		=	1;
	optional string CharName		=	2;
};

message CMessageUseSummonItemResponse
{
	optional uint32	ItemIndex		=	1;
	optional string CharName		=	2;
	optional uint32 Result			=	3;
};

message CMessageSplitEquipRequest
{
	optional uint32	EquipIndex		=	1;
	optional uint32	ItemIndex		=	2;
};

message CMessageSplitEquipResponse
{
	optional uint32	EquipIndex		=	1;
	optional uint32	ItemIndex		=	2;
	optional uint32	Result			=	3;
};

message CMessageGetStarRequest
{
	optional uint32	EquipIndex		=	1;
	optional uint32	ItemIndex		=	2;
	optional uint32	NPCEntityID		=	3;
};

message CMessageGetStarResponse
{
	optional uint32	EquipIndex		=	1;
	optional uint32	ItemIndex		=	2;
	optional uint32	Result			=	3;
};

message CMessageAddStarRequest
{
	optional uint32	EquipIndex		=	1;
	optional uint32	ItemIndex		=	2;
};

message CMessageAddStarResponse
{
	optional uint32	EquipIndex		=	1;
	optional uint32	ItemIndex		=	2;
	optional uint32	Result			=	3;
	optional uint32	Star			=	4;		// ���Ǻ�ĵȼ�
};

// װ������֪ͨ
message CMessageEquipmentOverdueNotify
{
	optional uint32	EquipIndex		=	1;		// װ������
	optional uint32	pos_type		=	2;		// ��Ʒλ�� ��EPosTypeö��
};

// ��Ʒ��ʼ���ڼ�ʱ֪ͨ
message CMessageItemStartTimerNotify
{
	optional uint32	pos_type		=	1;		// ��Ʒλ�� ��EPosTypeö��
	optional uint32 item_index		=	2;		// ����
	optional uint32 overdue_time	=	3;		// δ������ʱ��
};

message CMessageAddExtraRequest
{
	optional uint32	EquipIndex		=	1;
	optional uint32	ItemIndex		=	2;
	optional uint32	NPCEntityID		=	3;
};

message CMessageAddExtraResponse
{
	optional uint32	EquipIndex		=	1;
	optional uint32	ItemIndex		=	2;
	optional uint32	Result			=	3;
	optional uint32	ExtraType		=	4;		// ���ɵ�����
};

message CMessageChangeOwnCampNotify
{
	optional uint32	NPCEntityID		=	1;		// NPC ID
	optional uint32 CampID			=	2;		// ������ӪID
	optional uint32	PosX			=	3;
	optional uint32	PosY			=	4;
	optional uint32	TempID			=	5;
};

message CMessageWarOperateRequest
{
	optional uint32	NPCEntityID		=	1;		// NPC ID
	optional uint32	OpType			=	2;		// ��������
};

message CMessageWarOperateResponse
{
	optional uint32	NPCEntityID		=	1;		// NPC ID
	optional uint32	OpType			=	2;		// ��������
	optional uint32	Result			=	3;
};

// �ͻ���->������ �Ƿ����ʹ�òɼ����ߵ�����
message CMessageCanUseAutoCollectItemRequest
{	
	optional uint32 ItemIndex = 1;	// ��������	
};

// ������->�ͻ��� �Ƿ����ʹ�òɼ����ߵ���Ϣ��Ӧ
message CMessageCanUseAutoCollectItemResponse
{	
	optional uint32	Errcode	  = 1;	// ������
	optional uint32	ItemIndex = 2;	// ��������	
};

// �ͻ���->������ ʹ���Զ��ɼ����߲ɼ�����Ϣ����
message CMessageCollectByAutoItemRequest
{		
	optional uint32 ItemIndex = 1;	// ��������	
};

// ������->�ͻ��� ʹ���Զ��ɼ����߲ɼ�����Ϣ��Ӧ
message CMessageCollectByAutoItemResponse
{	
	optional uint32	Errcode		= 1;	// ������
	optional uint32 ItemIndex	= 2;	// ��������	
	optional uint32 LeftUseTimes= 3;	// ʣ��ʹ�ô���
};

message CMessageLearnFangCunSkillRequest
{
	optional uint32	SkillStage		=	1;
	optional uint32	SkillIndex		=	2;
	optional uint32	ItemIndex		=	3;
	optional uint32	NPCEntityID		=	4;
};

message CMessageLearnFangCunSkillResponse
{
	optional uint32	Result			=	1;
	optional uint32	SkillID			=	2;
	optional uint32	ItemIndex		=	3;
	optional uint32	ObjIndex		=	4;	// ��������
};

message CMessagePlayerTransformNotify
{
	optional uint32	EntityID		=	1;
	optional PBTransform Transform	=	2;
};

message CMessageHonorToItemRequest
{
	optional int32 ItemID		 = 		1; 		// �һ�����Ʒ
	optional int32 ItemNum		 = 		2; 		// �һ��ĸ���
};

message CMessageUseBlackPillsNotify
{	
	optional uint32	PillIndex			= 1;		// �ڹ����ڰ����е�����
	optional uint32	PillLeftTime		= 2;		// �ڹ����ʣ��ʹ��ʱ��
	optional uint32 OffLineTime			= 3;		// ��ҵ�ʣ����Ч����ʱ��	
	optional uint32	Exp					= 4;		// ��ȡ�ľ���
	optional uint32	OffLineTimeConsumed	= 5;		// ���ĵ�����ʱ��
	optional uint32	BlackPillsID		= 6;		// ���߾��鵤��ģ��ID
	optional uint32	Errcode				= 7;		// ������
};

message CMessageExpContainerNotify
{
	optional uint32	CurrentExp			= 1;		// �������鵤���ڵľ���
	optional uint32	ExpAdded			= 2;		// �������鵤���ӵľ���
	optional uint32	Index				= 3;		// �������鵤�ڱ����е�����	
	optional uint32	ExpPillsID			= 4;		// �������鵤������ʱת���ɵľ��鵤
};


message CMessageUpdateYuanBaoNotice
{
	optional uint32 MoneyType		= 1;//Ӧֻ��5 #define BIND_MONEY 1; UNBIND_MONEY  2;  LINEKONG_MONEY   3; SILVER_YUANBAO   4; GOLDEN_YUANBAO   5
	optional int32  Amount			= 2;//��ǮΪ+����ǮΪ-
};

message CMessageUpgAndJewNotify
{
	optional string	PlayerName			= 1;
	optional uint32	Type				= 2;		// ����/�ϳɵ�����
	optional PBItemObject	ItemInfo	= 3;		// ��Ʒ����
	optional uint32	CharID				= 4;		
};

message CMessageJewelCarveRequest
{
	optional uint32 JewelIndex		= 1;		// ��ʯλ��(װ��)
	optional uint32 CardIndex		= 2;		// ����λ��
	optional uint32	JewelPos		= 3;		// װ���Ϸ��ñ�ʯ��λ��
};

message CMessageJewelCarveResponse
{
	optional uint32	Result			= 1;
	optional uint32 JewelIndex		= 2;		// ��ʯλ��(װ��)
	optional uint32 CardIndex		= 3;		// ����λ��
	optional uint32	JewelPos		= 4;		// װ���Ϸ��ñ�ʯ��λ��
	optional uint32	EquipJewel		= 5;		// װ���ϵı�ʯID
};

//���ĵڶ���
//����ת��
message CMessageRequestChangeRune
{
	optional uint32	RuneIndex	    =	1;			// ���ĵ�λ��
	optional uint32 RuneChangeIndex =   2;			// ת������λ��
	optional uint32	BagSlot	= 3;					// �������ڵİ�������(ESlotType)
	
}

message CMessageResponseChangeRune
{
	optional uint32	Result			=	1;			// ����ת����� 0 Ϊ�ɹ�
	optional uint32 SrcItemid		=	2;          // Ŀ�� id
	optional uint32 RuneIndex		=   3;			// ���ߵ�λ��
	optional uint32 BagSlot			=   4;			// �������ڵİ�������(ESlotType)

}
//��������
// *************************************************************************** //
// CMessageRuneComRequest   ��Ϸ�ͻ���->��Ϸ������
// ������������
// *************************************************************************** //
message CMessageRequestRuneCom
{
	repeated uint32	RuneIndex		=	1;	// ���ĵ�λ��
	optional uint32	ItemIndex		=	2;	// ��������λ��
};

message CMessageResponseRuneCom																	
{
	optional uint32	Result	 =	1;			// ����ת����� 1 Ϊ�ɹ� 0 Ϊʧ��
	optional uint32 Errorcod =  2 ;			// ������

}

message CMessageQueryBossRequest
{
};

message PBBoss
{
	optional uint32	TempID			= 1;		// ģ��ID
	optional uint32 MapID			= 2;		// ��ͼID
	optional uint32	PosX			= 3;		// ��ͼ����X
	optional uint32	PosY			= 4;		// ��ͼ����Y
	optional uint32	HP				= 5;		// Ѫ��ʵ��ֵ
	optional uint32	ConfigTime		= 6;		// ���õ�ˢ��ʱ�䣨Hour*60+Min��
	optional uint32	NextTime		= 7;		// �´θ���ʱ�䣨time_t��
};

message CMessageQueryBossResponse
{
	repeated PBBoss BossData		= 1;		
};

// *************************************************************************** //
// CMessageStartDigitalFireworksRequest   ��Ϸ�ͻ���->��Ϸ������
// �������񻨵���Ϣ����
// *************************************************************************** //
message PBDigitalWords
{	
	optional uint32 PosX		= 1;		// �������ĺ�����
	optional uint32 PosY		= 2;		// ��������������
	optional uint32	DigitalWord = 3;		// �ַ�	
};
message CMessageStartDigitalFireworksRequest
{	
	optional uint32			ItemIndex		= 1;			// �������ڰ����е�����
	optional uint32			StyleID			= 2;			// �ַ�����ЧID
	repeated PBDigitalWords	DigitalWords 	= 3;			// ������������Ϣ
};

// *************************************************************************** //
// CMessageStartDigitalFireworksResponse  ��Ϸ������->��Ϸ�ͻ���
// �������񻨵���Ϣ��Ӧ
// *************************************************************************** //
message CMessageStartDigitalFireworksResponse
{	
	optional uint32	Errcode = 1;		// ������
};

// *************************************************************************** //
// CMessageStartDigitalFireworksResponse  ��Ϸ������->��Ϸ�ͻ���
// �������񻨵���Ϣ��Ӧ
// *************************************************************************** //
message CMessageStartDigitalFireworksNotify
{	
	optional uint32				EntityID	= 1;		// ���̻�����ҵ�ʵ��ID
	optional uint32				PosX		= 2;		// ���̻�����ҵĺ�����
	optional uint32				PosY		= 3;		// ���̻�����ҵ�������
	optional uint32				StyleID		= 4;		// �ַ�����ЧID
	repeated PBDigitalWords		DigitalWords= 5;		// �̻����ַ���Ϣ
};


// *************************************************************************** //
// ��ҷֽⷨ�� ����
// *************************************************************************** //
message CMessageDecomposeMWRequest
{
	optional uint32 ItemIndex			 = 		1; 	// ��������
};

// *************************************************************************** //
// ��ҷֽⷨ�� ��Ӧ
// *************************************************************************** //
message CMessageDecomposeMWResponse
{
	optional uint32 ItemIndex			 = 		1; 	// ����
	optional uint32 RetCode				 = 		2; 	// ������ 0�ɹ� ���������
};


// *************************************************************************** //
// ��������ӡ�� ����
// *************************************************************************** //
message CMessageMWQLPrintRequest
{
	optional uint32 MWIndex				= 		1; 	// ��������
	optional uint32 QLIndex				= 		2; 	// ��������
	optional uint32 ItemIndex			= 		3; 	// ������Ʒ����
};

// *************************************************************************** //
// ��������ӡ�� ��Ӧ
// *************************************************************************** //
message CMessageMWQLPrintResponse
{
	optional uint32 MWIndex			 = 		1; 	// ��������
	optional uint32 QLID			 = 		2; 	// ����ID
	optional uint32 RetCode			 = 		3; 	// ������ 0�ɹ� ���������
};


// *************************************************************************** //
// �������� ����
// *************************************************************************** //
message CMessageQuickUpRequest
{
	optional uint32 MWIndex				= 		1; 	// ��������
	optional uint32 ItemIndex			= 		2; 	// ��Ƭ����
	optional uint32 UpType				= 		3; 	// 0������  1����Ʒ
	optional uint32 MWIndexEx			= 		4; 	// ����������
};

// *************************************************************************** //
// �������� ��Ӧ
// *************************************************************************** //
message CMessageQuickUpResponse
{
	optional uint32 MWIndex			 = 		1; 	// ��������
	optional uint32 RetCode			 = 		2; 	// ������ 0�ɹ� ���������
	optional uint32 UpType			 = 		3; 	// 0������  1����Ʒ
};


// *************************************************************************** //
// ����ϳ� ����
// *************************************************************************** //
message CMessageQilinComposeRequest
{
	repeated uint32 QLIndex				= 		1; 	// ��������
};

// *************************************************************************** //
// ����ϳ� ��Ӧ
// *************************************************************************** //
message CMessageQilinComposeResponse
{
	optional uint32 RetCode			 = 		1; 	// ������ 0�ɹ� ���������
};

// *************************************************************************** //
// ���� ��þ��� ֪ͨ
// *************************************************************************** //
message CMessageMWObtainExpNotify
{
	optional uint32 ExpVal			 = 		1; 	// ��ֵ
};


message CMessageQueryAroundPlayerRequest
{
	optional uint32 QueryRange = 1;				// 1 ���ҷ�ΧΪ������ 2���ҷ�Χ��������ͼ
};

message AroundPlayer
{
	optional uint32 MapID			= 1;		// ��ͼID
	optional string CharName		= 2;		// �û���
	optional uint32 Sex				= 3;		// �Ա�
	optional uint32 HaveTeam		= 4;		// �Ƿ��ж���
	optional uint32 TeamNum			= 5;		// ��������
	optional uint32 Level			= 6;		// �ȼ�
	optional uint32 MetierID		= 7;		// ����ID
	optional uint32 CharID			= 8;		// ��ɫid
	optional uint32 EntityID		= 9;		// ʵ��ID
};

message CMessageQueryAroundPlayerResponse
{
	optional uint32 QueryRange		= 1;		// 1 ���ҷ�ΧΪ������ 2���ҷ�Χ��������ͼ
	optional uint32 InRepetion		= 2;		//�Ƿ��ڸ����� 0�񣬷�0 ��
	repeated  AroundPlayer 	PlayerData	= 3;	//�����Ϣ	
};

message CMessagePlayerRepetData
{
	optional uint32 RepetIndex		= 1;		// ��������
	optional uint32	RepetData		= 2;		// ��Ҹ������ݣ���ʱ�õ�������

};

message CMessageSyncFameNotify
{
	optional uint32	CombatFame		= 1;		// ��ǰ��������
	optional uint32	RepeFame		= 2;		// ��ǰ��������
	optional uint32	CommonFame		= 3;		// ��ǰ��������
	optional uint32	CombatDelta		= 4;		// ������������
	optional uint32	RepeDelta		= 5;		// ������������
	optional uint32	CommonDelta		= 6;		// ������������
	optional uint32	CombatToday		= 7;		// ���վ�������
	optional uint32	RepeToday		= 8;		// ���ո�������
	optional uint32	CommonToday		= 9;		// ������������
};


// *************************************************************************** //
// CMessgeSpiritOpenRequest  ��Ϸ�ͻ���->��Ϸ������
// ��������
// *************************************************************************** //
message CMessageSpiritOpenRequest
{
	optional uint32 PositionIndex	= 1;	// ��λ
	optional uint32 SpiritType		= 2;	// ϵ��
	optional uint32	SlotIndex		= 3;	// ������
}

// *************************************************************************** //
// CMessgeSpiritOpenResponse  ��Ϸ������->��Ϸ�ͻ���
// ������Ӧ
// *************************************************************************** //
message CMessageSpiritOpenResponse
{
	optional uint32 Result	= 1;	// ���
}

// *************************************************************************** //
// CMessgeSpiritCastingRequest  ��Ϸ�ͻ���->��Ϸ������
// ��������
// *************************************************************************** //
message CMessageSpiritCastingRequest
{
	optional uint32 PositionIndex	= 1;	// ��λ
	optional uint32 SpiritType		= 2;	// ϵ��
	repeated uint32	SlotIndex		= 3;	// ������
	repeated uint32	ItemIndex		= 4;	// ��������ڰ����е�����
}

// *************************************************************************** //
// CMessgeSpiritCastingResponse  ��Ϸ������->��Ϸ�ͻ���
// ������Ӧ
// *************************************************************************** //
message CMessageSpiritCastingResponse
{
	optional uint32 Result		= 1;	// ���
	repeated uint32	ItemIndex	= 2;	// ����ɹ�����������
}

// *************************************************************************** //
// CMessgeSpiritUpgradeRequest  ��Ϸ�ͻ���->��Ϸ������
// ��������
// *************************************************************************** //
message CMessageSpiritUpgradeRequest
{
	optional uint32 UpgradeItemIndex		= 1;	// �������ڰ����е�����
	repeated uint32 SpiritItemIndex			= 2;	// �����ڰ����е�����
	optional uint32 IsBatch					= 3;	// �Ƿ�������
}

// *************************************************************************** //
// CMessgeSpiritUpgradeResponse  ��Ϸ������->��Ϸ�ͻ���
// ������Ӧ
// *************************************************************************** //
message CMessageSpiritUpgradeResponse
{
	optional uint32 Result		= 1;	// ���
}

// *************************************************************************** //
// CMessgeSpiritDowngradeRequest  ��Ϸ�ͻ���->��Ϸ������
// ��������
// *************************************************************************** //
message CMessageSpiritDowngradeRequest
{
	optional uint32 PositionIndex			= 1;	// ��λ
	optional uint32 SpiritType				= 2;	// ϵ��
	optional uint32	SlotIndex				= 3;	// ������
	optional uint32	DowngradeItemIndex		= 4;	// ��������ڰ����е�����
}

// *************************************************************************** //
// CMessgeSpiritDowngradeResponse  ��Ϸ������->��Ϸ�ͻ���
// ������Ӧ
// *************************************************************************** //
message CMessageSpiritDowngradeResponse
{
	optional uint32 Result		= 1;	// ���
}

// *************************************************************************** //
// CMessgeSpiritInfoRequest  ��Ϸ������->��Ϸ�ͻ���
// ������Ϣ����
// *************************************************************************** //
message CMessageSpiritInfoRequest
{
}

// *************************************************************************** //
// CMessgeSpiritInfoRequest  ��Ϸ������->��Ϸ�ͻ���
// ������Ϣ֪ͨ
// *************************************************************************** //

message CMessageSpiritInfoNotify
{
	repeated uint32 Point						= 1;	// ÿ��ϵ����������ֵ
	optional PBSpiritInfo SpiritInfo			= 2;	// ÿ����λ�Ŀ��ס��Ƿ���������Ϣ
	optional uint32 Score						= 3;	// ������
}