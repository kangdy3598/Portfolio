#include "../../Header/stdafx.h"

EnemyTailClass::EnemyTailClass()
{
}
EnemyTailClass::EnemyTailClass(const EnemyTailClass& other)
{
}
EnemyTailClass::~EnemyTailClass()
{
}

EnemyTailClass* EnemyTailClass::Instance()
{
	static EnemyTailClass* instance = new EnemyTailClass();
	return instance;
}

bool EnemyTailClass::Initialize(ID3D11Device* device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}
	m_device = device;

	//m_head[0] = m_head[1] = XMFLOAT2(0, 0);

	m_bAttackAble = false;
	m_bAttack = false;
	m_attackDamage = 0;

	m_Pos.y = -279;

	m_attackStartFrame = 24;
	m_attackEndFrame = 26;

	nowSprite = LoadTexture(device, L"../Graphics/data/Enemy/TailAttack.dds", 923, 717, 8192, 8192, 6, 40, 90);

	m_isAnimationLoop = false;
	nowSprite.m_isRender = false;
	return true;
}

void EnemyTailClass::Frame(float tickTime)
{
	Attack(tickTime);
	if (m_isAnimationEnd)
	{
		m_isAnimationEnd = false;
		m_animationFrameCount = 1;
		m_animationX = m_animationY = 1;
		nowSprite.m_isRender = false;
	}
}

void EnemyTailClass::Attack(float tickTime)
{
	bool b_Check = true;
	//m_tickTime += tickTime;

	if (m_animationFrameCount >= m_attackStartFrame && m_animationFrameCount <= m_attackEndFrame)
	{
		m_bAttackAble = true;
		m_attackBox[0] = XMFLOAT2(m_Pos.x - 190, m_Pos.y + 350);
		m_attackBox[1] = XMFLOAT2(m_Pos.x + 110, m_Pos.y + 30);
		//m_tickTime = 0;
		b_Check &= PlayerClass::Instance()->m_hitBox[1].x >= m_attackBox[0].x;
		b_Check &= PlayerClass::Instance()->m_hitBox[0].x <= m_attackBox[1].x;
		if (b_Check && !m_bAttack)
		{
			// 피격 이펙트 , 데미지 계산
			m_bAttack = true;
			PlayerClass::Instance()->m_Hit = true;
			//m_hitPos.x = (m_attackBoundingBox[0].x + PlayerClass::m_boundingBox[1].x) / 2;
			//m_hitPos.y = (PlayerSkillEffect::m_boundingBox[0].x + PlayerSkillEffect::m_boundingBox[1].x) / 2;

			/*soundClass.fileName = "../Graphics/data/Enemy/Sound/Hit1.wav";
			soundClass.CreateEffectSound(1, &soundClass.fileName);
			soundClass.PlaySoundEffect(0);*/

			PlayerClass::Instance()->m_HitAmount = 1000;// PlayerClass::Instance()->m_maxHP* (m_attackDamage / 100.0f);
			PlayerClass::Instance()->m_nowHP -= PlayerClass::Instance()->m_HitAmount;
		}
	}
	else
	{
		m_bAttackAble = false;
		m_bAttack = false;
	}
}

