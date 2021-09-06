#pragma once
//#ifndef PLAYER_STATES_H
//#define PLAYER_STATES_H

#include "../../Header/stdafx.h"
#include "../FSM/State.h"
//#include "PlayerClass.h"

//#include "Skill_Swift.h"
#include "SkillEffect.h"
//#include "../../Class/SoundManager.h"

//class PlayerClass;
//class EnemyClass;
//class SoundClass;
//SoundClass _soundClass;
//
///*template <typename T>*/ class PlayerIdle;
///*template <typename T>*/ class PlayerMove;
///*template <typename T>*/ class PlayerSkill_Ultimate;
///*template <typename T>*/ class PlayerDie;
//
//bool m_bFlip = false;
//void VerticalMove(PlayerClass*);
//void HorizonMove(PlayerClass*);

//class PlayerState : public PlayerClass
//{
//public:
//    class Idle : public State
//    {
//    public:
//
//        static Idle* Instance()
//        {
//            static Idle instance;
//            return &instance;
//        }
//        virtual void Enter();
//        virtual void Execute();
//        virtual void Exit();
//    };
//    // move 
//    // attack
//    // skill_1
//    // ... etc
//};

// Execute() 함수에선 그 상태에 행동할 코드를 ChangeState()함수보다 위에 적을 것
class PlayerIdle : public State
{
public:
    PlayerClass* p = nullptr;
    static PlayerIdle* Instance()
    {
        static PlayerIdle* instance = new PlayerIdle();
        return instance;
    }
    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

class PlayerWalk : public State
{
private:
    void HorizonMove(PlayerClass* p, bool Flip);

public:
    PlayerClass* p = nullptr;
    static PlayerWalk* Instance()
    {
        static PlayerWalk* instance = new PlayerWalk();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

class PlayerJump : public State
{
private:
    void DoubleJump(PlayerClass* p);

public:
    PlayerClass* p = nullptr;
    static PlayerJump* Instance()
    {
        static PlayerJump* instance = new PlayerJump();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

class PlayerSkill_Ultimate : public State
{
private:

public:
    PlayerClass* p = nullptr;
    static PlayerSkill_Ultimate* Instance()
    {
        static PlayerSkill_Ultimate* instance = new PlayerSkill_Ultimate();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

class PlayerDie : public State
{
private:

public:
    PlayerClass* p = nullptr;
    static PlayerDie* Instance()
    {
        static PlayerDie* instance = new PlayerDie();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};
//static Idle* Instance()
//{
//    static Idle instance;
//    return &instance;
//}
//
//virtual void Enter()
//{
//    /*p->m_isAnimationLoop = true;
//    p->m_isAnimationEnd = false;
//
//    p->m_PlayerState = PlayerClass::ePlayerState::IDLE;*/
//    //p->LoadTexture(p->m_device, L"../Graphics/data/Player/Stand.dds", 150, 86, 300, 2, 4, 500);
//}
//
//virtual void Execute()
//{
//    /* if (p->m_PlayerMes != PlayerClass::ePlayerMes::STUN)
//     {
//         if (((GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000) ||
//             ((GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000) ||
//             ((GetAsyncKeyState(p->m_JumpKey) & 0x8000) == 0x8000))
//             p->ChangeState(PlayerMove<PlayerClass>::Instance());
//
//     }
//
//     if ((GetAsyncKeyState(p->m_AttackKey) & 0x8000) == 0x8000)
//     {
//         p->ChangeState(PlayerSkill_Ultimate<PlayerClass>::Instance());
//
//     }*/
//
//
//}
//
//virtual void Exit()
//{
//
//}
////template <typename T>
//class PlayerMove : public State
//{
//private:
//    PlayerMove() {}
//
//    PlayerMove(const PlayerMove&);
//    PlayerMove& operator=(const PlayerMove&);
//
//public:
//    static PlayerMove* Instance()
//    {
//        static PlayerMove instance;
//        return &instance;
//    }
//
//    virtual void Enter()
//    {
//        //p->m_isAnimationLoop = true;
//        //p->m_isAnimationEnd = false;
//
//      //  p->LoadTexture(p->m_device, L"../Graphics/data/Player/Walk.dds", 150, 86, 300, 2, 4, 140);
//    }
//
//    virtual void Execute()
//    {
//        /*p->m_Pos.y += p->m_Accelation;
//        if (p->m_PlayerMes != PlayerClass::ePlayerMes::STUN)
//        {
//            if (p->m_Pos.y > -240)
//            {
//                p->ChangeState(PlayerMove<PlayerClass>::Instance());
//                HorizonMove(p);
//            }
//            else
//            {
//                VerticalMove(p);
//                if ((GetAsyncKeyState(p->m_AttackKey) & 0x8000) == 0x8000)
//                {
//                    p->ChangeState(PlayerSkill_Ultimate<PlayerClass>::Instance());
//                }
//            }
//        }    
//        else
//        {
//            if (p->m_Pos.y > -240)
//            {
//                p->m_Accelation -= 0.95f;
//            }
//            else
//            {
//                p->ChangeState(PlayerIdle<PlayerClass>::Instance());
//            }
//           
//        }*/
//    }
//
//    virtual void Exit()
//    {
//
//    }
//};
//
////template <typename T>
//class PlayerSkill_Ultimate : public State
//{
//private:
//    PlayerSkill_Ultimate() {}
//
//    PlayerSkill_Ultimate(const PlayerSkill_Ultimate&);
//    PlayerSkill_Ultimate& operator=(const PlayerSkill_Ultimate&);
//
//public:
//    static PlayerSkill_Ultimate* Instance()
//    {
//        static PlayerSkill_Ultimate instance;
//        return &instance;
//    }
//
//    virtual void Enter()
//    {
//        //p->m_PlayerState = PlayerClass::ePlayerState::ATTACK;
//        //p->m_Effect[0]->m_attackTickTime = 300;
//
//        //p->m_isAnimationLoop = true;
//        //p->m_isAnimationEnd = false;
//
//       //p->m_Effect[1]->m_isAnimationEnd = false;
//       // p->m_Effect[1]->m_animationFrameCount = 1;
//       // p->m_Effect[1]->m_animationX = p->m_Effect[1]->m_animationY = 1;
//        
//        //p->m_Effect[2]->m_isAnimationLoop = true;
//        //p->m_Effect[2]->m_isAnimationEnd = false;
//        //p->m_Effect[2]->m_animationFrameCount = 1;
//        //p->m_Effect[2]->m_animationX = p->m_Effect[2]->m_animationY = 1;
//
//        //p->m_Effect[2]->LoadTexture(p->m_device, L"../Graphics/data/Player/Ultimate/Ultimate_Hit.dds",
//        //    212, 229, 1272, 256, 6, 6, 30, 0.5f, 1.0f, true);
//
//        //switch (p->m_Effect[1]->m_keydownNumber)
//        //{
//        //case 1:
//        //    p->m_Effect[1]->m_isAnimationLoop = false;
//        //    p->m_Effect[1]->LoadTexture(p->m_device, L"../Graphics/data/Player/Ultimate/ultimate_pre1.dds",
//        //        305, 123, 2048, 256, 5, 5, 45, 0.55f, 0.82f);
//        //    p->LoadTexture(p->m_device, L"../Graphics/data/Player/Ultimate_Pre.dds", 150, 86, 300, 2, 4, 50);
//        //    break;
//
//        //case 2:
//        //    p->m_Effect[1]->m_isAnimationLoop = true;
//        //    p->m_Effect[1]->LoadTexture(p->m_device, L"../Graphics/data/Player/Ultimate/ultimate_keydown1.dds", 
//        //        164, 116, 1024, 116, 6, 6, 45, 0.25f, 1.22f);
//        //    p->LoadTexture(p->m_device, L"../Graphics/data/Player/Ultimate_Keydown.dds", 150, 86, 512, 3, 6, 50);
//        //    p->m_Effect[0]->LoadTexture(p->m_device, L"../Graphics/data/Player/Ultimate/ultimate_keydown.dds", 
//        //        376, 256, 2256, 256, 6, 6, 50, 0.8f, 0.45f);
//
//        //    _soundClass.fileName = "../Graphics/data/Player/Ultimate/Loop.wav";
//        //    _soundClass.CreateEffectSound(1, &_soundClass.fileName);
//        //    //_soundClass.PlaySoundEffect(0);
//        //    break;
//        //case 3:
//        //    p->m_Effect[1]->m_isAnimationLoop = false;
//        //    p->m_Effect[1]->LoadTexture(p->m_device, L"../Graphics/data/Player/Ultimate/ultimate_end.dds",
//        //        175, 120, 1024, 120, 5, 5, 45, 0.29f, 0.82f);
//        //    p->LoadTexture(p->m_device, L"../Graphics/data/Player/Ultimate_Pre.dds", 150, 86, 300, 2, 4, 50);
//        //    break;
//        //}
//        
//        //
//    }
//
//    virtual void Execute()
//    {
//       // static int oldtime = GetTickCount();
//        ////int nowtime = GetTickCount64();
//        //int time = nowtime - oldtime;
//
//        //if (time >= p->m_Effect[0]->m_attackTickTime) oldtime = nowtime;
//        //if (oldtime == nowtime)
//        //{
//        // //   _soundClass.fileName = "../Graphics/data/Player/Ultimate/Loop.wav";
//        // //   _soundClass.CreateEffectSound(1, &_soundClass.fileName);
//        //    _soundClass.PlaySoundEffect(0);
//        //}
//        //
//        //switch (p->m_Effect[1]->m_keydownNumber)
//        //{
//        //case 1:
//        //    if (p->m_Effect[1]->m_isAnimationEnd)
//        //    {
//        //        if ((GetAsyncKeyState(p->m_AttackKey) & 0x8001) == 0x0000)
//        //        {
//        //            p->m_Effect[1]->m_keydownNumber = 3;
//        //            p->ChangeState(PlayerSkill_Ultimate<PlayerClass>::Instance());
//        //        }
//        //        else
//        //        {
//        //            p->m_Effect[1]->m_keydownNumber = 2;
//        //            p->ChangeState(PlayerSkill_Ultimate<PlayerClass>::Instance());
//        //        }
//        //        
//        //    }
//        //    break;
//        //case 2:
//        //    VerticalMove(p);
//        //    if ((GetAsyncKeyState(p->m_AttackKey) & 0x8001) == 0x0000)
//        //    {
//        //        p->m_Effect[1]->m_keydownNumber = 3;
//        //        p->ChangeState(PlayerSkill_Ultimate<PlayerClass>::Instance());
//        //    }
//        //    break;
//        //case 3:
//        //    if (p->m_Effect[1]->m_isAnimationEnd)
//        //    {
//        //        p->m_Effect[1]->m_keydownNumber = 1;
//        //        p->ChangeState(PlayerIdle<PlayerClass>::Instance());
//        //    }
//        //    break;
//        //}
//
//        /*if (p->m_PlayerMes == PlayerClass::ePlayerMes::STUN)
//        {
//            p->ChangeState(PlayerIdle<PlayerClass>::Instance());
//        }*/
//    }
//
//    virtual void Exit()
//    {
//
//    }
//};
//
////template <typename T>
//class PlayerDie : public State
//{
//private:
//    PlayerDie() {}
//
//public:
//    static PlayerDie* Instance()
//    {
//        static PlayerDie instance;
//        return &instance;
//    }
//
//    virtual void Enter()
//    {
//        /*p->m_isAnimationLoop = true;
//        p->m_isAnimationEnd = false;
//        p->m_Pos.y = -230;
//
//        p->m_PlayerState = PlayerClass::ePlayerState::DIE;
//        p->LoadTexture(p->m_device, L"../Graphics/data/Player/Dead.dds", 46, 69, 256, 1, 1, 500);*/
//    }
//
//    virtual void Execute()
//    {
//        /*if (p->m_bResurrection)
//        {
//            p->ChangeState(PlayerMove<PlayerClass>::Instance());
//            p->m_nowPlayerHP = p->m_maxPlayerHP;
//            p->m_bResurrection = false;
//        }*/
//            
//    }
//
//    virtual void Exit()
//    {
//
//    }
//};
//
//void VerticalMove(PlayerClass* p)
//{
//    //p->m_Pos.y = -240; // 
//    //p->m_Accelation = 0;
//    //p->m_moveAccelation = 0;
//
//    //if ((GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000)
//    //{
//    //    if (p->m_PlayerState != PlayerClass::ePlayerState::ATTACK)
//    //    {
//    //        p->m_PlayerState = PlayerClass::ePlayerState::WALK;
//    //        p->LoadTexture(p->m_device, L"../Graphics/data/Player/Walk.dds", 150, 86, 300, 2, 4, 140);
//    //    }
//    //        
//    //    p->m_moveAccelation = 3;
//    //    p->m_Pos.x -= p->m_moveAccelation; // 속력
//    //    p->m_Flip = FALSE;
//    //  //  p->m_Direction = 1;
//    //}
//
//    //else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000)
//    //{
//    //    if (p->m_PlayerState != PlayerClass::ePlayerState::ATTACK)
//    //    {
//    //        p->m_PlayerState = PlayerClass::ePlayerState::WALK;
//    //        p->LoadTexture(p->m_device, L"../Graphics/data/Player/Walk.dds", 150, 86, 300, 2, 4, 140);
//    //    }
//    //        
//    //    p->m_moveAccelation = 3;
//    //    p->m_Pos.x += p->m_moveAccelation; // 속력
//    //    p->m_Flip = TRUE;
//    //   // p->m_Direction = -1;
//    //}
//
//    //else if (p->m_PlayerState == PlayerClass::ePlayerState::WALK || 
//    //         p->m_PlayerState == PlayerClass::ePlayerState::JUMP ||
//    //         p->m_PlayerState == PlayerClass::ePlayerState::DOUBLEJUMP)
//    //{
//    //    if ((GetAsyncKeyState(VK_LEFT) & 0x8001) == 0x0000 ||
//    //        (GetAsyncKeyState(VK_RIGHT) & 0x8001) == 0x0000)
//    //    {
//    //        //p->ChangeState(PlayerIdle<PlayerClass>::Instance());
//    //    }
//    //}
//
//    //if ((GetAsyncKeyState(p->m_JumpKey) & 0x8000) == 0x8000)
//    //{
//    //    p->m_Accelation += 16;
//    //    m_bFlip = p->m_Flip;
//    //}
//    
//}
//
//void HorizonMove(PlayerClass* p)
//{
//    //p->LoadTexture(p->m_device, L"../Graphics/data/Player/Jump.dds", 150, 86, 256, 1, 1, 100);
//
//    //p->m_Accelation -= 0.95f;
//    //p->m_Pos.x += m_bFlip == TRUE ? p->m_moveAccelation : -p->m_moveAccelation;
//
//    //if ((GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000)
//    //{
//    //   // p->m_Direction = 1;
//    //    p->m_Flip = FALSE;
//    //}
//
//    //else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000)
//    //{
//    //  //  p->m_Direction = -1;
//    //    p->m_Flip = TRUE;
//    //}
//
//    //if (p->m_PlayerState != PlayerClass::ePlayerState::DOUBLEJUMP)
//    //{
//    //    p->m_PlayerState = PlayerClass::ePlayerState::JUMP;
//    //    if ((GetAsyncKeyState(p->m_JumpKey) & 0x0001))
//    //    {
//    //        p->m_PlayerState = PlayerClass::ePlayerState::DOUBLEJUMP;
//    //        p->m_Accelation += 3;
//    //        p->m_moveAccelation = 9;
//    //        m_bFlip = p->m_Flip;
//    //    }
//    //}
//}

//#endif

