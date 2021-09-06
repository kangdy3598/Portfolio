#pragma once

class EnemyHPClass : public UIClass
{
public:
	EnemyHPClass();
	EnemyHPClass(const EnemyHPClass&);
	~EnemyHPClass();

	bool Initialize(ID3D11Device*);

	static EnemyHPClass* Instance();

	XMFLOAT2 m_UIPos[6] = { XMFLOAT2(0, 0) };
};