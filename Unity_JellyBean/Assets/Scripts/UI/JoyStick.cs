using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class JoyStick : MonoBehaviour, IPointerDownHandler, IPointerUpHandler,IDragHandler
{
    public GameObject bgObject, knobObject, AttackObject, JumpObject;
    private Image bgImage;

    public GameObject TransObject;
    private Image TransImage;
    public Sprite HumanImage, SlimeImage;

    private int TouchNumber;
    private Vector3 dir;
    public int Axis_X, Axis_Y;
    public bool b_Jump, b_Attack;
    void Start()
    {
        bgImage = bgObject.GetComponent<Image>();
        TransImage = TransObject.GetComponent<Image>();

        TouchNumber = -1;
        Axis_X = Axis_Y = 0;
        b_Jump = b_Attack = false;
    }

    private void Update()
    {
        if (Player.C_Form == Player.PlayerForm.SLIME)
        {
            AttackObject.SetActive(false);
            TransImage.sprite = HumanImage;
        }
        else
        {
            AttackObject.SetActive(true);
            TransImage.sprite = SlimeImage;
        }
        if(Input.touchCount > 0)
        {
            Touch[] touch = Input.touches;
            for (int i = 0; i < Input.touchCount; i++)
            {
                switch (touch[i].phase)
                {
                    case TouchPhase.Began:
                        if (DistanceButton(AttackObject, touch[i].position)) b_Attack = true;
                        else if (!b_Jump && DistanceButton(JumpObject, touch[i].position)) b_Jump = true;
                        break;
                    case TouchPhase.Ended:
                        if (DistanceButton(AttackObject, touch[i].position)) b_Attack = false;
                        break;
                }
            }
        }
    }
    // 조이스틱 관련
    public virtual void OnDrag(PointerEventData ped)
    {
        if(TouchNumber == ped.pointerId)
        {
            dir = (ped.position - (Vector2)bgObject.transform.position).normalized;
            if (DistanceButton(bgObject, ped.position)) knobObject.transform.position = ped.position;
            else knobObject.transform.position = bgObject.transform.position + bgImage.rectTransform.sizeDelta.x / 2 * dir;

            if (dir.y <= -0.3) Axis_Y = -1;
            else if (dir.y <= 0.3) Axis_Y = 0;
            else Axis_Y = 1;

            if (dir.x < -0.3) Axis_X = -1;
            else if (dir.x > 0.3) Axis_X = 1;
            else Axis_X = 0;

        }
    }
    public void OnPointerDown(PointerEventData ped)
    {
        if (!bgObject.activeSelf)
        {
            bgObject.SetActive(true);
            bgObject.transform.position = ped.position;
            TouchNumber = ped.pointerId;
            OnDrag(ped);
        }
    }
    public void OnPointerUp(PointerEventData ped)
    {
        if (bgObject.activeSelf)
        {
            bgObject.SetActive(false);
            TouchNumber = -1;
            Axis_X = Axis_Y = 0;
            b_Jump = b_Attack = false;
        }
    }


    public bool DistanceButton(GameObject Button, Vector2 touchPos)
    {
        // 버튼 위치에서 터치 위치까지 거리가 버튼 반지름보다 작다면 버튼을 터치 중임
        if (Vector2.Distance(touchPos, Button.transform.position) <
            Button.GetComponent<Image>().rectTransform.sizeDelta.x / 2) return true;


        else return false;
    }
}
