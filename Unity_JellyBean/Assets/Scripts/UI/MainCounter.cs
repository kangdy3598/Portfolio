using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MainCounter : MonoBehaviour {

    private Text txt;

    // Use this for initialization
    void Start () {
        txt = GetComponent<Text>();
    }
	
	// Update is called once per frame
	void Update () {

        switch(transform.name)
        {
            case "CrystalText":
                txt.text = CharacterSell.MyMoney.ToString();//CharacterSell.Instance.MyMoney.ToString();
                break;
            case "BehaviorText":
             //   txt.text = Behavior.Instance.bfr[0]["Behavior"].ToString();
                break;
        }
        
	}
}
