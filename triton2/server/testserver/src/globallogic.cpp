//============================================================
// <T>ȫ�ַ�����</T>
//============================================================


//#include <sys/types.h>
//#include <sys/socket.h>
//#include <sys/time.h>
//#include <unistd.h>

#include <google/protobuf/descriptor.h>
#include "tinyxml.h"
#include "log.h"
#include "westserver.h"
#include "message_pb.hxx.pb.h"
#include "servermessage_in.h"
#include "coremessage_pb.hxx.pb.h"
#include "client_comm_engine.h"
#include "servermessage_pb.hxx.pb.h"
#include "ibstore.h"
#include <google/protobuf/descriptor.h>
#include "globallogic.h"

#include <list>

template<> CGlobalLoginModule* CSingleton<CGlobalLoginModule>::spSingleton = NULL;
CSharedMem* CGlobalLoginModule::mShmPtr = NULL; 

template<> CGlobalPlayerModule* CSingleton<CGlobalPlayerModule>::spSingleton = NULL;
CSharedMem* CGlobalPlayerModule::mShmPtr = NULL; 

template<> CGlobalCertifyPlayerModule* CSingleton<CGlobalCertifyPlayerModule>::spSingleton = NULL;
CSharedMem* CGlobalCertifyPlayerModule::mShmPtr = NULL; 

uint32 RTokenGenarator::_base = 0;
//============================================================
// <T>��½������ģ���С����</T>
//============================================================
unsigned int CGlobalLoginModule::CountSize(){
	return sizeof(CGlobalLoginModule);
}

//============================================================
// <T>��½������ģ���С����</T>
//============================================================
void* CGlobalLoginModule::operator new(size_t size){
	return (void*)CGlobalLoginModule::mShmPtr->CreateSegment(size);
}

//============================================================
// <T>��½������ģ���С����</T>
//============================================================
void  CGlobalLoginModule::operator delete(void* pointer){
}

//============================================================
// <T>��½������ģ���С����</T>
//============================================================
void* CGlobalLoginModule::operator new(size_t size, const char* file, int line){
	return (void*)mShmPtr->CreateSegment(size);
}

//============================================================
// <T>��½������ģ���С����</T>
//============================================================
void  CGlobalLoginModule::operator delete(void* pointer, const char* file, int line){
}

void CGlobalLoginModule::Initialize(){
	loginCount = 0;
	for(int i = 0;i < GS_LOGIN_MAXCOUNT;i ++){
		logins[i].Initialize();
	}
}

void CGlobalLoginModule::Resume(){
}

CGlobalLoginModule::CGlobalLoginModule(){
	srand(time(0));
	if ( mShmPtr->GetInitMode () == SHM_INIT )
	{
		LOG_DEBUG( "default", "CGlobalLoginModule Initailize");
		Initialize();
	}
	else
	{   
		LOG_DEBUG( "default", "CGlobalLoginModule Resume");
		Resume();
	} 
}

//============================================================
// <T>�õ�һ��������Ϣʵ��</T>
//============================================================
CGlobalLogin& CGlobalLoginModule::Alloc(){
	++loginCount;
	return logins[loginCount - 1];
}


//============================================================
// <T>��½������ģ���С����</T>
//============================================================
CGlobalLogin& CGlobalLoginModule::Get(int index){
	//LK_ASSERT((index > 0 && index < GS_LOGIN_MAXCOUNT),return);
	return logins[index];
}

//============================================================
// <T>��½������ģ���С����</T>
//============================================================

CGlobalLogin* CGlobalLoginModule::FindById(uint16 logseverId){
	for(int i = 0; i < loginCount; i++){
		if(logins[i].id == logseverId){
			return &logins[i];
		}
	}
	return NULL;
}

CGlobalLogin* CGlobalLoginModule::FindByHost(uint32 ipAddr){
	for(int i = 0; i < loginCount; i++){
		uint32 addr = inet_addr(logins[i].host);
		if(addr == ipAddr){
			return &logins[i];
		}
	}
	return NULL;
}

CGlobalLogin* CGlobalLoginModule::FindByHandle(uint16 handle){
	for(int i = 0; i < loginCount; i++){
		if(logins[i].handle == handle){
			return &logins[i];
		}
	}
	return NULL;
}

//============================================================
// <T>��ʼ��ȫ�ַ��������ģ��</T>
//============================================================
void CGlobalPlayerModule::Initialize(){
	for(int i = 0;i < GS_PLAYER_MAXCOUNT;i ++){
		players[i].Initialize();
	}
	_playerMap.initailize();
}

void CGlobalPlayerModule::Resume(){

}

//============================================================
// <T>����ȫ�ַ��������ģ��</T>
//============================================================
CGlobalPlayerModule::CGlobalPlayerModule(){
	srand(time(0));
	if ( mShmPtr->GetInitMode () == SHM_INIT )
	{
		LOG_DEBUG( "default", "CGlobalPlayerModule Initailize");
		Initialize();
	}
	else
	{   
		LOG_DEBUG( "default", "CGlobalPlayerModule Resume");
		Resume();
	} 
	
}
//============================================================
// <T>ȫ�ַ��������ģ���С����</T>
//============================================================
unsigned int CGlobalPlayerModule::CountSize(){
	
	return sizeof(CGlobalPlayerModule);
}

//============================================================
// <T>����new</T>
//============================================================
void* CGlobalPlayerModule::operator new(size_t size){
	return (void*)mShmPtr->CreateSegment(size);
}

//============================================================
// <T>����delete</T>
//============================================================
void  CGlobalPlayerModule::operator delete(void* pointer){

}

//============================================================
// <T>����new</T>
//============================================================
void* CGlobalPlayerModule::operator new(size_t size, const char* file, int line){
	return (void*)mShmPtr->CreateSegment(size);
}

//============================================================
// <T>����delete</T>
//============================================================
void  CGlobalPlayerModule::operator delete(void* pointer, const char* file, int line){

}

