using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class gal_playermove : MonoBehaviour {
    float Speed;
    public GameObject Bullet;
    public float hp = 3;
    public int score;
    public gal_hpicon hpIcon;
    public gal_Cameracs Camera;
    public float maxX;
    public float minX;
    // Use this for initialization
    void Start () {
        Speed = 7;
        score = 0;
        maxX = 2.5f;
        minX = -2.5f;

    }

    // Update is called once per frame
    void Update()
    {
        float moveX = Input.GetAxis("Horizontal");
        float moveY = Input.GetAxis("Vertical");
        if (this.transform.position.x > maxX)
        {
            if (moveX < 0)
                this.transform.Translate(transform.right * moveX * Speed * Time.deltaTime, Space.World);
        }
        else if (this.transform.position.x < minX)
        {
            if (moveX > 0)
                this.transform.Translate(transform.right * moveX * Speed * Time.deltaTime, Space.World);
        }
        else
        {
            this.transform.Translate(transform.right * moveX * Speed * Time.deltaTime, Space.World);
        }
        if (this.transform.position.y > 4.2)
        {
            if (moveY < 0)
                this.transform.Translate(new Vector2(0,1) * moveY * Speed * Time.deltaTime, Space.World);

        }
        else if (this.transform.position.y < -4.0)
        {
            if (moveY > 0)
                this.transform.Translate(new Vector2(0, 1) * moveY * Speed * Time.deltaTime, Space.World);
        }
        else
        {
            this.transform.Translate(new Vector2(0, 1) * moveY * Speed * Time.deltaTime, Space.World);
        }

        if(Input.GetKeyDown(KeyCode.Space))
        {
            GameObject g = Instantiate(Bullet, this.transform.position, this.transform.rotation);
            g.GetComponent<gal_bulletmove>().player = this;
            //g.transform.Rotate(new Vector3(90, 0, 0));
        }

       
    }

    public void hpMinus()
    {
        hp--;
        hpIcon.hpMinus();
    }
}
