#pragma once
#include "dungeontype.h"
#include "servertool.h"
#include "lk_hashmap.h"
#include "lk_assert.h"
#include "lk_vector.h"
#include "object.h"
// ������Ϣ
struct CRoleInfo
{
public:
	enum ERoleStatus
	{
		ESTATUS_NORMAL	= 0,	// ����
		ESTATUS_OFFLINE = 1,	// ����״̬,׼���߳�
		ESTATUS_WAIT    = 2,	// �ȴ����븱��״̬,׼���߳�
	};
public:
	int mRoleID;
	int mGameID;
	int mTeamFlag;		
	int mRoleStatus;
	int mOffTime;				// ���ߵ�ʱ��
public:
	int Initialize()
	{
		mRoleID = 0;
		mGameID = 0;
		mTeamFlag = 0;
		mRoleStatus = ESTATUS_NORMAL;
		mOffTime =0;
	}
public:
	CRoleInfo()
	{
		Initialize();
	}
};

// ս��ע����Ϣ
class CWarRegInfo : public CObj
{
public:
	CRoleInfo mRoleInfo[MAX_WAR_PLAYER_NUM];// �����Ľ�ɫID	
	KEY_TYPE mReptionKey;					// ����key
	int mRoleNum;							// �����е�����
	int mLevelID;							// ���ݵȼ����ڵĵȼ�ID
	int mCreateTime;						// ע����Ϣ�Ĵ���ʱ��
	int mServerKey;							// ���䵽������ID(����ID��ȡ������Ϣ)
	int mRegKey;							// ע���key
	int mStatus;							// ״̬	
	int mServerListID;						// ����������ID
public:
	enum EWarStatus
	{
		EWARSTATUS_INITIAL			= 0,	//	��ʼ״̬
		EWARSTATUS_CREATEREPTION	= 1,	// ��������״̬
		EWARSTATUS_START			= 2,	// ս����ʼ�׶�
		EWARSTATUS_BATTLEEND		= 3,	// ս��������ս���رյ���ʱ�׶�
	};
public:
	CWarRegInfo()
	{
		if ( CObj::msCreateMode )
		{
			Initialize();
		}
		else
		{
			
		}
	}
public:
	int Initialize()
	{
		memset( mRoleInfo, 0, sizeof( mRoleInfo ) );
		mRoleNum = 0;
		mReptionKey = 0;
		mLevelID = 0;
		mCreateTime = 0;
		mServerKey = 0;
		mRegKey = 0;
		mStatus = EWARSTATUS_INITIAL;
		mServerListID = 0;
		return 0;
	}
	int Resume(){ return 0; }
public:
	enum ETeamFlag
	{
		ETEAMFLAG_ONE = 1,	// ����1
		ETEAMFLAG_TWO = 2,	// ����2
	};
public:
	bool IsRepetionStart(){ return mReptionKey > 0; }
	void ClearReption(){ Initialize(); }
	bool IsFull( int nStartNum ){  return mRoleNum >= ARRAY_CNT( mRoleInfo ) || mRoleNum >= nStartNum; } 
	int InsertRole( CRoleInfo &rRoleInfo ); 	
	CRoleInfo *GetRoleInfo( int nRoleID );		
	int DeleteRoleInfo( int nRoleID );
	int AssignTeam( int nStartNum );	// �Ѷ����Զ��ֳ�����,ս����ʼ��ʱ�����(����1/2 WAR_START_NUM)
	int GetTeamNum( ETeamFlag eFlag, int nStarNum ); // ��ȡĳһ�ֶӵ�����
	ETeamFlag GetTeamFlag( int nStartNum );	// ����������ȡ��ӱ�ʶ
	bool HasRole( int nRoleID );			// �ж�ע����Ϣ���Ƿ��иý�ɫ	
	int ChangeRoleStatus( int nRoleID, int nStatus );	// �ı����״̬
	void RemoveTimeOutRole( int nMaxOfflineTime, int nMaxWaitTime,std::vector<int> &rRoleIDList );	// ɾ������ʱ�䳬���������ʱ���ս�����		
	bool InProtecTime( int nProtectTime );		// ����Ƿ��ڸ�������ʱ����
}; 

