// ********************************************************************** //
// Logic.cpp
// ��½�������߼�
// ��ɵ�½,�ǳ����Ŷ��߼�
//
// Author: Black
// ********************************************************************** //

#include <sys/socket.h>

#include "westserver.h"
#include "loginlogic.h"
#include "tinyxml.h"
#include "log.h"
#include "message_pb.hxx.pb.h"

#include "loginobj_manager.h"
#include "loginobj_manager_imp.h"
#include "servermessage_in.h"
#include "coremessage_pb.hxx.pb.h"
#include "client_comm_engine.h"
#include <google/protobuf/descriptor.h>
#include "servermessage_pb.hxx.pb.h"
#include "ibstore.h"


#ifdef USING_ERATING
#include "gm_service.h"
#include "charge_service.h"
#include "gmmessage_pb.hxx.pb.h"
#endif

#include <list>

/*
enum 
{
	MAX_LOGIN_PLAYER_ONCE_TIMER = 20,		//һ����Сʱ��Ƭ�������¼���������
	LOGIN_TIMER_INTERVAL = 1000,				//loginserver����Сʱ��Ƭ

	ERATING_HANDSET_INTERVAL = 20000,		// ERATING ����ͬ����Ϣ
	ERATING_SESSION_TIMER = 10000,	// ERATING ���첽��Ϣ��ʱ
	SERVER_SESSION_TIMER = 10000,	// MYSQL ���첽��Ϣ��ʱ
};
*/

CLoginServerConfigure::CLoginServerConfigure()
{
	int nOneSecond = 1000;
	nLoginTimerInterval = 1 * nOneSecond;
	nPingProxyInterval = 30 * nOneSecond;;
	nERatingHandsetInterval = 20 * nOneSecond;
	nEratingSessionTimeout = 10 * nOneSecond;
	nServerSessionTimeout = 10 * nOneSecond;
	nMaxLoginPlayerOnceTimer = 25;
	nMaxWorldPlayerNum = 10000;
	bVerifyByLocalForce = false;
	nClientHandleIdleSleep = 1 * nOneSecond;
	szEChargeCode[0] = 0;
	szEChargePasswd[0] = 0;
	nConnectEratingTimeout = 2 * nOneSecond;

	nEChargeID = 1000;

	nIbPayRetryFirstInterval = 30;
	nIbPayRetryFirstTimes = 120;

	nIbPayRetrySecondInterval = 1800;
	nIbPayRetrySecondTimes = 24;
	bLoginServiced = true;

	bVerifyClientMd5Code = false;
	nClientVersion = 0;

	nIbUsedRetryFirstInterval = 30;
	nIbUsedRetryFirstTimes = 120;

	nIbUsedRetrySecondInterval = 1800;
	nIbUsedRetrySecondTimes = 24;

	/*for (int i = 0; i < const_md5list_limit; ++i)
	{
		memset(sbClientMD5List[i], 0, const_md5code_length);
	}*/
	mClientMD5List.initailize();

	for (int i=0; i < const_whitelist_limit; ++i)
	{
		szWhiteNameList[i][0] = 0;
	}
	nValidateConnetSecOutTime = 10;
	nValidateConnetUSecOutTime = 0;

	for (size_t i=0; i < ARRAY_CNT(nBlackIPList); ++i)
	{
		nBlackIPList[i] = 0;
	}
};

using namespace ClientCommEngine;

// ********************************************************************** //
// CLoginServer
// ********************************************************************** //
template<> CLoginServer* CSingleton< CLoginServer >::spSingleton = NULL;
CSharedMem* CLoginServer::mShmPtr = NULL; 

// ***************************************************************
// Function:       Initialize
// Description:    ��ʼ��
// Input:          ��LoginServer��Ҫ�Ķ��󴴽��ڹ����ڴ���
// OutPut:         ��
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
int CLoginServer::Initialize( int vInitFlag )
{
	mRunFlag = EFLG_CTRL_NO;

	if (ReadCfg(mConfig) != 0)
	{
		printf("Read ../config/data/login_config/loginserver.xml failure. pls check it and run again.\n");
		exit(0);
	}
	CClientHandle::mShmPtr =  mShmPtr;
	mClientHandle = new CClientHandle;

	CLoginObjManager::mShmPtr = mShmPtr;
	CLoginObjManager* tpLoginObjMng = new CLoginObjManager;
		    
	CLoginLogic::mShmPtr = mShmPtr;
	CLoginLogic* tpLogic = new CLoginLogic;
		    
	CMessageQueue::mShmPtr = mShmPtr;
	CMessageQueue* tpMessageQueue = new CMessageQueue;

	CMessageDispatcher* tpMessageDispatcher = new CMessageDispatcher;
	CMessageFactory* tpMessageFactory = new CMessageFactory;
	mLastTickCount = LINEKONG::GetTickCount();

	if (ReadCfgByGameId(mConfig) != 0)
	{
		printf("ReadCfgByGameId failed.\n");
		exit(0);
	}

#ifdef USING_ERATING
	CGmServer* tpGmServer = new CGmServer();

	CChargeServer* tpChargeServer = new CChargeServer();

	mTimerOfReConn2ERating = CWTimer(CLoginServer::GetSingleton().mConfig.nERatingHandsetInterval);

	if (tpGmServer == NULL || tpChargeServer == NULL)
	{
		LOG_FATAL("default", "program alloc memory for tpGmServer or tpChargeServer error.");
		return -1;
	}
#endif

	mTimerOfKeepAlive = CWTimer(CLoginServer::GetSingleton().mConfig.nPingProxyInterval);
	mLastPorxyKeepAliveTime = time(0);

	if (tpLoginObjMng == NULL || tpLogic == NULL 
	|| tpMessageQueue == NULL || tpMessageDispatcher == NULL
	|| tpMessageFactory == NULL || mClientHandle == NULL)
	{
		LOG_FATAL("default", "program alloc memory for tpLogic error.");
		return -1;
	}

	mTmRecv4Erating = 0;
	mTmSend2Erating = 0;

	return 0;
}

// ***************************************************************
// Function:       CountSize
// Description:    ����LoginServer�Ĵ�С 
// Input:          
// OutPut:         ��
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
unsigned int CLoginServer::CountSize()
{
	//TODO: ���㽫����LoginServer ���󴴽��ڹ����ڴ��� 
	unsigned int tSize = sizeof( CLoginServer );

	tSize += CClientHandle::CountSize();
	tSize += CLoginLogic::CountSize();
	tSize += CLoginObjManager::CountSize();
	tSize += CMessageQueue::CountSize( );

	return tSize;
}

// ***************************************************************
// Function:       CheckRunFlags
// Description:    ���������б�־
// Input:          
// OutPut:         ��
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginServer::CheckRunFlags()
{
	if ( IsRunFlagSet( EFLG_CTRL_QUIT ) )
	{
		LOG_NOTICE( "default", "xyj-loginserver exit !" );

		CLoginLogic::GetSingleton().OnExit();

		// do something befor quit
		exit(0);
	}

	if ( IsRunFlagSet( EFLG_CTRL_RELOAD ) )
	{
		ClearRunFlag( );
		LOG_NOTICE( "default", "xyj-loginserver reload config ..." );

		// do reload
		//CLoginServerConfigure configure;
		if ( ReadCfg(mConfig) == 0) //success
		{
			if (ReadCfgByGameId(mConfig) == 0)
			{
				CLoginLogic::GetSingleton().OnReloadConfig();

				CGmServer::GetSingleton().ReloadCfg();
			}
			
			//mConfig = configure;

			
		}else
		{
			LOG_ERROR("default", "reload configure file error, please recheck it and reload it.");
		}
	}
}

// ***************************************************************
// Function:       SetRunFlag
// Description:    ���ó������б�־
// Input:          
// OutPut:         ��
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginServer::SetRunFlag( int vFlag )
{
	mRunFlag = vFlag;
}

// ***************************************************************
// Function:       ClearRunFlag
// Description:    ����������б�־
// Input:          
// OutPut:         ��
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginServer::ClearRunFlag()
{
	mRunFlag = EFLG_CTRL_NO;
}

// ***************************************************************
// Function:       IsRunFlagSet
// Description:    �жϳ������б�־
// Input:          
// OutPut:         ��
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
bool CLoginServer::IsRunFlagSet( int vFlag )
{
	return mRunFlag == vFlag;
}

#ifdef USING_ERATING

bool CLoginServer::IsConnected2ERating()
{
	return mERatingClient.GetSocket()->GetStatus() == tcs_connected;
}

// ***************************************************************
// Function:       CreateERatingMessage
// Description:    �Ӷ˿�fd������GateServer��������Ϣ 
// Input:          fd, tpMessage�ǵ�ַ
// OutPut:         tpMessage��msg_para�ᱻ��ֵ����Ҫ�����汻ɾ�� 
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
SysProtocol* CLoginServer::CreateERatingMessage(unsigned char* message_buffer, short message_length)
{
	// ������Erating�����ʽ����Ϣ
	SysProtocol* pproto = NULL; 

	unsigned int nCmdID = 0;
#ifdef USE_DECRYPTION_PROTOCAL
	SysProtocol::parseCommandID(message_buffer, message_length, &nCmdID);
#else
	SAGIPHeader*  pSAGIPHeader = (SAGIPHeader *)message_buffer;
	nCmdID = htonl(pSAGIPHeader->un_Command_ID);
#endif

	LOG_DEBUG("default", "Recv From ERating MsgID(%x), MsgLen(%d)", nCmdID, message_length);

	switch  (nCmdID)
	{
		/*
		case CMD_USER_LOGIN_RES: 
		{
			pproto = new AGIPUserLoginRes;
			break;
		}
		*/

		case CMD_JOINT_AUTHEN_RES:
		{
			pproto = new AGIPJointAuthenRes;
			break;
		}

		case CMD_USER_AUTH_RES:
		{
			pproto = new AGIPUserAuthRes;
			break;
		}

		case CMD_USER_AUTH_EX_RES:
		{
			pproto = new AGIPUserAuthExRes;	
			break;
		}

		case CMD_BIND_RES: 
		{
			pproto = new AGIPBindRes;
			break;	
		}

		case CMD_UNBIND_RES:
		{
			pproto = new AGIPUnbindRes;
			break;
		}

		case CMD_HANDSET_RES: 
		{
			pproto = new AGIPHandsetRes;
			break;
		}

		case CMD_USER_IB_PAY_RES:
		{
			pproto = new AGIPUserIBPayRes;
			break;
		}

		case CMD_USER_USE_PRODUCT_RES:
		{
			pproto = new AGIPUserUseProductRes;
			break;
		}

		case CMD_USER_IB_PAY_AUDIT_RES:
		{
			pproto = new AGIPUserIBPayAuditRes;
			break;
		}

		case CMD_USER_DATA_REPORT_RES:
		{
			pproto = new AGIPUserDataReportRes;
			break;
		}

		case CMD_USER_CASH_EXCHANGE_EX1_RES:
		{
			pproto = new AGIPUserCashExchangeEx1Res;
			break;
		}

		// ������Ϣֱ��ת��������
		case CMD_ROLE_LIST_RES:
		case CMD_CREATE_ROLE_RES:
		case CMD_DELETE_ROLE_RES:
		//case CMD_USER_ENTER_GAME_RES:
		case CMD_GW_DATA_REPORT_RES:
		case CMD_USER_LOGOUT_RES: 
		//case CMD_PASSWORD_VERIFY_RES: 
		case CMD_USER_ITEM_LIST_RES:
		case CMD_USER_ITEM_MINUS_RES:
		case CMD_ROLE_ENTER_GAME_EX_RES:
		case CMD_CREATE_GROUP_RES:
		case CMD_USER_BALANCE_INFO_RES:
		case CMD_USER_DRAW_BALANCE_RES:
		{
			CMessage tMessage;
			CMessageERatingProtoStream tProtoStream;
			tProtoStream.set_length(message_length);
			tProtoStream.set_buffer(message_buffer, message_length);

			pbmsg_sethead(&tMessage,ID_X2X_ERATING_PROTO_STREAM, 0, 0, 0, 0, 0, 0);
			tMessage.set_msgpara((uint32_t) &tProtoStream);

			CLoginLogic::GetSingleton().Send2Gate(&tMessage);
			return NULL;
		}

		default:
		{
			LOG_ERROR("default", " loginserver did NOT unpack msg(id = %x, length = %d)", nCmdID, message_length);
			return NULL;
		}
	}

	if (pproto == NULL) 
	{
		LOG_ERROR("default", " loginserver unpack msg(id = %d,length = %x) error", nCmdID, message_length);
		return NULL;
	}

#ifdef USE_DECRYPTION_PROTOCAL
	int result = pproto->setEncodedPDU(message_buffer, message_length, 0);
#else
	int result = pproto->setDecodedPDU(message_buffer, message_length, 0);
#endif

	if (result != S_SUCCESS)
	{
		LOG_ERROR("default", "SetEncodePDU/SetDeCodePDU failure,CommondID(%x) Length(%d), error(%d)", 
				nCmdID, message_length, result);

		delete pproto;
		return NULL;
	}

#ifdef _ECHARGE_DEBUG_
	if ( nCmdID != CMD_HANDSET_RES) 
	{
		printf(" recv from erating {\n");

		pproto->showInfo();
		printf("}\n");
	}
#endif

	return pproto;
}
#endif

// ***************************************************************
// Function:       RecvServerMsg
// Description:    ���ܲ������GateServer, ERatingServer ��������Ϣ�� �Լ���Gate����������
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginServer::RecvServerMsg(int vMsgCount)
{
	fd_set fds_read;
	struct timeval stMonTime;
	int iTempFD = -1;
	int iTempStatus = tcs_closed;
	int iMaxFD = 0;

	FD_ZERO( &fds_read );
	stMonTime.tv_sec = 0;
	stMonTime.tv_usec = 0;

	iTempFD = mProxyClient.GetSocket()->GetSocketFD(); 
	iTempStatus = mProxyClient.GetSocket()->GetStatus();
	if ( iTempFD > 0 && iTempStatus == tcs_connected )
	{
		FD_SET(iTempFD, &fds_read); 
		if(iTempFD > iMaxFD)
		{
			iMaxFD = iTempFD;
		}
	}	 

#ifdef USING_ERATING
	iTempFD = mERatingClient.GetSocket()->GetSocketFD(); 
	iTempStatus = mERatingClient.GetSocket()->GetStatus();
	if ( iTempFD > 0 && iTempStatus == tcs_connected )
	{
		FD_SET(iTempFD, &fds_read); 
		if(iTempFD > iMaxFD)
		{
			iMaxFD = iTempFD;
		}
	}
#endif

	int iOpenFDNum = select( iMaxFD + 1, &fds_read, NULL, NULL, &stMonTime );
	if ( iOpenFDNum <= 0 ) return;                                                                                                   
	BYTE tCodeBuff[ MAX_CODE_LEN ];
	unsigned short tBuffLen = sizeof( tCodeBuff );
	int iRet = -1; 

	iTempFD = mProxyClient.GetSocket()->GetSocketFD();
	if ( iTempFD >0 && FD_ISSET(iTempFD, &fds_read) )
	{
		mProxyClient.GetSocket()->RecvData();
		while (1)
		{
			tBuffLen = sizeof( tCodeBuff );
			iRet = mProxyClient.GetSocket()->GetOneCode( tBuffLen, tCodeBuff );
																			   
			if ( iRet <= 0  ) break;

			if( tBuffLen == 0 || tBuffLen > sizeof(tCodeBuff))
			{
				LOG_ERROR( "default", "Code Len %d impossible", tBuffLen );
				break;
			}

			CProxyHead tProxyHead;
			CMessage tMessage; 

			int decode_ret =  pbmsg_getheadmsg((unsigned char*)tCodeBuff, tBuffLen , &tProxyHead, &tMessage);
			if( decode_ret <= 0 )
			{
				LOG_ERROR("default", "decode message failed");
				continue;
			} 

			LOG_DEBUG( "default", "Recv Proxy(fd=%d) ProxyHead[%s]", iTempFD, tProxyHead.ShortDebugString().c_str());

			if ( CMD_KEEPALIVE == tProxyHead.opflag() && tProxyHead.srcfe() == CET_PROXYSERVER )
			{
				LOG_DEBUG("default", "RecvFromProxy: %s", tProxyHead.ShortDebugString().c_str());

				time(&mLastPorxyKeepAliveTime);
				continue;
			}

			Message* pUnknownMessagePara = (Message*) tMessage.msgpara();
			LK_ASSERT( pUnknownMessagePara != NULL, return  );

			const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessagePara->GetDescriptor();

			LOG_DEBUG( "default", "Recv Proxy(fd=%d) MsgName[%s] ProxyHead[%s] MsgHead[%s] MsgPara[%s] ",
					iTempFD , pDescriptor->name().c_str(), tProxyHead.ShortDebugString().c_str(),
					tMessage.msghead().ShortDebugString().c_str(), pUnknownMessagePara->ShortDebugString().c_str());

			CLoginLogic::GetSingletonPtr()->OnProxyMessage( &tMessage);
		}
	}

#ifdef USING_ERATING
	iTempFD = mERatingClient.GetSocket()->GetSocketFD();
	if ( iTempFD >0 && FD_ISSET(iTempFD, &fds_read) )
	{
		int r = mERatingClient.GetSocket()->RecvData();
		if ( r == ERR_RECV_REMOTE || r == ERR_RECV_FALIED)
		{
			CLoginLogic::GetSingletonPtr()->UpdateERatingBindStatus(false);
		}else
		{
			mTmRecv4Erating = time(0);
		}

		while (1)
		{
			tBuffLen = sizeof( tCodeBuff );
			iRet = mERatingClient.GetSocket()->GetOneCode(tBuffLen, tCodeBuff, use_network_byte);
																			   
			if ( iRet <= 0  ) break;
			if( tBuffLen == 0 || tBuffLen > sizeof(tCodeBuff))
			{
				LOG_ERROR( "default", "Code Len %d impossible", tBuffLen );
				break;
			}
			
			SysProtocol* pproto = CreateERatingMessage(tCodeBuff, tBuffLen);
			if (pproto != NULL)
			{
				CLoginLogic::GetSingleton().OnERatingMessage(pproto);

				delete pproto;
			}
		}
	}
#endif

//#ifdef	USING_VALIDATE
//	//RecvValidateMsg( 0, 0 );
//#endif
}
											    
