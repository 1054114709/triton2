#include "client_comm_engine.h"
#include "message_pb.hxx.pb.h"
#include "message_factory.h"
#include "oi_tea.h"
#include "network.h"

#ifdef LINUX
#include "lk_assert.h"
#else
#include <assert.h>
#define LK_ASSERT_STR(a,handle) assert(a)
#endif

namespace ClientCommEngine
{


// ***************************************************************
//  Function:		ConvertClientCodeToMsg2
//  Description:	�ͻ��˷�����ͨ�ã�ת�����ݰ�����Ϣ��ʽ���м�����л��ͽ���
//	Input:			
//	OutPut:			
//	Return:			
//	Others:			��������ж�Ҫ�����ϸ���Ϊ���ܻ��зǷ������ݰ���
//					Ҫ��֤�յ�ʲô���ݶ����ܱ���������release��ʱ������Ҫ-DNDEBUG��
//  Date:			02/05/2009
// 
// ***************************************************************
int ConvertClientCodeToMsg2( const void* pBuff, unsigned short usBuffLen, CCSHead* pCshead, CMessage* pMsg, const unsigned char* pEncrypt )
{
	if( (pBuff == NULL) || ( usBuffLen < sizeof(unsigned short)*4 ) || (pCshead == NULL) || (pMsg == NULL) )
	{
		return -1;
	}

	bool bParseRet = false;
	char* tpBuff = (char*)pBuff;
	int usTmpLen = 0;

	// �ܳ���
	int usTmpTotalLen = (int) *((unsigned short*)tpBuff);

	// ��֤�յ��İ��������ݰ��еİ����Ƿ�ƥ��
	if( usTmpTotalLen != (int)(usBuffLen) )
	{
		LK_ASSERT_STR(0, return -2, "usTmpTotalLen %d != usBuffLen %d", usTmpTotalLen, usBuffLen );
	}

	tpBuff += sizeof(unsigned short); 
	usTmpTotalLen -= sizeof(unsigned short);
	
	// �����л� CCSHead
	usTmpLen = (int) *((unsigned short*)tpBuff);
	tpBuff += sizeof(unsigned short);
	usTmpTotalLen -= sizeof(unsigned short);

	//TODO: ��ȫ���ж�,���� usTmpTotalLen ������< 0
	if( usTmpLen >= usTmpTotalLen || usTmpLen < 0 )
	{
		LK_ASSERT_STR(0, return -3, "usTmpLen %d", usTmpLen );
	}

	bParseRet = pCshead->ParseFromArray( tpBuff, usTmpLen );
	if( bParseRet != true )
	{
		return -4;
	}
	tpBuff += usTmpLen;
	usTmpTotalLen -= usTmpLen;

	if ( usTmpTotalLen <= 0 )
	{
		LK_ASSERT_STR(0, return -5, "usTmpTotalLen %d", usTmpTotalLen);
	}

	// ���￪ʼ����
	static unsigned char tEncryBuff[ MAX_PACKAGE_LEN ] = {0}; 
	unsigned char *tpEncryBuff = &tEncryBuff[0];
	int tOutLen = MAX_PACKAGE_LEN;
	
	DecryptData( EnCryptType1, pEncrypt, (unsigned char*)tpBuff, usTmpTotalLen, tpEncryBuff, &tOutLen );
	
	// ���ܺ�ĳ��Ȳ��ܳ������ushort , Ҳ���ܱ������δ����ǰ���ȳ�
	if( tOutLen >= 65535 || tOutLen > usTmpTotalLen )
	{
		LK_ASSERT_STR(0, return -6, "tOutLen %d", tOutLen );
	}

	// �����л� CMessage
	usTmpLen = (int) *((unsigned short*)tpEncryBuff);
	tpEncryBuff += sizeof(unsigned short);
	tOutLen -= sizeof(unsigned short);
	if( usTmpLen <= 3 || usTmpLen >= tOutLen || tOutLen <= 0 ) // �ͻ��˷�������Message������С��3
	{
#ifdef _DEBUG_ // ���������󽫻�ܶ࣬��Ҫ����Ϊ��Կ�仯��release�����ε���־��
		LK_ASSERT_STR(0, return -7, "usTmpLen %d", usTmpLen );
#else
		return -7;
#endif
	}

	bParseRet = pMsg->ParseFromArray( tpEncryBuff, usTmpLen );
	if( bParseRet != true )
	{
		return -8;
	}

	tpEncryBuff += usTmpLen;
	tOutLen -= usTmpLen;
	if( tOutLen <= 0 )
	{
		LK_ASSERT_STR(0, return -9, "tOutLen %d", tOutLen );
	}

	// �����л� CMessagePara
	usTmpLen = (int) *((unsigned short*)tpEncryBuff);
	if( usTmpLen < 0 || usTmpLen > tOutLen || usTmpLen >= 65535 )
	{
		LK_ASSERT_STR(0, return -10, "usTmpLen %d", usTmpLen );
	}

	tOutLen -= sizeof(unsigned short);

	// ��Ϣ����
	Message* tpMsgPara = CMessageFactory::GetSingletonPtr( )->CreateMessage( pMsg->msghead().messageid() );
	if( tpMsgPara == NULL )
	{
		LK_ASSERT_STR(0, return -11, "msgfactory can't create id %d ", pMsg->msghead().messageid() );
		return -11;
	}	

	tpEncryBuff += sizeof(unsigned short);
	bParseRet = tpMsgPara->ParseFromArray( tpEncryBuff, usTmpLen );

	if( bParseRet != true )
	{
#ifdef _USE_MESSAGE_BUFF_ // ���ʹ����placement new��new����һ�龲̬�洢��buffer,ֻ������������delete
		tpMsgPara->~Message();
#else
		delete tpMsgPara;
#endif
		
		pMsg->set_msgpara(0);
		
		return -12;
	}

	tOutLen -= usTmpLen;
	if( tOutLen != 0 )
	{
		LK_ASSERT_STR(0, return -13, "tOutLen %d", tOutLen );
	}

	pMsg->set_msgpara( (unsigned int)tpMsgPara );
	
	return 0;
}


// ***************************************************************
//  Function:		ConvertClientCodeToMsg2
//  Description:	������ר�ã�ת�����ݰ�����Ϣ��ʽ���м�����л��ͽ���
//	Input:			
//	OutPut:			
//	Return:			
//	Others:			��������ж�Ҫ�����ϸ���Ϊ���ܻ��зǷ������ݰ���
//					Ҫ��֤�յ�ʲô���ݶ����ܱ����������õ�assert,����release��ʱ������Ҫ-DNDEBUG��
//  Date:			02/05/2009
// 
// ***************************************************************
int ConvertClientCodeToMsg2 (  void* pBuff, unsigned short usBuffLen, CCSHead* pCshead, CMessage* pMsg, void* pMsgPara, unsigned short& rusParaLen, const unsigned char* pEncrypt )
{
	if( (pBuff == NULL) || ( usBuffLen < sizeof(unsigned short)*4 ) || (pCshead == NULL) || (pMsg == NULL) || (pMsgPara == NULL) )
	{
		return -1;
	}

	bool bParseRet = false;
	char* tpBuff = (char*)pBuff;
	int usTmpLen = 0;

	// �ܳ���
	int usTmpTotalLen = (int) *((unsigned short*)tpBuff);

	// ��֤�յ��İ��������ݰ��еİ����Ƿ�ƥ��
	if( usTmpTotalLen != (int) usBuffLen )
	{
		LK_ASSERT_STR(0, return -2, "usTmpTotalLen %d != usBuffLen %d", usTmpTotalLen, usBuffLen );
	}

	tpBuff += sizeof(unsigned short); 
	usTmpTotalLen -= sizeof(unsigned short);


	// �����л� CCSHead
	usTmpLen = (int) *((unsigned short*)tpBuff);
	tpBuff += sizeof(unsigned short);
	usTmpTotalLen -= sizeof(unsigned short);

	//TODO: ��ȫ���ж�,���� usTmpTotalLen ������<=0
	if( usTmpLen >= usTmpTotalLen || usTmpLen <= 0 )
	{
		LK_ASSERT_STR(0, return -3, "usTmpLen %d", usTmpLen );
	}

	bParseRet = pCshead->ParseFromArray( tpBuff, usTmpLen );
	if( bParseRet != true )
	{
		return -4;
	}
	tpBuff += usTmpLen;
	usTmpTotalLen -= usTmpLen;

	if ( usTmpTotalLen <= 0 )
	{
		LK_ASSERT_STR(0, return -5, "usTmpTotalLen %d", usTmpTotalLen );
		return -5;
	}

	// �����л� CMessage
	// ���￪ʼ����

	static unsigned char tEncryBuff[ MAX_PACKAGE_LEN ] = {0}; 
	unsigned char *tpEncryBuff = &tEncryBuff[0];
	int tOutLen = MAX_PACKAGE_LEN;
	DecryptData( EnCryptType1, pEncrypt, (unsigned char*)tpBuff, usTmpTotalLen, tpEncryBuff, &tOutLen );

	// ���ܺ�ĳ��Ȳ��ܳ������ushort , Ҳ���ܱ������δ����ǰ���ȳ�
	if( tOutLen >= 65535 || tOutLen > usTmpTotalLen )
	{
		LK_ASSERT_STR(0, return -6, "tOutLen %d", tOutLen);
	}

	usTmpLen = (int) *((unsigned short*)tpEncryBuff);
	tpEncryBuff += sizeof(unsigned short);
	tOutLen -= sizeof(unsigned short);

	if( usTmpLen <= 0 || usTmpLen >= tOutLen || tOutLen <= 0 )
	{
		LK_ASSERT_STR(0, return -7, "usTmpLen %d", usTmpLen);
	}

	bParseRet = pMsg->ParseFromArray( tpEncryBuff, usTmpLen );
	if( bParseRet != true )
	{
		return -8;
	}
	
	tpEncryBuff += usTmpLen;
	tOutLen -= usTmpLen;
	if( tOutLen <= 0 )
	{
		LK_ASSERT_STR(0, return -9, "tOutLen %d", tOutLen );
	}

	// ��Ϣ�巵�ص��ⲿ
	usTmpLen = *((unsigned short*)tpEncryBuff);
	tpEncryBuff += sizeof(unsigned short);

	memcpy( pMsgPara, tpEncryBuff, usTmpLen );
	rusParaLen = usTmpLen;

	return 0;
}



//int ConvertMsgToClientCode2( CCSHead* pCSHead, CMessage* pMsg, void* pBuff, unsigned short& rusBuffLen )
//{
//	if( (pCSHead == NULL) || (pMsg == NULL) || (pBuff == NULL) || (pMsg->msgpara() == 0)
//		|| (rusBuffLen < sizeof(unsigned short)*4)  )
//	{
//		return -1;
//	}
//
//	bool bSerializeRet = false;
//	char* tpBuff = (char*)pBuff;
//	unsigned short usTmpLen = 0;
//	unsigned short usTmpLeftLen = rusBuffLen;
//
//	// �ճ��ܳ���2bytes
//	tpBuff += sizeof(unsigned short);
//	usTmpLeftLen -= sizeof(unsigned short);
//
//	// ���л�CCSHead
//	// �ܳ����Ȳ���
//	pCSHead->set_totallength( 0 );
//	*((unsigned short*)tpBuff) = pCSHead->ByteSize();
//	tpBuff += sizeof(unsigned short);
//	usTmpLeftLen -= sizeof(unsigned short);
//	
//	bSerializeRet = pCSHead->SerializeToArray( tpBuff, usTmpLeftLen );
//	if( bSerializeRet != true )
//	{
//		return -1;
//	}
//
//	tpBuff += pCSHead->GetCachedSize();
//	usTmpLeftLen -= pCSHead->GetCachedSize();
//
//
//	// ���л� CMessage
//
//	// ���￪ʼ����
//	//unsigned char tEncryBuff[ MAX_PACKAGE_LEN ] = {0};
//	//unsigned char *tpEncryBuff = &tEncryBuff[0];
//
//	/**((unsigned short*)tpBuff) = pMsg->ByteSize();
//	tpBuff += sizeof(unsigned short);
//	usTmpLeftLen -= sizeof(unsigned short);*/
//
//	*((unsigned short*)tpBuff) = pMsg->ByteSize();
//	tpBuff += sizeof(unsigned short);
//	usTmpLeftLen -= sizeof(unsigned short);
//
//	bSerializeRet = pMsg->SerializeToArray( tpBuff, usTmpLeftLen );
//	if( bSerializeRet != true )
//	{
//		return -1;
//	}
//
//	/*tpBuff += pMsg->ByteSize();
//	usTmpLeftLen -= pMsg->ByteSize();*/
//
//	tpBuff += pMsg->GetCachedSize();
//	usTmpLeftLen -= pMsg->GetCachedSize();
//
//	// ���л� CMessagePara
//	Message* tpMsgPara = (Message*)pMsg->msgpara();
//	if( tpMsgPara == NULL )
//	{
//		return -1;
//	}
//
//	/**((unsigned short*)tpBuff) = tpMsgPara->ByteSize();
//	tpBuff += sizeof(unsigned short);
//	usTmpLeftLen -= sizeof(unsigned short);*/
//
//	*((unsigned short*)tpBuff) = tpMsgPara->ByteSize();
//	tpBuff += sizeof(unsigned short);
//	usTmpLeftLen -= sizeof(unsigned short);
//
//	bSerializeRet = tpMsgPara->SerializeToArray( tpBuff, usTmpLeftLen );
//	if( bSerializeRet != true )
//	{
//		return -1;
//	}
//
//	tpBuff += tpMsgPara->GetCachedSize();
//	usTmpLeftLen -= tpMsgPara->GetCachedSize();
//
//	//int tEncryptLen = MAX_PACKAGE_LEN;
//	//tpEncryBuff = &tEncryBuff[0];
//	//EncryptData( EnCryptType1, pEncrypt, tpEncryBuff, sizeof(unsigned short)*2 + pMsg->GetCachedSize() + tpMsgPara->GetCachedSize(), (unsigned char*)tpBuff, &tEncryptLen );
//
//	// ѹ���ܳ���
//	//rusBuffLen = sizeof(unsigned short)*4 + pCSHead->ByteSize() + pMsg->ByteSize() + tpMsgPara->ByteSize();
//	rusBuffLen = sizeof(unsigned short)*4 + pCSHead->ByteSize() + pMsg->ByteSize() + tpMsgPara->ByteSize();
//	*((unsigned short*)pBuff) = rusBuffLen;
//
//	return 0;
//}
//

// ***************************************************************
//  Function:	 
//  Description:	ֻ���л�CMessage����
//	Input:			
//	OutPut:			
//	Return:			
//	Others:			2bytes msghead���� + msg���л����buff + 2bytes msgpara���� + msgpara���л����buff
//  Date:			02/03/2009
// 
// ***************************************************************
int ConvertMsgToClientCode3( CMessage* pMsg, void* pBuff, unsigned short& rusBuffLen )
{
	if( (pMsg == NULL) || (pBuff == NULL) || (pMsg->msgpara() == 0) || (rusBuffLen < sizeof(unsigned short)*3)  )
	{
		return -1;
	}

	bool bSerializeRet = false;
	char* tpBuff = (char*)pBuff;
	unsigned short usTmpLeftLen = rusBuffLen;

	//// �ճ��ܳ���2bytes
	//tpBuff += sizeof(unsigned short);
	//usTmpLeftLen -= sizeof(unsigned short);

	// ���л� CMessage
	*((unsigned short*)tpBuff) = pMsg->ByteSize();
	tpBuff += sizeof(unsigned short);
	usTmpLeftLen -= sizeof(unsigned short);

	bSerializeRet = pMsg->SerializeToArray( tpBuff, usTmpLeftLen );
	if( bSerializeRet != true )
	{
		return -1;
	}

	tpBuff += pMsg->GetCachedSize();
	usTmpLeftLen -= pMsg->GetCachedSize();

	// ���л� CMessagePara
	Message* tpMsgPara = (Message*)pMsg->msgpara();
	if( tpMsgPara == NULL )
	{
		return -1;
	}

	*((unsigned short*)tpBuff) = tpMsgPara->ByteSize();
	tpBuff += sizeof(unsigned short);
	usTmpLeftLen -= sizeof(unsigned short);

	bSerializeRet = tpMsgPara->SerializeToArray( tpBuff, usTmpLeftLen );
	if( bSerializeRet != true )
	{
		return -1;
	}

	tpBuff += tpMsgPara->GetCachedSize();
	usTmpLeftLen -= tpMsgPara->GetCachedSize();

	rusBuffLen = sizeof(unsigned short)*2 + pMsg->GetCachedSize() + tpMsgPara->GetCachedSize();
	return 0;
}



int ConvertMsgToClientCode2( CCSHead* pCSHead, CMessage* pMsg, void* pBuff, unsigned short& rusBuffLen, const unsigned char* pEncrypt )
{
	if( (pCSHead == NULL) || (pMsg == NULL) || (pBuff == NULL) || (pMsg->msgpara() == 0)
		|| (rusBuffLen < sizeof(unsigned short)*4)  )
	{
		return -1;
	}

	bool bSerializeRet = false;
	char* tpBuff = (char*)pBuff;
	unsigned short usTmpLeftLen = rusBuffLen;

	// �ճ��ܳ���2bytes
	tpBuff += sizeof(unsigned short);
	usTmpLeftLen -= sizeof(unsigned short);

	// ���л�CCSHead
	// �ܳ����Ȳ���
	//pCSHead->set_totallength( 0 );
	*((unsigned short*)tpBuff) = pCSHead->ByteSize();
	tpBuff += sizeof(unsigned short);
	usTmpLeftLen -= sizeof(unsigned short);

	bSerializeRet = pCSHead->SerializeToArray( tpBuff, usTmpLeftLen );
	if( bSerializeRet != true )
	{
		return -2;
	}

	tpBuff += pCSHead->GetCachedSize();
	usTmpLeftLen -= pCSHead->GetCachedSize();


	// ���л� CMessage

	// ���￪ʼ����
	unsigned char tEncryBuff[ MAX_PACKAGE_LEN ] = {0};
	unsigned char *tpEncryBuff = &tEncryBuff[0];

	*((unsigned short*)tpEncryBuff) = pMsg->ByteSize();
	tpEncryBuff += sizeof(unsigned short);
	usTmpLeftLen -= sizeof(unsigned short);

	bSerializeRet = pMsg->SerializeToArray( tpEncryBuff, usTmpLeftLen );
	if( bSerializeRet != true )
	{
		return -3;
	}

	tpEncryBuff += pMsg->GetCachedSize();
	usTmpLeftLen -= pMsg->GetCachedSize();

	// ���л� CMessagePara
	Message* tpMsgPara = (Message*)pMsg->msgpara();
	if( tpMsgPara == NULL )
	{
		return -4;
	}

	*((unsigned short*)tpEncryBuff) = tpMsgPara->ByteSize();
	tpEncryBuff += sizeof(unsigned short);
	usTmpLeftLen -= sizeof(unsigned short);

	bSerializeRet = tpMsgPara->SerializeToArray( tpEncryBuff, usTmpLeftLen );
	if( bSerializeRet != true )
	{
		return -5;
	}

	tpEncryBuff += tpMsgPara->GetCachedSize();
	usTmpLeftLen -= tpMsgPara->GetCachedSize();

	int tEncryptLen = MAX_PACKAGE_LEN;
	tpEncryBuff = &tEncryBuff[0];
	EncryptData( EnCryptType1, pEncrypt, tpEncryBuff, sizeof(unsigned short)*2 + pMsg->GetCachedSize() + tpMsgPara->GetCachedSize(), (unsigned char*)tpBuff, &tEncryptLen );

	// ѹ���ܳ���
	rusBuffLen = sizeof(unsigned short)*2 + pCSHead->GetCachedSize() + tEncryptLen;
	*((unsigned short*)pBuff) = rusBuffLen;

	return 0;
}

//int EncryptMsg( void* pBuff, short& rusBuffLen, const unsigned char* pEncrypt )
//{
//	if( (pBuff == NULL) || (rusBuffLen < sizeof(unsigned short)*4)  )
//	{
//		return -1;
//	}
//
//	char* tpBuff = (char*)pBuff;
//
//	tpBuff += rusBuffLen;
//
//	char* tpIniBuff = tpBuff;
//	unsigned short usTmpLen = 0;
//	//unsigned short usTmpLeftLen = rusBuffLen;
//
//	// �ճ��ܳ���2bytes
//	unsigned short tTotalLen = *(unsigned short*)tpBuff;
//	tpBuff += sizeof(unsigned short);
//	//usTmpLeftLen -= sizeof(unsigned short);
//
//	unsigned short tHeadLen = *(unsigned short*)tpBuff;
//	tpBuff += sizeof(unsigned short);
//	//usTmpLeftLen -= sizeof(unsigned short);
//
//	tpBuff += tHeadLen;
//	//usTmpLeftLen -= tHeadLen;
//
//
//	// ���л� CMessage
//
//	// ���￪ʼ����
//	unsigned char tEncryBuff[ MAX_PACKAGE_LEN ] = {0};
//	unsigned char *tpEncryBuff = &tEncryBuff[0];
//
//	int tEncryptLen = MAX_PACKAGE_LEN;
//	memcpy( tpEncryBuff, tpBuff, tEncryptLen );
//	short tInLen = tTotalLen - tHeadLen - sizeof(unsigned short)*2;
//	if ( tInLen <= 0 )
//	{
//		return -1;
//	}
//	EncryptData( EnCryptType1, pEncrypt, tpEncryBuff, tInLen, (unsigned char*)tpBuff, &tEncryptLen );
//
//	// ѹ���ܳ���
//	//rusBuffLen = sizeof(unsigned short)*4 + pCSHead->ByteSize() + pMsg->ByteSize() + tpMsgPara->ByteSize();
//	tTotalLen = sizeof(unsigned short)*2 + tHeadLen + tEncryptLen;
//	*((unsigned short*)tpIniBuff) = tTotalLen;
//	rusBuffLen += tTotalLen;
//
//	return 0;
//}
//
//
//

// ***************************************************************
//  Function:		EncryptData 
//  Description:	��������
//	Input:			nAlgorithm	- �����㷨����
//					pbyKey		- ��Կ
//					pbyIn		- ����buff
//					nInLength	- ���볤��
//					pbyOut		- ���buff(��������)
//					pnOutLength	- �������
//	OutPut:			��
//	Return:			��
//	Others:			pbyOutΪ���ĸ�ʽ,pnOutLengthΪpbyOut�ĳ���,��8byte�ı���,����ӦԤ��nInLength+17;
//  Date:			12/18/2008
// 
// ***************************************************************
void EncryptData(short nAlgorithm, const BYTE *pbyKey, const BYTE *pbyIn, int nInLength, BYTE *pbyOut, int *pnOutLength)
{
	if ( pbyKey == NULL || pbyIn == NULL || pbyOut == NULL || pnOutLength == NULL )
	{
		return ;
	}

	switch( nAlgorithm )
	{
	case 0:
		{
			memcpy( pbyOut, pbyIn, nInLength );
			*pnOutLength = nInLength;
			break;
		}
	case 1:
		{
			oi_symmetry_encrypt( pbyIn, nInLength, pbyKey, pbyOut, pnOutLength );
			break;
		}
	case 2:
		{
			oi_symmetry_encrypt2( pbyIn, nInLength, pbyKey, pbyOut, pnOutLength );
			break;
		}
	default:
		{
			break;
		}

	}

	return ;
}
//
//
// ***************************************************************
//  Function:		DecryptData
//  Description:	��������
//	Input:			nAlgorithm	- �����㷨����
//					pbyKey		- ��Կ
//					pbyIn		- ����buff(��������)
//					nInLength	- ���볤��
//					pbyOut		- ���buff(��������)
//					pnOutLength	- �������
//	OutPut:			��
//	Return:			1 - ���ܳɹ�; 0 - ����ʧ��
//	Others:
//  Date:			12/18/2008
// 
// ***************************************************************
int DecryptData(short nAlgorithm, const BYTE *pbyKey, const BYTE *pbyIn, int nInLength, BYTE *pbyOut, int *pnOutLength)
{
	if( pbyKey == NULL || pbyIn == NULL || pbyOut == NULL || pnOutLength == NULL )
	{
		return 0;
	}

	int nDecryResult = 0;

	switch( nAlgorithm )
	{
	case 0:
		{
			memcpy( pbyOut, pbyIn, nInLength );
			*pnOutLength = nInLength;
			nDecryResult= 1;
			break;
		}
	case 1:
		{
			nDecryResult = oi_symmetry_decrypt( pbyIn, nInLength, pbyKey, pbyOut, pnOutLength );
			break;
		}
	case 2:
		{
			nDecryResult = oi_symmetry_decrypt2( pbyIn, nInLength, pbyKey, pbyOut, pnOutLength );
			break;
		}
	default:
		{
			break;
		}
	}

	return nDecryResult;

}




}

