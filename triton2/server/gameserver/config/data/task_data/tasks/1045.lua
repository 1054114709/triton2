task = {
  id = 1045,    --����ID
  kind = 3,    --��������
  color = 4,    --������ɫ
  name = "#td_1045_name",  
  desc = "#td_1045_desc",  
  dest = "#td_1045_dest",  
  section = "#td_1045_section",  
  give_npc = 35944,    --����NPC
  give_map_id = 60,    --����NPC���ڵĵ�ͼID
  recv_npc = 35944,    --����NPC
  recv_map_id = 60,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 0,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 1046,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 24,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 1,    --��������
  task_hard = 5,    --�������ͼ��Ѷ�
  trace={ 
	"#td_1045_trace1",
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
  give_items = {};   --���ŵ���
  --����NPC·��
  npc_waypoints = {};
  drop_items = {{npc_id=44893 ,item_id=36006 ,n=1 ,p=5000, mapid=60},{npc_id=44894 ,item_id=36006 ,n=1 ,p=5000, mapid=60}};   --�������
  --����������
  accept_cond = 
  {
	{func=check_before_task, args={task_id = 1044}},
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
	{func=check_items_of_bag, args={id = 36006,n = 15}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 56000}},
	{func=award_money, args={money = 6000}},
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
	npc_talk ="#td_1045_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_1045_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 148 ,func_code = 0},

	  }
	},
	[148] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_1045_dialog_accept_npctalk_148",
	buttons = {
        { player_talk = "#td_1045_dialog_accept_player_talk_148_1" ,dest_type = 1 ,dest_window_id = 149 ,func_code = 0},

	  }
	},
	[149] = {
	parent_id = 148,
	window_type = 1,
	npc_talk ="#td_1045_dialog_accept_npctalk_149",
	buttons = {
        { player_talk = "#td_1045_dialog_accept_player_talk_149_1" ,dest_type = 1 ,dest_window_id = 209 ,func_code = 0},

	  }
	},
	[209] = {
	parent_id = 149,
	window_type = 3,
	npc_talk ="#td_1045_dialog_accept_npctalk_209",
	buttons = {
        { player_talk = "#td_1045_dialog_accept_player_talk_209_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 3},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1045_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1045_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_1045_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 152 ,func_code = 0},

  }
},
	[152] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_1045_dialog_end_npctalk_152",
	buttons = {
        { player_talk = "#td_1045_dialog_end_player_talk_152_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}