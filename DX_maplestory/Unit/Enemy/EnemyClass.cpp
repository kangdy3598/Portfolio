#include "../../Header/stdafx.h"
//#include "EnemyObstacle.h"
//#include "EnemyPoison.h"
#include "EnemyState.h"
#include "EnemyClass.h"

EnemyClass::EnemyClass()
{
	
}
EnemyClass::EnemyClass(const EnemyClass& other)
{
}
EnemyClass::~EnemyClass()
{
}

EnemyClass* EnemyClass::Instance()
{
	static EnemyClass* instance = new EnemyClass();
	return instance;
}

bool EnemyClass::Initialize(ID3D11Device* device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}
	m_device = device;

	m_Pos.y = -280;
	m_maxHP = m_nowHP = 200000;

	// 제단 히트 박스
	m_hitBox[0] = XMFLOAT2(-60, 0); 
	m_hitBox[1] = XMFLOAT2(320, -250);
	
	m_objectType = L"Enemy";

	srand((unsigned int)time(NULL));
	for (int i = 0; i < sizeof(m_EnemyObstacle) / sizeof(EnemyObstacleClass*); i++)
	{
		m_EnemyObstacle[i] = new EnemyObstacleClass;
		m_EnemyObstacle[i]->m_Pos.x = -1500 + (rand() % 11) * 300.0f;
		for (int j = 0; j < i; j++)
		{
			if (m_EnemyObstacle[i]->m_Pos.x == m_EnemyObstacle[j]->m_Pos.x)
			{
				delete m_EnemyObstacle[i]; m_EnemyObstacle[i] = 0;
				i--;
				break;
			}
		}
		if (m_EnemyObstacle[i])
		{
			m_EnemyObstacle[i]->Initialize(device);
			ObjectPoolClass::Instance()->SetObjectPool(m_EnemyObstacle[i], "obstacle", 8);
		}
	}

	for (int i = 0; i < sizeof(m_EnemyTail) / sizeof(EnemyTailClass*); i++)
	{
		m_EnemyTail[i] = new EnemyTailClass;
		m_EnemyTail[i]->Initialize(device);
		ObjectPoolClass::Instance()->SetObjectPool(m_EnemyTail[i], "tail", 8);
	}

	for (int i = 0; i < sizeof(m_EnemyPoison) / sizeof(EnemyPoisonClass*); i++)
	{
		m_EnemyPoison[i] = new EnemyPoisonClass;
		m_EnemyPoison[i]->Initialize(device);
		ObjectPoolClass::Instance()->SetObjectPool(m_EnemyPoison[i], "poison", 24);
	}

	return true;
}

void EnemyClass::Frame(float tickTime)
{
	if (m_State)
	{
		m_State->Execute();
	}

	for (int i = 0; i < 6; i++)
	{
		if (m_patternCoolTime[i] > 0) m_patternCoolTime[i] -= tickTime;
		else m_patternCoolTime[i] = 0;
	}

	Attack(tickTime);
	Hit(tickTime);

	for (int i = 0; i < sizeof(m_EnemyTail) / sizeof(EnemyTailClass*); i++)
	{
		if (m_EnemyTail[i]->nowSprite.m_isRender) m_EnemyTail[i]->Frame(tickTime);
	}
	for (int i = 0; i < sizeof(m_EnemyPoison) / sizeof(EnemyPoisonClass*); i++)
	{
		if (m_EnemyPoison[i]->nowSprite.m_isRender) m_EnemyPoison[i]->Frame(tickTime);
	}
	for (int i = 0; i < sizeof(m_EnemyObstacle) / sizeof(EnemyObstacleClass*); i++)
	{
		if (m_EnemyObstacle[i] != NULL) m_EnemyObstacle[i]->Frame(tickTime);
	}
	// CheckAnimation////////////////////////////////////////////
	
	//if ((GetAsyncKeyState(0x53) & 0x0001)) //A
	//{
	//	m_Flip ^= TRUE; 
	//}
	//if (GetAsyncKeyState(0x53) & 0x0001) //S
	//{
	//	if (nowSprite.m_animationFrameTickTime == 10000000000) nowSprite.m_animationFrameTickTime = 100;
	//	else
	//	{
	//		nowSprite.m_animationFrameTickTime = 10000000000;
	//	}
	//}
	//if (GetAsyncKeyState(0x70) & 0x0001) //F1
	//{
	//	m_animationX++;
	//	m_animationFrameCount++;
	//	if (m_animationX > nowSprite.m_animationRowCount)
	//	{
	//		m_animationX = 1; ++m_animationY;
	//	}
	//}
	//if (GetAsyncKeyState(0x71) & 0x0001) // F2
	//{
	//	m_animationX--;
	//	m_animationFrameCount--;
	//	if (m_animationX < 0)
	//	{
	//		m_animationX = nowSprite.m_animationRowCount; --m_animationY;
	//	}
	//}
	/////////////////////////////////////////////////////////////
}

void EnemyClass::Hit(float tickTime)
{
	bool b_Check = true;
	if (m_animationFrameCount >= m_hitStartFrame && m_animationFrameCount <= m_hitEndFrame && m_nowHP > 0)
	{
		m_bHitAble = true;
	}

	else
	{
		m_bHit = false;
		m_bHitAble = false;
		m_hitDamage = 0;
	}

}

