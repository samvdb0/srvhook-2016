USE [World00_Character]
GO

/****** Object:  StoredProcedure [dbo].[usp_InstanceDungeon_GetTop20]    Script Date: 10/06/2020 4:12:52 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


-- =============================================
-- Author:			Sam "Saze" V. - saze#6008
-- Create date:		12/02/2019
-- Last updated:	10/06/2020
-- =============================================
CREATE PROCEDURE [dbo].[usp_InstanceDungeon_GetTop20]
@sMapIndex nvarchar(12),
@nModeIDLv tinyint,
@nType int
AS
SET NOCOUNT ON;
IF @nType = 0
SELECT TOP 20 IndunRank.nDamageDealt, Char.sID, Shape.nClass
FROM tInstanceDungeonRanking AS IndunRank INNER JOIN tCharacter AS Char ON (IndunRank.nCharNo = Char.nCharNo) INNER JOIN tCharacterShape AS Shape ON (IndunRank.nCharNo = Shape.nCharNo)
WHERE IndunRank.sMapIndex = @sMapIndex AND IndunRank.nModeIDLv = @nModeIDLv
ORDER BY IndunRank.nDamageDealt DESC
ELSE IF @nType = 1
SELECT TOP 20 IndunRank.nDamageTaken, Char.sID, Shape.nClass
FROM tInstanceDungeonRanking AS IndunRank INNER JOIN tCharacter AS Char ON (IndunRank.nCharNo = Char.nCharNo) INNER JOIN tCharacterShape AS Shape ON (IndunRank.nCharNo = Shape.nCharNo)
WHERE IndunRank.sMapIndex = @sMapIndex AND IndunRank.nModeIDLv = @nModeIDLv
ORDER BY IndunRank.nDamageTaken ASC
ELSE IF @nType = 2
SELECT TOP 20 IndunRank.nHealingDone, Char.sID, Shape.nClass
FROM tInstanceDungeonRanking AS IndunRank INNER JOIN tCharacter AS Char ON (IndunRank.nCharNo = Char.nCharNo) INNER JOIN tCharacterShape AS Shape ON (IndunRank.nCharNo = Shape.nCharNo)
WHERE IndunRank.sMapIndex = @sMapIndex AND IndunRank.nModeIDLv = @nModeIDLv
ORDER BY IndunRank.nHealingDone DESC
GO


