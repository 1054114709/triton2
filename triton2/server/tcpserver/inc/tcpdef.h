/******************************************************************************
	��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

/******************************************************************************
	�ļ���          : tcpdef.h
	�汾��          : 1.0
	����            : �ź���
	��������        : 2008-05-28
	����޸�        : 
	��������        : Tcp����������궨���ļ�
	�����б�        : 
	�޸���ʷ        : 
	1 ����          : 2008-05-28
	  ����          : �ź���
	  �޸�����      : ����
*******************************************************************************/

#ifndef __TCPDEF_H__
#define __TCPDEF_H__

#include <time.h>
#include <string.h>


#ifdef SMALL_SIZE
#define MAX_SOCKET_NUM				200				/*����TCPCtrl֧�ֵ�������*/
#endif

#ifdef MEDIUM_SIZE
#define MAX_SOCKET_NUM				3300				/*����TCPCtrl֧�ֵ�������*/
#endif

#ifdef LARGE_SIZE
#define MAX_SOCKET_NUM				13500				/*����TCPCtrl֧�ֵ�������*/
#endif


#define MAX_PORT_NUM				3					/*���˿���*/
#define MAX_IGNORE_ON_ERR_IP		3					/*����socket����ʱ�����Բ�д��־��IP��*/

#define CSHEAD_BASE_LEN				18					/*C/SЭ��ͷ���Ļ�����С*/
#define CSHEAD_OPT_LEN				127					/*C/SЭ���ѡ���ֵ���󳤶�*/

#define LISTEN_SOCKET				1					/*����socket*/ 
#define CONNECT_SOCKET				2					/*����socket*/

#define RECV_DATA					1					/*��־socketҪ��������*/
#define SEND_DATA					2					/*��־socketҪ��������*/

#define IP_LENGTH					20					/*IP��ַ����*/

#define SERVER_INIT_DAEMON			1					/*�����Ժ�̨�ķ�ʽ����*/
#define MAX_BUF_LEN                 (100*1024)			/*���������͸��ͻ��˵���������󳤶�*/ 
#define RECV_BUF_LEN				(8 * 1024)			/*���տͻ�����Ϣ�Ļ�����*/ 
#define PIPE_SIZE					((int)0x1000000)	/*�ڴ�ܵ��Ĵ�С*/
#define MAX_SEND_PKGS_ONCE			1000				/*һ�δ��ڴ�ܵ���ȡ���������ݰ�*/


#define MAIN_HAVE_SEND_DATA			1					/*��������������͹����ݸ�ĳSocket*/


enum ENSocketCloseSrcEn
{
	CLOSESOCKET_PLAYER			=	1,					/*�ͻ��������������*/
	CLOSESOCKET_MAINSERVER		=	2,					/*��̨���������������*/
};


#define CONFIG_FILE					"../config/tcpsvrd.cfg"
#define LOG_FILE					"../log/tcpsvrd"
#define MAX_PATH                    260                       /*�ļ������·����*/
#define INVALID_SOCKET              -1                        /*��Чsocket���*/
#define SOCKET_ERROR                -1                        /*socket api�ķ���ֵ*/
#define INVALID_HANDLE_VALUE        ((void * )(-1))           /*��Ч���ֵ*/
#define closesocket(fd)              shutdown(fd,2); close(fd);                     /*�ر�socket*/

#define ERRPACKETLENGTH				-2

#define RcMutex                     pthread_mutex_t           /*�߳���*/  
#define ThreadType                  void*                     /*�߳�����*/ 
typedef void                        *(*ThreadFunc )(void *);  /*�̺߳���ָ��*/


typedef int							LONG;
typedef unsigned int				ULONG;
typedef short						SHORT;
typedef unsigned short				USHORT;
typedef	unsigned char				BYTE;
typedef int                         SOCKET;


typedef enum _EnRunFlag
{
	reloadcfg = 1,
	tcpexit
}EnRunFlag;


/*Socket ���Ӵ�����*/
typedef enum _EnSocketStatus
{
	Client_Succeed			= 0,	/*�ͻ�����������*/
	Err_ClientClose			= -1,	/*�ͻ��˹ر�*/ 
	Err_ClientTimeout		= -2,	/*�ͻ��˳�ʱ*/
	Err_PacketError			= -3,	/*�ͻ��˷��͵İ�����*/ 
	Err_TCPBuffOver			= -4,	/*TCP����������*/ 
	Err_SendToMainSvrd		= -5,	/*���ݰ������ڴ�ܵ�ʧ��*/
	Err_System				= -6	/*ϵͳ������ʱδ��*/
}EnSocketStatus;



