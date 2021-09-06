#pragma once
#include "../../Header/stdafx.h"
#include "../FSM/State.h"

class EnemySummon : public State
{
public:
    EnemyClass* e = nullptr;
    static EnemySummon* Instance()
    {
        static EnemySummon* instance = new EnemySummon();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

class EnemyMove : public State
{
private:
    int m_randState = 3;
    void Move(EnemyClass*);
    void Pattern(EnemyClass*);
public:
    EnemyClass* e = nullptr;
    static EnemyMove* Instance()
    {
        static EnemyMove* instance = new EnemyMove();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

class EnemySkill_1 : public State
{
public:
    EnemyClass* e = nullptr;
    static EnemySkill_1* Instance()
    {
        static EnemySkill_1* instance = new EnemySkill_1();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

class EnemySkill_2 : public State
{
public:
    EnemyClass* e = nullptr;
    static EnemySkill_2* Instance()
    {
        static EnemySkill_2* instance = new EnemySkill_2();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

class EnemySkill_3 : public State
{
public:
    EnemyClass* e = nullptr;
    static EnemySkill_3* Instance()
    {
        static EnemySkill_3* instance = new EnemySkill_3();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

class EnemySkill_4 : public State
{
public:
    EnemyClass* e = nullptr;
    static EnemySkill_4* Instance()
    {
        static EnemySkill_4* instance = new EnemySkill_4();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

class EnemySkill_5 : public State
{
public:
    EnemyClass* e = nullptr;
    static EnemySkill_5* Instance()
    {
        static EnemySkill_5* instance = new EnemySkill_5();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

class EnemySkill_6 : public State
{
public:
    EnemyClass* e = nullptr;
    static EnemySkill_6* Instance()
    {
        static EnemySkill_6* instance = new EnemySkill_6();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

class EnemyDie : public State
{
public:
    EnemyClass* e = nullptr;
    static EnemyDie* Instance()
    {
        static EnemyDie* instance = new EnemyDie();
        return instance;
    }

    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};