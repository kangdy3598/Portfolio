using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TeleportNode
{
    public TeleportNode(Transform _target, Animator _anim, Transform _parent)
    {
        target = _target;
        target_player = _target;
        anim = _anim;
        parent = _parent;
    }

    private Transform target;
    private Transform target_player;
    private Animator anim;
    private Transform parent;

    private readonly string playAnimString = "state";
    private readonly int idleAnimNum = 0;
    private readonly int startTeleportAnimNum = 2;
    private readonly int endTeleportAnimNum = 3;

    private float teleportPostionX = 0.0f;
    private float teleportRange = 3.86f;
    private float detectAltarRange = 10.0f;
    private float teleportCooldownTimer = 0.0f, teleportCooldown = 15.0f;
    private float endTeleportTimer = 0.0f;

    public SelectorNode SetNode()
    {
        // 쿨타임이 돌았는가 -> 타겟이 텔레포트 범위 안에 있는가 -> 텔레포트 시작
        // -> 1초 후 텔레포트 시작 했을 때 타겟이 있는 위치로 이동
        // 쿨타임이 안 돌았거나 타겟이 텔레포트 범위 안에 없다면
        // 이 노드 밖으로 나감

        SelectorNode node = new SelectorNode(new List<INode>()
        {
            new SequenceNode
            (
                new List<INode>()
                {
                    new ActionNode(CheckCoolTime),
                    new ActionNode(CheckTarget),
                    new ActionNode(CheckRange),
                    new ActionNode(StartTeleport),
                }
            ),
            new SequenceNode
            (
                new List<INode>()
                {
                    new ActionNode(EndTeleport),
                }
            ),
        });

        return node;
    }

    #region Teleport

    // 쿨타임 체크용 함수
    INode.NodeState CheckCoolTime()
    {
        if (teleportCooldownTimer <= 0)
        {
            //Debug.Log("teleport checkcooltime success");
            return INode.NodeState.SUCCESS;
        }

        //Debug.Log("teleport checkcooltime failure");
        teleportCooldownTimer -= Time.deltaTime;
        return INode.NodeState.FAILURE;
    }

    INode.NodeState CheckTarget()
    {
        var overlapColliders = Physics2D.OverlapBoxAll(parent.position, Vector2.one * 30, 0, LayerMask.GetMask("Altar"));
        
        if (overlapColliders != null && overlapColliders.Length > 0)
        {
            target = overlapColliders[0].transform;
            return INode.NodeState.SUCCESS;
        }
        //Debug.Log("!!");
        target = target_player;
        return INode.NodeState.SUCCESS;
    }
    // 범위 체크용 함수
    INode.NodeState CheckRange()
    {
        //Debug.Log("target layer name : " + target.gameObject.layer);
        //Debug.Log("get mask : " + LayerMask.GetMask("Altar"));
        if (target.gameObject.layer == LayerMask.NameToLayer("Altar"))
            return INode.NodeState.SUCCESS;

        if (Vector3.SqrMagnitude(target.position - parent.position) < (teleportRange * teleportRange))
        {
            //Debug.Log("teleport checkrange success");
            return INode.NodeState.SUCCESS;
        }
        //Debug.Log("teleport checkrange failure");
        return INode.NodeState.FAILURE;
    }

    // 텔레포트 시작
    INode.NodeState StartTeleport()
    {
        //Debug.Log("teleport start teleport");
        anim.SetInteger(playAnimString, startTeleportAnimNum);

        teleportPostionX = target.position.x;
        teleportCooldownTimer = teleportCooldown;
        endTeleportTimer = 1.0f;

        return INode.NodeState.SUCCESS;
    }

    // 텔레포트 끝
    INode.NodeState EndTeleport()
    {
        if (anim.GetInteger(playAnimString) == startTeleportAnimNum)
        {
            // 1초가 안 지났다면 그냥 넘어감
            if (endTeleportTimer > 0)
            {
                //Debug.Log("endteleport running");
                endTeleportTimer -= Time.deltaTime;
                return INode.NodeState.RUNNING;
            }

            // 1초 후, 텔레포트 시작할 때 타겟의 위치로 이동하면서 애니메이션 출력
            parent.position = SetPositionX(teleportPostionX, parent.position);
            anim.SetInteger(playAnimString, endTeleportAnimNum);

            //Debug.Log("endteleport success");
            return INode.NodeState.SUCCESS;
        }

        if (anim.GetInteger(playAnimString) == endTeleportAnimNum)
        {
            if (IsAnimationPlaying("Skill03_After"))
            {
                //Debug.Log("is animation playing skill03_after");
                return INode.NodeState.RUNNING;
            }

            else
            {
                //Debug.Log("is not animation playing skill03_after");
                anim.SetInteger(playAnimString, idleAnimNum);
                return INode.NodeState.SUCCESS;
            }
        }
            

        // 최상위 노드는 SelectNode로, 다른 노드로 넘어가기 위해서 return Failure
        //Debug.Log("endteleport failure");
        //anim.SetInteger(playAnimString, idleAnimNum);
        return INode.NodeState.FAILURE;
    }

    #endregion

    bool IsAnimationPlaying(string stateName)
    {
        if (anim != null)
        {
            if (anim.GetCurrentAnimatorStateInfo(0).IsName(stateName))
            {
                var normalizedTime = anim.GetCurrentAnimatorStateInfo(0).normalizedTime;

                return normalizedTime < 1f;
            }
        }

        return false;
    }

    Vector3 SetPositionX(float newValue, Vector3 targetPosition)
    {
        targetPosition.x = newValue;
        return targetPosition;
    }
}