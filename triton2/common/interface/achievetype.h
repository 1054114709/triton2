#pragma once
/*
 *	�ɾ������ļ�
 */

#define MAX_PARAM			10		// �ɾ�������������
#define MAX_ACHIEVE_NUM		300		// �ɾ���������

#define PALYER_ACHIEVE_TLV_BUFFER 1024 * 10

#define INVALID_ARRAY(X) ( ( X < 1 ? true : false ) )
#define ACHIEVE_FINISH	1

// �ɾ�����
enum ACHIEVEMENT_TYPE
{
	emAchieveSpcLevel				= 1,		// ����ȼ�
	emAchieveTalentLevel			= 2,		// �컯�ȼ�(c)
	emAchieveMeltingEquip			= 3,		//����¯
	emAchieveSpcRankTitle			= 4,		//���а�ƺ�
	emAchieveSpcTitleNum			= 5,		//�ƺ�����
	emAchieveOpenPillNum			= 6,		//�����ڵ�����
	emAchievePacketGridNum			= 7,		//������������
	emAchieveUseGoldBugle			= 8,		//ʹ�ý����ȵ���
	emAchieveCompleteLuckTask		= 9,		//�����Ե����
	emAchieveCreateFamily			= 10,		//��������
	emAchieveJoinFamily				= 11,		//�������
	emAchieveAddFriend				= 12,		//��Ӻ���
	emAchieveJoinCorps				= 13,		//�������
	emAchieveCreateCorps			= 14,		//��������
	emAchieveDoubleExp				= 15,		//��˫
	emAchieveObtainObjID			= 16,		//���ָ��ID��Ʒ
	emAchieveObtainObjType			= 17,		//���ָ��������Ʒ
	emAchieveEquipLevel				= 18,		//װ���ȼ�
	emAchieveEquipGrade				= 19,		//װ��Ʒ��
	emAchieveEquipInsertRuneNum		= 20,		//װ����Ƕ���ĵ�����
	emAchieveEquipInsertJewelNum	= 21,		//װ����Ƕ�ı�ʯ����
	emAchieveCollectCard			= 22,		//�ռ���Ƭ
	emAchieveInsertJewel			= 23,		//��Ƕ��ʯ c
	emAchieveEquipUpg				= 24,		//װ������ c
	emAchieveInsertRune				= 25,		//��Ƕ���� c
	emAchieveMemberContribute		= 26,		//���幱�׶�
	emAchieveCorpsContribute		= 27,		//���Ź��׶�
	emAchieveFamilyRedPaper			= 28,		//ʹ�ü�����
	emAchieveCorpsRedPaper			= 29,		//ʹ�þ��ź��
	emAchieveFamilySuccess			= 30,		//����ս��ʤ
	emAchieveCorpsSuccess			= 31,		//����սʤ��
	emAchieveCorpsTask				= 32,		//��������
	emAchieveJudgeSystemGiveFavorPeopleNum	= 33,	//�Զ����˽��й��øж����� s
	emAchieveJudgeSystemIGiveFavorPeopleNum = 34,	//�����˶��ҽ��й��øж����� s
	emAchieveJudgeSystemIGiveFavorValue		= 35,	// ���ĳ�˶��ҵĺøжȴﵽĳֵs
	emAchieveJudgeSystemIGiveFavorTotal		= 36,	//��õĺøж���ֵs
	emAchieveJudgeSystemGiveFavorValue		= 37,	// ��ĳ�˵ĺøж�s
	emAchieveSuccessTaskNum					= 38,	// �����������
	emAchieveSuccessStorageTaskNum			= 39,	// ��ɻư���������
	emAchieveSuccessDesignateTask			= 40,	// ���ָ������
	emAchieveSuccessDesignateTaskMapID		= 41,	// ���ָ����ͼ����
	emAchieveSuccessStorageTaskMapID		= 42,	// ���ָ����ͼ�ư�����
	emAchieveSuccessMenpaiTaskLoopTime		= 43,	// ���ʦ���������
	emAchieveMineMapTask					= 44,	// ��ɲر�ͼ����
	emAchieveSuccessMainTaskNum				= 45,	// ���������������
	emAchieveSuccessAchieve					= 46,	// ���ָ���ɾ�
	emAchieveMapGroping						= 47,	// ��ͼ̽��
	emAchieveNPCStudyCook					= 48,	// ͨ��NPCѧϰ����䷽
	emAcheiveResearchCookNum				= 49,	// �����䷽����
	emAcheiveResearchCookID					= 50,	// ����ָ���䷽ID
	emAchieveStudyCookNum					= 51,	// ѧϰ�������
	emAchieveCookLevel						= 52,	// ��⿽���
	emAchieveUseItem						= 53,	// ʹ����Ʒ
	emAchieveCookExp						= 54,	// ��⿵�������
	emAchieveStudyPillMakeNum				= 55,	// ѧϰ��������
	emAchievePillMakeLevel					= 56,	// ��������
	emAchieveStudyCollectNum				= 57,	// ѧϰ�ɼ�����
	emAchieveCollectLevel					= 58,	// �ɼ�����
	emAchieveStudyGoldMakeNum				= 59,	// ѧϰ�������
	emAchieveGoldMakeLevel					= 60,	// ������
	emAchieveStudyArtificerNum				= 61,	// ѧϰ�ɽ�����
	emAchieveArtificerLevel					= 62,	// �ɽ�����
	emAchieveFirstLifeSkill					= 63,	// ��һ����ְһ������ְҵ
	emAchieveKillOgreNum					= 64,	// ɱ�ּ���
	emAchieveKillOgreID						= 65,	// ɱ��ָ��ID��
	emAchieveObtainFullSkillMagicWeaponID	= 66,	// ���ָ��ID��ȫ���ܷ���
	emAchieveCleanSkillPointTime			= 67,	// ���ü��ܵ�
	emAchieveCleanPotentialPointTime		= 68,	// ����Ǳ�ܵ�
	emAchieveSkillBuff						= 69,	// ָ��Buff
	emAchieveMapID							= 70,	// ָ����ͼ
	emAchieveUseItemType					= 71,	// ʹ��ָ��������Ʒ
	emAchieveEasyPantaoKillNum				= 72,	// ���������ɱ��
	emAchieveNormalPantaoKillNum			= 73,	// ��ͨ�����ɱ��
	emAchieveHardPantaoKillNum				= 74, 	// ��Ӣ�����ɱ��	
	emAchieveLonggongScore					= 75,	// ������û���
	emAchievePantaoScore					= 76,	// ��һ�û���
	emAchieveDungeonQuest					= 77,	// ����̽��
	emAchievePopularizeLevel				= 78,   // ��Ե�ȼ�
	emAchievePopularizeEducatedNum				= 79,   // ��ʦ��������
	emAchievePopularizeCopperNum				= 80,   // ��ͭ��Ե����
	emAchievePopularizeSilverNum				= 81,   // ������Ե����
	emAchievePopularizeGoldNum				= 82,   // �ƽ���Ե����
	emAchievePopularizeDiamondNum				= 83,   // ��ʯ��Ե����
 	emAchievePopularizeMasterTypeNum			= 84,   // ʦ������
	emAchievePopularizeSlaveTypeNum				= 85,   // ��Ե����
};

// ��������
enum CONDITION_TYPE
{
	emSameKindCnt	= 1,	// ͬ�����
	emDiffKindCnt,			// ��ͬ�����
	emEnumerate,			// �о�
	emTrustReport,			// �ϱ������
	emSpecial,				// ���ر���
	emCountReSet,			// ֱ����������		
};

// ��ϵ����
enum RELATION_TYPE
{
	emRelationOr = 1,	// ��
	emRelationAnd,
};
