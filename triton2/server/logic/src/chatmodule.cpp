#include "stdafx.hpp"
#include "chatmodule.h"
#include "westserver.h"
#include "servercore.h"
#include "entity.h"
#include "servertool.h"
#include "property.h"
#include "chatmessage_pb.hxx.pb.h"
#include "message_pb.hxx.pb.h"
#include "coremessage_pb.hxx.pb.h"
#include "promessage_pb.hxx.pb.h"
#include "chat.h"
#include "chatmanager.h"
#include "sceneobj_manager.h"
#include "dirtyword.h"
#include "friendmodule.h"
#include "mapmodule.h"
#include "teammodule.h"
#include "propertymodule.h"
#include "errcode.h"
#include "gmmessage_pb.hxx.pb.h"
#include "gmmodule.h"
#include "repetionmodule.h"
#ifdef LEAK_CHK_DEBUG_NEW
#include "debug_new.h"
#endif


template<> CChatModule* CSingleton< CChatModule >::spSingleton = NULL;

char CChatModule::sModuleName[ NAME_LENGTH ] = "Chat_1";
CChatManager* gpChatManager = NULL;

unsigned int CChatModule::CountSize( )
{
	unsigned int tSize = sizeof( CChatModule );	
	tSize += CChatManager::CountSize( );
	 return tSize;
}


 // ***********************************************************
 //  Function:		OnLaunchServer
 //  Description:	���������� 				
 //  Output:			
 //  Date:	03/16/2009
 // **********************************************************
void CChatModule::OnLaunchServer( )
{	
	CChatManager::mShmPtr = mShmPtr;
	gpChatManager = new CChatManager;
	if( gpChatManager == NULL )
	{
		LOG_ERROR( "chat", "[ %s : %d ][ %s ]Launch Error", __LK_FILE__, __LINE__, __FUNCTION__ );
		printf( "Create ChatManager Faild, So Exit\n");
		exit(1);
	}	
	OnLoadConfig();
}

// ***********************************************************
//  Function:		OnLoadConfig
//  Description:	���������ļ� 				
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::OnLoadConfig()
{
	CHAT_LOG* tpCfg  = CSceneCfgManager::GetSingletonPtr( )->GetChat_log( );	
	if( tpCfg != NULL )
	{
		INIT_ROLLINGFILE_LOG( tpCfg->mIdentifier, tpCfg->mDirectory, ( LogLevel )tpCfg->mPriority, tpCfg->mMaxfilesize, tpCfg->mMaxbackupindex );
	}
	m_sChatCfg = CSceneCfgManager::GetSingletonPtr( )->GetChat_cfg( );	
	InitialChatUserConfig();
	const char* pcConfigPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(), const_cast<char*>("chat/Chat.xml") );
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CChatModule::LoadChatUserConfigCallback);
}


// ***********************************************************
//  Function:		OnExitServer
//  Description:	�˳������� 				
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::OnExitServer( )
{
	if ( gpChatManager != NULL )
	{
		delete gpChatManager;
		gpChatManager = NULL;
	}
}

 
// ***********************************************************
//  Function:		OnTimer
//  Description:	������Timer 				
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::OnTimer( unsigned int vTickCount, unsigned int vTickOffset )
{	
	
	if ( mAutoTimer.Elapse( vTickOffset ) == true )
	{
		SendAutoMessToClient( & CChatManager::GetSingletonPtr( )->AutoChat );
		mAutoTimer=CWTimer( 1000 );
	} 	
	//if ( mTimer.Elapse( vTickOffset ) != true )
	//{	  
	//	return ;
	//} 
	//BugleMess * PlayerBugleChat =CChatManager::GetSingletonPtr()->BugleChat.GetCurrentChat();
	//	
	//// ���ȶ���Ϊ��
	//if( PlayerBugleChat == NULL )
	//{
	//	m_bIfBugleEmpty = true;		
	//	return;
	//}
	//
	//// ��������һ��������ң���һ��������Ҳ�����������
	//if( CChatManager::GetSingletonPtr()->BugleChat.GetPlayerCount() == 0 )
	//{
	//	m_bIfBugleEmpty = false;
	//}
	//
	//// �����Ϊ�����Ͷ��е�ǰ��������
	//int showintable=0;
	//ChatCallBackMsg  ChatCallBack;
	//ChatCallBack.SetChatCallBackMsg( CHANNEL_BUGLE, ( const char * )PlayerBugleChat->MessBuff
	//	, ( const char * )PlayerBugleChat->PlayerName,PlayerBugleChat->ItemBuff, PlayerBugleChat->ItemBuffLen
	//	, NULL, 1, CMessageRouter::ROUTER_CHAR, showintable, 0, PlayerBugleChat->PlayerCharID );			
	//CMessage *tpChatCallBack =  &ChatCallBack.MessageHead;
	//CSceneLogic::GetSingletonPtr( )->Send2Gate( tpChatCallBack );	
	//mTimer = CWTimer( m_sChatCfg->mBugletime*1000 );
}

// ***********************************************************
//  Function:		OnCreateMap
//  Description:	�������� 				
//  Output:			
//  Date:	03/16/2009
// **********************************************************
int CChatModule::OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName )
{
	return SUCCESS;	
}

// ***********************************************************
//  Function:		OnRouterMessage
//  Description:	·����Ϣ
//	Input:			CMessage* pMessage ·����Ϣ 				
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::OnRouterMessage( CMessage* pMessage )
{
	if( pMessage == NULL )
		return;	   
		
    int ID = pMessage->mutable_msghead()->messageid();	
	switch( ID ) 
	{	
		case ID_S2C_CHATSENDCALLBACK:
		{
			CMessageChatSendCallBack* tpMsg = ( CMessageChatSendCallBack* )pMessage->msgpara( );
			LK_ASSERT( tpMsg != NULL, return );	 		
		
			if ( tpMsg->router().sendback() == 1 )
			{ 			
				// ֻ��������Ҫ������Ϣ
				if ( tpMsg->channel() != CHANNEL_P2P )
				{
					return;
				}
				
				int SrcCharID = tpMsg->router().srccharid();
				if( tpMsg->router().routerreason() == CMessageRouter::REASON_SUCCESS )
				{					
					CEntityPlayer *pplayer = ( CEntityPlayer * ) CSceneLogic::GetSingletonPtr()->GetPlayerByCharID(SrcCharID);
					if ( pplayer != NULL )
					{
						CSceneLogic::GetSingletonPtr()->Send2Player( pplayer, pMessage );
					}					
					return;
				}

				if ( tpMsg->router().routerreason() == CMessageRouter::REASON_OFFLINE )
				{
					ChatResultMsg ChatResult;
					ChatResult.SetChatResultMsg(tpMsg->channel(),
							ERROR_CHAT_OFFLINE, tpMsg->msg().c_str(), tpMsg->router().desname().c_str());

					CEntityPlayer *pplayer =
						( CEntityPlayer * ) CSceneLogic::GetSingletonPtr()->GetPlayerByCharID(SrcCharID);

					CSceneLogic::GetSingletonPtr()->Send2Player(pplayer, &ChatResult.MessageHead );
					return;
				}
			}

			if ( tpMsg->router().sendback() == 0 )
			{  
				if ( tpMsg->channel() == CHANNEL_FAMILY || tpMsg->channel() == CHANNEL_CORPS )
				{
					// OnGateChatMsg( pMessage );
					return;
				}
				
				if( tpMsg->mutable_router( )->routerreason( ) == CMessageRouter::REASON_SUCCESS )
				{
					if ( tpMsg->router().routertype( ) == CMessageRouter::ROUTER_CHAR && tpMsg->router().descharid() == 0)
					{
						int tNationID = -1;
						if ( tpMsg->channel() == CHANNEL_COUNTRY )
						{
							tNationID = tpMsg->countryid();
						}
						CSceneLogic::GetSingletonPtr()->SendSceneMessage(pMessage, tNationID);
					}else
					{
						CEntityPlayer *tpDesPlayer = tpMsg->router().routertype( ) == CMessageRouter::ROUTER_CHAR
							? CSceneLogic::GetSingletonPtr()->GetPlayerByCharID(tpMsg->router().descharid())
							: CSceneLogic::GetSingletonPtr()->GetPlayerByName(tpMsg->router().desname().c_str());

						if ( tpDesPlayer == NULL   )
						{
							LOG_ERROR("chatmodule","[%s,%d][%s] Can not get des CEntityPlayer by name !",
									__LK_FILE__,__LINE__,__FUNCTION__ );
							return;
						}

						if( CFriendModule::GetSingletonPtr()->IsInBlack(tpMsg->router().srccharid(), tpDesPlayer->GetCharID()))
						{
							LOG_DEBUG("chatmodule", "palyer(%d) is in player(%s)'s blcaklist.", 
											tpMsg->router().srccharid(), tpDesPlayer->GetCharID());
							return;
						}	

						// �����P2P��Ϣ Ҫ��鲢����Ŀ���û�����
						if ( tpMsg->channel() == CHANNEL_P2P )
						{
							if ( CGMModule::GetSingleton().IsGm( tpDesPlayer->GetGmStatus() ) )
								tpMsg->set_desusertype(USERTYPE_GM);
						}
												
						CSceneLogic::GetSingletonPtr()->Send2Player(tpDesPlayer,  pMessage);
					}
				}
			}

			break;
		}

		default:
			break;		
	}
}

