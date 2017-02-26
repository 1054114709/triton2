#include "activity.h"
#include "gateobj_manager.h"
#include "gatelogic.h"
#include "servermessage_in.h"
#include "nameservice.h"
#include "servermessage_pb.hxx.pb.h"
#include "gmmessage_pb.hxx.pb.h"
#include "tinyxml.h"
#include "core_service.h"
#include "gateobj_manager_imp.h"
#include "ActivityYQS.h"

using namespace GateServer;
using namespace std;
#include <list>

template<> CServiceActivity* CSingleton< CServiceActivity >::spSingleton = NULL;

// string fmt must be is YYYY-MM-DD HH24:MI:SS
time_t GetTimeSecond(const char* szTime)
{
	char year[4+1] = {0};
	char month[2+1] = {0};
	char day[2+1] = {0};

	char hh24[2+1] = {0};
	char mi[2+1] = {0};
	char ss[2+1] = {0};

	if (szTime == NULL) return -1;

	sscanf(szTime, "%4[0-9]-%2[0-9]-%2[0-9] %2[0-9]:%2[0-9]:%2[0-9]", year, month, day, hh24, mi, ss);

	if ( !year[0] || !month[0] || !day[0] || !hh24[0] || !mi[0] || !ss[0] ) return -1;

	struct tm tm;
	tm.tm_year = atoi(year) - 1900;
	tm.tm_mon = atoi(month) - 1;
	tm.tm_mday = atoi(day);

	tm.tm_hour = atoi(hh24);
	tm.tm_min = atoi(mi);
	tm.tm_sec = atoi(ss);

	return mktime(&tm);
}

void CServiceActivity::OnLaunchServer()
{
	// ���¶��������ļ�
	if ( mShmPtr->GetInitMode() == SHM_INIT )
	{
		LoadActivityFromXml(CGateLogic::GetSingletonPtr()->GetConfigDataFileNamePath(CGateLogic::GetSingleton().mConfig.nGameID,"activity/activity.xml"));
		////LoadActivityManagerFromXml("../config/data/activity/activity_manager.xml");
		//LoadActivityManagerFromXml(CGateLogic::GetSingletonPtr()->GetConfigDataFileNamePath(CGateLogic::GetSingleton().mConfig.nGameID,"activity/activity_manager.xml"));
		//int gameid = 0;
		//gameid = CGateLogic::GetSingleton().mConfig.nGameID;
		//LOG_ERROR("default", " activities_manager  xmlfile game_id = (%d) failure.", gameid);
		//ACTIVITYMANAGER::iterator it = m_pActivityManager.find( gameid );
		//if ( it != m_pActivityManager.end() )
		//{
		//	LOG_ERROR("default", " load activities_manager  xmlfile filename= (%s) failure.", (it->second).c_str());
		//	//LoadActivityFromXml((it->second).c_str());
		//    char tmpbuf[1024] = {0};
		//	strcpy( tmpbuf, CGateLogic::GetSingletonPtr()->GetConfigDataFileNamePath(CGateLogic::GetSingleton().mConfig.nGameID,"activity/") );
		//	strcat( tmpbuf, (it->second).c_str() );
		//	LoadActivityFromXml(tmpbuf);
		//}
	}else
	{
		RebuildItemIndex();
	}
	/*LoadSceneAvtivitys("../config/data/activity/induct_server.xml");*/
	LoadSceneAvtivitys(CGateLogic::GetSingletonPtr()->GetConfigDataFileNamePath(CGateLogic::GetSingleton().mConfig.nGameID,"/activity/induct_server.xml"));
	CheckActivitys(true);

	// ע��������õĻص�����
	const char* pcConfigPath = CGateLogic::GetSingletonPtr()->GetConfigDataFileNamePath(CGateLogic::GetSingleton().mConfig.nGameID,"activity/activity.xml");
	CGateServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CServiceActivity::LoadActivityXmlCallback);

	pcConfigPath = CGateLogic::GetSingletonPtr()->GetConfigDataFileNamePath(CGateLogic::GetSingleton().mConfig.nGameID,"activity/induct_server.xml");
	CGateServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CServiceActivity::LoadInductXmlCallback);
}

// ����������е����ݣ��ؽ�����
void CServiceActivity::RebuildItemIndex()
{
	CGateObjManagerImp::ObjMng_ActivityItems* pPool= NULL;
	if ( CGateObjManager::GetSingleton().mGateObjManagerImp != NULL)
	{
		pPool = &(CGateObjManager::GetSingleton().mGateObjManagerImp->mActivityItemsPool);
	}

	if(pPool== NULL) return;

	CGateObjManagerImp::ObjMng_ActivityItems::iterator iter = pPool->begin();
	for(;iter!= pPool->end(); iter++)
	{
		CActivityItem* pItem=  &(*iter);
		if (pItem!= NULL)
		{
			m_pActivityItems->insert(ACTIVITYITEMSTYPE::value_type(pItem->GetPkgCode(), pItem->get_id()));
		}
	}
}

void CServiceActivity::ReloadCfg()
{
	// �������á��߼������ŵ��ص�������
	const char* pcConfigPath = CGateLogic::GetSingletonPtr()->GetConfigDataFileNamePath(CGateLogic::GetSingleton().mConfig.nGameID,"activity/activity.xml");
	CServiceActivity::GetSingleton().LoadActivityXmlCallback(pcConfigPath);
	
	pcConfigPath = CGateLogic::GetSingletonPtr()->GetConfigDataFileNamePath(CGateLogic::GetSingleton().mConfig.nGameID,"activity/induct_server.xml");
	CServiceActivity::GetSingleton().LoadInductXmlCallback(pcConfigPath);
}

void CServiceActivity::OnExitServer()
{
	
}

void CServiceActivity::OnTimer( unsigned int vTickCount, unsigned int vTickOffset )
{
	if( mCheckActivityTimer.Elapse( vTickOffset) )
	{
		CheckActivitys();
	}
}

