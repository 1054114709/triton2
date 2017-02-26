#ifndef _BASE_H_
#define _BASE_H_

#include <netinet/in.h>
#include <sys/file.h>
#include <sys/types.h>
#include <vector>
#include <string>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>


#ifdef USE_COREDUMPER
#include "google/coredumper.h"
#endif

#define LOOPBACK_IF_NAME "lo"   
#define MAX_NET_CARDS 16     
#define MAC_ADDR_LEN  16

#define	MAX_CODE_LEN	64000  // �������������Ϣ������

#ifdef _DEBUG_
#define RECVBUFLENGTH	4096000
#define POSTBUFLENGTH	4096000
#else
#define RECVBUFLENGTH	4096000*6
#define POSTBUFLENGTH	4096000*6
#endif


#define MINPROXYMSGLEN	10 // ��Сproxy��Ϣ����(һ���ǿ������͵���Ϣ)

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef False
#define	False  0
#endif

#ifndef True
#define	True   1
#endif

struct timeval;

#define I64FMTD "%llu"

typedef __int64_t   int64;
typedef __int32_t   int32;
typedef __int16_t   int16;
typedef __int8_t    int8;
typedef __uint64_t  uint64;
typedef __uint32_t  uint32;
typedef __uint16_t  uint16;
typedef __uint8_t   uint8;


typedef unsigned char BYTE;
typedef unsigned char byte;



typedef char TName[32];

typedef char TFName[64];


#define MAX_SERVER_TRANS_LEN        64000


#define __LK_FILE__	( ( strrchr( __FILE__, '/' ) == NULL ) ? __FILE__ :  strrchr( __FILE__, '/' ) + 1 )


// �Ƿ�ʹ��google��Դ��coredumper��
#ifdef USE_COREDUMPER
#define WRITE_COREDUMP WriteCoreDump
#else
#define WRITE_COREDUMP
#endif

typedef enum
{
	Block = 0,
	NBlock = 1
} TBlockFlag;



typedef struct
{
	int m_iYear;
	int m_iMon;
	int m_iDay;
	int m_iHour;
	int m_iMin;
	int m_iSec;
	int m_iMSec;
} TStruTime;

// �ѵ�ǰʱ��(��)ת��Ϊ��ʶ�����������
int GetStructTime(time_t tTime, TStruTime *pstTime);
void TrimStr( char *strInput );//�ָ��ַ�������ȡ����
int TimeValPlus(timeval& tvA, timeval& tvB, timeval& tvResult);
int TimeValMinus(timeval& tvA, timeval& tvB, timeval& tvResult);
int TimeValMinus(timeval& tvA, timeval& tvB);

// �� YYYY-MM-DD HH:MM:SS ��ʽ���ַ���ʱ��ת����time_t
time_t TimeStrToRealTime( const char* pszTimeStrs );

//const char* GetTimeString( time_t& time, char* buff );


int SplitSockAddr( const char* vAddress, char* vIP, short& vPort );
int SockAddrToString(sockaddr_in *pstSockAddr, char *szResult);
int SplitSockAddr( const char* vAddress, char* vIP, short& vPort );


typedef std::vector<std::string> Tokens;
Tokens StrSplit(const std::string &src, const std::string &sep);


// Linuxƽ̨�·���΢��
namespace LINEKONG
{
	uint64_t GetTickCount();
}

#ifndef IS_DOUBLE_CHAR
#define IS_DOUBLE_CHAR(ch) 		( ch>=0xA0&&ch<0xFF)
#endif

// �����ַ����е�ת���ַ�
int EscapeDataString(char **dest, int iDstLen, char *src , int iSrcLen);

// ���������Կ
int GetRandomKey( char *src, int len );



/************************************************************************/
/* ʱ����жϺ���                                                                     */
/************************************************************************/
//һ�������
#define SECONDS_OF_DAY   (60*60*24)
//һСʱ������
#define SECONDS_OF_HOUR   (60*60)
//һ�����ڵ���������������1-6�ֱ�Ϊ��Ӧ��ֵ����������Ϊ0
#define WEEK_DAY_NUM                     7
//time������ʼʱ�������������1970.1.1��Ϊ������
#define WEEK_DAY_OFC_OMPUTETIME_BEGIN              4

// ȡ��UTCʱ��
int GetUTCAndLocalDiffSec();

// �Ƿ����µ�һ��
bool IsANewDay(time_t tOldTime,  time_t tNewTime);

// �Ƿ����µ�һ��
bool IsANewWeek(time_t tOldTime, time_t tNewTime);

// �Ƿ����µ�һ��
bool IsANewMonth(time_t tOldTime, time_t tNewTime);

// �õ���ǰ�����ڼ�
int GetTimeWeekNum(time_t tTime);

// ��׼time_tʱ��͵�����ַ�����HH:MM:SS�Ƚ� 0-��ȣ�>0-����; <0-С��
int IntTimeCompareToStringTime( time_t tNow, const char* pszTimeStr );

// �ַ���ת������
int charset_convert(const char* from_charset, const char* to_charset, char* inbuf, size_t inlen, char* outbuf, size_t* poutlen);

// ��ӡ������ջ���ļ�,���log4cpp��־ʹ��,���̰߳�ȫ
void print_trace_fd ( const char* fd_name );

// ��ȡ������Ϣ
bool GetNicInfoForLinux( char *pMacBuffer, char *pIpBuffer );

// ����һ���ļ���
int CreatDir( const char *pDirName, int nMode );

// ����UTF-8��ʽ�ַ������ַ����� 
int GetUTF8CharLen(char* pcUTF8String, int nBufferLen);

int CalSum(const char* from, size_t len);

int get_file_length( const char* file );

// �������ݿ��û���/����ӽ���
bool DecryptAscIICode(const char* szInput, int nInput, char* szOutput, int* pnOutput);

// 16�����ַ���ת��Ϊ����; 0�ɹ�; !0ʧ��
int HexToDec( const char* shex, int& idec );


#define SHMKEY_HEX_STR_LEN 8  // �����ڴ�hex����key����

// ���ļ����ɹ����ڴ��õ�key
int MakeShmKey( const char* pFile, char cID );

#endif



