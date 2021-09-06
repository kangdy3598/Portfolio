#pragma once
#include "EnemyState.h"

// ´ÙÀÌºê
void EnemySkill_4::Enter()
{
	e = (EnemyClass*)ob;
	e->m_EnemyState = EnemyClass::eEnemyState::ATTACK4;
	e->nowSprite = e->sprite[8];
	e->m_isAnimationLoop = false;

	e->m_patternCoolTime[(int)e->m_EnemyState - 1] = 30000;

	e->m_attackStartFrame = 22;
	e->m_attackEndFrame = 27;

	e->m_hitStartFrame = 21;
	e->m_hitEndFrame = 27;

	if (!e->m_Flip)
	{
		e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x + -950, e->m_Pos.y + 350);
		e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x + 150, e->m_Pos.y + 50);

		e->m_hitBox[0] = XMFLOAT2(e->m_Pos.x - 55, e->m_Pos.y + 550);
		e->m_hitBox[1] = XMFLOAT2(e->m_Pos.x + 220, e->m_Pos.y + 50);
	}
	else
	{
		e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x + -150, e->m_Pos.y + 350);
		e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x + 950, e->m_Pos.y + 50);

		e->m_hitBox[0] = XMFLOAT2(e->m_Pos.x - 40, e->m_Pos.y + 550);
		e->m_hitBox[1] = XMFLOAT2(e->m_Pos.x + 230, e->m_Pos.y + 50);
	}
}

void EnemySkill_4::Execute()
{
	e->m_head.x = e->m_Pos.x - 300;
	e->m_head.y = e->m_Pos.y + 500;
	if (e->m_isAnimationEnd) e->ChangeState(EnemyMove::Instance(), e);

}

void EnemySkill_4::Exit()
{
}
