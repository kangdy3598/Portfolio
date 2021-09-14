using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerUnder : MonoBehaviour {

    public enum PlayerUnderState
    {
        IDLE,
        WALK,
        JUMP,
        LAND,
    };
    public static PlayerUnderState C_UnderState;
    public StateChange<PlayerUnder> UnderStateChange;
    public float MoveSpeed, JumpSpeed;

    private void Start()
    {
        UnderStateChange = new StateChange<PlayerUnder>();
        UnderStateChange.Init_State(this, P_State_Idle.Instance);
    }
    public virtual void FixedUpdate()
    {
        UnderStateChange.Update_State();
        if (Player.rigid.velocity.y < 0)
        {
            C_UnderState = PlayerUnderState.LAND;
            Player.ani.SetInteger("UnderState", (int)PlayerUnderState.LAND);
        }

    }

    private void Update()
    {
        if (CheckingGround() && C_UnderState == PlayerUnderState.LAND) Change_State(P_State_Idle.Instance);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (PlayerExtra.C_ExtraState != PlayerExtra.PlayerExtraState.ATTACKED)
        {
            if (transform.name == "[Player1](Clone)")
            {
                if (PlayerExtra.C_ExtraState != PlayerExtra.PlayerExtraState.SLIDE)
                    if (Input.GetKey(KeyCode.LeftArrow) || Input.GetKey(KeyCode.RightArrow)) Change_State(P_State_Walk.Instance);

                if (PlayerExtra.C_ExtraState == PlayerExtra.PlayerExtraState.NORMAL && Player.ani.GetInteger("UnderState") <= 1)
                {
                    if (Input.GetKeyDown(KeyCode.Space)) Change_State(P_State_Jump.Instance);
                }
            }
            else
            {
                if (Player.ani.GetCurrentAnimatorClipInfo(0)[0].clip.name != "TransferToSlime" &&
                Player.ani.GetCurrentAnimatorClipInfo(0)[0].clip.name != "TransferToHuman")
                {
                    if (PlayerExtra.C_ExtraState == PlayerExtra.PlayerExtraState.NORMAL && Input.GetKeyDown(KeyCode.Space)) Change_State(P_State_Jump.Instance);
                    if (PlayerUpper.C_UpperState != PlayerUpper.PlayerUpperState.NORMALATTACK)
                    {
                        if (Input.GetKey(KeyCode.LeftArrow) || Input.GetKey(KeyCode.RightArrow)) Change_State(P_State_Walk.Instance);
                        
                    }
                }
            }
        }
    }
    public void Change_State(StateController<PlayerUnder> State)
    {
        UnderStateChange.Change_State(State);
    }
    public bool CheckingGround()
    {
        Vector3 RightFrom, RightTo, LeftFrom, LeftTo;
        RightFrom = LeftFrom = RightTo = LeftTo = transform.position;
        RightFrom.x += 0.15f; RightTo.x += 0.15f; RightTo.y -= 0.3f;
        LeftFrom.x -= 0.1f; LeftTo.x -= 0.1f; LeftTo.y -= 0.3f;

        RaycastHit2D RightRayHit = Physics2D.Raycast(RightFrom, Vector2.down, 0.3f, 1 << LayerMask.NameToLayer("Step"));
        RaycastHit2D LeftRayHit = Physics2D.Raycast(LeftFrom, Vector2.down, 0.3f, 1 << LayerMask.NameToLayer("Step"));

        Debug.DrawLine(RightFrom, RightTo);
        if (LeftRayHit || RightRayHit)
        {
           // JoyStick.b_Jump = false;
            return true;
        }
        else
        {
            return false;
        }
    }
}
