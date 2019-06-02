using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class gal_Cameracs : MonoBehaviour
{
    public GameObject Enemy;
    public GameObject Boss;
    public gal_playermove player;
    float time;
    float stagetime;
    float waittime;
    public int stage;
    bool isboss = false;
    // Use this for initialization
    void Start()
    {
        time = 0;
        stagetime = 0;
        waittime = 0;
        stage = 1;
    }

    // Update is called once per frame
    void Update()
    {
        if (stage == 1)
        {
            time += Time.deltaTime;
            stagetime += Time.deltaTime;
            if (stagetime > 15)
            {
                waittime += Time.deltaTime;
                if (waittime > 3)
                {
                    this.transform.position = new Vector3(20, 0, -10);
                    player.transform.position = new Vector3(20, -4, -1);
                    player.minX += 20;
                    player.maxX += 20;
                    stagetime = 0;
                    stage = 2;
                    time = 0;
                }

            }
            else if(time > 1)
            {
                Vector3 newpos = new Vector3(Random.Range(-2.5f, 2.5f), 6.0f, -1);
                Instantiate(Enemy, newpos, Enemy.transform.rotation);
                time = 0;
            }
        }



        if (stage == 2)
        {
            time += Time.deltaTime;
            if (time > 3 && isboss == false)
            {
                Boss.SetActive(true);
                Boss.transform.rotation = Enemy.transform.rotation;
                Vector3 newpos = new Vector3(20, 7.0f, -1);
                //Instantiate(Boss, newpos, Enemy.transform.rotation);
                Boss.transform.position = newpos;
                time = 0;
                isboss = true;
            }
        }
    }
}
