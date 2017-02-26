#include "stdafx.hpp"
#include "entity.h"
#include "sceneobj_define.h"
#include "sceneobj_manager.h"
#include "sceneobj_manager_imp.h"
#include "stallmodule.h"
#include "stallmessage_pb.hxx.pb.h"
#include "promessage_pb.hxx.pb.h"
#include "mapmodule.h"
#include "propertymodule.h"
#include "logservertype.h"
#include "message_maker.h"
#include "worldmodule.h"

char CStallModule::sModuleName[ NAME_LENGTH ] = "Stall";
template<> CStallModule* CSingleton<CStallModule>::spSingleton = NULL;

// ����������
void CStallModule::OnLaunchServer( )
{
	STALL_LOG* tpLog = CSceneCfgManager::GetSingletonPtr()->GetStall_log();
	INIT_ROLLINGFILE_LOG( tpLog->mIdentifier, tpLog->mDirectory, (LogLevel)tpLog->mPriority, tpLog->mMaxfilesize, tpLog->mMaxbackupindex );
}

unsigned int CStallModule::CountSize()
{
	return sizeof( CStallModule );
}

// �˳�������
void CStallModule::OnExitServer( )
{
	
}

// ������Timer
void CStallModule::OnTimer( unsigned int vTickCount, unsigned int vTickOffset )
{
	
}

// ��������
int CStallModule::OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName )
{
	return SUCCESS;
}

// ·����Ϣ
void CStallModule::OnRouterMessage( CMessage* pMessage )
{
}

