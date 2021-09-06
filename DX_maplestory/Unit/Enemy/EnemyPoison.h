#pragma once
class EnemyPoisonClass : public ObjectClass
{
public:
	EnemyPoisonClass();
	EnemyPoisonClass(const EnemyPoisonClass&);
	~EnemyPoisonClass();

	bool Initialize(ID3D11Device*);
	void Frame(float tickTime);

	void Attack(float tickTime);
	void Duration(float durationTime);

	static EnemyPoisonClass* Instance();

public:
	XMFLOAT2 m_attackBox[2] = { XMFLOAT2(0,0) };
	bool m_bAttackAble = false;
	
	int m_attackStartFrame = 0, m_attackEndFrame = 0;
	float m_durationTime = 0;

private:
	float m_tickTime = 0;
	
};