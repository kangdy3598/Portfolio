#pragma once
#include "EnemyState.h"

// ±í¼û
static int m_attackNumber = 0;
void EnemySkill_6::Enter()
{
	e = (EnemyClass*)ob;
	e->m_EnemyState = EnemyClass::eEnemyState::ATTACK6;

	e->m_isAnimationLoop = false;

	e->m_patternCoolTime[(int)e->m_EnemyState - 1] = 50000;

	e->m_attackStartFrame = 14;
	e->m_attackEndFrame = 18;

	e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x + -150, e->m_Pos.y + 550);
	e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x + 50, e->m_Pos.y + 50);

	if (!e->m_Flip)
	{
		e->m_hitBox[0] = XMFLOAT2(e->m_Pos.x - 60, e->m_Pos.y + 280);
		e->m_hitBox[1] = XMFLOAT2(e->m_Pos.x + 180, e->m_Pos.y + 50);
	}
	else
	{
		e->m_hitBox[0] = XMFLOAT2(e->m_Pos.x - 40, e->m_Pos.y + 550);
		e->m_hitBox[1] = XMFLOAT2(e->m_Pos.x + 230, e->m_Pos.y + 50);
	}
	switch (m_attackNumber)
	{
	case 0:
		e->nowSprite = e->sprite[13];
		e->m_hitStartFrame = 18;
		e->m_hitEndFrame = 52;
		break;
	case 1:
		e->nowSprite = e->sprite[14];
		e->m_hitStartFrame = 1;
		e->m_hitEndFrame = 12;
		break;
	case 2:
		e->m_hitStartFrame = 1;
		e->m_hitEndFrame = 12;
		break;
	case 3:
		e->m_hitStartFrame = 1;
		e->m_hitEndFrame = 12;
		break;
	case 4:
		e->nowSprite = e->sprite[15];
		e->m_hitStartFrame = 1;
		e->m_hitEndFrame = 7;
		break;
	case 5:
		e->nowSprite = e->sprite[16];
		e->m_hitStartFrame = 1;
		e->m_hitEndFrame = 4;
		break;
	}
}

void EnemySkill_6::Execute()
{
	if (e->m_isAnimationEnd)
	{
		switch (m_attackNumber)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			m_attackNumber++;
			e->ChangeState(EnemySkill_6::Instance(), e);
			break;
		case 5:
			m_attackNumber = 0;
			e->ChangeState(EnemyMove::Instance(), e);
			break;
		}
	}

	if (!e->m_frameTrigger && m_attackNumber == 5)
	{
		e->m_frameTrigger = true;
		if (e->m_animationFrameCount == 1) e->m_summon = true;
	}

}

void EnemySkill_6::Exit()
{
}
