using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bomb : MonoBehaviour {

    public GameObject BombEffect;
    private Animator ani;
    private Vector2 pos;
	// Use this for initialization
	void Start () {

        ani = GetComponent<Animator>();
        SoundManager.Instance.PlayerSound(SoundManager.Instance.Bomb);
    }
	
	// Update is called once per frame
	void Update () {
        if (ani.GetCurrentAnimatorStateInfo(0).normalizedTime > 0.95f)
        {
            GameObject BombObject = ObjectPool.Instance.PopFromPool("BombEffect");
            if (BombObject != null)
            {
                pos = transform.position;
                pos.y += 0.5f;
                BombObject.transform.position = pos;
                BombObject.SetActive(true);
                ObjectPool.Instance.PushToPool(gameObject.name, gameObject);
                
            }
        }
	}
}
