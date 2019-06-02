using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cra_Player : MonoBehaviour {
    Animator animator;
    Vector3 CurPos;
    float speed;
    float time;
    float respon;
    public GameObject balloon;
    public bool attacked = false;
    public bool die = false;
    public GameObject Camerasc;
    // Use this for initialization
    void Start () {
        animator = GetComponent<Animator>();
        CurPos = new Vector3(-2.25f, -2.23f, -1);
        speed = 2;
	}
	
	// Update is called once per frame
	void Update () {
        time += Time.deltaTime;
        
        if (attacked)
        {
            time = 0;
            die = true;
            attacked = false;
            animator.SetInteger("State", 4);
        }
        if (!die && Camerasc.GetComponent<cra_Camera>().Playing)
        {
            if (Input.GetKey(KeyCode.RightArrow))
            {
                animator.SetInteger("State", 0);
                if (this.transform.position.x < 2.4f)
                    this.transform.Translate(this.transform.right * Time.deltaTime * speed, Space.World);
            }
            else if (Input.GetKey(KeyCode.LeftArrow))
            {
                animator.SetInteger("State", 1);
                if (this.transform.position.x > -2.4f)
                    this.transform.Translate(-this.transform.right * Time.deltaTime * speed, Space.World);
            }
            else if (Input.GetKey(KeyCode.UpArrow))
            {
                animator.SetInteger("State", 2);
                if (this.transform.position.y < 2.3f)
                    this.transform.Translate(this.transform.up * Time.deltaTime * speed, Space.World);
            }
            else if (Input.GetKey(KeyCode.DownArrow))
            {
                animator.SetInteger("State", 3);
                if (this.transform.position.y > -2.3f)
                    this.transform.Translate(-this.transform.up * Time.deltaTime * speed, Space.World);
            }

            if (Input.GetKeyDown(KeyCode.Space))
            {
                Instantiate(balloon, this.transform.position, Quaternion.identity);
            }
        }
		else
        {
            respon += Time.deltaTime;
            if (time > 0.3f)
            {
                
                time = 0;
                animator.SetInteger("State", 3);
                
            }              
            if(respon > 0.5f)
            {
                die = false;
                respon = 0;
                this.transform.position = new Vector3(-2.25f, -2.23f, -1);
            }
        }
        
        
    }

    void OnCollisionEnter2D(Collision2D col)
    {
        if (col.gameObject.CompareTag("Enemy"))
        {
            if (!die)
                attacked = true;
        }
        
    }
}
