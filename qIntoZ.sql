DECLARE @zy VARCHAR(20) 
DECLARE @qh VARCHAR(6) 
DECLARE @tp VARCHAR(20) 
DECLARE @sfz VARCHAR(30) 

SELECT 
@zy = db_upload.dbo.TABLEUPLOAD.InSurVisitId, 
@qh = db_upload.dbo.TABLEUPLOAD.CBDTCQH, 
@tp = db_upload.dbo.TABLEUPLOAD.FIDCARD_TYPE, 
@sfz = db_upload.dbo.TABLEUPLOAD.FIDCARD 
FROM dbo.TABLEUPLOAD 
WHERE dbo.TABLEUPLOAD.FPRN = @bah AND dbo.TABLEUPLOAD.FTIMES = @cs 

INSERT INTO db_upload.dbo.TABLEZ(
dbo.TABLEZ.ZID,
dbo.TABLEZ.FPRN,
dbo.TABLEZ.FTIMES,
dbo.TABLEZ.InSurVisitId,
dbo.TABLEZ.CBDTCQH,
dbo.TABLEZ.FIDCARD_TYPE,
dbo.TABLEZ.FIDCARD,
dbo.TABLEZ.ZPX,
dbo.TABLEZ.ZZDLX,
dbo.TABLEZ.ZJBMC,
dbo.TABLEZ.ZICDM,
dbo.TABLEZ.ZRYBQBH,
dbo.TABLEZ.ZRYBQ)

VALUES (