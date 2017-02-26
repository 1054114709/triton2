#ifndef _LOGIN_LOGIC_H_
#define _LOGIN_LOGIC_H_

#include "tcp_conn.h"
#include "entity.h"
#include "globaldata.h"
#include "clienthandle.h"
#include "message_pb.hxx.pb.h"
#include "coremessage_pb.hxx.pb.h"
#include "message_queue.h"
#include "message_dispatcher.h"

//============================================================
#define GS_DATABSE_MAXLENGTH 40

//============================================================
enum EGlobalServerSocketType{
   EGlobalServerSocketType_Client,
   EGlobalServerSocketType_Login
};

//============================================================
struct SSocketInfo{
   EGlobalServerSocketType type;
   int index;
};

//============================================================
// <T>��¼��������Ϣ</T>
//============================================================
class CGlobalLoginModule : public CSingleton<CGlobalLoginModule>{
public:
	static CSharedMem*  mShmPtr;
public:
   int loginCount;
   CGlobalLogin logins[GS_LOGIN_MAXCOUNT];
public:
   static unsigned int CountSize();
   void* operator new(size_t size);
   void  operator delete(void* pointer);
   void* operator new(size_t size, const char* file, int line);
   void operator delete(void* pointer, const char* file, int line);
public:
   CGlobalLoginModule();
	void Initialize();
	void Resume();
public:
	CGlobalLogin& Alloc(); 
	CGlobalLogin& Get(int index);
	CGlobalLogin* FindById(uint16 logseverId);
	CGlobalLogin* FindByHost(uint32 ipAddr);
	CGlobalLogin* FindByHandle(uint16 handle);


};

//============================================================
// <T>Token���ɡ�</T>
//============================================================
#define TOKEN_UPPER_BOUND 100000
class RTokenGenarator{
public:
	static uint32 GenToken(){
		if(_base > TOKEN_UPPER_BOUND){
			_base = 0;
		}
		return ++_base;
	}
private:
	static uint32 _base;
};

//============================================================
// <T>��¼�û���Ϣ</T>
//============================================================
class CGlobalPlayerModule : public CSingleton<CGlobalPlayerModule>{
public:
	static CSharedMem*  mShmPtr;
public:
   CGlobalPlayer players[GS_PLAYER_MAXCOUNT];
	typedef lk::hash_map<int,int,GS_PLAYER_MAXCOUNT> GlobalPlayMap;
	typedef lk::hash_map<int,int,GS_PLAYER_MAXCOUNT>::iterator GlobalPlayerIterator;
	typedef lk::hash_map<int,int,GS_PLAYER_MAXCOUNT>::value_type GlobalPlayerValuePair;
	typedef std::pair<GlobalPlayerIterator, bool> _Pairib;
	GlobalPlayMap _playerMap;
public:
	CGlobalPlayerModule();
	void Initialize();
	void Resume();
public:
   static unsigned int CountSize();
   void* operator new(size_t size);
   void  operator delete(void* pointer);
   void* operator new(size_t size, const char* file, int line);
   void operator delete(void* pointer, const char* file, int line);
public:
	CGlobalPlayer* Alloc(int accountId){
		CGlobalPlayer* tpPlayer = GetByAccount(accountId);
		if(tpPlayer){
			return tpPlayer;
		}
		for(int i = 0; i < GS_PLAYER_MAXCOUNT; i++){
			if(!players[i].used){
				players[i].used = true;
				GlobalPlayerValuePair valuePair(accountId,i);
				if(_playerMap.insert(valuePair).second){
					LOG_DEBUG("default","Insert into global player map<%d,%d>.",accountId,i);
					return &players[i];
				}else{
					LOG_ERROR("default","Insert into global player map<%d,%d> error.",accountId,i);
					return NULL;
				}
			}
		}
		LOG_ERROR("default","Global player map is full.");
		return NULL;
	}
	bool Release(int accountId){
		GlobalPlayerIterator item = _playerMap.find(accountId);
		if(item == _playerMap.end()){
			LOG_ERROR("default","CGlobalPlayerModule Release unAlloc player with account:%d.",accountId);
			return false;
		}
		int index =(*item).second;
		players[index].Initialize();
		_playerMap.erase(item);
		LOG_DEBUG("default","Release global player<%d,%d> from map.",accountId,index);
		return true;
	}

	CGlobalPlayer* GetByAccount(int accountId){
		GlobalPlayerIterator item = _playerMap.find(accountId);
		if(item == _playerMap.end()){
			return NULL;
		}
		int index = (*item).second;
		return &players[index];
	}
	CGlobalPlayer* GetByIndex(int index){
		if(index < 0 || index >= GS_PLAYER_MAXCOUNT){
			return NULL;
		}
		if(players[index].used){
			return &players[index]; 
		}
		LOG_NOTICE("default","access an unused player.");
		return NULL;
	}
   bool FetchPlayerInfos(CGlobalPlayer& pPlayer);
};

