-- ȫ��ս��dataKey
local GlobalWar_Data_Key =
{	
	GlobalWar_Data_CAMP1_NUM = 0,		-- ��Ӫ1������
	GlobalWar_Data_CAMP2_NUM = 1,		-- ��Ӫ2������
	GlobalWar_Data_CAMP1_SCORE= 3,	-- ��Ӫ1�Ļ���
	GlobalWar_Data_CAMP2_SCORE= 4,	-- ��Ӫ2�Ļ���
	GlobalWar_Data_CAMP1_BuddhaID= 5,	-- ��Ӫ1���������ʵ��ID
	GlobalWar_Data_CAMP2_BuddhaID= 6,	-- ��Ӫ2���������ʵ��ID
	CAMP1_OGRE_NUM	=	7,							-- ��Ӫ1�Ĺ�������
	CAMP2_OGRE_NUM	=	8,							-- ��Ӫ2�Ĺ�������
	REPETION_END_FLAG	=	9,							-- ��Ӫ2�Ĺ�������	0��ʾû�н���1��ʾ�Ѿ�����
	CAMP1_PLYER_KILLEDNUM=10,					--  ��Ӫ1ɱ��������
	CAMP1_OGRE_KILLEDNUM=11, 					--  ��Ӫ1ɱ��������
	CAMP1_BOSS_KILLEDNUM=12,						--  ��Ӫ1ɱ����BOSS����
	CAMP2_PLYER_KILLEDNUM=13,					--  ��Ӫ2ɱ��������
	CAMP2_OGRE_KILLEDNUM=14, 					--  ��Ӫ2ɱ��������
	CAMP2_BOSS_KILLEDNUM=15,					--  ��Ӫ2ɱ����BOSS����
	MAP_PLAYER_NUM =  16,					--  ������ͼ������
	HIEROGRAN_CREATE_INDEX =  17,					--  ���������ʽ����
	HIEROGRAN_TIMESS =  18	,				--  �������
}

-- ����ս����Ϣ
local Player_War_Data_INDEX = 
{
	WAR_SCORE 			=  0,
	PALYER_KILLEDNUM=  1,
	OGRE_KILLEDNUM	=  2,
	BOSS_KILLEDNUM	=	 3,
	TOTAL_SCORE			=  4,
	ReliveTimes			=  5,
	STATUS_INWAR 		=	 6,			-- 0��ʾ֮ǰ����ս����1��ʾ֮ǰ��ս����
}



--ս���赲ID,��ʱ�����
WAR_PREPARE_BLOCK_ID = { 76584, 76583 }
WAR_PREPARE_TIME =  120000--120000 -- 2����
MAX_BLOCK_NUM = 100

--ħ���ſ���
WAR_MAGIC_DOOR_BLOCK_ID = { 52433, 40293}
WAR_MAGIC_DOOR_TIME = 120000 -- 2����

--����ˢ������ʱ
WAR_ARMYSYMBOL_TIME = 120000 --300000 -- 2����

-- ���ˢ��ʱ��
HIEROGRAN_TIME = 60000

-- С����ˢ��ʱ�� 
LITTLE_OGRE_TIME = 60000

-- ��Ӫ��Ϣ
CampData = 
{
	Camp1ID = 1,
	Camp2ID = 2,
	Camp1PosX = 64,--3,  
	Camp1PosY = 4,--73,  
	Camp2PosX = 22,--136,  
	Camp2PosY = 117,--29,   
}

-- buff
WarBuff = 
{
	[CampData.Camp1ID] = 76422,
	[CampData.Camp2ID] = 76423,
	EscapBuff = 76424,
	EndBuff = 77030,
	TimeLimitBuff = 77176,
}

-- ������Ҫˢ�µ�npc
EndNpcIndex = 
{
	155076,155077,155080, 155081,
}

--�������
GoldSodiersConfig =
{
	[1] = 
	{
		GoldSodiersIndex = 
		{ 
			[CampData.Camp1ID] = { 155032, 155028, 155029 },			-- �������������
			[CampData.Camp2ID] = { 155038, 155034, 155035 },			-- �������������
		},
		ArmySymbolIndex = 155015,					-- ����������
	},
	[2] = 
	{
		GoldSodiersIndex =
		{ 
			[CampData.Camp1ID] = { 155030, 155031, 155032 },			-- �������������
			[CampData.Camp2ID] = { 155036, 155037, 155038 },			-- �������������
		},						
		ArmySymbolIndex = 155016,		
	}	,
}


-- ս��ʱ��
RepetionCloseTime =  1200000--600000 --900000

-- �����رյ���ʱʱ��
REPETIONCLOSE_LEFTTIME = 120000--30000	-- 30��

-- ս������
WarScoreConfig = 
{
	Player= 	-- ɱ����ҵĻ���
	{ 
		SelfScore=1, -- ���˻�õĻ���
		CampScore=1, -- ��Ӫ����	
	},			
	EndScore=200,		-- ����ս���Ļ���	
	OgreScore= 		-- ɱ����ͨ�ֵĻ���
	{ 
		SelfScore=5, -- ���˻�õĻ���	
		CampScore=5, --  ��Ӫ�Ļ���			
	},
	Boss= 				-- boss�ֵĻ���
	{ 		
		SelfScore=50, -- ���˻�õĻ���	
		CampScore=50, --  ��Ӫ�Ļ���			
	},	
	ScoreLimit=100, -- �������޲��ܳ���100
	ExtraScore=
	{
		WinCamp = 200,
		LoseCamp = 50,
	},
	Item =
	{
		ID = 76640,
		Num = 1,
		LoseNum = 1,	
		Level = 90,
	},
	LittleOgre = 
	{
		CampScore = 5,
	},
}

