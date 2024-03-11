using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_DJump : StateController<PlayerController>
{
    static readonly P_State_DJump instance = new P_State_DJump();
    public static P_State_DJump Instance
    {
        get { return instance; }
    }

    static P_State_DJump() { }
    private P_State_DJump() { }

    private Vector2 djumpSpeed;
    public override void EnterState(PlayerController P)
    {
        P.stateName = PlayerController.STATENAME.DJUMP;
        P.anim.SetInteger("state", 2);

        if(P.IsLookLeft())
            djumpSpeed.x = -5;
        else
            djumpSpeed.x = 5;
        djumpSpeed.y = 3;

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
