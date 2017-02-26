#ifndef _BASE_LOG_
#define _BASE_LOG_

#include "base.h"
#include "log.h"
#include "lk_assert.h"
#include "servertool.h"
#include "logservertype.h"

#define SQL_HOST_INFO_STRING	128		// ���ݿ�������Ϣ

#define SAVE_DATA_CIRCLE		60		// ��¼�¼�����(��)

#define MAX_NAME_LENGTH			32		// ������󳤶�

struct stPlayerBaseInfo
{
	int m_nMapID;							// ������ڵ�ͼID
	int m_nLineID;							// ���������ID
	int m_nCharID;							// ��ҵ�CHARID
	int m_nMetier;							// ���ְҵ
	int m_nLevel;							// ��ҵȼ�
	char m_cCharName[MAX_NAME_LENGTH];		// �������

	stPlayerBaseInfo()
	{
		m_nMapID	= 0;
		m_nLineID	= 0;
		m_nCharID	= 0;
		m_nMetier	= 0;
		m_nLevel	= 0;
		memset( m_cCharName, 0, sizeof(m_cCharName) );
	}

	void PushInfo( int nMapID, int nlineID, int nCharID, int nMetier, int nLevel, const char *cCharName, int nLength )
	{
		m_nMapID	= nMapID;
		m_nLineID	= nlineID;
		m_nCharID	= nCharID;
		m_nMetier	= nMetier;
		m_nLevel	= nLevel;
		strncpy( m_cCharName, cCharName, nLength );
	}

	void PushInfo( stPlayerBaseInfo& stPBI )
	{
		m_nMapID	= stPBI.m_nMapID;
		m_nLineID	= stPBI.m_nLineID;
		m_nCharID	= stPBI.m_nCharID;
		m_nMetier	= stPBI.m_nMetier;
		m_nLevel	= stPBI.m_nLevel;
		strncpy( m_cCharName, stPBI.m_cCharName, strlen(stPBI.m_cCharName) + 1 );
	}

	int GetMapID( ) { return m_nMapID; }
	void SetMapID( int nMapID ) { m_nMapID = nMapID; }
	int GetLineID( ) { return m_nLineID; }
	void SetLineID( int nLineID ) { m_nLineID = nLineID; }
	int GetCharID( ) { return m_nCharID; }
	void SetCharID( int nCharID ) { m_nCharID = nCharID; }
	int GetMetier( ) { return m_nMetier; }
	void SetMetier( int nMetier ) { m_nMetier = nMetier; }
	int GetLevel( ) { return m_nLevel; }
	void SetLevel( int nLevel ) { m_nLevel = nLevel; }
	const char* GetCharName( ) { return m_cCharName; }
	void SetCharName( const char* cCharName, int nLength ) { memcpy( m_cCharName, cCharName, nLength ); }
};

#endif // _BASE_LOG_

