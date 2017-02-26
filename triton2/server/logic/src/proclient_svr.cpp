// ********************************************************************** //
// ProClient.cpp
// �������������?��(����,��?��Ŀ?Buff��,����?
// �漿������,��f,��f,��?��,п?f,��f,����,ֿ?����
// Author: Black
// ********************************************************************** //
#include "stdafx.hpp"
#include "proclient_svr.h"
#include "coremessage_pb.hxx.pb.h"
#include "promessage_pb.hxx.pb.h"
#include "sceneobj_manager.h"
#include "scenelogic.h"
#include "westserver.h"
#include "servercore.h"
#include "entity.h"
#include "template.h"
#include "property.h"
#include "entity.h"
#include "pro_define.h"
#include "propertymodule.h"
#include "scenecfg_manager.h"
#include "repetionmodule.h"
#include <llimits.h>
#ifdef LEAK_CHK_DEBUG_NEW
#include "debug_new.h"
#endif


//int CBuffList::sBuffListID=0;


////TODO: ���øýӿ�ǰ�������жϸ����Ƿ�����
//int CItemBox::RemoveItemByID( unsigned int vItemID, unsigned int vNumber /*= 0xFFFF*/, int vType )
//{
//	CItemBoxToolkit tBoxToolkit(this);
//	
//	int nWantRemveNum = vNumber;
//	int nRemovedNum = 0;
//
//	for ( unsigned short i = 0; i < mReleaseIndex; i ++ )
//	{
//		nRemovedNum = tBoxToolkit.RemoveItem( i, vItemID, vNumber, vType );
//		if( vNumber != (unsigned int)(-1) )
//		{
//			vNumber -= nRemovedNum;
//			if( vNumber == 0 )
//			{
//				ResetPair( vItemID, -nWantRemveNum);
//				return ERROR_REMOVEITEM_SUCCESS;
//			}
//		}
//	}
//	
//	// ��������
//	for ( int i = 0; i < mKitBagIndex; ++i )
//	{
//		int tBeginIndex = 0;
//		int tEndIndex	= 0;
//		int tRet = GetKitBagIndexRange( BAGTYPE_KITBAG, i, tBeginIndex, tEndIndex );
//		if ( tRet != SUCCESS )
//		{
//			continue;
//		}
//		for ( int j = tBeginIndex; j <= tEndIndex; ++j )
//		{
//			nRemovedNum = tBoxToolkit.RemoveItem( j, vItemID, vNumber, vType );
//			if( vNumber != (unsigned int)(-1) )
//			{
//				vNumber -= nRemovedNum;
//				if( vNumber == 0 )
//				{
//					ResetPair( vItemID, -nWantRemveNum);
//					return ERROR_REMOVEITEM_SUCCESS;
//				}
//			}
//		}
//	}
//
//	ResetPair( vItemID, -nWantRemveNum);
//
//	return ERROR_REMOVEITEM_SUCCESS;
//}

// �õ���ս��״̬��HP�ָ��ٶ�
unsigned int CPropertyFormula::GetNormalHPRSpeed( CPropertyCharacter* pProperty )
{
	CPropertyValue tValue;
	if ( pProperty->GetEntityType( ) == ENTITYTYPE_PLAYER )
	{
		CPropertyPlayer* tpProPlayer = ( CPropertyPlayer* )pProperty;
		int tFixValue = tpProPlayer->GetEquipment( )->GetFixNumber( CTemplateProperty::PROPERTYINC_HPRSPEEDFIX )
						+ tpProPlayer->GetEquipment( )->GetSuitInc( CTemplateProperty::PROPERTYINC_HPRSPEEDFIX );	// �õ�װ���̶�ֵ����
		int tPerValue = tpProPlayer->GetEquipment( )->GetPerNumber( CTemplateProperty::PROPERTYINC_HPRSPEEDPER )
						+ tpProPlayer->GetEquipment( )->GetSuitPer( CTemplateProperty::PROPERTYINC_HPRSPEEDPER );	// �õ�װ���ٷֱ�����
		
		CBuffList *tpBuff = tpProPlayer->GetBuffList( );
		tFixValue += tpBuff->GetFixNumber( CTemplateBuff::BUFFINC_HPRSPEEDFIX );					// �õ�BUFF�̶�ֵ����
		tPerValue += tpBuff->GetPerNumber( CTemplateBuff::BUFFINC_HPRSPEEDPER );					// �õ�BUFF�ٷֱ�����
		
		CSkillList& tpSkill = tpProPlayer->GetSkillList( );
		tFixValue += tpSkill.GetFixNumber( CTemplateSkill::PASSINC_HPRSPEEDFIX );	// �õ����̶ܹ�ֵ����
		tPerValue += tpSkill.GetPerNumber( CTemplateSkill::PASSINC_HPRSPEEDPER );	// �õ����ܰٷֱ�����

		CTemplateMetier* tpMetierTpl = (CTemplateMetier*) CDataStatic::SearchMetier( pProperty->GetPropertyTempID() );
		if ( tpMetierTpl == NULL )
			return tValue;

		tValue.mInitValue	= tpMetierTpl->mNormalHPRSpeed;
		tValue.mDeltaValue	= 0;

	}

	if ( pProperty->GetEntityType( ) == ENTITYTYPE_FUNCNPC || pProperty->GetEntityType( ) == ENTITYTYPE_OGRE 
			|| pProperty->GetEntityType( ) == ENTITYTYPE_PET )
	{
		CEntityNpc* tpEntityNpc = (CEntityNpc*) CSceneLogic::GetSingletonPtr()->GetEntity( pProperty->GetEntityID( ) );
		if ( tpEntityNpc == NULL )
		{
			LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] tpEntity is NULL!\n", __LK_FILE__, __LINE__, __FUNCTION__ );
			return tValue;
		}

		if ( tpEntityNpc->GetEntityType( ) == ENTITYTYPE_OGRE || tpEntityNpc->GetEntityType( ) == ENTITYTYPE_FUNCNPC)
		{
			CTemplateOgre* tpNpcTpl = (CTemplateOgre*) CDataStatic::SearchTpl( pProperty->GetPropertyTempID( ) );
			if ( tpNpcTpl == NULL )
				return tValue;

			CBuffList *tpBuff = pProperty->GetBuffList( );
			int		tFixValue	= tpBuff->GetFixNumber( CTemplateBuff::BUFFINC_HPRSPEEDFIX );			// �õ�BUFF�̶�ֵ����
			int		tPerValue	= tpBuff->GetPerNumber( CTemplateBuff::BUFFINC_HPRSPEEDPER );			// �õ�BUFF�ٷֱ�����

			int		tTotalValue	= ( int )( ( tpNpcTpl->mHPRSpeed + tFixValue ) * ( 1 + tPerValue / SERVER_PERCENT_FLOAT ) );
			int		tInitValue	= tpNpcTpl->mHPRSpeed;
			tTotalValue			= std::max( tTotalValue, 0 );

			tValue.mInitValue	= tInitValue;
			tValue.mDeltaValue	= tTotalValue - tInitValue;
			return tValue;
		}

		if ( tpEntityNpc->GetEntityType( ) == ENTITYTYPE_PET )
		{
			CEntityPet* tpEntityPet = (CEntityPet*) tpEntityNpc;
			if ( tpEntityPet == NULL )
			{
				LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] tpEntityPet is NULL!\n", __LK_FILE__, __LINE__, __FUNCTION__ );
				return tValue;
			}

			if ( 
				tpEntityPet->GetCurLevel( ) != CTemplateSummonBeast::PET_LEVEL_ONE 
				&& tpEntityPet->GetCurLevel( ) != CTemplateSummonBeast::PET_LEVEL_TWO
				&& tpEntityPet->GetCurLevel( ) != CTemplateSummonBeast::PET_LEVEL_THREE
				)
			{
				LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] mCurLevel of tpEntityPet is %d!\n", __LK_FILE__, __LINE__, __FUNCTION__, tpEntityPet->GetCurLevel( ) );
				return tValue;
			}

			CTemplateSummonBeast* tpPetTpl = (CTemplateSummonBeast*) CDataStatic::SearchTpl( pProperty->GetPropertyTempID( ) );
			if ( tpPetTpl == NULL )
			{
				LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] tpPetTpl is NULL!\n", __LK_FILE__, __LINE__, __FUNCTION__ );
				return tValue;
			}

			CBuffList *tpBuff = pProperty->GetBuffList( );
			int		tFixValue	= tpBuff->GetFixNumber( CTemplateBuff::BUFFINC_HPRSPEEDFIX );			// �õ�BUFF�̶�ֵ����
			int		tPerValue	= tpBuff->GetPerNumber( CTemplateBuff::BUFFINC_HPRSPEEDPER );			// �õ�BUFF�ٷֱ�����

			int		tTotalValue	= ( int )( ( tpPetTpl->mPetData[ tpEntityPet->GetCurLevel( ) ].mHPRSpeed + tFixValue ) * ( 1 + tPerValue / SERVER_PERCENT_FLOAT ) );
			int		tInitValue	= tpPetTpl->mPetData[ tpEntityPet->GetCurLevel( ) ].mHPRSpeed;
			tTotalValue			= std::max( tTotalValue, 0 );

			tValue.mInitValue	= tInitValue;
			tValue.mDeltaValue	= tTotalValue - tInitValue;
			return tValue;
		}
	}

	return tValue;
}

