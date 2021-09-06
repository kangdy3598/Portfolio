#pragma once
#include "PlayerState.h"

void PlayerDie::Enter()
{
	p = (PlayerClass*)ob;
	p->m_PlayerState = PlayerClass::ePlayerState::DIE;
	p->nowSprite = p->sprite[(int)p->m_PlayerState];

	p->m_nowHP = 0;
	p->m_Pos.y = -240.0f;
}

void PlayerDie::Execute()
{

}

void PlayerDie::Exit()
{
}
