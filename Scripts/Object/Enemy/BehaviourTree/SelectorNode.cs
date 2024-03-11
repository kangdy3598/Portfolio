using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public sealed class SelectorNode :INode
{
    List<INode> _childs;

    public SelectorNode(List<INode> childs)
    {
        _childs = childs;
    }

    public override INode.NodeState Evaluate(/*int value = 0*/)
    {
        if (_childs == null)
            return INode.NodeState.FAILURE;

        foreach(var child in _childs)
        {
            switch(child.Evaluate())
            {
                case INode.NodeState.RUNNING:
                    return INode.NodeState.RUNNING;
                case INode.NodeState.SUCCESS:
                    return INode.NodeState.SUCCESS;
            }
        }

        return INode.NodeState.FAILURE;
    }
}
