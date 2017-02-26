#pragma once

#include "activitytype.h"
#include "lk_hashmap.h"
#include "lk_vector.h"
#include "marriagetype.h"
#include "servertool.h"

// 100311 MAOCY ADD-BEGIN
#define ROLE_VALID_QUESTION_FAILURE_COUNT 2
#define ROLE_VALID_QUESTION_RESOURCE_LENGTH 64*64*2

#define ROLE_VALID_QUESTION_COUNT 256
#define ROLE_VALID_QUESTION_GROUP_COUNT 4
#define ROLE_VALID_QUESTION_OPTION_COUNT 64
#define ROLE_VALID_QUESTION_DESCRIPTION_LENGTH 1024

// Ӧ������
enum EAppType
{
	APPTYPE_NULL			= 0x00,			// û�н����κδ���
	APPTYPE_NPC				= 0x01,			// ÿ���ʴ�
	APPTYPE_QUESTIONPAPER	= 0x02,			// ���
	APPTYPE_ACTIVITY		= 0x04,			// �
};

// ��Ŀ�����ݽṹ
struct CQuestion
{		
	unsigned short QuestionID;				// ��ĿID
	unsigned short QuestionAnswer;			// ��Ŀ��
	CQuestion()
	{
		if ( CObj::msCreateMode )
		{
			QuestionID = 0;
			QuestionAnswer = 0;
		}
		else
		{
			
		}
	}
};

// �������ݽṹ
struct CQuestionLib
{
	int LibID;
	int QuestionNum;
	int	FirstQuestionIndex;
	CQuestionLib()
	{
		if ( CObj::msCreateMode )
		{
			LibID = 0;
			QuestionNum = 0;
			FirstQuestionIndex = 0;
		}
		else
		{
			
		}
	}
};


// �������Ӧ�õ����ݽṹ
struct CAppType
{
	int			TypeID;
	char		TypeName[XML_ELEMENT_NAME_LENGTH];
	int			QuestionLibNum;
	CQuestionLib QuestionLib[MAX_QUESTIONLIB_NUM];
	CAppType()
	{
		if ( CObj::msCreateMode )
		{
			TypeID = 0;
			memset( TypeName, 0, sizeof( TypeName ) );
			QuestionLibNum = 0;
			memset( QuestionLib, 0, sizeof( QuestionLib ) );
		}
		else
		{
		
		}
	}
};

// ��Ʒ������Ϣ
struct CItemPrize
{
	int ItemPrizeID;
	int ItemPrizeNum;	
};

// ��������
class  CQuestionManager
{
public:
	typedef lk::vector< CItemPrize, MAX_NPCPRIZE_NUM > NpcPrizeList;
public:
	int AddNewLib( int LibID, const char *pAppType );
	int AddQuestion( const char *QuestionID, const char *Answer );
	int CreatQuestion( int Apptype, int QuestionNum,int *Question, int *Answer );
	int CreatLibID( CAppType *pAppType,int QuestionNum, int *vLibIndex );
	int GetQuestFromLib( CAppType *pAppType,int QuestionNum,int *Question, int *Answer  );	
	int InsertNpcPrize( CItemPrize &rNpcPrize );
	int GetNpcPrize( CItemPrize *pPrizeList, int &rNum );
public:
	CQuestionManager( );
	~CQuestionManager( ){ }
	int Initialize();
	int Resume();
	
protected:
private:
	CAppType	mNpcLib;						// ÿ���ʴ�npc�����
	CAppType	mPaperLib;						// ��������
	CQuestion	mQuestion[TOTAL_QUESTION_NUM];	// ���е���Ŀ
	int			mQuestionNum;
	int			mCurrentLibID;					// ���ڶ�ȡ���ID
	NpcPrizeList mNpcPrizeList;					// npc�������Ʒ����			
};	



// ���ڼ�¼��Ҵ���״̬
class  CAnswerStatus : public CObj
{

public:
	// �����Ƿ���ȷ
	int CheckAnswer( int QuestionID,int QuestAnswer );
	
	// ��ȡ����Ŀ��ID
	int	GetNewQuestID( );
	
