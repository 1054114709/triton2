#include "stdafx.hpp"
#include "code_queue.h"
#include "clienthandle.h"
#include "macro.h"
#include "message_pb.hxx.pb.h"
#include "scenelogic.h"
#include "client_comm_engine.h"
#include "message_dispatcher.h"
#include "coremessage_pb.hxx.pb.h"
#include "message_factory.h"
#include "mapmessage_pb.hxx.pb.h"
#include "promessage_pb.hxx.pb.h"

CSharedMem* CClientHandle::mShmPtr = NULL;

char CClientHandle::msMessageBuff[ MAX_EMULATOR_MSG_BUF ] = {0};
extern char g_szRunPath[256];
extern int g_nFtokParam;
CClientHandle::CClientHandle()
{
	int size = sizeof(CSharedMem) + CCodeQueue::CountQueueSize(MAX_PIPE_SIZE);

	//char szCmd[ FILE_MAX_PATH ] = {0};

	//snprintf(szCmd, sizeof(szCmd)-1,"touch %s", "./scpipefile");
	//system(szCmd);

	//snprintf(szCmd, sizeof(szCmd)-1,"touch %s", "./cspipefile");
	//system(szCmd);

	char tPipeFileAddr[500] = {0};
	strncpy(tPipeFileAddr, g_szRunPath, 499 );
	strcat( tPipeFileAddr, "/scpipefile" );
	unsigned int tkeys2c = MakeKey( tPipeFileAddr, 'O' );
	LOG_NOTICE( "default", "make tkeys2c key use %s...\n", tPipeFileAddr );
	if ( g_nFtokParam != 0 )
	{
		unsigned int iKeyOld = tkeys2c;
		tkeys2c |= g_nFtokParam;
		printf("ftok scpipefile got key %x, new key is %x\n", iKeyOld, tkeys2c );
	}

	strncpy(tPipeFileAddr, g_szRunPath, 499 );
	strcat( tPipeFileAddr, "/cspipefile" );
	unsigned int tkeyc2s = MakeKey( tPipeFileAddr, 'I' );
	LOG_NOTICE( "default", "make tkeyc2s key use %s...\n", tPipeFileAddr );
	if ( g_nFtokParam != 0 )
	{
		unsigned int iKeyOld = tkeyc2s;
		tkeyc2s |= g_nFtokParam;
		printf("ftok cspipefile got key %x, new key is %x\n", iKeyOld, tkeyc2s );
	}

	// ����-1Ϊʧ��
	if( tkeys2c == (unsigned int)(-1) ||  tkeyc2s == (unsigned int)(-1) )
	{
		printf( "make shm key failed. s2ckey %d, c2skey %d, strerror %s \n", tkeys2c, tkeyc2s, strerror(errno ) );
		LOG_ERROR( "default", "make shm key failed. s2ckey %d, c2skey %d, strerror %s", tkeys2c, tkeyc2s,  strerror(errno ) );	
		exit(-1);
	}

	LOG_NOTICE("default", "scpipefile %08X, cspipefile %08X", tkeys2c, tkeyc2s );

	BYTE* tpS2CPipe = CreateShareMem ( tkeys2c, size);
	BYTE* tpC2SPipe = CreateShareMem ( tkeyc2s, size);

	LK_ASSERT( ( tpS2CPipe != NULL ) && ( tpC2SPipe != NULL ), exit(1) );

	CSharedMem::pbCurrentShm = tpC2SPipe;
	CCodeQueue::pCurrentShm = new CSharedMem( tkeyc2s, size );
	mC2SPipe = new CCodeQueue( MAX_PIPE_SIZE, IDX_PIPELOCK_C2S );

	CSharedMem::pbCurrentShm = tpS2CPipe;
	CCodeQueue::pCurrentShm = new CSharedMem( tkeys2c, size );
	mS2CPipe = new CCodeQueue( MAX_PIPE_SIZE, IDX_PIPELOCK_S2C );

	LK_ASSERT( ( mC2SPipe != NULL ) && ( mS2CPipe != NULL ), exit(1) );


	if ( mShmPtr->GetInitMode( ) == SHM_INIT )
	{
		LOG_DEBUG( "default" , " ClientHandle Initailize" );
		Initialize( );
	} 
	else
	{
		LOG_DEBUG( "default" , " ClientHandle Resume" );
		Resume( ); 
	}
}


CClientHandle::~CClientHandle()
{

}

int CClientHandle::Initialize( )
{
	return 0;
}


void* CClientHandle::operator new( size_t size )
{
	return ( void* ) mShmPtr->CreateSegment( size );
}

void  CClientHandle::operator delete( void* pointer ) 
{ 
}

