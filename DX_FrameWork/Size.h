#pragma once

struct Size
{
public:
	Size();
	Size(const Size& size);
	Size(float width, float height);
	~Size();

	Size operator+(const Size& size) const;
	Size operator-(const Size& size) const;
	bool Equals(const Size& size) const;
	bool Empty() const;

public:
	float width;
	float height;
};

