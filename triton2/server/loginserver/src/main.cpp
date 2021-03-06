// ********************************************************************** //
// Main.cpp
// 这个文件不用说了, 一看就知道
// ********************************************************************** //

#include "stdafx.hpp"
#include "westserver.h"
#include "loginlogic.h"
#include "version.h"
#include "sys/stat.h"
#include "sys/types.h"

int CGuidGen::sGuid = 0;

#ifdef LINUX
void ignore_pipe()
{
	struct sigaction sig;

	sig.sa_handler = SIG_IGN;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGPIPE,&sig,NULL);
}

void init_daemon(void)
{
	int lock_fd;
	lock_fd = open("./loginlock.lock", O_RDWR|O_CREAT, 0640);
	if(lock_fd < 0 )
	{
		printf("Open Lock File Failed, LoginServer Init Failed!\n");
		exit( 0 );
	}
	int ret;
	ret = flock(lock_fd, LOCK_EX | LOCK_NB);
	if(ret < 0 )
	{
		printf("Lock File Failed, LoginServer is already Running!\n");
		exit ( 0 );
	}

	pid_t pid;

	if ((pid = fork()) != 0) exit(0);

	setsid();

	signal(SIGINT,  SIG_IGN);
	signal(SIGHUP,  SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);                                                                                     
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGHUP,  SIG_IGN);
	ignore_pipe();

	if ((pid = fork()) != 0)                                                                                      
		exit(0);                                                                                                  

	char tPath[ 256 ];
	//snprintf( tPath, sizeof( tPath ) - 1 , "%s/server/loginserver/bin", getenv("TRITON_HOME") );
	getcwd( tPath, sizeof( tPath ) );
	if( chdir((const char *)tPath) )
	{
		printf( "Can't change run dir to %s after init daemon(%s), exit.\n", tPath, strerror(errno));
		exit(2);
	}

	umask(0);
}

void sigusr1_handle( int iSigVal )
{
	CLoginServer::GetSingletonPtr()->SetRunFlag( CLoginServer::EFLG_CTRL_RELOAD );
	signal(SIGUSR1, sigusr1_handle);
}

void sigusr2_handle( int iSigVal )
{
	CLoginServer::GetSingletonPtr()->SetRunFlag( CLoginServer::EFLG_CTRL_QUIT );
	signal(SIGUSR2, sigusr2_handle);
}

int Initailize( int vInitFlag )
{
	char szCmd[ FILE_MAX_PATH ] = {0};
	snprintf(szCmd, sizeof(szCmd)-1,"touch %s", "./loginpipefile");
	system(szCmd);

	unsigned int tkeyCore = MakeKey( "./loginpipefile", 'C' );
	unsigned int tSize = CLoginServer::CountSize() + sizeof( CSharedMem );
	BYTE* tpCoreShm = CreateShareMem ( tkeyCore, tSize );

	LK_ASSERT( ( tpCoreShm != NULL ), exit(1) );

	LOG_INFO( "loginserver", "Core Shm Size is %u ", tSize );

	CSharedMem::pbCurrentShm = tpCoreShm;
	CLoginServer::mShmPtr = new CSharedMem( tkeyCore, tSize, vInitFlag );
	LK_ASSERT( CLoginServer::mShmPtr != NULL, exit( 1 ) );

	if ( CLoginServer::mShmPtr->GetInitMode( ) == SHM_INIT )
	{
		CObj::msCreateMode = 1;
	} 
	else
	{
		CObj::msCreateMode = 0;
	}

	return 0;
}

#endif



void printHint(const char*)
{
	printf("No Help.\n");
}

int main( int argc, char* argv[] )
{
	int tnDaemon = 0;
	int tInitFlag = 1;

	// 创建LOG 目录
	mkdir( "../log", 0777 );

//	INIT_ROLLINGFILE_LOG( "default", "../log/loginserver.log", LEVEL_DEBUG );

	if( argc > 1 )
	{
		if( !strcasecmp(argv[1], "-v") )
		{
#ifdef _DEBUG_
#ifdef TAIWAN
			printf("xyj loginserver debug %s  TaiWan build at %s %s\n", _LOGIN_VER, __DATE__, __TIME__);
#else
			printf("xyj loginserver debug %s  build at %s %s\n", _LOGIN_VER, __DATE__, __TIME__);
#endif
#else
#ifdef TAIWAN
			printf("xyj loginserver release %s  TaiWan  build at %s %s\n", _LOGIN_VER, __DATE__, __TIME__);
#else
			printf("xyj loginserver release %s  build at %s %s\n", _LOGIN_VER, __DATE__, __TIME__);
#endif
#endif
			exit(0);
		}

		if( strcasecmp((const char *)argv[1], "Init") == 0 )
		{
			tInitFlag = 1;
		}

		if( strcasecmp((const char *)argv[1], "-D") == 0 )
		{
			tnDaemon = 1;
		}
	}

	
	//守护模式
	if (tnDaemon) init_daemon();

	Initailize( tInitFlag );

	//创建GlobalServer
	CLoginServer* tpLoginServer= new CLoginServer;
	tpLoginServer->Initialize( tInitFlag );
	tpLoginServer->Launch();

	signal(SIGUSR1, sigusr1_handle);
	signal(SIGUSR2, sigusr2_handle);

	printf( "\n" );
	printf("------------------------------------\n");
	printf("|  xyj-loginserver startup success!|\n");
	printf("------------------------------------\n");

	LOG_NOTICE( "default", "xyj-loginserver startup success!" );


	tpLoginServer->Run( tnDaemon);

	delete tpLoginServer;

	LOG_SHUTDOWN_ALL;

	return 0;
}


