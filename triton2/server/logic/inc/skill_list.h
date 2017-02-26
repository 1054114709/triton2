#ifndef _SKILL_LIST_H_
#define _SKILL_LIST_H_

#include "lk_vector.h"
#include "coretype.h"
#include "skill.h"
#include "timermanager.h"

#define MAX_SKILL_NUM 250

class CPropertyCharacter;
class PBSkillObject;
class PBSkillList;

struct BuffState 
{
	BuffState()
	{
		if(CObj::msCreateMode)
		{
			Initialize();
		}
	}

	~BuffState() {}

	void Initialize()
	{
		mBuffID = 0;
		mRand = 0;
		mTime = 0;
		mTarget = 0;
		mHP = 0;
	}

	int mBuffID;		// ����״̬��BUFFID
	int mRand;			// ���ֵĸ���
	int mTime;			// ��ȴʱ��
	int mTarget;		// Ŀ��
	int	mHP;			// HP�ٷֱ�
};

typedef lk::vector< BuffState, STATENUM > StateList;


//////////////////////////////////////////////////////////////////////////

/**
** �����б�ӿ��࣬���ģ����ʹ��
**
*/
class CSkillList
{
public:

	// �õ�������
	virtual int GetSkillNum( ) = 0;

	// �õ�ָ��ϵ��ļ��ܵȼ��ܺ�
	virtual int GetGenerPoint( int vGenerID ) = 0;

	// ͨ������ID�ҵ����ܶ���
	virtual CSkillObject* GetSkillObjectByID( unsigned int vSkillID ) = 0;

	// ͨ������ID�ҵ���������( >=0 ��Ч )
	virtual int GetSkillIndexByID( unsigned int usSkillID ) = 0;

	// ͨ�����������ҵ����ܶ���
	virtual CSkillObject* GetSkillObjectByIndex( unsigned int unSkillIndex ) = 0;

	// ���뼼��
	virtual bool InsertSkill( unsigned int vSkillID, int vMaxLevel, int nMWSkillID = 1 ) = 0;

	// ɾ������
	virtual void RemoveSkill( unsigned int vSkillID ) = 0;

	// ��PB�ṹ��������
	virtual void CreateFromTlv2( PBSkillList* pBuffer ) = 0;

	// �����ݸ�ֵ��PB�ṹ
	virtual void GetTlvBuffer2( PBSkillList* pBuffer ) = 0;

	// ��ü���������ֵ�̶�ֵ
	virtual unsigned int  GetFixNumber( CTemplateSkill::PASSINC_TYPE vType ) = 0;

	// ��ü���������ֵ�ٷֱ�
	virtual int  GetPerNumber( CTemplateSkill::PASSINC_TYPE vType ) = 0;

	// ���ĳ�����ܸı���
	virtual int GetValueByID( unsigned int vSkillID, CTemplateSkill::PASSINC_TYPE vType ) = 0;

	// ��ü������ӵ�״̬ID
	virtual int	GetStateID( StateList& vBuffList, CTemplateSkill::PASSINC_TYPE vType ) = 0;

	// ��ռ����б�
	virtual void Clean( ) = 0;

	// ��ռ���CD
	virtual void ClearCooldown( ) = 0;

	// ˢ�¼���CD
	virtual void RefreshCooldown() = 0;
};


//////////////////////////////////////////////////////////////////////////

template< int SIZE >
class CSkillListInstance : public CSkillList
{
private:
	unsigned short	mSkillNumber;
	CSkillObject	mSkillList[ SIZE ];					// �����б�

public:
	CSkillListInstance( );
	~CSkillListInstance( );

	int Initialize( );
	int Resume( );

	// ��ռ����б�
	void Clean( );

	// ��ռ����б�2
	int PartClean( );

	// �õ�������
	int GetSkillNum( ) { return mSkillNumber; }

	// �õ������б����ֵ
	int MaxSkillSize( ) { return SIZE; };

	// �õ�ָ��ϵ��ļ��ܵȼ��ܺ�
	int GetGenerPoint( int vGenerID );

	// ͨ������ID�ҵ����ܶ���
	CSkillObject* GetSkillObjectByID( unsigned int vSkillID );

