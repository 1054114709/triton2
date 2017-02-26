task = {
  id = 1081,    --����ID
  kind = 7,    --��������
  color = 4,    --������ɫ
  name = "#td_1081_name",  
  desc = "#td_1081_desc",  
  dest = "#td_1081_dest",  
  section = "#td_1081_section",  
  give_npc = 45625,    --����NPC
  give_map_id = 63,    --����NPC���ڵĵ�ͼID
  recv_npc = 45625,    --����NPC
  recv_map_id = 63,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 0,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 1082,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 39,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 1,    --��������
  task_hard = 6,    --�������ͼ��Ѷ�
  trace={ 
	"#td_1081_trace1",
	"#td_1081_trace2",
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
	{func=check_before_task, args={task_id = 1080}},
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
	{func=check_many_orges_by_killed, args={id1 = 44905,id2 = 44906,id3 = 44907,id4 = 0,id5 = 0,n = 20}},
	{func=check_many_orges_by_killed, args={id1 = 44908,id2 = 44909,id3 = 44910,id4 = 0,id5 = 0,n = 20}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 112500}},
	{func=award_money, args={money = 12250}},
	{func=award_items_by_metier, args={id = 43183,n = 1,metier = 4,is_free = 0}},
	{func=award_items_by_metier, args={id = 43183,n = 1,metier = 5,is_free = 0}},
	{func=award_items_by_metier, args={id = 43182,n = 1,metier = 2,is_free = 0}},
	{func=award_items_by_metier, args={id = 43182,n = 1,metier = 3,is_free = 0}},
	{func=award_items_by_metier, args={id = 43181,n = 1,metier = 1,is_free = 0}},
	{func=award_items_by_metier, args={id = 43181,n = 1,metier = 6,is_free = 0}},
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
	npc_talk ="#td_1081_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_1081_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 266 ,func_code = 0},

	  }
	},
	[266] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_1081_dialog_accept_npctalk_266",
	buttons = {
        { player_talk = "#td_1081_dialog_accept_player_talk_266_1" ,dest_type = 1 ,dest_window_id = 267 ,func_code = 0},

	  }
	},
	[267] = {
	parent_id = 266,
	window_type = 1,
	npc_talk ="#td_1081_dialog_accept_npctalk_267",
	buttons = {
        { player_talk = "#td_1081_dialog_accept_player_talk_267_1" ,dest_type = 1 ,dest_window_id = 268 ,func_code = 0},

	  }
	},
	[268] = {
	parent_id = 267,
	window_type = 3,
	npc_talk ="#td_1081_dialog_accept_npctalk_268",
	buttons = {
        { player_talk = "#td_1081_dialog_accept_player_talk_268_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 3},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1081_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1081_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_1081_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 271 ,func_code = 0},

  }
},
	[271] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_1081_dialog_end_npctalk_271",
	buttons = {
        { player_talk = "#td_1081_dialog_end_player_talk_271_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}