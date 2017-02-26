//================================================================================
// battlemgr.h
//================================================================================
#pragma  once
#include "module_manager.h"
#include "corpstype.h"
#include "corps.h"
#include "family.h"
#include "familytype.h"
#include "shm.h"
#include "lk_hashmap.h"
#include "gateobj_define.h"
#include "corpsinfo_pb.hxx.pb.h"   
#include "entity.h"


//#include "gatelogic.h"
//#include "corpservice.h"
//using namespace GateServer;	
//ս��������
class CBattleMgr : public CSingleton< CBattleMgr >
{
public:
	CBattleMgr();
	~CBattleMgr();
	int Initialize( );
	int Resume( );
	static CSharedMem* mShmPtr;
	void * operator new( size_t tsize );
	void   operator delete( void *pPointer );
	static unsigned int CountSize();

public:
	void OnTimerCheckState();

public:
	///���ݿ�ͬ������
	void LoadFromDB( int nStart, int nTotalCount );
	//void GetNumFromDB();
	void OnSessionLoadFromDB( CMessage* pMessage, int nStart, int nTotalCount );
	//void OnSessionGetNumFromDB();
	int SynDataToDB();

public:
	///��ʼ��һ���µ�ս����Ϣ
	int InitBattle(int nAttCorpsID, int nDefCorpsID, int nType, int nNpcID, int nMapID);
	void StartBattle( KEY_TYPE nKey, int nNpcID );
	void GetBattle( KEY_TYPE nKey, int& nSrcCorpsID, int& nDesCorpsID, int& nType, int& nNpcID, int& nMapID );
	int GetBattle( int nNpcID, int &nSrcCorpsID, int& nDesCorpsID, int& nMapID );
	int DelBattle( int nNpcID );
	int DelBattle( KEY_TYPE nKey );

	bool InChallegeBattle( int nCorpsID );
	KEY_TYPE GetBattleKey( int nNpcID, int nType );
	bool IsInBattle( int nNpcID );
	bool IsInBattleByCorpsID( int nCorpsID, int nTypeTag);
	int GetBattleBeginTime( int nNpcID, int nType );

	void SendJoinNotice();
	//�жϾ����Ƿ�����ս����
	//bool CorpsIsInBattle(int nCorpsID);
protected:
private:
	class BattleInfo
	{
	public:
		KEY_TYPE	m_Key;				// ����key
		int			m_AttCorpsID;		// ������ID
		int			m_DefCorpsID;		// ���ط�ID
		int			m_Type;				// ��������
		int			m_NpcID;			// NpcID
		int			m_MapID;			// ��ͼID
		int			m_BattleTime;		// ս����ʼʱ��
		int			m_SynTag;			// �����ݿ�ͬ��0������  1ͬ�� 2update����

	public:
		BattleInfo( ){ m_Key = INVITED_KEY_VALUE; m_AttCorpsID = 0; m_DefCorpsID = 0; m_Type = 0; m_NpcID = 0; m_MapID = 0; m_BattleTime=0; }
		BattleInfo( KEY_TYPE nKey, int nAttCorpsID, int nDefCorpsID, int nType, int nNpcID, int nMapID ) : m_Key( nKey ),
			m_AttCorpsID( nAttCorpsID ), m_DefCorpsID( nDefCorpsID ), m_Type( nType ), m_NpcID( nNpcID ), m_MapID( nMapID ),m_BattleTime(0){ }
		~BattleInfo( ){ }
	};
	typedef lk::vector< BattleInfo, SERVER_CAP_CORPS > BattleInfoList;	///< ս���б�from mgr
	BattleInfoList m_BattleInfoList;
	
public:
	void OnEventBattleOver(KEY_TYPE nKey);
	CCorps* GetBattleCorpsByCampID(KEY_TYPE nKey, int nCampID, int& nNpcID);

};