	// ͨ������ID�ҵ���������( >=0 ��Ч )
	int GetSkillIndexByID( unsigned int usSkillID );

	// ͨ�����������ҵ����ܶ���
	CSkillObject* GetSkillObjectByIndex( unsigned int unSkillIndex );

	// ���뼼��  �������������������ܳ�ʼ�ȼ�
	bool InsertSkill( unsigned int vSkillID, int vMaxLevel, int nMWSkillID = 1 );

	// ���ͼ��ܵȼ� 
	bool SkillLevelDown( unsigned int vSkillID, int nLevel =1 );

	// ɾ������
	void RemoveSkill( unsigned int vSkillID );

	// ��PB�ṹ��������
	void CreateFromTlv2( PBSkillList* pBuffer );

	// �����ݸ�ֵ��PB�ṹ
	void GetTlvBuffer2( PBSkillList* pBuffer );

	// ��ü���������ֵ�̶�ֵ
	unsigned int  GetFixNumber( CTemplateSkill::PASSINC_TYPE vType );

	// ��ü���������ֵ�ٷֱ�
	int  GetPerNumber( CTemplateSkill::PASSINC_TYPE vType );

	// ���ĳ�����ܸı���
	int GetValueByID( unsigned int vSkillID, CTemplateSkill::PASSINC_TYPE vType );
	
	// ��ü������ӵ�״̬ID
	int	GetStateID( StateList& vBuffList, CTemplateSkill::PASSINC_TYPE vType );

	// ��ռ���CD
	void ClearCooldown( );

	// ˢ�¼���CD
	virtual void RefreshCooldown() ;

};



//////////////////////////////////////////////////////////////////////////
// CSkillList
//////////////////////////////////////////////////////////////////////////
template< int SIZE >
CSkillListInstance<SIZE>::CSkillListInstance( )
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

template< int SIZE >
CSkillListInstance<SIZE>::~CSkillListInstance( )
{
}

template< int SIZE >
int CSkillListInstance<SIZE>::Initialize( )
{
	Clean( );
	return 0;
}

template< int SIZE >
int CSkillListInstance<SIZE>::Resume( )
{
	return 0;
}

template< int SIZE >
void CSkillListInstance<SIZE>::Clean( )
{
	mSkillNumber = 0;
	::memset( mSkillList, 0, sizeof( mSkillList ) );
}

// �õ�ָ��ϵ��ļ��ܵȼ��ܺ�
template< int SIZE >
int CSkillListInstance<SIZE>::GetGenerPoint( int vGenerID )
{
	int tSkillPoint = 0;
	for ( int i = 0; i < mSkillNumber; i ++ )
	{
		CTemplateSkill* tpTempSkill = (CTemplateSkill*) CDataStatic::SearchSkill( mSkillList[ i ].GetSkillID(), mSkillList[ i ].GetSkillLevel() - mSkillList[ i ].GetIncLevel() );
		if ( tpTempSkill == NULL )
			continue;

		if ( tpTempSkill->mGenerID == vGenerID )
			tSkillPoint += mSkillList[ i ].GetSkillLevel() - mSkillList[ i ].GetIncLevel();
	}

	return tSkillPoint;
}

template< int SIZE >
CSkillObject* CSkillListInstance<SIZE>::GetSkillObjectByID( unsigned int vSkillID )
{
	for ( int i = 0; i < mSkillNumber; i ++ )
	{
		if ( mSkillList[ i ].GetSkillID() == vSkillID )
			return &mSkillList[ i ];
	}

	return NULL;
}

template< int SIZE >
int CSkillListInstance<SIZE>::GetSkillIndexByID( unsigned int usSkillID )
{
	for ( int i = 0; i < mSkillNumber; i ++ )
	{
		if ( mSkillList[ i ].GetSkillID() == usSkillID )
			return i;
	}

	return -1;
}

template< int SIZE >
CSkillObject* CSkillListInstance<SIZE>::GetSkillObjectByIndex( unsigned int unSkillIndex )
{
	if( unSkillIndex >= mSkillNumber )
	{
		return NULL;
	}

	return &mSkillList[ unSkillIndex ];
}


