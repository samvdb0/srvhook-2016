USE [World00_Character]
GO

/****** Object:  StoredProcedure [dbo].[usp_InstanceDungeon_GetAllRanks]    Script Date: 10/06/2020 4:12:08 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


-- =============================================
-- Author:			Sam "Saze" V. - saze#6008
-- Create date:		10/06/2020
-- Last updated:	10/06/2020
-- =============================================
CREATE PROCEDURE [dbo].[usp_InstanceDungeon_GetAllRanks]
@nCharNo int,
@sMapIndex nvarchar(12),
@nModeIDLv tinyint,
@nType tinyint
AS
SET NOCOUNT ON;
DECLARE @nResults int

SELECT @nResults = COUNT(*)
FROM tInstanceDungeonRanking
WHERE nCharNo = @nCharNo

IF @nResults > 0
BEGIN
	IF @nType = 0
	BEGIN
		SELECT nCharNo
		FROM tInstanceDungeonRanking
		WHERE sMapIndex = @sMapIndex AND nModeIDLv = @nModeIDLv
		ORDER BY nDamageDealt DESC
	END
	ELSE IF @nType = 1
	BEGIN
		SELECT nCharNo
		FROM tInstanceDungeonRanking
		WHERE sMapIndex = @sMapIndex AND nModeIDLv = @nModeIDLv
		ORDER BY nDamageTaken ASC
	END
	ELSE IF @nType = 2
	BEGIN
		SELECT nCharNo
		FROM tInstanceDungeonRanking
		WHERE sMapIndex = @sMapIndex AND nModeIDLv = @nModeIDLv
		ORDER BY nHealingDone DESC
	END
END
GO


