#include "stdafx.h"

Map::Map()
{

}

Map::~Map()
{
}

void Map::Init()
{
	for (int i = 0; i < TOTALMAPTILENUM; i++)
	{
		int a = i % MAPTILENUMX;
		int b = i / MAPTILENUMX;
		mapTile[i].Init(2, a * 50, b * 50);
	}
}

void Map::Update()
{
	for (int i = 0; i < TOTALMAPTILENUM; i++)
	{
		mapTile[i].Update();
	}
}

void Map::LoadMap()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(L"mapData.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, mapTile, sizeof(mapTile), &read, NULL);
	CloseHandle(file);
	for (int i = 0; i < TOTALMAPTILENUM; i++)
	{
		mapTile[i].GetRender();
	}
}