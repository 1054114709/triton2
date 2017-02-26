-- �Ʒ䶴dataKey
local Hornets_Data_Key =
{
	HORNETS_FIREBRANDB_STATUS		= 0,		--���B��״̬
	HORNETS_FIREBRANDC_STATUS		= 1,		--���C��״̬
	HORNETS_WHITEHAIREPRINCES_STATUS	= 2,		--��ë������ʱ����
	HORNETS_IMMORTALHAIRSLAY_STATUS		= 3,		--��ë��ʿ��ʱ����
	HORNETS_WALLB_ONE			= 4,		-- ���ɹ�����ʯǽB1
	HORNETS_WALLB_TWO			= 5,		-- ���ɹ�����ʯǽB2
	HORNETS_COUTEDOGRE			= 6,		-- ��Ҫ�����Ĺ���
	HORNETS_BOX				= 7,		-- ��������
	HORNETS_YELLOORGESTATUS			= 8,		-- �Ʒ��״̬
	HORNETS_DOORNEARFIREGEARA		= 9,		-- �������A�Ĵ���
	HORNETS_DOORNEARYELLOORGE		= 10,		-- �����Ʒ�ֵĴ���
}
-- ���Լ����Ĺ���ID
local CountedOgreID = 
{
	55678, 55676, 55675, 55677, 55679 --, 55683, 55681, 55680, 55682 
}

local ScoreType = 
{
	HONETSHOLE_SCORE_REPTIONLEVEL	  = 1,		--�����ȼ�
	HONETSHOLE_SCORE_OGRENUM	  = 2,		--��������
	HONETSHOLE_SCORE_TOTALTIME	  = 3,		--ͨ��ʱ��
	HONETSHOLE_SCORE_GENERALSCORE	  = 4,		--����
	HONETSHOLE_SCORE_EXTRALSCORE      = 5,		--��������
	HONETSHOLE_SCORE_TOTALSCORE	  = 6,		--������
}

-- ��ѿ��ر�־
local FLAGFIREON  = 1
local FLAGFIREOFF = 0

-- �ɹ�����ʯǽA
local StoneDoorCanbeAttackedA = { 90136, 55935 }
local StoneDoorCanbeAttackedB = { 90150, 55936 }



local MAX_NPCNUM_SAMETEMPID = 10


-- ��ѻ���
local FireGear = 
{	A = { index = 90128, id   = 55944 },	-- ������A 
	B = { index = 90129,id	  = 55945 },	-- ������B --������ʱ��
	C = { index = 90131,id    = 55946 },	-- ������C --������ʱ��
}
-- δ��ȼ�Ļ��
local FireBrand = 
{
	A = { index = 90118 , id   = 55950, },	-- ���A
	B = { index = 90123, id	  = 55951, },	-- ���B
	C = { index = 90122, id	  = 55952, },	-- ���C
}

-- ��ȼ�Ļ��
local FireBrandOnFire = 
{	
	-- ���A
	A = { 
		{ index = 90125,  id = 55947, },
		{ index = 90119,  id = 55947, },
	    },	

	-- ���B
	B = {
		{ index = 90120, id = 55948  },
		{ index = 90127, id = 55948 },
	    },

	-- ���C
	C = {
		{ index = 90121, id = 55949 },
		{ index = 90126, id = 55949 },
	    },
}

-- ��Ѵ�����npc�赲�ı�
local FireBrandBlock = 
{
	A = {					-- ���A����ȼʱ�ı���赲
		--{ id = 55939 },
		{ id = 52433 },
		{ id = 55944 },
		{ id = 55950 },
	    },

	B = {					-- ���B����ȼʱ�ı���赲
		{ id = 55945 },
		{ id = 55951 },
	    },

	C = {					-- ���C����ȼʱ�ı���赲
		{ id = 55946 },
		{ id = 55952 },
	    },

	D = {					-- ���B�ͻ��Cͬʱ����ʱ�ı���赲
		--{ id = 55939 },
		{ id = 55985 },
	    },
}

