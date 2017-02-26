#ifndef _LOG_TOOLS_H_
#define _LOG_TOOLS_H_

#include "log_msg_pb.hxx.pb.h"
#include "message_pb.hxx.pb.h"
#include "linux/types.h"

CMessage* BuildFamilyLogMessage(uint32_t nFamilyID, uint32_t nOpRoleID, 
		EOrganAction emAction, EFamilyAttr nAttrID, int nParam1, int nParam2,int nParam3 = 0 );

CMessage* BuildCorpsLogMessage(uint32_t nCorpsID, uint32_t nOpRoleID, 
		EOrganAction emAction, ECorpsAttr nAttrID, int nParam1, int nParam2, int nParam3 = 0 );

CMessage* BuildWorldLogMessage(int nWorldID, int nAction, int nParam1, int nParam2, int nParam3 = 0 );

void LogFamilyAction(uint32_t nFamilyID, uint32_t nOpRoleID, 
		EOrganAction emAction, EFamilyAttr nAttrID, int nParam1, int nParam2, int nParam3 = 0 );

void LogCorpsAction(uint32_t nCorpsID, uint32_t nOpRoleID, 
		EOrganAction emAction, ECorpsAttr nAttrID, int nParam1, int nParam2, int nParam3 = 0 );

void LogWorldAction(int nWorldID, int nAction, int nParam1, int nParam2, int nParam3 = 0);
		

// ��¼������Ϣ
void LogChatMsg( int nRoleID, const char* szRoleName, const char* szMsg, int nGateWayID, int nChannel, int nIP = 0 );



// - ��Ա����
#define  LogMemberJoin( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_MEMBERJOIN, EM_FAMILY_MEMBER, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_MEMBERJOIN, EM_CORPS_MEMBER, nParam1, nParam2, nParam3 ); }	

// - ��Ա�뿪
#define  LogMemberLeave( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_MEMBERLEAVE, EM_FAMILY_MEMBER, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_MEMBERLEAVE, EM_CORPS_MEMBER, nParam1, nParam2 ); }

// - ����(����)���� (AGIP)
#define  LogOrganCreate( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_CREATE, EM_FAMILY_MEMBER, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_CREATE, EM_CORPS_MEMBER, nParam1, nParam2 ); } 

// - ����(����)��ɢ
#define  LogOrganDisband( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY )  \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_DISBAND, EM_FAMILY_MEMBER, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )			 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_DISBAND, EM_CORPS_MEMBER, nParam1, nParam2 ); } 

// - ���ļ���(����)��Ǯ
#define  LogOrganGetMoney( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY )\
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_GETMONEY, EM_FAMILY_MONEY, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_GETMONEY, EM_CORPS_MONEY, nParam1, nParam2 ); } 

// - ���׼���(����)��Ǯ
#define  LogOrganContributeMoney( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_CONTRIBUTEMONEY, EM_FAMILY_MONEY, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_CONTRIBUTEMONEY, EM_CORPS_MONEY, nParam1, nParam2 ); } 

// - �������(����)��Ʒ(���)
#define  LogOrganBuyItem( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_BUYITEM, EM_FAMILY_MONEY, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_BUYITEM, EM_CORPS_MONEY, nParam1, nParam2 ); } 

// - ����(����)����
#define  LogOrganLevelUP( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_LEVELUP, EM_FAMILY_LEVEL, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_LEVELUP, EM_CORPS_LEVEL, nParam1, nParam2 ); } 

// - ���������������ļ����Ǯ�ı�
#define  LogOrganMoneyByLevelUP( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_LEVELUP, EM_FAMILY_MONEY, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_LEVELUP, EM_CORPS_MONEY, nParam1, nParam2 ); } 


// - ����(����)ְλ�趨
#define  LogOrganSetPost( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_SETPOST, EM_FAMILY_RANK, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_SETPOST, EM_CORPS_RANK, nParam1, nParam2, nParam3 ); }	

