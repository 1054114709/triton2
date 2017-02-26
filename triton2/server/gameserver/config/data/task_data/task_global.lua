---------------------------Global Data---------------------------
-- ������������ (id ������ID�ĵ�һλ) ע�⣺���˳�������������־�����ʾ˳��

ETaskShowType =
{
	{ id=0x0001, task_type="#task_type_name_0x0001" },
	{ id=0x0100, task_type="#task_type_name_0x0100" },
	{ id=0x0008, task_type="#task_type_name_0x0008" },
	{ id=0x0004, task_type="#task_type_name_0x0004" },
	{ id=0x1000, task_type="#task_type_name_0x1000" },
	{ id=0x0040, task_type="#task_type_name_0x0040" },
	{ id=0x0002, task_type="#task_type_name_0x0002" },
	{ id=0x0010, task_type="#task_type_name_0x0010" },
	{ id=0x0020, task_type="#task_type_name_0x0020" },
	{ id=0x0024, task_type="#task_type_name_0x0024" },
	{ id=0x0080, task_type="#task_type_name_0x0080" },
	{ id=0x0200, task_type="#task_type_name_0x0200" },
	{ id=0x0400, task_type="#task_type_name_0x0400" },
	{ id=0x0800, task_type="#task_type_name_0x0800" },
	{ id=0x2000, task_type="#task_type_name_0x2000" },
	{ id=0x4000, task_type="#task_type_name_0x4000" },
};

	EButtonType =
	{
		TYPE_WINDOW = 1,				-- ����һ���´���
		TYPE_FUNC = 2,					-- ����ĳ�ֹ���
	};

	EWindowType =
	{
		WINDOW_COMMON = 1,				-- ��ͨ
		WINDOW_AWARD =2,				-- ����
		WINDOW_ACCEPT = 3,			-- �������
	}

	EButttonFunc =
	{
		FUNC_RETURN = 1,				-- ����
		FUNC_CLOSE = 2,					-- �ر�
		FUNC_EXTANDTASK = 3,			-- ��������
		FUNC_CALLBACKTASK = 4,			-- �������
		FUNC_ERRORANSWER = 5,  			-- �����д����ѡ��
		FUNC_END_TALK		= 6,			-- �����Ի�
	};
	

ETaskKind =
{
  KIND_SEEKITEM = 1,    --Ѱ��, 
  KIND_SENDMAIL = 2,    --����, 
  KIND_COLLECT = 3,     --�ռ��� 
  KIND_ZAYI = 4,        --����, 
  KIND_MAKEITEM = 5,    --����, 
  KIND_XIULIAN = 6,     --������ 
  KIND_KILLORGE = 7,    --ɱ��
  KIND_REVENGE = 8      --����, 
};

ETaskCtrl =
{
  CTRL_REPEATEABLE = 1,    --����ɹ�����ظ�
  CTRL_CANCELABLE = 2,     --������Ա�ȡ��
  CTRL_RETRYABLE = 3,      --����ʧ�ܺ��������
  CTRL_DIRECTCOMPLETE = 4, --����ֱ�����
  CTRL_FAILONKILLED = 5,   --��ұ�ɱ������Ϊ����ʧ��
  CTRL_SENDNPC    = 6,	-- ����NPCģ��ID
  CTRL_MAXGIRD    = 7,      --  ��������
  CTRL_NAME	   = 8,     --  ��������
  CTRL_OFF_FAIL	   = 9,     -- �Ƿ����������ʧ��
  CTRL_TASKGROUP=10,   -- ������ID
  CTRL_ISAUTOABORT = 11,  -- �Ƿ�ʧ�ܺ��Զ�����
  CTRL_ISSHARE = 12,	 -- �Ƿ���ɺ����ͬ�����
  CTRL_TIMEOUT_TYPE	= 13,	 -- ��ʱ����ʱ�䵽�Ժ�Ĳ���
  CTRL_TIMELMT_TYPE = 14,	 -- ��ʱ�������� ��������Ϸ
  CTRL_IS_DAILY_FAILED=15,	-- �Ƿ����ʧ��
  CTRL_IS_TEAMLOOP=16,	 -- �Ƿ���ӻ�����
  CTRL_TEAM_MEMBER=17,	 -- ������������
  CTRL_FINISH_TIME=18,	 -- �������ʱ������
  CTRL_REFRESH_AWARD=19,	 -- �Ƿ����ˢ��������
  CTRL_TASK_ENDTIME=20,	-- ������ɺ����ò����ٽ�����
  CTRL_TASK_PUBLISHTYPE = 21, --�õ�����ķ�������

};

