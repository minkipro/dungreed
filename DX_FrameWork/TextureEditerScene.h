#pragma once

class TextureEditerScene :public SceneMain
{
public:
	TextureEditerScene();

	void Init() override;
	void Update() override;
	void Release() override;
	void Render() override;

private:
	TextureEditer * editer;
};