// ***********************************************************
//  Function:		OnClientMessage
//  Description:	�ͻ�����Ϣ
//	Input:			CMessage* pMessage �ͻ�����Ϣ
//  Input:			CEntityPlayer* pPlayer				
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	/*ChatMsg( pPlayer, pMessage );*/
	if ( pMessage == NULL )
	{
		return;
	}	
	int ID = pMessage->mutable_msghead( )->messageid( );
	switch( ID )
	{
		case ID_C2S_CMESSCHATSEND:   
			{
				OnMessageChatSend( pPlayer, pMessage );
			}
			break;
	
		case ID_C2S_NOTIFY_AUTOCHATMESSAGE :
			{ 
				OnMessageAutoChat( pPlayer, pMessage );
			}
			break;
		case ID_C2S_NOTIFY_STOPAUTOCHAT :
			{
				OnMessageStopAutoChat( pPlayer, pMessage );
			}
			break;
		case ID_C2S_NOTIFY_USECHATITEM :
		   {
			   OnMessageUseItem( pPlayer ,pMessage );
	       }
		    break; 
		case ID_C2S_NOTIFY_CLICKBUGLEITEM :
			{
				OnMessageClickBugleItem( pPlayer , pMessage );
			}
			break ;
		case ID_C2S_REQUEST_CHECKDIRTYWORD :
			{
				OnMessageCheckDirtyWord(  pPlayer , pMessage );
			}
			break ;
	}

}

// ***********************************************************
//  Function:		OnCreateEntity
//  Description:	����ʵ��
//	Input:			CEntity* pEntity
//	Input:			CCreator* pCreator
//  Input:			bool vFirst			
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::OnCreateEntity( CEntity* pEntity, CCreator* pCreator, bool vFirst )
{
	LK_ASSERT( pEntity != NULL, return )
	if ( pEntity->IsPlayer() )
	{
		CChat* tpChat = CChatManager::GetSingletonPtr( )->AddPlayer( (CEntityPlayer*)pEntity );
		if( tpChat == NULL )
		{
			LOG_ERROR( "chat", "[ %s : %d ][ %s ] Creat object %d failed when OnCreatEntity", 
				__LK_FILE__, __LINE__, __FUNCTION__, ((CEntityPlayer*)pEntity)->GetCharID() );
			return;
		}		
		
		// ��ȡ��ҵĽ������
		int	tRoleStatus = ( ( CEntityPlayer * )pEntity )->GetRoleStatus();
		int	tFreeTime = ( ( CEntityPlayer * )pEntity )->GetRoleStatusParam();
		int tTimePriod = tFreeTime - time( NULL );		
		if ( tTimePriod < 0 )
		{
			tTimePriod = 0;
		}
		tpChat->InitialChannel( tRoleStatus, tTimePriod );			
	}
}


// ***********************************************************
//  Function:		OnDestroyEntity
//  Description:	����ʵ��
//	Input:			CEntity* pEntity
//	Input:			int vCode	
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::OnDestroyEntity( CEntity* pEntity, int vCode )
{
	LK_ASSERT( pEntity != NULL, return );
	if ( pEntity->GetEntityType() == ENTITYTYPE_PLAYER )
	{
		CEntityPlayer* tpPlayer = (CEntityPlayer*) pEntity;		
		CChatManager::GetSingletonPtr()->Erase( tpPlayer );
		CChatManager::GetSingletonPtr()->AutoChat.DelAutoMess( tpPlayer->GetCharID(), 0 );		
	}	
}


// ***********************************************************
//  Function:		OnSaveData
//  Description:	��������
//	Input:			CEntityPlayer *pPlayer
//	Input:			int vSaveCode	
//  Output:			
//  Date:	03/16/2009
// **********************************************************
bool CChatModule::OnSaveData( CEntityPlayer *pPlayer, int vSaveCode )
{  
	return true;	
}

// ***********************************************************
//  Function:		OnMessageChatSend
//  Description:	������Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			CMessage* pMessage	
//	Input:			int IsAutoMess
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void  CChatModule::OnMessageChatSend( CEntityPlayer* pPlayer, CMessage* pMessage, int IsAutoMess )
{   
	CMessageChatSend *tpMessage = ( CMessageChatSend * ) pMessage->msgpara( );
	LK_ASSERT( tpMessage != NULL, return );
	

	// ���������������
	if( ( tpMessage->pkgindex_size() != tpMessage->itemindex_size() ) ||
		( tpMessage->pkgindex_size() != tpMessage->itemsequence_size() ) )	
	{
		return;
	}

	CChatContent tChatContent;
	tChatContent.mMsg.assign( (char *)tpMessage->mutable_msg()->c_str() );

	if( tpMessage->pkgindex_size() > 0 && tpMessage->pkgindex_size() <= CChatContent::MAX_CHATATTACH_ITEM )
	{
		for( int i = 0; i < tpMessage->pkgindex_size() ; i++ )
		{
			tChatContent.mPkgIdx[ i ] = tpMessage->pkgindex( i );
			tChatContent.mItemIdx[ i ] = tpMessage->itemindex( i );
			tChatContent.mItemSeq[ i ] = tpMessage->itemsequence( i );
			tChatContent.mItemNum++;
		}
	}

	// ���Ŀ��Ŀ��������ֳ����Ƿ�Ϸ�
	if( tpMessage->has_playername() )
	{	
		LK_ASSERT( tpMessage->mutable_playername()->length( ) < NAME_LENGTH, return );
		tChatContent.mDstCharName.append( ( char * )tpMessage->mutable_playername()->c_str() );		
	}

	tChatContent.mSrcEntityID = pPlayer->GetEntityID();
	tChatContent.mSrcCharID = pPlayer->GetCharID();
	tChatContent.mSrcCharName.append( pPlayer->GetCharName() );
	tChatContent.mChannel = tpMessage->channel();
	tChatContent.mSrcPlayerType = ( CGMModule::GetSingleton().IsGm( pPlayer->GetGmStatus() ) ? USERTYPE_GM : USERTYPE_NONE ) ;

	// ����������Ϣ
	CheckChatMsg( pPlayer, &tChatContent, IsAutoMess );
} 

// ***********************************************************
//  Function:		CAutoChatMessage
//  Description:	���������Զ���������Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			CMessage* pMessage	
//	Input:			int IsAutoMess
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::OnMessageAutoChat( CEntityPlayer* pPlayer, CMessage* pMessage, int IsAutoMess )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CAutoChatMessage   *tpMess = ( CAutoChatMessage * ) pMessage->msgpara();
	LK_ASSERT( tpMess != NULL, return );
    int				IfModifyOk		= 0; 	
	LK_ASSERT( tpMess->has_msg(), return );		
	LK_ASSERT( tpMess->mutable_msg()->length() < MAX_MASSAGE_LEN, return );	
	LK_ASSERT(  CDataStatic::sAutoChatItemId > 0, return );
	
	// ���ȼ��Ƿ����Ҫ��
	if ( CheckLevel( tpMess->channel(), pPlayer ) != 1 )
	{ 		
		SendChatResultMsg( pPlayer, (int)tpMess->channel(), ERROR_CHAT_CHANNELWORLDLEVELLOW, tpMess->mutable_msg()->c_str(), pPlayer->GetCharName() );		
		return;
	}
	
	// �ж��Ƿ��к�������
	char * pMsg = NULL;	
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	int tIndex = -1;
	int tNum = 0;
	tpProperty->GetBaggage()->HasItemOfCertainType( CTplItem::ITEM_AUTOSHOUT, tNum, tIndex );
	if ( tIndex < 0 || tNum < 1 )
	{ 
		SendChatResultMsg( pPlayer, CHANNEL_AUTOMSG, ERROR_CHAT_HASNOAUTOCHATITEM, pMsg,  pPlayer->GetCharName(), tpMess->count() );		
		return;
	} 	
	
	// �ж�ʱ�������Ƿ���ȷ
	if ( CheckAutoChatTime( tpMess->time(), tpMess->channel() ) == -1 )
	{
		return;
	}	
	pMsg = ( char * )tpMess->mutable_msg()->c_str();
	CDirtyWord::GetSingletonPtr()->OI_Dirty_Check( 1, pMsg );
	IfModifyOk = CChatManager::GetSingletonPtr()->AutoChat.ModifyAutoMess( pPlayer->GetCharID(), pMsg, tpMess->time(), tpMess->channel(), tpMess->count() ); 
	if ( IfModifyOk == 1 )
	{		
		SendChatResultMsg( pPlayer, CHANNEL_AUTOMSG,CHAT_MODIFYAUTOCHATOK, pMsg, pPlayer->GetCharName(), tpMess->count() );  			
	}
	else
	{
		SendChatResultMsg( pPlayer, CHANNEL_AUTOMSG, CHAT_STARTAUTOCHAT, pMsg, pPlayer->GetCharName(), tpMess->count() );	
	}
}