//************************************
// Method:    InsertSkill
// FullName:  CSkillList::InsertSkill
// Access:    public 
// Returns:   bool
// Qualifier: ���뼼��ʱ�����޸ļ�����ȴʱ��
// Parameter: unsigned short vSkillID
// Parameter: int vMaxLevel
// Parameter: unsigned int & vpSkillID
// Parameter: int & vIndex
//************************************
template< int SIZE >
bool CSkillListInstance<SIZE>::InsertSkill( unsigned int vSkillID, int vMaxLevel, int nMWSkillID /*= 1*/ )
{
	CTemplateNormalSkill* tpSkill = ( CTemplateNormalSkill* )CDataStatic::SearchSkill( vSkillID, vMaxLevel );
	if( tpSkill == NULL )
	{
		LOG_ERROR( "pro", "[%s:%d] skill id %d level %d not found", __FUNCTION__, __LINE__, vSkillID, vMaxLevel );
		return false;
	}

	for ( unsigned int i = 0; i < ARRAY_CNT( mSkillList ); i ++ )
	{

		if ( mSkillList[ i ].GetSkillID() == vSkillID )
		{
			if ( mSkillList[ i ].GetSkillLevel() - mSkillList[ i ].GetIncLevel( ) == (unsigned int)vMaxLevel )
				return false;

			mSkillList[ i ].SetSkillLevel( mSkillList[ i ].GetSkillLevel() + 1 ) ;
			mSkillList[ i ].SetOriginalCooldown( tpSkill->mCDTime );

			return true;
		}

		if ( mSkillList[ i ].GetSkillID() == 0 )
		{
			mSkillList[ i ].SetSkillID( vSkillID );
			mSkillList[ i ].SetCooldown( 0 );
			mSkillList[ i ].SetSkillLevel( nMWSkillID );
			mSkillList[ i ].SetOriginalCooldown( tpSkill->mCDTime );
			mSkillNumber = i + 1;						// changed by lixi

			return true;
		}
	}

	return false;
}


//************************************
// Method:    SkillLevelDown	
// Qualifier: ���ܵȼ����� ������Сϴ������
//************************************
template< int SIZE >
bool CSkillListInstance<SIZE>::SkillLevelDown( unsigned int vSkillID, int nLevel )
{
	for ( unsigned int i = 0; i < ARRAY_CNT( mSkillList ); i ++ )
	{
		if ( mSkillList[ i ].GetSkillID() == vSkillID )
		{
			mSkillList[ i ].SetSkillLevel( mSkillList[ i ].GetSkillLevel() - nLevel);
			return true;
		}
	}

	return false;
}



template< int SIZE >
void CSkillListInstance<SIZE>::RemoveSkill( unsigned int vSkillID )
{
	for ( int i = 0; i < mSkillNumber; i ++ )
	{
		if ( mSkillList[ i ].GetSkillID() == vSkillID )
		{
			// �������һ������Ҫ���������洢
			// TODO: װ������ļ���,��Ϊ���ܴ��м�ɾ��,���������Ժ���
			if( i != mSkillNumber-1 )
			{
				for ( int j = i; j < mSkillNumber; j ++ )
					mSkillList[ j ] = mSkillList[ j + 1 ];
			}
			mSkillList[ mSkillNumber-1 ].Initialize();// ��ʼ�������1���ڵ�
			mSkillNumber --;
			break;
		}
	}
}

template< int SIZE >
void CSkillListInstance<SIZE>::CreateFromTlv2( PBSkillList* pBuffer )
{
	mSkillNumber = pBuffer->skillnumber();
	if ( mSkillNumber > ARRAY_CNT(mSkillList) )
	{
		LOG_ERROR( "pro", "[%s:%d] skill num %d over max %d ", __FUNCTION__, __LINE__, mSkillNumber, ARRAY_CNT(mSkillList) );
		mSkillNumber = ARRAY_CNT(mSkillList);
	}

	for ( int i = 0; i < mSkillNumber && i < pBuffer->skillobjects_size(); i ++ )
	{
		PBSkillObject* tpPBSkillObject = pBuffer->mutable_skillobjects( i );
		mSkillList[ i ].SetSkillID( tpPBSkillObject->skillid() );
		mSkillList[ i ].SetSkillLevel( tpPBSkillObject->skilllevel() );
		mSkillList[ i ].SetCooldown( tpPBSkillObject->cooldown() );
		mSkillList[ i ].SetIncLevel( tpPBSkillObject->inclevel() );
	}
}


