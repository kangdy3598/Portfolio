using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Altar : MonoBehaviour, IInteractionComp
{
    private Animator altarAnim;

    private int altarState;
    private int interactionCount;

    public DeathCount deathcount;
 
    void Awake()
    {
        altarAnim = GetComponent<Animator>();

        altarState = 0;
        interactionCount = 0;
    }

    private void OnEnable()
    {
        altarState = 0;
        interactionCount = 0;
        altarAnim.SetInteger("state", 0);

        Vector3 pos = transform.position;
        pos.x = Random.Range(-4.0f, 6.0f);
        transform.position = pos;
    }
    // Update is called once per frame
    void Update()
    {
        if (interactionCount == 5)
        {
            altarAnim.SetInteger("state", ++altarState);
            interactionCount = 0;
            
        }
    }
    public void InteractionKeyDown()
    {
        interactionCount++;
    }
    public void InteractionKeyUp()
    {

    }

    // Animation Frame에 의해 제어
    public void SetRedToWhite()
    {
        //deathcount.RedToWhite();
        GameManager.Instance.clearDeathCountAction.Invoke();
    }
    public void SetDisableObject()
    {
        gameObject.SetActive(false);
    }
}
