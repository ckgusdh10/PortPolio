#include "stdafx.h"

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	int N, K, L;
	int board[101][101] = { 0 };
	int apple[101][101] = { 0 };
	queue<pair<int, char>> rot;
	queue<pair<int, int>> visit;
	visit.push(make_pair(1, 1));

	int dirX[4] = { 0,1,0,-1 };
	int dirY[4] = { 1,0,-1,0 };

	cin >> N >> K;

	for (int k = 0; k < K; ++k)
	{
		int x = 0, y = 0;
		cin >> x >> y;
		board[x][y] = 1;
	}

	cin >> L;

	for (int l = 0; l < L; ++l)
	{
		int count;
		char dir;
		cin >> count >> dir;
		rot.push(make_pair(count, dir));
	}

	int snake_x = 1;
	int snake_y = 1;
	int dir = 0;

	int answer = 0;

	while (true)
	{
		++answer;

		int nx = snake_x += dirX[dir];
		int ny = snake_y += dirY[dir];

		if (nx <= 0 || nx > N || ny <= 0 || ny > N)
		{
			break;
		}
		if (board[nx][ny] == -1)
		{
			break;
		}

		if (board[nx][ny] == 1)
		{
			visit.push(make_pair(nx, ny));
			board[nx][ny] = -1;
		}
		else if (board[nx][ny] == 0)
		{
			visit.push(make_pair(nx, ny));
			board[nx][ny] = -1;
			int x = visit.front().first;
			int y = visit.front().second;
			board[x][y] = 0;
			visit.pop();
		}

		if (rot.size() > 0)
		{
			if (answer == rot.front().first)
			{
				if (rot.front().second == 'D')
				{
					dir = (dir + 1) % 4;
				}
				else if (rot.front().second == 'L')
				{
					dir = (dir + 3) % 4;
				}
				rot.pop();
			}
		}
	}
	//cout << visit.back().first << " " << visit.back().second << endl;
	cout << answer << endl;
}