template< int SIZE >
void CSkillListInstance<SIZE>::GetTlvBuffer2( PBSkillList* pBuffer )
{
	// ��ֹ����Խ��
	if( mSkillNumber > ARRAY_CNT(mSkillList) )
	{
		mSkillNumber = ARRAY_CNT( mSkillList );
	}

	pBuffer->set_skillnumber( mSkillNumber );

	for ( int i = 0; i < mSkillNumber; i ++ )
	{
		PBSkillObject* tpPBSkillObject = pBuffer->add_skillobjects();

		tpPBSkillObject->set_skillid( mSkillList[ i ].GetSkillID() );
		tpPBSkillObject->set_skilllevel( mSkillList[ i ].GetSkillLevel() );
		if( mSkillList[ i ].GetCooldown() != 0 )
			tpPBSkillObject->set_cooldown( mSkillList[ i ].GetCooldown() );
		if( mSkillList[ i ].GetIncLevel() != 0 )
			tpPBSkillObject->set_inclevel( mSkillList[ i ].GetIncLevel() );
	}
}

// ��ü������ӹ̶���ֵ
template< int SIZE >
unsigned int CSkillListInstance<SIZE>::GetFixNumber(  CTemplateSkill::PASSINC_TYPE vType )
{
	unsigned int tValue = 0;
	int i = 0;

	for( i = 0; i < mSkillNumber; i++ )
	{	
		int tSkillLevel = 0;													
		tSkillLevel += mSkillList[ i ].GetSkillLevel();		
		CTemplateSkill* tpSkillTempl = (CTemplateSkill*) CDataStatic::SearchSkill( mSkillList[ i ].GetSkillID(), tSkillLevel );	
		if ( tpSkillTempl == NULL )
		{
			LOG_ERROR( "pro", "[%s:%d] can't find skill id %d, level %d", __FUNCTION__, __LINE__, mSkillList[ i ].GetSkillID(), tSkillLevel );
			continue;																					
		}

		// TODO: ���ǲ߻�2��һ�㲻����4��funcidһ����buff, ��ʱ��if .. else if .. else if ...
		if ( tpSkillTempl->mSkillFuncID1 == vType )							
			tValue += tpSkillTempl->mParameter1[ 0 ];											
		else if ( tpSkillTempl->mSkillFuncID2 == vType )							
			tValue += tpSkillTempl->mParameter2[ 0 ];													
		else if ( tpSkillTempl->mSkillFuncID3 == vType )							
			tValue += tpSkillTempl->mParameter3[ 0 ];													
		else if ( tpSkillTempl->mSkillFuncID4 == vType )							
			tValue += tpSkillTempl->mParameter4[ 0 ];															
	}

	return tValue;
}


template< int SIZE >
int CSkillListInstance<SIZE>::GetPerNumber(CTemplateSkill::PASSINC_TYPE vType )
{
	int tValue = 0;

	for( int i = 0; i < mSkillNumber; i++ )
	{														
		int tSkillLevel = mSkillList[ i ].GetSkillLevel();		
		CTemplateSkill* tpSkillTempl = (CTemplateSkill*) CDataStatic::SearchSkill( mSkillList[ i ].GetSkillID(), tSkillLevel );	
		if ( tpSkillTempl == NULL )																	
		{
			LOG_ERROR( "pro", "[%s:%d] can't find skill id %d, level %d", __FUNCTION__, __LINE__, mSkillList[ i ].GetSkillID(), tSkillLevel );
			continue;																					
		}

		// TODO: ���ǲ߻�2��һ�㲻����4��funcidһ����buff, ��ʱ��if .. else if .. else if ...
		if ( tpSkillTempl->mSkillFuncID1 == vType )							
			tValue += tpSkillTempl->mParameter1[ 0 ];													
		else if ( tpSkillTempl->mSkillFuncID2 == vType )							
			tValue += tpSkillTempl->mParameter2[ 0 ];													
		else if ( tpSkillTempl->mSkillFuncID3 == vType )							
			tValue += tpSkillTempl->mParameter3[ 0 ];													
		else if ( tpSkillTempl->mSkillFuncID4 == vType )							
			tValue += tpSkillTempl->mParameter4[ 0 ];															
	}

	return tValue;
}


