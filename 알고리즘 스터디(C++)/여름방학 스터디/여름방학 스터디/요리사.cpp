#include "stdafx.h"

#include <iostream>

using namespace std;

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t)
	{
		int N;
		cin >> N;

		int base[16][16] = { 0 };

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				cin >> base[i][j];
			}
		}
	}
}