// ս����Ϣ����
enum EWarRegStatus
{
	EWARREG_STATUS_READY = 0,	// ׼���׶�
	EWARREG_STATUS_START = 1,	// ս���Ѿ���ʼ	
};


struct CWaitPlayer  
{
public:
	int mLevelID;
	int mRoleID;
	int mGameID;
public:
	CWaitPlayer()
	{
		mLevelID = 0;
		mRoleID = 0;
		mGameID = 0;
	}
};

// ս����Ϣ(ÿ��ȫ�ָ���һ��manager)
class CWarRegInfoManager
{	
public:
	enum 
	{
		EMANAGER_STATUS_UNUSED = 0,	// δ��ʹ��״̬
		EMANAGER_STATUS_USED = 1,	// ��ʹ��״̬
	};
public:
	CWarRegInfoManager()
	{
		if ( CObj::msCreateMode )
		{
			Initialize();
		}
		else
		{
			Resume();
		}
	}
	~CWarRegInfoManager(){ }
public:

	// ÿ���ȴ���������һ��ʱ��������ʱ��Ϊ���ʱ��
	class WaitPlayer : public lk::vector< CWaitPlayer, MAX_PLAYER_INLIST >
	{
	private:
		int mCreateTime;					
	public:
		bool TimeOut( int nMaxTime )
		{
			return time( NULL ) - mCreateTime > nMaxTime;
		}
		int GetCreateTime(){ return mCreateTime; }
		void SetCreateTime( int nTime ){ mCreateTime = nTime; }		
		void GetRoleIDList( std::vector<int> &rRoleIDList )
		{			
			for ( iterator it = begin(); it != end(); ++it )
			{
				rRoleIDList.push_back( it->mRoleID );
			}
		}
	public: 
		WaitPlayer()
		{
			mCreateTime = time(NULL);			
		}
	};	
public:	
	typedef lk::vector< int, MAX_WARREGINFO_INLIST > WarRegInfoList;
public:	
	typedef lk::hash_map< int, WaitPlayer, MAX_LEVLESECTION_NUM > WaitPlayerSet;	 // ÿ���ȼ��εĵȼ��б�	
	typedef lk::hash_map< int, WarRegInfoList, MAX_LEVLESECTION_NUM > WarRegInfoSet; // ÿ���ȼ��ο�����ս��
	typedef lk::vector< int, MAX_WARNUM_CANSTART > WarEnableList;					  // �������������Կ�����ս����Ϣ�б�
public:
	int Initialize();		// ��ʼ��	
	int Resume(){ return 0; }	
	CWarRegInfo* FindWarRegInfoWithoutFull( int nLevelID ); // ��ȡĳ����������δ����ս��ע����Ϣ
	int RegRoleInfo( CRoleInfo &rRoleInfo, int &rRegKey, int nLevelID );	// ע��ĳ����ɫ��Ϣ��ս��
	CWarRegInfo *GetWarRegInfo( EWarRegStatus eStatus, int nLevelID );	// ��ȡĳ���ȼ��ε�ս����Ϣ	
	CWarRegInfo *CreateWarRegInfo(  );									// ����һ��ս����ע����Ϣ
	int DeleteWarRegInfo( int nRegKey );								// ע�����Ѿ�������ս����Ϣ
	CWarRegInfo *GetWarRegInfoByRoleID( int nRoleID );					// ��ȡĳ����ɫ��ս��ע����Ϣ
	CWarRegInfo *GetWarRegInfoByKey( KEY_TYPE nRepetionKey );			// ���ݸ�����key��ȡս��ע����Ϣ
	CWarRegInfo *GetWarRegInfoByRegKey( int nKey );						// ����ע���keyֵ��ȡע����Ϣ
	int FetchRoleIntoWarFromWaitlist( CRoleInfo *pRoleInfo, int *pWarRegKey, int &rNum ); // �ѽ�ɫ�ӵȴ������ƶ���ս��
	int CheckWarRegInfo( int nWarTimeInterval );		// ����Ƿ��п��Կ�����ս��
	CWarRegInfo *DeleteRoleWarRegInfo( int nRoleID );					// ɾ��ĳ����ɫ��ע����Ϣ
	bool CheckApply( int nRoleID );										// ����ɫ�Ƿ��Ѿ�����
	bool InWaritList( int nRoleID );									// �Ƿ��ڵȴ��б�����		
	bool DeleteFromWaitList( int nRoleID );								// �Ӷ�����ɾ��ĳ����ҵı�����Ϣ
	int InsertWaitPlayer2List( CWaitPlayer &rPlayer );	// ����һ����ɫ��Ϣ���б���
	int InsertWarRegInfo2List( CWarRegInfo *pWarRegInfo );	// ����һ����ɫ��Ϣ���б���
	int GetWarNumOfCertainLevel( int nLevelID );						// ��ȡĳ���ȼ��ο�����ս����Ŀ	
	WarRegInfoList* GetWarRegInfoListByLevelID( int nLevelID );		// ��ȡĳ���ȼ��ε�ս����Ϣ����
	WaitPlayer* GetWaitPlayerListByLevelID( int nLevelID );		// ��ȡĳ���ȼ��εĵȴ�������Ϣ			
	int DeleteWarRegInfoListByLevelID( int nLevelID );					// ���ݵȼ�IDɾ��һ��ս������
	int DeleteWaitPlayerListByLevelID( int nLevelID );					// ���ݵȼ�IDɾ��һ���ȴ�����
	int EraseWarInfoFromList( WarRegInfoList &rList, int nWarRegInfoID ); // ���ĳ��ս����ע����Ϣ
	bool InWaitList( WaitPlayer &rList, int nRoleID );					 // 
	bool InWaitList( int nRoleID );					 // ����б����Ƿ���ĳ����ɫ��Ϣ
	int RemoveTimeOutRole( int nMaxOfflineTime, int nMaxWaitTime, std::vector<int> &rRoleIDList );		 // ɾ����ʱ�����
	void DeleteValidWarRegInfo( int nMaxWarAliveTime, int nProtectTime, std::vector<int> &rDeleteWarInfo ); // ɾ�����ڵĻʱ��
	void DeleteTimeOutWaitList( int nMaxTime, std::vector<int> &rRoleIDList );
	bool IsManagerFree();							// �жϹ������Ƿ����������ʹ��
public:
	void SetLastWarStartTime( int nTime ){ mLastWarStartTime = nTime; }
	int GetLastWarStartTime(){ return mLastWarStartTime; }	
	void SetWarStartNum( int nNum ){ mWarStartNum = nNum; }				// ���ÿ���ս����Ҫ������
	int GetWarStartNum(){ return mWarStartNum; }						// ���ÿ���ս����Ҫ������	
	WarEnableList& GetWarEnableList(){ return mWarEnableList; }			// ��ȡ���Կ�����ս���б�
	void SetWarManagerStatus( int nStatus ) { mWarManagerStatus = nStatus; } // ����ս����������״̬
	int GetWarManagerStatus(){ return mWarManagerStatus; }				// ��ȡս����������״̬
	void SetRepetionIndex( int nIndex ){ mRepetionIndex = nIndex; }		// ���ø�������
	int GetRepetionIndex(){ return mRepetionIndex; }					// ��ȡ��������
	void SetServerListID( int nID ){ mServerListID = nID; }				// ���÷������б�ID
	int GetServerListID(){ return mServerListID; }						// ��ȡ�������б�ID
private:	
	int mRepetionIndex;						// ��������
	int mServerListID;						// �������б�ID
	int mWarStartNum;	
	int mLastWarStartTime;					// ���һ��ս���Ŀ���ʱ��
	int mWarManagerStatus;					// 
	WaitPlayerSet mWaitPlayerSet;			// �ȴ������е����				
	WarRegInfoSet mWarRegInfoSet;			// ս��ע����Ϣ
	WarEnableList mWarEnableList;			// �������������Կ�����ս����Ϣ�б�
};

