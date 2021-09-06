#pragma once

#include "../Header/stdafx.h"
class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	//bool Initialize(ID3D11Device*, WCHAR*);
	bool Initialize(ID3D11Device*, LPCWSTR);
	ID3D11ShaderResourceView* Init(ID3D11Device*, LPCWSTR);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();


private:
	ID3D11ShaderResourceView* m_texture = nullptr;
};