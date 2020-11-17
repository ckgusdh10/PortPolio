#include "stdafx.h"

#include <iostream>

using namespace std;

int main()
{	
	int T;
	int testcase;
	
	int score[1421] = { 0 };

	cin >> T;
	for (int i = 0; i < T; ++i)
	{
		cin >> testcase;

		int fre = 0;
		int index = 0;

		for (int j = 0; j < 14200; ++j)
		{
			int n;
			cin >> n;
			++score[n];
		}

		for (int i = 0; i < 1421; ++i)
		{
			if (score[i] >= fre)
			{
				fre = score[i];
				index = i;
			}
		}

		cout << "#" << i + 1 << " " << index << endl;
		
		for (int i = 0; i < 1421; ++i)
			score[i] = 0;
	}
	
}

