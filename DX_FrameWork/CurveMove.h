#pragma once
class Animal;
class CurveMove : public AnimalAI
{
public:
	CurveMove();
	CurveMove(Animal* animal);

	virtual void Update();
};