#include "stdafx.h"

Shader::Shader()
{
	blendOk = false;
	endPassNum = 0;
	currentPass = 0;
}

Shader::~Shader()
{
	SAFE_RELEASE(shader);
}

void Shader::ShaderEnd()
{
	shader->EndPass();
	shader->End();
}

void Shader::SetBlend(bool blend)
{
	blendOk = blend;
}

void Shader::SelectPass(UINT num)
{
	assert(num <= endPassNum);

	currentPass = num;
}

void Shader::CreateShader(string fileName)
{
	SAFE_RELEASE(shader);

	LPD3DXBUFFER error;
	wstring wFileName;
	wFileName.assign(fileName.begin(), fileName.end());
	HRESULT hr = D3DXCreateEffectFromFile(DEVICE, wFileName.c_str(), NULL,
		NULL, D3DXSHADER_DEBUG, NULL, &shader, &error);

	if (error != NULL)
	{
		string str = (const char*)error->GetBufferPointer();
		MessageBoxA(NULL, str.c_str(), "Shader Error", MB_OK);
	}

	assert(shader != nullptr);
}

void Shader::ShaderBegin()
{
	shader->Begin(NULL, NULL);
	shader->BeginPass(currentPass);
}
