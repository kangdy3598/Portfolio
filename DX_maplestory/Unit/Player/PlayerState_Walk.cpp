#include "PlayerState.h"

void PlayerWalk::Enter()
{
	p = (PlayerClass*)ob;
	p->m_PlayerState = PlayerClass::ePlayerState::WALK;
	p->nowSprite = p->sprite[(int)p->m_PlayerState];

	p->m_AccelationX = 3;
	p->m_isMove = true;
}

void PlayerWalk::Execute()
{
	if (!p->m_key[DIK_LEFT] && !p->m_key[DIK_RIGHT]) p->ChangeState(PlayerIdle::Instance(), p);
	if (InputClass::Instance()->GetKeyDown(p->m_JumpKey)) p->ChangeState(PlayerJump::Instance(), p);
	if (InputClass::Instance()->GetKeyDown(p->m_AttackKey)) p->ChangeState(PlayerSkill_Ultimate::Instance(), p);
	//HorizonMove(p, Flip(p));
	
	p->Flip();
}

void PlayerWalk::Exit()
{
	//p->m_AccelationX = 0;
	p->m_isMove = false;
}

void PlayerWalk::HorizonMove(PlayerClass* p, bool Flip)
{
	//if(Flip) p->m_Pos.x += p->m_AccelationX;
	//else	 p->m_Pos.x -= p->m_AccelationX;
}