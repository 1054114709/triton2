#include "servermessage_in.h"
#include "message_factory.h" 
#include "message_pb.hxx.pb.h"
#include "proxymessage_pb.hxx.pb.h" 
#include "client_comm_engine.h"

// ���Cmessage �� msgpara() ռ�õ��ڴ�ռ�
void pbmsg_delmsg(CMessage* pMessage)
{
	if(pMessage->msgpara())
	{
#ifdef _USE_MESSAGE_BUFF_ // ���ʹ����placement new, ֻ������ɾ��
		Message* pMessagePara = (Message*)(pMessage->msgpara());
		pMessagePara->~Message();
#else
		delete (Message*)(pMessage->msgpara());
#endif
		pMessage->set_msgpara(0);

	}
}

void pbmsg_setproxy(CProxyHead* pProxy, unsigned int nSrcFE, unsigned int nDstFE, unsigned int nSrcID, 
		unsigned int nDstID, EMTransType emTransTp, EMProxyCmd emProxyCmd, unsigned char* szOption, unsigned int nOptlen)
{
	if (nSrcFE) pProxy->set_srcfe( nSrcFE );
	if (nDstFE) pProxy->set_dstfe( nDstFE );
	if (nSrcID) pProxy->set_srcid( nSrcID );
	if (nDstID) pProxy->set_dstid( nDstID );

	pProxy->set_transfertype(emTransTp);
	pProxy->set_opflag(emProxyCmd);

	if (szOption && nOptlen)
	{
		pProxy->set_optlength(nOptlen);
		pProxy->set_option(szOption, nOptlen);
	}
}

/*
 * ���ܣ� Ϊ����Ϣͷ�ĸ���д�ĺ���
 *
 */
void pbmsg_sethead(CMessage* tMessage, unsigned int nMsgID, unsigned int nMsgSeq, unsigned int nMsgType,
		unsigned int nSrcFE, unsigned int nDstFE, unsigned int nSrcID, unsigned int nDstID)
{
	CMessageHead* tpHead = tMessage->mutable_msghead();

	tpHead->set_messageid( nMsgID );
	//if (nMsgType) tpHead->set_msgtype( nMsgType );
	if (nMsgSeq) tpHead->set_msgseq( nMsgSeq );
	if (nSrcFE) tpHead->set_srcfe( nSrcFE );
	if (nDstFE) tpHead->set_dstfe( nDstFE );
	if (nSrcID) tpHead->set_srcid( nSrcID );
	if (nDstID) tpHead->set_dstid( nDstID );
}

/*
 *
 *  �γ���Ϣ��: ���룺ת����Ϣͷ, ��Ϣͷ, ��Ϣ����, �γ���Ϣ������󳤶� �������, �Լ����ĳ���
 *
 *  net_message struct:
 *
 *  total_lenth + head_length + head_content + message_length + message_content + para_length + para_content
 *  2 bytes           2 bytes     m  bytes        2 bytes            n bytes        2 bytes        x bytes
 *
 *  total_length = lenght of (net_message)
 *  head_length = length of (head_content) 
 *  message_length = length of (message_content) 
 *  para_length = length of (para_content)
 *
 *  messaget_content = message_head + [point to para_object (4 bytes)]
 *  message_head = msg_id + optional some fields
 *
 *  ����: ��tHeader, tMessage �γ���Ϣ���� unBufferSize ��С�� szBuffer ��
 *  
 *  ����:
 *
 *  T:  �ͻ��˷������� CCSHead, ������֮���� CProxyHead
 *  tMessage: ��Ҫѹ��ȥ��Message
 *  szBuffer: �γɵ��ֽ���
 *  unBufferSize: szBuffer �Ĵ�С�� ע�ⲻ�����ɵ����ĳ���
 *
 *  ����ֵ:
 *
 * 	== 0 : ʧ��, protobuf �ڲ����ʧ��
 * 	>  0 : ���ɵ����ĳ���
 * 	<  0 : szBuffer ��������ֽڵĲ��ܺϳɰ�
 * 
 */

