task = {
  id = 9803,    --����ID
  kind = 0,    --��������
  color = 0,    --������ɫ
  name = "#td_9803_name",  
  desc = "#td_9803_desc",  
  dest = "#td_9803_dest",  
  section = "#td_9803_section",  
  give_npc = 61234,    --����NPC
  give_map_id = 69,    --����NPC���ڵĵ�ͼID
  recv_npc = 61234,    --����NPC
  recv_map_id = 69,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 1,    --�����ܷ񱻷���
  repeatable = 1,    --����ɹ���ɷ�����
  retryable = 0,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 0,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 0,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 2048,    --��������
  task_hard = 3,    --�������ͼ��Ѷ�
  trace={ 
	"#td_9803_trace1",
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 524296,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 60,    --���������ĵ�ͼID
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
	{func=check_level, args={min_level = 30,max_level = 0}},
	{func=check_today_completedbygroup, args={group_id = 524296,max_times = 1}},
	{func=check_mutex_by_group, args={group_id = 524296}},
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
	{func=check_multi_cond, args={
		{func=check_items_of_bag, args={id = 45512,n = 1}},
	}};
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr_by_level_table, args={expr = 0}},
	{func=award_money_by_level_table, args={expr = 0}},
	{func=award_option_items, args={id1 = 58215,n1 = 1,id2 = 58219,n2 = 1,id3 = 58218,n3 = 1,id4 = 58216,n4 = 1,id5 = 58217,n5 = 1,id6 = 58220,n6 = 1,id7 = 0,n7 = 0,id8 = 0,n8 = 0,is_free = 0}},
	{func=award_items, args={id = 60350,n = 1,is_free = 0}},
	{func=award_items, args={id = 60194,n = 5,is_free = 0}},
	{func=award_items, args={id = 61331,n = 1,is_free = 0}},
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
	npc_talk ="#td_9803_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_9803_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 4 ,func_code = 0},

	  }
	},
	[4] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_9803_dialog_accept_npctalk_4",
	buttons = {
        { player_talk = "#td_9803_dialog_accept_player_talk_4_1" ,dest_type = 1 ,dest_window_id = 8 ,func_code = 0},

	  }
	},
	[8] = {
	parent_id = 4,
	window_type = 3,
	npc_talk ="#td_9803_dialog_accept_npctalk_8",
	buttons = {

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_9803_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_9803_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_9803_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 5 ,func_code = 0},

  }
},
	[5] = {
	parent_id = 3,
	window_type = 1,
	npc_talk ="#td_9803_dialog_end_npctalk_5",
	buttons = {
        { player_talk = "#td_9803_dialog_end_player_talk_5_1" ,dest_type = 1 ,dest_window_id = 6 ,func_code = 0},

  }
},
	[6] = {
	parent_id = 5,
	window_type = 1,
	npc_talk ="#td_9803_dialog_end_npctalk_6",
	buttons = {
        { player_talk = "#td_9803_dialog_end_player_talk_6_1" ,dest_type = 1 ,dest_window_id = 7 ,func_code = 0},

  }
},
	[7] = {
	parent_id = 6,
	window_type = 2,
	npc_talk ="#td_9803_dialog_end_npctalk_7",
	buttons = {

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}