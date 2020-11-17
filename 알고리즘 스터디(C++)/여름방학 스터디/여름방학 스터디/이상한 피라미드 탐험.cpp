#include "stdafx.h"

#include <iostream>

using namespace std;

int main()
{
	int T;
	cin >> T;

	int pyramid[142][142] = { 0 };

	for (int t = 0; t < T; ++t)
	{
		int a, b;
		cin >> a >> b;
		int apos[2];
		int bpos[2];


		int sum = 1;
		for (int i = 0; i < 142; ++i)
		{
			for (int j = 0; j < 142; ++j)
			{
				if (i < j)
				{
					break;
				}
				pyramid[i][j] = sum;
				if (sum == a)
				{
					apos[0] = i;
					apos[1] = j;
				}
				if (sum == b)
				{
					bpos[0] = i;
					bpos[1] = j;
				}

				sum++;

			}
		}

		/*cout << apos[0] << " " << apos[1] << endl;
		cout << bpos[0] << " " << bpos[1] << endl;*/
		int dis = 0;


		if ((bpos[0] > apos[0] && bpos[1] < apos[1]) || (apos[0] > bpos[0] && apos[1] < bpos[1]))		// 왼쪽 아래 or 오른쪽 위
		{
			dis = abs(apos[0] - bpos[0]) + abs(apos[1] - bpos[1]);										// a와 b의 x축 차이 + y축 차이
		}
		else if (apos[0] == bpos[0])																	//  x축이 똑같을 때
		{
			dis = abs(apos[1] - bpos[1]);																// a와 b의 y축 차이
		}
		else if (apos[1] == bpos[1])																	// y축이 같을 때
		{		
			dis = abs(apos[0] - bpos[0]);																// x축의 차이
		}
		else if((bpos[0] > apos[0] && bpos[1] > apos[1]))												// 오른쪽 아래
		{
			if (bpos[0] - apos[0] > bpos[1] - apos[1])													// 오른쪽아래애서 x축의 차이가 y축의 차이보다 클 때
			{
				dis = bpos[1] - apos[1] + (bpos[0] - (apos[0] + bpos[1] - apos[1]));					// b의 y - a의 y + ( b의 x - ( a의 x + b의 y - a의 y)
			}
			else
			{
				dis = bpos[0] - apos[0] + (bpos[1] - (apos[1] + bpos[0] - apos[0]));
			}
		}
		else
		{
																										// 왼쪽 위
		}
		{
			if (apos[0] - bpos[0] > apos[1] - bpos[1])
			{
				dis = apos[1] - bpos[1] + (apos[0] - (bpos[0] + apos[1] - bpos[1]));
			}
			else
			{
				dis = apos[0] - bpos[0] + (apos[1] - (bpos[1] + apos[0] - bpos[0]));
			}
		}

		cout << "#" << t + 1 << " " << dis << endl;
	}

}