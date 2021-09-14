using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectPlacement : MonoBehaviour {

    
    public GameObject[] Steps; // 발판 종류
    public GameObject[] StepObject;
    public static int[] StepsRate = { 60, 0, 0 };

    public GameObject[] Boxes; // 상자 종류
    public GameObject[] BoxObject;
    public static int[] BoxesRate = { 40, 30, 30 };

    public int CreateProbability;
    public static int Boxfloor = 1, Stepfloor = 1;

    private void OnEnable()
    {
        CreateProbability = 0;
        StepCreate();
        BoxCreate();
    }

    void StepRateUpdate(int count)
    {
        if (count % 10 == 0)
        {
            //1단계 발판 확률/////////////////////////////
            switch (count)
            {
                case 40:
                case 50:
                    StepsRate[0] -= 15;
                    break;
                case 70:
                case 90:
                case 100:
                    StepsRate[0] -= 10;
                    break;
            }
            //2단계 발판 확률/////////////////////////////
            if (count >= 20 && count <= 50) StepsRate[1] += 10;
            else if (count == 80) StepsRate[1] -= 10;
            else if (count == 100) StepsRate[1] += 10;
            //3단계 발판 확률/////////////////////////////
            if (StepsRate[2] >= 20 && StepsRate[2] < 60) StepsRate[2] += 10;
            else if (count >= 20 && count < 100) StepsRate[2] += 5;
        }
        FallingCreate.Floor++;
    }
    void BoxRateUpdate(int count)
    {
        if (count % 10 == 0 && count >= 20)
        {
            //1단계 상자 확률//////////////////////////////
            if (BoxesRate[0] > 0)
            {
                BoxesRate[0] -= 10;
            }
            //2단계 상자 확률/////////////////////////////
            if (count <= 50) BoxesRate[1] += 5;
            else if (BoxesRate[1] > 0) BoxesRate[1] -= 10;
            //3단계 상자 확률/////////////////////////////
            if (count <= 50) BoxesRate[2] += 5;
            else if (BoxesRate[1] < 100) BoxesRate[2] += 10;
            
        }
        
    }

    void StepCreate()
    {
        float StepCreateRate;
        for (int i = 0; i < StepObject.Length; i++)
        {
            if (Stepfloor <= 100)
            {
                if (i == 1 || i == 4 || i == 6 || i == 9) StepRateUpdate(++Stepfloor);
            }
            for (int j = 0; j < StepsRate.Length; j++)
            {
                if (StepsRate[j] == 0) break;
                CreateProbability += StepsRate[j];
                StepCreateRate = Random.Range(1, 100);
                if (StepCreateRate <= CreateProbability)
                {
                    StepObject[i].GetComponent<SpriteRenderer>().sprite = Steps[j].GetComponent<SpriteRenderer>().sprite;
                    StepObject[i].GetComponent<Animator>().runtimeAnimatorController = Steps[j].GetComponent<Animator>().runtimeAnimatorController;
                    StepObject[i].GetComponent<ObjectDestroy>().maxHP = Steps[j].GetComponent<ObjectDestroy>().maxHP;
                    StepObject[i].SetActive(true);
                    CreateProbability = 0;
                }
            }
        }
    }
    void BoxCreate()
    {
        float BoxCreateRate;
        for (int i = 0; i < BoxObject.Length; i++)
        {
            if (Boxfloor <= 100)
            {
                if (i == 2 && i == 4 && i == 7 && i == 9) BoxRateUpdate(++Boxfloor);
            }
            for (int j = 0; j < BoxesRate.Length; j++)
            {
                if (BoxesRate[j] == 0) break;
                CreateProbability += BoxesRate[j];
                BoxCreateRate = Random.Range(1, 100);
                if (BoxCreateRate <= BoxesRate[j])
                {
                    BoxObject[i].GetComponent<SpriteRenderer>().sprite = Boxes[j].GetComponent<SpriteRenderer>().sprite;
                    BoxObject[i].GetComponent<Animator>().runtimeAnimatorController = Boxes[j].GetComponent<Animator>().runtimeAnimatorController;
                    BoxObject[i].GetComponent<ObjectDestroy>().maxHP = Boxes[j].GetComponent<ObjectDestroy>().maxHP;
                    BoxObject[i].SetActive(true);
                    CreateProbability = 0;
                }
            }
        }
    }
}
