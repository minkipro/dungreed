#pragma once

#define MAPTILENUMX 20
#define MAPTILENUMY 20
#define TOTALMAPTILENUM MAPTILENUMX*MAPTILENUMY

#define TILENUMX 9
#define TILENUMY 10
#define TOTALTILENUM TILENUMX*TILENUMY

#define MAPTILE

class MapEditScene : public SceneMain
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Release();
	virtual void Render();
	void SelectTile();
	void InputTile();

	void SaveMap();

	void LoadMap();

private:
	Tile tile[TOTALTILENUM];
	Tile currentTile;
	Point mousePos;
	Tile mapTile[TOTALMAPTILENUM];
};