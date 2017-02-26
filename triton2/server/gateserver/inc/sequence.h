#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "servertool.h"
#include "gatelogic.h"

/*
 * ����Ψһ�����к�
 *
 */
class CSequence : public CSingleton< CSequence >
{
	private:
		// ÿ��Ԥ����ĸ���
		enum { em_once_block_size = 5000 };

		int m_nMinID;
		int m_nMaxID;
		int m_nStep;

		int m_nCurID;
		int m_nLeft;
	public:
		CSequence(int nMinID, int nMaxID, int nStep): m_nMinID(nMinID), m_nMaxID (nMaxID), m_nStep(nStep)
		{
			m_nLeft = 0;
		}

		~CSequence() {}

		int NextID()
		{
			// ���û��ʣ�࣬�����
			if ( m_nLeft == 0 )
			{
				int lastid = -1;

				//FILE* fp = fopen("../config/data/gate_config/sequence.cfg", "r+");
				//CGateLogic::GetSingletonPtr()->GetConfigDataFileNamePath(CGateLogic::GetSingleton().mConfig.nGameID,"gate_config/sequence.cfg")
				FILE* fp = fopen(CGateLogic::GetSingletonPtr()->GetConfigDataFileNamePath(CGateLogic::GetSingleton().mConfig.nGameID,"gate_config/sequence.cfg"), "r+");
				if (fp == NULL) return -1;
				if ( fscanf(fp, "%d\n", &lastid) <= 0)  return -1;

				int nextid = lastid + m_nStep * em_once_block_size;

				// ������������ֵ, Ϊ�򻯲�����������ֵΪ��Сֵ
				if ( nextid > m_nMaxID || nextid < m_nMinID) 
				{
					nextid = m_nMinID + m_nStep * em_once_block_size;
					lastid = m_nMinID;

					if ( nextid > m_nMaxID || nextid < m_nMinID)
					{
						return -1;
					}
				}

				// �ƶ����ļ��Ŀ�ʼλ��
				if ( fseek(fp, 0, SEEK_SET) < 0)
				{
					return -1;
				}

				// ��Ԥ������nextidд�뵽�ļ���
				if ( fprintf(fp, "%010d\n", nextid ) < 0) 
				{
					return -1;
				}

				if ( fclose(fp) != 0 )
				{
					return -1;
				}

				m_nLeft = em_once_block_size;
				m_nCurID = lastid;
			}

			m_nCurID += m_nStep;	// ��С��ID��ʹ��
			m_nLeft --;

			return m_nCurID;
		}
};

#endif
