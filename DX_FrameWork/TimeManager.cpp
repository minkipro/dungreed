#include "stdafx.h"

TimeManager* TimeManager::instance = nullptr;

TimeManager::TimeManager()
{
	lockFPS = 60.0f;
}

TimeManager * TimeManager::Get()
{
	if (instance == nullptr)
	{
		instance = new TimeManager;
	}

	return instance;
}

void TimeManager::Init()
{
	timer.Init();
}

void TimeManager::Update()
{
	timer.Tick(lockFPS);
}

void TimeManager::Render(bool trueORfalse)
{
	timer.Render(trueORfalse);
}

float TimeManager::GetElapsedTime()
{
	return timer.GetElapsedTime();
}
