#pragma once
#include "EnemyState.h"

void EnemySummon::Enter()
{
	e = (EnemyClass*)ob;
	e->m_EnemyState = EnemyClass::eEnemyState::SUMMON;
	e->LoadSprite();
	e->nowSprite = e->sprite[1];

	e->m_isAnimationLoop = false;

	e->m_hitBox[0] = XMFLOAT2(0, 0);
	e->m_hitBox[1] = XMFLOAT2(0, 0);
}

void EnemySummon::Execute()
{
	if (e->m_isAnimationEnd) e->ChangeState(EnemyMove::Instance(), e);
}

void EnemySummon::Exit()
{
}