// �õ���ս��״̬��MP�ָ��ٶ�
unsigned int CPropertyFormula::GetNormalMPRSpeed( CPropertyCharacter* pProperty )
{
	CPropertyValue tValue;
	if ( pProperty->GetEntityType( ) == ENTITYTYPE_PLAYER )
	{
		CPropertyPlayer* tpProPlayer = ( CPropertyPlayer* )pProperty;

		int tFixValue = tpProPlayer->GetEquipment( )->GetFixNumber( CTemplateProperty::PROPERTYINC_MPRSPEEDFIX )
						+ tpProPlayer->GetEquipment( )->GetSuitInc( CTemplateProperty::PROPERTYINC_MPRSPEEDFIX );// �õ�װ���̶�ֵ����
		int	tPerValue = tpProPlayer->GetEquipment( )->GetPerNumber( CTemplateProperty::PROPERTYINC_MPRSPEEDPER )
						+ tpProPlayer->GetEquipment( )->GetSuitPer( CTemplateProperty::PROPERTYINC_MPRSPEEDPER );	// �õ�װ���ٷֱ�����

		CBuffList *tpBuff = tpProPlayer->GetBuffList( );
		tFixValue += tpBuff->GetFixNumber( CTemplateBuff::BUFFINC_MPRSPEEDFIX );	// �õ�BUFF�̶�ֵ����
		tPerValue += tpBuff->GetFixNumber( CTemplateBuff::BUFFINC_MPRSPEEDPER );	// �õ�BUFF�ٷֱ�����

		CSkillList& tpSkill = tpProPlayer->GetSkillList( );
		tFixValue += tpSkill.GetFixNumber( CTemplateSkill::PASSINC_MPRSPEEDFIX );		// �õ����̶ܹ�ֵ����
		tPerValue += tpSkill.GetPerNumber( CTemplateSkill::PASSINC_MPRSPEEDPER );		// �õ����ܰٷֱ�����

		CTemplateMetier* tpMetierTpl = (CTemplateMetier*) CDataStatic::SearchMetier( pProperty->GetPropertyTempID() );
		if ( tpMetierTpl == NULL )
			return tValue;

		// �õ�������������
		//int tCorrect		= (int)( tpMetierTpl->mMPRSpeedPerSpr * ( int )CPropertyFormula::GetSpr( tpProPlayer ) );
		//int tTotalValue		= (int)( ( tpMetierTpl->mNormalMPRSpeed + tFixValue + tCorrect ) * ( 1 + tPerValue / SERVER_PERCENT_FLOAT ) );
		//int tInitValue		= (int)( tpMetierTpl->mNormalMPRSpeed + tCorrect );

		tValue.mInitValue	= tpMetierTpl->mNormalMPRSpeed;
		tValue.mDeltaValue	= 0;

		//LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] EntityID( %d ) EquipmentFix( %d | %d ) EquipmentPer( %d | %d ) BufferFix( %d ) BufferPer( %d ) SkillFix( %d ) SkillPer( %d ) Correct( %d ) TotalValue( %d ) InitValue( %d )",
		//	__LK_FILE__,
		//	__LINE__,
		//	__FUNCTION__, 
		//	pProperty->GetEntityID(), 
		//	tpProPlayer->mEquipment.GetFixMPRSpeed(), 
		//	tpProPlayer->mEquipment.GetSuitInc( CTemplateProperty::PROPERTYINC_MPRSPEEDFIX ),
		//	tpProPlayer->mEquipment.GetPerMPRSpeed(),
		//	tpProPlayer->mEquipment.GetSuitPer( CTemplateProperty::PROPERTYINC_MPRSPEEDPER ),
		//	tpProPlayer->mBuff.GetFixNumber( CTemplateBuff::BUFFINC_MPRSPEEDFIX ),
		//	tpProPlayer->mBuff.GetPerNumber( CTemplateBuff::BUFFINC_MPRSPEEDPER ),
		//	tpProPlayer->mSkill.GetFixNumber( tpProPlayer, CTemplateSkill::PASSINC_MPRSPEEDFIX ),
		//	tpProPlayer->mSkill.GetPerNumber( tpProPlayer, CTemplateSkill::PASSINC_MPRSPEEDPER ),
		//	tCorrect,
		//	tTotalValue,
		//	tInitValue
		//	);
	}

	if ( pProperty->GetEntityType( ) == ENTITYTYPE_FUNCNPC || pProperty->GetEntityType( ) == ENTITYTYPE_OGRE 
			|| pProperty->GetEntityType( ) == ENTITYTYPE_PET )
	{
		CTemplateOgre* tpNpcTpl = (CTemplateOgre*) CDataStatic::SearchTpl( pProperty->GetPropertyTempID( ) );
		if ( tpNpcTpl == NULL )
			return tValue;

		CBuffList *tpBuff = pProperty->GetBuffList( );
		int		tFixValue	= tpBuff->GetFixNumber( CTemplateBuff::BUFFINC_MPRSPEEDFIX );			// �õ�BUFF�̶�ֵ����
		int		tPerValue	= tpBuff->GetPerNumber( CTemplateBuff::BUFFINC_MPRSPEEDPER );			// �õ�BUFF�ٷֱ�����

		int		tTotalValue	= ( int )( ( tpNpcTpl->mMPRSpeed + tFixValue ) * ( 1 + tPerValue / SERVER_PERCENT_FLOAT ) );
		int		tInitValue	= tpNpcTpl->mMPRSpeed;
		tTotalValue			= std::max( tTotalValue, 0 );

		tValue.mInitValue	= tInitValue;
		tValue.mDeltaValue	= tTotalValue - tInitValue;
	}

	return tValue;
}


// �õ�����������Сֵ
CPropertyValue CPropertyFormula::GetMAttackLower( CPropertyCharacter* pProperty )
{
	return pProperty->GetMAttackMin( );
}

// �õ������������ֵ
CPropertyValue CPropertyFormula::GetMAttackUpper( CPropertyCharacter* pProperty )
{
	return pProperty->GetMAttackMax( );
}

// �õ���������Сֵ
CPropertyValue CPropertyFormula::GetPAttackLower( CPropertyCharacter* pProperty )
{
	return pProperty->GetPAttackMin( );
}

// �õ����������ֵ
CPropertyValue CPropertyFormula::GetPAttackUpper( CPropertyCharacter* pProperty )
{
	return pProperty->GetPAttackMax( );
}

CPropertyValue CPropertyFormula::GetCon( CPropertyPlayer* pProperty )
{
	return pProperty->GetCon();
}

CPropertyValue CPropertyFormula::GetSta( CPropertyPlayer* pProperty )
{
	return pProperty->GetSta( );
}

CPropertyValue CPropertyFormula::GetWis( CPropertyPlayer* pProperty )
{
	return pProperty->GetWis( );
}

CPropertyValue CPropertyFormula::GetSpr( CPropertyPlayer* pProperty )
{
	return pProperty->GetSpr( );
}

CPropertyValue CPropertyFormula::GetStr( CPropertyPlayer* pProperty )
{
	return pProperty->GetStr( );
}

// �õ���������
//CPropertyValue CPropertyFormula::GetMResist( CPropertyCharacter* pProperty )
//{
//	return pProperty->GetMResist( );
//}

// �õ�������
//CPropertyValue CPropertyFormula::GetPResist( CPropertyCharacter* pProperty )
//{
//	return pProperty->GetPResist( );
//}