ETaskState =
{
  STATE_NOT_START = -1,    -- ����û����
  STATE_TASK_BEGIN = 0,    -- �����Ѿ����ܣ�������
  STATE_TASK_COMPLETE = 1, -- �����Ѿ���ɣ�����û�н�
  STATE_TASK_END = 2,      -- �����Ѿ�����
  STATE_TASK_ACTIVE = 3,   -- �����Ѿ�����
};


EPlayerAttr =
{
  PLAYER_MONEY  = 1,
  PLAYER_EXPR   = 2,
  PLAYER_LEVEL  = 3,
  PLAYER_REGION = 4,
  PLAYER_SEX    = 5,
  PLAYER_METIER = 6,
};

EAwardType =
{
	AWARD_EXP = 1, --�������� (n��ʾ����ֵ)
	AWARD_MONEY = 2, --������Ǯ(n��ʾ��Ǯֵ)
	AWARD_ITEM = 3, --������Ʒ(id,n)
	AWARD_TASK = 4, --����һ������(id��ʾ����ID)
	AWARD_TRANS = 5, --�������ͣ�(id��ʾĿ���ͼID��x,y��ʾĿ������)
	AWARD_TELANT=6, --������Ϊ��
	AWARD_HONOR=7, -- ������ѫ
	AWARD_FAMILY_GLORY		=8,     -- �������˼�����ҫֵ
	AWARD_FAMILY_MONEY		=9,    -- ���������Ǯ
	AWARD_FAMILY_CONTRIBUTE	=10,   -- �������˼��幱�׶�
	AWARD_CORPS_GLORY		=11,  --  �������˾�����ҫֵ
	AWARD_CORPS_MONEY		=12,   -- �������Ž�Ǯ
	AWARD_CORPS_CONTRIBUTE	=13,  --  �������˾��Ź��׶�
	
	AWARD_BUILD_RENSHI		=14,  --  ���������
	AWARD_BUILD_HUKOU		=15,  --  ���������
	AWARD_BUILD_LIBIN			=16,  --  �񲿽����
	AWARD_BUILD_GUOFANG		=17,  --  ���������
	AWARD_BUILD_FAYUAN		=18,  --  �̲������
	AWARD_BUILD_GONGCHENG	=19,  --  ���������
	AWARD_WIS_ARTS			=20,  --  �����Ż����飺�Ĳ�
	AWARD_WIS_TACTICS			=21,  --  �����Ż����飺����
	AWARD_WIS_POWER			=22,  --  �����Ż����飺����
	AWARD_WIS_WISDOM			=23,  --  �����Ż����飺ı��
	AWARD_WIS_POLITICS		=24,  --  �����Ż����飺����
	AWARD_WIS_EDUCATE		=25,  --  �����Ż����飺����
	AWARD_BIND_YUANBAO		=26,  --  ������Ԫ��
	AWARD_BUFF				=27,  --  ����BUFF
};

