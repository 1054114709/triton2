task = {
  id = 2041,    --����ID
  kind = 3,    --��������
  color = 3,    --������ɫ
  name = "#td_2041_name",  
  desc = "#td_2041_desc",  
  dest = "#td_2041_dest",  
  section = "#td_2041_section",  
  give_npc = 39367,    --����NPC
  give_map_id = 70,    --����NPC���ڵĵ�ͼID
  recv_npc = 39367,    --����NPC
  recv_map_id = 70,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 1,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 2042,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 58,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 2,    --��������
  task_hard = 7,    --�������ͼ��Ѷ�
  trace={ 
	"#td_2041_trace1",
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 70,    --���������ĵ�ͼID
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
  drop_items = {{npc_id=44933 ,item_id=39632 ,n=1 ,p=5000, mapid=70},{npc_id=44934 ,item_id=39632 ,n=1 ,p=5000, mapid=70}};   --�������
  --����������
  accept_cond = 
  {
	{func=check_before_task, args={task_id = 2040}},
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
	{func=check_items_of_bag, args={id = 39632,n = 20}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 80000}},
	{func=award_money, args={money = 10600}},
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
	npc_talk ="#td_2041_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_2041_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 279 ,func_code = 0},

	  }
	},
	[279] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_2041_dialog_accept_npctalk_279",
	buttons = {
        { player_talk = "#td_2041_dialog_accept_player_talk_279_1" ,dest_type = 1 ,dest_window_id = 280 ,func_code = 0},

	  }
	},
	[280] = {
	parent_id = 279,
	window_type = 1,
	npc_talk ="#td_2041_dialog_accept_npctalk_280",
	buttons = {
        { player_talk = "#td_2041_dialog_accept_player_talk_280_1" ,dest_type = 1 ,dest_window_id = 281 ,func_code = 0},

	  }
	},
	[281] = {
	parent_id = 280,
	window_type = 3,
	npc_talk ="#td_2041_dialog_accept_npctalk_281",
	buttons = {

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_2041_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_2041_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_2041_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 282 ,func_code = 0},

  }
},
	[282] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_2041_dialog_end_npctalk_282",
	buttons = {

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}