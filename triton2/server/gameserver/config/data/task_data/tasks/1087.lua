task = {
  id = 1087,    --����ID
  kind = 2,    --��������
  color = 4,    --������ɫ
  name = "#td_1087_name",  
  desc = "#td_1087_desc",  
  dest = "#td_1087_dest",  
  section = "#td_1087_section",  
  give_npc = 7328,    --����NPC
  give_map_id = 1,    --����NPC���ڵĵ�ͼID
  recv_npc = 7372,    --����NPC
  recv_map_id = 1,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 0,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 1094,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 11,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 1,    --��������
  task_hard = 3,    --�������ͼ��Ѷ�
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
	{func=check_before_task, args={task_id = 1086}},
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
	{func=award_expr, args={expr = 2500}},
	{func=award_money, args={money = 425}},
	{func=award_items_by_metier, args={id = 36043,n = 1,metier = 1}},
	{func=award_items_by_metier, args={id = 36046,n = 1,metier = 2}},
	{func=award_items_by_metier, args={id = 36049,n = 1,metier = 3}},
	{func=award_items_by_metier, args={id = 36055,n = 1,metier = 4}},
	{func=award_items_by_metier, args={id = 36052,n = 1,metier = 5}},
	{func=award_items_by_metier, args={id = 36058,n = 1,metier = 6}},
	{func=award_items, args={id = 36781,n = 1,is_free = 0}},
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
	npc_talk ="#td_1087_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_1087_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 168 ,func_code = 0},

	  }
	},
	[168] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_1087_dialog_accept_npctalk_168",
	buttons = {
        { player_talk = "#td_1087_dialog_accept_player_talk_168_1" ,dest_type = 1 ,dest_window_id = 172 ,func_code = 0},

	  }
	},
	[172] = {
	parent_id = 168,
	window_type = 1,
	npc_talk ="#td_1087_dialog_accept_npctalk_172",
	buttons = {
        { player_talk = "#td_1087_dialog_accept_player_talk_172_1" ,dest_type = 1 ,dest_window_id = 173 ,func_code = 9},

	  }
	},
	[173] = {
	parent_id = 172,
	window_type = 3,
	npc_talk ="#td_1087_dialog_accept_npctalk_173",
	buttons = {
        { player_talk = "#td_1087_dialog_accept_player_talk_173_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 9},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1087_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1087_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_1087_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 171 ,func_code = 0},

  }
},
	[171] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_1087_dialog_end_npctalk_171",
	buttons = {
        { player_talk = "#td_1087_dialog_end_player_talk_171_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}