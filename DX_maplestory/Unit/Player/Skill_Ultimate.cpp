#include "../../Header/stdafx.h"
#include "SkillEffect.h"
#include "Skill_Ultimate.h"

Skill_Ultimate::Skill_Ultimate()
{
}
Skill_Ultimate::Skill_Ultimate(const Skill_Ultimate& other)
{
}
Skill_Ultimate::~Skill_Ultimate()
{
}

Skill_Ultimate* Skill_Ultimate::Instance()
{
	static Skill_Ultimate* instance = new Skill_Ultimate();
	return instance;
}

bool Skill_Ultimate::Initialize(ID3D11Device* device, int order)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}
	m_device = device;

	sprite = new Sprite[5];

	m_layerOrder = order;
	switch (m_layerOrder)
	{
	case 0:
		sprite[0] = LoadTexture(device, L"../Graphics/data/Player/Ultimate/ultimate_keydown_front.dds", 376, 256, 2256, 256, 6, 6, 30, 0.74f, 0.48f);
		break;
	case 1:
		sprite[1] = LoadTexture(device, L"../Graphics/data/Player/Ultimate/ultimate_pre_back.dds", 305, 123, 2048, 256, 5, 5, 25, 0.55f, 0.82f);
		sprite[2] = LoadTexture(device, L"../Graphics/data/Player/Ultimate/ultimate_keydown_back.dds", 164, 116, 1024, 116, 6, 6, 30, 0.25f, 1.23f);
		sprite[3] = LoadTexture(device, L"../Graphics/data/Player/Ultimate/ultimate_end_back.dds", 175, 120, 1024, 120, 5, 5, 40, 0.29f, 0.82f);
		break;
	case 2:
		sprite[4] = LoadTexture(device, L"../Graphics/data/Player/Ultimate/Ultimate_Hit.dds", 212, 229, 1272, 256, 6, 6, 30);
	default:
		break;
	}

	m_attackBox[0] = XMFLOAT2(10, 130);
	m_attackBox[1] = XMFLOAT2(250, 10);
	
	m_tickTime = 0;
	m_rapidAttack = 6.6f;

	return true;
}

void Skill_Ultimate::Frame(Skill* s, PlayerClass* p, float tickTime, int layerOrder)
{
	if (layerOrder != 2)
	{
		s->m_Pos = p->m_Pos;
		Flip(s, p);
	}
	if (layerOrder == 0) attack(s, tickTime);

	if (EnemyClass::Instance()->m_bHit)
	{
		for (int i = 0; i < 15; i++)
		{
			if(!p->m_skillEffect[i] && m_bHitEffect)
			{
				p->m_skillEffect[i] = new Skill;
				p->m_skillEffect[i]->Initialize(m_device);
				p->m_skillEffect[i]->InitAnimation();
				p->m_skillEffect[i]->nowSprite.m_isRender = true;
				p->m_skillEffect[i]->m_layerOrder = 2;
				p->m_skillEffect[i]->m_name = L"Ultimate_hit";

				p->m_skillEffect[i]->m_skill_Ultimate = new Skill_Ultimate;
				p->m_skillEffect[i]->m_skill_Ultimate->Initialize(m_device, 2);
				p->m_skillEffect[i]->nowSprite = p->m_skillEffect[i]->m_skill_Ultimate->sprite[4];

				m_bHitEffect = false;
				break;
			}
		}
	}
}

void Skill_Ultimate::Flip(Skill* s, PlayerClass* p)
{
	s->m_Flip = p->m_Flip;
	s->m_attackBox[0].x = p->m_Pos.x + m_attackBox[0].x * (2 * s->m_Flip - 1);
	s->m_attackBox[1].x = p->m_Pos.x + m_attackBox[1].x * (2 * s->m_Flip - 1);

	s->m_attackBox[0].y = p->m_Pos.y + m_attackBox[0].y;
	s->m_attackBox[1].y = p->m_Pos.y + m_attackBox[1].y;

	if (!s->m_Flip)
	{
		float _temp = m_attackBox[0].x;
		m_attackBox[0].x = m_attackBox[1].x;
		m_attackBox[1].x = _temp;
	}
}

void Skill_Ultimate::attack(Skill* s, float tickTime)
{
	EnemyClass* e = EnemyClass::Instance();
	bool b_Check = true;

	b_Check &= e->m_EnemyState > EnemyClass::eEnemyState::SUMMON;
	b_Check &= e->m_hitBox[0].x != e->m_hitBox[1].x;
	b_Check &= s->m_attackBox[1].x >= e->m_hitBox[0].x;
	b_Check &= s->m_attackBox[0].x <= e->m_hitBox[1].x;
	b_Check &= e->m_bHitAble;

	if (b_Check)
	{
		EnemyClass::Instance()->m_hitDamage = 1000;
		
		m_tickTime -= tickTime;
		if (m_tickTime <= 0)
		{
			m_tickTime = 1000 / m_rapidAttack;
			EnemyClass::Instance()->m_bHit = true;
			m_bHitEffect = true;
			EnemyClass::Instance()->m_nowHP -= EnemyClass::Instance()->m_hitDamage;
		}
	}
}
