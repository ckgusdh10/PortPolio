#include "stdafx.h"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M, X;
vector<pair<int, int>> v[1001];
int dis[1001];
int dist[1001];

void Dijkstra(int s)
{
	priority_queue<pair<int, int>> pq;
	dis[s] = 0;
	pq.push(make_pair(0, s));

	while (pq.empty() == 0)
	{
		int dist = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();

		for (int i = 0; i < v[cur].size(); i++)
		{
			int next = v[cur][i].first;
			int ndist = v[cur][i].second;

			if (dis[next] > dist + ndist)
			{
				dis[next] = dist + ndist;
				pq.push(make_pair(-dis[next], next));
			}
		}
	}

}

int main()
{
	cin >> N >> M >> X;

	for (int i = 0; i < M; ++i)
	{
		int s, e, d;
		cin >> s >> e >> d;
		v[s].push_back(make_pair(e, d));
	}


	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j) 
			dis[j] = 9999999;
		Dijkstra(i);
		dist[i] = dis[X];
	}
	/*for (int i = 1; i <= N; ++i)
	{
		cout << dist[i] << endl;
	}*/
	for (int i = 1; i <= N; ++i)
		dis[i] = 9999999;
	Dijkstra(X);
	for (int i = 1; i <= N; ++i)
	{
		dist[i] += dis[i];
	}
	sort(dist + 1, dist + N + 1);

	cout << dist[N] << endl;
	
}