template< int SIZE >
int CSkillListInstance<SIZE>::GetValueByID(  unsigned int vSkillID, CTemplateSkill::PASSINC_TYPE vType )
{
	unsigned int tValue = 0;
	for( int i = 0; i < mSkillNumber; i++ )
	{	
		int tSkillLevel = mSkillList[ i ].GetSkillLevel();		
		CTemplateSkill* tpSkillTempl = (CTemplateSkill*) CDataStatic::SearchSkill( mSkillList[ i ].GetSkillID(), tSkillLevel );	
		if ( tpSkillTempl == NULL )
		{
			LOG_ERROR( "pro", "[%s:%d] can't find skill id %d, level %d", __FUNCTION__, __LINE__, mSkillList[ i ].GetSkillID(), tSkillLevel );
			continue;																					
		}

		if ( tpSkillTempl->mSkillFuncID1 == vType )	
		{
			if ( vSkillID == tpSkillTempl->mParameter1[ 0 ] )
				tValue += tpSkillTempl->mParameter1[ 1 ];											
		}
		else if ( tpSkillTempl->mSkillFuncID2 == vType )							
		{
			if ( vSkillID == tpSkillTempl->mParameter2[ 0 ] )
				tValue += tpSkillTempl->mParameter2[ 1 ];													
		}
		else if ( tpSkillTempl->mSkillFuncID3 == vType )							
		{
			if ( vSkillID == tpSkillTempl->mParameter3[ 0 ] )
				tValue += tpSkillTempl->mParameter3[ 1 ];													
		}
		else if ( tpSkillTempl->mSkillFuncID4 == vType )							
		{
			if ( vSkillID == tpSkillTempl->mParameter4[ 0 ] )
				tValue += tpSkillTempl->mParameter4[ 1 ];															
		}
	}

	return tValue;
}


template< int SIZE >
int	CSkillListInstance<SIZE>::GetStateID(StateList& vBuffList, CTemplateSkill::PASSINC_TYPE vType )
{
	for( int i = 0; i < mSkillNumber; i++ )
	{	
		int tSkillLevel = mSkillList[ i ].GetSkillLevel();		
		CTemplateSkill* tpSkillTempl = (CTemplateSkill*) CDataStatic::SearchSkill( mSkillList[ i ].GetSkillID(), tSkillLevel );	
		if ( tpSkillTempl == NULL )
		{
			LOG_ERROR( "pro", "[%s:%d] can't find skill id %d, level %d", __FUNCTION__, __LINE__, mSkillList[ i ].GetSkillID(), tSkillLevel );
			continue;																					
		}

		if ( tpSkillTempl->mSkillFuncID1 == vType )	
		{
			BuffState tBuff;
			tBuff.mBuffID = tpSkillTempl->mParameter1[ 0 ];
			tBuff.mRand = tpSkillTempl->mParameter1[ 1 ];
			tBuff.mTime = tpSkillTempl->mParameter1[ 2 ];	
			tBuff.mTarget = tpSkillTempl->mParameter1[ 3 ];  // Ǳ����(��ͬ)�� mTarget��mHPֻ��ͬʱ����һ����Ŀǰ��3
			tBuff.mHP = tpSkillTempl->mParameter1[ 3 ];		// ����Paramter[3]����ֵ��������3������һ��Paramter��5�����ǲ߻�ģ�廹һֱδ��
			vBuffList.push_back( tBuff );
		}
		else if ( tpSkillTempl->mSkillFuncID2 == vType )							
		{
			BuffState tBuff;
			tBuff.mBuffID = tpSkillTempl->mParameter2[ 0 ];
			tBuff.mRand = tpSkillTempl->mParameter2[ 1 ];
			tBuff.mTime = tpSkillTempl->mParameter2[ 2 ];
			tBuff.mTarget = tpSkillTempl->mParameter2[ 3 ];
			tBuff.mHP = tpSkillTempl->mParameter2[ 3 ];
			vBuffList.push_back( tBuff );
		}
		else if ( tpSkillTempl->mSkillFuncID3 == vType )							
		{
			BuffState tBuff;
			tBuff.mBuffID = tpSkillTempl->mParameter3[ 0 ];
			tBuff.mRand = tpSkillTempl->mParameter3[ 1 ];
			tBuff.mTime = tpSkillTempl->mParameter3[ 2 ];
			tBuff.mTarget = tpSkillTempl->mParameter3[ 3 ];
			tBuff.mHP = tpSkillTempl->mParameter3[ 3 ];
			vBuffList.push_back( tBuff );
		}
		else if ( tpSkillTempl->mSkillFuncID4 == vType )							
		{
			BuffState tBuff;
			tBuff.mBuffID = tpSkillTempl->mParameter4[ 0 ];
			tBuff.mRand = tpSkillTempl->mParameter4[ 1 ];
			tBuff.mTime = tpSkillTempl->mParameter4[ 2 ];
			tBuff.mTarget = tpSkillTempl->mParameter4[ 3 ];
			tBuff.mHP = tpSkillTempl->mParameter4[ 3 ];
			vBuffList.push_back( tBuff );
		}
	}

	return 0;
}

