using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class P_State_Slide : StateController<PlayerExtra>
{
    static readonly P_State_Slide instance = new P_State_Slide();
    public static P_State_Slide Instance
    {
        get
        { return instance; }
    }

    private float SlideSpeed, DecelSpeed;

    static P_State_Slide() { }
    private P_State_Slide() { }

    public override void EnterState(PlayerExtra P)
    { 
        SlideSpeed = 12; DecelSpeed = 1.0f;
        
        PlayerExtra.C_ExtraState = PlayerExtra.PlayerExtraState.SLIDE;
        Player.ani.SetInteger("ExtraState", (int)PlayerExtra.PlayerExtraState.SLIDE);

       // P.SlideParticle.Play();
        SoundManager.Instance.PlayerSound(SoundManager.Instance.Slide);
    }

    public override void UpdateState(PlayerExtra P)
    {
        DecelSpeed += 10 * Time.deltaTime;
        Player.trans.Translate((int)Player.trans.localScale.x * (SlideSpeed - DecelSpeed) * Time.deltaTime, 0, 0);
        if (Player.ani.GetCurrentAnimatorStateInfo(0).normalizedTime >= 0.95f)
        {
            P.Change_State(P_State_ExNormal.Instance);
        }

    }

    public override void ExitState(PlayerExtra P)
    {
       // P.SlideParticle.Stop();
    }
}
