//#include "../Header/stdafx.h"
#include "TextureClass.h"
#include "DDSTextureLoader.h"

TextureClass::TextureClass()
{
}


TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}



bool TextureClass::Initialize(ID3D11Device* device, LPCWSTR filename)
{
	if(FAILED(CreateDDSTextureFromFile(device, filename, nullptr, &m_texture)))
	{
		MessageBox(NULL, filename, L"Error", MB_OK);
		return false;
	}

	return true;
}

ID3D11ShaderResourceView* TextureClass::Init(ID3D11Device* device, LPCWSTR filename)
{
	if (FAILED(CreateDDSTextureFromFile(device, filename, nullptr, &m_texture)))
	{
		std::wstring text = std::wstring(filename) + L"\n경로에 파일이 없습니다.";
		LPCWSTR lpText = text.c_str();
		MessageBox(0, lpText, L"파일 오류", MB_OK);

		return nullptr;
	}
	return m_texture;
}

void TextureClass::Shutdown()
{
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
}


ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}