// ͬʱ��֤��������
#define MAX_CERTIFY_CLIENT 65535
class CGlobalCertifyPlayerModule: public CSingleton<CGlobalCertifyPlayerModule>{
public:
	static CSharedMem*  mShmPtr;
	CCertifyPlayer _players[MAX_CERTIFY_CLIENT];
public:
	static unsigned int CountSize(){
		return sizeof(CGlobalCertifyPlayerModule);
	}
	void* operator new(size_t size){
		return (void*)mShmPtr->CreateSegment(size);
	}
	void  operator delete(void* pointer){

	}
	void* operator new(size_t size, const char* file, int line){
		return (void*)mShmPtr->CreateSegment(size);
	}
	void operator delete(void* pointer, const char* file, int line){

	}
public:
	void Initialize(){
		memset((char*)_players,0,sizeof(CCertifyPlayer)*MAX_CERTIFY_CLIENT);
	}
	void Resume(){

	}
	CCertifyPlayer* GetPlayerByComm(int socketIndex){
		LK_ASSERT((socketIndex > 0 && socketIndex < MAX_CERTIFY_CLIENT),NULL);
		memset((char*)&_players[socketIndex],0,sizeof(CCertifyPlayer));
		_players[socketIndex]._handle  = socketIndex;
		LOG_DEBUG("default","certify player come from socket:%d.",socketIndex);
		return &_players[socketIndex];
	}
	CCertifyPlayer* FindPlayerByComm(int socketIndex){
		LK_ASSERT((socketIndex > 0 && socketIndex < MAX_CERTIFY_CLIENT),NULL);
		return &_players[socketIndex];
	}

	bool FetchPlayerInfos(CCertifyPlayer* certifyPlayer){
		if(!CGlobalPlayerData::GetSingleton().FetchByPassport2(certifyPlayer,certifyPlayer->_passport)){
			return false;
		}
		return true;
	}
	CGlobalLogin* FindSuitableLoginServer(CCertifyPlayer* tpPlayer){
		int loginId;
		int nGate = tpPlayer->_gateCount;
		if(nGate > 0){  // �н�ɫ
			SGlobalPlayerGateInfo* gates = tpPlayer->_gates;
			loginId = gates[0].loginId;
			int minRoleCount = gates[0].roleCount;
			for(int i = 1; i < nGate;i++){
				int nRoles  = gates[i].roleCount;
				int tempLoginId = gates[i].loginId;
				if(nRoles < minRoleCount){
					loginId = tempLoginId;
					minRoleCount = nRoles;
				}else if(nRoles == minRoleCount){ // ��һ���������ٵ�
					int PrevPlayerOnline = CGlobalLoginModule::GetSingleton().FindById(loginId)->playerCurrent;
					int CurPlayerOnline = CGlobalLoginModule::GetSingleton().FindById(tempLoginId)->playerCurrent;
					if(PrevPlayerOnline > CurPlayerOnline){
						loginId = tempLoginId;
					}
				}
			}
		}else{// �޽�ɫ ȡ��֤�����ٵ�Login
			int nLogin = CGlobalLoginModule::GetSingleton().loginCount;
			LK_ASSERT((nLogin > 0), NULL);
			loginId = CGlobalLoginModule::GetSingleton().Get(0).id;
			int minPlayers = CGlobalLoginModule::GetSingleton().Get(0).playerCurrent;
			for(int i = 1; i < nLogin; i++){
				int curCount = CGlobalLoginModule::GetSingleton().Get(i).loginCount ;
				if(curCount < minPlayers){
					loginId = CGlobalLoginModule::GetSingleton().Get(i).id;
					minPlayers = curCount;
				}
			}
		}
		return CGlobalLoginModule::GetSingleton().FindById(loginId);
	}
};

