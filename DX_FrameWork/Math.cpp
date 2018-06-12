#include "stdafx.h"
const float Math::PI = 3.14159265f;

int Math::RandomRange(int r1, int r2)
{
	return (int)(rand() % (r2 - r1 + 1)) + r1;
}

float Math::DegreeToRadian(float degree)
{
	return degree * PI / 180.0f;
}

float Math::RadianToDegree(float radian)
{
	return radian * 180.0f / PI;
}
