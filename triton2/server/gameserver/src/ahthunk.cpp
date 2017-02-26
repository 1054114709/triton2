#include "stdafx.hpp"
#include "ahthunk.h"
#include "scenelogic.h"
#include "coremessage_pb.hxx.pb.h"

#ifdef _ANTIBOT_
#include "ApexProxy.h"
#include <pthread.h>
#endif

template<> CAHContorlManager* CSingleton< CAHContorlManager >::spSingleton = NULL;

CAHContorlManager::CAHContorlManager()
{
	if( CObj::msCreateMode )
		mPlayerDelayProcList.initailize();
}


CAHContorlManager::~CAHContorlManager()
{

}

int CAHContorlManager::OnTimer( unsigned int vTickCount, unsigned int vTickOffset )
{
	/*
	 * Ŀǰ�Ĵ����붼��λ������û�з�1,4,6 ��ͷ�Ĵ�����
	 * a. ��1,6��ͷ��47200���ȴ���ŵ���ʾ����Ϣ������������ӶϿ�����
	 * b. 47001��47011�����ֵ�ǰԭ�򲻱䣨�ͻ��˶࿪) 
	 * c. �������ţ���4��ͷ�ģ����Ե����������������
	 *
	 */

 	APEX* pApexCfg = CSceneCfgManager::GetSingletonPtr()->GetApex();

	for( PLAYERID_VEC::iterator it = mPlayerDelayProcList.begin(); it != mPlayerDelayProcList.end(); ++it )
	{
		if( it->second.mReason == (int)(pApexCfg->mMulti_client) )
		{
			CSceneLogic::GetSingletonPtr()->KickPlayer( it->first, EM_KICKOUT_ANTIBOT_MULTICLIENT );
		}
		else if( it->second.mReason == (int)(pApexCfg->mVm )  ) 
		{
			CSceneLogic::GetSingletonPtr()->KickPlayer( it->first, EM_KICKOUT_ANTIBOT_VM );
		}
		else if( it->second.mReason == (int)(pApexCfg->mMulti_user ) )
		{
			CSceneLogic::GetSingletonPtr()->KickPlayer( it->first, EM_KICKOUT_ANTIBOT_MULTIUSER );
		}
		else if( it->second.mReason == 47200 
			|| (it->second.mReason  >= 10000 && it->second.mReason  < 20000)
			|| (it->second.mReason  >= 60000 && it->second.mReason  < 70000))
		{
			CSceneLogic::GetSingletonPtr()->KickPlayer( it->first, EM_KICKOUT_ANTIBOT_OTHER );
		}
		else
		{
			CSceneLogic::GetSingletonPtr()->KickPlayer( it->first, EM_KICKOUT_ANTIBOT );
		}
	}

	mPlayerDelayProcList.clear();

	return 0;
}


// ���뵽�ӳ������б���
int CAHContorlManager::AddToDelayProcessList( const CAHDelayData& rDelayData )
{
	mPlayerDelayProcList.insert( std::pair<int,CAHDelayData>( rDelayData.mCharID, rDelayData ) );
	return 0;
}



#ifdef _ANTIBOT_

// �̻߳����ź���
static pthread_mutex_t g_stGlobalMutex;	

// ������պ���
_FUNC_S_REC pfRec = NULL;

#endif

/* GameServer�ṩ��Apex Proxy �ķ��ͺ���;
������pBuffer: �������ݵĻ�����
nLen : �������ݵĳ���
*/
long NetSendToGameClient(signed int nSendId,const char * pBuffer,int nLen)
{
#ifdef _ANTIBOT_
	// ����
	pthread_mutex_lock( &g_stGlobalMutex);

	LOG_DEBUG( "default", "send antidata to client, player %d len %d", nSendId, nLen );

	CMessage tMessage;
	CMessageSendAntiBotDataToClientNotify tAntiBotMsg;

	tMessage.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_SERVERANTIBOTDATA );
	tMessage.set_msgpara( (uint32)&tAntiBotMsg );

	tAntiBotMsg.set_serverdata( (const void*)pBuffer, nLen );
	tAntiBotMsg.set_length( nLen );

	CSceneLogic::GetSingletonPtr()->Send2Player( nSendId, &tMessage );

	// ����
	pthread_mutex_unlock( &g_stGlobalMutex);

#endif
	return 0;
}