	//  ����Ǳ������Ƿ��Ѿ�����
	int CheckIfQuestionInvalidation( int CheckType );
	
	// ��������
	int EndAnswerQuesetion(  );
	
	// �����Ŀ���Ĵ���
	int CheckCountAnswered( int QuestionID = 0 );
	
	// �������״̬��Ϣ
	void ClearStatus(  );

public:
	  void SetAppType( int status ){	mAppType = status; }
	  int  GetAppType(  ) { return mAppType;	 } 	  
	  
	  void SetCurrentQuestIndex( int index  ) {  mCurrentQuestIndex = index; } 
	  int  GetCurrentQuestIndex( ){  return mCurrentQuestIndex; }	
	  
	  void SetCountAnswered( int count ){  mCountAnswered = count; }
	  int  GetCountAnswered(){  return mCountAnswered; }
	  
	  int  SetQuestion( int QuestNum, int *Question, int *Answer );	
	  
	  void SetQuestionNum( int QuestionNum ){ mQuestionNum = QuestionNum; } 
	  int  GetQuestionNum( ){  return mQuestionNum; }		
	  
	  void SetPaperIndex( int Index ){ mQuestPaperIndex = Index; }
	  int  GetPaperIndex(  ){ return mQuestPaperIndex; }
	  
	  void SetRightAnswerNum( int Num ){ mRightAnswerNum = Num; } 
	  int  GetRightAnswerNum(  ) { return mRightAnswerNum; }
	  
	  void SetSingleTimerID( int TimerID ) { mSingleTimerID = TimerID; }
	  int  GetSingleTimerID( ){  return mSingleTimerID; }
	  
	  void SetTotalTimerID( int TimerID ){ mTotalTimerID = TimerID; }
	  int GetTotalTimerID(  ){  return mTotalTimerID; }
	  
	  void SetInvestLibID( int vLibID ) { mInvestLibID = vLibID; } 
	  int  GetInvestLibID( ){ return mInvestLibID; } 
	  
	  void SetExpRate( int nExpRate ){ mExpRate = nExpRate; }
	  int  GetExpRate(  ){ return mExpRate; }
 
	  void SetQuestionVerifyDataLength( int nLength ) { mQuestionVerifyDataLength = nLength; }
	  int GetQuestionVerifyDataLength() { return mQuestionVerifyDataLength; }
	  
	  void SetQuestionVerifyData( const char *pData, int nLength )
	  {
		if ( pData != NULL )
		{
			int tSize = nLength > (int)( sizeof( mQuestionVerifyData ) ) ?   (int)(sizeof( mQuestionVerifyData )) : nLength; 
			memcpy( mQuestionVerifyData, pData, tSize );
			mQuestionVerifyDataLength = tSize;
		}
	  } 
	  
	  bool CheckQuestionVerifyData( const char *pData, int nLength )
	  {
		  if ( pData == NULL )
		  {
			return false;
		  }
		  
		  if ( nLength != mQuestionVerifyDataLength )		  
		  {
			return false;
		  }
		  
		  if ( memcmp( mQuestionVerifyData, pData, mQuestionVerifyDataLength ) == 0 )
		  {
			return true;
		  }
		  
		  return false;
	  }
	  
	  void SetRoleVerifyKind( int nKind ){ mRoleVerifyKind = nKind; }
	  int GetRoleVerifyKind(){ return mRoleVerifyKind; }
	  
	  void SetRoleVerifyType( int nType ){ mRoleVerifyType = nType; }
	  int GetRoleverifyType(  ) { return mRoleVerifyType; }
	  
