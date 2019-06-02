using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class cra_Camera : MonoBehaviour {
    public int enemynum;
    int stage;
    public GameObject map1;
    public GameObject map2;
    public Text winScore;
    float time;
    public GameObject Player;
    public GameObject enemy;
    public bool Playing = true;
    // Use this for initialization
    void Start () {
        enemynum = 3;
        stage = 1;
        time = 0;
        winScore.text = "Clear!!";
    }
	
	// Update is called once per frame
	void Update () {     
        if(stage == 1)
        {
            if (enemynum == 0)
            {
                time += Time.deltaTime;
                winScore.gameObject.SetActive(true);
                Playing = false;

            }
            if (time >= 5)
            {
                Player.GetComponent<cra_Player>().transform.position = new Vector3(-2.25f, -2.23f, -1);
                winScore.gameObject.SetActive(false);
                map1.SetActive(false);

                map2.SetActive(true);
                time = 0;
                stage = 2;
                winScore.gameObject.SetActive(false);
                //Instantiate(enemy, new Vector3(-2.28f, 2.233f, -1), Quaternion.identity);
                //Instantiate(enemy, new Vector3(2.246f, 2.233f, -1), Quaternion.identity);
                //Instantiate(enemy, new Vector3(2.246f, -2.22f, -1), Quaternion.identity);
                enemy.SetActive(true);
                enemynum = 3;
                Playing = true;
            }
        }  
		
        if(stage == 2)
        {
            if(enemynum == 0)
            {
                winScore.text = "You Win!!";
                winScore.gameObject.SetActive(true);
            }
           
        }

    }
}
