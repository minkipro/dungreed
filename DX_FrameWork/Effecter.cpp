#include "stdafx.h"

//Effecter::Effecter()
//{
//	effect = new EFFECT[MAXEFFECT];
//
//	for (UINT i = 0; i < MAXEFFECT; i++)
//	{
//		stayList.push_back(&effect[i]);
//	}
//
//	view = nullptr;
//}
//
//Effecter::~Effecter()
//{
//	delete[] effect;
//}
//
//void Effecter::Update()
//{
//	for (vector<EFFECT*>::iterator it = playList.begin(); it != playList.end(); it++)
//	{
//		if ((*it)->isTextureSize)
//		{
//			Point textureSize = (*it)->render->GetSizeToTextureAni();
//			(*it)->info.SetScale({ textureSize.x / 100,textureSize.y / 100 });
//			(*it)->info.SetCenterPos(textureSize / 2);
//			(*it)->info.translationVec.x = (*it)->pos.x - (*it)->render->GetSize().x / 2;
//			(*it)->info.translationVec.y = (*it)->pos.y - (*it)->render->GetSize().y / 2;
//		}
//
//		(*it)->info.Update();
//
//		if (!(*it)->render->GetRenderState())
//		{
//			stayList.push_back(*it);
//			it = playList.erase(it);
//		}
//	}
//}
//
//void Effecter::PlayEffect(string textureName, string effectName, Point pos, Point size, UINT fps)
//{
//	assert(stayList.size()); // 이펙트 한도 초과
//
//	stayList.back()->render->SetImgName(textureName);
//	stayList.back()->render->SetFPS(fps);
//
//	if (view != nullptr)
//	{
//		stayList.back()->render->SetView(view);
//	}
//	else
//	{
//		stayList.back()->render->SetMainView();
//	}
//
//	stayList.back()->render->SetAni(effectName, false, true);
//
//	if (size.x == 0 && size.y == 0)
//	{
//		Point textureSize = stayList.back()->render->GetSizeToTextureAni();
//		stayList.back()->info.SetScale({ textureSize.x / 100,textureSize.y / 100 });
//		stayList.back()->info.SetCenterPos(textureSize / 2);
//		stayList.back()->isTextureSize = true;
//		stayList.back()->pos = pos;
//	}
//	else
//	{
//		stayList.back()->info.SetScale({ size.x / 100,size.y / 100 });
//		stayList.back()->info.SetCenterPos(size / 2);
//		stayList.back()->isTextureSize = false;
//	}
//
//	stayList.back()->info.translationVec.x = pos.x - stayList.back()->render->GetSize().x / 2;
//	stayList.back()->info.translationVec.y = pos.y - stayList.back()->render->GetSize().y / 2;
//	stayList.back()->info.Update();
//
//	playList.push_back(stayList.back());
//	stayList.pop_back();
//}
//
//void Effecter::SetView(D3DXMATRIX * view)
//{
//	this->view = view;
//}
//
//void Effecter::OffAllEffect()
//{
//	for (vector<EFFECT*>::iterator it = playList.begin(); it != playList.end(); it++)
//	{
//		stayList.push_back(*it);
//		(*it)->render->SetRender(false);
//		it = playList.erase(it);
//	}
//}