	  void SetVerifyTimeID( int nID ){ mVerifyTimeID = nID; }
	  int GetVerifyTimeID(){ return mVerifyTimeID; }
	 
	  
	  // �����֤��Ϣ
	  void ClearQuestionVerifyInfo()
	  {
		  mQuestionVerifyDataLength = 0;
		  memset( mQuestionVerifyData, 0, sizeof( mQuestionVerifyData ) );	
		  mRoleVerifyKind = 0;
		  mRoleVerifyType = 0;	  
	  }  
public:  
	  CAnswerStatus( )
	  {		
		  if( CObj::msCreateMode )
		  {
			  Initialize();
		  }
		  else
		  {
			  Resume();
		  }	
	  }
public:
	// ��ʼ��
	virtual int Initialize( ) 
	{ 		
		mAppType = 0;
		mQuestionNum  = 0;
		mCurrentQuestIndex = -1;
		mCountAnswered    = 0;	
		mRightAnswerNum = 0;
		mQuestPaperIndex = 0;
		mTotalTimerID = 0;
		mSingleTimerID = 0 ;
		memset( mQuestionIDSet, 0, sizeof( mQuestionIDSet ) );
		memset( mAnswerSet,	0, sizeof( mAnswerSet ) );
		mInvestLibID = 0;
		mExpRate = 1;	
		
		mQuestionVerifyDataLength = 0;
		memset( mQuestionVerifyData, 0, sizeof( mQuestionVerifyData ) );	
		mRoleVerifyKind = 0;
		mRoleVerifyType = 0;
		mVerifyTimeID=0;	
		return 0;
	} 
	// �ָ�
	virtual int Resume( ) { return 0; } 
protected:
public:
	int		  mQuestionIDSet[MAX_PLAYER_QUESTIONNUM];	// ��Ŀ
	int		  mAnswerSet[MAX_PLAYER_QUESTIONNUM];		// ��Ŀ��
	short	  mAppType;									// Ŀǰ�Ĵ���״̬
	short 	  mQuestionNum;								// Ŀǰ���ش���Ŀ������
	short     mCurrentQuestIndex;						// Ŀǰ���������Ŀ������
	short	  mCountAnswered;							// ������Ŀ�Ѿ��ش�Ĵ���		
	short     mRightAnswerNum;							// �Ѿ��ش���ȷ����Ŀ����
	short     mQuestPaperIndex;							// ����������
	int		  mTotalTimerID;							// ������Ŀ�ļ�ʱ��
	int		  mSingleTimerID;							// ÿ����Ŀ�ļ�ʱ��
	int		  mInvestLibID;							    // �����ʾ����ĿID
	int		  mExpRate;									// �����ľ���ӳ�
	
	int		  mQuestionVerifyDataLength;							// ������֤���ݳ���
	char	  mQuestionVerifyData[ROLE_VALID_QUESTION_RESOURCE_LENGTH]; // ������֤������			
	short	  mRoleVerifyKind;										// ������֤���ͣ�������֤������ͨ��֤
	short	  mRoleVerifyType;										// ��֤���ͣ�ʲô��������(��ʱ�������ߵ�)	
	int		  mVerifyTimeID;										// ��֤ʱ��ʱ����ID
};



/*****************�ʾ��������ݽṹ*************/ 
struct CInvestAnswer
{
public:
	short mAnswerCount[MAX_OPTION_NUM];
	int	  mQuestionID;
public:
	CInvestAnswer()
	{
		if ( CObj::msCreateMode )
		{
			memset( mAnswerCount, 0, sizeof( mAnswerCount ) );	
			mQuestionID = 0;
		}
		else
		{	
					
		}		
	}
};

class  CInvestQuestionLib
{	
public:
	int Initialize();
	int Resume();
	CInvestQuestionLib();
	~CInvestQuestionLib(){ }	
public:
	void SetLibID( int vLibID ){ m_nLibID = vLibID; }
	int	 GetLibID( ){ return m_nLibID; }
	
	void SetQuestionNum( int vQuestionNum ){ m_nQuestionNum = vQuestionNum; }
	int  GetQuestionNum(  ){ return m_nQuestionNum; }
	
	int InsertQuestion( int QuetionID, int IfSelected );
	int GetQuestion( int QuestionIndex );
	
	void SetExpPrize( int vExp ){ m_nExpPrize = vExp; } 	
	int  GetExpPrize(  ){ return m_nExpPrize; }	
	
	int InsertItemPrize( int ItemID, int ItemNum );
	int GetItemPrize( int Index, CItemPrize &vItemPrize );
	int GetItemPrizeNum(){ return m_nItemPrizeNum; }	
	
