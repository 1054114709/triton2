-- BOSS������(�����������)
local boss_num = 5;
-- INT DATAʹ�ù淶��
-- 1-boss_num : С����ʵ��ID
-- 6-boss_num*2�����ʵ�ʵ��ID
-- ���������£�
local INT_DATA_KEY = 
{
	PIG_KING_ENTITYID = boss_num*2+1,	-- �����ʵ��ID
	JINJIAO_ENTITYID = boss_num*2+2,	-- ���ʵ��ID
	YINJIAO_ENTITYID = boss_num*2+3,	-- ����ʵ��ID
	JINJIAO_DIE_FLAG = boss_num*2+4,	-- ���������־ 1=����
	YINJIAO_DIE_FLAG = boss_num*2+5,	-- ����������־ 1=����
	SMALL_BOSS_DIE_NUM = boss_num*2+6,	-- СBOSS ���������� (M)
	OGRE_DIE_NUM = boss_num*2+7,	-- ��ͨ������������ (N)
	KILLJINJIAOYINJIAO_TIME = boss_num*2+8,	-- �ӽ��븱����ɱ��������ǵ�ʱ��  (T)
	MONSTER_DIE_NUM = boss_num*2+9,	-- ��ɱС��������  (P)
	SPECIAL_OGRE_DIE_NUM = boss_num*2+10,	-- ��ɱ������������  (K)
};

local fb_close_time = 60 * 60 * 1000;				-- �ر�ʱ��
local kill_time = 20 * 60 * 1000;					-- ��ɱ����ʱʱ��
local pawn_disapear_time = 5*1000;				-- ������ʧʱ��
local boss_add_kill_time = 5*60*1000;				-- ÿ�λ�ɱBOSS ���ӵ�ʣ��ʱ��
local end_close_time = 2*60*1000;				-- ɱ����������Ժ󸱱����õĹر�ʱ��
local boss_relive_time = 2*1000;					-- ������Ǹ���ʱ��
local boss_relive_shout_time = 8*1000;				-- ������Ǹ����ǰ�ϻ�ʱ��(�������ϻ���ʼʱ��)

-- ���������� ������ֵ����ö��
local enLianhuadongMarkType = 
{
	MARKTYPE_FB_LEVEL	=	1,	-- �����ȼ�
	MARKTYPE_SAVE_NUM=2,		-- ���������
	MARKTYPE_KILLNUM=3,		-- ɱ������
	MARKTYPE_TIME=4,			-- ͨ��ʱ�䣨�룩
	MARKTYPE_MARK=5,			-- ����
	MARKTYPE_EXTRA_MARK=6,	-- ��������
};

-- BOSS �����б�
local boss_indexs = {91031, 91060, 91071, 91083, 91119};
-- ���ʵ�����ID�б�
local pawn_indexs = {91033, 91068, 91144, 91141, 91122};
-- ���ʵ�ģ��ID�б�
local pawn_tempids = { {55962, 55963, 55964 },
				  {55965, 55966, 55967 },
				  {55974},
				  {55975},
				  {55968, 55969, 55970, 55971, 55972, 55973},
				};
				
-- ��Ҫ������С�ֵ�ģ��ID
local ogre_tempids = {55628, 55629, 55630, 55631, 55632, 55633, 55634, 55635, 55636, 55637 };
				
-- ��Ҫ������������������ID
local special_ogre_indexs = { 91123, 91137 };

-- Ѻ��С���������б�
local monster_indexs = {91138, 91139, 91140, 91142, 91143};
-- ��Ӧˢ������������б�
local box_indexs = {91147, 91152, 91151, 91150, 91149};

-- ���ʸ��Լ���BUFF��skill_id
local pawn_skill_id = 56066;

-- ����ȥ��BUFF��skill_id
local pawn_removebuff_skill_id = 56158;

-- С��ɱ�����õļ���ID
local kill_pawn_skillid = 56157;

-- ��������
local fox_index = 91137;

-- ����·��
local fox_router = 
{
	{ x = 151, y = 62 },
	{ x = 151, y = 74 },
	{ x = 155, y = 79 },
	{ x = 155, y = 171 },
	{ x = 146, y = 180 },
	{ x = 114, y = 180 },
	{ x = 106, y = 168 },
	{ x = 99, y = 158 },
	{ x = 99, y = 136 },
	{ x = 87, y = 136 },
};