/*
template <class T>
int pbmsg_setmsg(T& tHeader, CMessage& tMessage, char* szBuffer, unsigned short unBufferSize)
{
	// ����������ǿת
	Message* pPara = (Message *) (tMessage.msgpara());

	// ����������Ϣ���ĳ���
	int iPkgSize =  tHeader.ByteSize() + tMessage.ByteSize() + pPara->ByteSize() + 2*4;

#ifdef LK_DEBUG
	printf("==========================Set==========================");
#endif

	// ���Ե�unBufferSize�ĳ���һ�����������������Ϣ���ĳ���, ������ǳ����������
	if (unBufferSize < iPkgSize) return (unBufferSize - iPkgSize); 

	// ת�����м�¼��������Ϣ�ĳ���, ע��tHeader�����totallength������fix32
	//tHeader.set_totallength( iPkgSize );


	// Ϊ������Ϣ�ĳ��ȸ�ֵ
	char * tpBuffer = szBuffer;
	*((unsigned short*)tpBuffer) = iPkgSize;
	tpBuffer += 2; 

	// ��¼ת����Ϣͷ�ĳ���
	*((unsigned short*)tpBuffer) = tHeader.ByteSize();
	tpBuffer += 2;

	// ��ת����Ϣͷѹ��szBuffer�У�
	// ֮ǰ�Ѿ���������� һ����unBufferSize֮���ˣ��������ʹ���������Ӧ���ǰ�ȫ��
	bool ret = tHeader.SerializeToArray(tpBuffer, unBufferSize);
	if( ret != true )
	{
#ifdef LK_DEBUG
		printf("error at line(%d), tHeader.SerializeToArray \n", __LINE__ );
#endif
		return 0;
	} else
	{	
		tpBuffer += tHeader.ByteSize();

#ifdef LK_DEBUG
		printf("Header Length (%d) context is {\n", tHeader.ByteSize());
		printf(tHeader.DebugString().c_str());
		printf("}\n");
#endif
	}

	// ��¼��Ϣͷ�ĳ���
	*((unsigned short*)tpBuffer) = tMessage.ByteSize();
	tpBuffer += 2;

	// ����Ϣͷѹ��������
	ret = tMessage.SerializeToArray(tpBuffer, unBufferSize);
	if( ret != true )
	{
#ifdef LK_DEBUG
		printf("error at line(%d), tMessage.SerializeToArray \n", __LINE__ );
#endif
		return 0;
	}else
	{

		tpBuffer += tMessage.ByteSize();
#ifdef LK_DEBUG
		printf("Message Length (%d) context is { \n", tMessage.ByteSize());
		printf("%s\n", tMessage.DebugString().c_str());
		printf("}\n");
#endif
	}

	// ��¼��Ϣ������ĳ���
	*((unsigned short*)tpBuffer) = pPara->ByteSize();
	tpBuffer += 2;

	// ����Ϣ������ѹ��������
	ret = pPara->SerializeToArray(tpBuffer, unBufferSize);
	if( ret != true )
	{
#ifdef LK_DEBUG
		printf("error at line(%d), pPara->SerializeToArray \n", __LINE__ );
#endif
		return 0;
	}else
	{
		tpBuffer += pPara->ByteSize();
#ifdef LK_DEBUG
		printf("Para Length (%d), context is { \n", pPara->ByteSize());
		printf("%s\n", pPara->DebugString().c_str());
		printf("}\n");

		printf("pkg size is %d\n", iPkgSize);
#endif
	}

	// �˴�����һ��  iPkgSize == tpBuffer - sBuffer;
	assert(iPkgSize == (tpBuffer - szBuffer));

	return iPkgSize;
}
*/

/*
 *  ����fd������ ���ȵ���ת��ΪCProxyHead, CMessage,  
 *  ���ص�CproxyHead* �Ǿֲ��ľ�̬�����ĵ�ַ, ����Ҫ�ⲿ�����ͷţ� ����ⲿ������Ҫ��ʱ�����븴�� 
 *
 *  ˵����
 *   	��ʹ����Ϣ���е�ʱ��ʹ�ã�ֱ�Ӵ����ж�ȡ�ֽ��������뷵��Header �� tpMessage; 
 *   	����tpMessage�е�msgpara()�Ƕ�̬���ɵ�, ��Ҫ���õĳ�������֮���ͷ�
 *
 *  ������
 *
 * 		szBuffer:		��socketfd�������
 * 		unBufferLength: ��socketfd �������ĳ��� 
 * 		pHeader:		�ӿͻ��˶��������дCCSHead, �����������дCPorxyHead
 * 		pMessage:		�������ȡ�õ�pMessage
 *
 * ����ֵ:
 *
 * 	== 0 : ʧ��, protobuf �ڲ����ʧ��
 * 	>  0 : �Ѿ�����ĳ���, �´��ٵ��ã���Ҫƫ��������ȵ�ָ��
 * 	<  0 : ��������ֽڵĲ��ܽ��
 *
 */
