//  ����ϵͳ��Ϣ���������ļ�
//  ���ߣ�����  08-10-15
//  �汾��1.0

import "coremessage_pb.hxx";

//  ������ٶ�����/������
option optimize_for = SPEED;

//  ��������Ϣ��ID�����ٴΣ���ֹ�ظ�����
//  friend message��Ϣ��ID��Χ[0x1800 -- 0x1C00)
//  ĩλΪR����·����Ϣ

enum FRIEND_MSG_ID
{
	ID_C2S_FRIEND_INVITE_REQUEST                    = 0x1800 ;	// ������������
	ID_S2C_FRIEND_INVITE_NOTICE_R                   = 0x1A01 ;  // ��������֪ͨ + 0x0200
	ID_C2S_FRIEND_INVITE_OPTION                     = 0x1802 ; 	// ��������ظ�
	ID_S2S_FRIEND_INVITE_RESPONSE_R                 = 0x1A03 ; 	// �������ѻ�Ӧ + 0x0200
	ID_S2C_FRIEND_INVITE_RESPONSE_NOTICE            = 0x1804 ; 	// �������ѻ�Ӧ �����ͻ���
	ID_C2S_FRIEND_DEL_REQUEST                       = 0x1805 ;	// ɾ����������
	ID_S2C_FRIEND_ERRCODE_NOTICE					= 0x1A06 ;  // ������+ 0x0200 (·����Ϣ)
	ID_S2C_FRIEND_CHANGE_FRIEND_NOTICE				= 0x1A07 ;  // ���º���֪ͨ  + 0x0200
	ID_S2C_FRIEND_GETLIST_NOTICE					= 0x1808 ;  // �����ͻ��˵ĺ����б�
	ID_C2S_FRIEND_GETLIST_REQUEST					= 0x1809 ;  // �ͻ��˻�ú�����Ϣ������
	ID_S2C_FRIEND_GROUPNAME_NOTICE					= 0x180B ;  // �����ͻ�������
	ID_S2S_FRIEND_CHANGESTATUS_NOTICE_R				= 0x1A0C ;  // ����״̬�����ı�֪ͨ(��������������) + 0x0200
	ID_C2S_FRIEND_CHANGESTATUS_REQUEST				= 0x180D ;  // �ı�״̬����
	ID_S2C_FRIEND_CHANGESTATUS_NOTICE				= 0x180E ;  // ����״̬�����ı�֪ͨ (�������������ͻ���)

	ID_S2S_FRIEND_ADDFRIEND_NOTICE					= 0x1A0F ;  // ��������������Ӻ��ѳɹ�֪ͨ + 0x0200 (·����Ϣ)
	ID_C2S_FRIEND_CHGGROUPNAME_REQUEST				= 0x1810 ;  // ����޸���������
	ID_C2S_FRIEND_CHGFRIENDGROUP_REQUEST			= 0x1811 ;  // ����ƶ����ѵ��������������
	ID_C2S_FRIEND_SENDMESSAGE_REQUEST				= 0x1812 ;  // ��ҷ�����Ϣ����
	ID_S2C_FRIEND_MESSAGE_NOTICE_R					= 0x1A13 ;  // ����յ���Ϣ��֪ͨ
	ID_C2S_FRIEND_MOVETOBLACK_REQUEST				= 0x1814 ;  // �Ϻ�����
	ID_C2S_FRIEND_ADDBLACK_REQUEST					= 0x1815 ;  // ��Ӻ�����
	ID_S2C_FRIEND_CHGFRIENDGROUP_NOTICE				= 0x1816 ;  // �ƶ�����֪ͨ
	ID_S2C_FRIEND_MOVETOBLACK_NOTICE				= 0x1817 ;  // �ƶ���������֪ͨ
	ID_C2S_FRIEND_LOCKENEMY_REQUEST					= 0x1818 ;  // �����������
	
	ID_C2S_FRIEND_GETFRIENDSSTATE_REQUEST			= 0x1819 ;  // �ͻ�������ˢ�º���״̬
	ID_S2C_FRIEND_GETFRIENDSSTATE_NOTICE			= 0x181A ;  // �ͻ�������ˢ�º���״̬ �ظ�
	ID_C2S_FRIEND_UPDATEENEMY_REQUEST				= 0x181B ;  // �ͻ���������³��

	ID_C2S_FRIEND_ADDFRIENDBYNAME_REQUEST			= 0x181C ;  // �ͻ��˸������ּӺ���

	ID_C2S_REQUEST_CHANGEMASTER						= 0x181D;	// �ͻ���->������ ѡ��ǰ������
	ID_S2C_RESPONSE_CHANGEMASTER					= 0x1820;	// ������->�ͻ��� ѡ��ǰ����Ӧ
	ID_S2C_NOTIFY_CHANGEMASTER						= 0x1821;	// ������->�ͻ��� ѡ��ǰ��֪ͨ

	ID_C2S_REQUEST_GETSLAVE							= 0x1822;	// �ͻ���->������ ��ú��б�
	ID_S2C_RESPONSE_GETSLAVE						= 0x1823;	// ������->�ͻ��� ��ú��б�
	ID_S2C_NOTIFY_SLAVELEVELUP						= 0x1824;	// ������->�ͻ��� ���������
	ID_S2C_NOTIFY_ANSWERCHANGE						= 0x1825;	// �ظ�ǰ��ѡ��

	ID_C2S_REQUEST_QUERYPLAYER						= 0x1826;	// �ͻ���->������ ��ѯ��������
	ID_S2C_RESPONSE_QUERYPLAYER						= 0x1827;
	ID_S2C_NOTIFY_SLAVEONOFF						= 0x1828;	// ������->�ͻ��� ������֪ͨ
	ID_S2C_NOTIFY_SLAVENUM							= 0x1829;	// ������->�ͻ��� �󱲽���֪ͨ
	ID_C2S_REQUEST_REMOVESLAVE						= 0x182A;	// ������->�ͻ��� ȥ��������
	ID_S2C_RESPONSE_REMOVESLAVE						= 0x182B;	
	ID_S2C_NOTIFY_REMOVESLAVE						= 0x182C;
	ID_C2S_REQUEST_REMOVEMASTER						= 0x182D;	// ������->�ͻ��� ȥ��ǰ������
	ID_S2C_RESPONSE_REMOVEMASTER					= 0x182E;	
	ID_S2C_NOTIFY_REMOVEMASTER						= 0x182F;
	ID_C2S_REQUEST_ALTERMASTERPERCENT				= 0x1830;	// ������->�ͻ��� �����ж�����
	ID_S2C_RESPONSE_ALTERMASTERPERCENT				= 0x1831;
	ID_C2S_REQUEST_GETLOWPLAYER						= 0x1832;	// ������->�ͻ��� ��õ͵ȼ����
	ID_S2C_RESPONSE_GETLOWPLAYER					= 0x1833;
	ID_C2S_REQUEST_ANSWERCHANGE						= 0x1834;	// �ͻ���->������ �ظ�ǰ��ѡ��

	ID_S2C_NOTIFY_FRIENDLEVELUP						= 0x1A35;	// ������->�ͻ��� ����������֪ͨ(��10��)(·����Ϣ)	
	ID_C2S_REQUEST_FRIENDBLESS						= 0x1836;	// �ͻ���->������ ����������ף��
	ID_S2C_RESPONSE_FRIENDBLESS						= 0x1837;	// ������->�ͻ��� ����������ף����Ӧ	
	ID_S2S_NOTIFY_FRIENDBLESS						= 0x1A38;	// ������->������ ���ѵ�ף��֪ͨ	
	ID_S2S_NOTIFY_MODIFYINTIMACY					= 0x1839;	// ������->������ ͬ���������ܶ�	
	ID_S2S_NOTIFY_MODIFYLASTTIMEALLONLINE			= 0x183A;	// ������->������ ���ͬʱ����ʱ��	

	ID_C2S_REQUEST_CREATESWORNTEAM					= 0x183B;	// �ͻ���->������ ����������������
	ID_S2C_RESPONSE_CREATESWORNTEAM					= 0x183C;	// ������->�ͻ��� ��������������Ϣ��Ӧ
	ID_C2S_REQUEST_LEAVESWORNTEAM					= 0x183D;	// �ͻ���->������ �뿪��ݵ���Ϣ����
	ID_S2C_RESPONSE_LEAVESWORNTEAM					= 0x183E;	// ������->�ͻ��� �뿪��ݵ���Ϣ��Ӧ
	ID_C2S_REQUEST_KICKSWORNMEMBER					= 0x1840;	// �ͻ���->������ �߳���ݳ�Ա����Ϣ����
	ID_S2C_RESPONSE_KICKSWORNMEMBER					= 0x1841;	// ������->�ͻ��� �߳���ݳ�Ա����Ϣ��Ӧ
	ID_C2S_REQUEST_DISBANDSWORNTEAM					= 0x1842;	// �ͻ���->������ ��ɢ����������Ϣ����
	ID_S2C_RESPONSE_DISBANDSWORNTEAM				= 0x1843;	// ������->�ͻ��� ��ɢ����������Ϣ��Ӧ
	ID_S2C_NOTIFY_SWORNINFO							= 0x1844;	// ������->�ͻ��� ���������Ϣ��֪ͨ
	ID_S2C_NOTIFY_LEAVESWORNTEAM					= 0x1845;	// ������->�ͻ��� �뿪����������Ϣ֪ͨ
	ID_S2C_NOTIFY_KICKSWORNMEMBER					= 0x1846;	// ������->�ͻ��� ���˵�֪ͨ
	ID_C2S_REQUEST_CHANGESWORNNAME					= 0x1847;	// �ͻ���->������ ��ݸ���������
	ID_S2C_RESPONSE_CHANGESWORNNAME					= 0x1848;	// ������->�ͻ��� ��ݸ����Ļ�Ӧ
	ID_S2C_NOTIFY_CHANGESWORNNAME					= 0x1849;	// ������->�ͻ��� ��ݸ�����֪ͨ
	ID_S2C_NOTIFY_DISBANDSWORNTEAM					= 0x184A;	// ������->�ͻ��� ��ɢ����������Ϣ֪ͨ
	ID_S2C_NOTIFY_CREATESWORNTEAM					= 0x184B;	// ������->�ͻ��� ������崴���ɹ���֪ͨ��Ϣ
	
