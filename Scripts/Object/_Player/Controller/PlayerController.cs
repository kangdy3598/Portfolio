using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;

public class PlayerController : MonoBehaviour
{
    public Text text;
    /// <summary>
    /// ///////////////////////////////////////////////
    /// </summary>
    public enum STATENAME
    {
        IDLE,
        WALK,
        JUMP,
        DJUMP,
        LAND,
        DEAD,
    };
    public STATENAME stateName { get; set; }

    public enum STATUSNAME
    {
        NONE,
        STUN,
    };
    public STATUSNAME statusName { get; set; }


    public RigidComponent rigid;
    public Animator anim;
    public SpriteRenderer sprite;

    public GameObject tombstone;
    public float moveAccelAmount;
    //private bool isLookLeft;

    public StateChange<PlayerController> playerState;

    private void Start()
    {
        playerState = new StateChange<PlayerController>();
        playerState.Init_State(this, P_State_Jump.Instance);

        statusName = STATUSNAME.NONE;
        //isLookLeft = true;

        rigid.footholdStayEvent += DecreaseMoveAccel;

        PlayerInfo.Instance.playerHPComp.deadEvent += ChangeStateDead;
        PlayerInfo.Instance.playerHPComp.resurrectionEvent += ChangeStateIdle;
    }

    private void Update()
    {
        playerState.Update_State();
        text.text = stateName.ToString();
    }
    private void FixedUpdate()
    {
        if (statusName == STATUSNAME.NONE)
            playerState.FixedUpdate_State();

        else
            ChangeStateIdle();

    }

    public void Change_State(StateController<PlayerController> State)
    {
        playerState.Change_State(State);

    }

    private void DecreaseMoveAccel()
    {
        moveAccelAmount *= 0.8f;
    }

    private void ChangeStateIdle()
    {
        moveAccelAmount = 0.0f;
        playerState.Change_State(P_State_Idle.Instance);
    }
    private void ChangeStateDead()
    {
        playerState.Change_State(P_State_Dead.Instance);
    }

    public bool IsLookLeft()
    {
        return !sprite.flipX;
    }
}
