#ifndef __ERR_CODE_H__
#define __ERR_CODE_H__

//ErrorCode define rule:
//20XXX ever server base error code
//21XXX in loginserver error
//22XXX in dbserver error
//23XXX in proxyserver error
//24XXX in gateserver error 
//26XXX in sceneserver error

//base err code( 0, -20000 - -20999 ) only use in server
#define		SUCCESS							( 0 )
#define		ERR_UNKNOWN						( -20000 )
#define		ERR_NO_ENOUGH_MEMORY			( -20001 )
#define		ERR_INVALID_PARAMETER			( -20002 )
#define		ERR_FOPNE						( -20003 )
#define		ERR_NOT_FOUND					( -20004 )
#define		ERR_PENGING						( -20005 )
#define		ERR_FULL						( -20006 )
#define		ERR_EXIST						( -20007 )
#define		ERR_BUSY						( -20008 )
#define		ERR_PARSEPB						( -20009 ) // ����PB blob�ֶ�ʧ��


#include "langcode.h"

//////////////////////////////sceneserver///////////////////////////
//property		( -26000 - -29999 )

// �󶨽�� ( -26049 - -26000 )
enum ItemBindResult
{
	ITEM_BINDRESULT_SUCESS  	=	-26049	,					// �󶨳ɹ�
	ITEM_BINDRESULT_BINDED	=	-26048	,						// ��Ʒ�Ѿ���
	ITEM_BINDRESULT_NOEXIST	=	-26047	,						// ��Ʒģ�岻����
	ITEM_BINDRESULT_WRONGBINDWAY	=	-26046	,				// �����Ͳ�ƥ�� 
	ITEM_BINDRESULT_CANNOTBIND	=	-26045	,					// ��Ʒ�����ֶ���
	ITEM_BINDRESULT_CONSUMEITEMERROR	=	-26044	,			// ��ʯ����
	ITEM_FREEITEM_SUCESS 	=	-26043	,						// ����󶨳ɹ�
	ITEM_FREEITEM_NONEED	=	-26042	,						// װ��û���ֶ���
	ITEM_THROW_BINDED                      	=	-26041	,		// ����Ʒʱװ����
	ITEM_TRADE_BINDED                      	=	-26040	,		// ����ʱ��Ʒ��
	ITEM_SELL_BINDED                       	=	-26039	,		// ���̵�ʱ��Ʒ��	
	ITEM_STALL_BINDED	=	-26038	,							// ��̯������Ʒʱ��
	ITEM_MAIL_BINDED	=	-26037	,							// �����ʼ�ʱ��Ʒ��
	ITEM_EATEQUIP_BINDED                   	=	-26036	,		// ��װ��ʱװ�����ֶ���
	ITEM_RESUMEBIND_SUCESS	=	-26035	,						// ȡ������ֶ��󶨳ɹ�		
	ITEM_BINDRESULT_ERROR	=	-26034	,						// ��������	
	ITEM_STALL_BINDEDBYITEM	=	-26033	,						// �ֶ��󶨵���Ʒ���ܽ��а�̯ 
	ITEM_BINDRESULT_MONEYNOTENOUGH	=	-26032	,				// �󶨷��ò���	 
	ITEM_FREEBINDRESULT_MONEYNOTENOUGH	=	-26031	,			// ȡ���ֶ���ʱ��Ǯ����
	ITEM_RESUMEBINDRESULT_MONEYNOTENOUGH	=	-26030	,		// �ָ���ʱ��Ǯ����
	ITEM_SENDMAIL_BINDEDBYITEM	=	-26029	,					// ���ܽ��ֶ��󶨵���Ʒ�����ʵ�
	ITEM_EATEQUIP_BINDEDBYITEM	=	-26028	,					// ���ֶ��󶨵���Ʒ��������¯����
	ITEM_UPGE_BINDEDBYITEM	=	-26027	,						// ���ֶ��󶨵���Ʒ����װ������
	ITEM_ADDBINDSTONE_NOTBINDSTEON	=	-26026	,				// �ֶ��󶨽��棬���ǰ�ʯ����Ʒ����ʯͷ��
	ITEM_BINDITEM_HASNOEQUIP	=	-26025	,					// û�з���װ��������󶨰�ť
	ITEM_BINDITEM_HASNOBINDSTONE	=	-26024	,				// û�з����ʯ������󶨰�ť
	ITEM_BINDITEM_HASBINDED	=	-26023	,						// �����ֶ������Ե�װ���󣬵���󶨰�ť
	ITEM_BINDITEM_CANNOTBINDED	=	-26022	,					// ����װ������Ʒ�����ֶ�������
	ITEM_FREEITEM_HASNOTBINDED	=	-26021	,					// �����װ������Ϊ���ֶ���״̬��������ť	
	ITEM_COMMONBIND_WRONGBINDITEM	=	-26020	,					// ��ͨ��ʱ��ʯ���Ͳ���
	ITEM_COMMONBIND_ITEMBINDED		=	-26019	,					// ��Ʒ�Ѿ����й���ͨ��
	ITEM_COMMONBIND_PIPELIMIT		=	-26018	,					// �ɶѵ�����Ʒ���ܽ�����ͨ��
	ITEM_COMMONBIND_BINDBYITEM		=	-26017	,					// �ֶ��󶨵���Ʒ���ܽ�����ͨ��

};

// ���߻��������� ( -26099 - -26050 )
enum EItemECode
{
	ERROR_ITEM_ITEMNOTREGISTER	=	-26099	,			// ��������û��ע��
	ERROR_ITEM_DATANOTEXIST	=	-26098	,				// �������ݲ�����
	ERROR_SKILL_DATANOTEXIST	=	-26097	,			// �������ݲ�����
	ERROR_SKILLTREE_DATANOTEXIST	=	-26096	,		// ���������ݲ�����
	ERROR_SKILLTREE_INDEXOVERFLOW	=	-26095	,		// ����������Խ��
	ERROR_METIER_DATANOTEXIST	=	-26094	,			// ְҵ���ݲ�����
	ERROR_DEBUG_CMDNOTFOUND	=	-26093	,				// ����ָ��û���ҵ�
	ERROR_SPECIAL_TASK_ITEM_ERROR	=	-26092	,		// ����������߲����ظ����
	ERROR_TASK_ITEM_NONEED	=	-26091	,				// �㲻��Ҫ����������
	ERROR_ITEM_MINEINFRONT	=	-26090	,				// ��δ����������ǰ��
	ERROR_ITEM_NOTEVENT	=	-26089	,					// û���¼�
	ERROR_ITEM_HASCARD	=	-26088	,					// �Ѿ����������Ƭ
	ERROR_INVILID_ITEM	=	-26087	,					// ���ڵ���Ʒ
	ERROR_OVERMAX_TELE_LISTS	=	-26086	,			// ��������¼������
	ERROR_CANT_ADD_TELEPOINT	=	-26085	,			// ������Ӵ��͵�
	ERROR_ITEM_INVALID	=	-26084	,					// ��Ʒ��ʧЧ�����������
	ERROR_FLOWER_DES_INVILID	=	-26083	,			// ʹ���ʻ�ʱ�Է������߻���Ҳ�����
	ERROR_FLOWER_OVER_MAX_TIMES 	=	-26082	,		// �����ѳ����ʻ����ʹ�ô���
	ERROR_GIFT_OVER_MAX_TIMES		= -26081,			// ����ʹ������ѳ�������
	ERROR_ITEM_INWEDDINGHALL		=	-26080	,		// �����ò���ʹ�����η�
	ERROR_ITEM_REAUEST_MENPAI		=	-26079	,		// ���������ɲ��ܿ�
	ERROR_ITEM_OVER_TIME			= -26078,			// ʹ����Ʒ�Ѵ����
	ERROR_TREASUREBOWL_CANNOTUSED	= -26077,			// ��Ʒ���ܱ����ھ۱�
	ERROR_TREASUREBOWL_TOTALTIMELIMIT= -26076,			// �ܹ��۱������Ѵﵽ��������
	ERROR_TREASUREBOWL_ITEMTIMELIMIT= -26075,			// ��Ʒ�۱������Ѵﵽ��������
	ERROR_TREASUREBOWL_BAGGAGEFULL = -26074,			// �����ռ䲻�������ܾ۱�
	ERROR_TREASUREBOWL_FAILED = -26073,					// �۱�ʧ��
	ERROR_TREASUREBOWL_MONEYNOTENOUGH	= -26072,		// �۱�ʱ��Ǯ����
};

// �ƶ�����ʱ�Ĵ����� ( -26149 - -26100 )
enum EMoveItem
{
	ERROR_MOVEITEM_SUCCESS							=	-26149	,			// �ƶ�����ʱ���ƶ��ɹ�
	ERROR_MOVEITEM_SAMEINDEX							=	-26148	,		// �ƶ�����ʱ��Դ��Ŀ����ͬ
	ERROR_MOVEITEM_ITEMNOTEXIST							=	-26147	,		// �ƶ�����ʱ�����߲�����
	ERROR_MOVEITEM_DESINVALID							=	-26146	,		// �ƶ�����ʱ���ƶ���Ŀ����Ч
	ERROR_MOVEITEM_SRCINVALID							=	-26145	,		// �ƶ�����ʱ���ƶ���Դ��Ч
	ERROR_MOVEITEM_SLOTINVALID							=	-26144	,		// �ƶ�����ʱ������������Ч
	ERROR_MOVEITEM_ITEMLOCKED							=	-26143	,		// �ƶ�����ʱ�����߱�����
	ERROR_MOVEITEM_NOTSERVICE							=	-26142	,		// �ƶ�����ʱ��û�д��ڲֿ����״̬
	ERROR_MOVEITEM_KITBAGINVALID							=	-26141	,	// �������ƶ���Ʒ�����������Ѿ�ʧЧ
	ERROR_MOVEITEM_DESINDEXINVALID							=	-26140	,	// Ŀ���������Ϸ�
};

// ��ӵ���ʱ�Ĵ����� ( -26199 - -26150 )
enum EInsertItem
{
	ERROR_INSERTITEM_SUCCESS		= -26199,		// ��ӵ���ʱ����ӳɹ�
	ERROR_INSERTITEM_NOSPACE= -26198,						// ��ӵ���ʱ���ռ䲻����
	ERROR_INSERTITEM_INVALIDNUM= -26197,					// ��ӵ���ʱ����������ȷ
};

// ɾ������ʱ�Ĵ����� ( -26249 - -26200 )
enum ERemoveItem
{
	ERROR_REMOVEITEM_SUCCESS		= -26249,		// ɾ������ʱ��ɾ���ɹ�
	ERROR_REMOVEITEM_ITEMNOTEXIST= -26248,					// ɾ������ʱ�����߲�����
	ERROR_REMOVEITEM_ITEMLOCKED= -26247,					// ɾ������ʱ�����߱�����
};

// װ������ʱ�Ĵ����� ( -26299 - -26250 )
enum EEquipItem
{
	ERROR_EQUIPITEM_SUCCESS							=	-26299	,			// װ������ʱ���ƶ��ɹ�
	ERROR_EQUIPITEM_ITEMNOTEXIST							=	-26298	,	// װ������ʱ�����߲�����
	ERROR_EQUIPITEM_NOTEQUIPABLE							=	-26297	,	// װ������ʱ�����ǿ���װ���ĵ���
	ERROR_EQUIPITEM_NOSPACE							=	-26296	,			// װ������ʱ���ռ䲻����
	ERROR_EQUIPITEM_NEEDMORECON							=	-26295	,		// װ������ʱ����Ҫ���������
	ERROR_EQUIPITEM_NEEDMORESTA							=	-26294	,		// װ������ʱ����Ҫ���������
	ERROR_EQUIPITEM_NEEDMORESPR							=	-26293	,		// װ������ʱ����Ҫ����ľ���
	ERROR_EQUIPITEM_NEEDMOREWIS							=	-26292	,		// װ������ʱ����Ҫ������ǻ�
	ERROR_EQUIPITEM_NEEDMORESTR							=	-26291	,		// װ������ʱ����Ҫ���������
	ERROR_EQUIPITEM_NEEDMORELEVEL							=	-26290	,	// װ������ʱ����Ҫ����ĵȼ�
	ERROR_EQUIPITEM_NEEDSEX							=	-26289	,			// װ������ʱ����Ҫ��ȷ���Ա�
	ERROR_EQUIPITEM_NEEDMETIER							=	-26288	,		// װ������ʱ����Ҫ��ȷ��ְҵ
	ERROR_EQUIPITEM_INVALIDTIME							=	-26287,			// װ������ʱ���Ѿ�����
	ERROR_EQUIPITEM_CANOTEXCHANGE						=	-26286,			// �������Ѿ����ڵİ����е�װ���滻���ϵ�װ��
};

// ж�µ���ʱ�Ĵ����� ( -26349 - -26300 )
enum EUnEquipItem
{
	ERROR_UNEQUIPITEM_SUCCESS		= -26349,		// ����װ��ʱ�����³ɹ�
	ERROR_UNEQUIPITEM_DESINVALID= -26348,					// ����װ��ʱ��Ŀ����Ч
	ERROR_UNEQUIPITEM_ITEMNOTEXIST= -26347,					// ����װ��ʱ�����߲�����
	ERROR_UNEQUIPITEM_EXPIREDBAG  = -26346,					// ����װ��ʱ��Ŀ������Ѿ�����
};

// ʹ�ü���ʱ�Ĵ����� ( -26399 - -26350 )
enum EUseSkill
{
	ERROR_USESKILL_SKILLNOTFOUND							=	-26399	,				// ʹ�ü���ʱ�����ܲ�����
	ERROR_USESKILL_TEMPATENOTFOUND							=	-26398	,				// ʹ�ü���ʱ������ģ�治����
	ERROR_USESKILL_TARGETNOTFOUND							=	-26397	,				// ʹ�ü���ʱ��Ŀ���Ҳ���
	ERROR_USESKILL_TARGETDIE							=	-26396	,					// ʹ�ü���ʱ��Ŀ���Ѿ�����
	ERROR_USESKILL_WEAPONNEED							=	-26395	,					// ʹ�ü���ʱ���ֳ��������Ͳ�ƥ��
	ERROR_USESKILL_NEEDMOREMANA							=	-26394	,					// ʹ�ü���ʱ����Ҫ����ķ���ֵ
	ERROR_USESKILL_NEEDMORELIFE							=	-26393	,					// ʹ�ü���ʱ����Ҫ���������ֵ
	ERROR_USESKILL_NEEDMOREITEM							=	-26392	,					// ʹ�ü���ʱ����Ҫ����ĵ���
	ERROR_USESKILL_SOURCEDIE							=	-26391	,					// ʹ�ü���ʱ��ʩ�����Ѿ�����
	ERROR_USESKILL_OUTOFRANGE							=	-26390	,					// ʹ�ü���ʱ�����벻��
	ERROR_USESKILL_NOTCOOLDOWN							=	-26389	,					// ʹ�ü���ʱ��û����ȴ
	ERROR_USESKILL_SILENCE							=	-26388	,						// ʹ�ü���ʱ����Ĭ״̬�²���ʹ�ü���
	ERROR_USESKILL_TARGETINVALID							=	-26387	,				// ʹ�ü���ʱ�����ܶԸ�Ŀ��ʹ��
	ERROR_USESKILL_PKPROTECT							=	-26386	,					// ʹ�ü���ʱ���㲻�ܶ��Ǹ�Ŀ��ʹ��
	ERROR_USESKILL_ERRDEST							=	-26385	,						// ��ЧĿ��
	ERROR_USESKILL_UNUSE							=	-26384	,						// ����ʹ�ü���
	ERROR_USESKILL_EPTUNAVAILABLE          							=	-26383	,		// װ���Ѿ���
	ERROR_USESKILL_ONHORSE							=	-26382	,						// ���������޷�����
	ERROR_USESKILL_INSERTBUFF_DISSATISFY							=	-26381	,		// Buff����������
	ERROR_USESKILL_INSERTBUFF_TIMEADD							=	-26380	,			// ʱ�����
	ERROR_USESKILL_INSERTBUFF_UNTEMPLATE							=	-26379	,		// ������
	ERROR_USESKILL_INSERTBUFF_LARGE							=	-26378	,				// ��ǿЧ��
	ERROR_USESKILL_INSERTBUFF_FULL							=	-26377	,				// buff��
	ERROR_USESKILL_SRCRESIST								=	-26376,					// �Է��޷�����
	ERROR_USESKILL_TARGETLEVELHIGH							=	-26375,					// ʹ�ü���ʱ���Է��ȼ�����
	ERROR_USESKILL_BUFFTIME_LIMIT							=   -26374,					// buffʱ����Ӵﵽ����
	ERROR_USESKILL_MW_DISALLOW_MAP							=   -26373,					// ��ǰ���������ڵ�ǰ��ͼʹ�ü���
	ERROR_USESKILL_INSERTBUFF_REMOVECOUNT					=	-26372,					// ����buff����
};

// �ƶ������� ( -26449 - -26400 )
enum
{
	ERR_PLAYER_CHANNETMOVE = -26449,
};

// ��ѯ����ʱ�Ĵ����� ( -26499 - -26450 )
enum EProperty
{
	ERROR_PROPERTY_ENTITYNOTFOUND							=	-26499	,		// ��ѯ����ʱ��ʵ�岻����
	ERROR_PROPERTY_ENTITYTYPEINVALID							=	-26498	,	// ��ѯ����ʱ��ʵ�����ʹ���
	ERROR_PROPERTY_DIPLOIDLESS							=	-26497	,			// ˫��ʱ�䲻��
	ERROR_PROPERTY_HASFREEZE							=	-26496	,			// �Ѷ��ᣬ��ⶳ
	ERROR_PROPERTY_NOTDIPLOID							=	-26495	,			// û����ȡ˫�������足��
	ERROR_PROPERTY_NOTFREEZE							=	-26494	,			// �Ƕ���״̬������ⶳ
	ERROR_PROPERTY_NOTNEEDFREEZE							=	-26493	,		// �Ѿ����ᣬ�����ٴζ���
	ERROR_PROPERTY_NOTVALIDDIPLOID							=	-26492	,		// ˫��ʱ����Ч
	ERROR_PROPERTY_OVERFLOWOBTAIN							=	-26491	,		// ˫��ʱ���������ȡ4Сʱ
	ERROR_PROPERTY_MONEYUPDATEERROR							=	-26490	,		// ��Ǯ�ı���̫��ÿ�����1000ͭ
	ERROR_PROPERTY_DIPLOIDSUCCESS							=	-26489	,		// ��ȡ˫���ɹ�
	ERROR_PROPERTY_FREEZESUCCESS							=	-26488	,		// ˫������ɹ�
	ERROR_PROPERTY_UNFREEZESUCCESS							=	-26487	,		// ˫���ⶳ�ɹ�
	ERROR_PROPERTY_DIPLOIDDISAPPEAR							=	-26486	,		// ˫��״̬��ʧ
	ERROR_PROPERTY_MONEYNOTENOUGH							=	-26485	,		// ����ʱ����Ǯ����
	ERROR_PROPERTY_TITLENOTEXIST							=	-26484	,		// �ƺŲ�����
	ERROR_PROPERTY_TITLEHASEXIST							=	-26483	,		// �ƺ��Ѵ���
	ERROR_PROPERTY_NOTONLINE								=	-26482	,		// ��ɫ������
    	ERROR_PROPERTY_NOTSHOWEQUIP                             =   -26481  ,       // ��ɫ����ʾװ��
};

// ���ü��ܵ�ʱ�Ĵ����� ( -26549 - -26500 )
enum EClickSP
{
	ERROR_CLICKSP_SUCCESS							=	-26549	,			// ���ü��ܵ�ʱ�����óɹ�
	ERROR_CLICKSP_NEEDMOREPOINT							=	-26548	,		// ���ü��ܵ�ʱ����Ҫ����ļ��ܵ�
	ERROR_CLICKSP_NEEDSKILLPOINT							=	-26547	,	// ���ü��ܵ�ʱ��ָ����Ҫǰ�����ܵļ��ܵ㲻��
	ERROR_CLICKSP_NEEDGENERPOINT							=	-26546	,	// ���ü��ܵ�ʱ��ָ����Ҫǰ����ϵ���ܵ㲻��
	ERROR_CLICKSP_NEEDMORELEVEL							=	-26545	,		// ���ü��ܵ�ʱ����Ҫ����ĵȼ�
	ERROR_CLICKSP_NEEDMETIER							=	-26544	,		// ���ü��ܵ�ʱ�����ֲ��������������ܵ�
	ERROR_CLICKSP_SKILLOVERFLOW							=	-26543	,		// ���ü��ܵ�ʱ��������ѧϰ����ļ�����
	ERROR_CLICKSP_NEEDMONEY							=	-26542	,			// ���ü��ܵ�ʱ����Ҫ����Ľ�Ǯ
	ERROR_CLICKSP_NONEPLAYER							=	-26541	,		// ���ü��ܵ�ʱ���Ҳ������ʵ��(�ͻ��˿��Բ���ʾ)
	ERROR_CLICKSP_NONESKILL							=	-26540	,			// ���ü��ܵ�ʱ���Ҳ���Ҫѧϰ�ļ���
	ERROR_CLICKSP_MONEYNOTENOUGH							=	-26539	,	// ��Ҳ���ѧϰ����

	ERROR_FANGCUN_HASLEARN							= -26538,				// �Ѿ�ѧ����
	ERROR_FANGCUN_NOPRESKILL						= -26537,				// û��ǰ�ü���
	ERROR_FANGCUN_NOITEM							= -26536,				// û�м�����
	ERROR_FANGCUN_LOWLEVEL							= -26535,				// �ȼ�����
};

// ���ܵ�����ʱ�Ĵ����� ( -26599 - -26550 )
enum EResetASP
{
	ERROR_RESETASP_SUCCESS			= -26599,			// ���ü��ܵ�ʱ�����óɹ�
	ERROR_RESETASP_FAILED= -26598,								// ���ü��ܵ�ʧ��
	ERROR_RESETASP_MAXNUM= -26597,								// ���ü��ܵ�ʧ��,����������
	ERROR_RESETTALENT_SUCCESS = -26596,					// �����컯�ɹ�
	ERROR_RESETTALENT_STEPLOW = -26595,					// �����컯�ȼ���
	ERROR_RESETTALENT_UNKNOWN = -26594,					// �����컯δ֪����
};

// ְҵ����ʱ�Ĵ����� ( -26649 - -26600 )
enum EResetMetier
{
	ERROR_RESETMETIER_SUCCESS		= -26649,			// ����ְҵʱ�����óɹ�
};

// ���ܵ�����һ��ʱ�Ĵ����� ( -26699 - -26650 )
enum EResetSSP
{
	ERROR_RESETSSP_SUCCESS			= -26699,			// ���ü��ܵ�һ��ʱ�����óɹ�
	ERROR_RESETSSP_FAIL= -26698,								// ���ü��ܵ�һ��ʱ������ʧ��
};

// �������Ե�ʱ�Ĵ����� ( -26749 - -26700 )
enum EClickPP
{
	ERROR_CLICKPP_SUCCESS			= -26749,			// �������Ե�ʱ�����óɹ�
	ERROR_CLICKPP_NEEDMOREPOINT= -26748,						// �������Ե�ʱ����Ҫ��������Ե�
	ERROR_CLICKPP_PROPERTYINVALID= -26747,						// �������Ե�ʱ��ָ����������Ч
};

// ���Ե�����һ��ʱ�Ĵ����� ( -26799 - -26750 )
enum EResetSPP
{
	ERROR_RESETSPP_SUCCESS			= -26799,			// �������Ե�һ��ʱ,���óɹ�
	ERROR_RESETSPP_OUTOFPROPERTY= -26798,						// �������Ե�һ��ʱ,���Ե㲻����
	ERROR_RESETSPP_PROPERTYINVALID= -26797,						// �������Ե�һ��ʱ,ָ����������Ч
};

// ���Ե��������е�ʱ�Ĵ����� ( -26849 - -26800 )
enum EResetAPP
{
	ERROR_RESETAPP_SUCCESS			= -26849,			// �������Ե����е�ʱ,���óɹ�
	ERROR_RESETAPP_FAILED= -26848,								// �������Ե�ʧ��
	ERROR_RESETAPP_MAXNUM= -26847,								// �������Ե�ʧ��,����������
};

// ��ͨ������������� ( -26899 - -26850 )
enum ENormalAttack
{
	ERROR_NORMALATTACK_NOWEAPON				= -26899,		// ����û����������
	ERROR_NORMALATTACK_NOTWEAPON= -26898,							// �������ŵĲ�������
	ERROR_NORMALATTACK_OUTOFRANGE= -26897,							// ���벻��
	ERROR_NORMALATTACK_SRCSTATEINVALID= -26896,						// Դ״̬����ȷ
	ERROR_NORMALATTACK_DESSTATEINVALID= -26895,						// Ŀ��״̬����ȷ
	ERROR_NORMALATTACK_NOTCOOLDOWN= -26894,						// ���ܻ�����ʹ��
};

