#include "stdafx.hpp"
#include "westserver.h"
#include  "mailmessage_pb.hxx.pb.h"
#include "mail.h"
#include "mailmanager.h"
#include "mailmodule.h"
#include "property.h"
#include "propertymodule.h"
#include "property_pb.hxx.pb.h"
#include  "sceneobj_manager.h"
#include "sceneobj_define.h"
#include "errcode.h"   
#include "message_maker.h"
#include "logservertype.h"
#include "scenelogic.h"
#include "logmodule.h"

MailInfo     CMail::m_sMailInfo;						         // ���ڴ浽���ݿ�����ݽṹ	

// ***********************************************************
//  Function:		GetMailDetailInfoCallBack
//  Description:	��ȡ�ʼ���ϸ��Ϣ�Ļص�����	
//  Input:			int CharID						��ҽ�ɫid
//  Input:			int	MailID						�ʼ��������id
//  Input:			MailInfo &MailDeltailInfo		�ʼ�������Ϣ
//  OutPut:			
//  Return:			
//  Others:
//  Date:			03/18/2009		
// **********************************************************
void CMail::GetMailDetailInfoCallBack( int CharID, int MailID, MailInfo &MailDeltailInfo, bool bMailExist /* = true */ )
{
	CEntityPlayer *pPlayer = ( CEntityPlayer * )CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID( CharID );
	if ( pPlayer == NULL )
	{
		// ����Ѿ�����
		return;
	}
	CMail *tpMail = CMailManager::GetSingletonPtr( )->GetMail( pPlayer );
	if ( tpMail == NULL )
	{
		LOG_ERROR( "mail","[%s,%d][%s] Get CMail of CharID:%d Error! ",
			__LK_FILE__,__LINE__,__FUNCTION__,CharID );
		return;
	}
	
	// ����ʼ��Ѿ������ڣ���ɾ���ͻ��˵��ʼ�
	if ( !bMailExist )
	{
		CMessageDelMailResponse tMsgDelMail;
		CMessage				tMessageHead;
		tMsgDelMail.set_mailid( MailID );
		tMessageHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_DELMAIL );
		tMessageHead.set_msgpara( (int)&tMsgDelMail );
		CSceneLogic::GetSingletonPtr()->Send2Player( pPlayer, &tMessageHead );		
		return;		 		
	}
	
	//	���״̬
	if ( tpMail->GetMailStatus() != MAIL_STATUS_GETMAILDETAIL )
	{
		LOG_ERROR( "mail","[%s,%d][%s] Wrong MailBox Status of CharID:%d!",
			__LK_FILE__,__LINE__,__FUNCTION__,CharID );
	}
	
	// �����ʼ�Ϊ��״̬
	tpMail->SetMailStatus( MAIL_STATUS_OPEN );	
	
	// ��ȡ�ʼ�����
	CMailCache *tpMailCache = tpMail->GetMailCacheByMailID( MailID );
	LK_ASSERT( tpMailCache != NULL, return );
	CMessageMailReadResponse MsgReadMail;
	CMessage				 MessageHead;
	MsgReadMail.set_mailid( MailID );
	if ( MailDeltailInfo.mBody != NULL )
	{
		MsgReadMail.set_mailbody( MailDeltailInfo.mBody );
		MAIL_SETTYPE_HASBODY( tpMailCache->mType, 1 );
	}
	else
	{
		MAIL_SETTYPE_HASBODY( tpMailCache->mType, 0 );
	}													  		 
		
	// �и���
	if ( MailDeltailInfo.mExtLen > 0 )
	{
		// �и�����Ϣ
		MailItemBox PbAccesoryBox;
		
		// �и�����Ϣ
		bool Ret              =  PbAccesoryBox.ParseFromArray( MailDeltailInfo.mExtDate, MailDeltailInfo.mExtLen );
		if ( Ret == false )
		{
			LOG_ERROR( "mail","[%s,%d][%s] Parse Accessory From Array Error! ", __LK_FILE__,__LINE__,__FUNCTION__ );
			CSceneObjManager::GetSingletonPtr( )->DestroyObject( OBJTYPE_MAIL_MAILCACHE );
			return;
		}
		
		// ����и����򽫸�����������
		tpMailCache->mItemNum =  PbAccesoryBox.mailitem_size( );
		if ( tpMailCache->mItemNum >= 0  )
		{
			CItemObject  *tpItemObj   = NULL;
			PBItemObject *tpPbItemObj = NULL; 
			CTplItem     *tpTplItem   = NULL;
			int           ItemIndex   = 0;
			
			// ��������Ʒ
			for( int i = 0 ; i<tpMailCache->mItemNum ; i++ )
			{
				tpPbItemObj = PbAccesoryBox.mutable_mailitem( i );
				ItemIndex	= PbAccesoryBox.itemindex( i );
				tpTplItem   =( CTplItem    * ) CDataStatic::SearchTpl( tpPbItemObj->itemid() );
				if ( tpTplItem == NULL )
				{				
					continue;
				}

				tpItemObj   = ( CItemObject  * )CItemRunTime::CloneFromBinary2( tpPbItemObj );
				if ( tpItemObj == 0 )
				{					
					continue;
				}
				tpPbItemObj = MsgReadMail.add_accessory();
				tpItemObj->GetItemBinaryBuffer2( tpPbItemObj, tpItemObj->GetItemNum() );
				MsgReadMail.add_mailitemindex( ItemIndex );							
				tpMailCache->mItemObjID[ItemIndex] = tpItemObj->get_id();				
			}
		}
	}
	MessageHead.mutable_msghead( )->set_messageid( ID_S2C_RESPONSE_READMAIL );
	MessageHead.set_msgpara( ( int )& MsgReadMail );
	CSceneLogic::GetSingletonPtr()->Send2Player( pPlayer, &MessageHead ); 
	
	// ��¼��־
	LogEventReceiveMail( CharID, tpMailCache, tpMail->m_nTotalMailCount );
	
	// ��������ʼ��Ļ�����Ҫ���̣��ı��ʼ���״̬
	if ( MAIL_IS_NEW( tpMailCache->mType ) )
	{
		MAIL_SETTYPE_NEW( tpMailCache->mType, 0 )
		MAIL_SETTYPE_NEEDSAVE( tpMailCache->mType, 1 )
	}	
	
	// �ʼ������Ѷ�
	MAIL_SETTYPE_HASSENDTOCLIENT( tpMailCache->mType, 1 )	
}

// ***********************************************************
//  Function:		SendMailCallBack
//  Description:	�����ʼ��Ļص�����������ʼ�id���ʼ����͸��ͻ���
//  Input:			int MailID				�ʼ�id
//  Input:			int MailCacheID			�ʼ��������id
//  Input:			int CharID				�ʼ����շ���ɫid		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			03/18/2009		
// **********************************************************
void CMail::SendMailCallBack( int MailID, int MailCacheID, int CharID )
{		
	CMailCache *tpMailCache = ( CMailCache * )CSceneObjManager::GetSingletonPtr()->GetObject( MailCacheID );
	LK_ASSERT( tpMailCache != NULL, return );
	
	// �ʼ��洢ʧ��						  
	if( MailID == -1 )
	{
		LOG_ERROR( "mail","[%s,%d][%s] Empty CMailCache of CharID %d",__LK_FILE__,__LINE__,__FUNCTION__, CharID );
		CSceneObjManager::GetSingletonPtr()->DestroyObject( MailCacheID );
		return;
	}  
	tpMailCache->mMailID = MailID; 
	
	// ��¼���ݿ�, ��������Ʒ
	int pItemIDList[MAIL_ITEM_COUNT_MAX] = { 0 };
	int pItemNumList[MAIL_ITEM_COUNT_MAX] = { 0 };	 
	int tItemNum = 0;	
	for ( int i = 0; i < MAIL_ITEM_COUNT_MAX; ++i )
	{
		if ( tpMailCache->mItemObjID[i] == 0 )
		{			
			continue;
		}
		CItemObject *tpItemObj = ( CItemObject * )CSceneObjManager::GetSingleton().GetObject( tpMailCache->mItemObjID[i] );
		if ( tpItemObj == NULL )
		{
			continue;
		}		
		pItemIDList[tItemNum]	 = tpItemObj->GetItemID();
		pItemNumList[tItemNum]   = tpItemObj->GetItemNum();
		++tItemNum;		
		CSceneObjManager::GetSingletonPtr()->DestroyObject( tpMailCache->mItemObjID[i] );			
	}	
	
	
	LogEventSendMail( tpMailCache->mSrcId, tpMailCache, pItemIDList, pItemNumList, tItemNum, CharID );	

	int tRet = SendNewMailNotice( CharID, tpMailCache );   		
	if ( tRet == 0 )
	{
		CSceneObjManager::GetSingletonPtr()->DestroyObject( MailCacheID );
	}	
}


