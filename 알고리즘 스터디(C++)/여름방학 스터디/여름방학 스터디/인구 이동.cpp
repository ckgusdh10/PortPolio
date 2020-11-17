#include "stdafx.h"

#include <iostream>
#include <vector>


using namespace std;

bool visit[50][50] = { false };
int base[50][50];
int pop = 0;
int dirX[4] = { 1,-1,0,0 };
int dirY[4] = { 0,0,1,-1 };
int N, L, R;
int nb = 0;


vector<pair<int, int>> pos;

void dfs(int x, int y)
{
	for (int i = 0; i < 4; ++i)
	{
		int nx = x + dirX[i];
		int ny = y + dirY[i];

		if (nx >= 0 && nx < N && ny >= 0 && ny < N)
		{
			if (abs(base[x][y] - base[nx][ny]) >= L && abs(base[x][y] - base[nx][ny]) <= R && visit[nx][ny] == false)
			{
				visit[nx][ny] = true;
				pos.push_back(make_pair(nx, ny));
				pop += base[nx][ny];
				++nb;
				dfs(nx, ny);

			}
		}
	}
}

int main()
{
	cin >> N >> L >> R;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> base[i][j];
		}
	}
	int count = 0;
	while (true)
	{
		bool b = false;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				visit[i][j] = false;
			}
		}

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (visit[i][j] == true)
					continue;

				visit[i][j] = true;
				pop = base[i][j];

				pos.clear();
				pos.push_back(make_pair(i, j));

				nb = 0;
				dfs(i, j);

				if (nb > 0)
				{
					for (int k = 0; k < pos.size(); ++k)
					{
						b = true;
						base[pos[k].first][pos[k].second] = pop / (nb + 1);
					}
				}

			}
		}
		if (!b)
			break;
		else
			++count;
	}
	
	
	/*for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cout << base[i][j] << " ";
		}
		cout << endl;
	}*/
	cout << count << endl;
}