// ***********************************************************
//  Function:		OnMessageClickBugleItem
//  Description:	������ҵ�����ߵ���Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			CMessage* pMessage	
//	Input:			int IsAutoMess
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::OnMessageClickBugleItem( CEntityPlayer* pPlayer, CMessage* pMessage, int IsAutoMess )
{	
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return ); 
	CChat *tpChat = CChatManager::GetSingleton().GetChat( pPlayer );
	LK_ASSERT( tpChat != NULL, return );   	

	// ��ҽ���������ж�		
	if ( tpChat->InChannel( CHANNEL_BUGLE ) || tpChat->InChannel( CHANNEL_ALL ) )
	{
		// TODO:���ͱ����Ե�֪ͨ
		if( time(NULL) > tpChat->GetForbidenFreeTime() )
		{
			CChatModule::GetSingleton().SetChannelTrue(pPlayer->GetCharID(), CHANNEL_ALL );
		}
		else
		{
			// TODO:���ͱ����Ե�֪ͨ
			SendChatResultMsg( pPlayer, CHANNEL_BUGLE, CHAT_FORBIDDEN, NULL, NULL, tpChat->GetForbidenFreeTime() - time(NULL )  );
				//CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_CHAT_CHATFORBIDEN );
			return;
		}		
	}	
	
	// ���ȼ�
	if ( CSceneCfgManager::GetSingleton().GetChat_cfg()->mBuglelevellimit > pPlayer->GetLevel() )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_CHAT_BUGLELEVELLIMIT );		
		return;
	}

	// ��ҵ������ָ�������ȵ���
    CMessage HeadMessage;
	CMessageLockItemNotice LockItemNotice ;	
	
	   
	//��ȡָ�����ӵĵ�����Ϣ
	CMesssageClickBugleItem  *tpMess = ( CMesssageClickBugleItem * ) pMessage->msgpara() ;
	LK_ASSERT( tpMess != NULL, return );
	CPropertyPlayer* tpSrcProperty = ( CPropertyPlayer* )pPlayer->GetProperty( );
	CItemObject * tpSrcItem =( CItemObject * ) tpSrcProperty->GetBaggage( )->GetItemObjPtr( tpMess->itemindex() );
	if( tpSrcItem == NULL )
	{	
		LOG_ERROR( "chat"," [%s,%d][%s]Get item wrong, RoleID:%d!" ,__LK_FILE__,__LINE__,__FUNCTION__, pPlayer->GetCharID() );
		return ;
	}
	
	CTplItem *tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( tpSrcItem->GetItemID() );
	if ( tpTplItem == NULL )
	{
		LOG_ERROR( "chat","can not find template of item ( TemplateID:%d ), ( RoleID:%d )!" ,__LK_FILE__,__LINE__,__FUNCTION__, tpSrcItem->GetItemID(), pPlayer->GetCharID() );
		return;
	}

	if ( tpTplItem->mItemType != CTplItem::ITEM_SHOUT )
	{	
		LOG_ERROR("chat"," [%s,%d][%s]Error itemid ( TemplateID:%d, RoleID:%d ) !",__LK_FILE__,__LINE__,__FUNCTION__, tpSrcItem->GetItemID(), pPlayer->GetCharID() );
		return;
	}
	
	//��ȡ�ɹ����������ȵ���
	if ( tpMess->locktype() == 1 )
	{					
		//�Ǽ�����Ϣ�������߼���
		tpSrcProperty->GetBaggage( )->Lock( tpMess->itemindex(), LOCKTYPE_SHOUT );		
		HeadMessage.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_LOCKITEM );
        HeadMessage.set_msgpara( (int )&LockItemNotice );
        LockItemNotice.set_index( tpMess->itemindex());
		LockItemNotice.set_locked( LOCKTYPE_SHOUT );
	    CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &HeadMessage );
	    	 
		//֪ͨ�ͻ��˿��������������		
		SendChatResultMsg( pPlayer, CHANNEL_AUTOMSG, CHAT_CANSENDBUGLEMESS, NULL, pPlayer->GetCharName() );  						
		return ;
	}
	else if ( tpMess->locktype() == 0 )
	{
		//�Ǽ�����Ϣ�������߼���
		tpSrcProperty->GetBaggage( )->Lock( tpMess->itemindex(), LOCKTYPE_NONE ); 
		    
		//���ȡ�����ȷ��ԣ������߽���
		HeadMessage.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_LOCKITEM );
		HeadMessage.set_msgpara( (int )&LockItemNotice );
		LockItemNotice.set_index( tpMess->itemindex());
		LockItemNotice.set_locked( LOCKTYPE_NONE );
		CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &HeadMessage );							
	}
	else
	{
		//����δ֪����Ϣ		
		LOG_ERROR( "chat","[%s,%d][%s] Error MSG! ",__LK_FILE__,__LINE__,__FUNCTION__ );
		return;
	}
}

// ***********************************************************
//  Function:		OnMessageStopAutoChat
//  Description:	��������ֹͣ�Զ���������Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			CMessage* pMessage	
//	Input:			int IsAutoMess
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::OnMessageStopAutoChat( CEntityPlayer* pPlayer, CMessage* pMessage, int IsAutoMess )
{	
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CStopAutoChatMessage *tpMess = ( CStopAutoChatMessage * ) pMessage->msgpara();
	if ( tpMess == NULL )
	{
		return;
	}
	int IsDelOk = CChatManager::GetSingletonPtr()->AutoChat.DelAutoMess( pPlayer->GetCharID(), 0 );
	if ( IsDelOk == 1 )
	{
		SendChatResultMsg( pPlayer, CHANNEL_AUTOMSG, CHAT_STOPSAUTOCHAT , mCurrentAutoChat.MessBuff , pPlayer->GetCharName() );		
	}
	return ;
}

// ***********************************************************
//  Function:		OnMessageStopAutoChat
//  Description:	����ʹ�����ȵ��ߵ���Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			CMessage* pMessage	
//	Input:			int IsAutoMess
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::OnMessageUseItem( CEntityPlayer* pPlayer, CMessage* pMessage, int IsAutoMess )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageUseItem  *tpMess = ( CMessageUseItem * )pMessage->msgpara( );
	LK_ASSERT( tpMess != NULL, return );
	LK_ASSERT( tpMess->has_msg(), return );
	LK_ASSERT( tpMess->mutable_msg()->length() < MAX_MASSAGE_LEN, return );
	
	char *pMsg = ( char * )tpMess->mutable_msg()->c_str();
	//TODO: �����ͻ���Ҳ��֧�����Ҽ��򿪵Ľ����Ƚ������������
	//const char *pItemInfo = NULL;
	//int			ItemBuffLen = 0;
	//if ( tpMess->has_iteminfo() )
	//{
	//	LK_ASSERT( tpMess->iteminfo().length() < MAX_ITEMBUFF_LENGTH, return );
	//	pItemInfo = tpMess->iteminfo().c_str();
	//	ItemBuffLen = tpMess->iteminfo().length();		
	//}
	
	// ���ȼ�
	if ( CSceneCfgManager::GetSingleton().GetChat_cfg()->mBuglelevellimit > pPlayer->GetLevel() )
	{			
		return;
	}

	// �������GM˵�Ļ� �Ž��м��
	if ( !CGMModule::GetSingleton().IsGm( pPlayer->GetGmStatus() ) )
		CDirtyWord::GetSingletonPtr()->OI_Dirty_Check( 1 , ( char * )pMsg );	 
		 
	//�ȸ��������߽��� 
	CPropertyPlayer* tpSrcProperty = ( CPropertyPlayer* )pPlayer->GetProperty();
	CItemObject * tpSrcItem =( CItemObject * ) tpSrcProperty->GetBaggage( )->GetItemObjPtr( tpMess->itemindex() );
	if( tpSrcItem == NULL )
	{
		return ;
	} 
	
	CChatContent tChatContent;
	tChatContent.mMsg.assign( pMsg );
	tChatContent.mSrcEntityID = pPlayer->GetEntityID();
	tChatContent.mSrcCharID = pPlayer->GetCharID();
	tChatContent.mSrcCharName.append( pPlayer->GetCharName() );
	tChatContent.mChannel = CHANNEL_BUGLE;
	tChatContent.mSrcPlayerType = ( CGMModule::GetSingleton().IsGm( pPlayer->GetGmStatus() ) ? USERTYPE_GM : USERTYPE_NONE ) ;


	//����һ��ָ�������еĺ�������
	ChatOnChannelBugle( pPlayer, &tChatContent, tpMess->itemindex() ); 
}


