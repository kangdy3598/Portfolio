using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;


public class Sand : MonoBehaviour
{
    [Serializable]
    private struct Sandglass
    {
        public SpriteRenderer[] top_sandSprites;
        public SpriteRenderer[] bot_sandSprites;
    }

    [SerializeField] private Sandglass leftSandglass;
    [SerializeField] private Sandglass rightSandglass;

    //public Action sandClearAction { get; set; }
    private int sandSpriteLength;

    private int nowLevel;
    private float timer;
    private float screenTime;

    private void Start()
    {
        sandSpriteLength = leftSandglass.top_sandSprites.Length;
        nowLevel = 0;
        timer = 0.0f;

        screenTime = 10; // 3min
    }

    private void Update()
    {
        timer += Time.deltaTime;
        if (timer >= screenTime / (sandSpriteLength - 1))
        {
            SetSandglass(++nowLevel);
            timer = 0;
        }
    }

    private void SetSandglass(int level)
    {
        if (level >= sandSpriteLength - 1)
        {
            InitSandglass();
            GameManager.Instance.loseDeathCountAction?.Invoke();
            //sandClearAction?.Invoke();
            return;
        }

        leftSandglass.top_sandSprites[level].gameObject.SetActive(false);
        rightSandglass.top_sandSprites[level].gameObject.SetActive(false);

        leftSandglass.bot_sandSprites[level].gameObject.SetActive(true);
        rightSandglass.bot_sandSprites[level].gameObject.SetActive(true);

        leftSandglass.top_sandSprites[0].gameObject.SetActive(false);
        rightSandglass.top_sandSprites[0].gameObject.SetActive(false);

    }

    private void InitSandglass()
    {
        for (int i = 0; i < sandSpriteLength; i++)
        {
            leftSandglass.top_sandSprites[i].gameObject.SetActive(true);
            rightSandglass.top_sandSprites[i].gameObject.SetActive(true);
        }

        for (int i = 1; i < sandSpriteLength; i++)
        {
            leftSandglass.bot_sandSprites[i].gameObject.SetActive(false);
            rightSandglass.bot_sandSprites[i].gameObject.SetActive(false);
        }

        nowLevel = 0;
    }
    
}
