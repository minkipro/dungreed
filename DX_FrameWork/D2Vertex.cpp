#include "stdafx.h"

#ifdef DX2DFRAME
DWORD D2Vertex::fvf = D3DFVF_XYZ | D3DFVF_TEX1;
typedef D2Vertex Vertex;
#endif // DX2DFRAME

D2Vertex::D2Vertex(float x, float y, float u, float v)
{
	position = { x,y,0 };
	uv = { u,v };
}