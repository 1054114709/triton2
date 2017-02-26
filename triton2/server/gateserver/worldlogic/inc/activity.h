#ifndef _ACTIVITY_SERVICE_H_
#define _ACTIVITY_SERVICE_H_

#include "module_manager.h"
#include "entity.h"
#include "lk_hashmap.h"
#include "lk_string.h"
#include "gateobj_define.h"
#include "lk_set.h"
#include "SysProtocol.h"
#include "property_pb.hxx.pb.h"
#include "gmmessage_pb.hxx.pb.h"
#include "activitytype.h"
#include "servermessage_pb.hxx.pb.h"
#include "protype.h"
#define ACTIVITY_CAP 255
using namespace GateServer;

// ��������ƶ���
class CSingleSceneActivityObj
{
public:
	int m_nTime;	// ����ʱ��
	int m_nType;	// ʱ������ �� enActivityTypeö��
	int m_nID;		// �ID
	int m_nLmtLevel;	// �ȼ�����
	int m_nMaxTimes;	// ÿ��������

	CSingleSceneActivityObj()
	{
		if ( CObj::msCreateMode )		
		{
			m_nTime = 0;
			m_nType = 0;
			m_nID   = 0;
			m_nLmtLevel = 0;
			m_nMaxTimes = 0;
		}
	}
};

// ÿ�����صľ�̬����
class CSingleActivityInfo
{
public:
	struct DropInfo
	{
		int mOgreID;
		int mDropID;
		DropInfo()
		{
			mOgreID = 0;
			mDropID = 0;			
		}
	};
	struct MapDropInfo
	{
		int mDropID;
		int mDropType;
		char mMaps[DROP_MAPS_STR_LEN];
		MapDropInfo()
		{
			mDropID=0;
			mDropType=0;
			memset (mMaps, 0, sizeof(mMaps));
		}
	};
	lk::vector<DropInfo, ACTIVITY_DROP_SZ> mDropInfo;
	lk::vector<MapDropInfo, ACTIVITY_MAPDROP_SIZE> mMapDropInfo;
	lk::vector<int, ACTIVITY_OGREINDEX_SZ> mOgreIndex;
	CSingleActivityInfo()
	{
		if (CObj::msCreateMode)
		{
			mDropInfo.initailize();
			mOgreIndex.initailize();
			mMapDropInfo.initailize();
		}
	}
};
// ��ʱ������
bool operator < ( const CSingleSceneActivityObj& rLeft, const CSingleSceneActivityObj& rRight );

class CServiceActivity :public CDataModule, public CSingleton< CServiceActivity >
{
public:
	void OnLaunchServer();
	void OnExitServer();
	void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );
	void OnMessage(int nServerID, CMessage* pMessage );
	void ReloadCfg();
	void RebuildItemIndex();

	CServiceActivity();
	~CServiceActivity();

	int Initialize();
	int Resume();
	static unsigned int CountSize();

	void* operator new( size_t size );
	void  operator delete( void* pointer );

	virtual bool IsLaunched() { return true; }

	// �յ�erating�������ȡ��ƷnItemID�Ļ�Ӧ
	void OnAGIPSessionUserItemMinus( SysProtocol* pSysProto, 
			int nRoleID, int nRoleLevel, int nRoleMetier, int nItemNum, const char* szItemCode);

	// �յ�erating����Ҳ鿴��Ʒ������
	void OnAGIPSessionUserItemList( SysProtocol* pSysProto, int nParam1, int nParam2 , int nParam3, int nParam4);

	// �յ����ݿⷵ�صĻ��Ʒ�б�
	// void OnSessionLoadActivityItemFromDB(CMessage* tpMessage, int nStart, int ONCECOUNT);
