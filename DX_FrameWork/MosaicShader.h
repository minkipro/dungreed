#pragma once

//pass  0:mosaicShader(mosaicSize) ����������ũ �׸��� ������ �Է�
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