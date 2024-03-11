using UnityEngine;
using System.Collections.Generic;

//Pop :
//GameObject objectName = ObjectPool.Instance.PopFromPool("Pool Item Name");
//if (objectName != null)
//{
//    objectName.transform.position = pos;
//    objectName.SetActive(true);
//}

// Push : 
//ObjectPool.Instance.PushToPool(gameObject.name, gameObject);
public class ObjectPool : Singleton<ObjectPool>
{
    public List<PooledObject> objectPool = new List<PooledObject>();

    void Awake()
    {
        for (int i = 0; i < objectPool.Count; ++i)
        {
            objectPool[i].Initialize(transform);
        }
 
    }

    public bool PushToPool(string itemName, GameObject item, Transform parent = null)
    {
        PooledObject pool = GetPoolItem(itemName);
        if (pool == null) return false;

        
        pool.PushToPool(item, parent == null ? transform : parent);
        
        return true;
    }

    public GameObject PopFromPool(string itemName, Transform parent = null)
    {
        PooledObject pool = GetPoolItem(itemName);
        if (pool == null) return null;

        return pool.PopFromPool(parent);
    }

    public PooledObject GetPoolItem(string itemName)
    {
        for (int i = 0; i < objectPool.Count; i++)
        {
            if (objectPool[i].poolItemName.Equals(itemName))
                return objectPool[i]; 
        }
        
        return null;
    }
}
