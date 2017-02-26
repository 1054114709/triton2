#pragma once
#define MakeSession( object, func, param1, param2 )															\
	CSession< CDBReceiver >( object, (CSession<CDBReceiver>::DataProc) &func, param1, param2 )				\

#include "message_pb.hxx.pb.h"
#include "db_msg_pb.hxx.pb.h"
#include "object.h"
#include "servertool.h"

// sql ִ�к�����ѡ����
enum 
{
	SQL_NONE			= 0,	// �޻�ִ���޷����������ֶ�ֵ
	SQL_NEED_CALLBACK	= 0x01, // ��Ҫ��ִ
	SQL_LATEST_INC_ID	= 0x02, // ��Ҫ�������һ�ε�auto increment id , �������ֶ�
	SQL_REMOTE_HOST		= 0x04,	// ĳЩserver���������󣬱���logserver,��ʾ��ȥԶ��mysqlִ��
};


enum CSessionType
{
	saveplayer = 0,
	loadplayerforlogin,
	mailrecenothing,
	dbmailrece,
	getmailboxinforrece,
	dbmsgrece,
	getmailcountrece,
	addblackcallback,
	commonsqlcallback,
	playeraddfriendcallback,
	loadfriendscallback,
	loadfriendscallback2,
	getmaildetailrece,
	saveplayer_charprofile,
	saveplayer_storage,
	saveplayer_baggage,
	loadplayerforlogin_charprofile,
	loadplayerforlogin_baggage,
	loadplayerforlogin_storage,
	checknewmail,
	saveinvestanswer,
	save_clienthost,
	saveplayer_storagekitbag,		  
	loadplayerforlogin_storagekitbag,	
	ibitemused,
	loadplayerforlogin_baggagekitbag,
	saveplayer_baggagekitbag,	
	em_dbsession_pay_amount,
	loadplayerforlogin_yuanbao,
	freeze_account,
	unfreeze_account,
	updatesilveryb,
	em_dbsession_achieve_save,
	em_dbsession_achieve_query,
	em_dbsession_save_stat,
	em_dbsession_load_stat,
	load_task_global,
	save_task_global,
	checkmailindb,
	em_dbsession_judge_query,
	saveplayer_property_all,
	loadplayer_property_all,
	SESSION_LOAD_PLAYER_BAGGAGE,			// ������ҵ�����Ϣ.����˵��: 0����,1�ֿ�,2װ��
	SESSION_SAVE_PLAYER_BAGGAGE,			// ������ҵ�����Ϣ,����˵����0����,1�ֿ�,2װ��
	session_creatmarriageinfo,				// �����������ݿ���Ϣ
	session_marriage_loadmarriagenum,		// ��ȡ���ݿ��л�����¼������
	session_marriage_loadmarriageinfo,		// ��ȡ���ݿ��л�����¼������	
	session_marriage_loadcampinfo,			// ��ȡ���ݿ�����Ӫ��Ϣ
	session_marriage_loadplayermarriageinfo,// ��ȡ��ҵĻ�����Ϣ
	session_creatcampinfo,					// ������Ӫ����Ϣ	
	session_deletemarriageinfo,				// ������Ӫ����Ϣ
	ssion_updatemarriageid,					// ������ҵĻ���ID	
	ssion_updatemarriageinfo,				// ���»�����Ϣ		 	
	ssion_updatecampinfo,					// ������Ӫ��Ϣ
	bourse_load_by_account,
	bourse_inc_account,
	bourse_dec_account,
	bourse_add_doc_buy,
	bourse_add_doc_sell,
	bourse_dec_doc_buy,
	bourse_dec_doc_sell,
    session_yaoqianshu_loadplayerinfo,    // ��ȡ�û��ɳ����Լ��Ͻ���¶����
    session_yaoqianshu_loadplayerpick,    // ��ȡ�û���ʰȡ��ñ�����Ϣ
    session_yaoqianshu_updateplayerinfo,  // �����û��ɳ����Լ��Ͻ���¶�ĸ���
    session_yaoqianshu_insertplayerpick,  // �����û�ʰȡ������Ϣ
    session_yaoqianshu_loadcampinfo,      // ��ȡҡǮ����Ӫ��Ϣ
    session_yaoqianshu_loadplayerrankinfo,// ��ȡ�û����׶�����
	
	yb_stall_exchange,					// Ԫ����̯����

	SESSION_GETSEQUEST,
	mail_changecamp,					// ת��Ӫ���ʼ�����
	em_dbsession_pay_func,				// ���ܸ�������
	em_dbsession_createswornteam,			// ���������Ϣ
	em_dbsession_getswornteam,			// ��ȡ�����Ϣ
	em_dbsession_updateswornteam,		// ���½����Ϣ
	em_dbsession_updateroleswornid,		// ������ҽ��ID
	em_dbsession_deleteswornteam,		// ɾ����ݵ����ݿ���Ϣ
	em_dbsession_savechatmsg,			// �洢������Ϣ
	em_dbsession_loadchatmsg,			// ��ȡ������Ϣ
	em_dbsession_deletechatmsg,			// ��ȡ������Ϣ
};

// ********************************************************************** //
// CGuidGen
// ********************************************************************** //

