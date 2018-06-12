#pragma once

class TimeManager
{
public:
	TimeManager();
	static TimeManager * Get();
	void Init();
	void Update();
	void Render(bool trueORfalse);

	void SetFPS(float fps) { lockFPS = fps; }
	float GetElapsedTime();

private:
	static TimeManager * instance;
	Timer timer;
	float stopTime;
	float slowSpeed;
	float lockFPS;
};