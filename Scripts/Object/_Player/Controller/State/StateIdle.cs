using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Idle : StateController<PlayerController>
{
    static readonly P_State_Idle instance = new P_State_Idle();
    public static P_State_Idle Instance
    {
        get { return instance; }
    }

    static P_State_Idle() { }
    private P_State_Idle() { }
    
    public override void EnterState(PlayerController P)
    {
        P.stateName = PlayerController.STATENAME.IDLE;
        P.anim.SetInteger("state",0);

       // P.moveAccelAmount = 0;
    }
 
    public override void UpdateState(PlayerController P)
    {
        if (Input.GetKey(KeyCode.F))
        {
            P.Change_State(P_State_Jump.Instance);
            return;
        }
        if (Input.GetKey(KeyCode.LeftArrow))
            P.Change_State(P_State_Walk.Instance);
        
        if (Input.GetKey(KeyCode.RightArrow))
            P.Change_State(P_State_Walk.Instance);
    }

    public override void FixedUpdateState(PlayerController P)
    {
       
    }
    public override void ExitState(PlayerController P)
    {
        
    }
}
