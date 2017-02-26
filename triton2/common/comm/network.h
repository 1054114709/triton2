#pragma once
#include "message_pb.hxx.pb.h"

typedef unsigned char BYTE;
#define MAX_PACKAGE_LEN 45000 // �������Ϳͻ��˼���������

// ********************************************************************** //
// CStatistics
// ********************************************************************** //

class CStatistics
{
public:
	int		mBytesSent;			// �ܷ����ֽ���
	int		mBytesRecv;			// �ܽ����ֽ���
	int		mPackagesSent;		// �ܷ��Ͱ���
	int		mPackagesRecv;		// �ܽ��հ���
	int		mBytesSentAvg;		// ÿ�뷢���ֽ���
	int		mBytesRecvAvg;		// ÿ������ֽ���
	int		mPackagesSentAvg;	// ÿ�뷢�Ͱ���
	int		mPackagesRecvAvg;	// ÿ����հ���
	int		mPingInterval;		// pingֵ
};
//
//// ********************************************************************** //
//// CMessage
//// ********************************************************************** //
//
//class CMessage
//{
//public:
//
//	// ��Ϣʵ��
//	enum enMessageFE
//	{
//		FE_CLIENT = 0,		// �ͻ���
//		FE_SCENCESERVER,	// ����������
//		FE_LOGINSERVER,		// ��½������
//		FE_INFOSERVER,		// ��Ϣ������
//		FE_GATESERVER,		// ���ط�����
//		FE_DATASERVER,		// ���ݷ�����
//		FE_ROUTERSERER,		// ·�з�����
//	};
//
//	// ��Ϣ����
//	enum enMessageType
//	{
//		REQUEST = 0,		// ����
//		RESPONSE,			// �ظ�
//		NOTIFY,				// ֪ͨ
//		ACK,				// Ӧ��
//	};
//
//public:
//	unsigned short	mMessageSize;
//	unsigned short	mMessageID;
//	unsigned int	mCheckSum;
//
//	int				mMsgSeq;	// ��Ϣ���к�
//	short			mMsgType;	// ��Ϣ����
//	char			mSrcFE;		// ��ϢԴʵ��
//	char			mDstFE;		// ��ϢĿ��ʵ��
//	int				mSrcID;		// ��ϢԴID
//	int				mDstID;		// ��ϢĿ��ID
//
//public:
//	
//	virtual int Encode();
//	virtual int Decode();
//	virtual int Print();
//
//public:
//	CMessage( unsigned short vMessageSize, unsigned short vMessageID, short vMsgType = REQUEST, int vMsgSeq = 0, char vSrcFE = FE_CLIENT, char vDstFE = FE_SCENCESERVER )
//		: mMessageSize( vMessageSize ), mMessageID( vMessageID ), mCheckSum( BuildCheckSum( ) ), mMsgType( vMsgType ), mMsgSeq( vMsgSeq ), mSrcFE( vSrcFE ), mDstFE( vDstFE ) { }
//
//	unsigned int BuildCheckSum( )
//		{ return mCheckSum = ~( ( (unsigned int) mMessageSize << 16 ) | (unsigned int) mMessageID ); }
//
//	void SetMessageSize( unsigned short vMessageSize )
//		{ mMessageSize = vMessageSize; mCheckSum = BuildCheckSum( ); }
//
//	void SetMessageID( unsigned short vMessageID )
//		{ mMessageID = vMessageID; mCheckSum = BuildCheckSum( ); }
//
//	bool CheckHeader( )
//		{ return mCheckSum == BuildCheckSum( ); }
//
//};
//
//// ********************************************************************** //
//// CCSHead:��Ҫ�ǿͻ��˵����������������Ϣ��, �����㷨, Э��汾��, �Լ���������Э����
//// ********************************************************************** //
//#define MAXOPTLENGTH		127			//C/SЭ���ѡ���ֵ���󳤶�
//#define CSHEADBASELENGTH	18			//C/SЭ��ͷ���Ļ�����С
//
//class CCSHead
//{
//public:
//	short				mTotalLength;
//	short				mVer;
//	int					mDialogID;	// ��������ͻ��˵ĻỰID
//	int					mSeq;
//	unsigned int		mUin;
//	unsigned char		mBodyFlag;
//	unsigned char		mOptLength;
//	unsigned char		mOption[MAXOPTLENGTH];
//
//public:
//	CCSHead() : mTotalLength( 0 ), mVer( 0 ), mDialogID( 0 ), mSeq( 0 ), mUin( 0 ), mBodyFlag( 0 ), mOptLength( 0 ) {}
//	~CCSHead() {}
//}; 


