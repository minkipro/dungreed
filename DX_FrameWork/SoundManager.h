#pragma once

#include "inc\fmod.hpp"
#pragma comment(lib,"lib/fmodex_vc.lib")

using namespace FMOD;

#define SOUNDCOUNT 15

struct SOUNDnCH
{
	Sound* sound;
	Channel* channel;

	SOUNDnCH()
	{
		sound = nullptr;
		channel = nullptr;
	}
};

class SoundManager
{
public:
	static SoundManager * Get();
	void Init();
	void AddSound(string keyName, string soundName, bool bgm, bool loop);
	void AddSoundToFolder(string folderName, string extension,bool bgm, bool loop);

	void Update();

	void Play(string keyName, float volum = 1.0f);
	void Stop(string keyName);
	void Pause(string keyName);
	void Resume(string keyName);

	void StopAll();

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

private:
	static SoundManager * instance;
	System * _system;
	map<string, SOUNDnCH*>totalSound;
	map<string, SOUNDnCH*>::iterator it;
};