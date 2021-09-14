using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMove : MonoBehaviour
{
    Vector3 CameraPos;

    private Vector2 constPosY;
    // Use this for initialization
    void Start()
    {
        Screen.sleepTimeout = SleepTimeout.NeverSleep;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        CameraPos.y = Player.trans.position.y;
        CameraPos.y += 4;
        CameraPos.z = -12.5f;
        transform.position = CameraPos;

    }
}
