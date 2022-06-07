#pragma once
#include "pch.h"

class Folder
{
public:
	static char* GetBaseDir()
	{
		static char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		auto pos = std::string(buffer).find_last_of("\\/");
		strcpy_s(buffer, std::string(buffer).substr(0, pos).append("\\").c_str());
		return buffer;
	}
};
