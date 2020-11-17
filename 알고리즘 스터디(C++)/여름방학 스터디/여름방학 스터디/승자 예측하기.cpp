#include "stdafx.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	int T;
	long long N;

	scanf_s("%d", &T);
	//cin >> T;

	for (int t = 0; t < T; ++t)
	{
		scanf_s("%lld", &N);
		//cin >> N;
	
		long long x = 1;
		long long count = 1;
		
		int term = 0;
		while (x < N)
		{
			if (!term)
			{
				count *= 4;
			}
			x += count;
			term = !term;
		}
		
		if (!term)
			printf("#%d Bob\n", t + 1);
		else
			printf("#%d Alice\n", t + 1);

	}
}