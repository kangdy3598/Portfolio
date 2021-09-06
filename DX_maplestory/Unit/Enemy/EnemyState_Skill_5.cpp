#pragma once
#include "EnemyState.h"

// µ¶
static int m_attackNumber = 0;
void EnemySkill_5::Enter()
{
	e = (EnemyClass*)ob;
	e->m_EnemyState = EnemyClass::eEnemyState::ATTACK5;
	e->nowSprite = e->sprite[9 + m_attackNumber];
	e->m_isAnimationLoop = false;

	e->m_patternCoolTime[(int)e->m_EnemyState - 1] = 20000;

	e->m_attackStartFrame = 14;
	e->m_attackEndFrame = 16;

	e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x + -200, e->m_Pos.y + 550);
	e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x + 200, e->m_Pos.y + 50);

    switch (m_attackNumber)
    {
    case 0:
        // soundClass.fileName = "../Graphics/data/Enemy/Sound/Attack2.wav";
        e->m_hitStartFrame = 15;
        e->m_hitEndFrame = 25;
        break;
    case 1:
        //soundClass.fileName = "../Graphics/data/Enemy/Sound/Attack3.wav";
        e->m_hitStartFrame = 1;
        e->m_hitEndFrame = 25;
        break;
    case 2:
        //soundClass.fileName = "../Graphics/data/Enemy/Sound/Attack4.wav";
        e->m_hitStartFrame = 1;
        e->m_hitEndFrame = 25;
        break;
    case 3:
        //soundClass.fileName = "../Graphics/data/Enemy/Sound/Attack5.wav";
        e->m_hitStartFrame = 1;
        e->m_hitEndFrame = 25;
        break;
    case 4:
        //soundClass.fileName = "../Graphics/data/Enemy/Sound/Attack6.wav";
        e->m_hitStartFrame = 1;
        e->m_hitEndFrame = 25;
        break;
    }

    e->m_hitBox[0] = XMFLOAT2(e->m_Pos.x - 120, e->m_Pos.y + 280);
    e->m_hitBox[1] = XMFLOAT2(e->m_Pos.x + 180, e->m_Pos.y + 30);

    e->m_head.x = e->m_Pos.x + 300 * (e->m_Flip * 2 - 1);
    e->m_head.y = e->m_Pos.y + 500;
}

void EnemySkill_5::Execute()
{  
    if (e->m_isAnimationEnd)
    {
        switch (m_attackNumber)
        {
        case 0:
        case 1:
        case 2:
            m_attackNumber++;
            e->ChangeState(EnemySkill_5::Instance(), e);
            break;
        case 3:
            m_attackNumber = 0;
            e->ChangeState(EnemyMove::Instance(), e);
            break;
        }
    }

    if (!e->m_frameTrigger && m_attackNumber >= 1 && m_attackNumber <= 3)
    {
        e->m_frameTrigger = true;
        if (e->m_animationFrameCount == 7) e->m_summon = true;
        if (e->m_animationFrameCount == 9) e->m_summon = true;
        if (e->m_animationFrameCount == 14)
        {
            e->m_warningCount++; e->m_warning = true;
        }
    }
}

void EnemySkill_5::Exit()
{
}
