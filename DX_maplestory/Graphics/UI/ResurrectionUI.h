#pragma once

class ResurrectionUIClass : public UIClass
{
public:
	ResurrectionUIClass();
	ResurrectionUIClass(const ResurrectionUIClass&);
	~ResurrectionUIClass();

	bool Initialize(ID3D11Device*);
	bool ClickButton(POINT pos, int type);
	static ResurrectionUIClass* Instance();


	XMFLOAT2 m_UIPos[2] = { XMFLOAT2(0, 0) };
};