// ���NPC������ ( -26949 - -26900 )
enum EClickNpc
{
	ERROR_CLICKNPC_OUTOFRANGE		=	-26949,		// ���벻��
	ERROR_CLICKNPC_STATEINVALID=	-26948,					// ״̬��Ч
	ERROR_CLICKNPC_TARGETINVALID=	-26947,					// Ŀ����Ч
	ERROR_CLICKNPC_OUTOFMONEY=	-26946,						// ��Ҳ���
	ERROR_CLICKNPC_NOTMETIER=	-26945,						// ְҵ��ƥ��
	ERROR_CLICKNPC_BOXOWNER_ERR=	-26944,					// ������䲻������
    ERROR_CLICKNPC_BOXHASPICKED= -26943,                    // ����������Ѿ�ʰȡ����
};

// �Ӵ����� ( -26959 - -26950 )
enum EThrow
{
	ERROR_THROW_OUTOFMONEY			=	-26959,		// ��Ҳ���
	ERROR_PICK_CANNOT=	-26958,								// ��ʰȡȨ����ʱ��ʰȡ
};

// ʹ�õ��ߴ����� ( -27049 - -27000 )
enum EUseItem
{
	ERROR_ITEMSUCCESS							=	-27049	,			// ʹ�óɹ�
	ERROR_ITEMNOTEXIST							=	-27048	,			// ��Ʒ������
	ERROR_TPLNOTEXIST							=	-27047	,			// ģ�岻����
	ERROR_WRONGTYPE							=	-27046	,				// ���ʹ���
	ERROR_NOTENOUGHPOINT							=	-27045	,		// ��������
	ERROR_NOTCOOLDOWN							=	-27044	,			// û����ȴ
	ERROR_RECOVERING							=	-27043	,			// ���߻ָ���
	ERROR_RANDOMTP							=	-27042	,				// �������
	ERROR_RETURNTP							=	-27041	,				// ��ڴ���
	ERROR_REMEMBERTP							=	-27040	,			// ���䴫��
	ERROR_TOWNTP							=	-27039	,				// �سǴ���
	ERROR_SRCDEAD							=	-27038	,				// ʹ��������
	ERROR_UNUSEITEM							=	-27037	,				// �����޷���ҩ״̬
	ERROR_NOTTASKIITEM							=	-27036	,			// �����������
	ERROR_CANTUSE							=	-27035	,				// ��������߲���ʹ��
	ERROR_OUTOFRANGE							=	-27034	,			// ��������߱�����ָ���ص�ʹ��		
	ERROR_OUTNATION							=	-27033	,				// ֻ���ڱ���ʹ��
	ERROR_BAGGAGEFULL							=	-27032	,			// �����ˣ������ٲ���������
	ERROR_LEVELLOW							=	-27031	,				// �ȼ�����
	ERROR_METIERDIF							=	-27030	,				// ְҵ�����
	ERROR_HORSE							=	-27029	,					// �����߼�
	ERROR_FULLHP							=	-27028	,				// ��ҩѪ����
	ERROR_FULLMP							=	-27027	,				
	ERROR_RETURNPAPER							=	-27026	,			// ���ɷ��ؾ�
	ERROR_TELESYMBOL							=	-27025	,			// ���ͷ�
	ERROR_STOVE							=	-27024	,					// ָ��¯ʯ
	ERROR_CANNOTRIDE							=	-27023	,			// �޷�ʹ������
	ERROR_FOREIGNUSE							=	-27022	,			// ����޷�ʹ�õ���
	ERROR_ITEMLOCKED							=	-27021	,				// ��Ʒ����
	ERROR_NOSENDNPC							=	-27020	,				// ��û�л���NPC�� 
	ERROR_NPCNOBUFF							=	-27019	,				// ���Ļ���NPC����û�����BUFF
	ERROR_APFULL							=	-27018	,				// ���Ļ���ֵ����������Ҫʹ��ҩƷ
	ERROR_CANNUSEITEM							=	-27017	,			// ����ʹ����Ʒ
	ERROR_ISVIP							=	-27016	,					// �Ѿ��ǻ�Ա
	ERROR_INVALIDVIP							=	-27015	,			// ��Ч��Ա����
	ERROR_USEVIPITEMSUCCESS							=	-27014	,		// ��Ա��ͨ�ɹ�
	ERROR_LOWERCLEANITEM							=	-27013	,		// ����ʹ�õͼ�ϴ���	-27013
	ERROR_LEVELLOWER							=	-27012	,			// ����30������ʹ��Ǳ��ϴ��� -27012
	ERROR_PPINIT							=	-27011	,				// Ǳ�ܵ��Ѿ��ǳ�ʼ�� -27011
	ERROR_SPINIT							=	-27010	,				// ���ܵ��Ѿ��ǳ�ʼ�� -27010
	ERROR_WRONGPLACE 							=	-27009	,			// ʹ�õ�λ�ò���ȷ -27009
	ERROR_REDNOUSE							=	-27008	,				// ��������ʹ��
	ERROR_CANNOTOFF							=   -27007	,				// �赲��������
	ERROR_RIDENOAP							=	-27006,					// �������㲻����
	ERROR_LEVELHIGH							=	-27005,					// �ȼ�����
	ERROR_INWEDDINGHALL						=	-27004,					// �����ò��ܴ��������
	ERROR_NOTRED							=	-27003,					// ��������ʹ��	
	ERROR_SUMMONOFFLINE						=	-27002,					// ʹ���ټ�ʱ��Ҳ�����
	ERROR_SUMMONDIFFCOUNTRY					=	-27001,					// �ټ�ʱ��Ӫ��ͬ
	ERROR_SUMMONWRONGPLACE					=	-27000,					// �ó��������ټ�
	ERROR_NOSTAR							=	-26999,					// �޷�ժ��
	ERROR_STARHIGHLEVEL						=	-26998,					// ���ǵȼ���
	ERROR_STARHIGHSTAR						=	-26997,					// �����Ǽ���
	ERROR_NOITEM							=   -26996,					// ʹ��ʱȱ����Ʒ
	ERROR_BLACKPILLSNONEED					=   -26995,					// û����Ч������ʱ�䣬���óԺڹ���
	ERROR_USERED							=	-26994,					// ʹ��������
	ERROR_NOTUSEMAP							=	-26993,					// ʹ�õ�ͼ����
	ERROR_BLACKPILLS_MAXLEVEL				=	-26992,					// �Ѵﵽ���ȼ�������ʹ�úڹ���
	ERROR_BLACKPILLS_MAXTIME				=	-26991,					// �ڹ�����ۻ�ʱ�䳬�����
	ERROR_BLACKPILLS_DIFFRENTBLACKPILLID	=	-26990,					// ʹ�õĺڹ������ʹ�õĺڹ��費��ͬһ����
	ERROR_EXPPILLS_MAXLEVEL					=	-26989,					// ���ȼ�����ʹ�þ��鵤
	ERROR_EXPPILLS_LEVELLOW					=	-26988,					// �ȼ���������ʹ�þ��鵤
	ERROR_BAIHUA_TIMEOUT					=	-26987,					// ���İٻ���������ѹ���(ʹ��ʱ��ʾ)
	ERROR_BAIHUA_BAGFULL					=	-26986,					// ������ ���ܿ����ٻ��������
	ERROR_BAIHUA_OVERTM						=	-26985,					// ���İٻ����ӳƺ��ѹ��ڡ����İٻ����ӵ����ѹ��ڡ����İٻ����Ӽ����ѹ��ڡ�ϵͳ��������Ʒ��ȫ���ջء�
	ERROR_DIGITALFIREWORKS_WRONGITEM		=	-26984,					// ʹ�õ���Ʒ����������
	ERROR_DIGITALFIREWORKS_WRONGTYPE		=	-26983,					// �������񻨲���ʹ�ø���Ч
	ERROR_DIGITALFIREWORKS_TO0MUCHWORDS		=	-26982,					// �������񻨲���ʹ����ô����ַ�
	ERROR_FAME_LIMIT						=	-26981,					// �����������޷�ʹ��
	ERROR_EXPTOME_MAXLEVEL	=	-26980,		//ʹ�������ĵµȼ�����
	ERROR_EXPTOME_LOWLEVEL	=	-26979,		//ʹ�������ĵµȼ�����
};

// ���������� ( -27099 - -27050 )

enum EProduceItem
{
	ERROR_PROSUCCESS			=	-27099	,			// �����ɹ�
	ERROR_PRONOPRODUCE			=	-27098	,			// �޷�����������Ʒ
	ERROR_PRONOMATERIAL			=	-27097	,		// ���ϲ���
	ERROR_PRONOSPACE			=	-27096	,			// �����ռ䲻��
	ERROR_PRONOTYPE			=	-27095	,			// ���ʹ���
	ERROR_ATTACKCANCEL			=	-27094	,			// �ܵ�������������ֹ
	ERROR_MOVECANCEL			=	-27093	,			// �ƶ���������ֹ
	ERROR_PROLOWLEVEL			=	-27092	,			// �ȼ�����
	ERROR_PRONOMONEY			=	-27091	,			// ��Ǯ����
	EEROR_PROLEVELUP			=	-27090	,			// ��������
	ERROR_PROCANCEL			=	-27089	,			// �����ж�
};

// ����װ�������� ( -27149 - -27100 )
enum EUpgItem
{
	ERROR_UPGSUCCESS			= -27149,				// �����ɹ�
	ERROR_UPGNOTYPE= -27148,									// ������Ʒ���Ͳ���
	ERROR_UPGLIMIT= -27147,										// ��װ���Ѿ��������		
	ERROR_UPGNOTEXIST= -27146,									// ����ָ���ĵ��߲�����
	ERROR_UPGCANCEL= -27145,									// �����ж�
	ERROR_UPGEQUIPBINDBYITEM= -27144,							// ��Ѫ��װ����������
};

// ����װ�������� ( -27199 - -27150 )
enum EMendResult
{
	EUIPMENT_SUCCESS				= -27199,		// ����ɹ�
	EUIPMENT_MONEYNOTENOUGH= -27198,						// ��Ǯ����
	EUIPMENT_MENDNOTNEED= -27197,							// װ������Ҫ���� 
	EUIPMENT_NOTEUIPMENT= -27196,							// �����װ��

};

// ��Ƕ���� ( -27249 - -27200 )
enum EINSERTRUNE
{
	ERROR_RUNESUCCESS			= -27249,				// ��Ƕ�ɹ�
	ERROR_RUNENOTYPE= -27248,									// ������Ʒ���Ͳ���
	ERROR_CANNOTINSERT= -27247,									// �޷���Ƕ
	ERROR_RUNEEQUIPBINDEDBYITEM= -27246,						// ��Ѫװ�����ܽ��з�����Ƕ
};

// ��Ƕ��ʯ ( -27299 - -27250 )
enum EINSERTJEWEL
{
	ERROR_JEWELSUCCESS							=	-27299	,					// ��Ƕ�ɹ�
	ERROR_JEWELNOTYPE							=	-27298	,					// ��Ʒ���Ͳ���
	ERROR_JEWELWRONGSLOT							=	-27297	,				// �������ָ���İ���
	ERROR_JEWELSLOTCLOSED							=	-27296	,				// ����δ��
	ERROR_JEWELOPENFAIL							=	-27295	,					// �޷��򿪰���
	ERROR_JEWELLESSEGG							=	-27294	,					// �򿪲۵�Ԫ��������
	ERROR_JEWELEATFAIL							=	-27293	,					// ��װ��ʧ��
	ERROR_COMPOSEFAIL							=	-27292	,					// �ϳ�ʧ��
	ERROR_CANNOTEAT							=	-27291	,						// ���ܱ�����¯�Ե��ĵ��߷�����������
	ERROR_EQUIPBINDEDBYITEM							=	-27290	,				// �ֶ��󶨵���Ʒ���ܱ�����
	ERROR_JEWELEUIQPBINDEDBYITEM							=	-27289	,		// �ֶ��󶨵���Ʒ������Ƕ��ʯ
	ERROR_OPENSLOT_EQUIPBINDEDBYITEM							=	-27288	,	// �ֶ��󶨵���Ʒ����װ������
	ERROR_EATWRONGTYPE							= -27287,						// ��װ�����Ͳ���
	ERROR_CARVE_NOCARD							= -27286,						// ���������Ͳ���
	ERROR_CARVE_CANNOT							= -27285,						// ���ܵ���
	ERROR_CARVE_NOMONEY							= -27284,						// ��Ǯ����
	ERROR_CARVE_NOSPACE							= -27283,						// ��Ҫ����һ���ո�
	ERROR_CARVE_BINDED							= -27282,						// �Ѿ�����
};

// ��Ҵ��� ( -27349 - -27300 )
enum ETELEPORT
{
	ERROR_TELESUCCESS		= -27349,					// ���ͳɹ�
	ERROR_TELENONPC= -27348,									// NPCû�д��͹���
	ERROR_TELENOFEE= -27347,									// ���ò���
	ERROR_INSERVICE= -27346,									// �����У����ܴ���
	ERROR_TELEPORT_NOITEM= -27345,								// �޴�����Ҫ��Ʒ
	ERROR_TELEPORT_MAPLEVELLIMIT= -27344,						// ����ʱ��ͼ�ȼ�����
	ERROR_TELEPORT_CALLTIMEOUT= -27343,							// ����ʱ�ٻ��Ѿ���ʱ
	ERROR_TELEPORT_NOBUFF	= -27342,							// ����ʱ��buff
	ERROR_TELEPORT_NOLEVEL	= -27341,							// ����ʱ�ȼ�����
};

// �ı�PKģʽ ( -27399 - -27350 )
enum ECHANGEPKMODE
{
	ERROR_CHANGEPKMODE_SUCCESS				= -27399,		// �ı�PKģʽ�ɹ�
	ERROR_CHANGEPKMODE_NEEDMORELEVEL= -27398,						// �ȼ�����
	ERROR_CHANGEPKMODE_NONEPKMODE= -27397,							// ��Ч��PKģʽ
	ERROR_CHANGEPKMODE_SAMEPKMODE= -27396,							// ��ͬ��PKģʽ,�����л�
	ERROR_CHANGEPKMODE_UNKNOWN= -27395,								// δ֪����
	ERROR_CHANGEPKMODE_BADPK= -27394,								// ����PK�޷��л�PKģʽ
	ERROR_CHANGEPKMODE_WORLDWAR = -27393,							// ��Ӫ��ս�޷��л�PKģʽ
};

// ����¶������ ( -27449 - -27400 )
enum EOPERATION
{
	ERROR_ADDSLOTPUSHERROR							=	-27449	,			// ���Ӱ��۷���ʧ��
	ERROR_ADDSLOTPOPERROR							=	-27448	,			// ���Ӱ����ó�ʧ��
	ERROR_ADDSLOTERROR							=	-27447	,				// ���Ӱ���ʧ��
	ERROR_REMOVEJEWELPUSHERROR							=	-27446	,		// ժ����ʯ����ʧ��
	ERROR_REMOVEJEWELPOPERROR							=	-27445	,		// ժ����ʯ�ó�ʧ��
	ERROR_REMOVEJEWELERROR							=	-27444	,			// ժ����ʯʧ��
	ERROR_JUDGEPUSHERROR							=	-27443	,			// ����װ������ʧ��
	ERROR_JUDGEPOPERROR							=	-27442	,				// ����װ���ó�ʧ��
	ERROR_JUDGEERROR							=	-27441	,				// ����װ��ʧ��
	ERROR_CHANGEPUSHERROR							=	-27440	,			// ת�����Է���ʧ��
	ERROR_CHANGEPOPERROR							=	-27439	,			// ת�������ó�ʧ��
	ERROR_CHANGEERROR							=	-27438	,				// ת������ʧ��
	ERROR_JEWCOMPUSHERROR							=	-27437	,			// ��ʯ�ϳɷ���ʧ��
	ERROR_JEWCOMPOPERROR							=	-27436	,			// ��ʯ�ϳ��ó�ʧ��
	ERROR_JEWCOMERROR							=	-27435	,				// ��ʯ�ϳ�ʧ��
	ERROR_MULTICOMERROR							=	-27434	,				// ���Ӻϳ�ʧ��
	ERROR_MULTICOMNOTENOUGH							=	-27433	,			// ���Ӻϳ���ֵ����
	ERROR_MULTICOMFULL							=	-27432	,				// ���Ӻϳɰ�����
	ERROR_CLICKTALENTFAILED							=	-27431	,			// ����컯��ʧ��
	ERROR_INCREASETALENTFAILED							=	-27430	,		// �컯����ʧ��
	ERROR_CLICKTALENT_NOMONEY							=	-27429	,		// ����컯��Ǯ����
	ERROR_CLICKTALENT_MAX							=	-27428	,			// ����컯���Ѿ��ﵽ���
	ERROR_CLICKTALENT_NOPOINT							=	-27427	,		// ����컯���������
	ERROR_MULTIPUSHERROR							=	-27426	,			// ���Ӻϳɷ���ʧ��
	ERROR_MULTIPOPERROR							=	-27425	,				// ���Ӻϳ��ó�ʧ��
	ERROR_ADDWIZARD_UNKNOWN							=	-27424	,			// �Ż��ӵ�ʧ��
	ERROR_ADDWIZARD_NOTENOUGH							=	-27423	,		// �Ż��ӵ��������
	ERROR_GETTREND_NOMONEY							=	-27422	,			// ����Ǯ����
	ERROR_JEWCOMFAIL							=	-27421	,				// ��ʯ�ϳ�ʧ��
	ERROR_JEWREMOVE_EQUIPBINDEDBYITEM							=	-27420,	// ��Ѫ��װ�������Ƴ���ʯ,
	ERROR_ADDSLOT_EQUIPBINDEDBYITEM 							=	-27419,	// ��Ѫ��װ���������Ӱ���,
	ERROR_JUDGE_EQUIPBINDEDBYITEM 							=	-27418	,	// ��Ѫ��װ�����ܽ���װ������
	ERROR_CHANGERES_EQUIPBINDEDBYITEM 							=	-27417,		// ��Ѫ��װ�����ܽ���װ������	,
	ERROR_CHANGEEQUIPERROR									= -27416,		// ת��װ������ʧ��
	ERROR_CANNOTEXTRA										= -27415,		// �޷����п�ӡ
	ERROR_HASNOMARRINTIMACY									= -27414,		// û�н�鲻�ܽ��н��װ��������
	ERROR_MARRINTIMACYNOTENOUGH								= -27413,		// �������ܶȲ���,���ܶһ�װ��
	ERROR_NOTINSWORNTEAM									= -27412,		// û�н�ݲ��ܽ��н��װ���һ�
	ERROR_SWORNCOMPOSE_NUMBERNOTENOUGH						= -27411,		// ��ݶһ�ʱ������
	ERROR_SWORNCOMPOSE_NOTINSAMESWORNTEAM					= -27410,		// ��ݶһ�ʱ���������˲����ڽ������
	ERROR_SWORNCOMPOSE_INTIMACYNOTENOUGH					= -27409,		// ��ݶһ�ʱ������ܶȲ���
};

//map			( -30999 - -30000 )
//friend		( -32999 - -31000 )

enum EFriendModuleErrorCode
{
	ERROR_DES_PLAYER_IS_NOT_ONLINE							=	-32999	,	 // �Է���Ҳ�����
	ERROR_YOUR_LIST_FULL							=	-32998	,				   // ��ĺ����б����ˣ���Ӻ���ʧ��
	ERROR_DES_LIST_FULL							=	-32997	,					   // �Է������б����ˣ���Ӻ���ʧ��
	ERROR_CANT_ADD_SELF							=	-32996	,					   // ��������Լ�
	ERROR_GROUP_NAME_TOO_LONG							=	-32995	,		   // ������̫��
	ERROR_MOVE_FRIEND_FAIL							=	-32994	,			 // �ƶ����ѷ���ʧ��
	ERROR_MESSAGE_TOO_LONG							=	-32993	,			 // ˽����Ϣ̫��
	ERROR_YOU_ARE_BLACK							=	-32992	,				 // ���ڶԷ��������У�����˽��
	ERROR_DES_OFFLINE			    				=	-32991	,			 // �Է������ߣ�����˽��
	ERROR_MOVE_BLACK_FAIL							=	-32990	,			 // �ƶ����ѵ�������ʧ��
	ERROR_INVALID_PLAYER							=	-32989	,			 // ��Ҳ�����
	ERROR_LOCKENEMYFAIL							=	-32988	,					// �������ʧ��
	ERROR_STRANGERBLOCK							=	-32987	,					// �����ˡ��ܾ�İ������Ϣ������ҷ�����Ϣ" ShowText="�Է�����
	ERROR_ADDOTHERNATIONFRIEND							=	-32986	,			// "��������Ҽ�Ϊ����" ShowText="������������ҽ������ѹ�ϵ
	ERROR_ADDSELFTOBLACK							=	-32985	,				// ���ܼ��Լ���������
	ERROR_ISFRIEND							=	-32984	,						// �Ѿ��Ǻ����ˣ����ʧ��
	ERROR_YOU_ARE_BLACK_ADD							=	-32983	,				// ���ڶԷ����������Ӻ���ʧ��
	ERROR_ADDBLACKFAIL							=	-32982	,					// ��������
	ERROR_ADDBLACKFAIL_EXSIT							=	-32981	,			// �Ѵ��ڵĺ�����
	ERROR_DES_IN_YOUR_BLACK							=	-32980	,				// �˽�ɫ�ѱ������Ρ�����������Ϣ��
	ERROR_MASTER_LOWLEVEL							=	-32979	,				// ǰ����ҵȼ�����
	ERROR_MASTER_NOTONLINE							=	-32978	,				// ǰ����Ҳ�����
	ERROR_MASTER_HIGHLEVEL							=	-32977	,				// ����ҵȼ���
	ERROR_MASTER_NOTNULL							=	-32976	,				// �Ѿ�����ǰ��
	ERROR_MASTER_FULL							=	-32975	,					// ǰ����Һ�����
	ERROR_MASTER_NOSLAVE						=	-32974	,					// ɾ��ʱû�д˺�
	ERROR_JEWCOM_LOWLEVEL						=	-32973	,					// ��ʯ�ϳɵȼ���
	ERROR_MASTER_NOMASTER						=	-32972	,					// ɾ��ʱû�д����
	ERROR_MASTER_CHANGENOMASTER					=	-32971	,					// �ı�ж�ʱ����ǰ��
	ERROR_MASTER_CHANGEOVERFLOW					=	-32970	,					// �ı�ж�ʱ������Χ
	ERROR_MASTER_NOMOREMASTER					=	-32969	,					// ���������ǰ��
	ERROR_MASTER_NOTIMES						=	-32968	,					// ���ǰ����������
	ERROR_MASTER_NOITEM							=	-32967	,					// ȱ�ٵ��߽��
	ERROR_MASTER_NOMONEY						=	-32966	,					// ȱ��Ǯ���
	ERROR_MASTER_REFUSED						=	-32965	,					// �Է��ܾ�
	ERROR_MASTER_NOTSAMEWORLD					=	-32964	,					// ��ͬ��Ӫ���ܰ�ʦ
	ERROR_SWORN_KICK_HASNORIGHT					=	-32963	,					// �������ʱû��Ȩ��
	ERROR_SWORN_KICK_NOTINSWORNTEAM				=	-32962	,					// �������ʱ����֮�˲��ڽ����������
	ERROR_SWORN_LEAVE_NOTINSWORNTEAM			=	-32961	,					// �뿪���ʱ���ڽ����
	ERROR_SWORN_DISBAND_HSARIGHT				=	-32960	,					// ��ɢ���ʱû��Ȩ��
	ERROR_SWORN_CREATE_MEMBERNOTENOUGH			=	-32959	,					// �������ʱ��������(һ���˲��ܴ���)
	ERROR_SWORN_CREATE_HAVENOTEAM				=	-32958	,					// û�ж��鲻�ܴ������
	ERROR_SWORN_CREATE_NOTHEADER				=	-32957	,					// ���Ƕӳ����ܽ��
	ERROR_SWORN_CREATE_INSWORNTEAM				=	-32956	,					// �����������Ѿ���ݣ����ܽ��н��
	ERROR_SWORN_CREATE_INTIMACYNOTENOUGH		=	-32955	,					// �������������ܶȲ��������ܽ��
	ERROR_SWORN_CREATE_HASDITYWORD				=	-32954	,					// ���ƺ������	
	ERROR_SWORN_DISBAND_HASNORIGHT				=	-32953	,					// ��ɢ�������ʱû��Ȩ��
	ERROR_SWORN_CHANGENAME_HASNOWRIGHT			=	-32952	,					// ��ݸ���ʱû��Ȩ��
	ERROR_SWORN_CHANGENAME_HASDIRTYWORD			=	-32951	,					// ��ݸ���ʱ���ƺ������
	ERROR_SWORN_CREATE_MEMBERTOOFAR				=	-32950	,					// �������ʱ�г�Ա����̫Զ
	ERROR_SWORN_CREATE_HASNOTIME				=	-32949	,					// �������ʱû�е���
	ERROR_SWORN_KICKMEMBER_HASNOTIME			=	-32948	,					// ����ʱû�е���
	ERROR_SWORN_DISBAND_HASNOTIME				=	-32947	,					// ��ɢʱû�е���
	ERROR_SWORN_CHANGENAME_HASNOTIME			=	-32946	,					// ����ʱû�е���
	ERROR_DELFRIEND_SPOURSE						=	-32945	,					// ����ϵ����ɾ������
	ERROR_DELFRIEND_INSAMESWORNTEAM				=	-32944	,					// ��ݹ�ϵ����ɾ������
	ERROR_MOVEBLACK_INSAMESWORNTEAM				=	-32943	,					// ��ݹ�ϵ�����ƶ���������
	ERROR_MOVEBLACK_MARRIED						=	-32942	,					// �н���ϵ�����ƶ���������
	ERROR_SWORN_REBUILD_HASNOTEAM				=	-32941	,					// û����Ӳ������¼���
	ERROR_SWORN_REBUILD_NOTHEADER				=	-32940	,					// ���ǽ���ϴ������¼���
	ERROR_SWORN_REBUILD_HASNOSWORN				=	-32939	,					// û�н�ݲ������¼���
	ERROR_SWORN_REBUILD_MEBERTOOFAR				=	-32938	,					// ������ʱ���˾����Զ
	ERROR_SWORN_REBUILD_NEWMEMBERHASSWORN		=	-32936	,					// �����Ѿ��н��
	ERROR_SWORN_REBUILD_MEMBEROFFLIEN			=	-32935	,					// �н�ݳ�Ա���ڶ����У��޷����
	ERROR_SWORN_REBUILD_HASNONEWMEMBER			=	-32934	,					// ��ݼ���ʱ������û���³�Ա
	ERROR_SWORN_REBUILD_HASNOREBUILDITEM		=	-32933	,					// ���³�Աû�м�������Ҫ�ĵ���
	ERROR_SWORN_REBUILD_INTIMACYNOTENOUGH		=	-32932	,					// �����³�Աʱ�������ܶȲ���
};
//team			( -35999 - -33000 )

