#pragma once
#include "stdafx.h"
#include "Bullet.h"
#include "Box.h"

class ObjMgr
{

public:
	list<Bullet*> BulletList;
	vector<Box*> BoxList;
	default_random_engine dre;
	int bulletNum = 0;
	ObjMgr();
	~ObjMgr();

	void animate();

};
