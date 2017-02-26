local family_close_time = 30 * 60 * 1000;					--�ر�ʱ��
local family_close_wait_time = 2 * 60 * 1000;				--ʤ����ر�ʱ��
local begin_time = 2 * 60 * 1000;
local FAMILY_DATA_KEY =
{
	FAMILY_RESOURCE1	= 0,	--������Դ
	FAMILY_RESOURCE2	= 1,	--�ط���Դ
	FAMILY_BOX1		= 2,	--��¯1
	FAMILY_BOX2		= 3,	--��¯2	
	FAMILY_BOX3		= 4,	--��¯3
	FAMILY_STATE		= 5,	--ʤ��״̬ 	
};
local boxindex1 = 65005;		--��¯1����
local boxindex2 = 65004;		--��¯2����
local boxindex3 = 65006;		--��¯3����
local boxtemp1 = 45141;		--��¯1ģ��
local boxtemp2 = 45142;		--��¯2ģ��
local boxtemp3 = 45143;		--��¯3ģ��
local num1 = 0;		--������¯��
local num2 = 0;		--�ط���¯��
local incrate1 = 1;		--������1
local incrate2 = 5;		--������1
local resourcemax = 3000;	--��Դ���ֵ
local box1 = 0;		--��¯1
local box2 = 0;		--��¯2
local box3 = 0;		--��¯3
local state = 0;		--ʤ��״̬ 
local killrate = 5;		--ɱ����������
local buff1 = 50052;		--���ӵ�buff1
local buff2 = 50054;		--���ӵ�buff2
local time = 0;		--ʣ�࿪ʼʱ��

local function create_ogre( vRepetionID, vParame )
	if boxindex1 == vParame.index then
		ObserverMachinery( vRepetionID, vParame.entityid );
	end
	if boxindex2 == vParame.index then
		ObserverMachinery( vRepetionID, vParame.entityid );
	end
	if boxindex3 == vParame.index then
		ObserverMachinery( vRepetionID, vParame.entityid );
	end	
end

local function relive( repetion_index, repetion_id, args, loop_index )
	PlayerRelive( repetion_id, 1, args.x1, args.y1 );
	PlayerRelive( repetion_id, 2, args.x2, args.y2 );
end

local campid;
local time;
local CampTime =
{
	[ 1 ] = 5,
	[ 2 ] = 6,
};

local function get_num( vRepetionID )
	num1 = 0;
	num2 = 0;
	box1 = GetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_BOX1 );
	box2 = GetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_BOX2 );
	box3 = GetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_BOX3 );
	if box1 == 1 then
		num1 = num1 + 1;
	elseif box1 == 2 then
		num2 = num2 + 1;
	end
	if box2 == 1 then
		num1 = num1 + 1;
	elseif box2 == 2 then
		num2 = num2 + 1;
	end
	if box3 == 1 then
		num1 = num1 + 1;
	elseif box3 == 2 then
		num2 = num2 + 1;
	end
end

local function other_camp( camp )
	if camp == 1 then
		return 2;
	else
		return 1;
	end
end

local function family_end( vRepetionID, vCamp )
	Infor( "family_end" );

	state = GetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_STATE );
	if state == 1 then
		return;
	end
	EventNoticeByCamp( vRepetionID, vCamp, RepetionNoticeEventKind.END, 1, 0 );	
	EventNoticeByCamp( vRepetionID, other_camp( vCamp ), RepetionNoticeEventKind.END, 0, 0 );

    	PlayerRelive( vRepetionID, 1, 3, 73 );
    	PlayerRelive( vRepetionID, 2, 136, 29 );
	
	Infor( "send_notify" );
	SendBattleEndNotifyByFamily( vRepetionID, vCamp );	
	
	TimeBegin( vRepetionID, 4 );
	EventNoticeAll( vRepetionID, RepetionNoticeEventKind.CLOSE, family_close_wait_time, 0 );
	SetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_STATE, 1 );
	
	insert_item_by_camp( vRepetionID, vCamp, 45557, 3, RepetionInsertItemReason.WIN );
	insert_item_by_camp( vRepetionID, other_camp( vCamp ), 45557, 1, RepetionInsertItemReason.LOST );

	--RepetionClose( vRepetionID );
end

