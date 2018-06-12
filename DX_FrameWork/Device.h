#pragma once
class Device
{
public:
	static Device* Get(HWND hwnd = NULL);
	static void Delete();

	static LPDIRECT3DDEVICE9 GetDevice()
	{
		return device;
	}
	void BeginScene(DWORD clearColor);
	void EndScene();
private:
	Device(HWND hwnd);
	~Device();
	static Device* instance;


	LPDIRECT3D9 d3d;
	static LPDIRECT3DDEVICE9 device;

};