//============================================================
// <T>�����ṩ��Player��Ϣ�����ݿ��в��Ҳ���������ֶ�</T>
//============================================================
bool CGlobalPlayerModule::FetchPlayerInfos(CGlobalPlayer& pPlayer){
	if(!CGlobalPlayerData::GetSingleton().FetchByPassport(&pPlayer,pPlayer.passport)){
		return false;
	}
	return true;
	

}

//============================================================
// <T>��½������ģ���С����</T>
//============================================================
CGlobalServerConfiguration::CGlobalServerConfiguration(){
};

//============================================================
// <T>CGlobalServerʵ��</T>
//============================================================
template<> CGlobalServer* CSingleton< CGlobalServer >::spSingleton = NULL;
CSharedMem* CGlobalServer::mShmPtr = NULL; 


CGlobalServerConfiguration& CGlobalServer::Configuration(){  
	return mConfig; 
}

//============================================================
// <T>��½������ģ���С����</T>
//============================================================
int CGlobalServer::Initialize( int vInitFlag ){

	// 100323 MZYNG ADD-BEGIN
	// TODO�� ����Global server��ö������
	#define GLOBAL_SERVER_TYPE 10
	pLoginServer = new CTCPConn<RECVBUFLENGTH, POSTBUFLENGTH>();
	//for(int i = 0; i < GS_LOGIN_MAXCOUNT; i++){
	//	pLoginSockets[i]  = new CTCPSocket<RECVBUFLENGTH, POSTBUFLENGTH>();
	//	pLoginSockets[i]->CreateClient();
	//}
	CClientHandle::mShmPtr = mShmPtr;
	pClientHandle = new CClientHandle();
	pClientHandle->Initialize();
	// 100323 MZYNG ADD-END
	    
	CGlobalLogic::mShmPtr = mShmPtr;
	CGlobalLogic* tpLogic = new CGlobalLogic;

	CGlobalLoginModule::mShmPtr = mShmPtr;
	CGlobalLoginModule* tPLoginModule = new CGlobalLoginModule();

	CGlobalPlayerModule::mShmPtr = mShmPtr;
	CGlobalPlayerModule* tPlayerModule = new CGlobalPlayerModule();

	CGlobalCertifyPlayerModule::mShmPtr = mShmPtr;
	CGlobalCertifyPlayerModule* tpCertifyPlayerModule = new CGlobalCertifyPlayerModule;

	CMessageQueue::mShmPtr = mShmPtr;
	CMessageQueue* tpMessageQueue = new CMessageQueue;

	CMessageDispatcher* tpMessageDispatcher = new CMessageDispatcher;
	CMessageFactory* tpMessageFactory = new CMessageFactory;
	
	CGlobalPlayerData* tPlayerData = new CGlobalPlayerData();
	if (tpLogic == NULL 
	|| tpMessageQueue == NULL || tpMessageDispatcher == NULL
	|| tpMessageFactory == NULL)
	{
		LOG_FATAL("default", "program alloc memory for tpLogic error.");
		return -1;
	}
	if (ReadCfg(mConfig) != 0)
	{
		LOG_ERROR("default", "Read ../config/data/login_config/loginserver.xml failure. pls check it and run again.");
		exit(0);
	}
	mGlobalServerID = 1;
	pLoginServer->Initialize(GLOBAL_SERVER_TYPE,mGlobalServerID,inet_addr(mConfig.serverHost),mConfig.serverPort);
	if(pLoginServer->CreateServer()){
		LOG_ERROR("default","Creat global listen login socket failed.");
	}else{
		LOG_DEBUG("default","Global listen for login at<%s:%d>",mConfig.serverHost,mConfig.serverPort);
	}
	pLoginServer->GetSocket()->SetNBlock(pLoginServer->GetSocket()->GetSocketFD());
	return 0;
}

//============================================================
// <T>��½������ģ���С����</T>
//============================================================
unsigned int CGlobalServer::CountSize()
{
	//TODO: ���㽫����LoginServer ���󴴽��ڹ����ڴ��� 
	unsigned int tSize = sizeof( CGlobalServer );

	tSize += CClientHandle::CountSize();
	tSize += CGlobalLogic::CountSize();
	tSize += CGlobalLoginModule::CountSize();
	tSize += CGlobalCertifyPlayerModule::CountSize();
	tSize += CGlobalPlayerModule::CountSize();
	tSize += CMessageQueue::CountSize( );

	return tSize;
}

//============================================================
// <T>��½������ģ���С����</T>
//============================================================
void CGlobalServer::AcceptClients(){
	int listenFD = pLoginServer->GetSocket()->GetSocketFD();
	struct sockaddr_in tPeerAddr;
	socklen_t addrLen = sizeof(tPeerAddr);
	int acceptFD;
	do{
		acceptFD = accept(listenFD,(sockaddr*)&tPeerAddr,&addrLen);
		if(acceptFD < 0){
			if(EAGAIN != errno){
				LOG_ERROR( "default", "global server accept error:%d",errno);
			}
			break;
		//}else if(acceptFD >= GS_LOGIN_MAXCOUNT){
			//LOG_ERROR( "default", "Too much login server.");
			//exit(1);
		}else{
			CGlobalLogin* pLogin = CGlobalLoginModule::GetSingleton().FindByHost(tPeerAddr.sin_addr.s_addr);
			if(NULL == pLogin){
				LOG_ERROR("default","UnAllowed login<%s %d> server connect request.",inet_ntoa(tPeerAddr.sin_addr),tPeerAddr.sin_addr.s_addr);
            close(acceptFD);
				continue;
			}
         LOG_DEBUG("default","Accept %s. (handle=%d)", inet_ntoa(tPeerAddr.sin_addr), acceptFD);
			pLogin->handle = acceptFD;
         pLogin->socket.Accept(acceptFD);
         pLogin->socket.SetNBlock(acceptFD);
			//pLoginSockets[acceptFD]->Accept(acceptFD);
			//pLoginSockets[acceptFD]->SetNBlock(acceptFD);
		}
	}while(acceptFD > 0);
}

