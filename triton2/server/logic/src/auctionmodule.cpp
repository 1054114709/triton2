#include "servercore.h"
#include <sys/stat.h>
#ifdef WIN32
#include <io.h>
#endif
#ifdef LINUX
#include <sys/io.h>
#endif
#include <stdio.h>
#include "westserver.h"
#include "tinyxml.h"
#include "mailmessage.h"


char CAuctionModule::sModuleName[ NAME_LENGTH ] = "Auction";

CAuctionManager* gpAuctionManager = NULL;

// ����������
void CAuctionModule::OnLaunchServer( )
{
	gpAuctionManager = new CAuctionManager;
	if( gpAuctionManager == NULL )
		return;

	CModuleManager::GetSingletonPtr()->RegisterFunc( CLogicFunc( "Auction.OpenAuction", this,
            ( CLogicFunc::InvokeProc )&CAuctionModule::OnAuctionOpen ) );
    CModuleManager::GetSingletonPtr()->RegisterFunc( CLogicFunc( "Auction.CloseAuction", this,
            ( CLogicFunc::InvokeProc )&CAuctionModule::OnAuctionClose ) );
}

// �˳�������
void CAuctionModule::OnExitServer( )
{
	if( gpAuctionManager != NULL )
		delete gpAuctionManager;

}

// ������Timer
void CAuctionModule::OnTimer( unsigned int vTickCount, unsigned int vTickOffset )
{
}

// ��������
int CAuctionModule::OnCreateMap( unsigned short vLineID, unsigned short vMapID, const char* pTplName )
{
	return SUCCESS;
}

// ·����Ϣ
void CAuctionModule::OnRouterMessage( CMessageRouter* pMessage )
{
	//switch( pMessage->mMessageID )
}

// �ͻ��˷�����Ϣ
void CAuctionModule::OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	switch( pMessage->mMessageID )
	{
		default:
			break;
	}
}

// ����ʵ��
void CAuctionModule::OnCreateEntity( CEntity* pEntity, CCreator* pCreator, bool vFirst)
{
	if( pEntity->mEntityType == ENTITYTYPE_PLAYER )
	{
		CEntityPlayer* tpPlayer = (CEntityPlayer*)pEntity;
	}
}

// ����ʵ��
void CAuctionModule::OnDestroyEntity( CEntity* pEntity, int vCode )
{
	if( pEntity->mEntityType == ENTITYTYPE_PLAYER )
	{
		CEntityPlayer* tpPlayer = (CEntityPlayer*)pEntity;
	}
}

bool CAuctionModule::OnSaveData( CEntityPlayer *pPlayer, int vSaveCode )
{
	return true;
}

void CAuctionModule::OnAuctionOpen( CDispParams *pParams, CVariant *pResult )
{
	if( pParams->mNumberOfArgs != 1 )
		return;
	int tCharID = pParams->mVariants[ 0 ].mLongValue;
}

void CAuctionModule::OnAuctionClose( CDispParams *pParams, CVariant *pResult )
{
	CMessageAuctionEndCallBack tCallBack;
    if( pParams->mNumberOfArgs != 1 )
        return;
    int tCharID = pParams->mVariants[ 0 ].mLongValue;
}