-- ����
local Ogre = 
{
	A = { index = 90094, id = 55682 },	-- �Ʒ��
	B = { index = 90136, id = 55935 },	-- �ɹ���ʯǽA , ������ʱ��
	C = { index = 90060, id = 55681 },	-- ��ë����  
	D = { index = 90150, id = 55936 },	-- ���Թ�����ʯǽB, ����ʱ������ʱ��
	E = { index = 90083, id = 55680 },	-- ��ë��ʿ
	F = { index = 90135, id = 55938 },	-- ���ɹ�����ʯǽB1
	G = { index = 90148, id = 55938 },	-- ���ɹ�����ʯǽB2
	H = { index = 90130, id = 55943 },	-- ����A
	J = { index = 90132, id = 55943 },	-- ����B
	K = { index = 90107, id = 55683 },	-- �Ʒ����
	L = { index = 90133, id = 55939 },	-- �Ʒ綴ʯ��1��������1�����رյ�ʯ��
	M = { index = 90155, id = 55939 },	-- �Ʒ綴ʯ��2���Ʒ�ִ����رյ�ʯ��

}

-- ��������������npc�赲�ı�
local OgreBlock =
{
	A = {					-- �Ʒ�ִ������赲�ı䣬npc����
			{ id = 55937  },			
	     },

	B = {					-- �ɹ���ʯǽA�������赲�ı�
			{ id = 55983 },
	     },
	C = {					-- ��ë�����������赲�ı䣬��Ҫ��ʱ���������
			{ id = 55998 },
	     },

	D = {					-- �ɹ�����ʯǽB�������赲�ı�
			{ id = 55984 },	
	    },

	E = {					-- ��ë��ʿ�������赲�ı�,��ʱ�����
			{ id = 55938 },		
			{ id = 55999 },		
	     },	
}	

-- ��������������npcˢ��
local OrgeRefresh = 
{
	A = {					-- �Ʒ�ִ�����npcˢ��
		{ index = 90136, id = 55935  },
		{ index = 90150, id = 55936  },
	    },

	B = {					-- �ɹ���ʯǽA������npcˢ��

	    },

	C = {					-- ��ë����������npcˢ��
		{ index = 90130, id = 55943  },
	    },

	D = {					-- �ɹ�����ʯǽB������npcˢ��
		
	    },

	E = {					-- ��ë��ʿ����������npcˢ��		
		{ index = 90132, id = 55943 },		
	    },	
}
-- �������
local TokenID = 45538
local TokenNum = 3

-- ʱ������

local RepetionCloseTime = 2700000;	-- �����ر�ʱ�� 3600000 ( 45���� )

local FireBrandSustainTime = 120000;	-- 2����

local WhitehairPrinceTime = 60000;	-- 1����

local ImmortHairLayTime	  = 60000;	-- 1����

-- �����رյ���ʱʱ��
REPETIONCLOSE_LEFTTIME = 120000	-- 2����

--����
local function relive( map_id, repetion_id, args, loop_index )
	PlayerRelive( repetion_id, 1, args.x1, args.y1 );
end

-- ��������رյ�֪ͨ
local function RepetionDoorClose( )
		
end

-- �ж��Ƿ�����Ҫ�����Ĺ���
local function IsCountedOrge( index, id )
	local i = 1
	while CountedOgreID[i] ~= nil do
		if CountedOgreID[i] == id then
			return  1
		end
		i = i + 1
	end
	return 0
end

-- �������
local function creat_firebrand( vRepetionID, vParame )
	local i = 1
	while vParame[i] ~= nil do
		CreateNpc( vRepetionID, vParame[i].index )
		i = i+1
	end
end

-- �ı��赲
local function destroyblock( vRepetionID, vParame )
	local i = 1
	while vParame[i] ~= nil do
		DestroyAliveTempOgre( vRepetionID, vParame[i].id ,MAX_NPCNUM_SAMETEMPID  )
		i = i + 1
	end
end


