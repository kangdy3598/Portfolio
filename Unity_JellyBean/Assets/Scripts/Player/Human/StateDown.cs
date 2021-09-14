using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Down : StateController<PlayerExtra>
{
    static readonly P_State_Down instance = new P_State_Down();
    public static P_State_Down Instance
    {
        get
        { return instance; }
    }
    
    static P_State_Down() { }
    private P_State_Down() { }

    public override void EnterState(PlayerExtra P)
    {
        PlayerExtra.C_ExtraState = PlayerExtra.PlayerExtraState.DOWN;
        Player.ani.SetInteger("ExtraState", (int)PlayerExtra.PlayerExtraState.DOWN);
        
    }

    public override void UpdateState(PlayerExtra P)
    {
        if (Player.ani.GetCurrentAnimatorClipInfo(0)[0].clip.name == "Down_Off" && 
            Player.ani.GetCurrentAnimatorStateInfo(0).normalizedTime >= 0.95f)
        {
            P.Change_State(P_State_ExNormal.Instance);
        }
    }

    public override void ExitState(PlayerExtra P)
    {

    }

   
}