class CGuidGen
{
	static int sGuid;
public:
	static int GenID( )
		{ return sGuid ++; }
};

 //********************************************************************** //
 //CDatabaseMessage
 //���ڷ������ݿ���Ϣ����
 //********************************************************************** //

// ********************************************************************** //
// CDBReceiver
// ********************************************************************** //

class CDBReceiver
{
public:
	virtual ~CDBReceiver( ) {	}
};

// ********************************************************************** //
// CSession
// ********************************************************************** //

//template< typename T >
class CSession : public CObj
{
private:

	int			mSessionID;
	int			mParameter1;
	int			mParameter2;
	int			mParam[4];	// �����Դ��룺��������
	int			mSessionType;
	CWTimer		mTimer;


public:

	CSession()
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	}

	~CSession() {}

	int Initialize()
	{
		mSessionID = 0;
		return 0;
	}

	int Resume() {return 0;}


	void assign(int session_id, int session_type, int param1, int param2, int timeout = 10000)
	{
		mSessionID = session_id;
		mSessionType = session_type;
		mParameter1 = param1;
		mParameter2 = param2;
		memset( mParam, 0, sizeof(mParam) );
		mTimer = CWTimer( timeout ); 
	}

	void Fire( CMessage* pMessage, int vParameter1, int vParameter2 )
	{
	}


	// get & set
	inline void SetParam1( int nPara ) { mParameter1 = nPara; }
	inline int GetParam1( ) { return mParameter1; }

	inline void SetParam2( int nPara ) { mParameter2 = nPara; }
	inline int GetParam2( ) { return mParameter2; }
	
	inline void SetParam3( int nPara ) { mParam[0] = nPara; }
	inline int GetParam3( ) { return mParam[0]; }

	inline void SetParam4( int nPara ) { mParam[1] = nPara; }
	inline int GetParam4( ) { return mParam[1]; }

	inline void SetParam5( int nPara ) { mParam[2] = nPara; }
	inline int GetParam5( ) { return mParam[2]; }

	// ���Ǽ��ݽӿڣ��Ⱥ�����ͳһ�ˡ�
	// index��1��ʼ
	inline void SetParam( int nIdx, int nParam ) 
	{
		switch( nIdx )
		{
		case 1:
			{
				SetParam1( nParam );
				break;
			}
		case 2:
			{
				SetParam2( nParam );
				break;
			}
		case 3:
			{
				SetParam3( nParam );
				break;
			}
		case 4:
			{
				SetParam4( nParam );
				break;
			}
		case 5:
			{
				SetParam4( nParam );
				break;			
			}
		default:
			{
				break;
			}
		}
	}

	inline int GetParam( int nIdx, int nParam )
	{
		switch( nIdx )
		{
		case 1:
			{
				return GetParam1( );
				break;
			}
		case 2:
			{
				return GetParam2(  );
				break;
			}
		case 3:
			{
				return GetParam3(  );
				break;
			}
		case 4:
			{
				return GetParam4(  );
				break;
			}
		case 5:
			{
				return GetParam4(  );
				break;
			}
		default:
			{
				break;
			}
		}
	}



	inline void SetSessionType( int nType ) { mSessionType = nType; }
	inline int GetSessionType( ) { return mSessionType; }
	
	inline void SetTimer( CWTimer rTimer ) { mTimer = rTimer; }
	inline CWTimer& GetTimer( ) { return mTimer; }
};

// ********************************************************************** //
// CSessionDispatch
// ********************************************************************** //
//
//class CSessionDispatch
//{
//public:
//	lk::hash_map< int, CSession >			mSessions;
//
//public:
//	void Elapse( int vTickOffset )
//	{
//		//map< int, CSession< CDBReceiver > >::iterator tBeginIter = mSessions.begin( );
//		//map< int, CSession< CDBReceiver > >::iterator tEndIter = mSessions.end( );
//		//for ( ; tBeginIter != tEndIter; tBeginIter ++ )
//		//{
//		//	// �����ʱ����֪ͨ�߼����ݿⳬʱ
//		//	if ( tBeginIter->second.mTimer.Elapse( vTickOffset ) == true )
//		//	{
//		//		CMessageExecuteSqlResponse* tpResponse = (CMessageExecuteSqlResponse*) CMessageExecuteSqlResponse::CreateMessage( 
//		//			tBeginIter->second.mSessionID );
//		//		tBeginIter->second.Fire( tpResponse, tBeginIter->second.mParameter1, tBeginIter->second.mParameter2 );
//		//		mSessions.erase( tBeginIter );
//		//		return;
//		//	}
//		//}
//	}
//
//	void Register( CSession& rSession )
//	{
//		mSessions.insert( std::pair< int, CSession >( rSession.mSessionID, rSession ) );
//	}
//
//	void OnMessage( CMessage* pMessage )
//	{
//		CMessageExecuteSqlResponse3* tpExecuteSql = (CMessageExecuteSqlResponse3*)pMessage->msgpara();
//
//		map< int, CSession >::iterator tFindIter = mSessions.find( tpExecuteSql->sessionid() );
//		if ( tFindIter == mSessions.end( ) )
//			return;
//
//		tFindIter->second.Fire( pMessage, tFindIter->second.mParameter1, tFindIter->second.mParameter2 );
//		mSessions.erase( tFindIter );
//
//	}
//};
