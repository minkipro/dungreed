#include "stdafx.h"
#include "Device.h"

Device* Device::instance = NULL;
LPDIRECT3DDEVICE9 Device::device = NULL;

Device * Device::Get(HWND hwnd)
{
	if (instance == NULL)
		instance = new Device(hwnd);

	return instance;
}

void Device::Delete()
{
	SAFE_DELETE(instance);
}

void Device::BeginScene(DWORD clearColor)
{
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clearColor, 1.0f, 0);
	device->BeginScene();
}

void Device::EndScene() //후면버퍼
{
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}

Device::Device(HWND hwnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	assert(d3d != NULL);

	D3DPRESENT_PARAMETERS param = { 0 };
	param.Windowed = TRUE;
	param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	param.AutoDepthStencilFormat = D3DFMT_D16;
	param.EnableAutoDepthStencil = TRUE;

	param.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr;
	hr = d3d->CreateDevice
	(
		D3DADAPTER_DEFAULT //주화면쓸거냐 보조화면쓸거냐
		, D3DDEVTYPE_HAL //하드
		, hwnd //핸들 (중요!!)핸들에서 렌더링된다
		, D3DCREATE_HARDWARE_VERTEXPROCESSING //정점처리 누가할거냐(하드웨어가한다)
		, &param //추가정보 설정
		, &device
	);
	assert(SUCCEEDED(hr));
}

Device::~Device()
{
	SAFE_RELEASE(device);
	SAFE_RELEASE(d3d);
}
