#include "stdafx.h"

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<int> v[3000];
bool visit[3000] = { false };

struct ENEMY {
	int x;
	int y;
	double r;
};

void dfs(int index)
{
	visit[index] = true;

	for (int i = 0; i < v[index].size(); ++i)
	{
		if (visit[v[index][i]])
			continue;

		dfs(v[index][i]);
	}
}

int main()
{
	int T, N;
	cin >> T;

	ENEMY enemy[3000];

	for (int t = 0; t < T; ++t)
	{
		cin >> N;
		for (int i = 0; i < 3000; ++i)
		{
			visit[i] = false;
			v[i].clear();
		}
		for (int i = 0; i < N; ++i)
		{
			int x, y, r;
			cin >> enemy[i].x >> enemy[i].y >> enemy[i].r;
		
		}

		for (int i = 0; i < N; ++i)
		{
			for (int j = i + 1; j < N; ++j)
			{
				int disX = enemy[i].x - enemy[j].x;
				int disY = enemy[i].y - enemy[j].y;
				double d = sqrt(disX * disX + disY * disY);

				if (d <= enemy[i].r + enemy[j].r)
				{
					v[i].push_back(j);
					v[j].push_back(i);
				}
			}
		}
		int count = 0;
		for (int i = 0; i < N; ++i)
		{
			if (visit[i])
				continue;
			
			++count;
			for (int j = 0; j < v[i].size(); ++j)
			{
				dfs(v[i][j]);
				
			}
		
		}

		cout << count << endl;
	
	}
}