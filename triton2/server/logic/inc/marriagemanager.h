#pragma once
#include "servertool.h"
#include "object.h"
#include "protype.h"
#include <string.h>
#include "shm.h"
#include "lk_hashmap.h"
#include "lk_vector.h"
#include "marriagetype.h"
#include "sceneobj_define.h"


class CMarriageInfo : public CObj
{
public:
	char mGroomName[NAME_LENGTH];	// ��������
	char mBrideName[NAME_LENGTH];			// ��������
	unsigned int  mGroomID;					// ���ɽ�ɫID	
	unsigned int  mBrideID;					// �����ɫID		
	int  mMarriageStatus;					// ����״̬
	int  mWeddingTime;						// ������е�ʱ��
	int  mWeddingTimeLength;				// ������е�ʱ�䳤��
	int  mCampSequence;						// ��Ӫ�ڼ���
	int  mServerSequence;					// ȫ���ڼ���
	int	 mWeddingModule;					// �����ģ	
	int	 mCampID;							// ��ӪID
	int  mWeddinNpcID[MAX_WEDDING_NPCNUM];	// ����npc��ʵ��ID
	int	 mWeddingNpcPosIndex[MAX_WEDDING_NPCNUM];	// ����npc�ƶ���λ������
	int	 mSynchMark[MAX_WEDDING_NPCNUM];	// �����ͬ�����־
	int	 mGroomKeepsakeIndex;				// ���ɵĽ�����������
	int  mGroomKeepsakeStatus;				// ���ɵĽ�������״̬
	int	 mBrideKeepsakeIndex;				// ����Ľ�����������
	int  mBrideKeepsakeStatus;				// ����Ľ�������״̬
	int  mWeddingEventStatus;				// ������¼�״̬
	int  mWaitSynMark;						// ���ڵȴ���ͬ����־ID
	
public:
	CMarriageInfo()
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
	
	virtual int Initialize();
	virtual int Resume();
public:

	// ����&��ȡ��������
	void SetGroomName( const char *pName )
	{
		strncpy( mGroomName, pName, NAME_LENGTH - 1 );
		mGroomName[NAME_LENGTH-1] = '\0';
	}
	const char *GetGroomName( ){ return mGroomName; } 
	
	// ����&��ȡ��������
	void SetBrideName( const char *pName )
	{
		strncpy( mBrideName, pName, NAME_LENGTH - 1 );
		mBrideName[NAME_LENGTH - 1] = '\0';
	}
	
	const char *GetBrideName(){ return mBrideName; }
	
	// ����&��ȡ���ɵĽ�ɫID
	void SetGroomID( int nGroomID ){ mGroomID = nGroomID; }
	unsigned int GetGroomID(){ return mGroomID; }
	
	// ����&��ȡ����Ľ�ɫID
	void SetBrideID( int nBrideID ){ mBrideID = nBrideID; }
	unsigned int	GetBrideID( ){ return mBrideID; }
	
	// ����&��ȡ����״̬
	void SetMarriageStatus( int nStatus ){ mMarriageStatus = nStatus; }
	int GetMarriageStatus(){ return mMarriageStatus; }
	
	// ����&��ȡ����ľ���ʱ��
	void SetWeddingTime( int nTime ){ mWeddingTime = nTime; }
	int GetWeddingTime(){ return mWeddingTime; }
	
	// ����&��ȡ������е�ʱ�䳤��
	void SetWeddingTimeLength( int nTimeLength ){ mWeddingTimeLength = nTimeLength; }
	int GetWeddingTimeLength(  ){ return mWeddingTimeLength; }
	
	// ����&��ȡ�����ģ
	void SetWeddingModule( int nWeddingModule ){ mWeddingModule = nWeddingModule; }
	int	GetWeddingModule(){ return mWeddingModule; }
	
	// ������Ӫ����
	void SetCampSequence( int nSequence ){ mCampSequence = nSequence; }
	int	GetCampSequence( ){ return mCampSequence; }
	