	ID_S2C_NOTIFY_LASTCONTACTER						= 0x1A4C;	// ������->�ͻ��� �����һ����ϵ�˸�֪�ͻ���
	ID_S2G_NOTIFY_UPDATELASTCONTACTER				= 0x184D;   // ����->���� �������һ����ϵ����Ϣ
	ID_S2G_NOTIFY_UPLOADCONTACTERLIST				= 0x184E;   // ����->���� �ϴ���ϵ���б���Ϣ
	ID_G2S_NOTIFY_CONTACTERSTATUS					= 0x1850;   // ����->���� �����״̬֪ͨ����ϵ��
	ID_S2C_NOTIFY_CONTACTERSTATUS					= 0x1851;   // ����->�ͻ��� �����״̬֪ͨ����ϵ��
	ID_C2S_REQUEST_REBUILDSWORN						= 0x1852;   // �ͻ���->���� �ؽ���ݵ���Ϣ����
	ID_S2C_RESPONSE_REBUILDSWORN					= 0x1853;   // ����->�ͻ��� �ؽ���ݵ���Ϣ��Ӧ
	ID_S2C_NOTIFY_REBUILDSWORN						= 0x1854;   // ����->�ͻ��� �ؽ���ݵ���Ϣ֪ͨ
};


// *************************************************************************** //
// CMessageInviteFriendRequest �ͻ���->��Ϸ������
//
// ����������Ӻ��� ����ID
// *************************************************************************** //
message CMessageInviteFriendRequest
{
	optional uint32 PlayerID    = 		1;  // ���ӵĺ��ѽ�ɫID
};


// *************************************************************************** //
// CMessageInviteFriendRequestByName �ͻ���->��Ϸ������
//
// �������mInvitedPlayerName����Ϊ����
// *************************************************************************** //
message CMessageInviteFriendRequestByName
{
	optional string InvitedPlayerName    = 		1;  // ���ӵĺ�������
};


// *************************************************************************** //
// CMessageInviteFriendNotice ��Ϸ������->�ͻ���
// 
// ������֪ͨ�Զ���ң�ĳ�˽������Ϊ����, ������Է��Ƿ�ͬ�� (·����Ϣ ·����Ϣ��������)
// *************************************************************************** //
message CMessageInviteFriendNotice
{
	optional CMessageRouter Router			 = 		1;    
	optional uint32			SrcHead			 = 		2; 	// �����ߵ�ͷ��ID
	optional uint32         SrcCharID		 = 		3; 	// �����ߵ�ID����Ҫ�ͻ��˴洢���ID
	optional uint32			SrcMetier		 = 		4; 	// �����ߵ�ְҵID��Ҳ������ID
	optional uint32			SrcLevel		 = 		5; 	// �����ߵĵȼ�
	optional uint32			SrcSex			 = 		6; 	// �����ߵ��Ա�
	optional uint32         DesCharID		 = 		7; 	// �������ߵ�ID
};


// *************************************************************************** //
// CMessageInviteFriendOption �ͻ���->����������
// 
// �Զ�����Ƿ�ͬ����ҵĺ���Ҫ��ظ�
// *************************************************************************** //
message CMessageInviteFriendOptionRequest 
{
	optional uint32 InvitingPlayerID		 = 		1; 	// �����ߵ�ID
	optional uint32 AgreeCode				 = 		2;     // 1=ͬ�⣬0=�ܾ�
};


// *************************************************************************** //
// CMessageInviteFriendResponse ����������->����������
// 
// �Զ�����Ƿ�ͬ����ҵĺ���Ҫ��ظ� �������������ڵķ�����
// *************************************************************************** //
message CMessageInviteFriendResponseMsg
{
	optional CMessageRouter Router			 = 		1;    
	optional uint32 IsDesInMyLst			 = 		2; 	// �������Ѿ����ҵĺ����б�����
	optional uint32 BeInvitingPlayerNation	 = 		3; 	// �������ߵĹ���
	optional uint32 BeInvitingPlayerHead     = 		4; 	// �������ߵ�ͷ��
	optional string BeInvitingPlayerName     = 		5; 	// �������ߵ�����
	optional uint32 BeInvitingPlayerSex	     = 		6; 	// �������ߵ��Ա�
	optional uint32	IsFriendLstFull			 = 		7; 	// �������ߵĺ����б��Ƿ�����
	optional uint32 AgreeCode				 = 		8;     // 1=ͬ�⣬0=�ܾ�
};

// *************************************************************************** //
// CMessageInviteFriendResponseNotice ����������->�ͻ���
// 
// �Զ�����Ƿ�ͬ����ҵĺ���Ҫ��ظ� �����������ڵķ��������������ߵĿͻ���
// *************************************************************************** //
message CMessageInviteFriendResponseNotice
{
	optional string BeInvitingPlayerName		 = 		1; 	// �������ߵ�����
	optional uint32 AgreeCode					 = 		2;     // 1=ͬ�⣬0=�ܾ�
};

// *************************************************************************** //
// CMessageDelFrientRequest �ͻ���->����������
// 
// ɾ�����ѵ�����
// *************************************************************************** //
message CMessageDelFrientRequest
{
	optional uint32 Type		 = 		1; 	// ���ͣ�EDelFriendType
	optional uint32 CharID		 = 		2; 	// Ҫɾ���ĺ��ѵ�char id
};


