-- ----------------------------
-- Table structure for `UMS_ACTIVITY_YQS_CAMPINFO`
-- ----------------------------
DROP TABLE IF EXISTS `UMS_ACTIVITY_YQS_CAMPINFO`;
CREATE TABLE `UMS_ACTIVITY_YQS_CAMPINFO` (
  `ID` int(11) NOT NULL COMMENT '�����',
  `CampID` int(11) NOT NULL COMMENT '��ӪID',
  `CampRank` int(11) DEFAULT NULL,
  `CurrHandinDawNum` int(11) DEFAULT '0' COMMENT '��ǰ�Ͻ���¶����',
  `CurrGrowing` int(11) DEFAULT '0' COMMENT '��ǰ�ɳ���',
  `CurrLevel` int(11) DEFAULT '0' COMMENT '��ǰ�ȼ�',
  `SettlePhase` int(11) DEFAULT '-1' COMMENT '�����Ľ���׶�',
  PRIMARY KEY (`ID`,`CampID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `UMS_ACTIVITY_YQS_INDEX`
-- ----------------------------
DROP TABLE IF EXISTS `UMS_ACTIVITY_YQS_INDEX`;
CREATE TABLE `UMS_ACTIVITY_YQS_INDEX` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `ActivityID` int(11) NOT NULL,
  `StartTime` datetime NOT NULL,
  `EndTime` datetime DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `UMS_ACTIVITY_YQS_STOREBOXINFO`
-- ----------------------------
DROP TABLE IF EXISTS `UMS_ACTIVITY_YQS_STOREBOXINFO`;
CREATE TABLE `UMS_ACTIVITY_YQS_STOREBOXINFO` (
  `PlayerId` int(11) NOT NULL COMMENT '�û�ID',
  `ActivityIndex` int(11) NOT NULL,
  `SettlePhase` int(11) NOT NULL,
  `StoreBoxId` int(11) NOT NULL,
  PRIMARY KEY (`PlayerId`,`ActivityIndex`,`SettlePhase`,`StoreBoxId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `UMS_ACTIVITY_YQS_USERINFO`
-- ----------------------------
DROP TABLE IF EXISTS `UMS_ACTIVITY_YQS_USERINFO`;
CREATE TABLE `UMS_ACTIVITY_YQS_USERINFO` (
  `PlayerId` int(11) NOT NULL COMMENT '���ID',
  `AcitivityIndex` int(11) NOT NULL COMMENT 'ҡǮ���������ָ��ĳ��ҡǮ�����UMS_ACITIVITY_YQS�е�ID�ֶζ�Ӧ��',
  `Contribute` int(11) DEFAULT NULL COMMENT '��ҶԱ���ҡǮ����Ĺ���ֵ',
  `HandInNum` int(11) DEFAULT NULL COMMENT '�û��Ͻ���¶��',
  PRIMARY KEY (`PlayerId`,`AcitivityIndex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- View structure for `v_activity_yqs`
-- ----------------------------
DROP VIEW IF EXISTS `v_activity_yqs`;
CREATE VIEW `v_activity_yqs` AS select `UMS_ACTIVITY_YQS_INDEX`.`ID` AS `ID`,`UMS_ACTIVITY_YQS_INDEX`.`ActivityID` AS `ActivityID`,`UMS_ACTIVITY_YQS_INDEX`.`StartTime` AS `StartTime`,`UMS_ACTIVITY_YQS_INDEX`.`EndTime` AS `EndTime`,`UMS_ACTIVITY_YQS_CAMPINFO`.`CampID` AS `CampID`,`UMS_ACTIVITY_YQS_CAMPINFO`.`CampRank` AS `CampRank`,`UMS_ACTIVITY_YQS_CAMPINFO`.`CurrHandinDawNum` AS `CurrHandinDawNum`,`UMS_ACTIVITY_YQS_CAMPINFO`.`CurrGrowing` AS `CurrGrowing`,`UMS_ACTIVITY_YQS_CAMPINFO`.`CurrLevel` AS `CurrLevel`,`UMS_ACTIVITY_YQS_CAMPINFO`.`SettlePhase` AS `SettlePhase` from (`UMS_ACTIVITY_YQS_INDEX` join `UMS_ACTIVITY_YQS_CAMPINFO`) where (`UMS_ACTIVITY_YQS_INDEX`.`ID` = `UMS_ACTIVITY_YQS_CAMPINFO`.`ID`);

-- ----------------------------
-- View structure for `v_activity_yqs_playerrankinfo`
-- ----------------------------
DROP VIEW IF EXISTS `v_activity_yqs_playerrankinfo`;
CREATE VIEW `v_activity_yqs_playerrankinfo` AS select `UMS_ACTIVITY_YQS_INDEX`.`ID` AS `ID`,`UMS_ACTIVITY_YQS_USERINFO`.`PlayerId` AS `role_id`,`UMS_ROLE`.`role_name` AS `role_name`,`UMS_ROLE`.`metier_id` AS `metier_id`,`UMS_ROLE`.`role_level` AS `role_level`,`UMS_ACTIVITY_YQS_USERINFO`.`Contribute` AS `Contribute` from ((`UMS_ACTIVITY_YQS_INDEX` join `UMS_ACTIVITY_YQS_USERINFO`) join `UMS_ROLE`) where ((`UMS_ACTIVITY_YQS_INDEX`.`ID` = `UMS_ACTIVITY_YQS_USERINFO`.`AcitivityIndex`) and (`UMS_ACTIVITY_YQS_USERINFO`.`PlayerId` = `UMS_ROLE`.`role_id`));

-- ----------------------------
-- Procedure structure for `ProcYaoQianShuEndActivity`
-- ----------------------------
DROP PROCEDURE IF EXISTS `ProcYaoQianShuEndActivity`;
DELIMITER ;;
CREATE PROCEDURE `ProcYaoQianShuEndActivity`(nId int, tEndTime datetime)
BEGIN
	update UMS_ACTIVITY_YQS_INDEX set EndTime=tEndTime where id=nId;
END;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `ProcYaoQianShuLoadActivity`
-- ----------------------------
DROP PROCEDURE IF EXISTS `ProcYaoQianShuLoadActivity`;
DELIMITER ;;
CREATE PROCEDURE `ProcYaoQianShuLoadActivity`(nActivityId int, nCampId int)
BEGIN
	 select * from UMS_ACTIVITY_YQS where ActivityId=nActivityId and CampID=nCampId and EndTime="00:00";
END;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `ProcYaoQianShuLoadPlayerRankInfo`
-- ----------------------------
DROP PROCEDURE IF EXISTS `ProcYaoQianShuLoadPlayerRankInfo`;
DELIMITER ;;
CREATE PROCEDURE `ProcYaoQianShuLoadPlayerRankInfo`()
BEGIN
	DECLARE nID int;
	select ID into nID from UMS_ACTIVITY_YQS_INDEX order by ID desc limit 1;

	select * from v_activity_yqs_playerrankinfo where ID=nID order by Contribute desc limit 50;
END;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `ProcYaoQianShuStartActivity`
-- ----------------------------
DROP PROCEDURE IF EXISTS `ProcYaoQianShuStartActivity`;
DELIMITER ;;
CREATE PROCEDURE `ProcYaoQianShuStartActivity`(nActivityID int, tStartTime datetime)
BEGIN
	DECLARE nID int;
	if not exists( select * from UMS_ACTIVITY_YQS_INDEX  where StartTime=tStartTime  ) then
		insert into UMS_ACTIVITY_YQS_INDEX( ActivityID, StartTime, EndTime ) values( nActivityID, tStartTime, "" );
	end if;

	select ID into nID from UMS_ACTIVITY_YQS_INDEX where StartTime=tStartTime;

	if not exists( select * from UMS_ACTIVITY_YQS_CAMPINFO where ID=nID ) then
		insert into UMS_ACTIVITY_YQS_CAMPINFO( ID, CampID, CampRank, CurrHandinDawNum, CurrGrowing, CurrLevel, SettlePhase  ) values( nID, 1, 1, 0, 0, 1, -1  );
		insert into UMS_ACTIVITY_YQS_CAMPINFO( ID, CampID, CampRank, CurrHandinDawNum, CurrGrowing, CurrLevel, SettlePhase  ) values( nID, 2, 2, 0, 0, 1, -1  );
		insert into UMS_ACTIVITY_YQS_CAMPINFO( ID, CampID, CampRank, CurrHandinDawNum, CurrGrowing, CurrLevel , SettlePhase ) values( nID, 3, 3, 0, 0, 1, -1  );
		insert into UMS_ACTIVITY_YQS_CAMPINFO( ID, CampID, CampRank, CurrHandinDawNum, CurrGrowing, CurrLevel , SettlePhase ) values( nID, 4, 4, 0, 0, 1, -1  );
	end if;

	select * from v_activity_yqs where ID=nID;
END;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `ProcYaoQianShuUpdateUserInfo`
-- ----------------------------
DROP PROCEDURE IF EXISTS `ProcYaoQianShuUpdateUserInfo`;
DELIMITER ;;
CREATE PROCEDURE `ProcYaoQianShuUpdateUserInfo`(nPlayerId int, nActivityId int, nContribute int, nHandInNum int)
BEGIN
	if not exists( select * from UMS_ACTIVITY_YQS_USERINFO where PlayerId=nPlayerId and  AcitivityIndex=nActivityId  ) then
		insert into UMS_ACTIVITY_YQS_USERINFO( PlayerId, AcitivityIndex, Contribute, HandInNum ) values( nPlayerId, nActivityId, nContribute, nHandInNum );
	else
		update UMS_ACTIVITY_YQS_USERINFO set Contribute=nContribute, HandInNum=nHandInNum where PlayerId=nPlayerId and AcitivityIndex=nActivityId;
	end if;
END;;
DELIMITER ;