	void SetMaxQuestionNum( int vNum ){ m_nMaxQuestionNum = vNum; }
	int GetMaxQuestionNum(){ return m_nMaxQuestionNum; }
	
	void SetMoney( int vMoney ){ m_nMoney = vMoney; }
	int  GetMoney(  ){ return m_nMoney; }
	
	void SetBindMoney( int vBindMoney ){ m_nBindMoney = vBindMoney; }
	int  GetBindMoney( ){ return m_nBindMoney; } 
	
	void SetCowry( int vCowry ){ m_nCowry = vCowry; }
	int  GetCowry(  ){ return m_nCowry; }
	
	int CreatInvestQuestionID( );
	
	// ��¼��
	int RecordAnswer( int nQuestionID, int nAnswerOption );
	
	// �����
	void ClearAnswer(){  memset( m_nAnswerList, 0, sizeof( m_nAnswerList ) ); }
	
	// �Ƿ���ĳ����Ŀ
	bool HasQuestion( int nQuestionID );	
	
	// ����ĳ����Ŀĳ��ѡ�������
	void SetOptionCount( int nQuestionID, int nOptionIndex, int nCount );

public:
	CInvestAnswer *GetAnswerInfo( int nIndex )
	{ 
		if ( nIndex < 0 || nIndex >= (int)ARRAY_CNT( m_nAnswerList ) )
		{
			return NULL;
		}
		return &m_nAnswerList[nIndex];
	}
private:						  
	int m_nLibID;										// ���ID
	int m_sQuestionList[MAX_QUESTIONNUM_EACHLIB];		// ��Ŀ�б�
	int m_nQuestionNum;									// ��Ŀ����
	int m_nExpPrize;									// ���齱��
	CItemPrize m_nItemPrizeList[MAX_INVEST_PRIZENUM];	// ��Ʒ����
	int m_nItemPrizeNum;								// ������Ʒ������
	int m_nMaxQuestionNum;							    // ����еĵ����ʾ�������Ŀ����С����Ŀ����
	int m_nSelectedQuestionNum;							// ��ѡ��Ŀ����
	int m_nMoney;										// �����Ľ�Ǯ
	int m_nBindMoney;									// �����İ󶨽�Ǯ
	int m_nCowry;										// ������Ԫ��	
	CInvestAnswer m_nAnswerList[MAX_QUESTIONNUM_EACHLIB];// ���б�
};


class CInvestQuestionManage
{
public:
	typedef lk::hash_map< int, CInvestQuestionLib, MAX_INVEST_QUESTLIBNUM > INVESTLIBLIST; 
public:
	CInvestQuestionManage();
	~CInvestQuestionManage(){}
	int Initialize();
	int Resume();
public:
	CInvestQuestionLib *GetInvestQuestLib( int vLibID );
	int InsertInvestQuestLib( CInvestQuestionLib *pQuestionLib );
	INVESTLIBLIST *GetQuestionLibList(){ return &m_tInvestLibList; }
	
	// ��¼��Ŀ��
	int RecordLibAnswer( int nLibID, int nQuestionID, int nOption );
	
	// ���ĳ�����Ĵ�	
	int ClearLibAnswer( int nLibID );
	
	// ���������Ŀ�Ĵ�
	int ClearAllLibAnswer();
	
	// ����&��ȡ�����ʾ��Ƿ������
	void SetInvestOutput( bool bOutput ){ m_bInvestOutput = bOutput; }
	bool GetInvestOutput(){ return m_bInvestOutput; }

private:
	INVESTLIBLIST m_tInvestLibList;	
	bool m_bInvestOutput;								// �������Ƿ������		
};



// �������������
struct CHydrangeaNpcPath
{
public:
	CWTPoint mNpcPath[MAX_WEDDINGNPCPATH_STEPS];
	int		mNpcTmpID;
	int		mMapID;	
public:
	CHydrangeaNpcPath( )
	{
		if ( CObj::msCreateMode )
		{
			memset( mNpcPath, 0, sizeof( mNpcPath ) );
			mNpcTmpID = 0;
			mMapID = 0;			
		}
		else
		{

		}
	}
};

