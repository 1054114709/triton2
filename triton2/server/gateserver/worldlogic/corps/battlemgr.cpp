//================================================================================
// battlemgr.cpp
//================================================================================
#include "battlemgr.h"
#include "corpsmanager.h"
#include "corpservice.h"
#include "gatelogic.h"
#include "bidmgr.h"
#include "log_tools.h"

using namespace GateServer;

//-------------------------------------------------------------------------
CSharedMem *CBattleMgr::mShmPtr = NULL;
template<> CBattleMgr * CSingleton< CBattleMgr >::spSingleton = NULL;
//-------------------------------------------------------------------------
CBattleMgr::CBattleMgr()
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
CBattleMgr::~CBattleMgr()
{
	;
}
//-------------------------------------------------------------------------
int CBattleMgr::Initialize( )
{
	m_BattleInfoList.initailize();
	return 0;
}
//-------------------------------------------------------------------------
int CBattleMgr::Resume( )
{
	return 0;
}//-------------------------------------------------------------------------
void* CBattleMgr::operator new( size_t size )
{
	return ( void* ) mShmPtr->CreateSegment( size );
}
//-------------------------------------------------------------------------
void  CBattleMgr::operator delete( void* pointer )
{

}
//-------------------------------------------------------------------------
unsigned int CBattleMgr::CountSize()
{
	return sizeof(CBattleMgr);
}

// ��ʼ���µ�ս����Ϣ��key == 0
int CBattleMgr::InitBattle(int nAttCorpsID, int nDefCorpsID, int nType, int nNpcID, int nMapID)
{
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if ( DataTag_Del != it->m_SynTag && it->m_NpcID == nNpcID )
		{
			LOG_ERROR( "corps", "Npc has in battle.NpcID[%d], [%s:%d]", nNpcID, __LK_FILE__, __LINE__ );
			return -1;
		}
	}
	BattleInfo tBattleInfo( 0, nAttCorpsID, nDefCorpsID, nType, nNpcID, SCENENPCID_2(nMapID));
	tBattleInfo.m_BattleTime = time(NULL) + SUBMIT_TIME_BEFORE_BATTLE ;//����30���Ӻ�ս

	tBattleInfo.m_SynTag = DataTag_New;//������
	m_BattleInfoList.push_back( tBattleInfo );
	return 0;
}

// ս�������ɹ�����ʼս������ʱ��ֵ��Key
void CBattleMgr::StartBattle( KEY_TYPE nKey, int nNpcID )
{
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		if ( it->m_Key == nKey )
		{
			LOG_ERROR( "corps", "Battle Key dumplicate![%s:%d]", __LK_FILE__, __LINE__ );
			break ;
		}
		if ( it->m_NpcID == nNpcID && INVITED_KEY_VALUE == it->m_Key )
		{
			it->m_Key = nKey;
			it->m_BattleTime = time(NULL);	//ս���Ѿ���ʼ������ʵ��ս����ʼʱ��
			it->m_SynTag = (DataTag_New == it->m_SynTag) ? DataTag_New : DataTag_Upd;

			if (TYPE_BATTLE_SCRABBLE == it->m_Type)
			{
				// LOG:��������ս��ս
				LogJoinNPCBattle(ORGANLOGTYPE_CORPS, 
					it->m_DefCorpsID, 0, it->m_AttCorpsID, SCENENPCID_2(it->m_NpcID), 0);
			}
			break;
		}
	}
	return ;
}

// ���ս����ս���� [11/28/2009 Macro]
int CBattleMgr::GetBattle( int nNpcID, int &nSrcCorpsID, int& nDesCorpsID, int& nMapID )
{	
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		if ( it->m_NpcID == nNpcID )
		{
			nSrcCorpsID = it->m_AttCorpsID;
			nDesCorpsID = it->m_DefCorpsID;
			nMapID = it->m_MapID;
			
			if (it->m_Key == INVITED_KEY_VALUE)
			{
				return 0;
			} 
			else
			{
				return 1;
			}
			
		}
	}
	return -1;
}
//BattleInfo* CBattleMgr::GetBattleInfo( int nNpcID, int &nSrcCorpsID, int& nDesCorpsID, int& nMapID )
//{	
//	BattleInfoList::iterator it = m_BattleInfoList.begin();
//	for ( ; it != m_BattleInfoList.end(); ++ it )
//	{
//		if ( it->m_NpcID == nNpcID )
//		{
//			nSrcCorpsID = it->m_AttCorpsID;
//			nDesCorpsID = it->m_DefCorpsID;
//			nMapID = it->m_MapID;
//			break;
//		}
//	}
//	return SUCCESS;
//}

