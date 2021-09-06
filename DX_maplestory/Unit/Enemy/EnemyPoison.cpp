#include "../../Header/stdafx.h"
//#include "../ObjectPool.h"
#include "EnemyPoison.h"

EnemyPoisonClass::EnemyPoisonClass()
{
	
}
EnemyPoisonClass::EnemyPoisonClass(const EnemyPoisonClass& other)
{
}
EnemyPoisonClass::~EnemyPoisonClass()
{
}

EnemyPoisonClass* EnemyPoisonClass::Instance()
{
	static EnemyPoisonClass* instance = new EnemyPoisonClass();
	return instance;
}

bool EnemyPoisonClass::Initialize(ID3D11Device* device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}
	m_device = device;

	//m_attackBox[2] = { XMFLOAT2(0,0) };

	sprite = new Sprite[2];
	sprite[0] = LoadTexture(device, L"../Graphics/data/Enemy/attack5_areaWarning.dds", 256, 675, 4096, 4096, 8, 27, 100);
	sprite[1] = LoadTexture(device, L"../Graphics/data/Enemy/attack5_Poison.dds", 174, 47, 512, 512, 2, 6, 100);
	
	nowSprite = sprite[0];

	m_bAttackAble = false;
	m_attackStartFrame = 24;
	m_attackEndFrame = 26;
	m_durationTime = 0;
	m_isAnimationLoop = false;
	nowSprite.m_isRender = false;

	m_Pos.y = -240;
	return true;
}

void EnemyPoisonClass::Frame(float tickTime)
{
	Attack(tickTime);
	if (nowSprite.m_img == sprite[1].m_img) Duration(tickTime);
	if (m_isAnimationEnd)
	{
		m_isAnimationEnd = false;
		m_animationFrameCount = 1;
		m_animationX = m_animationY = 1;
		if (nowSprite.m_img == sprite[0].m_img)
		{
			nowSprite = sprite[1];
			m_isAnimationLoop = true;
			
			m_Pos.y = -235;
			m_attackStartFrame = 1;
			m_attackEndFrame = 6;
		}
		else
		{
			//nowSprite = sprite[0];
			//ObjectPoolClass::Instance()->PushToPool(this);
		}
	}
	
}

void EnemyPoisonClass::Attack(float tickTime)
{
	bool b_Check = true;
	float hitAmount = 0;
	m_tickTime += tickTime;
	m_attackBox[0] = XMFLOAT2(m_Pos.x - 60, m_Pos.y + 30);
	m_attackBox[1] = XMFLOAT2(m_Pos.x + 60, m_Pos.y + 10);

	if (nowSprite.m_img == sprite[0].m_img)
	{
		if (m_animationFrameCount >= 22 && m_animationFrameCount <= 23)
		{
			m_bAttackAble = true;
			hitAmount = 50;
		}
		else
			m_bAttackAble = false;
	}
	else
	{
		m_bAttackAble = true;
		hitAmount = 10;
	}

	if (m_bAttackAble && m_tickTime >= 1000)
	{
		m_tickTime = 0;
		b_Check &= PlayerClass::Instance()->m_hitBox[1].x >= m_attackBox[0].x;
		b_Check &= PlayerClass::Instance()->m_hitBox[0].x <= m_attackBox[1].x;
		if (b_Check)
		{
			// 피격 이펙트 , 데미지 계산
			//m_bAttack = true;
			//PlayerClass::Instance()->m_bHit = true;
			//m_hitPos.x = (m_attackBoundingBox[0].x + PlayerClass::m_boundingBox[1].x) / 2;
			//m_hitPos.y = (PlayerSkillEffect::m_boundingBox[0].x + PlayerSkillEffect::m_boundingBox[1].x) / 2;

			/*soundClass.fileName = "../Graphics/data/Enemy/Sound/Hit1.wav";
			soundClass.CreateEffectSound(1, &soundClass.fileName);
			soundClass.PlaySoundEffect(0);*/

			PlayerClass::Instance()->m_Hit = true;
			PlayerClass::Instance()->m_HitAmount = PlayerClass::Instance()->m_maxHP * (hitAmount / 100.0f);
			if(PlayerClass::Instance()->m_nowHP > 0) PlayerClass::Instance()->m_nowHP -= PlayerClass::Instance()->m_HitAmount;
		}
	}
}

void EnemyPoisonClass::Duration(float durationTime)
{
	m_durationTime += durationTime;
	if (m_durationTime >= 4000.0f)
	{
		m_bAttackAble = false;
		nowSprite = sprite[0];
		m_durationTime = 0;

		m_isAnimationEnd = false;
		m_animationFrameCount = 1;
		m_animationX = m_animationY = 1;
		nowSprite.m_isRender = false;
		//ObjectPoolClass::Instance()->PushToPool(this);
	}
}
