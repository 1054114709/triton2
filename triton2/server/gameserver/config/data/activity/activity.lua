ENUM_ACTIVITYS=
{
	HELPID_BAIHUAXIANZI			= 125,  -- �ٻ�����
	HELPID_ONLINEGIFT				= 127,  -- �����ͺ���
	HELPID_ONLINEGIFT2				= 158,  -- �����ͺ���2
};

ENUM_STATE=
{
	ACTIVITY_START = 0,	-- ���ʼ
	ACTIVITY_END = 1,	-- �����
	ACTIVITY_ACTION_GETGIFT = 100, -- ��ȡ����
	ACTIVITY_ACTION_ONCREATE = 200, -- �������
	ACTIVITY_ACTION_LEVELUP = 300, -- �������
};

-- �����ͺ������ñ�
OnlineGiftCfg=
{
	-- ����  ʱ�� ��ƷID
	{ timer=900, item=77263 };
	{ timer=2700, item=77264 };
	{ timer=3600, item=77265 };


--~ 	{ timer=30, item=70879 };
--~ 	{ timer=50, item=70880 };
--~ 	{ timer=90, item=70900 };
--~ 	{ timer=120, item=70881 };
--~ 	{ timer=150, item=70882 };
};

OnlineGiftCfg_level=
{
	-- ����  ʱ�� ��ƷID

        { min_level=5,   timer=30, item=75777 };
        { min_level=7, timer=180, item=41444 };
        { min_level=10, timer=300, item=69473 };
        { min_level=14, timer=300, item=36036 };
        { min_level=19, timer=600, item=64841 };
        { min_level=24, timer=600, item=69139 };
        { min_level=29, timer=900, item=70127 };
        { min_level=34, timer=1200, item=75778 };
        { min_level=39, timer=1800, item=75779 };
        { min_level=44, timer=1800, item=61313 };
        { min_level=47, timer=2400, item=75678 };
        { min_level=50, timer=2400, item=75781 };
};

-- �ͺ���2�� �����͵ȼ�
function get_min_level_for_gift2()
	if OnlineGiftCfg_level == nil or OnlineGiftCfg_level[1] == nil then
		return 0;
	else
		return OnlineGiftCfg_level[1].min_level or 0;
	end
end

-- LUA ��׼�¼�ID  0  ���ʼ 1 �����  
-- Ŀǰ�������壺�ٻ����� 2 ���ʼ� 3 �����
function fire_activity_event( activity_id, event_id, param )
	
	if activity_id==ENUM_ACTIVITYS.HELPID_BAIHUAXIANZI then
		return do_baihua_activitys( event_id, param );
	elseif activity_id==ENUM_ACTIVITYS.HELPID_ONLINEGIFT or activity_id==ENUM_ACTIVITYS.HELPID_ONLINEGIFT2 then
		return do_gift_activitys( event_id, param );
	end	

end

-- �ٻ����ӻ�Ĵ���
function do_baihua_activitys( event_id, param )
	if event_id == 2 then -- ���ʼ� ��������
		local role_id=param.IntParam1;
		local role_name=param.StringParam1;
		if role_id == 0 then
			return 0;
		end
		--�����ʼ�
		local tab={ char_name=role_name, char_id=role_id, id=38, camp_id=param.IntParam2, money=0, item_id1=70809, item_num1=1};
		SendSysMail(tab);
		return 0;
	end
	
	if event_id == 3 then -- ���ʹ�ðٻ���� 
		-- ���ж���Ч�� ��������ʾ����
		local tCreaTime = param.IntParam1;
		if tCreaTime < GetLastMon_Time()-1000 then -- ���1000�� �㹻��
			SendErrNotice( param.IntParam2, -26987);
			return 0;
		end
		-- �жϰ�����
		if GetPlayerBagSpaceNum(param.IntParam2) < 2 then
			SendErrNotice( param.IntParam2, -26986);
			return -1;
		end
		-- ����Ҫ�����������Ʒ��δ������ʱ��
		local inv_tm=GetNextMon_Time();
		-- ����Ҳ��������Ķ���
		local ins_param={ entity_id=param.IntParam2,
		         item_id=70771,
		         num=1,
		         star=0,
		         invalid_time=inv_tm,};
		InsertItem(ins_param);
		
		local camp_id=GetCampID(param.IntParam2);
		if camp_id==1 then -- ����
			ins_param.item_id=70753;
			InsertItem(ins_param);
		elseif camp_id==2 then -- Ǭ��
			ins_param.item_id=70755;
			InsertItem(ins_param);
		elseif  camp_id==3 then -- ����
			ins_param.item_id=70752;
			InsertItem(ins_param);
		else
			ins_param.item_id=70754;
			InsertItem(ins_param);
		end
		return 0;
	end
