using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BombEffect : MonoBehaviour {

    private Animator ani;
	// Use this for initialization
	void Start () {

        ani = GetComponent<Animator>();

	}
	
	// Update is called once per frame
	void Update () {

        if (ani.GetCurrentAnimatorStateInfo(0).normalizedTime > ani.GetCurrentAnimatorStateInfo(0).length)
            ObjectPool.Instance.PushToPool(gameObject.name, gameObject);

    }
}
