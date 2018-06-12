#include "stdafx.h"

TextureEditer::TextureEditer()
{
	assert(TEXTUREMANAGER->textureList.size());
	it = TEXTUREMANAGER->textureList.begin();
	arrSize = 1;
	sIndex = 0;
	eIndex = 0;
	setXheight = 10;
	isIndexPick = false;
	renderIndex = 0.0f;
	isPick = false;
	state = ONEFRAME;
	currect = NONE_CURRECT;
	currectLine = 0;

	D3DXMatrixIdentity(&frameButtonView);
	D3DXMatrixIdentity(&aniButtonView);
	D3DXMatrixIdentity(&editerView);

	render = TEXTUREMANAGER->GetRenderInfo(info);
	render->SetImgName(it->first);
	render->Init();
	render->SetBlend(false);
	D3DXVECTOR2 scale;
	scale.x = it->second->info.Width / 100.0f;
	scale.y = it->second->info.Height / 100.0f;
	info.SetScale(scale);
	subView = TEXTUREMANAGER->GetRenderInfo(subViewInfo);
	subView->SetImgName(it->first);
	subView->Init();
}

TextureEditer::~TextureEditer()
{
	for (auto iter : aniButtonList)
	{
		delete iter;
	}

	for (auto iter : frameButtonList)
	{
		delete iter;
	}

	for (auto iter : aniIndexButton)
	{
		delete iter;
	}
}

void TextureEditer::Update()
{
	ChangeImg();
	ViewMove();

	if (state == EDIT_ADDANI)
	{
		AniEdit();

		if (KEYBOARD->KeyDown(VK_CAPITAL))
		{
			ButtonClear();
			state = ONEFRAME;
			frameButtonView._42 = 0;
			aniButtonView._41 = 0;
		}

		for (auto it : aniButtonList)
		{
			it->Update();
		}

		for (auto it : frameButtonList)
		{
			it->Update();
		}

		for (auto it : aniIndexButton)
		{
			it->Update();
		}
	}
	else
	{
		if (!isPick)
		{
			if (KEYBOARD->KeyDown(VK_LBUTTON))
			{
				renderIndex = 0.0f;
				pickFrame.LTuv = GetUV(MOUSE->GetPosition());
				setXheight = 10;
				isPick = true;
				pickPos = { MOUSE->GetPosition().x + info.translationVec.x,MOUSE->GetPosition().y + info.translationVec.y };
			}

			if (KEYBOARD->KeyDown(VK_CAPITAL))
			{
				int num = (int)state;
				num++;
				state = (RE_EDITMODE)num;

				if (state == EDIT_ADDANI)
				{
					render->SetRender(false);
					AniEditButtonSetting();
				}
				else
				{
					render->SetRender(true);
				}

			}

			if (KEYBOARD->KeyDown(VK_BACK))
			{
				if (it->second->frameList.size() != 0)
				{
					it->second->frameList.pop_back();
					delete frameButtonList.back();
					frameButtonList.pop_back();
				}
			}
		}
		else
		{
			switch (state)
			{
			case ONEFRAME:
				OneFrameAdd();
				break;
			case ARRFRAME:
				ArrFrameAdd();
				break;
			case X_SET_FRAME:
				XSetFrameAdd();
				break;
			}

			DrawRect(Point{ pickPos.x - info.translationVec.x,pickPos.y - info.translationVec.y }, MOUSE->GetPosition());
		}

		FrameButtonSetting();
	}

	if (KEYBOARD->KeyPress(VK_CONTROL))
	{
		if (KEYBOARD->KeyDown('S'))
		{
			SaveTextureInfo();
		}
	}

	render->Update();
	SubViewControl();

	subViewInfo.translationVec.x = MOUSE->GetPosition().x;
	subViewInfo.translationVec.y = MOUSE->GetPosition().y;
	subView->Update();
}

void TextureEditer::Render()
{

}

