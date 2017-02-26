/*
 *	Achieve Module
 *  Created By: Gao Hong
 */

// Include Head Files
#pragma once

#include "servercore.h"
#include "servertool.h"
#include "scenelogic.h"

#include "errcode.h"
#include "achieve.h"
#include "achievetype.h"
#include "achievemessage_pb.hxx.pb.h"

// �ɾ��߼�����
class CAchieveModule : public CLogicModule, public CSingleton< CAchieveModule >
{
public:	
	typedef lk::hash_map< int, CAchieveCfgItem, MAX_ACHIEVE_NUM > ACHIEVE_CFG_LIST;
	// �����������ҳɾ������б�
	typedef lk::hash_map< int, int, SERVER_CAP_PLAYER > ACHIEVE_UNIT_TYPE;
	ACHIEVE_UNIT_TYPE	mAchieveUnitList;
	ACHIEVE_CFG_LIST	mAchieveCfgList;
	
public:
	CAchieveModule() : CLogicModule( sModuleName )	
	{
		mAchieveUnitList.initailize();
		mAchieveCfgList.initailize();
	}
	~CAchieveModule()
	{ 
		mAchieveUnitList.clear();
		mAchieveCfgList.clear();
	}
	static char		sModuleName[ NAME_LENGTH ];
	static unsigned int CountSize();

	virtual void OnLaunchServer( );
	virtual void OnExitServer( );
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );
	virtual int	 OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName );
	virtual void OnRouterMessage( CMessage* pMessage );
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage );
	virtual void OnCreateEntity( CEntity* pEntity, CCreator* pCreator, bool vFirst );
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode );
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode );
	virtual void OnLoadConfig( );
	virtual bool OnCheckLaunch( ) { return true; }

	// Internal Interface
public:
	int	LoadAchieveCfg();
	int LoadAchieveDBData( int nAccountID, int nCharID );

	int GetAchieveDataUnit( int nCharID );
	int DelAchieveDataUnit( int nCharID );
	CAchieveCfgItem*  GetAchieveCfgItem( int nAchieveID );


	void OnDBSession( CMessage* npMessage, int nParam1, int nParam2 );
	void OnSessionQueryAchieveDB( CMessage* npMessage, int nParam1, int nParam2 );
	void OnSessionSaveAchieveDB( CMessage* npMessage, int nParam1, int nParam2 );

	// ���سɾ����õĻص�����
	static void LoadAchieveConfigCallback(const char* pcConfigPath);
	// External Interface
public:
	// �ɾ��ϱ�����
	void OnMessageReportAchieveRequest( CEntityPlayer* npPlayer, CMessage* npMessage );
	// ��ȡ�����ɾ���������
	void OnMessageObtainSingleAchieveRequest( CEntityPlayer* npPlayer, CMessage* npMessage );
	// ��ȡ���гɾ���������
	void OnMessageObtainAllAchieveRequest( CEntityPlayer* npPlayer, CMessage* npMessage );
	// ��ȡ������������
	void OnMessageObtainAllHonorRequest( CEntityPlayer* npPlayer, CMessage* npMessage );

	void SendAchieveFinishNotice( CEntityPlayer* npPlayer, int nAchieveID );

	void OnEventSaveAchieveSession( CEntityPlayer* npPlayer );
	void OnEventInitAchieveDB( CEntityPlayer* npPlayer );
	void OnEventSendAward( CEntityPlayer* npPlayer, int nAwardID, int nID );
	void OnEventHonor( CEntityPlayer* npPlayer, CAchieveDataUnit* npUnit, CAchieveCfgItem* npCfgItem );
	void OnEventClearAchieveMemory( CEntityPlayer* npPlayer );

	// ����ģ�鴥���ɾ� [12/10/2009 Macro]
	void OnEventFireAchieve( CEntityPlayer* npPlayer, int nValue, int nParam );

	void OnEventInsertHonor( CEntityPlayer* npPlayer, int nMapID );
	void OnMessageGetStageBonusRequest( CEntityPlayer* npPlayer, CMessage* npMessage );
};