// ***********************************************************
//  Function:		OnMessageCheckDirtyWord
//  Description:	�Զ���Ƶ�����ķǷ��ʼ��
//	Input:			CEntityPlayer* pPlayer
//	Input:			CMessage* pMessage	
//	Input:			int IsAutoMess
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::OnMessageCheckDirtyWord( CEntityPlayer* pPlayer, CMessage* pMesage, int IsAutoMess )
{
	CMessage  MessageHead;
	CMessageHasDirtyWord MessageHasDirtyWord;
	LK_ASSERT( pPlayer != NULL && pMesage != NULL, return );     
	CMessageCheckDirtyWord *tpMessage = ( CMessageCheckDirtyWord *) pMesage->msgpara( );
	LK_ASSERT( tpMessage != NULL, return );
	LK_ASSERT( tpMessage->has_msg(), return );
	LK_ASSERT( tpMessage->mutable_msg()->length() <= MAX_MASSAGE_LEN, return ); 
	char *pMsg   = (char *)tpMessage->mutable_msg()->c_str();
	int   Flag = tpMessage->flag(); 
	int  HasDirtyWorld = CDirtyWord::GetSingletonPtr()->OI_Dirty_Check( 1, ( char * )pMsg );
	if ( HasDirtyWorld == 0 )
	{
		MessageHasDirtyWord.set_hasdirtyword( HAS_NO_DIRTYWORD );
	}
	else
	{
		MessageHasDirtyWord.set_hasdirtyword( HAS_DIRTYWORD );	   
	} 
	MessageHasDirtyWord.set_msg( pMsg );   
	MessageHasDirtyWord.set_flag( Flag );
	MessageHead.set_msgpara( ( int ) &MessageHasDirtyWord  );
	MessageHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_HASDIRTYWORD  );
	CSceneLogic::GetSingletonPtr()->Send2Player( pPlayer, &MessageHead );
}

// ***********************************************************
//  Function:		ChatOnChannelCommon
//  Description:	����ͨƵ������������Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			int vChannel
//	Input:			char *pMsg
//  Input:			*DesName
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::ChatOnChannelCommon( CEntityPlayer* pPlayer, CChatContent* pChatContent )
{		
		
	ChatCallBackMsg ChatCallBack;				
	GetChatUserFlag( pPlayer, ChatCallBack );
	ChatCallBack.SetChatCallBackMsg( pChatContent ) ;		
	CMapModule::GetSingletonPtr()->MessageBroadCast( pPlayer, &ChatCallBack.MessageHead, false,  true );
	SendChatResultMsg( pPlayer, pChatContent->mChannel, CHAT_SUCCESS, pChatContent->mMsg.c_str(), pPlayer->GetCharName() );
}	  

// ***********************************************************
//  Function:		ChatOnChannelP2P
//  Description:	������Ƶ������������Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			int vChannel
//	Input:			char *pMsg
//  Input:			*DesName
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::ChatOnChannelP2P( CEntityPlayer* pPlayer, CChatContent* pChatContent )
{ 
	LK_ASSERT( pChatContent->mDstCharName.c_str() != NULL, return );
	if ( strncmp( pPlayer->GetCharName(), pChatContent->mDstCharName.c_str(), NAME_LENGTH ) == 0 )
	{
		return;
	}
	
	// �鿴�Ƿ��ڱ�����������
	CEntityPlayer *pDesPlayer = CSceneLogic::GetSingletonPtr()->GetPlayerByName( pChatContent->mDstCharName.c_str() );	
	ChatCallBackMsg ChatCallBack;
	GetChatUserFlag( pPlayer, ChatCallBack );			
	if ( pDesPlayer == NULL )
	{
		// ��Ҳ��ڱ�������������·����Ϣ���͸�����			
		ChatCallBack.SetChatCallBackMsg( pChatContent ) ;

		CSceneLogic::GetSingletonPtr()->Send2Gate( &ChatCallBack.MessageHead );
	}
	else
	{
		// ����Ƿ��ں�������
		bool Result =  CFriendModule::GetSingletonPtr()->IsInBlack( pPlayer->GetCharID() , pDesPlayer->GetCharID());
		if ( Result == true )
		{				
			return;
		}		

		pChatContent->mDstPlayerType =  CGMModule::GetSingleton().IsGm( pDesPlayer->GetGmStatus() )  ? USERTYPE_GM : USERTYPE_NONE ;
		pChatContent->mDstCharID = pDesPlayer->GetCharID();

		ChatCallBack.SetChatCallBackMsg( pChatContent );

		CSceneLogic::GetSingletonPtr()->Send2Player( pDesPlayer, &ChatCallBack.MessageHead );			
		CSceneLogic::GetSingletonPtr()->Send2Player( pPlayer, &ChatCallBack.MessageHead );					
	}		
}	 

// ***********************************************************
//  Function:		ChatOnChannelWorld
//  Description:	������Ƶ������������Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			int vChannel
//	Input:			char *pMsg
//  Input:			*DesName
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::ChatOnChannelWorld( CEntityPlayer* pPlayer, CChatContent* pChatContent )
{
	LK_ASSERT( pPlayer != NULL && pChatContent != NULL, return );
	
	//���߼�������� 
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	int tIndex = -1;
	int tNum = 0;
	tpProperty->GetBaggage()->HasItemOfCertainType( CTplItem::ITEM_AUTOSHOUT, tNum, tIndex );
	if ( tIndex < 0 || tNum < 1 )
	{ 
		SendChatResultMsg( pPlayer, pChatContent->mChannel, ERROR_CHAT_WORLDBUGLENO, pChatContent->mMsg.c_str(), NULL );		
		return;
	} 
	
	CItemObject* tpItemObj = tpProperty->GetBaggage()->GetItemObjPtr( tIndex );
	if( tpItemObj == NULL )
	{
		return;
	}
	
	uint64_t ullGUID = tpItemObj->GetGUID();
	int nTplID = tpItemObj->GetItemID();
	if( CPropertyModule::GetSingleton().PlayerRemoveItem( pPlayer, tIndex, 1 ) == 0 )
	{
		LogEventLostItemByUse( pPlayer, ullGUID, nTplID, 1);
	}
							   
	ChatCallBackMsg ChatCallBack;	
	GetChatUserFlag( pPlayer, ChatCallBack );
	ChatCallBack.SetChatCallBackMsg( pChatContent );
	CSceneLogic::GetSingletonPtr()->Send2Gate( &ChatCallBack.MessageHead );		
}

// ***********************************************************
//  Function:		ChatOnChannelWorld
//  Description:	�ڶ���Ƶ������������Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			int vChannel
//	Input:			char *pMsg
//  Input:			*DesName
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::ChatOnChannelTeam( CEntityPlayer* pPlayer, CChatContent* pChatContent )
{
	LK_ASSERT( pPlayer != NULL, return )	
	int tTeamID  = CTeamModule::GetSingleton().InTeam( pPlayer->GetCharID() );
	if ( tTeamID == INVALID_OBJ_ID )
	{
	
		return;				
	}		

	ChatCallBackMsg tChatCallBack;	
	GetChatUserFlag( pPlayer, tChatCallBack );
	tChatCallBack.SetChatCallBackMsg( pChatContent );	
	CSceneLogic::GetSingleton().Send2Gate( &tChatCallBack.MessageHead );	
}

// ***********************************************************
//  Function:		ChatOnChannelBattle
//  Description:	��ս��Ƶ��������Ϣ
//	Input:			CEntityPlayer* pPlayer
//  Output:			
//  Date:	05/30/2009
// **********************************************************
void CChatModule::ChatOnChannelBattle( CEntityPlayer* pPlayer, CChatContent* pChatContent)
{
// �ڸ�����ʹ��			
#ifdef _FB_
	LK_ASSERT( pPlayer != NULL && pChatContent != NULL, return )	
	ChatCallBackMsg ChatCallBack;				
	GetChatUserFlag( pPlayer, ChatCallBack );
	ChatCallBack.SetChatCallBackMsg( pChatContent ) ;		
	CPlayerRepetion *tpPlayerRepetion = ((CPropertyPlayer *)pPlayer->GetProperty())->GetRepetion();
	if ( tpPlayerRepetion->GetOldRepeKey() <= 0 )
	{
		return;
	}	
	if ( tpPlayerRepetion->GetCampID() <= 0 )
	{
		return;
	}	
	CRepetion *tpRepetion = CRepetionModule::GetSingleton().GetRepetion( pPlayer );
	if ( tpRepetion == NULL )
	{
		return;
	}
	CRepetionModule::GetSingleton().SendBattleMsgByCamp( tpRepetion->get_id(), tpPlayerRepetion->GetCampID(), &ChatCallBack.MessageHead );
	SendChatResultMsg( pPlayer, pChatContent->mChannel, CHAT_SUCCESS, pChatContent->mMsg.c_str(), pPlayer->GetCharName() );
#endif
}
	
