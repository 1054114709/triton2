task = {
  id = 3022,    --����ID
  kind = 3,    --��������
  color = 0,    --������ɫ
  name = "#td_3022_name",  
  desc = "#td_3022_desc",  
  dest = "#td_3022_dest",  
  section = "#td_3022_section",  
  give_npc = 7364,    --����NPC
  give_map_id = 62,    --����NPC���ڵĵ�ͼID
  recv_npc = 7364,    --����NPC
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
  task_level = 27,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 4,    --��������
  task_hard = 3,    --�������ͼ��Ѷ�
  trace={ 
	"#td_3022_trace1",
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 60,    --���������ĵ�ͼID
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
  drop_items = {{npc_id=44895 ,item_id=36021 ,n=1 ,p=4000, mapid=60},{npc_id=44896 ,item_id=36021 ,n=1 ,p=4000, mapid=60}};   --�������
  --����������
  accept_cond = 
  {
	{func=check_level, args={min_level = 27,max_level = 200}},
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
	{func=check_items_of_bag, args={id = 36021,n = 10}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 60000}},
	{func=award_money, args={money = 3800}},
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
	npc_talk ="#td_3022_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_3022_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 287 ,func_code = 0},

	  }
	},
	[287] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_3022_dialog_accept_npctalk_287",
	buttons = {
        { player_talk = "#td_3022_dialog_accept_player_talk_287_1" ,dest_type = 1 ,dest_window_id = 288 ,func_code = 0},

	  }
	},
	[288] = {
	parent_id = 287,
	window_type = 1,
	npc_talk ="#td_3022_dialog_accept_npctalk_288",
	buttons = {
        { player_talk = "#td_3022_dialog_accept_player_talk_288_1" ,dest_type = 1 ,dest_window_id = 289 ,func_code = 0},

	  }
	},
	[289] = {
	parent_id = 288,
	window_type = 3,
	npc_talk ="#td_3022_dialog_accept_npctalk_289",
	buttons = {
        { player_talk = "#td_3022_dialog_accept_player_talk_289_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 3},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_3022_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_3022_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_3022_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 290 ,func_code = 0},

  }
},
	[290] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_3022_dialog_end_npctalk_290",
	buttons = {
        { player_talk = "#td_3022_dialog_end_player_talk_290_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}