// *************************************************************************** //
// CMessageFriendErrorNotice ����������->�ͻ���
// 
// ������֪ͨ
// *************************************************************************** //
message CMessageFriendErrorNotice
{
	optional CMessageRouter Router			 = 		1;    
	optional int32 ErrorCode				 = 		2; 	// ������
};


// *************************************************************************** //
// CMessageChangeFriendNotice ����������->�ͻ���
// 
// ���ѷ��������֪ͨ
// *************************************************************************** //
message CMessageChangeFriendNotice
{
	optional CMessageRouter Router	 = 		1;    
	optional string Name			 = 		2; 	// Ҫ�����ĺ��ѵ�����
	optional uint32 NationID		 = 		3; 	// ����
	optional uint32 Sex				 = 		4;     // �Ա�
	optional uint32 ReltoMe			 = 		5;     // ���ҵĹ�ϵ
	optional uint32 OprCode			 = 		6;     // �����룬����鿴��Ķ���(����5��ֵ�ĸ���Ч�ɾ���Ĳ����������뿴���ע��)
	optional uint32 TimeOrder		 = 		7;    // ���ʱ���
	optional uint32 IsLock			 = 		8;    // ����Ƿ����� 1=����
	optional uint32 Status			 = 		9; 	// ״̬��
	optional uint32 CharID			 = 		10; 	// Ҫ�����ĺ��ѵ�ID
	optional uint32 BeKilled		 = 		11;    // ��ɱ�Ĵ���
	optional uint32 Killed			 = 		12;    // ɱ���Ĵ���
	optional uint32 Head			 = 		13; 	// ͷ��ID
	optional uint32 GroupID			 = 		14;     // ����ID  PLAYER_GROUP_COUNT+1�Ǻ�����
	optional uint32 VipFlag			 = 		15;   // ��Ա��־
};

message SingleFriendData
{
	optional uint32 BeKilled		 = 		1;  // ��ɱ�Ĵ���
	optional uint32 Head			 = 		2;   // ͷ��ID
	optional uint32 Status			 = 		3;   // ״̬��
	optional uint32 GroupID			 = 		4;   // ����ID  PLAYER_GROUP_COUNT+1�Ǻ�����
	optional uint32 CharID			 = 		5;   // ���ѵĽ�ɫID  ÿ����Ϣ���MAX_ONCE_FRIENDS��
	optional string Name			 = 		6;   // ����
	optional uint32 NationID		 = 		7; 	// ����
	optional uint32 Relation		 = 		8;   // ���ҵĹ�ϵ
	optional uint32 Sex				 = 		9;   // �Ա�
	optional uint32 IsLock			 = 		10;   // ����Ƿ����� 1=����
	optional uint32 TimeOrder		 = 		11;   // ���ʱ���
	optional uint32 Killed			 = 		12;   // ɱ���Ĵ���
	optional uint32	VipFlag			 =		13;		// ��Ա��־
	optional uint32	IntimacyDegree	 =		14;		// ���ܶ�
};

// *************************************************************************** //
// CMessageFriendListNotice ����������->�ͻ���
// 
// ���������ݿͻ��˴����ĺ��ѵ�char id ���غ��ѵ����ֺ�״̬���Ժ������������Ϣ
// *************************************************************************** //
message CMessageFriendGetListNotice
{
	repeated SingleFriendData	Friends		 = 		1;   // ���к���
	repeated string				GroupName	 = 		2;   // �������϶���PLAYER_GROUP_COUNT��
};


// *************************************************************************** //
// CMessageFriendGetListRequest �ͻ���->����������
// 
// �ͻ���ȡ�ú��ѵ����ֺ�״̬����Ϣ���Ժ������������Ϣ <����>
// *************************************************************************** //
message CMessageFriendGetListRequest
{
};


// *************************************************************************** //
// CMessageFriendGroupNameNotice ����������->�ͻ���
// 
// ��ҽ��볡����ʱ����ͻ��˷�����Ϣ(����)
// *************************************************************************** //
message CMessageFriendGroupNameNotice
{
	repeated uint32 GroupID			 = 		1;   // ��ID���϶���PLAYER_GROUP_COUNT��
	repeated string GroupName		 = 		2;   // �������϶���PLAYER_GROUP_COUNT��
};

// *************************************************************************** //
// CMessageFriendChangeStatusNotice_R ����������->����������
// 
// ����״̬�ı�֪ͨ
// *************************************************************************** //
message CMessageFriendChangeStatusNotice_R
{
	optional CMessageRouter Router	 = 		1;    
	optional uint32		    Status	 = 		2;   // �µ�״̬��
	optional uint32		    Rels	 = 		3;   // ��ϵ
	optional uint32			VipFlag	 =		4;	 // ��Ա��־
};


// *************************************************************************** //
// CMessageFriendChangeStatusNotice ����������->�ͻ���
// 
// ����״̬�ı�֪ͨ
// *************************************************************************** //
message CMessageFriendChangeStatusNotice
{
	optional uint32 CharID			 = 		1;   // ���ѵĽ�ɫID
	optional uint32 Status			 = 		2;   // �µ�״̬��
	optional uint32 Rels			 = 		3;   // ��ϵ
	optional uint32			VipFlag	 =		4;	 // ��Ա��־
};


// *************************************************************************** //
// CMessageFriendChangeStatusRequest �ͻ���->����������
// 
// ��Ҹı�״̬����
// *************************************************************************** //
message CMessageFriendChangeStatusRequest
{
	optional uint32 Status			 = 		1;   // �µ�״̬��
};

