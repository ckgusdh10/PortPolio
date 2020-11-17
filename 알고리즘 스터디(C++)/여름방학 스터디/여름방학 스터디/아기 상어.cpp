#include "stdafx.h"

#include <iostream>
#include <vector>
#include <queue>


using namespace std;

struct fish {
	int x;
	int y;
	int size;
	int growth;
};

struct Destination {
	int x;
	int y;
	int dis;
};

int N;
int base[20][20];
int dist[20][20];

int dirX[4] = { 1,-1,0,0 };
int dirY[4] = { 0,0,1,-1 };

bool visit[20][20] = { false };
queue<pair<int, int>> q;
int answer = 0;


Destination bfs(int size, int dest_x, int dest_y)
{
	bool flag = false;
	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		
		for (int i = 0; i < 4; ++i)
		{
			int nx = x + dirX[i];
			int ny = y + dirY[i];

			if (nx == dest_x && ny == dest_y)
			{
				dist[nx][ny] = dist[x][y] + 1;
				while (!q.empty())
				{
					flag = true;
					q.pop();
				}
				break;
			}

			if (nx < 0 || nx >= N || ny < 0 || ny >= N)
				continue;
			if (visit[nx][ny] == true || size < base[nx][ny])
				continue;

			dist[nx][ny] = dist[x][y] + 1;
			visit[nx][ny] = true;
			q.push(make_pair(nx, ny));
		}
	}
	//cout << dist[dest_x][dest_y] << endl;
	//answer += dist[dest_x][dest_y];
	Destination d;
	if (flag)
		d.dis = dist[dest_x][dest_y];
	else
		d.dis = 30;
	d.x = dest_x;
	d.y = dest_y;
	return d;
}

void bfs2(int size, int dest_x, int dest_y)
{
	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; ++i)
		{
			int nx = x + dirX[i];
			int ny = y + dirY[i];

			if (nx == dest_x && ny == dest_y)
			{
				dist[nx][ny] = dist[x][y] + 1;
				while (!q.empty())
				{
					q.pop();
				}
				break;
			}

			if (nx < 0 || nx >= N || ny < 0 || ny >= N)
				continue;
			if (visit[nx][ny] == true || size < base[nx][ny])
				continue;

			dist[nx][ny] = dist[x][y] + 1;
			visit[nx][ny] = true;
			q.push(make_pair(nx, ny));
		}
	}
	//cout << dist[dest_x][dest_y] << endl;
	answer += dist[dest_x][dest_y];
}


int main()
{

	cin >> N;


	fish shark;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> base[i][j];
			if (base[i][j] == 9)
			{
				shark.x = i;
				shark.y = j;
				shark.size = 2;
				shark.growth = 0;
				base[i][j] = 0;
			}
		}
	}

	while (true)
	{
		vector<pair<int, int>> feed;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (shark.size > base[i][j] && base[i][j] != 0)
				{
					feed.push_back(make_pair(i, j));
				}
			}
		}

		if (feed.size() == 0)
		{
			break;
		}
		
		/*for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				dist[i][j] = 0;
				visit[i][j] = false;
			}
		}*/

		int min_dis = 30;
		int feed_x = 0;
		int feed_y = 0;
		Destination destination;
		for (int i = 0; i < feed.size(); ++i)
		{
		
			q.push(make_pair(shark.x, shark.y));
			visit[shark.x][shark.y] = true;
			Destination di = bfs(shark.size, feed[i].first, feed[i].second);
			if (di.dis < min_dis)
			{
				min_dis = di.dis;
				feed_x = di.x;
				feed_y = di.y;
				destination = di;
			}
			else if (di.dis == min_dis)
			{
				if (di.x < feed_x)
				{
					feed_x = di.x;
					feed_y = di.y;
					destination = di;
				}
				else if (di.x == feed_x)
				{
					if (di.y < feed_y)
					{
						feed_x = di.x;
						feed_y = di.y;
						destination = di;
					}
				}
			}
			for (int k = 0; k < N; ++k)
			{
				for (int j = 0; j < N; ++j)
				{
					dist[k][j] = 0;
					visit[k][j] = false;
				}
			}
		}
		answer += destination.dis;
		cout << destination.dis << endl;
		/*for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				dist[i][j] = 0;
				visit[i][j] = false;
			}
		}

		q.push(make_pair(shark.x, shark.y));
		visit[shark.x][shark.y] = true;
		bfs2(shark.size, feed_x, feed_y);*/
		
		shark.x = feed_x;
		shark.y = feed_y;
		shark.growth += 1;
		base[feed_x][feed_y] = 0;
		if (shark.size == shark.growth)
		{
			shark.size++;
			shark.growth = 0;
		}

		//cout << feed_x << " " << feed_y << endl;
	}


	cout << answer << endl;

}