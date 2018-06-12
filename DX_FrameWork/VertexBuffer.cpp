#include "stdafx.h"

LPDIRECT3DVERTEXBUFFER9 VertexBuffer::vertexBuffer = nullptr;
const int VertexBuffer::MAXBUFFERSIZE = 100000;
UINT VertexBuffer::stockByte = 0;

VertexBuffer::VertexBuffer()
{
	renderMemory = nullptr;
	byteSize = 0;
}

void VertexBuffer::Init(void* memory, UINT byteSize, bool dynamic)
{
	assert(memory);
	assert(byteSize);
	assert(!renderMemory);
	assert(stockByte + byteSize < MAXBUFFERSIZE);

	if (vertexBuffer == nullptr)
	{
		if (dynamic)
		{
			DEVICE->CreateVertexBuffer(MAXBUFFERSIZE, D3DUSAGE_DYNAMIC, Vertex::fvf,
				D3DPOOL_DEFAULT, &vertexBuffer, NULL);
		}
		else
		{
			DEVICE->CreateVertexBuffer(MAXBUFFERSIZE, 0, Vertex::fvf,
				D3DPOOL_DEFAULT, &vertexBuffer, NULL);
		}

		DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	}

	startByte = stockByte;

	vertexBuffer->Lock(startByte, byteSize, &renderMemory, NULL);
	memcpy(renderMemory, memory, byteSize);
	vertexBuffer->Unlock();

	this->byteSize = byteSize;
	stockByte += byteSize;
}

void VertexBuffer::Release()
{
	SAFE_RELEASE(vertexBuffer);
}

void VertexBuffer::ChangeVertex(void * memory, UINT byteSize, bool dynamic)
{
	assert(memory);
	assert(byteSize);
	assert(renderMemory);
	assert(vertexBuffer);

	vertexBuffer->Lock(startByte, byteSize, &renderMemory, NULL);
	memcpy(renderMemory, memory, byteSize);
	vertexBuffer->Unlock();

	this->byteSize = byteSize;
}

void VertexBuffer::ChangeUV(TEXTUREFRAME uv)
{
	assert(renderMemory);
	assert(byteSize == 120);

	vertexBuffer->Lock(startByte, byteSize, &renderMemory, NULL);

	float* memory = (float*)renderMemory;

	memory += 3;
	(*memory) = uv.LTuv.x;
	memory++;
	(*memory) = uv.LTuv.y;

	memory += 4;
	(*memory) = uv.RBuv.x;
	memory++;
	(*memory) = uv.LTuv.y;

	memory += 4;
	(*memory) = uv.RBuv.x;
	memory++;
	(*memory) = uv.RBuv.y;

	memory += 4;
	(*memory) = uv.LTuv.x;
	memory++;
	(*memory) = uv.LTuv.y;

	memory += 4;
	(*memory) = uv.RBuv.x;
	memory++;
	(*memory) = uv.RBuv.y;

	memory += 4;
	(*memory) = uv.LTuv.x;
	memory++;
	(*memory) = uv.RBuv.y;

	vertexBuffer->Unlock();

}
