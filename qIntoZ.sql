DECLARE @zy VARCHAR(20) 
DECLARE @qh VARCHAR(6) 
DECLARE @tp VARCHAR(20) 
DECLARE @sfz VARCHAR(30) 

SELECT 
@zy = db_upload.dbo.TT.InSurVisitId, 
@qh = db_upload.dbo.TT.CBDTCQH, 
@tp = db_upload.dbo.TT.FIDCARD_TYPE, 
@sfz = db_upload.dbo.TT.FIDCARD 
FROM dbo.TT 
WHERE dbo.TT.FPRN = @bah AND dbo.TT.FTIMES = @cs 

INSERT INTO db_upload.dbo.ZZ(
dbo.ZZ.ZID,
dbo.ZZ.FPRN,
dbo.ZZ.FTIMES,
dbo.ZZ.InSurVisitId,
dbo.ZZ.CBDTCQH,
dbo.ZZ.FIDCARD_TYPE,
dbo.ZZ.FIDCARD,
dbo.ZZ.ZICDBB,
dbo.ZZ.ZPX,
dbo.ZZ.ZZDLX,
dbo.ZZ.ZJBMC,
dbo.ZZ.ZICDM,
dbo.ZZ.ZRYBQBH,
dbo.ZZ.ZRYBQ)

VALUES (