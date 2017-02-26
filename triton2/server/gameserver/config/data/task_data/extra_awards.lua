-- �ļ������� ���ļ���¼�˶��⽱�� ���绷����ÿ�����3�θ����⽱����
-- ���ļ���Ϊ�������ã�ԭ�����ɳ���Ͳ����޸� 
-- ע�⣺���ﲻ׼������Ʒ�ȿ���ʧ�ܵĶ��������� Ҳ���ܽ�����������Ķ�����

-----------------------------------------------------------------------------------------------------------------------
-- ���⽱����صĶ��壺
EXTRA_DEFINE=
{
	LOOP_TASK = 1;	-- ������
	TRAGEDY_TASK = 2; -- ��������
	CHAIRMAN_TASK = 3; -- ��������
	TEAMLOOP_ENDLOOP = 4;  -- ��ӻ����� ���һ�ֽ���
	TEAMLOOP_TEAMEXTRA = 5; -- ��ӻ����� ��Ӷ��⽱��	
};

extra_awards = {};

-- ��������⽱��
extra_awards[EXTRA_DEFINE.LOOP_TASK]=
{
	-- ��������4�ֶ��⽱��
	  [4] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name ="5" ,
			body = "",
			item_id1 = 52940, 
			item_id2 = 52940,
			item_id3 = 32663,
			item_id4 = 59562,
			item_id5 = 59532,
			item_num1 = 1,
			item_num2 = 1,
			item_num3 = 2,
			item_num4 = 1,
			item_num5 = 1,
			money = 2000,
		}},
	  },
};

-- ����������⽱��
extra_awards[EXTRA_DEFINE.TRAGEDY_TASK]=
{
	-- ����������1�׽��ѣ����⽱��
	  [9] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "6",
			body = "",
			item_id1 = 36781, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 5000,
		}},
	  },
	  [18] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "7",
			body = "",
			item_id1 = 36781, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 5000,
		}},
	  },
	  [27] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "8",
			body = "",
			item_id1 = 36781, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 5000,
		}},
	  },
	  [36] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "9",
			body = "",
			item_id1 = 36781, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 5000,
		}},
	  },
};

-- ����������⽱��
extra_awards[EXTRA_DEFINE.CHAIRMAN_TASK]=
{
		[303] = {
	  [3] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "10",
			body = "",
			item_id1 = 61332, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [5] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "11",
			body = "",
			item_id1 = 57059, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [10] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "12",
			body = "",
			item_id1 = 61768, 
			item_id2 = 61808,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 1,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	  };
	  		[306] = {
	  [3] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "13",
			body = "",
			item_id1 = 61332, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 5,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [5] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "14",
			body = "",
			item_id1 = 57060, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [10] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "15",
			body = "",
			item_id1 = 60333, 
			item_id2 = 61809,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 1,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	  };
	 		[307] = {
	  [3] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "16",
			body = "",
			item_id1 = 61332, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 10,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [5] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "17",
			body = "",
			item_id1 = 57058, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [10] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "18",
			body = "",
			item_id1 = 60336, 
			item_id2 = 61810,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 1,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	  };
			[308] = {
	  [3] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "19",
			body = "",
			item_id1 = 61331, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 5,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [5] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "20",
			body = "",
			item_id1 = 57111, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [10] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "21",
			body = "",
			item_id1 = 61853, 
			item_id2 = 61851,
			item_id3 = 61811,
			item_id4 = 58085,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 1,
			item_num3 = 1,
			item_num4 = 1,
			item_num5 = 0,
			money = 0,
		}},
	  },
	  };
	  		[311] = {
	  [3] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "22",
			body = "",
			item_id1 = 61331, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 10,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [5] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "23",
			body = "",
			item_id1 = 57056, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [10] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "24",
			body = "",
			item_id1 = 61841, 
			item_id2 = 60334,
			item_id3 = 61812,
			item_id4 = 58077,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 1,
			item_num3 = 1,
			item_num4 = 1,
			item_num5 = 0,
			money = 0,
		}},
	  },
	  };
	  		[310] = {
	  [3] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "25",
			body = "",
			item_id1 = 61198, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 5,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [5] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "26",
			body = "",
			item_id1 = 57063, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [10] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "27",
			body = "",
			item_id1 = 60337, 
			item_id2 = 60334,
			item_id3 = 61813,
			item_id4 = 58085,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 1,
			item_num3 = 1,
			item_num4 = 1,
			item_num5 = 0,
			money = 0,
		}},
	  },
	  };
	 		[309] = {
	  [3] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "28",
			body = "",
			item_id1 = 61198, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 10,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [5] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "29",
			body = "",
			item_id1 = 57064, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	 [10] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "30",
			body = "",
			item_id1 = 61849, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
	  };
};


-- ��ӻ�����������ֽ���
extra_awards[EXTRA_DEFINE.TEAMLOOP_ENDLOOP]=
{
	-- ���20���Ľ���
	[20] = 
	  {
		{func=award_send_mail, args = {		
			title = "", 
			src_name = "61",
			body = "",
			item_id1 = 76043, 
			item_id2 = 0,
			item_id3 = 0,
			item_id4 = 0,
			item_id5 = 0,
			item_num1 = 1,
			item_num2 = 0,
			item_num3 = 0,
			item_num4 = 0,
			item_num5 = 0,
			money = 0,
		}},
	  },
};

-- ���˽�������⽱��
extra_awards[EXTRA_DEFINE.TEAMLOOP_TEAMEXTRA]=
{
	-- 2����ӽ�����
	[2] = 
	  {
		-- ע�ͣ�����ÿ��һ�� ��Ҫ���Ľ���������Ƕ���������Ǯ��Ĭ���ߵ������������hard�������ϣ�����Ǹ�������args��д�� hard=xxx����
		{func=award_expr_by_level_table, args={hard=9}},
	  },
	[3] = 
	  {
		-- ע�ͣ�����ÿ��һ�� ��Ҫ���Ľ���������Ƕ���������Ǯ��Ĭ���ߵ������������hard�������ϣ�����Ǹ�������args��д�� hard=xxx����
		{func=award_expr_by_level_table, args={hard=9}},
	  },
	[4] = 
	  {
		-- ע�ͣ�����ÿ��һ�� ��Ҫ���Ľ���������Ƕ���������Ǯ��Ĭ���ߵ������������hard�������ϣ�����Ǹ�������args��д�� hard=xxx����
		{func=award_expr_by_level_table, args={hard=9}},
	  },
	[5] = 
	  {
		-- ע�ͣ�����ÿ��һ�� ��Ҫ���Ľ���������Ƕ���������Ǯ��Ĭ���ߵ������������hard�������ϣ�����Ǹ�������args��д�� hard=xxx����
		{func=award_expr_by_level_table, args={hard=9}},
	  },
	[6] = 
	  {
		-- ע�ͣ�����ÿ��һ�� ��Ҫ���Ľ���������Ƕ���������Ǯ��Ĭ���ߵ������������hard�������ϣ�����Ǹ�������args��д�� hard=xxx����
		{func=award_expr_by_level_table, args={hard=9}},
	  },
};
