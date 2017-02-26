#pragma once

#include "base_define.h"
#include "lk_vector.h"
#include "lk_string.h"
#include "lk_hashmap.h"
#include "servertool.h"
#include "module_manager.h"
#include "rankmessage_pb.hxx.pb.h"
#include "gatelogic.h"
#include "ranktype.h"
#include <iostream>
#include <sstream>
#include <map>

class CMessage;
class CSharedMem;
using namespace GateServer;


#define MAX_COUNTRY   6 // ��������
#define TOPTEN_TYPE	  2 // 
#define TOPTEN_VALUE  10 //


template< int Max, class Node, int CountryNum >
class CRankBoard
{
public:
	// ����
	class CCountryRank
	{
	public:
		CCountryRank( )
		{
			if( CObj::msCreateMode == SHM_INIT )
			{
				mNum = 0;
				mKeyMap.initailize();
			}
		}
		~CCountryRank() {}
		unsigned int Size() { return mNum; }
		unsigned int MaxSize() { return Max; }
		
		// value����
		int mNum;
		Node mContainer[Max];		

		// first: keyֵ ; second: ����index
		typedef lk::hash_map< unsigned int, unsigned int, Max> KeyMap;
		KeyMap mKeyMap;

		std::string show( int iCountry )
		{
			std::stringstream lstrbuf;
			lstrbuf<< "CCountryRank::Show Country("<<iCountry<<") Num("<<mNum<<") \n";
			for ( int i=0; i<mNum; i++)
			{
				if ( mNum>=10 )
				{
					break;
				}
				lstrbuf<< mContainer[i].Show() << "\n";
			}
			lstrbuf << std::ends;
			return lstrbuf.str();
		}

		int ClearData()
		{
			for (int i = 0 ; i < std::min(mNum, Max); ++i )
				mContainer[i].Initialize();
			mNum = 0;
			mKeyMap.clear();
			return 0;
		}

		// ���������±� ɾ��һ��
		int RemoveLine( int nIndex )
		{
			if ( nIndex < 0 || nIndex >= mNum )
				return -1;

			// ��������ɾ��
			for ( int i = nIndex; i < std::min(mNum, Max)-1; ++i )
			{
				LOG_DEBUG("rank", "key %d = key %d", mContainer[i].HashKey(), mContainer[i+1].HashKey() );
				mContainer[i] = mContainer[i+1];
			}
			if ( mNum > Max )
			{
				LOG_ERROR("rank", "num > max? num=%d", mNum );
				return -1;
			}
			mContainer[mNum-1].Initialize();
			--mNum;
			LOG_NOTICE("rank", "remove line:%d now num:%d", nIndex, mNum );
			return 0;
		}

		// ��������õ�ָ������
		Node* GetNodeByIndex( int nIndex )
		{
			if ( nIndex < 0 || nIndex >= mNum )
				return NULL;
			return &mContainer[nIndex];
		}

		// �ؽ�����
		void RebuildIndex()
		{
			mKeyMap.clear();
			for ( int i = 0; i < std::min(mNum, Max); ++i )
			{
				std::pair<typename KeyMap::iterator, bool> ret = 
					mKeyMap.insert( typename KeyMap::value_type(mContainer[i].HashKey(),i) );
				if (!ret.second)
				{
					LOG_ERROR("rank", "RebuildIndex error! i=%d key=%d", i, mContainer[i].HashKey() );
				}
			}
		}

		// ��� ����0�ɹ�
		int CheckRank()
		{
			std::vector<int> _todel; // Ҫɾ�����±���

			for (int i = 0 ; i < std::min(mNum, Max); ++i )
			{
				unsigned int unKey = mContainer[i].HashKey();
				if (unKey == 0 || !mContainer[i].MeetRequirement()) // �Ƿ�����
				{
					_todel.push_back(i);
					continue;
				}

				typename KeyMap::iterator it = mKeyMap.find(unKey);
				if ( it == mKeyMap.end() ) // û�ҵ�
				{
					_todel.push_back(i);
				}
				else // �ҵ���
				{
					if ( i != (int)it->second ) // ��һ�� �ɵ�
					{
						_todel.push_back(i);
					}
				}
			}

			// �ɵ�
			for ( std::vector<int>::iterator it = _todel.begin(); it != _todel.end(); ++it )
			{
				// ÿ�Ƴ�1�� �����������Ҫ��һ��
				RemoveLine(*it-(it-_todel.begin()));
			}
			// �ؽ�����
			RebuildIndex();
			return 0;
		}

		// �����а���ɾ��ָ��char id
		int RemoveFromRank( int nCharID )
		{
			for( int i = 0; i < mNum; ++i )
			{
				if( mContainer[ i ].HashKey( ) == (unsigned int) nCharID )
				{
					RemoveLine( i );
				}
			}

			// �ؽ�����
			RebuildIndex();
	
			return 0;		// fuck write
		}

	};


public:

	CCountryRank* GetCountryRank( int nCountryID )
	{
		LK_ASSERT( nCountryID >= 0 && nCountryID < CountryNum, return NULL );
		return &mCountryRank[nCountryID];
	}

	// ContryID=0��ʾ���� ������ʾ����
	int GetTopTen( int* vpCharList, int vNum, int nCountryID )
	{
		if ( vpCharList == NULL )
		{
			return -1;
		}
		if ( nCountryID < 0 || nCountryID >= CountryNum )
		{
			return -1;
		}
		int i = 0;
		for ( i = 0; i < Max && i < vNum && i < mCountryRank[nCountryID].mNum; i ++ )
		{
			vpCharList[ i ] = mCountryRank[nCountryID].mContainer[i].HashKey();
		}
		return i;
	}

	// �������а� (ֻ����������ݵĸ��� ���������ݿ�����)
	int Update( const Node& rNode, bool bIsUpdateWorld )
	{
		LOG_INFO( "rank", "[%s] begin", __FUNCTION__ );
		int nResult = 0;
		
		// ���±�����
		if ( 0 == rNode.GetCountry() ) // û�����Ĳ�����
			return -1;

		LOG_INFO("rank", "test-debug func=%s, Player country=%d, hash_key=%d ", __FUNCTION__, rNode.GetCountry(), rNode.HashKey() );
		if ( rNode.GetCountry()==1 )
		{
			LOG_NOTICE( "rank", "before : %s", mCountryRank[rNode.GetCountry()].show( rNode.GetCountry() ).c_str() ); 
		}

		nResult = UpdateByCountry( rNode, rNode.GetCountry() );
		//if( nResult == 0 )
		{
			LOG_DEBUG( "rank", "Native Update: %s", rNode.Show() );
		}

		// ���������
		if (bIsUpdateWorld)
		{
			LOG_DEBUG("rank", "test-debug func=%s, UpdateWorld Player country=%d, hash_key=%d", __FUNCTION__, rNode.GetCountry(), rNode.HashKey() );
			nResult = UpdateByCountry( rNode, 0 );
		}

		if ( rNode.GetCountry()==1 )
		{
			LOG_NOTICE( "rank", "after : %s", mCountryRank[rNode.GetCountry()].show( rNode.GetCountry() ).c_str() ); 
		}

		LOG_INFO( "rank", "[%s] finished", __FUNCTION__ );

		return 0;
	}

	// ��������ݿ���ؽ��������а���Ϣ
	// Ϊ�˺��ϵļ��� 2���������Ǵ�1��ʼ���õ�ʱ��Ҫ-1
	int OnLoadRankData( const Node& rNode, int nIndex , int nRankCountry )
	{
		if ( nIndex <= 0 || nIndex > Max || nRankCountry <= 0 || nRankCountry > CountryNum )
			return -1;

		LOG_INFO("rank", "[%s], load data index=%d, country=%d, info=%s", __FUNCTION__, nIndex, nRankCountry, rNode.Show());

		std::pair<typename CCountryRank::KeyMap::iterator, bool> ret;
		ret = mCountryRank[nRankCountry-1].mKeyMap.insert( typename CCountryRank::KeyMap::value_type(rNode.HashKey(),nIndex-1) );
		if( ret.second == false )
		{
			LOG_ERROR( "rank", "[%s] load rank data failed! nIndex(%d) nRankCountry(%d) Rank(%s)", __FUNCTION__, nIndex, nRankCountry, rNode.Show() );
			return -2;
		}

		mCountryRank[nRankCountry-1].mContainer[nIndex-1] = rNode;
		++mCountryRank[nRankCountry-1].mNum;

		return 0;
	}
		//int PrepareSqlForInTimeTable( unsigned int unCountry, char* pszBuffer, int& nLen )
	//{
	//	LK_ASSERT( unCountry <= CountryNum, return -1 );

	//	int nTotalLen = 0;
	//	int nMaxLen = nLen;

	//	nTotalLen = snprintf( pszBuffer+nTotalLen, nMaxLen-nTotalLen, "%s", mCountryRank[0].mContainer[0].PreSqlStmtForInTimeTable( ) );
	//	
	//	for( unsigned int i = 0; i < mCountryRank[unCountry].Size(); i++ )
	//	{
	//		nTotalLen += snprintf( pszBuffer+nTotalLen, nMaxLen-nTotalLen, "%s%s",
	//			mCountryRank[unCountry].mContainer[i].ValueStmt(),
	//			i == mCountryRank[unCountry].Size()-1 ? ";" : "," );
	//	}

