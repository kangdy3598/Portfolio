#include "../../Header/stdafx.h"
//#include "../ObjectPool.h"
#include "../Player/PlayerState.h"
#include "EnemyObstacle.h"

EnemyObstacleClass::EnemyObstacleClass()
{
}
EnemyObstacleClass::EnemyObstacleClass(const EnemyObstacleClass& other)
{
}
EnemyObstacleClass::~EnemyObstacleClass()
{
}

EnemyObstacleClass* EnemyObstacleClass::Instance()
{
	static EnemyObstacleClass* instance = new EnemyObstacleClass();
	return instance;
}

bool EnemyObstacleClass::Initialize(ID3D11Device* device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}
	m_device = device;

	sprite = new Sprite[2];
	sprite[0] = LoadTexture(device, L"../Graphics/data/Enemy/Obstacle.dds", 247, 1937, 4096, 4096, 12, 23, 70);
	sprite[1] = LoadTexture(device, L"../Graphics/data/Enemy/Obstacle_End.dds", 306, 302, 1024, 1024, 3, 5, 70, 0.50001f, 0.99995f);

	nowSprite = sprite[0];
	m_isAnimationLoop = false;

	m_Pos.y = -240;

	return true;
}

void EnemyObstacleClass::Frame(float tickTime)
{
	if(nowSprite.m_img == sprite[1].m_img) Attack(0, 3, tickTime);

	if (m_isAnimationEnd)
	{
		m_isAnimationEnd = false;
		m_animationFrameCount = 1;
		m_animationX = m_animationY = 1;
		if (nowSprite.m_img == sprite[0].m_img)
		{
			nowSprite = sprite[1];
		}
		else
		{
			nowSprite = sprite[0];
			m_bAttackAble = false;
			m_attackBox[0] = m_attackBox[1] = XMFLOAT2(0, 0);
			nowSprite.m_isRender = false;
		}
	}
}

float EnemyObstacleClass::SetRandomPos(EnemyObstacleClass* ob)
{
	//¡Ú
	//srand((unsigned int)time(NULL));
	//m_Pos.x = rand() % 11 * 50;// -1500 + (rand() % 11) * 300;
	//
	//if (m_Pos.x == ob->m_Pos.x) return -1;
	//else return m_Pos.x;
	return 0;
}

void EnemyObstacleClass::Attack(int startFrame, int endFrame, float tickTime)
{
	bool b_Check = true;
	
	if (m_animationFrameCount >= startFrame && m_animationFrameCount <= endFrame)
	{
		m_bAttackAble = true; 
		m_attackBox[0] = XMFLOAT2(m_Pos.x - 30, m_Pos.y + 180);
		m_attackBox[1] = XMFLOAT2(m_Pos.x + 30, m_Pos.y - 10);

		b_Check &= PlayerClass::Instance()->m_hitBox[1].x >= m_attackBox[0].x;
		b_Check &= PlayerClass::Instance()->m_hitBox[0].x <= m_attackBox[1].x;
		if (b_Check && PlayerClass::Instance()->m_PlayerMes != PlayerClass::ePlayerMes::STUN)
		{
			PlayerClass::Instance()->m_PlayerMes = PlayerClass::ePlayerMes::STUN;
			PlayerClass::Instance()->ChangeState(PlayerIdle::Instance(), PlayerClass::Instance());
		}
	}
	else
	{
		m_bAttackAble = false;
		m_attackBox[0] = m_attackBox[1] = XMFLOAT2(0, 0);
	}
}
