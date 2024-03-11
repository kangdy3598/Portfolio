using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEditor;
using System;

public class WindowEditor : MonoBehaviour
{
    [MenuItem("File/AttackListUpdate")]
    static void DomSomething()
    {
        var list = Selection.GetFiltered<GameObject>(SelectionMode.TopLevel);
        foreach(var obj in list)
        {
            var attackComponent = obj.GetComponent<AttackComponent>();
            if (!attackComponent) continue;

            // error : CS0206
            string[] temp = attackComponent.stringList;
            ReadFile(ref temp, ref attackComponent.attackInfoList);
            attackComponent.stringList = temp;
        }

        
    }

    static void ReadFile(ref string[] stringList, ref AttackComponent.AttackInfo[] attackInfoList)
    {
        string line;
        int count = 0;
        Array.Resize(ref stringList, count);
        Array.Resize(ref attackInfoList, count);

        FileStream file = new FileStream(Application.dataPath + "/Mainmap/Resources/Datas/Attack.txt", FileMode.Open);
        StreamReader reader = new StreamReader(file);

        while ((line = reader.ReadLine()) != null)
        {
            if (stringList.Length <= count)
            {
                Array.Resize(ref stringList, stringList.Length + 1);
                Array.Resize(ref attackInfoList, attackInfoList.Length + 1);
            }

            if (line.Length == 0)
            {
                count++;
                continue;
            }
            //SetHierarchyAttackList(ref stringList, count, line);
            SetAttackInfo(ref attackInfoList, ref stringList, count, line);

        }
        reader.Close();
        file.Close();
    }

    static void SetHierarchyAttackList(ref string[] stringList, int count, string line)
    {
        int AttackNameLength = "AttackName".Length;
        int NameLength = AttackNameLength + 4;
        if (line.Length <= 0)
            return;

        if (line.Substring(0, AttackNameLength) != "AttackName")
            return;

        int nowCursor = NameLength;
        while(nowCursor < line.Length)
        {
            if (line[++nowCursor] == '\"')
                break;
        }
        stringList[count] = line.Substring(NameLength, nowCursor - NameLength);
    }

    static void SetAttackInfo(ref AttackComponent.AttackInfo[] attackInfoList, ref string[] stringList, int count, string line)
    {
        if (line.Length <= 0)
            return;

        // form - TITLENAME : "VALUENAME"
        // Find Title //////////////////////////////////////////////
        int nowCursor = 0;
        while (nowCursor < line.Length)
        {
            if (line[++nowCursor] == ':')
                break;
        }
        string title = line.Substring(0, nowCursor -1);
        //////////////////////////////////////////////////////////

        // Find Value //////////////////////////////////////////////
        int value_startCursor = nowCursor += 3;
        while (nowCursor < line.Length)
        {
            if (line[++nowCursor] == '\"')
                break;
        }
        string value = line.Substring(value_startCursor, nowCursor - value_startCursor);
        //////////////////////////////////////////////////////////
        
        // AttackInfo Value Setting
        if(title == "AttackName")
        {
            stringList[count] = value;
            attackInfoList[count].attackName = value;
        }

        else if (title == "AttackType")
        {
            attackInfoList[count].attackType = value;
        }

        else if (title == "AttackDamage")
        {
            attackInfoList[count].damage = value;
        }
        else if (title == "StatusType")
        {
            attackInfoList[count].statusType = value;
        }

        else if (title == "StatusDuration")
        {
            attackInfoList[count].statusDuration = value;
        }

    }
}