-- Ұ������������
local pigking_index = 91123;
local yepigking_index = 91183;

-- �����������
local jinjiao_index=91184;
local yinjiao_index = 91128;

-- ������Ǹ���ϻ���ʱ������
local jinjiao_relife_shout_timer_index = boss_num+2+1;
local yinjiao_relife_shout_timer_index = boss_num+2+2;

local jinjiao_relife_timer_index = boss_num+2+3;
local yinjiao_relife_timer_index = boss_num+2+4;

-- ���յı���
local final_box_index = 91148;

-- ����ID
local paizi_id = 45542;
local paizi_num = 3;
---------------------------------------------------------------------------------------------------------------------------------------------
-- ˽��API
--------------------------------------------
-- ����Ƿ����ʡ�BOSS�� �ǵĻ������±�
local function get_charactor_arr_index( tab, value )
	if tab == nil or value == nil then
		return 0;
	end
	
	for i=1, table.getn(tab) do
		if tab[i] == value then
			return i;
		end
	end
	return 0;
end

-- ���Ӹ���ʣ���ɱʱ��
local function add_kill_time(repetion_id)
	local left_time = GetTime(repetion_id,1);
	if left_time > 0  then 
		local new_time = left_time + boss_add_kill_time;
		Debug("LIANHUADONG-change timer1 to "..new_time);
		ChangeTime( repetion_id, 1, new_time );
	end
end

-- ��ɿɹ���״̬
local function change_to_attackable( entity_id )
Debug( "LIANHUADONG-change_to_attackable entity=".. entity_id );
	ChangePKType( entity_id, 12481 );
end

-- �������
local function dispos_mark(repetion_id)
	local fb_level = GetRepeLevel(repetion_id);
	local pass_time = GetIntData(repetion_id, INT_DATA_KEY.KILLJINJIAOYINJIAO_TIME);
	local kill_small_boss = GetIntData(repetion_id, INT_DATA_KEY.SMALL_BOSS_DIE_NUM);
	local kill_ogre_num = GetIntData(repetion_id, INT_DATA_KEY.OGRE_DIE_NUM)+kill_small_boss; 
	local kill_monster = GetIntData(repetion_id, INT_DATA_KEY.MONSTER_DIE_NUM);
	
	Debug("level="..fb_level.." kill_ogre_num="..kill_ogre_num.." pass_time="..pass_time.." kill_small_boss="..kill_small_boss.." kill_monster="..kill_monster);
	
	local mark = (1/2)*((fb_level/75)^2)*((kill_ogre_num^2/( pass_time/60+45))+kill_small_boss*40+kill_monster*50+100);
	local extra_mark = (fb_level/55)*GetIntData(repetion_id, INT_DATA_KEY.SPECIAL_OGRE_DIE_NUM)*100;
	
	-- ������� �����ͻ��� �ӵ��������
	EventNoticeAll( repetion_id, RepetionNoticeEventKind.TAKE_COUNT, enLianhuadongMarkType.MARKTYPE_FB_LEVEL, fb_level );
	EventNoticeAll( repetion_id, RepetionNoticeEventKind.TAKE_COUNT, enLianhuadongMarkType.MARKTYPE_SAVE_NUM, kill_monster );
	EventNoticeAll( repetion_id, RepetionNoticeEventKind.TAKE_COUNT, enLianhuadongMarkType.MARKTYPE_KILLNUM, kill_ogre_num );
	EventNoticeAll( repetion_id, RepetionNoticeEventKind.TAKE_COUNT, enLianhuadongMarkType.MARKTYPE_TIME, pass_time ); -- �룡��
	EventNoticeAll( repetion_id, RepetionNoticeEventKind.TAKE_COUNT, enLianhuadongMarkType.MARKTYPE_MARK, mark+extra_mark );
	EventNoticeAll( repetion_id, RepetionNoticeEventKind.TAKE_COUNT, enLianhuadongMarkType.MARKTYPE_EXTRA_MARK, extra_mark );

	AddIntData2AllPlayer( repetion_id, 0, mark+extra_mark );
end


