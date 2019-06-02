using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class enemybulletmove : MonoBehaviour {
    float speed;
    public GameObject player;
    Vector3 dir;
    // Use this for initialization
    void Start () {
        speed = 7;
        dir = Vector3.Normalize(player.transform.position - this.transform.position);
    }
	
	// Update is called once per frame
	void Update () {
        this.transform.Translate(new Vector3(0, 1, 0) * speed * Time.deltaTime);

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
    //void OnTriggerEnter2D(Collider2D col)
    //{

    //    if (col.tag == "Player")
    //    {
    //        col.transform.GetComponent<gal_playermove>().hp -= 5;
    //        Destroy(gameObject);
    //    }
    //}
}
