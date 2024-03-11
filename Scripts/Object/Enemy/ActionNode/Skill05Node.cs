using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Skill05Node
{
    public Skill05Node(Transform _target, Animator _anim, Transform _parent)
    {
        target = _target;
        anim = _anim;
        parent = _parent;

        attackComp = parent.GetComponent<AttackComponent>();
    }

    private Transform target;
    private Animator anim;
    private Transform parent;
    private AttackComponent attackComp;

    #region SkillProperties

    private readonly string skillAnimName = "Skill05";
    private readonly int skillNumber = 5;
    private readonly string playAnimName = "state";
    private readonly int idleAnimNum = 0;

    private float attackCooldownTimer = 0.0f, attackCooldown = 5.0f;
    private float attackRange = 1.5f;
    #endregion

    public SequenceNode SetNode(float _probability)
    {
        // 쿨타임이 돌았는가 -> 타겟이 공격 범위 안에 있는가 -> 공격 시작
        // 쿨타임이 안 돌았거나 타겟이 공격 범위 안에 없다면
        // 이 노드 밖으로 나감

        SequenceNode node = new SequenceNode(new List<INode>()
        {
            new SequenceNode
            (
                new List<INode>()
                {
                    new ActionNode(CheckAttacking),
                    new ActionNode(CheckCoolTime),
                    new ActionNode(CheckRange),
                    new ActionNode(DoAttack),
                }
            ),
        });

        node._probability = _probability;

        return node;
    }

    #region Skill

    // 공격 중인지 체크용 함수
    INode.NodeState CheckAttacking()
    {
        if (IsAnimationPlaying(skillAnimName))
        {
            //AttackSkillObject();
            //Debug.Log("check attacking running");
            return INode.NodeState.RUNNING;
        }

        anim.SetInteger(playAnimName, idleAnimNum);
        //Debug.Log("check attacking success");
        return INode.NodeState.SUCCESS;
    }

    // 쿨타임 체크용 함수
    INode.NodeState CheckCoolTime()
    {
        if (attackCooldownTimer <= 0)
        {
            //Debug.Log("skill01 checkcooltime success");
            return INode.NodeState.SUCCESS;
        }

        //Debug.Log("skill01 checkcooltime failure");
        attackCooldownTimer -= Time.deltaTime;
        return INode.NodeState.FAILURE;
    }

    // 범위 체크용 함수
    INode.NodeState CheckRange()
    {
        if (Vector3.SqrMagnitude(target.position - parent.position) < (attackRange * attackRange))
        {
            //Debug.Log("skill01 CheckRange success");
            return INode.NodeState.SUCCESS;
        }
        //Debug.Log("skill01 CheckRange failure");
        return INode.NodeState.FAILURE;
    }

    // 공격 시작
    INode.NodeState DoAttack()
    {
        if (anim.GetInteger(playAnimName) == idleAnimNum)
        {
            //Debug.Log("skill01 DoAttack success");
            attackComp.nowAttackInfo = attackComp.attackInfoList[2];
            anim.SetTrigger("attack");
            anim.SetInteger(playAnimName, skillNumber);
            attackCooldownTimer = attackCooldown;
            return INode.NodeState.RUNNING;
        }


        //Debug.Log("skill01 DoAttack failure");
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
}
