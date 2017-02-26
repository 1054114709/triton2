#include "stdafx.hpp"
#include "rankmodule.h"
#include "rankmessage_pb.hxx.pb.h"
#include "ranktype.h"
#include "propertymodule.h"
#include "scenelogic.h"
#include "gmmodule.h"
#include "achievemodule.h"
#include "worldmodule.h"

template<> CRankModule* CSingleton< CRankModule >::spSingleton = NULL;
//char CRankModule::sModuleName[ NAME_LENGTH ] = "RankModuel";


// ����������
void CRankModule::OnLaunchServer( )
{
	OnLoadConfig( );
}

unsigned int CRankModule::CountSize( )
{
	return sizeof(CRankModule);
}

// �˳�������
void CRankModule::OnExitServer( )
{

}

// ������Timer
void CRankModule::OnTimer( unsigned int vTickCount, unsigned int vTickOffset )
{

}

// ��������
int CRankModule::OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName )
{
	return 0;
}

// ·����Ϣ
void CRankModule::OnRouterMessage( CMessage* pMessage )
{

}

// �ͻ��˷�����Ϣ
void CRankModule::OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	switch ( pMessage->msghead().messageid() )
	{
	case ID_C2S_REQUEST_PLAYERRANK:
		{
			OnClientMessagePlayerRankRequest( pPlayer, pMessage );
			break;
		}
	default:
		{
			break;
		}
	}
}

// ����ʵ��
void CRankModule::OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst )
{
	//
	if ( pEntity->IsPlayer() == false )
	{
		return ;
	}
	CEntityPlayer* tpPlayer = ( CEntityPlayer* ) pEntity;

	// �����������ص㣬������
	if ( ( IS_GLOBAL_SCENESERVER( tpPlayer->GetLineID() ) == false ) && ( IS_DUNGEONSERVER_LINE( tpPlayer->GetLineID() ) == false ) )
	{		
		CMessage tMessage;
		CMessageObtainTopTenRequest tPara;
		tMessage.mutable_msghead()->set_messageid( ID_S2G_REQUEST_TOPTEN );
		tMessage.set_msgpara( (long) &tPara );
		tPara.set_charid( tpPlayer->GetCharID() );
		CSceneLogic::GetSingleton().Send2Gate( &tMessage );
	}
	// ����ƺ�
	DisposTitleList(tpPlayer);
}

// ����ʵ��
void CRankModule::OnDestroyEntity( CEntity* pEntity, int vCode )
{

}

// �洢����
// �ϱ���Ϣ ������������
bool CRankModule::OnSaveData( CEntityPlayer* pPlayer, int vSaveCode )
{
	if ( vSaveCode == SAVE_RETURN2GATE || vSaveCode == SAVE_LEAVEGAME || vSaveCode == SAVE_KICKOUT || vSaveCode == SAVE_FORCEEXIT)
		SendPersonalRankInfoToGate( pPlayer );

	return true;
}

// ��������
void CRankModule::OnLoadConfig( )
{
	// ��־
	RANK_LOG* tpCfg = CSceneCfgManager::GetSingletonPtr()->GetRank_log();
	if( tpCfg != NULL )
	{
		INIT_ROLLINGFILE_LOG( tpCfg->mIdentifier, tpCfg->mDirectory, (LogLevel)tpCfg->mPriority, tpCfg->mMaxfilesize, tpCfg->mMaxbackupindex );
	}
}


// ���͸������а���Ϣ������(���������ߵ�ʱ�����)
int CRankModule::SendPersonalRankInfoToGate( CEntityPlayer* pPlayer )
{
	LK_ASSERT(pPlayer != NULL, return -1 );

	// û���� ֱ��K��
	if (pPlayer->GetNationality() == 0)
		return -1;

	// GM����������
	if ( CGMModule::GetSingleton().IsGm( pPlayer->GetGmStatus() ) )
		return -2;

	CMessage tMessage;
	CMessagePersonalRankInfoNotify tRankPara;
	tRankPara.set_flag(0);

	tMessage.mutable_msghead()->set_messageid( ID_S2G_NOTIFY_PERSONALRANKINFO );
	tMessage.set_msgpara( (uint32)&tRankPara );

	PBPersonalRankInfo* pSinglePersonInfo = tRankPara.add_personalranks();
	SetPersonalRank( pPlayer, pSinglePersonInfo, REFRESHTYPE_ALL );
	
	CSceneLogic::GetSingletonPtr()->Send2Gate( &tMessage );

	return 0;
}

// ���Ͷ�����а���Ϣ������ (��������Ҫ��)
int CRankModule::SendPersonalRankInfoToGate( std::vector<CEntityPlayer*>& rPlayers, int nType )
{
	CMessage tMessage;
	CMessagePersonalRankInfoNotify tRankPara;

	tMessage.mutable_msghead()->set_messageid( ID_S2G_NOTIFY_PERSONALRANKINFO );
	tMessage.set_msgpara( (uint32)&tRankPara );

	int n = 0;
	LOG_NOTICE("rank", "%s: SEND GATE DATA! total=%d", __FUNCTION__, rPlayers.size() );
	for( std::vector<CEntityPlayer*>::iterator it = rPlayers.begin(); it != rPlayers.end(); ++it )
	{
		// û���� ֱ��K��
		if ((*it)->GetNationality() == 0)
			continue;

		// GM�˺� ����������
		if ( CGMModule::GetSingleton().IsGm( (*it)->GetGmStatus() ) )
			continue;

		if (nType == REFRESHTYPE_DAYLY) // �����ÿ��ˢ�� �����ʵʱ����Ҫ������
		{
			CPropertyPlayer* tpProPlayer = (CPropertyPlayer*)(*it)->GetProperty();
			// ��յ����ɱ����
			tpProPlayer->SetTodayKillEnemyNumIn(0);
			tpProPlayer->SetTodayKillEnemyNumOut(0);

			// ��ս��չ�ѫ
			tpProPlayer->SetTodayHonor(0);
		}

		PBPersonalRankInfo* pSinglePersonInfo = tRankPara.add_personalranks();
		SetPersonalRank( *it, pSinglePersonInfo, nType );
		if ( ++n >= SINGLE_PAK_LINE )
		{
			tRankPara.set_flag(1);
			tRankPara.set_rtype( nType );
			LOG_NOTICE("rank", "%s: SEND GATE DATA! n=%d", __FUNCTION__, n );
			CSceneLogic::GetSingletonPtr()->Send2Gate( &tMessage );
			tRankPara.Clear();
			n = 0;
		}
	}

	tRankPara.set_isover(1);
	tRankPara.set_flag(1);
	tRankPara.set_rtype( nType );
	LOG_NOTICE("rank", "%s 2: SEND GATE DATA! n=%d", __FUNCTION__, n );
	CSceneLogic::GetSingletonPtr()->Send2Gate( &tMessage );

	return 0;
}

