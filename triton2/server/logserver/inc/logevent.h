#ifndef _LOGEVENG_H_
#define _LOGEVENG_H_

#include "lk_string.h"
#include "message_factory.h"

#include "google/protobuf/message.h"
#include "google/protobuf/descriptor.h"

typedef ::google::protobuf::Descriptor Descriptor;
typedef ::google::protobuf::Reflection Reflection;
typedef ::google::protobuf::FieldDescriptor FieldDescriptor;

enum EMAppendResult
{
	em_append_ok,
	em_append_fail,
	em_append_full,
};

typedef lk::string<0x7FFF> CMaxString;

class CMessage;

// logͳ����Ϣ
struct CLogStat
{
	unsigned int m_uiMsgID;	// ��ϢID
	unsigned int m_uiRecvNum; // ������Ϣ��
	unsigned int m_uiInsertNum; //���뵽���ݿ��е�����
	struct timeval m_tSyncInsertTime; //ͬ��insertִ��ʱ��

	const CLogStat&  operator +( const CLogStat& rLogStat )
	{
		m_uiRecvNum += rLogStat.m_uiRecvNum;
		m_uiInsertNum += rLogStat.m_uiInsertNum;
		m_tSyncInsertTime.tv_sec += rLogStat.m_tSyncInsertTime.tv_sec;
		m_tSyncInsertTime.tv_usec += rLogStat.m_tSyncInsertTime.tv_usec;
		return *this;
	}
};

class CLogEvent
{
  private:
	CMaxString *m_pInsBuf;
	char m_szTableName[32+1];
	int m_nSplit;

	CLogStat mLogStat; // ͳ����Ϣ

  public:

	CLogEvent(const char* szTableName, const int nSplit);
	~CLogEvent();

	EMAppendResult AppendMessage(int nIndex, CMessage* pMessage);
	EMAppendResult AppendDropItemMessage( int nIndex, CMessage * pMessage);
	EMAppendResult AppendStatInfoMessage( int nIndex, CMessage * pMessage);
	EMAppendResult AppendItemGhostMessage( int nIndex, CMessage * pMessage);

	const char* GetSql(int nIndex);
	void ClearSql(int nIndex);
	size_t size() { return m_nSplit; }

	void ClearStatInfo( ) { memset( &mLogStat, 0, sizeof(mLogStat) ); }
	CLogStat& GetLogStat( ) { return mLogStat; }

  private:
	void PrintRecord(const Message& message, CMaxString& generator);
	void PrintField(const Message& message, const Reflection* reflection, const FieldDescriptor* field, CMaxString& generator);
};


#endif
