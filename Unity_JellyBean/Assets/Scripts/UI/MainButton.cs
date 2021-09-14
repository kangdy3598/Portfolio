using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.EventSystems;

public class MainButton : MonoBehaviour {

    public GameObject AchievementWindow;
    public GameObject PopUpWindow;

    public CsvFileWriter bfw;
    private List<string> columns;

    public List<Dictionary<string, object>> bfr;

    private static MainButton instance = null;
    public static MainButton Instance
    {
        get
        {
            if (instance == null)
                instance = GameObject.FindObjectOfType<MainButton>() as MainButton;

            return instance;
        }
    }
    // Use this for initialization
    void Start () {

        //Screen.sleepTimeout = SleepTimeout.NeverSleep;
    }
	
	// Update is called once per frame
	void Update () {
        
    }

    public void ClickButton()
    {
        SoundManager.Instance.PlayerSound(SoundManager.Instance.ButtonClick);

        switch (transform.name)
        {
            case "Setting":
                break;

            case "Achievement":
                AchievementWindow.SetActive(true);
                break;

            case "Start":
                if (!AchievementWindow.activeSelf)
                {
                 //   if ((int)CharacterSell.Instance.sfr[SelectCharacter.Num]["Sell"] != 0)
                    
                        //using (bfw = new CsvFileWriter("Assets/Resources/Main/CSV/Behavior.csv"))
                        //{
                        //    columns = new List<string>() { "Behavior", "NowTime", "SelectChar" };

                        //    bfw.WriteRow(columns);
                        //    columns.Clear();

                        //    columns.Add("1"); columns.Add(System.DateTime.Now.ToString()); columns.Add(SelectCharacter.Num.ToString());
                        //    bfw.WriteRow(columns);
                        //    columns.Clear();
                            
                        //    bfw.Dispose();
                        //}
                        //Behavior.Instance.bfr = CSVReader.Read("Main/CSV/Behavior");
                        StartCoroutine(LoadingScene());
                    
                }
                break;

            case "Left":
                if (!AchievementWindow.activeSelf)
                    if (SelectCharacter.Num != 0) SelectCharacter.Num--;
                break;

            case "Right":
                if (!AchievementWindow.activeSelf)
                    if (SelectCharacter.Num < SelectCharacter.Count - 1) SelectCharacter.Num++;
                break;
        }
    }

    IEnumerator LoadingScene()
    {
        AsyncOperation ao = SceneManager.LoadSceneAsync(3);
        while(!ao.isDone)
        {
            yield return null;

        }
    }
}