	//	nLen = nTotalLen;

	//	return 0;
	//}


	// ׼�������ݿ��SQL
	int PrepareSqlForRankTable( unsigned int unCountry, char* pszBuffer, int& nLen, int nFlag, bool bIsOutdated )
	{
		LK_ASSERT( unCountry <= CountryNum, return -1 );

		int nTotalLen = 0;
		int nMaxLen = nLen;

		if (bIsOutdated)
		{
			nTotalLen = snprintf( pszBuffer+nTotalLen, nMaxLen-nTotalLen, "%s", mCountryRank[0].mContainer[0].PreSqlStmtmForOutdatedTable( ) );
			LOG_NOTICE( "rank", "[%s] PreSqlStmtForInTimeTable( %s )", 
				__FUNCTION__, mCountryRank[0].mContainer[0].PreSqlStmtmForOutdatedTable( ) );
		}
		else
		{
			nTotalLen = snprintf( pszBuffer+nTotalLen, nMaxLen-nTotalLen, "%s", mCountryRank[0].mContainer[0].PreSqlStmtForInTimeTable( ) );
			LOG_NOTICE( "rank", "[%s] PreSqlStmtForInTimeTable( %s )", 
				__FUNCTION__, mCountryRank[0].mContainer[0].PreSqlStmtForInTimeTable( ) );
		}

		for( unsigned int i = 0; i < mCountryRank[unCountry].Size(); ++i )
		{
			nTotalLen += snprintf( pszBuffer+nTotalLen, nMaxLen-nTotalLen, "%s%s",
				mCountryRank[unCountry].mContainer[i].ValueStmt(nFlag, bIsOutdated, i+1, unCountry+1),
				i == mCountryRank[unCountry].Size()-1 ? ";" : "," );

			LOG_NOTICE( "rank", "[%s] nFlag(%d) i+1(%d) unCountry+1(%d) data( %s )", 
				__FUNCTION__, nFlag, (i+1), (unCountry+1), 
				mCountryRank[unCountry].mContainer[i].ValueStmt(nFlag, bIsOutdated, i+1, unCountry+1) );
		}

		nLen = nTotalLen;

		return 0;
	}

	// �ѵ�ǰ����д�����ݿ� ���������а����ͣ��Ƿ�������ʷ��
	int SaveRankDataToDB( int nFlag, bool bIsOutdated )
	{
		char tSqlStmt[ 40000 ] = {0};
		time_t t = time( 0 );
		tm tmp;
		localtime_r( &t, &tmp );

		for( unsigned int i = 0; i < CountryNum; ++i )
		{
			int nStmtLen = sizeof(tSqlStmt);
			LOG_NOTICE("rank", "[%s], begin : rank_type=%d, isout=%d, rank_num=%d key_size=%d cur country=%d", __FUNCTION__, nFlag
				, bIsOutdated, mCountryRank[i].Size(), mCountryRank[i].mKeyMap.size(), i );
			if (mCountryRank[i].Size() == 0)
				continue;

			if (bIsOutdated)
			{
				const char* szDelStmt = "DELETE FROM UMS_RANK_PLAYER_OUTDATED WHERE rank_type = %d and rank_country = %d and rank_date='%04d-%02d-%02d'";
				CGateLogic::GetSingleton().ExecuteSql( em_dbsession_null, 0, 0, 1, SQL_NONE, DELETE, szDelStmt, nFlag, i+1, tmp.tm_year+1900, tmp.tm_mon+1, tmp.tm_mday); 
			}
			else
			{
				const char* szDelStmt = "DELETE FROM UMS_RANK_PLAYER WHERE rank_type = %d and rank_country = %d";
				CGateLogic::GetSingleton().ExecuteSql( em_dbsession_null, 0, 0, 1, SQL_NONE, DELETE, szDelStmt, nFlag, i+1); 
			}

			PrepareSqlForRankTable( i, tSqlStmt, nStmtLen, nFlag, bIsOutdated );
			if( CGateLogic::GetSingleton().ExecuteSql( em_dbsession_save_rank, 0, 0, 
				1, SQL_NONE, INSERT, tSqlStmt, nStmtLen ) == false )
			{
				LOG_ERROR( "rank", "[%s:%d] exec sql %s failed", __FUNCTION__, __LINE__, tSqlStmt );
				return -1;
			}

			LOG_NOTICE("rank", "[%s], finished : rank_type=%d, isout=%d, rank_num=%d key_size=%d cur country=%d", __FUNCTION__, nFlag
				, bIsOutdated, mCountryRank[i].Size(), mCountryRank[i].mKeyMap.size(), i );
		}

		return 0;
	}

	// ���ϵıȽ� �������� ��
	// ����nContinusOnboardLimit:�����ϰ��������(�ﵽ���1)
	int CompareWithOld( CRankBoard<Max, Node, CountryNum>& rOldRank, unsigned int nContinusOnboardLimit )
	{
		for (int i = 0; i < CountryNum; ++i )
		{
			typename CRankBoard<Max, Node, CountryNum>::CCountryRank* pOldCountryData = rOldRank.GetCountryRank(i);
			LK_ASSERT(pOldCountryData!=NULL, continue); // ������

			for (int j = 0; j < Max; ++j )
			{
				unsigned int unThisKey = mCountryRank[i].mContainer[j].HashKey( );
				typename CCountryRank::KeyMap::iterator _old = pOldCountryData->mKeyMap.find( unThisKey );
				if ( _old == pOldCountryData->mKeyMap.end() ) // ���û�ҵ� �������ϰ��
				{
					mCountryRank[i].mContainer[j].SetRankChange(NEW_RANK_FLAG); // ���ϰ�� ���ñ��
					if (j < CONTINUS_ONBOARD_TOPNUM)
						mCountryRank[i].mContainer[j].SetCoutinuseOnBoard(1); 
					else
						mCountryRank[i].mContainer[j].SetCoutinuseOnBoard(0); 

					if ( j == 0 ) // ��ε�һ��
						mCountryRank[i].mContainer[j].SetCoutinuseFirst(1); 
				}
				else // �ϴξ��ϰ��
				{
					int nLastIndex = _old->second;
					LK_ASSERT( nLastIndex >= 0 && nLastIndex < Max, continue );
					if (j < CONTINUS_ONBOARD_TOPNUM)
					{
						if (pOldCountryData->mContainer[j].GetCoutinuseOnBoard() < (int)nContinusOnboardLimit)
							mCountryRank[i].mContainer[j].SetCoutinuseOnBoard(pOldCountryData->mContainer[nLastIndex].GetCoutinuseOnBoard()+1); 
						else // ������(TODO�Ժ���ܸ�����)
							mCountryRank[i].mContainer[j].SetCoutinuseOnBoard(1); 
					}
					else // ����ǰ10
					{
						mCountryRank[i].mContainer[j].SetCoutinuseOnBoard(0); 
					}

					if ( j == 0 )// ��һ��
					{
						if (pOldCountryData->mContainer[j].GetCoutinuseFirst() < (int)nContinusOnboardLimit)
							mCountryRank[i].mContainer[j].SetCoutinuseFirst(pOldCountryData->mContainer[nLastIndex].GetCoutinuseFirst()+1); 
						else // ������(TODO�Ժ���ܸ�����)
							mCountryRank[i].mContainer[j].SetCoutinuseFirst(1); 
					}
					else
					{
						mCountryRank[i].mContainer[j].SetCoutinuseFirst(0); 
					}

					mCountryRank[i].mContainer[j].SetRankChange(nLastIndex-j);
					//if ( j > nLastIndex ) // �½�
					//{
					//	mCountryRank[i].mContainer[j].SetRankChange(nLastIndex-j);
					//}
					////else if ( j < nLastIndex ) // ������
					////{
					////	mCountryRank[i].mContainer[j].SetRankChange(1);
					////}
					//else
					//{
					//	mCountryRank[i].mContainer[j].SetRankChange(0);  // û��
					//}
				}
			}
		}
		return 0;
	}

	// ������а�
	int ClearData()
	{
		for (int i = 0 ; i < CountryNum; ++i )
			mCountryRank[i].ClearData();
		return 0;
	}

	// ������а��߼� ��ֹ����һ���� 0֮���
	int CheckRank()
	{
		for (int i = 0 ; i < CountryNum; ++i )
		{
			mCountryRank[i].CheckRank();
		}
		return 0;
	}

	int RemoveFromRank( int nCharID )
	{
		for (int i = 0; i < CountryNum; ++i )
		{
			mCountryRank[i].RemoveFromRank( nCharID );
		}

		return 0;
	}

protected:

