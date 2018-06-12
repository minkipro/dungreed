#include "stdafx.h"

SceneManager* SceneManager::instance;

SceneManager::~SceneManager()
{
	for (auto it : sceneList)
	{
		SAFE_DELETE(it.second.scene);
	}
}

SceneManager * SceneManager::Get()
{
	if (instance == nullptr)
	{
		instance = new SceneManager;
	}

	return instance;
}

void SceneManager::Init()
{
	assert(currentScene.scene);

	currentScene.scene->Init();
	//TIMEMG->Render(true);
}

void SceneManager::Update()
{
	assert(currentScene.scene);

	currentScene.scene->Update();
}

void SceneManager::Render()
{
	TEXTUREMANAGER->Render(iter->first);
	currentScene.scene->Render();
}

void SceneManager::Releaase()
{
}

void SceneManager::AddScene(string keyName, SceneMain * scene, bool release)
{
	assert(scene);

	if (sceneList.size() != 0)
	{
		iter = sceneList.find(keyName);

		assert(iter == sceneList.end());
	}

	SCENE temp;
	temp.scene = scene;
	temp.release = release;

	sceneList.insert({ keyName,temp });
	TEXTUREMANAGER->AddSceneRender(keyName);

	currentScene.scene = scene;
	currentScene.release = release;
	iter = sceneList.find(keyName);
}

string SceneManager::ChangeScene(string keyName)
{
	string temp = iter->first;

	if (iter->first == keyName)
	{
		return keyName;
	}

	TIMER->Render(false);

	iter = sceneList.find(keyName);

	assert(iter != sceneList.end());

	if (currentScene.release)
	{
		currentScene.scene->Release();
	}

	TEXTUREMANAGER->SelectSceneRender(keyName);

	currentScene = iter->second;
	currentScene.scene->Init();

	//TIMEMG->Render(true);
	return temp;
}

void * SceneManager::GetSTLAdress(string keyName, int num)
{
	auto it = sceneList.find(keyName);

	return it->second.scene->GetSTLAddress(num);
}
