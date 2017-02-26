#include "family_manager.h"
#include "message_pb.hxx.pb.h"
#include "familymessage_pb.hxx.pb.h"
#include "family.h"
#include "dirtyword.h"
#include "familydbinfo_pb.hxx.pb.h"
#include "gateobj_manager.h"
#include "gateobj_define.h"
#include "gatelogic.h"
#include "nameservice.h"
#include "lk_hashmap.h"	 
#include "corpsmanager.h"
#include "familyservice.h"
#include "core_service.h"
#include "repetionmodule.h"	
#include "log_tools.h"
#include "corpservice.h"

template<> CFamilyManager * CSingleton< CFamilyManager >::spSingleton = NULL;	
CSharedMem * CFamilyManager::mShmPtr = NULL;

// ***************************************************************
//  Function:       CFamilyManager
//  Description:	���캯��	
//  Input:         	
//  Input:			
//  OutPut:         
//  Return:         
//  Others:
//  Date:           04/24/2009
// 
// ***************************************************************
CFamilyManager::CFamilyManager( )
{		
	if( CObj::msCreateMode )
	{
		Initailize();
	}
	else
	{
		Resume();
	}		
}
 
// ***************************************************************
//  Function:       Initailize
//  Description:	��ʼ������	
//  Input:         	
//  Input:			
//  OutPut:         
//  Return:         
//  Others:
//  Date:           04/24/2009
// 
// ***************************************************************
int CFamilyManager::Initailize()
{  
	m_tFamilies.initailize();
	m_tApplies.initailize();	
	mNpcList.initailize();
	mNPCSubmitList.initailize();
	mBattleList.initailize();
	mRoomList.initailize();
	mFamilyReptionKeyList.initailize();
	return 0;
}

// ***************************************************************
//  Function:       Resume
//  Description:	����	
//  Input:         	
//  Input:			
//  OutPut:         
//  Return:         
//  Others:
//  Date:           04/24/2009
// 
// ***************************************************************
int CFamilyManager::Resume()
{
	return 0;
}


// ***************************************************************
//  Function:       operator new
//  Description:   	
//  Input:         	
//  Input:			
//  OutPut:         
//  Return:         
//  Others:
//  Date:           04/24/2009
// 
// ***************************************************************
void* CFamilyManager::operator new( size_t tSize )
{
	  return ( void* ) mShmPtr->CreateSegment( tSize );	  	  	  
}

// ***************************************************************
//  Function:       operator delete
//  Description:   	
//  Input:         	
//  Input:			
//  OutPut:         
//  Return:         
//  Others:
//  Date:           04/24/2009
// 
// ***************************************************************
void CFamilyManager::operator delete( void *pPointer )
{
	
}

// ***************************************************************
//  Function:      CountSize
//  Description:   	
//  Input:         	
//  Input:			
//  OutPut:         
//  Return:         
//  Others:
//  Date:           04/24/2009
// 
// ***************************************************************
unsigned int CFamilyManager::CountSize()
{
	return sizeof( CFamilyManager );
}

// ***************************************************************
//  Function:       OnEventEstablishFamily
//  Description:   	��������
//  Input:         	nRoleID			��ɫID
//  Input:			szFamilyName	��������
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:           04/24/2009
// 
// ***************************************************************
int CFamilyManager::OnEventEstablishFamily( roleid_t nRoleID, const char* szFamilyName, int &FamilyID )
{
	CGatePlayer *pRoleInfo = CPlayerManager::GetSingleton().ScenePlayer( nRoleID );
	if ( pRoleInfo == NULL )
	{
		LOG_ERROR( "family"," can not find player(CGatePlayer) (roleid:%d) ", nRoleID );
		return -1;
	}	
	
	// �ж���ɫ��û�м���	
	if ( GetFamilyOfPlayer( nRoleID ) != NULL )
	{
		return ERROR_FAMILY_CREATFAMILY_HASFAMILY;
	}
		
	// �жϴ�����ļ��������Ƿ����
	CFamily* pfamily = GetFamilyByName(szFamilyName);
	if ( pfamily != NULL )
	{
		// Send2Player(nARoleID, EFAMILY_CREATE_DUPNAME);
		// TODO:���������Ѿ����ڵĴ�����
		return ERROR_FAMILY_CREATFAMILY_NAMEEXIST;
	}

	//�ж�����ļ��������Ƿ�Ϸ�
	if ( CDirtyWord::GetSingleton().OI_Dirty_Check( 1, ( char * )szFamilyName ) != 0 )
	{
		// �������ƺ������
		return ERROR_FAMILY_CREATFAMILY_HASDIRTYWORD;
	}

	// ���������ü���ID
	pfamily = ( CFamily * )CGateObjManager::GetSingleton().CreateObject( OBJTYPE_FAMILY );
	if ( pfamily == NULL )
	{
		LOG_ERROR( "family","creat familyobj error by player(roleid:%d)", nRoleID );
		return -1;
	}
	
	pfamily->SetID( pfamily->get_id() ); 
	
	// ��ֵrooter��name
	pfamily->SetRooter( nRoleID );
	pfamily->SetName( szFamilyName );
	pfamily->SetRooterName( pRoleInfo->mCharName );
	pfamily->SetCountryID( pRoleInfo->mCountryID );	
	pfamily->SetCorpsID( 0 );	
	
	// ��ȡ��ʼ������
	int tStability = 0;
	GetFamilyConfig()->GetInitialStability( 1, tStability );
	if ( tStability <= 0 )
	{
		tStability = FAMILY_INITIAL_STABILITY;
	}
	pfamily->SetStabilityDegree( tStability );
	
	// ���������뵽�����б�����		 
	family_info_t nRooterInfor;
	nRooterInfor.mFamilyPost = ( labelid_t )FAMILY_POST_HEADER;	
	pfamily->GetMembers().insert( CFamily::members_t::value_type( nRoleID, nRooterInfor ) ); 
	
	#ifdef _GLOBAL_NAME_
	CGateLogic::GetSingleton().SendCreateGroupProto2ERating(
			nRoleID, szFamilyName, em_family_group, pfamily->get_id()); 
	#else

	// ���ݿ���� 
	CreatFamilyDBInfo( pfamily );
	
	// �����б�	 
	/*int tRet = InsertFamily( pfamily );
	if ( tRet != 0 )
	{
		CGateObjManager::GetSingleton().DestroyObject( pfamily->get_id() );
	}*/
	
	// ����洢״̬
	pfamily->ClearSaveStatus();
	
	// ��¼�¼���ID
	// FamilyID = pfamily->GetID();
	#endif
	return SUCCESS;
}  

// ***************************************************************
//  Function:       OnEventInvite2Family
//  Description:   	������Ҽ������
//  Input:         	nInvitingRoleID		���뷽��ɫID
//  Input:		    nInvitedRoleID		�����뷽��ɫID
//  Input:			nFamilyID			���뷽����ID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:			04/24/2009
// 
// ***************************************************************
int CFamilyManager::OnEventInvite2Family( roleid_t nInvitingRoleID, roleid_t nInvitedRoleID )
{
	// �жϼ����Ƿ����
	CFamily* pfamily = GetFamilyOfPlayer( nInvitingRoleID );
	if ( pfamily == NULL )
	{
		//TODO:
		return -1;
	}

	// �ж��������Ƿ���Ȩ������		
	if ( pfamily->GetRooter() != nInvitingRoleID )
	{				
		if ( !pfamily->MemberHasRight( nInvitingRoleID, EM_INVITE_MEMBER ) )
		{
			return ERROR_FAMILY_INVITE_HASNORIGHT;
		}	 		
	}

	// �жϱ��������Ƿ��Ѿ��м���::���ڳ����������ж�
	
	// �ж����뷽�ǲ����Լ�
	if ( nInvitingRoleID == nInvitedRoleID )
	{
		return ERROR_FAMILY_INVITE_SELFINVITE;
	}
	

	// �жϼ����Ƿ���Ա
	if (pfamily->IsFull())
	{
		return ERROR_FAMILY_INVITE_FAMILYFULL;
	}
	
	// ����ɹ�	 	
	return 0;
}

// ***************************************************************
//  Function:       OnEventRefusedByPlayer
//  Description:	���뱻�˾ܾ�
//  Input:         	nInvitingRoleID		���뷽��ɫID
//  Input:			nInvitedRoleID		�����뷽��ɫID
//  Input:			nFamilyID			����ID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:           04/24/2009
// 
// ***************************************************************
int CFamilyManager::OnEventRefusedByPlayer(roleid_t nInvitingRoleID, roleid_t nInvitedRoleID, int nFamilyID)
{
	// �жϼ����Ƿ����
	CFamily* pfamily = GetFamilyByID(nFamilyID);
	if (pfamily == NULL)
	{
		return -1;
	}
	return 0;
}			  

// ***************************************************************
//  Function:       OnEventAgreeedByPlayer
//  Description:   	nInvitedRoleID agree nInvitingRoleID 's inviting to nFamilyID
//  Input:         	nInvitingRoleID , nInvitedRoleID, nFamilyID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:           04/24/2009
// 
// ***************************************************************
int CFamilyManager::OnEventAgreeedByPlayer( roleid_t nInvitingRoleID, roleid_t nInvitedRoleID, int nFamilyID )
{
	// �жϼ����Ƿ����
	CFamily* pFamily = GetFamilyByID( nFamilyID );
	if ( pFamily == NULL )
	{
		LOG_ERROR( "family","can not find family by ID:%d", nFamilyID );
		return -1;
	}
	
	
	// ��������б�
	family_info_t tFamilyInfo;
	if (pFamily->Ins2Member(nInvitedRoleID, tFamilyInfo) != true)
	{  	
		// ͬ��ʱ�����Ѿ�����
		return ERROR_FAMILY_REPLYINVITE_FAMILYFULL;
	}

	// TODO:֪ͨ�������ߺͼ����Ա	
	return 0;
}

// ***************************************************************
//  Function:       OnEventListFamilies
//  Description:   	��ȡ�����Ա�б�
//  Input:         	roleid_t nRoleID		��ɫID	  
//  Input:			nFamilyID				����ID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:           04/24/2009
// 
// ***************************************************************
int CFamilyManager::OnEventListFamilies( roleid_t nRoleID, int* pMember, int &nNum, int ExceptRoleID /* = 0 */ )
{
	LK_ASSERT( pMember != NULL, return -1 );
	
	CFamily *pFamily = GetFamilyOfPlayer( nRoleID );
	if ( pFamily == NULL )
	{
		LOG_ERROR( "family"," can not find family of player( roleid:%d ) ", nRoleID );
		return -1;
	}	
		
	int tRet = OnEventListFamilies( pFamily, pMember, nNum, ExceptRoleID );
	return tRet;	   	
}

// ***************************************************************
//  Function:       OnEventListFamilies
//  Description:   	��ȡ�����Ա�б�
//  Input:          CFamily *				����
//  Input:			nFamilyID				����ID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:           04/24/2009
// 
// ***************************************************************
int CFamilyManager::OnEventListFamilies( CFamily *pFamily, int* pMember, int &nNum, int ExceptRoleID /* = 0 */ )
{
	LK_ASSERT( pFamily != NULL && pMember != NULL, return -1 )
	CFamily::members_t::iterator it = pFamily->GetMembers().begin();
	pMember[0] = pFamily->GetRooter();
	int i = 1;
	if ( ExceptRoleID == pFamily->GetRooter() )
	{
		i = 0;
	}		
	for ( ; it != pFamily->GetMembers().end() && i < nNum; ++it )
	{								
		if ( it->first == ( roleid_t )ExceptRoleID || it->first == pFamily->GetRooter() )
		{
			continue;
		}
		pMember[i] = it->first;
		++i;
	}
	nNum = i;
	return SUCCESS;  	
}

// ***************************************************************
//  Function:       OnEventListFamily
//  Description:   	�г����м���Ļ�����Ϣ
//  Input:         	roleid_t nRoleID		��ɫID	  
//  Input:			int nCountryID			����ID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:           04/24/2009
// 
// ***************************************************************
int CFamilyManager::OnEventListFamily( roleid_t nRoleID, int nCountryID, PBFamilyList &pFamilyData, int nCurPage, int &rTotalPage )
{
	// ȡ�����������Ĺ���
	TFamilies::iterator iter = m_tFamilies.begin();
	CFamily *pFamily = NULL;
	int tTotalNum = 0;
	for( ; iter != m_tFamilies.end( ); ++iter )
	{
		pFamily = ( CFamily * )CGateObjManager::GetSingleton().GetObject( iter->second );
		if ( pFamily == NULL )
		{	
			LOG_ERROR( "family","can not find family by id:%d objid:%d", iter->first, iter->second );
			continue;
		}
		
		if ( nCountryID == pFamily->GetCountryID() )
		{
			if ( tTotalNum >= nCurPage*FAMILYCORPS_MAXGETNUM && tTotalNum < ( nCurPage + 1 )*FAMILYCORPS_MAXGETNUM )
			{
				FamilyData *pbFamilyData =  pFamilyData.add_familyinfo();		
				pFamily->GetFamilyBasicInfo( *pbFamilyData );
			}
			++tTotalNum;						
		}
	}	 	
	rTotalPage = tTotalNum / FAMILYCORPS_MAXGETNUM;
	if ( tTotalNum % FAMILYCORPS_MAXGETNUM > 0 )
	{
		++rTotalPage;
	}
	return 0;
}

// ***************************************************************
//  Function:       OnEventApplyByID
//  Description:   	ͨ������ID����������
//  Input:         	nApplyingRoleID, nFamilyID
//  OutPut:         
//  Return:        int
//  Others:
//  Date:           04/29/2009
// 
// ***************************************************************
int CFamilyManager::OnEventApplyByID( roleid_t nApplyingRoleID, int nFamilyID )
{
	CFamily *pFamily = GetFamilyByID( nFamilyID );
	int tRet = OnEventSubmitApply( nApplyingRoleID, pFamily );
	return tRet;
}

// ***************************************************************
//  Function:       OnEventApplyByID
//  Description:   	ͨ������ID����������
//  Input:         	nApplyingRoleID, nFamilyID
//  OutPut:         
//  Return:        int
//  Others:
//  Date:           04/29/2009
// 
// ***************************************************************
int CFamilyManager::OnEventApplyByName( roleid_t nApplyingRoleID, const char *pFamilyName )
{
	LK_ASSERT( pFamilyName != NULL, return -1 )
	CFamily *pFamily = GetFamilyByName( pFamilyName );
	int tRet = OnEventSubmitApply( nApplyingRoleID, pFamily );
	return tRet;
}

// ***************************************************************
//  Function:       OnEventSubmitApply
//  Description:   	����ҵ�������Ϣ�ύ������ļ���
//  Input:         	nApplyingRoleID, nFamilyID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:           05/24/2009
// 
// ***************************************************************
int CFamilyManager::OnEventSubmitApply( roleid_t nApplyingRoleID, CFamily *pfamily )
{
	// ���岻����
	LK_ASSERT( pfamily != NULL, return ERROR_FAMILY_APPLY_FAMILYNOTEXIST );
	
	// ����������Ѿ������룬�����Ѿ��м�����Ϣ����ܾ�
	if ( GetFamilyOfPlayer(nApplyingRoleID) != NULL )
	{
		return ERROR_FAMILY_APPLY_INFAMILY;
	}	
	
	// ����Ƿ��Ѿ����������
	if ( pfamily->CheckApply( nApplyingRoleID ) )
	{
		return ERROR_FAMILY_APPLY_APPLIED;
	}

	//������ڣ�����������б�
	int tRet = pfamily->InsertApply( nApplyingRoleID );
	if ( tRet != SUCCESS )
	{
		return tRet;
	}	
	return 0;
}

// ***************************************************************
//  Function:       OnEventListAllApplies
//  Description:    ��ȡ��������������б�	
//  Input:         	nRoleID, nFamilyID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:           05/24/2009
// 
// ***************************************************************
int CFamilyManager::OnEventListAllApplies( roleid_t nRoleID, PBApplyList &pbApply )
{  
	CFamily *pFamily = GetFamilyOfPlayer( nRoleID );
	if ( pFamily == NULL )
	{
		LOG_ERROR( "family"," can not find family of player(roleid:%d) ", nRoleID );
		return -1;
	}	
	
	// �ж���û��Ȩ��	
	if ( nRoleID != pFamily->GetRooter() )
	{
		if ( !pFamily->MemberHasRight( nRoleID, EM_APPROVE_APPLY ) )
		{
			return ERROR_FAMILY_HASNORIGHT;
		}	
	}
	pFamily->GetApplyList( pbApply ); 
	return 0;
}


// ***************************************************************
//  Function:       OnEventListApply
//  Description:    ��ȡ��������������б�	
//  Input:         	nRoleID, nFamilyID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:           05/24/2009
// 
// ***************************************************************
bool CFamilyManager::OnEventListApply(roleid_t nRoleID, int nFamilyID)
{
	//��ȡ�����б�	

	return true;	
}

