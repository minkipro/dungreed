#pragma once

//pass  0: nomal blur(blurCount)  1: GaussianBlur
class BlurShader final :public Shader
{
public:
	BlurShader();
	virtual ~BlurShader() override;
	virtual void ShaderReady(RenderInfo* render) override;

	void SetBlurCount(UINT count) { blurCount = count; }

private:
	UINT blurCount;
};