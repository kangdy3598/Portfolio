using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StatusComponent : MonoBehaviour
{
    private PlayerController playerController;
    private GameObject statusEffect;
    private float durationTime;

    private void Start()
    {
        playerController = transform.parent.GetComponent<PlayerController>();

    }
    private void Update()
    {
        if (!statusEffect || !statusEffect.activeSelf)
            return;

        durationTime -= Time.deltaTime;
        if(durationTime <= 0)
        {
            playerController.statusName = PlayerController.STATUSNAME.NONE;
            statusEffect.SetActive(false);
        }
    }

    public void SetStatus(string statusType, GameObject effect, float _durationTime)
    {
        statusEffect = effect;
        durationTime = _durationTime;

        switch (statusType)
        {
            case "Stun":
                playerController.statusName = PlayerController.STATUSNAME.STUN;
                break;
        }
        statusEffect.SetActive(true);
    }
}