// �ͻ��˷�����Ϣ
void CStallModule::OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	if ( pPlayer == NULL || pMessage == NULL )
	{
		LOG_DEBUG( "stall", "client message invalid." );
		return ;
	}
	CMessageHead* tpHead = pMessage->mutable_msghead();
	switch( tpHead->messageid() )
	{
	case ID_C2S_REQUEST_OPENSTALL:
		{
			OnMessageOpenStall( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_UPDATEGOODS:
		{
			OnMessageUpdateGoods( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_UPDATEPRICE:
		{
			OnMessageUpdatePrice( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_UPDATETEXT:
		{
			OnMessageUpdateText( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_CLICKSTALL:
		{
			OnMessageClickStall( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_BUYGOODS:
		{
			OnMessageBuyGoods( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_CLOSESTALL:
		{
			OnMessageCloseStall( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_STALLRECORD:
		{
			OnMessageGetStallRecord( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_CLEANRECORD:
		{
			OnMessageClearStallRecord( pPlayer, pMessage );
			break;
		}
	default:
		break;
	}
	return ;
}


void CStallModule::OnCreateEntity( CEntity* pEntity, CCreator* pCreator,bool vFirst )
{
	
}

// ����ʵ��
void CStallModule::OnDestroyEntity( CEntity* pEntity, int vCode )
{
	if ( pEntity == NULL || pEntity->IsPlayer() == false )
	{
		return ;
	}

	CEntityPlayer* tpPlayer = ( CEntityPlayer* ) pEntity;
	if ( tpPlayer->HasStall() == false )
	{
		return ;
	}

	// simulate close stall message
	CMessage tMessage;
	CMessageCloseStallRequest tPara;
	tMessage.mutable_msghead()->set_messageid( ID_C2S_REQUEST_CLOSESTALL );
	tMessage.set_msgpara( (long) &tPara );
	OnMessageCloseStall( tpPlayer, &tMessage );
	return ;
}

//***********************************
// FunctionName : OnSaveData 
// Description  : 
// Input Params : 
// Output Params: 
// Return Types : 
// Modified Time: [2/25/2009]
//***********************************

bool CStallModule::OnSaveData( CEntityPlayer *pPlayer, int vSaveCode )
{
	return true;
}

//***************************************
// Function Name : OnMessageOpenStall
// Description 	 : ��ʼ��̯
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 1/13/2009
//***************************************

void CStallModule::OnMessageOpenStall(CEntityPlayer *pPlayer, CMessage *pMessage)
{
	CMessageOpenStallRequest* tpRequest = ( CMessageOpenStallRequest* ) pMessage->msgpara();
	LK_ASSERT( tpRequest != NULL, return );
	
	// ����Ƿ������뱣��
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	int tPwdCheckRet = tpProperty->GetRolePassword()->CheckActionAllowed( EM_PASSWORD_ACTION_GAMEACTION );
	if ( tPwdCheckRet != SUCCESS )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, tPwdCheckRet );
		return;
	}	

	if ( pPlayer->HasStall() == true )
	{
		SendOpenStallError( pPlayer, ERROR_STALL_HASSTALL );
		return ;
	}

	if ( pPlayer->GetLevel() < tpCfg->mLevellimit )
	{
		SendOpenStallError( pPlayer, ERROR_STALL_LEVELLESS );
		return ;
	}
	
	if ( CMapModule::GetSingleton().IsStallSafeArea( pPlayer->GetLineID(), pPlayer->GetMapID(), 
		pPlayer->GetMapIndex(), pPlayer->GetPosX(), pPlayer->GetPosY() ) == false )
	{
		SendOpenStallError( pPlayer, ERROR_STALL_NOTSAFTYAREAR );
		return ;
	}

	CWTPoint tPos = pPlayer->GetPos( );
	if ( CMapModule::GetSingleton().HasInStall( pPlayer->GetLineID(), pPlayer->GetMapID(), 
		pPlayer->GetMapIndex(), tPos ) == true )
	{
		SendOpenStallError( pPlayer, ERROR_STALL_HASOTHERSTALL );
		return ;
	}	

	// ��������ʱ��������������̯
	if ( pPlayer->GetNationality() != pPlayer->GetLineID() && !IS_NEUTRAL_LINE_ID( pPlayer->GetLineID() ) )
	{
		SendOpenStallError( pPlayer, ERROR_STALL_DIFFNATION );
		return ;
	}

	if ( tpProperty->GetHorseState() != LK_ZERO )
	{
		SendOpenStallError( pPlayer, ERROR_STALL_INHORSE );
		return ;
	}

	int tStallType = tpRequest->stalltype();
	if (( tStallType!=EM_STALL_TYPE_ALL ) && (tStallType!=EM_STALL_TYPE_MONEY) && (tStallType!=EM_STALL_TYPE_YB))
	{
		LOG_ERROR("stall", "STALL TYPE %d ERROR.", tStallType);
		SendOpenStallError(pPlayer, ERROR_STALL_ERRORSTALLTYPE);
		return;

	}
	if ((tpCfg->mStallflag == 0) && (tStallType != EM_STALL_TYPE_MONEY))
	{
		LOG_ERROR("stall", "STALL TYPE %d ERROR.NOT allowed. stall_cfg-StallFlag = %d", tStallType, tpCfg->mStallflag);
		SendOpenStallError(pPlayer, ERROR_STALL_ERRORSTALLTYPE);//��ʱʹ�ô���ʾ
		return;
	}

	CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().CreateObject( OBJTYPE_STALL );
	if ( tpStall == NULL )
	{
		LOG_DEBUG( "stall", "CreateStall() failed. [%s : %d]", __LK_FILE__, __LINE__ );
		return ;
	}
	


	tpStall->InitStall( pPlayer->GetEntityID(), tStallType);
	tpStall->UpdateStallName( tpRequest->stallname().c_str() );
	tpStall->UpdateAdContent( tpRequest->adcontent().c_str() );
	// set stall state in entity body
	pPlayer->SetStallID( tpStall->get_id() );

	CMessage tMessage;
	CMessageStartStallNotify tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_STARTSTALL );
	tPara.set_entityid( pPlayer->GetEntityID() );
	
	if ( GetStallData( pPlayer, &tPara ) != LK_ISUCCESS )
	{
		SendOpenStallError( pPlayer, ERROR_STALL_BINDITEM );
		return ;
	}

	tpProperty->SetServiceStatus(SERVICE_STALL);
	
	tPara.set_stallname( tpStall->GetStallName() );
	tPara.set_adcontent( tpStall->GetAdContent() );
	tPara.set_stalltype(tStallType);
	tMessage.set_msgpara( (long) &tPara );
	CMapModule::GetSingleton().MessageBroadCast( pPlayer, &tMessage, false, true );
	return ;
}

//***************************************
// Function Name : OnMessageUpdateGoods
// Description 	 :
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 1/13/2009
//***************************************

void CStallModule::OnMessageUpdateGoods(CEntityPlayer *pPlayer, CMessage *pMessage)
{
	CMessageUpdateStallRequest* tpRequest = ( CMessageUpdateStallRequest* ) pMessage->msgpara();
	LK_ASSERT( tpRequest != NULL, return );
	
	if ( pPlayer->HasStall() == false )
	{
		SendErrorNotice( pPlayer, ERROR_STALL_NOTEXIST );
		return ;
	}

	CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( pPlayer->GetStallID() );
	if ( tpStall == NULL )
	{
		LOG_DEBUG( "stall", "GetStall() failed. EntityID = %d.[%s : %d]", pPlayer->GetEntityID(), __LK_FILE__, __LINE__ );
		return ;
	}

	CMessage tMessage;
	CMessageUpdateStallResponse tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_UPDATEGOODS );
	if ( tpRequest->type() == STALL_PUSH )
	{		
		tPara.set_type( STALL_PUSH );
		tPara.set_stallindex( tpRequest->stallindex() );
		tPara.set_price( tpRequest->price() );
		tPara.set_pricetype(tpRequest->pricetype());
		PBItemObject* tpItem = tPara.mutable_item();

		int tRes = CPropertyModule::GetSingleton().GetItemBinary( pPlayer->GetEntityID(), tpRequest->itemindex(), tpRequest->itemnum(), tpItem, tRes, true );		
		if ( tRes != LK_ISUCCESS )
		{
			return ;
		}

		CTplItem* tpTplItem = ( CTplItem* )CDataStatic::SearchTpl( tpItem->itemid() );
		if ( tpTplItem == NULL )
		{
			LOG_ERROR( "stall", "Item Template not find.[%s : %d]", __LK_FILE__, __LINE__ );
			return ;
		}

		unsigned int tPriceLimit = 0;
		if ( tpTplItem->mPileLimit > LK_ONE )
		{
			// �ɶѵ���
			tPriceLimit = tpCfg->mMaxprice;
		}
		else
		{
			// ���ɶѵ�
			tPriceLimit = tpCfg->mMaxprice * 100;
		}


		if (((tpStall->GetStallType() == EM_STALL_TYPE_YB) && (tpRequest->pricetype() != CYuanBao::em_golden_yuanbao)) ||
			((tpStall->GetStallType() == EM_STALL_TYPE_MONEY) && (tpRequest->pricetype() != CYuanBao::em_unbind_money)))
		{
			SendErrorNotice( pPlayer, ERROR_STALL_PRICEERROR );
			return ;
		}

		// check price scope Ԫ�������������Ϊ�ǰ���1/100
		if (((tpRequest->pricetype() == CYuanBao::em_unbind_money ) &&( tpRequest->price() > tPriceLimit || tpRequest->price() < LK_ZERO ))
			|| (( tpRequest->pricetype() == CYuanBao::em_golden_yuanbao ) &&( tpRequest->price() > tPriceLimit/100 || tpRequest->price() < tpCfg->mMinybprice )))
		{
			SendErrorNotice( pPlayer, ERROR_STALL_PRICEERROR );
			return ;
		}
		

		if ( tpStall->InsertGoods( tpItem->itemid(), tpRequest->itemnum(), tpRequest->price(), tpRequest->stallindex(),
			tpRequest->itemindex(),tpRequest->pricetype()) != LK_ISUCCESS )
		{
			SendErrorNotice( pPlayer, ERROR_STALL_PUSHUPFAILED );
			return ;
		}
		tpStall->LockGoods( tpRequest->itemindex() );
	}
	else
	{
		tPara.set_type( STALL_DOWN );
		tPara.set_stallindex( tpRequest->stallindex() );
		
		unsigned int tItemIndex = 0, tPrice = 0, tNum = 0, tItemID = 0, tPriceType;
		tpStall->GetGoodsIndex( tpRequest->stallindex(), tItemIndex, tNum, tPrice, tItemID, tPriceType );
		if ( tpStall->RemoveGoods( tItemIndex, tpRequest->stallindex(), tNum ) != LK_ISUCCESS )
		{
			return ;
		}
		tpStall->UnLockGoods( tItemIndex );
	}
	tPara.set_entityid( pPlayer->GetEntityID() );
	tMessage.set_msgpara( (long) &tPara );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMessage );
	return ;
}

//***************************************
// Function Name : OnMessageUpdatePrice
// Description 	 :
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 1/13/2009
//***************************************

void CStallModule::OnMessageUpdatePrice(CEntityPlayer *pPlayer, CMessage *pMessage)
{
	CMessageUpdatePriceRequest* tpRequest = ( CMessageUpdatePriceRequest* ) pMessage->msgpara();
	LK_ASSERT( tpRequest != NULL, return );

	if ( pPlayer->HasStall() == false )
	{
		SendErrorNotice( pPlayer, ERROR_STALL_NOTEXIST );
		return ;
	}
	
	CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( pPlayer->GetStallID() );
	if ( tpStall == NULL )
	{
		LOG_DEBUG( "stall", "GetStall() failed.[%s : %d]", __LK_FILE__, __LINE__ );
		return ;
	}

	unsigned int tItemID = 0, tItemIndex = 0, tPrice = 0, tItemNum = 0, tPriceType = 0;
	if ( tpStall->GetGoodsIndex( tpRequest->stallindex(), tItemIndex, tItemNum, tPrice, tItemID, tPriceType ) != LK_ISUCCESS )
	{
		LOG_ERROR( "stall", "GetGoodsIndex() failed.StallIndex: %d", tpRequest->stallindex() );
		return ;
	}

	CTplItem* tpTplItem = ( CTplItem* ) CDataStatic::SearchTpl( tItemID );
	if ( tpTplItem == NULL )
	{
		LOG_ERROR( "stall", "Item Template not find.TempID:%d", tItemID );
		return ;
	}

	unsigned int tPriceLimit = 0;
	if ( tpTplItem->mPileLimit > LK_ONE )
	{
		// �ɶѵ���
		tPriceLimit = tpCfg->mMaxprice;
	}
	else
	{
		// ���ɶѵ�
		tPriceLimit = tpCfg->mMaxprice * 100;
	}


	if (((tpStall->GetStallType() == EM_STALL_TYPE_YB) && (tpRequest->pricetype() != CYuanBao::em_golden_yuanbao)) ||
		((tpStall->GetStallType() == EM_STALL_TYPE_MONEY) && (tpRequest->pricetype() != CYuanBao::em_unbind_money)))
	{
		SendErrorNotice( pPlayer, ERROR_STALL_PRICEERROR );
		return ;
	}

	// check price scope Ԫ�������������Ϊ�ǰ���1/100
	if (((tpRequest->pricetype() == CYuanBao::em_unbind_money ) &&( tpRequest->price() > tPriceLimit || tpRequest->price() < LK_ZERO ))
		|| (( tpRequest->pricetype() == CYuanBao::em_golden_yuanbao ) &&( tpRequest->price() > tPriceLimit/100 || tpRequest->price() < tpCfg->mMinybprice )))
	{
		SendErrorNotice( pPlayer, ERROR_STALL_PRICEERROR );
		return ;
	}



	if ( tpStall->UpdatePrice( tpRequest->stallindex(), tpRequest->price() , tpRequest->pricetype()) != LK_ISUCCESS )
	{
		SendErrorNotice( pPlayer, ERROR_STALL_PRICEFAILED );
		return ;
	}

	CMessage tMessage;
	CMessageUpdatePriceResponse tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_UPDATEPRICE );
	tPara.set_stallindex( tpRequest->stallindex() );
	tPara.set_price( tpRequest->price() );
	tPara.set_entityid( pPlayer->GetEntityID() );
	tPara.set_pricetype(tpRequest->pricetype());
	tMessage.set_msgpara( (long) &tPara );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMessage );
	return ;
}

//***************************************
// Function Name : OnMessageClickStall
// Description 	 :
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 1/13/2009
//***************************************

void CStallModule::OnMessageClickStall(CEntityPlayer *pPlayer, CMessage *pMessage)
{
	CMessageClickStallRequest* tpRequest = ( CMessageClickStallRequest* ) pMessage->msgpara();
	LK_ASSERT( tpRequest != NULL, return );

	CEntityPlayer* tpMaster = dynamic_cast< CEntityPlayer* >( CSceneLogic::GetSingleton().GetEntity( tpRequest->entityid() ) );
	LK_ASSERT( tpMaster != NULL, return );

	// check nationality
	if ( ( pPlayer->GetNationality() != tpMaster->GetNationality() ) && !IS_NEUTRAL_LINE_ID(tpMaster->GetLineID()) )
	{
		SendErrorNotice( pPlayer, ERROR_STALL_NOTLOOKENEMY );
		return ;
	}

	if ( tpMaster->HasStall() == false )
	{
		return ;
	}

	CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( tpMaster->GetStallID() );
	if ( tpStall == NULL )
	{
		LOG_DEBUG( "stall", "GetStall() failed. [%s : %d]", __LK_FILE__, __LINE__ );
		return ;
	}

	CMessage tMessage;
	CMessageClickStallResponse tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_CLICKSTALL );
	if ( tpStall->GetStallInfo( &tPara ) != LK_ISUCCESS )
	{
		SendErrorNotice( pPlayer, ERROR_STALL_CLICKSTALLFAILED );
		return ;
	}
	tPara.set_entityid( tpMaster->GetEntityID() );
	tMessage.set_msgpara( (long) &tPara );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMessage );
	return ;
}

//***************************************
// Function Name : OnMessageBuyGoods
// Description 	 :
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 1/14/2009
//***************************************

void CStallModule::OnMessageBuyGoods(CEntityPlayer *pPlayer, CMessage *pMessage)
{
	CMessageBuyGoodsRequest* tpRequest = ( CMessageBuyGoodsRequest* ) pMessage->msgpara();
	LK_ASSERT( tpRequest != NULL, return );		  	
	LK_ASSERT( pPlayer != NULL, return )
	
	// ����Ƿ������뱣��
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	int tPwdCheckRet = tpProperty->GetRolePassword()->CheckActionAllowed( EM_PASSWORD_ACTION_GAMEACTION );
	if ( tPwdCheckRet != SUCCESS )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, tPwdCheckRet );
		return;
	}	

	CEntityPlayer* tpMaster = dynamic_cast<CEntityPlayer*>(CSceneObjManager::GetSingletonPtr( )->GetObject( tpRequest->entityid() ));
	LK_ASSERT( tpMaster != NULL, return );

	if ( tpMaster->HasStall() == false  )
	{
		return ;
	}

	CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( tpMaster->GetStallID() );
	if ( tpStall == NULL )
	{
		LOG_ERROR( "stall", "[%s : %d] Player  %d GetStall() failed.", __LK_FILE__, __LINE__, tpMaster->GetCharID() );
		return ;
	}

	unsigned int tItemIndex = 0, tItemNum = 0, tPrice = 0, tItemID = 0, tPriceType = 0;
	int tRet = tpStall->GetGoodsIndex( tpRequest->stallindex(), tItemIndex, tItemNum, tPrice, tItemID, tPriceType );
	
	// ��������ϵ���Ʒ�Ƿ��ǰ�̯ʱ�ŵ���Ʒ
	bool bLastCheck = CPropertyModule::GetSingletonPtr()->HasItemOnIndex( tpMaster->GetEntityID(), tItemIndex, tItemID, tItemNum );
	if( bLastCheck != true )
	{
		LOG_ERROR( "stall", "[%s : %d] player %d index %d has changed", __LK_FILE__, __LINE__, tpMaster->GetCharID(), tItemIndex );
		SendErrorNotice( pPlayer, ERROR_STALL_GOODSCHANGED );
		return ;
	}

	// ���̯λ�����ϵ���Ʒ�Ƿ��ڽ�����
	if( tpStall->GetGoodsStatus( tpRequest->stallindex() ) == GOODS::EGOODS_STATUS_TRADING )
	{
		SendErrorNotice( pPlayer, ERROR_STALL_BUYGOODSFAILED );
		return ;
	}

	// check if goods is real
	if ( tRet != LK_ISUCCESS || tItemID != tpRequest->itemid() )
	{
		SendErrorNotice( pPlayer, ERROR_STALL_GOODSCHANGED );
		return ;
	}

	if (( tPrice != tpRequest->price() ) || (tPriceType != tpRequest->pricetype()))
	{
		SendErrorNotice( pPlayer, ERROR_STALL_PRICECHANGED );
		return ;
	}

	if ( tpRequest->number() > tItemNum || tpRequest->number() <= LK_ZERO )
	{
		SendErrorNotice( pPlayer, ERROR_STALL_NUMBEROVER );
		return ;
	}

	//----------------------------------------------------

	// �ڶ�����д�����̯�м�������˳��߼�ǰ�ǵ�Ҫ�������
	CStallRecord* tpStallRecord = (CStallRecord*)CSceneObjManager::GetSingletonPtr()->CreateObject( OBJTYPE_STALL_RECORD );
	LK_ASSERT( tpStallRecord != NULL, return );

	tpStallRecord->mBuyerName = lk::string<NAME_LENGTH>( pPlayer->GetCharName() );
	tpStallRecord->mItemID = tItemID; 
	tpStallRecord->mPrice = tPrice; 
	tpStallRecord->mNumber = tpRequest->number();
	tpStallRecord->mTimeStamp = (int) time( NULL );
	tpStallRecord->mAction = 0;
	tpStallRecord->mTax = 0;
	tpStallRecord->mItemIndex = tItemIndex;
	tpStallRecord->mPriceType = tPriceType;
	tpStallRecord->mFee = 0;
	tpStallRecord->mStallIndex = tpRequest->stallindex();
	
	// --------------------------------------------------------

	//�ǰ����
	unsigned int tTradeMoney = 0;
	unsigned int tTradeYB = 0;
	unsigned int tTaxMoney = 0;
	if ((tpStall->GetStallType() != EM_STALL_TYPE_YB) && (tPriceType == CYuanBao::em_unbind_money))
	{
		// check buyer's money
		unsigned int tSrcMoney = CPropertyModule::GetSingleton().GetPlayerMoney( pPlayer->GetEntityID() );
		tTradeMoney = tPrice * tpRequest->number();
		if ( tTradeMoney > tSrcMoney )
		{
			SendErrorNotice( pPlayer, ERROR_STALL_SRCMONEYLESS );
			CSceneObjManager::GetSingletonPtr()->DestroyObject( tpStallRecord->get_id() );
			return ;
		}


		// ��������̯Ҫ��˰
		if ( IS_NEUTRAL_LINE_ID( pPlayer->GetLineID() ) == true )
		{
			CTemplateWorldBattleConfig *tpConfig = (CTemplateWorldBattleConfig*)CDataStatic::GetTemp( TEMP_BATTLECONFIG );
			if ( tpConfig != NULL )
			{
				int tRate = 0;
				int tOrder = CWorldModule::GetSingleton().mRateOrder;
				if ( tOrder >= 0 &&  (unsigned int)(tOrder) < ARRAY_CNT(tpConfig->mTax) )
				{
					tRate = tpConfig->mTax[ tOrder ].mTaxRate;
				}
				// ��ʤ����˰
				if ( tpMaster->GetNationality() == CWorldModule::GetSingleton().mWinWorld && tpConfig->mWinTax != 0 )
				{
					tRate = tRate * tpConfig->mWinTax / SERVER_PERCENT_FLOAT;
				}
				tTaxMoney = tTradeMoney * ( tRate / SERVER_PERCENT_FLOAT );
			}
		}	

		// check master money
		CTemplateLevelMoneyLmt* tpMoneyTable = (CTemplateLevelMoneyLmt*)CDataStatic::GetTemp(TEMP_MONEYLMT_CFG);
		LK_ASSERT( tpMoneyTable!=NULL, return );
		LK_ASSERT( tpMaster->GetLevel() >= 0 && tpMaster->GetLevel() < TMP_MAX_GRADE, return );
		unsigned int tMoney = tTradeMoney + ( CPropertyModule::GetSingleton().GetPlayerMoney( tpMaster->GetEntityID() ) );
		if ( tMoney > MONEY_LIMIT  || 
			tMoney > tpMoneyTable->mLmtTable[tpMaster->GetLevel()].mBagMoneyLmt )
		{
			// simulate put down item message
			CMessage tMsgDown;
			CMessageUpdateStallRequest tParaDown;
			tMsgDown.mutable_msghead()->set_messageid( ID_C2S_REQUEST_UPDATEGOODS );
			tParaDown.set_stallindex( tpRequest->stallindex() );
			tParaDown.set_type( STALL_DOWN );
			tMsgDown.set_msgpara( (long) &tParaDown );
			OnMessageUpdateGoods( tpMaster, &tMsgDown );
			SendErrorNotice( pPlayer, ERROR_STALL_MASTERMONEYOUT );
			

			tpStallRecord->mAction = 1;
			// ��¼̯λ��Ϣ
			CPropertyModule::GetSingleton().OnEventSaveStallRecord( tpMaster, tpStallRecord,  tpStall->GetStallType());
			CSceneObjManager::GetSingletonPtr()->DestroyObject( tpStallRecord->get_id() );
			return ;
		}

	}

	int tFee = 0;
	if ((tpStall->GetStallType() != EM_STALL_TYPE_MONEY) && (tPriceType == CYuanBao::em_golden_yuanbao))
	{
		//������Ԫ��
		CYuanBao& tBuyerYB = tpProperty->GoldenYB();
		tTradeYB = tPrice * tpRequest->number();
		if ( (int)(tTradeYB) > tBuyerYB.remain() )
		{
			SendErrorNotice( pPlayer, ERROR_PLAYER_HASNO_ENOUGHYB );
			CSceneObjManager::GetSingletonPtr()->DestroyObject( tpStallRecord->get_id() );
			return ;
		}


		//�������Ԫ��
		CYuanBao& tMasterYB = tpMaster->GetGolden();
		if (tTradeYB + tMasterYB.remain() > 100000000)//CYuanBao::em_max_yaunbao_amount)
		{
			CMessage tMsgDown;
			CMessageUpdateStallRequest tParaDown;
			tMsgDown.mutable_msghead()->set_messageid( ID_C2S_REQUEST_UPDATEGOODS );
			tParaDown.set_stallindex( tpRequest->stallindex() );
			tParaDown.set_type( STALL_DOWN );
			tMsgDown.set_msgpara( (long) &tParaDown );
			OnMessageUpdateGoods( tpMaster, &tMsgDown );
			SendErrorNotice( pPlayer, ERROR_STALL_MASTERMONEYOUT );

			tpStallRecord->mAction = 1;
			// ��¼̯λ��Ϣ
			CPropertyModule::GetSingleton().OnEventSaveStallRecord( tpMaster, tpStallRecord ,tpStall->GetStallType());
			CSceneObjManager::GetSingletonPtr()->DestroyObject( tpStallRecord->get_id() );
			return ;
		}

		//����������

		tFee = tTradeYB * tpCfg->mFeerate/1000;//ȡ����
		if (tFee < 1)
		{
			tFee = 1;
		}
	}
	tpStallRecord->mFee = tFee;

	// to trade the goods
	short tSrcList[ 2 ] = { 0 };
	short tDesList[ 2 ] = { tItemIndex, tpRequest->number() };
	// ����Ƿ������뱣��
	CPropertyPlayer *tpMasterProperty = ( CPropertyPlayer * )tpMaster->GetProperty();
	CItemObject * tpExchItem = tpMasterProperty->GetBaggage( )->GetItemObjPtr( tItemIndex );
	uint64 ullExchItemGUID = 0;
	if (tpExchItem != NULL)
	{
		ullExchItemGUID = tpExchItem->GetGUID();
	}
	tpStallRecord->mItemGuid = ullExchItemGUID;
	
	int tReturn = CPropertyModule::GetSingletonPtr( )->CheckChange( tpMaster, pPlayer, 1, 0, 0, tTradeMoney );

	if( tReturn != EXCHAGE_SUCCESS )
	{
		if( tReturn == EXCHAGE_MYMONEYOVERFLOW )
		{
			CPropertyModule::GetSingletonPtr()->SendProErrorNotice( pPlayer, ERROR_STALL_MASTERMONEYOUT );
		}
		else if( tReturn == EXCHAGE_DESMONEYOVERFLOW  )
		{
			CPropertyModule::GetSingletonPtr()->SendProErrorNotice( pPlayer, ERR_BAG_MONEY_UPLMT );;
		}

		LOG_ERROR( "stall", "[ %s : %d ][ %s ] Stall Trade Error, Index %d Num %d, Player( %s : %d: %d ), "
			"Master( %s : %d : %d ) CheckChange %d", __LK_FILE__, __LINE__,	__FUNCTION__, tItemIndex, 
			tpRequest->number(), pPlayer->GetCharNameShow( ), pPlayer->GetCharID( ), pPlayer->GetEntityID( ),
			tpMaster->GetCharNameShow( ), tpMaster->GetCharID( ), tpMaster->GetEntityID( ), tReturn );
		CSceneObjManager::GetSingletonPtr()->DestroyObject( tpStallRecord->get_id() );
		return;
	}

	//��¼������־	
	pPlayer->SetExchange(true);
	tpMaster->SetExchange(true);
	if(tPriceType == CYuanBao::em_golden_yuanbao)
	{
		//1.�ۼ�����ڴ��еĽ�Ǯ
		CYuanBao& tBuyerYB = tpProperty->GoldenYB();
		tBuyerYB.lock(tTradeYB);
		////2.������Ʒ
		//if (( CPropertyModule::GetSingleton().ExchangeBaggage( pPlayer, tpMaster, 0, tSrcList, 1, tDesList, tTradeMoney, 0, em_exchange_by_stall_yb)) != EXCHAGE_SUCCESS )
		//{
		//	pPlayer->SetExchange(false);
		//	tpMaster->SetExchange(false);
		//	tBuyerYB.rollback(tTradeYB);
		//	SendErrorNotice( pPlayer, ERROR_STALL_BUYGOODSFAILED );
		//	return ;
		//}
		////3.���ݿ��н��׽�Ǯ���������ѣ�ע�⣬Ŀǰ��Ϊ�����ݿ��н��׽�Ǯ�ض��ɹ�
		SendExchageRequest(pPlayer, tpMaster, tpStallRecord, tpCfg->mFeeibid);
		// ���ﲻ��������Դ����session���ػ��߳�ʱ��ʱ��Ḻ�������ա�	

		// �������ҵ�̯λ��Ʒ����ֹ��Ϊ����ظ����򣬶������ɿ۶��Ԫ����ֻ�õ�һ����Ʒ����ʧ.
		// ��Ʒ�ڹ���ɹ������߹���ʱ��ʱ�������
		// ���̯λ�����ϵ���Ʒ�Ƿ��ڽ�����
		tpStall->SetGoodsStatus( tpRequest->stallindex(), GOODS::EGOODS_STATUS_TRADING );

		return;

		////4.���������ڴ��Ǯ
		//tBuyerYB.commit(tTradeYB);
		//CYuanBao& tMasterYB = tpMaster->GetGolden();
		//tMasterYB.add(tTradeYB);
		//// ��¼��־�ۼ����Ԫ��
		//LogEventLostMoneyByStall((CEntityPlayer*) pPlayer, CYuanBao::em_golden_yuanbao, tTradeYB, 
		//	tpMaster->GetCharID(), tItemID, ullExchItemGUID);

		//// ��¼��־��������Ԫ��
		//LogEventGetMoneyByStall((CEntityPlayer*) tpMaster, CYuanBao::em_golden_yuanbao, tTradeYB, 
		//	pPlayer->GetCharID(), tItemID, ullExchItemGUID);

		//tMasterYB.lock(tFee);
		//tMasterYB.commit(tFee);

		//// ��¼��־��������
		//LogEventLostMoneyByFee((CEntityPlayer*) tpMaster, CYuanBao::em_golden_yuanbao, tFee, tTradeYB, tItemID, ullExchItemGUID);

		////�������ʧȥԪ����Ϣ
		//CPropertyModule::GetSingleton().SendUpdateYuanbaoNotice(pPlayer, -tTradeYB, tPriceType);
		////�������һ��Ԫ����Ϣ�����Ԫ���۳�������
		//CPropertyModule::GetSingleton().SendUpdateYuanbaoNotice(tpMaster, tTradeYB, tPriceType);
		//CPropertyModule::GetSingleton().SendUpdateYuanbaoNotice(tpMaster, -tFee, tPriceType);
	}
	else
	{
		// unlock item
		// check if you buy all item???
		if ( tpRequest->number() == tItemNum )
		{
			tpStall->UnLockGoods( tItemIndex );
		}

		if (( CPropertyModule::GetSingleton().ExchangeBaggage( pPlayer, tpMaster, 0, tSrcList, 1, tDesList, tTradeMoney, 0, em_exchange_by_stall)) != EXCHAGE_SUCCESS )
		{
			pPlayer->SetExchange(false);
			tpMaster->SetExchange(false);
			SendErrorNotice( pPlayer, ERROR_STALL_BUYGOODSFAILED );
			CSceneObjManager::GetSingletonPtr()->DestroyObject( tpStallRecord->get_id() );
			return ;
		}

	}

	pPlayer->SetExchange(false);
	tpMaster->SetExchange(false);

	tpStallRecord->mTax = tTaxMoney;
	//��˰
	if ( tPriceType == CYuanBao::em_unbind_money && tTaxMoney > 0 && CPropertyModule::GetSingleton().PlayerChangeMoney( tpMaster, tTaxMoney, true, false ) == SUCCESS )
	{
		LogEventLostMoneyByTax( tpMaster, CYuanBao::em_unbind_money, tTaxMoney, 0, tItemID, tpRequest->number() );
		CWorldModule::GetSingleton().SendAddTaxNotify( tTaxMoney );
		
	}
	
	// remove data form stall vector container
	tpStall->RemoveGoods( tItemIndex, tpRequest->stallindex(), tpRequest->number() );

	CMessage tMessage;
	CMessageBuyGoodsResponse tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_BUYGOODS );
	tPara.set_stallindex( tpRequest->stallindex() );
	tPara.set_entityid( tpMaster->GetEntityID() );
	tPara.set_number( tpRequest->number() );
	tPara.set_buyerentityid( pPlayer->GetEntityID() );
	tMessage.set_msgpara( (long) &tPara );

	std::vector<CEntityPlayer*> tPlayerVec;
	tPlayerVec.push_back( pPlayer );
	tPlayerVec.push_back( tpMaster ); 
	CSceneLogic::GetSingleton().Send2Player( &tPlayerVec, &tMessage );


	CPropertyModule::GetSingleton().OnEventSaveStallRecord( tpMaster, tpStallRecord, tpStall->GetStallType());

	PrintTradeLog( tpMaster->GetCharNameShow(), tpMaster->GetCharID(), pPlayer->GetCharNameShow(), pPlayer->GetCharID(), tItemID, tpRequest->number(), tPrice, tPriceType );

	CSceneObjManager::GetSingletonPtr()->DestroyObject( tpStallRecord->get_id() );
	return ;
}

//***************************************
// Function Name : OnMessageCloseStall
// Description 	 :
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 1/14/2009
//***************************************

void CStallModule::OnMessageCloseStall(CEntityPlayer *pPlayer, CMessage *pMessage)
{
	CMessageCloseStallRequest* tpRequest = ( CMessageCloseStallRequest* ) pMessage->msgpara();
	LK_ASSERT( tpRequest != NULL, return );

	if ( pPlayer->HasStall() == false )
	{
		SendErrorNotice( pPlayer, ERROR_STALL_NOTEXIST );
		return ;
	}
	
	CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( pPlayer->GetStallID() );
	if ( tpStall == NULL )
	{
		LOG_DEBUG( "stall", "GetStall() failed. [%s : %d]", __LK_FILE__, __LINE__ );
		return ;
	}

	// if save, saved data
	if ( (bool)( tpRequest->issaved())  == true  )
	{
		SaveStallData( pPlayer );
	}
	
	CMessage tMessage;
	CMessageCloseStallResponse tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_CLOSESTALL );
	tPara.set_entityid( pPlayer->GetEntityID() );
	tMessage.set_msgpara( (long) &tPara );
	CMapModule::GetSingleton().MessageBroadCast( pPlayer, &tMessage, false, true );
	
	tpStall->ReleaseGoods();
	CSceneObjManager::GetSingleton().DestroyObject( tpStall->get_id() );

	pPlayer->SetStallID( LK_ZERO );
	
	// remove stall service status
	CPropertyPlayer* tpProperty = ( CPropertyPlayer* )pPlayer->GetProperty();
	if ( tpProperty == NULL )
	{
		LOG_ERROR( "stall", "Deeply Error, CProperty can't find.[%s : %d]", __LK_FILE__, __LINE__ );
		return ;
	}
	tpProperty->SetServiceStatus( SERVICE_NONE );
	return ;
}

//***************************************
// Function Name : OnMessageUpdateText
// Description 	 :
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 1/14/2009
//***************************************

void CStallModule::OnMessageUpdateText(CEntityPlayer *pPlayer, CMessage *pMessage)
{
	CMessageUpdateTextRequest* tpRequest = ( CMessageUpdateTextRequest* ) pMessage->msgpara();
	LK_ASSERT( tpRequest != NULL, return );

	if ( pPlayer->HasStall() == false )
	{
		SendErrorNotice( pPlayer, ERROR_STALL_NOTEXIST );
		return ;
	}

	CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( pPlayer->GetStallID() );
	if ( tpStall == NULL )
	{
		LOG_DEBUG( "stall", "GetStall() failed. [%s : %d]", __LK_FILE__, __LINE__ );
		return ;
	}

	CMessage tMessage;
	CMessageUpdateTextResponse tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_UPDATETEXT );
	tPara.set_entityid( pPlayer->GetEntityID() );

	if ( tpRequest->type() == STALL_NAME )
	{ 
		if ( strlen( tpRequest->stallname().c_str() ) > tpCfg->mMaxnamelen )
		{
			SendErrorNotice( pPlayer, ERROR_STALL_NAMELONGER );
		}
		else
		{
			char tStr[ NAME_LENGTH ] = { 0 };
			strncpy( tStr, tpRequest->stallname().c_str(), sizeof( tStr ) - 1 );
			CDirtyWord::GetSingleton().OI_Dirty_Check( 1, tStr );
			tpStall->UpdateStallName( tStr );
		}
		tPara.set_stallname( tpStall->GetStallName() );
		tPara.set_type( STALL_NAME );
	}
	else if ( tpRequest->type() == STALL_ADCONTENT )
	{
		if ( strlen( tpRequest->adcontent().c_str() ) > tpCfg->mMaxadcontent )
		{
			SendErrorNotice( pPlayer, ERROR_STALL_ADLONGER );
		}
		else
		{
			char tStr[ 2 * NAME_LENGTH ] = { 0 };
			strncpy( tStr, tpRequest->adcontent().c_str(), sizeof( tStr ) - 1 );
			CDirtyWord::GetSingleton().OI_Dirty_Check( 1, tStr );
			tpStall->UpdateAdContent( tStr );
		}
		tPara.set_adcontent( tpStall->GetAdContent() );
		tPara.set_type( STALL_ADCONTENT );
	}
	tMessage.set_msgpara( (long) &tPara );
	CMapModule::GetSingleton().MessageBroadCast( pPlayer, &tMessage, false, true );
	return ;
}

//***************************************
// Function Name : TouchStallPedal
// Description 	 :
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 1/16/2009
//***************************************

void CStallModule::TouchStallPedal(CEntityPlayer* pPlayer, PBStallInfo* pStallInfo )
{
	LK_ASSERT( pPlayer != NULL, return );

	if ( pPlayer->HasStall() == false )
	{
		// false�Ͳ��������ˣ�Ĭ��Ҳ��0,��ʡ����
		//pStallInfo->set_hasflag( (int) false );
		return ;
	}

	CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( pPlayer->GetStallID() );
	if ( tpStall == NULL )
	{
		LOG_DEBUG( "stall", "GetStall() failed.[%s : %d]", __LK_FILE__, __LINE__ );
		return ;
	}

	// encapsulation the stall info data
	pStallInfo->set_hasflag( true);
	pStallInfo->set_stallname( tpStall->GetStallName() );
	pStallInfo->set_adcontent( tpStall->GetAdContent() );
	pStallInfo->set_stalltype(tpStall->GetStallType());
	return ;
}

//***************************************
// Function Name : SendErrorNotice
// Description 	 :
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 1/16/2009
//***************************************

void CStallModule::SendErrorNotice(CEntityPlayer* pPlayer, int vCode )
{
	LK_ASSERT( pPlayer != NULL, return );

	CMessage tMessage;
	CMessageProErrorNotice tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_PROERROR );
	tPara.set_errorcode( vCode );
	tMessage.set_msgpara( (long) &tPara );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMessage );
	return ;
}


