#pragma once

#include "sceneobj_manager.h"
#include "sceneobj_manager_imp.h"
#include "entity.h"
#include "mapmodule.h"

class CEntity;
class CCreator;

// ����ӳ�ˢ����
#define MAX_DELAY_REFRESH_CREATURE_NUM	1000


// �ӳ�ˢ��
struct CDelayRefreshedCreature
{	
	CDelayRefreshedCreature(	unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, unsigned int unCreatorID, unsigned int vNpcID = 0 )
		: mLineID( vLineID ), mMapID( vMapID ), mMapIndex( vIndex ), mCreatorID( unCreatorID ), mNpcID( vNpcID )
	{}
	
	CDelayRefreshedCreature() 
	{
		if( CObj::msCreateMode )
		{
			mLineID = 0;
			mMapID = 0;
			mMapIndex = 0;
			mCreatorID = 0;
			mNpcID = 0;
		}
	}
	~CDelayRefreshedCreature() {}

	unsigned short	mLineID;		// ��ID
	unsigned short	mMapID;			// ��ͼID
	unsigned short	mMapIndex;		// ��ͼ����
	unsigned int	mCreatorID;		// ������ID
	unsigned int	mNpcID;			// NpcID�����ܻ����ⲿָ����Ĭ��0
};


class CCreatureRefresher : public CSingleton< CCreatureRefresher >
{
public:
	CCreatureRefresher();
	~CCreatureRefresher();

	void Initailze();
	void Resume();

	/*
	1����ʱˢ��
	��������ʵʱ��ˢ�¡�
	ÿ����ض�ʱ�䣨����ÿ���12��00��
	ÿ�ܵ��ض�ʱ�䣨����ÿ�ܵ���6��12��00��
	ÿ�µ��ض�ʱ�䣨����5�µĵ�1���12��00��
	�ض��µ��ض��ܵ��ض�ʱ�䣨�������µĵ�2�ܵ���5��20��00��
	����4�־�Ҫ���ͬʱ���ö��ʱ�䣨����ÿ���8��00��12��00��16��00��20��00��
	���ϵ�4����ˢ�·�ʽ����Թ��ﱾ��
	5����ʱ���������������ڼ�ʱ��ùִ��ڣ��������˴�ˢ�µ�ʱ�䡣
	*/
	void OnTimeRefreshEvent( int vIndex = 0 );

	/*
	2����������
	��һ��������ˢ��N�����Ժ�ˢ���ض��֡���Ҫ����������������ض��Ĺ֣�
	�������˺�N��ˢ���ض��֣�N���ɲ߻����ã�
	��ˢ�¹������һ������
	�����һ�ֹ֣�ˢ��N��A�ֺ�ˢ���ض���B�֣�Ȼ��A�ּ���ˢ�£�����ΪB�ֵĳ��ֶ��ı�A�ֵ�ˢ�²��ԡ���B�������Ժ����¿�ʼ����������A��ˢ�µ�������
	������N�ֹּ��ϣ����������й�ˢ��N����ˢ���ض���B�֡�B��ˢ�º���ΪB�ֵĳ��ֶ��ı����������ֵ�ˢ�²��ԡ���B�������Ժ����¿�ʼ���������������ֵ�������
	Ҫ�����ˢ���߼�������1000���Ժ�ˢA��3000���Ժ�ˢB��A��B��ˢ�²��໥���ţ���
	����������ͬһ������������ͬ��ˢ�¹��򣬷�����Ϊͬһ������ֵ���ڡ�
	*/
	void OnNumericalRefreshEvent( CEntityNpc* pNpc );


	/*
	3�����ʴ���
	��һ��������ˢ��A�ֵ�ͬʱ��һ���ĸ���ˢ���ض���B�֡�
	�ڸ�������ÿˢ��һ��A������һ������ˢ��B�֡�
	B���Ǻ�A��һ��ˢ�£������Ǹ���A�֡�
	�����������Ĺֲ����ܸ��ʴ���B�ֵ�ˢ�£�������������Ҳ������B�ֵ�ˢ�¸��ʣ�
	B�ֵ�ˢ�²���Ӱ��������������κ�ˢ�¹���
	Ҫ��һ���ֿɸ��ʴ�������ֵ�ˢ�¡�
	*/
	void OnPossibilityRefreshEvent( COgreCreator *pCreator, int vIndex );
	
	/*
	4�����ʱ��ˢ��
	����A���һ��ʱ��û����ˢ������һ�ֹ���B��
	����A�ǿ����ƶ��Ĺ֡�
	����Bˢ�µ�ʱ���ڹ���A��ǰ�ĵ���ˢ�¡�
	����Bˢ�µ�ʱ�����A��ʧ��
	����A����ˢ���߼�ˢ�º�ʼ������ʱ��
	���ʱ���ɲ߻����á�
	Ҫ��������ö��������A���һ��ʱ��ˢB��B���һ��ʱ��ˢC����
	*/
	void OnLifetimeRefreshEvent( CEntityNpc* pNpc, int index );


	/*
	8��������һ����ʽˢ��
	һ��ˢ�µ�����N���ֵ�ˢ�£�ÿ���ֶ�����һ��ˢ�¸��ʣ�N���ֵ�ˢ�¸��ʺ�Ϊ1��
	ˢ��ĳ�ֹֺ��������ֵ�ˢ���ˡ���50%ˢA��50%ˢB��Bˢ�º�ˢA����
	*/
	int OnDeathRefreshEvent( COgreCreator* pCreator );


	/*
	7�����ͼ���ˢ��
	���ͼ�Ķ��ˢ�£���Ϊͬһ��ˢ�µ㴦��
	10���㶼��һ������ˢ��A�֣�����A���ڵ�1����ˢ�º󣬺���9����Ͳ�ˢ���ˡ�
	�����ˢ�¼����ɲ߻����ã����ʺ�Ϊ1��
	*/
	COgreCreator* OnMutiMapRefreshEvent( COgreCreator* pCreator );

public:

	// ���뵽�ӳ�ˢ���б�
	bool AddToDelayRefreshList( const CDelayRefreshedCreature& pCreature );

	// ���ӳ�ˢ���б�ɾ��
	bool RemoveFromDelayRefreshList( CDelayRefreshedCreature& pCreature );

	// ����ӳ�ˢ���б�
	void ClearDelayRefreshList( ); 

	// ִ���ӳ�ˢ��
	int DoDelayRefresh( );

	// ��ʱ��
	void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );

private:

	typedef lk::vector< CDelayRefreshedCreature, MAX_DELAY_REFRESH_CREATURE_NUM > TDelayRefreshList;

	
	TDelayRefreshList	mDelayRefreshList;	// �ӳ�ˢ���б�
	CWTimer				mDelayRefreshTimer;	// �ӳ�ˢ��timer

};
