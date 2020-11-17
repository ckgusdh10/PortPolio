#include "stdafx.h"

#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int cmp(int a, int b)
{
	return a > b;
}

bool check(int mid, vector<int> stones, int k)
{
	int count = 0;
	for (int i = 0; i < stones.size(); ++i)
	{
	
		if (stones[i] - mid <= 0)
			count++;
		else
			count = 0;

		if (count >= k)
			return false;
	}
	return true;
}

int solution(vector<int> stones, int k) {
	int answer = 0;
	vector<int> v = stones;
	sort(v.begin(), v.end(), cmp);
	//cout << v[0] << endl;

	int minnum = 1;
	int maxnum = v[0];

	while (minnum <= maxnum)
	{
		int mid = (minnum + maxnum) / 2;

		if (check(mid, stones, k))
		{
			minnum = mid + 1;
		}
		else
			maxnum = mid - 1;
	}
	
	
	return minnum;
}

int main()
{
	vector<int> stones = { 2,4, 5,3,2,1,4,2,5,1 };
	int k = 3;

	cout << solution(stones, 3) << endl;
}