/*
 Navicat Premium Data Transfer

 Source Server         : lk
 Source Server Type    : MySQL
 Source Server Version : 80027
 Source Host           : localhost:3306
 Source Schema         : biodb

 Target Server Type    : MySQL
 Target Server Version : 80027
 File Encoding         : 65001

 Date: 23/12/2021 11:58:10
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for classtable
-- ----------------------------
DROP TABLE IF EXISTS `classtable`;
CREATE TABLE `classtable`  (
  `classId` int(0) NOT NULL AUTO_INCREMENT,
  `class` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `divisionId` int(0) NULL DEFAULT NULL,
  `createTime` timestamp(0) NULL DEFAULT NULL,
  `updateTime` timestamp(0) NULL DEFAULT NULL,
  PRIMARY KEY (`classId`) USING BTREE,
  UNIQUE INDEX `classId`(`classId`) USING BTREE,
  UNIQUE INDEX `class`(`class`) USING BTREE,
  INDEX `classtable_ibfk_1`(`divisionId`) USING BTREE,
  CONSTRAINT `classtable_ibfk_1` FOREIGN KEY (`divisionId`) REFERENCES `divisiontable` (`divisionId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 11 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of classtable
-- ----------------------------
INSERT INTO `classtable` VALUES (1, '哺乳纲', 1, '2021-12-12 21:00:50', '2021-12-12 21:00:50');
INSERT INTO `classtable` VALUES (2, '无颌纲', 1, '2021-12-12 21:00:50', '2021-12-12 21:00:50');
INSERT INTO `classtable` VALUES (3, '单子叶植物纲', 2, '2021-12-18 01:46:49', '2021-12-18 01:46:49');
INSERT INTO `classtable` VALUES (4, '多毛纲', 3, '2021-12-21 17:18:57', '2021-12-21 17:18:57');

-- ----------------------------
-- Table structure for commonnametable
-- ----------------------------
DROP TABLE IF EXISTS `commonnametable`;
CREATE TABLE `commonnametable`  (
  `commonName` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `speciesId` int(0) NOT NULL,
  PRIMARY KEY (`speciesId`, `commonName`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of commonnametable
-- ----------------------------
INSERT INTO `commonnametable` VALUES ('七星鳗', 3);
INSERT INTO `commonnametable` VALUES ('八目鳗 ', 3);
INSERT INTO `commonnametable` VALUES ('人类', 11);
INSERT INTO `commonnametable` VALUES ('晚期智人', 11);

-- ----------------------------
-- Table structure for distribute
-- ----------------------------
DROP TABLE IF EXISTS `distribute`;
CREATE TABLE `distribute`  (
  `distributionId` int(0) NOT NULL,
  `speciesId` int(0) NOT NULL,
  PRIMARY KEY (`distributionId`, `speciesId`) USING BTREE,
  INDEX `speciesId`(`speciesId`) USING BTREE,
  CONSTRAINT `distribute_ibfk_1` FOREIGN KEY (`speciesId`) REFERENCES `speciestable` (`speciesId`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `distribute_ibfk_2` FOREIGN KEY (`distributionId`) REFERENCES `distributiontable` (`distributionId`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of distribute
-- ----------------------------
INSERT INTO `distribute` VALUES (1, 2);
INSERT INTO `distribute` VALUES (2, 2);
INSERT INTO `distribute` VALUES (3, 2);
INSERT INTO `distribute` VALUES (1, 3);
INSERT INTO `distribute` VALUES (2, 3);
INSERT INTO `distribute` VALUES (12, 5);
INSERT INTO `distribute` VALUES (4, 6);
INSERT INTO `distribute` VALUES (13, 7);
INSERT INTO `distribute` VALUES (13, 12);

-- ----------------------------
-- Table structure for distributiontable
-- ----------------------------
DROP TABLE IF EXISTS `distributiontable`;
CREATE TABLE `distributiontable`  (
  `distributionId` int(0) NOT NULL AUTO_INCREMENT,
  `distribution` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`distributionId`) USING BTREE,
  UNIQUE INDEX `distributionId`(`distributionId`) USING BTREE,
  UNIQUE INDEX `distribution`(`distribution`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 14 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of distributiontable
-- ----------------------------
INSERT INTO `distributiontable` VALUES (13, '南海');
INSERT INTO `distributiontable` VALUES (12, '台湾省');
INSERT INTO `distributiontable` VALUES (2, '吉林省');
INSERT INTO `distributiontable` VALUES (4, '山东省');
INSERT INTO `distributiontable` VALUES (8, '山西省');
INSERT INTO `distributiontable` VALUES (5, '广东省');
INSERT INTO `distributiontable` VALUES (6, '广西省');
INSERT INTO `distributiontable` VALUES (3, '辽宁省');
INSERT INTO `distributiontable` VALUES (7, '陕西省');
INSERT INTO `distributiontable` VALUES (1, '黑龙江省');

-- ----------------------------
-- Table structure for divisiontable
-- ----------------------------
DROP TABLE IF EXISTS `divisiontable`;
CREATE TABLE `divisiontable`  (
  `divisionId` int(0) NOT NULL AUTO_INCREMENT,
  `division` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `kingdomId` int(0) NULL DEFAULT NULL,
  `createTime` timestamp(0) NULL DEFAULT NULL,
  `updateTime` timestamp(0) NULL DEFAULT NULL,
  PRIMARY KEY (`divisionId`) USING BTREE,
  UNIQUE INDEX `divisionId`(`divisionId`) USING BTREE,
  UNIQUE INDEX `division`(`division`) USING BTREE,
  INDEX `divisiontable_ibfk_1`(`kingdomId`) USING BTREE,
  CONSTRAINT `divisiontable_ibfk_1` FOREIGN KEY (`kingdomId`) REFERENCES `kingdomtable` (`kingdomId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 10 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of divisiontable
-- ----------------------------
INSERT INTO `divisiontable` VALUES (1, '脊索动物门', 1, '2021-12-12 21:00:50', '2021-12-12 21:00:50');
INSERT INTO `divisiontable` VALUES (2, '被子植物门', 2, '2021-12-18 01:46:49', '2021-12-18 01:46:49');
INSERT INTO `divisiontable` VALUES (3, '环节动物门', 1, '2021-12-21 17:18:57', '2021-12-21 17:18:57');

-- ----------------------------
-- Table structure for familytable
-- ----------------------------
DROP TABLE IF EXISTS `familytable`;
CREATE TABLE `familytable`  (
  `familyId` int(0) NOT NULL AUTO_INCREMENT,
  `family` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `orderId` int(0) NULL DEFAULT NULL,
  `createTime` timestamp(0) NULL DEFAULT NULL,
  `updateTime` timestamp(0) NULL DEFAULT NULL,
  PRIMARY KEY (`familyId`) USING BTREE,
  UNIQUE INDEX `familyId`(`familyId`) USING BTREE,
  UNIQUE INDEX `family`(`family`) USING BTREE,
  INDEX `familytable_ibfk_1`(`orderId`) USING BTREE,
  CONSTRAINT `familytable_ibfk_1` FOREIGN KEY (`orderId`) REFERENCES `ordertable` (`orderId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 11 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of familytable
-- ----------------------------
INSERT INTO `familytable` VALUES (2, '七鳃鳗科', 2, '2021-12-12 21:00:50', '2021-12-12 21:00:50');
INSERT INTO `familytable` VALUES (3, '天南星科', 3, '2021-12-18 01:46:49', '2021-12-18 01:46:49');
INSERT INTO `familytable` VALUES (4, '海女虫科', 4, '2021-12-21 17:18:57', '2021-12-21 17:18:57');

-- ----------------------------
-- Table structure for genustable
-- ----------------------------
DROP TABLE IF EXISTS `genustable`;
CREATE TABLE `genustable`  (
  `genusId` int(0) NOT NULL AUTO_INCREMENT,
  `genus` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `familyId` int(0) NULL DEFAULT NULL,
  `createTime` timestamp(0) NULL DEFAULT NULL,
  `updateTime` timestamp(0) NULL DEFAULT NULL,
  UNIQUE INDEX `genusId`(`genusId`) USING BTREE,
  UNIQUE INDEX `genus`(`genus`) USING BTREE,
  INDEX `genustable_ibfk_1`(`familyId`) USING BTREE,
  CONSTRAINT `genustable_ibfk_1` FOREIGN KEY (`familyId`) REFERENCES `familytable` (`familyId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 13 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of genustable
-- ----------------------------
INSERT INTO `genustable` VALUES (2, '七鳃鳗属', 2, '2021-12-12 21:00:50', '2021-12-12 21:00:50');
INSERT INTO `genustable` VALUES (3, '魔芋属', 3, '2021-12-18 01:46:49', '2021-12-18 01:46:49');
INSERT INTO `genustable` VALUES (4, '英虫属', 4, '2021-12-21 17:18:57', '2021-12-21 17:18:57');

-- ----------------------------
-- Table structure for kingdomtable
-- ----------------------------
DROP TABLE IF EXISTS `kingdomtable`;
CREATE TABLE `kingdomtable`  (
  `kingdomId` int(0) NOT NULL AUTO_INCREMENT,
  `kingdom` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `createTime` timestamp(0) NULL DEFAULT NULL,
  `updateTime` timestamp(0) NULL DEFAULT NULL,
  PRIMARY KEY (`kingdomId`) USING BTREE,
  UNIQUE INDEX `kingdomId`(`kingdomId`) USING BTREE,
  UNIQUE INDEX `kingdom`(`kingdom`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 9 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of kingdomtable
-- ----------------------------
INSERT INTO `kingdomtable` VALUES (1, '动物界', '2021-12-12 21:00:50', '2021-12-12 21:00:50');
INSERT INTO `kingdomtable` VALUES (2, '植物界', '2021-12-18 00:00:13', '2021-12-18 00:00:13');

-- ----------------------------
-- Table structure for ordertable
-- ----------------------------
DROP TABLE IF EXISTS `ordertable`;
CREATE TABLE `ordertable`  (
  `orderId` int(0) NOT NULL AUTO_INCREMENT,
  `ordername` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `classId` int(0) NULL DEFAULT NULL,
  `createTime` timestamp(0) NULL DEFAULT NULL,
  `updateTime` timestamp(0) NULL DEFAULT NULL,
  PRIMARY KEY (`orderId`) USING BTREE,
  UNIQUE INDEX `orderId`(`orderId`) USING BTREE,
  UNIQUE INDEX `ordername`(`ordername`) USING BTREE,
  INDEX `ordertable_ibfk_1`(`classId`) USING BTREE,
  CONSTRAINT `ordertable_ibfk_1` FOREIGN KEY (`classId`) REFERENCES `classtable` (`classId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 11 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of ordertable
-- ----------------------------
INSERT INTO `ordertable` VALUES (1, '灵长目', 1, '2021-12-12 21:00:50', '2021-12-12 21:00:50');
INSERT INTO `ordertable` VALUES (2, '七鳃鳗目', 2, '2021-12-12 21:00:50', '2021-12-12 21:00:50');
INSERT INTO `ordertable` VALUES (3, '天南星目', 3, '2021-12-18 01:46:49', '2021-12-18 02:28:09');
INSERT INTO `ordertable` VALUES (4, '沙蚕目', 4, '2021-12-21 17:18:57', '2021-12-21 17:18:57');

-- ----------------------------
-- Table structure for speciestable
-- ----------------------------
DROP TABLE IF EXISTS `speciestable`;
CREATE TABLE `speciestable`  (
  `speciesId` int(0) NOT NULL AUTO_INCREMENT,
  `species` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `genusId` int(0) NULL DEFAULT NULL,
  `createTime` timestamp(0) NULL DEFAULT NULL,
  `updateTime` timestamp(0) NULL DEFAULT NULL,
  PRIMARY KEY (`speciesId`) USING BTREE,
  UNIQUE INDEX `speciesId`(`speciesId`) USING BTREE,
  UNIQUE INDEX `species`(`species`) USING BTREE,
  INDEX `speciestable_ibfk_1`(`genusId`) USING BTREE,
  CONSTRAINT `speciestable_ibfk_1` FOREIGN KEY (`genusId`) REFERENCES `genustable` (`genusId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 20 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of speciestable
-- ----------------------------
INSERT INTO `speciestable` VALUES (2, '东北七鳃鳗', 2, '2021-12-12 21:00:50', '2021-12-12 21:00:50');
INSERT INTO `speciestable` VALUES (3, '日本七鳃鳗', 2, '2021-12-12 21:00:50', '2021-12-12 21:00:50');
INSERT INTO `speciestable` VALUES (4, '花魔芋', 3, '2021-12-18 01:46:49', '2021-12-18 01:46:49');
INSERT INTO `speciestable` VALUES (5, '台湾魔芋', 3, '2021-12-18 02:34:25', '2021-12-18 02:34:25');
INSERT INTO `speciestable` VALUES (6, '南非英虫', 4, '2021-12-21 17:18:57', '2021-12-21 17:18:57');
INSERT INTO `speciestable` VALUES (7, '太平洋英虫', 4, '2021-12-21 19:28:51', '2021-12-21 19:28:51');
INSERT INTO `speciestable` VALUES (12, '唇英虫', 4, '2021-12-21 23:32:39', '2021-12-21 23:32:39');

-- ----------------------------
-- View structure for qry
-- ----------------------------
DROP VIEW IF EXISTS `qry`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `qry` AS select `kingdomtable`.`kingdom` AS `kingdom`,`divisiontable`.`division` AS `division`,`classtable`.`class` AS `class`,`ordertable`.`ordername` AS `ordername`,`familytable`.`family` AS `family`,`genustable`.`genus` AS `genus`,`speciestable`.`species` AS `species` from ((((((`kingdomtable` join `divisiontable`) join `classtable`) join `ordertable`) join `familytable`) join `genustable`) join `speciestable`) where ((`kingdomtable`.`kingdomId` = `divisiontable`.`kingdomId`) and (`divisiontable`.`divisionId` = `classtable`.`divisionId`) and (`classtable`.`classId` = `ordertable`.`classId`) and (`ordertable`.`orderId` = `familytable`.`orderId`) and (`familytable`.`familyId` = `genustable`.`familyId`) and (`speciestable`.`genusId` = `genustable`.`genusId`))  WITH CASCADED CHECK OPTION;

-- ----------------------------
-- View structure for vcname
-- ----------------------------
DROP VIEW IF EXISTS `vcname`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `vcname` AS select `speciestable`.`species` AS `species`,`commonnametable`.`commonName` AS `commonname` from (`speciestable` join `commonnametable`) where (`speciestable`.`speciesId` = `commonnametable`.`speciesId`)  WITH CASCADED CHECK OPTION;

-- ----------------------------
-- View structure for vdistri
-- ----------------------------
DROP VIEW IF EXISTS `vdistri`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `vdistri` AS select `speciestable`.`species` AS `species`,`distributiontable`.`distribution` AS `distribution` from ((`speciestable` join `distributiontable`) join `distribute`) where ((`distribute`.`distributionId` = `distributiontable`.`distributionId`) and (`distribute`.`speciesId` = `speciestable`.`speciesId`))  WITH CASCADED CHECK OPTION;

-- ----------------------------
-- Procedure structure for deld
-- ----------------------------
DROP PROCEDURE IF EXISTS `deld`;
delimiter ;;
CREATE PROCEDURE `deld`(nm VARCHAR(50),pos VARCHAR(50))
begin
		DECLARE posid INT;
		DECLARE nmid INT;
		#INSERT INTO distributiontable(distribution) VALUES(pos);
		IF((SELECT COUNT(*) FROM speciestable WHERE species=nm GROUP BY speciesId)=1
		AND	(SELECT COUNT(*) FROM distributiontable WHERE distribution=pos GROUP BY distributionId)=1)
		THEN 
			SET nmid=(SELECT speciesId FROM speciestable WHERE species=nm);
			SET posid=(SELECT distributionId FROM distributiontable WHERE distribution=pos);
			DELETE FROM distribute WHERE speciesId=nmid AND distributionId=posid;
		END IF;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for ins
-- ----------------------------
DROP PROCEDURE IF EXISTS `ins`;
delimiter ;;
CREATE PROCEDURE `ins`(kingdomv VARCHAR(50),divisionv VARCHAR(50),classv VARCHAR(50),ordernamev VARCHAR(50),familyv VARCHAR(50),genusv VARCHAR(50),speciesv VARCHAR(50))
begin
	DECLARE res INT;
	IF(EXISTS (SELECT kingdomId FROM kingdomtable WHERE kingdom=kingdomv)) THEN
		SET res=(SELECT kingdomId FROM kingdomtable WHERE kingdom=kingdomv);
	ELSE
		INSERT INTO kingdomtable(kingdom) VALUES(kingdomv);
		SET res=(SELECT kingdomId FROM kingdomtable WHERE kingdom=kingdomv);
	END IF;
	
	
	IF(EXISTS (SELECT divisionId FROM divisiontable WHERE division=divisionv)) THEN
		SET res=(SELECT divisionId FROM divisiontable WHERE division=divisionv);
	ELSE
		INSERT INTO divisiontable(division,kingdomId) VALUES(divisionv,res);
		SET res=(SELECT divisionId FROM divisiontable WHERE division=divisionv);
	END IF;
	
	
	IF(EXISTS (SELECT classId FROM classtable WHERE class=classv)) THEN
		SET res=(SELECT classId FROM classtable WHERE class=classv);
	ELSE
		INSERT INTO classtable(class,divisionId) VALUES(classv,res);
		SET res=(SELECT classId FROM classtable WHERE class=classv);
	END IF;
	
	
	IF(EXISTS (SELECT orderId FROM ordertable WHERE ordername=ordernamev)) THEN
		SET res=(SELECT orderId FROM ordertable WHERE ordername=ordernamev);
	ELSE
		INSERT INTO ordertable(ordername,classId) VALUES(ordernamev,res);
		SET res=(SELECT orderId FROM ordertable WHERE ordername=ordernamev);
	END IF;
	
	
	IF(EXISTS (SELECT familyId FROM familytable WHERE family=familyv)) THEN
		SET res=(SELECT familyId FROM familytable WHERE family=familyv);
	ELSE
		INSERT INTO familytable(family,orderId) VALUES(familyv,res);
		SET res=(SELECT familyId FROM familytable WHERE family=familyv);
	END IF;
	
	
	IF(EXISTS (SELECT genusId FROM genustable WHERE genus=genusv)) THEN
		SET res=(SELECT genusId FROM genustable WHERE genus=genusv);
	ELSE
		INSERT INTO genustable(genus,familyId) VALUES(genusv,res);
		SET res=(SELECT genusId FROM genustable WHERE genus=genusv);
	END IF;
	
	INSERT INTO speciestable(species,genusId) VALUES(speciesv,res);
end
;;
delimiter ;

-- ----------------------------
-- Procedure structure for insd
-- ----------------------------
DROP PROCEDURE IF EXISTS `insd`;
delimiter ;;
CREATE PROCEDURE `insd`(nm VARCHAR(50),pos VARCHAR(50))
begin
		DECLARE posid INT;
		DECLARE nmid INT;
		#INSERT INTO distributiontable(distribution) VALUES(pos);
		SET nmid=(SELECT speciesId FROM speciestable WHERE species=nm);
		SET posid=(SELECT distributionId FROM distributiontable WHERE distribution=pos);
		INSERT INTO distribute(distributionId,speciesId) VALUES(posid,nmid);
end
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
