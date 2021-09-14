using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerExtra : MonoBehaviour
{
    public enum PlayerExtraState
    {
        NORMAL,
        DOWN,
        SLIDE,
        ATTACKED
    };
    public static PlayerExtraState C_ExtraState;
    public StateChange<PlayerExtra> ExtraStateChange;

    private void Start()
    {
        ExtraStateChange = new StateChange<PlayerExtra>();
        ExtraStateChange.Init_State(this, P_State_ExNormal.Instance);
    }
    public virtual void FixedUpdate()
    {
        ExtraStateChange.Update_State();
    }

    private void Update()
    {
        if (Input.GetKey(KeyCode.DownArrow))
        {
            if (PlayerUnder.C_UnderState <= PlayerUnder.PlayerUnderState.WALK && PlayerUpper.C_UpperState == PlayerUpper.PlayerUpperState.NORMAL)
            {
                if (Input.GetKeyDown(KeyCode.Space)) Change_State(P_State_Slide.Instance);
                else if (C_ExtraState < PlayerExtraState.SLIDE) Change_State(P_State_Down.Instance);
            }
        }
        else 
        {
            if (C_ExtraState <= PlayerExtraState.DOWN)
            {
                Change_State(P_State_ExNormal.Instance);
            }
        }
    }
    public void Change_State(StateController<PlayerExtra> State)
    {
        ExtraStateChange.Change_State(State);
    }
    
}
