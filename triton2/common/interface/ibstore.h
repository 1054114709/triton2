#ifndef _IBSTORE_H_
#define _IBSTORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coretype.h"



// ��Ʒ��λ����Ϣ erating �ͽ�������%d-%d-%d, �ֱ�Ϊpage_id, row_id,  col_id
// ���� page_id ��101 ��ʼ����, row_id, col_id ���� 1 ��ʼ���� 
class CLocation
{
  private:
	int m_nPageID;
	int m_nRow;
	int m_nCol;

  public:
	CLocation(){}
	~CLocation(){}

	void SetPage(int nPageID) { m_nPageID = nPageID; }
	const int  GetPage() const { return m_nPageID; }

	void SetRow(int nRow) { m_nRow = nRow; }
	const int  GetRow() const { return m_nRow; }

	void SetCol(int nCol) { m_nCol =  nCol; }
	const int  GetCol() const { return m_nCol; }

	const char* GetLocationString() const
	{ 
		static char szLocation[32+1];

		szLocation[0] = 0;
		int ineed = snprintf(szLocation, sizeof(szLocation), "%d-%d-%d", m_nPageID, m_nRow, m_nCol);

		return ineed < (int) sizeof(szLocation) && ineed > 0 ? szLocation : NULL;
	}

	bool SetLocationString(const char* szLocation)
	{
		int nPageID = 0, nRow = 0, nCol = 0;

		nPageID = atoi(szLocation);
		char* p = strchr(szLocation, '-');

		if ( p == NULL || *(p+1) == '\0') return false;
		nRow = atoi(p+1);

		p = strchr(p+1, '-');
		if ( p == NULL || *(p+1) == '\0') return false;
		nCol = atoi(p+1); 

		m_nPageID = nPageID;
		m_nRow = nRow;
		m_nCol = nCol;

		return true;
	}
};

// �̳��д洢�ĵ�����Ʒ����Ϣ
class CGoods
{
  public:
	enum 
	{
		em_ibitem_active 	= 1, // ��Ч
		em_ibitem_inactive  = 2, // ��Ч
	};

	enum 
	{
		em_ibitem_ulimit = -1,	// ������
	};

  private:
	int  m_nGoodsID;		// ��ƷID
	int  m_nGoodsCount;		// ��Ʒ����Ŀ

	int  m_nItemID;			// ��ƷID
	int  m_nItemCount;		// ��Ʒ�ĸ���

	char m_szGoodsName[32+1];  // ��Ʒ����
	char m_szGoodsDesc[255+1]; // ��Ʒ����

	CLocation m_tLocation;	// ��Ʒ�ڻ��ܵ�λ��

	int  m_nPriceValue;		// ��Ʒԭ��
	int  m_nDiscount;		// ��Ʒ�ۿۺ�ļ۸�
	int  m_nPriceUnit;		// ���ҵ�λ
	int  m_nExpiryTime;		// ��Ʒ���۽�������

	int  m_nColdTime; 		// ��ƷCDʱ��
	int  m_nElapsedTime;	// �Ѿ���ȥ��CDʱ��

	bool m_bActiveFlag;		// ��Ʒ�ϼܱ��
	bool m_bIsPackage;		// �Ƿ��Ǵ����Ʒ

	int m_nOnSaleTime;		// ��Ʒ�ϼ�ʱ��

	int m_nLimitPerChar;	// ��ҹ�����������
	int m_nLimitType;		// ����޹���������

	int m_nFlag;			// ��Ʒ��ǩ
  public:

	CGoods(){}
	~CGoods(){}

	// m_nGoodsID
	int GetGoodsID() { return m_nGoodsID; }
	void SetGoodsID(int nGoodsID) { m_nGoodsID = nGoodsID; }

	// m_nGoodsCount
	int  GetGoodsCount() { return m_nGoodsCount; }
	void SetGoodsCount(int nCount) { m_nGoodsCount = nCount; }

	// m_nItemId
	int GetItemID() { return m_nItemID; }
	void SetItemID(int nItemID) { m_nItemID = nItemID; }

	// m_nItemCount
	int  GetItemCount() { return m_nItemCount; }
	void SetItemCount(int nCount) { m_nItemCount = nCount; }

	// m_szGoodsName
	const char* GetGoodsName() const { return m_szGoodsName; } 
	void SetGoodsName(const char* szGoodsName) 
	{ 
		strncpy(m_szGoodsName, szGoodsName, sizeof(m_szGoodsName)); 
		m_szGoodsName[sizeof(m_szGoodsName)-1] = 0;
	}