	// ���÷�������
	void SetServerSequence( int nSequence ){ mServerSequence = nSequence; }
	int GetServerSequence( ){ return mServerSequence; }
	
	// ����&��ȡ��ӪID
	void SetCampID( int nCampID ){ mCampID = nCampID; }
	int	GetCampID( ){ return mCampID; }
	
	// ����&��ȡ���ɵ���������
	void SetGroomKeepsakeIndex( int nIndex ){ mGroomKeepsakeIndex = nIndex; }
	int GetGroomKeepsakeIndex(){ return mGroomKeepsakeIndex; }
	
	// ����&��ȡ�������������
	void SetBrideKeepsakeIndex( int nIndex ){ mBrideKeepsakeIndex = nIndex; }
	int GetBrideKeepsakeIndex(){ return mBrideKeepsakeIndex; } 
	
	// ����&��ȡ������¼�
	void SetWeddingEventStatus( int nStatus ){ mWeddingEventStatus = nStatus; }
	int	GetWeddingEventStatus( ){ return mWeddingEventStatus; }
	
	// ����&��ȡ��������
	void SetKeepsakeIndex( int nIndex, int nSex )
	{	
		if ( nSex == 2 )
		{
			mGroomKeepsakeIndex = nIndex;
		}
		else
		{
			mBrideKeepsakeIndex = nIndex;
		}
	}
	
	int GetKeepsakeIndex( int nSex )
	{	
		if ( nSex == 2 )
		{
			return mGroomKeepsakeIndex;		
		}
		else
		{
			return mBrideKeepsakeIndex;
		}
	}
	
	// ����&��ȡ���ɽ�������״̬
	void SetGroomKeepsakeStatus( int nSatus ){ mGroomKeepsakeStatus = nSatus; } 
	int GetGroomKeepsakeStatus(){ return mGroomKeepsakeStatus; } 
	
	// ����&��ȡ���ɽ�������״̬
	void SetBrideKeepsakeStatus( int nStatus ){ mBrideKeepsakeStatus = nStatus; } 
	int GetBrideKeepsakeStatus(){ return mBrideKeepsakeStatus; } 
	
		
	// ����&��ȡ��������״̬
	void SetKeepsakeStatus( int nStatus, int nSex )
	{	
		if ( nSex == 2 )
		{
			mGroomKeepsakeStatus = nStatus;
		}
		else
		{
			mBrideKeepsakeStatus = nStatus;
		}
	}
	int GetKeepsakeSatus( int nSex )
	{
		if ( nSex == 2 )
		{
			return mGroomKeepsakeStatus;
		}
		else
		{
			return mBrideKeepsakeStatus;
		}			
	}
	
	// ����&��ȡNpc��ʵ��ID
	void SetWeddingNpcID( int nPos, int nNpcID )
	{
		if ( nPos >= 0 && nPos < (int)ARRAY_CNT( mWeddinNpcID ) )
		{
			mWeddinNpcID[nPos] = nNpcID;
		}
	}
	int GetWeddingNpcID( int nPos )
	{
		if ( nPos >= 0 && nPos < (int)ARRAY_CNT( mWeddinNpcID ) )
		{
			return mWeddinNpcID[nPos];
		}
		return 0;
	}
	
	// ��ʼ������npc��ID
	int InitializeNpcID()
	{
		memset( mWeddinNpcID, 0, sizeof( mWeddinNpcID ) );
		return SUCCESS;
	}
	
	// ����&��ȡnpc���ƶ�λ������
	void SetWeddingNpcPosIndex( int nPos, int nIndex )
	{
		if ( nPos >= 0 && nPos < (int)ARRAY_CNT( mWeddingNpcPosIndex ) )
		{
			mWeddingNpcPosIndex[nPos] = nIndex;
		}
	}
	
