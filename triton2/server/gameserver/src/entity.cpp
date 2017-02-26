#include "stdafx.hpp"
#include "entity.h"
#include "template.h"
#include "sceneobj_define.h"
#include "sceneobj_manager_imp.h"
#include "sceneobj_manager.h"
#include "mapmodule.h"
#include "mapobjmanager.h"
#include "timer_define.h"
#include "teammodule.h"
#include "taskmodule.h"
#include "trademodule.h"
#include "creature_refresher.h"
#include "message_maker.h"
#include "logservertype.h"
#include "message_maker.h"
#include "message_maker.h"
#include "entity_searcher_imp.h"  
#include "base.h"
#include "message_factory.h"
#include "activitymodule.h"
#include "gmmodule.h"
#ifdef LEAK_CHK_DEBUG_NEW
#include "debug_new.h"
#endif

//////////////////////////////////////////////////////////////////////////
//		CEntity
//////////////////////////////////////////////////////////////////////////


CEntity* CEntity::GetOwner()
{
	return (CEntity*)CSceneObjManager::GetSingletonPtr()->GetObject(GetOwnerID());
}

bool CEntity::AddFunResult( unsigned int unSrcEntityID, unsigned short usFunc, unsigned short usResult, bool bBroadCast, unsigned int unValue1, unsigned int unValue2, unsigned int unValue3 /*= 0*/, unsigned int unValue4 /*= 0*/, unsigned int unValue5 /*= 0*/ )
{
	if ( bBroadCast == false )
	{
		return CPropertyModule::GetSingletonPtr( )->GetSingleList( )->push_back( unSrcEntityID, this, usFunc, usResult, bBroadCast, unValue1, unValue2, unValue3, unValue4, unValue5 );
	}
	else
	{
		return CPropertyModule::GetSingletonPtr( )->GetResultList( )->push_back( unSrcEntityID, this, usFunc, usResult, bBroadCast, unValue1, unValue2, unValue3, unValue4, unValue5 );
	}	
}

// ��ʼ�������б�
void CEntity::InitFunResult( int nListID )
{
//	CPropertyModule::GetSingleton( ).GetResultList( )->Initialize( );
	if ( nListID != 0 )
		CPropertyModule::GetSingleton( ).GetResultList( )->SetListID( nListID );
}


// ***************************************************************
//  Function:		��Ŀ��ʵ����뵽�ɼ���
//  Description:	AddViewEntity
//	Input:			pTarget - Ŀ��
//	OutPut:			��
//	Return:			true - ��ӳɹ��� false - û�����
//	Others:
//  Date:			11/26/2008
// 
// ***************************************************************
bool CEntity::AddViewEntity(CEntity* pTarget)
{
	LK_ASSERT( pTarget != NULL, return false );

	if( pTarget == this )
	{
		return false;
	}

	if(  pTarget->IsPlayer() )
	{
		mSeenPlayerContainer.Add( pTarget->GetEntityID() );

#ifdef _DEBUG_
		LOG_DEBUG( "map", "Add %d to Entity %d ", pTarget->GetEntityID(), this->GetEntityID());

		mSeenPlayerContainer.Show( "map" );
#endif

		return true;
	}

	return false;
}

// ***************************************************************
//  Function:		��Ŀ��ʵ��ӿɼ���ɾ��
//  Description:	DeleteViewEntity
//	Input:			pTarget - Ŀ��
//	OutPut:			��
//	Return:			true - ɾ���ɹ��� false - û��ɾ��
//	Others:
//  Date:			11/26/2008
// 
// ***************************************************************
bool CEntity::DeleteViewEntity(CEntity *pTarget)
{
	LK_ASSERT( pTarget != NULL, return false );

	if( pTarget == this )
	{
		return false;
	}

	if( pTarget->IsPlayer() ) // ����Ҳ��������NPC�Ŀɼ�����
	{
		mSeenPlayerContainer.Remove( pTarget->GetEntityID() );

#ifdef _DEBUG_
		LOG_DEBUG( "map", "delete %d from Entity %d", pTarget->GetEntityID(), this->GetEntityID() );

		mSeenPlayerContainer.Show( "map" );
#endif
		return true;
	}

	return false;
}

// �õ���ͼ����
CMapObject* CEntity::GetMapObject( )
{
	return (CMapObject*) CSceneObjManager::GetSingletonPtr()->GetObject( mMapObjectID );
}

// Ŀ���Ƿ��ھ��뷶Χ��
bool CEntity::IsWithinDistance( CEntity* pTarget, unsigned int unDistance )
{
	if( pTarget == NULL )
	{
		return false;
	}

	// ����һ����ͼû�бȽϵ�����
	if( GetMapObjectID() != pTarget->GetMapObjectID() )
	{
		return false;
	}

	return GetPos().LimitDistance( pTarget->GetPos(), unDistance );
}


