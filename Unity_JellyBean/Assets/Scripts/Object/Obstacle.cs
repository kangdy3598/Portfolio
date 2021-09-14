using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Obstacle : MonoBehaviour {

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Player")
        {
            if ((PlayerExtra.C_ExtraState != PlayerExtra.PlayerExtraState.SLIDE && PlayerExtra.C_ExtraState != PlayerExtra.PlayerExtraState.DOWN) &&
                Player.ani.GetBool("IsHuman"))
            {
                Player.trans.GetComponent<PlayerExtra>().Change_State(P_State_Attacked.Instance);
                Player.trans.GetComponent<Player>().HPImage.fillAmount -= 0.1f;
            }
        }
    }
}