enum ETeam 
{
	ERROR_DISABLEHANDLE						=	-35999	,					// ��ǰ״̬�£��޷�ִ�д˲���
	ERROR_TEAM_DESBUSY						=	-35998	,					// �Է���æ���޷�������Ӳ���
	ERROR_TEAM_DIFFNATION						=	-35997	,				// �ͶԷ���ͬ�������޷����
	ERROR_TEAM_FULLTEAM							=	-35996	,				// �������� 
	ERROR_TEAM_OVERFAR						=	-35995	,					// �Է�������Ч���룬�޷�����
	ERROR_TEAM_NOTEXIST							=	-35994	,				// �Բ��𣬶��鲻����
	ERROR_TEAM_LEVELLESS						=	-35993	,				// �Բ��������𲻹�
	ERROR_TEAM_SRCINTEAM						=	-35992	,				// �����ж��飬���ɼ�����������
	ERROR_TEAM_DESINTEAM						=	-35991	,				// �Է����ж���
	ERROR_TEAM_SRCNOTTEAM						=	-35990	,				// �Բ�����û�ж���	(0)
	ERROR_TEAM_DESNOTTEAM						=	-35989	,				// �Բ��𣬶Է�û�ж���
	ERROR_TEAM_REFUSE						=	-35988	,					// �Բ��𣬶Է��ܾ�����������
	ERROR_TEAM_DESOFFLINE						=	-35987	,				// �Բ��𣬶Է����ߣ��޷�����
	ERROR_TEAM_MONEYLESS						=	-35986	,				// �Բ��𣬽�Ҳ���
	ERROR_TEAM_COOLINGTIME						=	-35985	,				// �Բ�����ȴʱ��δ��
	ERROR_TEAM_TELEFAILED						=	-35984	,				// ����ʧ��
	ERROR_TEAM_INSERVICE						=	-35983	,				// �����У��޷�����
	ERROR_TEAM_SENDAPPLYTOHEADER						=	-35982	,		// ������ӳ������������
	ERROR_TEAM_NOTHEADER						=	-35981	,				// �Բ��������Ƕӳ����޷�����
	ERROR_TEAM_INVITE_SUCCESS						=	-35980	,			// �������**�ɹ�(0)
	ERROR_TEAM_REQUEST_SUCCESS						=	-35979	,			// ������**�����������
	ERROR_TEAM_INVITE_REFUSE						=	-35978	,			// �Բ���**�ܾ��������������
	ERROR_TEAM_REQUEST_REFUSE						=	-35977	,			// �Բ���**�ܾ��������������
	ERROR_TEAM_CREATE_HASINTEAM							=	-35976	,		// ���ڶ����У��޷��Խ�����
	ERROR_TEAM_INVITE_DESINTEAM							=	-35975	,		// �Է����ж��飬�޷������������
	ERROR_TEAM_REQEUST_SRCINTEAM						=	-35974	,		// ���Ѿ��ڶ����У��޷������������
	ERROR_TEAM_NEWHEAD_NOTHEADER						=	-35973	,		// �����Ƕӳ����޷����жӳ�Ȩ��ת��
	ERROR_TEAM_JOINTEAM							=	-35972	,				// **�������
	ERROR_TEAM_END_SUCCESS						=	-35971	,				// �����ڵĶ����ѽ�ɢ
	ERROR_TEAM_NEWHEAD_SUCCESS						=	-35970	,			// A���ӳ�ת�ø�B(0)
	ERROR_TEAM_CREATE_SUCCESS						=	-35969	,			// �Խ�����ɹ�
	ERROR_TEAM_LEAVE_SUCCESS						=	-35968	,			// **�뿪����
	ERROR_TEAM_KICK_SUCCESS							=	-35967	,			// **���������
	ERROR_TEAM_CLAIM_INTEAM							=	-35966	,			// �����У��޷�����������Ϣ
	ERROR_TEAM_CANTFOLLOW_FAR						=	-35965	,			// ����̫Զ�޷�����
	ERROR_TEAM_OPEN_FOLLOW						=	-35964	,				// ��������״̬
	ERROR_TEAM_CLOSE_FOLLOW							=	-35963	,			// �رո���״̬
	ERROR_TEAM_ASSIGN_RANDOM						=	-35962	,			// ����ģʽΪ���ɷ���
	ERROR_TEAM_ASSIGN_TURN						=	-35961	,				// ����ģʽΪ��������
	ERROR_TEAM_NONATION							=	-35960	,				// û�й������������
	ERROR_TEAM_NOTSAMETEAM						=	-35959	,				// ��ͬ��
	ERROR_TEAM_CHANGED						=	-35958	,					// �����ѱ仯
	ERROR_TEAM_NOTINGAME						=	-35957	,				// ����Ҳ��ڳ���
	ERROR_TEAM_NOTINVITE						=	-35956	,				// û������
	ERROR_TEAM_NOTREQUEST						=	-35955	,				// û������
	ERROR_TEAM_MOREREQ						=	-35954	,					// ������ܵ�������Ϣ�ﵽ����
	ERROR_TEAM_MOREINV						=	-35953	,					// ��ҽ��ܵ�������Ϣ�ﵽ����
	ERROR_TEAM_ASSIGN_PRO						=	-35952	,				// ����ģʽΪ���ʷ���

};

//stall			( -36999 - -36000 )

enum EStall
{
	ERROR_STALL_NOTSAFTYAREAR							=	-36999	,		// ���ڰ�̯��ȫ��					(-36999)
	ERROR_STALL_LEVELLESS							=	-36998	,			// �ȼ�����
	ERROR_STALL_INSAFTYTIME							=	-36997	,			// ��ȫ����ʱ����
	ERROR_STALL_DIFFNATION							=	-36996	,			// ����������
	ERROR_STALL_HASOTHERSTALL							=	-36995	,		// �˵���������̯λ
	ERROR_STALL_HASSTALL							=	-36994	,			// ������̯λ
	ERROR_STALL_CANNOTSELLIT							=	-36993	,		// ���ܳ��۸���Ʒ
	ERROR_STALL_BINDITEM							=	-36992	,			// ����Ʒ�޷��ϼ�
	ERROR_STALL_MASTERMONEYOUT							=	-36991	,		// ̯����Ǯ ����Я������					
	ERROR_STALL_NOTEXIST							=	-36990	,			// ̯λ������						(-36990)
	ERROR_STALL_NAMELONGER							=	-36989	,			// ̯������
	ERROR_STALL_ADLONGER							=	-36988	,			// ������ݹ���
	ERROR_STALL_OFFLINE							=	-36987	,				// ��Ҳ�����
	ERROR_STALL_GOODSCHANGED							=	-36986	,		// ��Ʒ�Ѹ���
	ERROR_STALL_PRICECHANGED							=	-36985	,		// �۸��Ѹ���
	ERROR_STALL_PRICEERROR							=	-36984	,			// �۸񳬷�Χ
	ERROR_STALL_PRICEFAILED							=	-36983	,			// �۸����ʧ��
	ERROR_STALL_BUYGOODSFAILED							=	-36982	,		// ������Ʒʧ��
	ERROR_STALL_GRIDHASSTALL							=	-36981	,		// �������Ѿ���������Ұ�̯		
	ERROR_STALL_SRCMONEYLESS							=	-36980	,		// ��ҽ�Ǯ����					(-36980)
	ERROR_STALL_PUSHUPFAILED							=	-36979	,		// ��Ʒ�ϼ�ʧ��
	ERROR_STALL_CLICKSTALLFAILED							=	-36978	,	// ���̯λʧ��
	ERROR_STALL_FULLGOODS							=	-36977	,			// ̯λ��Ʒ����
	ERROR_STALL_INVALIDOPERATION							=	-36976	,	// ��̯״̬���޷����иò���
	ERROR_STALL_TASKITEM							=	-36975	,			// ������Ʒ�����ϼܳ���
	ERROR_STALL_GOODSNOTEXIST							=	-36974	,		// ��̯λ��Ʒ�޴���
	ERROR_STALL_NOTLOOKENEMY							=	-36973	,		// ���ܲ鿴�й�̯λ
	ERROR_STALL_INHORSE							=	-36972	,				// ����״̬�����ܰ�̯
	ERROR_STALL_NUMBEROVER							=	-36971	,			// ������������					
	ERROR_STALL_INOTHERSERVICE							=	-36970	,		// ����������������				(036970)
	ERROR_STALL_CREATESTALLSUCCESS							=	-36969	,	// ����̯λ�ɹ�
	ERROR_STALL_BAGGAGENOTENOUGH							=	-36968	,	// �˿͹���ʱ�����ռ䲻��
	ERROR_STALL_UPDATEPRICESUCCESS							=	-36967	,	// �۸��޸ĳɹ�
	ERROR_STALL_ERRORSTALLTYPE						= -36966,				// ��̯���ʹ���

};

//chat			( -39999 - -37000 )

enum EChat
{
	ERROR_CHAT_OFFLINE  							=	-39999	,				// �޷��ҵ��������
	ERROR_CHAT_EMPTYMSG             							=	-39998	,	// ȫ���ո���ִ�û���κκ��壬�޷�����
	ERROR_CHAT_EMPTYP2PMSG        							=	-39997	,		// ���ܷ��Ϳ����Ļ�
	ERROR_CHAT_SETCHANNELNULL       							=	-39996	,	// ��������ĳ��Ƶ��
	ERROR_CHAT_CANCELCHANNELNULL    							=	-39995	,	// ȡ��Ƶ��
	ERROR_CHAT_SETCHATDIANULL       							=	-39994	,	// ������������
	ERROR_CHAT_CANCELCHATDIANULL    							=	-39993	,	// ȡ��������������
	ERROR_CHAT_SETWORDCOLNULL       							=	-39992	,	// ���������Զ�����ɫ
	ERROR_CHAT_CANCELWORDCOLNULL  							=	-39991	,		// ȡ�����������Զ�����ɫ
	ERROR_CHAT_CANCELPERCHATNULL    							=	-39990	,	// ȡ����ĳ�˵���������
	ERROR_CHAT_CONTRYCHATLEVELLOW   							=	-39989	,	// ����Ƶ�����Եȼ�����������10��
	ERROR_CHAT_CONTRYMSGSUCESS      							=	-39988	,	// ����Ƶ�����Գɹ�
	ERROR_CHAT_CHANNELCONTRYAPLOW   							=	-39987	,	// ����Ƶ������AP����������10
	ERROR_CHAT_CHANNELWORLDLEVELLOW							=	-39986	,		// ����Ƶ���ȼ�����������30
	ERROR_CHAT_WORLDMSGSUCESS      							=	-39985	,		// ����Ƶ�����Գɹ�
	ERROR_CHAT_CHANNELWORLDAPLOW    							=	-39984	,	// ����Ƶ������AP����������20
	ERROR_CHAT_WORLDCHATFAST        							=	-39983	,	// ���������Ƶ�����Գɹ���180�����ٴη���
	ERROR_CHAT_SCREENLOCK           							=	-39982	,	// ʹ������Ƶ���ܣ���Ļ������ǰ״̬
	ERROR_CHAT_SCREENUNLOCK         							=	-39981	,	// ��Ļ����
	ERROR_CHAT_NOFAMILY             							=	-39980	,	// û�м��岻���ڼ���Ƶ������
	ERROR_CHAT_NOTEAM               							=	-39979	,	// û����Ӳ��������Ƶ������
	ERROR_CHAT_NOBEGTEAM            							=	-39978	,	 // û���ŶӲ������Ŷ�Ƶ������
	ERROR_CHAT_NOCORP               							=	-39977	,	 // û�о��Ų����ھ���Ƶ��������Ϣ
	ERROR_CHAT_CHATFORBIDEN         							=	-39976	,	// ������
	ERROR_CHAT_CHATNOTALLOWED       							=	-39975	,	// ���Ի�δ�����ֻ���ڶ���Ƶ������
	ERROR_CHAT_HAVENOBUGLEITEM      							=	-39974	,	// ������Ƶ������ʱû�����ȵ���
	ERROR_CHAT_HIGHFREQUENCY	    						=	-39973	,		// ���Թ���Ƶ��
	ERROR_CHAT_CHANNELDIRTYWORD     							=	-39972	,	// �Խ�Ƶ�����зǷ���
	ERROR_CHAT_DELETECHATNNEL       							=	-39971	,	// ɾ�����Խ�Ƶ��
	ERROR_CHAT_DELETECHANTNELERROR  							=	-39970	,	// ɾ��Ƶ������
	ERROR_CHAT_CHATMSGSAVED        							=	-39969	,		// ������Ϣ�Ѿ�����
	ERROR_CHAT_SETAUTOCHAT          							=	-39968	,	// �������Զ���������
	ERROR_CHAT_HASNOAUTOCHATITEM    							=	-39967	,	// �����Զ���������ʱû��ʨ�Ӻ�
	ERROR_CHAT_AUTOCHATTIMESHORT    							=	-39966	,	// �Զ��������ʱ��С����ѡƵ���ķ��Լ��ʱ��
	ERROR_CHAT_AUTOCHATTIMELONG     							=	-39965	,	// ������õ��Զ��������ʱ�����5����
	ERROR_CHAT_CHANNELBUGLESUCESS   							=	-39964	,	// ����Ƶ�����Գɹ�
	ERROR_CHAT_BUGLENEEDWAIT       							=	-39963	,		// ʹ�����ȷ��ԣ������Ŷ����
	ERROR_CHAT_MSGREPEATET         							=	-39962	,		// ͬһ�仰�ظ���������
	ERROR_CHAT_INCOOLTIME          							=	-39961	,		// ��¼���߿��������������
	ERROR_CHAT_WORLDBUGLENO		   					=	-39960	,				// ����Ƶ������ʱ�����Ȳ�����
	ERROR_CHAT_BUGLELEVELLIMIT							=	-39959	,				// ����Ƶ�������ȼ�����

};
// task         ( -42999 - -40000 )
enum ETask
{
	ERROR_TASK_SUCCESS							=	-42999	,
	ERROR_TASK_HASACCEPT							=	-42998	,					// �����ѽ���
	ERROR_TASK_HASDONE							=	-42997	,						// ���������
	ERROR_TASK_OUTOFSPACE							=	-42996	,					// �����б�����
	ERROR_TASK_DIALOGIDINVALID							=	-42995	,				// ����Ի�ID��Ч
	ERROR_TASK_TASKIDINVALID							=	-42994	,				// ����ID��Ч
	ERROR_TASK_NOTCOMPLETE							=	-42993	,					// ����û�����
	ERROR_TASK_NOSPACE							=	-42992	,						// û���㹻�İ����ռ�
	ERROR_TASK_ABORTINVALID							=	-42991	,					// �����������
	ERROR_TASK_ACCEPTINVALID							=	-42990	,				// �����������������
	ERROR_TASK_MUTI_AWARD_ERROR							=	-42989	,				// û��ѡ���ѡ������Ʒ
	ERROR_TASK_CANT_DO_INVITE							=	-42988	,				// �Է����ܽ��������(����ķ�������Ӧ)
	ERROR_TASK_ABORTINVALID_NOITEM  							=	-42987	,		// �����ܹ�������	 ��Ϊ���ŵ���Ʒ����ȫ��
	ERROR_TASK_TELEPORTFAIL							=	-42986	,					// ����ʧ��
	ERROR_TASK_CANTABORTMAIN							=	-42985	,				// �����ܷ���
	ERROR_TASK_TALKWITHNPC_FAILED							=	-42984	,			// ��NPC�Ի�ʧ��
	ERROR_TASK_STORAGEMAX							=	-42983	,					// �������Ѿ����ֵ
	ERROR_TASK_BAD_RECV_ITEM							=	-42982	,				// ���������Ʒ�ύ����
	ERROR_TASK_LESS_RECV_ITEM							=	-42981	,				// �ύ�������Ʒ����
	ERROR_TASK_ITEM_BIND_ERROR							=	-42980	,				// ����Ʒ���ֶ��󶨵� �������ڽ�����
	ERROR_TASK_COLLECT_FAIL							=	-42979	,					// �ɼ�ʧ��(�����Ѿ�����)
	ERROR_TASK_COLLECT_GRIDERR							=	-42978	,				// �ɼ�����̫Զ
	ERROR_TASK_NPC_BUSY							=	-42977	,						// NPC���ڱ��������ռ�� 
	ERROR_TASK_SENDNPC_LEAVE							=	-42976	,				// �����뿪�˻���NPC
	ERROR_TASK_LOOP_CD_NOTEND							=	-42975	,				// ��������ȴʱ��δ����
	ERROR_TASK_INVITE_TIMEOUT							=	-42974	,				// �������룺������ʧЧ
	ERROR_TASK_NOT_YOUR_NPC							=	-42973	,					// �����ܺͷ��Լ��ٻ���NPC�Ի�
	ERROR_TASK_ON_END_A_NEW_LOOP							=	-42972	,			// ��ϲ������˱��ܵĻ�����
	ERROR_TASK_ON_END_TRAGEDY10							=	-42971	,				// ��ϲ�������ʮ��
	ERROR_TASK_MAX_RMB_REFRESH							=	-42970	,				// �Ѵﵽÿ�����ʹ��RMBˢ���������
	ERROR_TASK_GOT_CHAIRMAN							=	-42969	,					// �ѽӹ�����ϵ�е���������
	ERROR_TASK_CHAIRMAN_AWARDED							=	-42968	,				// �������������⽱��֪ͨ
	ERROR_TASK_TEAMLOOP_MEMBERGOT						=	-42966	,				// ��ӻ������������Ѿ���ȡ��ӻ�����
	ERROR_TASK_TEAMLOOP_MEMBERCOMP						=	-42965	,				// ��ӻ����������ҵ���ɴ����Ѿ��ﵽ���� 
	ERROR_TASK_TEAMLOOP_MEMBERFULL						=	-42964	,				// ��ӻ����������ҵ������б�����
	ERROR_TASK_TEAMLOOP_YOUNOTHEAD						=	-42963	,				// ��ӻ������㲻�Ƕӳ� ���ܽ�
	ERROR_TASK_TEAMLOOP_MEMBERLESS						=	-42962	,				// ��ӻ����񣺶�����������ȷ ���ܽ�
	ERROR_TASK_TEAMLOOP_MEMBERERR						=	-42961	,				// ��ӻ��������ж����Ա���ڸ���
	ERROR_TASK_TEAMLOOP_CANT_ACCEPT						=	-42960	,				// ��ӻ��������%s���������������
	ERROR_TASK_PUBLISH_PLAYER_LEVEL						=	-42959	,				// �������񣺲����㷢������ɫ���������
	ERROR_TASK_PUBLISH_COLOR_MAX						=	-42958	,				// �������񣺸���ɫ���������ѵ�����
	ERROR_TASK_PUBLISH__MAX_TIMES						=   -42957	,				// �������񣺽��췢�������Ѿ�������
	ERROR_TASK_PUBLISH_NOT_EXIST						=   -42956	,				// ���������������ݲ�����
	ERROR_TASK_UNPUBLISHED								=   -42955	,				// ��������������δ����
			
	ERROR_TASK_HAS_PUBLISHED							=	-42954	,				// ���巢�����������ѷ�������ֹ�ظ�����
	ERROR_TASK_GROUPPUBLISH_TODAYMAX					=   -42953  ,               // ���巢�����񣺽��췢�������Ѿ�������
	ERROR_TASK_GROUPPUBLISH_WEEKMAX						=   -42952  ,               // ���巢������ ���ܷ��������ѵ�����
	ERROR_TASK_PUBLISH_CONDITION_UNENOUGH				=   -42951  ,				// ��������������
	ERROR_TASK_SINGLE_PUBLISH_NOAWARD					=   -42950  ,				// û�п���ȡ�Ľ���


	// û�õ�
	ERROR_TASK_ORP_FAILED			,		// ����ʧ�ܣ�������ʧ�ܣ��������ʧ�ܣ����ڿͻ��˽��йرնԻ��Ȳ�����
};

// trade		( -43999 - -43000 )
enum ETrade
{
	ERROR_TRADE_INTRADE							=	-43999	,			// ������
	ERROR_TRADE_OFFTRADE							=	-43998	,		// �뿪���ף����׿���
	ERROR_TRADE_PLAYERNOTFOUND							=	-43997	,	// ��Ҳ�����
	ERROR_TRADE_GOODSNOTFOUND							=	-43996	,	// ��Ʒ������
	ERROR_TRADE_GOODSINTRADE							=	-43995	,	// ��Ʒ�ڽ�����
	ERROR_TRADE_GOODSOFFTRADE							=	-43994	,	// ��Ʒ���ã����ڽ�����
	ERROR_TRADE_REFUSE							=	-43993	,			// ��������ܾ�
	ERROR_TRADE_INBUSY							=	-43992	,			// ���׷�æ��
	ERROR_TRADE_FAR							=	-43991	,				// ����̫Զ���޷�����
	ERROR_TRADE_END							=	-43990	,				// ���׽�������		(0)
	ERROR_TRADE_SRCBAGLESS							=	-43989	,		// Դ�����ռ䲻��
	ERROR_TRADE_DESBAGLESS							=	-43988	,		// �Է������ռ䲻��
	ERROR_TRADE_OFFLINE							=	-43987	,			// ��ҵ��ߣ����׽���
	ERROR_TRADE_DESMONEYOVER							=	-43986	,	// ����ʱ���Է�����Я������Ľ�Ǯ
	ERROR_TRADE_SAFETIME							=	-43985	,		// ��ȫʱ���ڣ��޷�����
	ERROR_TRADE_BINDITEM							=	-43984	,		// ��Ʒ�󶨣��޷�����
	ERROR_TRADE_INVITESELF							=	-43983	,		// �������Լ�����
	ERROR_TRADE_GOODSLOCKED							=	-43982	,		// ��Ʒ���������޷��䶯��Ϣ
	ERROR_TRADE_GOODSUNLOCKED							=	-43981	,	// ��Ʒ��δ����
	ERROR_TRADE_FAILURE							=	-43980	,			// ����ʧ��	(0)
	ERROR_TRADE_MONEYERROR							=	-43979	,		// ���׽����Ч
	ERROR_TRADE_INVITEREPEATED							=	-43978	,	// �ظ���������
	ERROR_TRADE_INVITETIMEOVER							=	-43977	,	// ���볬ʱ��Ч
	ERROR_TRADE_CANCEL							=	-43976	,			// ���ȡ������
	ERROR_TRADE_MONEYLESS							=	-43975	,		// ������Ҳ���
	ERROR_TRADE_MONEYOVERFLOW							=	-43974	,	// ����ʱ��������Я������Ľ�Ǯ
	ERROR_TRADE_INVITEOVERFLOW							=	-43973	,	// ����������������
	ERROR_TRADE_DESBUSY							=	-43972	,			// �Է���æ���޷����н���
	ERROR_TRADE_MONEYOUT							=	-43971	,		// ��Ǯ���
	ERROR_TRADE_INVITE_SUCCESS							=	-43970	,	// ��������ɹ�(0)
	ERROR_TRADE_DIFFNATION							=	-43969	,		// ������ͬ�����ܽ���
	ERROR_TRADE_NOTPILE								=	-43968	,		// ����������Ʒ����
	ERROR_TRADE_INEXPIREDKITBAG							=	-43967	,	// ���ڱ����������Ʒ�������ڽ���
};


