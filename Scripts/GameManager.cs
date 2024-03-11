using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class GameManager : MonoBehaviour
{
    private static GameManager instance = null;
    public static GameManager Instance
    {
        get
        {
            if (instance == null)
                instance = GameObject.FindObjectOfType<GameManager>() as GameManager;

            return instance;
        }
    }
    public Action preLoseDeathCountAction; // �ʷϻ� �ذ��� ������ �ذ� ���������� �ٲ� ��
    public Action loseDeathCountAction; // �ƿ� ���� ī��Ʈ�� �Ҿ��� ��
    public Action clearDeathCountAction; // ������ �ذ��� �ʷϻ� �ذ� ���������� �ٲ� ��

    public int nowDeathCount;
    public int nowRedcount;

    private void Awake()
    {
        nowDeathCount = 5;
        nowRedcount = 0;
    }
}
