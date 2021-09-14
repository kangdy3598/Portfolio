using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectDestroy : MonoBehaviour
{

    public int maxHP, nowHP;
    public Animator ani;
    private int aniCount;

    public GameObject[] DropItems;
    public int[] DropRate;
    private void OnEnable()
    {
        nowHP = maxHP;
        ani = GetComponent<Animator>();
        aniCount = 0;
    }
    // Update is called once per frame
    void Update()
    {
        if (nowHP <= 0)
        {
            SoundManager.Instance.PlayerSound(SoundManager.Instance.DestroyBox);
            ItemDrop();
            if (transform.tag == "Fall")
            {
                Score.DestroyFalling++;
                ObjectPool.Instance.PushToPool(gameObject.name, gameObject);
            }
            else
            {
                Score.DestroyOb++;
                gameObject.SetActive(false);
            }
        }

        if (nowHP == maxHP / 2)
        {
            ani.SetInteger("Crash", ++aniCount);
            maxHP = nowHP;
        }

    }

    void ItemDrop()
    {
        int CreateRate;
        for (int i = 0; i < DropItems.Length; i++)
        {
            if (DropRate[i] == 0) break;
            CreateRate = Random.Range(1, 100);
            if (CreateRate <= DropRate[i])
            {
                GameObject DropObject = ObjectPool.Instance.PopFromPool(DropItems[i].name);
                if (DropObject != null)
                {
                    DropObject.transform.position = transform.position;
                    DropObject.SetActive(true);
                }
            }
        }
    }

}