//============================================================
// <T>�������߼�</T>
//============================================================
class CGlobalLogic : public CSingleton< CGlobalLogic >{
public:
   // �����ʼ����ַ
   static CSharedMem*  mShmPtr;
   // ����ռ���ڴ��С
   static unsigned int CountSize();
public:
   // ���캯��
   CGlobalLogic(){};
   // ��������
   ~CGlobalLogic(){};
   // ������new �� delete 
   void* operator new( size_t size );
   void  operator delete( void* pointer );
public:
   // ��ʼ��
   void Initialize();
   // �ָ�����
   void Resume();
   // ��½������ʱ��
   void OnTimer( unsigned int vTickCount );
   // ��Ӧ���¶���loginserver.xml
   void OnReloadConfig();
   // ��Ӧ�˳���Ϣ
   void OnExit();
public:
   // ��Ӧ�ͻ���ȫ�ַ�������У�����Ϣ
   void OnClientCertifyRequest(uint32 playerId, CMessage* pMessage);
   // ��Ӧ�ͻ�����Ϣ
   void OnClientMessage(uint32 playerId, CMessage* pMessage);
public:
   // ��¼��������ȫ�ַ�������֤Ӧ��
   void OnLoginCertifyQueryResponse(uint32 handle, CMessage* pMessage);
   // ��¼��������ȫ�ַ�������֤��������
   void OnLoginCertifyTockenRequest(uint32 handle, CMessage* pMessage);
   // ��¼��������ȫ�ַ�����֪ͨ��ɫ��Ϣ
   void OnLoginRoleQueryNotify(uint32 handle, CMessage* pMessage);
   // ��������Ϣ֪ͨ
   void OnLoginOnlineStatusNotify(uint32 handle, CMessage* pMessage);
   // ��ӦServer����Ϣ
   void OnLoginMessage(uint32 handle, CMessage* pMessage);

	// <T>��¼��������ȫ�ַ�������֤Ӧ��</T>
	void OnLoginCertifyQueryResponse(uint32 handle, CMessageCertifyQueryResponse* pCerifyLoginResponse);

	// <T>��¼��������ȫ�ַ�������֤��������</T>
	void OnLoginCertifyTockenRequest(uint32 handle, CMessageCertifyTokenRequest* pCerifyTokenRequest);

	// <T>��¼��������ȫ�ַ�����֪ͨ��ɫ��Ϣ</T>
	void OnLoginRoleQueryNotify(uint32 handle, CMessageRoleQueryNotify* pMessage);

	// <T>��������Ϣ֪ͨ</T>
	void OnLoginOnlineStatusNotify(uint32 handle, CMessageOnlineStatusNotify* pLoginStatusNotify);
};

//============================================================
// <T>����������</T>
//============================================================
class CGlobalServerConfiguration
{
public:
   char  serverHost[GS_HOST_MAXLENGTH];            // ȫ�ַ�������Ϣ
   int16 serverPort;                               // ȫ�ַ������˿�
   char  dataHost[GS_HOST_MAXLENGTH];              // ���ݿ�����
   int16 dataPort;                                 // ���ݿ�˿�
   char  dataLoginUser[GS_PASSPORT_MAXLENGTH];     // ���ݿ��¼�û���
   char  dataLoginPassword[GS_PASSWORD_MAXLENGTH]; // ���ݿ�����
   char  dataDatabase[GS_DATABSE_MAXLENGTH];       // ���ݿ�����
   long  clientHandleIdleSleep;                   // û�����ݵ�˯��ʱ��
public:
	CGlobalServerConfiguration();
};

//============================================================
// <T>������</T>
//============================================================
class CGlobalServer : public CSingleton<CGlobalServer>{
public:
   static CSharedMem* mShmPtr;
   static unsigned int CountSize(); 

   //SSocketInfo socketInfo[65536];
   CGlobalServerConfiguration mConfig;
   CClientHandle* pClientHandle;
   CTCPConn<RECVBUFLENGTH, POSTBUFLENGTH>* 	pLoginServer;
   //CTCPSocket<RECVBUFLENGTH, POSTBUFLENGTH>* pLoginSockets[GS_LOGIN_MAXCOUNT];
   //phtread_t mListenLoginThreadId;
   
   int mGlobalServerID;  // ȫ�ַ�������server id
public:
   CGlobalServer(){}
   ~CGlobalServer(){}
public:
	CGlobalServerConfiguration& Configuration();
public:
	// ��ʼ��
	int Initialize( int vInitFlag );
	// ����������
	void Launch();
	// ���з����� 
	void Run(const int nDaemon );
	// �������ļ�loginserver.xml ��ȡ���õ�vConfig
	int ReadCfg(CGlobalServerConfiguration& config);
public:
	// ��������
	void AcceptClients();
   // �ӹ����ڴ��ȡ�ͻ��˹�������Ϣ
   void RecvClientMsg(int vMsgCount);
   // ��ȡ�ӷ�������������Ϣ
   void RecvLoginMsg();
	// ���� login�� ip �� port ���� socket
	// ����ҷ�����Ϣ�ӿ�
	void Send2Player(CCertifyPlayer* pPlayer, CMessage* pMessage);
	// ���¼������������Ϣ�ӿ�
	bool Send2Login(int handle, CMessage& pMessage);
	// �����
	int PakMessage(CMessage& tMessage,char *msgBuffer,int bufferSzie);
	int UnPakMessage(unsigned char* szBuffer, unsigned int unBufferLength,CMessage* tpMessage);
};
#endif
