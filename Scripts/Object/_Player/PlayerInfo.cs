using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;

public class PlayerInfo : MonoBehaviour
{
    private static PlayerInfo instance = null;
    public static PlayerInfo Instance
    {
        get
        {
            if (instance == null)
                instance = GameObject.FindObjectOfType<PlayerInfo>() as PlayerInfo;

            return instance;
        }
    }

    public Vector2 nowPosition;
    public Vector2 nowScale;

    [SerializeField] public PlayerHP playerHPComp { get; set; }
    
    private void Awake()
    {
        playerHPComp = GetComponent<PlayerHP>();

    }

    private void Update()
    {
        nowPosition = transform.position;
        nowScale = transform.localScale;

        
    }
}
