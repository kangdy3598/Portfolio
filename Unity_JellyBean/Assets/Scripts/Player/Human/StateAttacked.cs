using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Attacked : StateController<PlayerExtra>
{
    static readonly P_State_Attacked instance = new P_State_Attacked();
    public static P_State_Attacked Instance
    {
        get
        { return instance; }
    }

    static P_State_Attacked() { }
    private P_State_Attacked() { }

    public override void EnterState(PlayerExtra P)
    {
        PlayerExtra.C_ExtraState = PlayerExtra.PlayerExtraState.ATTACKED;
        Player.ani.SetInteger("ExtraState", (int)PlayerExtra.PlayerExtraState.ATTACKED);

    }

    public override void UpdateState(PlayerExtra P)
    {
        if (0.95f < Player.ani.GetCurrentAnimatorStateInfo(0).normalizedTime)
        {
            P.Change_State(P_State_ExNormal.Instance);
            //PlayerExtra.C_ExtraState = PlayerExtra.PlayerExtraState.NORMAL;
            //Player.ani.SetInteger("ExtraState", (int)PlayerExtra.PlayerExtraState.NORMAL);
        }

    }

    public override void ExitState(PlayerExtra P)
    {
        
    }
}