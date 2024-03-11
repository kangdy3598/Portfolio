using System;
using UnityEditor;
using UnityEditorInternal;
using UnityEngine;

[CustomEditor(typeof(AttackComponent))]
public class ObjectInspectorEditor : Editor
{
    AttackComponent obj;

    private void OnEnable()
    {
        obj = (AttackComponent)target;

    }
    
    public override void OnInspectorGUI()
    {
        base.OnInspectorGUI();
        serializedObject.Update();

        string[] options = { };

        SerializedProperty array = serializedObject.FindProperty("stringList");
        Array.Resize(ref options, array.arraySize);
        for (int i = 0; i < options.Length; i++)
        {
            options[i] = array.GetArrayElementAtIndex(i).stringValue;
        }

        obj.index = EditorGUILayout.Popup("AttackName", obj.index, options);
        //obj.nowAttackInfo.attackName = options[obj.index];
        
        serializedObject.ApplyModifiedProperties();
        
    }
}