// RedirectMap		( -44999 ~ -44000 )
enum ERedirect
{
	ERR_REDIRECT_PLAYER_IN_MAP      = -44999,
	ERR_REDIRECT_OBJECT_IS_FULL= -44998,
	ERR_REDRIECT_UNKNOW= -44997,
	ERR_REDIRECT_MAP_NOTOPEN= -44996,
	ERR_REDIRECT_MAP_PLAYER_IS_FULL= -44995,
};

// RedirectMap		( -45999 ~ -45000 )
enum ERepetion
{
	ERR_REPETION_PLAYERNUMBER_LESS			= -45999,	// Parame1 Need PlayerNumber, Parame2 Now PlayerNumber
	ERR_REPETION_EVERYDAY_TIME_FULL			= -45998,	// Parame1 EventyDay Time Max, Parame2 PlayerID
	ERR_REPETION_NEED_TASK					= -45997,	// Parame1 TaskID, Parame2 PlayerID
	ERR_REPETION_LEVEL_MIN					= -45996,	// Parame1 Map Need Level, Parame2 Player Level	
	ERR_REPETION_TEAM_MEMBER_FAR			= -45995,	// Parame1 PlayerID
	ERR_REPETION_TEAM_MEMBER_UNINSAMESCENE	= -45994, 	// Parame1 UNINSAMESCENE Player CharID
	ERR_REPETION_ISNOT_HEADER				= -45993,	// ���Ƕӳ�
	ERR_REPETION_DIE						= -45992,	// Parame1 PlayerID
	ERR_REPETION_HOUR						= -45991,	// ʱ�䲻ƥ��
	ERR_REPETION_PVP_WAITLIST_FULL			= -45990,	// ս���ȴ�������
	ERR_REPETION_PVP_LEVEL_NOTFOUND			= -45989,	// �ȼ�����
	ERR_BATTLE_TIMEOUT						= -45988,	// ս���ȴ����볬ʱ
	ERR_BATTLE_NOT_PERMITED					= -45987,	// û�б�׼�����ս��
	ERR_REPETION_CREATE_FULL				= -45986,	// ��������ʧ��( ��Դ�� )
	ERR_REPETION_CREATE_EXIST				= -45985,	// ��������ʧ��( �Ѿ����� )
	ERR_REPETION_CREATE_NOTFOUND			= -45984,
	ERR_REPETION_WEEK_TIME_FULL				= -45983,	// Parame1 Week Time Max, Parame2 PlayerID
	ERR_REPETION_PLAYER_CAMP_FULL			= -45982,	// ��Ӫ��������
	ERR_REPETION_PLAYERNUMBER_MORE			= -45981,	// ������������ Parame1 Need PlayerNumber Max, Parame2 Now PlayerNumber
	ERR_REPETION_OVERMONEYLMT_SYSMAIL		= -45980,	// ���Ľ�Ǯ�ѳ���Я�����ޣ���������ϵͳ�ѷ����ʼ��������
	ERR_REPETION_LEVEL_MAX					= -45979,	// Parame1 Map Need Level, Parame2 Player Level	

	REPETION_BATTLE_LEAVE_WAITLIST			= -45978,
	
	REPETION_TOWER_FLOOR					= -45977,	// ������ͨ��ȫ����֪ͨ
	ERR_REPETION_PVP_FULL					= -45976,	// ������������
	ERR_REPETION_NO_NECESSITY				= -45975,	// û�н��븱������Ʒ
	ERR_REPETION_SHITU_SHIP					= -45974,	// �����ʦͽ��ϵ
	ERR_REPETION_GLOBALWAR_NOTSAMEREPETION  = -45973,	// ս������ʱ����ͬһ��ս��
	ERR_REPETION_GLOBALWAR_NOTSAMECAMP		= -45972,	// ս������ʱ����ͬһ����Ӫ
	ERR_REPETION_GLOBALWAR_CAMPKICKON		= -45971,	// ����ͶƱ�������������
	ERR_REPETION_KICKCAMPPLAYER_NOTINBATTLE	= -45970,	// ���ڸ����в�������
	ERR_REPETION_KICKCAMPPLAYER_NOTONLINE	= -45969,	// ���ߵ��˲�����
	ERR_REPETION_KICKCAMPPLAYER_VOTED		= -45968,	// �Ѿ�Ͷ��Ʊ
	ERR_REPETION_REPETIONDESTORIED			= -45967,	// ���븱��ʱ�����Ѿ��ر�
};

// mail				( -46999 ~ - 46000  )
enum  EMailCode
{	
	ERR_MAIL_GETACCESSORY_NOPACKAGESPACE = -46999,			// ��ȡ�ʼ�����ʱ�����ռ䲻��
	ERR_MAIL_MONEYOUT					 = -46998,			// ��ȡ��Ǯʱ��Ǯ���
	ERR_MAIL_GETACCESSORY_SUCCESS		 = -46997,			// ��ȡ�����ɹ�
	ERR_MAIL_GETMONEY_SUCESS			 = -46996,			// ��ȡ������Ǯ�ɹ�
	ERR_MAIL_TIMEPROTECTED				 = -46995,			// ��ȫ�������ڵ�������͡���ť���ֶ�ɾ���ʼ�
	ERR_MAIL_PRODUCE_OPENMAILBOX		 = -46994,			// ���������д�����
	ERR_MAIL_ADDACCESSORY_BINDED		 = -46993,			// ��ͼ�Ѱ���Ʒ���븽���б�
	ERR_MAIL_ADDACCESSORY_TASKITEM		 = -46992,			// ��ͼ��������Ʒ���븽���б�
	ERR_MAIL_SENDMAIL_LISTFULL			 = -46991,			// ��Ӹ���ʱ�����б��Ѿ�����
	ERR_MAIL_SENDMAIL_EMPTYNAME			 = -46990,			// �ʼ�����������Ϊ��
	ERR_MAIL_SENDMAIL_EMPTYTITLE		 = -46989,			// �����ʼ�ʱû���ʼ�����
	ERR_MAIL_SENDMAIL_NOTINSELFCONTRY	 = -46988,			// �����ʼ�ʱ�����Լ�����
	ERR_MAIL_SENDMAIL_SELFSEND			 = -46987,			// �����ʼ�ʱ�ʼ����շ�Ϊ�Լ�
	ERR_MAIL_SENDMAIL_MONEYNOTENOUGH	 = -46986,			// �����ʼ�ʱ���ʲ���
	ERR_MAIL_SENDMAIL_CONFIRM			 = -46985,			// ������������ʱ����������͡���ť
	ERR_MAIL_SENDMAIL_DESNOTEXIST		 = -46984,			// �����ʼ�ʱ�ʼ������˲�����
	ERR_MAIL_SENDMAIL_DESMAILFULL		 = -46983,			// �����ʼ�ʱ�Է�������
	ERR_MAIL_SENDMAIL_DESOINOTHERCOUNTRY = -46982,			// �����ʼ�ʱ�ʼ����շ�����������
	ERR_MAIL_SENDMAIL_INBLACKLIST		 = -46981,			// �����ʼ�ʱ�ڶԷ��������б���
	ERR_MAIL_SENDMAIL_SUCESS			 = -46980,			// �����ʼ��ɹ�
	ERR_MAIL_DELMAIL_EMPTYOPTION		 = -46975,			// ɾ���ʼ�ʱû��ѡ����
	ERR_MAIL_LOCKMAIL_MONEYNEEDTOPAY	 = -46997,			// ������δ���ѵĸ����ʼ�������ʧ��	
	ERR_MAIL_LOCKMAIL_SUCCESS			 = -46973,			// �����ʼ��ɹ�
	ERR_MAIL_UNLOCKMAIL_SUCCESS			 = -46972,			// �����ʼ��ɹ�
	ERR_MAIL_LOCKMAIL_FULL				 = -46971,			// �����ʼ�ʱ�Ѿ���������
	ERR_MAIL_DELMAIL_LOCKED				 = -46970,			// �������ʼ����ܱ�ɾ��
	ERR_MAIL_DELMAIL_NEEDTOPAY			 = -46969,			// ����ɾ����û�и��ѵ��ʼ�
	ERR_MAIL_DELMAIL_HASACCESSORY		 = -46968,			// ���и������ʼ����ܱ�ɾ��
	ERR_MAIL_DELMAIL_NEWTEXT			 = -46967,			// �ֶ�ɾ���µĴ��ı��ʼ�
	ERR_MAIL_DELALLMAIL_HASNOTEXT		 = -46966,			// ɾ��ȫ���ʼ�ʱû�д��ı��ʼ�
	ERR_MAIL_DELALLMAIL_NEWTEXT			 = -46965,			// ɾ��ȫ���ʼ�ʱ����û��ɾ���Ĵ��ı��ʼ�	
	ERR_MAIL_DELALLMAIL_CONFIRM			 = -46964,			// ɾ��ȫ���ʼ�ʱ����ʾ
	ERR_MAIL_DELMAIL_SUCESS				 = -46963,			// ɾ���ʼ��ɹ�
	ERR_MAIL_MAILBOX_FULL				 = -46962,			// �����Ѿ����˵���ʾ��Ϣ
	ERR_MAIL_GEATACEESSORY_NOOPTION		 = -46961,			// ��ȡ����ʱû��			
	ERR_MAIL_BACKMAIL_SUCESS			 = -46960,			// �ʼ����ųɹ�
	ERR_MAIL_BACKMAIL_BACKED			 = -46959,			// �����˻ر��˻ص��ʼ�	
	ERR_MAIL_BACKMAIL_TEXT				 = -46958,			// ���ı��ʼ����ܱ��˻�
	ERR_MAIL_MONEYNEEDMAIL_HASNOITEM	 = -46957,			// �����ʼ�û�з�����Ʒ
	ERR_MAIL_MONEYNEEDMAIL_MONEYNOTSET	 = -46956,			// �����ʼ�û����Ҫ�Է�֧���Ľ�Ǯ
	ERR_MAIL_MONEYNEEDMAIL_SHOWMONEY	 = -46955,			// �����ʼ���ʾҪ��֧���Ľ�Ǯ
	ERR_MAIL_MONEYNEEDMAIL_MONEYNOTENOUGH= -46954,			// ��ȡ�����ʼ�����ʱ��Ǯ����	
	ERR_MAIL_SENDMAIL_SENDNOTALLOWED	 = -46952,			// ���������ʼ�
	
	ERR_MAIL_PAYMAIMONEY_NONEED			 = -46951,			// ��ͨ�ʼ�����Ҫ����
	ERR_MAIL_PAYMAIMONEY_MONEYNOTENOUGH	 = -46950,			// ��Ǯ����
	ERR_MAIL_GETACCESSORY_MONEYNOTPAY	 = -46949,			// ��ȡ����ʱ�����ʼ���û��֧����Ǯ
	ERR_MAIL_PAYMONEYFORMAIL_INVALIDE	 = -46948,			// Ϊ�����ʼ�����ʱ,�ʼ��Ѿ�ʧЧ
	ERR_MAIL_BACKMONEY_OVER				 = -46947,			// ���Ϸ��ص�Ǯ���������Я������
	ERR_MAIL_GETACCESSORY_EXPIRED		 = -46946,			// ���Ϸ��ص�Ǯ���������Я������
};

// judge ( -47499 ~ -47000 )
enum EJudge
{
	ERR_JUDGE_PLAYERNOTEXIST			= -47499,			// ��Ҳ�����
	ERR_JUDGE_DESOFFLINE				= -47498,			// �Է�������
	ERR_JUDGE_NEEDSCORE					= -47497,			// �������ʱ����ֵ����Ϊ��
	ERR_JUDGE_FAILED					= -47496,			// ����ʧ��
	ERR_JUDGE_SCORENOTENOUGH			= -47495,			// ��֧���������
	ERR_JUDGE_NUMFULL					= -47494,			// ���۴����ﵽ����
	ERR_JUDGE_COOLTIME					= -47493,			// ������ȴ��
	ERR_JUDGE_LEVELLOWER				= -47492,			// ��Ҽ��𲻹�
	ERR_JUDGE_DESLEVELLOWER				= -47491,			// �Է���Ҽ��𲻹�
	ERR_JUDGE_MODIFYNONE				= -47490,			// û�п����޸ĵ����

	ERR_ACHIEVE_MAX						= -47489,			// �Ѿ��쵽���
	ERR_ACHIEVE_NO						= -47488,			// ��������
	ERR_ACHIEVE_FULL					= -47487,			// ��������
};

// activity ( -47999 ~ -47500 )
enum EActitity
{
	ERR_ACTIVITY_INANSWERSTATUS			= -47999,			// �Ѿ����ڴ���״̬�������ظ�����
	ERR_ACTIVITY_HASANSWERED			= -47998,			// �Ѿ���ȡ��ÿ�ո����Ĵ���
	ERR_ACTIVITY_LEVELLOW				= -47997,			// ��ȡ�����ĵȼ�����	
	ERR_ACTIVITY_NOSPACE				= -47996,			// �ռ䲻���޷���ȡnpc����
	ERR_HYDRANGEA_GRABED				= -47995,			// �Ѿ���������
	ERR_HYDRANGEA_GRABERFULL			= -47994,			// ���������Ա����	
	ERR_HYDRANGEA_ACTIVITYEND			= -47993,			// ������ʱ��Ѿ�����	
	ERR_THROWHYDRANGEA_ACTIVITYEND		= -47992,			// ������ʱ��Ѿ�����
	ERR_THROWHYDRANGEA_NOTALLOWED		= -47991,			// ��ǰ״̬������������
	ERR_THROWHYDRANGEA_NOTHOLDER		= -47990,			// ������ʱ�������������
	ERR_THROWHYDRANGEA_FAILED			= -47989,			// ������ʱʧ�ܼ�����������
	ERR_THROWHYDRANGEA_FARDISTANCE		= -47988,			// ������Χ����������
	ERR_MONEYOVER_SYSMAIL				= -47987,			// ÿ�ո�������Ǯ������ǮЯ�����ޣ��ѷ�ϵͳ�ʼ��������
	ERR_NINETAILFOX_DEATH				= -47986,			// ��β�ߺ���ʱ�Ĵ�����
	ERR_PRESTIGEMARSHAL_DEATH			= -47985,			// ����Ԫ˧��ʱ�Ĵ�����
	ERR_GRASSJELLYEND					= -47984,			// �ɲݻ���������Ĵ�����
};

// redstone ( -48999 ~ -48000 )
enum ERedstone
{
	ERR_REDSTONE_PROTECTED				= -48999,			// �ڵ����ڱ���״̬
	ERR_REDSTONE_MAGIC					= -48988,			// �Ѿ���������״̬	
	ERR_REDSTONE_NOTINTEAM				= -48987,			// ����ڵ�ʱ���û�ж���
	ERR_REDSTONE_PROCESSTIMER			= -48986,			// �ڵ����ڱ����˿���
	ERR_REDSTONE_SUCESS					= -48985,			// �ڵ����ɹ�����
	ERR_REDSTONE_STARTED				= -48984,			// �ڵ��Ѿ�������	
	ERR_REDSTONE_REDSTONEEFFECT			= -48983,			// ÿ������ֻ�ܿ���һ���ڵ�
};

// password( -49999 ~ - 49000 )
enum EPassword
{
   ERR_PASSWORD_WRONGPASSWORD			= -49999,			// ���������
   ERR_PASSWORD_PASSWORDSETED			= -49998,			// ��������ʱ�����Ѿ�����
   ERR_PASSWORD_SETPASSWORDWRONG		= -49997,			// �����������
   ERR_PASSWORD_SETPASSWORDINPROTECTIME	= -49996,			// ��ȫʱ���ڲ������޸Ļ�����������
   ERR_PASSWORD_WRONGPROTECTTIME		= -49995,			// �Ƿ��İ�ȫ����ʱ��
   ERR_PASSWORD_INPROTECTTIME			= -49994,			// �Ʋ����������ڼ䲻����ò���
   ERR_PASSWORD_ACTIONNOTALLOWED		= -49993,			// ���뱣���ڼ䲻����ò���	   
   ERR_PASSWORD_NOTFREE					= -49992,			// ��ȫ���뱣��û�д��ڽ���״̬��������������
   ERR_PASSWORD_DESINPROTECTSTATUS		= -49991,			// ����ʱ�Է��������뱣��״̬
}; 

// storage( -50999 ~ -50000 ) 
enum EStorage
{
	ERR_STORAGE_STORMONEYFULL			 = -50999,			// �洢��Ǯʱ��Ǯ����	
	ERR_STORAGE_HASNOSOMUCHMONEY		 = -50998,			// ȡ��Ǯʱ�ֿ�û����ô���Ǯ 
	ERR_STORAGE_BAGMONEYFUULL			 = -50997,			// �Ӳֿ�ȡǮʱ������Ǯ��
	ERR_KITBAG_CANNOTSWAP				 = -50996,			// �����ñ����滻��ǰ�ֿⱳ��
	ERR_KITBAG_CANNOTADD				 = -50995,			// �������ܱ����õ��ֿⱳ����
	ERR_KITBAG_TAKEKITBAG_NOTEMPTY		 = -50994,			// ȡ�±���ʱ������Ϊ��
	ERR_KITBAG_ADDKITBAG_NOTEMPTY		 = -50993,			// ���ñ���ʱĿ����λ��Ϊ��
	ERR_KITBAGNEEDLE_NOTNEEDLEITEM		 = -50992,			// ���õ���Ʒ�����廨��	
	ERR_KITBAGNEEDLE_NOTKITBAG			 = -50991,			// ������Ĳ��Ǳ���		
	ERR_KITBAGNEEDLE_NOTSUITABLENEEDLE   = -50990,			// �廨��������ı���������С�ڵ�ǰҪ����ı���
	ERR_KITBAGNEEDLE_KITBAGNOTEXPIRED	 = -50989,			// ������δ���ڣ��������� 
	ERR_STORAGE_MONEY_UPLMT				 = -50988,			// �ֿ��Ǯ�ﵽ���� ���ܽ��иò���
	ERR_BAG_MONEY_UPLMT					 = -50987,			// ������Ǯ�ﵽ���� ���ܽ��иò���
	ERR_STORAGE_BIND_MONEY_UPLMT		 = -50986,			// �ֿ�󶨽�Ǯ�ﵽ���� ���ܽ��иò���
	ERR_BAG_BIND_MONEY_UPLMT			 = -50985,			// �����󶨽�Ǯ�ﵽ���� ���ܽ��иò���
	ERR_FASHIONNEEDLE_WRONGCOLOR		 = -50984,			// ʱװ�廨�벻�ܶ�������ɫ��ʱװʹ��
	ERR_FASHIONNEEDLE_NOTFASHION		 = -50983,			// ʱװ�廨�벻�ܶԷ�ʱװʹ��
	ERR_FASHIONNEEDLE_FASHIONNOTEXPIRED  = -50982,			// ʱװû�й��ڣ�����ʹ���廨���޸�
};