	int GetWeddingNpcPosIndex( int nPos )
	{
		if ( nPos >= 0 && nPos < (int)ARRAY_CNT( mWeddingNpcPosIndex ) )
		{
			return mWeddingNpcPosIndex[nPos];
		}
		return -1;
	}

	
	// ��ʼ������npc���ƶ�λ������
	int InitializeNpcPosIndex()
	{
		memset( mWeddingNpcPosIndex, 0, sizeof( mWeddingNpcPosIndex ) );
		return SUCCESS;
	}
	
	// ����ͬ����־
	void SetSynchMark( int nPos, int nMark )
	{
		if ( nPos >= 0 && nPos < (int)ARRAY_CNT( mWeddingNpcPosIndex ) )
		{
			mSynchMark[nPos] = nMark;
		}
	}
	
	// ��ȡͬ����־
	int GetSynchMark( int nPos )
	{
		if ( nPos >= 0 && nPos < (int)ARRAY_CNT( mWeddingNpcPosIndex ) )
		{
			return mWeddingNpcPosIndex[nPos];
		}
		return -1;	
	}
	
	// ��ʼ��ͬ����־
	void InitializeSyncMark()
	{
		memset( mSynchMark, 0, sizeof( mSynchMark ) );	
	}
	
	// ����Ƿ����е㶼��������Ҫͬ����λ��
	bool CheckSynchMark( );
	
	// ����&��ȡͬ����־
	void SetWaitSynMark( int nMark ){ mWaitSynMark = nMark;  }
	int GetWaitSynMark( ){ return mWaitSynMark; }
		
public:
	
	// �ж�ĳ�����ʱ���Ƿ�����ڵ�ʱ���໥��ͻ
	bool JudgeTimeValide( int nTime, int nTimeLength );	
	
	// ��ȡ����ľ���״̬	
	int GetWeddingStatus();
	
	// ��ʼ��������Ϣ
	void InitialWeddingInfo();
};	

// �������ʱnpc������·��
struct CNpcPos
{
public:
	int mPosX;
	int mPosY;
	int mSynchMark;		// ͬ����־	
public:
	CNpcPos()
	{
		if ( CObj::msCreateMode )
		{
			mPosX = 0;
			mPosY = 0;
		}
	} 	
};
struct CWeddingNpcPath
{
public:
	CNpcPos mNpcPath[MAX_WEDDINGNPCPATH_STEPS];
	int		mNpcTmpID;
	int		mMapID;
	int		mMapIndex;
public:
	CWeddingNpcPath( )
	{
		if ( CObj::msCreateMode )
		{
			memset( mNpcPath, 0, sizeof( mNpcPath ) );
			mNpcTmpID = 0;
			mMapID = 0;
			mMapIndex = 0;
		}
		else
		{
	
		}
	}
};

struct CWeddingNpcInfo
{
public:
	  CWeddingNpcPath mNpcPathInfo[MAX_WEDDING_NPCNUM];
public:
	CWeddingNpcInfo( )
	{
		if ( CObj::msCreateMode )
		{
			memset( mNpcPathInfo, 0, sizeof( mNpcPathInfo ) );
		}
		else
		{
			
		}
	}
};

class CCampInfo
{
public:
	int mCampID;
	int mMarriageNum;
public:
	CCampInfo()
	{
		if ( CObj::msCreateMode )
		{
			mCampID = 0;
			mMarriageNum = 0;
		}
		else
		{
			
		}
	}
	~CCampInfo() { }
public:
	void SetMarriageNum( int nMarriageNum ){ mMarriageNum = nMarriageNum; }
	int GetMarriageNum( ){ return mMarriageNum; }
	
	// ����&��ȡ��ӪID
	void SetCampID( int nCampID ){ mCampID = nCampID; }
	int	GetCampID( ){ return mCampID; }
};		


// �����ϵͳ��ѡʱ���
struct CWeddingSysTime
{
public:	
	int mBeginTime;				// ��ʼʱ��
	int mEndTime;			// ʱ��εĳ���		
	int	mCommonAllowed;			// ��ͨ�����Ƿ����
	
public:
	CWeddingSysTime()
	{
		mBeginTime		= 0;
		mEndTime		= 0;
		mCommonAllowed	= 0;
	}
};					 

