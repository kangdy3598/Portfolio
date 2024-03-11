using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class HitComponent : MonoBehaviour
{
    public GameObject hitEffect;
    public GameObject statusEffect;
    public GameObject hitFont;

    private bool isHitable;

    private float invincibilityCoolTime;
    private float timer;

    public Action<string> hitEvent { get; set; }
    private StatusComponent statusComponent;
    
    private void Start()
    {
        invincibilityCoolTime = 1;
        isHitable = true;
        timer = 0.0f;

        statusComponent = GetComponent<StatusComponent>();
    }

    private void Update()
    {
        if(!isHitable)
        {
            timer += Time.deltaTime;
            if (timer >= invincibilityCoolTime)
            {
                isHitable = true;
                timer = 0.0f;
            }
        }
    }

    public void HitDamage(AttackComponent.AttackInfo attackInfo, IAttackComp attackEvent)
    {
        if(isHitable)
        {
            GameObject hitText = ObjectPool.Instance.PopFromPool("HitText");
            if (hitText != null)
            {
                hitText.GetComponent<TestHitDamage>().hitComp = this;
                hitText.SetActive(true);
            }

            hitEvent?.Invoke(attackInfo.damage);
            attackEvent?.AttackEvent(this);
            SetStatus(attackInfo);

            isHitable = false;
        }
    }   


    void SetStatus(AttackComponent.AttackInfo attackInfo)
    {
        statusComponent.SetStatus(attackInfo.statusType, statusEffect, float.Parse(attackInfo.statusDuration));
    }
}