// ***********************************************************
//  Function:		RecMailFromDBCallBack
//  Description:	�������ݿ����淵�ص��ʼ��������������
//  Input:			int pMail								���CMail����ָ��
//  Input:			MailInfo *tpMailInfor					�ʼ�������Ϣ
//  Input:			bool IfEnd								�Ƿ�����ȡ���һ���ʼ�
//  Input:			CMessageMailListNotify & MsgMailList	�ʼ�֪ͨ�б���Ϣ	
//  Input:			int ReceKind							�����ݿ�ȡ�ʼ������ͣ���ȡ�ʼ��б�ȡ�µ�δ���ʼ���
//  OutPut:			
//  Return:				
//  Others:
//  Date:			2009-02-18		
// **********************************************************
void CMail::RecMailFromDBCallBack( CEntityPlayer *pPlayer, CMail *tpMail, MailInfo *tpMailInfor, bool IfEnd, CMessageMailListNotify & MsgMailList, int ReceKind /* = FETCHMAIL_PAGE */ )
{

	LK_ASSERT( pPlayer != NULL && tpMail != NULL, return );	 

	// ����һҳ�ʼ���Ϣ
	if ( IfEnd == true )
	{
		CMessage                   MessageHead;			
		MessageHead.mutable_msghead( )->set_messageid( ID_S2C_NOTIFY_MAILLISTINFO );
		MessageHead.set_msgpara( (int)&MsgMailList );
		CSceneLogic::GetSingletonPtr( )->Send2Player( pPlayer, &MessageHead );			
		return ;
	}
	if ( tpMailInfor == NULL )
	{
		return;
	}		
	CMailCache *tpMailCache = ( CMailCache * )CSceneObjManager::GetSingletonPtr( )->CreateObject( OBJTYPE_MAIL_MAILCACHE );
	if ( tpMailCache == NULL  )
	{
		LOG_ERROR( "mail","[%s,%d][%s] Creat CMailCache Failed! ", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}
	tpMailCache->mMailID           =  tpMailInfor->mMailBase.mMailID; 
	tpMailCache->mSendTime         =  tpMailInfor->mMailBase.mSendTime;
	tpMailCache->mSrcId			   =  tpMailInfor->mMailBase.mSrcId;
	if ( tpMailInfor->mMailBase.mSrc != NULL )
	{
		strncpy(  tpMailCache->mSrcName,tpMailInfor->mMailBase.mSrc ,NAME_LENGTH-1 );
		tpMailCache->mSrcName[NAME_LENGTH -1] = '\0';
	}
	tpMailCache->mLevel            =  tpMailInfor->mMailBase.mLevel;
	tpMailCache->mType             =  tpMailInfor->mMailBase.mType;
	if ( tpMailInfor->mMailBase.mTitle != NULL )
	{
		strncpy( tpMailCache->mMailTitle , tpMailInfor->mMailBase.mTitle , MAIL_TITLE_LEN - 1 );
		tpMailCache->mMailTitle[MAIL_TITLE_LEN-1] = '\0';
	}
	tpMailCache->mMoney            =  tpMailInfor->mMoneySend;
	tpMailCache->mMoneyNeedPayBack =  tpMailInfor->mMoneyNeedBack;
	tpMailCache->mExpiredTime	   =  tpMailInfor->mMailBase.mExpiredTime;	
	
	// �ʼ�����δ��
	MAIL_SETTYPE_HASSENDTOCLIENT( tpMailCache->mType, 0  );
	
	// ȡ���ʼ�
	if ( ReceKind == FETCHMAIL_NEW )
	{
		// ��������ʼ����뵽����ͷ		
		int nInsertRet = tpMail->InsertMail( tpMailCache );
	
		if( ( nInsertRet == 0) || (nInsertRet == 1) )
		{
			CMessageNewMailNotify MsgNewMail;
			CMessage			   MessageHead;	
			if ( tpMailInfor->mMailBase.mTitle != NULL )
			{
				MsgNewMail.mutable_maillist(  )->set_title( tpMailInfor->mMailBase.mTitle );
			}	
			MsgNewMail.mutable_maillist(  )->set_sendtime( tpMailInfor->mMailBase.mSendTime );
			MsgNewMail.mutable_maillist(  )->set_maillevel( tpMailInfor->mMailBase.mLevel );
			if ( tpMailInfor->mMailBase.mSrc != NULL )
			{
				MsgNewMail.mutable_maillist(  )->set_srcname( tpMailInfor->mMailBase.mSrc );
			}		
			MsgNewMail.mutable_maillist(  )->set_money( tpMailInfor->mMoneySend );
			MsgNewMail.mutable_maillist(  )->set_itemnum( tpMailInfor->mMailBase.mItemNum );
			MsgNewMail.mutable_maillist(  )->set_mailid( tpMailInfor->mMailBase.mMailID );	
			MsgNewMail.mutable_maillist(  )->set_mailtype( tpMailInfor->mMailBase.mType );	
			MsgNewMail.mutable_maillist(  )->set_expiredtime( tpMailInfor->mMailBase.mExpiredTime/DAY_TIME );
			MsgNewMail.mutable_maillist(  )->set_moneyneedback( tpMailInfor->mMoneyNeedBack );
			
			MsgNewMail.set_haslist( (nInsertRet == 0) ? 0:  1 );
			
			MessageHead.mutable_msghead(  )->set_messageid( ID_S2C_NOTIFY_NEWMAIL );
			MessageHead.set_msgpara( (int)&MsgNewMail );
			CSceneLogic::GetSingletonPtr()->Send2Player( pPlayer, &MessageHead );
		}

		if( nInsertRet != 1 )
		{
			CSceneObjManager::GetSingletonPtr()->DestroyObject( tpMailCache->get_id() );
		}

	}
	// ȡ�ʼ��б�		
	else if ( ReceKind == FETCHMAIL_PAGE )
	{	 	
		// ������������ʼ����������ʼ�����++
		if ( MAIL_IS_LOCK( tpMailCache->mType ) )
		{
			++ tpMail->m_nLockMailNum;
		}
		
		// ��ȡһҳ���ļ������뵽����β		
		if( tpMail->InsertMail( tpMailCache ) != 1 )
		{
			CSceneObjManager::GetSingletonPtr()->DestroyObject( tpMailCache->get_id() );
			return ;
		}

		CMailInfo *pMailInfo = MsgMailList.add_maillist( );
		if ( tpMailInfor->mMailBase.mTitle != NULL )
		{	 
			pMailInfo->set_title( tpMailInfor->mMailBase.mTitle );
		}					 			
		pMailInfo->set_sendtime( tpMailInfor->mMailBase.mSendTime );
		pMailInfo->set_maillevel( tpMailInfor->mMailBase.mLevel );
		if ( tpMailInfor->mMailBase.mSrc != NULL )
		{
			pMailInfo->set_srcname( tpMailInfor->mMailBase.mSrc );
		}		
		pMailInfo->set_money( tpMailInfor->mMoneySend );
		pMailInfo->set_itemnum( tpMailInfor->mMailBase.mItemNum );
		pMailInfo->set_mailid( tpMailInfor->mMailBase.mMailID );	
		pMailInfo->set_mailtype( tpMailInfor->mMailBase.mType );
		pMailInfo->set_expiredtime( tpMailInfor->mMailBase.mExpiredTime/DAY_TIME );	
		pMailInfo->set_moneyneedback( tpMailInfor->mMoneyNeedBack );
	}	
	return;
}	

// ***********************************************************
//  Function:		
//  Description:	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::GetCharID( )
{	
	CEntityPlayer *pPlayer = GetEntityPlayer();
	LK_ASSERT( pPlayer != NULL, return 0 );
	return pPlayer->GetCharID();
}

// ***********************************************************
//  Function:		
//  Description:	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2010-01-01		
// **********************************************************
bool CMail::CanSendNewMailNotice( )
{ 
	// �ͻ����ܹ���ʾ���ʼ��������������ܲ���
	if ( m_nCurCacheMailCount >= MAIL_MAILBOX_MAXMAILNUM || m_nTotalMailCount > MAIL_MAILBOX_MAXMAILNUM )
	{			
		return false;
	}		
	return 	true;
}


// ***********************************************************
//  Function:		GetMailStatus
//  Description:	��ȡ�ʼ�״̬
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int  CMail::GetMailStatus(  )
{
	return m_nMailBoxStatus;
}

// ***********************************************************
//  Function:		vMailStatus
//  Description:	�����ʼ�״̬���첽�¼�����״̬һ��
//  Input:			int  vMailStatus �ʼ�״̬
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
void CMail::SetMailStatus( int  vMailStatus )
{
	m_nMailBoxStatus = vMailStatus;
}


// ***********************************************************
//  Function:		IfMailBoxInitial
//  Description:	�����Ƿ��Ѿ���ʼ�����,�Ƿ��ȡ���ݿ��ʼ��������
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
bool CMail::IfMailBoxInitial(  )
{
	if ( m_nMailBoxStatus != MAIL_STATUS_INITIALIZE )
	{
		return true;
	}
	return false;
}


// ***********************************************************
//  Function:		Send	
//  Description:	����׫д���ʼ�
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::Send( int vMoney, int MoneyNeedPayBack, const char *pMailTitle, const char *pMailBody, int DesCharID, const char *pDesname )
{	
	CEntityPlayer *pPlayer = GetEntityPlayer();
	if( pPlayer == NULL )
		return -1;
		
    // ���㷢����Ҫ�Ľ�Ǯ  
    int MoneyNeedToPay = MAIL_SEND_MONEY_PRO;
	for ( int i=0; i <  MAIL_ITEM_COUNT_MAX ; i++ )
	{
		if ( m_nList[i].ItemNum > 0 )
		{
			MoneyNeedToPay = MoneyNeedToPay + MAIL_ITEM_CHARGE;
		}
	}		
	CPropertyPlayer* pProperty = ( CPropertyPlayer* ) pPlayer->GetProperty( );
		
	// ��Ǯ����
    if ( ( unsigned int  )( pProperty->GetMoney( ) + pProperty->GetBindMoney() ) < ( unsigned int )(  MoneyNeedToPay + vMoney )
		 || ( unsigned int )pProperty->GetMoney() < ( unsigned int )vMoney 
	   )
    {
		// �����ʼ���ϣ���ո����б�
		ClearItemList( );	
		return ERR_MAIL_SENDMAIL_MONEYNOTENOUGH;
    }
    
    // ������Ҫ���ĵİ󶨽�Ǯ
    int tBindMoney = MoneyNeedToPay< pProperty->GetBindMoney()?MoneyNeedToPay:pProperty->GetBindMoney();
    int tMoneyCharge = MoneyNeedToPay - tBindMoney + vMoney; 
    	
	// ����һ���ʼ�����
	CMailCache *tpMailCache = CreatNewMail( vMoney , MoneyNeedPayBack , pMailTitle , DesCharID, pDesname);
	if ( tpMailCache == NULL )
	{
		// �����ʼ�ʧ��
		LOG_ERROR( "mail","[%s,%d][%s] Creat CMailCache Failed! ",
		 __LK_FILE__,__LINE__,__FUNCTION__ );
		return -1;
	}
	
	//// ����ռ������ߣ����ʼ����͸��Է�
	//bool IfNeedCallBack = SendMailToPlayer( DesCharID, tpMailCache  );	
	
	// ���ʼ����浽���ݿ�	
	SaveMail( tpMailCache, pMailBody, DesCharID, true, pDesname, pPlayer->GetNationality() );
	
	// �۱������ʼ��ķ���  	
	if ( tBindMoney > 0 && CPropertyModule::GetSingletonPtr( )->PlayerChangeMoney( pPlayer, tBindMoney , true, true ) == SUCCESS)
	{
		LogEventLostMoneyByPostalFee(pPlayer, CYuanBao::em_bind_money, tBindMoney, DesCharID, tpMailCache->get_id() );
	}

	if ( tMoneyCharge > 0 && CPropertyModule::GetSingletonPtr( )->PlayerChangeMoney( pPlayer, tMoneyCharge , true, false ) == SUCCESS)
	{
		LogEventLostMoneyBySendMail(pPlayer, CYuanBao::em_unbind_money, tMoneyCharge, DesCharID, tpMailCache->get_id());
	}

	// �����ʼ���ϣ���ո����б�( ���յ����ݿ���Ϣ���غ������ )
	ClearItemList( );	
	return ERR_MAIL_SENDMAIL_SUCESS;	
}


// ***********************************************************
//  Function:		SendMailToPlayer	
//  Description:	�����ʼ����ͻ���
//  Input:			int DesCharID				�Է���ɫid
//  Input:			CMailCache *tpMailCache		�ʼ�����ָ��
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
//bool CMail::SendMailToPlayer( int DesCharID, CMailCache *tpMailCache )
//{
//	if ( tpMailCache == NULL )
//	{
//		return false;
//	}	
//	bool IfNeedCallBack = true;
//	
//	// ��ȡ�ռ��˵��ʼ���Ϣ
//	CEntityPlayer *pPlayer = ( CEntityPlayer * )CSceneLogic::GetSingleton().GetPlayerByCharID( DesCharID );
//	if ( pPlayer != NULL )
//	{
//		CMail *tpDesMail    = CMailManager::GetSingletonPtr( )->GetMail( pPlayer );
//		LK_ASSERT( tpDesMail != NULL, return  false );
//		
//		// ���뵽�ռ������ʼ�������
//		bool tRet =  tpDesMail->CanSendNewMailNotice(); /*tpDesMail->InsertMail( tpMailCache, 1 );	*/	
//		if ( tRet != true )
//		{
//			IfNeedCallBack = false;	 		
//		}
//		else
//		{
//			CMessage MsgHead;
//			CMessageNewMailNotify MsgNewMail;
//			MsgNewMail.set_haslist( 0 );
//			MsgHead.set_msgpara( (int)&MsgNewMail );
//			MsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_NEWMAIL );
//			CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
//		}	  								
//	}
//	return IfNeedCallBack;
//}

// ***********************************************************
//  Function:		SendNewMailNotice	
//  Description:	�������ʼ�����Ϣ֪ͨ
//  Input:			int DesCharID				�Է���ɫid
//  Input:			CMailCache *tpMailCache		�ʼ�����ָ��
//  OutPut:			
//  Return:			int		1��ʾ����Ҫɾ���ʼ����棬 0��ʾҪɾ���ʼ�����
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::SendNewMailNotice( int DesCharID, CMailCache *tpMailCache ) 
{  	
	LK_ASSERT( tpMailCache != NULL, return 0 );
	CMessageNewMailNotify MsgNewMail;
	CMessage			   MessageHead;	 	
	MsgNewMail.mutable_router()->set_send2player( 0 );
	MsgNewMail.mutable_router()->set_srccharid( tpMailCache->mSrcId );
	MsgNewMail.mutable_router()->set_descharid( DesCharID );
	MsgNewMail.mutable_router()->set_routertype( CMessageRouter::ROUTER_CHAR );	
	if ( tpMailCache->mMailTitle != NULL )
	{
		MsgNewMail.mutable_maillist( )->set_title( tpMailCache->mMailTitle );
	}	
	MsgNewMail.mutable_maillist( )->set_sendtime( tpMailCache->mSendTime );
	MsgNewMail.mutable_maillist( )->set_maillevel( tpMailCache->mLevel );
	if ( tpMailCache->mSrcName != NULL )
	{
		MsgNewMail.mutable_maillist(  )->set_srcname( tpMailCache->mSrcName );
	}		
	MsgNewMail.mutable_maillist(  )->set_money( tpMailCache->mMoney );
	MsgNewMail.mutable_maillist(  )->set_itemnum( tpMailCache->mItemNum );
	MsgNewMail.mutable_maillist(  )->set_mailid( tpMailCache->mMailID );	
	MsgNewMail.mutable_maillist(  )->set_mailtype( tpMailCache->mType );	
	MsgNewMail.mutable_maillist(  )->set_expiredtime( tpMailCache->mExpiredTime/DAY_TIME );
	MsgNewMail.mutable_maillist(  )->set_moneyneedback( tpMailCache->mMoneyNeedPayBack );
	MessageHead.mutable_msghead(  )->set_messageid( ID_S2C_NOTIFY_NEWMAIL );
	MessageHead.set_msgpara( (int)&MsgNewMail );
	
	CEntityPlayer *pPlayer = CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID( DesCharID );
	
	// ����ڱ�����������
	if ( pPlayer != NULL )
	{			  
		CMail *tpMail = CMailManager::GetSingleton().GetMail( pPlayer );
		LK_ASSERT( tpMail != NULL, return 0 );
	
		int nInsertRet = tpMail->InsertMail( tpMailCache, 1 );
		if ( (nInsertRet == 0 ) || (nInsertRet == 1 ) )
		{
			MsgNewMail.set_haslist( (nInsertRet == 0) ? 0 : 1 );	

			CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &MessageHead );
		}

		if( nInsertRet != 1 )
		{
			return 0;
		}

		return 1;
	}  		
	
	// ��Ҳ����߻���������������
	CSceneLogic::GetSingletonPtr( )->Send2Gate( &MessageHead );
	return 0;			
}	

