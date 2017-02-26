-- repetionid define
RepetionID =
{
	GUANGHANGONG	= 1,
	PUTUO			= 2,
	WUZHUANGGUAN	= 3,
	SHITUOLING		= 4,
	LINEYANGE		= 5,
	TIANWANG		= 6,

	LONGGONG		= 7,
	LONGGONG_EASY	= 8,
	LONGGONG_HARD	= 9,

	PANTAO			= 10,
	PANTAO_EASY		= 11,
	PANTAO_HARD		= 12,

	HUAGUOSHAN		= 13, 
	
	CHANGBAOTU		= 14,

	CORPS_BATTLE	= 15,

	FAMILY			= 16,

	DAYANTA			= 17,
	LIANHUADONG		= 18, -- ������
	HORNETSHOLE		= 19, -- �Ʒ䶴
	FAMILY_TASTE	= 20, -- ����Ʒ����
	CORPS_CHALLEGE	= 21,	-- ������ս��
	FAMILY_CHALLENGE= 22, --������ս��
	FLY_WAR			= 23,	-- ���ƴ�ս
	GRAND			= 24,	-- ����԰
	TOWER			= 25,	-- ͨ����
	LAST_ONE                = 26,	-- ����ɱ 
	LAST_ONE_TEAM           = 27,	-- ����ɱ��� 
	WUDIDONG		= 28,
	SHITU			= 29,	--ʦͽ
	GLOBALWAR	= 30,	--ȫ�ָ���
	CORPSBOSS               = 31,   -- ����boss
}


--��ʱ����������
RepetionTimeBeginKind =
{
	START_BEGIN = 1,				--������ʼʱ������
	COMPLATE_BEGIN = 2,				--�������ʱ������
	EVENT_BEGIN = 3					--�¼�����
};

RepetionTimeResultKind =
{
	NONE  = 0,
	CLOSE = 1
};
--�¼�����
RepetionEventKind = 
{
	PLAYER_CREATE 			= 0,		--��Ҵ���
	OGRE_CREATE 			= 1,		--NPC����
	TASK_END				= 2,		--�������
	OGRE_DEATH				= 3,		--NPC����
	BOX_MACHINERY_SPING		= 4,		--����
	TIME_ASSIGNMENT			= 5;			--��ʱ�¼�
	ENTITY_MOVE_STOP		= 6;
	CLOSE_EVENT				= 7;		--�����ر�
	BEGIN_REPETION			= 8;		-- ������ʼ
	EACH_OTHER				= 9,		-- ������ҽ���
	LEAVE_REPETION                  = 10,     --����뿪����
	CALL_FUN				= 11,
        PLAYER_RELIVE                   = 12,          --��Ҹ���
	DEBUG_COMMAND		= 13,          -- �����õ�ָ��
	CHECK_AWARD		= 14,
};
--֪ͨClient�¼�
RepetionNoticeEventKind = 
{
	NONE				= 0,			--��
	CLOSE				= 1,			--�ر�
	END					= 2,			--����
	CREATE_NPC 			= 3,			--����NPC
	KILL				= 4,			--����
	COUNT_DOWN			= 5,			--����ʱ��ʼ
	COUNT_DOWN_END 		= 6,			--����ʱ����
	TAKE_COUNT			= 7,	
	RESOURCE			= 8,	
	GET				= 9,	
	CORPS_FLAG			= 10,
	CORPS_RESOURCE			= 11,
	CORPS_OGRE			= 12,
	RELIVE				= 13,
	FLAGTEMP			= 14,
	MSG				= 15,
	CORPS_BATTLEMAP		= 17,			-- ����ս�����ͼ
};

RepetionEnd =
{
	UN_COMPLATE = 0,					--δ���
	COMPLATE    = 1,						--���
};

-- ��������
RepetionDataKey = 
{
};

RepetionParameIndex =
{
	PARAME1				= 0,
	PARAME2				= 1,
};


RepetionTimeSyncKind = 
{
	NONE				= 0,		-- ��ͬ��
	ALL					= 1,		-- ȫ��ͬ��
	CAMP				= 2,		-- ��Ӫͬ��
};

RepetionTimeSyncKey = 
{
	CLOSE				= 0,
};

RepetionInsertItemReason =
{
	NONE				= 0,
	WIN					= 1;
	LOST				= 2;
	NEW					= 3;
	PASS				= 4;
};

RepetionInitPost =
{
    [RepetionID.LAST_ONE] = 
    {
        [1] = {
            {x = 14, y = 42},
            {x = 25, y = 54}, 
            {x = 24, y = 25}, 
            {x = 43, y = 47}, 
            {x = 30, y = 37}, 
        },
    }, 

}

RepetionTeleCharge = {
        [RepetionID.LAST_ONE] = {
                coef = 1,
                mapid = 165,
                post = {
		    {x = 14, y = 42},
		    {x = 25, y = 54}, 
		    {x = 24, y = 25}, 
		    {x = 43, y = 47}, 
		    {x = 30, y = 37}, 
                },
        },
}
