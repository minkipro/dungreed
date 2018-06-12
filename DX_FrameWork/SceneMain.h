#pragma once

class SceneMain
{
public:
	SceneMain() {}
	virtual ~SceneMain() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Release() = 0;
	virtual void Render() = 0;

	virtual void* GetSTLAddress(int num) { assert(false); return nullptr; }

protected:

};