void TextureEditer::SubViewControl()
{
	if (isPick)
	{
		pickFrame.RBuv = GetUV(MOUSE->GetPosition());

		subView->SetRender(true);
		switch (state)
		{
		case ONEFRAME:
			subView->GetBuffer()->ChangeUV(pickFrame);
			break;
		case ARRFRAME:
		{
			RenderIndexUpdate(arrSize);

			float arrWidth, arrHeight;
			arrWidth = pickFrame.RBuv.x - pickFrame.LTuv.x;
			arrHeight = pickFrame.RBuv.y - pickFrame.LTuv.y;
			TEXTUREFRAME temp;
			UINT renderNum = (UINT)renderIndex;

			if (arrWidth*it->second->info.Width >= arrHeight * it->second->info.Height)
			{
				temp.LTuv = pickFrame.LTuv;
				temp.LTuv.x += arrWidth * renderNum / arrSize;
				temp.RBuv.x = temp.LTuv.x + arrWidth / arrSize;
				temp.RBuv.y = pickFrame.RBuv.y;
			}
			else
			{
				temp.LTuv = pickFrame.LTuv;
				temp.LTuv.y += arrHeight * renderNum / arrSize;
				temp.RBuv.x = pickFrame.RBuv.x;
				temp.RBuv.y = temp.LTuv.y + arrHeight / arrSize;
			}

			subView->GetBuffer()->ChangeUV(temp);
		}
		break;
		case X_SET_FRAME:
			break;
		case EDIT_ADDANI:
			break;
		default:
			break;
		}
	}
	else
	{
		subView->SetRender(false);
	}
}

void TextureEditer::FrameButtonSetting()
{
	for (UINT i = frameButtonList.size(); i < it->second->frameList.size(); i++)
	{
		Button*temp = new Button;
		temp->Init(it->first, i, i, Point{ 50,50 },
			Point{ (float)(WIN_WIDTH - 500 + (i % 10) * 50),(float)(100 + (i / 10) * 50) }, nullptr);
		frameButtonList.push_back(temp);
	}

	for (UINT i = 0; i < frameButtonList.size(); i++)
	{
		frameButtonList[i]->Update();
	}
}

void TextureEditer::SaveTextureInfo()
{
	TEXTUREMANAGER->SaveTextureInfo(it->first);
}

void TextureEditer::EditModeTextOut()
{
}

void TextureEditer::RenderIndexUpdate(UINT value)
{
	renderIndex += DELTATIME * 5;

	if (renderIndex >= value)
	{
		renderIndex = 0;
	}
}

D3DXVECTOR2 TextureEditer::GetUV(Point pos)
{
	D3DXVECTOR2 uv;
	uv.x = (pos.x - info.translationVec.x) / it->second->info.Width;
	uv.y = (pos.y - info.translationVec.y) / it->second->info.Height;

	return uv;
}

Point TextureEditer::GetPos(D3DXVECTOR2 uv)
{
	Point pos;
	pos.x = uv.x * it->second->info.Width;
	pos.y = uv.y * it->second->info.Height;

	return pos;
}

void TextureEditer::ViewMove()
{
	if (KEYBOARD->KeyPress(VK_RIGHT))
	{
		info.translationVec.x -= 300*DELTATIME;
	}

	if (KEYBOARD->KeyPress(VK_LEFT))
	{
		info.translationVec.x += 300*DELTATIME;

	}

	if (KEYBOARD->KeyPress(VK_UP))
	{
		info.translationVec.y += 300*DELTATIME;
	}

	if (KEYBOARD->KeyPress(VK_DOWN))
	{
		info.translationVec.y -= 300*DELTATIME;
	}
}

void TextureEditer::DrawRect(Point sPos, Point ePos)
{
	//Vertex vertex[5];

	//D3DXMATRIX temp;
	//D3DXMatrixIdentity(&temp);
	//DEVICE->SetTransform(D3DTS_WORLD, &temp);
	//LPDIRECT3DVERTEXBUFFER9 buffer;
	//vertex[0] = { sPos.x,sPos.y,0.0f,0.0f };
	//vertex[1] = { ePos.x,sPos.y,0.0f,0.0f };
	//vertex[2] = { ePos.x,ePos.y,0.0f,0.0f };
	//vertex[3] = { sPos.x,ePos.y,0.0f,0.0f };
	//vertex[4] = { sPos.x,sPos.y,0.0f,0.0f };

	//DEVICE->CreateVertexBuffer(sizeof(vertex), 0,
	//	Vertex::fvf, D3DPOOL_DEFAULT, &buffer, NULL);
	//void* bufferPointer;
	//buffer->Lock(0, sizeof(vertex), &bufferPointer, 0);
	//memcpy(bufferPointer, vertex, sizeof(vertex));
	//buffer->Unlock();
	//DEVICE->SetStreamSource(0, buffer, 0, sizeof(Vertex));
	//DEVICE->DrawPrimitive(D3DPT_LINESTRIP, 0, 4);

	//buffer->Release();
}

void TextureEditer::OneFrameAdd()
{
	if (KEYBOARD->KeyDown(VK_RBUTTON))
	{
		isPick = false;
		pickFrame.ZeroSet();
	}

	if (KEYBOARD->KeyDown(VK_LBUTTON))
	{
		it->second->frameList.push_back(pickFrame);
		pickFrame.ZeroSet();

		isPick = false;
	}
}

