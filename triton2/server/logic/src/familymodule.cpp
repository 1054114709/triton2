#include "stdafx.hpp"
#include "westserver.h"	  
#include "familymodule.h"
#include "familymessage_pb.hxx.pb.h"
#include "message_pb.hxx.pb.h"
#include "familydbinfo_pb.hxx.pb.h"
#include "entity.h"
#include "scenecfg_manager.h"
#include "protype.h"
#include "scenelogic.h"
#include "propertymodule.h"
#include "mapobjmanager.h"
#include "activitymodule.h"
#include "corpsmodule.h"
#include "logmodule.h"
#ifdef LEAK_CHK_DEBUG_NEW
#include "debug_new.h"
#endif

class CMapObject;

template<> CFamilyModule * CSingleton< CFamilyModule >::spSingleton = NULL;
typedef ::google::protobuf::Message Message;

char CFamilyModule::sModuleName[NAME_LENGTH] = "familyModule";

// ***********************************************************
//  Function:		CountSize
//  Description:	�������ģ��Ĵ�С 				
//  Output:			
//  Date:	04/20/2009
// **********************************************************
unsigned int CFamilyModule::CountSize( )
{
	unsigned int tSize = sizeof( CFamilyModule );
	return tSize;
}

// ***********************************************************
//  Function:		OnLaunchServer
//  Description:	���������� 				
//  Output:			
//  Date:	04/20/2009
// **********************************************************
void CFamilyModule::OnLaunchServer( )
{
	mNameList.initailize();
	mNpcList.initailize();
	mFamilyList.initailize();
	mFamilyTask.initailize();
	OnLoadConfig();
}

// ***********************************************************
//  Function:		OnExitServer
//  Description:	���������� 				
//  Output:			
//  Date:	04/20/2009
// **********************************************************
void CFamilyModule::OnExitServer( )
{
	
}

// ***********************************************************
//  Function:		OnTimer	
//  Description:	������Timer
//  Output:			
//  Date:	04/20/2009
// **********************************************************
void CFamilyModule::OnTimer( unsigned int vTickCount, unsigned int vTickOffsekt )
{
	
}

// ***********************************************************
//  Function:		OnCreateMap
//  Description:	��������
//  Output:			
//  Date:	04/20/2009
// **********************************************************
int CFamilyModule::OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName )
{
	  return SUCCESS;
}

// ***********************************************************
//  Function:		OnRouterMessage
//  Description:	·����Ϣ
//  Output:			
//  Date:	04/20/2009
// **********************************************************
void CFamilyModule::OnRouterMessage( CMessage* pMessage )
{
	
}


