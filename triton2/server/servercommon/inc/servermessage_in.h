#ifndef _SERVERMESSAGE_IN_
#define _SERVERMESSAGE_IN_

#include "base.h" 
#include "message_factory.h" 
#include "message_pb.hxx.pb.h" 
#include "proxymessage_pb.hxx.pb.h"
#include "log.h"
#include "lk_assert.h"

void pbmsg_delmsg(CMessage* pMessage);

void pbmsg_sethead(CMessage* tMessage, unsigned int nMsgID, unsigned int nMsgSeq, unsigned int nMsgType,
		unsigned int nSrcFE, unsigned int nDstFE, unsigned int nSrcID, unsigned int nDstID);

void pbmsg_setproxy(CProxyHead* pProxy, unsigned int nSrcFE, unsigned int nDstFE, unsigned int nSrcID, 
		unsigned int nDstID, EMTransType emTransTp = TRANS_P2P, EMProxyCmd emProxyCmd = CMD_NULL, 
		unsigned char* szOption = NULL, unsigned int nOptlen = 0);

int pbmsg_getheadmsg(unsigned char* szBuffer, unsigned int unBufferLength, CProxyHead* pHeader, CMessage* tpMessage);

int pbmsg_getheadpb(char* szBuffer, unsigned int unBufferLength, 
		CProxyHead* pHeader, CMessage* tpMessage, char* szProtoBuf, unsigned short *punProtoBufLen);


template <class T>
int pbmsg_setmsg(T& tHeader, CMessage& tMessage, char* szBuffer, unsigned short unBufferSize)
{
	// ����������ǿת
	Message* pPara = (Message *) (tMessage.msgpara());

	if (pPara == NULL)
	{
		LOG_ERROR( "default", "The Message Para is NULL" );
		return 0;
	}

	// ����������Ϣ���ĳ���
	int iPkgSize =  tHeader.ByteSize() + tMessage.ByteSize() + pPara->ByteSize() + 2*4;

	if (iPkgSize > 0xffff || iPkgSize < 0)
	{
		LOG_ERROR("default", " The Message(%d) PackSize(%d) more than 0xFFFF, Pls check it",tMessage.msghead().messageid(), iPkgSize);
		return 0;
	}

	// ���Ե�unBufferSize�ĳ���һ�����������������Ϣ���ĳ���, ������ǳ����������
	if (unBufferSize < iPkgSize) 
		return (unBufferSize - iPkgSize); 

	// Ϊ������Ϣ�ĳ��ȸ�ֵ
	char * tpBuffer = szBuffer;
	*((unsigned short*)tpBuffer) = iPkgSize;
	tpBuffer += 2; 

	// ��¼ת����Ϣͷ�ĳ���
	*((unsigned short*)tpBuffer) = tHeader.GetCachedSize();
	tpBuffer += 2;

	// ��ת����Ϣͷѹ��szBuffer�У�
	// ֮ǰ�Ѿ���������� һ����unBufferSize֮���ˣ��������ʹ���������Ӧ���ǰ�ȫ��
	bool ret = tHeader.SerializeToArray(tpBuffer, unBufferSize);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] pHeader->SerializeToArray error",
				__LK_FILE__, __LINE__, __FUNCTION__ );
		return 0;
	} 
	
	tpBuffer += tHeader.GetCachedSize();


	// ��¼��Ϣͷ�ĳ���
	*((unsigned short*)tpBuffer) = tMessage.GetCachedSize();
	tpBuffer += 2;

	// ����Ϣͷѹ��������
	ret = tMessage.SerializeToArray(tpBuffer, unBufferSize);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] tMessage.SerializeToArray error",
				__LK_FILE__, __LINE__, __FUNCTION__ );
		return 0;
	}

	tpBuffer += tMessage.GetCachedSize();

	// ��¼��Ϣ������ĳ���
	*((unsigned short*)tpBuffer) = pPara->GetCachedSize();
	tpBuffer += 2;

	// ����Ϣ������ѹ��������
	ret = pPara->SerializeToArray(tpBuffer, unBufferSize);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] pPara->SerializeToArray error",
				__LK_FILE__, __LINE__, __FUNCTION__ );

		return 0;
	}

	tpBuffer += pPara->GetCachedSize();

	// �˴�����һ��  iPkgSize == tpBuffer - sBuffer;
	assert(iPkgSize == (tpBuffer - szBuffer));

	return iPkgSize;
}

// ����Ϣ������buffer��
int CodeMsgToBuffer( char *pBuffer, int nBufferLength, CMessage &tMsg );

// ��buffer�н�����Ϣ
int DecodeMsgFromBufer( char *pBuffer, int nBufferLength, CMessage &tMsg );

#endif

