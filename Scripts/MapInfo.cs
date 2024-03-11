using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class MapInfo : MonoBehaviour
{
    protected Vector2 mapLimitPosLT{ get; private set; }
    protected Vector2 mapLimitPosRB { get; private set; }

    private Vector2 limitValue;
    private void Awake()
    {
        limitValue = new Vector2(8.9f, 4.1f);
        mapLimitPosLT = new Vector2(-limitValue.x, limitValue.y);
        mapLimitPosRB = new Vector2(limitValue.x, -limitValue.y);
    }
}