// ɾ��ս�� [11/28/2009 Macro]
// ֻɾ��ָ��NPC��δ��ʼ��ս��
int CBattleMgr::DelBattle( int nNpcID )
{
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		if ( it->m_NpcID == nNpcID && it->m_Key == INVITED_KEY_VALUE )
		{
			//m_BattleInfoList.erase( it );
			it->m_SynTag = DataTag_Del;
			if (it->m_Type == TYPE_BATTLE_SCRABBLE)
			{
				//CBidMgr::GetSingleton().SetBidOpen(it->m_NpcID);
			}
			break;
		}
	}
	return SUCCESS;
}

//ɾ��ָ��Key��ս��
int CBattleMgr::DelBattle( KEY_TYPE nKey )
{
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		if ( it->m_Key == nKey )
		{
			//m_BattleInfoList.erase( it );
			it->m_SynTag = DataTag_Del;
			if (it->m_Type == TYPE_BATTLE_SCRABBLE)
			{
				//CBidMgr::GetSingleton().SetBidOpen(it->m_NpcID);
			}
			break;
		}
	}
	return SUCCESS;
}

// �жϾ����Ƿ���ս����
bool CBattleMgr::IsInBattleByCorpsID( int nCorpsID, int nTypeTag)
{
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		if ( it->m_AttCorpsID == nCorpsID || it->m_DefCorpsID == nCorpsID)
		{
			if (nTypeTag & ST_WaitBtl && INVITED_KEY_VALUE == it->m_Key)
			{
				//�ȴ���ս��
				if (nTypeTag & ST_CityMap)
				{
					if (IS_MAIN_CITY(SCENENPCID_2(it->m_MapID)))
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			if (nTypeTag & ST_InBtl && INVITED_KEY_VALUE != it->m_Key)
			{
				//���ڿ�ս��
				if (nTypeTag & ST_CityMap)
				{
					if (IS_MAIN_CITY(SCENENPCID_2(it->m_MapID)))
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

// �������Ƿ�������ս�� [12/5/2009 Macro]
bool CBattleMgr::InChallegeBattle( int nCorpsID )
{
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		if (TYPE_BATTLE_CHALLEGE != it->m_Type)
		{
			continue;
		}
		if ( it->m_AttCorpsID == nCorpsID || it->m_DefCorpsID == nCorpsID )
		{
			return true;
		}
	}
	return false;
}

//ȡ��ָ��Key��ս����Ϣ
void CBattleMgr::GetBattle( KEY_TYPE vKey, int& vSrcCorpsID, int& vDesCorpsID, int& vType, int& vNpcID, int& vMapID )
{
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		if ( it->m_Key == vKey )
		{
			vSrcCorpsID = it->m_AttCorpsID;
			vDesCorpsID = it->m_DefCorpsID;
			vType = it->m_Type;
			vNpcID = it->m_NpcID;
			vMapID = it->m_MapID;
			break;
		}
	}
	return ;
}

//�ж�NPC�Ƿ���ս����
bool CBattleMgr::IsInBattle( int nNpcID )
{
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		if ( it->m_NpcID == nNpcID && it->m_Type == TYPE_BATTLE_SCRABBLE )
		{
			return true;
		}
	}
	return false;
}

//  [3/12/2010 GaoHong]
//��ȡָ��NPC�����͵�ս��Key
KEY_TYPE CBattleMgr::GetBattleKey( int nNpcID, int nType )
{
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		if ( it->m_NpcID == nNpcID && it->m_Type == nType )
		{
			return it->m_Key;
		}
	}
	return INVITED_KEY_VALUE;
}

// �õ�ս����ʼʱ��
int CBattleMgr::GetBattleBeginTime( int nNpcID, int nType )
{
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		if ( it->m_NpcID == nNpcID && it->m_Type == nType )
		{
			return it->m_BattleTime;
		}
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////
// BY DLC
// ս����������
void CBattleMgr::OnEventBattleOver(KEY_TYPE nKey)
{
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}
		if ( it->m_Key == nKey )
		{
			//m_BattleInfoList.erase(it);
			it->m_SynTag = DataTag_Del;
			if (it->m_Type == TYPE_BATTLE_SCRABBLE)
			{
				//CBidMgr::GetSingleton().SetBidOpen(it->m_NpcID);
			}
			break;
		}
	}
	return ;
}

/// �ҳ�ָ��ս����ĳ��Ӫ�ľ���
CCorps* CBattleMgr::GetBattleCorpsByCampID(KEY_TYPE nKey, int nCampID, int& nNpcID)
{
	int tnRetCorpsID = 0;
	CCorps* tpCorps = NULL;
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if ( it->m_Key == nKey )
		{
			nNpcID = it->m_NpcID;
			if (CAMP_1 == nCampID)
			{
				tnRetCorpsID = it->m_AttCorpsID;
			} 
			else if (CAMP_2 == nCampID)
			{
				tnRetCorpsID = it->m_DefCorpsID;
			}
			tpCorps = CCorpsManager::GetSingleton().GetCorpsByID( tnRetCorpsID );

			if (NULL == tpCorps)
			{
				LOG_ERROR( "corps", "Corps[%d] Not Found.[%s:%d]", tnRetCorpsID, __LK_FILE__, __LINE__ );
				return NULL;
			}
			return tpCorps; 
		}
	}
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//���ݿ�ͬ������
void CBattleMgr::LoadFromDB( int nStart, int nTotalCount )
{
	const char* pSqlstr = "select \
						  att_corps_id, \
						  def_corps_id, \
						  fight_type, \
						  npc_id, \
						  map_id, \
						  battle_key, \
						  battle_time from UMS_CORPS_BATTLE limit %d,%d ";
	CGateLogic::GetSingleton().ExecuteSql( em_dbsession_load_corpsbattle, nStart, nTotalCount, 3, SQL_NEED_CALLBACK, SELECT, 
		pSqlstr, nStart, COUNT_LOADCORPSBATTLE );
}

void CBattleMgr::OnSessionLoadFromDB( CMessage* pMessage, int nStart, int nTotalCount )
{
	LK_ASSERT( pMessage != NULL, return )
		CMessageExecuteSqlResponse3* tpMsg = (CMessageExecuteSqlResponse3 *) pMessage->msgpara();
	if ( tpMsg == NULL )
	{
		LOG_ERROR( "corps","[%s,%d] load corps_battle error, database error! ",__FUNCTION__, __LINE__ );
		printf( "[%s,%d] load corps_battle error, database error! ",__FUNCTION__, __LINE__ );
		exit( 0 );
	}
	int tcolnum = tpMsg->colcount();
	int trownum = tpMsg->rowcount();	
	if ( tcolnum != 7 )
	{
		LOG_ERROR( "corps","Load corps_battle failed!" );
		printf( "Load corps_battle failed! tcolnum=%d\n", tcolnum);
		exit( 0 );
	}
	if ( tpMsg->resultcode() == 1 )
	{
		for ( int i = 0; i < trownum; ++i )
		{	
			BattleInfo tBattleInfo;
			tBattleInfo.m_AttCorpsID = atoi( tpMsg->fieldvalue( i*tcolnum + 0 ).c_str() );	
			tBattleInfo.m_DefCorpsID = atoi( tpMsg->fieldvalue( i*tcolnum + 1 ).c_str() );	
			tBattleInfo.m_Type		= atoi( tpMsg->fieldvalue( i*tcolnum + 2 ).c_str() );	
			tBattleInfo.m_NpcID		= atoi( tpMsg->fieldvalue( i*tcolnum + 3 ).c_str() );	
			tBattleInfo.m_MapID		= atoi( tpMsg->fieldvalue( i*tcolnum + 4 ).c_str() );	
			tBattleInfo.m_Key		= atoi( tpMsg->fieldvalue( i*tcolnum + 5 ).c_str() );
			tBattleInfo.m_BattleTime = atoi( tpMsg->fieldvalue( i*tcolnum + 6 ).c_str() );

			
			if (0 == tBattleInfo.m_Key)
			{
				//����δ��ս������
				tBattleInfo.m_SynTag = DataTag_Syn;
				if (tBattleInfo.m_Type == TYPE_BATTLE_SCRABBLE)
				{
					//�����ȴ���ս�����ݣ�����NPC���۹ر�
					CBidMgr::GetSingleton().SetBidOpen(tBattleInfo.m_NpcID, false);
				}
			}
			else
			{
				//ɾ���Ѿ���ս������
				tBattleInfo.m_SynTag = DataTag_Del;
				//��ʱ��ս�����ݣ��϶����¾ɰ汾�Ѿ��л��ɹ���
				//����NPC״̬���Ѿ���ʼ����ϣ��ο����ݼ������̣�
				//NPC����״̬���ֲ���
				//CBidMgr::GetSingleton().SetBidOpen(tBattleInfo.m_NpcID);
			}
			
			m_BattleInfoList.push_back(tBattleInfo);

			
		}

		LOG_NOTICE("corps", "Load corps_battle data start %d num %d total %d", nStart, trownum, nTotalCount );

		if ( trownum < COUNT_LOADCORPSBATTLE )
		{
			if ( nTotalCount < nStart + trownum )
			{
				printf( "[%s,%d]load corps_battle error, incorrect number :%d total number:%d", __FUNCTION__, __LINE__, nStart + trownum, nTotalCount );
				LOG_ERROR( "corps","[%s,%d]load corps_battle error, incorrect number :%d total number:%d", __FUNCTION__, __LINE__, nStart + trownum, nTotalCount );
				exit( 0 );				
			}
		}
		else
		{
			if ( trownum + nStart < nTotalCount )
			{
				//�������ؾ���ս������
				LoadFromDB( nStart + trownum, nTotalCount );
			}			
		}

		// �������
		if ( trownum + nStart >= nTotalCount )
		{
			//printf( "load corps end, total number:%d", nTotalCount );
			LOG_NOTICE( "corps","Load corps_battle Complete, Total Number:%d", nTotalCount );
			
			CCorpservice::GetSingleton().StartLoadAllFromDB(TAB_CORPS);			 
		}
	}	
	else
	{
		printf( "[%s,%d] load corps_battle error, database error! ",__FUNCTION__, __LINE__ );
		LOG_ERROR( "corps","[%s,%d] load corps_battle error, database error! ",__FUNCTION__, __LINE__ );
		exit( 0 );
	}			   
}

//�������ݵ����ݿ�
int CBattleMgr::SynDataToDB()
{
	LOG_DEBUG("corps","%s %s ----------", __FUNCTION__, __FILE__);
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); )
	{		
		LOG_DEBUG("corps", "[TAG:%d]CORPS_BATTLE(att_corps_id %d, def_corps_id %d, fight_type %d, npc_id %d, map_id %d, battle_key %lld, battle_time %d)", 
			it->m_SynTag,
			it->m_AttCorpsID, 
			it->m_DefCorpsID,
			it->m_Type,
			it->m_NpcID,
			it->m_MapID,
			it->m_Key,
			it->m_BattleTime);
		if (DataTag_New == it->m_SynTag)
		{
			const char *tpSql0 = "insert into UMS_CORPS_BATTLE(att_corps_id, def_corps_id, fight_type, npc_id, map_id, battle_key, battle_time)\
								values( '%d', '%d', '%d', '%d', %d, %lld, '%d' ) ";
			CGateLogic::GetSingleton( ).ExecuteSql(
				em_dbsession_update_corpsbattle, 0, 0, 3, SQL_NONE, INSERT, tpSql0, 
				it->m_AttCorpsID, 
				it->m_DefCorpsID,
				it->m_Type,
				it->m_NpcID,
				it->m_MapID,
				it->m_Key,
				it->m_BattleTime);
			it->m_SynTag = DataTag_Syn;

			++ it;
		}
		else if (DataTag_Syn == it->m_SynTag)
		{
			++ it;
		}
		else if (DataTag_Upd == it->m_SynTag)
		{
			const char *tpSql2 = "update UMS_CORPS_BATTLE set \
					att_corps_id=%d, \
					def_corps_id=%d, \
					map_id='%d', \
					battle_key='%lld', \
					battle_time=%d where npc_id=%d and fight_type=%d ";
			CGateLogic::GetSingleton( ).ExecuteSql(
				em_dbsession_update_corpsbattle, 0, 0, 3, SQL_NONE, UPDATE, tpSql2,
				it->m_AttCorpsID, 
				it->m_DefCorpsID,
				it->m_MapID,
				it->m_Key,
				it->m_BattleTime,
				it->m_NpcID,
				it->m_Type);
			it->m_SynTag = DataTag_Syn;

			++ it;
		}
		else if (DataTag_Del == it->m_SynTag)
		{
			const char *tpSql3 = "delete from UMS_CORPS_BATTLE where npc_id=%d and fight_type=%d";
			CGateLogic::GetSingleton( ).ExecuteSql(
				em_dbsession_update_corpsbattle, 0, 0, 3, SQL_NONE, DELETE, tpSql3,
				it->m_NpcID, 
				it->m_Type);

			it = m_BattleInfoList.erase(it);
		}
		else
		{
			++ it;
			LOG_ERROR("corps", "INVALID m_SynTag:%d in m_BattleInfoList", it->m_SynTag);
		}
	}
	return 0;
}


