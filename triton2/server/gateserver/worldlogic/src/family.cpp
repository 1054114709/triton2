#include "family.h"
#include "gatelogic.h"
#include "nameservice.h"
#include "core_service.h"
#include "family_manager.h"
#include "corps.h"
#include "corpsmanager.h"
#include "coretype.h"
#include "template.h"
#include "gateobj_manager.h"
#include "base.h"

// ***********************************************************
//  Function:		CFamily
//  Description:	���캯�� 
//  Output:			
//  Date:	04/22/2009
// **********************************************************
CFamily::CFamily()
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

// ***********************************************************
//  Function:		Initialize
//  Description:	��ʼ������ 
//  Output:			
//  Date:	04/22/2009
// **********************************************************
int CFamily::Initialize()
{	
	m_nFamilyID = 0;
	memset( m_sFamilyName, 0, sizeof( m_sFamilyName ) );
	m_nRooter = 0;
	memset(m_sRooterName, 0, sizeof(m_sRooterName));
	m_tMembers.initailize();
	memset( m_szBulletin, 0, sizeof( m_szBulletin ) );
	m_nCountryID = 0;	
	m_nFamilyDBID = 0;
	m_tApplyList.initailize();
	m_nCorpsID = 0;
	m_tInviteList.initailize();
	m_nFamilyStatus	= EM_FAMILY_STATUS_ALIVE;
	m_nSaveStatus = FAMILY_INFONOCHANGE;
	m_nDisbandTime = time(NULL);
	m_nLastTimeApplyCorps = 0;
	m_nLastTimeLeaveCorps = 0; 
	m_nStar = 0;
	m_nLevel = 1;
	m_nGlory = 0;
	m_nMoney = 0;
	m_nFreezeMoney = 0;
	m_nContribution = 0;
	m_nHot = 0;
	m_nProd = 0;
	m_nFun = 0;
	m_nTech = 0;
	m_nCul = 0;	
	
	m_nPVPWinNum = 0;
	m_nPVPFailedNum = 0;
	m_nPVPScore = 0;	
	m_nPVPStarLevel = 1;   
	m_bJoinBattle = false;
	m_nNpcID = 0;
	m_nBidMoney = 0;
	m_nBidTime = 0;
	m_nBattleState = STATE_BIDDING;
	m_nWarRank = 1;
	memset( m_sPVPName, 0, sizeof( m_sPVPName ) );
	
	m_nFamilyNpcMoney = 0;
	m_nFamilyNpcGlory = 0;
	m_nNpcWelfareGetTime = -1;			
	m_nFamilyBossKey = 0;	
	m_nFamilyRepetionLevel = 1;
	m_nReptionScore = 0;
	m_nRepetionDate = 0;
	m_nRepetionOpenTimes = 0;
		
	// ��ʼ����ְϵͳ
	InitialOrganization( );	
	
	m_tFamilyShop.Initialize();
	m_nStabilityDegree = 200;	
	m_nWeekNum = 0;
	return 0;
}

// ***********************************************************
//  Function:		SetSaveStatus
//  Description:	���ô洢״̬ 
//  Output:			
//  Date:	04/22/2009
// **********************************************************
void CFamily::SetSaveStatus( int vSaveStatus )
{	
	if ( vSaveStatus == m_nSaveStatus )
	{
		return;
	}
	
	if ( m_nSaveStatus == FAMILY_INFONOCHANGE )
	{
		m_nSaveStatus = vSaveStatus;
	}
	else
	{	
		m_nSaveStatus = FAMILY_ALLINFOCHANGED;
	}				
}

// ***********************************************************
//  Function:		Resume
//  Description:	 
//  Output:			
//  Date:	04/22/2009
// **********************************************************
int CFamily::Resume()
{
	return 0;
}

// ***********************************************************
//  Function:		GetLabel
//  Description:	ȡ�ù��� 
//  Output:			
//  Date:	04/22/2009
// **********************************************************
CLabel * CFamily::GetLabel( labelid_t nLabelID )
{
	//LK_ASSERT(nLabelID <  em_family_officer_limit, return NULL);
	//return m_tOfficers[(unsigned int)nLabelID].mLabel.GetID() == em_family_label_null ? NULL : &(m_tOfficers[(unsigned int)nLabelID].mLabel);
	return NULL;
}

// ***********************************************************
//  Function:		GetMemberCount
//  Description:	ȡ�õ�ǰ��Ա���� 
//  Output:			
//  Date:	04/22/2009
// **********************************************************
int CFamily::GetMemberCount()
{
	return m_tMembers.size();
}

// ***********************************************************
//  Function:		IsFull
//  Description:	�жϼ�ͥ��Ա�Ƿ��Ѵ����� 
//  Output:			
//  Date:	04/22/2009
// **********************************************************
bool CFamily::IsFull()
{
	int nMaxNum = 0;
	int tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetMemberNumLimitByLevel( m_nLevel, nMaxNum );
	if ( tRet == -1 )
	{
		return true;
	}
	if ( (int)m_tMembers.size() >= nMaxNum ||  m_tMembers.size() >= m_tMembers.max_size() )
	{
		return true;
	}				   
	else
	{			
		return false;	
	}						
}

// ***********************************************************
//  Function:		Ins2Member
//  Description:	����³�Ա 
//  Output:			
//  Date:	04/22/2009
// **********************************************************
bool CFamily::Ins2Member(roleid_t nRoleID, family_info_t &stFamilyInfo) 
{		
	int nMaxNum = 0;
	int tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetMemberNumLimitByLevel( m_nLevel, nMaxNum );
	if ( tRet == -1 )
	{
		return false;
	}
	if ( (int)m_tMembers.size() >= nMaxNum ||  m_tMembers.size() >= m_tMembers.max_size() )
	{
		  return false;
	}				   
	else
	{
		m_tMembers.insert(members_t::value_type(nRoleID, stFamilyInfo));
		SetSaveStatus( FAMILY_MEMBERCHANGED );
		return true;	
	}					
}

// ***********************************************************
//  Function:		Del4Member
//  Description:	ɾ����Ա 
//  Output:			
//  Date:	04/22/2009
// **********************************************************
bool CFamily::Del4Member(roleid_t nRoleID)
{
	iterator it = m_tMembers.find( nRoleID );
	if ( it == m_tMembers.end() )
	{
		return false;
	}	
	else
	{
		m_tMembers.erase( nRoleID);
		// ����ھ����У�ɾ�����Ų�ս�б�
		CCorps* pCorp = CCorpsManager::GetSingleton().GetCorpsByID(m_nCorpsID);
		if (pCorp)
		{
			pCorp->DelBattleRole( nRoleID );
			pCorp->SetSaveStatus( CCorps::CORPS_ALLINFOCHANGED);
		}
		SetSaveStatus( FAMILY_MEMBERCHANGED );
		return true;
	}	
}

// ***********************************************************
//  Function:		GetMemberFamilyInfo
//  Description:	ȡ�ó�Ա�ڼ����е���Ϣ 
//  Output:			
//  Date:	04/22/2009
// **********************************************************
family_info_t* CFamily::GetMemberFamilyInfo(roleid_t nRoleID)
{
	members_t::iterator iter = m_tMembers.find(nRoleID);
	return (iter != m_tMembers.end()) ? &(iter->second) : NULL;
}

// ***********************************************************
//  Function:		MemberHasRight
//  Description:	�жϼ����Ա�Ƿ�ӵ��Ȩ��emright
//  Output:			
//  Date:	04/22/2009
// **********************************************************
bool CFamily::MemberHasRight(roleid_t nRoleID, EmRight emright)
{
	members_t::iterator iter = m_tMembers.find(nRoleID); 	
	return PostHasRight( (iter->second).mFamilyPost, emright );
}

// ***********************************************************
//  Function:		GetMemberInfoList
//  Description:	��ȡ��Ա��Ϣ�б�
//  Output:			
//  Date:	05/09/2009
// **********************************************************
void CFamily::GetMemberInfoList( PBFamilyMemberInfoList *pbMembList )
{
	LK_ASSERT( pbMembList != NULL, return )
	if( m_tMembers.empty() )
	{
		return;
	}
	members_t::iterator it = m_tMembers.begin();
	for ( ; it != m_tMembers.end() ; ++it )
	{
		PBFamilyMemberInfo *pbMemberInfo = pbMembList->add_memberinfo();
		pbMemberInfo->set_roleid( it->first );
		pbMemberInfo->set_familypost( (it->second).mFamilyPost );
		pbMemberInfo->set_familycontribute( (it->second).mFamilyContribue );
		pbMemberInfo->set_corpscontribute( (it->second).mCorpsContribue );
		pbMemberInfo->set_corpspost( (it->second).mCorpsPost );
		pbMemberInfo->set_corpstitle( (it->second).mName );
	}
}

// ***********************************************************
//  Function:		CreatMemberInfo
//  Description:	ͨ��PBFamilyMemberInfoList������Ա��Ϣ
//  Output:			
//  Date:	05/09/2009
// **********************************************************
void CFamily::CreatMemberInfo( PBFamilyMemberInfoList *pbMembList )
{  
	LK_ASSERT( pbMembList != NULL, return );	
	family_info_t t;
	for ( int i = 0; i < pbMembList->memberinfo_size(); ++i )
	{				
		PBFamilyMemberInfo *pbFamilyMember = pbMembList->mutable_memberinfo( i );  		
		LK_ASSERT( pbFamilyMember != NULL, continue )
		t.mFamilyPost = pbFamilyMember->familypost();	
		t.mFamilyContribue = pbFamilyMember->familycontribute();	
		t.mCorpsContribue  = pbFamilyMember->corpscontribute();	 	 	 	
		t.mCorpsPost	    = pbFamilyMember->corpspost();
		strncpy( t.mName, pbFamilyMember->mutable_corpstitle()->c_str(), sizeof( t.mName ) - 1 );		
		m_tMembers.insert( members_t::value_type( pbFamilyMember->roleid(), t ) );	
	}
}

// ***********************************************************
//  Function:		CheckApply
//  Description:	�����ҵ������Ƿ����
//  Output:			
//  Date:	06/05/2009
// **********************************************************
bool CFamily::CheckApply( int nApplyingID )
{
	if ( m_tApplyList.empty() )
	{
		return false;
	}
	for ( FamilyApplyList::iterator it = m_tApplyList.begin(); it != m_tApplyList.end(); ++it )
	{
		if ( *it == nApplyingID )
		{
			return true;
		}
	}
	return false;
}

// ***********************************************************
//  Function:		InsertApply
//  Description:	������������б��������һ����ҵ�����
//  Output:			
//  Date:	05/09/2009
// **********************************************************
int CFamily::InsertApply( int nApplyingID )
{
	if ( CheckApply( nApplyingID ) )
	{
		return SUCCESS;
	}		
	if ( m_tApplyList.size() >= MAX_APPLYLIST_APPLIESNUM )
	{
		return ERROR_FAMILY_APPLY_APPLYLISTFULL;
	}		
	m_tApplyList.push_back( nApplyingID );
	return SUCCESS;
}

// ***********************************************************
//  Function:		DeletApply
//  Description:	ɾ����ҵ�����
//  Output:			
//  Date:	05/09/2009
// **********************************************************
int CFamily::DeletApply( int nApplyingID )
{
	if ( m_tApplyList.empty() )
	{
		return 0;
	}
	for ( FamilyApplyList::iterator it = m_tApplyList.begin(); it != m_tApplyList.end(); ++it )
	{
		if ( *it == nApplyingID )
		{
			m_tApplyList.erase( it );
			break;
		}
	}
	return 0;
}

