#pragma once
struct Tile
{
	Point pos;
	RenderInfo* tile;
	LocationInfo tileInfo;
	UINT frameNum;
	RECT rc;
	bool isMap;
	bool isCollision;
	Tile(){}
	~Tile(){}
	void Init(UINT num, float x = 0, float y = 0)
	{
		frameNum = num;
		pos = { x,y };
		rc = {};
		tile = nullptr;
		isCollision = false;
	}
	void Update()
	{
		if (frameNum == 36)
		{
			isCollision = true;
		}
		tile->SetPosToCenter(&pos);
		tile->SetFrame(frameNum);
		rc = tile->GetRect();
		tile->Update();
	}
	void GetRender()
	{
		tile = NULL;
		GET_RENDER(tile, tileInfo);
		tile->Init({ 50,50 });
		tile->SetImgName("Tile");
	}
};