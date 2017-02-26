task = {
  id = 1017,    --����ID
  kind = 2,    --��������
  color = 4,    --������ɫ
  name = "#td_1017_name",  
  desc = "#td_1017_desc",  
  dest = "#td_1017_dest",  
  section = "#td_1017_section",  
  give_npc = 33773,    --����NPC
  give_map_id = 1,    --����NPC���ڵĵ�ͼID
  recv_npc = 33773,    --����NPC
  recv_map_id = 1,    --����NPC���ڵĵ�ͼID
  hard = 0,    --�����Ѷ�
  timer = 0,    --����ʱ��(��)
  cancelable = 0,    --�����ܷ񱻷���
  repeatable = 0,    --����ɹ���ɷ�����
  retryable = 1,    --����ʧ�ܺ�ɷ�����
  fail_on_killed = 0,    --��ұ�ɱ�����Ƿ���Ϊ����ʧ��
  after_task = 0,    --��������(�Զ�����)
  direct_complete = 1,    --�����Ƿ�ֱ�����(������NPC��)
  get_metier_task = 0,    --�Ƿ���ְ����
  task_level = 10,    --������Ӧ��ҵȼ�
  send_npc_id = 0,    --Ҫ���͵�NPC
  max_gird = 0,    --����뻤��NPC����������
  is_open_npc = 1,    --�Ƿ��ڽ�����ʱ���ֺ�NPC����(����������)
  is_fetch = 0,    --�Ƿ�������(Ĭ�Ϸ�)
  task_type = 1,    --��������
  task_hard = 2,    --�������ͼ��Ѷ�
  trace={ 
	"#td_1017_trace1",
	"#td_1017_trace2",
	"#td_1017_trace3",
	"#td_1017_trace4",
	"#td_1017_trace5",
	"#td_1017_trace6",
  }; 
  max_send_time = 0,    --����뿪����NPC���ʱ��(��)
  offline_fail = 0,    --�Ƿ�������������ʧ��
  group_id = 0,    --���������
  is_fail_auto_abort = 0,    --�Ƿ�ʧ��ʱ�Զ�����
  is_share_complete = 0,    --ͬ������Ƿ��������ɹ�
  task_map_id = 1,    --��ʾ�ѽ�����ĵ�ͼID
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
	{func=check_metier, args={metier = 7}},
	{func=check_before_task, args={task_id = 1118}},
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
	{func=check_not_metier, args={metier = 7}},
  };
  --������ɽ���
  awards = 
  {
	{func=award_expr, args={expr = 4000}},
	{func=award_money, args={money = 210}},
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
	npc_talk ="#td_1017_dialog_accept_npctalk_1",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_1_1" ,dest_type = 1 ,dest_window_id = 38 ,func_code = 0},

	  }
	},
	[38] = {
	parent_id = 1,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_38",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_38_1" ,dest_type = 1 ,dest_window_id = 39 ,func_code = 0},

	  }
	},
	[39] = {
	parent_id = 38,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_39",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_39_1" ,dest_type = 1 ,dest_window_id = 40 ,func_code = 0},
        { player_talk = "#td_1017_dialog_accept_player_talk_39_2" ,dest_type = 1 ,dest_window_id = 45 ,func_code = 0},

	  }
	},
	[40] = {
	parent_id = 39,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_40",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_40_1" ,dest_type = 1 ,dest_window_id = 41 ,func_code = 0},
        { player_talk = "#td_1017_dialog_accept_player_talk_40_2" ,dest_type = 1 ,dest_window_id = 44 ,func_code = 0},

	  }
	},
	[41] = {
	parent_id = 40,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_41",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_41_1" ,dest_type = 1 ,dest_window_id = 42 ,func_code = 0},
        { player_talk = "#td_1017_dialog_accept_player_talk_41_2" ,dest_type = 1 ,dest_window_id = 43 ,func_code = 0},

	  }
	},
	[42] = {
	parent_id = 41,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_42",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_42_1" ,dest_type = 1 ,dest_window_id = 50 ,func_code = 0},

	  }
	},
	[43] = {
	parent_id = 41,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_43",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_43_1" ,dest_type = 1 ,dest_window_id = 56 ,func_code = 0},

	  }
	},
	[44] = {
	parent_id = 40,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_44",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_44_1" ,dest_type = 1 ,dest_window_id = 52 ,func_code = 0},

	  }
	},
	[45] = {
	parent_id = 39,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_45",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_45_1" ,dest_type = 1 ,dest_window_id = 46 ,func_code = 0},
        { player_talk = "#td_1017_dialog_accept_player_talk_45_2" ,dest_type = 1 ,dest_window_id = 47 ,func_code = 0},

	  }
	},
	[46] = {
	parent_id = 45,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_46",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_46_1" ,dest_type = 1 ,dest_window_id = 59 ,func_code = 0},

	  }
	},
	[47] = {
	parent_id = 45,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_47",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_47_1" ,dest_type = 1 ,dest_window_id = 48 ,func_code = 0},
        { player_talk = "#td_1017_dialog_accept_player_talk_47_2" ,dest_type = 1 ,dest_window_id = 49 ,func_code = 0},

	  }
	},
	[48] = {
	parent_id = 47,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_48",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_48_1" ,dest_type = 1 ,dest_window_id = 62 ,func_code = 0},

	  }
	},
	[49] = {
	parent_id = 47,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_49",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_49_1" ,dest_type = 1 ,dest_window_id = 65 ,func_code = 0},

	  }
	},
	[50] = {
	parent_id = 42,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_50",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_50_1" ,dest_type = 1 ,dest_window_id = 85 ,func_code = 0},

	  }
	},
	[52] = {
	parent_id = 44,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_52",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_52_1" ,dest_type = 1 ,dest_window_id = 87 ,func_code = 0},

	  }
	},
	[56] = {
	parent_id = 43,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_56",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_56_1" ,dest_type = 1 ,dest_window_id = 86 ,func_code = 0},

	  }
	},
	[59] = {
	parent_id = 46,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_59",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_59_1" ,dest_type = 1 ,dest_window_id = 88 ,func_code = 0},

	  }
	},
	[62] = {
	parent_id = 48,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_62",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_62_1" ,dest_type = 1 ,dest_window_id = 63 ,func_code = 0},

	  }
	},
	[63] = {
	parent_id = 62,
	window_type = 3,
	npc_talk ="#td_1017_dialog_accept_npctalk_63",
	buttons = {

	  }
	},
	[65] = {
	parent_id = 49,
	window_type = 1,
	npc_talk ="#td_1017_dialog_accept_npctalk_65",
	buttons = {
        { player_talk = "#td_1017_dialog_accept_player_talk_65_1" ,dest_type = 1 ,dest_window_id = 66 ,func_code = 0},

	  }
	},
	[66] = {
	parent_id = 65,
	window_type = 3,
	npc_talk ="#td_1017_dialog_accept_npctalk_66",
	buttons = {

	  }
	},
	[85] = {
	parent_id = 50,
	window_type = 3,
	npc_talk ="#td_1017_dialog_accept_npctalk_85",
	buttons = {

	  }
	},
	[86] = {
	parent_id = 56,
	window_type = 3,
	npc_talk ="#td_1017_dialog_accept_npctalk_86",
	buttons = {

	  }
	},
	[87] = {
	parent_id = 52,
	window_type = 3,
	npc_talk ="#td_1017_dialog_accept_npctalk_87",
	buttons = {

	  }
	},
	[88] = {
	parent_id = 59,
	window_type = 3,
	npc_talk ="#td_1017_dialog_accept_npctalk_88",
	buttons = {

	  }
	},
  --������жԻ�
	[2] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1017_dialog_doing_npctalk_2",
	buttons = {
        { player_talk = "#td_1017_dialog_doing_player_talk_2_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 2},

  }
},
  --�������Ի�
	[3] = {
	parent_id = 0,
	window_type = 1,
	npc_talk ="#td_1017_dialog_end_npctalk_3",
	buttons = {
        { player_talk = "#td_1017_dialog_end_player_talk_3_1" ,dest_type = 1 ,dest_window_id = 84 ,func_code = 0},

  }
},
	[84] = {
	parent_id = 3,
	window_type = 2,
	npc_talk ="#td_1017_dialog_end_npctalk_84",
	buttons = {
        { player_talk = "#td_1017_dialog_end_player_talk_84_1" ,dest_type = 2 ,dest_window_id = 0 ,func_code = 4},

  }
},
};
  --�Ի�NPC
  dialog_with_npc = {
};
}