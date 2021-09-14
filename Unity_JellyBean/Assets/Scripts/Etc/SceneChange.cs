using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class SceneChange : MonoBehaviour {

    public Animator TitleImgAni;
    public Image Img;
    private Color alphaFade;

    private AsyncOperation ao;
    private int currentSceneNumber;

    ///////////Title////////////////////////////////
    public Image GaugeImage;
    public GameObject touchTxt, Gauge, loadingTxt;
    /// ////////////////////////////////////////////
    public GameObject CutScene;
    public Sprite[] CutSceneImage;
    private int currentCutSceneNumber;
    private float _time;

    // Use this for initialization
    void Start () {
        
        Img = GetComponent<Image>();
        alphaFade = Img.color;
        _time = 0;

        currentCutSceneNumber = -1;
        currentSceneNumber = SceneManager.GetActiveScene().buildIndex;
        StartCoroutine(LoadingScene(currentSceneNumber + 1));

        Screen.sleepTimeout = SleepTimeout.NeverSleep;
        
    }

    // Update is called once per frame
    void Update()
    {
        
        switch (currentSceneNumber)
        {
            case 0:
                if (Input.GetMouseButtonDown(0) && GaugeImage.fillAmount == 1.0f) TitleImgAni.SetBool("Click", true);

                if (TitleImgAni.GetCurrentAnimatorStateInfo(0).IsName("TitleClick") &&
                   TitleImgAni.GetCurrentAnimatorStateInfo(0).normalizedTime > 0.95f &&
                   TitleImgAni.GetBool("Click"))
                {
                    TitleImgAni.SetBool("Click", false);
                    StartCoroutine(FadeOut());
                }
                if (Img.color.a == 1) ao.allowSceneActivation = true;
                break;
            case 1:
                if (Img.color.a == 1)
                {
                    if (currentCutSceneNumber < 3) currentCutSceneNumber++;
                    else ao.allowSceneActivation = true;

                    CutScene.GetComponent<SpriteRenderer>().sprite = CutSceneImage[currentCutSceneNumber];
                    StartCoroutine(FadeIn());
                }
                else if(Img.color.a == 0) _time += Time.deltaTime;

                if(_time >= 2.5f)
                {
                    _time = 0;
                    StartCoroutine(FadeOut());
                    
                }
                //if(Input.GetMouseButtonDown(0))
                //{
                //    if (Img.color.a <= 0 && currentCutSceneNumber <= 2)
                //    {
                //        alphaFade.a = 1;
                //        Img.color = alphaFade;
                //        CutScene.GetComponent<SpriteRenderer>().sprite = CutSceneImage[++currentCutSceneNumber];
                //    }
                //    else ao.allowSceneActivation = true;
                //}
                //if (Img.color.a == 1) StartCoroutine(FadeIn());
                break;
        }


    }

    IEnumerator LoadingScene(int SceneNumber)
    {
        ao = SceneManager.LoadSceneAsync(SceneNumber);
        ao.allowSceneActivation = false;
        float timer = 0.0f;

        while (!ao.isDone)
        {
            yield return null;
            timer += Time.deltaTime;
            yield return new WaitForSeconds(0.1f);

            if (currentSceneNumber == 0)
            {
                if (ao.progress >= 0.9f)
                {
                    GaugeImage.fillAmount = Mathf.Lerp(GaugeImage.fillAmount, 1f, timer);
                    if (GaugeImage.fillAmount == 1.0f)
                    {
                        touchTxt.SetActive(true);
                        Gauge.SetActive(false);
                        loadingTxt.SetActive(false);
                    }
                }
                else
                {
                    GaugeImage.fillAmount = Mathf.Lerp(GaugeImage.fillAmount, ao.progress, timer);
                    if (GaugeImage.fillAmount >= ao.progress)
                    {
                        timer = 0f;
                    }
                }
            }

        }
    }
    // 점점 밝아짐
    IEnumerator FadeIn()
    {
        while (Img.color.a > 0)
        {
            alphaFade.a -= Time.deltaTime;
            Img.color = alphaFade;
            yield return null;
        }
        alphaFade.a = 0;
        Img.color = alphaFade;
    }
    // 점점 어두워짐
    IEnumerator FadeOut()
    {
        while(Img.color.a < 1)
        {
            alphaFade.a += Time.deltaTime;
            Img.color = alphaFade;
            yield return null;
        }
        alphaFade.a = 1;
        Img.color = alphaFade;
    }
}
