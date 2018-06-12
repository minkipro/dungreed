#pragma once

struct TEXTUREFRAME;

class VertexBuffer
{
public:
	VertexBuffer();

	void Init(void* memory, UINT byteSize, bool dynamic=true);
	void Release();
	void ChangeVertex(void* memory, UINT byteSize, bool dynamic=true);
	void ChangeUV(TEXTUREFRAME uv);

	static LPDIRECT3DVERTEXBUFFER9 GetVertex() { return vertexBuffer; }
	void* GetRenderMemory() { return renderMemory; }
	UINT GetByteSize() { return byteSize; }
	UINT GetStartByte() { return startByte; }

private:
	static LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	static const int MAXBUFFERSIZE;
	static UINT stockByte;
	void* renderMemory;
	UINT startByte;
	UINT byteSize;
};