using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cra_allballoon : MonoBehaviour {
    float time;
	// Use this for initialization
	void Start () {
        time = 0;
	}
	
	// Update is called once per frame
	void Update () {
        time += Time.deltaTime;
        if(time >= 0.5)
        {
            Destroy(gameObject);
        }
	}

    void OnCollisionEnter2D(Collision2D col)
    {
        if (col.gameObject.CompareTag("Enemy"))
        {
            col.gameObject.GetComponent<cra_Dao>().attacked = true;
        }
        if (col.gameObject.CompareTag("Player"))
        {
            col.gameObject.GetComponent<cra_Player>().attacked = true;
        }
    }
}