// ***********************************************************
//  Function:		ChatOnChannelBugle
//  Description:	������Ƶ������������Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			int vChannel
//	Input:			char *pMsg
//  Input:			*DesName
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::ChatOnChannelBugle( CEntityPlayer* pPlayer, CChatContent* pChatContent, int ItemIndex /* = -1 */ )
{	
	LK_ASSERT( pPlayer != NULL, return );
	

	//  ���Ľ�����
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	if ( ItemIndex == -1 )
	{			
		int tNum		= 0;
		
		tpProperty->GetBaggage()->HasItemOfCertainType( ITEM_SHOUT, tNum, ItemIndex );
		if ( tNum < 1 || ItemIndex < 0 )
		{							
			SendChatResultMsg( pPlayer, pChatContent->mChannel, ERROR_CHAT_HAVENOBUGLEITEM, pChatContent->mMsg.c_str(), NULL );			
			return;
		}
	}
	else
	{
		CItemObject *tpItemObj = tpProperty->GetBaggage()->GetItemObjPtr( ItemIndex );
		if ( tpItemObj == NULL )
		{
			return;
		}
		CTplItem *tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( tpItemObj->GetItemID() );
		if ( tpTplItem == NULL )
		{
			return;
		}
		if ( tpTplItem->mItemType != CTplItem::ITEM_SHOUT )
		{
			return;
		}
		
		if( tpProperty->GetBaggage( )->Lock( ItemIndex ,LOCKTYPE_NONE ) == true )
		{
			CPropertyModule::GetSingleton().SendLockItemNotice( pPlayer, ItemIndex, LOCKTYPE_NONE );
		} 
	}	 	  	
	
	CItemObject* tpItemObj = tpProperty->GetBaggage()->GetItemObjPtr( ItemIndex );
	if( tpItemObj == NULL )
	{
		return;
	}

	uint64_t ullGUID = tpItemObj->GetGUID();
	int nTplID = tpItemObj->GetItemID();
	if( CPropertyModule::GetSingleton( ).PlayerRemoveItem( pPlayer, ItemIndex, 1 ) == 0 )
	{
		LogEventLostItemByUse( pPlayer, ullGUID, nTplID, 1);
	}

	ChatCallBackMsg BugleMsg;
	GetChatUserFlag( pPlayer, BugleMsg );
	BugleMsg.SetChatCallBackMsg( pChatContent );
	CSceneLogic::GetSingletonPtr( )->Send2Gate( &BugleMsg.MessageHead );

	SendChatResultMsg( pPlayer, pChatContent->mChannel, CHAT_SUCCESS, pChatContent->mMsg.c_str(), pPlayer->GetCharName(), 8 );		
} 


// ***********************************************************
//  Function:		ChatOnChannelCountry
//  Description:	�ڹ���Ƶ������������Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			int vChannel
//	Input:			char *pMsg
//  Input:			*DesName
//  Output:			
//  Date:	06/24/2009
// **********************************************************
void CChatModule::ChatOnChannelCountry( CEntityPlayer* pPlayer, CChatContent* pChatContent )
{
	LK_ASSERT( pPlayer != NULL, return );	
	ChatCallBackMsg tCountryMsg;
	GetChatUserFlag( pPlayer, tCountryMsg );
	tCountryMsg.SetChatCallBackMsg( pChatContent );	
	tCountryMsg.ChatCallBack.set_countryid( pPlayer->GetNationality() );
	CSceneLogic::GetSingleton().Send2Gate( &tCountryMsg.MessageHead );
	
}

// ***********************************************************
//  Function:		ChatOnChannelFamily
//  Description:	�ڼ���Ƶ������������Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			int vChannel
//	Input:			char *pMsg
//  Input:			*DesName
//  Output:			
//  Date:	06/24/2009
// **********************************************************
void CChatModule::ChatOnChannelFamily( CEntityPlayer* pPlayer,CChatContent* pChatContent )
{	
	LK_ASSERT( pPlayer != NULL, return );	
	ChatCallBackMsg tFamilyMsg;
	GetChatUserFlag( pPlayer, tFamilyMsg );
	tFamilyMsg.SetChatCallBackMsg( pChatContent );
	tFamilyMsg.ChatCallBack.set_flagid(  pPlayer->GetFamilyID() );
	
	CSceneLogic::GetSingleton().Send2Gate( &tFamilyMsg.MessageHead );

}

// ***********************************************************
//  Function:		ChantOnChannelCorps
//  Description:	�ھ���Ƶ������������Ϣ
//	Input:			CEntityPlayer* pPlayer
//	Input:			int vChannel
//	Input:			char *pMsg
//  Input:			*DesName
//  Output:			
//  Date:	06/24/2009
// **********************************************************
void CChatModule::ChantOnChannelCorps( CEntityPlayer* pPlayer,CChatContent* pChatContent)
{	
	LK_ASSERT( pPlayer != NULL, return );	
	ChatCallBackMsg tCorpsMsg;
	GetChatUserFlag( pPlayer, tCorpsMsg );
	tCorpsMsg.SetChatCallBackMsg( pChatContent );
	tCorpsMsg.ChatCallBack.set_flagid( pPlayer->GetCorpsID() );
	CSceneLogic::GetSingleton().Send2Gate( &tCorpsMsg.MessageHead );

}

// ***********************************************************
//  Function:		SendChatResultMsg
//  Description:	����������
//	Input:			CEntityPlayer* pPlayer
//	Input:			int vChannel
//	Input:			char *pMsg
//  Input:			char *DesName
//	Input:			int vLeftTime	����Ƶ�����Ե�ʣ��ʱ��
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::SendChatResultMsg( CEntityPlayer *pPlayer, int vChannel, int vChatRes, const char *vInfor, const char *vName, int vLeftTime )
{
	LK_ASSERT( pPlayer != NULL, return );
	ChatResultMsg ChatResult;
	ChatResult.SetChatResultMsg( vChannel, vChatRes, vInfor, vName, vLeftTime );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &ChatResult.MessageHead );
}

// ***********************************************************
//  Function:		SendAutoMessToClient
//  Description:	�����Զ�������������������������Զ���������
//	Input:			CAutoMsg *AutoChat
//	Input:			
//	Input:			
//  Input:			
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::SendAutoMessToClient( CAutoMsg *AutoChat )
{
	if ( AutoChat->GetSpeakNum( ) == 0 )
	{
		return ;
	}
	int Result = 0;
	while( 1 )
	{		
		Result = AutoChat->GetCurrentChat( &mCurrentAutoChat );
		if ( Result == CAutoMsg::CHATCOMPLETE )
		{
		    //��������һ��ѭ��������
			break ;
		}
		if ( Result == CAutoMsg::CURCHATNOTINTIME )
		{			
			continue;
		}				
		CEntityPlayer *pplayer =( CEntityPlayer * ) CSceneLogic::GetSingletonPtr()->GetPlayerByCharID( mCurrentAutoChat.PlayerId );
		if ( pplayer != NULL )  
		{  
			// ��һ��ڱ�����������	�����Զ���������Ϣ	
            CMessage MessageHead;
			CMessageChatSend ChatCallBack;		
			ChatCallBack.set_channel(  mCurrentAutoChat.channel  );			
			if ( mCurrentAutoChat.MessBuff != NULL )
			{
				ChatCallBack.set_msg( mCurrentAutoChat.MessBuff );
			}		
			MessageHead.mutable_msghead()->set_messageid( ID_C2S_CMESSCHATSEND );		  
			MessageHead.set_msgpara( ( int )&ChatCallBack );	
			OnMessageChatSend( pplayer, &MessageHead, 1 );			
		}	
		else
		{ 			
		  //��Ҳ��ڱ��������������Զ����������ݴ�������һ������������
		  CChatManager::GetSingletonPtr()->AutoChat.DelAutoMess( mCurrentAutoChat.PlayerId );		  
		}
	}
}

// ***********************************************************
//  Function:		ConsumeChatItem
//  Description:	�������ȵ���
//	Input:			int ItemId			����ID
//	Input:			int ItemNum			��������
//	Input:			CEntityPlayer* pPlayer
//  Input:			int ItemIndex	    λ������
//  Output:			
//  Date:	03/16/2009
// **********************************************************
int CChatModule::ConsumeChatItem( int ItemId, int ItemNum, CEntityPlayer* pPlayer, int ItemIndex )
{				
	int ConsumeOk = 0;
	if ( ItemIndex != -1 )
	{
		CPropertyModule::GetSingletonPtr()->ConsumeItemByIndex( pPlayer->GetEntityID() , ItemId , ItemNum , ItemIndex, ConsumeOk );		
		if ( ConsumeOk == 1 )
		{
			return 1;
		}
		return -1;
	}
	int   HasItem = 0;
	int vItemIndex =  CPropertyModule::GetSingletonPtr()->HasItem(  pPlayer->GetEntityID() ,ItemId, ItemNum , HasItem, 0 );
	if ( HasItem == 0 )
	{
		return -1;
	}
		
	if ( vItemIndex != -1 )
	{
		CPropertyModule::GetSingletonPtr()->ConsumeItemByIndex( pPlayer->GetEntityID() , ItemId , ItemNum , vItemIndex, ConsumeOk );		
	}	
	return 1;
}