// ***********************************************************
//  Function:		ChangeMailItem	
//  Description:	�ı䷢���ʼ��ĸ���
//  Input:			int SrcIndex		Դ����	 
//  Input:			int ItemNum			�ƶ�����Ʒ����
//  Input:			int MovePos			�ƶ���ʽ��0��ʾ�ڰ����͸����б�λ��
//	֮����ƶ���ItemNum>0 ��ʾ�Ӱ����������б� ItemNum<=0 ��ʾ�Ӹ����б�
//	������ ����1��ʾ�ڸ����б�λ���ϵ��ƶ�
//  OutPut:			
//  Return:			int					1��ʾ�ƶ��ɹ������ʾ�ƶ�ʧ��
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::ChangeMailItem( int SrcIndex, int ItemNum, int DesIndex, int MovePos )
{

	// ������ȷ�Լ��
	if ( ItemNum < 0 || SrcIndex < 0  || DesIndex < 0 )
	{
		LOG_ERROR( "mail","[%s,%d][%s] WrongItemIndex��source index:%d, destination index :%d !",
			 __LK_FILE__,__LINE__,__FUNCTION__, SrcIndex, DesIndex );
		return -1;
	}	
	// ��ȡ�������
	CEntityPlayer *pPlayer = GetEntityPlayer();
	if( pPlayer == NULL )
	{
		LOG_ERROR( "mail","[%s,%d][%s] CEntityPlayer is null, entity id:%d !", 
			__LK_FILE__,__LINE__,__FUNCTION__, m_nEntityID );
		return -1;
	}
	CPropertyPlayer* tpProperty = ( CPropertyPlayer* )pPlayer->GetProperty( );		
	
	// �ڸ����б�֮���ƶ���Ʒ
	if ( MovePos == ITEM_MOVE )
	{
		if ( SrcIndex >= MAIL_ITEM_COUNT_MAX || DesIndex >= MAIL_ITEM_COUNT_MAX )
		{
			LOG_ERROR( "mail","[%s,%d][%s] Wrong Item Index, source index:%d, destination index:%d!",
				 __LK_FILE__,__LINE__,__FUNCTION__, SrcIndex, DesIndex );
			return -1;
		}	
		
		// Դ��Ŀ����ͬ		
		if( SrcIndex == DesIndex )
		{
			LOG_DEBUG( "mail","[%s,%d][%s]  same Src index and des Index, source index:%d !", 
				__LK_FILE__,__LINE__,__FUNCTION__, SrcIndex );
			return -1;
		}
		if ( m_nList[SrcIndex].ItemNum > 0  )
		{
			int MoveItemIndex =  m_nList[DesIndex].ItemNum;
			int MoveItemNum   =	 m_nList[DesIndex].ItemIndex;
			m_nList[DesIndex].ItemNum	= m_nList[SrcIndex].ItemNum;
			m_nList[DesIndex].ItemIndex = m_nList[SrcIndex].ItemIndex;
			m_nList[SrcIndex].ItemNum	= MoveItemIndex;
			m_nList[SrcIndex].ItemIndex = MoveItemNum;			
			return 1;
		}
		LOG_ERROR( "mail","[%s,%d][%s] Item num is wrong, item number:%d, source index:%d  !",
			 __LK_FILE__,__LINE__,__FUNCTION__, m_nList[SrcIndex].ItemNum, SrcIndex );
		return -1;
	}	
		
	// �ڸ����б�Ͱ���֮���ƶ���Ʒ		
	int PackageIndex = 0;		// �ƶ�����Ʒ�ڰ������������
	if ( ItemNum > 0 )
	{
		PackageIndex = SrcIndex;
	}
	else
	{
		PackageIndex = DesIndex;
	}

	// ��ȡ���ƶ�����Ʒ
	CItemObject *tpItemObj =( CItemObject * ) tpProperty->GetBaggage( )->GetItemObjPtr( PackageIndex );
	if ( tpItemObj == NULL )
	{
		// error
		LOG_ERROR( "mail","[%s,%d][%s] Item is null while sending mail, item index:%d ",
			__LK_FILE__,__LINE__,__FUNCTION__, SrcIndex );
		// ��Ʒ������
		return -1;
	}	
	
	// �ж���Ʒ�İ�״̬
	if ( tpItemObj->GetBindStatus() != ITEM_BINDSTATUS_FREE )
	{
		// ��Ʒ�Ѿ���
		return ITEM_MAIL_BINDED;
	}  
		
	// ȡ�¸�����Ʒ
	if( MovePos == ITEM_TAKE )
	{
	  
		// ����λ�úϷ��Լ��
	   if ( SrcIndex >= MAIL_ITEM_COUNT_MAX || ( !tpProperty->GetBaggage( )->CheckIndexValid( DesIndex ) ) )
	   {
			// error
			LOG_ERROR( "mail","[%s,%d][%s] wrong item index, ��source index:%d , destination index: %d !", 
				__LK_FILE__,__LINE__,__FUNCTION__, SrcIndex, DesIndex );
			return -1;
	   }
	   // û����Ʒ�����ƶ�   	
	   if ( m_nList[ SrcIndex ].ItemNum <= 0 )
	   {
			// error 
			LOG_ERROR( "mail","[%s,%d][%s] wrong item index��source index:%d , destination index: %d !  !",
				 __LK_FILE__,__LINE__,__FUNCTION__, SrcIndex, DesIndex );
			return -1;
	   }
	   if (  m_nList[ SrcIndex ].ItemIndex != DesIndex  )
	   {
			LOG_ERROR( "mail","[%s,%d][%s] wrong item index��source index:%d , destination index: %d !", __LK_FILE__,__LINE__,__FUNCTION__, SrcIndex, DesIndex );
		   return -1;
	   }
	   
	   // ����Ʒ����
	   if ( tpItemObj->GetLockStatus() == LOCKTYPE_MAIL )
	   {
		   CMessage HeadMessage;
		   CMessageLockItemNotice LockItemNotice ;   
		   tpProperty->GetBaggage( )->Lock( m_nList[ SrcIndex ].ItemIndex ,LOCKTYPE_NONE );	
		   HeadMessage.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_LOCKITEM );
		   HeadMessage.set_msgpara( (int )&LockItemNotice );
		   LockItemNotice.set_index( m_nList[ SrcIndex ].ItemIndex );
		   LockItemNotice.set_locked( LOCKTYPE_NONE );
		   CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &HeadMessage ); 
	   }	 
	   m_nList[SrcIndex].ItemNum = 0;
	   m_nList[SrcIndex].ItemIndex = -1;
	}
	// ���ø�����Ʒ
	else if( MovePos == ITEM_ADD )
	{			
		// �ж���Ʒ������״̬
		if ( tpItemObj->GetLockStatus() != LOCKTYPE_NONE )
		{
			return -1;
		}		
	
		// ����λ�úϷ��Լ��
		if( ( !tpProperty->GetBaggage( )->CheckIndexValid( SrcIndex ) ) || DesIndex >= MAIL_ITEM_COUNT_MAX )
		{
			LOG_ERROR( "mail","[%s,%d][%s] wrong item index ��source index:%d , destination index: %d !", __LK_FILE__,__LINE__,__FUNCTION__, SrcIndex, DesIndex );
			return -1;
		}
		
		// �Ѿ�����Ʒ���ܷ�����Ʒ
		if ( m_nList[ DesIndex ].ItemNum > 0 )
		{
			LOG_ERROR( "mail","[%s,%d][%s] Wrong destination item index��source index:%d , destination index: %d ",
				 __LK_FILE__,__LINE__,__FUNCTION__, SrcIndex, DesIndex);
			return -1;	
		}			
		
		// ����Ʒ����
		CMessage HeadMessage;
		CMessageLockItemNotice LockItemNotice ;   
		m_nList[DesIndex].ItemNum = ItemNum;			// ��¼����
		m_nList[DesIndex].ItemIndex = SrcIndex;			// ��¼��Ʒ�ڰ����е�����
		tpProperty->GetBaggage( )->Lock( SrcIndex ,LOCKTYPE_MAIL );
		HeadMessage.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_LOCKITEM );
		HeadMessage.set_msgpara( (int )&LockItemNotice );
		LockItemNotice.set_index( SrcIndex );
		LockItemNotice.set_locked( LOCKTYPE_MAIL );
		CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &HeadMessage ); 
	}	
	return SUCCESS;
}

// ***********************************************************
//  Function:		SetMailReceiverID	
//  Description:	�����ʼ����շ���ɫID
//  Input:			int DestCharID		��ҽ�ɫid	 
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
void CMail::SetMailReceiverID( int DestCharID )
{
	m_nReceiverID = DestCharID;
}


// ***********************************************************
//  Function:		GetMailReceiverID	
//  Description:	��ȡ�ʼ����շ���ɫID
//  OutPut:			
//  Return:			int				�ʼ����շ���ɫid	
//  Others:
//  Date:			2009-02-18		
// **********************************************************

int CMail::GetMailReceiverID()
{
	return m_nReceiverID;
}


// ***********************************************************
//  Function:	  GetAccessory	
//  Description:  ��ȡ�շ��ʼ��ĸ���	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::GetAccessory( int vMailID )
{
	
	CMailCache *tpMailCache = GetMailCacheByMailID( vMailID );
	if ( tpMailCache == NULL )
	{
		return -1;
	}	
	CEntityPlayer *pPlayer = GetEntityPlayer();
	if ( pPlayer == NULL )
	{
		return -1;
	}
	CPropertyPlayer* tpProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	CTemplateLevelMoneyLmt* tpMoneyTable = (CTemplateLevelMoneyLmt*)CDataStatic::GetTemp(TEMP_MONEYLMT_CFG);
	LK_ASSERT( tpMoneyTable!=NULL, return -1 );
	LK_ASSERT( pPlayer->GetLevel() >= 0 && pPlayer->GetLevel() < TMP_MAX_GRADE, return -1 );

	// �жϽ�Ǯ����
	if(  tpProperty->GetMoney() + tpMailCache->mMoney > MONEY_LIMIT 
		|| (unsigned int)(tpProperty->GetMoney() + tpMailCache->mMoney) > tpMoneyTable->mLmtTable[pPlayer->GetLevel()].mBagMoneyLmt ) 
	{
		return ERR_BAG_MONEY_UPLMT;
	}

	// ��ȡ��Ǯ
	if (CPropertyModule::GetSingletonPtr( )->PlayerChangeMoney( pPlayer, tpMailCache->mMoney, false, false ) == SUCCESS)
	{
		LogEventGetMoneyByRecvMail(pPlayer, 
				CYuanBao::em_unbind_money, tpMailCache->mMoney, tpMailCache->mSrcId, vMailID, tpMailCache->mSendTime );
	}
	
	/*
		�ѽ�Ǯ���͸��ʼ����ͷ�
	*/
	
	tpMailCache->mMoney = 0;	
	/*
		�жϰ�����������
	*/ 
	// ��ȡ����
	for ( int i = 0; i<MAIL_ITEM_COUNT_MAX; i ++ )
	{
		if ( tpMailCache->mItemObjID[i] == 0 )
		{
			continue;
		}
		CItemObject *tpObj = ( CItemObject * )CSceneObjManager::GetSingletonPtr()->GetObject( tpMailCache->mItemObjID[i] );
		if ( tpObj == NULL )
		{
			continue;
		}

		int nItemNum = tpObj->GetItemNum();
		uint64_t ullGUID = tpObj->GetGUID();

		if (CPropertyModule::GetSingletonPtr( )->PlayerInsertItem( pPlayer, tpObj ));
		{
			LogEventGetItemByRecvMail(pPlayer, ullGUID, tpObj->GetItemID(), nItemNum, 
					tpMailCache->mSrcId, vMailID, tpMailCache->mSendTime );
		}

		tpMailCache->mItemObjID[i]  = 0;
	}  
	return 0;
}



