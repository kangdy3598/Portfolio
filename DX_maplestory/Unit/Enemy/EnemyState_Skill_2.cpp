#pragma once
#include "EnemyState.h"

// 불
static int m_attackNumber = 0;
void EnemySkill_2::Enter()
{
	e = (EnemyClass*)ob;
	e->m_EnemyState = EnemyClass::eEnemyState::ATTACK2;
	e->nowSprite = e->sprite[2 + m_attackNumber];
	e->m_isAnimationLoop = false;

    e->m_patternCoolTime[(int)e->m_EnemyState - 1] = 25000;

#pragma region 충돌 상자
	 e->m_hitBox[0] = XMFLOAT2(e->m_Pos.x - 120, e->m_Pos.y + 280);
     e->m_hitBox[1] = XMFLOAT2(e->m_Pos.x + 180, e->m_Pos.y + 30);

     switch (m_attackNumber)
     {
     case 0:
         // soundClass.fileName = "../Graphics/data/Enemy/Sound/Attack2.wav";
         e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x - 150, e->m_Pos.y + 550);
         e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x + 150, e->m_Pos.y + 50);

         e->m_hitStartFrame = 16;
         e->m_hitEndFrame = 26;

         e->m_attackStartFrame = 14;
         e->m_attackEndFrame = 16;
         break;
     case 1:
         //soundClass.fileName = "../Graphics/data/Enemy/Sound/Attack3.wav";
         if (e->m_Flip)
         {
             e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x + 700, e->m_Pos.y + 550);
             e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x + 1050, e->m_Pos.y + 50);
         }
         else
         {
             e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x - 1050, e->m_Pos.y + 550);
             e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x - 700, e->m_Pos.y + 50);
         }

         e->m_hitStartFrame = 1;
         e->m_hitEndFrame = 29;

         e->m_attackStartFrame = 18;
         e->m_attackEndFrame = 22;
         break;
     case 2:
         //soundClass.fileName = "../Graphics/data/Enemy/Sound/Attack4.wav";
         if (e->m_Flip)
         {
             e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x + 600, e->m_Pos.y + 550);
             e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x + 950, e->m_Pos.y + 50);
         }
         else
         {
             e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x - 950, e->m_Pos.y + 550);
             e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x - 600, e->m_Pos.y + 50);
         }
         e->m_hitStartFrame = 1;
         e->m_hitEndFrame = 28;

         e->m_attackStartFrame = 18;
         e->m_attackEndFrame = 22;
         break;
     case 3:
         //soundClass.fileName = "../Graphics/data/Enemy/Sound/Attack5.wav";
         if (e->m_Flip)
         {
             e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x + 300, e->m_Pos.y + 550);
             e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x + 650, e->m_Pos.y + 50);
         }
         else
         {
             e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x - 650, e->m_Pos.y + 550);
             e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x - 300, e->m_Pos.y + 50);
         }
         e->m_hitStartFrame = 1;
         e->m_hitEndFrame = 27;

         e->m_attackStartFrame = 18;
         e->m_attackEndFrame = 22;
         break;
     case 4:
         //soundClass.fileName = "../Graphics/data/Enemy/Sound/Attack6.wav";
         e->m_attackBox[0] = XMFLOAT2(e->m_Pos.x - 150, e->m_Pos.y + 550);
         e->m_attackBox[1] = XMFLOAT2(e->m_Pos.x + 150, e->m_Pos.y + 50);

         e->m_hitStartFrame = 1;
         e->m_hitEndFrame = 5;

         e->m_attackStartFrame = 6;
         e->m_attackEndFrame = 8;
         break;
     }
#pragma endregion

     e->m_head.x = e->m_Pos.x + 300 * (e->m_Flip * 2 - 1);
     e->m_head.y = e->m_Pos.y + 500;
}

void EnemySkill_2::Execute()
{
    if (e->m_isAnimationEnd)
    {
        switch (m_attackNumber)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            m_attackNumber++;
            e->ChangeState(EnemySkill_2::Instance(), e);
            break;
        case 4:
            m_attackNumber = 0;
            e->ChangeState(EnemyMove::Instance(), e);
            break;
        }
    }
    if (!e->m_frameTrigger && m_attackNumber >= 1 && m_attackNumber <= 3)
    {
        e->m_frameTrigger = true;
        if (e->m_animationFrameCount == 2) e->m_summon = true;
    //    if (e->m_animationFrameCount == 16) e->m_summon = true;
    }
}

void EnemySkill_2::Exit()
{
}