	// m_szGoodsDesc
	const char* GetItemDesc() const { return m_szGoodsDesc; }
	void SetItemDesc(const char* szGoodsDesc)
	{
		strncpy(m_szGoodsDesc, szGoodsDesc, sizeof(m_szGoodsDesc));
		m_szGoodsDesc[sizeof(m_szGoodsDesc)-1] = 0;
	}

	// m_tLocation
	const CLocation& GetLocation() { return m_tLocation; }
	void SetLocation(const CLocation& rLocation) { m_tLocation = rLocation; }

	// m_nPriceUnit
	int GetPriceUnit() { return m_nPriceUnit; }
	void SetPriceUnit( int nPriceUnit ) { m_nPriceUnit = nPriceUnit; }

	// m_nPriceValue
	int GetPriceValue() { return m_nPriceValue; }
	void SetPriceValue( int nPriceValue ) { m_nPriceValue = nPriceValue; }

	// m_nDiscount
	int GetDiscount() { return m_nDiscount; }
	void SetDiscount( int nPriceValue ) { m_nDiscount = nPriceValue; }

	// m_nExpiryTime
	int GetExpiryTime() { return m_nExpiryTime; }
	void SetExpiryTime( int nExpiryTime ) { m_nExpiryTime = nExpiryTime; }

	// m_bActiveFlag
	bool IsActive() { return m_bActiveFlag == em_ibitem_active; }
	void SetActive(bool bActiveFlag) { m_bActiveFlag =  ( bActiveFlag ? em_ibitem_active : em_ibitem_inactive); }

	// m_bIsPackage
	bool IsPackage() { return m_bIsPackage; }
	void SetIsPackage(bool bIsPackage) { m_bIsPackage = bIsPackage; } 

	// m_nColdTime 
	int GetColdTime() { return m_nColdTime; }
	void SetColdTime( int nCDTime ) { m_nColdTime = nCDTime; }
	
	// m_nElapsedTime
	int GetElapsedTime() { return m_nElapsedTime; }
	void SetElapsedTime( int nCDTime ) { m_nElapsedTime = nCDTime; }

	// m_nOnSaleTime
	int GetOnsaleTime() { return m_nOnSaleTime; }
	void SetOnsaleTime( int nOnSaleTime ) { m_nOnSaleTime = nOnSaleTime; }

	// m_nLimitPerChar 
	int GetLimitPerChar() { return m_nLimitPerChar; }
	void SetLimitPerChar( int nLimitPerChar ) { m_nLimitPerChar = nLimitPerChar; }

	// m_nLimitType
	int GetLimitType() { return m_nLimitType; }
	void SetLimitType( int nLimitType) { m_nLimitType = nLimitType; }
	// m_nFlag
	int GetFlag() { return m_nFlag; }
	void SetFlag( int nFlag) { m_nFlag = nFlag; }
};

class CPromotion
{
	private:
		int m_nGoodsID;					// ��ƷID
		uint32_t m_nBeginTime;			// ������ʼʱ�� HH24MISS
		uint32_t m_nEndTime;			// ��������ʱ�� HH24MISS
		uint32_t m_nBeginVal;			// �������͵Ŀ�ʼֵ	
		uint32_t m_nEndVal;				// �������͵Ľ���ֵ

		time_t	 m_nActiveTimeStamp;	// ��ʼ������ʱ���
		time_t	 m_nExpirityTimeStamp;	// �˴δ���������ʱ���

		int m_nType;		// ��������

		int m_nRemainCount;		// ��ǰʣ��
		int m_nMaxCount;		// ������������

		/*
		int  m_nColdTime; 		// ��ƷCDʱ��
		int  m_nElapsedTime;	// �Ѿ���ȥ��CDʱ��
		int  m_nColdNum;		// ÿCDʱ���������Ʒ����
		*/

		int m_nUpdateTime;		// ���õ�

		/*
		int  m_nNoticeTimerCount;		
		int  m_nNoticeTimer[10];	// ���뿪ʼʱ��ķ�����Ϊ�趨��ֵʱ��ʾ

		int  m_nNoticeNumberCount;
		int  m_nNoticeNumber[10];	// ������Ϊ������ʱ����Ҫ��ʾ
		*/

	public:
		// m_nGoodsID
		int GetGoodsID() { return m_nGoodsID; }
		void SetGoodsID( int nGoodsID) { m_nGoodsID = nGoodsID; }

		// m_nStartTime
		int GetBeginTime() { return m_nBeginTime; }
		void SetBeginTime(int nBeginTime) { m_nBeginTime = nBeginTime; }

		// m_nEndTime
		int GetEndTime() { return m_nEndTime; }
		void SetEndTime( int nEndTime ) { m_nEndTime = nEndTime; }

