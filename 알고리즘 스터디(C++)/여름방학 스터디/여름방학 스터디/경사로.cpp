#include "stdafx.h"

#include <iostream>
#include <queue>

using namespace std;

struct Pos {
	int x;
	int y;
};

int T;
int N, M, L;
Pos hole;
int base[51][51] = { 0 };
bool visit[51][51] = { false };

int dirX[4] = { -1,0,1,0 };//╩С,©Л,го,аб
int dirY[4] = { 0,1,0,-1 };

queue<pair<int, int>> q;
int answer = 0;

void bfs()
{
	int time = 0;

	while (true)
	{
		++time;

		if (time == L)
		{
			while (!q.empty())
				q.pop();
			break;
		}

		int size = q.size();
		for (int i = 0; i < size; ++i)
		{
			int x = q.front().first;
			int y = q.front().second;
			q.pop();

			int val = base[x][y];

			for (int j = 0; j < 4; ++j)
			{
				if (val == 2 && (j == 1 || j == 3))
					continue;
				else if (val == 3 && (j == 0 || j == 2))
					continue;
				else if (val == 4 && (j == 2 || j == 3))
					continue;
				else if (val == 5 && (j == 0 || j == 3))
					continue;
				else if (val == 6 && (j == 0 || j == 1))
					continue;
				else if (val == 7 && (j == 1 || j == 2))
					continue;

				int nx = x + dirX[j];
				int ny = y + dirY[j];
				int nval = base[nx][ny];

				if (nx < 0 || ny < 0 || nx >= N || ny >= M)
				{
					continue;
				}
				if (visit[nx][ny] == true)
					continue;
				if (nval == 0)
					continue;

				if (j == 0)
				{
					if (nval == 1 || nval == 2 || nval == 5 || nval == 6)
					{
						visit[nx][ny] = true;
						q.push(make_pair(nx, ny));
					}
				}
				else if (j == 1)
				{
					if (nval == 1 || nval == 3 || nval == 6 || nval == 7)
					{
						visit[nx][ny] = true;
						q.push(make_pair(nx, ny));
					}
				}
				else if (j == 2)
				{
					if (nval == 1 || nval == 2 || nval == 4 || nval == 7)
					{
						visit[nx][ny] = true;
						q.push(make_pair(nx, ny));
					}
				}
				else if(j == 3)
				{
					if (nval == 1 || nval == 3 || nval == 4 || nval == 5)
					{
						visit[nx][ny] = true;
						q.push(make_pair(nx, ny));
					}
				}
			}
		}
	}
}

int main()
{
	cin >> T;

	for (int t = 1; t <= T; ++t)
	{
		cin >> N >> M >> hole.x >> hole.y >> L;

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				cin >> base[i][j];
				visit[i][j] = false;
			}
		}
		q.push(make_pair(hole.x, hole.y));
		visit[hole.x][hole.y] = true;

		bfs();
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (visit[i][j])
				{
					++answer;
				}
			}
		}

		cout << "#" << t << " " <<  answer << endl;

		answer = 0;
	
	}
}