// ***********************************************************
//  Function:		CheckAutoChatTime
//  Description:	����Զ�������ʱ������
//	Input:			unsigned int time	ʱ��
//	Input:			int channel			Ƶ��
//	Input:			
//  Input:			
//  Output:			
//  Date:	03/16/2009
// **********************************************************
int CChatModule::CheckAutoChatTime( unsigned int time , int channel )
{
	if ( time > m_sChatCfg->mMaxautochattime )
	{
		return -1;
	}
	switch( channel )
	{
		case CHANNEL_COMMON:
			{
				return ( time < m_sChatCfg->mCommonautochattime ) ? -1 : 1;
			}
		
			break;
		case CHANNEL_WORLD:
			{
				return  ( time < m_sChatCfg->mWorldautochattime ) ? -1 : 1;
			}
			
			break;		
		case CHANNEL_CORPS:
			{
				return 1;
			}
			break;
		case CHANNEL_FAMILY:			
			{
				return 1;
			}
			break;		
		case CHANNEL_COUNTRY:
			{
				return 1;
			}
			break;	
		
		case CHANNEL_OTHERCOUNTRY:
			{
				return 1;
			}
	       break;
	    case CHANNEL_TEAM:
			{
				return 1;
			}
		default:
			return -1;	
	}
}



// ***********************************************************
//  Function:		SendMsgOnChannelCommon
//  Description:	����ͨƵ������������Ϣ
//	Input:			CEntityPlayer *pPlayer	ʱ��
//	Input:			const char *pMess			Ƶ��
//	Input:			
//  Input:			
//  Output:			
//  Date:	03/16/2009
// **********************************************************
//void CChatModule::SendMsgOnChannelCommon( CEntityPlayer *pPlayer , const char *pMess )
//{
//	LK_ASSERT( pPlayer != NULL && pMess != NULL, return )
//	ChatCallBackMsg ChatCallBack;
//	ChatCallBack.SetChatCallBackMsg( CHANNEL_COMMON, ( char * )pMess , pPlayer->GetCharName()  
//		, NULL, 0,  NULL , 1, CMessageRouter::ROUTER_NAME  , 1, 0 , 0 
//		, (CGMModule::GetSingleton().IsGm( pPlayer->GetGmStatus() ) ? USERTYPE_GM : USERTYPE_NONE ) );	
//	CSceneLogic::GetSingletonPtr()->Send2Player( pPlayer , &ChatCallBack.MessageHead );	
//}


// ***********************************************************
//  Function:		SetChannelFalse
//  Description:	�������ĳ��Ƶ������
//  Input:			CEntityPlayer *pPlayer		���ʵ��ָ��
//  Input:			int			  vChannel	    �����Ե�Ƶ��,Chattype.h �ļ������CHAT_CHANNELö��
//  Return:			void
//  Others:
//  Date:	02/01/2009
// **********************************************************
void CChatModule::SetChannelFalse( int vCharID, int vChannel, int nPeriod )
{
	CEntityPlayer *pPlayer = CSceneLogic::GetSingletonPtr()->GetPlayerByCharID( vCharID );
	if ( pPlayer == NULL )
	{
		return;
	}
	
	//GM���ܱ���
	if( CGMModule::GetSingletonPtr()->IsGm( pPlayer->GetGmStatus() ) )
	{
		return;
	}

	CChat *tpChat = CChatManager::GetSingletonPtr()->GetChat( pPlayer );	
	if ( tpChat == NULL )
	{
		return;		
	}
	tpChat->InitialChannel( pPlayer->GetRoleStatus(), nPeriod );	
	tpChat->SetChannel( vChannel, false );
	pPlayer->SetRoleStatus( tpChat->GetForbidenChannel() );	
	pPlayer->SetRoleStatusParam( tpChat->GetForbidenFreeTime() );
}

// ***********************************************************
//  Function:		SetChannelTrue
//  Description:	�ָ������ĳ��Ƶ���ķ���Ȩ��
//  Input:			CEntityPlayer *pPlayer		���ʵ��ָ��
//  Input:			int			  vChannel	    ���ָ����Ե�Ƶ��,Chattype.h �ļ������CHAT_CHANNELö��
//  Return:			void
//  Others:
//  Date:	02/01/2009
// **********************************************************  
void CChatModule::SetChannelTrue( int vCharID, int vChannel )
{
	CEntityPlayer *pPlayer = CSceneLogic::GetSingletonPtr()->GetPlayerByCharID( vCharID );
	if ( pPlayer == NULL )
	{
		return;
	}	
	CChat *tpChat = CChatManager::GetSingletonPtr()->GetChat( pPlayer );	
	if ( tpChat == NULL )
	{
		return;
	}
	tpChat->InitialChannel( pPlayer->GetRoleStatus(), 0 );	
	tpChat->SetChannel( vChannel, true );
	pPlayer->SetRoleStatus( tpChat->GetForbidenChannel() );
	pPlayer->SetRoleStatusParam( 0 );
}

// ***********************************************************
//  Function:		CheckDirtyWordOfMsg
//  Description:	���������Ϣ�е����
//  Input:			char *pMsg			��������
//  Input:			
//  Return:			void
//  Others:
//  Date:	03/16/2009
// **********************************************************
void CChatModule::CheckDirtyWordOfMsg( char *pMsg )
{
	if ( pMsg == NULL )
	{														
		return;
	}
	CDirtyWord::GetSingleton().OI_Dirty_Check( 1, ( char * )pMsg );
}


// ***********************************************************
//  Function:		CheckChatTime
//  Description:	��������ʱ������
//  Input:			char *pMsg			��������
//  Return:			int					���ؼ������ö��ֵ -1��ʾ����
//  Others:
//  Date:	03/16/2009
// **********************************************************
int CChatModule::CheckChatTime( int vChannel, char *pMsg, CChat *tpChat, bool bVip /* = false */ )
{ 
	if ( tpChat == NULL )
	{
		return -1;
	}
	int ChatLimitTime = 0;
	int MsgLimitTime  = 0;
	TimeLimit *tpTime = NULL;
	int tRet  = GetChannelTime( vChannel,tpChat, ChatLimitTime, MsgLimitTime, tpTime, bVip );
	if ( tRet == -1 )
	{
		return -1;
	}
	if ( tRet == 0 )
	{
		return TimeLimit::SendOk;
	}
	if ( tpTime == NULL )
	{
		return -1;
	}
	int Result = tpTime->CanSendMess( pMsg, ChatLimitTime, MsgLimitTime );
	if ( Result == TimeLimit::SendOk )		
	{
		return CHAT_SUCCESS;
	}
	else if ( Result == TimeLimit::INCOOLTIME )
	{
		 return ERROR_CHAT_INCOOLTIME;
	}
	else if( Result == TimeLimit::NotInTimeLimit )
	{
		return ERROR_CHAT_HIGHFREQUENCY;
	}
	else
	{  
		return ERROR_CHAT_MSGREPEATET;		
	}
}

// ***********************************************************
//  Function:		GetChannelTime
//  Description:	��ȡƵ��ʱ��������Ϣ
//  Input:			int vChannel			Ƶ��
//  Output:			int &ChatLimitTime		����������Ϣ֮���ʱ������
//  Output:			int &MsgLimitTime		һ�仰���������ε�ʱ������
//  Return:			int						�Ƿ���ʱ������ 1��ʾ�� 0��ʾû��
//  Others:
//  Date:	03/16/2009
// **********************************************************
int CChatModule::GetChannelTime( int vChannel, CChat *tpChat, int &ChatLimitTime, int &MsgLimitTime, TimeLimit *&tpTime, bool bVip /* = false */ )
{	
	if ( tpChat == NULL )
	{
		return -1;
	}
	int Result = 1;
	switch( vChannel )	
	{
		case CHANNEL_P2P:
			{
				ChatLimitTime = m_sChatCfg->mChatlimittime;
				MsgLimitTime  = m_sChatCfg->mMsglimittime;
				tpTime		  = &tpChat->CommonTimeLimit; 
				break;
			}			
		case CHANNEL_COMMON:
			{
				ChatLimitTime = m_sChatCfg->mChatlimittime;
				MsgLimitTime  = m_sChatCfg->mMsglimittime;
				tpTime		  = &tpChat->CommonTimeLimit; 
				break;
			} 		
		case CHANNEL_WORLD:
			{
				/*ChatLimitTime =	m_sChatCfg->mWorldautochattime;
				MsgLimitTime  =	0;
				tpTime		  = &tpChat->WorldTimeLimit;  */
				Result = 0;
				break;			   
			}							
		case CHANNEL_OTHERCOUNTRY:
			{
				Result = 0;
				break;
			} 		
		case CHANNEL_TEAM:
			{
				Result = 0;
				break;
			} 
		case CHANNEL_COUNTRY:
			{
				if ( bVip == true )
				{
					ChatLimitTime = m_sChatCfg->mCampviptime;
				}
				else
				{
					ChatLimitTime = m_sChatCfg->mCountrytime;
				}
				
				MsgLimitTime  = 0;
				tpTime		  = &tpChat->CounrtyTimeLimit; 
				break;
			}	
		case CHANNEL_FAMILY:
			{
				Result = 0;
				break;
			}		
		case CHANNEL_CORPS:
			{
				ChatLimitTime = m_sChatCfg->mChatlimittime;
				MsgLimitTime  = m_sChatCfg->mMsglimittime;
				tpTime		  = &tpChat->CommonTimeLimit;
				break;
			}		
		default:
			Result = 0;			
		break;
	}
	return Result;	
}

