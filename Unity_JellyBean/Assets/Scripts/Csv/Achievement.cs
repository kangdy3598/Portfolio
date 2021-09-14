using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Achievement : MonoBehaviour {

    public int Number;
    public GameObject[] Player;
    public Sprite AchieveSpr;

    public GameObject BarUI;
    public Sprite[] BarUISpr;
    //public List<Dictionary<string, object>> fr;
    //public List<Dictionary<string, object>> br;


    private Vector2 spawnPos;
    private static Achievement instance = null;
    public static Achievement Instance
    {
        get
        {
            if (instance == null)
                instance = GameObject.FindObjectOfType<Achievement>() as Achievement;

            return instance;
        }
    }

    // Use this for initialization
    void Awake () {

        //fr = CSVReader.Read("Main/CSV/Achievement");
        //br = CSVReader.Read("Main/CSV/Behavior");
        if (Number >= 0 && OverRestart.Clear[int.Parse(gameObject.name) -1] == 1)//&& (int)fr[Number]["Clear"] == 1)
        {
            GetComponent<Image>().sprite = AchieveSpr;
        }
        else if(Number == -1)
        {
            spawnPos = new Vector2(0, -8);
            Score.Player = Instantiate(Player[SelectCharacter.Num], spawnPos, Quaternion.identity);
            BarUI.GetComponent<Image>().sprite = BarUISpr[SelectCharacter.Num];
        }
    }

    public void ShowAchievementComplete(string name)
    {
        transform.GetChild(0).GetChild(0).GetComponent<Text>().text = name;
    }
}
