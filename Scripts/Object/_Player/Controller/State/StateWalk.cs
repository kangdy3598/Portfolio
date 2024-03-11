using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Walk : StateController<PlayerController>
{
    static readonly P_State_Walk instance = new P_State_Walk();
    public static P_State_Walk Instance
    {
        get
        { return instance; }
    }

    static P_State_Walk() { }
    private P_State_Walk() { }


    private float moveSpeed;
    public override void EnterState(PlayerController P)
    {
        //  Player.ani.SetInteger("UnderState", (int)PlayerUnder.PlayerUnderState.WALK);
        P.stateName = PlayerController.STATENAME.WALK;
        P.anim.SetInteger("state", 1);

        moveSpeed = 3;
    }

    public override void UpdateState(PlayerController P)
    {
        
        if (P.rigid.rigidbody2d.velocity.y == 0 &&
            !Input.GetKey(KeyCode.LeftArrow) && 
            !Input.GetKey(KeyCode.RightArrow))

            P.Change_State(P_State_Idle.Instance);

        if (Input.GetKey(KeyCode.F))
            P.Change_State(P_State_Jump.Instance);
    }

    public override void FixedUpdateState(PlayerController P)
    {
        Flip(P);
        Walk(P);
    }

    public override void ExitState(PlayerController P)
    {

    }

    //좌우 방향 관련
    private void Flip(PlayerController P)
    {
        P.moveAccelAmount = Input.GetAxisRaw("Horizontal");
        if (Input.GetAxisRaw("Horizontal") == 1)
            P.sprite.flipX = true;
        if (Input.GetAxisRaw("Horizontal") == -1)
            P.sprite.flipX = false;
    }

    //좌우 이동 관련
    private void Walk(PlayerController P)
    {
        P.transform.Translate(moveSpeed * Time.deltaTime * Input.GetAxisRaw("Horizontal"), 0, 0);
    }
}