-- ��ø�������
local function NoticeRepetionscore( vReptionID )
	local Level = GetRepeLevel( vReptionID )
	local OgreNum = GetIntData( vReptionID, Hornets_Data_Key.HORNETS_COUTEDOGRE )
	local Time =  ( RepetionCloseTime - GetTime( vReptionID, 1 ) ) / 1000
	local BoxNum = GetIntData( vReptionID, Hornets_Data_Key.HORNETS_BOX )
	local BoxScore = (Level/45)*BoxNum*100
	local CommonScore = ( Level / 55 )*( ( OgreNum*OgreNum )/( 50 + Time )*100 + 200 )
	local TotalScore = BoxScore + CommonScore
	
	EventNoticeAll( vReptionID, RepetionNoticeEventKind.TAKE_COUNT,  ScoreType.HONETSHOLE_SCORE_REPTIONLEVEL,Level  )
	EventNoticeAll( vReptionID, RepetionNoticeEventKind.TAKE_COUNT,  ScoreType.HONETSHOLE_SCORE_OGRENUM,OgreNum  )
	EventNoticeAll( vReptionID, RepetionNoticeEventKind.TAKE_COUNT,  ScoreType.HONETSHOLE_SCORE_TOTALTIME,Time )
	EventNoticeAll( vReptionID, RepetionNoticeEventKind.TAKE_COUNT,  ScoreType.HONETSHOLE_SCORE_GENERALSCORE,CommonScore )
	EventNoticeAll( vReptionID, RepetionNoticeEventKind.TAKE_COUNT,  ScoreType.HONETSHOLE_SCORE_EXTRALSCORE,BoxScore )
	EventNoticeAll( vReptionID, RepetionNoticeEventKind.TAKE_COUNT,  ScoreType.HONETSHOLE_SCORE_TOTALSCORE,TotalScore )
	AddIntData2AllPlayer( vReptionID, 0, TotalScore )
end

-- ���͸����رյ���ʱ֪ͨ
local function NoticeRepetionCloseTime( vRepetionID )

	local Time = GetTime( vRepetionID, 1 )
	if Time > REPETIONCLOSE_LEFTTIME then
		Time = REPETIONCLOSE_LEFTTIME
		TimeBegin( vRepetionID, 2 )
		--ChangeTime( vRepetionID, 1, Time )
	end
	EventNoticeAll( vRepetionID, RepetionNoticeEventKind.COUNT_DOWN,0, Time )
end

--����NPC
local function create_ogre( vRepetionID, vParame )--, vParame1, vParame2 )


-- ��ӵ����ع۲��¼�	
	-- ��ѻ���A
	if FireGear.A.id == vParame.tempid  and FireGear.A.index == vParame.index then 
		ObserverMachinery( vRepetionID, vParame.entityid )
	end

	-- ��ѻ���B
	if FireGear.B.id == vParame.tempid  and FireGear.B.index == vParame.index then 
		ObserverMachinery( vRepetionID, vParame.entityid )
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_FIREBRANDB_STATUS, FLAGFIREOFF )
	end

	-- ��ѻ���C
	if FireGear.C.id == vParame.tempid  and FireGear.C.index == vParame.index then 
		ObserverMachinery( vRepetionID, vParame.entityid )
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_FIREBRANDC_STATUS, FLAGFIREOFF )
	end

