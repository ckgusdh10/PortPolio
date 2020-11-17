#include "stdafx.h"

#include <iostream>

using namespace std;

int main()
{
	int n;
	int num[100000] = { 0 };
	int cur = 0;


	cin >> n;


	for (int i = 0; i < n; ++i)
	{
		cin >> num[i];
	}
	cur = num[0];

	// 1 2 3
	// -5 1 2 3 - 4 5
	long long max_num = -999999;

	for (int i = 1; i < n; ++i)
	{
		if (cur < 0)									// 현재 숫자가 0보다 작을 때
		{
			if (cur > max_num)							// 지금까지 max값이 현재 값 보다 작을 때 ( 지금까지 음수값만 나온 경우 )
				max_num = cur;
			if (cur < num[i] && max_num < num[i])		// 현재 값과 max값이 다음 값보다 작을 때
				max_num = num[i];
			cur = num[i];			
			continue;
		}
		if (cur + num[i] > 0)							// 현재 값과 다음 값의 합이 0보다 클 때
		{
			cur += num[i];
		}
		else											// 현재 값과 다음 값의 합이 0보다 클 때
		{
			if (i != n - 1)								// 배열의 끝이 아닐 때
			{
				cur = num[i + 1];
				++i;
			}

		}
		if (cur > max_num)								// 최대값 갱신
			max_num = cur;
	}
	if (cur > max_num)
		max_num = cur;

	cout << max_num << endl;
}
