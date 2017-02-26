/******************************************************************************
   ��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

/******************************************************************************
  �ļ���          : tcpctrl.cpp
  �汾��          : 1.0
  ����            : ZHL
  ��������        : 2008-06-10
  ����޸�        : 
  ��������        : Tcp����Դ�ļ�
  �����б�        : 
  �޸���ʷ        : 
  1 ����          : 2008-06-10
    ����          : ZHL
    �޸�����      : ����
*******************************************************************************/

#include <stdlib.h>
//#include <fstream.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#include "config.h"
#include "shm.h"
#include "code_queue.h"
#include "tcpdef.h"
#include "tcpctrl.h"
#include "log.h"
#include "base.h"

BYTE* CTCPCtrl::pCurrentShm = NULL;  /*��ʼ�������ڴ��ĵ�ַ*/

extern int g_nFtokParam;
extern char g_szRunPath[256];

int GetUinFromCode(BYTE* pCode, short nCodeLength)
{
    u_int uiTemp = 0;
    
    if( !pCode || nCodeLength < CSHEAD_BASE_LEN )
    {
        return 0;
    }
    
    memcpy((void *)&uiTemp, (const void *)&pCode[12], sizeof(u_int));
    
   // return (int)ntohl(uiTemp);
	return uiTemp;
}



/*******************************************************************************
  ������          : CTCPCtrl::CTCPCtrl
  ��������        : ���캯��
  �������        : void
  �������        :
  ����ֵ          : ---
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
CTCPCtrl::CTCPCtrl()
{

}


/*******************************************************************************
  ������          : CTCPCtrl::~CTCPCtrl
  ��������        : ��������
  �������        : void
  �������        :
  ����ֵ          : ---
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
CTCPCtrl::~CTCPCtrl()
{
}


/*******************************************************************************
  ������          : new
  ��������        : ����new������ΪCTCPCtrl���乲���ڴ棬�ṩ�������е����ܡ�
  �������        : size_t nSize
  �������        :
  ����ֵ          : void*
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
void* CTCPCtrl::operator new( size_t nSize )
{
    return (void * )pCurrentShm;
}


/*******************************************************************************
  ������          : delete
  ��������        : ����delete����
  �������        : void *pBase
  �������        :
  ����ֵ          : void
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
void CTCPCtrl::operator delete(void *pBase)
{

}

/*******************************************************************************
  ������          : CTCPCtrl::CountSize
  ��������        : ����CTCPCtrl����Ҫ���ڴ�ռ�
  �������        : void
  �������        :
  ����ֵ          : int
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
int CTCPCtrl::CountSize()
{
    int iTempSize  =  sizeof(CTCPCtrl);
    iTempSize     +=  MAX_SOCKET_NUM * sizeof(TSocketInfo);
    return iTempSize;
}


/*******************************************************************************
  ������          : CTCPCtrl::CreateTCPCtrl
  ��������        : �ڹ����ڴ��ڴ���CTCPCtrl����
  �������        : void
  �������        :
  ����ֵ          : CTCPCtrl*
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
CTCPCtrl* CTCPCtrl::CreateTCPCtrl()
{
    key_t iKey;
    size_t iTempShmSize;
    int iShmID;
    char byPipeID = 'C';
    char szLockFile[] = "./tcppipefile";

	iKey = MakeShmKey( szLockFile, byPipeID );

	LOG_NOTICE( "default", "tcpctrl key is 0X%08X", iKey );

    iTempShmSize = CountSize();

    if( iKey < 0 )
    {
        LOG_ERROR( "default","Error in ftok, %s.", strerror(errno ));
        exit(-1);
    }

    iShmID = shmget( iKey, iTempShmSize, IPC_CREAT|IPC_EXCL|0666);

    if( iShmID < 0 )
    {
        if(errno != EEXIST )
        {
            LOG_ERROR("default","CTCPCtrl: Alloc share memory failed, %s", strerror(errno ));
            exit(-1);
        }

        LOG_ERROR("default","CTCPCtrl: Same shm seg (key=%08X ) exist, now try to attach it...", iKey);

        iShmID = shmget( iKey, iTempShmSize, 0666);
        if( iShmID < 0 )
        {
            LOG_ERROR("default","CTCPCtrl: Attach to share memory %d failed, %s. Now try to touch it", iShmID, strerror(errno ));
            iShmID = shmget( iKey, 0, 0666);
            if( iShmID < 0 )
            {
                LOG_ERROR("default","Fatel error, touch to shm failed, %s.", strerror(errno ));
                exit(-1);
            }
            else
            {
                LOG_ERROR("default","First remove the exist share memory %d", iShmID);
                if( shmctl( iShmID, IPC_RMID, NULL ) )
                {
                    LOG_ERROR("default","Remove share memory failed, %s", strerror(errno ));
                    exit(-1);
                }
                iShmID = shmget( iKey, iTempShmSize, IPC_CREAT|IPC_EXCL|0666);
                if( iShmID < 0 )
                {
                    LOG_ERROR("default","Fatal error, alloc share memory failed, %s", strerror(errno ));
                    exit(-1);
                }
            }
        }
        else
        {
            LOG_ERROR("default","Attach to share memory succeed");
        }
    }

    LOG_INFO("default","Successfully alloced share memory block, key = %08X, id = %d, size = %d", iKey, iShmID, iTempShmSize);

    pCurrentShm = (BYTE * )shmat( iShmID, NULL, 0);

    CTCPCtrl *pTempTCPCtrl = new CTCPCtrl;

    return pTempTCPCtrl;
}


/*******************************************************************************
  ������          : CTCPCtrl::Initialize
  ��������        : ��ʼ��CTCPCtrl����ĸ���Ա����
  �������        : TConfig *pstConfig
  �������        :
  ����ֵ          : int
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
int CTCPCtrl::Initialize()
{
    int i;
    int iTempRet;
    BYTE *pbTemp;
    int iIndex;

    m_iRunFlag = 0;
    m_iWriteStatCount = 0;
    memset(&m_stTcpStat, 0, sizeof(m_stTcpStat));
 
    iTempRet = ReadCfgFile();
    if( 0 != iTempRet )
    {
        return iTempRet;
    }

    pCurrentShm = pCurrentShm + sizeof(*this);
    for( i = 0; i < MAX_SOCKET_NUM; i++ )
    {
        /*������socket�ṹ���г�ʼ��*/
        //m_pstSocketInfo[i] = new TSocketInfo;
        pbTemp = pCurrentShm + i * sizeof(TSocketInfo);
        m_pstSocketInfo[i] = (TSocketInfo *)pbTemp;

        /*��ʼ��socketinfo*/
        memset(m_pstSocketInfo[i], 0, sizeof(TSocketInfo));
        m_pstSocketInfo[i]->m_iSocket   = INVALID_SOCKET;
    }

    events = NULL;

    /*��ʼ�������˿�*/    
    for (i = 0; i < m_stConfig.m_iListenPortNum; i++)
    {
        iTempRet = InitEpollSocket((USHORT)m_stConfig.m_iListenPorts[i]);
        if (0 != iTempRet)
        {
           LOG_ERROR("default","InitEpollSocket Failed! So TCP Server Init Failed!");   
            return iTempRet;
        }
       LOG_INFO("default","Socket id = %d Listen port %d Ok!\n", m_iSocket, m_stConfig.m_iListenPorts[i]);

        iIndex = m_iSocket;

        m_pstSocketInfo[iIndex]->m_iSocket     = m_iSocket;
        m_pstSocketInfo[iIndex]->m_iSocketType = LISTEN_SOCKET;
        m_pstSocketInfo[iIndex]->m_iSocketFlag = RECV_DATA;
        m_pstSocketInfo[iIndex]->m_iConnectedPort = m_stConfig.m_iListenPorts[i];
    }

    maxfds = m_iSocket++;

    timeout = 10;


	strncpy(m_szCSPipeFile, (const char*)g_szRunPath, sizeof(m_szCSPipeFile)-1);
	strncpy(m_szSCPipeFile, (const char*)g_szRunPath, sizeof(m_szSCPipeFile)-1);

	strcat( m_szCSPipeFile, "/cspipefile" );
	strcat( m_szSCPipeFile, "/scpipefile" );

    /*������mainsvrdͨѶ���ڴ�ܵ�*/
    iTempRet = CreatePipe();
    if( 0 != iTempRet )
    {
       LOG_ERROR("default","CreatePipe Failed! So TCP Server Init Failed!");
        return iTempRet;
    }

    time(&m_iNowTime);
    time(&m_iLastTime);
    time(&m_iLastWriteStatTime);

	memset( m_szRunArgs, 0, sizeof(m_szRunArgs));
    LOG_INFO("default","TCP Server Init Success!");

    return 0;
}