void CRankModule::SetPersonalRank( CEntityPlayer* pPlayer, PBPersonalRankInfo* pInfoTobeSet, int nType )
{
	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	CStorage* pStorage = pProperty->GetStorage();
	LK_ASSERT(pStorage!=NULL, return );
	LOG_NOTICE("rank", "%s player=%s", __FUNCTION__, pPlayer->GetCharNameShow() );

	pInfoTobeSet->Clear();

	pInfoTobeSet->set_charid( pPlayer->GetCharID() );
	pInfoTobeSet->set_charname( pPlayer->GetCharName() );
	pInfoTobeSet->set_country( pPlayer->GetNationality() );
	pInfoTobeSet->set_metier( pPlayer->GetMetier() );
	pInfoTobeSet->set_title( 0 );	
	if ( nType  == REFRESHTYPE_DAYLY || nType == REFRESHTYPE_ALL ) // ��ÿ��ˢ�� ��������Щ��������
	{
		pInfoTobeSet->set_level( pPlayer->GetLevel() );
		pInfoTobeSet->set_exp( pPlayer->GetExp() );
		pInfoTobeSet->set_money( (pPlayer->GetMoney() + pProperty->GetStorageMoney()) );
		pInfoTobeSet->set_boundedmoney( (pPlayer->GetBindMoney() + pProperty->GetStorageBindMoney()) );
		pInfoTobeSet->set_honor( pPlayer->GetHonor() );
		pInfoTobeSet->set_killenemynumin( ((CPropertyPlayer*)pPlayer->GetProperty())->GetKillNumIn() );
		pInfoTobeSet->set_killenemynumout( ((CPropertyPlayer*)pPlayer->GetProperty())->GetKillNumOut() );
		pInfoTobeSet->set_completedtasks( ((CPropertyPlayer*)pPlayer->GetProperty())->GetCompletedTaskNum() );
		pInfoTobeSet->set_dienum( ((CPropertyPlayer*)pPlayer->GetProperty())->GetDieNum() );
		int nOnlineSecs = pPlayer->GetOnlineTime() + ((unsigned int)time(0) - pPlayer->GetLastLoginTime());
		pInfoTobeSet->set_onlinetime((int)(nOnlineSecs/60));
		pInfoTobeSet->set_pantaomark( GetPantaoMark( pPlayer ) );
		pInfoTobeSet->set_longgongmark( GetLonggongMark( pPlayer ) );
		pInfoTobeSet->set_originrelivetimes( pProperty->GetOriginReliveTimes() );
		pInfoTobeSet->set_killsamenationnum( pProperty->GetKillSameNationNum() );
		pInfoTobeSet->set_killogrenum( pProperty->GetKillOgreNum() );
		pInfoTobeSet->set_upfailnum( pProperty->GetUpFailNum() );
		int tmp = 0;
		pProperty->GetRepetion()->GetIntData( _REPE_DAYANTA_INDEX_, 0, &tmp);
		pInfoTobeSet->set_dayanta(tmp);
		tmp = 0;
//		pProperty->GetRepetion()->GetIntData( _REPE_LIANHUADONG_MAP_ID_, 0, &tmp);
		pProperty->GetRepetion()->GetIntData( _REPE_LIANHUADONG_INDEX_, 0, &tmp);
		pInfoTobeSet->set_lianhuadong(tmp);
		tmp = 0;
//		pProperty->GetRepetion()->GetIntData( _REPE_HUANGFENGDONG_MAP_ID_, 0, &tmp);
		pProperty->GetRepetion()->GetIntData( _REPE_HORNETSHOLE_INDEX_, 0, &tmp);
		pInfoTobeSet->set_huangfengdong(tmp);

		int tAchiveID = CAchieveModule::GetSingleton().GetAchieveDataUnit(pPlayer->GetCharID());
		CAchieveDataUnit* tpAchive = (CAchieveDataUnit*)CSceneObjManager::GetSingleton().GetObject(tAchiveID);
		if (tpAchive != NULL)
		{
			pInfoTobeSet->set_achivepoint( tpAchive->mTotalPoint );
		}
		pInfoTobeSet->set_charmvalue(pProperty->GetCharmValue());

		// ���÷��и�������
		pProperty->GetRepetion()->GetIntData( _REPE_FLY_WAR, 0, &tmp);
		pInfoTobeSet->set_flydungmark(tmp);
		pInfoTobeSet->set_zhangong(pProperty->GetTotalWar());
		pInfoTobeSet->set_tongshuai( pProperty->mWizard.GetWizardPoint(WIZARD_TACTICS)+pProperty->mWizard.GetWizardIncrease(WIZARD_TACTICS) +
			pProperty->mWizard.GetWizardPoint(WIZARD_POWER)+pProperty->mWizard.GetWizardIncrease(WIZARD_POWER) +
			pProperty->mWizard.GetWizardPoint(WIZARD_WISDOM)+pProperty->mWizard.GetWizardIncrease(WIZARD_WISDOM) );

		pInfoTobeSet->set_zhiguo( pProperty->mWizard.GetWizardPoint(WIZARD_ARTS)+pProperty->mWizard.GetWizardIncrease(WIZARD_ARTS) +
			pProperty->mWizard.GetWizardPoint(WIZARD_EDUCATE)+pProperty->mWizard.GetWizardIncrease(WIZARD_EDUCATE) +
			pProperty->mWizard.GetWizardPoint(WIZARD_POLITICS)+pProperty->mWizard.GetWizardIncrease(WIZARD_POLITICS));
		
		pInfoTobeSet->set_wisall( pInfoTobeSet->tongshuai()+pInfoTobeSet->zhiguo() );
		tmp = 0;
		pProperty->GetRepetion()->GetIntData( _REPE_TOWNER_INDEX_, 0, &tmp);
		pInfoTobeSet->set_yunxiao(tmp);	
		if ( pPlayer->GetSex() == 3 )// ֻ��Ů�������
			pInfoTobeSet->set_weekinccharm( pProperty->GetWeekIncCharm() );

		tmp = 0;
		pProperty->GetRepetion()->GetIntData( _REPE_TOWNER_INDEX_, 2, &tmp);
		pInfoTobeSet->set_yunxiaolevel(tmp);	

		pInfoTobeSet->set_xianyuanmark(pProperty->GetSlavePoint());
		pInfoTobeSet->set_shide(pProperty->GetMasterPoint());
		pInfoTobeSet->set_chushitu(pProperty->GetSlaveNum());
        
		tmp = 0;
		pProperty->GetRepetion()->GetIntData( _REPE_WUDIDONG_INDEX_, 0, &tmp);
		pInfoTobeSet->set_wudidongmark(tmp);

		tmp = 0;
		pProperty->GetRepetion()->GetIntData( _REPE_LASTONE_INDEX_ , 6, &tmp);
		pInfoTobeSet->set_daluandou(tmp);

		tmp = 0;
		pProperty->GetRepetion()->GetIntData( _REPE_LASTONE_INDEX_ , 11, &tmp);
		pInfoTobeSet->set_daluandoutotal(tmp);

		tmp = 0;
		pProperty->GetRepetion()->GetIntData( _REPE_GLOBALWAR_INDEX_ , 4, &tmp);
		pInfoTobeSet->set_globalwar(tmp);

		CSpiritInfo& rSpiritInfo = pProperty->GetSpiritInfo();
		int nSpiritScore = rSpiritInfo.GetScore();
		pInfoTobeSet->set_spiritscore(nSpiritScore);
	}

	if ( nType == REFRESHTYPE_HALFHOUR || nType == REFRESHTYPE_ALL ) // ��Сʱˢ��
	{
		pInfoTobeSet->set_todaykillenemynumin( pProperty->GetTodayKillEnemyNumIn() );
		pInfoTobeSet->set_todaykillenemynumout( pProperty->GetTodayKillEnemyNumOut() );
		LOG_DEBUG("rank", "player %s send2Gate: in:%d out:%d", pPlayer->GetCharNameShow()
			,pProperty->GetTodayKillEnemyNumIn(), pProperty->GetTodayKillEnemyNumOut());
		pInfoTobeSet->set_todayhonor( pProperty->GetTodayHonor() );
	}
}

