#pragma once
class Map;

class Cat
{
public:
	Cat();
	~Cat();
	void Update();
	void SetIdle();
	void SetWalk();
	void Jump();
	void SeeRight();
	void SeeLeft();
	void SetRect();
	void Walk();
	void SetPosToBefore(int y);
	void SetMap(Map* map);

	void CollisionCheck();

	RECT rc;

	bool hi;
	bool hello;
private:
	RenderInfo * cat;
	LocationInfo catInfo;
	Point catPos;
	Point tempCatPos;
	Point beforePos;
	Point catVel;
	float speed;
	float gravity;

	Map* map;


private:
	UINT aniState;
	bool isJump;
	Point mousePos;
};