/* GameServer�ṩ�����˺���
����:nId: ��ҵ�id
ʵ���������,��һ�����������;
*/
long GameServerKillUser(signed int nId, int nAction)
{
#ifdef _ANTIBOT_

	// ����
	pthread_mutex_lock( &g_stGlobalMutex);

	LOG_INFO( "default", "[%s:%d] AS Server kill %d, reason %d", __FUNCTION__, __LINE__, nId, nAction );

	CAHDelayData tDelayData;
	tDelayData.mCharID = nId;
	tDelayData.mReason = nAction;

	CAHContorlManager::GetSingletonPtr()->AddToDelayProcessList( tDelayData );

	// ����
	pthread_mutex_unlock( &g_stGlobalMutex);
#endif
	return 0;
}


int StartApexProxy()
{
#ifdef _ANTIBOT_

	APEX* tpApex = CSceneCfgManager::GetSingletonPtr()->GetApex();
	if( tpApex != NULL )
		INIT_ROLLINGFILE_LOG( tpApex->mIdentifier, tpApex->mDirectory, ( LogLevel ) tpApex->mPriority , tpApex->mMaxfilesize, tpApex->mMaxbackupindex);	

	//���밴����˳�����;
	//1 . CHSStart ;2 . CHSSetFunc
	CHSStart(NetSendToGameClient,pfRec);
	CHSSetFunc((void*)(GameServerKillUser),FLAG_KILLUSER);
	LOG_NOTICE( "apex", "ApexProxy Start ... ");

	// ��ʼ���̻߳����ź���
	if( pthread_mutex_init( &g_stGlobalMutex, NULL ) != 0 )
	{
		LOG_FATAL( "default", "thread mutex for antibot moudle init failed. so exit" );
		exit(-1);
		return -1;
	}
#endif
	return 0;
}

//���� :ֹͣApexProxy
int StopApexProxy()
{
#ifdef _ANTIBOT_
	CHSEnd();
	LOG_INFO( "default", "ApexProxy Stop ... ");
#endif
	return 0;
}

//
//����      :֪ͨ,ApexProxy,��ҽ���;
//          DoDataRec �е���;
//����
//nSendId  ��ҵ�id
int NoticeApexProxy_UserLogin( int nSendId )
{

#ifdef _ANTIBOT_

	LOG_NOTICE( "apex", "Player %d Login, Notify AS Server", nSendId );

	//Ҫ��֤,ÿһ�����,�����ʱ��,�������������;
	//Apex Proxy ֻ����һ����� ֻ���� 1 �� �������;
	//����,nSendId,���������������ҵ�Id
	if(pfRec)
	{
		CEntityPlayer* pPlayer = CSceneLogic::GetSingletonPtr()->GetPlayerByCharID( nSendId );
		if( pPlayer == NULL )
		{
			return -1;
		}

		pfRec('L',nSendId, pPlayer->GetCharNameShow(), strlen( pPlayer->GetCharNameShow() ) );

		char szBuf[5] = {0};

		szBuf[0] = 1;
		memcpy( (void*)(&szBuf[1]), (const void*)(&pPlayer->GetClientInfo()->mClientAddr), sizeof(int) );

		pfRec('S',nSendId,(const char*)szBuf,5);
	}
#endif

	return 0;
};


int	NoticeApexClient_Ret(int nSendId, const char * pRet)
{
#ifdef _ANTIBOT_
	if(pfRec)
	{
		pfRec('R',nSendId,(char*)pRet,4);
	}
#endif
	return 0;
}



//
//����    :֪ͨ,ApexProxy,����뿪;
//         DoDataRec �е���;
//����
//nSendId  ��ҵ�id
int	NoticeApexProxy_UserLogout( int nSendId )
{
#ifdef _ANTIBOT_

	LOG_NOTICE( "apex", "Player %d Logout, Notify AS Server", nSendId );

	//Ҫ��֤,ÿһ�����,�뿪��ʱ��,�������������;
	//Apex Proxy ����һ����� ���ü��� �������;
	CEntityPlayer* pPlayer = CSceneLogic::GetSingletonPtr()->GetPlayerByCharID( nSendId );
	if( pPlayer == NULL )
	{
		return -1;
	}

	if(pfRec)
	{
		pfRec('G',nSendId, pPlayer->GetCharNameShow(),strlen(pPlayer->GetCharNameShow()));
	}
#endif
	return 0;
}; 



//
//����     :֪ͨ,AepxProxy,�����ݵ���;;
//         DoDataRec �е���;
//����
//nSendId ��ҵ�id
//pBuf     : �������ݵĻ�����
//nBufLen  : �������ݵĳ���
int	NoticeApexProxy_UserData(int nSendId,const char * pBuf,int nBufLen)
{
#ifdef _ANTIBOT_
	if(pfRec)
	{
		pfRec('T',nSendId,pBuf,nBufLen);
	}
#endif
	return 0;
}; 




