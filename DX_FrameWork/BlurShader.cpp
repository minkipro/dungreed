#include "stdafx.h"

BlurShader::BlurShader()
{
	endPassNum = 1;
	blurCount = 0;
}

BlurShader::~BlurShader()
{
	SAFE_RELEASE(shader);
}

void BlurShader::ShaderReady(RenderInfo * render)
{
	if (shader == nullptr)
	{
		CreateShader("BlurShader.hlsl");
	}

	shader->SetTexture("_map", render->GetTexture());

	if (currentPass == 0)
	{
		shader->SetInt("_blurCount", blurCount);
	}

	shader->SetFloatArray("_uvSize", (float*)&(render->GetRenderUVSize()), 2);
	shader->SetBool("_blendOk", blendOk);
	ShaderBegin();
}