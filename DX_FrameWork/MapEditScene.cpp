#include "stdafx.h"

void MapEditScene::Init()
{
	for (int i = 0; i < TOTALMAPTILENUM; i++)
	{
		int a = i % MAPTILENUMX;
		int b = i / MAPTILENUMX;
		mapTile[i].Init(2, a * 50, b * 50);
		
	}
	LoadMap();
	for (int i = 0; i < TOTALMAPTILENUM; i++)
	{

		mapTile[i].GetRender();
	}

	
	for (int i = 0; i < TOTALTILENUM; i++)
	{
		int x = i % TILENUMX;
		int y = i / TILENUMX;
		tile[i].Init(i, WIN_WIDTH - 50 * (TILENUMX - x - 1), y * 50);
		tile[i].GetRender();
	}
	mousePos = {};
	currentTile.Init(1, mousePos.x, mousePos.y);
	currentTile.GetRender();
}

void MapEditScene::Update()
{
	if (KEYBOARD->KeyPress(VK_LBUTTON))
	{
		SelectTile();
		InputTile();
	}
	for (int i = 0; i < TOTALTILENUM; i++)
	{
		tile[i].Update();
	}
	mousePos = MOUSE->GetPosition();
	currentTile.pos = { mousePos.x - 25, mousePos.y - 25 };
	currentTile.Update();

	for (int i = 0; i < TOTALMAPTILENUM; i++)
	{
		mapTile[i].Update();
	}

	if (KEYBOARD->KeyPress(VK_LCONTROL))
	{
		if (KEYBOARD->KeyDown('S'))
		{
			SaveMap();
		}
	}
}

void MapEditScene::Release()
{

}

void MapEditScene::Render()
{
	TEXTUREMANAGER->Render("MapEditScene");
}

void MapEditScene::SelectTile()
{
	for (int i = 0; i < TOTALTILENUM; i++)
	{
		if (PtInRect(&tile[i].rc,
			{ (long)mousePos.x,(long)mousePos.y }))
		{
			currentTile.frameNum = tile[i].frameNum;
		}
	}
}

void MapEditScene::InputTile()
{
	for (int i = 0; i < TOTALMAPTILENUM; i++)
	{
		if (PtInRect(&mapTile[i].rc,
			{ (long)mousePos.x,(long)mousePos.y }))
		{
			mapTile[i].frameNum = currentTile.frameNum;
		}
	}
}

void MapEditScene::SaveMap()
{
	HANDLE file;
	DWORD write;

	file = CreateFile(L"mapData.map", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, mapTile, sizeof(mapTile), &write, NULL);
	CloseHandle(file);
}

void MapEditScene::LoadMap()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(L"mapData.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, mapTile, sizeof(mapTile), &read, NULL);
	CloseHandle(file);
}
