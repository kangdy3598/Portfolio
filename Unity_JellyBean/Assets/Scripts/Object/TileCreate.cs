using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TileCreate : MonoBehaviour {

    public GameObject[] TileObject = new GameObject[3];
    public GameObject temp;
    private Vector2 pos;
	// Use this for initialization
	void Start () {

        pos = transform.position;

        for (int i = 0; i < TileObject.Length; i++)
        {
            TileObject[i] = ObjectPool.Instance.PopFromPool("Tile");
            if (TileObject[i] != null)
            {
                TileObject[i].SetActive(true);
                TileObject[i].transform.position = pos;
                pos.y += 12;

            }
        }

    }
	
	// Update is called once per frame
	void Update () {

        if (Player.trans.position.y > TileObject[2].transform.position.y)
        {
            temp = TileObject[0];
            TileObject[0] = TileObject[1]; TileObject[1] = TileObject[2]; TileObject[2] = TileObject[3];
            TileObject[3] = temp; ObjectPool.Instance.PushToPool(TileObject[3].name, TileObject[3]);
            TileObject[3] = ObjectPool.Instance.PopFromPool("Tile");
            if (TileObject[3] != null)
            {
                TileObject[3].SetActive(true);
                TileObject[3].transform.position = pos;
                pos.y += 12;

            }
        }
    }
}