-- ������Ϣ
OgreConfig =
{
	[155032] = { CampID = CampData.Camp1ID, IsBossOgre=0, AddScore=0, },		--�����·��һ��
	[155028] = { CampID = CampData.Camp1ID, IsBossOgre=0, AddScore=0, },	
	[155029] = { CampID = CampData.Camp1ID, IsBossOgre=0, AddScore=0, },	
	
	[155030] = { CampID = CampData.Camp1ID, IsBossOgre=0, AddScore=0, },	-- �����·�ڶ���
	[155031] = { CampID = CampData.Camp1ID, IsBossOgre=0, AddScore=0, },
	[155032] = { CampID = CampData.Camp1ID, IsBossOgre=0, AddScore=0, },
	
	[155019] = { CampID = CampData.Camp1ID, IsBossOgre=0, AddScore=1, },		-- ��·����
	[155020] = { CampID = CampData.Camp1ID, IsBossOgre=0, AddScore=1, },
	[155021] = { CampID = CampData.Camp1ID, IsBossOgre=0, AddScore=1, },
	[155022] = { CampID = CampData.Camp1ID, IsBossOgre=0, AddScore=1, },		
	[155017] = { CampID = CampData.Camp1ID, IsBossOgre=1, AddScore=1, },			
	
	[155038] = { CampID = CampData.Camp2ID, IsBossOgre=0, AddScore=0, },	-- �����·��һ��
	[155034] = { CampID = CampData.Camp2ID, IsBossOgre=0, AddScore=0, },
	[155035] = { CampID = CampData.Camp2ID, IsBossOgre=0, AddScore=0, },
	
	[155036] = { CampID = CampData.Camp2ID, IsBossOgre=0, AddScore=0, },	-- �����·�ڶ���
	[155037] = { CampID = CampData.Camp2ID, IsBossOgre=0, AddScore=0, },
	[155038] = { CampID = CampData.Camp2ID, IsBossOgre=0, AddScore=0, },
	
	[155023] = { CampID = CampData.Camp2ID, IsBossOgre=0, AddScore=1, }, -- ��·����		
	[155024] = { CampID = CampData.Camp2ID, IsBossOgre=0, AddScore=1, },
	[155025] = { CampID = CampData.Camp2ID, IsBossOgre=0, AddScore=1, },
	[155026] = { CampID = CampData.Camp2ID, IsBossOgre=0, AddScore=1, },	
	[155018] = { CampID = CampData.Camp2ID, IsBossOgre=1, AddScore=1, },		
}

-- �赲��ʧ����Ҫ�����Ĺ���
OgreIndex=
{
	155019, 155020, 155021, 155022, 155017,
	155023, 155024, 155025, 155026, 155018,
}

-- ����buff
BufferID=76058

-- ��Ϣ
MSG = 
{
	SELE_CAMP_ROLENUM = 0,	-- ������Ӫ����
	ENEMY_CAMP_ROLENUM=1,	-- �з���Ӫ����
	KILLED_PLAYER_NUM	 = 2, -- ��ɱ������
	CAMP_SCORE	 = 3,				-- ������Ӫ����
	RELIVE_TIMES = 4,				-- ������
	KILLED_OGRE_NUM =5,			-- ɱ�������Ŀ
	ENEMY_CAMP_SCORE =6,			-- �з���Ӫ����
	ARMYSYMBOL_START =7,			-- ��������
	BOSS_DEATH =8,			-- boss����
	SELF_BOSS_STATUS =9,			-- ����boss״̬
	ENEMY_BOSS_STATUS=10,	-- �з�boss״̬
	SELF_OGRE_NUM=11,	-- ������������
	ENEMY_OGRE_NUM=12,	-- ������������
}

-- �����Ϣ
local Hierogran_Data =
{
	[1] = { x=38, y=56, 	temp=76594 },
	[2] = { x=36, y=65, 	temp=76592 },
	[3] = { x=42, y=49, 	temp=76592 },
	[4] = { x=32, y=53, 	temp=76593 },
	[5] = { x=47, y=59, 	temp=76593 },  
	[6] = { x=7,  y=7,  	temp=76594 }, 
	[7] = { x=73, y=120,	temp=76594 }, 
	[8] = { x=4,  y=117,	temp=76592 }, 
	[9] = { x=72, y=10,		temp=76592 }, 
}

local Hierogran_CreateWay = 
{
	[1] = { 4,5,9,2,8,7,3,4,6},
	[2] = { 3,7,4,9,6,5,2,3,8},
	[3] = { 5,6,8,4,2,7,9,3,5},
	[4] = { 3,8,5,4,3,2,7,6,9},
	[5] = { 5,6,7,5,9,3,8,4,2},
	[6] = { 4,7,2,5,9,4,3,6,8},
	[7] = { 4,3,5,6,8,2,7,4,9},
	[8] = { 4,2,8,3,5,9,7,4,6},
	[9] = { 1,7,9,2,8,3,4,6,5},
	[10] = { 1,7,2,5,6,8,3,9,4},
	[11] = { 1,5,2,3,7,9,4,8,6},
	[12] = { 1,4,9,2,5,6,3,7,8},
	[13] = { 1,9,4,8,2,5,6,7,3},
	[14] = { 5,2,8,7,6,9,5,3,4},
	[15] = { 3,9,2,8,5,3,4,6,7},
	[16] = { 3,2,5,6,9,7,3,8,4},
	[17] = { 2,4,8,3,6,2,9,5,7},
	[18] = { 5,3,8,4,9,7,2,6,5},
	[19] = { 2,3,5,4,9,8,7,6,2},
	[20] = { 1,2,6,7,9,5,4,3,8},	
}

-- С������Ϣ
local LittleOgreData = 
{
	Index		 = { 155083, 155084, 155085 },
	[155083] = { x=6, y=8, temp=77021 }, 
	[155084] = { x=39, y=56, temp=77021 }, 
	[155085] = { x=72, y=117, temp=77021 }, 
}


-- ��ø�������
local function NoticeRepetionscore( vReptionID )
	
end

-- ���͸����رյ���ʱ֪ͨ
local function NoticeRepetionCloseTime( vRepetionID )

-- ��������ʱ��ʼ
end

