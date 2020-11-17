#include "stdafx.h"

#include <iostream>

using namespace std;

int pay[4] = { 0 };
int plan[12] = { 0 };
int answer = 0;

void dfs(int month, int price)
{
	if (month > 11)
	{
		if (answer > price)
		{
			answer = price;
		}
		return;
	}

	if (plan[month] == 0)
		dfs(month + 1, price);
	else
	{
		dfs(month + 1, plan[month] * pay[0] + price);

		dfs(month + 1, pay[1] + price);

		dfs(month + 3, pay[2] + price);
	}

}

int main()
{
	int T;
	cin >> T;

	for (int t = 1; t <= T; ++t)
	{

		for (int i = 0; i < 4; ++i)
		{
			cin >> pay[i];
		}

		for (int i = 0; i < 12; ++i)
		{
			cin >> plan[i];
		}

		answer = pay[3];
		dfs(0, 0);

		cout << "#" << t << " " << answer << "\n";
	}
}
