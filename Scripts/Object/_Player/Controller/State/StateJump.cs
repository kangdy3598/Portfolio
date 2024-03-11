using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Jump : StateController<PlayerController>
{
    static readonly P_State_Jump instance = new P_State_Jump();
    public static P_State_Jump Instance
    {
        get
        { return instance; }
    }

    static P_State_Jump() { }
    private P_State_Jump() { }

    private float moveSpeed;
    private float jumpSpeed;

    public override void EnterState(PlayerController P)
    {
        P.stateName = PlayerController.STATENAME.JUMP;
        P.anim.SetInteger("state", 2);

        moveSpeed = 3;
        jumpSpeed = 8;
        Jump(P);
    }

    public override void UpdateState(PlayerController P)
    {
        if (Input.GetKeyDown(KeyCode.F))
        {
            if (Input.GetKey(KeyCode.UpArrow))
            {
                P.Change_State(P_State_DJump.Instance);

            }

            else
            {
                P.Change_State(P_State_DJump.Instance);

            }
        }

        Flip(P);
    }

    public override void FixedUpdateState(PlayerController P)
    {
        if (P.rigid.rigidbody2d.velocity.y < 0)
            P.stateName = PlayerController.STATENAME.LAND;

        if(P.stateName == PlayerController.STATENAME.LAND && P.rigid.GetOnGround())
            P.Change_State(P_State_Idle.Instance);

        Walk(P);
        
    }

    public override void ExitState(PlayerController P)
    {

    }

    private void Jump(PlayerController P)
    {
       if(P.rigid.GetOnGround())
        {
            P.rigid.rigidbody2d.AddForce(Vector2.up * jumpSpeed, ForceMode2D.Impulse);
        }
    }

    //좌우 방향 관련
    private void Flip(PlayerController P)
    {
        SetMoveAccel(P);
        if (Input.GetAxisRaw("Horizontal") == 1)
            P.sprite.flipX = true;
        if (Input.GetAxisRaw("Horizontal") == -1)
            P.sprite.flipX = false;
    }

    //좌우 이동 관련
    private void Walk(PlayerController P)
    {
        P.transform.Translate(moveSpeed * Time.deltaTime * P.moveAccelAmount, 0, 0);
    }

    private void SetMoveAccel(PlayerController P)
    {
        if (Input.GetAxisRaw("Horizontal") == 0)
            return;

        int AxisRawSign = Math.Sign(Input.GetAxisRaw("Horizontal"));
        int moveAccelSign = Math.Sign(P.moveAccelAmount);
        if (AxisRawSign != moveAccelSign)
            return;

        P.moveAccelAmount = Input.GetAxisRaw("Horizontal");
    }
}