// �õ���������
int CPropertyFormula::GetPImmunity( int vLevel, CPropertyCharacter* pProperty )
{
	int i = 0;
	int tFixValue = 0;
	int tPerValue = 0;

	CSkillList& tpSkillList = pProperty->GetSkillList( );
	for( i = 0; i < tpSkillList.GetSkillNum(); i++ )
	{
		CSkillObject* pSkillObj = tpSkillList.GetSkillObjectByIndex( i );

		CTemplateSkill* tpSkill = pSkillObj->GetSkillTpl();
		if( tpSkill != NULL )
		{
			if( tpSkill->mSkillFuncID1 == CTemplateSkill::PASSINC_DAMAGELESSFIX )
				tFixValue += tpSkill->mParameter1[ 0 ];
			else if( tpSkill->mSkillFuncID1 == CTemplateSkill::PASSINC_DAMAGELESSPER )
				tPerValue += tpSkill->mParameter1[ 0 ];
            
			if( tpSkill->mSkillFuncID2 == CTemplateSkill::PASSINC_DAMAGELESSFIX )
                tFixValue += tpSkill->mParameter2[ 0 ];
            else if( tpSkill->mSkillFuncID2 == CTemplateSkill::PASSINC_DAMAGELESSPER )
                tPerValue += tpSkill->mParameter2[ 0 ];
            
			if( tpSkill->mSkillFuncID3 == CTemplateSkill::PASSINC_DAMAGELESSFIX )
                tFixValue += tpSkill->mParameter3[ 0 ];
            else if( tpSkill->mSkillFuncID3 == CTemplateSkill::PASSINC_DAMAGELESSPER )
                tPerValue += tpSkill->mParameter3[ 0 ];
            
			if( tpSkill->mSkillFuncID4 == CTemplateSkill::PASSINC_DAMAGELESSFIX )
                tFixValue += tpSkill->mParameter4[ 0 ];
            else if( tpSkill->mSkillFuncID4 == CTemplateSkill::PASSINC_DAMAGELESSPER )
                tPerValue += tpSkill->mParameter4[ 0 ];
		}
	}
	int tPImmunity = 10900 * tFixValue / ( tFixValue + 300 * ( vLevel - pProperty->GetLevel( ) )  + 10000 ) + tPerValue;
	return tPImmunity;
}

// �õ���������
int CPropertyFormula::GetMImmunity( int vLevel, CPropertyCharacter* pProperty )
{
    int i = 0;
    int tFixValue = 0;
    int tPerValue = 0;
   
	CSkillList& tpSkillList = pProperty->GetSkillList( );
    for( i = 0; i < tpSkillList.GetSkillNum(); i++ )
    {
		CSkillObject* pSkillObj = tpSkillList.GetSkillObjectByIndex( i );
        CTemplateSkill* tpSkill = pSkillObj->GetSkillTpl();
        if( tpSkill != NULL )
        {
            if( tpSkill->mSkillFuncID1 == CTemplateSkill::PASSINC_DAMAGELESSFIX )
                tFixValue += tpSkill->mParameter1[ 0 ];
            else if( tpSkill->mSkillFuncID1 == CTemplateSkill::PASSINC_DAMAGELESSPER )
                tPerValue += tpSkill->mParameter1[ 0 ];
            
			if( tpSkill->mSkillFuncID2 == CTemplateSkill::PASSINC_DAMAGELESSFIX )
                tFixValue += tpSkill->mParameter2[ 0 ];
            else if( tpSkill->mSkillFuncID2 == CTemplateSkill::PASSINC_DAMAGELESSPER )
                tPerValue += tpSkill->mParameter2[ 0 ];
            
			if( tpSkill->mSkillFuncID3 == CTemplateSkill::PASSINC_DAMAGELESSFIX )
                tFixValue += tpSkill->mParameter3[ 0 ];
            else if( tpSkill->mSkillFuncID3 == CTemplateSkill::PASSINC_DAMAGELESSPER )
                tPerValue += tpSkill->mParameter3[ 0 ];
            
			if( tpSkill->mSkillFuncID4 == CTemplateSkill::PASSINC_DAMAGELESSFIX )
                tFixValue += tpSkill->mParameter4[ 0 ];
            else if( tpSkill->mSkillFuncID4 == CTemplateSkill::PASSINC_DAMAGELESSPER )
                tPerValue += tpSkill->mParameter4[ 0 ];
        }
    }
	int tMImmunity = 10900 * tFixValue / ( tFixValue + 300 * ( vLevel - pProperty->GetLevel( ) )  + 10000 ) + tPerValue;
    return tMImmunity;
}

// �õ���������
CPropertyValue CPropertyFormula::GetMDefence( CPropertyCharacter* pProperty )
{
	return pProperty->GetMDefence( );
}

// �õ��������
CPropertyValue CPropertyFormula::GetPDefence( CPropertyCharacter* pProperty )
{
	return pProperty->GetPDefence( );
}

// ���㼼�ܿ����˺�
unsigned int CPropertyFormula::GetResAttack( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateSkill* pSkill )
{
	if ( pSkill == NULL || pSrcEntity == NULL || pDesEntity == NULL )
		return 0;

	CPropertyCharacter* pSrcProperty = (CPropertyCharacter*) pSrcEntity->GetProperty();
	CPropertyCharacter* pDesProperty = (CPropertyCharacter*) pDesEntity->GetProperty();

	int tAttValue = pSkill->mResValue + pSrcProperty->GetResAtt( pSkill->mResType );
	int tDefValue = pDesProperty->GetResDef( pSkill->mResType );	

	float tResParam1 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mResparam1 / SERVER_PERCENT_FLOAT;
	float tResParam2 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mResparam2 / SERVER_PERCENT_FLOAT;
	float tResParam3 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mResparam3 / SERVER_PERCENT_FLOAT;
	float tResParam4 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mResparam4 / SERVER_PERCENT_FLOAT;
	float tResParam5 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mResparam5 / SERVER_PERCENT_FLOAT;

	float tRate = tResParam1 * tDefValue / ( tResParam2 * tDefValue + tResParam3 + tResParam4 * pow( pSrcProperty->GetLevel( ), tResParam5 ) );

	return tAttValue * ( (1 - tRate) > 0 ? (1 - tRate) : 0 );
}

