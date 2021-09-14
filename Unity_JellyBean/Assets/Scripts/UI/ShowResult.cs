using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ShowResult : MonoBehaviour {
    
    private Text MeterText,
                 BreakText,
                 GoldText,
                 CrystalText,
                 TotalText;

    public GameObject Meter,
                      Break,
                      Gold,
                      Crystal,
                      Total;

    
	// Use this for initialization
	void Start () {
        
       

	}

    public void OnEnable()
    {
        int Hnum = (int)Score.Height; 
        MeterText = Meter.GetComponent<Text>();
        MeterText.text = Hnum.ToString();

        BreakText = Break.GetComponent<Text>();
        BreakText.text = Score.DestroyOb.ToString();

        GoldText = Gold.GetComponent<Text>();
        GoldText.text = Score.GetCoin.ToString();

        CrystalText = Crystal.GetComponent<Text>();
        CrystalText.text = "3";

        TotalText = Total.GetComponent<Text>();
        TotalText.text = (Hnum * 10 + Score.DestroyOb * 50 + Score.GetCoin * 100 + 3 * 5).ToString();
    }
}
