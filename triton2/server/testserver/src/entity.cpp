#include "globallogic.h"
#include "entity.h"

//100326 MZYNG ADD-BEGIN

//------------------------------------------------------------
char RBytes::HexChars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
char RBytes::HexValues[128];
RBytes RBytes::_instance;

//============================================================
// <T>����ö��ֵֵ�õ�����������</T>
//
// @param valueö��ֵ
// @return ����������
//============================================================
EGlobalLoginType RGlobalLoginType::Parse(int value){
	switch(value){
		case 0:
			return EGlobalLoginType_Unused;//δʹ��
		case 1:
			return EGlobalLoginType_Normal; //����
		case 2:
			return EGlobalLoginType_New; //�·�
	}
	return EGlobalLoginType_Unused;

}

//============================================================
// <T>����ö��ֵֵ�õ�����������˵��</T>
//
// @param valueö��ֵ
// @return ����������˵��
//============================================================
const char* RGlobalLoginType::ToString(EGlobalLoginType value){
	switch(value){
		case EGlobalLoginType_Unused:
			return "Unused";
		case EGlobalLoginType_Normal:
			return "Normal";
		case EGlobalLoginType_New:
			return "New";
	}
	return "Unused";
}

//============================================================
// <T>����ö��ֵֵ�õ�������״̬����</T>
//
// @param valueö��ֵ
// @return ������״̬����
//============================================================
EGlobalLoginStatusType RGlobalLoginStatusType::Parse(int value){
	switch(value){
		case 0:
			return EGlobalLoginStatusType_System; //ϵͳ
		case 1:
			return EGlobalLoginStatusType_Custom; //����
	}
	return EGlobalLoginStatusType_System;
}

//============================================================
// <T>����ö��ֵֵ�õ�����������˵��</T>
//
// @param valueö��ֵ
// @return ����������˵��
//============================================================
const char* RGlobalLoginStatusType::ToString(EGlobalLoginStatusType value){
	switch(value){
		case EGlobalLoginStatusType_System:
			return "System";
		case EGlobalLoginStatusType_Custom:
			return "Custom";
	}
	return "System";
}

//============================================================
// <T>����ö��ֵֵ�õ�������״̬</T>
//
// @param valueö��ֵ
// @return ������״̬
//============================================================
EServerGatewayStatus RGlobalLoginStatus::Parse(int value){
	switch(value){
		case 0:
			return EServerGatewayStatus_Unknown; // δ֪(K)
		case 1:
			return EServerGatewayStatus_Update;  // ά��(U)
		case 2:
			return EServerGatewayStatus_Full;    // ��(F)
		case 3:
			return EServerGatewayStatus_Rush;    // ��æ(R)
		case 4:
			return EServerGatewayStatus_Busy;    // æµ(B)
		case 5:
			return EServerGatewayStatus_Idle;    // ����(I)
	}
	return EServerGatewayStatus_Unknown;
}

//============================================================
// <T>����ö��ֵֵ�õ�����������˵��</T>
//
// @param valueö��ֵ
// @return ����������˵��
//============================================================
const char* RGlobalLoginStatus::ToString(EServerGatewayStatus value){
	switch(value){
		case EServerGatewayStatus_Unknown:
			return "Unknown";
		case EServerGatewayStatus_Update:
			return "Update";
      case EServerGatewayStatus_Full:
         return "Full";
		case EServerGatewayStatus_Rush:
			return "Rush";
		case EServerGatewayStatus_Busy:
			return "Busy";
		case EServerGatewayStatus_Idle:
			return "Idle";
	}
	return "Unknown";
}

//============================================================
// <T>����һ��CGlobalLoginʵ��</T>
//============================================================
CGlobalLogin::CGlobalLogin(){
	if( CObj::msCreateMode){
		Initialize();
	}else{
		Resume();
	}
}

//============================================================
// <T>�ͷ�CGlobalLoginʵ��</T>
//============================================================
CGlobalLogin::~CGlobalLogin(){
}

//============================================================
// <T>��ʼ��CGlobalLogin����</T>
//============================================================
int CGlobalLogin::Initialize(){
	used = false;
	id = 0;
	memset(host, 0, GS_HOST_MAXLENGTH);
	port = 0;
	type = EGlobalLoginType_Unused;
	statusType = EGlobalLoginStatusType_System;
	status = EServerGatewayStatus_Unknown;
	playerTotal = 0;
	playerCurrent = 0;
   socket.CreateClient();
	return 0;
}