// ***********************************************************
//  Function:		DeletApply
//  Description:	��ȡ����������б�
//  Output:			
//  Date:	05/09/2009
// **********************************************************
int CFamily::GetApplyList( PBApplyList &pbApply ) 
{	
	if ( m_tApplyList.empty() )
	{
		return 0;
	}			 
	for (  FamilyApplyList::iterator it = m_tApplyList.begin() ; it != m_tApplyList.end(); ++it )
	{
		ApplyInfo *pbApplyinfor = pbApply.add_applydata();			
		pbApplyinfor->set_playercharid( *it );

		CRoleGlobalInfo *pPlayerInfo = CServiceRoleIDName::GetSingleton().GetRoleInfoByRoleID( *it );
		LK_ASSERT( pPlayerInfo != NULL,continue );
		if ( pPlayerInfo->CountryID() != m_nCountryID )
		{
			m_tApplyList.erase( it-- );
			continue;
		}
			
		pbApplyinfor->set_playerlevel( pPlayerInfo->Level() );
		pbApplyinfor->set_playermetier( pPlayerInfo->Metier() );
		pbApplyinfor->set_playername( pPlayerInfo->RoleName() );
		pbApplyinfor->set_facetype( pPlayerInfo->FaceType() );			
		pbApplyinfor->set_playersex( pPlayerInfo->GenderID() );
		pbApplyinfor->set_playeronline( 0 );
		pbApplyinfor->set_mapid( 0 );
		pbApplyinfor->set_lineid( 0 );
		CGatePlayer *pGatePlayer = CPlayerManager::GetSingleton().ScenePlayer( *it );
		/* ��ȡ���������Ϣ */
		if ( pGatePlayer != NULL )
		{
			pbApplyinfor->set_playeronline( 1 );
			pbApplyinfor->set_mapid( pGatePlayer->mMapID );				
			pbApplyinfor->set_lineid( pGatePlayer->mLineID ); 								
		} 			
											
	}	
	return 0;			
}

// ***********************************************************
//  Function:		GetFamilyMemberInfoList
//  Description:	��ȡ����ĳ�Ա��Ϣ�б�
//  Output:			
//  Date:	06/11/2009
// **********************************************************
int CFamily::GetFamilyMemberInfoList( PBFamilyMemberList &pbFamilyMemberList, bool bCorpsInfo /* = false */ )
{ 
	CCorps* tpCorps = CCorpsManager::GetSingleton().GetCorpsByID( m_nCorpsID );
	
	for ( members_t::iterator it = m_tMembers.begin(); it != m_tMembers.end( ); ++it )
	{	
		CRoleGlobalInfo *pPlayerInfo = CServiceRoleIDName::GetSingleton( ).GetRoleInfoByRoleID( it->first );
		if ( pPlayerInfo == NULL )
		{
			LOG_ERROR( "family", "can not find player info:%d ", it->first );
			continue;
		}
				
		FamilyMemberInfo *pbMeberInfo = pbFamilyMemberList.add_members();	
		pbMeberInfo->set_playerlevel( pPlayerInfo->Level() );
		pbMeberInfo->set_metierid( pPlayerInfo->Metier() );
		pbMeberInfo->set_playername( pPlayerInfo->RoleName() );
		pbMeberInfo->set_faceid( pPlayerInfo->FaceType() );								
		pbMeberInfo->set_rolesex( pPlayerInfo->GenderID() );				
		pbMeberInfo->set_online( 0 );
		pbMeberInfo->set_mapid( 0 );
		pbMeberInfo->set_lineid( 0 );
		pbMeberInfo->set_playercharid( it->first );
		pbMeberInfo->set_contribute( (it->second).mFamilyContribue );
		pbMeberInfo->set_corpscontribute( (it->second).mCorpsContribue );
		pbMeberInfo->set_familywar( CFamilyManager::GetSingletonPtr()->GetSubmit( it->first ) );
		
		CGatePlayer *pGatePlayer = CPlayerManager::GetSingleton().ScenePlayer( it->first );		
		
		/* ��ȡ���������Ϣ */
		if ( pGatePlayer != NULL )
		{
			pbMeberInfo->set_online( 1 );
			pbMeberInfo->set_mapid( pGatePlayer->mMapID );				
			pbMeberInfo->set_lineid( pGatePlayer->mLineID );
			pbMeberInfo->set_playerlevel( pGatePlayer->mLevel ); 								
		} 
		
		if( bCorpsInfo )
		{					
			pbMeberInfo->set_playerpost( (it->second).mCorpsPost );
			pbMeberInfo->set_corpstitle( (it->second).mName );		
		} 
		else
		{
			pbMeberInfo->set_playerpost( (it->second).mFamilyPost );
		}	
		
		//
		//if ( bCorpsInfo )
		//{
		//	pbMeberInfo->set_playerpost( CORPS_POST_MEMBER );	
		//}
		//else
		//{
		//	pbMeberInfo->set_playerpost( 1 );	
		//}
		//
		//// ����Ǽ����峤
		//if ( tpCorps != NULL )
		//{							
		//	if ( m_nRooter == it->first )
		//	{
		//		if ( !bCorpsInfo )
		//		{
		//			pbMeberInfo->set_playerpost( 0 );						
		//		}
		//		else
		//		{				
		//			
		//			if ( tpCorps->GetRooterID() == m_nRooter )
		//			{
		//				pbMeberInfo->set_playerpost( CORPS_POST_CORPSHEADER );
		//			}
		//			else
		//			{
		//				pbMeberInfo->set_playerpost( CORPS_POST_FAMILYHEADER );
		//			}
		//		}
		//	}			
		//}
	
		
		if (  tpCorps == NULL )
			continue;			
			
		if ( tpCorps->IsInBattleList( it->first ) )
		{
			pbMeberInfo->set_corpswar( true );
		}
		
		if ( tpCorps->GetRooterID() == it->first )
		{	 
			(it->second).mCorpsPost = CORPS_POST_CORPSHEADER;
		}
	}
	return 0;
}

// ***********************************************************
//  Function:		GetFamilyMemberInfoList
//  Description:	��ȡ����ĳ�Ա��Ϣ�б�
//  Output:			
//  Date:	06/11/2009
// **********************************************************
int CFamily::GetFamilyBasicInfo( FamilyData &pbFamilyData )
{
	pbFamilyData.set_familyid( m_nFamilyID );
	pbFamilyData.set_familyname( m_sFamilyName );
	pbFamilyData.set_headername( m_sRooterName );
	pbFamilyData.set_membernum( m_tMembers.size() );
	pbFamilyData.set_familylevel( m_nLevel );
	pbFamilyData.set_headerroleid( m_nRooter );	
	pbFamilyData.set_familyglory( m_nGlory );
	int tMemberNum = 0;
	int tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetMemberNumLimitByLevel( m_nLevel, tMemberNum );
	if ( tRet != -1 )
	{
		pbFamilyData.set_maxmembernum( tMemberNum );
	}
	pbFamilyData.set_familystarlevel( m_nPVPStarLevel );
	if ( GetBidMoney() == 0 )
	{
		pbFamilyData.set_npcid( m_nNpcID );
	}
	
	
	if ( m_nCorpsID != 0 )
	{
		CCorps *tpCorps = CCorpsManager::GetSingleton().GetCorpsByID( m_nCorpsID );
		if ( tpCorps != NULL )
		{
			pbFamilyData.set_corpsname( tpCorps->GetCorpsName() );
		}
	}
		
	
	//pbFamilyData.set_familydevelop( 0 );
	//pbFamilyData.set_npcid( m_nNpcID );	
	//pbFamilyData.set_bidmoney( m_nBidMoney );	
	//pbFamilyData.set_bidtime( m_nBidTime );	
	//
	//pbFamilyData.set_warnpcstatus( m_nBattleState );
	//pbFamilyData.set_warrank( 1 );
	//pbFamilyData.set_warwinnum( m_nPVPWinNum );
	//pbFamilyData.set_warlostnum( m_nPVPFailedNum );
	//pbFamilyData.set_familystarlevel( m_nPVPStarLevel );
	//pbFamilyData.set_warexp( m_nPVPScore );
	//pbFamilyData.set_warstatus( GetNPCState() );
	/*int tScore = 0;
	int tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetPVPScoreLimit( m_nPVPStarLevel, tScore );
	if ( tRet != -1 )
	{
		pbFamilyData.set_warmaxexp( tScore );
	}		*/
	return 0;
}

// ***********************************************************
//  Function:		GetFamilyMemberIDList
//  Description:	��ȡ����ĳ�ԱID�б�
//  Output:			
//  Date:	06/11/2009
// **********************************************************
int CFamily::GetFamilyMemberIDList( int *pMemberList, int &nNum, int nExceptRoleID /* = 0 */ )
{	
	int i = 0;
	for ( members_t::iterator it = m_tMembers.begin() ; it != m_tMembers.end() && i < nNum; ++it )
	{
		if ( it->first == nExceptRoleID )
		{
			continue;
		}
		pMemberList[i] = it->first;
		++i;
	}
	nNum = i;
	return 0;			
}

// ***********************************************************
//  Function:		CheckCorpsInvite
//  Description:	�������Ƿ���ĳ�����ŵ�������Ϣ
//  Output:			
//  Date:	06/11/2009
// **********************************************************
bool CFamily::CheckCorpsInvite( int nCorpsID )
{
	if ( m_tInviteList.begin() == m_tInviteList.end() )
	{
		return false;
	}
	for ( CorpsInviteList::iterator it = m_tInviteList.begin(); it != m_tInviteList.end(); ++it )
	{
		if ( *it == nCorpsID )
		{
			return true;
		}
	}
	return false;
}

// ***********************************************************
//  Function:		InsertCorpsInvite
//  Description:	����һ�����ŵ�������Ϣ
//  Output:			
//  Date:	06/11/2009
// **********************************************************
int CFamily::InsertCorpsInvite( int nCorpsID )
{
	if ( CheckCorpsInvite(nCorpsID) )
	{
		return SUCCESS;
	}
	
	if ( m_tInviteList.size() >= MAX_CORPSINVITE_NUM )
	{
		return 1;
	}
	m_tInviteList.push_back( nCorpsID );
	return SUCCESS;
}	

// ***********************************************************
//  Function:		DeleteCorpsInvite
//  Description:	ɾ��һ�����ŵ�������Ϣ
//  Output:			
//  Date:	06/11/2009
// **********************************************************
int CFamily::DeleteCorpsInvite( int nCorpsID ) 
{
	if ( m_tInviteList.begin() == m_tInviteList.end() )
	{
		return 1;
	}
	for ( CorpsInviteList::iterator it = m_tInviteList.begin(); it != m_tInviteList.end(); ++ it )
	{
		if ( *it == nCorpsID )
		{
			m_tInviteList.erase( it );
			return SUCCESS;
		}
	}
	return 1;
}

