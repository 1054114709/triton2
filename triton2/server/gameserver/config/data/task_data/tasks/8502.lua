task = {
  id = 8502,    --����ID
  kind = 0,    --��������
  color = 0,    --������ɫ
  name = "#td_8502_name",  
  desc = "#td_8502_desc",  
  dest = "#td_8502_dest",  
  section = "#td_8502_section",  
  give_npc = 36098,    --����NPC
  give_map_id = 13,    --����NPC���ڵĵ�ͼID
  recv_npc = 36098,    --����NPC
  recv_map_id = 13,    --����NPC���ڵĵ�ͼID
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
  send_npc_id = 39966,    --Ҫ���͵�NPC
  max_gird = 20,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 16,    --��������
  task_hard = 3,    --�������ͼ��Ѷ�
  trace={ 
	"#td_8502_trace1",
	"#td_8502_trace2",
  }; 
  max_send_time = 5,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 0,    --���������ĵ�ͼID
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
  npc_waypoints = {{x=66,y=59,map=13},{x=61,y=63,map=13},{x=60,y=66,map=13},{x=59,y=66,map=13},{x=59,y=69,map=13},{x=56,y=69,map=13},{x=54,y=71,map=13},{x=54,y=73,map=13},{x=49,y=73,map=13},{x=49,y=79,map=13},{x=47,y=79,map=13},{x=47,y=83,map=13}};
  drop_items = {};   --�������
  --����������
  accept_cond = 
  {
	{func=check_level, args={min_level = 20,max_level = 200}},
	{func=check_metier, args={metier = 2}},
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
	{func=check_send_npc, args={id = 39966}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr_in_loop, args={unused = 0}},
	{func=award_money_in_loop, args={unused = 0}},
};
  --����������
  accept_awards = 
  {
	{func=start_send_npc, args={nouse = 0}},
};
  --�Ի�
  dialog =   {
  --������Ի�
	[1] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_8502_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_8502_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 4 ,func_code = 3},

	  }
	},
	[4] = {
	parent_id = 1,
	window_type = 3,
	npc_talk ="#td_8502_dialog_accept_npctalk_4",
	buttons = {
        { player_talk = "#td_8502_dialog_accept_player_talk_4_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 3},

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_8502_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_8502_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_8502_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 5 ,func_code = 0},

  }
},
	[5] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_8502_dialog_end_npctalk_5",
	buttons = {
        { player_talk = "#td_8502_dialog_end_player_talk_5_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}