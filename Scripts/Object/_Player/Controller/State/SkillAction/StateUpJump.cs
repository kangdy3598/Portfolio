using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_UJump : StateController<PlayerController>
{
    static readonly P_State_UJump instance = new P_State_UJump();
    public static P_State_UJump Instance
    {
        get { return instance; }
    }

    static P_State_UJump() { }
    private P_State_UJump() { }

    private Vector2 djumpSpeed;
    public override void EnterState(PlayerController P)
    {
        P.stateName = PlayerController.STATENAME.DJUMP;
        P.anim.SetInteger("state", 2);

        DJump(P);
    }

    public override void UpdateState(PlayerController P)
    {
        if (P.rigid.rigidbody2d.velocity.y < 0)
            P.stateName = PlayerController.STATENAME.LAND;

        if (P.stateName == PlayerController.STATENAME.LAND && P.rigid.GetOnGround())
            P.Change_State(P_State_Idle.Instance);


    }

    public override void FixedUpdateState(PlayerController P)
    {

    }
    public override void ExitState(PlayerController P)
    {

    }

    private void DJump(PlayerController P)
    {
        P.rigid.rigidbody2d.AddForce(djumpSpeed, ForceMode2D.Impulse);
    }

    //좌우 방향 관련
    private void Flip(PlayerController P)
    {
        //  P.moveAxisRaw = Input.GetAxisRaw("Horizontal");
        if (Input.GetAxisRaw("Horizontal") == 1)
            P.sprite.flipX = true;
        if (Input.GetAxisRaw("Horizontal") == -1)
            P.sprite.flipX = false;
    }

}
