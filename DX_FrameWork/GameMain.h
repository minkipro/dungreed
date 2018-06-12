#pragma once 
#include "Window.h"


class GameMain : public Window
{
public:
	GameMain(HINSTANCE instance);
	~GameMain();

	void Initialize();
	void Destroy();
	void Update();
	void Render();

private:

};