/*
void CServiceActivity::LoadActivityItemFromDB(int nStart, int nCount)
{
	const char* stmtfmt =  " SELECT item_id, template_id, number, slot_property1, slot_property2, slot_property3, slot_property4,"
							" slot_jewel1, slot_jewel2, slot_jewel3, slot_jewel4, slot_spell, level, producer_name, slot_number "
							" FROM GMS_ACTIVITY_ITEM WHERE valid = 1 limit %d, %d";

	if (! CGateLogic::GetSingleton().ExecuteSql(em_dbsession_activityitem, nStart, nCount, 
				1, SQL_NEED_CALLBACK, SELECT, stmtfmt, nStart, nCount))
	{
		LOG_ERROR("default", "create dbsession on function %s", __FUNCTION__);
	}
}
*/
//Ӧ��Ϸ��ͬ���xml ����gateserver����� add by  qiufufu 
void CServiceActivity::LoadActivityManagerFromXml(const char* xmlfile)
{
	TiXmlDocument xmldoc;
	xmldoc.LoadFile( xmlfile );

	TiXmlElement* tpRoot= xmldoc.FirstChildElement();
	if (tpRoot == NULL)
	{
		LOG_ERROR("default", "load activitityManager from xmlfile(%s) failure.", xmlfile);
		return;
	}
	//load section menus
	TiXmlElement* pActivityElem = tpRoot->FirstChildElement("menus");
	if ( ! pActivityElem ) 
	{
		LOG_ERROR("default", "load activitityManager form xmlfile(%s) on section(%s)", xmlfile, "menus");
		return;
	}
	m_pActivityManager.clear();
	TiXmlElement* tpElement = pActivityElem->FirstChildElement();
	for ( ; tpElement != NULL; tpElement = tpElement->NextSiblingElement())
	{
		const char* p = tpElement->Attribute("game_id");
		if(p) 
		{
			const char* name = tpElement->Attribute("activitityFileName");
			if (name)
			{
				m_pActivityManager.insert( std::pair<int, lk::CString32>(atoi(p),lk::CString32(name)));
				//LOG_ERROR("default", "load activitityManager form game_id(%d),filname =(%s) ", atoi(p), lk::CString32( name ));
			}	
		}
	}
}