// �Ƿ��ڿɼ���Χ��
bool CEntity::IsWithinViewDistance( CEntity* pTarget )
{
	// ����һ����ͼû�бȽϵ�����
	if( GetMapObjectID() != pTarget->GetMapObjectID() )
	{
		return false;
	}

	if ( ::abs( pTarget->GetPosX() - this->GetPosX() ) <= VIEW_RADIUS_X &&
		::abs( pTarget->GetPosY() - this->GetPosY() <= VIEW_RADIUS_Y ) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

 
//////////////////////////////////////////////////////////////////////////
///		CEntityPlayer	
//////////////////////////////////////////////////////////////////////////



CEntityPlayer::CEntityPlayer( ) : CEntityCharacter( ENTITYTYPE_PLAYER )
{

      if ( CObj::msCreateMode )
      {
          Initialize( );
      } 
      else
      {
          Resume( );
      }
 
}

CEntityPlayer::~CEntityPlayer()
{
	
}



// ***************************************************************
//  Function:		IsHostileTo 
//  Description:	�Ƿ�ж�
//	Input:			pEntity - �Է�ʵ��
//	OutPut:			��
//	Return:			��
//	Others:			Ŀǰ���ж��൱�Ŀ��ɣ���Ϊ���ϵͳ��δ����
//  Date:			11/13/2008
// 
// ***************************************************************
bool CEntityPlayer::IsHostileTo( CEntity* pEntity )
{
	LK_ASSERT( pEntity != NULL, return false );
	
	// ������Լ�
	if( this == pEntity )
	{
		return false;
	}

    if( pEntity->IsCharacter( ) == true )
    {
        int tSrcCampID = GetCampID( );
        int tDesCampID = ( ( CEntityCharacter* )pEntity )->GetCampID( );

        if( tSrcCampID != 0 && tDesCampID != 0 )
        {
            return tSrcCampID != tDesCampID;
        }
    }

	switch ( pEntity->GetEntityType() )
	{
	case ENTITYTYPE_PLAYER:
		{
			CEntityPlayer* tpPlayer = ( CEntityPlayer* )pEntity;
			// TODO: ���Ѳ��ɹ���
			if ( IsTeamTo( tpPlayer ) == true )
			{
				return false;
			}

			// TODO: ͬһ���岻�ɹ���
			if ( IsFamilyTo( tpPlayer ) )
			{
				return false;
			}
			
			// GM���ܱ�����
			if( CGMModule::GetSingleton().IsGm( tpPlayer->GetGmStatus() ) == true  )
			{
				return false;
			}
			
			// TODO: �ж���ұ�������
			if ( IsBeginnerProtect() == true || tpPlayer->IsBeginnerProtect() == true || tpPlayer->IsTransProtect() == true )
			{
				return false;
			}

			CPropertyPlayer* tpSrcPro = ( CPropertyPlayer* )this->GetProperty( );
			CPropertyPlayer* tpDesPro = ( CPropertyPlayer* )tpPlayer->GetProperty( );

			if( tpSrcPro->GetStateParam( STATE_UNATTACK_PLAYER ).mInState == true )
			{
				return false;
			}
			if( tpDesPro->GetStateParam( STATE_PLAYER_UNATTACK ).mInState == true )
			{
				return false;
			}


			switch ( GetPKMode() )
			{
			case PKMODE_TRAINING:// ����ģʽ
				{
					// TODO: ͬ��������Ҳ��ɹ���
					/*if ( GetNationality() == tpPlayer->GetNationality() && tpDesPro->IsWhitePKStatus() )
					{
						return false;
					}
					return true;*/
					if( GetNationality() != tpPlayer->GetNationality() )
					{
						return true;
					}
					return false;
				}
				break;
			case PKMODE_ALL:// ��ɱģʽ
				{
					return true;
				}
				break;
			case PKMODE_CORPS:// ����ģʽ
				{
					// TODO: ͬһ�����е���Ҳ��ɹ���
					if ( IsCorpsTo( tpPlayer ) )
					{
						return false;
					}			
					return true;
				}
				break;
			case PKMODE_ALLY:// �˹�ģʽ
				{
					// TODO: ������ͬ�˹���Ҷ����ɹ���, ��ʱ��֧�ֽ���
					if( GetNationality() != tpPlayer->GetNationality() )
					{
						return true;
					}
					return false;
				}
				break;
			case PKMODE_EVIL:// ��ɱģʽ
				{
					if ( GetNationality() == tpPlayer->GetNationality() && tpDesPro->IsWhitePKStatus() )
					{
						return false;
					}
					return true;
				}
				break;
			default:
				break;
			}

			break;
		}
	case ENTITYTYPE_BLOCK:
	case ENTITYTYPE_OGRE:
	case ENTITYTYPE_FUNCNPC:
		{
			// TODO: �����Ƿ�ɹ���,��ģ�����
			CEntityNpc *pNpc = (CEntityNpc *)pEntity;
			// �����ͬ��
			if ( pNpc->GetOwnCampID() != 0 )
			{
				if ( GetNationality() != pNpc->GetOwnCampID() )
				{
					if( ( pNpc->GetPKType( ) & ENEMY_TO_FC ) == ENEMY_TO_FC )
					{
						return true;
					}
				}
				else
				{
					if( ( pNpc->GetPKType( ) & ENEMY_TO_SC ) == ENEMY_TO_SC )
					{
						return true;
					}
					return false;
				}
			}
			if ( GetNationality() == pNpc->GetNationality() ) 
			{
				if( ( pNpc->GetPKType( ) & ENEMY_TO_SC ) == ENEMY_TO_SC )
				{
					return true;
				}
			}
			// �����������
			else
			{
				if( ( pNpc->GetPKType( ) & ENEMY_TO_FC ) == ENEMY_TO_FC )
				{
					return true;
				}
			}
			break;
		}
	case ENTITYTYPE_PET:
		{
			CEntityPlayer* pOwner = (CEntityPlayer*) ( pEntity->GetOwner() );
			if ( pOwner == NULL )
			{
				return false;
			}
			// TODO: �Լ��ĳ���,�޷�����
			if ( pOwner->GetEntityID() == GetEntityID() )
			{
				return false;
			}
			
			return IsHostileTo( pOwner );
		}
	default:
		break;
	}

	return false;
}


// �Ƿ��Ѻ�
bool CEntityPlayer::IsFriendlyTo( CEntity* pEntity )
{
	LK_ASSERT( pEntity != NULL, return false );

	// ������Լ�
	if( this == pEntity )
	{
		return true;
	}
	
	if ( pEntity->IsPlayer() || pEntity->IsPet() )
	{
		return ! IsHostileTo( pEntity );
	}
	else if ( pEntity->IsOgre() || pEntity->IsFunNpc() )
	{
		CEntityNpc *pNpc = (CEntityNpc *)pEntity;
		if ( pNpc->GetOwnCampID() != 0 )			
		{
			if ( GetNationality() == pNpc->GetOwnCampID() )
			{
				if( ( pNpc->GetPKType( ) & FRIEND_TO_SC ) == FRIEND_TO_SC || ( pNpc->GetPKType( ) & NEUTRAL_TO_SC ) == NEUTRAL_TO_SC )
				{
					return true;
				}
				return false;
			}
			else
			{
				if( ( pNpc->GetPKType( ) & FRIEND_TO_SC ) == FRIEND_TO_FC || ( pNpc->GetPKType( ) & NEUTRAL_TO_FC ) == NEUTRAL_TO_FC )
				{
					return true;
				}
				return false;
			}
		}
		// �����ͬ��
		if ( GetNationality() == pNpc->GetNationality() ) 
		{
			if( ( pNpc->GetPKType( ) & FRIEND_TO_SC ) == FRIEND_TO_SC || ( pNpc->GetPKType( ) & NEUTRAL_TO_SC ) == NEUTRAL_TO_SC )
			{
				return true;
			}
		}
		// �����������
		else
		{
			if( ( pNpc->GetPKType( ) & FRIEND_TO_SC ) == FRIEND_TO_FC || ( pNpc->GetPKType( ) & NEUTRAL_TO_FC ) == NEUTRAL_TO_FC )
			{
				return true;
			}
		}
	}
	return false;
}

// �Ƿ��Ƕ���
bool CEntityPlayer::IsTeamTo( CEntity* pEntity )
{
	LK_ASSERT( pEntity != NULL, return false );

	// ������Լ�
	if ( this == pEntity )
	{
		return true;
	}

	if ( this->GetTeamFlag() != TEAM_NONE
		&& this->GetTeamFlag() == pEntity->GetTeamFlag() )
	{
		return true;
	}
	
	return false;
}

// �Ƿ���ͬһ�����Ա
bool CEntityPlayer::IsFamilyTo( CEntity *pEntity )
{
	LK_ASSERT( pEntity != NULL, return false )
	
	// ������Լ�
	if ( this == pEntity )
	{
		return true;
	}
	
	// ���ʵ�岻�����
	if ( !pEntity->IsPlayer() )
	{
		return false;
	}
	
	CEntityPlayer *tpPlayer = ( CEntityPlayer * )pEntity;
	
	if ( mFamilyID != 0 && mFamilyID == tpPlayer->GetFamilyID()  )
	{
		return true;
	}
	
	return false;
}

// �Ƿ���ͬһ����
bool CEntityPlayer::IsCorpsTo( CEntity *pEntity )
{
	LK_ASSERT( pEntity != NULL, return false )

	// ������Լ�
	if ( this == pEntity )
	{
		return true;
	}

	// ���ʵ�岻�����
	if ( !pEntity->IsPlayer() )
	{
		return false;
	}

	CEntityPlayer *tpPlayer = ( CEntityPlayer * )pEntity;

	if ( mCorpsID != 0 && mCorpsID == tpPlayer->GetCorpsID() )
	{
		return true;
	}
	return false;
}

// ��ʼ��������־��׷�����������Ϣ��
int CEntityPlayer::InitializeLog( )
{ 
	const char *tpLogDir = "../log/playerlog/";
	
	char tRirName[LOGNAMELENGTH] = { 0 };
	sprintf( tRirName, "%s%d", tpLogDir, mCharProfile.mAccountID );
	CreatDir( tRirName, 0700 );
	
	time_t tTime = time( NULL );
	tm	   *tTm = localtime( &tTime );
	memset( mLogName, 0, sizeof( mLogName ) );
	sprintf(mLogName,"%d_%04d%02d%02d", mCharProfile.mCharID, tTm->tm_year+1900, tTm->tm_mon, tTm->tm_mday );
	char tDir[LOGNAMELENGTH] = { 0 };
	sprintf( tDir,"%s/%s.log", tRirName, mLogName );
	INIT_ROLLINGFILE_LOG( mLogName, tDir, LEVEL_NOTSET, 100*1024*1024 );	
	return 0;
}

// �رո�����־
int CEntityPlayer::CloseLog( )
{
	if ( mIfTracedPlayer )
	{
		LOG_SHUTDOWN( mLogName );
	}
	return 0;
}

// д��Ϣ��������־
int CEntityPlayer::WriteMsgInfo( CMessage *pMessage, int nMsgType /* = 1 */ )
{  
	LK_ASSERT( pMessage != NULL, return -1 )	
	if ( mIfTracedPlayer == false )
	{
		return 1;
	}
	Message* pUnknownMessagePara = (Message*) pMessage->msgpara();
	LK_ASSERT( pUnknownMessagePara != NULL, return -1 );
	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessagePara->GetDescriptor();
	
	// �յ�����Ϣ
	if( nMsgType == 1 )
	{
		LOG_NOTICE( mLogName, "---- Recv Client[%s] Msg[ %s ][id: 0x%04x / %d] ----", GetCharNameShow(), pDescriptor->name().c_str(), pMessage->msghead().messageid(), pMessage->msghead().messageid());
		LOG_NOTICE( mLogName, "[%s]", ((Message*)pMessage->msgpara())->ShortDebugString().c_str() ); 	 		
	}	
	
	// ���͵���Ϣ
	else
	{
		LOG_NOTICE( mLogName, "---- Send Client[%s] Msg[ %s ][id: 0x%04x / %d] ----", GetCharNameShow(), pDescriptor->name().c_str(), pMessage->msghead().messageid(), pMessage->msghead().messageid());
		LOG_NOTICE( mLogName, "[%s]", ((Message*)pMessage->msgpara())->ShortDebugString().c_str() ); 
	}
	return 0;
}

// �Ƿ�����ʵ���Ѻ�
bool CEntityPlayer::IsHostileToPlayers()
{
	return true;
}

// ����ʵ��
unsigned int CEntityPlayer::GetOwnerID()
{
	// ��ҵ�����Ϊ���Լ�
	return GetEntityID();
}

// �����ұ�������
bool CEntityPlayer::IsBeginnerProtect()
{
	if ( /* TODO: �Ƿ��ڱ������� */true )
	{
		CPropertyPlayer* tpProperty = (CPropertyPlayer*) GetProperty();

		if ( tpProperty == NULL )
		{
			return true;
		}

		CTemplateBeginner* tpBeginner = (CTemplateBeginner*) CDataStatic::GetTemp( TEMP_BEGINNER );
		if ( tpBeginner == NULL )
		{
			return true;
		}

		// TODO: ��ʱд��Ϊ�̶��ȼ�,�Ժ��ģ��
		if ( (int)tpProperty->GetLevel( ) < tpBeginner->mBeginnerProtectLevel )
		{
			return true;
		}
	}

	return false;
}

// �������Ƿ��ܵ��糡���������򱣻�
bool CEntityPlayer::IsTransProtect()
{
	// TODO: ����п糡������״̬
	return false;
}

unsigned short CEntityPlayer::GetTeamLevel( )
{
	CEntityPlayer* tpPlayerArr[ TEAM_NUMBER ] = { NULL };
	unsigned short tLevel = 0;
	int tCountReal = 0;
	int tRtn = 0, tCount = 0;
	tRtn = CTeamModule::GetSingletonPtr( )->OnGetMemberList( this, tpPlayerArr, ARRAY_CNT( tpPlayerArr ), tCount );
	if (tRtn < 0)
	{
		return this->GetLevel();
	}
	
	for( unsigned int i = 0; i < ( unsigned int )tCount && i < ARRAY_CNT( tpPlayerArr ); i++ )
	{
		if( tpPlayerArr[ i ] != NULL )
		{
			tLevel += ( ( CPropertyPlayer* )tpPlayerArr[ i ]->GetProperty( ) )->GetLevel( );
			tCountReal++;
		}
	}

	return ( tCountReal != 0 ) ? ( unsigned short )tLevel / tCountReal : tLevel;
}

unsigned short CEntityPlayer::GetTeamMaxLevel( )
{
	CEntityPlayer* tpPlayerArr[ TEAM_NUMBER ] = { NULL };
	//unsigned short tLevel = 0;
	//int tCountReal = 0;
	int tRtn = 0, tCount = 0;

	tRtn = CTeamModule::GetSingletonPtr( )->OnGetMemberList( this, tpPlayerArr, ARRAY_CNT( tpPlayerArr ), tCount );
	if ( tRtn < 0 )
	{
		return this->GetLevel();
	}
	
	int tMinLevel = 0;
	for( unsigned int i = 0; i < ( unsigned int )tCount && i < ARRAY_CNT( tpPlayerArr ); i++ )
	{
		if( tpPlayerArr[ i ] != NULL )
		{
			if( (unsigned int)tMinLevel < ( ( CPropertyPlayer* )tpPlayerArr[ i ]->GetProperty( ) )->GetLevel( ) )
			{
				tMinLevel = ( ( CPropertyPlayer* )tpPlayerArr[ i ]->GetProperty( ) )->GetLevel( );
			}
		}
	}

	return tMinLevel;
}

unsigned short CEntityPlayer::GetTeamMinLevel( )
{
	CEntityPlayer* tpPlayerArr[ TEAM_NUMBER ] = { NULL };
	//unsigned short tLevel = 0;
	//int tCountReal = 0;
	int tRtn = 0, tCount = 0;
	tRtn = CTeamModule::GetSingletonPtr( )->OnGetMemberList( this, tpPlayerArr, ARRAY_CNT( tpPlayerArr ), tCount );
	if (tRtn < 0)
	{
		return this->GetLevel();
	}
	
	int tMaxLevel = 0;
	for( unsigned int i = 0; i < ( unsigned int )tCount && i < ARRAY_CNT( tpPlayerArr ); i++ )
	{
		if( tpPlayerArr[ i ] != NULL )
		{
			if( (unsigned int) tMaxLevel > ( ( CPropertyPlayer* )tpPlayerArr[ i ]->GetProperty( ) )->GetLevel( ) || tMaxLevel == 0 )
			{
				tMaxLevel = ( ( CPropertyPlayer* )tpPlayerArr[ i ]->GetProperty( ) )->GetLevel( );
			}
		}
	}

	return tMaxLevel;
}

void CEntityPlayer::IncAfterFcmKilled(int nCount)
{
	const int nKilledLimit = 50;
	const int nResetSeconds = 3600 * 5;

	int nLastFcmKilled = m_nAfterFcmKilled;

	m_nAfterFcmKilled += nCount;
	if ( m_nAfterFcmKilled > nKilledLimit && nLastFcmKilled <= nKilledLimit && GetFcmStatus() == em_half_rate )
	{
		CMessage tMessage;
		CMessageFCMPlayerResetRequest tPara;

		tPara.set_accountid(GetAccountID());
		tPara.set_seconds(nResetSeconds);

		tMessage.set_msgpara((uint32_t) &tPara);
		tMessage.mutable_msghead()->set_messageid( ID_S2G_FCMPLAYERRESET_REQUEST);
		CSceneLogic::GetSingletonPtr()->Send2Gate( &tMessage );
	}
}



// ***********************************************************
//  Function:		PKIsYellow
//  Description:	PK�Ƿ����
//  Input:			CEntity* pDesEntity ������ʵ��
//  OutPut:			
//  Return:			bool �Ƿ��ͻ�������Ϣ
//  Others:
//  Date:	11/20/2008
// **********************************************************
bool CEntityPlayer::PKIsYellow( CEntity* pDesEntity )
{
	//LK_ASSERT( pDesEntity != NULL, return false );

	//if ( pDesEntity->GetEntityType() == ENTITYTYPE_PLAYER || pDesEntity->GetEntityType() == ENTITYTYPE_PET )
	//{
	//	CEntityPlayer* tpDesPlayer = NULL;
	//	if ( pDesEntity->GetEntityType() == ENTITYTYPE_PLAYER )
	//		tpDesPlayer = (CEntityPlayer*) pDesEntity;
	//	else if ( pDesEntity->GetEntityType() == ENTITYTYPE_PET )
	//		tpDesPlayer = (CEntityPlayer*) pDesEntity->GetOwner();

	//	if ( tpDesPlayer == NULL )
	//	{
	//		return false;
	//	}

	//	// TODO: ������ҹ����������,�����߽������״̬,������ҹ���������������,�����κδ���
	//	// TODO: ������ҹ���������һ�������,���û���ʱ��,������ҹ����������,�����κδ���
	//	// TODO: ������ҹ����κ���Ҷ���������
	//	if ( GetPKStatus() == PKSTATUS_WHITE )
	//	{
	//		if ( tpDesPlayer->GetPKStatus() == PKSTATUS_WHITE )
	//		{
	//			SetPKStatus( PKSTATUS_YELLOW );
	//			// ��������ʱ��Ϊ60��
	//			SetPKYellowTimer( 60000 );
	//			return true;
	//		}
	//	}
	//	else if ( GetPKStatus() == PKSTATUS_YELLOW )
	//	{
	//		if ( tpDesPlayer->GetPKStatus() == PKSTATUS_WHITE || tpDesPlayer->GetPKStatus() == PKSTATUS_YELLOW )
	//		{
	//			SetPKYellowTimer( 60000 );
	//		}
	//	}
	//}
	return false;
}

// ɱ���Ƿ����
bool CEntityPlayer::PKIsRed( CEntity* pDesEntity )
{
	LK_ASSERT( pDesEntity != NULL, return false );

	if ( pDesEntity->GetEntityType() != ENTITYTYPE_PLAYER )
		return false;

//	CEntityPlayer* tpPlayer = (CEntityPlayer*) pDesEntity;

	// TODO: ����ɱ������,�������������PKֵ��1,����ɱ���������ߺ���,���κα仯
	// TODO: ����ɱ������,�������������PKֵ��1,����ɱ���������ߺ���,���κα仯
	// TODO: ����ɱ������,����PKֵ��1,����ɱ���������ߺ���,���κα仯
	/*if ( GetPKStatus() == PKSTATUS_WHITE || GetPKStatus() == PKSTATUS_YELLOW )
	{
		if ( tpPlayer->GetPKStatus() == PKSTATUS_WHITE )
		{
			SetPKStatus( PKSTATUS_RED );
			int tRedTimer = 1000 * 60 * 60 * 2;
			SetPKRedTimer( tRedTimer );
			int tPKValue = GetPKValue() + 100;
			SetPKValue( tPKValue );
			return true;
		}
	}
	if ( GetPKStatus() == PKSTATUS_RED )
	{
		if ( tpPlayer->GetPKStatus() == PKSTATUS_WHITE )
		{
			int tRedTimer = 1000 * 60 * 60 * 2;
			SetPKRedTimer( tRedTimer );
			int tPKValue = GetPKValue() + 100;
			SetPKValue( tPKValue );
		}
	}*/
	return false;
}


// ***************************************************************
//  Function:		IsVisibleFor 
//  Description:	�Ƿ��Ŀ����ҿɼ�
//	Input:			pTargetPlayer - Ŀ�����
//	OutPut:			��
//	Return:			��
//	Others:			
//  Date:			11/13/2008
// 
// ***************************************************************
bool CEntityPlayer::IsVisibleFor( CEntity* pTarget )
{
	LK_ASSERT( pTarget != NULL, return false );

	if( mVisibility == VISIBLITY_SELF )
	{
		return false;
	}
	else if ( mVisibility == VISIBLITY_TEAM )
	{
		return pTarget->GetTeamFlag() == GetTeamFlag();
	}
	else 
	{
		return true;
	}
}	


// �ı�PKģʽ
int CEntityPlayer::ChangePKMode( unsigned int vPKMode )
{
	// �������ܸı�ģʽ
	if ( GetAliveStatus( ) == ALIVE_DIE )
		return ERROR_CHANGEPKMODE_NONEPKMODE;

	if ( vPKMode != PKMODE_TRAINING && vPKMode != PKMODE_ALL 
		&& vPKMode != PKMODE_CORPS && vPKMode != PKMODE_ALLY
		&& vPKMode != PKMODE_EVIL )
		return ERROR_CHANGEPKMODE_NONEPKMODE;

	if ( mPKMode == (EPKMode)vPKMode )
		return ERROR_CHANGEPKMODE_SAMEPKMODE;

	CTemplateBeginner* tpBeginner = (CTemplateBeginner*) CDataStatic::GetTemp( TEMP_BEGINNER );
	if ( tpBeginner == NULL )
		return ERROR_CHANGEPKMODE_UNKNOWN;

	CPropertyPlayer* tpProPlayer = (CPropertyPlayer*) GetProperty();
	if ( tpProPlayer == NULL )
		return ERROR_CHANGEPKMODE_UNKNOWN;

	// pkģʽ�ȼ�����
	if ( (int)tpProPlayer->GetLevel( ) < tpBeginner->mBeginnerProtectLevel )
	{
		if( GetPKMode() == PKMODE_TRAINING )
		{
			return ERROR_CHANGEPKMODE_NEEDMORELEVEL;
		}

		// TODO:(�����ʱ��pk�ȼ���������) �����ǰ���� ������ģʽ������������ĵ�
	}

	SetPKMode( (EPKMode)vPKMode );
	return ERROR_CHANGEPKMODE_SUCCESS;
}

// ִ�м�������
void CEntityPlayer::DoSkillCost( CTemplateSkill* tpSkillTpl, bool bIsMagicWeapon /*= false*/ )
{
	LK_ASSERT( tpSkillTpl != NULL, return );

	CItemMagicWeapon* tpMW = NULL;
	if ( bIsMagicWeapon )
	{
		tpMW = (CItemMagicWeapon*)mProperty.GetEquipment()->GetItemObjPtr( EQUIPMENT_MAGICWEAPON );
		if ( tpMW == NULL )
			return ;
	}

	// ���㼼������
	for ( int i = 0; i < (int)ARRAY_CNT( tpSkillTpl->mCost ); i ++ )
	{
		if ( tpSkillTpl->mCost[ i ].mCostType == CTemplateSkill::COST_MP )
		{
			if ( bIsMagicWeapon )
			{
				tpMW->OnIncMp( (0-tpSkillTpl->mCost[ i ].mCostParam[ 0 ]) );
			}
			else
			{
				CPropertyValue tValue = CPropertyFormula::GetSkillLess( &mProperty, tpSkillTpl->mGenerID );
				int tDecMp = std::max( 0, (int)( ( tpSkillTpl->mCost[ i ].mCostParam[ 0 ] - tValue.mDeltaValue ) 
					* ( SERVER_PERCENT_FLOAT - tValue.mInitValue ) / SERVER_PERCENT_FLOAT ) );
				//mProperty.SetCurMP( mProperty.GetCurMP( ) - tDecMp );
				//
				//AddFunResult( GetEntityID(), FUNC_DECMP, RESULT_COST, tDecMp, mProperty.GetCurMP( ), mProperty.GetMaxMP( )  );
				ExpendMP( tDecMp, GetEntityID(), RESULT_COST );
			}
		}
		else if ( tpSkillTpl->mCost[ i ].mCostType == CTemplateSkill::COST_HP )
		{
			if ( bIsMagicWeapon )
			{
				tpMW->OnIncHp( (0-tpSkillTpl->mCost[ i ].mCostParam[ 0 ]) );
			}
			else
			{
				//mProperty.SetCurHP( mProperty.GetCurHP( ) - tpSkillTpl->mCost[ i ].mCostParam[ 0 ] );

				//AddFunResult( GetEntityID(), FUNC_DECMP, RESULT_COST, tpSkillTpl->mCost[ i ].mCostParam[ 0 ] , mProperty.GetCurHP( ), mProperty.GetMaxHP( )  );
				ExpendHP( tpSkillTpl->mCost[ i ].mCostParam[ 0 ], GetEntityID(), RESULT_COST );
			}
		}
		// ֻ����Ҳ������ĵ���
		else if ( tpSkillTpl->mCost[ i ].mCostType == CTemplateSkill::COST_ITEM )
		{
			bool tBind = false;
			CPropertyModule::GetSingletonPtr()->PlayerRemoveItemByID( this, tpSkillTpl->mCost[ i ].mCostParam[ 0 ], tpSkillTpl->mCost[ i ].mCostParam[ 1 ], tBind );
			LogEventLostItemByUse(this, 0, tpSkillTpl->mCost[ i ].mCostParam[ 0 ], tpSkillTpl->mCost[ i ].mCostParam[ 1 ]);
		}
		// ֻ����Ҳ������Ļ���
		else if ( tpSkillTpl->mCost[ i ].mCostType == CTemplateSkill::COST_AP )
		{
			CPropertyPlayer* tpProperty = (CPropertyPlayer*) GetProperty();
			if ( tpProperty->IsVip() == false )
			{
				int tAp = tpProperty->GetCurAP();
				tpProperty->SetCurAP( std::max( 0, tAp - tpSkillTpl->mCost[ i ].mCostParam[ 0 ] ) );
				AddFunResult( this->GetEntityID(), FUNC_DECAP, RESULT_NORMAL, true, tpSkillTpl->mCost[ i ].mCostParam[ 0 ], tpProperty->GetCurAP(), tpProperty->GetMaxAP() );
			}
		}
	}
}

// �жϼ��������Ƿ�����
bool CEntityPlayer::CheckSkillCost( CTemplateSkill* tpSkillTpl, bool bIsMagicWeapon /*= false*/ )
{
	LK_ASSERT( tpSkillTpl != NULL, return false );
	CItemMagicWeapon* tpMW = (CItemMagicWeapon*)mProperty.GetEquipment()->GetItemObjPtr( EQUIPMENT_MAGICWEAPON );
	if ( bIsMagicWeapon && tpMW == NULL )
		return false;
	
	// �жϼ��������Ƿ�����
	for ( int i = 0; i < (int)ARRAY_CNT( tpSkillTpl->mCost ); i ++ )
	{
		if ( tpSkillTpl->mCost[ i ].mCostType == (int)CTemplateSkill::COST_HP )
		{
			if ( bIsMagicWeapon )
			{
				if ((int)tpMW->GetHp() < tpSkillTpl->mCost[ i ].mCostParam[ 0 ])
					return false;
			}
			else
			{
				if ((int)mProperty.GetCurHP( ) < tpSkillTpl->mCost[ i ].mCostParam[ 0 ])
					return false;
			}
		}
		else if( tpSkillTpl->mCost[ i ].mCostType == (int)CTemplateSkill::COST_MP )
		{
			if ( bIsMagicWeapon )
			{
				if ((int)tpMW->GetMp() < tpSkillTpl->mCost[ i ].mCostParam[ 0 ])
					return false;
			}
			else
			{
				if ((int)mProperty.GetCurMP( ) < tpSkillTpl->mCost[ i ].mCostParam[ 0 ] )
					return false;
			}
		}

		// ֻ����Ҳ������ĵ���
		else if ( tpSkillTpl->mCost[ i ].mCostType == (int)CTemplateSkill::COST_ITEM )
		{
			if ( mProperty.GetBaggage( )->HasItem( tpSkillTpl->mCost[ i ].mCostParam[ 0 ], tpSkillTpl->mCost[ i ].mCostParam[ 1 ], BIND_ALL ) == false )
			{
				return false;
			}
		}

		// ֻ����Ҳ������Ļ���
		if ( tpSkillTpl->mCost[ i ].mCostType == (int)CTemplateSkill::COST_AP )
		{
			if ( mProperty.IsVip() == false )
			{
				if ((int)mProperty.GetCurAP( ) < tpSkillTpl->mCost[ i ].mCostParam[ 0 ])
					return false;
			}
		}
	}

	return true;
}


// ��鼼��ǰ������
int CEntityPlayer::CheckSpecialUseCondition( CTemplateSkill* tpSkillTpl, bool bIsMagicWeapon /*= false*/ )
{
	CItemMagicWeapon* tpMW = (CItemMagicWeapon*)mProperty.GetEquipment()->GetItemObjPtr( EQUIPMENT_MAGICWEAPON );
	if ( bIsMagicWeapon && tpMW == NULL )
		return ERROR_MW_NOTEQUIP;

	// ���⼼��ʹ�������ж�
	for ( int i = 0; i < (int)ARRAY_CNT( tpSkillTpl->mUseCondition ); i++ )
	{
		switch ( tpSkillTpl->mUseCondition[ i ].mConditionType )
		{
		case CTemplateSkill::SKILL_USECONDITION_NONE:
			{
				return SUCCESS;
			}
		case CTemplateSkill::SKILL_USECONDITION_HPPER:
			{
				if ( bIsMagicWeapon ) // ��������
				{
					int tMaxHP = tpMW->GetMaxHp();
					int tHPPer = (int) ( ( SERVER_PERCENT_FLOAT * tpMW->GetHp() ) / tMaxHP );
					if ( tHPPer <= tpSkillTpl->mUseCondition[ i ].mParam )
					{
						return ERROR_USESKILL_NEEDMORELIFE;
					}
				}
				else
				{
					CPropertyValue tMaxHPValue = CPropertyFormula::GetMaxHP( &mProperty );
					int tMaxHP = tMaxHPValue.mDeltaValue + tMaxHPValue.mInitValue;
					int tHPPer = (int) ( ( SERVER_PERCENT_FLOAT * mProperty.GetCurHP( ) ) / tMaxHP );
					if ( tHPPer <= tpSkillTpl->mUseCondition[ i ].mParam )
					{
						return ERROR_USESKILL_NEEDMORELIFE;
					}
				}
			}
			break;
		case CTemplateSkill::SKILL_USECONDITION_MPPER:
			{
				if ( bIsMagicWeapon ) // ��������
				{
					int tMaxMP = tpMW->GetMaxMp();
					int tMPPer = (int) ( ( SERVER_PERCENT_FLOAT * tpMW->GetMp() ) / tMaxMP );
					if ( tMPPer <= tpSkillTpl->mUseCondition[ i ].mParam )
					{
						return ERROR_USESKILL_NEEDMORELIFE;
					}
				}
				else
				{
					CPropertyValue tMaxMPValue = CPropertyFormula::GetMaxMP( &mProperty );
					int tMaxMP = tMaxMPValue.mDeltaValue + tMaxMPValue.mInitValue;
					int tMPPer = (int) ( ( SERVER_PERCENT_FLOAT * mProperty.GetCurMP( ) ) / tMaxMP );
					if ( tMPPer <= tpSkillTpl->mUseCondition[ i ].mParam )
					{
						return ERROR_USESKILL_NEEDMOREMANA ;
					}
				}
			}
			break;
		case CTemplateSkill::SKILL_USECONDITION_ITEM:
			{
				int tItemNum = mProperty.BaggageHasItem( tpSkillTpl->mUseCondition[ i ].mParam );
				if ( tItemNum <= 0 )
				{
					return ERROR_USESKILL_NEEDMOREITEM ;
				}
			}
			break;
		}
	}

	return SUCCESS;
}


// �����Ƿ����ʹ��
int CEntityPlayer::CanUseSkill( CSkillObject* tpSkillObj, bool bIsMagicWeapon /*= false*/ )
{
	LK_ASSERT( tpSkillObj != NULL, return ERROR_USESKILL_SKILLNOTFOUND );	
	CTemplateSkill *tpSkill = tpSkillObj->GetSkillTpl( );
	if ( tpSkill == NULL )
	{
		return ERROR_USESKILL_SKILLNOTFOUND;
	}
	
	// ���ڰ�̯�����׷���״̬�������ü���
	if( GetServiceStatus() == SERVICE_TRADE || GetServiceStatus() == SERVICE_STALL )
	{
		return ERROR_USESKILL_UNUSE;
	}

	// ������������Ƿ�����
	if ( CheckSkillWeapon( tpSkill ) == false )
	{
		return ERROR_USESKILL_WEAPONNEED;	
	}

	if ( !bIsMagicWeapon )
	{
		// ��������;ö�
		if( CPropertyModule::GetSingletonPtr()->EquipmentAvailable( this , EQUIPMENT_WEAPON ) == false )
		{
			return ERROR_USESKILL_EPTUNAVAILABLE;
		}
	}

	// ��鼼������
	if( CheckSkillCost( tpSkill, bIsMagicWeapon ) == false )
	{
		return ERROR_USESKILL_NEEDMOREMANA;
	}

	// ��鼼����������
	int nSpecailCnd = CheckSpecialUseCondition( tpSkill, bIsMagicWeapon );
	if( nSpecailCnd != SUCCESS )
	{
		return nSpecailCnd;
	}

	// ��鼼����CD
	if (CheckCDGroup( tpSkill->mCDGroup, ARRAY_CNT( tpSkill->mCDGroup ) ) != SUCCESS )
	{
		return ERROR_USESKILL_NOTCOOLDOWN ;
	}

	// ��鼼����ȴ
	if( tpSkillObj->IsCommonCDSkill() &&  ( GetCommonCD() > 0 )  )
	{
		//LOG_DEBUG( "pro", "Entity( %d ) UseSkill( SkillID = %d ) common cd not cool down", this->GetEntityID(), tpSkillObj->GetSkillID() );
		return ERROR_USESKILL_NOTCOOLDOWN;
	}

	if( tpSkillObj->IsCoolingDown() )
	{
		//LOG_DEBUG( "pro", "Entity( %d ) UseSkill( SkillID = %d ) not cool down", this->GetEntityID(), tpSkillObj->GetSkillID() );
		return ERROR_USESKILL_NOTCOOLDOWN;
	}

	// ���Դ�Ѿ���������ô����ʹ��
	if( IsAlive() == false )
	{
		return ERROR_USESKILL_SOURCEDIE;
	}

	if( GetAttackable() == false )
	{
		return ERROR_USESKILL_UNUSE ;
	}

	return SUCCESS;
}

// ������ȴ
void CEntityPlayer::DoSkillCoolDown( CSkillObject* pSkillObject, bool bIsMagicWeapon )
{
	LK_ASSERT( pSkillObject != NULL, return );
	
	// ���㼼����ȴ
	int nTimerOtherInfo[ TIMER_OTHER_INFO ] = {MESSAGE_PROPERTY,0,0,0};

	//if ( pSkillObject->IsCommonCDSkill() )
	//{
	//	// ���ù�����ȴʱ��
	//	nTimerOtherInfo[1] = 0;
	//	mProperty.SetCommonCD( SKILL_COMMON_COOLDOWN );
	//	int nCommonCDTimer = GetTimerReciver()->SetTimer( GetEntityID(), TIMER_SKLL_COOLDOWN, SKILL_COMMON_COOLDOWN, 2, nTimerOtherInfo );
	//	pSkillObject->SetCommonCDTimer( nCommonCDTimer );
	//}

	nTimerOtherInfo[1] = pSkillObject->GetSkillID();
	nTimerOtherInfo[2] = pSkillObject->GetSkillLevel();
	if (bIsMagicWeapon)  // ����Ƿ������� Ҫ���뷨������ID
	{
		CItemObject* tpMW = mProperty.GetEquipment()->GetItemObjPtr( EQUIPMENT_MAGICWEAPON );
		if ( tpMW != NULL )
			nTimerOtherInfo[3] = tpMW->get_id();
		else
			LOG_ERROR("pro", "no mw?? skillid=%d", pSkillObject->GetSkillID() );
	}

	int nTimerID = GetTimerReciver()->SetTimer( GetEntityID(), 
		TIMER_SKLL_COOLDOWN, 
		pSkillObject->GetOriginalCooldown() - pSkillObject->GetReduceCoolFix(),
		4, nTimerOtherInfo );
	pSkillObject->SetCDTimer( nTimerID );
	pSkillObject->SetCooldown( pSkillObject->GetOriginalCooldown() - pSkillObject->GetReduceCoolFix() );
}

// ���npc���� ��������������
void CEntityPlayer::InterruptNpcService()
{
	
}

// ��鼼�������Ƿ�����
bool CEntityPlayer::CheckSkillWeapon( CTemplateSkill* tpSkillTpl )
{
	LK_ASSERT( tpSkillTpl != NULL, return false );

	// ����Ƿ������� ���������������� ֱ�ӷ���true
	if ( tpSkillTpl->mIsMagicWeaponSkill == 1 && tpSkillTpl->mRequireWeapon == CTemplateWeapon::WEAPON_UNLIMIT )
		return true;
	
	// �жϼ��ܹ�����ʽ
	int tWeaponType = 0;
	CItemObject* tpWeapon = mProperty.GetEquipment( )->GetItemObjPtr( EQUIPMENT_WEAPON );
	if ( tpWeapon == NULL )
		return false;

	CTemplateWeapon* tpWeaponTpl = ( CTemplateWeapon* ) CDataStatic::SearchTpl( tpWeapon->GetItemID() );
	if ( tpWeaponTpl == NULL )
		return false;     	
	tWeaponType = tpWeaponTpl->mWeaponType;

	// ���������������������Ҫ��
	if ( tpSkillTpl->mRequireWeapon != CTemplateWeapon::WEAPON_UNLIMIT && tWeaponType != CTemplateWeapon::WEAPON_UNLIMIT && 
		tpSkillTpl->mRequireWeapon != tWeaponType )
		return false;

	return true;
}

int CEntityPlayer::RefreshCDGroup( int *vCDGroup, int vNum )
{
	for ( int i = 0; i < vNum; i++ )
	{
		if ( vCDGroup[ i ] == 0 )
			break;
		if ( vCDGroup[ i ] < 0 || vCDGroup[ i ] > ( CDGROUP - 1 ) )
			continue;
		CTemplateCDGroupTable *tplTable = (CTemplateCDGroupTable*)CDataStatic::GetTemp( TEMP_CDGROUP );
		if ( tplTable == NULL )
			continue;

		CGroupCD& rGroupCD = mProperty.GetCDGroupList().GetGroupCD( vCDGroup[ i ] );
		rGroupCD.SetCDTime( tplTable->mCDTime[ vCDGroup[ i ] ] );

		int nOtherInfo[4] = { MESSAGE_PROPERTY, rGroupCD.GetCDGroupIdx(), 0, 0 };

		//���֮ǰ��cd
		if( rGroupCD.GetTimerID() != INVALID_OBJ_ID )
		{
			GetTimerReciver()->ClearTimer( rGroupCD.GetTimerID() );
		}

		int nTimerID = GetTimerReciver()->SetTimer( GetEntityID(), TIMER_CDGROUP, rGroupCD.GetCDTime(), 2, nOtherInfo ); 
		rGroupCD.SetTimerID( nTimerID );
	}
	return SUCCESS;
}

// ���CD��
int CEntityPlayer::ClearCDGroup( int *nCDGroup, int nNum )
{
	for ( int i = 0; i < nNum; i++ )
	{
		if ( nCDGroup[ i ] == 0 )
			break;
		if ( nCDGroup[ i ] < 0 || nCDGroup[ i ] > ( CDGROUP - 1 ) )
			continue;
		CTemplateCDGroupTable *tplTable = (CTemplateCDGroupTable*)CDataStatic::GetTemp( TEMP_CDGROUP );
		if ( tplTable == NULL )
			continue;

		CGroupCD& rGroupCD = mProperty.GetCDGroupList().GetGroupCD( nCDGroup[ i ] );
		rGroupCD.SetCDTime( 0 );

		//���֮ǰ��cd
		if( rGroupCD.GetTimerID() != INVALID_OBJ_ID )
		{
			GetTimerReciver()->ClearTimer( rGroupCD.GetTimerID() );
			rGroupCD.SetTimerID( INVALID_OBJ_ID );
		}

	}

	return SUCCESS;
}

int CEntityPlayer::CheckCDGroup( int *vCDGroup, int vNum )
{
	for ( int i = 0; i < vNum; i++ )
	{
		if ( vCDGroup[ i ] == 0 )
			break;
		if ( vCDGroup[ i ] < 0 || vCDGroup[ i ] > ( CDGROUP - 1 ) )
			continue;

		CGroupCD& rGroupCD = mProperty.GetCDGroupList().GetGroupCD( vCDGroup[ i ] );
		if ( rGroupCD.GetCDTime( ) > 0 )
			return ERROR_NOTCOOLDOWN;
	}
	return SUCCESS;
}


// ���ͼʱ���buff
int CEntityPlayer::CheckBuffOnChangeMap( CMapObject* vpMap )
{
	CPropertyPlayer* tpProPlayer = (CPropertyPlayer*)GetProperty();
	CBuffList* pBuffList = tpProPlayer->GetBuffList();

	int tRemoveBuffList[ CBuffList::MAX_BUFF_NUM ] = { 0 };
	int tRemoveNumber = 0;

	for( int i = 0; i < pBuffList->GetBuffNum() && tRemoveNumber < ( int )ARRAY_CNT( tRemoveBuffList ); i++ )
	{
		CBuffObject& rBuffObj = pBuffList->GetBuffObjectByIndex( i );
		
		CTemplateBuff* tpBuff = ( CTemplateBuff* ) CDataStatic::SearchTpl( rBuffObj.mBuffID );
		if ( tpBuff == NULL )
		{
			continue;
		}

		if( CheckBuffCondition( tpBuff, vpMap ) == false )
		{
			tRemoveBuffList[ tRemoveNumber ] = tpBuff->mTempID;
			tRemoveNumber++;
			continue;
		}
	}

	for( int i = 0; i < tRemoveNumber && i < ( int )ARRAY_CNT( tRemoveBuffList ); i++ )
	{
		EntityRemoveBuff( tRemoveBuffList[ i ] );
		LogEventLostBuffByChangeMap( this, tRemoveBuffList[ i ]);  // ���ͼʧȥBUFF
	}

	return 0;
}

bool CEntityCharacter::CheckBuffCondition( CTemplateBuff* vpBuff, CMapObject* vpMap )
{
	LK_ASSERT( vpBuff != NULL, return false );
	LK_ASSERT( vpMap != NULL, return false );

	if( vpBuff->mCountryBuff != 0 )
	{
		if( GetLineID( ) != GetNationality( ) )
		{
			return false;
		}	
	}

	if( vpBuff->mBuffMapType != CTemplateBuff::NON_BUFF )
	{
		if( vpMap != NULL )
		{
			switch( vpBuff->mBuffMapType )
			{
				case CTemplateBuff::BATTLE_BUFF:
					{
						if( vpMap->IsBattleMap( ) != true )
						{
							return false;
						}
					}
					break;
				case CTemplateBuff::FB_BUFF:
					{
						if( vpMap->IsFBMap( ) != true )
						{
							return false;
						}
					}
					break;
				case CTemplateBuff::COMM_BUFF:
					{
						if( vpMap->IsCommMap( ) != true )
						{
							return false;
						}

					}
					break;
				case CTemplateBuff::GROUND_BUFF:
					{
						if( vpMap->IsGroundMap( ) != true )
						{
							return false;
						}
					}
					break; 
				default:
					break;
			}
		}
	}

	// �жϵ�ǰBUFF�Ƿ����ض���ͼ�ſ�ʹ�õ�BUFF ( 0 ��ʾȫ��ͼ���� )
	if ( vpBuff->mBuffMapID != 0 )
	{
		if ( GetMapID( ) != vpBuff->mBuffMapID )
		{
			// ��ָ����ͼ,��ɾ��BUFF
			// ��Ϊ�Ƿ������,����ѭ����ɾ����ǰBUFF,����
			//				EntityRemoveBuff( tpBuff->mTempID );
			return false;
		}
	}

	if ( vpBuff->mBuffLineID != 0 )
	{
		// �Ը���Ҫ���⴦����Ϊ���������ж����ÿ���в�ͬ��lineid,�ú����ж������
		if( IS_REPETION_LINE_ID( vpBuff->mBuffLineID ) )
		{
			if( ! IS_REPETION_LINE_ID( GetLineID( ) ) ) 
				return false;
		}
		else
		{
			if ( GetLineID( ) != vpBuff->mBuffLineID )
				return false;
		}
	}

	return true;
}



//************************************
// Method:    DailyCountRefresh
// FullName:  CEntityPlayer::DailyCountRefresh
// Access:    public 
// Returns:   void
// Qualifier: ÿ�ռ��������ݵ���ˢ��
//************************************
void CEntityPlayer::DailyCountRefresh( unsigned int unDate )
{
	if( (unDate != 0) && (unDate != (unsigned int) mProperty.GetSaveDate()) )
	{
		mProperty.SetSaveDate( unDate );
		mProperty.SetInHonPerDay( 0 );
		mProperty.SetOutHonPerDay( 0 );
		mProperty.SetWelfareStatus( 0 );
		//pProperty->SetDiploid( 0 );		
		CActivityModule::GetSingleton().ClearHydrangeaStatus( this );

		//repetion
		CRepetionModule::GetSingletonPtr( )->CleanRepetion( &mProperty );
	}
	
}

//************************************
// Method:   CheckMsgFrequency
// FullName: �����ϢƵ��
// Access:    public 
// Returns:   bool 
// Qualifier: 
//************************************
bool CEntityPlayer::CheckMsgFrequency( int nMsgLimitPerSec, int nCountLimit )
{ 

	if (  ++mMsgCount < nCountLimit )
	{
		return true;
	}

	int tTimeLength = time(NULL) - mFirstMsgTime; 

	if ( tTimeLength == 0 )
	{
		return false;	
	}	
		
	if ( mMsgCount/tTimeLength >= nMsgLimitPerSec )
	{
		return false;
	}
	mMsgCount = 0;
	mFirstMsgTime = time(NULL);
	return true;									
}

// �������� ( ��ʱֻ��PLAYERʹ�� )
void CEntityPlayer::HonorForDie( CEntityCharacter* pSrcEntity )
{
	// ��ʱֻ�����ɱ��ҲŻ�������
	if ( pSrcEntity->IsPlayer() )
	{
		int tpMemberList[ TEAMNUM ] = { 0 };
		CEntityPlayer* tpPlayer = (CEntityPlayer*) pSrcEntity;
		int tRtn = 0, tCount = 0;
		tRtn = CTeamModule::GetSingleton( ).OnGetMemberList( tpPlayer->GetCharID( ), tpMemberList, ARRAY_CNT( tpMemberList ), tCount );
		if ( tRtn < 0 )
		{
			LOG_ERROR( "team", "in honor, get team list failed.id=%d,[%s:%d]", tpPlayer->GetCharID(), __LK_FILE__, __LINE__ );
			return ;
		}
		
		CPropertyModule::GetSingleton( ).PlayerObtainHonor( tpPlayer, this, tpMemberList, tCount );
	}
}

// PK���� ( ��ʱֻ��PLAYERʹ�� )
void CEntityPlayer::PKRuleForDie( CEntityCharacter* pSrcEntity )
{
	// �ж��Ƿ����
	CPropertyModule::GetSingleton( ).CheckPKIsRed( pSrcEntity, this );

	// �������ж��飬��֪�����Ա
	if ( GetTeamFlag( ) > TEAM_NONE )
	{
		//CTeamModule::GetSingleton( ).TeamMemberDie( this );
	}
}



// �����ٻ����߼� ( ��ʱֻ��PLAYER,PETʹ�� ) ���� �⺯��û�ط�����
void CEntityPlayer::PetLogicForDie( )
{
	CPropertyPlayer* pDesProperty = (CPropertyPlayer*) GetProperty( );

	if ( pDesProperty->GetPetID( ) != 0 )
	{
		// �����ٻ���
		pDesProperty->DestroyPetEntity( );
	}
}

void CEntityPlayer::NotifyPropertyRefresh( )
{
	CPropertyPlayer* tpProperty = ( CPropertyPlayer* )GetProperty();	
	CMessage tMessage;
	CMessageRefreshPropertyNotify tPara;
	PBInformation *tpInformation = tPara.mutable_information();
	if ( tpInformation == NULL )
		return;
	PBPropertyValue *tValue;

	tpInformation->set_remainpoint( tpProperty->GetRemainPoint() );
	tpInformation->set_remainskillpoint( tpProperty->GetSkillPoint() );

	tValue = tpInformation->mutable_str();
	tValue->set_initvalue( tpProperty->GetStr( ).mInitValue );
	//if( tpProperty->GetStr( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetStr( ).mDeltaValue );

	tValue = tpInformation->mutable_wis();
	tValue->set_initvalue( tpProperty->GetWis( ).mInitValue );
	//if( tpProperty->GetWis( ).mDeltaValue !=0 )
		tValue->set_deltavalue( tpProperty->GetWis( ).mDeltaValue );
	
	tValue = tpInformation->mutable_spr();
	tValue->set_initvalue( tpProperty->GetSpr( ).mInitValue );
	//if( tpProperty->GetSpr( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetSpr( ).mDeltaValue );
	
	tValue = tpInformation->mutable_con();
	tValue->set_initvalue( tpProperty->GetCon( ).mInitValue );
	//if( tpProperty->GetCon( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetCon( ).mDeltaValue );
	
	tValue = tpInformation->mutable_sta();
	tValue->set_initvalue( tpProperty->GetSta( ).mInitValue );
	//if( tpProperty->GetSta( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetSta( ).mDeltaValue );
	
	tValue = tpInformation->mutable_maxhp();
	tValue->set_initvalue( tpProperty->GetMaxHP( ).mInitValue );
	//if( tpProperty->GetMaxHP( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetMaxHP( ).mDeltaValue );


	tValue = tpInformation->mutable_maxmp();
	tValue->set_initvalue( tpProperty->GetMaxMP( ).mInitValue );
	//if( tpProperty->GetMaxMP( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetMaxMP( ).mDeltaValue );
	
	tValue = tpInformation->mutable_maxap();
	tValue->set_initvalue( tpProperty->GetMaxAP( ).mInitValue );
	//if( tpProperty->GetMaxAP( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetMaxAP( ).mDeltaValue );
	
	tValue = tpInformation->mutable_pattackmax();
	tValue->set_initvalue( tpProperty->GetPAttackMax( ).mInitValue );
	//if( tpProperty->GetPAttackMax( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetPAttackMax( ).mDeltaValue );
	
	tValue = tpInformation->mutable_pattackmin();
	tValue->set_initvalue( tpProperty->GetPAttackMin( ).mInitValue );
	//if( tpProperty->GetPAttackMin( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetPAttackMin( ).mDeltaValue );
	
	tValue = tpInformation->mutable_mattackmax();
	tValue->set_initvalue( tpProperty->GetMAttackMax( ).mInitValue );
	//if(  tpProperty->GetMAttackMax( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetMAttackMax( ).mDeltaValue );
	
	tValue = tpInformation->mutable_mattackmin();
	tValue->set_initvalue( tpProperty->GetMAttackMin( ).mInitValue );
	//if( tpProperty->GetMAttackMin( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetMAttackMin( ).mDeltaValue );

	tValue = tpInformation->mutable_deathrate();
	tValue->set_initvalue( tpProperty->GetDeathRate( ).mInitValue );
	//if( tpProperty->GetDeathRate( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetDeathRate( ).mDeltaValue );

	tValue = tpInformation->mutable_deathvalue();
	tValue->set_initvalue( tpProperty->GetDeathValue( ).mInitValue );
	//if( tpProperty->GetDeathValue( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetDeathValue( ).mDeltaValue );
	
	tValue = tpInformation->mutable_deathdefense();
	tValue->set_initvalue( tpProperty->GetDeathDefense( ).mInitValue );
	//if( tpProperty->GetDeathDefense( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetDeathDefense( ).mDeltaValue );
	
	tValue = tpInformation->mutable_normalduck();
	tValue->set_initvalue( tpProperty->GetNormalDuck( ).mInitValue );
	//if( tpProperty->GetNormalDuck( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetNormalDuck( ).mDeltaValue );
	
	tValue = tpInformation->mutable_skillduck();
	tValue->set_initvalue( tpProperty->GetSkillDuck( ).mInitValue );
	//if( tpProperty->GetSkillDuck( ).mDeltaValue !=0 )
		tValue->set_deltavalue( tpProperty->GetSkillDuck( ).mDeltaValue );
	
	tValue = tpInformation->mutable_ignoreduck();
	tValue->set_initvalue( tpProperty->GetIgnoreDuck( ).mInitValue );
	//if( tpProperty->GetIgnoreDuck( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetIgnoreDuck( ).mDeltaValue );
	
	tValue = tpInformation->mutable_speed();
	tValue->set_initvalue( tpProperty->GetSpeed( ).mInitValue );
	//if( tpProperty->GetSpeed( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetSpeed( ).mDeltaValue );
	
	tValue = tpInformation->mutable_pdefence();
	tValue->set_initvalue( tpProperty->GetPDefence( ).mInitValue );
	//if( tpProperty->GetPDefence( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetPDefence( ).mDeltaValue );

	tValue = tpInformation->mutable_mdefence();
	tValue->set_initvalue( tpProperty->GetMDefence( ).mInitValue );
	//if( tpProperty->GetMDefence( ).mDeltaValue != 0 )
		tValue->set_deltavalue( tpProperty->GetMDefence( ).mDeltaValue );

	tValue = tpInformation->mutable_maxap();
	tValue->set_initvalue( tpProperty->GetMaxAP().mInitValue );
	tValue->set_deltavalue( tpProperty->GetMaxAP().mDeltaValue );

	//if( tpProperty->GetAddFixDamage( ) != 0 )
		tpInformation->set_addfixdamage( tpProperty->GetAddFixDamage( ) );
	//if( tpProperty->GetAddPerDamage( ) != 0 )
		tpInformation->set_addperdamage( tpProperty->GetAddPerDamage( ) );
	//if( tpProperty->GetDecFixPDamage( ) != 0 )
		tpInformation->set_decfixpdamage( tpProperty->GetDecFixPDamage( ) );
	//if( tpProperty->GetDecFixMDamage( ) != 0 )
		tpInformation->set_decfixmdamage( tpProperty->GetDecFixMDamage( ) );
	//if( tpProperty->GetDecPerPDamage( ) != 0 )
		tpInformation->set_decperpdamage( tpProperty->GetDecPerPDamage( ) );
	//if( tpProperty->GetDecPerMDamage( ) != 0  )
		tpInformation->set_decpermdamage( tpProperty->GetDecPerMDamage( ) );
	//if( tpProperty->GetStealHP( ) != 0 )
		tpInformation->set_stealhp( tpProperty->GetStealHP( ) );
	//if( tpProperty->GetStealMP( ) != 0 )
		tpInformation->set_stealmp( tpProperty->GetStealMP( ) );
	//if( tpProperty->GetNormalHitRate( ) != 0 )
		tpInformation->set_normalhitrate( tpProperty->GetNormalHitRate( ) );
	//if( tpProperty->GetSkillHitRate( ) != 0 )
		tpInformation->set_skillhitrate( tpProperty->GetSkillHitRate( ) );
	//if( tpProperty->GetAttackType( ) != 0 )
		tpInformation->set_attacktype( (int)tpProperty->GetAttackType( ) );
	//if( tpProperty->GetSkillPoint() != 0 )
		tpInformation->set_remainskillpoint( tpProperty->GetSkillPoint() );
	//if( tpProperty->GetRemainPoint() != 0 )
		tpInformation->set_remainpoint( tpProperty->GetRemainPoint() );

	for ( int i = 0; i < RES_NUM; i ++ )
	{
		tpInformation->add_resdef( tpProperty->GetResDef( i ) );
		tpInformation->add_resatt( tpProperty->GetResAtt( i ) );
	}

	// ����Ӱ��CD
	CSkillList& pSkillList = tpProperty->GetSkillList();
	for ( int i = 0; i < pSkillList.GetSkillNum(); i++ )
	{
		CSkillObject* pSkillObj = pSkillList.GetSkillObjectByIndex( i );
		if ( pSkillObj->GetReduceCoolFix() > 0 || pSkillObj->GetIncLevel( ) > 0 )
		{
			tpInformation->add_skillindex( i );
			if( pSkillObj->GetReduceCoolFix() != 0 )
				tpInformation->add_reducecool( pSkillObj->GetReduceCoolFix() );
			if( pSkillObj->GetIncLevel( ) != 0 )
				tpInformation->add_inclevel( pSkillObj->GetIncLevel( ) );
		}
	}
	//if( tpProperty->GetReduceLevel( ) != 0 )
		tpInformation->set_reducelevel( tpProperty->GetReduceLevel( ) );
	for( int i = 0; i < WIZARD_NUM; i++ )
	{
		tpInformation->add_equipwizard( tpProperty->GetEquipWizard( i ) );
	}

	tPara.set_entityid( mEntityID );
	tPara.set_curhp( tpProperty->GetCurHP( ) );
	tPara.set_curmp( tpProperty->GetCurMP( ) );
	tPara.set_curap( tpProperty->GetCurAP( ) );
	tPara.set_level( tpProperty->GetLevel( ) );


	tMessage.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_REFRESHPROPERTY );
	tMessage.set_msgpara( ( long ) &tPara );

	// ��ҷ����Լ�
	CSceneLogic::GetSingleton().Send2Player( this, &tMessage );
}



// ����ʹ�ü��ܻ�ִ��Ϣ
void CEntityPlayer::SendUseSkillErrorNotice( int nType )
{
	CMessage tTotalMessage;

	CMessageHead* tpHead = NULL;
	tpHead = tTotalMessage.mutable_msghead();
	if ( tpHead == NULL )
	{
		LOG_DEBUG( "pro", "[ %s : %d ] [ %s ]", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}

	tpHead->set_messageid( ID_S2C_NOTIFY_PROERROR );

	CMessageProErrorNotice tMessage;
	tMessage.set_errorcode( nType );

	tTotalMessage.set_msgpara( (long)&tMessage );

	CSceneLogic::GetSingleton().Send2Player( this, &tTotalMessage );
}

// ʵ������ʱ,���BUFF
void CEntityPlayer::RemoveBuffEntityDie()
{
	CPropertyCharacter* pDesProperty = (CPropertyCharacter*) GetProperty();
	CBuffList *tpBuff = pDesProperty->GetBuffList( );

	for ( unsigned int i = tpBuff->mBuffNumber - 1; i >= 0 && i < ARRAY_CNT( tpBuff->mBuffList ); i-- )
	{
		CTemplateBuff* tpBuffTpl = (CTemplateBuff*) CDataStatic::SearchTpl( tpBuff->mBuffList[ i ].mBuffID );
		if ( tpBuffTpl == NULL )
		{
			LOG_ERROR( "pro", "[ %s : %d ] [ %s ] CTemplateBuff is NULL, TempID = %d", __LK_FILE__, __LINE__, __FUNCTION__, tpBuff->mBuffList[ i ].mBuffID );
			continue;
		}

		if ( tpBuffTpl->mBuffDieDel == CTemplateBuff::BUFF_CANCEL )
		{
			EntityRemoveBuff( tpBuffTpl->mTempID, tpBuff->mBuffList[ i ].mListID );
			LogEventLostBuffByDeath(this,tpBuff->mBuffList[ i ].mBuffID );
			LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] Remove Buff! for ActiveRemoveBuff error test!", __LK_FILE__, __LINE__, __FUNCTION__ );
		}
	}
}

// �ı�����ʱ����buff
void CEntityPlayer::ChangePKBuff( int vOldPKStatus, int vNewPKStatus, int vOldValue, int vNewValue )
{
	if ( vOldPKStatus == PKSTATUS_YELLOW )
	{

	}
	if ( vOldPKStatus == PKSTATUS_RED )
	{

	}
	if ( vNewPKStatus == PKSTATUS_YELLOW )
	{

	}
	if ( vNewPKStatus == PKSTATUS_RED )
	{

	}
}


// �����˫��ʱ��
void CEntityPlayer::OpenActiveDoubleTime( int nRate)
{
	CPropertyPlayer* tpProperty = (CPropertyPlayer*)GetProperty();

	// ���������ȡ����ǿ��ֹͣ���������ʱ��
	int tTimerID = tpProperty->GetDiploidState( TIMEID_STATE );
	if ( tTimerID != 0 )
	{
		GetTimerReciver()->TimeOutOneTimer( tTimerID );
		GetTimerReciver()->ClearTimer( tTimerID );	
		tpProperty->SetDoubleTimerID( 0 );
	}

	tpProperty->SetActivityState( nRate );
}

// �رջ˫��ʱ��
void CEntityPlayer::CloseActiveDoubleTime( )
{
	CPropertyPlayer* tpProperty = (CPropertyPlayer*)GetProperty();

	// ���������ֹͣ�˻˫��˵
	tpProperty->SetActivityState( 0 );

	// ����Ѿ��Ƕ���״̬ 
	if ( tpProperty->IsFreezeDouble() )
	{
		// �Ѿ����ᣬ����Ҫ
		return ;
	}
	// �Ƕ���״̬��Ҫ������ʱ��
	else if ( tpProperty->UnFreezeDouble() )
	{
		// ����������˫��ʱ
		int nTimerOtherInfo[ TIMER_OTHER_INFO ] = {MESSAGE_PROPERTY,0,0,0};
		int tTimerID = this->GetTimerReciver()->SetTimer( this->get_id(), TIMER_DIPLOID_TIME, tpProperty->GetValidDiploid(), 1, nTimerOtherInfo );

		// ��TimerIDά����������������ʱ�������ʱ��
		tpProperty->SetDoubleTimeState( true );	// ����˫������״̬
		tpProperty->SetDoubleFreezeState( false );		// �Ƕ���״̬
		tpProperty->SetDoubleTimerID( tTimerID );
	}

}

int CEntityPlayer::CalProfileCheckSum()
{
	m_nProfileCheckSum = 0;
	// У�� role_id, role_expr, role_money, bounded_money, role_level
	int nRoleID = GetCharID();	
	int nExp = GetExp();
	int nLevel = GetLevel();
	int nMoney = GetMoney();
	int nBindMoney = GetBindMoney();

	m_nProfileCheckSum += CalSum((const char*) &nRoleID, sizeof(int));
	m_nProfileCheckSum += CalSum((const char*) &nExp, sizeof(int));
	m_nProfileCheckSum += CalSum((const char*) &nLevel, sizeof(int));
	m_nProfileCheckSum += CalSum((const char*) &nMoney, sizeof(int));
	m_nProfileCheckSum += CalSum((const char*) &nBindMoney, sizeof(int));

	return m_nProfileCheckSum;
}

int CEntityPlayer::CalDetailCheckSum(const char* from, size_t nSize)
{
	//role_id, role_package, role_storage, role_package_kitbag, role_storage_kitbag
	
	m_nDetailCheckSum += CalSum(from, nSize);

	return m_nDetailCheckSum;
}


void CEntityPlayer::SetFcmStatus (EFcmStatus emStatus) 
{ 
	mFcmStatus = emStatus; 
} 

// �õ�����
CEntityPet* CEntityPlayer::GetPet( )
{
	return (CEntityPet*) CSceneObjManager::GetSingletonPtr()->GetObject( GetPetID() );
}


//// ������ù��Ķ�ʱ����ʱ���Ա���ʣ��ʱ�����
//void CEntityPlayer::TimeoutTimerForSaveData(  )
//{
//	CPropertyPlayer* pPro = (CPropertyPlayer*)GetProperty();
//
//	// cd��
//	for( int i = 0; i < pPro->GetCDGroupList().GetMaxGroupIdx(); i++ )
//	{
//		CGroupCD& rGroupCD = pPro->GetCDGroupList().GetGroupCD( i );
//		if( rGroupCD.GetTimerID() != INVALID_OBJ_ID )
//		{
//			// ��ʱ�������Ḻ��ɾ����ʱ��
//			GetTimerReciver()->TimeOutOneTimer( rGroupCD.GetTimerID() ); 
//		}
//	}
//
//	// ��ʱ����CD
//	CSkillList& pSkillList = pPro->GetSkillList();
//
//	// ����CDʱ��̣ܶ��������,ֱ��ɾ��
//	if( CSkillObject::GetCommonCDTimer() != INVALID_OBJ_ID )
//	{
//		GetTimerReciver()->ClearTimer( CSkillObject::GetCommonCDTimer() );
//	}
//
//	// ��ͨ������Ҫ��ʱ
//	for( int i = 0; i < pSkillList.GetSkillNum(); i++ )
//	{
//		CSkillObject* pSkillObj = pSkillList.GetSkillObjectByIndex( i );
//		if( pSkillObj->GetCDTimer() != INVALID_OBJ_ID )
//		{
//			GetTimerReciver()->TimeOutOneTimer( pSkillObj->GetCDTimer() );
//			GetTimerReciver()->ClearTimer( pSkillObj->GetCDTimer() );
//		}
//	}
//
//	// ����������Ҫ��ʱ
//	CItemMagicWeapon* tpMW = (CItemMagicWeapon*)pPro->GetEquipment()->GetItemObjPtr( EQUIPMENT_MAGICWEAPON );
//	if ( tpMW != NULL )
//	{
//		tpMW->OnStopSkillCD(this);
//	}
//
//	// װ��������Ҫ��ʱ
//	CSkillList* tpSkillList = pPro->GetEquipSkill();
//	LK_ASSERT( tpSkillList != NULL, return );
//	for( int i = 0; i < tpSkillList->GetSkillNum(); i++ )
//	{
//		CSkillObject* pSkillObj = tpSkillList->GetSkillObjectByIndex( i );
//		if( pSkillObj->GetCDTimer() != INVALID_OBJ_ID )
//		{
//			GetTimerReciver()->TimeOutOneTimer( pSkillObj->GetCDTimer() );
//			GetTimerReciver()->ClearTimer( pSkillObj->GetCDTimer() );
//		}
//	}
//
//	// �컯������Ҫ��ʱ
//	tpSkillList = &pPro->mTalentSkill;
//	for( int i = 0; i < tpSkillList->GetSkillNum(); i++ )
//	{
//		CSkillObject* pSkillObj = tpSkillList->GetSkillObjectByIndex( i );
//		if( pSkillObj->GetCDTimer() != INVALID_OBJ_ID )
//		{
//			GetTimerReciver()->TimeOutOneTimer( pSkillObj->GetCDTimer() );
//			GetTimerReciver()->ClearTimer( pSkillObj->GetCDTimer() );
//		}
//	}
//
//	// ��ʱBuff CD
//	CBuffList* pBuffList = pPro->GetBuffList();
//	for( int i = 0; i < pBuffList->GetBuffNum(); i++ )
//	{
//		CBuffObject& rBuffObj =  pBuffList->GetBuffObjectByIndex( i );
//		if( rBuffObj.GetBuffTimerID() != INVALID_OBJ_ID )
//		{
//			GetTimerReciver()->TimeOutOneTimer( rBuffObj.GetBuffTimerID() );
//		}
//	}
//
//
//	// ��˫
//	// set left valid diploid time	
//	if ( pPro->UnFreezeDouble() )
//	{
//		// û�ж���Ļ���˫������ϵͳʱ����ʧ
//		time_t tNow = time( NULL ); 
//		// record off line time
//		pPro->SetLastStopTime( (int) tNow );
//	}
//	
//	if ( pPro->GetDiploidTimerID() != INVALID_OBJ_ID )
//	{
//		GetTimerReciver()->TimeOutOneTimer( pPro->GetDiploidTimerID() );
//		GetTimerReciver()->ClearTimer( pPro->GetDiploidTimerID() );
//	}
//
//	pPro->SetDoubleTimerID( 0 );
//	pPro->SetActivityState( false );
//
//	// �������, ��ɱģʽ������
//	// ������
//	/*if ( pPro->GetYellowTimer() != INVALID_OBJ_ID && GetPKMode() != PKMODE_ALL )
//	{
//		pPro->SetPKStatus( PKSTATUS_WHITE );
//		pPro->SetYellowTimer( LK_ZERO );
//		pPro->SetYellowStatus( false );
//	}*/
//}


// ��ȡ��ʱ����ʣ��ʱ��
void CEntityPlayer::GetLeftTimeofPlayerTimer( )
{

	CPropertyPlayer* pPro = (CPropertyPlayer*)GetProperty();

	// cd��
	pPro->GetCDGroupList().RefreshCDTime();

	// ��ʱ����CD
	pPro->GetSkillList().RefreshCooldown();

	
	// ����������Ҫ��ʱ
	CItemMagicWeapon* tpMW = (CItemMagicWeapon*)pPro->GetEquipment()->GetItemObjPtr( EQUIPMENT_MAGICWEAPON );
	if ( tpMW != NULL )
	{
		CSkillList* tpMWList = tpMW->GetMWSkillList();
		tpMWList->RefreshCooldown();
	}

	// װ��������Ҫ��ʱ
	CSkillList* tpSkillList = pPro->GetEquipSkill();
	LK_ASSERT( tpSkillList != NULL, return );
	tpSkillList->RefreshCooldown();

	// �컯������Ҫ��ʱ
	tpSkillList = pPro->GetTallentSkill();
	LK_ASSERT( tpSkillList != NULL, return );
	tpSkillList->RefreshCooldown();

	// ��ʱBuff CD
	CBuffList* pBuffList = pPro->GetBuffList();
	LK_ASSERT( pBuffList != NULL, return );
	pBuffList->RefreshBuffLeftTime();


	// ��˫
	// set left valid diploid time	
	if ( pPro->UnFreezeDouble() )
	{
		// û�ж���Ļ���˫������ϵͳʱ����ʧ
		pPro->SetLastStopTime( (int)time( NULL ) );
	}

	if ( pPro->GetDiploidTimerID() != INVALID_OBJ_ID )
	{
		int nLeftSec = 0;
		int nLeftMillSec = 0;
		int nGetTimerRet = CTimerMng::GetSingletonPtr()->GetLeftTime( pPro->GetDiploidTimerID(), nLeftSec, nLeftMillSec );

		// cd�黹û�г���24Сʱ��
		if( nGetTimerRet == 0 )
		{
			pPro->SetValidDiploid( nLeftMillSec );
		}
		
	}

}


//************************************
// Method:    IsNewCharacter
// FullName:  CEntityPlayer::IsNewCharacter
// Access:    public 
// Returns:   bool
// Qualifier: �ж��Ƿ����½���ɫ,
//			֮������OnlineTime���жϣ�����Ϊ���ֵ������д��, ���������ݿ��е�ֵ��
//			���û�0������������½��Ľ�ɫ�����¼�һ��Ϊ0��
//************************************
bool CEntityPlayer::IsNewCharacter( )
{
	return ( GetOnlineTime() == 0 );
}


//////////////////////////////////////////////////////////////////////////
//		CEntityNpc
//////////////////////////////////////////////////////////////////////////

// ����ID
unsigned int CEntityNpc::GetOwnerID()
{
	// NPC������Ϊ���Լ�
	return GetEntityID();
}

// �Ƿ�ж�
bool CEntityNpc::IsHostileTo( CEntity* pEntity )
{
	LK_ASSERT( pEntity != NULL, return false );

	// ������Լ�
	if( this == pEntity )
	{
		return false;
	}
    if( pEntity->IsCharacter( ) == true )
    {
        int tSrcCampID = GetCampID( );
        int tDesCampID = ( ( CEntityCharacter* )pEntity )->GetCampID( );

        if( tSrcCampID != 0 && tDesCampID != 0 )
        {
            return tSrcCampID != tDesCampID;
        }
    }

	switch ( pEntity->GetEntityType() )
	{
		case ENTITYTYPE_PLAYER:
			{
				// GM���ܱ�����
				if( CGMModule::GetSingleton().IsGm( ((CEntityPlayer*)pEntity)->GetGmStatus() ) == true  )
				{
					return false;
				}
			}
		case ENTITYTYPE_PET:
			{
				if ( GetOwnCampID() != 0 ) 					
				{
					if ( pEntity->GetNationality() != GetOwnCampID() )
						return true;
					else
						return false;
				}
				if ( GetNationality() == pEntity->GetNationality() )
				{
					if ( ( mPKType & ENEMY_WITH_SC ) == ENEMY_WITH_SC )
					{
						return true;
					}
				}
				else
				{
					if ( ( mPKType & ENEMY_WITH_FC ) == ENEMY_WITH_FC )
					{
						return true;
					}
				}
				break;
			}
		case ENTITYTYPE_OGRE:
		case ENTITYTYPE_FUNCNPC:
		//case ENTITYTYPE_TASKNPC:
			{
				CEntityNpc *pNpc = (CEntityNpc *)pEntity; 
				if ( mGroupID == pNpc->mGroupID )
					return false;
				if ( ( mPKType & ENEMY_WITH_OGRE ) == ENEMY_WITH_OGRE && ( pNpc->mPKType & ENEMY_TO_OGRE ) == ENEMY_TO_OGRE )
				{
					return true;
				}
				break;
			}
		default:
			break;
	}

	return false;
}

// �Ƿ��Ѻ�
bool CEntityNpc::IsFriendlyTo( CEntity* pEntity )
{
	LK_ASSERT( pEntity != NULL, return true );

	// ������Լ�
	if( this == pEntity )
	{
		return true;
	}

	switch ( pEntity->GetEntityType() )
	{
	case ENTITYTYPE_PLAYER:
	case ENTITYTYPE_PET:
		{
			// �����ͬ��
			if ( GetOwnCampID() != 0 ) 
			{
				if ( pEntity->GetNationality() == GetOwnCampID() )
					return true;
				else
					return false;
			}
			if ( GetNationality() == pEntity->GetNationality() ) 
			{
				if( ( mPKType & FRIEND_TO_SC ) == FRIEND_WITH_SC || ( mPKType & NEUTRAL_TO_SC ) == NEUTRAL_WITH_SC )
				{
					return true;
				}
			}
			// �����������
			else
			{
				if( ( mPKType & FRIEND_TO_SC ) == FRIEND_WITH_FC || ( mPKType & NEUTRAL_TO_FC ) == NEUTRAL_WITH_FC )
				{
					return true;
				}
			}
			break;
		}
	case ENTITYTYPE_OGRE:
	case ENTITYTYPE_FUNCNPC:
		{
			CEntityNpc *pNpc = (CEntityNpc *)pEntity; 
			if ( mGroupID == pNpc->mGroupID )
				return true;
			if ( ( mPKType & ENEMY_WITH_OGRE ) == ENEMY_WITH_OGRE )
			{
				return false;
			}
			break;
		}
	default:
		break;
	}

	return true;
}

// �Ƿ����
bool CEntityNpc::IsTeamTo(CEntity *pEntity)
{
	return false;
}

// �Ƿ���ͬһ�����Ա
bool CEntityNpc::IsFamilyTo( CEntity* pEntity )
{
	return false;
}

// �Ƿ�����ʵ��ж�
bool CEntityNpc::IsHostileToPlayers()
{
	return false;
}

// ���״̬
int CEntityNpc::GetTeamFlag( )
{
	return TEAM_NONE;
}


void CEntityNpc::TimeForDie( )
{
	if ( IsPet() || IsFunNpc() )
	{
		int nTimerOtherInfo[ TIMER_OTHER_INFO ] = {MESSAGE_PROPERTY,0,0,0};
		GetTimerReciver()->SetTimer( get_id(), TIMER_ENTITY_DISAPPER, GetProperty( )->GetDisapperaTimer( ), 1, nTimerOtherInfo );
		if ( mNpcChangeState == 1 ) // ����Ǳ��NPC ����־
		{
			LOG_NOTICE("default", "***ChangedNpcDie2 NPCID=%d entityid=%d", GetNpcID(), GetEntityID() );
		}
	}
}






void CEntityNpc::NotifyPropertyRefresh( )
{
	CPropertyNPC* tpProperty = ( CPropertyNPC* )GetProperty();	

	CMessage tMessage;
	CMessageRefreshPropertyNotify tPara;
	PBInformation *tpInformation = tPara.mutable_information();
	PBPropertyValue *tValue;

	tValue = tpInformation->mutable_maxhp();
	tValue->set_initvalue( tpProperty->GetMaxHP( ).mInitValue );
	tValue->set_deltavalue( tpProperty->GetMaxHP( ).mDeltaValue );

	tValue = tpInformation->mutable_maxmp();
	tValue->set_initvalue( tpProperty->GetMaxMP( ).mInitValue );
	tValue->set_deltavalue( tpProperty->GetMaxMP( ).mDeltaValue );

	tPara.set_entityid( mEntityID );
	tPara.set_curhp( tpProperty->GetCurHP( ) );
	tPara.set_curmp( tpProperty->GetCurMP( ) );
	tPara.set_level( tpProperty->GetLevel( ) );


	tMessage.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_REFRESHPROPERTY );
	tMessage.set_msgpara( ( long ) &tPara );

	if ( this->IsOgre() || this->IsFunNpc() || this->IsBox() || this->IsPet() )
	{
		// npc ������Χ���
		CMapModule::GetSingletonPtr()->MessageBroadCast( this, &tMessage );
	}
}

