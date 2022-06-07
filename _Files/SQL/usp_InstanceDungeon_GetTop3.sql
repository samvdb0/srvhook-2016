USE [World00_Character]
GO

/****** Object:  StoredProcedure [dbo].[usp_InstanceDungeon_GetTop3]    Script Date: 10/06/2020 4:13:07 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


-- =============================================
-- Author:			Sam "Saze" V. - saze#6008
-- Create date:		12/02/2019
-- Last updated:	10/06/2020
-- =============================================
CREATE PROCEDURE [dbo].[usp_InstanceDungeon_GetTop3]
@sMapIndex nvarchar(12),
@nModeIDLv tinyint,
@nType tinyint
AS
SET NOCOUNT ON;
IF @nType = 0
SELECT TOP 3 Shape.nRace, Shape.nClass, Shape.nGender, Shape.nHairType, Shape.nHairColor, Shape.nFaceShape
FROM tInstanceDungeonRanking AS IndunRank INNER JOIN tCharacterShape AS Shape ON (IndunRank.nCharNo = Shape.nCharNo)
WHERE IndunRank.sMapIndex = @sMapIndex AND IndunRank.nModeIDLv = @nModeIDLv
ORDER BY IndunRank.nDamageDealt DESC
ELSE IF @nType = 1
SELECT TOP 3 Shape.nRace, Shape.nClass, Shape.nGender, Shape.nHairType, Shape.nHairColor, Shape.nFaceShape
FROM tInstanceDungeonRanking AS IndunRank INNER JOIN tCharacterShape AS Shape ON (IndunRank.nCharNo = Shape.nCharNo)
WHERE IndunRank.sMapIndex = @sMapIndex AND IndunRank.nModeIDLv = @nModeIDLv
ORDER BY IndunRank.nDamageTaken ASC
ELSE IF @nType = 2
SELECT TOP 3 Shape.nRace, Shape.nClass, Shape.nGender, Shape.nHairType, Shape.nHairColor, Shape.nFaceShape
FROM tInstanceDungeonRanking AS IndunRank INNER JOIN tCharacterShape AS Shape ON (IndunRank.nCharNo = Shape.nCharNo)
WHERE IndunRank.sMapIndex = @sMapIndex AND IndunRank.nModeIDLv = @nModeIDLv
ORDER BY IndunRank.nHealingDone DESC
GO


