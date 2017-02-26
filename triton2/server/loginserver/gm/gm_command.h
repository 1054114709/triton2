#ifndef _GM_COMMAND_H_
#define _GM_COMMAND_H_

#include <string>
#include <list>
#include "lk_string.h"
#include "google/protobuf/message.h"
#include "message_pb.hxx.pb.h"
#include "message_factory.h"
#include "log_msg_pb.hxx.pb.h"


#define CMD_RESPONSE_HEAD "HTTP/1.1 200 OK\nDate: %s\nServer: XiYou(%d)\nSession-ID: %d\n\
Content-Length: %d\nConnection: close\nContent-Type: text/xml\n\n%s\n"

//args[0], Response TimeStampt like Tue, 16 Sep 2008 07:41:43 GMT
//args[1], WorldID
//args[2], Session-ID is %d, like 1234567
//args[3], Content-Length TODO: I DONOT know
//args[4], command-Result XML String

#define MAX_HTML_LENGTH 2048000
#define SHORT_LENGTH 2048

typedef lk::string<MAX_HTML_LENGTH> CMaxString;
typedef lk::string<SHORT_LENGTH> C2KString;

typedef std::vector< std::pair<std::string, std::string> > replace_t;
typedef const char* (*PF_ID2NAME) ( int );
typedef struct proto_func_t{
	const char* name;
	PF_ID2NAME method;
}proto_func_t;


void protobuf2xml(const Message& pmessage, CMaxString& debug_string, 
		void (*pformat)(CMaxString&, const char*, const char*, const char*));

int code_convert(const char* from_charset, const char* to_charset, char* inbuf, size_t inlen, char* outbuf, size_t* outlen);

int DecodeFromGMStream(int nCommHandle, char* szStream, CMessage* tpMessage);
int FlashToGMStream(CMessage* tpMessage, char* szStream, 
		unsigned int StreamLength, int nSessionID, int(*pfflash)(CMessage*, CMaxString&));


