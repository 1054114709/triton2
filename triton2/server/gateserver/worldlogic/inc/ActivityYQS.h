
#pragma once

#define MAX_ACTIVIT_YAOQIANSHU_LEVEL 5
#define MAX_CAMP_NUM        5

#include <string>
#include <vector>
#include "module_manager.h"
#include "entity.h"
#include "lk_vector.h"
#include "lk_hashmap.h"
#include "lk_string.h"
#include "gateobj_define.h"
#include "lk_set.h"
#include "SysProtocol.h"
#include "property_pb.hxx.pb.h"
#include "gmmessage_pb.hxx.pb.h"
#include "activitytype.h"
#include "servermessage_pb.hxx.pb.h"
#include "servertool.h"

using namespace GateServer;

#define MAX_SETTLE_PHASE 10

class CYaoQianShuCampInfoUnit
{
public:
    int miId;                           // ���ʾ
    int miActivityID;                   // �ID
    int miCampId;                       // ��ӪID
    int miCampRank;                     // ��Ӫ����
    int miGrowingValue;                 // �ɳ���
    int miLevel;                        // �ɳ��ȼ�
    int miHandinDawNum;                 // �Ͻ���¶��
    int miSettlePhase;                  // ����׶�
    std::string mstrStartTime;          // �����ʱ��
    std::string mstrEndTime;            // �����ʱ��
public:
    time_t      mtStarttimer;
    int         miTimeDelay;
public:
    CYaoQianShuCampInfoUnit();;
    ~CYaoQianShuCampInfoUnit(){};
    CYaoQianShuCampInfoUnit& operator = ( CYaoQianShuCampInfoUnit& theObj );
    void clear();

    void UpdateCampInfo( void );

    void StartSettle( void );
    void ResetTimer( time_t tTimNow, int nTimeDelay );
    void OnSettleTimer( void );

    bool SendSettleNoticeToSence( void );
};

class CYaoQianShuSettleInfoUnit
{
public:
    int miPhase;                        // ����׶�
    int miTimeDelay;                    // ����˽׶ε�ʱ���Դ�
    int miCampRankLimit;                // ��Ӫ��������
    int miNoticeCode;                   // ������Ϣ��
    int miNoticeParam1;                 // ��Ϣ����
    int miNoticeParam2;                 // ��Ϣ����
    int miNoticeParam3;                 // ��Ϣ����
    int miEncourageId;                  // �ڼ��ν���

public:
    CYaoQianShuSettleInfoUnit();
    ~CYaoQianShuSettleInfoUnit(){};
    CYaoQianShuSettleInfoUnit& operator=( CYaoQianShuSettleInfoUnit& theObj );
};

class CYaoQianShuSettleInfo : public CSingleton< CYaoQianShuSettleInfo >
{
public:
    int                                                         miSettleTime;
    int                                                         miTimeDelayForEnd;          // ����ʱ�����ʱ���ӳ�
    std::vector< CYaoQianShuSettleInfoUnit >                    mSettlePhase;

    CYaoQianShuSettleInfoUnit* GetSettlePhase( int nSettlePhase );

    int GetLastPhase( );
    bool CheckSettlePhase( void );
    bool LoadSettlePhaseFromXML( TiXmlElement* tpRoot );
};

class CActivityYQS : public CDataModule, public CSingleton< CActivityYQS >
{
public:
    CYaoQianShuCampInfoUnit   moCampYaoQianShuInfo[MAX_CAMP_NUM];

public:
     bool   mbIsUsingYaoQianShu;
     bool   mbIsStarted;
     bool   mbIsLauched;
     int    mLevel[MAX_ACTIVIT_YAOQIANSHU_LEVEL];

     static unsigned int CountSize();


public:
    CActivityYQS();
    ~CActivityYQS(){};

    typedef std::multimap<int, int>         t_map;
    typedef t_map::iterator                 t_map_itor;
    typedef t_map::reverse_iterator         t_map_ritor;
    typedef t_map::value_type               t_map_value;

private:
    CWTimer mCheckTimer; // �����


public:
    // ����������
    virtual void OnLaunchServer( );

    bool IsAllStart( void );

    bool IsAllEnd( void );

    void Sort( void );

    bool StartActivity( std::string strStartTime );
    bool EndActivity( std::string strEndTime );

    bool OnSessionActivityEnd( CMessage* tpMessage, int Param1, int nParam2 );
    bool OnSessionActivityStart( CMessage* tpMessage, int nParam1, int nParam2 );

    bool IsYaoQianShu( int iActivityId );

    bool LoadActivityYQSConfigFromXml( const char* pFileName );

    // �˳�������
    virtual void OnExitServer( );

    // ������Timer
    virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );

    // �ͻ��˷�����Ϣ
    virtual void OnMessage( int nServerID, CMessage* pMessage );;

    // ���¼��������ļ�
    virtual void ReloadCfg();

    // �����Ƿ����
    virtual bool IsLaunched();

    std::string ConverTime( int nTime );
    bool SendSettleNoticeToSence( int nCampId );
    bool IsPassed( int nTime );
    void OnMessageGrowing( int nServerID, CMessage* pMessage );
    void OnMessageGetCampRank( int nServerID, CMessage* pMessage );
    void SendResultForUpdateYQSGrowing( int nServerId, int nResult, int nPlayerId, int nCampId, int nGrowing );
    void SendYaoQianShuAvtivityStartNotice( int nCampId );
    void SendResultForGetCampRankForYQS( int nServerId, int nResult, int nPlayerId, int nParam );

	// ����ҡǮ�����õĻص�����
	static void LoadActivityYQSConfigCallback(const char* pcConfigPath);
};
