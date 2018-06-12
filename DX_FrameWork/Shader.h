#pragma once

class RenderInfo;

//��� HLSL �ȼ� ���̴��� ��� bool�� _blendOk ������ ������ �־����
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