int FlashGmCmdNormalResult(CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdRoleDetailResult(CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdUserStorageInfoResult(CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdRoleLocationResult(CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdNpcDetailResult(CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdTaskInfoResult(CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdRoleProtoResult(CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdUserSocialInfoResult(CMessage* tpMessage, CMaxString& xmlbuf);

int FlashGmCmdIbInfoResult(CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdSqlDmlResult( CMessage* tpMessage, CMaxString& xmlbuf);

int FlashGmCmdRoleEquipmentResult( CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdRolePackInfoResult( CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdRoleItemInPackResult( CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdRoleEquipmentDetailResult( CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdRoleStorageDetailResult( CMessage* tpMessage, CMaxString& xmlbuf);

int FlashGmCmdRoleSkillInfoResult( CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdRoleDetailResult( CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdRoleSkillDetailResult( CMessage* tpMessage, CMaxString& xmlbuf);

// 2009-07-01 ������־��ѯ
int FlashGmCmdGoodAtNpcResult( CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdGoodAtUsersResult( CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdGoodHistoryResult( CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdOperationDetailResult( CMessage* tpMessage, CMaxString& xmlbuf);

// 2010-02-03 ������Ұ�ȫ����
int FlashGmCmdResetRolePassword( CMessage* tpMessage, CMaxString& xmlbuf);

// 2010-02-05
int FlashGmCmdRoleItemOperateResult( CMessage* tpMessage, CMaxString& xmlbuf );
int FlashGmCmdRoleMoneyOperateResult( CMessage* tpMessage, CMaxString& xmlbuf );
int FlashGmCmdRoleExpOperateResult( CMessage* tpMessage, CMaxString& xmlbuf );
int FlashGmCmdItemUpgradeResult( CMessage* tpMessage, CMaxString& xmlbuf );

// ItemID2Name
const char* ItemID2Name(int nItemID);

// TaskID2Name
const char* TaskID2Name(int nTaskID);

// NpcID2Name
const char* NpcID2Name(int nNpcID);

// Desc Item Action
template <int max_width>
lk::string<max_width>& DescItemAction(lk::string<max_width> & desc, const replace_t& repl, const proto_func_t*  func);

// CorpsTotal
int FlashGmCmdCorpsTotalResult(CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdCorpsDetailResult(CMessage* tpMessage, CMaxString& xmlbuf);

int FlashGmCmdCorpsLogResult(CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdFamilyLogResult(CMessage* tpMessage, CMaxString& xmlbuf);

int FlashGmCmdQueryDeathResult(CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdQueryLoginResult(CMessage* tpMessage, CMaxString& xmlbuf);
int FlashGmCmdQueryTaskResult(CMessage* tpMessage, CMaxString& xmlbuf);

// RocoverRoleItem
int FlashGmCmdRecoverRoleEquipResult(CMessage* tpMessage, CMaxString& xmlbuf);

// ��ѯ�ʼ�����
int FlashGmCmdRoleMailResult(CMessage* tpMessage, CMaxString& xmlbuf);

// ��ѯ��ҳƺ�
int FlashGmCmdRoleTitleResult(CMessage* tpMessage, CMaxString& xmlbuf);

// ��ѯ��ҵĵȼ���Ϣ
int FlashGmCmdRoleLevelInfoResult(CMessage* tpMessage, CMaxString& xmlbuf);

// ��ѯ�������
int FlashGmCmdUserInfoByIPResult(CMessage* tpMessage, CMaxString& xmlbuf);

// ��ѯ�������
int FlashGmCmdQueryLogoutIPResult(CMessage* tpMessage, CMaxString& xmlbuf);

int FlashGmCmdQueryStockResult(CMessage* tpMessage, CMaxString& xmlbuf);

// ��ѯԪ����̯���׼�¼
int FlashGmCmdQueryYBStallResult(CMessage* tpMessage, CMaxString& xmlbuf);

enum 
{
	//RoleDetail ����GateServer, GateServer��RoleInfo��ȡ����ҵ���Ϣ��ֱ�ӷ���; LoginServer ����󷵻ظ�gmServer
	//UserStorageInfo ���͵�GateServer, ���������ߣ����������Serverȡ����ҵĲֿ�buffer��
					//�����Ҳ����ߣ������ݿ�ȡ����Ҳֿ�����
	//RoleLocation, ����ͬ��
	//UserLevelInfo ���͵���־����������־����������־���ݿ��ѯ�󷵻�
	//UserSocialInfo ��ҵ���Ϣ��ѯͬUserStorageInfo�Ĳ�ѯ���̣���ҵ�����ϵ�������־�������Ĳ�ѯ����
	//CorpsTotal �ݻ�
	//CorpsDetail
	//CorpsMember
	//GoodsHistoryToNPC ֱ������־��������ѯ����
	//GoodsHistoryFromNPC
	//GoodsHistoryBetweenUsers
	//GoodsHistory
	//PetHistory
	//
	//OperationDetail ��ɫ������¼(so much)
	//GoodsDropLog ��ҵ���Ʒ�ĵ�����־��ѯ, ����־��������ѯ���ֱ��ѯ��Ʒ�ĵ�����־������ҵ���Ʒ���?����ط���ô����?
	  // û��Ψһ��ID��������Ϸ���籣����Ʒʼ����Ψһ��, Ŀǰ��Ψһ��ָ���������������
	//TaskInfo ����Ϸ�����������ҵ�������Ϣ
	//LoginInfo ֱ�Ӵ���־��������ѯ
	//OnlineTime
	//IpInfo
	//UserInfoByIp
	//AttrChangeHistory 
	//
	//ShutUp ֱ�ӷ�����Ϸ������·����Ϣ, ·�ɷ�����ת������Ӧ����, �����Ҳ��ڣ����ش������
	//CancelShutUp
	//KickRole
	//FreezeAccount ���������ߣ����ˣ������ʺ�
	//UnfreezeAccount, 
	//TrusteeUser ��Ӧ��Ϸ�е�ʲô������
	//UntrusteeUser
	//MoveRole
	//EndTask
	//TrusteeStorage, UntrusteeStorage 
	//RecoverRole, ������GMServer���ʲô
	//��ɫת�� �ֹ����
	//PostBulletin ��������
	//MultiExp ˫����������
	//CancelMultiExp ȡ��˫������
	//ChangeMoney ChangeExp ChangeItem ��Ǯ�����鲹��
	//EndFight ��֪����ɶ���ֲ��ǻغ�����Ϸ
	//DeleteRole 
	//ClearBag �����Ұ���
	//ChangePet ���ﲹ�� 
	//PostNews  ��������
	//SetOLGMAccount  ��������GM�˺�
	//IbInfo �̳���Ʒ��ʾ
	//SetIbPrice SetIbLocation IbOnSale IbNotSale IbDescript  
	//IpBind 
};

#endif

