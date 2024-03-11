using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class INode
{
    public enum NodeState
    {
        RUNNING,
        SUCCESS,
        FAILURE,
    }

    public float _probability;
    public abstract NodeState Evaluate(/*int value = 0*/);
}
