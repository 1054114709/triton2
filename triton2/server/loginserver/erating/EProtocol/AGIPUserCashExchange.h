#ifndef __AGIP_USER_CASH_EXCHANGE_H__
#define __AGIP_USER_CASH_EXCHANGE_H__

#include "SysProtocol.h"

#define CMD_USER_CASH_EXCHANGE          0x10003704
#define CMD_USER_CASH_EXCHANGE_RES      0x20003704


typedef struct _AGIP_USER_CASH_EXCHANGE_
{
    _AGIP_HEADER_    header;
    uint32_t         un_gateway_id;
    uint32_t         un_detail_id_h;
    uint32_t         un_detail_id_l;
    uint32_t         un_src_user_id;
    uint32_t         un_src_role_id;
    uint32_t         un_dst_user_id;
    uint32_t         un_dst_role_id;
    int16_t          n_subject_id;
    int16_t          n_flag;
    int32_t          n_amount;
    uint32_t         un_exchange_time;
}SAGIPUserCashExchange, *PSAGIPUserCashExchange;

typedef struct _AGIP_USER_CASH_EXCHANGE_RES_{
    _AGIP_HEADER_    header;
    int32_t          n_result_code;
    uint32_t         un_detail_id_h;
    uint32_t         un_detail_id_l;
    int16_t          n_flag;
    int16_t          n_pad;
    int32_t          n_total_exchange;
}SAGIPUserCashExchangeRes, *PSAGIPUserCashExchangeRes;

class Engine_Export AGIPUserCashExchange :
    public SysProtocol
{
public:
    AGIPUserCashExchange(void);

public:
    ~AGIPUserCashExchange(void);

    uint32_t    getGatewayID(void) const;
    void        setGatewayID(uint32_t nGatewayID);

    uint64_t    getDetailID(int32_t nFlag = 1) const;
    void        setDetailID(uint64_t ullDetailID, int32_t nFlag = 1);

    uint32_t    getSrcUserID(void) const;
    void        setSrcUserID(uint32_t unUserID);

    uint32_t    getSrcRoleID(void) const;
    void        setSrcRoleID(uint32_t unRoleID);

        
    uint32_t    getDstUserID(void) const;
    void        setDstUserID(uint32_t unUserID);

    uint32_t    getDstRoleID(void) const;
    void        setDstRoleID(uint32_t unRoleID);

    int16_t     getSubjectID(void) const;
    void        setSubjectID(int16_t nsSubjectID);

    int32_t     getAmount(void) const;
    void        setAmount(int32_t nAmount);

    uint32_t    getExchangeTime(void) const;
    void        setExchangeTime(uint32_t unExchangeTime);
    
    int16_t     getFlag(void) const;
    void        setFlag(int16_t nsFlag);

    virtual int showInfo(void);
};

class Engine_Export AGIPUserCashExchangeRes :
    public SysProtocol
{
public:
    AGIPUserCashExchangeRes(void);

public:
    ~AGIPUserCashExchangeRes(void);

    int32_t     getResultCode(void) const;
    void        setResultCode(int32_t nResultCode);

    uint64_t    getDetailID(int32_t nFlag = 1) const;
    void        setDetailID(uint64_t ullDetailID,int32_t nFlag = 1);

    int16_t     getFlag(void) const;
    void        setFlag(int16_t nsFlag);

    int32_t     getTotalExchange(void) const;
    void        setTotalExchange(int32_t nTotalExchange);

    virtual int showInfo(void);
};

#endif

