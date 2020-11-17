#include "stdafx.h"

#include <iostream>
#include <vector>

using namespace std;

int N, M;
int base[55][55];

vector<pair<int, int>> house;
vector<pair<int, int>> store;
vector<pair<int, int>> keep_store;

int dist = 55;
int answer = 1e9;

void dfs2(int index)
{
	if (keep_store.size() == M)
	{
		int result = 0;
		for (int i = 0; i < house.size(); ++i)
		{
			int dist = 55;
			for (int j = 0; j < keep_store.size(); ++j)
			{
				int dis = abs(house[i].first - keep_store[j].first) + abs(house[i].second - keep_store[j].second);
				if (dis < dist)
				{
					dist = dis;
				}
			}
			//cout << dist << endl;
			result += dist;
		}
		if (result < answer)
		{
			answer = result;
		}
		return;
	}

	for (int i = index; i < store.size(); ++i)
	{
		keep_store.push_back(store[i]);
		dfs2(i + 1);
		keep_store.pop_back();
	}

}

int main()
{
	cin >> N >> M;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> base[i][j];
			if (base[i][j] == 1)
			{
				house.push_back(make_pair(i, j));
			}
			else if (base[i][j] == 2)
			{
				store.push_back(make_pair(i, j));
			}
		}
	}

	dfs2(0);

	cout << answer << endl;
}