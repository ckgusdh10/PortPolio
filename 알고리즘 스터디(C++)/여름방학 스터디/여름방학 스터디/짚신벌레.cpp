#include "stdafx.h"

#include <iostream>
#include <vector>


using namespace std;

int bugs[14200000];

int main()
{
	int a, b, d, N;
	cin >> a >> b >> d >> N;

	bugs[0] = 1;

	for (int i = 1; i < N + 1; ++i)
	{
		if (i < a)
		{
			bugs[i] = bugs[i - 1] % 14200;
		}
		else if (i < b)
		{
			bugs[i] = (bugs[i - 1] + bugs[i - a]) % 14200;
		}
		else
		{
			bugs[i] = (bugs[i - 1] + bugs[i - a] - bugs[i - b] + 14200) % 14200;
		}
	}

	if (N >= d)
	{
		cout << ((bugs[N] - bugs[N - d] + 14200) % 14200) << endl;
	}
	else
		cout << bugs[N] % 14200 << endl;
	

}