template< int SIZE >
void CSkillListInstance<SIZE>::ClearCooldown( )
{
	for( int i = 0; i < mSkillNumber; i++ )
	{														
		mSkillList[ i ].SetCooldown( 0 );														
	}
}

template< int SIZE >
int CSkillListInstance<SIZE>::PartClean( )
{
	int tIDList[ SIZE ] = { 0 };
	int tLevelList[ SIZE ] = { 0 };
	int tNumber = 0;
	int tValue = 0;
	for( int i = 0; i < mSkillNumber; i++ )
	{	
		int tSkillLevel = mSkillList[ i ].GetSkillLevel();		
		CTemplateSkill* tpSkillTempl = (CTemplateSkill*) CDataStatic::SearchSkill( mSkillList[ i ].GetSkillID(), tSkillLevel );	
		if ( tpSkillTempl == NULL )
		{
			LOG_ERROR( "pro", "[%s:%d] can't find skill id %d, level %d", __FUNCTION__, __LINE__, mSkillList[ i ].GetSkillID(), tSkillLevel );
			continue;																					
		}
		if ( tpSkillTempl->mCanClean != 0 )
		{
			tIDList[ tNumber ] = mSkillList[ i ].GetSkillID();
			tLevelList[ tNumber ] = mSkillList[ i ].GetSkillLevel();
			tNumber++;
		}
		else
		{
			tValue += mSkillList[ i ].GetSkillLevel();
		}
	}
	Clean( );
	for ( int i = 0; i < tNumber; i++ )
	{
		for ( int j = 0; j < tLevelList[ i ]; j++ )
		{
			InsertSkill( tIDList[ i ], tLevelList[ i ], 1 );
		}
	}
	return tValue;
}



// ˢ�¼���CD
template< int SIZE >
void CSkillListInstance<SIZE>::RefreshCooldown( )
{
	int nLeftSec = 0;
	int nLeftMillSec = 0;

	for( int i = 0; i < mSkillNumber; i++ )
	{														
		if( mSkillList[ i ].GetCDTimer() != INVALID_OBJ_ID )
		{
			int nGetTimerRet = CTimerMng::GetSingletonPtr()->GetLeftTime( mSkillList[ i ].GetCDTimer(), nLeftSec, nLeftMillSec );
			if( nGetTimerRet == 0)
			{
				mSkillList[ i ].SetCooldown( nLeftMillSec );
			}
		}
	}

}



#endif // _SKILL_LIST_H_