#include "stdafx.h"

#include <iostream>

using namespace std;

int N;
int t[15] = { 0 };
int p[15] = { 0 };
int answer = 0;

void dfs(int day, int sum)
{
	if (day >= N)
	{
		if (sum > answer)
			answer = sum;
		return;
	}

	dfs(day + 1, sum);							// 상담을 하지 않을 때

	if (day + t[day] <= N)						// N일 안에 상담을 할 수 있을 때
	{
		dfs(day + t[day], sum + p[day]);
	}
}

int main()
{
	cin >> N;

	for (int i = 0; i < N; ++i)
	{
		cin >> t[i] >> p[i];
	}

	dfs(0, 0);

	cout << answer << endl;
}