EEventForTask =
{
	--  ����Ҫ��¼���¼�
	--  ��Ҫ���ӵ��¼�
	EVENT_ITEMCHANGE  = 0x18000001,             --  ��Ʒ�仯 Param����Ʒģ��ID �����ӡ� ��ǿ��ˢ�¿ͻ�������
	EVENT_OGREDIE     = 0x18000002,             --  �������� Param�ǹ���ID  �����ӡ���ǿ��ˢ�¿ͻ�������
	--  ����Ҫ���ӵ��¼�
	EVENT_CHANGEMONEY = 0x04000001,             --  ��Ǯ�仯 Param��0
	EVENT_LEVELCHANGE = 0x04000002,             --  �ȼ��仯 Param��0
	EVENT_MOVEREGION  = 0x04000003,             --  ����ƶ� Param��0 ����
	EVENT_PLAYERDIE   = 0x04000004,             --  ������� Param��  ����
	EVENT_NPCDIE      = 0x04000005,             --  NPC����  ����
	EVENT_METIERCHANGE= 0x04000006,			    --  ���ְҵ�ı�  Param��0
	EVENT_TASKCHANGE  = 0x04000007,			    --  �����������ı� Param����Ʒ����ID
	EVENT_KILLLEVELOGRE= 0x04000008,			-- ���ȼ�ɱ��
	EVENT_BUFFCHANGED	= 0x04000009,				-- ���BUFF�ѱ仯

	--  ��Ҫ��¼���¼�(��������������񶼼�¼) (������lua��check��clear)
	EVENT_USEITEM			  = 0x20000001,		--  ���ʹ�õ��� Param����ƷID
	EVENT_SENDNPCCOMPLETE	  = 0x20000002,		--  ��һ���NPC����ָ��λ�� Param��NPCģ��ID
	EVENT_TALKCOMPLETE		  = 0x20000003,		--  �Ի����  Param��NPCģ��ID

	--  ȫ��Ψһ�¼�(֧�ֿ��ٷ��ʣ����32��) (clear��ʱ��Ҫ���,��ȻҲ��Ҫ��¼)
	EVENT_UPEQT				  = 0x64000001,		--  ����ĳ����Ʒ���ھ���ʦ��ʹ����һ������ʯ��
	EVENT_PRODUCE_WEAPON      = 0x64000002,		--  ������������ʹ������������ȸ��������������һ��������
	EVENT_PRODUCE_PREVENT	  = 0x64000003,		--  �����˷��ߣ�ʹ��������߰׻���������������һ�����ߣ�
	EVENT_PRODUCE_DRUG		  = 0x64000004,		--  ������ҩƷ��ʹ�÷��𻨣��ɲΣ�����Ҷ����֥��ѩ������������һ��ҩƷ��
	EVENT_STOVE				  = 0x64000005,		--  ����ĳ����Ʒ������ĳ��װ����������¯�У������������¯�Ļ���ֵ�����ڿ��ܽ�Ԫ��ֵ��
	EVENT_JEWEL				  = 0x64000006,		--  ��Ƕ��ʯ����ͨ���«�����У�����ʯ��Ƕ��װ���ϣ�
	EVENT_CHARSTONE			  = 0x64000007,		--  ��Ƕ����ʯ(��ͨ���«�����У���������ʯ��Ƕ��װ����)
	EVENT_HOLE				  = 0x64000008,		--  Ϊĳ����Ʒ��ף���ͨ���«�����У��û���Ϊĳ����Ʒ��ף�};
	EVENT_SKILL				  = 0x64000009,		-- ѧϰ����
	EVENT_ENDLOOP			  = 0x6400000A,		-- ���һ�ֻ�����

	-- ����ʱ ��Ҫ�����������¼�����������¼�
	EVENT_COMPLETESTORAGETASK 	  = 0x02000001,		-- �����һ�ο�����	
	EVENT_KILLFOREIGNER		  = 0x02000002,		-- ɱ�������
	EVENT_COMPLETE_LOOP		  = 0x02000003,		-- ��ɻ�����
	EVENT_COMPLETE_QUESTION	  = 0x02000004,		-- ���ÿ�մ���
	
	-- ��ʱ�õ��¼����� ���ڴ�Lua����������Ϣ��C++  ��ͨ���߼� ����������߼� ����ע���¼��ĵط�����
	EVENT_PROTECT_FLAG			  = 0x01000001;		-- �������� param1��NPCģ��ID
};

	
MAX_NPC_TASKS = 128; -- NPC���������������
STORAGE_SIZE  = 10; -- ������ÿ�γ�ȡ����
TRAGEDY_TASK_SIZE =81; -- ������������

LOOP_SIZE  = 10; -- ����ÿ�γ�ȡ����

LOOP_START=0;
STORAGE_START=100;
TRAGEDY_START=200; -- ����������200��ͷ�������ļ�
CHAIRMAN_SIZE  = 10; -- ��������ÿ�γ�ȡ����

ETaskTip=
{
	TASKTIP_NONE					= 0,			-- ������û���κι�ϵ
	TASKTIP_ACTIVE					= 1,			-- ��������Խ�
	TASKTIP_BEGIN					= 2,			-- ��������Խ�( û����� )
	TASKTIP_COMPLETE				= 3,				-- ��������Խ�( �Ѿ���� )
	TASKTIP_LOOPTYPE				= 4,			-- have loop task
};

ETaskColor=
{
	WHITE = 1, --��
	BLUE   = 2, --��
	PURPLE= 3, --��
	GOLD   = 4, --��
};

ETaskRefreshType = 
{
	DAY  = 1, -- ÿ��ˢ
	BACK= 2, -- ��������ˢ
	RMB  = 3, --��RMB����ˢ
}

