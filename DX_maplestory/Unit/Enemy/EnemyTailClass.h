#pragma once

class EnemyTailClass : public ObjectClass
{
public:
	EnemyTailClass();
	EnemyTailClass(const EnemyTailClass&);
	~EnemyTailClass();

	bool Initialize(ID3D11Device*);
	void Frame(float tickTime);

	void Attack(float tickTime);
	void Hit(float tickTime);

	static EnemyTailClass* Instance();

public:
	XMFLOAT2 m_attackBox[2] = { XMFLOAT2(0,0) };
	XMFLOAT2 m_head[2] = { XMFLOAT2(0,0) };

	bool m_bAttackAble = false;
	bool m_bAttack = false;
	int m_attackStartFrame = 0, m_attackEndFrame = 0;
	int m_attackDamage = 0;

private:
	int m_tickTime = 0;
};