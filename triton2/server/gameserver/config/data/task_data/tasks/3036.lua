task = {
  id = 3036,    --����ID
  kind = 0,    --��������
  color = 0,    --������ɫ
  name = "#td_3036_name",  
  desc = "#td_3036_desc",  
  dest = "#td_3036_dest",  
  section = "#td_3036_section",  
  give_npc = 7370,    --����NPC
  give_map_id = 62,    --����NPC���ڵĵ�ͼID
  recv_npc = 7370,    --����NPC
  recv_map_id = 62,    --����NPC���ڵĵ�ͼID
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
  task_hard = 7,    --�������ͼ��Ѷ�
  trace={ 
	"#td_3036_trace1",
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
  drop_items = {{npc_id=44913 ,item_id=36024 ,n=1 ,p=5000, mapid=5},{npc_id=44914 ,item_id=36024 ,n=1 ,p=5000, mapid=5}};   --�������
  --����������
  accept_cond = 
  {
	{func=check_level, args={min_level = 43,max_level = 200}},
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
	{func=check_items_of_bag, args={id = 36024,n = 10}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 70000}},
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
	npc_talk ="#td_3036_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_3036_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 312 ,func_code = 0},

	  }
	},
	[312] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_3036_dialog_accept_npctalk_312",
	buttons = {
        { player_talk = "#td_3036_dialog_accept_player_talk_312_1" ,dest_type = 1 ,dest_window_id = 313 ,func_code = 0},

	  }
	},
	[313] = {
	parent_id = 312,
	window_type = 1,
	npc_talk ="#td_3036_dialog_accept_npctalk_313",
	buttons = {
        { player_talk = "#td_3036_dialog_accept_player_talk_313_1" ,dest_type = 1 ,dest_window_id = 314 ,func_code = 0},

	  }
	},
	[314] = {
	parent_id = 313,
	window_type = 1,
	npc_talk ="#td_3036_dialog_accept_npctalk_314",
	buttons = {
        { player_talk = "#td_3036_dialog_accept_player_talk_314_1" ,dest_type = 1 ,dest_window_id = 315 ,func_code = 0},

	  }
	},
	[315] = {
	parent_id = 314,
	window_type = 1,
	npc_talk ="#td_3036_dialog_accept_npctalk_315",
	buttons = {
        { player_talk = "#td_3036_dialog_accept_player_talk_315_1" ,dest_type = 1 ,dest_window_id = 316 ,func_code = 0},

	  }
	},
	[316] = {
	parent_id = 315,
	window_type = 3,
	npc_talk ="#td_3036_dialog_accept_npctalk_316",
	buttons = {
        { player_talk = "#td_3036_dialog_accept_player_talk_316_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 3},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_3036_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_3036_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_3036_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 317 ,func_code = 0},

  }
},
	[317] = {
	parent_id = 3,
	window_type = 1,
	npc_talk ="#td_3036_dialog_end_npctalk_317",
	buttons = {
        { player_talk = "#td_3036_dialog_end_player_talk_317_1" ,dest_type = 1 ,dest_window_id = 318 ,func_code = 0},

  }
},
	[318] = {
	parent_id = 317,
	window_type = 2,
	npc_talk ="#td_3036_dialog_end_npctalk_318",
	buttons = {
        { player_talk = "#td_3036_dialog_end_player_talk_318_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}