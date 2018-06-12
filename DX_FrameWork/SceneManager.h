#pragma once

struct SCENE
{
	SCENE()
	{
		scene = nullptr;
		release = true;
	}

	bool operator ==(const SCENE&_scene)
	{
		if (this->scene == _scene.scene &&
			this->release == _scene.release)
		{
			return true;
		}
	
		return false;
	}

	SceneMain* scene;
	bool release;
};

class SceneManager
{
public:
	~SceneManager();
	static SceneManager* Get();

	void Init();
	void Update();
	void Render();
	void Releaase();

	void AddScene(string keyName, SceneMain* scene, bool release);
	string ChangeScene(string keyName);
	void* GetSTLAdress(string keyName, int num);
	string GetSceneName() { assert(currentScene.scene); return iter->first; }

private:
	static SceneManager * instance;

	SCENE currentScene;
	map<string, SCENE> sceneList;
	map<string, SCENE>::iterator iter;


};