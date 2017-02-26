#ifndef _MODULEMANAGER_H_
#define _MODULEMANAGER_H_

#include <string>
#include "log.h"
#include "servertool.h"
#include "lk_vector.h"
#include "lk_string.h"
#include "shm.h"
#include "message_pb.hxx.pb.h"
namespace DungeonServer
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
		virtual void OnLoadConfig( )	= 0;

		// ��һ�쵽��
		virtual void OnNewDayCome(  ) { }

		// ��һ�ܵ���
		virtual void OnNewWeekCome(  ) { }

		// ����������ϼ��
		virtual bool OnCheckLaunch( ) = 0;

		// �����������ɹ�
		virtual void OnLaunchComplete( ){ }

		// ���շ�������Ϣ
		virtual void OnServerMessage( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID ) {}

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
		void Timer( unsigned int vTickCount, unsigned int vTickOffset );		
		
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

		// ���շ�������Ϣ
		void ServerMessage( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID );
	};

}
#endif


