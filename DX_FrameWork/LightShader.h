#pragma once

//pass  0: amount_Light(lightPos,amount)  1: rangeView (lightPos,range,deleteValue)
class LightShader final :public Shader
{
public:
	LightShader();
	virtual ~LightShader() override;
	virtual void ShaderReady(RenderInfo* render) override;

	void SetLightPos(Point* pos) { lightPos = pos; }
	void SetAmount(float value) { amount = value; }
	void SetRange(float value) { lightRange= value; }
	void SetDeleteValue(float value) { deleteValue= value; }
private:
	Point * lightPos;
	float amount;
	float lightRange;
	float deleteValue;
};