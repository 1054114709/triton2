/*
 *	Achieve Data
 */

// Created By GaoHong [11/18/2009 Macro]
#pragma once

#include "lk_hashmap.h"
#include "lk_vector.h"

#include "entity.h"
#include "achievetype.h"
#include "achievemessage_pb.hxx.pb.h"

class CMessage;


// �ɾ���������
struct ST_ACHIEVE_PARAM
{
	int mType;		
	int mValue;
	int mParam;
	ST_ACHIEVE_PARAM()
	{ mType = 0; mValue = 0; mParam = 0; }	
};

// �ɾ��������ݵ�Ԫ
class CAchieveCfgItem
{
public:
	typedef lk::vector< ST_ACHIEVE_PARAM, MAX_PARAM > PARAM_TYPE;

	enum emRequireType
	{
		Require_And = 1,
		Require_Or,
	};

	int		mID;	
	PARAM_TYPE mParam;
	int		mParamType;
	int		mPoint;
	int		mAward;
	int		mRootType;	// ����
	int		mRelation;
	int		mHonor;

public:
	CAchieveCfgItem()
	{
		mID = 0;
		mParamType = 0;
		mPoint = 0;
		mAward = 0;
		mRootType = 0;
		mRelation = 0;
		mHonor = 0;
		mParam.initailize();
	}
	~CAchieveCfgItem(){ mParam.clear();}

	// Set & Get
	inline void SetID( int nID ) { mID = nID; }
	inline int  GetID() { return mID; }

	inline void SetParamType( int nType ) { mParamType = nType; }
	inline int  GetParamType() { return mParamType; }

	inline void SetPoint( int nPoint ) { mPoint = nPoint; }
	inline int  GetPoint() { return mPoint; }

	inline void SetAward( int nAward ) { mAward = nAward; }
	inline int  GetAward() { return mAward; }

	inline void SetRoot( int nRoot ) { mRootType = nRoot; }
	inline int  GetRoot() { return mRootType; }

	inline void SetRelation( int nRelat ) { mRelation = nRelat; }
	inline int  GetRelation() { return mRelation; }

	inline void SetHonor( int nHonor ) { mHonor = nHonor; }
	inline int  GetHonor() { return mHonor; }

	int PushParam( ST_ACHIEVE_PARAM& nParam );
	int GetParam( int* npParamList, int& nNum );

	bool CheckParamValid( int nKey );
};

// ������ά���ĳɾ����ݵ�Ԫ

struct ST_ACHIEVE_DATA
{
	int		mKey;
	int		mValue;
	ST_ACHIEVE_DATA(){ mKey = 0; mValue = 0; }
};

// �������ݽṹ [12/7/2009 Macro]
struct ST_HONOR_DATA
{
	int		mMapID;
	int		mTime;
	ST_HONOR_DATA(){ mMapID = 0; mTime = 0; }
};

class CAchieveData
{
public:
	typedef lk::vector< ST_ACHIEVE_DATA, MAX_PARAM > PARAM_TYPE;
	
public:
	int						mID;
	bool					mStatus;	// �Ƿ����
	int						mTime;		// ���ʱ��	
	int						mRootType;	// ����
	PARAM_TYPE 				mParamList;
	
public:
	CAchieveData()
	{
		mID = 0;
		mStatus = false;
		mTime = 0;
		mRootType = 0;
		mParamList.initailize();
	}
	~CAchieveData()
	{
		mID = 0;
		mParamList.clear();
	}

	// Set & Get
	inline void SetID( int nID ){ mID = nID; }
	inline int  GetID(){ return mID; }

	inline void SetStatus( bool nStatus ) { mStatus = nStatus; }
	inline bool GetStatus() { return mStatus; }

	inline void SetTime( int nTime ) { mTime = nTime; }
	inline int  GetTime() { return mTime; }

	inline void SetRootType( int nType ) { mRootType = nType; }
	inline int  GetRootType() { return mRootType; }

	/*
	* nKey 		: ���� key
	* nOperate : ��1���ǡ��� etc.
	*/		
	int SetParam(int nKey, int nValue, int nType );
	int GetParam( int* npParamList, int& nNum, int nType );
	
	// ������ [12/10/2009 Macro]
	int SetParamValue( int nValue, int nParam = 0 );
	int GetParamValue();
	int GetTlvPB( PBAchieve* npAchievePB );

	// db pb
	int GetTlvDBPB( PBDBAchieve* npAchievePB );
	int SetFromDBPB( PBDBAchieve* npAchievePB );

	// ���ɾ��Ƿ����
	bool CheckAchieveFinish( CAchieveCfgItem* npCfgItem, int nCharID );
	// ������
	bool CheckSpecialAchieve( int* npParamList, int nNum, int nCharID );
};

// ���˵ĳɾ�����
class CAchieveDataUnit : public CObj
{
public:
	typedef lk::hash_map< int , CAchieveData, MAX_ACHIEVE_NUM > ACHIEVE_DATA_UNIT;
	typedef lk::vector< ST_HONOR_DATA, SERVER_CAP_MAP_TPL > HONOR_TYPE;
	ACHIEVE_DATA_UNIT	mAchieveUnit;
	HONOR_TYPE			mHonorList;	// �����б�

	int				mCharID;		// 
	int				mTotalPoint;	// �ܳɾ͵���
	int				mStage;			// ��ǰ�쵽�ĸ��׶���
public:
	CAchieveDataUnit()
	{
		mCharID = 0;
		mTotalPoint = 0;
		mStage = 0;
		mAchieveUnit.initailize();
		mHonorList.initailize();
	}
	~CAchieveDataUnit(){ mAchieveUnit.clear(); }

	virtual int Initialize() { return SUCCESS; }
	virtual int Resume() { return SUCCESS; }

	inline void SetOwnerCharID( int nCharID ) { mCharID = nCharID; }
	inline int  GetOwnerCharID() { return mCharID; }

	inline int GetTotalPoint() { return mTotalPoint; }
	inline void IncTotalPoint( int nPoint ) { mTotalPoint += nPoint; }

	inline int GetStage() { return mStage; }
	inline void IncStage( ) { mStage ++; }

	// Internal interface

public:
	// ��ʼ�ɾ�����(ͬ�����ݿ�)
	int InitFromSession( CMessage* npMessage );
	// ����ɾ����ݵ����ݿ�
	int SaveSessionData( CEntityPlayer* npPlayer );

	CAchieveData* GetAchieveData( int nID );
	int SetAchieveData( CAchieveData& nData );
	bool AchieveDataExist( int nID );

	int GetTlvPB( PBAchieveBuffer* npBuffer );
	int GetAchievePB( int nID, PBAchieve* npAchievePB );

	// DB PB
	int SetFromDBPB( PBDBAchieveBuffer* npBuffer );
	int GetTlvDBPB( PBDBAchieveBuffer* npBuffer );

	int PushHonor( ST_HONOR_DATA& nData );
	int GetHonorPBList( CMessageGetAllHonorResponse* npResponse );	

	int UpdateAchieveData( int nID, ST_ACHIEVE_DATA* npData, CAchieveCfgItem* npCfgItem );

	int UpdateAchieveDataInServer( int nID, int nValue, CAchieveCfgItem* npCfgItem );
};