// ��ȡ����
const char* CEntityNpc::GetName()
{
	CTemplateOgre* tpOgreTpl = (CTemplateOgre*) CDataStatic::SearchTpl( GetProperty()->GetPropertyTempID() );
	if ( tpOgreTpl == NULL )
		return NULL;

	return tpOgreTpl->mName;
}


//////////////////////////////////////////////////////////////////////////
//		CEntityOgre
//////////////////////////////////////////////////////////////////////////
bool CEntityOgre::IsHostileTo( CEntity* pEntity )
{
	return CEntityNpc::IsHostileTo( pEntity );
}


// �Ƿ��Ѻ�
bool CEntityOgre::IsFriendlyTo( CEntity* pEntity )
{
	return CEntityNpc::IsFriendlyTo( pEntity );
}

// �Ƿ����
bool CEntityOgre::IsTeamTo(CEntity *pEntity)
{
	return false;
}

// �Ƿ�ͬһ�����Ա
bool CEntityOgre::IsFamilyTo( CEntity* pEntity )
{
	return false;
}

// �Ƿ�����ʵ��ж�
bool CEntityOgre::IsHostileToPlayers()
{
	return true;
}

// ����ʵ��
unsigned int CEntityOgre::GetOwnerID()
{
	// OGRE������Ϊ���Լ�
	return GetEntityID();
}


// �ô�����Ϊʵ�帳ֵ
bool CEntityOgre::Setup( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos, bool bInit, int vNpcID )
{
	if( pCreator->GetCreatorType() != GetEntityType( ) )
	{
		return false;
	}

	COgreCreator *tpCreator = CCreatureRefresher::GetSingleton().OnMutiMapRefreshEvent( (COgreCreator*)pCreator );
	COgreCreator *pOgreCreator = (COgreCreator*)pCreator;
	if ( tpCreator != NULL )
	{
		pOgreCreator = tpCreator;		
	}
	// creatoridҪ���ܵ�ID
	mCreatorID = pCreator->get_id();

	int tRand = RAND(SERVER_PERCENT_INT);
	short tLow = 0;
	short tHigh = 0;

	// �������õĸ���ˢ��
	if ( vNpcID == 0 )
	{
		for ( int i = 0; i < pOgreCreator->mRCount1; i++ )
		{
			tLow += ( i == 0 ) ? 0 : pOgreCreator->mRefresh1[ i - 1 ].mOgreRand;
			tHigh += pOgreCreator->mRefresh1[ i ].mOgreRand;
			if ( tRand >= tLow && tRand <= tHigh )
				mNpcID = pOgreCreator->mRefresh1[ i ].mOgreID;
		}
	}
	// ���ָ����NpcID
	else
	{
		mNpcID = vNpcID;
	}
				
	if ( mNpcID == 0 )
		return false;

	mLineID = usLineID;
	mMapID = usMapID;
	mIndex = usMapIndex;
	if ( *pPos != CWTPoint( 0, 0 ) )
	{
		mPos = *pPos;
	}
	else
	{
		mPos = pOgreCreator->mPosition;
	}
	CTemplateNpc *tplOgre = (CTemplateNpc *)CDataStatic::SearchTpl( mNpcID );
	if ( tplOgre != NULL )
	{
		mPKType = tplOgre->mPKType;
		mGroupID = tplOgre->mGroupID;
		if ( tplOgre->mLmtLineID != 0 && tplOgre->mLmtLineID != usLineID )
		{
			return false;
		}
		mOwnCampID = tplOgre->mWarCamp;
	}
	else
	{
		mPKType = 0;
		mGroupID = 0;
	}		

	// ���ô��ʱ��
	for ( int i = 0; i < pOgreCreator->mRCount2; i++ )
	{
		if ( (int)mNpcID == pOgreCreator->mRefresh2[ i ].mOldID )
		{
			mOccurTime = pOgreCreator->mRefresh2[ i ].mTime;
			mOccurTimer = pOgreCreator->mRefresh2[ i ].mTime;
		}
	}

	// �ж��ض�NPC����ˢ��
	for ( int i = 0; i < pOgreCreator->mRCount7; i++ )
	{
		CCreator* tpCreator = CCreatorManager::GetSingletonPtr()->GetCreator( pOgreCreator->mRefresh7[ i ] );
		if ( tpCreator != NULL && tpCreator->mHasOgre != 0 )
		{
			return false;
		}
	}
	
	// �ж��ض�NPC���ˢ��
	for ( int i = 0; i < pOgreCreator->mRCount8; i++ )
	{
		CCreator* tpCreator = CCreatorManager::GetSingletonPtr()->GetCreator( pOgreCreator->mRefresh8[ i ] );
		if ( tpCreator != NULL && tpCreator->mHasOgre == 0 )
		{
			return false;
		}
	}

	mEntityID = this->get_id( );
//	SetEntityType( ENTITYTYPE_OGRE );	
	mSuperState = false;
	//mMoveable = true;
	//mControlable = true;
	mDirection = pOgreCreator->mDirection;
	mMotionState = MOTION_IDLE;
	mAliveState = ALIVE_NORMAL;
	mHasTarget = false;
	mOrginPos = mPos;	
	mOrginMapID = mMapID;

	GetProperty()->SetEntityID( this->get_id( ) );
	GetProperty()->SetPropertyTempID( mNpcID );
	SetNationality(usLineID);	

	//CSceneLogic::GetSingleton( ).CreateEntity( this, pOgreCreator );

	// �ӳ�ˢ��
	//CCreatureRefresher::GetSingletonPtr()->OnPossibilityRefreshEvent( pOgreCreator, usMapIndex );
	if( IsOgre() || ( IsBlock() )|| ( IsBox() ))
	{
		GetProperty()->Refresh( true );
		//TODO: ���ﲻ��ˢ�£���Ϊ���Ǹոմ����ģ��м�û�иı䣬���иı����ٵ�ˢ��Ҳ���ٰ�
		//NotifyPropertyRefresh( );
	}

	// ��¼ˢ��״��ҲҪ���ܵ�
	pCreator->mHasOgre = mEntityID;
	
	// ��¼����ʱ���
	mCreateTime = LINEKONG::GetTickCount();	

	return true;

}


// ***************************************************************
//  Function:		��Ŀ��ʵ����뵽�ɼ���
//  Description:	AddViewEntity
//	Input:			pTarget - Ŀ��
//	OutPut:			��
//	Return:			true - ��ӳɹ��� false - û�����
//	Others:			������˼��˽��ɼ���Ҳ���ٻ��޽���
//  Date:			11/26/2008
// 
// ***************************************************************
bool CEntityNpc::AddViewEntity(CEntity* pTarget)
{
	LK_ASSERT( pTarget != NULL, return false );

	if( this == pTarget )
	{
		return false;
	}

	// �����
	if(  pTarget->IsPlayer() )
	{
		mSeenPlayerContainer.Add( pTarget->GetEntityID() );

#ifdef _DEBUG_
		mSeenPlayerContainer.Show( "map" );
#endif
	}
	else if( pTarget->IsCharacter() )
	{
		// Ŀǰֻ�ӵжԹ�ϵnpc
		if( this->IsHostileTo( pTarget ) )
			mSeenNpcContainer.Add( pTarget->GetEntityID() );
		else
			return false;

#ifdef _DEBUG_
		mSeenNpcContainer.Show( "map" );
#endif

	}
	else
	{
		return false;
	}

#ifdef _DEBUG_
	LOG_DEBUG( "map", "add %d(%d,%d) to Entity %d(%d,%d)", 
		pTarget->GetEntityID(), pTarget->GetPosX(), pTarget->GetPosY(),
		this->GetEntityID(), this->GetPosX(), this->GetPosY());
#endif

	// npc��Ұ������һ��ʵ��
	if( mSeenPlayerContainer.mPlayers.size() + mSeenNpcContainer.mNpcCharactors.size() == 1 )
	{
		// ���ѹ���
		CNpcModule::GetSingletonPtr()->OnSleep( this, false );
	}

	return true;
}

// ***************************************************************
//  Function:		��Ŀ��ʵ��ӿɼ���ɾ��
//  Description:	DeleteViewEntity
//	Input:			pTarget - Ŀ��
//	OutPut:			��
//	Return:			true - ɾ���ɹ��� false - û��ɾ��
//	Others:
//  Date:			11/26/2008
// 
// ***************************************************************
bool CEntityNpc::DeleteViewEntity(CEntity *pTarget)
{
	LK_ASSERT( pTarget != NULL, return false );

	if( pTarget == this )
	{
		return false;
	}

	if(  pTarget->IsPlayer() )
	{
		mSeenPlayerContainer.Remove( pTarget->GetEntityID() );
	}
	else if( pTarget->IsCharacter() )
	{
		if( this->IsHostileTo( pTarget ) )
		{
			mSeenNpcContainer.Remove( pTarget->GetEntityID() );
		}
	}
	else
	{
		return false;
	}

#ifdef _DEBUG_
	LOG_DEBUG( "map", "delete %d from Entity %d", pTarget->GetEntityID(), this->GetEntityID());

	mSeenPlayerContainer.Show( "map" );
#endif

	// ��Ұû��
	if ( mSeenPlayerContainer.mPlayers.empty() && mSeenNpcContainer.mNpcCharactors.empty() )
	{
		// �ù�������
		CNpcModule::GetSingletonPtr()->OnSleep( this, true  );
	}

	return true;
}


int CEntityNpc::ChangeNpcByLevel( unsigned int vLevel )
{
	((CPropertyCharacter*)(GetProperty()))->SetLevel( vLevel );
	( ( CPropertyNPC* )GetProperty( ) )->SetTranChangeLevel( vLevel );
	GetProperty()->Refresh( true );
	NotifyPropertyRefresh( );
	return 0;
}


void CEntityOgre::ExpForDie( CEntityCharacter* pSrcEntity )
{
	// ֻ��PLAYERɱ��,�ż��㾭��  �ٻ��޸�����, �������������Ҳ�о���
	if ( !pSrcEntity->IsPlayer() && !pSrcEntity->IsPet() && !pSrcEntity->IsPedal() )
	{
		return;
	}

	CPropertyCharacter* pDesProperty = (CPropertyCharacter*) GetProperty();

	// ȡ������ʵ�壬�϶�����
	CEntityPlayer* pSrcOwner = (CEntityPlayer*)pSrcEntity->GetOwner();
	if( pSrcOwner == NULL )
	{
		return;
	}

	CTemplateOgre* tpTempOgre = (CTemplateOgre*) CDataStatic::SearchTpl( pDesProperty->GetPropertyTempID( ) );
	if ( tpTempOgre == NULL )
	{
		LOG_DEBUG( "pro", "EntityDie:Ogre id = %d not found", pDesProperty->GetPropertyTempID( ) );
		return;
	}			

	// ���tTeamList��EntityIDʵ����CharID
	CDamage tTeamList[ DAMAGELIMIT ];
	memset( tTeamList, 0, sizeof( CDamage ) * DAMAGELIMIT );
	int tTeamSize = 0;
	int tMaxDam = 0;
	int tMaxTeam =0;
	int tTotalDam = 0;
	CDamageList* tpDamageList = pDesProperty->GetDamageList( );

	// ά��һ��ɱ���б�(�϶����ڵ�ǰ������)
	int tKillerList[ DAMAGELIMIT ] = { 0 };

	for ( int i = 0; i < tpDamageList->mNumber; i++ )
	{
		int tIndex = tTeamSize;
		CEntity* tpEntity = CSceneLogic::GetSingletonPtr()->GetEntity( tpDamageList->mDamage[ i ].mSrcEntityID );
		if ( tpEntity == NULL )
			continue;

		// ֻ����ң��ٻ��ޣ������������ż��㽱��(����,....)
		if ( (!tpEntity->IsPlayer()) && (!tpEntity->IsPet()) && (!tpEntity->IsPedal()) )
		{
			continue;
		}		

		CEntityPlayer* tDamager = (CEntityPlayer*)tpEntity->GetOwner();
		if( tDamager == NULL )
		{
			continue;
		}

		if ( tDamager->IsAlive( ) == false )
			continue;
		bool tFind = false;
		int tTeamFlag = 0;	// ��ʾ��Ҷ���״̬

		if ( CTeamModule::GetSingleton().InTeam( tDamager->GetCharID() ) == 0 )
			// �޶���ʱΪ�����ɫID
			tTeamFlag = tDamager->GetCharID();
		else
			// ������ʱΪ�����е�һ����ǰ�������������charid
			tTeamFlag = CTeamModule::GetSingleton().GetLocalFirstOLMemberID( tDamager->GetCharID() );

		for ( int j = 0; j < tTeamSize; j++ ) 
		{
			if ( tTeamList[ j ].mSrcEntityID == tTeamFlag )
			{
				tIndex = j;
				tFind = true;
				break;
			}
		}
		if ( tFind == false )
			tTeamSize++;
		tKillerList[ tIndex ] = tDamager->GetCharID();
		tTeamList[ tIndex ].mSrcEntityID = tTeamFlag;
		tTeamList[ tIndex ].mDamageValue += tpDamageList->mDamage[ i ].mDamageValue;
		tTotalDam += tpDamageList->mDamage[ i ].mDamageValue;
		if ( tMaxDam < tTeamList[ tIndex ].mDamageValue )
		{
			tMaxDam = tTeamList[ tIndex ].mDamageValue;
			tMaxTeam = tTeamList[ tIndex ].mSrcEntityID;
		}
	}
	int tExp = tpTempOgre->mExp;
	CTemplateOgreTran* pTemplateOgreTran = (CTemplateOgreTran*) CDataStatic::SearchTpl( tpTempOgre->mTranID );
	if ( pTemplateOgreTran != NULL )
	{
		CPropertyCharacter* tpCharacter = ( CPropertyCharacter* )GetProperty( );
		int tChangeLevel = tpCharacter->GetTranChangeLevel( );
//		tExp = pTemplateOgreTran->mExp[ pDesProperty->GetLevel( ) ];
		tExp = pTemplateOgreTran->mExp[ tChangeLevel ];
	}
	for ( int i = 0; i < tTeamSize; i++ )
	{
		// ���㾭���ȡ
		int	tFinalExp	= 0;
		// �����ӳ�Ա�б�
		// Ϊ2B����ĳ�CharID
		int tpMemberList[ TEAMNUM ] = { 0 };
		int tCount = 0;
		
		CEntityPlayer *pPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tKillerList[ i ] );
		if( pPlayer == NULL)
		{
			continue;
		}
		CTeamModule::GetSingletonPtr()->OnGetMemberList( tTeamList[ i ].mSrcEntityID, tpMemberList, ARRAY_CNT(tpMemberList), tCount );
		
		tFinalExp = (int) ( tExp * pDesProperty->GetLastHPPer( ) * tTeamList[ i ].mDamageValue / (float)tTotalDam / 100.0 );

		// ��һ�þ���
		if ( tFinalExp > 0 )
		{
			CPropertyModule::GetSingleton( ).PlayerObtainExp( 
							pPlayer, tFinalExp, 0, tpMemberList, tCount, pDesProperty->GetLevel( ), this );

			/* ��ɱ�ֻ�þ����¼�ڽӿ�����
			if ( nFinalExp > 0)
			{
				LogEventGetExpByEntityDie( pPlayer, tFinalExp, nFinalExp, tCount, tpTempOgre->mTempID);
			}
			*/
		}
	}

	DropForDie( pSrcOwner, tMaxTeam );
}



