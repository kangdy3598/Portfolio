using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Walk : StateController<PlayerUnder>
{
    static readonly P_State_Walk instance = new P_State_Walk();
    public static P_State_Walk Instance
    {
        get
        { return instance; }
    }

    static P_State_Walk() { }
    private P_State_Walk() { }

    private float _soundTime = 0;
    public override void EnterState(PlayerUnder P)
    {
        if (PlayerExtra.C_ExtraState != PlayerExtra.PlayerExtraState.DOWN) P.MoveSpeed = 6;
        else P.MoveSpeed = 1;

        if (PlayerUnder.C_UnderState != PlayerUnder.PlayerUnderState.JUMP && PlayerUnder.C_UnderState != PlayerUnder.PlayerUnderState.LAND)
        {
            PlayerUnder.C_UnderState = PlayerUnder.PlayerUnderState.WALK;
            Player.ani.SetInteger("UnderState", (int)PlayerUnder.PlayerUnderState.WALK);
        }
    }

    public override void UpdateState(PlayerUnder P)
    {
        if (PlayerExtra.C_ExtraState < PlayerExtra.PlayerExtraState.SLIDE) Walk(P);
        if (Player.rigid.velocity.y == 0 && !Input.GetKey(KeyCode.LeftArrow) && ! Input.GetKey(KeyCode.RightArrow)) P.Change_State(P_State_Idle.Instance);
    }

    public override void ExitState(PlayerUnder P)
    {

    }

    //좌우 방향 관련
    public void Flip(PlayerUnder P)
    {
        Vector3 scale = Player.trans.localScale;
        if (Input.GetAxisRaw("Horizontal") == 1) scale.x = 1.25f;
        else if (Input.GetAxisRaw("Horizontal") == -1) scale.x = -1.25f;
        Player.trans.localScale = scale;
    }

    //좌우 이동 관련
    public void Walk(PlayerUnder P)
    {
        if(Player.ani.GetCurrentAnimatorClipInfo(0)[0].clip.name != "TransferToSlime" &&
            Player.ani.GetCurrentAnimatorClipInfo(0)[0].clip.name != "TransferToHuman")
        { 
            if (Player.rigid.velocity.y == 0) Flip(P);
            P.transform.Translate(P.MoveSpeed * Time.deltaTime * Input.GetAxisRaw("Horizontal"), 0, 0);

            // 사운드
            if (Player.C_Form == Player.PlayerForm.SLIME)
            {
                _soundTime += Time.deltaTime;
                if (_soundTime > 0.3f)
                {
                    _soundTime = 0;
                    SoundManager.Instance.PlayerSound(SoundManager.Instance.SlimeWalk);
                }
            }
        }
    }
}