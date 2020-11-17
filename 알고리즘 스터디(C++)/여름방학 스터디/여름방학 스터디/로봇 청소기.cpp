#include "stdafx.h"

#include <iostream>

using namespace std;

int N, M;
int base[60][60];
int pos[] = { 0,0 };
int dir = 0;
// 0번 : 북, 1번 : 동, 2번 : 남, 3번 : 서
int dirX[4] = { 0,1,0,-1 };
int dirY[4] = { -1,0,1,0 };

void Search()
{
	int cnt = 0;

	while (true)
	{
		if (base[pos[0]][pos[1]] == 0)		// 현재 자리가 빈칸일 때
		{
			base[pos[0]][pos[1]] = 3;
			++cnt;
		}

		bool check = false;					// 4방향 체크가 되었는 지 확인해 줄 변수
		for (int i = 0; i < 4; ++i)
		{

			dir = (dir + 3) % 4;			// 왼쪽방향 회전
			int posX = pos[0] + dirY[dir];
			int posY = pos[1] + dirX[dir];

			if (base[posX][posY] == 1 || base[posX][posY] == 3)		// 회전한 후 앞칸의 위치가 벽이거나 청소된 구역
			{
				continue;
			}

			if (posX < 0 || posX >= N || posY < 0 || posY >= M)		// 회전한 후 앞칸의 위치가 배열의 크기를 벗어났을 때
			{
				
				continue;
			}
			
			pos[0] = posX;											// for문 동안 이 부분을 한번도 안 거치면 4방향 다 막힌 것
			pos[1] = posY;
			check = true;
			break;
			
		}

		if (!check)
		{
			pos[0] = pos[0] - dirY[dir];
			pos[1] = pos[1] - dirX[dir];

			if (pos[0] < 0 || pos[0] >= N || pos[1] < 0 || pos[1] >= M || base[pos[0]][pos[1]] == 1)
			{
				break;
			}
		}
	}
	cout << cnt << endl;

}

int main()
{
	cin >> N >> M;							// N : 세로  M : 가로 
	cin >> pos[0] >> pos[1] >> dir;			// 로봇의 좌표와 방향
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cin >> base[i][j];
		}
	}
	Search();

}