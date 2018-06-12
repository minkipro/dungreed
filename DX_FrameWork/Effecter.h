#pragma once

#define MAXEFFECT 20

//struct EFFECT
//{
//	RenderInfo* render;
//	LocationInfo info;
//	Point pos;
//	bool isTextureSize;
//
//	EFFECT()
//	{
//		render = TEXTUREMG->GetRenderInfo(info);
//		render->Init();
//		render->SetBlend(true);
//		isTextureSize = false;
//	}
//
//	~EFFECT()
//	{
//		delete render;
//	}
//};
//
//
//class Effecter
//{
//public:
//	Effecter();
//	~Effecter();
//
//	void Update();
//	void PlayEffect(string textureName, string effectName, Point pos, Point size = { 0,0 }, UINT fps=15);
//	void SetView(D3DXMATRIX* view);
//	void OffAllEffect();
//
//private:
//	EFFECT * effect;
//	D3DXMATRIX* view;
//	vector<EFFECT*> playList;
//	vector<EFFECT*> stayList;
//};