int CTCPCtrl::PrepareToRun()
{

}


/*******************************************************************************
  ������          : CTCPCtrl::CheckTimeOut
  ��������        : ��socket���г�ʱ��⣬�ر�һ��ʱ����û�����а���socket��
  �������        : void
  �������        :
  ����ֵ          : int
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
int CTCPCtrl::WriteTcpStat()
{    
    struct tm *tmpTime;
    struct tm tmpTime1;
    struct tm tmpTime2;
    FILE *pFile;
    char szFile[MAX_PATH];

    int  iIndex = m_iWriteStatCount/m_stConfig.m_iMaxLogCount;

    if (0 == iIndex)
    {
        strncpy(szFile, "../log/tcpstat.log", sizeof(szFile)-1);
    }
    else
    {
        snprintf(szFile, sizeof(szFile)-1,  "../log/tcpstat%d.log", iIndex);
    }
    pFile = fopen(szFile, "a+");
    if (NULL == pFile)
    {
        return -1;
    }
    tmpTime = localtime(&m_iLastWriteStatTime);
    memcpy(&tmpTime1, tmpTime, sizeof(struct tm));
    tmpTime = localtime(&m_iNowTime);
    memcpy(&tmpTime2, tmpTime, sizeof(struct tm));
    

	int nSCPipeBegin = 0;
	int nSCPipeEnd = 0;
	int nSCLeft = 0;
	int nCSPipeBegin = 0;
	int nCSPipeEnd = 0;
	int nCSLeft = 0;

	m_pS2CPipe->GetCriticalData( nSCPipeBegin, nSCPipeEnd, nSCLeft );
	m_pC2SPipe->GetCriticalData( nCSPipeBegin, nCSPipeEnd, nCSLeft );

    fprintf(pFile, 
            "------------------------------------------------------------------\n"
            "Begin: [%.4u-%.2u-%.2u,%.2u:%.2u:%.2u]    End: [%.4u-%.2u-%.2u,%.2u:%.2u:%.2u]\n"
            "ConnIncoming %d \n"
            "ConnTotal  %d         maxfd %d\n"
			"PkgRecv  %5d\t	PkgRecvSize %9d\n"
			"PkgSend  %5d\t	PkgSendSize %9d\n"
			"SCPipe: left %d\n"
			"CSPipe: left %d\n",
            tmpTime1.tm_year + 1900,
            tmpTime1.tm_mon + 1,
            tmpTime1.tm_mday,
            tmpTime1.tm_hour,
            tmpTime1.tm_min,
            tmpTime1.tm_sec,

            tmpTime2.tm_year + 1900,
            tmpTime2.tm_mon + 1,
            tmpTime2.tm_mday,
            tmpTime2.tm_hour,
            tmpTime2.tm_min,
            tmpTime2.tm_sec,

            m_stTcpStat.m_iConnIncoming,
            m_stTcpStat.m_iConnTotal,
            maxfds,
			m_stTcpStat.m_iPkgRecv,
			m_stTcpStat.m_iPkgSizeRecv ,
			m_stTcpStat.m_iPkgSend,
			m_stTcpStat.m_iPkgSizeSend,
			nSCLeft,
			nCSLeft
            );

    fclose(pFile);

    m_iWriteStatCount += 4;
    m_stTcpStat.m_iConnIncoming = 0;
	m_stTcpStat.m_iPkgRecv = 0;
	m_stTcpStat.m_iPkgSizeRecv = 0;
	m_stTcpStat.m_iPkgSend = 0;
	m_stTcpStat.m_iPkgSizeSend = 0;

    return 0;
}


/*******************************************************************************
  ������          : CTCPCtrl::CheckTimeOut
  ��������        : ���Socket�Ƿ�ʱ���رճ�ʱ��socket
  �������        : void
  �������        : 
  ����ֵ          : int
  ���ú���        : 
  ��������        : 

  �޸���ʷ        : 
  1 ����          : 2004-2-4
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
int CTCPCtrl::CheckTimeOut()
{
    int    i;
    time_t tempTimeGap;
    time(&m_iNowTime); /*���㵱ǰʱ��*/

    if (m_iNowTime - m_iLastWriteStatTime >= m_stConfig.m_iWriteStatGap)
    {
        WriteTcpStat();
        m_iLastWriteStatTime = m_iNowTime;
    }

    /*���ϴμ��ʱ����ȣ�����ﵽ�˼��������м��*/
    if (m_iNowTime - m_iLastTime < m_stConfig.m_iCheckTimeGap)
    {
        return 0;
    }
    /*�ӵ�1�������շ����ݵ�socket�ṹ��ʼ����ǰ�������socket
    �ж�ÿ��socketͨѶ��ʱ���*/    
    for (i = m_iSocket; i <= maxfds; i++)
    {
        m_pSocketInfo = m_pstSocketInfo[i];
        if (0 == m_pSocketInfo->m_iSocketFlag)
        {
            continue;
        }

        if (MAIN_HAVE_SEND_DATA == m_pSocketInfo->m_iSendFlag) /*���Mainsvrd�Ѿ����socket���͹����ݣ����ж����һ�����հ���ʱ��*/
        {
            tempTimeGap = m_iNowTime - m_pSocketInfo->m_tStamp;
            /*�ѵ�ǰʱ������һ��socket�յ�����ʱ����ȣ����������ָ����ʱ������ر�socket*/
            if (tempTimeGap >= m_stConfig.m_iSocketTimeOut)
            {
                /*��socketͨѶ��ʱ*/            
                LOG_ERROR("default","Client[%s] socket id = %d port %d not recv packet %d seconds, Close.", 
                    m_pSocketInfo->m_szClientIP, m_pSocketInfo->m_iSocket, 
                    m_pSocketInfo->m_iConnectedPort, tempTimeGap);

                ClearSocketInfo(Err_ClientTimeout);
            }
        }
        else /*�ÿͻ����Ѿ����������ˣ�����Mainsvrd��û����������һ��������ʱ�ĳ�ʱ���̣���Ҫ�Ƿ�ֹ���⹥��*/
        {
            tempTimeGap = m_iNowTime - m_pSocketInfo->m_tCreateTime;
            if (m_stConfig.m_iConnTimeOut < tempTimeGap)
            {
                /*��socketͨѶ��ʱ*/

               LOG_ERROR("default","Client[%s] connect port %d Timeout %d seconds, close!",
                    m_pSocketInfo->m_szClientIP, m_pSocketInfo->m_iConnectedPort, tempTimeGap);

                ClearSocketInfo(Err_ClientTimeout);
            }
        }
    }

    /*���¼��ʱ��*/
    m_iLastTime = m_iNowTime;

    return 0;
}