// 
//***************************************
// Function Name : SendOpenStallError
// Description 	 : ���Ϳ�ʼ��̯ʱ�������Ϣ����̯��
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 1/16/2009
//***************************************
void CStallModule::SendOpenStallError( CEntityPlayer* pPlayer, int nErrCode )
{
	LK_ASSERT( pPlayer != NULL, return );

	CMessage tMessage;
	CMessageOpenStallResponse tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_OPENSTALL );
	tPara.set_entityid( pPlayer->GetEntityID() );
	tPara.set_errorcode( nErrCode );
	tMessage.set_msgpara( (long) &tPara );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMessage );
}


//***************************************
// Function Name : PrintTradeLog
// Description 	 :
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 2/10/2009
//***************************************

void CStallModule::PrintTradeLog(const char *pMaster,int nMasterID, const char *pBuyer, int nBuyerID, unsigned int vItemID, unsigned int vNumber, unsigned int vPrice, const int vPriceType)
{
	LOG_INFO( "stall", "entity[%s:%d] buy item from [%s:%d]: ID[%d] | Number[%d] | Price[%d] | PriceType[%d]", 
		pBuyer, nBuyerID, pMaster, nMasterID, vItemID, vNumber, vPrice, vPriceType );
	return ;
}

//***************************************
// Function Name : SaveStallData
// Description 	 :
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 2/19/2009
//***************************************