--����NPC
local function create_ogre( vRepetionID, vParame )--, vParame1, vParame2 )
	
	-- ��Ӫ1���ı���
	if vParame.index == GoldSodiersConfig[1].ArmySymbolIndex then
		ObserverMachinery( vRepetionID, vParame.entityid )
	end
	
	-- ��Ӫ2���ı���
	if vParame.index == GoldSodiersConfig[2].ArmySymbolIndex then
		ObserverMachinery( vRepetionID, vParame.entityid )
	end
	
	-- С����
	if LittleOgreData[vParame.index] ~= nil then
		ObserverEntityDeath( vRepetionID, vParame.entityid )
	end
	
	-- ����ǻ��ֹ���ע��
	if OgreConfig[vParame.index] ~= nil then
		ObserverEntityDeath( vRepetionID, vParame.entityid )
		SetCampID( vRepetionID, vParame.entityid, OgreConfig[vParame.index].CampID )			
		-- boss��	
		if OgreConfig[vParame.index].IsBossOgre == 1 then
			if OgreConfig[vParame.index].CampID == CampData.Camp1ID then
				SetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_BuddhaID, vParame.entityid )
				Camp1OgreNum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_OGRE_NUM )
				buffernum = 0
				while buffernum < Camp1OgreNum do
						EntityInsertBuff( vRepetionID, vParame.entityid, BufferID )
						buffernum = buffernum + 1
				end			
				EntityInsertBuff( vRepetionID, vParame.entityid, WarBuff[CampData.Camp1ID] )
				EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.SELF_BOSS_STATUS, 0 ) 
				EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.ENEMY_BOSS_STATUS, 0 ) 
			else
				SetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_BuddhaID, vParame.entityid )
				Camp2OgreNum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_OGRE_NUM )
				buffernum = 0
				while buffernum < Camp2OgreNum do
						EntityInsertBuff( vRepetionID, vParame.entityid, BufferID )
						buffernum = buffernum + 1
				end		
				EntityInsertBuff( vRepetionID, vParame.entityid, WarBuff[CampData.Camp2ID] )	
				EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.SELF_BOSS_STATUS, 0 ) 
				EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.ENEMY_BOSS_STATUS, 0 ) 
			end
		-- ��ͨ��
		else			
			if OgreConfig[vParame.index].CampID == CampData.Camp1ID then
				Camp1OgreNum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_OGRE_NUM ) + 1
				SetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_OGRE_NUM, Camp1OgreNum )				
				BossEntityID = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_BuddhaID )
				if BossEntityID > 0 then
					EntityInsertBuff( vRepetionID, BossEntityID, BufferID )
				end
				EntityInsertBuff( vRepetionID, vParame.entityid, WarBuff[CampData.Camp1ID] )
				EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.SELF_OGRE_NUM, Camp1OgreNum ) 
				EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.ENEMY_OGRE_NUM, Camp1OgreNum ) 			
			else
				Camp2OgreNum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_OGRE_NUM ) + 1
				SetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_OGRE_NUM, Camp2OgreNum )
				BossEntityID = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_BuddhaID )
				if BossEntityID > 0 then
					EntityInsertBuff( vRepetionID, BossEntityID, BufferID )
				end
				EntityInsertBuff( vRepetionID, vParame.entityid, WarBuff[CampData.Camp2ID] )
				EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.SELF_OGRE_NUM, Camp2OgreNum ) 
				EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.ENEMY_OGRE_NUM, Camp2OgreNum ) 		
			end						
		end
	end
end

