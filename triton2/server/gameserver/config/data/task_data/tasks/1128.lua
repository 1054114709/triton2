task = {
  id = 1128,    --����ID
  kind = 2,    --��������
  color = 4,    --������ɫ
  name = "#td_1128_name",  
  desc = "#td_1128_desc",  
  dest = "#td_1128_dest",  
  section = "#td_1128_section",  
  give_npc = 35950,    --����NPC
  give_map_id = 64,    --����NPC���ڵĵ�ͼID
  recv_npc = 46907,    --����NPC
  recv_map_id = 64,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 0,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 9312,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 50,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 1,    --��������
  task_hard = 2,    --�������ͼ��Ѷ�
  trace={ 
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 64,    --��ʾ�ѽ�����ĵ�ͼID
  can_invite = 0,    --�Ƿ��������
  timeout_action = 0,    --��ʱ����ʱ�������״̬
  time_lmt_type = 0,    --��ʱ��������
  is_redirect_fail = 0,    --�Ƿ���ͼ����ʧ��
  is_day_clear = 0,    --�Ƿ�ÿ�������ɼ�¼
  give_camp = 0,    --����NPC��Ӫ
  recv_camp = 0,    --����NPC��Ӫ
  is_day_fail = 0,    --�Ƿ����ʧ��
  loop_type = 0,    --����������
  team_member_lmt = 0,    --Ҫ���������
  finish_delay_time = 0,    --�����Ҫ����ò��ܽ������룩
  refresh_award_able = 0,    --�����Ƿ����ˢ�½���
  task_reaccept_time = 0,    --������ɺ��ÿ����ٽ���ͬ�����룩
  publish_type = 0,    --������������
  give_items = {};   --���ŵ���
  --����NPC·��
  npc_waypoints = {};
  drop_items = {};   --�������
  --����������
  accept_cond = 
  {
	{func=check_before_task, args={task_id = 1127}},
  };
  --������������
  publish_cond = 
  {
  };
  --������ʾ����
  show_cond = 
  {
  };
  --�������
  complete_cond = 
  {
	{func=check_level, args={min_level = 50,max_level = 0}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 34000}},
	{func=award_money, args={money = 4125}},
	{func=award_telant, args={money = 0}},
	{func=award_common_fame, args={value = 300}},
};
  --����������
  accept_awards = 
  {
};
  --�Ի�
  dialog =   {
  --������Ի�
	[1] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1128_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_1128_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 41 ,func_code = 0},

	  }
	},
	[41] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_1128_dialog_accept_npctalk_41",
	buttons = {
        { player_talk = "#td_1128_dialog_accept_player_talk_41_1" ,dest_type = 1 ,dest_window_id = 42 ,func_code = 0},

	  }
	},
	[42] = {
	parent_id = 41,
	window_type = 1,
	npc_talk ="#td_1128_dialog_accept_npctalk_42",
	buttons = {
        { player_talk = "#td_1128_dialog_accept_player_talk_42_1" ,dest_type = 1 ,dest_window_id = 43 ,func_code = 0},

	  }
	},
	[43] = {
	parent_id = 42,
	window_type = 3,
	npc_talk ="#td_1128_dialog_accept_npctalk_43",
	buttons = {
        { player_talk = "#td_1128_dialog_accept_player_talk_43_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 3},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1128_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1128_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_1128_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 44 ,func_code = 0},

  }
},
	[44] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_1128_dialog_end_npctalk_44",
	buttons = {
        { player_talk = "#td_1128_dialog_end_player_talk_44_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}