end

-- �õ�����һ0���time_t
function GetLastMon_Time()
	local ret=os.time();
	local wk=tonumber( os.date("%w", os.time() ) );
	if wk==0 then wk=7;end
	ret = ret - 86400*(wk-1);
	ret = ret - 3600*tonumber( os.date("%H", os.time() ) );
	ret = ret - 60*tonumber( os.date("%M", os.time() ) );
	ret = ret - tonumber( os.date("%S", os.time() ) );
	return ret;
end

-- �õ�����һ0���time_t
function GetNextMon_Time()
	local ret=os.time();
	local wk=tonumber( os.date("%w", os.time() ) );
	if wk==0 then wk=7;end
	wk=7-wk;
	ret = ret + 86400*wk;
	ret = ret + 3600*(23-tonumber( os.date("%H", os.time() ) ));
	ret = ret + 60*(59-tonumber( os.date("%M", os.time() ) ));
	ret = ret + (60-tonumber( os.date("%S", os.time() ) ));
	return ret;
end

-- �����ͺ��� ��߼�
function do_gift_activitys( event_id, param )
	--Log_Error("ER-"..event_id);
	if event_id==ENUM_STATE.ACTIVITY_START then -- ���ʼ��
		if OnlineGiftCfg[1] ~= nil then
			local s_p={
				activity_id=ENUM_ACTIVITYS.HELPID_ONLINEGIFT, 
				state=1, 
				param1=OnlineGiftCfg[1].timer, --ʱ��
				param2=OnlineGiftCfg[1].item, -- ��Ʒ
				notify=true;
				set_time=true;
				}; 
			ChangeAllActivityState(s_p);	
		end
		return 0;
	elseif event_id==ENUM_STATE.ACTIVITY_ACTION_GETGIFT then -- ��ȡ��Ʒ����
		-- param1 ���ʵ��ID
		-- param2 ��ǰ״̬
		-- param3 ��ǰ״̬�ѳ���ʱ�� ��
		local player_entity_id= param.IntParam1;
		local cur_state=param.IntParam2;
		local last_tm=param.IntParam3;
		local activityid=param.IntParam4;
		local player_level=param.IntParam5;
		local gift_type=param.IntParam6;
		
		local cfg_table=nil;
		if activityid == ENUM_ACTIVITYS.HELPID_ONLINEGIFT then
			cfg_table = OnlineGiftCfg;
		elseif activityid == ENUM_ACTIVITYS.HELPID_ONLINEGIFT2 then
			cfg_table = OnlineGiftCfg_level;
		else
			NotifyGetGiftResult(player_entity_id, 100, gift_type);
			return 100;
		end
		
		if cfg_table[cur_state] == nil then
			return 1;
		end
		
		--Log_Error("G:Get:cur"..OnlineGiftCfg[cur_state].timer.."  lsttm:"..last_tm);
		if last_tm < cfg_table[cur_state].timer then 
			NotifyGetGiftResult(player_entity_id, 100, gift_type);
			return 100;
		end
		
		if GetPlayerBagSpaceNum(player_entity_id) < 1 then -- ������
			SendErrNotice(player_entity_id, -26198 );
			NotifyGetGiftResult(player_entity_id, 101, gift_type);
			return 101;
		end
		
		local ins_param={ entity_id=player_entity_id,
			                         item_id=cfg_table[cur_state].item,
			                         num=1,
			                         star=0,
			                         invalid_time=0,};
		InsertItem(ins_param);
		local activity_state=GetActivityState(activityid);
		-- �ͺ���2�� ��Զ���ǿ���
		if activityid == ENUM_ACTIVITYS.HELPID_ONLINEGIFT2  then
			activity_state=1;
		end
		-- ������һ�ּ�ʱ
		if activity_state == 1 then
			if cfg_table[cur_state+1] ~= nil then -- ���ܼ�����ȥ
				local is_notifyed=0;
				if cfg_table[cur_state+1].min_level == nil or ( cfg_table[cur_state+1].min_level ~= nil and player_level>=cfg_table[cur_state+1].min_level ) then
					local s_p={
						entity_id=player_entity_id,
						activity_id=activityid, 
						state=cur_state+1, 
						param1=cfg_table[cur_state+1].timer, --ʱ��
						param2=cfg_table[cur_state+1].item, -- ��Ʒ
						notify=true;
						set_time=true;
						}; 
					NotifyGetGiftResult(player_entity_id, 0, gift_type);	
					ChangeSingleActivityState(s_p);
					is_notifyed=1;
				end
				if activityid == ENUM_ACTIVITYS.HELPID_ONLINEGIFT2  then
					if is_notifyed == 0 then
						NotifyGetGiftResult(player_entity_id, 0, gift_type);	
					end
					return 0;
				else
					return 1;
				end
			else
				if activityid == ENUM_ACTIVITYS.HELPID_ONLINEGIFT then -- һ�ڻ��ͣ
					local s_p={
						entity_id=player_entity_id,
						activity_id= activityid, 
						state=-1,  -- ��ͣ
						param1=0, --ʱ��
						param2=0, -- ��Ʒ
						notify=false;
						set_time=true;
						}; 
					ChangeSingleActivityState(s_p);	
				end
				NotifyGetGiftResult(player_entity_id, 0, gift_type);	
				return 0; -- ����
			end
		else
			if activityid == ENUM_ACTIVITYS.HELPID_ONLINEGIFT then -- һ�ڻ��ͣ
				local s_p={
					entity_id=player_entity_id,
					activity_id=activityid, 
					state=-1,  -- ��ͣ
					param1=0, --ʱ��
					param2=0, -- ��Ʒ
					notify=false;
					set_time=true;
					}; 
				ChangeSingleActivityState(s_p);	
			end
			NotifyGetGiftResult(player_entity_id, 0, gift_type);	
			return 0;
		end
	elseif event_id==ENUM_STATE.ACTIVITY_ACTION_ONCREATE then -- ����
		-- param1 ���ʵ��ID
		-- param2 ��ǰ״̬
		-- param3 ��ǰ״̬�ѳ���ʱ�� ��
		-- param4 �Ƿ��µ�¼		
		local player_entity_id= param.IntParam1;
		local cur_state=param.IntParam2;
		local last_tm=param.IntParam3;
		local is_first=param.IntParam4;
		local cur_activityid=param.IntParam5;
		
		if cur_state == -1 then -- ��Ч״̬ ����
			return 1;
		end		
		--Log_Error("ST-"..cur_state);
		--Log_Error("LST-"..last_tm);
		--Log_Error("DD-"..cur_activityid);
		if cur_state == 0 then -- ����� ��û���� 
			-- �����ʼû
			if cur_activityid == ENUM_ACTIVITYS.HELPID_ONLINEGIFT and GetActivityState(ENUM_ACTIVITYS.HELPID_ONLINEGIFT) == 1 then
				-- ��ʼ�� �����ͻ��� ��ʼ
				if OnlineGiftCfg[1] ~= nil then
					local s_p={
						entity_id=player_entity_id,
						activity_id=ENUM_ACTIVITYS.HELPID_ONLINEGIFT, 
						state=1, 
						param1=OnlineGiftCfg[1].timer, --ʱ��
						param2=OnlineGiftCfg[1].item, -- ��Ʒ
						notify=true;
						set_time=true;
						}; 
					ChangeSingleActivityState(s_p);
				end
			end
			--Log_Error("DD2-"..cur_activityid);
			-- ��鰴�ȼ��� �����ͺ���
			if cur_activityid == ENUM_ACTIVITYS.HELPID_ONLINEGIFT2 and OnlineGiftCfg_level[1] ~= nil and  GetPlayerLevel(player_entity_id) >= OnlineGiftCfg_level[1].min_level   then
				-- ��ʼ�� �����ͻ��� ��ʼ
					local s_p={
						entity_id=player_entity_id,
						activity_id=ENUM_ACTIVITYS.HELPID_ONLINEGIFT2, 
						state=1, 
						param1=OnlineGiftCfg_level[1].timer, --ʱ��
						param2=OnlineGiftCfg_level[1].item, -- ��Ʒ
						notify=true;
						set_time=true;
						}; 
					ChangeSingleActivityState(s_p);
			end
			return 1;
		end
		
		if cur_activityid == ENUM_ACTIVITYS.HELPID_ONLINEGIFT and OnlineGiftCfg[cur_state] == nil then
			return 1;
		end
		
		if cur_activityid == ENUM_ACTIVITYS.HELPID_ONLINEGIFT2 and OnlineGiftCfg_level[cur_state] == nil then
			return 1;
		end
		
		if cur_activityid == ENUM_ACTIVITYS.HELPID_ONLINEGIFT then
			if is_first==1 then -- ��������
				local new_time=0;
				local set_tm=false;
				if OnlineGiftCfg[cur_state].timer > last_tm then
					new_time=OnlineGiftCfg[cur_state].timer ;
					set_tm=true;
				end
				--Log_Error("G:tmer:"..OnlineGiftCfg[cur_state].timer.."  lsttm:"..last_tm);
				-- ���¿�������
				if GetActivityState(ENUM_ACTIVITYS.HELPID_ONLINEGIFT) == 1 or new_time==0 then
					local s_p={
						entity_id=player_entity_id,
						activity_id=ENUM_ACTIVITYS.HELPID_ONLINEGIFT, 
						state=cur_state, 
						param1=new_time, --ʱ��
						param2=OnlineGiftCfg[cur_state].item, -- ��Ʒ
						notify=true;
						set_time=set_tm;
						}; 
					ChangeSingleActivityState(s_p);
				end
				return 1;
			else -- ���
				local new_time=0;
				if OnlineGiftCfg[cur_state].timer > last_tm then
					new_time=OnlineGiftCfg[cur_state].timer - last_tm;
				end
				--Log_Error("G:KF tmr:"..OnlineGiftCfg[cur_state].timer.."  lsttm:"..last_tm);
				local s_p={
					entity_id=player_entity_id,
					activity_id=ENUM_ACTIVITYS.HELPID_ONLINEGIFT, 
					state=cur_state, 
					param1=new_time, --ʱ��
					param2=OnlineGiftCfg[cur_state].item, -- ��Ʒ
					notify=true;
					set_time=false;
					}; 
				ChangeSingleActivityState(s_p);
				return 1;
			end
		elseif cur_activityid == ENUM_ACTIVITYS.HELPID_ONLINEGIFT2 then	 -- ���ȼ��� �����Ƿ�������
				local new_time=0;
				if OnlineGiftCfg_level[cur_state].timer > last_tm then
					new_time=OnlineGiftCfg_level[cur_state].timer - last_tm;
				end
				--Log_Error("G:KF tmr:"..OnlineGiftCfg[cur_state].timer.."  lsttm:"..last_tm);
				local s_p={
					entity_id=player_entity_id,
					activity_id=ENUM_ACTIVITYS.HELPID_ONLINEGIFT2, 
					state=cur_state, 
					param1=new_time, --ʱ��
					param2=OnlineGiftCfg_level[cur_state].item, -- ��Ʒ
					notify=true;
					set_time=false;
					}; 
				ChangeSingleActivityState(s_p);
				return 1;
		end	
	elseif event_id==ENUM_STATE.ACTIVITY_ACTION_LEVELUP then -- ����
		local player_entity_id= param.IntParam1;
		local cur_state=param.IntParam2;
		local last_tm=param.IntParam3; -- �Դ��ϴ�״̬�ı䵽���ڵ�ʱ��
		local cur_activityid=param.IntParam4;
		local is_got=param.IntParam5; -- �Ƿ�����ȡ
		local player_level=param.IntParam6;
		if OnlineGiftCfg_level[cur_state] ~= nil then
			-- ������ڽ����У�ֱ�Ӳ����			
			-- ���û�н����У����������˾Ϳ��� ��Ȼ����� ��Ҫ����ǲ�����ȡ�ˡ��������鷳
			-- ����ȴ���ȡ ֱ�Ӳ����
			if last_tm < OnlineGiftCfg_level[cur_state].timer or is_got==0 then
				return 1;
			end
			
			-- ������µ� ���Կ�����~
			if OnlineGiftCfg_level[cur_state+1] ~= nil then
				if OnlineGiftCfg_level[cur_state+1].min_level <= player_level then -- �����µ�
					local s_p={
						entity_id=player_entity_id,
						activity_id=ENUM_ACTIVITYS.HELPID_ONLINEGIFT2, 
						state=cur_state+1, 
						param1=OnlineGiftCfg_level[cur_state+1].timer, --ʱ��
						param2=OnlineGiftCfg_level[cur_state+1].item, -- ��Ʒ
						notify=true;
						set_time=true;
						}; 
					ChangeSingleActivityState(s_p);	
					return 1;
				end
			end
		end
	end
end
