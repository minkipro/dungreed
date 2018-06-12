#pragma once

class D2Vertex
{
public:
	D2Vertex() {}
	D2Vertex(float x, float y, float u, float v);

	D3DXVECTOR3 position;
	D3DXVECTOR2 uv;

	static DWORD fvf;
};

#ifdef DX2DFRAME
typedef D2Vertex Vertex;
#endif // DX2DFRAME
