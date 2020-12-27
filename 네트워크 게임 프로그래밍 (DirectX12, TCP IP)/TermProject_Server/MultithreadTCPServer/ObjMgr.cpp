#include "ObjMgr.h"



ObjMgr::ObjMgr()
{
	uniform_real_distribution<> randomXY(-80.0f, 80.f);
	uniform_real_distribution<> randomZ(-100.0f, 100.0f);
	uniform_real_distribution<> randomDistance(20.0f, 50.0f);

	uniform_real_distribution<> randomAxis(-1.0f, 1.0f);
	uniform_real_distribution<> randomSpeed(5.0f, 10.0f);

	Box* pBox = nullptr;

	for (int i = 0; i < 10; ++i)
	{
		pBox = new Box;
		float x = randomXY(dre);
		float y = randomXY(dre);
		float z = randomXY(dre);
		pBox->setPosition(XMFLOAT3(x, y, z));
		//각 정육면체 객체의 위치를 설정한다.

		pBox->setMovingDirection(XMFLOAT3(randomAxis(dre), randomAxis(dre), randomAxis(dre)));
		pBox->movingDistance = randomDistance(dre);
		//pBox->SetOOBB(XMFLOAT3(x, y, z), XMFLOAT3(6.0f, 6.0f, 6.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		pBox->SetOOBB(XMFLOAT3(0, 0, 0), XMFLOAT3(6.0f, 6.0f, 6.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//	cout << pBox->getOOBB()->Center.x << pBox->getOOBB()->Center.y << pBox->getOOBB()->Center.z << endl;
		BoxList.push_back(pBox);
		//delete pBox;
	}
}


ObjMgr::~ObjMgr()
{
}

void ObjMgr::animate()
{

	for (auto p = BulletList.begin(); p != BulletList.end(); )
	{
		(*p)->move();
		if ((*p)->getDistance() > 500.0f)
		{
			p = BulletList.erase(p);
			bulletNum--;
		}
		else
			p++;
	}

	for (int i = 0; i < 10;++i)
	{
		BoxList[i]->move();
	}

}