#include "../../Header/stdafx.h"
#include "PlayerState.h"
#include "PlayerClass.h"
//#include "../Unit/Enemy/EnemyClass.h"
//#include "Skill_Ultimate.h"
#include <string>
PlayerClass::PlayerClass()
{
}
PlayerClass::~PlayerClass()
{
}

PlayerClass* PlayerClass::Instance()
{
	static PlayerClass* instance = new PlayerClass();
	return instance;
}

bool PlayerClass::Initialize(ID3D11Device* device)
{
	/*m_Effect[0] = new PlayerSkillEffect;
	m_Effect[1] = new PlayerSkillEffect;
	m_Effect[2] = new PlayerSkillEffect;*/

	if (!InitializeBuffers(device))
	{
		return false;
	}

	m_device = device;

	sprite = new Sprite[(int)ePlayerState::STATECOUNT];
	sprite[0] = LoadTexture(device, L"../Graphics/data/Player/Stand.dds", 150, 86, 300, 300, 2, 4, 500);
	sprite[1] = LoadTexture(device, L"../Graphics/data/Player/Walk.dds", 150, 86, 300, 300, 2, 4, 140);
	sprite[2] = LoadTexture(device, L"../Graphics/data/Player/Jump.dds", 150, 86, 256, 256, 1, 1, 100);
	sprite[3] = LoadTexture(device, L"../Graphics/data/Player/Ultimate_Pre.dds", 150, 86, 300, 300, 2, 4, 50);
	sprite[4] = LoadTexture(device, L"../Graphics/data/Player/Ultimate_Keydown.dds", 150, 86, 512, 512, 3, 6, 50);
	sprite[5] = LoadTexture(device, L"../Graphics/data/Player/Dead.dds", 46, 69, 256, 256, 1, 1, 500);

	/*for (int i = 0; i < sizeof(m_skillEffect) / sizeof(Skill*); i++)
	{
		m_skillEffect[i] = new Skill;
		m_skillEffect[i]->Initialize(device);
	}*/

	for (int i = 0; i < sizeof(m_hitDamage) / sizeof(DamageClass*); i++)
	{
		m_hitDamage[i] = new DamageClass;
		m_hitDamage[i]->Initialize(device, 0);
		//m_hitDamage[i]->nowSprite.m_isRender = false;
	}
	for (int i = 0; i < sizeof(m_attackDamage) / sizeof(DamageClass*); i++)
	{
		m_attackDamage[i] = new DamageClass;
		m_attackDamage[i]->Initialize(device, 1);
		//m_hitDamage[i]->nowSprite.m_isRender = false;
	}
	ChangeState(PlayerIdle::Instance(), this);
	
	return true;
}

void PlayerClass::Frame(float tickTime, unsigned char* key)
{
	m_key = key;
	if (m_State)
	{
		m_State->Execute();
	}

	if (!m_isMove)
	{
		if (isGrounding() && m_PlayerState != PlayerClass::ePlayerState::JUMP)
		{
			if (fabs(m_AccelationX) > 0) m_AccelationX = m_AccelationX - m_AccelationX * 0.55f;
			else m_AccelationX = 0;
		}
	}
	
	m_Pos.x += m_AccelationX * (m_AccelationDirect * 2 - 1);
	m_Pos.y += m_AccelationY;

	m_hitBox[0] = XMFLOAT2(m_Pos.x - 30, m_Pos.y + 80);
	m_hitBox[1] = XMFLOAT2(m_Pos.x + 30, m_Pos.y + 10);

	m_head.x = m_Pos.x;
	m_head.y = m_Pos.y + 100;

	if (m_nowHP <= 0)
	{
		ChangeState(PlayerDie::Instance(), this);
	}
	mesDuration(tickTime);
	
	for (int i = 0; i < sizeof(m_skillEffect) / sizeof(Skill*); i++)
	{
		if (m_skillEffect[i]) m_skillEffect[i]->Frame(tickTime);
	}
	for (int i = 0; i < sizeof(m_hitDamage) / sizeof(DamageClass*); i++)
	{
		if(m_hitDamage[i]->nowSprite.m_isRender) m_hitDamage[i]->Frame(tickTime);
	}
	for (int i = 0; i < sizeof(m_attackDamage) / sizeof(DamageClass*); i++)
	{
		if (m_attackDamage[i]->nowSprite.m_isRender) m_attackDamage[i]->Frame(tickTime);
	}
}

void PlayerClass::Flip()
{
	if (m_key[DIK_LEFT]) { m_Flip = false; }
	else if (m_key[DIK_RIGHT]) { m_Flip = true; }

	if (isGrounding()) m_AccelationDirect = m_Flip;
}

bool PlayerClass::isGrounding()
{
	if (m_Pos.y <= -240)
	{
		m_Pos.y = -240.0f;
		return true;
	}
	return false;
}

void PlayerClass::mesDuration(float tickTime)
{
	if (m_PlayerMes != ePlayerMes::NONE)
	{
		m_mesTickTime += tickTime;
		if (m_mesTickTime >= 3000)
		{
			m_PlayerMes = ePlayerMes::NONE;
			m_mesTickTime = 0;
		}
	}
}

void PlayerClass::Shutdown()
{
	ReleaseTexture();
	ShutdownBuffers();
	/*for (int i = 0; i < sizeof(m_skillEffect) / sizeof(Skill*); i++)
	{
		if (m_skillEffect[i])
		{
			m_skillEffect[i]->Shutdown();
			delete m_skillEffect[i];
			m_skillEffect[i] = 0;
		}
	}*/
}



/////////////////////////////////////////////////////////////////
	/*m_boundingBox[0] = XMFLOAT3(m_Pos.x - 30, m_Pos.y + 80, 0.0f);
	m_boundingBox[1] = XMFLOAT3(m_Pos.x + 30, m_Pos.y + 10, 0.0f);
	m_boundingBox[2] = XMFLOAT3(m_Pos.x - 30, m_Pos.y + 10, 0.0f);
	m_boundingBox[3] = XMFLOAT3(m_Pos.x + 30, m_Pos.y + 80, 0.0f);

	if (m_nowPlayerHP <= 0)
	{
		ChangeState(PlayerDie<PlayerClass>::Instance());
		m_nowPlayerHP = 0;
	}

	else if((GetAsyncKeyState(m_HPRecover) & 0x8000) == 0x8000)
	{
		m_nowPlayerHP = m_maxPlayerHP;
	}

	if (m_PlayerMes == ePlayerMes::STUN)
	{
		static int mes_oldtime = GetTickCount();
		int mes_nowtime = GetTickCount64();

		int mes_time = mes_nowtime - mes_oldtime;

		if (mes_time >= 4000)
		{
			mes_oldtime = mes_nowtime;
			m_PlayerMes = ePlayerMes::NONE;
		}
	}*/