// ��������,������Ʒ ( ��ʱֻ��OGRE�� )
void CEntityOgre::DropForDie( CEntityCharacter* pSrcEntity, int vMaxTeam )
{
	//CPropertyCharacter* pSrcProperty = (CPropertyCharacter*) pSrcEntity->GetProperty( );
	CPropertyCharacter* pDesProperty = (CPropertyCharacter*) GetProperty( );

	CTemplateOgre* tpTempOgre = (CTemplateOgre*) CDataStatic::SearchTpl( pDesProperty->GetPropertyTempID( ) );
	if ( tpTempOgre == NULL )
	{
		LOG_ERROR( "pro", "EntityDie:Ogre id = %d not found", pDesProperty->GetPropertyTempID( ) );
		return;
	}

	CEntity* tpOwnerEntity = pSrcEntity;

	// ���ȼ������
	if ( tpTempOgre->mDropType == 1 ) 
	{
		// �������BOSS��ô���ڵ�һ���Ըù�������˺������
		// TODO ���FirstEntityIDΪ�ٻ���,��ѹ�����������
		CEntityCharacter* tpTmpEntity = (CEntityCharacter*) CSceneLogic::GetSingleton( ).GetEntity( pDesProperty->GetFirstEntityID( ) );
		if ( tpTmpEntity != NULL )
		{
			// ����
			tpOwnerEntity = tpTmpEntity->GetOwner();
		}
	}

	if ( tpTempOgre->mDropType != 1 )
	{
		// �����BOSS
		tpOwnerEntity = CSceneLogic::GetSingleton( ).GetPlayerByCharID( vMaxTeam );
	}

	if ( tpOwnerEntity != NULL )
	{
		CPropertyModule::GetSingleton( ).DropItemByNpcDie( tpOwnerEntity, this, tpTempOgre );
	}
}

// ����������� ( ��ʱֻ��OGRE,FUNCNPC,PET�� )
void CEntityOgre::TimeForDie( )
{
	CPropertyNPC* pDesProperty = (CPropertyNPC*) GetProperty( );

	// ����Ǵ��ˢ�µĹ������Ҫɾ�����ˢ�¶�ʱ��
	if( GetOccurTime() > 0 )
	{
		GetTimerReciver()->ClearTimer(  TIMER_ENTITY_ALIVE_REFRESH );
	}

	pDesProperty->SetDisappearTimer( pDesProperty->GetDisapperaTime( ) );

	int nTimerOtherInfo[ TIMER_OTHER_INFO ] = {MESSAGE_PROPERTY,0,0,0};

	GetTimerReciver()->SetTimer( get_id(), TIMER_ENTITY_DISAPPER, pDesProperty->GetDisapperaTimer( ), 1, nTimerOtherInfo );

	// ��ĳһ����ˢ�ּ���ˢ��,
	CCreatureRefresher::GetSingletonPtr()->OnNumericalRefreshEvent( this );


}



//////////////////////////////////////////////////////////////////////////
//		CEntityFuncNpc
//////////////////////////////////////////////////////////////////////////
bool CEntityFuncNpc::Setup( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos, bool bInit, int vNpcID )
{
	int			tNpcID = 0;
	CWTPoint	tPosition;
	EDirType	tDirection;
	// ����ǹ���NPC
	if ( pCreator->GetCreatorType( ) == ENTITYTYPE_FUNCNPC )
	{
		CNpcCreator* pNpcCreator = (CNpcCreator*) pCreator;

		tNpcID		= pNpcCreator->mNpcID;
		tPosition	= pNpcCreator->mPosition;
		tDirection	= (EDirType) pNpcCreator->mDirection;
		// ����й�����  �Ͱѹ������óɺ͹�����һ��
		if ( pNpcCreator->mOwnerCharID != 0 )
		{
			CEntityPlayer* tpPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( pNpcCreator->mOwnerCharID );
			if (tpPlayer != NULL )
			{
				SetNationality( tpPlayer->GetNationality() );
			}
			else
			{
				LOG_ERROR("pro", "owner can't find? ownerid=%d", pNpcCreator->mOwnerCharID );
			}
		}
		mCreatorID = pNpcCreator->get_id();
		// ��ʾ��������
		mIsShowOwner = pNpcCreator->mIsShowOwner;
		mOwnerCharID = pNpcCreator->mOwnerCharID;
	}
	else if ( pCreator->GetCreatorType( ) == ENTITYTYPE_OGRE )
	{
		//TODO: ����һ��Ǳ����Fuck ��3. Ϊ�˼��ݣ����ǰ��������񷽷�����д

		COgreCreator *tpCreator = CCreatureRefresher::GetSingleton().OnMutiMapRefreshEvent( (COgreCreator*)pCreator );
		COgreCreator *pOgreCreator = (COgreCreator*)pCreator;
		if ( tpCreator != NULL )
		{
			pOgreCreator = tpCreator;
		}

		tPosition = pOgreCreator->mPosition;
		tDirection = (EDirType)pOgreCreator->mDirection;
		mCreatorID = pCreator->get_id();
		int tRand = RAND(SERVER_PERCENT_INT);
		short tLow = 0;
		short tHigh = 0;

		// �������õĸ���ˢ��
		if ( vNpcID == 0 )
		{
			for ( int i = 0; i < pOgreCreator->mRCount1; i++ )
			{
				tLow += ( i == 0 ) ? 0 : pOgreCreator->mRefresh1[ i - 1 ].mOgreRand;
				tHigh += pOgreCreator->mRefresh1[ i ].mOgreRand;
				if ( tRand >= tLow && tRand <= tHigh )
					tNpcID = pOgreCreator->mRefresh1[ i ].mOgreID;
			}
		}
		else
		{
			tNpcID = vNpcID;
		}

		if ( tNpcID == 0 )
			return false;

		for ( int i = 0; i < pOgreCreator->mRCount2; i++ )
		{
			if ( tNpcID == pOgreCreator->mRefresh2[ i ].mOldID )
			{
				mOccurTime = pOgreCreator->mRefresh2[ i ].mTime;
				mOccurTimer = pOgreCreator->mRefresh2[ i ].mTime;
			}
		}
		
		// ��ʾ��������
		mIsShowOwner = pOgreCreator->mIsShowOwner;
		mOwnerCharID = pOgreCreator->mOwnerCharID;
	}

	mEntityID = this->get_id( );
	// �������ˢ��NPC
	SetEntityType( ENTITYTYPE_FUNCNPC );
	mNpcID = tNpcID;
	mLineID =usLineID;
	mMapID = usMapID;
	mIndex = usMapIndex;
	mPos = tPosition;
	mSuperState = false;
	//mMoveable = true;
	//mControlable = true;
	mDirection = tDirection;
	mMotionState = MOTION_IDLE;
	mAliveState = ALIVE_NORMAL;
	mHasTarget = false;
	mOrginMapID = mMapID;
	mOrginPos = mPos;

	SetNationality( usLineID );	

	CTemplateNpc *tplNpc = (CTemplateNpc *)CDataStatic::SearchTpl( mNpcID );
	if ( tplNpc != NULL )
	{
		mPKType = tplNpc->mPKType;
		mGroupID = tplNpc->mGroupID;
		if ( tplNpc->mBidDay != 0 || tplNpc->mCorpsBattle != 0 )
		{
			CActivityModule::GetSingletonPtr()->AddNpcInfo( mNpcID, mEntityID );
		}
		if ( tplNpc->mLmtLineID != 0 && tplNpc->mLmtLineID != usLineID )
		{
			return false;
		}	
		mOwnCampID = tplNpc->mWarCamp;
	}
	else
	{
		mPKType = 0;
		mGroupID = 0;
	}

	GetProperty()->SetEntityID( this->get_id( ) );
	GetProperty()->SetPropertyTempID( mNpcID );
	GetProperty()->Refresh( true );
	//TODO: ���ﲻ��ˢ�£���Ϊ���Ǹոմ����ģ��м�û�иı䣬���иı����ٵ�ˢ��Ҳ���ٰ�
	//NotifyPropertyRefresh( );

	// ��¼����ʱ���
	mCreateTime = LINEKONG::GetTickCount();	
	pCreator->mHasOgre = GetEntityID();

	return true;
}


// ����NPC����
void CEntityFuncNpc::TimeForDie( )
{
	CPropertyNPC* pDesProperty = (CPropertyNPC*) GetProperty( );
	pDesProperty->SetDisappearTimer( pDesProperty->GetDisapperaTime( ) );
	int nTimerOtherInfo[ TIMER_OTHER_INFO ] = {MESSAGE_PROPERTY,0,0,0};
	GetTimerReciver()->SetTimer( get_id(), TIMER_ENTITY_DISAPPER, pDesProperty->GetDisapperaTimer( ), 1, nTimerOtherInfo );
	if ( mNpcChangeState == 1 ) // ����Ǳ��NPC ����־
	{
		LOG_NOTICE("default", "***ChangedNpcDie1 NPCID=%d entityid=%d", GetNpcID(), GetEntityID() );
	}
	// ��ĳһ����ˢ�ּ���ˢ��,
	CCreatureRefresher::GetSingletonPtr()->OnNumericalRefreshEvent( this );
}



//////////////////////////////////////////////////////////////////////////
//		CEntityPet
//////////////////////////////////////////////////////////////////////////
bool CEntityPet::IsHostileTo( CEntity* pEntity )
{
	LK_ASSERT( pEntity != NULL, return false );

	// ������Լ�
	if( this == pEntity )
	{
		return false;
	}

	bool bHostile = true;

	CEntityPlayer* pSrcOwner = (CEntityPlayer*) GetOwner();
	if ( pSrcOwner == NULL )
	{
		bHostile = false;
	}
	else
	{
		bHostile = pSrcOwner->IsHostileTo( pEntity );
	}

	return bHostile;
}


// �Ƿ��Ѻ�
bool CEntityPet::IsFriendlyTo( CEntity* pEntity )
{
	LK_ASSERT( pEntity != NULL, return false );

	// ������Լ�
	if( this == pEntity )
	{
		return true;
	}

	return ! IsHostileTo( pEntity );
}

// �Ƿ����
bool CEntityPet::IsTeamTo(CEntity *pEntity)
{
	return false;
}

// �Ƿ�����ʵ���Ѻ�
bool CEntityPet::IsHostileToPlayers()
{
	return true;
}

// ����ID
unsigned int CEntityPet::GetOwnerID()
{
	// �����ٻ���ID
	return mOwnerID;
}

// ���״̬
int CEntityPet::GetTeamFlag( )
{
	CEntityPlayer* pOwner = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( mOwnerID );
	if( pOwner != NULL )
	{
		return pOwner->GetTeamFlag();
	}
	else
	{
		return TEAM_NONE;
	}
}


bool CEntityPet::Setup(unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos, bool bInit, int vNpcID )
{
	// ������ٻ���
	if ( pCreator->GetCreatorType( ) != ENTITYTYPE_PET )
	{
		return false;
	}
	CPetCreator* tpPetCreator = (CPetCreator*)pCreator;
	int tPosX = tpPetCreator->mPos.mX;
	int tPosY = tpPetCreator->mPos.mY;
	EDirType tDirection = tpPetCreator->mDirection;
	int tNpcID = tpPetCreator->mPetID;

	mEntityID = this->get_id( );
	SetEntityType( ENTITYTYPE_PET );
	mNpcID = tNpcID;

	mLineID = usLineID;
	mMapID = usMapID;
	mIndex = usMapIndex;
	mPos = CWTPoint( tPosX, tPosY );
	mSuperState = false;
	mDirection = tDirection;
	mMotionState = MOTION_IDLE;
	mAliveState = ALIVE_NORMAL;
	mHasTarget = false;
	mOrginPos = mPos;
	mOrginMapID = mMapID;
	mCreatorID= tpPetCreator->get_id();

	mOwnerID = tpPetCreator->mSrcEntityID;
	mOnlineTime = tpPetCreator->mOnlineTime;
	mCurMode = tpPetCreator->mPetMode;
	mCurTargetID = 0;
	
	CPropertyPet* pProPet = ( CPropertyPet* ) GetProperty();

	pProPet->SetEntityID( this->get_id( ) );
	pProPet->SetPropertyTempID( mNpcID );
	
	SetNationality(usLineID);

	// �����ٻ��޵ȼ�Ϊ���˵ȼ�
	CEntity* pOwnerEntity = GetOwner();
	if( (pOwnerEntity != NULL) && pOwnerEntity->IsPlayer() )
	{	
		CPropertyPlayer* pPlayerPro = (CPropertyPlayer*) pOwnerEntity->GetProperty();
		pProPet->SetLevel( pPlayerPro->GetLevel() );
	}

	// ��¼����ʱ���
	if( mOnlineTime == 0 )
	{
		mCreateTime = LINEKONG::GetTickCount();
	}
	else
	{
		mCreateTime = std::max( (int)(LINEKONG::GetTickCount() - mOnlineTime), 0 );
		//����ǿ�������ģ���������������
		CPropertyModule::GetSingletonPtr()->SummonBeastLevelUp( this, 0, false );
	}

	pProPet->Refresh( true );

	return true;
}

void CEntityPet::PetLogicForDie( )
{
	CEntityCharacter* tpOwner = (CEntityCharacter*) GetOwner( );
	if ( tpOwner != NULL )
	{
		CPropertyCharacter* tpProOwner = (CPropertyCharacter*) tpOwner->GetProperty( );
		tpProOwner->SetPetID( 0 );
	}
}


//////////////////////////////////////////////////////////////////////////
//		CEntityPedal
//////////////////////////////////////////////////////////////////////////

bool CEntityPedal::IsHostileTo( CEntity* pEntity )
{
	LK_ASSERT( pEntity != NULL, return false );

	// ������Լ�
	if( this == pEntity )
	{
		return false;
	}

	bool bHostile = true;

	CEntityPlayer* pSrcOwner = (CEntityPlayer*) GetOwner();
	if ( pSrcOwner == NULL )
	{
		bHostile = false;
	}
	else
	{
		bHostile = pSrcOwner->IsHostileTo( pEntity );
	}

	return bHostile;
}


// �Ƿ��Ѻ�
bool CEntityPedal::IsFriendlyTo( CEntity* pEntity )
{
	LK_ASSERT( pEntity != NULL, return false );

	// ������Լ�
	if( this == pEntity )
	{
		return true;
	}

	return ! IsHostileTo( pEntity );
}

// �Ƿ����
bool CEntityPedal::IsTeamTo(CEntity *pEntity)
{
	return false;
}

// �Ƿ�����ʵ��ж�
bool CEntityPedal::IsHostileToPlayers()
{
	return true;
}

// ����ʵ��
unsigned int CEntityPedal::GetOwnerID()
{
	if( mPedalType == PEDAL_TELEPORT )
	{
		return this->GetEntityID();
	}
	else
	{
		// �����ͷ���ID
		return mOwnerID;
	}
}

bool CEntityPedal::Setup(unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator *pCreator , CWTPoint* pPos, bool bInit, int vNpcID )
{
	if ( pCreator->GetCreatorType( ) != ENTITYTYPE_PEDAL )
	{
		return false;
	}

	CPedalCreator* tpPedalCreator = (CPedalCreator*) pCreator;
	int tPosX = tpPedalCreator->mSrcRect.CenterPoint( ).mX;
	int tPosY = tpPedalCreator->mSrcRect.CenterPoint( ).mY;

	mEntityID = get_id( );
	SetEntityType( ENTITYTYPE_PEDAL );
	mNpcID = tpPedalCreator->mTempID;
	mLineID = usLineID;
	mMapID = usMapID;
	mIndex = usMapIndex;
	mPos = CWTPoint( tPosX, tPosY );
	//	mSuperState = false;
	//	mMoveable = true;
	//	mControlable = true;
	mDirection = DIR_DOWN;
	//	mMotionState = MOTION_IDLE;
	mAliveState = ALIVE_NORMAL;
	//	mHasTarget = false;
	//	mOrginPos = mPos;
	mCreatorID= tpPedalCreator->get_id();
	
	// ����������˿ɼ�
	

	SetOwnerID( tpPedalCreator->mSrcEntityID );
	SetSkillID( tpPedalCreator->mSkillID );
	SetSkillLevel( tpPedalCreator->mSkillLevel );
	SetTeamID( tpPedalCreator->mTeamID );
	SetPedalType( tpPedalCreator->mPedalType );
	
	SetSrcRect( tpPedalCreator->mSrcRect );
	SetActRect( tpPedalCreator->mActRect );

	if ( IsHierogram( ) == true )
	{
		mVisibility = VISIBLITY_ALL;
	}
	else if( IsTeleport( ) == true )
	{
		mVisibility = VISIBLITY_ALL;
	}
	else if( IsTrap( ) == true )
	{
		mVisibility = VISIBLITY_TEAM;
	}
	else if( IsNeedFire( ) == true )
	{
		mVisibility = VISIBLITY_ALL;
	}
	

	// �Ե�ͼ�߽�����ж�
	CMapObject* pMapObj = CMapObjManager::GetSingletonPtr()->GetMapObject(mLineID,mMapID,mIndex);
	if( pMapObj != NULL )
	{
		mSrcRect.mTopLeft.mX = std::max( mSrcRect.mTopLeft.mX, 0 );
		mSrcRect.mTopLeft.mY = std::max( mSrcRect.mTopLeft.mY, 0 );
		mSrcRect.mBottomRight.mX = std::min( mSrcRect.mBottomRight.mX, (int) pMapObj->GetWidth() );
		mSrcRect.mBottomRight.mY = std::min( mSrcRect.mBottomRight.mY, (int) pMapObj->GetHight() );
	}

	SetDstLineID( tpPedalCreator->mLineID );
	SetDstMapID( tpPedalCreator->mMapID );

	if( tpPedalCreator->mPedalType == PEDAL_TELEPORT )
	{
		SetPresistTime( 0 );
		SetSkillID( 0 );
		SetSkillLevel( 0 );
		SetMinLevel( 0 );
		SetRestrictNation( 0 );
		SetDesPos( tpPedalCreator->mDesPos );
	}
	else if( tpPedalCreator->mPedalType == PEDAL_TRAP )
	{
		// ����
		CTemplateTrapSkill* tpTrapTpl = (CTemplateTrapSkill*) CDataStatic::SearchSkill( tpPedalCreator->mSkillID, tpPedalCreator->mSkillLevel );
		if( tpTrapTpl == NULL )
		{
			LOG_ERROR( "pro", "[%s:%d][%s] skill template id = %d ,level = %d not found", 
					__LK_FILE__, __LINE__, __FUNCTION__, tpPedalCreator->mSkillID, tpPedalCreator->mSkillLevel );
		}
		else
		{
			SetPresistTime( tpTrapTpl->mLastTime );
			SetSkillID( tpPedalCreator->mSkillID );
			SetSkillLevel( tpPedalCreator->mSkillLevel );
			SetMinLevel( tpPedalCreator->mMinLevel );
			SetSrcEntityID( tpPedalCreator->mSrcEntityID ); 
		}
	}
	else if( tpPedalCreator->mPedalType == PEDAL_HIEROGRAM )
	{
		//���
		CTplHierogram* tpTpl = ( CTplHierogram* )CDataStatic::SearchTpl( tpPedalCreator->mTempID );
		LK_ASSERT_STR( tpTpl != NULL, return false, "TempID %d", tpPedalCreator->mTempID );
		SetPresistTime( tpTpl->mAlive * 1000 );
		SetSrcEntityID( tpPedalCreator->mSrcEntityID );
	}
	else if(tpPedalCreator->mPedalType == PEDAL_NEEDFIRE )
	{
		// ����
		CTemplateTrapSkill* tpTrapTpl = (CTemplateTrapSkill*) CDataStatic::SearchTpl( tpPedalCreator->mTempID );
		if( tpTrapTpl == NULL )
		{
			LOG_ERROR( "pro", "[%s:%d][%s] skill template id = %d ,level = %d not found", 
				__LK_FILE__, __LINE__, __FUNCTION__, tpPedalCreator->mSkillID, tpPedalCreator->mSkillLevel );
		}
		else
		{
			SetPresistTime( tpTrapTpl->mLastTime );
			SetSkillID( tpPedalCreator->mSkillID );
			SetSkillLevel( tpPedalCreator->mSkillLevel );
			SetMinLevel( tpPedalCreator->mMinLevel );
			SetSrcEntityID( tpPedalCreator->mSrcEntityID ); 
		}
	}

	GetProperty()->SetEntityID( this->get_id( ) );
	GetProperty( )->SetPropertyTempID( tpPedalCreator->mTempID );

	tpPedalCreator->mHasOgre = GetEntityID();
	//CSceneLogic::GetSingleton( ).CreateEntity( tpNpc, pNpcCreator );

	return true;
}



// ***************************************************************
//  Function:		IsVisibleFor 
//  Description:	�Ƿ��Ŀ����ҿɼ�
//	Input:			pTargetPlayer - Ŀ�����
//	OutPut:			��
//	Return:			��
//	Others:			
//  Date:			11/13/2008
// 
// ***************************************************************
bool CEntityPedal::IsVisibleFor( CEntity* pTarget )
{
	LK_ASSERT( pTarget != NULL, return false );

	if( mVisibility == VISIBLITY_SELF )
	{
		return false;
	}
	else if ( mVisibility == VISIBLITY_TEAM )
	{
		CEntityPlayer* pOwner = (CEntityPlayer*) GetOwner();
		LK_ASSERT( pOwner != NULL, return false );

		// �����˿ɼ�
		if( pOwner == pTarget )
		{
			return true;
		}

		return ( pOwner->IsTeamTo( pTarget ) );
	}
	else 
	{
		return true;
	}
}

//////////////////////////////////////////////////////////////////////////
//		CEntityDrop
//////////////////////////////////////////////////////////////////////////

bool CEntityDrop::IsHostileTo( CEntity* pEntity )
{
	return false;
}


// �Ƿ��Ѻ�
bool CEntityDrop::IsFriendlyTo( CEntity* pEntity )
{
	return true;
}

// �Ƿ�����ʵ��ж�
bool CEntityDrop::IsHostileToPlayers()
{
	return false;
}

// �Ƿ����
bool CEntityDrop::IsTeamTo(CEntity *pEntity)
{
	return false;
}

// ����ID
unsigned int CEntityDrop::GetOwnerID()
{
	return GetEntityID();
}






//////////////////////////////////////////////////////////////////////////
//		CEntityMoney
//////////////////////////////////////////////////////////////////////////
bool CEntityMoney::Setup(unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos, bool bInit, int vNpcID )
{
	// ������ǽ�Ǯ
	if ( pCreator->GetCreatorType( ) != ENTITYTYPE_MONEY )
	{
		return false;
	}

	CMoneyCreator* tpDropCreator = (CMoneyCreator*)pCreator;

	CWTPoint tOrginPos = CWTPoint( tpDropCreator->mCenterX, tpDropCreator->mCenterY );

	// ����Ǳ������䣬Ҫ��һ�����λ��
	if ( tpDropCreator->mDropType == DROP_OBJECTIVE )
	{
		CMapModule::GetSingletonPtr()->GetDropPos( usLineID, usMapID, usMapIndex, tOrginPos );
	}
	//TODO: ��ʱû�У��ȴ��ͻ����ϱ�. ������������䣬�жϵ����λ��
	//else if ( tpDropCreator->mDropType == DROP_SUBJECTIVE )
	//{
	//	if ( CMapModule::GetSingletonPtr()->IsStaticBlock( usLineID, usMapID, usMapIndex, tOrginPos ) > 0 )
	//	{
	//		return false;
	//	}
	//	else if ( CMapModule::GetSingletonPtr()->IsOccupied( usLineID, usMapID, usMapIndex, tOrginPos, ENTITYTYPE_MONEY ) )
	//	{
	//		return false;
	//	}
	//}

	mEntityID = this->get_id( );
	SetEntityType( ENTITYTYPE_MONEY );
	mNpcID = 0;

	mLineID = usLineID;
	mMapID = usMapID;
	mIndex = usMapIndex;
	mPos = tOrginPos;
	//	mSuperState = false;
	//	mMoveable = true;
	//	mControlable = true;
	mDirection = DIR_DOWN;
	//	mMotionState = MOTION_IDLE;
	mAliveState = ALIVE_NORMAL;
	//	mHasTarget = false;
	//	mOrginPos = mPos;
	//	mCreatorID= tpDropCreator->get_id();

	//CSceneLogic::GetSingleton( ).CreateEntity( tpNpc, pNpcCreator );
	GetProperty()->SetEntityID( this->get_id( ) );
	CPropertyMoney *pMoney = (CPropertyMoney *)( GetProperty() );
	pMoney->SetMoney( tpDropCreator->mMoney );

	return true;
}


//////////////////////////////////////////////////////////////////////////
//		CEntityItem
//////////////////////////////////////////////////////////////////////////
bool CEntityItem::Setup(unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos, bool bInit, int vNpcID )
{
	if ( pCreator->GetCreatorType( ) != ENTITYTYPE_ITEM )
	{
		return false;
	}

	CItemCreator* pItemCreator = (CItemCreator*)pCreator;

	CWTPoint tOrginPos = CWTPoint( pItemCreator->mCenterX, pItemCreator->mCenterY );

	// ����Ǳ������䣬Ҫ��һ�����λ��
	if ( pItemCreator->mDropType == DROP_OBJECTIVE )
	{
		CMapModule::GetSingletonPtr()->GetDropPos( usLineID, usMapID, usMapIndex, tOrginPos );
	}
	//TODO: ��ʱû�У��ȴ��ͻ����ϱ��� ������������䣬�жϵ����λ��
	//else if ( pItemCreator->mDropType == DROP_SUBJECTIVE )
	//{
	//	if ( CMapModule::GetSingletonPtr()->IsStaticBlock( usLineID, usMapID, usMapIndex, tOrginPos ) > 0 )
	//	{
	//		return false;
	//	}
	//	else if ( CMapModule::GetSingletonPtr()->IsOccupied( usLineID, usMapID, usMapIndex, tOrginPos, ENTITYTYPE_ITEM ) )
	//	{
	//		return false;
	//	}
	//}

	mEntityID = this->get_id( );
	SetEntityType( ENTITYTYPE_ITEM );
	mNpcID = pItemCreator->mItemID;
	mLineID = usLineID;
	mMapID = usMapID;
	mIndex = usMapIndex;
	mPos = tOrginPos;
	mDirection = DIR_DOWN;
	mAliveState = ALIVE_NORMAL;
	mProperty.SetLevel( pItemCreator->mLevel );

	GetProperty()->SetEntityID( this->get_id( ) );

	pItemCreator->mHasOgre = GetEntityID();
	//CSceneLogic::GetSingleton( ).CreateEntity( tpNpc, pNpcCreator );
	
	return true;
}

//////////////////////////////////////////////////////////////////////////
//		CEntityCollect
//////////////////////////////////////////////////////////////////////////
bool CEntityCollect::Setup(unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos, bool bInit, int vNpcID )
{
	if ( pCreator->GetCreatorType( ) != ENTITYTYPE_COLLECT )
	{
		return false;
	}

	CCollectCreator* pCollectCreator = (CCollectCreator*)pCreator;

	mEntityID = this->get_id( );
	mCreatorID = pCollectCreator->get_id( );
	SetEntityType( ENTITYTYPE_COLLECT );
	mNpcID = pCollectCreator->mNpcID;
	mLineID = usLineID;
	mMapID = usMapID;
	mIndex = usMapIndex;
	mPos = pCollectCreator->mPosition[ RAND( pCollectCreator->mPCount ) ];
	mOrginPos = mPos;
	mOrginMapID = mMapID;
	mDirection = DIR_DOWN;
	mAliveState = ALIVE_NORMAL;
	
	SetNationality(usLineID);
	// д��
	mPKType = ( FRIEND_WITH_SC | FRIEND_TO_SC | FRIEND_WITH_FC | FRIEND_TO_FC );

	GetProperty()->SetEntityID( this->get_id( ) );

	//CSceneLogic::GetSingleton( ).CreateEntity( tpNpc, pNpcCreator );
	
	pCollectCreator->mHasOgre = GetEntityID();

	return true;
}



int CEntityCharacter::AddAureoEntityList( CEntityCharacter* pEntity )
{
	if ( pEntity == NULL )
		return -1;

	for ( unsigned int i = 0; i < ARRAY_CNT( mEntityAureoList ); i++ )
	{
		if ( mEntityAureoList[ i ] == NULL )
		{
			mEntityAureoList[ i ] = pEntity;
			return i;
		}

		if ( mEntityAureoList[ i ] == pEntity )
		{
			return i;
		}
	}

	return -1;
}

void CEntityCharacter::ClearAureoEntityList( )
{
	memset( mEntityAureoList, 0, sizeof( mEntityAureoList ) );
}

void CEntityCharacter::RemoveAureoEntityList( CEntityCharacter* pEntity )
{
	int tIndex = -1;
	int tArrayCnt = ARRAY_CNT( mEntityAureoList );
	for ( int i = 0; i < tArrayCnt; i++ )
	{
		if ( mEntityAureoList[ i ] == NULL )
			return;

		if ( mEntityAureoList[ i ] == pEntity )
		{
			tIndex = i;
			break;
		}
	}
	
	// ���ɾ����ʵ������������һλ,�򲻴���,����Ѻ����������ǰ�ƶ�
	if ( tIndex >= 0 && tIndex < ( tArrayCnt - 1 - 1 ) )
	{
		memcpy( &( mEntityAureoList[ tIndex ] ), &( mEntityAureoList[ tIndex + 1 ] ), sizeof( mEntityAureoList[ 0 ] ) * ( tArrayCnt - tIndex - 1 ) );
	}
}

void CEntityCharacter::CheckAureoEntityList( CEntityCharacter** pEntityList, int vEntityCount, CEntityCharacter** pAddEntityList, int& vAddEntityCount, CEntityCharacter** pRemoveEntityList, int & vRemoveEntityCount )
{
	if ( pEntityList == NULL || pAddEntityList == NULL || pRemoveEntityList == NULL )
		return;

	CEntityCharacter* tpTempEntityList[ TEAMNUM ];
	memcpy( tpTempEntityList, mEntityAureoList, sizeof( tpTempEntityList ) );
	
	ClearAureoEntityList();
	
	vAddEntityCount = 0;
	vRemoveEntityCount = 0;

	for ( int i = 0; i < vEntityCount && i < (int)ARRAY_CNT( pEntityList ); i++ )
	{
		if ( pEntityList[ i ] == NULL )
			break;

		bool bIsInsert = false;
		for ( unsigned int j = 0; j < ARRAY_CNT( tpTempEntityList ); j++ )
		{
			if ( tpTempEntityList[ j ] == NULL )
				break;

			if ( pEntityList[ i ] == tpTempEntityList[ j ] )
			{
				AddAureoEntityList( pEntityList[ i ] );
				bIsInsert = true;
				break;
			}
		}

		if ( bIsInsert == false )
		{
			AddAureoEntityList( pEntityList[ i ] );
			pAddEntityList[ vAddEntityCount ] = pEntityList[ i ];
			vAddEntityCount++;
		}
	}
	
	for ( unsigned int i = 0; i < ARRAY_CNT( tpTempEntityList ); i++ )
	{
		if ( tpTempEntityList[ i ] == NULL )
			break;

		bool bIsSame = false;
		for ( unsigned int j = 0; j < ARRAY_CNT( mEntityAureoList ); j++ )
		{
			if ( mEntityAureoList[ j ] == NULL )
				break;

			if ( tpTempEntityList[ i ] == mEntityAureoList[ j ] )
			{
				bIsSame = true;
				break;
			}
		}

		if ( bIsSame == false )
		{
			pRemoveEntityList[ vRemoveEntityCount ] = tpTempEntityList[ i ];
			vRemoveEntityCount++;
		}
	}
}