//�����ų����ͱ���֪ͨ [2/3/2010 Macro]
void CBattleMgr::SendJoinNotice()
{
	CCorpsManager *pCorpsMgr = CCorpsManager::GetSingletonPtr();
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		// ��������������
		if ( it->m_Type != TYPE_BATTLE_SCRABBLE )
			continue;

		// �Ѿ���ս�Ĳ���Ҫ
		if ( it->m_Key != INVITED_KEY_VALUE )
			continue;

		// ����Ƿ����������
		if ( it->m_MapID == INVALID_MAP_ID || it->m_NpcID == INVALID_OBJ_ID )
			continue;

		// ��ս˫���������ݶ�����
		CCorps* tpSrcCorps = pCorpsMgr->GetCorpsByID( it->m_AttCorpsID );
		CCorps* tpDesCorps = pCorpsMgr->GetCorpsByID( it->m_DefCorpsID );
		if ( tpSrcCorps == NULL || tpDesCorps == NULL )
			continue;

		int tNpcID = SCENENPCID( it->m_NpcID, tpSrcCorps->GetCorpsCountryID() );

		int tSrcType = ( tpSrcCorps->GetUnionID() == INVALID_OBJ_ID )? (int) emTypeCorps : (int) emTypeUnion;
		int tDesType = ( tpDesCorps->GetUnionID() == INVALID_OBJ_ID )? (int) emTypeCorps : (int) emTypeUnion;

		// ����������
		CCorpservice::GetSingleton().SendBattleJoinNotice( tpSrcCorps->GetCorpsCountryID(), tNpcID, 
			tpDesCorps->GetCorpsName(), tpSrcCorps->GetRooterID(), tSrcType );
		
		// ���ط�����
		CCorpservice::GetSingleton().SendBattleJoinNotice( tpDesCorps->GetCorpsCountryID(), tNpcID, 
			tpSrcCorps->GetCorpsName(), tpDesCorps->GetRooterID(), tDesType );
	}
}

