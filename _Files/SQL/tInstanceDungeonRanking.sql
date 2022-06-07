USE [World00_Character]
GO

/****** Object:  Table [dbo].[tInstanceDungeonRanking]    Script Date: 10/06/2020 1:16:59 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

-- =============================================
-- Author:			Sam "Saze" V. - saze#6008
-- Create date:		12/02/2019
-- Last updated:	10/06/2020
-- =============================================

CREATE TABLE [dbo].[tInstanceDungeonRanking](
	[nCharNo] [int] NOT NULL,
	[sMapIndex] [nvarchar](12) NOT NULL,
	[nModeIDLv] [tinyint] NOT NULL,
	[nDamageDealt] [bigint] NOT NULL,
	[nDamageTaken] [bigint] NOT NULL,
	[nHealingDone] [bigint] NOT NULL,
	[nPlayTime] [int] NOT NULL,
	[dDate] [datetime] NOT NULL,
	[nLastDamageDealt] [bigint] NOT NULL,
	[nLastDamageTaken] [bigint] NOT NULL,
	[nLastHealingDone] [bigint] NOT NULL,
	[nLastPlayTime] [int] NOT NULL,
	[dLastDate] [datetime] NOT NULL
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[tInstanceDungeonRanking] ADD  CONSTRAINT [DF_tInstanceDungeonRanking_nDamageDealt]  DEFAULT ((0)) FOR [nDamageDealt]
GO

ALTER TABLE [dbo].[tInstanceDungeonRanking] ADD  CONSTRAINT [DF_tInstanceDungeonRanking_nDamageTaken]  DEFAULT ((0)) FOR [nDamageTaken]
GO

ALTER TABLE [dbo].[tInstanceDungeonRanking] ADD  CONSTRAINT [DF_tInstanceDungeonRanking_nHealingDone]  DEFAULT ((0)) FOR [nHealingDone]
GO

ALTER TABLE [dbo].[tInstanceDungeonRanking] ADD  CONSTRAINT [DF_tInstanceDungeonRanking_nPlayTime]  DEFAULT ((0)) FOR [nPlayTime]
GO

ALTER TABLE [dbo].[tInstanceDungeonRanking] ADD  CONSTRAINT [DF_tInstanceDungeonRanking_dDate]  DEFAULT (getdate()) FOR [dDate]
GO

ALTER TABLE [dbo].[tInstanceDungeonRanking] ADD  CONSTRAINT [DF_tInstanceDungeonRanking_nPrevDamageDealt]  DEFAULT ((0)) FOR [nLastDamageDealt]
GO

ALTER TABLE [dbo].[tInstanceDungeonRanking] ADD  CONSTRAINT [DF_tInstanceDungeonRanking_nPrevDamageTaken]  DEFAULT ((0)) FOR [nLastDamageTaken]
GO

ALTER TABLE [dbo].[tInstanceDungeonRanking] ADD  CONSTRAINT [DF_tInstanceDungeonRanking_nPrevHealingDone]  DEFAULT ((0)) FOR [nLastHealingDone]
GO

ALTER TABLE [dbo].[tInstanceDungeonRanking] ADD  CONSTRAINT [DF_tInstanceDungeonRanking_nPrevPlayTime]  DEFAULT ((0)) FOR [nLastPlayTime]
GO

ALTER TABLE [dbo].[tInstanceDungeonRanking] ADD  CONSTRAINT [DF_tInstanceDungeonRanking_dPrevDate]  DEFAULT ((0)) FOR [dLastDate]
GO


