#include "stdafx.h"

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager * ShaderManager::Get()
{
	if (instance == nullptr)
	{
		instance = new ShaderManager;
	}

	return instance;
}

void ShaderManager::AddShader(string name, Shader* shader)
{
	assert(ShaderList.count(name)==0);

	ShaderList.insert({ name,shader });
}

Shader * ShaderManager::GetShader(string name)
{
	it = ShaderList.find(name);
	assert(it != ShaderList.end());

	return it->second;
}

ShaderManager::ShaderManager()
{
	Shader* nomalShader = new ColorShader;
	nomalShader->SelectPass(2);
	ShaderList.insert({ "nomalShader",nomalShader });
}

ShaderManager::~ShaderManager()
{
	for (auto it : ShaderList)
	{
		SAFE_DELETE(it.second);
	}
}
