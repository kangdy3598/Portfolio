using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackCollider : MonoBehaviour {

    private GameObject Target;
    private bool b_Delay;
	// Use this for initialization
	void Start () {

        b_Delay = true;
	}

    private void Update()
    {
        // 근접 공격 관련
        if (transform.parent.name == "[Player1](Clone)")
        {
            if (PlayerUpper.C_UpperState == PlayerUpper.PlayerUpperState.NORMALATTACK && Player.ani.GetBool("IsAxe") && b_Delay && Target)
            {
                StartCoroutine(Delay(200, 10));

                GameObject AxeEffectObject = ObjectPool.Instance.PopFromPool("AxeEffect");
                if (AxeEffectObject != null)
                {
                    AxeEffectObject.transform.position = Target.transform.position;
                    AxeEffectObject.SetActive(true);
                }
                
            }

            if (Target != null && Target.GetComponent<ObjectDestroy>().nowHP == 0)
            {
                Player.ani.SetBool("IsAxe", false);
                Target = null;
            }

        }
        else
        {
            if (PlayerUpper.C_UpperState == PlayerUpper.PlayerUpperState.NORMALATTACK && b_Delay && Target)
            {
                if(GetComponent<Collider2D>().enabled)
                StartCoroutine(Delay(400, 200));                
            }

            if (Target != null && Target.GetComponent<ObjectDestroy>().nowHP == 0)
            {
                Target = null;
            }

            //if (!Player.ani.GetBool("IsHuman"))
            //    GetComponent<BoxCollider2D>().enabled = true;
            //else
            //    GetComponent<BoxCollider2D>().enabled = false;
        }
        


    }
    // 오브젝트와 가까워지면 원거리 공격에서 근접 공격으로 바뀌는 함수
    private void OnTriggerStay2D(Collider2D collision)
    {
        if (transform.parent.name == "[Player1](Clone)")
        {
            Player.ani.SetBool("IsAxe", true);
            if (collision.name == "Box")
            {
                Target = collision.gameObject;
            }
        }
        else
        {
            if (collision.tag == "Object")
                Target = collision.gameObject;
        }
        if((collision.tag == "Object" || collision.tag == "Fall") && !Player.ani.GetBool("IsHuman"))
        {
            Target = collision.gameObject;
            Target.GetComponent<ObjectDestroy>().nowHP = 0;
        }

    }

    // 폭탄 공격
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Object" || collision.tag == "Fall")
        {
            Target = collision.gameObject;
            // 원거리 공격 HP 소비
            if (gameObject.name == "BoomBall")
            {
                Target.GetComponent<ObjectDestroy>().nowHP -= 10;

                // 폭발 이펙트
                GameObject BoomEffectObject = ObjectPool.Instance.PopFromPool("BoomEffect");
                if (BoomEffectObject != null)
                {
                    BoomEffectObject.transform.position = transform.position;
                    BoomEffectObject.SetActive(true);
                }

                // 폭탄 수거
                ObjectPool.Instance.PushToPool(transform.name, gameObject);

                // 사운드
                SoundManager.Instance.PlayerSound(SoundManager.Instance.BoomHit);
                SoundManager.Instance.PlayerSound(SoundManager.Instance.HitBox);
            }
        }
    }

    // 오브젝트와 멀어지면 다시 초기화
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.tag == "Object")
        {
            Target = null;
            if (transform.parent.name == "[Player1](Clone)")
                Player.ani.SetBool("IsAxe", false);
            

        }
    }

    // 근접 공격 딜레이를 주기 위한 함수
    IEnumerator Delay(float T, int Damage)
    {
        b_Delay = false;
        SoundManager.Instance.PlayerSound(SoundManager.Instance.Axe);
       // SoundManager.Instance.PlayerSound(SoundManager.Instance.HitBox);
        Target.GetComponent<ObjectDestroy>().nowHP -= Damage;
        yield return new WaitForSeconds(T / 1000.0f);
        b_Delay = true;
    }
}
