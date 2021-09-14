using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class OverRestart : MonoBehaviour {
    
//    private List<string> columns;
//    public CsvFileWriter fw;

    public static int[] Count = new int[8];
    public static int[] Clear = new int[8];

    private string[] AchievementName =  {"하늘 위로!", "파괴 신 강림!", "부자다 부자!", "살려주세요!" ,
                                        "말캉 말캉!" , "나도 명사수!" , "새로운 시작!" , "다시 보자!" };

    public GameObject AchievementWindow;

    void OnEnable()
    {
        for (int i = 0; i < Count.Length; i++)
        {
        //    Count[i] = int.Parse(Achievement.Instance.fr[i]["Count"].ToString());
        //    if (int.Parse(Achievement.Instance.fr[i]["Clear"].ToString()) == 0)
            {
                if ((int)Score.Height + Count[0] >= 100)
                {
                    Count[0] += (int)Score.Height;
                    CompleteAchievement(0);
                    StartCoroutine(CloseUI(2));

                }
                
                if(Score.DestroyOb + Count[1] >= 5)
                {
                    Count[1] += Score.DestroyOb;
                    CompleteAchievement(1);
                    StartCoroutine(CloseUI(2));
                }

                if (Score.GetCoin + Count[2] >= 100)
                {
                    Count[2] += Score.GetCoin;
                    CompleteAchievement(2);
                    StartCoroutine(CloseUI(2));
                }

                if (Score.GetHP + Count[3] >= 1)
                {
                    Count[3] += Score.GetHP;
                    CompleteAchievement(3);
                    StartCoroutine(CloseUI(2));
                }

                if (Score.TransSlime + Count[4] >= 1)
                {
                    Count[4] += Score.TransSlime;
                    CompleteAchievement(4);
                    StartCoroutine(CloseUI(2));
                }

                if (Score.DestroyFalling + Count[5] >= 1)
                {
                    Count[5] += Score.DestroyFalling;
                    CompleteAchievement(5);
                    StartCoroutine(CloseUI(2));
                }

                if (Score.StartGame + Count[6] >= 1)
                {
                    Count[6] += Score.StartGame;
                    CompleteAchievement(6);
                    StartCoroutine(CloseUI(2));
                }

                if (Score.EndGame + Count[7] >= 1)
                {
                    Count[7] += Score.EndGame;
                    CompleteAchievement(7);
                    StartCoroutine(CloseUI(2));
                }
            }
        }
        //using (fw = new CsvFileWriter("Assets/Resources/Main/CSV/Achievement.csv"))
        //{
        //    columns = new List<string>() { "Name", "Count", "Clear"};
        //    fw.WriteRow(columns);
        //    columns.Clear();

        //    columns.Add("하늘 위로!"); columns.Add(((int)Score.Height + Count[0]).ToString()); columns.Add(Clear[0].ToString());
        //    fw.WriteRow(columns);
        //    columns.Clear();

        //    columns.Add("파괴 신 강림!"); columns.Add((Score.DestroyOb + Count[1]).ToString()); columns.Add(Clear[1].ToString());
        //    fw.WriteRow(columns);
        //    columns.Clear();

        //    columns.Add("부자다 부자!"); columns.Add((Score.GetCoin + Count[2]).ToString()); columns.Add(Clear[2].ToString());
        //    fw.WriteRow(columns);
        //    columns.Clear();

        //    columns.Add("살려주세요!"); columns.Add((Score.GetHP + Count[3]).ToString()); columns.Add(Clear[3].ToString());
        //    fw.WriteRow(columns);
        //    columns.Clear();

        //    columns.Add("말캉 말캉!"); columns.Add((Score.TransSlime + Count[4]).ToString()); columns.Add(Clear[4].ToString());
        //    fw.WriteRow(columns);
        //    columns.Clear();

        //    columns.Add("나도 명사수!"); columns.Add((Score.DestroyFalling + Count[5]).ToString()); columns.Add(Clear[5].ToString());
        //    fw.WriteRow(columns);
        //    columns.Clear();

        //    columns.Add("새로운 시작!"); columns.Add((Score.StartGame + Count[6]).ToString()); columns.Add(Clear[6].ToString());
        //    fw.WriteRow(columns);
        //    columns.Clear();

        //    columns.Add("다시 보자!"); columns.Add((Score.EndGame + Count[7]).ToString()); columns.Add(Clear[7].ToString());
        //    fw.WriteRow(columns);
        //    columns.Clear();
            
        //    fw.Dispose();
            
        //}
        //Achievement.Instance.fr = CSVReader.Read("Main/CSV/Achievement");
        Score.EndGame++;

    }
    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            SceneManager.LoadScene(2);
        }

    }

    void CompleteAchievement(int num)
    {
        Achievement.Instance.ShowAchievementComplete(AchievementName[num]);
        Clear[num] = 1;
    }
    IEnumerator CloseUI(float T)
    {
        AchievementWindow.SetActive(true);
        yield return new WaitForSeconds(T);
        AchievementWindow.SetActive(false);
    }
}
