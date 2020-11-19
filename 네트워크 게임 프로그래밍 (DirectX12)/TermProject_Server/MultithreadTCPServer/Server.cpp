#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include "ObjMgr.h"
#include "Player.h"
using namespace std;
#define SERVERPORT 9000
#define BUFSIZE 1024
#define FILENAMESIZE 50

ObjMgr mgr;
Player player[3];

HANDLE ableToCommu;
HANDLE ableToUpdate[3];

CRITICAL_SECTION cs;

float start = 0;
float TimeOver = 0;
int Time = 60;


float gameover = 0;
bool isGameover = false;

default_random_engine dre;
uniform_real_distribution<> randomAxis(-50.0f, 50.0f);

struct param {
	SOCKET s;
	int index;
}typedef param;

int clientNum = 0;

int num_of_Player = 3;

int particle = 0;
XMFLOAT3 Ppos;


void addBullet();
void collisionChek_Box_Bullet();
void collisionChek_Player_Bullet();
void collisionChek_Player_Box();
void restart();

void err_quit(char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCWSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void err_display(char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	printf("[%s] %s", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}


DWORD WINAPI Communicate(LPVOID arg)
{
	param* p = (param*)arg;

	SOCKET client_sock = p->s;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)& clientaddr, &addrlen);

	int id = p->index;
	bool passed = false;
	bool firstTime = false;      // �ʴ� ��Ŷ 60�� -> 0.017�ʿ� �ѹ�
	clock_t checkTime;
	//static UCHAR pKeyBuffer[10];
	player[id].hp = 10;
	player[id].setPosition(XMFLOAT3(0.0f, 0.0f, -60.0f));
	send(client_sock, (char*)&(player[id].xmfWorld), sizeof(player[id].xmfWorld), 0);

	while (1)
	{
		sendStruct S;
		keyValueStruct key;
		/*printf("\n");
		printf("Communicate [%d]\n", id);*/

		retval = recv(client_sock, (char*)&key, sizeof(key), 0);
		if(retval == 0 )
		{
			break;
		}
			      // Ű�Է� ���� ����
		
		player[id].dwKey = key.rot;                     // Ű�Է� ���� ����
		player[id].dwDirection = key.dir;               // Ű�Է� ���� ����

		ResetEvent(ableToCommu);                     // �̺�Ʈ ���ȣ�� ����
		SetEvent(ableToUpdate[id]);                     // �ڱ� id�� ableToUpdate ��ȣ���·� ���� 

		WaitForSingleObject(ableToCommu, INFINITE);         // ableToCommu ��ȣ�� ��ٸ�


		if (!firstTime)
		{
			firstTime = true;
			checkTime = clock();
		}
		else
		{
			while (checkTime + 17 > clock())         // 17 : 60������ , 33 : 30������
			{
			}
			checkTime = clock();
			//printf("�ð� : %d \n", checkTime);
		}                                    // ������ ���� 

		S.Position = player[id].xmfWorld;            // ���� ��Ŷ S�� �÷��̾� ��ġ ����
		S.Rotation = player[id].xmfRotate;            // ���� ��Ŷ S�� �÷��̾� ȸ������ ����
		S.Hp = player[id].hp;                     // ���� ��Ŷ S�� �÷��̾� HP ����
		S.active = player[id].isActive;               // ���� ��Ŷ S�� �÷��̾� ���翩�� ����

		S.ClientNum = clientNum;                  // ���� ��Ŷ S�� Ŭ���̾�Ʈ �� ����

		int n = 0;
		for (int i = 0; i < clientNum; i++)
		{
			if (i != id)
			{
				S.otherPosition[n] = player[i].xmfWorld;      // ���� ��Ŷ S�� �� �÷��̾� ��ġ ����
				S.otherRotation[n] = player[i].xmfRotate;      // ���� ��Ŷ S�� �� �÷��̾� ȸ������ ����
				S.otherHp[n] = player[i].hp;               // ���� ��Ŷ S�� �� �÷��̾� HP ����
				S.otherActive[n] = player[i].isActive;         // ���� ��Ŷ S�� �� �÷��̾� ���� ���� ����

				n++;
			}
		}

		S.Particle = particle;                           // ���� ��Ŷ S�� ��ƼŬ Ÿ�� ����
		S.particlePos = Ppos;                           // ���� ��Ŷ S�� ��ƼŬ ���� ��ġ ����

		send(client_sock, (char*)&S, sizeof(S), 0);            // ���� ��Ŷ S ����

		auto curTime = timeGetTime();
		auto eTime = curTime - start;
		start = curTime;
		TimeOver += eTime * 0.001;
		Time = 60 - (int)TimeOver;

		if (Time <= 0)
		{
			Sleep(3000);
			send(client_sock, (char*)&Time, sizeof(Time), 0);      // �ð� ���� ����
			Time = 60;
			TimeOver = 0;
			mgr.BulletList.clear();
			mgr.bulletNum = 0;
			for (int i = 0; i < 3; ++i)
			{
				player[i].setPosition(XMFLOAT3(randomAxis(dre), randomAxis(dre), randomAxis(dre)));
				player[i].isActive = true;
				player[i].hp = 10;
			}
		}
		else
			send(client_sock, (char*)&Time, sizeof(Time), 0);      // �ð� ���� ����


		mgr.bulletNum;
		//cout << mgr.bulletNum << endl;

		send(client_sock, (char*) &(mgr.bulletNum), sizeof(mgr.bulletNum), 0);         // �Ѿ� ���� ����

		int i = 1;
		for (auto p = mgr.BulletList.begin(); p != mgr.BulletList.end(); p++)
		{

			XMFLOAT3 pos = (*p)->xmfWorld;
			//printf("%d��° �Ѿ� : %lf %lf %lf\n", i, pos.x, pos.y, pos.z);
			i++;

			send(client_sock, (char*) &((*p)->xmfWorld), sizeof((*p)->xmfWorld), 0);   // �Ѿ� ��ġ ���� ����
		}

		boxStruct B;

		for (int i = 0; i < 10; ++i)
		{
			B.isActive[i] = mgr.BoxList[i]->isActive;               // ���� ��Ŷ B�� ��ֹ� �ڽ� ���翩�� ����
			B.Position[i] = mgr.BoxList[i]->xmfWorld;               // ���� ��Ŷ B�� ��ֹ� �ڽ� ��ġ ����
		}
		send(client_sock, (char*)&B, sizeof(B), 0);                  // ���� ��Ŷ B ����

	}

	closesocket(client_sock);
	clientNum--;
	exit(0);
	printf("[TCP ����] Ŭ���̾�Ʈ ���� : IP�ּ� = %s, ��Ʈ ��ȣ = %d \n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	
	return 0;
}

DWORD WINAPI Update(LPVOID arg)
{

	while (1)
	{
		//printf("Update \n");

		//WaitForSingleObject(ableToUpdate, INFINITE);

		WaitForMultipleObjects(3, ableToUpdate, TRUE, INFINITE);

		ResetEvent(ableToUpdate[0]);
		ResetEvent(ableToUpdate[1]);
		ResetEvent(ableToUpdate[2]);
		particle = 0;

		addBullet();

		mgr.animate();

		collisionChek_Box_Bullet();
		collisionChek_Player_Box();
		collisionChek_Player_Bullet();


		if (isGameover)
		{
			float curtime = timeGetTime();
			float etime = (curtime - gameover);

			//cout << etime << endl;

			if (etime > 3000)
			{
				isGameover = false;
				restart();
				gameover = 0;
			}
		}
		SetEvent(ableToCommu);

	}


	return 0;

}
int main()
{
	int retval;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
		err_quit("socket()");

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		err_quit("bind()");

	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
		err_quit("listen()");

	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;
	HANDLE hUpdate;

	ableToUpdate[0] = CreateEvent(NULL, TRUE, FALSE, NULL);
	ableToUpdate[1] = CreateEvent(NULL, TRUE, FALSE, NULL);
	ableToUpdate[2] = CreateEvent(NULL, TRUE, FALSE, NULL);
	ableToCommu = CreateEvent(NULL, TRUE, FALSE, NULL);


	while (1)
	{
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == SOCKET_ERROR)
		{
			err_display("accept()");
			break;
		}

		printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ ��ȣ = %d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));


		param p;
		p.s = client_sock;
		p.index = clientNum;

		param* pp = &p;
		hThread = CreateThread(NULL, 0, Communicate,
			(LPVOID)pp, 0, NULL);      // SOCKET Ÿ���� 32bit <= void*

									   // TODO : �Ӱ� ���� ?
		clientNum++;

		if (hThread == NULL)
			closesocket(client_sock);
		else
			CloseHandle(hThread);
		cout << clientNum << endl;

		if (clientNum == 3)
		{
			player[0].setPosition(XMFLOAT3(randomAxis(dre), randomAxis(dre), randomAxis(dre)));
			player[1].setPosition(XMFLOAT3(randomAxis(dre), randomAxis(dre), randomAxis(dre)));
			player[2].setPosition(XMFLOAT3(randomAxis(dre), randomAxis(dre), randomAxis(dre)));

			start = timeGetTime();
			hUpdate = CreateThread(NULL, 0, Update,
				NULL, 0, NULL);      // SOCKET Ÿ���� 32bit <= void*
			if (hUpdate == NULL)
				closesocket(client_sock);
			else
				CloseHandle(hUpdate);
		}
	}

	closesocket(listen_sock);

	WSACleanup();
	return 0;
}

