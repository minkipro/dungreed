#include "stdafx.h"

MosaicShader::MosaicShader()
{
	mosaicSize = { 10,10 };
}

MosaicShader::~MosaicShader()
{
	SAFE_RELEASE(shader);
}

void MosaicShader::ShaderReady(RenderInfo * render)
{
	if (shader == nullptr)
	{
		CreateShader("MosaicShader.hlsl");
	}

	shader->SetTexture("_map", render->GetTexture());

	shader->SetFloatArray("_mosaicSize", (float*)&(mosaicSize), 2);
	shader->SetFloatArray("_renderSize", (float*)&(render->GetVertexSize()*render->GetUVScale()), 2);
	shader->SetFloatArray("_startUV", (float*)&(render->GetStartUV()), 2);
	shader->SetBool("_blendOk", blendOk);
	ShaderBegin();
}