// - ��ȡ����(����)npc����	
#define  LogOrganGetNpcWelfareMoney( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_GETNPCWELFARE, EM_FAMILY_MONEY, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_GETNPCWELFARE, EM_CORPS_MONEY, nParam1, nParam2, nParam3 ); } 

#define  LogOrganGetNpcWelfareGlory( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
	if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_GETNPCWELFARE, EM_FAMILY_GLORY, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_GETNPCWELFARE, EM_CORPS_GLORY, nParam1, nParam2, nParam3 ); } 


// - ���׽�Ǯ�ı����(����)���׶�
#define  LogOrganContributeByContribute( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_CONTRIBUTEMONEY, EM_FAMILY_CONTRIBUTION, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_CONTRIBUTEMONEY, EM_CORPS_CONTRIBUTION, nParam1, nParam2 ); } 


// - ����ı���壨���ţ���Ǯ
#define  LogOrganMoneyByTask( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_TASK, EM_FAMILY_MONEY, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_TASK, EM_CORPS_MONEY, nParam1, nParam2 ); } 


// - ʹ�ù�������Ʒ�ı���壨���ţ���Ǯ
#define  LogOrganMoneyByUseFunItem( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
	if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_USEFUNCITEM, EM_FAMILY_MONEY, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_USEFUNCITEM, EM_CORPS_MONEY, nParam1, nParam2 ); } 


// - ʹ�ù�������Ʒ�ı��������ֵ
#define LogOrganRefineValueByUseFunItem( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_CORPS )\
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_USEFUNCITEM, EM_CORPS_REFINEVALUE, nParam1, nParam2 ); }

// - �ٻ�����boss���ľ�������ֵ
#define LogOrganRefineValueBySummonBoss( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_CORPS )\
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_SUMMONCORPSBOSS, EM_CORPS_REFINEVALUE, nParam1, nParam2 ); }

// - ��ɾ���fb�������Ż���
#define LogOrganCorpsScoreByCorpsFb( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_CORPS )\
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_CORPSREPETION, EM_CORPS_SCORE, nParam1, nParam2 ); }

// - ��ɾ��ţ��ɼ�������ı���ţ��ɼ�����Ծ��
#define LogOrganCorpsActivityByTask( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_CORPS )\
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_TASK, EM_CORPS_ACTIVITY, nParam1, nParam2 ); }

// - ����ı����(����) ���˹��׶�
#define  LogOrganContribteByTask( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_TASK, EM_FAMILY_CONTRIBUTION, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_TASK, EM_CORPS_CONTRIBUTION, nParam1, nParam2 ); }

// - ����һ��ı����(����) ���˹��׶�
#define  LogOrganContribteByExchange( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_EXCHANGE, EM_FAMILY_CONTRIBUTION, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_EXCHANGE, EM_CORPS_CONTRIBUTION, nParam1, nParam2 ); }
 
// - ����/���Ŷ�NPC����
#define  LogBidNpc( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_BID_, EM_FAMILY_BATTLE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_BID_, EM_CORPS_BATTLE, nParam1, nParam2, nParam3 ); }

// - ���۽����¼�
#define  LogConfirm( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_CONFIRM, EM_FAMILY_BATTLE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_CONFIRM, EM_CORPS_BATTLE, nParam1, nParam2, nParam3 ); }

// - NPC����ս��ս
#define  LogJoinNPCBattle( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_JOIN_BATTLE, EM_FAMILY_BATTLE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_JOIN_BATTLE, EM_CORPS_BATTLE, nParam1, nParam2, nParam3 ); }

// - NPC����ս����
#define  LogNPCFin( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_FIN, EM_FAMILY_BATTLE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_FIN, EM_CORPS_BATTLE, nParam1, nParam2, nParam3 ); }

// - ������NPC/�ǳص�ռ��
#define  LogAbort( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_ABORT, EM_FAMILY_BATTLE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_ABORT, EM_CORPS_BATTLE, nParam1, nParam2, nParam3 ); }