// ***********************************************************
//  Function:		CheckDisbandTime
//  Description:	����Ƿ�Ӧ�ý�ɢ����
//  Output:			
//  Date:	06/17/2009
// **********************************************************
bool CFamily::CheckDisbandTime( )
{	
	if ( m_nFamilyStatus == EM_FAMILY_STATUS_ALIVE )
	{
		return false;
	}				 
	if ( time(NULL) - m_nDisbandTime >= FAMILY_DISBAND_TIMELENGTH )
	{
		return true;
	}
	return false;	
}

// ***********************************************************
//  Function:		CheckLastTimeApplyCorps
//  Description:	���������ȴʱ��
//  Output:			
//  Date:	06/18/2009
// **********************************************************
bool CFamily::CheckLastTimeApplyCorps( )
{
	if ( time(NULL) - m_nLastTimeApplyCorps >= FAMILY_APPLYCORPS_TIMELENGTH )
	{
		return true;
	}
	return false;
}

// ***********************************************************
//  Function:		GetFamilyNpcGlory
//  Description:	��ȡ����npc������ҫֵ
//  Output:			
//  Date:	09/15/2009
// **********************************************************
int CFamily::GetFamilyNpcGlory( bool bRefresh /* = true */ )
{ 
	if ( m_nNpcWelfareGetTime == -1 || m_nNpcID <= 0 )
	{
		return -1;
	}
		
	int tTimes = ( time(NULL) - m_nNpcWelfareGetTime )/ WELFARE_REFESH_TIMELENGTH;
	int tGlory = tTimes*CFamilyManager::GetSingleton().GetFamilyConfig(  )->GetNpcGlory();	
	if ( tGlory > MAX_NPCWELFARE_GLORY )
	{
		tGlory = MAX_NPCWELFARE_GLORY;
	}  
	if ( bRefresh )
	{
		m_nNpcWelfareGetTime = time(NULL);
	}
				
	return tGlory;
}

// ***********************************************************
//  Function:		GetFamilyWelfare
//  Description:	��ȡ����npc����
//  Output:			
//  Date:	09/15/2009
// **********************************************************
int CFamily::GetFamilyWelfare( int nNpcTmpID, int &rGlory, int &rMoney, bool bRefresh /* = true */ )
{
	if ( m_nNpcID != nNpcTmpID )
	{
		return -1;
	}

	int tTimeNow = time(NULL);
	if ( m_nNpcWelfareGetTime == -1 || m_nNpcWelfareGetTime == 0 )
	{
		m_nNpcWelfareGetTime = tTimeNow - WELFARE_REFESH_TIMELENGTH;			
	}
	
	int tTimes = ( tTimeNow - m_nNpcWelfareGetTime )/ WELFARE_REFESH_TIMELENGTH;
	
	CNpcWelfare tNpcWelfare;
	CFamilyManager::GetSingleton().GetFamilyConfig()->GetNpcWelfare( nNpcTmpID, tNpcWelfare );
	rGlory = tTimes*tNpcWelfare.mNpcGlory;	
	if ( rGlory > MAX_NPCWELFARE_GLORY )
	{
		rGlory = MAX_NPCWELFARE_GLORY;
	}
	rMoney =  tTimes*tNpcWelfare.mNpcMoney;	
	if ( rMoney > MAX_NPCWELFARE_MONEY )
	{
		rMoney = MAX_NPCWELFARE_MONEY;
	}  
	
	if ( bRefresh )
	{
		m_nNpcWelfareGetTime = tTimeNow - ( tTimeNow - m_nNpcWelfareGetTime )%WELFARE_REFESH_TIMELENGTH;	
		SetSaveStatus( FAMILY_PROPERYCHANGED ); 		
	}
	return SUCCESS;	
}

// ***********************************************************
//  Function:		GetFamilyNpcMoney
//  Description:	��ȡ����npc���Ľ�Ǯֵ
//  Output:			
//  Date:	09/15/2009
// **********************************************************
int CFamily::GetFamilyNpcMoney( bool bRefresh /* = true */ )
{ 
	if ( m_nNpcWelfareGetTime == -1 || m_nNpcID <= 0 )
	{
		return -1;
	}

	int tTimes = ( time(NULL) - m_nNpcWelfareGetTime )/ WELFARE_REFESH_TIMELENGTH;
	int tMoney =  tTimes*CFamilyManager::GetSingleton().GetFamilyConfig(  )->GetNpcMoney();	
	if ( tMoney > MAX_NPCWELFARE_MONEY )
	{
		tMoney = MAX_NPCWELFARE_MONEY;
	}
	
	if ( bRefresh )
	{
		m_nNpcWelfareGetTime = time(NULL);
	} 
	return tMoney;				
}

// ***********************************************************
//  Function:		CheckLastTimeLeaveCorps
//  Description:	����뿪���ŵ���ȴʱ��
//  Output:			
//  Date:	06/18/2009
// **********************************************************
bool CFamily::CheckLastTimeLeaveCorps()
{		
	if ( time(NULL) - m_nLastTimeLeaveCorps >= FAMILY_LEAVECORPS_TIMELENGTH )
	{
		return true;
	}
	return false;
}

// ***********************************************************
//  Function:		SetPost
//  Description:	������ҵ�ְλ
//  Output:			
//  Date:	06/24/2009
// **********************************************************
void CFamily::SetPost( int nRoleID, labelid_t nPost, int &rOldPost, int nPostKind /* = EM_FAMILYACTION */ )
{  
	if ( nPostKind == EM_FAMILYACTION )
	{	
		SetFamilyPost( nRoleID, nPost, rOldPost );		
	}
	else if ( nPostKind == EM_CORPSACTION )
	{			
		SetCorpsPost( nRoleID, nPost, rOldPost );
	}	
}

// ***********************************************************
//  Function:		GetFamilyProperty
//  Description:	��ȡ����Ļ�������(�����Ա�ɼ�)
//  Output:			
//  Date:	09/01/2009
// **********************************************************
int CFamily::GetFamilyProperty( PBFamilyPropery &rPBProperty, bool bIfIncludeBasicInfo /* = true */ )
{
	// ��ȡ������Ϣ
	if ( bIfIncludeBasicInfo )
	{
		rPBProperty.set_familyid( m_nFamilyID );
		rPBProperty.set_familynotice( m_szBulletin );
		rPBProperty.set_membernum( m_tMembers.size() );
		rPBProperty.set_familyheaderid( m_nRooter );
		rPBProperty.set_familyheadername( m_sRooterName );
	}	
	
	// ��ȡ��ҫ�䶯����Ϣ
	rPBProperty.set_familylevel( m_nLevel );
	rPBProperty.set_familymoney( m_nMoney - m_nFreezeMoney );			  	
	rPBProperty.set_familyglory( m_nGlory );			  
	rPBProperty.set_familydevelop( 0 );
	rPBProperty.set_npcid( m_nNpcID );	
	rPBProperty.set_bidmoney( m_nBidMoney );	
	rPBProperty.set_bidtime( m_nBidTime );				  	
	rPBProperty.set_warnpcstatus( GetNPCState() );
	rPBProperty.set_warrank( 1 );
	rPBProperty.set_warwinnum( m_nPVPWinNum );
	rPBProperty.set_warlostnum( m_nPVPFailedNum );
	rPBProperty.set_familystarlevel( m_nPVPStarLevel );
	rPBProperty.set_warexp( m_nPVPScore );
	rPBProperty.set_warstatus( m_nBattleState );
	rPBProperty.set_enemyfamilyname( m_sPVPName );
	rPBProperty.set_stability( m_nStabilityDegree );	
	int tRedueceStability = 0;
	CFamilyManager::GetSingleton().GetFamilyConfig()->GetReduceStability( m_nLevel, tRedueceStability );	
	rPBProperty.set_reducestability( tRedueceStability );
	int tScore = 0;
	int tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetPVPScoreLimit( m_nPVPStarLevel, tScore );
	if ( tRet != -1 )
	{
		rPBProperty.set_warmaxexp( tScore );	 
	}	
	
	rPBProperty.set_challengestatus( m_nChallengeStatus );
	rPBProperty.set_challengemoney( m_nChallengeMoney );
	rPBProperty.set_challengestarted( m_sChallengeStarted );
	rPBProperty.set_challengereceived( m_sChallengeReceived );
	int tMemberNum = 0;
	tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetMemberNumLimitByLevel( m_nLevel, tMemberNum );
	if ( tRet != -1 )
	{
		rPBProperty.set_maxmembernum( tMemberNum );
	}
	
	int tPresterNum = 0;
	tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetPresbyterNumLimit( m_nLevel, tPresterNum );
	if ( tRet != -1 )
	{
		rPBProperty.set_maxpresbyternum( tPresterNum );
	}
		
	if ( CanFamilyLevelUp() )
	{	 
		rPBProperty.set_canlevelup( 1 );
	}	
	
	// ��ǰ�ȼ��µļ�����ҫ����
	int tGloryLimit = 0;
	tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetGloryLimitByLevel( m_nLevel, tGloryLimit );
	if ( tRet == SUCCESS )
	{
		rPBProperty.set_glorylimit( tGloryLimit );
	}	 
	
	int tMoneyLevelUpNeeded = 0;
	tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetMoneyLevelUPNeeded( m_nLevel, tMoneyLevelUpNeeded );	
	if ( tRet == SUCCESS )
	{
		rPBProperty.set_levelmoney( tMoneyLevelUpNeeded );
	}		

	// �����ڵ�����ӳ�
	int tExtraExp = 0;
	CFamilyManager::GetSingleton().GetFamilyConfig()->GetFamilyRedstoneConfig()->GetFamilyRedstone( m_nLevel, m_nStabilityDegree, tExtraExp );
	rPBProperty.set_extraredstonexp( tExtraExp );
	return SUCCESS;	
}

// ***********************************************************
//  Function:		GetMemberExp
//  Description:	��ȡ�����Ա�ľ���
//  Output:			
//  Date:	09/18/2009
// **********************************************************
int	CFamily::GetMemberExp( int nRoleID )
{
	members_t::iterator it = m_tMembers.find( nRoleID );	
	if ( it != m_tMembers.end() )
	{
		return (it->second).mExp;
	}
	return 0;
}

// ***********************************************************
//  Function:		AddMemberExp
//  Description:	���ӳ�Ա�ľ���
//  Output:			
//  Date:	09/18/2009
// **********************************************************
void CFamily::AddMemberExp( int nRoleID, int nExp )
{  
	members_t::iterator it = m_tMembers.find( nRoleID );
	if ( it != m_tMembers.end() )
	{
		(it->second).mExp+= nExp;
	}	
} 

// ***********************************************************
//  Function:		SetMemberExp
//  Description:	���ó�Ա����
//  Output:			
//  Date:	09/18/2009
// **********************************************************
void CFamily::SetMemberExp( int nRoleID, int nExp )
{	
	members_t::iterator it = m_tMembers.find( nRoleID );	
	if ( it != m_tMembers.end() )
	{
		(it->second).mExp= nExp;
	}				
}	

// ***********************************************************
//  Function:		GetMemberAP
//  Description:	��ȡ��ԱAPֵ
//  Output:			
//  Date:	09/18/2009
// **********************************************************
int CFamily::GetMemberAP( int nRoleID )
{	
	members_t::iterator it = m_tMembers.find( nRoleID );	
	if ( it != m_tMembers.end() )
	{
		return (it->second).mAP;
	}		
	return 0;		
}