-- ������� ����
local function on_fb_end(repetion_id)
	Debug( "LIANHUADONG-on_fb_end" );	
	-- �����������Ǹ��ʱ�� �������Ǹ�����
	TimeEnd( repetion_id, jinjiao_relife_shout_timer_index );
	TimeEnd( repetion_id, yinjiao_relife_shout_timer_index );
	TimeEnd( repetion_id, jinjiao_relife_timer_index );
	TimeEnd( repetion_id, yinjiao_relife_timer_index );
	
	-- ˢ����
	CreateNpc( repetion_id, final_box_index );
	

	local level = GetRepeLevel( repetion_id );
	-- ��������
	insert_item_all( repetion_id, paizi_id, paizi_num, RepetionInsertItemReason.WIN );
	if level >= 80 and level <= 110 then	
		insert_item_all( repetion_id, 66884, 2, RepetionInsertItemReason.WIN );
	end

	AwardFameAll( repetion_id, 3 );
	
	-- ��¼���ʱ��
	local end_time = fb_close_time - GetTime( repetion_id, 2 );
	SetIntData( repetion_id, INT_DATA_KEY.KILLJINJIAOYINJIAO_TIME, end_time/1000 );
	
	-- ����ʱ��
	ChangeTime( repetion_id, 2, end_close_time );

	-- �������
	dispos_mark(repetion_id);
end

-- ɱ����������
local function kill_all_pawns(repetion_id)
	for i = 1,  boss_num do
		-- ɱ����
		UseSkill( GetIntData( repetion_id, i ), GetIntData( repetion_id, boss_num+i ),  kill_pawn_skillid );	
	end
end
---------------------------------------------------------------------------------------------------------------------------------------------
--  �¼���������
local function create_player( vRepetionID, vParame )
	--UseSkill( vParame.entityid, vParame.entityid, 50055 );
	--TimeBegin( vRepetionID, 1 );
end

-- ��������
local function create_ogre( vRepetionID, vParame )
	Debug( "LIANHUADONG-create_ogre index=".. vParame.index.." tempid="..(vParame.tempid or 0 ) );

	-- ������/NPC�ĳ�ʼ������
	-- �����С��
	local 	tIndex = get_charactor_arr_index( monster_indexs, vParame.index );
	if tIndex>0 and tIndex <= boss_num then
		-- ��¼ʵ��ID
		SetIntData( vRepetionID, tIndex, vParame.entityid );
		-- ע��
		ObserverEntityDeath( vRepetionID, vParame.entityid );
		return;
	end
	
	-- �����СBOSS
	tIndex = get_charactor_arr_index( boss_indexs, vParame.index );
	if tIndex>0 and tIndex <= boss_num  then
		-- ע��
		ObserverEntityDeath( vRepetionID, vParame.entityid );
		return;
	end
	
	-- �����С�� ע��
	tIndex = get_charactor_arr_index( ogre_tempids, vParame.tempid );
	if tIndex>0  then
		-- ע��
		ObserverEntityDeath( vRepetionID, vParame.entityid );
		return;
	end
	
	-- ���������� ע��
	tIndex = get_charactor_arr_index( special_ogre_indexs, vParame.index );
	if tIndex>0  then
		-- ע��
		ObserverEntityDeath( vRepetionID, vParame.entityid );
		--return;
	end
	
	-- ���������
	tIndex = get_charactor_arr_index( pawn_indexs, vParame.index );
	if tIndex>0 and tIndex <= boss_num  then
		-- ��¼ʵ��ID
		SetIntData( vRepetionID, boss_num+tIndex, vParame.entityid );
		-- ���ʸ��Լ���BUFF
		UseSkill( vParame.entityid, vParame.entityid, pawn_skill_id );
		return;
	end	
	
	-- ����Ǻ��� ��·
	if  vParame.index == fox_index then
		Debug( "LIANHUADONG-fox start go! index=".. vParame.index );
		NpcPatrol( vRepetionID, vParame.entityid, 1, fox_router );
		return;
	end
	
	-- �����Ұ����� 
	if vParame.index == yepigking_index then
		-- ע��
		ObserverEntityDeath( vRepetionID, vParame.entityid );
		return;
	end
	
	-- ���������� ��¼ʵ��ID
	if vParame.index == pigking_index then
		Debug("LIANHUADONG-PigReg index="..pigking_index.." entityid="..vParame.entityid);
		SetIntData( vRepetionID, INT_DATA_KEY.PIG_KING_ENTITYID, vParame.entityid );
		return;
	end
	
	-- ����ǽ�Ǵ��� ��¼ʵ��ID
	if vParame.index == jinjiao_index then
		SetIntData( vRepetionID, INT_DATA_KEY.JINJIAO_ENTITYID, vParame.entityid );
		SetIntData( vRepetionID, INT_DATA_KEY.JINJIAO_DIE_FLAG, 0 );
		-- ע��
		ObserverEntityDeath( vRepetionID, vParame.entityid );
		--  ��Ǻ���Ϊ���ս���ҵĶ��ܡ�
		EventNoticeAll( vRepetionID, RepetionNoticeEventKind.MSG, vParame.entityid, 2 );

		return;
	end
	
	-- ��������Ǵ��� ��¼ʵ��ID
	if vParame.index == yinjiao_index then
		SetIntData( vRepetionID, INT_DATA_KEY.YINJIAO_ENTITYID, vParame.entityid );
		SetIntData( vRepetionID, INT_DATA_KEY.YINJIAO_DIE_FLAG, 0 );
		-- ע��
		ObserverEntityDeath( vRepetionID, vParame.entityid );
		--  ���Ǻ���Ϊ���ս���ҵĴ�硱
		EventNoticeAll( vRepetionID, RepetionNoticeEventKind.MSG, vParame.entityid, 2 );

		return;
	end