void* CClientHandle::operator new(size_t size, const char* file, int line)
{
	return operator new(size);
}
void CClientHandle::operator delete(void* pointer, const char* file, int line) {}

int CClientHandle::Resume( )
{
	return 0;
}

unsigned int CClientHandle::CountSize()
{
	return sizeof( CClientHandle );
}


// ***************************************************************
//  Function:		������Ϣ���ͻ���
//  Description:	Send
//	Input:			
//	OutPut:			
//	Return:			
//	Others:			������ض���Ϣid, ���ڷ����Ժ�tcpsvrd���Զ��Ͽ���ͻ��˵�socket����
//					Game ==> Tcpsvrd ���ṹ: CNetHead+2Bytes+MsgCode
//  Date:			02/12/2009
// 
// ***************************************************************
int CClientHandle::Send(CMessage* pMsg, std::vector<CEntityPlayer*>* pPlayerSet )
{
	LK_ASSERT( pMsg != NULL && pPlayerSet != NULL , return -1 );

	// message �������л�
	//TODO: ����ѷ���buffer��Ϊ���buffer+128, ��Ϊ��Ϣ���л����ټ��ܻ���18Bytes����; �ܰ�����ȻС��tcpsvrd�˵�������32752
	static BYTE tMessageBuff[MAX_PACKAGE_LEN+128] = {0};
	unsigned short tMessageBuffLen = sizeof(tMessageBuff);
	if( ClientCommEngine::ConvertMsgToClientCode3( pMsg, tMessageBuff, tMessageBuffLen ) < 0 )
	{
		LOG_FATAL( "default", "[%s:%d] message %d serialize too long", __FUNCTION__, __LINE__, pMsg->msghead().messageid() );
		return -1;
	}

	for( std::vector<CEntityPlayer*>::iterator it = pPlayerSet->begin(); it != pPlayerSet->end(); ++it )
	{
		CEntityPlayer* pPlayer = *it;
		if( pPlayer == NULL )
		{
			continue;
		}
		
		Send( pPlayer, tMessageBuff, tMessageBuffLen, pMsg );
	}
	
	return 0;
}

