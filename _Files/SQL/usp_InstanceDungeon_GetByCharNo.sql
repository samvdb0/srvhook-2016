USE [World00_Character]
GO

/****** Object:  StoredProcedure [dbo].[usp_InstanceDungeon_GetByCharNo]    Script Date: 10/06/2020 4:12:39 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


-- =============================================
-- Author:			Sam "Saze" V. - saze#6008
-- Create date:		12/02/2019
-- Last updated:	10/06/2020
-- =============================================
CREATE PROCEDURE [dbo].[usp_InstanceDungeon_GetByCharNo]
@nCharNo int
AS
SET NOCOUNT ON;
SELECT * FROM tInstanceDungeonRanking
WHERE nCharNo = @nCharNo
GO


