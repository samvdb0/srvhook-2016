USE [World00_Character]
GO

/****** Object:  StoredProcedure [dbo].[usp_InstanceDungeon_SaveRank]    Script Date: 10/06/2020 4:13:17 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


-- =============================================
-- Author:			Sam "Saze" V. - saze#6008
-- Create date:		12/02/2019
-- Last updated:	10/06/2020
-- =============================================
CREATE PROCEDURE [dbo].[usp_InstanceDungeon_SaveRank]
@nCharNo int,
@sMapIndex nvarchar(12),
@nModeIDLv tinyint,
@nPlayTime int,
@nDamageDealt bigint,
@nDamageTaken bigint,
@nHealingDone bigint
AS
SET NOCOUNT ON;

DECLARE @nResults int
DECLARE @Best_nPlayTime int
DECLARE @Best_nDamageDealt bigint
DECLARE @Best_nDamageTaken bigint
DECLARE @Best_nHealingDone bigint
DECLARE @Best_dDate datetime
DECLARE @HasChanged tinyint

SET @HasChanged = 0

SELECT @nResults = COUNT(*)
FROM tInstanceDungeonRanking
WHERE nCharNo = @nCharNo AND sMapIndex = @sMapIndex AND nModeIDLv = @nModeIDLv

IF @nResults > 0
BEGIN
	SELECT @Best_nPlayTime = nPlayTime, @Best_nDamageDealt = nDamageDealt, @Best_nDamageTaken = nDamageTaken, @Best_nHealingDone = nHealingDone, @Best_dDate = dDate
	FROM tInstanceDungeonRanking
	WHERE nCharNo = @nCharNo AND sMapIndex = @sMapIndex AND nModeIDLv = @nModeIDLv

	IF @Best_nPlayTime > @nPlayTime
	BEGIN
		SET @Best_nPlayTime = @nPlayTime
		SET @HasChanged = 1
	END

	IF @Best_nDamageDealt < @nDamageDealt
	BEGIN
		SET @Best_nDamageDealt = @nDamageDealt
		SET @HasChanged = 1
	END

	IF @Best_nDamageTaken > @nDamageTaken
	BEGIN
		SET @Best_nDamageTaken = @nDamageTaken
		SET @HasChanged = 1
	END
	
	IF @Best_nHealingDone < @nHealingDone
	BEGIN
		SET @Best_nDamageTaken = @nDamageTaken
		SET @HasChanged = 1
	END

	IF @HasChanged = 1
	BEGIN
		SET @Best_dDate = GETDATE()
	END

	UPDATE tInstanceDungeonRanking
	SET nDamageDealt = @Best_nDamageDealt, nDamageTaken = @Best_nDamageTaken, nHealingDone = @Best_nHealingDone, nPlayTime = @Best_nPlayTime, dDate = @Best_dDate, nLastDamageDealt = @nDamageDealt, nLastDamageTaken = @nDamageTaken, nLastHealingDone = @nHealingDone, nLastPlayTime = @nPlayTime, dLastDate = GETDATE()
	WHERE nCharNo = @nCharNo AND sMapIndex = @sMapIndex AND nModeIDLv = @nModeIDLv
END
ELSE
BEGIN
	INSERT INTO tInstanceDungeonRanking (nCharNo, sMapIndex, nModeIDLv, nDamageDealt, nDamageTaken, nHealingDone, nPlayTime, dDate, nLastDamageDealt, nLastDamageTaken, nLastHealingDone, nLastPlayTime, dLastDate)
	VALUES (@nCharNo, @sMapIndex, @nModeIDLv, @nDamageDealt, @nDamageTaken, @nHealingDone, @nPlayTime, GETDATE(), @nDamageDealt, @nDamageTaken, @nHealingDone, @nPlayTime, GETDATE())
END
GO