void CBattleMgr::OnTimerCheckState()
{
	CCorpsManager *pCorpsMgr = CCorpsManager::GetSingletonPtr();
	BattleInfoList::iterator it = m_BattleInfoList.begin();
	for ( ; it != m_BattleInfoList.end(); ++ it )
	{
		if (DataTag_Del == it->m_SynTag)
		{
			continue;
		}

		// ��������������
		if ( it->m_Type != TYPE_BATTLE_SCRABBLE )
			continue;

		// �Ѿ���ս�Ĳ�����
		if ( it->m_Key != INVITED_KEY_VALUE )
			continue;

		// ����Ƿ����������
		if ( it->m_MapID == INVALID_MAP_ID || it->m_NpcID == INVALID_OBJ_ID )
			continue;

		// ��ս˫���������ݶ�����
		CCorps* tpSrcCorps = pCorpsMgr->GetCorpsByID( it->m_AttCorpsID );
		CCorps* tpDesCorps = pCorpsMgr->GetCorpsByID( it->m_DefCorpsID );
		if ( tpSrcCorps == NULL || tpDesCorps == NULL )
			continue;

		// ʣ�»�δ��ս��������
		if (time(NULL) >= it->m_BattleTime)
		{
			//��սʱ���ѵ�
			CMessage tMessage;
			CMessageCorpsStartBattleRequest tPara;
			tMessage.mutable_msghead()->set_messageid( ID_S2G_REQUEST_STARTCOPRSBATTLE );//8671
			tMessage.set_msgpara( (long) &tPara );

			tPara.set_npcid( SCENENPCID_2(it->m_NpcID) );
			tPara.set_battleid( SCENENPCID_2(it->m_MapID) );

			CCorpservice::GetSingleton().OnMessageStartBattleRequest( SCENESERVERID(it->m_NpcID), &tMessage );
		}
	}
}

//bool CBattleMgr::CorpsIsInBattle(int nCorpsID)
//{
//	BattleInfoList::iterator it = m_BattleInfoList.begin();
//	for ( ; it != m_BattleInfoList.end(); ++ it )
//	{
//		if (DataTag_Del == it->m_SynTag)
//		{
//			continue;
//		}
//		if (it->m_Key != INVITED_KEY_VALUE)
//		{
//			if (it->m_AttCorpsID == nCorpsID ||
//				it->m_DefCorpsID == nCorpsID)
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}