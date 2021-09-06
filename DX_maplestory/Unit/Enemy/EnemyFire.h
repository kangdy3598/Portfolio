#pragma once
class EnemyFireClass : public ObjectClass
{
public:
	EnemyFireClass();
	EnemyFireClass(const EnemyFireClass&);
	~EnemyFireClass();

	bool Initialize(ID3D11Device*);
	void Frame(float tickTime);

	void Attack(float tickTime);

	static EnemyFireClass* Instance();

public:
	XMFLOAT2 m_attackBox[2] = { XMFLOAT2(0,0) };
	bool m_bAttackAble = false;

	int m_attackStartFrame = 0, m_attackEndFrame = 0;
};