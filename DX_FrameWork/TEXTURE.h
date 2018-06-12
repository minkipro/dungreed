#pragma once

struct TEXTUREFRAME
{
	void ZeroSet()
	{
		LTuv = { 0,0 };
		RBuv = { 0,0 };
	}

	D3DXVECTOR2 LTuv;
	D3DXVECTOR2 RBuv;
	Point frameSize;
};

struct TEXTURE
{
	TEXTURE(string name)
	{
		wstring temp;
		temp.assign(name.begin(), name.end());
		D3DXCreateTextureFromFileEx(DEVICE, temp.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2, 1, NULL,
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE, D3DX_FILTER_NONE,
			0xffffffff, &info, NULL, &texture);
	}

	~TEXTURE()
	{
		SAFE_RELEASE(texture);
	}

	map<string, vector<UINT>> aniList;
	vector<TEXTUREFRAME> frameList;
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO info;
	string folderName;
	DWORD deleteColor;
};