#include "stdafx.h"

RenderInfo::RenderInfo(LocationInfo* info, UINT idNum)
{
	this->idNum = idNum;
	renderOk = false;
	this->info = info;
	centerUV = { 0,0 };
	blendOk = true;
	indexImg = 0;
	isPlay = false;
	selectAniName = " ";
	isAniRenderer = false;
	dynamicAniSize = true;
	frameUpdateSec = 1.0f / 20;
	benchmarkPos = nullptr;
}

RenderInfo::~RenderInfo()
{
	SetRender(false);

	for (vector<RenderInfo*>::iterator it = TEXTUREMANAGER->renderInfo.begin();
		it != TEXTUREMANAGER->renderInfo.end(); it++)
	{
		if (*it == this)
		{
			TEXTUREMANAGER->renderInfo.erase(it);
			return;
		}
	}
}

void RenderInfo::Init(Point size, D3DXMATRIX* view,
	D3DXVECTOR2 startUV, D3DXVECTOR2 endUV, bool dynamic)
{
	isAniRenderer = false;
	this->size = size;
	RectVertex temp;
	temp.Init(size, startUV, endUV);

	if (buffer.GetRenderMemory() == nullptr)
	{
		buffer.Init(&temp, sizeof(temp), dynamic);
	}
	else
	{
		buffer.ChangeVertex(&temp, sizeof(temp), dynamic);
	}

	myView = view;

	if (myView == nullptr)
	{
		myView = TEXTUREMANAGER->mainView.GetWorldMatrix();
	}
}

void RenderInfo::Update()
{
	IndexControl();

	info->SetCenterPos({ size.x*centerUV.x,size.y*centerUV.y });

	if (reverse_x)
	{
		info->SetScale({ -abs(info->scaleVec.x),info->scaleVec.y });
	}
	else
	{
		info->SetScale({ abs(info->scaleVec.x),info->scaleVec.y });
	}

	if (reverse_y)
	{
		info->SetScale({ info->scaleVec.x ,-abs(info->scaleVec.y) });
	}
	else
	{
		info->SetScale({ info->scaleVec.x ,abs(info->scaleVec.y) });
	}

	if (benchmarkPos)
	{
		info->translationVec.x = benchmarkPos->x - info->centerPos.x;
		info->translationVec.y = benchmarkPos->y - info->centerPos.y;

		if (reverse_x)
		{
			info->translationVec.x += size.x*(1.0f - centerUV.x*2);
		}

		if (reverse_y)
		{
			info->translationVec.y += size.y*(1.0f - centerUV.y*2);
		}
	}

	info->Update();
}

void RenderInfo::Render()
{
	assert(buffer.GetVertex()); //Init ¾ÈµÆÀ½
	assert(keyname.size());  //SetImageName ¾ÈµÆÀ½

	SearchImg(keyname);

	DEVICE->SetTransform(D3DTS_VIEW, myView);
	DEVICE->SetTransform(D3DTS_WORLD, &info->world);

	if (shader)
	{
		shader->SetBlend(blendOk);
		shader->ShaderReady(this);
		DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST,
			buffer.GetStartByte() / sizeof(Vertex), 2);
		shader->ShaderEnd();
	}
	else
	{
		DEVICE->SetTexture(0, iter->second->texture);

		if (blendOk)
		{
			DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, buffer.GetStartByte() / sizeof(Vertex), 2);
			DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}
		else
		{
			DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, buffer.GetStartByte() / sizeof(Vertex), 2);
		}
	}
}

void RenderInfo::SetImgName(string name)
{
	SearchImg(name);
	SetRender(true);
}

void RenderInfo::SetRender(bool trueORfalse)
{
	if (renderOk == trueORfalse)
	{
		return;
	}

	if (trueORfalse)
	{
		TEXTUREMANAGER->renderIter->second.push_back(idNum);
		renderOk = true;
	}
	else
	{
		for (auto it = TEXTUREMANAGER->renderList.begin(); it != TEXTUREMANAGER->renderList.end(); it++)
		{
			for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
			{
				if (idNum == *it2)
				{
					it->second.erase(it2);
					renderOk = false;
					break;
				}
			}
		}
	}
}

void RenderInfo::SetRenderSize(Point size, D3DXVECTOR2 startUV, D3DXVECTOR2 endUV)
{
	this->size = size;
	RectVertex temp;
	temp.Init(size, startUV, endUV);

	buffer.ChangeVertex(&temp, sizeof(temp));
}

void RenderInfo::SetBlend(bool trueORfalse)
{
	blendOk = trueORfalse;
}

void RenderInfo::SetAni(string aniName, bool loop, bool effect)
{
	assert(keyname.size());

	if (selectAniName != aniName)
	{
		aniIter = iter->second->aniList.find(aniName);
		assert(aniIter != iter->second->aniList.end());
		selectAniName = aniName;
		indexImg = 0;
		elapsedSec = 0;

		selectAni = &aniIter->second;
		isPlay = true;
	}
	else
	{
		indexImg = 0;
		elapsedSec = 0;
		selectAni = &aniIter->second;
		isPlay = true;
	}

	assert(selectAni->size());

	if (dynamicAniSize)
	{
		SetRenderSize(GetSizeToTextureAni(), iter->second->frameList[(*selectAni)[indexImg]].LTuv,
			iter->second->frameList[(*selectAni)[indexImg]].RBuv);
	}
	else
	{
		buffer.ChangeUV(iter->second->frameList[(*selectAni)[indexImg]]);
	}

	isPlay = true;
	this->isLoop = loop;
	this->isEffect = effect;
	isAniRenderer = true;
	SetRender(true);
}