//************************************
// Method:    Send
// FullName:  CClientHandle::Send
// Access:    public 
// Returns:   int 0 �ɹ��� !0 ʧ��
// Qualifier: �������л������Ϣ2���Ƹ�������� �������л������Ϣ2���Ƹ��������
//				�ú�����Ҫ��Ϊ���������ܣ���ȥ��װvector�ĳɱ������л�һ�Σ����Ͷ�Ρ�
// Parameter: CEntityPlayer * pPlayer  ���
// Parameter: BYTE * pMessageBuff	���л������Ϣ2����
// Parameter: int nLen				���л����2���Ƴ���
// Parameter: CMessage * pMsg		ԭʼ��Ϣ����Ҫ��Ϊ����Send�ڲ���¼��־����ӡ��Ϣ����, ͳ����ϢID) 
//************************************
int CClientHandle::Send(CEntityPlayer* pPlayer, BYTE* pMessageBuff, int nLen, CMessage* pMsg )
{
	LK_ASSERT( pPlayer != NULL , return -1 );

	//TODO: ����ѷ���buffer��Ϊ���buffer+128, ��Ϊ��Ϣ���л����ټ��ܻ���18Bytes����; �ܰ�����ȻС��tcpsvrd�˵�������32752
	static BYTE tCodeBuf[MAX_PACKAGE_LEN+128] = {0};
	short tCodeLength = sizeof(tCodeBuf);

	// ��ʱCNetHeadָ��
	CNetHead *pNetHead = (CNetHead*)(&tCodeBuf[0]);

	// ��ʾ�Ƿ���tcpserver���������Ϣ���Զ����Ӧ�ͻ��˶Ͽ�����
	if( pMsg->mutable_msghead()->messageid() == ID_S2C_NOTIFY_DISCONNECT )
	{
		pNetHead->mSrcPort = 1; 
	}
	else
	{
		pNetHead->mSrcPort = 0;
	}

	unsigned short tLen = 0;
	char* pCodeBuff = (char*)&tCodeBuf[0];

	// �ճ�����NetHead����
	pCodeBuff += sizeof(CNetHead);
	tLen += sizeof(CNetHead);

	// �ճ��ܳ���
	pCodeBuff += sizeof(unsigned short);
	tLen += sizeof(unsigned short);

	//TODO: CSHead�������л����Ż��� ����CSHead��δ���������ã���ʱ����ͻ���Ĭ�Ͻ���0���������������������ִ���
	//CCSHead tCSHead;

	*(unsigned short*)pCodeBuff = (unsigned short)0;
	pCodeBuff += sizeof(unsigned short);
	tLen += sizeof(unsigned short);	

	//tCSHead.SerializeToArray( pCodeBuff, tCodeLength-tLen );
	//pCodeBuff += tCSHead.GetCachedSize();
	//tLen += tCSHead.GetCachedSize();

	int tEncryptLen  = tCodeLength - tLen;

	if ( *(pPlayer->GetKey( )) != 0 )
	{
		ClientCommEngine::EncryptData( EnCryptType1, (unsigned char*)pPlayer->GetKey( ), pMessageBuff, nLen, (unsigned char*)pCodeBuff, &tEncryptLen );
	}
	else
	{
		ClientCommEngine::EncryptData( EnCryptType1,  ClientCommEngine::tpKey, pMessageBuff, nLen, (unsigned char*)pCodeBuff, &tEncryptLen );
	}

	// NetHead
	pNetHead->mDstIP = pPlayer->GetClientInfo( )->mSockTime;
	pNetHead->mDstPort = pPlayer->GetClientInfo( )->mSockIndex;

	//TODO: �Ӹ��жϣ���ʲôʱ���0��
	if( pNetHead->mDstPort < 1 )
	{
		LOG_ERROR( "default", "player [%d:%d:%s] sockindex error %d", pPlayer->GetEntityID(), pPlayer->GetCharID(), pPlayer->GetCharNameShow(), pPlayer->GetClientInfo( )->mSockIndex );
		return -1;
	}

	// �ܳ���
	unsigned short usTotalLength = (unsigned short) (tEncryptLen+tLen);
	if( usTotalLength > MAX_PACKAGE_LEN )
	{
		LOG_FATAL( "default", "message %d too big after encode",  pMsg->msghead().messageid() );
		return -1;
	}

	*((unsigned short*)&tCodeBuf[sizeof(CNetHead)]) = (unsigned short) (usTotalLength-sizeof(CNetHead));

	int tRet = mS2CPipe->AppendOneCode ( tCodeBuf, usTotalLength );
	if ( tRet < 0 )
	{
		LOG_ERROR( "default", "In CClientHandle::Send(),  AppendOneCode return %d", tRet );
		return -1;
	}

	// ����Ǳ�׷�ٵ��ʺ���д��־
	if ( pPlayer->GetIfTracePlayer() )
	{	 
		pPlayer->WriteMsgInfo( pMsg, 0 );
	}

#ifdef _DEBUG_
	Message* pUnknownMessagePara = (Message*) pMsg->msgpara();
	LK_ASSERT( pUnknownMessagePara != NULL, return -1 );
	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessagePara->GetDescriptor();
	// ��ʱ�øñ�����ʾ�ò��ô���־
	if( pMsg->mutable_msghead()->messageid() != ID_C2S_NOTICE_ENTITYPATH 
		&& pMsg->mutable_msghead()->messageid() != ID_S2C_RESPONSE_PING
		)
	{
		LOG_DEBUG( "default", "---- Send To Client( %d | %s ) Msg[ %s ][id: 0x%04x/%d] ----", 
			pPlayer->GetEntityID(),pPlayer->GetCharNameShow(), pDescriptor->name().c_str(), 
			pMsg->msghead().messageid(), pMsg->msghead().messageid());

		LOG_DEBUG( "default", "[%s]", ((Message*)pMsg->msgpara())->ShortDebugString().c_str() );
	}
#endif
	return 0;
}


