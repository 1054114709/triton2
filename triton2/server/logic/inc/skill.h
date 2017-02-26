#ifndef _SKILL_H_
#define _SKILL_H_

#include "template.h"
#include "servertool.h"

// ********************************************************************** //
// CSkillObject
// ********************************************************************** //
class CSkillObject 
{
private:

	// ��Ҫ���̵ļ�������
	unsigned int	mSkillID;		// ����ID
	unsigned int	mSkillLevel;	// ���ܵȼ�
	int				mCooldown;		// ������ȴʱ��, 0��ʾĿǰ���ܿ���ʹ��
	unsigned int	mIncLevel;		// ���ӵļ��ܵȼ�

	// �����Ƕ�̬���ݣ��������
	enum 
	{
		SKILL_STATE_START,		// ������������
		SKILL_STATE_STOP,		// ����ֹͣ
	};


	char			mContinuedState;	// �����༼��״̬�� ( ���ڴ���ж� )
	char			mContinuedNum;		// �������ô���
	unsigned int	mContinuedLastTime;	// ��һ������ʱ��
	int				mCDTimerID;			// ������ȴ��ʱ��ID
	int				mReduceCoolFix;		// ��ȴʱ�����
	int				mDeathRateFix;		// ����������
	int				mDeathValueFix;		// �����˺�����
	int				mOriginalCooldown;	// ԭʼ��ȴʱ��( ��ģ����룬Ϊ�˽�ʡ��ѯʱ�� )

public:

	static int		mCommonCDTimerID;		// ������ȴ��ʱ��ID


public:
	CSkillObject( unsigned short vSkillID , unsigned short vSkillLevel ) : mSkillID( vSkillID ), mSkillLevel( vSkillLevel ), mCooldown( 0 ),
		mReduceCoolFix( 0 ), mDeathRateFix( 0 ), mDeathValueFix( 0 ), mOriginalCooldown( 0 )
	{
	}

	CSkillObject( )
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		}
		else
		{
			Resume( );
		}
	}
	~CSkillObject( ) {}

	int Initialize( );

	int Resume( )
	{
		return 0;
	}

	// Get & Set SkillID
	inline unsigned int GetSkillID() const { return mSkillID; }
	inline void SetSkillID(unsigned int val) { mSkillID = val; }

	// Get & Set SkillLevel
	inline unsigned int GetSkillLevel() const { return mSkillLevel; }
	inline void SetSkillLevel(unsigned int val) { mSkillLevel = val; }

	// Geet & Set Cooldown
	inline int GetCooldown() const { return mCooldown ; }
	inline void SetCooldown(int val) { mCooldown = val; }

	// Get & Set IncLevel
	inline unsigned int GetIncLevel() const { return mIncLevel; }
	inline void SetIncLevel(unsigned int val) { mIncLevel = val; }

	// Get & Set CDTimer
	inline int GetCDTimer( ) const { return mCDTimerID; }
	inline void SetCDTimer( int nTimer ) { mCDTimerID = nTimer; }

	// Get & Set CommonCDTimer
	static int GetCommonCDTimer( )  {return mCommonCDTimerID;}
	static void SetCommonCDTimer( int nTimer ) { mCommonCDTimerID = nTimer ;}

	// Get & Set ReduceCoolFix
	inline int GetReduceCoolFix( ) const { return mReduceCoolFix; }
	inline void SetReduceCoolFix( int nCoolFix ) { mReduceCoolFix = nCoolFix; }

	// Get & Set DeathRateFix
	inline int GetDeathRateFix( ) const { return mDeathRateFix; }
	inline void SetDeathRateFix( int nDeathRate ) { mDeathRateFix = nDeathRate; }

	// Get & Set DeathValueFix
	inline int GetDeathValueFix( ) const { return mDeathValueFix; }
	inline void SetDeathValueFix( int nDeathValue ) { mDeathValueFix = nDeathValue; }

	// Get & Set OriginalCooldown
	inline int GetOriginalCooldown( ) const { return mOriginalCooldown; }
	inline void SetOriginalCooldown( int nOriCooldown ) { mOriginalCooldown = nOriCooldown; }

	// �õ����ܹ�������
	unsigned int GetAttackDistance();

	// �õ����ܵ���������
	CTemplateSkill::SKILL_TYPE GetAttackType();

	// �Ƿ��ǵ������ü���
	bool IsSingeTargetSkill();

	// �Ƿ��ǳ����Լ���
	bool IsContinueSkill();

	// �õ�����ģ��(�������ӵļ��ܵȼ�)
	CTemplateSkill* GetSkillTpl( );

	// �õ�ԭʼ����ģ��(���������ӵļ��ܵȼ�)
	CTemplateSkill* GetOriginalSkillTpl( );

	// ������Ⱥ������
	bool SkillContinue( );

	// ��������Լ��ܶ�̬����
	void ClearContiunePara();

	// �ó����Լ��ܿ�ʼ����
	void StartContinueSkill();

	// �ó����Լ���ֹͣ����
	void StopContinueSkill();

public:

	bool IsCoolingDown() { return mCooldown > 0 ; }

	bool IsCommonCDSkill( )
	{
		CTemplateSkill* tpSkillTpl = (CTemplateSkill*) CDataStatic::SearchSkill( mSkillID, mSkillLevel );
		if( tpSkillTpl == NULL )
		{
			return NULL;
		}
		// �ܹ�����ȴӰ��
		return  ( tpSkillTpl->mAutoCoolingSkill == 0 );
	}
};



#endif // _SKILL_H_