// *************************************************************************** //
// CMessageAddFriendNotice ����������->����������
// 
// ��Ӻ��ѳɹ���֪ͨ�����������ڵĳ���������
// *************************************************************************** //
message CMessageAddFriendNotice
{
	optional CMessageRouter Router	 = 		1;    
	optional uint32 CharID			 = 		2; 	// Ҫ�����ĺ��ѵ�ID
	optional uint32 ReltoMe			 = 		3;     // ���ҵĹ�ϵ
	optional uint32 Status			 = 		4; 	// ״̬��
	optional uint32 GroupID			 = 		5;     // ����ID
};

// *************************************************************************** //
// CMessageFriendChgGroupNameRequest �ͻ���->����������
// 
// �޸��������� (��ɺ���Group Notice֪ͨ)
// *************************************************************************** //
message CMessageFriendChgGroupNameRequest
{
	optional string NewName			 = 		1; 	// ������
	optional uint32 GroupID			 = 		2; 	// Ҫ�����ķ���ID ��Χ��1-PLAYER_GROUP_COUNT
};

// *************************************************************************** //
// CMessageFriendChgFriendGroupRequest �ͻ���->����������
// 
// �ƶ����ѷ������� ��ֻ���ƶ����ѣ������ƶ��������ͳ�У�
// *************************************************************************** //
message CMessageFriendChgFriendGroupRequest
{
	optional uint32 CharID				 = 		1; 	// ���ѵĽ�ɫID
	optional uint32 DesGroupID			 = 		2; 	// Ŀ�����ID ��Χ��1-PLAYER_GROUP_COUNT
};

// *************************************************************************** //
// CMessageFriendSendMessageRequest �ͻ���->����������
// 
// ������Ϣ����
// *************************************************************************** //
message CMessageFriendSendMessageRequest
{
	optional string Msg				 = 		1; 	// ��Ϣ���ݣ�� MAX_FRIEND_MSG_LENGTH 
	optional uint32 CharID			 = 		2; 	// Ŀ��char id
	optional uint32 AutoFlag		 = 		3; 	// �Ƿ��Զ�����Ϣ
};


// *************************************************************************** //
// CMessageFriendMessageNotice ����������->�ͻ���
// 
// �յ���Ϣ֪ͨ
// *************************************************************************** //
message CMessageFriendMessageNotice
{
	optional CMessageRouter Router	 = 		1;    
	optional uint32 AutoFlag		 = 		2; 	// �Ƿ��Զ�����Ϣ
	optional uint32 CharID			 = 		3; 	// Դchar id
	optional uint32 Sex				 = 		4; 
	optional string Msg				 = 		5; 	// ��Ϣ���ݣ�� MAX_FRIEND_MSG_LENGTH 
	optional uint32 FaceID			 = 		6; 	// ͷ��
	optional string Name			 = 		7; 
	optional uint32	SendTime		 =		18;	// ����ʱ��
	optional uint32	CampID			 =		19;	// ��ӪID	
};


// *************************************************************************** //
// CMessageFriendMoveToBlackRequest �ͻ���->����������
// 
// �ƶ����ѵ�����������
// *************************************************************************** //
message CMessageFriendMoveToBlackRequest
{
	optional uint32 CharID			 = 		1; 	// Ŀ��char id
};


// *************************************************************************** //
// CMessageFriendAddBlackRequest �ͻ���->����������
// 
// ��Ӻ���������
// *************************************************************************** //
message CMessageFriendAddBlackRequest
{
	optional string  DesName			 = 		1; 	// Ŀ������
};

// *************************************************************************** //
// CMessageFriendChgFriendGroupNotice ����������->�ͻ���
// 
// �ƶ����ѷ���֪ͨ
// *************************************************************************** //
message CMessageFriendChgFriendGroupNotice
{
	optional uint32 CharID				 = 		1; 	// ���ѵĽ�ɫID
	optional uint32 DesGroupID			 = 		2; 	// Ŀ�����ID ��Χ��1-PLAYER_GROUP_COUNT
};

// *************************************************************************** //
// CMessageFriendMoveToBlackNotice ����������->�ͻ���
// 
// �ƶ����ѷֵ�������֪ͨ
// *************************************************************************** //
message CMessageFriendMoveToBlackNotice
{
	optional uint32 CharID				 = 		1; 	// ��ɫID
};


// *************************************************************************** //
// CMessageFriendLockEnemyRequest �ͻ���->����������
// 
// �����������
// *************************************************************************** //
message CMessageFriendLockEnemyRequest
{
	optional uint32 CharID				 = 		1; 	// ��ɫID
	optional uint32 LockType			 =      2;	// ��������
};


// *************************************************************************** //
// CMessageFriendGetFriendsStateRequest �ͻ���->����������
// 
// �ͻ���������Ѻͳ��״̬
// *************************************************************************** //
message CMessageFriendGetFriendsStateRequest
{
};

// *************************************************************************** //
// CMessageFriendGetFriendsStateNotice ����������->�ͻ���
// 
// �ͻ���������Ѻͳ��״̬�ظ�
// *************************************************************************** //
message CMessageFriendGetFriendsStateNotice
{
	repeated uint32	States				 = 		1; 	// ״̬
	repeated uint32 Rels				 = 		2; 	// ��ϵ(���ѣ����)
	repeated uint32 CharIDs				 = 		3; 	// ��ɫID
	repeated uint32	VipFlag				 =		4;	// vip״̬
};


