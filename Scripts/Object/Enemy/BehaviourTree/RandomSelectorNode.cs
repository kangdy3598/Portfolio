using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public sealed class RandomSelectorNode : INode
{
    INode _runningChild;
    List<INode> _childs;
    System.Random _random;

    public RandomSelectorNode(List<INode> childs)
    {
        _runningChild = null;
        _childs = childs;
        _random = new System.Random();
    }

    public override INode.NodeState Evaluate(/*int value = 0*/)
    {
        if (_childs == null)
            return INode.NodeState.FAILURE;

        if (_runningChild == null)
        {
            float randomValue = (float)_random.NextDouble();
            float cumulativeWeight = 0f;

            foreach(var child in _childs)
            {
                cumulativeWeight += child._probability;
                if(randomValue <= cumulativeWeight)
                {
                    _runningChild = child;
                    break;
                }
            }
        }

        switch (_runningChild.Evaluate())
        {
            case INode.NodeState.RUNNING:
                return INode.NodeState.RUNNING;
            case INode.NodeState.SUCCESS:
                _runningChild = null;
                return INode.NodeState.SUCCESS;
        }

        _runningChild = null;
        return INode.NodeState.FAILURE;
    }
}
