#include "../../Header/stdafx.h"
#include "SkillEffect.h"
#include "Skill_Swift.h"

Skill_Swift::Skill_Swift()
{
}
Skill_Swift::Skill_Swift(const Skill_Swift& other)
{
}
Skill_Swift::~Skill_Swift()
{
}

Skill_Swift* Skill_Swift::Instance()
{
	static Skill_Swift* instance = new Skill_Swift();
	return instance;
}

bool Skill_Swift::Initialize(ID3D11Device* device, int order)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}
	m_device = device;

	sprite = new Sprite[2];

	m_layerOrder = order;
	switch (m_layerOrder)
	{
	case 0:
		sprite[0] = LoadTexture(device, L"../Graphics/data/Player/Swift/Swift_1.dds", 257, 77, 512, 512, 1, 4, 50);
		break;
	case 1:
		sprite[1] = LoadTexture(device, L"../Graphics/data/Player/Swift/Swift_2.dds", 216, 107, 512, 512, 2, 7, 50);
		break;
	}
	
	nowSprite.m_isRender = false;

	return true;
}

void Skill_Swift::Frame(Skill* s, PlayerClass* p, float tickTime, int layerOrder)
{
	s->m_Pos = p->m_Pos;
	Flip(s, p);

	if (s->m_isAnimationEnd)
	{
		for (int i = 0; i < 15; i++)
		{
			if (p->m_skillEffect[i] == s)
			{
				p->m_skillEffect[i]->Shutdown();
				delete p->m_skillEffect[i];
				p->m_skillEffect[i] = NULL;
			}
		}
	}
	//m_Pos = PlayerClass::Instance()->m_Pos;
}

void Skill_Swift::Flip(Skill* s, PlayerClass* p)
{
	s->m_Flip = p->m_Flip;
}
