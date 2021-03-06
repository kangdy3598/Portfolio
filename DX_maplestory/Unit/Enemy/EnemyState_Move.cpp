#pragma once
#include "EnemyState.h"

void EnemyMove::Enter()
{
	e = (EnemyClass*)ob;
	e->m_EnemyState = EnemyClass::eEnemyState::MOVE;
	e->nowSprite = e->sprite[0];
    e->m_isAnimationLoop = true;

    e->Flip();
    e->m_hitStartFrame = e->m_hitEndFrame = 0;
    e->m_attackStartFrame = e->m_attackEndFrame = 0;

    if ((float)e->m_nowHP / e->m_maxHP < 0.8f)
    {
        m_randState = 4;
    }
    if ((float)e->m_nowHP / e->m_maxHP < 0.6f)
    {
        m_randState = 5;
    }
    //if ((float)e->m_nowHP / e->m_maxHP < 0.4f)
    //{
    //    m_randState = 6;
    //}

    if ((float)e->m_nowHP<= 0)
    {
        e->ChangeState(EnemyDie::Instance(), e);
    }

    e->m_Pos.y = -270;
}

void EnemyMove::Execute()
{
    Move(e);
    Pattern(e);
}

void EnemyMove::Exit()
{
}

void EnemyMove::Move(EnemyClass* e)
{

    if (PlayerClass::Instance()->m_Pos.x >= e->m_Pos.x)
    {
        e->m_Flip = true;
        e->m_Pos.x += e->m_AccelationX;
    }
    else
    {
        e->m_Flip = false;
        e->m_Pos.x -= e->m_AccelationX;
    }
}

void EnemyMove::Pattern(EnemyClass* e)
{
    srand((unsigned)time(NULL));
    int m_nowState = rand() % m_randState + 1;

    if (!e->m_patternCoolTime[m_nowState - 1])
    {
        e->m_Pos.y = -280;
        switch (m_nowState)
        {
        case 1: // ???? : ??Ÿ?? 10??
            e->ChangeState(EnemySkill_1::Instance(), e);
            break;
        case 2: // ?? : ??Ÿ?? 25??
            e->ChangeState(EnemySkill_2::Instance(), e);
            break;
        case 3: // ª?? : ??Ÿ?? 4??
            e->ChangeState(EnemySkill_3::Instance(), e);
            break;
        case 4: // ???̺? : ??Ÿ?? 30??
            e->ChangeState(EnemySkill_4::Instance(), e);
            break;
        case 5: // ?? : ??Ÿ?? 20??
            e->ChangeState(EnemySkill_5::Instance(), e);
            break;
        case 6: // ???? : ??Ÿ?? 50??
            e->ChangeState(EnemySkill_6::Instance(), e);
            break;
        }
    }
    
}