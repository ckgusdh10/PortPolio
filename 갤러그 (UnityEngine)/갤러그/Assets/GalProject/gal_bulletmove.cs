using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class gal_bulletmove : MonoBehaviour {
    float speed;
    public gal_playermove player;
    // Use this for initialization
    void Start () {
        speed = 3;
	}
	
	// Update is called once per frame
	void Update () {
        this.transform.Translate(new Vector3(0, 1, 0) * speed * Time.deltaTime);

        if (this.transform.position.y > 5)
            Destroy(gameObject);
	}

    void OnCollisionEnter2D(Collision2D col)
    {

        if (col.gameObject.tag == "Enemy")
        {
            col.transform.GetComponent<gal_enemymove>().hp -= 5;
            player.score += 10;
            Destroy(gameObject);
        }
        if (col.gameObject.tag == "Boss")
        {
            col.transform.GetComponent<gal_Bossmove>().hp -= 5;
            col.transform.GetComponent<gal_Bossmove>().attacked = true;
            player.score += 10;
            Destroy(gameObject);
        }
    }
    //void OnTriggerEnter2D(Collider2D col)
    //{

    //    if (col.gameObject.tag == "Enemy")
    //    {
    //        print("ㅊㄷ");
    //        Destroy(gameObject);
    //    }
    //}
}
