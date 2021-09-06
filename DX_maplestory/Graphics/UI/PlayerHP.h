#pragma once

class PlayerHPClass : public UIClass
{
public:
	PlayerHPClass();
	PlayerHPClass(const PlayerHPClass&);
	~PlayerHPClass();

	bool Initialize(ID3D11Device*);

	static PlayerHPClass* Instance();

	
	XMFLOAT2 m_UIPos[4] = { XMFLOAT2(0, 0) };
};