// ***********************************************************
//  Function:		GetAccessory
//  Description:	��ȡ��ͨ�ʼ�����	
//  Input:			int vItemIndex			������Ʒ����
//  Input:			int vMailID				�ʼ�ID
//  Input:			bool vIsMoney			�Ƿ��Ǯ
//  OutPut:			
//  Return:			1 ��ʾ��ȡ�ɹ���2��ʾ�ɹ�������Ҫ�ӿͻ����б�����ɾ���ʼ���
//					-1��ʾʧ��, ������ʾ������ʾ��
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::GetAccessory( int vItemIndex, int vMailID, bool vIsMoney )
{
	// ��ȡ�ʼ�
	CMailCache *tpMailCache = GetMailCacheByMailID( vMailID );
	if( tpMailCache == NULL )
	{	
		return -1;
	}
	
	// �����Ϸ��Լ��
	if ( vItemIndex < 0 || vItemIndex >= MAIL_ITEM_COUNT_MAX )
	{
		return -1;
	}
	
	// �ж��Ƿ񸶷��ʼ�
	if ( tpMailCache->mMoneyNeedPayBack > 0 )
	{
		return ERR_MAIL_GETACCESSORY_MONEYNOTPAY;
	}
	
	// ��ȡ��������
	CEntityPlayer *pPlayer = GetEntityPlayer();
	if ( pPlayer == NULL )
	{
		return -1;
	}
	CPropertyPlayer *tpProperty = ( CPropertyPlayer *)pPlayer->GetProperty();  
	
	// ����ʼ��Ѿ����ڣ�����ȡ����
	if ( tpMailCache->mExpiredTime <= time( NULL ) )
	{
		return ERR_MAIL_GETACCESSORY_EXPIRED;
	}

	// ��ȡ�����еĽ�Ǯ
	if ( vIsMoney == true )
	{
		CTemplateLevelMoneyLmt* tpMoneyTable = (CTemplateLevelMoneyLmt*)CDataStatic::GetTemp(TEMP_MONEYLMT_CFG);
		LK_ASSERT( tpMoneyTable!=NULL, return -1 );
		LK_ASSERT( pPlayer->GetLevel() >= 0 && pPlayer->GetLevel() < TMP_MAX_GRADE, return -1 );

		// �жϽ�Ǯ����
		if(  tpProperty->GetMoney() + tpMailCache->mMoney > MONEY_LIMIT 
			|| (unsigned int)(tpProperty->GetMoney() + tpMailCache->mMoney) > tpMoneyTable->mLmtTable[pPlayer->GetLevel()].mBagMoneyLmt ) 
		{
			return ERR_BAG_MONEY_UPLMT;
		}
		
		if ( tpMailCache->mMoney > 0 )
		{
			if (CPropertyModule::GetSingletonPtr()->PlayerChangeMoney( pPlayer, tpMailCache->mMoney, false , false ) == SUCCESS)
			{
				LogEventGetMoneyByRecvMail( pPlayer,
						CYuanBao::em_unbind_money, tpMailCache->mMoney, vMailID, tpMailCache->mSrcId, tpMailCache->mSendTime);
			}

			tpMailCache->mMoney = 0;
								
			// �ʼ��Ѿ��ı���Ҫ���´���
			MAIL_SETTYPE_NEEDSAVE( tpMailCache->mType, 1 )
			
			// �ı�һ�µ�ǰ���������ʼ�ID
			// ChangeActionMailID( vMailID );	
		}			
		
	}
	// ��ȡ������Ʒ
	else
	{
		int ItemID = tpMailCache->mItemObjID[ vItemIndex ];
		if ( ItemID == 0 )
		{
			return -1;
		}
		CItemObject *tpItemObj = ( CItemObject * )CSceneObjManager::GetSingletonPtr()->GetObject( ItemID );
		if ( tpItemObj == NULL )
		{
			return -1;
		}

		// �жϰ����Ƿ�����
		if ( !tpProperty->GetBaggage( )->Space( tpItemObj->GetItemID(), tpItemObj->GetItemNum() ) )
		{
			return ERR_MAIL_GETACCESSORY_NOPACKAGESPACE;
		}


		int64_t ullGUID = tpItemObj->GetGUID();
		int nItemNum = tpItemObj->GetItemNum();

		// �Ѹ�����Ʒ���뵽��Ұ�����
		if ( CPropertyModule::GetSingletonPtr( )->PlayerInsertItem( pPlayer, tpItemObj))
		{
			LogEventGetItemByRecvMail( pPlayer, ullGUID, tpItemObj->GetItemID(), nItemNum,
						tpMailCache->mSrcId, tpMailCache->mMailID,  tpMailCache->mSendTime);
		}
		else
		{
			LOG_ERROR( "mail", "Player(RoleID:%d) get item( ItemID:%d, ItemNum:%d ) accessory error !", pPlayer->GetCharID(),
					tpItemObj->GetItemID(), tpItemObj->GetItemNum() );
		}

		tpMailCache->mItemObjID[ vItemIndex ] = 0;	

		// �ʼ��Ѿ��ı���Ҫ���´���
		MAIL_SETTYPE_NEEDSAVE( tpMailCache->mType, 1 )

		// ���������ı�
		MAIL_SETTYPE_ACCECHAGED( tpMailCache->mType, 1 )
		--tpMailCache->mItemNum;		
	}

	// �ı�һ�µ�ǰ���������ʼ�ID
	// ChangeActionMailID( vMailID );
	
	if ( tpMailCache->mItemNum == 0 && tpMailCache->mMoney == 0 )
	{
		// û�и������ʼ�״̬��Ϊ��ͨ�ʼ�
		MAIL_SETTYPE_ACCESSORY( tpMailCache->mType, 0 )

		// �ʼ��Ѿ��ı���Ҫ���´���
		MAIL_SETTYPE_NEEDSAVE( tpMailCache->mType, 1 )
		
		// �ı䵽��ʱ��
		int tExpiredTime =	(time(NULL)+MAIL_TIME_COMMON);///DAY_TIME;
		tpMailCache->mExpiredTime = tExpiredTime>tpMailCache->mExpiredTime?tpMailCache->mExpiredTime:tExpiredTime; 
		
		// ��������Ż�����ϵͳ�ʼ�������û�����ĵ��ʼ��Ļ�����ɾ���ʼ�			
		if ( !MAIL_IS_HASBODY( tpMailCache->mType ) || MAIL_IS_BACKMAIL( tpMailCache->mLevel) || MAIL_IS_SYSTEM( tpMailCache->mLevel ) )
		{	
			// ��Ҫ�ӿͻ����б�����ɾ���ʼ�		
			DelMail( vMailID );
			return 2;
		}
	}	

	// �������µ����ݿ�
	UpdateMail( tpMailCache );	
	return 1;	  
}

// ***********************************************************
//  Function:		GetMailFromDB
//  Description:	�����ݿ��ȡ�ʼ�	
//  Input:			int count			��ȡ�ʼ�������
//  Input:			int LastMailID		�����ݿ��ȡ�����һ���ʼ���id
//  Input:			int ReceKind		��ȡ���ͣ� ��ȡ�ʼ��б��ǻ�ȡ���ʼ� ��
//  OutPut:							   
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::GetMailFromDB( int count, int LastMailID, int ReceKind ) 
{			
	CEntityPlayer *pPlayer = GetEntityPlayer();
	LK_ASSERT( pPlayer != NULL, return -1 );
	CMailDBOperate::GetMailFormDB( ReceKind , GetCharID(), count , LastMailID, pPlayer->GetNationality() );
	return 0;
}

// ***********************************************************
//  Function:		MailCacheClear
//  Description:	����ʼ�����	
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::MailCacheClear( )
{
	m_vMailCache.clear();
	return 0;
}

// ***********************************************************
//  Function:		SysSend
//  Description:	����ϵͳ�ʼ�	
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18			
// **********************************************************
int CMail::SysSend( const char *pDesName, int DesCharid, const char *pTitle, const char *pSrcName, const char *pBody, CItemObject ** tpItemObj,int ItemObjNum, int CountryID /* = 1 */, int nMoney /* = 0 */, int nCharID /* = 0 */ )
{		
	CMailCache *tpMailCache = ( CMailCache * )CSceneObjManager::GetSingletonPtr()->CreateObject( OBJTYPE_MAIL_MAILCACHE );
	if ( tpMailCache == NULL )
	{
		return -1;
	}
	
	// �����ʼ�״̬
	MAIL_SETLEVEL_SYSTEM( tpMailCache->mLevel );
	int ItemNum = 0;
	
	// ��ȡ������Ϣ
	if ( tpItemObj != NULL && ItemObjNum > 0 )
	{
		while ( tpItemObj[ItemNum] != NULL )
		{
			tpMailCache->mItemObjID[ItemNum] = tpItemObj[ItemNum]->get_id( );
			++ItemNum;
			if( ItemNum >= ItemObjNum )
			{
				break;
			}
		}
	} 
		
 	// �ж��Ƿ��и���
    if ( ItemNum >= 0 )
	{
		MAIL_SETTYPE_ACCESSORY( tpMailCache->mLevel,1 );
	}
	
	MAIL_SETLEVEL_MONEYNEED( tpMailCache->mLevel, false )
	
	MAIL_SETTYPE_NEW( tpMailCache->mType, true )
	
	// �����ʼ�ʱ��
	tpMailCache->mSendTime		= time( NULL );
	tpMailCache->mExpiredTime	= ( tpMailCache->mSendTime + MAIL_TIME_SYS );///DAY_TIME;
	
	tpMailCache->mMoney = nMoney;
	tpMailCache->mItemNum = ItemNum;
	
	// �ʼ�������
	if ( pSrcName != NULL )
	{
		strncpy( tpMailCache->mSrcName, pSrcName, NAME_LENGTH - 1 );
	}	
	
	// �ʼ�����
	if ( pTitle != NULL )
	{
		strncpy( tpMailCache->mMailTitle, pTitle, MAIL_TITLE_LEN-1 );
	}
	
	//// ����Է����߷��͸��Է����
	//bool IfNeedCallBack =  SendMailToPlayer( DesCharid, tpMailCache );
	
	// ���ʼ����浽���ݿ�
	SaveMail( tpMailCache, pBody, DesCharid, true, pDesName, CountryID, nCharID );	
	
	//// �����Ҳ����߻�������������ɾ���ʼ�
	//if ( IfNeedCallBack == false )
	//{
	//	CSceneObjManager::GetSingletonPtr()->DestroyObject( tpMailCache->get_id() );
	//}		
	return 0;
}

