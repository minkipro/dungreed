#pragma once

class LocationInfo;

inline float GetDistance(Point pos1, Point pos2)
{
	float x = pos1.x - pos2.x;
	float y = pos1.y - pos2.y;

	return (float)sqrt((x*x) + (y*y));
}

inline POINT GetCenterToRECT(const RECT &rect)
{
	POINT size = { rect.right - rect.left,rect.bottom - rect.top };

	return { rect.left + size.x,rect.top + size.y };
}

void CollisionMove(const RECT &player, const RECT &object, LocationInfo& playerInfo);