// *************************************************************************** //
// CMessageFriendUpdateEnemyRequest �ͻ���->����������
// 
// ��ұ�ɱ���������������ӳ��
// *************************************************************************** //
message CMessageFriendUpdateEnemyRequest
{
	optional uint32 KillerCharID		 = 		1;   // ˭ɱ��
	optional uint32 DelEnemyCharID		 = 		2;   // ��ɾ���ĳ�е�charID��û�оͲ���
};

// �޸�ǰ���������
message CMessageChangeMasterRequest
{
	optional string MasterName	= 1;
	optional uint32	CharID		= 2;
	optional uint32	NPCEntityID	= 3;
	repeated uint32	MasterID	= 4;
};

message CMessageChangeMasterResponse
{
	optional uint32	Result		= 1;
	optional uint32 MasterID	= 2;
	optional string	MasterName	= 3;
	optional uint32	CharID		= 4;
	optional uint32 Level		= 5;
	optional uint32 Metier		= 6;
};

message CMessageChangeMasterNotify
{
	optional SlaveInfo	Slave		= 1;
	optional uint32		CharID		= 2;
};

// ��ú���Ϣ
message CMessageGetSlaveRequest
{
	repeated uint32	SlaveID		= 1;
	optional uint32	CharID		= 2;
	optional uint32	NPCEntityID	= 3;
	repeated uint32 MasterID	= 4;
};

message SlaveInfo
{
	optional uint32	SlaveID		= 1;
	optional string SlaveName	= 2;
	optional uint32	Level		= 3;
	optional uint32	Metier		= 4;
	optional uint32	Face		= 5;
	optional uint32	Sex			= 6;
	optional uint32	Online		= 7;
};

message CMessageGetSlaveResponse
{
	optional uint32	   Result	= 1;	
	repeated SlaveInfo Slave	= 2;
	optional uint32	   CharID	= 3;
	repeated SlaveInfo Master	= 4;
};

// ������֪ͨ
message CMessageSlaveLevelUpNotify
{
	optional SlaveInfo	Slave	= 1;
	optional uint32		CharID	= 2;
};

message CMessageAnswerChangeNotify
{
	optional SlaveInfo	Slave	= 1;
	optional uint32		CharID	= 2;
};

message CMessageAnswerChangeRequest
{
	optional uint32		Result	= 1;
	optional uint32		CharID	= 2;
	optional uint32		SlaveID	= 3;
	optional uint32		Error	= 4;
};

message CMessageQueryPlayerRequest
{
	repeated uint32		QueryID	= 1;
	optional uint32		CharID	= 2;
};

message CMessageQueryPlayerResponse
{
	repeated SlaveInfo  Info	  = 1;	
	optional uint32		CharID	  = 2;
};

// ǰ���������߻���֪ͨ
message CMessageSlaveOnOffNotify
{
	optional uint32		SrcCharID	 = 1;
	optional string		SrcCharName  = 2;
	optional uint32		Online		 = 3;
	repeated uint32		DesCharID	 = 4;
	optional uint32		Level		 = 5;
};

message CMessageSlaveNumNotify
{
	repeated uint32		SlaveValue	 = 1;
	optional uint32		SlavePoint	 = 2;
	optional uint32		MasterPoint	 = 3;
	optional uint32		SlaveTotal	 = 4;
	optional uint32		MasterTotal	 = 5;
};

message CMessageRemoveSlaveRequest
{
	optional uint32		SlaveID		=  1;
	optional uint32		CharID		=  2;
	optional uint32		NPCEntityID	= 3;
};

message CMessageRemoveSlaveResponse
{
	optional uint32		Result		=	1;
	optional uint32		CharID		=	2;
	optional uint32		SlaveID		=	3;
	optional uint32		Param		=	4;
};

message CMessageRemoveSlaveNotify
{
	optional uint32		CharID		=	1;
	optional uint32		MasterID	=	2;	
};

message CMessageRemoveMasterRequest
{
	optional uint32		MasterID	=  1;
	optional uint32		CharID		=  2;
	optional uint32		NPCEntityID	= 3;
};

message CMessageRemoveMasterResponse
{
	optional uint32		Result		=	1;
	optional uint32		CharID		=	2;
	optional uint32		MasterID	=	3;
};

message CMessageRemoveMasterNotify
{
	optional uint32		CharID		=	1;
	optional uint32		SlaveID		=	2;
	optional uint32		Param		=	3;
};

message CMessageAlterMasterPercentRequest
{
	optional uint32		MasterID	= 1;
	optional uint32		Percent		= 2;
};

message CMessageAlterMasterPercentResponse
{
	optional uint32		Result		= 1;
	optional uint32		MasterID	= 2;
	optional uint32		Percent		= 3;
};

message CMessageGetLowPlayerRequest
{
	optional uint32	NPCEntityID	= 1;
};

message CMessageGetLowPlayerResponse
{
	optional uint32	   Result	= 1;	
	repeated SlaveInfo Player	= 2;	// ���ҽ��
	repeated SlaveInfo Required	= 3;	// Ĭ�Ϸ���һ����
};

