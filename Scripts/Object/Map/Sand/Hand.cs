using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hand : MonoBehaviour
{
    [SerializeField] private Animator[] stringAnim;

    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void enable()
    {
        for (int i = 0; i < stringAnim.Length; i++)
        {
            stringAnim[i].gameObject.SetActive(true);
        }
    }
    public void disable()
    {
        for (int i = 0; i < stringAnim.Length; i++)
        {
            stringAnim[i].gameObject.SetActive(false);
        }
    }
    public void Anima()
    {
        for(int i=0; i<stringAnim.Length; i++)
        {
            stringAnim[i].SetBool("shoot", true);
        }
    }
}
