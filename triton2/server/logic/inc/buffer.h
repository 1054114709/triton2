#pragma once
#include "coretype.h"
#include "protype.h"
#include "sceneobj_manager.h"
#include "promessage_pb.hxx.pb.h"
#include "share_define.h"
#include "property_pb.hxx.pb.h"
#include "lk_vector.h"
#include "lk_hashmap.h"
#include "template.h"
#include "timer_define.h"
#include "skill_list.h"

class CProperty;
class CPropertyCharacter;
class CPropertyPlayer;
class CPropertyNPC;
class CPropertyPet;
class CEntityCharacter;
class CEntityResultList;
class CEntityPlayer;
class CTransform
{
public:
	CTransform(){ Clear(); }
	~CTransform() {}

	void Clear()
	{
		mHasTransform = 0;
		mSexID = 0;
		mStateID = 0;
		mWeaponID = 0;
		mClothID = 0;
		mFashionID = 0;
		mNpcID = 0;
	}	

public:
	int				mHasTransform;		// �Ƿ���ڱ���״̬��0�����ڣ�>0����( buffid )
	int				mSexID;			// �Ա�
	int				mStateID;		// ����״̬
	int				mWeaponID;		// ����ID
	int				mClothID;		// �·�ID
	int				mFashionID;		// ʱװID
	int				mNpcID;			// ����ID
};

class CBuffObject 
{
public:
	unsigned int	mBuffID;			// Buffģ��ID
	int				mPersistTime;		// Buff����ʱ�䣨����Ϊ��λ��
	unsigned int	mSrcEntityID;		// �ͷ���ID
	int				mLastInterval;		// �ϴ�ʱ����
	int				mTimerType;			// ʱ������( ���ڷ������洢,����ģ����� )
	int				mParames[ MAX_BUFFFUN_COUNT ];		// ��չ����
	int				mParames2[ MAX_BUFFFUN_COUNT ];		// ��չ����2
	int				mBackDamage;		// �����˺�����
	int				mAttack;			// �˺�ֵ
	int				mBuffTimerID;		// buff��ʱ��ID
	int				mDstEntityID;		// buff����ʵ��
	int				mBuffSuperCount;	// buff���Ӳ���
	int				mListID;	

public:
	CBuffObject( ) 
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

	~CBuffObject( ) {}

	int Initialize( )
	{
		mBuffID = 0;
		mPersistTime = 0;
		mSrcEntityID = 0;
		mLastInterval = 0;
		mTimerType = 0;
		mBackDamage = 0;
		mAttack = 0;
		memset( mParames, 0, sizeof( mParames ) );
		memset( mParames2, 0, sizeof( mParames2 ) );
		mBuffTimerID = INVALID_OBJ_ID;
		mDstEntityID = 0;
		mBuffSuperCount = 0;

		mListID = 0;
		return 0;
	}

	int Resume( )
	{
		return 0;
	}

	// Buff����ֵӰ����ֵ(�̶���ٷֱ�)
	unsigned int GetAffectNumber( CTemplateBuff::BUFF_FUN_TYPE vBuffType );

	// Get & Set BuffTimerID
	int GetBuffTimerID( ) { return mBuffTimerID; }
	void SetBuffTimerID( int nTimeriD ) { mBuffTimerID = nTimeriD ;}

	// Get & Set SrcEntityID
	int GetBuffSrcEntityID() { return mSrcEntityID; }
	void SetBuffSrcEntityID( int nSrcEntityiD ) { mSrcEntityID = nSrcEntityiD; }

	void ChangeParames( int vBuffID, int vIndex, int vParames  );
	void ChangeParames2( int vBuffID, int vIndex, int vParames2 );

	void SetPersistTime( int nTime ) { mPersistTime = nTime; }
	int GetPersistTime( ) { return mPersistTime; }

	// �õ�buff�����ü��; -1��ʾʧ�ܣ�0��ʾ�ǳ���������buff; >0��ʾ�Ǽ��������buff
	int GetBuffActionTime( ) ;

};


/************************************************************************/
/*  Buff�б� ( �������Ե��� )                                                                     */
/************************************************************************/
class CBuffList
{
public:
	enum { MAX_BUFF_NUM = 24, };
public:
	unsigned int	mBuffNumber;
	CBuffObject		mBuffList[ MAX_BUFF_NUM ]; // BUFF�б�
	//	static int 		sBuffListID;
	int				mBuffListID;
	CTransform		mTransform;

public:
	CBuffList( ) 
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

	~CBuffList( )
	{

	}

	int Initialize( )
	{
		Clean( );
		return 0;
	}

	int Resume( )
	{
		return 0;
	}

public:
	void Clean( )
	{
		mBuffNumber = 0;
		mBuffListID = 0;
		::memset( mBuffList, 0, sizeof( mBuffList ) );
		::memset( &mTransform, 0, sizeof( mTransform ) );
	}

	CBuffObject* InsertBuff( unsigned int vBuffID, int vPersistTime, CEntityCharacter* pSrcEntity, unsigned int& vLastBuffID, int vAttack, CEntityCharacter* pDstEntity, int* vListID, int* vResultCode );


	int GetBuffNum( ) { return mBuffNumber; }

	int RemoveBuff( unsigned int vBuffID, CEntityCharacter* pEntity, int* vListID = 0 );

	// �������buff, ������ʱ��
	int RemoveAllBuff( CEntityCharacter* pEntity );

	void CreateFromTlv2( CPropertyCharacter* vpCharacter, PBBuffList* pBuffer );	

	void GetTlvBuffer2( PBBuffList* pBuffer );

	// �õ�����С����ʾ��buff��Ϣ
	void GetTlvBufferTeamShow( PBBuffList* pBuffer );

	// �õ��������������ʾ��buff��Ϣ
	void GetTlvBufferShow( PBBuffList* pBuffer );

	unsigned int GetFixNumber( CTemplateBuff::BUFF_FUN_TYPE vBuffType );

	// �õ�BuffList����ֵӰ��İٷֱ�
	int GetPerNumber( CTemplateBuff::BUFF_FUN_TYPE vBuffType );

	CBuffObject* GetBuffObjectByID( int nBuffID );

	// ͨ������ȡ��buff obj
	CBuffObject& GetBuffObjectByIndex( int nIdx ) { return mBuffList[nIdx]; }

	// �Ƿ���buff
	bool HasBuff( int nBuffID );

	// ˢ��Buffʣ��ʱ��
	void RefreshBuffLeftTime( );

	// ���Ʊ���
	void SetTransform( CEntityCharacter *pEntity, int nBuffID );

	// ��ñ���
	void GetTransform( PBTransform *pTran );

	// ����з���ɽ����; >0��ʾBuffID
	int HasTransform( ) { return mTransform.mHasTransform; }
};