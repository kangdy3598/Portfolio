using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lazer : MonoBehaviour {

    public GameObject BackGround;
    private float StartTime;
    private bool b_GameOver;
    // Use this for initialization
    void Start () {

        StartTime = 0;
        b_GameOver = false;
	}
	
	// Update is called once per frame
	void Update () {

        if(StartTime < 1.0f) StartTime += Time.deltaTime;

        else transform.Translate(-Time.deltaTime, 0, 0);

        if (b_GameOver || Player.trans.GetComponent<Player>().HPImage.fillAmount == 0) BackGround.SetActive(true);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.transform.tag == "Player")
        {
            b_GameOver = true;
            Score.EndGame++;
        } 
    }
}