-- ����ս��
local function  endglobalwar( map_id, repetion_id, args, index )	

	local endflag = GetIntData( repetion_id, GlobalWar_Data_Key.REPETION_END_FLAG )
	if endflag == 1 then
		return
	end		 
	
	-- ˢ��npc
	index = 1
	while EndNpcIndex[index] ~= nil do
		CreateNpc( repetion_id, EndNpcIndex[index] )		
		index = index + 1	
	end
	
	-- �޵�buff
	PlayerInsertBuffByMapID( repetion_id, WarBuff.EndBuff, 156 )
	
	SetIntData( repetion_id, GlobalWar_Data_Key.REPETION_END_FLAG, 1 )	
	-- ���㸱������
	local campid=0
	local camp1_score =	GetIntData( repetion_id, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_SCORE )
	local camp2_score = GetIntData( repetion_id, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_SCORE )     
	
	-- ����������,����֪ͨ���	
	repetionlevel=GetRepeLevel(repetion_id)
	if camp1_score == camp2_score then
		AddIntDataByCampID( repetion_id, CampData.Camp1ID, Player_War_Data_INDEX.WAR_SCORE, WarScoreConfig.ExtraScore.LoseCamp )
		AddIntDataByCampID( repetion_id, CampData.Camp1ID, Player_War_Data_INDEX.TOTAL_SCORE, WarScoreConfig.ExtraScore.LoseCamp ) 
		AddIntDataByCampID( repetion_id, CampData.Camp2ID, Player_War_Data_INDEX.WAR_SCORE, WarScoreConfig.ExtraScore.LoseCamp )
		AddIntDataByCampID( repetion_id, CampData.Camp2ID, Player_War_Data_INDEX.TOTAL_SCORE, WarScoreConfig.ExtraScore.LoseCamp ) 
		EventNoticeByCamp( repetion_id, CampData.Camp1ID,  RepetionNoticeEventKind.END, 2, 0 ) 			
		EventNoticeByCamp( repetion_id, CampData.Camp2ID,  RepetionNoticeEventKind.END, 2, 0 ) 
		if repetionlevel > WarScoreConfig.Item.Level then
			InsertItemByCamp( repetion_id, CampData.Camp1ID,  WarScoreConfig.Item.ID, WarScoreConfig.Item.LoseNum, 0 )
			InsertItemByCamp( repetion_id, CampData.Camp2ID,  WarScoreConfig.Item.ID, WarScoreConfig.Item.LoseNum, 0 )
		end
	elseif camp1_score > camp2_score then		
		AddIntDataByCampID( repetion_id, CampData.Camp1ID, Player_War_Data_INDEX.WAR_SCORE, WarScoreConfig.ExtraScore.WinCamp )
		AddIntDataByCampID( repetion_id, CampData.Camp1ID, Player_War_Data_INDEX.TOTAL_SCORE, WarScoreConfig.ExtraScore.WinCamp ) 
		AddIntDataByCampID( repetion_id, CampData.Camp2ID, Player_War_Data_INDEX.WAR_SCORE, WarScoreConfig.ExtraScore.LoseCamp )
		AddIntDataByCampID( repetion_id, CampData.Camp2ID, Player_War_Data_INDEX.TOTAL_SCORE, WarScoreConfig.ExtraScore.LoseCamp ) 
		EventNoticeByCamp( repetion_id, CampData.Camp1ID,  RepetionNoticeEventKind.END, 1, 0 ) 			
		EventNoticeByCamp( repetion_id, CampData.Camp2ID,  RepetionNoticeEventKind.END, 0, 0 ) 
		if repetionlevel > WarScoreConfig.Item.Level then
			InsertItemByCamp( repetion_id, CampData.Camp1ID,  WarScoreConfig.Item.ID, WarScoreConfig.Item.Num, 0 )
			InsertItemByCamp( repetion_id, CampData.Camp2ID,  WarScoreConfig.Item.ID, WarScoreConfig.Item.LoseNum, 0 )
		end
		campid = CampData.Camp1ID
	else	
		AddIntDataByCampID( repetion_id, CampData.Camp1ID, Player_War_Data_INDEX.WAR_SCORE, WarScoreConfig.ExtraScore.LoseCamp )
		AddIntDataByCampID( repetion_id, CampData.Camp1ID, Player_War_Data_INDEX.TOTAL_SCORE, WarScoreConfig.ExtraScore.LoseCamp ) 
		AddIntDataByCampID( repetion_id, CampData.Camp2ID, Player_War_Data_INDEX.WAR_SCORE, WarScoreConfig.ExtraScore.WinCamp )
		AddIntDataByCampID( repetion_id, CampData.Camp2ID, Player_War_Data_INDEX.TOTAL_SCORE, WarScoreConfig.ExtraScore.WinCamp ) 
		EventNoticeByCamp( repetion_id, CampData.Camp1ID,  RepetionNoticeEventKind.END, 0, 0 ) 
		EventNoticeByCamp( repetion_id, CampData.Camp2ID,  RepetionNoticeEventKind.END, 1, 0 ) 		
		if repetionlevel > WarScoreConfig.Item.Level then
			InsertItemByCamp( repetion_id, CampData.Camp2ID,  WarScoreConfig.Item.ID, WarScoreConfig.Item.Num, 0 )
			InsertItemByCamp( repetion_id, CampData.Camp1ID,  WarScoreConfig.Item.ID, WarScoreConfig.Item.LoseNum, 0 )
		end		
		campid = CampData.Camp2ID
	end			
	
	-- ���˻���
	EventNoticeAllInPlayerData( repetion_id, RepetionNoticeEventKind.TAKE_COUNT, 1, Player_War_Data_INDEX.WAR_SCORE  )

	-- ������
	CheckAward( repetion_id, campid );	
	
	-- �Ŷӻ���
	EventNoticeByCamp( repetion_id, CampData.Camp1ID,  RepetionNoticeEventKind.TAKE_COUNT, 2, camp1_score ) 
	EventNoticeByCamp( repetion_id, CampData.Camp2ID,  RepetionNoticeEventKind.TAKE_COUNT, 2, camp2_score ) 	
	
	-- �ܻ���		
	AddIntDataByCampID( repetion_id, CampData.Camp1ID, Player_War_Data_INDEX.WAR_SCORE, camp1_score )
	AddIntDataByCampID( repetion_id, CampData.Camp2ID, Player_War_Data_INDEX.WAR_SCORE, camp2_score )
	EventNoticeAllInPlayerData( repetion_id, RepetionNoticeEventKind.TAKE_COUNT, 3, Player_War_Data_INDEX.WAR_SCORE )	
	
	-- ��ɱ����
	--EventNoticeAllInPlayerData( repetion_id, RepetionNoticeEventKind.TAKE_COUNT, 4, Player_War_Data_INDEX.KILLED_PLAYER_NUM  )
	-- ��ɱ�����
	--EventNoticeAllInPlayerData( repetion_id, RepetionNoticeEventKind.TAKE_COUNT, 5, Player_War_Data_INDEX.KILLED_OGRE_NUM  )
	
	-- ����֮ǰ�Ķ�ʱ��
	TimeEnd( repetion_id, 1 )	 
	-- ��ʼ����ʱ
	TimeBegin( repetion_id, 2 )
	EventNoticeAll( repetion_id, RepetionNoticeEventKind.CLOSE, REPETIONCLOSE_LEFTTIME )		
	-- ֪ͨȫ�ַ�����ս���Ѿ�����
	EndGlobalWar( repetion_id )
end