// ***************************************************************
// Function:       RecvClientMsg
// Description:    ���ܲ�����ӿͻ��˹�������Ϣ, ������vMsgCount����Ϣ
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginServer::RecvClientMsg(int vMsgCount)
{
	int vRecvCount = 0;
	BYTE tMsgBuff[ MAX_PACKAGE_LEN ];
	short tMsgLen = sizeof( tMsgBuff );

	while( vRecvCount < vMsgCount )
	{
		tMsgLen = sizeof( tMsgBuff );
		int vRecvRet = mClientHandle->Recv ( );

		vRecvCount ++;

		/*�����ѿ�*/
		if ( vRecvRet == CLIENTHANDLE_QUEUE_EMPTY )
		{
			struct timespec tv;
			tv.tv_sec = 0;
			tv.tv_nsec = mConfig.nClientHandleIdleSleep; 

			/* ������пգ�˯�� 1 ms */
			nanosleep( &tv, NULL );

			break;
		}
		else if ( vRecvRet == CLIENTHANDLE_SUCCESS )
		{

		}
		else
		{
			LOG_ERROR( "default", "ClientHandle " );
			continue;
		}
	}
}

// ***************************************************************
// Function:       RecvValidateMsg
// Description:    ����������֤����������Ϣ
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           07/19/2008
// 
//***************************************************************
int CLoginServer::RecvValidateMsg( int nSec, int nUsec )
{
	int iTempFD		= mValidateClient.GetSocket()->GetSocketFD();
	int iTempStatus = mValidateClient.GetSocket()->GetStatus();
								   
	fd_set fds_read;
	struct timeval stMonTime;

	FD_ZERO( &fds_read );
	stMonTime.tv_sec = nSec;
	stMonTime.tv_usec = nUsec;


	if ( iTempFD > 0 && iTempStatus == tcs_connected )
	{
		FD_SET( iTempFD, &fds_read );		
	}

	int iOpenFDNum = select( iTempFD + 1, &fds_read, NULL, NULL, &stMonTime );
	if ( iOpenFDNum <= 0 ) 
	{			
		return -1;  
	}
	
	BYTE tCodeBuff[ MAX_CODE_LEN ];
	unsigned short tBuffLen = sizeof( tCodeBuff );	

	if ( iTempFD > 0 && FD_ISSET( iTempFD, &fds_read ) )
	{
		int tRet = mValidateClient.GetSocket()->RecvData();
		if ( tRet == ERR_RECV_REMOTE || tRet == ERR_RECV_FALIED)
		{	
			return -1;			
		}
		tBuffLen = sizeof( tCodeBuff );
		tRet = mValidateClient.GetSocket( )->GetOneCode( tBuffLen, tCodeBuff );
		CMessage tMsg;
		tRet = DecodeMsgFromBufer( (char *)tCodeBuff, tBuffLen, tMsg );
		if ( tRet != 0 )
		{
			CLoginLogic::GetSingleton( ).OnValidateMessage( &tMsg );
			pbmsg_delmsg(&tMsg);
			tMsg.Clear();	
			
			// TODO:����һ����֤�Ļ�ֱ�ӹر�socket			
			mValidateClient.GetSocket()->Close();
		}
		else
		{
			LOG_ERROR( "default","Decode message from validateserver error!" );						
			return -1;		
		}	
	}
	return SUCCESS;
}

// ***************************************************************
// Function:       Launch
// Description:    loginserver ����, ��ȡ����, ��������, ����Erating, ����mysql
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginServer::Launch()
{
	LOG_INFO("default", "login server is lauching.");
	
#ifdef  USING_VALIDATE
	// TODO: ������֤������
	if ( Regist2ValidateServer() == true )
	{	  	
		LOG_INFO("default", "loginserver has registed to validate server");
	}
	else
	{
		LOG_ERROR("default", "COnnect to validate server failure");
		exit( 0 );
	} 
#endif
																   
	if (Connect2Proxy() == true)
	{
		Regist2ProxyServer();
		LOG_INFO("default", "loginserver has registed to proxy server");
	}else
	{
		LOG_ERROR("default", "COnnect to Proxy failure, It will reconnect on runtime");
	}

	#ifdef USING_ERATING
	if (Connect2ERating(em_nblock_mode) == true)
	{
		mERatingClient.GetSocket()->CheckNoblockConnecting(1000000);
	}

	if (IsConnected2ERating() == true)
	{
		LOG_INFO("default", "loginserver has conneted to erating server");
	}else
	{
		//if timeout then close.
		if (mERatingClient.GetSocket()->GetStatus() == tcs_connecting)
		{
			mERatingClient.GetSocket()->Close();
		}

		LOG_INFO("default", "loginserver does not connect to erating server, then will reconnect later.");
		CLoginLogic::GetSingletonPtr()->UpdateERatingBindStatus(false);
	}

	if (CGmServer::GetSingleton().CreateGmCmdServer(mGmCmdServerPort.c_str()) == true)
	{
		LOG_INFO("default", "CreateGmCmdServer on port(%s) ok.", mGmCmdServerPort.c_str());
	}else
	{
		LOG_ERROR("default", "CreateGmCmdServer on port(%s) failure. it will retry again on runtime.", 
				mGmCmdServerPort.c_str());
	}

	if (CChargeServer::GetSingleton().CreateChargeServer(mChargeServerPort.c_str()) == true)
	{
		LOG_INFO("default", "CreateChargeServer ok on port(%s)", mChargeServerPort.c_str());
	}else
	{
		LOG_ERROR("default", "CreateChargeServer on port(%s) failure. it will retry again on runtime.",
				mChargeServerPort.c_str());
	}
	#endif
}


// ***************************************************************
// Function:       Regist2ProxyServer
// Description:    ��������, �����˼��ʱ�ӣ������������Ϣ, ����ͻ�����Ϣ�Ⱥ���
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginServer::Regist2ProxyServer()
{
	CProxyHead  tHead;

	char message_buffer[MAX_CODE_LEN];
	pbmsg_setproxy(&tHead, CET_OTHERSERVER, CET_PROXYSERVER, 1, 1, TRANS_P2P, CMD_REGSERVER);

	unsigned short message_length = tHead.ByteSize() + 4;
	*((unsigned short*) message_buffer)  = message_length;

	*((unsigned short*) (message_buffer + 2))  = tHead.ByteSize();

	if(tHead.SerializeToArray(message_buffer+4, message_length - 4))
	{
		LOG_DEBUG("default", "regist to proxyserver (len:%d): head=[%d:%s]",  message_length,tHead.ByteSize(), tHead.ShortDebugString().c_str());
		mProxyClient.GetSocket()->SendOneCode(message_length, (BYTE*)message_buffer);
	}else
	{
		LOG_ERROR("default", "regist to proxyserver error");
	}
}

void CLoginServer::SendKeepAliveToProxy()
{
	CProxyHead  tHead;

	char message_buffer[MAX_CODE_LEN];
	pbmsg_setproxy(&tHead, CET_OTHERSERVER, CET_PROXYSERVER, 1, 1, TRANS_P2P, CMD_KEEPALIVE);

	unsigned short message_length = tHead.ByteSize() + 4;
	*((unsigned short*) message_buffer)  = message_length;

	*((unsigned short*) (message_buffer + 2))  = tHead.ByteSize();

	if(tHead.SerializeToArray(message_buffer+4, message_length - 4))
	{
		mProxyClient.GetSocket()->SendOneCode(message_length, (BYTE*)message_buffer);
	}else
	{
		LOG_ERROR("default", " [ %s : %d ][ %s ] error", __LK_FILE__, __LINE__, __FUNCTION__);
	}
}

// ***************************************************************
// Function:       Run
// Description:    ��������, �����˼��ʱ�ӣ������������Ϣ, ����ͻ�����Ϣ�Ⱥ���
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginServer::Run(const int nDaemon )
{
	while(1)
	{
		// ������б�־
		CheckRunFlags();  

		// ���ʱ��
		CheckTimer();

		// ���շ�������Ϣ����Ϣ����(����ѭ��������N��)
		RecvServerMsg(3000);

#ifdef USING_ERATING
		// ����GM��Ϣ��ֱ����Ӧ
		CGmServer::GetSingleton().RecvGmCmdServerMsg(200);

		CChargeServer::GetSingleton().RecvEChargeMsg(200);
#endif

		// ���տͻ�����Ϣ����Ϣ����(����ѭ��������N��)
		
		// ���û��ͨ����֤����������֤���ܽ��տͻ��˵���Ϣ
//#ifdef  USING_VALIDATE
//		if ( mValidateStatus == EFLG_VALIDATE_CHECKED )
//		{
//			RecvClientMsg(3000);
//		}
//		else
//		{
//			LOG_ERROR( "default", "server not validated!") ;
//		}
//#else
		RecvClientMsg(3000);
// #endif 	

		// ������Ϣ�����е���Ϣ
		CMessageDispatcher::GetSingletonPtr( )->DispachMsg( ); 
	}

}
	
