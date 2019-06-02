using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cra_block1 : MonoBehaviour {
    public bool attacked = false;
    Animator animator;
    float time = 0;
    public bool die = false;
    // Use this for initialization
    void Start () {
        animator = GetComponent<Animator>();
	}
	
	// Update is called once per frame
	void Update () {
        time += Time.deltaTime;
		if(attacked)
        {
            animator.SetBool("attacked", true);
            die = true;
            time = 0;
            attacked = false;
        }
        if(die)
        {
            if (time > 1)
                Destroy(gameObject);
        }
	}
}
