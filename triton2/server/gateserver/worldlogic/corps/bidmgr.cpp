//================================================================================
// bidmgr.cpp
//================================================================================
#include "bidmgr.h"

#include "battlemgr.h"
#include "corpstype.h"	 
#include "corpsmanager.h"
#include "corps.h"
#include "corpservice.h"
#include "gatelogic.h"
#include "log_tools.h"
#include "world.h"

//using namespace GateServer;

//-------------------------------------------------------------------------

CSharedMem *CBidMgr::mShmPtr = NULL;
template<> CBidMgr * CSingleton< CBidMgr >::spSingleton = NULL;

//-------------------------------------------------------------------------
CBidMgr::CBidMgr()
{
	if( CObj::msCreateMode ) 
	{
		Initialize();
	}
	else
	{
		Resume();
	}
}
//-------------------------------------------------------------------------
CBidMgr::~CBidMgr()
{
	;
}
//-------------------------------------------------------------------------
int CBidMgr::Initialize( )
{
	m_NpcStatusMap.initailize();
	m_BidInfoList.initailize();
	return 0;
}
//-------------------------------------------------------------------------
int CBidMgr::Resume( )
{
	return 0;
}//-------------------------------------------------------------------------
void* CBidMgr::operator new( size_t size )
{
	return ( void* ) mShmPtr->CreateSegment( size );
}
//-------------------------------------------------------------------------
void  CBidMgr::operator delete( void* pointer )
{

}
//-------------------------------------------------------------------------
unsigned int CBidMgr::CountSize()
{
	return sizeof(CBidMgr);
}


