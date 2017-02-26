task = {
  id = 1062,    --����ID
  kind = 7,    --��������
  color = 4,    --������ɫ
  name = "#td_1062_name",  
  desc = "#td_1062_desc",  
  dest = "#td_1062_dest",  
  section = "#td_1062_section",  
  give_npc = 35947,    --����NPC
  give_map_id = 63,    --����NPC���ڵĵ�ͼID
  recv_npc = 35947,    --����NPC
  recv_map_id = 63,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 0,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 1063,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 38,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 1,    --��������
  task_hard = 6,    --�������ͼ��Ѷ�
  trace={ 
	"#td_1062_trace1",
	"#td_1062_trace2",
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
  give_items = {};   --���ŵ���
  --����NPC·��
  npc_waypoints = {};
  drop_items = {};   --�������
  --����������
  accept_cond = 
  {
	{func=check_before_task, args={task_id = 1061}},
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
	{func=check_many_orges_by_killed, args={id1 = 44900,id2 = 44901,id3 = 0,id4 = 0,id5 = 0,n = 20}},
	{func=check_many_orges_by_killed, args={id1 = 44902,id2 = 44903,id3 = 44904,id4 = 0,id5 = 0,n = 20}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 120000}},
	{func=award_money, args={money = 12500}},
	{func=award_items_by_metier, args={id = 43218,n = 1,metier = 5,is_free = 0}},
	{func=award_items_by_metier, args={id = 43219,n = 1,metier = 3,is_free = 0}},
	{func=award_items_by_metier, args={id = 43220,n = 1,metier = 2,is_free = 0}},
	{func=award_items_by_metier, args={id = 43221,n = 1,metier = 6,is_free = 0}},
	{func=award_items_by_metier, args={id = 43222,n = 1,metier = 1,is_free = 0}},
	{func=award_items_by_metier, args={id = 43223,n = 1,metier = 4,is_free = 0}},
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
	npc_talk ="#td_1062_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_1062_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 230 ,func_code = 0},

	  }
	},
	[230] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_1062_dialog_accept_npctalk_230",
	buttons = {
        { player_talk = "#td_1062_dialog_accept_player_talk_230_1" ,dest_type = 1 ,dest_window_id = 231 ,func_code = 0},

	  }
	},
	[231] = {
	parent_id = 230,
	window_type = 1,
	npc_talk ="#td_1062_dialog_accept_npctalk_231",
	buttons = {
        { player_talk = "#td_1062_dialog_accept_player_talk_231_1" ,dest_type = 1 ,dest_window_id = 232 ,func_code = 0},

	  }
	},
	[232] = {
	parent_id = 231,
	window_type = 3,
	npc_talk ="#td_1062_dialog_accept_npctalk_232",
	buttons = {
        { player_talk = "#td_1062_dialog_accept_player_talk_232_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 3},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1062_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1062_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_1062_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 233 ,func_code = 0},

  }
},
	[233] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_1062_dialog_end_npctalk_233",
	buttons = {
        { player_talk = "#td_1062_dialog_end_player_talk_233_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}