// ֪ͨ�������� ( CHARACTERʹ�� )
void CEntityCharacter::NotifyDeath( CEntityCharacter* pSrcEntity )
{
	unsigned short tDead = 0;
	unsigned int tEntityID = 0;
	if ( pSrcEntity != NULL && ! pSrcEntity->IsPlayer() )
	{
		tEntityID = pSrcEntity->GetEntityID( );
		tDead = 0;
	}
	else if ( ! IsPlayer() )
	{
		tEntityID = GetEntityID( );
		tDead = 1;
	}

	if ( tEntityID != 0 )
		CNpcModule::GetSingleton( ).OnDead( tEntityID, tDead );
}

// ����ɱ��ȡѪ ( CHARACTERʹ�� )
void CEntityCharacter::KillerRenew( CEntityCharacter* pSrcEntity )
{
	if ( pSrcEntity != NULL )
	{
		CPropertyCharacter* pSrcProperty = (CPropertyCharacter*) pSrcEntity->GetProperty( );

		if ( pSrcProperty->GetStateParam( STATE_KILLERRENEW ).mInState == true )
		{
			CPropertyCharacter* pDesProperty = (CPropertyCharacter*)GetProperty( );
			unsigned int tDesMaxHP = pDesProperty->GetMaxHP( );

			unsigned int tHP = (unsigned int) ( tDesMaxHP * pSrcProperty->GetStateParam( STATE_KILLERRENEW ).mParames1 / SERVER_PERCENT_FLOAT );
			//unsigned int tOldHP = pSrcProperty->GetCurHP( );

			tHP = pSrcEntity->CureHP( tHP, pSrcEntity->GetEntityID(), RESULT_STEALHP );
			//pSrcProperty->SetCurHP( min( ( tOldHP + tHP ), (unsigned int)( pSrcProperty->GetMaxHP( ) ) ) );

			//tHP = pSrcProperty->GetCurHP() - tOldHP;

			//pSrcEntity->AddFunResult( GetEntityID( ), FUNC_INCHP, RESULT_STEALHP, tHP, pSrcProperty->GetCurHP( ), pSrcProperty->GetMaxHP( ) );
		}
	}
}

// ʵ�����BUFF
int CEntityCharacter::EntityInsertBuff( CEntityCharacter* pSrcEntity, CTemplateBuff* pBuffTpl, int nSkillType, int nDamage, int nBuffTime )
{
	if ( pSrcEntity == NULL || pBuffTpl == NULL )
		return ERR_INVALID_PARAMETER;

	CPropertyCharacter* pDesProperty = (CPropertyCharacter*) GetProperty();

	CBuffList *tpBuff = pDesProperty->GetBuffList( );

	CMapObject* tpMapObj = GetMapObject( );
	LK_ASSERT_STR( tpMapObj != NULL, return ERR_UNKNOWN, "Map %d, LineID %d, MapIndex %d", GetMapID( ), GetLineID( ),
		GetMapIndex( ) );

	if( CheckBuffCondition( pBuffTpl, tpMapObj ) == false )
	{
		return ERROR_USESKILL_INSERTBUFF_DISSATISFY;
	}

	// ����Ǹ���BUFF,���ܶ��������ʹ��
	if ( pBuffTpl->mBuffType == CTemplateBuff::BUFF_DEC && pDesProperty->GetStateParam( STATE_IMMUNITYREVERSD ).mInState == true )
	{
		AddFunResult( pSrcEntity->GetEntityID(), FUNC_NONE, RESULT_IMMUNITY );
		return SUCCESS;
	}

	// ������ʵͣ��������
	if ( pBuffTpl->mAccurate != 0 && pBuffTpl->mAccurate < RAND(SERVER_PERCENT_INT) )
	{
		return SUCCESS;
	}
	

	// ���BuffʹĿ�����ս��
	if ( pBuffTpl->mEnableBattle == 1 )
	{
		// ����ս����ʱ��
		if( pSrcEntity->GetAliveStatus( ) == ALIVE_NORMAL )
		{
			pSrcEntity->SetAliveStatus( ALIVE_BATTLE );
			pSrcEntity->AddFunResult( 0, FUNC_BATTLE, RESULT_NORMAL );
		}

		if( GetAliveStatus( ) == ALIVE_NORMAL )
		{
			SetAliveStatus( ALIVE_BATTLE );
			AddFunResult( 0, FUNC_BATTLE, RESULT_NORMAL );

			// ����˺��б� ������
			CDamageList *tpDamageList = pDesProperty->GetDamageList( );
			tpDamageList->ClearDamage( );
		}
	}

	// ����Ǹ���BUFF
	if ( pBuffTpl->mBuffType == CTemplateBuff::BUFF_DEC )
	{
		// ���Ŀ��ΪNPC����ôҪ֪ͨNPCģ�鴦��NPC����
		if ( IsNpc() )
		{
			// ֪ͨNPCģ�飬NPC��������
			CNpcModule::GetSingleton().OnAttacked( pSrcEntity, this, 1 );
			// ��NPC�����˵��˺��б�
			CPropertyModule::GetSingleton().EntityInsertDamageList( this, pSrcEntity );
		}
	}	

	unsigned int tLastBuffID = 0;
	int nHorseID = 0;
	if ( this->IsPlayer() )
	{
		CPropertyPlayer* pPro = (CPropertyPlayer*)this->GetProperty();
		nHorseID = pPro->GetHorseTempID();
	}
	// �����Buff����ʱ�����0, ��ô���һ��Buff
	if ( pBuffTpl->mLastTime > 0 || pBuffTpl->mLastTime == -1 )
	{				
		int	tListID = 0;
		int tResultCode = 0;
		

		CBuffObject* tpBuffObj = tpBuff->InsertBuff( pBuffTpl->mTempID, (nBuffTime>0?nBuffTime:pBuffTpl->mLastTime), pSrcEntity, tLastBuffID, nDamage , this, &tListID, &tResultCode );
		if( tpBuffObj == NULL )
		{
			if( tResultCode != ERROR_USESKILL_INSERTBUFF_LARGE )
			{
				//TODO: �ڿɵ���buff������֮ǰ��С�����buff�����������ȹرղ�д��־
#ifdef _DEBUG_
				LOG_ERROR( "pro", "[ %s : %d ] [ %s ] InsertBuff error, Entity %d,NpcID %d,BuffID %d, BuffCount %d, ErrCode %d",
					__LK_FILE__, __LINE__, __FUNCTION__, GetEntityID( ),GetNpcID(), pBuffTpl->mTempID, tpBuff->mBuffNumber, 
					tResultCode );
#endif
			}
			if ( tResultCode == ERROR_USESKILL_INSERTBUFF_REMOVECOUNT )
			{
				AddFunResult( 0, FUNC_REMOVEBUFF, RESULT_NORMAL, true, pBuffTpl->mRemoveCountID, tListID );
				tResultCode = SUCCESS;
			}
			return tResultCode;
		}

		if ( tLastBuffID != 0 )
		{
			// ����Ǿ���BUFF,��ô�����ͻ��˷�ɾ��BUFF�İ�
			if( pBuffTpl->mBuffSuperposition == CTemplateBuff::NONE_SUPERPOSITION )
			{
				AddFunResult( 0, FUNC_REMOVEBUFF, RESULT_NORMAL, true, tLastBuffID, tListID );

				AddFunResult( pSrcEntity->GetEntityID(), FUNC_SYNCHPMP, RESULT_NONE, true, pDesProperty->GetCurHP( ), pDesProperty->GetMaxHP( ), pDesProperty->GetCurMP( ), pDesProperty->GetMaxMP( ) );
				// ��Ҫͬ�����״̬
				CTemplateBuff* tpLastBuffTpl = (CTemplateBuff*) CDataStatic::SearchTpl( tLastBuffID );
				if ( tpLastBuffTpl != NULL )
				{
					int nTempOne = 0;
					int nTempTwo = 0;
					RemoveBuffState( tpLastBuffTpl, nTempOne, nTempTwo );
				}
			}

			// �������ɽbuff����״̬
			int nFCSBuffID = tpBuff->HasTransform();
			if( (unsigned int)nFCSBuffID == tLastBuffID)
			{
				tpBuff->SetTransform( NULL, nFCSBuffID );
				CPropertyModule::GetSingleton().SendPlayerTransformNotify( (CEntityPlayer*)this );
				NotifyPropertyRefresh( );
			}
		}

		// һ��Ҫ�Ȳ���buff. ��Ϊ������ҿ��ܻ�����
		AddFunResult( pSrcEntity->GetEntityID(), FUNC_INSERTBUFF, RESULT_NORMAL, true, pBuffTpl->mTempID, tpBuffObj->mListID, tpBuffObj->mPersistTime );
	
		AddFunResult( pSrcEntity->GetEntityID(), FUNC_SYNCHPMP, RESULT_NONE, true, pDesProperty->GetCurHP( ), pDesProperty->GetMaxHP( ), pDesProperty->GetCurMP( ), pDesProperty->GetMaxMP( ) );


		if( tResultCode == SUCCESS )
		{
			InsertBuffState( pSrcEntity, pBuffTpl, tpBuffObj, nSkillType, nDamage );
		}

		// ��������
		if( pBuffTpl->mBuffFirstActionTime == 0 )
		{
			BuffTimeEvent( pBuffTpl, tpBuffObj/*&tpBuff->GetBuffObjectByIndex( tBuffInsertRet )*/ );
		}

		LOG_INFO( "pro", "Entity( %d ) insertBuff, BuffID = %d", pSrcEntity->GetEntityID( ), pBuffTpl->mTempID );

		// ���������BUFF����,���ͻ��˷�ɾ��֮ǰBUFF�İ�


	}
	else
	{
		InsertBuffState( pSrcEntity, pBuffTpl, NULL, nSkillType, nDamage );
	}

	// ���δ�ı�ǰ�����HP,���MP
	unsigned int tnOldMaxHP = pDesProperty->GetMaxHP( );
	unsigned int tnOldMaxMP = pDesProperty->GetMaxMP( );

	// һ��Ҫ�Ȳ���buff. ��Ϊ������ҿ��ܻ�����
	//AddFunResult( pSrcEntity->GetEntityID(), FUNC_INSERTBUFF, RESULT_NORMAL, pBuffTpl->mTempID, pDesProperty->GetCurHP( ), pDesProperty->GetMaxHP( ), pDesProperty->GetCurMP( ), pDesProperty->GetMaxMP( ) );

	

	// TODO: BUFF���ܸı�HP,MP����,ˢ��һ��
	pDesProperty->Refresh( );
	
	// ��NPC�������Buff�Ļ����ô���ˢ����Ϣ������û�����ԣ�ֻ����ҲŴ���
	if( this->IsPlayer() )
	{
		// ������Ʊ���
		if ( pBuffTpl->mTransform != 0 )
		{	
			// ���֮ǰ�б�����ȡ��
			if( tpBuff->HasTransform() )
			{
				tpBuff->SetTransform( NULL, pBuffTpl->mTempID );
				CPropertyModule::GetSingleton().SendPlayerTransformNotify( (CEntityPlayer*)this );
				NotifyPropertyRefresh( );
			}

			tpBuff->SetTransform( pSrcEntity, pBuffTpl->mTempID );
			CPropertyModule::GetSingleton().SendPlayerTransformNotify( (CEntityPlayer*)this );
		}
		NotifyPropertyRefresh( );
		// ֪ͨ����ģ��
		CTaskModule::GetSingleton().FireEvent( (CEntityPlayer*)this, EVENT_BUFFCHANGED, pBuffTpl->mTempID );		

		// ����������� ����Ҫȡ�����BUFF ��Ҫ�ж��ܲ�������
		if ( nHorseID != 0 )
		{
			CTplItemHorse* tpTplHorse = (CTplItemHorse*)CDataStatic::SearchTpl(nHorseID);
			if (tpTplHorse != NULL)
			{
				if ( tLastBuffID == (unsigned int)tpTplHorse->mSpeedBuff )
				{
					CPropertyModule::GetSingleton().SendRideHorseNotice( this, nHorseID, 0 );
				}
			}
		}
	}

	// ��ʱд������,�Ժ�������װ
	// ������HP�������MP�ı�ʱ,�㲥HP,MP�ı����Ϣ
	if ( tnOldMaxHP != ((unsigned int) pDesProperty->GetMaxHP( )) || tnOldMaxMP != ((unsigned int) pDesProperty->GetMaxMP( )) )
	{
		CMessage tMessage;
		CMessageEntityRefreshNotice tEntityRefreshNotice;

		if ( CPropertyModule::GetSingleton( ).CreateMessageEntityRefreshNotice( 
			&tMessage,
			&tEntityRefreshNotice,
			pDesProperty->GetEntityID( ),
			pDesProperty->GetCurHP( ),
			pDesProperty->GetCurMP( ),
			pDesProperty->GetMaxHP( ),
			pDesProperty->GetMaxMP( ) )
			)
		{
			CMapModule::GetSingleton( ).MessageBroadCast( this, &tMessage, false, false );
		}
	}

	return SUCCESS;
}


// ʵ�������Ƿ���ĳBUFF
bool CEntityCharacter::EntityHasBuff( int nBuffID )
{
	CPropertyCharacter* pProperty = (CPropertyCharacter*) GetProperty();
	CBuffList* tpBuff = pProperty->GetBuffList( );
	for ( unsigned int i = 0; i < ARRAY_CNT( tpBuff->mBuffList ) - 1; i++ )
	{
		if ( tpBuff->mBuffList[i].mBuffID != 0 )
		{
			if ( nBuffID == (int)tpBuff->mBuffList[i].mBuffID )
			{
				return true;
			}
		}
	}
	return false;
}

// ʵ��ɾ��BUFF
int CEntityCharacter::EntityRemoveBuff( int vBuffID, int vListID )
{
	CPropertyCharacter* pProperty = (CPropertyCharacter*) GetProperty();

	int nSrcEntityID = 0;
	int tBackDamage = 0;
	int tListID = vListID;

	CTemplateBuff* tpBuffTpl = (CTemplateBuff*) CDataStatic::SearchTpl( vBuffID );
	if( tpBuffTpl == NULL )
	{
		LOG_ERROR( "pro", "[ %s : %d ][ %s ]Buff( %d ) Cannt find Template", __LK_FILE__, __LINE__, __FUNCTION__,
			vBuffID );
		return 0;
	}

	int nHorseID = 0;
	bool bIsOffHorse = false; // �Ƿ���ɾ��BUFF������
	// ���ж��Ƿ�����BUFF ����� ������������� ����ȡ��
	if ( this->IsPlayer() )
	{
		CPropertyPlayer* pPro = (CPropertyPlayer*)pProperty;
		nHorseID = pPro->GetHorseTempID();

		// ����������� ����Ҫȡ�����BUFF ��Ҫ�ж��ܲ�������
		if ( nHorseID != 0 )
		{
			CTplItemHorse* tpTplHorse = (CTplItemHorse*)CDataStatic::SearchTpl(nHorseID);
			if (tpTplHorse == NULL)
			{
				LOG_ERROR("pro", "no such hourse? id=%d", nHorseID);
			}
			else
			{
				if ( vBuffID == tpTplHorse->mSpeedBuff ) // Ҫ���� ���ж��ܷ�����
				{
					// �赲�ﲻ������
					if ( CMapModule::GetSingleton().IsStaticBlock( GetLineID(), GetMapID(), 
						GetMapIndex(), GetPos() ) )
					{
						CPropertyModule::GetSingleton().SendRideHorseNotice( this, nHorseID, ERROR_CANNOTOFF );
						return ERROR_CANNOTOFF;
					}
					bIsOffHorse = true;
				}
			}
		}
	}


	CBuffList* tpBuff = pProperty->GetBuffList( );
	if ( IsAlive() == true )
	{
		for ( int i = 0; i < tpBuff->GetBuffNum(); i++ )
		{
			// ���Buff��ͬ
			if ( vBuffID == (int)tpBuff->mBuffList[i].mBuffID )
			{
				nSrcEntityID = tpBuff->mBuffList[ i ].mSrcEntityID;
				tBackDamage = tpBuff->mBuffList[ i ].mBackDamage;
			}
		}
	}

	int tRtn = tpBuff->RemoveBuff( vBuffID, this, &tListID );

	if( tRtn < 0 )
	{

		LOG_ERROR( "pro", "[ %s : %d ][ %s ]Entity( %d ) NpcID(%d) Remove Buff Err, BuffID = %d, rtn = %d", __LK_FILE__, __LINE__,
				__FUNCTION__, GetEntityID( ), GetNpcID(), vBuffID, tRtn );

#ifdef _DEBUG_
		print_trace_fd( "pro" );
#endif
		
		return tRtn;
	}

	// ���δ�ı�ǰ�����HP,���MP
	unsigned int tnOldMaxHP = pProperty->GetMaxHP( );
	unsigned int tnOldMaxMP = pProperty->GetMaxMP( );

	RemoveBuffState( tpBuffTpl, nSrcEntityID, tBackDamage );

	pProperty->Refresh( );

	AddFunResult( 0, FUNC_REMOVEBUFF, RESULT_NORMAL, true, vBuffID, tListID );
	AddFunResult( 0, FUNC_SYNCHPMP, RESULT_NONE, true, pProperty->GetCurHP( ), pProperty->GetMaxHP( ), pProperty->GetCurMP( ), pProperty->GetMaxMP( ) );

	// ��NPC����ȥ��Buff�Ļ����ô���ˢ����Ϣ������û�����ԣ�ֻ����ҲŴ���
	if( this->IsPlayer() )
	{
		// ������Ʊ���
		if ( tpBuffTpl->mTransform != 0 )
		{
			tpBuff->SetTransform( NULL, 0 );
			CPropertyModule::GetSingleton().SendPlayerTransformNotify( (CEntityPlayer*)this );
		}

		NotifyPropertyRefresh( );

		// ��������� ��֪ͨ
		if ( nHorseID != 0 && bIsOffHorse )
		{
			CPropertyModule::GetSingleton().SendRideHorseNotice( this, nHorseID, 0 );
		}
		// ֪ͨ����ģ��
		CTaskModule::GetSingleton().FireEvent( (CEntityPlayer*)this, EVENT_BUFFCHANGED, vBuffID );
	}

	// ��ʱд������,�Ժ�������װ
	// ������HP�������MP�ı�ʱ,�㲥HP,MP�ı����Ϣ
	if ( tnOldMaxHP != ((unsigned int) pProperty->GetMaxHP( )) || tnOldMaxMP != ((unsigned int) pProperty->GetMaxMP( )) )
	{
		CMessage tMessage;
		CMessageEntityRefreshNotice tEntityRefreshNotice;

		if ( CPropertyModule::GetSingleton( ).CreateMessageEntityRefreshNotice( 
			&tMessage,
			&tEntityRefreshNotice,
			pProperty->GetEntityID( ),
			pProperty->GetCurHP( ),
			pProperty->GetCurMP( ),
			pProperty->GetMaxHP( ),
			pProperty->GetMaxMP( ) )
			)
		{
			CMapModule::GetSingleton( ).MessageBroadCast( this, &tMessage, false, false );
		}
	}

	LOG_INFO( "pro", "[ %s : %d ][ %s ]Entity( %d ) Remove Buff, BuffID = %d, Now Buff %d", __LK_FILE__, __LINE__, __FUNCTION__, GetEntityID( ), vBuffID , tpBuff->mBuffNumber );

	return tRtn;
}

// ʵ������
//************************************
// Method:    EntityDie
// FullName:  CEntityCharacter::EntityDie
// Access:    public 
// Returns:   void
// Qualifier:  ��ע�⡿pSrcEntity ����Ϊnull,ÿ����֮ǰһ���жϡ�
// Parameter: CEntityCharacter * pSrcEntity
// Parameter: bool bKillSelf
// Parameter: bool vIsAward
//************************************
void CEntityCharacter::EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf, bool vIsAward )
{
	CPropertyCharacter* pDesProperty = (CPropertyCharacter*) GetProperty( );

	if( pSrcEntity != NULL )
	{
		LOG_DEBUG( "pro", "[ %s : %d ][ %s ]Entity( %d ) kill Entity( %d )", __LK_FILE__, __LINE__, __FUNCTION__, 
			pSrcEntity->GetEntityID( ), GetEntityID( ) );
	}

	SetAliveStatus( ALIVE_DIE );
	SetHasTarget( false );
	SetTargetPos( CWTPoint( ) );

	// ���BUFF
	RemoveBuffEntityDie( );
	
	

	// ���ͻ��˷�ʵ����������Ϣ
	AddFunResult( ((pSrcEntity!=NULL)?pSrcEntity->GetEntityID():0), FUNC_DIE, RESULT_NORMAL, true, GetPosX(), GetPosY() );
	//�����ȷ�һ��������Ϣ����Ȼ����ϵͳ����
	CPropertyModule::GetSingletonPtr()->ResultListSend();
	// ��ʱ���Ĵ���
	TimeForDie( );

	// ���������ߵ��˺��б�,�������ߴ��б��ж�����˺��б���ȥ��,������
	CDamageList *tpDamageList = pDesProperty->GetDamageList( ); 
	for ( int i = 0; i < tpDamageList->mNumber; i++ )
	{
		CPropertyCharacter* pAttacker = (CPropertyCharacter*) CProperty::SearchProByEntityID( tpDamageList->mDamage[ i ].mSrcEntityID );
		if ( pAttacker == NULL )
			continue;
		CDamageList* tpAttackList = pAttacker->GetDamageList( );
		tpAttackList->RemoveDamage( GetEntityID( ) );
	} 
	tpDamageList->ClearDamage( );

	// ֪ͨNPCģ���������
	if ( pSrcEntity != NULL )
		NotifyDeath( pSrcEntity );

	// ֪ͨ�۲���( ɱ���߿���ΪNULL,���类buffɱ������buff�����Ѿ����ߣ�
	if( vIsAward == true )
	{
		CharacterDeathNotity( this->GetEntityID( ), pSrcEntity != NULL ? pSrcEntity->GetEntityID( ) : NULL ); 
	}

	// ���ɱ���Է��󣬻�ȡѪ
	if ( pSrcEntity != NULL && pSrcEntity->IsPlayer() )
	{
		KillerRenew( pSrcEntity );
	}

	if ( IsPlayer() )
	{
		CPropertyPlayer* pPro = (CPropertyPlayer*)GetProperty( );
		pPro->SetDieNum( pPro->GetDieNum() + 1);
		// �ۼ���������ֵ
		CItemMagicWeapon* tpObjMW = (CItemMagicWeapon*)pPro->GetEquipment()->GetItemObjPtr( EQUIPMENT_MAGICWEAPON );
		if ( tpObjMW != NULL )
		{
			if ( tpObjMW->OnDieCutHp() != 0 )
			{
				CPropertyModule::GetSingleton().NotifyRefreshMagicWeaponProperty( (CEntityPlayer*)this, MAGIC_WEAPON_HP, -1 );
			}
		}		
	}	

	// ������Ŵ����¼�
	if ( this->IsOgre() || this->IsFunNpc() || this->IsBlock() )
	{
		CEntityNpc *tpNpc = (CEntityNpc*)this;
		CEntityPlayer *tpPlayer = (CEntityPlayer *)pSrcEntity;
		CTemplateOgre *tplNpc = (CTemplateOgre*)CDataStatic::SearchTpl( tpNpc->GetNpcID() );
		if ( tplNpc != NULL && tplNpc->mOgreEvent != 0 && tpPlayer != NULL )
		{
			CWorldModule::GetSingleton().SendSpecialEventNotify( tpPlayer->GetNationality(), this->GetLineID(), tplNpc->mOgreEvent, tpPlayer->GetCharID() );
		}
	}

	// ����PKֵ���������
	CPropertyModule::GetSingleton().ProcessPKValueOnDie( pSrcEntity, ( CEntityCharacter* ) this );	

	return ;
}

void CEntityNpc::EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf /* = false */, bool vIsAward /* = true */ )
{
	CEntityCharacter::EntityDie(pSrcEntity, bKillSelf, vIsAward);	
	return;
}

void CEntityPlayer::EntityDie(CEntityCharacter *pSrcEntity, bool bKillSelf, bool vIsAward)
{
	CPropertyPlayer* pDesProperty = (CPropertyPlayer*) GetProperty( );

	// �����ٻ���
	if ( pDesProperty->GetPetID( ) != 0 )
	{		
		pDesProperty->DestroyPetEntity( );
	}

	if ( pSrcEntity != NULL && vIsAward )
		HonorForDie( pSrcEntity );

	// ����ɱ��Ҫ����װ���;ö�
	CPropertyModule::GetSingleton().ChangeDurabilityOnDeath( this );

	// ����ȡ��
	CTradeModule::GetSingleton().OnCancelTrade( mEntityID );

	pDesProperty->SetDieNum( pDesProperty->GetDieNum() + 1);
	if ( pSrcEntity != NULL )
	{
		if ( pSrcEntity->IsPlayer() )
		{
			if ( GetNationality() != pSrcEntity->GetNationality() && ((CEntityPlayer*)pSrcEntity)->IsHandle( UN_HANDLE_PROCESS_FOR_ATTACK ) == true )
			{
				int tIntParam[ 5 ] = { 0 };
				tIntParam[ 0 ] = pSrcEntity->GetNationality();
				tIntParam[ 1 ] = this->GetNationality();
				tIntParam[ 2 ] = pSrcEntity->GetMapID();
				tIntParam[ 3 ] = pSrcEntity->GetPosX();
				tIntParam[ 4 ] = pSrcEntity->GetPosY();
				CPropertyModule::GetSingleton().SendEventNotify( NOTICE_KILLPLAYER, CSceneLogic::GetSingleton().GetLineID(), tIntParam, ARRAY_CNT(tIntParam), (char *)pSrcEntity->GetName(), NULL );
				CWorldModule::GetSingleton().SendKillPersonRequest( ((CEntityPlayer*)pSrcEntity)->GetCharID(), this->GetCharID() );
			}		
			
			LogEventPlayerKilledByPlayer((CEntityPlayer*)this, (CEntityPlayer*) pSrcEntity); 
		}
		else
		{
			LogEventPlayerKilledByOther((CEntityPlayer*)this, pSrcEntity);
		}
	}

	/*
	CSceneLogic::GetSingleton().Send2Log( BuildPlayerDieLogMessage( (CEntityPlayer*)this, tKillerType, tKillerID, 
		( pSrcEntity == NULL ? "" : pSrcEntity->GetName() ) ), (int)EIHANDLE_TWO, tKillerID);
	*/

	mSpeedChecker.ClearFailedCount();
	CEntityCharacter::EntityDie(pSrcEntity, bKillSelf, vIsAward);
	return ;
}

void CEntityOgre::EntityDie(CEntityCharacter *pSrcEntity, bool bKillSelf , bool vIsAward )
{	
	CPropertyCharacter* pDesProperty = ( CPropertyCharacter* ) GetProperty();
	if ( pSrcEntity != NULL && vIsAward )
	{
		ExpForDie( pSrcEntity );
		//CTaskModule::GetSingleton( ).OnEntityDie( pSrcEntity, this );
	}

	CTemplateNpc* tpTempOgre = (CTemplateNpc*) CDataStatic::SearchTpl( pDesProperty->GetPropertyTempID( ) );
	if ( tpTempOgre == NULL )
	{
		LOG_DEBUG( "pro", "EntityDie:Ogre id = %d not found", pDesProperty->GetPropertyTempID( ) );
		return;
	}

	// ����ǹ�ս������Դ��Ϣ
	if ( IS_BATTLE_LINE_ID( CSceneLogic::GetSingleton().GetLineID() ) == true
		&& tpTempOgre->mWarValue != 0
		&& pSrcEntity->IsPlayer() )
	{
		CEntityPlayer *tpPlayer = (CEntityPlayer*)pSrcEntity;
		CMessage tGateMessage;
		CMessageWarChangeNotify tGatePara;
		tGateMessage.mutable_msghead()->set_messageid( ID_S2G_NOTIFY_WARCHANGE );
		tGateMessage.set_msgpara( (long) &tGatePara );
		tGatePara.set_sourcetype( CHANGE_ADD );
		tGatePara.set_worldid( tpPlayer->GetNationality() );
		tGatePara.set_sourcevalue( tpTempOgre->mWarValue );
		tGatePara.set_mapid( GetMapID() );
		CSceneLogic::GetSingleton().Send2Gate( &tGateMessage );
		if ( GetOwnCampID() != 0 )
		{
			tGatePara.set_sourcetype( CHANGE_DEL );
			tGatePara.set_worldid( GetOwnCampID() );
			tGatePara.set_sourcevalue( tpTempOgre->mWarValue );
			tGatePara.set_mapid( GetMapID() );
			CSceneLogic::GetSingleton().Send2Gate( &tGateMessage );
		}

		CPropertyModule::GetSingleton().SendWarEventNotify( NOTICE_WAR_FLAG_CUTDOWN, tpPlayer->GetMapID(), tpPlayer->GetPosX(), 
			tpPlayer->GetPosY(), GetOwnCampID(), tpPlayer->GetNationality(), tpTempOgre->mWarValue, pDesProperty->GetPropertyTempID( ), tpPlayer->GetCharName() );

		CPropertyModule::GetSingleton().ObtainWarHonor( tpPlayer, tpTempOgre->mWarHonor, false );
	}

	if ( pSrcEntity != NULL && pSrcEntity->IsPlayer() )
	{
		CPropertyPlayer* tpProPlayer = (CPropertyPlayer*)pSrcEntity->GetProperty();
		tpProPlayer->SetKillOgreNum( tpProPlayer->GetKillOgreNum() +1);  // ɱ�ּ���

		// ������֮���ɱ�ּ���
		if( ((CEntityPlayer*) pSrcEntity)->GetFcmStatus() == em_half_rate )
		{
			((CEntityPlayer*) pSrcEntity)->IncAfterFcmKilled();
		}

		if ( tpTempOgre->mObtainTitle != INVALID_OBJ_ID )
		{
			CEntityPlayer* tTeamPlayerList[ TEAM_NUMBER ] = { NULL };
			int tNum = 0;
			CTeamModule::GetSingleton().OnGetMemberList( (CEntityPlayer*)pSrcEntity, tTeamPlayerList, TEAM_NUMBER, tNum );
			for ( int i = 0; i < tNum; i ++ )
			{
				if ( tTeamPlayerList[ i ] != NULL )
					CPropertyModule::GetSingleton().OnPlayerAddTitleEvent( tTeamPlayerList[ i ], tpTempOgre->mObtainTitle );
			}			
		}

		if ( tpTempOgre->mDisplayLevel == CTemplateOgre::OGRESHOW_BOSS )
		{
			int tIntParam[ 2 ] = { 0 };
			tIntParam[ 0 ] = pDesProperty->GetPropertyTempID( );
			tIntParam[ 1 ] = RAND(4);
			int tCountryID = this->GetLineID( );
			if( IS_REPETION_LINE_ID( tCountryID ) == false )
			{
				CPropertyModule::GetSingletonPtr()->SendEventNotify( NOTICE_PLAYERKILLBOSS, tCountryID, tIntParam, 
					ARRAY_CNT(tIntParam), (char *)(((CEntityPlayer*)pSrcEntity)->GetName( )), NULL );
			}			
		}

	}
	if ( pSrcEntity != NULL && pSrcEntity->IsOgre()  )
	{
		CProperty *tpProperty = pSrcEntity->GetProperty();
		if ( tpTempOgre->mDisplayLevel == CTemplateOgre::OGRESHOW_BOSS )
		{
		
			int tIntParam[ 2 ] = { 0 };
			tIntParam[ 0 ] = pDesProperty->GetPropertyTempID( );
			tIntParam[ 1 ] = tpProperty->GetPropertyTempID();
			int tCountryID = this->GetLineID( );
			
		
			if( IS_REPETION_LINE_ID( tCountryID ) == false && tIntParam[ 0 ] != tIntParam[ 1 ] )
			{
				CPropertyModule::GetSingletonPtr()->SendEventNotify( NOTICE_OGREKILLBOSS, tCountryID, tIntParam, 
					ARRAY_CNT(tIntParam),  NULL, NULL );				
			}			
		}		
	}
	
	if ( pSrcEntity != NULL )
	{
		CActivityModule::GetSingleton().CheckOgreActivityInfoOnDeath( pDesProperty->GetPropertyTempID(), pSrcEntity->GetEntityID() );
	}	

	CNpcModule::GetSingleton().OnSneered( 0, GetEntityID(), 1 );	

	CEntityCharacter::EntityDie(pSrcEntity, bKillSelf, vIsAward);
}

