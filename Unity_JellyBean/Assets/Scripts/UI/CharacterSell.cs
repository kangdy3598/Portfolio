using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CharacterSell : MonoBehaviour {


    public GameObject Sellable;
    public GameObject Result;

    public Sprite NotSellSpr;
    //public List<Dictionary<string, object>> sfr;

    public static int MyMoney = 1000, num;
    private static CharacterSell instance = null;
    //public static CharacterSell Instance
    //{
    //    get
    //    {
    //        if (instance == null)
    //            instance = GameObject.FindObjectOfType<CharacterSell>() as CharacterSell;

    //        return instance;
    //    }
    //}
    void Start()
    {
        //sfr = CSVReader.Read("Main/CSV/CharacterShop");
        
    }
    public void ClickSellButton()
    {
        if(MyMoney >= 500)
        {
            Sellable.SetActive(true);
        }
        else
        {
            Result.GetComponent<Image>().sprite = NotSellSpr;
            Result.SetActive(true);
        }
        //if((int)sfr[0]["MyMoney"] >= (int)sfr[SelectCharacter.Num]["Price"])
        //{
        //    // 1)
        //    Sellable.SetActive(true);
        //}
        //else
        //{
        //    // 2)
        //    Result.GetComponent<Image>().sprite = NotSellSpr;
        //    Result.SetActive(true);
        //}
    }

}
