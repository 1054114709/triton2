#include "command.h"
#include "entity.h"
#include "scenelogic.h"

// ֪ͨ��Ҹ�����Ϣ�ı䵽����
int CCommandSendPlayerDirtyDataToGate::Do()
{
	CEntityPlayer* pPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( mPlayerID );
	LK_ASSERT( pPlayer != NULL, return -1 );

	// ֻ������м��壬���ţ���Ӳ���Ҫ֪ͨ����
	if( pPlayer->GetTeamID() == 0 && pPlayer->GetFamilyID() == 0 )
	{
		//return 0;
	}


	CMessage tMessage;
	CMessageRoleGameInfoReportToGateNotify tNotifyPara;

	tMessage.mutable_msghead()->set_messageid( ID_S2G_NOTIFY_ROLEGAMEINFO2GATE );
	tMessage.set_msgpara( uint32(&tNotifyPara) );
	tNotifyPara.set_charid( pPlayer->GetCharID() );
	
	CPropertyPlayer *tpProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	// �ȼ��ı䣬Ҫ֪ͨǰ��
	if( mDirtyDataBit & DIRTYDATA_LEVEL )
	{
		tNotifyPara.set_level( pPlayer->GetLevel() );	
		// ֻ�м�������֪ͨ
		CTemplateMatrixTable *tpTable = (CTemplateMatrixTable*)CDataStatic::GetTemp( TEMP_MATRIXTABLE );
		if ( tpTable != NULL && ( pPlayer->GetLevel() <= tpTable->mFormalLevel || pPlayer->GetLevel() == tpTable->mEducatedLevel ) )
		{
			for ( int i = 0; i < MAX_MASTER_NUM; i++ )
			{
				if ( tpProperty->GetMasterID( i ) != 0 )
					tNotifyPara.add_masterid( tpProperty->GetMasterID( i ) );
			}
		}
	}
	if( mDirtyDataBit & DIRTYDATA_METIER )
		tNotifyPara.set_metier( pPlayer->GetMetier() );
	if( mDirtyDataBit & DIRTYDATA_MAPID )
	{
		tNotifyPara.set_lineid( pPlayer->GetLineID() );
		tNotifyPara.set_mapid( pPlayer->GetMapID() );
	}
	if( mDirtyDataBit & DIRTYDATA_RED )
	{
		tNotifyPara.set_pkvalue( tpProperty->GetPKValue() );
	}
	
	return CSceneLogic::GetSingletonPtr()->Send2Gate( &tMessage );
}


int CCommandSendPlayerDirtyDataToGate::OnEventTrigger( CEvent* pEvent )
{
	switch( pEvent->GetType() )
	{
	case OB_EVENT_LEVELUP:
		{
			mDirtyDataBit |= DIRTYDATA_LEVEL;
			break;
		}
	default:
		{
			break;
		}
	}

	Do();

	return 0;
}


int CCommandSendPlayerDirtyDataToGate::OnEventTrigger( int nBitFlag )
{
	mDirtyDataBit |= nBitFlag;
	Do();
	mDirtyDataBit |= ~nBitFlag; // clear bit set
	return 0;
}