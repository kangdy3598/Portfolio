#pragma once
#include "EnemyState.h"

void EnemyDie::Enter()
{
	e = (EnemyClass*)ob;
	e->m_EnemyState = EnemyClass::eEnemyState::DIE;
	e->nowSprite = e->sprite[17];

	e->m_isAnimationLoop = false;

	e->m_hitBox[0] = XMFLOAT2(0, 0);
	e->m_hitBox[1] = XMFLOAT2(0, 0);
}

void EnemyDie::Execute()
{
	
}

void EnemyDie::Exit()
{
}