void CServiceActivity::LoadActivityFromXml(const char* xmlfile)
{
	TiXmlDocument xmldoc;
	xmldoc.LoadFile( xmlfile );

	TiXmlElement* tpRoot= xmldoc.FirstChildElement();
	if (tpRoot == NULL)
	{
		LOG_ERROR("default", "load activities from xmlfile(%s) failure.", xmlfile);
		return;
	}

	//load section menus
	TiXmlElement* pActivityElem = tpRoot->FirstChildElement("menus");
	if ( ! pActivityElem ) 
	{
		LOG_ERROR("default", "load activities form xmlfile(%s) on section(%s)", xmlfile, "menus");
		return;
	}

	time_t now = time(0);
	TiXmlElement* tpElement = pActivityElem->FirstChildElement();
	for ( ; tpElement != NULL; tpElement = tpElement->NextSiblingElement())
	{
		CActivity activity;
		const char* p = tpElement->Attribute("menu_id");
		if(p) activity.SetMenuID( atoi(p)); else continue;

		/*
		p = tpElement->Attribute("code");
		if(p) activity.SetCode(p); else continue;
		*/

		p = tpElement->Attribute("desc");
		if(p) activity.SetDesc(p); else continue;

		// ���ÿ�ʼʱ��
		p = tpElement->Attribute("begin_time");
		time_t seconds = GetTimeSecond(p);
		if ( seconds == -1)
		{
			LOG_ERROR("default", "Can not convert %s to seconds", p);
			continue;
		}
		activity.SetBeginTime(seconds);


		// ���û����ʱ��
		p = tpElement->Attribute("end_time");
		seconds = GetTimeSecond(p);
		if ( seconds == -1)
		{
			LOG_ERROR("default", "Can not convert %s to seconds", p);
			continue;
		}
		activity.SetEndTime(seconds);

		// δ�����Ļȫ������
		if ( activity.GetEndTime() > now)
		{
			if (m_Activities.insert(ACTIVITYTYPE::value_type(activity.GetMenuID(), activity)).second == false)
			{
				LOG_ERROR("default", "Insert into m_Activities error menu_id(%d), code=(%s)", 
						activity.GetMenuID(), activity.GetCode());
			}
		}
	}

	//load section itmes
	TiXmlElement* pItemElem = tpRoot->FirstChildElement("items");
	if ( ! pItemElem ) 
	{
		LOG_ERROR("default", "load activities form xmlfile(%s) on section(%s)", xmlfile, "items");
		return;
	}

	TiXmlElement* tpProdElement = pItemElem->FirstChildElement();
	for ( ; tpProdElement != NULL; tpProdElement = tpProdElement->NextSiblingElement())
	{
		const char* pszItemCode = tpProdElement->Attribute("code");
		if ( pszItemCode == NULL) continue;

		const char* pszItemID = tpProdElement->Attribute("item_id");
		if ( pszItemID  == NULL) continue;

		m_pActivityItems->insert( ACTIVITYITEMSTYPE::value_type(pszItemCode, atoi(pszItemID)));

		/*
		const char* pszItemCode = tpProdElement->Attribute("code");
		if ( pszItemCode == NULL) continue;

		tpElement = tpProdElement->FirstChildElement();
		for ( ; tpElement != NULL; tpElement = tpElement->NextSiblingElement())
		{
			// create obj
			CActivityItem* pActivityItem = 
				(CActivityItem*) CGateObjManager::GetSingletonPtr()->CreateObject(OBJTYPE_ACTIVITYITEM);

			if ( pActivityItem == NULL )
			{
				LOG_ERROR("default", "create CActivityItem fail, please check pool_size");
				return;
			}

			const char* p = NULL;
			if( (p = tpElement->Attribute("template")) != NULL)
			{
				pActivityItem->SetTemplateID(atoi(p));
			}else
			{
				LOG_ERROR("default", "load activity item on attr:template error");
				CGateObjManager::GetSingletonPtr()->DestroyObject(pActivityItem->get_id());
				continue;
			}

			if( (p = tpElement->Attribute("number")) != NULL)
			{
				pActivityItem->SetNumber(atoi(p));
			}else
			{
				LOG_ERROR("default", "load activity item on attr:number error");
				CGateObjManager::GetSingletonPtr()->DestroyObject(pActivityItem->get_id());
				continue;
			}

			if( (p = tpElement->Attribute("special")) != NULL)
			{
				pActivityItem->SetSpecial(atoi(p));
			}else
			{
				LOG_ERROR("default", "load activity item on attr:special error");
				CGateObjManager::GetSingletonPtr()->DestroyObject(pActivityItem->get_id());
				continue;
			}

			if (pActivityItem->IsSpecial() )
			{
				if( (p = tpElement->Attribute("level")) != NULL)
				{
					pActivityItem->SetLevel(atoi(p));
				}else
				{
					LOG_ERROR("default", "load activity item on attr:level error");
					CGateObjManager::GetSingletonPtr()->DestroyObject(pActivityItem->get_id());
					continue;
				}

				if( (p = tpElement->Attribute("producer")) != NULL)
				{
					pActivityItem->SetProduceName(p);
				}

				if( (p = tpElement->Attribute("rune")) != NULL)
				{
					pActivityItem->SetRuneID(atoi(p));
				}

				if( (p = tpElement->Attribute("property")) != NULL)
				{
					char p0[32]= {0};
					char p1[32]= {0};
					char p2[32]= {0};
					char p3[32]= {0};
					char p4[32]= {0};
					char p5[32]= {0};
					char p6[32]= {0};
					char p7[32]= {0};


					sscanf(p, "%[0-9],%[0-9],%[0-9],%[0-9],%[0-9],%[0-9],%[0-9],%[0-9]", p0, p1, p2, p3, p4, p5, p6, p7);

					if ( !p0[0] || !p1[0] || !p2[0] || !p3[0] || !p4[0] || !p5[0] || !p6[0] || !p7[0]) 
					{
						LOG_ERROR("default", "load activity item on attr:property, it's format must like xx,xx,xx,xx,xx,xx,xx,xx");
						CGateObjManager::GetSingletonPtr()->DestroyObject(pActivityItem->get_id());
						continue;
					}

					pActivityItem->SetProperty(0, atoi(p0));
					pActivityItem->SetProperty(1, atoi(p1));
					pActivityItem->SetProperty(2, atoi(p2));
					pActivityItem->SetProperty(3, atoi(p3));
					pActivityItem->SetProperty(4, atoi(p4));
					pActivityItem->SetProperty(5, atoi(p5));
					pActivityItem->SetProperty(6, atoi(p6));
					pActivityItem->SetProperty(7, atoi(p7));
				}else
				{
					LOG_ERROR("default", "load activity item on attr:producer error");
					CGateObjManager::GetSingletonPtr()->DestroyObject(pActivityItem->get_id());
					continue;
				}

				if( (p = tpElement->Attribute("judge")) != NULL)
				{
					char p0[32]= {0};
					char p1[32]= {0};
					char p2[32]= {0};
					char p3[32]= {0};

					sscanf(p, "%[0-9],%[0-9],%[0-9],%[0-9]", p0, p1, p2, p3);

					if (!p0[0] || !p1[0] || !p2[0] || !p3[0])
					{
						LOG_ERROR("default", "load activity item on attr:judge, it's format must like xx,xx,xx,xx");
						CGateObjManager::GetSingletonPtr()->DestroyObject(pActivityItem->get_id());
						continue;
					}

					pActivityItem->SetJudge(0, atoi(p0));
					pActivityItem->SetJudge(1, atoi(p1));
					pActivityItem->SetJudge(2, atoi(p2));
					pActivityItem->SetJudge(3, atoi(p3));
				}

				if( (p = tpElement->Attribute("jewel")) != NULL)
				{
					char p0[32]= {0};
					char p1[32]= {0};
					char p2[32]= {0};
					char p3[32]= {0};
					char p4[32]= {0};
					char p5[32]= {0};

					sscanf(p, "%[0-9],%[-0-9],%[-0-9],%[-0-9],%[-0-9],%[-0-9]", p0, p1, p2, p3, p4, p5);

					if (!p0[0] || !p1[0] || !p2[0] || !p3[0] || !p4[0] || !p5[0])
					{
						LOG_ERROR("default", "load activity item on attr:jewel, it's format must like xx,xx,xx,xx,xx,xx");
						CGateObjManager::GetSingletonPtr()->DestroyObject(pActivityItem->get_id());
						continue;
					}

					pActivityItem->SetInitSlot(atoi(p0));

					pActivityItem->SetJewelID(0, atoi(p1));
					pActivityItem->SetJewelID(1, atoi(p2));
					pActivityItem->SetJewelID(2, atoi(p3));
					pActivityItem->SetJewelID(3, atoi(p4));
					pActivityItem->SetJewelID(4, atoi(p5));
				}

				if( (p = tpElement->Attribute("resist")) != NULL)
				{
					char p0[32]= {0};
					char p1[32]= {0};

					sscanf(p, "%[0-9],%[0-9]", p0, p1);

					if (!p0[0] || !p1[0])
					{
						LOG_ERROR("default", "load activity item on attr:resist, it's format must like xx,xx");
						CGateObjManager::GetSingletonPtr()->DestroyObject(pActivityItem->get_id());
						continue;
					}

					pActivityItem->SetResistType(atoi(p0));
					pActivityItem->SetResistLevel(atoi(p1));
				}

				if( (p = tpElement->Attribute("attack")) != NULL)
				{
					char p0[32]= {0};
					char p1[32]= {0};

					sscanf(p, "%[0-9],%[0-9]", p0, p1);

					if (!p0[0] || !p1[0])
					{
						LOG_ERROR("default", "load activity item on attr:attack, it's format must like xx,xx");
						CGateObjManager::GetSingletonPtr()->DestroyObject(pActivityItem->get_id());
						continue;
					}

					pActivityItem->SetAttackType(atoi(p0));
					pActivityItem->SetAttackLevel(atoi(p1));
				}
			}

			pActivityItem->SetPkgCode(pszItemCode);

			m_pActivityItems->insert( ACTIVITYITEMSTYPE::value_type(pszItemCode, pActivityItem->get_id()));
		}
		*/
	}
}



