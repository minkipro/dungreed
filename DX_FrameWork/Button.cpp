#include "stdafx.h"

Button::Button()
{
	upFrame = 0;
	downFrame = 0;
	type = BT_NOMAL;
	font = nullptr;

	render = TEXTUREMANAGER->GetRenderInfo(info);
	render->Init();
	render->SetDynamicAniSize(false);
}

Button::~Button()
{
	SAFE_DELETE(render);
}

void Button::Init(string textureName, string downTextrueName, Point size, Point pos, CALL_FUNC func, D3DXMATRIX* view)
{
	upImgkey = textureName;
	downImgkey = downTextrueName;
	callbackFunction = func;
	state = BT_UP;
	type = BT_NOMAL;

	SettingButtonRender(size, pos, view);
}

void Button::Init(string textureName, Point size, Point pos, CALL_FUNC func, CALL_FUNC func2, D3DXMATRIX * view)
{
	upImgkey = textureName;
	callbackFunction = func;
	callbackFunction2 = func2;
	state = BT_UP;
	type = BT_STAY;

	SettingButtonRender(size, pos, view);

	font = TEXTUREMANAGER->GetFont("±Ã¼­Ã¼", Point{ 15,15 });
	font->SetText(upImgkey);
	font->SetPos(pos + render->GetViewPos());
	font->SetActive(true);
}

void Button::Init(string textureName, UINT upFrame, UINT downFrame, Point size, Point pos, CALL_FUNC func, D3DXMATRIX* view)
{
	upImgkey = textureName;
	callbackFunction = func;
	this->upFrame = upFrame;
	this->downFrame = downFrame;
	state = BT_UP;
	type = BT_IMGPART;
	
	SettingButtonRender(size, pos, view);

	render->SetFrame(upFrame);
}

void Button::Init(string textureName, string aniName, UINT upFrame, Point size, Point pos, CALL_FUNC func, D3DXMATRIX* view)
{
	upImgkey = textureName;
	callbackFunction = func;
	this->upFrame = upFrame;
	this->aniName = aniName;
	state = BT_UP;
	type = BT_ANIMATION;

	SettingButtonRender(size, pos, view);

	render->SetFrame(upFrame);
}

void Button::Update()
{
	if (!active)
	{
		return;
	}

	switch (state)
	{
	case BT_UP:
		if (PtInRect(&rect, MOUSE->GetPosition()-render->GetViewPos()))
		{
			if (KEYBOARD->KeyDown(VK_LBUTTON))
			{
				switch (type)
				{
				case BT_NOMAL:
					render->SetImgName(downImgkey);
					info.SetScale(info.scaleVec * 0.9f);
					break;
				case BT_STAY:
					callbackFunction();
					info.SetScale(info.scaleVec * 0.9f);
					break;
				case BT_ANIMATION:
					render->SetAni(aniName);
					break;
				case BT_IMGPART:
					render->SetFrame(downFrame);
					break;
				default:
					break;
				}
				state = BT_DOWN;
			}
		}
		break;
	case BT_DOWN:
		if (callbackFunction != nullptr&&type != BT_STAY)
		{
			if (!PtInRect(&rect, MOUSE->GetPosition()-render->GetViewPos()))
			{
				state = BT_UP;
			}
			else
			{
				if (KEYBOARD->KeyUp(VK_LBUTTON))
				{
					callbackFunction();
					state = BT_UP;
				}
			}
		}
		else
		{

			if (PtInRect(&rect, MOUSE->GetPosition()-render->GetViewPos()))
			{
				if (KEYBOARD->KeyUp(VK_RBUTTON))
				{
					state = BT_UP;
				}
			}
		}

		if (state == BT_UP)
		{
			switch (type)
			{
			case BT_NOMAL:
				render->SetImgName(upImgkey);
				info.SetScale(info.scaleVec*1.1111111f);
				break;
			case BT_STAY:
				callbackFunction2();
				info.SetScale(info.scaleVec*1.1111111f);
				break;
			case BT_ANIMATION:
				render->SetFrame(upFrame);
				break;
			case BT_IMGPART:
				render->SetFrame(upFrame);
				break;
			default:
				break;
			}
		}

		break;
	}

	render->Update();
}

void Button::SetActive(bool active)
{
	render->SetRender(active);
	this->active = active;

	if (font != nullptr)
	{
		font->SetActive(active);
	}
}

void Button::ChangeTexture(string textureName)
{
	render->SetImgName(textureName);
	upImgkey = textureName;
}

void Button::SetPos(Point pos)
{
	info.translationVec.x = pos.x;
	info.translationVec.y = pos.y;

	rect = render->GetRect();
}

void Button::SettingButtonRender(Point size, Point pos, D3DXMATRIX* view)
{
	if (view == nullptr)
	{
		render->SetMainView();
	}
	else
	{
		render->SetView(view);
	}

	render->Init(size, view);
	render->SetImgName(upImgkey);
	render->SetCenterUV({ 0.5f,0.5f });
	render->Update();
	render->SetBlend(true);
	render->SetPosToCenter(pos);

	rect = render->GetRect();

	SetActive(true);
	render->Update();
}