int pbmsg_getheadmsg(unsigned char* szBuffer, unsigned int unBufferLength, CProxyHead* pHeader, CMessage* tpMessage)
{
	unsigned char * tpBuffer = szBuffer;
	unsigned short iPkgSize = *((unsigned short*)(tpBuffer));


	// У�鴫�����ĳ���, ������Ȳ�������Ҫ���ؼ�����
	if (iPkgSize > (unBufferLength)) return (unBufferLength - iPkgSize);

	// �����������ĳ����ֶ�
	tpBuffer += 2;

	//ÿ�ε���֮ǰ����Ҫ����tHeader
	pHeader->Clear();

	unsigned short unHeadLength = *((unsigned short*)(tpBuffer));
	bool ret = pHeader->ParseFromArray( tpBuffer+2, unHeadLength);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] pHeader->ParseFromArray error", 
				__LK_FILE__, __LINE__, __FUNCTION__ );

		return 0;
	}
	else
	{
		//iPkgSize -= tHeader.ByteSize();
		tpBuffer += (2 + pHeader->ByteSize());

		//����ʹ�� tpBuffer = tpBuffer + (2 + unHeadLength);
	}
#ifdef _DEBUG_
	//LOG_DEBUG("default", "PRoxyHead:%s", pHeader->ShortDebugString().c_str());
#endif
	if ( pHeader->opflag() == CMD_KEEPALIVE )
	{
		tpMessage->set_msgpara(0);
		assert(iPkgSize == (tpBuffer - szBuffer));

		return iPkgSize;
	}

	// ����Ϣͷ
	unsigned short unMsgHeadLength = *((unsigned short*)(tpBuffer));

	ret = tpMessage->ParseFromArray( tpBuffer+2,  unMsgHeadLength);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] tpMessage->ParseFromArray error", 
				__LK_FILE__, __LINE__, __FUNCTION__ );

		return 0;
	}else
	{
		//iPkgSize -= tpMessage->ByteSize();
		//���� tpBuffer += (2 + unMsgHeadLength);
		tpBuffer += (2 + tpMessage->ByteSize());
	}


	unsigned short unMsgID =  tpMessage->msghead().messageid();
	// �ж�unMsgID����Ч��

	// ����Ϣ��
	Message* tpMsgPara = CMessageFactory::GetSingleton().CreateMessage(unMsgID);

	if (tpMsgPara  == NULL)
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] CMessageFactory::CreateMessage error", 
				__LK_FILE__, __LINE__, __FUNCTION__ );

		return 0;
	}

	unsigned short unMsgParaLength = *((unsigned short*)(tpBuffer));
	ret = tpMsgPara->ParseFromArray( tpBuffer+2, unMsgParaLength);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] tpMsgPara->ParseFromArray error", 
				__LK_FILE__, __LINE__, __FUNCTION__ );
#ifdef _USE_MESSAGE_BUFF_
		tpMsgPara->~Message();
#else
		delete tpMsgPara;
#endif

		return 0;
	}
	else
	{
		// ����Ϣ�帽������Ϣ��, ��Ϣͷ�����ڲ���̬������
		//iPkgSize -= tpMsgPara->ByteSize();
		//
		tpBuffer += (2 + tpMsgPara->ByteSize()); 
		tpMessage->set_msgpara((unsigned int) tpMsgPara);

	}

	// ����iPkgSize Ӧ�� ͬ������ֽ���һ��
	assert(iPkgSize == (tpBuffer - szBuffer));

	// ����ProxyHead 
	return iPkgSize;
}

