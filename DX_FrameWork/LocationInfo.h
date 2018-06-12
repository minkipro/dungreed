#pragma once

//SRT SRT SRT SRT SRT SRT SRT SRT SRT SRT

class LocationInfo
{
public:
	LocationInfo();
	void SetScale(D3DXVECTOR2 vec);
	void SetScale(float x, float y);
	void SetRotation(D3DXVECTOR3 vec);
	D3DXMATRIX* GetWorldMatrix() { return &world; }
	Point GetCenterPos();

	D3DXVECTOR3 translationVec;
	D3DXVECTOR3 rotationVec;
	D3DXVECTOR2 scaleVec;

	friend class RenderInfo;
	friend class TextureManager;
private:
	void Update();
	void SetCenterPos(Point pos);

private:
	D3DXMATRIX world;
	D3DXMATRIX scale;
	D3DXMATRIX rotation;
	D3DXMATRIX translation;

	Point centerPos;
	D3DXMATRIX matCenter;
	D3DXMATRIX matInvCenter;
};