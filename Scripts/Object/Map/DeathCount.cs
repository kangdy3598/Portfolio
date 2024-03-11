using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DeathCount : MonoBehaviour
{
    public GameObject[] deathcountObject;
    private int deathcount;
    private int redCount;

    private void Start()
    {
        deathcount = GameManager.Instance.nowDeathCount;
        redCount = GameManager.Instance.nowRedcount;

        GameManager.Instance.preLoseDeathCountAction += WhiteToRed;
        GameManager.Instance.loseDeathCountAction += RedBreak;
        GameManager.Instance.clearDeathCountAction += RedToWhite;

        //PlayerInfo.Instance.deadEvent += RedBreak;
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Y))
            WhiteBreak();
    }

    // preLoseDeathCountAction(실에 맞으면)에 의해 실행됨
    public void WhiteToRed()
    {
        // 데스 카운트 왼쪽부터 한 칸씩 빨간색으로 바뀜
        if (redCount < 5)
        {
            deathcountObject[redCount++].GetComponent<Animator>().SetInteger("state", 1);
            GameManager.Instance.nowRedcount = redCount;
        }
    }

    public void RedToWhite()
    {
        for(int i=0; i<deathcountObject.Length; i++)
        {
            deathcountObject[i].GetComponent<Animator>().SetInteger("state", 0);
        }

        redCount = 0;
        GameManager.Instance.nowRedcount = 0; 
    }

    public void WhiteBreak()
    {
        deathcountObject[--deathcount].GetComponent<Animator>().SetInteger("state", 3);
        GameManager.Instance.nowDeathCount = deathcount;
    }

    public void RedBreak()
    {
        for(int i=0; i< redCount; i++)
        {
            deathcountObject[i].GetComponent<Animator>().SetInteger("state", 2);
        }

        // 데스카운트 아이콘 위치조정
        for (int i = 0; i < redCount; i++)
        {
            var temp = deathcountObject[0];
            var tempPosition = deathcountObject[deathcount - 1].transform.parent.position;
            for (int j = deathcount - 1; j > 0; j--)
            {
                deathcountObject[j].transform.parent.position = deathcountObject[j - 1].transform.parent.position;
            }
            deathcountObject[0].transform.parent.position = tempPosition;

            for (int j = 0; j < 4; j++)
            {
                deathcountObject[j] = deathcountObject[j+1];
            }
            
            deathcountObject[deathcount - 1] = temp;
        }

        deathcount -= redCount;
        GameManager.Instance.nowDeathCount = deathcount;
        redCount = 0;
        GameManager.Instance.nowRedcount = redCount;
    }
}