local function create_player( vRepetionID, vParame )
	Debug( "family create player, entityid " .. vParame.entityid .. ", charid " .. vParame.charid .. ", camp " ..
		vParame.campid );

	tCount = GetBeginTime( vRepetionID );
	tCount = ( os.time( ) - tCount ) * 1000;

	if tCount < family_close_time then
		EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.CLOSE, family_close_time - tCount, 0 ); 
	end	
	tCount = GetTime( vRepetionID, 1 );
	EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.RELIVE, tCount, 10000 ); 
	get_num( vRepetionID );
	EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.GET, box1, boxtemp1 ); 
	EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.GET, box2, boxtemp2 ); 
	EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.GET, box3, boxtemp3 ); 
	ObserverEntityDeath( vRepetionID, vParame.entityid );
	if vParame.campid == 1 then
		UseSkill( vParame.entityid, vParame.entityid, buff1 );
	end
	if vParame.campid == 2 then
		UseSkill( vParame.entityid, vParame.entityid, buff2 );
	end
	time = GetTime( vRepetionID, 5 );
	if time > 0 then
		EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.COUNT_DOWN, 2, time );
	end
	EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, 0, resourcemax );
end

local function entity_death( vRepetionID, vParame )
	state = GetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_STATE );
	if state == 1 then
		return;
	end

	resource1 = GetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_RESOURCE1 );
	resource2 = GetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_RESOURCE2 );

	if vParame.killedcampid == 1 then
		resource2 = resource2 + killrate;
	end
	if vParame.killedcampid == 2 then
		resource1 = resource1 + killrate;
	end
	SetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_RESOURCE1, resource1 );
	SetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_RESOURCE2, resource2 );
	EventNoticeAll( vRepetionID, RepetionNoticeEventKind.RESOURCE, resource1, resource2 );
	ObserverEntityDeath( vRepetionID, vParame.killedid );	
	if resource2 >= resourcemax then
		family_end( vRepetionID, 2 );
	elseif resource1 >= resourcemax then
		family_end( vRepetionID, 1 );
	end		
end

local function repetion_end( repetion_index, repetion_id, args, index )
	box1 = 0;
	box2 = 0;
	box3 = 0;
	resource1 = 0;
	resource2 = 0;	
	state = GetIntData( repetion_id, FAMILY_DATA_KEY.FAMILY_STATE );
	if state == 2 then
		return;
	end
	RepetionClose( repetion_id );
end

local function family_campx_lost( repetion_index, repetion_id, args, index )
	resource1 = GetIntData( repetion_id, FAMILY_DATA_KEY.FAMILY_RESOURCE1 );
	resource2 = GetIntData( repetion_id, FAMILY_DATA_KEY.FAMILY_RESOURCE2 );
	if resource1 > resource2 then
		family_end( repetion_id, 1 );
	end
	if resource1 < resource2 then
		family_end( repetion_id, 2 );
	end
	if resource1 == resource2 then
		family_end( repetion_id, 2 );
	end
end

local function family_camp1_lost( repetion_index, repetion_id, args, index )
	Infor( "Camp1 lost" );
	family_end( repetion_id, 2 );
end

local  function family_camp2_lost( repetion_index, repetion_id, args, index )
	Infor( "Camp2 lost" );
	family_end( repetion_id, 1 );
end

local function changeresource( repetion_index, repetion_id, args, index )
	state = GetIntData( repetion_id, FAMILY_DATA_KEY.FAMILY_STATE );
	if state == 1 then
		return;
	end
	get_num( repetion_id );
	resource1 = GetIntData( repetion_id, FAMILY_DATA_KEY.FAMILY_RESOURCE1 );
	resource2 = GetIntData( repetion_id, FAMILY_DATA_KEY.FAMILY_RESOURCE2 );
	if num1 == 3 then
		resource1 = resource1 + incrate2;
		SetIntData( repetion_id, FAMILY_DATA_KEY.FAMILY_RESOURCE1, resource1 );
	else
		resource1 = resource1 + incrate1 * num1;
		SetIntData( repetion_id, FAMILY_DATA_KEY.FAMILY_RESOURCE1, resource1 );
	end
 	if num2 == 3 then
		resource2 = resource2 + incrate2;
		SetIntData( repetion_id, FAMILY_DATA_KEY.FAMILY_RESOURCE2, resource2 );
	else
		resource2 = resource2 + incrate1 * num2;
		SetIntData( repetion_id, FAMILY_DATA_KEY.FAMILY_RESOURCE2, resource2 );
	end
	EventNoticeAll( repetion_id, RepetionNoticeEventKind.RESOURCE, resource1, resource2 );
	if resource2 >= resourcemax then
		family_end( repetion_id, 2 );
	elseif resource1 >= resourcemax then
		family_end( repetion_id, 1 );
	end
