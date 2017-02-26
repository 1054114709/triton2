#pragma once

#include "servercore.h"
#include "servertool.h"


class CEntityPlayer;
class CMessage;
class PBPersonalRankInfo;
class CCreator;


class CRankModule : public CLogicModule, public CSingleton< CRankModule >
{

public:
	CRankModule( ) : CLogicModule( "RankModule" ){ }
	
	static unsigned int CountSize( );

private:

	
	
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

	// ����������Ϣ
	void OnGateMessage(CMessage *pMessage);

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

public:
	
	// �ͻ���ȡ�ȼ������б�
	int OnClientMessagePlayerRankRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ���ػ�Ӧȡ�ȼ������б�
	int OnGateMessagePlayerRankResponse( CMessage* pMessage );

	// ���͸������а���Ϣ������
	int SendPersonalRankInfoToGate( CEntityPlayer* pPlayer );

	// ���Ͷ�����а���Ϣ������
	int SendPersonalRankInfoToGate( std::vector<CEntityPlayer*>& rPlayers, int nType );

	// ���ø���������Ϣ
	void SetPersonalRank( CEntityPlayer* pPlayer, PBPersonalRankInfo* pInfoTobeSet, int nType );

	int OnGateMessageAskPlayerInfoRequest( CMessage* pMessage );

	// �������ط��͵����������а��top10��ҳƺ�
	int OnGateMessageNewTopTenRequest( CMessage* pMessage );

	// �������ط�����ָ����ҵ�top 10 ���а�ƺ�
	int OnGateMessageObtainTopTenResponse( CMessage* pMessage );

	int GetPantaoMark( CEntityPlayer* pPlayer );
	int GetLonggongMark( CEntityPlayer* pPlayer );

	// ���а�ǰʮ���M�зQ̖���U̎���Դ��°�ˢ��
	int RepealOldRankTitle( CMessage* pMessage );
	// ת�������а��Ӧ�ĳƺ�
	int ConvertRankToTitle( int vType, int vIndex ,int& vTitleID);
	// �����ػ�ȡָ����ҵ����а���Ϣ
	int OnObtainRankTitleRequest( CEntityPlayer* vpPlayer );

	// ������ƺŴ���
	int DisposTitleList( CEntityPlayer* npPlayer );

	// ������ƺŴ���
	int OnEventNationTitle( CEntityPlayer* npPlayer, int nTitleID );
};