//============================================================
// <T>��½������ģ���С����</T>
//============================================================
void CGlobalServer::RecvLoginMsg(){
	


	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 10;

	fd_set tRset;
	FD_ZERO(&tRset);
	int nFds = 0;
	int tInUsedFds[GS_LOGIN_MAXCOUNT];

   CGlobalLogin* pLogins = CGlobalLoginModule::GetSingleton().logins;
   for(int n=0; n<GS_LOGIN_MAXCOUNT; n++){
      int iTempFD = pLogins[n].socket.GetSocketFD();
      int iTempStatus = pLogins[n].socket.GetStatus();
      if(iTempFD > 0 && iTempStatus == tcs_connected){
         FD_SET(iTempFD, &tRset);
         tInUsedFds[nFds++] = iTempFD;
      }
   }
   int nready = select(nFds,&tRset,NULL,NULL, &tv);
   if(-1 == nready){
      LOG_ERROR("default", "select error:%d.",errno);
   }
   for(int n = 0; n < nFds; n++) {
      if(FD_ISSET(tInUsedFds[n], &tRset)){
         int iRet = 0;
         do{
            CGlobalLogin* pLogin = CGlobalLoginModule::GetSingleton().FindByHandle(tInUsedFds[n]);
            int recvdRet = pLogin->socket.RecvData();
			BYTE tCodeBuff[ MAX_CODE_LEN ];
			unsigned short tBuffLen = MAX_CODE_LEN;
            iRet = pLogin->socket.GetOneCode(tBuffLen,tCodeBuff);
			LOG_DEBUG( "default", "get one code iRet = %d", iRet);
            if(iRet > 0 ){
               CMessage tMsg;

					if(0 == UnPakMessage(tCodeBuff,tBuffLen,&tMsg)){
						LOG_ERROR("default","UnPakMessage error.");
					}
               CGlobalLogic::GetSingleton().OnLoginMessage(tInUsedFds[n], &tMsg);
            }else{
               if(iRet  < 0){
                  LOG_ERROR("default", "GetOneCode error:%d.",iRet);
                  return;
               }
            }
         }while(iRet > 0);
      }
   }


	/*for(int i = 0; i < GS_LOGIN_MAXCOUNT; i++){
		int iTempFD = pLoginSockets[i]->GetSocketFD();
		int iTempStatus = pLoginSockets[i]->GetStatus();
		if(iTempFD > 0 && iTempStatus == tcs_connected){
			FD_SET(iTempFD, &tRset);
			tInUsedFds[nFds++] = iTempFD;
		}
	}
	
	int nready = select(nFds,&tRset,NULL,NULL, &tv);
	if(-1 == nready){
		LOG_ERROR("default", "select error:%d.",errno);
	}
	for(int i = 0; i < nFds; i++) {
		if(FD_ISSET(tInUsedFds[i],&tRset)){
			int iRet = 0;
			do{
				pLoginSockets[i]->RecvData();
				iRet = pLoginSockets[i]->GetOneCode(tBuffLen,tCodeBuff);
				if(iRet > 0 ){
					CMessage tMsg;
					tMsg.ParseFromArray(tCodeBuff,tBuffLen);
					CGlobalLogic::GetSingleton().OnLoginMessage(i, &tMsg);
				}
				else{
					if(iRet  < 0){
						LOG_ERROR("default", "GetOneCode error:%d.",iRet);
						return;
					}
				}
			}while(iRet > 0);
      }
	}*/
}
											    