void CStallModule::SaveStallData(CEntityPlayer* pPlayer )
{
	LK_ASSERT( pPlayer != NULL, return );

	CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( pPlayer->GetStallID() );
	LK_ASSERT( tpStall != NULL, return );

	tpStall->SaveData( pPlayer );
	return ;
}

//***************************************
// Function Name : GetStallData
// Description 	 :
// Input Params  :
// Output Params :
// Return Type   :
// Modified Time : 2/19/2009
//***************************************

int CStallModule::GetStallData(CEntityPlayer *pPlayer, CMessageStartStallNotify* pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return LK_IERROR );

	char tName[ NAME_LENGTH ] = { 0 };
	char tAd[ NAME_LENGTH * 2 ] = { 0 };
	int tItemAry[ MAX_STALL_INDEX ] = { 0 };
	int tStallAry[ MAX_STALL_INDEX ] = { 0 };
	int tPriceAry[ MAX_STALL_INDEX ] = { 0 };
	int tPriceTypeAry[ MAX_STALL_INDEX ] = { 0 };

	CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( pPlayer->GetStallID() );
	LK_ASSERT( tpStall != NULL, return LK_IERROR );

	int tNum = CPropertyModule::GetSingleton().GetStallInfo( pPlayer, tpStall->GetStallType(), tName, tAd, tItemAry, tStallAry, tPriceAry, tPriceTypeAry );
	
	if ( tName[0] != '\0' )
		tpStall->UpdateStallName( tName );
	if ( tAd[0] != '\0' )
		tpStall->UpdateAdContent( tAd );

	if ( tNum == LK_ZERO )
	{
		return LK_ISUCCESS;
	}

	for ( int i = 0; i < tNum; i ++ )
	{
		int tRes = 0;
		
		PBItemObject* tpObj = pMessage->add_itemlist();
		if ( CPropertyModule::GetSingleton().GetItemBinary( pPlayer->GetEntityID(), tItemAry[ i ], -1, tpObj, tRes, true ) != LK_ISUCCESS )
		{
			return LK_IERROR;
		}
		pMessage->add_price( tPriceAry[ i ] );
		//pMessage->add_stallindex( tStallAry[ i ] );	
		pMessage->add_stallindex( i );	// ̯λ0��ʼ����
		pMessage->add_pricetype(tPriceTypeAry[i]);//��¼�۸�����

		tpStall->InsertGoods( tpObj->itemid(), tpObj->number(), tPriceAry[ i ], /*tStallAry[ i ]*/ i , tItemAry[ i ], tPriceTypeAry[i]);
		tpStall->LockGoods( tItemAry[ i ] );

	}
	return LK_ISUCCESS;
}