/*******************************************************************************
  ������          : CTCPCtrl::CreatePipe
  ��������        : ������mainsvrdͨѶ�������ڴ�ܵ���һ����TCPSvrd����Mainsvrd�գ�

  �������        : void
  �������        :
  ����ֵ          : int
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
int CTCPCtrl::CreatePipe()
{
    m_pC2SPipe = CreatePipe(m_szCSPipeFile, 'I', IDX_PIPELOCK_C2S ); /*tcpsvrd=>mainsvrd���ڴ�ܵ�*/
    m_pS2CPipe = CreatePipe(m_szSCPipeFile, 'O', IDX_PIPELOCK_S2C ); /*mainsvrd=>tcpsvrd���ڴ�ܵ�*/


    if(!m_pC2SPipe || !m_pS2CPipe)
    {
        return -1;
    }

    return 0;
}

/*******************************************************************************
  ������          : CTCPCtrl::CreatePipe
  ��������        : ���������ڴ�飬����tcpsvrd��mainsvrd֮���ͨѶ������Ѿ���������ʹ����ǰ�������ڴ档
  �������        : const char * szLockFile
                  : char byPipeID
  �������        :
  ����ֵ          : CCodeQueue*
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
CCodeQueue* CTCPCtrl::CreatePipe(const char*szLockFile, char byPipeID, int iLockIdx)
{
	key_t iKey;
    size_t iTempShmSize;
    int iShmID;
    CCodeQueue* pTempCode = NULL;

    if( !szLockFile )
    {
        return NULL;
    }

	iKey = MakeShmKey( szLockFile, byPipeID );

	LOG_NOTICE( "default", "pipe key is 0X%08X", iKey );

	if ( g_nFtokParam != 0 )
	{
		key_t iKeyOld = iKey;
		iKey |= g_nFtokParam;
		printf("ftok %s got key %x, new key is %x\n", szLockFile, iKeyOld, iKey );
	}

    if( iKey < 0 )
    {
        LOG_ERROR("default","Error in ftok, %s.", strerror(errno ));
        exit(-1);
    }
	
	LOG_NOTICE( "default", "Make key use %s, and key is %08X", szLockFile, iKey );

    iTempShmSize = CCodeQueue::CountQueueSize(PIPE_SIZE);
    iTempShmSize += sizeof(CSharedMem);

    LOG_NOTICE("default","Try to alloc share memory of %d bytes...", iTempShmSize);

    iShmID = shmget( iKey, iTempShmSize, IPC_CREAT|IPC_EXCL|0666);

    if( iShmID < 0 )
    {
        if(errno != EEXIST )
        {
            LOG_ERROR("default","Alloc share memory failed, %s", strerror(errno ));
            exit(-1);
        }

        LOG_NOTICE("default","Same shm seg (key=%08X ) exist, now try to attach it...", iKey);

        iShmID = shmget( iKey, iTempShmSize, 0666);
        if( iShmID < 0 )
        {
            LOG_ERROR("default","Attach to share memory %d failed, %s. Now try to touch it", iShmID, strerror(errno ));
            iShmID = shmget( iKey, 0, 0666);
            if( iShmID < 0 )
            {
               LOG_ERROR("default","Fatel error, touch to shm failed, %s.", strerror(errno ));
                exit(-1);
            }
            else
            {
                LOG_ERROR("default","First remove the exist share memory %d", iShmID);
                if( shmctl( iShmID, IPC_RMID, NULL ) )
                {
                   LOG_ERROR("default","Remove share memory failed, %s", strerror(errno ));
                    exit(-1);
                }
                iShmID = shmget( iKey, iTempShmSize, IPC_CREAT|IPC_EXCL|0666);
                if( iShmID < 0 )
                {
                    LOG_ERROR("default","Fatal error, alloc share memory failed, %s", strerror(errno ));
                    exit(-1);
                }
            }
        }
        else
        {
            LOG_INFO("default","Attach to share memory succeed!");
        }
    }

   LOG_INFO("default","Successfully alloced share memory block, key = %08X, id = %d, size = %d", iKey, iShmID, iTempShmSize);

    CSharedMem::pbCurrentShm = (BYTE *)shmat( iShmID, NULL, 0);

    switch(iLockIdx)
    {
        case IDX_PIPELOCK_C2S:
        {
            m_pShmCSPipe = new CSharedMem( iKey, iTempShmSize);
            CCodeQueue::pCurrentShm = m_pShmCSPipe;
            break;
        }
        case IDX_PIPELOCK_S2C:
        {
            m_pShmSCPipe = new CSharedMem( iKey, iTempShmSize);
            CCodeQueue::pCurrentShm = m_pShmSCPipe;
            break;
        }
        default:
        {
            CCodeQueue::pCurrentShm = new CSharedMem(iKey, iTempShmSize);
            break;
        }
    }

	pTempCode = new CCodeQueue(PIPE_SIZE, iLockIdx);

    return pTempCode;
}

/*******************************************************************************
  ������          : CTCPCtrl::Run
  ��������        : ���غ��������������������ܺ���������
  �������        : void
  �������        :
  ����ֵ          : int
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
int CTCPCtrl::Run()
{
    LOG_NOTICE("default","TCP Server main thread run...");
    while(1)
    {
        if(tcpexit == m_iRunFlag)
        {
            WriteTcpStat();
            LOG_NOTICE("default","xyj-tcpserver %s exit!", GetRunArgs() );
            return 0;
        }
        if(reloadcfg == m_iRunFlag)
        {
            WriteTcpStat();
            ReloadCfgFile();
            LOG_NOTICE("default","reload tcpsvrd config file ok!");
            m_iRunFlag = 0;
        }
        GetExMessage();      /*��ȡ�ͻ�������*/
        CheckWaitSendData(); /*��ȡmainsvrd�д����͵�����*/
        CheckTimeOut();      /*���ͨѶ��ʱ��socket*/
    }
    return 0;
}

