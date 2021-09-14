using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;

// 캐릭터의 기본적인 움직임과 스팩이 담겨 있는 스크립트
public class Player : MonoBehaviour
{
    //캐릭터 형태
    public enum PlayerForm
    {
        HUMAN = 10,
        SLIME = 20,
    };
    public static PlayerForm C_Form;

    //캐릭터의 인스펙터 정보
    public static SpriteRenderer spr;
    public static Transform trans;
    public static CapsuleCollider2D Col;
    public static Rigidbody2D rigid;
    public static Animator ani;

    public JoyStick JoyStick; // 조이스틱 컨트롤러

    //
    public bool BoomAttack = false;
    
    //캐릭터 기본 스팩
    public float HP,
                 Attack;

    //캐릭터 HP/TP
    public Image HPImage, TPImage;

    //파티클
    public ParticleSystem SlideParticle;

    public virtual void Awake()
    {
        //캐릭터 인스펙터 저장
        spr = GetComponent<SpriteRenderer>();
        trans = GetComponent<Transform>();
        Col = GetComponent<CapsuleCollider2D>();
        rigid = GetComponent<Rigidbody2D>();
        ani = GetComponent<Animator>();

        HPImage = GameObject.Find("HP").GetComponent<Image>();
        TPImage = GameObject.Find("TP").GetComponent<Image>();

        C_Form = PlayerForm.HUMAN;

        Screen.SetResolution(720, 1280, true);

        Score.StartGame++;
    }

    private void Update()
    {
        if(Input.GetKeyDown(KeyCode.R))
        {
            ani.SetInteger("UnderState", 0);
            ani.SetInteger("UpperState", 0);
            ani.SetInteger("ExtraState", 0);
            ani.SetBool("IsAxe", false);
            ani.SetBool("IsHuman", false);
        }
        foreach(GameObject ob1 in GameObject.FindGameObjectsWithTag("Object"))
        {
            Physics2D.IgnoreCollision(Col, ob1.GetComponent<Collider2D>(), !ani.GetBool("IsHuman"));
        }
        foreach (GameObject ob2 in GameObject.FindGameObjectsWithTag("Fall"))
        {
            Physics2D.IgnoreCollision(Col, ob2.GetComponent<Collider2D>(), !ani.GetBool("IsHuman"));
        }
        if (Input.GetKeyDown(KeyCode.Tab))
        {
            Transfer();
            
        }
        switch (Player.ani.GetCurrentAnimatorClipInfo(0)[0].clip.name)
        {
            case "TransferToSlime":
            case "TransferToHuman":
                if (Player.ani.GetCurrentAnimatorStateInfo(0).normalizedTime > 0.95f) Player.ani.SetBool("Changing", false);
                break;
        }

    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Object")
            Physics2D.IgnoreCollision(Col, collision.GetComponent<Collider2D>(), ani.GetBool("IsHuman"));
    }
    // 버튼 입력 함수
    public void Transfer()
    {
       // if (PlayerUnder.C_UnderState == PlayerUnder.PlayerUnderState.IDLE && PlayerUpper.C_UpperState == PlayerUpper.PlayerUpperState.NORMAL)
        {
            if (C_Form == PlayerForm.HUMAN)// && TPImage.fillAmount >= 0.3f)
            {
                Score.TransSlime++;
                C_Form = PlayerForm.SLIME;
                GetComponent<PlayerUnder>().Change_State(P_State_Idle.Instance);
                GetComponent<PlayerUpper>().Change_State(P_State_Normal.Instance);
                ani.SetBool("IsHuman", false);
                ani.SetBool("Changing", true);
                //   TPImage.fillAmount -= 0.3f;
            }
            else
            {
                C_Form = PlayerForm.HUMAN;
                GetComponent<PlayerUnder>().Change_State(P_State_Idle.Instance);
                GetComponent<PlayerUpper>().Change_State(P_State_Normal.Instance);
                ani.SetBool("IsHuman", true);
                ani.SetBool("Changing", true);
            }
        }
    }
}