//============================================================
// <T>��½������ģ���С����</T>
//============================================================
void CGlobalServer::RecvClientMsg(int vMsgCount){
	int vRecvCount = 0;
	BYTE tMsgBuff[ MAX_CODE_LEN ];
	short tMsgLen = sizeof( tMsgBuff );

	while( vRecvCount < vMsgCount )
	{
		tMsgLen = sizeof( tMsgBuff );
		int vRecvRet = pClientHandle->Recv();

		vRecvCount ++;

		// �����ѿ�
		if ( vRecvRet == CLIENTHANDLE_QUEUE_EMPTY )
		{
			struct timespec tv;
			tv.tv_sec = 0;
			tv.tv_nsec = mConfig.clientHandleIdleSleep;

			// ������пգ�˯�� 1 ms 
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
	// 100324 MZYNG ADD-END
}


//============================================================
// <T>��½������ģ���С����</T>
//============================================================
void CGlobalServer::Launch(){
   CGlobalPlayerData::GetSingleton().Connect();
}


//============================================================
// <T>��½������ģ���С����</T>
//============================================================
void CGlobalServer::Run(const int nDaemon )
{
	while(1)
	{
		AcceptClients();
		RecvLoginMsg();	
		RecvClientMsg(3000);
		CMessageDispatcher::GetSingletonPtr( )->DispachMsg( ); 
	}

}

//============================================================
// <T>��xml�ļ��ж�ȡ������Ϣ</T>
//
// @return ��ȡ��Ϣ�Ƿ�ɹ�
//============================================================

int CGlobalServer::ReadCfg(CGlobalServerConfiguration& config){
	const char* login_cfgfile = "../config/login.xml";
	TiXmlDocument loginDoc;

	if(!loginDoc.LoadFile(login_cfgfile)){
		//��login.xml�ļ������¼��������Ϣ
		LOG_ERROR( "default", "load xml %s failed", login_cfgfile);
		printf( "load xml %s failed\n", login_cfgfile);
		return -1;
	}


	TiXmlElement* pLoginRootElement = NULL;
	TiXmlElement* pServersElement = NULL;
	TiXmlElement* pLoginServer = NULL;

	pLoginRootElement = loginDoc.RootElement();//�õ��ļ����ڵ�ָ��
	pServersElement = pLoginRootElement->FirstChildElement();//�õ����ڵ�ĵ�һ�����ӽڵ�
	pLoginServer = pServersElement->FirstChildElement();

	while(pLoginServer){
		CGlobalLogin& login = CGlobalLoginModule::GetSingleton().Alloc();

		login.id = atoi(pLoginServer->Attribute("id"));
		strcpy(login.host , pLoginServer->Attribute("host"));
		login.port = atoi(pLoginServer->Attribute("port"));
		login.type = RGlobalLoginType::Parse(atoi(pLoginServer->Attribute("type")));
		login.statusType = RGlobalLoginStatusType::Parse(atoi(pLoginServer->Attribute("status_type")));
		login.status = RGlobalLoginStatus::Parse(atoi(pLoginServer->Attribute("status")));

		pLoginServer = pLoginServer->NextSiblingElement();
	}

	const char* global_cfgfile = "../config/configure.xml";
	TiXmlDocument globalDoc;

	TiXmlElement* pConfigElement = NULL;
	TiXmlElement* pGlobalServerElement = NULL;
	TiXmlElement* pDataServerElement = NULL;

	if(!globalDoc.LoadFile(global_cfgfile)){
		//��config.xml�ļ�����ȫ�ַ�����������Ϣ
		LOG_ERROR( "default", "load xml %s failed", global_cfgfile);
		printf( "load xml %s failed\n", global_cfgfile);
		return -1;
	}

	pConfigElement = globalDoc.RootElement();
	pGlobalServerElement = pConfigElement->FirstChildElement("GlobalServer");
	pDataServerElement = pConfigElement->FirstChildElement("DataServer");

	
	strcpy(config.serverHost ,pGlobalServerElement->Attribute("host"));		
	config.serverPort = atoi(pGlobalServerElement->Attribute("port"));

	strcpy(config.dataHost,pDataServerElement->Attribute("host"));
	config.dataPort = atoi(pDataServerElement->Attribute("port"));
	strcpy(config.dataLoginUser,pDataServerElement->Attribute("passport"));
	strcpy(config.dataLoginPassword,pDataServerElement->Attribute("password"));
	strcpy(config.dataDatabase,pDataServerElement->Attribute("database"));

	return 0;
}



//============================================================
// <T>��½������ģ���С����</T>
//============================================================
// 100325 MZYNG ADD-BEGIN
void CGlobalServer::Send2Player(CCertifyPlayer* tpPlayer, CMessage* pMessage){
	if(tpPlayer == NULL) return;
	pClientHandle->Send(pMessage, tpPlayer);
}


int CGlobalServer::PakMessage(CMessage& tMessage,char *msgBuffer,int bufferSzie){
	
	// ����������ǿת
	Message* pPara = (Message *) (tMessage.msgpara());

	if (pPara == NULL)
	{
		LOG_ERROR( "default", "The Message Para is NULL" );
		return 0;
	}

	// ����������Ϣ���ĳ���
	//int iPkgSize =  tMessage.ByteSize() + 2*2;
	int iPkgSize =  tMessage.ByteSize() + pPara->ByteSize() + 2*3;
	if (iPkgSize > 0xffff || iPkgSize < 0)
	{
		LOG_ERROR("default", " The Message(%d) PackSize(%d) more than 0xFFFF, Pls check it",tMessage.msghead().messageid(), iPkgSize);
		return 0;
	}

	// ���Ե�unBufferSize�ĳ���һ�����������������Ϣ���ĳ���, ������ǳ����������
	if(iPkgSize > bufferSzie){
		LOG_ERROR("default","The Message(%d) PackSize(%d) more than bufffer Len %d, Pls check it",tMessage.msghead().messageid(), iPkgSize,bufferSzie);
	}

	// Ϊ������Ϣ�ĳ��ȸ�ֵ
	char * tpBuffer = msgBuffer;
	*((unsigned short*)tpBuffer) = iPkgSize;
	tpBuffer += 2; 


	// ��¼��Ϣͷ�ĳ���
	*((unsigned short*)tpBuffer) = tMessage.GetCachedSize();
	tpBuffer += 2;

	// ����Ϣͷѹ��������
	bool ret = tMessage.SerializeToArray(tpBuffer, bufferSzie);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] tMessage.SerializeToArray error",
			__LK_FILE__, __LINE__, __FUNCTION__ );
		return 0;
	}

	tpBuffer += tMessage.GetCachedSize();

	 //��¼��Ϣ������ĳ���
	*((unsigned short*)tpBuffer) = pPara->GetCachedSize();
	tpBuffer += 2;

	 //����Ϣ������ѹ��������
	ret = pPara->SerializeToArray(tpBuffer, bufferSzie);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] pPara->SerializeToArray error",
		__LK_FILE__, __LINE__, __FUNCTION__ );

		return 0;
	}

	tpBuffer += pPara->GetCachedSize();

	assert(iPkgSize == (tpBuffer - msgBuffer));
	return iPkgSize;

}

//============================================================
// <T>global��login֮�����Ϣ���</T>
// @param unsigned char* szBuffer �յ�����Ϣ����
// @param unsigned int unBufferLength �������ĳ���
// @param CMessage* tpMessage �������Ϣ
//============================================================
int CGlobalServer::UnPakMessage(unsigned char* szBuffer, unsigned int unBufferLength,CMessage* tpMessage){
	unsigned char * tpBuffer = szBuffer;
	unsigned short iPkgSize = *((unsigned short*)(tpBuffer));

	// У�鴫�����ĳ���, ������Ȳ�������Ҫ���ؼ�����
	if (iPkgSize > (unBufferLength)) return (unBufferLength - iPkgSize);

	// �����������ĳ����ֶ�
	tpBuffer += 2;

	// ����Ϣͷ
	unsigned short unMsgHeadLength = *((unsigned short*)(tpBuffer));

	bool ret = tpMessage->ParseFromArray( tpBuffer+2,  unMsgHeadLength);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] tpMessage->ParseFromArray error", 
			__LK_FILE__, __LINE__, __FUNCTION__ );

		return 0;
	}else
	{
		//iPkgSize -= tpMessage->ByteSize();
		//���� tpBuffer += (2 + unMsgHeadLength);
		tpBuffer += (2 + tpMessage->ByteSize());
	}

	unsigned short unMsgID =  tpMessage->msghead().messageid();
	// �ж�unMsgID����Ч��

	// ����Ϣ��
	Message* tpMsgPara = CMessageFactory::GetSingleton().CreateMessage(unMsgID);

	if (tpMsgPara  == NULL)
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] CMessageFactory::CreateMessage error", 
			__LK_FILE__, __LINE__, __FUNCTION__ );

		return 0;
	}

	unsigned short unMsgParaLength = *((unsigned short*)(tpBuffer));
	ret = tpMsgPara->ParseFromArray( tpBuffer+2, unMsgParaLength);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] tpMsgPara->ParseFromArray error", 
			__LK_FILE__, __LINE__, __FUNCTION__ );
