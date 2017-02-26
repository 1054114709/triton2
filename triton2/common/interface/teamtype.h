#pragma once

enum TEAM_DISTRIBUTE			// ������Ʒ����ģʽ
{
	ALTERNATION			=			0x1001,				// ��������
	RANDOM,												// ���ɷ���
	PROBABILITY,										// ���ʷ���
};

enum CONSCRIBE_TYPE				// ������ļ��������
{
	TYPE_SUBPALACE		=			0x1003,				// �ع�
	TYPE_COPY,											// ����
	TYPE_TASK ,											// ����
	TYPE_ACTIVITY,										// �
	TYPE_COMMON,										// ��ͨ
	TYPE_PVP,											// PVP
};

enum AVLIVE_STATE				// �������״̬
{	
	emOnLine			=	0xA001,						// ����, �ڵ�ͼ��
	emOffLine,											// ����, �뿪��Ϸ
	emDownLine,											// ����
	emLogonAgain,										// �ص�¼
	emRedirect,											// �糡��
	emItemDead,											// ��Ա����
	emOverDistance,										// ������Ч����
};

enum MEMBER_TYPE
{
	emTeamHead			=   0,
	emTeamItem			=	1,
};

enum MSG_TYPE
{
	TEAM_ASKFOR			=	0x3001,				// ������Ϣ
	TEAM_CONSCRIBE,
	TEAM_INITWND,								// ��ʼ������ļ����
	TEAM_CLAIMINIT,								// ���鴰�ڳ�ʼ��
	TEAM_RECRUITINIT,							// ��ļ������ʼ��
};

enum ACTIVE_RTN						// ����ķ��ؽ��
{
	emRefuse		=	0,					// �ܾ�
	emAgree			=	1,					// ͬ��
	emIgnore		=	2,					// ����
};

#define TEAM_ADD							0x100A		// ������Ա
#define TEAM_DEL							0x100B		// ɾ����Ա
#define TEAM_HEAD							0x100C		// �ӳ���־
#define TEAM_UPDATE							0x100D		// ���¶���

#define TEAM_SETUP							0x100E		// �������
#define TEAM_OVER							0x100F		// �����ɢ

#define _TEAM_INVITE_						0x0100		// ���붯��
#define _TEAM_INVITE_RTN_					0x0200		// ���뷵�ض���
#define _TEAM_REQUEST_						0x0300		// ���붯��
#define _TEAM_REQUEST_RTN_					0x0400		// ���뷵�ض���
#define _TEAM_CLAIMJOIN_					0x0500		// ���鶯��
#define _TEAM_RECRUIT_						0x0600		// ��ļ����
#define _TEAM_ATTORN_HEADER_				0x0700		// ת�ƶӳ�����
#define _TEAM_ALTER_DISTRIBUTE_				0x0800		// �ı����ģʽ����
#define _TEAM_LEAVE_TEAM_					0x0900		// �뿪����
#define _TEAM_END_TEAM_						0x0A00		// ��ɢ����
#define _TEAM_TICK_PLAYER_					0x0B00		// �߳����
#define _TEAM_FOLLOW_ORDER_					0x0C00		// �������
#define _TEAM_ASK_FOLLOW_					0x0D00		// �������
#define _TEAM_CREATETEAM_					0x0E00		// ��������
#define _TEAM_OPERATE_MASK_					0x0F00		// ��λ����
#define _TEAM_NOT_INSCENE_					0x1000		// ���ڱ�����
#define _TEAM_COOLING_TIME_					0x1100		// ��ȴʱ��		


#define _TEAM_SUCCESS_						0x0001		// �����ɹ�					
#define _TEAM_FAILURE_						0x0002		// ����ʧ��					
#define _TEAM_REFUSE_						0x0003		// �ܾ�����	
#define _TEAM_PLAYER_ADD_					0x0004		// ��ӳ�Ա
#define _TEAM_PLAYER_DEL_					0x0005		// ɾ����Ա
#define _TEAM_HEADER_						0X0006		// �ӳ���־
#define _TEAM_PLAYER_NONE_					0x0007		// ��Ҳ�����				
#define _TEAM_PLAYER_BUSY_					0x0008		// ���æµ��
#define _TEAM_NOT_FOUND_					0x0009		// ���鲻����
#define _TEAM_FULL_							0x000A		// ��������
#define _TEAM_IN_TEAM_						0x000B		// ����ڶ�����
#define _TEAM_HEADER_NONE_					0x000C		// ���Ƕӳ�
#define _TEAM_OUT_TEAM_						0x000D		// ��Ҳ��ڶ�����
#define _TEAM_REPEATED_MSG_					0x000E		// �ظ�������Ϣ
#define _TEAM_NEW_HEADER_					0x000F		// ��Ϊ�¶ӳ�
#define _TEAM_ON_LINE_						0x0010		// �������
#define _TEAM_DOWN_LINE_					0x0012		// ��ҵ���
#define _TEAM_MAP_FULL_						0x0013		// ά�����б�����
#define _TEAM_LEVEL_LOW_					0x0014		// ��Ҽ��𲻹�
#define _TEAM_MORE_DISTANCE_				0x0015		// ������Ч����
#define _TEAM_DIFFNATION_					0x0016		// ��ͬ����

enum TeamOrderType					// �������
{
	emCancelFollow			= 0,		// ȡ������
	emOrderFollow			= 1,		// ����
};

#define TEAM_NUMBER			6
#define TEAM_MSG_LEN		32
#define MAX_INVITE_NUM		6		//������롢������
#define MAX_RECINVITE_NUM	5		// ����յ����������
#define PAGE_MAX			8		// ÿҳ��ʾ�������Ϣ��
#define INVALID_DISTANCE	15		// 
#define TEAM_ORDER_FIRST    1      // �����е���ţ���1��ʼ


enum TEAM_UPDATE_TYPE
{
	ACTION_JOIN			= 0,
	ACTION_LEAVE,
	ACTION_KICK,
	ACTION_ENDTEAM,
	ACTION_CHANGEHEADER,
	ACTION_UPATEFLAG,
};

enum CLAIM_RECRUIT_TYPE
{
	TYPE_CLAIM			= 0,
	TYPE_RECRUIT,
};

enum FOLLOW_TYPE
{
	FOLLOW_REQUEST		= 0,
	FOLLOW_ORDER,
};

enum InvReqType
{
	Type_Inv			= 0,
	Type_Req,
};
