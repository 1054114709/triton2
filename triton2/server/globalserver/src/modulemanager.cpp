// ********************************************************************** //
// ModuleManager.cpp
// ģ�������,����ά��ģ���������
//
// Author: Black
// ********************************************************************** //
#include "modulemanager.h"

using namespace DungeonServer;

template<> CModuleManager* CSingleton< CModuleManager >::spSingleton = NULL;

//////////////////////////////////////////////////////////////////////////
// CLogicModule
//////////////////////////////////////////////////////////////////////////
CSharedMem* CLogicModule::mShmPtr = NULL;


void* CLogicModule::operator new( size_t size )
{
	return ( void* ) mShmPtr->CreateSegment( size );
}

void  CLogicModule::operator delete( void* pointer ) { }


void* CLogicModule::operator new(size_t size, const char* file, int line)
{
	return operator new(size);
}
void CLogicModule::operator delete(void* pointer, const char* file, int line)
{

}

bool CLogicModule::IsRegist( )
{
	return mRegist;
}

//////////////////////////////////////////////////////////////////////////
// CModuleManager
//////////////////////////////////////////////////////////////////////////
CModuleManager::CModuleManager( )
{
	//memset( mFuncList, 0, sizeof( mFuncList ) );
	mModules.initailize();
}

CModuleManager::~CModuleManager( )
{
	
}

void CModuleManager::RegisterModule( CLogicModule* pModule )
{
	mModules.push_back( pModule );
	pModule->mRegist = true;
	LOG_INFO( "default", "Module [ %s ] Regist OK", pModule->mModuleName.c_str( ) );
}

void CModuleManager::LaunchServer( )
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
		mModules[ i ]->OnLaunchServer( );
}

void CModuleManager::ExitServer( )
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
		mModules[ i ]->OnExitServer( );
}

// ����ע��ģ��
void CModuleManager::Timer( unsigned int vTickCount, unsigned int vTickOffset )
{
	char buff[128] = {0};

	for ( size_t i = 0; i < mModules.size( ); i ++ )
	{		
		mModules[ i ]->OnTimer( vTickCount, vTickOffset );
	}
}

// ��������
void CModuleManager::LoadConfig( )
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
		mModules[ i ]->OnLoadConfig( );
}

// ��һ�쵽��
void CModuleManager::OnNewDayCome(  )
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
		mModules[ i ]->OnNewDayCome( );
}

// ��һ�ܵ���
void CModuleManager::OnNewWeekCome(  )
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
		mModules[ i ]->OnNewWeekCome( );
}

bool CModuleManager::CheckLaunchServer()
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
	{
		if ( mModules[ i ]->OnCheckLaunch() == false )
			return false;
	}
	return true;
}

// �����������ɹ�
void CModuleManager::LaunchComplete()
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
	{
		mModules[ i ]->OnLaunchComplete();
	}
}


// ���շ�������Ϣ
void CModuleManager::ServerMessage( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID )
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
	{
		mModules[ i ]->OnServerMessage( pMsg, nGameID, nSrcFe, nSrcID );
	}
}