void CEntityPet::EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf /* = false */, bool vIsAward /* = true */ )
{
	CEntityCharacter* tpOwner = (CEntityCharacter*) GetOwner( );
	if ( tpOwner != NULL )
	{
		CPropertyCharacter* tpProOwner = (CPropertyCharacter*) tpOwner->GetProperty( );
		tpProOwner->SetPetID( 0 );
	}
	
	CNpcModule::GetSingleton().OnSneered( 0, GetEntityID(), 1 );
	
	CEntityCharacter::EntityDie(pSrcEntity, bKillSelf, vIsAward);
	return ;
}

void CEntityBlock::EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf /* = false */, bool vIsAward /* = true */ )
{
	CMapObject* tpMapObj = GetMapObject( );	
	
	LK_ASSERT_STR( tpMapObj != NULL, return, "Entity( %d ) Map( %d : %d : %d ) Is Null", GetEntityID( ),
		GetLineID( ), GetMapID( ), GetMapIndex( ) );

	( ( CEntityBlock* )this )->RemoveBlock( );

	if ( pSrcEntity != NULL )
		CTaskModule::GetSingleton( ).OnEntityDie( pSrcEntity, this );
	CEntityCharacter::EntityDie(pSrcEntity, bKillSelf, vIsAward);
	return ;
}

void CEntityPedal::EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf /* = false */, bool vIsAward /* = true */ )
{
	return ;
}

void CEntityFuncNpc::EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf /* = false */, bool vIsAward /* = true */ )
{
	if ( pSrcEntity != NULL )
	{
		CTaskModule::GetSingleton( ).OnEntityDie( pSrcEntity, this );
	}

	CNpcModule::GetSingleton().OnSneered( 0, GetEntityID(), 1 );
	
	CEntityCharacter::EntityDie(pSrcEntity, bKillSelf, vIsAward);
	return ;
}

void CEntityBox::EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf /* = false */, bool vIsAward /* = true */ )
{
	CEntityOgre::EntityDie(pSrcEntity, bKillSelf, vIsAward);
	return ;
}

