--- ϵͳAPI����
function min(val1, val2)
if val1 > val2 then
	return val2;
else
	return val1;
end
end

function debug_tab( tab, str )
lua_debug( str or "��ʼ�����");
	table.foreachi(tab, function(i,v)
		lua_debug("debug table: "..i.."---"..v);
	end);
end



function lua_debug(str)
--print("ISDEBUG="..ISDEBUG);
   if ISDEBUG == 1 then
       Debug(str);
   end
end

function lua_error(str)
	Error(str);
end




-------------------------------------------------------------------------------------------------------------------- �����ǹ��ܺ���
-- �õ�NPC�����б�
function get_npc_extend_tasks(npc_id)
  local r = {};
  local t = npc_extend_tasks[npc_id]
  local teamloop={};
  local dailyloop={};
  if t then
    --table.foreachi(t, function(i, v)
     for i = 1, table.getn(t) do
	-- ����Ҫ�� �������񲻳������б���
	--lua_debug("AllTasks[t[i]].task_type="..AllTasks[t[i]].task_type);
	if AllTasks[t[i]] ~= nil and  AllTasks[t[i]].task_type ~= ETaskType.TASKTYPE_CHAIRMAN and check_acceptable(t[i]) then 
	        if AllTasks[t[i]].loop_type ~= nil and AllTasks[t[i]].loop_type ~= 0 then
			if AllTasks[t[i]].loop_type == 1 then table.insert(teamloop, t[i]);end
			if AllTasks[t[i]].loop_type == 2 then table.insert(dailyloop, t[i]);end
		else
			table.insert(r, t[i]); 
		end	
	end
	if i > MAX_NPC_TASKS then break;end;
     end
     if table.getn(teamloop)>0 then
	table.insert(r, teamloop[math.random(table.getn(teamloop))]); 
     end
     if table.getn(dailyloop)>0 then
	table.insert(r, dailyloop[math.random(table.getn(dailyloop))]); 
     end
  end

  return r;
end


-- ����NPCͷ��
function get_npc_tip(npc_id)

local t = npc_back_tasks[npc_id];
local ret = ETaskTip.TASKTIP_NONE;

if t ~= nil and table.getn(t) >0 then
	-- �����������
	for i = 1, table.getn(t) do
		-- ���������Ƿ��ڽ�����
		local task_id = t[i];
		local state = GetTaskState( task_id );
		if  state == ETaskState.STATE_TASK_COMPLETE and ( AllTasks[task_id].recv_camp ==0 or AllTasks[task_id].recv_camp ==nil or  AllTasks[task_id].recv_camp == GetCurCampID()) then
			do return ETaskTip.TASKTIP_COMPLETE; end; -- ���ȼ����
		elseif state == ETaskState.STATE_TASK_BEGIN  then
			ret = ETaskTip.TASKTIP_BEGIN;  -- ���ȼ����
		end
		
		if i > MAX_NPC_TASKS then break;end;
	end
end

   t = npc_extend_tasks[npc_id]
   
  if t ~= nil and table.getn(t) >0 then
	-- ���㷢������
	for i = 1, table.getn(t) do
	
		if  check_acceptable(t[i])  then
			if AllTasks[t[i]].loop_type == 1 then
				do return ETaskTip.TASKTIP_LOOPTYPE;end; 
			else
				ret = ETaskTip.TASKTIP_ACTIVE; 
			end -- ���ȼ�һ��
		end
		
		if i > MAX_NPC_TASKS then break;end;
	end
end

return ret;
end



-- �õ�NPC���������б�
function get_npc_back_tasks(npc_id)
  local r = {};
  local t = npc_back_tasks[npc_id];

  if t then
    table.foreachi(t, function(i, v)
      local task_id = v;
      local state = GetTaskState(task_id) ;
      if state ==  ETaskState.STATE_TASK_COMPLETE and ( AllTasks[task_id].recv_camp ==0 or AllTasks[task_id].recv_camp ==nil or  AllTasks[task_id].recv_camp == GetCurCampID()) then
        table.insert(r, v); 
      end
    end);
  end

  return r;
end

-- ��ʼ������ ���Ϸ���
function init_tasks()
	--local triton_home = os.getenv("TRITON_HOME");
	
	--if triton_home == nil then 
	--	triton_home = "../../.."
	--end
	local dir = CDir("../config/data/task_data/tasks/");
	if dir == nil then
		return false;
	end
  
  local afile = dir:file();
  	if afile == nil then
		return false;
	end
  local tragedy_num = 0;
  
  npc_extend_tasks = {};
  npc_back_tasks    = {};
  
  -- Ϊ�������������� ��ʱ������
  local chairman_tmp_order={};
  local max_order=0;
  
  while afile do
    local npos = string.find(afile, ".lua") - 1;
    local task_id = tonumber(string.sub(afile, 1, npos));
    
    if task_id ~= nil and task_id > 0 then
	if not dofile("../config/data/task_data/tasks/" .. afile) then
	    if task.id ~= task_id then
		lua_error("����ID���ļ�����ƥ�䣡�ļ���ID="..task_id);
	    else
		    if task_id <= 100 then --��������
			      LoopTasks[task_id] = task;
			      lua_debug("���ػ�����[" .. task_id .. "]"..LoopTasks[task_id].name.."  ���");		      
		    elseif task_id > 100 and task_id < 200 then -- ���������
			      AllStorageTasks[task_id] = task;
			      if FirstStorageTasks == 0 then FirstStorageTasks = task_id; end;
			      lua_debug("���ػʰ�����[" .. task_id .. "]  ���");	
--~ 		    elseif task_id > 200 and task_id < 300 then -- �����������
--~ 			      TragedyTasks[task_id] = task;
--~ 			      tragedy_num = tragedy_num+1;
--~ 			      lua_debug("���ؽ�������[" .. task_id .. "]  ���");	
		    elseif task_id > 300 and task_id < 400 then -- ������������
			      AllChairManTasks[task_id] = task;
			      lua_debug("max3=".. task.order_id);
			      if task.order_id ~= nil and task.order_id~=0 then
				  chairman_tmp_order[task.order_id] = task_id;
				  if task.order_id > max_order then
					max_order = task.order_id;
				  end
				  lua_debug("max2=".. task.order_id);
			      end
			    --  if FirstStorageTasks == 0 then FirstStorageTasks = task_id; end;
			      lua_debug("������������[" .. task_id .. "]  ���");				      
		    elseif task_id >= 1000 then --����������������
			      lua_debug("��������[" .. task_id .. "](" .. task.name .. ")���");

		      AllTasks[task_id] = task;
		      -- ע�������õĵȼ�
		      if get_task_type(task) == ETaskType.TASKTYPE_MAIN or get_task_type(task) == ETaskType.TASKTYPE_LATERAL or get_task_type(task) == ETaskType.TASKTYPE_WEST then -- ע�����ߺ�֧������ ��������
			  -- ����ɽ���������񲻲�������
			  if task.task_map_id ~= beginer_mapid then
				RegLevelTask(task_id, task.task_level or 0); 
			  end
		      end
		      
		      -- ע��NPC����
		      if task.give_npc ~= 0 then
			  if npc_extend_tasks[task.give_npc] == nil then
				npc_extend_tasks[task.give_npc] = {};
			  end
			  table.insert( npc_extend_tasks[task.give_npc], task_id );
		      end
		      
		      if task.recv_npc ~= 0 then
			  if npc_back_tasks[task.recv_npc] == nil then
				npc_back_tasks[task.recv_npc] = {};
			  end
			  table.insert( npc_back_tasks[task.recv_npc], task_id );
		      end
		      
		      -- ע��������
		      if  task.group_id ~= nil and task.group_id >0 then
			    if group_tasks[task.group_id] == nil then
				group_tasks[task.group_id] = {};
			    end
			    table.insert( group_tasks[task.group_id] , task.id );
		      end
		      
		      -- ע������  
			local t = task.drop_items;		  
			table.foreachi(t, function(i, v)  
				RegDropTable( { task_id = task.id,  ogre_id=v.npc_id, item_id=v.item_id, n=v.n, p=v.p, maxn=get_collect_items_num_by_id( task.id, v.item_id) } );          
			end);    
			
			-- ����Ѽ������Ƿ��õ���
			local t2 = task.complete_cond;		  
			table.foreachi(t2, function(i, v)  
				if v.func == check_items_of_bag then
					CheckCollectItem( v.args.id, task.id, 0 );    
				end
			end);  

		      -- ע��ÿ�����
		      if task.is_day_clear == 1  then
			   table.insert(DayClearTasks, task.id);
		      end
		    end;
	    end;
	else
	    return false;
	end
    else
         lua_error("*****���棡��������"..string.sub(afile, 1, npos).."ʧ�ܣ������ļ�����");
    end
    afile = dir:file();
  end
  -- ����Ѽ���Ʒ���� ���
  CheckCollectItem( 0, 0, 1 );    
  
  -- ������������
  for i,v in pairs(LoopTasks) do
  	prob_tasks[i] = {};
	for hard=1,8 do
		prob_tasks[i][hard]={};
	end
	for j,k in ipairs(v.list) do
		if not check_task(k,"inti_loops") then return false;end;
		AllTasks[k].loop_id = i;
		lua_debug("init loop sub task"..i..":"..k);		
		if AllTasks[k].task_hard == 0 then
			lua_error("WARN:task "..k.."hard=0");
		else
			table.insert(prob_tasks[i][AllTasks[k].task_hard], k);
			--lua_debug("insert into loop"..i..":"..k.."hard id="..AllTasks[k].task_hard);
		end
	end
	for hard=1,8 do
		lua_debug("loop task "..i.."has hard="..hard.."'s tasks num="..  table.getn(prob_tasks[i][hard]) );
	end
	if v.metier ~= nil then
		if SortedLoops[v.metier] == nil then SortedLoops[v.metier]={};end;
		table.insert( SortedLoops[v.metier], i );
	end		
  end
  
  table.foreach( SortedLoops, function(i,v)
	lua_debug( "���� ��������� ����"..i.."---��"..table.getn(v).."�����������" );
	table.sort(v);
  end);
  
    -- �������������
    -- �ṹ��StorageTasks={ [105]={ [1]={ 6001,6002,6003 } , [2]={5,12,66 } }, [106]={ [1]={ 7,8,9 } , [2]={17,18,19 } } }
  for i,v in pairs(AllStorageTasks) do
        prob_tasks[i] = {};
	-- ����4����ɫ������
	for color = 1, 4 do
		prob_tasks[i][color]={};
	end

	for j,k in ipairs(v.list) do
		if AllTasks[k] ~= nil then
		    table.insert(prob_tasks[i][AllTasks[k].color], k);
		else
		    lua_error("***���ش����Ҳ�������"..k);
		end
		lua_debug("��ʼ��������"..i..":"..k);
		AllTasks[k].storage_id = i;
	end
	InitStaticStorageTask(i);
  end
  
  
    -- ����������������  3XX
    -- �ṹ��StorageTasks={ [105]={ [1]={ 6001,6002,6003 } , [2]={5,12,66 } }, [106]={ [1]={ 7,8,9 } , [2]={17,18,19 } } }
  for i,v in pairs(AllChairManTasks) do
        --prob_tasks[i] = {};
	-- ����4����ɫ������
	--for color = 1, 4 do
	--	prob_tasks[i][color]={};
	--end

	for j,k in ipairs(v.list) do
--~ 		if AllTasks[k] ~= nil then
--~ 		    table.insert(prob_tasks[i][AllTasks[k].color], k);
--~ 		else
--~ 		    lua_error("***���ش����Ҳ�������"..k);
--~ 		end
		lua_debug("��ʼ����������"..i..":"..k);
		if AllTasks[k] == nil then
			lua_error("��������"..k.."("..i..") δ�ҵ�");
		else
			AllTasks[k].chairman_id = i;
		end
	end
	
 end
 
 	-- ��������ID������
	for i=1, max_order do
		if chairman_tmp_order[i] ~= nil then
			lua_debug("��ʼ�����������б�".. chairman_tmp_order[i]);
			table.insert(AllChairManIDList, chairman_tmp_order[i] );
		end
	end
  
    -- ���������������
    --if tragedy_num ~= TRAGEDY_TASK_SIZE then lua_error("����������"..TRAGEDY_TASK_SIZE.."����");end;
  for i=1, TRAGEDY_TASK_SIZE do
	if tragedy_task[TRAGEDY_START+i] == nil then
		lua_error("��������"..TRAGEDY_START+i.."δ����");
	else
		for j,k in ipairs(tragedy_task[TRAGEDY_START+i].list) do
			if check_task(k,"init_tragedy") == true then
			    AllTasks[k].tragedy_id = TRAGEDY_START+i;
			    lua_debug("��ʼ����������"..TRAGEDY_START+i..":"..k);
			end
		end
	end
  end
  
  check_task( start_task, "start_task");
  -- ע����Ҫ���ӵ�NPC
  for i=1, table.getn(task_watch_npc) do
	RegMonitorNpc(task_watch_npc[i] or 0);
  end  
  
  -- ����
  LoadTaskComplete();

  math.randomseed(os.time())
  math.random(100); --û��
  
  return true;
end

function task_version()
  do return TASK_VERSION end
end

function get_collect_items(vTaskID)
  local r = {};

  if check_task(vTaskID,"get_collect_items") == false then return r;end;

  local t = AllTasks[vTaskID].complete_cond;
  table.foreachi(t, function(i, v)  

    if v.func == check_items_of_bag then 

      table.insert(r, v.args);
    end
  end);
  return r; 
end

-- ����ָ��ID�õ���Ҫ�Ѽ��ĵ��ߵ�������û�з���0
function get_collect_items_num_by_id(vTaskID, vItemID)

  local num = 0;
  if check_task(vTaskID,"get_collect_items_num_by_id") == false then return num;end;
  
  local t = AllTasks[vTaskID].complete_cond;
  table.foreachi(t, function(i, v)  
    if v.func == check_items_of_bag and v.args.id == vItemID then 
      num = v.args.n;
      return;
    end
  end);
  
  return num; 
end



-- ����ָ��ID�õ���Ҫɱ���Ĺ����������û�з���0
function get_kill_orges_num_by_id(vTaskID, vOrgeID)
  local ret = {num=0,id=vOrgeID};
  if check_task(vTaskID,"get_kill_orges_num_by_id") == false then return num;end;
  
  local t = AllTasks[vTaskID].complete_cond;
  table.foreachi(t, function(i, v)  
    if v.func == check_orges_by_killed and v.args.id == vOrgeID then 
      ret={num = v.args.n, id = vOrgeID} ; -- Ҫ����ID����Ϊ����ǲ���ɱ�֣�����ID�ʹ���ID��һ����
      lua_debug("�õ�ɱ�֣���������ͨɱ��"..i);
      return 1;
    end
    
    -- ������ɱ�ֵ����
    if v.func == check_many_orges_by_killed and 
    (v.args.id1 == vOrgeID or v.args.id2 == vOrgeID or v.args.id3 == vOrgeID or v.args.id4 == vOrgeID or v.args.id5 == vOrgeID 
    or v.args.id6 == vOrgeID or v.args.id7 == vOrgeID or v.args.id8 == vOrgeID or v.args.id9 == vOrgeID or v.args.id10 == vOrgeID 
    or v.args.id11 == vOrgeID or v.args.id12 == vOrgeID or v.args.id13 == vOrgeID or v.args.id14 == vOrgeID or v.args.id15 == vOrgeID 
    or v.args.id16 == vOrgeID or v.args.id17 == vOrgeID or v.args.id18 == vOrgeID or v.args.id19 == vOrgeID or v.args.id20 == vOrgeID 
    ) then 
      ret = {num = v.args.n, id=v.args.id1};-- ����ɱ���Ե�һ�ֹּ���
      lua_debug("�õ�ɱ�֣������ڲ���ɱ��"..i);
      return 1;
    end
    
    
  end);
  
  return ret; 
end

function get_awards_items(vTaskID, vSelectID, vColor)
  local r = {};
  local t = AllTasks[vTaskID].awards;
  table.foreachi(t, function(i, v)  
    if v.func == award_items then 
      table.insert(r, v.args);
    end

    if (v.func == award_option_items  or (v.func == award_option_items_by_metier and GetPlayer(EPlayerAttr.PLAYER_METIER)==v.args.metier)) and vSelectID ~= -100 then 
      
      if vSelectID == 1 then table.insert(r, {id = v.args.id1, n = v.args.n1}); end  
      if vSelectID == 2 then table.insert(r, {id = v.args.id2, n = v.args.n2}); end  
      if vSelectID == 3 then table.insert(r, {id = v.args.id3, n = v.args.n3}); end  
      if vSelectID == 4 then table.insert(r, {id = v.args.id4, n = v.args.n4}); end  
      if vSelectID == 5 then table.insert(r, {id = v.args.id5, n = v.args.n5}); end  
      if vSelectID == 6 then table.insert(r, {id = v.args.id6, n = v.args.n6}); end  
      if vSelectID == 7 then table.insert(r, {id = v.args.id7, n = v.args.n7}); end  
      if vSelectID == 8 then table.insert(r, {id = v.args.id8, n = v.args.n8}); end  
    end
    
    if v.func == award_items_by_metier and v.args.metier == GetPlayer(EPlayerAttr.PLAYER_METIER) then
       table.insert(r, {id = v.args.id, n = v.args.n});    
    end
    
    if v.func == award_items_by_refresh then
	local tab = task_refresh_awards[vTaskID][vColor].items;
	local tab_default = task_refresh_awards[vTaskID][ 1 ].items;
	table.foreachi(tab,function(i,v)
		if tab[i].id ~=0 and tab[i].num ~=0 then table.insert(r, {id = tab[i].id, n = tab[i].num} );  
		end
	end);
    end
    
    if v.func == award_level_eqt then
       table.insert(r, {id = v.args.id, n = v.args.n});    
    end
end);
 
  return r;
end

function get_max_award_option(vTaskID)
  local t = AllTasks[vTaskID].awards;

  local max_opt = table.foreachi(t, function(i, v)  
    if v.func == award_option_items  or (v.func == award_option_items_by_metier and GetPlayer(EPlayerAttr.PLAYER_METIER)==v.args.metier) then 

      if v.args.id1 == nil then return 0; end
      if v.args.id2 == nil then return 1; end
      if v.args.id3 == nil then return 2; end
      if v.args.id4 == nil then return 3; end
      if v.args.id5 == nil then return 4; end
      if v.args.id6 == nil then return 5; end
      if v.args.id7 == nil then return 6; end
      if v.args.id8 == nil then return 7; end

      return 8;
    end
  end);

  return max_opt or 0;
end

function do_task_awards(vTaskID, vSelectID,vTaskColor)
   if not check_task(vTaskID,"do_task_awards") then return false;end;
  --ȡ������Ľ������� 
  local t = {};
  local mutl = 1; --��Ǯ�����齱�����ı���
  
  --lua_debug("inAWD1");

  if AllTasks[vTaskID] == nil then
  lua_error("******���ش��󣡣� �ڽ�����AllTasks[vTaskID] == nil , vTaskID="..vTaskID);
  end
  
  if get_task_type(AllTasks[vTaskID]) == ETaskType.TASKTYPE_LOOP and AllTasks[vTaskID].loop_id ~= nil then -- ��������
        if LoopTasks[AllTasks[vTaskID].loop_id] == nil or LoopTasks[AllTasks[vTaskID].loop_id].award_multi == nil or LoopTasks[AllTasks[vTaskID].loop_id].award_multi_times == nil  then
	    lua_error("*****���ش����Ҳ��� LoopTasks�� taskid ="..vTaskID );
	else -- �����ն౶����
	
	    local times = GetTodayCompletedTimes(ETaskType.TASKTYPE_LOOP); -- �õ�������ɴ���
	    if times == nil then times = 99999999; end;
	    if times <= LoopTasks[AllTasks[vTaskID].loop_id].award_multi_times then -- ���������ɵĴ���С�ڵ��ڿ��Զ��⽱���Ĵ���
		mutl = LoopTasks[AllTasks[vTaskID].loop_id].award_multi;
	    end
	    
	end	
  end

  if get_task_type(AllTasks[vTaskID]) == ETaskType.TASKTYPE_STORAGE and AllTasks[vTaskID].storage_id ~= nil then -- ���������
        if AllStorageTasks[AllTasks[vTaskID].storage_id] == nil or AllStorageTasks[AllTasks[vTaskID].storage_id].award_multi == nil or AllStorageTasks[AllTasks[vTaskID].storage_id].award_multi_times == nil  then
	    lua_error("*****���ش����Ҳ��� AllStorageTasks[AllTasks[vTaskID].storage_id] taskid ="..vTaskID );
	else -- �����ն౶����
	
	    local times = GetTodayCompletedTimes(ETaskType.TASKTYPE_STORAGE); -- �õ�������ɴ���
	    if times == nil then times = 99999999; end;
	    if times <= AllStorageTasks[AllTasks[vTaskID].storage_id].award_multi_times then -- ���������ɵĴ���С�ڵ��ڿ��Զ��⽱���Ĵ���
		mutl = AllStorageTasks[AllTasks[vTaskID].storage_id].award_multi;
	    end
	    lua_debug("multi="..mutl);
	end	
  end

  t = AllTasks[vTaskID].awards;
  --�ռ�������ж���C�����н���
  local ret = table.foreachi(t, function(i, v)  
	if v.func == nil then
		lua_error("������nil2����do_task_awards������,vTaskID="..vTaskID..",vSelectID="..vSelectID);
	else
		v.args.task_id = vTaskID;
		v.args.color=vTaskColor;
		if v.func == award_option_items or (v.func == award_option_items_by_metier and GetPlayer(EPlayerAttr.PLAYER_METIER)==v.args.metier) then -- ���ֽ�����Ҫ2�������ġ�
		     v.func(v.args, vSelectID) 
		else
		     v.args.hard = AllTasks[vTaskID].task_hard;
		     v.func(v.args, mutl) ;
		end
		
	end
     end);
 
 -- ���event
clear_events(vTaskID);
    return ret == nil;
    
end

function clear_events(vTaskID)

  t = AllTasks[vTaskID].complete_cond;
  table.foreachi(t, function(i, v)  
    if v.func == check_use_item  then 
      ClearEvent( EEventForTask.EVENT_USEITEM, v.args.id ,v.args.n)
      
   elseif v.func == check_talk_withnpc  then 
      ClearEvent( EEventForTask.EVENT_TALKCOMPLETE, v.args.id ,1)
      
    elseif v.func == check_send_npc  then 
      ClearEvent( EEventForTask.EVENT_SENDNPCCOMPLETE, v.args.id ,1)
      
    elseif v.func == check_upeqt  then 
      ClearEvent( EEventForTask.EVENT_UPEQT, 0 ,MAX_INT)

    elseif v.func == check_produceweapon  then 
      ClearEvent( EEventForTask.EVENT_PRODUCE_WEAPON, 0 ,MAX_INT)
      
    elseif v.func == check_produceprevent  then 
      ClearEvent( EEventForTask.EVENT_PRODUCE_PREVENT, 0 ,MAX_INT)
      
    elseif v.func == check_producedrug  then 
      ClearEvent( EEventForTask.EVENT_PRODUCE_DRUG, 0 ,MAX_INT)
      
    elseif v.func == check_stove  then 
      ClearEvent( EEventForTask.EVENT_STOVE, 0 ,MAX_INT)
      
    elseif v.func == check_jewel  then 
      ClearEvent( EEventForTask.EVENT_JEWEL, 0 ,MAX_INT)
      
    elseif v.func == check_charstone  then 
      ClearEvent( EEventForTask.EVENT_CHARSTONE, 0 ,MAX_INT)
      
    elseif v.func == check_hole  then 
      ClearEvent( EEventForTask.EVENT_HOLE, 0 ,MAX_INT)
      
    elseif v.func == check_skill  then 
      ClearEvent( EEventForTask.EVENT_SKILL, 0 ,MAX_INT)
    
    elseif v.func == check_endloop  then 
      ClearEvent( EEventForTask.EVENT_ENDLOOP, 0 ,MAX_INT)
          
    end
  end);
  

end


function do_task_obt_awards(vTaskID, player_id)
  --ȡ������Ľ������� 
  local t = {};

  if AllTasks[vTaskID] == nil then
      lua_error("******���ش��󣡣� ��obt awards������AllTasks[vTaskID] == nil , vTaskID="..vTaskID);
  end
  
  t = AllTasks[vTaskID].accept_awards;
  if t == nil then
   return true;
 end
 
  --�ռ�������ж���C�����н���
  local ret = table.foreachi(t, function(i, v)  
	if v.func == nil or v.args == nil then
		lua_debug("������nil2����do_task_obt_awards������,vTaskID="..vTaskID);
	else
	    if v.func ~= award_items then -- ���������C++��ͳһ���Ź��ˣ��ڷ��������������
		v.args.task_id = vTaskID;
		v.args.player_id = player_id;
	        if v.func == start_send_npc then  -- �ǻ���NPC 
			v.args.npc_id  = AllTasks[vTaskID].send_npc_id;
			v.args.max_gird = AllTasks[vTaskID].max_gird;
			v.args.max_time = AllTasks[vTaskID].max_send_time;
		end
		v.func(v.args, 1) ;
	    end
		
	end
     end);
 
  return ret == nil;
end


function check_acceptable(vTaskID, vNpcID)
  --ȡ������Ľ�������
    if not check_task(vTaskID,"check_acceptable") then return false;end;
    
    -- ��� vNpcID ����0 ����nil  ��Ҫ��� ����Ͳ��ü��
    if vNpcID ~= nil and vNpcID ~= 0  then
	lua_debug("����npcid="..vNpcID);
	if AllTasks[vTaskID].give_npc ~= vNpcID then
		lua_debug("����false");
		return false;
	end
    end
    
    -- ���NPC����Ӫ�Ƿ�����
    if AllTasks[vTaskID].give_camp ~=0 and AllTasks[vTaskID].give_camp ~=nil and AllTasks[vTaskID].give_camp ~= GetCurCampID() then
	return false;
    end
    
    lua_debug("�������ͣ�"..get_task_type(AllTasks[vTaskID]) or 0);
      local state = GetTaskState(vTaskID) 
  lua_debug("�������״̬vTaskID = " .. vTaskID .. "(".. AllTasks[vTaskID].name .. ") ״̬= " .. state);
  
    --�ж������Ƿ��ڽ�����, �����ж�
  if state ~= ETaskState.STATE_NOT_START then return false; end
    
  local t = AllTasks[vTaskID].accept_cond;  
  local ret = nil;
    --����������е�����ȫ������Ҫ������Ϊ���Խ�������;������Ϊ���ܽ�����
  if t ~= nil then
    ret = table.foreachi(t, function(i, v)  
   	if v.func == nil then
		lua_error("������nil2��check_acceptable������,vTaskID="..vTaskID);
	else
		v.args.taskid = vTaskID; -- TODO ������������ �������taskid ����task_id!
	      if v.func(v.args) == false then 
		 return false ;
	      end
        end
    end);
  end

  if ret ==false then
       return false;
  end
  
  --����ǻ�����,���⴦��
  if get_task_type(AllTasks[vTaskID]) == ETaskType.TASKTYPE_LOOP   then 
  
            if AllTasks[vTaskID].loop_id == nil or AllTasks[vTaskID].loop_id == 0 then
	        lua_error( "������"..vTaskID.."δע�ᵽ����" );
		return false;
	    end

	    local this_id = GetCurSubTaskID();  -- �õ������Ļ������ID
	    local next_id = GetNextSubTaskID();
	    
	    lua_debug("ȡ�õ�ǰID "..this_id.." ��һ��ID ".. next_id );
	    if next_id ~= vTaskID then
		return false;
	    end
	    
	    if this_id ~= 0 and this_id ~= nil then -- ��ǰ������ID��0 ˵����û����
  
	    	local this_state = GetTaskState(this_id); 
		lua_debug("ȡ�õ�ǰ���������ǰ������״̬(" .. this_id .. ", " .. this_state .. ")");
	    	if  this_state ~= ETaskState.STATE_NOT_START then
		    return false;
		end
		
	    end; 
	    
 -- �������жϽ���
elseif get_task_type(AllTasks[vTaskID]) == ETaskType.TASKTYPE_STORAGE then -- ������Ҫ���⴦��
    
    if CheckStorageTaskInList(vTaskID) == false  then
        return false; 
    end
    
 -- �жϽ�������
elseif get_task_type(AllTasks[vTaskID]) == ETaskType.TASKTYPE_TRAGEDY then -- ��������Ҫ���⴦��
    lua_debug("������");
    local tragedy_id = AllTasks[vTaskID].tragedy_id or 0;
    if tragedy_id == 0 then
	lua_error("����"..vTaskID.."���ǽ�������");
	return false;
    end
    if IsTragedyTaskAcceptable(tragedy_id-TRAGEDY_START) == false  then
        return false; 
    end
    
end  -- �����������
    
return true;
end

-- ������񷢲�����
function check_publish_condition(vTaskID)

 --��鷢������
  if not check_task(vTaskID,"check_publish") then return false;end;
    
  local t = AllTasks[vTaskID].publish_cond;  
  local ret = nil;
    --����������е�����ȫ������Ҫ������Ϊ���Խ�������;������Ϊ���ܽ�����
  local types = AllTasks[vTaskID].publish_type;
  if types ==0 or types == nil then return false;end;
  
  if t ~= nil then
    ret = table.foreachi(t, function(i, v)  
   	if v.func == nil then
		lua_error("������nil2��check_publish������,vTaskID="..vTaskID);
	else
		v.args.taskid = vTaskID; -- TODO ������������ �������taskid ����task_id!
	        if v.func(v.args) == false then 
		 return false ;
	      end
        end
    end);
  end

  if ret ==false then
       return false;
  end
  return true;
end
-- ��� һ�ֻ�����
function init_loop_tasks( metier, level )
	local ret = {};
	if SortedLoops[metier] == nil or SortedLoops[metier] == {} then
		lua_error("û���ҵ�ְҵ"..metier.."��������������");
		return ret;
	end
	
	local loop_id = SortedLoops[metier][1];
	table.foreach( SortedLoops[metier], function(i,v)
		if LoopTasks[v] == nil then
			lua_error("û����ID="..v.."��������������");
			return ret;
		end
		if level < LoopTasks[v].min_level then
			return true;
		else
			loop_id = v;
		end
	end);	
	local rnd_tab={LoopTasks[loop_id].send_1_prob or 0, LoopTasks[loop_id].send_2_prob or 0,LoopTasks[loop_id].send_3_prob or 0,LoopTasks[loop_id].send_4_prob or 0,LoopTasks[loop_id].kill_1_prob or 0,LoopTasks[loop_id].kill_2_prob or 0,LoopTasks[loop_id].kill_3_prob or 0,LoopTasks[loop_id].kill_4_prob or 0};
	local tab=get_tasks_by_prob( loop_id, rnd_tab, LOOP_SIZE, nil, 0 );
	PlayerGetLoopTask(  tab ); -- ��������û�����
	return 0;
end

function check_complete(pTask)
  local  collector = ccollector.new();
  collector:init(pTask);

  return check_complete_internal(pTask.mTaskID, collector);
end

function check_complete_internal(vTaskID, collector)
  --ȡ�������������
  local t = AllTasks[vTaskID].complete_cond
  
   
  --���������������ȫ������Ҫ������Ϊ�����������
  if t ~= nil then
    local ret = table.foreachi(t, function(i, v)  
      if v.func == nil then
           lua_error("������nil,��check_complete_internal��,vTaskID="..vTaskID);
      else      
          if v.func(v.args, collector) == false then return false; end;      
      end
      
    end);
    return ret == nil
  else
    --���û�������������, ����Ϊ���ܼ����
    return true;
  end
end


-- ����ǲ��Ǹ�������
function is_fetch_task( pTask )
   if not check_task(pTask.mTaskID,"is_fetch_task") then return false;end;

	if AllTasks[pTask.mTaskID].is_fetch == 1 and AllTasks[pTask.mTaskID].direct_complete == 1 and check_complete(pTask) == true then
	      return true;
	else
	      return false;
	end

end
------------------------------------------------------------------------
function get_items_extend(vTaskID)
    if not check_task(vTaskID,"get_items_extend") then return {};end;
    if AllTasks[vTaskID].give_items == nil then
	lua_debug("����"..vTaskID.."û��give_items�ֶ�");
	return {};
    end
   
   local ret = AllTasks[vTaskID].give_items;
    
		      local t = AllTasks[vTaskID].accept_awards;
		      if t ~= nil then
		           table.foreachi(t, function(i, v)  
			   
			      if v.func == award_items  then
			           table.insert( ret, v.args );
			      end
			   end);
		      end
      return ret;
end

-- �õ�����NPC��·��
function get_npc_waypoints(vTaskID)
    if not check_task(vTaskID,"get_npc_waypoints") then return {};end;
    if AllTasks[vTaskID].npc_waypoints == nil then return {}; end;
    
    return AllTasks[vTaskID].npc_waypoints;
end

------------------------------------------------------------------------
-- ���������������{{ id=, n=,  maxn=}...} �ֱ���� �������ƷID�� �����������������Ҫ����ƷID
function get_items_droped(vTaskID, vNpcID)
--lua_debug("in get_items_droped,"..vTaskID..","..vNpcID);
if vTaskID ==0 or vNpcID ==nil then
	lua_debug("in get_items_droped IDs 0");
	return {};
end

    if not check_task(vTaskID,"get_items_droped") then return {};end;

  local t = AllTasks[vTaskID].drop_items;
if t == nil then
	lua_error("err t=nil");
	return {};
end

  local ret = {};
  
  table.foreachi(t, function(i, v)  
	    if v.npc_id  == vNpcID then 
		  if v.n ~= nil and v.n ~= 0 then 
			if math.random(10000) <= v.p then
			      table.insert(ret, {id=v.item_id, n=math.random(v.n), maxn=get_collect_items_num_by_id(vTaskID, v.item_id) }); 
			end
		  end
	    end
  end);  
lua_debug("�õ��������Ʒ������"..table.getn(ret) );
  return ret;
end

------------------------------------------------------------------------
function get_ctrl(vTaskID, vAttrID)
  if not check_task(vTaskID,"get_ctrl") then return 0;end;
  
  --lua_debug("task_id = " .. vTaskID .. " attr_id = " .. vAttrID);

  local t = AllTasks[vTaskID];
  if vAttrID == ETaskCtrl.CTRL_REPEATEABLE then
    return t.repeatable
  end 
  if vAttrID == ETaskCtrl.CTRL_CANCELABLE then  
    return t.cancelable
  end 
  if vAttrID == ETaskCtrl.CTRL_RETRYABLE then  
    return t.retryable 
  end 
  if vAttrID == ETaskCtrl.CTRL_FAILONKILLED then  
    return t.fail_on_killed
  end 
  if vAttrID == ETaskCtrl.CTRL_DIRECTCOMPLETE then  
    return t.direct_complete
  end
  
  if vAttrID == ETaskCtrl.CTRL_OFF_FAIL then  
    return t.offline_fail or 0;
  end
  
  if vAttrID == ETaskCtrl.CTRL_TASKGROUP then  
    return t.group_id or 0;
  end
  
  if vAttrID == ETaskCtrl.CTRL_ISAUTOABORT then  
    return t.is_fail_auto_abort or 0;
  end
  
  if vAttrID == ETaskCtrl.CTRL_ISSHARE then  
    return t.is_share_complete or 0;
  end
  
  if vAttrID == ETaskCtrl.CTRL_TIMEOUT_TYPE then  
    return t.timeout_action or 0;
  end
  
  if vAttrID == ETaskCtrl.CTRL_TIMELMT_TYPE then  
    return t.time_lmt_type or 0;
  end
 
  
  if vAttrID == ETaskCtrl.CTRL_SENDNPC then  
     if t.send_npc_id == nil then
        return 0;
     else
        return t.send_npc_id ;
     end
  end
  
    if vAttrID == ETaskCtrl.CTRL_MAXGIRD then  
     if t.max_gird == nil then
        return 0;
     else
        return t.max_gird ;
     end
  end
  
    if vAttrID == ETaskCtrl.CTRL_NAME then  
        return t.name or "";
    end
    
    if vAttrID == ETaskCtrl.CTRL_IS_DAILY_FAILED then  
        return t.is_day_fail or 0;
    end    
        
    if vAttrID == ETaskCtrl.CTRL_IS_TEAMLOOP then  
        return t.loop_type or 0;
    end            
    
    if vAttrID == ETaskCtrl.CTRL_TEAM_MEMBER then  
        return t.team_member_lmt or 0;
    end
    
    if vAttrID == ETaskCtrl.CTRL_FINISH_TIME then  
        return t.finish_delay_time or 0;
    end 
    
    if vAttrID == ETaskCtrl.CTRL_REFRESH_AWARD then  
        return t.refresh_award_able;
    end
    
    if vAttrID == ETaskCtrl.CTRL_TASK_ENDTIME then  
        return t.task_reaccept_time or 0;
    end     

    if vAttrID == ETaskCtrl.CTRL_TASK_PUBLISHTYPE then  
        return t.publish_type or 0;
    end   
  return false;
end

------------------------------------------------------------------------
function update_task(pTask) 
  
  local mTaskState = pTask.mState;
  
     if not check_task(pTask.mTaskID,"update_task") then return false;end;
     
  lua_debug("����֮ǰ,�����ID��״̬�ֱ���: (" .. pTask.mTaskID .. "("..AllTasks[pTask.mTaskID].name.."), ".. pTask.mState .. ")");

  --��������Ѿ��������������״̬��δ��ʼ, �򷵻�
  if mTaskState == ETaskState.STATE_TASK_END  or mTaskState == ETaskState.STATE_NOT_START  then 
    return false; 
  end

  --ȡ����������� û���ã�
 -- local task_kind  = AllTasks[pTask.mTaskID].kind

  --ȡ��������µ��¼�
  --local task_event = t.event;

  local  collector = nil;

  --���������ɱ������, ����¼���ɱ�ִ���, ������������

  collector = ccollector.new();
  collector:init(pTask);

  -- ��������Ƿ����, ����������״̬Ϊ���״̬
  if check_complete_internal(pTask.mTaskID, collector) then
        pTask.mState = ETaskState.STATE_TASK_COMPLETE;
  else
       if pTask.mState == ETaskState.STATE_TASK_COMPLETE then 
            pTask.mState = ETaskState.STATE_TASK_BEGIN;
       end
  end

  lua_debug("����֮��,�����ID��״̬�ֱ���: (" .. pTask.mTaskID .. "("..AllTasks[pTask.mTaskID].name.."), ".. pTask.mState .. ")");

  return true;
end
-------------------------------------------------------------------------------
function init_this_task(pTask)

  local vTaskID = pTask.mTaskID;
  local t = AllTasks[vTaskID].complete_cond;
  local orges_num = 0;
  if t then
    --����ط��ü����Ƶģ���ʼ������Ӧ�ò�һ��
    local collector = ccollector.new();
    collector:init(pTask);
    table.foreachi(t, function(i, v) --�ж��ж�����ɱ�֣�����¼����������ȥ,��ΪҪ��pairs���ݷ����ͻ���
      if v.func == nil then
          lua_debug("������nil,��init_this_task�У�����ID="..pTask.mTaskID);
      else
		-- ����ɱ��
	      if v.func == check_orges_by_killed then
		  collector:set_pair(v.args.id, 0);
		  orges_num = orges_num + 1;
		  lua_debug("��ʼ����collector:����ID="..v.args.id);
	      end
	      
	      -- ������ɱ��
	      if v.func == check_many_orges_by_killed then
		  collector:set_pair(v.args.id1, 0);
		  orges_num = orges_num + 1;
		  lua_debug("��ʼ�������� collector:����ID1="..v.args.id1);
	      end
	      
	      -- �����ȼ�ɱ��
	      if v.func == check_level_orges_by_killed then
		  collector:set_pair(cale_kill_level_ogre_id(v.args.min_level , v.args.max_level), 0);
	      end
	      
	      -- ע�� �����ɿ�����
	      if v.func == check_complete_storagetask then
		  collector:set_pair(enSpecialID.SPECIALID_COMPLETESTORAGE, 0);
	      end
	      
	      -- ע�� ���ɱ�����
	      if v.func == check_killforeigner then
		  collector:set_pair(enSpecialID.SPECIALID_KILLFOREIGNER, 0);
	      end
	      
	end
    end);
    collector:save(pTask);
  end
  
  --��������
  if get_task_type(AllTasks[vTaskID]) == ETaskType.TASKTYPE_LOOP and AllTasks[vTaskID].loop_id ~= nil then  
	InsertLoopTask( vTaskID );
  end
  
  -- ���������
  if get_task_type(AllTasks[vTaskID]) == ETaskType.TASKTYPE_STORAGE then
	RemoveStorageTask( vTaskID );
  end

  reg_task_tick(pTask);
  
  -- �������ʱ���� Ҫ��ʼ��ʱ
  if AllTasks[vTaskID].timer > 0 then
	StartTimeLimitTaskTimer( vTaskID, AllTasks[vTaskID].timer, AllTasks[vTaskID].time_lmt_type or 0 );
  end 
  
  if not ( AllTasks[vTaskID].is_redirect_fail == nil or AllTasks[vTaskID].is_redirect_fail == 0) then
	SetRedirectFailTask(vTaskID);
  end
  
  return orges_num;
end

function reg_task_tick(pTask)
   if not check_task(pTask.mTaskID,"reg_task_tick") then return false;end;
   local collector = ccollector.new();
   collector:init(pTask);

   		      local t = AllTasks[pTask.mTaskID].complete_cond;
		      if t ~= nil then
		           table.foreachi(t, function(i, v)  
				      if v.func == check_items_of_bag then
					   pTask:RegEventTick( EEventForTask.EVENT_ITEMCHANGE, v.args.id or 0, v.args.n - PlayerHasItem(v.args.id) );
				      elseif v.func == check_orges_by_killed then
					   pTask:RegEventTick( EEventForTask.EVENT_OGREDIE, v.args.id or 0, v.args.n-collector:get_pair(v.args.id) );
				      elseif v.func == check_many_orges_by_killed then
					   pTask:RegEventTick( EEventForTask.EVENT_OGREDIE, v.args.id1 or 0, v.args.n-collector:get_pair(v.args.id1) );
					 
  					   if  v.args.id2 ~= nil and v.args.id2 ~= 0 then
						pTask:RegEventTick( EEventForTask.EVENT_OGREDIE, v.args.id2 or 0, 0 );
					   end
					   if  v.args.id3 ~= nil and v.args.id3 ~= 0 then
						pTask:RegEventTick( EEventForTask.EVENT_OGREDIE, v.args.id3 or 0, 0 );
					   end
					   if  v.args.id4 ~= nil and v.args.id4 ~= 0 then
						pTask:RegEventTick( EEventForTask.EVENT_OGREDIE, v.args.id4 or 0, 0 );
					   end
					   if  v.args.id5 ~= nil and v.args.id5 ~= 0 then
						pTask:RegEventTick( EEventForTask.EVENT_OGREDIE, v.args.id5 or 0, 0 );
					   end
					   
				      elseif v.func == check_level then
					   pTask:RegEventTick( EEventForTask.EVENT_LEVELCHANGE, 0, 0 );
				      elseif v.func == check_money then
					   pTask:RegEventTick( EEventForTask.EVENT_CHANGEMONEY, 0, 0 );
				      elseif v.func == check_metier then
					   pTask:RegEventTick( EEventForTask.EVENT_METIERCHANGE, 0, 0 );		      
				      elseif v.func == check_not_metier then
					   pTask:RegEventTick( EEventForTask.EVENT_METIERCHANGE, 0, 0 );		      
				      elseif v.func == check_items_not_in_bag then
					   pTask:RegEventTick( EEventForTask.EVENT_ITEMCHANGE, v.args.id or 0, 0 );	      
				      elseif v.func == check_task_got then
					   pTask:RegEventTick( EEventForTask.EVENT_TASKCHANGE, v.args.id or 0, 0 );	   
				      elseif v.func == check_use_item then
					   pTask:RegEventTick( EEventForTask.EVENT_USEITEM, v.args.id or 0, 0 );	 
				      elseif v.func == check_send_npc then
					   pTask:RegEventTick( EEventForTask.EVENT_SENDNPCCOMPLETE, v.args.id or 0, 0 );	 
				      elseif v.func == check_talk_withnpc then
					   pTask:RegEventTick( EEventForTask.EVENT_TALKCOMPLETE, v.args.id or 0, 0 );	 					   
				    
				    elseif v.func == check_upeqt  then 
				      pTask:RegEventTick( EEventForTask.EVENT_UPEQT, 0 ,0)
				
				    elseif v.func == check_produceweapon  then 
				      pTask:RegEventTick( EEventForTask.EVENT_PRODUCE_WEAPON, 0 ,0)
				      
				    elseif v.func == check_produceprevent  then 
				      pTask:RegEventTick( EEventForTask.EVENT_PRODUCE_PREVENT, 0 ,0)
				      
				    elseif v.func == check_producedrug  then 
				      pTask:RegEventTick( EEventForTask.EVENT_PRODUCE_DRUG, 0 ,0)
				      
				    elseif v.func == check_stove  then 
				      pTask:RegEventTick( EEventForTask.EVENT_STOVE, 0 ,0)
				      
				    elseif v.func == check_jewel  then 
				      pTask:RegEventTick( EEventForTask.EVENT_JEWEL, 0 ,0)
				      
				    elseif v.func == check_charstone  then 
				      pTask:RegEventTick( EEventForTask.EVENT_CHARSTONE, 0 ,0)
				      
				    elseif v.func == check_hole  then 
				      pTask:RegEventTick( EEventForTask.EVENT_HOLE, 0 ,0)  
				      
				    elseif v.func == check_skill  then 
				      pTask:RegEventTick( EEventForTask.EVENT_SKILL, 0 ,0)  
				      
				    elseif v.func == check_endloop  then 
				      pTask:RegEventTick( EEventForTask.EVENT_ENDLOOP, 0 ,0)  

				     elseif v.func == check_level_orges_by_killed then
					pTask:RegEventTick( EEventForTask.EVENT_KILLLEVELOGRE, cale_kill_level_ogre_id(v.args.min_level , v.args.max_level), v.args.n-collector:get_pair(cale_kill_level_ogre_id(v.args.min_level , v.args.max_level) ) );	
				    
				     elseif v.func == check_complete_storagetask then
					pTask:RegEventTick( EEventForTask.EVENT_COMPLETESTORAGETASK, enSpecialID.SPECIALID_COMPLETESTORAGE, v.args.n );	
					
				     elseif v.func == check_complete_looptask then
					pTask:RegEventTick( EEventForTask.EVENT_COMPLETE_LOOP, enSpecialID.SPECIALID_COMPLETELOOPTASK, v.args.n );	
				
				     elseif v.func == check_killforeigner then
					pTask:RegEventTick( EEventForTask.EVENT_KILLFOREIGNER, enSpecialID.SPECIALID_KILLFOREIGNER, v.args.n );	
								
				     elseif v.func == check_buff then
					pTask:RegEventTick( EEventForTask.EVENT_BUFFCHANGED, v.args.buff_id, 0 );

				     elseif v.func == check_no_buff then
					pTask:RegEventTick( EEventForTask.EVENT_BUFFCHANGED, v.args.buff_id, 0 );	

				     elseif v.func == check_protect_flag then
					-- ��������
					pTask:RegEventTick( EEventForTask.EVENT_PROTECT_FLAG, v.args.npc_id, 0 );	
					-- ע����������
					RegProtectFlagTask( pTask.mTaskID, v.args.npc_id );
					
				    elseif v.func == check_ques_num then
					pTask:RegEventTick( EEventForTask.EVENT_COMPLETE_QUESTION, enSpecialID.SPECIALID_COMPLETEQUESTION, v.args.num );	
 					
				    elseif v.func == check_multi_cond then
				      table.foreachi(v.args, function(j, k)  
					if k.func ~= check_items_of_bag then
					    lua_error("����"..pTask.mTaskID.."����ɲ����������зǼ����Ʒ����");
					else
					    pTask:RegEventTick( EEventForTask.EVENT_ITEMCHANGE, k.args.id or 0, k.args.n - PlayerHasItem(k.args.id) );
					end
				    end);

				    end

			   end);
		      end
		      
		      -- ���������
		      
		       t = AllTasks[pTask.mTaskID].drop_items;
		      if t ~= nil then
		           table.foreachi(t, function(i, v)  
	
				pTask:RegEventTick( EEventForTask.EVENT_OGREDIE, v.npc_id or 0, 0 );

			    --   return 1;
			   end);
		      end
		      
		      
	return true;
end

function get_task_kill_orge_num(pTask)
   local  collector = ccollector.new();
    local num = collector:init(pTask);
    lua_debug("ȡ��ɱ����������"..num);
    return num;
end


--~ function  get_task_loop_id(vTaskID)
--~ if vTaskID == nil or vTaskID == 0 then return 0; end;

--~ if AllTasks[vTaskID] == nil or  AllTasks[vTaskID].loop_id == nil or AllTasks[vTaskID].loop_index == nil then 
--~    lua_debug("******���ش���  AllTasks[vTaskID] == nil vTaskID="..vTaskID);
--~    return 0;
--~ end

--~ return {loop_task_id = (AllTasks[vTaskID].loop_id or 0
--), loop_index = (AllTasks[vTaskID].loop_index or 0) };

--~ end

-- ����ҷ��������ʱ����ã�����ǻ����񣬿�������������������⴦���������
function  on_abort_task(vTaskID)
  if check_task(vTaskID,"on_abort_task") == false then return num;end;
  
  clear_events(vTaskID);
   
end

-- �ж��ǲ��ǻ������е����һ��
function  is_the_end_loop(vTaskID)
  if check_task(vTaskID,"is_the_end_loop") == false then return false;end;
  
  if vTaskID == nil or vTaskID == 0 or get_task_type(AllTasks[vTaskID]) ~= ETaskType.TASKTYPE_LOOP then return false; end;
  if  AllTasks[vTaskID].loop_id == nil then 
      return false; 
  end;
  local lask_loop_task_id = GetLastLoopTaskID();
  
  lua_debug("in is_the_end_loop vTaskID="..vTaskID.." lask_loop_task_id="..lask_loop_task_id or 999);
  return vTaskID == lask_loop_task_id;
end


function   is_direct_complete(vTaskID)
   if not check_task(vTaskID,"is_direct_complete") then return false;end;
   
  if AllTasks[vTaskID].direct_complete == 0 then
       return false;
  else
       return true;
  end
  
end

function check_task(vTaskID,str)
  if str == nil then str="NULL"; end;
  
  if vTaskID == nil then 
	lua_error("******���ش����Ҳ���AllTasks[vTaskID],vTaskID= nil in ..."..str); 
	return false; 
  end;
  
   if vTaskID == 0 then 
	lua_error("******���ش����Ҳ���AllTasks[vTaskID],vTaskID= 0 in ..."..str); 
	return false; 
   end;
  
  if AllTasks[vTaskID] == nil then 
      lua_error("******���ش����Ҳ���AllTasks[vTaskID],vTaskID="..vTaskID.."in ..."..str); 
      return false; 
  end;
  return true;
end



function  is_get_metier_task(vTaskID)

   if not check_task(vTaskID,"is_get_metier_task") then return false;end;
   
  if AllTasks[vTaskID].get_metier_task == 0 or AllTasks[vTaskID].get_metier_task == nil  then
       return false;
  else
       return true;
  end
end

-- �ڹ����������,���ȷʵ"����"����ô�����Ѿ�ɱ��������
function on_orge_die(pTask, t)

	    local  collector = nil;
	    local  ret = {num=0,id=0};
	    
	    collector = ccollector.new();
	    if collector:init(pTask) > 0 then

			      if t.id and t.n  then

				  local AllNumID = get_kill_orges_num_by_id(pTask.mTaskID, t.id); -- ���ص���Ӧ��ɱ�������ͼ���ID
				  if AllNumID == nil then return ret;end;
				  
				  local edNum    = collector:get_pair(AllNumID.id);
				  if edNum == nil then return ret;end;
								  
				  if edNum < AllNumID.num then -- ��ûɱ��
					  -- ���ûɱ����ֻ��1ֻ����Ϊһ��ֻ����1ֻ�֣�
					  lua_debug("���ɱ���ֲ�����collector:set ("  .. AllNumID.id .. ", 1)");
					  collector:set_pair(AllNumID.id, 1);
					  collector:save(pTask);
					  ret.num = edNum+1;
					  ret.id  = AllNumID.id;
				  end	  
				  
			      end
		    
	    end
	    return ret;
end

-- �����ȼ�ɱ��
function on_level_orge_die( pTask, level )
	    local  collector = nil;
	    collector = ccollector.new();
	    if collector:init(pTask) > 0 then
	    
		local ret_tab = collector:get_by_index(1);	-- ֻ������1��
		if ret_tab == nil or ret_tab.id == 0 then -- û�����������
			lua_error( "no level kill ogre? ogre level="..level );
			return 0;
		else
			local ret = get_ogre_level_by_caledid ( ret_tab.id );
			if ret == nil or ret.low == nil or ret.high == nil then
				lua_error("get_ogre_level_by_caledid return err!");
				return 0;
			end
			if level < ret.low or level > ret.high then
				return 0;
			end
			collector:set_pair( ret_tab.id, 1);
			collector:save(pTask);
			return (ret_tab.n+1);
		end
	    
	    end
	return 0;
end

function get_task_state(task_id)
  return GetTaskState(task_id);
end


-- ˢ�¿����񣬷���ˢ���Ľ���б�  ������������ID������ (ETaskRefreshType)
-- ����ǽ�����ˢ ���ʾ�Ƿ������ڴ����⣬����ȫ������
function refresh_storge_tasks( s_task_id,  type_id )

if prob_tasks[s_task_id] == nil or AllStorageTasks[s_task_id] == nil  then
   lua_error("****�Ҳ���StorageTasks["..s_task_id.."]");
   return {};
end

if type_id == ETaskRefreshType.RMB then  -- ����ҵ���ˢ
	-- �޸ĺ�������밴������ 1 2 3 4��˳����
	local rnd_table={AllStorageTasks[s_task_id].rmb_white, AllStorageTasks[s_task_id].rmb_blue, AllStorageTasks[s_task_id].rmb_purple , AllStorageTasks[s_task_id].rmb_gold};
	return get_tasks_by_prob(s_task_id, rnd_table, STORAGE_SIZE, ETaskColor.BLUE);
	
elseif type_id == ETaskRefreshType.BACK then -- ���������ʱ��ˢ <����Ƕ�ʱˢ��Ŀ������ˢ������ ������C++>
	local rnd_table={AllStorageTasks[s_task_id].back_white ,  AllStorageTasks[s_task_id].back_blue, AllStorageTasks[s_task_id].back_purple, 0};
	local num = table.getn(prob_tasks[s_task_id][ETaskColor.WHITE])+table.getn(prob_tasks[s_task_id][ETaskColor.BLUE])+table.getn(prob_tasks[s_task_id][ETaskColor.PURPLE])+table.getn(prob_tasks[s_task_id][ETaskColor.GOLD]);
	return get_tasks_by_prob(s_task_id, rnd_table, num, nil, 1);
else   -- ÿ��ˢ
	local rnd_table={ 100,0,0,0 };
	return get_tasks_by_prob(s_task_id, rnd_table, STORAGE_SIZE, nil);
end

return ret;	
end

-- �������ȼ�������
function  get_loop_award_exp(level, hard)
if level == nil or  level == 0 or hard == nil or hard == 0 then
   return 0;
end
if level < 1 or level > 159 then
   return 0;
end

return loop_awards_exp[level][hard] or 0;
end


-- �������ȼ�������
function  get_loop_award_money(level, hard)
if level == nil or  level == 0 or hard == nil or hard == 0 then
   return 0;
end
if level < 1 or level > 159 then
   return 0;
end

return loop_awards_money[level][hard] or 0;
end

-- ȡ�������� ��������ʵ��
function get_task_type( vTask )
	if vTask == nil then 
		lua_error("������nil??�����ܰ���");
		return 0; 
	end;
--~ 	if vTask.id >= 1000 and vTask.id < 2000 then return ETaskType.TASKTYPE_MAIN; end;
--~ 	if vTask.id >= 2000 and vTask.id < 3000 then return ETaskType.TASKTYPE_LATERAL; end;
--~ 	if vTask.id >= 3000 and vTask.id < 4000 then return ETaskType.TASKTYPE_WEST; end;
--~ 	if vTask.id >= 4000 and vTask.id < 5000 then return ETaskType.TASKTYPE_TRAGEDY; end;
--~ 	if vTask.id >= 5000 and vTask.id < 6000 then return ETaskType.TASKTYPE_LOOP; end;
--~ 	if vTask.id >= 6000 and vTask.id < 7000 then return ETaskType.TASKTYPE_STORAGE; end;
--~ 	if vTask.id >= 7000 and vTask.id < 8000 then return ETaskType.TASKTYPE_SCROLL; end;
--~ 	return 0;
	return vTask.task_type or 0;
end

function get_task_type_by_id( vTaskID )
if vTaskID == 0 then
	return 0;
end
  if check_task(vTaskID,"get_task_type_by_id") == false then return 0;end;
  return get_task_type(AllTasks[vTaskID]);
end

-- ȡ��һ����������ID ��������1�� ��ô�������Լ�
function get_next_tragedy( vTaskID )
local ret={task_id=0, index=0};

  if check_task(vTaskID,"get_next_tragedy") == false then return ret;end;
  if AllTasks[vTaskID].tragedy_id ~= nil and AllTasks[vTaskID].tragedy_id > 0 then
       
	for i,v in pairs(tragedy_task[AllTasks[vTaskID].tragedy_id].list) do
		if v == vTaskID then
			if tragedy_task[AllTasks[vTaskID].tragedy_id].list[i+1] ~= nil then
				return { task_id=tragedy_task[AllTasks[vTaskID].tragedy_id].list[i+1], index=AllTasks[vTaskID].tragedy_id-TRAGEDY_START};
			else
				return { task_id=vTaskID, index=AllTasks[vTaskID].tragedy_id-TRAGEDY_START};
			end
		end
	end

  end
  
  return ret;  
end

-- �������ID(����)
function get_tragedy_id( vTaskID )
  if check_task(vTaskID,"get_tragedy_id") == false then return 0;end;
  if AllTasks[vTaskID].tragedy_id == nil then return 0;end;
  return AllTasks[vTaskID].tragedy_id-TRAGEDY_START or 0;
end

-- �����ɺ�NPC�Ի�  ����������ID�� NPCģ��ID
function on_end_talk_with_npc( vTaskID, vNpcID, player_id )
  if check_task(vTaskID,"on_end_talk_with_npc") == false then return 0;end;
  
  local t = AllTasks[vTaskID].dialog_with_npc;
  if t == nil then
	lua_error("�Ҳ���dialog_with_npc  ����ID="..vTaskID);
	return 0;
  end
  
  t = AllTasks[vTaskID].dialog_with_npc[vNpcID];
  if t == nil then
	lua_error("�Ҳ���dialog_with_npc2  ����ID="..vTaskID.."NPC ID="..vNpcID);
	return 0;
  end
  
  t = AllTasks[vTaskID].dialog_with_npc[vNpcID].actions;
  if t == nil then
	lua_error("�Ҳ���dialog_with_npc3  ����ID="..vTaskID);
	return 0;
  end
  
    lua_debug("��NPC "..vNpcID.."�Ի�");
  
 table.foreachi(t, function(i, v)  
	if v.func == nil then
		lua_debug("������nil2����get_tragedy_id������,vTaskID="..vTaskID);
	else
		v.args.task_id = vTaskID;
		v.args.player_id = player_id;
		if v.func == start_send_npc then  -- �ǻ���NPC 
			v.args.npc_id  = AllTasks[vTaskID].send_npc_id;
			v.args.max_gird = AllTasks[vTaskID].max_gird;
			v.args.max_time = AllTasks[vTaskID].max_send_time;
		end
		v.func(v.args, vTaskID) ;
	end
     end);
     
   return 0;
end

-- �жϵ��׸ÿۼ���(����) ����  �����-1 ��ʾ����Ҫ������� -2 ��ʾ���� 
function check_recv_bag_item( task_id, id, num )
        if check_task(task_id,"check_recv_bag_item") == false then return -1;end;
	local t={};
	
	table.foreachi(AllTasks[task_id].complete_cond, function(i, v)  
		if v.func == check_multi_cond then
			t = v.args;
			return true;
		end	
        end);
	
	if table.getn(t) == 0 then
		return -1;
	end
     
        local ret = -1;
	table.foreachi(t, function(j, k)  
		if k.func ~= check_items_of_bag then
			lua_error("����"..task_id.."����ɲ����������зǼ����Ʒ����");
		else
			if k.args.id == id then
				lua_debug("�ҵ�ID"..id);
				if ret == -1 then ret = -2; end;
				lua_debug("k.args.n="..k.args.n);
				if k.args.n <= num and k.args.n > ret then 
					ret = k.args.n;
				end;
			end
		end
	end);

	return ret;	      
end


-- �ж������ܲ�������  1�ǿ��� 0 ������
function is_task_can_invite( vTaskID )
	if check_task(vTaskID,"is_task_can_invite") == false then return 0;end;
	
	if AllTasks[vTaskID].task_type == ETaskType.TASKTYPE_LOOP or AllTasks[vTaskID].task_type == ETaskType.TASKTYPE_TRAGEDY or AllTasks[vTaskID].task_type == ETaskType.TASKTYPE_SCROLL or AllTasks[vTaskID].task_type == ETaskType.TASKTYPE_STORAGE or AllTasks[vTaskID].task_type == ETaskType.TASKTYPE_MINEMAP  or AllTasks[vTaskID].task_type == ETaskType.TASKTYPE_LUCK  then
		return 0;
	end
	
	if table.getn(AllTasks[vTaskID].npc_waypoints) > 0 then
		return 0;
	end
	
	if table.getn( AllTasks[vTaskID].give_items ) > 0 then
		return 0;
	end
	
	if AllTasks[vTaskID].can_invite == 0 then -- ��������
		return 1;
	end
	
	return 0;
end

-- �費��Ҫ�Ӱ���������  ����1��0
function is_need_give_item( vTaskID )
	if check_task(vTaskID,"is_need_give_item") == false then return 0;end;
	
	local t = AllTasks[vTaskID].complete_cond;	  
	local ret = 0;
	if t ~= nil then
	    ret = table.foreachi(t, function(i, v)  
		if v.func == check_multi_cond then
			 return 1 ;
		end
	    end);
	end
	  
	return ret;
end

-- ȡ�û�������ص�����
-- �ֱ��û�����ID ÿ��౶�������� ÿ�ܻ�ö��⽱������Ҫ��������������������
function get_looptaskdata( vTaskID )
	local ret = { loopid=0, day_total=0, week_total=0, day_multi = 1 };
	if check_task(vTaskID,"get_looptaskdata") == false then return ret;end;
	ret.loopid=AllTasks[vTaskID].loop_id or 0;
	if LoopTasks[AllTasks[vTaskID].loop_id] == nil then return ret;end;
	ret.day_total = LoopTasks[AllTasks[vTaskID].loop_id].award_multi_times or 0;
	
	-- ���ÿ��������
	local week_times = 0;
	table.foreach(extra_awards[EXTRA_DEFINE.LOOP_TASK], function(i,v)
		if week_times == 0 then week_times = i; return 1; end
	end);
	ret.week_total = week_times;
	
	ret.day_multi = LoopTasks[AllTasks[vTaskID].loop_id].award_multi or 0;	
	return ret;
end


function check_acceptable_express( vTaskID )
   if not check_task(vTaskID,"check_acceptable_express") then return false;end;
  local t = AllTasks[vTaskID].accept_cond;  
  local ret = nil;
    --����������е�����ȫ������Ҫ������Ϊ���Խ�������;������Ϊ���ܽ�����
  if t ~= nil then
    ret = table.foreachi(t, function(i, v)  
   	if v.func == nil then
		lua_error("������nil2��check_acceptable������,vTaskID="..vTaskID);
	else
	
	      if v.func(v.args) == false then 
		 return false ;
	      end
        end
    end);
  end

  return  ret==nil;
  
end

function get_task_end_info(vTaskID)
  if not check_task(vTaskID,"get_task_end_info") then return {};end;
  local ret = {money=0, free=0, expr=0, groupid= AllTasks[vTaskID].group_id or 0};
  return ret;
end

function get_loop_task_punish_time( vTaskID )
		if not check_task(vTaskID,"get_loop_task_punish_time") then return 0;end;
		if AllTasks[vTaskID].loop_id == 0 or AllTasks[vTaskID].loop_id == nil then
			lua_error("task"..vTaskID.."not in list!");
			return 0;
		end
		 local loop_task = LoopTasks[AllTasks[vTaskID].loop_id];
		 if loop_task == nil then
			lua_error( "loop task"..vTaskID.." 's LOOPTASK is nil ! ");
			return false;
		 end
		 
	         return loop_task.abort_punish_cold_task  ;
end

-- �õ�������б�  ���������
function get_activity_tasks( vGroupID )
  local ret = {};
  
  if  group_tasks[vGroupID] == nil then
	return ret;
  end
  
    for i = 1, table.getn(group_tasks[vGroupID]) do
	  local tTaskID = group_tasks[vGroupID][i];
	  if not check_task(tTaskID,"get_activity_tasks") then return ret;end;
	  local t = AllTasks[tTaskID].show_cond;  
	  if t ~= nil then  
		lua_debug("get_activity_tasks - taskid="..tTaskID);
		local  sret = table.foreachi(t, function(i, v)  
			if v.func == nil then
				lua_error("func is nil2��get_activity_tasks ,tTaskID="..tTaskID);
			else	
			      if v.func(v.args) == false then 
				 return false ;
			      end
			end
	        end);
		if  sret == nil then  -- ͨ����
			lua_debug("get_activity_tasks insert taskid="..tTaskID);
			table.insert( ret, tTaskID );
		end
	  end    
    end
   return ret;
end

-- �������Ҫ�޸�collector��ֵ���¼�  Ҫ��¼����
-- ����Ŀǰ����
function set_colletor_value( pTask, vParam, vN )
   local  collector = ccollector.new();
    collector:init(pTask);
    collector:set_pair(vParam, vN );
    lua_debug("set_colletor_value  set"..vParam.." n="..vN);
    collector:save(pTask);
    return collector:get_pair(vParam );	
end

--  ��ÿ�����౶��������
function get_storage_task_extra_awards( )
	local ret = { multi=1, times=0 };
	if AllStorageTasks[FirstStorageTasks] == nil then return ret;end;
	ret.multi = AllStorageTasks[FirstStorageTasks].award_multi or 1;	-- ��������
	ret.times = AllStorageTasks[FirstStorageTasks].award_multi_times or 0;	-- ��������
	return ret;
end

-- ÿ�����x�λ����� ���⽱��
-- ע�⣺ֻ����x=���� �������� ��Ϊÿ��add�˶�����õ�
-- ����:  ������ID  ���ܴ���
-- ��������ܽ��� ����1
function on_weekly_end_loop_added( vTaskID, week_times )
	local loop_id = AllTasks[vTaskID].loop_id or 0;
	if LoopTasks[loop_id] == nil then return 0;end;
	--local week_times_lmt = LoopTasks[loop_id].week_award_multi_times or 0;
	--if week_times_lmt == week_times then
		lua_debug("week_times:"..week_times or 999);
		-- ��ÿ�ܽ���
		if  extra_awards[EXTRA_DEFINE.LOOP_TASK] ~= nil and extra_awards[EXTRA_DEFINE.LOOP_TASK][week_times] ~= nil then
			  local t = extra_awards[EXTRA_DEFINE.LOOP_TASK][week_times];
			  local ret = table.foreachi(t, function(i, v)  
				if v.func ~= nil then
					v.args.task_id = loop_id;
					v.args.hard = 0;
					v.func(v.args, 1) ;
				end					
			  end);
			  return 1;
		end		
	--end
	return 0;
end

-- ��ɽ����������� ���ò��øĶ��⽱��
function on_completed_tragedy( nTimes )
	if  extra_awards[EXTRA_DEFINE.TRAGEDY_TASK] ~= nil and extra_awards[EXTRA_DEFINE.TRAGEDY_TASK][nTimes] ~= nil then
		  local t = extra_awards[EXTRA_DEFINE.TRAGEDY_TASK][nTimes];
		  local ret = table.foreachi(t, function(i, v)  
			if v.func ~= nil then
				v.args.task_id = 0;
				v.args.hard = 0;
				v.func(v.args, 1) ;
			end					
		  end);
		 return 1;
	end
	return 0;
end 

-- �������ȼ�������
function  get_level_award_exp(level, hard)
	if level == nil or  level == 0 or hard == nil or hard == 0 then
	   return 0;
	end
	if level < 1 or level > 159 then
	   return 0;
	end
	
	if common_level_exp == nil then 
		return 0;
	end
	return common_level_exp[level][hard] or 0;
end

function   get_level_award_exp_for_nation_kill(level, hard, task_id)
	if not check_task(task_id,"get_level_award_exp_for_nation_kill") then return 0;end;

	local base_val=get_level_award_exp(level, hard);
	local src_camp = CommonGetData(GET_PLAYER_CAMP);  -- �����A��Ӫ��Ҳ�������������Ӫ
	local des_camp = AllTasks[task_id].recv_camp;  -- �����B��Ӫ��Ҳ����Ŀ����Ӫ ���������� �����0 �������裨�Ժ���
	
	-- ����ڹ�̽�ڼ�
	if CommonCheck( enCommonCheckCode.CHECKTYPE_IS_NATIONKILL, src_camp, des_camp, 0) == true then
		local level_A = GetWeakCampLevel(src_camp) or 0;
		local level_B = GetWeakCampLevel(des_camp) or 0;
		local beishu=week_camp_level_exp[level_A-level_B] ;
		if beishu == nil or beishu == 0 then beishu =1 ; end;
		return base_val*beishu;
		
	else -- ����ֱ��return
		return base_val;
	end 
	
	
end

-- �������ȼ�������
function  get_level_award_money(level, hard)
if level == nil or  level == 0 or hard == nil or hard == 0 then
   return 0;
end
if level < 1 or level > 159 then
   return 0;
end

if common_level_money == nil then 
	return 0;
end

return common_level_money[level][hard] or 0;
end

-- �����������Ƿ��ѿ�ʼ��ֻ�����ʾʱ��νӵ�����
function is_task_started( vTaskID )
  if not check_task(vTaskID,"is_task_started") then return false;end;   
  local t = AllTasks[vTaskID].accept_cond;  
  local ret = nil;
  local hour = tonumber( os.date("%H", os.time() ) );
  local minu = tonumber( os.date("%M", os.time() ) );
  --����������е�����ȫ������Ҫ������Ϊ���Խ�������;������Ϊ���ܽ�����
  if t ~= nil then
    ret = table.foreachi(t, function(i, v)  
   	if v.func == check_time_part then
	      -- �����ǰСʱ���������õ�
	      if hour > v.args.start_hour then -- �Ѿ���ʼ
			return true;
	      elseif hour < v.args.start_hour then
			return false;
	      else -- ==
			if minu >= v.args.start_minu then 
				return true;
			else
				return false;
			end
	      end
        end
    end);
  end
  
	if ret == nil then
		return false;
	end
	return ret;
end

-- ˢ����������
function refresh_chairman_tasks( s_task_id )

	if prob_tasks[s_task_id] == nil or AllChairManTasks[s_task_id] == nil  then
	   lua_error("****AllChairManTasks["..s_task_id.."]");
	   return {};
	end

	local rnd_table={AllChairManTasks[s_task_id].white_per, AllChairManTasks[s_task_id].blue_per, AllChairManTasks[s_task_id].purple_per , AllChairManTasks[s_task_id].gold_per};
	return get_tasks_by_prob(s_task_id, rnd_table, CHAIRMAN_SIZE);

end

-- ��������������� ���ò��øĶ��⽱��
-- ���ȫ������� ����true
function on_completed_chairmantask( nChairManID, nTimes )
	local ret={ is_finished=false, is_awarded=false};
	if  extra_awards[EXTRA_DEFINE.CHAIRMAN_TASK] ~= nil and extra_awards[EXTRA_DEFINE.CHAIRMAN_TASK][nChairManID] ~= nil then
			local t = extra_awards[EXTRA_DEFINE.CHAIRMAN_TASK][nChairManID][nTimes];
			if t~= nil then
				  ret.is_awarded=true;
				  local ret = table.foreachi(t, function(i, v)  
					if v.func ~= nil then
						v.args.task_id = 0;
						v.args.hard = 0;
						v.func(v.args, 1) ;
					end
				  end);
			end
	end
	lua_debug("manid="..nChairManID.." end_sz="..nTimes.." list_sz="..table.getn(AllChairManTasks[nChairManID].list));
	-- �ж��Ƿ�����
	if AllChairManTasks[nChairManID]~=nil and AllChairManTasks[nChairManID].list ~= nil and nTimes >= table.getn(AllChairManTasks[nChairManID].list) then
		ret.is_finished = true;
	end
	return ret;
end 

-- �õ�����ID
function get_chairman_id( vTaskID )
	if not check_task(vTaskID,"get_chairman_id") then return 0;end;
	return AllTasks[vTaskID].chairman_id;
end

-- �õ��������б�
function get_all_chairman_list()
	return AllChairManIDList;
end

-- ������������ID�õ������б�
function get_chairman_list_by_chairmanid( id )
	if AllChairManTasks[id]~= nil and AllChairManTasks[id].list ~= nil then
		return AllChairManTasks[id].list;
	end
	return {};
end

function get_task_group_id(vTaskID)
  if not check_task(vTaskID,"get_task_group_id") then return 0;end;
  return AllTasks[vTaskID].group_id or 0;
end

--  ���ÿ��Ҫ�����������
function  get_day_clear_tasks()
	return DayClearTasks;
end

-- ���ж��⽱�� ����1 2 3���� ������
function do_extra_awards( extra_type, task_id, param1, param2, param3 )
	if  extra_awards[extra_type] ~= nil then
		local t = {};
		if param1 ~= nil and param1 ~= 0 then
			t = extra_awards[extra_type][param1];
			if t == nil then return;end;
			
			if param2 ~= nil and param2 ~= 0 then
				t = extra_awards[extra_type][param1][param2];
				if t == nil then return;end;
				
				if param3 ~= nil and param3 ~= 0 then
					t = extra_awards[extra_type][param1][param2][param3];		
					if t == nil then return;end;					
				end
			end
		end
		
		local tHard=0;
		if task_id ~= 0 and AllTasks[task_id] ~= nil then
			tHard = AllTasks[task_id].task_hard;
		end

		if t~= nil then
			  local ret = table.foreachi(t, function(i, v)  
				if v.func ~= nil then
					v.args.task_id = task_id;
					if v.args.hard == nill then
						v.args.hard = tHard;
					end 	
					v.func(v.args, 1) ;
				end
			  end);
		end
	end
end

-- ���ÿ�������ӻ��������
function get_team_loop_num()
	return team_loop_num;
end


--�õ�������Ž�Ǯ
function  get_need_corps_money(vTaskID)

 --�õ�������Ž�Ǯ
  if not check_task(vTaskID,"get_need_corps_money") then return -1;end;
    
  local t = AllTasks[vTaskID].publish_cond;  
  local types = AllTasks[vTaskID].publish_type;
  if types ==0 or types == nil then return -1;end;
  
  local ret = 0;
  if t ~= nil then
   table.foreachi(t, function(i, v)  
   	if v.func == nil then
		lua_error("������nil2��check_publish������,vTaskID="..vTaskID);
	elseif v.func == check_corps_money then
	        ret = v.args.money;
        end
    end);
  end
  return ret;
end