-- ��������
ETaskType =
{
	TASKTYPE_MAIN		= 0x0001,		-- ��������
	TASKTYPE_LATERAL	= 0x0002,		-- ֧������
	TASKTYPE_WEST		= 0x0004,		-- ��������
	TASKTYPE_TRAGEDY	= 0x0008,		-- ��������
	TASKTYPE_LOOP		= 0x0010,		-- ��������
	TASKTYPE_STORAGE	= 0x0020,		-- ��������
	TASKTYPE_PUBLISH	= 0x0024,		-- ��������
	TASKTYPE_SCROLL	= 0x0040,		-- ��������
	TASKTYPE_MINEMAP	= 0x0080,		-- �ر�ͼ����
	TASKTYPE_LUCK		= 0x0100,		-- ��Ե����
	TASKTYPE_FAMILY	= 0x0200,		-- ��������
	TASKTYPE_CORPS	= 0x0400,		-- ��������
	TASKTYPE_ACTIVITY	= 0x0800,		-- �����
	TASKTYPE_NATION	= 0x1000,		-- ��������
	TASKTYPE_CHAIRMAN	= 0x2000,		-- ��������
	TASKTYPE_CAMP		= 0x4000,		-- ��Ӫ����
};

	
ISDEBUG = 1;  -- DEBUG��־����

MAX_INT = 1000000000;
GET_PLAYER_CAMP		= 7;

-- ������ID����  ���������  (��ֵ���ܸģ�������ҵ��ˣ�)
enTaskGroups =
{
	TASKGROUP_START				=   0x00010000,		-- ԭʼ���������ID��ʼ

	TASKGROUP_FAMILY_HONNER		=	0x00010001,		-- ������ҫ����
	TASKGROUP_FAMILY_KILL			=	0x00010002,		-- �����������
	TASKGROUP_FAMILY_SEND			=	0x00010003,		-- ���廤������
        TASKGROUP_FAMILY_CHALANGE              =       0x00010004,             -- ������ս����

	TASKGROUP_CORPS_IN			=	0x00020001,		-- �����ر�����
	TASKGROUP_CORPS_OUT			=	0x00020002,		-- �����ű�����
        TASKGROUP_CORPS_CHALANGE                =       0x00020003,             -- ������ս���� 
	TASKGROUP_MINEMAP				=	0x00040001,		-- �ر�ͼ����
};

-- ͨ��������� ������
enCommonCheckCode =
{
	CHECKTYPE_ISFAMILYMEMBER	=	1	,		-- �Ƿ�����Ա
	CHECKTYPE_ISFAMILYHEAD		=	2	,		-- �Ƿ�����峤
	CHECKTYPE_ISCORPSMEMBER	=	3	,		-- �Ƿ���ų�Ա
	CHECKTYPE_HASTITLE			=	4	,		--  �Ƿ���ĳ�ƺ�   ����1�ǳƺ�ID
	CHECKTYPE_BUFF			=	5	,		-- ��������Ƿ���ĳ��BUFF
	CHECKTYPE_COUNTRY			=	6	,		-- ������
	CHECKTYPE_PUBLISH			=	7	,		-- ��鷢�� �ҿɽӴ���0
	CHECKTYPE_FAMILY_NPC		=	8	,		-- ������ڼ���ռ����NPC
	CHECKTYPE_CORPS_NPC		=	9	,		-- ������ھ���ռ����NPC
	CHECKTYPE_ACTIVITY			=	10	,		-- ���ָ�������
	CHECKTYPE_REG_DATE		=	11	,		-- ���ע����������
	CHECKTYPE_QUES_NUM		=	12	,		-- ���������
	CHECKTYPE_HYDRANGEASTATUS	=	13	,		-- �������״̬
	CHECKTYPE_IN_CAMP			=	14	,		-- ����������Ӫ
	CHECKTYPE_ONLINESECS		=	15	,		-- ����ۼ�����ʱ�� ��
	CHECKTYPE_WEEKNATION		=	16	,		-- ��������
	CHECKTYPE_IN_MY_SELF		=	17	,		-- ���ֻ���ڱ���Ӫ������
	CHECKTYPE_IS_NATIONKILL		=	18	,		-- ����Ƿ��ڹ�̽�ڼ�
	CHECKTYPE_IS_LUANWU		=	19	,		-- ����Ƿ��������ڼ�
	CHECKTYPE_IS_MASTER		=	20	,		-- ����Ƿ�ʦ��
	CHECKTYPE_IS_TEAMHEAD		=	21	,		-- ����Ƿ�ӳ�
	CHECKTYPE_TEAM_MEMBER		=	22	,		-- ����������
	CHECKTYPE_ISVIP_PLAYER		= 	23	,		-- ����Ƿ���VIP
	CHECKTYPE_ISSWORNED_PLAYER	= 	24	,		-- ����Ƿ��Ѿ����
};