#ifdef _USE_MESSAGE_BUFF_
		tpMsgPara->~Message();
#else
		delete tpMsgPara;
#endif

		return 0;
	}
	else
	{
		// ����Ϣ�帽������Ϣ��, ��Ϣͷ�����ڲ���̬������
		//iPkgSize -= tpMsgPara->ByteSize();
		//
		tpBuffer += (2 + tpMsgPara->ByteSize()); 
		tpMessage->set_msgpara((unsigned int) tpMsgPara);

	}
	// ����iPkgSize Ӧ�� ͬ������ֽ���һ��
	assert(iPkgSize == (tpBuffer - szBuffer));
	// ����ProxyHead 
	return iPkgSize;
}

//============================================================
// <T>������Ϣ��ָ��socket�ĵ�½��������</T>
// @param int handle �����ݵ�Ŀ���¼��������socket
// @param CMessage& Ҫ������Ϣ
//============================================================
bool CGlobalServer::Send2Login(int handle, CMessage& pMessage){

	char message_buffer[MAX_CODE_LEN];
	int msgLen = PakMessage(pMessage,message_buffer,MAX_CODE_LEN);
	if(0 == msgLen){
		LOG_ERROR("default","PakMessage error.");
		return false;
	}
	LOG_DEBUG("default","Create new packet len = %d",msgLen);
	LK_ASSERT( pMessage.msgpara() != 0, NULL );
	CGlobalLogin* tpLogin = CGlobalLoginModule::GetSingleton().FindByHandle(handle);
	if(tpLogin){
		tpLogin->socket.SendOneCode(msgLen,(BYTE*)message_buffer);
	}else{
		LOG_ERROR("default","Can't find login server with handle:%d",handle);
		return false;
	}
	return true;		
}
// 100325 MZYNG ADD-END


//============================================================
// <T>CGlobalLogic��ʵ��</T>
//============================================================
template<> CGlobalLogic* CSingleton< CGlobalLogic >::spSingleton = NULL;
CSharedMem* CGlobalLogic::mShmPtr = NULL; 
//============================================================
// <T>new���������</T>
//============================================================
void* CGlobalLogic::operator new( size_t size ){
	return ( void* ) mShmPtr->CreateSegment( size );
}

//============================================================
// <T>delete���������</T>
//============================================================
void  CGlobalLogic::operator delete( void* pointer ){
}

//============================================================
// <T>ȫ�ַ������߼�ģ���С����</T>
//============================================================
unsigned int CGlobalLogic::CountSize(){
	return sizeof(CGlobalLogic);
}

//============================================================
// <T>ȫ�ַ������߼�ģ���ʼ��</T>
//============================================================
void CGlobalLogic::Initialize(){
	
}

//============================================================
// <T></T>
//============================================================
void CGlobalLogic::Resume(){
}

//============================================================
// <T>�����û���¼У������</T>
// 
// @param playerId ���id
// @param pMessage ��Ϣ��

//============================================================
// 100326 MZYNG ADD-BEGIN
void CGlobalLogic::OnClientCertifyRequest(uint32 socketIndex, CMessage* pMessage){
	LK_ASSERT(pMessage != NULL && pMessage->msgpara() != 0, return);
	CMessageCertifyRequest* tpCerifyRequest = (CMessageCertifyRequest*) pMessage->msgpara();

	LOG_DEBUG("default","[%s:%d][%s]Recv client(%d) CMessageCertifyRequest<passport:%s, password:%s>",
		__LK_FILE__,
		__LINE__,
		__FUNCTION__,
		socketIndex,
		tpCerifyRequest->passport().c_str(),
		tpCerifyRequest->password().c_str()
		);

	CMessageCertifyQueryRequest tG2LCertifyClient;
	
	CCertifyPlayer* tpPlayer = CGlobalCertifyPlayerModule::GetSingleton().FindPlayerByComm(socketIndex);
	// ���player����֪�ֶ�
	strcpy(tpPlayer->_passport,tpCerifyRequest->passport().c_str());
	strcpy(tpPlayer->_password,tpCerifyRequest->password().c_str());
	// ���ݿ��в������ڵ�login������(��д�˽�ɫ��Ϣ��accountId)
	//LOG_DEBUG("default","player passport:%s password:%s",);
	bool inDb = CGlobalCertifyPlayerModule::GetSingleton().FetchPlayerInfos(tpPlayer);
	tpPlayer->_inDb = inDb;
	// ��д����login server����֤������Ϣ
	// ����ʱ�����ֵ��ȡplayer����
	tG2LCertifyClient.set_playerid(socketIndex);
	tG2LCertifyClient.set_accountid(0);  // û����
	tG2LCertifyClient.set_passport(tpCerifyRequest->passport().c_str());
	tG2LCertifyClient.set_password(tpCerifyRequest->password().c_str());
	tG2LCertifyClient.set_md5code(tpCerifyRequest->md5code().c_str());
	tG2LCertifyClient.set_playerhost(tpPlayer->_clientIp);
	tG2LCertifyClient.set_playerport(tpPlayer->_clientPort);
	tG2LCertifyClient.set_playermac(tpCerifyRequest->mac().c_str());
	tG2LCertifyClient.set_sourceid(tpCerifyRequest->sourceid());
	tG2LCertifyClient.set_version(tpCerifyRequest->version());
	tG2LCertifyClient.set_taskversion(tpCerifyRequest->taskversion());
	tG2LCertifyClient.set_templateversion(tpCerifyRequest->templateversion());
	tG2LCertifyClient.set_matrixtype(tpCerifyRequest->matrixtype());
	tG2LCertifyClient.set_matrixcode(tpCerifyRequest->matrixcode().c_str());
	tG2LCertifyClient.set_matrixcoord(tpCerifyRequest->matrixcoord().c_str());
	
	// ��һ�����ʵ�login������֤��Ϣ
	CGlobalLogin* pLogin = CGlobalCertifyPlayerModule::GetSingleton().FindSuitableLoginServer(tpPlayer);
	if(NULL == pLogin){
		LOG_ERROR("default","FindSuitableLoginServer() error.");
		exit(1);
	}else{
		LOG_DEBUG("default","find login server:%d",pLogin->handle);
	}
	// ������Ϣ
	
	LOG_DEBUG("default","[%s:%d][%s] Send to login(%d) CMessageCertifyQueryRequest<playerid:%d, accountid:%d, passport:%s, password:%s>",
		__LK_FILE__,
		__LINE__,
		__FUNCTION__,
		pLogin->handle,
		tG2LCertifyClient.playerid(),
		tG2LCertifyClient.accountid(),
		tG2LCertifyClient.passport().c_str(), 
		tG2LCertifyClient.passport().c_str()
		);

	CMessage tMessage;
	tMessage.set_msgpara((uint32_t)&tG2LCertifyClient);
	pbmsg_sethead(&tMessage, ID_A2L_REQUEST_CERTIFYQUERY, 0, 0, 0, 0, 0, 0);
	if(!CGlobalServer::GetSingleton().Send2Login(pLogin->handle,tMessage)){
		LOG_ERROR("default","[%s:%d][%s] Send2Login CMessageCertifyQueryRequest error.",__LK_FILE__, __LINE__, __FUNCTION__);
	}

}