// ����������Ϣ
void CRankModule::OnGateMessage(CMessage *pMessage)
{
	switch ( pMessage->msghead().messageid() )
	{
	case ID_S2C_RESPONSE_PLAYERRANK:
		{
			OnGateMessagePlayerRankResponse( pMessage );
			break;
		}
	case ID_G2S_REQUEST_PERSONALRANKINFO:
		{
			OnGateMessageAskPlayerInfoRequest( pMessage );
			break;
		}
	case ID_G2S_NOTIFY_NEWTOPTEN:
		{
			OnGateMessageNewTopTenRequest( pMessage );
			break;
		}
	case ID_G2S_RESPONSE_TOPTEN:
		{
			OnGateMessageObtainTopTenResponse( pMessage );
			break;
		}
	default:
		{
			break;
		}
	}
}

// �ͻ���ȡ�����б�
int CRankModule::OnClientMessagePlayerRankRequest( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer!=NULL, return -1);
	// ������û���� ֱ��return 
	if (pPlayer->GetNationality() == 0)
	{
		return -1;
	}
	CMessageGetPlayerRankRequest* pLevelRankReq = (CMessageGetPlayerRankRequest*)pMessage->msgpara();
	pLevelRankReq->set_charid( pPlayer->GetCharID() );
	CSceneLogic::GetSingletonPtr()->Send2Gate( pMessage );

	return 0;
}