// ***************************************************************
// Function:       CheckTimer
// Description:    ���ʱ�� 
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginServer::CheckTimer()
{
	unsigned int tNowCount = LINEKONG::GetTickCount();

	int tInterval = tNowCount - mLastTickCount;
	if ( tInterval < CLoginServer::GetSingleton().mConfig.nLoginTimerInterval )
	{
		return ;
	}

	mLastTickCount = tNowCount ;

	if (mERatingClient.GetSocket()->GetStatus() == tcs_connecting)
	{
		int r = mERatingClient.GetSocket()->CheckNoblockConnecting();
		LOG_INFO("default", "%s", r == 0 ? "connecting erating":"connect erating failure");

		if (IsConnected2ERating() == true)
		{
			LOG_INFO("default", "loginserver has connected erating.");

			if (CLoginLogic::GetSingleton().IsWorldOpened() == true )
			{
				//sleep(1);
				CLoginLogic::GetSingleton().SendBindProto2ERating(em_reconnect);
			}
		}
	}

	#ifdef USING_ERATING
	if (CLoginLogic::GetSingleton().IsWorldOpened() == true 
			&& mTimerOfReConn2ERating.Elapse(tInterval) == true)
	{
		if (mERatingClient.GetSocket()->GetStatus() == tcs_connecting)
		{
			// �����Ȼ��connecting��close��, ��������
			mERatingClient.GetSocket()->Close();
		}

		if (IsConnected2ERating() == false)
		{
			LOG_INFO("default", "reconnecting to erating");
			if (Connect2ERating(em_nblock_mode) == true)
			{
				if (IsConnected2ERating() == true)
				{
					LOG_INFO("default", "connect erating successfully.");
					CLoginLogic::GetSingleton().SendBindProto2ERating(em_reconnect);
				}else
				{
					LOG_INFO("default", "connecting to erating");
				}
			}else
			{
				LOG_INFO("default", "connected erating failure.");
			}
		}
	}
	#endif

	// if proxy offline, then reconnect and regist this server.
	if ( mProxyClient.GetSocket()->GetStatus() != tcs_connected)
	{
		if (Connect2Proxy())
		{
			Regist2ProxyServer();
		}
	}else // if proxy ok, then keep alive.
	{
		if (mTimerOfKeepAlive.Elapse(tInterval) == true)
		{
			SendKeepAliveToProxy();

			// if some error like as cable error.
			if ((time(0) - mLastPorxyKeepAliveTime) > 3.1 * mTimerOfKeepAlive.mMaxDuration)
			{
				if (Connect2Proxy())
				{
					Regist2ProxyServer();
				}
			}
		}
	}

	// if echarge server is not be created , then do it
	if ( CChargeServer::GetSingleton().GetStatus() == tcs_closed )
	{
		if (CChargeServer::GetSingleton().CreateChargeServer(mChargeServerPort.c_str()) == true)
		{
			LOG_INFO("default", "CreateChargeServer ok on port(%s)", mChargeServerPort.c_str());
		}
	}
	
	// if gm server is not be created, then do it
	if ( CGmServer::GetSingleton().GetStatus() == tcs_closed )
	{
		if (CGmServer::GetSingleton().CreateGmCmdServer(mGmCmdServerPort.c_str()) == true)
		{
			LOG_INFO("default", "CreateGmCmdServer on port(%d) ok.", mGmCmdServerPort.c_str());
		}
	}

	CLoginLogic::GetSingletonPtr()->OnTimer(tInterval);

}
// �õ�gameid����� login����
int CLoginServer::ReadCfgByGameId(CLoginServerConfigure &vConfigure)
{
	char const_cfgfile[ CONFIG_STR_LEN ] = { 0 }; 
	CLoginLogic::GetSingleton().GetConfigDataFileNamePath(CLoginLogic::GetSingletonPtr()->GetGameID(),"login_config/loginserver.xml", const_cfgfile, CONFIG_STR_LEN);
	const char* whitelist_cfgfile = "../config/whitelist.xml";
	char verify_cfgfile[ CONFIG_STR_LEN ] = { 0 };
	CLoginLogic::GetSingleton().GetConfigDataFileNamePath(CLoginLogic::GetSingletonPtr()->GetGameID(),"versionctl.xml", verify_cfgfile, CONFIG_STR_LEN);
	TiXmlDocument tDoc;
	TiXmlDocument tWhiteDoc;
	TiXmlDocument tVerifyDoc;
	if (!tDoc.LoadFile( const_cfgfile ))
	{
		LOG_ERROR( "default", "load xml %s failed", const_cfgfile);
		printf( "load xml %s failed\n", const_cfgfile);
		return -1;
	}
	if( !tVerifyDoc.LoadFile( verify_cfgfile ) )
	{
		LOG_ERROR( "default", "load xml %s failed", verify_cfgfile );
		printf( "load xml %s failed\n", verify_cfgfile );
		return -1;
	}
	TiXmlElement* tpElement = NULL;
	TiXmlElement* tpChildElm = NULL;
	TiXmlElement* tpRoot = tDoc.FirstChildElement();

	TiXmlElement* tpVerChildElm = NULL;
	TiXmlElement* tpVerRoot = tVerifyDoc.FirstChildElement( );

	tpVerChildElm = tpVerRoot->FirstChildElement("verify_service");
	if (tpVerChildElm != NULL)
	{
		mConfig.mClientMD5List.initailize();

		const char* verifyon = tpVerChildElm->Attribute("verify");
		vConfigure.bVerifyClientMd5Code = ( verifyon == NULL || strcasecmp(verifyon, "true") == 0 );

		int i = 0;
		for( TiXmlElement* tpSubElement = tpVerChildElm->FirstChildElement(); 
			tpSubElement != NULL && i < const_md5list_limit ;
			tpSubElement = tpSubElement->NextSiblingElement() )
		{
			const char* szHashCode = tpSubElement->Attribute("value");
			if (szHashCode == NULL)
			{
				printf("version ctrl config wrong , miss value node\n");
				LOG_ERROR( "default", "version ctrl config wrong , miss value node" );
				continue;
			}

			const char* szClientVer = tpSubElement->Attribute("client_version");
			if( szClientVer == NULL )
			{
				printf("version ctrl config wrong , miss client_version node\n");
				LOG_ERROR( "default", "version ctrl config wrong , miss client_version node" );		
				continue;
			}

			std::pair<CLoginServerConfigure::MD5LIST::iterator, bool> ret = mConfig.mClientMD5List.insert( std::pair<int,lk::string<32> >(atoi(szClientVer), szHashCode) );
			if ( !ret.second )
			{
				LOG_ERROR("default", "add ver: %d-%s failed!", atoi(szClientVer), szHashCode );
			}
			else
			{
				LOG_DEBUG("default", "add ver: %d-%s", atoi(szClientVer), szHashCode );
			}
		}
	}

	if( tWhiteDoc.LoadFile( whitelist_cfgfile ) )
	{
		//		TiXmlElement* tpWhiteElement = NULL;
		TiXmlElement* tpWhiteChildElm = NULL;
		TiXmlElement* tpWhiteRoot = tWhiteDoc.FirstChildElement( );

		tpWhiteChildElm = tpWhiteRoot->FirstChildElement("login_service");
		if( tpWhiteChildElm != NULL )
		{
			const char* turnedon = tpWhiteChildElm->Attribute("turned_on");
			vConfigure.bLoginServiced = ( turnedon == NULL || strcasecmp(turnedon, "true") == 0 );

			int i = 0;
			for( TiXmlElement* tpSubElement = tpWhiteChildElm->FirstChildElement(); 
				tpSubElement != NULL && i < const_whitelist_limit ;
				tpSubElement = tpSubElement->NextSiblingElement() )
			{
				const char* szWhiteName = tpSubElement->Attribute("value");
				if (szWhiteName != NULL)
				{
					strncpy(vConfigure.szWhiteNameList[i], szWhiteName, CLoginPlayer::USER_NAME_LEN); 
					vConfigure.szWhiteNameList[i++][CLoginPlayer::USER_NAME_LEN] = 0;	
				}
			}
		}else
		{
			LOG_INFO("default", "bLoginServiced use default value(%s)", vConfigure.bLoginServiced ? "true" : "false");
		}	
	}
	else
	{
		LOG_INFO( "default", "No whitelist_cfgfile" );
	}
	tpElement = tpRoot->FirstChildElement("limit");
	if( tpElement != NULL )
	{
		tpChildElm = tpElement->FirstChildElement("max_login_player_once_timer");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nMaxLoginPlayerOnceTimer));
		}else
		{
			LOG_INFO("default", "max_login_player_once_timer use default value(%d)",
				vConfigure.nMaxLoginPlayerOnceTimer);
		}

		tpChildElm = tpElement->FirstChildElement("max_world_player_num");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nMaxWorldPlayerNum));
		}
		else
		{
			LOG_INFO("default", "max_world_player_num use default value(%d)",
				vConfigure.nMaxWorldPlayerNum);
		}

		tpChildElm = tpElement->FirstChildElement("local_verify_force");
		if( tpChildElm != NULL )
		{
			const char* pszVerify = tpChildElm->Attribute("value");
			if( pszVerify != NULL )
			{
				vConfigure.bVerifyByLocalForce = ( strcmp( pszVerify, "true" ) == 0 ) ? true : false;
			}
		}
		else
		{
			LOG_INFO("default", "local_verify_force use default value(%d)",
				vConfigure.bVerifyByLocalForce );
		}

	}

	// Log
	tpElement = tpRoot->FirstChildElement( "LOG" );
	if( tpElement != NULL )
	{
		for( tpChildElm = tpElement->FirstChildElement( ); tpChildElm != NULL; 
			tpChildElm = tpChildElm->NextSiblingElement( ) )
		{
			const char* tpKey = tpChildElm->Attribute("KEY");
			const char* tpFile = tpChildElm->Attribute("FILE");
			const char* tpLevel = tpChildElm->Attribute( "LEVEL" );

			if( ( tpKey == NULL ) || ( tpFile == NULL ) || ( tpLevel == NULL ) )
			{
				continue;
			}

			INIT_ROLLINGFILE_LOG( tpKey, tpFile, ( LogLevel )atoi( tpLevel ), 10*1024*1024, 20 );
		}
	}


	tpElement = tpRoot->FirstChildElement("timeout");
	if( tpElement != NULL )
	{
		tpChildElm = tpElement->FirstChildElement("ping_proxy_interval");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nPingProxyInterval));
		}else
		{
			LOG_INFO("default", "ping_proxy_interval use default value(%d)",
				vConfigure.nPingProxyInterval);
		}

		tpChildElm = tpElement->FirstChildElement("login_timer_interval");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nLoginTimerInterval));
		}else
		{
			LOG_INFO("default", "login_timer_interval use default value(%d)",
				vConfigure.nLoginTimerInterval);
		}

		tpChildElm = tpElement->FirstChildElement("erating_handset_interval");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nERatingHandsetInterval));
		}else
		{
			LOG_INFO("default", "erating_handset_interval use default value(%d)",
				vConfigure.nERatingHandsetInterval);
		}

		tpChildElm = tpElement->FirstChildElement("erating_session_timeout");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nEratingSessionTimeout));
		}else
		{
			LOG_INFO("default", "erating_session_timeout use default value(%d)",
				vConfigure.nEratingSessionTimeout);
		}

		tpChildElm = tpElement->FirstChildElement("server_session_timeout");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nServerSessionTimeout));
		}else
		{
			LOG_INFO("default", "server_session_timeout use default value(%d)",
				vConfigure.nServerSessionTimeout);
		}

		tpChildElm = tpElement->FirstChildElement("clienthanle_idle_sleep");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nClientHandleIdleSleep));
		}else
		{
			LOG_INFO("default", "clienthanle_idle_sleep use default value(%d)",
				vConfigure.nClientHandleIdleSleep);
		}

		tpChildElm = tpElement->FirstChildElement("connect_erating_timeout");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nConnectEratingTimeout));
		}else
		{
			LOG_INFO("default", "connect_erating_timeout use default value(%d)",
				vConfigure.nConnectEratingTimeout);
		}

		tpChildElm = tpElement->FirstChildElement("ibpay_retry_first_interval");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nIbPayRetryFirstInterval));
		}else
		{
			LOG_INFO("default", "ibpay_retry_first_interval use default value(%d)",
				vConfigure.nIbPayRetryFirstInterval);
		}

		tpChildElm = tpElement->FirstChildElement("ibpay_retry_second_interval");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nIbPayRetrySecondInterval));
		}else
		{
			LOG_INFO("default", "ibpay_retry_second_interval use default value(%d)",
				vConfigure.nIbPayRetrySecondInterval);
		}

		tpChildElm = tpElement->FirstChildElement("ibpay_retry_first_times");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nIbPayRetryFirstTimes));
		}else
		{
			LOG_INFO("default", "ibpay_retry_first_times use default value(%d)",
				vConfigure.nIbPayRetryFirstTimes);
		}

		tpChildElm = tpElement->FirstChildElement("ibpay_retry_second_times");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nIbPayRetrySecondTimes));
		}else
		{
			LOG_INFO("default", "ibpay_retry_second_times use default value(%d)",
				vConfigure.nIbPayRetrySecondTimes);
		}


		tpChildElm = tpElement->FirstChildElement("ibused_retry_first_interval");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nIbUsedRetryFirstInterval));
		}else
		{
			LOG_INFO("default", "ibused_retry_first_interval use default value(%d)",
				vConfigure.nIbUsedRetryFirstInterval);
		}

		tpChildElm = tpElement->FirstChildElement("ibused_retry_second_interval");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nIbUsedRetrySecondInterval));
		}else
		{
			LOG_INFO("default", "ibused_retry_second_interval use default value(%d)",
				vConfigure.nIbUsedRetrySecondInterval);
		}

		tpChildElm = tpElement->FirstChildElement("ibused_retry_first_times");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nIbUsedRetryFirstTimes));
		}else
		{
			LOG_INFO("default", "ibused_retry_first_times use default value(%d)",
				vConfigure.nIbUsedRetryFirstTimes);
		}

		tpChildElm = tpElement->FirstChildElement("ibused_retry_second_times");
		if( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nIbUsedRetrySecondTimes));
		}else
		{
			LOG_INFO("default", "ibused_retry_second_times use default value(%d)",
				vConfigure.nIbUsedRetrySecondTimes);
		}

		tpChildElm = tpElement->FirstChildElement("connect_validate_second_times");
		if ( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nValidateConnetSecOutTime));
		}
		else
		{
			LOG_INFO("default", "connect_validate_second_times use default value(%d)",
				vConfigure.nValidateConnetSecOutTime);
		}

		tpChildElm = tpElement->FirstChildElement("connect_validate_usecond_times ");
		if ( tpChildElm != NULL )
		{
			tpChildElm->Attribute("value", &(vConfigure.nValidateConnetUSecOutTime));
		}
		else
		{
			LOG_INFO("default", "connect_validate_usecond_times use default value(%d)",
				vConfigure.nValidateConnetUSecOutTime);
		}			
	}

	if (mProxyServerAddr.length() == 0 || mGmCmdServerPort.length() == 0 
		|| mERatingServerAddr.length() == 0 || mChargeServerPort.length() == 0 )
	{                                                                                                      
		LOG_ERROR("default", "configure file(%s) proxy_server(%s) or gate_server(%s) "
			"or erating_server(%s) or charge_server(%s)",
			const_cfgfile, mProxyServerAddr.c_str(), mGmCmdServerPort.c_str(), 
			mERatingServerAddr.c_str(), mChargeServerPort.c_str());

		return -1;
	}

	return 0;
}
int CLoginServer::ReadCfg(CLoginServerConfigure& vConfigure)
{
	const char* ip_cfgfile = "../config/ip.xml";
	TiXmlDocument tIPDoc;

	if( !tIPDoc.LoadFile( ip_cfgfile ) )
	{
		LOG_ERROR( "default", "load xml %s failed", ip_cfgfile );
		printf( "load xml %s failed\n", ip_cfgfile );
		return -1;
	}

	TiXmlElement* tpIPElement = NULL;
	TiXmlElement* tpIPChildElm = NULL;
	TiXmlElement* tpIPRoot = tIPDoc.FirstChildElement( );

	tpIPElement = tpIPRoot->FirstChildElement( "server" );
	if( tpIPElement != NULL )
	{
		tpIPChildElm = tpIPElement->FirstChildElement( "login_server" );
		if( tpIPChildElm != NULL )
		{
			const char* pszLoginID = tpIPChildElm->Attribute( "id" ) ;
			if( pszLoginID == NULL )
			{
				printf( "configure file(%s) has no login_server <id> node\n", ip_cfgfile );
				return -1;
			}
			else
			{
				mLoginServerID = ::atoi(pszLoginID);
			}
		}
		else
		{
			printf( "configure file(%s) has no login_server node\n", ip_cfgfile );
			LOG_ERROR( "default", "configure file(%s) has no login_server node", ip_cfgfile );
			return -1;
		}


		tpIPChildElm = tpIPElement->FirstChildElement( "gm_server" );
		if( tpIPChildElm != NULL )
		{
			mGmCmdServerPort = tpIPChildElm->Attribute( "port" );
		}
		else
		{
			printf( "configure file(%s) has no login_server node\n", ip_cfgfile );
			LOG_ERROR( "default", "configure file(%s) has no login_server node", ip_cfgfile );
			return -1;
		}

		tpIPChildElm = tpIPElement->FirstChildElement("proxy_server");
	    if( tpIPChildElm != NULL )
		{
			mProxyServerAddr = tpIPChildElm->Attribute("address");
		}else
		{
			printf("configure file(%s) has no proxy_server node\n", ip_cfgfile);
			LOG_ERROR("default", "configure file(%s) has no proxy_server node", ip_cfgfile );
			return -1;
		}

		tpIPChildElm = tpIPElement->FirstChildElement("erating_server");
	    if( tpIPChildElm != NULL )
		{
			mERatingServerAddr = tpIPChildElm->Attribute("address");
		}else
		{
			printf("configure file(%s) has no login_server node\n", ip_cfgfile);
			LOG_ERROR("default", "configure file(%s) has no login_server node", ip_cfgfile );
			return -1;
		}
		

		tpIPChildElm = tpIPElement->FirstChildElement("charge_server");
	    if( tpIPChildElm != NULL )
		{
			mChargeServerPort = tpIPChildElm->Attribute("port");
			tpIPChildElm->Attribute("echarge_id", &(vConfigure.nEChargeID));

			strncpy(vConfigure.szEChargeCode, tpIPChildElm->Attribute("echarge_code"),
					sizeof(vConfigure.szEChargeCode) -1); 
			vConfigure.szEChargeCode[sizeof(vConfigure.szEChargeCode) -1] = 0;

			strncpy(vConfigure.szEChargePasswd, tpIPChildElm->Attribute("echarge_psw"),
					sizeof(vConfigure.szEChargePasswd) -1);
			vConfigure.szEChargePasswd[sizeof(vConfigure.szEChargePasswd) -1] = 0;


		}else
		{
			printf("configure file(%s) has no charge_server node\n", ip_cfgfile);
			LOG_ERROR("default", "configure file(%s) has no charge_server node", ip_cfgfile);
			return -1;
		}

		for (size_t i=0; i < ARRAY_CNT(vConfigure.nBlackIPList); ++i)
		{
			vConfigure.nBlackIPList[i++] = 0;
		}

		TiXmlElement *tpBlackElm = tpIPElement->FirstChildElement("black_list");
	    if( tpBlackElm != NULL )
		{
			size_t i = 0;
			for(TiXmlElement* tpSubElement = tpBlackElm->FirstChildElement(); 
					tpSubElement != NULL && i < ARRAY_CNT(vConfigure.nBlackIPList);
					tpSubElement = tpSubElement->NextSiblingElement() )
			{
				const char* szBlackIP = tpSubElement->Attribute("value");
				if (szBlackIP != NULL)
				{
					vConfigure.nBlackIPList[i++] = inet_addr(szBlackIP);	
				}
			}
		}
	}

	return 0;
}



// ***************************************************************
// Function:       Connect2Proxy
// Description:    ����ERatingServer
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
bool CLoginServer::Connect2Proxy()
{
	char tIP[ 64 ] = {0};
	short tPort = 0;

	SplitSockAddr(mProxyServerAddr.c_str(), tIP, tPort );
	mProxyClient.Initialize( FE_LOGINSERVER, mLoginServerID, inet_addr( tIP ), tPort );

	SplitSockAddr(mGmCmdServerPort.c_str(), tIP, tPort );

	if ( mProxyClient.ConnectToServer() )
	{
		LOG_ERROR( "default", "Connect to ProxyServer(%s) Faild(%d:%s)", 
				mProxyServerAddr.c_str(), errno, strerror(errno));
		return false;
	}else
	{
		LOG_INFO( "default", "Connect to ProxyServer(%s) OK", mProxyServerAddr.c_str());
	}

	return true;
}

// ***************************************************************
// Function:      Connect2Validate
// Description:   ������֤������
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           07/15/2009
// 
//***************************************************************
bool CLoginServer::Connect2Validate( )
{ 
	//char tIP[ 64 ] = {0};
	//short tPort = 0;
	//int tServerID = 2 ;

	//SplitSockAddr( mValidateServerAddr.c_str(), tIP, tPort  );
	//mValidateClient.Initialize( FE_LOGINSERVER, tServerID, inet_addr( tIP ), tPort );
	//		
	//if ( mValidateClient.ConnectToServer(  ) )
	//{
	//	LOG_ERROR( "default", "Connect to ValidateServer(%s)(id=%d) Faild(%d:%s)", 
	//		mValidateServerAddr.c_str(), tServerID, errno, strerror(errno));
	//	return false;
	//}else
	//{
	//	LOG_INFO( "default", "Connect to ProxyServer(%s)(id=%d) OK", mProxyServerAddr.c_str(), tServerID);
	//}

	return true;	
}

// ***************************************************************
// Function:      Regist2ValidateServer
// Description:   ����֤������������֤��Ϣ
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           07/15/2009
// 
//***************************************************************
bool CLoginServer::Regist2ValidateServer(  )
{ 
	if ( Connect2Validate() != true )
	{		  	
		return false;	
	}	
	
	CMessage tMsgHead;
	CMessageServerValidateRequest tMsgValidate;		
	char tMacAddr[32] = { 0 };
	char tIPAddr[32] = { 0 };
	GetNicInfoForLinux( tMacAddr, tIPAddr );
	tMsgValidate.set_macaddr( tMacAddr );
	tMsgValidate.set_ipaddr( tIPAddr );	  	
	tMsgHead.mutable_msghead( )->set_messageid( ID_S2V_SERVERVALIDATE_REQUEST );
	tMsgHead.set_msgpara( (int)&tMsgValidate );				
	Send2Validate( &tMsgHead );	  	
		
	int tRet = RecvValidateMsg( mConfig.nValidateConnetSecOutTime, mConfig.nValidateConnetUSecOutTime );
	if ( tRet != SUCCESS )
	{
		return false;
	}
	return true;
}	

bool CLoginServer::IsBlackIP(unsigned int nAddr)
{
	bool ret = false;
	for ( size_t i = 0; i < ARRAY_CNT(mConfig.nBlackIPList); ++i)
	{
		if ( mConfig.nBlackIPList[i] == 0) break; 

		if ( mConfig.nBlackIPList[i] == nAddr)
		{
			return true;
		}
	}

	return ret;
}

// ***************************************************************
// Function:      Send2Validate
// Description:   ����֤������������Ϣ�Ľӿ�
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           07/15/2009
// 
//***************************************************************
void CLoginServer::Send2Validate( CMessage *tpMsg )
{ 
	LK_ASSERT( tpMsg != NULL, return )
	char tMsgBuffer[ MAX_CODE_LEN ] = { 0 };		
	int	 tBufferLenth = sizeof( tMsgBuffer );		   	
	int tLen = CodeMsgToBuffer( tMsgBuffer, tBufferLenth, *tpMsg );
	if ( tLen == -1 )
	{
		return;
	}	
	int tRet = mValidateClient.GetSocket()->SendOneCode( tLen, ( BYTE * ) tMsgBuffer );	
	if ( tRet != 0 )
	{
		LOG_ERROR( "default","Error occured when send message to ValidateServer!" );
	}	
}	


#ifdef USING_ERATING
// ***************************************************************
// Function:       UpdateERatingBindStatus
// Description:    ����ERatingServer
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::UpdateERatingBindStatus(bool is_binded)
{
	if ( IsERatingBinded() != is_binded)
	{
		LOG_INFO("default", "ERating Server Bind Status from %s to %s", 
				IsERatingBinded() ? "bind" : "unbind", is_binded? "bind" : "unbind"); 

		CMessage tMessage;

		CMessageERatingStateNotice tParaMessage;

		tParaMessage.set_gatewayid(mSingleWorld.mRegistID);
		tParaMessage.set_binded(is_binded ? 1 : 0);

		pbmsg_sethead(&tMessage,ID_L2G_ERATING_STATUS_NOTICE, 0, 0, 0, 0, 0, 0);
		tMessage.set_msgpara((uint32_t) &tParaMessage);
		Send2Gate(&tMessage);

		mERatingIsBinded = is_binded;
	}
}

// ***************************************************************
// Function:       ConnectToERatingServer
// Description:    ����ERatingServer
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
bool CLoginServer::Connect2ERating(eLinkMode emBlock)
{
	char tIP[ 64 ] = {0};
	short tPort = 0;
	int tServerID = 2 ;

	SplitSockAddr(mERatingServerAddr.c_str(), tIP, tPort );
	mERatingClient.Initialize( FE_GATESERVER, tServerID, inet_addr( tIP ), tPort );

	//SplitSockAddr(mGmCmdServerPort.c_str(), tIP, tPort );

	return mERatingClient.ConnectToServer(tIP, emBlock) == 0;
}
	
// ***************************************************************
// Function:       CreateSession4Proto
// Description:    ��ERatingServer����ע����Ϣ��
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
CAGIPSession* CLoginLogic::CreateSession4Proto(SysProtocol* pproto)
{
	// ��������Session, �����������Ϣָ��
	CAGIPSession* pSession= (CAGIPSession*) CLoginObjManager::GetSingletonPtr()->CreateObject(OBJTYPE_AGIPSESSION);
	if (pSession == NULL)
	{
		LOG_ERROR("default", "alloc an AGIPSession failure from objects pool.");
		return NULL;
	}

	int session_id = pSession->get_id();
	pproto->setSequenceID(session_id);

	unsigned int nCommandID = 0;
	pproto->getCommandID(&nCommandID);

	// ����GatewayID
	pproto->setGatewayID(GetRatingID());

	// ���û����GameID, ��ʹ��Ĭ��ֵ
	if (pproto->getGameID() == 0)
	{
		pproto->setGameID(mSingleWorld.mGameID);
	}

#ifdef _ECHARGE_DEBUG_
	if ( nCommandID != CMD_HANDSET_RES) 
	{
		printf(" send to erating {\n");

		pproto->showInfo();

		printf("}\n");
	}
#endif

	// ���ɶ����ư�
	unsigned char message_buffer[AGIP_MAX_BUFFER_SIZE+1];
	int message_length;

#ifdef USE_DECRYPTION_PROTOCAL
	int result = pproto->getEncodedPDU(message_buffer, AGIP_MAX_BUFFER_SIZE, &message_length);
#else
	int result = pproto->getDecodedPDU(message_buffer, AGIP_MAX_BUFFER_SIZE, &message_length);
#endif


	if (result != S_SUCCESS)
	{
		// ɾ��������Session
		CLoginObjManager::GetSingletonPtr()->DestroyObject(pSession->get_id());
		LOG_ERROR("default", "getEncodePDU/getDeCodePDU failure, Proto(%x), error:%d", nCommandID, result);
		return NULL;
	}

	if (CLoginServer::GetSingleton().Send2ERating(message_buffer, message_length) != true)
	{
		LOG_ERROR("default", "Send2ERating AGIPMsg(%d) Error", nCommandID);
		CLoginObjManager::GetSingletonPtr()->DestroyObject(pSession->get_id());
		pSession = NULL;
	}

	return pSession;
}
// ***************************************************************
// Function:       SendHandset
// Description:    ��ERatingServer����ע����Ϣ��
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::SendHandsetProto2ERating()
{
	AGIPHandset proto;

	CAGIPSession* pSession = CreateSession4Proto(&proto);

	if (pSession != NULL)
	{
		int session_id = pSession->get_id();

		#ifdef _DEBUG_
		LOG_DEBUG("default", "Send2ERating: MsgName[AGIPHandset] MsgSeq[%d] MsgPara[]", session_id);
		#endif

		// ���뵽Session �б�
		pSession->assign(session_id, em_agipsession_handset, 0, 0, 
				CLoginServer::GetSingleton().mConfig.nERatingHandsetInterval);
	}
}