//============================================================
// <T>����ͻ���������Ϣ</T>
//
// @param playerId ���id
// @param pMessage ��Ϣ��
//============================================================
void CGlobalLogic::OnClientMessage(uint32 socketIndex, CMessage* pMessage){

	LK_ASSERT(pMessage != NULL && pMessage->msgpara() != 0, return);
	CMessageHead* tpHead = pMessage->mutable_msghead();
	//LOG_DEBUG("default","recv msg dest id is:%ddest fe:%d,",tpHead->dstid(),tpHead->dstfe(),tpHead->srcid());
	switch(tpHead->messageid()){
	   case ID_C2A_REQUEST_CERTIFY:
		   OnClientCertifyRequest(socketIndex,pMessage);
		   break;
		default:
			LOG_ERROR("default","[%s:%d][%s] Recv unknown msg with id:%d from client:%d",
				__LK_FILE__,
				__LINE__,
				__FUNCTION__,
				tpHead->messageid(),socketIndex);
			break;
   }
}

//============================================================
// <T>�����½������������Ϣ</T>
// 
// @param handle ����Ϣ��������
// @param pMessage ��½������������Ϣ��
//============================================================
void CGlobalLogic::OnLoginMessage(uint32 handle, CMessage* pMessage){
   LK_ASSERT( pMessage != NULL && pMessage->msgpara() != 0, return );
   CMessageHead* tpHead = pMessage->mutable_msghead();
	LOG_DEBUG("default","[GS] Recv Login Message with id:%d",tpHead->messageid());
   switch(tpHead->messageid()){
      case ID_L2A_RESPONSE_CERTIFYQUERY: // ��¼��������ȫ�ַ�������֤Ӧ�� ID_L2A_RESPONSE_CERTIFYQUERY
         OnLoginCertifyQueryResponse(handle,(CMessageCertifyQueryResponse*)pMessage->msgpara());
         break;
      case ID_L2A_REQUEST_CERTIFYTOKEN:  // ��¼��������ȫ�ַ�������֤��������
         OnLoginCertifyTockenRequest(handle,(CMessageCertifyTokenRequest*)pMessage->msgpara());
         break;
      case ID_L2A_NOTIFY_ROLEQUERY:     // ��¼��������ȫ�ַ�����֪ͨ��ɫ��Ϣ
         OnLoginRoleQueryNotify(handle,(CMessageRoleQueryNotify*)pMessage->msgpara());
         break;
      case ID_L2A_NOTIFY_ONLINESTATUS:  // ��������Ϣ֪ͨ
         OnLoginOnlineStatusNotify(handle,(CMessageOnlineStatusNotify*)pMessage->msgpara());
         break;
		default:
			LOG_ERROR("default","[GS] Global server can't process msg with id:%d from login:%d",tpHead->messageid(),handle);
			break;
   }
}


//============================================================
// <T>�����¼�����������û���֤Ӧ��</T>
//
// @param handle ����Ϣ�ĵ�¼��������socket
// @param pCerifyLoginResponse ��½��������֤�û��Ľ��
// <P> In msg
//message CMessageCertifyQueryResponse
//{
//	enum EStatus
//	{
//		STATUS_SUCCESS = 0; // ��֤�ɹ�
//		STATUS_FAILURE = 1; // ִ��ʧ��
//	};
//	optional EStatus status    = 1; // ״̬
//	optional uint32  playerId  = 2; // ��ұ��
//	optional uint32  accountId = 3; // �˺ű��
//	optional uint32  errorCode = 4; // �������
//};
// </P>
// <P> Out msg
//============================================================
// �û���ȫ�ַ�������֤Ӧ��
//message CMessageCertifyResponse
//{
//optional EStatus                 status    = 1; // ״̬
//optional uint32                  playerId  = 2; // ��ұ��
//optional uint32                  accountId = 3; // �˺ű��
//optional string                  token     = 4; // ����
//repeated CMessageLoginServerInfo servers   = 5; // ��������Ϣ
//optional uint32                  errorCode = 6; // �������
//};
// <P>
//============================================================

