#pragma once
#include "pch.h"

#define ReadUInt32() ReadData<UINT32>(data, &readPos);
#define ReadInt32() ReadData<INT32>(data, &readPos);
#define ReadUInt16() ReadData<UINT16>(data, &readPos);
#define ReadByte() ReadData<BYTE>(data, &readPos);
#define ReadFloat() ReadData<FLOAT>(data, &readPos);
#define Skip(x) readPos += x;

struct SHNColumn
{
	char Name[48];
	UINT32 Type;
	UINT32 ColumnSize;
};

struct SHNData
{
	union
	{
		BYTE Byte;
		UINT16 UShort;
		INT32 Int;
		UINT32 UInt;
		UINT64 ULong;
		FLOAT Float;
		char* String;
	};
};

struct SHNRow
{
	SHNRow() : ColumnCount(0), Cells(NULL) {}
	~SHNRow() { DEL2DARR(Cells, ColumnCount); }

	template<typename T> T Get(int indx) { }
	template<> BYTE Get<BYTE>(int indx) { return Cells[indx]->Byte; }
	template<> UINT16 Get<UINT16>(int indx) { return Cells[indx]->UShort; }
	template<> INT32 Get<INT32>(int indx) { return Cells[indx]->Int; }
	template<> UINT32 Get<UINT32>(int indx) { return Cells[indx]->UInt; }
	template<> UINT64 Get<UINT64>(int indx) { return Cells[indx]->ULong; }
	template<> FLOAT Get<FLOAT>(int indx) { return Cells[indx]->Float; }
	template<> std::string Get<std::string>(int indx) { return std::string(Cells[indx]->String); }
	template<> char* Get<char*>(int indx) { return Cells[indx]->String; }

	UINT32 ColumnCount;
	SHNData** Cells;
};

enum SHNCrypto
{
	STANDARD = 0,
	NEBULA = 1
};

class SHNFile
{
public:
	SHNFile() {}
	~SHNFile()
	{
		for (UINT32 i = 0; i < Rows.size(); i++)
		{
			for (UINT32 j = 0; j < Columns.size(); j++)
			{
				if (Columns[j]->Type == 9 || Columns[j]->Type == 26)
				{
					delete[] Rows[i]->Cells[j]->String;
					Rows[i]->Cells[j]->String = nullptr;
				}
			}

			delete Rows[i];
			Rows[i] = nullptr;
		}

		for (UINT32 i = 0; i < Columns.size(); i++)
		{
			delete Columns[i];
			Columns[i] = nullptr;
		}

		Rows.clear();
		Columns.clear();
	}

	bool Read(const char* path)
	{
		char pathBuff[MAX_PATH];
		sprintf(pathBuff, "%s%s", GetBaseDir(), path);

		FILE* file;
		fopen_s(&file, pathBuff, "rb");

		if (!file)
		{
			return false;
		}

		fseek(file, 0, SEEK_END);
		long fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		BYTE* data = new BYTE[fileSize];
		fread(data, fileSize, 1, file);
		fclose(file);

		// Check if file is a SHN.
		if (data[28] != 1)
		{
			DELARR(data);
			return false;
		}

		Decrypt(data + 36, fileSize - 36);

		UINT32 readPos = 40;
		auto rowCount = ReadUInt32();
		Skip(4);
		auto columnCount = ReadUInt32();

		for (UINT32 i = 0; i < columnCount; i++)
		{
			auto currColumn = new SHNColumn();
			memcpy(currColumn, data + readPos, 56);

			Columns.push_back(currColumn);
			Skip(56);
		}

		for (UINT32 i = 0; i < rowCount; i++)
		{
			auto rowSize = ReadUInt16();
			auto currRow = new SHNRow();

			currRow->ColumnCount = columnCount;
			currRow->Cells = new SHNData * [currRow->ColumnCount];

			for (UINT32 j = 0; j < columnCount; j++)
			{
				auto currColumn = Columns[j];
				auto currData = new SHNData();

				switch (currColumn->Type)
				{
				case 1:
				case 12:
				case 16:
					currData->Byte = ReadByte();
					break;
				case 2:
					currData->UShort = ReadUInt16();
					break;
				case 3:
				case 11:
				case 18:
				case 27:
					currData->UInt = ReadUInt32();
					break;
				case 5:
					currData->Float = ReadFloat();
					break;
				case 9:
				case 24:
				{
					char* tempStr = new char[currColumn->ColumnSize + 1];
					memcpy(tempStr, data + readPos, currColumn->ColumnSize);
					tempStr[currColumn->ColumnSize] = 0;

					Skip(currColumn->ColumnSize);
					currData->String = tempStr;
				}
				break;
				case 26:
				{
					UINT32 length = strlen((char*)(data + readPos));
					char* tempStr2 = new char[length + 1];
					memcpy(tempStr2, data + readPos, length);
					tempStr2[length] = 0;

					Skip(length);
					currData->String = tempStr2;
				}
				break;
				default:
					Skip(currColumn->ColumnSize);
					currData->UInt = 0;
					break;
				}

				currRow->Cells[j] = currData;
			}

			Rows.push_back(currRow);
		}

		DELARR(data);
		return true;
	}

	UINT32 RowCount()
	{
		return Rows.size();
	}

	SHNRow* Row(UINT32 row)
	{
		if (row > Rows.size())
		{
			return nullptr;
		}

		return Rows.at(row);
	}

private:
	template <typename T>
	T ReadData(BYTE* data, UINT32* position)
	{
		*position += sizeof(T);
		return *reinterpret_cast<T*>(data + *position - sizeof(T));
	}

	BYTE* Decrypt(BYTE* data, long int fileSize)
	{
		BYTE key = fileSize & 0xFF;

		auto first = Config->GetInteger("SHN", "First", 15);
		auto second = Config->GetInteger("SHN", "Second", 85);
		auto third = Config->GetInteger("SHN", "Third", 11);
		auto fourth = Config->GetInteger("SHN", "Fourth", 170);

		for (long int i = fileSize - 1; i > 0; --i)
		{
			data[i] ^= key;
			BYTE tmp1 = third * (BYTE)i;
			BYTE tmp2 = (i & first) + second;
			key ^= tmp1 ^ tmp2 ^ fourth;
		}

		return data;
	}

	BYTE* Decrypt_NEBULA(BYTE* data, long int fileSize)
	{
		BYTE key = fileSize & 0xFF;

		for (long int i = fileSize - 1; i > 0; --i)
		{
			data[i] ^= key;
			BYTE tmp1 = 0x0B * (BYTE)i;
			BYTE tmp2 = (i & 0x0F) + 0x56;
			key ^= tmp1 ^ tmp2 ^ 0xAA;
		}

		return data;
	}

private:
	std::vector<SHNColumn*> Columns;
	std::vector<SHNRow*> Rows;
};