		// Active From TimeStamp To TimeStamp
		int GetActiveTime() const { return m_nActiveTimeStamp; }
		int GetExpirityTime() const { return m_nExpirityTimeStamp; }

		// m_nRemainCount
		int GetRemainCount() { return m_nRemainCount; }
		void SetRemainCount(int nRemainCount)  { m_nRemainCount = nRemainCount; }

		// m_nMaxCount
		int GetMaxCount() { return m_nMaxCount; }
		void SetMaxCount(int nMaxCount)  { m_nMaxCount = nMaxCount; }

		// m_nUpdateTime
		int GetUpdateTime() { return m_nUpdateTime; }
		void SetUpdateTime( int nTime ) { m_nUpdateTime = nTime; }

		/* m_nColdTime 
		int GetColdTime() { return m_nColdTime; }
		void SetColdTime( int nCDTime ) { m_nColdTime = nCDTime; }
	
		// m_nElapsedTime
		int GetElapsedTime() { return m_nElapsedTime; }
		void SetElapsedTime( int nCDTime ) { m_nElapsedTime = nCDTime; }

		// m_nColdNum
		int GetColdNum() { return m_nColdNum; }
		void SetColdNum( int nCDNum ) { m_nColdNum = nCDNum; }
		*/

		// �� ptm�е�HHMISS����
		time_t RebuildTime(struct tm *ptm, int HH24MISS)
		{
			ptm->tm_hour = HH24MISS / 10000;		
			ptm->tm_min = HH24MISS / 100 % 100;
			ptm->tm_sec = HH24MISS % 100;

			return mktime(ptm);
		}

		// ����YYYYMMDDHH24MISS �γ��µ�ʱ��
		time_t RebuildTime(int YYYYMMDD, int HH24MISS)
		{
			struct tm tmCurr;

			tmCurr.tm_year = YYYYMMDD / 10000 - 1900;
			tmCurr.tm_mon = YYYYMMDD / 100 % 100 - 1;
			tmCurr.tm_mday = YYYYMMDD % 100;

			tmCurr.tm_hour = HH24MISS / 10000;		
			tmCurr.tm_min = HH24MISS / 100 % 100;
			tmCurr.tm_sec = HH24MISS % 100;

			return mktime(&tmCurr);
		}

