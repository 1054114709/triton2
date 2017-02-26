task = {
  id = 10737,    --����ID
  kind = 0,    --��������
  color = 0,    --������ɫ
  name = "#td_10737_name",  
  desc = "#td_10737_desc",  
  dest = "#td_10737_dest",  
  section = "#td_10737_section",  
  give_npc = 70649,    --����NPC
  give_map_id = 62,    --����NPC���ڵĵ�ͼID
  recv_npc = 70649,    --����NPC
  recv_map_id = 62,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
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
  task_type = 2048,    --��������
  task_hard = 18,    --�������ͼ��Ѷ�
  trace={ 
	"#td_10737_trace1",
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 199,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 62,    --���������ĵ�ͼID
  can_invite = 1,    --�Ƿ��������
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
	{func=check_activity_on, args={id = 199}},
	{func=check_today_completedbygroup, args={group_id = 199,max_times = 50}},
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
	{func=check_multi_cond, args={
		{func=check_items_of_bag, args={id = 79190,n = 1}},
		{func=check_items_of_bag, args={id = 79191,n = 1}},
		{func=check_items_of_bag, args={id = 79192,n = 1}},
		{func=check_items_of_bag, args={id = 79193,n = 1}},
		{func=check_items_of_bag, args={id = 79194,n = 1}},
		{func=check_items_of_bag, args={id = 79195,n = 1}},
		{func=check_items_of_bag, args={id = 79196,n = 1}},
		{func=check_items_of_bag, args={id = 79197,n = 1}},
		{func=check_items_of_bag, args={id = 79198,n = 1}},
		{func=check_items_of_bag, args={id = 79199,n = 1}},
		{func=check_items_of_bag, args={id = 79200,n = 1}},
		{func=check_items_of_bag, args={id = 79201,n = 1}},
		{func=check_items_of_bag, args={id = 69363,n = 1}},
		{func=check_items_of_bag, args={id = 69364,n = 1}},
		{func=check_items_of_bag, args={id = 79206,n = 1}},
		{func=check_items_of_bag, args={id = 79204,n = 1}},
		{func=check_items_of_bag, args={id = 79205,n = 1}},
		{func=check_items_of_bag, args={id = 72976,n = 1}},
		{func=check_items_of_bag, args={id = 79202,n = 1}},
		{func=check_items_of_bag, args={id = 79203,n = 1}},
	}};
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr_by_level_table, args={expr = 0}},
	{func=award_money_by_level_table, args={expr = 0}},
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
	npc_talk ="#td_10737_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_10737_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 4 ,func_code = 0},

	  }
	},
	[4] = {
	parent_id = 1,
	window_type = 3,
	npc_talk ="#td_10737_dialog_accept_npctalk_4",
	buttons = {

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_10737_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_10737_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_10737_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 5 ,func_code = 0},

  }
},
	[5] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_10737_dialog_end_npctalk_5",
	buttons = {

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}