// ***********************************************************
//  Function:		SetMemberAP
//  Description:	���ó�ԱAPֵ
//  Output:			
//  Date:	09/18/2009
// **********************************************************
void CFamily::SetMemberAP( int nRoleID, int nAP )
{
	members_t::iterator it = m_tMembers.find( nRoleID );	
	if ( it != m_tMembers.end() )
	{
		(it->second).mAP = nAP;
	}		
}

// ***********************************************************
//  Function:		AddMemberAP
//  Description:	���ӳ�ԱAP
//  Output:			
//  Date:	09/18/2009
// **********************************************************
void CFamily::AddMemberAP( int nRoleID, int nAP )
{	
	members_t::iterator it = m_tMembers.find( nRoleID );	
	if ( it != m_tMembers.end() )
	{
		(it->second).mAP+=nAP;
	}			
}

// ***********************************************************
//  Function:		GetPost
//  Description:	��ȡ��ҵ�ְλ
//  Output:			
//  Date:	06/24/2009
// **********************************************************
int CFamily::GetPost( int nRoleID, int nType, int &rPost )
{  
	members_t::iterator it = m_tMembers.find( nRoleID );
	rPost = 0;
	if ( it != m_tMembers.end( ) )
	{
		
		switch( nType )
		{
			case EM_FAMILYACTION:
			{
				rPost = (it->second).mFamilyPost;
				break;
			}
			case EM_CORPSACTION:
			{
				rPost = (it->second).mCorpsPost;
				break;
			}
			default:
				rPost = FAMILY_POST_MEMEBER; 
				break;
		}		
	}	
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetMemberLimitNum
//  Description:	��ȡ���嵱ǰ�ȼ��µĳ�Ա��������
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::GetMemberLimitNum( )
{  	
	int tNum = 0;
	CFamilyManager::GetSingleton().GetFamilyConfig()->GetMemberNumLimitByLevel( m_nLevel, tNum );	
	return tNum;
}	

// ***********************************************************
//  Function:		GetGloryLimit
//  Description:	��ȡ���嵱ǰ�ȼ��µ���ҫֵ����
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::GetGloryLimit( )
{  	
	int tGlory = 0;
	CFamilyManager::GetSingleton().GetFamilyConfig()->GetGloryLimitByLevel( m_nLevel, tGlory );
	return tGlory;
}

// ***********************************************************
//  Function:		SetFamilyPost
//  Description:	���ü����Ա��ְλ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::SetFamilyPost( int nCharID, int nPost, int &rOldPost )
{	
	members_t::iterator it = m_tMembers.find( nCharID );
	if ( it != m_tMembers.end() )
	{
		// �����ְ����
		rOldPost = (it->second).mFamilyPost;			
		(it->second).mFamilyPost = nPost;
		SetSaveStatus( FAMILY_MEMBERCHANGED ); 		
	}
	return SUCCESS;			
}

// ***********************************************************
//  Function:		SetCorpsPost
//  Description:	���þ��ų�Ա��ְλ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::SetCorpsPost( int nCharID, int nPost, int &rOldPost )
{
	members_t::iterator it = m_tMembers.find( nCharID );
	if ( it != m_tMembers.end() )
	{  		
		rOldPost = (it->second).mCorpsPost;				
		(it->second).mCorpsPost = nPost;
		SetSaveStatus( FAMILY_MEMBERCHANGED ); 		
	}	
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetNumOfCertainPost
//  Description:	��ȡ������߾�����ĳ��ְλ������
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::GetNumOfCertainPost( int nPost, int nType )
{	
	if ( m_tMembers.empty() )
	{						
		return 0;
	}
	
	int tNum = 0; 
	members_t::iterator it = m_tMembers.begin();
	for ( ; it != m_tMembers.end(); ++it )
	{ 
		int tPost = 0;
		if ( nType == EM_FAMILYACTION )
		{
			tPost = (it->second).mFamilyPost;
		}
		else
		{
			tPost = (it->second).mCorpsPost;
		}
		if ( tPost == nPost )
		{
			++tNum;		
		}				
	}
	
	return tNum;					
}

// ***********************************************************
//  Function:		HasPost
//  Description:	����Ա�Ƿ���ĳ��ְλ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
bool CFamily::HasPost( int nRoleID, int nPost, int nPostKind )
{		
	members_t::iterator it = m_tMembers.find( nRoleID );
	if ( it != m_tMembers.end() )
	{			
		int tPost = 0;
		if ( nPostKind == EM_FAMILYACTION )
		{
			tPost = (it->second).mFamilyPost;			
		}
		else
		{
			tPost = (it->second).mCorpsPost;			
		}
		if ( tPost == nPost )
		{
			return true;		
		}				
	}	
	return false;
}

// ***********************************************************
//  Function:		GetPostLimitNum
//  Description:	ĳ�ּ���ְλ��ǰ�ȼ��µ���������
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::GetPostLimitNum( int nPost )
{
	int tNum = 1;
	CFamilyConfigInfo tFamilyInfo;
	CFamilyManager::GetSingleton().GetFamilyConfig()->GetFamilyConfigByLevel( m_nLevel, tFamilyInfo );		
	switch( nPost )
	{
		case FAMILY_POST_HEADER:
		{
			break;
		}		
		case FAMILY_POST_PRESBYTER:			
		{
			tNum = tFamilyInfo.mPresbyterNumLimit;
			break; 
		} 
		case FAMILY_POST_BUSINESSMAN:
		{				
			break;
		} 
		case FAMILY_POST_MEMEBER:
		{
			tNum = tFamilyInfo.mMemberNumLimit;
			break;
		}
	}	
	return tNum;
}

// ***********************************************************
//  Function:		SetMemberName
//  Description:	���ü����Ա������
//  Output:			
//  Date:	08/25/2009
// **********************************************************
void CFamily::SetMemberName( int nRoleID, const char *pName )
{
	LK_ASSERT( pName != NULL, return )
	members_t::iterator it = m_tMembers.find( nRoleID );
	if ( it != m_tMembers.end() )
	{
		memset( (it->second).mName, 0, sizeof( (it->second).mName ) );
		strncpy( (it->second).mName, pName, sizeof( (it->second).mName ) );
		SetSaveStatus( FAMILY_MEMBERCHANGED );
	}	
}

// ***********************************************************
//  Function:		AddMemberContribute
//  Description:	������ҵĹ��׶�
//  Output:			
//  Date:	08/25/2009
// **********************************************************
void CFamily::AddMemberContribute( int nMemberID, int nValue, int nType /* = EM_FAMILYACTION */ )
{
	if ( nValue <= 0 )
	{
		return;
	}
		  
	members_t::iterator it = m_tMembers.find( nMemberID );
	if ( it != m_tMembers.end() )
	{			
		if ( nType == EM_CORPSACTION )
		{
			(it->second).mCorpsContribue += nValue;
			if ( (it->second).mCorpsContribue > MAX_CONTRIBUTE  )
			{
				(it->second).mCorpsContribue = MAX_CONTRIBUTE;
			}  			 
		}
		else if ( nType == EM_FAMILYACTION  ||  (it->second).mCorpsContribue < 0 )
		{	
			(it->second).mFamilyContribue += nValue; 		  
			if ( (it->second).mFamilyContribue > MAX_CONTRIBUTE )
			{
				(it->second).mFamilyContribue = MAX_CONTRIBUTE;
			}
		}				
		SetSaveStatus( FAMILY_MEMBERCHANGED );
	}	
}

// ***********************************************************
//  Function:		ReduceMemberContribute
//  Description:	������ҵĹ��׶�
//  Output:			
//  Date:	08/25/2009
// **********************************************************
void CFamily::ReduceMemberContribute( int nMemberID, int nValue, int nType /* = EM_FAMILYACTION */ )
{ 
	if ( nValue <= 0 )
	{
		return;
	}
	
	members_t::iterator it = m_tMembers.find( nMemberID );
	if ( it != m_tMembers.end() )
	{			
		if ( nType == EM_CORPSACTION )
		{
			(it->second).mCorpsContribue -= nValue;
			if (  (it->second).mCorpsContribue < 0 )
			{
				(it->second).mCorpsContribue = 0;
			}  			 
		}
		else if ( nType == EM_FAMILYACTION  ||  (it->second).mCorpsContribue < 0 )
		{	
			(it->second).mFamilyContribue -= nValue; 		  
			if ( (it->second).mCorpsContribue < 0 )
			{
				(it->second).mFamilyContribue = 0;
			}
		}				
		SetSaveStatus( FAMILY_MEMBERCHANGED );
	}				
}

// ***********************************************************
//  Function:		GetMemberContribute
//  Description:	������ҵĹ��׶�
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::GetMemberContribute( int nMemberID, int nType /* = EM_FAMILYACTION */ )
{
	members_t::iterator it = m_tMembers.find( nMemberID );
	if ( it != m_tMembers.end() )
	{			
		if ( nType == EM_CORPSACTION )
		{
			return (it->second).mCorpsContribue; 
		}
		else if ( nType == EM_FAMILYACTION )
		{	
			return (it->second).mFamilyContribue; 		  
		}				
	}
	return 0;
}

// ***********************************************************
//  Function:		SetMemberContirubte
//  Description:	������ҵĹ��׶�
//  Output:			
//  Date:	01/15/2010
// **********************************************************
int CFamily::SetMemberContirubte( int nMemberID, int nContribute, int nType /* = EM_FAMILYACTION */ )
{
	members_t::iterator it = m_tMembers.find( nMemberID );
	if ( it != m_tMembers.end() )
	{			
		if ( nType == EM_CORPSACTION )
		{
			(it->second).mCorpsContribue = nContribute; 
		}
		else if ( nType == EM_FAMILYACTION )
		{	
			 (it->second).mFamilyContribue = nContribute; 		  
		}				
	}
	return 0;
}

// ***********************************************************
//  Function:		LevelUPFamily
//  Description:	��������
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::LevelUPFamily( int &rLevel, int &rMoney, int &rStability )
{
	int tGloryUPNeeded = 0;
	rMoney = 0;
	int tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetGloryLevelUPNeeded( m_nLevel, tGloryUPNeeded );
	rLevel = m_nLevel;	
	
	// �Ѿ���������
	if ( tRet == -1 )
	{
		return ERROR_FAMILY_LEVELUP_LEVELIMIT;
	}	
	
	if ( tGloryUPNeeded == -1 )
	{
		return	ERROR_FAMILY_LEVELUP_LEVELIMIT;
	}
		
	
	if ( m_nGlory < tGloryUPNeeded )
	{	
		return ERROR_FAMILY_LEVELUP_GLORYNOTENOUGH;
	}
	
	// �жϼ����Ǯ
	int tMoneyLevelUpNeeded = 0;
	CFamilyManager::GetSingleton().GetFamilyConfig()->GetMoneyLevelUPNeeded( m_nLevel, tMoneyLevelUpNeeded );
	if ( tMoneyLevelUpNeeded > m_nMoney || tMoneyLevelUpNeeded < 0 )
	{
		return	ERROR_FAMILY_LEVELUP_MONEYNOENOUGH;
	}
	
	rMoney = tMoneyLevelUpNeeded;
	m_nMoney -= tMoneyLevelUpNeeded;
		
	++m_nLevel;
	rLevel = m_nLevel;	 	
	
	// ������尲���ȵ��ڳ�ʼ�����ȣ����Ϊ��ʼ������
	int tInitialStability = 0;
	CFamilyManager::GetSingleton().GetFamilyConfig()->GetInitialStability( m_nLevel, tInitialStability );
	if ( m_nStabilityDegree < tInitialStability && tInitialStability > 0 )
	{
		rStability = tInitialStability - m_nStabilityDegree;
		m_nStabilityDegree = tInitialStability;		
	}
				
	SetSaveStatus( FAMILY_PROPERYCHANGED );	
	return SUCCESS;		
}

// ***********************************************************
//  Function:		ContributeMoney
//  Description:	�����Ա���׽�Ǯ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::ContributeMoney( int nMemberID, int nFamilyMoney )
{		
	AddFamilyMoney( nFamilyMoney );
	SetSaveStatus( FAMILY_PROPERYCHANGED ); 
	return SUCCESS;			
}

// ***********************************************************
//  Function:		AddGlory
//  Description:	������ҫ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::AddGlory( int nGloryValue, int nGloryType )
{
	int tGlory = 0;
	int tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetGloryLimitByLevel( m_nLevel, tGlory );

	// �Ѿ���������
	if ( tRet == -1 )
	{
		return ERROR_FAMILY_LEVELUP_LEVELIMIT;
	}	

	if ( tGlory <= 0 || m_nGlory >= tGlory )
	{
		return	ERROR_FAMILY_LEVELUP_LEVELIMIT;
	}	
		
	m_nGlory = nGloryValue+m_nGlory > tGlory ? tGlory:nGloryValue+m_nGlory;
	SetSaveStatus( FAMILY_PROPERYCHANGED ); 
	return SUCCESS;
}

// ***********************************************************
//  Function:		ReduceGlory
//  Description:	������ҫ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::ReduceGlory( int nGloryValue, int nGloryType )
{
	m_nGlory = ( m_nGlory - nGloryValue ) > 0 ? ( m_nGlory - nGloryValue ):0;
	SetSaveStatus( FAMILY_PROPERYCHANGED ); 	
	if ( m_nLevel <= 1 )
	{
		return SUCCESS;		
	}
	
	
			
	// �Ƿ�Ӧ�ý���
	if ( nGloryType == 0 )
	{
		return SUCCESS;
	}
	int tGlory = 0;
	int tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetGloryLevelUPNeeded( m_nLevel-1, tGlory );
	
	while ( m_nLevel > 1 )
	{
		if ( tRet == SUCCESS && m_nGlory < tGlory )
		{
			--m_nLevel;
			tGlory = 0;
			tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetGloryLevelUPNeeded( m_nLevel-1, tGlory );			
		}
		break;
	}		
			
	
	return SUCCESS;	
}

// ***********************************************************
//  Function:		GetTotalCorpsContribute
//  Description:	��ȡ����Ծ��ŵ��ܹ��׶�
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::GetTotalCorpsContribute( )
{
	if ( m_tMembers.empty() )
	{
		return 0; 
	}
	
	members_t::iterator it = m_tMembers.begin();
	int tContribute = 0;
	for ( ; it != m_tMembers.end(); ++it )
	{
		tContribute += (it->second).mCorpsContribue;		
	}
	return tContribute;		
}

// ***********************************************************
//  Function:		AddPVPScore
//  Description:	����pvp����
//  Output:			bool �Ǽ��Ƿ�����
//  Date:	08/25/2009
// **********************************************************
bool  CFamily::AddPVPScore( int nValue, int nFailedFamilyLevel, int nType /* = 0 */ )
{	
	int	 tPvpScore = 0;
	int tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetPVPScoreLimit( m_nPVPStarLevel, tPvpScore );
	if ( tRet == -1 )
	{
		return false;
	}
	
	if ( tPvpScore == -1 )
	{
		return false;
	}	
	
	nValue = 100 - ( m_nPVPStarLevel - nFailedFamilyLevel )*nValue; //- ( m_nPVPStarLevel - 1 )*nValue;
	if ( nValue <= 0 )
	{
		return false;
	}  	
				
	m_nPVPScore += nValue;		
			
	int tLevelUP = false;
	while( tRet != -1 && m_nPVPScore >= tPvpScore )
	{
		++m_nPVPStarLevel;
		tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetPVPScoreLimit( m_nPVPStarLevel, tPvpScore );
		tLevelUP = true;
	}					
		
	SetSaveStatus( FAMILY_PROPERYCHANGED );
	return tLevelUP;				
}

// ***********************************************************
//  Function:		AddPVPScore
//  Description:	����pvp����
//  Output:			bool �Ǽ��Ƿ�����
//  Date:	09/14/2009
// **********************************************************
bool CFamily::ReducePVPScore( int nValue, int nWinFamilyLevel, int nType /* = 0 */ )
{
	nValue = 20 + ( m_nPVPStarLevel - nWinFamilyLevel )*nValue + ( m_nPVPStarLevel - 1 )*5;			
	
	if ( nValue > 0 )
	{
		m_nPVPScore = ( m_nPVPScore - nValue ) > 0 ? m_nPVPScore - nValue : 0;
	}
	
	// ���pvp�ȼ���һ���򲻻ή��
	if ( m_nPVPStarLevel <= 1 )
	{
		return false;		
	}
	
	bool bLevelDown = false; 	
	
	for ( int i = m_nPVPStarLevel; i > 1;  --i )
	{
		int	 tPvpScore = 0;
		int tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetPVPScoreLimit( i - 1, tPvpScore );
		if ( tRet == -1 )
		{
			return false;
		}
		
		// �����ٽ�����
		if ( m_nPVPScore >= tPvpScore )
		{
			break;			
		}
		
		--m_nPVPStarLevel;
		bLevelDown = true;
	}
	return bLevelDown;
}

// ***********************************************************
//  Function:		GetMemberListOfPost
//  Description:	��ȡĳ��ְλ��Ա�б�
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::GetMemberListOfPost( int *pList, int& rNum, int nPost, int nType )
{
	if ( m_tMembers.empty() )
	{						
		return 0;
	}
	int nLength = rNum;
	rNum = 0;	
	members_t::iterator it = m_tMembers.begin();
	for ( ; it != m_tMembers.end(); ++it )
	{ 
		int tPost = 0;
		if ( nType ==  EM_FAMILYACTION )
		{								
			tPost = (it->second).mFamilyPost;
		}
		else
		{
			tPost = (it->second).mCorpsPost;
		}
		if ( tPost == nPost )
		{
			if ( rNum < nLength )
			{
				pList[rNum] = it->first;	
				++rNum;
			}			
		}				
	}

	return SUCCESS;			
}

// ***********************************************************
//  Function:		AddPVPWinNum
//  Description:	���Ӽ����pvpʤ������
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::AddPVPWinNum( int nNum )
{
	m_nPVPWinNum += nNum;
	SetSaveStatus( FAMILY_PROPERYCHANGED ); 
	return SUCCESS;
}

// ***********************************************************
//  Function:		AddPVPFailedNum
//  Description:	���Ӽ����pvpʧ�ܳ���
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::AddPVPFailedNum( int nNum )
{
	m_nPVPFailedNum += nNum;
	SetSaveStatus( FAMILY_PROPERYCHANGED ); 
	return SUCCESS;
}

// ***********************************************************
//  Function:		ConsumeFamilyMoney
//  Description:	���ļ����Ǯ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::ConsumeFamilyMoney( int nMoney, bool bFreeze )
{
	if ( nMoney < 0 )
	{
		return	ERROR_FAMILY_MONEYINVALIDE;
	}
	
	if ( nMoney > m_nMoney - m_nFreezeMoney )
	{
		return EM_MONEYNOTENOUGH;
	}
	if ( bFreeze == false )
	{		
		m_nMoney -= nMoney;
		
	}	
	else
	{
		m_nFreezeMoney += nMoney;
	}
	SetSaveStatus( FAMILY_PROPERYCHANGED );
	return SUCCESS;
}

// ***********************************************************
//  Function:		AddFamilyMoney
//  Description:	���Ӽ����Ǯ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamily::AddFamilyMoney( int nMoney, bool bFreeze )
{
	if ( nMoney < 0 )
	{
		return -1;
	}	
	
	if ( bFreeze == false )
	{
		m_nMoney += nMoney;				
		if ( m_nMoney >= MAX_FAMILYCORPS_MONEY || m_nMoney < 0 )
		{
			m_nMoney = MAX_FAMILYCORPS_MONEY;
		}
	}
	else
	{
		m_nFreezeMoney -= nMoney;
	}
	SetSaveStatus( FAMILY_PROPERYCHANGED );
	return SUCCESS;			
}

// ***********************************************************
//  Function:		RefreshStatus
//  Description:	����ˢ��һЩ����
//  Output:			
//  Date:	09/01/2009
// **********************************************************
int CFamily::RefreshStatus( )
{	
	m_nFamilyActivityStatus &= ~FAMILY_STATUS_FAMILYEXPCARD;	
	ClearMemberOnLineTime();
	return SUCCESS;	
}

// ***********************************************************
//  Function:		CanFamilyLevelUp
//  Description:	�����Ƿ��������
//  Output:			
//  Date:	09/27/2009
// **********************************************************
bool CFamily::CanFamilyLevelUp( )
{
	int tGloryUPNeeded = 0;
	int tRet = CFamilyManager::GetSingleton().GetFamilyConfig()->GetGloryLevelUPNeeded( m_nLevel, tGloryUPNeeded );	

	// �Ѿ���������
	if ( tRet == -1 )
	{
		return false;
	}	

	if ( tGloryUPNeeded == -1 )
	{
		return	false;
	}


	if ( m_nGlory < tGloryUPNeeded )
	{	
		return false;
	}

	// �жϼ����Ǯ
	int tMoneyLevelUpNeeded = 0;
	CFamilyManager::GetSingleton().GetFamilyConfig()->GetMoneyLevelUPNeeded( m_nLevel, tMoneyLevelUpNeeded );
	if ( tMoneyLevelUpNeeded > m_nMoney || tMoneyLevelUpNeeded < 0 )
	{
		return	false;
	}
	return true;		
}

// ***********************************************************
//  Function:		GetLevelCondition
//  Description:	��ȡ������Ҫ�Ľ�Ǯ����ҫ
//  Output:			
//  Date:	01/20/2010
// **********************************************************
int CFamily::GetLevelCondition( int &rMoney, int &rGlory )
{	
	CFamilyManager::GetSingleton().GetFamilyConfig()->GetGloryLimitByLevel( m_nLevel, rGlory );	
	CFamilyManager::GetSingleton().GetFamilyConfig()->GetMoneyLevelUPNeeded( m_nLevel, rMoney );
	return SUCCESS;
}

// ***********************************************************
//  Function:		InitialOrganization
//  Description:	��ʼ��ְλϵͳ
//  Output:			
//  Date:	10/20/2009
// **********************************************************
int CFamily::InitialOrganization()
{
	memset( m_tOfficers, 0, sizeof( m_tOfficers ) );
	// �����峤��ְλ
	int tPostRight = EM_CREATE_OFFICER | EM_GRANT_RIGHTS | EM_INVITE_MEMBER | EM_APPROVE_APPLY | EM_FIRE_MEMBER | EM_GRANT_SETOFFICER
		| EM_LIST_APPLY | EM_CHANGE_BULLETIN | EM_ACTVITY_REDSTONE | EM_TASK_CONVOY | EM_MONEY_REIN | EM_WAR_RID | EM_WAR_HALL | EM_WAR_HALL | EM_WAR_CHALLENGE | 
		EM_WAR_SETFIGHTER | EM_WELFARE_OBTAIN | EM_WARNPC_GIVEUP | EM_RIGHT_DISBAND | EM_RIGHT_CANCELDISBAND | EM_RIGHT_CHALLENGEROOM | EM_RIGHT_BUYFAMILYCORPSITEM | EM_RIGHT_STARTFAMILYBOSS;	
	m_tOfficers[FAMILY_POST_HEADER].mLabel.SetRight( (EmRight)tPostRight ); 
	
	// ���ó��ϵ�Ȩ��
	tPostRight = EM_INVITE_MEMBER | EM_APPROVE_APPLY | EM_FIRE_MEMBER | EM_GRANT_SETOFFICER
		| EM_LIST_APPLY | EM_CHANGE_BULLETIN | EM_ACTVITY_REDSTONE | EM_TASK_CONVOY | EM_MONEY_REIN | EM_WAR_RID | EM_WAR_HALL | EM_WAR_HALL 
		| EM_WAR_SETFIGHTER | EM_WELFARE_OBTAIN |  EM_RIGHT_CHALLENGEROOM| EM_WAR_CHALLENGE|EM_RIGHT_STARTFAMILYBOSS;	
	m_tOfficers[FAMILY_POST_PRESBYTER].mLabel.SetRight( (EmRight)tPostRight ); 
	
	// �������˵�Ȩ��
	m_tOfficers[FAMILY_POST_BUSINESSMAN].mLabel.SetRight( (EmRight)0 );  	
	
	// �������˵�Ȩ��
	m_tOfficers[FAMILY_POST_MEMEBER].mLabel.SetRight( (EmRight)0 );  	
	return SUCCESS;
}

// ***********************************************************
//  Function:		PostHasRight
//  Description:	�ж�ְλ��Ȩ�޵Ķ�Ӧ��ϵ
//  Output:			
//  Date:	10/20/2009
// **********************************************************
bool CFamily::PostHasRight( int nPost, int nRight )
{	
	if ( nPost >= FAMILY_POST_HEADER && nPost <= FAMILY_POST_MEMEBER )
	{
		return m_tOfficers[nPost].mLabel.HasRight( (EmRight)nRight ); 
	}
	
	return false;
}

// ***********************************************************
//  Function:		ListMemberOfRight
//  Description:	��ȡ��ĳ��Ȩ�޵�����б�
//  Output:			
//  Date:	10/22/2009
// **********************************************************
int CFamily::ListMemberOfRight( int *pIDList, int *pPost, int *pContributeList, int &rNum, int nRight )
{
	LK_ASSERT( pIDList != NULL && pPost != NULL && pContributeList != NULL, return -1 )		
	int tNum = rNum;
	rNum = 0;	

	for ( members_t::iterator it = m_tMembers.begin() ; it != m_tMembers.end() && rNum < tNum; ++it )
	{			
		if ( PostHasRight( (it->second).mFamilyPost, nRight ) )
		{
			pIDList[rNum] = it->first;
			pPost[rNum]	= (it->second).mFamilyPost;	
			pContributeList[rNum] = (it->second).mFamilyContribue;	
			++rNum;
		}		
	}	
	return SUCCESS;
}	

// ***********************************************************
//  Function:		SetFamilyRepetionInfo
//  Description:	���ü��帱����Ϣ
//  Output:			
//  Date:	11/27/2009
// **********************************************************
int CFamily::SetFamilyRepetionInfo( KEY_TYPE nRepetionKey, int nLevel )
{
	/*if ( nRepetionKey != 0 )	
	{
		return -1;
	}*/
	m_nFamilyBossKey = nRepetionKey;
	m_nFamilyRepetionLevel = nLevel;		
	return SUCCESS;	
}

// ***********************************************************
//  Function:		ClearFamilyRepetionInfo
//  Description:	��ռ��帱����Ϣ
//  Output:			
//  Date:	11/27/2009
// **********************************************************
int CFamily::ClearFamilyRepetionInfo(  )
{
	m_nFamilyBossKey = 0;
	m_nFamilyRepetionLevel  = 0;	
	return SUCCESS;
}		

// ***********************************************************
//  Function:		ClearFamilyRepetionInfo
//  Description:	��鸱������ʱ��
//  Output:			
//  Date:	11/27/2009
// **********************************************************
bool CFamily::CheckRepetionDate( int nDate, int nMaxTimes, int nMaxWeekNum )
{
	// ��鱾�ܴ���
	if ( IsANewWeek( m_nRepetionDate, nDate ) == false && nMaxWeekNum > 0 )
	{
		if ( m_nWeekNum >= nMaxWeekNum )
		{
			return false;
		}
	}
	
	// ��鵱�����
	if ( IsANewDay( m_nRepetionDate,  nDate ) == false && nMaxTimes > 0 )
	{			
		if ( m_nRepetionOpenTimes >= nMaxTimes )
		{
			return false;
		}
	}

	if ( IsANewDay( m_nRepetionDate, nDate ) == true )
	{
		m_nRepetionOpenTimes = 0;
	}

	if ( IsANewWeek( m_nRepetionDate, nDate ) == true )
	{
		m_nWeekNum= 0;		
	}
	return true;	
}

// ***********************************************************
//  Function:		GetFamilyShopPBInfo
//  Description:	��ȡ�����̵��pb��Ϣ
//  Output:			
//  Date:	01/11/2010
// **********************************************************
int CFamily::GetFamilyShopPBInfo( PBLeagueShopsListInfo &rPbInfo )
{
	m_tFamilyShop.GetShopListInfo( rPbInfo );
	return SUCCESS;
}

// ***********************************************************
//  Function:		SetFamilyShopFromPBInfo
//  Description:	ͨ�������̵��pb�ṹ��Ϣ���ü����̵�
//  Output:			
//  Date:	01/11/2010
// **********************************************************
int CFamily::SetFamilyShopFromPBInfo( PBLeagueShopsListInfo &rPbInfo )
{
	m_tFamilyShop.SetShopListInfo( rPbInfo );
	return SUCCESS;
}


// ***********************************************************
//  Function:		GetShopErrcode
//  Description:	��ȡ�̵�Ĵ�����
//  Output:			
//  Date:	01/12/2010
// **********************************************************
int CFamily::GetShopErrcode( int nErrcode, int &rShopErrcode )
{
	switch ( nErrcode )
	{
		case SUCCESS:
		{
			rShopErrcode = SUCCESS;
			break;
		}
		case CLeagueShopInfo::SHOPEEROR_EXCHANGEGOODS_NPCHASNOITEM:
		{			
			rShopErrcode = ERROR_FAMILY_FAMILYGOODS_CANOTBUY;
			break;
		}	
		
		case CLeagueShopInfo::SHOPERROR_BUYGOODS_ITEMNOTENOUGH:
		{
			rShopErrcode = ERROR_FAMILY_FAMILYGOODS_ITEMNOTENGOUGH;
			break;
		}		
		
		case CLeagueShopInfo::SHOPERROR_BUYGOODS_WRONGTEMP:
		{
			rShopErrcode = ERROR_FAMILY_FAMILYGOODS_CANOTBUY;
			break;
		}
		
		case CLeagueShopInfo::SHOPERROR_EXCHANGEGOODS_NPCHASNOCOMPOSEID:
		{				
			rShopErrcode = ERROR_FAMILY_EXCHANGE_ITEMNOTENOUGH;
			break;
		}
		
		case CLeagueShopInfo::SHOPERROR_EXCHANGEGOODS_WRONGTEMP:
		{
			rShopErrcode = ERROR_FAMILY_EXCHANGE_NOTALLOWED;
			break;
		}		
		
		default:
			return -1;
	}	
	return SUCCESS;
}

// ***********************************************************
//  Function:		CheckFamilyMoneyEnough
//  Description:	�жϼ����Ǯ�Ƿ��㹻
//  Output:			
//  Date:	01/12/2010
// **********************************************************
bool CFamily::CheckFamilyMoneyEnough( int nMoney )
{
	if ( nMoney < 0 )
	{
		return	false;
	}

	if ( nMoney > m_nMoney - m_nFreezeMoney )
	{
		return false;
	}	
	return true;
}

// ***********************************************************
//  Function:		InsertGoodInfo
//  Description:	����һ����Ʒ��Ϣ
//  Output:			
//  Date:	01/10/2010
// **********************************************************
int CLeagueShopInfo::InsertGoodInfo( int nItemID, CGoodSInfo &rGoodInfo )
{ 
	GoodsList::iterator it = mGoodsList.find( nItemID );
	if ( it != mGoodsList.end() )
	{
		(it->second).mItemNum	= rGoodInfo.mItemNum;
		(it->second).mComposeID = rGoodInfo.mComposeID;
		(it->second).mPurcharseTime = rGoodInfo.mPurcharseTime;
		(it->second).mItemID		= rGoodInfo.mItemID;
	}
	else
	{	
		mGoodsList.insert( GoodsList::value_type( nItemID, rGoodInfo ) );
	}
	return SUCCESS;	
}

// ***********************************************************
//  Function:		DeleteGoodInfo
//  Description:	ɾ��һ����Ʒ��Ϣ
//  Output:			
//  Date:	01/10/2010
// **********************************************************
int CLeagueShopInfo::DeleteGoodInfo( int nItemID )
{  
	GoodsList::iterator it = mGoodsList.find( nItemID );
	if ( it != mGoodsList.end() )
	{
		mGoodsList.erase( it );
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetGoodInfo
//  Description:	��ȡĳ����Ʒ����Ϣ
//  Output:			
//  Date:	01/10/2010
// **********************************************************
CGoodSInfo *CLeagueShopInfo::GetGoodInfo( int nItemID )
{
	GoodsList::iterator it = mGoodsList.find( nItemID );
	if ( it != mGoodsList.end() )
	{
		return &(it->second);
	}
	return NULL;
}

// ***********************************************************
//  Function:		GetGoodInfo
//  Description:	��ȡ��Ʒ���б�
//  Output:			
//  Date:	01/10/2010
// **********************************************************
int CLeagueShopInfo::GetGoodsList( PBLeagueShopInfo &rLeagueShop )
{
	for ( GoodsList::iterator it = mGoodsList.begin(); it != mGoodsList.end(); ++it )
	{
		PBGoodItemInfo *tpGoodInfo = rLeagueShop.add_iteminfo();
		tpGoodInfo->set_composeid( (it->second).mComposeID );
		tpGoodInfo->set_itemnum( (it->second).mItemNum );
		tpGoodInfo->set_itemid( (it->second).mItemID );
		tpGoodInfo->set_purcharsetime( (it->second).mPurcharseTime );
	}
	rLeagueShop.set_shoptype( mShopType );	
	rLeagueShop.set_shopid( mShopID );
	return SUCCESS;
}

// ***********************************************************
//  Function:		SetGoodsList
//  Description:	������Ʒ�б�
//  Output:			
//  Date:	01/10/2010
// **********************************************************
int CLeagueShopInfo::SetGoodsList( PBLeagueShopInfo &rLeagueShop )
{
	
	for ( int i = 0; i < rLeagueShop.iteminfo_size(); ++i )
	{
		if ( rLeagueShop.mutable_iteminfo( i )->itemid() <= 0 )
		{
			continue;
		}
		CGoodSInfo tGoodInfo;
		tGoodInfo.mComposeID = rLeagueShop.mutable_iteminfo( i )->composeid();
		tGoodInfo.mItemID	 = rLeagueShop.mutable_iteminfo( i )->itemid();
		tGoodInfo.mItemNum	= rLeagueShop.mutable_iteminfo( i )->itemnum();
		tGoodInfo.mPurcharseTime = rLeagueShop.mutable_iteminfo( i )->purcharsetime();
		mGoodsList.insert( GoodsList::value_type( tGoodInfo.mItemID, tGoodInfo ) );
	}
	mShopID = rLeagueShop.shopid();
	mShopType = rLeagueShop.shoptype();	
	return SUCCESS;
} 

// ***********************************************************
//  Function:		RefreshShopGoodsInfo
//  Description:	ˢ����Ʒ��Ϣ(ֻ����ս���̵�)
//  Output:			
//  Date:	01/11/2010
// **********************************************************
int CLeagueShopInfo::RefreshShopGoodsInfo( )
{	
	int tRefreshResult =  REFRESH_ITEMNOCHANGE;
	if ( mShopType != SHOPTYPE_WARNPC )
	{
		return tRefreshResult;
	}	
	
	CTemplateSellTable *tpTmpSellTable = ( CTemplateSellTable * )CDataStatic::SearchTpl( mShopID );
	LK_ASSERT( tpTmpSellTable != NULL, return -1 )
	
	for ( GoodsList::iterator it = mGoodsList.begin(); it != mGoodsList.end();  )
	{
		 int tPageIndex = -1;
		 int tItemIndex = -1;
		 for ( int i = 0; i < (int)ARRAY_CNT( tpTmpSellTable->mItem ); ++i )
		 {
			for ( int j = 0; j < (int)ARRAY_CNT( tpTmpSellTable->mItem[0].mItemID ); ++j )
			{
				if ( tpTmpSellTable->mItem[i].mItemID[j] == it->first )
				{
					tPageIndex = i;
					tItemIndex = j;
					break;
				}
			}
		 }
		 
		 if ( tPageIndex != -1 && tItemIndex != -1 )
		 {
			if ( ( time(NULL) - (it->second).mPurcharseTime ) >= tpTmpSellTable->mItemRefreshDay[tPageIndex][tItemIndex]*3600 )
			{
				mGoodsList.erase( it++ );
				tRefreshResult = REFRESH_ITEMCHANGED;
			}
			else
			{
				++it;
			}
		 }
		 else
		 {
			++it;
		 }
	}	
	return tRefreshResult;
}

// ***********************************************************
//  Function:		BuyItem
//  Description:	����ĳ����Ʒ
//  Input:			int nSellTableType �̵�����(CTemplateSellTable::EM_SELLTABLETYPE)	
//  Input:			int nIndex ��Ʒ�ڳ��۱��е�����
//  Output:			
//  Date:	01/11/2010
// **********************************************************
int CLeagueShopsManager::BuyItem( int nSellTableID, int nItemID, int nNum )
{		
	if ( nNum <= 0 )
	{
		return -1;
	}
	
	int tGoldPrice = 0;
	CGoodSInfo tTempGoodInfo;
	int tRet = GetItemInfoInSellTable( nSellTableID, nItemID, tTempGoodInfo, tGoldPrice );
	if ( tRet != SUCCESS )
	{
		return tRet;
	}	
	
	// �ж���Ʒ����
	LeagueShopsList::iterator it = mLeagueShopsList.find( nSellTableID );
	
	// �Ѿ���������̵����Ʒ	
	if ( it != mLeagueShopsList.end() )
	{	
		CLeagueShopInfo *tpLeagueShop = ( CLeagueShopInfo * )CGateObjManager::GetSingleton().GetObject( it->second );
		if ( tpLeagueShop == NULL )
		{
			return -1;
		}				
				
		// ˢ����Ʒ
		if ( tpLeagueShop->RefreshShopGoodsInfo() == CLeagueShopInfo::REFRESH_ITEMCHANGED )
		{
			SetSaveStatus( true );
		}
		
		CGoodSInfo *tpGoodInfo = tpLeagueShop->GetGoodInfo( nItemID ); 
								
		// �Ѿ����������Ʒ
		if ( tpGoodInfo != NULL )
		{
			if ( tpGoodInfo->mItemNum < nNum )
			{
				return CLeagueShopInfo::SHOPERROR_BUYGOODS_ITEMNOTENOUGH;
			}
			
			tpGoodInfo->mItemNum -= nNum;
			if ( tpGoodInfo->mPurcharseTime == 0 )
			{
				tpGoodInfo->mPurcharseTime = time( NULL );
			}
		}
		else
		{
			if ( tTempGoodInfo.mItemNum < nNum )
			{
				return CLeagueShopInfo::SHOPERROR_BUYGOODS_ITEMNOTENOUGH;
			}
			CGoodSInfo tGoodInfo;
			tGoodInfo.mItemID = nItemID;
			tGoodInfo.mItemNum = tTempGoodInfo.mItemNum - nNum;	
			tGoodInfo.mPurcharseTime = time( NULL );
			tpLeagueShop->InsertGoodInfo( nItemID, tGoodInfo );
		}
	}
	
	// ��û�й�������̵����Ʒ
	else
	{			
		if ( tTempGoodInfo.mItemNum < nNum )
		{
			return CLeagueShopInfo::SHOPERROR_BUYGOODS_ITEMNOTENOUGH; 
		}
		CGoodSInfo tGoodInfo;
		tGoodInfo.mItemID = nItemID;
		tGoodInfo.mItemNum = tTempGoodInfo.mItemNum - nNum;	
		tGoodInfo.mPurcharseTime = time( NULL );
		
		CLeagueShopInfo *tpLeagueShopInfo = ( CLeagueShopInfo * )CGateObjManager::GetSingleton().CreateObject( OBJTYPE_LEAGUESHOP );
		if ( tpLeagueShopInfo == NULL )
		{
			return -1;
		}
		tpLeagueShopInfo->SetShopType( CLeagueShopInfo::SHOPTYPE_WARNPC );
		tpLeagueShopInfo->SetShopID( nSellTableID );	
		tpLeagueShopInfo->InsertGoodInfo( nItemID, tGoodInfo );
		
		mLeagueShopsList.insert( LeagueShopsList::value_type( nSellTableID, tpLeagueShopInfo->get_id() ) );
	}
	SetSaveStatus( true );
	return SUCCESS;
}

// ***********************************************************
//  Function:		ExchangeItem
//  Description:	�һ�ĳ����Ʒ
//  Output:			
//  Date:	01/11/2010
// **********************************************************
int CLeagueShopsManager::ExchangeItem( int nExchangeID, int nItemID, int nNum, int nComposeID )
{  
	CLeagueShopInfo *tpLeagueShop = GetLeagueShopInfo( nExchangeID );
	if ( tpLeagueShop == NULL )
	{
		return CLeagueShopInfo::SHOPEEROR_EXCHANGEGOODS_NPCHASNOITEM;
	}
	
	CGoodSInfo *tpGoodInfo = tpLeagueShop->GetGoodInfo( nItemID );
	if ( tpGoodInfo == NULL )
	{
		return CLeagueShopInfo::SHOPEEROR_EXCHANGEGOODS_NPCHASNOITEM;
	}
	
	if ( tpGoodInfo->mComposeID != nComposeID )
	{
		return CLeagueShopInfo::SHOPEEROR_EXCHANGEGOODS_NPCHASNOITEM;
	}
	
	if ( tpGoodInfo->mItemNum < nNum )
	{
		return CLeagueShopInfo::SHOPEEROR_EXCHANGEGOODS_NPCHASNOITEM;
	}
	tpGoodInfo->mItemNum -= nNum;
	if ( tpGoodInfo->mItemNum <= 0 )
	{
		tpLeagueShop->DeleteGoodInfo( tpGoodInfo->mItemID );
	}	
	SetSaveStatus( true );
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetShopListInfo
//  Description:	��ȡ�̵��б�
//  Output:			
//  Date:	01/11/2010
// **********************************************************
int CLeagueShopsManager::GetShopListInfo( PBLeagueShopsListInfo &rShopList )
{
	for ( LeagueShopsList::iterator it = mLeagueShopsList.begin(); it != mLeagueShopsList.end(); ++it )
	{	 		 
		 CLeagueShopInfo *tpLeagueShop = ( CLeagueShopInfo * )CGateObjManager::GetSingleton().GetObject( it->second );
		 if ( tpLeagueShop == NULL )
		 {
			continue;	
		 }
		 PBLeagueShopInfo *tpLeaguShopInfo = rShopList.add_leagueshopinfo();
		 tpLeagueShop->GetGoodsList( *tpLeaguShopInfo );		
	}
	return SUCCESS;
}


// ***********************************************************
//  Function:		SetShopListInfo
//  Description:	�����̵��б�
//  Output:			
//  Date:	01/11/2010
// **********************************************************
int CLeagueShopsManager::SetShopListInfo( PBLeagueShopsListInfo &rShopList )
{
	for ( int i = 0; i < rShopList.leagueshopinfo_size(); ++i )
	{
		CLeagueShopInfo *tpLeagueShop = ( CLeagueShopInfo * )CGateObjManager::GetSingleton().CreateObject( OBJTYPE_LEAGUESHOP );
		LK_ASSERT( tpLeagueShop != NULL, return -1 )
		tpLeagueShop->SetGoodsList( *rShopList.mutable_leagueshopinfo( i ) );		
		mLeagueShopsList.insert( LeagueShopsList::value_type( rShopList.mutable_leagueshopinfo( i )->shopid(), tpLeagueShop->get_id() ) );
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetItemInfoInSellTable
//  Description:	��ȡ���۱���ĳ����Ʒ����Ϣ
//  Output:			
//  Date:	01/11/2010
// **********************************************************
int CLeagueShopsManager::GetItemInfoInSellTable( int nSellTableID,  int nItemID, CGoodSInfo &rGoodInfo, int &rGoldPrice )
{	
	// ��ȡnpc�ĳ��۱���Ϣ
	CTemplateSellTable *tpSellTable = ( CTemplateSellTable * )CDataStatic::SearchTpl( nSellTableID );
	if ( tpSellTable == NULL )
	{
		return CLeagueShopInfo::SHOPERROR_BUYGOODS_WRONGTEMP;
	}

	// �鿴���۱��Ƿ�ս���̵�	
	for ( int i = 0; i < (int)ARRAY_ROW( tpSellTable->mItem ); ++i )
	{
		for ( int j = 0; j < (int)ARRAY_CNT( tpSellTable->mItem[0].mItemID ); ++j )
		{
			if ( tpSellTable->mItem[i].mItemID[j] == nItemID )
			{
				rGoodInfo.mItemID = nItemID;
				rGoodInfo.mItemNum = tpSellTable->mItemNum[i][j];				
				rGoldPrice = tpSellTable->mItemGoldPrice[i][j];
				break;
			}
		}
	}

	return SUCCESS;
}

// ***********************************************************
//  Function:		GetItemInfoInExchangeShop
//  Description:	��ȡ�̵���ĳ����Ʒ����Ϣ
//  Output:			
//  Date:	01/13/2010
// **********************************************************
int CLeagueShopsManager::GetExchangeShopItemInfo( int nExchangeID, int nItemID, CGoodSInfo &rGoodInfo )
{			
	rGoodInfo.mComposeID = 0;
	rGoodInfo.mItemID = nItemID;
	rGoodInfo.mItemNum = 0;
	CLeagueShopInfo *tpLeagueShop = GetLeagueShopInfo( nExchangeID );
	if ( tpLeagueShop == NULL )
	{
		return CLeagueShopInfo::SHOPEEROR_EXCHANGEGOODS_NPCHASNOITEM;
	}
	
	CGoodSInfo *tpGoodInfo = tpLeagueShop->GetGoodInfo( nItemID );
	if ( tpGoodInfo == NULL )
	{
		return CLeagueShopInfo::SHOPEEROR_EXCHANGEGOODS_NPCHASNOITEM;
	}
	
	rGoodInfo.mItemNum = tpGoodInfo->mItemNum;	
	rGoodInfo.mComposeID = tpGoodInfo->mComposeID;
	return SUCCESS;
}

// ***********************************************************
//  Function:		InsertExchangeItem
//  Description:	����һ���ɶһ�����Ʒ
//  Input:			int nExchangeType �һ�����	
//  Output:			
//  Date:	01/11/2010
// **********************************************************
int CLeagueShopsManager::InsertExchangeItem( int nExchangeID, int nItemID, int nItemNum )
{
	if ( nItemNum <= 0 || nExchangeID <= 0 || nItemID <= 0 )
	{
		return -1;
	}
	
	// ��ȡ�һ���
	CTempateEquipExchangeTable *tpTable = ( CTempateEquipExchangeTable * )CDataStatic::SearchTpl( nExchangeID );
	if ( tpTable == NULL )
	{
		return CLeagueShopInfo::SHOPERROR_EXCHANGEGOODS_WRONGTEMP;
	}
		
	// ����Ƿ��и��Ӻϳ�ID
	bool tHasCompose = false;
	int	tComposeID	=	0;
	for ( int i = 0; i < (int)ARRAY_CNT( tpTable->mMultiComposeID ); ++i )
	{
		CTemplateMultiCompose *tpTplCompose = ( CTemplateMultiCompose * )CDataStatic::SearchTpl( tpTable->mMultiComposeID[i] );
		if ( tpTplCompose == NULL )
		{
			continue;
		}
		if ( nItemID == tpTplCompose->mItemID[0] )
		{
			tHasCompose = true;
			tComposeID = tpTplCompose->mTempID;
			break;			
		}
	}
	
	if ( tHasCompose == false )
	{
		return	CLeagueShopInfo::SHOPERROR_EXCHANGEGOODS_NPCHASNOCOMPOSEID;
	}
	
	LeagueShopsList::iterator it = mLeagueShopsList.find( nExchangeID );
		
	// �Ѿ����и�npc��Ϣ
	if ( it != mLeagueShopsList.end() )
	{
		CLeagueShopInfo *tpLeagueShop = ( CLeagueShopInfo * )CGateObjManager::GetSingleton().GetObject( it->second );
		LK_ASSERT( tpLeagueShop != NULL, return -1 )
		
		CGoodSInfo *tpGoodInfo = tpLeagueShop->GetGoodInfo( nItemID );
		if ( tpGoodInfo != NULL )
		{
			tpGoodInfo->mItemNum += nItemNum;	
			tpGoodInfo->mComposeID = tComposeID;		
		}
		else
		{
			CGoodSInfo tGoodInfo;
			tGoodInfo.mComposeID = tComposeID;
			tGoodInfo.mItemID = nItemID;
			tGoodInfo.mItemNum = nItemNum;		
			tpLeagueShop->InsertGoodInfo( nItemID, tGoodInfo );
		}
	}
	else
	{
		CGoodSInfo tGoodInfo;
		tGoodInfo.mComposeID = tComposeID;
		tGoodInfo.mItemID = nItemID;
		tGoodInfo.mItemNum = nItemNum;
		
		CLeagueShopInfo *tpLeagueShopInfo = ( CLeagueShopInfo * )CGateObjManager::GetSingleton().CreateObject( OBJTYPE_LEAGUESHOP );
		LK_ASSERT( tpLeagueShopInfo != NULL, return -1 )
		tpLeagueShopInfo->SetShopType( CLeagueShopInfo::SHOPTYPE_EXCHANGE );
		tpLeagueShopInfo->SetShopID( nExchangeID );		
		tpLeagueShopInfo->InsertGoodInfo( nItemID, tGoodInfo );		
		mLeagueShopsList.insert( LeagueShopsList::value_type( nExchangeID, tpLeagueShopInfo->get_id() ) );
	}
	
	SetSaveStatus( true );
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetShopInfo
//  Description:	��ȡĳ���̵����Ϣ
//  Input:			
//  Output:			
//  Date:	01/12/2010
// **********************************************************
int CLeagueShopsManager::GetShopInfo( int nShopID, PBLeagueShopInfo &tShopInfo )
{
	CLeagueShopInfo *tpLeagueShop = GetLeagueShopInfo( nShopID );
	if ( tpLeagueShop != NULL )
	{
		/*if ( tpLeagueShop->CheckRefreshTime() && tpLeagueShop->GetShopType() == CLeagueShopInfo::SHOPTYPE_WARNPC )
		{
			tpLeagueShop->ResetRefreshTime();*/
			if ( tpLeagueShop->RefreshShopGoodsInfo() == CLeagueShopInfo::REFRESH_ITEMCHANGED )
			{
				SetSaveStatus( true );			
			}
			
		//}
		tpLeagueShop->GetGoodsList( tShopInfo );
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetLeagueShopInfo
//  Description:	��ȡĳ���̵����Ϣ
//  Input:			
//  Output:			
//  Date:	01/12/2010
// **********************************************************
CLeagueShopInfo *CLeagueShopsManager::GetLeagueShopInfo( int nShopID )
{
	LeagueShopsList::iterator it = mLeagueShopsList.find( nShopID );
	CLeagueShopInfo *tpLeagueShop = NULL;
	if ( it != mLeagueShopsList.end() )
	{
		tpLeagueShop = ( CLeagueShopInfo * )CGateObjManager::GetSingleton().GetObject( it->second );		
	}
	return tpLeagueShop;
}	 


// ***********************************************************
//  Function:		GetWarShopItemInfo
//  Description:	��ȡս���̵���ĳ����Ʒ��������Ϣ(�ɹ�������)
//  Input:			
//  Output:			
//  Date:	01/12/2010
// **********************************************************
int CLeagueShopsManager::GetWarShopItemInfo( int nSellTableID, int nItemID, CGoodSInfo &rGoodInfo, int &rGoldPrice )
{		
	
	GetItemInfoInSellTable( nSellTableID, nItemID, rGoodInfo, rGoldPrice );

	CLeagueShopInfo *tpLeagueShop = GetLeagueShopInfo( nSellTableID );
	if ( tpLeagueShop != NULL )
	{
		CGoodSInfo *tpGoodInfo = tpLeagueShop->GetGoodInfo( nItemID );
		if ( tpGoodInfo != NULL )
		{
			rGoodInfo.mItemNum = tpGoodInfo->mItemNum;
			rGoodInfo.mItemID = nItemID;
		}
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		CheckFamilyRoleInfo
//  Description:	������ĳ�Ա��Ϣ(�ɹ�������)
//  Input:			
//  Output:			
//  Date:	01/12/2010
// **********************************************************
int CFamily::CheckFamilyRoleInfo()
{
	for ( members_t::iterator it = m_tMembers.begin(); it != m_tMembers.end( );  )
	{	
		CRoleGlobalInfo *pPlayerInfo = CServiceRoleIDName::GetSingleton( ).GetRoleInfoByRoleID( it->first );
		if ( pPlayerInfo == NULL )
		{
			LOG_ERROR( "family", "can not find player info:%d ", it->first );
			if ( it->first == m_nRooter )
			{
				return EM_MEMBERINFO_NEEDDISBAD;
			}
			
			m_tMembers.erase( it++ );
			continue;
		}  		
		++it;
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		ReduceStabilityDegree
//  Description:	���ټ��尲����
//  Input:			
//  Output:			
//  Date:	12/01/2010
// **********************************************************
int CFamily::ReduceStabilityDegree( int nValue )
{
	if ( nValue <= 0 )
	{	
		return SUCCESS;
	}
	m_nStabilityDegree -= nValue;
	if ( m_nStabilityDegree < 0 )
	{
		m_nStabilityDegree = 0;
	}
	SetSaveStatus( FAMILY_PROPERYCHANGED );
	return SUCCESS;
}

// ***********************************************************
//  Function:		AddStabilityDegree
//  Description:	���Ӽ��尲����
//  Input:			
//  Output:			
//  Date:	12/01/2010
// **********************************************************
int CFamily::AddStabilityDegree( int nValue )
{
	if ( nValue <=0 )
	{
		return SUCCESS;
	}
	m_nStabilityDegree += nValue;
	SetSaveStatus( FAMILY_PROPERYCHANGED );
	return SUCCESS;		
}

// ***********************************************************
//  Function:		AddStabilityByMemberOnTime
//  Description:	��������ۻ��İ�����
//  Input:			
//  Output:			
//  Date:	12/16/2010
// **********************************************************
int CFamily::AddStabilityByMemberOnTime( int nRoleID, int nLevel, int nTime, int &rOnLineTime, int &rAddStability )
{
	rOnLineTime = 0;
	rAddStability = 0;
	family_info_t *tpMemberInfo = GetMemberFamilyInfo( nRoleID );
	if ( tpMemberInfo == NULL )
	{
		return -1;
	}
	
	if ( nTime <= 0 )
	{
		return SUCCESS;
	}
	
	int tOldTime = tpMemberInfo->mOnLineTime;
	int tNewTime = tOldTime + nTime;

	// ǰnСʱÿһСʱ��Ҫ���Ӱ�����,ֻ��ʾ���ʱ����ۻ�ֵ
	int tOldOnLineTime = 0;		// �Ѿ��ۼӵ�ʱ��
	CFamilyManager::GetSingleton().GetFamilyConfig()->GetStabilityConfig()->GetStabilityValue( nLevel, tOldTime, tOldOnLineTime );
	int tNewOnLineTime = 0;
	for ( int tTime = tOldTime; tTime <= tNewTime; ++tTime )
	{			
		int tNewStability = CFamilyManager::GetSingleton().GetFamilyConfig()->GetStabilityConfig()->GetStabilityValue( nLevel, tTime, tNewOnLineTime );
		if ( tNewOnLineTime > tOldOnLineTime && tNewStability > 0 )
		{
			m_nStabilityDegree += tNewStability;			
			rAddStability = tNewStability;			
			tOldOnLineTime = tNewOnLineTime;
		}					
	}	
	rOnLineTime = tNewOnLineTime;
	tpMemberInfo->mOnLineTime += nTime;
	return SUCCESS;
}

// ***********************************************************
//  Function:		ClearMemberOnLineTime
//  Description:	���������ҵ������ۻ�ʱ��
//  Input:			
//  Output:			
//  Date:	12/16/2010
// **********************************************************
int CFamily::ClearMemberOnLineTime()
{
	members_t::iterator it = m_tMembers.begin();
	for ( ; it != m_tMembers.end(); ++it )
	{
		(it->second).mOnLineTime = 0;
	}
	return SUCCESS;
}