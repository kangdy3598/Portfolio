using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Normal : StateController<PlayerUpper>
{
    static readonly P_State_Normal instance = new P_State_Normal();
    public static P_State_Normal Instance
    {
        get
        { return instance; }
    }

    static P_State_Normal() { }
    private P_State_Normal() { }

    public override void EnterState(PlayerUpper P)
    {
        PlayerUpper.C_UpperState = PlayerUpper.PlayerUpperState.NORMAL;
        Player.ani.SetInteger("UpperState", (int)PlayerUpper.PlayerUpperState.NORMAL);
    }

    public override void UpdateState(PlayerUpper P)
    {
        
    }

    public override void ExitState(PlayerUpper P)
    {

    }
}