end

local function machinery_spring( vRepetionID, vParame )
	box1 = GetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_BOX1 );
	box2 = GetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_BOX2 );
	box3 = GetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_BOX3 );
	if vParame.index == boxindex1 then
		if box1 ~= vParame.campid then
			SetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_BOX1, vParame.campid );
			EventNoticeAll( vRepetionID, RepetionNoticeEventKind.GET, vParame.campid, boxtemp1 );
		end		
	elseif vParame.index == boxindex2 then
		if box2 ~= vParame.campid then
			SetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_BOX2, vParame.campid );
			EventNoticeAll( vRepetionID, RepetionNoticeEventKind.GET, vParame.campid, boxtemp2 );
		end
	elseif vParame.index == boxindex3 then
		if box3 ~= vParame.campid then
			SetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_BOX3, vParame.campid );
			EventNoticeAll( vRepetionID, RepetionNoticeEventKind.GET, vParame.campid, boxtemp3 );
		end
	end		
end

local function force_close( vRepetionID, vParame )
	Infor( "force_close1" );
	state = GetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_STATE );
	Infor( "state " .. state );
	if state == 1 or state == 2 then
		return;
	end	
	SetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_STATE, 0 );
	Infor( "force_close2" );
	family_end( vRepetionID, 2 );
	SetIntData( vRepetionID, FAMILY_DATA_KEY.FAMILY_STATE, 2 );		
end

local function begin_battle( repetion_index, repetion_id, args, loop_index )
	EventNoticeAll( repetion_id, RepetionEventKind.COUNT_DOWN_END, 2, 0 );
	DestroyAliveTempOgre( repetion_id, 52433, 0 );
end


-- ������������
repetion = 
{
	baseinfo = 
	{
		repetion_index = RepetionID.FAMILY,
		playercountmax = 40,		-- �����������
		mapid = { 66 },			-- ������ͼID
		taskid = 0,			-- ���븱����ǰ������
		posx = 94,				-- ��ʱ����
		posy = 124,				-- ��ʱ����
		pernumber = 3,			-- ÿ����븱���Ĵ����� 0-����
		minlevel = 20,			-- ��ͽ���ȼ�
		maxlevel = 110,
		unrelive = 1,

		-- �����Ϣ
		team = 
		{
			teamin = false,		-- �Ƿ���ӽ��룻 ture-��Ҫ���; false - �������
			count = 1,			-- �����������
		},
		

		backpos = 
		{
			mapid = 1,			-- ��ʱ����
			posx = 33,			-- ��ʱ����	
			posy = 13			-- ��ʱ����
		},
	},


    battle =
    {
        camp =
        {
            { campid = 1, posx = 3, posy = 73 },
            { campid = 2, posx = 136, posy = 29 }
        },

        level =
        {
            { levelmin = 10,    levelmax = 0 },
        },          
    },
	-- ��ʱ��
	timer = 
	{ 			
		{
			kind = RepetionTimeBeginKind.START_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = 15000,
			loop = 0,
			func = relive,
			args = { x1 = 3, y1 = 73, x2 = 136, y2 = 29 }
		},
		{
			kind = RepetionTimeBeginKind.START_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = 500,
			loop = 0,
			func = changeresource,
			args = { }
		},
		{
			kind = RepetionTimeBeginKind.START_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = family_close_time,
			loop = 1,
			func = family_campx_lost,
			args = { }
		},
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = family_close_wait_time,
			loop = 1,
			func = repetion_end,
			args = { }
		},
		{
			kind = RepetionTimeBeginKind.START_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = begin_time,
			loop = 1,
			func = begin_battle,
			args = { }
		}

	},
	event = 
	{
		[ RepetionEventKind.OGRE_CREATE ] = { func = create_ogre },
		[ RepetionEventKind.PLAYER_CREATE ] = { func = create_player },
		[ RepetionEventKind.OGRE_DEATH ] = { func = entity_death },
		[ RepetionEventKind.BOX_MACHINERY_SPING ] = { func = machinery_spring },
		[ RepetionEventKind.CLOSE_EVENT ] = { func = force_close },
	},
}


