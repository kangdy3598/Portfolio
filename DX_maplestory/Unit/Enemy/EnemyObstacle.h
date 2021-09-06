#pragma once
class ObjectPoolClass;
class PlayerClass;

class EnemyObstacleClass : public ObjectClass
{
public:
	EnemyObstacleClass();
	EnemyObstacleClass(const EnemyObstacleClass&);
	~EnemyObstacleClass();

	bool Initialize(ID3D11Device*);
	void Frame(float tickTime);

	float SetRandomPos(EnemyObstacleClass*);
	void Attack(int startFrame, int endFrame, float tickTime);

	static EnemyObstacleClass* Instance();

public:
	XMFLOAT2 m_attackBox[2] = { XMFLOAT2(0,0) };
	bool m_bAttackAble = false;
};