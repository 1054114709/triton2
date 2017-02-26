#include "performance.h"
#include "log.h"

CPerfInfo::CPerfInfo()
: mPerfLog(1), mTotalCalled(0),mCostTime(0), mMostCostTime(0), mLestCostTime(1000)
{
}

CPerfInfo::~CPerfInfo()
{
}



/// ������ε��þ�����ʱ�䣬���ر����õĴ���
int CPerfInfo::AddCalled(int iElapsed)
{

	++mTotalCalled;
	mCostTime += iElapsed;
	if ( iElapsed > mMostCostTime )
	{
		mMostCostTime = iElapsed;
	}
	if ( iElapsed < mLestCostTime )
	{
		mLestCostTime = iElapsed;
	}

	return mTotalCalled;
}


/// ����ͳ������
void CPerfInfo::Reset()
{
	mTotalCalled    = 0;
	mCostTime       = 0;
	mMostCostTime   = 0;
	mLestCostTime   = 1000;
}


PerfMap CPerfStat::msPerfMap ;



void CPerfStat::LogPerfInfo(PerfMap& rPerfMap, const char* pKey)
{
	static char szTitle[256];
	sprintf(szTitle,  "%39s\t%6s\t%6s\t%6s\t%6s\t%6s", 
		"name", "called", "cost", "most", "lest", "avg");
	
	LOG_INFO(pKey, "%s", szTitle );

	PerfMapIterator endi = rPerfMap.end();

	for(PerfMapIterator p = rPerfMap.begin(); p != endi; ++p)
	{
		char szRecord[256];
		const CPerfIndex& perfIndex = (*p).first;
		CPerfInfo& perfInfo = (*p).second;
		sprintf(szRecord,  "%39s\t%6d\t%6d\t%6d\t%6d\t%6d",
			perfIndex.mName.c_str(), perfInfo.mTotalCalled,
			perfInfo.mCostTime, perfInfo.mMostCostTime, perfInfo.mLestCostTime, 
			( perfInfo.mTotalCalled != 0 ) ? perfInfo.mCostTime / perfInfo.mTotalCalled : 0 );
		
		LOG_INFO(pKey, "%s", szRecord );

		perfInfo.Reset();
	}

	rPerfMap.clear();

	LOG_INFO(pKey, "----------------------------------------------------------------------------------" );

}
