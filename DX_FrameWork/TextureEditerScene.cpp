#include "stdafx.h"

TextureEditerScene::TextureEditerScene()
{
	
}

void TextureEditerScene::Init()
{
	editer = new TextureEditer;
}

void TextureEditerScene::Update()
{
	editer->Update();
}

void TextureEditerScene::Release()
{
	delete editer;
}

void TextureEditerScene::Render()
{
	editer->Render();
}
