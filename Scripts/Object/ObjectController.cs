using System.Collections;
using System.Collections.Generic;
using UnityEngine;
 
abstract public class StateController<Ob>
{
    abstract public void EnterState(Ob Object);
    abstract public void UpdateState(Ob Object);
    abstract public void FixedUpdateState(Ob Object);
    abstract public void ExitState(Ob Object);

}

// MonoBehaviour로 상속 받지 않은 클래스에 코루틴 함수를 적용 시키기 위해 작성
public class CoroutineHandler : MonoBehaviour
{
    IEnumerator enumerator = null;
    private void Coroutine(IEnumerator coro)
    {
        enumerator = coro;
        StartCoroutine(coro);
    }

    void Update()
    {
        if (gameObject.activeSelf)
        {
            Destroy(gameObject);
        }
    }

    public void Stop()
    {
        StopCoroutine(enumerator.ToString());
        Destroy(gameObject);
    }

    public static CoroutineHandler Start_Coroutine(IEnumerator Co)
    {
        GameObject ob = new GameObject("CoroutineHandle");
        CoroutineHandler handler = ob.AddComponent<CoroutineHandler>();

        if (handler)
            handler.Coroutine(Co);

        return handler;


    }
}