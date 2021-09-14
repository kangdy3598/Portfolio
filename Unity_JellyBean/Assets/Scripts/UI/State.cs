using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class State : MonoBehaviour {

    public GameObject P;
    private Vector2 UIPos;
    private Text txt;
	// Use this for initialization
	void Start () {

        txt = GetComponent<Text>();
	}
	
	// Update is called once per frame
	void Update () {
        UIPos = Camera.main.WorldToScreenPoint(P.transform.position);
        UIPos.x += 170;
        transform.position = UIPos;

        txt.text = "PlayerState : " + PlayerUnder.C_UnderState.ToString();



    }
}
