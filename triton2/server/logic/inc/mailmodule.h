#pragma once

#include "mailmessage_pb.hxx.pb.h"
#include "servercore.h"
#include "servertool.h"
#include "proclient_svr.h"
#include "servermessage_pb.hxx.pb.h"

// ********************************************************************** //
// CFriendModule
// ********************************************************************** //
class CMailModule : public CLogicModule, public CSingleton< CMailModule >
{

public:
	static char			sModuleName[ NAME_LENGTH ];
public:
	CMailModule( ) : CLogicModule( sModuleName ){ }
public:
	// ������ϢCMessageOpenMailBoxRequest
	void OnmessageOpenMailBoxReq( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ������ϢCMessageShutDownMailBoxRequest
	void OnmessageShutDownMailBoxReq( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ������ϢCMessageOpenSendMailBox
	void OnMessageOpenSendMailBox( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ������ϢCMessageOpenSendMailBox
	void OnMessageOpenReadMailBox( CEntityPlayer* pPlayer, CMessage* pMessage );
	 
	// ������ϢCMessageMailChangeItem
	void OnMessageChangeItem( CEntityPlayer* pPlayer, CMessage* pMessage );		
	
	// ������ϢCMessageMailSend
	void OnMessageSendMail( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ������ϢCMessageIfPlayerOnLine
	void OnMessageCanMailSend( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ������ϢCMessageShutMailBoxRequest
	void OnMessageShutMailBox( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ������ϢCMessageShutReadMailBoxRequest
	void OnMessageShutReadMailBox( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ������ϢCMessageShutSendMailBoxRequest
	void OnMessageShutSendMailBox( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ������ϢCMessageMailRead
	void OnMessageReadMail( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ������ϢCMessageGetAccessory
	void OnMessageGetAccessory( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ������ϢCMessageDelMail
	void OnMessageDelMail( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ������ϢCMessageReadMailEnd
	void OnMessageReadMailEnd( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������ϢCMessageBackMail
	void OnMessageBackMail( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ������ϢCMessageLockMail
	void OnMessageLockMail( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������ϢCMessageUnLockMail
	void OnMessageUnLockMail( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������ϢCMessageGetMailPageRequest
	void OnMessageGetMailPageRequest( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ������ϢCMessageCannelMailSend
	void OnMessageCannelMailSend( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// �����ʼ����ѵ�����
	void OnMessagePayMailMoneyRequest( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
public:
	// ������
	void OpenMailBox( CEntityPlayer*pPlayer );	
	
	// �򿪷�����
	void OpenSendMailBox( CEntityPlayer *pPlayer );
	
	// ���ռ���
	void OpenReadMailBox( CEntityPlayer *pPlayer );
	
	// �������ص����ֲ�ѯ���,�ж��Ƿ���Ը�Ŀ����ҷ����ʼ�
	void  CheckRoleNameInfo( CMessage* pMessage );
	
	// �����ʼ�
	void SendMail( CEntityPlayer* pPlayer, CMessageMailSend* pMessage );
	
	// ���������������������ʼ�
	void ReceiveRouterMail( CMessage *pMessage );
	
	// ��ѯ�������˵Ľ�ɫID��Ϣ
	void CheckInvitationReceiver( CEntityPlayer *pPlayer, CMessageGetPlayerMailInfoResponse *pMessage );

 	// ���û�����ϵͳ�ʼ�   
    void OnSendSysMailToPlayer( CMessage* pMessage );
	
public:
	
	// ����ҷ����ʼ�������Ϣ
	void SendMailErrorCode( CEntityPlayer *pPlayer, int ErrorCode );
	
	// ����ϵͳ�ʼ��Ľӿ�
	int SendSysMail( const char *pDesName, int DesCharid, const char *pTitle, const char *pSrcName, const char *pBody, CItemObject **tpItemObj,int  ItemObjNum, int CountryID, int nMoney = 0, int nCharID = 0 );
	
	// ����ϵͳ�ʼ��Ľӿ�
	int SendSysMail( const char *pDesName, int DesCharID, const char *pTitle, const char *pSrcName, const char *pBody, int *pItemIDList, int *pItemNumList, int nItemNum, int nCountryID, int nMoney = 0, int nCharID = 0 );
	
	// ����ϵͳ�ʼ��Ľӿ�
	int SendSysMailBySysID( int nSysMailID, const char *pDesName, int DesCharID, int *pItemIDList, int *pItemNumList, int nItemNum, int nCountryID, int nMoney = 0, char **pParam = NULL, int *pParamPos = NULL, int nNum = 0, int nCharID = 0 );
	
	// ���npc�ķ�������
	bool CheckMailService( CEntityPlayer *pPlayer, int nEntityID );
	
	// ������ݿ��Ƿ񻹴����ʼ�
	void CheckIfMailInDB( CEntityPlayer *pPlayer, int nMailID, int nCheckType );
	
	// ������ݿ��Ƿ񻹴����ʼ�
	void OnSessionCheckIfMailInDB( CMessage * pMessage, int nCharID, int nMailID );
	
	// Ϊ�����ʼ�����
	void PayMoneyForMail( CEntityPlayer *pPlayer, int nMailID, bool bMailDelted );
	
	// ��ʼ��ϵͳ�ʼ���Ϣ
	int InitializeSysMail( const char *pFileName );
	
	// �ʼ�ת��Ӫ
	void ChangeCampMail( CEntityPlayer *pPlayer,int nOldCampID, int nNewCampID );	
	
public:
	static unsigned int CountSize( );
public:
	// ����������
	virtual void OnLaunchServer( );

	// �˳�������
	virtual void OnExitServer( );

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );

	// ��������
	virtual int OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName );

	// ·����Ϣ
	virtual void OnRouterMessage( CMessage* pMessage );

	// �ͻ��˷�����Ϣ
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����ʵ��
	virtual void OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst );

	// ����ʵ��
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode );

	// �洢����
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode );

	// ��������
	virtual void OnLoadConfig( );

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }

	// ����Gate��Ϣ
	void OnGateMessage( CMessage *pMsg );

	// ����ϵͳ�ʼ����õĻص�����
	static void LoadSysMailConfigCallback(const char* pcConfigPath);
	
	// ������������
	void SendOffLineChatMsg( CEntityPlayer *pPlayer, int nDesCharID, const char *pMsg );

	// ��ȡ��������
	void OnSessionLoadOffLineChatMsg( CMessage *pMsg, int nParam1, int nParam2 );
};



