using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public sealed class ActionNode : INode
{
    Func</*int, */INode.NodeState> _onUpdate = null;

    public ActionNode(Func</*int, */INode.NodeState> onUpdate, float probability = 0.0f)
    {
        _probability = probability;
        _onUpdate = onUpdate;
    }

     public override INode.NodeState Evaluate(/*int value = 0*/) => _onUpdate?.Invoke(/*value*/) ?? INode.NodeState.FAILURE;
    //public INode.NodeState Evaluate(int parameter = 0)
    //{
    //    return _onUpdate?.Invoke(parameter) ?? INode.NodeState.FAILURE;
    //}
}