//	family( -51999 ~ -51000 )
enum EFamily
{
	ERROR_FAMILY_CREATFAMILY_HASFAMILY 							=	-51999	,				// ��������ʱ�Ѿ��м���
	ERROR_FAMILY_CREATFAMILY_LEVELLOW  							=	-51998	,				// û��30��ʱ����������
	ERROR_FAMILY_CREATFAMILY_HASDIRTYWORD 							=	-51997	,			// ��������ʱ�������ƺ������
	ERROR_FAMILY_CREATFAMILY_NAMEEXIST							=	-51996	,				// ��������ʱ���������Ѿ�����
	ERROR_FAMILY_CREATFAMILY_MONEYNOTENONGH							=	-51995	,			// ��������ʱ��Ǯ����
	ERROR_FAMILY_INVITE_INDIFFNATION   							=	-51994	,				// ����������ʱ�ͶԷ�������ͬ 
	ERROR_FAMILY_INVITE_INFAMILY	   						=	-51993	,					// �Է��Ѿ������˼��壬����ʧ��
	ERROR_FAMILY_INVITE_DESLOWLEVEL	   						=	-51992	,					// �Է��ȼ�δ��30��������ʧ��
	ERROR_FAMILY_INVITE_HASNORIGHT	   						=	-51991	,					// ����������ʱû��Ȩ��	::TODO
	ERROR_FAMILY_INVITE_FAMILYFULL	   						=	-51990	,					// ����������Ϣʱ�����Ա���� ::TODO
	ERROR_FAMILY_REPLYINVITE_FAMILYFULL							=	-51989	,				// ͬ��������ʱ�Է������Ա�Ѿ�����  ::TODO
	ERROR_FAMILY_APPLYLIST_FAMILYFULL  							=	-51988	,				// ���������б�ʱ�����Ա���� 	::TODO	
	ERROR_FAMILY_REPLYAPPLY_INFAMILY							=	-51987	,				// ͬ����Ҽ������ʱ�Ѿ��ڼ�����
	ERROR_FAMILY_REPLYAPPLY_INOHERFAMILY							=	-51986	,			// ͬ����Ҽ������ʱ�Է��Ѿ�������������
	ERROR_FAMILY_REPLYAPPLY_FAMILYFULL							=	-51985	,				// ͬ��������ʱ������������
	ERROR_FAMILY_REPLYINVITE_INFAMILY							=	-51984	,				// ͬ��������ʱ�Ѿ��м���
	ERROR_FAMILY_APPLY_INFAMILY		   					=	-51983	,						// �м���ʱ����������	
	ERROR_FAMILY_APPLY_FAMILYNOTEXIST  							=	-51982	,				// ����ļ�����������
	ERROR_FAMILY_APPLY_SUCESS          							=	-51981	,				// ����ļ���������  ����ɹ�����ȴ��������Ա���
	ERROR_FAMILY_CHANGNOTICE_DIRTYWORD 							=	-51980	,				// �ı���幫��ʱ����Ϣ�������
	ERROR_FAMILY_LEAVEFAMILY_ISHEADER  							=	-51979	,				// �峤�����뿪����		
	ERROR_FAMILY_HASNORIGHT							=	-51978	,							// û��Ȩ��
	ERROR_FAMILY_CHANGEROOTER_NOTINFAMILY							=	-51977	,			// ת������ְλʱ�Է����ڱ������� 
	ERROR_FAMILY_KICKPLAYER_KICKSELF							=	-51976	,				// �峤�����߳��Լ�
	ERROR_FAMILY_POSTAPPOINT_POSTSELF							=	-51975	,				// ���ܸ��Լ���ְ��
	ERROR_FAMILY_REPLYINVITE_FAMILYNOTEXIST							=	-51974	,			// �������ʱ�����岻����	 	
	ERROR_FAMILY_APPLY_LEVELLOW			 				=	-51973	,						// û��30��ʱ������������ 
	ERROR_FAMILY_INVITE_OFFLINE			 				=	-51972	,						// ����������ʱ�Է�������	 
	ERROR_FAMILY_INVITE_INVITELISTFULL	 						=	-51971	,				// ���������������б���
	ERROR_FAMILY_APPLY_APPLYLISTFULL							=	-51970	,				// �ﵽ30��û����壬����ļ��������ڣ�������������
	ERROR_FAMILY_APPLY_INAPPLYTIMELIMIT							=	-51969	,				// �ﵽ30��û����壬����ļ��������ڣ���24Сʱ����
	ERROR_FAMILY_APPLY_INFAMILYLIMIT							=	-51968	,				// �뿪����24Сʱ���ܼ������
	ERROR_FAMILY_APPOINT_APPOINTSELF							=	-51967	,				// ת��ְλʱĿ��Ϊ�峤����
	ERROR_FAMILY_APPLY_NOTINSAMECOUNTRY							=	-51966	,				// �ﵽ30��û����壬����ļ�����Ϊ��������
	ERROR_FAMILY_LEAVE_INCORPS							=	-51965	,						// �ھ����еļ��岻�ܽ�ɢ
	ERROR_FAMILY_KICK_NOTINFAMILY							=	-51964	,					// ����ʱ��Ҳ��ڼ�����
	ERROR_FAMILY_CHANGHEADER_CORPSHEADER							=	-51963	,			// �������첻��ת���峤ְλ
	ERROR_FAMILY_DISBAND_DISBANDSTATUS							=	-51962	,				//  ��ɢ����ʱ�Ѿ����ڽ�ɢ״̬
	ERROR_FAMILY_DISBAND_HASNOFAMILY							=	-51961	,				// ��ɢ����ʱû�м���
	ERROR_FAMILY_CANCELDISBAND_NOTNEED							=	-51960	,				// ȡ�������ɢʱ���岻���ڽ�ɢ״̬
	ERROR_FAMILY_REPLYINVITE_INDISBANDCOOLTIME							=	-51959	,		// ������ʱ���Է��뿪�������ȴʱ��δ��
	ERROR_FAMILY_STRINGTOOLONG							=	-51958	,						// �ַ�������	
	ERROR_FAMILY_INVITE_INVITED							=	-51957	,						// �Ѿ����͹�������Ϣ  42
	ERROR_FAMILY_APPLY_APPLIED							=	-51956	,						// �Ѿ�������������
	ERROR_FAMILY_INVITE_SELFINVITE							=	-51955	,					// ���������Լ�
	ERROR_FAMILY_REPLYAPPLY_TIMEOUT							=	-51954	,					// ������ʱ�����Ѿ�ʧЧ
	ERROR_FAMILY_CREATFAMILY_INDISBANDCOOLTIME							=	-51953	,		// ��ɢ���������Ա24Сʱ֮�ڲ��ܴ�������
	ERROR_FAMILY_REPLYAPPLY_ROLENOTEXIST							=	-51952	,			// ���������ʱ��Ϊ��ɾ����������ԭ���ɫ������
	ERROR_FAMILY_APPOINTHEADER_MEMBEROFFLINE							=	-51951	,		// �������Աת��ְλʱ��Ա������
	ERROR_FAMILY_APPOINTHEADER_MEMBERLEVELLOW							=	-51950	,		// �������Աת��ְλʱ��Ա�ȼ�����
	ERROR_FAMILY_LEVELUP_LEVELIMIT							=	-51949	,					// ��������ʱ�Ѿ�����ȼ�����
	ERROR_FAMILY_LEVELUP_GLORYNOTENOUGH							=	-51948	,				// ��������ʱ������ҫֵ����	
	ERROR_FAMILY_CONSUMEMONEY_MONEYNOTENOUGH							=	-51947	,		// ��������ʱ������ҫֵ����	
	ERROR_FAMILY_SETPOST_POSTFULL							=	-51946	,					// ����ְλʱְλ�Ѿ�����	
	ERROR_FAMILY_BIDNPC_NOTHEADER							=	-51945	,					// ��������ʱ�������峤
	ERROR_FAMILY_BIDNPC_BIDFAIL							=	-51944	,						// ��������ʱ������ʧ��
	ERROR_FAMILY_BIDNPC_HASOWN							=	-51943	,						// ��������ʱ���Ѿ�ռ���
	ERROR_FAMILY_BIDNPC_SAME							=	-51942	,						// ��������ʱ���ظ�����
	ERROR_FAMILY_BIDNPC_NOTHIGHEST							=	-51941	,					// ��������ʱ�����۵�
	ERROR_FAMILY_BIDNPC_BELOWOLD							=	-51940	,					// ��������ʱ�����۵��ھɵ�
	ERROR_FAMILY_ABORTNPC_NOTHEADER							=	-51939	,					// ����NPCʱ�������峤
	ERROR_FAMILY_ABORTNPC_NOTOWN							=	-51938	,					// ����NPCʱ��û��ӵ��
	ERROR_FAMILY_BIDNPC_WRONGTIME							=	-51937	,					// ��������ʱ��ʱ�䲻��ȷ
	ERROR_FAMILY_SUBMIT_WRONGTIME							=	-51936	,					// ������Աʱ��ʱ�䲻��ȷ
	ERROR_FAMILY_CONTRIBUTEMONEY_NOTENOUGH							=	-51935	,			// ���׼����Ǯʱ��Ǯ����		
	ERROR_FAMILY_MAKEROOM_EXIST							=	-51934	,						// ��������ʱ,�Ѿ�����
	ERROR_FAMILY_CHAROOM_NOTEXIST							=	-51933	,					// ��ս����ʱ,������
	ERROR_FAMILY_CHAROOM_NOTHEADER							=	-51932	,					// ��ս����ʱ,�����峤
	ERROR_FAMILY_AGREE_NOTHEADER							=	-51931	,					// ͬ����սʱ,�����峤
	ERROR_FAMILY_AGREE_UNKNOWN							=	-51930	,						// ͬ����սʱ,δ֪����
	ERROR_FAMILY_QUERY_NOTHEADER							=	-51929	,					// ��ѯʱ,�����峤
	ERROR_FAMILY_QUERY_NOTEXIST							=	-51928	,						// ��ѯʱ,�����ڷ���
	ERROR_FAMILY_ABORT_NOTEXIST							=	-51927	,						// ȡ��ʱ,�����ڷ���
	ERROR_FAMILY_ABORT_NOTHEADER							=	-51926	,					// ȡ��ʱ,�����峤
	ERROR_FAMILY_BIDNPC_NOMONEY							=	-51925	,						// ��������ʱ��Ǯ����
	ERROR_FAMILY_CHAROOM_SAME							=	-51924	,						// ��ս����ʱ,������ͬ
	ERROR_FAMILY_CHAROOM_EXIST							=	-51923	,						// ��ս����ʱ,�Ѿ���ս��
	ERROR_FAMILY_ABORTROOM_BATTLE							=	-51922	,					// ��������ʱ����ս����
	ERROR_FAMILY_CHAROOM_BATTLE							=	-51921	,						// ��ս����ʱ,��ս����
	ERROR_FAMILY_BIDNPC_DISBAND							=	-51920	,						// ��ɢ״̬���ܱ�������
	ERROR_FAMILY_MAKEROOM_DISBAND							=	-51919	,					// ��ɢ״̬���ܴ�������
	ERROR_FAMILY_CHAROOM_DISBAND							=	-51918	,					// ��ɢ״̬������ս����
	ERROR_FAMILY_MAKEROOM_NOTHEADER							=	-51917	,					// ��������ʱ,�����峤
	ERROR_FAMILY_AGREE_DISBAND							=	-51916	,						// ͬ����սʱ,һ�����ڽ�ɢ״̬	
	ERROR_FAMILY_NOTALLOWDONNPCFIGHT							=	-51915	,				//	����npc����״̬���ܽ�ɢ����
	ERROR_FAMILY_LEAVEFAMILY_ONNPCFIGHT							=	-51914	,				//	����npc����״̬�����뿪����
	ERROR_FAMILY_KICKPLAYER_ONNPCFIGHT							=	-51913	,				//	����npc����״̬��������	
	ERROR_FAMILY_GETNPCWELFARE_HASGETED							=	-51912	,				//  �Ѿ���ȡ������npc����
	ERROR_FAMILY_USEEXPCARD_HASNOITEM							=	-51911	,				// ʹ�þ�������ʱû�иõ���
	ERROR_FAMILY_GETEXPCARD_HASITEM							=	-51910	,					// ��ȡ��������ʱ�õ����Ѿ�����
	ERROR_FAMILY_GETEXPCARD_GETED							=	-51909	,					// һ��֮�ڵڶ�����ȡ��������
	ERROR_FAMILY_GETEXPCARD_NOTHEADER							=	-51908	,				// �����峤������ȡ��������
	ERROR_FAMILY_LEVELUP_MONEYNOENOUGH							=	-51907	,				// ��������ʱ��Ǯ����	   
	ERROR_FAMILY_CONTRIBUTE_MONEYLIMIT							=	-51906	,				// ��Ǯʱ�����Ǯ�Ѵ�����
	ERROR_FAMILY_CONTRIBUTE_MONEYINVAL							=	-51905	,				// ��Ǯʱ������Ŀ��Ч
	ERROR_FAMILY_GETMONEY_MONEYINVALIDE							=	-51904	,				// ��ȡ�����Ǯʱ��Ǯ��Ŀ��Ч
	ERROR_FAMILY_MONEYINVALIDE							=	-51903	,						// ��Ǯ��Ŀ��Ч	
	ERROR_FAMILY_REDPAPER_CONTRIBUTENOTENOUGH							=	-51902	,		// ����һ�ʱ���˹��׶Ȳ���	
	ERROR_FAMILY_REDPAPER_SPACENOTENOUGH							=	-51901	,			// ������ʱ�����ռ䲻��
	ERROR_FAMILY_REDPAPER_MONEYNOTENOUGH							=	-51900	,			// ������ʱ�����Ǯ����  -51900
	ERROR_FAMILY_EXCHANGE_HASONFAMILY							=	-51899	,				// ����һ�ʱû�м���
	ERROR_FAMILY_BUYFAMILYITE_HASONFAMILY							=	-51898	,			// ������ʱû�м���
	ERROR_FAMILY_FAMILYBOSS_REPETIONNOTEXIST							=	-51897	,		// �޷�������帱���������Ѿ��ر�
	ERROR_FAMILY_FAMILYBOSS_HASNOFAMILY							=	-51896	,				// û�м��岻�ܽ�����帱��
	ERROR_FAMILY_FAMILYBOSS_NOTINOPENTIME							=	-51895	,			// ������帱��ʱʱ�䲻��	
	ERROR_GROUPNAME_SERVICE_NOTOPEN							=	-51894	,					// �������Ʒ��񲻿���, ���Ժ�����
	ERROR_FAMILY_FAMILYBOSS_REPETIONHASOPENED							=	-51893	,		// �����Ѿ����������帱��
	ERROR_FAMILY_FAMILYBOSS_MONEYNOTENOUGH							=	-51892	,			// �������帱��ʱ��Ǯ����
	ERROR_FAMILY_FAMILYBOSS_GLORYNOTENOUGH							=	-51891	,			// �������帱��ʱ��ҫ����	
	ERROR_FAMILY_FAMILYGOODS_HASNOWARNPC							=	-51890	,			// û��ռ��npc�������ز��̵�����Ʒ
	ERROR_FAMILY_USELEAGUEBAG_HASNOFAMILY							=	-51889	,			// û�м��岻��ʹ�ü����ع���Ʒ	
	ERROR_FAMILY_FAMILYGOODS_ITEMNOTENGOUGH							=	-51888	,			// ������Ʒ��������
	ERROR_FAMILY_FAMILYGOODS_CANOTBUY							=	-51887	,				// ���ܹ���ü�����Ʒ
	ERROR_FAMILY_EXCHANGE_NOTALLOWED							=	-51886	,				// ���ܽ��м���һ�
	ERROR_FAMILY_EXCHANGE_ITEMNOTENOUGH 							=	-51885	,			//  ����һ���Ʒ����
	ERROR_FAMILY_FAMILYGOODS_HASNORIGHT							=	-51884	,				//  ��������̵���ƷʱȨ�޲���	

};	

//	corps( -52999 ~ -52000 )
enum ECorps
{
	ERROR_CORPS_CREAT_HASDIRTYWORD							=	-52999	,				// ��������ʱ�������
	ERROR_CORPS_CREAT_ISNOTFAMILYHEADER							=	-52998	,			// ��������ʱ���Ǽ����峤
	ERROR_CORPS_CREAT_LEVELNOTENOUGH							=	-52997	,			// ��������ʱ�����ȼ�����
	ERROR_CORPS_CREAT_HASNOFAMILY							=	-52996	,				// ��������ʱû�м���
	ERROR_CORPS_CREAT_INCORPS							=	-52995	,					// ��������ʱ�Ѿ��ھ�����
	ERROR_CORPS_CREAT_MONEYNOTENOUGH							=	-52994	,			// ��������ʱ��Ǯ����
	ERROR_CORPS_CREAT_NAMEEXIST							=	-52993	,					// ��������ʱ�����Ѿ�����
	ERROR_CORPS_APPLY_HASNOFAMILY							=	-52992	,				// ����������ʱ����Ҳ��ڼ�����
	ERROR_CORPS_APPLY_HASNORIGHT							=	-52991	,				// ����������ʱ����Ҳ����峤��û��Ȩ��
	ERROR_CORPS_APPLY_NOTINSAMECOUNTRY							=	-52990	,			// ����������ʱ������;��Ų���ͬһ������0
	ERROR_CORPS_APPLY_CORPSMEMBERFULL							=	-52989	,			// ����������ʱ�����ų�Ա��
	ERROR_CORPS_APPLY_APPLYLISTFULL							=	-52988	,				// ����������ʱ�������б���
	ERROR_CORPS_APPLY_HASINCORPS							=	-52987	,				// �����Ѿ��ھ����У������ټ������
	ERROR_CORPS_APPLY_NOTEXIST							=	-52986	,					// ����������ʱ�����Ų�����
	ERROR_CORPS_APPLY_INCORPS							=	-52985	,					// ����������ʱ�Ѿ��ھ�����
	ERROR_CORPS_APPOINT_NOTINCORPS							=	-52984	,				// ת��ְλʱ��Ҳ��ٱ�������
	ERROR_CORPS_HASNORIGHT							=	-52983	,						// Ȩ�޲���
	ERROR_CORPS_APPOINT_NOTFAMILYHEADER							=	-52982	,			// ��ְʱ�Է����Ǽ����峤
	ERROR_CORPS_DISBAND_NOTHEADER							=	-52981	,				// ��ɢ����ʱ���Ǿ�������
	ERROR_CORPS_DISBAND_NUMLIMIT							=	-52980	,				// ����500�˵ľ��Ų��ܽ�ɢ0
	ERROR_CORPS_INVITE_FAMILYNOTEXIST							=	-52979	,			// �������������ʱ���岻����		20
	ERROR_CORPS_INVITE_NOTINCORPS							=	-52978	,				// �������������ʱ���Ų�����
	ERROR_CORPS_INVITE_INVITELISTFULL							=	-52977	,			// �������������ʱ���������б���
	ERROR_CORPS_LEAVE_ISCORPSHEADER							=	-52976	,				// �󽫾������뿪����	
	ERROR_CORPS_REPLYAPPLY_INCORPS							=	-52975	,				// �󽫾��𸴼�������ʱ�����Ѿ��������
	ERROR_CORPS_REPLYAPPLY_MEMBERFULL							=	-52974	,			// �𸴼�������ʱ���ų�Ա����
	ERROR_CORPS_REPLYAPPLY_FAMILYEXIST							=	-52973	,			// �𸴼�������ʱ���岻����
	ERROR_CORPS_REPLYAPPLY_NOTINCORPS							=	-52972	,			// �𸴼�������ʱ�����Ѿ�������
	ERROR_CORPS_REPLYINVITE_INCORPS							=	-52971	,				// �𸴾�������ʱ�����Ѿ��ھ�����
	ERROR_CORPS_REPLYINVITE_CORPSMEBERFULL							=	-52970	,		// �𸴾�������ʱ���ų�Ա����0
	ERROR_CORPS_REPLYINVITE_NOTEXIST							=	-52969	,			// �𸴾�������ʱ���Ų�����
	ERROR_CORPS_APPOINTHEADER_SELFAPPOINT							=	-52968	,		// ���ܸ��Լ�ת��ְλ
	ERROR_CORPS_KICKFAMILY_SELFFAMILY							=	-52967	,			// �����߳��Լ��ļ���
	ERROR_CORPS_APPLY_ONDISBANDSTATUS							=	-52966	,			// �����ɢ�ڼ䲻�ܼ������
	ERROR_CORPS_INVITE_ONDISBANDSTATUS							=	-52965	,			// �������봦�ڽ�ɢ״̬�ļ���������
	ERROR_CORPS_INVITE_INCORPS							=	-52964	,					// ����������ʱ�����Ѿ��ھ�����
	ERROR_CORPS_DISBAND_DISBANDSTATUS							=	-52963	,			// ��ɢ����ʱ�Ѿ����ڽ�ɢ״̬
	ERROR_CORPS_CANCLEDISBAND_NOTNEED							=	-52962	,			// ȡ����ɢ����ʱ����û�д��ڽ�ɢ״̬
	ERROR_CORPS_APPLY_INCOOLTIME							=	-52961	,				// ����������ʱ������ȴʱ��
	ERROR_CORPS_JOINCORPS_INLEAVECOOLTIME							=	-52960	,		// �������ʱ������ȴʱ�� 0
	ERROR_CORPS_STRINGTOOLONG							=	-52959	,					// �ַ�������	  40
	ERROR_CORPS_APPLY_INAPPLYLIST							=	-52958	,				// ����������ʱ������������Ѿ��������б�����
	ERROR_CORPS_MEMBERFULL							=	-52957	,						// �����Ա��
	ERROR_CORPS_INVITE_NOTINOTHERCOUNTRY							=	-52956	,		// ����ʱ�ͶԷ����岻��ͬһ������
	ERROR_CORPS_REPLYINVITE_ONDISBANDSTATUS							=	-52955	,		// ���ڽ�ɢ״̬�ļ��岻�ܼ������
	ERROR_CORPS_CREATCORPS_INDISBANDCOOLTIME							=	-52954	,	// ��ɢ����24Сʱ��ͬһ�����岻���ٴ�������
	ERROR_CORPS_CREAT_ONDISBANDSTATUS							=	-52953	,			// ���崦�ڽ�ɢ״̬ʱ���ܴ�������
	ERROR_CORPS_LEVELUP_LEVELIMIT							=	-52952	,				// �����Ѿ������ٽ�������
	ERROR_CORPS_LEVELUP_GLORYNOTENOUGH							=	-52951	,			// ��������ʱ��ҫֵ����
	ERROR_CORPS_SETPOST_POSTFULL							=	-52950	,				// ���þ���ְλʱ��ְλ�Ѿ�����
	ERROR_CORPS_CONSUMEMONEY_MONEYNOTENGOUGH							=	-52949	,	// ���ľ��Ž�Ǯʱ��Ǯ����
	ERROR_CORPS_HASBID							=	-52948	,							// �Ѿ����������
	ERROR_CORPS_BIDTIMENOTOPEN							=	-52947	,					// ���Ǿ��ۿ���ʱ��
	ERROR_CORPS_MONEYNOTENOUGH							=	-52946	,					// ���Ž�Ǯ����
	ERROR_CORPS_BIDMONEYLOWER							=	-52945	,					// ���۽�Ǯ̫��
	ERROR_CORPS_BIDSUCCESS							=	-52944	,						// ���۱����ɹ�
	ERROR_CORPS_NOTROOTER							=	-52943	,						// ���Ǿ��ų�
	ERROR_CORPS_NOTEXIST							=	-52942	,						// ���Ų�����
	ERROR_CORPS_CANTBATTLE							=	-52941	,						// û�в�ս�ʸ�
	ERROR_CORPS_SELECTBATTLE_SUCCESS							=	-52940	,			// ������ս�ɹ�
	ERROR_CORPS_FAMILYNOTIN							=	-52939	,						// �м��岻���ھ���
	ERROR_CORPS_NOTINFAMILY							=	-52938	,						// �г�Ա�����ڼ���		
	ERROR_CORPS_FAMILYMONEYNOTENOUGH							=	-52937	,			// ��������Ź��׽�Ǯʱ���Ž�Ǯ����	
	ERROR_CORPS_HASHOLDCITY							=	-52936	,						// �Ѿ�ռ���гǳ�
	ERROR_CORPS_MEMBEROVERFLOW							=	-52935	,					// ��ս�������� -52935
	ERROR_CORPS_INBATTLE							=	-52934	,						// ս����
	ERROR_CORPS_ROOMEXIST							=	-52933	,						// �ѱ���
	ERROR_CORPS_ROOMNOTFOUND							=	-52932	,					// û�б���
	ERROR_CORPS_YOURSELF							=	-52931	,						// ������ս�Լ�
	ERROR_CORPS_BIDINUNION							=	-52930	,						// ���ܶ�ͬ�˾��ž���
	ERROR_CORPS_NPCWELFAREOBTAINED							=	-52929	,				// �����Ѿ���ȡ��	
	ERROR_CORPS_HASNOCORPSTOKEN							=	-52928	,					// ��������ʱû��������
	ERROR_CORPS_LEVELUP_MONEYNOTENOUGH							=	-52927	,			// ��������ʱ��Ǯ����
	ERROR_CORPS_MONEYLIMIT							=	-52926	,						// ��Ǯ�Ѿ��ﵽ����
	ERROR_CORPS_MONEYINVALIDE							=	-52925	,					// ��Ǯ��Ŀ��Ч	
	ERROR_CORPS_INSUBMITTING							=	-52924	,					// �����У��޷�����
	ERROR_CORPS_CORPSCANNOTBEDISBANDED							=	-52923	,			// ���ھ���,ս����ս��״̬�ľ��Ų��ܱ���ɢ
	ERROR_CORPS_CANOTLEAVECORPS							=	-52922	,					// ���ھ���,ս����ս��״̬ʱ���岻���뿪����
	ERROR_CORPS_CANOTKICKFAMILY							=	-52921	,					// ���ھ���,ս����ս��״̬ʱ���岻���߳�����	
	ERROR_CORPS_BUYREDPAPER_CONTRIBUTENOTENOUGH							=	-52920	,	// ���Ŷһ�ʱ���˹��׶Ȳ���		
	ERROR_CORPS_BUYREDPAPER_MONEYNOTENOUGH							=	-52919	,		// ������ʱ�����Ǯ����
	ERROR_CORPS_BUYREDPAPER_HASNOSPACE							=	-52918	,			// ������ʱ�����ռ䲻��
	ERROR_CORPS_EXCHANGE_HASNOCORPS							=	-52917	,				// ���Ŷһ�ʱû�о���	-52919	
	ERROR_CORPS_BUYFAMILYITE_HASONCORPS							=	-52916	,			// ������ʱû�о���
	ERROR_UNION_REACHLIMIT							=	-52915	,						// �Ѵ�����������
	ERROR_UNION_NOHEADER							=	-52914	,						// ����ʱû������
	ERROR_UNION_APPLY_NOCORPS							=	-52913	,					// ��������ʱû�о���
	ERROR_UNION_REPLYAPPLY_NOTINCORPS							=	-52912	,			// ��Ӧ����ʱû�о���
	ERROR_UNION_INVITE_NOTINCORPS							=	-52911	,				// ��������ʱû�о��� 
	ERROR_UNION_APPLY_NOTEXIST							=	-52910	,					// ����ʱ����������
	ERROR_UNION_APPLY_HASNOCORPS							=	-52909	,				// ����ʱû�о���
	ERROR_UNION_APPLY_HASNORIGHT							=	-52908	,				// ����ʱû��Ȩ��
	ERROR_UNION_APPLY_ONDISBANDSTATUS							=	-52907	,			// ����ʱ���ڽ�ɢ
	ERROR_UNION_APPLY_NOTINSAMECOUNTRY							=	-52906	,			// ����ʱ����ͬһ������
	ERROR_UNION_APPLY_HASINUNION							=	-52905	,				// ����ʱ�Ѿ�������
	ERROR_UNION_APPLY_APPLYLISTFULL							=	-52904	,				// ����ʱ�б�����
	ERROR_UNION_APPLY_INAPPLYLIST							=	-52903	,				// ����ʱ�Ѿ����б���
	ERROR_UNION_REPLYAPPLY_NOTEXIST							=	-52902	,				// ��Ӧ����ʱ�����ھ���
	ERROR_UNION_REPLYAPPLY_INUNION							=	-52901	,				// ��Ӧʱ�Ѿ�������
	ERROR_UNION_REPLYAPPLY_MEMBERFULL							=	-52900	,			// ��Ӧʱ��Ա����
	ERROR_UNION_INVITE_CORPSNOTEXIST							=	-52899	,			// ����ʱû�о���
	ERROR_UNION_INVITE_INUNION							=	-52898	,					// ����ʱ�Ѿ��ھ���
	ERROR_UNION_INVITE_ONDISBANDSTATUS							=	-52897	,			// ����ʱ���ڽ�ɢ
	ERROR_UNION_INVITE_NOTINOTHERCOUNTRY							=	-52896	,		// ����ʱ����ͬһ����
	ERROR_UNION_REPLYINVITE_NOTEXIST							=	-52895	,			// ������ʱ����������
	ERROR_UNION_REPLYINVITE_ONDISBANDSTATUS							=	-52894	,		// ������ʱ���ڽ�ɢ
	ERROR_UNION_REPLYINVITE_INUNION							=	-52893	,				// ������ʱ��������
	ERROR_UNION_REPLYINVITE_MEMBERFULL							=	-52892	,			// ������ʱ��Ա����
	ERROR_UNION_LEAVE_ISUNIONHEADER							=	-52891	,				// �˳�ʱ������
	ERROR_UNION_CANOTLEAVEINBATTLE							=	-52890	,				// ս���в����뿪
	ERROR_UNION_KICKCORPS_SELFCORPS							=	-52889	,				// �����߳��Լ�
	ERROR_UNION_MAKE_SELFNOTHEADER							=	-52888	,				// ����ʱ����Ȩ�޲���
	ERROR_UNION_MAKE_OTHERNOTHEADER							=	-52887	,				// ����ʱ�Է�Ȩ�޲���
	ERROR_UNION_MAKE_INVITESELF							=	-52886	,					// ����ʱ�������Լ�
	ERROR_UNION_MAKE_INUNION							=	-52885	,					// ����ʱ�Ѿ��ھ���
	ERROR_UNION_MAKE_INVITEBUSY							=	-52884	,					// ����ʱ����æµ
	ERROR_UNION_INFO_NOTEXIST							=	-52883	,					// ��ȡ��Ϣʱ������
	ERROR_UNION_DISBAND_NOTHEADER							=	-52882	,				// ��ɢʱ�����ų�
	ERROR_UNION_DISBAND_INBATTLE							=	-52881	,				// ս�����޷���ɢ
	ERROR_UNION_APPLYLIST_NOUNION							=	-52880	,				// ����б�ʱû������
	ERROR_UNION_LESSCORPS							=	-52879	,						// ��������ʱ��������Ų���
	ERROR_WORLD_INFO_NOCOUNTRY							=	-52878	,					// �Ҳ���ָ������
	ERROR_WORLD_JOIN_ALREADYIN							=	-52877	,					// �Ѿ��ڹ�����
	ERROR_WORLD_JOIN_NOCOUNTRY							=	-52876	,					// �޷�����ָ������
	ERROR_WORLD_LEAVE_NOCOUNTRY							=	-52875	,					// �뿪����ʱû�й���
	ERROR_WORLD_SET_NOCOUNTRY							=	-52874	,					// ����ʱ�Ҳ�������
	ERROR_WORLD_SET_NOTKING							=	-52873	,						// ����ʱ���ǹ���
	ERROR_WORLD_SET_NOOFFICIAL							=	-52872	,					// ����ʱ��ְ����ȷ
	ERROR_WORLD_SET_NOTONLINE							=	-52871	,					// ���������˲�����
	ERROR_WORLD_SET_ISKING							=	-52870	,						// �����������ǹ���
	ERROR_WORLD_SET_ERRCOUNTRY							=	-52869	,					// ���������˲���һ��
	ERROR_WORLD_UNSET_NOCOUNTRY							=	-52868	,					// ��ְʱ�Ҳ�������
	ERROR_WORLD_UNSET_NOTKING							=	-52867	,					// ��ְʱ���ǹ���
	ERROR_WORLD_UNSET_NOOFFICIAL							=	-52866	,				// ��ְʱ��ְ����ȷ
	ERROR_WORLD_USE_NOCOUNTRY							=	-52865	,					// ʹ��ʱ�Ҳ�������
	ERROR_WORLD_USE_NOTOFFICIAL							=	-52864	,					// ʹ��ʱȨ������
	ERROR_WORLD_USE_NOFUNCTION							=	-52863	,					// ʹ��ʱû�й���
	ERROR_WORLD_USE_NOTONLINE							=	-52862	,					// ��ʹ�õ��˲�����
	ERROR_WORLD_USE_ISKING							=	-52861	,						// ��ʹ�õ����ǹ���
	ERROR_WORLD_USE_ERRCOUNTRY							=	-52860	,					// ��ʹ�õ��˲���һ��
	ERROR_WORLD_USE_NOTIME							=	-52859	,						// ��������
	ERROR_WORLD_USE_NOPOWER							=	-52858	,						// ʹ��ʱû������
	ERROR_WORLD_USE_NOMONEY							=	-52857	,						// ʹ��ʱû��Ǯ
	ERROR_WORLD_USE_NOCONSTRUCT							=	-52856	,					// ʹ��ʱ����Ȳ���
	ERROR_WORLD_OP_ERRWORLD							=	-52855	,						// �������ʱ�������
	ERROR_WORLD_OP_SAMEWORLD							=	-52854	,					// �������ʱͬһ����
	ERROR_WORLD_OP_NOTKING							=	-52853	,						// �������ʱ��������
	ERROR_WORLD_OP_REPLYNOSRC							=	-52852	,					// �������Ӧ��ʱû�з�����
	ERROR_WORLD_OP_WRONGSTATUS							=	-52851	,					// �������ʱ״̬����ȷ
	ERROR_WORLD_OP_NUMLIMIT							=	-52850	,						// �������ʱ����������
	ERROR_CORPS_FULL_CHALL_TIMES							=	-52849	,				// ��ս̫Ƶ��
	ERROR_UNION_MAKE_ISOWNER							=	-52848	,					// һ����ִ������
	ERROR_UNION_MAKE_NAMEERR							=	-52847	,					// ����ʱ���ֻ򹫸����
	ERROR_WORLD_LEAVE_ISCORE							=	-52846	,					// ִ�����Ų����뿪����
	ERROR_UNION_DISBAND_ISLEADER							=	-52845	,				// ��ɢ����ʱ������
	ERROR_UNION_MAKE_NOITEM							=	-52844	,						// ����ǩ��ʱû����Ʒ
	ERROR_UNION_MAKE_DISBAND							=	-52843	,					// ��������ʱ���ڽ�ɢ״̬
	ERROR_UNION_CREAT_HASDIRTYWORD							=	-52842	,				// �����������������
	ERROR_UNION_CREAT_NAMEEXIST							=	-52841	,					// ��������ʱ�����Ѿ�����
	ERROR_WORLD_SET_HASOFFICIAL							=	-52840	,					// ����ʱ�Ѿ��й�ְ
	ERROR_UNION_NOTSAME							=	-52839	,							// ����ͬһ��������= -52839
	ERROR_UNION_HASBEENPRINCE							=	-52838	,					// �Ѿ��ǹ�����
	ERROR_UNION_MAPHASOWNER							=	-52837	,						// ��ͼ�Ѿ��й�����
	ERROR_UNION_DESROOTOFFLINE							=	-52836	,					// �Է����ų�������
	ERROR_UNION_ISTIANZI							=	-52835	,						// �Ѿ�������
	ERROR_UNION_NOTPRINCE							=	-52834	,						// ���ǹ���
	ERROR_UNION_MAPERROR							=	-52833	,						// Ǩ���ǳز���ȷ
	ERROR_CORPS_CHANGE_ISKING							=	-52832	,					// ת��ʱ������
	ERROR_WORLD_SET_LOWLEVEL							=	-52831	,					// ������Աʱ���ҵȼ�����
	ERROR_WORLD_SET_LOWCONSTRUCT							=	-52830	,				// ������Աʱ����ȵȼ�����	
	ERROR_WORLD_AWARD_FULLTIMES							=	-52829	,					// ��ȡ����ʱ��������
	ERROR_WORLD_AWARD_FULLBAGGAGE							=	-52828	,				// ��ȡ����ʱ��������
	ERROR_WORLD_AWARD_NOTOWNER							=	-52827	,					// ��ȡ����ʱû��ռ��
	ERROR_WORLD_AWARD_NOCOUNTRY							=	-52826	,					// ��ȡ����ʱ���Ҳ���
	ERROR_CORPS_GETGOODLIST_HASNOTOWNCITY							=	-52825	,		// ��ռ��ó��в���ʹ�ø�ս���̵�	
	ERROR_CORPS_USELEAGUEBAG_HASNOCORPS							=	-52824	,			// û�о��Ų���ʹ�þ����ع���Ʒ	 
	ERROR_CORPS_BUYCORPSGOOD_NOTALLOWED							=	-52823	,			// ���ܹ���ľ����̵����Ʒ
	ERROR_CORPS_BUYCORPSGOOD_ITEMNOTENOUGH							=	-52822	,		// �����̵���Ʒ����
	ERROR_CORPS_EXCHANGE_NOTALLOWED							=	-52821	,				// ���ܶһ�
	ERROR_CORPS_EXCHANGE_ITEMNOTENOUGH							=	-52820	,			// ��Ʒ�������㣬���ܶһ�
	ERROR_UNION_CHANGENOTHEAD							=	-52819	,					// ����ʱ���Ǿ��ų�
	ERROR_UNION_CHANGEERRNAME							=	-52818	,					// ����ʱ���ִ���
	ERROR_WORLD_SUMMONINREP							=	-52817	,								// �ٻ�ʱ�ڸ�����
	ERROR_WORLD_SUMMONINPRI							=	-52816	,								// �ٻ�ʱ�ڼ�����
	ERROR_CORPS_BUYCORPSITEM_HASNORIGHT							=	-52815	,			// ��������̵����Ʒʱû��Ȩ��
	ERROR_WORLD_SUMMONINGROUND							=	-52814	,					// �ٻ�ʱ�ڵع���
	ERROR_WORLD_SUMMONINFOREIGN							=	-52813	,					// �ٻ�ʱ�����
	ERROR_WORLD_SUMMONINSTALL							=	-52812	,					// �ٻ�ʱ�ڰ�̯
	ERROR_WORLD_SUMMONEDINPRI							=	-52811	,					// ���ٻ�ʱ�ڼ�����
	ERROR_WORLD_BATTLEUSE							=	-52810	,						// ���ܶ�ս�����ʹ��
	ERROR_WORLD_SUMMONEDINSTA							=	-52809	,					// ��̯ʱ���ܱ��ٻ�
																						
