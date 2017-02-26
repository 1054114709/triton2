#ifndef _GLOBAL_ENTITY_H_
#define _GLOBAL_ENTITY_H_

#include "object.h"
#include "coretype.h"
#include "log.h"
#include "servertool.h"
#include "dbinterface.h"
#include "lk_string.h"
#include "coretype.h"

#define GS_HOST_MAXLENGTH     40
#define GS_PASSPORT_MAXLENGTH 40
#define GS_PASSWORD_MAXLENGTH 40
#define GS_TOKEN_MAXLENGTH    40
#define GS_LOGIN_MAXCOUNT     32
#define GS_PLAYER_MAXCOUNT    1024*64
#define GS_SOCKET_RECEIVE     1024*1024*4
#define GS_SOCKET_SEND        1024*1024*4
#define PLAYERS_AS_IDDLE    4000    // ����
#define PLAYERS_AS_BUSY     7000    // æµ
#define PLAYERS_AS_RUSH     10000   // ��æ
//#define PLAYERS_AS_FULL             //  ��

//============================================================
// <T>������״̬����</T>
//============================================================
enum EGlobalLoginType{
   EGlobalLoginType_Unused, // δʹ��(U)
   EGlobalLoginType_Normal, // ��ʽ(N)
   EGlobalLoginType_New,    // �·�(W)
};
//============================================================
class RGlobalLoginType{
public:
   static EGlobalLoginType Parse(int value);
   static const char* ToString(EGlobalLoginType value);
};

//============================================================
// <T>������״̬����</T>
//============================================================
enum EGlobalLoginStatusType{
   EGlobalLoginStatusType_System, // ϵͳ(S)
   EGlobalLoginStatusType_Custom, // ����(C)
};
//============================================================
class RGlobalLoginStatusType{
public:
   static EGlobalLoginStatusType Parse(int value);
   static const char* ToString(EGlobalLoginStatusType value);
};

//============================================================
class RGlobalLoginStatus{
public:
   static EServerGatewayStatus Parse(int value);
   static const char* ToString(EServerGatewayStatus value);
};

//============================================================
// <T>������Ϣ��</T>
//============================================================
class CGlobalLogin: public CObj{
public:
   bool                   used;                    // ʹ�ñ�ʶ
   int                    handle;                  // ������ (socket fd)
   int                    id;                      // ���      (���Ƕ����Server Id)
   char                   host[GS_HOST_MAXLENGTH]; // ��������
   int                    port;                    // �˿�
   EGlobalLoginType       type;                    // ����
   EGlobalLoginStatusType statusType;              // ״̬����
   EServerGatewayStatus     status;                  // ״̬
   int                    playerTotal;             // �������
   int                    playerCurrent;           // ���������
   int                    loginCount;              // ��֤�д���
   CTCPSocket<RECVBUFLENGTH, POSTBUFLENGTH> socket; // ��������
public:
	CGlobalLogin();
   ~CGlobalLogin();
   int Initialize();
   int Resume();
public:
   EServerGatewayStatus GetStatus();
};


//============================================================
// <T>ȫ���û�������Ϣ��</T>
//============================================================
typedef struct _SGlobalPlayerGateInfo{
   int loginId;   // ��¼���������
   int roleCount; // ��ɫ����
} SGlobalPlayerGateInfo;

//============================================================
// <T>ȫ���û���Ϣ��</T>
//============================================================
class CGlobalPlayer: public CObj{
public:
	bool                  used;
   int                   accountId;                       // �˺ű��
   char                  passport[GS_PASSPORT_MAXLENGTH]; // ͨ���˺�
   char                  password[GS_PASSWORD_MAXLENGTH]; // ͨ������
   uint32                token;									 // ��ʱ����
   int                   tokenTimeout;                    // ���Ƴ�ʱ
   int                   gateCount;                       // ���ظ���
   SGlobalPlayerGateInfo gates[GS_LOGIN_MAXCOUNT];        // ������Ϣ
	time_t                lastActived;            
public:
	CGlobalPlayer();
   ~CGlobalPlayer();
	int Initialize();
	int Resume();
public:
	int GetRoleCountByServerId(int serverId);
	bool SetRoleCountByServerId(int serverId, int nRoles);
};

// ������֤���û�
struct CCertifyPlayer{
	bool _inDb;																// ���ݿ����Ƿ��Ѿ�����
	int  _handle;															// ������ͻ��Ķ˿�
	int  _clientIp;														// �ͻ���ip��ַ
	int  _clientPort;														// �ͻ��Ķ˿ں�
	int  _accountId;														// �ͻ����˻�ID
	char _passport[GS_PASSPORT_MAXLENGTH];							// ͨ���˺�
	char _password[GS_PASSWORD_MAXLENGTH];							// ͨ������
	int  _gateCount;														// ���ظ���
	SGlobalPlayerGateInfo _gates[GS_LOGIN_MAXCOUNT];			// ������Ϣ
	uint32                socketTime; 
};
//============================================================
class RBytes{
protected:
   static char HexChars[16];
   static char HexValues[128];
   static RBytes _instance;
public:
   RBytes();
public:
   static char* FromBytes(char* pValues, int count, char* pBuffer, int length);
   static char* ToChars(char* pValues, int count, char* pBuffer, int length);
};
#endif // _GLOBAL_ENTITY_H_