// ���ڽ���������ÿ������������Ϣ
struct CMapInfo  
{
public:
	int mMapID;
	int mPosX;
	int mPosY;
public:
	CMapInfo()
	{
		mMapID = 0;
		mPosX = 0;
		mPosY = 0;
	}	
};
struct CGlobalServerInfo
{
public:
	int mServerType;	// ����������
	int mWorldID;		// ����������Ϸid
	int mLineID;		// ���������serverid
						// ����

	CMapInfo mGlobalMapInfo;	// Ҫ�����ȫ�ַ������ĵ�ͼ��Ϣ
	CMapInfo mOriginalMapInfo;	// ԭʼ�������ĵ�ͼ��Ϣ
	lk::CString64 mAddr;// ��������ַ
	int mReptionIndex;	//��������
public:
	CGlobalServerInfo()
	{
		mServerType = 0;
		mWorldID = 0;
		mLineID = 1;		
		mAddr.clear();
		mReptionIndex = 0;
	}
};
struct CGameConfig
{
public:
	int mServerListID;
};

class CGlobalServerConfig
{
public:
	typedef lk::hash_map< int, CGlobalServerInfo, MAX_GLOBALSERVER_NUM > GlobalServerInfolist;
	typedef lk::hash_map< int, CGameConfig, MAX_GAMECONFIG_NUM > GameConfigList;
public:
	CGlobalServerConfig()
	{
		if ( CObj::msCreateMode )
		{
			Initialize();
		}
		else
		{
			Resume();
		}
	}
	~CGlobalServerConfig(){}
	int Initialize();
	int Resume(){ return 0; }
	int InitializeServerList();
	int InitializeGameConfig();
public:
	int InsertGlobalServerInfo( int nServerListID, int nKey, CGlobalServerInfo &rServerInfo );
	CGlobalServerInfo *GetGlobalServerInfo( int nKey, int &rServerListID );
	
