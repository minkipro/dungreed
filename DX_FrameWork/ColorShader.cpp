#include "stdafx.h"

ColorShader::ColorShader()
{
	endPassNum = 2;
	color = { 0,0,0,0 };
}

ColorShader::~ColorShader()
{
	SAFE_RELEASE(shader);
}

void ColorShader::ShaderReady(RenderInfo* render)
{
	if (shader == nullptr)
	{
		CreateShader("PixelColorShader.hlsl");
	}

	shader->SetTexture("_map", render->GetTexture());

	if (currentPass != 2)
	{
		shader->SetFloatArray("_color", (float*)color, 4);
	}

	shader->SetBool("_blendOk", blendOk);
	ShaderBegin();
}
