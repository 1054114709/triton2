//���ļ��������з��͵��ͻ��˵ģ���Ҫ����������Ϣ����Ϣ����

#ifndef		_FAMILY_CORPS_DEFINE_
#define		_FAMILY_CORPS_DEFINE_


	#define		FAMILY_APPLY_PASSED				 100	//����ͨ������������������
	#define		FAMILY_CREATE_FAIL_MONEYLESS	 101	//����ʧ��-��Ǯ����
	#define		FAMILY_CREATE_FAIL_ADDED		 102	//����ʧ��-�Ѿ������˼���
	#define		FAMILY_CREATE_FAIL_LEVELLESS 	 103	//����ʧ��-�ȼ�����
	#define		FAMILY_CREATE_FAIL_EXIST_NAME	 104	//������������
	#define		FAMILY_CREATE_NAME_TOO_LONG		 105	//�������ƹ���
	#define		FAMILY_CREATE_NAME_TOO_SHORT	 106	//�������ƹ���
	#define		FAMILY_CREATE_NAME_ILL			 107	//�Ƿ�����
	#define		FAMILY_CREATE_SUCCESS			 108	//�����ɹ�

						// �峤������ش���

	#define		REQUEST_ERROR_ADDEDFAMILY				 201	//����ʧ��-�Ѿ������˼���
	#define		REQUEST_ERROR_FAMILY_MAXPEOPLE			 202	//����ʧ��-��������
	#define		REQUEST_ERROR_NOT_B						 203	//����ʧ��-û��Ȩ��
	#define		REQUEST_ERROR_OTHER						 204	//����ԭ��ʧ�ܣ��ټ���
	#define		REQUEST_ERROR_READD						 205	//�ظ�����
	#define		REQUEST_ERROR_PLAYER_LEVEL_LESS			 206	//Ŀ����ҵȼ�����
	#define		REQUEST_NO_SUCH_PLAYER					 207	//û��������
	#define		REQUEST_PLAYER_OFFLINE					 208	//�Է�������
	#define		REQUEST_SUCCESS							 209	//���������޴���

									// ������ְ�󷵻���Ϣ

	#define		CHANGE_POS_FLAG_OK						 300	//��ְ�ɹ�
	#define		CHANGE_POS_FLAG_EXSITED_B				 301	//��ְʧ��-�Ѿ������峤
	#define		CHANGE_POS_FLAG_EXSITED_C				 302	//��ְʧ��-�Ѿ����ڳ���
	#define		CHANGE_POS_FLAG_EXSITED_D				 303	//�Ѿ����ڼ������ˣ�������ְ
	#define		CHANGE_POS_FLAG_NO						 304	//���޴���
	#define		CHANGE_POS_FLAG_NOTA					 305	//��������
	#define		CHANGE_POS_FLAG_SELF					 306    //���ܸ��Լ���ְ��
	#define		CHANGE_POS_FLAG_BAD_POS					 307	//�����ְλ

									//��ְ������Ϣ

	#define		TAKE_OFF_POS_OK							 400 //��ְ�ɹ�
	#define		LEAVE_POS_OK							 401 //��ְ�ɹ�
	#define		TAKE_OFF_POST_ERROR					     402 //ְλ����
	#define		TAKE_OFF_IS_A							 403 //����������ְ
	#define		TAKE_OFF_IS_E							 404 //�������ˣ�(���˻���ʲôְ��)
	#define		TAKE_OFF_NOT_A							 405 //û��Ȩ��	

//��ɢ���������Ϣ
	#define		KILL_FAIL								 501	//���޷���ɢ���壬ֻ���������ܽ�ɢ
									// һ�����

	#define		COMMON_NOT_FAMILY_MEMBER				 10001	//���Ǽ����Ա
	#define		COMMON_FAMILYLIST_FIRST_PAGE			 10002	//�Ѿ������һҳ
	#define		COMMON_FAMILYLIST_LAST_PAGE				 10003	//�Ѿ��������һҳ
	#define		COMMON_ERROR_FAMILY						 10004	//�����ڵļ���
	#define		COMMON_LEVEL_LESS						 10005	//�ȼ�̫С�����ܼ������
	#define		COMMON_EXSITED_FAMILY					 10006	//�Ѿ��м��壬��������
	#define		COMMON_APPLYED							 10007	//�����Ѿ��������
	#define		COMMON_APPLY_OK							 10008	//����ɹ�
	#define		COMMON_SUCCESS							 10009	//�����ɹ��������ڸ��ֳɹ�
	#define		COMMON_FAIL								 10010	//����ʧ�ܡ������ڸ���ʧ��
	//#define		COMMON_BE_CORPS_KICKED					 10011	//�������߳�
	#define		COOL_CREATE_FAIL						 10011		//��ȴʱ��δ�������ܴ�������(��ȴʱ�䣺24Сʱ����ͬ)
	#define		COOL_SET_POST_FAIL						 10012		//��ȴʱ��δ����������ְ
	#define		COOL_ADD_FAMILY_FAIL					 10013		//��ȴʱ��δ�������ܼ������	(Msg:Ҫ����������ұ�������뿪����24Сʱ)
	#define		FAMILY_KILLED							 10014	//���ļ����ѱ���ɢ��


