#include "stdafx.h"
#include "Size.h"

Size::Size()
{
	width = height = 0.0f;
}

Size::Size(const Size & size)
{
	width = size.width;
	height = size.height;
}

Size::Size(float width, float height)
{
	this->width = width;
	this->height = height;
}

Size::~Size()
{

}

Size Size::operator+(const Size & size) const
{
	return Size(width + size.width, height + size.height);
}

Size Size::operator-(const Size & size) const
{
	return Size(width - size.width, height - size.height);
}

bool Size::Equals(const Size & size) const
{
	return (width == size.width) && (height == size.height);
}

bool Size::Empty() const
{
	return (width == 0.0f) && (height == 0.0f);
}