#pragma once
#include "EnemyState.h"

// Âª¸ñ
void EnemySkill_3::Enter()
{
	e = (EnemyClass*)ob;
	e->m_EnemyState = EnemyClass::eEnemyState::ATTACK3;
	e->nowSprite = e->sprite[7];
	e->m_isAnimationLoop = false;

	e->m_patternCoolTime[(int)e->m_EnemyState - 1] = 4000;

	e->m_attackStartFrame = 14;
	e->m_attackEndFrame = 16;

	e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x - 200, e->m_Pos.y + 550);
	e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x + 200, e->m_Pos.y + 50);

	e->m_hitStartFrame = 15;
	e->m_hitEndFrame = 25;

	e->m_hitBox[0] = XMFLOAT2(e->m_Pos.x - 120, e->m_Pos.y + 280);
    e->m_hitBox[1] = XMFLOAT2(e->m_Pos.x + 180, e->m_Pos.y + 30);

	e->m_head.x = e->m_Pos.x + 300 * (e->m_Flip * 2 - 1);
	e->m_head.y = e->m_Pos.y + 300;
}

void EnemySkill_3::Execute()
{
	if (!e->m_frameTrigger)
	{
		e->m_frameTrigger = true;
		if (e->m_animationFrameCount == 15) e->m_summon = true;
	}

	if (e->m_isAnimationEnd) e->ChangeState(EnemyMove::Instance(), e);

}

void EnemySkill_3::Exit()
{
}
