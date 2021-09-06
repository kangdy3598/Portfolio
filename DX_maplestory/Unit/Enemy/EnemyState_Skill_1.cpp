#pragma once
#include "EnemyState.h"

// ±ä ¸ñ
void EnemySkill_1::Enter()
{
	e = (EnemyClass*)ob;
	e->m_EnemyState = EnemyClass::eEnemyState::ATTACK1;
	e->nowSprite = e->sprite[1];
	e->m_isAnimationLoop = false;

	e->m_patternCoolTime[(int)e->m_EnemyState - 1] = 10000;

	e->m_attackStartFrame = 14;
	e->m_attackEndFrame = 16;
	e->m_attackDamage = 10;

	e->m_hitStartFrame = 16;
	e->m_hitEndFrame = 26;

	if (!e->m_Flip)
	{
		e->m_hitBox[0] = XMFLOAT2(e->m_Pos.x - 55, e->m_Pos.y + 550);
		e->m_hitBox[1] = XMFLOAT2(e->m_Pos.x + 220, e->m_Pos.y + 50);
		e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x + -50, e->m_Pos.y + 550);
		e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x + 200, e->m_Pos.y + 50);
	}
	else
	{
		e->m_hitBox[0] = XMFLOAT2(e->m_Pos.x - 220, e->m_Pos.y + 550);
		e->m_hitBox[1] = XMFLOAT2(e->m_Pos.x + 55, e->m_Pos.y + 50);
		e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x + -200, e->m_Pos.y + 550);
		e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x + 50, e->m_Pos.y + 50);
	}

	e->m_head.x = e->m_Pos.x + 300 * (e->m_Flip * 2 - 1);
	e->m_head.y = e->m_Pos.y + 500;
}

void EnemySkill_1::Execute()
{
	if (!e->m_frameTrigger)
	{
		e->m_frameTrigger = true;
		if (e->m_animationFrameCount == 14) e->m_summon = true;
	}
	
	if (e->m_isAnimationEnd) e->ChangeState(EnemyMove::Instance(), e);
	
}

void EnemySkill_1::Exit()
{
}