void addBullet()
{
	for (int i = 0; i < clientNum; i++)
	{
		player[i].move();
		player[i].rotate();

		if (player[i].isActive)
		{
			if (player[i].dwKey & 0x01)
			{
				if (!player[i].shotOnce)
				{
					Bullet* b = new Bullet;
					b->xmfFiredPos = player[i].xmfWorld;
					b->xmfMovingDir = player[i].xmfLook;
					b->xmfWorld = player[i].xmfWorld;
					b->m_xmf4x4World._41 = b->xmfWorld.x;
					b->m_xmf4x4World._42 = b->xmfWorld.y;
					b->m_xmf4x4World._43 = b->xmfWorld.z;
					b->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
					b->settag(i);
					mgr.BulletList.push_back(b);
					mgr.bulletNum++;
					player[i].shotOnce = true;
				}
			}
			else
			{
				player[i].shotOnce = false;
			}
		}
	}
}

void collisionChek_Box_Bullet()
{
	for (int i = 0; i < 10; ++i)
	{
		if (mgr.BoxList[i]->isActive)
		{
			for (auto b = mgr.BulletList.begin(); b != mgr.BulletList.end();)
			{

				ContainmentType containType = (mgr.BoxList[i])->getOOBB()->Contains((*(*b)->getOOBB()));

				if (containType == INTERSECTS || containType == CONTAINS)
				{

					particle = 1;
					Ppos = (*b)->xmfWorld;
					b = mgr.BulletList.erase(b);
					--mgr.bulletNum;

					mgr.BoxList[i]->isActive = false;
					mgr.BoxList[i]->setDeadTime(chrono::system_clock::now());
				}
				else
					++b;
			}
		}
	}
}

