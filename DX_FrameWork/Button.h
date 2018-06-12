#pragma once

enum BUTTONSTATE
{
	BT_UP,
	BT_DOWN
};

enum BUTTONTYPE
{
	BT_NOMAL,
	BT_STAY,
	BT_ANIMATION,
	BT_IMGPART,
};

class Button
{
public:
	Button();
	~Button();
	//NOMAL
	void Init(string textureName, string downTextrueName, Point size, Point pos, CALL_FUNC func, D3DXMATRIX* view=nullptr);	
	//STAY
	void Init(string textureName, Point size, Point pos, CALL_FUNC func, CALL_FUNC func2, D3DXMATRIX* view = nullptr);
	//IMG_PART
	void Init(string textureName, UINT upFrame, UINT downFrame,Point size, Point pos, CALL_FUNC func, D3DXMATRIX* view = nullptr);
	//ANI
	void Init(string textureName, string aniName, UINT upFrame, Point size, Point pos, CALL_FUNC func, D3DXMATRIX* view = nullptr);

	void Update();
	void SetActive(bool active);
	bool GetActive() { return active; }

	void ChangeTexture(string textureName);
	void SetUpState() { state = BT_UP; }
	void SetPos(Point pos);
	BUTTONSTATE GetButtonState() { return state; }
	string GetName() { return upImgkey; }
	Point GetPos() { return Point{ info.translationVec.x,info.translationVec.y }; }
private:
	void SettingButtonRender(Point size, Point pos, D3DXMATRIX* view);
	
private:
	bool active=true;
	BUTTONSTATE state;
	BUTTONTYPE type;

	UINT upFrame;
	UINT downFrame;
	string upImgkey;
	string downImgkey;
	string aniName;
	RECT rect;

	Font* font;
	RenderInfo* render;
	LocationInfo info;

	CALL_FUNC callbackFunction;
	CALL_FUNC callbackFunction2;
};