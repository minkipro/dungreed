#include "stdafx.h"

LightShader::LightShader()
{
	endPassNum = 1;
	amount = 0.01f;
}

LightShader::~LightShader()
{
	SAFE_RELEASE(shader);
}

void LightShader::ShaderReady(RenderInfo * render)
{
	if (shader == nullptr)
	{
		CreateShader("LightShader.hlsl");
	}

	Point textureCenterPos = render->GetCenterPos();
	float correctionRadian = render->GetRotationRadian();
	Point correctionLightPos;
	float centerPosToLightPos_distance = GetDistance(textureCenterPos, *lightPos);

	//Rotationº¸Á¤
	if (correctionRadian != 0.0f)
	{
		float centerPosToLightPos_Radian = -atan2f(lightPos->x - textureCenterPos.x, lightPos->y - textureCenterPos.y) + D3DX_PI / 2;

		correctionRadian = centerPosToLightPos_Radian - correctionRadian;
		correctionLightPos = { textureCenterPos.x + cosf(correctionRadian)*centerPosToLightPos_distance,
			textureCenterPos.y + sinf(correctionRadian)*centerPosToLightPos_distance };
	}
	else
	{
		correctionLightPos = *lightPos;
	}

	shader->SetTexture("_map", render->GetTexture());

	switch (currentPass)
	{
	case 0:
		shader->SetFloat("_amount", amount);
		break;
	case 1:
		shader->SetFloat("_range", lightRange);
		shader->SetFloat("_deleteValue", deleteValue);
		break;
	}

	shader->SetFloatArray("_startUV", (float*)&(render->GetStartUV()), 2);
	shader->SetFloatArray("_pixelSize", (float*)&(render->GetUVScale()*(render->GetSize())), 2);
	shader->SetFloatArray("_texturePos", (float*)&(render->GetLTPos()), 2);
	shader->SetFloatArray("_lightPos", (float*)&correctionLightPos, 2);
	shader->SetBool("_blendOk", blendOk);
	ShaderBegin();
}