void CServiceActivity::OnAGIPSessionUserItemMinus( SysProtocol* pSysProto, 
		int nParam1, int nParam2, int nParam3, int nParam4, const char* szParam5)
{
	LK_ASSERT(pSysProto!= NULL && szParam5 , return);
	AGIPUserItemMinusRes* pprotores = (AGIPUserItemMinusRes*) pSysProto;
	
	int nRoleID = nParam1;
	//int nRoleLevel = nParam2;
	int nActivityID = nParam3;
	int nItemNum = nParam4;
	const char* szItemCode = szParam5;

	CGatePlayer* tpPlayer = CPlayerManager::GetSingleton().ScenePlayer(nRoleID);

	if(tpPlayer == NULL)
	{
		LOG_INFO("default", "player(Role=%d) is not in scene on function(%s)", nRoleID, __FUNCTION__);
		return;
	}

	//CheckPlayerEventAvailable(tpPlayer->mStatus, CGatePlayer::em_status_ingame_v4erating_itemminus);
	//tpPlayer->mStatus = CGatePlayer::em_status_ingame_idle;

	int32_t nResult;	
	pprotores->getResultCode(&nResult);

	CMessage tMessage;
	CMessageUserItemMinusResponse tFactMsg;

	tFactMsg.set_result(nResult);
	tFactMsg.set_roleid(nRoleID);

	if ( nResult == S_SUCCESS )
	{
		tFactMsg.mutable_item()->set_itemcode(szItemCode);
		tFactMsg.mutable_item()->set_number(nItemNum);
		tFactMsg.mutable_item()->set_activityid(nActivityID);

		LOG_INFO("default", "Player(%d:%s) Minus item_code(%s:%d) successfully(%d)", 
				tpPlayer->mCharID, tpPlayer->GetCharNameShow(), szItemCode, nItemNum, nResult);
	}else
	{
		LOG_ERROR("default", "Player(%d:%s) Minus item_code(%s:%d) error(%d)", 
				tpPlayer->mCharID, tpPlayer->GetCharNameShow(), szItemCode, nItemNum, nResult);
	}

	pbmsg_sethead(&tMessage, ID_E2S_USERITEMMINUS_RESPONSE, 0, 0, 0, 0, 0, 0);
	tMessage.set_msgpara((uint32_t) &tFactMsg);

	CGateServer::GetSingleton().Send2Scene(tpPlayer, &tMessage);
}

void CServiceActivity::OnAGIPSessionUserItemList( SysProtocol* pSysProto, int nParam1, int nParam2, int nParam3, int nParam4)
{
	LK_ASSERT(pSysProto!= NULL, return);
	AGIPUserItemListRes* pprotores = (AGIPUserItemListRes*) pSysProto;

	int nRoleID = nParam1;

	int nActivityID = nParam2;
	//int nRoleLevel = nParam3;
	//int nRoleMetier = nParam4;

	CGatePlayer* tpPlayer = CPlayerManager::GetSingleton().ScenePlayer(nRoleID);

	if(tpPlayer == NULL)
	{
		LOG_INFO("default", "player(Role=%d) is not in scene on function(%s)", nRoleID, __FUNCTION__);
		return;
	}

	//CheckPlayerEventAvailable(tpPlayer->mStatus, CGatePlayer::em_status_ingame_v4erating_activityitem);
	//tpPlayer->mStatus = CGatePlayer::em_status_ingame_idle;

	//convert it to protobuf and send it to game
	CMessage tMessage;
	CMessageUserItemListResponse tFactMsg;
	
	int32_t nResult = 0;
	int32_t nCount = 0;

	pprotores->getResultCode(&nResult);
	pprotores->getItemCount(&nCount);

	tFactMsg.set_roleid(nRoleID);
	tFactMsg.set_result(nResult);
	tFactMsg.set_menuid(nActivityID);


	//pprotores->showInfo();
	time_t now = time(0);

	for(int32_t i= 0; i < nCount; ++i)
	{
		char strItemCode[AGIP_ITEM_CODE_LEN+1] = {0};
		int nItemNum = 0;

		uint32_t nStartTime = 0;
		uint32_t nEndTime = 0;
		uint32_t nRActivityID = 0;
		 
		if (pprotores->getItemInfo(i, &nRActivityID, strItemCode, &nItemNum, &nStartTime, &nEndTime) == S_SUCCESS)
		{
			if ( (uint32) now > nEndTime || (uint32) now < nStartTime)
			{
				LOG_ERROR("default", " There are %d item %s for role(%d) on activity(%d) is expired(%d, %d)", 
						nItemNum, strItemCode, nRoleID, nRActivityID, nStartTime, nEndTime);
			}else
			{
				if ( memcmp(strItemCode, "i-", 2) == 0 	// �������
				|| strcmp(strItemCode, "s-money-0") == 0 //  δ�󶨵���Ϸ��
				|| strcmp(strItemCode, "s-money-1") == 0 // �󶨵���Ϸ��
				|| strcmp(strItemCode, "s-silver-1") == 0) // �Ѱ󶨵���Ԫ��
				{
					PBActivityItem* pPbActItem = tFactMsg.add_items();
					if ( pPbActItem != NULL)
					{
						pPbActItem->set_itemcode(strItemCode);
						pPbActItem->set_number(nItemNum);
						pPbActItem->set_activityid(nRActivityID);
					}

					LOG_DEBUG( "default", " There are %d item %s for role(%d) on activity(%d) is ok", 
						nItemNum, strItemCode, nRoleID, nRActivityID );
				}else
				{
					LOG_ERROR("default", " There are %d item %s for role(%d) on activity(%d) is invalid", 
						nItemNum, strItemCode, nRoleID, nRActivityID );
				}
			}
		}
	}

	pbmsg_sethead(&tMessage, ID_E2S_USERITEMLIST_RESPONSE, 0, 0, 0, 0, 0, 0);
	tMessage.set_msgpara((uint32_t) &tFactMsg);

	CGateServer::GetSingleton().Send2Scene(tpPlayer, &tMessage);
}


unsigned int CServiceActivity::CountSize()
{
	return sizeof(CServiceActivity);
}


CServiceActivity::CServiceActivity()
{
	m_pActivityItems = NULL;

	if( mShmPtr->GetInitMode() == SHM_INIT )		
	{
		Initialize();
	}else
	{
		Resume();
	}
}

CServiceActivity::~CServiceActivity()
{
	if ( m_pActivityItems != NULL) 
	{
		delete m_pActivityItems;
		m_pActivityItems = NULL;
	}
}

int CServiceActivity::Initialize()
{
	m_Activities.initailize();
	m_pActivityItems = new ACTIVITYITEMSTYPE;
	m_pActivityItems->initailize();
	m_pActivityManager.initailize();
	m_ActivityActions.initailize();
	m_nNextActivityIndex = 0;
	m_ActivityStates.initailize();
	m_ActivityInfo.initailize();
	

	mCheckActivityTimer = CWTimer( 1000 ); // 1����һ��

	return m_pActivityItems != NULL ?  0 : -1;
}

