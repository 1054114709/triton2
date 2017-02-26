#pragma once

class CMessage;
class CEntity;
class CMapObject;


// �����ɼ����е����
template< class Check >
struct SeenPlayerContainserSearcher
{
	SeenPlayerContainserSearcher( Check& rCheck, std::vector<CEntity*>& rEntitySet) 
		: m_Check( rCheck ), m_rEntitys(rEntitySet) {}


	void Visit( CEntity* pEntity );


	Check& m_Check;							// �����(��������)
	std::vector<CEntity*>& m_rEntitys;		
};

// �����ɼ����е�NPC
template< class Check >
struct SeenNpcContainserSearcher
{
	SeenNpcContainserSearcher( Check& rCheck, std::vector<CEntity*>& rEntitySet) 
		: m_Check( rCheck ), m_rEntitys(rEntitySet) {}


	void Visit( CEntity* pEntity );


	Check& m_Check;							// �����(��������)
	std::vector<CEntity*>& m_rEntitys;		
};




// ������ͼ�����ڵ���������ʵ��,��Check�����ж��Ƿ����
template< class Check >
struct MapRegionEntitySearcher
{
	MapRegionEntitySearcher(Check& rCheck) : m_Check( rCheck ) {}
	MapRegionEntitySearcher(Check& rCheck, CWTPoint& rTopLeft, CWTPoint& rBottomRight) 
		: m_Check( rCheck ), m_TopLeft( rTopLeft ), m_BottomRight( rBottomRight ) 
	{}

	Check& m_Check;							// �����(��������)
	CWTPoint& m_TopLeft;					// ���Ͻ�
	CWTPoint& m_BottomRight;				// ���½�

	void Visit( CMapObject* pMap );			// ������
};



// ����������
enum emObjectFunRsult 
{
	EM_OBJFUN_NONE				= 0, // û�н��
	EM_OBJFUN_ENTITY_NOTEXIST	= 1, // ����ID������
	EM_OBJFUN_ENTITY_TERMINATE	= 2, // ��ǰ����
};


// �ɹ���ͼ��ѯ�õ�
class ICheckerForMapSearch
{
public:

	virtual bool operator() ( int ) = 0;
	virtual int GetResult( ) = 0;
	virtual void SetResult( int  ) = 0; 
};


/**
	1.�����ɼ����е�ʵ�壬ͬʱ����ӵ�ʵ��ҲҪ��ɼ�������Ӹ����
	2.�������ɼ����������ң���ô�Ѹ���ҷŵ������У��Ա���淢����ʵ����Ϣ�����
	3.�������ɼ��������NPC,��ô�Ѹ�NPC�ŵ�NPC�����У��Ա�������ҷ��ʹ���NPC����Ϣ
	4.�������⴦��
*/
class VisibleViewEntityChecker : public ICheckerForMapSearch
{
public:

	VisibleViewEntityChecker(CEntityPlayer* pSelf) : m_pSelf( pSelf ), mResult( 0 )  {}

	bool operator() ( int nEntityID )
	{
		CEntity* pTarget = (CEntity*)CSceneObjManager::GetSingletonPtr()->GetObject( nEntityID );
		if( pTarget == NULL )
		{
			mResult = EM_OBJFUN_ENTITY_NOTEXIST;
			LOG_ERROR( "default", "[%s:%d] entity %d can't find entity %d", __FUNCTION__, __LINE__,
				m_pSelf->GetEntityID(),	nEntityID );
			return false;
		}

		if( pTarget->IsVisibleFor( m_pSelf ) )
		{	
			m_pSelf->AddViewEntity( pTarget );
			pTarget->AddViewEntity( m_pSelf );

			if( pTarget->IsPlayer() )
				m_Players.push_back( (CEntityPlayer*)pTarget );
			else
				m_Npcs.push_back( pTarget );
		}
		else
		{
			// ������Ҫ�Ǵ������壬������ҿ��������壬��������Ŀɼ�����Ҫ����ң�������
			// ����ʱΪ�˼��������㲥������Ϣ
			if( pTarget->IsPedal() )
			{
				pTarget->AddViewEntity( m_pSelf );
			}
		}

		return true;
	}

	inline int GetResult( ) { return mResult; }
	inline void SetResult( int nRet ) { mResult = nRet; }

	CEntityPlayer* m_pSelf;
	std::vector<CEntity*>		m_Npcs;		// ʵ������
	std::vector<CEntityPlayer*> m_Players;	// �������
	int mResult; // ���ڱ����м���
};


