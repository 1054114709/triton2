task = {
  id = 9701,    --����ID
  kind = 0,    --��������
  color = 0,    --������ɫ
  name = "#td_9701_name",  
  desc = "#td_9701_desc",  
  dest = "#td_9701_dest",  
  section = "#td_9701_section",  
  give_npc = 35953,    --����NPC
  give_map_id = 5,    --����NPC���ڵĵ�ͼID
  recv_npc = 35953,    --����NPC
  recv_map_id = 5,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 1,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 0,    --��������(�Զ�����)
  direct_complete = 0,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 42,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 20,    --����뻤��NPC����������
  is_open_npc = 0,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 8,    --��������
  task_hard = 8,    --�������ͼ��Ѷ�
  trace={ 
	"#td_9701_trace1",
	"#td_9701_trace2",
  }; 
  max_send_time = 10,    --����뿪����NPC���ʱ��(��)
  offline_fail = 1,    --�Ƿ�������������ʧ��
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
  give_items = {{id=43239, n=1}};   --���ŵ���
  --����NPC·��
  npc_waypoints = {{x=34,y=37,map=5},{x=44,y=37,map=5},{x=44,y=36,map=5},{x=46,y=36,map=5},{x=47,y=36,map=5},{x=47,y=38,map=5},{x=48,y=38,map=5},{x=48,y=39,map=5},{x=48,y=55,map=5},{x=61,y=55,map=5},{x=61,y=65,map=5},{x=78,y=65,map=5},{x=78,y=72,map=5},{x=85,y=72,map=5},{x=85,y=67,map=5},{x=100,y=67,map=5},{x=100,y=52,map=5},{x=92,y=52,map=5},{x=92,y=49,map=5},{x=91,y=49,map=5},{x=91,y=47,map=5},{x=89,y=47,map=5},{x=89,y=42,map=5},{x=88,y=42,map=5},{x=88,y=39,map=5},{x=85,y=39,map=5},{x=85,y=36,map=5}};
  drop_items = {};   --�������
  --����������
  accept_cond = 
  {
	{func=check_before_task, args={task_id = 9271}},
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
	{func=check_send_npc, args={id = 43017}},
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
	npc_talk ="#td_9701_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_9701_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 5 ,func_code = 0},

	  }
	},
	[5] = {
	parent_id = 1,
	window_type = 3,
	npc_talk ="#td_9701_dialog_accept_npctalk_5",
	buttons = {

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_9701_dialog_doing_npctalk_2",
	buttons = {

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_9701_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_9701_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 4 ,func_code = 0},

  }
},
	[4] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_9701_dialog_end_npctalk_4",
	buttons = {

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
[43017] = {
	[1] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_9701_dialog_npc_43017npctalk_1",
	buttons = {
        { player_talk = "#td_9701_dialog_npc_43017player_talk_1_1" ,dest_type = 1 ,dest_window_id = 2 ,func_code = 0},

  }
},
	[2] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_9701_dialog_npc_43017npctalk_2",
	buttons = {
        { player_talk = "#td_9701_dialog_npc_43017player_talk_2_1" ,dest_type = 1 ,dest_window_id = 3 ,func_code = 0},

  }
},
	[3] = {
	parent_id = 2,
	window_type = 4,
	npc_talk ="#td_9701_dialog_npc_43017npctalk_3",
	buttons = {
        { player_talk = "#td_9701_dialog_npc_43017player_talk_3_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 10},

  }
},
actions = 
{
	{func=start_send_npc, args={buff_time = 0,buff_id = 0}},
};

};
};
}