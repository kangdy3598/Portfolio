using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;

public class PlayerHP : MonoBehaviour
{
    private int HP, maxHP;

    [SerializeField] private HitComponent hitComp;
    private BoxCollider2D hitBox;
    [SerializeField] private Text hptext;
    [SerializeField] private Image hpGauge;

    public Action deadEvent;
    public Action resurrectionEvent;

    private void Awake()
    {
        hitComp.hitEvent += HPUpdate;
        hitBox = hitComp.GetComponent<BoxCollider2D>();
        HP = maxHP = 10;
        hptext.text = $"{HP.ToString()} \\ {maxHP.ToString()}";
        hpGauge.fillAmount = HP / (float)maxHP;
    }

    private void HPUpdate(string _damageAmount)
    {
        int damageAmount = int.Parse(_damageAmount);
        HP -= damageAmount;

        if (HP > maxHP) HP = maxHP;
        if (HP <= 0)
        {
            HP = 0;
            hitBox.enabled = false;
            deadEvent?.Invoke();
        }

        hptext.text = $"{HP.ToString()} \\ {maxHP.ToString()}";
        hpGauge.fillAmount = HP / (float)maxHP;
    }

    public void Resurrection()
    {
        HP = maxHP;
        hptext.text = $"{HP.ToString()} \\ {maxHP.ToString()}";
        hpGauge.fillAmount = HP / (float)maxHP;

        hitBox.enabled = true;
        resurrectionEvent?.Invoke();
    }
}
