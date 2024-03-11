using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JinHilla : MonoBehaviour
{
    BehaviorTreeRunner behaviorTreeRunner;

    public Transform target { get; set; }

    private struct Teleport
    {
        public TeleportNode comp { get; set; }
        public SelectorNode node { get; set; }
    }
    private Teleport teleportNode;

    [System.Serializable]
    public struct Skill01
    {
        public Skill01Node comp { get; set; }
        public SequenceNode node { get; set; }
        public GameObject[] skillObject;
    }
    public Skill01 skill01Node;

    [System.Serializable]
    public struct Skill04
    {
        public Skill04Node comp { get; set; }
        public SequenceNode node { get; set; }
        public GameObject skillObject;
    }
    public Skill04 skill04Node;

    [System.Serializable]
    public struct Skill05
    {
        public Skill05Node comp { get; set; }
        public SequenceNode node { get; set; }
    }
    public Skill05 skill05Node;
    INode SetBehaviorTree()
    {
        SetNode();
        return new SelectorNode
            (
                new List<INode>()
                {
                    teleportNode.node,
                    new RandomSelectorNode
                    (
                        new List<INode>()
                        {
                            skill01Node.node,
                            skill04Node.node,
                            skill05Node.node,
                        }
                    ),
                    
                    new SequenceNode
                    (
                        new List<INode>()
                        {
                            new ActionNode(MoveToTarget),
                        }
                    ),
                }
            );
    }

    private void SetNode()
    {
        Animator anim = GetComponent<Animator>();

        teleportNode.comp = new TeleportNode(PlayerInfo.Instance.transform, anim, transform);
        teleportNode.node = teleportNode.comp.SetNode();

        // 초앞보뒤
        skill01Node.comp = new Skill01Node(PlayerInfo.Instance.transform, anim, transform);
        skill01Node.node = skill01Node.comp.SetNode(0);
        skill01Node.comp.skillObject = skill01Node.skillObject;

        // 고근
        skill04Node.comp = new Skill04Node(PlayerInfo.Instance.transform, anim, transform);
        skill04Node.node = skill04Node.comp.SetNode(0);
        skill04Node.comp.skillObject = skill04Node.skillObject;

        // 파바
        skill05Node.comp = new Skill05Node(PlayerInfo.Instance.transform, anim, transform);
        skill05Node.node = skill05Node.comp.SetNode(1);
    }

    private void Start()
    {
        behaviorTreeRunner = new BehaviorTreeRunner(SetBehaviorTree());

        target = PlayerInfo.Instance.transform;
        
    }
    private void Update()
    {
        //transform.position = teleport.pos;
        behaviorTreeRunner.Operate();
    }

    Vector3 SetPositionX(float newValue, Vector3 targetPosition)
    {
        targetPosition.x = newValue;
        return targetPosition;
    }

    INode.NodeState MoveToTarget()
    {
        if (Vector3.SqrMagnitude(target.position - transform.position) < 1)
        {
            return INode.NodeState.SUCCESS;
        }

        if (transform.position.x < target.position.x)
            GetComponent<SpriteRenderer>().flipX = true;
        else
            GetComponent<SpriteRenderer>().flipX = false;

        float changePostionX = Mathf.MoveTowards(transform.position.x, target.position.x, Time.deltaTime);
        transform.position = SetPositionX(changePostionX, transform.position);

        return INode.NodeState.RUNNING;

    }

    private void OnDrawGizmos()
    {
        Gizmos.color = Color.green;
        Gizmos.DrawWireCube(transform.position, Vector3.one * 30);
        // teleport
        Gizmos.color = Color.blue;
        Gizmos.DrawWireSphere(transform.position, 3.86f);

        // attack
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(transform.position, 1.5f);


    }

    public void ObjectPoolPop(GameObject ob)
    {
        GameObject objectName = ObjectPool.Instance.PopFromPool(ob.name);
        if (objectName != null)
        {
            Vector3 objectPosition = objectName.transform.position;
            objectPosition.x = transform.position.x;
            objectName.transform.position = objectPosition;
            objectName.SetActive(true);
        }
    }
}
