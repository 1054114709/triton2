#pragma once 

#define MAX_MASSAGE_LEN 512			  // ��Ϣ��󳤶�
#define MAXBUGLECHATNUM 6000
#define MAXAUTOCHATNUM  3000
#define MAX_ITEMBUFF_LENGTH	2048	  // ������Ϣ������Ʒ��Ϣ��buff����
#define MIN_COUNTRYCHANNEL_LEVEL 10   // ����Ƶ���ķ�����͵ȼ� 
#define MAX_CHATUSER_NUM	30		  // ���������ݵ��������

typedef enum 
{
	CHAT_SUCCESS = 1,                 // ������Ϣ�ɹ�
	CHAT_HIGH_FREQUENCY,		      // ����Ƶ�ʹ���
	CHAT_MSGTIME_FAT,				  // һ�仰�ظ����ʹ������࣬
	CHATDES_UNACHEIEVE,				  // ������Ϣʧ��
	CHAT_NOTONOUGHPROP,               // ���߲�����ǧ�ﴫ����ʨ�Ӻ�����Žǣ����ҺŽǣ�
	CHAT_STARTAUTOCHAT,               // ��ʼ�Զ�����
	CHAT_STOPSAUTOCHAT,               // ֹͣ�Զ�����
	CHAT_MODIFYAUTOCHATOK,            // �޸��Զ�������Ϣ���ݳɹ�
	CHAT_WORLDCHANELLEVELLOW,         // ����Ƶ�����Եȼ�����
	CHAT_SENDAUTOCHAT,                // ����һ���Զ�����
	CHAT_CANSENDBUGLEMESS,            // ֪ͨ�ͻ����Ѿ��������������������Դ�����Ƶ���������
	CHAT_DESPLAYERINBLACK,            // ���﷢�Ͷ����ں�������
	CHAT_FORBIDDEN,	

} CHAT_RES2CLIENT;

enum CHAT_CHANNEL
{
	CHANNEL_ERR		=	   ~0,						//����
	CHANNEL_VOID	=		0,						//��Ƶ��
	CHANNEL_COMMON	=	   ( 1 << 0 ),				//��ͨ
	CHANNEL_WORLD	=	   ( 1 << 1 ),				//���� ����Ҫ����Žǵ���
	CHANNEL_P2P		=	   ( 1 << 2 ),				//˽��
	CHANNEL_CORPS	=	   ( 1 << 3 ),				//����
	CHANNEL_FAMILY	=	   ( 1 << 4 ),				//����
	CHANNEL_TEAM	=	   ( 1 << 5 ),				//���
	CHANNEL_COUNTRY	=	   ( 1 << 6 ),				//����
	CHANNEL_GM		=	   ( 1 << 7 ),				//GM
	CHANNEL_ECONOMY =	   ( 1 << 8 ),				//����
	CHANNEL_BEGTEAM =	   ( 1 << 9 ),				//�Ŷ�
	CHANNEL_ALLIED	=	   ( 1 << 10 ),			    //�˹�
	CHANNEL_BUGLE   =      ( 1 << 11 ),             //����Ƶ�����ԣ���Ҫǧ�ﴫ������
    CHANNEL_OTHERCOUNTRY=  ( 1 << 12 ),             //����Ƶ�����ԣ���Ҫ���ҺŽǵ���
	CHANNEL_AUTOMSG =      ( 1 << 13 ),             //�Զ���������Ҫʨ�Ӻ����
	CHANNEL_ALL     =      ( 1 << 14 ),				// ����Ƶ�����ԣ���������
	CHANNEL_SYS		=	   ( 1 << 15 ),				// ϵͳƵ��������ϵͳ������
	CHANNEL_WAR		=      ( 1 << 16 ),				// ս��Ƶ��
	CHANNEL_CURRENT	=	   ( 1 << 17 ),				// ��ǰƵ��	
	CHANNEL_BATTLE	=	   ( 1 << 21 ),				// ս��Ƶ��	
	CHANNEL_END		=      ( 1 << 22 ),				// Ƶ������
};
// ********************************************************************** //
// ���δʼ����
// ********************************************************************** //
enum CheckResult 
{
	HAS_DIRTYWORD     = 0,                         // û�зǷ���
	HAS_NO_DIRTYWORD  = 1                          // ���зǷ���
};

#define CHAT_IN_FORBIDDENCHANNEL(  mForbiddenChannel, vChannel )	( ( ( mForbiddenChannel ) & ( vChannel ) ) != 0 )

enum ETIPS_TYPE
{
	TPYE_OFFICE	=	1,
	TPYE_TITLE	=	2,		
};
