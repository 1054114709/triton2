task = {
  id = 10118,    --����ID
  kind = 0,    --��������
  color = 0,    --������ɫ
  name = "#td_10118_name",  
  desc = "#td_10118_desc",  
  dest = "#td_10118_dest",  
  section = "#td_10118_section",  
  give_npc = 65281,    --����NPC
  give_map_id = 106,    --����NPC���ڵĵ�ͼID
  recv_npc = 65281,    --����NPC
  recv_map_id = 106,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 600,    --����ʱ��(��)
  cancelable = 1,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 10241,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 108,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 1,    --��������
  task_hard = 4,    --�������ͼ��Ѷ�
  trace={ 
	"#td_10118_trace1",
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 106,    --���������ĵ�ͼID
  can_invite = 0,    --�Ƿ��������
  timeout_action = 1,    --��ʱ����ʱ�������״̬
  time_lmt_type = 0,    --��ʱ��������
  is_redirect_fail = 1,    --�Ƿ���ͼ����ʧ��
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
	{func=check_before_task, args={task_id = 10117}},
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
	{func=check_protect_flag, args={npc_id = 46943}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 0}},
	{func=award_money, args={money = 0,is_free = 0}},
	{func=award_telant, args={money = 0}},
	{func=award_items, args={id = 69217,n = 1,is_free = 0}},
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
	npc_talk ="#td_10118_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_10118_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 4 ,func_code = 0},

	  }
	},
	[4] = {
	parent_id = 1,
	window_type = 3,
	npc_talk ="#td_10118_dialog_accept_npctalk_4",
	buttons = {

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_10118_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_10118_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_10118_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 5 ,func_code = 0},

  }
},
	[5] = {
	parent_id = 3,
	window_type = 1,
	npc_talk ="#td_10118_dialog_end_npctalk_5",
	buttons = {
        { player_talk = "#td_10118_dialog_end_player_talk_5_1" ,dest_type = 1 ,dest_window_id = 6 ,func_code = 0},

  }
},
	[6] = {
	parent_id = 5,
	window_type = 1,
	npc_talk ="#td_10118_dialog_end_npctalk_6",
	buttons = {
        { player_talk = "#td_10118_dialog_end_player_talk_6_1" ,dest_type = 1 ,dest_window_id = 7 ,func_code = 0},

  }
},
	[7] = {
	parent_id = 6,
	window_type = 2,
	npc_talk ="#td_10118_dialog_end_npctalk_7",
	buttons = {

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}