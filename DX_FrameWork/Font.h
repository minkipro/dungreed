#pragma once

class Font
{
public:
	void SetText(string text);
	void SetPos(Point pos);
	void SetColor(D3DCOLOR color);
	void SetActive(bool trueORfalse);

	friend class TextureManager;
private:
	Font() {}
	Font(wstring fontName, Point size, UINT idNum);
	~Font();
	void Render();

private:
	UINT idNum;
	bool active;
	LPD3DXFONT font;
	wstring str;
	RECT rect;
	D3DXFONT_DESC desc = {0};
	D3DCOLOR color;
};