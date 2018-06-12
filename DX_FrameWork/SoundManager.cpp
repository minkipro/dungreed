#include "stdafx.h"

SoundManager* SoundManager::instance = nullptr;

SoundManager * SoundManager::Get()
{
	if (instance == nullptr)
	{
		instance = new SoundManager;
	}
	
	return instance;
}

void SoundManager::Init()
{
	System_Create(&_system);
	_system->init(SOUNDCOUNT, FMOD_INIT_NORMAL, NULL);
}

void SoundManager::AddSound(string keyName, string soundName, bool bgm, bool loop)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		return;
	}

	SOUNDnCH* soundnCh = new SOUNDnCH;

	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &soundnCh->sound);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &soundnCh->sound);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &soundnCh->sound);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &soundnCh->sound);
		}
	}

	totalSound.insert({ keyName,soundnCh });
}

void SoundManager::AddSoundToFolder(string folderName, string extension, bool bgm, bool loop)
{
	_finddata_t fd;

	long handle;
	int result = 1;
	string fileName;
	string keyName;

	fileName = folderName + "\\*.";
	fileName += extension + "*";
	handle = _findfirst(fileName.c_str(), &fd);
	assert(handle != -1);

	fileName = fd.name;

	while (result != -1)
	{
		for (int i = 0; i < fileName.size(); i++)
		{
			if (fileName[i] == '.')
			{
				break;
			}

			assert(fileName[i]);
			keyName += fileName[i];
		}

		AddSound(keyName, folderName + "/" + fd.name, bgm, loop);
		keyName.clear();
		result = _findnext(handle, &fd);
		fileName = fd.name;
	}
}

void SoundManager::Update()
{
	_system->update();
}

void SoundManager::Play(string keyName, float volum)
{

	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		_system->playSound(FMOD_CHANNEL_FREE, it->second->sound, false, &it->second->channel);
		it->second->channel->setVolume(volum);
	}
}

void SoundManager::Stop(string keyName)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		it->second->channel->stop();
	}
}

void SoundManager::Pause(string keyName)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		it->second->channel->setPaused(true);
	}
}

void SoundManager::Resume(string keyName)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		it->second->channel->setPaused(false);
	}
}

void SoundManager::StopAll()
{
	for (it = totalSound.begin(); it != totalSound.end(); it++)
	{
		it->second->channel->stop();
	}

	for (int i = 0; i < SOUNDCOUNT; i++)
	{
		_system->recordStop(i);
	}
}

bool SoundManager::isPlaySound(string keyName)
{
	it = totalSound.find(keyName);

	bool isPlay = false;

	if (it != totalSound.end())
	{
		it->second->channel->isPlaying(&isPlay);
	}

	return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
	it = totalSound.find(keyName);

	bool isPause = false;

	if (it != totalSound.end())
	{
		it->second->channel->getPaused(&isPause);
	}

	return isPause;
}
