#pragma once

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();
	static InputClass* Instance();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	/*void KeyDown(unsigned int);
	void KeyUp(unsigned int);
	bool IsKeyDown(unsigned int);*/

	bool GetKeyDown(unsigned int);
	bool GetKeyUp(unsigned int);
	bool GetKey(unsigned int);

	int GetMouseState(int state = 0);
	//bool IsEscapePressed();

	unsigned char m_keyboardState[256] = { 0, };
	
private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

public:
	int m_screenWidth = 0;
	int m_screenHeight = 0;
	DIMOUSESTATE m_mouseState;
private:
	IDirectInput8* m_directInput = nullptr;
	IDirectInputDevice8* m_keyboard = nullptr;
	IDirectInputDevice8* m_mouse = nullptr;

	bool m_mouseDown = false;

	bool m_down = false;
};