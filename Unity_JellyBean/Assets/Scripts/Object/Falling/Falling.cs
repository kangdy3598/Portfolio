using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Falling : MonoBehaviour {

    float _time;
    // Use this for initialization
	void Start () {

        
	}

    private void OnEnable()
    {
        _time = 0;
    }
    // Update is called once per frame
    void Update()
    {
        transform.Translate(0, -Time.deltaTime * 2.5f, 0);
        _time += Time.deltaTime;
        if(_time > 8.0f)
            ObjectPool.Instance.PushToPool(transform.name, gameObject);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag == "Player" && PlayerExtra.C_ExtraState != PlayerExtra.PlayerExtraState.SLIDE)
        {
            Player.trans.GetComponent<PlayerExtra>().Change_State(P_State_Attacked.Instance);
            Player.trans.GetComponent<Player>().HPImage.fillAmount -= 0.1f;
        }
    }
}
