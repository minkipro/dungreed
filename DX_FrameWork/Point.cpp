#include "stdafx.h"

Point::Point()
{
	x = y = 0.0f;
}

Point::Point(const Point & point)
{
	x = point.x;
	y = point.y;
}

Point::Point(const Size & size)
{
	x = size.width;
	y = size.height;
}

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

Point::~Point()
{
}

Point Point::operator+(const Point & point) const
{
	return Point(x + point.x, y + point.y);
}

Point Point::operator-(const Point & point) const
{
	return Point(x - point.x, y - point.y);
}

Point Point::operator*(const Point & point) const
{
	return Point(x * point.x, y * point.y);
}

Point Point::operator*(const float amount) const
{
	return Point(x * amount, y * amount);
}

Point Point::operator/(const Point & point) const
{
	return Point(x / point.x, y / point.y);
}

Point Point::operator/(const float amount) const
{
	return Point(x / amount, y / amount);
}


bool Point::operator==(const Point & point) const
{
	return (this->x == point.x&&this->y == point.y);
}

bool Point::Equals(const Point & point) const
{
	return (x == point.x) && (y == point.y);
}

float Point::Distance(const Point & a, const Point & b)
{
	float x = fabs(a.x - b.x);
	float y = fabs(a.y - b.y);

	return sqrt(pow(x, 2) + pow(y, 2));
}