// ���㼼�������˺�
unsigned int CPropertyFormula::GetPSkillAttack( 	CEntityCharacter* pSrcEntity,
													CEntityCharacter* pDesEntity,
													CTemplateSkill* pSkill,
													EResultType& rResult
												)
{
	if ( pSkill == NULL || pSrcEntity == NULL || pDesEntity == NULL )
		return 0;

	CPropertyCharacter* pSrcProperty = (CPropertyCharacter*) pSrcEntity->GetProperty();
	CPropertyCharacter* pDesProperty = (CPropertyCharacter*) pDesEntity->GetProperty();

	// ������������
	int tDeathRateFix = 0;
	int tDeathValueFix = 0;
	CSkillObject *pObject = pSrcProperty->GetSkillList( ).GetSkillObjectByID( pSkill->mSkillID );
	if ( pObject != NULL )
	{
		tDeathRateFix = pObject->GetDeathRateFix();
		tDeathValueFix = pObject->GetDeathValueFix();
	}
	int tDeath = (int)GetDeathRate( pSrcProperty, (pSkill->mIsMagicWeaponSkill==1) );

	int		tAttackValue	= ( int )( CPropertyFormula::GetPAttackValue( pSrcProperty, (pSkill->mIsMagicWeaponSkill==1) ) 
								* ( pSkill->mAttackPer / SERVER_PERCENT_FLOAT ) + pSkill->mAttackFix );
	int		tDefence		= GetPDefence( pDesProperty );
	int		tDeathDefence	= GetDeathDefense( pDesProperty );
	int		tDeathValue		= SERVER_PERCENT_INT;
	int		tFinalDamage	= 0; 
	int		tIgnoreDefence	= 0;

	// ��⹥����ҵ�BUFF�Թ�����Ӱ��
	CPropertyModule::GetSingleton().CheckBuffGetSkillAttackSrcEntity( pSrcEntity, pSkill, tDeath, tDeathValue, tIgnoreDefence, CTemplateBuff::BUFFFUNC_IGNOREPDEFENCE );
	tIgnoreDefence = std::min( tIgnoreDefence, SERVER_PERCENT_INT );
	tDefence = tDefence / SERVER_PERCENT_FLOAT * ( SERVER_PERCENT_INT - tIgnoreDefence );

	int tDeathRate = CPropertyFormula::GetDeathRate( pDesProperty->GetLevel( ), tDeath, tDeathDefence ) * SERVER_PERCENT_FLOAT;
	tDeathRate += tDeathRateFix;
	// �����������˺�
	if ( RAND( 10000 ) < tDeathRate )
	{
		rResult	= RESULT_DEATHHIT;
		tDeathValue = std::max( (int)( (int)CPropertyFormula::GetDeathValue( pSrcProperty ) + tDeathValueFix - (int)CPropertyFormula::GetDeathDefense( pDesProperty ) * (int)CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDeathchangeparam ), SERVER_PERCENT_INT );
	}

	int		tAddFixDamage = GetAddFixDamage( pSrcProperty );		// �˺��̶�ֵ�ӳ�
	int		tAddPerDamage = GetAddPerDamage( pSrcProperty );		// �˺��ٷֱȼӳ�
	int		tDecFixDamage = GetDecFixPDamage( pDesProperty );		// �˺��̶�ֵ����
	int		tDecPerDamage = GetDecPerPDamage( pDesProperty );		// �˺��ٷֱȼ���

	// ����ƺż���
	int tTitleDamage = 0;
	if ( pSrcEntity->IsPlayer() )
	{
		tTitleDamage = ((CPropertyPlayer*)pSrcProperty)->mTitleSkill.GetFixNumber( CTemplateSkill::PASSINC_DAMAGEFIX );
		tTitleDamage += ((CPropertyPlayer*)pSrcProperty)->mTalentSkill.GetFixNumber( CTemplateSkill::PASSINC_DAMAGEFIX );
	}
	
	// ��������˺�
	tDecPerDamage = std::max( 0, (tDecPerDamage - ((CPropertyPlayer*)pSrcProperty)->GetBuffList( )->GetPerNumber( CTemplateBuff::BUFFFUNC_IGNOREPIMUPER )) );

	CSkillList& tpSkillList = pSrcProperty->GetSkillList( );
	tFinalDamage = ( int )( std::max( 1, int(tAttackValue - tDefence) )  * ( tDeathValue / SERVER_PERCENT_FLOAT ) *
		( SERVER_PERCENT_FLOAT + tAddPerDamage ) / SERVER_PERCENT_FLOAT + tAddFixDamage + 
			tpSkillList.GetFixNumber( CTemplateSkill::PASSINC_DAMAGEFIX ) + tTitleDamage );
	
	int		tDesBuffFix 	= 0;
	int		tDesBuffPer 	= 0;

	// ��ⱻ������ҵ�BUFF�Թ�����Ӱ��
	CPropertyModule::GetSingleton().CheckBuffGetSkillAttackDesEntity( pDesEntity, pSkill, tDesBuffFix, tDesBuffPer );

	tDecFixDamage -= tDesBuffFix;	// �˺��̶�ֵ����
	tDecPerDamage -= tDesBuffPer;	// �˺��ٷֱȼ���

	unsigned int tDamage = std::max( 1, (int)( tFinalDamage * ( SERVER_PERCENT_FLOAT - tDecPerDamage ) / SERVER_PERCENT_FLOAT - tDecFixDamage ) );
	unsigned int tResDamage = std::max( 0, (int)( GetResAttack( pSrcEntity, pDesEntity, pSkill ) * ( tDeathValue / SERVER_PERCENT_FLOAT ) ) );
	return tDamage + tResDamage;
}

// ���㼼�ܷ����˺�
unsigned int CPropertyFormula::GetMSkillAttack( 	CEntityCharacter* pSrcEntity,
													CEntityCharacter* pDesEntity,
													CTemplateSkill* pSkill, 
													EResultType& rResult
											  )
{
	if ( pSkill == NULL || pSrcEntity == NULL || pDesEntity == NULL )
		return 0;

	CPropertyCharacter* pSrcProperty = (CPropertyCharacter*) pSrcEntity->GetProperty();
	CPropertyCharacter* pDesProperty = (CPropertyCharacter*) pDesEntity->GetProperty();

	// ������������
	int tDeathRateFix = 0;
	int tDeathValueFix = 0;
	CSkillObject *pObject = pSrcProperty->GetSkillList( ).GetSkillObjectByID( pSkill->mSkillID );
	if ( pObject != NULL )
	{
		tDeathRateFix = pObject->GetDeathRateFix();
		tDeathValueFix = pObject->GetDeathValueFix();
	}
	int tDeath = (int)GetDeathRate( pSrcProperty, (pSkill->mIsMagicWeaponSkill==1) );

	int		tAttackValue	= (int)( GetMAttackValue( pSrcProperty, (pSkill->mIsMagicWeaponSkill==1) ) * 
								( pSkill->mAttackPer / SERVER_PERCENT_FLOAT ) + pSkill->mAttackFix );
	int		tDefence		= GetMDefence( pDesProperty );
	int		tDeathDefence	= GetDeathDefense( pDesProperty );
	int		tDeathValue		= SERVER_PERCENT_INT;
	int		tFinalDamage	= 0; 
	int		tIgnoreDefence	= 0;

	// ��⹥����ҵ�BUFF�Թ�����Ӱ��
	CPropertyModule::GetSingleton().CheckBuffGetSkillAttackSrcEntity( pSrcEntity, pSkill, tDeath, tDeathValue, tIgnoreDefence, CTemplateBuff::BUFFFUNC_IGNOREMDEFENCE );
	tIgnoreDefence = std::min( tIgnoreDefence, SERVER_PERCENT_INT );
	tDefence = tDefence / SERVER_PERCENT_FLOAT * ( SERVER_PERCENT_INT - tIgnoreDefence );

	int tDeathRate = CPropertyFormula::GetDeathRate( pDesProperty->GetLevel( ), tDeath, tDeathDefence ) * SERVER_PERCENT_FLOAT;
	tDeathRate += tDeathRateFix;
	// �����������˺�
	if ( ( RAND( 10000 ) ) < tDeathRate )
	{
		rResult	= RESULT_DEATHHIT;
		tDeathValue = std::max( (int)( (int)CPropertyFormula::GetDeathValue( pSrcProperty ) + tDeathValueFix - (int)CPropertyFormula::GetDeathDefense( pDesProperty ) * CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDeathchangeparam ), SERVER_PERCENT_INT );
	}

	int		tAddFixDamage = GetAddFixDamage( pSrcProperty );		// �˺��̶�ֵ�ӳ�
	int		tAddPerDamage = GetAddPerDamage( pSrcProperty );		// �˺��ٷֱȼӳ�
	int		tDecFixDamage = GetDecFixMDamage( pDesProperty );		// �˺��̶�ֵ����
	int		tDecPerDamage = GetDecPerMDamage( pDesProperty );		// �˺��ٷֱȼ���

	// ����ƺż���
	int tTitleDamage = 0;
	if ( pSrcEntity->IsPlayer() )
	{
		tTitleDamage = ((CPropertyPlayer*)pSrcProperty)->mTitleSkill.GetFixNumber( CTemplateSkill::PASSINC_DAMAGEFIX );
		tTitleDamage += ((CPropertyPlayer*)pSrcProperty)->mTalentSkill.GetFixNumber( CTemplateSkill::PASSINC_DAMAGEFIX );
	}

	// ��������˺�
	tDecPerDamage = std::max( 0, (tDecPerDamage - ((CPropertyPlayer*)pSrcProperty)->GetBuffList( )->GetPerNumber( CTemplateBuff::BUFFFUNC_IGNOREMIMUPER )) );

	CSkillList &tpSkillList = pSrcProperty->GetSkillList( );
	tFinalDamage = ( int )( std::max( 1, int(tAttackValue - tDefence) )  * ( tDeathValue / SERVER_PERCENT_FLOAT ) * 
		( SERVER_PERCENT_FLOAT + tAddPerDamage ) / SERVER_PERCENT_FLOAT + tAddFixDamage + 
			tpSkillList.GetFixNumber( CTemplateSkill::PASSINC_DAMAGEFIX ) + tTitleDamage );

	int		tDesBuffFix 	= 0;
	int		tDesBuffPer 	= 0;

	// ��ⱻ������ҵ�BUFF�Թ�����Ӱ��
	CPropertyModule::GetSingleton().CheckBuffGetSkillAttackDesEntity( pDesEntity, pSkill, tDesBuffFix, tDesBuffPer );

	tDecFixDamage -= tDesBuffFix;	// �˺��̶�ֵ����
	tDecPerDamage -= tDesBuffPer;	// �˺��ٷֱȼ���

	unsigned int tDamage = std::max( 1, (int)( tFinalDamage * ( SERVER_PERCENT_FLOAT - tDecPerDamage ) / SERVER_PERCENT_FLOAT - tDecFixDamage ) );
	unsigned int tResDamage = GetResAttack( pSrcEntity, pDesEntity, pSkill ) * ( tDeathValue / SERVER_PERCENT_FLOAT );
	return tDamage + tResDamage;
}

