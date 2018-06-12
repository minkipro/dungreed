#pragma once

class GameScene :public SceneMain
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Release();
	virtual void Render();

private:
	Map* map;
	Cat * cat;
};