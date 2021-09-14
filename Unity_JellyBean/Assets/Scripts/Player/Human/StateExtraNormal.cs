using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_ExNormal : StateController<PlayerExtra>
{
    static readonly P_State_ExNormal instance = new P_State_ExNormal();
    public static P_State_ExNormal Instance
    {
        get
        { return instance; }
    }

    static P_State_ExNormal() { }
    private P_State_ExNormal() { }

    public override void EnterState(PlayerExtra P)
    {
        PlayerExtra.C_ExtraState = PlayerExtra.PlayerExtraState.NORMAL;
        Player.ani.SetInteger("ExtraState", (int)PlayerExtra.PlayerExtraState.NORMAL);
    }

    public override void UpdateState(PlayerExtra P)
    {

    }

    public override void ExitState(PlayerExtra P)
    {

    }
}