using UnityEngine;
using System.Collections;


public class Singleton<T> : MonoBehaviour where T : MonoBehaviour
{
    private static T instance = null;

    public static T Instance
    {
        get
        {
            if (instance == null)
                instance = GameObject.FindObjectOfType<T>() as T;

            return instance;
        }
    }
}
