#pragma once

class EnemyClass;
class Skill_Ultimate : public Skill
{
public:
	Skill_Ultimate();
	Skill_Ultimate(const Skill_Ultimate&);
	~Skill_Ultimate();

	bool Initialize(ID3D11Device*, int order);
	void Frame(Skill* s, PlayerClass* p, float tickTime, int layerOrder);
	void Flip(Skill* s, PlayerClass* p);
	void attack(Skill* s, float tickTime);

	static Skill_Ultimate* Instance();

public:
	
	float m_tickTime = 0;
	float m_rapidAttack = 0;
	bool m_bHitEffect = false;
private:
	// È®ÀÎ¿ë
	XMFLOAT4 m_attackColor = XMFLOAT4(1, 0, 0, 1);
};