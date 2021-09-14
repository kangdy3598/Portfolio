using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Jump : StateController<PlayerUnder>
{
    static readonly P_State_Jump instance = new P_State_Jump();
    public static P_State_Jump Instance
    {
        get
        { return instance; }
    }

    static P_State_Jump() { }
    private P_State_Jump() { }

    public override void EnterState(PlayerUnder P)
    {
        P.JumpSpeed = 20; if (Player.C_Form == Player.PlayerForm.SLIME) P.JumpSpeed += 5;

        PlayerUnder.C_UnderState = PlayerUnder.PlayerUnderState.JUMP;
        Player.ani.SetInteger("UnderState", (int)PlayerUnder.PlayerUnderState.JUMP);
    }

    public override void UpdateState(PlayerUnder P)
    {
        Jump(P);
        
    }

    public override void ExitState(PlayerUnder P)
    {

    }

    public void Jump(PlayerUnder P)
    {
        if (P.CheckingGround() && Player.rigid.velocity.y <= 0) // 1단 점프만 계속되기 위해
        {
            Player.rigid.AddForce(new Vector2(0, P.JumpSpeed), ForceMode2D.Impulse); // 점프

            //사운드
            if (Player.C_Form == Player.PlayerForm.HUMAN) SoundManager.Instance.PlayerSound(SoundManager.Instance.Jump);

            else SoundManager.Instance.PlayerSound(SoundManager.Instance.SlimeJump);
        }
    }
}