#pragma once

class TimeClass;
class InputClass;
class GraphicsClass;
class ObjectClass;

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName = L"";
	HINSTANCE m_hinstance = NULL;
	HWND m_hwnd = NULL;

	InputClass* m_Input = nullptr;
	GraphicsClass* m_Graphics = nullptr;
	TimeClass* m_Time = nullptr;

	POINT ptMouse;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static SystemClass* ApplicationHandle = 0;