task = {
  id = 1013,    --����ID
  kind = 2,    --��������
  color = 4,    --������ɫ
  name = "#td_1013_name",  
  desc = "#td_1013_desc",  
  dest = "#td_1013_dest",  
  section = "#td_1013_section",  
  give_npc = 7323,    --����NPC
  give_map_id = 1,    --����NPC���ڵĵ�ͼID
  recv_npc = 33773,    --����NPC
  recv_map_id = 1,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 0,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 1015,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 8,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 1,    --��������
  task_hard = 1,    --�������ͼ��Ѷ�
  trace={ 
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 1,    --��ʾ�ѽ�����ĵ�ͼID
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
	{func=check_before_task, args={task_id = 1012}},
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
	{func=award_expr, args={expr = 2400}},
	{func=award_money, args={money = 120}},
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
	npc_talk ="#td_1013_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_1013_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 154 ,func_code = 0},

	  }
	},
	[154] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_1013_dialog_accept_npctalk_154",
	buttons = {
        { player_talk = "#td_1013_dialog_accept_player_talk_154_1" ,dest_type = 1 ,dest_window_id = 155 ,func_code = 0},

	  }
	},
	[155] = {
	parent_id = 154,
	window_type = 1,
	npc_talk ="#td_1013_dialog_accept_npctalk_155",
	buttons = {
        { player_talk = "#td_1013_dialog_accept_player_talk_155_1" ,dest_type = 1 ,dest_window_id = 286 ,func_code = 0},

	  }
	},
	[286] = {
	parent_id = 155,
	window_type = 3,
	npc_talk ="#td_1013_dialog_accept_npctalk_286",
	buttons = {
        { player_talk = "#td_1013_dialog_accept_player_talk_286_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 3},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1013_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1013_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_1013_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 73 ,func_code = 0},

  }
},
	[73] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_1013_dialog_end_npctalk_73",
	buttons = {
        { player_talk = "#td_1013_dialog_end_player_talk_73_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}