// ������ͨ�������˺�
unsigned int CPropertyFormula::GetPNormalAttack( 	CEntityCharacter* pSrcEntity,
													CEntityCharacter* pDesEntity, 
													EResultType& rResult												)
{
	return 0;
	/*
	if ( pSrcEntity == NULL || pDesEntity == NULL )
		return 0;

	CPropertyCharacter* pSrcProperty = (CPropertyCharacter*) pSrcEntity->GetProperty();
	CPropertyCharacter* pDesProperty = (CPropertyCharacter*) pDesEntity->GetProperty();

	// ��������
	int tNormalHitrate	= pSrcProperty->GetNormalHitRate();
	int tNormalDuck		= GetNormalDuck( pDesProperty );
	int tHitrate		= 0;
	rResult				= RESULT_NORMAL;
	if ( tNormalHitrate == 0 && tNormalDuck == 0 )
		tHitrate		= 99;
	else
	{
		tHitrate		= ( int )( ( tNormalHitrate / ( 0.4f * tNormalDuck + tNormalHitrate ) ) * 100 );
		tHitrate		= std::min( 99, tHitrate );
		tHitrate		= max( 1, tHitrate );
	}
	if ( RAND(100) > tHitrate )
	{
		rResult			= RESULT_NORMALDUCK;
		return 0;
	}

	// ������������
	int tDeathRate = GetDeathRate( pSrcProperty );

	// �����������˺�
	if ( ( RAND( 1000 ) ) < tDeathRate )
		rResult			= RESULT_DEATHHIT;

	int		tAttackValue	= GetPAttackValue( pSrcProperty );
	int		tDefence		= GetPDefence( pDesProperty );
	int		tDeathValue		= (int)( ( int )CPropertyFormula::GetDeathValue( pSrcProperty ) );
	int		tFinalDamage	= 0; 

	// ��⹥����ҵ�BUFF�Թ�����Ӱ��
	CPropertyModule::GetSingleton().CheckBuffGetNormalAttackSrcEntity( pSrcEntity, tDeathRate, tDeathValue );

		if ( rResult == RESULT_DEATHHIT )
		tFinalDamage = ( int )( max( 1, tAttackValue - tDefence ) * tDeathValue / SERVER_PERCENT_FLOAT );
	else
		tFinalDamage = ( int )( max( 1, tAttackValue - tDefence ) );

	int		tAddFixDamage = 0;
	float	tAddPerDamage = 0.0;
	int		tDecFixDamage = 0;
	float	tDecPerDamage = 0.0;

	tAddFixDamage	= GetAddFixDamage( pSrcProperty );							// �˺��̶�ֵ�ӳ�
	tAddPerDamage	= GetAddPerDamage( pSrcProperty ) / SERVER_PERCENT_FLOAT;	// �˺��ٷֱȼӳ�
	tDecFixDamage	= GetDecFixPDamage( pDesProperty );							// �˺��̶�ֵ����	
	tDecPerDamage	= GetDecPerPDamage( pDesProperty ) / SERVER_PERCENT_FLOAT ;	// �˺��ٷֱȼ���		

	// �޸Ĺ��ļ��㹫ʽ
	unsigned int tDamage = max( 1, (int)(( tFinalDamage * ( 1 + tAddPerDamage ) + tAddFixDamage ) * ( 1 - tDecPerDamage ) - tDecFixDamage ) );
	return tDamage;
	*/
}

// ������ͨħ�������˺�
unsigned int CPropertyFormula::GetMNormalAttack(	CEntityCharacter* pSrcEntity,
													CEntityCharacter* pDesEntity, 
													EResultType& rResult
													)
{
	return 0;
	/*
	if ( pSrcEntity == NULL || pDesEntity == NULL )
		return 0;

	CPropertyCharacter* pSrcProperty = (CPropertyCharacter*) pSrcEntity->GetProperty();
	CPropertyCharacter* pDesProperty = (CPropertyCharacter*) pDesEntity->GetProperty();

	// ��������
	int tNormalHitrate	= pSrcProperty->GetNormalHitRate();
	int tNormalDuck		= GetNormalDuck( pDesProperty );
	int tHitrate		= ( int )( ( tNormalHitrate / ( 0.4f * tNormalDuck + tNormalHitrate ) ) * 100 );
	rResult				= RESULT_NORMAL;
	if ( RAND(100) > tHitrate )
	{
		rResult			= RESULT_NORMALDUCK;
		return 0;
	}

	// ������������
	int tDeathRate		= GetDeathRate( pSrcProperty );

	// �����������˺�
	if ( ( RAND( 1000 )  ) < tDeathRate )
		rResult			= RESULT_DEATHHIT;

	int 	tAttackValue	= GetMAttackValue( pSrcProperty );
	int 	tDefence		= GetMDefence( pDesProperty );
	int		tDeathValue		= (int)( ( int )CPropertyFormula::GetDeathValue( pSrcProperty ) );
	int		tFinalDamage	= 0; 

	// ��⹥����ҵ�BUFF�Թ�����Ӱ��
	CPropertyModule::GetSingleton().CheckBuffGetNormalAttackSrcEntity( pSrcEntity, tDeathRate, tDeathValue );

	if ( rResult == RESULT_DEATHHIT )
		tFinalDamage = ( int )( max( 1, tAttackValue - tDefence ) * tDeathValue / SERVER_PERCENT_FLOAT );
	else
		tFinalDamage = ( int )( max( 1, tAttackValue - tDefence ) );

	int		tAddFixDamage = 0;
	float	tAddPerDamage = 0.0;
	int		tDecFixDamage = 0;
	float	tDecPerDamage = 0.0;

	tAddFixDamage	= GetAddFixDamage( pSrcProperty );							// �˺��̶�ֵ�ӳ�
	tAddPerDamage	= GetAddPerDamage( pSrcProperty ) / SERVER_PERCENT_FLOAT;	// �˺��ٷֱȼӳ�
	tDecFixDamage	= GetDecFixPDamage( pDesProperty );							// �˺��̶�ֵ����	
	tDecPerDamage	= GetDecPerPDamage( pDesProperty ) / SERVER_PERCENT_FLOAT;	// �˺��ٷֱȼ���		

	// �޸Ĺ��ļ��㹫ʽ
	unsigned int tDamage = max( 1, (int)(( tFinalDamage * ( 1 + tAddPerDamage ) + tAddFixDamage ) * ( 1 - tDecPerDamage ) - tDecFixDamage ) );
	return tDamage;
	*/
}

// ���ڿ��ܷ���ֵΪ-ֵ���޸ĺ���
// �õ��˺��̶�ֵ�ӳ�( ����������ͷ��� )
int CPropertyFormula::GetAddFixDamage( CPropertyCharacter* pProperty )
{
	return pProperty->GetAddFixDamage( );
}

// �õ��˺��ٷֱȼӳ�( ����������ͷ��� )
int CPropertyFormula::GetAddPerDamage( CPropertyCharacter* pProperty )
{
	return pProperty->GetAddPerDamage( );
}

// �õ������˺��̶�ֵ����
int CPropertyFormula::GetDecFixPDamage( CPropertyCharacter* pProperty )
{
	return pProperty->GetDecFixPDamage( );
}

// �õ������˺��ٷֱȼ���
int CPropertyFormula::GetDecPerPDamage( CPropertyCharacter* pProperty )
{
	return pProperty->GetDecPerPDamage( );
}

// �õ������˺��̶�ֵ����
int CPropertyFormula::GetDecFixMDamage( CPropertyCharacter* pProperty )
{
	return pProperty->GetDecFixMDamage( );
}

