#include "stdafx.h"

#include <iostream>

using namespace std;

int N, M;
int base[60][60];
int pos[] = { 0,0 };
int dir = 0;
// 0�� : ��, 1�� : ��, 2�� : ��, 3�� : ��
int dirX[4] = { 0,1,0,-1 };
int dirY[4] = { -1,0,1,0 };

void Search()
{
	int cnt = 0;

	while (true)
	{
		if (base[pos[0]][pos[1]] == 0)		// ���� �ڸ��� ��ĭ�� ��
		{
			base[pos[0]][pos[1]] = 3;
			++cnt;
		}

		bool check = false;					// 4���� üũ�� �Ǿ��� �� Ȯ���� �� ����
		for (int i = 0; i < 4; ++i)
		{

			dir = (dir + 3) % 4;			// ���ʹ��� ȸ��
			int posX = pos[0] + dirY[dir];
			int posY = pos[1] + dirX[dir];

			if (base[posX][posY] == 1 || base[posX][posY] == 3)		// ȸ���� �� ��ĭ�� ��ġ�� ���̰ų� û�ҵ� ����
			{
				continue;
			}

			if (posX < 0 || posX >= N || posY < 0 || posY >= M)		// ȸ���� �� ��ĭ�� ��ġ�� �迭�� ũ�⸦ ����� ��
			{
				
				continue;
			}
			
			pos[0] = posX;											// for�� ���� �� �κ��� �ѹ��� �� ��ġ�� 4���� �� ���� ��
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
	cin >> N >> M;							// N : ����  M : ���� 
	cin >> pos[0] >> pos[1] >> dir;			// �κ��� ��ǥ�� ����
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cin >> base[i][j];
		}
	}
	Search();

}