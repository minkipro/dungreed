#include "stdafx.h"

LocationInfo::LocationInfo()
{
	centerPos = { 0,0 };
	scaleVec = { 1.0f,1.0f };
	rotationVec = { 0,0,0 };
	translationVec = { 0,0,0 };
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&rotation);
	D3DXMatrixIdentity(&translation);
	D3DXMatrixTranslation(&matCenter, centerPos.x, centerPos.y, world._43);
	D3DXMatrixInverse(&matInvCenter, NULL, &matCenter);
}

void LocationInfo::Update()
{
	D3DXMatrixTranslation(&translation, translationVec.x, translationVec.y, translationVec.z);
	world = scale * rotation * translation;
}

void LocationInfo::SetCenterPos(Point pos)
{
	if (centerPos == pos)
	{
		return;
	}

	centerPos = pos;
	D3DXMatrixTranslation(&matCenter, centerPos.x, centerPos.y, world._43);
	D3DXMatrixInverse(&matInvCenter, NULL, &matCenter);
}

void LocationInfo::SetScale(D3DXVECTOR2 vec)
{
	if (scaleVec == vec)
	{
		return;
	}

	scaleVec = vec;
	D3DXMATRIX matTemp;
	D3DXMatrixScaling(&matTemp, scaleVec.x, scaleVec.y, 1.0f);
	scale = matInvCenter * matTemp * matCenter;
}

void LocationInfo::SetScale(float x, float y)
{
	D3DXVECTOR2 vec = { x, y };
	if (scaleVec == vec)
	{
		return;
	}
	scaleVec = vec;
	D3DXMATRIX matTemp;
	D3DXMatrixScaling(&matTemp, scaleVec.x, scaleVec.y, 1.0f);
	scale = matInvCenter * matTemp * matCenter;
}

void LocationInfo::SetRotation(D3DXVECTOR3 vec)
{
	if (rotationVec == vec)
	{
		return;
	}

	rotationVec = vec;
	D3DXMATRIX matTemp;
	D3DXMatrixRotationYawPitchRoll(&matTemp, rotationVec.y, rotationVec.x, rotationVec.z);
	rotation = matInvCenter * matTemp * matCenter;
}

Point LocationInfo::GetCenterPos()
{

	return centerPos;
}
