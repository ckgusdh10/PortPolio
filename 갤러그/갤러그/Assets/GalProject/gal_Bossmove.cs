using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class gal_Bossmove : MonoBehaviour
{
    public int hp;
    // Use this for initialization
    Material[] mats;
    Renderer rend;
    public GameObject bullet;
    public GameObject winText;
    public Text winScore;
    public GameObject Player;
    public bool attacked = false;
    public float atime = 0;
    float time;
    float attacktime = 0;
    float i;
    bool battack4 = false;
    void Start()
    {
        this.transform.Rotate(new Vector3(180, 0, 0));
        rend = GetComponentInChildren<Renderer>();
        mats = rend.materials;
        time = 0;
        //rend.material = mats[1];
        hp = 300;
        //winText = FindObjectOfType<Text>("WinText");
    }

    // Update is called once per frame
    void Update()
    {
        time += Time.deltaTime;
        attacktime += Time.deltaTime;
        if (this.transform.position.y > 4)
        {
            this.transform.Translate(new Vector3(0, -1, 0) * Time.deltaTime * 0.5f, Space.World);
        }
        if (atime > 0.1f)
        {
            rend.material = mats[0];
            atime = 0;
            attacked = false;
        }

        if (attacked == true)
        {
            atime += Time.deltaTime;
            rend.material = mats[1];

        }
        if(battack4 == false)
        {
            if (time > 2)
            {
                int r = Random.Range(1, 5);
                //r = 4;
                if (r == 1)
                    attack1();
                else if (r == 2)
                    attack2();
                else if (r == 3)
                    attack3();
                else if (r == 4)
                {
                    battack4 = true;
              
                }

                // attack3();
                time = 0;
            }
        }     
        else if(battack4 == true)
        {
            if(time >= 0.05)
            {
                attack4(i);
                i++;
                time = 0;
                if (i >= 60)
                {
                    battack4 = false;
                    i = 0;
                }

            }
        }
        if(hp <= 0)
        {
            winText.SetActive(true);
            
            winScore.text = "Score : " + (Player.GetComponent<gal_playermove>().score).ToString();
            winScore.gameObject.SetActive(true);
            Destroy(gameObject);
        }
    }

    void makeBullet(Vector3 dir)
    {
        GameObject g = Instantiate(bullet, this.transform.position, Quaternion.identity);
        g.gameObject.GetComponent<gal_bossbullet>().dir = dir;
    }

    void attack1()
    {

        makeBullet(transform.up);
        makeBullet(-transform.up);
        makeBullet(transform.right);
        makeBullet(-transform.right);

    }

    void attack2()
    {
        for (int i = 0; i < 11; i++)
        {
            makeBullet(new Vector3(Mathf.Sin(i * 12.0f), Mathf.Cos(i * 12.0f)));

        }
    }

    void attack3()
    {
        // 3 4 5 6 7 8
        // 36 48 60 72 84 96
        // 42 54 66 78 90 102
        for (int i = 3; i < 9; ++i)
        {
            makeBullet(new Vector3(Mathf.Sin(i * 12.0f), Mathf.Cos(i * 12.0f)));
        }
        for (int i = 10; i < 35; i += 4)
        {
            makeBullet(new Vector3(Mathf.Sin(i * 3.0f), Mathf.Cos(i * 3.0f)));
        }
    }

    void attack4(float i)
    {
        makeBullet(new Vector3(Mathf.Sin(i * 6.0f), Mathf.Cos(i * 6.0f)));
    }


}
