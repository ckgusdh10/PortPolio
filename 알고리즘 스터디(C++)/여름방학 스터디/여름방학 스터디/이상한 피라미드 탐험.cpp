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


		if ((bpos[0] > apos[0] && bpos[1] < apos[1]) || (apos[0] > bpos[0] && apos[1] < bpos[1]))		// ���� �Ʒ� or ������ ��
		{
			dis = abs(apos[0] - bpos[0]) + abs(apos[1] - bpos[1]);										// a�� b�� x�� ���� + y�� ����
		}
		else if (apos[0] == bpos[0])																	//  x���� �Ȱ��� ��
		{
			dis = abs(apos[1] - bpos[1]);																// a�� b�� y�� ����
		}
		else if (apos[1] == bpos[1])																	// y���� ���� ��
		{		
			dis = abs(apos[0] - bpos[0]);																// x���� ����
		}
		else if((bpos[0] > apos[0] && bpos[1] > apos[1]))												// ������ �Ʒ�
		{
			if (bpos[0] - apos[0] > bpos[1] - apos[1])													// �����ʾƷ��ּ� x���� ���̰� y���� ���̺��� Ŭ ��
			{
				dis = bpos[1] - apos[1] + (bpos[0] - (apos[0] + bpos[1] - apos[1]));					// b�� y - a�� y + ( b�� x - ( a�� x + b�� y - a�� y)
			}
			else
			{
				dis = bpos[0] - apos[0] + (bpos[1] - (apos[1] + bpos[0] - apos[0]));
			}
		}
		else
		{
																										// ���� ��
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