#include "stdafx.h"

#include <iostream>

using namespace std;

int N;
int base[100][100] = { 0 };
bool visit[100][100] = { false };
int temp[100][100] = { 0 };

int dirX[4] = { 1,-1,0,0 };
int dirY[4] = { 0,0,1,-1 };

void dfs(int x, int y)
{

	visit[x][y] = true;

	for (int i = 0; i < 4; ++i)
	{
		int nx = x + dirX[i];
		int ny = y + dirY[i];

		

		if (nx >= 0 && nx < N && ny >= 0 && ny < N && visit[nx][ny] == false)
		{
			if (temp[nx][ny] != 0)
			{
				dfs(nx, ny);
			}
		}
	}
}

int main()
{
	cin >> N;
	int maxdep = 0;
	int answer = 0;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> base[i][j];
			if (base[i][j] > maxdep)
				maxdep = base[i][j];
		}
	}

	for (int m = maxdep; m >= 0; --m)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (base[i][j] > m)
					temp[i][j] = base[i][j];
			}
		}

		int count = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (temp[i][j] > 0 && visit[i][j] == false)
				{
					dfs(i, j);
					++count;
				}
				
			}
		}
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				visit[i][j] = false;
				temp[i][j] = 0;
			}
		}

		//cout << count << endl;
		if (count > answer)
			answer = count;
		
		
	}
	cout << answer << endl;

}