#pragma once

//
//template <typename T>

//class EnemyClass;
//class PlayerState;

class Skill;
class PlayerClass : public ObjectClass
{
public:
	enum class ePlayerState : int
	{
		IDLE = 0,
		WALK = 1,
		JUMP = 2,
		DOUBLEJUMP = 3,
		ATTACK = 4,
		DIE = 5,
		STATECOUNT
	};
	ePlayerState m_PlayerState = ePlayerState::IDLE;

	enum class ePlayerMes : int
	{
		NONE = 0,
		STUN = 1
	};
	ePlayerMes m_PlayerMes = ePlayerMes::NONE;

public:
	PlayerClass();
	~PlayerClass();

	static PlayerClass* Instance();

	bool Initialize(ID3D11Device*);
	void Frame(float tickTime, unsigned char* key);
	void Flip();
	bool isGrounding();
	void mesDuration(float tickTime);
	void Shutdown();
public :
	DamageClass* m_hitDamage[15];
	DamageClass* m_attackDamage[15];

	Skill* m_skillEffect[15] = { nullptr };

	XMFLOAT2 m_head = XMFLOAT2(0, 10);
	int m_maxHP = 50000, m_nowHP = 50000;
	int m_HitAmount = 0;
	bool m_Hit = false;

	float m_AccelationX = 0;
	float m_AccelationY = 0;
	bool m_AccelationDirect = false;
	bool m_isMove = false;

	bool m_bResurrection = false;
	int m_AttackKey = 0x41;
	int m_JumpKey = 0x46;
	int m_HPRecover = 0x45;

	unsigned char* m_key = nullptr;

	int m_attackCount = 0;
	float m_mesTickTime = 0;
private :
	//State* m_State = nullptr;
};