	// �������а�
    int UpdateByCountry( const Node& rNode, unsigned int unCountry )
	{
		// ���������а��Ź��ҵ� ֱ�ӷ���
		if( unCountry >= CountryNum )
			return -1 ;

		LOG_DEBUG("rank", "test-debug func=%s, unCountry=%d, CountryNum=%d", __FUNCTION__, unCountry, CountryNum );

		// ָ�������а�ǰ�񵥳���
		CCountryRank& rTheCountryRank = mCountryRank[unCountry];
		int nNativeSize = rTheCountryRank.Size();
		int nMaxSize = rTheCountryRank.MaxSize();

		// �Ƿ����ҵ���ͬkey�Ľڵ�
		bool bFindSameNode = false;
		int nNodeChange = 0; // -1 ��С; 0 ����; 1 ���

		// �����Ƿ������ͬ�ڵ㣬���жϽڵ�ı仯
		typename CCountryRank::KeyMap::iterator itFind = rTheCountryRank.mKeyMap.find( rNode.HashKey() );
		if( itFind != rTheCountryRank.mKeyMap.end() )
		{
			unsigned int unIndex = itFind->second;

			if ( rNode.HashKey() != rTheCountryRank.mContainer[ unIndex ].HashKey() )
			{
				LOG_ERROR( "rank", "error rNode! rNode.HashKey=%d, index in map=%d, truely hashkey=%d show=%s", rNode.HashKey()
					, unIndex, rTheCountryRank.mContainer[ unIndex ].HashKey(), rNode.Show() );
				return -1;
			}
			
			if( rNode < rTheCountryRank.mContainer[ unIndex ] )
			{
				nNodeChange = -1;
			}
			else if( rNode > rTheCountryRank.mContainer[ unIndex ] )
			{
				nNodeChange = 1;
			}

			rTheCountryRank.mContainer[ unIndex ] = rNode;
			bFindSameNode = true;
			LOG_NOTICE("rank", "test-debug func=%s, exsited!! node change=%d %s", __FUNCTION__, nNodeChange, rNode.Show() );
		}

		// �ų�����������Ҫ��Ľڵ�
		if( rNode.MeetRequirement() == false )
		{
			LOG_NOTICE("rank", "test-debug func=%s, not meet! %s", __FUNCTION__, rNode.Show() );
			// ������а������Ѿ��иýڵ��ˣ���ɾ����
			if( bFindSameNode == true )
			{
				int nCurrent = itFind->second;
				nCurrent++;
				while( nCurrent < nNativeSize )
				{
					//typename CCountryRank::KeyMap::iterator itFind2 = rTheCountryRank.mKeyMap.end();
					//// �޸�map�е�secode: �����±�.
					//itFind2 = rTheCountryRank.mKeyMap.find( rTheCountryRank.mContainer[ nCurrent ].HashKey() );
					//if(  itFind2 != rTheCountryRank.mKeyMap.end() )
					//{
					//	itFind2->second = nCurrent-1;
					//}

					//itFind2 = rTheCountryRank.mKeyMap.find( rTheCountryRank.mContainer[ nCurrent + 1].HashKey() );
					//if( itFind2 != rTheCountryRank.mKeyMap.end() )
					//{
					//	itFind2->second = nCurrent+1;
					//}

					rTheCountryRank.mContainer[ nCurrent-1 ]
					= rTheCountryRank.mContainer[ nCurrent ];

					nCurrent = nCurrent + 1;
				}

				// ��ʼ�������һ���ڵ㣬��������������
				nCurrent--;
				rTheCountryRank.mContainer[ nCurrent ].Initialize();
				rTheCountryRank.mNum--;

				//rTheCountryRank.mKeyMap.erase( itFind );
				// ����˳��ı��Ժ� �ؽ�����
				rTheCountryRank.RebuildIndex();
				return 0;
			}

			return -1;
		}

		// pos Ϊ�������ֵ��ʾ û�к���λ��
		int nPos = nMaxSize;

	
		// ����ҵ���ͬ�Ľڵ㣬ֻ����������
		if( bFindSameNode == true )
		{
			// ���޸ĵ�λ�����¶�λ, �������ǰֵС
			if( nNodeChange == -1 )
			{
				int nCurrent = itFind->second;

				while( nCurrent < nNativeSize-1 && 
					!( rTheCountryRank.mContainer[ nCurrent ] > rTheCountryRank.mContainer[ nCurrent + 1 ] ) )
				{
					LOG_NOTICE("rank", "--(chg-1)%d swap to %d", nCurrent, nCurrent+1 );
					// swap 
					Node tmp = rTheCountryRank.mContainer[ nCurrent ];

					rTheCountryRank.mContainer[ nCurrent ]
						= rTheCountryRank.mContainer[ nCurrent + 1 ];

					rTheCountryRank.mContainer[ nCurrent + 1 ] = tmp;

					// ͬʱ�޸�map�е�secode: �����±�.
					//itFind = rTheCountryRank.mKeyMap.find( rTheCountryRank.mContainer[ nCurrent ].HashKey() );
					//if(  itFind != rTheCountryRank.mKeyMap.end() )
					//{
					//	itFind->second = nCurrent;
					//}

					//itFind = rTheCountryRank.mKeyMap.find( rTheCountryRank.mContainer[ nCurrent + 1].HashKey() );
					//if( itFind != rTheCountryRank.mKeyMap.end() )
					//{
					//	itFind->second = nCurrent+1;
					//}

					nCurrent = nCurrent + 1;
				}
			}
			else if( nNodeChange == 1 ) // ������ǰֵ
			{
				int nCurrent = itFind->second;
				while( nCurrent > 0 && 
					(rTheCountryRank.mContainer[ nCurrent - 1 ] < rTheCountryRank.mContainer[ nCurrent ] ) )
				{
					//LOG_NOTICE("rank", "--(chg+1)%d swap to %d", nCurrent, nCurrent-1 );
					Node tmp = rTheCountryRank.mContainer[ nCurrent ];

					rTheCountryRank.mContainer[ nCurrent ]
					= rTheCountryRank.mContainer[ nCurrent - 1 ];

					rTheCountryRank.mContainer[ nCurrent - 1 ] = tmp;

					//itFind = rTheCountryRank.mKeyMap.find( rTheCountryRank.mContainer[ nCurrent ].HashKey() );
					//if( itFind != rTheCountryRank.mKeyMap.end() )
					//{
					//	itFind->second = nCurrent;
					//}

					//itFind = rTheCountryRank.mKeyMap.find( rTheCountryRank.mContainer[ nCurrent - 1].HashKey() );
					//if( itFind != rTheCountryRank.mKeyMap.end() )
					//{
					//	itFind->second = nCurrent-1;
					//}

					nCurrent = nCurrent - 1;
				}
			}
			// ����˳��ı��Ժ� �ؽ�����
			rTheCountryRank.RebuildIndex();
			return 0;
		}

		// Ϊ�½ڵ��Һ���λ�ò���
		for( int i = 0; i < nMaxSize ; i++ )
		{
			if( rTheCountryRank.mContainer[ i ] < rNode )
			{
				//LOG_NOTICE("rank", "test-debug func=%s, add new!", __FUNCTION__ );
				nPos = i;
				break;
			}
		}

		// �ж��Ƿ��ҵ�����λ�ã�û���򷵻�
		if( nPos == nMaxSize )
		{
			return -1;
		}

		// ���Ļ����һ���ᱻ�ɵ� �Ȱ����1����map��ɵ� (����Ҫ�ؽ����� �Ȳ��ɵ�)
		//if ( nNativeSize == nMaxSize )
		//{
		//	itFind = rTheCountryRank.mKeyMap.find( rTheCountryRank.mContainer[ nNativeSize-1 ].HashKey() );
		//	if( itFind != rTheCountryRank.mKeyMap.end() )
		//	{
		//		rTheCountryRank.mKeyMap.erase( itFind );
		//	}
		//}

		// �ӵ�����һ��ֵ��ʼ��λ
		for( int k = (nNativeSize-1); (k >= nPos) && (nNativeSize > 0); k-- )
		{
			if( k < nMaxSize-1 )
			{
				rTheCountryRank.mContainer[ k+1 ] = rTheCountryRank.mContainer[k];

				//itFind = rTheCountryRank.mKeyMap.find( rTheCountryRank.mContainer[ k + 1].HashKey() );
				//if( itFind != rTheCountryRank.mKeyMap.end() )
				//{
				//	itFind->second = k+1;
				//}
			}
		}

		// ��ֵ
		//LOG_NOTICE("rank", "test-debug func=%s, replace!", __FUNCTION__ );
		rTheCountryRank.mContainer[ nPos ] = rNode;

		// �������û������  ��++�� ����ﵽ������  �ټӾ�Խ���� ���ӵĻ�û�°� ��Ϊ�Ѿ������һ�������ˡ�
		if ( nNativeSize < nMaxSize )
			rTheCountryRank.mNum++;

		//rTheCountryRank.mKeyMap.insert( typename CCountryRank::KeyMap::value_type(rNode.HashKey(),nPos));
		//std::pair<typename CCountryRank::KeyMap::iterator,bool> ret 
		//	= rTheCountryRank.mKeyMap.insert( typename CCountryRank::KeyMap::value_type(rNode.HashKey(),nPos));
		//if (!ret.second)
		//{
		//	LOG_ERROR("rank", "insert into map error! hashkey=%d pos=%d", rNode.HashKey(), nPos);
		//	return -1;
		//}

		// ����˳��ı��Ժ� �ؽ�����
		rTheCountryRank.RebuildIndex();
		return 0;
	}