/**
 *
 * ˵��: ������Ϣ���е�ʱ��׷����Ϣ�ĵ���, ��Ϣ�����д洢������
 *
 * ����: 
 *
 * szBuffer:		��socketfd�������
 * unBufferLength:  ��socketfd �������ĳ��� 
 * pHeader:			�ӿͻ��˶��������дCCSHead, �����������дCPorxyHead
 * pMessage:		�������ȡ�õ�pMessage->msghead(), ע��ֻ������pMessage->msghead, pMessage->msgpara = 0;
 * szProtoBuf:		δ�����pMessage->msgpara()
 * punProtoBufLen:	δ�����pMessage->msgpara()�ĳ��� 
 *
 *
 * ����:
 * == 0 : ʧ��, protobuf �ڲ����ʧ��
 * >  0 : �Ѿ�����ĳ���, �´��ٵ��ã���Ҫƫ��������ȵ�ָ��
 * <  0 : ��������ֽڵĲ��ܽ��
 *
 */

int pbmsg_getheadpb(char* szBuffer, unsigned int unBufferLength, 
		CProxyHead* pHeader, CMessage* tpMessage, char* szProtoBuf, unsigned short *punProtoBufLen)
{
	char * tpBuffer = szBuffer;
	unsigned short iPkgSize = *((unsigned short*)(tpBuffer));


	// У�鴫�����ĳ���, ������Ȳ�������Ҫ���ؼ�����
	if (iPkgSize > (unBufferLength)) return unBufferLength - iPkgSize;

	// �����������ĳ����ֶ�
	tpBuffer += 2;

	//ÿ�ε���֮ǰ����Ҫ����tHeader
	pHeader->Clear();

	unsigned short unHeadLength = *((unsigned short*)(tpBuffer));
	bool ret = pHeader->ParseFromArray( tpBuffer+2, unHeadLength);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] pHeader->ParseFromArray error", 
				__LK_FILE__, __LINE__, __FUNCTION__ );

		return 0;
	}
	else
	{
		//iPkgSize -= tHeader.ByteSize();
		tpBuffer += (2 + pHeader->ByteSize());

		//����ʹ�� tpBuffer = tpBuffer + (2 + unHeadLength);
	}

	if ( pHeader->has_opflag() && pHeader->opflag() == CMD_KEEPALIVE )
	{
		tpMessage->set_msgpara(0);
		assert(iPkgSize == (tpBuffer - szBuffer));

		return iPkgSize;
	}

	if (tpMessage != NULL)
	{
		// ����Ϣͷ
		unsigned short unMsgHeadLength = *((unsigned short*)(tpBuffer));

		ret = tpMessage->ParseFromArray( tpBuffer+2,  unMsgHeadLength);
		if( ret != true )
		{
			LOG_ERROR("default", "[ %s : %d ][ %s ] tpMessage->ParseFromArray error", 
				__LK_FILE__, __LINE__, __FUNCTION__ );

			return 0;
		}else
		{
			//iPkgSize -= tpMessage->ByteSize();
			//���� tpBuffer += (2 + unMsgHeadLength);
			tpBuffer += (2 + tpMessage->ByteSize());
		}

		if (szProtoBuf != NULL)
		{
			*punProtoBufLen= *((unsigned short*)(tpBuffer));

			// ����iPkgSize Ӧ�� ͬ������ֽ���һ��
			assert(iPkgSize == 2 + 2 + unHeadLength + 2 + unMsgHeadLength + 2 + (*punProtoBufLen));
			memcpy(szProtoBuf, tpBuffer + 2, *punProtoBufLen);
		}
	}

	// ����ProxyHead 
	return iPkgSize;
}

