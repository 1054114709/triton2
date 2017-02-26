import "privilege_pb.hxx";


// ���Զ���
message PBAttrDef
{
	required uint32 	ID		= 1;	// ����ID
	optional string 	Code		= 2;	// ���Դ���
	required uint32		ValueType	= 3;	// ���Ե�����
};

enum EMPrivExecType
{
	EM_PRIV_CALL_DBPROC 		= 1;	// ����DBServer�Ĵ洢����
	EM_PRIV_CALL_LOGPROC 		= 2;	// ����LogServer�Ĵ洢����
	EM_PRIV_REMOTE_HOST_CALL 	= 3;	// ���͵�Զ������
	EM_PRIV_PLALYER_CALL 		= 4;	// ���͵�ָ�������������
};

enum EMFindPlayerMethod
{
	EM_FIND_BY_ACCOUNT_ID		= 1;	// �����ʺ�ID����
	EM_FIND_BY_ACCOUNT_NAME		= 2;	// �����ʺ����Ʋ���
	EM_FIND_BY_ROLE_ID		= 3;	// ���ݽ�ɫID����
	EM_FIND_BY_ROLE_NAME		= 4;	// ���ݽ�ɫ���Ʋ���
};

message PBPrivExec
{
	required EMPrivExecType ExecType	= 1;	// ִ������
	optional string Procedure		= 2; 	// �洢��������
	optional uint32	HostType		= 3;	// ��������
	optional uint32 HostID			= 4;	// ����ID
	optional EMFindPlayerMethod FindMethod	= 5; 	// ����ʲô�����������
	optional uint32 ParamID			= 6;	// ����ֶ���ʲô�ط�
};

// Ȩ�޼���������������� 
message PBPriv
{
	required uint32 	ID		= 1;	// Ȩ��ID 
	optional string 	Code		= 2;	// Ȩ�޴���
	repeated PBAttrDef	Input		= 3;	// ִ����Ҫ���������
	required uint32		Output		= 4;	// Ȩ�ޱ�ִ�з��ص���ϢID, ���ڴ�������Ϣ����Ϊ0
	required PBValue    	Property	= 5;	// Ȩ�ޱ�������
	optional PBPrivExec	Exec		= 6;	// ִ�з���
};

// ����Ȩ������, ����������ʱ��װ��
message CMessageAllPrivilegeNotify 
{
	repeated PBPriv 	Privileges	= 1;	// ȫ��Ȩ��ģ������, PBAttr��Ȩ��ģ�屾�������
};

// ����������֪ͨ
message CMessageServerStartUpNotify
{

};