// ���BUFF״̬
void CEntityCharacter::RemoveBuffState( CTemplateBuff* pBuffTpl, int& nSrcEntityID, int& nBackDamage )
{
	LK_ASSERT( pBuffTpl != NULL, return );

	CPropertyCharacter* pProperty = (CPropertyCharacter*) GetProperty();

	for ( unsigned int t = 0; t < ARRAY_CNT( pBuffTpl->mBuff ); t ++ )
	{
		if ( pBuffTpl->mBuff[ t ].mBuffFunc == 0 )
			continue;

		switch( pBuffTpl->mBuff[ t ].mBuffFunc )
		{
		case CTemplateBuff::BUFFFUNC_PLAYER_UNATTACK:
			{
				pProperty->DetachState( STATE_PLAYER_UNATTACK, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_UNATTACK_PLAYER:
			{
				pProperty->DetachState( STATE_UNATTACK_PLAYER, pBuffTpl->mTempID, BUFF );
			}
			break;
			// �ػ�
		case CTemplateBuff::BUFFFUNC_PROTECTED:
			{
				pProperty->DetachState( STATE_PROTECTED, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_MAGICSHIELD:
			{
				pProperty->DetachState( STATE_MAGICSHIELD, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_IMMUNITYDAMAGE:
			{
				pProperty->DetachState( STATE_IMMUNITYDAMAGE, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_IMMUNITYREVERSD:
			{
				pProperty->DetachState( STATE_IMMUNITYREVERSD, pBuffTpl->mTempID, BUFF );
			}
		case CTemplateBuff::BUFFFUNC_DAMAGELESS:
			{
				pProperty->DetachState( STATE_DAMAGELESS, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_UNATTACK:
			{
				pProperty->DetachState( STATE_UNATTACK, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_UNMOVE:
			{
				pProperty->DetachState( STATE_CANNTMOVE, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_UNUSEITEM:
			{
				pProperty->DetachState( STATE_FASTING, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_REBOUNDDAMAGE:
			{
				pProperty->DetachState( STATE_REBOUND, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFINC_DECSPEEDPER:
			{
				pProperty->DetachState( STATE_UNCREAMSPEED, pBuffTpl->mTempID, BUFF, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );

				unsigned int tNewSpeed = CPropertyFormula::GetRunSpeed( pProperty );

				// �ٶȲ�ͬ,֪ͨ�ɼ��ͻ���
				if ( pProperty->GetCurSpeed( ) != tNewSpeed )
				{
					pProperty->SetCurSpeed( tNewSpeed );

					AddFunResult( 0, FUNC_CHANGESPEED, RESULT_NORMAL, true, tNewSpeed );
					// ֪ͨNPCģ��
				}
			}
			break;
		case CTemplateBuff::BUFFINC_INCSPEEDPER:
			{
				pProperty->DetachState( STATE_INCREAMSPEED, pBuffTpl->mTempID, BUFF, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );

				unsigned int tNewSpeed = CPropertyFormula::GetRunSpeed( pProperty );

				// �ٶȲ�ͬ,֪ͨ�ɼ��ͻ���
				if ( pProperty->GetCurSpeed( ) != tNewSpeed )
				{
					pProperty->SetCurSpeed( tNewSpeed );

					AddFunResult( 0, FUNC_CHANGESPEED, RESULT_NORMAL, true, tNewSpeed );
					// ֪ͨNPCģ��
				}
			}
			break;
		case CTemplateBuff::BUFFFUNC_ENDEVENT:
			{
				if ( pBuffTpl->mBuff[t].mBuffParam[1] == 1 )
					nSrcEntityID = this->GetEntityID();
				if ( nSrcEntityID == 0 || IsAlive() == false )
					break;

				CEntityCharacter* tpSrcEntity = (CEntityCharacter*) CSceneLogic::GetSingletonPtr( )->GetEntity( nSrcEntityID );
				if ( tpSrcEntity == NULL  )
					break;

				if( tpSrcEntity->IsCharacter() == false )
					break;

				CTemplateBuff* tTmpTPL = (CTemplateBuff*) CDataStatic::SearchTpl( pBuffTpl->mBuff[t].mBuffParam[0] );
				if ( tTmpTPL == NULL )
				{
					LOG_ERROR( "pro", "[ %s : %d ][ %s ]Entity( %d ) Cannt find Buff( %d ) Template", 
						__LK_FILE__, __LINE__, __FUNCTION__, tpSrcEntity->GetEntityID( ), 
						pBuffTpl->mBuff[t].mBuffParam[0] );
					break;
				}
				// ������(����)
				this->AddFunResult( 0, FUNC_ATTACKED, RESULT_NONE, true, 
					this->GetEntityID( ), pBuffTpl->mTempID, 0, this->GetPosX( ), this->GetPosY( ) );

				EntityInsertBuff( tpSrcEntity, tTmpTPL );
			}
			break;

		case CTemplateBuff::BUFFFUNC_HPBACKEFFECT:
			{
				pProperty->DetachState( STATE_CUREHPLESS, pBuffTpl->mTempID, BUFF, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
			}
			break;
		case CTemplateBuff::BUFFFUNC_KILLERRENEW:
			{
				pProperty->DetachState( STATE_KILLERRENEW, pBuffTpl->mTempID, BUFF, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
			}
			break;
		case CTemplateBuff::BUFFFUNC_FIREEVENT:
			{
				pProperty->DetachState( STATE_FIREEVENT, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_ATTACKEVENT:
			{
				pProperty->DetachState( STATE_ATTACKEVENT, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_IGNORECLOTH:
			{
				pProperty->DetachState( STATE_IGNORECLOTH, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_UNARM:
			{
				pProperty->DetachState( STATE_UNARM, pBuffTpl->mTempID, BUFF );
			}
			break;
			// ���ӱ�����ʱ���������˺��̶�ֵ
		case CTemplateBuff::BUFFINC_INCDESPDAMAGEFIX:
			{
				pProperty->DetachState( STATE_INCDESPDAMAGEFIX, pBuffTpl->mTempID, BUFF );
			}
			break;
			// ���ӱ�����ʱ���������˺��ٷֱ�
		case CTemplateBuff::BUFFINC_INCDESPDAMAGEPER:
			{
				pProperty->DetachState( STATE_INCDESPDAMAGEPER, pBuffTpl->mTempID, BUFF );
			}
			break;
			// ���ͱ�����ʱ���������˺��̶�ֵ
		case CTemplateBuff::BUFFINC_DECDESPDAMAGEFIX:
			{
				pProperty->DetachState( STATE_DECDESPDAMAGEFIX, pBuffTpl->mTempID, BUFF );
			}
			break;
			// ���ͱ�����ʱ���������˺��ٷֱ�
		case CTemplateBuff::BUFFINC_DECDESPDAMAGEPER:
			{
				pProperty->DetachState( STATE_DECDESPDAMAGEPER, pBuffTpl->mTempID, BUFF );
			}
			break;
			// ���ӱ�����ʱ���ܷ����˺��̶�ֵ
		case CTemplateBuff::BUFFINC_INCDESMDAMAGEFIX:
			{
				pProperty->DetachState( STATE_INCDESMDAMAGEFIX, pBuffTpl->mTempID, BUFF );
			}
			break;
			// ���ӱ�����ʱ���ܷ����˺��ٷֱ�
		case CTemplateBuff::BUFFINC_INCDESMDAMAGEPER:
			{
				pProperty->DetachState( STATE_INCDESMDAMAGEPER, pBuffTpl->mTempID, BUFF );
			}
			break;
			// ���ͱ�����ʱ���ܷ����˺��̶�ֵ
		case CTemplateBuff::BUFFINC_DECDESMDAMAGEFIX:
			{
				pProperty->DetachState( STATE_DECDESMDAMAGEFIX, pBuffTpl->mTempID, BUFF );
			}
			break;
			// ���ͱ�����ʱ���ܷ����˺��ٷֱ�
		case CTemplateBuff::BUFFINC_DECDESMDAMAGEPER:
			{
				pProperty->DetachState( STATE_DECDESMDAMAGEPER, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_RANDMOVE:
			{
				pProperty->DetachState( STATE_RANDMOVE, pBuffTpl->mTempID, BUFF );
				pProperty->DetachState( STATE_CONFUSION, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_SNEER:
			{
				pProperty->DetachState( STATE_SNEER, pBuffTpl->mTempID, BUFF );

				if ( IsNpc() )
				{
					// ֪ͨNPCģ�飬NPC������
					// 0��ʾ���볰�� 1��ʾ�˳�����
					CNpcModule::GetSingleton().OnSneered( nSrcEntityID, GetEntityID(), 1 );
				}
			}
			break;
		case CTemplateBuff::BUFFFUNC_INCEXP:
			{
				pProperty->DetachState( STATE_INCEXP, pBuffTpl->mTempID, BUFF, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
			}
			break;
			// ���������ܵ��˺��İٷֱ� ( ����BUFF )
		case CTemplateBuff::BUFFFUNC_DECALLDAMAGEPER:
			{
				pProperty->DetachState( STATE_DECALLDAMAGEPER, pBuffTpl->mTempID, BUFF, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
			}
			break;
		case CTemplateBuff::BUFFFUNC_SAVEDAMAGE:
			{
				if ( nBackDamage > 0 )
				{
					CEntityCharacter* tpSrcEntity = (CEntityCharacter*) CSceneLogic::GetSingletonPtr( )->GetEntity( nSrcEntityID );
					if ( tpSrcEntity != NULL  )
					{
						CPropertyModule::GetSingleton().EntityDamaged( tpSrcEntity, this, nBackDamage, RESULT_REBOUND );
					}
				}
			}
			break;
		case CTemplateBuff::BUFFFUNC_TRANSFORM:
			{
				pProperty->DetachState( STATE_TRANSFORM, pBuffTpl->mTempID, BUFF );
			}
			break;
		case CTemplateBuff::BUFFFUNC_INCGENERDAMAGEPER:
			{
				pProperty->DetachState( STATE_INCGENERDAMAGEPER, pBuffTpl->mTempID, BUFF );
			}
			break;
			// ��ù�ѫ�ٷֱ�
		case CTemplateBuff::BUFFFUNC_INCHONORPER:
			{
				pProperty->DetachState( STATE_INCHONORSCALE,  pBuffTpl->mTempID, BUFF );
			}
			break;	
			
		// ���Ӿ��ŵ���ҫֵ
		case CTemplateBuff::BUFFFUNC_INCCORPSGORY:
			{
				pProperty->DetachState( STATE_INCCORPSGLORY, pBuffTpl->mTempID, BUFF, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
			}
			break;		
			
		// 	������ҵ�apֵ
		case CTemplateBuff::BUFFFUNC_INCAP:
			{
			   pProperty->DetachState( STATE_INCAP, pBuffTpl->mTempID, BUFF, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
			   break;
			}
		// ��������
		case CTemplateBuff::BUFFFUNC_HORSE:
			{
				pProperty->DetachState( STATE_RIDE_HORSE, pBuffTpl->mTempID, BUFF, 
					pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );				
				break;
			}
		// ����
		case CTemplateBuff::BUFFFUNC_INVISIBLE:
			{
				pProperty->DetachState( STATE_INVISIBLE, pBuffTpl->mTempID, BUFF, 
					pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
				break;
			}
		case CTemplateBuff::BUFFFUNC_DISINVISIBLE:
			{
				pProperty->DetachState( STATE_DISINVISIBLE, pBuffTpl->mTempID, BUFF, 
					pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
				break;
			}
		case CTemplateBuff::BUFFFUNC_FLY:
			{
				pProperty->DetachState( STATE_FLY, pBuffTpl->mTempID, BUFF, 
					pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
				break;
			}
		case CTemplateBuff::BUFFFUNC_STONE:
			{
				pProperty->DetachState( STATE_STONE, pBuffTpl->mTempID, BUFF, 
					pBuffTpl->mBuff[ t ].mBuffParam[ 0 ], pBuffTpl->mBuff[ t ].mBuffParam[ 1 ] );
				break;
			}
		case CTemplateBuff::BUFFFUNC_ADDSKILL:
			{
				if ( IsPlayer() == true )
				{
					CEntityPlayer *tpPlayer = (CEntityPlayer *)this;
					CPropertyPlayer *tpPro = (CPropertyPlayer *)tpPlayer->GetProperty();
					CSkillList&  tpSkill = tpPro->GetSkillList( );
					tpSkill.RemoveSkill( pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
				}
				break;
			}
		case CTemplateBuff::BUFFFUNC_HIDE:
			{
				pProperty->DetachState( STATE_HIDE, pBuffTpl->mTempID, BUFF, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
				break;
			}
		case CTemplateBuff::BUFFFUNC_INCOFFLINEEXP:
			{
				pProperty->DetachState( STATE_INCOFFLINEEXP, pBuffTpl->mTempID, BUFF, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
			}
			break;
		default:
			break;
		}
	}
}

// ���BUFF״̬
void CEntityCharacter::InsertBuffState( CEntityCharacter* pSrcEntity, CTemplateBuff* pBuffTpl, CBuffObject* vpBuffObject/*CBuffList* pBuffList*/, int nSkillType, int vDamage )
{
	LK_ASSERT( pSrcEntity != NULL && pBuffTpl != NULL && pBuffTpl != NULL, return )

	CPropertyCharacter* pSrcProperty = (CPropertyCharacter*) pSrcEntity->GetProperty();
	CPropertyCharacter* pDesProperty = (CPropertyCharacter*) GetProperty();

	CTplBuffImmunity* tpBuffImmunity = NULL;
	int tBuffUmmuTableID = 0;

	if( IsNpc() || IsPlayer() )
	{	
		if ( ( IsNpc( ) == true ) && ( IsPet( ) == false ) )
		{
			CEntityNpc* tpNpc = ( CEntityNpc* )this;
			CTemplateOgre* tpTpl = ( CTemplateOgre* )CDataStatic::SearchTpl( tpNpc->GetNpcID( ) );
			if( tpTpl != NULL )
			{
				tBuffUmmuTableID = tpTpl->mBuffImmunity;
			}
			else
			{
				LOG_ERROR( "default", "[ %s : %d ][ %s ] Cannt Get Npc( %d )'s Template( %d )", __LK_FILE__,
						__LINE__, __FUNCTION__, GetEntityID( ), tpNpc->GetNpcID( ) );
			}
		}
		else if( IsPlayer() ) // ��������������BUFF�б�
		{
			CEntityPlayer* tpPlayer = (CEntityPlayer*)this;
			CPropertyPlayer* tpPro = (CPropertyPlayer*)tpPlayer->GetProperty();
			CItemMagicWeapon* tpMW = (CItemMagicWeapon*)tpPro->GetEquipment()->GetItemObjPtr(EQUIPMENT_MAGICWEAPON);
			if ( tpMW != NULL )
			{
				CTemplateMagicWeapon* tpItemMW = (CTemplateMagicWeapon*)CDataStatic::SearchTpl( tpMW->GetItemID() );
				LK_ASSERT( tpItemMW != NULL, return );
				tBuffUmmuTableID = tpItemMW->mUmmiBuffTableID;
			}
		}

		if( tBuffUmmuTableID != 0 )
		{
			tpBuffImmunity = ( CTplBuffImmunity* )CDataStatic::SearchTpl( tBuffUmmuTableID );
			if( tpBuffImmunity == NULL )
			{
				LOG_ERROR( "default", "[ %s : %d ][ %s ] Cannt Find ImmunityTable %d, Entity( %d : %d )", 
					__LK_FILE__, __LINE__, __FUNCTION__, tBuffUmmuTableID, GetEntityID( ), GetEntityType( ) );
			}
		}
	}

	for ( int t = 0; t < (int)ARRAY_CNT( pBuffTpl->mBuff ) ; t ++ )
	{
		if ( pBuffTpl->mBuff[ t ].mBuffFunc == CTemplateBuff::BUFFINC_NONE )
			break;

		bool bIsContinue = false;
		if( tpBuffImmunity != NULL )
		{
			for( unsigned int i = 0; i < ARRAY_CNT( tpBuffImmunity->mBuffImmunity ); i++ )
			{
				if( tpBuffImmunity->mBuffImmunity[ i ] == CTemplateBuff::BUFFINC_NONE )
				{
					break;
				}
				if( tpBuffImmunity->mBuffImmunity[ i ] == pBuffTpl->mBuff[ t ].mBuffFunc )
				{
					LOG_INFO( "default", "[ %s : %d ][ %s ] Npc( %d : %d ) Immunity Buff( %d ) BuffFunc"
						" %d :  %d ", __LK_FILE__, __LINE__, __FUNCTION__, GetEntityID( ), 
						pSrcEntity->GetEntityID(), pBuffTpl->mTempID, t, pBuffTpl->mBuff[ t ].mBuffFunc );
					bIsContinue = true;
					break;
				}
			}

			if( bIsContinue == true )
			{
				continue;	
			}
		}	

		pDesProperty->AttachBuffState( pSrcEntity->GetEntityID( ), &pBuffTpl->mBuff[ t ], pBuffTpl->mTempID );

		switch( pBuffTpl->mBuff[ t ].mBuffFunc )
		{
			// ����ܵ��ػ�
			case CTemplateBuff::BUFFFUNC_PROTECTED:
				{					
					if( vpBuffObject != NULL )
					{
						vpBuffObject->ChangeParames( pBuffTpl->mTempID, t, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
						vpBuffObject->ChangeParames2( pBuffTpl->mTempID, t, pSrcEntity->GetEntityID() );
					}
					//				pBuffList->ChangeParames( pBuffTpl->mTempID, t, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
					//				pBuffList->ChangeParames2( pBuffTpl->mTempID, t, pSrcEntity->GetEntityID() );
				}
				break;
				//����
			case CTemplateBuff::BUFFFUNC_RELIVE:
				{
					CPropertyModule::GetSingleton().PlayerRelive( ( CEntityPlayer* )this, RELIVE_SKILL, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ], pBuffTpl->mBuff[ t ].mBuffParam[ 1 ] );
				}
				break;
				// ħ����
			case CTemplateBuff::BUFFFUNC_MAGICSHIELD:
				{
					float tShieldParam1 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mShieldparam1 / SERVER_PERCENT_FLOAT;
					float tShieldParam2 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mShieldparam2 / SERVER_PERCENT_FLOAT;
					int tAbsorb = pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] + tShieldParam1 * pow( tShieldParam2, pBuffTpl->mSkillLevel ) * vDamage;
					if( vpBuffObject != NULL )
					{
						vpBuffObject->ChangeParames( pBuffTpl->mTempID, t, tAbsorb );
					}
					//				pBuffList->ChangeParames( pBuffTpl->mTempID, t, tAbsorb );
				}
				break;
			case CTemplateBuff::BUFFFUNC_INCFIXHP:
				{
					float tParam1 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mCureparam1 / SERVER_PERCENT_FLOAT;
					float tParam2 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mCureparam2 / SERVER_PERCENT_FLOAT;
					int tCure = pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] + tParam1 * pow( tParam2, pBuffTpl->mSkillLevel ) * vDamage;
					CureHP( tCure, pSrcEntity->GetEntityID() );
				}
				break;
				// ҽ��HP�ٷֱ�
			case CTemplateBuff::BUFFFUNC_INCPERHP:
				{
					CureHP( (int)( pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] * ( (unsigned int)( pDesProperty->GetMaxHP() ) / SERVER_PERCENT_FLOAT ) ), pSrcEntity->GetEntityID() );
				}
				break;
				// �ָ�MP�̶�ֵ
			case CTemplateBuff::BUFFFUNC_INCFIXMP:
				{
					CureMP( pBuffTpl->mBuff[ t ].mBuffParam[ 0 ], pSrcEntity->GetEntityID() );
				}
				break;
				// �ָ�MP�ٷֱ�
			case CTemplateBuff::BUFFFUNC_INCPERMP:
				{
					CureMP( pDesProperty->GetCurMP() * pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] / SERVER_PERCENT_FLOAT, pSrcEntity->GetEntityID() );
				}
				break;
				// ����HP�̶�ֵ
			case CTemplateBuff::BUFFFUNC_DECFIXHP:
				{
					float tParam1 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDamageparam1 / SERVER_PERCENT_FLOAT;
					float tParam2 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDamageparam2 / SERVER_PERCENT_FLOAT;
					int tDamage = pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] + tParam1 * pow( pBuffTpl->mSkillLevel, tParam2 ) * vDamage;
					CPropertyModule::GetSingleton().EntityDamaged( pSrcEntity, this, tDamage, RESULT_NORMAL, nSkillType );
				}
				break;
				// ����HP�ٷֱ�
			case CTemplateBuff::BUFFFUNC_DECPERHP:
				{
					CPropertyModule::GetSingleton().EntityDamaged( pSrcEntity, this, (int)( pDesProperty->GetCurHP() * pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] / SERVER_PERCENT_FLOAT ), RESULT_NORMAL, nSkillType );
				}
				break;
				// ����MP�̶�ֵ
			case CTemplateBuff::BUFFFUNC_DECFIXMP:
				{
					ExpendMP( pBuffTpl->mBuff[ t ].mBuffParam[ 0 ], pSrcEntity->GetEntityID() );
				}
				break;
				// ����MP�ٷֱ�
			case CTemplateBuff::BUFFFUNC_DECPERMP:
				{
					ExpendMP( (int)(pDesProperty->GetCurMP() * pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] / SERVER_PERCENT_FLOAT), pSrcEntity->GetEntityID() );
				}
				break;
			case CTemplateBuff::BUFFFUNC_TELEPORT:
				{
					CPropertyModule::GetSingleton().EntityTeleportBuffer( this, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ], pBuffTpl->mBuff[ t ].mBuffParam[ 1 ] );
				}
				break;
				// ����N���˺�
			case CTemplateBuff::BUFFFUNC_DAMAGELESS:
				{
					if( vpBuffObject != NULL )
					{
						vpBuffObject->ChangeParames( pBuffTpl->mTempID, t, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
					}
					//				pBuffList->ChangeParames( pBuffTpl->mTempID, t, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
				}
				break;
			case CTemplateBuff::BUFFFUNC_CHANGEPATH:
				{
					// des positions of src entity and des entity 
					int tSrcDesX = GetPosX( );
					int tSrcDesY = GetPosY( );

					int tDesDesX = pSrcEntity->GetPosX( );
					int tDesDesY = pSrcEntity->GetPosY( );

					// src transport
					pSrcEntity->ChangePos( CWTPoint( tSrcDesX, tSrcDesY ), RESULT_TELEPORT, pSrcEntity->GetEntityID() );

					// des transport
					ChangePos( CWTPoint( tDesDesX, tDesDesY ), RESULT_TELEPORT, pSrcEntity->GetEntityID() );
					if ( IsOgre( ) == true || IsFunNpc( ) == true )
					{
						CNpcModule::GetSingletonPtr( )->OnTeleport( mEntityID, tDesDesX, tDesDesY );
					}
				}
				break;
			case CTemplateBuff::BUFFINC_INCSPEEDPER:
				{	
					unsigned int tNewSpeed = CPropertyFormula::GetRunSpeed( pDesProperty );

					// ����ٶȸı�,�򷢰�֪ͨ�ͻ���
					if ( pDesProperty->GetCurSpeed( ) != tNewSpeed )
					{
						pDesProperty->SetCurSpeed( tNewSpeed );
						AddFunResult( pSrcEntity->GetEntityID(), FUNC_CHANGESPEED, RESULT_NORMAL, true, tNewSpeed );
						// TODO ֪ͨnpcģ��
					}
				}
				break;
				// �����ٶȰٷֱ�
			case CTemplateBuff::BUFFINC_DECSPEEDPER:
				{
					unsigned int tNewSpeed = CPropertyFormula::GetRunSpeed( pDesProperty );

					// ����ٶȸı�,�򷢰�֪ͨ�ͻ���
					if ( pDesProperty->GetCurSpeed( ) != tNewSpeed )
					{
						pDesProperty->SetCurSpeed( tNewSpeed );
						AddFunResult( pSrcEntity->GetEntityID(), FUNC_CHANGESPEED, RESULT_NORMAL, true, tNewSpeed );
						// TODO ֪ͨnpcģ��
					}
				}
				break;
				// �������Buff
			case CTemplateBuff::BUFFFUNC_REMOVEREVERSDBUFF:
				{
					CPropertyModule::GetSingleton().EntityRemoveDebuff( this );
				}
				break;
				// �뿪��debuffʱ������Χ���ܵ�����Ч��
			case CTemplateBuff::BUFFFUNC_LEAVEAREA:
				{
					if( vpBuffObject != NULL )
					{
						vpBuffObject->ChangeParames( pBuffTpl->mTempID, t, ( GetPosX( ) << 16 ) | GetPosY( ) );
					}
					//				pBuffList->ChangeParames( pBuffTpl->mTempID, t, ( GetPosX( ) << 16 ) | GetPosY( ) );
				}	
				break;

			case CTemplateBuff::BUFFFUNC_MAGICFIRE:
				{
					unsigned int unMaxMP = pDesProperty->GetMaxMP();

					unsigned int tnMPConsume = (unsigned int)( unMaxMP * pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] / SERVER_PERCENT_FLOAT );

					if ( pDesProperty->GetCurMP() < tnMPConsume && pDesProperty->GetCurMP() > 0 )
					{
						tnMPConsume = pDesProperty->GetCurMP();
					}
					else if ( pDesProperty->GetCurMP() <= 0 )
					{
						break;
					}

					int tnHPConsume = (int)( tnMPConsume * pBuffTpl->mBuff[ t ].mBuffParam[ 1 ] / SERVER_PERCENT_FLOAT );

					if ( tnHPConsume > 0 )
					{
						ExpendMP( tnMPConsume, pSrcEntity->GetEntityID() );

						CPropertyModule::GetSingleton().EntityDamaged( pSrcEntity, this, tnHPConsume, RESULT_NORMAL, nSkillType );
					}
				}
				break;
				// ����
			case CTemplateBuff::BUFFFUNC_SUMMON:
				{
					// ͨ��ʩ����λ��,�������������
					int tPosX = pSrcEntity->GetPosX( );
					int tPosY = pSrcEntity->GetPosY( );

					if ( GetPosX( ) > pSrcEntity->GetPosX( ) )
					{
						tPosX = pSrcEntity->GetPosX( ) + 1;
					}
					else if ( GetPosX( ) < pSrcEntity->GetPosX( ) )
					{
						tPosX = pSrcEntity->GetPosX( ) - 1;
					}

					if ( GetPosY( ) > pSrcEntity->GetPosY( ) )
					{
						tPosY = pSrcEntity->GetPosY( ) + 1;
					}
					else if ( GetPosY( ) < pSrcEntity->GetPosY( ) )
					{
						tPosY = pSrcEntity->GetPosY( ) - 1;
					}

					// ���������Ϊ�赲,������ʵ���غ�,���Ҳ��ж��赲��ϵ
					if ( CanPass( tPosX, tPosY ) == false )
					{
						tPosX = pSrcEntity->GetPosX();
						tPosY = pSrcEntity->GetPosY();
					}

					// des transport
					ChangePos( CWTPoint( tPosX, tPosY ), RESULT_TELEPORT, pSrcEntity->GetEntityID() );

					if( IsNpc() )
						CNpcModule::GetSingleton().OnTeleport( GetEntityID(), tPosX, tPosY );
				}
				break;
			case CTemplateBuff::BUFFFUNC_EXCHANGE:
				{					
					int tSrcHP = pSrcProperty->GetCurHP( );
					int tDesHP = pDesProperty->GetCurHP( );
					int tDesMaxHP = pDesProperty->GetMaxHP();
					int tSrcMaxHP = pSrcProperty->GetMaxHP();

					int tSrcChange = tSrcMaxHP * ( (float)tDesHP / (float)tDesMaxHP ) - tSrcHP;
					int tDesChange = 0;
					if ( tSrcChange > 0 )
					{
						pSrcEntity->CureHP( tSrcChange, pSrcEntity->GetEntityID(), RESULT_STEALHP );
					}
					else
					{
						pSrcEntity->ExpendHP( tSrcChange * -1, pSrcEntity->GetEntityID() );
					}

					if ( ( tSrcHP * SERVER_PERCENT_INT / tSrcMaxHP ) < pBuffTpl->mBuff[t].mBuffParam[0] )
					{
						tDesChange = tDesHP - tDesMaxHP * ( pBuffTpl->mBuff[t].mBuffParam[0] / SERVER_PERCENT_FLOAT );
					}
					else
					{
						tDesChange = tDesHP - tDesMaxHP * ( (float)tSrcHP / (float)tSrcMaxHP );					
					}
					if ( tDesChange > 0 )
					{
						ExpendHP( tDesChange, pSrcEntity->GetEntityID() );
					}
					else
					{
						CureHP( tDesChange * -1, pSrcEntity->GetEntityID(), RESULT_STEALHP );
					}
				}
				break;
				// ����ȱʧ�ķ���ֵ�İٷֱȵ�Ѫ
			case CTemplateBuff::BUFFFUNC_DAMAGEFORMP:
				{
					CPropertyValue tDesMPValue = CPropertyFormula::GetMaxMP( pDesProperty );
					int tDesMaxMP = tDesMPValue.mDeltaValue + tDesMPValue.mInitValue;
					int tDamage = (int) ( ( tDesMaxMP - pDesProperty->GetCurMP( ) ) * pBuffTpl->mBuff[t].mBuffParam[0] / SERVER_PERCENT_FLOAT );

					CPropertyModule::GetSingleton().EntityDamaged( pSrcEntity, this, tDamage, RESULT_NORMAL, nSkillType );
				}
				break;
				// ����
			case CTemplateBuff::BUFFFUNC_HITDEATH:
				{
					ExpendHP( pDesProperty->GetCurHP(), pSrcEntity->GetEntityID() );

					PERF_FUNC( "EntityDie", EntityDie( pSrcEntity, pSrcEntity == this ? true : false ) );
				}
				break;
				// ����Ŀ�겢��Χ�˺�Ŀ����Χ
			case CTemplateBuff::BUFFFUNC_CUREDAMAGE:
				{
					// ���µķ�ʽʵ��,���������
				}
				break;
				// �ɹ��ż��ܻ��ܵ�����Ч��
			case CTemplateBuff::BUFFFUNC_FIREEVENT:
				{
					if( vpBuffObject != NULL )
					{
						vpBuffObject->ChangeParames( pBuffTpl->mTempID, t, pBuffTpl->mBuff[t].mBuffParam[1] );
					}
					//				pBuffList->ChangeParames( pBuffTpl->mTempID, t, pBuffTpl->mBuff[t].mBuffParam[1] );
				}
				break;
				// �漴�߶�
			case CTemplateBuff::BUFFFUNC_RANDMOVE:
				{
					switch( GetDirection( ) )
					{
						case DIR_DOWN:
							SetDirection( DIR_UP );
							break;
						case DIR_UP:
							SetDirection( DIR_DOWN );
							break;
						case DIR_RIGHT:
							SetDirection( DIR_LEFT );
							break;
						case DIR_LEFT:
							SetDirection( DIR_RIGHT );
							break;
						case DIR_LEFTUP:
							SetDirection( DIR_RIGHTDOWN );
							break;
						case DIR_RIGHTDOWN:
							SetDirection( DIR_LEFTUP );
							break;
						case DIR_LEFTDOWN:
							SetDirection( DIR_RIGHTUP);
							break;
						case DIR_RIGHTUP:
							SetDirection( DIR_LEFTDOWN );
							break;
						default:
							break;
					}
				}
				break;
			case CTemplateBuff::BUFFFUNC_IMBIBITIONMP:
				{
					int tDecMP = ExpendMP( pBuffTpl->mBuff[ t ].mBuffParam[ 0 ], pSrcEntity->GetEntityID() );
					pSrcEntity->CureMP( tDecMP, pSrcEntity->GetEntityID() );
				}
				break;
				// ��Ѫ����
			case CTemplateBuff::BUFFFUNC_SUICIDE:
				{
					int tSrcMaxHP = pSrcProperty->GetMaxHP();
					int tSrcHPPercent = (int)( SERVER_PERCENT_FLOAT * pSrcProperty->GetCurHP() / tSrcMaxHP );

					if ( tSrcHPPercent <= pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] )
					{
						break;
					}
					int tDecSrcHP = (int)( pSrcProperty->GetCurHP() - (int)( pSrcProperty->GetMaxHP() ) * pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] / SERVER_PERCENT_FLOAT );

					pSrcEntity->ExpendHP( tDecSrcHP, pSrcEntity->GetEntityID() );

					int tDamage = (int)( tDecSrcHP * pBuffTpl->mBuff[ t ].mBuffParam[ 1 ] / SERVER_PERCENT_FLOAT );
					CPropertyModule::GetSingleton().EntityDamaged( pSrcEntity, this, tDamage, RESULT_NORMAL, nSkillType );
				}
				break;
			case CTemplateBuff::BUFFFUNC_CHARGE:
				{
					CPropertyModule::GetSingleton().EntityCharge( pSrcEntity, this );
				}
				break;
			case CTemplateBuff::BUFFFUNC_SNEER:
				{
					if ( IsNpc() )
					{
						//// ֪ͨNPCģ�飬NPC������
						// 0��ʾ���볰�� 1��ʾ�Ƴ�����
						CNpcModule::GetSingleton().OnSneered( pSrcEntity->GetEntityID( ), GetEntityID( ), 0 );
					}
				}
				break; 	
			case CTemplateBuff::BUFFFUNC_HITDEATHHP:
				{
					if ( (int)pDesProperty->GetCurHP( ) <= pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] )
					{
						PERF_FUNC( "EntityDie", EntityDie( pSrcEntity ) );
					}
					else
					{
						CPropertyModule::GetSingleton().EntityDamaged( pSrcEntity, this, pBuffTpl->mBuff[ t ].mBuffParam[ 1 ], RESULT_NORMAL );
					}
				}
				break;
			case CTemplateBuff::BUFFFUNC_DAMAGEDEVENTSELF:
				{
					if( vpBuffObject != NULL )
					{
						vpBuffObject->ChangeParames( pBuffTpl->mTempID, t, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
						vpBuffObject->ChangeParames2( pBuffTpl->mTempID, t, pBuffTpl->mBuff[ t ].mBuffParam[ 1 ] );
					}
					//				pBuffList->ChangeParames( pBuffTpl->mTempID, t, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
					//				pBuffList->ChangeParames2( pBuffTpl->mTempID, t, pBuffTpl->mBuff[ t ].mBuffParam[ 1 ] );
				}
				break;
				// �������BUFF
			case CTemplateBuff::BUFFFUNC_CLEARBUFF:
				{
					// ���BUFFһ��Ҫ����ģ�幦��������,��Ȼ�����±����׳���
					CPropertyModule::GetSingleton().EntityClearbuff( this, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ], CTemplateBuff::BUFF_INC );
				}
				break;
				// �������BUFF
			case CTemplateBuff::BUFFFUNC_CLEARDEBUFF:
				{
					// ���BUFFһ��Ҫ����ģ�幦��������,��Ȼ�����±����׳���
					CPropertyModule::GetSingleton().EntityClearbuff( this, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ], CTemplateBuff::BUFF_DEC );
				}
				break;
				// �����˺�,��BUFF��ʧʱ���������յ��˺�
			case CTemplateBuff::BUFFFUNC_SAVEDAMAGE:
				{
					if( vpBuffObject != NULL )
					{
						vpBuffObject->ChangeParames( pBuffTpl->mTempID, t, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
					}
					//				pBuffList->ChangeParames( pBuffTpl->mTempID, t, pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] );
				}
				break;
				// ��Χ�̶��˺�
			case CTemplateBuff::BUFFFUNC_RANGEDAMAGE:
				{
					// ��������, �޶�����
					MapCellSearchEnemys tSearchEnemys(  pSrcEntity, 
							pBuffTpl->mBuff[ t ].mBuffParam[ 2 ],
							pBuffTpl->mBuff[ t ].mBuffParam[ 0 ],
							NULL );

					tSearchEnemys.Visit();

					// �����������������ҵ���ʵ��
					for (unsigned int i = 0; i < tSearchEnemys.mEnemys.size(); i ++ )
					{
						// ������(����)
						tSearchEnemys.mEnemys[ i ]->AddFunResult( pSrcEntity->GetEntityID( ), FUNC_ATTACKED, RESULT_NONE, true,
								pSrcEntity->GetEntityID( ), pBuffTpl->mTempID, 0, pSrcEntity->GetPosX( ), pSrcEntity->GetPosY( ) );

						// �˺�Ŀ��
						CPropertyModule::GetSingleton().EntityDamaged( pSrcEntity, tSearchEnemys.mEnemys[ i ], pBuffTpl->mBuff[ t ].mBuffParam[ 1 ], RESULT_NORMAL );
					}
				}
				break;
			case CTemplateBuff::BUFFFUNC_ADDSKILL:
				{
					if ( IsPlayer() == true )
					{
						CEntityPlayer* tpPlayer = (CEntityPlayer*)this;
						CPropertyPlayer* tpPro = (CPropertyPlayer*)tpPlayer->GetProperty();
						CSkillList&  tpSkill = tpPro->GetSkillList( );
						tpSkill.InsertSkill( pBuffTpl->mBuff[ t ].mBuffParam[ 0 ], pBuffTpl->mBuff[ t ].mBuffParam[ 1 ] );
					}
				}
				break;
            //ˢ�¼���cd add by yucx 20100625
            case CTemplateBuff::BUFFFUNC_REFRESHSKILLCD:
                {
                    if ( IsPlayer() == true )
                    {
                        CEntityPlayer* tpPlayer = (CEntityPlayer*)this;

                        OnBuffRefreshCD( tpPlayer, pBuffTpl->mBuff[ t ] );

                    }
                }
                break;
			case CTemplateBuff::BUFFFUNC_OBTEXP_BYTAB:
				{
					if ( IsPlayer() )
					{
						int tExp=0;
						CTemplateLevelExp* tpLevelExp = (CTemplateLevelExp*) CDataStatic::SearchTpl( pBuffTpl->mBuff[ t ].mBuffParam[ 0 ] ); 
						CEntityPlayer* tpPlayer = (CEntityPlayer*)this;
						if(NULL != tpLevelExp)
						{    
							if (tpPlayer->GetLevel( )>0 && tpPlayer->GetLevel( )<TMP_MAX_GRADE)
								tExp = (int) ( tpLevelExp->mLevelExp[ tpPlayer->GetLevel( ) ]);    
						}
						CPropertyModule::GetSingleton().PlayerObtainExp( tpPlayer, tExp, EXPREASON_BUFF);
					}
				}
				break;
			case CTemplateBuff::BUFFFUNC_BUFFAFTERBUFF:
				{
					if ( pDesProperty == NULL )
						break;

					int tSucessRate = pBuffTpl->mBuff[t].mBuffParam[0] ;
					int tSuccessTplID = pBuffTpl->mBuff[t].mBuffParam[1] ;
					int tFailTplID = pBuffTpl->mBuff[t].mBuffParam[2] ;

					int tRand = RAND(SERVER_PERCENT_INT);
					if ( tRand > tSucessRate )
					{
						//�ɹ�Ŀ����buff
						CTemplateBuff *tpBuffTemplate = (CTemplateBuff *)CDataStatic::SearchTpl(tSuccessTplID);
						if ( tpBuffTemplate == NULL )
						{
							LOG_DEBUG( "pro", "ATTACKEVENT : can't find CTemplateBuff : BuffID ( %d )\n", pBuffTpl->mBuff[t].mBuffParam[1] );
							continue;
						}
						this->EntityInsertBuff(pSrcEntity, tpBuffTemplate);
					}
					else
					{
						//ʧ���Լ���buff
						CTemplateBuff *tpBuffTemplate = (CTemplateBuff *)CDataStatic::SearchTpl(tFailTplID);
						if ( tpBuffTemplate == NULL )
						{
							LOG_DEBUG( "pro", "ATTACKEVENT : can't find CTemplateBuff : BuffID ( %d )\n", pBuffTpl->mBuff[t].mBuffParam[1] );
							continue;
						}
						pSrcEntity->EntityInsertBuff(pSrcEntity, tpBuffTemplate);
					}
				}
				break;

			//����HP���̶�ֵ
			case CTemplateBuff::BUFFFUNC_REDUCEHPTO:
				{		
						if ( pBuffTpl->mBuff[t].mBuffParam[0] <= 0 )
							break;
						
						int tTemp = pSrcProperty->GetCurHP() - pBuffTpl->mBuff[t].mBuffParam[0] ;
						if ( tTemp > 0 )
						{
							ExpendHP(tTemp , pSrcProperty->GetEntityID());
						}
						
				}
				break;
				
			//����MP���̶�ֵ
			case CTemplateBuff::BUFFFUNC_REDUCEMPTO:
				{
						if ( pBuffTpl->mBuff[t].mBuffParam[0] <= 0 )
							break;

						int tTemp = pSrcProperty->GetCurMP() - pBuffTpl->mBuff[t].mBuffParam[0] ;
						if ( tTemp > 0 )
						{
							ExpendMP(tTemp, pSrcProperty->GetEntityID());
						}
				}
				break;

			default:
				break;
		}
	}
}


// �ָ�HP
int CEntityCharacter::CureHP( int vCureHP, unsigned int nSrcEntityID, EResultType emType, bool bAddFunc )
{
	CPropertyCharacter* pProperty = (CPropertyCharacter*) GetProperty();
	
	// ��Ѫ�Ͳ��û���
	if( pProperty->GetCurHP() == (unsigned int)( pProperty->GetMaxHP().mInitValue + pProperty->GetMaxHP().mDeltaValue) )
	{
		return 0;
	}

	if ( vCureHP <= 0 )
		return 0;

	int tCureHP = vCureHP;
	int tOldHP = pProperty->GetCurHP();
	// �������͵ȡHP,����㽵��������
	if ( emType != RESULT_STEALHP )
	{
		if( pProperty->GetStateParam( STATE_CUREHPLESS ).mInState == true )
		{
			int tLessPer = std::min( (int)(pProperty->GetStateParam( STATE_CUREHPLESS ).mParames1), SERVER_PERCENT_INT );
			tCureHP = (int)( tCureHP / SERVER_PERCENT_FLOAT * ( SERVER_PERCENT_FLOAT - tLessPer ) );
			if ( tCureHP == 0 )
				return 0;
		}
	}

	pProperty->SetCurHP( std::min( (unsigned int)pProperty->GetMaxHP(), pProperty->GetCurHP( ) + tCureHP ) );
	int nRealChangeHP = pProperty->GetCurHP() - tOldHP;
	
	if ( bAddFunc == true )
		AddFunResult( nSrcEntityID, FUNC_INCHP, emType, true, pProperty->GetCurHP() - tOldHP, pProperty->GetCurHP(), pProperty->GetMaxHP() );

	return nRealChangeHP;
}

// �ָ�MP
int CEntityCharacter::CureMP( int vCureMP, unsigned int nSrcEntityID, EResultType emType, bool bAddFunc )
{
	if ( vCureMP <= 0 )
		return 0;

	CPropertyCharacter* pProperty = (CPropertyCharacter*) GetProperty();

	int nOldMP = pProperty->GetCurMP();
	vCureMP = std::min( (unsigned int)pProperty->GetMaxMP( ), pProperty->GetCurMP( ) + vCureMP );
	pProperty->SetCurMP( vCureMP );
	int nRealChangeMP = pProperty->GetCurMP() - nOldMP;
	
	if ( bAddFunc == true )
		AddFunResult( nSrcEntityID, FUNC_INCMP, emType, true, nRealChangeMP, pProperty->GetCurMP(), pProperty->GetMaxMP() );

	return nRealChangeMP;
}

// �ָ�AP
int CEntityCharacter::CureAP( int vCureAP, unsigned int nSrcEntityID, EResultType emType, bool bAddFunc )
{
	if ( vCureAP <= 0 )
		return 0;

	CPropertyCharacter* pProperty = (CPropertyCharacter*) GetProperty();

	int nOldAP = pProperty->GetCurAP();
	vCureAP = std::min( (unsigned int)pProperty->GetMaxAP( ), pProperty->GetCurAP( ) + vCureAP );
	pProperty->SetCurAP( vCureAP );
	int nRealChangeAP = pProperty->GetCurAP() - nOldAP;

	if ( bAddFunc == true )
		AddFunResult( nSrcEntityID, FUNC_INCAP, emType, true, nRealChangeAP, pProperty->GetCurAP(), pProperty->GetMaxAP() );

	return nRealChangeAP;
}

//************************************
// Method:    ExpendHP
// FullName:  CEntityCharacter::ExpendHP
// Access:    virtual public 
// Returns:   int �������ĵ�HP
// Qualifier: ����HP (���ʣ��HP>=0)
// Parameter: int vCureHP
// Parameter: unsigned int nSrcEntityID
// Parameter: EResultType emType
// Parameter: bool bAddFunc
//************************************
int CEntityCharacter::ExpendHP( int vCureHP, unsigned int nSrcEntityID, EResultType emType, bool bAddFunc )
{
	if ( vCureHP <= 0 )
		return 0;

	CPropertyCharacter* pProperty = (CPropertyCharacter*) GetProperty();

	int nOldHP = pProperty->GetCurHP();
	int nLeftHP = std::max( 0, nOldHP - vCureHP );
	pProperty->SetCurHP( nLeftHP );

	if ( IsPlayer( ) == true )
	{
		int tOldPer = nOldHP * 1.0 / (int)pProperty->GetMaxHP( ) * SERVER_PERCENT_INT;
		int tNewPer = pProperty->GetCurHP() * 1.0 / (int)pProperty->GetMaxHP( ) * SERVER_PERCENT_INT;
		((CPropertyPlayer*)pProperty)->InsertSelfBuff( NULL, CTemplateProperty::PROPERTYFUNC_HPSKILL, tOldPer, tNewPer );
	}
	
	// ����ϢʱHP����Ҫ��ԭʼ���ģ���ʹ��ʣ��HP����������Ҳ���ʾ��ˬ
	if ( bAddFunc == true )
		AddFunResult( nSrcEntityID, FUNC_DECHP, emType, true, vCureHP, pProperty->GetCurHP(), pProperty->GetMaxHP() );

	return nOldHP - pProperty->GetCurHP();
}


//************************************
// Method:    ExpendMP
// FullName:  CEntityCharacter::ExpendMP
// Access:    virtual public 
// Returns:   int  �������ĵ�HP
// Qualifier: ����MP (���ʣ��HP>=0)
// Parameter: int vExpendMP
// Parameter: unsigned int nSrcEntityID
// Parameter: EResultType emType
// Parameter: bool bAddFunc
//************************************
int CEntityCharacter::ExpendMP( int vExpendMP, unsigned int nSrcEntityID, EResultType emType, bool bAddFunc )
{
	if ( vExpendMP <= 0 )
		return 0;

	CPropertyCharacter* pProperty = (CPropertyCharacter*) GetProperty();

	int tOldMP = pProperty->GetCurMP();

	// ʵ��MP����,�������˺��б�,���Ծ��������������Ķ�
	int nLeftMP = std::max( (int)( pProperty->GetCurMP( ) - vExpendMP ), 0 );

	pProperty->SetCurMP( nLeftMP );

	if ( bAddFunc == true )
		AddFunResult( nSrcEntityID, FUNC_DECMP, emType, true, vExpendMP, pProperty->GetCurMP(), pProperty->GetMaxMP() );

	return tOldMP - pProperty->GetCurMP();
}

// ͵ȡHP
int CEntityCharacter::StealHP( int nDamage )
{
	if ( nDamage <= 0 )
		return 0;

	CPropertyCharacter* pProperty = (CPropertyCharacter*) GetProperty();

	int tStealHPPer = CPropertyFormula::GetStealHP( pProperty );

	if ( tStealHPPer > 0 )
	{
		int tStealHP = (int)(nDamage * tStealHPPer / SERVER_PERCENT_FLOAT);
		return CureHP( tStealHP, GetEntityID(), RESULT_STEALHP );
	}

	return 0;
}

// ͵ȡMP
int CEntityCharacter::StealMP( int nDamage )
{
	if ( nDamage <= 0 )
		return 0;

	CPropertyCharacter* pProperty = (CPropertyCharacter*) GetProperty();

	int tStealMPPer = CPropertyFormula::GetStealMP( pProperty );

	if ( tStealMPPer > 0 )
	{
		int tStealMP = (int)(nDamage * tStealMPPer / SERVER_PERCENT_FLOAT);
		return CureMP( tStealMP, GetEntityID(), RESULT_STEALMP );
	}

	return 0;
}

// ˲��ı�λ��
void CEntityCharacter::ChangePos( CWTPoint vPos, EResultType emType, unsigned int nSrcEntityID )
{
	AddFunResult( nSrcEntityID, FUNC_CHANGEPOS, emType, true, vPos.mX, vPos.mY );
	
	//TODO: ����һ��Ҫ�ȷ���һ��FunResult, ����ȸ��������Ժ��ٷ��Ļ��ͻ����ü���ʱ
	// ��ԭ�����Ŀ������Բ��ϣ��������ܹ�ȥ�ٱ��ֵ������һ��Ҫ�ڸú����ȷ�������Move֮ǰ����
	CPropertyModule::GetSingletonPtr()->ResultListSend();
	
	CMapModule::GetSingleton().OnEntityMove( this, vPos );

	// ֪ͨ����ģ��
	CTradeModule::GetSingleton().OnCancelTrade( mEntityID );
}



// ʵ������ʱ,���BUFF
void CEntityCharacter::RemoveBuffEntityDie()
{
	CPropertyCharacter* pDesProperty = (CPropertyCharacter*) GetProperty();
	CBuffList *tpBuff = pDesProperty->GetBuffList( );

	// �������״̬ 
	pDesProperty->CleanStateParam( );
	
	// �������buff
	tpBuff->RemoveAllBuff( this );
}

// ��������,��һ�þ��� ( ��ʱֻ��OGRE�� )

//****************************************************//
// CEntityRedStone
//**************************************************// 
bool CEntityRedStone::Setup( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator, CWTPoint* pPos, bool bInit, int vNpcID ) 
{
	CRedstondeCreator *tpCreator = ( CRedstondeCreator * )pCreator;
	
	CWTPoint tOrginPos = CWTPoint( tpCreator->mCenterX, tpCreator->mCenterY );
	// ����Ǳ������䣬Ҫ��һ�����λ��
	if ( tpCreator->mDropType == DROP_OBJECTIVE )
	{
		CMapModule::GetSingletonPtr()->GetDropPos( usLineID, usMapID, usMapIndex, tOrginPos );
	}
	//TODO: ��ʱû�У��ȴ��ͻ����ϱ� . ������������䣬�жϵ����λ��
	//else if ( tpCreator->mDropType == DROP_SUBJECTIVE )
	//{
	//	if ( CMapModule::GetSingletonPtr()->IsStaticBlock( usLineID, usMapID, usMapIndex, tOrginPos ) > 0 )
	//	{
	//		return false;
	//	}
	//	else if ( CMapModule::GetSingletonPtr()->IsOccupied( usLineID, usMapID, usMapIndex, tOrginPos, ENTITYTYPE_ITEM ) )
	//	{
	//		return false;
	//	}
	//}	
	
	mLineID = usLineID;
	mMapID  = usMapID;
	mIndex = usMapIndex;	
	SetEntityType( ENTITYTYPE_REDSTONE );	
	mPos = tOrginPos;
	mDirection = DIR_DOWN;
	mAliveState = ALIVE_NORMAL;	
	memcpy( mOwnerID,tpCreator->GetOwnerID(), sizeof( mOwnerID ) );	
	mTeamID = 0;
	mProcessTimerID = 0;
	GetProperty()->SetPropertyTempID( tpCreator->mItemID );
	GetProperty()->SetEntityID( this->get_id() );	
	SetEntityID( this->get_id() );	

	tpCreator->mHasOgre = GetEntityID();
	return true;
}
bool CEntityRedStone::CheckIfOwner( int vCharID )
{
	if ( mStatus == (int)REDSTONE_STATUS_PROTECT )
	{
		for( int i = 0; i < TEAMNUM ; i++ )
		{
			if( vCharID == (int)mOwnerID[i] )
			{
				return true;
			}
		}
		return false;
	}
	else if ( mStatus == (int)REDSTONE_STATUS_DROP )
	{
		return true;
	}
	else
	{
		return false;
	}
	
} 

// ���崥��
bool CEntityPedal::IsTouch( int vTickOffset )
{
	//if ( GetPedalType() == PEDAL_TELEPORT )
	//{
	//	// ����̤��
	//	TeleAction( vTickOffset );
	//}
	//else
	if ( GetPedalType() == PEDAL_TRAP )
	{
		// ����
		return TrapAction( );
	}
	else if( GetPedalType() == PEDAL_HIEROGRAM )
	{
		// ���
		return HierogramAction( );
	}
	else if( GetPedalType() == PEDAL_NEEDFIRE )
	{
		return NeedfireAction();
	}
	else
	{
		return true;
	}

	return false;
}

// ʵ���Ƿ�������/���͵���
bool CEntityPedal::IsTouchOn( CEntity* pEntity )
{
	if( mSrcRect.TopLeft().mX <= pEntity->GetPosX()
		&& mSrcRect.TopLeft().mY <= pEntity->GetPosY()
		&& mSrcRect.BottomRight().mX >= pEntity->GetPosX()
		&&  mSrcRect.BottomRight().mY >= pEntity->GetPosY() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

// ���Ͷ���
void CEntityPedal::TeleAction( int vTickOffset )
{
	// ����̤��ÿ500���봥��һ��,���Ե���
	if ( GetDelayTimer() > 0 )
	{
		unsigned int tTimer = std::max( (int)( GetDelayTimer() - vTickOffset ), 0 );
		SetDelayTimer( tTimer );
		if ( GetDelayTimer() > 0 )
			return;
	}

	SetDelayTimer( 500 );
#ifdef _FB_
	CMapObject* tpMapObj = CMapObjManager::GetSingletonPtr( )->GetMapObject( GetLineID( ), GetMapID( ), 
		GetMapIndex( ) );
#endif

	// ����̤���ϵ�ʵ��
	MapCellPedalSearcher tPedalSearcher(this);
	tPedalSearcher.Visit();

	for ( std::vector<CEntityCharacter*>::iterator it = tPedalSearcher.mEntitysOnPedal.begin();
		it != tPedalSearcher.mEntitysOnPedal.end();
		++ it)
	{
		CEntityPlayer* tpPlayer = (CEntityPlayer*) (*it);

		if( tpPlayer->GetNationality( ) == Zero	)
			continue;

#ifndef _FB_
		CMapModule::GetSingletonPtr()->Teleport( GetDstLineID(), GetDstMapID(), 
			GetDesPos().mX, GetDesPos().mY, tpPlayer );
#else
		if( tpMapObj == NULL )
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ] Cannt Find Teleport( %d ) Map( %d : %d : %d )", __LK_FILE__,
				__LINE__, __FUNCTION__, GetEntityID( ),  GetLineID( ), GetMapID( ), GetMapIndex( ) );
			continue;
		}
		CMapModule::GetSingletonPtr()->Teleport( GetDstLineID(), GetDstMapID(), GetDesPos().mX, GetDesPos().mY, 
			tpPlayer, INVALID_MAP_INDEX, ( tpMapObj != NULL ) ? tpMapObj->GetKey( ) : INVITED_KEY_VALUE );
#endif
	}
}

// ���嶯��
bool CEntityPedal::TrapAction( )
{
	CTemplateTrapSkill* tpTrapTpl = (CTemplateTrapSkill*) CDataStatic::SearchSkill( GetSkillID( ), GetSkillLevel( ) );
	if ( tpTrapTpl == NULL )
	{
		LOG_ERROR( "pro", "[ %s : %d ] [ %s ] can't find tripskill template SkillID( %d ) SkillLevel( %d )", __LK_FILE__, __LINE__, __FUNCTION__, GetSkillID( ), GetSkillLevel( ) );
		return false;
	}

	MapCellPedalSearcher tPedalSearcher(this);	

	CEntityCharacter* tpOwner = (CEntityCharacter*) GetOwner();
	LK_ASSERT ( tpOwner != NULL, return false );

	tPedalSearcher.Visit( );
	if ( tPedalSearcher.mEntitysOnPedal.size() == 0 )
		return false;

	// ���㹥�����к�
	AddAttackCount( );
	InitFunResult( GetAttListID( ) );

	int nEntityFunNum = 0; // ����ʵ����

	tPedalSearcher.Visit2( );
	for ( std::vector<CEntityCharacter*>::iterator it = tPedalSearcher.mEntitysOnPedal.begin();
		it != tPedalSearcher.mEntitysOnPedal.end() && nEntityFunNum < PDEAL_LIMIT; 
		++ it )
	{
		CEntityCharacter* pEntityCharctor = *it;

		// �ж��Ƿ��ܹ�����
		if ( CPropertyModule::GetSingleton().EntityPKValid( tpOwner, pEntityCharctor, tpTrapTpl ) )
		{
			// ����buff
			PedalBuffSkill( tpOwner, pEntityCharctor, tpTrapTpl );

			// ����ǵ�������,�����Ѿ�����,���˳�
			// ���۵��幥�����Ƿ�Χ����,����Ҫ�����б��еĵ�һ��ʵ��
			if ( ++nEntityFunNum > 0 && tpTrapTpl->mApplyType == CTemplateTrapSkill::APPLYTYPE_SINGLE )
				break;
			if ( nEntityFunNum >= tpTrapTpl->mEffectMaxNumber )
				break;
		}
	}

	if( nEntityFunNum > 0 )
	{
		// ���幦����
		AddFunResult( GetEntityID(), FUNC_TRAPONTOUCH, RESULT_NONE, true, GetSkillID( ), GetSkillLevel( ), GetPosX(), GetPosY() );

		// �������
		CSceneLogic::GetSingleton().AddDeleteList( this->GetEntityID() );

		CPropertyCharacter* tpProOwner = (CPropertyCharacter*) tpOwner->GetProperty();
		for ( int i = 0; i < tpProOwner->GetTripEntityIDListSize( ); i++ )
		{
			if ( tpProOwner->GetTripEntityIDList( i ).mTripEntityID == (int) GetEntityID() )
			{
				tpProOwner->GetTripEntityIDList( i ).Clean();
			}
		}

		// ����������Ϣ
		CPropertyModule::GetSingleton( ).ResultListSend( );
	}
	else
	{
		//����δ����
		return false;
	}

	return true;
}

// �������
bool CEntityPedal::HierogramAction( )
{
	MapCellPedalSearcher tPedalSearcher(this);
	tPedalSearcher.Visit();

	for ( std::vector<CEntityCharacter*>::iterator it = tPedalSearcher.mEntitysOnPedal.begin();
		it != tPedalSearcher.mEntitysOnPedal.end() ;
		++ it )
	{
		CEntityCharacter* tpEntityCharactor = *it;

		// �ж��Ƿ��ܹ�����
		if ( tpEntityCharactor->IsPlayer() )
		{
			// ��������
			OnEntityHierogram( (CEntityPlayer*) tpEntityCharactor );

			// �������
			CSceneLogic::GetSingleton().AddDeleteList( this->GetEntityID() );

			return true;
		}
	}

	return false;
}


/* --------------------------------------------------------------------------*/
/* 
* @Synopsis ���涯��
*/ 
/* ----------------------------------------------------------------------------*/
bool CEntityPedal::NeedfireAction( )
{

	CTemplateTrapSkill* tpTrapTpl = (CTemplateTrapSkill*) CDataStatic::SearchSkill( GetSkillID( ), GetSkillLevel( ) );
	if ( tpTrapTpl == NULL )
	{
		LOG_ERROR( "pro", "[ %s : %d ] [ %s ] can't find tripskill template SkillID( %d ) SkillLevel( %d )", __LK_FILE__, __LINE__, __FUNCTION__, GetSkillID( ), GetSkillLevel( ) );
		return false;
	}

	MapCellPedalSearcher tPedalSearcher(this);	


	tPedalSearcher.Visit( );
	if ( tPedalSearcher.mEntitysOnPedal.size() == 0 )
		return false;

	// ���㹥�����к�
	AddAttackCount( );
	InitFunResult( GetAttListID( ) );

	int nEntityFunNum = 0; // ����ʵ����

	tPedalSearcher.Visit2( );
	for ( std::vector<CEntityCharacter*>::iterator it = tPedalSearcher.mEntitysOnPedal.begin();
		it != tPedalSearcher.mEntitysOnPedal.end() && nEntityFunNum < PDEAL_LIMIT; 
		++ it )
	{
		CEntityCharacter* pEntityCharctor = *it;

		PedalBuffSkill( pEntityCharctor, pEntityCharctor, tpTrapTpl );
	}

	return true;
}


void CEntityPedal::OnEntityHierogram( CEntityPlayer* pPlayer )
{
	LK_ASSERT( pPlayer != NULL, return );
	
	CTplHierogram* tpTpl = ( CTplHierogram* )CDataStatic::SearchTpl( mNpcID );
	LK_ASSERT_STR( tpTpl != NULL, return, "TempID %d", mNpcID );

	if( tpTpl->mType == CTplHierogram::USE_SKILL )
	{
		CTemplateSkill* tpSkill = (CTemplateSkill*)CDataStatic::SearchSkill( tpTpl->mParame[ 0 ], tpTpl->mParame[ 1 ] );
		LK_ASSERT_STR( tpSkill != NULL, return, "TempID %d, SkillID %d, SkillLevel %d", mNpcID, tpTpl->mParame[ 0 ],
			tpTpl->mParame[ 1 ] );

		// ���㹥�����к�
		AddAttackCount( );
		InitFunResult( GetAttListID( ) );
		CPropertyModule::GetSingletonPtr( )->UseSkillForServer( pPlayer, pPlayer, tpSkill, NULL, 0 );

		CPropertyModule::GetSingleton( ).ResultListSend( );
	}
}

// ����BUFF����
void CEntityPedal::PedalBuffSkill( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateTrapSkill* pTrapSkill, int vSkillType )
{
	if ( pSrcEntity != NULL && pDesEntity != NULL && pTrapSkill != NULL )
	{
		EResultType tResult = RESULT_NORMAL;
		int tDamage = CPropertyFormula::GetPSkillAttack( pSrcEntity, pDesEntity, pTrapSkill, tResult );
		
		// ���㼼�����Buff
		CPropertyModule::GetSingletonPtr()->EntityBuffSkill( pSrcEntity, pDesEntity, pTrapSkill->mBuffGroupID, ARRAY_CNT(pTrapSkill->mBuffGroupID), vSkillType, tDamage );
	}

}

// �ֶ�ɾ��BUFF
bool CEntityCharacter::ActiveRemoveBuff( int nBuffID )
{
	CTemplateBuff* tpBuffTpl = (CTemplateBuff*) CDataStatic::SearchTpl( nBuffID );
	if ( tpBuffTpl == NULL )
	{
		LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] CTemplateBuff cann't find, BuffID = %d", __LK_FILE__, __LINE__, __FUNCTION__, nBuffID );
		return false;
	}

	// �����������
	if ( tpBuffTpl->mCancelBuff == CTemplateBuff::BUFF_NOTCANCEL )
		return false;

	int tnRtn = EntityRemoveBuff( nBuffID );

	//LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] Remove Buff! for ActiveRemoveBuff error test!", __LK_FILE__, __LINE__, __FUNCTION__ );
	if ( tnRtn < 0 )
	{
		LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] BUFF Active Remove Error! ErrorCode = %d, BuffID = %d", __LK_FILE__, __LINE__, __FUNCTION__, tnRtn, nBuffID );
		return false;
	}

	return true;
}

// �Ƿ����ͨ��
bool CEntityCharacter::CanPass( unsigned int nPosX, unsigned int nPosY )
{
	if ( IsPlayer() || IsPet() )
	{
		return CMapModule::GetSingleton().CanPlayerPass( GetLineID(), GetMapID(), GetMapIndex(), nPosX, nPosY, CanFly() );
	}	
	else if ( IsOgre() || IsFunNpc() )
	{
		return CMapModule::GetSingleton().CanNpcPass( GetLineID(), GetMapID(), GetMapIndex(), nPosX, nPosY, CanFly() );
	}
	return false;
}


// ʵ���Ƿ���buff
bool CEntityCharacter::HasBuff( int nBuffID ) 
{
	CPropertyCharacter* pProCharacter = (CPropertyCharacter*)GetProperty();

	// buff�б�����ΪNULL
	return pProCharacter->GetBuffList()->HasBuff( nBuffID);

}

bool CEntityCharacter::CanFly( )
{
	bool tState = false;
	if ( IsPlayer() || IsPet() )
	{		
		if ( IsPlayer() )
		{
			CEntityPlayer *tpPlayer = (CEntityPlayer*)this;
			CPropertyPlayer *tpProperty = (CPropertyPlayer*)tpPlayer->GetProperty();
			tState = tpProperty->GetStateParam( STATE_FLY ).mInState;
		}
		else if ( IsPet() )
		{
			CEntityPet *tpPet = (CEntityPet*)this;
			CPropertyPet *tpProperty = (CPropertyPet*)tpPet->GetProperty();
			tState = tpProperty->GetStateParam( STATE_FLY ).mInState;
		}

		return tState;
	}	
	else if ( IsOgre() || IsFunNpc() )
	{
		if ( IsOgre() )
		{
			CEntityOgre *tpNpc = (CEntityOgre*)this;
			CPropertyNPC *tpProperty = (CPropertyNPC*)tpNpc->GetProperty();
			tState = tpProperty->GetStateParam( STATE_FLY ).mInState;
		}	
		else if ( IsFunNpc() )
		{
			CEntityFuncNpc *tpNpc = (CEntityFuncNpc*)this;
			CPropertyNPC *tpProperty = (CPropertyNPC*)tpNpc->GetProperty();
			tState = tpProperty->GetStateParam( STATE_FLY ).mInState;
		}
		return tState;
	}
	return false;
}

//************************************
// Method:    BuffTimeEvent
// FullName:  CEntityCharacter::BuffTimeEvent
// Access:    public 
// Returns:   void
// Qualifier: buff������ʵ����
// Parameter: CTemplateBuff * tpBuffTpl
// Parameter: CBuffObject * tpBuff
//************************************
void CEntityCharacter::BuffTimeEvent( CTemplateBuff* tpBuffTpl, CBuffObject* tpBuff )
{
	for ( int j = 0; j < (int)ARRAY_CNT( tpBuffTpl->mBuff ) && IsAlive( ); j ++ )
	{
		if ( tpBuffTpl->mBuff[ j ].mBuffFunc == 0 )
			break;

		switch( tpBuffTpl->mBuff[ j ].mBuffFunc )
		{
			// ������Ѫ
		case CTemplateBuff::BUFFFUNC_PERSISTINCFIXHP:
			{
				float tParam1 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mHotparam1 / SERVER_PERCENT_FLOAT;
				float tParam2 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mHotparam2 / SERVER_PERCENT_FLOAT;
				int tCure = tpBuffTpl->mBuff[ j ].mBuffParam[ 0 ] + tParam1 * pow( tParam2, tpBuffTpl->mSkillLevel ) * tpBuff->mAttack / ( tpBuffTpl->mLastTime / 1000 );
				CureHP( tCure );
			}
			break;
			// ��������
		case CTemplateBuff::BUFFFUNC_PERSISTINCFIXMP:
			{
				CureMP( tpBuffTpl->mBuff[ j ].mBuffParam[ 0 ] );
			}
			break;
			// �����˺�
		case CTemplateBuff::BUFFFUNC_PERSISTDECFIXHP:
			{
				float tParam1 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDotparam1 / SERVER_PERCENT_FLOAT;
				float tParam2 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDotparam2 / SERVER_PERCENT_FLOAT;
				int tDamage = tpBuffTpl->mBuff[ j ].mBuffParam[ 0 ] + tParam1 * pow( tParam2, tpBuffTpl->mSkillLevel ) * tpBuff->mAttack / ( tpBuffTpl->mLastTime / 1000 );

				CEntityCharacter* pBuffSrcEntity = (CEntityCharacter*)CSceneLogic::GetSingletonPtr()->GetEntity( tpBuff->GetBuffSrcEntityID() );

				PERF_FUNC( "EntityDamage", CPropertyModule::GetSingletonPtr()->EntityDamaged( pBuffSrcEntity, this, tDamage, RESULT_NORMAL ) );
			}
			break;
			// �������ٷֱ��˺�
		case CTemplateBuff::BUFFFUNC_PERSISTDECPERHP:
			{

				CPropertyCharacter* tpProperty = (CPropertyCharacter*) GetProperty( );
				int tDamage = (int) ( ( (int)tpProperty->GetMaxHP( ) ) * (tpBuffTpl->mBuff[ j ].mBuffParam[ 0 ] / SERVER_PERCENT_FLOAT) );
				CEntityCharacter* pBuffSrcEntity = (CEntityCharacter*)CSceneLogic::GetSingletonPtr()->GetEntity( tpBuff->GetBuffSrcEntityID() );
				PERF_FUNC( "EntityDamage", CPropertyModule::GetSingletonPtr()->EntityDamaged( pBuffSrcEntity, this, tDamage, RESULT_NORMAL ) );
			}
			break;
			// ��������
		case CTemplateBuff::BUFFFUNC_PERSISTDECFIXMP:
			{
				ExpendMP( tpBuffTpl->mBuff[ j ].mBuffParam[ 0 ], tpBuff->GetBuffSrcEntityID() );

				// ������Ĺ���,��ɾ��BUFF,��Ҫ������BUFF����ɾ��
				if ( (int) ((CPropertyCharacter*)GetProperty())->GetCurHP() < tpBuffTpl->mBuff[ j ].mBuffParam[ 0 ] 
					&& ( tpBuffTpl->mBuffType == CTemplateBuff::BUFF_INC ) )
					{
						tpBuff->mPersistTime = 0;
					}
			}
			break;
			// �뿪��debuffʱ������Χ���ܵ�����Ч��
		case CTemplateBuff::BUFFFUNC_LEAVEAREA:
			{
				CWTPoint tPoint( tpBuff->mParames[ j ] >> 16, tpBuff->mParames[ j ] & 0x0000FFFF );
				if( GetPos( ).LimitDistance( tPoint, tpBuffTpl->mBuff[ j ].mBuffParam[ 0 ] ) == false )
				{
					//LOG_DEBUG( "pro", "[ %s : %d ][ %s ]Entity( %d ) Buff LeveEvent, InsertBuff Pos( %d"
					//	" : %d ), Now Pos(%d : %d ), Distance = %d, BuffPersistTime=%d", __LK_FILE__,
					//	__LINE__, __FUNCTION__, GetEntityID(), tPoint.mX, tPoint.mY, GetPosX( ),
					//	GetPosY( ), tpBuffTpl->mBuff[ j ].mBuffParam[ 0 ], tpBuff->mPersistTime );

					CTemplateBuff* tpBuffTemplate = (CTemplateBuff*)CDataStatic::SearchTpl( 
						tpBuffTpl->mBuff[ j ].mBuffParam[ 1 ] );

					if( tpBuffTemplate != NULL )
					{
						CEntityCharacter* pBuffSrcEntity = (CEntityCharacter*)CSceneLogic::GetSingletonPtr()->GetEntity( tpBuff->GetBuffSrcEntityID() );
						EntityInsertBuff( pBuffSrcEntity, tpBuffTemplate );
					}
					tpBuff->mPersistTime = 0;
				}
				else
				{
					tpBuff->mLastInterval = 0;
				}
			}
			break;
			// ������MaxHP�ٷֱȻָ�CurHP
		case CTemplateBuff::BUFFFUNC_PERSISTINCPERHP:
			{
				// ֻ��character����HP
				CPropertyCharacter* tpProperty = (CPropertyCharacter*) GetProperty( );
				int tIncHP = (int) ( ( (int)tpProperty->GetMaxHP( ) ) * (tpBuffTpl->mBuff[ j ].mBuffParam[ 0 ] / SERVER_PERCENT_FLOAT) );
				CureHP( tIncHP );

			}
			break;
			// ������MaxMP�ٷֱȻָ�CurMP
		case CTemplateBuff::BUFFFUNC_PERSISTINCPERMP:
			{
				// ֻ��character����HP
				CPropertyCharacter* tpProperty = (CPropertyCharacter*) GetProperty( );
				int tIncMP = (int) ( ( (int)tpProperty->GetMaxMP( ) ) * (tpBuffTpl->mBuff[ j ].mBuffParam[ 0 ] / SERVER_PERCENT_FLOAT) );
				CureMP( tIncMP );
			}
			break;
			// �������Ӿ���̶�ֵ
		case CTemplateBuff::BUFFFUNC_PERSISTINCFIXEXP:
			{
				// ֻ����Ҳ����ϻ�þ���buff
				if( IsPlayer() != true )
				{
					break;
				}
				CEntityPlayer* pPlayer = (CEntityPlayer*)this;
				int nCharID = pPlayer->GetCharID();

				int nFinalExp = CPropertyModule::GetSingletonPtr()->PlayerObtainExp( 
								pPlayer, tpBuffTpl->mBuff[ j ].mBuffParam[ 0 ], 1, &nCharID, 1 );

				if ( nFinalExp > 0)
				{
					LogEventGetExpByBuff(pPlayer, tpBuffTpl->mBuff[ j ].mBuffParam[ 0 ], nFinalExp, tpBuffTpl->mTempID);
				}

				break;
			}
		
		// �������Ӿ�����ҫֵ
		case CTemplateBuff::BUFFFUNC_INCCORPSGORY:
			{
				// ֻ����Ҳ����ϻ�þ���buff
				if( IsPlayer() != true )
				{
					break;
				}
				CEntityPlayer* pPlayer = (CEntityPlayer*)this;
				CCorpsModule::GetSingleton().ChangeCorpsGlory( pPlayer, tpBuffTpl->mBuff[j].mBuffParam[0] );
				break;
			}	
	
		// ����������ҹ�ѫ
		case CTemplateBuff::BUFFFUNC_INCAP:
			{
				// ֻ����Ҳ����ϻ�þ���buff
				if( IsPlayer() != true )
				{
					break;
				}
				CEntityPlayer* pPlayer = (CEntityPlayer*)this;	
				CPropertyModule::GetSingleton().OnPlayerObtainHonor( pPlayer, tpBuffTpl->mBuff[j].mBuffParam[0] );
				break;
			}
		default:
			break;
		}
	}
}


// �Ƿ����ͨ��
bool CEntityPlayer::CanPass( unsigned int nPosX, unsigned int nPosY )
{
	return CMapModule::GetSingleton().CanPlayerPass( GetLineID(), GetMapID(), GetMapIndex(), nPosX, nPosY, mProperty.GetStateParam( STATE_FLY ).mInState );
}

// �Ƿ����ͨ��
bool CEntityPet::CanPass( unsigned int nPosX, unsigned int nPosY )
{
	return CMapModule::GetSingleton().CanPlayerPass( GetLineID(), GetMapID(), GetMapIndex(), nPosX, nPosY, mProperty.GetStateParam( STATE_FLY ).mInState );
}

int CEntityPlayer::SpeedCheck( bool vIsCoerce )
{
	unsigned int tTickNow = CSceneServer::GetSingletonPtr( )->GetLastTickCount( );
	bool tNowCheck = false;

	if( vIsCoerce == false )
	{
		if( ( unsigned int )GetMoveDistance( ) >= 
			( unsigned int )( CSceneCfgManager::GetSingletonPtr( )->GetScenelogic_cfg( )->mMovecheckdistance ) )
		{
			tNowCheck = true;
		}
		else if( tTickNow > GetSpeekCheckTime( ) + 
			CSceneCfgManager::GetSingletonPtr( )->GetScenelogic_cfg( )->mMovechecktimespace )
		{
			if( GetMoveDistance( ) != 0 )
			{
				tNowCheck = true;
			}
			else
			{
				ResetSpeedCheck( );	
			}
		}
	}
	else
	{
		// �������ʱ�䴥���Ļ�,�������15��ż��һ��
		if( GetMoveDistance( ) >= 15 )
		{
			tNowCheck = true;
		}
		else
		{
			ResetSpeedCheck( );
		}
	}

	if( tNowCheck == true )
	{
		unsigned int tTime = ( GetSpeekCheckTime( ) < tTickNow ) ? ( tTickNow - GetSpeekCheckTime( ) ) : 0;
		CPropertyPlayer* tpPlayer = ( CPropertyPlayer* )GetProperty( );
		int tSpeed = tpPlayer->GetSpeed( );
		tSpeed = ( tSpeed > 30 ) ? tSpeed - 30 : tSpeed;

		int tLength = GetMoveDistance( );
		// �ٶȼ���Ƿ��д�
		if( tTime / tLength < ( unsigned int )tSpeed )
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ]Player( %s ) Speed Error, speed( %d ) time( %d ) distance( %d )",
				__LK_FILE__, __LINE__, __FUNCTION__, GetCharNameShow( ), tSpeed+30, tTime, GetMoveDistance( ) );
					
			// ������
//			CMapModule::GetSingletonPtr()->Teleport( GetLineID(), GetMapID(),  mLastCheckPoint.mX, mLastCheckPoint.mY, this );
		
//			ResetSpeedCheck( );
			SpeedCheckTeleport( );
			return SUCCESS;
		}

		LOG_DEBUG( "default", "[ %s : %d ][ %s ]Player(%s) Move Check, distance( %d ),time( %d ), server speed( %d )", 
			__LK_FILE__, __LINE__, __FUNCTION__, this->GetCharNameShow(), GetMoveDistance( ), tTime, tSpeed );
		

		ResetSpeedCheck( );
	}
	
	return SUCCESS;
}
 
int CEntityPlayer::SpeedCheckTeleport( )
{
	if( GetPosX( ) != mLastCheckPoint.mX || GetPosY( ) != mLastCheckPoint.mY )
	{
		CMapModule::GetSingletonPtr()->Teleport( GetLineID(), GetMapID(),  mLastCheckPoint.mX, mLastCheckPoint.mY, 
			this );
	}
	ResetSpeedCheck( );
	return SUCCESS;
}

int CEntityPlayer::ResetSpeedCheck( )
{
	mMoveDistance = 0; 
	mSpeedCheckTime = CSceneServer::GetSingletonPtr( )->GetLastTickCount( );
	mLastCheckPoint = GetPos();
	return SUCCESS;
}


// �����жϻ����
void CEntityCharacter::InterruptActivity()
{
	if ( IsPlayer() == false )
	{
		return ;
	}

	// ����ȡ��
	CTradeModule::GetSingleton().OnCancelTrade( mEntityID );

	// TODO

	return ;
}

/*
void CEntityBlock::EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf, bool vIsAward )
{
	CEntityOgre::EntityDie( pSrcEntity, bKillSelf, vIsAward );

	CTemplateBlock* tpTpl = ( CTemplateBlock* )CDataStatic::SearchTpl( GetNpcID( ) );
	CMapObject* tpMapObj = GetMapObject( );
	
	LK_ASSERT_STR( tpTpl != NULL, return, "TemplateID %d", GetNpcID( ) );
	LK_ASSERT_STR( tpMapObj != NULL, return, "MapID %d, LineID %d, Index %d", GetMapID( ), GetLineID( ), 
		GetMapIndex( ) );

	for( int i = 0; i <= ( int )ARRAY_CNT( tpTpl->mPos ); i++ )
	{
		if( tpTpl->mPos[ i ].mX == 0 && tpTpl->mPos[ i ].mY == 0 )
		{
			break;
		}

		int tX = GetPosX( ) + tpTpl->mPos[ i ].mX;
		int tY = GetPosY( ) + tpTpl->mPos[ i ].mY;

		tpMapObj->RemoveBlock( tX, tY );
	}
}

*/
void CEntityBlock::RemoveBlock( )
{
	CTemplateBlock* tpTpl = ( CTemplateBlock* )CDataStatic::SearchTpl( GetNpcID( ) );
	LK_ASSERT_STR( tpTpl != NULL, return, "Cannt GetTpl %d, EntityID %d", GetNpcID( ),
			GetEntityID( ) );

	CMapObject* tpMapObj = GetMapObject( );
	LK_ASSERT_STR( tpMapObj != NULL, return, "Cannt Get Entity( %d ) Map( %d : %d : %d )", GetEntityID( ), GetLineID( ),
		GetMapID( ), GetMapIndex( ) );

	unsigned int i = 0;

	for( i = 0; i < ARRAY_CNT( tpTpl->mPos ); i++ )
	{
		if( tpTpl->mPos[ i ].mX == 0 && tpTpl->mPos[ i ].mY == 0 )
		{
			break;
		}

		int tX = GetPosX( ) + tpTpl->mPos[ i ].mX;
		int tY = GetPosY( ) + tpTpl->mPos[ i ].mY;

		tpMapObj->RemoveBlock( tX, tY );
	}
}

int CEntityBlock::ChangeMode( )
{
	if( IsAlive( ) == true )
	{
		( ( CPropertyCharacter* )GetProperty( ) )->SetCurHP( 0 );
		EntityDie( this, true );
	}
	else
	{
		CPropertyModule::GetSingletonPtr( )->EntityRelive( this );
	}

	return SUCCESS;
}


int CEntityCharacter::SetCampID( int vCampID )
{
#ifdef _FB_
	CMessage tMsg;
	CMessageChangeCamp tChangeCamp;
	
	tChangeCamp.set_entityid( GetEntityID( ) );
	tChangeCamp.set_campid( vCampID );

	tMsg.mutable_msghead()->set_messageid( ID_S2C_CHANGE_CAMP );
	tMsg.set_msgpara( ( long ) &tChangeCamp );
	if( IsNpc( ) == true )
	{
		tChangeCamp.set_tempid( this->GetNpcID( ) );
	}
	if( IsPlayer( ) == true )
	{
		tChangeCamp.set_charid( ( ( CEntityPlayer* )this )->GetCharID( ) );
	}

	CMapObject* tpMapObj = GetMapObject( );
	LK_ASSERT_STR( tpMapObj != NULL, return ERR_UNKNOWN, "MapID %d, MapIndex %d", GetMapID( ), GetMapIndex( ) );

	tpMapObj->SendMsg2Player( &tMsg );
#endif
	return SUCCESS;
}

#ifdef _FB_
int CEntityPlayer::GetCampID( )
{
	CPlayerRepetion* tpRepetion = ( ( CPropertyPlayer* )GetProperty( ) )->GetRepetion( );
	if( CRepetionModule::GetSingletonPtr( )->IsBattleMap( GetMapID( ) ) == true )
	{
		return tpRepetion->GetCampID( );
	}

	return 0;
}
#endif

bool CEntityPlayer::RefrushPingTime( )
{
	unsigned int tTime = CSceneServer::GetSingletonPtr( )->GetLastTickCount( );
	if( ( tTime - mPingTime ) < ( _PLAYER_PING_TIME_MAX_ - 200 ) )
	{
		LOG_NOTICE( "default", "[ %s : %d ][ %s ] Player( %d : %d : %s ) PING Time LONG, Old %ud, Now %ud, Max %ud", 
			__LK_FILE__, __LINE__, __FUNCTION__, GetEntityID( ), GetCharID( ), GetCharNameShow( ), mPingTime, tTime, 
			_PLAYER_PING_TIME_MAX_ );
		mPingTime = tTime;
		return false;
	}

	mPingTime = tTime;

	return true;
}

int CEntityPlayer::GoldenNotice( )
{
    CMessageQueryGoldenYBResponse tPara;
    tPara.set_goldenyb( GetGoldenYB( ) );
    CMessage tMsg;
    tMsg.set_msgpara((uint32_t) &tPara);
	tMsg.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_QUERY_GOLDENYB ); 
    CSceneLogic::GetSingleton().Send2Player( this, &tMsg);

	return SUCCESS;
}

bool CEntityPlayer::CanRemainFly( )
{
	CPropertyPlayer *tpProperty = (CPropertyPlayer*)this->GetProperty();
	if ( tpProperty->IsVip() == false )
	{
		CTplItemHorse *tplHorse = (CTplItemHorse*)CDataStatic::SearchTpl( tpProperty->GetHorseTempID( ) );
		if ( tplHorse != NULL )
		{
			if ( ((int)tpProperty->GetCurAP()) < tplHorse->mDeltaAP )
			{
				return false;
			}
		}
	}
	return true;
}

// �͹���NPC�Ƿ��Ѻ�
bool CEntityFuncNpc::IsFriendlyTo( CEntity* pEntity )
{
	LK_ASSERT( pEntity != NULL, return true );

	// ������Լ�
	if( this == pEntity )
	{
		return true;
	}

	switch ( pEntity->GetEntityType() )
	{
	case ENTITYTYPE_PLAYER:
	case ENTITYTYPE_PET:
		{
			// �����ͬ��
			if ( GetOwnCampID() != 0 && pEntity->GetNationality() == GetOwnCampID() )
			{
				return true;
			}
			if ( GetNationality() == pEntity->GetNationality() ) 
			{
				if( ( mPKType & FRIEND_TO_SC ) == FRIEND_TO_SC || ( mPKType & FRIEND_WITH_SC ) == FRIEND_WITH_SC )
				{
					return true;
				}
			}
			// �����������
			else
			{
				if( ( mPKType & FRIEND_WITH_FC ) == FRIEND_WITH_FC || ( mPKType & FRIEND_TO_FC ) == FRIEND_TO_FC )
				{
					return true;
				}
			}
			break;
		}
	case ENTITYTYPE_OGRE:
	case ENTITYTYPE_FUNCNPC:
		{
			CEntityNpc *pNpc = (CEntityNpc *)pEntity; 
			if ( mGroupID == pNpc->GetGroupID() )
				return true;
			if ( ( mPKType & ENEMY_WITH_OGRE ) == ENEMY_WITH_OGRE )
			{
				return false;
			}
			break;
		}
	default:
		break;
	}

	return false;
}

bool CEntityCharacter::CanBeTransformed( )
{
	if ( IsPlayer() == true )
	{
		CEntityPlayer *tpPlayer = (CEntityPlayer*)this;
		CPropertyPlayer *tpProperty = (CPropertyPlayer*)tpPlayer->GetProperty();
		int tStateID = tpProperty->GetStateParam( STATE_TRANSFORM ).mParames1;
		CTemplateNpc *tplNpc = (CTemplateNpc*)CDataStatic::SearchTpl( tStateID );
		if ( tplNpc != NULL && tplNpc->mResistTran == 0 )
		{
			return false;
		}
		CTemplateEquipment *tplEquip = NULL;
		CItemEquipment* tpWeapon	= (CItemEquipment*) tpProperty->GetEquipment( )->GetItemObjPtr( EQUIPMENT_WEAPON );
		if ( tpWeapon != NULL && tpWeapon->IsOvertimed() == false )
		{
			tplEquip = (CTemplateEquipment*)CDataStatic::SearchTpl( tpWeapon->GetItemID() );
			if ( tplEquip != NULL && tplEquip->mResistTran == 0 )
			{
				return false;
			}
		}
		CItemEquipment* tpChest		= (CItemEquipment*) tpProperty->GetEquipment( )->GetItemObjPtr( EQUIPMENT_CHEST );
		if ( tpChest != NULL && tpChest->IsOvertimed() == false )
		{
			tplEquip = (CTemplateEquipment*)CDataStatic::SearchTpl( tpChest->GetItemID() );
			if ( tplEquip != NULL && tplEquip->mResistTran == 0 )
			{
				return false;
			}
		}
		CItemEquipment* tpFashion	= (CItemEquipment*) tpProperty->GetEquipment( )->GetItemObjPtr( EQUIPMENT_FASHION );
		if ( tpFashion != NULL && tpFashion->IsOvertimed() == false )
		{
			tplEquip = (CTemplateEquipment*)CDataStatic::SearchTpl( tpFashion->GetItemID() );
			if ( tplEquip != NULL && tplEquip->mResistTran == 0 )
			{
				return false;
			}
		}
	}
	if ( IsNpc() == true )
	{
		CEntityNpc *tpNpc = (CEntityNpc*)this;
		CTemplateNpc *tplNpc = (CTemplateNpc*)CDataStatic::SearchTpl( tpNpc->GetNpcID() );
		if ( tplNpc != NULL && tplNpc->mResistTran == 0 )
		{
			return false;
		}
	}
	return true;
}

/* --------------------------------------------------------------------------*/
/** 
 * * @Synopsis ˢ�¼������buff 
 * * 
 * * @Param tpPlayer
 * * @Param buffFunc CTemplateBuff�ڲ�����
 * */
/* ----------------------------------------------------------------------------*/

void CEntityCharacter::OnBuffRefreshCD( CEntityPlayer* tpPlayer, CTemplateBuff::CBuffFunc & buffFunc)
{

	LK_ASSERT( tpPlayer != NULL, return );

    CPropertyPlayer* tpPro = (CPropertyPlayer*)tpPlayer->GetProperty();
    CSkillList&  tpSkillList = tpPro->GetSkillList( );
    CGroupCDList& tpGroupCDList = tpPro->GetCDGroupList();
    CSkillObject* pSkillObj = NULL;
        
    // mBuffParam[0] = 0 ˢ��һ������      mBuffParam[1] Ҫˢ�µļ���id  mBuffParam[2] ��ˢ�µļ���id   
    //               = 1 ˢ��һ��ϵ�ļ���  mBuffParam[1] Ҫˢ�µļ���ϵ��id  
    //               = 2 ˢ��ȫ�弼��      
    //
        //ˢ��һ������
    if(buffFunc.mBuffParam[ 0 ] == 0 )
    {
        for( int i = 0 ; i < tpSkillList.GetSkillNum(); i++ )
        {
            
            pSkillObj =  tpSkillList.GetSkillObjectByIndex( i );
            if( pSkillObj == NULL)
                continue; 
            //Ҫˢ�µļ��� ���ǲ����Ǳ�����
            if(  (int)(pSkillObj->GetSkillID( )) == buffFunc.mBuffParam[ 1 ] &&  (int)(pSkillObj->GetSkillID( )) != buffFunc.mBuffParam[ 2 ] )
            {
                tpPro->OnSkillCDRefresh( pSkillObj, tpPlayer); 
            }
        }
    
    //ˢ��һ��ϵ�ļ���
    }else if(buffFunc.mBuffParam[ 0 ] == 1 )
    {
        CTemplateSkill* tpSkillTpl = NULL;

        for(   int i = 0 ; i < tpSkillList.GetSkillNum(); i++ )
        {
            pSkillObj = tpSkillList.GetSkillObjectByIndex( i );
        
            if( pSkillObj == NULL ||  pSkillObj->GetCooldown() == 0)
                continue;
            tpSkillTpl = pSkillObj->GetSkillTpl( ); 

            //����ϵ��
            if( tpSkillTpl == NULL || tpSkillTpl->mGenerID !=  buffFunc.mBuffParam[ 1 ]) 
                continue;
            //��ˢ�µļ���(������)
            if( (int)pSkillObj->GetSkillID( ) == buffFunc.mBuffParam[ 2 ] )
                continue;     
            tpPro->OnSkillCDRefresh( pSkillObj, tpPlayer); 
        }
    //ˢ��ȫ�弼��
    }else if(buffFunc.mBuffParam[ 0 ] == 2 )
    {
        //ˢ�¼���
        for(  int i = 0 ; i < tpSkillList.GetSkillNum(); i++ )
        {
            pSkillObj = tpSkillList.GetSkillObjectByIndex( i );
            if( pSkillObj == NULL || pSkillObj->GetCooldown() == 0)
                continue;
            
            //��ˢ�µļ���(������)
            if( (int)pSkillObj->GetSkillID( ) == buffFunc.mBuffParam[ 2 ] )
                continue;     
            tpPro->OnSkillCDRefresh( pSkillObj, tpPlayer); 
            
            CTemplateSkill *pSkillTpl = pSkillObj->GetSkillTpl( );

            //ˢ��cd��CD
            for ( int i = 0; i < (int)ARRAY_CNT( pSkillTpl->mCDGroup ); i ++ )
            {
                CGroupCD& rGroupCD = tpGroupCDList.GetGroupCD( pSkillTpl->mCDGroup[i]);    
                if(rGroupCD.GetCDTime() == 0 )
                {
                    continue;
                }
                tpPro->OnGroupCDRefresh( rGroupCD, tpPlayer);
            }

        }
    }
}



// �õ���ɫ��ʵ��ȼ�
int CEntityCharacter::GetLevel()
{
	if ( this->IsPlayer() )
	{
		CEntityPlayer* pPlayer = static_cast< CEntityPlayer* >( this );
		return pPlayer->GetLevel();
	}
	else if( this->IsNpc() )
	{
		CEntityNpc* pNpc = static_cast< CEntityNpc* >( this );
		return pNpc->GetLevel();
	}
	return 0;
}

int CEntityPlayer::BourseLogSend( )
{
	if( mBourseLogIsNeedLoad == false )
	{
		CMessageBourseTradeLog tLog;
		CMessage tMsg;

		tLog.mutable_sell_log( )->CopyFrom( mBourseSellLog );	
		tLog.mutable_buy_log( )->CopyFrom( mBourseBuyLog );

		tMsg.mutable_msghead()->set_messageid( ID_S2C_BOURSE_TRADE_LOG );	
		tMsg.set_msgpara( (uint32)&tLog );

		CSceneLogic::GetSingletonPtr( )->Send2Player( this, &tMsg );

	}
	return SUCCESS;
}

int CEntityPlayer::SetBourseLog( const PBBourseDetailList& vpBuyList, const PBBourseDetailList& vpSellList )
{
	mBourseBuyLog.CopyFrom( vpBuyList );
	mBourseSellLog.CopyFrom( vpSellList );
	SetBourseLogIsNeedLoad( false );
	return SUCCESS;
}




bool CEntityGhost::Setup(unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator *pCreator , CWTPoint* pPos, bool bInit, int vNpcID )
{
	if ( pCreator->GetCreatorType( ) != ENTITYTYPE_GHOST )
	{
		return false;
	}
	CGhostCreator* tpGhostCreator = (CGhostCreator*) pCreator;
	
	mEntityID = get_id( );
	mNpcID = tpGhostCreator->mNpcID;
	mLineID = usLineID;
	mMapID = usMapID;
	mIndex = usMapIndex;
	mPos = tpGhostCreator->mPos;
	mDirection = tpGhostCreator->mDirection;
	mAliveState = ALIVE_NORMAL;
	mCreatorID= tpGhostCreator->get_id();

	GetProperty()->SetEntityID( this->get_id( ) );
	GetProperty()->SetPropertyTempID( mNpcID );
	
	return true;
}

