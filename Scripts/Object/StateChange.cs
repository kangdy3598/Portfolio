using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//상태 전이 스크립트

public class StateChange<T>
{
    private T targetObject; // 상태를 전이시킬 오브젝트
    private StateController<T> nowState; // 현재상태
    //private PlayerStateController<T> PreState; // 과거상태

    //초기화
    public void Init_State(T Target, StateController<T> Init)
    {
        nowState = null;// PreState = null;
        targetObject = Target;
        Change_State(Init);
    }

    //상태 전이
    public void Change_State(StateController<T> NewState)
    {
        if (nowState != null)
            nowState.ExitState(targetObject);

        nowState = NewState;

        if (nowState != null)
        {
           // NowOpt = Opt;
            nowState.EnterState(targetObject);
        }
    }

    //갱신
    public void Update_State()
    {
        if(nowState != null)
            nowState.UpdateState(targetObject);
    }

    public void FixedUpdate_State()
    {
        if (nowState != null)
            nowState.FixedUpdateState(targetObject);
    }
}
