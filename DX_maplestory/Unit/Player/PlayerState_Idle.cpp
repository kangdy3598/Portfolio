#pragma once
#include "PlayerState.h"

void PlayerIdle::Enter()
{
	p = (PlayerClass*)ob;
	p->m_PlayerState = PlayerClass::ePlayerState::IDLE;
	p->nowSprite = p->sprite[(int)p->m_PlayerState];

	p->m_AccelationX = 0;
	p->m_AccelationY = 0;
}

void PlayerIdle::Execute()
{
	if (p->m_PlayerMes != PlayerClass::ePlayerMes::STUN)
	{
		if (p->m_key[DIK_LEFT] || p->m_key[DIK_RIGHT]) p->ChangeState(PlayerWalk::Instance(), p);
		if (InputClass::Instance()->GetKeyDown(p->m_AttackKey)) p->ChangeState(PlayerSkill_Ultimate::Instance(), p);
		if (InputClass::Instance()->GetKeyDown(p->m_JumpKey))  p->ChangeState(PlayerJump::Instance(), p);
	}
	
	if (InputClass::Instance()->GetKeyDown(p->m_JumpKey) || !p->isGrounding())  p->ChangeState(PlayerJump::Instance(), p);
	
}

void PlayerIdle::Exit()
{
}
