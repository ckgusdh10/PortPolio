using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cra_boom1 : MonoBehaviour {
    float time;
    // Use this for initialization
    void Start()
    {
        time = 0;
    }

    // Update is called once per frame
    void Update()
    {
        time += Time.deltaTime;
        if (time >= 0.5)
        {
            Destroy(gameObject);
        }
    }

    //void OnCollisionEnter2D(Collision2D col)
    //{
    //    if (col.gameObject.CompareTag("Enemy"))
    //    {
    //        if(!col.gameObject.GetComponent<cra_Dao>().die)
    //            col.gameObject.GetComponent<cra_Dao>().attacked = true;
    //    }
    //    if (col.gameObject.CompareTag("Player"))
    //    {
    //        if(!col.gameObject.GetComponent<cra_Player>().die)
    //            col.gameObject.GetComponent<cra_Player>().attacked = true;
    //    }
    //}
    void OnTriggerEnter2D(Collider2D col)
    {
        if (col.gameObject.CompareTag("Enemy"))
        {
            if (!col.gameObject.GetComponent<cra_Dao>().die)
                col.gameObject.GetComponent<cra_Dao>().attacked = true;
        }
        if (col.gameObject.CompareTag("Player"))
        {
            if (!col.gameObject.GetComponent<cra_Player>().die)
                col.gameObject.GetComponent<cra_Player>().attacked = true;
        }
        if (col.gameObject.CompareTag("block"))
        {
            if(!col.gameObject.GetComponent<cra_block1>().die)
                col.gameObject.GetComponent<cra_block1>().attacked = true;
        }
        if(col.gameObject.CompareTag("balloon"))
        {
            col.gameObject.GetComponent<cra_balloon>().attacked = true;
        }
    }
}
