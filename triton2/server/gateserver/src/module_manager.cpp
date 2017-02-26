// ********************************************************************** //
// ModuleManager.cpp
// ģ�������,����ά��ģ���������
//
// Author: Black
// ********************************************************************** //

#include "module_manager.h"
#include "log.h"
#include "base.h"
using namespace GateServer;

template<> CModuleManager* CSingleton< CModuleManager >::spSingleton = NULL;

CSharedMem* CDataModule::mShmPtr = NULL;


// ***************************************************************
//  Function:		SendGateErrorNotice
//  Description:	���ʹ�������ַ���
//	Input:			nErrCode - �����룻 pszErrString - �����ַ���
//	OutPut:			��
//	Return:			��
//	Others:			
//  Date:			10/29/2008
// 
// ***************************************************************
void* CDataModule::operator new( size_t size )
{
	return ( void* ) mShmPtr->CreateSegment( size );
}

// ***************************************************************
//  Function:		SendGateErrorNotice
//  Description:	���ʹ�������ַ���
//	Input:			nErrCode - �����룻 pszErrString - �����ַ���
//	OutPut:			��
//	Return:			��
//	Others:			
//  Date:			10/29/2008
// 
// ***************************************************************
void  CDataModule::operator delete( void* pointer ) { }

// ***************************************************************
//  Function:		CModuleManager
//  Description:	���캯��
//	Input:			
//	OutPut:			��
//	Return:			��
//	Others:			
//  Date:			11/12/2008
// 
// ***************************************************************
CModuleManager::CModuleManager( )
{
	mLastNewDayTime = time(0);
	mLastNewWeakTime = time(0);
	mNewTimer = CWTimer(60000);	// ���ʱ�� ���� 1����
}

// ***************************************************************
//  Function:		~CModuleManager
//  Description:	��������	
//	Input:			
//	OutPut:			��
//	Return:			��
//	Others:			
//  Date:			11/12/2008
// 
// ***************************************************************
CModuleManager::~CModuleManager( )
{
}

// ***************************************************************
//  Function:		RegisterModule
//  Description:	ע��ģ��
//	Input:			
//	OutPut:			��
//	Return:			��
//	Others:			
//  Date:			11/12/2008
// 
// ***************************************************************
void CModuleManager::RegisterModule( CDataModule* pModule )
{
	mModules.push_back( pModule );
}

// ***************************************************************
//  Function:		LaunchServer
//  Description:	Gate������ʱ��֪ͨ��ģ��
//	Input:			
//	OutPut:			��
//	Return:			��
//	Others:			
//  Date:			11/12/2008
// 
// ***************************************************************
void CModuleManager::LaunchServer( )
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
	{
		mModules[ i ]->OnLaunchServer( );
	}
}

// ***************************************************************
//  Function:		ExitServer
//  Description:	GateServer�˳���ʱ��֪ͨ��ģ��
//	Input:			
//	OutPut:			��
//	Return:			��
//	Others:			
//  Date:			11/12/2008
// 
// ***************************************************************
void CModuleManager::ExitServer()
{
	for ( size_t i = 0; i < mModules.size(); i ++ )
	{
		mModules[i]->OnExitServer();
	}
}

// ����ע��ģ��
// ***************************************************************
//  Function:		OnMessage
//  Description:	��ӦGameServer���͹��������Ϣ
//	Input:			
//	OutPut:			
//	Return:			
//	Others:			
//  Date:			11/12/2008
// 
// ***************************************************************
void CModuleManager::OnMessage(int nServerID, CMessage* pMessage )
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
	{
		if( mModules[i] != NULL)
		{
			mModules[ i ]->OnMessage( nServerID, pMessage );
		}
	}
}


// ***************************************************************
//  Function:		Timer
//  Description:	
//	Input:			
//	OutPut:			��
//	Return:			��
//	Others:			
//  Date:			11/12/2008
// 
// ***************************************************************
void CModuleManager::Timer( unsigned int vTickCount, unsigned int vTickOffset )
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
		mModules[ i ]->OnTimer( vTickCount, vTickOffset );

	// �Ƿ���һ��/��һ��
	if( mNewTimer.Elapse( vTickOffset ) )
	{
		time_t tNow = time(NULL);
		if( IsANewDay( mLastNewDayTime, tNow ) )
		{
			OnNewDayCome();
			mLastNewDayTime = tNow;
		}
		if( IsANewWeek( mLastNewWeakTime, tNow) )
		{
			OnNewWeekCome();
			mLastNewWeakTime = tNow;
		}
	}
}


void CModuleManager::OnReloadCfg()
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
	{
		mModules[ i ]->ReloadCfg();
	}
}

bool CModuleManager::IsLaunched()
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
	{
		if (! mModules[ i ]->IsLaunched()) 
		{
			LOG_WARN("default", "Module(%d) is not launch successfully!", i);
			return false;
		}
	}

	return true;
}

void CModuleManager::OnNewDayCome()
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
		mModules[ i ]->OnNewDayCome( );
}

void CModuleManager::OnNewWeekCome()
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
		mModules[ i ]->OnNewWeekCome( );
}

void CModuleManager::OnLaunchComplete()
{
	for ( size_t i = 0; i < mModules.size( ); i ++ )
		mModules[ i ]->OnLaunchComplete( );
}
