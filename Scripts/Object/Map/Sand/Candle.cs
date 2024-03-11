using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Candle : MonoBehaviour
{
    [SerializeField] private Sand sand;

    // 촛불 스프라이트 이미지
    [SerializeField] private SpriteRenderer[] stickSprite;
    private int stickCount;

    // 불꽃 스프라이트 이미지
    [SerializeField] private GameObject[] flame;
    private SpriteRenderer[] flameSprite;
    private Animator[] flameAnim;

    // 사라지는 촛불
    [SerializeField] private GameObject[] disappear;
    private SpriteRenderer[] disappearSprite;
    private Animator[] disappearAnim;
    private int flameCount;

    // 데스카운트 UI
    // [SerializeField] private DeathCount deathCount;

    // 제단
    [SerializeField] private GameObject altar;
    //private Altar altarComp;
    // 낫베기 스크린
    [SerializeField] private Animator screenAnim;

    void Start()
    {
        GameManager.Instance.preLoseDeathCountAction += EnableFlame;
        GameManager.Instance.loseDeathCountAction += DisableStick;
        GameManager.Instance.clearDeathCountAction += SuccessFlame;

        stickCount = stickSprite.Length;
        flameCount = 0;

        flameSprite = new SpriteRenderer[stickCount];
        flameAnim = new Animator[stickCount];
        for (int i = 0; i < stickCount; i++)
        {
            flameSprite[i] = flame[i].GetComponent<SpriteRenderer>();
            flameAnim[i] = flame[i].GetComponent<Animator>();
            //disappear.SetActive(false);
        }

        disappearSprite = new SpriteRenderer[stickCount];
        disappearAnim = new Animator[stickCount];
        for (int i = 0; i < stickCount; i++)
        {
            disappearSprite[i] = disappear[i].GetComponent<SpriteRenderer>();
            disappearAnim[i] = disappear[i].GetComponent<Animator>();
            //disappear.SetActive(false);
        }
        //altarComp = altar.GetComponent<Altar>();
        screenAnim.enabled = false;
    }

    private void DisableStick()
    {
        Invoke("EnableStick", 1f);
        for (int i = 0; i < stickCount; i++)
        {
            stickSprite[i].enabled = false;

            disappearSprite[i].enabled = true;
            disappearAnim[i].enabled = true;
            disappearAnim[i].Play("Disappear", -1, 0f);
        }

        stickCount = (GameManager.Instance.nowDeathCount + 1) / 2;
        ShowScreenImage();
        DisableFlame();
    }
    private void EnableStick()
    {
        for (int i = 0; i < stickCount; i++)
        {
            stickSprite[i].enabled = true;
        }
    }
    
    void DisableFlame()
    {
        for(int i=0; i< stickCount; i++)
        {
            //flame[i].SetActive(false);
            flameSprite[i].enabled = false;
        }
        flameCount = 0;
    }
    void EnableFlame()
    {
        if (stickCount > flameCount)
        {
            flameAnim[flameCount].enabled = true;
            flameAnim[flameCount++].Play("FlameAppear", -1, 0f);
        }
        
        if (stickCount == flameCount)
        {
            altar.SetActive(true);
            
        }
    }
    void SuccessFlame()
    {
        for (int i = 0; i < flameCount; i++)
        {
            flameAnim[i].SetTrigger("success");
        }
        flameCount = 0;
    }

    private void ShowScreenImage()
    {
        screenAnim.enabled = true;
        screenAnim.Play("Screen", -1, 0f);
    }
}