int CClientHandle::Recv()
{

	BYTE tTempCodeBuf[MAX_PACKAGE_LEN] = {0};
	int tTempCodeLength = sizeof(tTempCodeBuf);

	int tTempRet = mC2SPipe->GetHeadCode((BYTE *)tTempCodeBuf, &tTempCodeLength);

	if ( tTempRet < 0 )
	{
		LOG_ERROR( "default", "When GetHeadCode from C2SPipe, error ocurr %d", tTempRet );
		return CLIENTHANDLE_QUEUE_CRASH;
	}

	if ( tTempCodeLength == 0 )
	{
		return CLIENTHANDLE_QUEUE_EMPTY;
	}

	if( tTempCodeLength < (int)sizeof(CNetHead) )
	{
		return CLIENTHANDLE_CODE_NOTINTEGRITY;
	}

	CCSHead tCSHead;
	CMessage tMessage;
	
#ifdef _USE_MESSAGE_QUEUE_
	
	BYTE tMsgPara[MAX_PACKAGE_LEN] = {0};
	unsigned short tusParLen = sizeof(tMsgPara); 
	if ( DecodeNetMsg( tTempCodeBuf, tTempCodeLength, &tCSHead, &tMessage, tMsgPara, tusParLen ) < 0 )
	{
		return CLIENTHANDLE_DECODE_FAILED;
	}

	// ��ʱ����Ϣ���ͱ�ʾ��� charid
	tMessage.mutable_msghead()->set_msgtype( tCSHead.uin() );

	if ( CMessageDispatcher::GetSingletonPtr()->AppendMsg( &tMessage, (void*)tMsgPara, tusParLen ) < 0 )
	{
		return CLIENTHANDLE_QUEUE_CRASH;
	}

#else

	int nRet = DecodeNetMsg( tTempCodeBuf, tTempCodeLength, &tCSHead, &tMessage  );
	if ( nRet < 0 )
	{
		return CLIENTHANDLE_DECODE_FAILED;
	}
	else if( nRet > 0 )
	{
		// ��������Ѿ��ɹ�����Ϣ�Ѿ���������ʱҪ���ٵ�
		if( tMessage.msgpara() != 0 )
		{
			CMessage* pMsgPara = (CMessage*)tMessage.msgpara();

			#ifdef _USE_MESSAGE_BUFF_ // ���ʹ����placement new, ��ֻ����Ϣ����
					pMsgPara->~Message();
			#else
					delete pMsgPara;
			#endif

			tMessage.set_msgpara(0);
		}

		return CLIENTHANDLE_WRONG_SOCKSTATE;

	}


	CMessageDispatcher::GetSingletonPtr()->ProcessMessage( &tMessage );

#endif

	return CLIENTHANDLE_SUCCESS;
}