void CStallModule::OnMessageGetStallRecord(CEntityPlayer *pPlayer, CMessage *pMessage)
{
	if ( pPlayer == NULL || pMessage == NULL )
	{
		return ;
	}

	CMessageStallGetRecordRequest* tpReq = ( CMessageStallGetRecordRequest* ) pMessage->msgpara();

	CEntityPlayer* tpMaster = dynamic_cast<CEntityPlayer*>(CSceneObjManager::GetSingletonPtr( )->GetObject( tpReq->entityid() ));
	LK_ASSERT( tpMaster != NULL, return );

	if ( tpMaster->HasStall() == false  )
	{
		return ;
	}
	CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( tpMaster->GetStallID() );

	CPropertyPlayer* tpProperty = ( CPropertyPlayer* ) pPlayer->GetProperty();

	CStallInfo* tpInfo = ( CStallInfo* ) tpProperty->GetStallInfo(tpStall->GetStallType());
	if ( tpInfo == NULL )
		return ;

	CMessage tMessage;
	CMessageStallGetRecordResponse tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_STALLRECORD );
	tMessage.set_msgpara( (long) &tPara );

	CPropertyModule::GetSingleton().OnEventGetStallRecord( tpMaster, &tPara ,tpStall->GetStallType());

	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMessage );
	return ;
}

