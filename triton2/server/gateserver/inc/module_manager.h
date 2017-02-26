#ifndef _MODULE_MANAGER_H_
#define _MODULE_MANAGER_H_

#include "shm.h"
#include "sharemem.h"
#include "message_pb.hxx.pb.h"
#include "servertool.h"

namespace GateServer
{

class CDataModule
{
public:
	static CSharedMem* mShmPtr; // �����ڴ�ָ��

public:
	CDataModule()	{}
	virtual ~CDataModule()	{}

	void* operator new( size_t size );
	void  operator delete( void* pointer );

public:
	// ����������
	virtual void OnLaunchServer( ) = 0;

	// �˳�������
	virtual void OnExitServer( ) = 0;

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset ) = 0;

	// �ͻ��˷�����Ϣ
	virtual void OnMessage( int nServerID, CMessage* pMessage )	= 0;

	// ���¼��������ļ�
	virtual void ReloadCfg() { }

	// �����Ƿ����
	virtual bool IsLaunched() = 0;

	// ��һ�쵽��
	virtual void OnNewDayCome() { }

	// ��һ�ܵ���
	virtual void OnNewWeekCome() { }
	
	// ��������������
	virtual void OnLaunchComplete() { }	  
};


class CModuleManager : public CSingleton< CModuleManager >
{
private:
	std::vector< CDataModule* >				mModules;	// ģ���б�
	time_t	mLastNewDayTime;		// ��һ�Ρ���һ�족����ʱ��
	time_t	mLastNewWeakTime;		// ��һ�Ρ���һ�ܡ�����ʱ��
	CWTimer	mNewTimer;		// ��ʱ�����(�Ƿ�����һ�죬��һ��)

public:
	CModuleManager();
	~CModuleManager();

	void RegisterModule( CDataModule* pModule );

	void LaunchServer();

	void ExitServer();

	void OnMessage( int nServerID, CMessage* pMessage );

	void Timer( unsigned int vTickCount, unsigned int vTickOffset );

	void OnReloadCfg();

	bool IsLaunched();

	void OnNewDayCome();
	void OnNewWeekCome();	
	void OnLaunchComplete() ;
};

}

#endif



