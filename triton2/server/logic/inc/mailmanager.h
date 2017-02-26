#pragma once

#include "sceneobj_manager.h"
#include "entity.h"
#include "lk_hashmap.h"

// ********************************************************************** //
// CMailManager
// ********************************************************************** //
class CSysMailInfo
{
public:
	int	 mSysMailID;
	char mMailTitle[MAIL_TITLE_LEN];
	char mMailBody[MAIL_BODY_LEN];
	char mName[NAME_LENGTH];
public:
	CSysMailInfo()
	{
		if ( CObj::msCreateMode )
		{
			Initialize();
		}
		else
		{
			Resume();
		}
	}
	
	int Initialize()
	{
		mSysMailID = 0;
		memset( mMailTitle, 0, sizeof( mMailTitle ) );
		memset( mMailBody, 0, sizeof( mMailBody ) );
		memset( mName, 0, sizeof( mName ) );
		return 0;
	}
	
	int Resume()
	{
		return 0;
	}	
};
class CMailManager : public CSingleton< CMailManager >
{
public:	
	void* operator new( size_t size );                   
	void  operator delete( void* pointer );

	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* pointer, const char* file, int line);

	static CSharedMem* mShmPtr;					 // �����ڴ�ָ��
public:
  static	unsigned int CountSize(); 
	typedef lk::hash_map< int, CSysMailInfo, MAX_SYSMAILTYPE_NUM >	SysMail;
	SysMail mSysMailList;
public:
	CMailManager( )
	{
		if ( CObj::msCreateMode )
		{
			Initialize();
		}
		else
		{
			Resume();
		}
	}
	~CMailManager( );	
	

	//�õ��ʼ�
	CMail* GetMail( CEntityPlayer *pPlayer );			
	//������
	CMail* AddMail( CEntityPlayer *pPlayer );									
	//ɾ�����
	void Erase( CEntityPlayer *pPlayer );  
	
	int Initialize();
	int Resume()
	{
		return 0;
	}

public:
	// ����һ��ϵͳ�ʼ�����Ϣ
	int InsertSysMail( int nMailID, CSysMailInfo &rMailInfo );
	
	// ɾ��һ��ϵͳ�ʼ�����Ϣ
	int DeleteSysMail( int nMailID );
	
	// ��ȡһ��ϵͳ�ʼ�����Ϣ
	CSysMailInfo *GetSysMail( int nMailID );
};

