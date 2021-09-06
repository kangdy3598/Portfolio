#pragma once
#include "PlayerState.h"
#include "Skill_Ultimate.h"

static int m_attackNumber = 0;
void PlayerSkill_Ultimate::Enter()
{
	p = (PlayerClass*)ob;
	p->m_PlayerState = PlayerClass::ePlayerState::ATTACK;

    int m_count = 0;
    for (int i = 0; i < 15; i++)
    {
        if (m_count < 2 && !p->m_skillEffect[i])
        {
            p->m_skillEffect[i] = new Skill;
            p->m_skillEffect[i]->Initialize(p->m_device);
            p->m_skillEffect[i]->InitAnimation();
            p->m_skillEffect[i]->nowSprite.m_isRender = true;
            p->m_skillEffect[i]->m_layerOrder = m_count;

            p->m_skillEffect[i]->m_skill_Ultimate = new Skill_Ultimate;
            p->m_skillEffect[i]->m_skill_Ultimate->Initialize(p->m_device, m_count);

            p->m_skillEffect[i]->m_name = L"Ultimate";
            switch (m_attackNumber)
            {
            case 0:
                p->nowSprite = p->sprite[3];

                if (m_count == 1)
                {
                    p->m_skillEffect[i]->nowSprite = p->m_skillEffect[i]->m_skill_Ultimate->sprite[1];
                    p->m_skillEffect[i]->m_isAnimationLoop = false;
                }
                
                break;
            case 1:
                p->m_isMove = true;
                p->nowSprite = p->sprite[(int)p->m_PlayerState];

                if (m_count == 0)
                {
                    p->m_skillEffect[i]->nowSprite = p->m_skillEffect[i]->m_skill_Ultimate->sprite[0];
                    p->m_skillEffect[i]->m_isAnimationLoop = true;
                }
                
                else if(m_count == 1)
                {
                    p->m_skillEffect[i]->nowSprite = p->m_skillEffect[i]->m_skill_Ultimate->sprite[2];
                    p->m_skillEffect[i]->m_isAnimationLoop = true;
                }
                
                break;
            case 2:
                p->nowSprite = p->sprite[3];

                if (m_count == 0)
                {
                    p->m_skillEffect[i]->nowSprite.m_img = nullptr;
                }
                
                else if (m_count == 1)
                {
                    p->m_skillEffect[i]->nowSprite = p->m_skillEffect[i]->m_skill_Ultimate->sprite[3];
                    p->m_skillEffect[i]->m_isAnimationLoop = false;
                }
                break;
            }
            m_count++;
        }
    }
}

void PlayerSkill_Ultimate::Execute()
{
    p->Flip();
   // p->m_Effect->Flip(p);

    switch (m_attackNumber)
    {
    case 0:
        
        if (!InputClass::Instance()->GetKey(p->m_AttackKey))
        {
            m_attackNumber = 2;
            p->ChangeState(PlayerSkill_Ultimate::Instance(), p);
        }
        else if (p->m_isAnimationEnd)
        {
            m_attackNumber++;
            p->ChangeState(PlayerSkill_Ultimate::Instance(), p);
        }
        break;
    case 1:
        if (InputClass::Instance()->GetKeyUp(p->m_AttackKey))
        {
            m_attackNumber = 2;
            p->ChangeState(PlayerSkill_Ultimate::Instance(), p);
        }
        if (p->m_key[DIK_LEFT] || p->m_key[DIK_RIGHT]) p->m_AccelationX = 3;
        else p->m_AccelationX = 0;

        break;

    case 2:
        if (p->m_isAnimationEnd)
        {
            m_attackNumber = 0;
            p->ChangeState(PlayerIdle::Instance(), p);
        }
        break;
    }

    
}

void PlayerSkill_Ultimate::Exit()
{
    p->m_isMove = false;

    int m_count = 0;
    for (int i = 0; i < 15; i++)
    {
        if (m_count < 2 && p->m_skillEffect[i] != NULL)
        {
            if (p->m_skillEffect[i])
            {
                p->m_skillEffect[i]->m_attackBox[0] = XMFLOAT2(0, 0);
                p->m_skillEffect[i]->m_attackBox[1] = XMFLOAT2(0, 0);
                p->m_skillEffect[i]->Shutdown();
                delete p->m_skillEffect[i];
                p->m_skillEffect[i] = 0;

                m_count++;
            }
        }
    }
}