// ���ػ�Ӧȡ�ȼ������б�
int CRankModule::OnGateMessagePlayerRankResponse( CMessage* pMessage )
{
	CMessageGetPlayerRankResponse* pLevelRankRes = (CMessageGetPlayerRankResponse*)pMessage->msgpara();
	CEntityPlayer* pPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID(pLevelRankRes->charid());
	if (pPlayer == NULL)
		return -1;

	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	int tmp = 0;

	// ת���ƺ�
	for ( int i = 0; i < TOPTEN && i < pLevelRankRes->rankinfo_size(); i ++ )
	{
		int tTitleID = 0;
		ConvertRankToTitle( pLevelRankRes->ranktype(), i, tTitleID );
		PBSingleRankInfo* tpRankInfo = pLevelRankRes->mutable_rankinfo( i );
		tpRankInfo->set_title( tTitleID );
	}

	// �����ҵ���ֵ
	switch( pLevelRankRes->ranktype() )
	{
	case RANKTYPE_LEVEL_ALL:
	case RANKTYPE_LEVEL_MYNATION:
		{
			pLevelRankRes->set_myrankvalue(pPlayer->GetLevel());
			break;
		}
	case RANKTYPE_MONEY_NOBIND:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetMoney()+pProperty->GetStorageMoney());
			break;
		}
	case RANKTYPE_MONEY_ALL:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetMoney()+pProperty->GetStorageMoney()+pProperty->GetBindMoney()+pProperty->GetStorageBindMoney());
			break;
		}
	case RANKTYPE_KILL_PROT_NATION:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetKillNumIn());
			break;
		}
	case RANKTYPE_KILL_OUT:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetKillNumOut());
			break;
		}
	case RANKTYPE_KILL_TOTAL:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetKillNumOut()+pProperty->GetKillNumIn());
			break;
		}
	case RANKTYPE_HONER_MYNATION:
	case RANKTYPE_HONOR_ALL:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetHonor());
			break;
		}
	case RANKTYPE_DIE:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetDieNum());
			break;
		}
	case RANKTYPE_END_TASK:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetCompletedTaskNum());
			break;
		}
	case RANKTYPE_ONLINE_TIME:
		{
			pLevelRankRes->set_myrankvalue((pPlayer->GetOnlineTime() + ((unsigned int)time(0) - pPlayer->GetLastLoginTime()))/60);
			break;
		}
	case RANKTYPE_PANTAO_MARK:
		{
			pLevelRankRes->set_myrankvalue( GetPantaoMark(pPlayer) );
			break;
		}
	case RANKTYPE_LONGGONG_MARK:
		{
			pLevelRankRes->set_myrankvalue( GetLonggongMark(pPlayer) );
			break;
		}
	case RANKTYPE_ORIGINRELIVETIMES:
		{
			pLevelRankRes->set_myrankvalue( pProperty->GetOriginReliveTimes() );
			break;
		}
	case RANKTYPE_KILLSAMENATIONNUM:
		{
			pLevelRankRes->set_myrankvalue( pProperty->GetKillSameNationNum() );
			break;
		}
	case RANKTYPE_KILLOGRENUM:
		{
			pLevelRankRes->set_myrankvalue( pProperty->GetKillOgreNum() );
			break;
		}
	case RANKTYPE_UPFAILNUM:
		{
			pLevelRankRes->set_myrankvalue( pProperty->GetUpFailNum() );
			break;
		}
	case RANKTYPE_KILL_PROT_NATION_TODAY:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetTodayKillEnemyNumIn());
			break;
		}
	case RANKTYPE_KILL_OUT_TODAY:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetTodayKillEnemyNumOut());
			break;
		}
	case RANKTYPE_KILL_TOTAL_TODAY:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetTodayKillEnemyNumIn()+pProperty->GetTodayKillEnemyNumOut());
			break;
		}
	case RANKTYPE_HONOR_ALL_TODAY:
	case RANKTYPE_HONER_MYNATION_TODAY:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetTodayHonor());
			break;
		}
	case RANKTYPE_DAYANTA:
		{
			tmp = 0;
//			pProperty->GetRepetion()->GetIntData( _REPE_DAYANTA_MAP_ID_, 0, &tmp);
			pProperty->GetRepetion()->GetIntData( _REPE_DAYANTA_INDEX_, 0, &tmp);
			pLevelRankRes->set_myrankvalue(tmp);
			break;
		}
	case RANKTYPE_LIANHUADONG:
		{
			tmp = 0;
//			pProperty->GetRepetion()->GetIntData( _REPE_LIANHUADONG_MAP_ID_, 0, &tmp);
			pProperty->GetRepetion()->GetIntData( _REPE_LIANHUADONG_INDEX_, 0, &tmp);
			pLevelRankRes->set_myrankvalue(tmp);
			break;
		}
	case RANKTYPE_HUANGFENGDONG:
		{
			tmp = 0;
//			pProperty->GetRepetion()->GetIntData( _REPE_HUANGFENGDONG_MAP_ID_, 0, &tmp);
			pProperty->GetRepetion()->GetIntData( _REPE_HORNETSHOLE_INDEX_, 0, &tmp);
			pLevelRankRes->set_myrankvalue(tmp);
			break;
		}
	case RANKTYPE_ACHIVE_POINT:
		{
			int tAchiveID = CAchieveModule::GetSingleton().GetAchieveDataUnit(pPlayer->GetCharID());
			CAchieveDataUnit* tpAchive = (CAchieveDataUnit*)CSceneObjManager::GetSingleton().GetObject(tAchiveID);
			if (tpAchive != NULL)
			{
				pLevelRankRes->set_myrankvalue(tpAchive->mTotalPoint);
			}
			break;
		}
	case RANKTYPE_CHARM_VALUE:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetCharmValue());
			break;
		}
	case RANKTYPE_WORLD_WEEKINCCHARM:
	case RANKTYPE_CAMP_WEEKINCCHARM:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetWeekIncCharm());
			break;
		}
	case RANKTYPE_FLY_FB_MARK:
		{
			pProperty->GetRepetion()->GetIntData( _REPE_FLY_WAR, 0, &tmp);
			pLevelRankRes->set_myrankvalue(tmp);
			break;
		}
	// ��Щ���͵����а����������أ�����myvalue���Դ����ش�����
	case RANKTYPE_FAMILY_PVP:
	case RANKTYPE_CORPS_PVP	 :
	case RANKTYPE_FAMILY_TAO:
	case RANKTYPE_CORPSBOSS_SCORE:
	case RANKTYPE_CORPSCOLLECT_ACTIVE:
		{
			break;
		}
	case RANKTYPE_ZHANGONG:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetTotalWar());
			break;
		}
	case RANKTYPE_ZHIGUO:
		{
			pLevelRankRes->set_myrankvalue(pProperty->mWizard.GetWizardPoint(WIZARD_TACTICS)+pProperty->mWizard.GetWizardIncrease(WIZARD_TACTICS) +
				pProperty->mWizard.GetWizardPoint(WIZARD_POWER)+pProperty->mWizard.GetWizardIncrease(WIZARD_POWER) +
				pProperty->mWizard.GetWizardPoint(WIZARD_WISDOM)+pProperty->mWizard.GetWizardIncrease(WIZARD_WISDOM)
				);
			break;
		}
	case RANKTYPE_TONGSHUAI:
		{
			pLevelRankRes->set_myrankvalue(pProperty->mWizard.GetWizardPoint(WIZARD_ARTS)+pProperty->mWizard.GetWizardIncrease(WIZARD_ARTS) +
				pProperty->mWizard.GetWizardPoint(WIZARD_EDUCATE)+pProperty->mWizard.GetWizardIncrease(WIZARD_EDUCATE) +
				pProperty->mWizard.GetWizardPoint(WIZARD_POLITICS)+pProperty->mWizard.GetWizardIncrease(WIZARD_POLITICS)
				);
			break;
		}
	case RANKTYPE_WIS:
		{
			pLevelRankRes->set_myrankvalue( pProperty->mWizard.GetWizardPoint(WIZARD_TACTICS)+pProperty->mWizard.GetWizardIncrease(WIZARD_TACTICS) +
				pProperty->mWizard.GetWizardPoint(WIZARD_POWER)+pProperty->mWizard.GetWizardIncrease(WIZARD_POWER) +
				pProperty->mWizard.GetWizardPoint(WIZARD_WISDOM)+pProperty->mWizard.GetWizardIncrease(WIZARD_WISDOM) +	
				pProperty->mWizard.GetWizardPoint(WIZARD_ARTS)+pProperty->mWizard.GetWizardIncrease(WIZARD_ARTS) +
				pProperty->mWizard.GetWizardPoint(WIZARD_EDUCATE)+pProperty->mWizard.GetWizardIncrease(WIZARD_EDUCATE) +
				pProperty->mWizard.GetWizardPoint(WIZARD_POLITICS)+pProperty->mWizard.GetWizardIncrease(WIZARD_POLITICS)
				);
			break;
		}
	case RANKTYPE_YUNXIAO:
		{
			int tmp=0;
			pProperty->GetRepetion()->GetIntData( _REPE_TOWNER_INDEX_, 0, &tmp);
			pLevelRankRes->set_myrankvalue( tmp);	
			break;
		}
	case RANKTYPE_SHIDE:
		{
			pLevelRankRes->set_myrankvalue( pProperty->GetMasterPoint());	
			break;
		}
	case RANKTYPE_XIANYUANMARK:
		{
			pLevelRankRes->set_myrankvalue( pProperty->GetSlavePoint());	
			break;
		}
	case RANKTYPE_CHUSHITU:
		{
			pLevelRankRes->set_myrankvalue( pProperty->GetSlaveNum());	
			break;
		}
	case RANKTYPE_YUNXIAOTALEVEL:
		{
			int tmp = 0;
			pProperty->GetRepetion()->GetIntData( _REPE_TOWNER_INDEX_, 2, &tmp);
			pLevelRankRes->set_myrankvalue( tmp);	
			break;
		}
	case RANKTYPE_CAMPCHARM_LASTWEEK:
		{
			pLevelRankRes->set_myrankvalue(pProperty->GetLastWeekIncCharm());
			break;
		}
	case RANKTYPE_WUDIDONG:
		{
			int tmp=0;
			pProperty->GetRepetion()->GetIntData( _REPE_WUDIDONG_INDEX_, 0, &tmp);
			pLevelRankRes->set_myrankvalue( tmp);	
			break;
		}
	case RANKTYPE_LASTONE:
		{
			int tmp = 0;
			pProperty->GetRepetion()->GetIntData( _REPE_LASTONE_INDEX_, 6, &tmp);
			pLevelRankRes->set_myrankvalue(tmp);
			break;
		}
	case RANKTYPE_TOTAL_LASTONE:
		{
			int tmp = 0;
			pProperty->GetRepetion()->GetIntData( _REPE_LASTONE_INDEX_,11, &tmp);
			pLevelRankRes->set_myrankvalue(tmp);
			break;
		}
	case RANKTYPE_GLOBALWAR:
		{
			int tmp = 0;
			pProperty->GetRepetion()->GetIntData( _REPE_GLOBALWAR_INDEX_,4, &tmp);
			pLevelRankRes->set_myrankvalue(tmp);
			break;
		}
	case RANKTYPE_SPIRIT:
		{
			CSpiritInfo& rSpiritInfo = pProperty->GetSpiritInfo();
			int nSpiritScore = rSpiritInfo.GetScore();
			pLevelRankRes->set_myrankvalue(nSpiritScore);
		}
		break;
	default:
		{
			LOG_ERROR("rank", "in OnGateMessagePlayerRankResponse err type:%d", pLevelRankRes->ranktype());
			return -1;
		}
	}
	CSceneLogic::GetSingletonPtr()->Send2Player( pLevelRankRes->charid(), pMessage );
	return 0;
}

