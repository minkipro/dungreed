#pragma once

class RenderInfo;

//모든 HLSL 픽셀 쉐이더는 모두 bool형 _blendOk 변수를 가지고 있어야함
class Shader
{
public:
	Shader();
	virtual ~Shader();

	virtual void ShaderReady(RenderInfo* render) = 0;
	virtual void ShaderEnd();

	void SetBlend(bool blend);
	void SelectPass(UINT num);

protected:
	void CreateShader(string fileName);
	void ShaderBegin();

protected:
	UINT currentPass;
	UINT endPassNum;
	bool blendOk;
	LPD3DXEFFECT shader;
};