// ***********************************************************
//  Function:		CheckLevel
//  Description:	���ȼ��Ƿ���������Ƶ����Ҫ��
//  Input:			int vChannel			Ƶ��
//  Output:			CEntityPlayer *pPlayer	
//  Return:			int						1��ʾ�ȼ�����Ҫ�� 0��ʾ������Ҫ��   
//											-1��ʾ����
//  Others:
//  Date:	03/16/2009
// **********************************************************
int CChatModule::CheckLevel( int vChannel, CEntityPlayer *pPlayer )
{
	if ( pPlayer == NULL )
	{
		return -1;
	}
	int PlayerLevel = pPlayer->GetLevel();
	int Result		= 1;
	switch( vChannel )
	{
		case CHANNEL_WORLD:
		{
			Result = ( (unsigned int)PlayerLevel>=m_sChatCfg->mWorldlevellimit )?1:ERROR_CHAT_CHANNELWORLDLEVELLOW;
			break;
		}
		case CHANNEL_COUNTRY:
		{
			Result = ( (unsigned int)PlayerLevel>=MIN_COUNTRYCHANNEL_LEVEL )?1:ERROR_CHAT_CONTRYCHATLEVELLOW;
			break;
		}
		
		case CHANNEL_BUGLE:
		{
			Result = ( (unsigned int)PlayerLevel >=m_sChatCfg->mBuglelevellimit )?1:ERROR_CHAT_BUGLELEVELLIMIT;
			break;
		}
		default:
		break;
	}
	return Result;
}

// ***********************************************************
//  Function:		CheckAP
//  Description:	����缲AP�Ƿ����㷢��Ҫ��
//  Input:			int vChannel			Ƶ��
//  Output:			CEntityPlayer *pPlayer	
//  Return:			int						1��ʾ�ȼ�����Ҫ�� 0��ʾ������Ҫ��   
//											 -1��ʾ����
//  Others:
//  Date:	03/16/2009
// **********************************************************
int CChatModule::CheckAP( int vChannel, CEntityPlayer *pPlayer )
{
	if ( pPlayer == NULL )
	{
		return -1;
	}
	//int PlayerAP	= 0;	// GetAP
	int Result		= 1;
	switch( vChannel )
	{
		case CHANNEL_WORLD:
			{
			
				break;
			}
		default:
			break;
	}
	return Result;
}	 

// ***********************************************************
//  Function:		OnAutoChat
//  Description:	�����Զ���������Ϣ
//  Input:			int vChannel			Ƶ��
//  Output:			CEntityPlayer *pPlayer
//  Others:
//  Date:	03/16/2009
// **********************************************************
int CChatModule::OnAutoChat( CEntityPlayer *pPlayer, char *pMsg )
{
	LK_ASSERT( pPlayer != NULL, return -1 );	
	//if ( ConsumeChatItem( CDataStatic::sAutoChatItemId, 1, pPlayer ) == -1 )
	//{
	//	//���ĵ���ʧ�ܣ�ɾ�������е������Ϣ
	//	CChatManager::GetSingletonPtr()->AutoChat.DelAutoMess( pPlayer->GetCharID() );		
	//	SendChatResultMsg( pPlayer, CHANNEL_AUTOMSG, CHAT_STOPSAUTOCHAT, pMsg ); 					
	//	return -1;
	//}
	
	// �������ļ��
	int tBugleIndex = -1;
	int tNum		= 0;
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	tpProperty->GetBaggage()->HasItemOfCertainType( CTplItem::ITEM_AUTOSHOUT, tNum, tBugleIndex );
	if ( tNum < 1 || tBugleIndex < 0 )
	{						
		CChatManager::GetSingletonPtr()->AutoChat.DelAutoMess( pPlayer->GetCharID() );			
		SendChatResultMsg( pPlayer, CHANNEL_AUTOMSG, CHAT_STOPSAUTOCHAT, pMsg, NULL );			
		return -1;
	}
	
	CItemObject* tpItemObj = tpProperty->GetBaggage()->GetItemObjPtr( tBugleIndex );
	if( tpItemObj == NULL )
	{
		return -1;
	}

	uint64_t ullGUID = tpItemObj->GetGUID();
	int nTplID = tpItemObj->GetItemID();
	if( CPropertyModule::GetSingleton( ).PlayerRemoveItem( pPlayer, tBugleIndex, 1 ) == 0 )
	{
		LogEventLostItemByUse( pPlayer, ullGUID, nTplID, 1);
	}
	
	// �Զ������������
	if( mCurrentAutoChat.count == 0 )
	{ 		
		SendChatResultMsg( pPlayer, CHANNEL_AUTOMSG, CHAT_STOPSAUTOCHAT ,pMsg, pPlayer->GetCharName() );		
		return -1;
	}
	
	//֪ͨ��ҷ���һ���Զ��������ݳɹ�			
	SendChatResultMsg( pPlayer, CHANNEL_AUTOMSG, CHAT_SENDAUTOCHAT , pMsg, pPlayer->GetCharName(), mCurrentAutoChat.count );
	return 0;
}

// ***********************************************************
//  Function:		CheckChatMsg
//  Description:	����������Ϣ
//  Input:			int vChannel			Ƶ��
//  Input:			char *pMsg				������Ϣ
//  Input:			CEntityPlayer* pPlayer	
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::CheckChatMsg( CEntityPlayer* pPlayer, CChatContent* pChatContent, int IsAutoMess /* = 0 */ )
{	   
	LK_ASSERT( pPlayer != NULL && pChatContent != NULL, return ); 
	CChat *tpChat = CChatManager::GetSingleton().GetChat( pPlayer );
	LK_ASSERT( tpChat != NULL, return );   	
	
	// ��ҽ���������ж�		
	if ( tpChat->InChannel( (CHAT_CHANNEL) pChatContent->mChannel ) || tpChat->InChannel( CHANNEL_ALL ) )
	{
		// �����촥���Ƿ��Ѿ����
		if( time(NULL) > tpChat->GetForbidenFreeTime() )
		{
			CChatModule::GetSingleton().SetChannelTrue(pPlayer->GetCharID(), CHANNEL_ALL );
		}
		else
		{
			// TODO:���ͱ����Ե�֪ͨ
			SendChatResultMsg( pPlayer,  pChatContent->mChannel, CHAT_FORBIDDEN, NULL, NULL, tpChat->GetForbidenFreeTime() - time(NULL ) );
			//CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_CHAT_CHATFORBIDEN );
			return;
		}
	}
	
	int tRet = CheckChannelRule( pPlayer, pChatContent->mChannel );
	if ( tRet == -1 )
	{
		return;
	}
	
	if ( tRet != SUCCESS )
	{	
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, tRet );
		return;
	}
		
		
	// ��������Զ���������Ϣ�������ʼ��
	if ( IsAutoMess == 0 )
	{
		// �������GM˵�Ļ� �Ž��м��
		if ( !CGMModule::GetSingleton().IsGm( pPlayer->GetGmStatus() ) )
			CheckDirtyWordOfMsg( (char*)(pChatContent->mMsg.c_str()) );
	}
	
	// ���еȼ����Ƶļ��
	int LevelResult = CheckLevel( pChatContent->mChannel, pPlayer );
	LK_ASSERT( LevelResult != -1, return );		
	if ( LevelResult != 1 )
	{
		SendChatResultMsg( pPlayer, pChatContent->mChannel,LevelResult, pChatContent->mMsg.c_str(), pPlayer->GetCharName() );		
		return;
	}
	
	// ����ʱ�����Ƶļ��
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	tRet = CheckChatTime( pChatContent->mChannel, (char*)( pChatContent->mMsg.c_str() ), tpChat, tpProperty->IsVip() );	
	LK_ASSERT( tRet != -1, return );  		
	if ( tRet != CHAT_SUCCESS )
	{ 		
		// �Զ�������Ϣ�ӳٺ���
		if ( IsAutoMess == 1 ) 
		{ 			
			CChatManager::GetSingletonPtr( )->AutoChat.ChangeChatCount( pPlayer->GetCharID(), 1 );
		}
		SendChatResultMsg( pPlayer, pChatContent->mChannel, tRet, pChatContent->mMsg.c_str(), pPlayer->GetCharName() );		
		return;
	}
	
	// ���Զ��������ݽ��д���
	if ( IsAutoMess )
	{
		int tRet = OnAutoChat( pPlayer, (char*)(pChatContent->mMsg.c_str()) );
		if ( tRet == -1 )
		{
			return;
		}
	}
	
	// ͨ�ü����ϣ��ڸ�������Ƶ������������Ϣ
	ChatOnChannel( pPlayer, pChatContent ); 	
}	