		// ȡ����һ����Ч����
		bool ResetActivePeriod(time_t nThisTime)
		{
			struct tm tmCurr;
			uint64_t nThisVal = 0;

			// ��һ����Ч��ĳ��ʱ���
			switch( m_nType )
			{
				// eg: ��start_val ��end_var �ĸ���ʱ���, 
				// [1-7, HH24MISS]
				case 1:
				{
					if (localtime_r(&nThisTime,  &tmCurr) == NULL)  return false;
					nThisVal = (tmCurr.tm_wday == 0 ? 7 : tmCurr.tm_wday) ; 
					if (nThisVal < m_nBeginVal)
					{
						time_t nIncTime = nThisTime + 3600 * 24 * ( m_nBeginVal - nThisVal);
						if (localtime_r(&nIncTime,  &tmCurr) == NULL)  return false;

						m_nActiveTimeStamp = RebuildTime(&tmCurr, m_nBeginTime);
						m_nExpirityTimeStamp = RebuildTime(&tmCurr, m_nEndTime);
					}else if ( nThisVal <= m_nEndVal)
					{
						uint32_t nOffset = tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100 + tmCurr.tm_sec; 
						if ( nOffset < m_nEndTime ) 
						{
							// ��ʾ�����ʱ��
							m_nActiveTimeStamp = RebuildTime(&tmCurr, m_nBeginTime);
							m_nExpirityTimeStamp = RebuildTime(&tmCurr, m_nEndTime);
						}else
						{
							// �жϵڶ����Ƿ�����Ч��Χ��
							time_t nIncTime = nThisTime + 3600 * 24 ;
							if (localtime_r(&nIncTime,  &tmCurr) == NULL)  return false;

							uint64_t nNextVal = (tmCurr.tm_wday == 0 ? 7 : tmCurr.tm_wday); 
							if ( nNextVal < m_nBeginVal || nNextVal > m_nEndVal )
							{
								// ȡ���ܿ�ʼ��ʱ��
								nIncTime = nThisTime + 3600 * 24 * (7 -  nThisVal + m_nBeginVal);
								if (localtime_r(&nIncTime,  &tmCurr) == NULL)  return false;

								m_nActiveTimeStamp = RebuildTime(&tmCurr, m_nBeginTime);
								m_nExpirityTimeStamp = RebuildTime(&tmCurr, m_nEndTime);
							}else
							{
								// ȡ�����ʱ��
								m_nActiveTimeStamp = RebuildTime(&tmCurr, m_nBeginTime);
								m_nExpirityTimeStamp = RebuildTime(&tmCurr, m_nEndTime);
							}
						}
					}else
					{
						time_t nIncTime = nThisTime + 3600 * 24 * ( 7 - nThisVal + m_nBeginVal);
						if (localtime_r(&nIncTime,  &tmCurr) == NULL)  return false;

						m_nActiveTimeStamp = RebuildTime(&tmCurr, m_nBeginTime);
						m_nExpirityTimeStamp = RebuildTime(&tmCurr, m_nEndTime);
					}

					return true;
				}

				// [YYYYMMDD, HH24MISS]
				case 2:
				{
					if (localtime_r(&nThisTime,  &tmCurr) == NULL)  return false;

					nThisVal = (tmCurr.tm_year + 1900) * 10000 + (tmCurr.tm_mon + 1)* 100 + tmCurr.tm_mday;
					if (nThisVal < m_nBeginVal) 
					{
						m_nActiveTimeStamp = RebuildTime(m_nBeginVal, m_nBeginTime);
						m_nExpirityTimeStamp = RebuildTime(m_nBeginVal, m_nEndTime);
					} else if (nThisVal <= m_nEndVal)
					{
						uint32_t nOffset = tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100 + tmCurr.tm_sec; 
						if ( nOffset < m_nEndTime )
						{
							// ��ʾ�����ʱ��
							m_nActiveTimeStamp = RebuildTime(&tmCurr, m_nBeginTime);
							m_nExpirityTimeStamp = RebuildTime(&tmCurr, m_nEndTime);
						}else
						{
							// ��ʾ��һ���ʱ��
							time_t nIncTime = nThisTime + 3600 * 24;
							if (localtime_r(&nIncTime,  &tmCurr) == NULL)  return false;

							uint64_t nNextVal = (tmCurr.tm_year + 1900) * 10000 + (tmCurr.tm_mon + 1)* 100 + tmCurr.tm_mday;
							if (nNextVal > m_nEndVal || nNextVal < m_nBeginVal)  
							{
								m_nActiveTimeStamp = RebuildTime(m_nEndVal, m_nBeginTime);
								m_nExpirityTimeStamp = RebuildTime(m_nEndVal, m_nEndTime);
								return false;
							}

							m_nActiveTimeStamp = RebuildTime(&tmCurr, m_nBeginTime);
							m_nExpirityTimeStamp = RebuildTime(&tmCurr, m_nEndTime);
						}

						return true;
					}else
					{
						m_nActiveTimeStamp = RebuildTime(m_nEndVal, m_nBeginTime);
						m_nExpirityTimeStamp = RebuildTime(m_nEndVal, m_nEndTime);
					}

					break;
				}

				// [MMDD, HH24MISS]
				case 3:
				{
					if (localtime_r(&nThisTime,  &tmCurr) == NULL)  return false;
					nThisVal =  (tmCurr.tm_mon + 1)* 100 + tmCurr.tm_mday;
					if (nThisVal < m_nBeginVal )
					{
						m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year + 1900) * 10000 + m_nBeginVal, m_nBeginTime);
						m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year + 1900) * 10000 + m_nBeginVal, m_nEndTime);
					}else if (nThisVal <= m_nEndVal)
					{
						uint32_t nOffset = tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100 + tmCurr.tm_sec; 
						if ( nOffset < m_nEndTime)
						{
							// ��ʾ�����ʱ��
							m_nActiveTimeStamp = RebuildTime(&tmCurr, m_nBeginTime);
							m_nExpirityTimeStamp = RebuildTime(&tmCurr, m_nEndTime);
						}else
						{
							// ��ʾ��һ���ʱ��
							time_t nIncTime = nThisTime + 3600 * 24;
							if (localtime_r(&nIncTime,  &tmCurr) == NULL)  return false;

							uint64_t nNextVal =  (tmCurr.tm_mon + 1)* 100 + tmCurr.tm_mday;
							if (nNextVal > m_nEndVal || nNextVal < m_nBeginVal)  
							{
								// ȡ��һ���ʱ��
								if (localtime_r(&nThisTime,  &tmCurr) == NULL)  return false;
								m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year + 1900 + 1) * 10000 + m_nBeginVal, m_nBeginTime);
								m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year + 1900 + 1) * 10000 + m_nBeginVal, m_nEndTime);
							}else
							{
								// ȡ�����ʱ��
								m_nActiveTimeStamp = RebuildTime(&tmCurr, m_nBeginTime);
								m_nExpirityTimeStamp = RebuildTime(&tmCurr, m_nEndTime);
							}
						}
					}else
					{
						// ȡ��һ���ʱ��
						m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year + 1900 + 1) * 10000 + m_nBeginVal, m_nBeginTime);
						m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year + 1900 + 1) * 10000 + m_nBeginVal, m_nEndTime);
					}

					return true;
				}

				//[DD, HH24MISS]
				case 4:
				{
					if (localtime_r(&nThisTime,  &tmCurr) == NULL)  return false;

					nThisVal =  tmCurr.tm_mday;
					if (nThisVal < m_nBeginVal ) 
					{
						// ȡ��һ���·ݵ�
						m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year+1900) * 10000 + (tmCurr.tm_mon+1) * 100 + m_nBeginVal, m_nBeginTime);
						m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year+1900) * 10000 + (tmCurr.tm_mon+1) * 100 +  m_nBeginVal, m_nEndTime);
					} else if (nThisVal <= m_nEndVal)
					{
						// ȡ��ǰ�·ݵ�
						uint32_t nOffset = tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100 + tmCurr.tm_sec; 
						if ( nOffset < m_nEndTime) 
						{
							// ��ʾ�����ʱ��
							m_nActiveTimeStamp = RebuildTime(&tmCurr, m_nBeginTime);
							m_nExpirityTimeStamp = RebuildTime(&tmCurr, m_nEndTime);
						} else
						{
							// ȡ�ڶ���
							time_t nIncTime = nThisTime + 3600 * 24;
							if (localtime_r(&nIncTime,  &tmCurr) == NULL)  return false;

							uint64_t nNextVal =  tmCurr.tm_mday;
							if (nNextVal < m_nBeginVal || nNextVal > m_nEndVal) 
							{
								// ȡ�¸��µĵ�һ��
								if (localtime_r(&nThisTime,  &tmCurr) == NULL)  return false;
								if ( tmCurr.tm_mon == 11)
								{
									m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year+1901) * 10000 + 1 * 100 + m_nBeginVal, m_nBeginTime);
									m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year+1901) * 10000 + 1 * 100 +  m_nBeginVal, m_nEndTime);
								}else
								{
									m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year+1900) * 10000 + (tmCurr.tm_mon+2) * 100 + m_nBeginVal, m_nBeginTime);
									m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year+1900) * 10000 + (tmCurr.tm_mon+2) * 100 +  m_nBeginVal, m_nEndTime);
								}
							}else
							{
								m_nActiveTimeStamp = RebuildTime(&tmCurr, m_nBeginTime);
								m_nExpirityTimeStamp = RebuildTime(&tmCurr, m_nEndTime);
							}
						}
					}else
					{
						// ȡ�¸��µĵ�һ��
						if ( tmCurr.tm_mon == 11)
						{
							m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year+1901) * 10000 + 1 * 100 + m_nBeginVal, m_nBeginTime);
							m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year+1901) * 10000 + 1 * 100 +  m_nBeginVal, m_nEndTime);
						}else
						{
							m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year+1900) * 10000 + (tmCurr.tm_mon+2) * 100 + m_nBeginVal, m_nBeginTime);
							m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year+1900) * 10000 + (tmCurr.tm_mon+2) * 100 +  m_nBeginVal, m_nEndTime);
						}
					}

					return true;
				}

				// ��start_val �� end_val,  ����ʱ��
				// [YYYYMMDD,HH24MISS]
				case 5:
				{
					if (localtime_r(&nThisTime,  &tmCurr) == NULL)  return false;

					nThisVal =  (tmCurr.tm_year + 1900 )* 10000000000ll + (tmCurr.tm_mon + 1) * 100000000 + tmCurr.tm_mday * 1000000 
						+ tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100  + tmCurr.tm_sec;
					if ( nThisVal  < (m_nEndVal * 1000000 + m_nEndTime)) 
					{
						m_nActiveTimeStamp = RebuildTime(m_nBeginVal, m_nBeginTime);
						m_nExpirityTimeStamp = RebuildTime(m_nEndVal, m_nEndTime);

						return true;
					}else
					{
						m_nActiveTimeStamp = RebuildTime(m_nBeginVal, m_nBeginTime);
						m_nExpirityTimeStamp = RebuildTime(m_nEndVal, m_nEndTime);
					}

					break;
				}

				// [MMDD,HH24MISS]
				case 6:
				{
					if (localtime_r(&nThisTime,  &tmCurr) == NULL)  return false;

					nThisVal =  (tmCurr.tm_mon + 1)* 100000000 + tmCurr.tm_mday * 1000000 + tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100  + tmCurr.tm_sec;
					if ( nThisVal  < (m_nEndVal * 1000000 + m_nEndTime)) 
					{
						m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year + 1900)*10000 + m_nBeginVal, m_nBeginTime);
						m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year + 1900)*10000 + m_nEndVal, m_nEndTime);
					}else
					{
						m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year + 1901)*10000 + m_nBeginVal, m_nBeginTime);
						m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year + 1901)*10000 + m_nEndVal, m_nEndTime);
					}

					return true;
				}

				// [DD,HH24MISS]
				case 7:
				{
					if (localtime_r(&nThisTime,  &tmCurr) == NULL)  return false;

					nThisVal =  tmCurr.tm_mday * 1000000 + tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100  + tmCurr.tm_sec;
					if ( nThisVal  < (m_nEndVal * 1000000 + m_nEndTime)) 
					{
						m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year + 1900)*10000 + (tmCurr.tm_mon+1)*100 + m_nBeginVal, m_nBeginTime);
						m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year + 1900)*10000 +(tmCurr.tm_mon+1)*100 + m_nEndVal, m_nEndTime);
					}else
					{
						if ( tmCurr.tm_mon == 11)
						{
							m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year + 1901)*10000 + 100 + m_nBeginVal, m_nBeginTime);
							m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year + 1901)*10000 + 100 + m_nEndVal, m_nEndTime);
						}else
						{
							m_nActiveTimeStamp = RebuildTime((tmCurr.tm_year + 1900)*10000 + (tmCurr.tm_mon+2)*100 + m_nBeginVal, m_nBeginTime);
							m_nExpirityTimeStamp = RebuildTime((tmCurr.tm_year + 1900)*10000 + (tmCurr.tm_mon+2)*100 + m_nEndVal, m_nEndTime);
						}
					}

					return true;
				}

				default:
				{
					break;
				}
			}

			return false;
		}

		bool SetTimePeriod(int nType, uint32_t nBeginVal, uint32_t nEndVal, uint32_t nBeginTime, uint32_t nEndTime)
		{
			//TODO: check the param range.
			m_nType = nType;
			m_nBeginVal = nBeginVal;
			m_nEndVal = nEndVal;
			m_nBeginTime = nBeginTime;
			m_nEndTime = nEndTime;

			return true;
		}

		int GetType() const { return m_nType; }
		int GetBeginVal() const { return m_nBeginVal; }
		int GetEndVal() const { return m_nEndVal; }

		bool IsValidTime(time_t nThisTime)
		{
			return nThisTime >= m_nActiveTimeStamp && nThisTime <= m_nExpirityTimeStamp;
		}

		/*
		bool IsValidTime(time_t nThisTime)
		{
			// 1-�����͵�ÿ��ʱ��Σ�������Ϊ7��
			// 2-YYYYMMDD��ÿ���ʱ��Σ�
			// 3-MMDD��ÿ���ʱ��Σ�
			// 4-DD��ÿ���ʱ��Σ�
			// 5-YYYYMMDD�ʹ���ʼ����ʱ�䵽��ֹ����ʱ�䣻
			// 6-MMDD�ʹ���ʼ����ʱ�䵽��ֹ����ʱ�䣻
			// 7-DD�ʹ���ʼ����ʱ�䵽��ֹ����ʱ�䡣

			struct tm tmCurr;
			if (localtime_r(&nThisTime,  &tmCurr) == NULL)  return false;

			uint64_t nThisVal = 0;

			switch(m_nType) 
			{
				// eg: ��start_val ��end_var �ĸ���ʱ���, 
				// [1-7, HH24MISS]
				case 1:
				{
					nThisVal = tmCurr.tm_wday + 1; 
					if (nThisVal >= m_nBeginVal && nThisVal <= m_nEndVal)
					{
						uint32_t nOffset = tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100 + tmCurr.tm_sec; 
						return nOffset >= m_nBeginTime && nOffset <= m_nEndTime;
					}
					break;
				}

				// [YYYYMMDD, HH24MISS]
				case 2:
				{
					nThisVal = (tmCurr.tm_year + 1900) * 10000 + tmCurr.tm_mon * 100 + tmCurr.tm_mday;
					if (nThisVal >= m_nBeginVal && nThisVal <= m_nEndVal)
					{
						uint32_t nOffset = tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100 + tmCurr.tm_sec; 
						return nOffset >= m_nBeginTime && nOffset <= m_nEndTime;
					}
					break;
				}

				// [MMDD, HH24MISS]
				case 3:
				{
					nThisVal =  tmCurr.tm_mon * 100 + tmCurr.tm_mday;
					if (nThisVal >= m_nBeginVal && nThisVal <= m_nEndVal)
					{
						uint32_t nOffset = tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100 + tmCurr.tm_sec; 
						return nOffset >= m_nBeginTime && nOffset <= m_nEndTime;
					}
					break;
				}

				//[DD, HH24MISS]
				case 4:
				{
					nThisVal =  tmCurr.tm_mday;
					if (nThisVal >= m_nBeginVal && nThisVal <= m_nEndVal)
					{
						uint32_t nOffset = tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100 + tmCurr.tm_sec; 
						return nOffset >= m_nBeginTime && nOffset <= m_nEndTime;
					}
					break;
				}

				// ��start_val �� end_val,  ����ʱ��
				// [YYYYMMDD,HH24MISS]
				case 5:
				{
					nThisVal =  tmCurr.tm_year * 10000000000ll * tmCurr.tm_mon * 100000000 + tmCurr.tm_mday * 1000000 + tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100  + tmCurr.tm_sec;
					return nThisVal  >= (m_nBeginVal * 1000000ull + m_nBeginTime) && nThisVal  < (m_nEndVal * 1000000 + m_nEndTime);
				}

				// [MMDD,HH24MISS]
				case 6:
				{
					nThisVal =  tmCurr.tm_mon * 100000000 + tmCurr.tm_mday * 1000000 + tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100  + tmCurr.tm_sec;
					return nThisVal  >= (m_nBeginVal * 1000000ull + m_nBeginTime) && nThisVal  < (m_nEndVal * 1000000 + m_nEndTime);
				}

				// [DD,HH24MISS]
				case 7:
				{
					nThisVal =  tmCurr.tm_mday * 1000000 + tmCurr.tm_hour * 10000 + tmCurr.tm_min * 100  + tmCurr.tm_sec;
					return nThisVal  >= (m_nBeginVal * 1000000ull + m_nBeginTime) && nThisVal  < (m_nEndVal * 1000000 + m_nEndTime);
				}
			}

			return false;
		}
		*/

		bool IsEnougth(int nNum)
		{
			return m_nMaxCount == -1 || nNum <= m_nRemainCount; 
		}

		/*
		int GetNoticeTimerCount() { return m_nNoticeTimerCount; }
		int GetNoticeTimerSize() 
		{ 
			return sizeof(m_nNoticeTimer)/sizeof(m_nNoticeTimer[0]); 
		}

		int GetNoticeNumberCount() { return m_nNoticeNumberCount; }
		int GetNoticeNumberSize() 
		{ 
			return sizeof(m_nNoticeNumber)/sizeof(m_nNoticeNumber[0]);
		}

		void AddNoticeTimer(int nValue) 
		{ 
			if (m_nNoticeTimerCount < GetNoticeTimerSize())
			{
				m_nNoticeTimer[m_nNoticeTimerCount ++] = nValue;
			}
		}

		int GetNoticeTimer(int nIndex) 
		{
			if (nIndex < GetNoticeTimerCount())
			{
				return m_nNoticeTimer[nIndex];
			}
		}


		void AddNoticenumber(int nValue);
		{ 
			if (m_nNoticeNumberCount < GetNoticeNumberSize())
			{
				m_nNoticeNumber[m_nNoticeNumberCount ++] = nValue;
			}
		}

		int GetNoticeNumber(int nIndex) 
		{
			if (nIndex < GetNoticeNumberCount())
			{
				return m_nNoticeNumber[nIndex];
			}
		}
		*/
};

