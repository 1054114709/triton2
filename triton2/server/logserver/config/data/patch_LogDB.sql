-- 2010-03-24
-- ������Ʒ�������ͣ���Ǯ������ͺ;���������

INSERT INTO SYS_CODE_VALUE (type_id, value_id, value_name, value_code, code_group, value_desc)
VALUES (14,  49,  '���۽�������',  'EM_GET_BY_SELL_JINXIANGYU',  1 , 0);

INSERT INTO SYS_CODE_VALUE (type_id, value_id, value_name, value_code, code_group, value_desc)
VALUES (14,  14,  '�������ý�Ǯ',  'EM_GET_BY_GIFT',  1 , 0);

INSERT INTO SYS_CODE_VALUE (type_id, value_id, value_name, value_code, code_group, value_desc)
VALUES (9,  26,  '��ȡռ���ͼ����', 'EM_GET_BY_AWARD',  4 , 0);

INSERT INTO SYS_CODE_VALUE (type_id, value_id, value_name, value_code, code_group, value_desc)
VALUES (9,  71,  'ϵͳ�ջ���ʱ��Ʒ', 'EM_LOST_BY_TIMEOUT',  5 , 0);

INSERT INTO SYS_CODE_VALUE (type_id, value_id, value_name, value_code, code_group, value_desc)
VALUES (11,  13, '�����ʻ���þ���', 'EM_EXP_BY_FLOWER',  3 , 0);

-- 2010-04-14
UPDATE SYS_CODE_VALUE SET code_group ='0' WHERE (type_id='14') AND (value_id='67');
