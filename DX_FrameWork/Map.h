#pragma once
#include "MapEditScene.h"
class Map
{
public:
	Map();
	~Map();
	void Init();
	void Update();
	void LoadMap();

	Tile mapTile[TOTALMAPTILENUM];
};
