#include "skill.h"
#include "entity.h"

int	CSkillObject::mCommonCDTimerID  = 0;

int CSkillObject::Initialize( )
{
	mSkillID = 0;
	mSkillLevel = 0;
	mCooldown = 0;
	mIncLevel = 0;

	mReduceCoolFix = 0;
	mDeathRateFix = 0;
	mDeathValueFix = 0;

	mCDTimerID = INVALID_OBJ_ID;
	mOriginalCooldown = 0;

	ClearContiunePara();
	return 0;
}


// �õ����ܹ�������
unsigned int CSkillObject::GetAttackDistance()
{
	CTemplateSkill* tpSkillTpl = (CTemplateSkill*) CDataStatic::SearchSkill( mSkillID, mSkillLevel );
	LK_ASSERT ( tpSkillTpl != NULL, return 0 );

	// ����Զ
	const unsigned int cunLimited = (unsigned int)(-1);

	switch( tpSkillTpl->mSkillTemplateType )
	{
	case CTemplateSkill::SKILL_TEMPLATE_TYPE_AUREOLE: // �⻷����
		{
			return cunLimited;
		}
	case CTemplateSkill::SKILL_TEMPLATE_TYPE_NORMAL: // ��ͨ����
		{
			CTemplateNormalSkill* tpNormalSkill = (CTemplateNormalSkill*)tpSkillTpl;
			return tpNormalSkill->mMinDistance;
		}
	case CTemplateSkill::SKILL_TEMPLATE_TYPE_TRIP: // ���弼��
		{
			return cunLimited;
		}
	case CTemplateSkill::SKILL_TEMPLATE_TYPE_SUMMONBEAST: // �ٻ��޼���
		{
			return cunLimited;
		}
	default:
		{
			LOG_ERROR( "pro", "[%s:%d]wrong type %d", __FUNCTION__, __LINE__, tpSkillTpl->mSkillTemplateType );
			return 0;
		}
	}

}

CTemplateSkill::SKILL_TYPE CSkillObject::GetAttackType()
{
	CTemplateSkill* tpSkillTpl = (CTemplateSkill*) CDataStatic::SearchSkill( mSkillID, mSkillLevel );
	LK_ASSERT ( tpSkillTpl != NULL, return CTemplateSkill::SKILLTYPE_ATTACK );

	return tpSkillTpl->mSkillType;
}


bool CSkillObject::IsSingeTargetSkill()
{
	CTemplateSkill* tpSkillTpl = (CTemplateSkill*) CDataStatic::SearchSkill( mSkillID, mSkillLevel );
	if( tpSkillTpl->mSkillTemplateType == CTemplateSkill::SKILL_TEMPLATE_TYPE_NORMAL )
	{
		CTemplateNormalSkill* tpNormalSkill = (CTemplateNormalSkill*) tpSkillTpl;
		// ���ֻ�ܶԵ���ʹ��
		return ( tpNormalSkill->mAttackRange == CTemplateNormalSkill::RANGE_SINGLE );
	}

	return false;
}

// �õ�����ģ��(�������ӵļ��ܵȼ�)
CTemplateSkill* CSkillObject::GetSkillTpl( )
{
	return (CTemplateSkill*) CDataStatic::SearchSkill( mSkillID, mSkillLevel );
}

// �õ�ԭʼ����ģ��(���������ӵļ��ܵȼ�)
CTemplateSkill* CSkillObject::GetOriginalSkillTpl( )
{
	return (CTemplateSkill*) CDataStatic::SearchSkill( mSkillID, mSkillLevel - mIncLevel );
}

// ������Ⱥ������
bool CSkillObject::SkillContinue( )
{
	CTemplateNormalSkill* pNormalSkill = (CTemplateNormalSkill*) GetSkillTpl( );
	LK_ASSERT( pNormalSkill != NULL, return false );

	// ����״̬
	if( mContinuedState != SKILL_STATE_START )
	{
		return false;
	}

	// ���ô���
	if( (int)(mContinuedNum) > pNormalSkill->mContinuedNum )
	{
		return false;
	}

	// �ϴ�����ʱ��
	if( LINEKONG::GetTickCount() - mContinuedLastTime < (unsigned int)pNormalSkill->mContinuedInterval )
	{
		return false;
	}

	// ����ʱ������
	mContinuedLastTime = LINEKONG::GetTickCount();

	// ���ô�������
	if( (int)( ++mContinuedNum ) > pNormalSkill->mContinuedNum )
	{
		ClearContiunePara();
	}


	return true;
}

// �Ƿ��ǳ����Լ���
bool CSkillObject::IsContinueSkill()
{
	CTemplateSkill::SKILL_TYPE tType = GetAttackType();

	return ( tType == CTemplateSkill::SKILLTYPE_CONTINUEDATTACK ) 
		|| (tType == CTemplateSkill::SKILLTYPE_CONTINUEDATTACK) 
		|| (tType == CTemplateSkill::SKILLTYPE_CONTINUEDATTACK);
}

// �ó����Լ��ܿ�ʼ����
void CSkillObject::StartContinueSkill()
{
	// ����һ��ʹ�øü���ʱ����һ��״̬�Ͳ�������ֹ��Ϊ�����Լ�����һ��û���������������µ�״̬���⡣
	ClearContiunePara();
	mContinuedState = SKILL_STATE_START;
}

// �ó����Լ���ֹͣ����
void CSkillObject::StopContinueSkill()
{
	mContinuedState = SKILL_STATE_STOP;
	mContinuedLastTime = time(NULL);		
	mContinuedNum = 0;
}

// ��������Լ��ܶ�̬����
void CSkillObject::ClearContiunePara()
{
	mContinuedState = SKILL_STATE_STOP;			
	mContinuedLastTime = time(NULL);		
	mContinuedNum = 0;			
}

