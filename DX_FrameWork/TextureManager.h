#pragma once

class TextureManager
{
public:
	static TextureManager* Get();
	TextureManager();
	~TextureManager();
	void LoadTextureToFolder(string folderName, string extension);
	void SaveTextureInfo(string imgName);
	void LoadTextureInfo(string folderName, string imgName, TEXTURE* texture);
	void BaseMatrixSet();

	void Update();
	LPDIRECT3DTEXTURE9 GetTexture(string name);
	void AddFrame(string imgName, TEXTUREFRAME frameUV);
	void AddFrame(string imgName, int frameX, int frameY);

	void AddAnimation(string imgName, string aniName,UINT startFrame, UINT endFrame);

	void CameraSetSpotPoint(Point* pos, Point size = { 0.0f,0.0f });
	void SetMainViewScale(D3DXVECTOR2 scale);
	void CameraFree();
	Point GetMainViewPos() { return { mainView.translationVec.x,mainView.translationVec.y }; }
	Point GetMainViewScale() { return { mainView.scaleVec.x,mainView.scaleVec.y }; }

	RenderInfo* GetRenderInfo(LocationInfo& localInfo);
	RenderInfo* CopyRenderInfo(RenderInfo* renderInfo, LocationInfo& localInfo);

	Font* GetFont(string fontName,Point size);
	
	void AddSceneRender(string sceneName);
	void SelectSceneRender(string sceneName);
	void Render(string sceneName);

	friend class RenderInfo;
	friend class TextureEditer;
	friend class Font;
private:
	static TextureManager * instance;

	map<string, TEXTURE*> textureList;
	map<string, TEXTURE*>::iterator iter;
	D3DXMATRIX projection;
	LocationInfo mainView;

	Point* spotPoint;
	Point spotSize;

	typedef vector<UINT> SceneRender;
	string currentSceneName;

	vector<RenderInfo*> renderInfo;
	map<string, SceneRender> renderList;
	map<string, SceneRender>::iterator renderIter;

	vector<Font*> fontList;
	map<string, SceneRender> fontRenderList;
	map<string, SceneRender>::iterator fontIter;
};