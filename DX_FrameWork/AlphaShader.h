#pragma once

//pass  0:alpha_shader(alpha)
class AlphaShader final :public Shader
{
public:
	AlphaShader();
	virtual ~AlphaShader();
	virtual void ShaderReady(RenderInfo* render) override;

	void SetAlpha(float alpha) { this->alpha = alpha; }
private:
	float alpha;
};