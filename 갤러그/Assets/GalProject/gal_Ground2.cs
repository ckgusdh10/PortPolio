﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class gal_Ground2 : MonoBehaviour
{
    public GameObject ground2;
    float speed;
    float time;
    // Use this for initialization
    void Start()
    {
        speed = 5;
        time = 0;
    }

    // Update is called once per frame
    void Update()
    {
        time = Time.deltaTime;
        this.transform.Translate(new Vector3(0, -1) * Time.deltaTime * speed, Space.World);
        ground2.transform.Translate(new Vector3(0, -1) * Time.deltaTime * speed, Space.World);
        if (this.transform.position.y <= -10)
        {
            this.transform.position = new Vector3(20, 10, 0);
        }
        if (ground2.transform.position.y <= -10)
        {
            ground2.transform.position = new Vector3(20, 10, 0);
        }
    }
}
