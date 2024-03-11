using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TestHitDamage : MonoBehaviour
{
    private float fadeDuration = 1.0f;
    private Vector3 startPosition;
    private Vector3 movePosition;
    //private bool fadeInOnStart = true;
    //private bool fadeOutOnExit = true;

    private Text textComp;
    private Color originColor;
    //private float timer = 0.0f;

    public string damageAmount { get; set; }
    public Transform canvas;
    public HitComponent hitComp;
    // Start is called before the first frame update
    void Awake()
    {
        textComp = GetComponent<Text>();
        originColor = textComp.color;

        if (canvas == null) canvas = GameObject.Find("Canvas").transform;
    }

    private void OnEnable()
    {
        hitComp.hitEvent += SetDamageText;
    }

    private void SetDamageText(string damageAmount)
    {
        if (damageAmount == "0")
            return;

        transform.SetParent(canvas);
        Vector3 playerPos = PlayerInfo.Instance.transform.position;
        playerPos.y += 1;

        startPosition = transform.position = Camera.main.WorldToScreenPoint(playerPos);
        movePosition = transform.position;
        movePosition.y += 30;

        //timer = 0.0f;
        textComp.color = originColor;
        textComp.text = damageAmount;

        StartCoroutine(FadeInAndMoveCoroutine());
    }
    IEnumerator FadeInAndMoveCoroutine()
    {
        float timer = 0f;
        while (timer < fadeDuration)
        {
            float alpha = Mathf.Lerp(1f, 0f, timer / fadeDuration);
            textComp.color = new Color(originColor.r, originColor.g, originColor.b, alpha);

            transform.position = Vector3.Lerp(startPosition, movePosition, timer / fadeDuration); 
            timer += Time.deltaTime;
            yield return null;

        }

        hitComp.hitEvent -= SetDamageText;
        ObjectPool.Instance.PushToPool(gameObject.name, gameObject);
        
    }

}