	CCountryRank mCountryRank[CountryNum]; // 0���� ; 1-6 ����
};


// ���а����
class CRankBase
{
public:
	CRankBase() {}
	virtual ~CRankBase() {}

	virtual int Initialize() = 0;
	
	// �õ�hashkey
	virtual unsigned int HashKey( ) const = 0;

	// ȡ�ù���( ���а�ܶ��ǰ����� )
	virtual unsigned int GetCountry( ) const = 0;	
	
	// �Ƿ�������������
	virtual bool MeetRequirement( ) const = 0;		
	
	// ����sql���Value����
	virtual const char* ValueStmt( int nFlag, bool bIsOutdated, int nIndex, int nRankCountry ) const = 0;

};


// ��������������
class CPlayerRankMeta : public CRankBase
{
public:
	CPlayerRankMeta()
	{
		if( CObj::msCreateMode == SHM_INIT )
		{
			Initialize();
		}
	}

	CPlayerRankMeta(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle,  unsigned int unMetier, unsigned long long unValue2 = 0, int nRankChange = 0
		, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0) :
			mCharID( unCharID ), mCharName( pszName ), mValue( unValue),
			mCountry( unCountry ), mTitle( unTitle ), mMetier( unMetier ), mValue2( unValue2 ), 
			mRankChange(nRankChange), mCoutinuseOnBoard(nCoutinuseOnBoard), mCoutinuseFirst(nCoutinuseFirst)
	{
	}

	void SetValue2( unsigned long long unValue2 ) { mValue2 = unValue2; }

	virtual ~CPlayerRankMeta() {}

	virtual int Initialize()
	{
		mCharID = 0;
		mCharName.clear();
		mValue = 0;
		mCountry = 0;
		mTitle = 0;
		mMetier = 0;
		mValue2 = 0;
		mRankChange = 0;		// �����仯
		mCoutinuseOnBoard = 0;	// �����ϰ���
		mCoutinuseFirst  = 0;	// ����������һ��
		return 0;
	}

	// ������а���Ϣ����(��������)
	virtual void FillMessageData( PBSingleRankInfo* pMsgData )
	{
		pMsgData->set_charid( mCharID );
		pMsgData->set_charname( mCharName.c_str() );
		pMsgData->set_rankvalue( mValue );
		pMsgData->set_country( mCountry );
		pMsgData->set_metier( mMetier );
		if ( mRankChange > 0 )
		{
			pMsgData->set_rankchange( 1 );
			pMsgData->set_rankchangeval( mRankChange );
		}
		else if ( mRankChange < 0 )
		{
			pMsgData->set_rankchange( 2 );
			pMsgData->set_rankchangeval( 0-mRankChange );
		}
		else
			pMsgData->set_rankchange( 0 ); // û��

		if ( mRankChange == NEW_RANK_FLAG ) // ���ϰ��
			pMsgData->set_rankchangeval( 0 );

		//pMsgData->set_rankchange( mRankChange );
		pMsgData->set_continuousboard( mCoutinuseOnBoard );
		pMsgData->set_continuousfirst( mCoutinuseFirst );
		pMsgData->set_title( mTitle );
	}

	// �õ�hashkey
	virtual unsigned int HashKey( ) const { return mCharID; }

	// �������а����Ҫ��
	virtual bool MeetRequirement() const = 0;

	// ����ṹ�ֽ���
	virtual const char* Show( ) const = 0;

	// ����sql���  ��������ǰ���ڴ�����а����� �Ƿ���ʷ�� ���� ���а������������
	virtual const char* ValueStmt( int nFlag, bool bIsOutdated, int nIndex, int nRankCountry ) const 
	{
		time_t t = time( 0 );
		tm tmp;
		localtime_r( &t, &tmp );

		static char _value[256];
		memset( _value, 0, sizeof(_value) );

		// escape ����
		char tEscapeBuff[NAME_LENGTH*8] = { 0 };		
		char *tpshopEscapePtr =	tEscapeBuff;
		EscapeDataString( &tpshopEscapePtr, NAME_LENGTH*8, (char*)mCharName.c_str(), strlen(mCharName.c_str()) );

		if (!bIsOutdated)
		{
			snprintf( _value, sizeof(_value)-1, "(%d,'%s',%d,%d,%d,%d,'%04d-%02d-%02d', %d, %d, %d, %lld)",
				mCharID, tEscapeBuff, mValue, mCountry, mTitle, mMetier, tmp.tm_year+1900, tmp.tm_mon+1, tmp.tm_mday, nFlag, nIndex, nRankCountry, mValue2);
		}
		else
		{
			snprintf( _value, sizeof(_value)-1, "(%d,'%s',%d,%d,%d,%d,'%04d-%02d-%02d', %d, %d, %d, %d, %d, %d, %lld)",
				mCharID, tEscapeBuff, mValue, mCountry, mTitle, mMetier, tmp.tm_year+1900, tmp.tm_mon+1, tmp.tm_mday, nFlag, mRankChange, mCoutinuseOnBoard, mCoutinuseFirst, nIndex, nRankCountry, mValue2);
		}
		return _value;
	}

	// �����
	virtual unsigned int GetCountry( ) const { return mCountry; }
	//inline void SetCountry( unsigned int unCountry ) { mCountry = unCountry; }

	inline unsigned int GetCharID( ) const { return mCharID; }
	//inline void SetCharID( unsigned int unCharID ) { mCharID = unCharID; }

	inline const char* GetCharName( ) const { return mCharName.c_str() ; }

	// �õ�GBK������û���
	const char* GetCharNameShow( ) const
	{
		// �ַ���������ʾ
#ifdef CHARSET_SHOW_GBK
		static char cCharName[ NAME_LENGTH ] = {0};
		int nNameLen = sizeof(cCharName)-1;
		charset_convert( "utf8", "gbk", (char*)mCharName.c_str(), strlen( mCharName.c_str() ),
			cCharName, (size_t*)&nNameLen );
		return cCharName;
#else
		return mCharName.c_str();
#endif
	}
	//inline void SetCharName( const char* pszName ) { mCharName.append( pszName); }

	inline unsigned int GetMetier( ) const { return mMetier; }
	//inline void SetMetier( unsigned int unMetier ) { mMetier = unMetier ;}

	virtual unsigned int GetValue() const { return mValue; }
	virtual unsigned long long GetValue2() const { return mValue2; }
	virtual int GetTitle() const { return mTitle; }

	virtual void SetRankChange( int nRankChange ){ mRankChange = nRankChange; }
	virtual void SetCoutinuseOnBoard( int nCoutinuseOnBoard ){ mCoutinuseOnBoard = nCoutinuseOnBoard; }
	virtual void SetCoutinuseFirst( int nCoutinuseFirst ){ mCoutinuseFirst = nCoutinuseFirst; }

	virtual int GetRankChange( ){ return mRankChange; }
	virtual int GetCoutinuseOnBoard( ){ return mCoutinuseOnBoard ; }
	virtual int GetCoutinuseFirst( ){ return mCoutinuseFirst; }

	// ʵʱ��ǰ��sql���
	virtual const char* PreSqlStmtForInTimeTable( )
	{
#ifdef _SERVER_214_
		return "INSERT INTO UMS_RANK_PLAYER_214(role_id, role_name, rank_value, role_country, order_title, metier_id, rank_date, rank_type, order_id, rank_country, value2) values" ;
#else
		return "INSERT INTO UMS_RANK_PLAYER(role_id, role_name, rank_value, role_country, order_title, metier_id, rank_date, rank_type, order_id, rank_country, value2) values" ;
#endif
	}

	// ��ʷ��ǰ��sql���
	virtual const char* PreSqlStmtmForOutdatedTable( )
	{
#ifdef _SERVER_214_
		return "insert into UMS_RANK_PLAYER_OUTDATED_214 (role_id, role_name, rank_value, role_country, order_title, metier_id, rank_date, rank_type, order_change, coutinue_onboard, coutinue_first, order_id, rank_country, value2) VALUES";
#else
		return "insert into UMS_RANK_PLAYER_OUTDATED (role_id, role_name, rank_value, role_country, order_title, metier_id, rank_date, rank_type, order_change, coutinue_onboard, coutinue_first, order_id, rank_country, value2) VALUES";
#endif	
	}


private:
	unsigned int mCharID;	// ��ɫID
	lk::string<NAME_LENGTH> mCharName;	// ��ɫ��
	unsigned int mValue;	// ������ֵ
	unsigned int mCountry;	// ����
	unsigned int mTitle;	// �ƺ�
	unsigned int mMetier;	// ����
	unsigned long long mValue2;	// ���򸽼���ֵ
	int	mRankChange;		// �����仯 ������ʾ���� ������ʾ�µ� 0��ʾƽ NEW_RANK_FLAG��ʾ���ϰ�
	int mCoutinuseOnBoard;	// �����ϰ���
	int mCoutinuseFirst;	// ����������һ��
};


