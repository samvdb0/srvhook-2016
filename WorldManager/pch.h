// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H
#define _CRT_SECURE_NO_WARNINGS

// add headers that you want to pre-compile here

#include "framework.h"
#include <string>
#include <tlhelp32.h>
#include <Psapi.h>
#include <iostream>
#include <vector>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <list>
#include <set>
#include <WinSock2.h>
#include <cstdarg>
#include <fstream>
#include <map>
#include <algorithm>
#include <cstddef>
#include <functional>

#include <detours.h>

#define Detour(addr, func) DetourFunction((PBYTE) addr, (PBYTE) func)
#define STR(x) std::string(x).c_str()
#define FORMAT_STR(x, ...) Format::Create(x, __VA_ARGS__)
#define MF(x) MemberFuncToPtr(&x)
#define TOSTR(x) std::to_string(x)
#define NOW() std::time(0)
#define EQUALS(x, y) (_stricmp(x, y) == 0)
#define DEFINE_GLOBAL(TYPE, ADDR, NAME) TYPE& NAME = *(TYPE*) (ADDR);

#define DELARR(x) if(x != NULL){ delete [] x; x = NULL; }
#define DEL2DARR( arr, size ) { if( arr != NULL ) { for(UINT32 i = 0; i < size; i++){ delete arr[i]; } delete [] arr; arr = NULL; } }

#define sec * 1000
#define meters * 1000

#define HOOK_PUB_S public: static
#define HOOK_PUB_M public:

#define HOOK_PRIV_S private: static
#define HOOK_PRIV_M private:

#define HOOK_PROT_S protected: static
#define HOOK_PROT_M protected:

#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int
#define ulong unsigned long

// #define CONSOLE
// #define WEB_API

static long StartupTime;
static char LogFile[MAX_PATH];
inline char* GetBaseDir()
{
	static char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	auto pos = std::string(buffer).find_last_of("\\/");
	strcpy_s(buffer, std::string(buffer).substr(0, pos).append("\\").c_str());
	return buffer;
}
inline char* ReadFile(const char* fname)
{
	FILE* f;
	if (0 != fopen_s(&f, fname, "rb")) return NULL;
	fseek(f, 0, SEEK_END);
	int s = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* buf = new char[s + 1];
	fread(buf, s, 1, f);
	buf[s] = 0;
	fclose(f);
	return buf;
}
inline void WriteMem(DWORD* address, void* arr, int size)
{
	DWORD oldProtection;

	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtection);
	memcpy(address, arr, size);
	VirtualProtect(address, size, oldProtection, &oldProtection);
}

#include "Format.h"

#include "Log.h"
#include "Templates.hpp"

#include "INIFile.h"

static INIReader* Config;

#endif //PCH_H
