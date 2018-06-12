#include "stdafx.h"

DWORD D2LineVertex::fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;
vector<D2LineVertex> D2LineVertex::lineList;

D2LineVertex::D2LineVertex(float x, float y, DWORD color, float z)
{
	position = { x,y,z };
	this->color = color;
}
