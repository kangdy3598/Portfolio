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

    // preLoseDeathCountAction(�ǿ� ������)�� ���� �����
    public void WhiteToRed()
    {
        // ���� ī��Ʈ ���ʺ��� �� ĭ�� ���������� �ٲ�
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

        // ����ī��Ʈ ������ ��ġ����
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