// �ȼ�����
class CPlayerLevelRank : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������  �ȼ�Ҫ�ο���ֵ2
	bool operator < (const CPlayerLevelRank& other) const
	{
		if ( this->GetValue() == other.GetValue() )
			return this->GetValue2() < other.GetValue2();
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerLevelRank& other) const
	{
		if ( this->GetValue() == other.GetValue() )
			return this->GetValue2() > other.GetValue2();
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by level]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ �Ժ�ĳ�30)
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerLevelRank(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0
		, int nCoutinuseFirst = 0, unsigned long long unValue2 = 0 ) :
		CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst, unValue2 ) 
	{	}

	CPlayerLevelRank()
	{	}
};

// ���н�Ǯ����
class CPlayerMoneyRank : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerMoneyRank& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerMoneyRank& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by money]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� ��ǮҪ��ﵽ�����ϲ���
	virtual bool MeetRequirement() const { return GetValue() > 10000; }

	CPlayerMoneyRank(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerMoneyRank()
	{	}
};


// ɱ����������
class CPlayerKillRank : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerKillRank& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerKillRank& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by kill]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerKillRank(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerKillRank()
	{	}
};


// ��ѫ(����)����
class CPlayerHonorRank : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerHonorRank& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerHonorRank& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by honer]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerHonorRank(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerHonorRank()
	{	}
};


// ������������
class CPlayerDieNumRank : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerDieNumRank& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerDieNumRank& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by dienum]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerDieNumRank(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerDieNumRank()
	{	}
};

// ���������������
class CPlayerEndTaskRank : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerEndTaskRank& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerEndTaskRank& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by endtask]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerEndTaskRank(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerEndTaskRank()
	{	}
};

// ����ʱ������
class CPlayerOnLineRank : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerOnLineRank& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerOnLineRank& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by online]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerOnLineRank(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerOnLineRank()
	{	}
};



// �������
class CPlayerPantaoRank : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerPantaoRank& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerPantaoRank& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by pantao]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerPantaoRank(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerPantaoRank()
	{	}
};

// ��������
class CPlayerLonggongRank : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerLonggongRank& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerLonggongRank& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by longgong]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerLonggongRank(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerLonggongRank()
	{	}
};

// ԭ�ظ���������а�
class CPlayerOriginReliveTimes : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerOriginReliveTimes& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerOriginReliveTimes& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by CPlayerOriginReliveTimes]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerOriginReliveTimes(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerOriginReliveTimes()
	{	}
};

// ɱ������Ӫ���а�
class CPlayerRankKillSameNationNum : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankKillSameNationNum& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankKillSameNationNum& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by CPlayerRankKillSameNationNum]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankKillSameNationNum(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankKillSameNationNum()
	{	}
};


// ��ɱ�������а�
class CPlayerRankKillOgreNum : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankKillOgreNum& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

		bool operator > (const CPlayerRankKillOgreNum& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by CPlayerRankKillOgreNum]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankKillOgreNum(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankKillOgreNum()
	{	}
};


// ����ʧ�����а�
class CPlayerRankUpFailNum : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankUpFailNum& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankUpFailNum& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by CPlayerRankUpFailNum]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankUpFailNum(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankUpFailNum()
	{	}
};

// ����������
class CPlayerRankDayanta : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankDayanta& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankDayanta& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by Dayanta]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankDayanta(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankDayanta()
	{	}
};

// ���Ҷ�����
class CPlayerRankLastOne : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankLastOne& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankLastOne& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by LastOne]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankLastOne(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankLastOne()
	{	}
};


// ����������
class CPlayerRankLianhuadong : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankLianhuadong& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankLianhuadong& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by Lianhuadong]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankLianhuadong(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankLianhuadong()
	{	}
};

// ���и�������
class CPlayerRankFlyDung : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankFlyDung& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankFlyDung& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by RankFlyDung]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankFlyDung(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankFlyDung()
	{	}
};


// ͨ�ð񣡡��Ժ�һ������¶���������С�
class CPlayerRankCommon : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankCommon& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankCommon& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank ID=%d]%d\t %s\t %d\t %d\t %d\t %d", 0,
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankCommon(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{ }

	CPlayerRankCommon()
	{	}
};


// �Ʒ䶴����
class CPlayerRankHuangfengdong : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankHuangfengdong& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankHuangfengdong& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by Huangfengdong]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankHuangfengdong(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankHuangfengdong()
	{	}
};

// �ɾ�����
class CPlayerRankAchive : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankAchive& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankAchive& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by Achive]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankAchive(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankAchive()
	{	}
};

// �ø�����
class CPlayerRankFavor : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankFavor& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankFavor& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by Favor]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankFavor(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankFavor()
	{	}
};


// �������
class CPlayerRankBadPoint : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankBadPoint& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankBadPoint& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by BadPoint]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankBadPoint(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankBadPoint()
	{	}
};


// ����ֵ����
class CPlayerRankCharm : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankCharm& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankCharm& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by Charm]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� 
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankCharm(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankCharm()
	{	}
};


// �Ŷ���������
class CPlayerRankTeamPoints : public CPlayerRankMeta
{
public:
	// �����
	// ���ܲ��������������ŵ� ���Էŵ�������
	bool operator < (const CPlayerRankTeamPoints& other) const
	{
		return ( this->GetValue() < other.GetValue() );
	}

	bool operator > (const CPlayerRankTeamPoints& other) const
	{
		return ( this->GetValue() > other.GetValue() );
	}

	// ����ṹ�ֽ���
	virtual const char* Show( ) const
	{
		static char _buff[256];
		memset( _buff, 0, sizeof(_buff) );
		snprintf( _buff, sizeof(_buff)-1, "[rank by TeamPoints]%d\t %s\t %d\t %d\t %d\t %d",
			GetCharID(), GetCharNameShow(), GetValue(), GetCountry(), GetTitle(), GetMetier() );
		return _buff;
	}

	// �������а����Ҫ�� (TODO ������ )
	virtual bool MeetRequirement() const { return GetValue() > 0; }

	CPlayerRankTeamPoints(unsigned int unCharID, const char* pszName, unsigned int unValue, 
		unsigned int unCountry, unsigned int unTitle, unsigned int unMetier, int nRankChange = 0, int nCoutinuseOnBoard = 0, int nCoutinuseFirst = 0 ) :
	CPlayerRankMeta(unCharID, pszName, unValue, unCountry, unTitle, unMetier, nRankChange , nCoutinuseOnBoard , nCoutinuseFirst ) 
	{	}

	CPlayerRankTeamPoints()
	{	}
};


/** CRankModule 
**	���а�ϵͳ
**  ��������������������������ݻ����ڴˣ�
**  Ȼ����ݾ������(1��/1��)����������
**	a.�������ǰ�㱨һ��; 
**  b.�µ�1�쵽�������������������Ҫһ��
**
**  ���а��2�֣�
**  a. ��ǰ���а� - ������/������
**  b. ʵʱ���а� - Ϊ�´�������׼����ֻ�������ض������ļ�¼���ܽ����������ݺ��Ե�
**
**  ������Ҫ�����ݿ� -
**  a.��ǰ���а��Ǵ���ʷ��150��/�� * 365�� = 54750 ��
**	��ʱ����Ӫ3�꣬������Ҳ��С��������������ʾ��
**	b.ʵʱ���о�ֻ����150����¼����ʱupdate,truncat���Ժ�insert��ȥ��
**	
*/
class CRankModule : public CDataModule, public CSingleton< CRankModule >
{
public:

	CRankModule();
	~CRankModule();

	static int CountSize( ) { return sizeof( CRankModule ); }

	// ����������
	virtual void OnLaunchServer( );

	// �˳�������
	virtual void OnExitServer( );

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );

	// �ͻ��˷�����Ϣ
	virtual void OnMessage( int nServerID, CMessage* pMessage );

	// �����Ƿ����
	virtual bool IsLaunched();

	virtual void OnNewDayCome();

	virtual void OnNewWeekCome();

	// �������ϱ��ĸ���������Ϣ
	int OnMessagePersonalRankInfoReport(int nServerID, CMessage* pMessage );
	int OnMessageRankRemove( int nServerID, CMessage* pMsg );

	// �����ݿ����뵱ǰ�������
	int LoadCurrentPlayerRankFromDB( );

	// �����ݿ�����ʵʱ�ȼ�����
	int LoadInTimeLevelRankFromDB( );

	// ��ʵʱ�ȼ�����д�����ݿ�
	int SaveInTimePlayerRankToDB( );

	// ���صȼ�������Ϣ
	int OnSessionLoadIntimePlayerRankInfoFromDB( CMessage* tpMessage, int nParam1, int nParam2 );

	// ������ʷ������Ϣ
	int OnSessionLoadOutdatedPlayerRankInfoFromDB( CMessage* tpMessage, int nParam1, int nParam2 );

	// ÿ�ո������а�
	int DailyUpdate( );
	int OnDailyUpdate( );
	int HalfHourUpdate(); // ��Сʱˢ��
	int OnHalfHourUpdate( );

	// ÿ�ܸ������а�
	int WeeklyUpdate( );

	// �Ӱ���ɾ��ָ����ɫ
	int RemovePlayerFromRank( int nCharID, int nRankType );

	// ----------------- ��������������Ϣ ------------------------
	// TODO: ������������Ϣ���ǿͻ����������Ϣ��ֻ��ԭ�ⲻ��ת�������ˣ�
	// ֻ��Ϊ�˼���������ö��峬����ͬ����Ϣ����Ҫ������ˡ�
	// -------------------------------------------------------------
	
	// ����ȼ������б�
	int OnRouteMessagePlayerRankReqeust( int nServerID, CMessage* pMessage );
	// ����������е����а�ƺ�
	int OnMessageObtainTopTenRequest( int nServerID, CMessage* pMessage );
	int mLaunchFlag;
	time_t mLastDayTick; // ���ڼ���ÿ��
