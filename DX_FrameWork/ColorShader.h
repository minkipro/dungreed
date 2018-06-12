#pragma once

//pass  0:color_change(color)  1:color_multiply(color)  2:None Shader
class ColorShader final:public Shader
{
public:
	ColorShader();
	virtual ~ColorShader();
	virtual void ShaderReady(RenderInfo* render) override;

	void SetColor(D3DXCOLOR color) { this->color = color; }
private:
	D3DXCOLOR color;
};