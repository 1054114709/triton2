task = {
  id = 3034,    --����ID
  kind = 0,    --��������
  color = 0,    --������ɫ
  name = "#td_3034_name",  
  desc = "#td_3034_desc",  
  dest = "#td_3034_dest",  
  section = "#td_3034_section",  
  give_npc = 36083,    --����NPC
  give_map_id = 5,    --����NPC���ڵĵ�ͼID
  recv_npc = 35947,    --����NPC
  recv_map_id = 63,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 1,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 0,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 45,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 4,    --��������
  task_hard = 3,    --�������ͼ��Ѷ�
  trace={ 
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 5,    --���������ĵ�ͼID
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
	{func=check_level, args={min_level = 45,max_level = 200}},
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
	{func=award_expr, args={expr = 95000}},
	{func=award_money, args={money = 2000}},
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
	npc_talk ="#td_3034_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_3034_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 305 ,func_code = 0},

	  }
	},
	[305] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_3034_dialog_accept_npctalk_305",
	buttons = {
        { player_talk = "#td_3034_dialog_accept_player_talk_305_1" ,dest_type = 1 ,dest_window_id = 306 ,func_code = 0},

	  }
	},
	[306] = {
	parent_id = 305,
	window_type = 3,
	npc_talk ="#td_3034_dialog_accept_npctalk_306",
	buttons = {
        { player_talk = "#td_3034_dialog_accept_player_talk_306_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 3},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_3034_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_3034_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_3034_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 307 ,func_code = 0},

  }
},
	[307] = {
	parent_id = 3,
	window_type = 1,
	npc_talk ="#td_3034_dialog_end_npctalk_307",
	buttons = {
        { player_talk = "#td_3034_dialog_end_player_talk_307_1" ,dest_type = 1 ,dest_window_id = 308 ,func_code = 0},

  }
},
	[308] = {
	parent_id = 307,
	window_type = 2,
	npc_talk ="#td_3034_dialog_end_npctalk_308",
	buttons = {
        { player_talk = "#td_3034_dialog_end_player_talk_308_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}