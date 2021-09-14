using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Attack : StateController<PlayerUpper>
{
    static readonly P_State_Attack instance = new P_State_Attack();
    public static   P_State_Attack Instance
    {
        get
        {   return instance;   }
    }
    
    static P_State_Attack() { }
    private P_State_Attack() { }

    private float AttackTimer;
    public override void EnterState(PlayerUpper P)
    {
        PlayerUpper.C_UpperState += 1;
        Player.ani.SetInteger("UpperState", (int)PlayerUpper.C_UpperState);
        AttackTimer = 0;
        if (P.transform.name == "[Player2](Clone)")
            P.transform.GetComponent<PlayerUnder>().Change_State(P_State_Idle.Instance);
    }

    public override void UpdateState(PlayerUpper P)
    {
        
        switch (Player.ani.GetCurrentAnimatorClipInfo(0)[0].clip.name)
        {
            case "BoomAttack":
            case "BoomAttack(W)":
            case "BoomAttackUp":
            case "BoomAttackUp(W)":
                AttackTimer += Time.deltaTime;
                if (AttackTimer > 0.35f) P.Change_State(P_State_Normal.Instance);
                break;

            case "AxeAttack":
            case "AxeAttack(W)":
            case "Attack":
            case "JumpAttack":
                if(Player.ani.GetCurrentAnimatorStateInfo(0).normalizedTime > 0.95f)  P.Change_State(P_State_Normal.Instance);
                break;
        }
        
    }
 
    public override void ExitState(PlayerUpper P)
    {
        if (P.transform.name == "[Player1](Clone)") Player.ani.SetBool("IsAxe", false);
    }
}
