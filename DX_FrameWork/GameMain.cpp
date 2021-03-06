#include "stdafx.h"

GameMain::GameMain(HINSTANCE instance)
	: Window(instance)
{
	srand(time(0));
}

GameMain::~GameMain()
{
	delete SCENEMANAGER;
	delete TEXTUREMANAGER;
}

void GameMain::Initialize()
{
	TIMER->Init();
	TIMER->SetFPS(200.0f);

	TEXTUREMANAGER->LoadTextureToFolder("Image", "png");
	TEXTUREMANAGER->LoadTextureToFolder("Image", "jpg");
	//////////////////////////
	TEXTUREMANAGER->AddFrame("Tile", 9, 10);
	
	//씬 추가
	//SCENEMG->AddScene("textureEditerScene", new TextureEditerScene, true);
	SCENEMANAGER->AddScene("GameScene", new GameScene, true);
	SCENEMANAGER->AddScene("MapEditScene", new MapEditScene, true);
	SCENEMANAGER->ChangeScene("GameScene");
	//SCENEMANAGER->ChangeScene("MapEditScene");
	//////////////////////////
	SCENEMANAGER->Init();
}

void GameMain::Destroy()
{
	
}

void GameMain::Update()
{
	SCENEMANAGER->Update();
	TIMER->Update();
	TEXTUREMANAGER->Update();
}

void GameMain::Render()
{
	SCENEMANAGER->Render();
}