int CTCPCtrl::ReloadCfgFile()
{
    m_stConfigFile.OpenFile(CONFIG_FILE);

    m_stConfigFile.GetItemValue("syspara",
                          "SocketTimeOut",
                          m_stConfig.m_iSocketTimeOut,
                          180);
    LOG_INFO("default","SocketTimeOut: %d", m_stConfig.m_iSocketTimeOut);

    m_stConfigFile.GetItemValue("syspara",
                          "ConnTimeOut",
                          m_stConfig.m_iConnTimeOut,
                          30);
    LOG_INFO("default","ConnTimeOut: %d", m_stConfig.m_iConnTimeOut);

    m_stConfigFile.GetItemValue("syspara",
                                "CheckTimeGap",
                                m_stConfig.m_iCheckTimeGap,
                                5);
   LOG_INFO("default","CheckTimeGap: %d", m_stConfig.m_iCheckTimeGap);

    m_stConfigFile.GetItemValue("syspara",
                                "WriteStatGap",
                                m_stConfig.m_iWriteStatGap,
                                3600);
    LOG_INFO("default","WriteStatGap: %d", m_stConfig.m_iWriteStatGap);

    m_stConfigFile.GetItemValue("syspara", 
                          "MaxLogCount",
                          m_stConfig.m_iMaxLogCount,
                          10000); 
    LOG_INFO("default","MaxLogCount: %d", m_stConfig.m_iMaxLogCount);

	m_stConfigFile.GetItemValue("syspara", 
		"IgnoreOnErrIPNum",
		m_stConfig.m_iIgnoreOnErrIPNum,
		1); 

	char szIgnoreIPs[100];
	if( m_stConfig.m_iIgnoreOnErrIPNum > MAX_IGNORE_ON_ERR_IP )
	{
		m_stConfig.m_iIgnoreOnErrIPNum = MAX_IGNORE_ON_ERR_IP;
	}

	for( int i = 0; i < m_stConfig.m_iIgnoreOnErrIPNum; i++ )
	{
		snprintf(szIgnoreIPs, sizeof(szIgnoreIPs)-1,  "IgnoreOnErrIP%d", i + 1);
		m_stConfigFile.GetItemValue("syspara", 
			(const char*)szIgnoreIPs,
			&m_stConfig.m_aszIgnoreOnErrIPs[i][0],
			(unsigned int)(IP_LENGTH-1)); 
	}

    m_stConfigFile.CloseFile();

    return 0;
}

int CTCPCtrl::ReadCfgFile()
{
    int i;
    memset(&m_stConfig, 0, sizeof(TConfig));
    m_stConfigFile.OpenFile(CONFIG_FILE);

    m_stConfigFile.GetItemValue("tcpsvrd",
                          "ListenPortNum",
                          m_stConfig.m_iListenPortNum,
                          2);
    LOG_INFO("default","TCP ListenPortNum: %d", m_stConfig.m_iListenPortNum);

    char szPort[100];
    for (i = 0; i < m_stConfig.m_iListenPortNum; i++)
    {
        snprintf(szPort, sizeof(szPort)-1,  "ListenPort%d", i + 1);
        m_stConfigFile.GetItemValue("tcpsvrd",
                                    szPort,
                                    m_stConfig.m_iListenPorts[i],
                                    80);
       LOG_INFO("default","%s: %d", szPort, m_stConfig.m_iListenPorts[i]);
    }

    m_stConfigFile.GetItemValue("syspara",
                                "CheckTimeGap",
                                m_stConfig.m_iCheckTimeGap,
                                5);
   LOG_INFO("default","CheckTimeGap: %d", m_stConfig.m_iCheckTimeGap);

    m_stConfigFile.GetItemValue("syspara",
                          "SocketTimeOut",
                          m_stConfig.m_iSocketTimeOut,
                          180);
    LOG_INFO("default","SocketTimeOut: %d", m_stConfig.m_iSocketTimeOut);

    m_stConfigFile.GetItemValue("syspara",
                          "ConnTimeOut",
                          m_stConfig.m_iConnTimeOut,
                          30);
   LOG_INFO("default","ConnTimeOut: %d", m_stConfig.m_iConnTimeOut);

    m_stConfigFile.GetItemValue("syspara", 
                          "MaxLogCount",
                          m_stConfig.m_iMaxLogCount,
                          10000); 
   LOG_INFO("default","MaxLogCount: %d", m_stConfig.m_iMaxLogCount);

    m_stConfigFile.GetItemValue("syspara",
                                "TCPBufLen",
                                m_stConfig.m_iTcpBufLen,
                                102400);
   LOG_INFO("default","TCPBufLen: %d", m_stConfig.m_iTcpBufLen);

    m_stConfigFile.GetItemValue("syspara",
                                "WriteStatGap",
                                m_stConfig.m_iWriteStatGap,
                                60);
  LOG_INFO("default","WriteStatGap: %d", m_stConfig.m_iWriteStatGap);

    m_stConfigFile.GetItemValue("syspara",
                                "ShareMemMax",
                                m_stConfig.m_iShmMax,
                                 600000000);
  LOG_INFO("default","ShareMemMax: %d", m_stConfig.m_iShmMax);

    m_stConfigFile.GetItemValue("syspara",
                                "OpenFileMax",
                                m_stConfig.m_iOpenFileMax,
                                 60000);
   LOG_INFO("default","OpenFileMax: %d", m_stConfig.m_iOpenFileMax);

    m_stConfigFile.GetItemValue("syspara",
                                "CoreFileSize",
                                m_stConfig.m_iCoreFileSize,
                                 15000000);
    LOG_INFO("default","CoreFileSize: %d", m_stConfig.m_iCoreFileSize);


	m_stConfigFile.GetItemValue("syspara", 
		"IgnoreOnErrIPNum",
		m_stConfig.m_iIgnoreOnErrIPNum,
		1); 

	char szIgnoreIPs[100];
	if( m_stConfig.m_iIgnoreOnErrIPNum > MAX_IGNORE_ON_ERR_IP )
	{
		m_stConfig.m_iIgnoreOnErrIPNum = MAX_IGNORE_ON_ERR_IP;
	}

	for( int i = 0; i < m_stConfig.m_iIgnoreOnErrIPNum; i++ )
	{
		snprintf(szIgnoreIPs, sizeof(szIgnoreIPs)-1,  "IgnoreOnErrIP%d", i + 1);
		m_stConfigFile.GetItemValue("syspara", 
			szIgnoreIPs,
			&m_stConfig.m_aszIgnoreOnErrIPs[i][0],
			(unsigned int)(IP_LENGTH-1)); 
	}

    m_stConfigFile.CloseFile();

    //char szStr[256];
    //snprintf(szStr, sizeof(szStr)-1, "echo %d > /proc/sys/kernel/shmmax", m_stConfig.m_iShmMax);
    //printf("%s\n", szStr);
    //system(szStr);

    //snprintf(szStr, sizeof(szStr)-1,  "echo %d > /proc/sys/fs/file-max", m_stConfig.m_iOpenFileMax);
    //printf("%s\n", szStr);
    //system(szStr);

    //snprintf(szStr,  sizeof(szStr)-1 ,"ulimit -n %d", m_stConfig.m_iOpenFileMax);
    //printf("%s\n", szStr);
    //system(szStr);

    //snprintf(szStr, sizeof(szStr)-1 ,"ulimit -c %d", m_stConfig.m_iCoreFileSize);
    //printf("%s\n", szStr);
    //system(szStr);

    return 0;
}