// ***********************************************************
//  Function:		OnClientMessage
//  Description:	�ͻ�����Ϣ
//  Output:			
//  Date:	04/20/2009
// **********************************************************
void CFamilyModule::OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer!=NULL && pMessage != NULL, return );
	switch ( pMessage->mutable_msghead()->messageid() )
	{
		case ID_C2S_REQUEST_CREATFAMILY:
		{
			OnMessageCreatFamily( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_INVITEMEMBER:
		{
			OnMessageInviteMember( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_REPLYFAMILYINVITE:
		{
			OnMessageReplyFamilyInvite( pPlayer, pMessage );	
		}
		break;
		case ID_C2S_REQUEST_FAMILYAPPLY:
		{
			OnMessageApplyFamily( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_REPLYMEMBERAPPLY:
		{
			OnMessageReplyMemberApply( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_POSTAPPOINT:
		{
			OnMessagePostAppoint( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_LEAVEFAMILY:
		{
			OnMessageLeaveFamily( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_GETFAMILYMEMBERINFO:
		{
			OnMessageGetFamilyMemberInfo( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_GETFAMILYPROPERTY:
		{
			OnMessageGetFamilyPropetyInfo( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_GETALLFAMILYINFO:
		{
			OnMessageGetAllFamilyInfo( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_GETAPPLYLIST:
		{
			OnMessageGetApplyList( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_KICKMEMBER:
		{
			OnMessageKickPlayer( pPlayer, pMessage );
		}
		break;	
		case ID_C2S_REQUEST_DISBANDFAMILY:
		{
			OnMessageDisbandFamily( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_CHANGENOTICE:
		{
			OnMessageChangeFamilyNotice( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_APPOINTHEADER:
		{
			OnMessageAppointHeader( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_CLEARFAMILYAPPLYLIST:
		{
			OnMessageClearFamilyApply( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_CANCELFAMILYDISBAND:
		{
			OnMessageCancelDisbandFamily( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_REFRESHFAMILYINFO:
		{
			OnMessageRefreshFamilyInfo( pPlayer, pMessage );
		}			 
		break;
		
		case ID_C2S_REQUEST_SETFAMILYMEMBERPOST:
		{
			OnMessageSetFamilyMemberPost( pPlayer, pMessage );
		}
		break;

		case ID_C2S_REQUEST_LEVELUPFAMILY:
		{
			OnMessageLevelUPFamily( pPlayer, pMessage );
		}
		break;
		
		case ID_C2S_REQUEST_CONTRIBUTEFAMILYMONEY:
		{
			OnMessageContributeFamilyMoney( pPlayer, pMessage );
		}
		break;
		
		case ID_C2S_REQUEST_OBTAINFAMILYMONEY:
		{
			OnMessageObtainFamilyMoney( pPlayer, pMessage );
		}
		break;		 
		case ID_C2S_REQUEST_BIDNPC:
		{
			OnMessageBidNpc( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_BIDINFO:
		{
			OnMessageBidInfo( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_MEMBERSUBMIT:
		{
			OnMessageMemberSubmit( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_ABORTNPC:
		{
			OnMessageAbortNpc( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_MAKEROOM:
		{
			OnMessageMakeRoom( pPlayer, pMessage );
		}			 
		break;

		case ID_C2S_REQUEST_CHAROOM:
		{
			OnMessageChaRoom( pPlayer, pMessage );
		}
		break;

		case ID_C2S_REQUEST_AGREEBATTLE:
		{
			OnMessageAgreeBattle( pPlayer, pMessage );
		}
		break;

		case ID_C2S_REQUEST_QUERYALLROOM:
		{
			OnMessageQueryAllRoom( pPlayer, pMessage );
		}
		break;

		case ID_C2S_REQUEST_QUERYMYROOM:
		{
			OnMessageQueryMyRoom( pPlayer, pMessage );
		}
		break;		 
		case ID_C2S_REQUEST_QUERYMYCHA:
		{
			OnMessageQueryMyCha( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_ABORTROOM:
		{
			OnMessageAbortRoom( pPlayer, pMessage );
		}
		break;
		case ID_C2S_REQUEST_ABORTCHA:
		{
			OnMessageAbortCha( pPlayer, pMessage );
		}
		break; 	
		
		case ID_C2S_REQUEST_STARTFAMILYBOSS:
		{
			OnMessageStartFamilyBoss( pPlayer, pMessage );
		}		
		break;
				
		case ID_C2S_REQUEST_QUERYNPCWELFARE:
		{
			OnMessageQueryFamilyWelfare( pPlayer, pMessage );
		}				
		break;
		
		case ID_C2S_REQUEST_GETFAMILYMONEY:
		{
			OnMessageGetFamilyMoney( pPlayer, pMessage );
		}
		break;
		
		case ID_C2S_REQUEST_GETEXPCARD:
		{
			OnMessageGetFamilyExpCard( pPlayer, pMessage );
		}	
		break;	
		
		case ID_C2S_REQUEST_ENTERBOSSREPTION:
		{
			OnMessageEnterFamilyRepetion( pPlayer, pMessage );
		}	
		break;
		
		case ID_C2S_REQUEST_GETFAMILYGOODSLIST:
		{
			OnMessageGetFamilyGoodsList( pPlayer, pMessage );
		}
		break;
		
		case ID_C2S_REQUEST_GETFAMILYEXCHANGEGOODSLIST:
		{
			OnMessageGetFamilyExchangeGoodsList( pPlayer, pMessage );
		}
		break;
		
		default:
			break;
	}	
}

// ***********************************************************
//  Function:		OnCreateEntity
//  Description:	����ʵ��
//  Output:			
//  Date:	04/20/2009
// **********************************************************
void CFamilyModule::OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst )
{ 
	LK_ASSERT( pEntity != NULL, return )		
	//if ( pEntity->IsPlayer() )
	//{
	//	CEntityPlayer *tpPlayer = ( CEntityPlayer * )pEntity;
	//	if ( tpPlayer->GetFamilyID() != 0 )
	//	{
	//		// InsertFamilyMember( tpPlayer->GetCorpsID(), tpPlayer->GetFamilyID(), tpPlayer->GetEntityID() );
	//	}
	//}
}

// ***********************************************************
//  Function:		OnDestroyEntity
//  Description:	����ʵ��
//  Output:			
//  Date:	04/20/2009
// **********************************************************
void CFamilyModule::OnDestroyEntity( CEntity* pEntity, int vCode )
{ 
	LK_ASSERT( pEntity != NULL, return )		
	if ( pEntity->IsPlayer() )
	{
		CEntityPlayer *tpPlayer = ( CEntityPlayer * )pEntity;
		if ( tpPlayer->GetFamilyID() > 0 )
		{			
			// �ı������ҫֵ
			int tExpGloryNeeded = CSceneCfgManager::GetSingletonPtr( )->GetFamily_cfg( )->mExpperglory;			
			int tAPGloryNeeded = CSceneCfgManager::GetSingletonPtr( )->GetFamily_cfg( )->mExploitperglory;	
			int tGlory = 0;	
			
			CMemberInfo *tpMemberinfo = GetFamilyMemberInfo( tpPlayer )	;
			if ( tpMemberinfo != NULL )
			{
				if ( tExpGloryNeeded > 0 )
				{
					tGlory += tpMemberinfo->mExpGloryNeeded / tExpGloryNeeded;				
				}	
				if ( tAPGloryNeeded > 0 )
				{
					tGlory += tpMemberinfo->mApGloryNeeded / tAPGloryNeeded;
				}
				if ( tGlory > 0 )
				{
					ChangeFamilyGlory( tpPlayer, tGlory, false, REASON_MEMBEREXP );
				}	
			}		
			
			int tCfgTime = CSceneCfgManager::GetSingleton().GetFamily_cfg()->mMinstabilitytime;
			if ( tCfgTime > 0 )
			{
				int tTimeLength = ( time( NULL ) - tpPlayer->GetLoginTime() )/tCfgTime;
				if ( tTimeLength > 0 )
				{
					ChangeFamilyStability( tpPlayer, 0, REASON_ONLINETIME, tpPlayer->GetLevel(), tTimeLength );			
				}			
			}			
		}
		
		// ɾ�������еļ������
		DeleteFamilyMember( tpPlayer->GetFamilyID(), tpPlayer->GetCharID() );										
	}	
}

// ***********************************************************
//  Function:		OnSaveData
//  Description:	��������
//  Output:			
//  Date:	04/20/2009
// **********************************************************
bool CFamilyModule::OnSaveData( CEntityPlayer* pPlayer, int vSaveCode )
{
	return true;	
}

// ***********************************************************
//  Function:		OnLoadConfig
//  Description:	��������
//  Output:			
//  Date:	04/20/2009
// **********************************************************
void CFamilyModule::OnLoadConfig(  )
{
	FAMILY_LOG* tpCfg  = CSceneCfgManager::GetSingletonPtr( )->GetFamily_log( );	
	if( tpCfg != NULL )
	{
		INIT_ROLLINGFILE_LOG( tpCfg->mIdentifier, tpCfg->mDirectory, ( LogLevel )tpCfg->mPriority, tpCfg->mMaxfilesize, tpCfg->mMaxbackupindex );
	}
	int tRet = InitialFamilyConfig();	
	if ( tRet != SUCCESS )
	{
		LOG_ERROR( "family","Load FamilyConfig Error!" );
		printf( "Load FamilyConfig Error!" );
	}
	const char* pcConfigPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"family/familyconfig.xml" );
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CFamilyModule::LoadFamilyConfigCallback);
}

// ***********************************************************
//  Function:		OnTimeoutMessage
//  Description:	��ʱ����Ϣ
//  Output:			
//  Date:	04/20/2009
// **********************************************************
void CFamilyModule::OnTimeoutMessage( CMessage* pMessage )
{
	
}

// ***********************************************************
//  Function:		OnMessageCreatFamily
//  Description:	�����������Ϣ
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessageCreatFamily( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageCreatFamilyRequest *tpMsg = ( CMessageCreatFamilyRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	LK_ASSERT( tpMsg->familyname().length() < ( MAX_FAMILYNAME_LENGTH*MAX_UTF8_BYTES ), return );
	
	// ����״̬�����ط�����Ϣ֮ǰ�����ٴ�������
	if( pPlayer->GetFamilyID() == INVALID_FAMILYCORPSID )
	{
		return;
	}
	
	// ����ǿ��ַ����򷵻�
	if ( !tpMsg->has_familyname() )
	{
		return;
	}
	
	if ( tpMsg->familyname().length() <= 0 )
	{
		return;
	}
	
	// ����npc���ж�
	bool tSerRet = CheckNpcFamilyService( pPlayer, tpMsg->npcentityid(), FAMILYSERVICE_FAMILYNPC );
	if ( tSerRet == false )
	{
		return;
	}		

	CMessage MsgHead;
	CMessageCreatFamilyResponse MsgCreatFamily;
	MsgHead.set_msgpara( (int)&MsgCreatFamily );
	MsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_CREATFAMILY );		
	
	// û�м�����Դ�������
	if ( pPlayer->GetFamilyID() != 0 )
	{	
		MsgCreatFamily.set_errcode( ERROR_FAMILY_CREATFAMILY_HASFAMILY );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;		
	}  
		
	// �ȼ���֤
	if ( pPlayer->GetLevel() < LEVEL_CREATFAMILY )
	{
		MsgCreatFamily.set_errcode( ERROR_FAMILY_CREATFAMILY_LEVELLOW );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;
	}
	
	// �����֤
	int tRet = CDirtyWord::GetSingleton().OI_Dirty_Check( 3, (char *)tpMsg->familyname().c_str() );
	if ( tRet != 0 )
	{
		MsgCreatFamily.set_errcode( ERROR_FAMILY_CREATFAMILY_HASDIRTYWORD );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;	
	}
	

	// ��Ǯ��֤	TODO:�����첽����
	if ( pPlayer->GetMoney() < COST_CREATFAMILY )
	{
		MsgCreatFamily.set_errcode( ERROR_FAMILY_CREATFAMILY_MONEYNOTENONGH );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;	
	}
	
	// ��ȴʱ������
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	if ( time( NULL ) - tpProperty->GetLastTimeLeaveFamily( ) <= FAMILY_LEAVEFAMILY_TIMELENGTH )
	{  
		MsgCreatFamily.set_errcode( ERROR_FAMILY_CREATFAMILY_INDISBANDCOOLTIME );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;
	}
	
	// ����״̬�����ط�����Ϣ֮ǰ�����ٴ�������
	pPlayer->SetFamilyID( INVALID_FAMILYCORPSID );
	
	LOG_NOTICE( "family","[%s,%d][%s] Player( roleid:%d ) creat family at time:(%d), money( %d ) consumed ", __LK_FILE__, __LINE__, __FUNCTION__, pPlayer->GetCharID(), time(NULL), COST_CREATFAMILY );
	
	// �ȿ۵���Ǯ������ʧ��ʱ�ٷ���		
	tpProperty->SetMoney( tpProperty->GetMoney() - COST_CREATFAMILY );
	SenMsgToGate( pMessage, tpMsg, pPlayer );	
}

// ***********************************************************
//  Function:		OnMessageDisbandFamily
//  Description:	��ɢ�������Ϣ
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessageDisbandFamily( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageDisbandFamilyRequest *tpMsg = ( CMessageDisbandFamilyRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	
	// npc���ܼ��
	bool tRet = CheckNpcFamilyService( pPlayer, tpMsg->npcentityid(), FAMILYSERVICE_FAMILYNPC );
	if ( tRet == false )
	{
		return;
	}
	
	if( pPlayer->GetFamilyID() == 0 )
	{
		CMessage MsgHead;
		CMessageDisbandFamilyResponse MsgDisbandFamily;
		MsgDisbandFamily.set_errcode( ERROR_FAMILY_DISBAND_HASNOFAMILY );
		
		MsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_DISBANDFAMILY );
		MsgHead.set_msgpara( (int)&MsgDisbandFamily );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
		return;
	}
	
	SenMsgToGate( pMessage, tpMsg, pPlayer ) 	
}

// ***********************************************************
//  Function:		OnMessageGetAllFamilyInfo
//  Description:	��ȡ���м���Ļ�����Ϣ
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessageGetAllFamilyInfo( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageGetAllFanmilyInfoRequest *tpMsg = ( CMessageGetAllFanmilyInfoRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	SenMsgToGate( pMessage, tpMsg, pPlayer )  	
}

// ***********************************************************
//  Function:		OnMessageGetApplyList
//  Description:	��ȡ����������б�
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessageGetApplyList( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageGetApplyListRequest *tpMsg = ( CMessageGetApplyListRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	LK_ASSERT( pPlayer->GetFamilyID() != 0, return );
	SenMsgToGate( pMessage, tpMsg, pPlayer )		
}

// ***********************************************************
//  Function:		OnMessageGetFamilyMemberInfo
//  Description:	��ȡ�����Ա�Ļ�����Ϣ
//  Output:			
//  Date:	04/30/2009
// **********************************************************
void CFamilyModule::OnMessageGetFamilyMemberInfo( CEntityPlayer *pPlayer, CMessage *pMessage )
{	 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageGetFamilyMemberInfoRequest *tpMsg = ( CMessageGetFamilyMemberInfoRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	LK_ASSERT( pPlayer->GetFamilyID() != 0, return );
	SenMsgToGate( pMessage, tpMsg, pPlayer ) 	
}

// ***********************************************************
//  Function:		OnMessageGetFamilyPropetyInfo
//  Description:	��ȡ����Ļ���������Ϣ
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessageGetFamilyPropetyInfo( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageGetFamilyPropertyRequest *tpMsg = ( CMessageGetFamilyPropertyRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if ( pPlayer->GetFamilyID() == 0 )
	{
		return;
	}	
	SenMsgToGate( pMessage, tpMsg, pPlayer )
	
}

// ***********************************************************
//  Function:		OnMessageInviteMember
//  Description:	������Ҽ������
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessageInviteMember( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageInviteMemberRequest *tpMsg = ( CMessageInviteMemberRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );	
	
	CMessage MsgHead;
	CMessageInviteMemberResponse MsgInviteMember;  
	MsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_INVITEMEMBER );
	MsgHead.set_msgpara( (int)&MsgInviteMember );
	if  ( pPlayer->GetFamilyID() == 0 )
	{ 	
		return;
	}
	
	// Ȩ���ж�	, �����ж�
	/*if( !pPlayer->GetIsFamilyHeader() ) 
	{
		MsgInviteMember.set_errcode( ERROR_FAMILY_HASNORIGHT );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;
	}*/
	
	CEntityPlayer *pDesPlayer = NULL;
	if ( tpMsg->has_roleid() )
	{

		pDesPlayer = ( CEntityPlayer * )CSceneLogic::GetSingleton().GetPlayerByCharID( tpMsg->roleid() );
				//InviteFamilyMember( pPlayer, tpMsg->roleid(), tpMsg->rolename().c_str() );
	}
	else
	{
		LK_ASSERT( tpMsg->rolename().length() < NAME_LENGTH, return );
		pDesPlayer = ( CEntityPlayer * )CSceneLogic::GetSingleton().GetPlayerByName( tpMsg->rolename().c_str() );
	}  	
	
	// ��Ҳ��ڱ�������������ֱ�ӷ�������
	if ( pDesPlayer == NULL )
	{
		SenMsgToGate( pMessage, tpMsg, pPlayer ) 
		return;
	}
	
	// ����ڱ���������������һЩ�ж�
	if  ( pDesPlayer->GetNationality() != pPlayer->GetNationality() )
	{
		MsgInviteMember.set_errcode( ERROR_FAMILY_INVITE_INDIFFNATION );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;
	}
	
	// �ж��ǲ���������Լ�
	if ( pDesPlayer->GetCharID() == pPlayer->GetCharID() )
	{
		MsgInviteMember.set_errcode( ERROR_FAMILY_INVITE_SELFINVITE );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;		
	}
	
	// �ж϶Է���û�м���
	if ( pDesPlayer->GetFamilyID() != 0 )
	{
		MsgInviteMember.set_errcode( ERROR_FAMILY_INVITE_INFAMILY );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;
	}
	if ( pDesPlayer->GetLevel() < LEVEL_JOINFAMILY )
	{
		MsgInviteMember.set_errcode( ERROR_FAMILY_INVITE_DESLOWLEVEL );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;
	}
	
	// �����������㣬��������
	SenMsgToGate( pMessage, tpMsg, pPlayer )		
}

// ***********************************************************
//  Function:		OnMessageKickPlayer
//  Description:	�߳������Ա
//  Output:			
//  Date:	04/30/2009
// **********************************************************
void CFamilyModule::OnMessageKickPlayer( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageKickPlayerRequest *tpMsg = ( CMessageKickPlayerRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );	
	LK_ASSERT( pPlayer->GetFamilyID() != 0, return );
	
	// ��ȫ������
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	int tPwdCheckRet = tpProperty->GetRolePassword()->CheckActionAllowed( EM_PASSWORD_ACTION_GAMEACTION );
	if ( tPwdCheckRet != SUCCESS )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, tPwdCheckRet );
		return;
	}	
	
	
	SenMsgToGate( pMessage, tpMsg, pPlayer ) 	
}

// ***********************************************************
//  Function:		OnMessageLeaveFamily
//  Description:	����뿪����
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessageLeaveFamily( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageLeaveFamilyRequest *tpMsg = ( CMessageLeaveFamilyRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	
	// ��ȫ������
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	int tPwdCheckRet = tpProperty->GetRolePassword()->CheckActionAllowed( EM_PASSWORD_ACTION_GAMEACTION );
	if ( tPwdCheckRet != SUCCESS )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, tPwdCheckRet );
		return;
	}	
	
	if ( pPlayer->GetFamilyID() == 0 )
	{
		return;
	}
	SenMsgToGate( pMessage, tpMsg, pPlayer ) 	
}

// ***********************************************************
//  Function:		OnMessagePostAppoint
//  Description:	����ְλ
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessagePostAppoint( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessagePostAppointRequest *tpMsg = ( CMessagePostAppointRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	LK_ASSERT( pPlayer->GetFamilyID() != 0, return );
	
	// ���밲ȫ���
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	int tPwdCheckRet = tpProperty->GetRolePassword()->CheckActionAllowed( EM_PASSWORD_ACTION_GAMEACTION );
	if ( tPwdCheckRet != SUCCESS )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, tPwdCheckRet );
		return;
	}	

	SenMsgToGate( pMessage, tpMsg, pPlayer ) 	
	// AppiontPost( pPlayer, tpMsg->playercharid(), tpMsg->actionkind() );
}

// ***********************************************************
//  Function:		OnMessageReplyFamilyInvite
//  Description:	�𸴼�������
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessageReplyFamilyInvite( CEntityPlayer *pPlayer, CMessage *pMessage )
{	 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageReplyFamilyInviteRequest *tpMsg = ( CMessageReplyFamilyInviteRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if ( pPlayer->GetFamilyID() != 0 )
	{
		// TODO:  
		CMessage MsgHead;
		CMessageReplyFamilyInviteResponse MsgReplyInvite;
		MsgReplyInvite.set_errcode( ERROR_FAMILY_INVITE_INFAMILY );
		MsgReplyInvite.set_result( tpMsg->result() );
		
		MsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_REPLYFAMILYINVITE );
		MsgHead.set_msgpara( (int)&MsgReplyInvite );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;		
	}
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty(); 
	
	if ( time( NULL ) - tpProperty->GetLastTimeLeaveFamily( ) <= FAMILY_LEAVEFAMILY_TIMELENGTH )
	{
		if( tpMsg->result() == FAMILY_REPLY_REFUSE || tpMsg->result() == FAMILY_REPLY_IGNORE ) 
		{
			CMessage  MsgHead;
			CMessageReplyFamilyInviteResponse MsgReplyInvite;
			MsgReplyInvite.set_errcode( SUCCESS ); 					
			MsgReplyInvite.set_familyid( tpMsg->familyid() );
			MsgHead.set_msgpara( (int)&MsgReplyInvite );
			MsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_REPLYFAMILYINVITE );
			CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );	
		}
		else
		{
			CMessage  MsgHead;
			CMessageReplyFamilyInviteResponse MsgReplyInvite;
			MsgReplyInvite.set_errcode( ERROR_FAMILY_APPLY_INFAMILYLIMIT ); 					
			MsgReplyInvite.set_familyid( tpMsg->familyid() );
			MsgHead.set_msgpara( (int)&MsgReplyInvite );
			MsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_REPLYFAMILYINVITE );
			CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead ); 
		}		
				
		// ����������֮ǰ��������Ϣ
		tpMsg->set_result( FAMILY_REPLY_DELETE );
	}
		
	//// ����ID����λ����ʧ�ܵĻ�����0
	//if ( tpMsg->result() == 1 )
	//{
	//	pPlayer->SetFamilyID( tpMsg->familyid() );						
	//}
	SenMsgToGate( pMessage, tpMsg, pPlayer ) 		
}

// ***********************************************************
//  Function:		OnMessageReplyMemberApply
//  Description:	���������
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessageReplyMemberApply( CEntityPlayer *pPlayer, CMessage *pMessage )
{	 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageReplyMemberApplyRequest *tpMsg = ( CMessageReplyMemberApplyRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );	
	SenMsgToGate( pMessage, tpMsg, pPlayer ) 	
}

// ***********************************************************
//  Function:		OnMessageAppointHeader
//  Description:	ת������ְλ
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessageAppointHeader( CEntityPlayer *pPlayer, CMessage *pMessage )
{  
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageAppointHeaderRequest *tpMsg = ( CMessageAppointHeaderRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );	  	
	LK_ASSERT( pPlayer->GetFamilyID() != 0, return );
	
	// ��ȫ������
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	int tPwdCheckRet = tpProperty->GetRolePassword()->CheckActionAllowed( EM_PASSWORD_ACTION_GAMEACTION );
	if ( tPwdCheckRet != SUCCESS )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, tPwdCheckRet );
		return;
	}	
	SenMsgToGate( pMessage, tpMsg, pPlayer )  	
}

// ***********************************************************
//  Function:		OnMessageChangeFamilyNotice
//  Description:	�ı���幫��
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessageChangeFamilyNotice( CEntityPlayer *pPlayer, CMessage *pMessage )
{	

	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageChangeFamilyNoticeRequest *tpMsg = ( CMessageChangeFamilyNoticeRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	LK_ASSERT( tpMsg->notice().length() < MAX_FAMILYNOTICE_LENGTH*MAX_UTF8_BYTES, return );
	CDirtyWord::GetSingleton().OI_Dirty_Check( 1, (char *)tpMsg->mutable_notice()->c_str() );
	LK_ASSERT( pPlayer->GetCharID() != 0, return );
	SenMsgToGate( pMessage, tpMsg, pPlayer )   	
}

// ***********************************************************
//  Function:		OnMessageClearFamilyApply
//  Description:	������������б�
//  Output:			
//  Date:	06/09/2009
// **********************************************************
void CFamilyModule::OnMessageClearFamilyApply( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageClearFamilyApplyRequest *tpMsg = ( CMessageClearFamilyApplyRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	SenMsgToGate( pMessage, tpMsg, pPlayer )
}

// ***********************************************************
//  Function:		OnMessageCancelDisbandFamily
//  Description:	����ȡ�������ɢ����Ϣ����
//  Output:			
//  Date:	06/18/2009
// **********************************************************
void CFamilyModule::OnMessageCancelDisbandFamily( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageCancelFamilyDisbandRequest *tpMsg = ( CMessageCancelFamilyDisbandRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	SenMsgToGate( pMessage, tpMsg, pPlayer )
}

// ***********************************************************
//  Function:		OnMessageRefreshFamilyInfo
//  Description:	ˢ�¼�����Ϣ������
//  Output:			
//  Date:	06/23/2009
// **********************************************************
void CFamilyModule::OnMessageRefreshFamilyInfo( CEntityPlayer *pPlayer, CMessage *pMessage )
{  
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageRefreshFamilyInfoRequest *tpMsg = ( CMessageRefreshFamilyInfoRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	SenMsgToGate( pMessage, tpMsg, pPlayer )  
}

// ***********************************************************
//  Function:		OnMessageApplyFamily
//  Description:	�������������Ϣ
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::OnMessageApplyFamily( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageApplyFamilyRequest *tpMsg = ( CMessageApplyFamilyRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	if ( pPlayer->GetFamilyID() != 0 )
	{		
		// TODO:
		CMessage  MsgHead;
		CMessageApplyFamilyResponse MsgApplyFamily;
		MsgApplyFamily.set_errcode( ERROR_FAMILY_APPLY_INFAMILY ); 					
		MsgHead.set_msgpara( (int)&MsgApplyFamily );
		MsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_FAMILYAPPLY );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );									
		return;
	}
	if ( pPlayer->GetLevel() < LEVEL_JOINFAMILY )
	{
		// TODO:
		CMessage  MsgHead;
		CMessageApplyFamilyResponse MsgApplyFamily;
		MsgApplyFamily.set_errcode( ERROR_FAMILY_APPLY_LEVELLOW );
		MsgHead.set_msgpara( (int)&MsgApplyFamily );
		MsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_FAMILYAPPLY );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;
	}
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();			
	if ( time( NULL ) - tpProperty->GetLastTimeLeaveFamily( ) <= FAMILY_LEAVEFAMILY_TIMELENGTH )
	{
		CMessage  MsgHead;
		CMessageApplyFamilyResponse MsgApplyFamily;
		MsgApplyFamily.set_errcode( ERROR_FAMILY_APPLY_INFAMILYLIMIT ); 					
		MsgHead.set_msgpara( (int)&MsgApplyFamily );
		MsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_FAMILYAPPLY );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
		return;	
	}
	if ( time( NULL ) - tpProperty->GetLastFamilyApplyTime() <= FAMILYAPPLY_TIMELIMIT )
	{
		CMessage  MsgHead;
		CMessageApplyFamilyResponse MsgApplyFamily;
		MsgApplyFamily.set_errcode( ERROR_FAMILY_APPLY_INAPPLYTIMELIMIT ); 					
		MsgHead.set_msgpara( (int)&MsgApplyFamily );
		MsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_FAMILYAPPLY );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );	
		return;
	}	
	
	SenMsgToGate( pMessage, tpMsg, pPlayer ) 	
}	   

// ***********************************************************
//  Function:		CreatFamily
//  Description:	��������
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::CreatFamily( CEntityPlayer *pPlayer, const char *pFamilyName )
{  

}

// ***********************************************************
//  Function:		AppiontPost
//  Description:	ְλ����
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::AppiontPost( CEntityPlayer *pPlayer, int PlayerCharID, int ActionKind )
{

}

// ***********************************************************
//  Function:		ApplyFamily
//  Description:	����������
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::ApplyFamily( CEntityPlayer *pPlayer, int vEntityID, int FamilyID /* = 0 */ )
{
	
}

// ***********************************************************
//  Function:		AppointHeader
//  Description:	ת������ְλ
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::AppointHeader( CEntityPlayer *pPlayer, int PlayerCharID )
{

}

// ***********************************************************
//  Function:		ChangeFamilyNotice
//  Description:	�޸ļ��幫��
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::ChangeFamilyNotice( CEntityPlayer *pPlayer, const char *pNotice )
{

}

// ***********************************************************
//  Function:		CheckNpcFamilyService
//  Description:	��鹦��npc�ļ���
//  Output:			
//  Date:	04/21/2009
// **********************************************************
bool CFamilyModule::CheckNpcFamilyService( CEntityPlayer *pPlayer, int nNpcEntityID, int eService )
{
	LK_ASSERT( pPlayer != NULL, return  false )
	
	//TODO: nNpcEntityID�����ǿͻ�����Ϣ�ϱ��ģ�������Ϸ��ԡ�
	// ����npc���ж�
	CEntityNpc* tpEntity = dynamic_cast< CEntityNpc* >( CSceneObjManager::GetSingletonPtr( )->GetObject( nNpcEntityID ) );
	LK_ASSERT( tpEntity != NULL, return false  )
	if ( tpEntity->GetEntityType() != ENTITYTYPE_FUNCNPC )
	{
			return false;
	}

	// �����ж�
	CPropertyNPC * tpNpcProperty = ( CPropertyNPC * )tpEntity->GetProperty(); 
	CTemplateNpc *tpTmpNpc = ( CTemplateNpc * )CDataStatic::SearchTpl( tpNpcProperty->GetPropertyTempID() );
	LK_ASSERT( tpTmpNpc != NULL, return false )
	if ( tpTmpNpc->mFamilyService != eService )
	{
		return false;
	}
	
	// �����ж�
	return pPlayer->IsWithinDistance( tpEntity, MAX_NPC_TALK_GIRD );	
}

// ***********************************************************
//  Function:		DisbandFamily
//  Description:	��ɢ����
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::DisbandFamily( CEntityPlayer *pPlayer )
{

}

// ***********************************************************
//  Function:		GetAllFamilyInfo
//  Description:	��ȡ���м���Ļ�����Ϣ
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::GetAllFamilyInfo( CEntityPlayer *pPlayer )
{

}

// ***********************************************************
//  Function:		GetApplyList
//  Description:	��ȡ����������б�
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::GetApplyList( CEntityPlayer *pPlayer )
{

}

// ***********************************************************
//  Function:		OnMessageCreatFamily
//  Description:	�����������Ϣ
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::GetFamilyPropertyInfo( CEntityPlayer *pPlayer )
{

}

// ***********************************************************
//  Function:		GetFamilyMemberInfo
//  Description:	��ȡ����ĳ�Ա��Ϣ
//  Output:			
//  Date:	04/21/2009
// **********************************************************
CMemberInfo* CFamilyModule::GetFamilyMemberInfo( CEntityPlayer *pPlayer )
{
   return GetFamilyMemberInfo( pPlayer->GetFamilyID(), pPlayer->GetCharID() );
}

// ***********************************************************
//  Function:		InviteFamilyMember
//  Description:	������Ҽ������
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::InviteFamilyMember( CEntityPlayer *pPlayer, int vEntityID, const char *pName /* = NULL */ )
{

}

// ***********************************************************
//  Function:		KickFamilyMember
//  Description:	�߳������Ա
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::KickFamilyMember( CEntityPlayer *pPlayer, int PlayerCharID )
{

}

// ***********************************************************
//  Function:		LeaveFamily
//  Description:	����뿪����
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::LeaveFamily( CEntityPlayer *pPlayer )
{

}

// ***********************************************************
//  Function:		ReplyFamilyInvite
//  Description:	�ظ���������
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::ReplyFamilyInvite( CEntityPlayer *pPlayer, int Result, int FamilyID )
{

}

// ***********************************************************
//  Function:		ReplyMemberApply
//  Description:	����ҵ�����
//  Output:			
//  Date:	04/21/2009
// **********************************************************
void CFamilyModule::ReplyMemberApply( CEntityPlayer *pPlayer, int Result, int PlayerCharID )
{

} 

// ***********************************************************
//  Function:		OnGateMsg
//  Description:	�������ص���Ϣ
//  Output:			
//  Date:	04/30/2009
// **********************************************************
void CFamilyModule::OnGateMsg( CMessage *pMsg )
{ 
	LK_ASSERT( pMsg != NULL, return );


	// �������ط����Ĺ�����Ϣ
	switch ( pMsg->msghead().messageid() )
	{
	case ID_G2S_NOTIFY_FAMILYIDNAME:
		{
			OnMessageIDNameNotify( pMsg );
			return;
		}
	case ID_G2S_NOTIFY_NPCLIST:
		{
			OnMessageNpcListNotify( pMsg );
			return;
		}
	case ID_G2S_NOTIFY_BIDRESTART:
		{
			OnMessageBidRestartNotify( pMsg );
			return;
		}
	case ID_G2S_RESPONSE_BUYFAMILYITEM:
		{
			OnGateResponseBuyFamilyItem( pMsg );
			return;
		}
	case ID_G2S_RESPONSE_FAMILYEXCHANGE:
		{
			OnGateResponseFamilyExchange( pMsg );
			return;
		}
	case ID_G2S_RESPONSE_BATTLESTART:
		{
			return;
		} 
	default:
		break;
	}
	 
	// ��ȡ�������Ϣͷ
	Message* pUnknownMessage = (Message*)pMsg->msgpara();
	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessage->GetDescriptor();
	const ::google::protobuf::Reflection*  pReflection = pUnknownMessage->GetReflection();

	if (pDescriptor == NULL || pReflection == NULL) return; 
	const ::google::protobuf::FieldDescriptor*  pFieldDescriptor = pDescriptor->FindFieldByNumber(1);
	if (pFieldDescriptor == NULL) return; 
	if( pFieldDescriptor->type() != ::google::protobuf::FieldDescriptor::TYPE_MESSAGE  )
	{
		LOG_ERROR( "family", "[%s:%d] message %d is not family message", 
			__FUNCTION__, __LINE__, pMsg->msghead().messageid() );
		return ;
	}


	const Message& tFamilyHeader = pReflection->GetMessage( *pUnknownMessage, pFieldDescriptor ); 		
	FamilyHead* tpHead = ( FamilyHead* ) &tFamilyHeader;	
	
	// ��ȡ���
	CEntityPlayer *pPlayer = NULL;
	if ( tpHead->entityid() != 0 )
	{
		pPlayer = ( CEntityPlayer * )CSceneLogic::GetSingleton().GetEntity( tpHead->entityid() );
	}
	else
	{
		pPlayer = ( CEntityPlayer * )CSceneLogic::GetSingleton().GetPlayerByCharID( tpHead->roleid( ) );
	}							
	
	if( pPlayer == NULL ) 
	{
		LOG_ERROR( "family", "[%s:%d] in message %d can't find player by entityid %d or char id %d",
			__FUNCTION__, __LINE__, pMsg->msghead().messageid(), tpHead->entityid(), tpHead->roleid( ) );
		 return ;
	}
			
	switch ( pMsg->msghead().messageid() )
	{
		case ID_S2C_RESPONSE_CREATFAMILY:
		{
			OnGSCreatFamilyResponse( pPlayer, pMsg ); 			
			break;
		}
		case ID_S2C_RESPONSE_INVITEMEMBER:
		{
			OnGSIviteMemberResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIY_FAMILYINVITED:
		{
			OnGSFamilyInvitedNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_REPLYFAMILYINVITE:
		{
			OnGSReplyFamilyInviteResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_FAMILYAPPLY:
		{
			OnGSFamilyApplyResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIFY_MEMBERAPPLY:
		{
			OnGSMemberApplyNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_REPLYMEMBERAPPLY:
		{
			OnOnGSReplyMemberApplyResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIFY_FAMILYAPPLYSUCESS:
		{
			OnGSFamilyApplySucessNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIFY_FAMILYMEMBERADDED:
		{
			OnGSFamilyMemberAddedNotify( pPlayer, pMsg );
			break;
		}	
		case ID_S2C_NOTIFY_POSTAPPOINT:
		{
			OnGSPostAppointNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_LEAVEFAMILY:
		{
			OnGSLeaveFamilyResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIFY_MEMBERLEAVEFAMILY:
		{
			OnGSMemberLeaveFamilyNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_GETFAMILYMEMBERINFO:
		{
			OnGSGetFamilyMemberInfoResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_FAMILYPROPERTY:
		{
			OnGSFamilyPropertyResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_GETALLFAMILYINFO:
		{
			OnGSGetAllFamilyInfoResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_GETAPPLYLIST:
		{
			OnGSGetApplyListResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_KICKMEMBER:
		{
			OnGSKickMemberResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIFY_KICKPLAYER:
		{
			OnGSKickPlayerNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_DISBANDFAMILY:
		{
			OnGSDisbandFamilyResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIFY_DISBANDFAMILY:
		{
			OnGSDisbandFamilyNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_CHANGENOTICE:
		{
			OnGSChangeNoticeResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_APPOINTHEADER:
		{
			OnGSAppointHeaderResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIFY_CHANGERHEADER:
		{
			OnGSChangeHeaderNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIFY_FAMILYPEROPERTY:
		{
			OnGSFamilyPropertyNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIFY_INVITERESULT:
		{
			OnGSInviteMemberResultNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_CANCELFAMILYDISBAND:
		{
			OnGSCancelDisbandCorpsResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIFY_CHANGEFAMILYNOTICE:
		{
			OnGSChangeFamilyNoticeNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_CLEARFAMILYAPPLYLIST:
		{
			OnGSClearFamilyApplyListResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIFY_JOINCORPS:
		{
			OnGSJoinCorpsNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_REFRESHFAMILYINFO:
		{
			OnGSRefreshFamilyInfoResponse( pPlayer, pMsg );
			break;
		}
		
		case ID_S2C_RESPONSE_SETFAMILYMEMBERPOST:
		{
			OnGateMsgSetFamilyMemberPostResponse( pPlayer, pMsg );
			break;
		}		  		

		case ID_S2C_RESPONSE_LEVELUPFAMILY:
		{
			OnGateMsgLevelUPFamilyResponse( pPlayer, pMsg );
			break;
		}	
		
		case ID_S2C_RESPONSE_CONTRIBUTEFAMILYMONEY:
		{
			OnGateMsgContributeFamilyMoneyResponse( pPlayer, pMsg );
			break;	
		}
		
		case ID_S2C_RESPONSE_OBTAINFAMILYMONEY:
		{
			OnGateMsgObtainFamilyMoneyResponse( pPlayer, pMsg );
			break;	
		}	
		
		case ID_S2C_NOTIFY_SETFAMILYPOST:
		{
			OnGateMsgSetFamilyPostNotify( pPlayer, pMsg );
			break;	
		}	

		case ID_S2C_NOTIFY_LEVELUPFAMILY:
		{
			OnGateMsgLevelUPFamilyNotify( pPlayer, pMsg );
			break;	
		}	
		
		case ID_S2C_NOTIFY_FAMILYPVPSTARLEVELUP:	
		{
			OnGateMsgPVPStarLevelUPNotify( pPlayer, pMsg );
			break;	
		}
		case ID_S2C_RESPONSE_BIDNPC:
		{
			OnGSBidNpcResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_NOTIFY_MEMBERSUBMIT:
		{
			OnGSMemberSubmitNotify( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_MEMBERSUBMIT:
		{
			OnGSMemberSubmitResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_BIDINFO:
		{
			OnGSBidInfoResponse( pPlayer, pMsg );
			break;
		}

		case ID_S2C_RESPONSE_MAKEROOM:
		{
			OnGSMakeRoomResponse( pPlayer, pMsg );
			break;	
		}	

		case ID_S2C_RESPONSE_CHAROOM:
		{
			OnGSChaRoomResponse( pPlayer, pMsg );
			break;	
		}	

		case ID_S2C_RESPONSE_AGREEBATTLE:
		{
			OnGSAgreeBattleResponse( pPlayer, pMsg );
			break;	
		}	

		case ID_S2C_RESPONSE_QUERYALLROOM:	
		{
			OnGSQueryAllRoomResponse( pPlayer, pMsg );
			break;	
		}
		case ID_S2C_RESPONSE_QUERYMYROOM:
		{
			OnGSQueryMyRoomResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_QUERYMYCHA:
		{
			OnGSQueryMyChaResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_ABORTROOM:
		{
			OnGSAbortRoomResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_ABORTCHA:
		{
			OnGSAbortChaResponse( pPlayer, pMsg );
			break;
		}
		
		case ID_S2C_RESPONSE_STARTFAMILYBOSS:
		{
			OnGateMsgSetFamilyMemberPostResponse( pPlayer, pMsg );
			break;
		}				
		case ID_S2C_RESPONSE_QUERYNPCWELFARE:
		{
			OnGateMsgQueryNpcWelfareResponse( pPlayer, pMsg );
			break;
		}
		
		case ID_S2C_RESPONSE_GETFAMILYMONEY:
		{
			OnGateMsgGetFamilyMoney( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_GETEXPCARD:
		{
			OnGateMsgGetExpCard( pPlayer, pMsg );
			break;
		}	
		case ID_S2C_RESPONSE_POSTAPPOINT:
		{
			OnGSPostAppointResponse( pPlayer, pMsg );
			break;
		}			
		case ID_S2C_NOTIFY_MEMBERCONTRIBUTECHANGED:
		{
			OnGateNotifyFamilyContributeChanged( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_ENTERBOSSREPTION:
		{
			OnGateMsgEnterFamilyRepetion( pPlayer, pMsg );
			break;	
		}		
		case ID_S2C_RESPONSE_GETFAMILYGOODSLIST:
		{
			OnGateMsgGetFamilyGoodsListResponse( pPlayer, pMsg );
			break;
		}
		case ID_S2C_RESPONSE_GETFAMILYEXCHANGEGOODSLIST:
		{
			OnGateMsgGetFamilyExchangeGoodsListResponse( pPlayer, pMsg );
			break;
		}
		default:
			break;
	}
}

// ***********************************************************
//  Function:		OnGateMsg
//  Description:	�������ص���Ϣ
//  Output:			
//  Date:	04/30/2009
// **********************************************************
void CFamilyModule::SendToGate( void *pMsg, int MsgID, CEntityPlayer *pPlayer )
{  
	// TODO:
	Message* pUnknownMessage = (Message*) ( ( CMessage * )pMsg )->msgpara();
	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessage->GetDescriptor();
	const ::google::protobuf::Reflection*  pReflection = pUnknownMessage->GetReflection();

	if (pDescriptor == NULL || pReflection == NULL) return; 
	const ::google::protobuf::FieldDescriptor*  pFieldDescriptor = pDescriptor->FindFieldByNumber(1);
	if (pFieldDescriptor == NULL) return; 

	const Message& tFamilyHeader = pReflection->GetMessage( *pUnknownMessage, pFieldDescriptor ); 		
	FamilyHead* tpRouter = ( FamilyHead* ) &tFamilyHeader;	 				  
	tpRouter->set_entityid( pPlayer->GetEntityID() );
	tpRouter->set_msgid( MsgID );
	tpRouter->set_roleid( pPlayer->GetCharID() ); 
	
	CSceneLogic::GetSingleton().Send2Gate( ( CMessage * )pMsg );
}

// ***********************************************************
//  Function:	 OnGSAppointHeaderResponse
//  Description: ת������ְλ�Ļ�Ӧ��Ϣ	
//  Output:			
//  Date:		 05-04-2009
// **********************************************************
void CFamilyModule::OnGSAppointHeaderResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return )
	CMessageAppointHeaderResponse *tpMsg = ( CMessageAppointHeaderResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	 	
	if ( pPlayer == NULL )
	{
		return;
	}
	if ( tpMsg->errcode() == SUCCESS )
	{
		// pPlayer->SetIsFamilyHeader( false );
		CMemberInfo *tpMemberInfo = GetFamilyMemberInfo( pPlayer->GetFamilyID(), pPlayer->GetCharID() );
		if ( tpMemberInfo != NULL )
		{
			tpMemberInfo->mFamilyPost = FAMILY_POST_MEMEBER;
			tpMemberInfo->mFamilyHeaderID = tpMsg->playercharid();			
		}
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:		 OnGSChangeHeaderNotify
//  Description:	 �ı�������֪ͨ
//  Output:			
//  Date:			  05-04-2009
// **********************************************************
void CFamilyModule::OnGSChangeHeaderNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pMessage != NULL, return )
	CMessageChangeHeaderNotify *tpMsg = ( CMessageChangeHeaderNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return ) 	
	if ( pPlayer == NULL )
	{
		return;
	}			
	
	// �ı�ְλת�÷���ְλ
	if ( pPlayer->GetCharID() == tpMsg->playercharid() )
	{
		// pPlayer->SetIsFamilyHeader( true );
		CMemberInfo *tpMemberInfo = GetFamilyMemberInfo( pPlayer->GetFamilyID(), pPlayer->GetCharID() );
		if ( tpMemberInfo != NULL )
		{
			tpMemberInfo->mFamilyHeaderID = pPlayer->GetCharID();
			tpMemberInfo->mFamilyPost = FAMILY_POST_HEADER;
		}
	}
	   
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:	  OnGSChangeNoticeResponse
//  Description:  �޸Ĺ���Ļ�Ӧ��Ϣ	
//  Output:			
//  Date:		  05-04-2009
// **********************************************************
void CFamilyModule::OnGSChangeNoticeResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pMessage != NULL, return )
	CMessageChangeFamilyNoticeResponse *tpMsg = ( CMessageChangeFamilyNoticeResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:	 OnGSCreatFamilyResponse
//  Description: ���ش�����崴���Ļ�Ӧ	
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGSCreatFamilyResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pMessage != NULL, return ) ;	
	CMessageCreatFamilyResponse *tpMsg  = ( CMessageCreatFamilyResponse * )	pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );		
	
	// TODO:  
	LK_ASSERT( pPlayer != NULL, return );
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	pPlayer->SetFamilyID( 0 );
	tpProperty->SetMoney( tpProperty->GetMoney() + COST_CREATFAMILY );
	
	LOG_NOTICE( "family","[%s,%d][%s] Response of creat family:  player(roleid:%d) ", __LK_FILE__, __LINE__, __FUNCTION__, pPlayer->GetCharID() );
	if ( tpMsg->errcode() == SUCCESS )
	{		
		// ���ü���ID	 		
		pPlayer->SetFamilyID( tpMsg->familyid() );
				
		// ���ü�������
		//pPlayer->SetFamilyName( tpMsg->familyname().c_str() );
		
		// ��������
		// pPlayer->SetIsFamilyHeader( true );	
		
		// �۳���Ǯ
		if (CPropertyModule::GetSingleton().PlayerChangeMoney( pPlayer, COST_CREATFAMILY, true, False ) == SUCCESS)
		{
			LogEventLostMoneyByBuildFimaly(pPlayer, CYuanBao::em_unbind_money, COST_CREATFAMILY, tpMsg->familyid());
		}
		else
		{
			LOG_ERROR( "family","[%s,%d][%s] player ( roleid:%d) creat family(id:%d) Error at time(%d), change money Error ", __LK_FILE__, __LINE__, __FUNCTION__, pPlayer->GetCharID(), tpMsg->familyid(), time(NULL) );
		}
		
		// �����Ͻ���������Ϣ
		CMemberInfo tMemberInfo;
		tMemberInfo.mFamilyPost = FAMILY_POST_HEADER;
		tMemberInfo.mFamilyHeaderID = pPlayer->GetCharID();	
		tMemberInfo.mEntityID = pPlayer->GetEntityID();			
		InsertFamilyMember( pPlayer->GetCorpsID(), pPlayer->GetFamilyID(), pPlayer->GetCharID(), tMemberInfo, tpMsg->familyname().c_str(), NULL );
		
		// ����id������
		mNameList.insert( IDNameList::value_type( pPlayer->GetFamilyID(), lk::string<MAX_FAMILYNAME_LENGTH*MAX_UTF8_BYTES>( tpMsg->familyname().c_str() ) ) );
		
		LOG_NOTICE( "family","[%s,%d][%s] player ( roleid:%d) creat family(id:%d) sucess at time(%d) ", __LK_FILE__, __LINE__, __FUNCTION__, pPlayer->GetCharID(), tpMsg->familyid(), time(NULL) );
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:		  OnGSDisbandFamilyNotify
//  Description:	  ��ɢ�����֪ͨ
//  Output:			
//  Date:			  05-04-2009
// **********************************************************
void CFamilyModule::OnGSDisbandFamilyNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL && pPlayer != NULL, return )
	CMessageDisbandFamilyNotify *tpMsg = ( CMessageDisbandFamilyNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	

	DeleteFamilyInfo( pPlayer->GetFamilyID() );
	pPlayer->SetFamilyID( 0 );
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	tpProperty->SetLastTimeLeaveFamily( time(NULL) );
	pPlayer->SetCorpsID( 0 );
	//pPlayer->SetFamilyPost( -1 );
	//pPlayer->SetCorpsPost( -1 );
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:		OnGSDisbandFamilyResponse
//  Description:	��ɢ����Ļ�Ӧ��Ϣ
//  Output:			
//  Date:			05-04-2009
// **********************************************************
void CFamilyModule::OnGSDisbandFamilyResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pMessage != NULL, return )
	CMessageDisbandFamilyResponse *tpMsg = ( CMessageDisbandFamilyResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	if( pPlayer == NULL )
	{
		return;
	}	
	if ( tpMsg->errcode() == 0 )
	{
		// pPlayer->SetFamilyID( 0 );
		// CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
		// tpProperty->SetLastTimeLeaveFamily( time(NULL) );
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:	  OnGSFamilyApplyResponse
//  Description:  ����Ļظ���Ϣ	
//  Output:			
//  Date:		  05-04-2009
// **********************************************************
void CFamilyModule::OnGSFamilyApplyResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{							
	LK_ASSERT( pMessage != NULL && pPlayer != NULL, return )
	CMessageApplyFamilyResponse *tpMsg = ( CMessageApplyFamilyResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	if ( tpMsg->errcode() == 0 )
	{
		CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
		tpProperty->SetLastFamilyApplyTime( time( NULL ) );
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );	
}

// ***********************************************************
//  Function:		OnGSFamilyApplySucessNotify
//  Description:	����������Ľ��֪ͨ
//  Output:			
//  Date:			05-04-2009
// **********************************************************
void CFamilyModule::OnGSFamilyApplySucessNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pMessage != NULL, return )
	CMessageApplyFamilySuccessNotify *tpMsg = ( CMessageApplyFamilySuccessNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	if ( pPlayer == NULL )
	{
		return;
	}
	
	// ����ɹ�
	if ( tpMsg->result() == 1 )
	{
		pPlayer->SetFamilyID( tpMsg->familyid() );
		//if ( tpMsg->has_familyname() )
		/*{
			pPlayer->SetFamilyName( tpMsg->mutable_familyname()->c_str() );
		}*/
		pPlayer->SetCorpsID( tpMsg->corpsid() );
		/*if ( tpMsg->has_corpsname() )
		{
			pPlayer->SetCorpsName( tpMsg->mutable_corpsname()->c_str() );
		}*/
		if ( pPlayer->GetFamilyID() != 0 )
		{
			CMemberInfo tMemberInfo;
			tMemberInfo.mFamilyHeaderID = tpMsg->familyheader();
			tMemberInfo.mFamilyPost = FAMILY_POST_MEMEBER; 
			tMemberInfo.mEntityID = pPlayer->GetEntityID();
			InsertFamilyMember( pPlayer->GetCorpsID(), pPlayer->GetFamilyID(), pPlayer->GetCharID(), tMemberInfo, tpMsg->familyname().c_str(), tpMsg->corpsname().c_str() );
		}
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:	   OnGSFamilyInvitedNotify
//  Description:   ���ͱ���������֪ͨ��ʧ�ܻ��߳ɹ�
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGSFamilyInvitedNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pMessage != NULL, return )
	CMessageFamilyInvitedNotify *tpMsg = ( CMessageFamilyInvitedNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )		
	if( pPlayer != NULL )
	{
		SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
	}
}

// ***********************************************************
//  Function:	 OnGSFamilyMemberAddedNotify
//  Description: ���³�Ա�����֪ͨ	
//  Output:			
//  Date:		 05-04-2009
// **********************************************************
void CFamilyModule::OnGSFamilyMemberAddedNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pMessage != NULL, return )		
	CMessageFamilyMemberAddedNotify *tpMsg = ( CMessageFamilyMemberAddedNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if( pPlayer != NULL )
	{ 		
		SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
	}
}

// ***********************************************************
//  Function:	   OnGSFamilyPropertyNotify
//  Description:   �������Ըı��֪ͨ
//  Output:			
//  Date:		   05-04-2009
// **********************************************************
void CFamilyModule::OnGSFamilyPropertyNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{  
	LK_ASSERT( pMessage != NULL, return )
	CMessageFamilyPropertyNotify *tpMsg = ( CMessageFamilyPropertyNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:	  OnGSFamilyPropertyResponse
//  Description:  ��ȡ����������Ϣ�Ļ�Ӧ��Ϣ
//  Output:			
//  Date:		  05-04-2009
// **********************************************************
void CFamilyModule::OnGSFamilyPropertyResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pMessage != NULL, return )		
	CMessageGetFamilyPropertyResponse *tpMsg = ( CMessageGetFamilyPropertyResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );	
} 

// ***********************************************************
//  Function:	  OnGSGetAllFamilyInfoResponse
//  Description:  ��ȡ���м��������Ϣ�Ļ�Ӧ��Ϣ	
//  Output:			
//  Date:		  05-04-2009
// **********************************************************
void CFamilyModule::OnGSGetAllFamilyInfoResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pMessage != NULL, return )
	CMessageGetAllFamilyInfoResponse *tpMsg = ( CMessageGetAllFamilyInfoResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );	
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:		OnGSGetApplyListResponse
//  Description:	��ȡ�����б�
//  Output:			
//  Date:			05-04-2009
// **********************************************************
void CFamilyModule::OnGSGetApplyListResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pMessage != NULL, return )	
	CMessageGetApplyListResponse *tpMsg = ( CMessageGetApplyListResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:		OnGSGetFamilyMemberInfoResponse
//  Description:	��ȡ�����Ա��Ϣ�Ļ�Ӧ��Ϣ
//  Output:			
//  Date:			05-04-2009
// **********************************************************
void CFamilyModule::OnGSGetFamilyMemberInfoResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{  
	LK_ASSERT( pMessage != NULL, return );
	CMessageGetFamilyMemberInfoResponse *tpMsg = ( CMessageGetFamilyMemberInfoResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );	
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:	
//  Description:	
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGSIviteMemberResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return );
	CMessageInviteMemberResponse *tpMsg = ( CMessageInviteMemberResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );	
	if ( pPlayer != NULL )
	{
		SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
	}
}

// ***********************************************************
//  Function:		OnGSKickMemberResponse
//  Description:	�߳���ҵĻ�Ӧ��Ϣ
//  Output:			
//  Date:			05-04-2009
// **********************************************************
void CFamilyModule::OnGSKickMemberResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return )
	CMessageKickPlayerResponse *tpMsg = ( CMessageKickPlayerResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}																			 

// ***********************************************************
//  Function:		   OnGSKickPlayerNotify
//  Description:	   �߳���ҵ�֪ͨ
//  Output:			
//  Date:			   05-04-2009
// **********************************************************
void  CFamilyModule::OnGSKickPlayerNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pMessage != NULL, return )	
	CMessageKickPlayerNotify *tpMsg = ( CMessageKickPlayerNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if ( pPlayer == NULL )
	{
		return;
	}
	if ( pPlayer->GetCharID() == tpMsg->playercharid() )
	{
		DeleteFamilyMember( pPlayer->GetFamilyID(), pPlayer->GetCharID() );
		pPlayer->SetFamilyID( 0 );
		CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
		tpProperty->SetLastTimeLeaveFamily( time(NULL) );
		pPlayer->SetCorpsID( 0 );
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:	 OnGSLeaveFamilyResponse
//  Description: �뿪�������Ϣ��Ӧ	
//  Output:			
//  Date:		 05-04-2009
// **********************************************************
void CFamilyModule::OnGSLeaveFamilyResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pMessage != NULL, return )
	CMessageLeaveFamilyResponse *tpMsg =  ( CMessageLeaveFamilyResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	if ( pPlayer == NULL )
	{
		return;
	}
	if ( tpMsg->errcode() == SUCCESS )
	{
		DeleteFamilyMember( pPlayer->GetFamilyID(), pPlayer->GetCharID() );
		pPlayer->SetFamilyID( 0 );
		CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
		tpProperty->SetLastTimeLeaveFamily( time(NULL) );
		pPlayer->SetCorpsID( 0 );
		// pPlayer->SetFamilyPost( -1 );
		
		CPropertyModule::GetSingleton().ChangeTeamLeaverStatus( pPlayer );
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:	 OnGSMemberApplyNotify
//  Description: ����������������֪ͨ	
//  Output:			
//  Date:		 05-04-2009
// **********************************************************
void CFamilyModule::OnGSMemberApplyNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pMessage != NULL, return )
	CMessageMemberApplyNotify *tpMsg = ( CMessageMemberApplyNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	if ( pPlayer != NULL )
	{
		SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
	}
}

// ***********************************************************
//  Function:	  OnGSMemberLeaveFamilyNotify
//  Description:  �����Ա�뿪�����֪ͨ	
//  Output:			
//  Date:		   05-04-2009
// **********************************************************
void CFamilyModule::OnGSMemberLeaveFamilyNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pMessage != NULL, return )	
	CMessageMemberLeaveFamilyNotify *tpMsg = ( CMessageMemberLeaveFamilyNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:	 OnGSPostAppointNotify
//  Description: ְλ�������ļ���֪ͨ	
//  Output:			
//  Date:		 05-04-2009
// **********************************************************
void CFamilyModule::OnGSPostAppointNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pMessage != NULL, return )
	CMessagePostAppointNoify *tpMsg = ( CMessagePostAppointNoify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	if ( pPlayer == NULL )
	{
		return;
	}
	if ( tpMsg->playercharid() == pPlayer->GetCharID() )
	{
		CMemberInfo *tpMemberInfo = GetFamilyMemberInfo( pPlayer );
		if ( tpMemberInfo != NULL )
		{
			tpMemberInfo->mFamilyPost = tpMsg->actionkind();
		}
		//pPlayer->SetFamilyPost( tpMsg->actionkind() );
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ***********************************************************
//  Function:	
//  Description:	
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGSPostAppointResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessagePostAppointResponse *tpMsg  = ( CMessagePostAppointResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}

// ***********************************************************
//  Function:		OnGSReplyFamilyInviteResponse
//  Description:	�𸴼�������Ļ�Ӧ��Ϣ
//  Output:			
//  Date:			05-04-2009
// **********************************************************
void CFamilyModule::OnGSReplyFamilyInviteResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pMessage != NULL, return );
	CMessageReplyFamilyInviteResponse *tpMsg = ( CMessageReplyFamilyInviteResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	if ( pPlayer == NULL )
	{
		return;			
	}
	
	// ����ɹ�
	if ( tpMsg->errcode() == 0 && tpMsg->result() == FAMILY_REPLY_AGREE )
	{
		pPlayer->SetFamilyID( tpMsg->familyid() );
		/*if ( tpMsg->has_familyname() )
		{
			pPlayer->SetFamilyName( tpMsg->familyname().c_str() );
		}*/
		pPlayer->SetCorpsID( tpMsg->corpsid() );
		/*if ( tpMsg->has_corpsname() )
		{
			pPlayer->SetCorpsName( tpMsg->mutable_corpsname()->c_str() );
		}*/
		
		if ( pPlayer->GetFamilyID() != 0 )
		{
			CMemberInfo tMemberInfo;
			tMemberInfo.mFamilyHeaderID = tpMsg->has_familyheaderid();
			tMemberInfo.mFamilyPost = FAMILY_POST_MEMEBER;
			tMemberInfo.mEntityID = pPlayer->GetEntityID();
			InsertFamilyMember( pPlayer->GetCorpsID(), pPlayer->GetFamilyID(), pPlayer->GetCharID(), tMemberInfo, tpMsg->familyname().c_str(), tpMsg->corpsname().c_str() );
		}		
	}	
	else
	{
		pPlayer->SetFamilyID( 0 );	
	}						
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );	
}

// ***********************************************************
//  Function:	   OnOnGSReplyMemberApplyResponse
//  Description:   ���������Ļظ�
//  Output:			
//  Date:		   05-04-2009
// **********************************************************
void CFamilyModule::OnOnGSReplyMemberApplyResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return )	
	CMessageReplyMemberApplyResponse *tpMsg = ( CMessageReplyMemberApplyResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );	
	if( pPlayer != NULL )
	{
		SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
	}
}

// ***********************************************************
//  Function:	   OnGSInviteMemberResultNotify
//  Description:   ����Ľ��֪ͨ	 
//  Output:			
//  Date:			05-04-2009
// **********************************************************
void CFamilyModule::OnGSInviteMemberResultNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return )			
	CMessageInviteFamilyResultNotify *tpMsg = ( CMessageInviteFamilyResultNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )			
	if ( pPlayer == NULL )
	{						
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->msghead().messageid() );
}

// ***********************************************************
//  Function:	   OnGSCancelDisbandCorpsResponse
//  Description:   ȡ����ɢ�������Ϣ��Ӧ	 
//  Output:			
//  Date:			06-18-2009
// **********************************************************
void CFamilyModule::OnGSCancelDisbandCorpsResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )		
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}	 

// ***********************************************************
//  Function:	   OnGSClearFamilyApplyListResponse
//  Description:   ������������б����Ϣ��Ӧ	 
//  Output:			
//  Date:			06-22-2009
// **********************************************************
void CFamilyModule::OnGSClearFamilyApplyListResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}

// ***********************************************************
//  Function:	   OnGSChangeFamilyNoticeNotify
//  Description:   ���幫��ı��֪ͨ	 
//  Output:			
//  Date:			06-19-2009
// **********************************************************
void CFamilyModule::OnGSChangeFamilyNoticeNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}

// ***********************************************************
//  Function:	   OnGSRefreshFamilyInfoResponse
//  Description:   ˢ�¼�����Ϣ����Ϣ��Ӧ	 
//  Output:			
//  Date:			06-23-2009
// **********************************************************
void CFamilyModule::OnGSRefreshFamilyInfoResponse( CEntityPlayer *pPlayer, CMessage *pMessage ) 
{  
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}

// ***********************************************************
//  Function:	   OnGSJoinCorpsNotify
//  Description:   ���������ŵ�֪ͨ	 
//  Output:			
//  Date:			06-12-2009
// **********************************************************
void CFamilyModule::OnGSJoinCorpsNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageJoinCorpsNotify *tpMsg = ( CMessageJoinCorpsNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	pPlayer->SetCorpsID( tpMsg->corpsid() );
	if ( tpMsg->has_corpsname() )
	{
		// pPlayer->SetCorpsName( tpMsg->corpsname().c_str() );
		CFamilyInfo *tpFamilyInfo = GetFamilyInfo( pPlayer->GetFamilyID() );
		if ( tpFamilyInfo != NULL )
		{
			tpFamilyInfo->SetCorpsName( tpMsg->corpsname().c_str(), true );
			tpFamilyInfo->SetCorpsID( tpMsg->corpsid() );
		}
	}														
		
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}

// ***********************************************************
//  Function:	   OnGSInviteMemberResultNotify
//  Description:	
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::SendToClient( CEntityPlayer *pPlayer, void *pMsg, int MsgID )
{
	LK_ASSERT( pPlayer != NULL && pMsg != NULL, return );
	CMessage MsgHead;
	MsgHead.set_msgpara( (int)pMsg );
	MsgHead.mutable_msghead()->set_messageid( MsgID );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
}

// ***********************************************************
//  Function:	   OnMessageSetFamilyMemberPost
//  Description:	���ü����Աְλ����Ϣ����
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnMessageSetFamilyMemberPost( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageSetFamilyPostRequest *tpMsg = ( CMessageSetFamilyPostRequest * )pMessage->msgpara();
	if ( tpMsg == NULL )
	{
		return;
	}
	// ��ȫ������
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	int tPwdCheckRet = tpProperty->GetRolePassword()->CheckActionAllowed( EM_PASSWORD_ACTION_GAMEACTION );
	if ( tPwdCheckRet != SUCCESS )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, tPwdCheckRet );
		return;
	}	
	SenMsgToGate( pMessage, tpMsg, pPlayer )
}

// ***********************************************************
//  Function:	   OnMessageLevelUPFamily
//  Description:   �������������
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnMessageLevelUPFamily( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageLevelUPFamilyRequest *tpMsg = ( CMessageLevelUPFamilyRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	CMessage tMsgHead;
	CMessageLevelUPFamilyResponse tMsgLevelUPFamily;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_LEVELUPFAMILY );
	tMsgHead.set_msgpara( (int)&tMsgLevelUPFamily );
		 
	CMemberInfo *tpMemberInfo = GetFamilyMemberInfo( pPlayer );
	if ( tpMemberInfo == NULL )
	{	
		LOG_ERROR( "family","[%s,%d] cant not find family member info ( familyid:%d, roleid:%d )", __FUNCTION__,__LINE__, pPlayer->GetFamilyID(), pPlayer->GetCharID() );
		return;
	}
	
	if ( tpMemberInfo->mFamilyPost != FAMILY_POST_HEADER )
	{
		tMsgLevelUPFamily.set_errcode( ERROR_FAMILY_HASNORIGHT );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );		
		return;
	}
	
	/*if ( !pPlayer->GetIsFamilyHeader() )
	{
		tMsgLevelUPFamily.set_errcode( ERROR_FAMILY_HASNORIGHT );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );		
		return;
	}*/
	SenMsgToGate( pMessage, tpMsg, pPlayer )
}

// ***********************************************************
//  Function:	   OnMessageContributeFamilyMoney
//  Description:   ���׼����Ǯ����Ϣ����
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnMessageContributeFamilyMoney( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageContributeFamilyMoneyRequest *tpMsg = ( CMessageContributeFamilyMoneyRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )	pPlayer->GetProperty();
	if ( tpProperty->GetMoney() < (int)( tpMsg->money()*MONEY_EXCHANGERATE )
			|| (int)( tpMsg->money()*MONEY_EXCHANGERATE ) <= 0 )
	{
		CMessage tHead;
		CMessageContributeFamilyMoneyResponse tMsgContributeMoney;
		
		tHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_CONTRIBUTEFAMILYMONEY );
		tHead.set_msgpara( (int)&tMsgContributeMoney );
		
		tMsgContributeMoney.set_money( tpMsg->money() );
		tMsgContributeMoney.set_errcode( ERROR_FAMILY_CONTRIBUTEMONEY_NOTENOUGH );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &tHead );
		return;
	}
	
	// �ȿ۵���Ǯ������ʧ��ʱ�ٷ���		
	tpProperty->SetMoney( tpProperty->GetMoney() - tpMsg->money()*MONEY_EXCHANGERATE );	
	LOG_NOTICE( "family","[%s,%d] contribute money ( roleid:%d, money:%d, familyid:%d ) ", __FUNCTION__,__LINE__, pPlayer->GetCharID(), tpMsg->money(), pPlayer->GetFamilyID() );
	SenMsgToGate( pMessage, tpMsg, pPlayer );
}

// ***********************************************************
//  Function:	   OnMessageObtainFamilyMoney
//  Description:   ��ռ��npc����ȡ�����Ǯ����Ϣ����
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnMessageObtainFamilyMoney( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageObtainFamilyMoneyRequest *tpMsg = ( CMessageObtainFamilyMoneyRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// npc���ж�
	CEntityNpc *tpEntity =  dynamic_cast< CEntityNpc * >( CSceneObjManager::GetSingletonPtr()->GetObject( tpMsg->npcid() ) );
	LK_ASSERT( tpEntity != NULL, return )
	
	// ������
	if (  pPlayer->IsWithinDistance( tpEntity, MAX_NPC_TALK_GIRD ) == false )
	{
		return;
	}
	
	// ��ȡģ��ID
	CPropertyNPC * tpNpcProperty = ( CPropertyNPC * )tpEntity->GetProperty(); 		
	tpMsg->set_npctmpid( tpNpcProperty->GetPropertyTempID() );
	
	SenMsgToGate( pMessage, tpMsg, pPlayer )
}	

// ***********************************************************
//  Function:	  OnMessageStartFamilyBoss
//  Description:  ��������boss��֪ͨ
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnMessageStartFamilyBoss( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageStartFamilyBossRequest *tpMsg = ( CMessageStartFamilyBossRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	/*int tRet = CheckNpcFamilyService(  pPlayer, tpMsg->enityid(), FAMILYSERVICE_ACTIVITYNPC );
	LK_ASSERT( tRet != NULL, return )
	*/
	// ����ǲ����峤
	CMessage tMsgHead;
	CMessageStartFamilyBossResponse tMsgStartFamilyBoss;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_STARTFAMILYBOSS );
	tMsgHead.set_msgpara( (int)&tMsgStartFamilyBoss );
	
	if ( pPlayer->GetFamilyID() == 0 )
	{
		tMsgStartFamilyBoss.set_errcode( ERROR_FAMILY_FAMILYBOSS_HASNOFAMILY );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
		return;
	}	
	
	// TODO:����Ƿ���Խ�����帱��( �����ӿ� )
	CRepetionInfo *tpRepetionInfo = CRepetionModule::GetSingleton().GetRepetionInfoByMapID( FAMILYBOSS_MAP_ID );
	if ( tpRepetionInfo == NULL )
	{
		return;
	}	
	//if ( !tpRepetionInfo->IsInOpenTime() )
	//{
	//	tMsgStartFamilyBoss.set_errcode( ERROR_FAMILY_FAMILYBOSS_NOTINOPENTIME );
	//	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
	//	return;
	//}	
	//
	//tpMsg->set_date( CSceneLogic::GetSingletonPtr()->GetCurrentDay() );
	//
	//if ( CSceneCfgManager::GetSingleton().GetRepetion_cfg()->mNumcheck == 0 )
	//{
	//	tpMsg->set_maxtimes( 0 );
	//}
	//else
	//{
	//	tpMsg->set_maxtimes( tpRepetionInfo->GetPlayerPerNumber() );
	//}
	
																		 
	// ��������
	SenMsgToGate( pMessage, tpMsg, pPlayer );
}

// ***********************************************************
//  Function:	  OnMessageGetFamilyExpCard
//  Description:  ��ȡ���徭�����Ƶ���Ϣ����
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnMessageGetFamilyExpCard( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageGetExpCardRequest *tpMsg = ( CMessageGetExpCardRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	/*if ( !pPlayer->GetIsFamilyHeader() )
	{
		CMessage tMsgHead;
		CMessageGetExpCardResponse tMsgGetExpCard; 		
		tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_GETEXPCARD );
		tMsgHead.set_msgpara( (int)&tMsgGetExpCard );		
		tMsgGetExpCard.set_errcode( ERROR_FAMILY_HASNORIGHT );		
		return;
	}*/
	SenMsgToGate( pMessage, tpMsg, pPlayer )
}

// ***********************************************************
//  Function:	   OnMessageQueryFamilyWelfare
//  Description:   ��ѯ���帣��
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnMessageQueryFamilyWelfare( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageQueryNpcWelfareRequest *tpMsg = ( CMessageQueryNpcWelfareRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// npc���ж�
	CEntityNpc *tpEntity =  dynamic_cast< CEntityNpc * >( CSceneObjManager::GetSingletonPtr()->GetObject( tpMsg->entityid() ) );
	LK_ASSERT( tpEntity != NULL, return )

	// ������
	if (  pPlayer->IsWithinDistance( tpEntity, MAX_NPC_TALK_GIRD ) == false )
	{
		return;
	}
	
	// ��ȡģ��ID
	CPropertyNPC * tpNpcProperty = ( CPropertyNPC * )tpEntity->GetProperty(); 	
	tpMsg->set_npctmpid( tpNpcProperty->GetPropertyTempID() );		
	
	SenMsgToGate( pMessage, tpMsg, pPlayer ) 
}

// ***********************************************************
//  Function:	   OnMessageGetFamilyMoney
//  Description:   ��ȡ�����Ǯ������
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnMessageGetFamilyMoney( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageGetFamilyMoneyRequest *tpMsg = ( CMessageGetFamilyMoneyRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	CMessage tMsgHead;
	CMessageGetFamilyMoneyResponse tMsgGetFamilyMoney;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_GETFAMILYMONEY );
	tMsgHead.set_msgpara( (int)&tMsgGetFamilyMoney );  	
	
	/*if ( !pPlayer->GetIsFamilyHeader() )
	{		
	   tMsgGetFamilyMoney.set_errcode( ERROR_FAMILY_HASNORIGHT );
	   CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
	   return;
	}*/	
		
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	if ( tpMsg->familymoney() < 0 || ( unsigned int )( tpMsg->familymoney()*MONEY_EXCHANGERATE + tpProperty->GetMoney() ) > (unsigned int)MONEY_LIMIT )
	{
		tMsgGetFamilyMoney.set_errcode( ERROR_FAMILY_GETMONEY_MONEYINVALIDE );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
		return;
	}
	
	SenMsgToGate( pMessage, tpMsg, pPlayer )
}		

// ***********************************************************
//  Function:	   OnGateMsgSetFamilyMemberPostResponse
//  Description:   ���ü����Աְλ����Ϣ��Ϣ��Ӧ
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGateMsgSetFamilyMemberPostResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}

// ***********************************************************
//  Function:	   OnGateMsgLevelUPFamilyResponse
//  Description:   ��������Ļ�Ӧ
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGateMsgLevelUPFamilyResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );	
}

// ***********************************************************
//  Function:	   OnGateMsgContributeFamilyMoneyResponse
//  Description:   ���׼����Ǯ����Ϣ��Ӧ
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGateMsgContributeFamilyMoneyResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageContributeFamilyMoneyResponse *tpMsg = ( CMessageContributeFamilyMoneyResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	tpProperty->SetMoney( tpProperty->GetMoney() + tpMsg->money()*MONEY_EXCHANGERATE );	
	if ( tpMsg->errcode() == SUCCESS )
	{			
		if (CPropertyModule::GetSingleton().PlayerChangeMoney( pPlayer, tpMsg->money( )*MONEY_EXCHANGERATE, true, false ) == SUCCESS)
		{
			LogEventLostMoneyByContrFimaly(pPlayer, CYuanBao::em_unbind_money, tpMsg->money( )*MONEY_EXCHANGERATE, pPlayer->GetFamilyID());
			LOG_NOTICE( "family", "[%s,%d] Contribute money success (  roleid:%d, familyid:%d, money:%d )  ",  __FUNCTION__, __LINE__,  pPlayer->GetCharID(), pPlayer->GetFamilyID(), tpMsg->money() );
		}
		else
		{
			tpProperty->SetMoney( tpProperty->GetMoney() - tpMsg->money()*MONEY_EXCHANGERATE );	
			LOG_ERROR( "family","[%s,%d] change contribute money failed ( roleid:%d, family:%d, money:%d ) ",  __FUNCTION__, __LINE__, pPlayer->GetCharID(), pPlayer->GetFamilyID(), tpMsg->money() );
		}																   
	}	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage ); 
}

// ***********************************************************
//  Function:	   OnGateMsgObtainFamilyMoneyResponse
//  Description:   ��ռ��npc����ȡ�����Ǯ����Ϣ��Ӧ
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGateMsgObtainFamilyMoneyResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}

// ***********************************************************
//  Function:	   OnGateMsgSetFamilyPostNotify
//  Description:   ���ü���ְλ��֪ͨ
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGateMsgSetFamilyPostNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
}

// ***********************************************************
//  Function:	   OnGateMsgLevelUPFamily
//  Description:   ����������֪ͨ
//  Output:			
//  Date:	
// **********************************************************	
void CFamilyModule::OnGateMsgLevelUPFamilyNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}

// ***********************************************************
//  Function:	  OnGateMsgLevelUPFamily
//  Description:  ����������֪ͨ
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGateMsgPVPStarLevelUPNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
}

// ***********************************************************
//  Function:	  OnGateMsgStartFamilyBossResponse
//  Description:  ��������boss��Ļ�Ӧ��Ϣ
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGateMsgStartFamilyBossResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageStartFamilyBossResponse *tpMsg = ( CMessageStartFamilyBossResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
	
	// ������Կ��������ͽ��븱����֪ͨ
	/*if ( tpMsg->errcode() == SUCCESS )
	{
		
	}*/
}

// ***********************************************************
//  Function:	  OnGateMsgQueryNpcWelfareNotify
//  Description:  ��ѯ����npc����
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGateMsgQueryNpcWelfareResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}

// ***********************************************************
//  Function:	  OnGateMsgGetFamilyMoney
//  Description:  ��ȡ�����Ǯ
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::OnGateMsgGetFamilyMoney( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageGetFamilyMoneyResponse *tpMsg = ( CMessageGetFamilyMoneyResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if ( tpMsg->errcode() == SUCCESS )
	{
		if (CPropertyModule::GetSingleton().PlayerChangeMoney( pPlayer, 
					tpMsg->familymoney()*MONEY_EXCHANGERATE, false, false ) == SUCCESS)		
		{
			LogEventGetMoneyByFamily(pPlayer, CYuanBao::em_unbind_money, tpMsg->familymoney()*MONEY_EXCHANGERATE, pPlayer->GetFamilyID());
			LOG_NOTICE( "family","[%s,%d] player get money from family ( roleid:%d, familyid:%d, money:%d )", __FUNCTION__, __LINE__, pPlayer->GetCharID(), pPlayer->GetFamilyID(), tpMsg->familymoney() );
		}
		else
		{
			LOG_ERROR( "family","[%s,%d] Get family money error ( roleid:%d, familyid:%d, money:%d ) ", __FUNCTION__, __LINE__, pPlayer->GetCharID(), pPlayer->GetFamilyID(), tpMsg->familymoney() );
		}
	}
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}


// ***********************************************************
//  Function:	  AddPlayerContribute
//  Description:  ������ҵĹ��׶�
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::AddPlayerFamilyContribute( int nRoleID, int nContribute, int nAddType /* = 0 */ )
{
	CMessage tMsgHead;
	CMessageChangeFamilyContributeNotify tMsgChangeContribute;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2G_NOTIFY_CHANGEFAMILYCONTRIBUTE );	
	tMsgHead.set_msgpara( (int)&tMsgChangeContribute );
	
	tMsgChangeContribute.set_roleid( nRoleID );
	tMsgChangeContribute.set_contribute( nContribute );
	tMsgChangeContribute.set_changetype( nAddType );
	
	CSceneLogic::GetSingleton().Send2Gate( &tMsgHead );
}

// ***********************************************************
//  Function:	  ChangeFamilyMoney
//  Description:  �ı�����Ǯ
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::ChangeFamilyMoney( CEntityPlayer *pPlayer, int nMoney, bool bPayOut /* = false */, int nReason /* = REASON_TASK */ )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageChangeFamilyMoneyNotify tMsgChangeFamilyMoney;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2G_NOTIFY_CHANGEFAMILYMONEY );
	tMsgHead.set_msgpara( (int)&tMsgChangeFamilyMoney );
	
	tMsgChangeFamilyMoney.set_familyid( pPlayer->GetFamilyID() );
	tMsgChangeFamilyMoney.set_ifpayout( bPayOut );
	tMsgChangeFamilyMoney.set_money( nMoney ); 
	tMsgChangeFamilyMoney.set_roleid( pPlayer->GetCharID() );
	tMsgChangeFamilyMoney.set_reason( nReason );
	tMsgChangeFamilyMoney.set_rolename( pPlayer->GetCharName() );	
		
	CSceneLogic::GetSingleton().Send2Gate( &tMsgHead );
}

// ***********************************************************
//  Function:	  ChangeFamilyGlory
//  Description:  �ı������ҫֵ
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::ChangeFamilyGlory( CEntityPlayer *pPlayer, int nValue, int bReduced /* = false */, int nReason /* = REASON_TASK */ )
{  
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageChangeFamilyGloryNotify tMsgChangeFamilyGlory;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2G_NOTIFY_CHANGEFAMILYGLORY );		
	tMsgHead.set_msgpara( (int)&tMsgChangeFamilyGlory );
	
	tMsgChangeFamilyGlory.set_familyid( pPlayer->GetFamilyID() );
	tMsgChangeFamilyGlory.set_glory( nValue );
	tMsgChangeFamilyGlory.set_ifreduced( bReduced ); 
	tMsgChangeFamilyGlory.set_roleid( pPlayer->GetCharID() );
	tMsgChangeFamilyGlory.set_reason( nReason );
	tMsgChangeFamilyGlory.set_rolename( pPlayer->GetCharName() );	
		
	CSceneLogic::GetSingleton().Send2Gate( &tMsgHead );
}

// ***********************************************************
//  Function:	  ChangeFamilyStability
//  Description:  �ı���尲����
//  Output:			
//  Date:	
// **********************************************************
void CFamilyModule::ChangeFamilyStability( CEntityPlayer *pPlayer, int nValue, int nReason /* = REASON_TASK */, int nParam1 /* = 0 */, int nParam2 /* = 0 */ )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageChangeFamilyStabilityNotify tMsgStability;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2G_NOTIFY_CHANGEFAMILYSTABILITY );
	tMsgHead.set_msgpara( (int)&tMsgStability );
	
	tMsgStability.set_reason( nReason );
	tMsgStability.set_roleid( pPlayer->GetCharID() );
	tMsgStability.set_rolename( pPlayer->GetCharName() );
	tMsgStability.set_familyid( pPlayer->GetFamilyID() );
	tMsgStability.set_value( nValue );
		
	switch( nReason )		
	{
		case REASON_ONLINETIME:
		{
			tMsgStability.set_rolelevel( nParam1 );
			tMsgStability.set_onlinetime( nParam2 );
			break;
		}	
	}
	
	CSceneLogic::GetSingleton().Send2Gate( &tMsgHead );
}

void CFamilyModule::OnMessageIDNameNotify( CMessage *pMessage )
{  
	LK_ASSERT( pMessage != NULL, return );
	CMessageFamilyIDNameNotify *tpMsg = ( CMessageFamilyIDNameNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	for ( int i = 0; i < tpMsg->familyid_size() && i < tpMsg->familyname_size(); i++ )
	{
		mNameList.insert( IDNameList::value_type( tpMsg->familyid( i ), lk::string<MAX_FAMILYNAME_LENGTH*MAX_UTF8_BYTES>( tpMsg->familyname( i ).c_str( ) ) ) );
		LOG_NOTICE( "family", "%d - %s", tpMsg->familyid( i ), tpMsg->familyname( i ).c_str( ) );
	}	
}

void CFamilyModule::OnMessageNpcListNotify( CMessage *pMessage )
{  
	LK_ASSERT( pMessage != NULL, return );	
	CMessageNpcListNotify *tpMsg = ( CMessageNpcListNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
		
	if ( tpMsg->type() == TYPE_FAMILY )
	{
		for ( int i = 0; i < tpMsg->npcid_size() && i < tpMsg->familyid_size(); i++ )
		{
			NPCList::iterator it = mNpcList.find( tpMsg->npcid( i ) );
			if ( it != mNpcList.end() )
			{ 
				mNpcList.erase( it );
			}
			mNpcList.insert( NPCList::value_type( tpMsg->npcid( i ), tpMsg->familyid( i ) ) );
			LOG_NOTICE( "family", "familylist %d, %d", tpMsg->npcid( i ), tpMsg->familyid( i ) );
		}	
	}
	else if ( tpMsg->type() == TYPE_CORPS )
	{
		CCorpsModule::GetSingleton().InsertNpcList( tpMsg );
	}
}

void CFamilyModule::OnMessageBidRestartNotify( CMessage *pMessage )
{  
	LK_ASSERT( pMessage != NULL, return );	
	CMessageBidRestartNotify *tpMsg = ( CMessageBidRestartNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	CActivityModule::GetSingletonPtr()->DebugBattleEnd( tpMsg->npcid() );
}

char* CFamilyModule::GetFamilyName( int vFamilyID )
{
	IDNameList::iterator it = mNameList.find( vFamilyID );
	if ( it != mNameList.end() )
	{
		return (char*)(it->second.c_str());
	}
	return NULL;
}

int CFamilyModule::GetFamilyIDByNpcID( int vNpcID )
{
	NPCList::iterator it = mNpcList.find( vNpcID );
	if ( it != mNpcList.end() )
	{
		return it->second;
	}
	return 0;
}

void CFamilyModule::OnMessageBidNpc( CEntityPlayer *pPlayer, CMessage *pMessage )
{  
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageFamilyBidNpcRequest *tpMsg = ( CMessageFamilyBidNpcRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	
	CTemplateNpc *tplNpc = (CTemplateNpc*)CDataStatic::SearchTpl( tpMsg->npcid() );
	if ( tplNpc == NULL )
	{
		return;
	}
	// ������ܾ���
	if ( CActivityModule::GetSingleton().CanBidNpc( tplNpc->mTempID ) == false )
	{
		//LK_ASSERT( tpMsg->has_headmsg(), return );
		//FamilyHead *tpHead = tpMsg->mutable_headmsg();
		CMessage tMsgHead;
		CMessageFamilyBidNpcResponse tMsgResponse;

		/*tMsgResponse.mutable_headmsg()->set_roleid( tpHead->roleid() );	
		if ( tpHead->entityid() != 0 )
		{
			tMsgResponse.mutable_headmsg()->set_entityid( tpHead->entityid() );
		}*/
		tMsgResponse.set_result( ERROR_FAMILY_BIDNPC_WRONGTIME );
		tMsgResponse.set_npcid( tpMsg->npcid() );
		tMsgResponse.set_money( tpMsg->money() );

		tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_BIDNPC );
		tMsgHead.set_msgpara( (int)&tMsgResponse );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
		return;
	}
	// �����Ǯ����
	/*if ( pPlayer->GetMoney() < tpMsg->money() )
	{
		LK_ASSERT( tpMsg->has_headmsg(), return )
		FamilyHead *tpHead = tpMsg->mutable_headmsg();
		CMessage tMsgHead;
		CMessageFamilyBidNpcResponse tMsgResponse;

		tMsgResponse.mutable_headmsg()->set_roleid( tpHead->roleid() );	
		if ( tpHead->entityid() != 0 )
		{
			tMsgResponse.mutable_headmsg()->set_entityid( tpHead->entityid() );
		}
		tMsgResponse.set_npcid( tpMsg->npcid() );
		tMsgResponse.set_money( tpMsg->money() );

		tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_BIDNPC );
		tMsgHead.set_msgpara( (int)&tMsgResponse );
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
	}*/
	SenMsgToGate( pMessage, tpMsg, pPlayer ); 
}

void CFamilyModule::OnGSBidNpcResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return )
	CMessageFamilyBidNpcResponse *tpMsg = ( CMessageFamilyBidNpcResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if ( pPlayer == NULL )
	{
		return;
	}
	/*if ( tpMsg->result() == SUCCESS )
	{
		CPropertyModule::GetSingletonPtr()->PlayerChangeMoney( pPlayer, tpMsg->money()*10000, true, false );
	}*/
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

void CFamilyModule::OnGSMemberSubmitNotify( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return )
	CMessageMemberSubmitNotify *tpMsg = ( CMessageMemberSubmitNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

void CFamilyModule::OnGSMemberSubmitResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return )
	CMessageMemberSubmitResponse *tpMsg = ( CMessageMemberSubmitResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ��ȡ�����ڵ��Ļ�Ӧ��Ϣ
void CFamilyModule::OnGateMsgGetExpCard( CEntityPlayer *pPlayer, CMessage *pMessage )
{  
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageGetExpCardResponse *tpMsg = ( CMessageGetExpCardResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if ( tpMsg->errcode() == SUCCESS )
	{
		CPropertyModule::GetSingleton().CreatFamilyRedStone( pPlayer, tpMsg->redstoneid() );
	}
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}

// ��ҹ��׶ȸı����Ϣ
void CFamilyModule::OnGateNotifyFamilyContributeChanged( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageMemberContributeChangedNotify *tpMsg = ( CMessageMemberContributeChangedNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	if ( tpMsg->roleid() == pPlayer->GetCharID() )
	{	
		CMemberInfo *tpMemberInfo = GetFamilyMemberInfo( pPlayer );				
		if ( tpMemberInfo != NULL )
		{
			tpMemberInfo->mFamilyContribute = tpMsg->contribute();
		}
		// pPlayer->SetFamilyContribute( tpMsg->contribute() );	
	}
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );			
}

void CFamilyModule::OnMessageMemberSubmit( CEntityPlayer *pPlayer, CMessage *pMessage )
{  
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageMemberSubmitRequest *tpMsg = ( CMessageMemberSubmitRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	
	CTemplateNpc *tplNpc = (CTemplateNpc*)CDataStatic::SearchTpl( tpMsg->npcid() );
	if ( tplNpc == NULL )
	{
		return;
	}
	SenMsgToGate( pMessage, tpMsg, pPlayer ); 
}

void CFamilyModule::SendBattleEndNotify( KEY_TYPE vKey, int vWinSide )
{
	CMessage tMsgHead;
	CMessageBattleEndNotify tpMsg;

	tpMsg.set_key( vKey );
	tpMsg.set_winside( vWinSide );

	tMsgHead.mutable_msghead()->set_messageid( ID_S2G_NOTIFY_BATTLEEND );
	tMsgHead.set_msgpara( (int)&tpMsg );

	CSceneLogic::GetSingletonPtr()->Send2Gate( &tMsgHead );
}

void CFamilyModule::OnMessageBidInfo( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageBidInfoRequest *tpMsg = ( CMessageBidInfoRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	
	CTemplateNpc *tplNpc = (CTemplateNpc*)CDataStatic::SearchTpl( tpMsg->npcid() );
	if ( tplNpc == NULL )
	{
		return;
	}
	SenMsgToGate( pMessage, tpMsg, pPlayer ); 
}

void CFamilyModule::OnGSBidInfoResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return )
	CMessageBidInfoResponse *tpMsg = ( CMessageBidInfoResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

void CFamilyModule::OnMessageAbortNpc( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageAbortNpcRequest *tpMsg = ( CMessageAbortNpcRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	
	SenMsgToGate( pMessage, tpMsg, pPlayer ); 
}

void CFamilyModule::OnGSAbortNpcResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return )
	CMessageAbortNpcResponse *tpMsg = ( CMessageAbortNpcResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}


// �����跿����Ϣ
void CFamilyModule::OnMessageMakeRoom( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageMakeRoomRequest *tpMsg = ( CMessageMakeRoomRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );

	SenMsgToGate( pMessage, tpMsg, pPlayer ); 
}

// ������ս������Ϣ
void CFamilyModule::OnMessageChaRoom( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageChaRoomRequest *tpMsg = ( CMessageChaRoomRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );

	SenMsgToGate( pMessage, tpMsg, pPlayer ); 
}

// ����ͬ����ս��Ϣ
void CFamilyModule::OnMessageAgreeBattle( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageAgreeBattleRequest *tpMsg = ( CMessageAgreeBattleRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );

	SenMsgToGate( pMessage, tpMsg, pPlayer );
}

// �����ѯ�����б���Ϣ
void CFamilyModule::OnMessageQueryAllRoom( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageQueryAllRoomRequest *tpMsg = ( CMessageQueryAllRoomRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );

	SenMsgToGate( pMessage, tpMsg, pPlayer );
}

// �����ѯ�Լ��ķ�����Ϣ
void CFamilyModule::OnMessageQueryMyRoom( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageQueryMyRoomRequest *tpMsg = ( CMessageQueryMyRoomRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );

	SenMsgToGate( pMessage, tpMsg, pPlayer );
}

// �����ѯ�Լ�����ս��Ϣ
void CFamilyModule::OnMessageQueryMyCha( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageQueryMyChaRequest *tpMsg = ( CMessageQueryMyChaRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );

	SenMsgToGate( pMessage, tpMsg, pPlayer );
}

// �������������Ϣ
void CFamilyModule::OnMessageAbortRoom( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageAbortRoomRequest *tpMsg = ( CMessageAbortRoomRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );

	SenMsgToGate( pMessage, tpMsg, pPlayer );
}

// ���������ս��Ϣ
void CFamilyModule::OnMessageAbortCha( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageAbortChaRequest *tpMsg = ( CMessageAbortChaRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );

	SenMsgToGate( pMessage, tpMsg, pPlayer );
}

// ���跿���Ӧ
void CFamilyModule::OnGSMakeRoomResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return );
	CMessageMakeRoomResponse *tpMsg = ( CMessageMakeRoomResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ��ս�����Ӧ
void CFamilyModule::OnGSChaRoomResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return );
	CMessageChaRoomResponse *tpMsg = ( CMessageChaRoomResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ͬ����ս��Ӧ
void CFamilyModule::OnGSAgreeBattleResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return );
	CMessageAgreeBattleResponse *tpMsg = ( CMessageAgreeBattleResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ��ѯ�����б��Ӧ
void CFamilyModule::OnGSQueryAllRoomResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return );
	CMessageQueryAllRoomResponse *tpMsg = ( CMessageQueryAllRoomResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ��ѯ�Լ��ķ����Ӧ
void CFamilyModule::OnGSQueryMyRoomResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return );
	CMessageQueryMyRoomResponse *tpMsg = ( CMessageQueryMyRoomResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ��ѯ�Լ�����ս��Ӧ
void CFamilyModule::OnGSQueryMyChaResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return );
	CMessageQueryMyChaResponse *tpMsg = ( CMessageQueryMyChaResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ���������Ӧ
void CFamilyModule::OnGSAbortRoomResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return );
	CMessageAbortRoomResponse *tpMsg = ( CMessageAbortRoomResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}

// ������ս��Ӧ
void CFamilyModule::OnGSAbortChaResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return );
	CMessageAbortChaResponse *tpMsg = ( CMessageAbortChaResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	if ( pPlayer == NULL )
	{
		return;
	}
	SendToClient( pPlayer, tpMsg, pMessage->mutable_msghead()->messageid() );
}


// ***********************************************************
//  Function:		InsertFamilyMember
//  Description:	����һ����ҵ���Ϣ
//  Output:			
//  Date:			09/03/2009
// **********************************************************
int CFamilyModule::InsertFamilyMember( int nCorpsID, int nFamilyID, int nRoleID, CMemberInfo &rMemberInfo, const char *pFamilyName /* = NULL */, const char *pCorpsName /* = NULL */ )
{
	FamilyList::iterator it = mFamilyList.find( nFamilyID );
	if ( it == mFamilyList.end() )
	{								
		// ����һ���µļ�����Ϣ
		CFamilyInfo *tpFamilyInfo = ( CFamilyInfo * )CSceneObjManager::GetSingleton().CreateObject( OBJTYPE_FAMILYINFO );
		LK_ASSERT( tpFamilyInfo != NULL, return -1 )	
	
		tpFamilyInfo->InsertMember( nRoleID, rMemberInfo );
		tpFamilyInfo->SetCorpsID( nCorpsID );
		if ( pFamilyName != NULL )
		{
			tpFamilyInfo->SetFamilyName( pFamilyName );
		}
		
		if ( pCorpsName != NULL )
		{
			tpFamilyInfo->SetCorpsName( pCorpsName );
		}
		
		mFamilyList.insert( FamilyList::value_type( nFamilyID, tpFamilyInfo->get_id() ) );
	}
	else
	{
		CFamilyInfo *tpFamilyInfo = ( CFamilyInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		LK_ASSERT( tpFamilyInfo != NULL, return -1 )		
		int tRet = tpFamilyInfo->InsertMember( nRoleID, rMemberInfo );
		if ( tRet == -1 )
		{
			LOG_ERROR( "family","[%s,%d] insert family member error, familyid:%d ",__FUNCTION__,__LINE__, nFamilyID );
		}
		tpFamilyInfo->SetCorpsID( nCorpsID );
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		DeleteFamilyMember
//  Description:	ɾ��һ����ҵ���Ϣ
//  Output:			
//  Date:			09/03/2009
// **********************************************************
int CFamilyModule::DeleteFamilyMember( int nFamilyID, int nRoleID )
{
	FamilyList::iterator it = mFamilyList.find( nFamilyID );
	if ( it != mFamilyList.end() )
	{
		CFamilyInfo *tpFamilyInfo = ( CFamilyInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		LK_ASSERT( tpFamilyInfo != NULL, return -1 )
		tpFamilyInfo->DeleteMember( nRoleID );		
		if ( tpFamilyInfo->GetMemberNum() == 0 )
		{
			CSceneObjManager::GetSingleton().DestroyObject( it->second );
			mFamilyList.erase( it );  
		}	  								
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetFamilyMemberList
//  Description:	��ȡĳ������������Ϣ�б�
//  Output:			
//  Date:			09/03/2009
// ***********************************************************
int CFamilyModule::GetFamilyMemberList( int nFamilyID, int *pIDList, int &rNum )
{
	FamilyList::iterator it = mFamilyList.find( nFamilyID );
	if ( it != mFamilyList.end() )
	{
		CFamilyInfo *tpFamilyInfo = ( CFamilyInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		LK_ASSERT( tpFamilyInfo != NULL, return -1 )
		tpFamilyInfo->GetMemberList( pIDList, rNum );	
	}
	else
	{
		rNum = 0;
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		DeleteFamilyInfo
//  Description:	ɾ��������Ϣ( ��ɢ�����ʱ�� )
//  Output:			
//  Date:			09/03/2009
// ***********************************************************
int CFamilyModule::DeleteFamilyInfo( int nFamilyID )
{  
	FamilyList::iterator it = mFamilyList.find( nFamilyID );
	if ( it != mFamilyList.end() )
	{
		CSceneObjManager::GetSingleton().DestroyObject( it->second );
		mFamilyList.erase( it );
	}
	return SUCCESS;	
}

// ***********************************************************
//  Function:		GetCorpsMemberList
//  Description:	��ȡ��������������ĳ�����ŵĳ�Ա�б�
//  Output:			
//  Date:			09/04/2009
// ***********************************************************
int CFamilyModule::GetCorpsMemberList( int nCorpsID, int *pIDList, int &rNum )
{
	LK_ASSERT( pIDList != NULL, return -1 )
	int tNum = rNum;
	rNum = 0;
	FamilyList::iterator it = mFamilyList.begin();
	for ( ; it != mFamilyList.end(); ++it )
	{
		CFamilyInfo *tpFamilyInfo = ( CFamilyInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		LK_ASSERT( tpFamilyInfo != NULL, continue )
		if ( tpFamilyInfo->GetCorpsID() == nCorpsID )
		{
			int tListNum = tNum - rNum;
			tpFamilyInfo->GetMemberList( pIDList, tListNum );
			rNum += tListNum;
		}						
	}
	return SUCCESS;
} 

// ***********************************************************
//  Function:		GetFamilyAverageLevel
//  Description:	��ȡ�����ڵ�ǰ������������������ҵ�ƽ���ȼ�
//  Output:			
//  Date:			09/09/2009
// ***********************************************************
int CFamilyModule::GetFamilyAverageLevel( int nFamilyID, int &rLevel )
{
	int	tFamilyMemberList[MAX_FAMILYMEMBER_NUM] = { 0 };	
	int	tNum = MAX_FAMILYMEMBER_NUM;		
	
	GetFamilyMemberList( nFamilyID, tFamilyMemberList, tNum );
	rLevel = 0;
	if ( tNum > 0 )
	{
		int tOnLineNum = 0;
		int tTotalLevel = 0;
		for ( int i = 0; i < tNum; ++i )
		{
			CEntityPlayer *tpPlayer = ( CEntityPlayer * )CSceneLogic::GetSingleton().GetEntity( tFamilyMemberList[i] );
			if ( tpPlayer == NULL )
			{
				continue;
			}
			++tOnLineNum;
			tTotalLevel += tpPlayer->GetLevel();
		}
		if ( tOnLineNum > 0 )
		{
			rLevel = tTotalLevel / tOnLineNum;
			return SUCCESS;			
		}
		return -1;
	}
	return -1;
}


//// ***********************************************************
////  Function:		InsertMember
////  Description:	�������Ա���볡��ʱ,�����б�
////  Output:			
////  Date:			09/03/2009
//// **********************************************************
//int CFamilyInfo::InsertMember( int nRoleID, CMemberInfo &rMemberInfo )
//{  
//	if ( mMemberList.size() >= MAX_FAMILYMEMBER_NUM )
//	{ 		
//		return -1;
//	}
//	FamilyMemberList::iterator it = mMemberList.find( nRoleID );
//	if ( it != mMemberList.end() )
//	{			
//		mMemberList.erase( it );
//	}
//	mMemberList.insert( FamilyMemberList::value_type( nRoleID, rMemberInfo ) );
//	return	SUCCESS;
//}
//
//// ***********************************************************
////  Function:		Initialize
////  Description:	��ʼ����������Ϣ
////  Output:			
////  Date:			09/03/2009
//// **********************************************************
//int CFamilyInfo::Initialize()
//{  
//	mMemberList.initailize();
//	mCorpsID = 0;
//	memset( mFamilyName, 0, sizeof( mFamilyName ) );
//	memset( mCorpsName, 0, sizeof( mCorpsName ) );
//	return SUCCESS;
//}
//
//// ***********************************************************
////  Function:		DeleteMember
////  Description:	�������ʱɾ�������Ϣ,�����б�
////  Output:			
////  Date:			09/03/2009
//// **********************************************************
//int CFamilyInfo::DeleteMember( int nRoleID )
//{  
//	FamilyMemberList::iterator it = mMemberList.find( nRoleID );
//	if ( it != mMemberList.end() )
//	{
//		mMemberList.erase( it );
//	}
//	return SUCCESS;
//}
//
//
//// ***********************************************************
////  Function:		HasMember
////  Description:	�жϳ�Ա�б����Ƿ���ĳ�����,�����б�
////  Output:			
////  Date:			09/03/2009
//// **********************************************************
//bool CFamilyInfo::HasMember( int nRoleID )
//{
//	if ( mMemberList.find( nRoleID ) != mMemberList.end() )
//	{
//		return true;
//	}
//	return false;
//}
//
//// ***********************************************************
////  Function:		ChangeMemberInfo
////  Description:	�ı��Ա����Ϣ,�����б�
////  Output:			
////  Date:			09/03/2009
//// **********************************************************
//int CFamilyInfo::ChangeMemberInfo( int nRoleID, CMemberInfo &rMemberInfo )
//{
//	FamilyMemberList::iterator it = mMemberList.find( nRoleID );
//	if ( it != mMemberList.end() )
//	{
//		it->second = rMemberInfo; 
//	}
//	return SUCCESS;
//}
//
//// ��ȡ��Ա��Ϣ
//CMemberInfo *CFamilyInfo::GetMemberInfo( int nRoleID )
//{
//	FamilyMemberList::iterator it = mMemberList.find( nRoleID );
//	if ( it != mMemberList.end() )
//	{
//		return &it->second; 
//	}
//	return NULL;
//}
//
//// ***********************************************************
////  Function:		GetMemberList
////  Description:	��ȡ�����������б�,�����б�
////  Output:			
////  Date:			09/03/2009
//// **********************************************************
//int CFamilyInfo::GetMemberList( int *pIDList, int &rNum )
//{
//	LK_ASSERT( pIDList != NULL, return -1 )
//	int tNum = rNum;
//	rNum = 0;
//	FamilyMemberList::iterator it = mMemberList.begin();
//	for( ; it != mMemberList.end() && rNum < tNum ; ++it )
//	{	
//		pIDList[rNum] = (it->second).mEntityID;
//		++rNum;
//	}
//	return SUCCESS;
//}
//
//// ***********************************************************
////  Function:		SetFamilyName
////  Description:	���ü�������
////  Output:			
////  Date:			12/01/2009
//// **********************************************************
//void CFamilyInfo::SetFamilyName( const char *pName, bool bRefresh /* = false */ )
//{	
//	if ( pName == NULL )
//	{					
//		return;
//	}
//	
//	if ( mFamilyName[0] != '\0' && bRefresh == false )
//	{
//		return;
//	}
//	
//	strncpy( mFamilyName, pName, sizeof( mFamilyName ) - 1 );			
//}
//
//// ***********************************************************
////  Function:		SetCorpsName
////  Description:	���þ�������
////  Output:			
////  Date:			12/01/2009
//// **********************************************************
//void CFamilyInfo::SetCorpsName( const char *pName, bool bRefresh /* = false */ )
//{
//	if ( pName == NULL )
//	{					
//		return;
//	}
//
//	if ( mCorpsName[0] != '\0' && bRefresh == false )
//	{
//		return;
//	}
//
//	strncpy( mCorpsName, pName, sizeof( mCorpsName ) - 1 );	
//}
//
//// �ַ���������ʾ
//const char *CFamilyInfo::GetFamilyNameShow()
//{
//#ifdef CHARSET_SHOW_GBK
//	static char tFamilyName[ MAX_FAMILYNAME_LENGTH ] = {0};
//	int nNameLen = sizeof(tFamilyName)-1;
//	charset_convert( "utf8", "gbk", (char*)mFamilyName, strlen( mFamilyName ),
//		tFamilyName, (size_t*)&nNameLen );
//	return tFamilyName;
//#else
//	return mFamilyName;
//#endif	
//}
//
//
//const char *CFamilyInfo::GetCorpsNameShow()
//{
//	// �ַ���������ʾ
//#ifdef CHARSET_SHOW_GBK
//	static char tCorpsName[ MAX_CORPSNAME_LENGTH ] = {0};
//	int nNameLen = sizeof(tCorpsName)-1;
//	charset_convert( "utf8", "gbk", (char*)mCorpsName, strlen( mCorpsName ),
//		tCorpsName, (size_t*)&nNameLen );
//	return tCorpsName;
//#else
//	return mCorpsName;
//#endif	
//}

// ***********************************************************
//  Function:		OnGateMsgBuyFamilyRedPaper
//  Description:	�������������Ϣ��Ӧ
//  Output:			
//  Date:			10/29/2009
// **********************************************************
void CFamilyModule::OnGateResponseBuyFamilyItem( CMessage *pMessage )
{
	LK_ASSERT(  pMessage != NULL, return )	
	CMessageBuyFamilyItemResponse *tpMsg = ( CMessageBuyFamilyItemResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	CEntityPlayer *tpPlayer = ( CEntityPlayer * )CSceneLogic::GetSingleton().GetEntity( tpMsg->entityid() );	
	if ( tpPlayer == NULL )
	{
		LOG_ERROR( "family","[%s,%d][%s] can not find player ( roleid:%d, entityid:%d ) ", __LK_FILE__,__LINE__,__FUNCTION__,
			tpMsg->roleid(), tpMsg->entityid() );
		return;
	}
		
	if ( tpMsg->errcode() == SUCCESS )
	{
		// ����Ҳ�����		
		CPropertyModule::GetSingleton().PlayerInsertItem( tpPlayer, tpMsg->itemid(), tpMsg->itemnum(), false );
	}
	else
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( tpPlayer, tpMsg->errcode() );
	}	
}

// ***********************************************************
//  Function:		BuyFamilyItem
//  Description:	���������Ʒ�Ľӿ�
//  Output:			
//  Date:			11/03/2009
// **********************************************************
void CFamilyModule::BuyFamilyItem( CEntityPlayer *pPlayer, int nItemID, int nItemNum, int nNpcTmpID )
{ 
	LK_ASSERT( pPlayer != NULL, return )
	
	// Ȩ�޼��
	if ( pPlayer->GetFamilyID() == 0 )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_FAMILY_BUYFAMILYITE_HASONFAMILY );
		return;
	}
	
	// Ȩ�޼��
	/*if ( !pPlayer->GetIsFamilyHeader() )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_FAMILY_HASNORIGHT );
		return;
	}*/
	
	// �������
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	if ( !tpProperty->GetBaggage()->Space( nItemID, nItemNum ) )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_FAMILY_REDPAPER_SPACENOTENOUGH );
		return;
	}
	
	CMessage tMsgHead;
	CMessageBuyFamilyItemRequest tMsgBuyFamilyItem;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2G_REQUEST_BUYFAMILYITEM );	
	tMsgHead.set_msgpara( (int)&tMsgBuyFamilyItem );
	
	tMsgBuyFamilyItem.set_roleid( pPlayer->GetCharID() );
	tMsgBuyFamilyItem.set_entityid( pPlayer->GetEntityID() );
	tMsgBuyFamilyItem.set_familyid( pPlayer->GetFamilyID() );
	tMsgBuyFamilyItem.set_itemid( nItemID );
	tMsgBuyFamilyItem.set_itemnum( nItemNum );
	// tMsgBuyFamilyItem.set_totalcost( nItemPrice*nItemNum );
	tMsgBuyFamilyItem.set_npctmpid( nNpcTmpID );	
	CSceneLogic::GetSingleton().Send2Gate( &tMsgHead );
}

// ***********************************************************
//  Function:		OnMessageEnterFamilyRepetion
//  Description:	��ҽ�����帱������Ϣ����
//  Output:			
//  Date:			11/27/2009
// **********************************************************
void CFamilyModule::OnMessageEnterFamilyRepetion( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageEnterBossReptionRequest *tpMsg = ( CMessageEnterBossReptionRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if ( pPlayer->GetFamilyID() == 0 )
	{
		return;
	}
	tpMsg->set_familyid( pPlayer->GetFamilyID() ); 		
	SenMsgToGate( pMessage, tpMsg, pPlayer )	
}

// ***********************************************************
//  Function:		OnMessageGetFamilyGoodsList
//  Description:	��ȡ��������б����Ϣ����
//  Output:			
//  Date:			01/08/2010
// **********************************************************
void CFamilyModule::OnMessageGetFamilyGoodsList( CEntityPlayer *pPlayer, CMessage *pMessage )
{  
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageGetFamilyGoodsListRequest *tpMsg = ( CMessageGetFamilyGoodsListRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// ����npc���ж�
	CEntityNpc* tpEntity = dynamic_cast< CEntityNpc* >( CSceneObjManager::GetSingletonPtr( )->GetObject( tpMsg->entityid() ) );
	LK_ASSERT( tpEntity != NULL, return  )
	if ( tpEntity->GetEntityType() != ENTITYTYPE_FUNCNPC )
	{
		return;
	}
	
	if ( pPlayer->IsWithinDistance( tpEntity, MAX_NPC_TALK_GIRD ) == false )
	{
		return;
	}	
	
	if ( pPlayer->GetFamilyID() == 0 )
	{
		return;
	}

	// �����ж�
	CPropertyNPC * tpNpcProperty = ( CPropertyNPC * )tpEntity->GetProperty(); 
	CTemplateNpc *tpTmpNpc = ( CTemplateNpc * )CDataStatic::SearchTpl( tpNpcProperty->GetPropertyTempID() );
	LK_ASSERT( tpTmpNpc != NULL, return )
	tpMsg->set_npctmpid( tpTmpNpc->mTempID );	
	tpMsg->set_familyid( pPlayer->GetFamilyID() );
	SenMsgToGate( pMessage, tpMsg, pPlayer )
}

// ***********************************************************
//  Function:		OnMessageGetFamilyExchangeGoodsList
//  Description:	��ȡ����һ���Ʒ�б����Ϣ����
//  Output:			
//  Date:			01/11/2010
// **********************************************************
void CFamilyModule::OnMessageGetFamilyExchangeGoodsList( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageGetFamilyExchangeGoodsListRequest *tpMsg = ( CMessageGetFamilyExchangeGoodsListRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// ����npc���ж�
	CEntityNpc* tpEntity = dynamic_cast< CEntityNpc* >( CSceneObjManager::GetSingletonPtr( )->GetObject( tpMsg->entityid() ) );
	LK_ASSERT( tpEntity != NULL, return )
	if ( tpEntity->GetEntityType() != ENTITYTYPE_FUNCNPC )
	{
		return;
	}

	if ( pPlayer->IsWithinDistance( tpEntity, MAX_NPC_TALK_GIRD ) == false )
	{
		return;
	}	
	
	if ( pPlayer->GetFamilyID() == 0 )
	{
		return;
	}

	// �����ж�
	CPropertyNPC * tpNpcProperty = ( CPropertyNPC * )tpEntity->GetProperty(); 
	CTemplateNpc *tpTmpNpc = ( CTemplateNpc * )CDataStatic::SearchTpl( tpNpcProperty->GetPropertyTempID() );
	LK_ASSERT( tpTmpNpc != NULL, return )
	tpMsg->set_npctmpid( tpTmpNpc->mTempID );
	tpMsg->set_familyid( pPlayer->GetFamilyID() );
	SenMsgToGate( pMessage, tpMsg, pPlayer )
}

// ***********************************************************
//  Function:		OnGateMsgGetFamilyGoodsListResponse
//  Description:	��ȡ��������б�����ط�����Ϣ
//  Output:			
//  Date:			01/11/2010
// **********************************************************
void CFamilyModule::OnGateMsgGetFamilyGoodsListResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageGetFamilyGoodsListResponse *tpMsg = ( CMessageGetFamilyGoodsListResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}

// ***********************************************************
//  Function:		OnMessageGetFamilyExchangeGoodsList
//  Description:	��ȡ��������б����Ϣ����
//  Output:			
//  Date:			01/11/20109
// **********************************************************
void CFamilyModule::OnGateMsgGetFamilyExchangeGoodsListResponse( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );  
}

// ***********************************************************
//  Function:		FamilyExchange
//  Description:	����һ�
//  Output:			
//  Date:			01/14/2010
// **********************************************************
void CFamilyModule::FamilyExchange( CEntityPlayer *pPlayer, int nComposeID, int nEntityID, int nItemNum )
{
	LK_ASSERT( pPlayer != NULL, return )		
	CEntityFuncNpc *tpFuncNpc = static_cast< CEntityFuncNpc * >( CSceneObjManager::GetSingleton().GetObject( nEntityID ) );
	if ( tpFuncNpc == NULL )
	{
		return;
	}
	CPropertyNPC *tpNpcProperty = ( CPropertyNPC * )tpFuncNpc->GetProperty();
	CTemplateNpc *tpNpcTempLate = ( CTemplateNpc * )CDataStatic::SearchTpl( tpNpcProperty->GetPropertyTempID() );
	if ( tpNpcTempLate == NULL )
	{
		return;
	}
	
	if ( pPlayer->IsWithinDistance( tpFuncNpc, MAX_NPC_TALK_GIRD ) == false )
	{
		return;
	}
		  
	if ( pPlayer->GetFamilyID() == 0 )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_FAMILY_EXCHANGE_HASONFAMILY );
		return;
	}
	
	CTemplateMultiCompose *tpTplMultiCompose = ( CTemplateMultiCompose * )CDataStatic::SearchTpl( nComposeID );
	if ( tpTplMultiCompose == NULL )
	{								
		return;
	}
	
	// �������
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	if ( tpProperty->GetBaggage()->Space( tpTplMultiCompose->mItemID[0], nItemNum ) == false )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_MULTICOMFULL );
		return;
	}
	
	
	CMessage tMsgHead;
	CMessageFamilyExchangeRequest tMsgFamilyExchange;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2G_REQUEST_FAMILYEXCHANGE );
	tMsgHead.set_msgpara( (int)&tMsgFamilyExchange );
	
	tMsgFamilyExchange.set_composeid( nComposeID );
	tMsgFamilyExchange.set_roleid( pPlayer->GetCharID() );
	tMsgFamilyExchange.set_npctmpid( tpNpcTempLate->mTempID );
	tMsgFamilyExchange.set_familyid( pPlayer->GetFamilyID() );
	tMsgFamilyExchange.set_itemnum( nItemNum );
	
	CSceneLogic::GetSingleton().Send2Gate( &tMsgHead );
}

// ***********************************************************
//  Function:		OnGateResponseFamilyExchange
//  Description:	����һ��Ļ�Ӧ��Ϣ
//  Output:			
//  Date:			01/14/2010
// **********************************************************
void CFamilyModule::OnGateResponseFamilyExchange( CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return )
	CMessageFamilyExchangeResponse *tpMsg = ( CMessageFamilyExchangeResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	CEntityPlayer *tpPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMsg->roleid() );
	if ( tpPlayer == NULL )
	{
		LOG_ERROR( "family","[%s,%d] familyexchange error, can not find player, roleid:%d, composeid:%d, errcode:%d  ",__FUNCTION__, __LINE__, tpMsg->roleid(), tpMsg->composeid(), tpMsg->errcode() );
		return;
	}

	if ( tpMsg->errcode() == SUCCESS )
	{
		CTemplateMultiCompose *tpTmpCompose = ( CTemplateMultiCompose * )CDataStatic::SearchTpl( tpMsg->composeid() );
		if ( tpTmpCompose != NULL )
		{	
			CTplItem *tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( tpTmpCompose->mItemID[0] );
			if ( tpTplItem == NULL )
			{
				LOG_ERROR( "family","[%s,%d] can not find item templateid by id:%d, roleid:%d, composeid:%d ", __FUNCTION__, __LINE__, tpTmpCompose->mItemID[0], tpMsg->roleid(), tpTmpCompose->mTempID );
				return;
			}
			if ( tpTplItem->mPileLimit <= 1 )
			{
				for ( int i = 1; i <= (int)tpMsg->itemnum(); ++i )
				{
					CItemObject * pInsItemPile = CPropertyModule::GetSingleton().PlayerInsertItem( tpPlayer, tpTmpCompose->mItemID[0], 1 );
					if ( pInsItemPile != NULL )
					{
						LogEventGetItemByCompose( tpPlayer, pInsItemPile->GetGUID(), tpTmpCompose->mItemID[ 0 ], 1,
							tpTmpCompose->mMaterialID[ 0 ], tpTmpCompose->mMaterialNum[ 0 ] );
					}					
				}			
			}
			else
			{
				CItemObject * pInsItemPile = CPropertyModule::GetSingleton().PlayerInsertItem( tpPlayer, tpTmpCompose->mItemID[0], tpMsg->itemnum() );
				if ( pInsItemPile != NULL )
				{
					LogEventGetItemByCompose( tpPlayer, pInsItemPile->GetGUID(), tpTmpCompose->mItemID[ 0 ], tpMsg->itemnum(),
						tpTmpCompose->mMaterialID[ 0 ], tpTmpCompose->mMaterialNum[ 0 ] );
				}		
			}			
		}					
		//CPropertyModule::GetSingleton().PlayerMultiCom( tpPlayer, tpMsg->composeid() );
	}		
	else
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( tpPlayer, tpMsg->errcode() );		
	}
}

// ***********************************************************
//  Function:		AddFamilyExchangeItem
//  Description:	���Ӽ���һ���Ʒ�Ľӿ�
//  Output:			
//  Date:			01/15/2010
// **********************************************************
int CFamilyModule::AddFamilyExchangeItem( CEntityPlayer *pPlayer, CTplLeagueBag *tpTplLeagueBag )
{  
	LK_ASSERT( pPlayer != NULL && tpTplLeagueBag != NULL, return -1 )	
	if ( pPlayer->GetFamilyID() == 0 )
	{
		return ERROR_FAMILY_USELEAGUEBAG_HASNOFAMILY;
	}	
	
	CMessage tMsgHead;
	CMessageAddFamilyExchangeItemNotify tMsgAddFamilyExchangeItem;	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2G_NOTIFY_ADDFAMILYEXCHANGEITEM );
	tMsgHead.set_msgpara( (int)&tMsgAddFamilyExchangeItem );	
	tMsgAddFamilyExchangeItem.set_familyid( pPlayer->GetFamilyID() );
	tMsgAddFamilyExchangeItem.set_roleid( pPlayer->GetCharID() );
	tMsgAddFamilyExchangeItem.set_leaguebagtmpid( tpTplLeagueBag->mTempID );
	CSceneLogic::GetSingleton().Send2Gate( &tMsgHead );	
	return SUCCESS;
}

// ***********************************************************
//  Function:		OnMessageEnterFamilyRepetion
//  Description:	������帱�������ػ�Ӧ
//  Output:			
//  Date:			11/27/2009
// **********************************************************
void CFamilyModule::OnGateMsgEnterFamilyRepetion( CEntityPlayer *pPlayer, CMessage *pMessage )
{	 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageEnterBossReptionRequest *tpMsg = ( CMessageEnterBossReptionRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	tpMsg->set_familyid( pPlayer->GetFamilyID() );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, pMessage );
}

// ***********************************************************
//  Function:		ClearFamilyRepetionInfo
//  Description:	������帱����Ϣ
//  Output:			
//  Date:			11/27/2009
// **********************************************************
void CFamilyModule::ClearFamilyRepetionInfo( int nFamilyID, int nRepetionLevel, int nOgreNum, int nTimeLength , int nBigWaveNum, int nSamllWaveNum, int nMaxHitNum, int nScore )
{	
	// ���
	CMessage tMsgHead;
	CMessageClearFamilyRepetionInfoNotify tMsgClearFamilyRepetionInfo;	
	tMsgHead.mutable_msghead()->set_messageid( ID_G2S_NOTIFY_CLEARFAMILYREPETIONIFO );
	tMsgHead.set_msgpara( (int)&tMsgClearFamilyRepetionInfo );
	tMsgClearFamilyRepetionInfo.set_familyid( nFamilyID );	
	tMsgClearFamilyRepetionInfo.set_repetionscore( nScore ); 	
	CSceneLogic::GetSingleton().Send2Gate( &tMsgHead );
	
	// ���͸�������֪ͨ
	CMessageFamilyRepetionScoreNotify tMsgRepetionScore;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_FAMILYREPETIONSCORE );
	tMsgHead.set_msgpara( (int)&tMsgRepetionScore );
	
	tMsgRepetionScore.set_repetionlevel( nRepetionLevel );
	tMsgRepetionScore.set_ogrenum( nOgreNum );
	tMsgRepetionScore.set_timelength( nTimeLength );
	tMsgRepetionScore.set_wavenum( nBigWaveNum );
	tMsgRepetionScore.set_maxhitnum( nMaxHitNum );
	tMsgRepetionScore.set_score( nScore );
	CSceneLogic::GetSingleton().SendFamilyMessage( &tMsgHead, nFamilyID );
}

// ***********************************************************
//  Function:		GetFamilyNameByID
//  Description:	��ȡ��������,�����м����Ա�ڱ�����ʱ����Ч
//  Output:			
//  Date:			12/02/2009
// **********************************************************
const char *CFamilyModule::GetFamilyNameByID( int nFamilyID )
{ 
	FamilyList::iterator it = mFamilyList.find( nFamilyID );
	if ( it != mFamilyList.end() )
	{
		CFamilyInfo *tpFamilyInfo = ( CFamilyInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		LK_ASSERT( tpFamilyInfo != NULL, return NULL )
		return tpFamilyInfo->GetFamilyName();		
	}
	return NULL;		
}

// ***********************************************************
//  Function:		GetCorspNameByID
//  Description:	��ȡ��������,�����о��ų�Ա�ڱ�����ʱ����Ч
//  Output:			
//  Date:			12/02/2009
// **********************************************************
const char *CFamilyModule::GetCorspNameByID( int nFamilyID, int nCorpsID )
{
	FamilyList::iterator it = mFamilyList.find( nFamilyID );
	if ( it != mFamilyList.end() )
	{
		CFamilyInfo *tpFamilyInfo = ( CFamilyInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		LK_ASSERT( tpFamilyInfo != NULL, return NULL )
		if ( tpFamilyInfo->GetCorpsID() != nCorpsID )
		{
			return NULL;
		}
		return tpFamilyInfo->GetCorpsName();		
	}	
	return NULL;
}

// ***********************************************************
//  Function:		GetFamilyMemberInfo
//  Description:	��ȡ�����Ա�ĸ�����Ϣ
//  Output:			
//  Date:			12/02/2009
// **********************************************************
CMemberInfo *CFamilyModule::GetFamilyMemberInfo( int nFamilyID, int nRoleID )
{	
	FamilyList::iterator it = mFamilyList.find( nFamilyID );
	if ( it != mFamilyList.end() )
	{
		CFamilyInfo *tpFamilyInfo = ( CFamilyInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		LK_ASSERT( tpFamilyInfo != NULL, return NULL )
		return tpFamilyInfo->GetMemberInfo( nRoleID );
	}
	return NULL;				
}

// ***********************************************************
//  Function:		GetFamilyInfo
//  Description:	��ȡ������Ϣ
//  Output:			
//  Date:			12/03/2009
// **********************************************************
CFamilyInfo *CFamilyModule::GetFamilyInfo( int nFamilyID )
{  
	FamilyList::iterator it = mFamilyList.find( nFamilyID );
	if ( it != mFamilyList.end() )
	{
		CFamilyInfo *tpFamilyInfo = ( CFamilyInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		return tpFamilyInfo;
	}
	return NULL;
}

// ***********************************************************
//  Function:		HasFamilyRight
//  Description:	�ж�����Ƿ��Ǽ�������
//  Output:			
//  Date:			12/03/2009
// **********************************************************
bool CFamilyModule::HasFamilyRight( CEntityPlayer *pPlayer, int nRight )
{  
	if ( pPlayer == NULL )
	{
		return false;
	}
	
	CMemberInfo *tpMemberInfo = GetFamilyMemberInfo( pPlayer );
	if ( tpMemberInfo == NULL )
	{
		return false;
	}
	
	switch( nRight )
	{
		case EM_RIGHT_TASK: 
		{
			if ( tpMemberInfo->mFamilyPost == FAMILY_POST_HEADER )
			{
				return true;
			}				
			break;
		}
	}	
	return false;
}

// ***********************************************************
//  Function:		HasCorpsRight
//  Description:	�ж��Ƿ��Ǿ�������
//  Output:			
//  Date:			12/03/2009
// **********************************************************
bool CFamilyModule::HasCorpsRight( CEntityPlayer *pPlayer, int nRight )
{
	if ( pPlayer == NULL )
	{
		return false;
	}

	CMemberInfo *tpMemberInfo = GetFamilyMemberInfo( pPlayer );
	if ( tpMemberInfo == NULL )
	{
		return false;
	}

	switch( nRight )
	{
		case EM_RIGHT_TASK: 
		{
			if ( tpMemberInfo->mFamilyPost == CORPS_POST_CORPSHEADER )
			{
				return true;
			}				
			break;
		}
	}	
	return false;	
}

// ***********************************************************
//  Function:		InitialFamilyConfig
//  Description:	��ʼ����������
//  Output:			
//  Date:			12/02/2010
// **********************************************************
int CFamilyModule::InitialFamilyConfig( )
{	
	TiXmlDocument tDoc;
	LK_ASSERT( tDoc.LoadFile( CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"/family/familyconfig.xml" ) ) == true, return -1 );	
	
	TiXmlElement *tpRoot = tDoc.FirstChildElement( "FamilyConfig" );
	LK_ASSERT( tpRoot != NULL, return -1 )
	TiXmlElement *tpTaskConfig = tpRoot->FirstChildElement( "TaskConfig" );
	LK_ASSERT( tpTaskConfig != NULL, return -1 )
	
	mFamilyTask.initailize();
	for ( TiXmlElement *tpElement = tpTaskConfig->FirstChildElement( "FamilyTask" ); tpElement != NULL; tpElement = tpElement->NextSiblingElement() )
	{
		CFamilyTaskInfo tFamilyTask;
		int tTaskID = 0;
		if ( tpElement->Attribute( "ID" ) != NULL )
		{
			tTaskID = atoi( tpElement->Attribute( "ID" ) );
		}
		if ( tTaskID != 0 )
		{
			mFamilyTask.insert( FamilyTaskList::value_type( tTaskID, tFamilyTask ) );
		}		
	}
	
	return SUCCESS;
}

// ***********************************************************
//  Function:		IsFamilyTask
//  Description:	�ж��Ƿ���ĳ������
//  Output:			
//  Date:			12/02/2010
// **********************************************************
bool CFamilyModule::IsFamilyTask( int nTaskID )
{
	if ( mFamilyTask.find( nTaskID ) != mFamilyTask.end() )
	{
		return true;
	}		
	return false;
}

// ***********************************************************
//  Function:		OnTaksChangeStability
//  Description:	��ȡ����ļ��尲���Ƚ���
//  Output:			
//  Date:			12/02/2010
// **********************************************************
void CFamilyModule::OnTaksChangeStability( int nTaskID, CEntityPlayer *pPlayer )
{
	LK_ASSERT( pPlayer != NULL, return )
	if ( IsFamilyTask( nTaskID ) == true )
	{
		ChangeFamilyStability( pPlayer, 0, REASON_TASK );	
	}
}

void CFamilyModule::LoadFamilyConfigCallback(const char *pcConfigPath)
{
	int tRet = CFamilyModule::GetSingleton().InitialFamilyConfig();	
	if ( tRet != SUCCESS )
	{
		LOG_ERROR( "family","Load FamilyConfig Error!" );
		printf( "Load FamilyConfig Error!" );
	}
}