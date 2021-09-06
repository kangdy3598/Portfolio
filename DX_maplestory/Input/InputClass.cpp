#include "../Header/stdafx.h"
#include "InputClass.h"

InputClass::InputClass()
{
}
InputClass::InputClass(const InputClass& other)
{
}
InputClass::~InputClass()
{
}

InputClass* InputClass::Instance()
{
	static InputClass* instance = new InputClass();
	return instance;
}

bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	// 마우스 커서의 위치 지정에 사용될 화면 크기를 설정합니다.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	
	// Direct Input 인터페이스를 초기화 합니다.
	HRESULT result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// 키보드의 Direct Input 인터페이스를 생성합니다
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// 데이터 형식을 설정하십시오. 이 경우 키보드이므로 사전 정의된 데이터 형식을 사용할 수 있습니다.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	// 다른 프로그램과 공유하지 않도록 키보드의 협조 수준을 설정합니다
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// 키보드를 할당받는다
	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	// 마우스 Direct Input 인터페이스를 생성합니다.
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// 미리 정의 된 마우스 데이터 형식을 사용하여 마우스의 데이터 형식을 설정합니다.
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	// 다른 프로그램과 공유 할 수 있도록 마우스의 협력 수준을 설정합니다.
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// 마우스를 할당받는다
	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void InputClass::Shutdown()
{
	// 마우스를 반환합니다.
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	// 키보드를 반환합니다.
	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	// m_directInput 객체를 반환합니다.
	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}
}


bool InputClass::Frame()
{
	// 키보드의 현재 상태를 읽는다.
	if (!ReadKeyboard())
	{
		return false;
	}

	// 마우스의 현재 상태를 읽는다.
	if (!ReadMouse())
	{
		return false;
	}

	//ProcessInput();
	return true;
}


bool InputClass::ReadKeyboard()
{
	// 키보드 디바이스를 얻는다.
	HRESULT result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		// 키보드가 포커스를 잃었거나 획득되지 않은 경우 컨트롤을 다시 가져 온다
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool InputClass::ReadMouse()
{
	// 마우스 디바이스를 얻는다.
	HRESULT result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		// 마우스가 포커스를 잃었거나 획득되지 않은 경우 컨트롤을 다시 가져온다
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}
	
	return true;
}

void InputClass::ProcessInput()
{
	//m_mouseX += m_mouseState.lX;
	//m_mouseY += m_mouseState.lY;

	//if (m_mouseX < 0) { m_mouseX = 0; }
	//if (m_mouseY < 0) { m_mouseY = 0; }

	//if (m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
	//if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }
}

int InputClass::GetMouseState(int state)
{
	if (m_mouseState.rgbButtons[state] & 0x80)
	{
		if (!m_mouseDown)
		{
			//GetMouseButtonDown
			m_mouseDown = true;
			return 1;
		}
		else
		{
			//GetMouseButton
			return 2;
		}
	}
	else if (m_mouseDown)
	{
		//GetMouseButtonUp
		m_mouseDown = false;
		return 3;
	}

	else return 0;
}

bool InputClass::GetKeyDown(unsigned int input)
{
	/*if ((GetAsyncKeyState(input) & 0x8000) == 0x8000 && !m_down)
	{
		m_down = true; return true;
	}
	if ((GetAsyncKeyState(input) & 0x8001) == 0x0000 && m_down) m_down = false;
	return false;*/

	if (GetAsyncKeyState(input) & 0x0001) return true;
	else return false;
}

bool InputClass::GetKeyUp(unsigned int input)
{
	if ((GetAsyncKeyState(input) & 0x8000) == 0x8000 && !m_down) m_down = true;
	if ((GetAsyncKeyState(input) & 0x8001) == 0x0000 && m_down)
	{
		m_down = false; return true;
	}
	else return false;
}

bool InputClass::GetKey(unsigned int input)
{
	if ((GetAsyncKeyState(input) & 0x8000)) return true;
	else return false;
}


//bool InputClass::IsEscapePressed()
//{
//	if (m_keyboardState[DIK_ESCAPE] & 0x80)
//	{
//		return true;
//	}
//
//	return false;
//}

//void InputClass::KeyDown(unsigned int input)
//{
//	// 키가 눌렸다면 해당 키값을 true로 저장합니다
//	//int a = input;
//	//wchar_t buffer[256];
//	//wsprintfW(buffer, L"%d", a);
//	//MessageBoxW(nullptr, buffer, buffer, MB_OK);
//	m_keyboardState[input] = true;
//}
//
//void InputClass::KeyUp(unsigned int input)
//{
//	// 키가 해제되었다면 해당 키값을 false로 저장합니다
//	
//	m_keyboardState[input] = false;
//}
//
//bool InputClass::IsKeyDown(unsigned int key)
//{
//	// 현재 키값이 눌려졌는지 아닌지 상태를 반환합니다
//	return m_keyboardState[key] & 0x80;
//}

