using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class gal_hpicon : MonoBehaviour {
    public Image[] hearts;

    public int hp = 3;
    // Use this for initialization
    void Start () {
        hearts = GetComponentsInChildren<Image>();
    }
	
	// Update is called once per frame
	void Update () {
        
	}

    public void hpMinus()
    {
        if(hp >0)
        {
            hp--;
            hearts[2 - hp].enabled = false;
        }
    }
}