// �õ������˺��ٷֱȼ���
int CPropertyFormula::GetDecPerMDamage( CPropertyCharacter* pProperty )
{
	return pProperty->GetDecPerMDamage( );
}

// ��ȡ�˺�͵ȡHP�ٷֱ�
int CPropertyFormula::GetStealHP( CPropertyCharacter* pProperty )
{
	return pProperty->GetStealHP( );
}

// ��ȡ�˺�͵ȡMP�ٷֱ�
int CPropertyFormula::GetStealMP( CPropertyCharacter* pProperty )
{
	return pProperty->GetStealMP( );
}

unsigned int CPropertyFormula::GetPAttackValue( CPropertyCharacter* pProperty, bool bIsMagicWeapon/* = false*/ )
{
	if ( bIsMagicWeapon )
	{
		LK_ASSERT( pProperty->GetEntityType() == ENTITYTYPE_PLAYER, return 0 );
		CPropertyPlayer* tpPro = ( CPropertyPlayer* )pProperty;
		CItemMagicWeapon* tpMW = (CItemMagicWeapon*)tpPro->GetEquipment()->GetItemObjPtr( EQUIPMENT_MAGICWEAPON );
		if ( tpMW == NULL )
			return 0;
		return tpMW->GetAttackValue();
	}

	int tUpper = ( int )GetPAttackUpper( pProperty );
	int tLower = ( int )GetPAttackLower( pProperty );
	if ( tUpper == tLower )
		return tLower;

	return rand( ) % ( tUpper - tLower + 1 ) + tLower;
}

unsigned int CPropertyFormula::GetMAttackValue( CPropertyCharacter* pProperty, bool bIsMagicWeapon/* = false*/ )
{
	if ( bIsMagicWeapon )
	{
		LK_ASSERT( pProperty->GetEntityType() == ENTITYTYPE_PLAYER, return 0 );
		CPropertyPlayer* tpPro = ( CPropertyPlayer* )pProperty;
		CItemMagicWeapon* tpMW = (CItemMagicWeapon*)tpPro->GetEquipment()->GetItemObjPtr( EQUIPMENT_MAGICWEAPON );
		if ( tpMW == NULL )
			return 0;
		return tpMW->GetAttackValue();
	}

	int tUpper = ( int )GetMAttackUpper( pProperty );
	int tLower = ( int )GetMAttackLower( pProperty );
	if ( tUpper == tLower )
		return tLower;

	return rand( ) % ( tUpper - tLower + 1 ) + tLower;
}

// �õ��չ�����ֵ
CPropertyValue CPropertyFormula::GetNormalHitrate( CPropertyCharacter* pProperty )
{
	CPropertyValue tValue;
	if ( pProperty->GetEntityType( ) == ENTITYTYPE_PLAYER )
	{
		CPropertyPlayer* tpProPlayer = ( CPropertyPlayer* )pProperty;
		int tFixValue = 0;
		tFixValue += tpProPlayer->GetEquipment( )->GetFixNumber( CTemplateProperty::PROPERTYINC_NORMALHITRATE )
					+ tpProPlayer->GetEquipment( )->GetSuitInc( CTemplateProperty::PROPERTYINC_NORMALHITRATE );// �õ�װ���̶�ֵ����

		CSkillList& tpSkill = tpProPlayer->GetSkillList( );
		tFixValue += tpSkill.GetFixNumber( CTemplateSkill::PASSINC_NORMALHITRATE );	// �õ����̶ܹ�ֵ����

		CBuffList *tpBuff = tpProPlayer->GetBuffList( );
		tFixValue += tpBuff->GetFixNumber( CTemplateBuff::BUFFINC_NORMALHITRATEFIX );	// �õ�BUFF�̶�ֵ����

		CTemplateMetier* tpMetierTpl = (CTemplateMetier*) CDataStatic::SearchMetier( tpProPlayer->GetPropertyTempID() );
		if ( tpMetierTpl == NULL )
			return tValue;

		// �õ�������������
		int tLevelAmend = (int)( ( tpProPlayer->GetLevel( ) - tpMetierTpl->mInitLevel ) * tpMetierTpl->mDeltaNormalHitrate );

		unsigned int tTotalValue	= tpMetierTpl->mInitNormalHitrate + tLevelAmend + tFixValue;
		unsigned int tInitValue		= tpMetierTpl->mInitNormalHitrate + tLevelAmend;

		tValue.mInitValue	= tInitValue;
		tValue.mDeltaValue	= tTotalValue - tInitValue;

		//LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] EntityID( %d ) EquipmentFix( %d | %d ) BufferFix( %d ) SkillFix( %d ) tLevelAmend( %d ) tTotalValue( %d ) tInitValue( %d )",
		//	__LK_FILE__,
		//	__LINE__,
		//	__FUNCTION__, 
		//	pProperty->GetEntityID(), 
		//	tpProPlayer->mEquipment.GetFixNormalHitrate(), 
		//	tpProPlayer->mEquipment.GetSuitInc( CTemplateProperty::PROPERTYINC_NORMALHITRATE ),
		//	tpProPlayer->mBuff.GetFixNumber( CTemplateBuff::BUFFINC_NORMALHITRATEFIX ),
		//	tpProPlayer->mSkill.GetFixNumber( tpProPlayer, CTemplateSkill::PASSINC_NORMALHITRATE ),
		//	tLevelAmend,
		//	tTotalValue,
		//	tInitValue
		//	);
	}

	else if ( pProperty->GetEntityType( ) == ENTITYTYPE_FUNCNPC || pProperty->GetEntityType( ) == ENTITYTYPE_OGRE 
			|| pProperty->GetEntityType( ) == ENTITYTYPE_PET )
	{
		CTemplateOgre* tpNpcTpl = (CTemplateOgre*) CDataStatic::SearchTpl( pProperty->GetPropertyTempID( ) );
		if ( tpNpcTpl == NULL )
			return tValue;
		int tTplHit = tpNpcTpl->mNormalHitrate;
		CTemplateOgreTran* pTemplateOgreTran = (CTemplateOgreTran*)CDataStatic::SearchTpl( tpNpcTpl->mTranID );
		if ( pTemplateOgreTran != NULL )
		{
			tTplHit = pTemplateOgreTran->mHit[ pProperty->GetLevel( ) ];
		}

		CBuffList *tpBuff = pProperty->GetBuffList( );
		int		tFixValue	= tpBuff->GetFixNumber( CTemplateBuff::BUFFINC_NORMALHITRATEFIX );				// �õ�Buff�̶�ֵ����
		int		tTotalValue	= tTplHit + tFixValue;
		int		tInitValue	= tTplHit;
		tTotalValue			= std::max( tTotalValue, 0 );

		tValue.mInitValue	= tInitValue;
		tValue.mDeltaValue	= tTotalValue - tInitValue;
		return tValue;
	}

	return tValue;
}

// �õ��չ�����ֵ
CPropertyValue CPropertyFormula::GetNormalDuck( CPropertyCharacter* pProperty )
{
	return pProperty->GetNormalDuck( );
}

// �õ���������ֵ( ��Ӱ )
CPropertyValue CPropertyFormula::GetSkillDuck( CPropertyCharacter* pProperty )
{
	return pProperty->GetSkillDuck( );
}

// �õ���������ֵ
CPropertyValue CPropertyFormula::GetIgnoreDuck( CPropertyCharacter* pProperty )
{
	return pProperty->GetIgnoreDuck( );
}

// �õ�����һ����
CPropertyValue CPropertyFormula::GetDeathRate( CPropertyCharacter* pProperty, bool bIsMagicWeapon/* = false*/ )
{
	if ( bIsMagicWeapon )
	{
		CPropertyValue tValue;
		LK_ASSERT( pProperty->GetEntityType() == ENTITYTYPE_PLAYER, return tValue );
		CPropertyPlayer* tpPro = ( CPropertyPlayer* )pProperty;
		CItemMagicWeapon* tpMW = (CItemMagicWeapon*)tpPro->GetEquipment()->GetItemObjPtr( EQUIPMENT_MAGICWEAPON );
		if ( tpMW == NULL )
			return tValue;
		tValue.mInitValue = tpMW->GetDeathRate();
		return tValue;
	}
	return pProperty->GetDeathRate( );
}