// ********************************************************************** //
// CLockObject
// ********************************************************************** //

class CLockObject
{
public:
	virtual ~CLockObject( )
	{
	}

public:
	virtual void Lock( )	= 0;
	virtual void Unlock( )	= 0;
};

// ********************************************************************** //
// CClientNetwork
// ********************************************************************** //

class CClientNetwork
{
public:
	typedef void ( *OnConnectProc )( int vCode, int vUserData );
	typedef void ( *OnMessageProc )( BYTE* pMessage, int vMsgLen, int vUserData );
	typedef void ( *OnCloseProc )( int vCode, int vUserData );

public:
	OnConnectProc	mpConnectProc;
	OnMessageProc	mpMessageProc;
	OnCloseProc		mpCloseProc;

public:
	CClientNetwork( OnConnectProc pConnect, OnMessageProc pMessage, OnCloseProc pClose ) : mpConnectProc( pConnect ), mpMessageProc( pMessage ), mpCloseProc( pClose )
	{
	}
	CClientNetwork()
	{
	}

public:
	void Init(OnConnectProc pConnect, OnMessageProc pMessage, OnCloseProc pClose )
	{
		mpConnectProc = pConnect;
		mpMessageProc = pMessage;
		mpCloseProc = pClose;
	}
	void FireConnect( int vCode, int vUserData )
	{
		if ( mpConnectProc != 0 )
			(*mpConnectProc)( vCode, vUserData );
	}

	void FireMessage( BYTE* pMessage, int vMsgLen, int vUserData )
	{
		if ( mpMessageProc != 0 )
			(*mpMessageProc)( pMessage, vMsgLen, vUserData );
	}

	void FireClose( int vCode, int vUserData )
	{
		if ( mpCloseProc != 0 )
			(*mpCloseProc)( vCode, vUserData );
	}

public:
	virtual void SetUserData( int vUserData )				= 0;
	virtual void EnumEvent( )								= 0;
	virtual bool Create( const char* pAddress )				= 0;
	virtual void Shutdown( )								= 0;
	virtual void SendMsg( BYTE* pMessage, int vMsgLen )				= 0;
	virtual void GetStatistics( CStatistics* pStatistics )	= 0;
};

// ********************************************************************** //
// CServerNetwork
// ********************************************************************** //

class CServerNetwork
{
public:
	typedef void ( *OnAcceptProc )( int vCommHandle );
	typedef void ( *OnMessageProc )( int vCommHandle, BYTE* pMessage, int vMsgLen );
	typedef void ( *OnCloseProc )( int vCommHandle );
	typedef void ( *OnTimerProc )( unsigned int vTickCount );

public:
	OnAcceptProc	mpAcceptProc;
	OnMessageProc	mpMessageProc;
	OnCloseProc		mpCloseProc;
	OnTimerProc		mpTimerProc;
	CLockObject*	mpLock;
public:
	CServerNetwork( OnAcceptProc pAccept, OnMessageProc pMessage, OnCloseProc pClose, OnTimerProc pTimer, CLockObject* pLock ) : 
	  mpAcceptProc( pAccept ), mpMessageProc( pMessage ), mpCloseProc( pClose ), mpTimerProc( pTimer ), mpLock( pLock )
	{
	}

public:
	virtual ~CServerNetwork( )
	{
	}

public:
	void FireAccept( int vCommHandle )
	{
		if ( mpAcceptProc != 0 )
			(*mpAcceptProc)( vCommHandle );
	}

	void FireMessage( int vCommHandle, BYTE* pMessage, int vMsgLen )
	{
		if ( mpMessageProc != 0 )
			(*mpMessageProc)( vCommHandle, pMessage, vMsgLen);
	}

	void FireClose( int vCommHandle )
	{
		if ( mpCloseProc != 0 )
			(*mpCloseProc)( vCommHandle );
	}

	void FireTimer( unsigned long vTickCount )
	{
		if ( mpTimerProc != 0 )
			(*mpTimerProc)( vTickCount );
	}

public:
	virtual char* GetRemoteIPString( int vCommHandle )					= 0;
	virtual unsigned short GetRemotePort( int vCommHandle )				= 0;
	virtual bool Create( const char* pAddress )							= 0;
	virtual void Shutdown( )											= 0;
	virtual void SendMsg( int vCommHandle, BYTE* pMessage, int vMsgLen )	= 0;
	virtual void SetKeepAlive( int vCommHandle, unsigned int vTime )	= 0;
	virtual void GetStatistics( int vCommHandle, CStatistics* pStatistics ) = 0;

public:
	void Lock( )	{ mpLock->Lock( );	}
	void Unlock( )	{ mpLock->Unlock( );}
};