// ***********************************************************
//  Function:		DelMail	
//  Description:	ɾ���ʼ�
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::DelMail( int MailId )
{
	CEntityPlayer *pPlayer = GetEntityPlayer();
	LK_ASSERT( pPlayer != NULL, return  -1 );
	
	// ��ȡ�ʼ������б����Ƴ�
	CMailCache *tpMailCache = GetMailCacheByMailID( MailId  );
	if ( tpMailCache == NULL )
	{
		// ������ɾ��
		EraseMailCache( MailId  );

		return -1;
	}

	// ������ɾ��
	EraseMailCache( MailId  );

	if ( tpMailCache->mItemNum != 0  && tpMailCache->mMoney > 0 )
	{	
		// ������Ϊ�գ�����ɾ��
		return -1;
	}
	
	LogEventDeleteMail( GetCharID(), tpMailCache, m_nTotalMailCount );
	
	// ɾ���ʼ�����
    for ( int i = 0 ; i < MAIL_ITEM_COUNT_MAX; i++ )
    {
		if ( tpMailCache->mItemObjID[i] != 0 )
		{
			CSceneObjManager::GetSingletonPtr( )->DestroyObject( tpMailCache->mItemObjID[i] );
		}
    }
    CSceneObjManager::GetSingletonPtr( )->DestroyObject( tpMailCache->get_id( ) );
    	
    // �����ݿ���ɾ��     
    CMailDBOperate::MailDel( MailId,GetCharID(), pPlayer->GetNationality() );	 

	SetActionMailID( MailId );
           
    --m_nCurCacheMailCount;
    --m_nTotalMailCount;   	
    if ( m_nTotalMailCount >= MAIL_MAILBOX_MAXMAILNUM )
    {	
		// ��������п��еط��������ݿ��л����ʼ�(�ʼ��������������е��ʼ�)		
		GetMailFromDB( 1, GetMaxMailID(), FETCHMAIL_NEW );
    }    
	return 1;
}

// ***********************************************************
//  Function:		GetMailCacheByMailID
//  Description:	ͨ���ʼ�id��ȡ�ʼ�
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
CMailCache * CMail::GetMailCacheByMailID( int vMailID )
{
/*	_MAIL_CACHE_LIST_TYPE_::iterator it;
	for ( it=m_vMailCache.begin(); it != m_vMailCache.end() ; ++it  )
	{
		CMailCache *tpMailCache	 = ( CMailCache * )CSceneObjManager::GetSingletonPtr( )->GetObject( *it );	
		if ( tpMailCache == NULL )
		{
			continue;
		}
		if ( tpMailCache->mMailID == vMailID )
		{
			if ( IfRemoveFromCache == true )
			{
				m_vMailCache.erase( it );
			}
			return tpMailCache;
		}			
	}	
	return NULL;*/	

	_MAIL_CACHE_LIST_TYPE_::iterator it = m_vMailCache.find( vMailID );
	if( it != m_vMailCache.end() )
	{
		CMailCache *tpMailCache	 = ( CMailCache * )CSceneObjManager::GetSingletonPtr( )->GetObject( it->second );
		if ( tpMailCache == NULL )
		{
			LOG_ERROR( "mail", "[%s:%d] can't find mailcache obj by id %d", __FUNCTION__, __LINE__, it->second );
			return NULL;
		}

		return tpMailCache;
	}

	return NULL;
}


// ***********************************************************
//  Function:	 EraseMailCache	
//  Description: ���ʼ�������ɾ���ʼ�	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::EraseMailCache( int vMailID )
{
/*	_MAIL_CACHE_LIST_TYPE_::iterator it;
	for ( it=m_vMailCache.begin(); it != m_vMailCache.end() ; ++it  )
	{
		CMailCache *tpMailCache	 = ( CMailCache * )CSceneObjManager::GetSingletonPtr( )->GetObject( *it );	
		if ( tpMailCache == NULL )
		{
			continue;
		}
		if ( tpMailCache->mMailID == vMailID )
		{
			m_vMailCache.erase( it );
			return 1;
		}			
	}	
	return 0;	*/		

	_MAIL_CACHE_LIST_TYPE_::iterator it = m_vMailCache.find( vMailID );
	if( it != m_vMailCache.end() )
	{
		m_vMailCache.erase( it );
		return 1;
	}

	return 0;

}
//
//// ***********************************************************
////  Function:	GetMailCache	
////  Description: ��ȡ��������ʼ�	
////  Input:		
////  OutPut:			
////  Return:			
////  Others:
////  Date:			2009-02-18		
//// **********************************************************
//CMailCache * CMail::GetMailCache( int vIndex, int vMailID )
//{
//	if ( vIndex < 0  || vIndex >= m_nCurCacheMailCount )
//	{
//		return NULL;		
//	}
//	CMailCache *tpMail = ( CMailCache * )CSceneObjManager::GetSingletonPtr()->GetObject( m_vMailCache[ vIndex ] );
//	if ( tpMail == NULL )
//	{
//		return NULL;
//	}
//	if ( tpMail->mMailID != vMailID )
//	{
//		return NULL;
//	}
//	return tpMail;  
//}


// ***********************************************************
//  Function:	ClearItemList	
//  Description: ��ո����б�	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
void CMail::ClearItemList( )
{		
	CEntityPlayer *pPlayer = GetEntityPlayer();
	if( pPlayer == NULL )
	{
		return;
	}
	CPropertyPlayer* tpProperty = ( CPropertyPlayer* )pPlayer->GetProperty( );	
	CItemObject *tpItemObj = NULL;		
	CMessage				HeadMessage;
	CMessageLockItemNotice  LockItemNotice;
	for ( int i=0; i<MAIL_ITEM_COUNT_MAX; i++ )
	{	
		if (  m_nList[i].ItemNum == 0  )
		{
			continue;
		}
				
		tpItemObj = tpProperty->GetBaggage( )->GetItemObjPtr( m_nList[i].ItemIndex );
		
		if ( tpItemObj == NULL )
		{
			m_nList[i].ItemNum   = 0;			
			continue;
		}
		
		if ( tpItemObj->GetLockStatus() == LOCKTYPE_MAIL )
		{
			tpProperty->GetBaggage( )->Lock( m_nList[i].ItemIndex ,LOCKTYPE_NONE );	
			HeadMessage.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_LOCKITEM );
			HeadMessage.set_msgpara( (int )&LockItemNotice );
			LockItemNotice.set_index(  m_nList[i].ItemIndex );
			LockItemNotice.set_locked( LOCKTYPE_NONE );
			CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &HeadMessage ); 			
		}		
		m_nList[i].ItemNum   = 0;
	}
	return ;
}

// ***********************************************************
//  Function:	SetMaxMailID	
//  Description: ���ÿͻ�����ʾ���ʼ�ID�����ֵ	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-04-21
// **********************************************************
int CMail::SetMaxMailID( int vMailID )
{  
	if( vMailID > m_nLastMailID )
	{	
		m_nLastMailID = vMailID;	 
		return 1;	
	}

	return 0;
} 

// ***********************************************************
//  Function:	SetMaxMailID	
//  Description: ���ÿͻ�����ʾ���ʼ�ID�����ֵ	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-04-21
// **********************************************************
int CMail::GetMaxMailID(  )
{
	//if ( m_nMailIDFetched == m_nLastMailID  )
	//{
	//	++m_nMailFetcheCount;
	//	return 	m_nMailIDFetched + m_nMailFetcheCount;	
	//}
	//m_nMailIDFetched = m_nLastMailID;
	//m_nMailFetcheCount = 0;
	return m_nLastMailID;
}

// ***********************************************************
//  Function:	ClearItemList	
//  Description: ��ո����б�	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
CEntityPlayer* CMail::GetEntityPlayer()
{
	CEntityPlayer *pPlayer = ( CEntityPlayer * )CSceneLogic::GetSingleton().GetEntity( m_nEntityID );
	return pPlayer;
}

// ***********************************************************
//  Function:		CreatNewMail
//  Description:	�ø����б������ʼ�
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
CMailCache * CMail::CreatNewMail( int vMoney, int MoneyNeedPayBack, const char *pMailTitle , int nDesCharID, const char* pDesName)
{
	CMailCache *tpMailCache =(CMailCache *)CSceneObjManager::GetSingletonPtr( )->CreateObject( OBJTYPE_MAIL_MAILCACHE );
	LK_ASSERT( tpMailCache != NULL, return NULL );
	CEntityPlayer *pPlayer = GetEntityPlayer();	
	LK_ASSERT( pPlayer != NULL, return NULL );
	CPropertyPlayer *tpProperty =( CPropertyPlayer *) pPlayer->GetProperty( );	
   
	// ������
	strncpy( tpMailCache->mSrcName , pPlayer->GetCharName(), NAME_LENGTH-1 );
	tpMailCache->mSrcName[ NAME_LENGTH-1 ] = '\0' ; 
	
	//������id
	tpMailCache->mSrcId = GetCharID();
	 
	// ����
	strncpy( tpMailCache->mMailTitle , pMailTitle , MAIL_TITLE_LEN - 1 );
	tpMailCache->mMailTitle[ MAIL_TITLE_LEN - 1 ] = '\0';	
			
	// ��ʼ����������
	tpMailCache->mItemNum = 0;
	for( int i = 0 ; i < MAIL_ITEM_COUNT_MAX ; i++ )
	{
		if( m_nList[i].ItemNum > 0 )
		{
			CItemObject *tpObject = ( CItemObject * )tpProperty->GetBaggage( )->GetItemObjPtr( m_nList[i].ItemIndex );
			if ( tpObject == NULL )
			{
				// error : �������ø�����û����Ʒ
				LOG_ERROR( "mail","[%s,%d][%s] There is no item in index:%d of player:%d ",
					__LK_FILE__,__LINE__,__FUNCTION__, m_nList[i].ItemIndex, pPlayer->GetCharID() );
				continue;
			}
			if ( (int)tpObject->GetItemNum() < m_nList[ i ].ItemNum )
			{
				// error : ��������������û����ô�����Ʒ
				LOG_ERROR( "mail","[%s,%d][%s] There is not enough item in index:%d of player:%d ",
					__LK_FILE__,__LINE__,__FUNCTION__, m_nList[i].ItemIndex, pPlayer->GetCharID() );
				 continue;
			}
			tpObject = tpProperty->GetBaggage( )->EraseItem( m_nList[i].ItemIndex, m_nList[i].ItemNum );			
			if ( tpObject == NULL )
			{
				continue;
			}

			// ��¼���븽����־
			LogEventLostItemBySendMail(pPlayer, tpObject->GetGUID(), tpObject->GetItemID(), m_nList[i].ItemNum, 
					nDesCharID, tpMailCache->get_id());


			CPropertyModule::GetSingletonPtr()->SendRemoveItemNotice( pPlayer, POS_BAGGAGE, m_nList[i].ItemIndex, m_nList[i].ItemNum );
			tpMailCache->mItemObjID[i] = tpObject->get_id();
									
			++tpMailCache->mItemNum;
		}
	}		

	//if( tpMailCache->mItemNum <= 0 && MoneyNeedPayBack > 0 )
	//{
	//	// error : û�з�����Ʒȴ��Ҫ�Է�֧����Ǯ
	//	// return NULL;
	//}
	
	// Я���Ľ�Ǯ
	tpMailCache->mMoney            = vMoney;
	// ��Ҫ֧���Ľ�Ǯ
	tpMailCache->mMoneyNeedPayBack = MoneyNeedPayBack;
	
	// �����ʼ������״̬
	MAIL_SETLEVEL_USER( tpMailCache->mLevel );
	
	// �����ʼ���״̬							  
	tpMailCache->mSendTime    = time( NULL );
	if ( MoneyNeedPayBack > 0 )
	{
		MAIL_SETLEVEL_MONEYNEED( tpMailCache->mLevel , 1 );		
	    tpMailCache->mExpiredTime = ( tpMailCache->mSendTime + MAIL_TIME_MONEYNEED );// /DAY_TIME; 
		tpMailCache->mMailTimer   = CWTimer( MAIL_TIME_MONEYNEED );
	}
	else
	{
		if ( tpMailCache->mItemNum > 0 || vMoney > 0 )
		{			
			MAIL_SETTYPE_ACCESSORY( tpMailCache->mType , 1 );
			tpMailCache->mExpiredTime = ( tpMailCache->mSendTime + MAIL_TIME_PACKAGE ); // /DAY_TIME;
		}
		else
		{		
			tpMailCache->mExpiredTime = ( tpMailCache->mSendTime + MAIL_TIME_COMMON );// /DAY_TIME;
		}
	} 
	
	// ����Ϊ���ʼ�
	MAIL_SETTYPE_NEW( tpMailCache->mType , 1 );
	return tpMailCache;	
}