// �õ�����һ���˺��ӳ�
CPropertyValue CPropertyFormula::GetDeathValue( CPropertyCharacter* pProperty )
{
	return pProperty->GetDeathValue( ) ;
}

// �õ�����һ������
CPropertyValue CPropertyFormula::GetDeathDefense( CPropertyCharacter* pProperty )
{
	return pProperty->GetDeathDefense( ) ;
}

// �õ�����������
unsigned int CPropertyFormula::GetSkillHitrate( 	unsigned short vSkillID, 
													unsigned short vSkillLevel, 
													CPropertyCharacter* pProperty 
												)
{
	if ( pProperty->GetEntityType( ) == ENTITYTYPE_PLAYER )
	{
		CPropertyPlayer* tpProPlayer = ( CPropertyPlayer* )pProperty;
		// �õ����ܵȼ�
		CTemplateSkill* tpSkillTpl = (CTemplateSkill*) CDataStatic::SearchSkill( vSkillID, vSkillLevel );
		if ( tpSkillTpl == NULL || tpSkillTpl->mSkillType != CTemplateSkill::SKILLTYPE_ATTACK )
			return 0;

		CTemplateNormalSkill* tpNormalSkill = (CTemplateNormalSkill*) tpSkillTpl;

		CBuffList *tpBuff = tpProPlayer->GetBuffList( );
		unsigned int tHitrate = tpNormalSkill->mSkillHitrate + tpBuff->GetFixNumber( CTemplateBuff::BUFFINC_SKILLHITRATEFIX )
			+ tpProPlayer->GetEquipment( )->GetFixNumber( CTemplateProperty::PROPERTYINC_SKILLHITRATE );
		
		//LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] EntityID( %d ) Skill( %d ) EquipmentFix( %d ) BufferFix( %d ) tHitrate( %d )",
		//	__LK_FILE__,
		//	__LINE__,
		//	__FUNCTION__, 
		//	pProperty->GetEntityID(), 
		//	tpNormalSkill->mSkillHitrate, 
		//	tpProPlayer->mBuff.GetFixNumber( CTemplateBuff::BUFFINC_SKILLHITRATEFIX ),
		//	tpProPlayer->mEquipment.GetFixNormalHitrate(),
		//	tHitrate
		//	);
		return tHitrate;
	}
	else
	{
		CPropertyNPC* tpProNpc = ( CPropertyNPC* )pProperty;
		// �õ����ܵȼ�
		CTemplateSkill* tpSkillTpl = (CTemplateSkill*) CDataStatic::SearchSkill( vSkillID, 1 );
		if ( tpSkillTpl == NULL || tpSkillTpl->mSkillType != CTemplateSkill::SKILLTYPE_ATTACK )
		{
			LOG_ERROR("pro", "npc skill id %d not fond ", vSkillID );
			return 0;
		}

		CTemplateNormalSkill* tpNormalSkill = (CTemplateNormalSkill*) tpSkillTpl;

		CBuffList *tpBuff = tpProNpc->GetBuffList( );
		unsigned int tHitrate = tpNormalSkill->mSkillHitrate + tpBuff->GetFixNumber( CTemplateBuff::BUFFINC_SKILLHITRATEFIX );
		return tHitrate;
	}

	return 0;
}

// �õ�HP���ֵ
CPropertyValue CPropertyFormula::GetMaxHP( CPropertyCharacter* pProperty )
{																										
	return pProperty->GetMaxHP( );
}

// �õ�MP���ֵ
CPropertyValue CPropertyFormula::GetMaxMP( CPropertyCharacter* pProperty )
{
	return pProperty->GetMaxMP( );
}

// �������ҿ�˿?
CPropertyValue CPropertyFormula::GetWalkSpeed( CPropertyCharacter *pProperty )
{
	CPropertyValue tValue;
	if( pProperty->GetEntityType( ) == ENTITYTYPE_PLAYER )
	{
		CPropertyPlayer* tpProPlayer = ( CPropertyPlayer* )pProperty;
		CTemplateMetier* tpMetier = (CTemplateMetier*) CDataStatic::SearchMetier( tpProPlayer->GetPropertyTempID() );
		if( tpMetier != NULL )
		{
			tValue.mInitValue = tpMetier->mWalkSpeed;
		}
	}
	else if( pProperty->GetEntityType( ) == ENTITYTYPE_FUNCNPC )
	{
	
	}

	return tValue;
}

// �������ҿ�˿?
CPropertyValue CPropertyFormula::GetRunSpeed( CPropertyCharacter *pProperty )
{
	CPropertyValue tValue;
	if( pProperty->GetEntityType( ) == ENTITYTYPE_PLAYER )
	{
		CPropertyPlayer* tpProPlayer = ( CPropertyPlayer* )pProperty;
		CTemplateMetier* tpMetier = (CTemplateMetier*) CDataStatic::SearchMetier( tpProPlayer->GetPropertyTempID() );
		if( tpMetier != NULL )
		{
			int tPerInCreamValue = tpProPlayer->GetEquipment( )->GetPerNumber( CTemplateProperty::PROPERTYINC_SPEED ) + tpProPlayer->GetEquipment( )->GetSuitPer( CTemplateProperty::PROPERTYINC_SPEED );

			tPerInCreamValue += tpProPlayer->GetStateParam( STATE_INCREAMSPEED ).mParames1;

			tPerInCreamValue += tpProPlayer->GetSkillList().GetPerNumber( CTemplateSkill::PASSINC_SPEED ) + tpProPlayer->mTalentSkill.GetPerNumber( CTemplateSkill::PASSINC_SPEED ) + tpProPlayer->mTitleSkill.GetPerNumber( CTemplateSkill::PASSINC_SPEED );

			//tPerInCreamValue += tpProPlayer->GetHorseSpeedPer();
			
			int	tPerUnCreamValue = tpProPlayer->GetStateParam( STATE_UNCREAMSPEED ).mParames1;

			int	tTempValue = (int)( SERVER_PERCENT_FLOAT + tPerInCreamValue - tPerUnCreamValue );
			if ( tTempValue != 0 )
				tValue.mInitValue = (int)( ( tpMetier->mRunSpeed ) * SERVER_PERCENT_FLOAT / tTempValue );
			else
				tValue.mInitValue = 0;
		}
	}
	else if ( pProperty->GetEntityType( ) == ENTITYTYPE_OGRE 
		|| pProperty->GetEntityType( ) == ENTITYTYPE_FUNCNPC 
		/*|| pProperty->GetEntityType( ) == ENTITYTYPE_TASKNPC*/ )
	{
		CPropertyNPC* tpProNpc = ( CPropertyNPC* )pProperty;
		CTemplateOgre* tpNpcTpl = (CTemplateOgre*) CDataStatic::SearchTpl( tpProNpc->GetPropertyTempID( ) );
		if ( tpNpcTpl == NULL )
			return tValue;

		int tPerInCreamValue = tpProNpc->GetStateParam( STATE_INCREAMSPEED ).mParames1;
		int tPerUnCreamValue = tpProNpc->GetStateParam( STATE_UNCREAMSPEED ).mParames1;

		int tTempValue = (int)( SERVER_PERCENT_FLOAT + tPerInCreamValue - tPerUnCreamValue );
		if ( tTempValue != 0 )
			tValue.mInitValue = (int)( tpNpcTpl->mRunSpeed * SERVER_PERCENT_FLOAT / tTempValue );
		else
			tValue.mInitValue = tpNpcTpl->mRunSpeed;
		return tValue;
	}
	else if ( pProperty->GetEntityType( ) == ENTITYTYPE_PET )
	{
		CPropertyPet* tpProPet = ( CPropertyPet* )pProperty;
		CEntityPet* tpEntityPet = (CEntityPet*)CSceneLogic::GetSingletonPtr()->GetEntity( pProperty->GetEntityID( ) );
		if ( tpEntityPet == NULL )
		{
			LOG_ERROR( "pro", "[ %s : %d ] [ %s ] tpEntityPet(%d) is NULL!", __LK_FILE__, __LINE__, __FUNCTION__, pProperty->GetEntityID( )  );
			return tValue;
		}

		if ( 
			tpEntityPet->GetCurLevel( ) != CTemplateSummonBeast::PET_LEVEL_ONE 
			&& tpEntityPet->GetCurLevel( ) != CTemplateSummonBeast::PET_LEVEL_TWO
			&& tpEntityPet->GetCurLevel( ) != CTemplateSummonBeast::PET_LEVEL_THREE
		)
		{
			LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] mCurLevel of tpEntityPet is %d!\n", __LK_FILE__, __LINE__, 
				__FUNCTION__, tpEntityPet->GetCurLevel( ) );
			return tValue;
		}

		CTemplateSummonBeast* tpPetTpl = (CTemplateSummonBeast*) CDataStatic::SearchTpl( tpProPet->GetPropertyTempID());
		if ( tpPetTpl == NULL )
		{
			LOG_DEBUG( "pro", "[ %s : %d ] [ %s ] tpPetTpl is NULL!\n", __LK_FILE__, __LINE__, __FUNCTION__ );
			return tValue;
		}

		int tPerInCreamValue = tpProPet->GetStateParam( STATE_INCREAMSPEED ).mParames1;
		int tPerUnCreamValue = tpProPet->GetStateParam( STATE_UNCREAMSPEED ).mParames1;

		int tTempValue = (int)( SERVER_PERCENT_FLOAT + tPerInCreamValue - tPerUnCreamValue );
		if ( tTempValue != 0 )
			tValue.mInitValue = (int)( tpPetTpl->mPetData[ tpEntityPet->GetCurLevel( ) ].mSpeed * SERVER_PERCENT_FLOAT / tTempValue );
		else
			tValue.mInitValue = tpPetTpl->mPetData[ tpEntityPet->GetCurLevel( ) ].mSpeed;
		return tValue;
	
	}

	return tValue;
}

