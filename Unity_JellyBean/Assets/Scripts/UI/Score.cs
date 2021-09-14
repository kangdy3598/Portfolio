using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour {

    public GameObject Base;
    public static GameObject Player;

    public static double Height;
    public static int DestroyOb,
                      GetCoin,
                      GetHP,
                      TransSlime,
                      DestroyFalling,
                      StartGame,
                      EndGame;

    private Text txt;
	// Use this for initialization
	void Start () {
        txt = GetComponent<Text>();
	}
	
	// Update is called once per frame
	void Update () {

        Height = (Player.transform.position.y - (Base.transform.position.y + 0.375)) / 0.75 + 12;
        txt.text = (int)Height + "m";
	}
}