	ERROR_CORPS_LEAVECORPS_NOTFAMILYHEADER			= -52808,	// ���Ǽ����峤û��Ȩ���뿪����
	ERROR_CORPS_KICKFAMILY_CORPSHEADERINFAMILY		= -52807,	// ���߼����Ǵ󽫾����ڼ���

	ERROR_CORPS_CANTLOGINBATTLE						= -52806,	// ���ܽ���ս��
	ERROR_WORLD_SUMMONINWEDDINGHALL					= -52805,	// �ٻ�ʱ������
	ERROR_WORLD_NOTREDPRISON						= -52804,	// �������ܹ�

	ERROR_WAR_SUBMITLOWLEVEL						= -52803,	// �����ȼ���
	ERROR_WAR_SUBMITNOMONEY							= -52802,	// ����ûǮ
	ERROR_WAR_WARFULL								= -52801,	// ս������	
	ERROR_NOT_CORPS_APPLY_TIME						= -52800,	// ս��ʱ�䲻���޸Ĳ�ս����
	ERROR_WAR_NOTKING								= -52799,	// ���ǹ���
	ERROR_WAR_HASMONEY								= -52798,	// �Ѿ����۹���
	ERROR_WAR_HASSUBMIT								= -52797,	// �Ѿ�������
	ERROR_WAR_NOTSUBMITTIME							= -52796,	// ���Ǳ���ʱ��
	ERROR_WAR_NOTSUBMIT								= -52795,	// ��û�б���
	ERROR_WAR_NOTWARTIME							= -52794,	// ����ս��ʱ��
	ERROR_WAR_NOAWARD								= -52793,	// �����콱
	ERROR_WAR_MONEYFULL								= -52792,	// �콱��Ǯ��
	ERROR_WAR_LOSE									= -52791,	// �콱ʱս��
	ERROR_WAR_NOTBIDTIME							= -52790,	// ���Ǿ���ʱ��
	ERROR_WAR_BIDLOW								= -52789,	// ����Ǯ��
	ERROR_TAX_GETNOTKING							= -52788,	// û��Ȩ����ѯ
	ERROR_TAX_OVERTIMES								= -52787,	// �������ô���
	ERROR_TAX_SETNOTKING							= -52786,	// û��Ȩ������

	ERROR_WORLD_NOTLEADER							= -52785,	// û��Ȩ���ٻ�

	ERROR_CORPS_BIDINDISBANDING						= -52784,	// ���Ŵ��ڽ�ɢ״̬���ܾ���
	ERROR_WAR_GMNOSUBMIT							= -52783,	// GM���ò��ܱ���
	
	ERROR_CAMP_NotWeakCamp							= -52782,	// ���������Ӫ����������Ӫ
	ERROR_CAMP_NotWeakCampL2						= -52781,	// ��Ҳ������ƶ������£�����������Ӫ��������ȡ��Ʒ����
	ERROR_CAMP_AlreadyGetAward_Week					= -52780,	// �Ѿ���ȡ�����ܵ�������Ӫ����
	ERROR_CAMP_AlreadyGetAward_Day					= -52779,	// �Ѿ���ȡ�������������Ӫ����

	ERROR_ACCUSE_LOWLEVEL							= -52778,	// �����ȼ�����
	ERROR_ACCUSE_NOMONEY							= -52777,	// ����ûǮ
	ERROR_ACCUSE_NOTTIME							= -52776,	// ����ʱ�䲻��
	ERROR_ACCUSE_HASVOTED							= -52775,	// �Ѿ�Ͷ��Ʊ
	ERROR_CORPS_ACCUSEFORBID						= -52774,	// �����������ܾ���
	ERROR_CORPS_SubBidMainCity						= -52773,	// ����֮�е��Ӿ��Ų��ܾ�������

	ERROR_UNOIN_INVITE_CITY_CONTENDER				= -52772,	// �������������������ǵľ��ţ����������Ǿ��ۣ���ȴ���ս��ս���еľ��ţ� 
	ERROR_UNOIN_APPLY_CITY_CONTENDER				= -52771,	// �������Ѳ����������ǣ����������Ǿ��ۣ���ȴ���ս��ս���еľ��ţ�����ʱ��������������
	ERROR_UNOIN_REAPPLY_CITY_CONTENDER				= -52770,	// �Է������Ѳ����������ǣ����������Ǿ��ۣ���ȴ���ս��ս���еľ��ţ�������ͬ��Է����������
	ERROR_UNOIN_REINVITE_CITY_CONTENDER				= -52769,	// �������Ѳ����������ǣ����������Ǿ��ۣ���ȴ���ս��ս���еľ��ţ����Է���������Ч

	ERROR_WORLD_FUNCTIONTIMEERR						= -52768,	// ʹ�ù�ְ����ʱ�����
	ERROR_WORLD_CANNOTUSEGT							= -52767,	// ��ǰ����ʹ�ù�̽
	ERROR_WORLD_CANNOTUSELW							= -52766,	// ��ǰ����ʹ������
	ERROR_CANNOT_FIND_CORPS_BOSS					= -52765,	// �����ҵ��ٻ��ľ���boss
	ERROR_CORPCRYSTAL_NOTENOUGH						= -52764,	// û���㹻��boss����
	ERROR_CORPBOSSREPETION_NOTOPEN					= -52763,	// ����boss����û�п���
	ERROR_CORPBOSS_INCD										= -52762,  // ����boss����CD�У��޷��ٴ��ٻ�
	ERROR_CORPLEVEL_NOTENOUGH							= -52761,  // ���ŵȼ��������޷��ٻ�����boss
	ERROR_CORPS_REFINEVAL_NOTENOUGH							= -52760,  // ���ŵ������Ȳ������޷��ٻ�����boss

};

//	����( -53999 ~ -53000 )
enum EMagicWeapon
{
	ERROR_MW_NOT_ENOUGH_POINTS							=	-53999	,		// �ӵ�ʱ û���㹻���Ǳ�ܵ�
	ERROR_MW_ERRPERCENT							=	-53998	,				// ����ľ���������
	ERROR_MW_SKILLEXSITED							=	-53997	,			// �ü��ܿ������м���
	ERROR_MW_SKILLBOXNOTACT							=	-53996	,			// �ü��ܿ�û�м���
	ERROR_MW_ERRSKILL							=	-53995	,				// ����ļ���(�ڲ�����)
	ERROR_MW_NOSUCKSKILL							=	-53994	,			// û���������
	ERROR_MW_NOTEQUIP							=	-53993	,				// û��װ������
	ERROR_MW_NOTMW							=	-53992	,					// �������Ĳ��Ƿ���
	ERROR_MW_NOTMWSTONE							=	-53991	,				// �������Ĳ��Ƿ�������ʯ
	ERROR_MW_JUDGENOMONEY							=	-53990	,			// ������ʱ��Ǯ����
	ERROR_MW_SKILLNEEDMORELEVEL							=	-53989	,		// ��������ȼ����� 989
	ERROR_MW_SKILLNOPOINTS							=	-53988	,			// û���㹻�ļ��ܵ�
	ERROR_MW_SKILLMAXLEVEL							=	-53987	,			// ���������ѵ����ȼ�
	ERROR_MW_NOSTONE							=	-53986	,				// û�м���ʯ
	ERROR_MW_NPCINVALID							=	-53985	,				// NPC����Ƿ���
	ERROR_MW_ERRORBOXINDEX							=	-53984	,			// ����ļ��ܿ�����
	ERROR_MW_CANTUSEBOOK							=	-53983	,			// �÷�������ʹ�ü�����
	ERROR_MW_BOOKCOLORERROR							=	-53982	,			// �������뼼�ܿ���ɫ��һ��
	ERROR_MW_HASEDBOOKSKILL							=	-53981	,			// �Ѿ��иü����ˣ�����ʹ�ü�����ϳ�
	ERROR_MW_SKILLREPEATED							=	-53980	,			// ӵ�м����ظ�
	ERROR_MW_NOTSKILLBOOK							=	-53979	,			// �ϷŵĲ��Ǽ����� 979
	ERROR_MW_BADUSE							=	-53978	,					// �ù�������Ʒ����ʹ��
	ERROR_MW_CANTJUDGE							=	-53977	,				// ������ܿ��ܼ���
	ERROR_MW_LEVELUP							=	-53976	,				// ��ϲ�� ��������
	ERROR_MW_FULLHP							=	-53975	,					// ��ķ�������ֵ���� ���ó�ҩ
	ERROR_MW_FULLMP							=	-53974	,					// ��ķ�������ֵ���� ���ó�ҩ
	ERROR_MW_STEPCLEARED							=	-53973	,			// ����ȼ����Ѿ�Сϴ����
	ERROR_MW_CLEAR_STONE_ERROR							=	-53972	,		// ���ϵķ���ϴʯͷ���Ͳ�ƥ��
	ERROR_MW_CLEAR_TYPE_ERROR							=	-53971	,		// ϴ�����ʹ���
	ERROR_MW_CANT_CLEARPOINT							=	-53970	,		// �޷�ϴ��
	ERROR_MW_CANT_CLEARSP								=	-53969	,		// ûװ������ �޷�ϴ���ܵ�
	ERROR_MW_SP_NOADD									=	-53968	,		// ����û�мӵ㣬����Ҫϴ��
	ERROR_MW_DECPOM_BAGFUL								=	-53967	,		// �ֽⷨ��ʱ��������
	ERROR_MW_DECPOM_LESSMONEY								=	-53966	,		// �ֽⷨ��ʱ��ûǮ
	ERROR_MW_PRINT_LESSMONEY								=	-53965	,		// ����ӡ��ʱ��ûǮ
	ERROR_MW_PRINT_FAILED								=	-53964	,		// ����ӡ��ʧ��
	ERROR_MW_PRINT_ERRPIN								=	-53963	,		// Ʒ����ͬ������ӡ��
	ERROR_MW_QUICKUP_LEVELLESS							=	-53962	,		// �ȼ����������ܷ���
	ERROR_MW_QUICKUP_LESSMONEY							=	-53961	,		// ��������ʱ��ûǮ
	ERROR_MW_QUICKUP_LESSITEM							=	-53960	,		// ��������ʱ����Ʒ����
	ERROR_MW_QUICKUP_FAILED								=	-53959	,		// ��������ʱ��ʧ��
	ERROR_MW_UPLEVEL_ERROR2NDMW							=	-53958	,		// ������Ʒʱ��������������Ҫ��
	ERROR_MW_USESKILLBOOK_FAILED						=	-53957	,		// ʹ�ü�����ѧϰ���� ʧ��
	ERROR_MW_USESKILLBOOK_NOMONEY						=	-53956	,		// ʹ�ü�����ѧϰ���� ûǮ
	ERROR_MW_CANTIN_INVALIDBAG							=	-53955	,		// ����ʹ���ѹ��ڰ����еĲ���
	ERROR_MW_MWCANTIN_INVALIDBAG						=	-53954	,		// ����ʹ���ѹ��ڰ����еķ���
	ERROR_MW_QL_LESS									=	-53953	,		// �ϳ�ʱ���鲻��
	ERROR_MW_LEVEL_FULL									=	-53952	,		// �����Ѿ��ﵽ��ߵȼ�
	ERROR_MW_PRINT_PIN_ERR								=	-53951	,		// ����ӡ��ʱ���˷��ͷ���Ʒ����ͬ������ӡ��
	ERROR_MW_BIND_BYITEM								=  -53950,		// �������ֶ��󶨣�����ִ�иò���
};

// �����( -54999 ~ -54000 )
enum EM_LifeSkillError
{	
	ERROR_LIFESKILL_COMPOSENOTEXIST							=	-54999	,						// ѧϰ�䷽ʱ�䷽������
	ERROR_LIFESKILL_WRONGLIFESKILL							=	-54998	,						// ѧϰ�䷽ʱ�������Ͳ���
	ERROR_LIFESKILL_LOWDEGREE							=	-54997	,							// �����Ȳ���	
	ERROR_LIFESKILL_WRONGGETWAY							=	-54996	,							// �䷽�Ļ�ȡ��ʽ����
	ERROR_LIFESKILL_COMPOSEHASEXIST							=	-54995	,						// ѧϰ�䷽ʱ�䷽�Ѿ�����
	ERROR_LIFESKILL_HASINITIALIZED							=	-54994	,						// ������Ѿ�����
	ERROR_LIFESKILL_NOTINITIALIZED							=	-54993	,						// ѧϰ�����ʱ��û������
	ERROR_LIFESKILL_DIFFINITIALSKILL							=	-54992	,					// ѧϰ����������������ŵ�ʱ�������Ͳ�ͬ
	ERROR_LIFESKILL_LIFESKILLTABLENOTEXIST							=	-54991	,				// ����ܱ�����
	ERROR_LIFESKILL_CANNOTLEVELUP							=	-54990	,						// ����ܲ�������
	ERROR_LIFESKILL_LEVELNEEDMOREDEGREE							=	-54989	,					// ����ܽ�����Ҫ�����������
	ERROR_LIFESKILL_COMPOSENOTSTUDIED							=	-54988	,					// ����ܲ�δѧϰ
	ERROR_LIFESKILL_STUDYCOMPOSEFAILED							=	-54987	,					// �����䷽ʧ��
	ERROR_LIFESKILL_SKILLFULL							=	-54986	,							// ������Ѿ�ѧ��������ѧ
	ERROR_LIFESKILL_SKILLEXIST							=	-54985	,							// ���������ѧ
	ERROR_LIFESKILL_INITIALLEVELLOW							=	-54984	,						// ѧϰ�����ʱ�ȼ�����
	ERROR_LIFESKILL_STUDYMONEYNOTENOUGH							=	-54983	,					// ѧϰ�����ʱ��Ǯ����
	ERROR_LIFESKILL_LEVELUPMONEYNOTENOUGH							=	-54982	,				// ����ܽ���ʱ��Ǯ����	
	ERROR_LIFESKILL_LEVELUPLEVELNOTENOUGH							=	-54981	,				// ����ܽ���ʱ�ȼ�����
	ERROR_LIFESKILL_ITEMCANOTDECOMPOUND							=	-54980	,					// ��Ʒ���ܱ��ֽ�
	ERROR_LIFESKILL_DECOMPOUNDWITHOUTSPACE							=	-54979	,				// �ֽ�װ��ʱ�����ռ䲻��
	ERROR_LIFESKILL_DECOMPOUNDWITHOUTGOLDMAKE							=	-54978	,			// û�е���ܲ��ֽܷ�װ��
	ERROR_LIFESKILL_DECOMPOUNDWITHOUTENGOUGHDEGREE							=	-54977	,		// �ֽ�װ��ʱ�����Ȳ���
	ERROR_LIFESKILL_USECOMPOSEWITHOUTLIFESKILL							=	-54976	,			// ʹ���䷽ʱû�и������
	ERROR_LIFESKILL_COMPOSEDEGREENOTENOUGH							=	-54975	,				// ʹ���䷽ʱ�����Ȳ���
	ERROR_LIFESKILL_COLLECTWITHOUTRIGHTSKILL							=	-54974	,			// �ɼ�ʱû��ѧϰ�ɼ�����
	ERROR_LIFESKILL_COLLECTDEGREELOW							=	-54973	,					// ���вɼ�ʱ�����Ȳ���
	ERROR_LIFESKILL_COLLECTAPLOW							=	-54972	,						// �ɼ�ʱ��apֵ����
	ERROR_LIFESKILL_SETMAGICEUIPLEVELLOW							=	-54971	,				// ��ħʱװ���ȼ�����
	ERROR_LIFESKILL_SETMAGICFAILED							=	-54970	,						// ��ħʧ��
	ERROR_LIFESKILL_SETMAGICWITHOUTSKILL							=	-54969	,				// ��ħʱû�е����
	ERROR_LIFESKILL_SETEQUIPMAGICWRING							=	-54968	,					// �����ø�ħʯ����װ����ħ
	ERROR_LIFESKILL_USELIFESKILLPHISICWRONG							=	-54967	,				// ����ʹ�������ҩƷ
	ERROR_LIFESKILL_SPECIALIZEDEGREEFULL							=	-54966	,				// ������������Ѿ��������޲���Ҫ��ҩ
	ERROR_LIFESKILL_APNOTENOUGH							=	-54965	,							// ѧϰ�����ʱAPֵ����	
	ERROR_LIFESKILL_SETNUMLIMIT							=	-54964	,							// װ����ħʱͬ�ָ�ħʯ�Ѵ︽ħ����	
	ERROR_LIFESKILL_COMPOSESTUDYMONEYNOTENOUGH							=	-54963	,			// ѧϰ�䷽ʱ��Ǯ����
	ERROR_LIFESKILL_EQUIPNOTCOMPONEDE							=	-54962	,					// װ�����ɷֽ�
	ERROR_LIFESKILL_ITEMCANNOTCREATCOMPOSE							=	-54961	,				// ��Ʒ���������䷽����
	ERROR_LIFESKILL_BAGFULLWHENCOLLECT							=	-54960	,					// �ɼ�ʱ������	
	ERROR_LIFESKILL_COLLECTLEVELLOW								=	-54959	,					// �ɼ��ȼ���	

};

