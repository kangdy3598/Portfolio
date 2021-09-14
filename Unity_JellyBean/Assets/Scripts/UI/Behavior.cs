using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Behavior : MonoBehaviour {

    public List<Dictionary<string, object>> bfr;

    private static Behavior instance = null;
    public static Behavior Instance
    {
        get
        {
            if (instance == null)
                instance = GameObject.FindObjectOfType<Behavior>() as Behavior;

            return instance;
        }
    }
    void Start()
    {
        bfr = CSVReader.Read("Main/CSV/Behavior");
    }

    private void Update()
    {
        if((int)bfr[0]["Behavior"] < 60)
        {

        }
    }
}