void CGlobalLogic::OnLoginCertifyQueryResponse(uint32 handle, CMessageCertifyQueryResponse* pCerifyLoginResponse){

	uint32 playerId = pCerifyLoginResponse->playerid();
	uint32 accountId = pCerifyLoginResponse->accountid();
	LK_ASSERT(pCerifyLoginResponse != NULL,NULL);
	LOG_DEBUG("default","[%s:%d][%s] Recv from login(%d) CMessageCertifyQueryResponse<status:%d playerId:%d accountId:%d errorCode:%d>",
		__LK_FILE__,
		__LINE__,
		__FUNCTION__,
		handle,
		pCerifyLoginResponse->status(),
		playerId,
		accountId,
		pCerifyLoginResponse->errorcode());

	CCertifyPlayer* tpCertifyPlayer = CGlobalCertifyPlayerModule::GetSingleton().FindPlayerByComm(playerId);
	if(tpCertifyPlayer){

	}
	
	tpCertifyPlayer->_accountId = accountId;
	// ����
	if(!tpCertifyPlayer->_inDb){
		CGlobalPlayerData::GetSingleton().Insert2(tpCertifyPlayer);
	}
	// copy to global
	CGlobalPlayer* tpGlobalPlayer = CGlobalPlayerModule::GetSingleton().Alloc(accountId);
	uint32 tToken = RTokenGenarator::GenToken();
	tpGlobalPlayer->accountId = tpCertifyPlayer->_accountId;
	strcpy(tpGlobalPlayer->passport,tpCertifyPlayer->_passport);
	strcpy(tpGlobalPlayer->password,tpCertifyPlayer->_password);
	tpGlobalPlayer->token = tToken;
	// TODO:token��tokenTimeout
	int nGates = tpGlobalPlayer->gateCount = tpCertifyPlayer->_gateCount;
	memcpy((char*)tpGlobalPlayer->gates,(char*)tpCertifyPlayer->_gates,nGates * sizeof(SGlobalPlayerGateInfo));

	CMessageCertifyResponse tCertifyResponseMsg;
	tCertifyResponseMsg.set_playerid(playerId);
	tCertifyResponseMsg.set_accountid(accountId);
	tCertifyResponseMsg.set_token(tToken);
	char debugMsg[1024];
	if(CMessageCertifyQueryResponse_EStatus_STATUS_SUCCESS == pCerifyLoginResponse->status()){
		tCertifyResponseMsg.set_status(CMessageCertifyResponse_EStatus_STATUS_SUCCESS);

		// ���Server list
		int nlogins = CGlobalLoginModule::GetSingleton().loginCount;
		CGlobalLogin* pResponseLogin = CGlobalLoginModule::GetSingleton().FindByHandle(handle);
		int responseLoginId =  pResponseLogin->id;
		
		char* debugMsgPtr  = debugMsg;
		for(int i = 0; i < nlogins; i++){
			CGlobalLogin& tLogin = CGlobalLoginModule::GetSingleton().Get(i);
			if(tLogin.used){
				CMessageLoginServerInfo* pInfo = tCertifyResponseMsg.add_servers();
				pInfo->set_id(tLogin.id);
				pInfo->set_status(tLogin.GetStatus());
				pInfo->set_flag(EServerGatewayFlag_Normal);
				if(responseLoginId == tLogin.id){
					pInfo->set_count(tpGlobalPlayer->GetRoleCountByServerId(pResponseLogin->id));
				}else{
						pInfo->set_count(0);
				}

				sprintf(debugMsgPtr,"(Id:%d,Status:%d,Roles:%d)",pInfo->id(),pInfo->status(),pInfo->count());
				int len = strlen(debugMsgPtr);
				debugMsgPtr += len;
			}
		}	
	}else{
		tCertifyResponseMsg.set_status(CMessageCertifyResponse_EStatus_STATUS_FAILURE);
		tCertifyResponseMsg.set_errorcode(pCerifyLoginResponse->errorcode());
	}
	// TODO: ��ʱ CMessageCertifyResponse_EStatus_STATUS_INVALID

	

	CMessage tMessage;
	pbmsg_sethead(&tMessage,ID_A2C_RESPONSE_CERTIFY, 0, 0, 0, 0, 0, 0);
	tMessage.set_msgpara((uint32_t)&tCertifyResponseMsg);

	LOG_DEBUG("default","[%s:%d][%s] Send to Player(%d) CMessageCertifyResponse<status:%d playerId:%d accountId:%d token:%d servers:%s\n errorcode:%d> Len:%d",
		__LK_FILE__,
		__LINE__,
		__FUNCTION__,
		tpCertifyPlayer->_handle,
		tCertifyResponseMsg.status(),
		tCertifyResponseMsg.playerid(),
		tCertifyResponseMsg.accountid(),
		tCertifyResponseMsg.token(),
		debugMsg,
		tCertifyResponseMsg.errorcode(),
		tMessage.ByteSize());

	CGlobalServer::GetSingleton().Send2Player(tpCertifyPlayer,&tMessage);
}

