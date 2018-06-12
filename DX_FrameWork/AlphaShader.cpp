#include "stdafx.h"

AlphaShader::AlphaShader()
{
	endPassNum = 2;
	alpha = 1.0f;
}

AlphaShader::~AlphaShader()
{
	SAFE_RELEASE(shader);
}

void AlphaShader::ShaderReady(RenderInfo * render)
{
	if (shader == nullptr)
	{
		CreateShader("AlphaShader.hlsl");
	}

	shader->SetTexture("_map", render->GetTexture());

	shader->SetFloat("_alpha", alpha);
	shader->SetBool("_blendOk", blendOk);
	ShaderBegin();
}
