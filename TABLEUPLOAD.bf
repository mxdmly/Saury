/*
Navicat SQL Server Data Transfer

Source Server         : 198.8.8.7
Source Server Version : 100000
Source Host           : 198.8.8.7:1433
Source Database       : db_upload
Source Schema         : dbo

Target Server Type    : SQL Server
Target Server Version : 100000
File Encoding         : 65001

Date: 2018-01-11 07:41:20
*/


-- ----------------------------
-- Table structure for TABLEUPLOAD
-- ----------------------------
DROP TABLE [dbo].[TABLEUPLOAD]
GO
CREATE TABLE [dbo].[TABLEUPLOAD] (
[ID] bigint NOT NULL IDENTITY(1,1) ,
[ISUPLOAD] smallint NOT NULL DEFAULT ((1)) ,
[FID_TPATIENTVISIT] bigint NOT NULL ,
[FID_ZhaoQingInVisitSiRegId] int NOT NULL ,
[InSurVisitId] nvarchar(50) NOT NULL ,
[CBDTCQH] varchar(6) NOT NULL ,
[FIDCARD_TYPE] varchar(20) NOT NULL ,
[FIDCARD] varchar(30) NOT NULL ,
[FPRN] varchar(20) NOT NULL ,
[FTIMES] int NOT NULL ,
[FICDVERSION] tinyint NOT NULL ,
[FZYID] varchar(20) NOT NULL ,
[FAGE] smallint NOT NULL ,
[FNAME] varchar(30) NOT NULL ,
[FSEXBH] varchar(20) NOT NULL ,
[FBIRTHDAY] date NOT NULL ,
[FBIRTHPLACE] varchar(100) NULL ,
[FCOUNTRYBH] varchar(20) NOT NULL ,
[FCOUNTRY] varchar(100) NOT NULL ,
[FNATIONALITYBH] varchar(20) NOT NULL ,
[FNATIONALITY] varchar(50) NOT NULL ,
[FJOB] varchar(100) NOT NULL ,
[FSTATUSBH] varchar(20) NOT NULL ,
[FSTATUS] varchar(20) NOT NULL ,
[FDWNAME] varchar(60) NULL ,
[FDWADDR] varchar(100) NULL ,
[FDWTELE] varchar(40) NULL ,
[FDWPOST] varchar(20) NULL ,
[FHKADDR] varchar(100) NULL ,
[FHKPOST] varchar(20) NULL ,
[FLXNAME] varchar(30) NULL ,
[FRELATE] varchar(100) NULL ,
[FLXADDR] varchar(100) NULL ,
[FLXTELE] varchar(40) NULL ,
[FJKKH] varchar(100) NULL ,
[FRYDATE] date NOT NULL ,
[FRYTYKH] varchar(30) NOT NULL ,
[FRYDEPT] varchar(30) NOT NULL ,
[FRYBS] varchar(30) NOT NULL ,
[FCYDATE] date NOT NULL ,
[FCYTYKH] varchar(30) NOT NULL ,
[FCYDEPT] varchar(30) NOT NULL ,
[FCYBS] varchar(30) NOT NULL ,
[FDAYS] int NOT NULL ,
[FMZZDBH] varchar(30) NOT NULL ,
[FMZZD] varchar(200) NOT NULL ,
[FMZDOCTBH] varchar(20) NOT NULL ,
[FMZDOCT] varchar(30) NOT NULL ,
[FPHZD] varchar(1000) NULL ,
[FGMYW] varchar(200) NULL ,
[FQJTIMES] int NOT NULL ,
[FQJSUCTIMES] int NOT NULL ,
[FKZRBH] varchar(20) NOT NULL ,
[FKZR] varchar(30) NOT NULL ,
[FZRDOCTBH] varchar(30) NOT NULL ,
[FZRDOCTOR] varchar(30) NOT NULL ,
[FZZDOCTBH] varchar(30) NOT NULL ,
[FZZDOCT] varchar(30) NOT NULL ,
[FZYDOCTBH] varchar(30) NOT NULL ,
[FZYDOCT] varchar(30) NOT NULL ,
[FJXDOCTBH] varchar(30) NULL ,
[FJXDOCT] varchar(30) NULL ,
[FSXDOCTBH] varchar(30) NULL ,
[FSXDOCT] varchar(30) NULL ,
[FBMYBH] varchar(30) NULL ,
[FBMY] varchar(30) NULL ,
[FQUALITYBH] varchar(20) NOT NULL ,
[FQUALITY] varchar(20) NOT NULL ,
[FZKDOCTBH] varchar(20) NOT NULL ,
[FZKDOCT] varchar(30) NOT NULL ,
[FZKNURSEBH] varchar(20) NOT NULL ,
[FZKNURSE] varchar(30) NOT NULL ,
[FZKRQ] date NOT NULL ,
[FSUM1] numeric(18,2) NOT NULL ,
[FXYF] numeric(18,2) NOT NULL ,
[FZYF] numeric(18,2) NOT NULL ,
[FZCHYF] numeric(18,2) NOT NULL ,
[FZCYF] numeric(18,2) NOT NULL ,
[FQTF] numeric(18,2) NOT NULL ,
[FBODYBH] varchar(20) NULL ,
[FBODY] varchar(20) NOT NULL DEFAULT ('否') ,
[FBLOODBH] varchar(20) NULL ,
[FBLOOD] varchar(20) NULL ,
[FRHBH] varchar(20) NULL ,
[FRH] varchar(20) NULL ,
[FZKTYKH] varchar(30) NULL ,
[FZKDEPT] varchar(30) NULL ,
[FZKDATE] varchar(20) NULL ,
[FZKTIME] varchar(20) NULL ,
[FJBFXBH] varchar(20) NULL ,
[FJBFX] varchar(20) NULL ,
[FNATIVE] varchar(100) NULL ,
[FCURRADDR] varchar(100) NULL ,
[FCURRTELE] varchar(100) NULL ,
[FCURRPOST] varchar(100) NULL ,
[FJOBBH] int NULL ,
[FCSTZ] numeric(16,2) NULL ,
[FRYTZ] numeric(16,2) NULL ,
[FRYTJBH] varchar(20) NULL ,
[FRYTJ] varchar(20) NULL ,
[FYCLJBH] varchar(20) NULL ,
[FYCLJ] varchar(20) NULL ,
[FPHZDBH] varchar(30) NOT NULL DEFAULT ((0)) ,
[FPHZDNUM] varchar(50) NULL ,
[FIFGMYWBH] varchar(20) NULL ,
[FIFGMYW] varchar(20) NULL ,
[FNURSEBH] varchar(30) NULL ,
[FNURSE] varchar(30) NULL ,
[FLYFSBH] varchar(20) NULL ,
[FLYFS] varchar(200) NULL ,
[FYZOUTHOSTITAL] varchar(200) NULL ,
[FSQOUTHOSTITAL] varchar(200) NULL ,
[FISAGAINRYBH] varchar(20) NULL ,
[FISAGAINRY] varchar(400) NULL ,
[FISAGAINRYMD] varchar(400) NULL ,
[FRYQHMDAYS] int NULL ,
[FRYQHMHOURS] int NULL ,
[FRYQHMMINS] int NULL ,
[FRYQHMCOUNTS] int NULL ,
[FRYHMDAYS] int NULL ,
[FRYHMHOURS] int NULL ,
[FRYHMMINS] int NULL ,
[FRYHMCOUNTS] int NULL ,
[FFBBHNEW] varchar(20) NULL ,
[FFBNEW] varchar(30) NULL ,
[FZFJE] numeric(18,2) NULL ,
[FZHFWLYLF] numeric(18,2) NULL ,
[FZHFWLCZF] numeric(18,2) NULL ,
[FZHFWLHLF] numeric(18,2) NULL ,
[FZHFWLQTF] numeric(18,2) NULL ,
[FZDLBLF] numeric(18,2) NULL ,
[FZDLSSSF] numeric(18,2) NULL ,
[FZDLYXF] numeric(18,2) NULL ,
[FZDLLCF] numeric(18,2) NULL ,
[FZLLFFSSF] numeric(18,2) NULL ,
[FZLLFWLZWLF] numeric(18,2) NULL ,
[FZLLFSSF] numeric(18,2) NULL ,
[FZLLFMZF] numeric(18,2) NULL ,
[FZLLFSSZLF] numeric(18,2) NULL ,
[FKFLKFF] numeric(18,2) NULL ,
[FZYLZF] numeric(18,2) NULL ,
[FXYLGJF] numeric(18,2) NULL ,
[FXYLXF] numeric(18,2) NULL ,
[FXYLBQBF] numeric(18,2) NULL ,
[FXYLQDBF] numeric(18,2) NULL ,
[FXYLYXYZF] numeric(18,2) NULL ,
[FXYLXBYZF] numeric(18,2) NULL ,
[FHCLCJF] numeric(18,2) NULL ,
[FHCLZLF] numeric(18,2) NULL ,
[FHCLSSF] numeric(18,2) NULL ,
[FZHFWLYLF01] numeric(18,2) NULL ,
[FZHFWLYLF02] numeric(18,2) NULL ,
[FZYLZDF] numeric(18,2) NOT NULL DEFAULT ((0)) ,
[FZYLZLF] numeric(18,2) NOT NULL DEFAULT ((0)) ,
[FZYLZLF01] numeric(18,2) NOT NULL DEFAULT ((0)) ,
[FZYLZLF02] numeric(18,2) NOT NULL DEFAULT ((0)) ,
[FZYLZLF03] numeric(18,2) NOT NULL DEFAULT ((0)) ,
[FZYLZLF04] numeric(18,2) NOT NULL DEFAULT ((0)) ,
[FZYLZLF05] numeric(18,2) NOT NULL DEFAULT ((0)) ,
[FZYLZLF06] numeric(18,2) NOT NULL DEFAULT ((0)) ,
[FZYLQTF] numeric(18,2) NOT NULL DEFAULT ((0)) ,
[FZYLQTF01] numeric(18,2) NOT NULL DEFAULT ((0)) ,
[FZYLQTF02] numeric(18,2) NOT NULL DEFAULT ((0)) ,
[FZCLJGZJF] numeric(18,2) NOT NULL DEFAULT ((0)) ,
[ZY01] varchar(20) NULL ,
[ZY02] varchar(20) NULL ,
[ZY03] varchar(30) NULL ,
[ZY04] varchar(200) NULL ,
[ZY05] varchar(20) NULL ,
[ZY06] varchar(20) NULL ,
[ZY07] varchar(20) NULL ,
[ZY08] varchar(20) NULL ,
[ZY09] varchar(20) NULL ,
[ZY10] varchar(20) NULL ,
[ZY11] varchar(20) NULL ,
[ZY12] varchar(20) NULL ,
[ZY13] varchar(20) NULL ,
[ZY14] varchar(20) NULL ,
[JYLSH] varchar(64) NULL DEFAULT NULL ,
[RESULT] text NULL DEFAULT NULL ,
[UPTIME] datetime2(0) NULL ,
[BASBAH] varchar(20) NULL 
)


GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
NULL, NULL)) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'Oh my God'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'Oh my God'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'ID')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'主键，按顺序排列'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'ID'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'主键，按顺序排列'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'ID'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'ISUPLOAD')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'默认值是 1；
上传成功后改成返回值，（就是 0）；
失败改成返回值，（小于 0）'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'ISUPLOAD'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'默认值是 1；
上传成功后改成返回值，（就是 0）；
失败改成返回值，（小于 0）'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'ISUPLOAD'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'FID_TPATIENTVISIT')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'[dbo].[TPATIENTVISIT] 的主键 FID'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FID_TPATIENTVISIT'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'[dbo].[TPATIENTVISIT] 的主键 FID'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FID_TPATIENTVISIT'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'InSurVisitId')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'就诊流水号；'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'InSurVisitId'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'就诊流水号；'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'InSurVisitId'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'CBDTCQH')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'参保地统筹编号'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'CBDTCQH'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'参保地统筹编号'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'CBDTCQH'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'FIDCARD')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'身份证'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FIDCARD'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'身份证'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FIDCARD'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'FPRN')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'病案号'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FPRN'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'病案号'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FPRN'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'FAGE')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'age'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FAGE'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'age'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FAGE'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'FJKKH')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'健康卡号'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FJKKH'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'健康卡号'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FJKKH'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'FRYDATE')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'入院日期'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FRYDATE'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'入院日期'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FRYDATE'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'FZYDOCT')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'住院医生'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FZYDOCT'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'住院医生'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FZYDOCT'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'FSUM1')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'总费用'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FSUM1'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'总费用'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FSUM1'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'FZHFWLYLF02')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'END'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FZHFWLYLF02'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'END'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'FZHFWLYLF02'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'JYLSH')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'交易流水号'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'JYLSH'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'交易流水号'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'JYLSH'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'RESULT')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'社保系统返回的结果'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'RESULT'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'社保系统返回的结果'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'RESULT'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'UPTIME')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'上传时间'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'UPTIME'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'上传时间'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'UPTIME'
GO
IF ((SELECT COUNT(*) from fn_listextendedproperty('MS_Description', 
'SCHEMA', N'dbo', 
'TABLE', N'TABLEUPLOAD', 
'COLUMN', N'BASBAH')) > 0) 
EXEC sp_updateextendedproperty @name = N'MS_Description', @value = N'病案室病案号'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'BASBAH'
ELSE
EXEC sp_addextendedproperty @name = N'MS_Description', @value = N'病案室病案号'
, @level0type = 'SCHEMA', @level0name = N'dbo'
, @level1type = 'TABLE', @level1name = N'TABLEUPLOAD'
, @level2type = 'COLUMN', @level2name = N'BASBAH'
GO

-- ----------------------------
-- Indexes structure for table TABLEUPLOAD
-- ----------------------------

-- ----------------------------
-- Primary Key structure for table TABLEUPLOAD
-- ----------------------------
ALTER TABLE [dbo].[TABLEUPLOAD] ADD PRIMARY KEY ([ID])
GO