//============================================================
// <T>�����¼��������ȫ�ַ�������֤��������</T>
//
// @param handle ����Ϣ��������
// @param pCerifyTokenRequest ��½������������֤����Ϣ��
// <P>In msg ��¼��������ȫ�ַ�������֤��������
//message CMessageCertifyTokenRequest
//{
//	optional uint32 playerId  = 1; // ��ұ��
//	optional uint32 accountId = 2; // �˺ű��
//	optional string token     = 3; // ��¼�˺�
//};
//</P>
//<P>Out Msg ��¼��������ȫ�ַ�������֤����Ӧ��
//message CMessageCertifyTokenResponse
//{	
//	optional EStatus status    = 1; // ״̬
//	optional uint32  playerId  = 2; // ��ұ��
//	optional uint32  accountId = 3; // �˺ű��
//};
//</P>
//============================================================
void CGlobalLogic::OnLoginCertifyTockenRequest(uint32 handle, CMessageCertifyTokenRequest* pCerifyTokenRequest){
	
	int payerId = pCerifyTokenRequest->playerid();
	int  accountId = pCerifyTokenRequest->accountid();
	
	LOG_DEBUG("default","[%s:%d][%s] Recv from login(%d) CMessageCertifyTokenRequest<playerId:%d accountId:%d token:%d>",
		__LK_FILE__,
		__LINE__,
		__FUNCTION__,
		handle,
		payerId,
		accountId,
	   pCerifyTokenRequest->token()
		);

	CGlobalPlayer *tpPlayer = CGlobalPlayerModule::GetSingleton().GetByAccount(accountId);

	LK_ASSERT(tpPlayer != NULL, NULL);



	CMessageCertifyTokenResponse tCertifyTokenResponse;
	tCertifyTokenResponse.set_playerid(payerId);
	tCertifyTokenResponse.set_accountid(accountId);

	if(NULL == tpPlayer){
		tCertifyTokenResponse.set_status(CMessageCertifyTokenResponse_EStatus_STATUS_FAILURE);
		LOG_ERROR("default","[%s:%d][%s] Login send token certify request with accountid = %d,And this account hadn't connected to global yet.");
	}else{

		// TODO У��ʱ��
		if(tpPlayer->token == pCerifyTokenRequest->token()){
			tCertifyTokenResponse.set_status(CMessageCertifyTokenResponse_EStatus_STATUS_SUCCESS);
		}
		else{
			tCertifyTokenResponse.set_status(CMessageCertifyTokenResponse_EStatus_STATUS_FAILURE);
		}
		// ȫ�ַ�������½����ᣬ�ͷŷ�������
		//CGlobalPlayerModule::GetSingleton().Release(payerId);
		tpPlayer->lastActived = time(NULL);
	}
	CMessage tMessage;
	tMessage.set_msgpara((uint32_t)&tCertifyTokenResponse);
	pbmsg_sethead(&tMessage, ID_A2L_RESPONSE_CERTIFYTOKEN, 0, 0, 0, 0, 0, 0);

	LOG_DEBUG("default","[%s:%d][%s] Send to login(%d) CMessageCertifyTokenResponse<status:%d playerId%d accountId%d>",
		__LK_FILE__,
		__LINE__,
		__FUNCTION__,
		handle,
		tCertifyTokenResponse.status(),
		tCertifyTokenResponse.playerid(),
		tCertifyTokenResponse.accountid()
		);
	CGlobalServer::GetSingleton().Send2Login(handle,tMessage);
}

//============================================================
// <T>��¼��������ȫ�ַ�����֪ͨ��ɫ��Ϣ</T>
//
// @param handle ����Ϣ���׽��־��
// @param pRoleNotify ��ɫ��Ϣ֪ͨ
//============================================================
// ��¼��������ȫ�ַ�����֪ͨ��ɫ��Ϣ֪ͨ
//----------------------In Msg------------------------------
//message CMessageRoleQueryNotify
//{
//	optional EStatus status    = 1; // ״̬
//	optional uint32  playerId  = 2; // ��ұ��
//	optional uint32  accountId = 3; // �˺ű��
//	optional uint32  loginId   = 4; // �˺ű��
//	optional uint32  roleCount = 5; // ��ɫ����
//};
//============================================================
void CGlobalLogic::OnLoginRoleQueryNotify(uint32 handle, CMessageRoleQueryNotify* pRoleNotify){
	
	LOG_DEBUG("default","[%s:%d][%s] Recv from login(%d) CMessageRoleQueryNotify<status:%d, playerId:%d, accountId:%d, loginId:%d, roleCount:%d>",
		__LK_FILE__,
		__LINE__,
		__FUNCTION__,
		handle,
		pRoleNotify->status(),
	   pRoleNotify->playerid(),
		pRoleNotify->accountid(),
		pRoleNotify->loginid(),
		pRoleNotify->rolecount()
		);
	switch(pRoleNotify->status()){
		case CMessageRoleQueryNotify_EStatus_STATUS_SUCCESS:{
			int accountId = pRoleNotify->accountid();
			int playerId = pRoleNotify->playerid();
			int nRoles = pRoleNotify->rolecount();
		
			CGlobalLogin* pResponseLogin = CGlobalLoginModule::GetSingleton().FindByHandle(handle);
			int serverId = pResponseLogin->id;
			CGlobalPlayer* tpPlayer = CGlobalPlayerModule::GetSingleton().GetByAccount(accountId);
			LOG_DEBUG("default","Recv role notify from %d for player: %d. nRoles:%d",serverId,accountId,nRoles);
			if(tpPlayer->SetRoleCountByServerId(serverId, nRoles)){
				// �������ݿ�
				CGlobalPlayerData::GetSingleton().Update(tpPlayer);
			}
			break;
		   }
		case CMessageRoleQueryNotify_EStatus_STATUS_FAILURE:{
			LOG_ERROR("default", "Role query failed.");
			break;
		   }
	}
}

//============================================================
// <T>��������Ϣ֪ͨ</T>
// 
// @param handle ����Ϣ�������׽��־��
// @paran pLoginStatusNotify ��½��������״̬��Ϣ
//-----------------------------In msg-------------------------
//message CMessageOnlineStatusNotify
//{
//	optional uint32 serverId = 1; // ���������
//	optional uint32 total    = 2; // ������
//	optional uint32 current  = 3; // ��ǰ����
//};
//============================================================


void CGlobalLogic::OnLoginOnlineStatusNotify(uint32 handle, CMessageOnlineStatusNotify* pLoginStatusNotify){

	LOG_DEBUG("default","[%s:%d][%s] Recv from login(%d) CMessageOnlineStatusNotify<serverId:%d, total:%d, current:%d>",
		__LK_FILE__,
		__LINE__,
		__FUNCTION__,
		handle,
		pLoginStatusNotify->serverid(),
		pLoginStatusNotify->total(),
		pLoginStatusNotify->current()
		);

	//uint32 loginId = pLoginStatusNotify->serverid();
	CGlobalLogin* pLogin = CGlobalLoginModule::GetSingleton().FindByHandle(handle);
	pLogin->playerCurrent  = pLoginStatusNotify->current();
	pLogin->playerTotal = pLoginStatusNotify->total();
}