/*���巵�ؽ��*/
typedef enum _EnResult
{    
	TCP_SUCCESS = 0,                        /*�ɹ�*/            
	TCP_FAILED,                             /*ʧ��*/     
	TCP_CONTINUERECV,                       /*��Ϣ��δ������ϼ�������*/
	TCP_LENGTHERROR,                        /*���յ���Ϣ���Ⱥͱ�ʵ�ĳ��Ȳ�һ��*/    
}EnResult; 


/*��ǰʱ��*/
typedef struct _TTime
{
	ULONG		ulYear;			/*0000-9999*/
	ULONG		ulMonth;		/*00-12*/
	ULONG		ulDay;			/*01-31*/
	ULONG		ulHour;			/*00-23*/
	ULONG		ulMinute;		/*00-59*/
	ULONG		ulSecond;		/*00-59*/
}TTime;


/*�����������Ϣ*/
typedef struct _TConfig 
{
	int          m_iSocketTimeOut;						/*socket�ĳ�ʱʱ��*/
	int          m_iConnTimeOut;						/*socket�ĳ�ʱʱ��*/
	int          m_iCheckTimeGap;
	int          m_iListenPortNum;						/*����˿���Ϣ*/    
	int          m_iListenPorts[MAX_PORT_NUM];			/*����˿���Ϣ*/    
	int          m_iTcpBufLen;							/*tcp���ͻ�������С*/
	int          m_iMaxLogCount;			
	int          m_iWriteStatGap;						/*log������״̬�ļ��*/
	int          m_iShmMax;								/*�����ڴ������(size)*/
	int          m_iOpenFileMax;						/*�ļ���������*/
	int          m_iCoreFileSize;						/*core�ļ���С*/
	int			 m_iIgnoreOnErrIPNum;					/*����socket����ʱ���Բ�д��־��IP��IP���� */
	char		 m_aszIgnoreOnErrIPs[MAX_IGNORE_ON_ERR_IP][32]; /* IP��ַ */
}TConfig;


/*�ýṹ�Ǻ�mainserverͨѶ�õ�*/ 
typedef struct CNetHead
{ 
	enum { MAX_DEST_ENTITY = 1000 };

	ULONG	m_iSrcIP;					/*��tcpsvrd����mainserver����¼�˸�socket�Ĵ���ʱ��*/
	USHORT	m_nSrcPort;					/*��tcpsvrd����mainserver����¼�˸�socket�������е�λ��*/
	ULONG	m_iDstIP;				/*��mainserver���ظ�tcpsvrd��ֵ��m_iSrcIP��ͬ*/ 
	USHORT	m_nDstPort;				/*��mainserver���ظ�tcpsvrd��ֵ��m_iSrcPort*/
	time_t	m_tStamp;				/*���յ����ݰ���ʱ���*/
	char	m_cState;				/*״̬�� < 0 ˵���ر���socket*/

	CNetHead( ) : m_iSrcIP(0), m_nSrcPort(0), m_iDstIP(0), m_nDstPort(0),  m_tStamp(0), m_cState(0) {}
	~CNetHead() {}

}TNetHead;


#define TNetHeadSize     sizeof(TNetHead)   /*TNetHead��С*/


/*�Ϳͻ���ͨѶ��socket�ṹ*/
typedef struct _TSocketInfo
{
	SOCKET  m_iSocket;						/*socket���*/
	int     m_iSocketType;					/*socket���ͣ�����socket������socket*/
	int     m_iSocketFlag;					/*socket��־���Ƿ��հ�*/
	int     m_iRecvBytes;                   /*���յ��ֽ���*/
	char    m_szClientIP[IP_LENGTH];		/*�ͻ���IP��ַ*/
	char    m_szMsgBuf[RECV_BUF_LEN];		/*�洢���͸�gamesvrd����Ϣ*/
	time_t  m_tCreateTime;					/*socket�Ĵ���ʱ��*/
	ULONG   m_iSrcIP;						/*��tcpsvrd����gamesvrd����¼�˸�socket�Ĵ���ʱ��*/
	ULONG   m_iDstIP;						/*��gamesvrd���ظ�tcpsvrd��ֵ��m_iSrcIP��ͬ*/ 
	USHORT  m_nSrcPort;						/*��tcpsvrd����gamesvrd����¼�˸�socket�������е�λ��*/
	USHORT  m_nDstPort;						/*��gamesvrd���ظ�tcpsvrd��ֵ��m_iSrcPort*/
	time_t  m_tStamp;						/*���յ����ݰ���ʱ���*/
	int     m_iSendFlag;					/*��ʶmainsvrd�Ƿ����䷢���˰�*/
	int     m_iConnectedPort;
	int		m_iUin;							/*�û�Ψһ��ʶ*/
} TSocketInfo;

#endif // __TCPDEF_H__
