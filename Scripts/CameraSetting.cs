using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraSetting : MapInfo
{
    //DeadZone : 플레이어가 데드존 안에 있으면 카메라는 이동하지 않음
    //SoftZone : DeadZone 밖에 SoftZone 존재. 플레이어가 이곳에 존재하면 카메라는 추적을 시작(더 멀리 일수록 카메라가 빨리 추적)
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
        // 현재 카메라 월드 좌표 -> 스크린 좌표로 변환
        // 현재 스크린 너비 높이 값을 증감
        // 다시 월드 좌표로 변환

        
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
