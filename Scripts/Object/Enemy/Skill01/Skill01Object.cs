using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Skill01Object : MonoBehaviour
{
    public void ObjectPoolPush()
    {
        ObjectPool.Instance.PushToPool(gameObject.name, gameObject);
    }
}
