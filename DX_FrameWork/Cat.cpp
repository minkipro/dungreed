#include "stdafx.h"
#include "Cat.h"

//0. 식빵
//1. 화내기
//2. 울기
//3. 좋아하기
//4. 걷기
//5. 시무룩하기
//6. 뛰기
//7. 점프
//8. 앉기
//9. 서기
//10. 가만히있기

Cat::Cat()
	:aniState(10)
	, catVel({ 0, 0 }), speed(300), isJump(false)
	, gravity(600)
{
	GET_RENDER(cat, catInfo);

	cat->Init();
	cat->SetImgName("cat");
	cat->SetAni("cat10", true);
	cat->SetPosToCenter(&catPos);
	cat->SetBlend(true);
	cat->SetFPS(10);
	cat->SetDynamicAniSize(true);
	catPos = { WIN_WIDTH / 2, WIN_HEIGHT - 400 };
	tempCatPos = catPos;
	beforePos = catPos;
	catInfo.SetScale(2.0f, 2.0f);
	SetRect();
}

Cat::~Cat()
{
}

void Cat::Update()
{
	mousePos = MOUSE->GetPosition();
	Walk();
	
	if ((KEYBOARD->KeyPress(VK_RIGHT) && KEYBOARD->KeyPress(VK_LEFT))
		&&aniState!=7)
	{
 		SetIdle();
	}

	if (KEYBOARD->KeyDown(VK_SPACE))
	{
		Jump();
	}
	catVel.y += gravity * DELTATIME;
	beforePos = catPos;
	catPos = catPos + catVel * DELTATIME;
	SetRect();
	CollisionCheck();
	SetRect();
	cat->Update();
}

void Cat::SetIdle()
{
	if (aniState != 10)
	{
		cat->SetFPS(10);
		cat->SetAni("cat10");
		aniState = 10;
		catVel = {};
	}
}

void Cat::SetWalk()
{
	if (aniState != 4)
	{
		cat->SetFPS(5);
		cat->SetAni("cat4");
		aniState = 4;
	}
}

void Cat::Jump()
{
	if (!isJump)
	{
		cat->SetAni("cat7");
		aniState = 7;
		catVel.y = -600;
		isJump = true;
	}
}


void Cat::SeeRight()
{
	if (!cat->GetReverse_X())
	{
		cat->SetReverse_X(true);
		cat->SetCenterUV(0.3333333f, 0);
		catPos.x += 50;
	}
}

void Cat::SeeLeft()
{
	if (cat->GetReverse_X())
	{
		cat->SetReverse_X(false);
		cat->SetCenterUV(0, 0);
		catPos.x -= 50;
	}
}


void Cat::SetRect()
{
	Point catSize = cat->GetSize();
	rc = { (int)catPos.x, (int)catPos.y, (int)(catPos.x + catSize.x), (int)(catPos.y + catSize.y) };
}

void Cat::Walk()
{
	if (KEYBOARD->KeyDown(VK_RIGHT))
	{
		if (KEYBOARD->KeyDown(VK_LEFT))
		{
			SetIdle();
			catVel = {};
		}
	}

	if (KEYBOARD->KeyPress(VK_LEFT))
	{
		if(aniState==10)
			SetWalk();
		catVel.x = -speed;
	}
	if (KEYBOARD->KeyPress(VK_RIGHT))
	{
		if(aniState==10)
			SetWalk();
		catVel.x = +speed;
	}
}

void Cat::SetPosToBefore(int y)
{
	catPos = beforePos;
	catPos.y = y - (rc.bottom-rc.top);
	beforePos.y = catPos.y;
	SetIdle();
	isJump = false;
}

void Cat::SetMap(Map * map)
{
	this->map = map;
}

void Cat::CollisionCheck()
{
	RECT rect;
	bool isCollision = false;
	UINT tileNum;
	for (int i = 0; i < TOTALMAPTILENUM; i++)
	{
		if (map->mapTile[i].isCollision)
		{
			if (IntersectRect(&rect, &rc, &map->mapTile[i].rc))
			{
				isCollision = true;
				tileNum = i;
				break;
			}
		}
	}
	if (isCollision)
	{
		SetPosToBefore(map->mapTile[tileNum].rc.top);
	}
}