void CStallModule::OnMessageClearStallRecord( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	if ( pPlayer == NULL || pMessage == NULL )
	{
		return ;
	}
	
	if ( pPlayer->HasStall() == false )
	{
		return ;
	}
	CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( pPlayer->GetStallID());

	CPropertyPlayer* tpProperty = ( CPropertyPlayer* ) pPlayer->GetProperty();
	CStallInfo* tpInfo = ( CStallInfo* ) tpProperty->GetStallInfo(tpStall->GetStallType());
	if ( tpInfo == NULL )
	{
		return ;
	}

	tpInfo->CleanRecord();

	CMessage tMessage;
	CMessageStallCleanRecordResponse tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_CLEANRECORD );
	tMessage.set_msgpara( (long) &tPara );
	tPara.set_rtncode( SUCCESS );

	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMessage );
	return ;
}


void CStallModule::SendExchageRequest(CEntityPlayer* pBuyer,CEntityPlayer* pSeller, const CStallRecord* tpRecord ,const int nIBFeeID)
{
	LK_ASSERT(pSeller != NULL && pBuyer != NULL , return);

	// ��Ǯ
	int nSessionID = CSceneLogic::GetSingleton().ExecuteSql(yb_stall_exchange, pBuyer->GetCharID(), pSeller->GetCharID(),
		pSeller->GetAccountID(), SQL_NEED_CALLBACK, SELECT,
		"call ProcYBStallExchange(%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %lld, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
		pSeller->GetCharID(),
		pSeller->GetAccountID(),
		pBuyer->GetCharID(),
		pBuyer->GetAccountID(),
		pSeller->GetLevel(),
		pBuyer->GetLevel(),
		pSeller->GetMetier(),
		pBuyer->GetMetier(),
		pSeller->GetSex(),
		pBuyer->GetSex(),
		tpRecord->mItemID,
		tpRecord->mNumber,
		tpRecord->mItemGuid,
		tpRecord->mPrice,
		tpRecord->mPriceType,
		tpRecord->mFee,
		CSceneLogic::GetSingleton().GetWorldID()*100+8,	
		pBuyer->GetGameID(),
		pSeller->GetGameID(),
		pSeller->GetClientInfo()->mClientAddr,
		pBuyer->GetClientInfo()->mClientAddr,
		nIBFeeID //�������ļ��ж�ȡ��ʱ��Ԫ��˰����
		);

	if( nSessionID > 0 )
	{
		CSession* pSession = (CSession*) CSceneObjManager::GetSingletonPtr()->GetObject( nSessionID );
		LK_ASSERT( pSession != NULL,  return );

		// ��stall�����id���ø�session. ��session�ص����߳�ʱ��ʱ����.
		pSession->SetParam3( tpRecord->get_id() );
	}

	return ;
}



