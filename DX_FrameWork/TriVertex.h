#pragma once

class TriVertex
{
public:
	TriVertex();
	~TriVertex();

	void Init(Vertex* benchmark, Vertex* pos1, Vertex* pos2);

private:
	Vertex vertex[3];

private:
	bool ForwardDirCheck(Vertex* pos1, Vertex* pos2) const;
};