using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager : MonoBehaviour
{
    private static SoundManager instance = null;
    public static SoundManager Instance
    {
        get
        {
            if (instance == null)
                instance = GameObject.FindObjectOfType<SoundManager>() as SoundManager;

            return instance;
        }
    }

    private AudioSource audioSource;


    //메인화면 내 사운드
    public AudioClip ButtonClick;


    //인게임 내 사운드
    public AudioClip BoomHit, BoomAttack, Axe;
    public AudioClip Jump, SlimeWalk, SlimeJump, Slide;
    public AudioClip Bomb, GetPotion, GetGold;
    public AudioClip DestroyBox, HitBox;
    private void Start()
    {
        audioSource = GetComponent<AudioSource>();
    }
    
    public void PlayerSound(AudioClip audioClip)
    {
        audioSource.PlayOneShot(audioClip);
    }
}
