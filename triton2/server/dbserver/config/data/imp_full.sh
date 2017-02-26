#!/bin/bash
#
# 1. ���뱸�ݵ����������
#    - ��UMS_ROLE_DETAIL_XX֮������б�      PART_YYYYMMDDHH24MISS.SQL 
#    - ����仯�� UMS_ROLE_DETAIL_XX ����	 PART_UMS_ROLE_DETAIL.SQL
#
# 2. ���뱸�ݵ�δ���ݵ��ɫ����
#    - ����δ�仯��UMS_ROLE_DETAIL_XX����  	 FULL_UMS_ROLE_DETAIL_XX.SQL
#
#
# usage: dbrecovery.sh -p PART_YYYYMMDDHH24MISS.SQL  -c FULL_YYYYMMDD_XX.SQL
#
# FULL_YYYYMMDD_XX.SQL should be UMS_ROLE_DETAIL_00.SQL ~ UMS_ROLE_DETAIL_16.SQL


USERNAME=root
PASSWD=game
DBNAME=GameDB

MYSQL_HOME=/usr/local/mysql/
MYSQL_BIN=$MYSQL_HOME/bin/mysql
MYSQL_DUMP=$MYSQL_HOME/bin/mysqldump
MYSQL_EXEC=$MYSQL_BIN -u$USERNAME -p$PASSWD -s -vv -D$DBNAME -e

PAER_ROLE_DETAIL=
PART_REMAIN=
FULL_ROLE_DETAIL=

# �����UMS_ROLE_DETAIL֮������б�
MYSQL_EXEC "$PART_REMAIN" > $PART_REMAIN.LOG

# ���뷢���仯��UMS_ROLE_DETAIL��
MYSQL_EXEC "$PART_ROLE_DETAIL" > $PART_ROLE_DETAIL.LOG

# �������н�ɫ��, �ظ��Ĳ��벻�ɹ�
MYSQL_EXEC "$FULL_ROLE_DETAIL" > $FULL_ROLE_DETAIL.LOG

# ɾ����ȫ����ʱ��㵽�ָ���ʱ���֮�䣬�Ѿ���ɾ���Ľ�ɫ; ����DETAIL�д�����������
# TODO

# ��$FULL_ROLE_DETAIL.LOG��, �������
# TODO:
