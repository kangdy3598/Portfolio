using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//상태 전이 스크립트

public class StateChange<T>
{
    private T TargetObject; // 상태를 전이시킬 오브젝트
    private StateController<T> NowState; // 현재상태
    //private PlayerStateController<T> PreState; // 과거상태

    //초기화
    public void Init_State(T Target, StateController<T> Init)
    {
        NowState = null;// PreState = null;
        TargetObject = Target;
        Change_State(Init);
    }

    //상태 전이
    public void Change_State(StateController<T> NewState)
    {
        if (NowState != null)
            NowState.ExitState(TargetObject);

        NowState = NewState;

        if (NowState != null)
        {
           // NowOpt = Opt;
            NowState.EnterState(TargetObject);
        }
    }

    //갱신
    public void Update_State()
    {
        if(NowState != null)
            NowState.UpdateState(TargetObject);
    }
}
