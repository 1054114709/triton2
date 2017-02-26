#ifndef _RANKTYPE_
#define _RANKTYPE_

// ���а������
enum ERankType // ���а�����
{
	RANKTYPE_LEVEL_ALL				= 1, // ȫ���ĵȼ�����
	RANKTYPE_LEVEL_MYNATION			= 2, // �ҹ��ĵȼ�����
	RANKTYPE_MONEY_NOBIND			= 3, // ȫ���ķǰ�Ǯ
	RANKTYPE_MONEY_ALL				= 4, // ����Ǯ
	RANKTYPE_KILL_PROT_NATION		= 5, // ɱ����(���л���)
	RANKTYPE_KILL_OUT				= 6, // ɱ����(���г���)
	RANKTYPE_KILL_TOTAL				= 7, // ������ɱ��
	RANKTYPE_HONOR_ALL				= 8, // ���������ܹ�ѫ
	RANKTYPE_HONER_MYNATION			= 9, // ���ܱ����ܹ�ѫ
	RANKTYPE_DIE					= 10, // ��������(ȫ��)
	RANKTYPE_END_TASK				= 11, // ���������(ȫ��)
	RANKTYPE_ONLINE_TIME			= 12, // ����ʱ��(��ֵ������)
	RANKTYPE_PANTAO_MARK			= 13, // ��Ҹ������ۻ���
	RANKTYPE_LONGGONG_MARK			= 14, // �����������ۻ���
	RANKTYPE_ORIGINRELIVETIMES		= 15, // ԭ�ظ������(ȫ��)
	RANKTYPE_KILLSAMENATIONNUM		= 16, // ɱ����Ӫ����(ȫ��)
	RANKTYPE_KILLOGRENUM			= 17, // ɱ����(ȫ��)
	RANKTYPE_UPFAILNUM				= 18, // ����ʧ�ܴ���(ȫ��)
	RANKTYPE_KILL_PROT_NATION_TODAY	= 19, // ����ɱ����(����)
	RANKTYPE_KILL_OUT_TODAY			= 20, // ����ɱ����(����)
	RANKTYPE_KILL_TOTAL_TODAY		= 21, // ���ձ�����ɱ��
	RANKTYPE_HONOR_ALL_TODAY		= 22, // ������������
	RANKTYPE_HONER_MYNATION_TODAY	= 23, // ������Ӫ����
	RANKTYPE_DAYANTA				= 24, // ���������֣�ȫ����
	RANKTYPE_LIANHUADONG			= 25, // ���������֣�ȫ����
	RANKTYPE_HUANGFENGDONG			= 26, // �Ʒ䶴���֣�ȫ����
	RANKTYPE_ACHIVE_POINT			= 27, // �ɾ͵㣨ȫ����
	RANKTYPE_FAVOR_POINT			= 28, // �øжȣ�ȫ����
	RANKTYPE_BAD_POINT				= 29, // ����ȣ�ȫ����
	RANKTYPE_FAMILY_PVP				= 30, // ����PVP���֣�ȫ����
	RANKTYPE_CORPS_PVP				= 31, // ����PVP���֣�ȫ����
	RANKTYPE_FAMILY_TAO				= 32, // ����Ʒ���һ��֣�ȫ����
	RANKTYPE_CHARM_VALUE			= 33, // ����ֵ<��������>
	RANKTYPE_FLY_FB_MARK			= 34, // ���ƴ�ս��������
	RANKTYPE_ZHANGONG				= 35, // ս�������������棩
	RANKTYPE_ZHIGUO					= 36, // �ι������ڲŻ����棩
	RANKTYPE_TONGSHUAI				= 37, // ͳ�������ڲŻ����棩
	RANKTYPE_WIS					= 38, // �Ż���ֵ���ڲŻ����棩
	RANKTYPE_YUNXIAO				= 39, // ��������������
	RANKTYPE_WORLD_WEEKINCCHARM		= 40, // �����¼�����ֵ(����)
	RANKTYPE_CAMP_WEEKINCCHARM		= 41, // �����¼�����ֵ(����Ӫ)
	RANKTYPE_SHIDE					= 42, // ʦ�»��ֻ���ֵ���а�(����Ӫ)
	RANKTYPE_XIANYUANMARK			= 43, // ��Ե���ֻ���ֵ���а�(����Ӫ)
	RANKTYPE_CHUSHITU				= 44, // ��ʦͽ�����а�(����Ӫ)
	RANKTYPE_YUNXIAOTALEVEL			= 45, // ��������������(����)
	RANKTYPE_CAMPCHARM_LASTWEEK		= 46, // ���ܰٻ�������Ӫ���� (�¼�����ֵ(����Ӫ))
	RANKTYPE_WUDIDONG				= 47, // �޵׶���������
	RANKTYPE_LASTONE				= 48, // ���Ҷ���ǰ����
	RANKTYPE_TOTAL_LASTONE			= 49, // ���Ҷ��ܻ���
	RANKTYPE_GLOBALWAR				= 50, // ���ս����
	RANKTYPE_SPIRIT					= 51, // ��������
	RANKTYPE_CORPSBOSS_SCORE		= 52,  // ����boss����
	RANKTYPE_CORPSCOLLECT_ACTIVE	= 53,  // ���Ųɼ���Ծ��
	RANKTYPE_NEW_YUNXIAO			= 54,  // ������60�����
	TOTAL_RANK_NUM					 , // ����
};

