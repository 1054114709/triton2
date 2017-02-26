local corps_boss = { };
corps_boss.map_id = 161;
corps_boss.boss_pos={x = 25, y = 25}
corps_boss.end_time = 60 * 1000 * 60 * 4
corps_boss.close_time_left = 60 * 1000 * 10 
local CB_NPC_TYPE = {
    ogre_type   = 0x0002;
    box_type    = 0x0200;
}

local update_player_live_data 





local CB_PLAYER_DATA_KEY =
{
    CB_HAVE_OPEN_BOX = 0,
}

local CB_DATA_KEY = 
{
    CB_CORPS_ID = 0,
}

local MESSAGE_ID =
{
   ID_S2G_END_CORPSBOSS_REPETION = 0xAC16,
}

local CB_BOSS_BOX =
{
    {77214, 77287}, 
    {77215, 77288}, 
    {77216, 77289}, 
    {77217, 77290}, 
    {77218, 77291}, 
    {77219, 77292}, 
    {77220, 77293}, 
    {77221, 77294}, 
    {77222, 77295}, 
    {77223, 77296}, 
    {77224, 77297}, 
    {77225, 77298}, 
    {77226, 77299}, 
    {77227, 77300},   
}


--TIMER

--ս������
local function end_battle( repetion_index, repetion_id, args, loop_index )

end

--last_one ����

local function lo_end( repetion_index, repetion_id, args, loop_index )

end

--��������

local function  close_reption( repetion_index, repetion_id, args, loop_index )
    RepetionClose( repetion_id )
    local message = {} 
    message.battleid = RepetionID.CORPSBOSS
    message.mapid = corps_boss.map_id  
    message.corpsid = GetIntData( repetion_id, CB_DATA_KEY.CB_CORPS_ID )
    SendMessageInLua( MESSAGE_ID.ID_S2G_END_CORPSBOSS_REPETION,  message )
end


--event

--�������
local function create_player( repetion_id, vParame )

    if vParame.new == 1 then 
         SetIntData2Player( repetion_id, vParame.entityid ,CB_PLAYER_DATA_KEY.CB_HAVE_OPEN_BOX  , 0 )
    end


end

local function entity_death( repetion_id, vParame )
    if vParame.killedisplayer == 1 then
        return
    end

--    print("22222222222")
--    print(vParame.tempid)
    table.foreachi(CB_BOSS_BOX, function(i , v)

      if v[1] == vParame.tempid then
            local message = {} 
            message.battleid = RepetionID.CORPSBOSS
            message.mapid = corps_boss.map_id  
            message.corpsid = GetIntData( repetion_id, CB_DATA_KEY.CB_CORPS_ID )
            SendMessageInLua( MESSAGE_ID.ID_S2G_END_CORPSBOSS_REPETION,  message )
	    TimeEnd(repetion_id, 1)
            TimeBegin( repetion_id , 3)

      end
      if v[2] == vParame.tempid then
         SetIntData2Player( repetion_id, vParame.killerid,CB_PLAYER_DATA_KEY.CB_HAVE_OPEN_BOX  , 1 )
      end

      local parame_list = {}
      if v[1] == vParame.tempid then
        parame_list.posx = vParame.killedposx;
        parame_list.posy = vParame.killedposy;
        parame_list.npc_type = CB_NPC_TYPE.box_type;

	for var_i = -3,3,3 do
		parame_list.posx = parame_list.posx + var_i;
		for var_j = -3,3,3 do
			parame_list.posy = parame_list.posy + var_j;
			CreateNpcDynamic( repetion_id,corps_boss.map_id,  v[2], parame_list );
			parame_list.posy = vParame.killedposy;
		end
		parame_list.posx = vParame.killedposx;
	end
	
      end
      if v[2] == vParame.tempid then
	parame_list.posx = vParame.killedposx;
        parame_list.posy = vParame.killedposy
        parame_list.npc_type = CB_NPC_TYPE.box_type;
	CreateNpcDynamic( repetion_id,corps_boss.map_id,  v[2], parame_list )
      end
    end)


end

local function repetion_begin( repetion_id, vParame )
--    SetIntData( repetion_id, LO_DATA_KEY.MAX_KILL_NUM , 0)    
      SetIntData( repetion_id, CB_DATA_KEY.CB_CORPS_ID, vParame.parame2)    
      local parame_list = {}
      parame_list.posx = corps_boss.boss_pos.x;
      parame_list.posy = corps_boss.boss_pos.y;
      parame_list.npc_type = CB_NPC_TYPE.ogre_type;


      CreateNpcDynamic( repetion_id,corps_boss.map_id,  vParame.parame1, parame_list)

end

local function  create_ogre( repetion_id, vParame )

    ObserverEntityDeath( repetion_id , vParame.entityid )
end

local function leave_repetion( repetion_id, vParame )
    
end
function repetion_close( repetion_id, vParame )
end

function player_relive( repetion_id, vParame )
	EntityInsertBuff( repetion_id, vParame.entityid , 77230)
end







-- ������������
repetion = 
{

    baseinfo = 
    {
        repetion_index = RepetionID.CORPSBOSS,
        playercountmax = 240,		-- �����������
        mapid = { corps_boss.map_id  }, --90,			-- ������ͼID
        taskid = 0,			-- ���븱����ǰ������
        posx = 13,				-- ��ʱ����
        posy = 15,				-- ��ʱ����
        pernumber = 0,			-- ÿ����븱���Ĵ����� 0-����
--        minlevel = 50,			-- ��ͽ���ȼ�
--        maxlevel = 110,
        unrelive = 0,
        ontimeopen = 0,                 -- 1��ʱ����  0 ��
        mintimer = 4 *60* 60,
        notlimittime = 1,               -- 1���븱��������ʱ�� 0����

        -- �����Ϣ
        team = 
        {
            teamin = true,		-- �Ƿ���ӽ��룻 ture-��Ҫ���; false - �������
            count = 1,			-- �����������
        },

    },


    -- ��ʱ��
    timer =
    {
        --1
        {   
            kind = RepetionTimeBeginKind.START_BEGIN,
            result = RepetionTimeResultKind.CLOSE,
            time = corps_boss.end_time,
            loop = 1,
            func = close_reption, 
            args = { } ,
	    sync = { kind = RepetionTimeSyncKind.ALL, key = 0 },
        },  
        --2
        {
            kind = RepetionTimeBeginKind.START_BEGIN,
            result = RepetionTimeResultKind.NONE,
            time = corps_boss.end_time,
            loop = 1,
            func = lo_end,
            args = { }
        },

        --3 �����ر� 
        {
            kind = RepetionTimeBeginKind.EVENT_BEGIN,
            result = RepetionTimeResultKind.CLOSE,
            time = corps_boss.close_time_left,
            loop = 1,
            func = close_reption, 
            args = { },
	    sync = { kind = RepetionTimeSyncKind.ALL, key = 0 },
        },
    },


    --�¼�
    event = 
    {
        [ RepetionEventKind.OGRE_DEATH ] = { func = entity_death },
        [ RepetionEventKind.OGRE_CREATE ] = { func = create_ogre },
        [ RepetionEventKind.PLAYER_CREATE ] = { func = create_player },
        [ RepetionEventKind.CLOSE_EVENT] = { func = repetion_close},
        [ RepetionEventKind.BEGIN_REPETION] = { func = repetion_begin},
      --  [ RepetionEventKind.LEAVE_REPETION] = { func = leave_repetion},
        [ RepetionEventKind.PLAYER_RELIVE] = { func = player_relive},
    },
}
