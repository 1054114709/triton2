// ������ٶ�����/������
option optimize_for = SPEED;

enum EM_GMONLINE_MSG_ID
{
	ID_G2C_NOTIFY_PRIVILEGE 	= 0x4000;	// ��������ҷ�����Ȩ�б�
	ID_C2G_REQUEST_PRIVILEGE 	= 0x4001;	// ���������������ʹ��Ȩ
	ID_G2C_RESPONSE_PRIVILEGE 	= 0x4002;	// ��������һظ���Ȩ���

	ID_G2C_RESULTSET_RESPONSE	= 0x4011;	// ��ѯ�Ľ��������
};

// ������Ϣ����
message PBByteMsg
{
	required uint32 ID		= 1;	// PB��ϢID
	optional bytes	Content		= 2;	// PB��Ϣ����
};

// union ����
message PBValue
{
	required uint32 	ValueType	= 1;	// ����ID
	optional uint32 	UInt32Value	= 2;
	optional uint64 	UInt64Value	= 3;
	optional int32  	Int32Value  	= 4;
	optional int64  	Int64Value  	= 5;
	optional float  	FloatValue	= 6;
	optional double 	DoubleValue	= 7;
	optional string 	StringValue 	= 8;
	optional PBByteMsg 	MsgValue	= 9;	 
};

// ����ȡֵ
message PBAttrValue
{
	required uint32 	ID		= 1;	// ����ID
	required PBValue	Value		= 2;	// ����ȡֵ
};

// �û�Ȩ���б�
message CMessageUserPrivilegeNotify	
{
	required uint32 	UserID		= 1;	// �ʺ�ID
	repeated uint32		Privileges	= 2;	// Ȩ���б�
};

// ִ���������Ϣ 
message CMessageExecPrivilegeRequest
{
	required uint32 	PrivID		= 1;	// Ȩ��ID 
	repeated PBAttrValue    InputParam	= 2;	// ִ����Ҫ�����������ֵ
};

// �����
message CMessageExecPrivilegeResponse
{
	required int32		Error 		= 1;	// ִ������Ľ��
	required uint32 	PrivID		= 2;	// ִ�е�Ȩ��
	optional PBByteMsg 	Proto		= 3;	// ִ�е�����صĽ����
	optional string 	RoleName	= 4;	// �������Ӧ�Ľ�ɫ����
};

// ������ͷ���
message CMessageResultSetResponse
{
	optional uint32	RowCount		= 1[default=0]; // ������
	optional uint32	ColCount		= 2[default=0]; // ������
	repeated bytes	FieldValue		= 3; 		// ��ֵ ( �䳤�������Ϊ RowCount * ColCount )
	repeated uint32	FieldValueLen		= 4; 		// ��ֵ���� ( �䳤�������Ϊ RowCount * ColCount )
};
