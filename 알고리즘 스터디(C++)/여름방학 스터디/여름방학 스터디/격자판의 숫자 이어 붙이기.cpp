#include "stdafx.h"

#include <iostream>
#include <map>

using namespace std;

int base[4][4] = { 0 };

int dirX[4] = { 1,-1,0,0 };
int dirY[4] = { 0,0,1,-1 };

//int cnt = 0;

map<int, int> m;

void dfs(int x, int y, int c, int r)
{
	for (int i = 0; i < 4; ++i)
	{
		if (c == 7)
		{
			m[r]++;
			break;
		}

		int nx = x + dirX[i];
		int ny = y + dirY[i];

		if (nx >= 0 && nx < 4 && ny >= 0 && ny < 4)
		{
			int result = r * 10;
			
			dfs(nx, ny, c + 1, result + base[nx][ny]);
		}
	}
}

int main()
{
	int T;
	cin >> T;



	for (int t = 0; t < T; ++t)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				cin >> base[i][j];
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				dfs(i, j, 1, base[i][j]);
			}
		}

		cout << "#" << t + 1 << " " << m.size() << endl;
		m.clear();
	}

}