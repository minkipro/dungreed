#pragma once

#define SOURCEEDITMODE 1
#define CURRECTRANGE 5

enum RE_EDITMODE
{
	ONEFRAME,
	ARRFRAME,
	X_SET_FRAME,
	EDIT_ADDANI,
};

enum RE_CURRECTMODE
{
	NONE_CURRECT,
	UP_LINE,
	DOWN_LINE,
	SIDE_LINE,
};


class TextureEditer
{
public:
	TextureEditer();
	~TextureEditer();
	void Update();
	void Render();

	void SubViewControl();
	void FrameButtonSetting();
	void SaveTextureInfo();

private:
	void EditModeTextOut();
	void RenderIndexUpdate(UINT value);
	D3DXVECTOR2 GetUV(Point pos);
	Point GetPos(D3DXVECTOR2 uv);
	void ViewMove();
	void DrawRect(Point sPos, Point ePos);

#pragma region
	void OneFrameAdd();
	void ArrFrameAdd();
	void XSetFrameAdd();
	RE_CURRECTMODE CheckCurrectMode();
	void CurrectLine();

	void ChangeImg();
	int IndexCheck();
	void FrameSave();

	void ArrFrameRender();
	void XSetFrameRender();

	void MouseRender();
	void ImageFrameRender();
#pragma endregion AddFrame Func

#pragma region
	void AniEdit();
	void AniEditViewMove();
	void AniEditButtonSetting();
	void ButtonClear();

	void AniEditRender();

	void AddAnimation(string aniname, UINT arr[], UINT arrSize);
	//void AddAnimation(string aniname, UINT sIndex, UINT eIndex);

#pragma endregion AddAni Func

private:

	RE_EDITMODE state;
	RE_CURRECTMODE currect;
	UINT currectLine;

	RenderInfo* render;
	vector<RenderInfo*> frameList;
	LocationInfo info;
	D3DXMATRIX editerView;

	RenderInfo* subView;
	LocationInfo subViewInfo;

	bool isPick;
	UINT arrSize;
	float renderIndex;
	TEXTUREFRAME pickFrame;
	Point pickPos;
	vector<TEXTUREFRAME> pickList;
	int setXheight;

	TCHAR str[50];
	map<string, TEXTURE*>::iterator it;

	D3DXMATRIX frameButtonView;
	D3DXMATRIX aniButtonView;
	vector<UINT> aniIndexTemp;
	vector<Button*> aniIndexButton;
	vector<Button*> aniButtonList;
	vector<Button*> frameButtonList;
	int sIndex;
	int eIndex;
	bool isIndexPick;
};