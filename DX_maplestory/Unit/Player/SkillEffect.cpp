#include "../../Header/stdafx.h"
#include "SkillEffect.h"
#include "Skill_Ultimate.h"
#include "Skill_Swift.h"

Skill::Skill()
{
}
Skill::Skill(const Skill& other)
{
}
Skill::~Skill()
{
}

Skill* Skill::Instance()
{
	static Skill* instance = new Skill();
	return instance;
}

bool Skill::Initialize(ID3D11Device* device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}
	m_device = device;
	nowSprite.m_isRender = false;

	return true;
}

void Skill::InitAnimation()
{
	m_isAnimationEnd = false;
	m_animationFrameCount = 1;
	m_animationX = m_animationY = 1;
}

void Skill::DeleteAnimation()
{
	//if (m_isAnimationEnd && !m_isAnimationLoop)
	{
		Shutdown();
	//	delete this;
	}
}

void Skill::Frame(float tickTime)
{
	//m_Pos = PlayerClass::Instance()->m_Pos;
	//m_Flip = PlayerClass::Instance()->m_Flip;

	if (m_skill_Ultimate)
	{
		m_skill_Ultimate->Frame(this, PlayerClass::Instance(), tickTime, m_layerOrder);
	}

	if (m_skill_Swift)
	{
		m_skill_Swift->Frame(this, PlayerClass::Instance(), tickTime, m_layerOrder);
	}
}

void Skill::Shutdown()
{
	ReleaseTexture();
	ShutdownBuffers();

	if (m_skill_Ultimate)
	{
		m_skill_Ultimate->ReleaseTexture();
		m_skill_Ultimate->ShutdownBuffers();
		delete m_skill_Ultimate;
		m_skill_Ultimate = 0;
	}

	if (m_skill_Swift)
	{
		m_skill_Swift->ReleaseTexture();
		m_skill_Swift->ShutdownBuffers();
		delete m_skill_Swift;
		m_skill_Swift = 0;
	}
}