//  ����Ϣ������buffer��
int CodeMsgToBuffer( char *pCodeBuffer, int nCodeLength, CMessage &tMsg )
{ 
	char pBuffer[MAX_CODE_LEN];
	int	 nBufferLength = sizeof( pBuffer );
	LK_ASSERT( pBuffer != NULL && nBufferLength > 0, return -1 )

	// ���������ֽڼ�¼�ܳ���
	char *tpMsgBuffer = pBuffer+sizeof( unsigned short );
	int	  tBufferLen =	nBufferLength-sizeof( unsigned short );		
	
	// ������Ϣ
	*( unsigned short * )tpMsgBuffer = tMsg.ByteSize();
	tpMsgBuffer += sizeof( unsigned short );
	tBufferLen -= sizeof( unsigned short );

	int tRet = tMsg.SerializeToArray( tpMsgBuffer, tBufferLen );
	LK_ASSERT( tRet == true, return -1 )
	tpMsgBuffer += tMsg.ByteSize();
	tBufferLen -=   tMsg.ByteSize();


	// ���л� CMessagePara
	Message* tpMsgPara = (Message*)tMsg.msgpara();
	if( tpMsgPara == NULL )
	{
		return -1;
	}

	*((unsigned short*)tpMsgBuffer) = tpMsgPara->ByteSize();
	tpMsgBuffer += sizeof(unsigned short);	
	tBufferLen	-= sizeof(unsigned short);	  

	tRet = tpMsgPara->SerializeToArray( tpMsgBuffer, tBufferLen );
	if( tRet != true )
	{
		return -1;
	}
	tpMsgBuffer += tpMsgPara->ByteSize();	
	tBufferLen	-= tpMsgPara->ByteSize(); 
	
	int tTotalLen =	 nBufferLength - tBufferLen + 2;	
	*( unsigned short * )pBuffer = 	tTotalLen;
	
	// ����	 
	nCodeLength = MAX_CODE_LEN;
	ClientCommEngine::EncryptData( EnCryptType1, ClientCommEngine::tpKey, ( BYTE * )( pBuffer ), tTotalLen, ( BYTE * )( pCodeBuffer+2 ), &nCodeLength );
	*( unsigned short *)pCodeBuffer = nCodeLength+2;
	return nCodeLength+2;	
}

// ��buffer�н�����Ϣ
int DecodeMsgFromBufer( char *pCodeBuffer, int nCodeBufferLength, CMessage &tMsg )
{ 	
	unsigned short nCodeLength = *( ( unsigned short* )( pCodeBuffer ) );		
	LK_ASSERT( nCodeLength == nCodeBufferLength, return 0  )
	nCodeLength -= sizeof( unsigned short );
	
	// ����		
	char pBuffer[MAX_CODE_LEN];
	int	 nBufferLength = MAX_CODE_LEN;
	int tRet = ClientCommEngine::DecryptData( EnCryptType1, ClientCommEngine::tpKey, ( BYTE * )( pCodeBuffer+2 ), nCodeLength, ( BYTE * )pBuffer, &nBufferLength );			
	LK_ASSERT( tRet == 1, return 0 )
	
	// ������Ϣ
	unsigned char * tpBuffer = ( unsigned char * )pBuffer;
	LK_ASSERT( pBuffer != NULL && nBufferLength > 0, return -1 )
	tpBuffer += sizeof( unsigned short );

	//ÿ�ε���֮ǰ����Ҫ����tMsg
	tMsg.Clear();

	unsigned short unHeadLength = *((unsigned short*)(tpBuffer));
	bool ret = tMsg.ParseFromArray( tpBuffer+2, unHeadLength);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] pHeader->ParseFromArray error", 
			__LK_FILE__, __LINE__, __FUNCTION__ );

		return 0;
	}
	else
	{ 	
		tpBuffer += ( 2 + tMsg.ByteSize() ); 	
	}

	// ����Ϣͷ	 
	unsigned short unMsgID =  tMsg.msghead().messageid();	

	// ����Ϣ��
	Message* tpMsgPara = CMessageFactory::GetSingleton().CreateMessage( unMsgID );

	if (tpMsgPara  == NULL)
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] CMessageFactory::CreateMessage error", 
			__LK_FILE__, __LINE__, __FUNCTION__ );

		return 0;
	}

	unsigned short unMsgParaLength = *((unsigned short*)(tpBuffer));
	ret = tpMsgPara->ParseFromArray( tpBuffer+2, unMsgParaLength);
	if( ret != true )
	{
		LOG_ERROR("default", "[ %s : %d ][ %s ] tpMsgPara->ParseFromArray error", 
			__LK_FILE__, __LINE__, __FUNCTION__ );
#ifdef _USE_MESSAGE_BUFF_
		tpMsgPara->~Message();
#else
		delete tpMsgPara;
#endif

		return 0;
	}
	else
	{ 
		tpBuffer += (2 + tpMsgPara->ByteSize()); 
		tMsg.set_msgpara((unsigned int) tpMsgPara);	  
	}

	// ����iPkgSize Ӧ�� ͬ������ֽ���һ��
	//assert( nBufferLength == ( tpBuffer - pBuffer ) );

	// ����ProxyHead
	return nBufferLength;
}

