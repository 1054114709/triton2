-- Ǭ�������߼�lua�ļ�
-- ��Ҫ���߼����롢��C++�����ӿڣ��������Ķ�
-- ���ô����lucky_bag_cfg.lua��

-- ʹ��Ǭ��������
-- ����:���ʵ��ID��Ǭ�������ID��һ����ģ��ID��
-- ���أ���Ʒ�����ƷID������
function on_use_lucky_bag( player_entity_id, type_id )
	local ret = { award_type=0, item_id=0, num=0, notify_type=0, star=0 }; -- ���ص�����

	-- �������ñ����������ֽ���
	if  main_cfg==nil or main_cfg[type_id] == nil then
		return ret;
	end

	-- ��û�ط��� ������
	-- ���¸Ķ����������Ʒ��ʵ��ռ�ø�����
	local is_full=0;
	table.foreachi( main_cfg[type_id] , function(i, v)  
		--Log_Error(v.item_id.."--"..v.num );
		if string.sub( v.item_code, 1, 1 ) == "i" then
			local retx=CheckPileLimit(player_entity_id, v.item_id, v.num );
			if retx==true then
				--Log_Error("ret--ok");
			else
				is_full = 1;
				return 1;
			end
		end
	end );
	
	if is_full == 1 or GetPlayerBagSpaceNum(player_entity_id) < 1 then -- ������
		SendErrNotice(player_entity_id, -26198 );
		return ret;
	end	
	
	-- ׼�������
	local rnd_table={};
	local left=10000; -- �ݶ���ֱ�
	table.foreachi( main_cfg[type_id] , function(i, v)  
		table.insert( rnd_table, v.prob );
		left = left - v.prob;	
	end );
	
	if left > 0 then table.insert( rnd_table, left ); end; -- û��10000��ʣ�µ��浽�Ļ�����û����
	
	local tIndex = get_rand_index( rnd_table );
	if tIndex == nil or tIndex == 0 or tIndex > table.getn( main_cfg[type_id] ) then
		return ret;
	end
	
	-- **** ����ǷǶ��η�װ����Ķ�����ֻ1�ֵ��ߣ� ����C++����
	if main_cfg[type_id][tIndex].is_bag == nil or main_cfg[type_id][tIndex].is_bag == 0 then
		-- ����� q- �ǿ�������һ��Ǭ����
		if string.sub( main_cfg[type_id][tIndex].item_code, 1, 1 ) == "q" then
			return on_use_lucky_bag(player_entity_id, main_cfg[type_id][tIndex].item_id);
		end
		
		-- ���ݽ�����Ϣ�õ���ʵ�Ľ������ݣ�ID�ȣ�
		local item_final = switch_item( main_cfg[type_id][tIndex].item_code, main_cfg[type_id][tIndex].item_id , main_cfg[type_id][tIndex].num , player_entity_id, main_cfg[type_id][tIndex].notify_type );
	
		if item_final ~= nil then
			ret.award_type= item_final.award_type;
			ret.item_id= item_final.item_id;
			ret.num= item_final.num;
			ret.notify_type= main_cfg[type_id][tIndex].notify_type;
			ret.star = main_cfg[type_id][tIndex].star or 0; -- ����
			
			if item_final.award_type==enum_award_type.AWARD_TELEPORT then
				if teleport_points[item_final.item_id] ~= nil then
					ret.line_id=teleport_points[item_final.item_id].line_id;
					ret.map_id=teleport_points[item_final.item_id].map_id;
					ret.pos_x=teleport_points[item_final.item_id].x;
					ret.pos_y=teleport_points[item_final.item_id].y;
				end
			end
		end
	
	else -- �ǰ�  �Ƕ����Ʒ��
		ret.award_type = 0;
		-- ȡ�����������������
		if main_cfg[type_id][tIndex].item_id == nil or bags[main_cfg[type_id][tIndex].item_id] == nil then
			return ret;
		end
		
		local nItemNum = table.getn(bags[main_cfg[type_id][tIndex].item_id]);
		-- �жϰ��� ����� ֱ�Ӷ��������� ����
		if GetPlayerBagSpaceNum(player_entity_id) < nItemNum then -- ������
			SendErrNotice(player_entity_id, -26198 );
			return ret;
		end
		-- ��û���������������뱣֤ÿ����Ʒ���ܳ����ѵ����ޣ���
		table.foreachi( bags[main_cfg[type_id][tIndex].item_id], function(i, v)  
			local item_final = switch_item( v.item_code, v.item_id , v.num , player_entity_id, 0 );
			local ins_param={ entity_id=player_entity_id,
			                         item_id=item_final.item_id,
			                         num=item_final.num,
			                         star=v.star,
			                         invalid_time=0,};
			InsertItem(ins_param);
		end );
		ret.award_type = enum_award_type.AWARD_BAG;
		return ret;
	end
	
	return ret;
end

-- ��þ������ID�Ľ�������
-- ͬʱ�������Ĳ���
function switch_item( v_item_code, v_item_id, v_num, player_entityid, notify )
	local ret = { award_type=enum_award_type.AWARD_ITEM, item_id=v_item_id, num=v_num }; -- ���ص�����	
	
	if v_item_code==nil or v_item_id==nil or v_num==nil or player_entityid==nil then
		return ret;
	end
	
	-- �����"i-"�� ֱ�ӷ���
	if string.sub( v_item_code, 1, 1 ) == "i" then
		ret.award_type=enum_award_type.AWARD_ITEM;
		ret.item_id=v_item_id;
		ret.num=v_num;
	end
	
	-- �����m- �� ���ñ��������ʵ��ID
	if string.sub( v_item_code, 1, 1 ) == "m" then
		ret.award_type=enum_award_type.AWARD_ITEM;
		local metier = GetPlayerMetier(player_entityid);
		if metier_item_cfg[v_item_id]  ~= nil and metier ~= 0 then 
			ret.item_id=metier_item_cfg[v_item_id][metier] or v_item_id;
		end
		ret.num=v_num;
	end
	
	-- �����j-�� ���� �����Ա�
	if string.sub( v_item_code, 1, 1 ) == "j" then
		ret.award_type=enum_award_type.AWARD_ITEM;
		local jender = GetPlayerGender(player_entityid);
		if jender_item_cfg[v_item_id]  ~= nil and ( jender ==2 or jender == 3 ) then 
			ret.item_id=jender_item_cfg[v_item_id][jender] or v_item_id;
		end
		ret.num=v_num;
	end
	
	-- ����� t- �Ǵ���
	if string.sub( v_item_code, 1, 1 ) == "t" then
		ret.award_type=enum_award_type.AWARD_TELEPORT;
	end
	
	-- ����� f- ��BUFF
	if string.sub( v_item_code, 1, 1 ) == "f" then
		ret.award_type=enum_award_type.AWARD_OTHER;
		EntityInsertBuff(player_entityid, v_item_id, 0);
		if notify ~= nil or notify ~= 0 then
			SendErrNotice( player_entityid, notify );
		end
	end
	
	return ret;
end

-- �������� ���ˢ�������
-- eg: tab={10,20,5,15}  ���� 1,,2,3��4  ��ʾ�������ĸ�
function get_rand_index( tab )
	local n = table.getn( tab );
	local sum=0;
	for i=1, n do
		sum = sum+tab[i];
	end
	if sum == 0 then
		return 0;
	end
	local rnd = math.random(sum);
	local last_sum = 0;
	local ret = 0;
	for i=1, n do
		last_sum = last_sum + tab[i] or 0;
		ret = i;
		if rnd <= last_sum then
			return i;
		end
	end
	return ret;
end