#define CONTINUS_ONBOARD_TOPNUM 10  // top10������ϰ�ͳ��

// �����а�ͳ�Ƶ��ϰ���������
enum ERankContinusOnBoardLimit
{
	RANKLIMIT_LEVEL					= 10, // �ȼ�����
	RANKLIMIT_MONEY_NOBIND			= 10, // �ǰ�Ǯ
	RANKLIMIT_MONEY_ALL				= 10, // ����Ǯ
	RANKLIMIT_KILL_PROT_NATION		= 10, // ɱ����(���ܻ���)
	RANKLIMIT_KILL_OUT				= 10, // ɱ����(���ܳ���)
	RANKLIMIT_KILL_TOTAL			= 10, // ������ɱ��
	RANKLIMIT_HONOR					= 10, // ��ѫ��ս��(����)
	RANKLIMIT_DIE					= 10, // ��������(ȫ��)
	RANKLIMIT_END_TASK				= 10, // ���������(ȫ��)
	RANKLIMIT_ONLINE_TIME			= 10, // ����ʱ��
	RANKLIMIT_REPETIONMARK			= 10, // �������ۻ���
	RANKLIMIT_ORIGINRELIVETIMES		= 10, // ԭ�ظ������(ȫ��)
	RANKLIMIT_KILLSAMENATIONNUM		= 10, // ɱ����Ӫ����(ȫ��)
	RANKLIMIT_KILLOGRENUM			= 10, // ɱ����(ȫ��)
	RANKLIMIT_UPFAILNUM				= 10, // ����ʧ�ܴ���(ȫ��)
	RANKLIMIT_ACHIVE				= 10, // �ɾ͵�(ȫ��)
	RANKLIMIT_FAVBAD				= 10, // �øС����(ȫ��)
	RANKLIMIT_TEAM					= 10, // �Ŷ�
	RANKLIMIT_CHARM					= 10, // ��������
	RANKLIMIT_WIS					= 10, // �Ż�
	RANKLIMIT_COMMON				= 10, // ͨ��
};

// ���а�ˢ������
enum RefreshType  
{
	REFRESHTYPE_DAYLY,			// ÿ��ˢ��
	REFRESHTYPE_HALFHOUR,		// ��Сʱˢ��
	REFRESHTYPE_ALL,			// ȫ��
};

#define NEW_RANK_FLAG  10000
#define SINGLE_PAK_LINE	 200	// 	ÿ�������͵���Ҹ���

// ����������ɱ�־
#define LOADFLAG1	0x0F
#define LOADFLAG2	0xF0
#define LOADOK		0xFF

// �����
// ÿ��UPDATE���а�
#define DAILY_UPDATE( InTime, OutDated, RankLimit, RankType) \
	InTime.CompareWithOld( OutDated, RankLimit );	\
	OutDated = InTime;								\
	OutDated.SaveRankDataToDB( RankType, true );    \
	OutDated.CheckRank();							\
	LOG_NOTICE("rank", "CheckRank type %d end", RankType );

// ����ʵʱ��
#define LOAD_INTIME_FROM_DB( Rank_Type, Data_Obj, Data_Class ) \
		case Rank_Type: \
			{\
				Data_Obj.OnLoadRankData(\
					Data_Class( atoi( pSqlResponse->fieldvalue( 0 + tRowIndex * nColNum ).c_str() ),\
					(const char*)pSqlResponse->fieldvalue( 1 + tRowIndex * nColNum ).c_str(),\
					atoi( pSqlResponse->fieldvalue( 2 + tRowIndex * nColNum ).c_str() ),\
					atoi( pSqlResponse->fieldvalue( 3 + tRowIndex * nColNum ).c_str() ),\
					atoi( pSqlResponse->fieldvalue( 4 + tRowIndex * nColNum ).c_str() ),\
					atoi( pSqlResponse->fieldvalue( 5 + tRowIndex * nColNum ).c_str() )\
					), atoi( pSqlResponse->fieldvalue( 7 + tRowIndex * nColNum ).c_str() )\
					, atoi( pSqlResponse->fieldvalue( 8 + tRowIndex * nColNum ).c_str() )\
					);\
				break;\
			}

