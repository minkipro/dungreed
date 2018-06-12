#include "stdafx.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")


void Timer::Init()
{
	if (font == nullptr)
	{
		font = TEXTUREMANAGER->GetFont("궁서체", { 30,30 });
		font->SetPos({ 300,0 });
	}

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		isHardware = true;

		//일정 지점 안에서 몇번 진동했는지 나타내는 함수
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		isHardware = false;

		lastTime = timeGetTime();
		timeScale = 0.001f;
	}

	frameRate = 0;
	FPSframeCount = 0;
	FPSTimeElapse = 0;
}

void Timer::Tick(float lockFPS)
{
	if (isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	}
	else
	{
		curTime = timeGetTime();
	}

	timeElapsed = (curTime - lastTime)*timeScale;

	assert(lockFPS);

	if (timeElapsed < (1.0f / lockFPS))
	{
		Sleep(((1.0f / lockFPS) - timeElapsed)*1000);
		timeElapsed += (1.0f / lockFPS)-timeElapsed;

		if (isHardware)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
		}
		else
		{
			curTime = timeGetTime();
		}
	}

	lastTime = curTime;
	FPSframeCount++;
	FPSTimeElapse += timeElapsed;

	if (FPSTimeElapse > 1.0f)
	{
		frameRate = FPSframeCount;
		FPSframeCount = 0;
		FPSTimeElapse = 0;

		string fps= to_string((int)frameRate);
		font->SetText(fps);
	}
}

void Timer::Render(bool trueORfalse)
{
	font->SetActive(trueORfalse);
}