int CTCPCtrl::SetRunFlag(int iRunFlag)
{
    m_iRunFlag = iRunFlag;
    return 0;
}

/*******************************************************************************
  ������          : CTCPCtrl::ClearSocketInfo
  ��������        : ����socket��Դ���ر�socket��socket�����Ϣ���³�ʼ��
  �������        : void
  �������        :
  ����ֵ          : void
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
void CTCPCtrl::ClearSocketInfo(short enError)
{
    int  iTempRet;

    if(TCP_SUCCESS != enError)
    {
        //TNetHead *pTempNetHead = (TNetHead *)m_szMsgBuf;

		//TODO: htonl
        //pTempNetHead->m_iSrcIP   = htonl(m_pSocketInfo->m_iSrcIP);
        //pTempNetHead->m_nSrcPort = htons(m_pSocketInfo->m_nSrcPort);

        //pTempNetHead->m_iDstIP   = htonl(m_pSocketInfo->m_iUin);
        //pTempNetHead->m_tStamp     = htonl(m_pSocketInfo->m_tCreateTime);

        //pTempNetHead->m_nDstPort = htons(enError);

		m_stNetHead.m_iSrcIP		= (m_pSocketInfo->m_iSrcIP);
		m_stNetHead.m_nSrcPort		= (m_pSocketInfo->m_nSrcPort);
		m_stNetHead.m_tStamp		= (m_pSocketInfo->m_tCreateTime);
		m_stNetHead.m_iDstIP		= (m_pSocketInfo->m_tCreateTime);
		m_stNetHead.m_nDstPort		= m_pSocketInfo->m_iSocket;
		m_stNetHead.m_cState		= enError;

		memcpy( m_szMsgBuf, &m_stNetHead, sizeof(TNetHead) );
     
        iTempRet = m_pC2SPipe->AppendOneCode((const BYTE *)m_szMsgBuf, sizeof(m_stNetHead) );
        if(0 > iTempRet)
        {
            LOG_ERROR( "default","CTCPCtrl::ClearSocketInfo Error occurs while send msg to gamesvrd, ret code = %d.", iTempRet);
        }

		if( ! IsIgnoreIP( m_pSocketInfo->m_szClientIP ) )
		{
			LOG_NOTICE("default","CTCPCtrl::ClearSocketInfo, tcp => game [%d Bytes]close socket:%d for %d IP:%s ", sizeof(m_stNetHead), m_pSocketInfo->m_iSocket, enError, m_pSocketInfo->m_szClientIP);
		}
    }

    /*�ر�Socket����socket�����Ϣ���*/
    if (0 < m_pSocketInfo->m_iSocket)
    {
        m_stEpollEvent.data.fd = m_pSocketInfo->m_iSocket;
        if (epoll_ctl(kdpfd, EPOLL_CTL_DEL, m_pSocketInfo->m_iSocket, &m_stEpollEvent) < 0)
        {
           LOG_ERROR("default","epoll remove socket error: fd = %d ", m_pSocketInfo->m_iSocket);
        }

        closesocket(m_pSocketInfo->m_iSocket);

        //���ĵ�ǰ������socket
        if(m_pSocketInfo->m_iSocket >= maxfds)
        {
            int iUnUseSock;
            for(iUnUseSock = m_pSocketInfo->m_iSocket-1; iUnUseSock >= m_iSocket; iUnUseSock--)
            {
                if(0 != m_pstSocketInfo[iUnUseSock]->m_iSocketFlag)
                {
                    break;
                }
            }
            maxfds = iUnUseSock;
        }
        //����������1
        m_stTcpStat.m_iConnTotal--;
    }

    m_pSocketInfo->m_iSocket     = INVALID_SOCKET;
    m_pSocketInfo->m_iSrcIP      = 0;
    m_pSocketInfo->m_nSrcPort    = 0;
    m_pSocketInfo->m_iDstIP      = 0;
    m_pSocketInfo->m_nDstPort    = (USHORT)(-1);
    m_pSocketInfo->m_iRecvBytes  = 0;
    m_pSocketInfo->m_iSocketType = 0;
    m_pSocketInfo->m_iSocketFlag = 0;
    m_pSocketInfo->m_tCreateTime = 0;
    m_pSocketInfo->m_tStamp      = 0;
    m_pSocketInfo->m_iSendFlag   = 0;
    m_pSocketInfo->m_iConnectedPort = 0;

}