inline uint64_t world_trans_id (int nWorldID, uint32_t unPurchaseID)
{
	//nWorldID must be = MMM *  100 + NN
	//MMM = world_id   NN = server_id
	//world_trans_id must be  15 digits like as 101010000000001

	return nWorldID * 10000000000ll + unPurchaseID;
}

inline void local_trans_id( uint64_t ullWorldTransID, int* pnWorldID, uint32_t* punPurchaseID)
{
	 *punPurchaseID = ullWorldTransID % 10000000000ll;
	 *pnWorldID = (ullWorldTransID / 10000000000ll);
}

enum{
	FUNC_TEMPLATE_DXBUFFID		= 34001,		//˫�������buffid		
	FUNC_TEMPLATE_BlackPillID	= 70007,		//�ڹ����  ID
	FUNC_TEMPLATE_PROTECTTIME	= 56005,		//�󻤷��� buffID
};

//Ӧֻ��5 #define BIND_MONEY 1; UNBIND_MONEY  2;  LINEKONG_MONEY   3; SILVER_YUANBAO   4; GOLDEN_YUANBAO   5

enum{
	FUNC_CONSUME_NOMARL_PRICE	= 0,	//ֱ���ÿ��õļ�Ǯ
	FUNC_CONSUME_FROM_TAMPLATE	= 1,	//��ģ�����Ȼ���m_szFuncPrice���
};
//���ܸ��ѵ�λ
class CFuncConsume
{
	private:

