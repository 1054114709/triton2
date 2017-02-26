//================================================================================
// bidmgr.h
//================================================================================
#pragma  once
#include "corpstype.h"
//#include "module_manager.h"
#include "family.h"
#include "familytype.h"
#include "shm.h"
#include "lk_hashmap.h"
#include "lk_vector.h"
#include "gateobj_define.h"
#include "corpsinfo_pb.hxx.pb.h"   
#include "entity.h"

#define MAX_BID_FINISH_DELAY 30 //���۽�������������ӳ�ʱ�䣬��λ����
//#define ID_SWAP 10000000
#define MAPID_SWAP					1000000000	//ID_SWAP*100
#define OCP_MAINCITY				1	// ���Ǳ�ʶ
#define OCP_SUBCITY					2	// �����Ǳ�ʶ
#define GET_DBMAPID(type, mapid)	(type*MAPID_SWAP + mapid)

class CCorps;

/// ���ž�����Ϣ
struct CorpsBidInfo
{
	int m_NpcID;
	int m_CorpsID;
	int m_BidMoney;
	int m_Status;
	int m_BidTime;
	int	m_SynTag;			// �����ݿ�ͬ��0������  1ͬ�� 2update����
};

enum E_DATASYNTAG
{
	DataTag_New = 0,	//������
	DataTag_Syn,		//�Ѿ�ͬ��������
	DataTag_Upd,		//�и��µ�����
	DataTag_Del		//ɾ��������
};


struct NpcStatus
{
	int m_OwnerID;
	enum E_BIDSTATE
	{
		STATE_BidOpen,
		STATE_BidClose,
		STATE_WaitBattle,
		STATE_Inbattle,
		STATE_MaxValue
	};
	int m_Status;
	int m_BidMoneyRank1;	//������һ�ľ��ۼ۸�
	int m_BidMoneyRank2;	//�����ڶ��ľ��ۼ۸�
	int m_CorpsIDRank1;
	int m_CorpsIDRank2;
	int m_MapID;
	int m_WelfareTime;
	int m_OccupyTime;
	int m_SynTag;

	bool m_TmpTag;
	int m_TmpDesCorpID;
	int m_TmpBidMoney;
	int m_TmpNpcStat;
	int m_TmpWarStat;
	int m_NpcID;
	
	int m_nMapOccupyType;		//�ǳص�ռ������
};



/// ���۹�����
class CBidMgr : public CSingleton< CBidMgr >
{
public:
	CBidMgr();
	~CBidMgr();
	int Initialize( );
	int Resume( );
	static CSharedMem* mShmPtr;
	void * operator new( size_t tsize );
	void   operator delete( void *pPointer );
	static unsigned int CountSize();

	int m_nDataState; // 0,����״̬ 1,Ǩ��״̬ 
	
public:
	void LoadCorpsBidFromDB( int nStart, int nTotalCount );
	void LoadNpcStatusFromDB( int nStart, int nTotalCount );
	void OnSessionLoadCorpsBid( CMessage* pMessage, int nStart, int nTotalCount );
	void OnSessionLoadNpcStatus( CMessage* pMessage, int nStart, int nTotalCount );
	int SynDataToDB();

	void OnGMChangeNpcState(int nServeID, int nSceneNpcID, int nStateCode);

	/// ���NPC״̬��ֻ��������ʱ�ᱻ�ⲿ����
	int AddNpcStateInfo(int nNpcID, NpcStatus *pNpc);
public:
	void OnTimerCheckState();
public:
	//int OnEventClearBidList( int nNpcID, int* vpCorpsList, int* vpBidMoney, int& vSize );

	int OnEventRollAllBidList();
	int OnEventRollCorpsNpc( int nCorpsID, int nNpcID, int nServerID );


	void SendCorpsNpcList( int nServerID );
private:
	/// ����NPC�ľ�����Ϣ
	typedef lk::vector<CorpsBidInfo, SERVER_CAP_CORPS> BidInfoList;
	BidInfoList m_BidInfoList;

	/// NPC״̬��
	typedef lk::hash_map<int, NpcStatus, CORPS_NPC_CAP> NpcStatusMap;
	NpcStatusMap m_NpcStatusMap;

private:

	NpcStatusMap::iterator m_itNpcTmp;

public:
	int OnGetBattleMapList( int* npList, int* npCorspList, int& nNum, int nServerID );
	int SetNpcOwner(int nGateNpcID, int nCorpsID);
	int SetNpcOwnerByMapID(int nGateMapID, int nCorpsID);
	bool SetMainCity(int nCorpsID, int nSceneMapID);
	int GetMainCity(int nCorpsID);
public:
	int GetMapListByCorps(CCorps* pCorps, int* pnMapList, int& nNum);
	//int GetAllBidMoneyByCorpsID(int nCorpsID);
	///����NPC״̬
	NpcStatus* GetNpcStatus(int nGateNpcID);
	///ƴװ���ŵ�����ս״̬����
	void MakeCorpsBattleState(int nCorpsID, CorpsProperty* pProperty);
	
	void SetNpcStatusBegin();
	NpcStatus* GetOneNpcTmpState();

	/// ����ָ��Npc�ľ����б�
	int GetBidListByNpcID(int nNpcID, int* pnCorpsList, int* pnBidMoney, int& nNum);
	
	//����ָ��NPC�ľ���
	void SetBidOpen(int nGateNpcID, bool bOpen = true);

	//-------------------------------------------------------------------------
	/// ����ָ��NPC��ռ�����ID
	///	@param nMapID
	/// @return ����ID��0��ʾδ��ռ��
	int FindNpcOwnerByNpcID(int nGateNpcID);
	//-------------------------------------------------------------------------
	/// ����ָ��NPC��ռ�����ID
	///	@param nMapID
	/// @ret ����ID��0��ʾδ��ռ��
	int FindCityOwnerByMapID(int nGateMapID, int &nNpcID);
	//-------------------------------------------------------------------------
	/// ����ָ����MapID��Ӧ��NpcID
	///	@param nSceneMapID
	/// @ret NpcID��0��ʾû�ҵ�
	int GetNpcIDByMapID(int nSceneMapID);

	//-------------------------------------------------------------------------
	/// ������ս����
	/// @return 0��ʾ���۳ɹ���С��0Ϊ�����롣
	int BidForBattle(CCorps* pCorps, int nRoleID, int nNpcID, int nMapID, int nBidMoney);

	int OnBidFinishTimesUp(int nNpcID, CCorps* &pAttacker, CCorps* &pDefender, int& nMoneyAtt, int& nMoneyDef);

	// �жϵ�ǰ�����Ƿ���뾺�ۻ�ռ���˳ǳ��ڱ�������
	bool IsInBid(int nCorpsID, int nType);
private:
	int ChangeNpcBidRank(NpcStatus* pNpcStat, int nCorpsID, int nMoney);

	int DeleteNpcBidList(int nNpcID, int nCorpsID1 = 0, int nCorpsID2 = 0);

	//���Npc����״̬���У�Ԥ�ø�Npc��Ϣ
	int PreSetNpcState(int nGateNpcID);

	//���ݾ����б����¼���NPC�ľ���ǰ����
	void ReCalculeteBidRank(int nNpcID, int nServerID);

	// �ж�ָ��ʱ���Ƿ���ĳ��ָ��ʱ�䷶Χ��
	inline bool InTimeZone(tm* pLocal, int nEventDay, int nEventHour, int nEventMin, int nDelayMin);
};

