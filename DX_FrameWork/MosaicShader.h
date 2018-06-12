#pragma once

//pass  0:mosaicShader(mosaicSize) 작은모자이크 네모의 사이즈 입력
class MosaicShader final :public Shader
{
public:
	MosaicShader();
	virtual ~MosaicShader();
	virtual void ShaderReady(RenderInfo* render) override;

	void SetMosaicSize(Point size) { assert(size.x && size.y); this->mosaicSize = size; }
private:
	Point mosaicSize;
};