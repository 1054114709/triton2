#pragma once
// ***************************************************************
//  File:	log.h   version:  1.0
//	Date:	05/23/2008
// 	Desc:	log��ʵ�ֻ��ڿ�Դ���Log4Cpp-1.0, ��֮�Ͻ����˷�װ�ͺ꿪��.
//			����ʵ�ַ��������õĻؾ��ļ���ʽ����־�ļ�,֧����־�ּ�.
//			���������͵���־����ͳһ����,�����ƽ���
//  
//  Copyright (C) 2008 - LineKong Entertainment Technology Co.,Ltd
//						All Rights Reserved 
// ***************************************************************

// ��־ϵͳ����

#include <stdarg.h>


#ifdef USE_LOG4CPP
#	define INIT_ROLLINGFILE_LOG		InitLog					// ��ʼ��һ����־���ͣ����ڻؾ��ļ�)
#	define LOG_SHUTDOWN_ALL			ShutdownAllLog()		// �ر�����������־
#	define LOG_SHUTDOWN				ShutdownLog				// ������־���ر���־
#ifdef _DEBUG_
#	define LOG_DEBUG(logname, fmt, ... )				LogDebug(logname, fmt, ##__VA_ARGS__ )
#else
#	define LOG_DEBUG(logname, fmt, ... )				
#endif // !_DEBUG_
#	define LOG_NOTICE(logname, fmt, ... )				LogNotice(logname, fmt, ##__VA_ARGS__ )
#	define LOG_INFO(logname, fmt, ... )					LogInfo(logname, fmt, ##__VA_ARGS__ )
#	define LOG_WARN(logname, fmt, ... )					LogWarn(logname, fmt, ##__VA_ARGS__ )
#	define LOG_ERROR(logname, fmt, ... )				LogError(logname, fmt, ##__VA_ARGS__ )
#	define LOG_FATAL(logname, fmt, ... )				LogFatal(logname, fmt, ##__VA_ARGS__ )
#	define LOG(logname, fmt, ... )						Log(logname, fmt, ##__VA_ARGS__ )
#	define RE_INIT_LOG(logname, fmt, ... )				ReInitLog
#else
#	define INIT_ROLLINGFILE_LOG(logname, fmt, ... )	
#	define LOG_SHUTDOWN_ALL(logname, fmt, ... )	
#	define LOG_SHUTDOWN(logname, fmt, ... )	
#	define LOG_NOTICE(logname, fmt, ... )
#	define LOG_DEBUG(logname, fmt, ... )
#	define LOG_INFO(logname, fmt, ... )	
#	define LOG_WARN(logname, fmt, ... )
#	define LOG_ERROR(logname, fmt, ... )
#	define LOG_FATAL(logname, fmt, ... )
#	define LOG(logname, fmt, ... )
#	define RE_INIT_LOG				
#endif // !USE_LOG4CPP


//	��־�ȼ�
// NOTSET <  DEBUG < INFO  < WARN < LEVEL_NOTICE < ERROR  < FATAL 
enum LogLevel
{	
	LEVEL_FATAL  = 0,
	LEVEL_ERROR  = 300,
	LEVEL_WARN   = 400,
	LEVEL_NOTICE = 500,
	LEVEL_INFO   = 600,
	LEVEL_DEBUG  = 700,
	LEVEL_NOTSET = 800,
};


// ***************************************************************
//  Function: 	InitLog   
//  Description:��ʼ��һ�����͵���־�������������־�Ѵ��ڣ������³�ʼ���� 
//				��������ڣ��򴴽���
//  Date: 		05/23/2008
// 
// ***************************************************************
int InitLog( const char*	vLogName,						/*��־���͵�����(�ؼ���,�ɴ˶�λ����־�ļ�)*/
			const char*		vLogDir,						/*�ļ�����(·��)*/
			LogLevel		vPriority = LEVEL_NOTSET,		/*��־�ȼ�*/
			unsigned int	vMaxFileSize = 10*1024*1024,	/*�ؾ��ļ���󳤶�*/
			unsigned int	vMaxBackupIndex = 40,			/*�ؾ��ļ�����*/
			bool			vAppend = true);				/*�Ƿ�ض�(Ĭ�ϼ���)*/



// ***************************************************************
//  Function: 	InitLog   
//  Description:���¸��Ѵ��ڵ���־��ֵ�����ǲ��ܸı���־�����ƣ��Լ���λ���ļ���
//  Date: 		05/23/2008
// 
// ***************************************************************
int ReInitLog( const char* vLogName, 
			  LogLevel		vPriority = LEVEL_NOTSET,		/*��־�ȼ�*/
			  unsigned int	vMaxFileSize = 10*1024*1024,	/*�ؾ��ļ���󳤶�*/
			  unsigned int	vMaxBackupIndex = 40);			/*�ؾ��ļ�����*/
						


// ***************************************************************
//  Function: 	ShutdownAllLog   
//  Description:�ر��������µ���־��(�����ļ�����������ض���),�ڳ����˳�ǰ��.
//  Date: 		05/23/2008
// 
// ***************************************************************
int ShutdownAllLog( );

// ***************************************************************
//  Function: 	ShutdownLog   
//  Description:�ر���־( ������־���� )
//  Date: 		07/25/2009
// 
// ***************************************************************
int ShutdownLog( const char *pLogName );


// ***************************************************************
//  Function: 	LogXXX   
//  Description:������־��¼������д�봴��ʱ�������ļ�.
//  Date: 		05/23/2008
// 
// ***************************************************************
int LogDebug	( const char* vLogName, const char* vFmt, ... );
int LogInfo		( const char* vLogName, const char* vFmt, ... );
int LogNotice	( const char* vLogName, const char* vFmt, ... );
int LogWarn		( const char* vLogName, const char* vFmt, ... );
int LogError	( const char* vLogName, const char* vFmt, ... );
int LogFatal	( const char* vLogName, const char* vFmt, ... );
int log			( const char* vLogName, int vPriority, const char* vFmt, ... );

void Log_bin( const char* vLogName, void* vBin, int vBinLen );

int LogDebug_va	( const char* vLogName, const char* vFmt, va_list ap);
int LogNotice_va( const char* vLogName, const char* vFmt, va_list ap);
int LogInfo_va	( const char* vLogName, const char* vFmt, va_list ap );
int LogWarn_va	( const char* vLogName, const char* vFmt, va_list ap );
int LogError_va	( const char* vLogName, const char* vFmt, va_list ap );
int LogFatal_va	( const char* vLogName, const char* vFmt, va_list ap );
int log_va		( const char* vLogName, int vPriority, const char* vFmt, va_list ap );


//int LogDebug	( const char* vFmt, ... );
//int LogInfo		( const char* vFmt, ... );
//int LogWarn		( const char* vFmt, ... );
//int LogError	( const char* vFmt, ... );
//int LogFatal	( const char* vFmt, ... );
//int log( int vPriority, const char* vFmt, ... );

