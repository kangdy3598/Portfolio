#pragma once

//class EnemyFireClass;
class EnemyTailClass;
class EnemyPoisonClass;
class EnemyObstacleClass;

class PlayerClass;

class EnemyClass : public ObjectClass
{
public:
	enum class eEnemyState : int
	{
		WAIT = -2,
		SUMMON = -1,
		MOVE = 0,
		ATTACK1 = 1,
		ATTACK2 = 2,
		ATTACK3 = 3,
		ATTACK4 = 4,
		ATTACK5 = 5,
		ATTACK6 = 6,
		DIE
	};
	eEnemyState m_EnemyState = eEnemyState::WAIT;

public:
	EnemyClass();
	EnemyClass(const EnemyClass&);
	~EnemyClass();

	bool Initialize(ID3D11Device*);
	void Frame(float tickTime);
	void LoadSprite();

	void Attack(float tickTime);
	void Hit(float tickTime);
	void Flip();
	void Shutdown();

	static EnemyClass* Instance();

public:
	XMFLOAT2 m_attackBox[2] = { XMFLOAT2(0,0) };
	XMFLOAT2 m_head = XMFLOAT2(0, 0);
	//EnemyFireClass* m_EnemyFire[5] = { nullptr };

	int m_maxHP, m_nowHP;

	float m_AccelationX = 2;
	float m_AccelationY = 0;

	float m_patternCoolTime[6] = { 0 };

	bool m_bAttackAble = false;
	bool m_bAttack = false;

	int m_attackStartFrame = 0, m_attackEndFrame = 0;
	int m_attackDamage = 0;

	bool m_bHit = false;
	bool m_bHitAble = false;
	XMFLOAT2 m_hitPos = XMFLOAT2(0, 0);
	int m_hitStartFrame = 0, m_hitEndFrame = 0;
	int m_hitDamage = 0;
	
	bool m_summon = false;
	bool m_warning = false;
	int m_warningCount = -1;

	EnemyTailClass* m_EnemyTail[3] = { nullptr };
	EnemyPoisonClass* m_EnemyPoison[24] = { nullptr };
	EnemyObstacleClass* m_EnemyObstacle[8] = { nullptr };

private:
	
	int m_tickTime = 0;
	int m_EnemyCode = 0;
};