/// ����ָ��Npc�ľ����б�
int CBidMgr::GetBidListByNpcID(int nNpcID, int* pnCorpsList, int* pnBidMoney, int& nNum)
{
	if (pnCorpsList == NULL || pnBidMoney == NULL)
	{
		return -1;
	}

	int tSize = nNum; 
	nNum = 0;
	BidInfoList::iterator it = m_BidInfoList.begin();
	//
	for ( ; it != m_BidInfoList.end(); ++ it )
	{
		if ( it->m_NpcID == nNpcID && 
			nNum < tSize && 
			DataTag_Del != it->m_SynTag )
		{
			pnCorpsList[nNum] = it->m_CorpsID;
			pnBidMoney[nNum] = it->m_BidMoney;
			nNum ++;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// ���س���NPC�ı�ռ���߾���ID
int CBidMgr::FindNpcOwnerByNpcID(int nGateNpcID)
{
	NpcStatusMap::iterator it = m_NpcStatusMap.find(nGateNpcID);
	if ( it == m_NpcStatusMap.end() )
	{
		return 0;
	}
	else
	{
		return (it->second).m_OwnerID;
	}
}


// ��ȡNPC״̬��Ϣ
NpcStatus* CBidMgr::GetNpcStatus(int nGateNpcID)
{
	NpcStatusMap::iterator it = m_NpcStatusMap.find(nGateNpcID);
	if ( it == m_NpcStatusMap.end() )
	{
		return NULL;
	}
	else
	{
		return &(it->second);
	}
}

///ƴװ���ŵ�����ս״̬���ԣ����ڲ�ѯ
void CBidMgr::MakeCorpsBattleState(int nCorpsID, CorpsProperty* pProperty)
{
	NpcStatusMap::iterator it_npc = m_NpcStatusMap.begin();
	for ( ; it_npc != m_NpcStatusMap.end(); ++ it_npc )
	{
		int GateNpcID = it_npc->first;
		
		NpcStatus* tpNpcStat = &(it_npc->second);
		int OwnerID = tpNpcStat->m_OwnerID;
		int StateCode = tpNpcStat->m_Status;

		//�Ȱѱ��Ϊfalse��ȷ���뱾�����йغ��ٱ��Ϊtrue
		//��forѭ�������������뱾�����޹صĶ��ѱ��Ϊfalse
		tpNpcStat->m_TmpTag = false;
		
		if (StateCode != NpcStatus::STATE_BidOpen)
		{
			//�Ǿ��۽׶�
			int AttCorpsID;
			int DefCorpsID;
			int MapID;
			int retcode;
			retcode = CBattleMgr::GetSingleton().GetBattle(
				GateNpcID, 
				AttCorpsID,
				DefCorpsID,
				MapID);
			if (-1 == retcode)
			{
				//û��ս�����ݣ�
				if (OwnerID == nCorpsID && StateCode > NpcStatus::STATE_MaxValue)
				{
					//δս��ʤ�������ռ��óǳأ����ھ��ۻָ�����ʱ��
					PBCorpsBattle* tpBattleInfo = pProperty->add_battleinfo();
					tpBattleInfo->set_npcid( SCENENPCID_2(GateNpcID) );
					tpBattleInfo->set_npcstatus( STATE_OWN );
					tpBattleInfo->set_warstatus( STATE_BIDDING );//�˴�Ӧ�Ľ������Ӿ��۹ر�״̬

					tpNpcStat->m_TmpTag = true;
					tpNpcStat->m_TmpBidMoney = 0;
					tpNpcStat->m_TmpDesCorpID = 0;
					tpNpcStat->m_TmpNpcStat = STATE_OWN;
					tpNpcStat->m_TmpWarStat = STATE_BIDDING;

				}
			}
			else if (AttCorpsID == nCorpsID ||
				DefCorpsID == nCorpsID )
			{
				//��ս�����������ڲ�ս��
				PBCorpsBattle* tpBattleInfo = pProperty->add_battleinfo();
				tpBattleInfo->set_npcid( SCENENPCID_2(GateNpcID) );
				
				tpNpcStat->m_TmpTag = true;
				tpNpcStat->m_TmpBidMoney = 0;
					
				if (OwnerID == nCorpsID)
				{
					//ԭ����ռ��
					tpBattleInfo->set_npcstatus( STATE_OWN );
					tpNpcStat->m_TmpNpcStat = STATE_OWN;
				}
				else
				{
					//ԭ��δռ��
					tpBattleInfo->set_npcstatus( STATE_CHAZING );
					tpNpcStat->m_TmpNpcStat = STATE_CHAZING;
				}
				
				if (0 == retcode) 
				{
					//��δ��ս
					tpBattleInfo->set_warstatus( STATE_SUBMITTING );
					tpNpcStat->m_TmpWarStat = STATE_SUBMITTING;
				}
				else if (1 == retcode)
				{
					//ս����
					tpBattleInfo->set_warstatus( STATE_FIGHTING );
					tpNpcStat->m_TmpWarStat = STATE_FIGHTING;
				}

				//ȡ����ս��������
				CCorps* tpCorps = NULL;
				int nBattleCorpsID = (nCorpsID == AttCorpsID) ? DefCorpsID : AttCorpsID;
				tpCorps = CCorpsManager::GetSingleton().GetCorpsByID(nBattleCorpsID);
				if ( tpCorps != NULL )
				{
					tpBattleInfo->set_descorpsname( tpCorps->GetCorpsName() );
				}

				tpNpcStat->m_TmpDesCorpID = nBattleCorpsID;
			}				
		}
		else if ( OwnerID == nCorpsID )
		{
			//���۽׶�����ռ�еĳǳ�
			PBCorpsBattle* tpBattleInfo = pProperty->add_battleinfo();
			tpBattleInfo->set_npcid( SCENENPCID_2(it_npc->first) );
			tpBattleInfo->set_npcstatus( STATE_OWN );
			tpBattleInfo->set_warstatus( STATE_BIDDING );
			
			tpNpcStat->m_TmpTag = true;
			tpNpcStat->m_TmpBidMoney = 0;
			tpNpcStat->m_TmpDesCorpID = 0;
			tpNpcStat->m_TmpNpcStat = STATE_OWN;
			tpNpcStat->m_TmpWarStat = STATE_BIDDING;
		}
	}

	//���뾺�۵ĳǳ�
	BidInfoList::iterator it_bid = m_BidInfoList.begin();
	for ( ; it_bid != m_BidInfoList.end(); ++ it_bid )
	{
		if (it_bid->m_CorpsID == nCorpsID && DataTag_Del != it_bid->m_SynTag)
		{
			NpcStatus* tpNpcStat = GetNpcStatus(it_bid->m_NpcID);
			if (NULL == tpNpcStat)
			{
				//LOGERR
				continue;
			}
			PBCorpsBattle* tpBattleInfo = pProperty->add_battleinfo();
			tpBattleInfo->set_npcid( SCENENPCID_2(it_bid->m_NpcID) );
			tpBattleInfo->set_npcstatus( STATE_CHAZING );
			tpBattleInfo->set_warstatus( STATE_BIDDING );

			tpNpcStat->m_TmpTag = true;
			tpNpcStat->m_TmpBidMoney = it_bid->m_BidMoney;
			tpNpcStat->m_TmpDesCorpID = 0;
			tpNpcStat->m_TmpNpcStat = STATE_CHAZING;
			tpNpcStat->m_TmpWarStat = STATE_BIDDING;
		}
	}
}

void CBidMgr::SetNpcStatusBegin()
{
	m_itNpcTmp = m_NpcStatusMap.begin();
}

NpcStatus* CBidMgr::GetOneNpcTmpState()
{
	if (m_itNpcTmp == m_NpcStatusMap.end())
	{
		return NULL;
	}
	NpcStatus* pNpc = &(m_itNpcTmp->second);
	m_itNpcTmp ++;
	return pNpc;
}

// �����ռ��ĵ�ͼ�б�
int CBidMgr::OnGetBattleMapList( int* npList, int* npCorspList, int& nNum, int nServerID )
{
	if ( npList == NULL )
	{
		return -1;
	}

	int tSize = nNum; nNum = 0;
	NpcStatusMap::iterator it = m_NpcStatusMap.begin();
	for ( ; it != m_NpcStatusMap.end(); ++ it )
	{
		CCorps* tpCorps = CCorpsManager::GetSingleton().GetCorpsByID((it->second).m_OwnerID);
		if ( tpCorps == NULL )
			continue;

		if ( tpCorps->GetCorpsCountryID() != nServerID )
			continue;

		NpcStatus* pNpc = &(it->second);
		int tMapID = SCENENPCID( pNpc->m_MapID, nServerID );
		if ( tMapID != INVALID_MAP_ID && nNum < tSize )
		{
			npList[ nNum ] = tMapID;  
			npCorspList[ nNum ] = pNpc->m_OwnerID;
			nNum ++;
		}
	}

	return SUCCESS;
}

//-------------------------------------------------------------------------
// �Ծ���սNPC����
int CBidMgr::BidForBattle(CCorps* pCorps,  int nRoleID, int nNpcID, int nMapID, int nBidMoney)
{
	
	LOG_DEBUG("corps", "[%d] TryBidForBattle NPC[%d] $[%d]", pCorps->GetCorpsID(), nNpcID, nBidMoney);
	
	//���NPC״̬�����ڣ���ʼ��һ��
	int ret = PreSetNpcState(nNpcID);
	if (ret)
	{
		return ret;
	}
	//ȡ��NPC״̬
	NpcStatusMap::iterator it_npc = m_NpcStatusMap.find(nNpcID);
	NpcStatus* pNpcStat = NULL;
	if ( it_npc == m_NpcStatusMap.end() )
	{
		LOG_ERROR("corps", "Get bid request for invalid NPC");
		return -1;
	}
	else
	{
		pNpcStat = &(it_npc->second);
	}

	// �ж�����ھ����ڲ��Ƿ���Ȩ��
	int RetCode = pCorps->CheckIfHasBidRight(nRoleID, SCENENPCID_2(pNpcStat->m_MapID));
	
	if (RetCode)
	{
		//LOG_INFO("corps", "CheckIfHasBidRight fail");
		return RetCode;
	}
	
	//����ս����
	if (NpcStatus::STATE_Inbattle == pNpcStat->m_Status)
	{
		return ERROR_CORPS_INBATTLE;
	}
	
	//����δ����
	if (NpcStatus::STATE_BidOpen != pNpcStat->m_Status)
	{
		return ERROR_CORPS_BIDTIMENOTOPEN;
	}
	
	//�������Ѿ�ռ��
	if (pCorps->GetCorpsID() == pNpcStat->m_OwnerID)
	{
		return ERROR_CORPS_HASHOLDCITY;
	}

	// �������ǵ�ͼʱ�����۾��ź;���ռ������һ�������򲻵þ���
	CCorps* tpOwnerCorps = CCorpsManager::GetSingleton().GetCorpsByID(pNpcStat->m_OwnerID); 
	if (tpOwnerCorps && 
		INVALID_OBJ_ID != tpOwnerCorps->GetUnionID() &&
		tpOwnerCorps->GetUnionID() == pCorps->GetUnionID() &&
		IS_MAIN_CITY(nMapID) )
	{
		return ERROR_CORPS_BIDINUNION;
	}

	// �������ֹ���ܾ��۳���
	if ( nMapID == COUNTRY_MAP_CHANGAN && time(NULL) < pCorps->GetForbidTime() )
	{
		return ERROR_CORPS_ACCUSEFORBID;
	}

	//
	//���۽�Ǯ����
	
	//���������߾���
	if (nBidMoney <= pNpcStat->m_BidMoneyRank1)
	{
		return ERROR_CORPS_BIDMONEYLOWER;
	}

	//���Ž�Ǯ�����㹻����
	int tCorpsMoney = pCorps->GetCorpsMoney();
	bool BidDone = false;
	int tnReduceMoney = 0;
	BidInfoList::iterator it = m_BidInfoList.begin();
	for ( ; it != m_BidInfoList.end(); ++ it )
	{
		if (DataTag_Del != it->m_SynTag && 
			it->m_NpcID == nNpcID && 
			it->m_CorpsID == pCorps->GetCorpsID())
		{
			//���Ѿ�����
			if (nBidMoney - it->m_BidMoney <= tCorpsMoney)
			{
				//��۱��浽tnReduceMoney
				tnReduceMoney = nBidMoney - it->m_BidMoney;
				//�ۼ����Ž�Ǯ
				int tnRetCode = CCorpservice::GetSingleton().ConsumeCorpsMoney( pCorps->GetRooterID(), tnReduceMoney, REASON_WAR );
				if (tnRetCode)
				{
					LOG_ERROR("corps", "Bid money logic 1 error with return code : %d", tnRetCode);
					return tnRetCode;
				}
				//�޸ľ���
				BidDone = true;
				it->m_BidMoney = nBidMoney;
				it->m_BidTime = time(NULL);
				it->m_SynTag = (DataTag_New == it->m_SynTag) ? DataTag_New : DataTag_Upd;//�޸�����

				ChangeNpcBidRank(pNpcStat, pCorps->GetCorpsID(), it->m_BidMoney);
			}
			else
			{
				return ERROR_CORPS_MONEYNOTENOUGH;
			}
		}
	}

	//��һ�ξ���
	if (!BidDone)
	{
		if (nBidMoney <= pCorps->GetCorpsMoney())
		{
			tnReduceMoney = nBidMoney;
			//�ۼ����Ž�Ǯ
			int tnRetCode = CCorpservice::GetSingleton().ConsumeCorpsMoney( pCorps->GetRooterID(), tnReduceMoney, REASON_WAR );
			if (tnRetCode)
			{
				LOG_ERROR("corps", "Bid money logic 2 error with return code : %d", tnRetCode);
				return tnRetCode;
			}
			
			CorpsBidInfo tBidInfo;
			tBidInfo.m_NpcID = nNpcID;
			tBidInfo.m_CorpsID = pCorps->GetCorpsID();
			tBidInfo.m_BidMoney = nBidMoney;
			tBidInfo.m_BidTime = time(NULL);
			tBidInfo.m_SynTag = DataTag_New;//��������
			m_BidInfoList.push_back(tBidInfo);
			BidDone = true;
			
			ChangeNpcBidRank(pNpcStat, pCorps->GetCorpsID(), nBidMoney);
		}
		else
		{
			return ERROR_CORPS_MONEYNOTENOUGH;
		}
	}

	// LOG: �ɹ����뾺��
	LOG_INFO("corps", "Corps[%d] bid for battle of NPC[%d] at price[%d],spend $ %d", 
		pCorps->GetCorpsID(), 
		nNpcID, 
		nBidMoney,
		tnReduceMoney);
	LogBidNpc(ORGANLOGTYPE_CORPS, pCorps->GetCorpsID(), nRoleID, SCENENPCID_2(nNpcID), nBidMoney, tnReduceMoney);

	return SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// ���۽���
int CBidMgr::OnBidFinishTimesUp(int nNpcID, CCorps* &pAttacker, CCorps* &pDefender, int& nMoneyAtt, int& nMoneyDef)
{
	NpcStatusMap::iterator it = m_NpcStatusMap.find(nNpcID);
	NpcStatus* pNpcStat = NULL;
	if ( it == m_NpcStatusMap.end() )
	{
		LOG_ERROR("corps", "Get bid request for invalid NPC %d", nNpcID);
		pAttacker = NULL;
		pDefender = NULL;
		return -1;
	}
	
	// ���ȹرվ���
	pNpcStat = &(it->second);
	pNpcStat->m_Status = NpcStatus::STATE_BidClose;
	pNpcStat->m_SynTag = (DataTag_New == pNpcStat->m_SynTag) ? DataTag_New : DataTag_Upd;

	if (0 == pNpcStat->m_BidMoneyRank1)
	{
		//û�о��ۼ�¼
		LOG_NOTICE( "corps", "GateNpcID[%d] dosn't have any bid", nNpcID);
		pAttacker = NULL;
		pDefender = NULL;
	
		return -1;
	}
	CCorps* pCorpsRank1 = CCorpsManager::GetSingleton().GetCorpsByID(pNpcStat->m_CorpsIDRank1);
	if (NULL == pCorpsRank1)
	{
		LOG_ERROR( "corps", "GateNpcID[%d] can't find first bid corps [%d]", nNpcID, pNpcStat->m_CorpsIDRank1 );
		return -1;
	}

	
	if (0 == pNpcStat->m_OwnerID)
	{
		//NPCδ��ռ��
		pDefender = pCorpsRank1;
		nMoneyDef = pNpcStat->m_BidMoneyRank1;

		if (0 == pNpcStat->m_BidMoneyRank2)
		{
			//û�еڶ��������ߣ�Rank1ֱ�ӻ�ʤ
			pNpcStat->m_OwnerID = pNpcStat->m_CorpsIDRank1;
			pAttacker = NULL;
			nMoneyAtt = 0;

			//�������н�Ǯ
			DeleteNpcBidList(nNpcID, pNpcStat->m_CorpsIDRank1);
			//����NPC״̬
			pNpcStat->m_BidMoneyRank1 = 0;
			pNpcStat->m_BidMoneyRank2 = 0;
			pNpcStat->m_CorpsIDRank1 = 0;
			pNpcStat->m_CorpsIDRank2 = 0;

			return 0;
		} 
		else
		{
			//Rank1 Ϊ���ط�
			//Rank2 Ϊ������
			pAttacker = CCorpsManager::GetSingleton().GetCorpsByID(pNpcStat->m_CorpsIDRank2);
			if (NULL == pAttacker)
			{
				LOG_ERROR( "corps", "GateNpcID[%d] can't find rank2 bid corps [%d]", nNpcID, pNpcStat->m_CorpsIDRank2 );
				return -1;
			}
			DeleteNpcBidList(nNpcID, pNpcStat->m_CorpsIDRank1, pNpcStat->m_CorpsIDRank2);
			nMoneyAtt = pNpcStat->m_BidMoneyRank2;
		}
	}
	else
	{
		//NPC��ռ��
		//ռ����Ϊ���ط�
		pDefender = CCorpsManager::GetSingleton().GetCorpsByID(pNpcStat->m_OwnerID);
		nMoneyDef = 0;
		if (NULL == pDefender)
		{
			LOG_ERROR( "corps", "GateNpcID[%d] can't find owner corps [%d]", nNpcID, pNpcStat->m_OwnerID );
			return -1;
		}
		//Rank1 Ϊ������
		pAttacker = pCorpsRank1;
		nMoneyAtt = pNpcStat->m_BidMoneyRank1;

		DeleteNpcBidList(nNpcID, pNpcStat->m_CorpsIDRank1);
	}

	// ���ù���������Ӫ����ӪID Ϊ 1
	pAttacker->SetCorpsCamp( CAMP_1 );
	pAttacker->SetEnemyCorpsID(pDefender->GetCorpsID());
	// �����ط�������Ӫ����ӪID Ϊ2
	pDefender->SetCorpsCamp( CAMP_2 );
	pDefender->SetEnemyCorpsID(pAttacker->GetCorpsID());


	//����NPC״̬
	pNpcStat->m_BidMoneyRank1 = 0;
	pNpcStat->m_BidMoneyRank2 = 0;
	pNpcStat->m_CorpsIDRank1 = 0;
	pNpcStat->m_CorpsIDRank2 = 0;
	
	//��ʼ��ս����Ϣ
	CBattleMgr::GetSingleton().InitBattle(
		pAttacker->GetCorpsID(), 
		pDefender->GetCorpsID(), 
		TYPE_BATTLE_SCRABBLE, 
		nNpcID, 
		pNpcStat->m_MapID);

	return 0;
}

/// ���¾���ʱ�ı�ǰ����������
int CBidMgr::ChangeNpcBidRank(NpcStatus* pNpcStat, int nCorpsID, int nMoney)
{
	if (pNpcStat->m_CorpsIDRank1 != nCorpsID)
	{
		//���۾��������ǵ�һ
		pNpcStat->m_CorpsIDRank2 = pNpcStat->m_CorpsIDRank1;
		pNpcStat->m_BidMoneyRank2 = pNpcStat->m_BidMoneyRank1;
	}
	pNpcStat->m_CorpsIDRank1 = nCorpsID;
	pNpcStat->m_BidMoneyRank1 = nMoney;

	// û���޸ĵ�Ҫ��������ݣ������ñ�־λ
	return 0;
}

/// ���ھ��۽���ʱɾ�������б������ؾ���ʧ�ܾ��ŵĽ�Ǯ
/// nCorpsID* != 0 ʱ����ʾ���۳ɹ�����Ǯ������
int CBidMgr::DeleteNpcBidList(int nNpcID, int nCorpsID1, int nCorpsID2)
{
	BidInfoList::iterator it = m_BidInfoList.begin();
	CCorps* tpFailCorps;
	for ( ; it != m_BidInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		if (it->m_NpcID == nNpcID)
		{
			//ֻɾ����NPC�µ��б�
			if ( it->m_CorpsID != nCorpsID1 && it->m_CorpsID != nCorpsID2)
			{
				//���ؾ���ʧ�ܾ��ŵĽ�Ǯ
				tpFailCorps = CCorpsManager::GetSingleton().GetCorpsByID(it->m_CorpsID);
				if (NULL == tpFailCorps)
				{
					it->m_SynTag = DataTag_Del;
					//m_BidInfoList.erase(it);
					LOG_ERROR("corps", "[%s] Invalid corps_id[%d]", __FUNCTION__, it->m_CorpsID);
					continue;
				}

				tpFailCorps->SetCorpsMoney(tpFailCorps->GetCorpsMoney() + it->m_BidMoney);
				//tpFailCorps->ClearNpcBattleInfo( tpReq->npcid() );
			}
			it->m_SynTag = DataTag_Del;
			//m_BidInfoList.erase(it);
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
// �ع����о����б�
int CBidMgr::OnEventRollAllBidList()
{
	BidInfoList::iterator it = m_BidInfoList.begin();
	for ( ; it != m_BidInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		CCorps* tpCorps = CCorpsManager::GetSingleton().GetCorpsByID( it->m_CorpsID );
		if ( tpCorps == NULL )
		{
			continue;
		}
		int tMoney = tpCorps->GetCorpsMoney() + it->m_BidMoney;
		tpCorps->SetCorpsMoney( tMoney );
		int tCountryID = tpCorps->GetCorpsCountryID();
		int tNpcID = SCENENPCID( it->m_NpcID, tCountryID );
		tpCorps->ClearNpcBattleInfo( tNpcID );
		
		it->m_SynTag = DataTag_Del;//ɾ��
		
	}

	//m_BidInfoList.clear();

	ReCalculeteBidRank(0, 0);
	/// delete data in DB

	return SUCCESS;
}


// �ع�ָ��npc��ָ�����ŵľ���
int CBidMgr::OnEventRollCorpsNpc( int nCorpsID, int nNpcID , int nServerID)
{
	CCorps* tpCorps;
	BidInfoList::iterator it;
	// �ع�ָ��npc��ָ�����ŵľ���
	if ( INVALID_OBJ_ID != nCorpsID && INVALID_OBJ_ID != nNpcID )
	{
		tpCorps = CCorpsManager::GetSingleton().GetCorpsByID( nCorpsID );
		if ( tpCorps == NULL )
		{
			return -1;
		}

		it = m_BidInfoList.begin();
		for ( ; it != m_BidInfoList.end(); ++ it )
		{
			if (DataTag_Del == it->m_SynTag)
			{
				continue;
			}
			if ( it->m_NpcID == GATENPCID( nNpcID, tpCorps->GetCorpsCountryID() ) && tpCorps->GetCorpsID() == it->m_NpcID )
			{	
				int tMoney = tpCorps->GetCorpsMoney() + it->m_BidMoney;
				tpCorps->SetCorpsMoney( tMoney );
				tpCorps->ClearNpcBattleInfo( nNpcID );
				//m_BidInfoList.erase( it );
				/// Del from DB
				it->m_SynTag = DataTag_Del;
				break;
			}
		}
	}

	// �ع�ָ��npc�ľ����б�
	if ( INVALID_OBJ_ID == nCorpsID && INVALID_OBJ_ID != nNpcID )
	{
		int tNpcID = GATENPCID( nNpcID, nServerID );
		it = m_BidInfoList.begin();
		for ( ; it != m_BidInfoList.end(); ++ it )
		{
			if (DataTag_Del == it->m_SynTag)
			{
				continue;
			}
			if ( it->m_NpcID == tNpcID )
			{
				tpCorps = CCorpsManager::GetSingleton().GetCorpsByID(it->m_CorpsID);
				if ( tpCorps == NULL )
				{
					continue;
				}
				int tMoney = tpCorps->GetCorpsMoney() + it->m_BidMoney;
				tpCorps->SetCorpsMoney( tMoney );
				tpCorps->ClearNpcBattleInfo( nNpcID );
				//m_BidInfoList.erase( it );
				/// Del from DB
				it->m_SynTag = DataTag_Del;
				break;
			}
		}
	}
			
	// �ع�ָ�����ŵ����о���
	if ( INVALID_OBJ_ID != nCorpsID && INVALID_OBJ_ID == nNpcID )
	{
		CCorps* tpCorps = CCorpsManager::GetSingleton().GetCorpsByID( nCorpsID );
		if ( tpCorps == NULL )
		{
			return -1;
		}
		it = m_BidInfoList.begin();
		for ( ; it != m_BidInfoList.end(); ++ it)
		{
			if (DataTag_Del == it->m_SynTag)
			{
				continue;
			}
			if ( tpCorps->GetCorpsID() == it->m_CorpsID )
			{
				int tMoney = tpCorps->GetCorpsMoney() + it->m_BidMoney;
				tpCorps->SetCorpsMoney( tMoney );
				int tNpcID = SCENENPCID( it->m_NpcID, tpCorps->GetCorpsCountryID() );
				tpCorps->ClearNpcBattleInfo( tNpcID );
				//m_BidInfoList.erase( it );
				/// Del from DB
				it->m_SynTag = DataTag_Del;
			}
		}	
	}

	//���¼�������
	ReCalculeteBidRank(0, 0);

	return SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
//���ݿ�ͬ������

void CBidMgr::LoadCorpsBidFromDB( int nStart, int nTotalCount )
{
	const char* tpSqlstr = "select \
						  corps_id, \
						  npc_id, \
						  bid_money, \
						  bid_time from UMS_CORPS_BID limit %d,%d ";
	LOG_INFO("corps", tpSqlstr, nStart, COUNT_LOADCORPSBID);
	CGateLogic::GetSingleton().ExecuteSql( em_dbsession_load_corpsbid, nStart, nTotalCount, 3, SQL_NEED_CALLBACK, SELECT, 
		tpSqlstr, nStart, COUNT_LOADCORPSBID );
}

void CBidMgr::LoadNpcStatusFromDB( int nStart, int nTotalCount )
{
	const char* tpSqlstr = "select \
						  npc_id, \
						  map_id, \
						  owner_id, \
						  occupy_time, \
						  welfare_time, \
						  status from UMS_NPC_STATUS limit %d,%d ";
	CGateLogic::GetSingleton().ExecuteSql( em_dbsession_load_npcstatus, nStart, nTotalCount, 3, SQL_NEED_CALLBACK, SELECT, 
		tpSqlstr, nStart, COUNT_LOADCORPSBID );
	m_nDataState = 0;
}

void CBidMgr::OnSessionLoadCorpsBid( CMessage* pMessage, int nStart, int nTotalCount )
{
	LK_ASSERT( pMessage != NULL, return )
		CMessageExecuteSqlResponse3* tpMsg = (CMessageExecuteSqlResponse3 *) pMessage->msgpara();
	if ( tpMsg == NULL )
	{
		LOG_ERROR( "corps","[%s,%d] load corps_bid error, database error! ",__FUNCTION__, __LINE__ );
		printf( "[%s,%d] load corps_bid error, database error! ",__FUNCTION__, __LINE__ );
		exit( 0 );
	}
	int tcolnum = tpMsg->colcount();
	int trownum = tpMsg->rowcount();	
	if ( tcolnum != 4 )
	{
		LOG_ERROR( "corps","Load corps_bid failed!" );
		printf( "Load corps_bid failed!" );
		exit( 0 );
	}
	if ( tpMsg->resultcode() == 1 )
	{
		for ( int i = 0; i < trownum; ++i )
		{	
			CorpsBidInfo tBidInfo;
			tBidInfo.m_CorpsID = atoi( tpMsg->fieldvalue( i*tcolnum + 0 ).c_str() );	
			tBidInfo.m_NpcID = atoi( tpMsg->fieldvalue( i*tcolnum + 1 ).c_str() );	
			tBidInfo.m_BidMoney = atoi( tpMsg->fieldvalue( i*tcolnum + 2 ).c_str() );	
			tBidInfo.m_BidTime= atoi( tpMsg->fieldvalue( i*tcolnum + 3 ).c_str() );

			tBidInfo.m_SynTag = DataTag_Syn;
			
			LOG_DEBUG( "corps", "load corps_bid [CorpsID-%d NpcID-%d BidMoney-%d BidTime-%d]", 
				tBidInfo.m_CorpsID, 
				tBidInfo.m_NpcID, 
				tBidInfo.m_BidMoney, 
				tBidInfo.m_BidTime);

			m_BidInfoList.push_back(tBidInfo);
		}

		LOG_NOTICE("corps", "Load corps_bid data start %d num %d total %d", nStart, trownum, nTotalCount );

		if ( trownum < COUNT_LOADCORPSBID )
		{
			if ( nTotalCount < nStart + trownum )
			{
				printf( "[%s,%d]load corps_bid error, incorrect number :%d total number:%d", __FUNCTION__, __LINE__, nStart + trownum, nTotalCount );
				LOG_ERROR( "corps","[%s,%d]load corps_bid error, incorrect number :%d total number:%d", __FUNCTION__, __LINE__, nStart + trownum, nTotalCount );
				exit( 0 );				
			}
		}
		else
		{
			if ( trownum + nStart < nTotalCount )
			{
				//������������
				LoadCorpsBidFromDB( nStart + trownum, nTotalCount );
			}			
		}

		// �������
		if ( trownum + nStart >= nTotalCount )
		{
			//printf( "load corps end, total number:%d", nTotalCount );
			LOG_NOTICE( "corps","Load corps_bid Complete, Total Number:%d", nTotalCount );
			
			CCorpservice::GetSingleton().StartLoadAllFromDB(TAB_NPC);

		}
	}	
	else
	{
		printf( "[%s,%d] load corps_bid error, database error! ",__FUNCTION__, __LINE__ );
		LOG_ERROR( "corps","[%s,%d] load corps_bid error, database error! ",__FUNCTION__, __LINE__ );
		exit( 0 );
	}			   
}

void CBidMgr::OnSessionLoadNpcStatus( CMessage* pMessage, int nStart, int nTotalCount )
{
	LK_ASSERT( pMessage != NULL, return )
		CMessageExecuteSqlResponse3* tpMsg = (CMessageExecuteSqlResponse3 *) pMessage->msgpara();
	if ( tpMsg == NULL )
	{
		LOG_ERROR( "corps","[%s,%d] load npc_status error, database error! ",__FUNCTION__, __LINE__ );
		printf( "[%s,%d] load npc_status error, database error! ",__FUNCTION__, __LINE__ );
		exit( 0 );
	}
	int tcolnum = tpMsg->colcount();
	int trownum = tpMsg->rowcount();	
	if ( tcolnum != 6 )
	{
		LOG_ERROR( "corps","Load npc_status failed!" );
		printf( "Load npc_status failed!" );
		exit( 0 );
	}
	if ( tpMsg->resultcode() == 1 )
	{
		for ( int i = 0; i < trownum; ++i )
		{	
			NpcStatus tNpcInfo;
			int tNpcID = atoi( tpMsg->fieldvalue( i*tcolnum + 0 ).c_str() );
				
			int nDBMapID = atoi( tpMsg->fieldvalue( i*tcolnum + 1 ).c_str() );
			tNpcInfo.m_MapID = nDBMapID % MAPID_SWAP;
			tNpcInfo.m_nMapOccupyType = nDBMapID / MAPID_SWAP;

			tNpcInfo.m_OwnerID = atoi( tpMsg->fieldvalue( i*tcolnum + 2 ).c_str() );	
			tNpcInfo.m_OccupyTime = atoi( tpMsg->fieldvalue( i*tcolnum + 3 ).c_str() );
			tNpcInfo.m_WelfareTime = atoi( tpMsg->fieldvalue( i*tcolnum + 4 ).c_str() );
			tNpcInfo.m_Status = atoi( tpMsg->fieldvalue( i*tcolnum + 5 ).c_str() );
			
			if (tNpcInfo.m_Status < NpcStatus::STATE_MaxValue && 
				tNpcInfo.m_Status != NpcStatus::STATE_BidOpen)
			{
				//ǿ��ȫ��NPC�ָ������ۿ���״̬���ȶ�ȡս����ʱ������Ϊ�ر�
				tNpcInfo.m_Status = NpcStatus::STATE_BidOpen;
				tNpcInfo.m_SynTag = DataTag_Upd;
			}
			else
			{
				tNpcInfo.m_SynTag = DataTag_Syn;
			}
			
			if (0 == tNpcInfo.m_nMapOccupyType)
			{
				tNpcInfo.m_nMapOccupyType = OCP_SUBCITY;	// Ĭ��Ϊ������
				tNpcInfo.m_SynTag = DataTag_Upd;			// ������Ҫ����
				m_nDataState = 1;							// ����Ǩ��״̬
			}
			
			LOG_DEBUG( "corps", "Init From DataBase");

			AddNpcStateInfo(tNpcID, &tNpcInfo);
		}

		LOG_NOTICE("corps", "Load npc_status data start %d num %d total %d", nStart, trownum, nTotalCount );

		if ( trownum < COUNT_LOADCORPSBID )
		{
			if ( nTotalCount < nStart + trownum )
			{
				printf( "[%s,%d]load npc_status error, incorrect number :%d total number:%d", __FUNCTION__, __LINE__, nStart + trownum, nTotalCount );
				LOG_ERROR( "corps","[%s,%d]load npc_status error, incorrect number :%d total number:%d", __FUNCTION__, __LINE__, nStart + trownum, nTotalCount );
				exit( 0 );				
			}
		}
		else
		{
			if ( trownum + nStart < nTotalCount )
			{
				//������������
				LoadNpcStatusFromDB( nStart + trownum, nTotalCount );
			}			
		}

		// �������
		if ( trownum + nStart >= nTotalCount )
		{
			//printf( "load corps end, total number:%d", nTotalCount );
			LOG_NOTICE( "corps","Load npc_status Complete, Total Number:%d", nTotalCount );

			//���¼���ǰ������
			ReCalculeteBidRank(0, 0);
			CCorpservice::GetSingleton().StartLoadAllFromDB(TAB_BATTLE);

		}
	}	
	else
	{
		printf( "[%s,%d] load corps_bid error, database error! ",__FUNCTION__, __LINE__ );
		LOG_ERROR( "corps","[%s,%d] load corps_bid error, database error! ",__FUNCTION__, __LINE__ );
		exit( 0 );
	}			   
}

// ���һ��NPC״̬��Ϣ������ʱͨ��pNpc->m_SynTag�趨�Ƿ�Ҫ�������ݿ�
int CBidMgr::AddNpcStateInfo(int nNpcID, NpcStatus *pNpc)
{
	LOG_DEBUG( "corps", "add corps_npc_status [NpcID-%d MapID-%d OwnerID-%d WelfareTime-%d m_Status-%d]", 
		nNpcID, 
		pNpc->m_MapID, 
		pNpc->m_OwnerID, 
		pNpc->m_WelfareTime, 
		pNpc->m_Status);
	if ( m_NpcStatusMap.find(nNpcID) != m_NpcStatusMap.end() )
	{
		LOG_ERROR("corps", "[%s][%s]Duplicate NPC ID %d", __LINE__, __FUNCTION__, nNpcID);
		return -1;
	}
	
	pNpc->m_NpcID = SCENENPCID_2(nNpcID);
	
	m_NpcStatusMap.insert(NpcStatusMap::value_type(nNpcID, *pNpc));
	return 0;
}



//-------------------------------------------------------------------------
// ��ȡ����ռ��ĵ�ͼ�б�
int CBidMgr::GetMapListByCorps(CCorps* pCorps, int* pnMapList, int& nNum)
{
	//int tNum = nNum; nNum = 0;
	//CorpsBattleInfo::iterator it = m_BattleInfo.begin();
	//for ( ; it != m_BattleInfo.end(); ++ it )
	//{
	//	ST_BATTLE_INFO* tpInfo = ( ST_BATTLE_INFO* ) &( it->second );
	//	if ( tpInfo->mNpcStatus == STATE_OWN && nNum < tNum )
	//	{
	//		npMapList[ nNum ++ ] = tpInfo->mMapID;
	//	}
	//}
	int tnListSize = nNum;
	nNum = 0;
	NpcStatusMap::iterator it = m_NpcStatusMap.begin();
	NpcStatus *pNpcState = NULL;
	for ( ; it != m_NpcStatusMap.end(); ++ it )
	{
		pNpcState = &(it->second);
		if (pNpcState->m_OwnerID == pCorps->GetCorpsID() && nNum < tnListSize)
		{
			pnMapList[nNum++] = SCENENPCID_2(pNpcState->m_MapID);
		}
	}
	return 0;
}

//�������ᵼ��ռ�����滻�����ø�����ȡʱ��
int CBidMgr::SetNpcOwner(int nGateNpcID, int nCorpsID)
{
	NpcStatus* tpNpcState = GetNpcStatus(nGateNpcID);
	if (NULL == tpNpcState)
	{
		return -1;
	}
	if (nCorpsID != 0)
	{
		//������ռ�������NPC��ռ��ʱ�䣬
		tpNpcState->m_OccupyTime = time(NULL);

		if (tpNpcState->m_OwnerID != nCorpsID)
		{
			//�滻��ռ���ߵ�������������ø�����ȡʱ��
			tpNpcState->m_WelfareTime = tpNpcState->m_OccupyTime - WELFARE_REFESH_TIMELENGTH;
		}
	}
	tpNpcState->m_OwnerID = nCorpsID;
	//��ʼ״̬Ϊ����
	tpNpcState->m_nMapOccupyType = OCP_SUBCITY;
	tpNpcState->m_SynTag = (DataTag_New == tpNpcState->m_SynTag) ? DataTag_New : DataTag_Upd;
	// �޸ĵ���״̬
	if ( SCENENPCID_2(tpNpcState->m_MapID) == COUNTRY_MAP_CHANGAN )
	{
		CWorldManager::GetSingleton().ResetAccuseState( SCENESERVERID(tpNpcState->m_MapID) );
	}
	return 0;
}

//������������ʱ���ã������ø�����ȡʱ��
int CBidMgr::SetNpcOwnerByMapID(int nGateMapID, int nCorpsID)
{
	NpcStatusMap::iterator it = m_NpcStatusMap.begin();
	NpcStatus *tpNpcState = NULL;
	for ( ; it != m_NpcStatusMap.end(); ++ it )
	{
		tpNpcState = &(it->second);
		if (tpNpcState->m_MapID == nGateMapID)
		{
			tpNpcState->m_OwnerID = nCorpsID;
			tpNpcState->m_SynTag = (DataTag_New == tpNpcState->m_SynTag) ? DataTag_New : DataTag_Upd;
			return 0;
		}
	}
	return -1;
}

int CBidMgr::FindCityOwnerByMapID(int nGateMapID, int &nNpcID)
{
	NpcStatusMap::iterator it = m_NpcStatusMap.begin();
	NpcStatus *tpNpcState = NULL;
	for ( ; it != m_NpcStatusMap.end(); ++ it )
	{
		tpNpcState = &(it->second);
		if (tpNpcState->m_MapID == nGateMapID)
		{
			nNpcID = SCENENPCID_2(it->first);
			return tpNpcState->m_OwnerID;
		}
	}
	return 0;
}

int CBidMgr::GetNpcIDByMapID(int nSceneMapID)
{
	NpcStatusMap::iterator it = m_NpcStatusMap.begin();
	NpcStatus *tpNpcState = NULL;
	int nNpcID = 0;
	for ( ; it != m_NpcStatusMap.end(); ++ it )
	{
		tpNpcState = &(it->second);
		if (SCENENPCID_2(tpNpcState->m_MapID) == nSceneMapID)
		{
			nNpcID = SCENENPCID_2(it->first);
			return nNpcID;
		}
	}
	return 0;
}

void CBidMgr::SendCorpsNpcList( int nServerID )
{
	CMessage MsgHead;	
	CMessageNpcListNotify Notify;
	CCorpsManager *pCorpsMgr = CCorpsManager::GetSingletonPtr();

	NpcStatusMap::iterator it = m_NpcStatusMap.begin();
	for ( ; it != m_NpcStatusMap.end(); ++ it )
	{
		NpcStatus * pNpc = &(it->second);
		if ( 0 == pNpc->m_OwnerID )
			continue;
		CCorps* tpCorsp = pCorpsMgr->GetCorpsByID( pNpc->m_OwnerID );
		if ( tpCorsp == NULL )
			continue;
		if ( tpCorsp->GetCorpsCountryID() != nServerID )
			continue;

		//int tMapID = SCENENPCID( pNpc->m_MapID, nServerID );
		//int tNpcID = tpCorsp->HasOwnThisMap( tMapID );
		int tGateNpcID = it->first;
		int tNpcID = SCENENPCID_2(tGateNpcID);

		if ( tNpcID != INVALID_OBJ_ID )
		{
			PBCorpsNpc* tpNpc = Notify.add_corpsnpc();
			tpNpc->set_corpsid( tpCorsp->GetCorpsID() );
			tpNpc->set_corpsname( tpCorsp->GetCorpsName() );
			tpNpc->set_npcid( tNpcID );
			tpNpc->set_type( (int) true );
			LOG_NOTICE( "corps", "ServerID[%d],Npc Own: CorpsName:%s,CorpsID:%d,NpcID:%d,Add:1", 
				nServerID, tpCorsp->GetCorpsNameShow(), tpCorsp->GetCorpsID(), tNpcID );
		}			
	}

	Notify.set_type( TYPE_CORPS );
	MsgHead.set_msgpara( (int)&Notify );
	MsgHead.mutable_msghead()->set_messageid( ID_G2S_NOTIFY_NPCLIST );
	CGateServer::GetSingleton().Send2Scene( nServerID, &MsgHead );
}

void CBidMgr::OnTimerCheckState()
{
	NpcStatusMap::iterator it = m_NpcStatusMap.begin();
	NpcStatus *tpNpcState = NULL;

	time_t tNow = time( NULL );
	struct tm* tpLocal = localtime( &tNow );
	
	for ( ; it != m_NpcStatusMap.end(); ++ it )
	{
		tpNpcState = &(it->second);
		int tnNpcID = SCENENPCID_2(it->first);
		int tnServerID = SCENESERVERID(it->first);
		//ȡ��NPCģ��
		CTemplateNpc* tpTplNpc = ( CTemplateNpc* ) CDataStatic::SearchTpl(tnNpcID);

		//ֻ�����ھ��ۿ���״̬�е�NPC
		if (NpcStatus::STATE_BidOpen != tpNpcState->m_Status)
		{
			if ( InTimeZone(tpLocal,
				tpTplNpc->mCorpsBidStartDay, 
				tpTplNpc->mCorpsBidStartHour, 
				tpTplNpc->mCorpsBidStartMinute, MAX_BID_FINISH_DELAY) )
			{
				tpNpcState->m_Status = NpcStatus::STATE_BidOpen;
				tpNpcState->m_SynTag = (DataTag_New == tpNpcState->m_SynTag) ? DataTag_New : DataTag_Upd;
			}
			continue;
		}

		if ( NULL == tpTplNpc )
		{
			//����
			continue;
		}
		//����Ƿ��о���ս
		if ( tpTplNpc->mCorpsBattle == 0 )
		{
			//����
			continue;
		}
		

		//ƥ�侺�۽���ʱ��(��)
		if ( InTimeZone(tpLocal,
			tpTplNpc->mCorpsBidDay, 
			tpTplNpc->mCorpsBidHour, 
			tpTplNpc->mCorpsBidMinute, MAX_BID_FINISH_DELAY) )
		{
			//֪ͨ���ؾ��۽���
			CMessage tMessage;
			CMessageCorpsBidTimerStopRequest tPara;
			tPara.set_npcid( tpTplNpc->mTempID );
			tPara.set_battleid( tpTplNpc->mBattleCity );
			tMessage.mutable_msghead()->set_messageid( ID_S2G_REQUEST_BIDTIMERSTOP );
			tMessage.set_msgpara( (long) &tPara );

			CCorpservice::GetSingleton().OnMessageBidTimeOutRequest( tnServerID, &tMessage );
			//CSceneLogic::GetSingleton().Send2Gate( &tMessage );

			//LogEventCorpsBattle( tpTplNpc->mTempID, tpTplNpc->mBattleCity, EM_ORGAN_JOIN_BATTLE, 0 );

			LOG_NOTICE( "corps", "[%s:%d] Gate2Gate CorpsBidTimeout npc %d battleid %d" ,
				__LK_FILE__, __LINE__, tpTplNpc->mTempID, tpTplNpc->mBattleCity );
		}
	}
}

// �ж�ָ��ʱ���Ƿ���ĳ��ָ��ʱ�䷶Χ��
bool CBidMgr::InTimeZone(tm* pLocal, int nEventDay, int nEventHour, int nEventMin, int nDelayMin)
{
	if ((1 == pLocal->tm_wday && (nEventDay & CTemplateNpc::WDAY_MONDAY)) ||
		(2 == pLocal->tm_wday && (nEventDay & CTemplateNpc::WDAY_TUESDAY)) || 
		(3 == pLocal->tm_wday && (nEventDay & CTemplateNpc::WDAY_WEDENSDAY)) || 
		(4 == pLocal->tm_wday && (nEventDay & CTemplateNpc::WDAY_THURSDAY)) || 
		(5 == pLocal->tm_wday && (nEventDay & CTemplateNpc::WDAY_FRIDAY)) || 
		(6 == pLocal->tm_wday && (nEventDay & CTemplateNpc::WDAY_SATURDAY)) || 
		(0 == pLocal->tm_wday && (nEventDay & CTemplateNpc::WDAY_SUNDAY)))
	{
		int tnNowTime = pLocal->tm_hour * 60 + pLocal->tm_min;
		int tnEventTime = nEventHour * 60 + nEventMin;

		if ( tnNowTime >= tnEventTime && tnNowTime < tnEventTime + nDelayMin )
		{
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------
// ���NPC����״̬���У���ʼ����NPC��״̬����
int CBidMgr::PreSetNpcState(int nGateNpcID)
{
	NpcStatusMap::iterator it  = m_NpcStatusMap.find(nGateNpcID);
	
	if ( it == m_NpcStatusMap.end() )
	{
		LOG_NOTICE("corps", "Add New NPC State into BidMgr GateNpcID: %d", nGateNpcID);
		
		CTemplateNpc* tpTplNpc = ( CTemplateNpc* ) CDataStatic::SearchTpl(SCENENPCID_2(nGateNpcID));
		if ( NULL == tpTplNpc )
		{
			LOG_ERROR("corps", "Can not find Template, GateNpcID: %d", nGateNpcID);
			return -10;
		}
		if ( tpTplNpc->mCorpsBattle == 0 )
		{
			LOG_ERROR("corps", "tpTplNpc->mCorpsBattle == 0, GateNpcID: %d", nGateNpcID);
			return -20;
		}

		int ServerID = SCENESERVERID(nGateNpcID);

		NpcStatus tNpcState;
		tNpcState.m_MapID = GATENPCID(tpTplNpc->mBattleCity, ServerID);
		tNpcState.m_BidMoneyRank1 = 0;
		tNpcState.m_BidMoneyRank2 = 0;
		tNpcState.m_CorpsIDRank1 = 0;
		tNpcState.m_CorpsIDRank2 = 0;
		tNpcState.m_OwnerID = 0;
		tNpcState.m_Status = NpcStatus::STATE_BidOpen;
		tNpcState.m_WelfareTime = 0;

		// ��ʼʱΪ������
		tNpcState.m_nMapOccupyType = OCP_SUBCITY;

		tNpcState.m_SynTag = DataTag_New;	//������

		tNpcState.m_NpcID = SCENENPCID_2(nGateNpcID);
		m_NpcStatusMap.insert(NpcStatusMap::value_type(nGateNpcID, tNpcState));
	}
	return 0;
}

//-------------------------------------------------------------------------
// ͬ�����ݵ�DB
int CBidMgr::SynDataToDB()
{
	LOG_DEBUG("corps","%s ----------", __FUNCTION__);
	// ���澺������
	BidInfoList::iterator it = m_BidInfoList.begin();
	for ( ; it != m_BidInfoList.end(); )
	{		
		LOG_DEBUG("corps", "[TAG:%d] corps_id:%d, npc_id:%d, bid_money:%d, bid_time:%d",
			it->m_SynTag,
			it->m_CorpsID, 
			it->m_NpcID,
			it->m_BidMoney,
			it->m_BidTime);

		if (DataTag_New == it->m_SynTag)
		{
			const char *tpSql0 = "insert into UMS_CORPS_BID(corps_id, npc_id, bid_money, bid_time)\
								 values( %d, %d, %d, %d ) ";
			CGateLogic::GetSingleton( ).ExecuteSql(
				em_dbsession_update_corpsbid, 0, 0, 3, SQL_NONE, INSERT, tpSql0, 
				it->m_CorpsID, 
				it->m_NpcID,
				it->m_BidMoney,
				it->m_BidTime);
			it->m_SynTag = DataTag_Syn;
			++ it;
		}
		else if (DataTag_Syn == it->m_SynTag)
		{
			++ it;
		}
		else if (DataTag_Upd == it->m_SynTag)
		{
			const char *tpSql2 = "update UMS_CORPS_BID set \
								 bid_money=%d, \
								 bid_time=%d where corps_id=%d and npc_id=%d";
			CGateLogic::GetSingleton( ).ExecuteSql(
				em_dbsession_update_corpsbid, 0, 0, 3, SQL_NONE, UPDATE, tpSql2,
				it->m_BidMoney, 
				it->m_BidTime,
				it->m_CorpsID,
				it->m_NpcID);
			it->m_SynTag = DataTag_Syn;
			++ it;
		}
		else if (DataTag_Del == it->m_SynTag)
		{
			const char *tpSql3 = "delete from UMS_CORPS_BID where corps_id=%d and npc_id=%d";
			CGateLogic::GetSingleton( ).ExecuteSql(
				em_dbsession_updatecorpsinfo, 0, 0, 3, SQL_NONE, DELETE, tpSql3,
				it->m_CorpsID, 
				it->m_NpcID);

			it = m_BidInfoList.erase(it);
		}
		else
		{
			++ it;
			LOG_ERROR("corps", "INVALID m_SynTag:%d in m_BidInfoList", it->m_SynTag);
		}
	}
	// ����NPC״̬
	NpcStatusMap::iterator it2 = m_NpcStatusMap.begin();
	for ( ; it2 != m_NpcStatusMap.end(); ++ it2 )
	{		
		NpcStatus *pNpc = &(it2->second);
		LOG_DEBUG("corps", "[TAG:%d] NPC_STATUS(npc_id:%d, map_id:%d, owner_id:%d, occupy_time:%d, welfare_time:%d, status:%d)",
			pNpc->m_SynTag,
			it2->first,
			pNpc->m_MapID, 
			pNpc->m_OwnerID,
			pNpc->m_OccupyTime,
			pNpc->m_WelfareTime,
			pNpc->m_Status);

		if (DataTag_New == pNpc->m_SynTag)
		{
			const char *tpSql0 = "insert into UMS_NPC_STATUS(npc_id, map_id, owner_id, occupy_time, welfare_time, status)\
								 values( %d, %d, %d, %d, %d, %d ) ";
			CGateLogic::GetSingleton( ).ExecuteSql(
				em_dbsession_update_npcstatus, 0, 0, 3, SQL_NONE, INSERT, tpSql0, 
				it2->first,
				GET_DBMAPID(pNpc->m_nMapOccupyType, pNpc->m_MapID),	//ռ�����ͺ�MapID��ͬһ�ֶ� 
				pNpc->m_OwnerID,
				pNpc->m_OccupyTime,
				pNpc->m_WelfareTime,
				pNpc->m_Status);
			pNpc->m_SynTag = DataTag_Syn;
		}
		else if (DataTag_Syn == pNpc->m_SynTag)
		{
			continue;
		}
		else if (DataTag_Upd == pNpc->m_SynTag)
		{
			const char *tpSql2 = "update UMS_NPC_STATUS set \
								 map_id=%d, \
								 owner_id=%d, \
								 status=%d, \
								 occupy_time=%d, \
								 welfare_time=%d, \
								 status=%d where npc_id=%d";
			CGateLogic::GetSingleton( ).ExecuteSql(
				em_dbsession_update_npcstatus, 0, 0, 3, SQL_NONE, UPDATE, tpSql2,
				GET_DBMAPID(pNpc->m_nMapOccupyType, pNpc->m_MapID),	//ռ�����ͺ�MapID��ͬһ�ֶ� 
				pNpc->m_OwnerID, 
				pNpc->m_Status,
				pNpc->m_OccupyTime,
				pNpc->m_WelfareTime,
				pNpc->m_Status,
				it2->first);
			pNpc->m_SynTag = DataTag_Syn;
		}
	}
	return 0;
}

//���ݾ����б����¼���ָ����Ӫ��ָ��NPC�ľ���ǰ����
void CBidMgr::ReCalculeteBidRank(int nNpcID, int nServerID)
{
	//���NPC��������
	NpcStatusMap::iterator it_npc = m_NpcStatusMap.begin();
	for ( ; it_npc != m_NpcStatusMap.end(); ++ it_npc )
	{
		NpcStatus* pNpc = &(it_npc->second);
		pNpc->m_BidMoneyRank1 = 0;
		pNpc->m_BidMoneyRank2 = 0;
		pNpc->m_CorpsIDRank1 = 0;
		pNpc->m_CorpsIDRank2 = 0;
	}
	
	BidInfoList::iterator it_bid = m_BidInfoList.begin();
	for ( ; it_bid != m_BidInfoList.end(); ++ it_bid )
	{
		if (DataTag_Del == it_bid->m_SynTag)
		{
			continue;
		}
		it_npc = m_NpcStatusMap.find(it_bid->m_NpcID);
		if (it_npc ==  m_NpcStatusMap.end())
		{
			LOG_ERROR("corps", "[%s]Can not find NPC[%d] State for BidInfo[CorpsID:%d, Money:%d]",
				__FUNCTION__,
				it_bid->m_NpcID,
				it_bid->m_CorpsID,
				it_bid->m_BidMoney);
			continue;
		}
		NpcStatus* pNpc = &(it_npc->second);
		//����Rank1
		if (it_bid->m_BidMoney > pNpc->m_BidMoneyRank1)
		{
			//R1 => R2
			pNpc->m_BidMoneyRank2 = pNpc->m_BidMoneyRank1;
			pNpc->m_CorpsIDRank2 = pNpc->m_CorpsIDRank1;
			//NEW => R1
			pNpc->m_BidMoneyRank1 = it_bid->m_BidMoney;
			pNpc->m_CorpsIDRank1 = it_bid->m_CorpsID;		
			continue;
		}
		//��Rank1-2֮��
		if (it_bid->m_BidMoney > pNpc->m_BidMoneyRank2)
		{
			// NEW => R2
			pNpc->m_BidMoneyRank2 = it_bid->m_BidMoney;
			pNpc->m_CorpsIDRank2 = it_bid->m_CorpsID;
			continue;
		}
	}
}

//���ž���
void CBidMgr::SetBidOpen(int nGateNpcID, bool bOpen /*= true*/)
{
	NpcStatusMap::iterator it = m_NpcStatusMap.find(nGateNpcID);
	if (it == m_NpcStatusMap.end())
	{
		return;
	}
	NpcStatus *pNpcState = &(it->second);
	if (bOpen)
	{
		pNpcState->m_Status = NpcStatus::STATE_BidOpen;
	}
	else
	{
		pNpcState->m_Status = NpcStatus::STATE_BidClose;
	}
	pNpcState->m_SynTag = (DataTag_New == pNpcState->m_SynTag) ? DataTag_New : DataTag_Upd;
}


void CBidMgr::OnGMChangeNpcState(int nServeID, int nSceneNpcID, int nStateCode)
{
	int nGateNpcID = GATENPCID(nSceneNpcID, nServeID);
	NpcStatusMap::iterator it = m_NpcStatusMap.find(nGateNpcID);
	if (it == m_NpcStatusMap.end())
	{
		return;
	}
	NpcStatus *pNpcState = &(it->second);
	if (NpcStatus::STATE_BidOpen == nStateCode)
	{
		pNpcState->m_Status = NpcStatus::STATE_BidOpen;
		pNpcState->m_SynTag = (DataTag_New == pNpcState->m_SynTag) ? DataTag_New : DataTag_Upd;
	}
	else if (NpcStatus::STATE_BidClose == nStateCode)
	{
		//�ر�ǰ�Ȼع���Ǯ
		OnEventRollCorpsNpc(INVALID_OBJ_ID, nSceneNpcID, nServeID);
		pNpcState->m_Status = NpcStatus::STATE_BidClose;
		pNpcState->m_SynTag = (DataTag_New == pNpcState->m_SynTag) ? DataTag_New : DataTag_Upd;
	}
}

// �жϵ�ǰ�����Ƿ���뾺�ۻ�ռ���˳ǳ��ڱ�������, �����ָ����ͼ���ͱ�ʾȫ��
bool CBidMgr::IsInBid(int nCorpsID, int nType)
{
	NpcStatus* pNpc = NULL;
	
	if (nType & ST_Occupy)
	{
		NpcStatusMap::iterator it_npc = m_NpcStatusMap.begin();
		for ( ; it_npc != m_NpcStatusMap.end(); ++ it_npc )
		{
			pNpc = &(it_npc->second);
			int nSceneMapID = SCENENPCID_2(pNpc->m_MapID);
			if (pNpc->m_OwnerID == nCorpsID)
			{
				if (nType & ST_CityMap)
				{
					if (IS_MAIN_CITY(nSceneMapID))
					{	
						return true;
					}
				}
				else
				{
					return true;
				}
			}
		}
	}
	if (nType & ST_InBid)
	{
		BidInfoList::iterator it_bid = m_BidInfoList.begin();
		for ( ; it_bid != m_BidInfoList.end(); ++ it_bid )
		{
			if (DataTag_Del == it_bid->m_SynTag)
			{
				continue;
			}
			if (it_bid->m_CorpsID == nCorpsID)
			{
				if (nType & ST_CityMap)
				{
					pNpc = GetNpcStatus(it_bid->m_NpcID);
					if (pNpc && IS_MAIN_CITY(SCENENPCID_2(pNpc->m_MapID)))
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
		}
	}
	return false;
}


//ֻ�гɹ�����nSceneMapIDΪ���Ǻ�ŷ���true
bool CBidMgr::SetMainCity(int nCorpsID, int nSceneMapID)
{
	bool bRet = false;
	NpcStatusMap::iterator it_npc = m_NpcStatusMap.begin();
	for ( ; it_npc != m_NpcStatusMap.end(); ++ it_npc )
	{
		NpcStatus* pNpc = &(it_npc->second);
		if (pNpc->m_OwnerID == nCorpsID)
		{
			if (nSceneMapID == SCENENPCID_2(pNpc->m_MapID))
			{
				if (OCP_MAINCITY != pNpc->m_nMapOccupyType)
				{
					pNpc->m_nMapOccupyType = OCP_MAINCITY;
					pNpc->m_SynTag = (DataTag_New == pNpc->m_SynTag) ? DataTag_New : DataTag_Upd;
				}
				bRet = true;
			}
			else
			{
				if (OCP_SUBCITY != pNpc->m_nMapOccupyType)
				{
					pNpc->m_nMapOccupyType = OCP_SUBCITY;
					pNpc->m_SynTag = (DataTag_New == pNpc->m_SynTag) ? DataTag_New : DataTag_Upd;
				}
			}
		}
	}
	return bRet;
}

int CBidMgr::GetMainCity(int nCorpsID)
{
	NpcStatusMap::iterator it_npc = m_NpcStatusMap.begin();
	for ( ; it_npc != m_NpcStatusMap.end(); ++ it_npc )
	{
		NpcStatus* pNpc = &(it_npc->second);
		if (pNpc->m_OwnerID == nCorpsID && OCP_MAINCITY == pNpc->m_nMapOccupyType)
		{
			return SCENENPCID_2(pNpc->m_MapID);
		}
	}
	return INVALID_MAP_ID;
}