void CLoginLogic:: OnAGIPMsgHandsetResponse(SysProtocol* pSysProto, int nParam1, int nParam2){
	AGIPHandsetRes* pproto = (AGIPHandsetRes*) pSysProto;
	LK_ASSERT(pproto != NULL, return);

	if ( pproto != NULL) 
	{
		// ȡ����Ϣ��CommandID, ����ǿ��ת��
		unsigned int nCommandID = 0;
		pSysProto->getCommandID(&nCommandID);
		LK_ASSERT(nCommandID == CMD_HANDSET_RES, return);

		UpdateERatingBindStatus(true);
	}														  
}


// ***************************************************************
// Function:       UnbindGate2ERatingServer
// Description:    ��ERatingServer����ע����Ϣ��
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************

void CLoginLogic::SendUnbindProto2ERating()
{
	AGIPUnbind proto;
	int nWorldIndex = mSingleWorld.mRegistID;

	proto.setGatewayID(nWorldIndex);

	CAGIPSession* pSession = CreateSession4Proto(&proto);

	if (pSession != NULL)
	{
		int session_id = pSession->get_id();

		#ifdef _DEBUG_
		LOG_DEBUG("default", "Send2ERating: MsgName[AGIPUnbind] MsgSeq[%d] MsgPara[GateIndex:%d]", 
				session_id, nWorldIndex);
		#endif

		// ���뵽Session �б�
		pSession->assign(session_id, em_agipsession_unbind, nWorldIndex, 0, 
				CLoginServer::GetSingleton().mConfig.nEratingSessionTimeout);
	}
}

void CLoginLogic:: OnAGIPMsgUnbindResponse(SysProtocol* pSysProto, int nParam1, int nParam2)
{
	AGIPUnbindRes* pproto = (AGIPUnbindRes*) pSysProto;
	LK_ASSERT(pproto != NULL, return);

	if ( pproto != NULL) 
	{
		// ȡ����Ϣ��CommandID, ����ǿ��ת��
		unsigned int nCommandID = 0;
		pSysProto->getCommandID(&nCommandID);
		LK_ASSERT(nCommandID == CMD_UNBIND_RES, return);

		// ȡ����Ϣ�������
		int32_t nResultCode;
		pproto->getResultCode(&nResultCode);
		//TODO: ���ʧ�ܣ��޷��ҵ���ң��޷�����ҷ����κ���Ϣ
		if(nResultCode != S_SUCCESS)
		{
			LOG_ERROR("default", "Unbind Gate(%d) From ERATING ERROR(%d)", nParam1, nResultCode);
		}else
		{
			LOG_INFO("default", "Unbind Gate(%d) From ERATING SUCCESS", nParam1);
		}
	}
}

// ***************************************************************
// Function:       BindGate2ERatingServer
// Description:    ��ERatingServer����ע����Ϣ��
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::SendBindProto2ERating(em_connect_erating_flag emConnect)
{
	AGIPBind proto;

	proto.setGatewayCode(mSingleWorld.mGateCode);
	proto.setPassword(mSingleWorld.mGatePasswd);
	proto.setMAC(mSingleWorld.mGateMac);
	proto.setReconnectFlag(emConnect);
	proto.setServerID(0);		//default 0


	CAGIPSession* pSession = CreateSession4Proto(&proto);

	if (pSession != NULL)
	{
		int session_id = pSession->get_id();

		#ifdef _DEBUG_
		LOG_DEBUG("default", "Send2ERating: MsgName[AGIPBind] MsgSeq[%d] MsgPara[GateWayCode:%s Password:%s "
			"Mac:%s, ReconnectFlag:%d ServerID: %d GameID: %d]", 
			session_id, mSingleWorld.mGateCode, mSingleWorld.mGatePasswd, 
			mSingleWorld.mGateMac, emConnect , 0, proto.getGameID());
		#endif

		// ���뵽Session �б�
		pSession->assign(session_id, em_agipsession_bind, 0, 0,  
				CLoginServer::GetSingleton().mConfig.nEratingSessionTimeout);
	}
}
#endif

// ***************************************************************
// Function:       Send2Player
// Description:    ����ҷ�����Ϣ��
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
	
void CLoginServer::Send2PlayerImp(CLoginPlayer* tpPlayer, CMessage* pMessage)
{
	if(tpPlayer == NULL) return;

	mClientHandle->Send(pMessage, tpPlayer);
}

// ***************************************************************
// Function:       Send2ERating
// Description:    ��ERating������Ϣ��
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
bool CLoginServer::Send2ERating(BYTE* pMessage, int vMsgLen)
{
	LOG_DEBUG("default", "Send2ERating MsgLen(%d)", vMsgLen);
	mTmSend2Erating = time(0);

	return mERatingClient.GetSocket()->SendOneCode(vMsgLen, pMessage) == 0;
}

// ***************************************************************
// Function:       Send2ProxyImp
// Description:    ��ĳ�����緢����Ϣ��
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
int CLoginServer::Send2ProxyImp(BYTE* pMessage, int vMsgLen)
{
	return mProxyClient.GetSocket()->SendOneCode(vMsgLen, pMessage);
}


// ********************************************************************** //
// CLoginLogic
// ********************************************************************** //
template<> CLoginLogic* CSingleton< CLoginLogic >::spSingleton = NULL;
CSharedMem* CLoginLogic::mShmPtr = NULL; 

// ***************************************************************
// Function:       new
// Description:    ����CloginLogic ��new����, ����������create�������ڴ�ش���
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void* CLoginLogic::operator new( size_t size )
{
	return ( void* ) mShmPtr->CreateSegment( size );
}

// ***************************************************************
// Function:       delete
// Description:    ����CloginLogic ��delete����
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void  CLoginLogic::operator delete( void* pointer )
{

}

// ***************************************************************
// Function:       CountSize
// Description:    ����CLoginLogic�Ĵ�С 
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
unsigned int CLoginLogic::CountSize()
{
	return sizeof(CLoginLogic);
}

// ***************************************************************
// Function:       Initialize
// Description:    ��ʼ��LoginLogic�ĳ�Ա����
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::Initialize()
{
	mPlayerContainer.initailize();
	mPlayerConnected.initailize();
	//mLoginQueue.initailize();
	
	mCurrentPlayerNumber = 0;
	mOnceLoginNumber = 0;
	mOnceLeaveNumber = CLoginServer::GetSingleton().mConfig.nMaxLoginPlayerOnceTimer;

	mERatingIsBinded = false;
	mServiceTurnedOn = false;

	mWaitTimer = CWTimer(CLoginServer::GetSingleton().mConfig.nLoginTimerInterval);
	
	#ifdef USING_ERATING
	mERatingHandsetTimer = CWTimer(CLoginServer::GetSingleton().mConfig.nERatingHandsetInterval);

	mTimerOfIbPay = CWTimer(CLoginServer::GetSingleton().mConfig.nIbPayRetryFirstInterval * 1000);

	#endif
}

// ***************************************************************
// Function:       Resume
// Description:    
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::Resume()
{

}

// ***************************************************************
// Function:       OnMessageLoginServerRequest
// Description:    ��Ӧ��ҵ�½����������
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnMessageLoginServerRequest( int vCommHandle, CMessage* pMessage)
{
	LK_ASSERT(pMessage != NULL && pMessage->msgpara() != 0, return);
	CMessageLoginServerRequest* tpLoginRequest = (CMessageLoginServerRequest*) pMessage->msgpara();

	CMessage tMessage;
	CMessageLoginErrorNotice tErrorNotice;

	CLoginPlayer* tpPlayer = GetPlayerByComm(vCommHandle);
	if (tpPlayer == NULL) return;

	if ( CLoginServer::GetSingleton().mConfig.bLoginServiced == false)
	{
		bool iswhite = false;
		for ( int i = 0; i < const_whitelist_limit; ++i)
		{
			if (CLoginServer::GetSingleton().mConfig.szWhiteNameList[i][0] == 0) 
			{
				break;
			}

			if (strcmp(CLoginServer::GetSingleton().mConfig.szWhiteNameList[i], 
						tpLoginRequest->username().c_str()) == 0)
			{
				iswhite = true;	
				break;
			}
		}

		if (iswhite == false)
		{
			SendLoginErrorNotice(tpPlayer, ELOGIN_SERVER_BE_MAINTENANCE);
			return;
		}
	}

	// ���������Ƿ���
	if ( mServiceTurnedOn == false )
	{
		SendLoginErrorNotice(tpPlayer, ELOGIN_THEWORLD_ISNOT_OPEN);
		return;
	}

	// ���δ����md5У��
	if(CLoginServer::GetSingleton().mConfig.bVerifyClientMd5Code == true)
	{
		CLoginServerConfigure::MD5LIST::iterator it = 
			CLoginServer::GetSingleton().mConfig.mClientMD5List.find( tpLoginRequest->version() );
		LOG_DEBUG("default", "verify ver: %d ", tpLoginRequest->version() );
		 if( it == CLoginServer::GetSingleton().mConfig.mClientMD5List.end() )
		 {
			 LOG_DEBUG("default", "verify ver: %d failed", tpLoginRequest->version() );
			 SendLoginErrorNotice(tpPlayer, ELOGIN_CLIENT_VERSION_NOTMATCH);
			return;
		 }
	
		 if( memcmp( (it->second).c_str(), tpLoginRequest->md5code().c_str(), const_md5code_length) != 0)
		 {
			 LOG_DEBUG("default", "verify ver: %d failed md5", tpLoginRequest->version() );
			 SendLoginErrorNotice(tpPlayer, ELOGIN_CLIENT_MD5CODE_NOTMATCH);
			return;
		 }

	}

	// ��ֹ����������ڴ�δ������ɵı���
	int minMemory = 0;
	minMemory = std::min( sizeof(tpPlayer->mUserName), tpLoginRequest->username().length() );
	memcpy(tpPlayer->mUserName, tpLoginRequest->username().c_str(), minMemory);
	tpPlayer->mUserName[sizeof(tpPlayer->mUserName)-1] = 0;

	if(tpPlayer->IsPartner())
	{
		char buffer[12] = {0};
		memcpy(buffer, tpPlayer->mUserName, 4);
		tpPlayer->m_nGameID = atoi(&buffer[1]);
	}
	else
	{
		tpPlayer->m_nGameID = mSingleWorld.mGameID;
	}

	minMemory = std::min( sizeof(tpPlayer->mUserPasswd), tpLoginRequest->userpsw().length() );
	memcpy(tpPlayer->mUserPasswd, tpLoginRequest->userpsw().c_str(), minMemory);
	tpPlayer->mUserPasswd[sizeof(tpPlayer->mUserPasswd)-1] = 0;

	if ( tpLoginRequest->has_matrixtype() && tpLoginRequest->matrixtype() != 0)
	{
		tpPlayer->m_nMatrixType = tpLoginRequest->matrixtype();
	
		minMemory = std::min( sizeof(tpPlayer->m_szMatrixCode), tpLoginRequest->matrixcode().length() );
		strncpy(tpPlayer->m_szMatrixCode, tpLoginRequest->matrixcode().c_str(), minMemory);
		tpPlayer->m_szMatrixCode[sizeof(tpPlayer->m_szMatrixCode)-1] = 0;
		
		minMemory = std::min( sizeof(tpPlayer->m_szMatrixCoord), tpLoginRequest->matrixcoord().length() );
		strncpy(tpPlayer->m_szMatrixCoord, tpLoginRequest->matrixcoord().c_str(), minMemory );
		tpPlayer->m_szMatrixCoord[sizeof(tpPlayer->m_szMatrixCoord)-1] = 0;
	}

	if ( tpLoginRequest->has_mac() && tpLoginRequest->mac().c_str() != NULL)
	{
		minMemory = std::min( sizeof(tpPlayer->m_szMac), tpLoginRequest->mac().length() );
		strncpy(tpPlayer->m_szMac, tpLoginRequest->mac().c_str(), minMemory);
		tpPlayer->m_szMac[sizeof(tpPlayer->m_szMac)-1] = 0;
	}

	tpPlayer->m_nDiskID = tpLoginRequest->diskid();
	tpPlayer->m_nCpuID = tpLoginRequest->cpuid();

	tpPlayer->mUrlID = tpLoginRequest->sourceid();

	// ������Ϸ����������
	if( mCurrentPlayerNumber >= CLoginServer::GetSingleton().mConfig.nMaxWorldPlayerNum )
	{
		SendLoginErrorNotice(tpPlayer, ELOGIN_THEWORLD_IS_FULLLIST);
		return ;
	}

	// ֻ�Ŷ�,����������
	mLoginQueue.push_back( tpPlayer->get_id() );

	// �������һ�����������¼���������򱨸�һ����ҵ�λ��
	if (mLoginQueue.size() > CLoginServer::GetSingleton().mConfig.nMaxLoginPlayerOnceTimer)
	{
		SendQueuePostion( tpPlayer, mLoginQueue.size() );
	}
}

void CLoginLogic::SendQueuePostion(CLoginPlayer* tpPlayer, size_t nPos)
{
	if (tpPlayer == NULL) return;

	CMessage tMessage;
	CMessageWaitForLoginNotice tFactMsg;
	// ���������Ϣ��֮������������Ͽ��˿ͻ�������

	tFactMsg.set_queuenumber(nPos);
	pbmsg_sethead(&tMessage, ID_L2C_NOTIFY_WAITFORQUEUE, 0, 0, 0, 0, 0, 0);
	tMessage.set_msgpara((uint32_t) &tFactMsg);
	Send2Client(tpPlayer, &tMessage );	
}

void CLoginLogic::PlayerLogin(CLoginPlayer* tpPlayer)
{
	// ���������Ƿ���
	if ( mServiceTurnedOn == false )
	{
		SendLoginErrorNotice(tpPlayer, ELOGIN_THEWORLD_ISNOT_OPEN);
		return;
	}

	// ��֤��ǰ�����Ƿ�����
	if ( mPlayerContainer.size() >= PLAYER_AT_LOGIN_CAP )
	{
		SendLoginErrorNotice(tpPlayer, ELOGIN_THEWORLD_IS_FULLLIST);
		return;
	}

	// ���۵�¼�Ƿ�ɹ���++
	// mOnceLoginNumber ++;

#ifndef TAIWAN
	// �˺���תСд
	LoginToLower( tpPlayer->mUserName, strnlen(tpPlayer->mUserName, sizeof(tpPlayer->mUserName)-1) );
#endif


	/*
	if ( tpPlayer->m_nMatrixType != 4)
	{
		SendLoginErrorNotice(tpPlayer, ELOGIN_CLIENT_NEED_MATRIXCODE);
		return;
	}
	*/

	#ifdef USING_ERATING
	// ���Eratingδ����
	if (IsERatingBinded() == true)
	{
		// ���������ǿ���߱�����֤
		if( CLoginServer::GetSingleton().mConfig.bVerifyByLocalForce == true )
		{
			VerifyAcctByLocal(tpPlayer);
		}
		else
		{
			SendUserLoginProto2ERating(tpPlayer);
		}
		
	}else
	{
		// �����������Ӫ��eratingδ������ֱ�ӷ���
		if ( tpPlayer->IsPartner() )
		{
			SendUserLoginProto2ERating(tpPlayer);
		}else
		{
			VerifyAcctByLocal(tpPlayer);
		}
	}
	#else
	VerifyAcctByLocal(tpPlayer);
	#endif

}

#ifdef USING_ERATING
// ***************************************************************
// Function:       VerifyByERating
// Description:    ��Ӧ���صĸ������ذ汾��Ϣ
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::SendUserLoginProto2ERating(CLoginPlayer* tpPlayer)
{
	LK_ASSERT(tpPlayer != NULL, return);

	AGIPJointAuthen protoA('<', '>');
	AGIPUserAuthEx protoB; 

	SysProtocol* pproto = NULL;

	if ( IsJoinAuth(tpPlayer))
	{
		char buffer[32];
		sprintf(buffer, "%d", tpPlayer->GetGameID());
		protoA.setParameter("GameID", buffer);

		sprintf(buffer, "%d", GetRatingID());
		protoA.setParameter("GWID",buffer);

		if ( tpPlayer->IsPartner())
		{
			protoA.setParameter("UN",&tpPlayer->mUserName[4]);
		}else
		{
			protoA.setParameter("UN",tpPlayer->mUserName);
		}

		if (tpPlayer->IsPartner())
		{
			// ������ǰ���ݰٶ���, �����Ķ��� PW
			if ( tpPlayer->GetGameID() == 724)
			{
				protoA.setParameter("SID",tpPlayer->mUserPasswd);
			}else
			{
				protoA.setParameter("PW",tpPlayer->mUserPasswd);
			}
		}else
		{
			protoA.setParameter("PW",tpPlayer->mUserPasswd);
		}

		sprintf(buffer, "%d", tpPlayer->mClientAddr); 
		protoA.setParameter("UserIP4", buffer);

		sprintf(buffer, "%d", tpPlayer->mClientPort);
		protoA.setParameter("Port", buffer);

		protoA.setParameter("MAC",tpPlayer->m_szMac); 

		sprintf(buffer, "%d", tpPlayer->mUrlID);
		protoA.setParameter("ADID",buffer);

		sprintf(buffer, "%u", tpPlayer->m_nCpuID);
		protoA.setParameter("HWSN1",buffer);

		sprintf(buffer, "%u", tpPlayer->m_nDiskID);
		protoA.setParameter("HWSN2",buffer);

		pproto = &protoA;

		LOG_INFO("default", "Send2ERating: MsgName[JointAuth] MsgSeq[%d] "
				"MsgPara[UserName:%s Password:%s PasswordType:%d, UserPort:%d UserIP: %d GameID:%d MAC:%s ]", 
				0, tpPlayer->mUserName,  tpPlayer->mUserPasswd,
				1, tpPlayer->mClientPort, tpPlayer->mClientAddr, tpPlayer->GetGameID(), tpPlayer->m_szMac);
	}else
	{
		protoB.setGameID(mSingleWorld.mGameID);
		protoB.setGatewayID(GetRatingID());

		protoB.setUserName(tpPlayer->mUserName);
		protoB.setPassword(tpPlayer->mUserPasswd);

		//1 �C ��ʾһ����¼����
		//3 �C ��ʾ�ܱ�������
		protoB.setPasswordType(tpPlayer->m_nMatrixType);

		protoB.setUserPort(htons(tpPlayer->mClientPort));
		protoB.setUserIP(htonl(tpPlayer->mClientAddr));
		protoB.setMAC(tpPlayer->m_szMac);

		// �ܱ�������
		protoB.setMatrixPassword(tpPlayer->m_szMatrixCode);

		// �ܱ��������Ӧ����
		protoB.setMatrixCoord(tpPlayer->m_szMatrixCoord);

		// ����AD
		char szUrlID[32+1];
		sprintf(szUrlID, "%d", tpPlayer->mUrlID);
		protoB.setADID(szUrlID);

		// ����CpuID
		sprintf(szUrlID, "%u", tpPlayer->m_nCpuID);
		protoB.setHardwareSN1(szUrlID);

		// ����DiskID
		sprintf(szUrlID, "%u", tpPlayer->m_nDiskID);
		protoB.setHardwareSN2(szUrlID);
		
		pproto = &protoB;
	}

	pproto->setGameID(tpPlayer->GetGameID());
	CAGIPSession* pSession = CreateSession4Proto(pproto);

	if (pSession != NULL)
	{
		int session_id = pSession->get_id();

		#ifdef _DEBUG_
		LOG_DEBUG("default", "Send2ERating: MsgName[AGIPUserLogin] MsgSeq[%d] "
				"MsgPara[UserName:%s Password:%s PasswordType:%d, UserPort:%d UserIP: %d GameID:%d MAC:%s ]", 
				session_id, tpPlayer->mUserName,  tpPlayer->mUserPasswd,
				1, tpPlayer->mClientPort, tpPlayer->mClientAddr, tpPlayer->GetGameID(), tpPlayer->m_szMac);
		#endif


		// ��������Session, �����������Ϣָ��
		pSession->assign(session_id, em_agipsession_userlogin, tpPlayer->get_id(), 0, 
				CLoginServer::GetSingleton().mConfig.nEratingSessionTimeout);
	}
}