		//struct Price{
		//	int64	mPrice;			//��ֵ
		//	bool	mFlag;			//�Ƿ���Ч
		//};
	private:
		int m_nFuncID;			   // ����ID
		//int	m_nFuncPrice;		   // ���ܼӸ�
		int	m_nFuncValueType;		// value���� price /template_rate 
		int m_nFuncUnitType;
		int m_nFuncUnit;			// �������ĵ�λ
		char m_szFuncName[32+1];  // ��������
		char m_szFuncComment[255+1]; // ��������

		int	 m_szFuncValue[FUNC_CONSUME_COUNT];		//��������۸�
		int m_nIsShow;				// �Ƿ��ڽ�����ʾ
		int m_nDefaultType;			// Ĭ����������
		int mCountLimit;			// һ�����ƹ��������

	public:
		CFuncConsume( ){
			m_nFuncID = -1;			   // ����ID
			//int	m_nFuncPrice;		   // ���ܼӸ�
			m_nFuncValueType = -1;		// value���� price /template_rate 
			m_nFuncUnitType = -1;
			m_nFuncUnit = -1;			// �������ĵ�λ

			memset(m_szFuncName ,0 ,sizeof(m_szFuncName));

			memset( m_szFuncComment,0, sizeof(m_szFuncComment));

			memset(m_szFuncValue, 0, sizeof(m_szFuncValue));
			m_nIsShow = -1;				// �Ƿ��ڽ�����ʾ
			m_nDefaultType = -1;			// Ĭ����������
			mCountLimit = 0;
		};
		~CFuncConsume( ){};
		//m_nFuncID
		int GetFuncID( ){ return m_nFuncID ;}
		void SetFuncID( int nFuncID ){ m_nFuncID = nFuncID; }

