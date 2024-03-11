using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class String : MonoBehaviour, IAttackComp
{
    public GameObject hitEffect;
    public GameObject statusEffect;
    public void AttackEvent(HitComponent hitComp)
    {
        //hitComp.hitEffect = hitEffect;
        hitComp.statusEffect = statusEffect;

        GameManager.Instance.preLoseDeathCountAction?.Invoke();
    }
}
