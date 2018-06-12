#pragma once


class RectVertex
{
public:
	
	void Init(Point size, D3DXVECTOR2 startUV, D3DXVECTOR2 endUV);

private:
	TriVertex vertex[2];
};