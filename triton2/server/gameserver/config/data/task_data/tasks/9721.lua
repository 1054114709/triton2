task = {
  id = 9721,    --����ID
  kind = 0,    --��������
  color = 0,    --������ɫ
  name = "#td_9721_name",  
  desc = "#td_9721_desc",  
  dest = "#td_9721_dest",  
  section = "#td_9721_section",  
  give_npc = 46943,    --����NPC
  give_map_id = 65,    --����NPC���ڵĵ�ͼID
  recv_npc = 46943,    --����NPC
  recv_map_id = 65,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 3600,    --����ʱ��(��)
  cancelable = 1,    --�����ܷ񱻷���
  repeatable = 1,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 0,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 0,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 16384,    --��������
  task_hard = 8,    --�������ͼ��Ѷ�
  trace={ 
	"#td_9721_trace1",
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 4194306,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 1,    --ͬ������Ƿ��������ɹ�
  task_map_id = 65,    --���������ĵ�ͼID
  can_invite = 0,    --�Ƿ��������
  timeout_action = 0,    --��ʱ����ʱ�������״̬
  time_lmt_type = 1,    --��ʱ��������
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
	{func=check_time_part, args={start_hour = 14,start_minu = 0,end_hour = 18,end_minu = 0}},
	{func=check_today_completedbygroup, args={group_id = 4194306,max_times = 1}},
	{func=check_level, args={min_level = 30,max_level = 0}},
  };
  --������������
  publish_cond = 
  {
  };
  --������ʾ����
  show_cond = 
  {
	{func=check_level, args={min_level = 30,max_level = 0}},
  };
  --�������
  complete_cond = 
  {
	{func=check_orges_by_killed, args={id = 57051,n = 1}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr_by_level_table, args={expr = 0}},
	{func=award_money_by_level_table, args={expr = 0}},
	{func=award_honor, args={value = 30}},
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
	npc_talk ="#td_9721_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_9721_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 4 ,func_code = 0},

	  }
	},
	[4] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_9721_dialog_accept_npctalk_4",
	buttons = {
        { player_talk = "#td_9721_dialog_accept_player_talk_4_1" ,dest_type = 1 ,dest_window_id = 5 ,func_code = 0},

	  }
	},
	[5] = {
	parent_id = 4,
	window_type = 3,
	npc_talk ="#td_9721_dialog_accept_npctalk_5",
	buttons = {

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_9721_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_9721_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_9721_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 6 ,func_code = 0},

  }
},
	[6] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_9721_dialog_end_npctalk_6",
	buttons = {

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}