//������ض���


enum{
				//������Ϣ
				COMMON_NOT_IN_CORPS, //û�������
				COMMON_OK,				//�ɹ�
				COMMON_FAIL,			//ʧ��
				COMMON_CORPS_LIST_FIRSTPAGE, //�����б����һҳ
				COMMON_CORPS_LIST_LASTPAGE, //�����б������һҳ
				COMMON_RIGHT_LESS ,//û��Ȩ��
				COMMON_NOT_FAMILY_A , //�����Ǽ�������
				//������������ŵķ�����Ϣ
				CORPS_APPLY_NOT_IN_FAMILY,	//δ�������
				CORPS_ADDED_FAMILY,			//�Ѿ��������
				CORPS_APPLY_NOT_FAMILY_A ,	//���Ǽ�������
				CORPS_APPLY_MONEY_LESS	,	//Ǯ����
				CORPS_APPLY_OTHER_ERROR	,	//�������󣨺��ٷ�����
				CORPS_APPLY_NAME_TOO_LONG,	//����̫��
				CORPS_CREATE_BAD_NAME	,	//�Ƿ����ƣ�
				CORPS_CREATE_OK			,//�����ɹ�
				//�󽫾��������δ������ŵļ���������Ա�ķ�����Ϣ,�����ж��Ҽ��˵����Ƿ���ʾ��ص���Ŀ
				NOT_CORPS_BIG_GEN	, //���Ǵ󽫾���û��Ȩ�ޣ�
				PLAYER_NOT_IN_FAMLY	, //Ŀ�����û�м������
				PLAYER_FAMILY_IN_CORPS	, //Ŀ����ҵļ����Ѿ������˾���
				FAMILY_REQUEST_OK	, //��������	
				//���Ŵ󽫾��������������ķ���������״̬.���󽫾�����������ַ��ص���ϢҲ�����������
				REQUEST_OK, //����ɹ�
				REQUEST_OFFLINE	, //�Է�����û����
				REQUEST_BAD_FAMILY_NAME	, //û��������壡��
				REQUEST_RE_REQUEST	, //�ظ�����
				REQUEST_ADDED_CORPS	, //��������Ѿ������˾��ţ�
				REQUEST_ME_ADDED_CORPS,	//���Ѿ��������������ţ������������뷽)
				REQUEST_REDIRECT ,  //������ڿ糡�������Ժ��ٷ� (����������ټ�)
				//������������Ϣ
				JOIN_CORPS_APPLY_TWICE, //�����ظ�����
				JOIN_CORPS_ADDED_CORPS, //�Ѿ���������ˣ�����
				JOIN_CORPS_APPLY_SUCCESS, //���������ųɹ�
				MEMBER_TITLE_SET_OK,		//�޸���ҳƺųɹ�
				MEMBER_TITLE_TOO_LONG,		//��ҳƺ�̫����
				//�;��Ž�Ǯ�йص���Ϣ
				MONEY_GIVE_SUCCESS,	//�����ž�Ǯ�ɹ�
				MONEY_GET_SUCCESS,	//�󽫾�ȡǮ�ɹ�
				MONEY_ACCOUT_ERROR,		//Ǯ������ȷ
				MONEY_NOT_BIG_GEN,		//���Ǵ󽫾�
				MONEY_NOT_ENOUGH,		//Ǯ����
				MONEY_CARVE_SUCCESS,		//ǰ�潫����Ǯ�ɹ�
				SET_POST_DEST_NOT_A,	//����Ȩ��Ҳ��Ǽ�������
				SET_POST_TOO_MANY_C,	//ǰ�潫��̫��
				SET_POST_BAD_POSTNAME,	//�����ְλ��
				SET_POST_SELF,			//���ܸ��Լ���ְ��
				SET_POST_SUCCESS,		//�󽫾���ְ(��Ȩ)�ɹ�
				TAKEOFF_POST_SUCCESS,		//��ְ�ɹ�
				KICK_OUT_CANT_SELF_FAMILY,	//�����߳��Լ����ڵļ���
				KICK_OUT_SUCCESS,			//�߳�����ɹ�
				KILL_CORPS_SUCCESS,			//��ɢ���ųɹ���48Сʱ���ɢ��
				KILL_CORPS_CANCEL_SUCCESS,	//ȡ����ɢ���ųɹ�
				KILL_CORPS_FAIL,			//��ɢ����ʧ�ܣ�������������
				CORPS_DIED		,			//���ű���ɢ�ˣ�
				COOL_CORPS_SET_POST_FAIL			,		//��ȴʱ��δ�������ܸ����ų�Ա������ְ
				COOL_ADD_CORPS_FAIL,							//��ȴʱ��δ�������ܼ������
				CANT_LEAVE_POST,				//������ְ��ֻ�о�ʦ��ǰ�潫��������ְ
				LEAVE_POST_OK					//��ְ�ɹ�
};


#endif

