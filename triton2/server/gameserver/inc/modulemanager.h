#ifndef _MODULEMANAGER_H_
#define _MODULEMANAGER_H_

#include <string>
#include "servertool.h"
#include "lk_vector.h"
#include "lk_string.h"

class CEntityPlayer;
class CEntity;
class CCreator;
class CMessage;
class CSharedMem;

namespace SceneServer
{
	class CLogicModule;

// ********************************************************************** //
// CLogicModule
// ********************************************************************** //

class CLogicModule
{
public:
	lk::string<64> mModuleName;

	static CSharedMem* mShmPtr; // �����ڴ�ָ��
	bool mRegist;

public:
	CLogicModule( const char* pModuleName ) /*: mModuleName( pModuleName )*/
	{
		mModuleName.clear();
		mModuleName.append( pModuleName );
	}

	void* operator new( size_t size );
	void  operator delete( void* pointer );
	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* pointer, const char* file, int line);

	bool IsRegist( );

public:
	virtual ~CLogicModule( )	{	}

public:
	// ����������
	virtual void OnLaunchServer( )																		= 0;

	// �˳�������
	virtual void OnExitServer( )																		= 0;

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset )							= 0;

	// ��������
	virtual int OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName )		= 0;

	// ·����Ϣ
	virtual void OnRouterMessage( CMessage* pMessage )													= 0;

	// �ͻ��˷�����Ϣ
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage )							= 0;

	// �ڲ���ʱ��Ϣ
	virtual void OnTimeoutMessage( CMessage* pMessage )													{}

	// ����ʵ��
	virtual void OnCreateEntity( CEntity* pEntity, CCreator* pCreator, bool vFirst )					= 0;

	// ����ʵ��
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode )											= 0;

	// �洢����
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode )									= 0;

	// ��������
	virtual void OnLoadConfig( )	= 0;

	// ��һ�쵽��
	virtual void OnNewDayCome(  ) { return; }

	// ��һ�ܵ���
	virtual void OnNewWeekCome(  ) { return; }

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) = 0;

	// �����������ɹ�
	virtual void OnLaunchComplete( )	{}

	// ���׼���뿪
	virtual void OnPlayerLeave( CEntityPlayer* pPlayer, int nState ){}
};

class CModuleManager : public CSingleton< CModuleManager >
{
public:
	lk::vector< CLogicModule*, 50 >				mModules;	// ģ���б�	
	enum { MAX_LOGICFUC_NUM = 2000 };

public:
	CModuleManager( );
	~CModuleManager( );

public:

	// ע��ģ��
	void RegisterModule( CLogicModule* pModule );

	// ����ע��ģ��
	void LaunchServer( );

	// ����ע��ģ��
	void ExitServer( );

	// ����ע��ģ��
	void RouterMessage( CMessage* pMessage );

	// ����ע��ģ��
	void ClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����ע��ģ��
	void CreateEntity( CEntity* pEntity, CCreator* pCreator, bool vFirst );

	// ����ע��ģ��
	void DestroyEntity( CEntity* pEntity, int vCode );

	// ����ע��ģ��
	void Timer( unsigned int vTickCount, unsigned int vTickOffset );

	// ����ע��ģ��
	int CreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName );

	// ����ע��ģ��
	bool FillData( CEntityPlayer* pPlayer, int vSaveCode );

	// �ж��Ƿ���ĳ������
	bool HasFunc( int vFuncID );

	// ��������
	void LoadConfig( );

	// ��һ�쵽��
	void OnNewDayCome( );

	// ��һ�ܵ���
	void OnNewWeekCome( );

	// �����Ƿ�ɹ�
	bool CheckLaunchServer( );

	// �����������ɹ�
	void LaunchComplete();

	// ���׼���뿪
	void OnPlayerLeave( CEntityPlayer *pPlayer, int nState );
};

}
#endif


