#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "servertool.h"

/*
 * ����Ψһ�����к�
 *
 */
class CSequence : public CSingleton< CSequence >
{
	private:
		// ÿ��Ԥ����ĸ���
		enum { em_once_block_size = 5000 };

//		int m_nMinID;
//		int m_nMaxID;
//		int m_nStep;

		int m_nNextMinID;
		int m_nNextLeft;

		int m_nCurID;
		int m_nLeft;
	
		bool m_bGetLasting;
	public:
		CSequence( /* int nMinID, int nMaxID, int nStep */ ) // : m_nMinID(nMinID), m_nMaxID (nMaxID), m_nStep(nStep)
		{
			m_nLeft = 0;
			m_bGetLasting = false;

			m_nCurID = 0;
			m_nNextMinID = 0;
			m_nNextLeft = 0;
		}

		~CSequence() 
		{
		//	if ( m_nLeft <= 0) return;

			//Ϊ�˱����˷ѣ�����ǰֵд���ļ�
		//	FILE* fp = fopen("../config/data/scene_config/sequence.cfg", "w+");
		//	if (fp == NULL) return;

		//	if ( fprintf(fp, "%010d\n", m_nCurID ) < 0) 
		//	{
		//		return;
		//	}
				
		//	if (fclose(fp) != -1)
		//	{
		//		return;
		//	}
		}

		int SetStep( int nNextMinID, int nNextStep )
		{
			m_nNextLeft = nNextStep;
			m_nNextMinID = nNextMinID;
			LOG_NOTICE( "default", "[ %s : %d ][ %s ] Set Step %d, %d", __LK_FILE__, __LINE__, __FUNCTION__, 
				nNextMinID, nNextStep );
			return SUCCESS;	
		}

		//int GetNewSequent( );
		//int CanntGetNewSequent( );

		void GetLastingEnd( )
		{
			m_bGetLasting = false;
			LOG_NOTICE( "default", "[ %s : %d ][ %s ] End Get Sequent %d, %d, %d, %d", __LK_FILE__, __LINE__, 
				__FUNCTION__, m_nCurID, m_nLeft, m_nNextMinID, m_nNextLeft );
		}	

		void GetLastingBegin( )
		{
			m_bGetLasting = true;
			LOG_NOTICE( "default", "[ %s : %d ][ %s ] Begin Get Sequent %d, %d", __LK_FILE__, __LINE__, __FUNCTION__,
				m_nCurID, m_nLeft );
		}

		int NextID()
		{
			// ���û��ʣ�࣬�����
			if ( m_nLeft == 0 )
			{
				if( m_nNextLeft == 0 )
				{
					LOG_ERROR( "default", "[ %s : %d ][ %s ] Sequence Is Empty", __LK_FILE__, __LINE__, __FUNCTION__ );
					//GetNewSequent( );
					return -1;
				}

				m_nCurID = m_nNextMinID;
				m_nLeft = m_nNextLeft;
				m_nNextLeft = 0;
	//			int lastid = -1;

	//			FILE* fp = fopen("../config/data/scene_config/sequence.cfg", "r+");
	//			if (fp == NULL) return -1;
	//			if ( fscanf(fp, "%d\n", &lastid) <= 0)  return -1;

	//			int nextid = lastid + m_nStep * em_once_block_size;

				// ������������ֵ, Ϊ�򻯲�����������ֵΪ��Сֵ
	//			if ( nextid > m_nMaxID || nextid < m_nMinID) 
	//			{
	//				nextid = m_nMinID + m_nStep * em_once_block_size;
	//				lastid = m_nMinID;

	//				if ( nextid > m_nMaxID || nextid < m_nMinID)
	//				{
	//					return -1;
	//				}
	//			}

				// �ƶ����ļ��Ŀ�ʼλ��
	//			if ( fseek(fp, 0, SEEK_SET) < 0)
	//			{
	//				return -1;
	//			}

				// ��Ԥ������nextidд�뵽�ļ���
	//			if ( fprintf(fp, "%010d\n", nextid ) < 0) 
	//			{
	//				return -1;
	//			}

	//			if ( fclose(fp) != 0 )
	//			{
	//				return -1;
	//			}

	//			m_nLeft = em_once_block_size;
	//			m_nCurID = lastid;
			}

			m_nCurID++;
			m_nLeft--;

			if( m_nLeft <= 50 )
			{
				if( m_nNextLeft == 0 )
				{
					//GetNewSequent( );
				}
			}

			return m_nCurID;	

	//		m_nCurID += m_nStep;	// ��С��ID��ʹ��
	//		m_nLeft --;
//
//			return m_nCurID;
		}
};

#endif