//============================================================
// <T>�ָ�GlobalLogin</T>
//============================================================
int CGlobalLogin::Resume(){
   socket.CreateClient();
	return 0;
}

//============================================================
// <T>����ö��ֵֵ�õ�����������˵��</T>
//
// @param valueö��ֵ
// @return ����������˵��
//============================================================
EServerGatewayStatus CGlobalLogin::GetStatus(){
	if(EGlobalLoginStatusType_System == statusType){
		if(playerCurrent < PLAYERS_AS_IDDLE){
			status = EServerGatewayStatus_Idle;
		}else if(playerCurrent < PLAYERS_AS_BUSY){
			status = EServerGatewayStatus_Busy;
		}else if(playerCurrent < PLAYERS_AS_RUSH){
			status = EServerGatewayStatus_Rush;
		}else{
			status = EServerGatewayStatus_Full;
		}
	}
	return status;
}

//============================================================
// <T>����ȫ���û���Ϣʵ��</T>
//============================================================
CGlobalPlayer::CGlobalPlayer(){
	if( CObj::msCreateMode){
		Initialize();
	}else{
		Resume();
	}
}

//============================================================
// <T>�ͷ�ȫ���û���Ϣʵ��</T>
//============================================================
CGlobalPlayer::~CGlobalPlayer(){

}

//============================================================
// <T>��ʼ��ȫ���û���Ϣ</T>
//============================================================
int CGlobalPlayer::Initialize(){
	used = false;
	accountId = 0;
	memset(passport, 0, GS_PASSPORT_MAXLENGTH);
	memset(password, 0, GS_PASSWORD_MAXLENGTH);
	token = 0;
	tokenTimeout = 0;
	memset(&gates[0], 0, sizeof(SGlobalPlayerGateInfo) * GS_LOGIN_MAXCOUNT);
	lastActived  = 0;
	return 0;
}

//============================================================
// <T>�ָ�ȫ���û���Ϣ</T>
//============================================================
int CGlobalPlayer::Resume(){
	return 0;
}

//============================================================
// <T>ͨ��������ID�����ҽ�ɫ����</T>
//
// @param serverId������ID
// @return ��ɫ����
//============================================================
int CGlobalPlayer::GetRoleCountByServerId(int serverId){
	for(int i = 0; i < gateCount; i++){
		if(gates[i].loginId == serverId){
			return gates[i].roleCount;
		}
	}
	return 0;
}

//============================================================
// <T>����ĳ��������ҽ�ɫ��</T>
//
// @param serverId������ID��nRoles��ɫ����
// @return �Ƿ����˶�ӦserverId�ĵ�·�������ϵĽ�ɫ��
//============================================================
bool CGlobalPlayer::SetRoleCountByServerId(int serverId, int nRoles){
	for(int i = 0; i < gateCount; i++){
		if(gates[i].loginId == serverId){
			if(gates[i].roleCount == nRoles){
				return false;
			}
			gates[i].roleCount = nRoles;
			return true;
		}
	}
	gates[gateCount].loginId = serverId;
	gates[gateCount].roleCount = nRoles;
	++gateCount;
	return true;
}

//============================================================
// <T>����RBytesʵ��</T>
//============================================================
RBytes::RBytes(){
	for(int n='0'; n<= '9'; n++){
		HexValues[n] = n - '0';
	}
	for(int n='A'; n<= 'F'; n++){
		HexValues[n] = n - 'A' + 10;
	}
}

//============================================================
// <T>���ַ�����ʽ���ɶ�Ӧ����</T>
// @return  ��Ӧ����
//============================================================
char* RBytes::FromBytes(char* pValues, int count, char* pBuffer, int length){
	char* pPtr = pBuffer;
	while(--count >= 0){
		char ch = *pValues++;
		char cl = *pValues++;
		*pPtr++ = (HexValues[(int)ch] << 4) | HexValues[(int)cl];
	}
	*pPtr = 0;
	return pBuffer;
}

//============================================================
// <T>������ת����Ϊ�ַ���</T>
// @return �ַ���ָ��
//============================================================
char* RBytes::ToChars(char* pValues, int count, char* pBuffer, int length){
	char* pPtr = pBuffer;
	while(--count >= 0){
		char value = *pValues++;
		*pPtr++ = HexChars[value >> 4];
		*pPtr++ = HexChars[value & 0x0F];
	}
	*pPtr = 0;
	return pBuffer;
}

//100326 MZYNG ADD-END