// ***********************************************************
//  Function:		CheckChannelRule
//  Description:	���Ƶ������
//  Input:			int vChannel			Ƶ��
//  Input:			CEntityPlayer* pPlayer	
//  Output:			
//  Date:	03/16/2009
// **********************************************************
int CChatModule::CheckChannelRule( CEntityPlayer *pPlayer, int nChannel )
{
	LK_ASSERT( pPlayer != NULL, return -1 )	
	switch ( nChannel )
	{
		case CHANNEL_FAMILY:
		{
			if ( pPlayer->GetFamilyID() == 0 )
			{
				return	ERROR_CHAT_NOFAMILY;
			}
			break;
		}
		case CHANNEL_CORPS:
		{
			if ( pPlayer->GetCorpsID() == 0 )
			{
				return	ERROR_CHAT_NOCORP;
			}
			break;
		}
		default:
			break;			
	} 	
	return SUCCESS;
}

// ***********************************************************
//  Function:		ChatOnChannel
//  Description:	������Ƶ������������Ϣ
//  Input:			int vChannel			Ƶ��
//  Input:			char *pMsg				������Ϣ
//  Input:			char *SrcName				
//  Output:			
//  Date:	03/16/2009
// **********************************************************
void CChatModule::ChatOnChannel( CEntityPlayer* pPlayer, CChatContent* pChatContent )
{
	LK_ASSERT( pPlayer != NULL, return );
	LK_ASSERT( pChatContent != NULL, return );
	switch( pChatContent->mChannel )
	{
		case CHANNEL_P2P:
			{	
				ChatOnChannelP2P( pPlayer, pChatContent);
				SendChat2Log( pPlayer, pChatContent );
				break;
			}			
		case CHANNEL_COMMON:
			{ 		
				ChatOnChannelCommon( pPlayer, pChatContent );
				SendChat2Log( pPlayer, pChatContent );
				break;
			} 		
		case CHANNEL_WORLD:
			{ 		
				ChatOnChannelWorld( pPlayer, pChatContent );
				break;			   
			} 
		case CHANNEL_CORPS:
			{
				ChantOnChannelCorps( pPlayer, pChatContent);
				break;
			} 		
		case CHANNEL_FAMILY:			
			{			
				ChatOnChannelFamily( pPlayer, pChatContent );
				break;	
			} 			
		case CHANNEL_COUNTRY:
			{  		
				ChatOnChannelCountry( pPlayer,pChatContent );
				break;
			}
		case CHANNEL_OTHERCOUNTRY:
			{				
				break;
			} 
		case CHANNEL_BUGLE:
			{
				ChatOnChannelBugle( pPlayer, pChatContent);
				break;
			}	
		case CHANNEL_TEAM:
			{  		
				ChatOnChannelTeam( pPlayer, pChatContent );
				break;
			}
		case CHANNEL_BATTLE:
			{
				ChatOnChannelBattle( pPlayer, pChatContent );
				break;
			}
		default:		
			break;
	}
}

// ***********************************************************
//  Function:		SendSysNotice
//  Description:	����������Ϣ( GM�ӿ� )
//  Input:			const char *pMsg		������Ϣ
//  Input:			int RepeatedNum			�����ظ����͵Ĵ���
//  Input:				
//  Output:			
//  Date:	04/08/2009
// **********************************************************
void CChatModule::SendSysNotice( const char *pMsg, int RepeatedNum )
{
	//if ( pMsg == NULL || RepeatedNum <= 0 )
	//{
	//	return;
	//}
	//CMessage		MessageHead;
	//CMessageChatSendCallBack ChatCallBack;
	//ChatCallBack.mutable_router( )->set_srccharid( 0 );
	//ChatCallBack.mutable_router( )->set_descharid( 0 );
	//ChatCallBack.mutable_router( )->set_routertype( CMessageRouter::ROUTER_CHAR );
	//if ( pMsg != NULL )
	//{
	//	ChatCallBack.set_msg( pMsg );
	//}	
	//ChatCallBack.set_repeatednum( RepeatedNum );
	//ChatCallBack.set_channel( CHANNEL_SYS );  	
	//MessageHead.mutable_msghead()->set_messageid( ID_S2C_CHATSENDCALLBACK );	
	//MessageHead.set_msgpara( (int)&ChatCallBack );
	//CSceneLogic::GetSingleton().Send2Gate( &MessageHead );

	CMessage tMessage;
	CGMMessagePostBulletinCmd tGMPostBulletinMessage;

	tMessage.mutable_msghead()->set_messageid( ID_M2G_POSTBULLETIN_CMD );
	tMessage.set_msgpara( (uint32) &tGMPostBulletinMessage );

	tGMPostBulletinMessage.set_content( pMsg );
	tGMPostBulletinMessage.set_times(RepeatedNum);

	CSceneLogic::GetSingleton().Send2Gate( &tMessage );
}

// ***********************************************************
//  Function:		OnGateChatMsg
//  Description:	�����������صļ���;��ŵ���Ϣ
//  Input:			
//  Input:			
//  Input:				
//  Output:			
//  Date:	06/25/2009
// **********************************************************
void CChatModule::OnGateChatMsg( CMessage *pMsg )
{  
	/*LK_ASSERT( pMsg != NULL, return )	
	CEntityPlayer *tpPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( pMsg->mutable_msghead()->dstid() );
	if ( tpPlayer == NULL )
	{
		return;
	}
	CSceneLogic::GetSingleton().Send2Player( tpPlayer, pMsg );*/
}											

// �����������ݵ���־������ [2/5/2010 Macro]

void CChatModule::SendChat2Log(CEntityPlayer *pPlayer, CChatContent *npContent)
{
	if ( pPlayer == NULL || npContent == NULL )
	{
		return ;
	}

	// ϵͳ��Ϣ����¼
	if( npContent->mChannel == CHANNEL_SYS )
	{
		return;
	}

	// ������ ��Ҫ���˹ؼ���
	if( npContent->mChannel == CHANNEL_COMMON )
	{
		// �ж��Ƿ�����Ҫ��¼�Ĺؼ���(��8�ȼ������ǹؼ���)
		if ( CDirtyWord::GetSingleton().OI_Dirty_Check( 8, ( char * )npContent->mMsg.c_str(), 0 ) == 0 )
		{
			return;
		}
	}

	int tGateWayID = CSceneLogic::GetSingleton().GetWorldID();
	int tIp = pPlayer->GetClientInfo()->mClientAddr;

	LogEventSendChat( pPlayer->GetCharID(), pPlayer->GetName(), npContent->mMsg.c_str(), tGateWayID, npContent->mChannel, tIp );
	return ;
}


// ***********************************************************
//  Function:		InitialChatUserConfig
//  Description:	������������
//  Date:	12/07/2010
// **********************************************************
int CChatModule::InitialChatUserConfig()
{
	TiXmlDocument tDoc;
	LK_ASSERT( tDoc.LoadFile( CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(), const_cast<char*>("/chat/Chat.xml") )) == true, return -1 );
	TiXmlElement *tpRoot = tDoc.FirstChildElement( "UserConfig" );
	LK_ASSERT( tpRoot != NULL, return -1 )
	TiXmlElement *tpUserTypeElement = tpRoot->FirstChildElement( "UserType" );
	LK_ASSERT( tpUserTypeElement != NULL, return -1 )
	CChatManager::GetSingleton().InitializeChatUserList();
	for ( ; tpUserTypeElement != NULL; tpUserTypeElement = tpUserTypeElement->NextSiblingElement() )
	{
		CChatUser tChatUser;	
		if ( tpUserTypeElement->Attribute( "Type" ) != NULL )
		{
			tChatUser.mType = atoi( tpUserTypeElement->Attribute( "Type" ) );
		}
		
		for ( TiXmlElement *tpUserFlagElement = tpUserTypeElement->FirstChildElement( "UserFlag" );
				tpUserFlagElement != NULL; tpUserFlagElement = tpUserFlagElement->NextSiblingElement() )
		{
			if ( tpUserFlagElement->Attribute( "FlagID" ) != NULL )
			{
				tChatUser.mFlag = atoi( tpUserFlagElement->Attribute( "FlagID" ) );
			}
			
			if ( tpUserFlagElement->Attribute( "Priority" ) != NULL )
			{
				tChatUser.mPriority = atoi( tpUserFlagElement->Attribute( "Priority" ) );
			}
			
			CChatManager::GetSingleton().InsertChatUser( tChatUser );
		}
	}	
	return SUCCESS;	
}

// ***********************************************************
//  Function:		GetChatUserFlag
//  Description:	��ȡ��ҵ�������ݱ�־
//  Date:	12/07/2010
// **********************************************************
int CChatModule::GetChatUserFlag( CEntityPlayer *pPlayer, ChatCallBackMsg &rMsg )
{
	LK_ASSERT( pPlayer != NULL, return -1 )
	CChatUser tChatUser;
	CChatManager::GetSingleton().GetChatUserInfo( pPlayer, tChatUser );	
	rMsg.ChatCallBack.set_usertype( tChatUser.mType );
	rMsg.ChatCallBack.set_useflag( tChatUser.mFlag );
	rMsg.ChatCallBack.set_campid( pPlayer->GetNationality() );
	return SUCCESS;
}

void CChatModule::LoadChatUserConfigCallback(const char *pcConfigPath)
{
	CChatModule::GetSingleton().InitialChatUserConfig();
}