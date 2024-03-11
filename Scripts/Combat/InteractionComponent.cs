using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InteractionComponent : MonoBehaviour
{
    private KeyCode interactionKey;
    private bool isTriggerStay;
    IInteractionComp IinteractionComp;
    private void Awake()
    {
        interactionKey = KeyCode.Space;
        isTriggerStay = false;
        IinteractionComp = GetComponent<IInteractionComp>();
    }

    private void Update()
    {
        if (!isTriggerStay)
            return;

        if (Input.GetKeyDown(interactionKey))
            IinteractionComp.InteractionKeyDown();

        if (Input.GetKeyUp(interactionKey))
            IinteractionComp.InteractionKeyUp();

    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        HitComponent hitComp = collision.GetComponent<HitComponent>();
        if (!hitComp)
            return;

        isTriggerStay = true;
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        HitComponent hitComp = collision.GetComponent<HitComponent>();
        if (!hitComp)
            return;

        isTriggerStay = false;
    }
}

public interface IInteractionComp
{
    void InteractionKeyDown();
    void InteractionKeyUp();
}