private:
	//Ӧ��Ϸ��ͬ���xml ����gateserver����� add by  qiufufu 
	void LoadActivityManagerFromXml(const char* xmlfile);

	// �Ӹ�����xmlfile��װ��δ���ڵĻ�б�
	void LoadActivityFromXml(const char* xmlfile);

	// ��Ӧ��Ϸ�����������Ļ�б�������Ϣ
	void OnMessageActivityListRequest(int nServerID, CMessage* tpMessage);

	// �յ���Ҳ鿴��Ʒ������
	void OnMessageUserItemListRequest( int vServerID, CMessage* tpMessage );

	// �յ������ȡ��Ʒ������
	void OnMessageUserItemMinusRequest( int vServerID, CMessage* tpMessage );

	// load activity items from gamedb.gms_activity_item
	// void LoadActivityItemFromDB(int nStart, int nCount);

	// Fill PBActivityItem Proto
	bool FillPBActivityItem(PBActivityItem* pActItem, const char* pszItemCode, int nItemNum, int nRoleLevel, int nRoleMetier);

	// Fill PBExItem Proto
	// void FillPBExItem(PBExItem* pproto, CActivityItem* pActivityItem);

	// typedef std::multimap<lk::CString32, int>  ACTIVITYITEMSTYPE;
	// ACTIVITYITEMSTYPE* m_pActivityItems;

	typedef lk::hash_map<int, CActivity, ACTIVITY_CAP> ACTIVITYTYPE;
	ACTIVITYTYPE m_Activities;

	typedef lk::hash_map<lk::CString32, int, 1024>  ACTIVITYITEMSTYPE;
	ACTIVITYITEMSTYPE* m_pActivityItems;

	typedef lk::hash_map<int, lk::CString32,ACTIVITY_CAP> ACTIVITYMANAGER; //add by qiufufu 

	ACTIVITYMANAGER m_pActivityManager;
	//************************************************************************
	// ���£�������������ػ�Ŀ���
	//************************************************************************
	typedef lk::vector<CSingleSceneActivityObj,ACTIVITY_SIZE*3> SCENE_ACTIVITYTYPE;
	SCENE_ACTIVITYTYPE	m_ActivityActions; // �ʱ�������

	typedef lk::hash_map<int, int, ACTIVITY_SIZE> ACTIVITY_STATE_TYPE;
	ACTIVITY_STATE_TYPE	m_ActivityStates;  // �״̬������

	typedef lk::hash_map<int, CSingleActivityInfo, ACTIVITY_SIZE> ACTIVITY_INFO_TYPE;
	ACTIVITY_INFO_TYPE	m_ActivityInfo;  // ��ۺ���Ϣ������

	int m_nNextActivityIndex;	// ��һ����Ҫ���еĻ������ ��ʼ��0

	CWTimer mCheckActivityTimer; // �����
	
	// �ӳ���������ļ��м��ص����δ���еĻ
	void LoadSceneAvtivitys( const char* pFileName );

	// ���� ��������
	void SortActivitys();

	// �ж�ʱ���Ƿ��ʱ�� ��ʱ�˷���true ʱ���ʽ��HHMM
	bool IsPassed( int nTime );

	// ����������ʼ�˾�֪ͨ����������
	void CheckActivitys(bool bStart=false);

	// �ж��ǲ��ǽ���
	bool IsToday( int nDate );

	// ��û״̬
	int GetCurState( int nID );

	// �״̬�ı�Ĵ���
	void OnActivityStateChanged( int nActivityID, int nTymeType, int nTime, SingleActivity* pMsg );
	void OnFillSceneActivityChgMsg(int nActivityID, int nNewState, SingleActivity* pMsg);

public:
	// ֪ͨ���������� �����б�
	// �ڳ���������ע����Ϻ������ �������Ƿ������������
	void SendTodayList2Scene( int nServerID, bool bStart = false );

	// ��һ�쵽��
	virtual void OnNewDayCome();

	// ��һ�ܵ���
	virtual void OnNewWeekCome() ;
	void SendActivityEvent2Scene( int nSvrID, CMessageActivityEventNotify* pMsg );

	// �������õĻص�����
	static void LoadActivityXmlCallback(const char* pcConfigPath);
	static void LoadInductXmlCallback(const char* pcConfigPath);

};

// string fmt must be is YYYY-MM-DD HH24:MI:SS
time_t GetTimeSecond(const char* szTime);
#endif

