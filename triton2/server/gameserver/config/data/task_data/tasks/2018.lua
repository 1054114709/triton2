task = {
  id = 2018,    --����ID
  kind = 2,    --��������
  color = 2,    --������ɫ
  name = "#td_2018_name",  
  desc = "#td_2018_desc",  
  dest = "#td_2018_dest",  
  section = "#td_2018_section",  
  give_npc = 7365,    --����NPC
  give_map_id = 62,    --����NPC���ڵĵ�ͼID
  recv_npc = 7346,    --����NPC
  recv_map_id = 62,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 1,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 2019,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 35,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 2,    --��������
  task_hard = 1,    --�������ͼ��Ѷ�
  trace={ 
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 63,    --���������ĵ�ͼID
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
  give_items = {{id=35995, n=1}};   --���ŵ���
  --����NPC·��
  npc_waypoints = {};
  drop_items = {};   --�������
  --����������
  accept_cond = 
  {
	{func=check_level, args={min_level = 35,max_level = 200}},
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
	{func=check_items_of_bag, args={id = 35995,n = 1}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 9000}},
	{func=award_money, args={money = 1300}},
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
	npc_talk ="#td_2018_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_2018_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 218 ,func_code = 0},

	  }
	},
	[218] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_2018_dialog_accept_npctalk_218",
	buttons = {
        { player_talk = "#td_2018_dialog_accept_player_talk_218_1" ,dest_type = 1 ,dest_window_id = 219 ,func_code = 0},

	  }
	},
	[219] = {
	parent_id = 218,
	window_type = 3,
	npc_talk ="#td_2018_dialog_accept_npctalk_219",
	buttons = {
        { player_talk = "#td_2018_dialog_accept_player_talk_219_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 3},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_2018_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_2018_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_2018_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 220 ,func_code = 0},

  }
},
	[220] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_2018_dialog_end_npctalk_220",
	buttons = {
        { player_talk = "#td_2018_dialog_end_player_talk_220_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}