// ***************************************************************
//  Function:		DecodeNetMsg
//  Description:	������Ϣ���а汾���Ľ��ܺͷ����л�����
//	Input:			
//	OutPut:			
//	Return:			
//	Others:			ֱ�Ӱ������ϵ�2���ư������ܺͷ����л���CCSHead��CMessage����δ�������л�����Ϣ��ӳ���	
//  Date:			02/10/2009
// 
// ***************************************************************
//int CClientHandle::DecodeNetMsg( BYTE* pCodeBuff, int& vLen, CCSHead* pCSHead, CMessage* pMsg, BYTE* pMsgPara, unsigned short& usParaLen )
//{
//	LK_ASSERT( pCodeBuff != NULL && vLen >= sizeof(CNetHead) && vLen < 0xffff && pMsg != NULL, return -1 );
//
//	BYTE* pBuff = pCodeBuff;
//	int tLen = vLen;
//
//	//TODO: Ӧ�����Ƚ��� ����Ҫ�Ļ�������ѹ����
//	CNetHead tNetHead;
//	tNetHead.ParseFromArray( pBuff, sizeof(CNetHead) );
//	pBuff += tNetHead.Size();
//	tLen -= tNetHead.Size();
//
//	// ��tcpserver �ϵ�socket index 
//	short tSockIndex = tNetHead.mDstPort[0];
//
//	// �Ƿ��Ƕ�����Ϣ
//	if( tNetHead.mState < 0 )
//	{
//		LOG_DEBUG( "default", "client commhandle %d closed ", tSockIndex );
//
//		// ����Ƿ�����
//		CEntityPlayer* tpPlayer = SceneServer::CSceneLogic::GetSingletonPtr()->GetPlayerByComm( tSockIndex );
//		if( tpPlayer == NULL )
//		{
//			LOG_ERROR( "default", "[%s:%d][%s], socket %d has closed", __LK_FILE__, __LINE__, __FUNCTION__, tSockIndex );
//			return  -1;
//		}
//		else
//		{
//			// �ж��Ƿ���ͬһ�����
//			if( tpPlayer->GetClientInfo( )->mSockTime != tNetHead.mDstIP[0] )
//			{
//				LOG_ERROR( "default", "[%s:%d][%s], sock time not match (%d != %d)", 
//					__LK_FILE__, __LINE__, __FUNCTION__, tpPlayer->GetClientInfo( )->mSockTime, tNetHead.mDstIP[0] );
//				return -1;
//			}
//			else
//			{
//				// ������Comm����
//				if (tSockIndex != tpPlayer->GetCommHandle( )) 
//				{
//					LOG_DEBUG("default", "FATAL ERROR: nethead.SockIndex = %d, but player.SockIndex = %d",  
//								tSockIndex, tpPlayer->GetCommHandle( ));
//				}
//
//				SceneServer::CSceneLogic::PLAYERID_MAP::iterator tCommIter = 
//					SceneServer::CSceneLogic::GetSingletonPtr()->mPlayerCommIndex.find( tSockIndex);
//
//				if ( tCommIter != SceneServer::CSceneLogic::GetSingletonPtr()->mPlayerCommIndex.end() )
//				{
//					SceneServer::CSceneLogic::GetSingletonPtr()->mPlayerCommIndex.erase(tCommIter);
//					LOG_DEBUG("default", "remove fd(%d) from mPlayerCommIndex", tSockIndex);
//				}
//
//				// ģ��������Ϣ, ֪ͨ���߼�ģ��
//				CMessageHead* tpHead = pMsg->mutable_msghead();
//				tpHead->set_srcfe ( FE_CLIENT );
//				tpHead->set_srcid ( tpPlayer->get_id() );
//				tpHead->set_messageid( ID_C2S_REQUEST_LEAVEGAME );
//
//				CMessageLeaveGameRequest tMsgPara;
//				// ����������
//				tMsgPara.set_leavetype(1);
//
//				if( tMsgPara.SerializeToArray( pMsgPara+sizeof(unsigned short), usParaLen ) != true )
//				{
//					LOG_ERROR( "default", "[%s:%d][%s] searilize error", __LK_FILE__, __LINE__, __FUNCTION__ );
//					return -1;
//				}
//				else
//				{
//					usParaLen = tMsgPara.ByteSize() /*+ sizeof(unsigned short)*/;
//					*((unsigned short*)pMsgPara) = usParaLen;
//					return CLIENTHANDLE_SUCCESS;
//				}
//
//			}
//		}
//
//	}
//
//	// �������
//		   
//	int nRet = -1;
//	CEntityPlayer* tpCommPlayer = SceneServer::CSceneLogic::GetSingletonPtr()->GetPlayerByComm( tSockIndex );
//	if ( tpCommPlayer == NULL )
//	{
//		nRet = ClientCommEngine::ConvertClientCodeToMsg2( (void*)pBuff, (unsigned short)tLen, pCSHead, pMsg, (void*)pMsgPara, usParaLen, ClientCommEngine::tpKey );
//	}
//	else
//	{
//		if ( *(tpCommPlayer->GetKey( )) == 0 )
//		{
//			nRet = ClientCommEngine::ConvertClientCodeToMsg2( (void*)pBuff, (unsigned short)tLen, pCSHead, pMsg, (void*)pMsgPara, usParaLen, ClientCommEngine::tpKey );
//		}
//		else
//		{
//			nRet = ClientCommEngine::ConvertClientCodeToMsg2( (void*)pBuff, (unsigned short)tLen, pCSHead, pMsg, (void*)pMsgPara, usParaLen, (unsigned char *)tpCommPlayer->GetKey( ) );
//		}
//		
//	}
//
//	if( nRet < 0 )
//	{
//		LOG_ERROR( "default", "convert code failed %d, len %d, socket index %d ", nRet, tLen, tSockIndex  );
//#ifdef _DEBUG_
//		if( tpCommPlayer != NULL )
//		{
//			Log_bin( "default", tpCommPlayer->GetKey( ), KEYLEN );
//			LOG_DEBUG( "default", "try to use static key to decrypte player %s's msg..", tpCommPlayer->GetCharNameShow() );
//			nRet = ClientCommEngine::ConvertClientCodeToMsg2( (void*)pBuff, (unsigned short)tLen, pCSHead, pMsg, (void*)pMsgPara, usParaLen, (unsigned char *)ClientCommEngine::tpKey );
//			if( nRet == 0 )
//			{
//				LOG_DEBUG( "default", "use static key success, messge id is %d, csdialog id %d", pMsg->msghead().messageid(), pCSHead->dialogid() );
//				//LOG_DEBUG( "default", "[MsgPara: %s]", ((Message*)pMsg->msgpara())->ShortDebugString().c_str() );
//			}
//		}
//#endif
//		return -1;
//	}
//
//	CMessageHead* tpHead = pMsg->mutable_msghead();
//
//	// �߼����ж��Ƿ��������ڿͻ���ʵ�����Ϣ
//	//if( tpHead->srcfe() != FE_CLIENT )
//	//{
//	//	LOG_ERROR( "default", "invalid fe %d, msg id 0x%04x", tpHead->srcfe(), tpHead->messageid() );
//	//	return -1;
//	//}
//
//
//	// �Ƿ��ǡ��״Ρ�����
//	int nDialogID = (int)pCSHead->dialogid( ); 
//	if( nDialogID <= 0 )
//	{
//		// �ٴ�У�飬�Ƿ������û���½
//		if( tpCommPlayer != NULL )
//		{
//			return CLIENTHANDLE_DECODE_FAILED;
//		}
//
//		CEntityPlayer* tpPlayer = SceneServer::CSceneLogic::GetSingletonPtr()->GetWaitingPlayerByCharID( pCSHead->uin() );
//		if( tpPlayer == NULL )
//		{
//			// �Ƿ������
//			return CLIENTHANDLE_EVIL_PKG;
//		}
//		else
//		{
//			// ��¼��tcpserver��Ҫ�ĶԵ�������Ϣ
//			tpPlayer->GetClientInfo( )->mClientAddr = tNetHead.mSrcIP;
//			tpPlayer->GetClientInfo( )->mClientPort = tNetHead.mSrcPort;
//			tpPlayer->GetClientInfo( )->mSockTime = tNetHead.mDstIP[0];
//			tpPlayer->GetClientInfo( )->mSockIndex = tNetHead.mDstPort[0];
//			tpPlayer->GetClientInfo( )->m_tLastActiveTime = time(NULL); // ����Ծʱ��
//
//			// �޸Ŀͻ���Դid
//			tpHead->set_srcid ( tpPlayer->get_id() );
//		}
//
//	}
//	else
//	{
//		// ���ҵ�socket˵���������û���½
//		if( tpCommPlayer == NULL )
//		{
//			return CLIENTHANDLE_EVIL_PKG;
//		}
//	}
//
//	return CLIENTHANDLE_SUCCESS;
//}
//