--  ����۲��¼�

	-- �Ʒ��
	if vParame.tempid == Ogre.A.id and vParame.index == Ogre.A.index  then
		ObserverEntityDeath( vRepetionID, vParame.entityid )
	end

	-- �ɹ���ʯǽA
	if vParame.tempid == Ogre.B.id and vParame.index == Ogre.B.index  then
		ObserverEntityDeath( vRepetionID, vParame.entityid )
	end

	-- ��ë����
	if vParame.tempid == Ogre.C.id and vParame.index == Ogre.C.index  then
		ObserverEntityDeath( vRepetionID, vParame.entityid )
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_WHITEHAIREPRINCES_STATUS, 0 )
	end

	-- ���Թ�����ʯǽB
	if vParame.tempid == Ogre.D.id and vParame.index == Ogre.D.index  then
		ObserverEntityDeath( vRepetionID, vParame.entityid )
	end

	-- ��ë��ʿ
	if vParame.tempid == Ogre.E.id and vParame.index == Ogre.E.index  then
		ObserverEntityDeath( vRepetionID, vParame.entityid )
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_IMMORTALHAIRSLAY_STATUS, 0 )
	end

	-- ���ɹ�����ʯǽB1
	if vParame.tempid == Ogre.F.id and vParame.index == Ogre.F.index  then	
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_WALLB_ONE, vParame.entityid )
	end

	-- ���ɹ�����ʯǽB2		
	if vParame.tempid == Ogre.G.id and vParame.index == Ogre.G.index  then	
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_WALLB_TWO, vParame.entityid )
	end

	-- �Ƿ�����Ҫ�����Ĺ���
	if IsCountedOrge(  vParame.index, vParame.tempid ) == 1 then
		ObserverEntityDeath( vRepetionID, vParame.entityid )
	end

	-- ����
	if vParame.tempid == Ogre.H.id then	
		ObserverEntityDeath( vRepetionID, vParame.entityid )
	end

	-- �Ʒ����
	if vParame.tempid == Ogre.K.id and vParame.index == Ogre.K.index  then	
		ObserverEntityDeath( vRepetionID, vParame.entityid )		
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_YELLOORGESTATUS, 0 )
	end
	
	-- �Ʒ綴ʯ��1��������1�����رյ�ʯ��
	if vParame.tempid == Ogre.L.id and vParame.index == Ogre.L.index  then	
		ObserverEntityDeath( vRepetionID, vParame.entityid )		
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_DOORNEARFIREGEARA, vParame.entityid )
	end

	-- �Ʒ綴ʯ��2���Ʒ�ִ����رյ�ʯ��
	if vParame.tempid == Ogre.M.id and vParame.index == Ogre.M.index  then	
		ObserverEntityDeath( vRepetionID, vParame.entityid )		
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_DOORNEARYELLOORGE, vParame.entityid )
	end
end

--Npc����
local function ogre_death( vRepetionID, vParame )--vEntityID, vTempID )

-- �Ʒ�������¼�
	if vParame.tempid == Ogre.A.id and vParame.index == Ogre.A.index then
		-- �����赲
		destroyblock( vRepetionID, OgreBlock.A )
		CharacterDie( vRepetionID, GetIntData( vRepetionID, Hornets_Data_Key.HORNETS_WALLB_ONE ), 0 )

		-- ˢ��npc
		creat_firebrand( vRepetionID, OrgeRefresh.A )

		--����
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_COUTEDOGRE,  GetIntData(  vRepetionID, Hornets_Data_Key.HORNETS_COUTEDOGRE ) + 1 )
	end

-- �ɹ�����ʯǽA�����¼�
	if vParame.tempid == Ogre.B.id and vParame.index == Ogre.B.index then

		-- �����赲
		destroyblock( vRepetionID, OgreBlock.B )

		-- ����״̬
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_WHITEHAIREPRINCES_STATUS, 1  )

		-- ������ʱ��
		TimeBegin( vRepetionID, 5 )
	end

-- ��ë���������¼�
	if vParame.tempid == Ogre.C.id and vParame.index == Ogre.C.index then

		-- �����赲
		local PrincesStatus = GetIntData( vRepetionID, Hornets_Data_Key.HORNETS_WHITEHAIREPRINCES_STATUS )
		if PrincesStatus == 1 then
			destroyblock( vRepetionID, OgreBlock.C )
			CharacterDie( vRepetionID, GetIntData( vRepetionID, Hornets_Data_Key.HORNETS_WALLB_TWO ), 0 )
			creat_firebrand( vRepetionID, OrgeRefresh.C )
		end

		-- �������
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_COUTEDOGRE,  GetIntData(  vRepetionID, Hornets_Data_Key.HORNETS_COUTEDOGRE ) + 1 )
	end

