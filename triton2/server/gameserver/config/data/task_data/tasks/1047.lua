task = {
  id = 1047,    --����ID
  kind = 7,    --��������
  color = 4,    --������ɫ
  name = "#td_1047_name",  
  desc = "#td_1047_desc",  
  dest = "#td_1047_dest",  
  section = "#td_1047_section",  
  give_npc = 35945,    --����NPC
  give_map_id = 60,    --����NPC���ڵĵ�ͼID
  recv_npc = 35945,    --����NPC
  recv_map_id = 60,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 0,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 1048,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 25,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 1,    --��������
  task_hard = 5,    --�������ͼ��Ѷ�
  trace={ 
	"#td_1047_trace1",
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 60,    --��ʾ�ѽ�����ĵ�ͼID
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
  give_items = {{id=34109, n=1}};   --���ŵ���
  --����NPC·��
  npc_waypoints = {};
  drop_items = {};   --�������
  --����������
  accept_cond = 
  {
	{func=check_before_task, args={task_id = 1046}},
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
	{func=check_many_orges_by_killed, args={id1 = 44895,id2 = 44896,id3 = 0,id4 = 0,id5 = 0,n = 30}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 62000}},
	{func=award_money, args={money = 7500}},
	{func=award_items_by_metier, args={id = 43171,n = 1,metier = 4,is_free = 0}},
	{func=award_items_by_metier, args={id = 43171,n = 1,metier = 5,is_free = 0}},
	{func=award_items_by_metier, args={id = 43170,n = 1,metier = 2,is_free = 0}},
	{func=award_items_by_metier, args={id = 43170,n = 1,metier = 3,is_free = 0}},
	{func=award_items_by_metier, args={id = 43169,n = 1,metier = 1,is_free = 0}},
	{func=award_items_by_metier, args={id = 43169,n = 1,metier = 6,is_free = 0}},
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
	npc_talk ="#td_1047_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_1047_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 159 ,func_code = 0},

	  }
	},
	[159] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_1047_dialog_accept_npctalk_159",
	buttons = {
        { player_talk = "#td_1047_dialog_accept_player_talk_159_1" ,dest_type = 1 ,dest_window_id = 160 ,func_code = 0},

	  }
	},
	[160] = {
	parent_id = 159,
	window_type = 1,
	npc_talk ="#td_1047_dialog_accept_npctalk_160",
	buttons = {
        { player_talk = "#td_1047_dialog_accept_player_talk_160_1" ,dest_type = 1 ,dest_window_id = 161 ,func_code = 0},

	  }
	},
	[161] = {
	parent_id = 160,
	window_type = 3,
	npc_talk ="#td_1047_dialog_accept_npctalk_161",
	buttons = {
        { player_talk = "#td_1047_dialog_accept_player_talk_161_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 3},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1047_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1047_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_1047_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 162 ,func_code = 0},

  }
},
	[162] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_1047_dialog_end_npctalk_162",
	buttons = {
        { player_talk = "#td_1047_dialog_end_player_talk_162_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}