// ����Ԫ���������ݿⳬʱδ����
void CStallModule::OnSessionTimeoutYbStallExchange( CSession* pSession )
{
	LK_ASSERT( pSession != NULL, return );

	CStallRecord* pStallRecord = (CStallRecord*) CSceneObjManager::GetSingletonPtr()->GetObject( pSession->GetParam3() );

	LK_ASSERT( pStallRecord != NULL, return );

	LOG_ERROR( "stall", "Buyer %s buy item(ID:%d, Num:%d) Price(%d) from seller, but the session timeout", 
		pStallRecord->mBuyerName.c_str(), pStallRecord->mItemID, pStallRecord->mNumber, pStallRecord->mPrice );

	int nBuyerCharID = pSession->GetParam1();
	int nSellerCharID =  pSession->GetParam2();
	CEntityPlayer* pBuyer = CSceneLogic::GetSingletonPtr()->GetPlayerByCharID( nBuyerCharID );

	if( pBuyer != NULL )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pBuyer, ERROR_STALL_BUYGOODSFAILED );
	}
	

	CEntityPlayer* pSeller  = CSceneLogic::GetSingletonPtr()->GetPlayerByCharID( nSellerCharID );

	if( pSeller != NULL )
	{
		CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( pSeller->GetStallID() );
		if( tpStall != NULL )
		{
			// ����̯λ��Ʒ�������״̬
			tpStall->SetGoodsStatus( pStallRecord->mStallIndex, GOODS::EGOODS_STATUS_NONE );
		}
	}

	CSceneObjManager::GetSingletonPtr()->DestroyObject( pStallRecord->get_id() );
	
}



