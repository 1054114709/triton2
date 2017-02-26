
/////////////////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include "stdafx.hpp"
#include "scenecfg_manager.h"
#include "speedup_checker.h"

/////////////////////////////////////////////////////////////////////////////////////////

CSpeedChecker::CSpeedChecker()
{
	mullServerTimeBaseLine				= 0;
	mullClientTimeBaseLine				= 0;
	mullLastClientTime					= 0;
	mullLastServerTime					= 0;
	mllLastDiff							= 0;

	muiCheckCountsForCSTimeDiff         = 0;
	muiFailedCountsForCSTimeDiff        = 0;
    muiCheckCountsClientSpeed			= 0;
    muiFailedCountsForClientSpeed		= 0;

    miLastSpeed                         = 0;
    muiSpeedFailedCounts                  = 0;
}

CSpeedChecker::~CSpeedChecker()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void CSpeedChecker::ShowConfig( void )
{
    SPEEDCHECKER_CFG* lpSpCheckCfg = CSceneCfgManager::GetSingletonPtr()->GetSpeedchecker_cfg();
    if( lpSpCheckCfg == NULL )
    {
        LOG_NOTICE( "map", "[ %s : %d ][ %s ]Can't get speed checker configure info!",
		    __LK_FILE__, __LINE__, __FUNCTION__ );
        return ;
    }
	LOG_NOTICE( "map", "[ %s : %d ][ %s ] Show configure info : "
                "mUsespeedcheckerforcstimediff:%d, "
                "mUsespeedcheckerforclientspee:%d, "
                "mTimesyncountforcstimediff:%d, "
                "mTimesynintervalforcstimediff:%d, "
                "mMaxtimeerrorforcstimediff:%d, "
                "mTimeerrorforcstimediff:%d, "
                "mMaxabidecountsforcstimediff:%d, "
                "mTimesyncountforclientspeed:%d, "
                "mMaxtimeerrorforclientspeed:%d, "
                "mMaxabidecountsforclientspeed:%d, "
                "mMaxerrorcountforclientspeed:%d",
		    __LK_FILE__, __LINE__, __FUNCTION__,
	        lpSpCheckCfg->mUsespeedcheckerforcstimediff,
	        lpSpCheckCfg->mUsespeedcheckerforclientspeed,
            lpSpCheckCfg->mTimesyncountforcstimediff,
	        lpSpCheckCfg->mTimesynintervalforcstimediff,
	        lpSpCheckCfg->mMaxtimeerrorforcstimediff,
            lpSpCheckCfg->mTimeerrorforcstimediff,
            lpSpCheckCfg->mMaxabidecountsforcstimediff,
            lpSpCheckCfg->mTimesyncountforclientspeed,
            lpSpCheckCfg->mMaxtimeerrorforclientspeed,
            lpSpCheckCfg->mMaxabidecountsforclientspeed,
            lpSpCheckCfg->mMaxerrorcountforclientspeed );
    
}

/////////////////////////////////////////////////////////////////////////////////////////

