#include "stdafx.h"

void CollisionMove(const RECT & player, const RECT & object, LocationInfo & playerInfo)
{
	RECT temp;

	if (IntersectRect(&temp, &player, &object))
	{
		UINT collisionSize_x = temp.right - temp.left;
		UINT collisionSize_y = temp.bottom - temp.top;

		POINT centerPos= GetCenterToRECT(object);

		Point playerPos = Point{ playerInfo.translationVec.x,playerInfo.translationVec.y }+(playerInfo.GetCenterPos());

		if (collisionSize_x < collisionSize_y)
		{
			if (playerPos.x < centerPos.x)
			{
				playerInfo.translationVec.x -= collisionSize_x;
			}
			else
			{
				playerInfo.translationVec.x += collisionSize_x;
			}
		}
		else
		{
			if (playerPos.y < centerPos.y)
			{
				playerInfo.translationVec.y -= collisionSize_y;
			}
			else
			{
				playerInfo.translationVec.y += collisionSize_y;
			}
		}
	}
}