// ����Ԫ���������ݿⷵ��
void CStallModule::OnSessionYbStallExchangeResponse( CMessage* pMsg, int nParam1, int nParam2 )
{
	LK_ASSERT( pMsg != NULL, return );
	CMessageExecuteSqlResponse3* tpSqlRes = ( CMessageExecuteSqlResponse3* ) pMsg->msgpara();
	
	CSession* pSession = (CSession*) CSceneObjManager::GetSingletonPtr()->GetObject( tpSqlRes->sessionid() );
	LK_ASSERT( pSession != NULL, return );

	CStallRecord* pStallRecord = (CStallRecord*) CSceneObjManager::GetSingletonPtr()->GetObject( pSession->GetParam3() );
	LK_ASSERT( pStallRecord != NULL, return );


	int nBuyerCharID = pSession->GetParam1();
	int nSellerCharID = pSession->GetParam2() ;

	CEntityPlayer* pBuyer = CSceneLogic::GetSingletonPtr()->GetPlayerByCharID( nBuyerCharID );
	CEntityPlayer* pSeller = CSceneLogic::GetSingletonPtr()->GetPlayerByCharID( nSellerCharID );

	CStall* tpStall = NULL;

	// �ȸ����ҵ�̯λ��Ʒ�������״̬����ֹ��Ϊ�߼����Ͻ�����������Ʒ��������
	if( pSeller != NULL )
	{
		tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( pSeller->GetStallID() );
		if( tpStall != NULL )
		{
			tpStall->SetGoodsStatus( pStallRecord->mStallIndex, GOODS::EGOODS_STATUS_NONE );
		}
	}

	//TODO: ��Ϊ����˫��������С�����¼�������Ŀ���ǲ�������Ʒ��ˢԪ���� ���Լ򻯴������̣���������Һ�����˫��������ʱ�ż�������
	//		�������̽������ɴ˸������ɵ���ʧͨ���˹���ʽ������
	if( pBuyer == NULL || pSeller == NULL )
	{
		LOG_ERROR( "stall", "Buyer %d buy item(ID:%d, Num:%d) Price(%d) from seller %d, but one of them or both is offline ", 
			nBuyerCharID, pStallRecord->mItemID, pStallRecord->mNumber, pStallRecord->mPrice, nSellerCharID );
		
		// ������Դ
		CSceneObjManager::GetSingletonPtr()->DestroyObject( pStallRecord->get_id() );
		return;
	}



	// �ж������û��ִ��
	if ( tpSqlRes->resultcode() == 0 )
	{
		LOG_FATAL( "stall", "YbStallExchange exec failed, Buyer %d buy item(ID:%d, Num:%d) Price(%d) from seller %d", 
			nBuyerCharID, pStallRecord->mItemID, pStallRecord->mNumber, nSellerCharID, pStallRecord->mPrice );

		if( pBuyer != NULL )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pBuyer, ERROR_STALL_BUYGOODSFAILED );
		}

		// ������Դ
		CSceneObjManager::GetSingletonPtr()->DestroyObject( pStallRecord->get_id() );
		return ;
	}

	// �ж�ִ�к�Ľ��
	if( tpSqlRes->rowcount() != 1 || tpSqlRes->colcount() != 2 )
	{
		LOG_ERROR( "stall", "YbStallExchange return , but rowcount or colcount not match");
		
		if( pBuyer != NULL )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pBuyer, ERROR_STALL_BUYGOODSFAILED );
		}

		// ������Դ
		CSceneObjManager::GetSingletonPtr()->DestroyObject( pStallRecord->get_id() );
		return;
	}

	int nResult = atoi( tpSqlRes->fieldvalue( 0 ).c_str() );
	int nBalance =  atoi (tpSqlRes->fieldvalue( 1 ).c_str() );

	int nBuyerRemainGameYB = pBuyer->GetGoldenYB();

	// ִ�д洢����ʧ�ܣ���Ԫ������,��ʱ������ΪһЩbug�����Ϸ�ڴ��е�Ԫ�������ݿ��е�Ԫ����һ�¡�
	if( nResult < 0 )
	{
		LOG_FATAL( "stall", "Buyer %d buy item(ID:%d, Num:%d) Price(%d) from seller %d, maybe the balance in the db(%d) is not match with game(%d)", 
			nBuyerCharID, pStallRecord->mItemID, pStallRecord->mNumber, pStallRecord->mPrice, nSellerCharID, nBalance, nBuyerRemainGameYB );
		
		if( pBuyer != NULL )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pBuyer, ERROR_STALL_BUYGOODSFAILED );
		}

		// ������Դ
		CSceneObjManager::GetSingletonPtr()->DestroyObject( pStallRecord->get_id() );
		return;
	}

	short tSrcList[ 2 ] = { 0 };
	short tDesList[ 2 ] = { pStallRecord->mItemIndex, pStallRecord->mNumber };

	CYuanBao& tBuyerYB =  pBuyer->GetGolden();

	//int tTradeYB = pStallRecord->mPrice;
	//int tFee = pStallRecord->mFee;

	//CStall* tpStall = ( CStall* ) CSceneObjManager::GetSingleton().GetObject( pSeller->GetStallID() );
	if ( tpStall == NULL )
	{
		LOG_ERROR( "stall", "[%s : %d] Player  %d GetStall() failed.", __LK_FILE__, __LINE__, pSeller->GetCharID() );

		if( pBuyer != NULL )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pBuyer, ERROR_STALL_BUYGOODSFAILED );
		}

		// ������Դ
		CSceneObjManager::GetSingletonPtr()->DestroyObject( pStallRecord->get_id() );
		return ;
	}

	unsigned int tItemIndex = 0, tItemNum = 0, tPrice = 0, tItemID = 0, tPriceType = 0;
	int tRet = tpStall->GetGoodsIndex( pStallRecord->mStallIndex, tItemIndex, tItemNum, tPrice, tItemID, tPriceType );


	// unlock item
	// check if you buy all item???
	if ( pStallRecord->mNumber == tItemNum )
	{
		tpStall->UnLockGoods( pStallRecord->mItemIndex  );
	}


	//������Ʒ
	int tTradeYB = pStallRecord->mPrice * pStallRecord->mNumber;
	if (( CPropertyModule::GetSingleton().ExchangeBaggage( pBuyer, pSeller, 0, tSrcList, 1, tDesList, tTradeYB, 0, em_exchange_by_stall_yb)) != EXCHAGE_SUCCESS )
	{
		pBuyer->SetExchange(false);
		pSeller->SetExchange(false);
		
		tBuyerYB.rollback(tTradeYB);
		SendErrorNotice( pBuyer, ERROR_STALL_BUYGOODSFAILED );
		// ������Դ
		CSceneObjManager::GetSingletonPtr()->DestroyObject( pStallRecord->get_id() );
		return ;
	}


	//4.���������ڴ��Ǯ	
	tBuyerYB.commit(tTradeYB);
	CYuanBao& tSellerYB = pSeller->GetGolden();
	tSellerYB.add(tTradeYB);
	// ��¼��־�ۼ����Ԫ��
	LogEventLostMoneyByStall((CEntityPlayer*) pBuyer, CYuanBao::em_golden_yuanbao, tTradeYB, 
		pBuyer->GetCharID(), pStallRecord->mItemID, pStallRecord->mItemGuid);

	// ��¼��־��������Ԫ��
	LogEventGetMoneyByStall((CEntityPlayer*) pSeller, CYuanBao::em_golden_yuanbao, tTradeYB, 
		pSeller->GetCharID(), pStallRecord->mItemID, pStallRecord->mItemGuid);

	tSellerYB.lock(pStallRecord->mFee);
	tSellerYB.commit(pStallRecord->mFee);

	// ��¼��־��������
	LogEventLostMoneyByFee((CEntityPlayer*) pSeller, CYuanBao::em_golden_yuanbao, pStallRecord->mFee, pStallRecord->mPrice, 
		pStallRecord->mItemID, pStallRecord->mItemGuid);

	//�������ʧȥԪ����Ϣ
	CPropertyModule::GetSingleton().SendUpdateYuanbaoNotice(pBuyer, -tTradeYB, pStallRecord->mPriceType);
	//�������һ��Ԫ����Ϣ�����Ԫ���۳�������
	CPropertyModule::GetSingleton().SendUpdateYuanbaoNotice(pSeller, tTradeYB, pStallRecord->mPriceType);
	CPropertyModule::GetSingleton().SendUpdateYuanbaoNotice(pSeller, -pStallRecord->mFee, pStallRecord->mPriceType);

	tpStall->RemoveGoods( pStallRecord->mItemIndex, pStallRecord->mStallIndex, pStallRecord->mNumber );

	CMessage tMessage;
	CMessageBuyGoodsResponse tPara;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_BUYGOODS );
	tPara.set_stallindex( pStallRecord->mStallIndex );
	tPara.set_entityid( pSeller->GetEntityID() );
	tPara.set_number( pStallRecord->mNumber );
	tPara.set_buyerentityid( pBuyer->GetEntityID() );
	tMessage.set_msgpara( (long) &tPara );

	std::vector<CEntityPlayer*> tPlayerVec;
	tPlayerVec.push_back( pBuyer );
	tPlayerVec.push_back( pSeller ); 
	CSceneLogic::GetSingleton().Send2Player( &tPlayerVec, &tMessage );

	CPropertyModule::GetSingleton().OnEventSaveStallRecord( pSeller, pStallRecord, tpStall->GetStallType());

	PrintTradeLog( pSeller->GetCharNameShow(), pSeller->GetCharID(), pBuyer->GetCharNameShow(),pBuyer->GetCharID(), pStallRecord->mItemID, pStallRecord->mNumber, pStallRecord->mPrice, pStallRecord->mPriceType );

	// ������Դ
	CSceneObjManager::GetSingletonPtr()->DestroyObject( pStallRecord->get_id() );

}