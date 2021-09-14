using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Lookup : StateController<PlayerUpper>
{
    static readonly P_State_Lookup instance = new P_State_Lookup();
    public static P_State_Lookup Instance
    {
        get
        { return instance; }
    }
    
    static P_State_Lookup() { }
    private P_State_Lookup() { }

    public override void EnterState(PlayerUpper P)
    {
        PlayerUpper.C_UpperState = PlayerUpper.PlayerUpperState.LOOKUP;
        Player.ani.SetInteger("UpperState", (int)PlayerUpper.PlayerUpperState.LOOKUP);
    }

    public override void UpdateState(PlayerUpper P)
    {
        if (!Input.GetKey(KeyCode.UpArrow)) P.Change_State(P_State_Normal.Instance);
    }

    public override void ExitState(PlayerUpper P)
    {

    }
}