#ifndef _PROXY_HEAD_HPP_
#define _PROXY_HEAD_HPP_

#include "base.h"

#define MAXSVRNUMBER 256


#define BASEPXYHEADLENGTH			14
#define PROXY_RESERVE				((BYTE)0x01)
#define PROXY_CMD					((BYTE)0x02)



#define MAXPROXYOPTLENGTH			256
enum enProxyCmds
{
	CMD_NULL	= 0,
	CMD_REGKEY	= 1,
	CMD_START	= 2, 
	CMD_REGSERVER = 3,               //������ע��
	CMD_KEEPALIVE = 4,                 //����
};


/*���¶���ת������*/
enum eTransTypes
{
	trans_p2p = 0,			//�㵽��
	trans_p2g,				//�㵽��
	trans_broadcast,		//ͬ�͹㲥
	trans_bykey				//���ݹؼ���ת��
};


class CProxyHead
{
public:
	CProxyHead();
	~CProxyHead();
	int Encode(char *pCode, short & nCodeLength);
	int Decode(char *pCode, short nCodeLength);
	void Print();
		
	short m_nTotalLength;
	short m_nSrcFE;
	short m_nSrcID;
	short m_nDstFE;
	BYTE m_byTransferType;
	union _U
	{
		unsigned int Uin;
		short nDstID;
		struct _tagSvrs
		{
			short nFENumber;
			short anFEs[MAXSVRNUMBER];
		} stSvrs;
	} m_stTransferInfo;
	BYTE m_byOpFlag;
	short m_nOptLength;
	BYTE m_abyOpt[MAXPROXYOPTLENGTH];
	short m_nBodyLength;
};

#endif