// �������ҿ�˿?
CPropertyValue CPropertyFormula::GetRunSpeed( int vEntityType, int vEntityID )
{
	CPropertyValue tValue;
	if( vEntityType == ENTITYTYPE_PLAYER )
	{
		CTemplateMetier* tpMetier = (CTemplateMetier*) CDataStatic::SearchMetier( vEntityID );
		if( tpMetier != NULL )
		{

			tValue.mInitValue = tpMetier->mRunSpeed;
			
		}		
	}
	else if( vEntityType == ENTITYTYPE_FUNCNPC || vEntityType == ENTITYTYPE_OGRE )
	{
		CTemplateOgre *tpOgre = (CTemplateOgre*) CDataStatic::SearchTpl( vEntityID );
		if( tpOgre != NULL )
		{
			tValue.mInitValue = tpOgre->mRunSpeed;
		}		
	}

	return tValue;
}

CPropertyValue CPropertyFormula::GetSkillLess( CPropertyCharacter* pProperty, int vSkillGenerID )
{
	CPropertyValue tValue;
	int i = 0;
	CSkillList&  tpSkill = pProperty->GetSkillList( );
    for( i = 0; i < tpSkill.GetSkillNum(); i++ )
    {	
		CSkillObject* pSkillObj = tpSkill.GetSkillObjectByIndex( i );
		LK_ASSERT( pSkillObj != NULL, continue );

        CTemplateSkill* tpSkillTempl = pSkillObj->GetSkillTpl();
        if ( tpSkillTempl == NULL )
            continue;

        if( tpSkillTempl->mSkillFuncID1 == CTemplateSkill::PASSINC_NEEDMPPER )
		{
			if( (int)tpSkillTempl->mParameter1[ 0 ] == vSkillGenerID )
	            tValue.mInitValue += tpSkillTempl->mParameter1[ 1 ];
		}
		else if( tpSkillTempl->mSkillFuncID1 == CTemplateSkill::PASSINC_NEEDMPFIX )
		{
			if( (int)tpSkillTempl->mParameter1[ 0 ] == vSkillGenerID )
				tValue.mDeltaValue += tpSkillTempl->mParameter1[ 1 ];
		}

        if( tpSkillTempl->mSkillFuncID2 == CTemplateSkill::PASSINC_NEEDMPPER )
        {
            if( (int)tpSkillTempl->mParameter2[ 0 ] == vSkillGenerID )
                tValue.mInitValue += tpSkillTempl->mParameter2[ 1 ];
        }
        else if( tpSkillTempl->mSkillFuncID2 == CTemplateSkill::PASSINC_NEEDMPFIX )
        {
            if( (int)tpSkillTempl->mParameter2[ 0 ] == vSkillGenerID )
                tValue.mDeltaValue += tpSkillTempl->mParameter2[ 1 ];
        }

        if( tpSkillTempl->mSkillFuncID3 == CTemplateSkill::PASSINC_NEEDMPPER )
        {
            if( (int)tpSkillTempl->mParameter3[ 0 ] == vSkillGenerID )
                tValue.mInitValue += tpSkillTempl->mParameter3[ 1 ];
        }
        else if( tpSkillTempl->mSkillFuncID3 == CTemplateSkill::PASSINC_NEEDMPFIX )
        {
            if( (int)tpSkillTempl->mParameter3[ 0 ] == vSkillGenerID )
                tValue.mDeltaValue += tpSkillTempl->mParameter3[ 1 ];
        }

        if( tpSkillTempl->mSkillFuncID4 == CTemplateSkill::PASSINC_NEEDMPPER )
        {
            if( (int)tpSkillTempl->mParameter4[ 0 ] == vSkillGenerID )
                tValue.mInitValue += tpSkillTempl->mParameter4[ 1 ];
        }
        else if( tpSkillTempl->mSkillFuncID4 == CTemplateSkill::PASSINC_NEEDMPFIX )
        {
            if( (int)tpSkillTempl->mParameter4[ 0 ] == vSkillGenerID )
                tValue.mDeltaValue += tpSkillTempl->mParameter4[ 1 ];
        }
    }	

	return tValue;
}

float CPropertyFormula::GetHitrate( int vSrcLevel, int vDesLevel, int vHitValue )
{
	float tHitParam1 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mHitparam1 / SERVER_PERCENT_FLOAT;
	float tHitParam2 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mHitparam2 / SERVER_PERCENT_FLOAT;
	float tHitParam3 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mHitparam3 / SERVER_PERCENT_FLOAT;
	float tHitParam4 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mHitparam4 / SERVER_PERCENT_FLOAT;
	float tHitParam5 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mHitparam5 / SERVER_PERCENT_FLOAT;
	float tHitParam6 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mHitparam6 / SERVER_PERCENT_FLOAT;
	float tHitParam7 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mHitparam7 / SERVER_PERCENT_FLOAT;

	return tHitParam1 + tHitParam2 * ( vSrcLevel - vDesLevel ) + tHitParam3 * vHitValue / ( tHitParam4 * vHitValue + tHitParam5 + pow( vDesLevel, tHitParam6 ) * tHitParam7 );
}

float CPropertyFormula::GetDuckRate( int vSrcLevel, int vDuckValue, int vIgnoreValue )
{
	float tDuckParam1 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDuckparam1 / SERVER_PERCENT_FLOAT;
	float tDuckParam2 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDuckparam2 / SERVER_PERCENT_FLOAT;
	float tDuckParam3 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDuckparam3 / SERVER_PERCENT_FLOAT;
	float tDuckParam4 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDuckparam4 / SERVER_PERCENT_FLOAT;
	float tDuckParam5 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDuckparam5 / SERVER_PERCENT_FLOAT;
	float tDuckParam6 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDuckparam6 / SERVER_PERCENT_FLOAT;

	return tDuckParam1 + tDuckParam2 * ( vDuckValue - vIgnoreValue ) / ( tDuckParam3 * vIgnoreValue + tDuckParam4 + pow( vSrcLevel, tDuckParam5 ) * tDuckParam6 );
}

// ���㱩����
float CPropertyFormula::GetDeathRate( int vDesLevel, int vDeathRate, int vDeathDefense )
{
	float tDeathParam1 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDeathparam1 / SERVER_PERCENT_FLOAT;
	float tDeathParam2 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDeathparam2 / SERVER_PERCENT_FLOAT;
	float tDeathParam3 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDeathparam3 / SERVER_PERCENT_FLOAT;
	float tDeathParam4 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDeathparam4 / SERVER_PERCENT_FLOAT;
	float tDeathParam5 = CSceneCfgManager::GetSingleton().GetFormula_cfg()->mDeathparam5 / SERVER_PERCENT_FLOAT;

	return ( vDeathRate - tDeathParam1 * vDeathDefense ) / ( tDeathParam2 * pow( tDeathParam3, ( vDesLevel - tDeathParam4 ) / tDeathParam5 ) ); 
}





