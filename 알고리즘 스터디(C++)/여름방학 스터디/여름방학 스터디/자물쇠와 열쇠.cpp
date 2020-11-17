#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
bool answer = false;
void g_rotate(int graph[64][64], int size, int cnt, vector<vector<int>> lock)		// 확장시킨 자물쇠 배열, 크기, 회전횟수, 자물쇠정보
{
	if (cnt == 4 /*|| answer == false*/)
	{
		return;
	}
	int temp[64][64] = { 0 };
	int N = size;
	for (int i = 0; i < N; i++)									// 행렬 회전
	{
		for (int j = 0; j < N; j++)
			temp[i][j] = graph[N - j - 1][i];
	}
	graph = temp;

	int x = 0;
	int y = 0;
	bool b1 = true;
	while (b1)
	{
		bool b = true;
		for (int i = x; i < lock.size() + x; ++i)
		{
			for (int j = y; j < lock.size() + y; ++j)
			{
				if (graph[i][j] == lock[i - x][j - y])
				{
					b = false;
					break;
				}
			}
			if (!b)
			{
				//b1 = false;
				//answer = false;
				break;
			}
		}
		if (b)
		{
			answer = true;
			return;
			//cout << " 1" << endl;
			break;
		}

		y += 1;

		if (y > size - lock.size() + 1)
		{
			x += 1;
			y = 0;
			if (x > size - lock.size() + 1)
			{
				b1 = false;
			}
		}

	}

	g_rotate(graph, size, cnt + 1, lock);
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {

	int keybase[64][64] = { 0 };

	int keysize = key.size();
	int locksize = lock.size();
	//cout << keysize << endl;
	for (int i = 0; i < keysize; ++i)									// 이 이중 for문은 확장시킨 자물쇠배열 가운데에 자물쇠 정보를 입력
	{
		for (int j = 0; j < keysize; ++j)
		{
			keybase[i + locksize][j + locksize] = key[i][j];
		}
	}
	g_rotate(keybase, locksize * 3, 0, lock);

	return answer;
}

int main()
{
	vector<vector<int>> key = { { 0, 0, 0},{1, 0, 0 }, { 0, 1, 1 } };
	vector<vector<int>> lock = { {1, 1, 1},{1, 1, 0},{1, 0, 1} };

	cout << solution(key, lock) << endl;

}
