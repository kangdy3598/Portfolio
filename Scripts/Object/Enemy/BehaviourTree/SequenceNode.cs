using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public sealed class SequenceNode : INode
{
    List<INode> _childs;

    public SequenceNode(List<INode> childs)
    {
        _childs = childs;
    }

    public override INode.NodeState Evaluate(/*int value = 0*/)
    {
        if (_childs == null || _childs.Count == 0)
            return INode.NodeState.FAILURE;

        foreach (var child in _childs)
        {
            switch (child.Evaluate())
            {
                case INode.NodeState.RUNNING:
                    return INode.NodeState.RUNNING;
                case INode.NodeState.SUCCESS:
                    continue;
                case INode.NodeState.FAILURE:
                    return INode.NodeState.FAILURE;
            }
        }

        return INode.NodeState.SUCCESS;
    }
}
