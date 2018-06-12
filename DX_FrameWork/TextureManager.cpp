#include "stdafx.h"

TextureManager* TextureManager::instance;

TextureManager::TextureManager()
{
	BaseMatrixSet();
}

TextureManager::~TextureManager()
{
	for (auto iter1 : textureList)
	{
		SAFE_DELETE(iter1.second);
	}

	for (int i = renderInfo.size() - 1; i > 0; i = renderInfo.size() - 1)
	{
		renderInfo[i]->~RenderInfo();
	}

	for (auto iter1 : fontList)
	{
		SAFE_DELETE(iter1);
	}
}

void TextureManager::LoadTextureToFolder(string folderName, string extension)
{
	_finddata_t fd;

	long handle;
	int result = 1;
	string fileName;
	string keyName;

	fileName = folderName + "\\*.";
	fileName += extension + "*";
	handle = _findfirst(fileName.c_str(), &fd);
	assert(handle != -1);

	fileName = fd.name;

	while (result != -1)
	{

		for (int i = 0; i < fileName.size(); i++)
		{
			if (fileName[i] == '.')
			{
				break;
			}

			assert(fileName[i]);
			keyName += fileName[i];
		}

		TEXTURE* temp = new TEXTURE(folderName + "/" + fd.name);
		LoadTextureInfo(folderName, keyName, temp);
		temp->folderName = folderName;
		textureList.insert({ keyName,temp });
		keyName.clear();
		result = _findnext(handle, &fd);
		fileName = fd.name;
	}
}

void TextureManager::SaveTextureInfo(string imgName)
{
	iter = textureList.find(imgName);
	assert(iter != textureList.end());

	XmlDocument* document = new XmlDocument;

	XMLNode* node = document->NewElement("TextureAtlas");
	XmlElement* element = nullptr;

	Point size;
	size.x = iter->second->info.Width;
	size.y = iter->second->info.Height;

	for (UINT i = 0; i < iter->second->frameList.size(); i++)
	{
		element = document->NewElement((iter->first + to_string(i)).c_str());
		element->SetAttribute("x", (int)(iter->second->frameList[i].LTuv.x*size.x));
		element->SetAttribute("y", (int)(iter->second->frameList[i].LTuv.y*size.y));
		element->SetAttribute("w", (int)(iter->second->frameList[i].frameSize.x));
		element->SetAttribute("h", (int)(iter->second->frameList[i].frameSize.y));

		node->InsertEndChild(element);
	}

	document->InsertFirstChild(node);

	node = document->NewElement("AniList");
	string frameNumList;
	for (auto aniIter = iter->second->aniList.begin(); aniIter != iter->second->aniList.end(); aniIter++)
	{
		element = document->NewElement(aniIter->first.c_str());

		for (UINT i = 0; i < aniIter->second.size(); i++)
		{
			frameNumList += to_string(aniIter->second[i]);
			frameNumList += ".";
		}

		element->SetAttribute("frameNum", frameNumList.c_str());
		node->InsertEndChild(element);
		frameNumList.clear();
	}

	document->InsertEndChild(node);

	document->SaveFile((iter->second->folderName + "/" + imgName + ".xml").c_str());
	SAFE_DELETE(document);
}

void TextureManager::LoadTextureInfo(string folderName, string imgName, TEXTURE* texture)
{
	XmlDocument* document = new XmlDocument;
	document->LoadFile((folderName + "/" + imgName + ".xml").c_str());

	if (document->Error())
	{
		return;
	}

	XmlElement* list;
	XmlElement* element;

	list = document->FirstChildElement("TextureAtlas");
	element = list->FirstChildElement();

	TEXTUREFRAME temp;
	Point LT;
	Point RB;
	Point size;
	size.x = texture->info.Width;
	size.y = texture->info.Height;

	for (; element != NULL; element = element->NextSiblingElement())
	{
		LT.x = element->IntAttribute("x");
		LT.y = element->IntAttribute("y");
		temp.frameSize.x = element->IntAttribute("w");
		temp.frameSize.y = element->IntAttribute("h");

		RB.x = LT.x + temp.frameSize.x;
		RB.y = LT.y + temp.frameSize.y;

		LT = LT / size;
		RB = RB / size;

		temp.LTuv = LT;
		temp.RBuv = RB;

		texture->frameList.push_back(temp);
	}

	list = list->NextSiblingElement();

	if (list == NULL)
	{
		return;
	}

	element = list->FirstChildElement();

	if (element == NULL)
	{
		return;
	}

	string aniName;
	string aniNumList;
	string aniNum;
	vector<UINT> frameList;
	for (; element != NULL; element = element->NextSiblingElement())
	{
		aniName = element->Name();
		aniNumList = element->Attribute("frameNum");

		for (UINT i = 0; aniNumList[i] != NULL; i++)
		{
			if (aniNumList[i] == '.')
			{
				frameList.push_back(atoi(aniNum.c_str()));
				aniNum.clear();
			}
			else
			{
				aniNum += aniNumList[i];
			}
		}

		texture->aniList.insert({ aniName,frameList });
		frameList.clear();
	}

	SAFE_DELETE(document);
}

void TextureManager::BaseMatrixSet()
{
	D3DXMatrixIdentity(&projection);
	DEVICE->SetFVF(Vertex::fvf);

	D3DVIEWPORT9 viewPort;
	DEVICE->GetViewport(&viewPort);

	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, viewPort.Width, viewPort.Height, 0.0f, -1.0f, 1.0f);
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}