// �̳� ( -55999 �� -55000 )
enum EMIBStoreError
{
	ERROR_IBITEM_DOESNOT_EXIST 			= -55999,			// ��Ʒ������
	ERROR_IBITEM_ISNOT_ACTIVE  			= -55998,			// ��Ʒ����Ч
	ERROR_IBITEM_ISNOT_ENOUGH  			= -55997,			// ��Ʒ��Ŀ����
	ERROR_IBITEM_INTERNAL	   			= -55996,			// ���ݿ��ڲ�����, ������ʱ������
	ERROR_PLAYER_HAS_ANOTHER_TRANS		= -55995,			// ��������ڽ����е�δ�꽻��
	ERROR_PLAYER_HASNO_ENOUGHYB			= -55994,			// ���Ԫ�����ݲ���
	ERROR_PLAYER_HASNO_ACTIVEITEM 		= -55993,			// ���û����Ʒ���������Ѿ���ȡ����
	ERROR_ONLY_ONE_IBITEM_PERMITED		= -55992,			// ���ɶѵ�����Ʒֻ�ܹ���һ��
	ERROR_INSERTITEM_INTERNAL			= -55991, 			// ������Ʒ�ڲ�����
	ERROR_IBITEM_INVALID_NUMBER			= -55990,			// ����������Ʒ��������ȷ
	ERROR_IBSTORE_SAME_VERSION			= -55989,			// �̳ǰ汾��һ��
	ERROR_IBSTORE_INVALID_INPUT			= -55988,			// �������Ƿ�
	ERROR_IBSTORE_DRAW_SUCCESS			= -55987,			// ������ȡ�ɹ�
	ERROR_IBSTORE_DRAW_FAILURE			= -55986,			// ������ȡʧ��
	ERROR_IBSTORE_DRAW_ISNOT_ACTIVE		= -55985,			// ���񲻿���
	ERROR_PLAYER_IBITEM_LIMITED			= -55984,			// ������Ʒ�������� 
	ERROR_IBSTORE_INVALID_TRANS			= -55983,			// ��Ч�Ľ���
	ERROR_IBSTORE_LOCK_SUCCESS          = -55982,           // ������������Ʒ�ɹ�
	ERROR_IBSTORE_INVALID_TIME			= -55981,			// ��Ч��ʱ���
	ERROR_IBTRANS_NOT_RETURN			= -55920,			// �ϴν���δ���أ������µ�¼��

	ERROR_FUNC_DOESNOT_EXIST			= -55979,			// ���ܸ��������
	ERROR_FUNC_HASNO_ENOUGHMONEY		= -55978,			// û���㹻�Ľ�Ǯ
	ERROR_FUNC_USE						= -55977,			// ���ܸ��ѵĹ���ʹ��ʧ��
	ERROR_FUNC_TRANS_OBJ_FULL			= -55976,			// ���ܸ��ѽ��׶�������
	ERROR_PLAYER_HASNO_ENOUGHBINDYB		= -55975,			// ��Ұ�Ԫ����������
	ERROR_PLAYER_HASNO_ENOUGHFAME		= -55974,			// ��Ұ�Ԫ����������
};


// ���˴����� ( -56100 ~ -56000 )
enum EmKickOutReason
{
	EM_KICKOUT_ANTIBOT					= -56100,		// ���������,���������
	EM_KICKOUT_LOCKDATA					= -56099,		// ��������쳣����ɫ������������ϵ�ͷ���Ա
														// ��: ��Ҵ��̲������� �����������ģ�����Ҳ����ȵȣ�
														// ����������ң���ȷ��������������ݶ�ʧ
	EM_KICKOUT_TIMEOUT					= -56098,		// �ͻ������ӳ�ʱ
	EM_KICKOUT_SERVERMAINTANCE			= -56097,		// ������ͣ��ά��
	EM_KICKOUT_GM						= -56096,		// GM����
	EM_KICKOUT_ACCOUNTTRUSTEE			= -56095,		// �ʺű��й�
	EM_KICKOUT_UNKOWNACTION				= -56094,		// �����Ϊ�쳣( �磺�������������������Ϣ )
	EM_KICKOUT_RELOGIN					= -56093,		// ����ظ���¼����
	EM_KICKOUT_NOTINGATE				= -56092,		// ��ҵ��������ݲ�����
	EM_KICKOUT_SAVETIMEOUT				= -56091,		// ���̳�ʱ����
	EM_KICKOUT_ACCOUNTFROZEN			= -56090,		// �����ʺ�����
	EM_KICKOUT_ANTIBOT_MULTICLIENT		= -56089,		// ��������ˣ� �ͻ��˶࿪������3����
	EM_KICKOUT_ANTIBOT_VM				= -56088,		// ��������ˣ� ��������		
	EM_KICKOUT_ANTIBOT_MULTIUSER		= -56087,		// ��������ˣ� ���û�
	EM_KICKOUT_ANTIADDICTION			= -56086,		// ����������
	EM_KICKOUT_SPEEDCHEATING			= -56085,		// �ƶ��ٶ��쳣��������Ϸ
	EM_KICKOUT_SPEEDCHEATING2			= -56084,		// �ƶ��ٶ��쳣��������Ϸ
	EM_KICKOUT_MULTICLIENT				= -56083,		// ��IP��½��ҹ���, ������Ϸ
	EM_KICKOUT_DATACRASH				= -56082,		// �����𻵣���½��Ϸʧ��(�磺�������������ģ�����Ҳ��������ݿ����ֶ���Ŀ����ȷ)
	EM_KICKOUT_ANTIBOT_OTHER			= -56081,		// �������������
};

enum EmKickOutResult
{
	EM_KICKOUT_NOTHISCHAR				= -56050,		// ��Ҳ�����
	EM_KICKOUT_SAVING					= -56049,		// ������ڴ���, ���Ժ�
	EM_KICKOUT_KICKING					= -56048,		// ������ڱ��߹����У����Ժ�
	EM_KICKOUT_WITHOUTSAVE				= -56047, 		// �Ǵ������˳ɹ�
};

//  ����ϵͳ( -57999 ~ -57000 )
enum EmMarriageErrcode
{
	EM_MARRIAGE_MARRY_HASNOTEAM					= -57999,		// ���ʱû����ӣ����߶�����������
	EM_MARRIAGE_MARRY_SAMESEX					= -57998,		// ͬ�Բ��ܽ��
	EM_MARRIAGE_MARRY_MARRIED					= -57997,		// �Ѿ���鲻���ٽ��
	EM_MARRIAGE_MARRY_OTHERMARRIED				= -57996,		// �Է��Ѿ���鲻���ٽ��
	EM_MARRIAGE_MARRY_NOTTEAMHEADER				= -57995,		// ���Ƕӳ�����������
	EM_MARRIAGE_MARRY_NOTSAMECAMP				= -57994,		// ��Ӫ��ͬ���ܽ��	
	EM_MARRIAGE_MARRY_MARRIAGELEVELLOW			= -57993,		// ���ȼ�����
	EM_MARRIAGE_MARRY_WRONGWEDDINGTIME			= -57992,		// ���ڲ���
	EM_MARRIAGE_MARRY_WRONGWEDDINGTIMEFAILURE	= -57991,		// �����Ѿ�ʧЧ	
	EM_MARRIAGE_MARRY_MONEYNOTENOUGH			= -57990,		// ��Ǯ����
	EM_MARRIAGE_MARRY_NOTENOUGHBAGSPACE			= -57989,		// ���һ���İ����ռ䲻��
	EM_MARRIAGE_WEDDING_SPOUSEOFFLINE			= -57988,		// ��ʼ����ʱ��ż������
	EM_MARRIAGE_ENTERHALL_NOHOLDWEDDING			= -57987,		// û�����ھ��еĻ���
	EM_MARRIAGE_ENTERHALL_NOTENTERHALL			= -57986,		// ����δ���е����ã����ܽ�������
	EM_MARRIAGE_ENTERHALL_HASNOINVITATION		= -57985,		// û���������ܽ�������
	EM_MARRIAGE_PUTKEEPSAKE_WRONGKEEPSAKE 		= -57984,		// ������ָʱ���õ���Ʒ��������
	EM_MARRIAGE_EXCHANGEKEEPSAKE_NEWLYOFFLINE	= -57983,		// ��������ָʱһ��������
	EM_MARRIAGE_EXCHANGEKEEPSAKE_EMPTYKEEPSAKE	= -57982,		// ��������ָʱ����һ��û�з��ý�ָ
	EM_MARRIAGE_MARRY_OTHERHASMARRIAGEAPPLY		= -57981,		// ���ʱ�Է��Ѿ��л�Լ
	EM_MARRIAGE_DIVOCE_HASNODOVICEITEM			= -57980,		// ���ʱû��������
	EM_MARRIAGE_DIVOCE_NOMARRIAGE				= -57979,		// û�н�鲻�����
	EM_MARRIAGE_INVITATION_RECEIVERNOEXIST		= -57978,		// ���������˲�����
	EM_MARRIAGE_INVITATION_INDIFFCOUNTRY		= -57977,		// ���������˲���ͬһ����Ӫ
	EM_MARRIAGE_INVITATION_NOTINVITATION		= -57976,		// ��������ʱ���Ͳ���(��������)
	EM_MARRIAGE_INVITATION_NOTMARRIED			= -57975,		// û�н�鲻�ܷ�������
	EM_MARRIAGE_PUTKEEPSAKE_NOTINHALL			= -57974,		// û�����ò��ܽ�������
	EM_MARRIAGE_PUTKEEPSAKE_WEDDINGNOTHOLD		= -57973,		// û�о��л����ܽ�������
	EM_MARRIAGE_EXCHANGEKEEPSAKE_NOTMARRIED		= -57972,		// û�н�鲻�ܽ�������
	EM_MARRIAGE_EXCHANGEKEEPSAKE_OTHERNOEREADY	= -57971,		// ��������ʱ�Է�û��׼����
	EM_MARRIAGE_TELEPORT_OTHEROFFLINE			= -57970,		// ������ż�����߻��߲��ڱ���Ӫ�޷�����
	EM_MARRIAGE_ENTERHALL_NOMARRIAGE			= -57969,		// û�н�鲻�����������
	EM_MARRIAGE_ENTERHALL_WRONGTIME				= -57968,		// ��ǰ�����Լ��Ļ����ܽ�������
	EM_MARRIAGE_BEGINWEDDING_WRONGSTATUS		= -57967,		// ����û�н����߻���ʱ��δ�����ܾ��л���
	EM_MARRIAGE_INVITATION_SELFSEND				= -57966,		// ���ܸ��Լ�����ż��������
	EM_MARRIAGE_MARRY_INVALIDWEDDINGTIME		= -57965,		// ��ѡ�����Ѿ�ʧЧ�����ھ�������ʱ��̫�������Ѿ����˸û���
	EM_MARRIAGE_MARRY_INVALIDAPPLY				= -57964,		// �𸴽��ʱ�����Ѿ�ʧЧ
	EM_MARRIAGE_MARRY_FAILED					= -57963,		// ����ʧ�ܣ��Ժ�����
	EM_MARRIAGE_PUTKEEPSAKE_SPOUSEOFFLINE		= -57962,		// ��������ʱ�Է�������
	EM_MARRIAGE_TELEPORT_ONEQUIP				= -57961,		// û��װ������ָ����ʹ��
	EM_MARRIAGE_TELEPORT_NOMARRIED				= -57960,		// û�н�鲻��ʹ�ý��װ���Ĵ��͹���
	EM_MARRIAGE_TELEPORT_NOTMARRIEDEQUIP		= -57959,		// ��	�Ǻ͵�ǰ��ż�Ľ���ָ���ܴ���
	EM_MARRIAGE_TELEPORT_INVALIDMAP				= -57958,		// �ڸ����������ò���ʹ�ý���ָ����
	EM_MARRIAGE_DIVORCE_ONWEDDING				= -57957,		// ��������ʱ�������
	
	EM_MARRIAGE_PUTSAKEEXCHANGE_ONMARRIED		= -57956,		// û�н�鲻�ܽ������ｻ��
	EM_MARRIAGE_PUTSAKEEXCHANGE_WITHOUTDISTANCE	= -57955,		// ��ż�����Զ���ܽ������ｻ��
	EM_MARRIAGE_INVITATIONEXCHANGE_ITEMNOTEXIST	= -57954,		// �����һ�����Ʒ������
	EM_MARRIAGE_INVITATIONEXCHANGE_WRONGITEM	= -57953,		// �����������ܽ��������һ�
	EM_MARRIAGE_INVITATIONEXCHANGE_WEDDINGNOTEND= -57952,		// �������ǰ���ܶһ�����
	EM_MARRIAGE_MARRIAGEEQUIP_NOTMARRIED		= -57951,		// û�н�鲻����ʹ�ý��װ��
	EM_MARRIAGE_MARRIAGEEQUIP_NOTSPOUSE			= -57950,		// �Է�������ż����ʹ����ż����
	EM_MARRIAGE_MARRIAGEEQUIP_NOTMARRIEDKEEPSAKE= -57949,		// ʹ����ż����ʱʹ�õ�װ�����ԣ����Ǻ���ż���ʱ�Ľ��װ��
	EM_MARRIAGE_MARRY_NOMARRIAGEITEM			= -57948,		// ������ʱû�н�����
	EM_MARRIAGE_MARRYAPPLY_WRONGMODULE			= -57947,		// ��ʱ��β���ѡ����ֹ�ģ�Ļ���
	EM_MARRIAGE_MARRY_HASNOBASICITEM			= -57946,		// ���ʱ��֤������������
	EM_MARRIAGE_REVIEWWEDDING_NOTMARRY			= -57945,		// û�н�鲻�����²������
	EM_MARRIAGE_REVIEWWEDDING_WRONGSTATUS		= -57944,		// ����δ���в��ò���	
	EM_MARRIAGE_REVIEWWEDDING_WEDDINGCOOLTIME	= -57943,		// ������һ�λ�����24Сʱ
	EM_MARRIAGE_REVIEWWEDDING_TIMESELECTED		= -57942,		// ���ڲ���ѡ
	EM_MARRIAGE_REVIEWWEDDING_TIMETOONEAR		= -57941,		// ѡ��Ļ���ʱ��������ڵļ��̫��
	EM_MARRIAGE_REVIEWWEDDING_HASNOWEDDINGSCROLL= -57940,		// û�л������
	EM_MARRIAGE_REVIEWWEDDING_NOSPACE			= -57939,		// �����ռ䲻��
	EM_SWORNEQUIPMENT_NOTINSWORNTEAM			= -57938,		// û�н�ݲ���ʹ�ý������
	EM_SWORNEQUIPMENT_NOTINSAMESWORNTEAM		= -57937,		// ���ܶ�û�н�ݵ���ʹ�ý�����＼��
};

enum EmActivityYqsErrcode
{
    EM_YQS_ACTIVITYNOTSTART      =  -58001,             // ҡǮ���Ϊ����
    EM_YQS_USERNOTMATCH          =  -58002,             // �����û���Ŵ���
    EM_YQS_ACTIVITYIDNOTMATCH    =  -58003,             // ����Ļ��Ŵ���
    EM_YQS_HANDINITEMINVALIED    =  -58004,             // �Ͻ���Ʒ����
    EM_YQS_GETGROWINGVALUEFAILED =  -58005,             // ���ܻ�ȡҡǮ���ɳ�ֵ
    EM_YQS_SENDUPDATEMSGTOGATEFAILED =  -58006,         // ��GATE������������Ϣ����

};

enum Notice
{
	NOTICE_REFRESHBOSS							=	-69999	,			// ˢ��BOSS֪ͨ			int0 ����ID int1 MapID int2 PosX int3 PosY 
	NOTICE_PREREFRESHBOSS							=	-69998	,		// ��ǰˢ��BOSS֪ͨ		int0 ����ID(0���⴦��) int1 MapID(��׼ȷ��Ҫ����) int2 ��ǰ
	NOTICE_PLAYERKILLBOSS							=	-69997	,		// ���ɱ��BOSS֪ͨ		int0 ����ID int1 ��ʾ������ string1 �����
	NOTICE_PLAYERKILLBOSS_1							=	-69996	,		// �ͻ���ռλ��
	NOTICE_PLAYERKILLBOSS_2							=	-69995	,		
	NOTICE_PLAYERKILLBOSS_3							=	-69994	,		
	NOTICE_KILLPLAYER							=	-69993	,			// ɱ�����֪ͨ			int0 ɱ������Ӫ int1 ��ɱ����Ӫ int2 ��ͼID int3 PosX int4
	NOTICE_KILLPLAYER_1							=	-69992	,			// �ͻ���ռλ��
	NOTICE_KILLKING							=	-69991	,				// ɱ������֪ͨ			int0 ɱ������Ӫ int1 ��ɱ����Ӫ int2 ���� string1 ɱ������ string2 ��ɱ����
	NOTICE_KILLKING_1							=	-69990	,			// �ͻ���ռλ��
	NOTICE_DOPLAYER							=	-69989	,				// ��Ҵ���֪ͨ			int0 Type int1 Order int2 ����ID	string1 ����������
	NOTICE_KINGONLINE							=	-69988	,			// ��������				int0 0 off / 1 on int1 ��ӪID int2 ����ID string1 ��������
	NOTICE_OPEN_LUCKYBAG1						=	-69987	,			// ��Ǭ���������ö���	int0 ��ҽ�ɫID int1 ��ҿ�����Ʒ��ģ��ID int2 ��һ�õ���ƷID int3 ��һ�õ���Ʒ������ string0 �������
	NOTICE_OPEN_LUCKYBAG2						=	-69986	,			// ��Ǭ���������ö���	int0 ��ҽ�ɫID int1 ��ҿ�����Ʒ��ģ��ID int2 ��һ�õ���ƷID int3 ��һ�õ���Ʒ������ string0 �������
	NOTICE_OPEN_LUCKYBAG3						=	-69985	,			// ��Ǭ���������ö���	int0 ��ҽ�ɫID int1 ��ҿ�����Ʒ��ģ��ID int2 ��һ�õ���ƷID int3 ��һ�õ���Ʒ������ string0 �������
	NOTICE_OPEN_LUCKYBAG4						=	-69984	,			// ��Ǭ���������ö���	int0 ��ҽ�ɫID int1 ��ҿ�����Ʒ��ģ��ID int2 ��һ�õ���ƷID int3 ��һ�õ���Ʒ������ string0 �������
	NOTICE_OPEN_LUCKYBAG5						=	-69983	,			// ��Ǭ���������ö���	int0 ��ҽ�ɫID int1 ��ҿ�����Ʒ��ģ��ID int2 ��һ�õ���ƷID int3 ��һ�õ���Ʒ������ string0 �������
	NOTICE_OPEN_LUCKYBAG6						=	-69982	,			// ��Ǭ���������ö���	int0 ��ҽ�ɫID int1 ��ҿ�����Ʒ��ģ��ID int2 ��һ�õ���ƷID int3 ��һ�õ���Ʒ������ string0 �������
	NOTICE_OPEN_LUCKYBAG7						=	-69981	,			// ��Ǭ���������ö���	int0 ��ҽ�ɫID int1 ��ҿ�����Ʒ��ģ��ID int2 ��һ�õ���ƷID int3 ��һ�õ���Ʒ������ string0 �������
	NOTICE_OPEN_LUCKYBAG8						=	-69980	,			// ��Ǭ���������ö���	int0 ��ҽ�ɫID int1 ��ҿ�����Ʒ��ģ��ID int2 ��һ�õ���ƷID int3 ��һ�õ���Ʒ������ string0 �������
	NOTICE_OPEN_LUCKYBAG9						=	-69979	,			// ��Ǭ���������ö���	int0 ��ҽ�ɫID int1 ��ҿ�����Ʒ��ģ��ID int2 ��һ�õ���ƷID int3 ��һ�õ���Ʒ������ string0 �������
	NOTICE_OPEN_LUCKYBAG10						=	-69978	,			// ��Ǭ���������ö���	int0 ��ҽ�ɫID int1 ��ҿ�����Ʒ��ģ��ID int2 ��һ�õ���ƷID int3 ��һ�õ���Ʒ������ string0 �������
	NOTICE_MINEMAP								=	-69977	,			// ���ر�ͼ�ö��� int0 ��ҽ�ɫID int1 �� int2 ��һ�õ���ƷID int3 ��һ�õ���Ʒ������ string0 �������
	NOTICE_MINEMAP_SELF_MONEY					=	-69976	,			// �Լ��Ĳر�ͼ��Ϣ
	NOTICE_MINEMAP_SELF_ITEM					=	-69975	,			// �Լ��Ĳر�ͼ��Ϣ
	NOTICE_MINEMAP_OTHER_MONEY					=	-69974	,			// ���˵Ĳر�ͼ��Ϣ
	NOTICE_MINEMAP_OTHER_ITEM					=	-69973	,			// ���˵Ĳر�ͼ��Ϣ
	NOTICE_IBSTORE_TIMER_SELLING				=  	-69972	, 			// �̳�ĳ���߼�������
	NOTICE_IBSTORE_TIMER_SELLED					=  	-69971	, 			// �̳�ĳ�����Ѿ�����
	NOTICE_IBSTORE_TIMER_OVER					=   -69970	, 			// �̳�ĳ�����Ѿ���ֹ
	NOTICE_IBSTORE_NUMBER						=   -69969	, 			// �̳�ĳ����������ʾ
	NOTICE_IBSTORE_ZERO							=   -69968	, 			// �̳�ĳ����������ʾ

	NOTICE_WAR_STATUSCHANGED					=	-69967	,			// ս��״̬�ı� int0 ��ǰս��״̬
	NOTICE_WAR_STONE_CREATE						=	-69966,				// ��ʯ����				int0 ����X int1 ����Y int3 ģ��ID
	NOTICE_WAR_STONE_PICK						=	-69965,				// ��ʯ����				int0 ����X int1 ����Y 	int2 ģ��ID int3 ��ӪID string1 ����
	NOTICE_WAR_STONE_THROW						=	-69964,				// ��ʯ����				int0 ����X int1 ����Y int2 ģ��ID	int3 ��ӪID	 string1 ����
	NOTICE_WAR_STONE_GIVE						=	-69963,				// ��ʯ����				int0 ����X int1 ����Y int2 ģ��ID   int3 ��ӪID	 string1 ����
	NOTICE_WAR_FLAG_CUTDOWN						=	-69962,				// ���쿳��				int0 ����X int1 ����Y int2 ģ��ID	int3 ԭ��ӪID	int4 ����ӪID int5 ��Դ�� string1 ����
	NOTICE_WAR_FLAG_OCCUPY						=	-69961,				// �ݵ�ռ��				int0 ����X int1 ����Y int2 ģ��ID	int3 ԭ��ӪID	int4 ����ӪID int5 ��Դ��  string1 ����
	NOTICE_WAR_RESULT_CAMP						=	-69960,				// �ֲ�ս��				int0 ս��ID int1 ��ʤ��ӪID int ����
	NOTICE_WAR_RESULT_ALL						=	-69959,				// ����ս��				int0 ��ʤ��ӪID string1 ��������
	
	// ��ע�⡿ ����Ϣ���ʱ��ע��Ǭ����Ԥ���ĺŶΣ�
	NOTICE_OPEN_LUCKYBAG_MIN					=   -69800,				// Ǭ����ר��֪ͨ��Ϣ����
	NOTICE_OPEN_LUCKYBAG_MAX					=   -69600,				// Ǭ����ר��֪ͨ��Ϣ����
	
	NOTICE_OGREKILLBOSS							=   -69599,				// boss������ɱ��
	NOTICE_OGREKILLBOSSPRENOTICE     			=   -69598,				// ���ｫҪȥɱboss��֪ͨ
	