--  ���Թ�����ʯǽB�����¼�
	if vParame.tempid == Ogre.D.id and vParame.index == Ogre.D.index then
		-- �����赲
		destroyblock( vRepetionID, OgreBlock.D )

		-- ����״̬
		SetIntData(  vRepetionID, Hornets_Data_Key.HORNETS_IMMORTALHAIRSLAY_STATUS, 1 )

		-- ������ʱ��
		TimeBegin( vRepetionID, 6 )
	end

-- ��ë��ʿ�����¼�
	if vParame.tempid == Ogre.E.id and vParame.index == Ogre.E.index then

		-- �����赲
		local LayStatus =  GetIntData( vRepetionID, Hornets_Data_Key.HORNETS_IMMORTALHAIRSLAY_STATUS )

		if LayStatus == 1 then		 
			destroyblock( vRepetionID, OgreBlock.E )
			creat_firebrand( vRepetionID, OrgeRefresh.E )
		end
		
		-- �������
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_COUTEDOGRE,  GetIntData(  vRepetionID, Hornets_Data_Key.HORNETS_COUTEDOGRE ) + 1 )
	end

-- �Ƿ�����Ҫ�����Ĺ���
	if IsCountedOrge(  vParame.index, vParame.tempid ) == 1 then		
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_COUTEDOGRE,  GetIntData(  vRepetionID, Hornets_Data_Key.HORNETS_COUTEDOGRE ) + 1 )
	end

-- �Ʒ����
	if vParame.tempid == Ogre.K.id and vParame.index == Ogre.K.index  then			
		NoticeRepetionCloseTime( vRepetionID )
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_YELLOORGESTATUS, 1 )
		InsertItemAll( vRepetionID, TokenID, TokenNum  )

		-- �������
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_COUTEDOGRE,  GetIntData(  vRepetionID, Hornets_Data_Key.HORNETS_COUTEDOGRE ) + 1 )

		-- ��������
		NoticeRepetionscore( vRepetionID )

		AwardFameAll( vRepetionID, 4 );
	end

-- ��������
	if vParame.tempid == Ogre.H.id then
		local BoxNum = GetIntData( vRepetionID, Hornets_Data_Key.HORNETS_BOX ) + 1
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_BOX, BoxNum  )
	end
end

local function time_assignment( vRepetionID, vParame )

end

--�����¼�
local function machinery_spring( vRepetionID, vParame )

-- ���A�Ĵ���
	if vParame.index == FireGear.A.index and vParame.tempid == FireGear.A.id then

		-- ����δ��ȼ�Ļ��
		destroyblock( vRepetionID, FireBrandBlock.A )
		CharacterDie( vRepetionID,  GetIntData( vRepetionID, Hornets_Data_Key.HORNETS_DOORNEARFIREGEARA ), 0 )
		-- ������ȼ�Ļ��
		creat_firebrand( vRepetionID, FireBrandOnFire.A )
	end

-- ���B�Ĵ���
	if vParame.index == FireGear.B.index and vParame.tempid == FireGear.B.id then

		-- ����δ��ȼ�Ļ��
		destroyblock( vRepetionID, FireBrandBlock.B )

		-- ������ȼ�Ļ��
		creat_firebrand( vRepetionID, FireBrandOnFire.B )

		-- ���û��״̬
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_FIREBRANDB_STATUS, FLAGFIREON  )

		local FirebrandCStatus = GetIntData( vRepetionID, Hornets_Data_Key.HORNETS_FIREBRANDC_STATUS )

		if FirebrandCStatus == FLAGFIREOFF then
		
			-- ������ʱ��
			TimeBegin( vRepetionID, 3 )

			-- ֪ͨ���B�Ѿ���ȼ
			EventNoticeAll( vRepetionID, RepetionNoticeEventKind.MSG, 1, FireBrandSustainTime ) 
		else
			
			-- ����赲
			destroyblock( vRepetionID, FireBrandBlock.D )

			-- �������
			CharacterDie( vRepetionID,  GetIntData( vRepetionID, Hornets_Data_Key.HORNETS_DOORNEARYELLOORGE ), 0 )

			-- ֹ֪ͨͣ��ѵ���ʱ
			EventNoticeAll( vRepetionID, RepetionNoticeEventKind.MSG, 2, 0 ) 
		end
	end