/**
	1.NPC��ɼ��������ʵ�壬ͬʱ����ӵ�ʵ��ҲҪ��ɼ�������Ӹ����
	2.�������ɼ��������NPC,��ô�Ѹ�NPC�ŵ�NPC�����У��Ա�������ҷ��ʹ���NPC����Ϣ
	3.�������⴦��
*/
class VisibleViewPlayerChecker : public ICheckerForMapSearch
{
public:

	VisibleViewPlayerChecker(CEntity* pSelf) : m_pNPCSelf( pSelf ),mResult( 0 )  {}

	bool operator() (int nEntityID)
	{
		CEntity* pTarget = (CEntity*)CSceneObjManager::GetSingletonPtr()->GetObject( nEntityID );
		if( pTarget == NULL )
		{
			mResult = EM_OBJFUN_ENTITY_NOTEXIST;
			LOG_ERROR( "default", "[%s:%d] entity %d can't find entity %d", __FUNCTION__, __LINE__,
				m_pNPCSelf->GetEntityID(),	nEntityID );
			return false;
		}

		if( m_pNPCSelf->IsVisibleFor( pTarget ) )
		{	
			m_pNPCSelf->AddViewEntity( pTarget );
			pTarget->AddViewEntity( m_pNPCSelf );

			if( pTarget->IsPlayer() )
				m_Players.push_back( (CEntityPlayer*)pTarget );

		}
		else
		{
			// ���������⴦��
			if( m_pNPCSelf->IsPedal() )
			{
				m_pNPCSelf->AddViewEntity( pTarget );
			}
		}

		return true;
	}

	inline int GetResult( ) { return mResult; }
	inline void SetResult( int nRet ) { mResult = nRet; }

	CEntity* m_pNPCSelf; // �Լ��Ƿ����
	std::vector<CEntityPlayer*> m_Players;	// �������
	int mResult; // ���ڱ����м���
};


/**
	1.���ɾ���ɼ����е�ʵ�壬ͬʱ��ɾ����ʵ��ҲҪ�ӿɼ�����ɾ�������
	2.����Ǵӿɼ�����ɾ����ң���ô�Ѹ���ҷŵ������У��Ա���淢����ʵ����Ϣ�����
	3.����Ǵӿɼ�����ɾ��NPC,��ô�Ѹ�NPC�ŵ�NPC�����У��Ա�������ҷ�������NPC����Ϣ
	4.�������⴦��
*/
class VisibleViewEntityDeleter : public ICheckerForMapSearch
{
public:

	VisibleViewEntityDeleter(CEntityPlayer* pSelf) : m_pSelf( pSelf ),mResult( 0 )  {}

	bool operator() (int nEntityID)
	{
		CEntity* pTarget = (CEntity*)CSceneObjManager::GetSingletonPtr()->GetObject( nEntityID );
		if( pTarget == NULL )
		{
			mResult = EM_OBJFUN_ENTITY_NOTEXIST;
			LOG_ERROR( "default", "[%s:%d] entity %d can't find entity %d", __FUNCTION__, __LINE__,
				m_pSelf->GetEntityID(),	nEntityID );
			return false;
		}


		if( pTarget->IsVisibleFor( m_pSelf ) )
		{	
			pTarget->DeleteViewEntity( m_pSelf );
			m_pSelf->DeleteViewEntity( pTarget );

			if( pTarget->IsPlayer() )
				m_Players.push_back( (CEntityPlayer*)pTarget );
			else
				m_Npcs.push_back( pTarget );

		}
		else
		{
			// ��Ҷ����岻�ɼ��Ļ���ҲҪ������Ŀɼ���������ɾ��
			if( pTarget->IsPedal() )
			{
				pTarget->DeleteViewEntity( m_pSelf );
			}
		}

		return true;
	}


	inline int GetResult( ) { return mResult; }
	inline void SetResult( int nRet ) { mResult = nRet; }


	CEntityPlayer* m_pSelf;
	std::vector<CEntity*>		m_Npcs;		// ʵ������
	std::vector<CEntityPlayer*> m_Players;	// �������
	int mResult; // ���ڱ����м���
};


/**
	1.NPCɾ���ɼ����е�ʵ�壬ͬʱ��ɾ����ʵ��ҲҪ�ӿɼ�����ɾ����NPC
	2.����Ǵӿɼ�����ɾ����ң���ô�Ѹ���ҷŵ������У��Ա���淢����ʵ����Ϣ�����
	3.�������⴦��
*/
class VisibleViewPlayerDeleter : public ICheckerForMapSearch
{
public:

	VisibleViewPlayerDeleter(CEntity* pSelf) : m_pNpcSelf( pSelf ),mResult(0)  {}
	