void TextureEditer::ArrFrameAdd()
{
	if (KEYBOARD->KeyDown('Z'))
	{
		arrSize--;
		if (arrSize < 1)
		{
			arrSize = 1;
		}
	}
	else if (KEYBOARD->KeyDown('X'))
	{
		arrSize++;
	}

	if (KEYBOARD->KeyDown(VK_RBUTTON))
	{
		isPick = false;
		arrSize = 1;
		pickFrame.ZeroSet();
	}

	if (KEYBOARD->KeyDown(VK_LBUTTON))
	{
		float arrWidth, arrHeight;
		arrWidth = pickFrame.RBuv.x - pickFrame.LTuv.x;
		arrHeight = pickFrame.RBuv.y - pickFrame.LTuv.y;

		TEXTUREFRAME temp;
		for (int i = 0; i < arrSize; i++)
		{
			if (arrWidth*it->second->info.Width >= arrHeight * it->second->info.Height)
			{
				temp.LTuv = pickFrame.LTuv;
				temp.LTuv.x += arrWidth * i / arrSize;
				temp.RBuv.x = temp.LTuv.x + arrWidth / arrSize;
				temp.RBuv.y = pickFrame.RBuv.y;
				it->second->frameList.push_back(temp);
			}
			else
			{
				temp.LTuv = pickFrame.LTuv;
				temp.LTuv.y += arrHeight * i / arrSize;
				temp.RBuv.x = pickFrame.RBuv.x;
				temp.RBuv.y = temp.LTuv.y + arrHeight / arrSize;
				it->second->frameList.push_back(temp);
			}
		}

		pickFrame.ZeroSet();
		isPick = false;
		arrSize = 1;
	}
}

void TextureEditer::XSetFrameAdd()
{
}

RE_CURRECTMODE TextureEditer::CheckCurrectMode()
{
	return RE_CURRECTMODE();
}

void TextureEditer::CurrectLine()
{
}

void TextureEditer::ChangeImg()
{
	if (KEYBOARD->KeyDown(VK_TAB))
	{
		ButtonClear();

		info.translationVec.x = 0;
		info.translationVec.y = 0;

		it++;

		if (it == TEXTUREMANAGER->textureList.end())
		{
			it = TEXTUREMANAGER->textureList.begin();

		}

		render->SetImgName(it->first);
		D3DXVECTOR2 scale;
		scale.x = it->second->info.Width / 100.0f;
		scale.y = it->second->info.Height / 100.0f;
		info.SetScale(scale);
		subView->SetImgName(it->first);

		if (state == EDIT_ADDANI)
		{
			AniEditButtonSetting();
			render->SetRender(false);
		}

		isPick = false;
		sIndex = 0;
		eIndex = 0;
	}

}

int TextureEditer::IndexCheck()
{
	return 0;
}

void TextureEditer::FrameSave()
{
}

void TextureEditer::ArrFrameRender()
{
}

void TextureEditer::XSetFrameRender()
{
}

void TextureEditer::MouseRender()
{
}

void TextureEditer::ImageFrameRender()
{
}

void TextureEditer::AniEdit()
{
	if (KEYBOARD->KeyDown(VK_BACK))
	{
		if (aniIndexTemp.size())
		{
			aniIndexTemp.pop_back();

			for (UINT i = aniIndexButton.size() - 1; i >= 0; i--)
			{
				if (aniIndexButton[i]->GetActive())
				{
					aniIndexButton[i]->SetActive(false);
					break;
				}
			}
		}
	}

	if (KEYBOARD->KeyDown(VK_SPACE))
	{
		if (aniIndexTemp.size())
		{
			for (UINT i = 0; i < aniIndexButton.size(); i++)
			{
				aniIndexButton[i]->SetActive(false);
			}

			vector<UINT> indexlist;

			for (UINT i = 0; i < aniIndexTemp.size(); i++)
			{
				indexlist.push_back(aniIndexTemp[i]);
			}
			string keynameTemp;
			keynameTemp = it->first;
			char listNum[20];
			_itoa_s((UINT)it->second->aniList.size(), listNum, 10);
			keynameTemp += listNum;
			it->second->aniList.insert({ keynameTemp, indexlist });
			Button* button = new Button;
			button->Init(it->first, keynameTemp, aniIndexTemp[0], Point{ 70,70 },
				Point{ (float)aniButtonList.size() * 80 + 50,(float)(WIN_HEIGHT - 100) }, nullptr, &aniButtonView);
			aniButtonList.push_back(button);
			aniIndexTemp.clear();
		}
	}

	AniEditViewMove();

	for (int i = 0; i < frameButtonList.size(); i++)
	{
		if (frameButtonList[i]->GetButtonState() == BT_DOWN)
		{
			aniIndexTemp.push_back(i);
			frameButtonList[i]->SetUpState();

			for (int j = 0; j < aniIndexButton.size(); j++)
			{
				if (!aniIndexButton[j]->GetActive())
				{
					aniIndexButton[j]->Init(it->first, i, i, Point{ 50,50 },
						Point{ (float)(WIN_WIDTH - 500 + (j % 10) * 50),
						(float)(100 + (j / 10) * 50) }, nullptr);

					return;
				}
			}

			Button*temp = new Button;
			temp->Init(it->first, i, i, Point{ 50,50 },
				Point{ (float)(WIN_WIDTH - 500 + (aniIndexButton.size() % 10) * 50),
				(float)(100 + (aniIndexButton.size() / 10) * 50) }, nullptr);
			aniIndexButton.push_back(temp);
			return;
		}
	}
}