/*******************************************************************************
  ������          : CTCPCtrl::GetExMessage
  �������        : void
  �������        :
  ����ֵ          : int
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
int CTCPCtrl::GetExMessage()
{
    int       iTempRet;
    int       i;
    int       j;
    socklen_t iSockAddrSize;
    SOCKET    iNewSocket;
    SOCKET    iFDTemp;
    SOCKET    iMaxFD;
    int       nfds;
    int       flags;
    struct epoll_event *cevents;

    flags         = 1;
    iSockAddrSize = sizeof(m_stSockAddr);

    nfds = epoll_wait(kdpfd, events, MAX_SOCKET_NUM, timeout);
    if (-1 == nfds)
    {
        LOG_ERROR("default","epoll_wait return -1!");
    }

    for (i = 0, cevents = events; i < nfds; i++, cevents++)
    {
        iFDTemp = cevents->data.fd;
        m_pSocketInfo = m_pstSocketInfo[iFDTemp];
        if (0 >= iFDTemp)
        {
            LOG_ERROR("default","Error cevents->data.fd = %d!", cevents->data.fd);
            continue;
        }

        if (0 != (EPOLLERR & cevents->events))
        {
			m_pSocketInfo = m_pstSocketInfo[iFDTemp];

			if( ! IsIgnoreIP( m_pSocketInfo->m_szClientIP ) )
			{
				LOG_ERROR("default","socket %d: ip %s cevents->events generate error %d, event 0x%08x, total events %d", 
					iFDTemp, m_pSocketInfo->m_szClientIP, errno, cevents->events, nfds);
			}
           
            ClearSocketInfo(Err_ClientClose);
            continue;
        }

        if (0 == (EPOLLIN & cevents->events))
        {
           LOG_ERROR("default","cevents->events does not generate input event!");
            continue;
        }

        //if (iFDTemp == m_iSocket)
        if (LISTEN_SOCKET == m_pSocketInfo->m_iSocketType)
        {
     
            LOG_DEBUG("default","recv  events:%d fd:%d", nfds, iFDTemp);
   
            iNewSocket = accept(iFDTemp, (struct sockaddr *)&m_stSockAddr, (socklen_t *)&iSockAddrSize);
            if(0 >= iNewSocket) /*�ͻ������������Ժ��������ر���*/
            {
                
                 LOG_DEBUG("default","client connected port %d and disconnected!", m_pSocketInfo->m_iConnectedPort);
                
                 continue;
            }

            m_stTcpStat.m_iConnIncoming++;
            if(MAX_SOCKET_NUM <= iNewSocket)
            {
                LOG_ERROR("default","error: socket id is so big %d", iNewSocket);
                 closesocket(iNewSocket);
                 continue;
            }

            if ( ioctl(iNewSocket, FIONBIO, &flags)
                         &&  ((flags = fcntl(iNewSocket, F_GETFL, 0)) < 0
                          ||  fcntl(iNewSocket, F_SETFL, flags | O_NONBLOCK) < 0) )
            {
               LOG_ERROR("default","operate on socket %d error connect port %d!", iNewSocket, m_pSocketInfo->m_iConnectedPort);
                closesocket(iNewSocket);
                continue;
            }

            iTempRet = eph_new_conn(iNewSocket);
            if (0 != iTempRet)
            {
               LOG_ERROR("default","add to epoll failed [socket %d connect port %d]!", iNewSocket, m_pSocketInfo->m_iConnectedPort);
                closesocket(iNewSocket);
                continue;
            }

            //���ĵ�ǰ������socket
            if (iNewSocket > maxfds)
            {
                maxfds = iNewSocket;
            }
            //����������1
            m_stTcpStat.m_iConnTotal++;

            /*����һ�����е�socket�ṹ*/
            j = iNewSocket;
            char *pTempIP = inet_ntoa(m_stSockAddr.sin_addr);
            m_pstSocketInfo[j]->m_iSrcIP = m_stSockAddr.sin_addr.s_addr;
            m_pstSocketInfo[j]->m_nSrcPort = m_stSockAddr.sin_port;
            strncpy(m_pstSocketInfo[j]->m_szClientIP, pTempIP, sizeof(m_pstSocketInfo[j]->m_szClientIP)-1);
            time(&(m_pstSocketInfo[j]->m_tCreateTime));/*��¼��socket������ʱ��*/
            m_pstSocketInfo[j]->m_tStamp      = m_pstSocketInfo[j]->m_tCreateTime;
            m_pstSocketInfo[j]->m_iSocketType = CONNECT_SOCKET;
            m_pstSocketInfo[j]->m_iSocket     = iNewSocket;
            m_pstSocketInfo[j]->m_iSocketFlag = RECV_DATA;  /*����socket��״̬�Ǵ���������*/
            m_pstSocketInfo[j]->m_iConnectedPort = m_pSocketInfo->m_iConnectedPort;

            m_pstSocketInfo[j]->m_iUin = 0;

          
		   if( ! IsIgnoreIP(pTempIP) )
			 LOG_NOTICE("default","%s connected port %d, socket id = %d.", pTempIP, m_pSocketInfo->m_iConnectedPort, iNewSocket);
            
        }
        else
        {
            m_pSocketInfo = m_pstSocketInfo[iFDTemp];
            RecvClientData(iFDTemp);
        }
    }
}


/*******************************************************************************
  ������          : CTCPCtrl::CheckWaitSendData
  ��������        : ���ڴ�ܵ����ȡmainsvrd�����ݣ����͸�client
  �������        : void
  �������        :
  ����ֵ          : int
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
int CTCPCtrl::CheckWaitSendData()
{
    int   iTempRet;
    int   i, j;
    int nCodeLength;

    for(i = 0; i < MAX_SEND_PKGS_ONCE; i++)/*һ����෢��MAX_SEND_PKGS_ONCE�����ݰ�*/
    {
        nCodeLength = MAX_BUF_LEN;
        iTempRet = m_pS2CPipe->GetHeadCode((BYTE * )m_szMsgBuf, &nCodeLength);
        if(0 > iTempRet)
        {
            if (ERRPACKETLENGTH == iTempRet)
            {
				LOG_ERROR("default","Error: In S2C pipe a packet len is %d so long.", nCodeLength);
                break;
            }
            else
            {
                LOG_ERROR("default","Get head code failed, error code = %d.", iTempRet);
                break;
            }
        }

        if(nCodeLength <= 0 )
        {
            break;
        }

        if( SendClientData((BYTE *)m_szMsgBuf, nCodeLength) )
        {
            continue;
        }
    }

    return 0;
}