	NOTICE_STARTOGRESIEGE						=   -69597,				// ���﹥�ǻ��ʼ
	NOTICE_ENDOGRESIEGE							=   -69596,				// ���﹥�ǻ����
	NOTICE_SHOWOGRELIVETIME						=   -69595,				// ��ʾ����Ĵ��ʱ��
	NOTICE_GRASSJELLYLIVETIME					=   -69594,				// �ɲ�������ʾ	
	NOTICE_MARSHALTIMELEFT						=   -69593,				// ����Ԫ˧���ֵ���ʱ
	NOTICE_MARSHALFLEETIMELEFT					=   -69592,				// ����Ԫ˧���ӵ���ʱ
	NOTICE_GRASSLIVETIMELEFT					=   -69591,				// �ɲ�2����ʱ

    NOTICE_YQS_IRRIGATEPRIZE                    =   -69590,             // ҡǮ���-���XXX������¶�����˵Ļ��������Ľ�Ҷ֮����!
    NOTICE_YQS_IRRIGATE1                        =   -69589,             // ҡǮ���-ҡǮ���ɳ���!������XXX���齱����XXX���׻���!
    NOTICE_YQS_IRRIGATE2                        =   -69587,             // ҡǮ���-ҡǮ���ɳ���!������XXX���齱��!
    NOTICE_YQS_GROWING1                         =   -69586,             // ҡǮ���-����Ӫ��ҡǮ��������ѿ�ˣ�����������¶��
    NOTICE_YQS_GROWING2                         =   -69585,             // ҡǮ���-����Ӫ��ҡǮ�����������ˣ�����������¶��
    NOTICE_YQS_GROWING3                         =   -69584,             // ҡǮ���-����Ӫ��ҡǮ�����������ˣ�����������¶��
    NOTICE_YQS_GROWING4                         =   -69583,             // ҡǮ���-����Ӫ��ҡǮ����������ˣ�����������¶��
    //NOTICE_YQS_FINISHING1                       =   -69582,             // ҡǮ���-30���Ӻ󼴽����
    //NOTICE_YQS_FINISHING2                       =   -69581,             // ҡǮ���-20���Ӻ󼴽����
    NOTICE_YQS_FINISHING3                       =   -69580,             // ҡǮ���%s���Ӻ󼴽����
    NOTICE_YQS_FINISHING4                       =   -69579,              // ҡǮ���-������������佱��

	NOTICE_ACCUSE_LESSPEOPLE					=	-69578,				// ����ͶƱ�������� int0 ��ӪID int1 �޳� int2 ����	string1 ��������
	NOTICE_ACCUSE_LESSPERCENT					=	-69577,				// ������������		int0 ��ӪID int1 �޳� int2 ����	string1 ��������
	NOTICE_ACCUSE_SUCCESS						=	-69576,				// �����ɹ�			int0 ��ӪID int1 �޳� int2 ����	string1 ��������
	NOTICE_ACCUSE_DIRECT						=	-69575,				// ����ֱ����̨		int0 ��ӪID string1 ��������
	NOTICE_ACCUSE_KILLGATE						=	-69574,				// ���ű�ɱ��	int0 Դ��ӪID int1 Ŀ����ӪID string1 ɱ��������
	NOTICE_ACCUSE_KILLFLAG						=	-69573,				// ���챻ɱ��	int0 Դ��ӪID int1 Ŀ����ӪID string1 ɱ��������
	NOTICE_ACCUSE_CHANGEPOWER					=	-69572,				// �����ı�		int0 Դ��ӪID int1 Ŀ����ӪID int2 Դ���� int3 Ŀ������
	NOTICE_ACCUSE_PREPARE						=	-69571,				// ������ʼ			int0 ��ӪID string1 ��������
	NOTICE_ACCUSE_BEGIN							=	-69570,				// ������ʼ			int0 ��ӪID string1 ��������
	NOTICE_ACCUSE_HALFHOUR						=	-69569,				// ��Сʱ����		int0 ��ӪID string1 ��������
	NOTICE_ACCUSE_TOBE							=	-69568,				// ������			int0 ��ӪID string1 ��������
	NOTICE_ACCUSE_POWERCHANGE					=	-69567,				// �����ı�			int0 ԭ������ int1 ������
	NOTICE_ACCUSE_GATEATTACKED					=	-69566,				// ���ű�����		int0 ����ID

	NOTICE_KILLOFFICIAL							=	-69565,				// ɱ����Ա			int0 ɱ������Ӫ int1 ��ɱ����Ӫ int2 ���� int3 ��ְID string1 ɱ������ string2 ��ɱ����
	NOTICE_GETITEM								=	-69564	,			// ��ö���			int0 ��ҽ�ɫID int1 �����Ϊ0��Ϊ��������ȼ� int2 ��һ�õ���ƷID int3 ��һ�õ���Ʒ������ string0 �������
	NOTICE_BATTLE_WINNER						=	-69543,				// ֪ͨս��ʤ����	int0 ����ID		int1 ��ӪID int2 �ȼ� string1 ����
	NOTICE_BATTLE_NOWINNER						=   -69542,				// ֪ͨս����ʤ���� int0 ����ID     int1 �ȼ�

	NOTIFY_OPENITEM_SPECIAL1					=	-69541,				// ����������ʾ1	int0 CharID	int2 ItemID int3 Num string1 ����������
	NOTIFY_OPENITEM_SPECIAL2					=	-69540,				// ����������ʾ2
	NOTIFY_OPENITEM_SPECIAL3					=	-69539,				// ����������ʾ3
	NOTIFY_OPENITEM_SPECIAL4					=	-69538,				// ����������ʾ4
	NOTIFY_BATTLE_ONTIME_OPEN					=	-69537,				// ֪ͨ������ʱ���� int0 ����ID		int1 ��ͼID
	NOTIFY_BATTLE_CLOSE							=	-69536,				// ֪ͨ��������

	NOTIFY_OPENITEM_SPECIAL5					=	-69535,				// ����������ʾ5
	NOTIFY_OPENITEM_SPECIAL6					=	-69534,				// ����������ʾ6
	NOTIFY_OPENITEM_SPECIAL7					=	-69533,				// ����������ʾ7
	NOTIFY_OPENITEM_SPECIAL8					=	-69532,				// ����������ʾ8
	NOTIFY_OPENITEM_SPECIAL9					=	-69531,				// ����������ʾ9
	NOTIFY_OPENITEM_SPECIAL_MAX					=	-69430,				// ����������ʾ���ֵ

};

enum BOURSE_CODE
{
	BOURSE_DEC_NOTENOUGH_YB				= -79999,				// �ʻ�Ԫ������
	BOURSE_DEC_NOTENOUGH_MONEY			= -79998,				// �ʻ��ǰ󶨽���

	BOURSE_ACCOUNT_MONEY_MUCH			= -79997,				// �ʻ���Ǯ����
	BOURSE_ACCOUNT_YB_MUCH				= -79996,				// �ʻ�Ԫ������

	BOURSE_SUM_MONEY_MUCH				= -79995,
	BOURSE_SUM_YB_MUCH					= -79994,				// 

	BOURSE_MONEY_NOTENOUGH				= -79993,				// �ǰ󶨽���?
	BOURSE_YB_NOTENOUGH					= -79992,				// Ԫ������

	BOURSE_CANNT_FIND_DOC				= -79991,				// 

	BOURSE_BUY_LIST_MORE				= -79990,				// �����������ڻ����15
	BOURSE_SELL_LIST_MORE				= -79989,				// ���������ڻ����15
	
	BOURSE_BUY_NOTIFY					= -79988,				// ȫ����������֪ͨ
	BOURSE_SELL_NOTIFY					= -79987,				// ȫ��������֪ͨ
};

// ������Ϣ�� -80149 ~ -80100
enum ESpiritCode
{
	SPIRIT_OPEN_PRESLOT_NOTOPEN			= -80149,  // ǰ�ÿ�δ����
	SPIRIT_OPEN_SLOT_ALREADY_OPEN		= -80148,  // �ѿ���
	SPIRIT_OPEN_LACK_ITEM				= -80147,  // ������߲���
	SPIRIT_CASTING_SLOT_NOTOPEN			= -80146,  // ��δ����
	SPIRIT_CASTING_ALREADY				= -80145,  // �Ѿ�����
	SPIRIT_CASTING_LACK_ITEM			= -80144,  // ȱ���������
	SPIRIT_CASTING_TYPE_ERROR			= -80143,  // ����ϵ�𲻶�
	SPIRIT_CASTING_PLAYER_LEVEL_LOW		= -80142,  // ����ȼ�����
	SPIRIT_UPGRADE_LACK_ITEM			= -80141,  // ����������������
	SPIRIT_UPGARDE_LACK_UPGARDEIEM		= -80140,  // ����ȱ�پ�����
	SPIRIT_UPGARDE_LACK_MONEY			= -80139,  // ����ȱ�ٷǰ󶨽�
	SPIRIT_UPGARDE_INSERTNEW_ERROR		= -80138,  // ����������ʧ��
	SPIRIT_UPGRADE_ERROR				= -80137,  // ���鳣�����
	SPIRIT_DOWNGRADE_ERROR				= -80136,  // ���鳣�����
	SPIRIT_DOWNGARDE_LACK_DOWNGARDEIEM	= -80135,  // ����ȱ��������
	SPIRIT_DOWNGARDE_LACK_MONEY			= -80134,  // ����ȱ�ٷǰ󶨽�
	SPIRIT_DOWNGARDE_INSERTNEW_ERROR	= -80133,  // �������µ�����ʧ��
	SPIRIT_CASTING_ERROR				= -80132,  // ���鳣�����
	SPIRIT_UPGARDE_GRADE_ERROR			= -80131,  // ����ʱ������������Ѵ���߽׵ȣ�
};


////////////////////////////////gateserver 24xxx//////////////////////////
enum EGateServer
{
	// ��¼��������
	EGATE_THESCENE_ISNOT_ONLINE 		= -24001,	// ��¼��Ϸʧ��, ��ΪĿ�ĳ���δ����
	EGATE_TEMPLATE_ISNOTWITH_CLIENT		= -24002,	// ��¼��Ϸʧ�ܣ���Ϊ�ͻ�����������İ汾��һ��
	EGATE_PLAYERTOKEN_ISNOTAS_LOGIN		= -24003,	// ��¼��Ϸʧ��, ��Ϊ��¼���ص�TOKEN��LOGIN��TOKEN��һ��
	EGATE_PLAYER_ISCREATED_BYSCENE		= -24004,	// ��¼��Ϸʧ��, ������׼��������ݷ���ʧ��
	EGATE_ERATING_VERIFY_ENTERGAME_FAILURE	= -24005,	// ��¼��Ϸʧ��, ERating��֤��ҽ�����Ϸʧ��
	EGATE_ERATING_VERIFY_ENTERGAME_TIMEOUT 	= -24006,// ��¼��Ϸʧ��, ERating��֤��ҽ�����Ϸ��ʱ
	EGATE_PLAYER_STILLINGATE_TOLONG		= - 24007,	// ����ڳ�����ʱ����ã���������ǿ������
	EGATE_SCENE_VERIFY_ENTERGAME_TIMEOUT = -24008,
	EGATE_THESCENE_IS_FULLIST			= -24009,
	EGATE_PLAYER_WILL_DISCONNECT 		= -24010,
// �ظ���¼����
	EGATE_PLAYERSTATE_ISNOT_PERMITED 	= -24021,	// ��¼��Ϸʧ��, ��ǰ��ҵ�״̬�������¼
	EGATE_PLAYERSTATE_IS_REDIRECTING 	= -24022,	// ������ڿ糡����, �������ظ���¼
	EGATE_ROLE_ISNOT_LOGINEDROLE 		= -24023,	// �ظ���¼�Ľ�ɫ�����Ѿ��ڳ����Ľ�ɫ
	EGATE_PLAYER_ANOTHER_LOGIN			= -24024,	// �����Ϊ�����ط���¼����������
	EGATE_KICKOFFPLAYER_NOTIN_SCENE		= -24025,	// ��Ҫ�ߵ�����Ҳ�����Ӧ�ĳ���
	EGATE_KICKOFFPLAYERSTATE_NOT_PERMIT	= -24026,	// ��Ҫ�ߵ�������ڳ����е�״̬������������
	EGATE_KICKOFFPLAYER_TOOLONG_TIME    = -24027,

	// ������ɫ����
	EGATE_CREATECHAR_ON_DUPNAME 	= -24031,		// ������ɫʧ��, ��Ϊ��ɫ�����ظ�

	EGATE_CREATECHAR_ON_AGTIMEOUT 	= -24032, 		// ������ɫʧ��, ��ΪERating��ʱ
	EGATE_CREATECHAR_ON_DBTIMEOUT 	= -24033,		// ������ɫʧ��, ��ΪMYSQL��ʱ	

	EGATE_CREATECHAR_ON_LISTFULL 	= -24034,		// ������ɫʧ�ܣ���Ϊ��ɫ�б�����

	EGATE_CREATECHAR_ON_NOACCOUNT 	= -24035,		// ������ɫʧ�ܣ���Ϊ����ʺŲ�����

	EGATE_CREATECHAR_ON_DBSQL 		= -24036,		// ������ɫʧ�ܣ���Ϊ���ݿ�SQLִ��ʧ��
	EGATE_CREATECHAR_ON_AGDBSQL 	= -24037,		// ������ɫʧ��, ��ΪERating���ݿ�ִ��ʧ��
	EGATE_CREATECHAR_ON_AGCODE 		= -24038,		// ������ɫʧ��, ��ΪERating��������ʧ��


	EGATE_ROLENAME_DOES_EXIST 		= -24039,		// ������ɫʧ�ܣ���Ϊ��ɫ�����Ѿ�����	
	EGATE_ROLESEX_ISNOT_PERMITED 	= -24040,		// ������ɫʧ��, ��Ϊ��ɫ�Ա�Ƿ�
	EGATE_ROLENAME_IS_TOOLONG 		= -24041,		// ������ɫʧ�ܣ���Ϊ��ɫ���ƹ���
	EGATE_ROLENAME_HAS_INVALIDCHAR 	= -24042,		// ������ɫʧ��, ��Ϊ��ɫ�����к��зǷ��ַ�

	EGATE_CREATECHAR_ON_AGNOTOPEN 	= -24043,		// ������ɫʧ��, ��ΪERATING ����δ����
	EGATE_ROLECOUNTRY_ISNOT_PERMITED= -24044,		// ������ɫʧ��, ��Ϊ��ѡ���Ҵ������

	// ��ȡ��ɫ�б�����
	EGATE_ROLELIST_ON_DBTIMEOUT	= -24051,		// ��ȡ�б�ʧ�ܣ���ΪMYSQL��Ӧ��ʱ
	EGATE_ROLELIST_ON_AGTIMEOUT	= -24052,		// ��ȡ�б�ʧ�ܣ���ΪERating��Ӧ��ʱ
	EGATE_ROLELIST_ON_AGCODE	= -24053,		// ��ȡ�б�ʧ��, ��ΪERating����ʧ��
	EGATE_ROLELIST_ON_DBSQL		= -24054,		// ��ȡ�б�ʧ�ܣ���Ϊִ��MySQL���ʧ��
	EGATE_ROLELIST_ON_NOACCOUNT	= -24055,		// ��ȡ�б�ʧ��, ��Ϊ�ʺŲ�����
	EGATE_ROLE_DOESNOT_EXIST	= -24056,		// ��ɫ����Ч
	EGATE_ROLE_ENTERGAME_ONDELETESTATUS	= -24057,// ɾ���ȴ�״̬���ܽ�����Ϸ


	// ɾ����ɫ����
	EGATE_DELETEROLE_ON_USINGROLE 	= -24061,		// ɾ����ɫʧ��, ��Ϊ�˽�ɫ���ڱ�ʹ����
	EGATE_DELETEROLE_ON_NOACCOUT 	= -24062,		// ɾ����ɫʧ��, ��Ϊ��ɫ������

	EGATE_DELETEROLE_ON_DBSQL 		= -24063,		// ɾ����ɫʧ��, ��Ϊִ��SQL���ʧ��
	EGATE_DELETEROLE_ON_DBTIMEOUT 	= -24064,		// ɾ����ɫʧ��, ��Ϊִ��SQL��䳬ʱ

	EGATE_DELETEROLE_ON_AGTIMEOUT 	= -24065,		// ɾ����ɫʧ��, ��ΪERATING ��Ӧ��ʱ
	EGATE_DELETEROLE_ON_AGCODE 		= -24066,		// ɾ����ɫʧ��, ��ΪERATING������������
	EGATE_DELETEROLE_ON_AGDBSQL 	= -24067,		// ɾ����ɫʧ��, ��ΪERATING�������ݿ����ʧ��
	EGATE_DELETEROLE_ON_AGNOTOPEN	= -24068,		// ɾ����ɫʧ�ܣ���ΪERATING������֤δ����

	EGAME_SCENESERVER_MAP_NOT_EXIST	= -24083,		// ������Ϸʱ����ͼ������	
	EGAME_DELETEROLE_ON_FAMILYHEADER= -24082,		// ɾ����ɫʧ�ܣ��������첻��ɾ����ɫ
	EGAME_SCENESERVER_IS_FULLLIST	= -24081,		// ������������
	EGAME_SCENESERVER_MAP_IS_EMPTY  = -24080,		// ��ͼ����ʧ��
	
	EGAME_DELETEROLE_DELETEPROTECT  = -24079,		// ɾ����ɫʱ��ɫ����ɾ������״̬
	EGAME_DELETEROLE_DELETECOOLTIME = -24078,		// ɾ����ɫʱ��ɫ����ɾ��������ȴ״̬
	EGAME_DELETEROLE_DELETESUCCESS  = -24077,		// ɾ����ɫ�ɹ�����ʼ���ڽ�ɫ��ȴʱ��
	EGAME_DELETEROLE_WRONGPASSWORD  = -24076,		// ��ɫ���벻��ȷ

   // 100310 MAOCY ADD-BEGIN
   EGATE_ROLE_QUESTION_FAILURE     = -24090,		// ��ɫ��¼������֤ʧ�ܡ�
   // 100310 MAOCY ADD-END
};

////////////////////////////////loginserver 21xxx //////////////////////////
enum ELoginServer
{
	ELOGIN_THEWORLD_ISNOT_OPEN			= -21001,		// ��¼ʧ��, ����δ����
	ELOGIN_TEMPLATE_ISNOTWITH_CLIENT	= -21002,		// ��¼ʧ��, ģ��汾��ͻ��˲�һ��
	ELOGIN_THEWORLD_IS_FULLLIST			= -21003,		// ��¼ʧ��, ���������Ѿ��ﵽ����
	ELOGIN_USERNAME_DOESNOT_EXIST		= -21004, 		// ��¼ʧ��, �ʺŲ�����
	ELOGIN_USERPSW_DOESNOT_MATCH		= -21005,		// ��¼ʧ��, ���벻ƥ��
	ELOGIN_USER_IN_OTHERWORLD			= -21006,		// �ǳ�ʧ��, ����Ѿ���¼��������Ϸ����
	ELOGIN_PLAYER_IS_FROZEN				= -21007,		// ��¼ʧ��, ����ʺű�����
	ELOGIN_VERIFY_ON_AGDBSQL			= -21008,		// ��¼ʧ��, ERATINGУ��ִ��SQL���ʧ��, ʹ�ñ�����֤
	ELOGIN_VERIFY_ON_AGCODE				= -21009,		// ��¼ʧ��, ERATINGУ��δͨ��, ����ʹ�ñ�����֤
	ELOGIN_PLAYER_IN_LOGINING			= -21010,		// ��¼��Ϸʧ��, ��Ϊ������ڵ�¼������	
	ELOGIN_PLAYER_IN_RELOGINING			= -21011,		// ��¼��Ϸʧ��, ��������ظ���¼������
	ELOGIN_DBSESSION_IS_FULL			= -21012,		// ��¼��Ϸʧ��, ��ΪĿǰϵͳ����������ݿ��Session�ﵽ����
	ELOGIN_VERIFY_ON_DBSQL				= -21013,		// ��¼��Ϸʧ��, ���ݿ�ִ����֤��SQL���δִ�гɹ�
	ELOGIN_PLAYER_IN_GAMING				= -21014,		// ��¼��Ϸʧ�ܣ���Ϊ����Ѿ�����Ϸ��
	ELOGIN_VERIFY_BYMYSQL_TIMEOUT		= -21015,		// ��¼��Ϸʧ��, ��Ϊ������֤��ʱ
	ELOGIN_VERIFY_BYERATING_TIMEOUT		= -21016,		// ��¼��Ϸʧ��, ��Ϊ������֤��ʱ
	ELOGIN_CLIENT_VERSION_NOTMATCH 		= -21017, 		// �ͻ��˰汾���������ƥ��
	ELOGIN_SERVER_BE_MAINTENANCE		= -21018,		// ������ά���У���ʱ���ܵ�¼
	ELOGIN_CLIENT_MD5CODE_NOTMATCH 		= -21019, 		// �ͻ��˴����MD5����ȷ
	ELOGIN_CLIENT_NEED_MATRIXCODE		= -21020,		// ��Ҫ�ͻ��˴��붯̬�ܱ���
	ELOGIN_CLIENT_NEED_STATICMATRIXCODE	= -21021,		// ��Ҫ�ͻ��˴����ܱ���
	ELOGIN_CLIENT_NOTIN_LIMITIP			= -21022,		// û���ڰ�IP��ַ��½
};
///////////////////////////////

// ȫ�ַ�����23xxx
enum EDungeonErr
{
	EDUNGEON_ERROR_LEVELLOW			= -23999,		// ����ʱ�ȼ�����
	EDUNGEON_ERROR_SERVERNOTOPEN	= -23998,		// ����ʱȫ�ָ���������û��
	EDUNGEON_ERROR_NOTAPPLIED		= -23997,		// û�б������ܽ�����ս��
	EDUNGEON_ERROR_HASAPPLIED		= -23996,		// �Ѿ��������ܽ���ս��
	EDUNGEON_ERROR_MAXAPPLYNUM		= -23995,		// ���������Ѵ�����
	EDUNGEON_ERROR_APPLYTIMEOUT		= -23994,		// ���볬ʱ
	EDUNGEON_ERROR_CREATEREPETIONERR= -23993,		// �޷�����ս��
	EDUNGEON_ERROR_MAPFULL			= -23992,		// ��ͼ����
	EDUNGEON_ERROR_NOPLACEACTION	= -23991,		// �˵�ͼ�޷����д˲���
	EDUNGEON_ERROR_CANNOTGLOBALTELE = -23990,		// ��ǰ������Ҳ��ܴ��͵�ȫ�ַ�����
	EDUNGEON_ERROR_DEATH			= -23989,		// ����״̬���ܽ�����ս��
	EDUNGEON_ERROR_HASESCAPEBUFF	= -23988,		// ������buff���ܱ���
	EDUNGEON_ERROR_HASTIMELIMITBUFF	= -23987,		// ��ʱ�����Ƶ�buff���ܱ���(������ʿbuff)
};

enum ChangeCamp
{
	ERROR_CHANGE_CAMP_NO_HAVE_ITEM			= -80001,	//�ж��Ƿ���ת��Ӫ����	
	ERROR_CHANGE_CAMP_IN_CD					= -80002,	//�ж��Ƿ���ת��Ӫcd
	ERROR_CHANGE_CAMP_IN_SAME				= -80003,	//�Ƿ� �� ת��ԭ����Ӫ
	ERROR_CHANGE_CAMP_IN_BEST				= -80004,	//�ж�ת����Ƿ�����ǿ��Ӫ
	ERROR_CHANGE_CAMP_IN_TEAM				= -80005, 	//�ж��Ƿ������
	ERROR_CHANGE_CAMP_IN_FAMILY				= -80006,	//�ж��м���
	ERROR_CHANGE_CAMP_IN_COUNTRY			= -80007,	//�ж��Ƿ��й���	
	ERROR_CHANGE_CAMP_IN_MASTER_PRENTICE	= -80008,	//�ж��Ƿ���ʦͽ
	ERROR_CHANGE_CAMP_IN_MARRIAGE			= -80009,	//�ж��Ƿ��н��
	ERROR_CHANGE_CAMP_IN_PAYMAIL			= -80010,	//�ж��Ƿ��и����ʼ�
	ERROR_CHANGE_CAMP_IN_AUCTION			= -80011,	//�ж��Ƿ�������
	ERROR_CHANGE_CAMP_NO_CAMP				= -80012,   //ԭʼ����Ӫ ����ת��
	ERROR_CHANGE_CAMP_IN_TRDE				= -80013,   //���ڽ��ף��޷�ת��Ӫ
	ERROR_CHANGE_CAMP_NO_ENOUGH_LEVEL       = -80014,   //�ȼ�û�дﵽ30������
	ERROR_CHANGE_CAMP_INSWORNTEAM			= -80015,   //�н�ݲ���ת��Ӫ

};
//��������
enum  RuneCom
{
	ERROR_RUNE_COM_LOSE				 = -80050,//�������� ʧ��
};
//ת������ʧ��
enum  RuneChange
{
	ERROR_RUNE_CHANGE_ERROR			 = -80060,//ת������ʧ��
	ERROR_RUNE_STORE				 = -80061,//�������Ĳ���ת��
};

#endif









