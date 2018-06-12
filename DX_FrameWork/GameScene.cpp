#include "stdafx.h"

void GameScene::Init()
{
	
	map = new Map;
	map->Init();
	map->LoadMap();

	cat = new Cat;
	cat->SetMap(map);
}

void GameScene::Update()
{
	map->Update();

	cat->Update();
}

void GameScene::Release()
{
	SAFE_DELETE(map);
	SAFE_DELETE(cat);
}

void GameScene::Render()
{
	TEXTUREMANAGER->Render("GameScene");
}


