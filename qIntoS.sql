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

INSERT INTO db_upload.dbo.SS(
dbo.SS.SID,
dbo.SS.FPRN,
dbo.SS.FTIMES,
dbo.SS.InSurVisitId,
dbo.SS.CBDTCQH,
dbo.SS.FIDCARD_TYPE,
dbo.SS.FIDCARD,
dbo.SS.SPX,
dbo.SS.SSSM,
dbo.SS.SSSNAME,
dbo.SS.SSDATE,
dbo.SS.SQKBH,
dbo.SS.SQK,
dbo.SS.SYHBH,
dbo.SS.SYH,
dbo.SS.SSSYSBH,
dbo.SS.SSSYS,
dbo.SS.SMZFSBH,
dbo.SS.SMZFS,
dbo.SS.SSFFJSS,
dbo.SS.SIZBH,
dbo.SS.SIZNAME,
dbo.SS.SIIZBH,
dbo.SS.SIIZNAME,
dbo.SS.SMZYSBH,
dbo.SS.SMZYS,
dbo.SS.SZQSSBH,
dbo.SS.SZQSS,
dbo.SS.SSSJBBH,
dbo.SS.SSSJB)

VALUES (