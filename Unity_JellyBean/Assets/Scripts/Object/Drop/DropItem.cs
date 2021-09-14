using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DropItem : MonoBehaviour {

    private Rigidbody2D rigid;
    private float Power;
    public Player p;
    // Use this for initialization
    void Start()
    {
        p = Player.trans.GetComponent<Player>();
        rigid = GetComponent<Rigidbody2D>();

        if (rigid != null)
        {
            Power = Random.Range(-0.3f, 0.3f);
            rigid.AddForce(new Vector2(Power, 5), ForceMode2D.Impulse);
        }
    }
	
	// Update is called once per frame
	void Update () {
        if(gameObject.name != "BombEffect")
        Physics2D.IgnoreLayerCollision(8, 10);
	}

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.name == "GetItem")
        {
            switch (transform.name)
            {
                case "Coin_Bronze":
                    SoundManager.Instance.PlayerSound(SoundManager.Instance.GetGold);
                    Score.GetCoin += 10;
                    break;
                case "Coin_Silver":
                    SoundManager.Instance.PlayerSound(SoundManager.Instance.GetGold);
                    Score.GetCoin += 50;
                    break;
                case "Coin_Gold":
                    SoundManager.Instance.PlayerSound(SoundManager.Instance.GetGold);
                    Score.GetCoin += 100;
                    break;
                case "Potion_HP":
                    SoundManager.Instance.PlayerSound(SoundManager.Instance.GetPotion);
                    p.HPImage.fillAmount += 0.1f;
                    Score.GetHP++;
                    break;
                case "Potion_TP":
                    SoundManager.Instance.PlayerSound(SoundManager.Instance.GetPotion);
                    p.TPImage.fillAmount += 0.1f;
                    break;
                case "Jewel":
                    break;
                case "BombEffect":
                    if (Player.ani.GetBool("IsHuman"))
                    {
                        Player.trans.GetComponent<PlayerExtra>().Change_State(P_State_Attacked.Instance);
                        p.HPImage.fillAmount -= 0.1f;
                    }
                    break;
            }
            if(transform.name != "Bomb" && transform.name != "BombEffect")
                ObjectPool.Instance.PushToPool(transform.name, gameObject);
        }
        
    }
}