end 

-- ��������
local function entity_death( vRepetionID, vParame )
Debug( "LIANHUADONG-entity_death index=".. vParame.index.." tempid="..(vParame.tempid or 0 ) );
	-- �����BOSS���� 
	local tIndex = get_charactor_arr_index( boss_indexs, vParame.index );
	if tIndex>0 and tIndex <= boss_num  then
		-- ����ʱ��
		add_kill_time(vRepetionID);
		-- ��ӦС����ɿɹ���״̬
		change_to_attackable( GetIntData( vRepetionID, tIndex ) );
		-- ����ǵ����BOSS ��ˢ������� 
		if  tIndex == 5 then
			CreateNpc( vRepetionID, fox_index );
		end
		-- �����Ѿ�������СBOSS������
		local tNowNum = GetIntData( vRepetionID, INT_DATA_KEY.SMALL_BOSS_DIE_NUM )+1;
		SetIntData( vRepetionID, INT_DATA_KEY.SMALL_BOSS_DIE_NUM, tNowNum );
		Debug("LIANHUADONG-NOWNUM="..tNowNum.." bossnum="..boss_num);
		return;
	end
	
	-- �����С������
	tIndex = get_charactor_arr_index( monster_indexs, vParame.index );
	if tIndex>0 and tIndex <= boss_num  then
		if GetTime(vRepetionID,1) > 0 then -- ʣ���ɱʱ�� ������
			--  ��Ӧ������ȥ������BUFF
			UseSkill( GetIntData( vRepetionID, boss_num+tIndex ), GetIntData( vRepetionID, boss_num+tIndex ),  pawn_removebuff_skill_id );
			--  ����˵��
			EventNoticeAll( vRepetionID, RepetionNoticeEventKind.MSG, GetIntData(vRepetionID, boss_num+tIndex), 1 );
			-- ����������ʧ��ʱ��
			TimeBegin( vRepetionID, tIndex+2 );
			-- ����
			local tNowNum = GetIntData( vRepetionID, INT_DATA_KEY.MONSTER_DIE_NUM )+1;
			SetIntData( vRepetionID, INT_DATA_KEY.MONSTER_DIE_NUM, tNowNum );
			if tNowNum == boss_num then -- СBOSSȫɱ����
				TimeEnd(vRepetionID, 1);
			end
		else -- ��ɱ�˸�С��
			local tNowNum = GetIntData( vRepetionID, INT_DATA_KEY.OGRE_DIE_NUM )+1;
			SetIntData( vRepetionID, INT_DATA_KEY.OGRE_DIE_NUM, tNowNum );
		end

		return;
	end
	
	-- Ұ���������
	if vParame.index == yepigking_index then
		-- ���������ɿɹ�����
		change_to_attackable(GetIntData( vRepetionID, INT_DATA_KEY.PIG_KING_ENTITYID));
		return;
	end
	
	-- �������
	if vParame.index == jinjiao_index then
		-- �����������
		SetIntData( vRepetionID, INT_DATA_KEY.JINJIAO_DIE_FLAG, 1 );
		
		--  ��������ǲ���Ҳ���� ���false ����븴�ʱ��
		if GetIntData( vRepetionID, INT_DATA_KEY.YINJIAO_DIE_FLAG ) == 1 then -- ����Ҳ����
			on_fb_end(vRepetionID);
		else
			TimeBegin( vRepetionID, jinjiao_relife_shout_timer_index );
		end
		return;
	end
	
	-- ��������
	if vParame.index == yinjiao_index then
		-- �����������
		SetIntData( vRepetionID, INT_DATA_KEY.YINJIAO_DIE_FLAG, 1 );
		
		--  ��������ǲ���Ҳ���� ���false ����븴�ʱ��
		if GetIntData( vRepetionID, INT_DATA_KEY.JINJIAO_DIE_FLAG ) == 1 then -- ���Ҳ����
			on_fb_end(vRepetionID);
		else
			TimeBegin( vRepetionID, yinjiao_relife_shout_timer_index );
		end
		return;
	end
	
	-- С������
	tIndex = get_charactor_arr_index( ogre_tempids, vParame.tempid );
	if tIndex>0 and tIndex <= table.getn(ogre_tempids)  then
		local tNowNum = GetIntData( vRepetionID, INT_DATA_KEY.OGRE_DIE_NUM )+1;
		SetIntData( vRepetionID, INT_DATA_KEY.OGRE_DIE_NUM, tNowNum );
		return;
	end
	
	-- �����������
	tIndex = get_charactor_arr_index( special_ogre_indexs, vParame.index );
	if tIndex>0 and tIndex <= table.getn(special_ogre_indexs)  then
		local tNowNum = GetIntData( vRepetionID, INT_DATA_KEY.SPECIAL_OGRE_DIE_NUM )+1;
		SetIntData( vRepetionID, INT_DATA_KEY.SPECIAL_OGRE_DIE_NUM, tNowNum );
		return;
	end