void collisionChek_Player_Bullet()
{
	for (int i = 0; i < clientNum; ++i)
	{
		if (player[i].isActive)
		{
			for (auto b = mgr.BulletList.begin(); b != mgr.BulletList.end();)
			{
				if ((*b)->gettag() != i)
				{
					ContainmentType containType = player[i].getOOBB()->Contains((*(*b)->getOOBB()));
					if (containType == INTERSECTS || containType == CONTAINS)
					{
						player[i].hp--;
						if (player[i].hp > 0)
						{
							particle = 2;
							Ppos = (*b)->xmfWorld;
						}
						else
						{
							num_of_Player--;
							player[i].isActive = false;
							particle = 3;
							Ppos = (*b)->xmfWorld;
						}
						b = mgr.BulletList.erase(b);
						--mgr.bulletNum;

					}
					else
						++b;
				}
				else
					++b;
			}
		}

	}

	if (num_of_Player < 2 && !isGameover)
	{
		isGameover = true;
		gameover = timeGetTime();

		//restart();
	}
}

void collisionChek_Player_Box()
{
	for (int i = 0; i < 10; ++i)
	{
		if (mgr.BoxList[i]->isActive)
		{
			for (int j = 0; j < clientNum; ++j)
			{
				if (player[j].isActive)
				{
					ContainmentType containType = (mgr.BoxList[i])->getOOBB()->Contains(*(player[j].getOOBB()));
					if (containType == INTERSECTS || containType == CONTAINS)
					{

						particle = 1;
						Ppos = mgr.BoxList[i]->xmfWorld;


						mgr.BoxList[i]->isActive = false;
						mgr.BoxList[i]->setDeadTime(chrono::system_clock::now());
					}
				}

			}
		}
	}
}

void restart()
{

	Sleep(3000);
	Time = 60;
	TimeOver = 0;
	mgr.BulletList.clear();
	mgr.bulletNum = 0;
	for (int i = 0; i < clientNum; ++i)
	{
		player[i].setPosition(XMFLOAT3(randomAxis(dre), randomAxis(dre), randomAxis(dre)));
		player[i].isActive = true;
		player[i].hp = 10;
	}
	num_of_Player = clientNum;
}