struct CTimeInfo
{
public:
	int mWeekDay;
	int mHour;
	int mMinute;
	int mActivityID;
};

struct CHydrangeaNpcInfo
{
public:
	CHydrangeaNpcPath mNpcPath[MAX_HYDRANGEANPC_NUM];
	int				  mActivityID;
public:
	CHydrangeaNpcInfo()
	{
		if ( CObj::msCreateMode )
		{
			memset( mNpcPath, 0, sizeof( mNpcPath ) );
			mActivityID = 0;
		}
		else
		{
			
		}
	}
};
class CHydrangeaNpcManager
{
public:
	CHydrangeaNpcManager()
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
	~CHydrangeaNpcManager(){ }
	
	int Initialize();
	int Resume( ){ return SUCCESS; };
public:
	typedef lk::vector<CTimeInfo, HYDRANGEA_TIMENUM> TimeInfoList;	
public:

	// ����һ��npc��·����Ϣ
	int InsertNpcPath( CHydrangeaNpcPath &rNpcPath, int nActivityID );
	
	// ����ĳ��npc��ʵ��ID
	int SetNpcEntityID( int nNpcIndex, int nEntityID );
	
	// ��ȡĳ��npc��ʵ��ID
	int GetNpcEntityID( int nNpcIndex );
	
	// ���npcʵ�������
	int GetNpcNum();
	
	// ���ĳ��npc�Ƿ񵽴���ָ������
	bool CheckNpcPos( int nNpcIndex, int nPosX, int nPosY, bool &rReachEnd );
	
	// ����ĳ��npc���ƶ�λ������
	int SetNpcPosIndex( int nNpcIndex, int nPosIndex );
	
	// ��ȡnpcĳ��λ������������
	int GetNpcPos( int nNpcIndex, int nPosIndex, CWTPoint &rPoint );
	
	// ��ȡĳ��npc��·����Ϣ
	CHydrangeaNpcPath *GetHydrangeaNpcPath( int nIndex, int nActivityID );
	
	// ��ȡĳ��npc��λ������
	int GetNpcPosIndex( int nIndex );
	
	// ����һ��ʱ����Ϣ
	int InsertTimeInfo( CTimeInfo &rTimeInfo );	 
	
	// ����Ƿ���Կ�ʼ�
	bool CheckActivityTime( CTimeInfo &rTimeInfo, int &rActivityID );	
	
	// ��ʼ��������Ϣ
	void InitializeConfig();
	
	// ����&��ȡ�ID
	void SetActivityID( int nActivityID ){ mActivityID = nActivityID; }
	int GetActivityID(){ return mActivityID; }
	
	// ���ݻID��ȡnpc�Ļ�����Ϣ
	CHydrangeaNpcInfo *GetHydrangeaNpcInfo( int nActivityID );
	
private:
//	CHydrangeaNpcPath mHydrangeaPath[MAX_HYDRANGEANPC_NUM];		// ����npc��·��
	int		  mHydrangeaPosIndex[MAX_HYDRANGEANPC_NUM];		    // npc�ĵ�ǰλ������
	int		  mNpcEntityID[MAX_HYDRANGEANPC_NUM];				// npc��ʵ��ID
	TimeInfoList mTimeInfo;
	CHydrangeaNpcInfo mNpcInfo[HYDRANGEA_TIMENUM];				// npc��·����Ϣ
	int		 mActivityID;										// ��ǰ���еĻID
};

// ����
class CHydrangeaActivityManager
{
public:
	CHydrangeaActivityManager()
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
	int Initialize();
	int Resume(){ return SUCCESS; }
public:	
	int mHydrangeaGraberID[MAX_HYDRANGEARABER_NUM]; // ��������˵Ľ�ɫID
	int mHydrangeaGraberNum;						// �����������
	int mHydrangeaRollValue;						// ����������ֵ
	int mHydrangeaHolderID;							// ��������ߵ�ID
	int mActivityStatus;							// ����״̬
	int mHydrangeaHoldTimerID;						// ������ж�ʱ����ID
	int	mActivityTimerID;							// �������ʱ����ID
public:
	// ����&��ȡ�����������
	void SetHydrangeaGraberNum( int nNum ){ mHydrangeaGraberNum = nNum; }
	int GetHydrangeaGraberNum( ){ return mHydrangeaGraberNum; }
	
