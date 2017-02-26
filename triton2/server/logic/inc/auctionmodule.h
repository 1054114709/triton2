#pragma once

#ifdef WIN32
#include <hash_map>
using namespace stdext;
#else
#ifdef LINUX
#include <ext/hash_map>
using namespace __gnu_cxx;
#endif
#endif



// ********************************************************************** //
// CFriendModule
// ********************************************************************** //
class CAuctionModule : public CLogicModule
{

public:
	static char			sModuleName[ NAME_LENGTH ];
public:
	CAuctionModule( ) : CLogicModule( sModuleName )	{	}
	
public:
	// ����������
	virtual void OnLaunchServer( );

	// �˳�������
	virtual void OnExitServer( );

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );

	// ��������
	virtual int OnCreateMap( unsigned short vLineID, unsigned short vMapID, const char* pTplName );

	// ·����Ϣ
	virtual void OnRouterMessage( CMessageRouter* pMessage );

	// �ͻ��˷�����Ϣ
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����ʵ��
	virtual void OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst);

	// ����ʵ��
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode );

		// �洢����
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode );

	void OnAuctionOpen( CDispParams *pParams, CVariant *pResult );
	void OnAuctionClose( CDispParams *pParams, CVariant *pResult );
};