-- ���C�Ĵ���
	if vParame.index == FireGear.C.index and vParame.tempid == FireGear.C.id then

		-- ����δ��ȼ�Ļ��
		destroyblock( vRepetionID, FireBrandBlock.C )

		-- ������ȼ�Ļ��
		creat_firebrand( vRepetionID, FireBrandOnFire.C )

		-- ���û��״̬
		SetIntData( vRepetionID, Hornets_Data_Key.HORNETS_FIREBRANDC_STATUS, FLAGFIREON  )

		local FirebrandBStatus = GetIntData( vRepetionID, Hornets_Data_Key.HORNETS_FIREBRANDB_STATUS )

		if FirebrandBStatus == FLAGFIREOFF then

			-- ������ʱ��
			TimeBegin( vRepetionID, 4 )

			-- ֪ͨ���C�Ѿ���ȼ		
			EventNoticeAll( vRepetionID, RepetionNoticeEventKind.MSG, 0, FireBrandSustainTime ) 

		else
			-- ����赲
			destroyblock( vRepetionID, FireBrandBlock.D )

			-- �������
			CharacterDie( vRepetionID,  GetIntData( vRepetionID, Hornets_Data_Key.HORNETS_DOORNEARYELLOORGE ), 0 )

			-- ֹ֪ͨͣ��ѵ���ʱ
			EventNoticeAll( vRepetionID, RepetionNoticeEventKind.MSG, 2, 0 ) 
		end
	end
end

-- �����ر�
local function  close_reption( map_id, repetion_id, args, index )
	--local yellorgestatus = GetIntData( repetion_id, Hornets_Data_Key.HORNETS_YELLOORGESTATUS )
	--if yellorgestatus == 1 then
		--NoticeRepetionscore( repetion_id )
	--end

	RepetionClose( repetion_id )
end

-- ������ɫ
local function create_player( vRepetionID, vParame )
	
end

-- ���B�ļ�ʱʱ�䵽
local function Timeout_FirebrandB( map_id, repetion_id, args, index )

	local FireBrandCStatus = GetIntData( repetion_id, Hornets_Data_Key.HORNETS_FIREBRANDC_STATUS )

	-- ������C�Ѿ�����,��ˢ�»��
	if  FireBrandCStatus ~= FLAGFIREON then
		SetIntData( repetion_id, Hornets_Data_Key.HORNETS_FIREBRANDB_STATUS, FLAGFIREOFF ) -- ����״̬
		destroyblock( repetion_id, FireBrandOnFire.B ) --���Ļ��
		CreateNpc( repetion_id, FireGear.B.index )
		CreateNpc( repetion_id, FireBrand.B.index )			  -- ���������غ�δ��ȼ���
	end
end

-- ���C�ļ�ʱʱ�䵽
local function Timeout_FirebrandC( map_id, repetion_id, args, index )

	local FireBrandBStatus = GetIntData( repetion_id, Hornets_Data_Key.HORNETS_FIREBRANDB_STATUS )

	-- �������Ѿ�����,������ˢ�»��
	if  FireBrandBStatus ~= FLAGFIREON then	
		SetIntData( repetion_id, Hornets_Data_Key.HORNETS_FIREBRANDC_STATUS, FLAGFIREOFF ) -- ����״̬

		destroyblock( repetion_id, FireBrandOnFire.C )			  -- ����赲

		CreateNpc( repetion_id, FireGear.C.index )			  -- ���������غ�δ��ȼ���
		CreateNpc( repetion_id, FireBrand.C.index )			  
	end
end

-- ��ë�����ļ�ʱ����ʱ��
local function Timeout_WhitehairPrince( map_id, repetion_id, args, index )

	SetIntData( repetion_id, Hornets_Data_Key.HORNETS_WHITEHAIREPRINCES_STATUS, 0  )