end

-- ��ɱBOSS����ʱ��
local function on_kill_boss_timeout( repetion_index, repetion_id, args, loop_index )
	-- ���п���С��ɱ������
	kill_all_pawns(repetion_id);
end

-- ������ʧ ��������
local function on_pawn_disapear( repetion_index, repetion_id, args, loop_index )
Debug( "LIANHUADONG-on_pawn_disapear index=".. args.pawn_index );
	if args.pawn_index == nil or args.pawn_index <= 0 or args.pawn_index > table.getn(pawn_tempids) then
		Error("pawn index error!");
		return;
	end
	
	-- ������ʧ
	for i = 1, table.getn(pawn_tempids[args.pawn_index])  do
		DestroyAliveTempOgre(repetion_id, pawn_tempids[args.pawn_index][i], 1 );
	end
	
	-- ��������	
	CreateNpc( repetion_id, box_indexs[args.pawn_index] );
end

-- ������Ǹ���
local function on_jinjiao_relive( repetion_index, repetion_id, args, loop_index )
	SetIntData( repetion_id, INT_DATA_KEY.JINJIAO_DIE_FLAG, 0 );
	-- ������
	CreateNpc( repetion_id, jinjiao_index );
end

local function on_yinjiao_relive( repetion_index, repetion_id, args, loop_index )
	SetIntData( repetion_id, INT_DATA_KEY.YINJIAO_DIE_FLAG, 0 );
	-- ��������
	CreateNpc( repetion_id, yinjiao_index );
end

-- ������Ǹ���ǰ�ϻ�
local function on_jinjiao_relive_shout( repetion_index, repetion_id, args, loop_index )
	-- ��Ǽ������� �����ȷϻ�
	--  ���Ǻ�������ɣ��ҵĴ�硱
	EventNoticeAll( repetion_id, RepetionNoticeEventKind.MSG, GetIntData(repetion_id, INT_DATA_KEY.YINJIAO_ENTITYID), 1 );
	TimeBegin( repetion_id, jinjiao_relife_timer_index );
end