	bool operator() (int nEntityID)
	{
		CEntity* pTarget = (CEntity*)CSceneObjManager::GetSingletonPtr()->GetObject( nEntityID );
		if( pTarget == NULL )
		{
			mResult = EM_OBJFUN_ENTITY_NOTEXIST;
			LOG_ERROR( "default", "[%s:%d] entity %d can't find entity %d", __FUNCTION__, __LINE__,
				m_pNpcSelf->GetEntityID(),	nEntityID );
			return false;
		}


		if( pTarget->IsVisibleFor( m_pNpcSelf ) )
		{	
			m_pNpcSelf->DeleteViewEntity( pTarget );
			pTarget->DeleteViewEntity( m_pNpcSelf );
	
			if( pTarget->IsPlayer() )
				m_Players.push_back( (CEntityPlayer*)pTarget );	
		}
		else
		{
			// �������⴦��
			if( m_pNpcSelf->IsPedal() )
			{
				m_pNpcSelf->DeleteViewEntity( pTarget );
			}
		}

		return true;
	}


	inline int GetResult( ) { return mResult; }
	inline void SetResult( int nRet ) { mResult = nRet; }

	CEntity* m_pNpcSelf;
	std::vector<CEntityPlayer*> m_Players;	// �������
	int mResult; // ���ڱ����м���
};


// �ɹ���ʵ������, ��Ҫ���ڹ�����ٻ�����������Ŀ��
class AttackableEntityChecker
{
public:

	AttackableEntityChecker( CEntityCharacter* pSrcEntity ) : m_pSrcEntity( pSrcEntity ) { }

	bool operator() (CEntity* pTarget);

	CEntityCharacter* m_pSrcEntity;
};


// ��ͼ�������ʵ��
class MapPlayerChecker : public ICheckerForMapSearch
{
public:

	MapPlayerChecker(  ):mNum(0), mDistance(10000), mLineID(-1), mEntityPtr(NULL),mResult(0) { }
	CEntityPlayer* mPlayerList[MAX_WEDDINGHALL_PLAYENUM];
	int			   mNum;
	int			   mDistance;
	int			   mLineID;
	CEntity		   *mEntityPtr;		
	int				mResult;
	inline int GetResult( ) { return mResult; }
	inline void SetResult( int nRet ) { mResult = nRet; }

	bool operator()( int nEntityID )
	{		
		if ( mNum >= MAX_WEDDINGHALL_PLAYENUM )
		{
			mResult = EM_OBJFUN_ENTITY_TERMINATE;
			return false;
		}
			
		CEntity* tpEntity = (CEntity*)CSceneObjManager::GetSingletonPtr()->GetObject( nEntityID );
		if ( tpEntity->IsPlayer() == true )
		{
			mPlayerList[mNum] = ( CEntityPlayer * )tpEntity;
			++mNum;		
		}			
		return true;
	}		
			
	bool operator()( CEntity *pEntity )			
	{
		if ( pEntity->IsPlayer() == true )
		{
			if ( mNum >= MAX_WEDDINGHALL_PLAYENUM )
			{
				mResult = EM_OBJFUN_ENTITY_TERMINATE;
				return false;
			}
			
			bool bAddPlayer = false;
			if ( mEntityPtr == NULL )
			{
				bAddPlayer = true;
			}
			else
			{
				if ( mEntityPtr->IsWithinDistance( pEntity, mDistance ) == true )
				{
					if ( mLineID < 0 )
					{
						bAddPlayer = true;
					}
					else
					{
						if ( ( ( CEntityPlayer * )pEntity )->GetNationality() == mLineID )
						{
							bAddPlayer = true;
						}
					}
				}				
			}
			
			if ( bAddPlayer == true )
			{
				mPlayerList[mNum] = ( CEntityPlayer * )pEntity;
				++mNum;					
			}		
		}			
		return true;
	}

};

// Ѱ��һ������npc
class MapFuncNpcChecker : public ICheckerForMapSearch 
{
public:

	MapFuncNpcChecker():mEntityID(0){ }
	int  mEntityID;
	
	bool operator()( int nEntityID ) 
	{
		CEntity* tpEntity = (CEntity*)CSceneObjManager::GetSingletonPtr()->GetObject( nEntityID );
		if ( tpEntity != NULL & tpEntity->IsFunNpc() == true )
		{
			mEntityID = nEntityID;
			return false;
		}				
		return true;
	}

	int GetResult( ) { return EM_OBJFUN_NONE; }
	void SetResult( int )  {;} 
};

