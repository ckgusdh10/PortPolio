using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cra_balloon : MonoBehaviour {
    public GameObject ac1;
    public GameObject ac2;
    public GameObject ab;
    float time;
    public bool attacked = false;
    // Use this for initialization
    void Start () {
        time = 0;
        this.transform.position = new Vector3(this.transform.position.x, this.transform.position.y, this.transform.position.z + 0.5f);
	}
	
	// Update is called once per frame
	void Update () {
        time += Time.deltaTime;	
        if(time >= 2)
        {
            Instantiate(ac1, this.transform.position, Quaternion.identity);
            Instantiate(ac2, this.transform.position, Quaternion.identity);
            Destroy(gameObject);
            time = 0;
        }
        if(attacked == true)
        {
            Instantiate(ac1, this.transform.position, Quaternion.identity);
            Instantiate(ac2, this.transform.position, Quaternion.identity);
            Destroy(gameObject);
        }
	}
}