local function on_yinjiao_relive_shout( repetion_index, repetion_id, args, loop_index )
	-- ���Ǽ������� ����ȷϻ�
	--  ��Ǻ�������ɣ��ҵĶ��ܡ�
	EventNoticeAll( repetion_id, RepetionNoticeEventKind.MSG, GetIntData(repetion_id, INT_DATA_KEY.JINJIAO_ENTITYID), 1 );
	TimeBegin( repetion_id, yinjiao_relife_timer_index );
end

-- �����ر�
local function on_fb_close( repetion_index, repetion_id, args, loop_index )
	-- �������
	dispos_mark(repetion_id);
	
	-- �رգ�
	RepetionClose(repetion_id);
end


---------------------------------------------------------------------------------------------------------------------------------------------
repetion = 
{
	baseinfo = 
	{
		repetion_index = RepetionID.LIANHUADONG,
		playercountmax = 6,		-- 
		mapid = { 92 },
		taskid = 0,			-- into task condition 
		posx = 24,
		posy = 308,
	--	teamin = true,
		pernumber = 2,			-- everday into max number 
		minlevel = 60,
		maxlevel = 120,
		weekpernumber = 7,
		--check_time = 20000,  -- �����������������ʱ�䣬����
		relogin =	1,					-- 1��ʾ������0��ʾ��������
		closetime   = 120,	  -- û����ʱ��ú�ر�
		team = 
		{
			teamin = true,		
			count = 3,			-- team redirect player number less
		},
		
		backpos = 
		{
			mapid = 67,
			posx = 99,
			posy = 20
		},
		open = 
		{
			-- ��, �£��ܣ� �գ� ʱ, �֣� ��
			-- 0 �ǲ�����ʱ�� ����ÿ�µڼ���
			--��һ��ʱ��

			{
				start = { year = 0, month = 0, week = 0, day = 0, hr = 0, minute = 5, sec = 0 },
				finish = { year = 0, month = 0, week = 0, day = 0, hr = 23, minute = 55, sec = 0 }
			},
			-- ���֧�����ʱ��
		}
		
	},

	timer = 
	{ 
		-- ��ɱBOSS����ʱ
		{
			kind = RepetionTimeBeginKind.START_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = kill_time,
			loop = 1,
			func = on_kill_boss_timeout,
			args = { },
			sync = { kind = RepetionTimeSyncKind.ALL, key = 1 }
		},
		-- �����رյ���ʱ
		{
			kind = RepetionTimeBeginKind.START_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = fb_close_time,
			loop = 1,
			func = on_fb_close,
			args = { },
			sync = { kind = RepetionTimeSyncKind.ALL, key = 0 }
		},
		-- ���ʽ����ʧ��ʱ���� (index=1~5)
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = pawn_disapear_time,
			loop = 1,
			func = on_pawn_disapear,
			args = { pawn_index = 1 },
		},
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = pawn_disapear_time,
			loop = 1,
			func = on_pawn_disapear,
			args = { pawn_index = 2 },
		},
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = pawn_disapear_time,
			loop = 1,
			func = on_pawn_disapear,
			args = { pawn_index = 3 },
		},
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = pawn_disapear_time,
			loop = 1,
			func = on_pawn_disapear,
			args = { pawn_index = 4 },
		},
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = pawn_disapear_time,
			loop = 1,
			func = on_pawn_disapear,
			args = { pawn_index = 5 },
		},
		-- ��Ǹ���ϻ�
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = boss_relive_shout_time,
			loop = 1,
			func = on_jinjiao_relive_shout,
			args = { },
		},
		-- ���Ǹ���ϻ�
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = boss_relive_shout_time,
			loop = 1,
			func = on_yinjiao_relive_shout,
			args = { },
		},
		-- ��Ǹ���
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = boss_relive_time,
			loop = 1,
			func = on_jinjiao_relive,
			args = { },
		},
		-- ���Ǹ���
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = boss_relive_time,
			loop = 1,
			func = on_yinjiao_relive,
			args = { },
		},
	},
	event = 
	{
		[ RepetionEventKind.PLAYER_CREATE ] = { func = create_player },
		[ RepetionEventKind.OGRE_CREATE ] = { func = create_ogre },		
		[ RepetionEventKind.OGRE_DEATH ] = { func = entity_death },
	},
}