// �����ʳ���Ҫ�������
int CRankModule::OnGateMessageAskPlayerInfoRequest( CMessage* pMessage )
{
	CMessagePersonalRankInfoRequest* tpReq = ( CMessagePersonalRankInfoRequest* ) pMessage->msgpara();

	LOG_NOTICE("rank", "%s: GATE ASK DATA! ", __FUNCTION__ );
	std::vector<CEntityPlayer*> tPlayers;
	CSceneLogic::GetSingleton().GetPlayersInScene( tPlayers );
	SendPersonalRankInfoToGate( tPlayers, tpReq->rtype() );

	// ���ϴ��ϰ��ǰ10���Q̖���U����ˢ���°�
	// ÿ��ˢ�´���ƺţ���Сʱˢ����ʱ������
	if ( tpReq->rtype() == REFRESHTYPE_DAYLY )
		RepealOldRankTitle( pMessage );
	
	return 0;
}

// ˢ�����а�ǰ���ϴ����а�ƺ�����

int CRankModule::RepealOldRankTitle( CMessage* pMessage )
{
	if ( pMessage == NULL ) return -1;
	CMessagePersonalRankInfoRequest* tpReq = ( CMessagePersonalRankInfoRequest* ) pMessage->msgpara();

	for ( int i = 0; i < tpReq->toptenlist_size(); i ++ )
	{
		PBRankTopTen* tpTopTen = tpReq->mutable_toptenlist( i );
		for ( int j = 0; j < tpTopTen->charlist_size(); j ++ )
		{
			CEntityPlayer* tpPlayer = ( CEntityPlayer* ) CSceneLogic::GetSingleton().GetPlayerByCharID( tpTopTen->charlist( j ) );
			if ( tpPlayer == NULL )
			{
				continue;
			}

			int tTitleID = 0;
			ConvertRankToTitle( tpTopTen->ranktype(), j, tTitleID );
			CPropertyPlayer* tpProperty = ( CPropertyPlayer* ) tpPlayer->GetProperty();

			if( tTitleID == 0 )
				continue;

			if ( tpProperty->HasTitle( tTitleID ) == false )
				continue;

			tpProperty->RemoveTitle( tTitleID ); 
			CPropertyModule::GetSingleton().SendNotifyClientUpdateTitle( tpPlayer, TITLE_DELETE, tTitleID );

			if ( tTitleID == tpProperty->GetCurrentTitle() )
			{
				tpPlayer->NotifyPropertyRefresh();
				tpProperty->SetCurrentTitle( 0 );
				CPropertyModule::GetSingleton().SendNotifyUpdateCurrentTitle( tpPlayer, 0 );
			}				
		}				
	}

	return 0;
}

int CRankModule::OnGateMessageNewTopTenRequest(CMessage *pMessage)
{
	if ( pMessage == NULL ) return -1;

	CMessageNewRankTopTenNotify* tpNotify = ( CMessageNewRankTopTenNotify* ) pMessage->msgpara();

	for ( int i = 0; i < tpNotify->toptenlist_size(); i ++ )
	{
		PBRankTopTen* tpTopTen = tpNotify->mutable_toptenlist( i );
		for ( int j = 0; j < tpTopTen->charlist_size(); j ++ )
		{
			CEntityPlayer* tpPlayer = ( CEntityPlayer* ) CSceneLogic::GetSingleton().GetPlayerByCharID( tpTopTen->charlist( j ) );
			if ( tpPlayer == NULL )
				continue;

			int tTitleID = 0;
			ConvertRankToTitle( tpTopTen->ranktype(), j, tTitleID );

			CTitle* tpTitle = (CTitle*)CDataStatic::GetTitle( tTitleID );
			if ( tpTitle == NULL )
				continue;

			CPropertyPlayer* tpProperty = ( CPropertyPlayer* ) tpPlayer->GetProperty();

			if ( tpProperty->AddTitle( tTitleID ) > 0 )
			{
				if ( tpTitle->mIsReplace > 0 )
				{
					tpProperty->SetCurrentTitle( tTitleID );
					CPropertyModule::GetSingleton().SendNotifyUpdateCurrentTitle( tpPlayer, tTitleID );
				}
				else
					CPropertyModule::GetSingleton().SendNotifyClientUpdateTitle( tpPlayer, TITLE_ADD, tTitleID );
			}
			 
		}				
	}

	return 0;
}

