#pragma once
struct Point
{
public:
	Point();
	Point(const Point& point);
	Point(const Size& size);
	Point(float x, float y);
	~Point();

	Point operator+(const Point& point) const;
	Point operator-(const Point& point) const;
	Point operator*(const Point& point) const;
	Point operator*(const float amount) const;
	Point operator/(const Point& point) const;
	Point operator/(const float amount) const;

	bool operator==(const Point& point) const;
	operator POINT()
	{
		POINT temp;
		temp.x = (int)x;
		temp.y = (int)y;
		return temp;
	}

	operator D3DXVECTOR2()
	{
		D3DXVECTOR2 temp;
		temp.x = (float)x;
		temp.y = (float)y;
		return temp;
	}

	bool Equals(const Point& point) const;

	static float Distance(const Point& a, const Point & b);

public:
	float x;
	float y;
};

