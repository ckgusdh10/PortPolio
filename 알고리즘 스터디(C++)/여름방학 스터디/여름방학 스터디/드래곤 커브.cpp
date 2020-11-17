#include "stdafx.h"

#include <iostream>
#include <vector>


using namespace std;

struct Dragon_Info {
	int x;
	int y;
	int d;
	int g;
};

int dirX[4] = { 1,0,-1,0 };
int dirY[4] = { 0,-1,0,1 };


int main()
{
	int N;
	cin >> N;

	int base[101][101];
	bool visit[101][101] = { false };
	

	Dragon_Info dragon[20];

	for (int i = 0; i < N; ++i)
	{
		cin >> dragon[i].x >> dragon[i].y >> dragon[i].d >> dragon[i].g;
	}

	for (int i = 0; i < N; ++i)
	{
		int x = dragon[i].x;
		int y = dragon[i].y;
		int d = dragon[i].d;
		int g = dragon[i].g;

		vector<int> dir;
		dir.push_back(d);
		visit[y][x] = true;

		for (int j = 0; j < g; ++j)
		{
			vector<int> temp = dir;

			for (int k = temp.size() - 1; k >= 0; --k)
			{
				dir.push_back((temp[k] + 1) % 4);
			}

		}

		for (int j = 0; j < dir.size(); ++j)
		{
			x += dirX[dir[j]];
			y += dirY[dir[j]];

			if (x >= 0 && x < 101 && y >= 0 && y < 101)
			{
				visit[y][x] = true;
			}
		}
	}
	int count = 0;
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			if (visit[i][j] == true)
			{
				if (visit[i + 1][j] == true && visit[i][j + 1] == true && visit[i + 1][j + 1] == true)
				{
					++count;
				}
			}

		}
	}

	cout << count << endl;
}