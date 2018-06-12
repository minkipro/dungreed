#include "stdafx.h"

TriVertex::TriVertex()
{

}

TriVertex::~TriVertex()
{

}

void TriVertex::Init(Vertex * benchmark, Vertex * pos1, Vertex * pos2)
{
	assert(benchmark);
	assert(pos1);
	assert(pos2);

	vertex[0] = *benchmark;
	vertex[1] = *pos1;
	vertex[2] = *pos2;

	if (!ForwardDirCheck(pos1, pos2))
	{
		vertex[1].position = pos2->position;
		vertex[2].position = pos1->position;
	}

}

bool TriVertex::ForwardDirCheck(Vertex* pos1, Vertex* pos2) const
{

	float dir1 = -atan2f(pos1->position.x - vertex[0].position.x,
		pos1->position.y - vertex[0].position.y) + Math::PI / 2;
	float dir2 = -atan2f(pos2->position.x - vertex[0].position.x,
		pos2->position.y - vertex[0].position.y) + Math::PI / 2;
	float dir3;

	if (dir1 < 0)
	{
		dir1 += Math::PI * 2;
	}
	else if (dir1 >= Math::PI * 2)
	{
		dir1 -= Math::PI * 2;
	}

	if (dir2 < 0)
	{
		dir2 += Math::PI * 2;
	}
	else if (dir2 >= Math::PI * 2)
	{
		dir2 -= Math::PI * 2;
	}

	dir3 = fabs(dir1 - dir2);

	if (dir2 > dir1)
	{

		if (dir3 > Math::PI)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (dir3 > Math::PI)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
