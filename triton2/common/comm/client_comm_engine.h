#pragma once

#include "oi_tea.h"


// �����붨��
enum 
{
	CLIENT_COMM_ENGINE_SUCCESS = 0,
};

enum EncryptType
{
	EncryptNone	 = 0,
	EnCryptType1 = 1,
	EnCryptType2 = 2,
};


class CCSHead;
class CMessage;



namespace ClientCommEngine
{

static int tKey[ 4 ] = {4356,78534,46677,3545};		// ��ֵ����
static unsigned char* tpKey = (unsigned char*)&tKey[0];

// ***************************************************************
//  Function: 	ConvertClientCodeToMsg2   
//  Description:�ѿͻ���codeת����CCSHead + CMessage, 
//				��Ϣ��ָ���Ѿ����ڲ���ֵ����CMessage.msgpara
//				ע�⣺��Ҫ���ⲿdelete msgpara
//  Date: 		09/24/2008
// 
// ***************************************************************
int ConvertClientCodeToMsg2( const void* pBuff, unsigned short usBuffLen, CCSHead* pCshead, CMessage* pMsg, const unsigned char* pEncrypt = tpKey );


// ***************************************************************
//  Function: 	ConvertClientCodeToMsg2   
//  Description:�ѿͻ���codeת����CCSHead + CMessage, 
//				��������Ϣ�壬����ֵ (�������ڲ�ʹ��)
//  Date: 		09/24/2008
// 
// ***************************************************************
int ConvertClientCodeToMsg2 ( void* pBuff, unsigned short usBuffLen, CCSHead* pCshead, CMessage* pMsg, void* pMsgPara, unsigned short& rusParaLen, const unsigned char* pEncrypt = tpKey );


// ***************************************************************
//  Function: 	ConvertMsgToClientCode2   
//  Description:��CCSHead + CMessasge ת���ɿͻ���Code
//  Date: 		09/24/2008
// 
// ***************************************************************
int ConvertMsgToClientCode2(  CCSHead* pCSHead,  CMessage* pMsg, void* pBuff, unsigned short& rusBuffLen, const unsigned char* pEncrypt );

// ֻ���л�
//int ConvertMsgToClientCode2(  CCSHead* pCSHead,  CMessage* pMsg, void* pBuff, unsigned short& rusBuffLen );
int ConvertMsgToClientCode3( CMessage* pMsg, void* pBuff, unsigned short& rusBuffLen );

//int EncryptMsg( void* pBuff, short& rusBuffLen, const unsigned char* pEncrypt );





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
void EncryptData(short nAlgorithm, const BYTE *pbyKey, const BYTE *pbyIn, int nInLength, BYTE *pbyOut, int *pnOutLength);


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
int DecryptData(short nAlgorithm, const BYTE *pbyKey, const BYTE *pbyIn, int nInLength, BYTE *pbyOut, int *pnOutLength);


};


