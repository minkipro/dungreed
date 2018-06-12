#pragma once


class RenderInfo
{
public:
	~RenderInfo();
	void Init(Point size = { 100,100 }, D3DXMATRIX* view = nullptr, 
		D3DXVECTOR2 startUV = { 0.0f,0.0f }, D3DXVECTOR2 endUV = { 1.0f,1.0f },bool dynamic = true);
	void Update();

	void SetImgName(string name);
	void SetRender(bool trueORfalse);
	void SetRenderSize(Point size, D3DXVECTOR2 startUV = { 0.0f,0.0f }, D3DXVECTOR2 endUV = { 1.0f,1.0f });
	void SetBlend(bool trueORfalse);
	void SetAni(string aniName, bool loop = true,bool effect = false);
	void SetDynamicAniSize(bool dynamic) { dynamicAniSize = dynamic; }
	void SetCenterUV(Point uv) { centerUV = uv; }
	void SetCenterUV(float u, float v) { centerUV = { u, v }; }
	void SetFrame(UINT num);
	void SetFrame(TEXTUREFRAME frame);
	void SetFPS(float fps) { frameUpdateSec = 1.0f / fps; }
	void SetView(D3DXMATRIX* view) { myView = view; }
	void SetMainView();
	void SetPosToCenter(Point* pos) { benchmarkPos = pos; }
	void SetPosToCenter(Point pos);
	void SetReverse_X(bool reverse_x) { this->reverse_x = reverse_x; }
	void SetReverse_Y(bool reverse_y) { this->reverse_y = reverse_y; }
	bool GetReverse_X() { return reverse_x; }


	bool GetAniState() { return isPlay; }

	D3DXIMAGE_INFO GetTextureInfo() { return iter->second->info; }
	LPDIRECT3DTEXTURE9 GetTexture() { return iter->second->texture; }
	const LocationInfo* GetLocationInfo() { return info; }
	Point GetUV(Point pos);
	Point GetVertexSize() { return size; }
	Point GetSize();
	Point GetUVSize();
	Point GetRenderUVSize();
	Point GetUVScale();
	Point GetSizeToTextureAni();
	Point GetCenterPos();
	Point GetLTPos();
	D3DXVECTOR2 GetStartUV();
	float GetRotationRadian() { return info->rotationVec.z; }
	bool GetRenderState() { return renderOk; }
	bool IsAniRenderer() { return isAniRenderer; }

	Point GetViewPos() { return Point{ myView->_41,myView->_42 }; }
	Point GetWindowPos();
	string GetName() { return iter->first; }

	RECT GetRect();
	VertexBuffer* GetBuffer() { return &buffer; }
	UINT GetID() { return idNum; }

	void SetShader(Shader* shader) { this->shader = shader; }

private:
	friend class TextureManager;
	friend class Shader;
	RenderInfo(LocationInfo* info, UINT idNum);
	RenderInfo() {}
	void Render();
	void SearchImg(string key);

	void IndexControl();

private:
	map<string, TEXTURE*>::iterator iter;
	VertexBuffer buffer;
	Point size;
	Point centerUV;
	Point* benchmarkPos;
	LocationInfo* info;
	D3DXMATRIX* myView;
	string keyname;
	bool renderOk;
	bool blendOk;
	UINT idNum;

	map<string, vector<UINT>>::iterator aniIter;
	string selectAniName;
	vector<UINT>* selectAni;
	float frameUpdateSec;
	float elapsedSec;
	int indexImg;
	bool isPlay;
	bool isLoop;
	bool isEffect;
	bool isAniRenderer;
	bool dynamicAniSize;
	bool reverse_x;
	bool reverse_y;

	Shader* shader;
};