// - ������ս������
#define  LogOpenRoom( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_OPEN_ROOM, EM_FAMILY_CHANLENGE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_OPEN_ROOM, EM_CORPS_CHANLENGE, nParam1, nParam2, nParam3 ); }

// - �ر���ս������
#define  LogCloseRoom( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_CLOSE_ROOM, EM_FAMILY_CHANLENGE, nParam1,  nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_CLOSE_ROOM, EM_CORPS_CHANLENGE, nParam1,  nParam2, nParam3 ); }

// - ������ս����
#define  LogSendChallege( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_SEND_CHALLEGE, EM_FAMILY_CHANLENGE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_SEND_CHALLEGE, EM_CORPS_CHANLENGE, nParam1, nParam2, nParam3 ); }

#define  LogRecChallege( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_REC_CHALLEGE, EM_FAMILY_CHANLENGE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_REC_CHALLEGE, EM_CORPS_CHANLENGE, nParam1, nParam2, nParam3 ); }

// - ͬ����ս����
#define  LogJoinChaBattle( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_JOIN_BATTLE, EM_FAMILY_CHANLENGE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_JOIN_BATTLE, EM_CORPS_CHANLENGE, nParam1, nParam2, nParam3 ); }

#define  LogSubmit( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_SUBMIT, EM_FAMILY_BATTLE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_SUBMIT, EM_CORPS_BATTLE, nParam1, nParam2, nParam3 ); }

// - �����������ս����
#define  LogCloseChallenge( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_ABORT, EM_FAMILY_CHANLENGE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_ABORT, EM_CORPS_CHANLENGE, nParam1, nParam2, nParam3 ); }



// - ������ɻ�þ���
#define  LogGlroyByTask( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_TASK, EM_FAMILY_GLORY, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_TASK, EM_CORPS_GLORY, nParam1, nParam2, nParam3 ); }

// - ����Ʒ���Ҽ��ټ��徭��
#define  LogGlroyByRepetion( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_REPETION, EM_FAMILY_GLORY, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_REPETION, EM_CORPS_GLORY, nParam1, nParam2, nParam3 ); }

// - ������帱�����ټ����Ǯ
#define  LogOrganMoneyByRepetion( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_REPETION, EM_FAMILY_MONEY, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_REPETION, EM_CORPS_MONEY, nParam1, nParam2, nParam3 ); }

// - NPC������ʤ��
#define  LogOrganBattleVictory( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_BATTLEVICTORY, EM_FAMILY_BATTLE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_BATTLEVICTORY, EM_CORPS_BATTLE, nParam1, nParam2, nParam3 ); }

// - ��ս��ʤ��
#define  LogOrganChallengeVictory( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
	if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_BATTLEVICTORY, EM_FAMILY_CHANLENGE, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_BATTLEVICTORY, EM_CORPS_CHANLENGE, nParam1, nParam2, nParam3 ); }


// - ��ȡ�����ڵ���������ʱû��
#define  LogOrganStartRedstone( LogType, nRganID, nOpRoleID, nParam1, nParam2, nParam3 ) \
	if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_REDSTONE, EM_FAMILY_NULL, nParam1, nParam2, nParam3 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_REDSTONE, EM_CORPS_NULL, nParam1, nParam2, nParam3 ); }

#endif

// - ������˰��������ʱû��	
#define  LogOrganGetTax( LogType, nRganID, nOpRoleID, nParam1, nParam2 ) \
if( LogType == ORGANLOGTYPE_FAMILY ) \
{ LogFamilyAction(nRganID, nOpRoleID, EM_ORGAN_TAX, EM_FAMILY_MONEY, nParam1, nParam2 ); }	\
else if( LogType == ORGANLOGTYPE_CORPS )				 \
{ LogCorpsAction(nRganID, nOpRoleID, EM_ORGAN_TAX, EM_CORPS_MONEY, nParam1, nParam2 ); }
