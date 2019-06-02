using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class gal_bossbullet : MonoBehaviour {
    float speed;
    float time;
    public Vector3 dir;
    Vector3 firpos;
	// Use this for initialization
	void Start () {
        speed = 4;
        time = 0;
        firpos = this.transform.position;
	}
	
	// Update is called once per frame
	void Update () {

        this.transform.Translate(Vector3.Normalize(dir)* speed * Time.deltaTime);
        if(Vector3.Distance(firpos, this.transform.position) > 11)
        {
            Destroy(gameObject);
        }
	}

    void OnCollisionEnter2D(Collision2D col)
    {

        if (col.gameObject.tag == "Player")
        {

            col.transform.GetComponent<gal_playermove>().hpMinus();
            Destroy(gameObject);
        }
    }
}
