using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIsc : MonoBehaviour {
    public Text StageText;
    public Text ScoreText;
    private gal_playermove player;
    private gal_Cameracs Camera;
   
    // Use this for initialization
    void Start () {
        player = GameObject.Find("Players").GetComponent<gal_playermove>();
        Camera = GameObject.Find("Main Camera").GetComponent<gal_Cameracs>();
       
	}
	
	// Update is called once per frame
	void Update () {
        ScoreText.text = "Score : " + (player.score).ToString();
        StageText.text = "1 - " + (Camera.stage).ToString();

    }
}
