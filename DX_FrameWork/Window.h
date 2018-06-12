#pragma once
class Window
{
public:
	Window(HINSTANCE instance);
	~Window();

	void Create();
	WPARAM Run();

	LRESULT MessageLoop
	(
		HWND hwnd
		, UINT message
		, WPARAM wParam
		, LPARAM lParam
	);

	static Window* GetWindow()
	{
		return window;
	}

protected:
	virtual void Initialize() = 0;
	virtual void Destroy() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	static Window* window;

	HINSTANCE instance;
	HWND winHandle;
};