private:

	enum 
	{
		MAX_LEVEL_RANK_NUM = 150, // �ȼ����а񳤶�
		MAX_MONEY_RANK_NUM = 150, // ��Ǯ���а񳤶�
		MAX_KILL_RANK_NUM  = 150, // ɱ�����а񳤶�
		MAX_HONOR_RANK_NUM  = 150, // ��ѫ���а񳤶�
		MAX_DIE_RANK_NUM  = 150, // �������а񳤶�
		MAX_ENDTASK_RANK_NUM  = 150, // ����������а񳤶�
		MAX_ONLINE_RANK_NUM  = 150, // ����ʱ�����а񳤶�
		MAX_PANTAO_RANK_NUM  = 150, // ��Ҹ������а񳤶�
		MAX_LONGGONG_RANK_NUM  = 150, // �����������а񳤶�
        MAX_LASTONE_RANK_NUM  =  150 , //����ɱ�������а񳤶�
		MAX_ORIGINRELIVETIMES_RANK_NUM  = 150,   // ԭ�ظ������(ȫ��)
		MAX_KILLSAMENATIONNUM_RANK_NUM  = 150,   // ɱ����Ӫ����(ȫ��)
		MAX_KILLOGRENUM_RANK_NUM  = 150,		 // ɱ����(ȫ��)
		MAX_UPFAILNUM_RANK_NUM  = 150,			 // ����ʧ�ܴ���(ȫ��)
		MAX_DAYANTA_NUM = 150, // ������
		MAX_LIANHUADONG_NUM = 150, // ������
		MAX_HUANGFENGDONG_NUM = 150, // �Ʒ䶴
		MAX_RANK_ACHIVE_NUM= 150, // �ɾ͵�
		MAX_RANK_FAVOR_NUM= 150, // �øж�
		MAX_RANK_BAD_NUM= 150, // �����
		MAX_RANK_CHARM_NUM= 150, // ����ֵ���а�
		MAX_FAMILY_HONOR_NUM = 30, // ��������
		MAX_CORPS_HONOR_NUM = 30, // ��������
		MAX_FLY_DUNG_NUM = 150, // ���и�������
		MAX_COMMON_NUM	= 150,  // ͨ������
	};

	enum MONEY
	{
		FREE_MONEY, // �ǰ�Ǯ
		ALL_MONEY,  // ����Ǯ
	};

	enum KILL
	{
		KILL_PROT_NATION,
		KILL_OUT,			
		KILL_TOTAL,
	};

	typedef CRankBoard<MAX_LEVEL_RANK_NUM, CPlayerLevelRank, MAX_COUNTRY+1> RANK_LEVEL_TYPE;
	RANK_LEVEL_TYPE mLevelRankOutdated;	// ��ʷ�ȼ�����( �ͻ�����ʾ�� )
	RANK_LEVEL_TYPE mLevelRankInTime;	// ʵʱ�ȼ�����( ������ )

	typedef CRankBoard<MAX_MONEY_RANK_NUM, CPlayerMoneyRank, 1> RANK_MONEY_TYPE;
	RANK_MONEY_TYPE mMoneyRankOutdated[2];	// ��ʷ��Ǯ����( �ͻ�����ʾ�� )
	RANK_MONEY_TYPE mMoneyRankInTime[2];	// ʵʱ��Ǯ����( ������ )

	typedef CRankBoard<MAX_KILL_RANK_NUM, CPlayerKillRank, 1> RANK_KILL_TYPE;
	RANK_KILL_TYPE mKillRankOutdated[3];	// ��ʷɱ������( �ͻ�����ʾ�� )
	RANK_KILL_TYPE mKillRankInTime[3];		// ʵʱɱ������( ������ )

	RANK_KILL_TYPE mDayKillRankOutdated[3];	// ������ʷɱ������( �ͻ�����ʾ�� )
	RANK_KILL_TYPE mDayKillRankInTime[3];	// ����ʵʱɱ������( ������ )

	typedef CRankBoard<MAX_HONOR_RANK_NUM, CPlayerHonorRank, MAX_COUNTRY+1> RANK_HONOR_TYPE;
	RANK_HONOR_TYPE mHonorRankOutdated;		// ��ʷ��ѫ����( �ͻ�����ʾ�� )
	RANK_HONOR_TYPE mHonorRankInTime;		// ʵʱ��ѫ����( ������ )

	RANK_HONOR_TYPE mDayHonorRankOutdated;	// ������ʷ��ѫ����( �ͻ�����ʾ�� )
	RANK_HONOR_TYPE mDayHonorRankInTime;	// ����ʵʱ��ѫ����( ������ )

	typedef CRankBoard<MAX_DIE_RANK_NUM, CPlayerDieNumRank, 1> RANK_DIE_TYPE;
	RANK_DIE_TYPE mDieNumRankOutdated;	// ��ʷ��������( �ͻ�����ʾ�� )
	RANK_DIE_TYPE mDieNumRankInTime;	// ʵʱ��������( ������ )

	typedef CRankBoard<MAX_ENDTASK_RANK_NUM, CPlayerEndTaskRank, 1> RANK_ENDTASK_TYPE;
	RANK_ENDTASK_TYPE mEndTaskRankOutdated;	// ��ʷ�����������( �ͻ�����ʾ�� )
	RANK_ENDTASK_TYPE mEndTaskRankInTime;		// ʵʱ�����������( ������ )

	typedef CRankBoard<MAX_ONLINE_RANK_NUM, CPlayerOnLineRank, 1> RANK_ONLINE_TYPE;
	RANK_ONLINE_TYPE mOnLineRankOutdated;		// ��ʷ����ʱ������( �ͻ�����ʾ�� )
	RANK_ONLINE_TYPE mOnLineRankInTime;		// ʵʱ����ʱ������( ������ )

	typedef CRankBoard<MAX_PANTAO_RANK_NUM, CPlayerPantaoRank, 1> RANK_PANTAO_TYPE;
	RANK_PANTAO_TYPE mPantaoRankOutdated;		// ��ʷ����( �ͻ�����ʾ�� )
	RANK_PANTAO_TYPE mPantaoRankInTime;		// ʵʱ����( ������ )

	typedef CRankBoard<MAX_LONGGONG_RANK_NUM, CPlayerLonggongRank, 1> RANK_LONGGONG_TYPE;
	RANK_LONGGONG_TYPE mLonggongRankOutdated;	// ��ʷ����( �ͻ�����ʾ�� )
	RANK_LONGGONG_TYPE mLonggongRankInTime;		// ʵʱ����( ������ )

	typedef CRankBoard<MAX_ORIGINRELIVETIMES_RANK_NUM, CPlayerOriginReliveTimes, 1> RANK_ORIGINRELIVETIMES_TYPE;
	RANK_ORIGINRELIVETIMES_TYPE mOriginReliveRankOutdated;	// ��ʷԭ�ظ�������( �ͻ�����ʾ�� )
	RANK_ORIGINRELIVETIMES_TYPE mOriginReliveRankInTime;		// ʵʱԭ�ظ�������( ������ )

	typedef CRankBoard<MAX_KILLSAMENATIONNUM_RANK_NUM, CPlayerRankKillSameNationNum, 1> RANK_KILLSAMENATIONNUM_TYPE;
	RANK_KILLSAMENATIONNUM_TYPE mKillSameNationRankOutdated;	// ��ʷɱ������Ӫ����( �ͻ�����ʾ�� )
	RANK_KILLSAMENATIONNUM_TYPE mKillSameNationRankInTime;		// ʵʱɱ������Ӫ����( ������ )

	typedef CRankBoard<MAX_KILLOGRENUM_RANK_NUM, CPlayerRankKillOgreNum, 1> RANK_KILLOGRENUM_TYPE;
	RANK_KILLOGRENUM_TYPE mKillOgreRankOutdated;	// ��ʷɱ����������( �ͻ�����ʾ�� )
	RANK_KILLOGRENUM_TYPE mKillOgreRankInTime;		// ʵʱɱ����������( ������ )

	typedef CRankBoard<MAX_UPFAILNUM_RANK_NUM, CPlayerRankUpFailNum, 1> RANK_UPFAILNUM_TYPE;
	RANK_UPFAILNUM_TYPE mUpFailRankOutdated;	// ��ʷ����ʧ������( �ͻ�����ʾ�� )
	RANK_UPFAILNUM_TYPE mUpFailRankInTime;		// ʵʱ����ʧ������( ������ )

	//12.16�¼�
	typedef CRankBoard<MAX_DAYANTA_NUM, CPlayerRankDayanta, 1> RANK_DAYANTA_TYPE;
	RANK_DAYANTA_TYPE mDayantaRankOutdated;	// ��������ʷ����( �ͻ�����ʾ�� )
	RANK_DAYANTA_TYPE mDayantaRankInTime;	// ������ʵʱ����( ������ )

    typedef CRankBoard<MAX_LASTONE_RANK_NUM, CPlayerRankLastOne, 1> RANKTYPE_LASTONE_TYPE;
    RANKTYPE_LASTONE_TYPE mDaLuanDouOutdated;  // ���Ҷ���ʷ����( �ͻ�����ʾ�� )
    RANKTYPE_LASTONE_TYPE mDaLuanDouInTime;    // ���Ҷ�ʵʱ����( ������ )
	RANKTYPE_LASTONE_TYPE mDaLuanDouTotalOutdated;  // ���Ҷ���ʷ�����ܻ���( �ͻ�����ʾ�� )
	RANKTYPE_LASTONE_TYPE mDaLuanDouTotalInTime;    // ���Ҷ��ܻ���ʵʱ����( ������ )

	typedef CRankBoard<MAX_LIANHUADONG_NUM, CPlayerRankLianhuadong, 1> RANK_LIANHUADONG_TYPE;
	RANK_LIANHUADONG_TYPE mLianhuadongRankOutdated;	// ��������ʷ����( �ͻ�����ʾ�� )
	RANK_LIANHUADONG_TYPE mLianhuadongRankInTime;	// ������ʵʱ����( ������ )

	typedef CRankBoard<MAX_HUANGFENGDONG_NUM, CPlayerRankHuangfengdong, 1> RANK_HUANGFENGDONG_TYPE;
	RANK_HUANGFENGDONG_TYPE mHuangfengdongRankOutdated;	// �Ʒ䶴��ʷ����( �ͻ�����ʾ�� )
	RANK_HUANGFENGDONG_TYPE mHuangfengdongRankInTime;	// �Ʒ䶴ʵʱ����( ������ )

	typedef CRankBoard<MAX_RANK_ACHIVE_NUM, CPlayerRankAchive, 1> RANK_ACHIVE_TYPE;
	RANK_ACHIVE_TYPE mAchiveRankOutdated;	// �ɾ͵���ʷ����( �ͻ�����ʾ�� )
	RANK_ACHIVE_TYPE mAchiveRankInTime;		// �ɾ͵�ʵʱ����( ������ )

	typedef CRankBoard<MAX_RANK_FAVOR_NUM, CPlayerRankFavor, 1> RANK_FAVOR_TYPE;
	RANK_FAVOR_TYPE mFavorRankOutdated;	// �øж���ʷ����( �ͻ�����ʾ�� )
	RANK_FAVOR_TYPE mFavorRankInTime;	// �øж�ʵʱ����( ������ )

	typedef CRankBoard<MAX_RANK_BAD_NUM, CPlayerRankBadPoint, 1> RANK_BAD_TYPE;
	RANK_BAD_TYPE mBadRankOutdated;	// �������ʷ����( �ͻ�����ʾ�� )
	RANK_BAD_TYPE mBadRankInTime;	// �����ʵʱ����( ������ )

	typedef CRankBoard<MAX_FAMILY_HONOR_NUM , CPlayerRankTeamPoints, 1> RANK_FAMILY_POINTS_TYPE;
	RANK_FAMILY_POINTS_TYPE mFamilyRankOutdated;	// ����PVP��ʷ����( �ͻ�����ʾ�� )
	RANK_FAMILY_POINTS_TYPE mFamilyRankInTime;		// ����PVPʵʱ����( ������ )

	RANK_FAMILY_POINTS_TYPE mFamilyTaoRankOutdated;	// ����Ʒ������ʷ����( �ͻ�����ʾ�� )
	RANK_FAMILY_POINTS_TYPE mFamilyTaoRankInTime;	// ����Ʒ����ʵʱ����( ������ )

	typedef CRankBoard<MAX_CORPS_HONOR_NUM , CPlayerRankTeamPoints, 1> RANK_CORPS_POINTS_TYPE;
	RANK_CORPS_POINTS_TYPE mCorpsRankOutdated;	// ����PVP��ʷ����( �ͻ�����ʾ�� )
	RANK_CORPS_POINTS_TYPE mCorpsRankInTime;	// ����PVPʵʱ����( ������ )

	RANK_CORPS_POINTS_TYPE mCorpsBossScoreRankOutdated;		// ����boss������ʷ����( �ͻ�����ʾ�� )
	RANK_CORPS_POINTS_TYPE mCorpsBossScoreRankInTime;		// ����boss����ʵʱ����( ������ )

	RANK_CORPS_POINTS_TYPE mCorpsCollectActiveRankOutdated;		// ���Ųɼ���Ծ����ʷ����( �ͻ�����ʾ�� )
	RANK_CORPS_POINTS_TYPE mCorpsCollectActiveRankInTime;		// ���Ųɼ���Ծ��ʵʱ����( ������ )

	typedef CRankBoard<MAX_RANK_CHARM_NUM, CPlayerRankCharm, 1> RANK_CHARM_TYPE;
	RANK_CHARM_TYPE mCharmRankOutdated;	// ��ʷ����( �ͻ�����ʾ�� )
	RANK_CHARM_TYPE mCharmRankInTime;	// ʵʱ����( ������ )

	typedef CRankBoard<MAX_FLY_DUNG_NUM, CPlayerRankFlyDung, 1> RANK_FLY_DUNG_TYPE;
	RANK_FLY_DUNG_TYPE mFlyDungRankOutdated;	// ���и�����ʷ����( �ͻ�����ʾ�� )
	RANK_FLY_DUNG_TYPE mFlyDungRankInTime;		// ���и���ʵʱ����( ������ )

	typedef CRankBoard<MAX_COMMON_NUM, CPlayerRankCommon, 1> RANK_COMMON_WORLDRANK_TYPE;
	RANK_COMMON_WORLDRANK_TYPE mZhanGongOutdated;	// ս��( �ͻ�����ʾ�� )
	RANK_COMMON_WORLDRANK_TYPE mZhanGongInTime;		// ս��( ������ )

	RANK_COMMON_WORLDRANK_TYPE mZhiGuoOutDated;		// �ι�( �ͻ�����ʾ�� )
	RANK_COMMON_WORLDRANK_TYPE mZhiGuoInTime;		// �ι�( ������ )

	RANK_COMMON_WORLDRANK_TYPE mTongShuaiOutdated;		// ͳ˧( �ͻ�����ʾ�� )
	RANK_COMMON_WORLDRANK_TYPE mTongShuaiInTime;		// ͳ˧( ������ )

	RANK_COMMON_WORLDRANK_TYPE mWisAllOutdated;		// �Ż���ֵ( �ͻ�����ʾ�� )
	RANK_COMMON_WORLDRANK_TYPE mWisAllInTime;		// �Ż���ֵ( ������ )

	RANK_COMMON_WORLDRANK_TYPE mYunxiaoOutdated;	// ����������( �ͻ�����ʾ�� )
	RANK_COMMON_WORLDRANK_TYPE mYunxiaoInTime;		// ����������( ������ )

	typedef CRankBoard<MAX_COMMON_NUM, CPlayerRankCommon, MAX_COUNTRY+1> RANK_COMMON_ALLRANK_TYPE;
	RANK_COMMON_ALLRANK_TYPE mWeekCharmIncOutdated;		// ���ۼ�����ֵ����( �ͻ�����ʾ�� )
	RANK_COMMON_ALLRANK_TYPE mWeekCharmIncInTime;		// ���ۼ�����ֵ����( ������ )

	RANK_COMMON_WORLDRANK_TYPE mShideOutdated;		// ʦ��( �ͻ�����ʾ�� )
	RANK_COMMON_WORLDRANK_TYPE mShideInTime;		// ʦ��( ������ )

	RANK_COMMON_WORLDRANK_TYPE mXianYuanOutdated;	// ��Ե( �ͻ�����ʾ�� )
	RANK_COMMON_WORLDRANK_TYPE mXianYuanInTime;		// ��Ե( ������ )

	RANK_COMMON_WORLDRANK_TYPE mChuShiOutdated;		// ��ʦ( �ͻ�����ʾ�� )
	RANK_COMMON_WORLDRANK_TYPE mChuShiInTime;		// ��ʦ( ������ )

	RANK_COMMON_WORLDRANK_TYPE mYunLvOutdated;		// ����������( �ͻ�����ʾ�� )
	RANK_COMMON_WORLDRANK_TYPE mYunLvInTime;		// ����������( ������ )

	RANK_COMMON_ALLRANK_TYPE   mLastWeekCharmInc;		// �����ۼ�����ֵ����( �ͻ�����ʾ�� )

	RANK_COMMON_WORLDRANK_TYPE mWuDidongOutdated;		// �޵׶�����( �ͻ�����ʾ�� )
	RANK_COMMON_WORLDRANK_TYPE mWuDidongInTime;			// �޵׶�����( ������ )

	RANK_COMMON_WORLDRANK_TYPE mGlobalWarOutdated;		// ���ս����( �ͻ�����ʾ�� )
	RANK_COMMON_WORLDRANK_TYPE mGlobalWarInTime;		// ���ս����( ������ )

	RANK_COMMON_WORLDRANK_TYPE m_SpiritOutdated;		// ��������( �ͻ�����ʾ�� )
	RANK_COMMON_WORLDRANK_TYPE m_SpiritInTime;			// ��������( ������ )


	//CWTimer	mRankUpdateTimer;		// ��ʱ�����(�Ƿ�����һ�죬��һ��)
	CWTimer mInTimeRankSaveTimer;	// ��ʱ����ʵʱ��ļ��
	CWTimer mHalfHourTimer;			// ��Сʱtimer

	typedef lk::hash_map<int, int, SCENE_AT_GATE_CAP> RECV_SCENE_LIST_TYPE;
	
	RECV_SCENE_LIST_TYPE mRecvSceneList[REFRESHTYPE_ALL];

	template< typename TYPE >
	int FillTopTenData( TYPE* vpMsg, int nCountryID )
	{
		if ( vpMsg == NULL )
		{
			return -1;
		}
		
		PBRankTopTen* tpTopTen = vpMsg->add_toptenlist();
		int tCharList[ TOPTEN_VALUE ] = { 0 };
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
			tCharList[i] = 0;

		// -- ����ȼ����а�
		// ����
		mLevelRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), nCountryID );
		tpTopTen->set_ranktype( RANKTYPE_LEVEL_MYNATION );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// ȫ������
		tpTopTen = vpMsg->add_toptenlist();
		mLevelRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_LEVEL_ALL );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// -- ӵ�вƸ����а�
		// �ǰﶨ��
		tpTopTen = vpMsg->add_toptenlist();
		mMoneyRankOutdated[FREE_MONEY].GetTopTen( tCharList, ARRAY_CNT( tCharList ), nCountryID );
		tpTopTen->set_ranktype( RANKTYPE_MONEY_NOBIND );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// �ܼ�
		tpTopTen = vpMsg->add_toptenlist();
		mMoneyRankOutdated[ALL_MONEY].GetTopTen( tCharList, ARRAY_CNT( tCharList ), nCountryID );
		tpTopTen->set_ranktype( RANKTYPE_MONEY_ALL );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// -- ɱ�������а�
		// ���ܻ���
		tpTopTen = vpMsg->add_toptenlist();
		mKillRankOutdated[KILL_PROT_NATION].GetTopTen( tCharList, ARRAY_CNT( tCharList ), nCountryID );
		tpTopTen->set_ranktype( RANKTYPE_KILL_PROT_NATION );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// ���ܳ���
		tpTopTen = vpMsg->add_toptenlist();
		mKillRankOutdated[KILL_OUT].GetTopTen( tCharList, ARRAY_CNT( tCharList ), nCountryID );
		tpTopTen->set_ranktype( RANKTYPE_KILL_OUT );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// ������ɱ��
		tpTopTen = vpMsg->add_toptenlist();
		mKillRankOutdated[KILL_TOTAL].GetTopTen( tCharList, ARRAY_CNT( tCharList ), nCountryID );
		tpTopTen->set_ranktype( RANKTYPE_KILL_TOTAL );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// -- ��ѫ���а�
		// �����ܹ�ѫ
		tpTopTen = vpMsg->add_toptenlist();
		mHonorRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_KILL_TOTAL );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// �����ܹ�ѫ
		tpTopTen = vpMsg->add_toptenlist();
		mHonorRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), nCountryID );
		tpTopTen->set_ranktype( RANKTYPE_HONER_MYNATION );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// -- �����������а�
		tpTopTen = vpMsg->add_toptenlist();
		mDieNumRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_DIE );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// -- ������������а�
		tpTopTen = vpMsg->add_toptenlist();
		mEndTaskRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_END_TASK );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// -- ����ʱ�����а�
		tpTopTen = vpMsg->add_toptenlist();
		mOnLineRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_ONLINE_TIME );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// -- ��Ҹ���
		tpTopTen = vpMsg->add_toptenlist();
		mPantaoRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_PANTAO_MARK );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// -- ��������
		tpTopTen = vpMsg->add_toptenlist();
		mLonggongRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_LONGGONG_MARK );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// ԭ�ظ������(ȫ��)
		tpTopTen = vpMsg->add_toptenlist();
		mOriginReliveRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_ORIGINRELIVETIMES );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// ɱ����Ӫ����(ȫ��)
		tpTopTen = vpMsg->add_toptenlist();
		mKillSameNationRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_KILLSAMENATIONNUM );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// ɱ����(ȫ��)
		tpTopTen = vpMsg->add_toptenlist();
		mKillOgreRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_KILLOGRENUM );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		// ����ʧ�ܴ���(ȫ��)
		tpTopTen = vpMsg->add_toptenlist();
		mUpFailRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_UPFAILNUM );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}

		// ���а�ƺ������޸� [12/18/2009 Macro]

		// ��������������
		tpTopTen = vpMsg->add_toptenlist();
		mDayantaRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_DAYANTA );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}

		// ���Ҷ���������
		tpTopTen = vpMsg->add_toptenlist();
		mDaLuanDouOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_LASTONE );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		
		// ���Ҷ��ܻ������а�
		tpTopTen = vpMsg->add_toptenlist();
		mDaLuanDouTotalOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_TOTAL_LASTONE );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}

		// ��������������
		tpTopTen = vpMsg->add_toptenlist();
		mLianhuadongRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_LIANHUADONG );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		
		// �Ʒ䶴��������
		tpTopTen = vpMsg->add_toptenlist();
		mHuangfengdongRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_HUANGFENGDONG );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
		
		// �ɾ͵�����
		tpTopTen = vpMsg->add_toptenlist();
		mAchiveRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_ACHIVE_POINT );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}
	
		// �øж�����
		tpTopTen = vpMsg->add_toptenlist();
		mFavorRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_FAVOR_POINT );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}

		// ή��������
		tpTopTen = vpMsg->add_toptenlist();
		mBadRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_BAD_POINT );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}

		// ����pvp��������
		tpTopTen = vpMsg->add_toptenlist();
		mFamilyRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_FAMILY_PVP );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}

		// ����Ʒ��������
		tpTopTen = vpMsg->add_toptenlist();
		mFamilyTaoRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_FAMILY_TAO );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}

		// ����pvp��������
		tpTopTen = vpMsg->add_toptenlist();
		mCorpsRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_CORPS_PVP );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}

		// ����boss��������
		FILL_TOP_TEN( RANKTYPE_CORPSBOSS_SCORE,mCorpsBossScoreRankOutdated );

		// ���Ųɼ���Ծ������
		FILL_TOP_TEN( RANKTYPE_CORPSCOLLECT_ACTIVE,mCorpsCollectActiveRankOutdated );


		// ����ɱ��������(����)
		tpTopTen = vpMsg->add_toptenlist();
		mDayKillRankOutdated[ KILL_PROT_NATION ].GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_KILL_PROT_NATION_TODAY );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}

		// ����ɱ��������(����)
		tpTopTen = vpMsg->add_toptenlist();
		mDayKillRankOutdated[ KILL_OUT ].GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_KILL_OUT_TODAY );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}

		// ���ձ�����ɱ������
		tpTopTen = vpMsg->add_toptenlist();
		mDayKillRankOutdated[ KILL_TOTAL ].GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_KILL_TOTAL_TODAY );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}

		// �������� ����ֵ [2/3/2010 Macro]
		tpTopTen = vpMsg->add_toptenlist();
		mCharmRankOutdated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );
		tpTopTen->set_ranktype( RANKTYPE_CHARM_VALUE );
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )
		{
			tpTopTen->add_charlist( tCharList[i] );
			tCharList[ i ] = 0; 
		}

		FILL_TOP_TEN( RANKTYPE_ZHANGONG,mZhanGongOutdated )
		FILL_TOP_TEN( RANKTYPE_ZHIGUO,mZhiGuoOutDated )
		FILL_TOP_TEN( RANKTYPE_TONGSHUAI,mTongShuaiOutdated )
		FILL_TOP_TEN( RANKTYPE_WIS,mWisAllOutdated )
		FILL_TOP_TEN( RANKTYPE_YUNXIAO,mYunxiaoOutdated )
		FILL_TOP_TEN( RANKTYPE_WUDIDONG,mWuDidongOutdated )
		FILL_TOP_TEN( RANKTYPE_GLOBALWAR,mGlobalWarOutdated )
		FILL_TOP_TEN( RANKTYPE_SPIRIT,m_SpiritOutdated )

		return 0;
	}
};
