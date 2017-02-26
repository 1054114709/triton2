
#pragma once

#define MAX_STOREBOX_PICKNUM 20

#include "tinyxml.h"
#include "lk_hashmap.h"
#include "servertool.h"
#include "activitymessag_pb.hxx.pb.h"
#include "servermessage_pb.hxx.pb.h"
#include "entity.h"
#include <map>

class CPickStoreBox
{
public:
    int     miActivityIndex;
    int     miSettlePhase;
    int     miStoreBoxId;
public:
    CPickStoreBox();
    ~CPickStoreBox(){}
    CPickStoreBox& operator = ( CPickStoreBox& theObj );
};

class CPlayerInfoForYaoQianShu
{
public:
    typedef std::map< int, CPickStoreBox >                              t_map;
    typedef t_map::iterator                                             t_map_itor;
    typedef t_map::value_type                                           t_map_value;
    typedef std::pair< t_map_itor, bool  >                              t_map_pairib;

public:
    CPlayerInfoForYaoQianShu();

public:
    t_map   mPickStoreBoxIndex; // ���ʰȡ�ı���
    int     miSettlePhase;      // ����׶�
    int     miActivityID;       // �ID

public:
    int     miHandinDawNum;     // �Ͻ���¶��
    int     miContribute;       // ҡǮ���ɳ��Ĺ��׶�

public:
    void    SetHandInDawNum( int iNum ) { miHandinDawNum=iNum; };
    int     GetHandInDawNum( void )     { return miHandinDawNum; };

    void    SetContribute( int iContribute )    { miContribute=iContribute; };
    int     GetContribute( void )               { return miContribute; };

private:
    void InsertStoreBoxToDB( int nCharID, CPickStoreBox& oStoreBoxInfo );
    void UpdatePlayerInfoToDB( int nCharID, int nActivityId );

public:
    void OnMessageLoadPlayerInfo( CMessage *pMessage, int nParam1, int nParam2 );
    void OnMessageLoadPlayerPickStoreBoxInfo( CMessage *pMessage, int nParam1, int nParam2 );
public:
    bool    Handin( int nCharId, int nContribute );
    int     PickStoreBox( int nCharId, int nStoreBoxId );

};