int CRankModule::OnGateMessageObtainTopTenResponse(CMessage *pMessage)
{
	if ( pMessage == NULL ) return -1;

	CMessageObtainTopTenResponse* tpResponse = ( CMessageObtainTopTenResponse* ) pMessage->msgpara();

	CEntityPlayer* tpPlayer = ( CEntityPlayer* ) CSceneLogic::GetSingleton().GetPlayerByCharID( tpResponse->charid() );
	if ( tpPlayer == NULL )
	{
		return -1;
	}

	CPropertyPlayer* tpProperty = ( CPropertyPlayer* ) tpPlayer->GetProperty();

	CMessage tMessage;
	CMessageUpdateTitleNotice tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_NOTICE_UPDATETITLE );
	tMessage.set_msgpara( (long) &tPara );
	tPara.set_isbatch( (int) true );
	tPara.set_type( TITLE_ADD );

	int tIndex = 0;
	int tTopTenTitleList[ TOTAL_RANK_NUM ] = { 0 };

	// ��һ�õ����µ����а�ƺ�
	for ( int i = 0; i < tpResponse->ranktitle_size(); i ++ )
	{
		int tTitleID = 0;
		PBRankTitle* tpPbTitle = tpResponse->mutable_ranktitle( i );
		ConvertRankToTitle( tpPbTitle->ranktype(), tpPbTitle->index(), tTitleID );
		if ( tTitleID > 0 )
		{
			tTopTenTitleList[ tIndex ++ ] = tTitleID;
		}				
	}

	int tTitleList[ TITLEMAX_SELF ] = { 0 };
	int tNum = ARRAY_CNT( tTitleList );
	
	// ��ȡ������ϵĳƺ��б�
	tpProperty->GetTitleList( tTitleList, tNum );

	// ������ԭ�������а�ƺ��Ѿ����ϣ���ɾ������
	for ( int i = 0; i < tNum; i ++ )
	{
		int tTitle = tTitleList[ i ];
		
		if ( tTitle <= 0 )	continue ;
		
		bool bExist = false;
		for ( int j = 0; j < tIndex; j ++  )
		{
			if ( tTitle == tTopTenTitleList[ j ] )
			{
				bExist = true;
				break;
			}
		}
		if ( bExist == false )
		{
			CTitle* tpTitle = CDataStatic::GetTitle( tTitle );
			if ( tpTitle == NULL )	continue;

			// ������ƺŲ�����
			if ( tpTitle->mValidTime == emTitleForever )
				continue;

			// ������ƺŲ�����
			if ( tpTitle->mIsTeamTitle != 0 )
				continue;

			// �����ʱ��ƺŲ�����
			if ( tpTitle->mValidTime > 0 )
			{
				continue;
			}

			// ������ƺŴ���
			if ( IS_NATION_TITLE( tpTitle->mType, tpTitle->mObtainCondition ) )
			{
				OnEventNationTitle( tpPlayer, tTitle );
				continue;
			}

			// ��ʱ�����а�ƺŴ���
			tpProperty->RemoveTitle( tTitle );
			if ( tTitle == tpProperty->GetCurrentTitle() )
			{
				tpProperty->SetCurrentTitle( 0 );
				CPropertyModule::GetSingleton().SendNotifyUpdateCurrentTitle( tpPlayer, 0 );
			}
			CPropertyModule::GetSingleton().SendNotifyClientUpdateTitle( tpPlayer, TITLE_DELETE, tTitle );
		}
	}

	for ( int i = 0; i < tIndex; i ++ )
	{
		if ( tpProperty->AddTitle( tTopTenTitleList[ i ] ) > 0 )
		{
			tPara.add_titlelist( tTopTenTitleList[ i ] );
			tPara.add_timelist( tpProperty->GetTitleTime( tTopTenTitleList[ i ] ) );
		}
	}

	CSceneLogic::GetSingleton().Send2Player( tpPlayer, &tMessage );
	return 0;
}

// �����а����ת���ɶ�Ӧ�ĳƺ�

