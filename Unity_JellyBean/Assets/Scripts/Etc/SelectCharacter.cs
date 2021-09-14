using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct CInfo
{
    public int Price;
    public int IsSell;

    public CInfo(int Price, int IsSell)
    {
        this.Price = Price;
        this.IsSell = IsSell;
    }
}

public class SelectCharacter : MonoBehaviour {
    public GameObject[] Character;
    public static CInfo[] CharacterList = new CInfo[]
        {new CInfo (0, 1),
            new CInfo (500,0)
        };
    
    public GameObject SellButton;

    public static int Num = 0;
    public static int Count;

    private Animator Ani;
    private SpriteRenderer Spr;
    private Color Clr;

	// Use this for initialization
	void Start () {
        
        Ani = GetComponent<Animator>();
        Spr = GetComponent<SpriteRenderer>();
        
        Ani.runtimeAnimatorController = Character[0].GetComponent<Animator>().runtimeAnimatorController;
        Count = Character.Length;
}
    // Update is called once per frame
    void Update () {

        if (CharacterList[Num].IsSell == 0)
        {
            SellButton.SetActive(true);
            Clr = Color.black;
            Ani.runtimeAnimatorController = Character[Num].GetComponent<Animator>().runtimeAnimatorController;
            Spr.color = Clr;
        }
        else
        {
            SellButton.SetActive(false);
            Clr = Color.white;
            Ani.runtimeAnimatorController = Character[Num].GetComponent<Animator>().runtimeAnimatorController;
            Spr.color = Clr;
        }
    }
}
