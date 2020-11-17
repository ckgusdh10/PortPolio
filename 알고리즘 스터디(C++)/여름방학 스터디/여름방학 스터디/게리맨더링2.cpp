#include "stdafx.h"

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int base[21][21] = { 0 };

int div(int x, int y, int d1, int d2)
{
	vector<int> pop;

	pop.resize(5);
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			if (i < x + d1 && j <= y)
			{
				pop[0] += base[i][j];
			}
			else if (i <= x + d2 && j > y)
			{
				pop[1] += base[i][j];
			}
			else if (i >= x + d1 && j < y - d1 + d2)
			{
				pop[2] += base[i][j];
			}
			else if (i > x + d2 && j >= y - d1 + d2)
			{
				pop[3] += base[i][j];
			}
			else
			{
				pop[4] += base[i][j];
			}
		}
	}
	

	sort(pop.begin(), pop.end());
	
	int res = pop[4] - pop[0];
	
	return res;
}

int main()
{
	cin >> N;

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			cin >> base[i][j];
		}
	}

	int answer = 999999;
	for (int i = 1; i < N - 2; ++i)
	{
		for (int j = 2; j < N - 1; ++j)
		{
			int d1 = 1;
			int d2 = 1;

			for (int k = d1; k < j - 1 && k <= N - i - 1; ++k)
			{
				for (int r = d2; r <= N - j && r <= N - i - 1; ++r)
				{
					int res;
					res = div(i, j, k, r);

					if (res < answer)
						answer = res;
				}
			}
		}
	}

	cout << answer << endl;
}