// ***************************************************************
// Function:       OnAGIPMsgUserLoginResponse
// Description:    ��Ӧ��ERating��������Ϣ���
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic:: OnAGIPMsgUserLoginResponse(SysProtocol* pSysProto, int nParam1, int nParam2)
{
	LK_ASSERT(pSysProto != NULL && nParam1 != -1, return);

	// nParam1 �� CLoginPlayer::get_id()
	CLoginPlayer* tpPlayer = (CLoginPlayer*) CLoginObjManager::GetSingletonPtr()->GetObject(nParam1);
	if (tpPlayer == NULL)
	{
		LOG_INFO("default", "player(obj_id=%d) has left on function(%s)",  nParam1, __FUNCTION__);
		return;
	}

	// ȡ����Ϣ��CommandID, ����ǿ��ת��
	unsigned int nCommandID = 0;
	pSysProto->getCommandID(&nCommandID);


	AGIPJointAuthenRes* pProtoA = NULL;
	AGIPUserAuthRes* pProtoB = NULL;

	if ( IsJoinAuth(tpPlayer))
	{
		LK_ASSERT(nCommandID == CMD_JOINT_AUTHEN_RES, return);
		pProtoA = (AGIPJointAuthenRes*) pSysProto;
	}else
	{
		LK_ASSERT(nCommandID == CMD_USER_AUTH_EX_RES, return);
		pProtoB = (AGIPUserAuthRes*) pSysProto;
	}


	CMessage tMessage;
	CMessageLoginErrorNotice tErrorNotice;

	// ȡ����Ϣ�������
	int32_t nResultCode;
	if ( IsJoinAuth(tpPlayer))
	{
		nResultCode = pProtoA->getResultCode();
	}else
	{
		pProtoB->getResultCode(&nResultCode);
	}

	//TODO: ���ʧ�ܣ��޷��ҵ���ң��޷�����ҷ����κ���Ϣ
	switch (nResultCode)
	{
		case S_SUCCESS:
		#ifdef _TESTENV_
		case E_USER_IN_OTHER_GATEWAY:
		#endif
			break;

		case E_SYS_DATABASE_ERROR:
		case E_SYS_DATABASE_CONNECT_ERROR:
			{
				//tErrorNotice.set_errorcode(ELOGIN_VERIFY_ON_AGDBSQL);
				tpPlayer->mVerifiedByERating = false;
				LOG_INFO("default", "Account(%d) login ERating, Erating DB is error(%d).Using local", 
						nParam1, nResultCode);

				VerifyAcctByLocal(tpPlayer);
				return;
			}

		case E_USER_DYNAMIC_PSW_REQUIRED:
			{
				SendLoginErrorNotice(tpPlayer, ELOGIN_CLIENT_NEED_MATRIXCODE);
				return;
			}

		case E_USER_MATRIX_PASSWD_REQUIRED:
			{
				SendLoginErrorNotice(tpPlayer, ELOGIN_CLIENT_NEED_STATICMATRIXCODE);
				return;
			}
		case E_PASSCARD_NOT_CORRECT:
			{
				SendLoginErrorNotice(tpPlayer, ELOGIN_CLIENT_NEED_STATICMATRIXCODE);
				return;
			}

		case E_ERROR:
		case E_USER_ACCOUNT_ERROR:	
		case E_PARAMETER_ERROR:
		case E_USER_PASSWORD_ERROR:	
		case E_USER_STATE_FREEZED:
		#ifndef _TESTENV_
		case E_USER_IN_OTHER_GATEWAY:
		#endif
		default:
		{
			SendLoginErrorNotice(tpPlayer, nResultCode);
			return;
		}
	}

	uint32_t unUserID;
	int8_t cUserType;
	int8_t cAdultFlag;
	int8_t cUserClass;
	int8_t cUserRoleCount = 0;
	int32_t nUserPoint;
	uint32_t unPromoterID;
	uint32_t unUserFlag;
	uint32_t unSequenceID;

	if ( IsJoinAuth(tpPlayer))
	{
		unUserID = pProtoA->getUserID();      //���ID��
		cUserType  = pProtoA->getUserType();   //�������
		cAdultFlag = pProtoA->getAdultFlag(); //�����˱�־�� 1 �C ��ʾ�����ˣ� 0 �C ��ʾ�ǳ�����
		cUserClass = pProtoA->getUserClass(); //���VIP�ȼ�
		//pProtoA->getUserRoleCount(&cUserRoleCount); //������ڸù��������Ľ�ɫ����
		nUserPoint = pProtoA->getUserPoint();    //��һ���
		unPromoterID = pProtoA->getPromoterID(); //�ƹ�ԱID
		unUserFlag = pProtoA->getUserFlag();     //�����ǡ����磺���Ա�־�ȡ� ��Ҫ�ɿ������Ƶ�״̬�����ɴ�ά��
	}else
	{
		pProtoB->getUserID(&unUserID);      //���ID��
		#ifdef _TESTENV_
		if ( unUserID == 0) 
		{
			unUserID = atoi(&(tpPlayer->mUserName[2]));
		}
		#endif

		pProtoB->getUserType(&cUserType);   //�������
		pProtoB->getAdultFlag(&cAdultFlag); //�����˱�־�� 1 �C ��ʾ�����ˣ� 0 �C ��ʾ�ǳ�����
		pProtoB->getUserClass(&cUserClass); //���VIP�ȼ�
		//pProto->getUserRoleCount(&cUserRoleCount); //������ڸù��������Ľ�ɫ����
		pProtoB->getUserPoint(&nUserPoint);    //��һ���
		pProtoB->getPromoterID(&unPromoterID); //�ƹ�ԱID
		pProtoB->getUserFlag(&unUserFlag);     //�����ǡ����磺���Ա�־�ȡ� ��Ҫ�ɿ������Ƶ�״̬�����ɴ�ά��
	}

	pSysProto->getSequenceID(&unSequenceID);

	#ifdef _DEBUG_
	LOG_DEBUG("default", "Recv From ERating: MsgName[AGIPUserLoginRes] MsgSeq[%d] "
			"MsgPara[ ResultCode:%d UserID:%d UserType:%d UserRoleCount:%d UserName(%s) UserPasswd(%s)",  
			unSequenceID, nResultCode, unUserID, cUserType, cUserRoleCount,
			tpPlayer->mUserName, tpPlayer->mUserPasswd);
	#endif

	// �� AccountID ���и�ֵ
	tpPlayer->mAccountID = unUserID;
	tpPlayer->mUserClass = cUserClass;
	tpPlayer->mUserFlag = unUserFlag;
	tpPlayer->mUserPoint= nUserPoint;
	tpPlayer->mAdultFlag= cAdultFlag;


	tpPlayer->mVerifiedByERating = true;

	// �ڱ�����֤, �û���û�а취����
	VerifyAcctByLocal(tpPlayer);
}



#endif

// ***************************************************************
// Function:       OnMessageUpdateVersionNotice
// Description:    ��Ӧ���صĸ������ذ汾��Ϣ
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnMessageUpdateVersionNotice(CMessage* pMessage)
{
	LK_ASSERT(pMessage != NULL && pMessage->msgpara() != 0, return);
	//CMessageUpdateVersionNotice* tpUpdateVersion = (CMessageUpdateVersionNotice*) pMessage->msgpara();
	//LK_ASSERT(tpUpdateVersion != NULL, return);

	// TODO: ��Gate�İ汾������һ��ͳһ; �ҵ���Ӧ������, ������ID
	
	/*
	tpLogic->mTemplateVersion	= tpUpdateVersion->templateversion();
	tpLogic->mTaskVersion		= tpUpdateVersion->taskversion();
	*/
}

// ***************************************************************
// Function:       OnMessageGateInfoNotice
// Description:    ��Ӧ���ص�ע����Ϣ, �������ص���Ϣ���嵽mWorldServer��
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnMessageGateInfoNotice(CMessage* tpMessage)
{
	LK_ASSERT(tpMessage != NULL && tpMessage->msgpara() != 0, return);
	CMessageGateInfoNotice* tpHostInfo = (CMessageGateInfoNotice*) tpMessage->msgpara();

	CMessage tMessage;
	CMessageGateInfoResponse tGateInfo;
	CProxyHead tProxyHead;

	/*
	if (mServiceTurnedOn == true)
	{
		// TODO: �ظ�ע��
		tGateInfo.set_errorcode( ERROR_OUTOFDATE );
		tMessage.set_msgpara((uint32_t) &tGateInfo);
		pbmsg_sethead(&tMessage, ID_L2G_GATE_INFO_RESPONSE, 0, 0, 0, 0, 0, 0);
		Send2Gate(&tMessage);

		LOG_ERROR("default",  "�����ظ�ע��!");
		return;
	}else
	{
		*/

	mServiceTurnedOn = true;

	CWorldServer* pWorld = &mSingleWorld;

	strncpy(pWorld->mHostName, tpHostInfo->hostname().c_str(), sizeof(pWorld->mHostName));
	pWorld->mHostName[sizeof(pWorld->mHostName) - 1] = 0;

	strncpy(pWorld->mAddress, tpHostInfo->address().c_str(), sizeof(pWorld->mAddress));
	pWorld->mAddress[sizeof(pWorld->mAddress) - 1] = 0;

	pWorld->mWorldID = tpHostInfo->worldid();
	pWorld->mGameVersion = tpHostInfo->gateversion();

	// added by lihui @2010-01-11 
	pWorld->mGameID = tpHostInfo->gameid();
	CLoginServer::GetSingletonPtr()->ReadCfgByGameId(CLoginServer::GetSingletonPtr()->mConfig);


	tGateInfo.set_errorcode( 0 );
	tMessage.set_msgpara((uint32_t) &tGateInfo);
	pbmsg_sethead(&tMessage, ID_L2G_GATE_INFO_RESPONSE, 0, 0, 0, 0, 0, 0);
	Send2Gate(&tMessage);

	LOG_INFO("default",  "gateserver [%s:%s] report it's info to loginserver", 
					tpHostInfo->hostname().c_str(), tpHostInfo->address().c_str() );

	#ifdef USING_ERATING
	strncpy(pWorld->mGateCode, tpHostInfo->gatecode().c_str(), sizeof(pWorld->mGateCode));
	pWorld->mGateCode[sizeof(pWorld->mGateCode)-1] = 0;

	strncpy(pWorld->mGatePasswd, tpHostInfo->gatepasswd().c_str(), sizeof(pWorld->mGatePasswd));
	pWorld->mGatePasswd[sizeof(pWorld->mGatePasswd)-1] = 0;

	strncpy(pWorld->mGateMac, tpHostInfo->gatemac().c_str(), sizeof(pWorld->mGateMac));
	pWorld->mGateMac[sizeof(pWorld->mGateMac)-1] = 0;

	if ( CLoginServer::GetSingleton().IsConnected2ERating() == true)
	{
		SendBindProto2ERating(em_connect);
	}else
	{
		CMessage tMessage;
		CMessageERatingStateNotice tParaMessage;
		tParaMessage.set_binded(0);  //false

		pbmsg_sethead(&tMessage,ID_L2G_ERATING_STATUS_NOTICE, 0, 0, 0, 0, 0, 0);
		tMessage.set_msgpara((uint32_t) &tParaMessage);
		Send2Gate(&tMessage);
	}
	#endif
	//}
}

// ***************************************************************
// Function:       OnMessagePlayerLeaveGateNotice
// Description:    ��Ӧ����뿪��������
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnMessagePlayerLeaveGateNotice(CMessage* tpMessage)
{
	LK_ASSERT(tpMessage != NULL && tpMessage->msgpara() != 0, return);
	CMessagePlayerLeaveGateNotice* tpUserLeave = (CMessagePlayerLeaveGateNotice*) tpMessage->msgpara();

	// TODO: ���̴�����
	CLoginPlayer* tpPlayer = GetPlayerByAcct(tpUserLeave->accountid());
	if(tpPlayer != NULL) PlayerLeaveFromLogin(tpPlayer);
}

// ***************************************************************
// Function:       OnMessagePlayerEnterGateResponse
// Description:    ��Ӧ��ҽ��������Ӧ
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnMessagePlayerEnterGateResponse(CMessage* tpMessage)
{
	LK_ASSERT(tpMessage != NULL && tpMessage->msgpara() != 0, return);
	CMessagePlayerEnterGateResponse* tpLoginResponse = (CMessagePlayerEnterGateResponse*) tpMessage->msgpara();

	switch (tpLoginResponse->errorcode())
	{
		case 0:
		case ELOGIN_PLAYER_IN_GAMING:
		{
			// ��������
			CMessageRedirectGateNotice tRedirectGate;

			tRedirectGate.set_address(mSingleWorld.mAddress); 
			tRedirectGate.set_accountid(tpLoginResponse->accountid()); 
			tRedirectGate.set_logintoken(tpLoginResponse->logintoken() );
			if (tpLoginResponse->has_otherclient())
			{
				tRedirectGate.set_otherclient(tpLoginResponse->otherclient());
			}

			CMessage tMessage; 
			tMessage.set_msgpara((uint32_t) &tRedirectGate);
			pbmsg_sethead(&tMessage, ID_L2C_NOTIFY_REDIRECTGATE, 0, 0, 0, 0, 0, 0);

			CLoginPlayer* tpPlayer = GetPlayerByAcct(tpLoginResponse->accountid());
			if (tpPlayer == NULL)
			{
				LOG_INFO("default", "Player(account=%d) has left on %s", 
						tpLoginResponse->accountid(), __FUNCTION__);

				return;
			}

			//TODO: Ӧ��������ͻ��˶Ͽ�����, �������
			Send2Client(tpPlayer, &tMessage);

			UnRegistPlayerComm(tpLoginResponse->commhandle());

			mOnceLeaveNumber ++;
			tpPlayer->mWhere = CLoginPlayer::STATE_INGATE;
			break;
		}
		default:
		{
			CLoginPlayer* tpPlayer = GetPlayerByComm(tpLoginResponse->commhandle());
			if (tpPlayer == NULL)
			{
				LOG_INFO("default", "player has left on function %s.", __FUNCTION__);
				return;
			}

			SendLoginErrorNotice(tpPlayer, tpLoginResponse->errorcode());
			return;
		}
	}
}

// ***************************************************************
// Function:       OnMessagePlayerLoginCompleteNotice
// Description:    ��Ӧ��ҵ�¼�������֪ͨ
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnMessagePlayerLoginCompleteNotice(CMessage* tpMessage)
{
	LK_ASSERT(tpMessage != NULL && tpMessage->msgpara() != 0, return);
	CMessagePlayerLoginCompleteNotice* tpLoginComplete = (CMessagePlayerLoginCompleteNotice*) tpMessage->msgpara();

	CLoginPlayer* tpPlayer = GetPlayerByAcct(tpLoginComplete->accountid());

	if (tpPlayer != NULL)
	{
		tpPlayer->mWhere = CLoginPlayer::STATE_INGAME;

		//TODO: ĿǰLOGIN������������ң�ֻ�����ڵ�¼�е����
		PlayerLeaveFromLogin(tpPlayer);
	}
}

// ***************************************************************
// Function:       OnValidateMessage
// Description:	   ������֤����������Ϣ
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           07/15/2009
// 
//***************************************************************
void CLoginLogic::OnValidateMessage( CMessage *pMessage )
{
	LK_ASSERT( pMessage != NULL, return )
	switch( pMessage->mutable_msghead()->messageid() )	
	{
		case ID_V2S_SERVERVALIDATE_RESPONSE:
		{
			OnMessageValidateServerResponse( pMessage );
			break;
		}
	}
}

