using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraSetting : MapInfo
{
    //DeadZone : �÷��̾ ������ �ȿ� ������ ī�޶�� �̵����� ����
    //SoftZone : DeadZone �ۿ� SoftZone ����. �÷��̾ �̰��� �����ϸ� ī�޶�� ������ ����(�� �ָ� �ϼ��� ī�޶� ���� ����)
    //Damping : 
    private Vector3 nowPosition;
    private float damping;

    public GameObject DeadZone, SoftZone;
    private void Start()
    {
        nowPosition = Camera.main.transform.position;
        damping = 3.5f;
    }
    private void LateUpdate()
    {
        MoveCameraPosistion();
        
    }

    private void MoveCameraPosistion()
    {
        if (!OutOfDeadZone())
            return;

        SetCameraLimit(ref nowPosition);
    }
    private void SetCameraLimit(ref Vector3 _nowPosition)
    {
        
        _nowPosition = Vector2.MoveTowards(_nowPosition, PlayerInfo.Instance.nowPosition, damping * Time.deltaTime);
        _nowPosition.z = -10;

        Vector2[] nowCameraWorldLTRB = ReturnLTRB(_nowPosition, Screen.width, Screen.height);
        
        if (nowCameraWorldLTRB[0].x < mapLimitPosLT.x)
            _nowPosition.x = Camera.main.transform.position.x;

        if (nowCameraWorldLTRB[1].x > mapLimitPosRB.x)
            _nowPosition.x = Camera.main.transform.position.x;

        if (nowCameraWorldLTRB[0].y > mapLimitPosLT.y)
            _nowPosition.y = Camera.main.transform.position.y;

        if (nowCameraWorldLTRB[1].y < mapLimitPosRB.y)
            _nowPosition.y = Camera.main.transform.position.y;

        Camera.main.transform.position = _nowPosition;
    }

    bool OutOfDeadZone()
    {
        Vector2[] playerLTRB = ReturnLTRB(PlayerInfo.Instance.nowPosition, PlayerInfo.Instance.nowScale);
        Vector2[] deadLTRB = ReturnLTRB(DeadZone.transform.position, DeadZone.transform.localScale);

        if (playerLTRB[0].x < deadLTRB[0].x)
            return true;

        if (playerLTRB[1].x > deadLTRB[1].x)
            return true;

        if (playerLTRB[0].y > deadLTRB[0].y)
            return true;

        if (playerLTRB[1].y < deadLTRB[1].y)
            return true;

        return false;
    }

    Vector2[] ReturnLTRB(Vector2 anchorPosition, float sizeX, float sizeY)
    {
        // ���� ī�޶� ���� ��ǥ -> ��ũ�� ��ǥ�� ��ȯ
        // ���� ��ũ�� �ʺ� ���� ���� ����
        // �ٽ� ���� ��ǥ�� ��ȯ

        
        Vector2 screenPoistion = Camera.main.WorldToScreenPoint(anchorPosition);
        
        Vector2 LT = new Vector2(screenPoistion.x - sizeX/2, screenPoistion.y + sizeY/2);
        Vector2 RB = new Vector2(screenPoistion.x + sizeX/2, screenPoistion.y - sizeY/2);

        Vector2 worldLT = Camera.main.ScreenToWorldPoint(LT);
        Vector2 worldRB = Camera.main.ScreenToWorldPoint(RB);

        Vector2[] returnValue = { worldLT, worldRB };
       
        return returnValue;
    }

    Vector2[] ReturnLTRB(Vector2 anchorPosition, Vector3 size)
    {
        Vector2 screenPoistion = Camera.main.WorldToScreenPoint(anchorPosition);
        Vector2 screenSize = Camera.main.WorldToScreenPoint(new Vector2(size.x / 2, size.y / 2));

        Debug.Log(screenSize);
        Vector2 LT = new Vector2(screenPoistion.x - screenSize.x, screenPoistion.y + screenSize.y);
        Vector2 RB = new Vector2(screenPoistion.x + screenSize.x, screenPoistion.y - screenSize.y);

        Vector2 worldLT = Camera.main.ScreenToWorldPoint(LT);
        Vector2 worldRB = Camera.main.ScreenToWorldPoint(RB);

        Vector2[] returnValue = { worldLT, worldRB };

        return returnValue;
    }
}
