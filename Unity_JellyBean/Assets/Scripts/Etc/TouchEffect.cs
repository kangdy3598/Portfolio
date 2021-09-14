using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TouchEffect : MonoBehaviour {

    public ParticleSystem TouchParticle;
    private Vector3 particlePos;
    // Use this for initialization
    void Start () {
    }
	
	// Update is called once per frame
	void Update () {
		
        if(Input.GetMouseButtonDown(0))
        {
            particlePos = Input.mousePosition;
            particlePos.z = 10;
            TouchParticle.transform.position= Camera.main.ScreenToWorldPoint(particlePos);
            TouchParticle.Play();
        }
	}
}
