using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Dead : StateController<PlayerController>
{
    static readonly P_State_Dead instance = new P_State_Dead();
    public static P_State_Dead Instance
    {
        get { return instance; }
    }

    static P_State_Dead() { }
    private P_State_Dead() { }

    public override void EnterState(PlayerController P)
    {
        P.stateName = PlayerController.STATENAME.DEAD;
        P.anim.SetInteger("state", 3);

        P.tombstone.SetActive(true);
    }

    public override void UpdateState(PlayerController P)
    {

    }

    public override void FixedUpdateState(PlayerController P)
    {

    }
    public override void ExitState(PlayerController P)
    {
        P.tombstone.SetActive(false);
    }
}
