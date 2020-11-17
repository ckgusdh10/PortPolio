#include "stdafx.h"

#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
	int T, N;
	
	cin >> T;

	int score[1420];

	for (int t = 0; t < T; ++t)
	{
		cin >> N;

		int answer[142000] = { 0 };
		answer[0] = 1;

		int max = 0;
		for (int i = 0; i < N; ++i)
		{
			cin >> score[i];
			max += score[i];
			for (int j = max; j > 0; --j)
			{
				if (answer[j] > 0)
				{
					answer[j + score[i]]++;
				}
			}
			answer[score[i]]++;

		}
		int count = 0;
		for (int i = 0; i < 142000; ++i)
		{
			if (answer[i] > 0)
				++count;
		}
	
		cout << "#" << t + 1 << " " << count << endl;
	}

}