void EnemyClass::Flip()
{
	if (PlayerClass::Instance()->m_Pos.x > m_Pos.x) m_Flip = true;
	else m_Flip = false;
}

void EnemyClass::Shutdown()
{
	for (int i = 0; i < sizeof(m_EnemyTail) / sizeof(EnemyTailClass*); i++)
	{
		if (m_EnemyTail[i])
		{
			m_EnemyTail[i]->Shutdown();
			m_EnemyTail[i] = 0;
		}
	}

	for (int i = 0; i < sizeof(m_EnemyPoison) / sizeof(EnemyPoisonClass*); i++)
	{
		if (m_EnemyPoison[i])
		{
			m_EnemyPoison[i]->Shutdown();
			m_EnemyPoison[i] = 0;
		}
	}

	for (int i = 0; i < sizeof(m_EnemyObstacle) / sizeof(EnemyObstacleClass*); i++)
	{
		if (m_EnemyObstacle[i])
		{
			m_EnemyObstacle[i]->Shutdown();
			m_EnemyObstacle[i] = 0;
		}
	}

	ReleaseTexture();
	ShutdownBuffers();

	if (sprite)
	{
		delete[] sprite;
		sprite = 0;
	}
}

void EnemyClass::Attack(float tickTime)
{
	bool b_Check = true;
	//m_tickTime += tickTime;

	if (m_animationFrameCount >= m_attackStartFrame && m_animationFrameCount <= m_attackEndFrame && m_nowHP > 0)
	{
		m_bAttackAble = true;
		//m_tickTime = 0;
		b_Check &= PlayerClass::Instance()->m_hitBox[1].x >= m_attackBox[0].x;
		b_Check &= PlayerClass::Instance()->m_hitBox[0].x <= m_attackBox[1].x;
		if (b_Check && !m_bAttack)
		{
			// 피격 이펙트 , 데미지 계산
			m_bAttack = true;
			PlayerClass::Instance()->m_Hit = true;
			//m_hitPos.x = (m_attackBox[0].x + PlayerClass::Instance()->m_hitBox[1].x) / 2;
			//m_hitPos.y = (PlayerClass::Instance()->m_hitBox[1].x + PlayerClass::Instance()->m_hitBox[1].x) / 2;

			/*soundClass.fileName = "../Graphics/data/Enemy/Sound/Hit1.wav";
			soundClass.CreateEffectSound(1, &soundClass.fileName);
			soundClass.PlaySoundEffect(0);*/

			PlayerClass::Instance()->m_HitAmount = 100;// PlayerClass::Instance()->m_maxHP* (m_attackDamage / 100.0f);
			PlayerClass::Instance()->m_nowHP -= PlayerClass::Instance()->m_HitAmount;
		}
		
	}
	else
	{
		m_bAttackAble = false;
		m_bAttack = false;
	}
	
}

void EnemyClass::LoadSprite()
{
	sprite = new Sprite[18];
	sprite[0] = LoadTexture(m_device, L"../Graphics/data/Enemy/move.dds", 412, 206, 2048, 2048, 4, 10, 100);

	sprite[1] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack1.dds", 996, 776, 8192, 8192, 6, 33, 120, 0.413f, 1.0017f);

	sprite[2] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack2_1.dds", 996, 774, 8192, 8192, 5, 21, 100, 0.413f, 1.0017f);
	sprite[3] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack2_2.dds", 1665, 875, 8192, 8192, 4, 29, 100, 0.816f, 1.0228f);
	sprite[4] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack2_3.dds", 1498, 859, 8192, 8192, 4, 28, 100, 0.7955f, 1.042f);
	sprite[5] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack2_4.dds", 1220, 868, 8192, 8192, 4, 27, 100, 0.74899f, 1.0313f);
	sprite[6] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack2_5.dds", 714, 776, 4096, 4096, 4, 12, 100);

	sprite[7] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack3.dds", 996, 720, 8192, 8192, 5, 32, 100);

	sprite[8] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack4.dds", 1696, 720, 8192, 8192, 4, 30, 120, 0.75f, 1);

	sprite[9] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack5_1.dds", 996, 592, 4096, 4096, 4, 21, 100, 0.55f, 1);
	sprite[10] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack5_2.dds", 688, 1025, 8192, 8192, 6, 22, 100, 0.74765f, 1.034f);
	sprite[11] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack5_3.dds", 688, 1025, 8192, 8192, 6, 22, 100, 0.74765f, 1.034f);
	sprite[12] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack5_4.dds", 801, 1062, 8192, 8192, 7, 30, 100, 0.6423f, 0.9975f);

	sprite[13] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack6_1.dds", 1564, 1108, 16384, 16384, 6, 52, 100, 0.678f, 0.96f);
	sprite[14] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack6_2.dds", 1312, 876, 4096, 4096, 3, 12, 100, 0.756f, 1.0041f);
	sprite[15] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack6_3.dds", 1177, 758, 4096, 4096, 3, 7, 100, 0.843f, 1.059f);
	sprite[16] = LoadTexture(m_device, L"../Graphics/data/Enemy/attack6_4.dds", 714, 776, 4096, 4096, 4, 13, 100, 0.621f, 1.003f);

	sprite[17] = LoadTexture(m_device, L"../Graphics/data/Enemy/die.dds", 1008, 793, 8192, 8192, 6, 59, 100, 0.5f, 0.98f);
}