// ***************************************************************
// Function:       OnProxyMessage
// Description:    ��Ӧ�Ӹ���������ع�������Ϣ���
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnProxyMessage(CMessage* tpMessage)
{
	LK_ASSERT( tpMessage != NULL && tpMessage->msgpara() != 0, return );
	CMessageHead* tpHead = tpMessage->mutable_msghead();

	switch ( tpHead->messageid())
	{
		// ����������Ϣ
		case ID_G2L_UPDATE_VERSION_NOTICE:
		{
			OnMessageUpdateVersionNotice(tpMessage);
			break;
		}

		// ������Ϣ֪ͨ���������ط�������
		case ID_G2L_GATE_INFO_NOTICE:
		{
			OnMessageGateInfoNotice(tpMessage);
			break;
		}

		// ����뿪����֪ͨ���������ط�������
		case ID_G2L_PLAYER_LEAVE_GATE_NOTICE:
		{
			OnMessagePlayerLeaveGateNotice(tpMessage);
			break;
		}

		// ��ҵ�½��Ӧ���������ط�������
		case ID_G2L_PLAYER_ENTER_GATE_RESPONSE:
		{
			OnMessagePlayerEnterGateResponse(tpMessage);
			break;
		}

		// ��ҵ�½���֪ͨ���������ط�������
		case ID_G2S_PLAYER_LOGIN_COMPLETE_NOTICE:
		{
			OnMessagePlayerLoginCompleteNotice(tpMessage);
			break;
		}

		// �յ����ݿ��Ӧ����Ϣ
		case ID_S2S_EXECUTESQL_RESPONSE:
		{
			OnMessageExecuteSqlResponse(tpMessage);
			break;
		}

		case ID_G2L_GATE_SHUTDOWN_NOTICE:
		{
			OnMessageGateShutDownNotice(tpMessage);
			break;
		}

		// �յ�����������Ϣ
		case ID_G2L_HEARTBEAT_NOTICE:
		{
			OnMessageGateHeartBeatNotice(tpMessage);
			break;
		}		

		#ifdef USING_ERATING
		case ID_X2X_ERATING_PROTO_STREAM:
		{
			OnMessageERatingProtoStream(tpMessage);
			break;
		}

		case ID_G2M_CMDNORMAL_RESULT:
		case ID_G2M_ROLELOCATION_RESULT:
		case ID_G2M_TASKINFO_RESULT:
		case ID_G2M_ROLEEQUIPMENT_RESULT:
		case ID_G2M_ROLEPACKINFO_RESULT:
		case ID_G2M_ROLEITEMINPACK_RESULT:
		case ID_G2M_ROLESKILLINFO_RESULT:
		case ID_G2M_ROLEDETAIL_RESULT:
		case ID_G2M_ROLESKILLDETAIL_RESULT:
		case ID_G2M_USERSTORAGEINFO_RESULT:
		case ID_G2M_USERSOCIALINFO_RESULT:	 			
		case ID_G2S_RESPONSE_RESETROLEPASSWORD:	// ���������Ӧ��Ϣ
		case ID_G2M_SQL_QUERY_RESULT:
		case ID_G2M_USERINFOBYIP_RESULT:
		{
			CGmServer::GetSingleton().OnGMCmdMessageResult(tpMessage);
			break;
		}

		case ID_G2E_IBEXCHANGE_NOTICE:
		{
			CChargeServer::GetSingleton().OnMessageUserIbExchangeNotice(tpMessage);
			break;
		}

		case ID_S2E_IBITEMUSED_NOTICE:
		{
			CChargeServer::GetSingleton().OnMessageUserUseIbItemNotice(tpMessage);
			break;
		}
		#endif

		default:
		{
			LOG_ERROR("default", "there is no action for msgid(%d)",  tpHead->messageid()); 
		}
	}

	pbmsg_delmsg(tpMessage);
}
#ifdef USING_ERATING
// ***************************************************************
// Function:       OnMessageERatingProtoStream
// Description:    
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnMessageERatingProtoStream(CMessage* pMessage)
{
	LK_ASSERT( pMessage != NULL && pMessage->msgpara() != 0 , return );
	CMessageERatingProtoStream* pstream = (CMessageERatingProtoStream*) pMessage->msgpara();

	int message_length = pstream->length();
	unsigned char message_buffer[AGIP_MAX_BUFFER_SIZE+1];

	LK_ASSERT(message_length < AGIP_MAX_BUFFER_SIZE, return);


	memcpy(message_buffer, pstream->buffer().c_str(), message_length);

	CLoginServer::GetSingleton().Send2ERating(message_buffer, message_length);
}
#endif

