#ifndef _AHTHUNK_H_
#define _AHTHUNK_H_
/******************************************************************************
	��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

******************************************************************************
	�ļ���		: ahthunk.h
	�汾��		: 1.0
	����		: ZHL
	��������	: 16:6:2009
	����޸�	: 
	��������	: Apex����ҽӿ��ļ�

	�����б�	: 
	�޸���ʷ	: 

	Ƕ��˵����
	1. �� \ApexItemServer ������ gameserver ��(Ŀ¼�ǲ��޶���); 
	2. �� \ApexProxy\AHThunkConfig.xml �� \ApexProxy\ApexProxy.so ������ gameserver ��Ŀ¼��(���� gameserver �� .exe ����ͬ��Ŀ¼);
	3. �� \Client\ACDC.Dat��rdmex.dll��rdm.exe ��������Ϸ�ͻ��˵ĸ�Ŀ¼��;
	4. �� \Interface\Client\AHClientInterface.lib ��Interface\Client\ApexClient.h ������Ϸ�ͻ���;
	5. �� \Interface\Server\ApexProxy.h �� \Interface\Server\ApexProxy.cpp������Ϸ��������;
	6. �� gameserver ��Ŀ¼�½����ļ��� hook_log.

	˵����Ƕ��ʱ���������ļ�һ��Ҫ��ԭ��,��Ҫʹ�÷����ġ�
	\ApexItemServer\config\AHNetServerConfig.xml �޸� IP �� port��
	\ApexProxy\AHThunkConfig.xml �޸�����AHNetServer�� IP �� port��
	

*******************************************************************************/


#include "servertool.h"
#include "lk_vector.h"


// ������ӳٴ�������
class CAHDelayData
{
public:
	int mCharID; // ��ɫid
	int mReason; // ԭ��
};


// ����ҿ��ƹ�����
class CAHContorlManager : public CSingleton<CAHContorlManager>
{
	typedef lk::hash_map< int, CAHDelayData, 500 >	PLAYERID_VEC;	// �������

public:

	CAHContorlManager();
	~CAHContorlManager();

	int Initailize( );
	int Resume( );

	int OnTimer( unsigned int vTickCount, unsigned int vTickOffset );


	int AddToDelayProcessList( const CAHDelayData& rDelayData );

	// �ӳ������б�(charid)
	PLAYERID_VEC	mPlayerDelayProcList;
};



/* GameServer�ṩ��Apex Proxy �ķ��ͺ���;
������pBuffer: �������ݵĻ�����
		nLen : �������ݵĳ���
*/
long NetSendToGameClient(signed int nSendId, const char * pBuffer, int nLen);

/* GameServer�ṩ�����˺���
����:nId: ��ҵ�charid
ʵ���������,��һ�����������;
*/
long GameServerKillUser( signed int nId, int nAction );

/* ����Apex����
*/
int StartApexProxy();

/* ֹͣApex����
*/
int StopApexProxy();

/* ֪ͨApex��ҵ�½
����:nSendId: ��ҵ�charid
*/
int NoticeApexProxy_UserLogin( int nSendId );

/* ֪ͨApex��ҵ�½
����:nSendId: ��ҵ�charid
*/
int	NoticeApexClient_Ret( int nSendId, const char * pRet );

/* ֪ͨApex����˳�
����:nSendId: ��ҵ�charid
*/
int	NoticeApexProxy_UserLogout( int nSendId );

/* ֪ͨApex��ҷ��������
����:nSendId: ��ҵ�charid
	:pBuf: 2��������
	:nBuffLen: ���ݳ���
*/
int	NoticeApexProxy_UserData( int nSendId, const char * pBuf, int nBufLen );


#endif //_AHTHUNK_H_