void TextureManager::Update()
{
	if (spotPoint != nullptr)
	{
		mainView.translationVec.x = (-spotPoint->x  - spotSize.x / 2) * mainView.scaleVec.x + WIN_WIDTH / 2;
		mainView.translationVec.y = (-spotPoint->y  - spotSize.y / 2) * mainView.scaleVec.y + WIN_HEIGHT / 2;
	}

	mainView.Update();
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(string name)
{
	auto it = textureList.find(name);
	assert(it != textureList.end());

	return it->second->texture;
}

void TextureManager::AddFrame(string imgName, TEXTUREFRAME frameUV)
{
	assert(textureList.size());
	iter = textureList.find(imgName);
	assert(iter != textureList.end());

	iter->second->frameList.push_back(frameUV);
}

void TextureManager::AddFrame(string imgName, int frameX, int frameY)
{
	assert(textureList.size());
	iter = textureList.find(imgName);
	assert(iter != textureList.end());

	D3DXVECTOR2 uvSize = { 1.0f / frameX,1.0f / frameY };

	for (int i = 0; i < frameY; i++)
	{
		for (int j = 0; j < frameX; j++)
		{
			TEXTUREFRAME frame;
			D3DXVECTOR2 uv;
			uv.x = uvSize.x*j;
			uv.y = uvSize.y*i;
			frame.LTuv = uv;
			uv.x = uvSize.x*j + uvSize.x;
			uv.y = uvSize.y*i + uvSize.y;
			frame.RBuv = uv;

			iter->second->frameList.push_back(frame);
		}
	}
}

void TextureManager::AddAnimation(string imgName, string aniName, UINT startFrame, UINT endFrame)
{
	assert(textureList.size());
	iter = textureList.find(imgName);
	assert(iter != textureList.end());
	assert(iter->second->frameList.size() > startFrame&&
		iter->second->frameList.size() > endFrame);

	vector<UINT> frameNumList;

	if (startFrame <= endFrame)
	{
		for (UINT i = startFrame; i <= endFrame; i++)
		{
			frameNumList.push_back(i);
		}
	}
	else
	{
		for (UINT i = endFrame; i >= startFrame; i--)
		{
			frameNumList.push_back(i);
		}
	}

	assert(frameNumList.size());

	iter->second->aniList.insert({ aniName,frameNumList });
}

void TextureManager::CameraSetSpotPoint(Point * pos, Point size)
{
	assert(pos);
	spotPoint = pos;
	spotSize = size;
	mainView.translationVec.x = (-spotPoint->x - spotSize.x / 2) * mainView.scaleVec.x + WIN_WIDTH / 2;
	mainView.translationVec.y = (-spotPoint->y - spotSize.y / 2) * mainView.scaleVec.y + WIN_HEIGHT / 2;

	mainView.Update();
}

void TextureManager::SetMainViewScale(D3DXVECTOR2 scale)
{
	mainView.SetScale(scale);
	mainView.Update();
}


void TextureManager::CameraFree()
{
	spotPoint = nullptr;
	spotSize = { 0,0 };
}

RenderInfo * TextureManager::GetRenderInfo(LocationInfo& localInfo)
{
	RenderInfo* temp = new RenderInfo{ &localInfo, renderInfo.size() };
	renderInfo.push_back(temp);
	return renderInfo.back();
}

RenderInfo * TextureManager::CopyRenderInfo(RenderInfo* renderInfo, LocationInfo& localInfo)
{
	assert(renderInfo);
	assert(renderInfo->buffer.GetByteSize());
	RenderInfo* temp = new RenderInfo{ &localInfo, this->renderInfo.size() };
	temp->buffer = renderInfo->buffer;
	this->renderInfo.push_back(temp);

	temp->SetImgName(renderInfo->keyname);
	temp->SetBlend(renderInfo->blendOk);
	temp->SetView(renderInfo->myView);
	temp->SetRender(renderInfo->renderOk);
	return temp;
}

Font * TextureManager::GetFont(string fontName, Point size)
{
	wstring name;
	name.assign(fontName.begin(), fontName.end());
	Font* temp = new Font(name, size, fontList.size());

	fontList.push_back(temp);
	return temp;
}

void TextureManager::AddSceneRender(string sceneName)
{
	renderIter = renderList.find(sceneName);
	assert(renderIter == renderList.end()); //중복된 씬 네임 입력

	renderList.insert({ sceneName, SceneRender() });
	renderIter = renderList.find(sceneName);

	fontRenderList.insert({ sceneName, SceneRender() });
	fontIter = fontRenderList.find(sceneName);
}

void TextureManager::SelectSceneRender(string sceneName)
{
	renderIter = renderList.find(sceneName);
	fontIter = fontRenderList.find(sceneName);

	assert(renderIter != renderList.end());
	assert(fontIter != fontRenderList.end());
}

void TextureManager::Render(string sceneName)
{
	if (currentSceneName != sceneName)
	{
		renderIter = renderList.find(sceneName);
		fontIter = fontRenderList.find(sceneName);
		assert(renderIter != renderList.end());
		currentSceneName = sceneName;
	}

	DEVICE->SetStreamSource(0, VertexBuffer::GetVertex(), 0, sizeof(Vertex));

	for (UINT i = 0; i < renderIter->second.size(); i++)
	{
		renderInfo[renderIter->second[i]]->Render();
	}

	for (UINT i = 0; i < fontIter->second.size(); i++)
	{
		fontList[fontIter->second[i]]->Render();
	}
}


TextureManager * TextureManager::Get()
{
	if (instance == nullptr)
	{
		instance = new TextureManager;
	}

	return instance;
}



