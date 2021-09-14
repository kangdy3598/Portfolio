using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Idle : StateController<PlayerUnder>
{
    static readonly P_State_Idle instance = new P_State_Idle();
    public static P_State_Idle Instance
    {
        get { return instance; }
    }

    static P_State_Idle() { }
    private P_State_Idle() { }
    
    public override void EnterState(PlayerUnder P)
    {
        PlayerUnder.C_UnderState = PlayerUnder.PlayerUnderState.IDLE;
        Player.ani.SetInteger("UnderState", (int)PlayerUnder.PlayerUnderState.IDLE);
    }
 
    public override void UpdateState(PlayerUnder P)
    {
        
    }
 
    public override void ExitState(PlayerUnder P)
    {

    }
}