		////m_nFuncPrice
		//int GetFuncPrice( ){ return m_nFuncPrice ; }
		//void SetFuncPrice( int nFuncPrice ){  m_nFuncPrice = nFuncPrice }

		//m_szFuncPriceType 
		int GetFuncValueType(){ return m_nFuncValueType; }
		void SetFuncValueType( int nFuncValueType ) { m_nFuncValueType = nFuncValueType; }

		//m_nConsumeUnit
		int GetFuncUnit( ){ return m_nFuncUnit; }
		void SetFuncUnit( int nFuncUnit ){ m_nFuncUnit = nFuncUnit ;}

		//m_nConsumeType
		int GetFuncUnitType(){ return m_nFuncUnitType;}
		void SetFuncUnitType( int nFuncUnitType ){ m_nFuncUnitType = nFuncUnitType;}
		//m_szGoodsName
		const char * GetFuncName( ) const{ return m_szFuncName; }
		void SetFuncName( const char* szFuncName )
		{
			strncpy(m_szFuncName, szFuncName, sizeof(m_szFuncName)); 
			m_szFuncName[sizeof(m_szFuncName)-1] = 0;
		}

		//m_szFuncComment
		const char* GetFuncComment( ) const{ return m_szFuncComment; }
		void SetFuncComment( const char * szFuncComment )
		{
			strncpy(m_szFuncComment, szFuncComment, sizeof( m_szFuncComment ) );
			m_szFuncComment[sizeof(m_szFuncComment) - 1] = 0;
		}

		//m_szFuncPrice  return -1��Ч
		int GetFuncValue( int vConsume ) const{ 
			if( vConsume <= 0 || vConsume > FUNC_CONSUME_COUNT )
			{
				return ERR_INVALID_PARAMETER;
			}
			return m_szFuncValue[vConsume - 1];
		}
		void SetFuncValue( int nValue, int nConsume)
		{
			if( nConsume <= 0 || nConsume > FUNC_CONSUME_COUNT )
				return;
			m_szFuncValue[nConsume - 1] = nValue;
			return;
		}

		void SetFuncIsShow(int vIsShow)
		{
			m_nIsShow = vIsShow;
		}

		int GetFuncIsShow()
		{
			return m_nIsShow;
		}

		void SetDefaultType( int vType )
		{
			m_nDefaultType = vType;
		}

		int GetDefaultType()
		{
			return m_nDefaultType;
		}

		void SetFuncCountLimit( int vCountLimit ){ mCountLimit = vCountLimit ;}

		int GetFuncCountLimit(){ return mCountLimit ;}
};		
#endif
