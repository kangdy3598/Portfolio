using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FallingCreate : MonoBehaviour {

    private string[] FallingName = { "Fire", "Solid"};

    private bool b_Respon = true;
    private Vector2 CreatePos;

    public static int Floor = 1;
    
    // Use this for initialization
    void Start () {


    }
	
	// Update is called once per frame
	void Update () {

        if(b_Respon)
        {
            int Count = Random.Range(0, 2);
            GameObject FallingObject = ObjectPool.Instance.PopFromPool(FallingName[Count]);
            if (FallingObject != null)
            {
                CreatePos = Player.trans.position;
                CreatePos.y += 15;
                FallingObject.transform.position = CreatePos;
                FallingObject.SetActive(true);
            }
            b_Respon = false;
            StartCoroutine(spontTime());
        }
    }

    IEnumerator spontTime()
    {
        yield return new WaitForSeconds(2.5f);
        b_Respon = true;
    }
}
