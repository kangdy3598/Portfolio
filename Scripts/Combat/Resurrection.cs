using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Resurrection : MonoBehaviour
{
    private void Start()
    {
        PlayerInfo.Instance.playerHPComp.deadEvent += OnEnableUI;

        gameObject.SetActive(false);
        //PlayerInfo.Instance.deadEvent += OnEnableUI;
    }
    public void OnEnableUI()
    {
        gameObject.SetActive(true);
        
    }
    public void ResurrectionOnButton()
    {
        gameObject.SetActive(false);
        PlayerInfo.Instance.playerHPComp.Resurrection();
    }
}