bool CSpeedChecker::CheckClientSpeed( int iPlayerEntityId, 
                                      int iPlayerCharId, 
                                      std::string strPlayerCharName, 
                                      unsigned long long ullClientTimeNow, 
                                      int iSpeed )
{
    // �ж��Ƿ�ʹ���ٶȼ��
	SPEEDCHECKER_CFG* lpSpCheckCfg = CSceneCfgManager::GetSingletonPtr()->GetSpeedchecker_cfg();
	if ( lpSpCheckCfg->mUsespeedcheckerforclientspeed == false )
	{
		return true;
	}

	// ���û����ܼ���Ӱ��ʱ��ͷ���ɸ����ݰ��ᰴ��ԭ�з���Ƶ�ʽ��з��ͣ���˵��û����ܵ�
	// ���ٵ�Ӱ��ʱ��ͷ���ɸ����ݰ�����ԭ�����ʽ�����֤
    if( miLastSpeed == 0 )
    {
        miLastSpeed = iSpeed;
    }else
    {
        if( miLastSpeed < iSpeed )
        {
            muiSpeedFailedCounts++;
            if( muiSpeedFailedCounts > lpSpCheckCfg->mMaxerrorcountforclientspeed )
            {
                miLastSpeed         = iSpeed;
                muiSpeedFailedCounts = 0;
            }
        }else
        {
            muiSpeedFailedCounts     = 0;
            miLastSpeed             = iSpeed;
        }
    }


	long long lllClientTimeDiff			= ullClientTimeNow-mullLastClientTime;
	int  liMinClientSpeedDiff		    = miLastSpeed - lpSpCheckCfg->mMaxtimeerrorforclientspeed;

	LOG_NOTICE( "map", "[ %s : %d ][ %s ] Player( %d:%d:%s ), check client speed"
            "ClientTime( now:%lld lase:%lld diff:%lld ), "
		    "Speed( new:%d mindiff:%d ), SpeedCheckCount( %d ), " 
            "failedCount( %d ) SpeedChangeDelayCount( %d/%d )",
		__LK_FILE__, __LINE__, __FUNCTION__,
        iPlayerEntityId, iPlayerCharId, strPlayerCharName.c_str(),
		ullClientTimeNow, mullLastClientTime, lllClientTimeDiff,
		iSpeed, liMinClientSpeedDiff, muiCheckCountsClientSpeed, muiFailedCountsForClientSpeed,
        muiSpeedFailedCounts, lpSpCheckCfg->mMaxerrorcountforclientspeed );

	// �Կͻ�����С����������м�
	if( ullClientTimeNow>(mullLastClientTime) && lllClientTimeDiff<liMinClientSpeedDiff )
	{
		muiFailedCountsForClientSpeed++;
		if( muiFailedCountsForClientSpeed>lpSpCheckCfg->mMaxabidecountsforclientspeed )
		{
			return false;
		}
	}
	muiCheckCountsClientSpeed++;
	if( muiCheckCountsClientSpeed>=lpSpCheckCfg->mTimesyncountforclientspeed )
	{
		muiCheckCountsClientSpeed=0;
		muiFailedCountsForClientSpeed=0;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool CSpeedChecker::CheckCSTimeDiff( int iPlayerEntityId, 
                                     int iPlayerCharId, 
                                     std::string strPlayerCharName, 
                                     unsigned long long ullClientTimeNow )
{
	// �ж��Ƿ�ʹ���ٶȼ��
	SPEEDCHECKER_CFG* lpSpCheckCfg = CSceneCfgManager::GetSingletonPtr()->GetSpeedchecker_cfg();
	if ( lpSpCheckCfg->mUsespeedcheckerforcstimediff == false )
	{
		return true;
	}

	unsigned long long lullServerTimeNow			= Clock::now()/1000;
    long long lllTimeDiff                           = lpSpCheckCfg->mTimesynintervalforcstimediff;
    if( mullServerTimeBaseLine!=0 && ( (long long)(lullServerTimeNow-mullServerTimeBaseLine)>lllTimeDiff ) )
    {
	    LOG_NOTICE( "map", "[ %s : %d ][ %s ] Player( %d:%d:%s ), check syn time"
	            "LocalTime( base:%lld now:%lld last:%lld ) ",
	    	__LK_FILE__, __LINE__, __FUNCTION__,
            iPlayerEntityId, iPlayerCharId, strPlayerCharName.c_str(),
		    mullServerTimeBaseLine, lullServerTimeNow, mullServerTimeBaseLine);
		
    
        mullServerTimeBaseLine  = 0;
        mullClientTimeBaseLine  = 0;
		muiFailedCountsForCSTimeDiff	= 0;
        muiCheckCountsForCSTimeDiff		= 0;
    }

	// ��ʼ���ͻ����������ʱ�䷢��ʱ��������
	if ( mullServerTimeBaseLine==0 || ullClientTimeNow<mullClientTimeBaseLine )
	{
		mullServerTimeBaseLine = lullServerTimeNow;
	}
	if ( mullClientTimeBaseLine==0 || ullClientTimeNow<mullClientTimeBaseLine )
	{
		mullClientTimeBaseLine = ullClientTimeNow;
	}

	long long	luiServerTimeDiff	    = lullServerTimeNow-mullServerTimeBaseLine;
	long long	luiClientTimeDiff	    = ullClientTimeNow-mullClientTimeBaseLine;
	long long   lllDiff				    = luiClientTimeDiff-luiServerTimeDiff;
    long long   lllTimeDiffForServer    = lullServerTimeNow-mullLastServerTime;
    
    // ���ڵ���ʱ�����������ʱ������������ʱ�䲹��
    if( mullLastServerTime!=0 &&
        lllDiff>0 &&    
        (lllTimeDiffForServer>lpSpCheckCfg->mMaxtimeerrorforcstimediff) && 
        muiFailedCountsForCSTimeDiff==0 )
    {
	    LOG_NOTICE( "map", "[ %s : %d ][ %s ] Player( %d : %d : %s ), "
                "Change client time base line! "
                "LocalTime( last:%lld now:%lld diff:%lld/%d ), " 
                "FailedCounts( %d ) ClinetBaseLine( old:%lld new:%lld )",
		        __LK_FILE__, __LINE__, __FUNCTION__,
                iPlayerEntityId, iPlayerCharId, strPlayerCharName.c_str(),
                mullLastServerTime, lullServerTimeNow, lllTimeDiffForServer, lpSpCheckCfg->mMaxtimeerrorforcstimediff,
                muiFailedCountsForCSTimeDiff, 
                mullClientTimeBaseLine, (mullClientTimeBaseLine+lllDiff) );
                
        mullClientTimeBaseLine  += lllDiff;
	    luiServerTimeDiff	    = lullServerTimeNow-mullServerTimeBaseLine;
	    luiClientTimeDiff	    = ullClientTimeNow-mullClientTimeBaseLine;
	    lllDiff				    = luiClientTimeDiff-luiServerTimeDiff;
    }

	LOG_NOTICE( "map", "[ %s : %d ][ %s ] Player( %d : %d : %s ), check cs time diff"
	    "LocalTime( base:%lld now:%lld diff:%lld ) "
		"ClientTime( base:%lld now:%lld diff:%lld ) Diff( %lld ) "
		"FailedCounts( %d ), CheckCount( %d )",
		__LK_FILE__, __LINE__, __FUNCTION__,
        iPlayerEntityId, iPlayerCharId, strPlayerCharName.c_str(),
		mullServerTimeBaseLine, lullServerTimeNow, luiServerTimeDiff,
		mullClientTimeBaseLine, ullClientTimeNow,  luiClientTimeDiff,
		lllDiff, muiFailedCountsForCSTimeDiff, muiCheckCountsForCSTimeDiff );

    // �������η�������ͻ���ʱ���Ĳ�ֵ
    long long  lllDiffOfTwice = lllDiff-mllLastDiff;

	// �Կͻ����������֮�����ݰ�ʱ�������м��
	if ( (lllDiff>lpSpCheckCfg->mMaxtimeerrorforcstimediff) ||
         ((lllDiff>lpSpCheckCfg->mTimeerrorforcstimediff) && 
         (lllDiffOfTwice)>lpSpCheckCfg->mMintimeerrorforcstimediff ) )
	{
		muiFailedCountsForCSTimeDiff++;
		if( (muiFailedCountsForCSTimeDiff) > lpSpCheckCfg->mMaxabidecountsforcstimediff )
		{
			return false;
		}
	}else
    {
	
	    LOG_NOTICE( "map", "[ %s : %d ][ %s ] Player( %d:%d:%s ), reset failed counts "
	    	"Diff( now:%lld last:%lld Max:%d Min:%d) ",
			__LK_FILE__, __LINE__, __FUNCTION__,
        	iPlayerEntityId, iPlayerCharId, strPlayerCharName.c_str(),
			lllDiff, mllLastDiff, lpSpCheckCfg->mMaxtimeerrorforcstimediff, lpSpCheckCfg->mTimeerrorforcstimediff );
        
        muiFailedCountsForCSTimeDiff=0;

        // ���ڷ�����ʱ����ͻ���ʱ���ֵС����С�Ͽɲ�ֵʱ�Կͻ��˻�׼ʱ�����в���
        if ( (lllDiffOfTwice)>0 && lllDiffOfTwice<lpSpCheckCfg->mMintimeerrorforcstimediff )
        {
            LOG_NOTICE( "map", "[ %s : %d ][ %s ] Player( %d : %d : %s ), "
                "Change client time base line! "
                "LocalTime( base:%lld now:%lld diff:%lld ), " 
                "ClientTime( base:%lld now:%lld diff:%lld ), "
                "Diff( last:%lld now:%lld diff:%lld/%d ) "
                "FailedCounts( %d ) ClinetBaseLine( old:%lld new:%lld )",
                __LK_FILE__, __LINE__, __FUNCTION__,
                iPlayerEntityId, iPlayerCharId, strPlayerCharName.c_str(),
                mullServerTimeBaseLine, lullServerTimeNow, luiServerTimeDiff,
                mullClientTimeBaseLine, ullClientTimeNow,  luiClientTimeDiff,
                mllLastDiff, lllDiff, lllDiffOfTwice, lpSpCheckCfg->mMintimeerrorforcstimediff,
                muiFailedCountsForCSTimeDiff,mullClientTimeBaseLine, (mullClientTimeBaseLine+lllDiffOfTwice) );
            mullClientTimeBaseLine+=lllDiffOfTwice;
        }
    }

    mullLastClientTime      = ullClientTimeNow;
    mullLastServerTime      = lullServerTimeNow;
    mllLastDiff             = lllDiff;
	muiCheckCountsForCSTimeDiff++;
    if ( muiCheckCountsForCSTimeDiff>lpSpCheckCfg->mTimesyncountforcstimediff )
	{
		mullServerTimeBaseLine	= 0;
		mullClientTimeBaseLine	= 0;
		muiFailedCountsForCSTimeDiff		= 0;
        muiCheckCountsForCSTimeDiff         = 0;
	}
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

std::string CSpeedChecker::DebugInfoForCSTimeDiff( void )
{
	unsigned long long	luiServerTimeDiff	= mullLastServerTime-mullServerTimeBaseLine;
	unsigned long long	luiClientTimeDiff	= mullLastClientTime-mullClientTimeBaseLine;
	long long			lllDiff				= luiClientTimeDiff-luiServerTimeDiff;

	std::stringstream lstrSpeedupCheckerInfo;
	lstrSpeedupCheckerInfo << "ServerTime( base:"<<mullServerTimeBaseLine<<" now:"<<mullLastServerTime<<" diff:"<<luiServerTimeDiff<<" ) "
		"ClientTime( base:"<<luiClientTimeDiff<<" now:"<<mullLastClientTime<<" diff:"<<luiClientTimeDiff<<" ) Diff( "<<lllDiff<<" ) "
		"FailedCounts( "<<muiFailedCountsForCSTimeDiff<<" ), CheckCount( "<<muiCheckCountsForCSTimeDiff<<" )" << std::ends;
	return lstrSpeedupCheckerInfo.str();
}

/////////////////////////////////////////////////////////////////////////////////////////

std::string CSpeedChecker::DebugInfoForClientSpeed( unsigned long long ullClientTimeNow )
{
	long long	luiClientTimeDiff	= ullClientTimeNow-mullLastClientTime;

	std::stringstream lstrSpeedupCheckerInfo;
	lstrSpeedupCheckerInfo << "ClientTime( last:"<<mullLastClientTime<<" now:"<<ullClientTimeNow<<" diff:"<<luiClientTimeDiff<<" )"
		"FailedCounts( "<<muiFailedCountsForClientSpeed<<" ), CheckCount( "<<muiCheckCountsClientSpeed<<" )" << std::ends;
	return lstrSpeedupCheckerInfo.str();
}

/////////////////////////////////////////////////////////////////////////////////////////
// End of file
/////////////////////////////////////////////////////////////////////////////////////////