	// ����&��ȡ����������ֵ
	void SetHydrangeaRollValue( int nValue ){ mHydrangeaRollValue = nValue; }
	int GetHydrangeaRollValue(){ return mHydrangeaRollValue; }
	
	// ����&��ȡ��������ߵ�ID
	void SetHydrangeaHolderID( int nRoleID ){ mHydrangeaHolderID = nRoleID; }
	int GetHydrangeaHolderID( ){ return mHydrangeaHolderID; }
	
	// ����&��ȡ������״̬
	void SetActivityStatus( int nStatus ){ mActivityStatus = nStatus; }
	int GetActivityStatus(){ return mActivityStatus; }
		
	// ��ȡԭʼ���������
	int GetOriginalHolder(){ return mHydrangeaGraberID[0]; }
	
	// ����&��ȡ������ж�ʱ����ID
	void SetHydrangeaHolderTimerID( int nTimerID ){ mHydrangeaHoldTimerID = nTimerID; }
	int GetHydrangeaHolderTimerID(){ return mHydrangeaHoldTimerID; }
	
	// ����&��ȡ������ʱ��ID
	void SetActivityTimerID( int nTimerID ){ mActivityTimerID = nTimerID; }
	int GetActivityTimerID( ){ return mActivityTimerID; }
public:
	int InitializeGrab( );					// ������ĳ�ʼ��
	int GrabHydrangea( int nRoleID );		// ��������
	bool CheckGraber( int nRoleID );		// ����Ƿ��Ѿ���������		
};

// ���﹥�ǻ�Ĺ�����Ϣ
class COgreInfo
{
public:
	int mTempID;							// �����ģ��ID
	int mActivityType;						// ����Ļ����
	int mLiveTime;							// ��ʾ�����ʣ��ʱ��
	int mKillerID;							// ɱ�����������һ���ֵ�ID
	int mErrcode;							// ��ʾ�����ʣ��ʱ��ʱӦ����ʾ�Ĵ�����
	int mBossOgre;							// �Ƿ�boss��
	int mEntityID[MAX_TEMPENTITY_NUM];		// ģ��ˢ���Ĺ���	
	int mDeathErrcode;						// ����ʱ������
public:
	void ClearEntityID(){ memset( mEntityID, 0, sizeof( mEntityID ) ); }
	void SetEntityID( int nEntityID )
	{
		for ( int i = 0; i < (int)ARRAY_CNT( mEntityID ); ++i )
		{
			if ( mEntityID[i] == 0 )
			{
				mEntityID[i] = nEntityID;
				break;
			}
		}
	}
	bool IsDead()
	{
		if ( mEntityID[0] == 0 )
		{
			return true;
		}
		return false;
	}
public:
	COgreInfo()
	{
		mTempID = 0;
		mActivityType = 0;
		mLiveTime = 0;
		mKillerID = 0;
		mErrcode = 0;
		mBossOgre = 0;
		memset( mEntityID, 0, sizeof( mEntityID ) );
		mDeathErrcode = 0;
	}
	~COgreInfo(){}
};

// ���﹥�ǻ�Ĺ�����
class COgreActivityManager
{
public:
	typedef lk::hash_map< int, COgreInfo, MAX_ACTIVITYOGRE_NUM > OgreInfoList;
public:
	int Initialize()
	{
		mOgreInfoList.initailize();
		return 0;
	}
	int Resume()
	{
		return 0;
	}
public:
	COgreActivityManager()
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
	~COgreActivityManager(){ }
public:
	int InsertOgreInfo( COgreInfo &rOgreInfo );
	COgreInfo* GetOgreInfo( int nTempID );		
	int EndOgreActivity( int nExceptTempID );
private:
	OgreInfoList mOgreInfoList;
};



