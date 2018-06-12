#include "stdafx.h"

void Font::SetText(string text)
{
	str.assign(text.begin(), text.end());
	rect.right = rect.left + desc.Weight*str.size();
}

void Font::SetPos(Point pos)
{
	rect.left = pos.x;
	rect.top = pos.y;
	rect.right = pos.x + desc.Weight*str.size();
	rect.bottom = pos.y + desc.Height;
}

void Font::SetColor(D3DCOLOR color)
{
	this->color = color;
}

void Font::SetActive(bool trueORfalse)
{
	if (active == trueORfalse)
	{
		return;
	}

	if (trueORfalse)
	{
		TEXTUREMANAGER->fontIter = TEXTUREMANAGER->fontRenderList.find(SCENEMANAGER->GetSceneName());
		TEXTUREMANAGER->fontIter->second.push_back(idNum);
		active = true;
	}
	else
	{
		for (auto it = TEXTUREMANAGER->fontRenderList.begin(); it != TEXTUREMANAGER->fontRenderList.end(); it++)
		{
			for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
			{
				if (idNum == *it2)
				{
					it->second.erase(it2);
					active = false;
					break;
				}
			}
		}
	}
}

Font::Font(wstring fontName, Point size, UINT idNum)
{
	SAFE_RELEASE(font);

	desc.Weight = size.x;
	desc.Height = size.y;
	desc.CharSet = ANSI_CHARSET;
	wcscpy_s(desc.FaceName, fontName.c_str());
	D3DXCreateFontIndirect(DEVICE, &desc, &font);
	
	this->idNum = idNum;
	SetPos({ 0,0 });
	color = 0xff000000;
	active = false;
}

Font::~Font()
{
	SAFE_RELEASE(font);
}

void Font::Render()
{
	assert(font);

	if (active)
	{
		font->DrawText(NULL, str.c_str(), -1, &rect, DT_LEFT, color);
	}
}