// *************************************************************************** //
// CMessageFriendLevelUpNotify
// ����������֪ͨ
// *************************************************************************** //
message CMessageFriendLevelUpNotify
{
	optional CMessageRouter Router	=	1;  // ·����Ϣ
	optional uint32	Level			=	2;	// ���ѵȼ�
	optional string	Name			=	3;	// ��������		
	optional uint32	RoleID			=	4;	// ���ѽ�ɫID
};

// *************************************************************************** //
// CMessageFriendBlessRequest
// ף����������������
// *************************************************************************** //
message CMessageFriendBlessRequest
{
	optional uint32	 RoleID	= 1;	// ���ѽ�ɫID
};


// *************************************************************************** //
// CMessageFriendBlessResponse
// ף�����������Ļ�Ӧ
// *************************************************************************** //
message CMessageFriendBlessResponse
{
	optional uint32	 Errcode	= 1;	// ������
};

// *************************************************************************** //
// CMessageFriendBlessNotify
// ���ѵ�ף��֪ͨ
// *************************************************************************** //
message CMessageFriendBlessNotify
{
	optional CMessageRouter Router		= 1;
	optional string			FriendName	= 2;	// ��������
	optional uint32			Exp			= 3;	// ����ֵ
};

// *************************************************************************** //
// CMessageModifyIntimacyNogify
// ͬ���������ܶ�
// *************************************************************************** //
message CMessageModifyIntimacyNogify
{
	optional CMessageRouter Router			= 1; // 
	optional uint32			ChangeValue		= 2; // �ı����ֵ
	optional uint32			IntimacyDegree  = 3; // �ı������ܶ�
	optional uint32			Type			= 4; // ��������(EM_EntimacyChangeType)
	optional uint32			FriendID		= 5; // ���ܶȸı�ĺ���ID	
	optional uint32			UpdateTime		= 7; // ���ܶ����ӵĸı�ʱ��
	optional uint32			DailyIntimacy	= 8; // ÿ�����ӵ����ܶ���ֵ
};

// *************************************************************************** //
// CMessageModifyLastTimeAllOnLineNotify
// ���ͬʱ����ʱ��
// *************************************************************************** //
message CMessageModifyLastTimeAllOnLineNotify
{
	optional CMessageRouter Router			= 1; // 
	optional uint32			Time			= 2; // ʱ��ֵ
	optional uint32			FriendID		= 3; // ���ѽ�ɫID
};

// *************************************************************************** //
// CMessageCreateSwornTeamRequest
// ����������������
// *************************************************************************** //
message CMessageCreateSwornTeamRequest
{
	optional string	SwornName	=	1;		// ��������
};

// *************************************************************************** //
// CMessageCreateSwornTeamResponse
// �����������Ļ�Ӧ��Ϣ
// *************************************************************************** //
message CMessageCreateSwornTeamResponse
{
	optional uint32	Errcode = 1;	
};

// *************************************************************************** //
// CMessageLeaveSwornTeamRequest
// �뿪��ݵ���Ϣ����
// *************************************************************************** //
message CMessageLeaveSwornTeamRequest
{
	
};

// *************************************************************************** //
// CMessageLeaveSwornTeamResponse
// �뿪��ݵ���Ϣ��Ӧ
// *************************************************************************** //
message CMessageLeaveSwornTeamResponse
{
	optional uint32	Errcode = 1;																				
};

// *************************************************************************** //
// CMessageKickSwornMemberRequest
// �߳���ݳ�Ա����Ϣ����
// *************************************************************************** //
message CMessageKickSwornMemberRequest
{
	optional uint32	RoleID = 1;
};

// *************************************************************************** //
// CMessageKickSwornMemberResponse
// �߳���ݳ�Ա����Ϣ����
// *************************************************************************** //
message CMessageKickSwornMemberResponse
{
	optional uint32	Errcode = 1;	
};

// *************************************************************************** //
// CMessageDisbandSwornTeamRequest
// ��ɢ�������Ϣ����
// *************************************************************************** //
message CMessageDisbandSwornTeamRequest
{

};

// *************************************************************************** //
// CMessageDisbandSwornTeamResponse
// ��ɢ�������Ϣ��Ӧ
// *************************************************************************** //
message CMessageDisbandSwornTeamResponse
{
	optional uint32	Errcode = 1;	
};

// *************************************************************************** //
// CMessageSwornInfoNotify
// ���������Ϣ��֪ͨ
// *************************************************************************** //
message CMsgSwornMember
{
	optional uint32 RoleID		= 1;	
	optional string	RoleName	= 2;	// ��ɫ����
	optional uint32	RolePos		= 3;	// �������
	optional uint32	FaceID		= 4;	// ����
	optional uint32	RoleLevel	= 5;	// ��ɫ�ȼ�
	optional uint32	MetierID	= 6;	// ����ID	
	optional uint32	GenderID	= 7;	// �Ա�
};
message CMessageSwornInfoNotify
{	
	repeated CMsgSwornMember  SwornMember = 1;
	optional string			  SwornName	  = 2;	// �������
	optional uint32			  RoleID	  = 3;	// ��ɫID	
};