--Npc����
local function ogre_death( vRepetionID, vParame )
	
	-- �������
	local playerscore = 0
	local campscore = 0
	local bossnum = 0
	local ogrenum = 0
	local campid = 0
	local playernum = 0
	
	-- �������
	if vParame.killedisplayer == 1 then					
		playerscore = WarScoreConfig.Player.SelfScore
		playernum = 1
		campscore = WarScoreConfig.Player.CampScore
		if GetCampID( vRepetionID,vParame.killedid ) == CampData.Camp1ID then
			campid = CampData.Camp2ID
		else
			campid = CampData.Camp1ID
		end			
		local relivetimes = GetIntData2Player( vRepetionID, vParame.killedid, Player_War_Data_INDEX.ReliveTimes )	+ 1	
		SetIntData2Player( vRepetionID, vParame.killedid, Player_War_Data_INDEX.ReliveTimes, relivetimes )
		EventNoticeSingle( vRepetionID, vParame.killedid,  RepetionNoticeEventKind.MSG, MSG.RELIVE_TIMES, relivetimes )
		ObserverEntityDeath( vRepetionID, vParame.killedid )
	--��������
	elseif OgreConfig[vParame.index] ~= nil then
		if 	OgreConfig[vParame.index].IsBossOgre == 1 then
			playerscore = WarScoreConfig.Boss.SelfScore
			campscore = WarScoreConfig.Boss.CampScore
			bossnum = 1
		elseif 	OgreConfig[vParame.index].AddScore == 1 then
			playerscore = WarScoreConfig.OgreScore.SelfScore
			campscore = WarScoreConfig.OgreScore.CampScore
			ogrenum = 1
		end					
			
		 if OgreConfig[vParame.index].CampID == CampData.Camp1ID then					
		 	campid = CampData.Camp2ID 
		 else
		 	campid = CampData.Camp1ID  
		 end			
		
		-- ����buff
		-- boss��		
		if OgreConfig[vParame.index].IsBossOgre == 1 then
			playername=GetNameByCharID( vRepetionID, vParame.killercharid )
			if campid == CampData.Camp1ID then
				SetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_BuddhaID, 0 )
				EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.BOSS_DEATH, 1, playername, 0 ) 
				EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.BOSS_DEATH, 0, playername, 0 ) 
				EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.SELF_BOSS_STATUS, 1 ) 
				EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.ENEMY_BOSS_STATUS, 1 ) 	
			else
				SetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_BuddhaID, 0 )
				EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.BOSS_DEATH, 0, playername, 0 ) 
				EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.BOSS_DEATH, 1, playername, 0 ) 	
				EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.SELF_BOSS_STATUS, 1 ) 
				EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.ENEMY_BOSS_STATUS, 1 ) 	
			end		
		-- ��ͨ��
		else
			if campid == CampData.Camp2ID then							
				local	OgreNum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_OGRE_NUM ) - 1			
				SetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_OGRE_NUM, OgreNum )											
				local	BossEntityID = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_BuddhaID )
				if BossEntityID > 0 then
					EntityRemoveBuff( vRepetionID, BossEntityID, BufferID  )				
				end
				EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.SELF_OGRE_NUM, OgreNum ) 
				EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.ENEMY_OGRE_NUM, OgreNum )
			else
				local	OgreNum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_OGRE_NUM ) - 1			
				SetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_OGRE_NUM, OgreNum )					
				local	BossEntityID = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_BuddhaID )
				if BossEntityID > 0 then
					EntityRemoveBuff( vRepetionID, BossEntityID, BufferID )				
				end
				EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.SELF_OGRE_NUM, OgreNum ) 
				EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.ENEMY_OGRE_NUM, OgreNum )
			end
		end			
	-- С��������	
	elseif LittleOgreData[vParame.index] ~= nil then
		campscore = WarScoreConfig.LittleOgre.CampScore		
		campid = vParame.killercampid 						
		CreateHierogram( vRepetionID, LittleOgreData[vParame.index].temp, LittleOgreData[vParame.index].x, LittleOgreData[vParame.index].y )			
	end						
	
	-- �����ɱ����
	if vParame.killercharid ~= 0 then			
		AddIntData2Player( vRepetionID, vParame.killerid, Player_War_Data_INDEX.PALYER_KILLEDNUM, playernum )		
		AddIntData2Player( vRepetionID, vParame.killerid, Player_War_Data_INDEX.OGRE_KILLEDNUM, ogrenum )					
		AddIntData2Player( vRepetionID, vParame.killerid, Player_War_Data_INDEX.BOSS_KILLEDNUM, bossnum )
		GotedScore = GetIntData2Player( vRepetionID, vParame.killerid, Player_War_Data_INDEX.WAR_SCORE )
		local realscore = WarScoreConfig.ScoreLimit - GotedScore
		if realscore > playerscore then
			realscore = playerscore
		else
			if realscore < 0 then
				realscore = 0
			end
		end
		AddIntData2Player( vRepetionID, vParame.killerid, Player_War_Data_INDEX.WAR_SCORE, realscore )	
		AddIntData2Player( vRepetionID, vParame.killerid, Player_War_Data_INDEX.TOTAL_SCORE, realscore )	
		
		-- ֪ͨ����ս����Ϣ				
		-- ɱ����
		if playernum > 0 then
				local killednum=GetIntData2Player( vRepetionID, vParame.killerid, Player_War_Data_INDEX.PALYER_KILLEDNUM ) 
				EventNoticeSingle( vRepetionID, vParame.killerid,  RepetionNoticeEventKind.MSG, MSG.KILLED_PLAYER_NUM, killednum )
		end		
				
		-- ɱ�������
		if ogrenum > 0 then
				local totalogrenum = GetIntData2Player( vRepetionID, vParame.killerid, Player_War_Data_INDEX.OGRE_KILLEDNUM )
				totalogrenum = totalogrenum + GetIntData2Player( vRepetionID, vParame.killerid, Player_War_Data_INDEX.BOSS_KILLEDNUM )
				EventNoticeSingle( vRepetionID, vParame.killerid, RepetionNoticeEventKind.MSG, MSG.KILLED_OGRE_NUM, totalogrenum )
		end				
		-- ���˻�����
	end	
	
	local totalscore= 0
	
	-- ������Ӫ1
	if campid == CampData.Camp1ID then
		
			-- �ܻ���
		  totalscore = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_SCORE )
      totalscore = totalscore + campscore
      SetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_SCORE, totalscore )
      
      --����������ֵ       
      
      -- ɱ����
     	playerkillednum = playernum + GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_PLYER_KILLEDNUM )
     	SetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_PLYER_KILLEDNUM, playerkillednum )
     	
      -- ɱ�����������
      ogrekillednum = ogrenum + GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_OGRE_KILLEDNUM ) + bossnum
	SetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_OGRE_KILLEDNUM, ogrekillednum )	
			
			-- ɱ��boss������
	bosskillednum = bossnum + GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_BOSS_KILLEDNUM )
	SetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_BOSS_KILLEDNUM, bosskillednum )
      
	-- ������Ӫ2
	else
			-- �ܻ���
		  totalscore = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_SCORE )
      totalscore = totalscore + campscore
      SetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_SCORE, totalscore )
      
      --����������ֵ       
      
      -- ɱ����
     	playerkillednum = playernum + GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_PLYER_KILLEDNUM )
     	SetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_PLYER_KILLEDNUM, playerkillednum )
     	
      -- ɱ�����������
      ogrekillednum = ogrenum + GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_OGRE_KILLEDNUM ) + bossnum
      SetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_OGRE_KILLEDNUM, ogrekillednum )	
			
			-- ɱ��boss������
	bosskillednum = bossnum + GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_BOSS_KILLEDNUM )
	SetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_BOSS_KILLEDNUM, bosskillednum )
	end
	
	-- ֪ͨ������Ӫ����������
	if campscore > 0 then
			EventNoticeByCamp( vRepetionID, campid, RepetionNoticeEventKind.MSG, MSG.CAMP_SCORE, totalscore )			
			if campid == CampData.Camp1ID then
				EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.ENEMY_CAMP_SCORE, totalscore )
			else
				EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.ENEMY_CAMP_SCORE, totalscore )
			end
	end
	-- �ж��Ƿ���Խ���ս��
	if totalscore >= WarScoreConfig.EndScore then
			endglobalwar( 0, vRepetionID, 0, 0  )
	end	