int CServiceActivity::Resume()
{
	m_pActivityItems = new ACTIVITYITEMSTYPE;
	return m_pActivityItems != NULL ?  0 : -1;
}

void* CServiceActivity::operator new( size_t size )
{
	return ( void* ) mShmPtr->CreateSegment( size );
}

void  CServiceActivity::operator delete( void* pointer )
{

}

//************************************************************************
// ���£�������������ػ�Ŀ���
//************************************************************************
// ���ص������л
void CServiceActivity::LoadSceneAvtivitys( const char* pFileName )
{
	LOG_NOTICE("default", "LOAD Activity from %s", pFileName );
	// TODO �������ʣ��� ȫ��֪ͨ


	m_ActivityActions.clear();
	m_nNextActivityIndex = 0;
	m_ActivityStates.clear();
	m_ActivityInfo.clear();

	TiXmlDocument xmldoc;
	xmldoc.LoadFile( pFileName );

	TiXmlElement* tpRoot= xmldoc.FirstChildElement();
	if (tpRoot == NULL)
	{
		LOG_ERROR("default", "load activities from xmlfile(%s) failure.", pFileName);
		return;
	}


	// �����ÿ�춼�е�

	// �����ָ�����ڲ��е�

	TiXmlElement* tpElement = tpRoot->FirstChildElement();
	for ( ; tpElement != NULL; tpElement = tpElement->NextSiblingElement())
	{
		const char* pStr = tpElement->Attribute("DataType");
		int tDataType = 0;
		if ( pStr != NULL )
			tDataType = ::atoi(pStr);

		pStr = tpElement->Attribute("TotalTimes");
		int tTotalTimes = 0;
		if ( pStr != NULL )
			tTotalTimes =::atoi(pStr);

		pStr = tpElement->Attribute("LevelLimit");
		int tLevelLimit = 0;
		if ( pStr != NULL )
			tLevelLimit = ::atoi(pStr);

		pStr = tpElement->Attribute("ID");
		int tID = 0;
		if ( pStr != NULL )
			tID = ::atoi(pStr);

		CSingleActivityInfo info;

		LOG_NOTICE("default", "LOAD Activity ID= %d", tID );

		if ( tID == 0 )
			continue;

		if ( tDataType == 0 ) // ÿ�춼�еĻ
		{
			TiXmlElement* tpElementChild = tpElement->FirstChildElement();
			while ( tpElementChild != NULL )
			{
				int tStartTime = 0;
				int tEndTime = 0;
				int tOgreID  = 0;
				int tDropID  = 0;
				int tOgreIndex  = 0;
				CSingleActivityInfo::MapDropInfo map_drop;

				const char* pStr = tpElementChild->Attribute("StartTime");
				if ( pStr != NULL )
					tStartTime = ::atoi(pStr);

				pStr = tpElementChild->Attribute("EndTime");
				if ( pStr != NULL )
					tEndTime = ::atoi(pStr);

				pStr = tpElementChild->Attribute("OgreID");
				if ( pStr != NULL )
					tOgreID = ::atoi(pStr);

				pStr = tpElementChild->Attribute("DropTableID");
				if ( pStr != NULL )
					tDropID = ::atoi(pStr);

				const char* pValue = tpElementChild->Value();

				if ( pValue != NULL && strcmp( pValue, "OgreIndex" ) == 0 )
				{
					const char* pIndex = tpElementChild->Attribute("Value");
					if ( pIndex != NULL )
					{
						tOgreIndex = ::atoi(pIndex);
					}
				}
				else if ( pValue != NULL && strcmp( pValue, "DropEx" ) == 0 ) // �ǰ���ͼˢ��
				{
					const char* pIndex = tpElementChild->Attribute("DropTableID");
					if ( pIndex != NULL )
					{
						map_drop.mDropID = ::atoi(pIndex);
					}

					pIndex = tpElementChild->Attribute("DropType");
					if ( pIndex != NULL )
					{
						map_drop.mDropType = ::atoi(pIndex);
					}

					pIndex = tpElementChild->Attribute("MapID");
					if ( pIndex != NULL )
					{
						strncpy( map_drop.mMaps, pIndex, sizeof(map_drop.mMaps)-1);
					}
				}

				if ( tStartTime != 0 || tEndTime != 0 ) // �����ʱ��ڵ�
				{
					CSingleSceneActivityObj obj;
					obj.m_nID = tID;
					obj.m_nLmtLevel = tLevelLimit;
					obj.m_nMaxTimes = tTotalTimes;

					obj.m_nType = ACTIVITY_START;
					obj.m_nTime = tStartTime;
					m_ActivityActions.push_back(obj);

					obj.m_nType = ACTIVITY_END;
					obj.m_nTime = tEndTime;
					m_ActivityActions.push_back(obj);
				}

				// ����������� �ǵ���ڵ�
				if ( tOgreID != 0 && tDropID != 0 )
				{
					LOG_NOTICE("default", "LOAD DROP %d-%d", tOgreID, tDropID);
					CSingleActivityInfo::DropInfo drop;
					drop.mOgreID = tOgreID;
					drop.mDropID = tDropID;
					info.mDropInfo.push_back(drop);
				}

				// �����ͼ����ڵ�
				if (map_drop.mDropID != 0 )
				{
					LOG_NOTICE("default", "LOAD MAPDROP %d-%d-%s", map_drop.mDropID, map_drop.mDropType, map_drop.mMaps);
					info.mMapDropInfo.push_back(map_drop);
				}
				
				// ��������
				if ( tOgreIndex != 0 )
				{
					LOG_NOTICE("default", "LOAD OGREINDEX %d", tOgreIndex);
					if ( info.mOgreIndex.size() < ACTIVITY_OGREINDEX_SZ )
						info.mOgreIndex.push_back(tOgreIndex);
					else
						LOG_ERROR("default", "OGREINDEX over!!!!!!!!!!!!!!");
				}

				tpElementChild = tpElementChild->NextSiblingElement();
			}
		}
		else if ( tDataType == 1 ) // ָ�����ڵĻ
		{
			// �ȱ��������б� ���н���û
			bool bFound = false;
			time_t t = time( 0 );
			tm tmp;
			localtime_r( &t, &tmp);
			TiXmlElement* tpElementChild = tpElement->FirstChildElement();
			while ( tpElementChild != NULL )
			{
				const char* pValue = tpElementChild->Value();
				if ( pValue != NULL && strcmp( pValue, "Date" ) == 0 )
				{
					const char* pDate = tpElementChild->Attribute("Date");
					if ( pDate != NULL && IsToday(::atoi(pDate) ) )
					{
						bFound =true;
						//LOG_DEBUG("default", "***FOUND:1");
						break;
					}
					const char* pWeekDay = tpElementChild->Attribute("WeekDay");
					if ( pWeekDay != NULL )
					{
						int nWeekDay = ::atoi(pWeekDay);
						if ( nWeekDay != 0 && (nWeekDay == tmp.tm_wday || (nWeekDay==7&&tmp.tm_wday==0) ) )
						{
							bFound =true;
							//LOG_DEBUG("default", "***FOUND:2");
							break;
						}
					}
					const char* pMonthDay = tpElementChild->Attribute("MonthDay");
					if ( pMonthDay != NULL )
					{
						int nMonthDay = ::atoi(pMonthDay);
						if ( nMonthDay != 0 && nMonthDay == tmp.tm_mday )
						{
							bFound =true;
							//LOG_DEBUG("default", "***FOUND:3");
							break;
						}
					}
				}
				tpElementChild = tpElementChild->NextSiblingElement();
			}

			//LOG_DEBUG("default", "***FOUNDX:%d", bFound);
			if ( bFound ) // �ҵ���
			{
				tpElementChild = tpElement->FirstChildElement();
				while ( tpElementChild != NULL )
				{
					const char* pValue = tpElementChild->Value();
					if ( pValue != NULL && strcmp( pValue, "Time" ) == 0 )
					{
						int tStartTime = 0;
						int tEndTime = 0;

						const char* pStr = tpElementChild->Attribute("StartTime");
						if ( pStr != NULL )
							tStartTime = ::atoi(pStr);
						pStr = tpElementChild->Attribute("EndTime");
						if ( pStr != NULL )
							tEndTime = ::atoi(pStr);

						if ( tEndTime == 0 )
						{
							LOG_WARN("default", "activity id=%d passed", tID );
							tpElementChild = tpElementChild->NextSiblingElement();
							continue;
						}

						CSingleSceneActivityObj obj;
						obj.m_nID = tID;
						obj.m_nLmtLevel = tLevelLimit;
						obj.m_nMaxTimes = tTotalTimes;

						obj.m_nType = ACTIVITY_START;
						obj.m_nTime = tStartTime;
						m_ActivityActions.push_back(obj);

						obj.m_nType = ACTIVITY_END;
						obj.m_nTime = tEndTime;
						m_ActivityActions.push_back(obj);
					}
					else if( pValue != NULL && strcmp( pValue, "Drop" ) == 0 )
					{
						int tOgreID  = 0;
						int tDropID  = 0;

						const char* pStr = tpElementChild->Attribute("OgreID");
						if ( pStr != NULL )
							tOgreID = ::atoi(pStr);

						pStr = tpElementChild->Attribute("DropTableID");
						if ( pStr != NULL )
							tDropID = ::atoi(pStr);

						// �����������
						if ( tOgreID != 0 && tDropID != 0 )
						{
							LOG_NOTICE("default", "LOAD DROP2 %d-%d", tOgreID, tDropID);
							CSingleActivityInfo::DropInfo drop;
							drop.mOgreID = tOgreID;
							drop.mDropID = tDropID;
							info.mDropInfo.push_back(drop);
						}
					}
					else if( pValue != NULL && strcmp( pValue, "DropEx" ) == 0 )
					{
						CSingleActivityInfo::MapDropInfo map_drop;
						const char* pIndex = tpElementChild->Attribute("DropTableID");
						if ( pIndex != NULL )
						{
							map_drop.mDropID = ::atoi(pIndex);
						}

						pIndex = tpElementChild->Attribute("DropType");
						if ( pIndex != NULL )
						{
							map_drop.mDropType = ::atoi(pIndex);
						}

						pIndex = tpElementChild->Attribute("MapID");
						if ( pIndex != NULL )
						{
							strncpy( map_drop.mMaps, pIndex, sizeof(map_drop.mMaps)-1);
						}

						// �����ͼ����ڵ�
						if (map_drop.mDropID != 0 )
						{
							LOG_NOTICE("default", "LOAD MAPDROP2 %d-%d-%s", map_drop.mDropID, map_drop.mDropType, map_drop.mMaps);
							info.mMapDropInfo.push_back(map_drop);
						}
					}
					else if( pValue != NULL && strcmp( pValue, "OgreIndex" ) == 0 )
					{
						int tOgreIndex  = 0;

						const char* pStr = tpElementChild->Attribute("Value");
						if ( pStr != NULL )
							tOgreIndex = ::atoi(pStr);

						// ��������
						if ( tOgreIndex != 0 )
						{
							LOG_NOTICE("default", "LOAD OGREINDEX %d", tOgreIndex);
							if ( info.mOgreIndex.size() < ACTIVITY_OGREINDEX_SZ )
								info.mOgreIndex.push_back(tOgreIndex);
							else
								LOG_ERROR("default", "OGREINDEX over!!!!!!!!!!!!!!");
						}
					}
					tpElementChild = tpElementChild->NextSiblingElement();
				}
			}
		}

		// 1�����Ԫ�������
		LOG_DEBUG("default", "DROP REG %d->num %d", tID, info.mDropInfo.size() );
		m_ActivityInfo.insert( std::pair<int, CSingleActivityInfo>(tID, info) );
	}
	SortActivitys();
}

