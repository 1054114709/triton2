//-------------------------------------------------------------------------
// weakprotecter.h
//-------------------------------------------------------------------------
#pragma  once


#define UI_LevelScore(x)	((x) / 10)
#define UI_HonerScore(x)	((x) / 1000)
#define GET_TotalScore(level, honer)	(UI_LevelScore(level) + UI_HonerScore(honer))
class CMessage;

class CWeakProtecter
{

public:
	CWeakProtecter();
	~CWeakProtecter();
public:
	enum EWP_STATUS
	{
		EWP_Normal = 0,
		EWP_Waiting,
		EWP_Max
	};
	// ����������Ӫ�б�
	void OnMessageCampWeakListReq(int nServerID, CMessage* pMessage);
	
	// �������ֵ
	void OnMessageCampAddHonerScore(int nServerID, CMessage* pMessage);
	
	// ������Ӫ�б�
	void SendCampWeakList(int nServerID);

	// ���ô洢����ͳ�ƻ�Ծ�û�����
	void StartGetActiveRoleInfo();
	
	// ���ݿⷵ�ش洢����ͳ�ƽ��
	void OnSessionGetActiveRoleInfo(CMessage* pMessage);
public:
	// ���㲢������������Ӫ
	void CalculateCampWeakRank();
	
	// 
	void RefreshWeakInfo();

public:

	int GetWeekLevelByWordID(int nWorldID);

	void OnTimerCheckState();
private:
	int AddHonerScore(int nCampID, int nScore, int nRoleID);
	void JudgeWeakLevel(int nSumTotal, int* nLevelScore, int *nTotalScore, bool IsChange);

	int m_State;
};
