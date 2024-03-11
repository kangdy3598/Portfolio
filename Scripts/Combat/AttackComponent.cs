using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class AttackComponent : MonoBehaviour
{
    [HideInInspector] public string[] stringList;
    [Serializable]
    public struct AttackInfo
    {
        public string attackName;
        public string attackType;
        public string damage;
        public string statusType;
        public string statusDuration;
    }
    public AttackInfo[] attackInfoList;
    [HideInInspector] public int index;
    [HideInInspector] public AttackInfo nowAttackInfo;

    //public Action attackEvent;
    //private bool isAttackFrame;
    [SerializeField] private BoxCollider2D col;

    IAttackComp IattackComp;
    void Start()
    {
        if(!col) col = GetComponent<BoxCollider2D>();
        IattackComp = GetComponent<IAttackComp>();

        nowAttackInfo = attackInfoList[index];
        DisableAttackFrame();
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        HitComponent hitComp = collision.GetComponent<HitComponent>();
        if (!hitComp)
            return;

        hitComp.HitDamage(nowAttackInfo, IattackComp);
    }
    // Animation Frame에 의해 제어
    public void EnableAttackFrame()
    {
        //isAttackFrame = true;
        col.enabled = true;
    }
    public void DisableAttackFrame()
    {
        //isAttackFrame = false;
        col.enabled = false;
    }


   
}
public interface IAttackComp
{
    void AttackEvent(HitComponent hitComp);
}