// ���� ��������
void CServiceActivity::SortActivitys()
{
	sort( m_ActivityActions.begin(), m_ActivityActions.end() );
	for ( SCENE_ACTIVITYTYPE::iterator it = m_ActivityActions.begin(); it != m_ActivityActions.end(); ++it )
	{
		if ( it->m_nType == ACTIVITY_START )
			LOG_NOTICE("default", "Sorted Activity %d start time:%d", it->m_nID, it->m_nTime );
		else
			LOG_NOTICE("default", "Sorted Activity %d end time:%d", it->m_nID, it->m_nTime );
	}
}

// �ж�ʱ���Ƿ�ʼ�� ��ʱ�˷���true ʱ���ʽ��HHMM
bool CServiceActivity::IsPassed( int nTime )
{
	time_t t = time( 0 );
	tm tmp;
	localtime_r( &t, &tmp);

	int tHour = nTime/100;
	int tMini = nTime%100;

	if ( tmp.tm_hour > tHour ) // Сʱ������
	{
		return true;
	}
	else if ( tmp.tm_hour == tHour ) // Сʱ���
	{
		if ( tmp.tm_min >= tMini ) // ���ӳ�����
		{
			return true;
		}
	}
	return false;
}

// �ж��ǲ��ǽ���
bool CServiceActivity::IsToday( int nDate )
{
	time_t t = time( 0 );
	tm tmp;
	localtime_r( &t, &tmp);

	int tYear  = nDate/10000;
	int tMonth = (nDate%10000)/100;
	int tDay   = nDate%100;

	return (tYear==tmp.tm_year+1900)&&(tMonth==tmp.tm_mon+1)&&(tDay==tmp.tm_mday);
}