end


local function time_assignment( vRepetionID, vParame )
	
end

local function machinery_spring( vRepetionID, vParame )				
			
			-- ���ٱ���
			CharacterDie( vRepetionID,  vParame.machineryid, 0 )			
			
			-- ������Ӫ1�ķ������
			if vParame.index == GoldSodiersConfig[1].ArmySymbolIndex and vParame.campid > 0 then
					local	tIndex = 1
					while GoldSodiersConfig[1].GoldSodiersIndex[vParame.campid][tIndex] ~= nil
					do
						CreateNpc( vRepetionID, GoldSodiersConfig[1].GoldSodiersIndex[vParame.campid][tIndex] )
						tIndex = tIndex + 1
					end					
			end		
			
			-- ������Ӫ2�ķ������
			if vParame.index == GoldSodiersConfig[2].ArmySymbolIndex and vParame.campid > 0 then
					local	tIndex = 1
					while GoldSodiersConfig[2].GoldSodiersIndex[vParame.campid][tIndex] ~= nil
					do
						CreateNpc( vRepetionID, GoldSodiersConfig[2].GoldSodiersIndex[vParame.campid][tIndex] )
						tIndex = tIndex + 1
					end
			end							

			--���������������		
			if vParame.springcharid > 0 then
				playername = GetNameByCharID( vRepetionID, vParame.springcharid )
				if vParame.campid == CampData.Camp1ID then
					EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.ARMYSYMBOL_START, 0, playername ) 
					EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.ARMYSYMBOL_START, 1, playername ) 
				else
					EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.ARMYSYMBOL_START, 1, playername ) 
					EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.ARMYSYMBOL_START, 0, playername ) 
				end
			end
end

-- �����ر�
local function  close_reption( map_id, repetion_id, args, index )	
	RepetionClose( repetion_id )
end

-- ������ɫ
local function create_player( vRepetionID, vParame )
	
	local InWar = GetIntData2Player( vRepetionID,  vParame.entityid, Player_War_Data_INDEX.STATUS_INWAR )		
	if InWar == 0 or vParame.new == 1 or vParame.first == 1 then
		SetIntData2Player( vRepetionID,  vParame.entityid, Player_War_Data_INDEX.STATUS_INWAR, 1 )		
								
		-- �������	
		SetIntData2Player( vRepetionID, vParame.entityid, Player_War_Data_INDEX.PALYER_KILLEDNUM, 0 )
		SetIntData2Player( vRepetionID, vParame.entityid, Player_War_Data_INDEX.OGRE_KILLEDNUM, 0 )
		SetIntData2Player( vRepetionID, vParame.entityid, Player_War_Data_INDEX.BOSS_KILLEDNUM, 0 )
		SetIntData2Player( vRepetionID, vParame.entityid, Player_War_Data_INDEX.WAR_SCORE, 0 )
		SetIntData2Player( vRepetionID,  vParame.entityid, Player_War_Data_INDEX.ReliveTimes, 0 )
		ObserverEntityDeath( vRepetionID, vParame.entityid )		
		
		local camp1_score =	GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_SCORE )
		local camp2_score = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_SCORE )     	
	
		-- ����������ʼ�ص�
		local Camp1_Num = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_NUM )
		local Camp2_Num = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_NUM )
		
		-- ��������
		Camp1OgreNum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_OGRE_NUM )
		Camp2OgreNum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_OGRE_NUM )
		Camp1BossID = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_BuddhaID )
		Camp2BossID = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_BuddhaID )
		if Camp1BossID > 0 then
			Camp1BossID = 0
		else
			Camp1BossID = 1
		end
		if Camp2BossID > 0 then
			Camp2BossID = 0
		else
			Camp2BossID = 1
		end
				
		if vParame.campid == CampData.Camp1ID then
			Camp1_Num = Camp1_Num + 1			
			SetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_NUM, Camp1_Num )			
			-- ֪ͨ����
			EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.SELE_CAMP_ROLENUM, Camp1_Num ) 
			EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.ENEMY_CAMP_ROLENUM, Camp1_Num ) 			
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.ENEMY_CAMP_ROLENUM, Camp2_Num ) 			
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.SELE_CAMP_ROLENUM, Camp1_Num ) 	
			-- ֪ͨ����
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.CAMP_SCORE, camp1_score ) 			
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.ENEMY_CAMP_SCORE, camp2_score ) 
			-- ����buff			
			EntityInsertBuff( vRepetionID, vParame.entityid, WarBuff[CampData.Camp1ID]  )
			EntityInsertBuff( vRepetionID, vParame.entityid, WarBuff.TimeLimitBuff )
			-- ����		
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.SELF_OGRE_NUM, Camp1OgreNum ) 			
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.ENEMY_OGRE_NUM, Camp2OgreNum ) 	
			-- boss			
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.SELF_BOSS_STATUS, Camp1BossID ) 			
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.ENEMY_BOSS_STATUS, Camp2BossID ) 	
		elseif  vParame.campid == CampData.Camp2ID then
			Camp2_Num = Camp2_Num + 1			
			SetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_NUM, Camp2_Num )			
			-- ֪ͨ����
			EventNoticeByCamp( vRepetionID, CampData.Camp2ID, RepetionNoticeEventKind.MSG, MSG.SELE_CAMP_ROLENUM, Camp2_Num ) 
			EventNoticeByCamp( vRepetionID, CampData.Camp1ID, RepetionNoticeEventKind.MSG, MSG.ENEMY_CAMP_ROLENUM, Camp2_Num ) 
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.ENEMY_CAMP_ROLENUM, Camp1_Num ) 		
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.SELE_CAMP_ROLENUM, Camp2_Num ) 			
			-- ֪ͨ����
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.CAMP_SCORE, camp2_score ) 			
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.ENEMY_CAMP_SCORE, camp1_score )													
			EntityInsertBuff( vRepetionID, vParame.entityid, WarBuff[CampData.Camp2ID] )
			EntityInsertBuff( vRepetionID, vParame.entityid, WarBuff.TimeLimitBuff )
			-- ����		
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.SELF_OGRE_NUM, Camp2OgreNum ) 			
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.ENEMY_OGRE_NUM, Camp1OgreNum ) 	
			-- boss			
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.SELF_BOSS_STATUS, Camp2BossID ) 			
			EventNoticeSingle( vRepetionID, vParame.entityid, RepetionNoticeEventKind.MSG, MSG.ENEMY_BOSS_STATUS, Camp1BossID ) 	
		end			
	end
	
	if vParame.first == 1  then
	local	x,y = GetPos( vRepetionID, vParame.entityid  )		
		if vParame.campid == CampData.Camp1ID and ( x ~= CampData.Camp1PosX or y ~= CampData.Camp1PosY ) then
			Teleport( vRepetionID, vParame.entityid, CampData.Camp1PosX, CampData.Camp1PosY )																						
		elseif  vParame.campid == CampData.Camp2ID and ( x ~= CampData.Camp2PosX or y ~= CampData.Camp2PosY ) then
			Teleport( vRepetionID, vParame.entityid, CampData.Camp2PosX, CampData.Camp2PosY )																						
		end
	end
