using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerUpper : MonoBehaviour
{
    public enum PlayerUpperState
    {
        NORMAL,
        NORMALATTACK,
        LOOKUP,
        LOOKUPATACK,
    };
    public static PlayerUpperState C_UpperState;
    public StateChange<PlayerUpper> UpperStateChange;
    
    private bool b_Delay;

    private void Start()
    {
        UpperStateChange = new StateChange<PlayerUpper>();
        UpperStateChange.Init_State(this, P_State_Normal.Instance);
        b_Delay = true;
    }
    
    private void Update()
    {
        if (transform.name == "[Player1](Clone)")
        {
            if (C_UpperState == PlayerUpperState.NORMAL && Input.GetKey(KeyCode.UpArrow))
            {
                Change_State(P_State_Lookup.Instance);
            }
        }

        if((int)C_UpperState %2 == 0)
        {
            if(PlayerExtra.C_ExtraState == PlayerExtra.PlayerExtraState.NORMAL && Input.GetKeyDown(KeyCode.Z))
            {
                Change_State(P_State_Attack.Instance);
            }
        }

        else
        {
            if (b_Delay && transform.name == "[Player1](Clone)")
            {
                if (!Player.ani.GetBool("IsAxe"))
                {
                    if (C_UpperState == PlayerUpperState.NORMALATTACK || C_UpperState == PlayerUpperState.LOOKUPATACK)
                    {
                        BoomShot();
                        StartCoroutine(Delay());
                    }
                }
                else
                {
                    if(C_UpperState >= PlayerUpperState.LOOKUP)
                    {
                        BoomShot();
                        StartCoroutine(Delay());
                    }
                }
            }
        }
        
    }

    public virtual void FixedUpdate()
    {
        UpperStateChange.Update_State();
    }

    public void Change_State(StateController<PlayerUpper> State)
    {
        UpperStateChange.Change_State(State);
    }

    void BoomShot()
    {
        Vector2 pos;
        GameObject BoomObject = ObjectPool.Instance.PopFromPool("BoomBall");
        if(BoomObject != null)
        {
            SoundManager.Instance.PlayerSound(SoundManager.Instance.BoomAttack);
            pos = transform.position;
            if (C_UpperState == PlayerUpperState.LOOKUPATACK) pos.y += 2;
            else if (C_UpperState == PlayerUpperState.NORMALATTACK) pos.y += 1;
            BoomObject.transform.position = pos;
            BoomObject.SetActive(true);
        }
    }
    IEnumerator Delay()
    {
        b_Delay = false;
        yield return new WaitForSeconds(0.2f);
        b_Delay = true;
    }
}
