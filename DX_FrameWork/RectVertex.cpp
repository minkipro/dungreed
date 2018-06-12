#include "stdafx.h"

void RectVertex::Init(Point size, D3DXVECTOR2 startUV, D3DXVECTOR2 endUV)
{
	Vertex LT(0.0f, 0.0f, startUV.x, startUV.y);
	Vertex RT(size.x, 0.0f, endUV.x, startUV.y);
	Vertex RB(size.x, size.y, endUV.x, endUV.y);
	Vertex LB(0.0f, size.y, startUV.x, endUV.y);

	vertex[0].Init(&LT, &RT, &RB);
	vertex[1].Init(&LT, &RB, &LB);
}
