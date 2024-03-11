using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Skill01Node
{
    public Skill01Node(Transform _target, Animator _anim, Transform _parent)
    {
        target = _target;
        anim = _anim;
        parent = _parent;
    }

    private Transform target;
    private Animator anim;
    private Transform parent;

    #region SkillProperties
    public GameObject[] skillObject;

    private readonly string playAnimName = "state";
    private readonly int idleAnimNum = 0;
    private readonly int skillTypeCount = 2;

    private float attackCooldownTimer = 0.0f, attackCooldown = 30.0f;
    private float attackRange = 1.5f;
    #endregion

    public SequenceNode SetNode(float _probability)
    {
        // ��Ÿ���� ���Ҵ°� -> Ÿ���� ���� ���� �ȿ� �ִ°� -> ���� ����
        // ��Ÿ���� �� ���Ұų� Ÿ���� ���� ���� �ȿ� ���ٸ�
        // �� ��� ������ ����
        
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

    #region Teleport
    
    // ���� ������ üũ�� �Լ�
    INode.NodeState CheckAttacking()
    {
        int skillNumber = anim.GetInteger(playAnimName) ;

        if(IsAnimationPlaying("Skill0" + skillNumber))
        {
            return INode.NodeState.RUNNING;
        }

        anim.SetInteger(playAnimName, idleAnimNum);
        return INode.NodeState.SUCCESS;
    }

    // ��Ÿ�� üũ�� �Լ�
    INode.NodeState CheckCoolTime()
    {
        if (attackCooldownTimer <= 0)
        {
            return INode.NodeState.SUCCESS;
        }

        attackCooldownTimer -= Time.deltaTime;
        return INode.NodeState.FAILURE;
    }

    // ���� üũ�� �Լ�
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

    // ���� ����
    INode.NodeState DoAttack()
    {
        if (anim.GetInteger(playAnimName) == idleAnimNum)
        {
            int type = Random.Range(1, skillTypeCount+1); // 1 or 2
            anim.SetTrigger("attack");
            anim.SetInteger(playAnimName, type);
            attackCooldownTimer = attackCooldown;
            return INode.NodeState.RUNNING;
        }

        return INode.NodeState.FAILURE;
    }

    
    #endregion

    //void AttackSkillObject(int skillType)
    //{
    //    AnimatorClipInfo[] clipInfo = anim.GetCurrentAnimatorClipInfo(0);
    //    AnimationClip currentClip = clipInfo[0].clip;
    //    float frameCount = currentClip.length * currentClip.frameRate;

    //    AnimatorStateInfo stateInfo = anim.GetCurrentAnimatorStateInfo(0);
    //    float normalizedTime = stateInfo.normalizedTime;
    //    int currentFrame = Mathf.FloorToInt(normalizedTime * frameCount) % Mathf.FloorToInt(frameCount);

    //    if (currentFrame == objectFrame)
    //    {
    //        skillObject[skillType-1].SetActive(true);
    //    }
    //}

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
