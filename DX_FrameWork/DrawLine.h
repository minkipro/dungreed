#pragma once

struct D2LineVertex
{
	static DWORD fvf;
	static vector<D2LineVertex> lineList;

	D3DXVECTOR3 position;
	DWORD color;

	D2LineVertex() {}
	D2LineVertex(float x, float y, DWORD color, float z);
};

inline void DrawLine(Point pos1, Point pos2, D3DXMATRIX& world, D3DXMATRIX& view, DWORD color = 0, float z=-0.1f)
{
	D2LineVertex vertex[2];
	vertex[0] = { pos1.x,pos1.y,color,z };
	vertex[1] = { pos2.x,pos2.y,color,z };

	DEVICE->SetFVF(D2LineVertex::fvf);
	DEVICE->SetTexture(0, nullptr);
	DEVICE->SetTransform(D3DTS_VIEW, &view);
	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, vertex, sizeof(D2LineVertex));

	DEVICE->SetFVF(Vertex::fvf);
}

inline void DrawRect(Point LT, Point RB, D3DXMATRIX& world, D3DXMATRIX& view, DWORD color = 0, float z = -0.1f)
{
	D2LineVertex vertex[5];
	vertex[0] = { LT.x,LT.y,color,z };
	vertex[1] = { RB.x,LT.y,color,z };
	vertex[2] = { RB.x,RB.y,color,z };
	vertex[3] = { LT.x,RB.y,color,z };
	vertex[4] = { LT.x,LT.y,color,z };

	DEVICE->SetFVF(D2LineVertex::fvf);
	DEVICE->SetTexture(0, nullptr);
	DEVICE->SetTransform(D3DTS_VIEW, &view);
	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, vertex, sizeof(D2LineVertex));

	DEVICE->SetFVF(Vertex::fvf);
}