class CMarriageManager : public CSingleton< CMarriageManager >
{
public:
	CMarriageManager()
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
	~CMarriageManager(){ }
public:
	static CSharedMem* mShmPtr; // �����ڴ�ָ��
public:
	int Initialize();		
	int Resume();	
public:	
	void *operator new( size_t nSize );
	void operator delete( void *pPointer );
	static unsigned int CountSize();	
public:
	typedef lk::hash_map< int, int, SERVER_CAP_MARRIAGEINFO >	MarriageInfoList;				// ������Ϣ�б�	
	typedef lk::vector< int, SERVER_CAP_MARRIAGEINFO >		MarriageApplyInfo;					// ���д�����Ļ�����Ϣ
	typedef lk::hash_map< int, CWeddingSysTime, MAX_WEDDNGTIMEAREA_NUM > SysWeddingTimeList;	// ϵͳ����ʱ���
	typedef lk::hash_map< int, int, MAX_WEDDING_TIMERNUM >	WeddingTimeList;					// ����ʱ���б�
private:
	MarriageInfoList mMarriageInfoList;															// ����Ӫ���еĻ�����Ϣ
	MarriageInfoList mWeddingList;																// ����Ӫ���д��ٰ����Ļ�����Ϣ
	CCampInfo		 mCampInfo;																	// ��Ӫ��Ϣ
	int				 mCurretnWeddingID;															// Ŀǰ���ھ��л���Ļ�����ϢID
	MarriageApplyInfo mMarriageApplyInfo;	
	MarriageInfoList mOtherCampMarriageInfo;													// �ڱ�����������Ӫ����ҵĻ�����Ϣ	
	CWeddingNpcInfo	mNpcPath[MAX_WEDDING_MODULENUM];											// npc��·����Ϣ	
	SysWeddingTimeList mWeddingTimeInfo;														// ϵͳ�Ļ���ʱ�����Ϣ
	WeddingTimeList		mWeddingTimer;															// ����ʱ��
public:	

	// ��ȡ&�������ھ��л���Ļ�����ϢID
	int GetCurrentWeddingID(){ return mCurretnWeddingID; }
	void SetCurrentWeddingID( int nWeddingID ){ mCurretnWeddingID = nWeddingID; }
	
	// ��ȡ���ھ��л���Ļ�����Ϣ
	CMarriageInfo * GetCurrentWeddingInfo()
	{
		return GetMarriageInfo( mCurretnWeddingID );
	}
	
	// ��ȡ��Ӫ��Ϣ
	CCampInfo *GetCampInfo( ){ return &mCampInfo; }
	
	// ����һ��������Ϣ
	CMarriageInfo * CreatMarriageInfo( const char *pGroomName, int nGroomID, const char *pBrideName, int nBrideID, int nWeddingTime, int nWeddingTimeLength, int nWeddingModule, int nCampID );					
	
	// ����һ����ҵĻ�����Ϣ
	int InsertMarriageInfo( int nServerSequence, CMarriageInfo *tpMarriageInfo );
	
	// ��ȡ��ҵĻ�����Ϣ
	CMarriageInfo * GetMarriageInfo( int nServerSequenceID );
	
	// ��ȡĳ����ҵ���Ϣ��ͨ����ɫID
	CMarriageInfo * GetMarriageByRoleID( unsigned int nRoleID );	
	
	// ɾ��ĳ��������Ϣ
	int DeleteMarriageInfo( int nServerSequenceID );
	
	// ��ȡ��ǰ���Խ��л���ļ���
	CMarriageInfo *GetWeddingMarriageInfo();
	
	// ��ȡ����Ӫ�����л�����Ϣ���б�
	MarriageInfoList &GetMarriageInfoList(){ return mMarriageInfoList; }
	
	// ��ȡ����Ӫ���д����л������Ϣ�б�
	MarriageInfoList &GetWeddingList(){ return mWeddingList; }
	
	// ������ʱ���Ƿ����Ҫ��
	bool CheckWeddingTime( int nWeddingTime, int nWeddingTimeLength );
	
