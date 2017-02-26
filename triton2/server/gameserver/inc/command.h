
/******************************************************************************
	��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

******************************************************************************
	�ļ���          : command.h
	�汾��          : 1.0
	����            : ZHL
	��������        : 2009-06-24
	����޸�        : 
	��������        : ����ģʽ��Ϲ۲���ģʽ�������������ӿڣ�Ϊ�Ժ��ع���׼����
	�����б�        : 
	�޸���ʷ        : 
	1 ����          : 2009-06-24
	����			: ZHL
	�޸�����		: ����
*******************************************************************************/
#pragma once

#include "event.h"




// ��������
enum enCmdType
{
	ECMD_SENDPLAYERINFTOGATE	= 1,
};


class CCommand : public CEventObserver
{
public:

	CCommand() {}
	virtual ~CCommand() {}

	virtual int Do() = 0;

	virtual int OnEventTrigger( CEvent* pEvent ) = 0;
	
};


// ֪ͨ��Ҹ�����Ϣ�ı䵽����
class CCommandSendPlayerDirtyDataToGate : public CCommand
{
public:

	CCommandSendPlayerDirtyDataToGate( unsigned int unPlayerID ): mPlayerID( unPlayerID ), mDirtyDataBit(0) {}
	virtual ~CCommandSendPlayerDirtyDataToGate() {}


	virtual int Do();

	virtual int OnEventTrigger( CEvent* pEvent ) ;
	virtual int OnEventTrigger( int nBitFlag );

	enum
	{
		DIRTYDATA_LEVEL		= 0x0001,
		DIRTYDATA_LINEID	= 0x0002,
		DIRTYDATA_MAPID		= 0x0004,
		DIRTYDATA_METIER	= 0x0008,
		DIRTYDATA_HP		= 0x0010,
		DIRTYDATA_MP		= 0x0020,
		DIRTYDATA_RED		= 0x0040,
	};

private:

	unsigned int mPlayerID;	// ��ID��Ϊ���Ժ���ڹ����ڴ���
	int mDirtyDataBit;
};