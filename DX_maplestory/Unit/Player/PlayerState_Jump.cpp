#pragma once
#include "PlayerState.h"
#include "Skill_Swift.h"

static int m_jumpCount = 0;
void PlayerJump::Enter()
{
	p = (PlayerClass*)ob;
	p->m_PlayerState = PlayerClass::ePlayerState::JUMP;
	p->nowSprite = p->sprite[(int)p->m_PlayerState];

	if (InputClass::Instance()->GetKey(p->m_JumpKey)) p->m_AccelationY = 13;
}

void PlayerJump::Execute()
{
	if (m_jumpCount < 2 &&
		(InputClass::Instance()->GetKeyDown(p->m_JumpKey) || InputClass::Instance()->GetKeyDown(0x46))) DoubleJump(p);
	if (p->isGrounding())
	{
		m_jumpCount = 0;  p->ChangeState(PlayerIdle::Instance(), p);
	}
	else p->m_AccelationY -= 0.68f;

	p->Flip();
}

void PlayerJump::Exit()
{
	p->m_AccelationY = 0;
}

//bool PlayerJump::Flip(PlayerClass* p)
//{
//	if (p->m_key[DIK_LEFT])       p->m_Flip = false;
//	else if (p->m_key[DIK_RIGHT]) p->m_Flip = true;
//
//	return p->m_Flip;
//}

void PlayerJump::DoubleJump(PlayerClass* p)
{
	m_jumpCount++;

	int m_count = 0;
	for (int i = 0; i < 15; i++)
	{
		if (m_count < 2 && !p->m_skillEffect[i])
		{
			p->m_skillEffect[i] = new Skill;
			p->m_skillEffect[i]->Initialize(p->m_device);
			p->m_skillEffect[i]->InitAnimation();
			
			p->m_skillEffect[i]->nowSprite.m_isRender = true;
			p->m_skillEffect[i]->m_layerOrder = m_count;

			p->m_skillEffect[i]->m_skill_Swift = new Skill_Swift;
			p->m_skillEffect[i]->m_skill_Swift->Initialize(p->m_device, m_count);

			p->m_skillEffect[i]->m_name = L"Swift";
			p->m_skillEffect[i]->nowSprite = p->m_skillEffect[i]->m_skill_Swift->sprite[m_count];
			p->m_skillEffect[i]->m_isAnimationLoop = false;

			m_count++;
		}
	}
	
	p->m_AccelationDirect = p->m_Flip;

	p->m_AccelationX = 8.5f;
	p->m_AccelationY += 3.15f;
}