end

-- ��ë��ʿ�ļ�ʱ����ʱ
local function Timeout_ImmortalHairsLay( map_id, repetion_id, args, index )
	SetIntData( repetion_id, Hornets_Data_Key.HORNETS_IMMORTALHAIRSLAY_STATUS, 0  )
end


-- ������������
repetion = 
{
	baseinfo = 
	{
		repetion_index = RepetionID.HORNETSHOLE,
		playercountmax = 6,		-- �����������
		mapid = { 91 },			-- ������ͼID
		taskid = 0,			-- ���븱����ǰ������
		posx = 9,			-- ��ʱ����
		posy = 277,			-- ��ʱ����
		pernumber = 1,			-- ÿ����븱���Ĵ����� 0-����
		minlevel = 40,			-- ��ͽ���ȼ�
		maxlevel = 120,			-- 
		--check_time = 20000,		-- ��鸱������ʱ��(����)
                weekpernumber = 4,
		question_check=0,		-- �Ƿ���и���������֤
		relogin =	1,					-- 1��ʾ������0��ʾ��������
		closetime   = 120,	  -- û����ʱ��ú�ر�
		special = 
		{
			{ item = 63856, flag = 3 },
		},
		-- �����Ϣ
		team = 
		{
			teamin = true,		-- �Ƿ���ӽ��룻 ture-��Ҫ���; false - �������
			count = 3,		-- �����������
		},
		

		backpos = 
		{
			mapid = 1,			-- ��ʱ����
			posx = 33,			-- ��ʱ����	
			posy = 13,			-- ��ʱ����
		},

		-- ��������ʱ��
		open = 
		{
			-- ��, �£��ܣ� �գ� ʱ, �֣� ��
			-- 0 �ǲ�����ʱ�� ����ÿ�µڼ���
			--��һ��ʱ��

			{
				start = { year = 0, month = 0, week = 0, day = 0, hr = 13, minute = 00, sec = 0 },
				finish = { year = 0, month = 0, week = 0, day = 0, hr = 15, minute = 00, sec = 0 }
			},
			--�ڶ���ʱ��
			{
				start = { year = 0, month = 0, week = 0, day = 0, hr = 18, minute = 00, sec = 0 },
				finish = { year = 0, month = 0, week = 0, day = 0, hr = 21, minute = 00, sec = 0 }
			},
		}
	},
	-- ��ʱ��
	timer = 
	{ 
		-- ������ʼʱ��ʱ����ʼ
		{
			kind = RepetionTimeBeginKind.START_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = RepetionCloseTime,			
			loop = 1,
			func = close_reption,
			args = { },
			sync = { kind = RepetionTimeSyncKind.ALL, key = 0 },
		},
		

		-- �����رռ�ʱ��
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = REPETIONCLOSE_LEFTTIME,
			loop = 1,
			func = close_reption,
			args = { },

		},

		-- ���B��ʱ��
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = FireBrandSustainTime,
			loop = 1,
			func = Timeout_FirebrandB,
			args = { }
		},
		
		-- ���C��ʱ��
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = FireBrandSustainTime,
			loop = 1,
			func = Timeout_FirebrandC,
			args = { }
		},
		

		-- ��ë�����ļ�ʱ��
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = FireBrandSustainTime,
			loop = 1,
			func = Timeout_WhitehairPrince,
			args = { }
		},

		-- ��ë��ʿ�ļ�ʱ��
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = FireBrandSustainTime,
			loop = 1,
			func = Timeout_ImmortalHairsLay,
			args = { }
		},
	},

	event = 
	{
		[ RepetionEventKind.PLAYER_CREATE ] = { func = create_player },
		[ RepetionEventKind.OGRE_CREATE ] = { func = create_ogre },
		[ RepetionEventKind.OGRE_DEATH	] = { func = ogre_death },
		[ RepetionEventKind.TIME_ASSIGNMENT ] = { func = time_assignment },
		[ RepetionEventKind.BOX_MACHINERY_SPING ] = { func = machinery_spring },
	},
}



 