// *************************************************************************** //
// CMessageSwornInfoNotify ID_S2C_NOTIFY_CREATESWORNTEAM
// ������崴���ɹ���֪ͨ��Ϣ
// *************************************************************************** //
message CMessageCreateSwornTeamNotify
{
	repeated CMsgSwornMember  SwornMember = 1;
	optional string			  SwornName	  = 2;	// �������
	optional uint32			  MasterID	  = 3;	// �ϴ�Ľ�ɫID
};

// *************************************************************************** //
// CMessageLeaveSwornTeamNotify ID_S2C_NOTIFY_LEAVESWORNTEAM
// �뿪����������Ϣ֪ͨ
// *************************************************************************** //
message CMessageLeaveSwornTeamNotify
{
	optional CMessageRouter Router = 1;
	optional uint32	 RoleID		= 2;	// �뿪�˵Ľ�ɫID
	optional uint32	 MasterID	= 3;	// ����뿪�������ϴ�Ļ������ϴ�Ľ�ɫID	
};

// *************************************************************************** //
// CMessageKickSwornMemberNotify 
// ���˵�֪ͨ
// *************************************************************************** //
message CMessageKickSwornMemberNotify
{
	optional CMessageRouter Router = 1;
	optional uint32			RoleID = 2;
};

// *************************************************************************** //
// CMessageChangeSwornNameRequest
// ��ݸ���������
// *************************************************************************** //
message CMessageChangeSwornNameRequest
{
	optional string	 SwornName = 1;
};

// *************************************************************************** //
// CMessageChangeSwornNameResponse
// ��ݸ����Ļ�Ӧ
// *************************************************************************** //
message CMessageChangeSwornNameResponse
{
	optional uint32	Errcode	=	1;
};

// *************************************************************************** //
// CMessageChangeSwornNameNotify ID_S2C_NOTIFY_CHANGESWORNNAME
// ��ݸ�����֪ͨ
// *************************************************************************** //
message CMessageChangeSwornNameNotify
{
	optional CMessageRouter Router = 1;
	optional string	 SwornName = 2;
};

// *************************************************************************** //
// CMessageDisabanSwornTeamNotify 
// ��ݽ�ɢ��֪ͨ
// *************************************************************************** //
message CMessageDisbandSwornTeamNotify
{
	optional CMessageRouter Router = 1;
	optional uint32	SwornID = 2;
};

// *************************************************************************** //
// CMessageLatestContactChangeStatusNotice ����������->�ͻ���
// 
// �����ϵ��״̬�ı�֪ͨ
// *************************************************************************** //
message CMessageLatestContactChangeStatusNotice
{
	optional uint32 CharID			 = 		1;   // ���ѵĽ�ɫID
	optional uint32 Status			 = 		2;   // �µ�״̬��
	optional uint32	VipFlag			 =		3;	 // ��Ա��־
};

// *************************************************************************** //
// CMessageLastContacterNotice ����������->�ͻ���
// 
// ���һ����ϵ��֪ͨ
// *************************************************************************** //
message CMessageLastContacterNotice
{
	optional CMessageRouter Router		= 		1;  
	optional uint32 CharID				= 		2;   // ��ɫID
	optional uint32 Sex					= 		3; 
	optional uint32 FaceID				= 		4; 	 // ͷ��
	optional string Name				= 		5; 
	optional uint32 NationID			= 		6;   // ������Ӫ
};

// *************************************************************************** //
// CMessageUpdateLastContacterNotice ����������->���ط�����
// 
// ���һ����ϵ��֪ͨ
// *************************************************************************** //
message CMessageUpdateLastContacterNotice
{
	optional uint32 SenderID		= 		1;   // ��Ϣ�����߽�ɫID
	optional uint32 ReceiverID		= 		2;   // ��Ϣ�����߽�ɫID
};

// *************************************************************************** //
// CMessageUploadContacterList ����������->���ط�����
// 
// �ϴ������ϵ���б�
// *************************************************************************** //
message CMessageUploadContacterList
{
	optional uint32 PlayerID		= 1;	// ��ҽ�ɫid
	repeated uint32 ContacterID		= 2;	// ��ϵ�˽�ɫid
};

// *************************************************************************** //
// CMessageUploadContacterList ���ط�����->����������
// 
// ����ҵ�״̬֪ͨ����ϵ��
// *************************************************************************** //
message CMessageContacterStatusNotifyG2S
{
	optional uint32 PlayerID		= 1;	// ��ҽ�ɫid
	optional uint32 PlayerStatus	= 2;	// ���״̬
	optional uint32 ContacterID		= 3;    // ��ϵ��
};

// *************************************************************************** //
// CMessageRebuildSwornRequest
// �ؽ���ݵ���Ϣ����
// *************************************************************************** //
message CMessageRebuildSwornRequest
{

};

// *************************************************************************** //
// CMessageRebuildSwornResponse
// �ؽ���ݵ���Ϣ��Ӧ
// *************************************************************************** //
message CMessageRebuildSwornResponse
{
	optional uint32	 Errcode = 1;	//������
};

// *************************************************************************** //
// CMessageRebuildSwornNotify
// �ؽ���ݵ���Ϣ֪ͨ
// *************************************************************************** //
message CMessageRebuildSwornNotify
{
	repeated CMsgSwornMember  SwornMember = 1;	// �µĳ�Ա�б�
	optional string			  SwornName	  = 2;	// �������
	repeated uint32			  NewMember	  = 3;	// ���˽�ɫID		
};