// ������ʷ��
#define LOAD_OUTDATED_FROM_DB( Rank_Type, Data_Obj, Data_Class ) \
		case Rank_Type:\
			{\
				Data_Obj.OnLoadRankData(\
					Data_Class( atoi( pSqlResponse->fieldvalue( 0 + tRowIndex * nColNum ).c_str() ),\
					(const char*)pSqlResponse->fieldvalue( 1 + tRowIndex * nColNum ).c_str(),\
					atoi( pSqlResponse->fieldvalue( 2 + tRowIndex * nColNum ).c_str() ),\
					atoi( pSqlResponse->fieldvalue( 3 + tRowIndex * nColNum ).c_str() ),\
					atoi( pSqlResponse->fieldvalue( 4 + tRowIndex * nColNum ).c_str() ),\
					atoi( pSqlResponse->fieldvalue( 5 + tRowIndex * nColNum ).c_str() ),\
					atoi( pSqlResponse->fieldvalue( 7 + tRowIndex * nColNum ).c_str() ),\
					atoi( pSqlResponse->fieldvalue( 8 + tRowIndex * nColNum ).c_str() ),\
					atoi( pSqlResponse->fieldvalue( 9 + tRowIndex * nColNum ).c_str() )\
					), atoi( pSqlResponse->fieldvalue( 10 + tRowIndex * nColNum ).c_str() )\
					, atoi( pSqlResponse->fieldvalue( 11 + tRowIndex * nColNum ).c_str() )\
					);\
				break;\
			}

// ��Ӧ���
#define PLAYER_GET_RANK( Rank_Type, MaxNum, Rank_Obj_Type, Rank_Obj, World_ID )\
		case Rank_Type:\
			{\
				nNum = std::min( nNum , (int)MaxNum );\
				if ( nNum <= 0 )\
					return -1;\
				Rank_Obj_Type::CCountryRank* pRankData = Rank_Obj.GetCountryRank( World_ID );\
				LK_ASSERT( pRankData != NULL, return -1 );\
				pRankMeta = (CPlayerRankMeta*)pRankData->mContainer;\
				nMaxSize = (int)pRankData->Size();\
				Rank_Obj_Type::CCountryRank::KeyMap::iterator it = pRankData->mKeyMap.find( pRankReq->charid() );\
				if ( it != pRankData->mKeyMap.end() )\
				{\
					LK_ASSERT( it->second >= 0 && it->second < pRankData->Size(), return -1 );\
					tRetMsg.set_myrankchange(pRankData->mContainer[it->second].GetRankChange());\
					tRetMsg.set_myrankindex( it->second+1 );\
				}\
				break;\
			}

// ���ƺ�
#define FILL_TOP_TEN( Rank_Type, Rank_OutDated  ) \
		tpTopTen = vpMsg->add_toptenlist(); \
		Rank_OutDated.GetTopTen( tCharList, ARRAY_CNT( tCharList ), 0 );\
		tpTopTen->set_ranktype( Rank_Type );\
		for( unsigned int i = 0; i < ARRAY_CNT( tCharList ); i ++ )\
		{\
			tpTopTen->add_charlist( tCharList[i] );\
			tCharList[ i ] = 0; \
		}

// ��óƺ�
#define OBTAIN_TOP10( RANK_TYPE, Rank_OutDated, CountryID, Rank_Type )\
		RANK_TYPE::CCountryRank* pRank##Rank_OutDated = Rank_OutDated.GetCountryRank( CountryID );\
		LK_ASSERT( pRank##Rank_OutDated != NULL, return -1 );\
		for ( int i = 0; i < TOPTEN_VALUE; i ++ )\
		{\
			if ( pRank##Rank_OutDated->mContainer[ i ].HashKey() == tpReq->charid() )\
			{\
				PBRankTitle* tpTitle = tPara.add_ranktitle();\
				tpTitle->set_ranktype( Rank_Type );\
				tpTitle->set_index( i );\
			}		\
		}

#endif
