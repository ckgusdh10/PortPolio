#include "stdafx.h"

#include <iostream>

using namespace std;

int main()
{
	int N, K;
	int name[1420] = { 0 };
	int multitap[1420] = { 0 };
	int count = 0;

	cin >> N >> K;

	for (int i = 0; i < K; ++i)
	{
		cin >> name[i];
	}

	for (int i = 0; i < K; ++i)
	{
		bool b = false;
		if (name[i] != 0)
		{
			for (int j = 0; j < N; ++j)
			{
				if (multitap[j] == 0)
				{
					multitap[j] = name[i];
					name[i] = 0;
					b = false;
					break;
				}

				if (multitap[j] == name[i])
				{
					name[i] = 0;

					b = false;
					break;
				}
				b = true;
			}
		}

		if (b)
		{
			int dis = 0;
			int index = 0;

			for (int r = 0; r < N; ++r)
			{
				for (int j = 0; j < K; ++j)
				{
					if (multitap[r] == name[j])
					{
						if (j > dis)
						{
							dis = j;
							index = r;
							break;
						}
						else
							break;
					}
					if (j == K - 1)
						dis = 0;
				}
				if (dis == 0)
				{
					index = r;
					dis = 1;
					break;
				}

			}
			multitap[index] = name[i];
			name[i] = 0;
			++count;
		
		}

	}

	cout << count << endl;
}