/*******************************************************************************
  ������          : CTCPCtrl::RecvClientData
  ��������        : ���տͻ��˷��͵�����
  �������        : short nIndex : socket�ṹ������±�
  �������        :
  ����ֵ          : int
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
int CTCPCtrl::TcpRead(SOCKET iSocket, char *pBuf, int iLen)
{
    int iRecvBytes;

    while(1)
    {
        iRecvBytes = read(iSocket, pBuf, iLen);

        if (0 < iRecvBytes)
        {
            return iRecvBytes;
        }
        else
        {    
            if (0 > iRecvBytes && errno == EINTR)
            {
                continue;
            }        
            return iRecvBytes;            
        }        
    }
    return -1;
}

int CTCPCtrl::RecvClientData(short nIndex)
{
    int iTempRet;
    int iRecvBytes;
    int iOffset;
    char *pTemp;
    char *pTemp1;
    int nRecvLen;
    int nRecvAllLen;
    time_t tTempTime;
    //TNetHead *pTempNetHead;
    unsigned int unTempUin;
    SOCKET iSocket = m_pSocketInfo->m_iSocket;
    iOffset = m_pSocketInfo->m_iRecvBytes;

    //iRecvBytes = read(iSocket, m_pSocketInfo->m_szMsgBuf + iOffset, sizeof(m_pSocketInfo->m_szMsgBuf) - iOffset);
    iRecvBytes = TcpRead(iSocket, m_pSocketInfo->m_szMsgBuf + iOffset, sizeof(m_pSocketInfo->m_szMsgBuf) - iOffset);
    if( 0 >= iRecvBytes )
    {
        /*�ͻ���������socket�ر�*/
        
      LOG_NOTICE("default","Client[%s] socket id = %d close connect port %d!", 
             m_pSocketInfo->m_szClientIP, m_pSocketInfo->m_iSocket, m_pSocketInfo->m_iConnectedPort);
       
        ClearSocketInfo(Err_ClientClose);
        return -1;
    }

	/*ͳ����Ϣ*/
	m_stTcpStat.m_iPkgSizeRecv += iRecvBytes;

    /*�����յ������ֽ���*/
    m_pSocketInfo->m_iRecvBytes = m_pSocketInfo->m_iRecvBytes + iRecvBytes;

    pTemp1      = m_pSocketInfo->m_szMsgBuf;
    nRecvAllLen = m_pSocketInfo->m_iRecvBytes;

    time(&(tTempTime)); /*��¼��socket���տͻ������ݵ�ʱ��*/
    m_pSocketInfo->m_tStamp = tTempTime;

    while(1)
    {
        if(4 > nRecvAllLen)
        {
            break;
        }
		//TODO: ntohs
        //nRecvLen = ntohs(*(short*)pTemp1); /*������*/
		nRecvLen = *(short*)pTemp1;

		if ( (10240 < nRecvLen) || (16 > nRecvLen) )
        {
           
            LOG_ERROR("default","the packet len %d is impossible, Client IP :%s , Uin :%u\n", nRecvLen, m_pSocketInfo->m_szClientIP, m_pSocketInfo->m_iUin);
            
            ClearSocketInfo(Err_PacketError);
            return -1;
        }

#ifdef _DEBUG_
		LOG_DEBUG("default","TCP client[%d] [%s]=> gamesvrd [%d Bytes].", m_pSocketInfo->m_iUin, m_pSocketInfo->m_szClientIP, nRecvLen);
        //PrintBinToLog(m_pSocketInfo->m_iUin, pTemp1, nRecvLen);
#endif       

        nRecvAllLen = nRecvAllLen - nRecvLen;
        pTemp1      = pTemp1 + nRecvLen;
        if( 0 > nRecvAllLen )
        {
            nRecvAllLen = nRecvAllLen + nRecvLen;
            pTemp1      = pTemp1 - nRecvLen;
           
           LOG_ERROR("default","Recv client part data left len = %d, real len =%d!", nRecvAllLen, nRecvLen);
            
            break;
        }

        pTemp        = m_szMsgBuf;
        //pTempNetHead = (TNetHead *)m_szMsgBuf

		//TODO: htonl
        //pTempNetHead->m_iSrcIP   = htonl(m_pSocketInfo->m_iSrcIP);
        //pTempNetHead->m_nSrcPort = htons(m_pSocketInfo->m_nSrcPort);
        //pTempNetHead->m_iDstIP   = htonl(m_pSocketInfo->m_tCreateTime);
        //pTempNetHead->m_nDstPort = htons(nIndex);
        //pTempNetHead->m_tStamp   = htonl(tTempTime);

		//pTempNetHead->m_iSrcIP   = (m_pSocketInfo->m_iSrcIP);
		//pTempNetHead->m_nSrcPort = (m_pSocketInfo->m_nSrcPort);
		//pTempNetHead->m_nDstEntityNum = 1;
		//pTempNetHead->m_iDstIP[0]   = (m_pSocketInfo->m_tCreateTime);
		//pTempNetHead->m_nDstPort[0] = (nIndex);
		//pTempNetHead->m_tStamp   = (tTempTime);
		//pTempNetHead->m_cState	 = 0;

		m_stNetHead.m_iSrcIP = (m_pSocketInfo->m_iSrcIP);
		m_stNetHead.m_nSrcPort = (m_pSocketInfo->m_nSrcPort);
		
		m_stNetHead.m_iDstIP = (m_pSocketInfo->m_tCreateTime);
		m_stNetHead.m_nDstPort = (nIndex);
		m_stNetHead.m_tStamp = (tTempTime);
		m_stNetHead.m_cState = 0;

		memcpy( pTemp, &m_stNetHead, sizeof(TNetHead) );

        pTemp = pTemp + sizeof(TNetHead);
        
        memcpy(pTemp, pTemp1 - nRecvLen, nRecvLen);
   
        m_pSocketInfo->m_iUin = GetUinFromCode((BYTE *)pTemp, nRecvLen);

        iTempRet = m_pC2SPipe->AppendOneCode((const BYTE * )m_szMsgBuf, nRecvLen + sizeof(TNetHead));
        if(0 > iTempRet)
        {
            LOG_ERROR( "default", "CTCPCtrl::RecvClientData: Error occurs while send msg to gamesvrd, ret code = %d.", iTempRet);
            ClearSocketInfo(Err_SendToMainSvrd);
            return iTempRet;
        }

		/*ͳ����Ϣ*/
		m_stTcpStat.m_iPkgRecv ++;
    }
    if( 0 == nRecvAllLen )
    {
        m_pSocketInfo->m_iRecvBytes = 0; /*�Ѿ����յ��ֽ���*/
    }
    else
    {
        if ((10240 < nRecvAllLen ) || ( 0 > nRecvAllLen))
        {
            LOG_ERROR("default","the part packet len %d is impossible!", nRecvAllLen);
            ClearSocketInfo(Err_PacketError);
            return -1;
        }
        m_pSocketInfo->m_iRecvBytes = nRecvAllLen;
        memmove(m_pSocketInfo->m_szMsgBuf, pTemp1, nRecvAllLen);
    }

    CheckWaitSendData();

    return 0;
}


/*******************************************************************************
  ������          : CTCPCtrl::SendClientData
  ��������        : ���ڴ�ܵ������ݷ��͸�client
  �������        : BYTE* pbyInBuf
                  : short nInLength
  �������        :
  ����ֵ          : int
  ���ú���        :
  ��������        :

  �޸���ʷ        :
  1 ����          : 
    ����          :  
    �޸ķ�ʽ      : ����
*******************************************************************************/
int CTCPCtrl::TcpWrite(SOCKET iSocket, char *pBuf, int iPackLen)
{
    int iSendBytes;
    int iLeftLen = iPackLen;

    while(1)
    {
        iSendBytes = write(iSocket, pBuf, iPackLen);        
        if (iSendBytes == iPackLen)
        {
            return iSendBytes;
        }
        else
        {
            if (0 >= iSendBytes && EINTR == errno)
            {
                continue;
            }
            
            return iSendBytes;
        }        
    }
} 