// ***************************************************************
//  Function:       OnEventAgreeApply
//  Description:    nApprovalRoleID agree nApplyingRoleID 's apply to nFamilyID
//  Input:         	nApprovalRoleID, nApplyingRoleID, nFamilyID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:           05/24/2009
// 
// ***************************************************************
int CFamilyManager::OnEventReplayApply( roleid_t nApprovalRoleID, int nApplyingRoleID, int tRet )
{
	// �������峤�Լ�����ͬ������
	CFamily* pfamily = GetFamilyOfPlayer( nApprovalRoleID );
	if ( pfamily == NULL )
	{
		LOG_ERROR( "family","can not find family of player(roleid:%d)", nApprovalRoleID );
		return -1;
	}	
	
	// ��������б������Ƿ�����ҵ�����
	if ( !pfamily->CheckApply( nApplyingRoleID ) )
	{
		return ERROR_FAMILY_REPLYAPPLY_TIMEOUT;
	}
	
	// �ж���׼�˵����
	if ( pfamily->GetRooter() != nApprovalRoleID )
	{ 	
		// �Ƿ��ǳ���	
		if ( !pfamily->MemberHasRight( nApprovalRoleID, EM_APPROVE_APPLY ) )
		{
			return ERROR_FAMILY_HASNORIGHT;
		}			
	}
	
	// ɾ��������Ϣ
	pfamily->DeletApply( nApplyingRoleID );	 
	
	// �����ͬ��
	if ( tRet != 1  )
	{ 		
		return SUCCESS;
	}

	// �ж������˴�ʱû�м����������� 	
	CFamily *pAppfamily = GetFamilyOfPlayer( nApplyingRoleID );
	if( pAppfamily != NULL )
	{
		if ( pAppfamily->GetID() == pfamily->GetID() )
		{				
			// �Ѿ��ڼ�������
			return ERROR_FAMILY_REPLYAPPLY_INFAMILY;
		}else
		{
			// ����Ѿ��м���
			return ERROR_FAMILY_REPLYAPPLY_INOHERFAMILY;			
		} 		
	}

	// ���뵽�����б���
	family_info_t pInfo;
	pInfo.mFamilyPost = FAMILY_POST_MEMEBER;	
	if ( pfamily->Ins2Member( nApplyingRoleID, pInfo ) == false )
	{
		return ERROR_FAMILY_REPLYAPPLY_FAMILYFULL;
	}	
	
	// ɾ����������е�������Ϣ
	DeleteAllApplyOfPlayer( nApplyingRoleID );
	
	return 0;  
}

// ***************************************************************
//  Function:       OnEventRemoveApply
//  Description:    �����ҵ�����
//  Input:         	nApprovalRoleID, nApplyingRoleID, nFamilyID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:          04/27/2009
// 
// ***************************************************************
bool CFamilyManager::OnEventRemoveApply( roleid_t nRoleID )
{	 
	m_tApplies.erase( nRoleID );
	return true;
}

// ***************************************************************
//  Function:       OnEventClearAllApply
//  Description:    ������е�����
//  Input:         	nApprovalRoleID, nApplyingRoleID, nFamilyID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:          04/27/2009
// 
// ***************************************************************
bool CFamilyManager::OnEventClearAllApply()
{
	m_tApplies.clear();
	return true;
}

// ***************************************************************
//  Function:       OnEventClearAllApply
//  Description:    OnEventClearApplyByTimer
//  Input:         	nApprovalRoleID, nApplyingRoleID, nFamilyID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:          04/27/2009
// 
// ***************************************************************
void CFamilyManager::OnEventClearApplyByTimer()
{
	//iterator iter = m_tFamilies.begin(); 	
	//for(; iter != m_tFamilies.end(); ++iter)
	//{
	//	iter->ClearApplyingList();
	//}
}

// ***************************************************************
//  Function:       ����ת��ְλ���������
//  Description:    ClearApply nFamilyID's applylist
//  Input:         	nFamilyID
//  OutPut:         
//  Return:         true or false
//  Others:
//  Date:           04/27/2009
// 
// ***************************************************************
int CFamilyManager::OnEventARoleAlienate( roleid_t nARoleID, roleid_t nDestRoleID )
{
	CFamily* pfamily = GetFamilyOfPlayer( nARoleID );
	if ( pfamily == NULL )
	{	
		LOG_ERROR( "family"," can not find family of player(roleid:%d) ", nARoleID );
		return -1;
	}
	
	// ����Ǿ�������Ļ�,����ת���峤ְλ
	if ( pfamily->GetCorpsID() != 0 )
	{
		CCorps *tpCorps = CCorpsManager::GetSingleton().GetCorpsByID( pfamily->GetCorpsID() );
		if ( tpCorps != NULL )
		{
			if ( tpCorps->GetRooterID() == nARoleID )
			{
				return ERROR_FAMILY_CHANGHEADER_CORPSHEADER;	
			}
		}
	}  		

	// ת���˱���������
	if( pfamily->GetRooter() != nARoleID ) 
	{
		// Send2Scene(nARoleID, EFAMILY_NOT_AROLE);
		return ERROR_FAMILY_HASNORIGHT;
	} 
	
	if ( nARoleID == nDestRoleID )
	{
		return ERROR_FAMILY_APPOINT_APPOINTSELF;
	}
	
	// �����˱����Ǵ˼����еĳ�Ա
	if ( pfamily->HasMember( nDestRoleID ) == false )
	{
		// Send2Scene(nARoleID, EFAMILY_NOT_AROLE);
		// ���Ǳ�����ĳ�Ա
		return ERROR_FAMILY_CHANGEROOTER_NOTINFAMILY;
	}
	
	CRoleGlobalInfo *pRoleInfo = CServiceRoleIDName::GetSingleton().GetRoleInfoByRoleID( nDestRoleID );
	if ( pRoleInfo == NULL )
	{
		LOG_ERROR( "family"," can not find player info(CRoleGlobalInfo) of player( roleid:%d ) ", nDestRoleID );
		return -1;
	}
	
	pfamily->SetRooter( nDestRoleID );
	pfamily->SetRooterName( pRoleInfo->RoleName() );
	
	int tOldPost = 0;
	pfamily->SetPost( nARoleID, FAMILY_POST_MEMEBER, tOldPost );
	pfamily->SetPost( nDestRoleID, FAMILY_POST_HEADER, tOldPost );
	pfamily->SetCorpsPost( nDestRoleID, CORPS_POST_FAMILYHEADER, tOldPost );
	pfamily->SetCorpsPost( nARoleID, CORPS_POST_MEMBER, tOldPost );
	
	LogOrganSetPost( ORGANLOGTYPE_FAMILY, pfamily->GetID(), nARoleID, nARoleID, FAMILY_POST_MEMEBER , CORPS_POST_FAMILYHEADER )
	LogOrganSetPost( ORGANLOGTYPE_FAMILY, pfamily->GetID(), nARoleID, nDestRoleID, CORPS_POST_FAMILYHEADER, FAMILY_POST_MEMEBER )
	return 0;
}
 
// ***************************************************************
//  Function:       OnEventFirePlayer
//  Description:    �������
//  Input:         	nABCRoleID, nDestRoleID, nFamilyID
//  OutPut:         
//  Return:         int	 0��ʾ�ɹ�������ʾ������
//  Others:
//  Date:           04/27/2009
// 
// ***************************************************************
int CFamilyManager::OnEventFirePlayer(roleid_t nABCRoleID, roleid_t nDestRoleID )
{
	CFamily* pfamily = GetFamilyOfPlayer(nABCRoleID);
	if ( pfamily == NULL )
	{
		LOG_ERROR( "family"," can not find family of player( roleid:%d ) ", nABCRoleID );
		return -1;
	}	 
	
	
	// TODO:Ȩ�޼��
	// �ж��Ƿ�������	
	if ( nABCRoleID != pfamily->GetRooter() )
	{	
		// �Ƿ���Ȩ��
		int tManagerPost = 0;
		pfamily->GetPost( nABCRoleID, CFamily::EM_FAMILYACTION, tManagerPost );
		if ( !pfamily->PostHasRight( tManagerPost, EM_FIRE_MEMBER ) )
		{
			return ERROR_FAMILY_HASNORIGHT;
		}		
		
		int tPost = 0;
		pfamily->GetPost( nDestRoleID, CFamily::EM_FAMILYACTION, tPost );
		if ( tPost <= tManagerPost )
		{							
			return ERROR_FAMILY_HASNORIGHT;
		}
	}  	
	
	if ( nABCRoleID == nDestRoleID )
	{
		return	ERROR_FAMILY_KICKPLAYER_KICKSELF;
	}
	
	if ( !pfamily->HasMember( nDestRoleID ) )
	{
		return	ERROR_FAMILY_KICK_NOTINFAMILY;
	}
	
	// TODO:����ս���в�������
	/*if( pfamily->GetNPCState( ) == STATE_CHAZING || pfamily->GetChallengeStatus( ) == STATE_BUSY )
	{
		return ERROR_FAMILY_KICKPLAYER_ONNPCFIGHT;
	}	*/
	
	
	// ������ս����
	CCorps* pCorp = CCorpsManager::GetSingleton().GetCorpsByID(pfamily->GetCorpsID());
    if (pCorp
		&& pCorp->IsInBattle(TYPE_BATTLE_ALL, ST_Union|ST_Single|ST_InBtl|ST_WaitBtl) 
		&& pCorp->IsInBattleList(nDestRoleID))
	{
		return ERROR_FAMILY_KICKPLAYER_ONNPCFIGHT;
	}


	//  ��¼��־
	LOG_INFO( "family","[%s,%d] player kicked( managerid:%d, roleid:%d ) ", __FUNCTION__,__LINE__, nABCRoleID, nDestRoleID );
	LogMemberLeave( ORGANLOGTYPE_FAMILY, pfamily->GetID(), nABCRoleID, nDestRoleID, 0 )
	
	pfamily->Del4Member(nDestRoleID); 
	
	return 0;
}

// ***************************************************************
//  Function:      OnEventDismissFamily
//  Description:   ��ɢ����
//  Input:         nARoleID, nFamilyID
//  OutPut:      
//  Return:        int	 0��ʾ�ɹ�������ʾ������ 
//  Others:
//  Date:          04/27/2009
// 
// ***************************************************************
int CFamilyManager::OnEventDismissFamily( roleid_t nARoleID, int *pMemberList, int &rMemberNum )
{
	CFamily* pfamily = GetFamilyOfPlayer( nARoleID );
	if ( pfamily == NULL )
	{
		LOG_ERROR( "family","can not find family of player(roleid:%d)", nARoleID );
		return -1;
	}	
	
	if ( pfamily->GetRooter() != nARoleID )
	{
		// �����������ܽ�ɢ
		return ERROR_FAMILY_HASNORIGHT;
	}
	if( pfamily->GetCorpsID() != 0 )
	{
		// �ھ����еļ��岻�ܽ�ɢ
		return ERROR_FAMILY_LEAVE_INCORPS;
	}
	if ( pfamily->GetFamilyStatus() == CFamily::EM_FAMILY_STATUS_DISBAND )
	{  		
		return ERROR_FAMILY_DISBAND_DISBANDSTATUS;
	}
	
	// ����ս���в��ܽ�ɢ����
	if( pfamily->GetNPCState( ) != STATE_NOBID || pfamily->GetChallengeStatus( ) == STATE_BUSY )
	{
		return ERROR_FAMILY_NOTALLOWDONNPCFIGHT;
	}
	
	pfamily->GetFamilyMemberIDList( pMemberList, rMemberNum );
	
	pfamily->SetFamilyStatus( CFamily::EM_FAMILY_STATUS_DISBAND );
	pfamily->SetFamilyDisbandTime( time( NULL ) );
	
	// �ͷ�npc
	if ( pfamily->GetNpcID() > 0 )
	{
		SetNpcOwner( pfamily->GetNpcID(), pfamily->GetID(), pfamily->GetCountryID() );
	}	
	
	// OnEventClearFamilyInfo( pfamily ); 	
	return 0; 
}

// ***************************************************************
//  Function:       OnEventLeaveFromFamily
//  Description:    �뿪����
//  Input:         	nARoleID, nFamilyID
//  OutPut:         
//  Return:        int	 0��ʾ�ɹ�������ʾ������ 
//  Others:
//  Date:          04/27/2009
// 
// ***************************************************************
int CFamilyManager::OnEventLeaveFromFamily( roleid_t nRoleID )
{
	CFamily *pFamily = GetFamilyOfPlayer( nRoleID );
	if ( pFamily == NULL )
	{
		LOG_ERROR( "family","can not find family of player(roleid:%d)", nRoleID );
		return -1;
	}
	
	if ( pFamily->GetRooter() == nRoleID )
	{
		return ERROR_FAMILY_LEAVEFAMILY_ISHEADER;
	}	
	

	// ������ս����
	CCorps* pCorp = CCorpsManager::GetSingleton().GetCorpsByID(pFamily->GetCorpsID());
	if (pCorp
		&& pCorp->IsInBattle(TYPE_BATTLE_ALL, ST_Union|ST_Single|ST_InBtl|ST_WaitBtl) 
		&& pCorp->IsInBattleList(nRoleID))
	{
		return ERROR_FAMILY_LEAVEFAMILY_ONNPCFIGHT;
	}


	if ( pFamily->Del4Member( nRoleID ) == false )
	{
		LOG_ERROR( "family"," delete family member of player(roleid %d) Error! ", nRoleID );
		return -1;
	}
	//CRoleGlobalInfo *pRoleInfo = CServiceRoleIDName::GetSingleton().GetRoleInfoByRoleID( nRoleID );
	//if ( pRoleInfo != NULL )
	//{
	//	pRoleInfo->SetFamilyID( 0 );
	//}			

	
	LOG_INFO( "family","[%s,%d] player leave family( roleid:%d, familyid:%d ) ", __FUNCTION__,__LINE__, nRoleID, pFamily->GetID() );				
	LogMemberLeave( ORGANLOGTYPE_FAMILY, pFamily->GetID(), nRoleID, nRoleID, 1 )
	return SUCCESS;
}

// ***************************************************************
//  Function:       OnEventOperateOfficer
//  Description:    ���ù�ְ
//  Input:         	nARoleID, nFamilyID
//  OutPut:         
//  Return:        int	 0��ʾ�ɹ�������ʾ������ 
//  Others:
//  Date:          04/27/2009
// 
// ***************************************************************
int CFamilyManager::OnEventOperateOfficer( roleid_t nRoleID, int nFamilyID, labelid_t nLabelID, const char* szLabelName )
{
	LK_ASSERT( nLabelID < CFamily::em_family_officer_limit, return false );

	// ȡ�ü���
	CFamily* pfamily = GetFamilyByID(nFamilyID);
	if ( pfamily == NULL )
	{
		LOG_ERROR( "family"," can not find family by ID:%d ", nFamilyID );
		return -1;
	}	

	// ȡ�ó�ԱnRoleID��Ȩ��
	/*if (MemberHasRight(nRoleID, em_create_officer) != true)
	{
		return false;
	}*/
	if ( pfamily->GetRooter() != nRoleID )
	{	 
		// TODO:û��Ȩ��
		return ERROR_FAMILY_HASNORIGHT;
	}
	

	// ��label��ֵ
	CLabel * plabel = pfamily->GetLabel(nLabelID);
	if( plabel != NULL)
	{
		//plabel->SetName(szLabelName);
	}else
	{	
		//organization_t *pOffices = pfamily->GetOfficers();
		// pOffices[(unsigned char)nLabelID].mLabel.SetID( (char)nLabelID ) ;
		// pOffices[(unsigned char)nLabelID].mLabel.SetName(szLabelName);
	}
		
	return 0;
}  
// ***************************************************************
//  Function:       OnEventOperateRights
//  Description:    Ϊְλ����Ȩ��
//  Input:         	nARoleID, nFamilyID
//  OutPut:         
//  Return:        int	 0��ʾ�ɹ�������ʾ������ 
//  Others:
//  Date:          04/27/2009
// ***************************************************************
int CFamilyManager::OnEventOperateRights(roleid_t nRoleID, int nFamilyID, labelid_t nLabelID, int rights)
{
	LK_ASSERT( nLabelID < CFamily::em_family_officer_limit, return false );

	// ȡ�ü���
	CFamily* pfamily = GetFamilyByID(nFamilyID);
	LK_ASSERT( pfamily != NULL, return -1 );

	// ȡ�ó�ԱnRoleID��Ȩ��
	/*if (MemberHasRight(nRoleID, em_create_officer) != true)
	{
		return false;
	}
*/
	if ( nRoleID != pfamily->GetRooter() )
	{
		// ���û��Ȩ��
		return ERROR_FAMILY_HASNORIGHT;
	}
	
	// ��label��ֵ
	CLabel * plabel = pfamily->GetLabel( nLabelID );
	if( plabel != NULL)
	{
		plabel->SetRight( (EmRight)rights );			
	}  
		
	// TODO:����֪ͨ
	return 0;
}

// ***********************************************************
//  Function:		GetFamilyByID
//  Description:	���ݼ���ID��ȡ������Ϣ
//  Output:			
//  Date:	04/21/2009
// **********************************************************
CFamily *CFamilyManager::GetFamilyByID( int nFamilyID )
{  
	TFamilies::iterator itor = m_tFamilies.find( nFamilyID ); 	
	
	if ( itor != m_tFamilies.end() )
	{
		CFamily *pFamily = ( CFamily * )CGateObjManager::GetSingleton().GetObject( itor->second );
		return pFamily;
	}				

	return NULL;				
}

// ***********************************************************
//  Function:		GetFamilyByName
//  Description:	���ݼ������ƻ�ȡ������Ϣ
//  Output:			
//  Date:	04/24/2009
// **********************************************************
CFamily *CFamilyManager::GetFamilyByName( const char* szFamilyName )
{  
	TFamilies::iterator itor = m_tFamilies.begin(); 	
	for ( ; itor != m_tFamilies.end(); ++itor )
	{
		CFamily *pFamily = ( CFamily * )CGateObjManager::GetSingleton().GetObject( itor->second );
		if ( pFamily == NULL )
		{
			LOG_ERROR( "family"," CFamilyManager::GetFamilyByName: can not find family by id:%d, objid:%d ", itor->first, itor->second );
			continue;
		}
		
		if ( strncmp( pFamily->GetName() , szFamilyName, MAX_FAMILYNAME_LENGTH*MAX_UTF8_BYTES -1 ) == 0 )
		{
			return pFamily;
		}				
	}	
	return NULL;				
}

// ***********************************************************
//  Function:		GetFamilyOfPlayer
//  Description:	��ȡ��Ҽ���
//  Output:			
//  Date:	04/27/2009
// **********************************************************
CFamily *CFamilyManager::GetFamilyOfPlayer( roleid_t nRoleID )
{ 
	// CRoleGlobalInfo *pGatePlayer = CServiceRoleIDName::GetSingleton().GetRoleInfoByRoleID( nRoleID );
	// LK_ASSERT( pGatePlayer != NULL, return NULL );
	TFamilies::iterator it = m_tFamilies.begin();
	for ( ; it != m_tFamilies.end(); ++it )
	{
		CFamily *pFamily = ( CFamily * )CGateObjManager::GetSingleton().GetObject( it->second );
		if ( pFamily == NULL )
		{
			continue;
		}
		if ( pFamily->HasMember( nRoleID ) )
		{
			return pFamily;
		}
	}	
	return NULL;
}

