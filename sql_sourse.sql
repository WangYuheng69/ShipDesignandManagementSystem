/*
 Navicat Premium Data Transfer

 Source Server         : catsql
 Source Server Type    : MySQL
 Source Server Version : 80027
 Source Host           : localhost:3306
 Source Schema         : shipmanagement

 Target Server Type    : MySQL
 Target Server Version : 80027
 File Encoding         : 65001

 Date: 19/12/2024 22:41:58
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for approvefile
-- ----------------------------
DROP TABLE IF EXISTS `approvefile`;
CREATE TABLE `approvefile`  (
  `recordid` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `fileid` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `filename` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `changewhy` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `changedate` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `approverid` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NULL DEFAULT NULL,
  PRIMARY KEY (`recordid`) USING BTREE,
  INDEX `record`(`recordid` ASC, `fileid` ASC) USING BTREE COMMENT '审计记录的文件',
  INDEX `approveforeign1`(`fileid` ASC) USING BTREE,
  INDEX `approveforeign2`(`filename` ASC) USING BTREE,
  INDEX `approveforeign3`(`approverid` ASC) USING BTREE,
  CONSTRAINT `approveforeign1` FOREIGN KEY (`fileid`) REFERENCES `designfile` (`fileid`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `approveforeign2` FOREIGN KEY (`filename`) REFERENCES `designfile` (`filename`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `approveforeign3` FOREIGN KEY (`approverid`) REFERENCES `approver` (`approverid`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of approvefile
-- ----------------------------
INSERT INTO `approvefile` VALUES ('r001', 'f001', 'fn001', 'delete', '2024.1.2', '202403001');
INSERT INTO `approvefile` VALUES ('r002', 'f002', 'fn002', 'add', '2024.2.2', '202403002');
INSERT INTO `approvefile` VALUES ('r003', 'f003', 'fn003', 'alter', '2024.3.3', '202403003');
INSERT INTO `approvefile` VALUES ('r004', 'f004', 'fn004', 'add', '2024.4.4', '202403004');

-- ----------------------------
-- Table structure for approver
-- ----------------------------
DROP TABLE IF EXISTS `approver`;
CREATE TABLE `approver`  (
  `approverid` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '审计员的id',
  `password` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '审计员登录用的密码',
  `name` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '姓名',
  `gender` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '性别',
  `phone` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NULL DEFAULT NULL COMMENT '电话',
  `email` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NULL DEFAULT NULL COMMENT '邮箱',
  PRIMARY KEY (`approverid`) USING BTREE,
  INDEX `approver`(`approverid` ASC, `password` ASC) USING BTREE COMMENT '审计员的登录id和密码'
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of approver
-- ----------------------------
INSERT INTO `approver` VALUES ('202403001', '12303001', 'a001', 'female', '198001', 'a001@gmail.com');
INSERT INTO `approver` VALUES ('202403002', '12303002', 'a002', 'female', '198002', 'a002@gmail.com');
INSERT INTO `approver` VALUES ('202403003', '12303003', 'a003', 'male', '198003', 'a003@gmail.com');
INSERT INTO `approver` VALUES ('202403004', '12303004', 'a004', 'female', '198004', 'a004@gmail.com');

-- ----------------------------
-- Table structure for designer
-- ----------------------------
DROP TABLE IF EXISTS `designer`;
CREATE TABLE `designer`  (
  `designerid` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '设计师的id',
  `password` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '设计师登录界面用的密码',
  `name` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '设计师的姓名',
  `gender` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '设计师的性别',
  `phone` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NULL DEFAULT NULL COMMENT '设计师的电话',
  `email` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NULL DEFAULT NULL COMMENT '设计师的邮箱',
  PRIMARY KEY (`designerid`) USING BTREE,
  INDEX `designer`(`designerid` ASC, `password` ASC) USING BTREE COMMENT '设计师的登录id和密码'
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of designer
-- ----------------------------
INSERT INTO `designer` VALUES ('202401001', '12301001', 'd001', 'male', '186001', 'd001@gmail.com');
INSERT INTO `designer` VALUES ('202401002', '12301002', 'd002', 'female', '186002', 'd002@gmail.com');
INSERT INTO `designer` VALUES ('202401003', '12301003', 'd003', 'female', '186003', 'd003@gmail.com');
INSERT INTO `designer` VALUES ('202401004', '12301004', 'd004', '', '186004', 'd004@gmail.com');

-- ----------------------------
-- Table structure for designfile
-- ----------------------------
DROP TABLE IF EXISTS `designfile`;
CREATE TABLE `designfile`  (
  `fileid` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `filename` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `filetype` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `uploaddate` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `versionnumber` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `designerid` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `projectid` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`fileid`) USING BTREE,
  INDEX `file`(`fileid` ASC, `filename` ASC) USING BTREE COMMENT '文件的id和文件名',
  INDEX `filename`(`filename` ASC) USING BTREE,
  INDEX `fileforeign1`(`designerid` ASC) USING BTREE,
  INDEX `fileforeign2`(`projectid` ASC) USING BTREE,
  CONSTRAINT `fileforeign1` FOREIGN KEY (`designerid`) REFERENCES `designer` (`designerid`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `fileforeign2` FOREIGN KEY (`projectid`) REFERENCES `project` (`projectid`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of designfile
-- ----------------------------
INSERT INTO `designfile` VALUES ('f001', 'fn001', 'cad', '2024.1.1', '1.1', '202401001', 'p001');
INSERT INTO `designfile` VALUES ('f002', 'fn002', 'readme', '2024.2.2', '1.2', '202401002', 'p002');
INSERT INTO `designfile` VALUES ('f003', 'fn003', 'txt', '2024.3.3', '1.3', '202401003', 'p003');
INSERT INTO `designfile` VALUES ('f004', 'fn004', 'dll', '2024.4.4', '2024.4.5', '202401004', 'p004');

-- ----------------------------
-- Table structure for manager
-- ----------------------------
DROP TABLE IF EXISTS `manager`;
CREATE TABLE `manager`  (
  `managerid` varchar(45) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '项目经理的id',
  `password` varchar(45) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '项目经理的登录密码',
  `name` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '名字',
  `gender` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '性别',
  `phone` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NULL DEFAULT NULL COMMENT '电话',
  `email` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NULL DEFAULT NULL COMMENT '邮箱',
  PRIMARY KEY (`managerid`) USING BTREE,
  INDEX `manager`(`managerid` ASC, `password` ASC) USING BTREE COMMENT '管理员的登录id和密码'
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of manager
-- ----------------------------
INSERT INTO `manager` VALUES ('202402001', '12302001', 'm001', 'male', '188001', 'm001@gmail.com');
INSERT INTO `manager` VALUES ('202402002', '12302002', 'm002', 'male', '188002', 'm002@gmail.com');
INSERT INTO `manager` VALUES ('202402003', '12302003', 'm003', 'female', '188003', 'm003@gmail.com');
INSERT INTO `manager` VALUES ('202402004', '12302004', 'm004', 'female', '188004', 'm004@gmail.com');

-- ----------------------------
-- Table structure for project
-- ----------------------------
DROP TABLE IF EXISTS `project`;
CREATE TABLE `project`  (
  `projectid` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `projectname` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `startdate` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NULL DEFAULT NULL,
  `enddate` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NULL DEFAULT NULL,
  `status` varchar(25) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`projectid`) USING BTREE,
  INDEX `project`(`projectid` ASC, `projectname` ASC) USING BTREE COMMENT '项目的id和名字\r\n'
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of project
-- ----------------------------
INSERT INTO `project` VALUES ('p001', 'n001', '2024.1.1', '2024.1.2', 'done');
INSERT INTO `project` VALUES ('p002', 'n002', '2024.2.2', '2024.2.3', 'doing');
INSERT INTO `project` VALUES ('p003', 'n003', '2024.3.3', '2024.3.4', 'undo');
INSERT INTO `project` VALUES ('p004', 'n004', '2024.4.4', '2024.4.5', 'doing');

-- ----------------------------
-- View structure for file change include the all id
-- ----------------------------
DROP VIEW IF EXISTS `file change include the all id`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `file change include the all id` AS select `designfile`.`fileid` AS `fileid`,`designfile`.`filename` AS `filename`,`approvefile`.`recordid` AS `recordid`,`designfile`.`designerid` AS `designerid`,`designfile`.`projectid` AS `projectid`,`approvefile`.`approverid` AS `approverid`,`approvefile`.`changewhy` AS `changewhy` from (`designfile` join `approvefile` on(((`designfile`.`fileid` = `approvefile`.`fileid`) and (`designfile`.`filename` = `approvefile`.`filename`))));

-- ----------------------------
-- View structure for file the all information
-- ----------------------------
DROP VIEW IF EXISTS `file the all information`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `file the all information` AS select `designfile`.`fileid` AS `fileid`,`designfile`.`filename` AS `filename`,`designfile`.`filetype` AS `filetype`,`designfile`.`uploaddate` AS `uploaddate`,`designfile`.`versionnumber` AS `versionnumber`,`designfile`.`designerid` AS `designerid`,`designfile`.`projectid` AS `projectid`,`designer`.`email` AS `email`,`designer`.`phone` AS `phone`,`designer`.`gender` AS `gender`,`designer`.`name` AS `name` from (`designfile` join `designer` on((`designfile`.`designerid` = `designer`.`designerid`)));

-- ----------------------------
-- View structure for one project`s all design files
-- ----------------------------
DROP VIEW IF EXISTS `one project``s all design files`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `one project``s all design files` AS select `project`.`projectid` AS `projectid`,`project`.`projectname` AS `projectname`,`project`.`startdate` AS `startdate`,`project`.`enddate` AS `enddate`,`designfile`.`fileid` AS `fileid`,`designfile`.`filename` AS `filename`,`designfile`.`filetype` AS `filetype`,`designfile`.`uploaddate` AS `uploaddate`,`designfile`.`versionnumber` AS `versionnumber` from (`project` join `designfile` on((`project`.`projectid` = `designfile`.`projectid`)));

-- ----------------------------
-- View structure for the change`s all information
-- ----------------------------
DROP VIEW IF EXISTS `the change``s all information`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `the change``s all information` AS select `approvefile`.`recordid` AS `recordid`,`approvefile`.`fileid` AS `fileid`,`designfile`.`versionnumber` AS `versionnumber`,`designfile`.`projectid` AS `projectid`,`designfile`.`designerid` AS `designerid`,`designfile`.`uploaddate` AS `uploaddate`,`designfile`.`filename` AS `filename`,`designfile`.`filetype` AS `filetype`,`approvefile`.`approverid` AS `approverid`,`approvefile`.`changedate` AS `changedate`,`approvefile`.`changewhy` AS `changewhy` from ((`approvefile` join `approver` on((`approvefile`.`approverid` = `approver`.`approverid`))) join `designfile` on(((`approvefile`.`fileid` = `designfile`.`fileid`) and (`approvefile`.`filename` = `designfile`.`filename`))));

-- ----------------------------
-- Triggers structure for table designfile
-- ----------------------------
DROP TRIGGER IF EXISTS `fileadd`;
delimiter ;;
CREATE TRIGGER `fileadd` AFTER INSERT ON `designfile` FOR EACH ROW BEGIN
INSERT INTO approverfile(fileid,filename)VALUES(new.fileid,new.filename);
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table designfile
-- ----------------------------
DROP TRIGGER IF EXISTS `filealter`;
delimiter ;;
CREATE TRIGGER `filealter` AFTER UPDATE ON `designfile` FOR EACH ROW BEGIN
UPDATE approvefile SET approver.filename=designfile.filename WHERE approver.fileid=designer.fileid; 
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table designfile
-- ----------------------------
DROP TRIGGER IF EXISTS `filedelete`;
delimiter ;;
CREATE TRIGGER `filedelete` AFTER DELETE ON `designfile` FOR EACH ROW BEGIN
DELETE FROM approvefile WHERE approver.fileid=designfile.fileid;
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
