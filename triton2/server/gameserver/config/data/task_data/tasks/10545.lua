task = {
  id = 10545,    --����ID
  kind = 0,    --��������
  color = 0,    --������ɫ
  name = "#td_10545_name",  
  desc = "#td_10545_desc",  
  dest = "#td_10545_dest",  
  section = "#td_10545_section",  
  give_npc = 75712,    --����NPC
  give_map_id = 164,    --����NPC���ڵĵ�ͼID
  recv_npc = 75715,    --����NPC
  recv_map_id = 164,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 0,    --�����ܷ񱻷���
  repeatable = 1,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
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
  task_hard = 6,    --�������ͼ��Ѷ�
  trace={ 
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 530049,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 164,    --���������ĵ�ͼID
  can_invite = 1,    --�Ƿ�������루Ĭ��0Ϊ�������룩
  timeout_action = 0,    --��ʱ����ʱ�������״̬
  time_lmt_type = 0,    --��ʱ��������
  is_redirect_fail = 0,    --�Ƿ���ͼ����ʧ��
  is_day_clear = 0,    --�Ƿ�ÿ�������ɼ�¼
  give_camp = 0,    --����NPC��Ӫ
  recv_camp = 0,    --����NPC��Ӫ
  is_day_fail = 0,    --�Ƿ����ʧ��
  loop_type = 2,    --����������
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
	{func=check_level, args={min_level = 60,max_level = 0}},
	{func=check_today_completedbygroup, args={group_id = 530049,max_times = 1}},
	{func=check_mutex_by_group, args={group_id = 530049}},
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
  };
  --������ɽ���
  awards = 
  {
	{func=award_items, args={id = 75944,n = 2,is_free = 0}},
};
  --����������
  accept_awards = 
  {
	{func=award_buff, args={id = 76069}},
};
  --�Ի�
  dialog =   {
  --������Ի�
	[1] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_10545_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_10545_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 4 ,func_code = 0},

	  }
	},
	[4] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_10545_dialog_accept_npctalk_4",
	buttons = {
        { player_talk = "#td_10545_dialog_accept_player_talk_4_1" ,dest_type = 1 ,dest_window_id = 5 ,func_code = 0},

	  }
	},
	[5] = {
	parent_id = 4,
	window_type = 3,
	npc_talk ="#td_10545_dialog_accept_npctalk_5",
	buttons = {

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_10545_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_10545_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_10545_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 6 ,func_code = 0},

  }
},
	[6] = {
	parent_id = 3,
	window_type = 1,
	npc_talk ="#td_10545_dialog_end_npctalk_6",
	buttons = {
        { player_talk = "#td_10545_dialog_end_player_talk_6_1" ,dest_type = 1 ,dest_window_id = 7 ,func_code = 0},

  }
},
	[7] = {
	parent_id = 6,
	window_type = 1,
	npc_talk ="#td_10545_dialog_end_npctalk_7",
	buttons = {
        { player_talk = "#td_10545_dialog_end_player_talk_7_1" ,dest_type = 1 ,dest_window_id = 8 ,func_code = 0},

  }
},
	[8] = {
	parent_id = 7,
	window_type = 1,
	npc_talk ="#td_10545_dialog_end_npctalk_8",
	buttons = {
        { player_talk = "#td_10545_dialog_end_player_talk_8_1" ,dest_type = 1 ,dest_window_id = 9 ,func_code = 0},

  }
},
	[9] = {
	parent_id = 8,
	window_type = 1,
	npc_talk ="#td_10545_dialog_end_npctalk_9",
	buttons = {
        { player_talk = "#td_10545_dialog_end_player_talk_9_1" ,dest_type = 1 ,dest_window_id = 10 ,func_code = 0},

  }
},
	[10] = {
	parent_id = 9,
	window_type = 1,
	npc_talk ="#td_10545_dialog_end_npctalk_10",
	buttons = {
        { player_talk = "#td_10545_dialog_end_player_talk_10_1" ,dest_type = 1 ,dest_window_id = 11 ,func_code = 0},

  }
},
	[11] = {
	parent_id = 10,
	window_type = 2,
	npc_talk ="#td_10545_dialog_end_npctalk_11",
	buttons = {

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}