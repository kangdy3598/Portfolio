using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoomShot : MonoBehaviour {

    private float elapsedTime, LifeTime;
    private int Rotation , Destination;
    
    private Vector3 vector;
    private Vector3 boomSpeed;
    private float Gravity = 0.2f;
	// Use this for initialization
    void OnEnable()
    {
        elapsedTime = 0.0f;
        LifeTime = 1.5f;
        Rotation = (int)PlayerUpper.C_UpperState;
        Destination = (int) Player.trans.localScale.x;

    }
    // Update is called once per frame
    void Update () {
        
        elapsedTime += Time.deltaTime;
        // shot
        if (Rotation == 3)
        {
            boomSpeed.x = 0.005f; boomSpeed.y = 1.2f;
        }
        else
        {
            boomSpeed.x = 0.3f; boomSpeed.y = 0.3f;
        }

        // 포물선
        vector.x = Destination * boomSpeed.x * Mathf.Cos(10 * Mathf.Deg2Rad);
        vector.y = boomSpeed.y * Mathf.Sin(10 * Mathf.Deg2Rad) - Gravity * elapsedTime;
        transform.Translate(vector);

        // push
        if (elapsedTime > LifeTime)
        {
            elapsedTime = 0;
            ObjectPool.Instance.PushToPool(transform.name, gameObject);
        }
    }

    
}