void RenderInfo::SetFrame(UINT num)
{
	assert(iter->second->frameList.size() > num);
	isPlay = false;
	buffer.ChangeUV(iter->second->frameList[num]);
	SetRender(true);
}

void RenderInfo::SetFrame(TEXTUREFRAME frame)
{
	buffer.ChangeUV(frame);
}

void RenderInfo::SetMainView()
{
	myView = TEXTUREMANAGER->mainView.GetWorldMatrix();
}

void RenderInfo::SetPosToCenter(Point pos)
{
	info->translationVec.x = pos.x - info->centerPos.x;
	info->translationVec.y = pos.y - info->centerPos.y;

	if (reverse_x)
	{
		info->translationVec.x += size.x*(1.0f - centerUV.x*2);
	}

	if (reverse_y)
	{
		info->translationVec.y += size.y*(1.0f - centerUV.y*2);
	}
}

Point RenderInfo::GetUV(Point pos)
{
	Point uv;
	uv.x = pos.x / iter->second->info.Width;
	uv.y = pos.y / iter->second->info.Height;

	return uv;
}

Point RenderInfo::GetSize()
{
	return Point{ size.x*(info->scaleVec.x),
		size.y*(info->scaleVec.y) };
}

Point RenderInfo::GetUVSize()
{
	return Point{ 1.0f / size.x, 1.0f / size.y };
}

Point RenderInfo::GetRenderUVSize()
{
	return Point{ 1.0f / (size.x*info->scaleVec.x*myView->_11), 1.0f / (size.y*info->scaleVec.y*myView->_22) };
}

Point RenderInfo::GetUVScale()
{
	if (isAniRenderer)
	{
		D3DXVECTOR2 aniUVScale = (iter->second->frameList[(*selectAni)[indexImg]].RBuv -
			iter->second->frameList[(*selectAni)[indexImg]].LTuv);
		return Point{ 1.0f / aniUVScale.x, 1.0f / aniUVScale.y };
	}

	return { 1.0f,1.0f };
}

Point RenderInfo::GetSizeToTextureAni()
{
	assert(selectAni != nullptr);

	return iter->second->frameList[(*selectAni)[indexImg]].frameSize;
}

Point RenderInfo::GetCenterPos()
{
	return Point(info->translationVec.x + info->centerPos.x,
		info->translationVec.y + info->centerPos.y);
}

Point RenderInfo::GetLTPos()
{
	Point realSize = GetSize();

	return { info->translationVec.x - (realSize.x - size.x) * (info->centerPos.x / size.x) ,
		info->translationVec.y - (realSize.y - size.y)  * (info->centerPos.y / size.y) };
}

D3DXVECTOR2 RenderInfo::GetStartUV()
{
	if (isAniRenderer)
	{
		return iter->second->frameList[(*selectAni)[indexImg]].LTuv;
	}

	return { 0.0f,0.0f };
}

Point RenderInfo::GetWindowPos()
{
	Point pos;

	pos.x = info->translationVec.x + myView->_41 + (info->centerPos.x*info->scaleVec.x);
	pos.y = info->translationVec.y + myView->_42 + (info->centerPos.y*info->scaleVec.y);

	return pos;
}

RECT RenderInfo::GetRect()
{
	RECT rect;
	Point realSize = GetSize();

	if (realSize.x < 0)
	{
		rect.right = info->translationVec.x - (realSize.x - size.x) * (info->centerPos.x / size.x);
		rect.left = rect.right + realSize.x;
	}
	else
	{
		rect.left = info->translationVec.x - (realSize.x - size.x) * (info->centerPos.x / size.x);
		rect.right = rect.left + realSize.x;
	}

	if (realSize.y < 0)
	{
		rect.bottom = info->translationVec.y - (realSize.y - size.y)* (info->centerPos.y / size.y);
		rect.top = rect.bottom + realSize.y;
	}
	else
	{
		rect.top = info->translationVec.y - (realSize.y - size.y)* (info->centerPos.y / size.y);
		rect.bottom = rect.top + realSize.y;
	}

	return rect;
}

void RenderInfo::SearchImg(string key)
{
	assert(TEXTUREMANAGER->textureList.size());
	if (keyname != key)
	{
		keyname = key;
		iter = TEXTUREMANAGER->textureList.find(key);
		assert(iter != TEXTUREMANAGER->textureList.end());
	}
	else
	{
		return;
	}
}

void RenderInfo::IndexControl()
{
	if (!isPlay)
	{
		return;
	}

	float elapsedtime = TIMER->GetElapsedTime();

	if (elapsedtime > 0)
	{
		elapsedSec += elapsedtime;
	}

	if (elapsedSec >= frameUpdateSec)
	{
		elapsedSec -= frameUpdateSec;
		indexImg++;

		if (indexImg < selectAni->size())
		{
			if (dynamicAniSize)
			{
				SetRenderSize(GetSizeToTextureAni(), iter->second->frameList[(*selectAni)[indexImg]].LTuv,
					iter->second->frameList[(*selectAni)[indexImg]].RBuv);
			}
			else
			{
				buffer.ChangeUV(iter->second->frameList[(*selectAni)[indexImg]]);
			}
		}
	}

	if (selectAni->size() == indexImg)
	{
		if (!isLoop)
		{
			indexImg--;
			isPlay = false;

			if (isEffect)
			{
				SetRender(false);
			}
		}
		else
		{
			indexImg = 0;

			if (dynamicAniSize)
			{
				SetRenderSize(GetSizeToTextureAni(), iter->second->frameList[(*selectAni)[indexImg]].LTuv,
					iter->second->frameList[(*selectAni)[indexImg]].RBuv);
			}
			else
			{
				buffer.ChangeUV(iter->second->frameList[(*selectAni)[indexImg]]);
			}
		}
	}
}
