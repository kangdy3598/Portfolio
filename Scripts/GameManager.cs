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
    public Action preLoseDeathCountAction; // 초록색 해골이 빨간색 해골 아이콘으로 바뀔 때
    public Action loseDeathCountAction; // 아예 데스 카운트를 잃었을 때
    public Action clearDeathCountAction; // 빨간색 해골이 초록색 해골 아이콘으로 바뀔 때

    public int nowDeathCount;
    public int nowRedcount;

    private void Awake()
    {
        nowDeathCount = 5;
        nowRedcount = 0;
    }
}