// ***************************************************************
// Function:       OnMessageExecuteSqlResponse
// Description:    ��Ӧ�����������CMessage��Session
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::FireServerSession(int nSessionClass, CMessage* tpMessage, int nParam1, int nParam2)
{
	LK_ASSERT(tpMessage != NULL && tpMessage->msgpara() != 0, return);

	switch(nSessionClass)
	{
		case em_dbsession_verifyacctbymysql:
		{
			OnSessionVerifyAcctByMySql(tpMessage, nParam1, nParam2);
			break;
		}

#ifdef USING_ERATING
		case em_dbsession_roledetail:
		{
			CGmServer::GetSingleton().OnGmMessageRoleDetailResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_roleproto:
		{
			CGmServer::GetSingleton().OnGmMessageRoleProtoResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_ipbind:
		{
			CGmServer::GetSingleton().OnGmMessageNormalSqlDmlResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_chargeamount:
		{
			CChargeServer::GetSingleton().OnSessionChargeAmount(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_chargeaudit:
		{
			CChargeServer::GetSingleton().OnSessionChargeAudit(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_createaccount:
		{
			CChargeServer::GetSingleton().OnSessionCreateOrUpdateUser(tpMessage, nParam1, nParam2);
			break;
		}	

		case em_dbsession_currentibpay:
		{
			CChargeServer::GetSingleton().OnSessionLoadIbPayFromDB(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_ibpayres:
		{
			CChargeServer::GetSingleton().OnSessionUserIbPayRes(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_loadibused:
		{
			CChargeServer::GetSingleton().OnSessionLoadIbItemUsedFromDB(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_loadbourselog:
		{
			CChargeServer::GetSingleton( ).OnSessionLoadBourseLog( tpMessage, nParam1, nParam2 );
			break;
		}

		case em_dbsession_paylistquery:
		{
			CChargeServer::GetSingleton().OnSessionPayListQuery(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_paydetaildemand:
		{
			CChargeServer::GetSingleton().OnSessionPayDetailDemand(tpMessage, nParam1, nParam2);
			break;
		}

		//2009-07-01 ����
		case em_dbsession_goods2npc:
		{
			CGmServer::GetSingleton().OnGmMessageGoods2NpcResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_goodsfromnpc:
		{
			CGmServer::GetSingleton().OnGmMessageGoods4NpcResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_goodsbetweenusers:
		{
			CGmServer::GetSingleton().OnGmMessageGoodsAtUsersResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_goodshistory:
		{
			CGmServer::GetSingleton().OnGmMessageGoodsHistoryResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_operationdetail:
		{
			CGmServer::GetSingleton().OnGmMessageOperationDetailResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_roleitemoperate:
		{
			CGmServer::GetSingleton().OnGmMessageRoleItemOperateResult(tpMessage, nParam1, nParam2);
			break;
		}
		/*case em_dbsession_query_rolepickitemfromboss:
		{
			CGmServer::GetSingleton().OnGMMsgRolePickItemFromBossResult(tpMessage, nParam1, nParam2);
			break;
			
		}*/
		case em_dbsession_rolemoneyoperate:
		{
			CGmServer::GetSingleton().OnGmMessageRoleMoneyOperateResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_roleexpoperate:
		{
			CGmServer::GetSingleton().OnGmMessageRoleExpOperateResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_itemupgrade:
		{
			CGmServer::GetSingleton().OnGmMessageItemUpgradeResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_corpslist:
		{
			CGmServer::GetSingleton().OnGmMessageCorpsTotalResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_corpsdetail:
		{
			CGmServer::GetSingleton().OnGmMessageCorpsDetailResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_querydeath:
		{
			CGmServer::GetSingleton().OnGmMsgQueryDeathResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_querytask:
		{
			CGmServer::GetSingleton().OnGmMsgQueryTaskResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_querylogin:
		{
			CGmServer::GetSingleton().OnGmMsgQueryLoginResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_corpslog:
		{
			CGmServer::GetSingleton().OnGmMsgCorpsLogResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_familylog:
		{
			CGmServer::GetSingleton().OnGmMsgFamilyLogResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_recoverequip:
		{
			CGmServer::GetSingleton().OnGmMsgQueryRoleEquipResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_userlevel:
		{
			CGmServer::GetSingleton().OnGmMsgRoleLevelInfoResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_queryiplog:
		{
			CGmServer::GetSingleton().OnGmMsgQueryLogoutIPResult(tpMessage, nParam1, nParam2);
			break;
		}

		case em_dbsession_query_stock1:
		case em_dbsession_query_stock2:
		case em_dbsession_query_stock3:
		{
			CGmServer::GetSingleton().OnGmMsgQueryStockResult(tpMessage, nParam1, nParam2);
			break;
		}
		case em_dbsession_query_ybstall:
		{
			CGmServer::GetSingleton().OnGmMsgQueryYBStallResult(tpMessage, nParam1, nParam2);
			break;
		}
#endif

		default:
		{
			LOG_ERROR("default", "There is no action for the Session Class (%d) on function(%s)", 
					nSessionClass, __FUNCTION__);
			break;
		}
	}
}

void CLoginLogic::OnServerSessionTimeout(int nSessionClass, int nParam1, int nParam2)
{
	switch(nSessionClass)
	{
		case em_dbsession_verifyacctbymysql:
		{
			CLoginPlayer* tpPlayer = (CLoginPlayer*) CLoginObjManager::GetSingletonPtr()->GetObject(nParam1);
			if (tpPlayer == NULL)
			{
				LOG_INFO("default", "player(obj_id=%d) has left on function(%s)",  nParam1, __FUNCTION__);
				return;
			}

			LOG_INFO("default", "player(mCharName=%s) wait verifyacctbymysql timeout", tpPlayer->mUserName);
			SendLoginErrorNotice(tpPlayer, ELOGIN_VERIFY_BYMYSQL_TIMEOUT);

			break;
		}

		case em_dbsession_roledetail:
		case em_dbsession_roleproto:
		case em_dbsession_ipbind:
		case em_dbsession_goods2npc:
		case em_dbsession_goodsfromnpc:
		case em_dbsession_goodsbetweenusers:
		case em_dbsession_goodshistory:
		case em_dbsession_operationdetail:
		case em_dbsession_roleitemoperate:
		case em_dbsession_rolemoneyoperate:
		case em_dbsession_roleexpoperate:
		case em_dbsession_itemupgrade:
		case em_dbsession_corpslist:
		case em_dbsession_corpsdetail:
		case em_dbsession_userlevel:
		case em_dbsession_query_rolepickitemfromboss:
		{
			CGmServer::GetSingleton().Send2GMNormalResult(0, nParam1, nParam2);
			break;
		}

		case em_dbsession_chargeamount:
		case em_dbsession_chargeaudit:
		case em_dbsession_ibpayres:
		case em_dbsession_ibpayaudit:
		case em_dbsession_ibtranserror:
		case em_dbsession_paylistquery:
		case em_dbsession_paydetaildemand:
		{
			// TODO
			break;
		}

		case em_dbsession_currentibpay:
		{
			//��Ϊ��ʱ��������ԭ������dbsvrdû�з��ؽ��������loginsvrdһֱ��retry״̬
			CChargeServer::GetSingletonPtr()->SetRetrying(false);	
			break;
		}

		case em_dbsession_createaccount:
		{
			AGIPCreateOrUpdateUserRes* pprotores = (AGIPCreateOrUpdateUserRes* )nParam2;

			delete pprotores;
			break;
		}

		case em_dbsession_loadibused:
		{
			CChargeServer::GetSingletonPtr()->SetIsSendingIbItemUsed(false);
			break;
		}
	
		default:
		{
			LOG_ERROR("default", "There is no action for the Session Class (%d) on function(%s)", 
					nSessionClass, __FUNCTION__);
			break;
		}
	}
}

void CLoginLogic::OnMessageExecuteSqlResponse(CMessage* tpMessage)
{
	LK_ASSERT(tpMessage != NULL && tpMessage->msgpara() != 0, return);
	CMessageExecuteSqlResponse3* tpExecuteSql = (CMessageExecuteSqlResponse3*) tpMessage->msgpara();

	int nSessionID = tpExecuteSql->sessionid();
	CServerSession* pSession = NULL; 

	pSession = (CServerSession*) CLoginObjManager::GetSingletonPtr()->GetObject(nSessionID);
	if (pSession == NULL)
	{
		LOG_ERROR("default", "Get CServerSession object failure, SessionID(%d), ObjectID(%d)", nSessionID, nSessionID);
		return;
	}

	// �����󶨵���Ϣ
	FireServerSession(pSession->GetSessionType(), tpMessage, pSession->GetParam1(), pSession->GetParam2());

	// ɾ��Session����
	if ( pSession->GetParam4() == 0)
	{
		CLoginObjManager::GetSingletonPtr()->DestroyObject(nSessionID);
	}
}

void CLoginLogic::OnMessageGateShutDownNotice(CMessage* tpMessage)
{
	LK_ASSERT(tpMessage != NULL && tpMessage->msgpara() != 0, return);
	/*
	CMessageGateShutDownNotice* tGateShutDownNotice = (CMessageGateShutDownNotice*) tpMessage->msgpara();
	LK_ASSERT(tGateShutDownNotice != NULL, return);
	*/

#ifdef USING_ERATING
	SendUnbindProto2ERating();
#endif
	mServiceTurnedOn = false;
}

void CLoginLogic::OnMessageGateHeartBeatNotice(CMessage* tpMessage)
{
	LK_ASSERT(tpMessage != NULL && tpMessage->msgpara() != 0, return);
	CMessageGate2LoginHeartBeatNotice* tpHBNotice = (CMessageGate2LoginHeartBeatNotice*) tpMessage->msgpara();

	mCurrentPlayerNumber = tpHBNotice->playeratgate();

	return ;
}

// ***************************************************************
// Function:       OnClientMessage
// Description:    ��Ӧ�ӿͻ��˹�������Ϣ���
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnClientMessage(CMessage* tpMessage)
{
	LK_ASSERT( tpMessage != NULL && tpMessage->msgpara() != 0, return );
	CMessageHead* tpHead = tpMessage->mutable_msghead();

	int nCommHandle = tpHead->srcid();

	switch ( tpHead->messageid())
	{
		// ��ҵ�½����������
		case ID_C2L_REQUEST_LOGINSERVER:
		{
			OnMessageLoginServerRequest(nCommHandle, tpMessage);
			break;
		}

		case ID_S2G_CANCEL_LOGINQUEUE:
		{
			OnMessagePlayerCancelLoginQueue( nCommHandle, tpMessage  );
			break;
		}

		default:
		{
			LOG_INFO("default", "There is no action for msgid(%d)", tpHead->messageid());
			return;
		}
	}

}

void CLoginLogic::OnMessagePlayerCancelLoginQueue( int vCommHandle, CMessage* tpMessage)
{
	CLoginPlayer* tpPlayer = GetPlayerByComm(vCommHandle);
	if (tpPlayer == NULL) return;

	PlayerLeaveFromLogin(tpPlayer);
}

#ifdef USING_ERATING
// ***************************************************************
// Function:       OnAGIPMsgBindResponse
// Description:    Bind ��Ӧ������3�ֽ����ͨ����δͨ����ʹ�ñ�����֤
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnAGIPMsgBindResponse(SysProtocol* pSysProto, int nParam1, int nParam2)
{
	AGIPBindRes* pprotores = (AGIPBindRes*) pSysProto;
	LK_ASSERT(pprotores != NULL, return);

	if (pprotores != NULL)
	{
		// ȡ����Ϣ��CommandID, ����ǿ��ת��
		unsigned int nCommandID = 0;
		pSysProto->getCommandID(&nCommandID);
		LK_ASSERT(nCommandID == CMD_BIND_RES, return);


		int32_t nResultCode; 
		uint32_t nGatewayID;

		pprotores->getResultCode(&nResultCode);

		if (nResultCode == S_SUCCESS)
		{
			pprotores->getGatewayID(&nGatewayID);

			unsigned int session_id;
			pprotores->getSequenceID(&session_id);

			#ifdef _DEBUG_
			LOG_DEBUG("default", "Recv From ERating: MsgName[AGIPBindRes] MsgSeq[%d] MsgPara[ ResultCode:%d GatewayID:%d ]", 
					session_id, nResultCode, nGatewayID);
			#endif

			LOG_INFO("default", "loginserver bind to erating successfully by gateway id(%d)", nGatewayID);

			mSingleWorld.mRegistID = nGatewayID;

			UpdateERatingBindStatus(true);

		}else
		{
			switch (nResultCode)
			{
				case E_ERROR:
				case E_SYS_DATABASE_ERROR:
				case E_SYS_DATABASE_CONNECT_ERROR:
				{
					LOG_ERROR("default", "regist gateserver(%d) failure for reason(%d), "
							"game will run ont in erating control mode", nGatewayID, nResultCode);

					UpdateERatingBindStatus(false);
					return;
				}

				case E_GATEWAY_STATE_ERROR:
				case E_GATEWAY_NOT_FOUND:
				case E_PARAMETER_ERROR:
				case E_GATEWAY_UID_PWD_ERROR:
				{
					
					UpdateERatingBindStatus(false);

					// TODO: ��ͣ���������ӣ�֪�����ӳɹ�
					LOG_ERROR("default", "regist gateserver(%d) failure for reason(%d),"
							"game will not running until reconnect and bind erating successfully.", nGatewayID, nResultCode);
					return;
				}
			}
		}

	}
}

// ***************************************************************
// Function:       FireAGIPSession
// Description:    
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::FireAGIPSession(int nSessionClass, SysProtocol* pproto, int nParam1, int nParam2)
{
	LK_ASSERT(pproto != NULL, return);

	switch(nSessionClass)
	{
		case em_agipsession_handset:
		{
			OnAGIPMsgHandsetResponse(pproto, nParam1, nParam2);
			break;
		}

		case em_agipsession_unbind:
		{
			OnAGIPMsgUnbindResponse(pproto, nParam1, nParam2);
			break;
		}

		case em_agipsession_bind:
		{
			OnAGIPMsgBindResponse(pproto, nParam1, nParam2);
			break;
		}

		case em_agipsession_userlogin:
		{
			OnAGIPMsgUserLoginResponse(pproto, nParam1, nParam2);
			break;
		}


		case em_agipsession_ibitemused:
		{
			CChargeServer::GetSingleton().OnAGIPMsgUserUseProductRes(pproto, nParam1, nParam2);
			break;
		}

		case em_agipsession_ibexchange1:
		case em_agipsession_ibexchange2:
		case em_agipsession_ibexchange3:
		case em_agipsession_ibexchange4:
		{
			CChargeServer::GetSingleton().OnAGIPMsgUserIbPayRes(pproto, nParam1, nParam2);
			break;
		}
		case em_agipsession_exchange:
		{
			CChargeServer::GetSingletonPtr( )->OnAGIPMSGExchange( pproto, nParam1, nParam2 );
		}
		break;

		default:
		{
			LOG_ERROR("default", "There is no action for the Session Class (%d)", nSessionClass);
			break;
		}
	}

}

void CLoginLogic::OnAGIPSessionTimeout(int nSessionClass, int nParam1, int nParam2)
{
	switch(nSessionClass)
	{
		case em_agipsession_handset:
		{
			LOG_ERROR("default", "Handset to ERATING From ERATING TIMEOUT");
			UpdateERatingBindStatus(false);
			CLoginServer::GetSingleton().CloseERating();

			break;
		}

		case em_agipsession_unbind:
		{
			LOG_ERROR("default", "Unbind Gate(%d) From ERATING TIMEOUT", nParam1);
			break;
		}

		case em_agipsession_bind:
		{
			LOG_ERROR("default", "bind Gate(%d) From ERATING TIMEOUT", nParam1);
			UpdateERatingBindStatus(false);

			//close erating client, and when timeout, reconnect it.
			CLoginServer::GetSingleton().CloseERating();
			break;
		}

		case em_agipsession_userlogin:
		{
			// ��¼��ʱ
			CLoginPlayer* tpPlayer = (CLoginPlayer*) CLoginObjManager::GetSingletonPtr()->GetObject(nParam1); 
			if (tpPlayer == NULL) 
			{
				LOG_INFO("default", "player(obj_id=%d) has left on function(%s)", nParam1, __FUNCTION__);
				return;
			}else
			{
				LOG_INFO("default", "UserName(%s) login ERating timeout", tpPlayer->mUserName);
				VerifyAcctByLocal(tpPlayer);
			}

			break;
		}

		case em_agipsession_ibpayaudit:
		{
			uint64_t ullTransID = world_trans_id(nParam1, (uint32_t) nParam2);
			LOG_ERROR("default", "ibpayaudit(%lld) wait timeout , resend it!", ullTransID);

			break;
		}

		case em_agipsession_ibexchange1:
		case em_agipsession_ibexchange2:
		{
			uint64_t ullTransID = world_trans_id(nParam1, (uint32_t) nParam2);

			LOG_ERROR("default", "ibtransid (%lld) send timeout, wait resend!", ullTransID);
			CChargeServer::GetSingleton().UpdateIbExchangeNoticeError(nParam1, nParam2);

			break;	
		}
		case em_agipsession_exchange:
		{
			 CChargeServer::GetSingleton().UpdateExchangeError( nParam1, nParam2 );
		}

		default:
		{
			LOG_ERROR("default", "There is no action for the Session Class (%d)", nSessionClass);
			break;
		}
	}
}

void CLoginLogic::OnERatingMessage(SysProtocol* pProto)
{
	unsigned int nSessionID = 0; 
	pProto->getSequenceID(&nSessionID);

	CAGIPSession* pSession = NULL; 

	pSession = (CAGIPSession*)  CLoginObjManager::GetSingletonPtr()->GetObject(nSessionID);
	if (pSession == NULL)
	{
		LOG_ERROR("default", "Get agip session object failure, SessionID(%d), ObjectID(%d)", nSessionID, nSessionID);
		return;
	}

	// �����󶨵���Ϣ
	FireAGIPSession(pSession->GetSessionType(), pProto, pSession->GetParam1(), pSession->GetParam2());

	// ɾ��Session����
	CLoginObjManager::GetSingletonPtr()->DestroyObject(nSessionID);
}

#endif
// ***************************************************************
// Function:       RegistPlayerComm
// Description:    ע����Ҷ˿�
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::RegistPlayerComm(int nCommHandle, CLoginPlayer* tpPlayer)
{
	LK_ASSERT(tpPlayer != NULL, return);

	std::pair<PLAYERCONTAINER::iterator, bool>  ret = 
		mPlayerConnected.insert(PLAYERCONTAINER::value_type(nCommHandle, tpPlayer->get_id()));

	if (ret.second == false)
	{
		LOG_ERROR("default", "The port(%d) that player objid(%d) used will be replace by player obj(%d). pls check it",
				nCommHandle, ret.first->second, tpPlayer->get_id());

		ret.first->second = tpPlayer->get_id();
	}
}

// ***************************************************************
// Function:       PlayerLeaveFromLogin
// Description:    ����뿪��½������
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::PlayerLeaveFromLogin( CLoginPlayer* pPlayer)
{
	LK_ASSERT(pPlayer != NULL, return);

	if ( pPlayer->mWhere == CLoginPlayer::STATE_INWAIT || pPlayer->mWhere == CLoginPlayer::STATE_INLOGIN)
	{
		mOnceLeaveNumber ++;
	}

	switch (pPlayer->mWhere)
	{
		case CLoginPlayer::STATE_INLOGIN:
		case CLoginPlayer::STATE_INGATE:
		case CLoginPlayer::STATE_INGAME:
		{
			PLAYERCONTAINER::iterator iter4Acct = mPlayerContainer.find (pPlayer->mAccountID);
			if (iter4Acct != mPlayerContainer.end())
			{
				// ���ٶ���	
				CLoginObjManager::GetSingletonPtr()->DestroyObject(pPlayer->get_id());
				
				// ɾ������
				mPlayerContainer.erase(iter4Acct);
			}

			break;
		}

		case CLoginPlayer::STATE_INWAIT:
		{
			// ����ڵȴ������У��ǵ��Ƴ�
			QUEUEPLAYERCONTAINER::iterator iter4queue = mLoginQueue.begin();
			while(iter4queue != mLoginQueue.end())
			{
				if (pPlayer->get_id() == (*iter4queue)) 
				{
					iter4queue = mLoginQueue.erase(iter4queue);
					break;
				}
				iter4queue ++;
			}

			CLoginObjManager::GetSingletonPtr()->DestroyObject(pPlayer->get_id());
			break;
		}

		default:
		{
			LOG_INFO("default", "Player Account (%d) is invalide", pPlayer->mAccountID);
		}
	}
}

// ***************************************************************
// Function:       GetPlayerByComm
// Description:    ���ݶ˿ں�ȡ�����
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
CLoginPlayer* CLoginLogic::GetPlayerByComm( int nCommHandle )
{
	PLAYERCONTAINER::iterator iter =  mPlayerConnected.find(nCommHandle);
	if (iter != mPlayerConnected.end())
	{
		CLoginPlayer* pPlayer = (CLoginPlayer*) CLoginObjManager::GetSingletonPtr()->GetObject(iter->second); 
		if (pPlayer != NULL) 
		{
			if (pPlayer->mCommHandle == nCommHandle) 
			{
				return pPlayer;
			}else
			{
				LOG_ERROR("default", "Can NOT find player by the sockfd (%d)", nCommHandle);
				return NULL;
			}
		}
	}

	return NULL;
}

// ***************************************************************
// Function:       GetPlayerByAcct
// Description:    �����ʺ�ȡ�����
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
CLoginPlayer* CLoginLogic::GetPlayerByAcct( int nAccountID )
{
	PLAYERCONTAINER::iterator iter =  mPlayerContainer.find(nAccountID);
	if (iter != mPlayerContainer.end())
	{
		return (CLoginPlayer*) CLoginObjManager::GetSingletonPtr()->GetObject(iter->second); 
	}

	return NULL;
}

// ***************************************************************
// Function:       AccountVerify
// Description:    �ʺ���֤
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
int CLoginLogic::VerifyAcctByLocal( CLoginPlayer* tpPlayer)
{
	LK_ASSERT(tpPlayer != NULL, return -1);
	tpPlayer->mUserPasswd[CLoginPlayer::USER_PASSWD_DBLEN] = 0;
	if ( !ExecuteSql(em_dbsession_verifyacctbymysql, tpPlayer->get_id(), 0, 
				tpPlayer->mAccountID, SQL_NEED_CALLBACK, SELECT, "call ProcAccountVerify3rd( %d, %d, '%s', '%s', %d, %d, %d, %d, %d, %u )", 
				tpPlayer->mVerifiedByERating ? 1 : 0,  tpPlayer->mAccountID, 
				tpPlayer->mUserName, tpPlayer->mUserPasswd,
				tpPlayer->mUserClass, tpPlayer->mUserPoint, tpPlayer->mAdultFlag, tpPlayer->mUserFlag, tpPlayer->mUrlID,
				htonl(tpPlayer->mClientAddr)
				))
	{
		LOG_ERROR("default", "object pool create serversession error!");

		SendLoginErrorNotice(tpPlayer, ELOGIN_DBSESSION_IS_FULL);
		return -1;
	}

	return 0;
}

// ***************************************************************
// Function:       OnSessionVerifyAcctByMySql
// Description:    �ʺ���֤, �ɹ��������������
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnSessionVerifyAcctByMySql(CMessage* tpMessage, int vParamater1, int vParamater2 )
{
	LK_ASSERT(tpMessage != NULL && vParamater1 != 0 , return);

	CMessage tMessage;
	CMessageLoginErrorNotice tErrorNotice;
	CMessageExecuteSqlResponse3* pMessage = (CMessageExecuteSqlResponse3 *) tpMessage->msgpara();
	LK_ASSERT(pMessage != NULL, return);
	
	CLoginPlayer* tpPlayer = (CLoginPlayer*) CLoginObjManager::GetSingletonPtr()->GetObject(vParamater1);
	if (tpPlayer == NULL)
	{
		LOG_INFO("default", "player(obj_id=%d) has left on function(%s)",  vParamater1, __FUNCTION__);
		return;
	}

	int tRet = 0;
	if ( pMessage->resultcode() == 1 ) // �ɹ�ִ��
	{
		tRet = atoi(pMessage->fieldvalue(0).c_str());
		if ( tRet > 0 ) // fieldvalue(0) �� CharID
		{
			if ( tpPlayer->mVerifiedByERating == true ) 
			{
				LK_ASSERT(tpPlayer->mAccountID == tRet, return);

				// ���·������������Ϣ
				/*
				ExecuteSql(em_dbsession_null, 0, 0,
					tpPlayer->mAccountID, SQL_NONE, UPDATE,
						"update UMS_ACCOUNT set user_class = %d, user_point = %d, adult_flag = %d, user_flag = %d " 
						"where account_id = %d and user_name = '%s' ", 
						tpPlayer->mUserClass, tpPlayer->mUserPoint, tpPlayer->mAdultFlag, tpPlayer->mUserFlag, 
						tpPlayer->mAccountID, tpPlayer->mUserName);
				*/

				// Send2Erating ur linfo

			}else
			{
				// ��ȡ��ҵĻ�����Ϣ
				tpPlayer->mUserClass = atoi(pMessage->fieldvalue(2).c_str());	
				tpPlayer->mUserPoint = atoi(pMessage->fieldvalue(3).c_str());	
				tpPlayer->mAdultFlag = atoi(pMessage->fieldvalue(4).c_str());	
				tpPlayer->mUserFlag  = atoi(pMessage->fieldvalue(5).c_str());	

				tpPlayer->mAccountID = tRet;
			}

			// �����Ƿ�ͨ��eRating��֤ ������״̬
			tpPlayer->mStatus = atoi(pMessage->fieldvalue(1).c_str());	
		}else
		{
			memset(tpPlayer->mUserName, 0, sizeof(tpPlayer->mUserName));
			memset(tpPlayer->mUserPasswd, 0, sizeof(tpPlayer->mUserPasswd));
			SendLoginErrorNotice(tpPlayer, tRet);
			return;
		}

	}else
	{
		LOG_ERROR("default", " execute VerifyAcctByMySql failure");

		memset(tpPlayer->mUserName, 0, sizeof(tpPlayer->mUserName));
		memset(tpPlayer->mUserPasswd, 0, sizeof(tpPlayer->mUserPasswd));
		SendLoginErrorNotice(tpPlayer, ELOGIN_VERIFY_ON_DBSQL);
		return;
	}

	// ����ʺ��Ѿ���½, �����ʺ��ظ���¼, ��֮ǰ��¼�ĳ��
	PLAYERCONTAINER::iterator iter = mPlayerContainer.find(tpPlayer->mAccountID) ; 
	if( iter == mPlayerContainer.end( ) )
	{
		memset(tpPlayer->mUserName, 0, sizeof(tpPlayer->mUserName));
		memset(tpPlayer->mUserPasswd, 0, sizeof(tpPlayer->mUserPasswd));
		tpPlayer->mWhere = CLoginPlayer::STATE_INLOGIN;

		std::pair<PLAYERCONTAINER::iterator, bool> ret = 
			mPlayerContainer.insert( PLAYERCONTAINER::value_type(tpPlayer->mAccountID, tpPlayer->get_id()));

		if ( ret.second == true )
		{
			Push2Gate(tpPlayer );

			LOG_INFO("default", "player account_id(%d), account_name(%s) has logined the server. now online %d players",
				tpPlayer->mAccountID, tpPlayer->mUserName, mCurrentPlayerNumber);
		}else
		{
			LOG_ERROR("default", "PLAYERCONTAINER is full, it has %d player. why", mPlayerContainer.size()); 

			// ���ͷ�����������Ϣ
			SendLoginErrorNotice(tpPlayer, ELOGIN_THEWORLD_IS_FULLLIST);
		}
	}else
	{
		if (iter->second != tpPlayer->get_id())
		{
			CLoginPlayer* tpFirstPlayer = (CLoginPlayer*) CLoginObjManager::GetSingletonPtr()->GetObject(iter->second); 
			if(tpFirstPlayer == NULL) 
			{
				LOG_ERROR("default", "why the first player is null for account_id(%d) objid(%d)", 
						tpPlayer->mAccountID, iter->second);
			}

			// ����ͻ�����Ȼ������LOGIN, ��Ͽ�
			if (tpFirstPlayer && tpFirstPlayer->mWhere == CLoginPlayer::STATE_INLOGIN)
			{
				CMessage tMessage;
				CMessageLoginErrorNotice tErrorNotice;

				tErrorNotice.set_errorcode(ELOGIN_PLAYER_IN_RELOGINING);
				pbmsg_sethead(&tMessage, ID_L2C_NOTIFY_LOGINERROR, 0, 0, 0, 0, 0, 0);
				tMessage.set_msgpara((uint32_t) &tErrorNotice);
				Send2Client(tpFirstPlayer, &tMessage );	

				UnRegistPlayerComm(tpFirstPlayer->mCommHandle);
			}else // �����Ҳ��ڵ�¼������, ����Push2Gate
			{
				Push2Gate(tpPlayer );
			}

			//�õ�֮ǰ�����, ����
			CLoginObjManager::GetSingletonPtr()->DestroyObject(iter->second);
			mOnceLeaveNumber ++;

			//ʹ�õ�ǰ���
			iter->second = tpPlayer->get_id();


			LOG_INFO("default", "player account(%d, %s) relogin the server. now online %d players",
					tpPlayer->mAccountID, tpPlayer->mUserName, mCurrentPlayerNumber);
		}else
		{
			memset(tpPlayer->mUserName, 0, sizeof(tpPlayer->mUserName));
			memset(tpPlayer->mUserPasswd, 0, sizeof(tpPlayer->mUserPasswd));
			SendLoginErrorNotice(tpPlayer, ELOGIN_PLAYER_IN_LOGINING);
		}

		return;
	}
}
// ***************************************************************
// Function:       ExecuteSql
// Description:    ִ��SQL���
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
CServerSession* CLoginLogic::ExecuteSql( int vSessionType, int vParam1, int vParam2,
							int nFixID, int vCallBack, SQLTYPE vSqlType, const char * pSQL, ... )
{
	int nSessionID = 0;
	CServerSession* pSession= NULL;
	if ( vCallBack & SQL_NEED_CALLBACK )
	{
		pSession= (CServerSession*) CLoginObjManager::GetSingletonPtr()->CreateObject(OBJTYPE_SERVERSESSION);
		if (pSession == NULL) return NULL;

		nSessionID = pSession->get_id();
		pSession->assign( nSessionID, vSessionType, vParam1, vParam2,
				CLoginServer::GetSingleton().mConfig.nServerSessionTimeout);

		pSession->SetParam3(nFixID);
	}

	va_list tArgs;
	char tSqlCommand[ 30000 ] = { 0 };

	va_start( tArgs, pSQL );
	::vsprintf( tSqlCommand, pSQL, tArgs );
	va_end( tArgs );

	CMessageExecuteSqlRequest msg;
	msg.set_sessionid(nSessionID);
	msg.set_sql(tSqlCommand);
	msg.set_callback( vCallBack  );

	if( vCallBack & SQL_LATEST_INC_ID )
	{
		msg.set_latestautoincid(1);
	}

	msg.set_sqltype(vSqlType);
	msg.set_sessiontype( vParam1 );

	CMessage tMessage ;
	pbmsg_sethead(&tMessage, ID_S2S_EXECUTESQL_REQUEST, 0, 0, 0, 0, 0, 0);
	tMessage.set_msgpara((uint32_t) &msg);

	switch (vSessionType)
	{
		case em_dbsession_goods2npc:
		case em_dbsession_goodsfromnpc:
		case em_dbsession_goodsbetweenusers:
		case em_dbsession_goodshistory:
		case em_dbsession_operationdetail:
		case em_dbsession_roleitemoperate:
		case em_dbsession_rolemoneyoperate:
		case em_dbsession_roleexpoperate:
		case em_dbsession_itemupgrade:
		case em_dbsession_familylog:
		case em_dbsession_corpslog:
		case em_dbsession_querylogin:
		case em_dbsession_querydeath:
		case em_dbsession_querytask:
		case em_dbsession_recoverequip:
		case em_dbsession_userlevel:
		case em_dbsession_queryiplog:
		case em_dbsession_query_rolepickitemfromboss:
		{
			Send2Log( ID_S2S_EXECUTESQL_REQUEST, &tMessage );
			break;
		}

		default:
			Send2Data( nFixID, &tMessage );
	}

	return pSession;
}


// ***************************************************************
// Function:       OnTimer
// Description:    ��½������ʱ��
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnTimer( unsigned int vTickOffset )
{
	// ����Ŷ���Ѱʱ�䵽
	if ( mWaitTimer.Elapse( vTickOffset ) == true )
	{
		// ���AGIP��SESSION��ʱ
		#ifdef USING_ERATING
		CLoginObjManagerImp::ObjMng_AGIPSession* pAGIPSessions = NULL;
		if ( CLoginObjManager::GetSingleton().mLoginObjManagerImp != NULL)
		{
			pAGIPSessions = &(CLoginObjManager::GetSingleton().mLoginObjManagerImp->mAGIPSessionPool);
		}
		
		if ( pAGIPSessions == NULL) return;

		std::list< int > lstAGDelObjs;

		CLoginObjManagerImp::ObjMng_AGIPSession::iterator iter4ag = pAGIPSessions->begin();
		for(;iter4ag != pAGIPSessions->end(); iter4ag++)
		{
			CAGIPSession* pSession =  &(*iter4ag);
			if(pSession->GetTimer().Elapse( mWaitTimer.mMaxDuration) == true)
			{
				OnAGIPSessionTimeout(pSession->GetSessionType(), pSession->GetParam1(), pSession->GetParam2());
				lstAGDelObjs.push_back(pSession->get_id());
			}
		}

		std::list< int >::iterator iter = lstAGDelObjs.begin();
		for(; iter != lstAGDelObjs.end(); ++iter)
		{
			CLoginObjManager::GetSingletonPtr( )->DestroyObject(*iter);
		}

		#endif

		// ���DBSESSION �ĳ�ʱ
		CLoginObjManagerImp::ObjMng_ServerSession* pServerSessions = NULL;
		if ( CLoginObjManager::GetSingleton().mLoginObjManagerImp != NULL)
		{
			pServerSessions = &(CLoginObjManager::GetSingleton().mLoginObjManagerImp->mServerSessionPool);
		}

		std::list< int > lstDBDelObjs;

		CLoginObjManagerImp::ObjMng_ServerSession::iterator iter4db = pServerSessions->begin();
		for(;iter4db != pServerSessions->end(); iter4db++)
		{
			CServerSession* pSession =  &(*iter4db);
			if (pSession != NULL)
			{
				if(pSession->GetTimer().Elapse( mWaitTimer.mMaxDuration ) == true)
				{
					OnServerSessionTimeout(pSession->GetSessionType(), pSession->GetParam1(), pSession->GetParam2());
					lstDBDelObjs.push_back(pSession->get_id());
				}
			}
		}

		std::list< int >::iterator iter2 = lstDBDelObjs.begin();
		for(; iter2 != lstDBDelObjs.end(); ++iter2)
		{
			CLoginObjManager::GetSingletonPtr( )->DestroyObject(*iter2);
		}


		// ���Ƶ�¼������
		int nMaxPermit = CLoginServer::GetSingleton().mConfig.nMaxLoginPlayerOnceTimer;

		// ����ܵ�¼�����ϸ������뿪������
		// �˴��п�����ҵ�¼���س�ʱ,�������ʱ�뿪��¼���������Ӷ���ɵ�¼����

		if ( mLoginQueue.size() != 0)
		{
			// ����ϸ�����������뿪
			if (mOnceLeaveNumber > 0)
			{
				// ������֤������ 
				int nExistLogin = mOnceLeaveNumber < mOnceLoginNumber ? mOnceLoginNumber - mOnceLeaveNumber : 0; 

				// ����˴������¼������
				int nThisPermit = nExistLogin < nMaxPermit ? nMaxPermit - nExistLogin : 0;

				LOG_DEBUG("default", "BEGIN Login(%d) Logout(%d) Queue(%d) Permit(%d) ",  
					mOnceLoginNumber, mOnceLeaveNumber, mLoginQueue.size(), nThisPermit);

				int nThisLogin = 0;
				// �����������뿪�����ļ���
				mOnceLeaveNumber = 0;
				while(mLoginQueue.size() > 0 && nThisLogin < nThisPermit)
				{
					int one = mLoginQueue.front();
					CLoginPlayer* tpPlayer = (CLoginPlayer*) CLoginObjManager::GetSingletonPtr()->GetObject(one); 

					if (tpPlayer != NULL) 
					{
						PlayerLogin(tpPlayer);
					}

					mLoginQueue.pop_front();

					nThisLogin ++;
				}

				// ��¼���ص�¼������
				mOnceLoginNumber = nThisLogin;

				LOG_DEBUG("default", "END Login(%d) Logout(%d) Queue(%d) Permit(%d) ",  
					mOnceLoginNumber, mOnceLeaveNumber, mLoginQueue.size(), nThisPermit);
			}

			LOG_DEBUG("default", "NOT Login(%d) Logout(%d) Queue(%d)  ",  
				mOnceLoginNumber, mOnceLeaveNumber, mLoginQueue.size() );
		}else
		{
			// Ϊ�����׽�������
			if ( CLoginObjManager::GetSingleton().mLoginObjManagerImp->mPlayerAtLoginPool.size() == 0)
			{
				mOnceLeaveNumber = nMaxPermit;
			}
		}

		QUEUEPLAYERCONTAINER::iterator iter4queue = mLoginQueue.begin();
		while(iter4queue != mLoginQueue.end())
		{
			CLoginPlayer* tpPlayer = (CLoginPlayer*) CLoginObjManager::GetSingletonPtr()->GetObject(*iter4queue); 
			if (tpPlayer == NULL) 
			{
				iter4queue = mLoginQueue.erase(iter4queue);
				continue;
			}

			SendQueuePostion( tpPlayer, distance(mLoginQueue.begin(),  iter4queue)+1);
			iter4queue ++; 
		}

		// ��ERating����������Ϣ
		#ifdef USING_ERATING
		//if (mERatingHandsetTimer.Elapse(mWaitTimer.mMaxDuration) == true)
		int nNowSeconds = time(0);
		if ((nNowSeconds -  CLoginServer::GetSingleton().mTmSend2Erating) > mERatingHandsetTimer.mMaxDuration) 
		{
			if ( IsERatingBinded() == true)
			{
				CLoginServer::GetSingleton().mTmSend2Erating = nNowSeconds;
				SendHandsetProto2ERating();
			}
		}

		// ���ڴ����ݿ�load��IB���Ѽ�¼�ط�
		if (mTimerOfIbPay.Elapse(mWaitTimer.mMaxDuration) == true)
		{
			CChargeServer::GetSingleton().OnTimerOfIbPayRetry();
			//CChargeServer::GetSingleton().OnTimerOfIbUsedRetry();
			CChargeServer::GetSingleton( ).LoadBourseLog( );
		}


		#endif

		// �����ʱ��gate��״̬�ǹر�״̬������login�����˵�֪ͨ
		if (mServiceTurnedOn == false)
		{
			CMessage tMessage;		
			CMessageLoginSvrStartUpNotice tFactMsg;

			pbmsg_sethead(&tMessage,ID_L2G_LOGINSVRSTARTUP_NOTICE, 0, 0, 0, 0, 0, 0);
			tMessage.set_msgpara((uint32_t) &tFactMsg);
			Send2Gate(&tMessage);
		}
	}
}

// ***************************************************************
// Function:       Push2Gate
// Description:    �������������
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::Push2Gate(CLoginPlayer* pPlayer )
{
	LK_ASSERT( pPlayer != NULL, return );

	pPlayer->mLoginToken = rand();

	// ֪ͨ���ش�������
	CMessagePlayerEnterGateNotice tPlayerEnter;

	tPlayerEnter.set_commhandle(pPlayer->mCommHandle); 
	tPlayerEnter.set_logintoken(pPlayer->mLoginToken); 
	tPlayerEnter.set_accountid(pPlayer->mAccountID);

	tPlayerEnter.set_adultflag(pPlayer->mAdultFlag);
	tPlayerEnter.set_userclass(pPlayer->mUserClass);
	tPlayerEnter.set_userpoint(pPlayer->mUserPoint);
	tPlayerEnter.set_userflag(pPlayer->mUserFlag);

	tPlayerEnter.set_userstatus( pPlayer->mStatus );
	tPlayerEnter.set_gameid(pPlayer->GetGameID());

	tPlayerEnter.set_cpuid(pPlayer->m_nCpuID);
	tPlayerEnter.set_diskid(pPlayer->m_nDiskID);

	// �Ӵ��ϵ�¼����������������
	tPlayerEnter.set_worldplayerlimit( CLoginServer::GetSingleton().mConfig.nMaxWorldPlayerNum );

	CMessage tMessage;
	pbmsg_sethead(&tMessage, ID_L2G_PLAYER_ENTER_GATE_NOTICE, 0, 0, 0, 0, 0, 0);
	tMessage.set_msgpara((uint32_t) &tPlayerEnter);


	Send2Gate(&tMessage);
}

// ***************************************************************
// Function:       Send2Client
// Description:    �������ݵ���Ϸ�ͻ���
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::Send2Client( CLoginPlayer* pPlayer, CMessage* pMessage )
{
	CLoginServer::GetSingleton().Send2PlayerImp(pPlayer, pMessage);
}


// ***************************************************************
// Function:       CLoginLogic
// Description:    ���캯��
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
CLoginLogic::CLoginLogic()
{
	srand(time(0));

	if ( mShmPtr->GetInitMode () == SHM_INIT )
	{
		LOG_DEBUG( "default", "CLoginLogic Initailize");
		Initialize();
	}
	else
	{   
		LOG_DEBUG( "default", "CLoginLogic Resume");
		Resume();
	}   
}

// ***************************************************************
// Function:       Send2Gate
// Description:    �������ݵ�����
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::Send2Gate( CMessage* pMessage )
{
	char message_buffer[MAX_CODE_LEN];
	CProxyHead tProxyHead;

	pbmsg_setproxy(&tProxyHead, CET_OTHERSERVER, CET_OTHERSERVER, 1, 2, TRANS_P2P, CMD_NULL, NULL, 0);
	int message_length  = pbmsg_setmsg(tProxyHead, *pMessage, message_buffer, sizeof(message_buffer));

	LK_ASSERT( pMessage != NULL && pMessage->msgpara() != 0, return );
	Message* pUnknownMessagePara = (Message*) pMessage->msgpara();
	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessagePara->GetDescriptor();

	if (message_length > 0)
	{
		LOG_DEBUG("default", "Send2Gate: MsgName[%s] ProxyHead[%s] MsgHead[%s] MsgPara[%s]",
				pDescriptor->name().c_str(), tProxyHead.ShortDebugString().c_str(),
				pMessage->ShortDebugString().c_str(), ((Message*) pMessage->msgpara())->ShortDebugString().c_str());

		CLoginServer::GetSingleton().Send2ProxyImp((BYTE*)message_buffer, message_length);
	}
	else
	{
		LOG_ERROR("default", "pbmsg_setmsg encoding message (%x:%s) error",
				pMessage->msghead().messageid(), pDescriptor->name().c_str());
	}
}

void CLoginLogic::Send2AllScene(CMessage* pMessage)
{
	char message_buffer[MAX_CODE_LEN];
	CProxyHead tProxyHead;

	pbmsg_setproxy(&tProxyHead, CET_OTHERSERVER, CET_GAMESERVER, 1, 0, TRANS_P2G, CMD_NULL, NULL, 0);
	int message_length  = pbmsg_setmsg(tProxyHead, *pMessage, message_buffer, sizeof(message_buffer));

	LK_ASSERT( pMessage != NULL && pMessage->msgpara() != 0, return );
	Message* pUnknownMessagePara = (Message*) pMessage->msgpara();
	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessagePara->GetDescriptor();

	if (message_length > 0)
	{
		LOG_DEBUG("default", "Send2AllScene: MsgName[%s] ProxyHead[%s] MsgHead[%s] MsgPara[%s]",
				pDescriptor->name().c_str(), tProxyHead.ShortDebugString().c_str(),
				pMessage->ShortDebugString().c_str(), ((Message*) pMessage->msgpara())->ShortDebugString().c_str());

		CLoginServer::GetSingleton().Send2ProxyImp((BYTE*)message_buffer, message_length);
	}
	else
	{
		LOG_ERROR("default", "pbmsg_setmsg encoding message (%x:%s) error",
				pMessage->msghead().messageid(), pDescriptor->name().c_str());
	}
}

// ***************************************************************
// Function:       Send2Data
// Description:    �������ݵ�DBserver
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::Send2Data(int nFixID, CMessage* pMessage )
{
	CProxyHead tProxyHead;
	char message_buffer[MAX_CODE_LEN];
	pbmsg_setproxy(&tProxyHead, CET_OTHERSERVER, CET_DBSERVER, 1, 1, TRANS_P2P, CMD_NULL, NULL, 0);

	tProxyHead.set_uin(nFixID);
	int message_length = pbmsg_setmsg(tProxyHead, *pMessage, message_buffer, sizeof(message_buffer));

	LK_ASSERT( pMessage != NULL && pMessage->msgpara() != 0 , return  );
	Message* pUnknownMessagePara = (Message*) pMessage->msgpara();
	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessagePara->GetDescriptor();

	if (message_length > 0)
	{
		LOG_DEBUG("default", "Send2Data: MsgName[%s] ProxyHead=[%d:%s], MsgHead=[%s], Msgpara=[%s] ",
				 pDescriptor->name().c_str(), tProxyHead.ByteSize(), tProxyHead.ShortDebugString().c_str(), 
				 pMessage->ShortDebugString().c_str(), ((Message*) pMessage->msgpara())->ShortDebugString().c_str());

		CLoginServer::GetSingleton().Send2ProxyImp((BYTE*)message_buffer, message_length);
	}else
	{
		LOG_ERROR("default", "pbmsg_setmsg encoding message (%x:%s) error",
				pMessage->msghead().messageid(), pDescriptor->name().c_str());
	}
}

void CLoginLogic::Send2Log(int nFixID, CMessage* pMessage )
{
	CProxyHead tProxyHead;
	char message_buffer[MAX_CODE_LEN];
	pbmsg_setproxy(&tProxyHead, CET_OTHERSERVER, CET_OTHERSERVER, 1, 3, TRANS_P2P, CMD_NULL, NULL, 0);

	tProxyHead.set_uin(nFixID);
	int message_length = pbmsg_setmsg(tProxyHead, *pMessage, message_buffer, sizeof(message_buffer));

	LK_ASSERT( pMessage != NULL && pMessage->msgpara() != 0 , return  );
	Message* pUnknownMessagePara = (Message*) pMessage->msgpara();
	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessagePara->GetDescriptor();

	if (message_length > 0)
	{
		LOG_DEBUG("default", "Send2Log: MsgName[%s] ProxyHead=[%d:%s], MsgHead=[%s], Msgpara=[%s] ",
				 pDescriptor->name().c_str(), tProxyHead.ByteSize(), tProxyHead.ShortDebugString().c_str(), 
				 pMessage->ShortDebugString().c_str(), ((Message*) pMessage->msgpara())->ShortDebugString().c_str());

		CLoginServer::GetSingleton().Send2ProxyImp((BYTE*)message_buffer, message_length);
	}else
	{
		LOG_ERROR("default", "pbmsg_setmsg encoding message (%x:%s) error",
				pMessage->msghead().messageid(), pDescriptor->name().c_str());
	}
}

// ***************************************************************
// Function:       SendLoginErrorNotice
// Description:    ���ʹ�����뵽��Ϸ�ͻ���
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::SendLoginErrorNotice(CLoginPlayer* tpPlayer, int nErrorCode)
{
	if (tpPlayer == NULL)
		return;

	CMessage tMessage;
	CMessageLoginErrorNotice tErrorNotice;
	// ���������Ϣ��֮������������Ͽ��˿ͻ�������

	tErrorNotice.set_errorcode(nErrorCode);
	pbmsg_sethead(&tMessage, ID_L2C_NOTIFY_LOGINERROR, 0, 0, 0, 0, 0, 0);
	tMessage.set_msgpara((uint32_t) &tErrorNotice);
	Send2Client(tpPlayer, &tMessage );	

	UnRegistPlayerComm(tpPlayer->mCommHandle);

	if (nErrorCode != ELOGIN_PLAYER_IN_LOGINING)
	{
		PlayerLeaveFromLogin(tpPlayer);
	}
}


// ***************************************************************
// Function:       UnRegistPlayerComm
// Description:    ɾ����Ҷ˿�����
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::UnRegistPlayerComm(int nCommHandle)
{
	PLAYERCONTAINER::iterator iter = mPlayerConnected.find (nCommHandle);
	if (iter != mPlayerConnected.end())
	{
		CLoginPlayer* tpPlayer = (CLoginPlayer*) CLoginObjManager::GetSingletonPtr()->GetObject(iter->second); 
		if (tpPlayer != NULL && iter->second == tpPlayer->get_id())
		{
			mPlayerConnected.erase(iter);
		}
	}
}

// ***************************************************************
// Function:       OnReloadConfig
// Description:    �����յ�RELOAD������ʱ��,CLoginLogic��ʲô
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnReloadConfig()
{
	mWaitTimer = CWTimer(CLoginServer::GetSingleton().mConfig.nLoginTimerInterval);
	
	#ifdef USING_ERATING
	mERatingHandsetTimer = CWTimer(CLoginServer::GetSingleton().mConfig.nERatingHandsetInterval);
	#endif
}

// ***************************************************************
// Function:       GetRatingID
// Description:    ȡ����Ϸע�ᵽERATING,ERATING���ص�gatewayID
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
uint32_t CLoginLogic::GetRatingID()
{
	return mSingleWorld.mRegistID;
}

// ***************************************************************
// Function:       OnExit
// Description:    ���յ��˳��ź�ʱ��CLoginLogic��ʲô
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnExit()
{
	#ifdef USING_ERATING
	if (IsERatingBinded())
	{
		UpdateERatingBindStatus(false);
		SendUnbindProto2ERating();
	}
	#endif
}



void CLoginLogic::LoginToLower( char * pszSrc, size_t len)
{
	BYTE    cb;
	size_t  i;

	if (NULL == pszSrc)
	{
		return;
	}

	for (i=0; i<len; i++)
	{
		cb = *(BYTE *)(pszSrc + i);
		if (cb >='A' && cb<='Z')
		{
			*(BYTE *)(pszSrc + i) = (BYTE)(cb + 32);
		}
	}
}


// ***************************************************************
// Function:       OnMessageValidateServerResponse
// Description:    ��֤����������֤���
// Input:          
// OutPut:         
// Return:         ��
// Others:         
// Date:           10/29/2008
// 
//***************************************************************
void CLoginLogic::OnMessageValidateServerResponse( CMessage* pMessage )
{ 
	//LK_ASSERT( pMessage != NULL, return )	
	//CMessageServerValidateResponse *tpMsg = ( CMessageServerValidateResponse * )pMessage->msgpara();
	//LK_ASSERT( tpMsg != NULL, return )
	//if ( tpMsg->checkresult() == 1 )
	//{
	//	CLoginServer::GetSingleton().SetValidateStatusTrue( );
	//}
	//else
	//{
	//	CLoginServer::GetSingleton().SetValidateStatusFalse();
	//}
}

// ǰ��������ʺ��Ѿ���ֵ
bool CLoginLogic::IsJoinAuth(CLoginPlayer* tpPlayer)
{
#if YUENAN || TAIWAN
	return  true;
#endif

	return tpPlayer != NULL &&  tpPlayer->IsPartner();
}

//��ȡ config �����ļ���Ŀ¼
void CLoginLogic::GetConfigDataFileNamePath(int nGameID, char *filename, char *input, int len)
{
	memset(input,0,len);
	snprintf(input, len, "../config/data_%d/%s",nGameID,filename);
	FILE* file = fopen( input, "rb" );	
	if ( file )
	{
		return;
	}
	else
	{
		memset(input,0,len);
		snprintf(input, len, "../config/data/%s",filename);
	}
}