end

-- ����뿪
local function player_leave( vRepetionID, vParame )

	-- �ж������Ƿ���Խ���ս��		
	local Camp1_Num = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_NUM )
	local Camp2_Num = GetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_NUM )	
	local CampID = GetCampID( vRepetionID, vParame.entityid )
	SetIntData2Player( vRepetionID,  vParame.entityid, Player_War_Data_INDEX.STATUS_INWAR, 0 )		
	
	-- ��buff(���ս��δ����,��������buff)
	local endflag = GetIntData( vRepetionID, GlobalWar_Data_Key.REPETION_END_FLAG )
	if endflag ~= 1 then
		EntityInsertBuff( vRepetionID, vParame.entityid, WarBuff.EscapBuff  )	
	end		 
	
	if CampID == CampData.Camp1ID then
		Camp1_Num = Camp1_Num - 1
		SetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP1_NUM, Camp1_Num  )
		-- ֪ͨ����			
		EventNoticeByCamp( vRepetionID, 1, RepetionNoticeEventKind.MSG, MSG.SELE_CAMP_ROLENUM, Camp1_Num ) 
		EventNoticeByCamp( vRepetionID, 2, RepetionNoticeEventKind.MSG, MSG.ENEMY_CAMP_ROLENUM, Camp1_Num ) 
	else	
		Camp2_Num = Camp2_Num - 1		
		SetIntData( vRepetionID, GlobalWar_Data_Key.GlobalWar_Data_CAMP2_NUM, Camp2_Num )		
		-- ֪ͨ����			
		EventNoticeByCamp( vRepetionID, 2, RepetionNoticeEventKind.MSG, MSG.SELE_CAMP_ROLENUM, Camp2_Num ) 
		EventNoticeByCamp( vRepetionID, 1, RepetionNoticeEventKind.MSG, MSG.ENEMY_CAMP_ROLENUM, Camp2_Num ) 
	end
end

-- ׼������ʱ
local function WarPrepare( map_id, repetion_id, args, index )	

		-- ����˫���赲
		i = 1
		while WAR_PREPARE_BLOCK_ID[i] ~= nil do
			DestroyAliveTempOgre( repetion_id, WAR_PREPARE_BLOCK_ID[i], MAX_BLOCK_NUM  )							
			i = i+1
		end
		
		
		-- �ٻ�����
		local Index = 1
		while OgreIndex[Index] ~= nil do
				CreateNpc( repetion_id, OgreIndex[Index] )
				Index = Index + 1
		end		
		
		-- ��ʼħ���ŵ���ʱ
		TimeBegin( repetion_id, 4 )
		
		-- ���ˢ�µ���ʱ
		TimeBegin( repetion_id, 7 )
end

-- ħ���Źر�
local function MagicDoorDisappear( map_id, repetion_id, args, index )	

		-- ����ħ�����赲
		i = 1
		while WAR_MAGIC_DOOR_BLOCK_ID[i] ~= nil do
			DestroyAliveTempOgre( repetion_id, WAR_MAGIC_DOOR_BLOCK_ID[i], MAX_BLOCK_NUM  )							
			i = i+1
		end		
end

-- ��������		
local function CreateArmySymbol( map_id, repetion_id, args, index )	
	-- ��������
	CreateNpc( repetion_id, GoldSodiersConfig[1].ArmySymbolIndex )
	CreateNpc( repetion_id, GoldSodiersConfig[2].ArmySymbolIndex )
	-- ˢ��С���ﵹ��ʱ
	TimeBegin( repetion_id, 8 )
end

-- ��ʱ����
local function relive( repetion_index, repetion_id, args, loop_index )
	PlayerRelive( repetion_id, 1, args.x1, args.y1 );
	PlayerRelive( repetion_id, 2, args.x2, args.y2 );
end

local function check_award( vRepetionID, vParame )
	local singleplayernum = GetIntData2Player( vRepetionID, vParame.entityid, Player_War_Data_INDEX.PALYER_KILLEDNUM );
	local singleogrenum = GetIntData2Player( vRepetionID, vParame.entityid, Player_War_Data_INDEX.OGRE_KILLEDNUM );
	local point = 0;
	local singlepoint = singleplayernum + singleogrenum * 3;
	local teamplayernum = 0;
	local teamogrenum = 0;
	local teambossnum = 0;
	if vParame.campid == CampData.Camp1ID then
		teamplayernum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_PLYER_KILLEDNUM );
		teamogrenum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_OGRE_KILLEDNUM ); 
		teambossnum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP1_BOSS_KILLEDNUM );
	else
		teamplayernum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_PLYER_KILLEDNUM );
		teamogrenum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_OGRE_KILLEDNUM ); 
		teambossnum = GetIntData( vRepetionID, GlobalWar_Data_Key.CAMP2_BOSS_KILLEDNUM );
	end
	local teampoint = ( teamplayernum + teamogrenum * 3 ) / 10;
	if singlepoint >= teampoint then 
		point = singlepoint;
	else
		point = teampoint;
	end
	
	if point > 30 then
		point = 30;
	end

	if teambossnum > 0 then
		point = point + 70;
	end

	if vParame.campid == vParame.wincamp then
		point = point + 100;
	else
		point = point + 30;
	end
	AwardFameSingle( vRepetionID, vParame.entityid, 1, point * 10000 / 200 );
