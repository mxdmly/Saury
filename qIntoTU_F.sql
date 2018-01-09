DECLARE @id VARCHAR(20)
DECLARE @zy VARCHAR(20)

SELECT @id = nhis.dbo.InVisit.InVisitId, @zy = nhis.dbo.ZhaoQingInVisitSiReg.InSurVisitId
FROM nhis.dbo.ZhaoQingInVisitSiReg, nhis.dbo.InVisit
WHERE nhis.dbo.InVisit.InVisitId = '