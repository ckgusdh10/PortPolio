using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class gal_enemymove : MonoBehaviour {
    public GameObject Player;
    public GameObject Bullet;
    Vector3 dir;
    float speed;
    public int hp;
    float time;
    Transform look;
	// Use this for initialization
	void Start () {
        speed = 1;
        hp = 5;
        time = 1;
        this.transform.LookAt(Player.transform);
        this.transform.Rotate(new Vector3(0, 90, 0));
        
        look = Player.transform;
        look.Rotate(-90, -90, 0);
        //transform.eulerAngles = new Vector3(0, 0, -getAngle(transform.position.x, transform.position.y, Player.transform.position.x, Player.transform.position.y) + 180.0f);
       // dir = Vector3.Normalize(Player.transform.position - this.transform.position);
        dir = new Vector3(Random.Range(-4, 4), -5, -1);
    }
	
	// Update is called once per frame
	void Update () {
        time += Time.deltaTime;
       // transform.eulerAngles = new Vector3(0, 0, -getAngle(transform.position.x, transform.position.y, Player.transform.position.x, Player.transform.position.y) + 180.0f);

        

        this.transform.Translate(dir * speed * Time.deltaTime, Space.World);
       // this.transform.LookAt(Player.transform.position);
       // this.transform.Rotate(0,-90,0);
        if(this.hp <= 0)
        {
            Destroy(gameObject);
        }

        if(time > 1)
        {
            GameObject g = Instantiate(Bullet, this.transform.position, this.transform.rotation);
            g.transform.Rotate(new Vector3(0, 0, 90));
            g.gameObject.GetComponent<enemybulletmove>().player = Player;
            time = 0;
        }
        if (this.transform.position.y < -5.0f)
            Destroy(gameObject);
	}

    void OnCollisionEnter2D(Collision2D col)
    {
        if (col.gameObject.tag == "Player")
        {

            col.transform.GetComponent<gal_playermove>().hpMinus();

            Destroy(gameObject);
        }
    }

    private float getAngle(float x1, float y1, float x2, float y2)

    {

        float dx = x2 - x1;

        float dy = y2 - y1;



        float rad = Mathf.Atan2(dx, dy);

        float degree = rad * Mathf.Rad2Deg;



        return degree;

    }



}
