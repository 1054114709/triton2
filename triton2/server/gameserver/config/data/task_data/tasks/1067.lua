task = {
  id = 1067,    --����ID
  kind = 2,    --��������
  color = 4,    --������ɫ
  name = "#td_1067_name",  
  desc = "#td_1067_desc",  
  dest = "#td_1067_dest",  
  section = "#td_1067_section",  
  give_npc = 45625,    --����NPC
  give_map_id = 63,    --����NPC���ڵĵ�ͼID
  recv_npc = 7355,    --����NPC
  recv_map_id = 62,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 0,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 1080,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 39,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 1,    --��������
  task_hard = 4,    --�������ͼ��Ѷ�
  trace={ 
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 63,    --��ʾ�ѽ�����ĵ�ͼID
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
  give_items = {{id=34114, n=1}};   --���ŵ���
  --����NPC·��
  npc_waypoints = {};
  drop_items = {};   --�������
  --����������
  accept_cond = 
  {
	{func=check_before_task, args={task_id = 1066}},
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
	{func=check_items_of_bag, args={id = 34114,n = 1}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 60000}},
	{func=award_money, args={money = 3250}},
	{func=award_telant, args={money = 0}},
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
	npc_talk ="#td_1067_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_1067_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 254 ,func_code = 0},

	  }
	},
	[254] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_1067_dialog_accept_npctalk_254",
	buttons = {
        { player_talk = "#td_1067_dialog_accept_player_talk_254_1" ,dest_type = 1 ,dest_window_id = 255 ,func_code = 0},

	  }
	},
	[255] = {
	parent_id = 254,
	window_type = 1,
	npc_talk ="#td_1067_dialog_accept_npctalk_255",
	buttons = {
        { player_talk = "#td_1067_dialog_accept_player_talk_255_1" ,dest_type = 1 ,dest_window_id = 256 ,func_code = 0},

	  }
	},
	[256] = {
	parent_id = 255,
	window_type = 1,
	npc_talk ="#td_1067_dialog_accept_npctalk_256",
	buttons = {
        { player_talk = "#td_1067_dialog_accept_player_talk_256_1" ,dest_type = 1 ,dest_window_id = 257 ,func_code = 0},

	  }
	},
	[257] = {
	parent_id = 256,
	window_type = 3,
	npc_talk ="#td_1067_dialog_accept_npctalk_257",
	buttons = {
        { player_talk = "#td_1067_dialog_accept_player_talk_257_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 3},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1067_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1067_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_1067_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 259 ,func_code = 0},

  }
},
	[259] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_1067_dialog_end_npctalk_259",
	buttons = {
        { player_talk = "#td_1067_dialog_end_player_talk_259_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}