int CRankModule::ConvertRankToTitle(int vType, int vIndex, int& vTitleID)
{
	int tRankType = 0, tScopeParam = 0, tSubParam = -1, tSubParam2 = -1;
	
	// ly�޸ģ������level 1 2 3 ������ �����ٿ���������
	if ( vIndex == 0 )
	{
		tSubParam = CTplTitleManager::LEVEL_1;
	}
	else if ( vIndex == 1 )
	{
		tSubParam = CTplTitleManager::LEVEL_2;
	}
	else if ( vIndex == 2 )
	{
		tSubParam = CTplTitleManager::LEVEL_3;
	}

	if ( vIndex > 0 && vIndex < 4 )
		tSubParam2 = CTplTitleManager::LEVEL_2_4;
	else if ( vIndex > 3 && vIndex < 10 )
		tSubParam2 = CTplTitleManager::LEVEL_5_10;

	if ( tSubParam == -1 )
		tSubParam = tSubParam2;

	switch ( vType )
	{
	case RANKTYPE_LEVEL_ALL:
		{
			tRankType =  CTplTitleManager::RANK_PLAYER_LEVEL;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;			
			break;
		}
	case RANKTYPE_LEVEL_MYNATION:
		{
			tRankType =  CTplTitleManager::RANK_PLAYER_LEVEL;
			tScopeParam = CTplTitleManager::SCOPE_COUNTRY;
			break;
		}
	case RANKTYPE_MONEY_NOBIND:
		{
			tRankType = CTplTitleManager::RANK_MONEY_OWN;
			tScopeParam = CTplTitleManager::SCOPE_UNBOUNDMONEY;
			break;
		}
	case RANKTYPE_MONEY_ALL:
		{
			tRankType = CTplTitleManager::RANK_MONEY_OWN;
			tScopeParam = CTplTitleManager::SCOPE_TOTAL;
			break;
		}
	case RANKTYPE_KILL_PROT_NATION:
		{
			tRankType = CTplTitleManager::RANK_KILLENEMY_NUM;
			tScopeParam = CTplTitleManager::SCOPE_PROTECT_WEEK;
			break;
		}
	case RANKTYPE_KILL_OUT:
		{
			tRankType = CTplTitleManager::RANK_KILLENEMY_NUM;
			tScopeParam = CTplTitleManager::SCOPE_BATTLE_WEEK;
			break;
		}
	case RANKTYPE_KILL_TOTAL:
		{
			tRankType = CTplTitleManager::RANK_KILLENEMY_NUM;
			tScopeParam = CTplTitleManager::SCOPE_TOTAL;
			break;
		}
	case RANKTYPE_HONOR_ALL:
		{
			tRankType = CTplTitleManager::RANK_EXPLOIT;
			tScopeParam = CTplTitleManager::SCOPE_WORLD_TOTAL;
			break;
		}
	case RANKTYPE_HONER_MYNATION:
		{
			tRankType = CTplTitleManager::RANK_EXPLOIT;
			tScopeParam = CTplTitleManager::SCOPE_COUNTRY_TOTAL;
			break;
		}
	case RANKTYPE_DIE:
		{
			tRankType = CTplTitleManager::RANK_NUM_DIE;
			tScopeParam = CTplTitleManager::SCOPE_TOTAL;
			break;
		}
	case RANKTYPE_END_TASK:
		{
			tRankType = CTplTitleManager::RANK_TOTAL_TASK;
			tScopeParam = CTplTitleManager::SCOPE_TASKFINISH;
			break;
		}
	case RANKTYPE_ONLINE_TIME:
		{
			tRankType = CTplTitleManager::RANK_ONLINE_TIME;
			tScopeParam = CTplTitleManager::SCOPE_ONLINETIME;
			break;
		}
	case RANKTYPE_PANTAO_MARK:
		{
			tRankType = CTplTitleManager::RANK_PRSNHONER_FB;
			tScopeParam = CTplTitleManager::SCOPE_PANTAO;
			break;
		}
	case RANKTYPE_LONGGONG_MARK:
		{
			tRankType = CTplTitleManager::RANK_PRSNHONER_FB;
			tScopeParam = CTplTitleManager::SCOPE_LONGGONG;
			break;
		}
	case RANKTYPE_KILLSAMENATIONNUM:
		{
			tRankType = CTplTitleManager::RANK_KILLSAMENATION;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_ORIGINRELIVETIMES:
		{
			tRankType = CTplTitleManager::RANK_RELIFE;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_KILLOGRENUM:
		{
			tRankType = CTplTitleManager::RANK_KILLOGRE_NUM;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_UPFAILNUM:
		{
			tRankType = CTplTitleManager::RANK_REFINEFAIL_NUM;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
		// ���а�ƺ������޸� [12/18/2009 Macro]
	case RANKTYPE_HONOR_ALL_TODAY: // ������������
		{
			tRankType = CTplTitleManager::RANK_HONOR_ALL_TODAY;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_HONER_MYNATION_TODAY: // ������Ӫ����
		{
			tRankType = CTplTitleManager::RANK_HONER_MYNATION_TODAY;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_DAYANTA:	// ���������֣�ȫ����
		{
			tRankType = CTplTitleManager::RANK_DAYANTA;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_LIANHUADONG:	// ���������֣�ȫ����
		{
			tRankType = CTplTitleManager::RANK_LIANHUADONG;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_HUANGFENGDONG: // �Ʒ䶴���֣�ȫ����
		{
			tRankType = CTplTitleManager::RANK_HUANGFENGDONG;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_ACHIVE_POINT: // �ɾ͵㣨ȫ����
		{
			tRankType = CTplTitleManager::RANK_ACHIVE_POINT;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_FAVOR_POINT: // �øжȣ�ȫ����
		{
			tRankType = CTplTitleManager::RANK_FAVOR_POINT;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_BAD_POINT:	// ����ȣ�ȫ����
		{
			tRankType = CTplTitleManager::RANK_BAD_POINT;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_FAMILY_PVP:	// ����PVP���֣�ȫ����
		{
			tRankType = CTplTitleManager::RANK_FAMILY_PVP;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_CORPS_PVP: // ����PVP���֣�ȫ����
		{
			tRankType = CTplTitleManager::RANK_CORPS_PVP;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_CORPSBOSS_SCORE:  // ����boss���� ��ȫ����
		{
			tRankType = CTplTitleManager::RANK_CORPSBOSS_SCORE;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_CORPSCOLLECT_ACTIVE:  // ���Ųɼ���Ծ�� ��ȫ����
		{
			tRankType = CTplTitleManager::RANK_CORPSCOLLECT_ACTIVE;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_FAMILY_TAO:	// ����Ʒ���һ��֣�ȫ����
		{
			tRankType = CTplTitleManager::RANK_FAMILY_TAO;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_KILL_PROT_NATION_TODAY: // ����ɱ����(����)
		{
			tRankType = CTplTitleManager::RANK_KILL_PROT_NATION_TODAY;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_KILL_OUT_TODAY: // ����ɱ����(����)
		{
			tRankType = CTplTitleManager::RANK_KILL_OUT_TODAY;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_KILL_TOTAL_TODAY:  // ���ձ�����ɱ��
		{
			tRankType = CTplTitleManager::RANK_KILL_TOTAL_TODAY;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}

		// �������� [2/3/2010 Macro]
	case RANKTYPE_CHARM_VALUE:
		{
			tRankType = CTplTitleManager::RANK_CHARM;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
		// ���ƴ�ս����
	case RANKTYPE_FLY_FB_MARK:
		{
			tRankType = CTplTitleManager::RANK_FLYFB;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}

	case RANKTYPE_ZHANGONG:
		{
			tRankType = CTplTitleManager::RANK_ZHANGONG;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_ZHIGUO:
		{
			tRankType = CTplTitleManager::RANK_ZHIGUO;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_TONGSHUAI:
		{
			tRankType = CTplTitleManager::RANK_TONGSHUAI;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_WIS:
		{
			tRankType = CTplTitleManager::RANK_WISALL;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_YUNXIAO:
		{
			tRankType = CTplTitleManager::RANK_YUNXIAOTA;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_WUDIDONG:
		{
			tRankType = CTplTitleManager::RANK_WUDIDONG;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_GLOBALWAR:
		{
			tRankType = CTplTitleManager::RANK_GLOBALWAR;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	case RANKTYPE_SPIRIT:
		{
			tRankType = CTplTitleManager::RANK_SPIRIT;
			tScopeParam = CTplTitleManager::SCOPE_GLOBAL;
			break;
		}
	default:
		break;
	}

	if ( NULL == CDataStatic::GetTitle( tRankType, tScopeParam, tSubParam, vTitleID ) )
		CDataStatic::GetTitle( tRankType, tScopeParam, tSubParam2, vTitleID ) ;
	return 0;
}

// �õ���һ���
int CRankModule::GetPantaoMark( CEntityPlayer* pPlayer )
{
	int nRet = 0;
	int nTmp = 0;
	LK_ASSERT( CSceneCfgManager::GetSingleton().GetRank_cfg()->mPantaomap1 < MAP_INDEX_MAX, return 0 );
	LK_ASSERT( CSceneCfgManager::GetSingleton().GetRank_cfg()->mPantaomap2 < MAP_INDEX_MAX, return 0 );
	LK_ASSERT( CSceneCfgManager::GetSingleton().GetRank_cfg()->mPantaomap3 < MAP_INDEX_MAX, return 0 );
	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	if ( pProperty->GetRepetion()->GetIntData( CSceneCfgManager::GetSingleton().GetRank_cfg()->mPantaomap1, 0, &nTmp ) == SUCCESS )
		nRet += nTmp;
	if ( pProperty->GetRepetion()->GetIntData( CSceneCfgManager::GetSingleton().GetRank_cfg()->mPantaomap2, 0, &nTmp ) == SUCCESS )
		nRet += nTmp;
	if ( pProperty->GetRepetion()->GetIntData( CSceneCfgManager::GetSingleton().GetRank_cfg()->mPantaomap3, 0, &nTmp ) == SUCCESS )
		nRet += nTmp;
	return nRet;
}

// �õ���������
int CRankModule::GetLonggongMark( CEntityPlayer* pPlayer )
{
	int nRet = 0;
	int nTmp = 0;
	LK_ASSERT( CSceneCfgManager::GetSingleton().GetRank_cfg()->mLonggongmap1 < MAP_INDEX_MAX, return 0 );
	LK_ASSERT( CSceneCfgManager::GetSingleton().GetRank_cfg()->mLonggongmap2 < MAP_INDEX_MAX, return 0 );
	LK_ASSERT( CSceneCfgManager::GetSingleton().GetRank_cfg()->mLonggongmap3 < MAP_INDEX_MAX, return 0 );
	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	if ( pProperty->GetRepetion()->GetIntData( CSceneCfgManager::GetSingleton().GetRank_cfg()->mLonggongmap1, 0, &nTmp ) == SUCCESS )
		nRet += nTmp;
	if ( pProperty->GetRepetion()->GetIntData( CSceneCfgManager::GetSingleton().GetRank_cfg()->mLonggongmap2, 0, &nTmp ) == SUCCESS )
		nRet += nTmp;
	if ( pProperty->GetRepetion()->GetIntData( CSceneCfgManager::GetSingleton().GetRank_cfg()->mLonggongmap3, 0, &nTmp ) == SUCCESS )
		nRet += nTmp;
	return nRet;
}

int CRankModule::OnObtainRankTitleRequest(CEntityPlayer *vpPlayer)
{
	if ( vpPlayer == NULL ) return -1; 

	CMessage tMessage;
	CMessageObtainTopTenRequest tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2G_REQUEST_TOPTEN );
	tPara.set_charid( vpPlayer->GetCharID() );
	tMessage.set_msgpara( (long) &tPara );
	CSceneLogic::GetSingleton().Send2Gate( &tMessage );
	
	return 0;
}


// ������ƺŴ���
int CRankModule::DisposTitleList(CEntityPlayer *npPlayer)
{
	if ( npPlayer == NULL )
	{
		return -1;
	}

	CPropertyPlayer* tpProperty = ( CPropertyPlayer* ) npPlayer->GetProperty();
	int nTitleIDs[TITLEMAX_SELF] = {0};
	int nTitleNum = TITLEMAX_SELF;
	tpProperty->GetTitleList( nTitleIDs, nTitleNum );

	for ( int i = 0 ; i < nTitleNum && i < TITLEMAX_SELF ; ++i )
	{
		CTitle* tpTitle = CDataStatic::GetTitle( nTitleIDs[i] );  
		if ( tpTitle == NULL )
		{
			continue;
		}

		if ( tpTitle->mValidTime > 0 ) // ��ʱ��
		{
			time_t tNow = time( NULL );
			int tTime = tpProperty->GetTitleTime( nTitleIDs[i] );
			LOG_DEBUG("pro", "START TIMER hour:%d", tpTitle->mValidTime );
			LOG_DEBUG("pro", "START TIMER NOW:%d time:%d", tNow, tTime );
			if ( tNow >= tTime ) // ������
			{
				tpProperty->RemoveTitle( nTitleIDs[i] );
				if ( nTitleIDs[i] == tpProperty->GetCurrentTitle() )
				{
					tpProperty->SetCurrentTitle( 0 );
					CPropertyModule::GetSingleton().SendNotifyUpdateCurrentTitle( npPlayer, 0 );
				}
				CPropertyModule::GetSingleton().SendNotifyClientUpdateTitle( npPlayer, TITLE_DELETE, nTitleIDs[i] );
			}
			else // ���붨ʱ��
			{
				// ������ʱ��
				int nTimerOtherInfo[ TIMER_OTHER_INFO ] = { MESSAGE_PROPERTY, nTitleIDs[i], 0, 0};
				npPlayer->GetTimerReciver()->SetTimerBySec( npPlayer->GetEntityID(), TIMER_TITLE_DISAPPEAR
					, (tTime-tNow), 2, nTimerOtherInfo ) ;
				LOG_DEBUG("pro", "START TIMER MIN:%d", (tTime-tNow) );
			}
		}
	}

	return SUCCESS;
}

// ������ƺŴ��� [3/2/2010 GaoHong]
int CRankModule::OnEventNationTitle( CEntityPlayer* npPlayer, int nTitleID )
{
	if ( npPlayer == NULL || nTitleID <= 0 )
	{
		return -1;
	}

	CPropertyPlayer* tpProperty = ( CPropertyPlayer* ) npPlayer->GetProperty();

	CTitle* tpTitle = CDataStatic::GetTitle( nTitleID );  
	if ( tpTitle == NULL )
	{
		return -1;
	}

	if ( tpProperty->HasTitle( nTitleID ) == false )
	{
		return -1;
	}

	// ����Ƿ��ǹ����ƺ�
	if ( IS_NATION_TITLE( tpTitle->mType, tpTitle->mObtainCondition ) == false )
	{
		return -1;
	}

	// �õ�����ID
	int tCountryID = CWorldModule::GetSingleton().ConvertMapIDToCountry( tpTitle->mParm );

	if ( npPlayer->GetCountryID() == tCountryID )
	{
		// ����Ҫ����
		return 0;
	}

	if ( npPlayer->GetCountryID() == COUNTRY_NONE )
	{
		return -1;
	}

	// ɾ���Ϲ����ƺ�
	CWorldModule::GetSingleton().OnEventNationTitle( npPlayer, tCountryID, false );

	// �����¹����ƺ�
	CWorldModule::GetSingleton().OnEventNationTitle( npPlayer, npPlayer->GetCountryID(), true );
	
	return 0;
}