// ***********************************************************
//  Function:		Insert2ApplyList
//  Description:	����ҵ�������뵽�����б�����( �������� )
//  Output:			
//  Date:	04/27/2009
// **********************************************************
int CFamilyManager::Insert2ApplyList( int RoleID, int FamilyID )
{	
	TApplyList::iterator it = m_tApplies.find( RoleID );
	if ( it != m_tApplies.end() )
	{
		m_tApplies.erase( it );					
	}
	m_tApplies.insert( TApplyList::value_type( RoleID, FamilyID ) );
	return 0;		
}

// ***********************************************************
//  Function:		GetApplyList
//  Description:	��ȡ����������б�
//  Output:			
//  Date:	04/27/2009
// **********************************************************
int CFamilyManager::GetApplyList( int nFamilyID, PBApplyList& pbApplyList )
{
	TApplyList::iterator it = m_tApplies.begin();
	for ( ; it != m_tApplies.end(); ++it )
	{
		if ( it->second == nFamilyID )
		{	 
			ApplyInfo *pbApplyinfor = pbApplyList.add_applydata();			
			pbApplyinfor->set_playercharid( it->first );
			
			CRoleGlobalInfo *pPlayerInfo = CServiceRoleIDName::GetSingleton().GetRoleInfoByRoleID( it->first );
			if ( pPlayerInfo == NULL )
			{
				LOG_ERROR( "family"," can not find player info(CRoleGlobalInfo) ( roleid:%d ) ", it->first );
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
			CGatePlayer *pGatePlayer = CPlayerManager::GetSingleton().ScenePlayer( it->first );
			/* ��ȡ���������Ϣ */
			if ( pGatePlayer != NULL )
			{
				pbApplyinfor->set_playeronline( 1 );
				pbApplyinfor->set_mapid( pGatePlayer->mMapID );				
				pbApplyinfor->set_lineid( pGatePlayer->mLineID ); 								
			} 			
		}									
	}	
	return 0;	
}

// ***********************************************************
//  Function:		GetFamilyNameByID
//  Description:	ͨ������id��ȡ���������
//  Output:			
//  Date:	04/27/2009
// **********************************************************
const char *CFamilyManager::GetFamilyNameByID( int nRoleID )
{
	CFamily *pFamily = GetFamilyOfPlayer( nRoleID );
	return pFamily==NULL?NULL:pFamily->GetName();	
}

// ***********************************************************
//  Function:		GetApplyList
//  Description:	��ȡ����������б�
//  Output:			
//  Date:	04/27/2009
// **********************************************************
int CFamilyManager::OnEventAgreeInvite( roleid_t nInvitingRoleID, roleid_t nInvitedRoleID )
{	
	CFamily *pInvitingFamily = GetFamilyOfPlayer( nInvitingRoleID );
	
	// ������뷽��û�м���
	if ( pInvitingFamily == NULL )
	{
		LOG_ERROR( "family","can not find family of player( roleid:%d )", nInvitingRoleID );
		return -1;
	}	
	
	// ��������뷽��û�м���
	CFamily *pInvitedFamily = GetFamilyOfPlayer( nInvitedRoleID );
	if ( pInvitedFamily != NULL )
	{
		// TODO:ͬ������ʱ�Ѿ��м���
		return ERROR_FAMILY_REPLYINVITE_INFAMILY;
	}
	family_info_t  FamilyInfo;
	if ( !pInvitingFamily->Ins2Member( nInvitedRoleID, FamilyInfo ) )
	{
		return ERROR_FAMILY_REPLYINVITE_FAMILYFULL;
	}
	
	
	
	// CRoleGlobalInfo *pInvitedRoleInfo = CServiceRoleIDName::GetSingleton().GetRoleInfoByRoleID( nInvitedRoleID );
	// LK_ASSERT( pInvitedRoleInfo != NULL, return -1 );
	// pInvitedRoleInfo->SetFamilyID( pInvitingFamily->GetID() );
	
	// ɾ�������������е�������Ϣ
	DeleteAllApplyOfPlayer( nInvitedRoleID ); 
	return 0;
}

// ***********************************************************
//  Function:		OnEventPostAppoint
//  Description:	ְλ����
//  input:			roleid_t RooterID, roleid_t MemberID, int LabelID
//					������ID,		   ��������ID��		   ְλID( Ϊ0ʱ��ʾ��ͨ��Ա )
//  Output:			
//  output:			
//  Date:	04/27/2009
// **********************************************************
int CFamilyManager::OnEventPostAppoint( roleid_t RooterID, roleid_t MemberID, int LabelID )
{
	CFamily *pRooterFamily = GetFamilyOfPlayer( RooterID );
	if ( pRooterFamily == NULL )
	{
		LOG_ERROR( "family","can not find family of player( roleid:%d )", RooterID );
		return -1;
	}	
	
	// ����ͬһ���� 
	if ( !pRooterFamily->HasMember( RooterID ) )
	{
		LOG_ERROR( "family"," family( id:%d ) manager( roleid:%d ) appoint post to a player( roleid:%d ) who is not in family ", 
			pRooterFamily->GetID(), RooterID, MemberID );
		return -1;
	}
	
	// TODO: Ȩ�޼��( Ŀǰֻ���峤һ�� )  
	if ( RooterID != pRooterFamily->GetRooter() )
	{
		return ERROR_FAMILY_HASNORIGHT;			// ERRORCODE:û��Ȩ��
	}
	
	// TODO:�����˺ͱ������˵�Ȩ���Ƚ�
	if ( RooterID ==  MemberID )
	{
		return ERROR_FAMILY_POSTAPPOINT_POSTSELF;
	}
	
	// ���ñ������˵�Ȩ��
	family_info_t *pMemberInfo = pRooterFamily->GetMemberFamilyInfo( MemberID );
	if ( pMemberInfo == NULL )
	{
		LOG_ERROR( "family", "Get family info of member( roleid:%d ) Error!", MemberID );
		return -1;
	}
	
	pMemberInfo->mFamilyPost  = ( labelid_t )LabelID;
	// ���óɹ�����֪ͨ
	return 0;
}

// ***********************************************************
//  Function:		OnEventGetFamiyProperty
//  Description:	��ȡ�����������Ϣ
//  input:			
//					
//  Output:			
//  output:			
//  Date:	04/29/2009
// **********************************************************
int  CFamilyManager::OnEventGetFamiyProperty( roleid_t nRoleID, PBFamilyPropery &pFamilyData )
{  
	CFamily *pFamily = GetFamilyOfPlayer( nRoleID )	;
	if ( pFamily == NULL )
	{
		LOG_ERROR( "family"," can not find family of player( roleid:%d ) ", nRoleID );
		return -1;
	}
	
	pFamily->GetFamilyProperty( pFamilyData );	
	return 0;	
}

// ***********************************************************
//  Function:		OnEventChangeFamilyBulletin
//  Description:	�޸ļ���Ĺ���
//  input:			
//					
//  Output:			
//  output:			
//  Date:	04/29/2009
// **********************************************************
int CFamilyManager::OnEventChangeFamilyBulletin( roleid_t nRoleID, const char *pBulletion )
{ 
	CFamily *pFamily = GetFamilyOfPlayer( nRoleID );
	if ( pFamily == NULL )
	{
		LOG_ERROR( "family"," can not find family of player( roleid:%d ) ", nRoleID );
		return -1;
	}
	
	//TODO:Ȩ�޼��
	//if ( pFamily->MemberHasRight( nRoleID, em_change_bulletin ) )
	//{
	//	// û��Ȩ��
	//	return -2;
	//}
	if( nRoleID != pFamily->GetRooter() )
	{
		// �Ƿ��ǳ���
		int tPost = 0;
		pFamily->GetPost( nRoleID, CFamily::EM_FAMILYACTION, tPost );
		if ( !pFamily->PostHasRight( tPost, EM_CHANGE_BULLETIN ) )
		{
			return ERROR_FAMILY_HASNORIGHT;
		}			
	}  
	pFamily->SetBulletin( pBulletion );
	return 0;	
}

// ***********************************************************
//  Function:		ClearApplyListOfFamily
//  Description:	���ĳ������������б�
//  input:			
//					
//  Output:			
//  output:			
//  Date:	04/29/2009
// ********************************************************** 
int CFamilyManager::ClearApplyListOfFamily( int FamilyID )
{										  
	if ( m_tApplies.begin() == m_tApplies.end() )
	{
		return 0;
	}
	TApplyList::iterator it = m_tApplies.begin();
	for ( ; it != m_tApplies.end();  )
	{
		if( it->second == FamilyID )
		{
			m_tApplies.erase( it++ );
		} 
		else
		{
			++it;
		}
	}	
	return 0;			
}

// ***********************************************************
//  Function:		OnEventClearApplyList
//  Description:	���ĳ������������б�
//  input:			
//					
//  Output:			
//  output:			
//  Date:	04/29/2009
// ********************************************************** 
int CFamilyManager::OnEventClearApplyList( roleid_t nRoleID )
{
	CFamily *pFamily = GetFamilyOfPlayer( nRoleID );
	if ( pFamily == NULL )
	{	    
		LOG_ERROR( "family","can not find family of player(roleid:%d)", nRoleID );
		return -1;
	}
	
	if ( pFamily->GetRooter() != nRoleID )
	{		
		return	ERROR_FAMILY_HASNORIGHT;
	}
	pFamily->ClearApplyList();
	return SUCCESS;
}  

// ***********************************************************
//  Function:		OnEventClearFamilyInfo
//  Description:	��ɢ���壬��������������Ϣ
//  input:			
//					
//  Output:			
//  output:			
//  Date:	06/17/2009
// **********************************************************
int CFamilyManager::OnEventClearFamilyInfo( CFamily *pFamily )
{  
	LK_ASSERT( pFamily != NULL, return -1 )
		
   	// �����ݿ���ɾ����Ϣ
	DeletFamilyDBInfo( pFamily );

	// ��������ɾ������Ϣ
	m_tFamilies.erase( m_tFamilies.find( pFamily->GetID() ) );

	// ���ټ�����Ϣ	
	CGateObjManager::GetSingleton( ).DestroyObject( pFamily->get_id() );
	
	return 0;
}

// ***********************************************************
//  Function:		OnEventCancelFamilyDisband
//  Description:	ȡ����ɢ����
//  input:			
//					
//  Output:			
//  output:			
//  Date:	06/18/2009
// **********************************************************
int CFamilyManager::OnEventCancelFamilyDisband( int nRoleID )
{
	CFamily *tpFamily = GetFamilyOfPlayer( nRoleID );
	if ( tpFamily == NULL )
	{
		LOG_ERROR( "family","can not find family of player(roleid:%d)", nRoleID );
		return -1;
	}
	
	if ( tpFamily->GetRooter() != nRoleID )
	{
		return ERROR_FAMILY_HASNORIGHT;
	}
	if ( tpFamily->GetFamilyStatus() != CFamily::EM_FAMILY_STATUS_DISBAND )
	{
		return ERROR_FAMILY_CANCELDISBAND_NOTNEED;
	}
		
	tpFamily->SetFamilyStatus( CFamily::EM_FAMILY_STATUS_ALIVE );
	return SUCCESS;
}

// ***********************************************************
//  Function:		CreatFamilyDBInfo
//  Description:	�Ѵ����ļ���������ݿ�
//  Output:			
//  Date:	05/09/2009
// **********************************************************
int CFamilyManager::CreatFamilyDBInfo( CFamily *pFamily )
{
	LK_ASSERT( pFamily != NULL, return -1  ) 	

	char MemberInfoBuff[MAX_FAMILYMEMBERINFO_BUFFULENT] ={ 0 };
	char EscapeBuff[MAX_FAMILYMEMBERINFO_BUFFULENT] = { 0 };
	PBFamilyMemberInfoList pbMemberInfo;
	pFamily->GetMemberInfoList( &pbMemberInfo );
	int tRet = pbMemberInfo.SerializeToArray( MemberInfoBuff, MAX_FAMILYMEMBERINFO_BUFFULENT );
	LK_ASSERT( tRet == true, return  -1 )
	int ByteSize = pbMemberInfo.ByteSize();

	char  *pAddress =   EscapeBuff;
	int CapRet = EscapeDataString( &pAddress, MAX_FAMILYMEMBERINFO_BUFFULENT, MemberInfoBuff, ByteSize );
	LK_ASSERT( CapRet != -1, return -1 )			
	
	char tFamilyName[MAX_FAMILYNAME_LENGTH*MAX_UTF8_BYTES]	= { 0 };
	char *tpFamilyNamePtr = tFamilyName;
	int tFamilyNameCapRet = EscapeDataString( &tpFamilyNamePtr, MAX_FAMILYNAME_LENGTH*MAX_UTF8_BYTES, ( char * )pFamily->GetName(), strlen( pFamily->GetName() ) );
	LK_ASSERT( tFamilyNameCapRet != -1, return -1 )			
	

	#ifdef _GLOBAL_NAME_
	const char* stmtfmt = "insert into UMS_FAMILY( family_id, family_name, create_role_id, create_role_name, "
						"member_info, country_id, corps_id, family_status, disband_time, family_level," 
						"family_creattime, family_stability ) values( %d, '%s', %d, '%s','%s', %d, %d, %d, %d, %d, %d, %d )";	

	CGateLogic::GetSingleton().ExecuteSql( em_dbsession_creatfamily, pFamily->get_id(), 0, 2, 
		SQL_NEED_CALLBACK|SQL_LATEST_INC_ID, INSERT, stmtfmt, pFamily->GetID(), tFamilyName, pFamily->GetRooter(),
		pFamily->GetRooterName(), pAddress, pFamily->GetCountryID(), pFamily->GetCorpsID(), pFamily->GetFamilyStatus(),
		pFamily->GetFamilyDisbandTime(), pFamily->GetLevel(), time(NULL), pFamily->GetStabilityDegree() );

	#else
	const char* stmtfmt = "insert into UMS_FAMILY( family_name, create_role_id, create_role_name, member_info, country_id, corps_id, family_status, disband_time, family_level, family_creattime, family_stability ) values( '%s', %d, '%s','%s', %d, %d, %d, %d, %d, %d, %d )";

	CGateLogic::GetSingleton().ExecuteSql( em_dbsession_creatfamily, pFamily->get_id(), 0, 2, SQL_NEED_CALLBACK|SQL_LATEST_INC_ID, INSERT, stmtfmt, tFamilyName, pFamily->GetRooter(),
		pFamily->GetRooterName(), pAddress, pFamily->GetCountryID(), pFamily->GetCorpsID(), pFamily->GetFamilyStatus(),
		pFamily->GetFamilyDisbandTime(), pFamily->GetLevel(), time(NULL), pFamily->GetStabilityDegree() );
	#endif
		
	return 0;
}

// ***********************************************************
//  Function:		UpDateFamilyDBInfo
//  Description:	���¼�����Ϣ�����ݿ���
//  Output:			
//  Date:	05/09/2009
// **********************************************************
int CFamilyManager::UpDateFamilyDBInfo( CFamily *pFamily )
{
	LK_ASSERT( pFamily != NULL, return -1 )

	// ����Ҫ���¼�����Ϣ
	if( pFamily->GetSaveStatus( ) == CFamily::FAMILY_INFONOCHANGE && pFamily->GetFamilyShop()->GetSaveStatus() == false )
	{
		return 0;
	} 		
		
	if ( pFamily->GetSaveStatus() != CFamily::FAMILY_INFONOCHANGE )
	{
		char MemberInfoBuff[MAX_FAMILYMEMBERINFO_BUFFULENT] ={ 0 };
		char EscapeBuff[MAX_FAMILYMEMBERINFO_BUFFULENT] = { 0 }; 		

		// ����������Ϣ	
		if ( pFamily->GetSaveStatus() == CFamily::FAMILY_PROPERYCHANGED 
				|| pFamily->GetSaveStatus() == CFamily::FAMILY_ALLINFOCHANGED )
		{
			char tFamilyNoticeEscapeBuff[MAX_FAMILYNOTICE_LENGTH*MAX_UTF8_BYTES]	= { 0 };
			char *tpNoticeEscapePtr =	tFamilyNoticeEscapeBuff;
			int tNoticeEscapeRet = EscapeDataString( &tpNoticeEscapePtr,MAX_FAMILYNOTICE_LENGTH*MAX_UTF8_BYTES, ( char * )pFamily->GetBulletin(), strlen( pFamily->GetBulletin() ) );
			LK_ASSERT( tNoticeEscapeRet != -1 , return -1 )					

			const char *stmtfmt = "update UMS_FAMILY set family_notice = '%s', family_money=%d, create_role_id=%d, create_role_name='%s' , corps_id=%d, family_status=%d, disband_time=%d, npc_id=%d, bid_money=%d, bid_time=%d, \
							war_rank=%d, war_winnum=%d, war_lostnum=%d, family_starlevel=%d,  \
							war_exp=%d, family_glory=%d, war_status=%d, family_npcwelfaretime=%d, family_level=%d, family_repetionopendate = %d, family_repetionopentimes = %d, family_repetionscore = %d, family_stability=%d, family_weeknum=%d where family_id=%d";
			CGateLogic::GetSingleton().ExecuteSql( 1,0, 0, 2, SQL_NONE, UPDATE, stmtfmt, tFamilyNoticeEscapeBuff, pFamily->GetMoney(), pFamily->GetRooter(), pFamily->GetRooterName(), pFamily->GetCorpsID(), 
				pFamily->GetFamilyStatus(), pFamily->GetFamilyDisbandTime(), pFamily->GetNpcID(), pFamily->GetBidMoney(), pFamily->GetBidTime(), pFamily->GetWarRank(), pFamily->GetPVPWinNum(),
				pFamily->GetPVPFailedNum(), pFamily->GetPVPStarLevel(), pFamily->GetPVPScore(), pFamily->GetGlory(), pFamily->GetBattleState(), pFamily->GetNpcWelfareGetTime(), pFamily->GetLevel(), 
				pFamily->GetRepetionDate(), pFamily->GetRepetionOpenTimes(), pFamily->GetRepetionScore(), pFamily->GetStabilityDegree(), pFamily->GetWeekNum(), pFamily->GetID() );
		}

		// ���³�Ա��Ϣ
		if ( pFamily->GetSaveStatus() == CFamily::FAMILY_MEMBERCHANGED 
				|| pFamily->GetSaveStatus() == CFamily::FAMILY_ALLINFOCHANGED ) 
		{  	

			PBFamilyMemberInfoList pbMemberInfo;
			pFamily->GetMemberInfoList( &pbMemberInfo );
			int tRet = pbMemberInfo.SerializeToArray( MemberInfoBuff, MAX_FAMILYMEMBERINFO_BUFFULENT );
			LK_ASSERT( tRet == true, return  -1 )
			int ByteSize = pbMemberInfo.ByteSize();	
			char  *pAddress =   EscapeBuff;
			int CapRet = EscapeDataString( &pAddress, MAX_FAMILYMEMBERINFO_BUFFULENT, MemberInfoBuff, ByteSize );
			LK_ASSERT( CapRet != -1, return -1 )
			const char *stmtfmt = "update UMS_FAMILY set member_info='%s' where family_id=%d";
			CGateLogic::GetSingleton().ExecuteSql( 1, 0, 0, 2, SQL_NONE, UPDATE, stmtfmt, EscapeBuff, pFamily->GetID() );
		}  

		// ��մ洢״̬
		pFamily->ClearSaveStatus();
	}
		
		
	// �жϼ����̵��Ƿ���Ҫ�洢
	if ( pFamily->GetFamilyShop()->GetSaveStatus() )
	{	
		char tFamilyShopEscapeBuff[MAXSHOPBYTELEN]	= { 0 };
		PBLeagueShopsListInfo tLeagueShop;
		pFamily->GetFamilyShop()->GetShopListInfo( tLeagueShop );				
		int tRet = tLeagueShop.SerializeToArray( tFamilyShopEscapeBuff, MAXSHOPBYTELEN );
		LK_ASSERT( tRet == true, return -1 )				
		int tByteSize = tLeagueShop.ByteSize();	
			
		char tShopEscapeBuff[MAXESCAPEBUFFLENGTH] = { 0 };		
		char *tpshopEscapePtr =	tShopEscapeBuff;
		int tShopEscapeRet = EscapeDataString( &tpshopEscapePtr, MAXESCAPEBUFFLENGTH, tFamilyShopEscapeBuff, tByteSize );
		LK_ASSERT( tShopEscapeRet != -1 , return -1 )
		const char *tpStmtfmt = "update UMS_FAMILY set family_shopinfo='%s' where family_id=%d";
		CGateLogic::GetSingleton().ExecuteSql( 1, 0, 0, 2, SQL_NONE, UPDATE, tpStmtfmt, tShopEscapeBuff, pFamily->GetID() );
		pFamily->GetFamilyShop()->SetSaveStatus( false );	
	}		
	return 0;
}


// ***********************************************************
//  Function:		DeletFamilyDBInfo
//  Description:	ɾ����������ݿ���Ϣ
//  Output:			
//  Date:	05/09/2009
// **********************************************************
int CFamilyManager::DeletFamilyDBInfo( CFamily *pFamliy )
{ 
	LK_ASSERT( pFamliy != NULL, return -1 ) 
	LOG_INFO( "family","[%s,%d]family disband ( familyid:%d )", __FUNCTION__,__LINE__, pFamliy->GetID() );
	LogOrganDisband( ORGANLOGTYPE_FAMILY, pFamliy->GetID(), pFamliy->GetRooter(), 1, 0 )
	const char* stmtfmt = "delete from UMS_FAMILY where family_id=%d";
	CGateLogic::GetSingleton().ExecuteSql( 1, 0, 0, 2, SQL_NONE, DELETE, stmtfmt, pFamliy->GetID( ) );
	return 0;		
}

// ******************************************* ****************
//  Function:		UpDateAllFamilyDBInfo
//  Description:	�������м�������ݿ���Ϣ
//  Output:			
//  Date:	05/13/2009
// **********************************************************
void CFamilyManager::UpDateAllFamilyDBInfo()
{
	// ����δ���سɹ�ǰ��������ĸò���
	if ( CServiceFamily::GetSingleton().IsLaunched() == false )
	{			
		return;
	}	
	
	if ( m_tFamilies.begin() == m_tFamilies.end() )
	{
		return ;
	}	
	for ( TFamilies::iterator it = m_tFamilies.begin(); it != m_tFamilies.end(); ++it )
	{
		CFamily *pFamily = ( CFamily * )CGateObjManager::GetSingleton().GetObject( it->second );
		if ( pFamily == NULL )
		{
			LOG_ERROR( "family"," can not find family ( id:%d )( objid:%d ) ", it->first, it->second );
			continue;
		}
		
		UpDateFamilyDBInfo( pFamily );
		pFamily->ClearSaveStatus();
	}
	return ;
}

// ***********************************************************
//  Function:		UpDateAllFamilyDBInfo
//  Description:	�������м�������ݿ���Ϣ
//  Output:			
//  Date:	05/13/2009
// **********************************************************
int CFamilyManager::InsertFamily( CFamily *pFamily )
{
	LK_ASSERT( pFamily != NULL, return -1 )
	if ( m_tFamilies.size() >= em_family_num )
	{
		return -1;
	}
	m_tFamilies.insert( TFamilies::value_type(  pFamily->GetID() , pFamily->get_id() ) );
	return 0;
}

// ***********************************************************
//  Function:		UpDateAllFamilyDBInfo
//  Description:	�������м�������ݿ���Ϣ
//  Output:			
//  Date:	05/13/2009
// **********************************************************
int CFamilyManager::GetFamilyApplyNum( int vFamilyID )
{	
	CFamily *pFamily = GetFamilyByID( vFamilyID );
	if ( pFamily == NULL )
	{
		LOG_ERROR( "family", " can not find family by ID:%d ", vFamilyID );
		return 0;
	}
	LK_ASSERT( pFamily != NULL, return 0 )
	return pFamily->GetAppplyNum();
}

// ***********************************************************
//  Function:		DeleteFamilyOnTimeDisband
//  Description:	��ɢ���й��ڵļ���
//  Output:			
//  Date:	06/17/2009
// **********************************************************
void CFamilyManager::DeleteFamilyOnTimeDisband()
{
	if ( m_tFamilies.empty() )
	{
		return ;
	}	
	for ( TFamilies::iterator it = m_tFamilies.begin(); it != m_tFamilies.end();  )
	{
		CFamily *pFamily = ( CFamily * )CGateObjManager::GetSingleton().GetObject( it->second );
		if ( pFamily == NULL )
		{
			++it;
			continue;
		}
		if ( !pFamily->CheckDisbandTime() )
		{	
			++it;			
			continue;		
		} 	
		int tRoleIDList[MAX_FAMILYMEMBER_NUM] = { 0 };
		int tNum = MAX_FAMILYMEMBER_NUM;							   
		pFamily->GetFamilyMemberIDList( tRoleIDList, tNum );
		CServiceFamily::GetSingleton().SendNotifyDisbandFamily( pFamily->GetID(), tRoleIDList, tNum );
	
		// �����ݿ���ɾ����Ϣ
		DeletFamilyDBInfo( pFamily );

		// ��������ɾ������Ϣ
		m_tFamilies.erase( it++ );

		// ���ټ�����Ϣ	
		CGateObjManager::GetSingleton( ).DestroyObject( pFamily->get_id() );  	 		
	}	
}

// ***********************************************************
//  Function:		RefreshFamilyStatus
//  Description:	ˢ�����м����״̬
//  Output:			
//  Date:	06/17/2009
// **********************************************************
void CFamilyManager::RefreshFamilyStatus( )
{
	// �����尲����
	CheckFamilyStability();
	
	// ˢ�¼���״̬	
	TFamilies::iterator it = m_tFamilies.begin();
	for ( ; it != m_tFamilies.end(); ++it )
	{
		CFamily *tpFamily = ( CFamily * )CGateObjManager::GetSingleton().GetObject( it->second );
		if ( tpFamily == NULL )
		{				
			LOG_ERROR( "family"," can not find family ( ID:%d )( OBJID:%d ) ", it->first, it->second );
			continue;
		}
				
		tpFamily->RefreshStatus();
	}	
}		

// ***********************************************************
//  Function:		DeleteAllApplyOfPlayer
//  Description:	ɾ����ҵ�����������Ϣ
//  Output:			
//  Date:	06/17/2009
// **********************************************************
void CFamilyManager::DeleteAllApplyOfPlayer( int nRoleID )			 
{
	TFamilies::iterator it = m_tFamilies.begin();
	for ( ; it != m_tFamilies.end(); ++it )
	{
		CFamily *tpFamily = ( CFamily * )CGateObjManager::GetSingleton().GetObject( it->second );
		if ( tpFamily == NULL )
		{
			LOG_ERROR( "family","can not find family (id:%d)(objid:%d)", it->first, it->second );
			continue;
		}
		
		tpFamily->DeletApply( nRoleID );
	}
}

// ***********************************************************
//  Function:		OnEventSetFamilyPost
//  Description:	����ְλ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyManager::OnEventSetFamilyPost( int nManagerID, int nMemberID, int nPost, int &rOldPost )
{ 
	CFamily *tpFamily = GetFamilyOfPlayer( nManagerID );
	if ( tpFamily == NULL )
	{
		LOG_ERROR( "family"," can not find family of player( roleid:%d ) ", nManagerID );
		return -1;
	}	
	
	if ( !tpFamily->HasMember( nMemberID ) )
	{
		LOG_ERROR( "family", " family(id:%d) has no member ( roleid:%d ) ", tpFamily->GetID(), nMemberID );
		return -1;
	}
	
	if ( nMemberID == nManagerID )
	{
		return -1;
	}
	
	int tManagerPost = 0;
	int	tMemberPost	 = 0;
	
	tpFamily->GetPost( nManagerID, CFamily::EM_FAMILYACTION, tManagerPost );
	tpFamily->GetPost( nMemberID, CFamily::EM_FAMILYACTION, tMemberPost );
	
	if ( !tpFamily->PostHasRight( tManagerPost, EM_GRANT_SETOFFICER ) )
	{
		return ERROR_FAMILY_HASNORIGHT;
	}
	
	if ( tManagerPost >= tMemberPost || tManagerPost >= nPost )
	{
		return  ERROR_FAMILY_HASNORIGHT;
	}

	if ( tpFamily->GetNumOfCertainPost( nPost, CFamily::EM_FAMILYACTION ) >= tpFamily->GetPostLimitNum( nPost ) )
	{
		return ERROR_FAMILY_SETPOST_POSTFULL;
	}	
	
	tpFamily->SetFamilyPost( nMemberID, nPost, rOldPost );
	LogOrganSetPost( ORGANLOGTYPE_FAMILY, tpFamily->GetID(), nManagerID, nMemberID, nPost, rOldPost );
	return SUCCESS;	
}

// ***********************************************************
//  Function:		OnEventContributeMoney
//  Description:	���׽�Ǯ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyManager::OnEventContributeMoney( int nMemberID, int nMoney )
{
	CFamily *pFamily = GetFamilyOfPlayer( nMemberID );
	LK_ASSERT( pFamily != NULL, return -1 )	
	
	if ( nMoney <= 0 )
	{
		return ERROR_FAMILY_CONTRIBUTE_MONEYINVAL;
	}
	
	if ( ( nMoney + pFamily->GetMoney() ) < 0 )
	{
		return ERROR_FAMILY_CONTRIBUTE_MONEYLIMIT;
	}
	
	if ( ( unsigned int )( nMoney + pFamily->GetMoney() ) > ( unsigned int )MAX_FAMILYCORPS_MONEY )
	{
		return ERROR_FAMILY_CONTRIBUTE_MONEYLIMIT;
	}			
	
	pFamily->ContributeMoney( nMemberID, nMoney );
	int tContribute = nMoney*m_tFamilyConfig.GetContributePerGold();
	pFamily->AddMemberContribute( nMemberID, tContribute );
	return SUCCESS;
}

// ***********************************************************
//  Function:		OnEventConsumeMoney
//  Description:	���Ľ�Ǯ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyManager::OnEventConsumeMoney( int nManagerID, int nMoney, bool bFreeze )
{
	CFamily *pFamily = GetFamilyOfPlayer( nManagerID );
	if ( pFamily == NULL )
	{
		LOG_ERROR( "family","can not find family of player( roleid:%d )", nManagerID );
		return -1;
	}	
	
	// Ȩ���ж�
	if ( pFamily->GetRooter() != nManagerID )
	{
		if ( !pFamily->HasPost( nManagerID, FAMILY_POST_PRESBYTER, CFamily::EM_FAMILYACTION ) )
		{
			return ERROR_FAMILY_HASNORIGHT;
		}	
	}
	
	int tRet = pFamily->ConsumeFamilyMoney( nMoney, bFreeze );
	if ( tRet == CFamily::EM_MONEYNOTENOUGH )
	{
		return ERROR_FAMILY_CONSUMEMONEY_MONEYNOTENOUGH;
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		OnEventLevelUPFamily
//  Description:	��������
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyManager::OnEventLevelUPFamily( int nManagerID, int &rLevel, int &rMoney, int &rStability )
{
	CFamily *pFamily = GetFamilyOfPlayer( nManagerID );
	if ( pFamily == NULL )
	{
		LOG_ERROR( "family"," can not find family of player( roleid:%d ) ", nManagerID );
		return -1;
	}	
	
	// Ȩ�޼��
	if ( pFamily->GetRooter() != nManagerID )
	{
		/*if ( pFamily->HasPost( nManagerID, FAMILY_POST_PRESBYTER, CFamily::EM_FAMILYACTION ) )
		{*/
			return ERROR_FAMILY_HASNORIGHT;
		//}
	}
	
	return pFamily->LevelUPFamily( rLevel, rMoney, rStability );
}

// ***********************************************************
//  Function:		OnEventAddFamilyGlory
//  Description:	���Ӽ�����ҫ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyManager::OnEventAddFamilyGlory( int nFamilyID, int nGloryValue )
{
	CFamily *pFamily = GetFamilyByID( nFamilyID );
	if ( pFamily == NULL )
	{
		LOG_ERROR( "family"," can not get family by ID:%d ", nFamilyID );
		return -1;
	}
	
	pFamily->AddGlory( nGloryValue );
	return SUCCESS;
}

// ***********************************************************
//  Function:		OnEventReduceFamilyGlory
//  Description:	���ټ�����ҫ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyManager::OnEventReduceFamilyGlory( int nFamilyID, int nGloryValue, bool &rLevelDown )
{
	CFamily *pFamily = GetFamilyByID( nFamilyID );
	if ( pFamily == NULL )
	{
		LOG_ERROR( "family"," can not find family by id:%d ", nFamilyID );
		return -1;
	}
	
	rLevelDown = pFamily->ReduceGlory( nGloryValue );
	return SUCCESS;
}

// ***********************************************************
//  Function:		OnEventAddFamilyPVPScore
//  Description:	���Ӽ���pvp���ֵĽ�
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyManager::OnEventAddFamilyPVPScore( int nFamilyID, int nScoreValue, bool &rLevelUP )
{
	CFamily *pFamily = GetFamilyByID( nFamilyID );
	if ( pFamily == NULL )
	{
		LOG_ERROR( "family","can not find family by id:%d", nFamilyID );
		return -1;
	}
	
	rLevelUP = pFamily->AddPVPScore( nScoreValue, pFamily->GetPVPStarLevel() );
	return SUCCESS;
}


// ***********************************************************
//  Function:		InsertFamilyConfig
//  Description:	����һ������������Ϣ
//  Output:			
//  Date:	08/21/2009
// **********************************************************
int CFamilyConfig::InsertFamilyConfig( CFamilyConfigInfo& rFamilyConfig )
{
	mConfigList.insert( FamilyConfig::value_type( rFamilyConfig.mLevel, rFamilyConfig ) );
	return SUCCESS;	
}

// ***********************************************************
//  Function:		SetFamilyPropertyConfig
//  Description:	���ü���Ļ�����������
//  Output:			
//  Date:	08/21/2009
// **********************************************************
int CFamilyConfig::SetFamilyPropertyConfig( CFamilyPropertyConfigInfo &rFamilyPropertyConfig )
{  
	memcpy( &mPropertyConfig, &rFamilyPropertyConfig, sizeof( mPropertyConfig ) );
	return SUCCESS;
}

// ***********************************************************
//  Function:		SetFamilyPropertyConfig
//  Description:	����ĳ��npc������Ϣ
//  Output:			
//  Date:	01/05/2010
// **********************************************************
int CFamilyConfig::InsertNpcWelfare( int nNpcID, CNpcWelfare &rNpcWelfare )
{
	mNpcWelfare.insert( NpcWelfareList::value_type( nNpcID, rNpcWelfare ) );
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetNpcWelfare
//  Description:	��ȡĳ��npc�ĸ�����Ϣ
//  Output:			
//  Date:	01/05/2010
// **********************************************************
int CFamilyConfig::GetNpcWelfare( int nNpcID, CNpcWelfare &rNpcWelfare )
{ 
	rNpcWelfare.mNpcGlory = 0;
	rNpcWelfare.mNpcMoney = 0;
	NpcWelfareList::iterator it = mNpcWelfare.find( nNpcID );
	if( it != mNpcWelfare.end() )
	{
		rNpcWelfare.mNpcMoney = ( it->second ).mNpcMoney;
		rNpcWelfare.mNpcGlory =	( it->second ).mNpcGlory;
		return SUCCESS;
	}
	return -1;
}

// ***********************************************************
//  Function:		GetFamilyConfigByLevel
//  Description:	��ȡĳһ�ȼ��ļ���������Ϣ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyConfig::GetFamilyConfigByLevel( int nLevel, CFamilyConfigInfo& rFamilyConfig )
{		
	FamilyConfig::iterator it = mConfigList.find( nLevel );
	if ( it == mConfigList.end() )
	{
		return -1;
	}
	
	rFamilyConfig.mGloryLimit			= (it->second).mGloryLimit;
	rFamilyConfig.mMemberNumLimit		= (it->second).mMemberNumLimit;	
	rFamilyConfig.mGloryLevelUPNeeded	= (it->second).mGloryLevelUPNeeded;
	rFamilyConfig.mLevel				= (it->second).mLevel;
	rFamilyConfig.mPresbyterNumLimit	= (it->second).mPresbyterNumLimit;
	rFamilyConfig.mPVPScoreLimit		= (it->second).mPVPScoreLimit;	
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetMemberNumLimitByLevel
//  Description:	��ȡ����ĳһ�ȼ��µ���������
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyConfig::GetMemberNumLimitByLevel( int nLevel, int &rMemberNum )
{ 
	FamilyConfig::iterator it = mConfigList.find( nLevel );
	if ( it == mConfigList.end() )
	{
		return -1;
	}
	rMemberNum = (it->second).mMemberNumLimit;
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetMemberNumLimitByLevel
//  Description:	��ȡ����ĳһ�ȼ��µ���ҫ����
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyConfig::GetGloryLimitByLevel( int nLevel, int &rGlory )
{ 
	FamilyConfig::iterator it = mConfigList.find( nLevel );
	if ( it == mConfigList.end() )
	{
		return -1;
	}
	rGlory = (it->second).mGloryLimit;	
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetPresbyterNumLimit
//  Description:	��ȡ���ϵ���������
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyConfig::GetPresbyterNumLimit( int nLevel, int &rNumber )
{ 
	FamilyConfig::iterator it = mConfigList.find( nLevel );
	if ( it == mConfigList.end() )
	{
		return -1;
	}
	rNumber = (it->second).mPresbyterNumLimit;	
	return SUCCESS;	
}

// ***********************************************************
//  Function:		GetPVPScoreLimit
//  Description:	��ȡĳһpvp�Ǽ�����������һpvp�Ǽ���pvp����
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyConfig::GetPVPScoreLimit( int nLevel, int &rPvPScoreLimit )
{
	FamilyConfig::iterator it = mConfigList.find( nLevel );
	if ( it == mConfigList.end() )
	{
		return -1;
	}
	rPvPScoreLimit = (it->second).mPVPScoreLimit;	
	return SUCCESS;	
}

// ***********************************************************
//  Function:		GetGloryLevelUPNeeded
//  Description:	��ȡĳһ�ȼ�����������һ�ȼ���Ҫ����ҫֵ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyConfig::GetGloryLevelUPNeeded( int nLevel, int &rGlory )
{ 
	FamilyConfig::iterator it = mConfigList.find( nLevel );
	if ( it == mConfigList.end() )
	{
		return -1;
	}
	rGlory = (it->second).mGloryLevelUPNeeded;	
	return SUCCESS;		
}

// ***********************************************************
//  Function:		GetMoneyLevelUPNeeded
//  Description:	��ȡĳһ�ȼ�����������һ�ȼ���Ҫ�Ľ�Ǯ
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyConfig::GetMoneyLevelUPNeeded( int nLevel, int &rMoney )
{
	FamilyConfig::iterator it = mConfigList.find( nLevel );
	if ( it == mConfigList.end() )
	{
		return -1;
	}
	rMoney = (it->second).mMoneyLevelUPNeeded;	
	return SUCCESS;		
}

// ***********************************************************
//  Function:		GetInitialStability
//  Description:	��ȡĳһ�ȼ��ĳ�ʼ������
//  Output:			
//  Date:	12/01/2009
// **********************************************************
int CFamilyConfig::GetInitialStability( int nLevel, int &rStability )
{
	FamilyConfig::iterator it = mConfigList.find( nLevel );
	if ( it == mConfigList.end() )
	{
		return -1;
	}
	rStability = (it->second).mInitialStability;	
	return SUCCESS;		
}

// ***********************************************************
//  Function:		GetReduceStability
//  Description:	��ȡĳһ���ȼ�ÿ��Ӧ�ü��ٵļ��尲����
//  Output:			
//  Date:	12/01/2009
// **********************************************************
int CFamilyConfig::GetReduceStability( int nLevel, int &rStability )
{
	FamilyConfig::iterator it = mConfigList.find( nLevel );
	if ( it == mConfigList.end() )
	{
		return -1;
	}
	rStability = (it->second).mReduceStability;	
	return SUCCESS;		
}


// ***********************************************************
//  Function:		GetContributePerGold
//  Description:	��ȡһ�����ӵĹ��׶�
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyConfig::GetContributePerGold(  )
{	
	return mPropertyConfig.mContributePerGold;	
}

// ***********************************************************
//  Function:		GetScorePerFight
//  Description:	ÿʤ��һ����ȡ�Ļ���
//  Output:			
//  Date:	08/25/2009
// **********************************************************
int CFamilyConfig::GetScorePerFight(  )
{
	return mPropertyConfig.mScorePerFight;
}

// ***********************************************************
//  Function:		InsertRepetionTimeInfo
//  Description:	����ʱ����Ϣ
//  Output:			
//  Date:	04/28/2010
// **********************************************************
int CFamilyConfig::InsertRepetionTimeInfo( CRepetionTimeInfo &rRepetionTimeInfo )
{
	mRepetionTimeInfoList.push_back( rRepetionTimeInfo );
	return SUCCESS;
}

// ***********************************************************
//  Function:		CheckRepetionOpenTime
//  Description:	����Ƿ���Խ�����帱��
//  Output:			
//  Date:	04/28/2010
// **********************************************************
int CFamilyConfig::CheckRepetionOpenTime( )
{
	int tTimeNow = time( NULL );
	tm *tpLocalTime = localtime( (time_t *)&tTimeNow );
	int tErrcode = ERROR_FAMILY_FAMILYBOSS_NOTINOPENTIME;
	
	RepetionTimeInfoList::iterator it = mRepetionTimeInfoList.begin();
	for ( ; it != mRepetionTimeInfoList.end(); ++it )
	{
		if ( (*it).mWeekDay == tpLocalTime->tm_wday )
		{  					
			tErrcode = SUCCESS;	
			break;
		}		  		
	}
	return tErrcode;
}

// ***********************************************************
//  Function:		GetCurrentReptionTimeInfo
//  Description:	��ȡ����ĸ���ʱ����Ϣ
//  Output:			
//  Date:	04/28/2010
// **********************************************************	
CRepetionTimeInfo *CFamilyConfig::GetCurrentReptionTimeInfo()
{
	int tTimeNow = time( NULL );
	tm *tpLocalTime = localtime( (time_t *)&tTimeNow );
	RepetionTimeInfoList::iterator it = mRepetionTimeInfoList.begin();
	for ( ; it != mRepetionTimeInfoList.end(); ++it )
	{
		if ( (*it).mWeekDay%7 == tpLocalTime->tm_wday )
		{  					
			return it;
			break;
		}				  		
	}
	return NULL;
}

int CFamilyManager::InsertNPC( int vNpcID, int vCountryID )
{
	NPCList::iterator it = mNpcList.find( vNpcID * 10 + vCountryID );
	if ( it != mNpcList.end() )
	{
		return 1;
	}
	NPCInfo tInfo = NPCInfo();
	tInfo.mOwnFamily = 0;	
	tInfo.mDefID = 0;
	tInfo.mAttID = 0;
	tInfo.mMaxMoney = 0;
	tInfo.mOwnFamily = 0;
	mNpcList.insert( NPCList::value_type( vNpcID * 10 + vCountryID, tInfo ) );
	NPCList::iterator Npcit = mNpcList.find( vNpcID * 10 + vCountryID );
	if ( Npcit == mNpcList.end() )
	{
		return 1;
	}
	NPCInfo *tpInfo = (NPCInfo*)&(Npcit->second);
	tpInfo->mBidList.initailize();
	return 0;
}

int CFamilyManager::GetNpcOwner( int vNpcID, int vCountryID )
{
	NPCList::iterator it = mNpcList.find( vNpcID * 10 + vCountryID );
	if ( it == mNpcList.end() )
	{
		return -1;
	}
	NPCInfo *tInfo = (NPCInfo*)&(it->second);
	return tInfo->mOwnFamily;
}

int CFamilyManager::SetNpcOwner( int vNpcID, int vOwnerFamily, int vCountryID, bool vInit )
{
	NPCList::iterator it = mNpcList.find( vNpcID * 10 + vCountryID );
	if ( it == mNpcList.end() )
	{
		return -1;
	}
	NPCInfo *tpInfo = (NPCInfo*)&(it->second);
	tpInfo->mOwnFamily = vOwnerFamily;
	if ( vOwnerFamily != 0 && vInit == false )
	{
		tpInfo->mBidList.clear();
		tpInfo->mMaxMoney = 0;
	}	
	return 0;
}

int CFamilyManager::AddBid( int vNpcID, int vBidFamily, int vBidMoney, int vBidTime, int vCountryID, bool vInit )
{
	NPCList::iterator Npcit = mNpcList.find( vNpcID * 10 + vCountryID );
	if ( Npcit == mNpcList.end() )
	{
		return ERROR_FAMILY_BIDNPC_BIDFAIL;
	}
	NPCInfo *tInfo = (NPCInfo*)&(Npcit->second);
	CFamily *tpFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( vBidFamily );
	if ( tpFamily == NULL )
	{
		LOG_ERROR( "family"," can not find family by ID:%d ", vBidFamily );
		return -3;
	}
	
	
	if ( tpFamily->GetNpcID( ) != 0 )
	{
		// ����Ѿ�ռ�첻�ܱ���
		if ( tpFamily->GetBidMoney( ) == 0 )
			return ERROR_FAMILY_BIDNPC_HASOWN;
		// �����ظ�������ͬ��NPC
		else if ( tpFamily->GetNpcID( ) != vNpcID )
			return ERROR_FAMILY_BIDNPC_SAME;
	}
	
	// ���������߱��ۣ����ܱ�
	if ( vBidMoney <= tInfo->mMaxMoney && vInit == false )
	{
		return ERROR_FAMILY_BIDNPC_NOTHIGHEST;
	}	

	BidList::iterator Bidit = tInfo->mBidList.find( vBidFamily );
	if ( Bidit != tInfo->mBidList.end() )
	{
		BidInfo *tBid = (BidInfo*)&(Bidit->second);
		if ( tBid->mBidMoney < vBidMoney )
		{
			int tMoney = tBid->mBidMoney;
			tBid->mBidMoney = vBidMoney;
			tBid->mBidTime = vBidTime;
			tInfo->mMaxMoney = vBidMoney;
			return vBidMoney - tMoney;
		}
		return ERROR_FAMILY_BIDNPC_BIDFAIL;
	}
	BidInfo tBid;
	tBid.mBidMoney = vBidMoney;
	tBid.mBidTime = vBidTime;
	tInfo->mBidList.insert( BidList::value_type( vBidFamily, tBid ) );
	tInfo->mMaxMoney = vBidMoney;
	return vBidMoney;
}

int CFamilyManager::DelBid( int vNpcID, int vBidFamily, int vCountryID )
{
	NPCList::iterator Npcit = mNpcList.find( vNpcID * 10 + vCountryID );
	if ( Npcit == mNpcList.end() )
	{
		return -1;
	}
	NPCInfo *tInfo = (NPCInfo*)&(Npcit->second);
	int tMoney = 0;
	BidList::iterator Bidit = tInfo->mBidList.find( vBidFamily );
	if ( Bidit == tInfo->mBidList.end() )
	{
		return -2;
	}
	BidInfo *tBid = (BidInfo*)&(Bidit->second);
	tMoney = tBid->mBidMoney;
	tInfo->mBidList.erase( Bidit );
	// �������߱��ۣ����¼���
	if ( tMoney == tInfo->mMaxMoney )
	{
		int tMaxMoney = 0;
		tInfo->mMaxMoney = 0;
		Bidit = tInfo->mBidList.begin();
		for ( ; Bidit != tInfo->mBidList.end(); ++Bidit )
		{
			BidInfo *tBid = (BidInfo*)&(Bidit->second);
			if ( tBid->mBidMoney > tMaxMoney )
			{
				tInfo->mMaxMoney = tBid->mBidMoney;
			}
		}
	}	
	return 0;
}

int CFamilyManager::ClearBid( int vNpcID, int vCountryID )
{
	NPCList::iterator Npcit = mNpcList.find( vNpcID * 10 + vCountryID );
	if ( Npcit == mNpcList.end() )
	{
		return -1;
	}
	NPCInfo *tInfo = (NPCInfo*)&(Npcit->second);
	BidList::iterator Bidit = tInfo->mBidList.begin();
	for ( ; Bidit != tInfo->mBidList.end(); ++Bidit )
	{
		// ֪ͨ�����޸ľ���
		CFamily *tpFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( Bidit->first );
		if ( tpFamily == NULL )
		{
			LOG_ERROR( "family"," can not find family by ID:%d ", Bidit->first );
			continue;
		}
		tpFamily->SetNpcID( 0 );
		tpFamily->SetBidMoney( 0 );
		tpFamily->SetBidTime( 0 );
	}	
	tInfo->mBidList.clear();
	tInfo->mMaxMoney = 0;
	tInfo->mDefID = 0;
	tInfo->mAttID = 0;
	return 0;
}

int CFamilyManager::GetWinner( int vNpcID, int &vAttFamily, int &vDefFamily, int vCountryID )
{
	NPCList::iterator Npcit = mNpcList.find( vNpcID * 10 + vCountryID );
	if ( Npcit == mNpcList.end() )
	{
		return -1;
	}
	NPCInfo *tInfo = (NPCInfo*)&(Npcit->second);
	if ( tInfo->mDefID != 0 || tInfo->mAttID != 0 )
	{
		vAttFamily = tInfo->mAttID;
		vDefFamily = tInfo->mDefID;
		return SUCCESS;
	}
	BidList::iterator Bidit = tInfo->mBidList.begin();
	int tFirstFamily = 0, tFirstMoney = 0, tFirstTime = time(NULL);
	int tSecondFamily = 0, tSecondMoney = 0, tSecondTime = tFirstTime;
	for ( ; Bidit != tInfo->mBidList.end(); ++Bidit )
	{
		BidInfo *tBid = (BidInfo*)&(Bidit->second);
		if ( tBid->mBidMoney > tFirstMoney )
		{
			tSecondFamily = tFirstFamily;
			tSecondMoney = tFirstMoney;
			tSecondTime = tFirstTime;
			tFirstFamily = Bidit->first;
			tFirstMoney = tBid->mBidMoney;
			tFirstTime = tBid->mBidTime;			
		}
		else if ( tBid->mBidMoney == tFirstMoney )
		{
			if ( tBid->mBidTime < tFirstTime )
			{
				tSecondFamily = tFirstFamily;
				tSecondMoney = tFirstMoney;
				tSecondTime = tFirstTime;
				tFirstFamily = Bidit->first;
				tFirstMoney = tBid->mBidMoney;
				tFirstTime = tBid->mBidTime;
			}
		}
		else if ( tBid->mBidMoney > tSecondMoney )
		{
			tSecondFamily = Bidit->first;
			tSecondMoney = tBid->mBidMoney;
			tSecondTime = tBid->mBidTime;
		}
		else if ( tBid->mBidMoney == tSecondMoney )
		{
			if ( tBid->mBidTime < tSecondTime )
			{
				tSecondFamily = Bidit->first;
				tSecondMoney = tBid->mBidMoney;
				tSecondTime = tBid->mBidTime;
			}
		}
	}
	// ���û��ռ��ļ��壬����ǰ���������򷵻س������
	if ( tInfo->mOwnFamily == 0 )
	{
		vAttFamily = tSecondFamily;
		vDefFamily = tFirstFamily;
	}
	else
	{
		vAttFamily = tFirstFamily;
		vDefFamily = tInfo->mOwnFamily;
	}
	if ( vDefFamily == tInfo->mOwnFamily && vAttFamily == 0 )
	{
		vAttFamily = -1;
	}

	tInfo->mAttID = vAttFamily;
	tInfo->mDefID = vDefFamily;
	return SUCCESS;	
}

int CFamilyManager::GetAllFamily( int vNpcID, int *FamilyList, int *MoneyList, int &Num, int vCountryID )
{
	NPCList::iterator Npcit = mNpcList.find( vNpcID * 10 + vCountryID );
	if ( Npcit == mNpcList.end() )
	{
		return -1;
	}
	NPCInfo *tInfo = (NPCInfo*)&(Npcit->second);	
	BidList::iterator Bidit = tInfo->mBidList.begin();
	int tNum = 0;
	for ( ; Bidit != tInfo->mBidList.end(); ++Bidit )
	{
		BidInfo *tBid = (BidInfo*)&(Bidit->second);
		FamilyList[ tNum ] = Bidit->first;
		MoneyList[ tNum ] = tBid->mBidMoney;
		tNum++;
	}
	Num = tNum;
	return SUCCESS;
}

void CFamilyManager::GetBid( int vNpcID, int vCountryID, CMessageBidInfoResponse &vResponse )
{
	NPCList::iterator Npcit = mNpcList.find( vNpcID * 10 + vCountryID );
	if ( Npcit == mNpcList.end() )
	{
		return;
	}
	NPCInfo *tInfo = (NPCInfo*)&(Npcit->second);
	CFamily *tpFamily = CFamilyManager::GetSingleton().GetFamilyByID( tInfo->mOwnFamily );
	if ( tpFamily != NULL )
	{
		vResponse.set_familyname( tpFamily->GetName( ) );
	}	
	BidList::iterator Bidit = tInfo->mBidList.begin();
	for ( ; Bidit != tInfo->mBidList.end(); ++Bidit )
	{
		CFamily *tpFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( Bidit->first );
		if ( tpFamily == NULL )
		{
			LOG_ERROR( "family"," can not find family by ID:%d ", Bidit->first );
			continue;
		}
		
		BidInfo *tBid = (BidInfo*)&(Bidit->second);
		BidResult* tpInfo = vResponse.add_biddata();
		tpInfo->set_familyid( tpFamily->GetID() );
		tpInfo->set_familyname( tpFamily->GetName() );
		tpInfo->set_money( tBid->mBidMoney );
		tpInfo->set_country( tpFamily->GetCountryID() );
		tpInfo->set_win( tpFamily->GetPVPWinNum() );
		tpInfo->set_lost( tpFamily->GetPVPFailedNum() );
		tpInfo->set_level( tpFamily->GetPVPStarLevel() );
	}
}

void CFamilyManager::AddSubmit( int vFamilyID, int vCharID )
{
	SubmitList::iterator Familyit = mNPCSubmitList.find( vFamilyID );
	if ( Familyit == mNPCSubmitList.end() )
	{
		MemberList tList;
		mNPCSubmitList.insert( SubmitList::value_type( vFamilyID, tList ) );
		Familyit = mNPCSubmitList.find( vFamilyID );
		Familyit->second.initailize();
	}
	Familyit->second.push_back( vCharID );
}

int CFamilyManager::GetSubmit( int vCharID )
{
	SubmitList::iterator Familyit = mNPCSubmitList.begin();
	for ( ; Familyit != mNPCSubmitList.end(); ++Familyit )
	{
		CFamily *tpFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( Familyit->first );
		if ( tpFamily == NULL )
		{
			continue;
		}
		if ( tpFamily->HasMember( vCharID ) == false )
		{
			continue;
		}
		MemberList::iterator MemberIt = Familyit->second.begin();
		for ( ; MemberIt != Familyit->second.end(); ++MemberIt )
		{
			if ( *MemberIt == vCharID )
			{
				return 1;
			}
		}
	}
	return 0;
}

void CFamilyManager::ClearSubmit( int vFamilyID )
{
	SubmitList::iterator Familyit = mNPCSubmitList.find( vFamilyID );
	if ( Familyit == mNPCSubmitList.end() )
	{
		return;
	}
	Familyit->second.clear();
}

void CFamilyManager::NotifyBattle( int vAttFamilyID, int vDefFamilyID, int vType, int vNpcID )
{	
	// �����NPC����
	if ( vType == TYPE_BATTLE_NPC )
	{
		KEY_TYPE tKey = CRepetionModule::GetSingletonPtr()->CreateBattleByIndex( _REPE_FAMILY_INDEX_, 1, vDefFamilyID, vNpcID );
		if( tKey == INVITED_KEY_VALUE )
		{
			LOG_ERROR( "family", "fuck zhang 3" );
			return;
		}
		mBattleList.push_back( BattleInfo( tKey, vAttFamilyID, vDefFamilyID, vType ) );
		SubmitList::iterator DefFamilyit = mNPCSubmitList.find( vDefFamilyID );
		if ( DefFamilyit != mNPCSubmitList.end() )
		{
			CFamily *tpDefFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( vDefFamilyID );
			if ( tpDefFamily == NULL )
			{
				return;
			}
			MemberList::iterator Memberit2 = DefFamilyit->second.begin();
			for( ; Memberit2 != DefFamilyit->second.end(); ++Memberit2 )
			{
				if ( tpDefFamily->HasMember( *Memberit2 ) )
				{
					CRepetionModule::GetSingletonPtr()->PlayerJoin( *Memberit2, _REPE_FAMILY_INDEX_, tKey, 2 );
				}			
			}
		}		
		
		SubmitList::iterator AttFamilyit = mNPCSubmitList.find( vAttFamilyID );	
		if ( AttFamilyit != mNPCSubmitList.end() )
		{
			CFamily *tpAttFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( vAttFamilyID );
			if ( tpAttFamily == NULL )
			{
				return;
			}
			MemberList::iterator Memberit1 = AttFamilyit->second.begin();
			for( ; Memberit1 != AttFamilyit->second.end(); ++Memberit1 )
			{
				if ( tpAttFamily->HasMember( *Memberit1 ) )
				{
					CRepetionModule::GetSingletonPtr()->PlayerJoin( *Memberit1, _REPE_FAMILY_INDEX_, tKey, 1 );
				}			
			}
		}		
	}	
	// ����Ǽ�����ս
	else if ( vType == TYPE_BATTLE_PLAYER )
	{
		KEY_TYPE tKey = CRepetionModule::GetSingletonPtr()->CreateBattleByIndex( _REPE_FAMILY_CHALLENGE_INDEX_, 1, 
			vDefFamilyID );
		if( tKey == INVITED_KEY_VALUE )
		{
			LOG_ERROR( "default", "fuck zhang 3" );
			return;
		}
		mBattleList.push_back( BattleInfo( tKey, vAttFamilyID, vDefFamilyID, vType ) );
		CFamily *tpAttFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( vAttFamilyID );
		CFamily *tpDefFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( vDefFamilyID );
		if ( tpDefFamily != NULL )
		{
			for ( CFamily::members_t::iterator it = tpDefFamily->GetMembers().begin(); it != tpDefFamily->GetMembers().end(); ++it )
			{
				CRepetionModule::GetSingletonPtr()->PlayerJoin( it->first, _REPE_FAMILY_CHALLENGE_INDEX_, tKey, 2 );
			}
		}
		if ( tpAttFamily != NULL )
		{
			for ( CFamily::members_t::iterator it = tpAttFamily->GetMembers().begin(); it != tpAttFamily->GetMembers().end(); ++it )
			{
				CRepetionModule::GetSingletonPtr()->PlayerJoin( it->first, _REPE_FAMILY_CHALLENGE_INDEX_, tKey, 1 );
			}
		}		
	}	
}

void CFamilyManager::EndBattle( KEY_TYPE vKey, int vWinSide )
{
	BattleList::iterator it = mBattleList.begin();
	for ( ; it != mBattleList.end(); ++it )
	{
		if ( it->mKey == vKey )
		{
			CFamily *tpAttFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( it->mAttFamilyID );
			CFamily *tpDefFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( it->mDefFamilyID );
			if ( tpDefFamily != NULL )
			{
				tpDefFamily->SetPVPName( "" );
				tpDefFamily->SetChallengeStatus( STATE_IDLE );
			}
			if ( tpAttFamily != NULL )
			{
				tpAttFamily->SetPVPName( "" );
				tpAttFamily->SetChallengeStatus( STATE_IDLE );
			}
			if ( vWinSide == WIN_ATTSIDE )
			{					
				if ( tpDefFamily == NULL )
				{
					LOG_ERROR( "family", " can not find family by ID:%d ", it->mDefFamilyID );
					return;
				}
				if ( tpAttFamily == NULL )
				{
					LOG_ERROR( "family", " can not find family by ID:%d ", it->mAttFamilyID );
					return;
				}
								
				tpAttFamily->AddPVPWinNum( 1 );
				tpDefFamily->AddPVPFailedNum( 1 );
				tpAttFamily->AddPVPScore( m_tFamilyConfig.GetScorePerFight(), tpDefFamily->GetPVPStarLevel() );
				tpAttFamily->AddGlory( m_tFamilyConfig.GetGloryPerFight() );
				tpDefFamily->ReducePVPScore( m_tFamilyConfig.GetScorePerFight(), tpAttFamily->GetPVPStarLevel() );								
				
				if ( it->mType == TYPE_BATTLE_NPC )
				{
					LogOrganBattleVictory( ORGANLOGTYPE_FAMILY, it->mAttFamilyID, 0, it->mDefFamilyID, tpDefFamily->GetNpcID(), 0 );					
				}
				else
				{
					LogOrganChallengeVictory( ORGANLOGTYPE_FAMILY, it->mAttFamilyID, 0, it->mDefFamilyID, 0, 0 );					
				}		
			}
			// �ط���ʤ
			else if ( vWinSide == WIN_DEFSIDE )
			{
				LK_ASSERT( tpDefFamily != NULL, return );
				tpDefFamily->AddPVPWinNum( 1 );
				if ( tpAttFamily != NULL )
				{
					tpAttFamily->AddPVPFailedNum( 1 );	
				}					
				
				int tAttackPvPLevel = tpDefFamily->GetPVPStarLevel();
				if ( tpAttFamily != NULL )
				{
					tAttackPvPLevel = tpAttFamily->GetPVPStarLevel();
				}
											
				
				tpDefFamily->AddPVPScore( m_tFamilyConfig.GetScorePerFight(), tAttackPvPLevel );
				tpDefFamily->AddGlory( m_tFamilyConfig.GetGloryPerFight() );
				
				if ( tpAttFamily != NULL )
				{						
					tpAttFamily->ReducePVPScore( m_tFamilyConfig.GetScorePerFight(), tpDefFamily->GetPVPStarLevel() );
				}	
				if ( it->mType == TYPE_BATTLE_NPC )
				{
					LogOrganBattleVictory( ORGANLOGTYPE_FAMILY, it->mDefFamilyID, 0, it->mAttFamilyID, tpDefFamily->GetNpcID(), 0 );					
				}
				else
				{
					LogOrganChallengeVictory( ORGANLOGTYPE_FAMILY, it->mDefFamilyID, 0, it->mAttFamilyID, 0, 0 );					
				}
				
			}
			
			// �����NPC����
			if ( it->mType == TYPE_BATTLE_NPC )
			{				
				tpDefFamily->SetBattleState( STATE_BIDDING );
				if ( tpAttFamily != NULL )
				{
					tpAttFamily->SetBattleState( STATE_BIDDING );
				}
				// ֪ͨ����ս�����
				CServiceFamily::GetSingletonPtr()->SendBattleResultNotify( tpDefFamily->GetCountryID(), tpDefFamily->GetNpcID(), it->mAttFamilyID, it->mDefFamilyID, vWinSide );
				// ֪ͨ�����������¿�ʼ
				CServiceFamily::GetSingletonPtr()->SendBidRestartNotify( tpDefFamily->GetCountryID(), tpDefFamily->GetNpcID() );
				// ������Ǯ
				int tFamilyList[ CFamilyManager::em_family_num ] = { 0 };
				int tMoneyList[ CFamilyManager::em_family_num ] = { 0 };
				int tNum = 0;
				GetAllFamily( tpDefFamily->GetNpcID(), tFamilyList, tMoneyList, tNum, tpDefFamily->GetCountryID() );
				for ( int i = 0; i < tNum; i++ )
				{
					// ����˫������Ǯ
					if ( tFamilyList[ i ] == it->mDefFamilyID || tFamilyList[ i ] == it->mAttFamilyID )
					{
						continue;
					}
					CFamily *tpFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( tFamilyList[ i ] );
					if ( tpFamily == NULL )
					{
						continue;
					}
					CServiceFamily::GetSingletonPtr()->AddFamilyMoney( tpFamily->GetRooter(), tpFamily->GetBidMoney(), tpFamily->GetRooterName(), false, REASON_WAR );
				}
				int tNpcID = tpDefFamily->GetNpcID();
				ClearBid( tpDefFamily->GetNpcID(), tpDefFamily->GetCountryID() );
				// ������ʤ
				if ( vWinSide == WIN_ATTSIDE )
				{
					LK_ASSERT( tpDefFamily != NULL && tpAttFamily != NULL, return );
					SetNpcOwner( tNpcID, tpAttFamily->GetID(), tpAttFamily->GetCountryID() );					
					tpAttFamily->SetNpcID( tNpcID );
					tpAttFamily->SetNpcWelfareGetTime( time(NULL) - WELFARE_REFESH_TIMELENGTH );
					tpDefFamily->SetNpcID( 0 );
					SendSingleNpc( tpDefFamily->GetCountryID(), tNpcID, tpAttFamily->GetID() );
					tpDefFamily->SetNpcWelfareGetTime( -1 );
				}
				else if ( vWinSide == WIN_DEFSIDE )
				{
					LK_ASSERT( tpDefFamily != NULL, return );
					SetNpcOwner( tNpcID, tpDefFamily->GetID(), tpDefFamily->GetCountryID() );
					tpDefFamily->SetNpcID( tNpcID );
					SendSingleNpc( tpDefFamily->GetCountryID(), tNpcID, tpDefFamily->GetID() );
					tpDefFamily->SetNpcWelfareGetTime( time(NULL) - WELFARE_REFESH_TIMELENGTH );
				}
				CServiceFamily::GetSingletonPtr()->SendNotifyFamilyProperty( it->mAttFamilyID );
				CServiceFamily::GetSingletonPtr()->SendNotifyFamilyProperty( it->mDefFamilyID );				
				break;
			}
			// ����Ǽ�����ս
			else if ( it->mType  == TYPE_BATTLE_PLAYER )
			{				
				CServiceFamily::GetSingletonPtr()->SendBattleResultNotify( tpDefFamily->GetCountryID(), 0, it->mAttFamilyID, it->mDefFamilyID, vWinSide );
				LockRoom( it->mDefFamilyID, false );
				if ( vWinSide == WIN_ATTSIDE )
				{
					// ��ʱɾ�����ط�����
					int tMoney = 0;
					DelRoom( it->mDefFamilyID, tMoney );
					if ( tpAttFamily != NULL )
					{
						tpAttFamily->RemoveFreezeMoney( );
						//int tMoney = tpAttFamily->GetFreezeMoney( );
						//CServiceFamily::GetSingletonPtr()->AddFamilyMoney( tpAttFamily->GetRooter(), tpAttFamily->GetFreezeMoney(), tpAttFamily->GetRooterName(), true, REASON_CHALLENGEWAR );
						//CServiceFamily::GetSingletonPtr()->AddFamilyMoney( tpAttFamily->GetRooter(), tMoney * 0.8, tpAttFamily->GetRooterName(), false, REASON_CHALLENGEWAR );
						tpAttFamily->SetChallengeMoney( 0 );
					}
					if ( tpDefFamily != NULL )
					{
						//int tMoney = tpDefFamily->GetFreezeMoney( );
						tpDefFamily->RemoveFreezeMoney( );
						//tpDefFamily->SetMoney( tpDefFamily->GetMoney() - tMoney );
						tpDefFamily->SetChallengeMoney( 0 );
						//tpDefFamily->ConsumeFamilyMoney( tMoney, false );
					}					
				}
				else if ( vWinSide == WIN_DEFSIDE )
				{					
					if ( tpDefFamily != NULL )
					{
						tpDefFamily->RemoveFreezeMoney( );
						//int tMoney = tpDefFamily->GetFreezeMoney( );
						//CServiceFamily::GetSingletonPtr()->AddFamilyMoney( tpDefFamily->GetRooter(), tpDefFamily->GetFreezeMoney(), true );	
						//CServiceFamily::GetSingletonPtr()->AddFamilyMoney( tpDefFamily->GetRooter(), tMoney * 0.8, tpDefFamily->GetRooterName(), false, REASON_CHALLENGEWARWIND );
					}
					if ( tpAttFamily != NULL )
					{
						//int tMoney = tpAttFamily->GetFreezeMoney( );
						tpAttFamily->RemoveFreezeMoney( );
						//tpAttFamily->SetMoney( tpAttFamily->GetMoney() - tMoney );
						//tpAttFamily->ConsumeFamilyMoney( tMoney, false );	
						tpAttFamily->SetChallengeMoney( 0 );
					}					
				}
				break;
			}
		}
	}	
	mBattleList.erase( it );
}

bool CFamilyManager::InList( int vFamilyID, int vCharID )
{
	SubmitList::iterator Familyit = mNPCSubmitList.find( vFamilyID );
	if ( Familyit == mNPCSubmitList.end() )
	{
		return false;
	}
	MemberList::iterator Memberit = Familyit->second.begin();
	for( ; Memberit != Familyit->second.end(); ++Memberit )
	{
		// ����ڱ����б���
		if ( *Memberit == vCharID )
		{
			return true;
		}
	}
	return false;
}

void CFamilyManager::NotifyEnter( int vFamilyID, int vCharID )
{
	CFamily *tpFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( vFamilyID );
	if ( tpFamily == NULL )
	{						
		LOG_ERROR( "family"," can not find family by ID:%d ", vFamilyID );
		return;
	}
	
	BattleList::iterator it = mBattleList.begin();
	for ( ; it != mBattleList.end(); ++it )
	{
		if ( it->mType == TYPE_BATTLE_PLAYER || InList( vFamilyID, vCharID ) == true )
		{
			if ( it->mAttFamilyID == vFamilyID )
			{
				CRepetionModule::GetSingletonPtr()->PlayerJoin( vCharID, FAMILY_MAP_ID, it->mKey, 1 );
			}
			else if ( it->mDefFamilyID == vFamilyID )
			{
				CRepetionModule::GetSingletonPtr()->PlayerJoin( vCharID, FAMILY_MAP_ID, it->mKey, 2 );
			}
		}							
	}
}

int CFamilyManager::AddRoom( int vFamilyID, int vMoney, char * vName )
{
	RoomList::iterator it = mRoomList.find( vFamilyID );
	if ( it == mRoomList.end() )
	{
		RoomInfo tInfo;
		mRoomList.insert( RoomList::value_type( vFamilyID, tInfo ) );
		it = mRoomList.find( vFamilyID );
		it->second.mMoney = vMoney;
		CDirtyWord::GetSingleton().OI_Dirty_Check( 1, ( char * )vName );
		strncpy( it->second.mName, vName, NAME_LENGTH - 1 );
		it->second.mName[ NAME_LENGTH - 1 ] = '\0';
		it->second.mChList.initailize();
		it->second.mState = STATE_IDLE;
		it->second.mLock = false;
		return SUCCESS;
	}
	else
	{
		return ERROR_FAMILY_MAKEROOM_EXIST;
	}
}

int CFamilyManager::AddCha( int vRoomFamilyID, int vChaFamilyID )
{
	if ( vRoomFamilyID == vChaFamilyID )
	{
		return ERROR_FAMILY_CHAROOM_SAME;
	}
	
	RoomList::iterator RoomIt = mRoomList.find( vRoomFamilyID );
	if ( RoomIt == mRoomList.end() )
	{
		return ERROR_FAMILY_CHAROOM_NOTEXIST;
	}
	if ( RoomIt->second.mLock == true )
	{
		return ERROR_FAMILY_CHAROOM_BATTLE;
	}
	ChaList::iterator ChaIt = RoomIt->second.mChList.begin();
	for ( ; ChaIt != RoomIt->second.mChList.end(); ++ChaIt )
	{
		if ( *ChaIt == vChaFamilyID )
		{
			return ERROR_FAMILY_CHAROOM_EXIST;
		}
	}
	RoomIt->second.mChList.push_back( vChaFamilyID );
	return SUCCESS;
}

int	CFamilyManager::DelRoom( int vFamilyID, int &vMoney )
{
	RoomList::iterator it = mRoomList.find( vFamilyID );
	if ( it == mRoomList.end() )
	{
		return ERROR_FAMILY_ABORT_NOTEXIST;
	}
	// �����������ɾ��
	if ( it->second.mLock == true )
	{
		return ERROR_FAMILY_ABORTROOM_BATTLE;
	}
	vMoney = it->second.mMoney;
	mRoomList.erase( it );
	return SUCCESS;
}

int CFamilyManager::DelCha( int vFamilyID )
{
	RoomList::iterator RoomIt = mRoomList.begin();
	for( ; RoomIt != mRoomList.end(); ++RoomIt )
	{
		ChaList::iterator ChaIt = RoomIt->second.mChList.begin();
		for ( ; ChaIt != RoomIt->second.mChList.end(); ++ChaIt )
		{
			if ( *ChaIt == vFamilyID )
			{
				RoomIt->second.mChList.erase( ChaIt );
				if ( RoomIt->second.mChList.empty() == true )
				{
					RoomIt->second.mState = STATE_IDLE;
				}
				break;
			}
		}
	}
	return SUCCESS;
}

int CFamilyManager::ClearCha( int vFamilyID )
{
	RoomList::iterator it = mRoomList.find( vFamilyID );
	if ( it == mRoomList.end() )
	{
		return -1;
	}
	it->second.mChList.clear();
	return 0;
}

int CFamilyManager::SetRoom( int vFamilyID, int vState )
{
	RoomList::iterator it = mRoomList.find( vFamilyID );
	if ( it == mRoomList.end() )
	{
		return -1;
	}
	it->second.mState = vState;
	return 0;
}

int CFamilyManager::LockRoom( int vFamilyID, bool vLock )
{
	RoomList::iterator it = mRoomList.find( vFamilyID );
	if ( it == mRoomList.end() )
	{
		return -1;
	}
	it->second.mLock = vLock;
	return 0;
}

int CFamilyManager::HasCha( int vRoomFamilyID, int vChaFamilyID, int &vMoney )
{
	RoomList::iterator RoomIt = mRoomList.find( vRoomFamilyID );
	if ( RoomIt == mRoomList.end() )
	{
		return ERROR_FAMILY_AGREE_UNKNOWN;
	}
	if ( RoomIt->second.mLock == true )
	{
		return ERROR_FAMILY_AGREE_UNKNOWN;
	}
	ChaList::iterator ChaIt = RoomIt->second.mChList.begin();
	for ( ; ChaIt != RoomIt->second.mChList.end(); ++ChaIt )
	{
		if ( *ChaIt == vChaFamilyID )
		{
			vMoney = RoomIt->second.mMoney;
			return SUCCESS;
		}
	}
	return ERROR_FAMILY_AGREE_UNKNOWN;
}

int CFamilyManager::QueryAllRoom( CMessageQueryAllRoomResponse &vResponse )
{
	RoomList::iterator RoomIt = mRoomList.begin();
	for( ; RoomIt != mRoomList.end(); ++RoomIt )
	{
		CFamily *tpFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( RoomIt->first );
		if ( tpFamily == NULL )
		{
			continue;
		}

		ChaList::iterator ChaIt = RoomIt->second.mChList.begin();
		AllRoomInfo* tpInfo = vResponse.add_roomdata();
		tpInfo->set_familyid( tpFamily->GetID() );
		tpInfo->set_familyname( tpFamily->GetName() );
		tpInfo->set_money( RoomIt->second.mMoney );
		tpInfo->set_roomname( RoomIt->second.mName );
		tpInfo->set_win( tpFamily->GetPVPWinNum( ) );
		tpInfo->set_lost( tpFamily->GetPVPFailedNum( ) );
		tpInfo->set_state( RoomIt->second.mState );
		if ( ChaIt != RoomIt->second.mChList.end() )
		{
			CFamily *tpAttFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( *ChaIt );
			if ( tpAttFamily == NULL )
			{
				continue;
			}
			tpInfo->set_attname( tpAttFamily->GetName() );
		}		
	}
	return SUCCESS;
}

int CFamilyManager::QueryMyRoom( int vFamilyID, int &vMoney, CMessageQueryMyRoomResponse &vResponse )
{
	RoomList::iterator RoomIt = mRoomList.find( vFamilyID );
	if ( RoomIt == mRoomList.end() )
	{
		return ERROR_FAMILY_QUERY_NOTEXIST;
	}
	vMoney = RoomIt->second.mMoney;
	vResponse.set_name( RoomIt->second.mName );
	ChaList::iterator ChaIt = RoomIt->second.mChList.begin();
	for ( ; ChaIt != RoomIt->second.mChList.end(); ++ChaIt )
	{
		CFamily *tpFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( *ChaIt );
		if ( tpFamily == NULL )
		{
			continue;
		}
		MyRoomInfo* tpInfo = vResponse.add_roomdata();
		tpInfo->set_familyid( tpFamily->GetID() );
		tpInfo->set_familyname( tpFamily->GetName() );
		tpInfo->set_win( tpFamily->GetPVPWinNum( ) );
		tpInfo->set_lost( tpFamily->GetPVPFailedNum( ) );
	}
	return SUCCESS;
}

int CFamilyManager::QueryMyCha( int vFamilyID, CMessageQueryMyChaResponse &vResponse )
{
	RoomList::iterator RoomIt = mRoomList.begin();
	for( ; RoomIt != mRoomList.end(); ++RoomIt )
	{
		CFamily *tpFamily = CFamilyManager::GetSingletonPtr()->GetFamilyByID( RoomIt->first );
		if ( tpFamily == NULL )
		{
			continue;
		}

		ChaList::iterator ChaIt = RoomIt->second.mChList.begin();
		for ( ; ChaIt != RoomIt->second.mChList.end(); ++ChaIt )
		{
			if( *ChaIt != vFamilyID )
				continue;
			MyChaInfo* tpInfo = vResponse.add_roomdata();
			tpInfo->set_familyid( tpFamily->GetID() );
			tpInfo->set_familyname( tpFamily->GetName() );
			tpInfo->set_win( tpFamily->GetPVPWinNum( ) );
			tpInfo->set_lost( tpFamily->GetPVPFailedNum( ) );
			tpInfo->set_roomname( RoomIt->second.mName );
			tpInfo->set_money( RoomIt->second.mMoney );
		}		
	}
	return SUCCESS;
}

void CFamilyManager::SendFamilyIDName( int vServerID )
{
	CMessage MsgHead;	
	CMessageFamilyIDNameNotify Notify;

	TFamilies::iterator it = m_tFamilies.begin();
	int tCount = 0;
	for ( ; it != m_tFamilies.end(); ++it )
	{
		CFamily *pFamily = ( CFamily * )CGateObjManager::GetSingleton().GetObject( it->second );
		if ( pFamily == NULL )
		{
			continue;
		}
		Notify.add_familyid( pFamily->GetID() );
		Notify.add_familyname( pFamily->GetName() );
		tCount++;
		if ( tCount > 100 )
		{
			MsgHead.set_msgpara( (int)&Notify );
			MsgHead.mutable_msghead()->set_messageid( ID_G2S_NOTIFY_FAMILYIDNAME );
			CGateServer::GetSingleton().Send2Scene( vServerID, &MsgHead );
			Notify.Clear( );
			tCount = 0;
		}
	}	
	if ( tCount != 0 )
	{
		MsgHead.set_msgpara( (int)&Notify );
		MsgHead.mutable_msghead()->set_messageid( ID_G2S_NOTIFY_FAMILYIDNAME );
		CGateServer::GetSingleton().Send2Scene( vServerID, &MsgHead );
	}	
}

void CFamilyManager::SendNpcList( int vServerID )
{
	CMessage MsgHead;	
	CMessageNpcListNotify Notify;

	TFamilies::iterator it = m_tFamilies.begin();
	for ( ; it != m_tFamilies.end(); ++it )
	{
		CFamily *pFamily = ( CFamily * )CGateObjManager::GetSingleton().GetObject( it->second );
		if ( pFamily == NULL )
		{
			continue;
		}
		if ( pFamily->GetCountryID() != vServerID )
		{
			continue;
		}
		if ( pFamily->GetNpcID() != 0 && pFamily->GetBidMoney() == 0 && pFamily->GetBidTime() == 0 )
		{
			Notify.add_npcid( pFamily->GetNpcID() );
			Notify.add_familyid( pFamily->GetID() );
		}		
	}	
	Notify.set_type( TYPE_FAMILY );
	MsgHead.set_msgpara( (int)&Notify );
	MsgHead.mutable_msghead()->set_messageid( ID_G2S_NOTIFY_NPCLIST );
	CGateServer::GetSingleton().Send2Scene( vServerID, &MsgHead );
}

void CFamilyManager::SendSingleIDName( int vServerID, int vFamilyID, char *vFamilyName )
{
	CMessage MsgHead;	
	CMessageFamilyIDNameNotify Notify;

	Notify.add_familyid( vFamilyID );
	Notify.add_familyname( vFamilyName );

	MsgHead.set_msgpara( (int)&Notify );
	MsgHead.mutable_msghead()->set_messageid( ID_G2S_NOTIFY_FAMILYIDNAME );
	CGateServer::GetSingleton().Send2Scene( vServerID, &MsgHead );
}

void CFamilyManager::SendSingleNpc( int vServerID, int vNpcID, int vFamilyID )
{
	CMessage MsgHead;	
	CMessageNpcListNotify Notify;

	Notify.add_npcid( vNpcID );
	Notify.add_familyid( vFamilyID );

	Notify.set_type( TYPE_FAMILY );

	MsgHead.set_msgpara( (int)&Notify );
	MsgHead.mutable_msghead()->set_messageid( ID_G2S_NOTIFY_NPCLIST );
	CGateServer::GetSingleton().Send2Scene( vServerID, &MsgHead );
}

// ***************************************************************
//  Function:       GetManagerOfRight
//  Description:   	��ȡ��������ĳ��Ȩ�޵�ְλ��߲������ߵĳ�Ա��Ϣ
//  OutPut:         
//  Others:
//  Date:           10/26/2009
// 
// ***************************************************************
CGatePlayer *CFamilyManager::GetManagerOfRight( CFamily *pFamily, int nRight )
{  
	if ( pFamily == NULL )
	{
		return NULL;
	}
	
	int tRoleIDList[MAX_FAMILYMEMBER_NUM] = { 0 };
	int tPostList[MAX_FAMILYMEMBER_NUM] = { 0 };
	int tContributeList[MAX_FAMILYMEMBER_NUM] = { 0 };	
	int tNum = MAX_FAMILYMEMBER_NUM;
	int tRet = pFamily->ListMemberOfRight( tRoleIDList, tPostList, tContributeList, tNum, nRight );
	if ( tRet != SUCCESS )
	{
		return NULL;
	}	
	
	int tManagerPost = 100;
	int tManagerID	 = 100;
	int tContribute	 = 0;
	CGatePlayer *tpManager = NULL;
	for ( int i = 0; i < tNum; ++i )
	{	  
		CGatePlayer *pPlayer = CPlayerManager::GetSingleton().ScenePlayer( tRoleIDList[i] );
		if ( pPlayer == NULL )
		{
			continue;
		} 		
		if ( tPostList[i] < tManagerPost )
		{
			tManagerPost = tPostList[i];
			tManagerID = tRoleIDList[i];
			tpManager = pPlayer;
			tContribute = tContributeList[i];
		}
		else if ( tPostList[i] == tManagerPost && tContribute < tContributeList[i] )
		{
			tManagerPost = tPostList[i];
			tManagerID = tRoleIDList[i];
			tpManager = pPlayer;
			tContribute = tContributeList[i];
		}				
	}
	return tpManager;
}

// ***************************************************************
//  Function:       InsertFamilyReptionKey
//  Description:   	����һ������Key
//  OutPut:         
//  Others:
//  Date:           03/19/2010
// 
// ***************************************************************
int CFamilyManager::InsertFamilyReptionKey( int nFamilyID, KEY_TYPE nReptionKey )
{
	 FamilyRepitonKeyList::iterator it = mFamilyReptionKeyList.find( nFamilyID );
	 if ( it != mFamilyReptionKeyList.end() )
	 {
		it->second = nReptionKey;
	 }
	 else
	 {
		mFamilyReptionKeyList.insert( FamilyRepitonKeyList::value_type( nFamilyID, nReptionKey ) );
	 }
	 return SUCCESS;
}

// ***************************************************************
//  Function:       DeleteFamilyReptionKey
//  Description:   	ɾ��һ������
//  OutPut:         
//  Others:
//  Date:           03/19/2010
// ***************************************************************
int CFamilyManager::DeleteFamilyReptionKey( int nFamilyID )
{
	FamilyRepitonKeyList::iterator it = mFamilyReptionKeyList.find( nFamilyID );
	if ( it != mFamilyReptionKeyList.end() )
	{
		mFamilyReptionKeyList.erase( it );
	}
	
	return SUCCESS;
}

// ***************************************************************
//  Function:       EndFamilyReptionByKey
//  Description:   	ʹ�ø���Key��������
//  OutPut:         bool bNormalEnd ( Ϊtrueʱ��ʾ��������, Ϊfalse��ʾ�쳣����  )
//  Others:
//  Date:           03/19/2010
// 
// ***************************************************************
int CFamilyManager::EndFamilyReptionByKey( KEY_TYPE nReptionKey, bool bNormalEnd )
{
	CFamily *pFamily = NULL;
	for ( FamilyRepitonKeyList::iterator it = mFamilyReptionKeyList.begin(); it != mFamilyReptionKeyList.end(); ++it )
	{
		if ( it->second == nReptionKey )
		{	
			pFamily = GetFamilyByID( it->first );
			mFamilyReptionKeyList.erase( it );					
			break;
		}
	}
	
	if ( pFamily != NULL && bNormalEnd == false )
	{
		pFamily->SetRepetionOpenTimes( 0 );		
		pFamily->ClearFamilyRepetionInfo( );
	}		
	
	return SUCCESS;		
}

// ***************************************************************
//  Function:       DisbandFamily
//  Description:   	���ݼ���ID��ɢ����
//  OutPut:         
//  Others:
//  Date:           09/20/2010
// 
// ***************************************************************
int CFamilyManager::DisbandFamily( CFamily *pFamily )
{	
	if ( pFamily == NULL )
	{
		return SUCCESS;
	}
	
	// ��¼���屻ɾ
	LOG_NOTICE( "family","family(familyid:%d) disbanded, rooterid:%d", pFamily->GetID(), pFamily->GetRooter() );
	
	// �����ݿ���ɾ����Ϣ
	DeletFamilyDBInfo( pFamily );

	// ���ټ�����Ϣ	
	CGateObjManager::GetSingleton( ).DestroyObject( pFamily->get_id() );
	return SUCCESS; 
}

// ***************************************************************
//  Function:       ClearNoExistFamily
//  Description:   	��Ϊ��ɫ�����ڵ�ԭ��ɾ��һ�������ڵļ���
//  OutPut:         
//  Others:
//  Date:           09/20/2010
// 
// ***************************************************************
int CFamilyManager::ClearNoExistFamily( CFamily *pFamily )
{
	LK_ASSERT( pFamily != NULL, return SUCCESS )
	
	// �о��ţ��Ƚ��о��ŵ���ز���
	if ( pFamily->GetCorpsID() > 0 )
	{
		CCorps *tpCorps =   CCorpsManager::GetSingleton().GetCorpsByID( pFamily->GetCorpsID() );
		if ( tpCorps != NULL )
		{
			// ����Ǿ��ų���ɢ����
			if ( tpCorps->GetRooterID() == pFamily->GetRooter() )
			{
				// ����Ǿ����������ɢ����
				CUnion *tpUnion = CCorpsManager::GetSingleton().GetUnionByID( tpCorps->GetUnionID() );
				if ( tpUnion != NULL )
				{					
					if ( tpUnion->GetCoreID() == tpCorps->GetCorpsID() )
					{
						LOG_NOTICE( "corps","CUnion(CUnion:%d) disbanded, rooterid:%d", tpUnion->GetUnionID(), tpUnion->GetCoreID() );
						CCorpsManager::GetSingleton().OnEventDisbandUnion( tpCorps->GetRooterID() );
					}
					else
					{
						tpUnion->RemoveCorps( tpCorps->GetCorpsID() );
					}
				}  
				
				
				int tCorpsID = tpCorps->GetCorpsID();	
				LOG_NOTICE( "corps","corps(corps:%d) disbanded, rooterid:%d", tpCorps->GetCorpsID(), tpCorps->GetRooterID() );
				CCorpsManager::GetSingleton().DisbandCorps( tpCorps );
				CCorpsManager::GetSingleton().RemoveCorpsFromList( tCorpsID );						
				
			}	
			
			// �뿪����			
			else
			{				
				tpCorps->GetFamilyList().erase( tpCorps->GetFamilyList().find( pFamily->GetCorpsID() ) );
			}
		}
	}
	
	// ��ɢ����	
	DisbandFamily( pFamily );
	return SUCCESS;
}

// ***************************************************************
//  Function:     RemoveFromList
//  Description:  ���б����Ƴ�����
//  OutPut:         
//  Others:
//  Date:           09/21/2010
// 
// ***************************************************************
int CFamilyManager::RemoveFromList( int nFamilyID )
{
	m_tFamilies.erase( m_tFamilies.find( nFamilyID ) );
	return SUCCESS;
}

// ***************************************************************
//  Function:     CheckFamily
//  Description:  �������������ڵ���Ϣ
//  OutPut:         
//  Others:
//  Date:           09/21/2010
// 
// ***************************************************************
int CFamilyManager::CheckFamily()
{
	for ( TFamilies::iterator it = m_tFamilies.begin(); it != m_tFamilies.end();  )
	{
		CFamily *pFamily = ( CFamily * )CGateObjManager::GetSingleton().GetObject( it->second );
		if ( pFamily == NULL )
		{
			++it;
			continue;
		}
		
		if ( pFamily->CheckFamilyRoleInfo() == CFamily::EM_MEMBERINFO_NEEDDISBAD )
		{
			ClearNoExistFamily( pFamily );
			m_tFamilies.erase( it ++ );
		}
		else
		{
			++it;
		}			
	}
	return SUCCESS;
}

// ***************************************************************
//  Function:     CheckFamilyStability
//  Description:  �����尲����
//  OutPut:         
//  Others:
//  Date:           12/01/2010
// 
// ***************************************************************
int CFamilyManager::CheckFamilyStability()
{
	if ( m_tFamilies.empty() )
	{
		return 0;
	}	
	for ( TFamilies::iterator it = m_tFamilies.begin(); it != m_tFamilies.end();  )
	{
		CFamily *pFamily = ( CFamily * )CGateObjManager::GetSingleton().GetObject( it->second );
		if ( pFamily == NULL )
		{
			++it;
			continue;
		}
		
		// ���ڼ��ټ��尲����				
		int tStability = 0;
		GetFamilyConfig()->GetReduceStability( pFamily->GetLevel(), tStability );
		int tOldStability = pFamily->GetStabilityDegree();
		pFamily->ReduceStabilityDegree( tStability );
		int tNewStability = pFamily->GetStabilityDegree();
		if ( tNewStability < tOldStability )
		{
			CServiceFamily::GetSingleton().SendNotifyFamilyStabilityChanged( tNewStability, pFamily->GetRooter(), pFamily->GetID(), REASON_REDUCEONTIME, tOldStability - tNewStability, pFamily->GetRooterName() );
		}
		
		int tUseStabily = GetFamilyConfig()->GetStabilityConfig()->GetUseStability();
		if ( pFamily->GetStabilityDegree() > 0 || tUseStabily <= 0 )
		{	
			++it;			
			continue;		
		} 
		
		if ( DisbandedFamilyOrg( pFamily ) == false )
		{
			++it;	
			continue;
		}
		
		// ���ͼ����ɢ��ϵͳ�ʼ�
		SendDisbandNoticeByMail( pFamily );	
		
		// ���尲����С��0,��ɢ����
		int tRoleIDList[MAX_FAMILYMEMBER_NUM] = { 0 };
		int tNum = MAX_FAMILYMEMBER_NUM;							   
		pFamily->GetFamilyMemberIDList( tRoleIDList, tNum );
		CServiceFamily::GetSingleton().SendNotifyDisbandFamily( pFamily->GetID(), tRoleIDList, tNum );		

		// �����ݿ���ɾ����Ϣ
		DeletFamilyDBInfo( pFamily );

		// ��������ɾ������Ϣ
		m_tFamilies.erase( it++ );

		// ���ټ�����Ϣ	
		CGateObjManager::GetSingleton( ).DestroyObject( pFamily->get_id() );  	 		
	}
	return SUCCESS;	
}

// ***************************************************************
//  Function:     SendDisbandNoticeByMail
//  Description:  ���ͼ����ɢ��ϵͳ�ʼ�
//  OutPut:         
//  Others:
//  Date:           12/01/2010
// 
// ***************************************************************	
int CFamilyManager::SendDisbandNoticeByMail( CFamily *pFamily )
{
	LK_ASSERT( pFamily != NULL, return -1 )
	int tMemberList[MAX_FAMILYMEMBER_NUM] = { 0 };
	int tNum = MAX_FAMILYMEMBER_NUM;
	pFamily->GetFamilyMemberIDList( tMemberList, tNum, pFamily->GetRooter() );
	int tDisbandMailID = GetFamilyConfig()->GetStabilityConfig()->GetDisbandMailID();
	int tHeaderMailID = GetFamilyConfig()->GetStabilityConfig()->GetHeaderMailID();	
	char tName[NAME_LENGTH] = { 0 };
	
	// ��ȡ����
	CSceneServer* tpSceneServer = CGateServer::GetSingleton().GetServerByID( pFamily->GetCountryID() );
	if( tpSceneServer == NULL )
	{
		LOG_ERROR( "default", "[%s] Can't get scene server by  CountryID(%d)", __FUNCTION__, pFamily->GetCountryID() );
		return -1;
	}
		
	// �������Ա�����ʼ�	
	sprintf( tName, "%d", tDisbandMailID );	
	CMessage tMsgHead;
	CMessageSendSysMailToPlayer tMsgSysMail;
	tMsgHead.mutable_msghead()->set_messageid( ID_G2S_NOTIFY_SENDSYSMAILTOPLAYER );	
	tMsgHead.set_msgpara( (int)&tMsgSysMail );	
	tMsgSysMail.set_role_name( tName );
	tMsgSysMail.set_mailsendtype( MAILSENDTYPE_BYID );
	tMsgSysMail.set_receive_countryid( pFamily->GetCountryID() );
	for ( int i = 0; i < tNum; ++i )
	{		
		tMsgSysMail.set_role_id( tMemberList[i] );		
		CGateServer::GetSingleton().Send2Scene( tpSceneServer, &tMsgHead );		
	}
	
	// �����峤�����ʼ�
	memset( tName, 0, sizeof( tName ) );
	sprintf( tName, "%d", tHeaderMailID );	
	tMsgSysMail.Clear();
	tMsgSysMail.set_mailsendtype( MAILSENDTYPE_BYID );
	tMsgSysMail.set_sender_name( tName );
	tMsgSysMail.set_role_id( pFamily->GetRooter() );
	tMsgSysMail.set_receive_countryid( pFamily->GetCountryID() );
	CSysMailInfo *tpMailItem = GetFamilyConfig()->GetMailConfig()->GetMailInfoByID( tHeaderMailID );
	if ( tpMailItem != NULL )
	{		
		int tIndex = 0;
		for ( ; tIndex < (int)ARRAY_CNT( tpMailItem->mItemID ) && tIndex < (int)ARRAY_CNT( tpMailItem->mItemNum ); ++tIndex )
		{
			if ( tpMailItem->mItemID[tIndex] > 0 && tpMailItem->mItemNum[tIndex] > 0 )
			{
				tMsgSysMail.add_itemid( tpMailItem->mItemID[tIndex] );
				tMsgSysMail.add_itemnum( tpMailItem->mItemNum[tIndex] );
			}
		}
	}
	CGateServer::GetSingleton().Send2Scene( tpSceneServer, &tMsgHead );	
	return SUCCESS;	
}

// ***************************************************************
//  Function:     DisbandedFamilyOrg
//  Description:  ��ɢ������ϲ���֯
//  OutPut:       bool �����Ƿ���Խ�ɢ
//  Others:
//  Date:           12/01/2010
// 
// ***************************************************************	
bool CFamilyManager::DisbandedFamilyOrg( CFamily *pFamily )
{
	LK_ASSERT( pFamily != NULL, return false )	
	
	// ����ռ��npc���ܽ�ɢ
	if ( pFamily->GetNpcID() != 0 && pFamily->GetBidMoney() == 0 )
	{
		return false;
	}
	
	// û�о��ſ���ֱ�ӽ�ɢ		
	if ( pFamily->GetCorpsID() == 0 )
	{
		return true;
	}
	
	// ��ȡ����
	CCorps *tpCorps = CCorpsManager::GetSingleton().GetCorpsByID( pFamily->GetCorpsID() );
	if ( tpCorps == NULL )
	{
		return true;
	}	
	
	// ��������������뿪����
	if ( tpCorps->GetRooterID() != pFamily->GetRooter() )
	{
		int tRet = CCorpsManager::GetSingleton().OnEventLeaveCorps( pFamily->GetRooter() );					
		if ( tRet != SUCCESS )
		{
			return false;
		}		
		
		// ���ͼ����뿪���ŵ�֪ͨ
		int tRoleIDList[CORPS_MAXMEMBERNUM] = { 0 };
		int tNum = CORPS_MAXMEMBERNUM;
		CCorpsManager::GetSingleton().GetCorpsMemberList( tpCorps, tRoleIDList, tNum, pFamily->GetID(), 0 ); 	
		CCorpservice::GetSingleton().SendNotifyFamilyLeaved( pFamily->GetID(), pFamily->GetName(), tRoleIDList, tNum );
		return true;
	}		
	
	// �����Ƿ���ռ����Ϣ	
	if ( tpCorps->IsInBattle( TYPE_BATTLE_SCRABBLE, ST_Single|ST_Occupy ) == true )
	{
		return false;		
	}	

	CUnion *tpUnion = CCorpsManager::GetSingleton().GetUnionByID( tpCorps->GetUnionID( ) );
	if ( tpUnion == NULL )
	{		
		CCorpsManager::GetSingleton().DeleteCorpsWithNotify( tpCorps );
		return true;
	}
	
	// ���˳�Ա�����Խ�ɢ
	if ( tpUnion->GetCoreID() != tpCorps->GetCorpsID() )
	{
		// �Ӿ�������ɵ�
		tpUnion->RemoveCorps( tpCorps->GetCorpsID() );
		
		// ��ɢ���Ų���֪ͨ
		CCorpsManager::GetSingleton().DeleteCorpsWithNotify( tpCorps );
		return true;
	}	

	// ������ռ��Ļ����ܽ�ɢ
	if ( tpCorps->IsInBattle( TYPE_BATTLE_SCRABBLE, ST_Union|ST_Occupy ) == true )
	{
		return false;
	}
	
	// �Ǿ���������,���˽�ɢ
	CCorpsManager::GetSingleton().DeleteUnionWithNotify( tpUnion, tpCorps->GetRooterID() );
	
	// ��ɢ����
	CCorpsManager::GetSingleton().DeleteCorpsWithNotify( tpCorps );
	return true;
}

// ***************************************************************
//  Function:     InsertStablity
//  Description:  ����һ�������ȵ�����
//  Date:           11/30/2010
// 
// ***************************************************************
int CStability::InsertStablity( int nTimeValue, int nStability )
{	
	unsigned int tIndex =0;
	for ( ; tIndex < ARRAY_CNT( mTimeValue ) && mTimeValue[tIndex] > 0; ++tIndex )
	{
		if ( nTimeValue <= mTimeValue[tIndex] )
		{
			break;
		}								
	}			

	for ( unsigned int i = tIndex + 1; i < ARRAY_CNT( mTimeValue ) && mTimeValue[i-1] > 0 && tIndex > 0; ++i )
	{		
		int tTimeValue = mTimeValue[i];
		int tStablity  = mStability[i];	
		mTimeValue[i] = mTimeValue[tIndex];
		mStability[i] = mStability[tIndex];		
		mTimeValue[tIndex] = tTimeValue;
		mStability[tIndex] = tStablity;
	}
	
	mTimeValue[tIndex] = nTimeValue;
	mStability[tIndex] = nStability;
	return SUCCESS;
}

// ***************************************************************
//  Function:     GetStablity
//  Description:  ��ȡ������
//  Date:         11/30/2010
// 
// ***************************************************************
int CStability::GetStablity( int nTimeValue, int &rOnLineTime )
{
	int tStability = 0;	
	unsigned int tIndex = 0;
	rOnLineTime = 0;
	for ( ; mTimeValue[tIndex] > 0 && tIndex < ARRAY_CNT( mTimeValue );  ++tIndex )
	{
		if ( nTimeValue < mTimeValue[tIndex] )
		{			
			break;
		}
	}
	if ( tIndex > 0 )
	{
		tStability = mStability[tIndex-1];
		rOnLineTime = mTimeValue[tIndex-1];
	}
	return tStability;
}

// ***************************************************************
//  Function:     InsertLevelInfo
//  Description:  ����һ���ȼ���ص�����
//  Date:         11/30/2010
// ***************************************************************
void CStabilityConfig::InsertLevelInfo( CStability &rStabiliy )
{
	unsigned int tIndex =0;
	for ( ; tIndex < ARRAY_CNT( mLevelStablity ) && mLevelStablity[tIndex].mLevel > 0; ++tIndex )
	{
		if ( rStabiliy.mLevel <= mLevelStablity[tIndex].mLevel )
		{
			break;
		}								
	}	
		
	for ( unsigned int i = tIndex + 1; i < ARRAY_CNT( mLevelStablity ) && mLevelStablity[i-1].mLevel > 0 && tIndex > 0; ++i )
	{							
		CStability tStablity = mLevelStablity[i];		
		memcpy( &mLevelStablity[i], &mLevelStablity[tIndex], sizeof( CStability ) );
		mLevelStablity[tIndex] = tStablity;

	}
	
	memcpy( &mLevelStablity[tIndex], &rStabiliy, sizeof( CStability ) );
}

// ***************************************************************
//  Function:     GetStabilityValue
//  Description:  ��ȡĳ���ȼ�����ʱ������Ӧ�İ�����
//  Date:         11/30/2010
// ***************************************************************
int CStabilityConfig::GetStabilityValue( int nLevel, int nTime, int &rOnLineTime )
{		
	unsigned int tIndex = 0;
	int tStability = 0;
	for ( ; mLevelStablity[tIndex].mLevel > 0 && tIndex < ARRAY_CNT( mLevelStablity );  ++tIndex )
	{
		if ( nLevel < mLevelStablity[tIndex].mLevel )
		{			
			break;
		}
	}
	
	if ( tIndex > 0 )
	{
		tStability = mLevelStablity[tIndex-1].GetStablity( nTime, rOnLineTime );
	}	
	return tStability;
}

// ***************************************************************
//  Function:     Initialize
//  Description:  ��ʼ��
//  Date:         11/30/2010
// ***************************************************************
int CStabilityConfig::Initialize()
{
	mMoneyStablity = 0;
	mTaskStability = 0;	
	memset( mLevelStablity, 0, sizeof( mLevelStablity ) );
	mUseStability = 0;
	return SUCCESS;
}

// ***************************************************************
//  Function:     InsertMailInfo
//  Description:  ����һ���ʼ���Ϣ
//  Date:         12/02/2010
// ***************************************************************
int CMailConfig::InsertMailInfo( int nSysID, CSysMailInfo &rMailInfo )
{
	mMailInfoList.insert( MailInfoList::value_type( nSysID, rMailInfo ) );
	return SUCCESS;	
}

// ***************************************************************
//  Function:     GetMailInfoByID
//  Description:  ��ȡĳ���ʼ���Ϣ
//  Date:         12/02/2010
// ***************************************************************
CSysMailInfo * CMailConfig::GetMailInfoByID( int nSysID )
{
	MailInfoList::iterator it = mMailInfoList.find( nSysID );
	if ( it != mMailInfoList.end() )
	{
		return &(it->second);
	}
	return NULL;
}

// ***************************************************************
//  Function:     GetRedStoneID
//  Description:  ��ȡ��ǰ���尲������Ӧ�û�ȡ���ڵ�ID
//  Date:         12/28/2010
// ***************************************************************
int CStabilityRedstone::GetRedStoneID( int nStablity, int &rExtraExp )
{
	
	rExtraExp = 0;
	unsigned int i = 0;
	for ( ; i < ARRAY_CNT( mStability ) && i < ARRAY_CNT( mRedstoneID ) && mStability[i] > 0; ++i )
	{
		if ( nStablity <= mStability[i] )
		{
			rExtraExp = mEtraExp[i];				
			return mRedstoneID[i];
		}				
	}

	if ( i > 0 )
	{
		rExtraExp = mEtraExp[i-1];	
		return mRedstoneID[i-1];			
	}	
	return 0;
}

// ***************************************************************
//  Function:     InsertStabilityRedstone
//  Description:  ����ĳ�������ȶ�Ӧ���ڵ�ID
//  Date:         12/28/2010
// ***************************************************************
int CStabilityRedstone::InsertStabilityRedstone(int nStability, int nRedstone, int nExtraExp )
{
	unsigned int tIndex = 0;
	for ( ; tIndex < ARRAY_CNT( mStability ) && tIndex < ARRAY_CNT( mRedstoneID ) && mStability[tIndex] > 0; ++tIndex )
	{
		if ( nStability <= mStability[tIndex] )
		{
			break;
		}
	 }

	for ( unsigned int i = tIndex + 1; i < ARRAY_CNT( mStability ) && i < ARRAY_CNT( mRedstoneID ) && tIndex > 0; ++i  )
	{
		int tStability = mStability[i];
		int tRestoneID = mRedstoneID[i];
		int tEtraExp   = mEtraExp[i];	
		mStability[i] = mStability[tIndex];	
		mRedstoneID[i] = mRedstoneID[tIndex];
		mEtraExp[i] = mEtraExp[tIndex];	
		mStability[tIndex] = tStability;
		mRedstoneID[tIndex] = tRestoneID;
		mEtraExp[tIndex] = tEtraExp;
	}

	mStability[tIndex] = nStability;
	mRedstoneID[tIndex] = nRedstone;
	mEtraExp[tIndex] = nExtraExp;
	return SUCCESS;
}

// ***************************************************************
//  Function:     GetRedStoneInfo
//  Description:  ��ȡĳ���ȼ��¼���
//  Date:         12/29/2010
// ***************************************************************
int CFamilyRedstoneConfig::GetFamilyRedstone( int nLevel, int nStablity, int &rExtraExp )
{
	rExtraExp = 0;
	if ( nLevel >= 1 && nLevel <= (int)ARRAY_CNT(  mStablityRedstone ) )
	{
		return mStablityRedstone[nLevel-1].GetRedStoneID( nStablity, rExtraExp );
	}
	return 0;
}

// ***************************************************************
//  Function:     InsertFamilyRedstone
//  Description:  ����һ�������ڵ�����
//  Date:         12/29/2010
// ***************************************************************
int CFamilyRedstoneConfig::InsertFamilyRedstone(int nLevel, int nRedstoneID, int nStablity, int nExtraExp )
{	
	if ( nLevel >= 1 && nLevel <= (int)ARRAY_CNT( mStablityRedstone ) )
	{
		mStablityRedstone[nLevel-1].InsertStabilityRedstone( nStablity, nRedstoneID, nExtraExp );
	}
	return SUCCESS;	
}