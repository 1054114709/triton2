task = {
  id = 3037,    --����ID
  kind = 0,    --��������
  color = 0,    --������ɫ
  name = "#td_3037_name",  
  desc = "#td_3037_desc",  
  dest = "#td_3037_dest",  
  section = "#td_3037_section",  
  give_npc = 35953,    --����NPC
  give_map_id = 5,    --����NPC���ڵĵ�ͼID
  recv_npc = 35953,    --����NPC
  recv_map_id = 5,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 1,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 0,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 43,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 4,    --��������
  task_hard = 6,    --�������ͼ��Ѷ�
  trace={ 
	"#td_3037_trace1",
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 5,    --���������ĵ�ͼID
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
  drop_items = {{npc_id=44913 ,item_id=36030 ,n=1 ,p=5000, mapid=5},{npc_id=44914 ,item_id=36030 ,n=1 ,p=5000, mapid=5}};   --�������
  --����������
  accept_cond = 
  {
	{func=check_before_task, args={task_id = 3036}},
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
	{func=check_items_of_bag, args={id = 36030,n = 10}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 75000}},
	{func=award_money, args={money = 9800}},
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
	npc_talk ="#td_3037_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_3037_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 319 ,func_code = 0},

	  }
	},
	[319] = {
	parent_id = 1,
	window_type = 3,
	npc_talk ="#td_3037_dialog_accept_npctalk_319",
	buttons = {

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_3037_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_3037_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_3037_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 320 ,func_code = 0},

  }
},
	[320] = {
	parent_id = 3,
	window_type = 1,
	npc_talk ="#td_3037_dialog_end_npctalk_320",
	buttons = {
        { player_talk = "#td_3037_dialog_end_player_talk_320_1" ,dest_type = 1 ,dest_window_id = 321 ,func_code = 0},

  }
},
	[321] = {
	parent_id = 320,
	window_type = 1,
	npc_talk ="#td_3037_dialog_end_npctalk_321",
	buttons = {
        { player_talk = "#td_3037_dialog_end_player_talk_321_1" ,dest_type = 1 ,dest_window_id = 322 ,func_code = 0},

  }
},
	[322] = {
	parent_id = 321,
	window_type = 1,
	npc_talk ="#td_3037_dialog_end_npctalk_322",
	buttons = {
        { player_talk = "#td_3037_dialog_end_player_talk_322_1" ,dest_type = 1 ,dest_window_id = 323 ,func_code = 0},

  }
},
	[323] = {
	parent_id = 322,
	window_type = 1,
	npc_talk ="#td_3037_dialog_end_npctalk_323",
	buttons = {
        { player_talk = "#td_3037_dialog_end_player_talk_323_1" ,dest_type = 1 ,dest_window_id = 324 ,func_code = 0},

  }
},
	[324] = {
	parent_id = 323,
	window_type = 2,
	npc_talk ="#td_3037_dialog_end_npctalk_324",
	buttons = {
        { player_talk = "#td_3037_dialog_end_player_talk_324_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}