// ***************************************************************
//  Function:	 DecodeNetMsg
//  Description: ������Ϣ���а汾�Ľ��ܺͷ����л�����
//	Input:			
//	OutPut:			
//	Return:			
//	Others:		ֱ�Ӱ������ϵ�2���ư������ܺͷ����л���CCSHead��CMessage	
//  Date:		02/10/2009
// 
// ***************************************************************
int CClientHandle::DecodeNetMsg( BYTE* pCodeBuff, int& nLen, CCSHead* pCSHead, CMessage* pMsg )
{
	//TODO: ������Է��ģ����÷��ܱ�֤�������жϲ���
	//LK_ASSERT( pCodeBuff != NULL && nLen >= CNetHead::MinSize() , return -1 );

	BYTE* pBuff = pCodeBuff;
	int tLen = nLen;

	CNetHead tNetHead;
	memcpy( &tNetHead, pBuff, sizeof(CNetHead) );
	pBuff += sizeof(CNetHead);
	tLen -= sizeof(CNetHead);

	// ��tcpserver �ϵ�socket index 
	short tSockIndex = tNetHead.mDstPort;

	// �Ƿ��Ƕ�����Ϣ
	if( tNetHead.mState < 0 )
	{
		LOG_DEBUG( "default", "[%s:%d][%s] client commhandle %d closed ", __LK_FILE__, __LINE__, __FUNCTION__, tSockIndex );

		// ����Ƿ�����
		CEntityPlayer* tpPlayer = SceneServer::CSceneLogic::GetSingletonPtr()->GetPlayerByComm( tSockIndex );
		if( tpPlayer == NULL )
		{
			LOG_DEBUG( "default", "[%s:%d][%s], socket %d has closed", __LK_FILE__, __LINE__, __FUNCTION__, tSockIndex );
			return  -1;
		}
		else
		{
			// �ж��Ƿ���ͬһ�����
			if( tpPlayer->GetClientInfo( )->mSockTime != tNetHead.mDstIP)
			{
				LOG_ERROR( "default", "[%s:%d][%s], sock time not match (%d != %d)", 
					__LK_FILE__, __LINE__, __FUNCTION__, tpPlayer->GetClientInfo( )->mSockTime, tNetHead.mDstIP );
				return -1;
			}
			else
			{
				// ������Comm����
				if (tSockIndex != tpPlayer->GetCommHandle( )) 
				{
					LOG_ERROR("default", "[%s:%d][%s] FATAL ERROR: nethead.SockIndex = %d, but player.SockIndex = %d",  
							__LK_FILE__, __LINE__, __FUNCTION__, tSockIndex, tpPlayer->GetCommHandle( ));
				}

				// �ȴ�������ɾ��socket
				SceneServer::CSceneLogic::PLAYERID_MAP::iterator tCommIter = 
					SceneServer::CSceneLogic::GetSingletonPtr()->mPlayerCommIndex.find( tSockIndex);
				if ( tCommIter != SceneServer::CSceneLogic::GetSingletonPtr()->mPlayerCommIndex.end() )
				{
					SceneServer::CSceneLogic::GetSingletonPtr()->mPlayerCommIndex.erase(tCommIter);
					LOG_DEBUG("default", "[%s:%d][%s] remove fd(%d) from mPlayerCommIndex", 
							__LK_FILE__, __LINE__, __FUNCTION__, tSockIndex);
				}

				// �ٰ����socket�ó�0
				tpPlayer->SetCommHandle( 0 );

				if ( tpPlayer->GetCommState() == CEntityPlayer::STATE_INMAP )
				{
					// ģ��������Ϣ, ֪ͨ���߼�ģ��
					CMessageHead* tpHead = pMsg->mutable_msghead();
					tpHead->set_srcfe ( FE_CLIENT );
					tpHead->set_srcid ( tpPlayer->get_id() );
					tpHead->set_messageid( ID_C2S_REQUEST_LEAVEGAME );
					tpHead->set_msgseq( tpPlayer->GetCurRequestSeq()+1 ); //ģ��seq+1

					CMessageLeaveGameRequest *tpMsgPara = new (msMessageBuff) CMessageLeaveGameRequest;

					// ����������
					tpMsgPara->set_leavetype(1);
					pMsg->set_msgpara( (uint32)tpMsgPara );

					return CLIENTHANDLE_SUCCESS; 
				}
				else
				{

					LOG_INFO("default", "Player(%d:%s) 's status is (%d) which does not need onEvent LeaveGameRequest",
						tpPlayer->GetCharID(), tpPlayer->GetCharName(), tpPlayer->GetCommState());

					return -1;
				}
			}
		}
	}

	// �������

	int nRet = -1;

	CEntityPlayer* tpCommPlayer = SceneServer::CSceneLogic::GetSingletonPtr()->GetPlayerByComm( tSockIndex );
	if ( tpCommPlayer == NULL )
	{
		nRet = ClientCommEngine::ConvertClientCodeToMsg2( (void*)pBuff, (unsigned short)tLen, pCSHead, pMsg, ClientCommEngine::tpKey );
	}
	else
	{
		if ( *(tpCommPlayer->GetKey( )) == 0 )
		{
			nRet = ClientCommEngine::ConvertClientCodeToMsg2( (void*)pBuff, (unsigned short)tLen, pCSHead, pMsg, ClientCommEngine::tpKey );
		}
		else
		{
			nRet = ClientCommEngine::ConvertClientCodeToMsg2( (void*)pBuff, (unsigned short)tLen, pCSHead, pMsg,  (unsigned char *)tpCommPlayer->GetKey( ) );
		}

		pMsg->mutable_msghead()->set_dstid( tpCommPlayer->GetCharID() );


	}

	if( nRet < 0 )
	{
		if ( nRet != -7 ) // ���������̫���ˣ��Ͳ���ӡ��
			LOG_ERROR( "default", "convert code failed %d, InLen %d", nRet, tLen );

#ifdef _DEBUG_
		if( tpCommPlayer != NULL )
		{
			Log_bin( "default", tpCommPlayer->GetKey( ), KEYLEN );
			LOG_DEBUG( "default", "try to use static key to decrypte player %s's msg..", tpCommPlayer->GetCharNameShow() );
			nRet = ClientCommEngine::ConvertClientCodeToMsg2( (void*)pBuff, (unsigned short)tLen, pCSHead, pMsg, (unsigned char *)ClientCommEngine::tpKey );
			if( nRet == 0 )
			{
				LOG_DEBUG( "default", "use static key success, messge id is %d, csdialog id %d", pMsg->msghead().messageid(), pCSHead->dialogid() );

				// debug��ҲҪ��ֹ�ڴ�й¶ 
				CMessage* pMsgPara = (CMessage*) pMsg->msgpara();
				if( pMsgPara != NULL )
				{
					#ifdef _USE_MESSAGE_BUFF_ // ���ʹ����placement new��new����һ�龲̬�洢��buffer,ֻ������������delete
						pMsgPara->~Message();
					#else
						delete pMsgPara;
					#endif
				}

			}
		}
#endif
		return -1;
	}


	// �Ƿ��ǡ��״Ρ�����
	int nDialogID = (int)pCSHead->dialogid( ); 
	if( nDialogID <= 0 )
	{
		// �ٴ�У�飬�Ƿ������û���½
		if( tpCommPlayer != NULL )
		{
			LOG_ERROR( "default", "[%s:%d] player %d, comm %d is not a new player",
				__FUNCTION__, __LINE__, tpCommPlayer->GetCharID(), tpCommPlayer->GetCommState() );
			return CLIENTHANDLE_DECODE_FAILED;
		}

		CEntityPlayer* tpPlayer = SceneServer::CSceneLogic::GetSingletonPtr()->GetWaitingPlayerByCharID( pCSHead->uin() );
		if( tpPlayer == NULL )
		{
			LOG_DEBUG( "default", "[%s:%d] can't find player %d", __FUNCTION__, __LINE__, pCSHead->uin() );
			// �Ƿ������
			return CLIENTHANDLE_EVIL_PKG;
		}
		else
		{
			// ��¼��tcpserver��Ҫ�ĶԵ�������Ϣ
			tpPlayer->GetClientInfo( )->mClientAddr = tNetHead.mSrcIP;
			tpPlayer->GetClientInfo( )->mClientPort = tNetHead.mSrcPort;
			tpPlayer->GetClientInfo( )->mSockTime = tNetHead.mDstIP;
			tpPlayer->GetClientInfo( )->mSockIndex = tNetHead.mDstPort;
			tpPlayer->GetClientInfo( )->m_tLastActiveTime = time(NULL); // ����Ծʱ��

			// �޸Ŀͻ���Դid
			pMsg->mutable_msghead()->set_srcid ( tpPlayer->get_id() );

			pMsg->mutable_msghead()->set_dstid( tpPlayer->GetCharID() );

			// ��¼�ͻ���������Ϣseq
			tpPlayer->SetCurRequestSeq( pMsg->msghead().msgseq() );
		}

	}
	else
	{
		// ���ҵ�socket˵���������û���½
		if( tpCommPlayer == NULL )
		{
			LOG_ERROR( "default", "[%s:%d] can't find player by comm %d", __FUNCTION__, __LINE__, tSockIndex );
			return CLIENTHANDLE_EVIL_PKG;
		}
	}


	return CLIENTHANDLE_SUCCESS;
}