void TextureEditer::AniEditViewMove()
{
	if (KEYBOARD->KeyPress('W'))
	{
		if (frameButtonView._42 > 0)
		{
			frameButtonView._42 -= 5;
		}
	}

	if (KEYBOARD->KeyPress('S'))
	{

		frameButtonView._42 += 5;
	}

	if (KEYBOARD->KeyPress('A'))
	{
		if (aniButtonView._41 > 0)
		{
			aniButtonView._41 -= 5;
		}
	}

	if (KEYBOARD->KeyPress('D'))
	{
		aniButtonView._41 += 5;
	}
}

void TextureEditer::AniEditButtonSetting()
{
	ButtonClear();

	for (int i = 0; i < it->second->frameList.size() / 10 + 1; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (j + i * 10 < it->second->frameList.size())
			{
				if (j + i * 10 < frameButtonList.size())
				{
					frameButtonList[j + i * 10]->Init(it->first, j + i * 10, j + i * 10, Point{ 50,50 },
						Point{ (float)(j * 60 + 100),(float)(i * 60 + 100) }, nullptr, &frameButtonView);
				}
				else
				{
					Button *temp = new Button;
					temp->Init(it->first, j + i * 10, j + i * 10, Point{ 50,50 },
						Point{ (float)(j * 60 + 100),(float)(i * 60 + 100) }, nullptr, &frameButtonView);
					frameButtonList.push_back(temp);
				}
			}
		}
	}

	auto aniIter = it->second->aniList.begin();
	for (UINT i = 0; i < it->second->aniList.size(); i++)
	{
		if (aniIter == it->second->aniList.end())
		{
			return;
		}

		if (i < aniButtonList.size())
		{
			aniButtonList[i]->Init(it->first, aniIter->first, aniIter->second[0],
				Point{ 70,70 }, Point{ (float)i * 80 + 50,WIN_HEIGHT - 100 }, nullptr, &aniButtonView);
		}
		else
		{
			Button *temp = new Button;
			temp->Init(it->first, aniIter->first, aniIter->second[0],
				Point{ 70,70 }, Point{ (float)i * 80 + 50,WIN_HEIGHT - 100 }, nullptr, &aniButtonView);
			aniButtonList.push_back(temp);
		}

		aniIter++;
	}
}

void TextureEditer::ButtonClear()
{
	for (int i = 0; i < aniButtonList.size(); i++)
	{
		aniButtonList[i]->SetActive(false);
	}

	for (int i = 0; i < frameButtonList.size(); i++)
	{
		frameButtonList[i]->SetActive(false);
	}

	for (int i = 0; i < aniIndexButton.size(); i++)
	{
		aniIndexButton[i]->SetActive(false);
	}
}

void TextureEditer::AniEditRender()
{

	RenderIndexUpdate(aniIndexTemp.size());


	if (aniIndexTemp.size())
	{
		UINT tempIndex = (UINT)renderIndex;


		for (int i = 0; i < aniIndexTemp.size() / 3 + 1; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (aniIndexTemp.size() > j + i * 3)
				{
					//BITMAPMG->Animation(it->first, POINT{ WINWIDTH - 200 + j * 50, i * 50 + 150 }, 45, 45, aniIndexTemp[j + i * 3]);
				}
			}
		}
	}

}

void TextureEditer::AddAnimation(string aniname, UINT arr[], UINT arrSize)
{
}


