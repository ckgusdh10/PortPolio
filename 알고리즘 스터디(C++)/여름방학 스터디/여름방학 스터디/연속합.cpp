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
		if (cur < 0)									// ���� ���ڰ� 0���� ���� ��
		{
			if (cur > max_num)							// ���ݱ��� max���� ���� �� ���� ���� �� ( ���ݱ��� �������� ���� ��� )
				max_num = cur;
			if (cur < num[i] && max_num < num[i])		// ���� ���� max���� ���� ������ ���� ��
				max_num = num[i];
			cur = num[i];			
			continue;
		}
		if (cur + num[i] > 0)							// ���� ���� ���� ���� ���� 0���� Ŭ ��
		{
			cur += num[i];
		}
		else											// ���� ���� ���� ���� ���� 0���� Ŭ ��
		{
			if (i != n - 1)								// �迭�� ���� �ƴ� ��
			{
				cur = num[i + 1];
				++i;
			}

		}
		if (cur > max_num)								// �ִ밪 ����
			max_num = cur;
	}
	if (cur > max_num)
		max_num = cur;

	cout << max_num << endl;
}
