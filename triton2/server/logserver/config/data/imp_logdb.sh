#!/bin/bash
#
#  - ��UMS_ROLE_DETAIL_XX֮������б�    PART_YYYYMMDDHH24MISS.SQL 
#  - ����仯�� UMS_ROLE_DETAIL_XX ����	 PART_UMS_ROLE_DETAIL.SQL
#

USERNAME=root
PASSWD=game
DBNAME=LogDB


if [ $# != 2 ]; then
	echo "Usage: $0 path table_header"
	exit;
fi;

HOST_NAME=$1
TABLE_HEAD=$2

MYSQL_HOME=/usr/local/mysql/
MYSQL_BIN=$MYSQL_HOME/bin/mysql
MYSQL_DUMP=$MYSQL_HOME/bin/mysqldump
MYSQL_EXEC="$MYSQL_BIN -u$USERNAME -p$PASSWD -s -vv -D$DBNAME -e"
TABLE_SQL="show tables like '$TABLE_HEAD%' "



NUM=`$MYSQL_EXEC "$TABLE_SQL" | wc -l`
HEADNUM=`expr ${NUM} - 3`
TAILNUM=`expr ${NUM} - 7`
ARR1=`$MYSQL_EXEC "$TABLE_SQL" | head -n"$HEADNUM" | tail -n "$TAILNUM"`
ARR2=($ARR1)

DUMPOPT="-u$USERNAME -p"$PASSWD" --hex-blob --skip-opt -t"

i=0
while [ "$i" -lt "${#ARR2[@]}" ]
do
	TABLENAME=${ARR2[$i]}

	if [ -f $HOST_NAME/$TABLENAME.SQL ]
	then
		$MYSQL_EXEC "source $HOST_NAME/$TABLENAME.SQL"
	fi

	let "i++"
done 