// ***********************************************************
//  Function:		SaveMail
//  Description:	�ѷ��͵��ʼ����뵽���ݿ���
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
void CMail::SaveMail( CMailCache * tpMail , const char * pMailBody, int DesCharID /* = 0 */, bool IfNeedCallBack /* = false */, const char *pDesname /* = NULL */, int CountryID /* = 1 */, int nCharID /* = 0 */ )
{	
	MailItemBox  PbAccesoryBox;
	int          ItemNum = 0;
	char         AccesoryBuf[MAIL_EXTDATE_LEN];	
    if ( tpMail == NULL )
    {			
		return;
    }
	m_sMailInfo.ClearMailInfor( );
	
	// �����ʼ�������Ϣ��������Ϣ	
	m_sMailInfo.mMailBase.mMailID    	= tpMail->mMailID;	
	m_sMailInfo.mMailBase.mSrc			= tpMail->mSrcName;
	m_sMailInfo.mMailBase.mTitle		= tpMail->mMailTitle;
	m_sMailInfo.mMailBase.mSendTime		= tpMail->mSendTime;
	m_sMailInfo.mMailBase.mExpiredTime  = tpMail->mExpiredTime;
	m_sMailInfo.mMailBase.mLevel        = tpMail->mLevel;
	m_sMailInfo.mMailBase.mType         = tpMail->mType ;	
	m_sMailInfo.mMailBase.mSrcId		= tpMail->mSrcId;
	m_sMailInfo.mMailBase.mItemNum		= tpMail->mItemNum;	
	m_sMailInfo.mMailBase.mDesName		= pDesname;
	
	// ��ȡ�ʼ�����
	m_sMailInfo.mBody					= pMailBody;
	
	// ��ȡ������Ϣ
	for ( int i=0 ; i< MAIL_ITEM_COUNT_MAX ; i++ )
	{
		if (  tpMail->mItemObjID[i] == 0 )
		{
			continue;
		}
		CItemObject *tpObj = ( CItemObject * )CSceneObjManager::GetSingletonPtr( )->GetObject( tpMail->mItemObjID[i] );
		if ( tpObj == NULL )
		{
		  // error		  
		   continue;
		}		

	    PBItemObject *tPbitem = PbAccesoryBox.add_mailitem( );
		tpObj->GetItemBinaryBuffer2( tPbitem , tpObj->GetItemNum( ) );
		PbAccesoryBox.add_itemindex( i );		
		// ɾ����Ʒ��Ϣ( ���յ����ݿⷵ����Ϣ����ɾ�� )
		//CSceneObjManager::GetSingletonPtr()->DestroyObject( tpMail->mItemObjID[i] );	
		//tpMail->mItemObjID[i] = 0;
		ItemNum++;
	}	
	
	// ��ȡ��Ǯ��Ϣ
	m_sMailInfo.mMoneySend         = tpMail->mMoney;
	m_sMailInfo.mMoneyNeedBack     = tpMail->mMoneyNeedPayBack;

	// ���л�������Ϣ	
	bool Ret = PbAccesoryBox.SerializeToArray( AccesoryBuf, MAIL_EXTDATE_LEN );
	if( Ret ==  false )
	{
		// ���л�ʧ��
		LOG_ERROR( "mail","[%s,%d][%s] Accessory SerializeToArray Error!  ",__LK_FILE__,__LINE__,__FUNCTION__ );
		return;
	}	
	int Byesize = PbAccesoryBox.ByteSize();
	
	// ���˸������л�buff�е�ת���ַ� 
	char *DesBuf = m_sMailInfo.mExtDate;
	int CapRet = EscapeDataString( &DesBuf, MAIL_EXTDATE_LEN , AccesoryBuf , Byesize );
    if ( CapRet ==-1 )
    { 		
		LOG_ERROR( "mail","[%s,%d][%s] EscapeDataString Error!  ",__LK_FILE__,__LINE__,__FUNCTION__ );
		return;
    }
        
	// ���ʼ��������ݿ���
  	CMailDBOperate::MailSend( DesCharID , tpMail->get_id( ), &m_sMailInfo, IfNeedCallBack, CountryID, nCharID );
 }

// ***********************************************************
//  Function:		InsertMail
//  Description:	���ʼ������в���һ�����ʼ���InsertPos = 0 ��ʾ�������ͷ������������β��
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int  CMail::InsertMail( CMailCache *tpMailCache, int IfNewMail )
{	 	
	if ( tpMailCache == NULL )
	{		
		return -1;
	}
	
	if ( IfNewMail == 1 )
	{
		// �ʼ�������1
		++m_nTotalMailCount ;	
	}
	
	// �ͻ����ܹ���ʾ���ʼ��������������ܲ���
	if ( m_nCurCacheMailCount >= MAIL_MAILBOX_MAXMAILNUM )
	{			
		return -1;
	}	
	if ( m_nTotalMailCount > MAIL_MAILBOX_MAXMAILNUM && IfNewMail == 1 )
	{
		return -1;
	}
	
	// ���ڲ������ʼ���Ϣ���ȵ�������ʱ�ٷ���
	if ( m_nLeftPageMailNum != -1  )
	{
		++m_nLeftPageMailNum;
		return 0;
	}
	   	
	// �ѻ�ȡ���ʼ��ŵ��ʼ��б��ͷ��	
	_MAIL_CACHE_LIST_TYPE_::_Pairib tInsertRet = m_vMailCache.insert( std::pair<int,int>(tpMailCache->mMailID, tpMailCache->get_id()) );
	if( tInsertRet.second == true )
	{
		++m_nCurCacheMailCount;	

		SetMaxMailID( tpMailCache->mMailID );

		return 1;
	}
	else
	{
		LOG_ERROR( "mail", "[%s:%d] insert mail %d failed, cache mailnum:%d, total mailnum:%d ", __FUNCTION__, __LINE__,
			 tpMailCache->mMailID, m_nCurCacheMailCount, m_nTotalMailCount );
		if ( IfNewMail == 1 )
		{
			// �ʼ�������1
			--m_nTotalMailCount ;	
		}
		return -1;
	}	
}

// ***********************************************************
//  Function:	 ReceiverRouterMail	
//  Description: ���������������������ʼ�	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		 2009-03-20		
// **********************************************************
int CMail::ReceiveRouterMail( CMessageNewMailNotify *tpMsg )
{	
	LK_ASSERT( tpMsg != NULL, return -1 );	
	if ( !tpMsg->has_maillist() )
	{						  
		return -1;			
	}
	
	// ����ͻ��������Ѿ������򲻷������ʼ�֪ͨ
	if( m_nCurCacheMailCount >= MAIL_MAILBOX_MAXMAILNUM )
	{
		tpMsg->set_haslist( 0 );
		++m_nTotalMailCount;
		return -1;
	}
	if ( m_nLeftPageMailNum != -1 )
	{
		++m_nLeftPageMailNum;
		tpMsg->set_haslist( 0 );
		return 1;
	}
	CMailCache *tpMailCache = ( CMailCache * )CSceneObjManager::GetSingleton().CreateObject( OBJTYPE_MAIL_MAILCACHE );
	LK_ASSERT( tpMailCache != NULL, return  -1 );
	tpMailCache->mSrcId		  = tpMsg->router().srccharid();
	tpMailCache->mMailID	  =	tpMsg->maillist().mailid();	
	tpMailCache->mExpiredTime = tpMsg->maillist().expiredtime()*DAY_TIME;
	tpMailCache->mSendTime    = tpMsg->maillist().sendtime();
	tpMailCache->mType		  = tpMsg->maillist().mailtype();
	tpMailCache->mLevel		  = tpMsg->maillist().maillevel();
	tpMailCache->mMoney		  = tpMsg->maillist().money();
	tpMailCache->mMoneyNeedPayBack	= tpMsg->maillist().moneyneedback();
	if ( tpMsg->maillist().has_srcname() )
	{
		strncpy( tpMailCache->mSrcName, tpMsg->maillist().srcname().c_str(), NAME_LENGTH-1 );
		tpMailCache->mSrcName[NAME_LENGTH-1] = '\0';
	}
	if ( tpMsg->maillist().has_title() )
	{
		strncpy( tpMailCache->mMailTitle, tpMsg->maillist().title().c_str(), MAIL_TITLE_LEN -1 );
		tpMailCache->mMailTitle[MAIL_TITLE_LEN-1] = '\0';
	}
	tpMsg->set_haslist( 1 );

	int nInsertRet = InsertMail( tpMailCache, 1 );
	if( nInsertRet != 1 )
	{
		CSceneObjManager::GetSingletonPtr()->DestroyObject( tpMailCache->get_id() );
		return -1;
	}

	return 1;

}

// ***********************************************************
//  Function:	 UpdateMail	
//  Description: �����ʼ���Ϣ�����ݿ���	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::UpdateMail(  CMailCache *tpMailCache )
{
	if (  tpMailCache == NULL )
	{
		return -1;
	}
	if ( MAIL_IS_NEEDSAVE( tpMailCache->mType ) )
	{
		MAIL_SETTYPE_NEEDSAVE( tpMailCache->mType, 0 )
		if ( MAIL_IS_ACCECHAG( tpMailCache->mType ) )
		{
			MAIL_SETTYPE_ACCECHAGED( tpMailCache->mType, 0 )
			UpdateAccesory( tpMailCache );
		}
		else
		{
			UpdateMailStatus( tpMailCache );	
		}				
	}	
	return 1;
}


// ***********************************************************
//  Function:	 UpdateAccesory	
//  Description: ���¸�����Ϣ�����ݿ���	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::UpdateAccesory( CMailCache *tpMail )
{					
	CEntityPlayer *pPlayer = GetEntityPlayer() ;
	LK_ASSERT( tpMail != NULL, return -1 );
	MailItemBox  PbAccesoryBox;
	int          ItemNum = 0;
	char         AccesoryBuf[MAIL_EXTDATE_LEN];		
	m_sMailInfo.ClearMailInfor();
	
	// ��ȡ������Ϣ
	for ( int i=0 ; i< MAIL_ITEM_COUNT_MAX ; i++ )
	{
		if ( tpMail->mItemObjID[i] == 0 )
		{
			continue;
		}
		CItemObject *tpObj = ( CItemObject * )CSceneObjManager::GetSingletonPtr()->GetObject( tpMail->mItemObjID[i] );
		if ( tpObj == NULL )
		{
			// error		  
			continue;
		}		
		PbAccesoryBox.add_mailitem();
		PBItemObject *tPbitem = PbAccesoryBox.mutable_mailitem( ItemNum );
		PbAccesoryBox.add_itemindex( i );
		tpObj->GetItemBinaryBuffer2( tPbitem , tpObj->GetItemNum() ); 		
		ItemNum++;
	}	
	
	// �ʼ�״̬
	m_sMailInfo.mMailBase.mLevel		= tpMail->mLevel;
	m_sMailInfo.mMailBase.mExpiredTime	= tpMail->mExpiredTime;
	m_sMailInfo.mMailBase.mType			= tpMail->mType;
	m_sMailInfo.mMoneyNeedBack			= tpMail->mMoneyNeedPayBack;
	m_sMailInfo.mMoneySend				= tpMail->mMoney;
	m_sMailInfo.mMailBase.mItemNum      = ItemNum;
	
	// ���л�������Ϣ	
	bool Ret = PbAccesoryBox.SerializeToArray( AccesoryBuf, MAIL_EXTDATE_LEN );
	if( Ret ==  false )
	{
		// ���л�ʧ��
		//return;
		LOG_ERROR( "mail","[%s,%d][%s] SerializeToArray Error!",__LK_FILE__,__LINE__,__FUNCTION__ );
		return -1;
	}
	int Byesize = PbAccesoryBox.ByteSize( );

	// ���˸������л�buff�е�ת���ַ� 
	char *DesBuf = m_sMailInfo.mExtDate;
	EscapeDataString( &DesBuf, MAIL_EXTDATE_LEN , AccesoryBuf , Byesize );

	// ���ʼ����µ����ݿ���			
	CMailDBOperate::UpMailAccessory( tpMail->mMailID, &m_sMailInfo,GetCharID(), pPlayer->GetNationality() );
	return 0;
}


// ***********************************************************
//  Function:		UpdateMailStatus	
//  Description:	�����ʼ��Ľ�Ǯ��Ϣ��״̬��Ϣ�����ݿ���
//  Input:			CMailCache *tpMail		�����µ��ʼ�
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::UpdateMailStatus( CMailCache *tpMail )
{
	CEntityPlayer *pPlayer = GetEntityPlayer();
	if ( tpMail == NULL )
	{
		return -1;
	}	

	// �ʼ�״̬
	m_sMailInfo.mMailBase.mLevel		= tpMail->mLevel;
	m_sMailInfo.mMailBase.mExpiredTime	= tpMail->mExpiredTime;
	m_sMailInfo.mMailBase.mType			= tpMail->mType;
	m_sMailInfo.mMoneyNeedBack			= tpMail->mMoneyNeedPayBack;
	m_sMailInfo.mMoneySend				= tpMail->mMoney;
	CMailDBOperate::UpMailStatus( tpMail->mMailID, &m_sMailInfo, GetCharID(), pPlayer->GetNationality() );
	return 0;
}

// ***********************************************************
//  Function:		BackMail				
//  Description:	����
//  Input:			int vMailID				 �ʼ�ID
//  Input:			const char *pMailBody	 �ʼ�����
//  OutPut:			
//  Return:			1 ��ʾ���ųɹ� �����ʾ����ʧ��
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::BackMail(  int vMailID, const char *pMailBody )
{ 
	CEntityPlayer *pPlayer = GetEntityPlayer();
	if ( pPlayer == NULL )
	{
		return -1;
	}	

	// ��ȡ�ʼ�
	CMailCache *tpMailCache = GetMailCacheByMailID( vMailID );
	if ( tpMailCache == NULL )
	{	
		// error
		return -1;
	}  
		
	// ���ı���������
	if ( tpMailCache->mItemNum == 0  && tpMailCache->mMoney <= 0 )
	{
		// ���ı���������
		return ERR_MAIL_BACKMAIL_TEXT;
	}
		
	// ���˻ص��ʼ������ٴ�����
	if ( MAIL_IS_BACKMAIL( tpMailCache->mLevel ) )
	{
		return ERR_MAIL_BACKMAIL_BACKED;
	}
	
	// ϵͳ�ʼ���������
	if ( MAIL_IS_SYSTEM( tpMailCache->mLevel ) )
	{
		return -1;
	}
	
	// ���ʲ�����������
	CPropertyPlayer *tpProperty = ( CPropertyPlayer  *)pPlayer->GetProperty();
	if ( MAIL_SEND_MONEY_PRO > tpProperty->GetBindMoney() + tpProperty->GetMoney() )
	{
		return  ERR_MAIL_SENDMAIL_MONEYNOTENOUGH;  
	}
	int tBindMoney = MAIL_SEND_MONEY_PRO > tpProperty->GetBindMoney()? tpProperty->GetBindMoney():MAIL_SEND_MONEY_PRO;
	int tMoney	   = MAIL_SEND_MONEY_PRO - tBindMoney;
		
	// ���ʼ��б���ɾ��
	EraseMailCache( vMailID );
			   	
	// ɾ�����ݿ��е��ż�
	CMailDBOperate::MailDel( vMailID, GetCharID(), pPlayer->GetNationality() );
	
	// ���ԭ����״̬
	tpMailCache->mType  = 0;
	tpMailCache->mLevel = 0;
	
	// �����ʼ�����Ϊ�û�����
	MAIL_SETLEVEL_BACKMAIL( tpMailCache->mLevel, 1 );
	MAIL_SETLEVEL_USER( tpMailCache->mLevel );	
	MAIL_SETTYPE_NEW( tpMailCache->mType, 1 )
	
	
	tpMailCache->mMoneyNeedPayBack = 0;
	MAIL_SETLEVEL_MONEYNEED( tpMailCache->mLevel, false )
	
	// �������ŵķ��ͷ�	 	
	int DestCharID = tpMailCache->mSrcId;
	tpMailCache->mSrcId = pPlayer->GetCharID();
	const char *pSrcName = pPlayer->GetCharName( ); 	
	char DesName[ NAME_LENGTH ];
	
	// �����ʼ����շ�����
	memset( DesName, 0, sizeof( DesName ) );
	strncpy( DesName, tpMailCache->mSrcName, NAME_LENGTH -1 );
	
	// �����ʼ����ͷ�����
	memset( tpMailCache->mSrcName, 0 , sizeof( tpMailCache->mSrcName ) );	
	strncpy( tpMailCache->mSrcName, pSrcName, sizeof( tpMailCache->mSrcName ) - 1 );
	
	// ��������ʱ����ʼ�����
	tpMailCache->mSendTime		= time( NULL );
	tpMailCache->mExpiredTime	= ( tpMailCache->mSendTime + MAIL_TIME_PACKAGE );// /DAY_TIME;	   
	
	//  ����Է����ߵĻ��򷢸��Է�	
	/*bool IfNeedCallBack = SendMailToPlayer( DestCharID, tpMailCache );		*/
		
	// �����ʼ������ݿ�
	SaveMail( tpMailCache, pMailBody, DestCharID, true, DesName, pPlayer->GetNationality() );
	
	//// �����������ɾ���ʼ�
	//if (  IfNeedCallBack == false )
	//{
	//	CSceneObjManager::GetSingletonPtr()->DestroyObject( tpMailCache->get_id() );
	//}
	//
	// �۳���������
	if (CPropertyModule::GetSingletonPtr( )->PlayerChangeMoney( pPlayer, tBindMoney, true, true ) == SUCCESS)
	{
		LogEventLostMoneyByPostalFee(pPlayer, 
				CYuanBao::em_bind_money, tBindMoney, DestCharID, tpMailCache->get_id() );
	}

	if(CPropertyModule::GetSingletonPtr( )->PlayerChangeMoney( pPlayer, tMoney, true, false ) == SUCCESS)
	{
		LogEventLostMoneyBySendMail(pPlayer, 
				CYuanBao::em_unbind_money, tMoney, DestCharID, tpMailCache->get_id() );
	}
	
	// �ı��Լ����ʼ�����
	--m_nCurCacheMailCount;
	--m_nTotalMailCount;
	
	// ����������ʼ������ݿ��еĻ�����ȡ��
	if ( m_nTotalMailCount >= MAIL_MAILBOX_MAXMAILNUM  )
	{	
		// ��������п��еط��������ݿ��л����ʼ�(�ʼ��������������е��ʼ�)		
		GetMailFromDB( 1, GetMaxMailID(), FETCHMAIL_NEW );
	}    
	return 1;
}

// ***********************************************************
//  Function:	 GetMAilListInfo	
//  Description: ��ȡ�ʼ��б�	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		 2009-02-18		
// **********************************************************
int CMail::GetMAilListInfo( CMessageMailListNotify &pMessage )
{	
	_MAIL_CACHE_LIST_TYPE_::iterator it;
	CMailCache *tpMailCache = NULL ;
	CMailInfo *MailInfo = NULL;
	int MailNum = 0;
	for ( it = m_vMailCache.begin( ); it != m_vMailCache.end( ); it++ )
	{
		tpMailCache = ( CMailCache * )CSceneObjManager::GetSingletonPtr( )->GetObject( it->second );
		if ( tpMailCache == NULL )
		{	
			LOG_ERROR( "mail","[%s,%d][%s] Can't get CMailCache Object",__LK_FILE__,__LINE__,__FUNCTION__ );
			return -1;
		}
		if ( tpMailCache->mMailID == 0 )
		{
			LOG_ERROR( "mail","[%s,%d][%s] CMailCache Obj %d dosn't have mailid",
				__LK_FILE__,__LINE__,__FUNCTION__ , tpMailCache->get_id() );
			continue;
		}
		pMessage.add_maillist( );
		MailInfo = pMessage.mutable_maillist( MailNum );	
		MailInfo->set_title( tpMailCache->mMailTitle );
		MailInfo->set_sendtime( tpMailCache->mSendTime );
		MailInfo->set_maillevel( tpMailCache->mLevel );
		MailInfo->set_srcname( tpMailCache->mSrcName );
		MailInfo->set_money( tpMailCache->mMoney );
		MailInfo->set_itemnum( tpMailCache->mItemNum );
		MailInfo->set_mailid( tpMailCache->mMailID );
		MailInfo->set_mailtype( tpMailCache->mType );
		MailInfo->set_expiredtime( tpMailCache->mExpiredTime/DAY_TIME );
		MailInfo->set_moneyneedback( tpMailCache->mMoneyNeedPayBack );
		MailNum ++;
	}
	return 1;	
}

// ***********************************************************
//  Function:		DestroyMailCache
//  Description:	�����ʼ�����
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
void CMail::DestroyMailCache( )
{
    _MAIL_CACHE_LIST_TYPE_ ::iterator it;
    CMailCache *tpCache = NULL;
	for ( it = m_vMailCache.begin() ; it != m_vMailCache.end(); )
	{
		tpCache = ( CMailCache * )CSceneObjManager::GetSingletonPtr( )->GetObject( it->second );
		if ( tpCache == NULL )
		{
			// error
			LOG_ERROR( "mail","[%s,%d][%s] Empty MailCache! ",__LK_FILE__,__LINE__,__FUNCTION__  );
			m_vMailCache.erase( it++ );
			continue;
		}

		UpdateMail( tpCache );

		for ( int i = 0; i < MAIL_ITEM_COUNT_MAX ; i++ )
		{
			if ( tpCache->mItemObjID[ i ] != 0 )
			{
				CSceneObjManager::GetSingletonPtr( )->DestroyObject( tpCache->mItemObjID[ i ] );
			}	
		}

		CSceneObjManager::GetSingletonPtr( )->DestroyObject( tpCache->get_id() );	

		m_vMailCache.erase( it++ );
	}
}

// ***********************************************************
//  Function:	 DestroyMailAccessory	
//  Description: �����ʼ�������Ʒ	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::DestroyMailAccessory( CMailCache *tpMailCache )
{
	if ( tpMailCache == NULL )
	{
		return -1;
	}
	for ( int i  = 0; i < MAIL_ITEM_COUNT_MAX; ++i  )
	{
		if ( tpMailCache->mItemObjID[i] == 0 )
		{	
			continue;
		}
		CSceneObjManager::GetSingletonPtr()->DestroyObject( tpMailCache->mItemObjID[i] );	
	}
	return 0;
}

// ***********************************************************
//  Function:		SetActionMailID
//  Description:	��ȡ�ʼ�����ϸ��Ϣ
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
void CMail::SetActionMailID( int MailID )
{
/*	if ( m_nActionMailID <= 0 )
	{
		m_nActionMailID = MailID;
		return;
	}
	if ( m_nActionMailID != MailID )
	{		
		UpdateMailInfo( m_nActionMailID );
		m_nActionMailID = MailID;
	}	*/	

	m_nActionMailID = MailID;

}

// ***********************************************************
//  Function:		SendMsgMailBoxStatus
//  Description:	������������״̬(��¼֮��ͻᷢ��)
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-04-15		
// **********************************************************
void CMail::SendMsgMailBoxStatus( int MailCount, int NewMailCount )
{
	CEntityPlayer *pPlayer = GetEntityPlayer( );
	LK_ASSERT( pPlayer != NULL, return );
	CMessage MsgHead;
	CMessageMailBoxStatusNotify MsgMailBoxStatus;	
	MsgMailBoxStatus.set_newmailcount( NewMailCount );
	MsgMailBoxStatus.set_mailcount( MailCount>MAIL_MAILBOX_MAXMAILNUM?MAIL_MAILBOX_MAXMAILNUM:MailCount );
	MsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_MAILBOXSTATUS );
	MsgHead.set_msgpara( (int)&MsgMailBoxStatus );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead );
}

// ***********************************************************
//  Function:		GetMailDetailInfo
//  Description:	��ȡ�ʼ�����ϸ��Ϣ
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::GetMailDetailInfo( int vMailID, CMessageMailReadResponse &MsgMailRead )
{
	CMailCache *tpMailCache = GetMailCacheByMailID( vMailID );
	LK_ASSERT( tpMailCache != NULL, return -1 );
	MsgMailRead.set_mailid( vMailID );
	
	// ״̬����Ϊ�Ѷ�
	if ( MAIL_IS_NEW( tpMailCache->mType ) )
	{
		MAIL_SETTYPE_NEW( tpMailCache->mType, 0 )
		MAIL_SETTYPE_NEEDSAVE( tpMailCache->mType, 1 )
	}	
	CItemObject *tpItemObj = NULL;
	int Index = 0;
	for ( int i = 0; i < tpMailCache->mItemNum; i++ )
	{
		if ( tpMailCache->mItemObjID[ i ] == 0 )
		{
			continue;
		}
		tpItemObj = ( CItemObject * )CSceneObjManager::GetSingletonPtr( )->GetObject( tpMailCache->mItemObjID[ i ] );
		if ( tpItemObj == NULL )
		{
			continue;
		}
		MsgMailRead.add_accessory( );
		tpItemObj->GetItemBinaryBuffer2( MsgMailRead.mutable_accessory( Index ) );				
		++Index;
	}
	
	// �ı�һ�±��������ʼ�ID
	// ChangeActionMailID( vMailID );
	UpdateMail( tpMailCache );
	return 1;
}