	// ������������Ϣ
	int InsertGameConfig( int nWorldID, CGameConfig &rConfig );
	CGameConfig *GetGameConfig( int nWorldID );	
	int SetWarStartNum( int nServerListID, int nNum );
	int GetWarStartNum( int nServerListID );
public:
	GlobalServerInfolist mGlobalServerInfoList[MAX_GLOBAL_SERVERLIST_NUM];
	int mWarStartNum[MAX_GLOBAL_SERVERLIST_NUM];
	GameConfigList mGameConfigList;
};

// ����ÿ���������ĸ������
struct CServerStatus
{
public:	
	int mRoleNum;			// �ڳ����е�����
	int mWarNum;			// ����ս������		
};
class CServerManager
{
public:
	typedef lk::hash_map< int, CServerStatus, MAX_GLOBALSERVER_NUM > ServerStatusList;
public:
	CServerManager()
	{
		if ( CObj::msCreateMode )
		{
			Initialize();
		}
		else
		{
			Resume();
		}
	}
	~CServerManager(){ }
	int Initialize();
	int Resume(){ return 0; }
public:
	enum ESlectType
	{
		ESELECT_TYPE_BYWARNUM = 0,
		ESELECT_TYPE_BYROLENUM = 1,
	};	
public:
	int SelectServerWithMinNum( int nServerListID, EServerType eServerType, ESlectType eType, CGlobalServerConfig &rConfig, int nRepetionIndex = 0 );
	int ChangeServerSatus( int nServerListID, int &rKey, int nRoleNum, int nWarNum, CGlobalServerConfig &rConfig, ESlectType eSelectType = ESELECT_TYPE_BYWARNUM, EServerType eServerType = ESERVERTYPE_DUNGEON );
	CServerStatus *GetServerStatus( int nKey );
public:
	ServerStatusList mServerStatusList;
};

// �ȼ��ε�����
struct CLevelSection
{
public:
	int mMinLevel;	 
	int mLevelID;
	int mMaxWarNum;	// ����ͬʱ���������ս����Ŀ
public:
	CLevelSection()
	{		
		mMinLevel = 0;
		mLevelID = 0;
		mMaxWarNum = 20;
	}
};

class CLevelConfig
{
public:
	CLevelConfig()
	{
		if ( CObj::msCreateMode )
		{
			Initialize();
		}
		else
		{
			Resume();
		}
	}
	~CLevelConfig(){} 
public:
	int Initialize();
	int Resume(){ return 0; }
	void SetMaxLevel( int nLevel ) { mMaxLevel = nLevel; }
	int GetMaxLevel(){ return mMaxLevel; }
	int InsertLevelSection( CLevelSection &rLevelSection );
	int GetIDByLevel( int nLevel );
	CLevelSection *GetLeveSection( int nLevelID );	
	int GetLevelRange( int nLevelID, int &rMinLevel, int &rMaxLevel );
private:
	CLevelSection mLevelSectionList[MAX_LEVLESECTION_NUM];
	int mMaxLevel;
};