int CTCPCtrl::SendClientData(BYTE* pbyInBuf, short nInLength )
{
    BYTE   *pbyTemp = NULL;
    unsigned short	unPackLen;
    unsigned short  unTempShort;
    int    iSendBytes;
    short  nIndex;
    short  nCloseFlag;

    if(!pbyInBuf || nInLength < 0 )
    {
        return -1;
    }

    pbyTemp = pbyInBuf;
    unPackLen = nInLength;
	memcpy( &m_stNetHead, pbyTemp, sizeof(TNetHead));
	

	pbyTemp = pbyTemp + sizeof(TNetHead);
	unPackLen = unPackLen - sizeof(TNetHead);

    memcpy((void *)&unTempShort, (const void *)pbyTemp, sizeof(unsigned short));

    //TODO: ntohl
	//unTempShort = ntohl(unTempShort);
	unTempShort = unTempShort;

    if(unPackLen != unTempShort)
    {
        LOG_ERROR("default","Code length not matched, left length %d is less than body length %d", unPackLen, unTempShort);
        return -1;
    }

	//TODO: ntohl
    //m_stNetHead.m_iDstIP   = ntohl(m_stNetHead.m_iDstIP);
    //m_stNetHead.m_nDstPort = ntohs(m_stNetHead.m_nDstPort);
    //nCloseFlag             = ntohs(m_stNetHead.m_nSrcPort);
	//m_stNetHead.m_iDstIP   = m_stNetHead.m_iDstIP;
	//m_stNetHead.m_nDstPort = m_stNetHead.m_nDstPort;
	nCloseFlag             = m_stNetHead.m_nSrcPort;

	nIndex = m_stNetHead.m_nDstPort;
	if(1 > nIndex || MAX_SOCKET_NUM <= nIndex)
	{
		LOG_ERROR("default","Invalid socket Index %d !", nIndex);
		return -1;
	}
	if(m_pstSocketInfo[nIndex]->m_tCreateTime != (time_t)m_stNetHead.m_iDstIP)
	{
		//LOG_ERROR("default","socket[%d] already closed(%d : %d) : gamesvrd => client [%d Bytes] Failed!", nIndex, m_pstSocketInfo[nIndex]->m_tCreateTime, m_stNetHead.m_iDstIP, unPackLen);
		return -1;
	}

	m_pSocketInfo = m_pstSocketInfo[nIndex]; /*�õ�socketָ��*/

	iSendBytes = TcpWrite(m_pSocketInfo->m_iSocket, (char *)pbyTemp, unPackLen);

	if(unPackLen == iSendBytes) /*�������ݵ��ͻ��˳ɹ�*/
	{        
#ifdef _DEBUG_
		LOG_DEBUG("default","TCP gamesvrd => client[%d] [%s] [%d Bytes].",m_pSocketInfo->m_iUin, m_pSocketInfo->m_szClientIP, iSendBytes);
		//PrintBinToLog(m_pSocketInfo->m_iUin, (char *)pbyTemp, iSendBytes);
#endif

		/*ͳ����Ϣ*/
		m_stTcpStat.m_iPkgSend ++;
		m_stTcpStat.m_iPkgSizeSend += iSendBytes;

		m_pSocketInfo->m_iSendFlag = MAIN_HAVE_SEND_DATA;
		if(0 == nCloseFlag) /*mainsvrd֪ͨtcpsvrd����ر�socket*/
		{
			return 0;
		}
		if(CLOSESOCKET_PLAYER == nCloseFlag)
		{
			LOG_NOTICE("default","after player logout or commit sysmsg, tcpsvrd close socket of:%s!", m_pSocketInfo->m_szClientIP);
		}
		else
		{
			LOG_ERROR("default","Invalid ncloseFlag = %d!", nCloseFlag);
		}

		ClearSocketInfo(TCP_SUCCESS);
		return 0;
	}

	ClearSocketInfo(Err_ClientClose);
	LOG_ERROR("default","send to client %s Failed due to error %d!", m_pSocketInfo->m_szClientIP, errno);

    return 0;
}

int CTCPCtrl::InitEpollSocket(USHORT port)
{
    int iTempRet;
    socklen_t iOptVal = 0;
    int iOptLen = sizeof(int);

    int i, flags = 1;
    struct linger ling = {0, 0};
    struct sockaddr_in addr;

    if (eph_init() == -1)
    {
        return 2;
    }

    if ((m_iSocket = eph_socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        eph_cleanup();
        return 3;
    }

    setsockopt(m_iSocket, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags));
    setsockopt(m_iSocket, SOL_SOCKET, SO_KEEPALIVE, &flags, sizeof(flags));
    setsockopt(m_iSocket, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(m_iSocket, (struct sockaddr *) &addr, sizeof(addr)) == -1)
    {
        eph_close(m_iSocket);
        eph_cleanup();
        return 4;
    }

    /*���÷��ͻ���Ĵ�С*/
    iOptLen = sizeof(socklen_t);
    iOptVal = m_stConfig.m_iTcpBufLen;

    if (setsockopt(m_iSocket, SOL_SOCKET, SO_SNDBUF, (const void *)&iOptVal, iOptLen))
    {
        LOG_INFO("default","Set send buffer size to %d failed!", iOptVal);
        return -1;
    }
    if (!getsockopt(m_iSocket, SOL_SOCKET, SO_SNDBUF, (void *)&iOptVal, (socklen_t *)&iOptLen))
    {
        LOG_INFO("default","Set Send buf of socket is %d.", iOptVal);
    }

    /*���ý��ն��д�С*/
     iTempRet = listen(m_iSocket, 1024);
     if(-1 == iTempRet)
     {
		 LOG_ERROR("default","listen %d connection error!", 1024);
        return -1;
    }

    if (eph_new_conn(m_iSocket) == -1)
    {
        eph_close(m_iSocket);
        eph_cleanup();
        return 5;
    }

    return 0;
}

int CTCPCtrl::eph_init()
{
    if (NULL != events)
    {
        return 0;
    }
    int i;

    memset(&m_stEpollEvent, 0, sizeof(struct epoll_event));
    m_stEpollEvent.events = EPOLLIN | EPOLLERR | EPOLLHUP;
    m_stEpollEvent.data.ptr = NULL;
    m_stEpollEvent.data.fd  = -1;

    if (!(events = (struct epoll_event *) malloc(MAX_SOCKET_NUM * sizeof(struct epoll_event))))
    {
        LOG_ERROR("default","malloc() error!");
        return -1;
    }
    if ((kdpfd = epoll_create(MAX_SOCKET_NUM)) < 0)
    {
        LOG_ERROR("default","Error : %s", strerror(errno));
		LOG_ERROR("default","epoll_create error!");
        return -1;
    }

    return 0;
}

int CTCPCtrl::eph_socket(int domain, int type, int protocol)
{
    int sfd = socket(domain, type, protocol);
    int flags = 1;

    if (sfd == -1)
    {
        return -1;
    }
    if (ioctl(sfd, FIONBIO, &flags)
        && ((flags = fcntl(sfd, F_GETFL, 0)) < 0
        || fcntl(sfd, F_SETFL, flags | O_NONBLOCK) < 0))
    {
        close(sfd);
        return -1;
    }
    return sfd;
}

int CTCPCtrl::eph_new_conn(int sfd)
{
    m_stEpollEvent.data.fd  = sfd;
    if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, sfd, &m_stEpollEvent) < 0)
    {
        return -1;
    }
    return 0;
}

int CTCPCtrl::eph_close(int sfd)
{
    close(sfd);
    return 0;
}

int CTCPCtrl::eph_cleanup(void)
{
    free(events);
    close(kdpfd);
    return 0;
}


void CTCPCtrl::SetRunArgs( const char* pszArgs )
{
	strncpy( m_szRunArgs, pszArgs, sizeof(m_szRunArgs) );
}

char* CTCPCtrl::GetRunArgs( )
{
	return m_szRunArgs;
}


bool CTCPCtrl::IsIgnoreIP( char* szIP )
{
	if( szIP == NULL )
		return false;

	for( int i = 0; i < m_stConfig.m_iIgnoreOnErrIPNum; i++ )
	{
		if( strncmp( szIP, m_stConfig.m_aszIgnoreOnErrIPs[i], IP_LENGTH-1 ) == 0 )
		{
			return true;
		}
	}

	return false;
}

