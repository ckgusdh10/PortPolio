using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cra_Dao : MonoBehaviour {
    float time;
    float speed;
    bool moving;
    int r;
    Animator animator;
    public bool attacked = false;
    public bool die = false;
    public GameObject Camerasc;
    // Use this for initialization
    void Start () {
        time = 0;
        speed = 0.5f;
        moving = false;
        r = 0;
        animator = GetComponent<Animator>();
	}

    // Update is called once per frame
    void Update() {
        time += Time.deltaTime;
        if (attacked)
        {
            die = true;
            time = 0;
            animator.SetInteger("State", 4);
            attacked = false;
            // Destroy(gameObject);
        }
        if (!die)
        {
            if (!moving)
            {
                r = Random.Range(1, 5);
                moving = true;
            }
            else
            {
                if (r == 1)
                {
                    if (this.transform.position.x < 2.4f)
                    {
                        animator.SetInteger("State", 2);
                        this.transform.Translate(this.transform.right * speed * Time.deltaTime);
                    }
                    else
                        moving = false;
                }
                else if (r == 2)
                {
                    if (this.transform.position.x > -2.4f)
                    {
                        animator.SetInteger("State", 3);
                        this.transform.Translate(-this.transform.right * speed * Time.deltaTime);
                    }
                    else
                        moving = false;
                }
                else if (r == 3)
                {
                    if (this.transform.position.y > -2.3f)
                    {
                        animator.SetInteger("State", 0);
                        this.transform.Translate(-this.transform.up * speed * Time.deltaTime);
                    }
                    else
                        moving = false;
                }
                else if (r == 4)
                {
                    if (this.transform.position.y < 2.3f)
                    {
                        animator.SetInteger("State", 1);
                        this.transform.Translate(this.transform.up * speed * Time.deltaTime);
                    }
                    else
                        moving = false;
                }
            }
            if (time >= 2)
            {
                moving = false;
                time = 0;
            }
        }
        else
        {
            if (time > 0.7f)
            {
                Camerasc.GetComponent<cra_Camera>().enemynum -= 1;
                Destroy(gameObject);

            }
        }

       
    }
}
