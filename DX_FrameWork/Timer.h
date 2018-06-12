#pragma once

class Font;

class Timer
{
public:
	void Init();
	void Tick(float lockFPS = 60.0f);
	void Render(bool trueORfalse);

	unsigned long GetFrameRate()  { return frameRate; }
	float GetElapsedTime() { return timeElapsed; }

private:
	Font* font;
	bool isHardware;
	float timeScale;
	float timeElapsed = 0;

	__int64 curTime;
	__int64 lastTime;
	__int64 periodFrequency;

	unsigned long frameRate;
	unsigned long FPSframeCount;

	float FPSTimeElapse;
};