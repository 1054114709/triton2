
// ������ٶ�����/������
option optimize_for = SPEED;

// ��Ϣʵ��
enum enMessageFE
{
	FE_TIMER			= 0;	// �ڲ���Ϣ(��ʱ��)
	FE_CLIENT			= 1;	// �ͻ���
	FE_SCENCESERVER		= 2;	// ����������
	FE_LOGINSERVER		= 3;	// ��½������
	FE_INFOSERVER		= 4;	// ��Ϣ������
	FE_GATESERVER		= 5;	// ���ط�����
	FE_DATASERVER		= 6;	// ���ݷ�����
	FE_ROUTERSERVER		= 7;	// ·�ɷ�����
	FE_PROXYSERVER		= 8;	// ���������
	FE_GLOBALSERVER		= 9;	// ȫ�ַ�����
	FE_COUNTRY			= 10;	// ����
	FE_FAMILY			= 11;	// ����
	FE_CORPS			= 12;	// ����
	FE_DUNGEONSERVER	= 13;	// ȫ�ָ���������	
	FE_OTHERGATE		= 14;	// ������������
};

// ��Ϣ����
enum enMessageType
{
	REQUEST		= 0;		// ����
	RESPONSE	= 1;		// �ظ�
	NOTIFY		= 2;		// ֪ͨ
	ACK			= 3;		// Ӧ��
};

// �ͻ����������֮�����Ϣͷ
message CCSHead
{
	optional uint32		Uin				 = 		1; 
	optional uint32		DialogID		 = 		2;  // ��������ͻ��˵ĻỰID
};


// ��Ϣͷ( server -> client �Ŀ���ֻ��messageid, ��client -> server ����Ҫ��ȫ )
message CMessageHead
{
	optional uint32 DstFE		 = 		1;  // ��ϢĿ��ʵ��
	optional uint32 MsgSeq		 = 		2;  // ��Ϣ���к�
	optional uint32 SrcFE		 = 		3;  // ��ϢԴʵ��
	optional uint32 MessageID	 = 		4;  // ��ϢID
	optional uint32 SrcID		 = 		5;  // ��ϢԴID
	optional uint32 DstID		 = 		6;  // ��ϢĿ��ID	
};

// ��Ϣ
message CMessage
{
	required CMessageHead	MsgHead  = 		1; 				// ��Ϣͷ
	optional fixed32		MsgPara  = 		2; 	// ��Ϣ��( ָ�� 4bytes )
};


/*
˵����Ϊ�˱�֤��������ģ���һʱ�������Ӧ��Ϣ���ر�Ϊ��Ϣ���зֶΡ�##

��ϢID��unsigned short���ͣ�ռ2 bytes. 16 bits.
��1bit��ʾ�ͻ������������Ϣ,���Ƿ���������Ϣ��( 0 : client - server  1 : server - server )
��2~6bits��ʾģ��(���Ա�ʾ32��ģ��),
��7bit��ʾ�Ƿ���·����Ϣ( 1 yes/ 0 no )
��9bits��ʾID(���Ա�ʾ512��ID)
*/

/* ��Ϣ�ֶ�
** ����Ƿ���������Ϣ�ڴ˻�����	+ 0x8000
** �����·����Ϣ�ڴ˻�����		+ 0x0200
*/
enum EmModuleFlagForMessage
{
	MESSAGE_GLOBAL		= 0x0000;	// ���������������ط���������Ϣ��������ֶ�, ����������Ϣ

	MESSAGE_CORE		= 0x0400;	//a. core message		( 0x0400  )	( 0 00001 0 000000000 )
	MESSAGE_PROPERTY	= 0x0800;	//b. pro message		( 0x0800  )	( 0 00010 0 000000000 )
	MESSAGE_MAP			= 0x0C00;	//c. map message		( 0x0C00  )	( 0 00011 0 000000000 )
	MESSAGE_TASK		= 0x1000;	//d. task message		( 0x1000  )	( 0 00100 0 000000000 )  
	MESSAGE_CHAT		= 0x1400;	//e. chat message		( 0x1400  )	( 0 00101 0 000000000 )
	MESSAGE_FRIEND		= 0x1800;	//f. friend message		( 0x1800  )	( 0 00110 0 000000000 )
	MESSAGE_TEAM		= 0x1C00;	//g. team message		( 0x1C00  )	( 0 00111 0 000000000 )
	MESSAGE_MAIL		= 0x2000;	//h. mail message		( 0x2000  )	( 0 01000 0 000000000 )
	MESSAGE_TRADE		= 0x2400;	//i. trade message		( 0x2400  )	( 0 01001 0 000000000 )
	MESSAGE_STALL		= 0x2800;	//j. stall message 		( 0x2800  )	( 0 01010 0 000000000 )
	MESSAGE_REPETION	= 0x2C00;	//k. repetion message	( 0x2C00  ) ( 0 01011 0 000000000 )
	MESSAGE_ACTIVITY	= 0x3000;	//l. activity message   ( 0x3000  ) ( 0 01100 0 000000000 )
	MESSAGE_FAMILY		= 0x3400;	//m. family message   	( 0x3400  ) ( 0 01101 0 000000000 )
	MESSAGE_CORPS		= 0x3800;	//n. corps  message   	( 0x3800  ) ( 0 01110 0 000000000 )
	MESSAGE_RANK		= 0x3C00;	//o. rank message     	( 0x3C00  )	( 0 01111 0 000000000 )
	MESSAGE_GM			= 0x4000;	//p. gm message			( 0x4000  )	( 0 10000 0 000000000 )
	MESSAGE_LOG			= 0x4400;	//q. log message		( 0x4400  )	( 0 10001 0 000000000 )
	MESSAGE_IB			= 0x4800;	//r. ib message
	MESSAGE_JUDGE		= 0x4C00;	//s. judge message	
	MESSAGE_ACHIEVE		= 0x5000;	//t. achieve message
	MESSAGE_COUNTRY		= 0x5400;	//u. country message
	MESSAGE_BOURSE		= 0x5800;	//v. bourse message
	MESSAGE_MARRIAGE	= 0x5C00;	//w. marriage message  
	MESSAGE_CAMP		= 0x6000;	//x. camp massage
	MESSAGE_GLOBALDUNGEON=0x6400;	//y. globaldungeon message	
	// ����DB
	MESSAGE_DB			= 0x7C00;	//  db messages
};

