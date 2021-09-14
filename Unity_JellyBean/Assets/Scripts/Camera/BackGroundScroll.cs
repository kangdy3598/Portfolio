using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackGroundScroll : MonoBehaviour {

    public Vector3 vPos;
    // Use this for initialization
    void Start()
    {
        vPos = transform.position;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        vPos.y = Player.trans.position.y + 3;
        transform.position = vPos;
 
    }
}