	// ����Ƿ���Ѿ�������ҵĻ���ʱ���ͻ
	bool CheckMarriageWeddingTime( int nWeddingTime, int nWeddingTimeLength );
	
	// ��ȡ�͵�ǰʱ����ͻ�Ļ�����Ϣ
	CMarriageInfo *GetMarriageInfoConfictedWithTime( int nWeddingTime, int nWeddingTimeLength );
	
	// ����Ƿ�����������ҵĻ���ʱ���ͻ
	bool CheckMarriageApplyWeddingTime( int nWeddingTime, int nWeddingTimeLength );
	
	// ��ȡĳ��������Ļ�����Ϣ
	CMarriageInfo *GetMarriageApplyInfo( unsigned int nRoleID );
	
	// ��ȡ��ҵĻ�����Ϣ
	CMarriageInfo *GetMarriageInfoByMarriageID( int nMarriageID );
	
	// ����һ��������Ļ�����Ϣ
	CMarriageInfo * CreatMarriageApplyInfo( int nGroomID, int nBrideID, int nWeddingTime, int nWeddingTimeLength, int nWeddingModule );			
	
	// ɾ��һ��������Ļ�����Ϣ
	int DeleteMarriageApplyInfo( unsigned int nRoleID );	
	
	// ��¼һ������������ҵĻ�����Ϣ
	int InsertOtherCampMarriageInfo( CMarriageInfo *pMarriageInfo );  	
	
	// ��¼һ������������ҵĻ�����Ϣ
	void DeleteOtherCampMarriageInfo( int nMarriageID ); 
	
	// ��ȡһ���ڱ���Ӫ��������Ӫ��ҵĻ�����Ϣ
	CMarriageInfo *GetMarriageInfoOfOtherCamp( int nMarriageID ); 
	
	// ��ȡ��ҵĻ�����Ϣ
	CMarriageInfo* GetMarriageInfoByID( int nCampID, int nMarriageID );	
	
	// ��ȡnpc�Ƿ񵽴�Ŀ���
	bool CheckNpcPos( int nNpcPosIndex, int nWeddingModule, int nNpcIndex, int nNpcPosX, int nNpcPosY, bool &rReachEnd );
	
	// ��ȡĳ�ֹ�ģ��npc·����Ϣ	
	CWeddingNpcInfo *GetWeddingNpcInfo( int nWeddingModule );	
	
	// ��ȡĳ�ֹ�ģ��npc��·����Ϣ
	
	// ��ȡnpc���ƶ������
	int GetNpcMovePos( int nWeddingModule,  int nNpcIndex, int nNpcPosIndex, CNpcPos &rNpcPos );
	
	// ����һ��npc��·����Ϣ
	int InsertNpcPath( int nWeddingModule, CWeddingNpcPath &rNpcPath );
	
	
	// ����һ��ϵͳ����ʱ���
	int InsertSysWeddingTimeInfo( int nTimeID, CWeddingSysTime &rWeddingTime );	
	
	// ��ȡָ��ID�Ļ���ʱ���
	CWeddingSysTime* GetWeddingTimeInfo( int nTimeID );
	
	// ɾ��һ��ϵͳʱ���
	void DeleteWeddingTimeInfoByID( int nTimeID );
	
	// ��ȡʱ���б�
	SysWeddingTimeList *GetWeddingTimeInfoList(){ return &mWeddingTimeInfo; }
	
	// ��ʼ������ʱ������
	int InitialWeddingTimeInfo();
	
	// ��ʼ��npc��·����Ϣ
	int InitialNpcPathInfo( );
	
	// ���û���ʱ��
	int SetWeddingTimer( int nTimeMark,	int nTimerID );
	
	// ��ȡ����ʱ��
	int GetWeddingTimerID( int nTimerMark );
	
	// �������ʱ��
	int ClearWeddingTimer( int nTimerMark );
	
	// ������ж�ʱ��
	int ClearAllWeddingTime();
};