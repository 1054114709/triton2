#include "stdafx.hpp"
#include "westserver.h"	  
#include "familymodule.h"
#include "familymessage_pb.hxx.pb.h"
#include "message_pb.hxx.pb.h"
#include "familydbinfo_pb.hxx.pb.h"
#include "entity.h"
#include "scenecfg_manager.h"
#include "protype.h"
#include "scenelogic.h"
#include "propertymodule.h"
#include "mapobjmanager.h"
#include "activitymodule.h"
#include "corpsmodule.h"
#include "logmodule.h"
#ifdef LEAK_CHK_DEBUG_NEW
#include "debug_new.h"
#endif


// ***********************************************************
//  Function:		InsertMember
//  Description:	�������Ա���볡��ʱ,�����б�
//  Output:			
//  Date:			09/03/2009
// **********************************************************
int CFamilyInfo::InsertMember( int nRoleID, CMemberInfo &rMemberInfo )
{  
	if ( mMemberList.size() >= MAX_FAMILYMEMBER_NUM )
	{ 		
		return -1;
	}
	FamilyMemberList::iterator it = mMemberList.find( nRoleID );
	if ( it != mMemberList.end() )
	{			
		mMemberList.erase( it );
	}
	mMemberList.insert( FamilyMemberList::value_type( nRoleID, rMemberInfo ) );
	return	SUCCESS;
}

// ***********************************************************
//  Function:		Initialize
//  Description:	��ʼ����������Ϣ
//  Output:			
//  Date:			09/03/2009
// **********************************************************
int CFamilyInfo::Initialize()
{  
	mMemberList.initailize();
	mCorpsID = 0;
	memset( mFamilyName, 0, sizeof( mFamilyName ) );
	memset( mCorpsName, 0, sizeof( mCorpsName ) );
	return SUCCESS;
}

// ***********************************************************
//  Function:		DeleteMember
//  Description:	�������ʱɾ�������Ϣ,�����б�
//  Output:			
//  Date:			09/03/2009
// **********************************************************
int CFamilyInfo::DeleteMember( int nRoleID )
{  
	FamilyMemberList::iterator it = mMemberList.find( nRoleID );
	if ( it != mMemberList.end() )
	{
		mMemberList.erase( it );
	}
	return SUCCESS;
}


// ***********************************************************
//  Function:		HasMember
//  Description:	�жϳ�Ա�б����Ƿ���ĳ�����,�����б�
//  Output:			
//  Date:			09/03/2009
// **********************************************************
bool CFamilyInfo::HasMember( int nRoleID )
{
	if ( mMemberList.find( nRoleID ) != mMemberList.end() )
	{
		return true;
	}
	return false;
}

// ***********************************************************
//  Function:		ChangeMemberInfo
//  Description:	�ı��Ա����Ϣ,�����б�
//  Output:			
//  Date:			09/03/2009
// **********************************************************
int CFamilyInfo::ChangeMemberInfo( int nRoleID, CMemberInfo &rMemberInfo )
{
	FamilyMemberList::iterator it = mMemberList.find( nRoleID );
	if ( it != mMemberList.end() )
	{
		it->second = rMemberInfo; 
	}
	return SUCCESS;
}

// ��ȡ��Ա��Ϣ
CMemberInfo *CFamilyInfo::GetMemberInfo( int nRoleID )
{
	FamilyMemberList::iterator it = mMemberList.find( nRoleID );
	if ( it != mMemberList.end() )
	{
		return &it->second; 
	}
	return NULL;
}

// ***********************************************************
//  Function:		GetMemberList
//  Description:	��ȡ�����������б�,�����б�
//  Output:			
//  Date:			09/03/2009
// **********************************************************
int CFamilyInfo::GetMemberList( int *pIDList, int &rNum )
{
	LK_ASSERT( pIDList != NULL, return -1 )
		int tNum = rNum;
	rNum = 0;
	FamilyMemberList::iterator it = mMemberList.begin();
	for( ; it != mMemberList.end() && rNum < tNum ; ++it )
	{	
		pIDList[rNum] = (it->second).mEntityID;
		++rNum;
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		SetFamilyName
//  Description:	���ü�������
//  Output:			
//  Date:			12/01/2009
// **********************************************************
void CFamilyInfo::SetFamilyName( const char *pName, bool bRefresh /* = false */ )
{	
	if ( pName == NULL )
	{					
		return;
	}

	if ( mFamilyName[0] != '\0' && bRefresh == false )
	{
		return;
	}

	strncpy( mFamilyName, pName, sizeof( mFamilyName ) - 1 );			
}

// ***********************************************************
//  Function:		SetCorpsName
//  Description:	���þ�������
//  Output:			
//  Date:			12/01/2009
// **********************************************************
void CFamilyInfo::SetCorpsName( const char *pName, bool bRefresh /* = false */ )
{
	if ( pName == NULL )
	{					
		return;
	}

	if ( mCorpsName[0] != '\0' && bRefresh == false )
	{
		return;
	}

	strncpy( mCorpsName, pName, sizeof( mCorpsName ) - 1 );	
}

// �ַ���������ʾ
const char *CFamilyInfo::GetFamilyNameShow()
{
#ifdef CHARSET_SHOW_GBK
	static char tFamilyName[ MAX_FAMILYNAME_LENGTH ] = {0};
	int nNameLen = sizeof(tFamilyName)-1;
	charset_convert( "utf8", "gbk", (char*)mFamilyName, strlen( mFamilyName ),
		tFamilyName, (size_t*)&nNameLen );
	return tFamilyName;
#else
	return mFamilyName;
#endif	
}


const char *CFamilyInfo::GetCorpsNameShow()
{
	// �ַ���������ʾ
#ifdef CHARSET_SHOW_GBK
	static char tCorpsName[ MAX_CORPSNAME_LENGTH ] = {0};
	int nNameLen = sizeof(tCorpsName)-1;
	charset_convert( "utf8", "gbk", (char*)mCorpsName, strlen( mCorpsName ),
		tCorpsName, (size_t*)&nNameLen );
	return tCorpsName;
#else
	return mCorpsName;
#endif	
}
