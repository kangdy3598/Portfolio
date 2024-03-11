using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RigidComponent : MonoBehaviour
{
    private float gravity;
    private bool onGround;

    public Rigidbody2D rigidbody2d { get; private set; }

    public Action footholdStayEvent { get; set; }
    //private Action footholdExitEvent;

    public bool GetOnGround()
    {
        return onGround;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.transform.tag != "Foothold")
            return;

        onGround = true;
    }
    private void OnCollisionStay2D(Collision2D collision)
    {
        if (collision.transform.tag != "Foothold")
            return;

        footholdStayEvent?.Invoke();
    }
    private void OnCollisionExit2D(Collision2D collision)
    {
        if (collision.transform.tag != "Foothold")
            return;

        //footholdExitEvent?.Invoke();
        onGround = false;
    }

    private void Awake()
    {
        onGround = false;
        rigidbody2d = GetComponent<Rigidbody2D>();
       // footholdCollsionEvent.AddListener
    }

    private void Update()
    {
       
    }
}
