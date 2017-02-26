#pragma once

#include "sceneobj_define.h"
#include "chatmanager.h"
#include "proclient_svr.h"
#include "chat.h"



// ********************************************************************** //
// CChatModule
// ********************************************************************** //
class CChatModule : public CLogicModule, public CSingleton< CChatModule >
{
public:
	static char	sModuleName[ NAME_LENGTH ];
    
   // ��������Ƶ��ʱ�Ӽ�����ʱ��8��
	CWTimer	  mTimer;   	

   //�����Զ������ļ�ʱ����ÿһ����һ�κ�������
    CWTimer   mAutoTimer;	

   //��ȡ�������������ڿ��Է��Ե���Ϣ����
	sAutoMsg  mCurrentAutoChat;	
	CHAT_CFG*   m_sChatCfg;
	bool        m_bIfBugleEmpty;		// ���ڱ�־���ȶ���Ϊ��ʱ���Ƿ�����ҵķ��Դ�����ʾ������	
public:
	CChatModule( ) : CLogicModule( sModuleName ), mTimer(8000),mAutoTimer(1000)	
	{	
		m_sChatCfg = NULL;
		m_bIfBugleEmpty = true;				
	}

	static unsigned int CountSize( );
public:
	// ���Ƶ������
	int CheckChannelRule( CEntityPlayer *pPlayer, int nChannel );

	// ��������������Ϣ
    void CheckChatMsg( CEntityPlayer* pPlayer, CChatContent* pChatContent, int IsAutoMess = 0 ); 
    
    // ������Ƶ�����÷���������Ϣ
    void ChatOnChannel( CEntityPlayer* pPlayer, CChatContent* pChatContent  );  
 
	//����Զ������������Ƿ��п��Է��Ե���ң�����еĻ��򽫷������ݷ��ͳ�ȥ
	void SendAutoMessToClient( CAutoMsg *AutoChat );
	
	// ���ĺ�������
	int ConsumeChatItem( int ItemId, int ItemNum , CEntityPlayer * player, int ItemIndex = -1 );

	// ����Զ�������ʱ���Ƿ�����Ҫ��
	int CheckAutoChatTime( unsigned int time , int channel );
    
	// ��һ�仰����ͨƵ�����ͳ�ȥ
	//void SendMsgOnChannelCommon( CEntityPlayer *pPlayer , const char *pMess );     

	//������ϢCMessageChatSend
	void OnMessageChatSend( CEntityPlayer* pPlayer, CMessage* pMessage, int IsAutoMess = 0 );

	//������ϢCAutoChatMessage
	void OnMessageAutoChat( CEntityPlayer* pPlayer, CMessage* pMessage, int IsAutoMess = 0 );

	//������ϢCStopAutoChatMessage
	void OnMessageStopAutoChat(CEntityPlayer* pPlayer, CMessage* pMesage, int IsAutoMess = 0 );

	//������ϢCMessageUseItem
	void OnMessageUseItem( CEntityPlayer* pPlayer, CMessage* pMesage, int IsAutoMess = 0 );

	//������ϢCMesssageClickBugleItem
	void OnMessageClickBugleItem( CEntityPlayer* pPlayer, CMessage* pMesage, int IsAutoMess = 0 );
	
	//������ϢCMesssageCheckDirtyWord
	void OnMessageCheckDirtyWord( CEntityPlayer* pPlayer, CMessage* pMesage, int IsAutoMess = 0 );  
	
    // ������ͨƵ����Ϣ
	void ChatOnChannelCommon( CEntityPlayer* pPlayer, CChatContent* pChatContent );

	// ��������Ƶ����Ϣ
	void ChatOnChannelP2P( CEntityPlayer* pPlayer, CChatContent* pChatContent );
    
	// ��������Ƶ����Ϣ
	void ChatOnChannelWorld( CEntityPlayer* pPlayer,CChatContent* pChatContent);
    
	// �������Ƶ����Ϣ
	void ChatOnChannelTeam( CEntityPlayer* pPlayer, CChatContent* pChatContent);

	// ����ս��Ƶ��
	void ChatOnChannelBattle( CEntityPlayer* pPlayer, CChatContent* pChatContent);
    
	// ��������Ƶ����Ϣ
	void ChatOnChannelBugle( CEntityPlayer* pPlayer, CChatContent* pChatContent, int ItemIndex = -1 );
	
	// ���͹���Ƶ����Ϣ
	void ChatOnChannelCountry( CEntityPlayer* pPlayer,CChatContent* pChatContent );
	
	// ���ͼ���Ƶ����Ϣ
	void ChatOnChannelFamily( CEntityPlayer* pPlayer, CChatContent* pChatContent);
	
	// ���;���Ƶ����Ϣ
	void ChantOnChannelCorps( CEntityPlayer* pPlayer, CChatContent* pChatContent);
	
	// ����������Ϣ���
	void SendChatResultMsg( CEntityPlayer *pPlayer, int vChannel, int vChatRes, const char *vInfor, const char *vName, int vLeftTime = 0 );	
	
    // ��ֹ�����ĳ��Ƶ������    
    void SetChannelFalse( int vCharID, int vChannel, int nPeriod ); 
        
    // �ָ������ĳ��Ƶ���ķ���Ȩ��
    void SetChannelTrue( int vCharID, int vChannel ); 
    
    // �����������صļ���;��ŵ���Ϣ
    void OnGateChatMsg( CMessage *pMsg );
    
    // ������������
    int InitialChatUserConfig();
    
    // ��ȡ��ҵ�������ݱ�־
    int GetChatUserFlag( CEntityPlayer *pPlayer, ChatCallBackMsg &rMsg );
public:
	// ������
	void CheckDirtyWordOfMsg( char *pMsg );
	
	// ��ȡƵ��ʱ��������Ϣ
	int  GetChannelTime( int vChannel, CChat *tpChat, int &ChatLimitTime, int &MsgLimitTime, TimeLimit *&tpTime, bool bVip = false );
	
	// ��鷢��ʱ��
	int  CheckChatTime( int vChannel, char *pMsg, CChat *tpChat, bool bVip = false );
		
	// ���ȼ�
	int	 CheckLevel( int vChannel, CEntityPlayer *pPlayer );
	
	// ���AP
	int  CheckAP( int vChannel, CEntityPlayer *pPlayer ); 
	
	// ����Զ������������Ϣ
	int OnAutoChat( CEntityPlayer *pPlayer, char *pMsg );
		
	// ����ϵͳ����
	void SendSysNotice( const char *pMsg, int RepeatedNum );

	// �����������ݵ���־������
	void SendChat2Log( CEntityPlayer *pPlayer, CChatContent* npContent );
	
public:
	// ����������
	virtual void OnLaunchServer( );

	// �˳�������
	virtual void OnExitServer( );

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffsekt );

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
	virtual void OnLoadConfig( ) ;	 

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }

	// ���ڼ����������õĻص�����
	static void LoadChatUserConfigCallback(const char* pcConfigPath);
};