end

		
local function CreateHierogran( map_id, repetion_id, args, index )	
		tCreateIndex = GetIntData( repetion_id, GlobalWar_Data_Key.HIEROGRAN_CREATE_INDEX )					 
	 	tTimes = GetIntData( repetion_id, GlobalWar_Data_Key.HIEROGRAN_TIMESS )	
	 	hierogran = Hierogran_CreateWay[tCreateIndex][tTimes+1]	
	 	CreateHierogram( repetion_id, Hierogran_Data[hierogran].temp, Hierogran_Data[hierogran].x, Hierogran_Data[hierogran].y )			
	 	SetIntData( repetion_id, GlobalWar_Data_Key.HIEROGRAN_TIMESS, tTimes + 1 )			
end

local function BeginRepetion( vRepetionID, vParame )				
	 local tData = math.random(1,2000000)%20 + 1
	 SetIntData( vRepetionID, GlobalWar_Data_Key.HIEROGRAN_CREATE_INDEX, tData )					 
	 SetIntData( vRepetionID, GlobalWar_Data_Key.HIEROGRAN_TIMESS, 0 )				
end
		
local function CreateLittleOgre( map_id, repetion_id, args, index )	
	local tData = math.random(1,2000000)%3 + 1
	CreateNpc( repetion_id, LittleOgreData.Index[tData] )
end
-- ������������
repetion = 
{
	baseinfo = 
	{
		repetion_index = RepetionID.GLOBALWAR,
		playercountmax = 40,		-- �����������
		mapid = { 156},			-- ������ͼID
		taskid = 0,			-- ���븱����ǰ������
		posx = 32,			-- ��ʱ����
		posy = 11,			-- ��ʱ����
		pernumber = 0,			-- ÿ����븱���Ĵ����� 0-����
		minlevel = 60,			-- ��ͽ���ȼ�
		maxlevel = 120,			-- ��߽���ȼ�
		--check_time = 20000,		-- ��鸱������ʱ��(����)
		question_check=0,		-- �Ƿ���и���������֤
		unrelive = 1,			
		-- �����Ϣ
		team = 
		{
			teamin = false,		-- �Ƿ���ӽ��룻 ture-��Ҫ���; false - �������
			count = 1,		-- �����������
		},		


		backpos = 
		{
			mapid = 1,			-- ��ʱ����
			posx = 33,			-- ��ʱ����	
			posy = 13,			-- ��ʱ����
		},
	},
			
	battle =
  {
       camp =
       {
           { campid = 1, posx = 64, posy = 4 },
           { campid = 2, posx = 22, posy = 117 },
       },
       level =
       {
           { levelmin = 60,    levelmax = 110 },
       },          
   },
	
		-- ��������ʱ��
		open = 
		{
			-- ��, �£��ܣ� �գ� ʱ, �֣� ��
			-- 0 �ǲ�����ʱ�� ����ÿ�µڼ���
			--��һ��ʱ��

			{
				start = { year = 0, month = 0, week = 1, day = 0, hr = 13, minute = 00, sec = 0 },
				finish = { year = 0, month = 0, week = 1, day = 0, hr = 15, minute = 00, sec = 0 }
			},
			--�ڶ���ʱ��
			{
				start = { year = 0, month = 0, week = 1, day = 0, hr = 18, minute = 00, sec = 0 },
				finish = { year = 0, month = 0, week = 1, day = 0, hr = 21, minute = 00, sec = 0 }
			},
			-- ���֧�����ʱ��
			{
				start = { year = 0, month = 0, week = 3, day = 0, hr = 13, minute = 00, sec = 0 },
				finish = { year = 0, month = 0, week = 3, day = 0, hr = 15, minute = 00, sec = 0 }
			},
			--�ڶ���ʱ��
			{
				start = { year = 0, month = 0, week = 3, day = 0, hr = 18, minute = 00, sec = 0 },
				finish = { year = 0, month = 0, week = 3, day = 0, hr = 21, minute = 00, sec = 0 }
			},		
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
			func = endglobalwar,
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

		-- ȫ��ս��׼��ʱ��
		{
			kind = RepetionTimeBeginKind.START_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = WAR_PREPARE_TIME,
			loop = 1,
			func = WarPrepare,
			args = {  },
			sync = { kind = RepetionTimeSyncKind.ALL, key = 1 },
		},	
		
		-- ħ���ŵ���ʱ
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = WAR_MAGIC_DOOR_TIME,
			loop = 1,
			func = MagicDoorDisappear,
			args = { },
			sync = { kind = RepetionTimeSyncKind.ALL, key = 2 },
		},			
		
		-- ����ˢ������ʱ
		{
			kind = RepetionTimeBeginKind.START_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = WAR_ARMYSYMBOL_TIME,
			loop = 1,
			func = CreateArmySymbol,
			args = { },
		},
		
		-- �����ʱ			
		{
			kind = RepetionTimeBeginKind.START_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = 15000,
			loop = 0,
			func = relive,
			args = { x1 = 64, y1 = 4, x2 = 22, y2 = 117 },
			sync = { kind = RepetionTimeSyncKind.ALL, key = 3 },
		},
		
		-- ���ˢ������ʱ
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = HIEROGRAN_TIME,
			loop = 9,
			func = CreateHierogran,
			args = { },		
		},			
		
		-- ˢС���ﵹ��ʱ
		{
			kind = RepetionTimeBeginKind.EVENT_BEGIN,
			result = RepetionTimeResultKind.NONE,
			time = LITTLE_OGRE_TIME,
			loop = 0,
			func = CreateLittleOgre,
			args = { },		
		},			
	},

	event = 
	{
		[ RepetionEventKind.PLAYER_CREATE ] = { func = create_player },
		[ RepetionEventKind.OGRE_CREATE ] = { func = create_ogre },
		[ RepetionEventKind.OGRE_DEATH	] = { func = ogre_death },
		[ RepetionEventKind.TIME_ASSIGNMENT ] = { func = time_assignment },
		[ RepetionEventKind.BOX_MACHINERY_SPING ] = { func = machinery_spring },		
		[ RepetionEventKind.LEAVE_REPETION] = { func = player_leave },	
		[ RepetionEventKind.CHECK_AWARD] = { func = check_award },		
		[ RepetionEventKind.BEGIN_REPETION ] = { func = BeginRepetion },	
	},
}



 