-- ͨ�ý��� ����
enCommonAwardCode =
{
	AWARDTYPE_TELANT				=	1	,		-- ������Ϊ��(����1������)
	AWARDTYPE_FAMILY_HONOR		=	2	,		-- �������˼�����ҫֵ
	AWARDTYPE_FAMILY_MONEY		=	3	,		-- ���������Ǯ
	AWARDTYPE_FAMILY_CONTRIBUTE	=	4	,		-- �������˼��幱�׶�
	AWARDTYPE_CORPS_GLORY			=	5	,		-- �������˾�����ҫֵ
	AWARDTYPE_CORPS_MONEY			=	6	,		-- �������Ž�Ǯ
	AWARDTYPE_CORPS_CONTRIBUTE		=	7	,		-- �������˾��Ź��׶�
	AWARDTYPE_TITLE				=	8	,		-- �����ƺ�
	AWARDTYPE_HONOR				=	9	,		-- ������ѫ
	AWARDTYPE_BINDYINGYUANBAO		=	10	,		-- �����󶨵���Ԫ��
	AWARDTYPE_COUNTRYBUILD		=	11	,		-- �������ҽ����
	AWARDTYPE_UPWIS				=	12	,		-- �ϱ��Ż�
	AWARDTYPE_WISEXP				=	13	,		-- �����Ż�����
	AWARDTYPE_CLEARHYDRANGEASTATUS	=	14	,		-- �������״̬
	AWARDTYPE_COMBAT_FAME			=	15	,		-- ������������
	AWARDTYPE_REPE_FAME			=	16	,		-- ������������
	AWARDTYPE_COMMON_FAME		=	17	,		-- ������������
	AWARDTYPE_CORPS_COLLECTACTIVE	=	18	,		-- �������ţ��ɼ�����Ծ��

};

--  ����ģ��ID�������Ǹ�����Ҳ����˵���λ��Զ������Ϊ1�������ƶ�һ��������ڲ�ID ����ʵ���������Ҫ�����Ĺ���
enSpecialID=
{
	SPECIALID_COMPLETESTORAGE			=	0x80000001,	-- �����������
	SPECIALID_KILLFOREIGNER				=	0x80000002,	-- ɱ�������
	SPECIALID_COMPLETELOOPTASK			=	0x80000003,	-- ��ɻ�����
	SPECIALID_COMPLETEQUESTION			=	0x80000004,	-- ���ÿ�մ���
};


---------------------------------------
emPublishCheck = 
{
	CHECK_CORPS_LEVEL		= 1,
	CHECK_CORPS_MONEY		= 2,
	CHECK_CORPS_POSITION	= 3,
};
AllTasks={};
LoopTasks = {}; -- ��¼ȫ�ֻ������ļ�
SortedLoops = {}; -- �����Ļ����� eg: {[1]={1,3,5...} (��ְҵ���� ���水�ȼ�����)
--StorageTasks={};  -- ����洢���ǰ�����ɫ�ȵ�������������
AllStorageTasks={}; -- ������ڴ洢����task�ļ� 1XX�� ���ڶ�ȡȫ������
AllChairManTasks={}; -- ��������
AllChairManIDList={};  -- ��������ID�б�
--TragedyTasks={};
FirstStorageTasks = 0; -- ��һ��������ID
npc_extend_tasks ={};
npc_back_tasks = {};
prob_tasks={}; -- �������еĻᰴ����ˢ������ �����±���Ǵ�ID ��1000���ڵ���Щ��
group_tasks={};  -- ������
beginer_mapid=22; -- ����ɽ��ͼID
DayClearTasks={}; -- ÿ����Ҫ���������ID��
------------------------------------------------------ȫ�ֺ���
-- ������ݵȼ�ɱ�ֵ��¼�ID
function cale_kill_level_ogre_id( min_level, max_level )
	return (min_level or 0)*10000+(max_level or 0);
end

-- ����������෴�ĺ���
function get_ogre_level_by_caledid( caled_id )
	local ret = {low=0, high=0};
	if caled_id == 0 or caled_id == nil then
		return ret;
	end
	ret.high = math.mod( caled_id, 10000 );
	ret.low  = math.ceil(caled_id/10000);
	if ret.high > 0 then
		ret.low = ret.low -1;
	end
	return ret;
end

-- ����Ӫ ���� ��������
week_camp_level_exp=
{
	[-3]=1.6;
	[-2]=1.7;
	[-1]=1.8;
	[0]=1.8;
	[1]=1.8;
	[2]=1.9;
	[3]=2.0;
};

-- ���� �̶�����
luanwu_exp=1.4;

-- ÿ����ӻ��������
team_loop_num=20;