void CClientHandle::Dump(char* pBuffer, unsigned int& unLen )
{
	unsigned int unMaxLen = unLen;
	unLen = 0;

	int nBegin = 0;
	int nEnd = 0;
	int nLeft = 0;

	mC2SPipe->GetCriticalData( nBegin, nEnd, nLeft );
	unLen += snprintf( pBuffer+unLen,  unMaxLen-unLen, "%20s\t%6d\t%6d\n", "c2s pipe", nLeft, MAX_PIPE_SIZE );

	mS2CPipe->GetCriticalData( nBegin, nEnd, nLeft );
	unLen += snprintf( pBuffer+unLen,  unMaxLen-unLen, "%20s\t%6d\t%6d\n", "s2c pipe", nLeft, MAX_PIPE_SIZE );

}


//int CClientHandle::EncodeNetMsg( CMessage* pMsg, BYTE* pCodeBuff, short& vLen, int vCommNum, CEntityPlayer** ppPlayer )
//{
//	LK_ASSERT( pMsg != NULL && pCodeBuff != NULL && vLen > 0 && ppPlayer != NULL, return -1 );
//
//	CNetHead tNetHead;
//
//	CEntityPlayer* pPlayer = *ppPlayer;
//
//	// ��ʾ�Ƿ���tcpserver���������Ϣ���Զ����Ӧ�ͻ��˶Ͽ�����
//	if(  pMsg->msghead().messageid() == ID_S2C_RESPONSE_LEAVEGAME || pMsg->msghead().messageid() == ID_S2C_NOTIFY_KICK )
//	{
//		tNetHead.mSrcPort = 1; 
//	}
//	else
//	{
//		tNetHead.mSrcPort = 0;
//	}
//
//	tNetHead.mDstEntityNum = 0;
//
//	for( int i = 0 ; i < vCommNum && i < CNetHead::MAX_DEST_ENTITY; i++, ++ppPlayer )
//	{
//		CEntityPlayer* pPlayer = *ppPlayer;
//		if( pPlayer == NULL )
//		{
//			continue;
//		}
//		
//		tNetHead.mDstIP[ tNetHead.mDstEntityNum ] = pPlayer->mClientInfo.mSockTime;
//		tNetHead.mDstPort[ tNetHead.mDstEntityNum ] = pPlayer->mClientInfo.mSockIndex;
//
//		//LOG_DEBUG( "default", "client handle will send to socket[%d], create time %d ",tNetHead.mDstPort[ tNetHead.mDstEntityNum ], tNetHead.mDstIP[ tNetHead.mDstEntityNum ] );
//
//		tNetHead.mDstEntityNum ++;
//	}
//
//
//	short tLen = 0;
//
//	// NetHead ���л�
//	tNetHead.SerializeToArray( pCodeBuff, sizeof(CNetHead) );
//	short tNetHeadSize = tNetHead.Size();
//	pCodeBuff += tNetHeadSize;
//	tLen += tNetHeadSize;
//
//	CCSHead tCSHead;
//	unsigned short tusClientCodeLen = vLen - tLen;
//
//	if( ClientCommEngine::ConvertMsgToClientCode2( &tCSHead, pMsg, pCodeBuff, tusClientCodeLen ) < 0 )
//	{
//		return -1;
//	}
//
//	//tLen += tusClientCodeLen;
//
//	// ����ֵ
//	vLen = tNetHeadSize;
//
//	return 0;
//}
