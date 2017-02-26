#pragma once

#include "logservertype.h"
#include "servertool.h"
#include "log_msg_pb.hxx.pb.h"

class CEntity;
class CEntityNpc;
class CEntityPlayer;
class CMessage;
class CMessageCreatePlayerProNotice;
class CMessageCreateNpcProNotice;
class CItemObject;
class CTplItem;
class CWTPoint;

// Ϊ�˱�֤Build��������Ϣ���ᳬ��Buff(32k)��С����ĳЩ�����ϢҪ�����ƣ�������ְ�����
#define MAX_NPC_NUM_OF_CREATE_MSG		256	// BuildCreateNpcProMessage ��һ�δ����NPC��Ϣ����
#define MAX_PLAYER_NUM_OF_CREATE_MSG	128	// BuildCreatePlayerProMessage ��һ�δ����player��Ϣ����


// �������������Ϣ
void SetPlayerProMessageForSinglePlayer( CEntityPlayer* pPlayer, CMessageCreatePlayerProNotice& rCreatePlayerProMsg );
CMessage* BuildCreatePlayerProMessage(std::vector<CEntityPlayer*>* pPlayerSet);
CMessage* BuildCreatePlayerProMessage(CEntityPlayer* pPlayer);

// ��������npc��Ϣ
void SetNpcProMessage( CEntity* pEntity, CMessageCreateNpcProNotice& rCreatNpcProMsg, int nListID, CEntityPlayer* pSelf );
CMessage* BuildCreateNpcProMessage(std::vector<CEntity*>* pNpcSet, int vListID = 0, CEntityPlayer* pSelf = NULL );
CMessage* BuildCreateNpcProMessage(CEntity* pEntity, int vListID = 0, CEntityPlayer* pSelf = NULL );

// ��������ʵ����Ϣ
CMessage* BuildDestroyEntityMessage( CEntity* pEntitySelf );
CMessage* BuildDestroyEntityMessage( std::vector<CEntityPlayer*>* pPlayers, std::vector<CEntity*>* pNpcs );

// ����ʵ���ƶ���Ϣ
CMessage* BuildEntityPathMessage( CEntity* pEntity, const CWTPoint& rSrcPos, const CWTPoint& rDstPos );

// �����������Ϣ
CMessage* BuildFuncResultMessage( CEntity* pEntity, unsigned short vFunc, unsigned short vResult, int vListID, unsigned int vValue1, unsigned int vValue2, unsigned int vValue3 = 0, unsigned int vValue4 = 0, unsigned int vValue5 = 0 );

// �����ı�״̬����Ϣ
CMessage* BuildChangeStateNoticeMessage(unsigned int vEntityID, int vState, int vParame1, int vParame2, bool vInState );


// Exp
CMessage* BuildPlayerOpExpLogMessage( CEntityPlayer* pPlayer, 
		EUpgradeType emType, uint64_t nCurrent, int nDelta, int nOpType, int nParam1, int nParam2, uint64_t ullParam3);

// Item
CMessage* BuildPlayerOpItemLogMessage( CEntityPlayer* pPlayer, uint64_t ullGuID, 
		int nItemID, int nItemNum, int nTotal, EItemAction emAction, int nParam1, int nParam2, uint64_t ullParam3);

// Money
CMessage* BuildPlayerOpMoneyLogMessage( CEntityPlayer* pPlayer, int nUnit, int nDelta, 
		EMoneyAction emAction, int nParam1 , int nParam2 , uint64_t ullParam3 );

// Buff

CMessage* BuildPlayerBuffLogMessage( CEntityPlayer* pPlayer, int BuffID, int PersistTime, 
		 int nParam1 , int nParam2 , unsigned short bufftype );

// Logout
CMessage* BuildPlayerLogoutMessage( CEntityPlayer* pPlayer, EMLeaveReason emLeave, EMSaveResult emSave);

// Killed
CMessage* BuildPlayerBeKilledLogMessage( CEntityPlayer* pPlayer, 
		int nKillerType, int nKillerID, int nKillerMetier, int nKillerLevel);

// Task
CMessage* BuildPlayerOpTaskLogMessage( CEntityPlayer* pPlayer, 
		int nTaskID, ETaskAction emAction, int nParam1, int nParam2, uint64_t ullParam3 );

// NpcDrop
CMessage* BuildNpcDropLogMessage( CEntityNpc* pDropingEntity, std::vector<CEntity*>& rDropedEntityVec);

// UseItemDrop
CMessage* BuildUseItemDropLogMessage( CEntityPlayer* pPlayer, int nItemID, std::vector<CEntity*>& rDropedEntityVec );

// RoleLevelUp
CMessage* BuildPlayerLevelUpLogMessage( CEntityPlayer* pPlayer, EUpgradeType emUpgrade, int SubType, int nCurrentLevel, int nLevel);


// EntityDispear
CMessage* BuildDropedItemDestroyLogMessage(CEntity* pEntity);

// ItemLevelUp
CMessage* BuildItemLevelUpLogMessage(CEntityPlayer* pPlayer, 
		int nItemID, uint64_t ullGUID, int nType, int nResult, int nCurrLevel, int nPrevLevel, int nItem1, int nItem2);
