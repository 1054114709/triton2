task = {
  id = 9123,    --����ID
  kind = 0,    --��������
  color = 0,    --������ɫ
  name = "#td_9123_name",  
  desc = "#td_9123_desc",  
  dest = "#td_9123_dest",  
  section = "#td_9123_section",  
  give_npc = 42904,    --����NPC
  give_map_id = 28,    --����NPC���ڵĵ�ͼID
  recv_npc = 42905,    --����NPC
  recv_map_id = 64,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 1,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 9124,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 48,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 20,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 8,    --��������
  task_hard = 7,    --�������ͼ��Ѷ�
  trace={ 
	"#td_9123_trace1",
  }; 
  max_send_time = 10,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 64,    --���������ĵ�ͼID
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
  npc_waypoints = {{x=54,y=53,map=28},{x=54,y=70,map=28},{x=54,y=96,map=28},{x=59,y=96,map=28},{x=59,y=107,map=28},{x=70,y=110,map=28},{x=71,y=107,map=28},{x=71,y=116,map=28},{x=75,y=116,map=28},{x=75,y=121,map=28},{x=25,y=29,map=64},{x=20,y=40,map=64},{x=20,y=47,map=64},{x=18,y=47,map=64},{x=18,y=49,map=64},{x=17,y=49,map=64},{x=17,y=52,map=64},{x=15,y=52,map=64},{x=15,y=54,map=64},{x=14,y=54,map=64},{x=14,y=56,map=64},{x=12,y=56,map=64},{x=12,y=58,map=64},{x=11,y=58,map=64},{x=11,y=59,map=64},{x=9,y=59,map=64},{x=9,y=61,map=64},{x=5,y=61,map=64},{x=5,y=63,map=64},{x=2,y=63,map=64},{x=2,y=79,map=64},{x=40,y=79,map=64},{x=40,y=96,map=64},{x=44,y=96,map=64},{x=44,y=126,map=64},{x=77,y=126,map=64},{x=83,y=135,map=64}};
  drop_items = {};   --�������
  --����������
  accept_cond = 
  {
	{func=check_before_task, args={task_id = 9122}},
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
	{func=check_send_npc, args={id = 42904}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 0}},
	{func=award_money, args={money = 0,is_free = 0}},
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
	npc_talk ="#td_9123_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_9123_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 6 ,func_code = 2},

	  }
	},
	[6] = {
	parent_id = 1,
	window_type = 3,
	npc_talk ="#td_9123_dialog_accept_npctalk_6",
	buttons = {

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_9123_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_9123_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_9123_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 4 ,func_code = 0},

  }
},
	[4] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_9123_dialog_end_npctalk_4",
	buttons = {

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
[42904] = {
	[1] = {
	parent_id = 0,
	window_type = 4,
	npc_talk ="#td_9123_dialog_npc_42904npctalk_1",
	buttons = {
        { player_talk = "#td_9123_dialog_npc_42904player_talk_1_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 10},

  }
},
actions = 
{
	{func=start_send_npc, args={buff_time = 0,buff_id = 0}},
};

};
};
}