// ***********************************************************
//  Function:		UpdateMailInfo
//  Description:	�����ʼ���Ϣ�����ݿ�
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::UpdateMailInfo( int MailID )
{
	CMailCache *tpMailCache = GetMailCacheByMailID( MailID );
	if ( tpMailCache == NULL )
	{
		return -1;
	}
	return UpdateMail( tpMailCache );
}

// ***********************************************************
//  Function:	 GetMailPage	
//  Description: ��ȡһҳ�ʼ���Ϣ	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::GetMailPage(  )
{
	if ( m_nMailBoxStatus == MAIL_STATUS_INITIALIZE )
	{
		// ���ʹ�����ʾ
		return -1;
	}
	
	// �ʼ��Ѿ�ȡ����
	if ( m_nLeftPageMailNum == -1  )
	{
		// ���ʹ�����ʾ
		return -1;
	}
	if ( m_nLeftPageMailNum > MAIL_MAX_PAGENUM )
	{
		GetMailFromDB( MAIL_MAX_PAGENUM, m_nLastPageMailID, FETCHMAIL_PAGE );
		m_nLeftPageMailNum -= MAIL_MAX_PAGENUM;
		return 1;
	}	
	GetMailFromDB( m_nLeftPageMailNum, m_nLastPageMailID, FETCHMAIL_PAGE );
	m_nLeftPageMailNum = -1;	
	return 1;
}

// ***********************************************************
//  Function:	 LockMail	
//  Description: ���ʼ�����	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::LockMail( int MailId )
{
	CMailCache *tpMailCache = GetMailCacheByMailID( MailId );
	if ( tpMailCache == NULL )
	{
		return -1;
	}
	/*
	TODO: �ж��Ƿ����Ѿ����ѵĸ����ʼ�
	*/
	if ( m_nLockMailNum >= MAIL_LOCKNUM_MAX )
	{
		return -2;
	}

	MAIL_SETTYPE_LOCK( tpMailCache->mType, 1  )
	MAIL_SETTYPE_NEEDSAVE( tpMailCache->mType, 1 )
	MAIL_SETTYPE_ACCECHAGED( tpMailCache->mType, 0 )
	++m_nLockMailNum;
	return 1;
}

// ***********************************************************
//  Function:	 UnLockMail	
//  Description: ���ʼ�����	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
int CMail::UnLockMail( int MailId )
{
	CMailCache *tpMailCache = GetMailCacheByMailID( MailId );
	if ( tpMailCache == NULL )
	{
		// error
		return -1;		
	}
	if ( !MAIL_IS_LOCK( tpMailCache->mType ) )
	{	
		// error
		return -1;			
	}
	MAIL_SETTYPE_LOCK( tpMailCache->mType, 0 )
	MAIL_SETTYPE_NEEDSAVE( tpMailCache->mType, 1 )
	MAIL_SETTYPE_ACCECHAGED( tpMailCache->mType, 0 )
	--m_nLockMailNum;
	return 1;
}

// ***********************************************************
//  Function:		GetMailCountCallBack
//  Description:	�����ݿ��ȡ�ʼ������Ļص�����
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-02-18		
// **********************************************************
void CMail::GetMailCountCallBack( int CharID, int MailCount )
{
	CEntityPlayer *pPlayer = ( CEntityPlayer * )CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID( CharID );
	if ( pPlayer == NULL )
	{
		// ��������������
		return;
	}
	CMail *tpMail = CMailManager::GetSingletonPtr()->GetMail( pPlayer );
	if ( tpMail == NULL )
	{
		// ����
		LOG_ERROR( "mail","[%s,%d][%s] Get CMail Error! ", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}
	if ( MailCount < 0 )
	{
		MailCount = 0;		
	}
	
	// �ʼ�����
	tpMail->m_nTotalMailCount  =  MailCount;  	
	
	// ��δ�����ݿ�ȡ�����ʼ�����
	tpMail->m_nLeftPageMailNum = std::min( MailCount, MAIL_MAX_PAGENUM );
	
	// �������ʼ�������ʼ��Ϊ0
	tpMail->m_nLockMailNum	   = 0;	 
	
	// ����Ѿ���ȡ���ʼ�����	
	if ( tpMail->m_nMailBoxStatus & MAIL_STATUS_CHECKNEWMAIL )
	{
		int NewMailCount = tpMail->m_nCurCacheMailCount; 
		if ( MailCount > MAIL_MAILBOX_MAXMAILNUM )
		{
			NewMailCount -= MailCount - MAIL_MAILBOX_MAXMAILNUM;
		}						
		tpMail->SendMsgMailBoxStatus( MailCount, NewMailCount );
		
		// �ʼ���ʼ�����
		tpMail->m_nMailBoxStatus = MAIL_STATUS_SHUTDOWN;
		tpMail->m_nCurCacheMailCount =  0;	 				
		return;
	} 	
	tpMail->m_nMailBoxStatus |= MAIL_STATUS_GETCOUNT;  	
}

// ***********************************************************
//  Function:		CheckNewMailCallBack
//  Description:	�����ݿ��ȡ���ʼ������Ļص�����
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:			2009-04-14		
// **********************************************************
void CMail::CheckNewMailCallBack( int CharID, int NewMailCount )
{
	CEntityPlayer *pPlayer = ( CEntityPlayer * )CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID( CharID );
	if ( pPlayer == NULL )
	{
		// ��������������
		return;
	}
	CMail *tpMail = CMailManager::GetSingletonPtr()->GetMail( pPlayer );
	if ( tpMail == NULL )
	{
		// ����
		LOG_ERROR( "mail","[%s,%d][%s] Get CMail Error! ", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}
	if ( NewMailCount < 0 )
	{
		NewMailCount = 0;		
	}  
	
	// �ʼ������Ѿ���ȡ���
	if ( tpMail->m_nMailBoxStatus & MAIL_STATUS_GETCOUNT )
	{	   				
		if ( tpMail->m_nTotalMailCount > MAIL_MAILBOX_MAXMAILNUM )
		{
			NewMailCount -= tpMail->m_nTotalMailCount - MAIL_MAILBOX_MAXMAILNUM;
		}
		tpMail->SendMsgMailBoxStatus( tpMail->m_nTotalMailCount, NewMailCount );
		tpMail->m_nMailBoxStatus = MAIL_STATUS_SHUTDOWN;
		return;		
	} 
	
	// ��������״̬
	tpMail->m_nCurCacheMailCount = NewMailCount;
	tpMail->m_nMailBoxStatus |= MAIL_STATUS_CHECKNEWMAIL;	
}		 

// ***********************************************************
//  Function:		GetMailDetailFromDB
//  Description:	�����ݿ��ȡ�ʼ��ĸ�����Ϣ��������Ϣ	
//  Input:			
//  OutPut:			
//  Return:			
//  Others:			
//  Date:			2009-02-18			
// **********************************************************
int CMail::GetMailDetailFromDB( int MailID )
{
	CEntityPlayer *pPlayer = GetEntityPlayer();
	LK_ASSERT( pPlayer != NULL, return -1 );
	CMailCache *tpMailCache = GetMailCacheByMailID( MailID );
	if ( tpMailCache == NULL )
	{
		return -1;
	}
	if( MAIL_IS_HASSENDTOCLIENT( tpMailCache->mType ) ) 
	{
		return -2;
	}
	CMailDBOperate::GetMailDetailInfo( MailID, GetCharID(), pPlayer->GetNationality() );	
	return 1;
}

// ***********************************************************
//  Function:		PayMoneyForMail
//  Description:	Ϊ�����ʼ�֧����Ǯ	
//  Input:			
//  OutPut:			
//  Return:			
//  Others:			
//  Date:			2009-02-18			
// **********************************************************
int CMail::PayMoneyForMail( int nMailID, int &rMoney, int &rTime )
{  
	CMailCache *tpCache = GetMailCacheByMailID( nMailID );		
	if ( tpCache == NULL )
	{
		return -1;
	}
	
	if ( tpCache->mMoneyNeedPayBack <= 0 && !MAIL_IS_MONEYNEED( tpCache->mLevel ) )
	{
		return ERR_MAIL_PAYMAIMONEY_NONEED;
	}
	
	if ( rMoney < tpCache->mMoneyNeedPayBack )
	{
		return ERR_MAIL_PAYMAIMONEY_MONEYNOTENOUGH;
	}
	
	// ��Ǯ
	rMoney = tpCache->mMoneyNeedPayBack;
		
	// ��������״̬
	MAIL_SETLEVEL_BACKMAIL( tpCache->mLevel, false )
	MAIL_SETLEVEL_MONEYNEED( tpCache->mLevel, false ) 
	tpCache->mExpiredTime = ( time(NULL) + MAIL_TIME_PACKAGE );// /DAY_TIME;
	rTime = tpCache->mExpiredTime/DAY_TIME;
	
	// �ʼ��Ѿ��ı���Ҫ���´���
	MAIL_SETTYPE_NEEDSAVE( tpCache->mType, 1 )
	tpCache->mMoneyNeedPayBack = 0;
	// ChangeActionMailID( nMailID );
	UpdateMail( tpCache );
	
	// �����ʼ�
	CMailCache *tpReplyCache = ( CMailCache * )CSceneObjManager::GetSingleton().CreateObject( OBJTYPE_MAIL_MAILCACHE ); 
	if ( tpReplyCache == NULL )
	{
		return -1;
	}
	
	CEntityPlayer *pPlayer = GetEntityPlayer();
	LK_ASSERT( pPlayer != NULL, return -1 );
	tpReplyCache->mMoney = rMoney;
	
	// �����ʼ����շ�����	
	strncpy( tpReplyCache->mSrcName, pPlayer->GetCharName(), NAME_LENGTH );
	tpReplyCache->mSrcName[NAME_LENGTH-1] = '\0';	
	tpReplyCache->mSrcId = pPlayer->GetCharID();

	// ��������ʱ����ʼ�����
	tpReplyCache->mSendTime		= time( NULL );
	tpReplyCache->mExpiredTime	= ( tpReplyCache->mSendTime + MAIL_TIME_PACKAGE );// /DAY_TIME;	   
	
	// �����ʼ�����
	strncpy(  tpReplyCache->mMailTitle, tpCache->mMailTitle, sizeof(tpCache->mMailTitle) - 1 );
	tpReplyCache->mMailTitle[sizeof(tpCache->mMailTitle) - 1]='\0';
	
	// �����ʼ�Ϊ���ʼ�
	MAIL_SETTYPE_NEW( tpReplyCache->mType, true )

	//  ����Է����ߵĻ��򷢸��Է�	
	//bool IfNeedCallBack = SendMailToPlayer( tpCache->mSrcId, tpReplyCache );
			
	m_sMailInfo.mMailBase.mTitle		= tpCache->mMailTitle;
	const char *pBody = "";
	
	// �����ʼ������ݿ�
	SaveMail( tpReplyCache, pBody, tpCache->mSrcId, true, tpCache->mSrcName, pPlayer->GetNationality() );

	//// �����������ɾ���ʼ�
	//if (  IfNeedCallBack == false )
	//{
	//	CSceneObjManager::GetSingletonPtr()->DestroyObject( tpReplyCache->get_id() );
	//}  		
	LogEventLostMoneyBySendMail( pPlayer, CYuanBao::em_unbind_money, rMoney, tpCache->mSrcId, nMailID );
	
	return SUCCESS;
}	

bool CMail::IsHavePayMail()
{
	_MAIL_CACHE_LIST_TYPE_::iterator it;
	CMailCache *tpMailCache = NULL ;
	for ( it = m_vMailCache.begin( ); it != m_vMailCache.end( ); it++ )
	{
		tpMailCache = ( CMailCache * )CSceneObjManager::GetSingletonPtr( )->GetObject( it->second );
		if(tpMailCache->mMoneyNeedPayBack > 0)
			return true;
	}
	return false;

}
