using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;

public class CloseUI : MonoBehaviour {

    public GameObject Result;
    public Sprite CompleteSellSpr;

    public CsvFileWriter sfw;

    private List<string> columns;
    private int MyMoney, Num;

    public void ClickClose()
    {
        //MyMoney = (int)CharacterSell.Instance.sfr[0]["MyMoney"];
        Num = SelectCharacter.Num;

        switch (transform.name)
        {
            case "SellYes":
                //   MyMoney -= (int)CharacterSell.Instance.sfr[SelectCharacter.Num]["Price"];
                //using (sfw = new CsvFileWriter("Assets/Resources/Main/CSV/CharacterShop.csv"))
                //{
                //    columns = new List<string>() { "Name", "Price", "Sell", "MyMoney" };

                //    sfw.WriteRow(columns);
                //    columns.Clear();

                //    columns.Add("Char1"); columns.Add("0"); columns.Add("1"); columns.Add(MyMoney.ToString());
                //    sfw.WriteRow(columns);
                //    columns.Clear();

                //    columns.Add("Char2"); columns.Add("500");
                //    if(Num == 1) columns.Add("1");
                //   // else if((int)CharacterSell.Instance.sfr[SelectCharacter.Num]["Sell"] != 1) columns.Add("0");
                //    sfw.WriteRow(columns);
                //    columns.Clear();

                //    sfw.Dispose();
                //}
                CharacterSell.MyMoney -= 500; //CharacterSell.Instance.MyMoney -= 500;
                SelectCharacter.CharacterList[1].IsSell = 1;
                Result.GetComponent<Image>().sprite = CompleteSellSpr;
                Result.SetActive(true);
                
                //CharacterSell.Instance.sfr = CSVReader.Read("Main/CSV/CharacterShop");

                break;
            case "SellNo":
                break;
            case "SellOK":
                break;
            case "Close":
                break;
        }
        
        transform.parent.gameObject.SetActive(false);
    }
}