//************************************************************
// Class:       SRoleValidQuestion
// Description: ��֤��ɫ�����ⶨ��
// Date:        2010-03-04
//************************************************************
typedef struct _SRoleValidQuestion{
	int id;
	int typeId;
	int resultId;
	char code[ROLE_VALID_QUESTION_DESCRIPTION_LENGTH];
	char description[ROLE_VALID_QUESTION_DESCRIPTION_LENGTH];
} SRoleValidQuestion;

//************************************************************
// Class:       SRoleValidQuestionOption
// Description: ��֤��ɫ������ѡ���
// Date:        2010-03-04
//************************************************************
typedef struct _SRoleValidQuestionOption{
	int id;
	int groupId;
	int length;
	char filename[ROLE_VALID_QUESTION_DESCRIPTION_LENGTH];
	char data[ROLE_VALID_QUESTION_RESOURCE_LENGTH];
} SRoleValidQuestionOption;

//************************************************************
// Class:       SRoleValidQuestionGroup
// Description: ��֤��ɫ������ѡ���鶨��
// Date:        2010-03-04
//************************************************************
typedef struct _SRoleValidQuestionGroup{
	int id;
	int count;
	SRoleValidQuestionOption options[ROLE_VALID_QUESTION_OPTION_COUNT];
} SRoleValidQuestionGroup;


// �۱���ĸ�����Ϣ
class CTreasureBowlProbality
{
public:
	int mNum[MAX_TREASUREBOWL_EXCHANGENUM];
	int mProbality[MAX_TREASUREBOWL_EXCHANGENUM];
public:
	CTreasureBowlProbality()
	{
		memset( mNum, 0, sizeof( mNum ) );
		memset( mProbality, 0, sizeof( mProbality ) );
	}
	~CTreasureBowlProbality(){}
};
// �۱������Ʒ�һ���Ϣ
class CTreasureItemExchangeInfo
{
public:	
	int mExchangeItemID;	// �һ��ɵ���ƷID
	int mProbilityID;		// ѡ�õĸ���ID
	int mTipsNum;			// ��������ʱ��Ӫ��ʾ
	int mUseTime;			// ÿ����Զһ��Ĵ���
	int mTaxMoney;			// �۱���Ҫ�Ľ�Ǯ
	int mTipsType;			// ��ʾ����0��ʾ��Ӫ��ʾ1��ʾȫ����ʾ
public:
	CTreasureItemExchangeInfo()
	{
		mExchangeItemID = 0;			
		mProbilityID = 0;
		mTipsNum = 0;
		mUseTime = 0;
		mTipsType = 0;
	}
	~CTreasureItemExchangeInfo(){}
};

//
class CTreasureBowlManager
{
public:
	typedef lk::hash_map< int, CTreasureBowlProbality, MAX_TREASUREBOWL_PROBALITY_NUM >	CTreasureBowlProbalityList;
	typedef lk::hash_map< int, CTreasureItemExchangeInfo, MAX_TREASUREBOWL_ITEM_NUM  >	 CTreasureBowlItemExchangeList;
public:
	CTreasureBowlManager()
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
	
	~CTreasureBowlManager(){}	
public:
	int Initialize()
	{
		mTreasureBowlProbalityList.initailize();
		mTreasureBowlItemExchangeList.initailize();
		mTotalNum = 0;		
		return 0;
	}
	int Resume()
	{
		return 0;
	}
public:
	int InsertTreasureBowlProbality( int nProbalityID, CTreasureBowlProbality &rProbality );
	int	InsertTreasureBowlExchangeInfo( int  nTemID, CTreasureItemExchangeInfo &rExchangeInfo );
	CTreasureBowlProbality* GetTreasureBowlProbality( int nProbalityID );
	CTreasureItemExchangeInfo* GetTreasureBowlExchangeInfo( int nItemID );		
	int GetTotalNum() { return mTotalNum; }	
	void SetTotalNum( int nTotalNum ) { mTotalNum = nTotalNum; }	
	int StartTreasureBowl( int nItemID, int &rNum, int &rNewItemID );	
public:
	CTreasureBowlProbalityList mTreasureBowlProbalityList;
	CTreasureBowlItemExchangeList mTreasureBowlItemExchangeList;	
	int mTotalNum;			// �۱���ÿ�����ʹ�õĴ���	
};