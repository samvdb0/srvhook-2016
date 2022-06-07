#pragma once
#include "pch.h"

#include "SHNFile.hpp"

std::vector<std::string> NoExpoMaps;

class DataStore
{
	HOOK_PUB_S bool Load()
	{
		auto shinePath = Config->Get("Path", "Shine", "9Data/Shine");
		auto hookPath = Config->Get("Path", "Hook", "9Data/Hook");

		auto noExpoMaps = new SHNFile();
		if (!noExpoMaps->Read(FORMAT_STR("..\\%s\\NoExpeditionMap.shn", hookPath)))
		{
			Log::Info("Failed to read NoExpeditionMap.shn");
			return false;
		}

		for (uint i = 0; i < noExpoMaps->RowCount(); i++)
		{
			auto row = noExpoMaps->Row(i);

			NoExpoMaps.emplace_back(row->Get<std::string>(0));
		}

		return true;
	}

	HOOK_PUB_S bool IsNoRaidMap(char* map)
	{
		auto ret = std::find_if(NoExpoMaps.begin(), NoExpoMaps.end(), [map](const std::string& s) { return !strcmp(map, s.c_str()); });

		return ret != NoExpoMaps.end() ? true : false;
	}
};