// ����������ʼ�˾�֪ͨ����������
// ����������ʱ��
void CServiceActivity::CheckActivitys(bool bStart)
{
	if ( m_nNextActivityIndex >= (int)m_ActivityActions.size() ) 
	{ // ����Ļ�����
		return;
	}
	CMessageActivityChangeNotify msg;
	CMessage tMessage;
	pbmsg_sethead(&tMessage, ID_G2S_ACTIVITY_CHANGE_NOTIFY, 0, 0, 0, 0, 0, 0);
	tMessage.set_msgpara((uint32_t) &msg);

	int tStartIndex = m_nNextActivityIndex;
	for ( SCENE_ACTIVITYTYPE::iterator it = m_ActivityActions.begin()+tStartIndex;
		it != m_ActivityActions.end(); ++it )
	{
		if ( IsPassed( it->m_nTime ) )
		{
			// ʱ�䵽�� ����ʱ�����
			SingleActivity* tpSingle = msg.add_activitylist();
			OnActivityStateChanged( it->m_nID, it->m_nType, it->m_nTime, tpSingle );
			++m_nNextActivityIndex;
		}
		else
		{
			break;
		}
	}

	if ( msg.activitylist_size() <= 0 )
		return;

	if (!bStart)
	{
		// ����������
		for ( int i = 1; i <= CGateServer::GetSingleton().GetMaxSceneServerID(); ++i)
		{
			CSceneServer *pScene =  CGateServer::GetSingleton().GetServerByID(i);
			if ( pScene )
			{	
				LOG_NOTICE("default", "notify scene%d activity changed", i );
				CGateServer::GetSingleton().Send2Scene( pScene, &tMessage);
			}
		}
	}
}

// �״̬�ı�Ĵ���
void CServiceActivity::OnActivityStateChanged( int nActivityID, int nTymeType, int nTime, SingleActivity* pMsg )
{
	int nNewState = 0; // ��״̬
    
	if ( nTymeType == ACTIVITY_START ) // ���ʼ
	{
		nNewState = ACTIVITYSTATE_STARTED;
		ACTIVITY_STATE_TYPE::iterator it = m_ActivityStates.find( nActivityID );
		if ( it == m_ActivityStates.end() )
		{
			m_ActivityStates.insert( std::pair<int, int>(nActivityID, nNewState) );

            // ����ҡǮ���
            if ( CActivityYQS::GetSingleton().IsYaoQianShu( nActivityID ) )
            {
                std::string lstrTime = CActivityYQS::GetSingleton().ConverTime( nTime );
                CActivityYQS::GetSingleton().StartActivity( lstrTime );
            }
            
		}
		else
		{
			it->second = nNewState;
		}
	}
	else if ( nTymeType == ACTIVITY_END ) // �����
	{
		nNewState = ACTIVITYSTATE_NOT_START;
		m_ActivityStates.erase( nActivityID );

        // ����ҡǮ���
        if ( CActivityYQS::GetSingleton().IsYaoQianShu( nActivityID ) )
        {
            std::string lstrTime = CActivityYQS::GetSingleton().ConverTime( nTime );
            CActivityYQS::GetSingleton().EndActivity( lstrTime );
        }
        
	}
    
	LOG_NOTICE("default", "nActivityID=%d new state=%d", nActivityID, nNewState );
	// ֪ͨ����
	OnFillSceneActivityChgMsg(nActivityID, nNewState, pMsg);
}

// ��䳡����仯֪ͨ��Ϣ
void CServiceActivity::OnFillSceneActivityChgMsg(int nActivityID, int nNewState, SingleActivity* pMsg)
{
	if ( pMsg != NULL )
	{
		pMsg->set_activityid( nActivityID );
		pMsg->set_activitystate( nNewState );
		// ����ͼ��������
		ACTIVITY_INFO_TYPE::iterator it = m_ActivityInfo.find(nActivityID);
		if (it != m_ActivityInfo.end())
		{
			for ( lk::vector<CSingleActivityInfo::MapDropInfo, ACTIVITY_MAPDROP_SIZE>::iterator it2 = it->second.mMapDropInfo.begin();
				it2 != it->second.mMapDropInfo.end(); ++it2 )
			{
				MapDrop* tpDrop = pMsg->add_mapdrops();
				LK_ASSERT( tpDrop!=NULL, continue );
				tpDrop->set_dropid(it2->mDropID);
				tpDrop->set_droptype(it2->mDropType);
				// �ֽ��ַ���
				char* pTmp = it2->mMaps;
				char* pTmp2 = pTmp;
				while( *pTmp != '\0' )
				{
					if ( *pTmp == ',' )
					{
						char tmp[10]={0};
						strncpy(tmp, pTmp2, std::min(9,pTmp-pTmp2));
						tpDrop->add_mapids(::atoi(tmp));
						pTmp2=pTmp+1;
					}
					++pTmp;
				}
				tpDrop->add_mapids(::atoi(pTmp2));
			}
		}
	}
}

