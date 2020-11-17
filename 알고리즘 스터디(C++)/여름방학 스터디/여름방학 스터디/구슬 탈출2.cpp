#include "stdafx.h"

#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct ball {
	int x;
	int y;
};

int dirX[4] = { 1,-1,0,0 };
int dirY[4] = { 0,0,1,-1 };

int N, M;
char base[10][10];
bool visit[10][10][10][10] = { false };

ball red;
ball blue;
queue<pair<int, int>> rq;
queue<pair<int, int>> bq;
int answer = 0;
bool check = false;

void bfs()
{
	while (!rq.empty())
	{
		int size = rq.size();

		while (size--)
		{
			//answer = 0;
			int rx = rq.front().first;
			int ry = rq.front().second;
			int bx = bq.front().first;
			int by = bq.front().second;
			rq.pop();
			bq.pop();

			if (answer > 10)
				break;

			if (base[rx][ry] == 'O')
			{
				//cout << answer << endl;
				check = true;
				break;
			}

			for (int i = 0; i < 4; ++i)
			{
				int nrx = rx;
				int nry = ry;
				int nbx = bx;
				int nby = by;
				int rdis = 0;
				int bdis = 0;

				while (base[nrx + dirX[i]][nry + dirY[i]] != '#' && base[nrx][nry] != 'O')
				{
					nrx += dirX[i];
					nry += dirY[i];
					rdis++;
				}
				while (base[nbx + dirX[i]][nby + dirY[i]] != '#' && base[nbx][nby] != 'O')
				{
					nbx += dirX[i];
					nby += dirY[i];
					bdis++;
				}
				//++answer;
				if (base[nbx][nby] == 'O')
				{
					continue;
				}

				if (nrx == nbx && nry == nby)
				{
					if (rdis > bdis)
					{
						nrx -= dirX[i];
						nry -= dirY[i];
					}
					else
					{
						nbx -= dirX[i];
						nby -= dirY[i];
					}

				}

				if (visit[nrx][nry][nbx][nby] == true)
					continue;
				rq.push(make_pair(nrx, nry));
				bq.push(make_pair(nbx, nby));
				visit[nrx][nry][nbx][nby] = true;
			}
			
		}
		
		if (check)
		{
			break;
		}
		else
			answer++;
	}
	if (check)
		cout << answer << endl;
	else
		cout << -1 << endl;
	//cout << "-1" << endl;

}

int main()
{
	cin >> N >> M;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cin >> base[i][j];
			if (base[i][j] == 'R')
			{
				red.x = i;
				red.y = j;
			}
			else if (base[i][j] == 'B')
			{
				blue.x = i;
				blue.y = j;
			}
		}
	}
	rq.push(make_pair(red.x, red.y));
	bq.push(make_pair(blue.x, blue.y));
	visit[red.x][red.y][blue.x][blue.y] = true;

	bfs();

	//cout << answer << endl;

}