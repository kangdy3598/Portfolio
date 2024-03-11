using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Skill04Object : MonoBehaviour
{
    private float moveSpeed;
    private Transform leftSide, rightSide;
    private Vector3 pos;
    private void Awake()
    {
        moveSpeed = 3.0f;
        leftSide = transform.GetChild(0);
        rightSide = transform.GetChild(1);

        pos = leftSide.position;
    }
    private void OnEnable()
    {
        InitObjetSetting();
        Invoke("ObjectPoolPush", 1);
    }

    private void Update()
    {
        leftSide.Translate(-Time.deltaTime * moveSpeed, 0, 0);
        rightSide.Translate(Time.deltaTime * moveSpeed, 0, 0);
    }

    void InitObjetSetting()
    {
        pos.x = 0;
        leftSide.position = pos;
        rightSide.position = pos;
    }
    void ObjectPoolPush()
    {
        ObjectPool.Instance.PushToPool(gameObject.name, gameObject);
    }
}