// ֪ͨ���������� �����б�
// �ڳ���������ע����Ϻ������
void CServiceActivity::SendTodayList2Scene( int nServerID, bool bStart )
{
	CMessageTodayActivitysNotify msg;

	CMessage tMessage;
	pbmsg_sethead(&tMessage, ID_G2S_TODAYACTIVITYS_LIST_NOTIFY, 0, 0, 0, 0, 0, 0);
	tMessage.set_msgpara((uint32_t) &msg);

	for ( SCENE_ACTIVITYTYPE::iterator it = m_ActivityActions.begin();
		it != m_ActivityActions.end(); ++it )
	{
		SingleActivityObj* tpSingle = msg.add_activitylist();
		LK_ASSERT( tpSingle != NULL, continue );
		tpSingle->set_activityid( it->m_nID );
		tpSingle->set_lmtlevel( it->m_nLmtLevel );
		tpSingle->set_maxtimes( it->m_nMaxTimes );
		tpSingle->set_timeinfo( it->m_nTime );
		tpSingle->set_timetype( it->m_nType );
		tpSingle->set_state( GetCurState(it->m_nID) );
	}

	// ����ۺϾ�̬����
	for ( ACTIVITY_INFO_TYPE::iterator it = m_ActivityInfo.begin();
		it != m_ActivityInfo.end(); ++it )
	{
		SingleActivityInfo* tpSingle = msg.add_activityinfo();
		LK_ASSERT( tpSingle != NULL, continue );
		tpSingle->set_activityid( it->first );
		for ( lk::vector<CSingleActivityInfo::DropInfo, ACTIVITY_DROP_SZ>::iterator it2 = it->second.mDropInfo.begin();
			it2 != it->second.mDropInfo.end(); ++it2 )
		{
			DropInfo* tpDrop = tpSingle->add_dropinfo();
			LK_ASSERT( tpDrop!=NULL, continue );
			tpDrop->set_ogreid(it2->mOgreID);
			tpDrop->set_dropid(it2->mDropID);
		}
		for ( lk::vector<int, ACTIVITY_OGREINDEX_SZ>::iterator it3 = it->second.mOgreIndex.begin();
			it3 != it->second.mOgreIndex.end(); ++it3 )
		{
			tpSingle->add_ogreindex(*it3);
		}
	}

	LOG_NOTICE("default", "notify scene%d activity", nServerID );
	CGateServer::GetSingleton().Send2Scene( nServerID, &tMessage);

	// ����Ƿ����������� ��Ҫ���״̬�ı���Ϣ
	if (bStart)
	{
		CMessageActivityChangeNotify msg2;
		CMessage tMessage2;
		pbmsg_sethead(&tMessage2, ID_G2S_ACTIVITY_CHANGE_NOTIFY, 0, 0, 0, 0, 0, 0);
		tMessage2.set_msgpara((uint32_t) &msg2);

		for( ACTIVITY_STATE_TYPE::iterator it = m_ActivityStates.begin(); it != m_ActivityStates.end(); ++it)
		{
			if (it->second == ACTIVITYSTATE_STARTED)
			{
				SingleActivity* tpSingle = msg2.add_activitylist();
				OnFillSceneActivityChgMsg( it->first, ACTIVITYSTATE_STARTED, tpSingle);
			}
		}
		CGateServer::GetSingleton().Send2Scene( nServerID, &tMessage2);
	}
}

// ��û״̬
int CServiceActivity::GetCurState( int nID )
{
	ACTIVITY_STATE_TYPE::iterator it = m_ActivityStates.find( nID );
	if ( it == m_ActivityStates.end() ) // û�ҵ�
		return ACTIVITYSTATE_NOT_START;
	return it->second;
}

bool operator < ( const CSingleSceneActivityObj& rLeft, const CSingleSceneActivityObj& rRight )
{
	return rLeft.m_nTime < rRight.m_nTime;
}

// ��һ�쵽��
void CServiceActivity::OnNewDayCome() 
{
	/*LoadSceneAvtivitys("../config/data/activity/induct_server.xml");*/
	LoadSceneAvtivitys(CGateLogic::GetSingletonPtr()->GetConfigDataFileNamePath(CGateLogic::GetSingleton().mConfig.nGameID,"activity/induct_server.xml"));
	// ���߳�����������б�
	for ( int i = 1; i <= CGateServer::GetSingleton().GetMaxSceneServerID(); ++i)
	{
		SendTodayList2Scene( i );
	}
	CheckActivitys();
}

// ��һ�ܵ���
void CServiceActivity::OnNewWeekCome()
{
}

// ���������ͻ
void CServiceActivity::SendActivityEvent2Scene( int nSvrID, CMessageActivityEventNotify* pMsg )
{
	LOG_ERROR("default", "#ACT Send ACTIVITY_EVENT_NOTIFY to %d", nSvrID);
	CMessage tMessage;
	pbmsg_sethead(&tMessage, ID_G2S_ACTIVITY_EVENT_NOTIFY, 0, 0, 0, 0, 0, 0);
	tMessage.set_msgpara((uint32_t) pMsg);

	CGateServer::GetSingleton().Send2Scene( nSvrID, &tMessage);
}

void CServiceActivity::LoadActivityXmlCallback(const char* pcConfigPath)
{
	if (pcConfigPath == NULL)
	{
		return;
	}

	if (CServiceActivity::GetSingleton().m_pActivityItems == NULL)
	{
		return;
	}

	// ������������
	CServiceActivity::GetSingleton().m_Activities.clear();

	//��ն���
	std::list<int> lstDelObjs;
	ACTIVITYITEMSTYPE::iterator iter = CServiceActivity::GetSingleton().m_pActivityItems->begin();
	for ( ; iter != CServiceActivity::GetSingleton().m_pActivityItems->end(); ++iter)
	{
		lstDelObjs.push_back(iter->second);	
	}

	std::list< int >::iterator iter2 = lstDelObjs.begin();
	for(; iter2 != lstDelObjs.end(); ++iter2)
	{
		CGateObjManager::GetSingletonPtr( )->DestroyObject(*iter2);
	}

	// �������
	CServiceActivity::GetSingleton().m_pActivityItems->clear();

	CServiceActivity::GetSingleton().LoadActivityFromXml(pcConfigPath);
}

void CServiceActivity::LoadInductXmlCallback(const char* pcConfigPath)
{
	if (pcConfigPath == NULL)
	{
		return;
	}

	CServiceActivity::GetSingleton().LoadSceneAvtivitys(pcConfigPath);
	// ���߳�����������б�
	for ( int i = 1; i <= CGateServer::GetSingleton().GetMaxSceneServerID(); ++i)
	{
		CServiceActivity::GetSingleton().SendTodayList2Scene( i );
	}
	CServiceActivity::GetSingleton().CheckActivitys();
}